#pragma once
#include "soapH.h"
#include "SafeBool.h"
#include <QString>
#include <QDebug>


#define GENERIC_FAULT 600

class SimpleResponse : public SafeBool<void> {

public:

	SimpleResponse() :
		mErrorCode(SOAP_OK),
		mFault(),
		mFaultDetail() {

	}

	SimpleResponse(int errorCode, const QString &rFault = QString(), const QString &rFaultDetail = QString()) :
		mErrorCode(errorCode),
		mFault(rFault),
		mFaultDetail(rFaultDetail) {

	}

	virtual ~SimpleResponse() {}

	SimpleResponse(const SimpleResponse &rOther) :
		mErrorCode(rOther.mErrorCode),
		mFault(rOther.mFault),
		mFaultDetail(rOther.mFaultDetail) {

	}

	SimpleResponse& operator=(const SimpleResponse &rOther) {

		if(&rOther == this) {
			return *this;
		}
		this->mErrorCode = rOther.mErrorCode;
		this->mFault = rOther.mFault;
		this->mFaultDetail = rOther.mFaultDetail;
		return *this;
	}

	QString GetSoapFault() const { return mFault; }
	void SetFault(const QString &rFault) { mFault = rFault; }
	QString GetSoapFaultDetail() const { return mFaultDetail; }
	void SetFaultDetail(const QString &rFaultDetail) { mFaultDetail = rFaultDetail; }
	QString GetCompleteFault() const {
		auto whatFault = QString("No Fault");
		if(IsFault()) {
			whatFault = "Generic Fault";
			if(IsTcpFault())whatFault = "TCP Fault";
			else if(IsSoapFault()) whatFault = "SOAP Fault";
			else if(IsXmlValidationFault()) whatFault = "XML Val Fault";
			else if(IsSslFault()) whatFault = "SSL Fault";
			else if(IsZlibFault()) whatFault = "Zlib Fault";
			else if(IsHttpFault()) whatFault = "HTTP Fault";
			else whatFault = "Generic Fault";
			whatFault += GetSoapFault();
			whatFault += GetSoapFaultDetail();
		}
		return whatFault;
	}
	int GetErrorCode() const { return mErrorCode; }

	virtual bool IsSuccess() const { return !IsFault(); }
	virtual bool IsFault() const { return mErrorCode != SOAP_OK; }
	bool IsTcpFault() const { return soap_tcp_error_check(mErrorCode); }
	bool IsSoapFault() const { return soap_soap_error_check(mErrorCode); }
	bool IsXmlValidationFault() const { return soap_xml_error_check(mErrorCode); }
	bool IsSslFault() const { return soap_ssl_error_check(mErrorCode); }
	bool IsZlibFault() const { return soap_zlib_error_check(mErrorCode); }
	bool IsHttpFault() const { return soap_http_error_check(mErrorCode); }
	bool BooleanTest() const { return IsSuccess(); }

private:

	int mErrorCode;
	QString mFault;
	QString mFaultDetail;
};

class DetailedResponse : public SimpleResponse {

public:

	DetailedResponse() :
		SimpleResponse(),
		mpFaultResultObject(nullptr) {

	}

	DetailedResponse(int errorCode, const QString &rFault = QString(), const QString &rFaultDetail = QString(), const SOAP_ENV__Detail *pFaultObject = nullptr) :
		SimpleResponse(errorCode, rFault, rFaultDetail),
		mpFaultResultObject(pFaultObject ? soap_dup_SOAP_ENV__Detail(nullptr, nullptr, pFaultObject) : nullptr) {
	}

	virtual ~DetailedResponse() {

		if(mpFaultResultObject) {
			soap_del_SOAP_ENV__Detail(mpFaultResultObject);
		}
		delete mpFaultResultObject;
	}

	DetailedResponse(const DetailedResponse &rOther) :
		SimpleResponse(rOther),
		mpFaultResultObject(rOther.mpFaultResultObject ? soap_dup_SOAP_ENV__Detail(nullptr, nullptr, rOther.mpFaultResultObject) : nullptr) {

	}

	DetailedResponse& operator=(const DetailedResponse &rOther) {

		if(&rOther == this) {
			return *this;
		}
		SimpleResponse::operator=(rOther);
		if(mpFaultResultObject) {
			soap_del_SOAP_ENV__Detail(mpFaultResultObject);
		}
		delete mpFaultResultObject;
		this->mpFaultResultObject = rOther.mpFaultResultObject ? soap_dup_SOAP_ENV__Detail(nullptr, nullptr, rOther.mpFaultResultObject) : nullptr;
		return *this;
	}

	template <typename F> F* GetFaultObject() {
		if(mpFaultResultObject && mpFaultResultObject->fault && mpFaultResultObject->__type) {
			return static_cast<F*>(mpFaultResultObject->fault);
		}
		return nullptr;
	}

private:

	SOAP_ENV__Detail* mpFaultResultObject;
};

template <class T> struct SoapDeleter {

	void operator()(T* p) {
		if(p) p->soap_del();
		delete p;
	}
};

template <class T> struct SoapDuplicator {

	T* operator()(const T *p) {
		return p->soap_dup();
	}
};

template <class T, class Deleter = SoapDeleter<T>, class Duplicator = SoapDuplicator<T>> 
class Response : public DetailedResponse {

public:

	Response() :
		DetailedResponse(),
		mDeleter(),
		mDuplicator(),
		mpResultObject(nullptr) {

	}

	Response(int errorCode, const QString &rFault = QString(), const QString &rFaultDetail = QString(), const T *pResultObject = nullptr, const SOAP_ENV__Detail *pFaultObject = nullptr) :
		DetailedResponse(errorCode, rFault, rFaultDetail, pFaultObject),
		mDeleter(),
		mDuplicator(),
		mpResultObject(pResultObject ? mDuplicator(pResultObject) : nullptr) {

	}

	Response(const T *pResultObject) :
		DetailedResponse(),
		mDeleter(),
		mDuplicator(),
		mpResultObject(pResultObject ? mDuplicator(pResultObject) : nullptr) {

	}

	virtual ~Response() {

		mDeleter(mpResultObject);
	}

	Response(const Response &rOther) :
		DetailedResponse(rOther),
		mDeleter(rOther.mDeleter),
		mDuplicator(rOther.mDuplicator),
		mpResultObject(rOther.mpResultObject ? mDuplicator(rOther.mpResultObject) : nullptr) {

	}

	Response& operator=(const Response &rOther) {

		if(&rOther == this) {
			return *this;
		}
		DetailedResponse::operator=(rOther);
		this->mDeleter(this->mpResultObject);
		this->mpResultObject = rOther.mpResultObject ? mDuplicator(pResultObject) : nullptr;
		return *this;
	}

	const T* getResultObject() const { return mpResultObject; }

	virtual bool IsFault() const { return DetailedResponse::IsFault() || !getResultObject(); }

private:

	Deleter mDeleter;
	Duplicator mDuplicator;
	T* mpResultObject;
};

template <class T> class ArbitraryResponse : public DetailedResponse {

public:

	ArbitraryResponse() :
		DetailedResponse(),
		mResultObject() {

	}

	ArbitraryResponse(int errorCode, const QString &rFault = QString(), const QString &rFaultDetail = QString(), const SOAP_ENV__Detail *pFaultObject = nullptr) :
		DetailedResponse(errorCode, rFault, rFaultDetail, pFaultObject),
		mResultObject() {

	}

	ArbitraryResponse(const DetailedResponse &rOther) :
		DetailedResponse(rOther),
		mResultObject() {

	}

	ArbitraryResponse(const ArbitraryResponse &rOther) :
		DetailedResponse(rOther),
		mResultObject(rOther.mResultObject) {

	}

	ArbitraryResponse& operator=(const ArbitraryResponse &rOther) {

		if(&rOther == this) {
			return *this;
		}
		DetailedResponse::operator=(rOther);
		mResultObject = rOther.mResultObject;
		return *this;
	}

	ArbitraryResponse& operator=(const DetailedResponse &rOther) {

		if(&rOther == this) {
			return *this;
		}
		DetailedResponse::operator=(rOther);
		mResultObject = T();
		return *this;
	}

	T GetResultObject() const { return mResultObject; }
	void SetResultObject(const T &rResultObject) { mResultObject = rResultObject; }

private:

	T mResultObject;
};
