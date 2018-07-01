#pragma once
#include "Response.h"
#include "Client.h"
#include <QObject>
#include <QUrl>


struct OnvifDevicePrivate;

class OnvifDevice : public QObject {

	Q_OBJECT

public:
	OnvifDevice(const QUrl &rDeviceEndpoint, QObject *pParent = nullptr);
	virtual ~OnvifDevice();

	void SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode = AUTO);
	SimpleResponse Initialize();
	SimpleResponse InitializeTopicSet();

private:

	OnvifDevicePrivate *mpD;
};