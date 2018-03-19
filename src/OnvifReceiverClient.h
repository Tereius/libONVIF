#pragma once
#include "Response.h"
#include "Request.h"
#include "Client.h"
#include "OnvifReceiverExport.h"

struct OnvifReceiverClientPrivate;

class ONVIFRECEIVER_EXPORT OnvifReceiverClient : public Client {

	Q_OBJECT

public:
	OnvifReceiverClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~OnvifReceiverClient();

	Response<_trv__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_trv__GetServiceCapabilities> &rRequest);
	Response<_trv__GetReceiversResponse> GetReceivers(Request<_trv__GetReceivers> &rRequest);
	Response<_trv__GetReceiverResponse> GetReceiver(Request<_trv__GetReceiver> &rRequest);
	Response<_trv__CreateReceiverResponse> CreateReceiver(Request<_trv__CreateReceiver> &rRequest);
	Response<_trv__DeleteReceiverResponse> DeleteReceiver(Request<_trv__DeleteReceiver> &rRequest);
	Response<_trv__ConfigureReceiverResponse> ConfigureReceiver(Request<_trv__ConfigureReceiver> &rRequest);
	Response<_trv__SetReceiverModeResponse> SetReceiverMode(Request<_trv__SetReceiverMode> &rRequest);
	Response<_trv__GetReceiverStateResponse> GetReceiverState(Request<_trv__GetReceiverState> &rRequest);

private:
	Q_DISABLE_COPY(OnvifReceiverClient);

	OnvifReceiverClientPrivate *mpD;
};
