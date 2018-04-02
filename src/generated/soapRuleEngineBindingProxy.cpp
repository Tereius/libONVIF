/* soapRuleEngineBindingProxy.cpp
   Generated by gSOAP 2.8.55 for rcx.h

gSOAP XML Web services tools
Copyright (C) 2000-2017, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapRuleEngineBindingProxy.h"

RuleEngineBindingProxy::RuleEngineBindingProxy()
{	this->soap = soap_new();
	this->soap_own = true;
	RuleEngineBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

RuleEngineBindingProxy::RuleEngineBindingProxy(const RuleEngineBindingProxy& rhs)
{	this->soap = rhs.soap;
	this->soap_own = false;
	this->soap_endpoint = rhs.soap_endpoint;
}

RuleEngineBindingProxy::RuleEngineBindingProxy(struct soap *_soap)
{	this->soap = _soap;
	this->soap_own = false;
	RuleEngineBindingProxy_init(_soap->imode, _soap->omode);
}

RuleEngineBindingProxy::RuleEngineBindingProxy(const char *endpoint)
{	this->soap = soap_new();
	this->soap_own = true;
	RuleEngineBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = endpoint;
}

RuleEngineBindingProxy::RuleEngineBindingProxy(soap_mode iomode)
{	this->soap = soap_new();
	this->soap_own = true;
	RuleEngineBindingProxy_init(iomode, iomode);
}

RuleEngineBindingProxy::RuleEngineBindingProxy(const char *endpoint, soap_mode iomode)
{	this->soap = soap_new();
	this->soap_own = true;
	RuleEngineBindingProxy_init(iomode, iomode);
	soap_endpoint = endpoint;
}

RuleEngineBindingProxy::RuleEngineBindingProxy(soap_mode imode, soap_mode omode)
{	this->soap = soap_new();
	this->soap_own = true;
	RuleEngineBindingProxy_init(imode, omode);
}

RuleEngineBindingProxy::~RuleEngineBindingProxy()
{	if (this->soap_own)
		soap_free(this->soap);
}

void RuleEngineBindingProxy::RuleEngineBindingProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this->soap, imode);
	soap_omode(this->soap, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] = {
        {"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", NULL},
        {"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/", NULL},
        {"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
        {"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
        {"c14n", "http://www.w3.org/2001/10/xml-exc-c14n#", NULL, NULL},
        {"ds", "http://www.w3.org/2000/09/xmldsig#", NULL, NULL},
        {"saml1", "urn:oasis:names:tc:SAML:1.0:assertion", NULL, NULL},
        {"saml2", "urn:oasis:names:tc:SAML:2.0:assertion", NULL, NULL},
        {"wsu", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd", NULL, NULL},
        {"xenc", "http://www.w3.org/2001/04/xmlenc#", NULL, NULL},
        {"wsc", "http://docs.oasis-open.org/ws-sx/ws-secureconversation/200512", NULL, NULL},
        {"wsse", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd", "http://docs.oasis-open.org/wss/oasis-wss-wssecurity-secext-1.1.xsd", NULL},
        {"chan", "http://schemas.microsoft.com/ws/2005/02/duplex", NULL, NULL},
        {"wsa5", "http://www.w3.org/2005/08/addressing", "http://schemas.xmlsoap.org/ws/2004/08/addressing", NULL},
        {"wsdd", "http://schemas.xmlsoap.org/ws/2005/04/discovery", NULL, NULL},
        {"wsrfr", "http://docs.oasis-open.org/wsrf/r-2", NULL, NULL},
        {"xmime", "http://tempuri.org/xmime.xsd", NULL, NULL},
        {"xop", "http://www.w3.org/2004/08/xop/include", NULL, NULL},
        {"tt", "http://www.onvif.org/ver10/schema", NULL, NULL},
        {"wsrfbf", "http://docs.oasis-open.org/wsrf/bf-2", NULL, NULL},
        {"wstop", "http://docs.oasis-open.org/wsn/t-1", NULL, NULL},
        {"tad", "http://www.onvif.org/ver10/analyticsdevice/wsdl", NULL, NULL},
        {"tan", "http://www.onvif.org/ver20/analytics/wsdl", NULL, NULL},
        {"tds", "http://www.onvif.org/ver10/device/wsdl", NULL, NULL},
        {"tev", "http://www.onvif.org/ver10/events/wsdl", NULL, NULL},
        {"wsnt", "http://docs.oasis-open.org/wsn/b-2", NULL, NULL},
        {"timg", "http://www.onvif.org/ver20/imaging/wsdl", NULL, NULL},
        {"tls", "http://www.onvif.org/ver10/display/wsdl", NULL, NULL},
        {"tptz", "http://www.onvif.org/ver20/ptz/wsdl", NULL, NULL},
        {"trc", "http://www.onvif.org/ver10/recording/wsdl", NULL, NULL},
        {"trp", "http://www.onvif.org/ver10/replay/wsdl", NULL, NULL},
        {"trt", "http://www.onvif.org/ver10/media/wsdl", NULL, NULL},
        {"trv", "http://www.onvif.org/ver10/receiver/wsdl", NULL, NULL},
        {"tse", "http://www.onvif.org/ver10/search/wsdl", NULL, NULL},
        {NULL, NULL, NULL, NULL}
    };
	soap_set_namespaces(this->soap, namespaces);
}

RuleEngineBindingProxy *RuleEngineBindingProxy::copy()
{	RuleEngineBindingProxy *dup = SOAP_NEW_COPY(RuleEngineBindingProxy);
	if (dup)
		soap_copy_context(dup->soap, this->soap);
	return dup;
}

RuleEngineBindingProxy& RuleEngineBindingProxy::operator=(const RuleEngineBindingProxy& rhs)
{	if (this->soap != rhs.soap)
	{	if (this->soap_own)
			soap_free(this->soap);
		this->soap = rhs.soap;
		this->soap_own = false;
		this->soap_endpoint = rhs.soap_endpoint;
	}
	return *this;
}

void RuleEngineBindingProxy::destroy()
{	soap_destroy(this->soap);
	soap_end(this->soap);
}

void RuleEngineBindingProxy::reset()
{	this->destroy();
	soap_done(this->soap);
	soap_initialize(this->soap);
	RuleEngineBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

void RuleEngineBindingProxy::soap_noheader()
{	this->soap->header = NULL;
}

void RuleEngineBindingProxy::soap_header(struct _wsse__Security *wsse__Security, char *wsa5__MessageID, struct wsa5__RelatesToType *wsa5__RelatesTo, struct wsa5__EndpointReferenceType *wsa5__From, struct wsa5__EndpointReferenceType *wsa5__ReplyTo, struct wsa5__EndpointReferenceType *wsa5__FaultTo, char *wsa5__To, char *wsa5__Action, struct chan__ChannelInstanceType *chan__ChannelInstance, struct wsdd__AppSequenceType *wsdd__AppSequence)
{	::soap_header(this->soap);
	this->soap->header->wsse__Security = wsse__Security;
	this->soap->header->wsa5__MessageID = wsa5__MessageID;
	this->soap->header->wsa5__RelatesTo = wsa5__RelatesTo;
	this->soap->header->wsa5__From = wsa5__From;
	this->soap->header->wsa5__ReplyTo = wsa5__ReplyTo;
	this->soap->header->wsa5__FaultTo = wsa5__FaultTo;
	this->soap->header->wsa5__To = wsa5__To;
	this->soap->header->wsa5__Action = wsa5__Action;
	this->soap->header->chan__ChannelInstance = chan__ChannelInstance;
	this->soap->header->wsdd__AppSequence = wsdd__AppSequence;
}

::SOAP_ENV__Header *RuleEngineBindingProxy::soap_header()
{	return this->soap->header;
}

::SOAP_ENV__Fault *RuleEngineBindingProxy::soap_fault()
{	return this->soap->fault;
}

const char *RuleEngineBindingProxy::soap_fault_string()
{	return *soap_faultstring(this->soap);
}

const char *RuleEngineBindingProxy::soap_fault_detail()
{	return *soap_faultdetail(this->soap);
}

int RuleEngineBindingProxy::soap_close_socket()
{	return soap_closesock(this->soap);
}

int RuleEngineBindingProxy::soap_force_close_socket()
{	return soap_force_closesock(this->soap);
}

void RuleEngineBindingProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this->soap, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void RuleEngineBindingProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this->soap, os);
}
#endif

char *RuleEngineBindingProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this->soap, buf, len);
}
#endif

int RuleEngineBindingProxy::GetSupportedRules(const char *endpoint, const char *soap_action, _tan__GetSupportedRules *tan__GetSupportedRules, _tan__GetSupportedRulesResponse &tan__GetSupportedRulesResponse)
{	struct soap *soap = this->soap;
	struct __tan__GetSupportedRules soap_tmp___tan__GetSupportedRules;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/GetSupportedRules";
	soap_tmp___tan__GetSupportedRules.tan__GetSupportedRules = tan__GetSupportedRules;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__GetSupportedRules(soap, &soap_tmp___tan__GetSupportedRules);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__GetSupportedRules(soap, &soap_tmp___tan__GetSupportedRules, "-tan:GetSupportedRules", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__GetSupportedRules(soap, &soap_tmp___tan__GetSupportedRules, "-tan:GetSupportedRules", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__GetSupportedRulesResponse*>(&tan__GetSupportedRulesResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__GetSupportedRulesResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__GetSupportedRulesResponse.soap_get(soap, "tan:GetSupportedRulesResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::CreateRules(const char *endpoint, const char *soap_action, _tan__CreateRules *tan__CreateRules, _tan__CreateRulesResponse &tan__CreateRulesResponse)
{	struct soap *soap = this->soap;
	struct __tan__CreateRules soap_tmp___tan__CreateRules;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/CreateRules";
	soap_tmp___tan__CreateRules.tan__CreateRules = tan__CreateRules;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__CreateRules(soap, &soap_tmp___tan__CreateRules);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__CreateRules(soap, &soap_tmp___tan__CreateRules, "-tan:CreateRules", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__CreateRules(soap, &soap_tmp___tan__CreateRules, "-tan:CreateRules", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__CreateRulesResponse*>(&tan__CreateRulesResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__CreateRulesResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__CreateRulesResponse.soap_get(soap, "tan:CreateRulesResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::DeleteRules(const char *endpoint, const char *soap_action, _tan__DeleteRules *tan__DeleteRules, _tan__DeleteRulesResponse &tan__DeleteRulesResponse)
{	struct soap *soap = this->soap;
	struct __tan__DeleteRules soap_tmp___tan__DeleteRules;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/DeleteRules";
	soap_tmp___tan__DeleteRules.tan__DeleteRules = tan__DeleteRules;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__DeleteRules(soap, &soap_tmp___tan__DeleteRules);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__DeleteRules(soap, &soap_tmp___tan__DeleteRules, "-tan:DeleteRules", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__DeleteRules(soap, &soap_tmp___tan__DeleteRules, "-tan:DeleteRules", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__DeleteRulesResponse*>(&tan__DeleteRulesResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__DeleteRulesResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__DeleteRulesResponse.soap_get(soap, "tan:DeleteRulesResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::GetRules(const char *endpoint, const char *soap_action, _tan__GetRules *tan__GetRules, _tan__GetRulesResponse &tan__GetRulesResponse)
{	struct soap *soap = this->soap;
	struct __tan__GetRules soap_tmp___tan__GetRules;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/GetRules";
	soap_tmp___tan__GetRules.tan__GetRules = tan__GetRules;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__GetRules(soap, &soap_tmp___tan__GetRules);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__GetRules(soap, &soap_tmp___tan__GetRules, "-tan:GetRules", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__GetRules(soap, &soap_tmp___tan__GetRules, "-tan:GetRules", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__GetRulesResponse*>(&tan__GetRulesResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__GetRulesResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__GetRulesResponse.soap_get(soap, "tan:GetRulesResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::GetRuleOptions(const char *endpoint, const char *soap_action, _tan__GetRuleOptions *tan__GetRuleOptions, _tan__GetRuleOptionsResponse &tan__GetRuleOptionsResponse)
{	struct soap *soap = this->soap;
	struct __tan__GetRuleOptions soap_tmp___tan__GetRuleOptions;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/GetRuleOptions";
	soap_tmp___tan__GetRuleOptions.tan__GetRuleOptions = tan__GetRuleOptions;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__GetRuleOptions(soap, &soap_tmp___tan__GetRuleOptions);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__GetRuleOptions(soap, &soap_tmp___tan__GetRuleOptions, "-tan:GetRuleOptions", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__GetRuleOptions(soap, &soap_tmp___tan__GetRuleOptions, "-tan:GetRuleOptions", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__GetRuleOptionsResponse*>(&tan__GetRuleOptionsResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__GetRuleOptionsResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__GetRuleOptionsResponse.soap_get(soap, "tan:GetRuleOptionsResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::ModifyRules(const char *endpoint, const char *soap_action, _tan__ModifyRules *tan__ModifyRules, _tan__ModifyRulesResponse &tan__ModifyRulesResponse)
{	struct soap *soap = this->soap;
	struct __tan__ModifyRules soap_tmp___tan__ModifyRules;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/ModifyRules";
	soap_tmp___tan__ModifyRules.tan__ModifyRules = tan__ModifyRules;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__ModifyRules(soap, &soap_tmp___tan__ModifyRules);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__ModifyRules(soap, &soap_tmp___tan__ModifyRules, "-tan:ModifyRules", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__ModifyRules(soap, &soap_tmp___tan__ModifyRules, "-tan:ModifyRules", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__ModifyRulesResponse*>(&tan__ModifyRulesResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__ModifyRulesResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__ModifyRulesResponse.soap_get(soap, "tan:ModifyRulesResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::GetServiceCapabilities(const char *endpoint, const char *soap_action, _tan__GetServiceCapabilities *tan__GetServiceCapabilities, _tan__GetServiceCapabilitiesResponse &tan__GetServiceCapabilitiesResponse)
{	struct soap *soap = this->soap;
	struct __tan__GetServiceCapabilities soap_tmp___tan__GetServiceCapabilities;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/GetServiceCapabilities";
	soap_tmp___tan__GetServiceCapabilities.tan__GetServiceCapabilities = tan__GetServiceCapabilities;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__GetServiceCapabilities(soap, &soap_tmp___tan__GetServiceCapabilities);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__GetServiceCapabilities(soap, &soap_tmp___tan__GetServiceCapabilities, "-tan:GetServiceCapabilities", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__GetServiceCapabilities(soap, &soap_tmp___tan__GetServiceCapabilities, "-tan:GetServiceCapabilities", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__GetServiceCapabilitiesResponse*>(&tan__GetServiceCapabilitiesResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__GetServiceCapabilitiesResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__GetServiceCapabilitiesResponse.soap_get(soap, "tan:GetServiceCapabilitiesResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::GetSupportedAnalyticsModules(const char *endpoint, const char *soap_action, _tan__GetSupportedAnalyticsModules *tan__GetSupportedAnalyticsModules, _tan__GetSupportedAnalyticsModulesResponse &tan__GetSupportedAnalyticsModulesResponse)
{	struct soap *soap = this->soap;
	struct __tan__GetSupportedAnalyticsModules soap_tmp___tan__GetSupportedAnalyticsModules;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/GetSupportedAnalyticsModules";
	soap_tmp___tan__GetSupportedAnalyticsModules.tan__GetSupportedAnalyticsModules = tan__GetSupportedAnalyticsModules;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__GetSupportedAnalyticsModules(soap, &soap_tmp___tan__GetSupportedAnalyticsModules);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__GetSupportedAnalyticsModules(soap, &soap_tmp___tan__GetSupportedAnalyticsModules, "-tan:GetSupportedAnalyticsModules", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__GetSupportedAnalyticsModules(soap, &soap_tmp___tan__GetSupportedAnalyticsModules, "-tan:GetSupportedAnalyticsModules", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__GetSupportedAnalyticsModulesResponse*>(&tan__GetSupportedAnalyticsModulesResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__GetSupportedAnalyticsModulesResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__GetSupportedAnalyticsModulesResponse.soap_get(soap, "tan:GetSupportedAnalyticsModulesResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::CreateAnalyticsModules(const char *endpoint, const char *soap_action, _tan__CreateAnalyticsModules *tan__CreateAnalyticsModules, _tan__CreateAnalyticsModulesResponse &tan__CreateAnalyticsModulesResponse)
{	struct soap *soap = this->soap;
	struct __tan__CreateAnalyticsModules soap_tmp___tan__CreateAnalyticsModules;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/CreateAnalyticsModules";
	soap_tmp___tan__CreateAnalyticsModules.tan__CreateAnalyticsModules = tan__CreateAnalyticsModules;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__CreateAnalyticsModules(soap, &soap_tmp___tan__CreateAnalyticsModules);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__CreateAnalyticsModules(soap, &soap_tmp___tan__CreateAnalyticsModules, "-tan:CreateAnalyticsModules", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__CreateAnalyticsModules(soap, &soap_tmp___tan__CreateAnalyticsModules, "-tan:CreateAnalyticsModules", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__CreateAnalyticsModulesResponse*>(&tan__CreateAnalyticsModulesResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__CreateAnalyticsModulesResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__CreateAnalyticsModulesResponse.soap_get(soap, "tan:CreateAnalyticsModulesResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::DeleteAnalyticsModules(const char *endpoint, const char *soap_action, _tan__DeleteAnalyticsModules *tan__DeleteAnalyticsModules, _tan__DeleteAnalyticsModulesResponse &tan__DeleteAnalyticsModulesResponse)
{	struct soap *soap = this->soap;
	struct __tan__DeleteAnalyticsModules soap_tmp___tan__DeleteAnalyticsModules;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/DeleteAnalyticsModules";
	soap_tmp___tan__DeleteAnalyticsModules.tan__DeleteAnalyticsModules = tan__DeleteAnalyticsModules;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__DeleteAnalyticsModules(soap, &soap_tmp___tan__DeleteAnalyticsModules);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__DeleteAnalyticsModules(soap, &soap_tmp___tan__DeleteAnalyticsModules, "-tan:DeleteAnalyticsModules", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__DeleteAnalyticsModules(soap, &soap_tmp___tan__DeleteAnalyticsModules, "-tan:DeleteAnalyticsModules", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__DeleteAnalyticsModulesResponse*>(&tan__DeleteAnalyticsModulesResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__DeleteAnalyticsModulesResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__DeleteAnalyticsModulesResponse.soap_get(soap, "tan:DeleteAnalyticsModulesResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::GetAnalyticsModules(const char *endpoint, const char *soap_action, _tan__GetAnalyticsModules *tan__GetAnalyticsModules, _tan__GetAnalyticsModulesResponse &tan__GetAnalyticsModulesResponse)
{	struct soap *soap = this->soap;
	struct __tan__GetAnalyticsModules soap_tmp___tan__GetAnalyticsModules;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/GetAnalyticsModules";
	soap_tmp___tan__GetAnalyticsModules.tan__GetAnalyticsModules = tan__GetAnalyticsModules;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__GetAnalyticsModules(soap, &soap_tmp___tan__GetAnalyticsModules);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__GetAnalyticsModules(soap, &soap_tmp___tan__GetAnalyticsModules, "-tan:GetAnalyticsModules", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__GetAnalyticsModules(soap, &soap_tmp___tan__GetAnalyticsModules, "-tan:GetAnalyticsModules", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__GetAnalyticsModulesResponse*>(&tan__GetAnalyticsModulesResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__GetAnalyticsModulesResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__GetAnalyticsModulesResponse.soap_get(soap, "tan:GetAnalyticsModulesResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::GetAnalyticsModuleOptions(const char *endpoint, const char *soap_action, _tan__GetAnalyticsModuleOptions *tan__GetAnalyticsModuleOptions, _tan__GetAnalyticsModuleOptionsResponse &tan__GetAnalyticsModuleOptionsResponse)
{	struct soap *soap = this->soap;
	struct __tan__GetAnalyticsModuleOptions soap_tmp___tan__GetAnalyticsModuleOptions;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/GetAnalyticsModuleOptions";
	soap_tmp___tan__GetAnalyticsModuleOptions.tan__GetAnalyticsModuleOptions = tan__GetAnalyticsModuleOptions;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__GetAnalyticsModuleOptions(soap, &soap_tmp___tan__GetAnalyticsModuleOptions);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__GetAnalyticsModuleOptions(soap, &soap_tmp___tan__GetAnalyticsModuleOptions, "-tan:GetAnalyticsModuleOptions", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__GetAnalyticsModuleOptions(soap, &soap_tmp___tan__GetAnalyticsModuleOptions, "-tan:GetAnalyticsModuleOptions", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__GetAnalyticsModuleOptionsResponse*>(&tan__GetAnalyticsModuleOptionsResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__GetAnalyticsModuleOptionsResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__GetAnalyticsModuleOptionsResponse.soap_get(soap, "tan:GetAnalyticsModuleOptionsResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int RuleEngineBindingProxy::ModifyAnalyticsModules(const char *endpoint, const char *soap_action, _tan__ModifyAnalyticsModules *tan__ModifyAnalyticsModules, _tan__ModifyAnalyticsModulesResponse &tan__ModifyAnalyticsModulesResponse)
{	struct soap *soap = this->soap;
	struct __tan__ModifyAnalyticsModules soap_tmp___tan__ModifyAnalyticsModules;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_action == NULL)
		soap_action = "http://www.onvif.org/ver20/analytics/wsdl/ModifyAnalyticsModules";
	soap_tmp___tan__ModifyAnalyticsModules.tan__ModifyAnalyticsModules = tan__ModifyAnalyticsModules;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize___tan__ModifyAnalyticsModules(soap, &soap_tmp___tan__ModifyAnalyticsModules);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___tan__ModifyAnalyticsModules(soap, &soap_tmp___tan__ModifyAnalyticsModules, "-tan:ModifyAnalyticsModules", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___tan__ModifyAnalyticsModules(soap, &soap_tmp___tan__ModifyAnalyticsModules, "-tan:ModifyAnalyticsModules", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<_tan__ModifyAnalyticsModulesResponse*>(&tan__ModifyAnalyticsModulesResponse)) // NULL ref?
		return soap_closesock(soap);
	tan__ModifyAnalyticsModulesResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	tan__ModifyAnalyticsModulesResponse.soap_get(soap, "tan:ModifyAnalyticsModulesResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */
