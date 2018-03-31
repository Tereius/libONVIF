#pragma once
#include "DeleterDuplicator.h"
#include "Request.h"
#include "Response.h"
#include "Client.h"
#include "OnvifDiscoveryExport.h"
#include <QVector>
#include <QUrl>


using ResolveTypeResponse = Response<wsdd__ResolveType, ResolveTypeDeleter<wsdd__ResolveType>, ResolveTypeDuplicator<wsdd__ResolveType>>;
using ProbeMatchTypeResponse = Response<wsdd__ProbeMatchesType, ProbeMatchTypeDeleter<wsdd__ProbeMatchesType>, ProbeMatchTypeDuplicator<wsdd__ProbeMatchesType>>;
using HelloTypeRequest = Request<wsdd__HelloType, HelloTypeDeleterReq<wsdd__HelloType>>;
using ProbeTypeRequest = Request<wsdd__ProbeType, ProbeTypeDeleterReq<wsdd__ProbeType>>;
using ByeTypeRequest = Request<wsdd__ByeType, ByeTypeDeleterReq<wsdd__ByeType>>;

struct OnvifDiscoveryClientPrivate;

class ONVIFDISCOVERY_EXPORT OnvifDiscoveryClient : public Client {

	Q_OBJECT

public:
	OnvifDiscoveryClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~OnvifDiscoveryClient();

	ResolveTypeResponse Hello(HelloTypeRequest &rRequest);
	ResolveTypeResponse Bye(ByeTypeRequest &rRequest);
	ProbeMatchTypeResponse Probe(ProbeTypeRequest &rRequest);
	virtual void SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode = AUTO) final;
	virtual void DisableAuth() final;

private:
	Q_DISABLE_COPY(OnvifDiscoveryClient);

	OnvifDiscoveryClientPrivate *mpD;
};