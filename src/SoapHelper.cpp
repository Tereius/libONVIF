#include "SoapHelper.h"
#include <QUuid>


QString SoapHelper::GenerateUuid() {

	return QUuid::createUuid().toString().mid(1, 36);
}

QUuid SoapHelper::QuuidFromString(const QString &rUuidString) {

	auto proposedUuid = rUuidString.right(36);
	return QUuid(proposedUuid);
}
