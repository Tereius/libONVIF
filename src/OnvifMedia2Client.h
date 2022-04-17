/* Copyright(C) 2021 Björn Stresing
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
#include "OnvifMedia2Export.h"

struct OnvifMedia2ClientPrivate;

/*!
 *
 * \brief Client side service implementations of Onvif Media2
 *
 */
class ONVIFMEDIA2_EXPORT OnvifMedia2Client : public Client {

	Q_OBJECT

public:
	OnvifMedia2Client(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(),
	                  QObject *pParent = nullptr);
	virtual ~OnvifMedia2Client();

	static QString GetServiceNamespace() { return SOAP_NAMESPACE_OF_tr2; }
	Response<_tr2__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_tr2__GetServiceCapabilities> &rRequest);
	Response<_tr2__CreateProfileResponse> CreateProfile(Request<_tr2__CreateProfile> &rRequest);
	Response<_tr2__GetProfilesResponse> GetProfiles(Request<_tr2__GetProfiles> &rRequest);
	Response<_tr2__AddConfigurationResponse> AddConfiguration(Request<_tr2__AddConfiguration> &rRequest);
	Response<_tr2__RemoveConfigurationResponse> RemoveConfiguration(Request<_tr2__RemoveConfiguration> &rRequest);
	Response<_tr2__DeleteProfileResponse> DeleteProfile(Request<_tr2__DeleteProfile> &rRequest);
	Response<_tr2__GetVideoSourceConfigurationsResponse> GetVideoSourceConfigurations(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetVideoEncoderConfigurationsResponse> GetVideoEncoderConfigurations(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetAudioSourceConfigurationsResponse> GetAudioSourceConfigurations(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetAudioEncoderConfigurationsResponse> GetAudioEncoderConfigurations(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetAnalyticsConfigurationsResponse> GetAnalyticsConfigurations(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetMetadataConfigurationsResponse> GetMetadataConfigurations(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetAudioOutputConfigurationsResponse> GetAudioOutputConfigurations(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetAudioDecoderConfigurationsResponse> GetAudioDecoderConfigurations(Request<tr2__GetConfiguration> &rRequest);
	Response<tr2__SetConfigurationResponse> SetVideoSourceConfiguration(Request<_tr2__SetVideoSourceConfiguration> &rRequest);
	Response<tr2__SetConfigurationResponse> SetVideoEncoderConfiguration(Request<_tr2__SetVideoEncoderConfiguration> &rRequest);
	Response<tr2__SetConfigurationResponse> SetAudioSourceConfiguration(Request<_tr2__SetAudioSourceConfiguration> &rRequest);
	Response<tr2__SetConfigurationResponse> SetAudioEncoderConfiguration(Request<_tr2__SetAudioEncoderConfiguration> &rRequest);
	Response<tr2__SetConfigurationResponse> SetMetadataConfiguration(Request<_tr2__SetMetadataConfiguration> &rRequest);
	Response<tr2__SetConfigurationResponse> SetAudioOutputConfiguration(Request<_tr2__SetAudioOutputConfiguration> &rRequest);
	Response<tr2__SetConfigurationResponse> SetAudioDecoderConfiguration(Request<_tr2__SetAudioDecoderConfiguration> &rRequest);
	Response<_tr2__GetVideoSourceConfigurationOptionsResponse> GetVideoSourceConfigurationOptions(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetVideoEncoderConfigurationOptionsResponse> GetVideoEncoderConfigurationOptions(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetAudioSourceConfigurationOptionsResponse> GetAudioSourceConfigurationOptions(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetAudioEncoderConfigurationOptionsResponse> GetAudioEncoderConfigurationOptions(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetMetadataConfigurationOptionsResponse> GetMetadataConfigurationOptions(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetAudioOutputConfigurationOptionsResponse> GetAudioOutputConfigurationOptions(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetAudioDecoderConfigurationOptionsResponse> GetAudioDecoderConfigurationOptions(Request<tr2__GetConfiguration> &rRequest);
	Response<_tr2__GetVideoEncoderInstancesResponse> GetVideoEncoderInstances(Request<_tr2__GetVideoEncoderInstances> &rRequest);
	Response<_tr2__GetStreamUriResponse> GetStreamUri(Request<_tr2__GetStreamUri> &rRequest);
	Response<tr2__SetConfigurationResponse> StartMulticastStreaming(Request<tr2__StartStopMulticastStreaming> &rRequest);
	Response<tr2__SetConfigurationResponse> StopMulticastStreaming(Request<tr2__StartStopMulticastStreaming> &rRequest);
	Response<_tr2__SetSynchronizationPointResponse> SetSynchronizationPoint(Request<_tr2__SetSynchronizationPoint> &rRequest);
	Response<_tr2__GetSnapshotUriResponse> GetSnapshotUri(Request<_tr2__GetSnapshotUri> &rRequest);
	Response<_tr2__GetVideoSourceModesResponse> GetVideoSourceModes(Request<_tr2__GetVideoSourceModes> &rRequest);
	Response<_tr2__SetVideoSourceModeResponse> SetVideoSourceMode(Request<_tr2__SetVideoSourceMode> &rRequest);
	Response<_tr2__GetOSDsResponse> GetOSDs(Request<_tr2__GetOSDs> &rRequest);
	Response<_tr2__GetOSDOptionsResponse> GetOSDOptions(Request<_tr2__GetOSDOptions> &rRequest);
	Response<tr2__SetConfigurationResponse> SetOSD(Request<_tr2__SetOSD> &rRequest);
	Response<_tr2__CreateOSDResponse> CreateOSD(Request<_tr2__CreateOSD> &rRequest);
	Response<tr2__SetConfigurationResponse> DeleteOSD(Request<_tr2__DeleteOSD> &rRequest);
	Response<_tr2__GetMasksResponse> GetMasks(Request<_tr2__GetMasks> &rRequest);
	Response<_tr2__GetMaskOptionsResponse> GetMaskOptions(Request<_tr2__GetMaskOptions> &rRequest);
	Response<tr2__SetConfigurationResponse> SetMask(Request<_tr2__SetMask> &rRequest);
	Response<_tr2__CreateMaskResponse> CreateMask(Request<_tr2__CreateMask> &rRequest);
	Response<tr2__SetConfigurationResponse> DeleteMask(Request<_tr2__DeleteMask> &rRequest);

private:
	Q_DISABLE_COPY(OnvifMedia2Client);

	OnvifMedia2ClientPrivate *mpD;
};