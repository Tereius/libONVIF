/* Copyright(C) 2018 Björn Stresing
*
* This program is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.If not, see < http://www.gnu.org/licenses/>.
*/
#include "OnvifPtzClient.h"
#include "soapPTZBindingProxy.h"


struct OnvifPtzClientPrivate {

	OnvifPtzClientPrivate(OnvifPtzClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		soap_set_namespaces(mProxy.soap, SoapCtx::GetDefaultNamespaces());
		mpQ->GetCtx()->Release();
	}
	OnvifPtzClient *mpQ;
	PTZBindingProxy mProxy;
};

OnvifPtzClient::OnvifPtzClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) : Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifPtzClientPrivate(this)) {
}

OnvifPtzClient::~OnvifPtzClient() {

	delete mpD;
}

Response<_tptz__GetServiceCapabilitiesResponse> OnvifPtzClient::GetServiceCapabilities(Request<_tptz__GetServiceCapabilities> &rRequest) {

	_tptz__GetServiceCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetServiceCapabilitiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GetConfigurationsResponse> OnvifPtzClient::GetConfigurations(Request<_tptz__GetConfigurations> &rRequest) {

	_tptz__GetConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GetPresetsResponse> OnvifPtzClient::GetPresets(Request<_tptz__GetPresets> &rRequest) {

	_tptz__GetPresetsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetPresets(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetPresetsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__SetPresetResponse> OnvifPtzClient::SetPreset(Request<_tptz__SetPreset> &rRequest) {

	_tptz__SetPresetResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.SetPreset(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__SetPresetResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__RemovePresetResponse> OnvifPtzClient::RemovePreset(Request<_tptz__RemovePreset> &rRequest) {

	_tptz__RemovePresetResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.RemovePreset(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__RemovePresetResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GotoPresetResponse> OnvifPtzClient::GotoPreset(Request<_tptz__GotoPreset> &rRequest) {

	_tptz__GotoPresetResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GotoPreset(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GotoPresetResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GetStatusResponse> OnvifPtzClient::GetStatus(Request<_tptz__GetStatus> &rRequest) {

	_tptz__GetStatusResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetStatus(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetStatusResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GetConfigurationResponse> OnvifPtzClient::GetConfiguration(Request<_tptz__GetConfiguration> &rRequest) {

	_tptz__GetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GetNodesResponse> OnvifPtzClient::GetNodes(Request<_tptz__GetNodes> &rRequest) {

	_tptz__GetNodesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetNodes(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetNodesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GetNodeResponse> OnvifPtzClient::GetNode(Request<_tptz__GetNode> &rRequest) {

	_tptz__GetNodeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetNode(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetNodeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__SetConfigurationResponse> OnvifPtzClient::SetConfiguration(Request<_tptz__SetConfiguration> &rRequest) {

	_tptz__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.SetConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GetConfigurationOptionsResponse> OnvifPtzClient::GetConfigurationOptions(Request<_tptz__GetConfigurationOptions> &rRequest) {

	_tptz__GetConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetConfigurationOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GotoHomePositionResponse> OnvifPtzClient::GotoHomePosition(Request<_tptz__GotoHomePosition> &rRequest) {

	_tptz__GotoHomePositionResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GotoHomePosition(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GotoHomePositionResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__SetHomePositionResponse> OnvifPtzClient::SetHomePosition(Request<_tptz__SetHomePosition> &rRequest) {

	_tptz__SetHomePositionResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.SetHomePosition(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__SetHomePositionResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__ContinuousMoveResponse> OnvifPtzClient::ContinuousMove(Request<_tptz__ContinuousMove> &rRequest) {

	_tptz__ContinuousMoveResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.ContinuousMove(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__ContinuousMoveResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__RelativeMoveResponse> OnvifPtzClient::RelativeMove(Request<_tptz__RelativeMove> &rRequest) {

	_tptz__RelativeMoveResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.RelativeMove(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__RelativeMoveResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__SendAuxiliaryCommandResponse> OnvifPtzClient::SendAuxiliaryCommand(Request<_tptz__SendAuxiliaryCommand> &rRequest) {

	_tptz__SendAuxiliaryCommandResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.SendAuxiliaryCommand(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__SendAuxiliaryCommandResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__AbsoluteMoveResponse> OnvifPtzClient::AbsoluteMove(Request<_tptz__AbsoluteMove> &rRequest) {

	_tptz__AbsoluteMoveResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.AbsoluteMove(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__AbsoluteMoveResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GeoMoveResponse> OnvifPtzClient::GeoMove(Request<_tptz__GeoMove> &rRequest) {

	_tptz__GeoMoveResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GeoMove(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GeoMoveResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__StopResponse> OnvifPtzClient::Stop(Request<_tptz__Stop> &rRequest) {

	_tptz__StopResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.Stop(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__StopResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GetPresetToursResponse> OnvifPtzClient::GetPresetTours(Request<_tptz__GetPresetTours> &rRequest) {

	_tptz__GetPresetToursResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetPresetTours(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetPresetToursResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GetPresetTourResponse> OnvifPtzClient::GetPresetTour(Request<_tptz__GetPresetTour> &rRequest) {

	_tptz__GetPresetTourResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetPresetTour(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetPresetTourResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GetPresetTourOptionsResponse> OnvifPtzClient::GetPresetTourOptions(Request<_tptz__GetPresetTourOptions> &rRequest) {

	_tptz__GetPresetTourOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetPresetTourOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetPresetTourOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__CreatePresetTourResponse> OnvifPtzClient::CreatePresetTour(Request<_tptz__CreatePresetTour> &rRequest) {

	_tptz__CreatePresetTourResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.CreatePresetTour(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__CreatePresetTourResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__ModifyPresetTourResponse> OnvifPtzClient::ModifyPresetTour(Request<_tptz__ModifyPresetTour> &rRequest) {

	_tptz__ModifyPresetTourResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.ModifyPresetTour(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__ModifyPresetTourResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__OperatePresetTourResponse> OnvifPtzClient::OperatePresetTour(Request<_tptz__OperatePresetTour> &rRequest) {

	_tptz__OperatePresetTourResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.OperatePresetTour(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__OperatePresetTourResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__RemovePresetTourResponse> OnvifPtzClient::RemovePresetTour(Request<_tptz__RemovePresetTour> &rRequest) {

	_tptz__RemovePresetTourResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.RemovePresetTour(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__RemovePresetTourResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tptz__GetCompatibleConfigurationsResponse> OnvifPtzClient::GetCompatibleConfigurations(Request<_tptz__GetCompatibleConfigurations> &rRequest) {

	_tptz__GetCompatibleConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetCompatibleConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tptz__GetCompatibleConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}
