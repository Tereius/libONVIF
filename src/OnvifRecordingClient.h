#pragma once
#include "Response.h"
#include "Request.h"
#include "Client.h"
#include "OnvifRecordingExport.h"

struct OnvifRecordingClientPrivate;

class ONVIFRECORDING_EXPORT OnvifRecordingClient : public Client {

	Q_OBJECT

public:
	OnvifRecordingClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~OnvifRecordingClient();

	Response<_trc__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_trc__GetServiceCapabilities> &rRequest);
	Response<_trc__CreateRecordingResponse> CreateRecording(Request<_trc__CreateRecording> &rRequest);
	Response<_trc__DeleteRecordingResponse> DeleteRecording(Request<_trc__DeleteRecording> &rRequest);
	Response<_trc__GetRecordingsResponse> GetRecordings(Request<_trc__GetRecordings> &rRequest);
	Response<_trc__SetRecordingConfigurationResponse> SetRecordingConfiguration(Request<_trc__SetRecordingConfiguration> &rRequest);
	Response<_trc__GetRecordingConfigurationResponse> GetRecordingConfiguration(Request<_trc__GetRecordingConfiguration> &rRequest);
	Response<_trc__GetRecordingOptionsResponse> GetRecordingOptions(Request<_trc__GetRecordingOptions> &rRequest);
	Response<_trc__CreateTrackResponse> CreateTrack(Request<_trc__CreateTrack> &rRequest);
	Response<_trc__DeleteTrackResponse> DeleteTrack(Request<_trc__DeleteTrack> &rRequest);
	Response<_trc__GetTrackConfigurationResponse> GetTrackConfiguration(Request<_trc__GetTrackConfiguration> &rRequest);
	Response<_trc__SetTrackConfigurationResponse> SetTrackConfiguration(Request<_trc__SetTrackConfiguration> &rRequest);
	Response<_trc__CreateRecordingJobResponse> CreateRecordingJob(Request<_trc__CreateRecordingJob> &rRequest);
	Response<_trc__DeleteRecordingJobResponse> DeleteRecordingJob(Request<_trc__DeleteRecordingJob> &rRequest);
	Response<_trc__GetRecordingJobsResponse> GetRecordingJobs(Request<_trc__GetRecordingJobs> &rRequest);
	Response<_trc__SetRecordingJobConfigurationResponse> SetRecordingJobConfiguration(Request<_trc__SetRecordingJobConfiguration> &rRequest);
	Response<_trc__GetRecordingJobConfigurationResponse> GetRecordingJobConfiguration(Request<_trc__GetRecordingJobConfiguration> &rRequest);
	Response<_trc__SetRecordingJobModeResponse> SetRecordingJobMode(Request<_trc__SetRecordingJobMode> &rRequest);
	Response<_trc__GetRecordingJobStateResponse> GetRecordingJobState(Request<_trc__GetRecordingJobState> &rRequest);
	Response<_trc__ExportRecordedDataResponse> ExportRecordedData(Request<_trc__ExportRecordedData> &rRequest);
	Response<_trc__StopExportRecordedDataResponse> StopExportRecordedData(Request<_trc__StopExportRecordedData> &rRequest);
	Response<_trc__GetExportRecordedDataStateResponse> GetExportRecordedDataState(Request<_trc__GetExportRecordedDataState> &rRequest);

private:
	Q_DISABLE_COPY(OnvifRecordingClient);

	OnvifRecordingClientPrivate *mpD;
};
