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
#include "SoapAuthHandler.h"
#include "soapH.h"
#include "global.h"
#include <QDebug>
#ifdef WITH_OPENSSL
#include "wsseapi.h"
#include "httpda.h"
#else
#include "wsseapi-lite.h"
#endif // WITH_OPENSSL

struct DefaultAuthHandlerPrivate {
	explicit DefaultAuthHandlerPrivate(SoapAuthHandler *pQ) :
	 mpQ(pQ),
	 mAuthmode(AuthHandlerMode::NO_AUTH),
	 mUserName(),
	 mPassword(),
#ifdef WITH_OPENSSL
	 mDigestStore(),
#endif // WITH_OPENSSL
	 mAuthProcessed(false) {
	}

	SoapAuthHandler *mpQ;
	AuthHandlerMode mAuthmode;
	QString mUserName;
	QString mPassword;
#ifdef WITH_OPENSSL
	http_da_info mDigestStore;
#endif // WITH_OPENSSL
	bool mAuthProcessed;
};

DefaultAuthHandler::DefaultAuthHandler() : mpD(new DefaultAuthHandlerPrivate(this)) {}

DefaultAuthHandler::~DefaultAuthHandler() {

	delete mpD;
}

void DefaultAuthHandler::SetAuth(soap *pCtx, const QString &rUserName, const QString &rPassword, AuthHandlerMode mode) {

	if(pCtx) {
#ifdef WITH_OPENSSL
		if(!soap_lookup_plugin(pCtx, HTTP_DA_ID)) {
			soap_register_plugin(pCtx, http_da);
		}
#endif
		FreeAuth(pCtx);
		mpD->mAuthProcessed = false;
#ifndef WITH_OPENSSL
		if(mode != AuthHandlerMode::NO_AUTH && mode != AuthHandlerMode::WS_USERNAME_TOKEN) {
			mode = AuthHandlerMode::WS_USERNAME_TOKEN;
			qWarning() << "This build doesn't support http digest auth. Switching back to ws token";
		}
#endif // WITH_OPENSSL
		mpD->mAuthmode = mode;
		mpD->mUserName = rUserName;
		mpD->mPassword = rPassword;
	}
}

void DefaultAuthHandler::FreeAuth(soap *pCtx) {

	mpD->mAuthmode = AuthHandlerMode::NO_AUTH;
	mpD->mAuthProcessed = false;
	if(pCtx) {
#ifdef WITH_OPENSSL
		if(mpD->mDigestStore.authrealm) {
			http_da_release(pCtx, &mpD->mDigestStore);
		}
#endif // WITH_OPENSSL
		soap_wsse_delete_Security(pCtx);
	}
}

bool DefaultAuthHandler::IsAuthFault(soap *pCtx) {

	return IsHttpAuthFault(pCtx) || IsWssTokenAuthFault(pCtx);
}

bool DefaultAuthHandler::IsHttpAuthFault(soap *pCtx) {

	if(pCtx) return pCtx->error == HTTP_UNAUTHORIZED;
	return false;
}

bool DefaultAuthHandler::IsWssTokenAuthFault(soap *pCtx) {

	if(pCtx) {
		auto faultsubcode = QString();
		if(pCtx->error != SOAP_OK) {
			if(*soap_faultsubcode(pCtx)) faultsubcode = QString::fromLocal8Bit(*soap_faultsubcode(pCtx));
		}
		return pCtx->error == SOAP_CLI_FAULT && faultsubcode.compare("\"http://www.onvif.org/ver10/error\":NotAuthorized") == 0;
	}
	return false;
}

void DefaultAuthHandler::RestoreAuthData(soap *pCtx) {

	if(pCtx) {
		if(mpD->mAuthProcessed) {
			if(mpD->mAuthmode == AuthHandlerMode::HTTP_DIGEST || mpD->mAuthmode == AuthHandlerMode::BOTH) {
#ifdef WITH_OPENSSL
				if(mpD->mDigestStore.authrealm) {
					http_da_restore(pCtx, &mpD->mDigestStore);
				} else {
					qWarning() << "The authrealm is missing in http_da_restore. Falling back to WS token auth.";
					mpD->mAuthmode = AuthHandlerMode::WS_USERNAME_TOKEN;
				}
#endif // WITH_OPENSSL
			}
			if(mpD->mAuthmode == AuthHandlerMode::WS_USERNAME_TOKEN || mpD->mAuthmode == AuthHandlerMode::BOTH) {
				soap_wsse_delete_Security(pCtx);
#ifdef WITH_OPENSSL
				soap_wsse_add_UsernameTokenDigest(pCtx, nullptr, qPrintable(mpD->mUserName), qPrintable(mpD->mPassword));
#else
				soap_wsse_add_UsernameTokenText(pCtx, nullptr, qPrintable(mpD->mUserName), qPrintable(mpD->mPassword));
#endif
				soap_wsse_add_Timestamp(pCtx, nullptr, 0);
			}
		}
	}
}

bool DefaultAuthHandler::ProcessAuthFaultAndRetry(soap *pCtx, int numRetry) {

	if(pCtx) {
		bool ret = false;
		if(IsAuthFault(pCtx)) {

			if(IsHttpAuthFault(pCtx) && mpD->mAuthProcessed && pCtx->authrealm && numRetry == 0) {
				// nonce probably changed
				mpD->mAuthProcessed = false;
			}

			if(!mpD->mAuthProcessed) {
				if((mpD->mAuthmode == AuthHandlerMode::HTTP_DIGEST || mpD->mAuthmode == AuthHandlerMode::BOTH ||
				    mpD->mAuthmode == AuthHandlerMode::AUTO) &&
				   pCtx->authrealm) {
					// HTTP digest auth.
					if(mpD->mAuthmode == AuthHandlerMode::AUTO) mpD->mAuthmode = AuthHandlerMode::HTTP_DIGEST;
#ifdef WITH_OPENSSL
					http_da_save(pCtx, &mpD->mDigestStore, pCtx->authrealm, qPrintable(mpD->mUserName), qPrintable(mpD->mPassword));
#endif // WITH_OPENSSL
				}
				if(mpD->mAuthmode == AuthHandlerMode::WS_USERNAME_TOKEN || mpD->mAuthmode == AuthHandlerMode::BOTH ||
				   mpD->mAuthmode == AuthHandlerMode::AUTO) {
					// WS token auth.
					if(mpD->mAuthmode == AuthHandlerMode::AUTO) mpD->mAuthmode = AuthHandlerMode::WS_USERNAME_TOKEN;
				}
				ret = mpD->mAuthProcessed = true;
			} else {
				emit Unauthorized();
				// check if new credentials were provided. If so retry
				ret = false;
			}
		}
		return ret;
	}
	return false;
}
