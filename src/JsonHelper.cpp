#include "JsonHelper.h"
#include "stdsoap2.h"
#include "soapStub.h"
#include <QVariant>
#include <QDebug>


JsonHelper::JsonHelper() {

}

JsonHelper::~JsonHelper() {

}

void JsonHelper::Parse(QJsonObject &rJson, struct soap_dom_element *pDomElement) {

	auto tag = QString::fromUtf8(pDomElement->tag());
	auto ns = QString::fromUtf8(pDomElement->ns());
	qDebug() << "Found tag: " << tag << " ns: " << ns;
	for(auto attr = pDomElement->att_begin(); attr != pDomElement->att_end(); attr++) {
		Parse(rJson, attr.iter);
	}
	if(pDomElement->elt_size() == 0) {
		qDebug() << "Its a leaf";
		switch(pDomElement->type) {
			case SOAP_TYPE_xsd__dateTime:
				rJson.insert(tag, QJsonValue::fromVariant(*(xsd__dateTime*)pDomElement->node));
				break;
			case SOAP_TYPE_xsd__duration:
				rJson.insert(tag, QJsonValue::fromVariant(*(xsd__duration*)pDomElement->node));
				break;
			case SOAP_TYPE_xsd__double:
				rJson.insert(tag, QJsonValue::fromVariant(QString(*(xsd__double*)pDomElement->node).toDouble()));
				break;
			case SOAP_TYPE_xsd__integer:
			case SOAP_TYPE_tt__NetworkInterfaceConfigPriority:
				rJson.insert(tag, QJsonValue::fromVariant(QString(*(xsd__integer*)pDomElement->node).toLongLong()));
				break;
			case SOAP_TYPE_xsd__nonNegativeInteger:
				rJson.insert(tag, QJsonValue::fromVariant(QString(*(xsd__nonNegativeInteger*)pDomElement->node).toULongLong()));
				break;
			case SOAP_TYPE_xsd__string:
			case SOAP_TYPE_xsd__NCName:
			case SOAP_TYPE_xsd__anySimpleType:
			case SOAP_TYPE_xsd__anyURI:
			case SOAP_TYPE_xsd__token:
			case SOAP_TYPE__xml__lang:
			case SOAP_TYPE_tt__IntAttrList:
			case SOAP_TYPE_tt__FloatAttrList:
			case SOAP_TYPE_tt__StringAttrList:
			case SOAP_TYPE_tt__ReferenceTokenList:
			case SOAP_TYPE_trc__EncodingTypes:
			case SOAP_TYPE_trt__EncodingTypes:
			case SOAP_TYPE_tds__EAPMethodTypes:
			case SOAP_TYPE_tt__ReferenceToken:
			case SOAP_TYPE_tt__Name:
			case SOAP_TYPE_tt__IPv4Address:
			case SOAP_TYPE_tt__IPv6Address:
			case SOAP_TYPE_tt__HwAddress:
			case SOAP_TYPE_tt__DNSName:
			case SOAP_TYPE_tt__Domain:
				rJson.insert(tag, QJsonValue::fromVariant(*(xsd__string*)pDomElement->node));
				break;
			case SOAP_TYPE_wsnt__AbsoluteOrRelativeTimeType:
				rJson.insert(tag, QJsonObject{
					{"dateTime", ((wsnt__AbsoluteOrRelativeTimeType*)pDomElement->node)->IsDateTime() ? QJsonValue::fromVariant(((wsnt__AbsoluteOrRelativeTimeType*)pDomElement->node)->GetDateTime()) : QJsonValue(QJsonValue::Null)},
					{"duration", ((wsnt__AbsoluteOrRelativeTimeType*)pDomElement->node)->IsDuration() ? QJsonValue::fromVariant(((wsnt__AbsoluteOrRelativeTimeType*)pDomElement->node)->GetDuration()) : QJsonValue(QJsonValue::Null)}
				});
				break;
			case SOAP_TYPE_xsd__QName:
				rJson.insert(tag, QJsonValue::fromVariant(QString::fromStdString(*(xsd__QName*)pDomElement->node)));
				break;
			default:
				if(pDomElement->text) {
					rJson.insert(tag, QJsonValue::fromVariant(QString::fromUtf8(pDomElement->text)));
				}
				else {
					rJson.insert(tag, QJsonValue(QJsonValue::Null));
				}
				break;
		}
	}
	else {
		for(auto child = pDomElement->elt_begin(); child != pDomElement->elt_end(); child++) {
			auto jsonChild = QJsonObject();
			rJson.insert(tag, jsonChild);
			Parse(jsonChild, child.iter);
		}
	}
}

void JsonHelper::Parse(QJsonObject &rJson, struct soap_dom_attribute *pDomAttribute) {

	auto tag = QString::fromUtf8(pDomAttribute->tag());
	auto ns = QString::fromUtf8(pDomAttribute->ns());
	qDebug() << "Found attribute: " << tag << " ns: " << ns;
	if(pDomAttribute->get_text()) {
		auto value = QString::fromUtf8(pDomAttribute->get_text());
		auto valid = false;
		auto result = value.toDouble(&valid);
		if(valid) {
			rJson.insert(tag, result);
		}
		else if(value.compare("true") == 0) {
			rJson.insert(tag, true);
		}
		else if(value.compare("false") == 0) {
			rJson.insert(tag, false);
		}
		else {
			rJson.insert(tag, value);
		}
	}
	else {
		rJson.insert(tag, QJsonValue(QJsonValue::Null));
	}
}

QJsonObject JsonHelper::Parse(struct soap_dom_element *pDomElement) {

	auto root = QJsonObject();
	Parse(root, pDomElement);
	return root;
}
