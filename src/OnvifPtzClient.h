#pragma once
#include "Response.h"
#include "Request.h"
#include "Client.h"
#include "OnvifPtzExport.h"

struct OnvifPtzClientPrivate;

class ONVIFPTZ_EXPORT OnvifPtzClient : public Client {

	Q_OBJECT

public:
	OnvifPtzClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~OnvifPtzClient();

	static QString GetServiceNamespace() { return "http://www.onvif.org/ver20/ptz/wsdl"; }
	Response<_tptz__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_tptz__GetServiceCapabilities> &rRequest);
	Response<_tptz__GetConfigurationsResponse> GetConfigurations(Request<_tptz__GetConfigurations> &rRequest);
	Response<_tptz__GetPresetsResponse> GetPresets(Request<_tptz__GetPresets> &rRequest);
	Response<_tptz__SetPresetResponse> SetPreset(Request<_tptz__SetPreset> &rRequest);
	Response<_tptz__RemovePresetResponse> RemovePreset(Request<_tptz__RemovePreset> &rRequest);
	Response<_tptz__GotoPresetResponse> GotoPreset(Request<_tptz__GotoPreset> &rRequest);
	Response<_tptz__GetStatusResponse> GetStatus(Request<_tptz__GetStatus> &rRequest);
	Response<_tptz__GetConfigurationResponse> GetConfiguration(Request<_tptz__GetConfiguration> &rRequest);
	Response<_tptz__GetNodesResponse> GetNodes(Request<_tptz__GetNodes> &rRequest);
	Response<_tptz__GetNodeResponse> GetNode(Request<_tptz__GetNode> &rRequest);
	Response<_tptz__SetConfigurationResponse> SetConfiguration(Request<_tptz__SetConfiguration> &rRequest);
	Response<_tptz__GetConfigurationOptionsResponse> GetConfigurationOptions(Request<_tptz__GetConfigurationOptions> &rRequest);
	Response<_tptz__GotoHomePositionResponse> GotoHomePosition(Request<_tptz__GotoHomePosition> &rRequest);
	Response<_tptz__SetHomePositionResponse> SetHomePosition(Request<_tptz__SetHomePosition> &rRequest);
	Response<_tptz__ContinuousMoveResponse> ContinuousMove(Request<_tptz__ContinuousMove> &rRequest);
	Response<_tptz__RelativeMoveResponse> RelativeMove(Request<_tptz__RelativeMove> &rRequest);
	Response<_tptz__SendAuxiliaryCommandResponse> SendAuxiliaryCommand(Request<_tptz__SendAuxiliaryCommand> &rRequest);
	Response<_tptz__AbsoluteMoveResponse> AbsoluteMove(Request<_tptz__AbsoluteMove> &rRequest);
	Response<_tptz__GeoMoveResponse> GeoMove(Request<_tptz__GeoMove> &rRequest);
	Response<_tptz__StopResponse> Stop(Request<_tptz__Stop> &rRequest);
	Response<_tptz__GetPresetToursResponse> GetPresetTours(Request<_tptz__GetPresetTours> &rRequest);
	Response<_tptz__GetPresetTourResponse> GetPresetTour(Request<_tptz__GetPresetTour> &rRequest);
	Response<_tptz__GetPresetTourOptionsResponse> GetPresetTourOptions(Request<_tptz__GetPresetTourOptions> &rRequest);
	Response<_tptz__CreatePresetTourResponse> CreatePresetTour(Request<_tptz__CreatePresetTour> &rRequest);
	Response<_tptz__ModifyPresetTourResponse> ModifyPresetTour(Request<_tptz__ModifyPresetTour> &rRequest);
	Response<_tptz__OperatePresetTourResponse> OperatePresetTour(Request<_tptz__OperatePresetTour> &rRequest);
	Response<_tptz__RemovePresetTourResponse> RemovePresetTour(Request<_tptz__RemovePresetTour> &rRequest);
	Response<_tptz__GetCompatibleConfigurationsResponse> GetCompatibleConfigurations(Request<_tptz__GetCompatibleConfigurations> &rRequest);

private:
	Q_DISABLE_COPY(OnvifPtzClient);

	OnvifPtzClientPrivate *mpD;
};
