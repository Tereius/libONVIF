#include "OnvifEventClient.h"
#include "soapPullPointSubscriptionBindingProxy.h"
#include "wsaapi.h"


struct OnvifEventClientPrivate {

	OnvifEventClientPrivate(OnvifEventClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		mpQ->GetCtx()->Release();
	}
	OnvifEventClient *mpQ;
	PullPointSubscriptionBindingProxy mProxy;
};

OnvifEventClient::OnvifEventClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) :
Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifEventClientPrivate(this)) {

}

OnvifEventClient::~OnvifEventClient() {

	delete mpD;
}

ArbitraryResponse<QSharedPointer<OnvifPullPoint>> OnvifEventClient::CreatePullPointSubscription(Request<_tev__CreatePullPointSubscription> &rRequest) {

	_tev__CreatePullPointSubscriptionResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/EventPortType/CreatePullPointSubscriptionRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		auto ret = mpD->mProxy.CreatePullPointSubscription(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tev__CreatePullPointSubscriptionResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	ArbitraryResponse<QSharedPointer<OnvifPullPoint>> finalResponse(response);
	if(response && response.getResultObject()) {
		auto pullPointEndpoint = QUrl(response.getResultObject()->SubscriptionReference.Address);
		if(pullPointEndpoint.isValid()) {
			auto pullPoint = QSharedPointer<OnvifPullPoint>::create(pullPointEndpoint);
			finalResponse.SetResultObject(pullPoint);
		}
		else {
			finalResponse = DetailedResponse(GENERIC_FAULT, "Given Pull Point url is invalid.", response.getResultObject()->SubscriptionReference.Address);
		}
	}
	return finalResponse;
}

Response<_tev__PullMessagesResponse> OnvifEventClient::PullMessages(Request<_tev__PullMessages> &rRequest) {

	_tev__PullMessagesResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/PullPointSubscription/PullMessagesRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.PullMessages(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tev__PullMessagesResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tev__SeekResponse> OnvifEventClient::Seek(Request<_tev__Seek> &rRequest, const QUrl &rEndpoint) {

	_tev__SeekResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/PullPointSubscription/SeekRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.Seek(rEndpoint.toString().toStdString().c_str(), action, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tev__SeekResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_wsnt__RenewResponse> OnvifEventClient::Renew(Request<_wsnt__Renew> &rRequest) {

	_wsnt__RenewResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/SubscriptionManager/RenewRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.Renew(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_wsnt__RenewResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_wsnt__UnsubscribeResponse> OnvifEventClient::Unsubscribe(Request<_wsnt__Unsubscribe> &rRequest) {

	_wsnt__UnsubscribeResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/SubscriptionManager/UnsubscribeRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.Unsubscribe(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_wsnt__UnsubscribeResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tev__SetSynchronizationPointResponse> OnvifEventClient::SetSynchronizationPoint(Request<_tev__SetSynchronizationPoint> &rRequest) {

	_tev__SetSynchronizationPointResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/PullPointSubscription/SetSynchronizationPointRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.SetSynchronizationPoint(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tev__SetSynchronizationPointResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tev__GetServiceCapabilitiesResponse> OnvifEventClient::GetServiceCapabilities(Request<_tev__GetServiceCapabilities> &rRequest) {

	_tev__GetServiceCapabilitiesResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/EventPortType/GetServiceCapabilitiesRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tev__GetServiceCapabilitiesResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_tev__GetEventPropertiesResponse> OnvifEventClient::GetEventProperties(Request<_tev__GetEventProperties> &rRequest) {

	_tev__GetEventPropertiesResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/EventPortType/GetEventPropertiesRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.GetEventProperties(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_tev__GetEventPropertiesResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_wsnt__SubscribeResponse> OnvifEventClient::Subscribe(Request<_wsnt__Subscribe> &rRequest) {

	_wsnt__SubscribeResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/NotificationProducer/SubscribeRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.Subscribe(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_wsnt__SubscribeResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_wsnt__GetCurrentMessageResponse> OnvifEventClient::GetCurrentMessage(Request<_wsnt__GetCurrentMessage> &rRequest) {

	_wsnt__GetCurrentMessageResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/NotificationProducer/GetCurrentMessageRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.GetCurrentMessage(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_wsnt__GetCurrentMessageResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

SimpleResponse OnvifEventClient::send_Notify(Request<_wsnt__Notify> &rRequest) {

	auto action = "http://docs.oasis-open.org/wsn/bw-2/NotificationConsumer/Notify";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.send_Notify(qPrintable(GetEndpointString()), action, &rRequest);
	} while(retry(pSoap));
	SimpleResponse response(ret, mpD->mProxy.soap_fault_string(), mpD->mProxy.soap_fault_detail());
	releaseCtx(pSoap);
	return response;
}

Response<_wsnt__Notify> OnvifEventClient::recv_Notify() {

	__tev__Notify responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.recv_Notify(responseObject);
	} while(retry(pSoap));
	Response<_wsnt__Notify> response(ret, mpD->mProxy.soap_fault_string(), mpD->mProxy.soap_fault_detail(), ret == SOAP_OK && responseObject.wsnt__Notify ? responseObject.wsnt__Notify->soap_dup() : nullptr);
	releaseCtx(pSoap);
	return response;
}

SimpleResponse OnvifEventClient::recv_Notify_empty_response() {

	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.recv_Notify_empty_response();
	} while(retry(pSoap));
	SimpleResponse response(ret, mpD->mProxy.soap_fault_string(), mpD->mProxy.soap_fault_detail());
	releaseCtx(pSoap);
	return response;
}

SimpleResponse OnvifEventClient::Notify(Request<_wsnt__Notify> &rRequest) {

	auto action = "http://docs.oasis-open.org/wsn/bw-2/NotificationConsumer/Notify";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.Notify(qPrintable(GetEndpointString()), action, &rRequest);
	} while(retry(pSoap));
	SimpleResponse response(ret, mpD->mProxy.soap_fault_string(), mpD->mProxy.soap_fault_detail());
	releaseCtx(pSoap);
	return response;
}

Response<_wsnt__GetMessagesResponse> OnvifEventClient::GetMessages(Request<_wsnt__GetMessages> &rRequest) {

	_wsnt__GetMessagesResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/PullPoint/GetMessagesRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.GetMessages(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_wsnt__GetMessagesResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_wsnt__DestroyPullPointResponse> OnvifEventClient::DestroyPullPoint(Request<_wsnt__DestroyPullPoint> &rRequest) {

	_wsnt__DestroyPullPointResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/PullPoint/DestroyPullPointRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.DestroyPullPoint(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_wsnt__DestroyPullPointResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_wsnt__PauseSubscriptionResponse> OnvifEventClient::PauseSubscription(Request<_wsnt__PauseSubscription> &rRequest) {

	_wsnt__PauseSubscriptionResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/PausableSubscriptionManager/PauseSubscriptionRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.PauseSubscription(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_wsnt__PauseSubscriptionResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

Response<_wsnt__ResumeSubscriptionResponse> OnvifEventClient::ResumeSubscription(Request<_wsnt__ResumeSubscription> &rRequest) {

	_wsnt__ResumeSubscriptionResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/PausableSubscriptionManager/ResumeSubscriptionRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.ResumeSubscription(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_wsnt__ResumeSubscriptionResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	return response;
}

QSharedPointer<OnvifPullPoint> OnvifEventClient::CreatePullPoint(Request<_wsnt__CreatePullPoint> &rRequest) {

	_wsnt__CreatePullPointResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/CreatePullPoint/CreatePullPointRequest";
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.CreatePullPoint(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	Response<_wsnt__CreatePullPointResponse> response(ret, GetFaultString(), GetFaultDetail(), ret == SOAP_OK ? &responseObject : nullptr, ret != SOAP_OK && pSoap->fault ? pSoap->fault->SOAP_ENV__Detail : nullptr);
	releaseCtx(pSoap);
	if(response && response.getResultObject()) {
		auto pullPoint = QSharedPointer<OnvifPullPoint>::create(QUrl(response.getResultObject()->PullPoint.Address));
	}
	return nullptr;
}
