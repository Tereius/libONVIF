#pragma once
#include <QSharedPointer>
#include <QUrl>


template <class T> class Request : public T {

public:
	Request() : 
		T(),
		mSoapAction() {
	
	}
	virtual ~Request() {
		soap_del();
	}
	//! If you want to overwrite the SOAP action of the request.
	void SetSoapAction(const QString &rAction) { mSoapAction = rAction; }
	const QString& GetSoapAction() const { return mSoapAction; }

private:
	Request(const Request &);
	Request & operator=(const Request &);

	QString mSoapAction;
};
