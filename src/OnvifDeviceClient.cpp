#include "OnvifDeviceClient.h"
#include "soapDeviceBindingProxy.h"
#include "namespaces.nsmap"

struct OnvifDeviceClientPrivate {

	OnvifDeviceClientPrivate(OnvifDeviceClient *pQ) : mpQ(pQ),
		mProxy(mpQ->GetCtx()->Acquire()) {
		soap_set_namespaces(mProxy.soap, namespaces);
		mpQ->GetCtx()->Release();
	}
	OnvifDeviceClient *mpQ;
	DeviceBindingProxy mProxy;
};

OnvifDeviceClient::OnvifDeviceClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx /*= QSharedPointer<SoapCtx>::create()*/, QObject *pParent /*= nullptr*/) : Client(rEndpoint, sharedCtx, pParent),
mpD(new OnvifDeviceClientPrivate(this)) {
}

OnvifDeviceClient::~OnvifDeviceClient() {

	delete mpD;
}

Response<_tds__GetServicesResponse> OnvifDeviceClient::GetServices(Request<_tds__GetServices> &rRequest) {

	_tds__GetServicesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetServices(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetServicesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetServiceCapabilitiesResponse> OnvifDeviceClient::GetServiceCapabilities(Request<_tds__GetServiceCapabilities> &rRequest) {

	_tds__GetServiceCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetServiceCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetServiceCapabilitiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetDeviceInformationResponse> OnvifDeviceClient::GetDeviceInformation(Request<_tds__GetDeviceInformation> &rRequest) {

	_tds__GetDeviceInformationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetDeviceInformation(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetDeviceInformationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetSystemDateAndTimeResponse> OnvifDeviceClient::SetSystemDateAndTime(Request<_tds__SetSystemDateAndTime> &rRequest) {

	_tds__SetSystemDateAndTimeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetSystemDateAndTime(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetSystemDateAndTimeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetSystemDateAndTimeResponse> OnvifDeviceClient::GetSystemDateAndTime(Request<_tds__GetSystemDateAndTime> &rRequest) {

	_tds__GetSystemDateAndTimeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetSystemDateAndTime(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetSystemDateAndTimeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetSystemFactoryDefaultResponse> OnvifDeviceClient::SetSystemFactoryDefault(Request<_tds__SetSystemFactoryDefault> &rRequest) {

	_tds__SetSystemFactoryDefaultResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetSystemFactoryDefault(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetSystemFactoryDefaultResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__UpgradeSystemFirmwareResponse> OnvifDeviceClient::UpgradeSystemFirmware(Request<_tds__UpgradeSystemFirmware> &rRequest) {

	_tds__UpgradeSystemFirmwareResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.UpgradeSystemFirmware(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__UpgradeSystemFirmwareResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SystemRebootResponse> OnvifDeviceClient::SystemReboot(Request<_tds__SystemReboot> &rRequest) {

	_tds__SystemRebootResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SystemReboot(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SystemRebootResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__RestoreSystemResponse> OnvifDeviceClient::RestoreSystem(Request<_tds__RestoreSystem> &rRequest) {

	_tds__RestoreSystemResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RestoreSystem(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__RestoreSystemResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetSystemBackupResponse> OnvifDeviceClient::GetSystemBackup(Request<_tds__GetSystemBackup> &rRequest) {

	_tds__GetSystemBackupResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetSystemBackup(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetSystemBackupResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetSystemLogResponse> OnvifDeviceClient::GetSystemLog(Request<_tds__GetSystemLog> &rRequest) {

	_tds__GetSystemLogResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetSystemLog(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetSystemLogResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetSystemSupportInformationResponse> OnvifDeviceClient::GetSystemSupportInformation(Request<_tds__GetSystemSupportInformation> &rRequest) {

	_tds__GetSystemSupportInformationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetSystemSupportInformation(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetSystemSupportInformationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetScopesResponse> OnvifDeviceClient::GetScopes(Request<_tds__GetScopes> &rRequest) {

	_tds__GetScopesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetScopes(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetScopesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetScopesResponse> OnvifDeviceClient::SetScopes(Request<_tds__SetScopes> &rRequest) {

	_tds__SetScopesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetScopes(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetScopesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__AddScopesResponse> OnvifDeviceClient::AddScopes(Request<_tds__AddScopes> &rRequest) {

	_tds__AddScopesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.AddScopes(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__AddScopesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__RemoveScopesResponse> OnvifDeviceClient::RemoveScopes(Request<_tds__RemoveScopes> &rRequest) {

	_tds__RemoveScopesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RemoveScopes(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__RemoveScopesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetDiscoveryModeResponse> OnvifDeviceClient::GetDiscoveryMode(Request<_tds__GetDiscoveryMode> &rRequest) {

	_tds__GetDiscoveryModeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetDiscoveryMode(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetDiscoveryModeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetDiscoveryModeResponse> OnvifDeviceClient::SetDiscoveryMode(Request<_tds__SetDiscoveryMode> &rRequest) {

	_tds__SetDiscoveryModeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetDiscoveryMode(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetDiscoveryModeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetRemoteDiscoveryModeResponse> OnvifDeviceClient::GetRemoteDiscoveryMode(Request<_tds__GetRemoteDiscoveryMode> &rRequest) {

	_tds__GetRemoteDiscoveryModeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetRemoteDiscoveryMode(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetRemoteDiscoveryModeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetRemoteDiscoveryModeResponse> OnvifDeviceClient::SetRemoteDiscoveryMode(Request<_tds__SetRemoteDiscoveryMode> &rRequest) {

	_tds__SetRemoteDiscoveryModeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetRemoteDiscoveryMode(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetRemoteDiscoveryModeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetDPAddressesResponse> OnvifDeviceClient::GetDPAddresses(Request<_tds__GetDPAddresses> &rRequest) {

	_tds__GetDPAddressesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetDPAddresses(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetDPAddressesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetEndpointReferenceResponse> OnvifDeviceClient::GetEndpointReference(Request<_tds__GetEndpointReference> &rRequest) {

	_tds__GetEndpointReferenceResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetEndpointReference(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetEndpointReferenceResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetRemoteUserResponse> OnvifDeviceClient::GetRemoteUser(Request<_tds__GetRemoteUser> &rRequest) {

	_tds__GetRemoteUserResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetRemoteUser(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetRemoteUserResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetRemoteUserResponse> OnvifDeviceClient::SetRemoteUser(Request<_tds__SetRemoteUser> &rRequest) {

	_tds__SetRemoteUserResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetRemoteUser(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetRemoteUserResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetUsersResponse> OnvifDeviceClient::GetUsers(Request<_tds__GetUsers> &rRequest) {

	_tds__GetUsersResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetUsers(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetUsersResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__CreateUsersResponse> OnvifDeviceClient::CreateUsers(Request<_tds__CreateUsers> &rRequest) {

	_tds__CreateUsersResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.CreateUsers(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__CreateUsersResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__DeleteUsersResponse> OnvifDeviceClient::DeleteUsers(Request<_tds__DeleteUsers> &rRequest) {

	_tds__DeleteUsersResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeleteUsers(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__DeleteUsersResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetUserResponse> OnvifDeviceClient::SetUser(Request<_tds__SetUser> &rRequest) {

	_tds__SetUserResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetUser(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetUserResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetWsdlUrlResponse> OnvifDeviceClient::GetWsdlUrl(Request<_tds__GetWsdlUrl> &rRequest) {

	_tds__GetWsdlUrlResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetWsdlUrl(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetWsdlUrlResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetCapabilitiesResponse> OnvifDeviceClient::GetCapabilities(Request<_tds__GetCapabilities> &rRequest) {

	_tds__GetCapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCapabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetCapabilitiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetDPAddressesResponse> OnvifDeviceClient::SetDPAddresses(Request<_tds__SetDPAddresses> &rRequest) {

	_tds__SetDPAddressesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetDPAddresses(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetDPAddressesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetHostnameResponse> OnvifDeviceClient::GetHostname(Request<_tds__GetHostname> &rRequest) {

	_tds__GetHostnameResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetHostname(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetHostnameResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetHostnameResponse> OnvifDeviceClient::SetHostname(Request<_tds__SetHostname> &rRequest) {

	_tds__SetHostnameResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetHostname(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetHostnameResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetHostnameFromDHCPResponse> OnvifDeviceClient::SetHostnameFromDHCP(Request<_tds__SetHostnameFromDHCP> &rRequest) {

	_tds__SetHostnameFromDHCPResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetHostnameFromDHCP(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetHostnameFromDHCPResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetDNSResponse> OnvifDeviceClient::GetDNS(Request<_tds__GetDNS> &rRequest) {

	_tds__GetDNSResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetDNS(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetDNSResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetDNSResponse> OnvifDeviceClient::SetDNS(Request<_tds__SetDNS> &rRequest) {

	_tds__SetDNSResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetDNS(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetDNSResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetNTPResponse> OnvifDeviceClient::GetNTP(Request<_tds__GetNTP> &rRequest) {

	_tds__GetNTPResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetNTP(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetNTPResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetNTPResponse> OnvifDeviceClient::SetNTP(Request<_tds__SetNTP> &rRequest) {

	_tds__SetNTPResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetNTP(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetNTPResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetDynamicDNSResponse> OnvifDeviceClient::GetDynamicDNS(Request<_tds__GetDynamicDNS> &rRequest) {

	_tds__GetDynamicDNSResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetDynamicDNS(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetDynamicDNSResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetDynamicDNSResponse> OnvifDeviceClient::SetDynamicDNS(Request<_tds__SetDynamicDNS> &rRequest) {

	_tds__SetDynamicDNSResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetDynamicDNS(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetDynamicDNSResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetNetworkInterfacesResponse> OnvifDeviceClient::GetNetworkInterfaces(Request<_tds__GetNetworkInterfaces> &rRequest) {

	_tds__GetNetworkInterfacesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetNetworkInterfaces(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetNetworkInterfacesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetNetworkInterfacesResponse> OnvifDeviceClient::SetNetworkInterfaces(Request<_tds__SetNetworkInterfaces> &rRequest) {

	_tds__SetNetworkInterfacesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetNetworkInterfaces(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetNetworkInterfacesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetNetworkProtocolsResponse> OnvifDeviceClient::GetNetworkProtocols(Request<_tds__GetNetworkProtocols> &rRequest) {

	_tds__GetNetworkProtocolsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetNetworkProtocols(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetNetworkProtocolsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetNetworkProtocolsResponse> OnvifDeviceClient::SetNetworkProtocols(Request<_tds__SetNetworkProtocols> &rRequest) {

	_tds__SetNetworkProtocolsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetNetworkProtocols(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetNetworkProtocolsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetNetworkDefaultGatewayResponse> OnvifDeviceClient::GetNetworkDefaultGateway(Request<_tds__GetNetworkDefaultGateway> &rRequest) {

	_tds__GetNetworkDefaultGatewayResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetNetworkDefaultGateway(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetNetworkDefaultGatewayResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetNetworkDefaultGatewayResponse> OnvifDeviceClient::SetNetworkDefaultGateway(Request<_tds__SetNetworkDefaultGateway> &rRequest) {

	_tds__SetNetworkDefaultGatewayResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetNetworkDefaultGateway(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetNetworkDefaultGatewayResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetZeroConfigurationResponse> OnvifDeviceClient::GetZeroConfiguration(Request<_tds__GetZeroConfiguration> &rRequest) {

	_tds__GetZeroConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetZeroConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetZeroConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetZeroConfigurationResponse> OnvifDeviceClient::SetZeroConfiguration(Request<_tds__SetZeroConfiguration> &rRequest) {

	_tds__SetZeroConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetZeroConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetZeroConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetIPAddressFilterResponse> OnvifDeviceClient::GetIPAddressFilter(Request<_tds__GetIPAddressFilter> &rRequest) {

	_tds__GetIPAddressFilterResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetIPAddressFilter(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetIPAddressFilterResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetIPAddressFilterResponse> OnvifDeviceClient::SetIPAddressFilter(Request<_tds__SetIPAddressFilter> &rRequest) {

	_tds__SetIPAddressFilterResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetIPAddressFilter(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetIPAddressFilterResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__AddIPAddressFilterResponse> OnvifDeviceClient::AddIPAddressFilter(Request<_tds__AddIPAddressFilter> &rRequest) {

	_tds__AddIPAddressFilterResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.AddIPAddressFilter(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__AddIPAddressFilterResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__RemoveIPAddressFilterResponse> OnvifDeviceClient::RemoveIPAddressFilter(Request<_tds__RemoveIPAddressFilter> &rRequest) {

	_tds__RemoveIPAddressFilterResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.RemoveIPAddressFilter(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__RemoveIPAddressFilterResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetAccessPolicyResponse> OnvifDeviceClient::GetAccessPolicy(Request<_tds__GetAccessPolicy> &rRequest) {

	_tds__GetAccessPolicyResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetAccessPolicy(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetAccessPolicyResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetAccessPolicyResponse> OnvifDeviceClient::SetAccessPolicy(Request<_tds__SetAccessPolicy> &rRequest) {

	_tds__SetAccessPolicyResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetAccessPolicy(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetAccessPolicyResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__CreateCertificateResponse> OnvifDeviceClient::CreateCertificate(Request<_tds__CreateCertificate> &rRequest) {

	_tds__CreateCertificateResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.CreateCertificate(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__CreateCertificateResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetCertificatesResponse> OnvifDeviceClient::GetCertificates(Request<_tds__GetCertificates> &rRequest) {

	_tds__GetCertificatesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCertificates(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetCertificatesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetCertificatesStatusResponse> OnvifDeviceClient::GetCertificatesStatus(Request<_tds__GetCertificatesStatus> &rRequest) {

	_tds__GetCertificatesStatusResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCertificatesStatus(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetCertificatesStatusResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetCertificatesStatusResponse> OnvifDeviceClient::SetCertificatesStatus(Request<_tds__SetCertificatesStatus> &rRequest) {

	_tds__SetCertificatesStatusResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetCertificatesStatus(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetCertificatesStatusResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__DeleteCertificatesResponse> OnvifDeviceClient::DeleteCertificates(Request<_tds__DeleteCertificates> &rRequest) {

	_tds__DeleteCertificatesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeleteCertificates(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__DeleteCertificatesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetPkcs10RequestResponse> OnvifDeviceClient::GetPkcs10Request(Request<_tds__GetPkcs10Request> &rRequest) {

	_tds__GetPkcs10RequestResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetPkcs10Request(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetPkcs10RequestResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__LoadCertificatesResponse> OnvifDeviceClient::LoadCertificates(Request<_tds__LoadCertificates> &rRequest) {

	_tds__LoadCertificatesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.LoadCertificates(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__LoadCertificatesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetClientCertificateModeResponse> OnvifDeviceClient::GetClientCertificateMode(Request<_tds__GetClientCertificateMode> &rRequest) {

	_tds__GetClientCertificateModeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetClientCertificateMode(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetClientCertificateModeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetClientCertificateModeResponse> OnvifDeviceClient::SetClientCertificateMode(Request<_tds__SetClientCertificateMode> &rRequest) {

	_tds__SetClientCertificateModeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetClientCertificateMode(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetClientCertificateModeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetRelayOutputsResponse> OnvifDeviceClient::GetRelayOutputs(Request<_tds__GetRelayOutputs> &rRequest) {

	_tds__GetRelayOutputsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetRelayOutputs(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetRelayOutputsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetRelayOutputSettingsResponse> OnvifDeviceClient::SetRelayOutputSettings(Request<_tds__SetRelayOutputSettings> &rRequest) {

	_tds__SetRelayOutputSettingsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetRelayOutputSettings(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetRelayOutputSettingsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetRelayOutputStateResponse> OnvifDeviceClient::SetRelayOutputState(Request<_tds__SetRelayOutputState> &rRequest) {

	_tds__SetRelayOutputStateResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetRelayOutputState(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetRelayOutputStateResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SendAuxiliaryCommandResponse> OnvifDeviceClient::SendAuxiliaryCommand(Request<_tds__SendAuxiliaryCommand> &rRequest) {

	_tds__SendAuxiliaryCommandResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SendAuxiliaryCommand(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SendAuxiliaryCommandResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetCACertificatesResponse> OnvifDeviceClient::GetCACertificates(Request<_tds__GetCACertificates> &rRequest) {

	_tds__GetCACertificatesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCACertificates(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetCACertificatesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__LoadCertificateWithPrivateKeyResponse> OnvifDeviceClient::LoadCertificateWithPrivateKey(Request<_tds__LoadCertificateWithPrivateKey> &rRequest) {

	_tds__LoadCertificateWithPrivateKeyResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.LoadCertificateWithPrivateKey(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__LoadCertificateWithPrivateKeyResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetCertificateInformationResponse> OnvifDeviceClient::GetCertificateInformation(Request<_tds__GetCertificateInformation> &rRequest) {

	_tds__GetCertificateInformationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetCertificateInformation(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetCertificateInformationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__LoadCACertificatesResponse> OnvifDeviceClient::LoadCACertificates(Request<_tds__LoadCACertificates> &rRequest) {

	_tds__LoadCACertificatesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.LoadCACertificates(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__LoadCACertificatesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__CreateDot1XConfigurationResponse> OnvifDeviceClient::CreateDot1XConfiguration(Request<_tds__CreateDot1XConfiguration> &rRequest) {

	_tds__CreateDot1XConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.CreateDot1XConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__CreateDot1XConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetDot1XConfigurationResponse> OnvifDeviceClient::SetDot1XConfiguration(Request<_tds__SetDot1XConfiguration> &rRequest) {

	_tds__SetDot1XConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetDot1XConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetDot1XConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetDot1XConfigurationResponse> OnvifDeviceClient::GetDot1XConfiguration(Request<_tds__GetDot1XConfiguration> &rRequest) {

	_tds__GetDot1XConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetDot1XConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetDot1XConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetDot1XConfigurationsResponse> OnvifDeviceClient::GetDot1XConfigurations(Request<_tds__GetDot1XConfigurations> &rRequest) {

	_tds__GetDot1XConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetDot1XConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetDot1XConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__DeleteDot1XConfigurationResponse> OnvifDeviceClient::DeleteDot1XConfiguration(Request<_tds__DeleteDot1XConfiguration> &rRequest) {

	_tds__DeleteDot1XConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeleteDot1XConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__DeleteDot1XConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetDot11CapabilitiesResponse> OnvifDeviceClient::GetDot11Capabilities(Request<_tds__GetDot11Capabilities> &rRequest) {

	_tds__GetDot11CapabilitiesResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetDot11Capabilities(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetDot11CapabilitiesResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetDot11StatusResponse> OnvifDeviceClient::GetDot11Status(Request<_tds__GetDot11Status> &rRequest) {

	_tds__GetDot11StatusResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetDot11Status(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetDot11StatusResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__ScanAvailableDot11NetworksResponse> OnvifDeviceClient::ScanAvailableDot11Networks(Request<_tds__ScanAvailableDot11Networks> &rRequest) {

	_tds__ScanAvailableDot11NetworksResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.ScanAvailableDot11Networks(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__ScanAvailableDot11NetworksResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetSystemUrisResponse> OnvifDeviceClient::GetSystemUris(Request<_tds__GetSystemUris> &rRequest) {

	_tds__GetSystemUrisResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetSystemUris(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetSystemUrisResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__StartFirmwareUpgradeResponse> OnvifDeviceClient::StartFirmwareUpgrade(Request<_tds__StartFirmwareUpgrade> &rRequest) {

	_tds__StartFirmwareUpgradeResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.StartFirmwareUpgrade(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__StartFirmwareUpgradeResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__StartSystemRestoreResponse> OnvifDeviceClient::StartSystemRestore(Request<_tds__StartSystemRestore> &rRequest) {

	_tds__StartSystemRestoreResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.StartSystemRestore(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__StartSystemRestoreResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetStorageConfigurationsResponse> OnvifDeviceClient::GetStorageConfigurations(Request<_tds__GetStorageConfigurations> &rRequest) {

	_tds__GetStorageConfigurationsResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetStorageConfigurations(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetStorageConfigurationsResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__CreateStorageConfigurationResponse> OnvifDeviceClient::CreateStorageConfiguration(Request<_tds__CreateStorageConfiguration> &rRequest) {

	_tds__CreateStorageConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.CreateStorageConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__CreateStorageConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetStorageConfigurationResponse> OnvifDeviceClient::GetStorageConfiguration(Request<_tds__GetStorageConfiguration> &rRequest) {

	_tds__GetStorageConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetStorageConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetStorageConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetStorageConfigurationResponse> OnvifDeviceClient::SetStorageConfiguration(Request<_tds__SetStorageConfiguration> &rRequest) {

	_tds__SetStorageConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetStorageConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetStorageConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__DeleteStorageConfigurationResponse> OnvifDeviceClient::DeleteStorageConfiguration(Request<_tds__DeleteStorageConfiguration> &rRequest) {

	_tds__DeleteStorageConfigurationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeleteStorageConfiguration(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__DeleteStorageConfigurationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__GetGeoLocationResponse> OnvifDeviceClient::GetGeoLocation(Request<_tds__GetGeoLocation> &rRequest) {

	_tds__GetGeoLocationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.GetGeoLocation(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__GetGeoLocationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__SetGeoLocationResponse> OnvifDeviceClient::SetGeoLocation(Request<_tds__SetGeoLocation> &rRequest) {

	_tds__SetGeoLocationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.SetGeoLocation(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__SetGeoLocationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}

Response<_tds__DeleteGeoLocationResponse> OnvifDeviceClient::DeleteGeoLocation(Request<_tds__DeleteGeoLocation> &rRequest) {

	_tds__DeleteGeoLocationResponse responseObject;
	auto ret = SOAP_OK;
	auto pSoap = ackquireCtx();
	do {
		ret = mpD->mProxy.DeleteGeoLocation(qPrintable(GetEndpointString()), !rRequest.GetSoapAction().isNull() ? qPrintable(rRequest.GetSoapAction()) : nullptr, &rRequest, responseObject);
	} while(retry(pSoap));
	auto response = Response<_tds__DeleteGeoLocationResponse>::Builder();
	response.From(GetCtx(), &responseObject);
	releaseCtx(pSoap);
	return response.Build();
}
