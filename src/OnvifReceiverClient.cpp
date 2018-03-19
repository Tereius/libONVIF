#include "OnvifReceiverClient.h"
#include "soapReceiverBindingProxy.h"


struct OnvifReceiverClientPrivate {
	OnvifReceiverClientPrivate(OnvifReceiverClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		mpQ->GetCtx()->Release();
	}

	OnvifReceiverClient *mpQ;
	ReceiverBindingProxy mProxy;
};

OnvifReceiverClient::OnvifReceiverClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) :
Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifReceiverClientPrivate(this)) {

}

OnvifReceiverClient::~OnvifReceiverClient() {

	delete mpD;
}

Response<_trv__GetServiceCapabilitiesResponse> OnvifReceiverClient::GetServiceCapabilities(Request<_trv__GetServiceCapabilities> &rRequest) {

	_trv__GetServiceCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trv__GetServiceCapabilitiesResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_trv__GetReceiversResponse> OnvifReceiverClient::GetReceivers(Request<_trv__GetReceivers> &rRequest) {

	_trv__GetReceiversResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetReceivers(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trv__GetReceiversResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_trv__GetReceiverResponse> OnvifReceiverClient::GetReceiver(Request<_trv__GetReceiver> &rRequest) {

	_trv__GetReceiverResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetReceiver(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trv__GetReceiverResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_trv__CreateReceiverResponse> OnvifReceiverClient::CreateReceiver(Request<_trv__CreateReceiver> &rRequest) {

	_trv__CreateReceiverResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.CreateReceiver(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trv__CreateReceiverResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_trv__DeleteReceiverResponse> OnvifReceiverClient::DeleteReceiver(Request<_trv__DeleteReceiver> &rRequest) {

	_trv__DeleteReceiverResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeleteReceiver(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trv__DeleteReceiverResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_trv__ConfigureReceiverResponse> OnvifReceiverClient::ConfigureReceiver(Request<_trv__ConfigureReceiver> &rRequest) {

	_trv__ConfigureReceiverResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.ConfigureReceiver(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trv__ConfigureReceiverResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_trv__SetReceiverModeResponse> OnvifReceiverClient::SetReceiverMode(Request<_trv__SetReceiverMode> &rRequest) {

	_trv__SetReceiverModeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetReceiverMode(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trv__SetReceiverModeResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_trv__GetReceiverStateResponse> OnvifReceiverClient::GetReceiverState(Request<_trv__GetReceiverState> &rRequest) {

	_trv__GetReceiverStateResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetReceiverState(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_trv__GetReceiverStateResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}
