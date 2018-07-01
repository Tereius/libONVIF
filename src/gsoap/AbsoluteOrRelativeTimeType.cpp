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
		auto val = (LONG64)aorTime->GetDuration();
		return soap_out_xsd__duration(soap, tag, id, &val, type);
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
