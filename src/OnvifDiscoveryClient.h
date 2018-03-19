#pragma once
#include "Client.h"
#include "soapRemoteDiscoveryBindingProxy.h"
#include "Request.h"
#include "Response.h"
#include "OnvifDiscoveryExport.h"
#include <QVector>
#include <QUrl>


class ONVIFDISCOVERY_EXPORT OnvifDiscoveryClient : public Client {

	Q_OBJECT

public:
	OnvifDiscoveryClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr) :
		Client(rEndpoint, sharedCtx, pParent),
		mProxy(GetCtx()->Acquire()) {
		GetCtx()->Release();
	}

	virtual ~OnvifDiscoveryClient() {}

	ArbitraryResponse<QVector<QUrl>> Probe(wsdd__ProbeType &rRequest);

private:
	Q_DISABLE_COPY(OnvifDiscoveryClient);

	RemoteDiscoveryBindingProxy mProxy;
};