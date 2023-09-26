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
#include "SoapAuthHandler.h"
#include "soapH.h"
#include <QAtomicInt>
#include <QDebug>
#include <QMutex>
#include <QObject>
#include <utility>


struct ClientPrivate {
	ClientPrivate(Client *pQ, QUrl rEndpoint, QSharedPointer<SoapCtx> sharedCtx) :
	 mpQ(pQ), mCtx(std::move(sharedCtx)), mEndpoint(std::move(rEndpoint)), mOwnsContext(false) {}

	Client *mpQ;
	QSharedPointer<SoapCtx> mCtx;
	QUrl mEndpoint;
	QMutex mMutex;
	QAtomicInt mOwnsContext;
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
		mpD->mOwnsContext = true;
	}
	return pCtx;
}

soap *Client::TryAcquireCtx(int timeoutMs /*= 0*/) {

	auto pCtx = mpD->mCtx->TryAcquire(timeoutMs);
	if(pCtx) {
		mpD->mCtx->RestoreAuthData();
		mpD->mOwnsContext = true;
	}
	return pCtx;
}

void Client::ReleaseCtx(soap *pCtx) {

	if(pCtx) {
		mpD->mOwnsContext = false;
		soap_destroy(pCtx);
		soap_end(pCtx);
		mpD->mCtx->Release();
	}
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

void Client::CancelRequest() {

	if(mpD->mOwnsContext) {
		mpD->mCtx->ForceSocketClose();
	}
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
