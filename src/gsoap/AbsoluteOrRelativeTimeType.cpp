#include "soapH.h"
#include <QDebug>


SOAP_FMAC1 void SOAP_FMAC2 soap_default_wsnt__AbsoluteOrRelativeTimeType(struct soap *soap, AbsoluteOrRelativeTime *aorTime) {

	(void)soap; /* appease -Wall -Werror */
	*aorTime = AbsoluteOrRelativeTime();
}

SOAP_FMAC1 void SOAP_FMAC2 soap_serialize_wsnt__AbsoluteOrRelativeTimeType(struct soap *soap, const AbsoluteOrRelativeTime *aorTime) {

	(void)soap; (void)aorTime; /* appease -Wall -Werror */
}

SOAP_FMAC3S const char* SOAP_FMAC4S soap_wsnt__AbsoluteOrRelativeTimeType2s(struct soap *soap, AbsoluteOrRelativeTime aorTime) {

	if(aorTime.IsDateTime()) {
		return soap_xsd__dateTime2s(soap, aorTime.GetDateTime());
	}
	else {
		return soap_xsd__duration2s(soap, aorTime.GetDuration());
	}
	return nullptr;
}

SOAP_FMAC1 int SOAP_FMAC2 soap_out_wsnt__AbsoluteOrRelativeTimeType(struct soap *soap, const char *tag /*tev:InitialTerminationTime*/, int id /*0*/, const AbsoluteOrRelativeTime *aorTime, const char *type) {

	if(aorTime->IsDateTime()) {
		return soap_out_xsd__dateTime(soap, tag, id, &aorTime->GetDateTime(), type);
	}
	else {
		return soap_out_xsd__duration(soap, tag, id, &aorTime->GetDuration(), type);
	}
	return SOAP_TYPE;
}

SOAP_FMAC3S int SOAP_FMAC4S soap_s2wsnt__AbsoluteOrRelativeTimeType(struct soap *soap, const char *string, AbsoluteOrRelativeTime *aorTime) {

	(void)soap; (void)string; (void)aorTime; /* appease -Wall -Werror */
	qCritical() << "Deserialization of AbsoluteOrRelativeTimeType not implemented";
	return SOAP_TYPE;
}

SOAP_FMAC1 AbsoluteOrRelativeTime * SOAP_FMAC2 soap_in_wsnt__AbsoluteOrRelativeTimeType(struct soap *soap, const char *tag, AbsoluteOrRelativeTime *aorTime, const char *type) {

	(void)soap; (void)tag; (void)aorTime; (void)type; /* appease -Wall -Werror */
	qCritical() << "Deserialization of AbsoluteOrRelativeTimeType not implemented";
	return nullptr;
}
