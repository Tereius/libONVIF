#include "OnvifReplayClient.h"
#include "soapReplayBindingProxy.h"


struct OnvifReplayClientPrivate {
	OnvifReplayClientPrivate(OnvifReplayClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		mpQ->GetCtx()->Release();
	}

	OnvifReplayClient *mpQ;
	ReplayBindingProxy mProxy;
};

OnvifReplayClient::OnvifReplayClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) :
Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifReplayClientPrivate(this)) {

}

OnvifReplayClient::~OnvifReplayClient() {

	delete mpD;
}

Response<_trp__GetServiceCapabilitiesResponse> OnvifReplayClient::GetServiceCapabilities(Request<_trp__GetServiceCapabilities> &rRequest) {

	_trp__GetServiceCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trp__GetServiceCapabilitiesResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_trp__GetReplayUriResponse> OnvifReplayClient::GetReplayUri(Request<_trp__GetReplayUri> &rRequest) {

	_trp__GetReplayUriResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetReplayUri(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trp__GetReplayUriResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_trp__GetReplayConfigurationResponse> OnvifReplayClient::GetReplayConfiguration(Request<_trp__GetReplayConfiguration> &rRequest) {

	_trp__GetReplayConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetReplayConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trp__GetReplayConfigurationResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_trp__SetReplayConfigurationResponse> OnvifReplayClient::SetReplayConfiguration(Request<_trp__SetReplayConfiguration> &rRequest) {

	_trp__SetReplayConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetReplayConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trp__SetReplayConfigurationResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}
