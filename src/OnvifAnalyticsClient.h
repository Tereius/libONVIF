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
#include "OnvifAnalyticsExport.h"

struct OnvifAnalyticsClientPrivate;

/*!
 *
 * \brief Client side service implementations of Onvif Analytics
 *
 */
class ONVIFANALYTICS_EXPORT OnvifAnalyticsClient : public Client {

	Q_OBJECT

public:
	OnvifAnalyticsClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(),
	                     QObject *pParent = nullptr);
	virtual ~OnvifAnalyticsClient();

	static QString GetServiceNamespace() { return SOAP_NAMESPACE_OF_tan; }
	Response<_tad__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_tad__GetServiceCapabilities> &rRequest);
	Response<_tad__DeleteAnalyticsEngineControlResponse> DeleteAnalyticsEngineControl(Request<_tad__DeleteAnalyticsEngineControl> &rRequest);
	Response<_tad__CreateAnalyticsEngineControlResponse> CreateAnalyticsEngineControl(Request<_tad__CreateAnalyticsEngineControl> &rRequest);
	Response<_tad__SetAnalyticsEngineControlResponse> SetAnalyticsEngineControl(Request<_tad__SetAnalyticsEngineControl> &rRequest);
	Response<_tad__GetAnalyticsEngineControlResponse> GetAnalyticsEngineControl(Request<_tad__GetAnalyticsEngineControl> &rRequest);
	Response<_tad__GetAnalyticsEngineControlsResponse> GetAnalyticsEngineControls(Request<_tad__GetAnalyticsEngineControls> &rRequest);
	Response<_tad__GetAnalyticsEngineResponse> GetAnalyticsEngine(Request<_tad__GetAnalyticsEngine> &rRequest);
	Response<_tad__GetAnalyticsEnginesResponse> GetAnalyticsEngines(Request<_tad__GetAnalyticsEngines> &rRequest);
	Response<_tad__SetVideoAnalyticsConfigurationResponse>
	SetVideoAnalyticsConfiguration(Request<_tad__SetVideoAnalyticsConfiguration> &rRequest);
	Response<_tad__GetAnalyticsEngineInputResponse> GetAnalyticsEngineInput(Request<_tad__GetAnalyticsEngineInput> &rRequest);
	Response<_tad__GetAnalyticsEngineInputsResponse> GetAnalyticsEngineInputs(Request<_tad__GetAnalyticsEngineInputs> &rRequest);
	Response<_tad__GetAnalyticsDeviceStreamUriResponse> GetAnalyticsDeviceStreamUri(Request<_tad__GetAnalyticsDeviceStreamUri> &rRequest);
	Response<_tad__GetVideoAnalyticsConfigurationResponse>
	GetVideoAnalyticsConfiguration(Request<_tad__GetVideoAnalyticsConfiguration> &rRequest);
	Response<_tad__CreateAnalyticsEngineInputsResponse> CreateAnalyticsEngineInputs(Request<_tad__CreateAnalyticsEngineInputs> &rRequest);
	Response<_tad__DeleteAnalyticsEngineInputsResponse> DeleteAnalyticsEngineInputs(Request<_tad__DeleteAnalyticsEngineInputs> &rRequest);
	Response<_tad__GetAnalyticsStateResponse> GetAnalyticsState(Request<_tad__GetAnalyticsState> &rRequest);

private:
	Q_DISABLE_COPY(OnvifAnalyticsClient);

	OnvifAnalyticsClientPrivate *mpD;
};
