/* Copyright(C) 2018 Björn Stresing
 *
 * This program is free software : you can redistribute it and / or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see < http://www.gnu.org/licenses/>.
 */
#include "OnvifPullPoint.h"
#include "OnvifEventClient.h"
#include "Request.h"
#include <QDebug>
#include <QThread>
#include <utility>
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QRegularExpression>
#else
#include <QRegExp>
#endif
#if(QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
#define HAS_QT_RECURSIVEMUTEX
#include <QRecursiveMutex>
#else
#include <QMutex>
#endif

#define PULL_POINT_MAX_RETRIES 10
#define PULL_POINT_DEFAULT_TIMEOUT 3600000
#define PULL_POINT_DEFAULT_MSG_LIMIT 100

OnvifPullPointWorker::OnvifPullPointWorker(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx, QObject *pParent) :
 QThread(pParent), mEndpoint(rEndpoint), mpClient(new OnvifEventClient(mEndpoint, std::move(sharedCtx), this)) {}

OnvifPullPointWorker::~OnvifPullPointWorker() {

	StopListening();
}

void OnvifPullPointWorker::run() {

	mpClient->GetCtx()->Save();

	mpClient->GetCtx()->EnableOModeFlags(SOAP_IO_KEEPALIVE);
	mpClient->GetCtx()->EnableIModeFlags(SOAP_IO_KEEPALIVE);
	int messageLimit = PULL_POINT_DEFAULT_MSG_LIMIT;
	int timeoutLimit = PULL_POINT_DEFAULT_TIMEOUT; // 1 h
	int pullFaultCount = 0;
	bool failedPullHandled = false;
	bool shortPull = true; // The first pull should have a short timeout so we can check if it's working.

	qDebug() << "Starting new pullpoint:" << mpClient->GetEndpointString();

	while(!isInterruptionRequested() && pullFaultCount < PULL_POINT_MAX_RETRIES) {

		Request<_tev__PullMessages> request;
		if(shortPull) {
			request.MessageLimit = 1;
			request.Timeout = SOAP_DEFAULT_RECEIVE_TIMEOUT;
		} else {
			request.MessageLimit = messageLimit;
			request.Timeout = timeoutLimit;
		}
		mpClient->GetCtx()->SetReceiveTimeout(request.Timeout + 10000); // Add some headroom so we don't get a read timeout.
		auto resp = mpClient->PullMessages(request);
		if(resp && resp.GetResultObject()) {
			pullFaultCount = 0;
			shortPull = false;
			qDebug() << "Received new messages from pullpoint:" << mpClient->GetEndpointString();
			for(auto it : resp.GetResultObject()->wsnt__NotificationMessage) {
				if(it->Message.__any) {
					// We have a dom element we try to cast to _tt__Message
					auto *message =
					 const_cast<_tt__Message *>(static_cast<const _tt__Message *>(it->Message.__any->get_node(SOAP_TYPE__tt__Message)));
					if(message) {
						it->Message.Message = message->soap_dup();
					}
				}
				emit MessageReceived(Response<wsnt__NotificationMessageHolderType>(it));
			}

			if(failedPullHandled) {
				emit ResumedPullPoint();
				failedPullHandled = false;
			}
		} else {
			pullFaultCount++;
			qWarning() << "Pull failed (" << pullFaultCount << "/" << PULL_POINT_MAX_RETRIES << "retries):" << mpClient->GetEndpointString();
			auto faultDetail = resp.GetFaultObject<_tev__PullMessagesFaultResponse>();
			if(faultDetail) {
				if(faultDetail->MaxMessageLimit < messageLimit) {
					messageLimit = faultDetail->MaxMessageLimit;
					qDebug() << "Got new message limit from pullpoint:" << messageLimit << ")";
				}
				if(faultDetail->MaxTimeout < timeoutLimit) {
					timeoutLimit = faultDetail->MaxTimeout;
					qDebug() << "Got new timeout limit from pullpoint:" << timeoutLimit;
				}
			} else {
				shortPull = true;
				qWarning() << "Unknown pullpoint fault" << resp;
				// Sleeping
				for(auto i = 1; i <= 10 && !QThread::isInterruptionRequested(); ++i)
					QThread::msleep(1000);
			}
			if(!failedPullHandled && pullFaultCount >= 2) {
				failedPullHandled = true;
				emit LostPullPoint(resp);
			}
			emit UnsuccessfulPull(pullFaultCount, resp);
		}
	}
	mpClient->GetCtx()->Restore();
	Request<_wsnt__Unsubscribe> req;
	auto resp = mpClient->Unsubscribe(req);
	if(!resp) {
		qWarning() << "Couldn't unsubscribe from pullpoint:" << mpClient->GetEndpointString();
	}
}

Response<_tev__CreatePullPointSubscriptionResponse> OnvifPullPointWorker::Setup() {

	Request<_tev__CreatePullPointSubscription> request;
	request.InitialTerminationTime = new AbsoluteOrRelativeTime(SOAP_DEFAULT_SEND_TIMEOUT + SOAP_DEFAULT_RECEIVE_TIMEOUT + 10000);
	return mpClient->CreatePullPointSubscription(request);
}

bool OnvifPullPointWorker::StartListening() {

	if(!isRunning()) {
		qDebug() << "Starting pullpoint worker";
		auto response = Setup();
		if(response) {
			if(response.GetResultObject()) {
				if(response.GetResultObject()->SubscriptionReference.Address) {
					mpClient->SetEndpoint(QUrl::fromUserInput(QString::fromLocal8Bit(response.GetResultObject()->SubscriptionReference.Address)));
				} else if(response.GetResultObject()->SubscriptionReference.__size > 0) {
					// TODO: Don't know why gsop does not deserialize wsa5__EndpointReferenceType? As a workaround we parse it ourselves!
					for(auto i = 0; i < response.GetResultObject()->SubscriptionReference.__size; i++) {
						auto address = response.GetResultObject()->SubscriptionReference.__any[i];
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
						QRegularExpression rx(".+Address>(.*)<\\/");
						QStringList addressList = rx.match(QString::fromLocal8Bit(address)).capturedTexts();
#else
						QRegExp rx(".+Address>(.*)<\\/");
						QStringList addressList = rx.capturedTexts();
#endif
						if(addressList.length() > 1) {
							mpClient->SetEndpoint(addressList[1]);
							break;
						}
					}
				} else {
					qWarning() << "Missing a valid pullpoint subscription reference";
				}
			} else {
				qWarning() << "Missing a valid pullpoint subscription response";
			}
			start();
			qDebug() << "pullpoint worker successfully started";
			return true;
		}
		qWarning() << "Couldn't start pullpoint worker - initial setup failed:" << response.GetCompleteFault();
		return false;
	}
	return true;
}

void OnvifPullPointWorker::StopListening() {

	if(!isInterruptionRequested() && isRunning()) {
		qDebug() << "Stopping pullpoint worker";
		requestInterruption();
		mpClient->GetCtx()->ForceSocketClose();
		const auto waitTimespan = 20000UL;
		auto terminated = wait(waitTimespan);
		if(!terminated)
			qWarning() << "pullpoint worker couldn't be terminated within time:" << waitTimespan << "ms";
		else
			qDebug() << "pullpoint worker successfully stopped";
	}
}

struct OnvifPullPointPrivate {

	OnvifPullPointPrivate(OnvifPullPoint *pQ, const QUrl &rEndpoint) :
	 mpQ(pQ),
	 mEndpoint(rEndpoint),
	 mpWorker(nullptr),
#if defined(HAS_QT_RECURSIVEMUTEX)
	 mMutex(),
#else
	 mMutex(QMutex::Recursive),
#endif
	 mActive(false) {
	}

	OnvifPullPoint *mpQ;
	const QUrl mEndpoint;
	OnvifPullPointWorker *mpWorker;
#if defined(HAS_QT_RECURSIVEMUTEX)
	QRecursiveMutex mMutex;
#else
	QMutex mMutex;
#endif
	bool mActive;
};

OnvifPullPoint::OnvifPullPoint(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/,
                               QObject *pParent /*= nullptr*/) :
 Client(rEndpoint, sharedCtx, pParent), mpD(new OnvifPullPointPrivate(this, rEndpoint)) {}

OnvifPullPoint::~OnvifPullPoint() {

	Stop();
	delete mpD;
}

void OnvifPullPoint::Start() {

	bool activeBackup = mpD->mActive;
	mpD->mMutex.lock();
	if(!mpD->mpWorker) {
		mpD->mpWorker = new OnvifPullPointWorker(mpD->mEndpoint, GetCtx(), this);
		connect(mpD->mpWorker, &OnvifPullPointWorker::MessageReceived, this, &OnvifPullPoint::MessageReceived);
		connect(mpD->mpWorker, &OnvifPullPointWorker::UnsuccessfulPull, this, &OnvifPullPoint::UnsuccessfulPull);
		connect(mpD->mpWorker, &OnvifPullPointWorker::LostPullPoint, this, &OnvifPullPoint::LostPullPoint);
		connect(mpD->mpWorker, &OnvifPullPointWorker::ResumedPullPoint, this, &OnvifPullPoint::ResumedPullPoint);
		mpD->mActive = mpD->mpWorker->StartListening();
		if(!mpD->mActive) {
			Stop();
		}
	}
	mpD->mMutex.unlock();
	if(activeBackup != mpD->mActive) emit ActiveChanged(mpD->mActive);
}

void OnvifPullPoint::Stop() {

	auto activeBackup = mpD->mActive;
	mpD->mMutex.lock();
	if(mpD->mpWorker) {
		mpD->mpWorker->StopListening();
		mpD->mpWorker->deleteLater();
		mpD->mpWorker = nullptr;
		mpD->mActive = false;
	}
	mpD->mMutex.unlock();
	if(activeBackup != mpD->mActive) emit ActiveChanged(mpD->mActive);
}

bool OnvifPullPoint::Active() {

	QMutexLocker lock(&mpD->mMutex);
	return mpD->mActive;
}
