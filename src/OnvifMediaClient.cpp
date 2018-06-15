#include "OnvifMediaClient.h"
#include "soapMediaBindingProxy.h"


struct OnvifMediaClientPrivate {
	OnvifMediaClientPrivate(OnvifMediaClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		soap_set_namespaces(mProxy.soap, SoapCtx::GetDefaultNamespaces());
		mpQ->GetCtx()->Release();
	}

	OnvifMediaClient *mpQ;
	MediaBindingProxy mProxy;
};

OnvifMediaClient::OnvifMediaClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) : Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifMediaClientPrivate(this)) {
}

OnvifMediaClient::~OnvifMediaClient() {

	delete mpD;
}

Response<_trt__GetServiceCapabilitiesResponse> OnvifMediaClient::GetServiceCapabilities(Request<_trt__GetServiceCapabilities> &rRequest) {

	_trt__GetServiceCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetServiceCapabilitiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetVideoSourcesResponse> OnvifMediaClient::GetVideoSources(Request<_trt__GetVideoSources> &rRequest) {

	_trt__GetVideoSourcesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetVideoSources(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetVideoSourcesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioSourcesResponse> OnvifMediaClient::GetAudioSources(Request<_trt__GetAudioSources> &rRequest) {

	_trt__GetAudioSourcesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioSources(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioSourcesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioOutputsResponse> OnvifMediaClient::GetAudioOutputs(Request<_trt__GetAudioOutputs> &rRequest) {

	_trt__GetAudioOutputsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioOutputs(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioOutputsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__CreateProfileResponse> OnvifMediaClient::CreateProfile(Request<_trt__CreateProfile> &rRequest) {

	_trt__CreateProfileResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.CreateProfile(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__CreateProfileResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetProfileResponse> OnvifMediaClient::GetProfile(Request<_trt__GetProfile> &rRequest) {

	_trt__GetProfileResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetProfile(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetProfileResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetProfilesResponse> OnvifMediaClient::GetProfiles(Request<_trt__GetProfiles> &rRequest) {

	_trt__GetProfilesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetProfiles(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetProfilesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__AddVideoEncoderConfigurationResponse> OnvifMediaClient::AddVideoEncoderConfiguration(Request<_trt__AddVideoEncoderConfiguration> &rRequest) {

	_trt__AddVideoEncoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.AddVideoEncoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__AddVideoEncoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__AddVideoSourceConfigurationResponse> OnvifMediaClient::AddVideoSourceConfiguration(Request<_trt__AddVideoSourceConfiguration> &rRequest) {

	_trt__AddVideoSourceConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.AddVideoSourceConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__AddVideoSourceConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__AddAudioEncoderConfigurationResponse> OnvifMediaClient::AddAudioEncoderConfiguration(Request<_trt__AddAudioEncoderConfiguration> &rRequest) {

	_trt__AddAudioEncoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.AddAudioEncoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__AddAudioEncoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__AddAudioSourceConfigurationResponse> OnvifMediaClient::AddAudioSourceConfiguration(Request<_trt__AddAudioSourceConfiguration> &rRequest) {

	_trt__AddAudioSourceConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.AddAudioSourceConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__AddAudioSourceConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__AddPTZConfigurationResponse> OnvifMediaClient::AddPTZConfiguration(Request<_trt__AddPTZConfiguration> &rRequest) {

	_trt__AddPTZConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.AddPTZConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__AddPTZConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__AddVideoAnalyticsConfigurationResponse> OnvifMediaClient::AddVideoAnalyticsConfiguration(Request<_trt__AddVideoAnalyticsConfiguration> &rRequest) {

	_trt__AddVideoAnalyticsConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.AddVideoAnalyticsConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__AddVideoAnalyticsConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__AddMetadataConfigurationResponse> OnvifMediaClient::AddMetadataConfiguration(Request<_trt__AddMetadataConfiguration> &rRequest) {

	_trt__AddMetadataConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.AddMetadataConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__AddMetadataConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__AddAudioOutputConfigurationResponse> OnvifMediaClient::AddAudioOutputConfiguration(Request<_trt__AddAudioOutputConfiguration> &rRequest) {

	_trt__AddAudioOutputConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.AddAudioOutputConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__AddAudioOutputConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__AddAudioDecoderConfigurationResponse> OnvifMediaClient::AddAudioDecoderConfiguration(Request<_trt__AddAudioDecoderConfiguration> &rRequest) {

	_trt__AddAudioDecoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.AddAudioDecoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__AddAudioDecoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__RemoveVideoEncoderConfigurationResponse> OnvifMediaClient::RemoveVideoEncoderConfiguration(Request<_trt__RemoveVideoEncoderConfiguration> &rRequest) {

	_trt__RemoveVideoEncoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RemoveVideoEncoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__RemoveVideoEncoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__RemoveVideoSourceConfigurationResponse> OnvifMediaClient::RemoveVideoSourceConfiguration(Request<_trt__RemoveVideoSourceConfiguration> &rRequest) {

	_trt__RemoveVideoSourceConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RemoveVideoSourceConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__RemoveVideoSourceConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__RemoveAudioEncoderConfigurationResponse> OnvifMediaClient::RemoveAudioEncoderConfiguration(Request<_trt__RemoveAudioEncoderConfiguration> &rRequest) {

	_trt__RemoveAudioEncoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RemoveAudioEncoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__RemoveAudioEncoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__RemoveAudioSourceConfigurationResponse> OnvifMediaClient::RemoveAudioSourceConfiguration(Request<_trt__RemoveAudioSourceConfiguration> &rRequest) {

	_trt__RemoveAudioSourceConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RemoveAudioSourceConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__RemoveAudioSourceConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__RemovePTZConfigurationResponse> OnvifMediaClient::RemovePTZConfiguration(Request<_trt__RemovePTZConfiguration> &rRequest) {

	_trt__RemovePTZConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RemovePTZConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__RemovePTZConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__RemoveVideoAnalyticsConfigurationResponse> OnvifMediaClient::RemoveVideoAnalyticsConfiguration(Request<_trt__RemoveVideoAnalyticsConfiguration> &rRequest) {

	_trt__RemoveVideoAnalyticsConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RemoveVideoAnalyticsConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__RemoveVideoAnalyticsConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__RemoveMetadataConfigurationResponse> OnvifMediaClient::RemoveMetadataConfiguration(Request<_trt__RemoveMetadataConfiguration> &rRequest) {

	_trt__RemoveMetadataConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RemoveMetadataConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__RemoveMetadataConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__RemoveAudioOutputConfigurationResponse> OnvifMediaClient::RemoveAudioOutputConfiguration(Request<_trt__RemoveAudioOutputConfiguration> &rRequest) {

	_trt__RemoveAudioOutputConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RemoveAudioOutputConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__RemoveAudioOutputConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__RemoveAudioDecoderConfigurationResponse> OnvifMediaClient::RemoveAudioDecoderConfiguration(Request<_trt__RemoveAudioDecoderConfiguration> &rRequest) {

	_trt__RemoveAudioDecoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RemoveAudioDecoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__RemoveAudioDecoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__DeleteProfileResponse> OnvifMediaClient::DeleteProfile(Request<_trt__DeleteProfile> &rRequest) {

	_trt__DeleteProfileResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeleteProfile(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__DeleteProfileResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetVideoSourceConfigurationsResponse> OnvifMediaClient::GetVideoSourceConfigurations(Request<_trt__GetVideoSourceConfigurations> &rRequest) {

	_trt__GetVideoSourceConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetVideoSourceConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetVideoSourceConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetVideoEncoderConfigurationsResponse> OnvifMediaClient::GetVideoEncoderConfigurations(Request<_trt__GetVideoEncoderConfigurations> &rRequest) {

	_trt__GetVideoEncoderConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetVideoEncoderConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetVideoEncoderConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioSourceConfigurationsResponse> OnvifMediaClient::GetAudioSourceConfigurations(Request<_trt__GetAudioSourceConfigurations> &rRequest) {

	_trt__GetAudioSourceConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioSourceConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioSourceConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioEncoderConfigurationsResponse> OnvifMediaClient::GetAudioEncoderConfigurations(Request<_trt__GetAudioEncoderConfigurations> &rRequest) {

	_trt__GetAudioEncoderConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioEncoderConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioEncoderConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetVideoAnalyticsConfigurationsResponse> OnvifMediaClient::GetVideoAnalyticsConfigurations(Request<_trt__GetVideoAnalyticsConfigurations> &rRequest) {

	_trt__GetVideoAnalyticsConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetVideoAnalyticsConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetVideoAnalyticsConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetMetadataConfigurationsResponse> OnvifMediaClient::GetMetadataConfigurations(Request<_trt__GetMetadataConfigurations> &rRequest) {

	_trt__GetMetadataConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetMetadataConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetMetadataConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioOutputConfigurationsResponse> OnvifMediaClient::GetAudioOutputConfigurations(Request<_trt__GetAudioOutputConfigurations> &rRequest) {

	_trt__GetAudioOutputConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioOutputConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioOutputConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioDecoderConfigurationsResponse> OnvifMediaClient::GetAudioDecoderConfigurations(Request<_trt__GetAudioDecoderConfigurations> &rRequest) {

	_trt__GetAudioDecoderConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioDecoderConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioDecoderConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetVideoSourceConfigurationResponse> OnvifMediaClient::GetVideoSourceConfiguration(Request<_trt__GetVideoSourceConfiguration> &rRequest) {

	_trt__GetVideoSourceConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetVideoSourceConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetVideoSourceConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetVideoEncoderConfigurationResponse> OnvifMediaClient::GetVideoEncoderConfiguration(Request<_trt__GetVideoEncoderConfiguration> &rRequest) {

	_trt__GetVideoEncoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetVideoEncoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetVideoEncoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioSourceConfigurationResponse> OnvifMediaClient::GetAudioSourceConfiguration(Request<_trt__GetAudioSourceConfiguration> &rRequest) {

	_trt__GetAudioSourceConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioSourceConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioSourceConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioEncoderConfigurationResponse> OnvifMediaClient::GetAudioEncoderConfiguration(Request<_trt__GetAudioEncoderConfiguration> &rRequest) {

	_trt__GetAudioEncoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioEncoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioEncoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetVideoAnalyticsConfigurationResponse> OnvifMediaClient::GetVideoAnalyticsConfiguration(Request<_trt__GetVideoAnalyticsConfiguration> &rRequest) {

	_trt__GetVideoAnalyticsConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetVideoAnalyticsConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetVideoAnalyticsConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetMetadataConfigurationResponse> OnvifMediaClient::GetMetadataConfiguration(Request<_trt__GetMetadataConfiguration> &rRequest) {

	_trt__GetMetadataConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetMetadataConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetMetadataConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioOutputConfigurationResponse> OnvifMediaClient::GetAudioOutputConfiguration(Request<_trt__GetAudioOutputConfiguration> &rRequest) {

	_trt__GetAudioOutputConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioOutputConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioOutputConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioDecoderConfigurationResponse> OnvifMediaClient::GetAudioDecoderConfiguration(Request<_trt__GetAudioDecoderConfiguration> &rRequest) {

	_trt__GetAudioDecoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioDecoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioDecoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetCompatibleVideoEncoderConfigurationsResponse> OnvifMediaClient::GetCompatibleVideoEncoderConfigurations(Request<_trt__GetCompatibleVideoEncoderConfigurations> &rRequest) {

	_trt__GetCompatibleVideoEncoderConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCompatibleVideoEncoderConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetCompatibleVideoEncoderConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetCompatibleVideoSourceConfigurationsResponse> OnvifMediaClient::GetCompatibleVideoSourceConfigurations(Request<_trt__GetCompatibleVideoSourceConfigurations> &rRequest) {

	_trt__GetCompatibleVideoSourceConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCompatibleVideoSourceConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetCompatibleVideoSourceConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetCompatibleAudioEncoderConfigurationsResponse> OnvifMediaClient::GetCompatibleAudioEncoderConfigurations(Request<_trt__GetCompatibleAudioEncoderConfigurations> &rRequest) {

	_trt__GetCompatibleAudioEncoderConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCompatibleAudioEncoderConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetCompatibleAudioEncoderConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetCompatibleAudioSourceConfigurationsResponse> OnvifMediaClient::GetCompatibleAudioSourceConfigurations(Request<_trt__GetCompatibleAudioSourceConfigurations> &rRequest) {

	_trt__GetCompatibleAudioSourceConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCompatibleAudioSourceConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetCompatibleAudioSourceConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetCompatibleVideoAnalyticsConfigurationsResponse> OnvifMediaClient::GetCompatibleVideoAnalyticsConfigurations(Request<_trt__GetCompatibleVideoAnalyticsConfigurations> &rRequest) {

	_trt__GetCompatibleVideoAnalyticsConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCompatibleVideoAnalyticsConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetCompatibleVideoAnalyticsConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetCompatibleMetadataConfigurationsResponse> OnvifMediaClient::GetCompatibleMetadataConfigurations(Request<_trt__GetCompatibleMetadataConfigurations> &rRequest) {

	_trt__GetCompatibleMetadataConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCompatibleMetadataConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetCompatibleMetadataConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetCompatibleAudioOutputConfigurationsResponse> OnvifMediaClient::GetCompatibleAudioOutputConfigurations(Request<_trt__GetCompatibleAudioOutputConfigurations> &rRequest) {

	_trt__GetCompatibleAudioOutputConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCompatibleAudioOutputConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetCompatibleAudioOutputConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetCompatibleAudioDecoderConfigurationsResponse> OnvifMediaClient::GetCompatibleAudioDecoderConfigurations(Request<_trt__GetCompatibleAudioDecoderConfigurations> &rRequest) {

	_trt__GetCompatibleAudioDecoderConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCompatibleAudioDecoderConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetCompatibleAudioDecoderConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__SetVideoSourceConfigurationResponse> OnvifMediaClient::SetVideoSourceConfiguration(Request<_trt__SetVideoSourceConfiguration> &rRequest) {

	_trt__SetVideoSourceConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetVideoSourceConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__SetVideoSourceConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__SetVideoEncoderConfigurationResponse> OnvifMediaClient::SetVideoEncoderConfiguration(Request<_trt__SetVideoEncoderConfiguration> &rRequest) {

	_trt__SetVideoEncoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetVideoEncoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__SetVideoEncoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__SetAudioSourceConfigurationResponse> OnvifMediaClient::SetAudioSourceConfiguration(Request<_trt__SetAudioSourceConfiguration> &rRequest) {

	_trt__SetAudioSourceConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetAudioSourceConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__SetAudioSourceConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__SetAudioEncoderConfigurationResponse> OnvifMediaClient::SetAudioEncoderConfiguration(Request<_trt__SetAudioEncoderConfiguration> &rRequest) {

	_trt__SetAudioEncoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetAudioEncoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__SetAudioEncoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__SetVideoAnalyticsConfigurationResponse> OnvifMediaClient::SetVideoAnalyticsConfiguration(Request<_trt__SetVideoAnalyticsConfiguration> &rRequest) {

	_trt__SetVideoAnalyticsConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetVideoAnalyticsConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__SetVideoAnalyticsConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__SetMetadataConfigurationResponse> OnvifMediaClient::SetMetadataConfiguration(Request<_trt__SetMetadataConfiguration> &rRequest) {

	_trt__SetMetadataConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetMetadataConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__SetMetadataConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__SetAudioOutputConfigurationResponse> OnvifMediaClient::SetAudioOutputConfiguration(Request<_trt__SetAudioOutputConfiguration> &rRequest) {

	_trt__SetAudioOutputConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetAudioOutputConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__SetAudioOutputConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__SetAudioDecoderConfigurationResponse> OnvifMediaClient::SetAudioDecoderConfiguration(Request<_trt__SetAudioDecoderConfiguration> &rRequest) {

	_trt__SetAudioDecoderConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetAudioDecoderConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__SetAudioDecoderConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetVideoSourceConfigurationOptionsResponse> OnvifMediaClient::GetVideoSourceConfigurationOptions(Request<_trt__GetVideoSourceConfigurationOptions> &rRequest) {

	_trt__GetVideoSourceConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetVideoSourceConfigurationOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetVideoSourceConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetVideoEncoderConfigurationOptionsResponse> OnvifMediaClient::GetVideoEncoderConfigurationOptions(Request<_trt__GetVideoEncoderConfigurationOptions> &rRequest) {

	_trt__GetVideoEncoderConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetVideoEncoderConfigurationOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetVideoEncoderConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioSourceConfigurationOptionsResponse> OnvifMediaClient::GetAudioSourceConfigurationOptions(Request<_trt__GetAudioSourceConfigurationOptions> &rRequest) {

	_trt__GetAudioSourceConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioSourceConfigurationOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioSourceConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioEncoderConfigurationOptionsResponse> OnvifMediaClient::GetAudioEncoderConfigurationOptions(Request<_trt__GetAudioEncoderConfigurationOptions> &rRequest) {

	_trt__GetAudioEncoderConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioEncoderConfigurationOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioEncoderConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetMetadataConfigurationOptionsResponse> OnvifMediaClient::GetMetadataConfigurationOptions(Request<_trt__GetMetadataConfigurationOptions> &rRequest) {

	_trt__GetMetadataConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetMetadataConfigurationOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetMetadataConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioOutputConfigurationOptionsResponse> OnvifMediaClient::GetAudioOutputConfigurationOptions(Request<_trt__GetAudioOutputConfigurationOptions> &rRequest) {

	_trt__GetAudioOutputConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioOutputConfigurationOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioOutputConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetAudioDecoderConfigurationOptionsResponse> OnvifMediaClient::GetAudioDecoderConfigurationOptions(Request<_trt__GetAudioDecoderConfigurationOptions> &rRequest) {

	_trt__GetAudioDecoderConfigurationOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAudioDecoderConfigurationOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetAudioDecoderConfigurationOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse> OnvifMediaClient::GetGuaranteedNumberOfVideoEncoderInstances(Request<_trt__GetGuaranteedNumberOfVideoEncoderInstances> &rRequest) {

	_trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetGuaranteedNumberOfVideoEncoderInstances(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetStreamUriResponse> OnvifMediaClient::GetStreamUri(Request<_trt__GetStreamUri> &rRequest) {

	_trt__GetStreamUriResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetStreamUri(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetStreamUriResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__StartMulticastStreamingResponse> OnvifMediaClient::StartMulticastStreaming(Request<_trt__StartMulticastStreaming> &rRequest) {

	_trt__StartMulticastStreamingResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.StartMulticastStreaming(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__StartMulticastStreamingResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__StopMulticastStreamingResponse> OnvifMediaClient::StopMulticastStreaming(Request<_trt__StopMulticastStreaming> &rRequest) {

	_trt__StopMulticastStreamingResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.StopMulticastStreaming(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__StopMulticastStreamingResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__SetSynchronizationPointResponse> OnvifMediaClient::SetSynchronizationPoint(Request<_trt__SetSynchronizationPoint> &rRequest) {

	_trt__SetSynchronizationPointResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetSynchronizationPoint(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__SetSynchronizationPointResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetSnapshotUriResponse> OnvifMediaClient::GetSnapshotUri(Request<_trt__GetSnapshotUri> &rRequest) {

	_trt__GetSnapshotUriResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetSnapshotUri(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetSnapshotUriResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetVideoSourceModesResponse> OnvifMediaClient::GetVideoSourceModes(Request<_trt__GetVideoSourceModes> &rRequest) {

	_trt__GetVideoSourceModesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetVideoSourceModes(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetVideoSourceModesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__SetVideoSourceModeResponse> OnvifMediaClient::SetVideoSourceMode(Request<_trt__SetVideoSourceMode> &rRequest) {

	_trt__SetVideoSourceModeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetVideoSourceMode(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__SetVideoSourceModeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetOSDsResponse> OnvifMediaClient::GetOSDs(Request<_trt__GetOSDs> &rRequest) {

	_trt__GetOSDsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetOSDs(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetOSDsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetOSDResponse> OnvifMediaClient::GetOSD(Request<_trt__GetOSD> &rRequest) {

	_trt__GetOSDResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetOSD(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetOSDResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__GetOSDOptionsResponse> OnvifMediaClient::GetOSDOptions(Request<_trt__GetOSDOptions> &rRequest) {

	_trt__GetOSDOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetOSDOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__GetOSDOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__SetOSDResponse> OnvifMediaClient::SetOSD(Request<_trt__SetOSD> &rRequest) {

	_trt__SetOSDResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetOSD(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__SetOSDResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__CreateOSDResponse> OnvifMediaClient::CreateOSD(Request<_trt__CreateOSD> &rRequest) {

	_trt__CreateOSDResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.CreateOSD(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__CreateOSDResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trt__DeleteOSDResponse> OnvifMediaClient::DeleteOSD(Request<_trt__DeleteOSD> &rRequest) {

	_trt__DeleteOSDResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeleteOSD(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trt__DeleteOSDResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}
