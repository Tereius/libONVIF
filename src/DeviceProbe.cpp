//
// Created by bjoern on 16.04.22.
//
#include "DeviceProbe.h"
#include <QScopedPointer>
#include "OnvifDeviceClient.h"
#include "OnvifEventClient.h"
#include "OnvifMediaClient.h"
#include "OnvifMedia2Client.h"
#include "OnvifAnalyticsClient.h"
#include "OnvifDisplayClient.h"
#include "OnvifImagingClient.h"
#include "OnvifPtzClient.h"
#include "OnvifReceiverClient.h"
#include "OnvifReplayClient.h"
#include "OnvifRecordingClient.h"
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(pr, "DeviceProbe")

class DeviceProbePrivate {

public:
	explicit DeviceProbePrivate(DeviceProbe *pQ) :
	 mpQ(pQ),
	 mEndpoint(),
	 mError(),
	 mFirmwareVersion(),
	 mHardwareId(),
	 mManufacturer(),
	 mModel(),
	 mSerialNumber(),
	 mDateTimeOffset(0),
	 mEndpointReference(),
	 mServices() {}

	DeviceProbe *mpQ;
	QUrl mEndpoint;
	QString mError;
	QString mFirmwareVersion;
	QString mHardwareId;
	QString mManufacturer;
	QString mModel;
	QString mSerialNumber;
	qint64 mDateTimeOffset;
	QUuid mEndpointReference;
	QList<DeviceProbe::OnvifServicesTye> mServices;
};

DeviceProbe::DeviceProbe() : mpD(new DeviceProbePrivate(this)) {}

DeviceProbe::DeviceProbe(const QUrl &rDeviceEndpoint) : DeviceProbe::DeviceProbe() {

	mpD->mEndpoint = rDeviceEndpoint;
	QScopedPointer<OnvifDeviceClient> mpDeviceClient(new OnvifDeviceClient(rDeviceEndpoint));

	if(mpDeviceClient->GetEndpoint().isValid()) {
		Request<_tds__GetSystemDateAndTime> dateTimeRequest;
		auto timestamp = QDateTime::currentMSecsSinceEpoch();
		auto dateTimeResponse = mpDeviceClient->GetSystemDateAndTime(dateTimeRequest);
		if(dateTimeResponse) {
			if(auto sysDateTime = dateTimeResponse.GetResultObject()->SystemDateAndTime) {
				bool daylightSaving = sysDateTime->DaylightSavings;
				if(sysDateTime->UTCDateTime && sysDateTime->UTCDateTime->Time && sysDateTime->UTCDateTime->Date) {
					auto deviceTime =
					 QTime(sysDateTime->UTCDateTime->Time->Hour, sysDateTime->UTCDateTime->Time->Minute, sysDateTime->UTCDateTime->Time->Second);
					auto deviceDate =
					 QDate(sysDateTime->UTCDateTime->Date->Year, sysDateTime->UTCDateTime->Date->Month, sysDateTime->UTCDateTime->Date->Day);
					auto currentDateTime = QDateTime::currentDateTimeUtc();
					auto rtt = currentDateTime.toMSecsSinceEpoch() - timestamp;
					mpD->mDateTimeOffset = currentDateTime.addMSecs(-std::llround(rtt / 2)).msecsTo(QDateTime(deviceDate, deviceTime, Qt::UTC));
				} else {
					qWarning(pr) << "Couldn't extract device UTC date time";
				}
			} else {
				qWarning(pr) << "Couldn't extract device date time";
			}

			Request<_tds__GetDeviceInformation> deviceInfoRequest;
			auto infoResponse = mpDeviceClient->GetDeviceInformation(deviceInfoRequest);
			if(infoResponse) {
				if(auto info = infoResponse.GetResultObject()) {
					mpD->mModel = info->Model;
					mpD->mManufacturer = info->Manufacturer;
					mpD->mSerialNumber = info->SerialNumber;
				}

				Request<_tds__GetServices> servicesRequest;
				servicesRequest.IncludeCapability = false;
				auto response = mpDeviceClient->GetServices(servicesRequest);
				if(response) {
					auto services = response.GetResultObject();
					for(auto service : services->Service) {
						if(service->Namespace == OnvifDeviceClient::GetServiceNamespace()) {
							// Device Service
							mpD->mServices.push_back(DeviceProbe::ONVIF_DEVICE);
						} else if(service->Namespace == OnvifEventClient::GetServiceNamespace()) {
							// Event Service
							mpD->mServices.push_back(DeviceProbe::ONVIF_EVENT);
						} else if(service->Namespace == OnvifMediaClient::GetServiceNamespace()) {
							// Media Service
							mpD->mServices.push_back(DeviceProbe::ONVIF_MEDIA);
						} else if(service->Namespace == OnvifMedia2Client::GetServiceNamespace()) {
							// Media2 Service
							mpD->mServices.push_back(DeviceProbe::ONVIF_MEDIA2);
						} else if(service->Namespace == OnvifAnalyticsClient::GetServiceNamespace()) {
							// Analytics Service
							mpD->mServices.push_back(DeviceProbe::ONVIF_ANALYTICS);
						} else if(service->Namespace == OnvifDisplayClient::GetServiceNamespace()) {
							// Display Service
							mpD->mServices.push_back(DeviceProbe::ONVIF_DISPLAY);
						} else if(service->Namespace == OnvifImagingClient::GetServiceNamespace()) {
							// Imaging Service
							mpD->mServices.push_back(DeviceProbe::ONVIF_IMAGING);
						} else if(service->Namespace == OnvifPtzClient::GetServiceNamespace()) {
							// Ptz Service
							mpD->mServices.push_back(DeviceProbe::ONVIF_PTZ);
						} else if(service->Namespace == OnvifReceiverClient::GetServiceNamespace()) {
							// Receiver Service
							mpD->mServices.push_back(DeviceProbe::ONVIF_RECEIVER);
						} else if(service->Namespace == OnvifRecordingClient::GetServiceNamespace()) {
							// Recording Service
							mpD->mServices.push_back(DeviceProbe::ONVIF_RECORDING);
						} else if(service->Namespace == OnvifReplayClient::GetServiceNamespace()) {
							// Replay Service
							mpD->mServices.push_back(DeviceProbe::ONVIF_REPLAY);
						} else {
							qInfo(pr) << "Skipping unsupported service:" << service->Namespace;
						}
					}
				} else {
					qWarning(pr) << "Couldn't get device services:" << response;
					mpD->mError = response.GetCompleteFault();
				}
			} else {
				qWarning(pr) << "Couldn't get device info" << infoResponse;
				mpD->mError = infoResponse.GetCompleteFault();
			}
		} else {
			qWarning(pr) << "Couldn't get device date and time:" << dateTimeResponse;
			mpD->mError = dateTimeResponse.GetCompleteFault();
		}
	} else {
		qWarning(pr) << "Couldn't init device - invalid endpoint: " << mpDeviceClient->GetEndpoint();
		mpD->mError = QObject::tr("Invalid Endpoint url: %1").arg(mpDeviceClient->GetEndpoint().toString());
	}
}

DeviceProbe DeviceProbe::create(const QUrl &rDeviceEndpoint) {

	return {rDeviceEndpoint};
}

bool DeviceProbe::IsValid() const {

	return GetDeviceEndpoint().isValid();
}

QUrl DeviceProbe::GetDeviceEndpoint() const {

	return mpD->mEndpoint;
}

QString DeviceProbe::GetError() const {

	return mpD->mError;
}
QString DeviceProbe::GetFirmwareVersion() const {

	return mpD->mFirmwareVersion;
}

QString DeviceProbe::GetHardwareId() const {

	return mpD->mHardwareId;
}

QString DeviceProbe::GetManufacturer() const {

	return mpD->mManufacturer;
}

QString DeviceProbe::GetModel() const {

	return mpD->mModel;
}

QString DeviceProbe::GetSerialNumber() const {

	return mpD->mSerialNumber;
}

qint64 DeviceProbe::GetDateTimeOffset() const {

	return mpD->mDateTimeOffset;
}

QUuid DeviceProbe::GetEndpointReference() const {

	return mpD->mEndpointReference;
}

QList<DeviceProbe::OnvifServicesTye> DeviceProbe::GetServices() const {

	return mpD->mServices;
}
