#include "OnvifDisplayClient.h"
#include "soapDisplayBindingProxy.h"
#include "namespaces.nsmap"

struct OnvifDisplayClientPrivate {

	OnvifDisplayClientPrivate(OnvifDisplayClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		soap_set_namespaces(mProxy.soap, namespaces);
		mpQ->GetCtx()->Release();
	}
	OnvifDisplayClient *mpQ;
	DisplayBindingProxy mProxy;
};

OnvifDisplayClient::OnvifDisplayClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) : Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifDisplayClientPrivate(this)) {
}

OnvifDisplayClient::~OnvifDisplayClient() {

	delete mpD;
}

Response<_tls__GetServiceCapabilitiesResponse> OnvifDisplayClient::GetServiceCapabilities(Request<_tls__GetServiceCapabilities> &rRequest) {

	_tls__GetServiceCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tls__GetServiceCapabilitiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tls__GetLayoutResponse> OnvifDisplayClient::GetLayout(Request<_tls__GetLayout> &rRequest) {

	_tls__GetLayoutResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetLayout(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tls__GetLayoutResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tls__SetLayoutResponse> OnvifDisplayClient::SetLayout(Request<_tls__SetLayout> &rRequest) {

	_tls__SetLayoutResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetLayout(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tls__SetLayoutResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tls__GetDisplayOptionsResponse> OnvifDisplayClient::GetDisplayOptions(Request<_tls__GetDisplayOptions> &rRequest) {

	_tls__GetDisplayOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetDisplayOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tls__GetDisplayOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tls__GetPaneConfigurationsResponse> OnvifDisplayClient::GetPaneConfigurations(Request<_tls__GetPaneConfigurations> &rRequest) {

	_tls__GetPaneConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetPaneConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tls__GetPaneConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tls__GetPaneConfigurationResponse> OnvifDisplayClient::GetPaneConfiguration(Request<_tls__GetPaneConfiguration> &rRequest) {

	_tls__GetPaneConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetPaneConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tls__GetPaneConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tls__SetPaneConfigurationsResponse> OnvifDisplayClient::SetPaneConfigurations(Request<_tls__SetPaneConfigurations> &rRequest) {

	_tls__SetPaneConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetPaneConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tls__SetPaneConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tls__SetPaneConfigurationResponse> OnvifDisplayClient::SetPaneConfiguration(Request<_tls__SetPaneConfiguration> &rRequest) {

	_tls__SetPaneConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetPaneConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tls__SetPaneConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tls__CreatePaneConfigurationResponse> OnvifDisplayClient::CreatePaneConfiguration(Request<_tls__CreatePaneConfiguration> &rRequest) {

	_tls__CreatePaneConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.CreatePaneConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tls__CreatePaneConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tls__DeletePaneConfigurationResponse> OnvifDisplayClient::DeletePaneConfiguration(Request<_tls__DeletePaneConfiguration> &rRequest) {

	_tls__DeletePaneConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeletePaneConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tls__DeletePaneConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}
