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
#include "OnvifEventClient.h"
#include "soapPullPointSubscriptionBindingProxy.h"
#include "wsaapi.h"
#include <functional>


 // TODO: Ugly - copied from proxy class to inject a functor before the namespace map is deallocated in soap_end_recv()
int GetEventPropertiesOther(soap *soap, std::function<int(_tev__GetEventPropertiesResponse &)> nsLookup, const char *endpoint, const char *soap_action, _tev__GetEventProperties *tev__GetEventProperties, _tev__GetEventPropertiesResponse &tev__GetEventPropertiesResponse) {

	struct __tev__GetEventProperties soap_tmp___tev__GetEventProperties;
	auto soap_endpoint = endpoint;
	if(soap_action == NULL)
		soap_action = "http://www.onvif.org/ver10/events/wsdl/EventPortType/GetEventPropertiesRequest";
	soap_tmp___tev__GetEventProperties.tev__GetEventProperties = tev__GetEventProperties;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tev__GetEventProperties(soap, &soap_tmp___tev__GetEventProperties);
	if(soap_begin_count(soap))
		return soap->error;
	if(soap->mode & SOAP_IO_LENGTH) {
		if(soap_envelope_begin_out(soap)
			 || soap_putheader(soap)
			 || soap_body_begin_out(soap)
			 || soap_put___tev__GetEventProperties(soap, &soap_tmp___tev__GetEventProperties, "-tev:GetEventProperties", "")
			 || soap_body_end_out(soap)
			 || soap_envelope_end_out(soap))
			return soap->error;
	}
	if(soap_end_count(soap))
		return soap->error;
	if(soap_connect(soap, soap_endpoint, soap_action)
		 || soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tev__GetEventProperties(soap, &soap_tmp___tev__GetEventProperties, "-tev:GetEventProperties", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap)
		 || soap_end_send(soap))
		return soap_closesock(soap);
	if(!static_cast<_tev__GetEventPropertiesResponse*>(&tev__GetEventPropertiesResponse)) // NULL ref?
		return soap_closesock(soap);
	tev__GetEventPropertiesResponse.soap_default(soap);
	if(soap_begin_recv(soap)
		 || soap_envelope_begin_in(soap)
		 || soap_recv_header(soap)
		 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tev__GetEventPropertiesResponse.soap_get(soap, "tev:GetEventPropertiesResponse", NULL);
	if(soap->error)
		return soap_recv_fault(soap, 0);
	if(soap_body_end_in(soap)
		 || soap_envelope_end_in(soap)
		 || nsLookup(tev__GetEventPropertiesResponse) // ---------------------------------------> inject ns lookups befor they are removed
		 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}


struct OnvifEventClientPrivate {

	OnvifEventClientPrivate(OnvifEventClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		soap_set_namespaces(mProxy.soap, SoapCtx::GetDefaultNamespaces());
		mpQ->GetCtx()->Release();
	}
	OnvifEventClient *mpQ;
	PullPointSubscriptionBindingProxy mProxy;
};

OnvifEventClient::OnvifEventClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) : Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifEventClientPrivate(this)) {
}

OnvifEventClient::~OnvifEventClient() {

	delete mpD;
}

Response<_tev__CreatePullPointSubscriptionResponse> OnvifEventClient::CreatePullPointSubscription(Request<_tev__CreatePullPointSubscription> &rRequest) {

	_tev__CreatePullPointSubscriptionResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/EventPortType/CreatePullPointSubscriptionRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.CreatePullPointSubscription(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tev__CreatePullPointSubscriptionResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tev__PullMessagesResponse> OnvifEventClient::PullMessages(Request<_tev__PullMessages> &rRequest) {

	_tev__PullMessagesResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/PullPointSubscription/PullMessagesRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.PullMessages(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tev__PullMessagesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tev__SeekResponse> OnvifEventClient::Seek(Request<_tev__Seek> &rRequest, const QUrl &rEndpoint) {

	_tev__SeekResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/PullPointSubscription/SeekRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.Seek(rEndpoint.toString().toStdString().c_str(), action, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tev__SeekResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_wsnt__RenewResponse> OnvifEventClient::Renew(Request<_wsnt__Renew> &rRequest) {

	_wsnt__RenewResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/SubscriptionManager/RenewRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.Renew(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_wsnt__RenewResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_wsnt__UnsubscribeResponse> OnvifEventClient::Unsubscribe(Request<_wsnt__Unsubscribe> &rRequest) {

	_wsnt__UnsubscribeResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/SubscriptionManager/UnsubscribeRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.Unsubscribe(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_wsnt__UnsubscribeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tev__SetSynchronizationPointResponse> OnvifEventClient::SetSynchronizationPoint(Request<_tev__SetSynchronizationPoint> &rRequest) {

	_tev__SetSynchronizationPointResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/PullPointSubscription/SetSynchronizationPointRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.SetSynchronizationPoint(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tev__SetSynchronizationPointResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tev__GetServiceCapabilitiesResponse> OnvifEventClient::GetServiceCapabilities(Request<_tev__GetServiceCapabilities> &rRequest) {

	_tev__GetServiceCapabilitiesResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/EventPortType/GetServiceCapabilitiesRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tev__GetServiceCapabilitiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tev__GetEventPropertiesResponse> OnvifEventClient::GetEventProperties(Request<_tev__GetEventProperties> &rRequest) {

	_tev__GetEventPropertiesResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/EventPortType/GetEventPropertiesRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.GetEventProperties(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tev__GetEventPropertiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

ArbitraryResponse<TopicSet> OnvifEventClient::GetParsedEventProperties(Request<_tev__GetEventProperties> &rRequest) {

	_tev__GetEventPropertiesResponse responseObject;
	auto action = "http://www.onvif.org/ver10/events/wsdl/EventPortType/GetEventPropertiesRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	TopicSet topicSet;
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = GetEventPropertiesOther(pSoap, [pSoap, &topicSet](_tev__GetEventPropertiesResponse &tev__GetEventPropertiesResponse) {

			tev__GetEventPropertiesResponse.wstop__TopicSet->soap = pSoap;
			topicSet = TopicSet::FromXml(tev__GetEventPropertiesResponse.wstop__TopicSet);
			return 0;
		}, qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = ArbitraryResponse<TopicSet>::Builder();
	response.From(GetCtx(), topicSet);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_wsnt__SubscribeResponse> OnvifEventClient::Subscribe(Request<_wsnt__Subscribe> &rRequest) {

	_wsnt__SubscribeResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/NotificationProducer/SubscribeRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.Subscribe(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_wsnt__SubscribeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_wsnt__GetCurrentMessageResponse> OnvifEventClient::GetCurrentMessage(Request<_wsnt__GetCurrentMessage> &rRequest) {

	_wsnt__GetCurrentMessageResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/NotificationProducer/GetCurrentMessageRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.GetCurrentMessage(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_wsnt__GetCurrentMessageResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

SimpleResponse OnvifEventClient::send_Notify(Request<_wsnt__Notify> &rRequest) {

	auto action = "http://docs.oasis-open.org/wsn/bw-2/NotificationConsumer/Notify";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.send_Notify(qPrintable(GetEndpointString()), action, &rRequest);
	} while(Retry(pSoap));
	SimpleResponse response(ret, mpD->mProxy.soap_fault_string(), mpD->mProxy.soap_fault_detail());
	ReleaseCtx(pSoap);
	return response;
}

Response<_wsnt__Notify> OnvifEventClient::recv_Notify() {

	__tev__Notify responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.recv_Notify(responseObject);
	} while(Retry(pSoap));
	Response<_wsnt__Notify> response(ret, mpD->mProxy.soap_fault_string(), mpD->mProxy.soap_fault_detail(), ret == SOAP_OK && responseObject.wsnt__Notify ? responseObject.wsnt__Notify->soap_dup() : nullptr);
	ReleaseCtx(pSoap);
	return response;
}

SimpleResponse OnvifEventClient::recv_Notify_empty_response() {

	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.recv_Notify_empty_response();
	} while(Retry(pSoap));
	SimpleResponse response(ret, mpD->mProxy.soap_fault_string(), mpD->mProxy.soap_fault_detail());
	ReleaseCtx(pSoap);
	return response;
}

SimpleResponse OnvifEventClient::Notify(Request<_wsnt__Notify> &rRequest) {

	auto action = "http://docs.oasis-open.org/wsn/bw-2/NotificationConsumer/Notify";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.Notify(qPrintable(GetEndpointString()), action, &rRequest);
	} while(Retry(pSoap));
	SimpleResponse response(ret, mpD->mProxy.soap_fault_string(), mpD->mProxy.soap_fault_detail());
	ReleaseCtx(pSoap);
	return response;
}

Response<_wsnt__GetMessagesResponse> OnvifEventClient::GetMessages(Request<_wsnt__GetMessages> &rRequest) {

	_wsnt__GetMessagesResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/PullPoint/GetMessagesRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.GetMessages(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_wsnt__GetMessagesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_wsnt__DestroyPullPointResponse> OnvifEventClient::DestroyPullPoint(Request<_wsnt__DestroyPullPoint> &rRequest) {

	_wsnt__DestroyPullPointResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/PullPoint/DestroyPullPointRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.DestroyPullPoint(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_wsnt__DestroyPullPointResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_wsnt__PauseSubscriptionResponse> OnvifEventClient::PauseSubscription(Request<_wsnt__PauseSubscription> &rRequest) {

	_wsnt__PauseSubscriptionResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/PausableSubscriptionManager/PauseSubscriptionRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.PauseSubscription(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_wsnt__PauseSubscriptionResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_wsnt__ResumeSubscriptionResponse> OnvifEventClient::ResumeSubscription(Request<_wsnt__ResumeSubscription> &rRequest) {

	_wsnt__ResumeSubscriptionResponse responseObject;
	auto action = "http://docs.oasis-open.org/wsn/bw-2/PausableSubscriptionManager/ResumeSubscriptionRequest";
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		soap_wsa_request(pSoap, soap_wsa_rand_uuid(pSoap), qPrintable(GetEndpointString()), action);
		ret = mpD->mProxy.ResumeSubscription(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_wsnt__ResumeSubscriptionResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}
