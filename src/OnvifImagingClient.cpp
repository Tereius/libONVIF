#include "OnvifImagingClient.h"
#include "soapImagingBindingProxy.h"


struct OnvifImagingClientPrivate {

	OnvifImagingClientPrivate(OnvifImagingClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		soap_set_namespaces(mProxy.soap, SoapCtx::GetDefaultNamespaces());
		mpQ->GetCtx()->Release();
	}
	OnvifImagingClient *mpQ;
	ImagingBindingProxy mProxy;
};

OnvifImagingClient::OnvifImagingClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) : Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifImagingClientPrivate(this)) {
}

OnvifImagingClient::~OnvifImagingClient() {

	delete mpD;
}

Response<_timg__GetServiceCapabilitiesResponse> OnvifImagingClient::GetServiceCapabilities(Request<_timg__GetServiceCapabilities> &rRequest) {

	_timg__GetServiceCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_timg__GetServiceCapabilitiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_timg__GetImagingSettingsResponse> OnvifImagingClient::GetImagingSettings(Request<_timg__GetImagingSettings> &rRequest) {

	_timg__GetImagingSettingsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetImagingSettings(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_timg__GetImagingSettingsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_timg__SetImagingSettingsResponse> OnvifImagingClient::SetImagingSettings(Request<_timg__SetImagingSettings> &rRequest) {

	_timg__SetImagingSettingsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetImagingSettings(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_timg__SetImagingSettingsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_timg__GetOptionsResponse> OnvifImagingClient::GetOptions(Request<_timg__GetOptions> &rRequest) {

	_timg__GetOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_timg__GetOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_timg__MoveResponse> OnvifImagingClient::Move(Request<_timg__Move> &rRequest) {

	_timg__MoveResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.Move(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_timg__MoveResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_timg__StopResponse> OnvifImagingClient::Stop(Request<_timg__Stop> &rRequest) {

	_timg__StopResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.Stop(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_timg__StopResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_timg__GetStatusResponse> OnvifImagingClient::GetStatus(Request<_timg__GetStatus> &rRequest) {

	_timg__GetStatusResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetStatus(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_timg__GetStatusResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_timg__GetMoveOptionsResponse> OnvifImagingClient::GetMoveOptions(Request<_timg__GetMoveOptions> &rRequest) {

	_timg__GetMoveOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetMoveOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_timg__GetMoveOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_timg__GetPresetsResponse> OnvifImagingClient::GetPresets(Request<_timg__GetPresets> &rRequest) {

	_timg__GetPresetsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetPresets(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_timg__GetPresetsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_timg__GetCurrentPresetResponse> OnvifImagingClient::GetCurrentPreset(Request<_timg__GetCurrentPreset> &rRequest) {

	_timg__GetCurrentPresetResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCurrentPreset(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_timg__GetCurrentPresetResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_timg__SetCurrentPresetResponse> OnvifImagingClient::SetCurrentPreset(Request<_timg__SetCurrentPreset> &rRequest) {

	_timg__SetCurrentPresetResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetCurrentPreset(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_timg__SetCurrentPresetResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}
