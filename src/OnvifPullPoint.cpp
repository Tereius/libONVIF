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
		if(resp && resp.getResultObject()) {
			pullFaultCount = 0;
			shortPull = false;
			qDebug() << "Received new messages from Pull Point:" << mpClient->GetEndpointString();
			for(auto it : resp.getResultObject()->wsnt__NotificationMessage) {
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

OnvifPullPoint::OnvifPullPoint(const QUrl &rEndpoint, QObject *pParent /*= nullptr*/) :
	Client(rEndpoint, QSharedPointer<SoapCtx>::create(), pParent),
	mEndpoint(rEndpoint),
	mpWorker(nullptr),
	mMutex(QMutex::Recursive),
	mActive(false) {

}

OnvifPullPoint::~OnvifPullPoint() {

	Stop();
}

void OnvifPullPoint::Start() {

	bool activeBackup = mActive;
	mMutex.lock();
	if(!mpWorker) {
		mpWorker = new OnvifPullPointWorker(mEndpoint, this);
		mActive = mpWorker->StartListening();
		if(!mActive) {
			Stop();
		}
	}
	mMutex.unlock();
	if(activeBackup != mActive) emit ActiveChanged();
}

void OnvifPullPoint::Stop() {

	auto activeBackup = mActive;
	mMutex.lock();
	if(mpWorker) {
		mpWorker->StopListening();
		mpWorker->deleteLater();
		mpWorker = nullptr;
		mActive = false;
	}
	mMutex.unlock();
	if(activeBackup != mActive) emit ActiveChanged();
}

bool OnvifPullPoint::Active() {

	QMutexLocker lock(&mMutex);
	return mActive;
}
