#pragma once


class GsoapResolver {
public:
	static bool isStringDerived(const QString &rQname) {
		if(rQname.isEmpty()) return false;
		else if(rQname == "_xml:lang") return true;
		else if(rQname == "tds:EAPMethodTypes") return true;
		else if(rQname == "tr2:EncodingTypes") return true;
		else if(rQname == "trc:EncodingTypes") return true;
		else if(rQname == "trt:EncodingTypes") return true;
		else if(rQname == "tt:AudioClassType") return true;
		else if(rQname == "tt:AuxiliaryData") return true;
		else if(rQname == "tt:Description") return true;
		else if(rQname == "tt:Dot11PSKPassphrase") return true;
		else if(rQname == "tt:FloatAttrList") return true;
		else if(rQname == "tt:IntAttrList") return true;
		else if(rQname == "tt:Name") return true;
		else if(rQname == "tt:RecordingJobMode") return true;
		else if(rQname == "tt:RecordingJobState") return true;
		else if(rQname == "tt:ReferenceToken") return true;
		else if(rQname == "tt:JobToken") return true;
		else if(rQname == "tt:ReceiverReference") return true;
		else if(rQname == "tt:RecordingJobReference") return true;
		else if(rQname == "tt:RecordingReference") return true;
		else if(rQname == "tt:TrackReference") return true;
		else if(rQname == "tt:ReferenceTokenList") return true;
		else if(rQname == "tt:StringAttrList") return true;
		else if(rQname == "tt:StringList") return true;
		else if(rQname == "tt:XPathExpression") return true;
		else if(rQname == "xsd:NCName") return true;
		else if(rQname == "xsd:anySimpleType") return true;
		else if(rQname == "xsd:anyURI") return true;
		else if(rQname == "xsd:token") return true;
		else if(rQname == "tt:DNSName") return true;
		else if(rQname == "tt:Domain") return true;
		else if(rQname == "tt:HwAddress") return true;
		else if(rQname == "tt:IPv4Address") return true;
		else if(rQname == "tt:IPv6Address") return true;
		else if(rQname == "wstop:ConcreteTopicExpression") return true;
		else if(rQname == "wstop:FullTopicExpression") return true;
		else return false;
	}
};
