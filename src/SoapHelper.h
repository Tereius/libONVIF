#pragma once
#include "OnvifCommonExport.h"
#include <QString>
#include <QUuid>


class ONVIFCOMMON_EXPORT SoapHelper {

public:

	static QString GenerateUuid();
	static QUuid QuuidFromString(const QString &rUuidString);
};