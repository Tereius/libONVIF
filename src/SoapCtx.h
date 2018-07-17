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
#pragma once
#include "soapH.h"
#include "OnvifCommonExport.h"
#include <QMutex>
#include <QSharedPointer>


#define SOAP_NEW_IO_DEFAULT (SOAP_IO_DEFAULT | SOAP_C_UTFSTRING | SOAP_DOM_NODE | SOAP_XML_TREE)
#define SOAP_NEW_SSL_DEFAULT (SOAP_SSL_REQUIRE_SERVER_AUTHENTICATION | SOAP_TLSv1 | SOAP_SSL_CLIENT)
#define SOAP_DEFAULT_CONNECT_TIMEOUT 10000
#define SOAP_DEFAULT_RECEIVE_TIMEOUT 10000
#define SOAP_DEFAULT_SEND_TIMEOUT 10000

struct Namespace;
struct CtxPrivate;

/*!
 *
 * \brief Wrapper class for the raw soap context
 *
 */
class ONVIFCOMMON_EXPORT SoapCtx {

public:

	/*!
	*
	* \brief Construct a soap context with default settings
	*
	*/
	SoapCtx();

	/*!
	*
	* \brief Construct a soap context with custom mode
	*
	*/
	SoapCtx(soap_mode imode, soap_mode omode);
	virtual ~SoapCtx();
	//! Set the imode
	void SetIMode(soap_mode imode);
	//! Set the omode
	void SetOMode(soap_mode omode);
	//! Enable one imode flag
	void EnableIModeFlags(soap_mode imode);
	//! Enable one mode flag
	void EnableModeFlags(soap_mode mode);
	//! Enable one omode flag
	void EnableOModeFlags(soap_mode omode);
	//! Disable one imode flag
	void DisableIModeFlags(soap_mode imode);
	//! Disable one mode flag
	void DisableModeFlags(soap_mode mode);
	//! Disable one omode flag
	void DisableOModeFlags(soap_mode omode);
	//! This context will print the raw soap messages to console and logs (very noisy)
	void EnablePrintRawSoap();
	//! This context will not print the raw soap messages
	void DisablePrintRawSoap();
	//! Get a informative fault message of the last WS call
	QString GetFaultString();
	//! Get a detailed, informative fault message of the last WS call
	QString GetFaultDetail();
	//! Get the gsoap error code of the last WS call (SOAP_OK(0) means no error)
	int GetFaultCode();
	//! Get the soap fault code of the last WS call
	QString GetFaultSubcode();
	//! Enable SSL support
	bool EnableSsl();
	//! Deletes an object from gsoap memory space
	void SoapDelete(void *p);
	//! Deallocates an object from gsoap memory space
	void SoapDealloc(void *p);
	//! Unlinks an object from gsoap memory space
	void SoapUnlink(void *p);
	//! Frees cached data
	void SoapFreeTemp();
	//! Set the connection timeout in ms
	void SetConnectTimeout(int timeoutMs);
	//! Set the send timeout in ms
	void SetSendTimeout(int timeoutMs);
	//! Set the receive timeout in ms
	void SetReceiveTimeout(int timeoutMs);
	//! Set a combination of socket flags
	void SetSocketFlags(int soFlags); // soap::socket_flags
	//! Set a combination of connection flags
	void SetConnectFlags(int conFlags); // soap::connect_flags
	//! Set a combination of bind flags
	void SetBindFlags(int bindFlags); // soap::bind_flags
	//! Set a combination of accept flags
	void SetAcceptFlags(int acceptFlags); // soap::accept_flags
	//! Interrupt the pending WS call. Non blocking
	void ForceSocketClose();
	//! Save the current state of the soap context
	void Save();
	//! Restore the previously saved state of the soap context
	void Restore();
	//! Acquire the raw soap ctx. Release must be called afterwards
	soap* Acquire();
	//! Acquire the raw soap ctx. Release must be called afterwards
	//! (If the timeout is reached before the soap context could be acquired null is returned)
	soap* TryAcquire(int timeoutMs = 0);
	//! Release a previously acquired raw soap context
	void Release();
	//! Get the default namespace map
	static const Namespace* GetDefaultNamespaces();
	//! Get the prefix of namespace from default namespace map
	static QString GetPrefix(const QString &rNamespace);
	//! Get the namespace of prefix from default namespace map
	static QString GetNamespace(const QString &rPrefix);

	/*!
	*
	* \brief Builds a soap context
	*
	*/
	class Builder {

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

	CtxPrivate *mpD;
};
