#pragma once
#include "SoapCtx.h"
#include "OnvifCommonExport.h"
#include <QObject>
#include <QUrl>
#include <QSharedPointer>


struct soap;
struct ClientPrivate;

enum AuthMode {
	NO_AUTH, HTTP_DIGEST, WS_USERNAME_TOKEN, BOTH, AUTO
};

class ONVIFCOMMON_EXPORT Client : public QObject {

	Q_OBJECT

public:
	Client(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	virtual ~Client();
	// The Soap context this client is working with.
	QSharedPointer<SoapCtx> GetCtx() const;
	// Returns the fault string of the last service call.
	QString GetFaultString();
	// Returns the fault detail string of the last service call.
	QString GetFaultDetail();
	const QUrl& GetEndpoint() const;
	const QString GetEndpointString() const;
	//! Releases old auth data and sets the new one.
	void SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode = AUTO);
	void DisableAuth();

protected:
	soap* ackquireCtx();
	soap* TryAcquireCtx(int timeout = 0);
	void releaseCtx(soap *pCtx);
	int retry(soap *pCtx);

private:
	//! Should be called every time before a service method is invoked.
	void RestoreAuth(soap *pCtx);
	//! Checks if there is an auth fault and processes it. Returns true if the caller should call the service method again, false otherwise.
	bool ProcessAuthFaultAndRetry(soap *pCtx);

private:
	Q_DISABLE_COPY(Client);
	void FreeAuthData();

	ClientPrivate *mpD;
};
