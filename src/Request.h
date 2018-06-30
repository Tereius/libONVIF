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
#include <QSharedPointer>
#include <QUrl>

//! Deleter functor
template <class T> struct SoapDeleterReq {

	void operator()(T* p) {
		if(p) p->soap_del();
	}
};

/*!
 *
 * \brief Holds the request parameter of a WS call
 *
 */
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
	//! Use to overwrite the SOAP action of the request
	void SetSoapAction(const QString &rAction) { mSoapAction = rAction; }
	//! The SOAP action to use. Returns a null string if the default SOAP action is used
	QString GetSoapAction() const { return mSoapAction; }

private:
	Request(const Request &);
	Request & operator=(const Request &);

	QString mSoapAction;
	Deleter mDeleter;
};
