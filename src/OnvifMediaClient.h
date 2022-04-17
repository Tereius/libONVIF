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
#include "OnvifMediaExport.h"

struct OnvifMediaClientPrivate;

/*!
 *
 * \brief Client side service implementations of Onvif Media
 *
 */
class ONVIFMEDIA_EXPORT OnvifMediaClient : public Client {

	Q_OBJECT

public:
	OnvifMediaClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~OnvifMediaClient();

	static QString GetServiceNamespace() { return SOAP_NAMESPACE_OF_trt; }
	Response<_trt__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_trt__GetServiceCapabilities> &rRequest);
	Response<_trt__GetVideoSourcesResponse> GetVideoSources(Request<_trt__GetVideoSources> &rRequest);
	Response<_trt__GetAudioSourcesResponse> GetAudioSources(Request<_trt__GetAudioSources> &rRequest);
	Response<_trt__GetAudioOutputsResponse> GetAudioOutputs(Request<_trt__GetAudioOutputs> &rRequest);
	Response<_trt__CreateProfileResponse> CreateProfile(Request<_trt__CreateProfile> &rRequest);
	Response<_trt__GetProfileResponse> GetProfile(Request<_trt__GetProfile> &rRequest);
	Response<_trt__GetProfilesResponse> GetProfiles(Request<_trt__GetProfiles> &rRequest);
	Response<_trt__AddVideoEncoderConfigurationResponse> AddVideoEncoderConfiguration(Request<_trt__AddVideoEncoderConfiguration> &rRequest);
	Response<_trt__AddVideoSourceConfigurationResponse> AddVideoSourceConfiguration(Request<_trt__AddVideoSourceConfiguration> &rRequest);
	Response<_trt__AddAudioEncoderConfigurationResponse> AddAudioEncoderConfiguration(Request<_trt__AddAudioEncoderConfiguration> &rRequest);
	Response<_trt__AddAudioSourceConfigurationResponse> AddAudioSourceConfiguration(Request<_trt__AddAudioSourceConfiguration> &rRequest);
	Response<_trt__AddPTZConfigurationResponse> AddPTZConfiguration(Request<_trt__AddPTZConfiguration> &rRequest);
	Response<_trt__AddVideoAnalyticsConfigurationResponse>
	AddVideoAnalyticsConfiguration(Request<_trt__AddVideoAnalyticsConfiguration> &rRequest);
	Response<_trt__AddMetadataConfigurationResponse> AddMetadataConfiguration(Request<_trt__AddMetadataConfiguration> &rRequest);
	Response<_trt__AddAudioOutputConfigurationResponse> AddAudioOutputConfiguration(Request<_trt__AddAudioOutputConfiguration> &rRequest);
	Response<_trt__AddAudioDecoderConfigurationResponse> AddAudioDecoderConfiguration(Request<_trt__AddAudioDecoderConfiguration> &rRequest);
	Response<_trt__RemoveVideoEncoderConfigurationResponse>
	RemoveVideoEncoderConfiguration(Request<_trt__RemoveVideoEncoderConfiguration> &rRequest);
	Response<_trt__RemoveVideoSourceConfigurationResponse>
	RemoveVideoSourceConfiguration(Request<_trt__RemoveVideoSourceConfiguration> &rRequest);
	Response<_trt__RemoveAudioEncoderConfigurationResponse>
	RemoveAudioEncoderConfiguration(Request<_trt__RemoveAudioEncoderConfiguration> &rRequest);
	Response<_trt__RemoveAudioSourceConfigurationResponse>
	RemoveAudioSourceConfiguration(Request<_trt__RemoveAudioSourceConfiguration> &rRequest);
	Response<_trt__RemovePTZConfigurationResponse> RemovePTZConfiguration(Request<_trt__RemovePTZConfiguration> &rRequest);
	Response<_trt__RemoveVideoAnalyticsConfigurationResponse>
	RemoveVideoAnalyticsConfiguration(Request<_trt__RemoveVideoAnalyticsConfiguration> &rRequest);
	Response<_trt__RemoveMetadataConfigurationResponse> RemoveMetadataConfiguration(Request<_trt__RemoveMetadataConfiguration> &rRequest);
	Response<_trt__RemoveAudioOutputConfigurationResponse>
	RemoveAudioOutputConfiguration(Request<_trt__RemoveAudioOutputConfiguration> &rRequest);
	Response<_trt__RemoveAudioDecoderConfigurationResponse>
	RemoveAudioDecoderConfiguration(Request<_trt__RemoveAudioDecoderConfiguration> &rRequest);
	Response<_trt__DeleteProfileResponse> DeleteProfile(Request<_trt__DeleteProfile> &rRequest);
	Response<_trt__GetVideoSourceConfigurationsResponse> GetVideoSourceConfigurations(Request<_trt__GetVideoSourceConfigurations> &rRequest);
	Response<_trt__GetVideoEncoderConfigurationsResponse>
	GetVideoEncoderConfigurations(Request<_trt__GetVideoEncoderConfigurations> &rRequest);
	Response<_trt__GetAudioSourceConfigurationsResponse> GetAudioSourceConfigurations(Request<_trt__GetAudioSourceConfigurations> &rRequest);
	Response<_trt__GetAudioEncoderConfigurationsResponse>
	GetAudioEncoderConfigurations(Request<_trt__GetAudioEncoderConfigurations> &rRequest);
	Response<_trt__GetVideoAnalyticsConfigurationsResponse>
	GetVideoAnalyticsConfigurations(Request<_trt__GetVideoAnalyticsConfigurations> &rRequest);
	Response<_trt__GetMetadataConfigurationsResponse> GetMetadataConfigurations(Request<_trt__GetMetadataConfigurations> &rRequest);
	Response<_trt__GetAudioOutputConfigurationsResponse> GetAudioOutputConfigurations(Request<_trt__GetAudioOutputConfigurations> &rRequest);
	Response<_trt__GetAudioDecoderConfigurationsResponse>
	GetAudioDecoderConfigurations(Request<_trt__GetAudioDecoderConfigurations> &rRequest);
	Response<_trt__GetVideoSourceConfigurationResponse> GetVideoSourceConfiguration(Request<_trt__GetVideoSourceConfiguration> &rRequest);
	Response<_trt__GetVideoEncoderConfigurationResponse> GetVideoEncoderConfiguration(Request<_trt__GetVideoEncoderConfiguration> &rRequest);
	Response<_trt__GetAudioSourceConfigurationResponse> GetAudioSourceConfiguration(Request<_trt__GetAudioSourceConfiguration> &rRequest);
	Response<_trt__GetAudioEncoderConfigurationResponse> GetAudioEncoderConfiguration(Request<_trt__GetAudioEncoderConfiguration> &rRequest);
	Response<_trt__GetVideoAnalyticsConfigurationResponse>
	GetVideoAnalyticsConfiguration(Request<_trt__GetVideoAnalyticsConfiguration> &rRequest);
	Response<_trt__GetMetadataConfigurationResponse> GetMetadataConfiguration(Request<_trt__GetMetadataConfiguration> &rRequest);
	Response<_trt__GetAudioOutputConfigurationResponse> GetAudioOutputConfiguration(Request<_trt__GetAudioOutputConfiguration> &rRequest);
	Response<_trt__GetAudioDecoderConfigurationResponse> GetAudioDecoderConfiguration(Request<_trt__GetAudioDecoderConfiguration> &rRequest);
	Response<_trt__GetCompatibleVideoEncoderConfigurationsResponse>
	GetCompatibleVideoEncoderConfigurations(Request<_trt__GetCompatibleVideoEncoderConfigurations> &rRequest);
	Response<_trt__GetCompatibleVideoSourceConfigurationsResponse>
	GetCompatibleVideoSourceConfigurations(Request<_trt__GetCompatibleVideoSourceConfigurations> &rRequest);
	Response<_trt__GetCompatibleAudioEncoderConfigurationsResponse>
	GetCompatibleAudioEncoderConfigurations(Request<_trt__GetCompatibleAudioEncoderConfigurations> &rRequest);
	Response<_trt__GetCompatibleAudioSourceConfigurationsResponse>
	GetCompatibleAudioSourceConfigurations(Request<_trt__GetCompatibleAudioSourceConfigurations> &rRequest);
	Response<_trt__GetCompatibleVideoAnalyticsConfigurationsResponse>
	GetCompatibleVideoAnalyticsConfigurations(Request<_trt__GetCompatibleVideoAnalyticsConfigurations> &rRequest);
	Response<_trt__GetCompatibleMetadataConfigurationsResponse>
	GetCompatibleMetadataConfigurations(Request<_trt__GetCompatibleMetadataConfigurations> &rRequest);
	Response<_trt__GetCompatibleAudioOutputConfigurationsResponse>
	GetCompatibleAudioOutputConfigurations(Request<_trt__GetCompatibleAudioOutputConfigurations> &rRequest);
	Response<_trt__GetCompatibleAudioDecoderConfigurationsResponse>
	GetCompatibleAudioDecoderConfigurations(Request<_trt__GetCompatibleAudioDecoderConfigurations> &rRequest);
	Response<_trt__SetVideoSourceConfigurationResponse> SetVideoSourceConfiguration(Request<_trt__SetVideoSourceConfiguration> &rRequest);
	Response<_trt__SetVideoEncoderConfigurationResponse> SetVideoEncoderConfiguration(Request<_trt__SetVideoEncoderConfiguration> &rRequest);
	Response<_trt__SetAudioSourceConfigurationResponse> SetAudioSourceConfiguration(Request<_trt__SetAudioSourceConfiguration> &rRequest);
	Response<_trt__SetAudioEncoderConfigurationResponse> SetAudioEncoderConfiguration(Request<_trt__SetAudioEncoderConfiguration> &rRequest);
	Response<_trt__SetVideoAnalyticsConfigurationResponse>
	SetVideoAnalyticsConfiguration(Request<_trt__SetVideoAnalyticsConfiguration> &rRequest);
	Response<_trt__SetMetadataConfigurationResponse> SetMetadataConfiguration(Request<_trt__SetMetadataConfiguration> &rRequest);
	Response<_trt__SetAudioOutputConfigurationResponse> SetAudioOutputConfiguration(Request<_trt__SetAudioOutputConfiguration> &rRequest);
	Response<_trt__SetAudioDecoderConfigurationResponse> SetAudioDecoderConfiguration(Request<_trt__SetAudioDecoderConfiguration> &rRequest);
	Response<_trt__GetVideoSourceConfigurationOptionsResponse>
	GetVideoSourceConfigurationOptions(Request<_trt__GetVideoSourceConfigurationOptions> &rRequest);
	Response<_trt__GetVideoEncoderConfigurationOptionsResponse>
	GetVideoEncoderConfigurationOptions(Request<_trt__GetVideoEncoderConfigurationOptions> &rRequest);
	Response<_trt__GetAudioSourceConfigurationOptionsResponse>
	GetAudioSourceConfigurationOptions(Request<_trt__GetAudioSourceConfigurationOptions> &rRequest);
	Response<_trt__GetAudioEncoderConfigurationOptionsResponse>
	GetAudioEncoderConfigurationOptions(Request<_trt__GetAudioEncoderConfigurationOptions> &rRequest);
	Response<_trt__GetMetadataConfigurationOptionsResponse>
	GetMetadataConfigurationOptions(Request<_trt__GetMetadataConfigurationOptions> &rRequest);
	Response<_trt__GetAudioOutputConfigurationOptionsResponse>
	GetAudioOutputConfigurationOptions(Request<_trt__GetAudioOutputConfigurationOptions> &rRequest);
	Response<_trt__GetAudioDecoderConfigurationOptionsResponse>
	GetAudioDecoderConfigurationOptions(Request<_trt__GetAudioDecoderConfigurationOptions> &rRequest);
	Response<_trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse>
	GetGuaranteedNumberOfVideoEncoderInstances(Request<_trt__GetGuaranteedNumberOfVideoEncoderInstances> &rRequest);
	Response<_trt__GetStreamUriResponse> GetStreamUri(Request<_trt__GetStreamUri> &rRequest);
	Response<_trt__StartMulticastStreamingResponse> StartMulticastStreaming(Request<_trt__StartMulticastStreaming> &rRequest);
	Response<_trt__StopMulticastStreamingResponse> StopMulticastStreaming(Request<_trt__StopMulticastStreaming> &rRequest);
	Response<_trt__SetSynchronizationPointResponse> SetSynchronizationPoint(Request<_trt__SetSynchronizationPoint> &rRequest);
	Response<_trt__GetSnapshotUriResponse> GetSnapshotUri(Request<_trt__GetSnapshotUri> &rRequest);
	Response<_trt__GetVideoSourceModesResponse> GetVideoSourceModes(Request<_trt__GetVideoSourceModes> &rRequest);
	Response<_trt__SetVideoSourceModeResponse> SetVideoSourceMode(Request<_trt__SetVideoSourceMode> &rRequest);
	Response<_trt__GetOSDsResponse> GetOSDs(Request<_trt__GetOSDs> &rRequest);
	Response<_trt__GetOSDResponse> GetOSD(Request<_trt__GetOSD> &rRequest);
	Response<_trt__GetOSDOptionsResponse> GetOSDOptions(Request<_trt__GetOSDOptions> &rRequest);
	Response<_trt__SetOSDResponse> SetOSD(Request<_trt__SetOSD> &rRequest);
	Response<_trt__CreateOSDResponse> CreateOSD(Request<_trt__CreateOSD> &rRequest);
	Response<_trt__DeleteOSDResponse> DeleteOSD(Request<_trt__DeleteOSD> &rRequest);

private:
	Q_DISABLE_COPY(OnvifMediaClient);

	OnvifMediaClientPrivate *mpD;
};
