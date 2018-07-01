#pragma once
#include "OnvifPullPoint.h"
#include "Response.h"
#include "Request.h"
#include "Client.h"
#include "OnvifEventExport.h"
#include "Topics.h"


struct OnvifEventClientPrivate;

class ONVIFEVENT_EXPORT OnvifEventClient : public Client {

	Q_OBJECT

public:
	OnvifEventClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~OnvifEventClient();

	static QString GetServiceNamespace() { return "http://www.onvif.org/ver10/events/wsdl"; }
	Response<_tev__CreatePullPointSubscriptionResponse> CreatePullPointSubscription(Request<_tev__CreatePullPointSubscription> &rRequest);
	Response<_tev__PullMessagesResponse> PullMessages(Request<_tev__PullMessages> &rRequest);
	Response<_wsnt__RenewResponse> Renew(Request<_wsnt__Renew> &rRequest);
	Response<_tev__SeekResponse> Seek(Request<_tev__Seek> &rRequest, const QUrl &rEndpoint);
	Response<_wsnt__UnsubscribeResponse> Unsubscribe(Request<_wsnt__Unsubscribe> &rRequest);
	Response<_tev__SetSynchronizationPointResponse> SetSynchronizationPoint(Request<_tev__SetSynchronizationPoint> &rRequest);
	Response<_tev__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_tev__GetServiceCapabilities> &rRequest);
	Response<_tev__GetEventPropertiesResponse> GetEventProperties(Request<_tev__GetEventProperties> &rRequest);
	ArbitraryResponse<TopicSet> GetParsedEventProperties(Request<_tev__GetEventProperties> &rRequest);
	Response<_wsnt__SubscribeResponse> Subscribe(Request<_wsnt__Subscribe> &rRequest);
	Response<_wsnt__GetCurrentMessageResponse> GetCurrentMessage(Request<_wsnt__GetCurrentMessage> &rRequest);
	SimpleResponse send_Notify(Request<_wsnt__Notify> &rRequest);
	Response<_wsnt__Notify> recv_Notify();
	SimpleResponse recv_Notify_empty_response();
	SimpleResponse Notify(Request<_wsnt__Notify> &rRequest);
	Response<_wsnt__GetMessagesResponse> GetMessages(Request<_wsnt__GetMessages> &rRequest);
	Response<_wsnt__DestroyPullPointResponse> DestroyPullPoint(Request<_wsnt__DestroyPullPoint> &rRequest);
	Response<_wsnt__PauseSubscriptionResponse> PauseSubscription(Request<_wsnt__PauseSubscription> &rRequest);
	Response<_wsnt__ResumeSubscriptionResponse> ResumeSubscription(Request<_wsnt__ResumeSubscription> &rRequest);

private:
	Q_DISABLE_COPY(OnvifEventClient);

	OnvifEventClientPrivate *mpD;
};
