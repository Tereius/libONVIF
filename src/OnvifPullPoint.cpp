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

}

void OnvifPullPointWorker::run() {

	mpClient->GetCtx()->Save();

	int messageLimit = PULL_POINT_DEFAULT_MSG_LIMIT;
	int timeoutLimit = PULL_POINT_DEFAULT_TIMEOUT; // 1 h
	int pullFaultCount = 0;
	bool shortPull = true; // The first pull should have a short timeout so we can check if it's working.

	qDebug() << "Starting new Pull Point:" << mpClient->GetEndpointString();

	while(!isInterruptionRequested() && pullFaultCount < PULL_POINT_MAX_RETRIES) {

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
			}
		}
	}
	mpClient->GetCtx()->Restore();
	emit Unsubscribed();
	Request<_wsnt__Unsubscribe> req;
	auto resp = mpClient->Unsubscribe(req);
	if(!resp) {
		qWarning() << "Couldn't unsubscribe from Pull Point:" << mpClient->GetEndpointString();
	}
}

void OnvifPullPointWorker::Unsubscribe() {

	this->requestInterruption();
	mpClient->GetCtx()->ForceSocketClose();
	this->start();
}

OnvifPullPoint::OnvifPullPoint(const QUrl &rEndpoint, QObject *pParent /*= nullptr*/) :
Client(rEndpoint, QSharedPointer<SoapCtx>::create(), pParent),
mpWorker(new OnvifPullPointWorker(rEndpoint, this)) {

	connect(mpWorker, &OnvifPullPointWorker::finished, mpWorker, &QObject::deleteLater);
}

OnvifPullPoint::~OnvifPullPoint() {

	Unsubscribe();
}

void OnvifPullPoint::Unsubscribe() {

	mpWorker->Unsubscribe();
}

void OnvifPullPoint::Start() {

	mpWorker->start();
}
