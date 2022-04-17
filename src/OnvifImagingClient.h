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
#include "OnvifImagingExport.h"

struct OnvifImagingClientPrivate;

/*!
 *
 * \brief Client side service implementations of Onvif Imaging
 *
 */
class ONVIFIMAGING_EXPORT OnvifImagingClient : public Client {

	Q_OBJECT

public:
	OnvifImagingClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(),
	                   QObject *pParent = nullptr);
	virtual ~OnvifImagingClient();

	static QString GetServiceNamespace() { return SOAP_NAMESPACE_OF_timg; }
	Response<_timg__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_timg__GetServiceCapabilities> &rRequest);
	Response<_timg__GetImagingSettingsResponse> GetImagingSettings(Request<_timg__GetImagingSettings> &rRequest);
	Response<_timg__SetImagingSettingsResponse> SetImagingSettings(Request<_timg__SetImagingSettings> &rRequest);
	Response<_timg__GetOptionsResponse> GetOptions(Request<_timg__GetOptions> &rRequest);
	Response<_timg__MoveResponse> Move(Request<_timg__Move> &rRequest);
	Response<_timg__StopResponse> Stop(Request<_timg__Stop> &rRequest);
	Response<_timg__GetStatusResponse> GetStatus(Request<_timg__GetStatus> &rRequest);
	Response<_timg__GetMoveOptionsResponse> GetMoveOptions(Request<_timg__GetMoveOptions> &rRequest);
	Response<_timg__GetPresetsResponse> GetPresets(Request<_timg__GetPresets> &rRequest);
	Response<_timg__GetCurrentPresetResponse> GetCurrentPreset(Request<_timg__GetCurrentPreset> &rRequest);
	Response<_timg__SetCurrentPresetResponse> SetCurrentPreset(Request<_timg__SetCurrentPreset> &rRequest);

private:
	Q_DISABLE_COPY(OnvifImagingClient);

	OnvifImagingClientPrivate *mpD;
};