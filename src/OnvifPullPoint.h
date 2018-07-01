#pragma once
#include "Client.h"
#include "Response.h"
#include "OnvifEventExport.h"
#include <QThread>
#include <QList>


class OnvifEventClient;

class OnvifPullPointWorker : public QThread {

	Q_OBJECT

public:

	OnvifPullPointWorker(const QUrl &rEndpoint, QObject *pParent = nullptr);
	virtual ~OnvifPullPointWorker();
	bool StartListening();
	void StopListening();

signals:
	void MessageReceived(const Response<wsnt__NotificationMessageHolderType> &rResponse);

protected:

	void run();

private:

	Response<_tev__CreatePullPointSubscriptionResponse> Setup();

	QUrl mEndpoint;
	OnvifEventClient *mpClient;
};


class ONVIFEVENT_EXPORT OnvifPullPoint : public Client {

	Q_OBJECT

public:
	OnvifPullPoint(const QUrl &rEndpoint, QObject *pParent = nullptr);
	virtual ~OnvifPullPoint();
	bool Active();

signals:
	void MessageReceived(const Response<_tev__PullMessagesResponse> &rResponse);
	void Unsubscribed();
	void ActiveChanged();

	public slots:
	void Start();
	void Stop();

private:
	Q_DISABLE_COPY(OnvifPullPoint);

	const QUrl mEndpoint;
	OnvifPullPointWorker *mpWorker;
	QMutex mMutex;
	bool mActive;
};
