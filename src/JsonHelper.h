#pragma once
#include "onvifcommonExport.h"
#include <QJsonObject>


struct soap_dom_element;
struct soap_dom_attribute;

class ONVIFCOMMON_EXPORT JsonHelper {

public:
	JsonHelper();
	virtual ~JsonHelper();
	static QJsonObject Parse(struct soap_dom_element *pDomElement);
	static void Parse(QJsonObject &rJson, struct soap_dom_element *pDomElement);
	static void Parse(QJsonObject &rJson, struct soap_dom_attribute *pDomAttribute);
};