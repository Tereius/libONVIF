#include "OnvifRecordingClient.h"
#include "soapRecordingBindingProxy.h"


struct OnvifRecordingClientPrivate {

	OnvifRecordingClientPrivate(OnvifRecordingClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		soap_set_namespaces(mProxy.soap, SoapCtx::GetDefaultNamespaces());
		mpQ->GetCtx()->Release();
	}

	OnvifRecordingClient *mpQ;
	RecordingBindingProxy mProxy;
};

OnvifRecordingClient::OnvifRecordingClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) : Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifRecordingClientPrivate(this)) {
}

OnvifRecordingClient::~OnvifRecordingClient() {

	delete mpD;
}

Response<_trc__GetServiceCapabilitiesResponse> OnvifRecordingClient::GetServiceCapabilities(Request<_trc__GetServiceCapabilities> &rRequest) {

	_trc__GetServiceCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__GetServiceCapabilitiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__CreateRecordingResponse> OnvifRecordingClient::CreateRecording(Request<_trc__CreateRecording> &rRequest) {

	_trc__CreateRecordingResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.CreateRecording(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__CreateRecordingResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__DeleteRecordingResponse> OnvifRecordingClient::DeleteRecording(Request<_trc__DeleteRecording> &rRequest) {

	_trc__DeleteRecordingResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeleteRecording(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__DeleteRecordingResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__GetRecordingsResponse> OnvifRecordingClient::GetRecordings(Request<_trc__GetRecordings> &rRequest) {

	_trc__GetRecordingsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetRecordings(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__GetRecordingsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__SetRecordingConfigurationResponse> OnvifRecordingClient::SetRecordingConfiguration(Request<_trc__SetRecordingConfiguration> &rRequest) {

	_trc__SetRecordingConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetRecordingConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__SetRecordingConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__GetRecordingConfigurationResponse> OnvifRecordingClient::GetRecordingConfiguration(Request<_trc__GetRecordingConfiguration> &rRequest) {

	_trc__GetRecordingConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetRecordingConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__GetRecordingConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__GetRecordingOptionsResponse> OnvifRecordingClient::GetRecordingOptions(Request<_trc__GetRecordingOptions> &rRequest) {

	_trc__GetRecordingOptionsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetRecordingOptions(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__GetRecordingOptionsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__CreateTrackResponse> OnvifRecordingClient::CreateTrack(Request<_trc__CreateTrack> &rRequest) {

	_trc__CreateTrackResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.CreateTrack(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__CreateTrackResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__DeleteTrackResponse> OnvifRecordingClient::DeleteTrack(Request<_trc__DeleteTrack> &rRequest) {

	_trc__DeleteTrackResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeleteTrack(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__DeleteTrackResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__GetTrackConfigurationResponse> OnvifRecordingClient::GetTrackConfiguration(Request<_trc__GetTrackConfiguration> &rRequest) {

	_trc__GetTrackConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetTrackConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__GetTrackConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__SetTrackConfigurationResponse> OnvifRecordingClient::SetTrackConfiguration(Request<_trc__SetTrackConfiguration> &rRequest) {

	_trc__SetTrackConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetTrackConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__SetTrackConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__CreateRecordingJobResponse> OnvifRecordingClient::CreateRecordingJob(Request<_trc__CreateRecordingJob> &rRequest) {

	_trc__CreateRecordingJobResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.CreateRecordingJob(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__CreateRecordingJobResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__DeleteRecordingJobResponse> OnvifRecordingClient::DeleteRecordingJob(Request<_trc__DeleteRecordingJob> &rRequest) {

	_trc__DeleteRecordingJobResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeleteRecordingJob(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__DeleteRecordingJobResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__GetRecordingJobsResponse> OnvifRecordingClient::GetRecordingJobs(Request<_trc__GetRecordingJobs> &rRequest) {

	_trc__GetRecordingJobsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetRecordingJobs(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__GetRecordingJobsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__SetRecordingJobConfigurationResponse> OnvifRecordingClient::SetRecordingJobConfiguration(Request<_trc__SetRecordingJobConfiguration> &rRequest) {

	_trc__SetRecordingJobConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetRecordingJobConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__SetRecordingJobConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__GetRecordingJobConfigurationResponse> OnvifRecordingClient::GetRecordingJobConfiguration(Request<_trc__GetRecordingJobConfiguration> &rRequest) {

	_trc__GetRecordingJobConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetRecordingJobConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__GetRecordingJobConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__SetRecordingJobModeResponse> OnvifRecordingClient::SetRecordingJobMode(Request<_trc__SetRecordingJobMode> &rRequest) {

	_trc__SetRecordingJobModeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetRecordingJobMode(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__SetRecordingJobModeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__GetRecordingJobStateResponse> OnvifRecordingClient::GetRecordingJobState(Request<_trc__GetRecordingJobState> &rRequest) {

	_trc__GetRecordingJobStateResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetRecordingJobState(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__GetRecordingJobStateResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__ExportRecordedDataResponse> OnvifRecordingClient::ExportRecordedData(Request<_trc__ExportRecordedData> &rRequest) {

	_trc__ExportRecordedDataResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.ExportRecordedData(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__ExportRecordedDataResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__StopExportRecordedDataResponse> OnvifRecordingClient::StopExportRecordedData(Request<_trc__StopExportRecordedData> &rRequest) {

	_trc__StopExportRecordedDataResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.StopExportRecordedData(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__StopExportRecordedDataResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trc__GetExportRecordedDataStateResponse> OnvifRecordingClient::GetExportRecordedDataState(Request<_trc__GetExportRecordedDataState> &rRequest) {

	_trc__GetExportRecordedDataStateResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetExportRecordedDataState(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trc__GetExportRecordedDataStateResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}
