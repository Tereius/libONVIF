#pragma once
#include "Response.h"
#include "Request.h"
#include "Client.h"
#include "OnvifDisplayExport.h"


struct OnvifDisplayClientPrivate;

class ONVIFDISPLAY_EXPORT OnvifDisplayClient : public Client {

	Q_OBJECT

public:
	OnvifDisplayClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~OnvifDisplayClient();

	static QString GetServiceNamespace() { return "http://www.onvif.org/ver10/display/wsdl"; }
	Response<_tls__GetServiceCapabilitiesResponse>GetServiceCapabilities(Request<_tls__GetServiceCapabilities> &rRequest);
	Response<_tls__GetLayoutResponse>GetLayout(Request<_tls__GetLayout> &rRequest);
	Response<_tls__SetLayoutResponse>SetLayout(Request<_tls__SetLayout> &rRequest);
	Response<_tls__GetDisplayOptionsResponse>GetDisplayOptions(Request<_tls__GetDisplayOptions> &rRequest);
	Response<_tls__GetPaneConfigurationsResponse>GetPaneConfigurations(Request<_tls__GetPaneConfigurations> &rRequest);
	Response<_tls__GetPaneConfigurationResponse>GetPaneConfiguration(Request<_tls__GetPaneConfiguration> &rRequest);
	Response<_tls__SetPaneConfigurationsResponse>SetPaneConfigurations(Request<_tls__SetPaneConfigurations> &rRequest);
	Response<_tls__SetPaneConfigurationResponse>SetPaneConfiguration(Request<_tls__SetPaneConfiguration> &rRequest);
	Response<_tls__CreatePaneConfigurationResponse>CreatePaneConfiguration(Request<_tls__CreatePaneConfiguration> &rRequest);
	Response<_tls__DeletePaneConfigurationResponse>DeletePaneConfiguration(Request<_tls__DeletePaneConfiguration> &rRequest);

private:
	Q_DISABLE_COPY(OnvifDisplayClient);

	OnvifDisplayClientPrivate *mpD;
};