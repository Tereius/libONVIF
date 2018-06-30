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
#include "OnvifReplayClient.h"
#include "soapReplayBindingProxy.h"


struct OnvifReplayClientPrivate {
	OnvifReplayClientPrivate(OnvifReplayClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		soap_set_namespaces(mProxy.soap, SoapCtx::GetDefaultNamespaces());
		mpQ->GetCtx()->Release();
	}

	OnvifReplayClient *mpQ;
	ReplayBindingProxy mProxy;
};

OnvifReplayClient::OnvifReplayClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) : Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifReplayClientPrivate(this)) {
}

OnvifReplayClient::~OnvifReplayClient() {

	delete mpD;
}

Response<_trp__GetServiceCapabilitiesResponse> OnvifReplayClient::GetServiceCapabilities(Request<_trp__GetServiceCapabilities> &rRequest) {

	_trp__GetServiceCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trp__GetServiceCapabilitiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trp__GetReplayUriResponse> OnvifReplayClient::GetReplayUri(Request<_trp__GetReplayUri> &rRequest) {

	_trp__GetReplayUriResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetReplayUri(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trp__GetReplayUriResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trp__GetReplayConfigurationResponse> OnvifReplayClient::GetReplayConfiguration(Request<_trp__GetReplayConfiguration> &rRequest) {

	_trp__GetReplayConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.GetReplayConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trp__GetReplayConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_trp__SetReplayConfigurationResponse> OnvifReplayClient::SetReplayConfiguration(Request<_trp__SetReplayConfiguration> &rRequest) {

	_trp__SetReplayConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = acquireCtx();
	do {
		ret = mpD->mProxy.SetReplayConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_trp__SetReplayConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}
