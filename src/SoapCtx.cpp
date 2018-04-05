#include "SoapCtx.h"
#include "QMutexLocker"
#include "httpda.h"
#include "wsaapi.h"
#include "namespaces.nsmap"
#include <QString>
#include <QDebug>
#include <QPointer>


struct arbData {

	bool enableDebug = false;
	int(*fsend)(struct soap*, const char*, size_t);
	size_t(*frecv)(struct soap*, char*, size_t);
	QPointer<QObject> pObject = nullptr;
};

int fsend(struct soap *soap, const char *s, size_t n) {

	auto ret = ((arbData*)soap->user)->fsend(soap, s, n);
	if(((arbData*)soap->user)->enableDebug) {
		auto out = QString::fromUtf8(s, n).trimmed();
		if(!out.isEmpty()) qDebug().noquote() << out;
	}
	return ret;
}

size_t frecv(struct soap *soap, char *s, size_t n) {

	auto length = ((arbData*)soap->user)->frecv(soap, s, n);
	if(((arbData*)soap->user)->enableDebug) {
		auto out = QString::fromUtf8(s, length).trimmed();
		if(!out.isEmpty()) qDebug().noquote() << out;
	}
	return length;
}

SoapCtx::SoapCtx() :
mpSoap(soap_new()),
mMutex(QMutex::Recursive),
mIsSaved(false) {

	soap_init2(mpSoap, SOAP_NEW_IO_DEFAULT, SOAP_NEW_IO_DEFAULT);
	InitCtx();
}

SoapCtx::SoapCtx(soap_mode imode, soap_mode omode) :
mpSoap(soap_new()),
mMutex(QMutex::Recursive),
mIsSaved(false) {

	soap_init2(mpSoap, imode, omode);
	InitCtx();
}

SoapCtx::~SoapCtx() {

	delete mpSoap->user;
	mpSoap->user = nullptr;
	soap_free(mpSoap);
}


void SoapCtx::SoapDelete(void *p) {

	QMutexLocker locker(&mMutex);
	soap_delete(mpSoap, p);
}

void SoapCtx::SoapDealloc(void *p) {

	QMutexLocker locker(&mMutex);
	soap_dealloc(mpSoap, p);
}

void SoapCtx::SoapUnlink(void *p) {

	QMutexLocker locker(&mMutex);
	soap_unlink(mpSoap, p);
}

void SoapCtx::SoapFreeTemp() {

	QMutexLocker locker(&mMutex);
	soap_free_temp(mpSoap);
}

void SoapCtx::SetIMode(soap_mode imode) {

	QMutexLocker locker(&mMutex);
	soap_imode(mpSoap, imode);
}

void SoapCtx::SetOMode(soap_mode omode) {

	QMutexLocker locker(&mMutex);
	soap_omode(mpSoap, omode);
}

void SoapCtx::EnableIModeFlags(soap_mode imode) {

	QMutexLocker locker(&mMutex);
	soap_set_imode(mpSoap, imode);
}

void SoapCtx::EnableOModeFlags(soap_mode omode) {

	QMutexLocker locker(&mMutex);
	soap_set_omode(mpSoap, omode);
}

void SoapCtx::DisableIModeFlags(soap_mode imode) {

	QMutexLocker locker(&mMutex);
	soap_clr_imode(mpSoap, imode);
}

void SoapCtx::DisableOModeFlags(soap_mode omode) {

	QMutexLocker locker(&mMutex);
	soap_clr_omode(mpSoap, omode);
}

soap* SoapCtx::Acquire() {

	mMutex.lock();
	return mpSoap;
}

void SoapCtx::Release() {

	mMutex.unlock();
}

soap* SoapCtx::TryAcquire(int timeout) {

	bool locked = mMutex.tryLock(timeout);
	if(locked) return mpSoap;
	return nullptr;
}

void SoapCtx::InitCtx() {

	soap_register_plugin(mpSoap, http_da);
	soap_register_plugin(mpSoap, soap_wsa);

	mpSoap->connect_timeout = SOAP_DEFAULT_CONNECT_TIMEOUT * -1000;
	mpSoap->recv_timeout = SOAP_DEFAULT_RECEIVE_TIMEOUT * -1000;
	mpSoap->send_timeout = SOAP_DEFAULT_SEND_TIMEOUT * -1000;
	soap_set_namespaces(mpSoap, namespaces);

	int(*pFsend)(struct soap *, const char *, size_t);
	pFsend = &fsend;
	size_t(*pFrecv)(struct soap *soap, char *s, size_t n);
	pFrecv = &frecv;
	auto ud = new arbData();
	ud->frecv = mpSoap->frecv;
	ud->fsend = mpSoap->fsend;
	mpSoap->user = ud;
	mpSoap->frecv = pFrecv;
	mpSoap->fsend = pFsend;
}

void SoapCtx::SetConnectTimeout(int timeoutMs) {

	QMutexLocker locker(&mMutex);
	mpSoap->connect_timeout = timeoutMs * -1000;
}

void SoapCtx::SetSendTimeout(int timeoutMs) {

	QMutexLocker locker(&mMutex);
	mpSoap->send_timeout = timeoutMs * -1000;
}

void SoapCtx::SetReceiveTimeout(int timeoutMs) {

	QMutexLocker locker(&mMutex);
	mpSoap->recv_timeout = timeoutMs * -1000;
}

void SoapCtx::ForceSocketClose() {

	// Not mutex lock here. This should be non blocking.
	soap_force_closesock(mpSoap);
}

void SoapCtx::Save() {

	QMutexLocker locker(&mMutex);
	mIModeSaved = mpSoap->imode;
	mOModeSaved = mpSoap->omode;
	mConnectTimeoutSaved = mpSoap->connect_timeout;
	mReceiveTimeout = mpSoap->recv_timeout;
	mSendTimeout = mpSoap->send_timeout;
	mSoFlags = mpSoap->socket_flags;
	mConFlags = mpSoap->connect_flags;
	mBindFlags = mpSoap->bind_flags;
	mAcceptFlags = mpSoap->accept_flags;
	mIsSaved = true;
}

void SoapCtx::Restore() {

	QMutexLocker locker(&mMutex);
	if(mIsSaved) {
		soap_set_imode(mpSoap, mIModeSaved);
		soap_set_omode(mpSoap, mOModeSaved);
		mpSoap->connect_timeout = mConnectTimeoutSaved;
		mpSoap->recv_timeout = mReceiveTimeout;
		mpSoap->send_timeout = mSendTimeout;
		mpSoap->socket_flags = mSoFlags;
		mpSoap->connect_flags = mConFlags;
		mpSoap->bind_flags = mBindFlags;
		mpSoap->accept_flags = mAcceptFlags;
		mIsSaved = false;
	}
}

bool SoapCtx::EnableSsl() {

	QMutexLocker locker(&mMutex);
	auto result = soap_ssl_client_context(
		mpSoap,
		SOAP_NEW_SSL_DEFAULT,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr
		);
	if(result != SOAP_OK) {
		qWarning() << GetFaultString();
	}
	return result == SOAP_OK;
}

QString SoapCtx::GetFaultString() {

	QMutexLocker locker(&mMutex);
	auto ret = QString();
	if(mpSoap->error != SOAP_OK) {
		if(!*soap_faultcode(mpSoap)) soap_set_fault(mpSoap);
		ret += QString::fromLocal8Bit(*soap_faultcode(mpSoap));
		if(!*soap_faultstring(mpSoap)) *soap_faultstring(mpSoap) = "";
		auto faultDetail = QString::fromLocal8Bit(*soap_faultstring(mpSoap));
		if(!faultDetail.isEmpty()) {
			ret += QString(": ") + faultDetail;
		}
	}
	return ret;
}

QString SoapCtx::GetFaultDetail() {

	QMutexLocker locker(&mMutex);
	if(mpSoap->error != SOAP_OK) {
		if(*soap_faultdetail(mpSoap)) return QString::fromLocal8Bit(*soap_faultdetail(mpSoap));
	}
	return QString();
}

void SoapCtx::EnablePrintRawSoap() {

	QMutexLocker locker(&mMutex);
	((arbData*)mpSoap->user)->enableDebug = true;
}

void SoapCtx::DisablePrintRawSoap() {

	QMutexLocker locker(&mMutex);
	((arbData*)mpSoap->user)->enableDebug = false;
}

void SoapCtx::SetSocketFlags(int soFlags) {

	QMutexLocker locker(&mMutex);
	mpSoap->socket_flags = soFlags;
}

void SoapCtx::SetConnectFlags(int conFlags) {

	QMutexLocker locker(&mMutex);
	mpSoap->connect_flags = conFlags;
}

void SoapCtx::SetBindFlags(int bindFlags) {

	QMutexLocker locker(&mMutex);
	mpSoap->bind_flags = bindFlags;
}

void SoapCtx::SetAcceptFlags(int acceptFlags) {

	QMutexLocker locker(&mMutex);
	mpSoap->accept_flags = acceptFlags;
}

int SoapCtx::GetFaultCode() {

	QMutexLocker locker(&mMutex);
	return mpSoap->error;
}
