#include "SoapHelper.h"
#include <QUuid>


QString SoapHelper::GenerateUuid() {

	return QUuid::createUuid().toString().mid(1, 36);
}
