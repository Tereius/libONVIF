/* Copyright(C) 2018 Björn Stresing
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
#include "SoapCtx.h"
#ifdef WITH_OPENSSL
#include "httpda.h"
#endif // WITH_OPENSSL
#include "namespaces.nsmap"
#include "wsaapi.h"
#include "info.h"
#include <QDebug>
#include <QLatin1String>
#include <QSysInfo>
#include <QPointer>
#include <QString>
#include <QMutexLocker>
#if(QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
#define HAS_QT_RECURSIVEMUTEX
#include <QRecursiveMutex>
#else
#include <QMutex>
#endif


struct arbData {

	bool enableDebug = false;
	QString userAgent = QString("%1/%2.%3.%4 (%5; %6)")
	                     .arg(INFO_PROJECTNAME)
	                     .arg(INFO_VERSION_MAJOR)
	                     .arg(INFO_VERSION_MINOR)
	                     .arg(INFO_VERSION_PATCH)
	                     .arg(QSysInfo::prettyProductName())
	                     .arg(QSysInfo::currentCpuArchitecture());
	int (*fsend)(struct soap *, const char *, size_t) = nullptr;
	size_t (*frecv)(struct soap *, char *, size_t) = nullptr;
	int (*fposthdr)(struct soap *soap, const char *key, const char *val) = nullptr;
	QPointer<QObject> pObject = nullptr;
};

int fsend(struct soap *soap, const char *s, size_t n) {

	auto ret = ((arbData *)soap->user)->fsend(soap, s, n);
	if(((arbData *)soap->user)->enableDebug) {
		auto out = QString::fromUtf8(s, n).trimmed();
		if(!out.isEmpty()) qDebug() << qUtf8Printable(out);
	}
	return ret;
}

int fposthdr(struct soap *soap, const char *key, const char *val) {

	auto latinKey = QLatin1String(key);
	const auto latinUserAgent = QLatin1String("User-Agent");
	if(latinKey.size() == latinUserAgent.size() && QLatin1String(key).startsWith(QLatin1String("User-Agent"), Qt::CaseInsensitive)) {
		return ((arbData *)soap->user)->fposthdr(soap, key, qPrintable(((arbData *)soap->user)->userAgent));
	}
	return ((arbData *)soap->user)->fposthdr(soap, key, val);
}

size_t frecv(struct soap *soap, char *s, size_t n) {

	auto length = ((arbData *)soap->user)->frecv(soap, s, n);
	if(((arbData *)soap->user)->enableDebug) {
		auto out = QString::fromUtf8(s, length).trimmed();
		if(!out.isEmpty()) qDebug() << qUtf8Printable(out);
	}
	return length;
}

struct CtxPrivate {
	explicit CtxPrivate(SoapCtx *pQ) :
	 mpQ(pQ),
	 mpSoap(nullptr),
#if defined(HAS_QT_RECURSIVEMUTEX)
	 mMutex(),
#else
	 mMutex(QMutex::Recursive),
#endif
	 mIsSaved(false),
	 mIModeSaved(),
	 mOModeSaved(),
	 mConnectTimeoutSaved(),
	 mSendTimeout(),
	 mReceiveTimeout(),
	 mSoFlags(),
	 mConFlags(),
	 mBindFlags(),
	 mAcceptFlags(),
	 mRetryCounter(0),
	 mAuthHandler(nullptr) {
	}

	SoapCtx *mpQ;
	soap *mpSoap;
#if defined(HAS_QT_RECURSIVEMUTEX)
	QRecursiveMutex mMutex;
#else
	QMutex mMutex;
#endif
	bool mIsSaved;
	soap_mode mIModeSaved;
	soap_mode mOModeSaved;
	int mConnectTimeoutSaved;
	int mSendTimeout;
	int mReceiveTimeout;
	int mSoFlags;
	int mConFlags;
	int mBindFlags;
	int mAcceptFlags;
	int mRetryCounter;
	std::unique_ptr<SoapAuthHandler> mAuthHandler;
};

SoapCtx::SoapCtx() : mpD(new CtxPrivate(this)) {

	mpD->mpSoap = soap_new();
	soap_init2(mpD->mpSoap, SOAP_NEW_I_DEFAULT, SOAP_NEW_O_DEFAULT);
	InitCtx();
}

SoapCtx::SoapCtx(soap_mode imode, soap_mode omode) : mpD(new CtxPrivate(this)) {

	mpD->mpSoap = soap_new();
	soap_init2(mpD->mpSoap, imode, omode);
	InitCtx();
}

SoapCtx::~SoapCtx() {

	if(mpD->mAuthHandler) {
		mpD->mAuthHandler->FreeAuth(mpD->mpSoap);
		mpD->mAuthHandler.reset(nullptr);
	}
	delete(arbData *)mpD->mpSoap->user;
	mpD->mpSoap->user = nullptr;
	soap_free(mpD->mpSoap);
	delete mpD;
}


const Namespace *SoapCtx::GetDefaultNamespaces() {

	return namespaces;
}

QString SoapCtx::GetPrefix(const QString &rNamespace) {

	const struct Namespace *p;
	for(p = GetDefaultNamespaces(); p && p->id; p++) {
		if(QString::fromLocal8Bit(p->ns) == rNamespace) {
			return QString::fromLocal8Bit(p->id);
		}
	}
	return QString();
}

QString SoapCtx::GetNamespace(const QString &rPrefix) {

	const struct Namespace *p;
	for(p = GetDefaultNamespaces(); p && p->id; p++) {
		if(QString::fromLocal8Bit(p->id) == rPrefix) {
			return QString::fromLocal8Bit(p->ns);
		}
	}
	return QString();
}

void SoapCtx::SoapDelete(void *p) {

	QMutexLocker locker(&mpD->mMutex);
	soap_delete(mpD->mpSoap, p);
}

void SoapCtx::SoapDealloc(void *p) {

	QMutexLocker locker(&mpD->mMutex);
	soap_dealloc(mpD->mpSoap, p);
}

void SoapCtx::SoapUnlink(void *p) {

	QMutexLocker locker(&mpD->mMutex);
	soap_unlink(mpD->mpSoap, p);
}

void SoapCtx::SoapFreeTemp() {

	QMutexLocker locker(&mpD->mMutex);
	soap_free_temp(mpD->mpSoap);
}

void SoapCtx::SetIMode(soap_mode imode) {

	QMutexLocker locker(&mpD->mMutex);
	soap_imode(mpD->mpSoap, imode);
}

void SoapCtx::SetOMode(soap_mode omode) {

	QMutexLocker locker(&mpD->mMutex);
	soap_omode(mpD->mpSoap, omode);
}

void SoapCtx::EnableIModeFlags(soap_mode imode) {

	QMutexLocker locker(&mpD->mMutex);
	soap_set_imode(mpD->mpSoap, imode);
}

void SoapCtx::EnableModeFlags(soap_mode mode) {

	QMutexLocker locker(&mpD->mMutex);
	soap_set_mode(mpD->mpSoap, mode);
}

void SoapCtx::EnableOModeFlags(soap_mode omode) {

	QMutexLocker locker(&mpD->mMutex);
	soap_set_omode(mpD->mpSoap, omode);
}

void SoapCtx::DisableIModeFlags(soap_mode imode) {

	QMutexLocker locker(&mpD->mMutex);
	soap_clr_imode(mpD->mpSoap, imode);
}

void SoapCtx::DisableModeFlags(soap_mode mode) {

	QMutexLocker locker(&mpD->mMutex);
	soap_clr_mode(mpD->mpSoap, mode);
}

void SoapCtx::DisableOModeFlags(soap_mode omode) {

	QMutexLocker locker(&mpD->mMutex);
	soap_clr_omode(mpD->mpSoap, omode);
}

soap *SoapCtx::Acquire() {

	mpD->mMutex.lock();
	mpD->mRetryCounter = 0;
	return mpD->mpSoap;
}

void SoapCtx::Release() {

	mpD->mRetryCounter = 0;
	mpD->mMutex.unlock();
}

soap *SoapCtx::TryAcquire(int timeoutMs) {

	bool locked = mpD->mMutex.tryLock(timeoutMs);
	if(locked) {
		mpD->mRetryCounter = 0;
		return mpD->mpSoap;
	}
	return nullptr;
}

void SoapCtx::InitCtx() {

	soap_register_plugin(mpD->mpSoap, soap_wsa);
	mpD->mpSoap->connect_retry = 1;
	mpD->mpSoap->connect_timeout = SOAP_DEFAULT_CONNECT_TIMEOUT * -1000;
	mpD->mpSoap->recv_timeout = SOAP_DEFAULT_RECEIVE_TIMEOUT * -1000;
	mpD->mpSoap->send_timeout = SOAP_DEFAULT_SEND_TIMEOUT * -1000;
	soap_set_namespaces(mpD->mpSoap, SoapCtx::GetDefaultNamespaces());

	int (*pFsend)(struct soap *, const char *, size_t);
	pFsend = &fsend;
	size_t (*pFrecv)(struct soap * soap, char *s, size_t n);
	pFrecv = &frecv;
	int (*pFposthdr)(struct soap * soap, const char *s, const char *v);
	pFposthdr = &fposthdr;
	auto ud = new arbData();
	ud->frecv = mpD->mpSoap->frecv;
	ud->fsend = mpD->mpSoap->fsend;
	ud->fposthdr = mpD->mpSoap->fposthdr;
	mpD->mpSoap->user = ud;
	mpD->mpSoap->frecv = pFrecv;
	mpD->mpSoap->fsend = pFsend;
	mpD->mpSoap->fposthdr = pFposthdr;
	SetSoapAuthHandler(std::unique_ptr<SoapAuthHandler>(new DefaultAuthHandler()));
}

void SoapCtx::SetConnectTimeout(int timeoutMs) {

	QMutexLocker locker(&mpD->mMutex);
	mpD->mpSoap->connect_timeout = timeoutMs * -1000;
}

void SoapCtx::SetSendTimeout(int timeoutMs) {

	QMutexLocker locker(&mpD->mMutex);
	mpD->mpSoap->send_timeout = timeoutMs * -1000;
}

void SoapCtx::SetReceiveTimeout(int timeoutMs) {

	QMutexLocker locker(&mpD->mMutex);
	mpD->mpSoap->recv_timeout = timeoutMs * -1000;
}

void SoapCtx::ForceSocketClose() {

	// No mutex lock here. This should be non blocking.
#ifdef WITH_SELF_PIPE
	soap_close_connection(mpD->mpSoap);
#endif
	// TODO: How to interrupt ongoing requests on systems that don't support WITH_SELF_PIPE in a nonblocking way?
}

void SoapCtx::Save() {

	QMutexLocker locker(&mpD->mMutex);
	mpD->mIModeSaved = mpD->mpSoap->imode;
	mpD->mOModeSaved = mpD->mpSoap->omode;
	mpD->mConnectTimeoutSaved = mpD->mpSoap->connect_timeout;
	mpD->mReceiveTimeout = mpD->mpSoap->recv_timeout;
	mpD->mSendTimeout = mpD->mpSoap->send_timeout;
	mpD->mSoFlags = mpD->mpSoap->socket_flags;
	mpD->mConFlags = mpD->mpSoap->connect_flags;
	mpD->mBindFlags = mpD->mpSoap->bind_flags;
	mpD->mAcceptFlags = mpD->mpSoap->accept_flags;
	mpD->mIsSaved = true;
}

void SoapCtx::Restore() {

	QMutexLocker locker(&mpD->mMutex);
	if(mpD->mIsSaved) {
		soap_set_imode(mpD->mpSoap, mpD->mIModeSaved);
		soap_set_omode(mpD->mpSoap, mpD->mOModeSaved);
		mpD->mpSoap->connect_timeout = mpD->mConnectTimeoutSaved;
		mpD->mpSoap->recv_timeout = mpD->mReceiveTimeout;
		mpD->mpSoap->send_timeout = mpD->mSendTimeout;
		mpD->mpSoap->socket_flags = mpD->mSoFlags;
		mpD->mpSoap->connect_flags = mpD->mConFlags;
		mpD->mpSoap->bind_flags = mpD->mBindFlags;
		mpD->mpSoap->accept_flags = mpD->mAcceptFlags;
		mpD->mIsSaved = false;
	}
}

#ifdef WITH_OPENSSL
bool SoapCtx::EnableSsl() {

	QMutexLocker locker(&mpD->mMutex);
	auto result = soap_ssl_client_context(mpD->mpSoap, SOAP_NEW_SSL_DEFAULT, nullptr, nullptr, nullptr, nullptr, nullptr);
	if(result != SOAP_OK) {
		qWarning() << GetFaultString();
	}
	return result == SOAP_OK;
}
#endif // WITH_OPENSSL

QString SoapCtx::GetFaultString() {

	QMutexLocker locker(&mpD->mMutex);
	auto ret = QString();
	if(mpD->mpSoap->error != SOAP_OK) {
		if(!*soap_faultcode(mpD->mpSoap)) soap_set_fault(mpD->mpSoap);
		ret += QString::fromLocal8Bit(*soap_faultcode(mpD->mpSoap));
		if(!*soap_faultstring(mpD->mpSoap)) *soap_faultstring(mpD->mpSoap) = "";
		auto faultDetail = QString::fromLocal8Bit(*soap_faultstring(mpD->mpSoap));
		if(!faultDetail.isEmpty()) {
			ret += QString(": ") + faultDetail;
		}
	}
	return ret;
}

QString SoapCtx::GetFaultDetail() {

	QMutexLocker locker(&mpD->mMutex);
	if(mpD->mpSoap->error != SOAP_OK) {
		if(*soap_faultdetail(mpD->mpSoap)) return QString::fromLocal8Bit(*soap_faultdetail(mpD->mpSoap));
	}
	return QString();
}

void SoapCtx::EnablePrintRawSoap() {

	QMutexLocker locker(&mpD->mMutex);
	((arbData *)mpD->mpSoap->user)->enableDebug = true;
}

void SoapCtx::DisablePrintRawSoap() {

	QMutexLocker locker(&mpD->mMutex);
	((arbData *)mpD->mpSoap->user)->enableDebug = false;
}

void SoapCtx::SetUserAgent(const QString &rUserAgent) {

	QMutexLocker locker(&mpD->mMutex);
	((arbData *)mpD->mpSoap->user)->userAgent = rUserAgent;
}

void SoapCtx::SetSocketFlags(int soFlags) {

	QMutexLocker locker(&mpD->mMutex);
	mpD->mpSoap->socket_flags = soFlags;
}

void SoapCtx::SetConnectFlags(int conFlags) {

	QMutexLocker locker(&mpD->mMutex);
	mpD->mpSoap->connect_flags = conFlags;
}

void SoapCtx::SetBindFlags(int bindFlags) {

	QMutexLocker locker(&mpD->mMutex);
	mpD->mpSoap->bind_flags = bindFlags;
}

void SoapCtx::SetAcceptFlags(int acceptFlags) {

	QMutexLocker locker(&mpD->mMutex);
	mpD->mpSoap->accept_flags = acceptFlags;
}

int SoapCtx::GetFaultCode() {

	QMutexLocker locker(&mpD->mMutex);
	return mpD->mpSoap->error;
}

QString SoapCtx::GetFaultSubcode() {

	QMutexLocker locker(&mpD->mMutex);
	if(mpD->mpSoap->error != SOAP_OK) {
		if(*soap_faultsubcode(mpD->mpSoap)) return QString::fromLocal8Bit(*soap_faultsubcode(mpD->mpSoap));
	}
	return QString();
}

void SoapCtx::SetSoapAuthHandler(std::unique_ptr<SoapAuthHandler> handler) {

	QMutexLocker locker(&mpD->mMutex);
	if(mpD->mAuthHandler) {
		mpD->mAuthHandler->FreeAuth(mpD->mpSoap);
		disconnect(mpD->mAuthHandler.get(), nullptr, this, nullptr);
	}
	mpD->mAuthHandler.swap(handler);
	if(mpD->mAuthHandler) {
		mpD->mAuthHandler->moveToThread(this->thread());
		connect(mpD->mAuthHandler.get(), &SoapAuthHandler::Unauthorized, this, &SoapCtx::Unauthorized, Qt::DirectConnection);
	}
}

void SoapCtx::SetAuth(const QString &rUserName, const QString &rPassword, AuthHandlerMode mode /*= AuthHandlerMode::AUTO*/) {

	QMutexLocker locker(&mpD->mMutex);
	if(mpD->mAuthHandler) {
		mpD->mAuthHandler->FreeAuth(mpD->mpSoap);
		mpD->mAuthHandler->SetAuth(mpD->mpSoap, rUserName, rPassword, mode);
	}
}

void SoapCtx::DisableAuth() {

	QMutexLocker locker(&mpD->mMutex);
	if(mpD->mAuthHandler) mpD->mAuthHandler->FreeAuth(mpD->mpSoap);
}

bool SoapCtx::IsAuthFault() {

	QMutexLocker locker(&mpD->mMutex);
	if(mpD->mAuthHandler) return mpD->mAuthHandler->IsAuthFault(mpD->mpSoap);
	return false;
}

void SoapCtx::RestoreAuthData() {

	QMutexLocker locker(&mpD->mMutex);
	if(mpD->mAuthHandler) mpD->mAuthHandler->RestoreAuthData(mpD->mpSoap);
}

bool SoapCtx::ProcessAuthFaultAndRetry() {

	auto retry = false;
	QMutexLocker locker(&mpD->mMutex);
	if(mpD->mAuthHandler) {
		if(mpD->mAuthHandler->IsAuthFault(mpD->mpSoap)) {
			retry = mpD->mAuthHandler->ProcessAuthFaultAndRetry(mpD->mpSoap, mpD->mRetryCounter++);
		}
		mpD->mAuthHandler->ProcessResponse(mpD->mpSoap);
	}
	return retry;
}
