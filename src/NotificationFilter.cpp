#include "NotificationFilter.h"


QString Filter::Attr::Val::toString() const {

	return QString("@Value=\"%1\"").arg(mVal.toString());
}

QString Filter::Attr::And::toString() const {

	QStringList strList;
	for(auto str : mExList)
		strList.push_back(str->toString());
	return strList.join(QString(" and ")).prepend("(").append(")");
}

QString Filter::Attr::Or::toString() const {

	QStringList strList;
	for(auto str : mExList)
		strList.push_back(str->toString());
	return strList.join(QString(" or ")).prepend("(").append(")");
}

QString Filter::Attr::Not::toString() const {

	return QString("not(%1)").arg(mEx->toString());
}

QString Filter::SimpleItem::toString() const {

	auto ret = QString("//tt:SimpleItem[@Name=\"%1\"").arg(mName);
	if(mEx) {
		ret.append(QString(" and (%1)").arg(mEx->toString()));
	}
	ret.append("]");
	return ret;
}

QString Filter::BoolExpr::toString() const {

	return QString("boolean(%1)").arg(mItem->toString());
}

QString Filter::And::toString() const {

	QStringList strList;
	for(auto str : mExList)
		strList.push_back(str->toString());
	return strList.join(QString(" and ")).prepend("(").append(")");
}

QString Filter::Or::toString() const {

	QStringList strList;
	for(auto str : mExList)
		strList.push_back(str->toString());
	return strList.join(QString(" or ")).prepend("(").append(")");
}

QString Filter::Not::toString() const {

	return QString("not(%1)").arg(mEx->toString());
}
