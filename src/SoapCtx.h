#pragma once
#include "soapH.h"
#include "OnvifCommonExport.h"
#include <QMutex>
#include <QSharedPointer>


#define SOAP_NEW_IO_DEFAULT (SOAP_IO_DEFAULT | SOAP_DOM_NODE | SOAP_XML_TREE)
#define SOAP_NEW_SSL_DEFAULT (SOAP_SSL_REQUIRE_SERVER_AUTHENTICATION | SOAP_TLSv1 | SOAP_SSL_CLIENT)
#define SOAP_DEFAULT_CONNECT_TIMEOUT 10000
#define SOAP_DEFAULT_RECEIVE_TIMEOUT 10000
#define SOAP_DEFAULT_SEND_TIMEOUT 10000

class ONVIFCOMMON_EXPORT SoapCtx {

public:
	SoapCtx();
	SoapCtx(soap_mode imode, soap_mode omode);
	virtual ~SoapCtx();
	void SetIMode(soap_mode imode);
	void SetOMode(soap_mode omode);
	void EnableIModeFlags(soap_mode imode);
	void EnableOModeFlags(soap_mode omode);
	void DisableIModeFlags(soap_mode imode);
	void DisableOModeFlags(soap_mode omode);
	void EnablePrintRawSoap();
	void DisablePrintRawSoap();
	QString GetFaultString();
	QString GetFaultDetail();
	bool EnableSsl();
	void SoapDelete(void *p);
	void SoapDealloc(void *p);
	void SoapUnlink(void *p);
	void SoapFreeTemp();
	void SetConnectTimeout(int timeoutMs);
	void SetSendTimeout(int timeoutMs);
	void SetReceiveTimeout(int timeoutMs);
	void SetSocketFlags(int soFlags); // soap::socket_flags
	void SetConnectFlags(int conFlags); // soap::connect_flags
	void SetBindFlags(int bindFlags); // soap::bind_flags
	void SetAcceptFlags(int acceptFlags); // soap::accept_flags
	//! Non blocking.
	void ForceSocketClose();
	void Save();
	void Restore();
	//! If you need the raw soap ctx use Acquire(). You have to call Release() afterwards.
	soap* Acquire();
	soap* TryAcquire(int timeout = 0);
	//! Release the raw soap ctx after Acquire().
	void Release();

	static class Builder {

	public:
		Builder() :
			mpResult(QSharedPointer<SoapCtx>::create()) {}

		Builder& SetConnectTimeout(int timeoutMs) { mpResult->SetConnectTimeout(timeoutMs); return *this; }
		Builder& SetSendTimeout(int timeoutMs) { mpResult->SetSendTimeout(timeoutMs); return *this; }
		Builder& SetReceiveTimeout(int timeoutMs) { mpResult->SetReceiveTimeout(timeoutMs); return *this; }
		Builder& EnableIMode(soap_mode timeoutMs) { mpResult->EnableIModeFlags(timeoutMs); return *this; }
		Builder& EnableOMode(soap_mode timeoutMs) { mpResult->EnableOModeFlags(timeoutMs); return *this; }
		Builder& EnablePrintRawSoap() { mpResult->EnablePrintRawSoap(); return *this; }
#ifdef WITH_OPENSSL
		Builder& EnableSsl() { mpResult->EnableSsl(); return *this; }
#endif // WITH_OPENSSL
		const QSharedPointer<SoapCtx>& Build() const { return mpResult; }

	private:

		QSharedPointer<SoapCtx> mpResult;
	};

private:
	Q_DISABLE_COPY(SoapCtx);
	void InitCtx();

	soap *mpSoap;
	QMutex mMutex;
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
};
