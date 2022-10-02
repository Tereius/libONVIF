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
#include "SoapCtx.h"
#include "global.h"
#include "soapH.h"
#include <QDebug>
#include <QString>


#define GENERIC_FAULT 600

//! Deleter functor
template<class T>
struct SoapDeleter {

	void operator()(T *p) {
		if(p) p->soap_del();
		delete p;
	}
};

//! Duplicator functor
template<class T>
struct SoapDuplicator {

	T *operator()(const T *p) { return p->soap_dup(); }
};

/*!
 *
 * \brief A response of a WS call
 *
 * Holds an error
 *
 */
class SimpleResponse {

 public:
	/*!
	 *
	 * \brief Construct an errorless response
	 *
	 */
	SimpleResponse() : mErrorCode(SOAP_OK), mFault(), mFaultDetail(), mFaultSubcode(), mIsAuthFault(false) {}

	/*!
	 *
	 * \brief Construct a response
	 *
	 */
	SimpleResponse(int errorCode, const QString &rFault = QString(), const QString &rFaultDetail = QString()) :
	 mErrorCode(errorCode), mFault(rFault), mFaultDetail(rFaultDetail), mFaultSubcode(), mIsAuthFault(false) {}

	virtual ~SimpleResponse() {}

	SimpleResponse(const SimpleResponse &rOther) :
	 mErrorCode(rOther.mErrorCode),
	 mFault(rOther.mFault),
	 mFaultDetail(rOther.mFaultDetail),
	 mFaultSubcode(rOther.mFaultSubcode),
	 mIsAuthFault(rOther.mIsAuthFault) {}

	SimpleResponse &operator=(const SimpleResponse &rOther) {

		if(&rOther == this) {
			return *this;
		}
		this->mErrorCode = rOther.mErrorCode;
		this->mFault = rOther.mFault;
		this->mFaultDetail = rOther.mFaultDetail;
		this->mFaultSubcode = rOther.mFaultSubcode;
		this->mIsAuthFault = rOther.mIsAuthFault;
		return *this;
	}

	//! Get a informative fault message
	QString GetSoapFault() const { return mFault; }
	//! Set a informative fault message
	void SetFault(const QString &rFault) { mFault = rFault; }
	//! Get a detailed, informative fault message
	QString GetSoapFaultDetail() const { return mFaultDetail; }
	//! Set a detailed, informative soap fault message
	void SetFaultDetail(const QString &rFaultDetail) { mFaultDetail = rFaultDetail; }
	//! Get a complete, informative fault message
	QString GetCompleteFault() const {
		auto whatFault = QString("No Fault");
		if(IsFault()) {
			whatFault = "Generic Fault: ";
			if(IsTcpFault())
				whatFault = "TCP Fault: ";
			else if(IsSoapFault())
				whatFault = "SOAP Fault: ";
			else if(IsXmlValidationFault())
				whatFault = "XML Val Fault: ";
			else if(IsSslFault())
				whatFault = "SSL Fault: ";
			else if(IsZlibFault())
				whatFault = "Zlib Fault: ";
			else if(IsHttpFault())
				whatFault = "HTTP Fault: ";
			else
				whatFault = "Generic Fault: ";
			if(IsAuthFault()) whatFault.prepend("(Authentication failed) ");
			whatFault += GetSoapFault();
			whatFault += GetSoapFaultDetail();
		}
		return whatFault;
	}
	//! Get the gsoap error code (SOAP_OK(0) means no error)
	int GetErrorCode() const { return mErrorCode; }
	//! Set the gsoap error code
	void SetErrorCode(int errorCode) { mErrorCode = errorCode; }
	//! Get the soap fault code
	QString GetFaultSubcode() const { return mFaultSubcode; }
	//! Set the soap fault code
	void SetFaultSubcode(const QString &rFaultSubcode) { mFaultSubcode = rFaultSubcode; }
	//! Check if the response holds no error
	virtual bool IsSuccess() const { return !IsFault(); }
	//! Check if the response holds an error
	virtual bool IsFault() const { return mErrorCode != SOAP_OK; }
	//! Check if the origin of the fault (tcp)
	bool IsTcpFault() const { return soap_tcp_error_check(mErrorCode); }
	//! Check if the origin of the fault (soap)
	bool IsSoapFault() const { return soap_soap_error_check(mErrorCode); }
	//! Check if the origin of the fault (xml validation)
	bool IsXmlValidationFault() const { return soap_xml_error_check(mErrorCode); }
	//! Check if the origin of the fault (ssl)
	bool IsSslFault() const { return soap_ssl_error_check(mErrorCode); }
	//! Check if the origin of the fault (compression)
	bool IsZlibFault() const { return soap_zlib_error_check(mErrorCode); }
	//! Check if the origin of the fault (http)
	bool IsHttpFault() const { return soap_http_error_check(mErrorCode); }
	//! Check if the origin of the fault (authentication)
	bool IsAuthFault() const { return mIsAuthFault; }
	//! Safe bool
	explicit operator bool() const { return IsSuccess(); }

	virtual void PopulateFromCtx(const QSharedPointer<SoapCtx> &rSoapCtx) {

		auto errorCode = rSoapCtx->GetFaultCode();
		if(errorCode != SOAP_OK) {
			SetErrorCode(errorCode);
			SetFault(rSoapCtx->GetFaultString());
			SetFaultDetail(rSoapCtx->GetFaultDetail());
			SetFaultSubcode(rSoapCtx->GetFaultSubcode());
			mIsAuthFault = rSoapCtx->IsAuthFault();
		} else {
			SetErrorCode(SOAP_OK);
			mFault.clear();
			mFaultDetail.clear();
			mFaultSubcode.clear();
			mIsAuthFault = false;
		}
	}

 private:
	int mErrorCode;
	QString mFault;
	QString mFaultDetail;
	QString mFaultSubcode;
	bool mIsAuthFault;
};

inline QDebug operator<<(QDebug debug, const SimpleResponse &rResponse) {

	QDebugStateSaver saver(debug);
	debug.nospace() << rResponse.GetCompleteFault();
	return debug;
}

/*!
 *
 * \brief A detailed response of a WS call
 *
 * Holds an error and a soap fault response object or a soap header
 *
 */
class DetailedResponse : public SimpleResponse {

 public:
	/*!
	 *
	 * \brief Construct an errorless response
	 *
	 */
	DetailedResponse() : SimpleResponse(), mpFaultResultObject(nullptr), mpSoapHeader(nullptr) {}

	/*!
	 *
	 * \brief Construct a response
	 *
	 */
	DetailedResponse(int errorCode, const QString &rFault = QString(), const QString &rFaultDetail = QString(),
	                 const SOAP_ENV__Detail *pFaultObject = nullptr) :
	 SimpleResponse(errorCode, rFault, rFaultDetail),
	 mpFaultResultObject(pFaultObject ? soap_dup_SOAP_ENV__Detail(nullptr, nullptr, pFaultObject) : nullptr),
	 mpSoapHeader(nullptr) {}

	virtual ~DetailedResponse() {

		if(mpFaultResultObject) soap_del_SOAP_ENV__Detail(mpFaultResultObject);
		delete mpFaultResultObject;
		if(mpSoapHeader) soap_del_SOAP_ENV__Header(mpSoapHeader);
		delete mpSoapHeader;
	}

	DetailedResponse(const DetailedResponse &rOther) :
	 SimpleResponse(rOther),
	 mpFaultResultObject(rOther.mpFaultResultObject ? soap_dup_SOAP_ENV__Detail(nullptr, nullptr, rOther.mpFaultResultObject) : nullptr),
	 mpSoapHeader(rOther.mpSoapHeader ? soap_dup_SOAP_ENV__Header(nullptr, nullptr, rOther.mpSoapHeader) : nullptr) {}

	DetailedResponse &operator=(const DetailedResponse &rOther) {

		if(&rOther == this) {
			return *this;
		}
		SimpleResponse::operator=(rOther);
		if(mpFaultResultObject) soap_del_SOAP_ENV__Detail(mpFaultResultObject);
		delete mpFaultResultObject;
		this->mpFaultResultObject =
		 rOther.mpFaultResultObject ? soap_dup_SOAP_ENV__Detail(nullptr, nullptr, rOther.mpFaultResultObject) : nullptr;
		if(mpSoapHeader) soap_del_SOAP_ENV__Header(mpSoapHeader);
		delete mpSoapHeader;
		this->mpSoapHeader = rOther.mpSoapHeader ? soap_dup_SOAP_ENV__Header(nullptr, nullptr, rOther.mpSoapHeader) : nullptr;
		return *this;
	}

	//! Get the soap fault response object
	template<typename F>
	F *GetFaultObject() {
		if(mpFaultResultObject && mpFaultResultObject->fault && mpFaultResultObject->__type) {
			return static_cast<F *>(mpFaultResultObject->fault);
		}
		return nullptr;
	}

	//! Set the soap fault response object
	void SetEnvDetail(const SOAP_ENV__Detail *pFaultObject) {

		if(mpFaultResultObject) soap_del_SOAP_ENV__Detail(mpFaultResultObject);
		delete mpFaultResultObject;
		mpFaultResultObject = pFaultObject ? soap_dup_SOAP_ENV__Detail(nullptr, nullptr, pFaultObject) : nullptr;
	}

	//! Get the soap header object
	const SOAP_ENV__Header *const GetSoapHeader() { return mpSoapHeader; }

	//! Set the soap header object
	void SetSoapHeader(const SOAP_ENV__Header *pSoapHeader) {

		if(mpSoapHeader) soap_del_SOAP_ENV__Header(mpSoapHeader);
		delete mpSoapHeader;
		this->mpSoapHeader = pSoapHeader ? soap_dup_SOAP_ENV__Header(nullptr, nullptr, pSoapHeader) : nullptr;
	}

	//! Get the field "message id" from the soap header
	QString GetSoapHeaderMessageId() const {

		if(mpSoapHeader) {
			return QString::fromUtf8(mpSoapHeader->wsa5__MessageID);
		}
		return QString();
	}

	//! Get the field "relates to" from the soap header
	QString GetSoapHeaderRelatesTo() const {

		if(mpSoapHeader && mpSoapHeader->wsa5__RelatesTo && mpSoapHeader->wsa5__RelatesTo->__item) {
			return QString::fromUtf8(mpSoapHeader->wsa5__RelatesTo->__item);
		}
		return QString();
	}

	//! Get the field "action" from the soap header
	QString GetSoapHeaderAction() const {

		if(mpSoapHeader && mpSoapHeader->wsa5__Action) {
			return QString::fromUtf8(mpSoapHeader->wsa5__Action);
		}
		return QString();
	}

	//! Get the field "to" from the soap header
	QString GetSoapHeaderTo() const {

		if(mpSoapHeader && mpSoapHeader->wsa5__To) {
			return QString::fromUtf8(mpSoapHeader->wsa5__To);
		}
		return QString();
	}

	virtual void PopulateFromCtx(const QSharedPointer<SoapCtx> &rSoapCtx) override {

		SimpleResponse::PopulateFromCtx(rSoapCtx);
		auto errorCode = rSoapCtx->GetFaultCode();
		if(errorCode != SOAP_OK) {
			SetSoapHeader(nullptr);
			auto pSoap = rSoapCtx->Acquire();
			if(pSoap->fault) SetEnvDetail(pSoap->fault->SOAP_ENV__Detail);
			rSoapCtx->Release();
		} else {
			SetEnvDetail(nullptr);
			auto pSoap = rSoapCtx->Acquire();
			SetSoapHeader(pSoap->header);
			rSoapCtx->Release();
		}
	}

 private:
	SOAP_ENV__Detail *mpFaultResultObject;
	SOAP_ENV__Header *mpSoapHeader;
};

/*!
 *
 * \brief A complete response of a WS call
 *
 * Holds an error and a soap fault response object or a soap header and a soap response object
 *
 */
template<class T, class Deleter = SoapDeleter<T>, class Duplicator = SoapDuplicator<T>>
class Response : public DetailedResponse {

 public:
	/*!
	 *
	 * \brief Construct an errorless response
	 *
	 */
	Response() : DetailedResponse(), mDeleter(), mDuplicator(), mpResultObject(nullptr), mpDomElement(nullptr) {}

	/*!
	 *
	 * \brief Construct response
	 *
	 */
	Response(int errorCode, const QString &rFault = QString(), const QString &rFaultDetail = QString(), const T *pResultObject = nullptr,
	         const SOAP_ENV__Detail *pFaultObject = nullptr) :
	 DetailedResponse(errorCode, rFault, rFaultDetail, pFaultObject),
	 mDeleter(),
	 mDuplicator(),
	 mpResultObject(pResultObject ? mDuplicator(pResultObject) : nullptr),
	 mpDomElement(nullptr) {}

	Response(const T *pResultObject) :
	 DetailedResponse(),
	 mDeleter(),
	 mDuplicator(),
	 mpResultObject(pResultObject ? mDuplicator(pResultObject) : nullptr),
	 mpDomElement(nullptr) {}

	virtual ~Response() {
		mDeleter(mpResultObject);
		soap_del_xsd__anyType(mpDomElement);
	}

	Response(const Response &rOther) :
	 DetailedResponse(rOther),
	 mDeleter(rOther.mDeleter),
	 mDuplicator(rOther.mDuplicator),
	 mpResultObject(rOther.mpResultObject ? mDuplicator(rOther.mpResultObject) : nullptr),
	 mpDomElement(nullptr) {}

	Response &operator=(const Response &rOther) {

		if(&rOther == this) {
			return *this;
		}
		DetailedResponse::operator=(rOther);
		this->mDeleter(this->mpResultObject);
		this->mpResultObject = rOther.mpResultObject ? mDuplicator(rOther.mpResultObject) : nullptr;
		this->mpDomElement = rOther.mpDomElement ? soap_dup_xsd__anyType(nullptr, nullptr, rOther.mpDomElement) : nullptr;
		return *this;
	}

	//! Get the result object of a WS response
	const T *GetResultObject() const { return mpResultObject; }

#ifdef WITH_DOM
	//! Get the underlying dom tree (only available if SOAP_XML_DOM is set for soap_mode imode)
	const soap_dom_element *GetDomTree() const { return mpDomElement; }
#endif

	//! Set the result object of a WS response
	void SetResultObject(const T *pResultObject) {

		this->mDeleter(this->mpResultObject);
		this->mpResultObject = pResultObject ? mDuplicator(pResultObject) : nullptr;
	}

	bool IsFault() const override { return DetailedResponse::IsFault() || !GetResultObject(); }

	/*!
	 *
	 * \brief Builds a response object
	 *
	 */
	class Builder {

	 public:
		Builder() : mpResult() {}

		Builder &From(const QSharedPointer<SoapCtx> &rSoapCtx, const T *pResultObject = nullptr) {

			mpResult.PopulateFromCtx(rSoapCtx);
			auto errorCode = rSoapCtx->GetFaultCode();
			if(errorCode != SOAP_OK) {
				mpResult.SetResultObject(nullptr);
				mpResult.mpDomElement = nullptr;
			} else {
				auto *pSoap = rSoapCtx->Acquire();
				if(pSoap->dom) mpResult.mpDomElement = soap_dup_xsd__anyType(nullptr, nullptr, pSoap->dom);
				rSoapCtx->Release();
				mpResult.SetResultObject(pResultObject);
			}
			return *this;
		}

		Response<T, Deleter, Duplicator> Build() const { return mpResult; }

	 private:
		Response<T, Deleter, Duplicator> mpResult;
	};

 private:
	Deleter mDeleter;
	Duplicator mDuplicator;
	T *mpResultObject;
	soap_dom_element *mpDomElement;
};

/*!
 *
 * \brief An arbitrary response of a WS call
 *
 * Holds an error and a soap fault response object or a soap header and an arbitrary response object
 *
 */
template<class T>
class ArbitraryResponse : public DetailedResponse {

 public:
	/*!
	 *
	 * \brief Construct an errorless response
	 *
	 */
	ArbitraryResponse() : DetailedResponse(), mResultObject() {}

	/*!
	 *
	 * \brief Construct a response
	 *
	 */
	ArbitraryResponse(int errorCode, const QString &rFault = QString(), const QString &rFaultDetail = QString(),
	                  const SOAP_ENV__Detail *pFaultObject = nullptr) :
	 DetailedResponse(errorCode, rFault, rFaultDetail, pFaultObject), mResultObject() {}

	ArbitraryResponse(const DetailedResponse &rOther) : DetailedResponse(rOther), mResultObject() {}

	ArbitraryResponse(const ArbitraryResponse &rOther) : DetailedResponse(rOther), mResultObject(rOther.mResultObject) {}

	ArbitraryResponse &operator=(const ArbitraryResponse &rOther) {

		if(&rOther == this) {
			return *this;
		}
		DetailedResponse::operator=(rOther);
		mResultObject = rOther.mResultObject;
		return *this;
	}

	ArbitraryResponse &operator=(const DetailedResponse &rOther) {

		if(&rOther == this) {
			return *this;
		}
		DetailedResponse::operator=(rOther);
		mResultObject = T();
		return *this;
	}

	// Get the arbitrary response object
	T GetResultObject() const { return mResultObject; }
	// Set the arbitrary response object
	void SetResultObject(const T &rResultObject) { mResultObject = rResultObject; }

	/*!
	 *
	 * \brief Builds an arbitrary response object
	 *
	 */
	class Builder {

	 public:
		Builder() : mpResult() {}

		Builder &From(const QSharedPointer<SoapCtx> &rSoapCtx, const T &rResultObject) {

			mpResult.PopulateFromCtx(rSoapCtx);
			auto errorCode = rSoapCtx->GetFaultCode();
			if(errorCode == SOAP_OK) {
				mpResult.SetResultObject(rResultObject);
			}
			return *this;
		}

		Builder &From(const QSharedPointer<SoapCtx> &rSoapCtx) {

			mpResult.PopulateFromCtx(rSoapCtx);
			return *this;
		}

		ArbitraryResponse<T> Build() const { return mpResult; }

	 private:
		ArbitraryResponse<T> mpResult;
	};

 private:
	T mResultObject;
};

REGISTER_METATYPE(SimpleResponse)
