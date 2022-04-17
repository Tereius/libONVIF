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
#pragma once
#include "Response.h"
#include "Request.h"
#include "Client.h"
#include "OnvifReceiverExport.h"

struct OnvifReceiverClientPrivate;

/*!
 *
 * \brief Client side service implementations of Onvif Receiver
 *
 */
class ONVIFRECEIVER_EXPORT OnvifReceiverClient : public Client {

	Q_OBJECT

public:
	OnvifReceiverClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(),
	                    QObject *pParent = nullptr);
	virtual ~OnvifReceiverClient();

	static QString GetServiceNamespace() { return SOAP_NAMESPACE_OF_trv; }
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
