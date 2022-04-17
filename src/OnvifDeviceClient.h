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
#include "Response.h"
#include "Request.h"
#include "Client.h"
#include "OnvifDeviceExport.h"

struct OnvifDeviceClientPrivate;

/*!
 *
 * \brief Client side service implementations of Onvif Device
 *
 */
class ONVIFDEVICE_EXPORT OnvifDeviceClient : public Client {

	Q_OBJECT

public:
	OnvifDeviceClient(const QUrl &rEndpoint, QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(),
	                  QObject *pParent = nullptr);
	virtual ~OnvifDeviceClient();

	static QString GetServiceNamespace() { return SOAP_NAMESPACE_OF_tds; }
	Response<_tds__GetServicesResponse> GetServices(Request<_tds__GetServices> &rRequest);
	Response<_tds__GetServiceCapabilitiesResponse> GetServiceCapabilities(Request<_tds__GetServiceCapabilities> &rRequest);
	Response<_tds__GetDeviceInformationResponse> GetDeviceInformation(Request<_tds__GetDeviceInformation> &rRequest);
	Response<_tds__SetSystemDateAndTimeResponse> SetSystemDateAndTime(Request<_tds__SetSystemDateAndTime> &rRequest);
	Response<_tds__GetSystemDateAndTimeResponse> GetSystemDateAndTime(Request<_tds__GetSystemDateAndTime> &rRequest);
	Response<_tds__SetSystemFactoryDefaultResponse> SetSystemFactoryDefault(Request<_tds__SetSystemFactoryDefault> &rRequest);
	Response<_tds__UpgradeSystemFirmwareResponse> UpgradeSystemFirmware(Request<_tds__UpgradeSystemFirmware> &rRequest);
	Response<_tds__SystemRebootResponse> SystemReboot(Request<_tds__SystemReboot> &rRequest);
	Response<_tds__RestoreSystemResponse> RestoreSystem(Request<_tds__RestoreSystem> &rRequest);
	Response<_tds__GetSystemBackupResponse> GetSystemBackup(Request<_tds__GetSystemBackup> &rRequest);
	Response<_tds__GetSystemLogResponse> GetSystemLog(Request<_tds__GetSystemLog> &rRequest);
	Response<_tds__GetSystemSupportInformationResponse> GetSystemSupportInformation(Request<_tds__GetSystemSupportInformation> &rRequest);
	Response<_tds__GetScopesResponse> GetScopes(Request<_tds__GetScopes> &rRequest);
	Response<_tds__SetScopesResponse> SetScopes(Request<_tds__SetScopes> &rRequest);
	Response<_tds__AddScopesResponse> AddScopes(Request<_tds__AddScopes> &rRequest);
	Response<_tds__RemoveScopesResponse> RemoveScopes(Request<_tds__RemoveScopes> &rRequest);
	Response<_tds__GetDiscoveryModeResponse> GetDiscoveryMode(Request<_tds__GetDiscoveryMode> &rRequest);
	Response<_tds__SetDiscoveryModeResponse> SetDiscoveryMode(Request<_tds__SetDiscoveryMode> &rRequest);
	Response<_tds__GetRemoteDiscoveryModeResponse> GetRemoteDiscoveryMode(Request<_tds__GetRemoteDiscoveryMode> &rRequest);
	Response<_tds__SetRemoteDiscoveryModeResponse> SetRemoteDiscoveryMode(Request<_tds__SetRemoteDiscoveryMode> &rRequest);
	Response<_tds__GetDPAddressesResponse> GetDPAddresses(Request<_tds__GetDPAddresses> &rRequest);
	Response<_tds__GetEndpointReferenceResponse> GetEndpointReference(Request<_tds__GetEndpointReference> &rRequest);
	Response<_tds__GetRemoteUserResponse> GetRemoteUser(Request<_tds__GetRemoteUser> &rRequest);
	Response<_tds__SetRemoteUserResponse> SetRemoteUser(Request<_tds__SetRemoteUser> &rRequest);
	Response<_tds__GetUsersResponse> GetUsers(Request<_tds__GetUsers> &rRequest);
	Response<_tds__CreateUsersResponse> CreateUsers(Request<_tds__CreateUsers> &rRequest);
	Response<_tds__DeleteUsersResponse> DeleteUsers(Request<_tds__DeleteUsers> &rRequest);
	Response<_tds__SetUserResponse> SetUser(Request<_tds__SetUser> &rRequest);
	Response<_tds__GetWsdlUrlResponse> GetWsdlUrl(Request<_tds__GetWsdlUrl> &rRequest);
	Response<_tds__GetCapabilitiesResponse> GetCapabilities(Request<_tds__GetCapabilities> &rRequest);
	Response<_tds__SetDPAddressesResponse> SetDPAddresses(Request<_tds__SetDPAddresses> &rRequest);
	Response<_tds__GetHostnameResponse> GetHostname(Request<_tds__GetHostname> &rRequest);
	Response<_tds__SetHostnameResponse> SetHostname(Request<_tds__SetHostname> &rRequest);
	Response<_tds__SetHostnameFromDHCPResponse> SetHostnameFromDHCP(Request<_tds__SetHostnameFromDHCP> &rRequest);
	Response<_tds__GetDNSResponse> GetDNS(Request<_tds__GetDNS> &rRequest);
	Response<_tds__SetDNSResponse> SetDNS(Request<_tds__SetDNS> &rRequest);
	Response<_tds__GetNTPResponse> GetNTP(Request<_tds__GetNTP> &rRequest);
	Response<_tds__SetNTPResponse> SetNTP(Request<_tds__SetNTP> &rRequest);
	Response<_tds__GetDynamicDNSResponse> GetDynamicDNS(Request<_tds__GetDynamicDNS> &rRequest);
	Response<_tds__SetDynamicDNSResponse> SetDynamicDNS(Request<_tds__SetDynamicDNS> &rRequest);
	Response<_tds__GetNetworkInterfacesResponse> GetNetworkInterfaces(Request<_tds__GetNetworkInterfaces> &rRequest);
	Response<_tds__SetNetworkInterfacesResponse> SetNetworkInterfaces(Request<_tds__SetNetworkInterfaces> &rRequest);
	Response<_tds__GetNetworkProtocolsResponse> GetNetworkProtocols(Request<_tds__GetNetworkProtocols> &rRequest);
	Response<_tds__SetNetworkProtocolsResponse> SetNetworkProtocols(Request<_tds__SetNetworkProtocols> &rRequest);
	Response<_tds__GetNetworkDefaultGatewayResponse> GetNetworkDefaultGateway(Request<_tds__GetNetworkDefaultGateway> &rRequest);
	Response<_tds__SetNetworkDefaultGatewayResponse> SetNetworkDefaultGateway(Request<_tds__SetNetworkDefaultGateway> &rRequest);
	Response<_tds__GetZeroConfigurationResponse> GetZeroConfiguration(Request<_tds__GetZeroConfiguration> &rRequest);
	Response<_tds__SetZeroConfigurationResponse> SetZeroConfiguration(Request<_tds__SetZeroConfiguration> &rRequest);
	Response<_tds__GetIPAddressFilterResponse> GetIPAddressFilter(Request<_tds__GetIPAddressFilter> &rRequest);
	Response<_tds__SetIPAddressFilterResponse> SetIPAddressFilter(Request<_tds__SetIPAddressFilter> &rRequest);
	Response<_tds__AddIPAddressFilterResponse> AddIPAddressFilter(Request<_tds__AddIPAddressFilter> &rRequest);
	Response<_tds__RemoveIPAddressFilterResponse> RemoveIPAddressFilter(Request<_tds__RemoveIPAddressFilter> &rRequest);
	Response<_tds__GetAccessPolicyResponse> GetAccessPolicy(Request<_tds__GetAccessPolicy> &rRequest);
	Response<_tds__SetAccessPolicyResponse> SetAccessPolicy(Request<_tds__SetAccessPolicy> &rRequest);
	Response<_tds__CreateCertificateResponse> CreateCertificate(Request<_tds__CreateCertificate> &rRequest);
	Response<_tds__GetCertificatesResponse> GetCertificates(Request<_tds__GetCertificates> &rRequest);
	Response<_tds__GetCertificatesStatusResponse> GetCertificatesStatus(Request<_tds__GetCertificatesStatus> &rRequest);
	Response<_tds__SetCertificatesStatusResponse> SetCertificatesStatus(Request<_tds__SetCertificatesStatus> &rRequest);
	Response<_tds__DeleteCertificatesResponse> DeleteCertificates(Request<_tds__DeleteCertificates> &rRequest);
	Response<_tds__GetPkcs10RequestResponse> GetPkcs10Request(Request<_tds__GetPkcs10Request> &rRequest);
	Response<_tds__LoadCertificatesResponse> LoadCertificates(Request<_tds__LoadCertificates> &rRequest);
	Response<_tds__GetClientCertificateModeResponse> GetClientCertificateMode(Request<_tds__GetClientCertificateMode> &rRequest);
	Response<_tds__SetClientCertificateModeResponse> SetClientCertificateMode(Request<_tds__SetClientCertificateMode> &rRequest);
	Response<_tds__GetRelayOutputsResponse> GetRelayOutputs(Request<_tds__GetRelayOutputs> &rRequest);
	Response<_tds__SetRelayOutputSettingsResponse> SetRelayOutputSettings(Request<_tds__SetRelayOutputSettings> &rRequest);
	Response<_tds__SetRelayOutputStateResponse> SetRelayOutputState(Request<_tds__SetRelayOutputState> &rRequest);
	Response<_tds__SendAuxiliaryCommandResponse> SendAuxiliaryCommand(Request<_tds__SendAuxiliaryCommand> &rRequest);
	Response<_tds__GetCACertificatesResponse> GetCACertificates(Request<_tds__GetCACertificates> &rRequest);
	Response<_tds__LoadCertificateWithPrivateKeyResponse>
	LoadCertificateWithPrivateKey(Request<_tds__LoadCertificateWithPrivateKey> &rRequest);
	Response<_tds__GetCertificateInformationResponse> GetCertificateInformation(Request<_tds__GetCertificateInformation> &rRequest);
	Response<_tds__LoadCACertificatesResponse> LoadCACertificates(Request<_tds__LoadCACertificates> &rRequest);
	Response<_tds__CreateDot1XConfigurationResponse> CreateDot1XConfiguration(Request<_tds__CreateDot1XConfiguration> &rRequest);
	Response<_tds__SetDot1XConfigurationResponse> SetDot1XConfiguration(Request<_tds__SetDot1XConfiguration> &rRequest);
	Response<_tds__GetDot1XConfigurationResponse> GetDot1XConfiguration(Request<_tds__GetDot1XConfiguration> &rRequest);
	Response<_tds__GetDot1XConfigurationsResponse> GetDot1XConfigurations(Request<_tds__GetDot1XConfigurations> &rRequest);
	Response<_tds__DeleteDot1XConfigurationResponse> DeleteDot1XConfiguration(Request<_tds__DeleteDot1XConfiguration> &rRequest);
	Response<_tds__GetDot11CapabilitiesResponse> GetDot11Capabilities(Request<_tds__GetDot11Capabilities> &rRequest);
	Response<_tds__GetDot11StatusResponse> GetDot11Status(Request<_tds__GetDot11Status> &rRequest);
	Response<_tds__ScanAvailableDot11NetworksResponse> ScanAvailableDot11Networks(Request<_tds__ScanAvailableDot11Networks> &rRequest);
	Response<_tds__GetSystemUrisResponse> GetSystemUris(Request<_tds__GetSystemUris> &rRequest);
	Response<_tds__StartFirmwareUpgradeResponse> StartFirmwareUpgrade(Request<_tds__StartFirmwareUpgrade> &rRequest);
	Response<_tds__StartSystemRestoreResponse> StartSystemRestore(Request<_tds__StartSystemRestore> &rRequest);
	Response<_tds__GetStorageConfigurationsResponse> GetStorageConfigurations(Request<_tds__GetStorageConfigurations> &rRequest);
	Response<_tds__CreateStorageConfigurationResponse> CreateStorageConfiguration(Request<_tds__CreateStorageConfiguration> &rRequest);
	Response<_tds__GetStorageConfigurationResponse> GetStorageConfiguration(Request<_tds__GetStorageConfiguration> &rRequest);
	Response<_tds__SetStorageConfigurationResponse> SetStorageConfiguration(Request<_tds__SetStorageConfiguration> &rRequest);
	Response<_tds__DeleteStorageConfigurationResponse> DeleteStorageConfiguration(Request<_tds__DeleteStorageConfiguration> &rRequest);
	Response<_tds__GetGeoLocationResponse> GetGeoLocation(Request<_tds__GetGeoLocation> &rRequest);
	Response<_tds__SetGeoLocationResponse> SetGeoLocation(Request<_tds__SetGeoLocation> &rRequest);
	Response<_tds__DeleteGeoLocationResponse> DeleteGeoLocation(Request<_tds__DeleteGeoLocation> &rRequest);

private:
	Q_DISABLE_COPY(OnvifDeviceClient);

	OnvifDeviceClientPrivate *mpD;
};
