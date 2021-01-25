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
#include "OnvifMedia2Client.h"
#include "soapMedia2BindingProxy.h"


struct OnvifMedia2ClientPrivate {
	OnvifMedia2ClientPrivate(OnvifMedia2Client *pQ) : mpQ(pQ), mProxy(mpQ->GetCtx()->Acquire()) {
		soap_set_namespaces(mProxy.soap, SoapCtx::GetDefaultNamespaces());
		mpQ->GetCtx()->Release();
	}

	OnvifMedia2Client *mpQ;
	Media2BindingProxy mProxy;
};

OnvifMedia2Client::OnvifMedia2Client(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/,
                                     QObject *pParent /*= nullptr*/) :
 Client(rEndpoint, sharedCtx, pParent), mpD(new OnvifMedia2ClientPrivate(this)) {}

OnvifMedia2Client::~OnvifMedia2Client() {

	delete mpD;
}

Response<_tr2__GetServiceCapabilitiesResponse> OnvifMedia2Client::GetServiceCapabilities(Request<_tr2__GetServiceCapabilities> &rRequest) {

	_tr2__GetServiceCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()),
		                                         !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                         responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetServiceCapabilitiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__CreateProfileResponse> OnvifMedia2Client::CreateProfile(Request<_tr2__CreateProfile> &rRequest) {

	_tr2__CreateProfileResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.CreateProfile(qPrintable(GetEndpointString()),
		                                !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__CreateProfileResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetProfilesResponse> OnvifMedia2Client::GetProfiles(Request<_tr2__GetProfiles> &rRequest) {

	_tr2__GetProfilesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret =
		 mpD->mProxy.GetProfiles(qPrintable(GetEndpointString()),
		                         !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetProfilesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__AddConfigurationResponse> OnvifMedia2Client::AddConfiguration(Request<_tr2__AddConfiguration> &rRequest) {

	_tr2__AddConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.AddConfiguration(qPrintable(GetEndpointString()),
		                                   !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                   responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__AddConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__RemoveConfigurationResponse> OnvifMedia2Client::RemoveConfiguration(Request<_tr2__RemoveConfiguration> &rRequest) {

	_tr2__RemoveConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.RemoveConfiguration(qPrintable(GetEndpointString()),
		                                      !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                      responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__RemoveConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__DeleteProfileResponse> OnvifMedia2Client::DeleteProfile(Request<_tr2__DeleteProfile> &rRequest) {

	_tr2__DeleteProfileResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.DeleteProfile(qPrintable(GetEndpointString()),
		                                !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__DeleteProfileResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetVideoSourceConfigurationsResponse>
OnvifMedia2Client::GetVideoSourceConfigurations(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetVideoSourceConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetVideoSourceConfigurations(qPrintable(GetEndpointString()),
		                                               !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                               &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetVideoSourceConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetVideoEncoderConfigurationsResponse>
OnvifMedia2Client::GetVideoEncoderConfigurations(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetVideoEncoderConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetVideoEncoderConfigurations(qPrintable(GetEndpointString()),
		                                                !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                                &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetVideoEncoderConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetAudioSourceConfigurationsResponse>
OnvifMedia2Client::GetAudioSourceConfigurations(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetAudioSourceConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetAudioSourceConfigurations(qPrintable(GetEndpointString()),
		                                               !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                               &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetAudioSourceConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetAudioEncoderConfigurationsResponse>
OnvifMedia2Client::GetAudioEncoderConfigurations(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetAudioEncoderConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetAudioEncoderConfigurations(qPrintable(GetEndpointString()),
		                                                !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                                &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetAudioEncoderConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetAnalyticsConfigurationsResponse> OnvifMedia2Client::GetAnalyticsConfigurations(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetAnalyticsConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetAnalyticsConfigurations(qPrintable(GetEndpointString()),
		                                             !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                             &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetAnalyticsConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetMetadataConfigurationsResponse> OnvifMedia2Client::GetMetadataConfigurations(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetMetadataConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetMetadataConfigurations(qPrintable(GetEndpointString()),
		                                            !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                            &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetMetadataConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetAudioOutputConfigurationsResponse>
OnvifMedia2Client::GetAudioOutputConfigurations(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetAudioOutputConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetAudioOutputConfigurations(qPrintable(GetEndpointString()),
		                                               !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                               &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetAudioOutputConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetAudioDecoderConfigurationsResponse>
OnvifMedia2Client::GetAudioDecoderConfigurations(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetAudioDecoderConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetAudioDecoderConfigurations(qPrintable(GetEndpointString()),
		                                                !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                                &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetAudioDecoderConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse>
OnvifMedia2Client::SetVideoSourceConfiguration(Request<_tr2__SetVideoSourceConfiguration> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.SetVideoSourceConfiguration(qPrintable(GetEndpointString()),
		                                              !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                              &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse>
OnvifMedia2Client::SetVideoEncoderConfiguration(Request<_tr2__SetVideoEncoderConfiguration> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.SetVideoEncoderConfiguration(qPrintable(GetEndpointString()),
		                                               !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                               &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse>
OnvifMedia2Client::SetAudioSourceConfiguration(Request<_tr2__SetAudioSourceConfiguration> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.SetAudioSourceConfiguration(qPrintable(GetEndpointString()),
		                                              !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                              &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse>
OnvifMedia2Client::SetAudioEncoderConfiguration(Request<_tr2__SetAudioEncoderConfiguration> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.SetAudioEncoderConfiguration(qPrintable(GetEndpointString()),
		                                               !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                               &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse> OnvifMedia2Client::SetMetadataConfiguration(Request<_tr2__SetMetadataConfiguration> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.SetMetadataConfiguration(qPrintable(GetEndpointString()),
		                                           !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                           responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse>
OnvifMedia2Client::SetAudioOutputConfiguration(Request<_tr2__SetAudioOutputConfiguration> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.SetAudioOutputConfiguration(qPrintable(GetEndpointString()),
		                                              !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                              &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse>
OnvifMedia2Client::SetAudioDecoderConfiguration(Request<_tr2__SetAudioDecoderConfiguration> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.SetAudioDecoderConfiguration(qPrintable(GetEndpointString()),
		                                               !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                               &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetVideoSourceConfigurationOptionsResponse>
OnvifMedia2Client::GetVideoSourceConfigurationOptions(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetVideoSourceConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetVideoSourceConfigurationOptions(qPrintable(GetEndpointString()),
		                                                     !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                                     &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetVideoSourceConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetVideoEncoderConfigurationOptionsResponse>
OnvifMedia2Client::GetVideoEncoderConfigurationOptions(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetVideoEncoderConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetVideoEncoderConfigurationOptions(qPrintable(GetEndpointString()),
		                                                      !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                                      &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetVideoEncoderConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetAudioSourceConfigurationOptionsResponse>
OnvifMedia2Client::GetAudioSourceConfigurationOptions(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetAudioSourceConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetAudioSourceConfigurationOptions(qPrintable(GetEndpointString()),
		                                                     !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                                     &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetAudioSourceConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetAudioEncoderConfigurationOptionsResponse>
OnvifMedia2Client::GetAudioEncoderConfigurationOptions(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetAudioEncoderConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetAudioEncoderConfigurationOptions(qPrintable(GetEndpointString()),
		                                                      !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                                      &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetAudioEncoderConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetMetadataConfigurationOptionsResponse>
OnvifMedia2Client::GetMetadataConfigurationOptions(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetMetadataConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetMetadataConfigurationOptions(qPrintable(GetEndpointString()),
		                                                  !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                                  &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetMetadataConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetAudioOutputConfigurationOptionsResponse>
OnvifMedia2Client::GetAudioOutputConfigurationOptions(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetAudioOutputConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetAudioOutputConfigurationOptions(qPrintable(GetEndpointString()),
		                                                     !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                                     &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetAudioOutputConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetAudioDecoderConfigurationOptionsResponse>
OnvifMedia2Client::GetAudioDecoderConfigurationOptions(Request<tr2__GetConfiguration> &rRequest) {

	_tr2__GetAudioDecoderConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetAudioDecoderConfigurationOptions(qPrintable(GetEndpointString()),
		                                                      !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr,
		                                                      &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetAudioDecoderConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetVideoEncoderInstancesResponse>
OnvifMedia2Client::GetVideoEncoderInstances(Request<_tr2__GetVideoEncoderInstances> &rRequest) {

	_tr2__GetVideoEncoderInstancesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetVideoEncoderInstances(qPrintable(GetEndpointString()),
		                                           !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                           responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetVideoEncoderInstancesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetStreamUriResponse> OnvifMedia2Client::GetStreamUri(Request<_tr2__GetStreamUri> &rRequest) {

	_tr2__GetStreamUriResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret =
		 mpD->mProxy.GetStreamUri(qPrintable(GetEndpointString()),
		                          !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetStreamUriResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse> OnvifMedia2Client::StartMulticastStreaming(Request<tr2__StartStopMulticastStreaming> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.StartMulticastStreaming(qPrintable(GetEndpointString()),
		                                          !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                          responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse> OnvifMedia2Client::StopMulticastStreaming(Request<tr2__StartStopMulticastStreaming> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.StopMulticastStreaming(qPrintable(GetEndpointString()),
		                                         !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                         responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__SetSynchronizationPointResponse>
OnvifMedia2Client::SetSynchronizationPoint(Request<_tr2__SetSynchronizationPoint> &rRequest) {

	_tr2__SetSynchronizationPointResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.SetSynchronizationPoint(qPrintable(GetEndpointString()),
		                                          !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                          responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__SetSynchronizationPointResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetSnapshotUriResponse> OnvifMedia2Client::GetSnapshotUri(Request<_tr2__GetSnapshotUri> &rRequest) {

	_tr2__GetSnapshotUriResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetSnapshotUri(qPrintable(GetEndpointString()),
		                                 !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                 responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetSnapshotUriResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetVideoSourceModesResponse> OnvifMedia2Client::GetVideoSourceModes(Request<_tr2__GetVideoSourceModes> &rRequest) {

	_tr2__GetVideoSourceModesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetVideoSourceModes(qPrintable(GetEndpointString()),
		                                      !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                      responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetVideoSourceModesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__SetVideoSourceModeResponse> OnvifMedia2Client::SetVideoSourceMode(Request<_tr2__SetVideoSourceMode> &rRequest) {

	_tr2__SetVideoSourceModeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.SetVideoSourceMode(qPrintable(GetEndpointString()),
		                                     !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                     responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__SetVideoSourceModeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetOSDsResponse> OnvifMedia2Client::GetOSDs(Request<_tr2__GetOSDs> &rRequest) {

	_tr2__GetOSDsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetOSDs(qPrintable(GetEndpointString()),
		                          !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetOSDsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetOSDOptionsResponse> OnvifMedia2Client::GetOSDOptions(Request<_tr2__GetOSDOptions> &rRequest) {

	_tr2__GetOSDOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetOSDOptions(qPrintable(GetEndpointString()),
		                                !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetOSDOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse> OnvifMedia2Client::SetOSD(Request<_tr2__SetOSD> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.SetOSD(qPrintable(GetEndpointString()),
		                         !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__CreateOSDResponse> OnvifMedia2Client::CreateOSD(Request<_tr2__CreateOSD> &rRequest) {

	_tr2__CreateOSDResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret =
		 mpD->mProxy.CreateOSD(qPrintable(GetEndpointString()),
		                       !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__CreateOSDResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse> OnvifMedia2Client::DeleteOSD(Request<_tr2__DeleteOSD> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret =
		 mpD->mProxy.DeleteOSD(qPrintable(GetEndpointString()),
		                       !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetMasksResponse> OnvifMedia2Client::GetMasks(Request<_tr2__GetMasks> &rRequest) {

	_tr2__GetMasksResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret =
		 mpD->mProxy.GetMasks(qPrintable(GetEndpointString()),
		                      !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetMasksResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__GetMaskOptionsResponse> OnvifMedia2Client::GetMaskOptions(Request<_tr2__GetMaskOptions> &rRequest) {

	_tr2__GetMaskOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.GetMaskOptions(qPrintable(GetEndpointString()),
		                                 !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest,
		                                 responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__GetMaskOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse> OnvifMedia2Client::SetMask(Request<_tr2__SetMask> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret = mpD->mProxy.SetMask(qPrintable(GetEndpointString()),
		                          !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<_tr2__CreateMaskResponse> OnvifMedia2Client::CreateMask(Request<_tr2__CreateMask> &rRequest) {

	_tr2__CreateMaskResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret =
		 mpD->mProxy.CreateMask(qPrintable(GetEndpointString()),
		                        !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<_tr2__CreateMaskResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}

Response<tr2__SetConfigurationResponse> OnvifMedia2Client::DeleteMask(Request<_tr2__DeleteMask> &rRequest) {

	tr2__SetConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = AcquireCtx();
	do {
		ret =
		 mpD->mProxy.DeleteMask(qPrintable(GetEndpointString()),
		                        !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(Retry(pSoap));
	auto response = Response<tr2__SetConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	ReleaseCtx(pSoap);
	return response.Build();
}
