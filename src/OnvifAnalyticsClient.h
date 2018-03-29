#pragma once
#include "Response.h"
#include "Request.h"
#include "Client.h"
#include "OnvifAnalyticsExport.h"


struct OnvifAnalyticsClientPrivate;

class ONVIFANALYTICS_EXPORT OnvifAnalyticsClient : public Client {

	Q_OBJECT

public:
	OnvifAnalyticsClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~OnvifAnalyticsClient();

	static QString GetServiceNamespace() { return "http://www.onvif.org/ver20/analytics/wsdl"; }
	Response<_tad__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_tad__GetServiceCapabilities> &rRequest);
	Response<_tad__DeleteAnalyticsEngineControlResponse> DeleteAnalyticsEngineControl(Request<_tad__DeleteAnalyticsEngineControl> &rRequest);
	Response<_tad__CreateAnalyticsEngineControlResponse> CreateAnalyticsEngineControl(Request<_tad__CreateAnalyticsEngineControl> &rRequest);
	Response<_tad__SetAnalyticsEngineControlResponse> SetAnalyticsEngineControl(Request<_tad__SetAnalyticsEngineControl> &rRequest);
	Response<_tad__GetAnalyticsEngineControlResponse> GetAnalyticsEngineControl(Request<_tad__GetAnalyticsEngineControl> &rRequest);
	Response<_tad__GetAnalyticsEngineControlsResponse> GetAnalyticsEngineControls(Request<_tad__GetAnalyticsEngineControls> &rRequest);
	Response<_tad__GetAnalyticsEngineResponse> GetAnalyticsEngine(Request<_tad__GetAnalyticsEngine> &rRequest);
	Response<_tad__GetAnalyticsEnginesResponse> GetAnalyticsEngines(Request<_tad__GetAnalyticsEngines> &rRequest);
	Response<_tad__SetVideoAnalyticsConfigurationResponse> SetVideoAnalyticsConfiguration(Request<_tad__SetVideoAnalyticsConfiguration> &rRequest);
	Response<_tad__GetAnalyticsEngineInputResponse> GetAnalyticsEngineInput(Request<_tad__GetAnalyticsEngineInput> &rRequest);
	Response<_tad__GetAnalyticsEngineInputsResponse> GetAnalyticsEngineInputs(Request<_tad__GetAnalyticsEngineInputs> &rRequest);
	Response<_tad__GetAnalyticsDeviceStreamUriResponse> GetAnalyticsDeviceStreamUri(Request<_tad__GetAnalyticsDeviceStreamUri> &rRequest);
	Response<_tad__GetVideoAnalyticsConfigurationResponse> GetVideoAnalyticsConfiguration(Request<_tad__GetVideoAnalyticsConfiguration> &rRequest);
	Response<_tad__CreateAnalyticsEngineInputsResponse> CreateAnalyticsEngineInputs(Request<_tad__CreateAnalyticsEngineInputs> &rRequest);
	Response<_tad__DeleteAnalyticsEngineInputsResponse> DeleteAnalyticsEngineInputs(Request<_tad__DeleteAnalyticsEngineInputs> &rRequest);
	Response<_tad__GetAnalyticsStateResponse> GetAnalyticsState(Request<_tad__GetAnalyticsState> &rRequest);

private:
	Q_DISABLE_COPY(OnvifAnalyticsClient);

	OnvifAnalyticsClientPrivate *mpD;
};
