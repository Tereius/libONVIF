#pragma once
#include "soapH.h"
#include <QObject>


class GetServicesResponse : public _tds__GetServicesResponse, public QObject {

	Q_OBJECT;
	Q_PROPERTY(std::vector<tds__Service *> service MEMBER Service);
};

Q_DECLARE_METATYPE(GetServicesResponse)
Q_DECLARE_METATYPE(std::vector<tds__Service *>)