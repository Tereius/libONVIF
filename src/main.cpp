#include "OnvifDeviceClient.h"
#include "OnvifEventClient.h"
#include <QRunnable>
#include <QThreadPool>
#include <QDebug>
#include <QTimer>


class Runner : public QRunnable {

public:
	Runner(OnvifDeviceClient &rDevice) : QRunnable(), rmDevice(rDevice) {}

	virtual void run() {
		Request<_tds__GetServices> request;
		rmDevice.GetServices(request);
	}

private:
	OnvifDeviceClient &rmDevice;
};

int main(int _Argc, char ** _Argv) {

	auto builder = SoapCtx::Builder();
	auto ctx = builder
#ifndef NDEBUG
		.EnableOMode(SOAP_XML_INDENT)
#endif
		.Build();

	OnvifDeviceClient onvifDevice(QUrl("http://192.168.0.25:8080/onvif/device_service"), ctx);
	onvifDevice.SetAuth("admin", "admin", AUTO);
	auto pool = QThreadPool::globalInstance();

	OnvifEventClient *onvifEvent = nullptr;

	Request<_tds__GetServices> request;
	request.IncludeCapability = false;
	auto servicesResponse = onvifDevice.GetServices(request);

	QString eventUrl = "";
	if(servicesResponse) {
		for(auto service : servicesResponse.getResultObject()->Service) {
			qDebug() << "namespace:" << service->Namespace.toStdString().c_str() << "Url:" << service->XAddr.toStdString().c_str();
			if(service->Namespace == "http://www.onvif.org/ver10/events/wsdl") {
				onvifEvent = new OnvifEventClient(QUrl(service->XAddr.toStdString().c_str()), ctx);
				onvifEvent->SetAuth("admin", "admin", AUTO);
			}
		}
	}

// 	Request<_tev__GetEventProperties> req;
// 	auto res = onvifEvent->GetEventProperties(req);
// 	if(auto resObj = res.getResultObject()) {
// 		if(auto topicSet = resObj->wstop__TopicSet) {
// 			for(auto it : topicSet->__any) {
// 				if(auto topicAtt = soap_att_get(it, "http://docs.oasis-open.org/wsn/t-1", "topic")) {
// 					for(auto itt = soap_elt_get(it, "http://www.onvif.org/ver10/schema", "MessageDescription"); itt; itt = soap_elt_get_next(itt)) {
// 						auto node = (tt__MessageDescription*)soap_elt_get_node(itt, SOAP_TYPE_tt__MessageDescription);
// 						bool property = node->IsProperty ? node->IsProperty : false;
// 					}
// 				}
// 			}
// 		}
// 	}

	if(onvifEvent) {
		Request<_tev__CreatePullPointSubscription> request;
		request.InitialTerminationTime = new AbsoluteOrRelativeTime(60000);
		auto response = onvifEvent->CreatePullPointSubscription(request);
		if(response && response.GetResultObject()) {
			response.GetResultObject()->Start();
			for(auto i = 0; i < 60; i++) {
				QThread::currentThread()->msleep(10000);
			}
		}
	}
	return 0;
}
