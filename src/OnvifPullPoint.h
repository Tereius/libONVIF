#pragma once
#include "Client.h"
#include "Response.h"
#include "OnvifEventExport.h"
#include <QThread>


class OnvifEventClient;

class OnvifPullPointWorker : public QThread {

	Q_OBJECT

public:

	OnvifPullPointWorker(const QUrl &rEndpoint, QObject *pParent = nullptr);
	virtual ~OnvifPullPointWorker();
	void Unsubscribe();

signals:
	void MessageReceived(const Response<wsnt__NotificationMessageHolderType> &rResponse);
	void Unsubscribed();

protected:

	void run();

private:

	QUrl mEndpoint;
	OnvifEventClient *mpClient;
};


class ONVIFEVENT_EXPORT OnvifPullPoint : public Client {

	Q_OBJECT

public:
	OnvifPullPoint(const QUrl &rEndpoint, QObject *pParent = nullptr);
	virtual ~OnvifPullPoint();
	void Unsubscribe();
	void Start();

signals:
	void MessageReceived(const Response<_tev__PullMessagesResponse> &rResponse);
	void Unsubscribed();

private:
	Q_DISABLE_COPY(OnvifPullPoint);
	//! Returns the DateTime when the Pull Point will time out. An invalid DateTime is returned if the Pull Point already timed out.
	QDateTime Renew();
	OnvifPullPointWorker *mpWorker;
};
