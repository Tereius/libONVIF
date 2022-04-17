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
#include "OnvifReplayExport.h"

struct OnvifReplayClientPrivate;

/*!
 *
 * \brief Client side service implementations of Onvif Replay
 *
 */
class ONVIFREPLAY_EXPORT OnvifReplayClient : public Client {

	Q_OBJECT

public:
	OnvifReplayClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(),
	                  QObject *pParent = nullptr);
	virtual ~OnvifReplayClient();

	static QString GetServiceNamespace() { return SOAP_NAMESPACE_OF_trp; }
	Response<_trp__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_trp__GetServiceCapabilities> &rRequest);
	Response<_trp__GetReplayUriResponse> GetReplayUri(Request<_trp__GetReplayUri> &rRequest);
	Response<_trp__GetReplayConfigurationResponse> GetReplayConfiguration(Request<_trp__GetReplayConfiguration> &rRequest);
	Response<_trp__SetReplayConfigurationResponse> SetReplayConfiguration(Request<_trp__SetReplayConfiguration> &rRequest);

private:
	Q_DISABLE_COPY(OnvifReplayClient);

	OnvifReplayClientPrivate *mpD;
};
