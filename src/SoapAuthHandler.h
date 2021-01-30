/* Copyright(C) 2021 Björn Stresing
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
#include "OnvifCommonExport.h"
#include <QString>
#include <QObject>


struct soap;
struct DefaultAuthHandlerPrivate;

enum class AuthHandlerMode { NO_AUTH = 0, HTTP_DIGEST = 1, WS_USERNAME_TOKEN = 2, BOTH = 3, AUTO = 4, CUSTOM = 100 };

/*!
 *
 * \brief An authorization handler stub
 *
 * Use this abstract class to implement your own handler that evaluates/manages the authorization state of a soap ctx
 *
 */
class ONVIFCOMMON_EXPORT SoapAuthHandler : public QObject {

	Q_OBJECT

public:
	//! The implementation receives the credentials and the proposed AuthHandlerMode
	virtual void SetAuth(soap *pCtx, const QString &rUserName, const QString &rPassword, AuthHandlerMode mode) = 0;
	/*!
	 * \brief The implementation shall reset the authorization state of pCtx and free any memory holding authorization specific data
	 * From now on the implementation shall behave like AuthHandlerMode equals NO_AUTH until SoapAuthHandler::SetAuth is called again
	 */
	virtual void FreeAuth(soap *pCtx) = 0;
	//! The implementation shall return true if it detects an authorization fault. False shall be returned otherwise
	virtual bool IsAuthFault(soap *pCtx) = 0;
	/*!
	 * \brief The implementation shall set authorization specific data of pCtx
	 * This method is invoked <b>before</b> every WS call.
	 * If the AuthHandlerMode equals NO_AUTH the implementation shall do nothing
	 */
	virtual void RestoreAuthData(soap *pCtx) = 0;
	/*!
	 * \brief The implementation shall return true to signal the caller to rerun the WS call.
	 * This method is invoked <b>after</b> every WS call and only if SoapAuthHandler::IsAuthFault returned true before.
	 * If the AuthHandlerMode equals NO_AUTH the implementation shall always return false.
	 * \warning This may lead to an infinite loop if true is always returned. The implementation is responsible to avoid this loop
	 */
	virtual bool ProcessAuthFaultAndRetry(soap *pCtx) = 0;

signals:
	/*!
	 * \brief Signal the receiver that the authorization finally failed
	 * If this signal is connected to a slot via a direct connection or blocking queued connection you have a chance
	 * to provide new credentials by calling SoapAuthHandler::SetAuth. The failed request will then be rerun.
	 * Implementations may emit this signal to provide the functionality described above
	 */
	void Unauthorized();
};

/*!
 *
 * \brief The default authorization handler
 *
 * This handler manages WSS token and HTTP digest authorization
 *
 */
class ONVIFCOMMON_EXPORT DefaultAuthHandler : public SoapAuthHandler {

public:
	DefaultAuthHandler();
	~DefaultAuthHandler() override;
	void SetAuth(soap *pCtx, const QString &rUserName, const QString &rPassword, AuthHandlerMode mode) override;
	//! Returns true if either an WSS token or HTTP digest authorization fault is detected
	bool IsAuthFault(soap *pCtx) override;
	//! Returns true if an HTTP digest authorization fault is detected
	virtual bool IsHttpAuthFault(soap *pCtx);
	//! Returns true if an WSS token authorization fault is detected
	virtual bool IsWssTokenAuthFault(soap *pCtx);
	void FreeAuth(soap *pCtx) override;
	void RestoreAuthData(soap *pCtx) override;
	bool ProcessAuthFaultAndRetry(soap *pCtx) override;

private:
	DefaultAuthHandlerPrivate *mpD;
};
