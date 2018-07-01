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
#include "Request.h"
#include "OnvifEventClient.h"
#include <QThread>
#include <QDebug>


#define PULL_POINT_MAX_RETRIES 10
#define PULL_POINT_DEFAULT_TIMEOUT 3600000
#define PULL_POINT_DEFAULT_MSG_LIMIT 100

OnvifPullPointWorker::OnvifPullPointWorker(const QUrl &rEndpoint, QObject *pParent) :
	QThread(pParent),
	mEndpoint(rEndpoint),
	mpClient(new OnvifEventClient(mEndpoint, QSharedPointer<SoapCtx>::create(), this)) {

	mpClient->GetCtx()->EnableOModeFlags(SOAP_IO_KEEPALIVE);
	mpClient->GetCtx()->EnableIModeFlags(SOAP_IO_KEEPALIVE);
}

OnvifPullPointWorker::~OnvifPullPointWorker() {

	StopListening();
}

void OnvifPullPointWorker::run() {

	mpClient->GetCtx()->Save();

	int messageLimit = PULL_POINT_DEFAULT_MSG_LIMIT;
	int timeoutLimit = PULL_POINT_DEFAULT_TIMEOUT; // 1 h
	int pullFaultCount = 0;
	bool shortPull = true; // The first pull should have a short timeout so we can check if it's working.

	qDebug() << "Starting new Pull Point:" << mpClient->GetEndpointString();

	while(!isInterruptionRequested() /*&& pullFaultCount < PULL_POINT_MAX_RETRIES*/) {

		Request<_tev__PullMessages> request;
		if(shortPull) {
			request.MessageLimit = 1;
			request.Timeout = SOAP_DEFAULT_RECEIVE_TIMEOUT;
		}
		else {
			request.MessageLimit = messageLimit;
			request.Timeout = timeoutLimit;
		}
		mpClient->GetCtx()->SetReceiveTimeout(request.Timeout + 10000); // Add some headroom so we don't get a read timeout.
		auto resp = mpClient->PullMessages(request);
		if(resp && resp.GetResultObject()) {
			pullFaultCount = 0;
			shortPull = false;
			qDebug() << "Received new messages from Pull Point:" << mpClient->GetEndpointString();
			for(auto it : resp.GetResultObject()->wsnt__NotificationMessage) {
				emit MessageReceived(Response<wsnt__NotificationMessageHolderType>(it));
			}
		}
		else {
			pullFaultCount++;
			qWarning() << "Pull failed (" << pullFaultCount << "/" << PULL_POINT_MAX_RETRIES << "retries):" << mpClient->GetEndpointString();
			auto faultDetail = resp.GetFaultObject<_tev__PullMessagesFaultResponse>();
			if(faultDetail) {
				if(faultDetail->MaxMessageLimit < messageLimit) {
					messageLimit = faultDetail->MaxMessageLimit;
					qDebug() << "Got new message limit from Pull Point:" << messageLimit << ")";
				}
				if(faultDetail->MaxTimeout < timeoutLimit) {
					timeoutLimit = faultDetail->MaxTimeout;
					qDebug() << "Got new timeout limit from Pull Point:" << timeoutLimit;
				}
			}
			else {
				shortPull = true;
				qWarning() << resp;
				// Sleeping
				for(auto i = 1; i <= 10 && !QThread::isInterruptionRequested(); ++i) QThread::msleep(1000);
			}
		}
	}
	mpClient->GetCtx()->Restore();
	Request<_wsnt__Unsubscribe> req;
	auto resp = mpClient->Unsubscribe(req);
	if(!resp) {
		qWarning() << "Couldn't unsubscribe from Pull Point:" << mpClient->GetEndpointString();
	}
}

Response<_tev__CreatePullPointSubscriptionResponse> OnvifPullPointWorker::Setup() {

	Request<_tev__CreatePullPointSubscription> request;
	request.InitialTerminationTime = new AbsoluteOrRelativeTime(SOAP_DEFAULT_SEND_TIMEOUT + SOAP_DEFAULT_RECEIVE_TIMEOUT + 10000);
	return mpClient->CreatePullPointSubscription(request);
}

bool OnvifPullPointWorker::StartListening() {

	if(!isRunning()) {
		qDebug() << "Starting PullPoint worker";
		auto response = Setup();
		if(response) {
			start();
			qDebug() << "PullPoint worker successfully started";
			return true;
		}
		qWarning() << "Couldn't start PullPoint worker - initial setup failed:" << response.GetCompleteFault();
		return false;
	}
	return true;
}

void OnvifPullPointWorker::StopListening() {

	if(!isInterruptionRequested() && isRunning()) {
		qDebug() << "Stopping PullPoint worker";
		requestInterruption();
		mpClient->GetCtx()->ForceSocketClose();
		const auto waitTimespan = 20000UL;
		auto terminated = wait(waitTimespan);
		if(!terminated) qWarning() << "PullPoint worker couldn't be terminated within time:" << waitTimespan << "ms";
		else qDebug() << "PullPoint worker successfully stopped";
	}
}

struct OnvifPullPointPrivate {

	OnvifPullPointPrivate(OnvifPullPoint *pQ, const QUrl &rEndpoint) :
		mpQ(pQ),
		mEndpoint(rEndpoint),
		mpWorker(nullptr),
		mMutex(QMutex::Recursive),
		mActive(false) {

	}

	OnvifPullPoint *mpQ;
	const QUrl mEndpoint;
	OnvifPullPointWorker *mpWorker;
	QMutex mMutex;
	bool mActive;
};

OnvifPullPoint::OnvifPullPoint(const QUrl &rEndpoint, QObject *pParent /*= nullptr*/) :
	Client(rEndpoint, QSharedPointer<SoapCtx>::create(), pParent),
	mpD(new OnvifPullPointPrivate(this, rEndpoint)) {

}

OnvifPullPoint::~OnvifPullPoint() {

	Stop();
	delete mpD;
}

void OnvifPullPoint::Start() {

	bool activeBackup = mpD->mActive;
	mpD->mMutex.lock();
	if(!mpD->mpWorker) {
		mpD->mpWorker = new OnvifPullPointWorker(mpD->mEndpoint, this);
		mpD->mActive = mpD->mpWorker->StartListening();
		if(!mpD->mActive) {
			Stop();
		}
	}
	mpD->mMutex.unlock();
	if(activeBackup != mpD->mActive) emit ActiveChanged();
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
	if(activeBackup != mpD->mActive) emit ActiveChanged();
}

bool OnvifPullPoint::Active() {

	QMutexLocker lock(&mpD->mMutex);
	return mpD->mActive;
}
