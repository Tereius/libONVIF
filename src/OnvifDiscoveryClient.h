#pragma once
#include "DeleterDuplicator.h"
#include "Request.h"
#include "Response.h"
#include "Client.h"
#include "OnvifDiscoveryExport.h"
#include <QVector>
#include <QUrl>


using ProbeMatchesResponse = Response<__wsdd__ProbeMatches, ProbeMatchesDeleter<__wsdd__ProbeMatches>, ProbeMatchesDuplicator<__wsdd__ProbeMatches>>;
using ResolveTypeResponse = Response<wsdd__ResolveType, ResolveTypeDeleter<wsdd__ResolveType>, ResolveTypeDuplicator<wsdd__ResolveType>>;
using ProbeMatchTypeResponse = Response<wsdd__ProbeMatchesType, ProbeMatchTypeDeleter<wsdd__ProbeMatchesType>, ProbeMatchTypeDuplicator<wsdd__ProbeMatchesType>>;
using HelloTypeRequest = Request<wsdd__HelloType, HelloTypeDeleterReq<wsdd__HelloType>>;
using ProbeTypeRequest = Request<wsdd__ProbeType, ProbeTypeDeleterReq<wsdd__ProbeType>>;
using ByeTypeRequest = Request<wsdd__ByeType, ByeTypeDeleterReq<wsdd__ByeType>>;

struct OnvifDiscoveryClientPrivate;

class ONVIFDISCOVERY_EXPORT OnvifDiscoveryClient : public Client {

	Q_OBJECT

public:
	OnvifDiscoveryClient(const QUrl &rEndpoint = QUrl("soap.udp://239.255.255.250:3702"), QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~OnvifDiscoveryClient();

	DetailedResponse Hello(HelloTypeRequest &rRequest);
	DetailedResponse Bye(ByeTypeRequest &rRequest);
	DetailedResponse Probe(ProbeTypeRequest &rRequest);
	ProbeMatchesResponse ReceiveProbeMatches();

	virtual void SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode = AUTO) final;
	virtual void DisableAuth() final;

private:
	Q_DISABLE_COPY(OnvifDiscoveryClient);

	OnvifDiscoveryClientPrivate *mpD;
};