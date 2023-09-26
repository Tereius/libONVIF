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
#include "OnvifDevice.h"
#include "OnvifAnalyticsClient.h"
#include "OnvifDeviceClient.h"
#include "OnvifDiscoveryClient.h"
#include "OnvifDisplayClient.h"
#include "OnvifEventClient.h"
#include "OnvifImagingClient.h"
#include "OnvifMedia2Client.h"
#include "OnvifMediaClient.h"
#include "OnvifPtzClient.h"
#include "OnvifPullPoint.h"
#include "OnvifReceiverClient.h"
#include "OnvifRecordingClient.h"
#include "OnvifReplayClient.h"
#include "SoapCtx.h"
#include <QUrl>


struct OnvifDevicePrivate {

	explicit OnvifDevicePrivate(OnvifDevice *pQ) :
	 mpQ(pQ),
	 mUserName(),
	 mPassword(),
	 mAnalyticsEndpoint(),
	 mDeviceEndpoint(),
	 mDiscoveryEndpoint(),
	 mDisplayEndpoint(),
	 mEventEndpoint(),
	 mImagingEndpoint(),
	 mMediaEndpoint(),
	 mPtzEndpoint(),
	 mReceiverEndpoint(),
	 mRecordingEndpoint(),
	 mReplayEndpoint(),
	 mpOnvifAnalyticsClient(nullptr),
	 mpOnvifDeviceClient(nullptr),
	 mpOnvifDiscoveryClient(nullptr),
	 mpOnvifDisplayClient(nullptr),
	 mpOnvifEventClient(nullptr),
	 mpOnvifImagingClient(nullptr),
	 mpOnvifMediaClient(nullptr),
	 mpOnvifMedia2Client(nullptr),
	 mpOnvifPtzClient(nullptr),
	 mpOnvifReceiverClient(nullptr),
	 mpOnvifRecordingClient(nullptr),
	 mpOnvifReplayClient(nullptr),
	 mpOnvifPullPoint(nullptr) {}

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
	QUrl mMedia2Endpoint;
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
	OnvifMedia2Client *mpOnvifMedia2Client;
	OnvifPtzClient *mpOnvifPtzClient;
	OnvifReceiverClient *mpOnvifReceiverClient;
	OnvifRecordingClient *mpOnvifRecordingClient;
	OnvifReplayClient *mpOnvifReplayClient;
	OnvifPullPoint *mpOnvifPullPoint;
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
	            .Build();
	if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
		ctx->SetAuth(mpD->mUserName, mpD->mPassword);
	}

	qDebug() << "Using device endpoint: " << mpD->mDeviceEndpoint.toString();
	auto device = mpD->mpOnvifDeviceClient = new OnvifDeviceClient(mpD->mDeviceEndpoint, ctx, this);

	OnvifEventClient *onvifEvent = nullptr;

	Request<_tds__GetServices> request;
	request.IncludeCapability = false;
	auto servicesResponse = device->GetServices(request);
	if(servicesResponse) {
		for(auto service : servicesResponse.GetResultObject()->Service) {
			if(service->Namespace == OnvifAnalyticsClient::GetServiceNamespace()) {
				qDebug() << "ONVIF analytics service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				auto url = QUrl(qPrintable(service->XAddr));
				url.setPort(mpD->mDeviceEndpoint.port());
				mpD->mpOnvifAnalyticsClient = new OnvifAnalyticsClient(url, ctx, this);
			}
			if(service->Namespace == OnvifDeviceClient::GetServiceNamespace()) {
				qDebug() << "ONVIF device service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				auto url = QUrl(qPrintable(service->XAddr));
				url.setPort(mpD->mDeviceEndpoint.port());
				mpD->mpOnvifDeviceClient = new OnvifDeviceClient(url, ctx, this);
			} else if(service->Namespace == OnvifDisplayClient::GetServiceNamespace()) {
				qDebug() << "ONVIF display service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				auto url = QUrl(qPrintable(service->XAddr));
				url.setPort(mpD->mDeviceEndpoint.port());
				mpD->mpOnvifDisplayClient = new OnvifDisplayClient(url, ctx, this);
			} else if(service->Namespace == OnvifEventClient::GetServiceNamespace()) {
				qDebug() << "ONVIF event service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				auto url = QUrl(qPrintable(service->XAddr));
				url.setPort(mpD->mDeviceEndpoint.port());
				mpD->mpOnvifEventClient = new OnvifEventClient(url, ctx, this);
			} else if(service->Namespace == OnvifImagingClient::GetServiceNamespace()) {
				qDebug() << "ONVIF imaging service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				auto url = QUrl(qPrintable(service->XAddr));
				url.setPort(mpD->mDeviceEndpoint.port());
				mpD->mpOnvifImagingClient = new OnvifImagingClient(url, ctx, this);
			} else if(service->Namespace == OnvifMediaClient::GetServiceNamespace()) {
				qDebug() << "ONVIF media service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				auto url = QUrl(qPrintable(service->XAddr));
				url.setPort(mpD->mDeviceEndpoint.port());
				mpD->mpOnvifMediaClient = new OnvifMediaClient(url, ctx, this);
			} else if(service->Namespace == OnvifMedia2Client::GetServiceNamespace()) {
				qDebug() << "ONVIF media2 service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				auto url = QUrl(qPrintable(service->XAddr));
				url.setPort(mpD->mDeviceEndpoint.port());
				mpD->mpOnvifMedia2Client = new OnvifMedia2Client(url, ctx, this);
			} else if(service->Namespace == OnvifPtzClient::GetServiceNamespace()) {
				qDebug() << "ONVIF ptz service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				auto url = QUrl(qPrintable(service->XAddr));
				url.setPort(mpD->mDeviceEndpoint.port());
				mpD->mpOnvifPtzClient = new OnvifPtzClient(url, ctx, this);
			} else if(service->Namespace == OnvifReceiverClient::GetServiceNamespace()) {
				qDebug() << "ONVIF receiver service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				auto url = QUrl(qPrintable(service->XAddr));
				url.setPort(mpD->mDeviceEndpoint.port());
				mpD->mpOnvifReceiverClient = new OnvifReceiverClient(url, ctx, this);
			} else if(service->Namespace == OnvifRecordingClient::GetServiceNamespace()) {
				qDebug() << "ONVIF recording service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				auto url = QUrl(qPrintable(service->XAddr));
				url.setPort(mpD->mDeviceEndpoint.port());
				mpD->mpOnvifRecordingClient = new OnvifRecordingClient(url, ctx, this);
			} else if(service->Namespace == OnvifReplayClient::GetServiceNamespace()) {
				qDebug() << "ONVIF replay service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
				auto url = QUrl(qPrintable(service->XAddr));
				url.setPort(mpD->mDeviceEndpoint.port());
				mpD->mpOnvifReplayClient = new OnvifReplayClient(url, ctx, this);
			} else {
				qDebug() << "Unknown service"
				         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
			}
		}
	} else {
		qWarning() << "Couldn't receive response: " << servicesResponse.GetCompleteFault();
	}

	/*
	Request<_tds__GetCapabilities> r;
	auto res = device->GetCapabilities(r);
	if(auto rr = res.GetResultObject()) {
	 auto capa = res.GetResultObject()->Capabilities;
	 if(capa->Device) {
	  //	TODO: Print
	 }
	}*/

	InitializeTopicSet();

	Request<_tds__GetEndpointReference> endpointRefRequest;
	auto endpointRefResponse = mpD->mpOnvifDeviceClient->GetEndpointReference(endpointRefRequest);
	if(endpointRefResponse) {
		if(auto endpointRef = endpointRefResponse.GetResultObject()) {

		} else {
			qWarning() << "Couldn't extract the device endpoint reference";
		}
	} else {
		qWarning() << endpointRefResponse;
	}

	return SimpleResponse();
}

SimpleResponse OnvifDevice::InitializeTopicSet() {

	if(mpD->mpOnvifEventClient) {
		Request<_tev__GetEventProperties> request;
		auto response = mpD->mpOnvifEventClient->GetParsedEventProperties(request);
		if(response) {
			for(auto topic : response.GetResultObject().GetTopics()) {
				auto topicPath = topic.GetTopicPath().join("/");
				if(topicPath.isEmpty()) topicPath.append("/");
				qDebug() << "\nTopic name" << topic.GetName();
				qDebug() << "Topic path" << topicPath;
				for(auto item : topic.GetItems()) {
					if(item.GetPrimitiveType() == SimpleItemInfo::PRIMITIVE_UNKNOWN) {
						qDebug() << "    Unknown Item" << item.GetName() << "type" << item.GetSoapTypeQname();
					} else {
						QString primitive;
						switch(item.GetPrimitiveType()) {
							case SimpleItemInfo::PRIMITIVE_BOOL:
								primitive = "boolean";
								break;
							case SimpleItemInfo::PRIMITIVE_INTEGER:
								primitive = "integer";
								break;
							case SimpleItemInfo::PRIMITIVE_REAL:
								primitive = "real";
								break;
							case SimpleItemInfo::PRIMITIVE_STRING:
								primitive = "string";
								break;
							default:
								primitive = "unknown";
								break;
						}
						qDebug() << "    Item" << item.GetName() << "type" << item.GetSoapTypeQname() << "primitive" << primitive;
					}
				}
			}
		} else {
			qWarning() << "Couldn't get event properties" << response.GetCompleteFault();
		}
	}
	return SimpleResponse();
}

void OnvifDevice::SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode /*= AUTO*/) {

	mpD->mUserName = rUserName;
	mpD->mPassword = rPassword;
}

void OnvifDevice::SubscribePullPoint() {

	if(mpD->mpOnvifEventClient) {
		auto ctx = QSharedPointer<SoapCtx>::create();
		if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
			ctx->SetAuth(mpD->mUserName, mpD->mPassword);
		}
		mpD->mpOnvifPullPoint = new OnvifPullPoint(mpD->mpOnvifEventClient->GetEndpoint(), ctx, this);
		connect(mpD->mpOnvifPullPoint, &OnvifPullPoint::LostPullPoint, this, &OnvifDevice::LostPullPoint);
		connect(mpD->mpOnvifPullPoint, &OnvifPullPoint::UnsuccessfulPull, this, &OnvifDevice::UnsuccessfulPull);
		connect(mpD->mpOnvifPullPoint, &OnvifPullPoint::MessageReceived, this, &OnvifDevice::MessageReceived);
		connect(mpD->mpOnvifPullPoint, &OnvifPullPoint::ResumedPullPoint, this, &OnvifDevice::ResumedPullPoint);
		mpD->mpOnvifPullPoint->Start();
	} else {
		qWarning() << "Missing ONVIF event service - could not start pullpoint";
	}
}

void OnvifDevice::UnsuccessfulPull(int unsuccessfulPullcount, const SimpleResponse &rCause) {

	qWarning() << "Unsuccessful pull" << rCause;
}

void OnvifDevice::MessageReceived(const Response<wsnt__NotificationMessageHolderType> &rResponse) {

	if(auto result = rResponse.GetResultObject()) {
		qDebug() << "";
		qDebug() << "pullpoint message";
		if(result->Topic) {
			qDebug() << "    Topic Dialect" << result->Topic->Dialect;
		}
		if(result->Message.Message) {
			qDebug() << "        Source";
			OnvifDevice::PrintItemList(result->Message.Message->Source);
			qDebug() << "        Key";
			OnvifDevice::PrintItemList(result->Message.Message->Key);
			qDebug() << "        Data";
			OnvifDevice::PrintItemList(result->Message.Message->Data);
		}
	}
}

void OnvifDevice::LostPullPoint(const SimpleResponse &rCause) {

	qWarning() << "Lost pullpoint pull" << rCause;
}

void OnvifDevice::ResumedPullPoint() {

	qWarning() << "Resumed pullpoint";
}

void OnvifDevice::PrintItemList(tt__ItemList *list) {

	if(list) {
		for(const auto &entry : list->SimpleItem) {
			qDebug() << "            Name" << entry.Name << "Value" << entry.Value;
		}
		for(const auto &entry : list->ElementItem) {
			qDebug() << "            Name" << entry.Name;
		}
	}
}
