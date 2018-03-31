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


Response<wsdd__ResolveType, ResolveTypeDeleter<wsdd__ResolveType>, ResolveTypeDuplicator<wsdd__ResolveType>> OnvifDiscoveryClient::Hello(Request<wsdd__HelloType, ResolveTypeDeleterReq<wsdd__HelloType>> &rRequest) {

	wsdd__ResolveType responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.Hello(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, rRequest, responseObject);
	} while(retry(pSoap));
	Response<wsdd__ResolveType, ResolveTypeDeleter<wsdd__ResolveType>, ResolveTypeDuplicator<wsdd__ResolveType>> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}
/*
Response<wsdd__ResolveType> OnvifDiscoveryClient::Bye(Request<wsdd__ByeType> &rRequest) {

}

Response<wsdd__ProbeMatchesType> OnvifDiscoveryClient::Probe(Request<wsdd__ProbeType> &rRequest) {

}
*/

void OnvifDiscoveryClient::SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode /*= AUTO*/) {
	
	// Ignored
}

void OnvifDiscoveryClient::DisableAuth() {

	// Ignored
}


/*
void wsdd_event_Hello(struct soap *  	soap,
unsigned int  	InstanceId,
const char *  	SequenceId,
unsigned int  	MessageNumber,
const char *  	MessageID,
const char *  	RelatesTo,
const char *  	EndpointReference,
const char *  	Types,
const char *  	Scopes,
const char *  	MatchBy,
const char *  	XAddrs,
unsigned int  	MetadataVersion) {

}

void wsdd_event_Bye(struct soap *  	soap,
unsigned int  	InstanceId,
const char *  	SequenceId,
unsigned int  	MessageNumber,
const char *  	MessageID,
const char *  	RelatesTo,
const char *  	EndpointReference,
const char *  	Types,
const char *  	Scopes,
const char *  	MatchBy,
const char *  	XAddrs,
unsigned int *  	MetadataVersion) {

}

soap_wsdd_mode wsdd_event_Probe(struct soap *  	soap,
const char *  	MessageID,
const char *  	ReplyTo,
const char *  	Types,
const char *  	Scopes,
const char *  	MatchBy,
struct wsdd__ProbeMatchesType *  	matches) {

return SOAP_WSDD_ADHOC;
}

void wsdd_event_ProbeMatches(struct soap *  	soap,
unsigned int  	InstanceId,
const char *  	SequenceId,
unsigned int  	MessageNumber,
const char *  	MessageID,
const char *  	RelatesTo,
struct wsdd__ProbeMatchesType *  	matches) {

}

soap_wsdd_mode wsdd_event_Resolve(struct soap *  	soap,
const char *  	MessageID,
const char *  	ReplyTo,
const char *  	EndpointReference,
struct wsdd__ResolveMatchType *  	match) {

return SOAP_WSDD_ADHOC;
}

void wsdd_event_ResolveMatches(struct soap *  	soap,
unsigned int  	InstanceId,
const char *  	SequenceId,
unsigned int  	MessageNumber,
const char *  	MessageID,
const char *  	RelatesTo,
struct wsdd__ResolveMatchType *  	match) {

}
*/