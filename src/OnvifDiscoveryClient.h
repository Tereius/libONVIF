#pragma once
#include "Request.h"
#include "Response.h"
#include "Client.h"
#include "OnvifDiscoveryExport.h"
#include <QVector>
#include <QUrl>


struct OnvifDiscoveryClientPrivate;

template <class T> struct ResolveTypeDeleter { 

	void operator()(T* p) {
		if(p) soap_del_wsdd__ResolveType(p);
		delete p;
	}
};

template <class T> struct ResolveTypeDeleterReq {

	void operator()(T* p) {
		if(p) soap_del_wsdd__HelloType(p);
		delete p;
	}
};

template <class T> struct ResolveTypeDuplicator {

	T* operator()(const T *p) {
		return soap_dup_wsdd__ResolveType(nullptr, nullptr, p);
	}
};

class ONVIFDISCOVERY_EXPORT OnvifDiscoveryClient : public Client {

	Q_OBJECT

public:
	OnvifDiscoveryClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~OnvifDiscoveryClient();

	Response<wsdd__ResolveType, ResolveTypeDeleter<wsdd__ResolveType>, ResolveTypeDuplicator<wsdd__ResolveType>> Hello(Request<wsdd__HelloType, ResolveTypeDeleterReq<wsdd__HelloType>> &rRequest);
	//Response<wsdd__ResolveType> Bye(Request<wsdd__ByeType> &rRequest);
	//Response<wsdd__ProbeMatchesType> Probe(Request<wsdd__ProbeType> &rRequest);
	virtual void SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode = AUTO) final;
	virtual void DisableAuth() final;

private:
	Q_DISABLE_COPY(OnvifDiscoveryClient);

	OnvifDiscoveryClientPrivate *mpD;
};