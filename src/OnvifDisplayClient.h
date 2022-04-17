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
#include "OnvifDisplayExport.h"

struct OnvifDisplayClientPrivate;

/*!
 *
 * \brief Client side service implementations of Onvif Display
 *
 */
class ONVIFDISPLAY_EXPORT OnvifDisplayClient : public Client {

	Q_OBJECT

public:
	OnvifDisplayClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(),
	                   QObject *pParent = nullptr);
	virtual ~OnvifDisplayClient();

	static QString GetServiceNamespace() { return SOAP_NAMESPACE_OF_tls; }
	Response<_tls__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_tls__GetServiceCapabilities> &rRequest);
	Response<_tls__GetLayoutResponse> GetLayout(Request<_tls__GetLayout> &rRequest);
	Response<_tls__SetLayoutResponse> SetLayout(Request<_tls__SetLayout> &rRequest);
	Response<_tls__GetDisplayOptionsResponse> GetDisplayOptions(Request<_tls__GetDisplayOptions> &rRequest);
	Response<_tls__GetPaneConfigurationsResponse> GetPaneConfigurations(Request<_tls__GetPaneConfigurations> &rRequest);
	Response<_tls__GetPaneConfigurationResponse> GetPaneConfiguration(Request<_tls__GetPaneConfiguration> &rRequest);
	Response<_tls__SetPaneConfigurationsResponse> SetPaneConfigurations(Request<_tls__SetPaneConfigurations> &rRequest);
	Response<_tls__SetPaneConfigurationResponse> SetPaneConfiguration(Request<_tls__SetPaneConfiguration> &rRequest);
	Response<_tls__CreatePaneConfigurationResponse> CreatePaneConfiguration(Request<_tls__CreatePaneConfiguration> &rRequest);
	Response<_tls__DeletePaneConfigurationResponse> DeletePaneConfiguration(Request<_tls__DeletePaneConfiguration> &rRequest);

private:
	Q_DISABLE_COPY(OnvifDisplayClient);

	OnvifDisplayClientPrivate *mpD;
};