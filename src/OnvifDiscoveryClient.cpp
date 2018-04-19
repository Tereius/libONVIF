#include "OnvifDiscoveryClient.h"
#include "soapwsddProxy.h"
#include "wsaapi.h"
#include "namespaces.nsmap"
#include <QUuid>


struct OnvifDiscoveryClientPrivate {

	OnvifDiscoveryClientPrivate(OnvifDiscoveryClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		soap_set_namespaces(mProxy.soap, namespaces);
		mpQ->GetCtx()->Release();
	}

	OnvifDiscoveryClient *mpQ;
	wsddProxy mProxy;
};

OnvifDiscoveryClient::OnvifDiscoveryClient(const QUrl &rEndpoint /*= QUrl("soap.udp://239.255.255.250:3702")*/, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) :
Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifDiscoveryClientPrivate(this)) {

	auto soap = GetCtx()->Acquire();
	//soap->ipv4_multicast_ttl = 1; // see setsockopt IPPROTO_IP,
	GetCtx()->Release();
}

OnvifDiscoveryClient::~OnvifDiscoveryClient() {

	delete mpD;
}

DetailedResponse OnvifDiscoveryClient::Hello(HelloTypeRequest &rRequest) {

	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.Hello(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest);
	} while(retry(pSoap));
	DetailedResponse response(ret, GetFaultString(), GetFaultDetail(), ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

DetailedResponse OnvifDiscoveryClient::Bye(ByeTypeRequest &rRequest) {

	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.Bye(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest);
	} while(retry(pSoap));
	DetailedResponse response(ret, GetFaultString(), GetFaultDetail(), ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

DetailedResponse OnvifDiscoveryClient::Probe(ProbeTypeRequest &rRequest, const QString &rMessageId) {

	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	soap_wsa_request(pSoap, rMessageId.toUtf8().constData(), "urn:schemas-xmlsoap-org:ws:2005:04:discovery", "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe");
	do {
		auto ret = mpD->mProxy.Probe(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest);
	} while(retry(pSoap));
	DetailedResponse response(ret, GetFaultString(), GetFaultDetail(), ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

ProbeMatchesResponse OnvifDiscoveryClient::ReceiveProbeMatches() {

	__wsdd__ProbeMatches responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		auto ret = mpD->mProxy.recv_ProbeMatches(responseObject);
	} while(retry(pSoap));
	auto builder = ProbeMatchesResponse::Builder();
	builder.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return builder.Build();
}

void OnvifDiscoveryClient::SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode /*= AUTO*/) {

	// Ignored
}

void OnvifDiscoveryClient::DisableAuth() {

	// Ignored
}
