#include "OnvifDevice.h"
#include "CmdLineParser.h"
#include "OnvifDiscoveryClient.h"
#include "OnvifDiscover.h"
#include <QCoreApplication>
#include <QRunnable>
#include <QThreadPool>
#include <QDebug>
#include <QTimer>
#include <QDateTime>


int main(int argc, char **argv) {

	QCoreApplication app(argc, argv);
	QCoreApplication::setApplicationName("ONVIFinfo");
	QCoreApplication::setApplicationVersion("1.0.0");
	QCoreApplication::setOrganizationName("");
	QCoreApplication::setOrganizationDomain("com.github.Tereius.libONVIF");

	QCommandLineParser parser;
	CmdLineParser::setup(parser);
	parser.process(app);
	auto response = CmdLineParser::parse(parser);
	if(response) {
		auto options = response.GetResultObject();
			if(options.discover) {
			auto ctxBuilder = SoapCtx::Builder();
			if(options.verbose) ctxBuilder.EnablePrintRawSoap();
			auto discovery = new OnvifDiscoveryClient(QUrl("soap.udp://239.255.255.250:3702"), ctxBuilder.Build(), &app);
			ProbeTypeRequest requestt;
			requestt.Types = "tds:Device";
			auto probeResponseTwo = discovery->Probe(requestt);
			ProbeTypeRequest request;
			request.Types = "tdn:NetworkVideoTransmitter";
			auto probeResponseOne = discovery->Probe(request);
			if(probeResponseOne && probeResponseTwo) {
				qDebug() << "Searching ONVIF devices for" << options.discoverTime / 1000 << "seconds";
				auto foundMatches = 0;
				auto beginTs = QDateTime::currentMSecsSinceEpoch();
				while(QDateTime::currentMSecsSinceEpoch() < beginTs + options.discoverTime) {
					auto matchResp = discovery->ReceiveProbeMatches();
					if(auto matchs = matchResp.getResultObject()) {
						if(matchs->wsdd__ProbeMatches) {
							for(auto i = 0; i < matchs->wsdd__ProbeMatches->__sizeProbeMatch; ++i) {
								wsdd__ProbeMatchesType match = matchs->wsdd__ProbeMatches[i];
								for(auto ii = 0; ii < match.__sizeProbeMatch; ++ii) {
									foundMatches++;
									auto probe = match.ProbeMatch[ii];
									qDebug() << "Found match:";
									qDebug() << "    Type:" << probe.Types;
									qDebug() << "    Endpoint:" << probe.XAddrs;
									if(probe.Scopes) {
										auto scopeList = QString::fromLocal8Bit(probe.Scopes->__item).split(' ');
										auto matchBy = QString::fromLocal8Bit(probe.Scopes->MatchBy);
										if(!matchBy.isEmpty()) {
											qDebug() << "    Match:" << matchBy;
										}
										qDebug() << "    Scope:";
										for(auto scope : scopeList) {
											if(!scope.isEmpty()) qDebug() << "        " << scope;
										}
									}
								}
							}
						}
					}
				}
				qDebug() << "Found" << foundMatches << (foundMatches > 1 ? "matches" : "match");
			}
			else {
				if(!probeResponseOne) qDebug() << probeResponseOne.GetCompleteFault();
				else qDebug() << probeResponseTwo.GetCompleteFault();
			}
		}
		else {
			auto device = new OnvifDevice(response.GetResultObject().endpointUrl, &app);
			device->SetAuth(response.GetResultObject().user, response.GetResultObject().pwd);
			device->Initialize();
		}
	}
	else {
		qCritical() << response.GetCompleteFault();
	}

	/*
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
	*/
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
/*
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
	*/
	return 0;
}
