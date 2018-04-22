#include "Client.h"
#include "soapH.h"
#include "UserData.h"
#include "wsseapi-lite.h"
#include "global.h"
#include "httpda.h"
#include <QDebug>
#include <QObject>


#define CheckIfDigestAuthFault(pSoap) (pSoap->error == HTTP_UNAUTHORIZED)
#define CheckIfWsTokenAuthFault(pSoap) (pSoap->error == SOAP_CLI_FAULT && QString::compare(QString::fromLocal8Bit(*soap_faultsubcode(pSoap)), QString("\"http://www.onvif.org/ver10/error\":NotAuthorized)")) != 0)
#define CheckIfAuthFault(pSoap) (CheckIfWsTokenAuthFault(pSoap) || CheckIfDigestAuthFault(pSoap))

struct ClientPrivate {
	ClientPrivate(Client *pQ, const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx) :
		mpQ(pQ),
		mCtx(sharedCtx),
		mEndpoint(rEndpoint),
		mAuthmode(NO_AUTH),
		mUserName(),
		mPassword(),
		mDigest(),
		mDigestStore(),
		mAuthProcessed(false) {

	}

	Client *mpQ;
	QSharedPointer<SoapCtx> mCtx;
	QUrl mEndpoint;
	AuthMode mAuthmode;
	QString mUserName;
	QString mPassword;
	QString mDigest;
	http_da_info mDigestStore;
	bool mAuthProcessed;
};

Client::Client(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx, QObject *pParent) :
QObject(pParent),
mpD(new ClientPrivate(this, rEndpoint, sharedCtx)) {

}

Client::~Client() {

	FreeAuthData();
	delete mpD;
}

soap* Client::ackquireCtx() {

	auto pCtx = mpD->mCtx->Acquire();
	RestoreAuth(pCtx);
	return pCtx;
}

soap* Client::TryAcquireCtx(int timeout /*= 0*/) {

	auto pCtx = mpD->mCtx->TryAcquire(timeout);
	if(pCtx) RestoreAuth(pCtx);
	return pCtx;
}

void Client::releaseCtx(soap *pCtx) {

	if(pCtx) {
		soap_destroy(pCtx);
		soap_end(pCtx);
		mpD->mCtx->Release();
	}
}

bool Client::ProcessAuthFaultAndRetry(soap *pCtx) {

	bool ret = false;
	if(mpD->mAuthProcessed == false && CheckIfAuthFault(pCtx)) {
		if((mpD->mAuthmode == HTTP_DIGEST || mpD->mAuthmode == BOTH || mpD->mAuthmode == AUTO) && pCtx->authrealm) {
			// HTTP digest auth.
			if(mpD->mAuthmode == AUTO) mpD->mAuthmode = HTTP_DIGEST;
			mpD->mDigest = QString::fromLocal8Bit(pCtx->authrealm);
			http_da_save(pCtx, &mpD->mDigestStore, pCtx->authrealm, qPrintable(mpD->mUserName), qPrintable(mpD->mPassword));
		}
		if(mpD->mAuthmode == WS_USERNAME_TOKEN || mpD->mAuthmode == BOTH || mpD->mAuthmode == AUTO) {
			// WS token auth.
			if(mpD->mAuthmode == AUTO) mpD->mAuthmode = WS_USERNAME_TOKEN;
		}
		ret = mpD->mAuthProcessed = true;
	}
	return ret;
}

void Client::RestoreAuth(soap *pCtx) {

	if(mpD->mAuthProcessed == true) {
		if(mpD->mAuthmode == HTTP_DIGEST || mpD->mAuthmode == BOTH) {
			if(mpD->mDigestStore.authrealm) {
				http_da_restore(pCtx, &mpD->mDigestStore);
			}
			else {
				qWarning() << "The authrealm is missing in http_da_restore. Falling back to WS token auth.";
				mpD->mAuthmode = WS_USERNAME_TOKEN;
			}
		}
		if(mpD->mAuthmode == WS_USERNAME_TOKEN || mpD->mAuthmode == BOTH) {
			soap_wsse_delete_Security(pCtx);
			soap_wsse_add_UsernameTokenText(pCtx, nullptr, qPrintable(mpD->mUserName), qPrintable(mpD->mPassword));
			soap_wsse_add_Timestamp(pCtx, nullptr, 0);
		}
	}
}

void Client::DisableAuth() {

	auto pCtx = mpD->mCtx->Acquire();
	mpD->mAuthmode = NO_AUTH;
	mpD->mAuthProcessed = true;
	FreeAuthData();
	mpD->mCtx->Release();
}

void Client::SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode) {

	auto pCtx = mpD->mCtx->Acquire();
	mpD->mAuthProcessed = false;
	mpD->mAuthmode = mode;
	mpD->mUserName = rUserName;
	mpD->mPassword = rPassword;
	FreeAuthData();
	mpD->mCtx->Release();
}

void Client::FreeAuthData() {

	auto pCtx = mpD->mCtx->Acquire();
	if(mpD->mDigestStore.authrealm) {
		http_da_release(pCtx, &mpD->mDigestStore);
	}
	soap_wsse_delete_Security(pCtx);
	mpD->mCtx->Release();
}

QString Client::GetFaultString() {
	return mpD->mCtx->GetFaultString();
}

QString Client::GetFaultDetail() {
	return mpD->mCtx->GetFaultDetail();
}

const QUrl Client::GetEndpoint() {

	mpD->mCtx->Acquire();
	auto ret = mpD->mEndpoint;
	mpD->mCtx->Release();
	return ret;
}

void Client::SetEndpoint(const QUrl &rEndpoint) {

	mpD->mCtx->Acquire();
	mpD->mEndpoint = rEndpoint;
	mpD->mCtx->Release();
}

const QString Client::GetEndpointString() {

	return GetEndpoint().toString();
}

QSharedPointer<SoapCtx> Client::GetCtx() const {

	return mpD->mCtx;
}

int Client::retry(soap *pCtx) {

	return ProcessAuthFaultAndRetry(pCtx);
}
