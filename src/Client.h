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
#include "OnvifCommonExport.h"
#include "SoapCtx.h"
#include <QObject>
#include <QSharedPointer>
#include <QUrl>


struct soap;
struct ClientPrivate;

enum AuthMode { NO_AUTH, HTTP_DIGEST, WS_USERNAME_TOKEN, BOTH, AUTO };

/*!
 *
 * \brief This is the base class for all the client side service implementations
 *
 * This class provides thread safe accessors for the soap context and other commonly used methods.
 *
 */
class ONVIFCOMMON_EXPORT Client : public QObject {

	Q_OBJECT

 public:
	/*!
	 *
	 * \brief Construct a new client
	 *
	 * A client may use its own soap context or a shared one. Remember that a pending WS request from one client will block all other
	 * clients that share the same context until the request is finished. If in doubt let every client use its own soap context.
	 *
	 * \param rEndpoint The WS endpoint this client will use for its WS calls
	 * \param sharedCtx The soap context
	 * \param pParent A QObject parent
	 *
	 */
	explicit Client(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	~Client() override;
	/*!
	 *
	 * \brief Get the soap context which is used by the client. The context can be shared between multiple clients
	 *
	 * \return The soap context
	 *
	 */
	QSharedPointer<SoapCtx> GetCtx() const;
	//! Returns the informative fault string of the last service call
	virtual QString GetFaultString();
	//! Returns the informative fault detail string of the last service call
	virtual QString GetFaultDetail();
	//! Returns the WS endpoint url this client was initialized with
	virtual QUrl GetEndpoint();
	//! Change the WS endpoint this client uses
	virtual void SetEndpoint(const QUrl &rEndpoint);
	//! Returns the WS endpoint url as a string this client was initialized with
	virtual QString GetEndpointString();
	//! If this client is currently doing a request it will be canceled immediately. Otherwise nothing happens.
	void CancelRequest();

 protected:
	//! Service implementations use this to acquire/init a raw soap context. releaseCtx must be called afterwards
	soap *AcquireCtx();
	//! Service implementations use this to acquire/init a raw soap context. releaseCtx must be called afterwards if successful.
	//! (If the timeout is reached before the soap context could be acquired/prepared null is returned)
	soap *TryAcquireCtx(int timeoutMs = 0);
	//! Service implementations use this to release a previously acquired raw soap context
	void ReleaseCtx(soap *pCtx);
	//! Service implementations use this to find out how many times a service call has to be repeated
	//! (needed because of HTTP digest authentication)
	int Retry(soap *pCtx) const;

 private:
	Q_DISABLE_COPY(Client);

	ClientPrivate *mpD;
};
