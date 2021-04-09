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
#include "Client.h"
#include "soapH.h"
#include "SoapAuthHandler.h"
#include <QDebug>
#include <QObject>
#include <utility>
#include <QMutex>


struct ClientPrivate {
	ClientPrivate(Client *pQ, QUrl rEndpoint, QSharedPointer<SoapCtx> sharedCtx) :
	 mpQ(pQ), mCtx(std::move(sharedCtx)), mEndpoint(std::move(rEndpoint)) {}

	Client *mpQ;
	QSharedPointer<SoapCtx> mCtx;
	QUrl mEndpoint;
	QMutex mMutex;
};

Client::Client(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx, QObject *pParent) :
 QObject(pParent), mpD(new ClientPrivate(this, rEndpoint, std::move(sharedCtx))) {}

Client::~Client() {

	delete mpD;
}

soap *Client::AcquireCtx() {

	auto pCtx = mpD->mCtx->Acquire();
	if(pCtx) {
		mpD->mCtx->RestoreAuthData();
	}
	return pCtx;
}

soap *Client::TryAcquireCtx(int timeoutMs /*= 0*/) {

	auto pCtx = mpD->mCtx->TryAcquire(timeoutMs);
	if(pCtx) {
		mpD->mCtx->RestoreAuthData();
	}
	return pCtx;
}

void Client::ReleaseCtx(soap *pCtx) {

	if(pCtx) {
		soap_destroy(pCtx);
		soap_end(pCtx);
		mpD->mCtx->Release();
	}
}

void Client::DisableAuth() {

	mpD->mCtx->DisableAuth();
}

void Client::SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode /* = AUTO */) {

	auto authMode = AuthHandlerMode::AUTO;
	switch(mode) {
		case NO_AUTH:
			authMode = AuthHandlerMode::NO_AUTH;
			break;
		case HTTP_DIGEST:
			authMode = AuthHandlerMode::HTTP_DIGEST;
			break;
		case WS_USERNAME_TOKEN:
			authMode = AuthHandlerMode::WS_USERNAME_TOKEN;
			break;
		case BOTH:
			authMode = AuthHandlerMode::BOTH;
			break;
		case AUTO:
		default:
			authMode = AuthHandlerMode::AUTO;
			break;
	}
	mpD->mCtx->SetAuth(rUserName, rPassword, authMode);
}

QString Client::GetFaultString() {

	return mpD->mCtx->GetFaultString();
}

QString Client::GetFaultDetail() {

	return mpD->mCtx->GetFaultDetail();
}

QUrl Client::GetEndpoint() {

	mpD->mMutex.lock();
	auto ret = mpD->mEndpoint;
	mpD->mMutex.unlock();
	return ret;
}

void Client::SetEndpoint(const QUrl &rEndpoint) {

	mpD->mMutex.lock();
	mpD->mEndpoint = rEndpoint;
	mpD->mMutex.unlock();
}

QString Client::GetEndpointString() {

	return GetEndpoint().toString();
}

QSharedPointer<SoapCtx> Client::GetCtx() const {

	return mpD->mCtx;
}

int Client::Retry(soap *pCtx) const {

	Q_UNUSED(pCtx)
	auto retry = false;
	if(mpD->mCtx->IsAuthFault()) retry = mpD->mCtx->ProcessAuthFaultAndRetry();
	if(retry) {
		mpD->mCtx->RestoreAuthData();
	}
	return retry;
}
