#include "OnvifDevice.h"
#include "OnvifAnalyticsClient.h"
#include "OnvifDeviceClient.h"
#include "OnvifDiscoveryClient.h"
#include "OnvifDisplayClient.h"
#include "OnvifEventClient.h"
#include "OnvifImagingClient.h"
#include "OnvifMediaClient.h"
#include "OnvifEventClient.h"
#include "OnvifImagingClient.h"
#include "OnvifMediaClient.h"
#include "OnvifPtzClient.h"
#include "OnvifReceiverClient.h"
#include "OnvifRecordingClient.h"
#include "OnvifReplayClient.h"
#include "SoapCtx.h"
#include "OnvifDeviceClient.h"
#include "JsonHelper.h"
#include <QUrl>


struct OnvifDevicePrivate {

	OnvifDevicePrivate(OnvifDevice *pQ) : mpQ(pQ) {

	}

	OnvifDevice *mpQ;
	QString mUserName;
	QString mPassword;
	QUrl mAnalyticsEndpoint;
	QUrl mDeviceEndpoint;
	QUrl mDiscoveryEndpoint;
	QUrl mDisplayEndpoint;
	QUrl mEventEndpoint;
	QUrl mImagingEndpoint;
	QUrl mMediaEndpoint;
	QUrl mPtzEndpoint;
	QUrl mReceiverEndpoint;
	QUrl mRecordingEndpoint;
	QUrl mReplayEndpoint;
	OnvifAnalyticsClient *mpOnvifAnalyticsClient;
	OnvifDeviceClient *mpOnvifDeviceClient;
	OnvifDiscoveryClient *mpOnvifDiscoveryClient;
	OnvifDisplayClient *mpOnvifDisplayClient;
	OnvifEventClient *mpOnvifEventClient;
	OnvifImagingClient *mpOnvifImagingClient;
	OnvifMediaClient *mpOnvifMediaClient;
	OnvifPtzClient *mpOnvifPtzClient;
	OnvifReceiverClient *mpOnvifReceiverClient;
	OnvifRecordingClient *mpOnvifRecordingClient;
	OnvifReplayClient *mpOnvifReplayClient;
};

OnvifDevice::OnvifDevice(const QUrl &rDeviceEndpoint, QObject *pParent /*= nullptr*/) :
	QObject(pParent), mpD(new OnvifDevicePrivate(this)) {

	mpD->mDeviceEndpoint = rDeviceEndpoint;
}

OnvifDevice::~OnvifDevice() {

	delete mpD;
}

SimpleResponse OnvifDevice::Initialize() {

	auto builder = SoapCtx::Builder();
	auto ctx = builder
#ifndef NDEBUG
		//.EnableOMode(SOAP_XML_INDENT)
#endif
		.SetConnectTimeout(1000)
		.Build();


	qDebug() << "Using device endpoint: " << mpD->mDeviceEndpoint.toString();
	auto device = mpD->mpOnvifDeviceClient = new OnvifDeviceClient(mpD->mDeviceEndpoint, ctx, this);
	if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
		device->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
	}

	OnvifEventClient *onvifEvent = nullptr;

	Request<_tds__GetServices> request;
	request.IncludeCapability = false;
	auto servicesResponse = device->GetServices(request);
	if(servicesResponse) {
		for(auto service : servicesResponse.getResultObject()->Service) {
			if(service->Namespace == OnvifAnalyticsClient::GetServiceNamespace()) {
				qDebug() << "ONVIF analytics service" << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				mpD->mpOnvifAnalyticsClient = new OnvifAnalyticsClient(QUrl(qPrintable(service->XAddr)), ctx, this);
				if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
					mpD->mpOnvifAnalyticsClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
				}
			}
			if(service->Namespace == OnvifDeviceClient::GetServiceNamespace()) {
				qDebug() << "ONVIF device service" << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				mpD->mpOnvifDeviceClient = new OnvifDeviceClient(QUrl(qPrintable(service->XAddr)), ctx, this);
				if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
					mpD->mpOnvifDeviceClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
				}
				Request<_tds__GetServiceCapabilities> capReq;
				auto capResp = mpD->mpOnvifDeviceClient->GetServiceCapabilities(capReq);
				if(capResp) {

					auto soap = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_NODE);
					auto dom = soap_dom_element(soap, nullptr, "root", (void*)capResp.getResultObject()->Capabilities, capResp.getResultObject()->Capabilities->soap_type());
					auto jsonRes = JsonHelper::Parse(&dom);
					dom.set((void*)capResp.getResultObject()->Capabilities, capResp.getResultObject()->Capabilities->soap_type());
					qDebug() << jsonRes;
					soap_destroy(dom.soap);
					soap_end(dom.soap);
					soap_done(dom.soap);
					free(dom.soap);
				}
			}
			else if(service->Namespace == OnvifDisplayClient::GetServiceNamespace()) {
				qDebug() << "ONVIF display service" << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				mpD->mpOnvifDisplayClient = new OnvifDisplayClient(QUrl(qPrintable(service->XAddr)), ctx, this);
				if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
					mpD->mpOnvifDisplayClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
				}
			}
			else if(service->Namespace == OnvifEventClient::GetServiceNamespace()) {
				qDebug() << "ONVIF event service" << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				mpD->mpOnvifEventClient = new OnvifEventClient(QUrl(qPrintable(service->XAddr)), ctx, this);
				if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
					mpD->mpOnvifEventClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
				}
			}
			else if(service->Namespace == OnvifImagingClient::GetServiceNamespace()) {
				qDebug() << "ONVIF imaging service" << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				mpD->mpOnvifImagingClient = new OnvifImagingClient(QUrl(qPrintable(service->XAddr)), ctx, this);
				if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
					mpD->mpOnvifImagingClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
				}
			}
			else if(service->Namespace == OnvifMediaClient::GetServiceNamespace()) {
				qDebug() << "ONVIF media service" << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				mpD->mpOnvifMediaClient = new OnvifMediaClient(QUrl(qPrintable(service->XAddr)), ctx, this);
				if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
					mpD->mpOnvifMediaClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
				}
			}
			else if(service->Namespace == OnvifPtzClient::GetServiceNamespace()) {
				qDebug() << "ONVIF ptz service" << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				mpD->mpOnvifPtzClient = new OnvifPtzClient(QUrl(qPrintable(service->XAddr)), ctx, this);
				if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
					mpD->mpOnvifPtzClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
				}
			}
			else if(service->Namespace == OnvifReceiverClient::GetServiceNamespace()) {
				qDebug() << "ONVIF receiver service" << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				mpD->mpOnvifReceiverClient = new OnvifReceiverClient(QUrl(qPrintable(service->XAddr)), ctx, this);
				if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
					mpD->mpOnvifReceiverClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
				}
			}
			else if(service->Namespace == OnvifRecordingClient::GetServiceNamespace()) {
				qDebug() << "ONVIF recording service" << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				mpD->mpOnvifRecordingClient = new OnvifRecordingClient(QUrl(qPrintable(service->XAddr)), ctx, this);
				if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
					mpD->mpOnvifRecordingClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
				}
			}
			else if(service->Namespace == OnvifReplayClient::GetServiceNamespace()) {
				qDebug() << "ONVIF replay service" << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				mpD->mpOnvifReplayClient = new OnvifReplayClient(QUrl(qPrintable(service->XAddr)), ctx, this);
				if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
					mpD->mpOnvifReplayClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
				}
			}
			else {
				qDebug() << "Unknown service" << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
			}
		}
	}
	else {
		qWarning() << "Couldn't receive response: " << servicesResponse.GetCompleteFault();
	}

	Request<_tds__GetCapabilities> r;
	auto res = device->GetCapabilities(r);
	if(auto rr = res.getResultObject()) {
		auto capa = res.getResultObject()->Capabilities;
		if(capa->Device) {

		}
	}

	InitializeTopicSet();

	return SimpleResponse();
}

SimpleResponse OnvifDevice::InitializeTopicSet() {

	Request<_tev__GetEventProperties> request;
	auto response = mpD->mpOnvifEventClient->GetParsedEventProperties(request);
	if(response) {
	}
	else {
		qWarning() << "Couldn't get event properties" << response.GetCompleteFault();
	}

	return SimpleResponse();
}

void OnvifDevice::SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode /*= AUTO*/) {

	mpD->mUserName = rUserName;
	mpD->mPassword = rPassword;
}
