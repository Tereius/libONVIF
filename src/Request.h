#pragma once
#include <QSharedPointer>
#include <QUrl>


template <class T> struct SoapDeleterReq {

	void operator()(T* p) {
		if(p) p->soap_del();
		delete p;
	}
};

template <class T, class Deleter = SoapDeleterReq<T>> class Request : public T {

public:
	Request() : 
		T(),
		mSoapAction(),
		mDeleter() {
	
	}
	virtual ~Request() {

		mDeleter(this);
	}
	//! If you want to overwrite the SOAP action of the request.
	void SetSoapAction(const QString &rAction) { mSoapAction = rAction; }
	const QString& GetSoapAction() const { return mSoapAction; }

private:
	Request(const Request &);
	Request & operator=(const Request &);

	QString mSoapAction;
	Deleter mDeleter;
};
