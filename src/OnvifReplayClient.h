#pragma once
#include "Response.h"
#include "Request.h"
#include "Client.h"
#include "OnvifReplayExport.h"


struct OnvifReplayClientPrivate;

class ONVIFREPLAY_EXPORT OnvifReplayClient : public Client {

	Q_OBJECT

public:
	OnvifReplayClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~OnvifReplayClient();

	Response<_trp__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_trp__GetServiceCapabilities> &rRequest);
	Response<_trp__GetReplayUriResponse> GetReplayUri(Request<_trp__GetReplayUri> &rRequest);
	Response<_trp__GetReplayConfigurationResponse> GetReplayConfiguration(Request<_trp__GetReplayConfiguration> &rRequest);
	Response<_trp__SetReplayConfigurationResponse> SetReplayConfiguration(Request<_trp__SetReplayConfiguration> &rRequest);

private:
	Q_DISABLE_COPY(OnvifReplayClient);

	OnvifReplayClientPrivate *mpD;
};
