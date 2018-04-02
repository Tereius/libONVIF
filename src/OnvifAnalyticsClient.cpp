#include "OnvifAnalyticsClient.h"
#include "soapAnalyticsDeviceBindingProxy.h"
#include "namespaces.nsmap"


struct OnvifAnalyticsClientPrivate {

	OnvifAnalyticsClientPrivate(OnvifAnalyticsClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		soap_set_namespaces(mProxy.soap, namespaces);
		mpQ->GetCtx()->Release();
	}
	OnvifAnalyticsClient *mpQ;
	AnalyticsDeviceBindingProxy mProxy;
};

OnvifAnalyticsClient::OnvifAnalyticsClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) : Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifAnalyticsClientPrivate(this)) {
}

OnvifAnalyticsClient::~OnvifAnalyticsClient() {

	delete mpD;
}

Response<_tad__GetServiceCapabilitiesResponse> OnvifAnalyticsClient::GetServiceCapabilities(Request<_tad__GetServiceCapabilities> &rRequest) {

	_tad__GetServiceCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__GetServiceCapabilitiesResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__DeleteAnalyticsEngineControlResponse> OnvifAnalyticsClient::DeleteAnalyticsEngineControl(Request<_tad__DeleteAnalyticsEngineControl> &rRequest) {

	_tad__DeleteAnalyticsEngineControlResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.DeleteAnalyticsEngineControl(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__DeleteAnalyticsEngineControlResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__CreateAnalyticsEngineControlResponse> OnvifAnalyticsClient::CreateAnalyticsEngineControl(Request<_tad__CreateAnalyticsEngineControl> &rRequest) {

	_tad__CreateAnalyticsEngineControlResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.CreateAnalyticsEngineControl(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__CreateAnalyticsEngineControlResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__SetAnalyticsEngineControlResponse> OnvifAnalyticsClient::SetAnalyticsEngineControl(Request<_tad__SetAnalyticsEngineControl> &rRequest) {

	_tad__SetAnalyticsEngineControlResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.SetAnalyticsEngineControl(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__SetAnalyticsEngineControlResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__GetAnalyticsEngineControlResponse> OnvifAnalyticsClient::GetAnalyticsEngineControl(Request<_tad__GetAnalyticsEngineControl> &rRequest) {

	_tad__GetAnalyticsEngineControlResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.GetAnalyticsEngineControl(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__GetAnalyticsEngineControlResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__GetAnalyticsEngineControlsResponse> OnvifAnalyticsClient::GetAnalyticsEngineControls(Request<_tad__GetAnalyticsEngineControls> &rRequest) {

	_tad__GetAnalyticsEngineControlsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.GetAnalyticsEngineControls(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__GetAnalyticsEngineControlsResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__GetAnalyticsEngineResponse> OnvifAnalyticsClient::GetAnalyticsEngine(Request<_tad__GetAnalyticsEngine> &rRequest) {

	_tad__GetAnalyticsEngineResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.GetAnalyticsEngine(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__GetAnalyticsEngineResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__GetAnalyticsEnginesResponse> OnvifAnalyticsClient::GetAnalyticsEngines(Request<_tad__GetAnalyticsEngines> & rRequest) {

	_tad__GetAnalyticsEnginesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.GetAnalyticsEngines(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__GetAnalyticsEnginesResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__SetVideoAnalyticsConfigurationResponse> OnvifAnalyticsClient::SetVideoAnalyticsConfiguration(Request<_tad__SetVideoAnalyticsConfiguration> & rRequest) {

	_tad__SetVideoAnalyticsConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.SetVideoAnalyticsConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__SetVideoAnalyticsConfigurationResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__GetAnalyticsEngineInputResponse> OnvifAnalyticsClient::GetAnalyticsEngineInput(Request<_tad__GetAnalyticsEngineInput> & rRequest) {

	_tad__GetAnalyticsEngineInputResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.GetAnalyticsEngineInput(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__GetAnalyticsEngineInputResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__GetAnalyticsEngineInputsResponse> OnvifAnalyticsClient::GetAnalyticsEngineInputs(Request<_tad__GetAnalyticsEngineInputs> & rRequest) {

	_tad__GetAnalyticsEngineInputsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.GetAnalyticsEngineInputs(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__GetAnalyticsEngineInputsResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__GetAnalyticsDeviceStreamUriResponse> OnvifAnalyticsClient::GetAnalyticsDeviceStreamUri(Request<_tad__GetAnalyticsDeviceStreamUri> & rRequest) {

	_tad__GetAnalyticsDeviceStreamUriResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.GetAnalyticsDeviceStreamUri(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__GetAnalyticsDeviceStreamUriResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__GetVideoAnalyticsConfigurationResponse> OnvifAnalyticsClient::GetVideoAnalyticsConfiguration(Request<_tad__GetVideoAnalyticsConfiguration> & rRequest) {

	_tad__GetVideoAnalyticsConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.GetVideoAnalyticsConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__GetVideoAnalyticsConfigurationResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__CreateAnalyticsEngineInputsResponse> OnvifAnalyticsClient::CreateAnalyticsEngineInputs(Request<_tad__CreateAnalyticsEngineInputs> & rRequest) {

	_tad__CreateAnalyticsEngineInputsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.CreateAnalyticsEngineInputs(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__CreateAnalyticsEngineInputsResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__DeleteAnalyticsEngineInputsResponse> OnvifAnalyticsClient::DeleteAnalyticsEngineInputs(Request<_tad__DeleteAnalyticsEngineInputs> & rRequest) {

	_tad__DeleteAnalyticsEngineInputsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.DeleteAnalyticsEngineInputs(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__DeleteAnalyticsEngineInputsResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tad__GetAnalyticsStateResponse> OnvifAnalyticsClient::GetAnalyticsState(Request<_tad__GetAnalyticsState> & rRequest) {

	_tad__GetAnalyticsStateResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.GetAnalyticsState(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tad__GetAnalyticsStateResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}
