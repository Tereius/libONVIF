#include "OnvifDiscoveryClient.h"
#include "soapRemoteDiscoveryBindingProxy.h"


struct OnvifDiscoveryClientPrivate {

	OnvifDiscoveryClientPrivate(OnvifDiscoveryClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		mpQ->GetCtx()->Release();
	}
	OnvifDiscoveryClient *mpQ;
	RemoteDiscoveryBindingProxy mProxy;
};

OnvifDiscoveryClient::OnvifDiscoveryClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) :
Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifDiscoveryClientPrivate(this)) {

}

OnvifDiscoveryClient::~OnvifDiscoveryClient() {

	delete mpD;
}


ResolveTypeResponse OnvifDiscoveryClient::Hello(HelloTypeRequest &rRequest) {

	wsdd__ResolveType responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.Hello(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, rRequest, responseObject);
	} while(retry(pSoap));
	ResolveTypeResponse response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

ResolveTypeResponse OnvifDiscoveryClient::Bye(ByeTypeRequest &rRequest) {

	wsdd__ResolveType responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.Bye(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, rRequest, responseObject);
	} while(retry(pSoap));
	ResolveTypeResponse response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

ProbeMatchTypeResponse OnvifDiscoveryClient::Probe(ProbeTypeRequest &rRequest) {

	wsdd__ProbeMatchesType responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.Probe(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, rRequest, responseObject);
	} while(retry(pSoap));
	ProbeMatchTypeResponse response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

void OnvifDiscoveryClient::SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode /*= AUTO*/) {

	// Ignored
}

void OnvifDiscoveryClient::DisableAuth() {

	// Ignored
}
