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
#pragma once
#include "global.h"
#include "OnvifEventExport.h"
#include <QVariant>
#include <QString>
#include <QList>
#include <QStringList>


class wstop__TopicSetType;
class tt__MessageDescription;
struct soap_dom_element;
struct soap;


/*!
*
* \brief Details of a simple item
*
*/
class ONVIFEVENT_EXPORT SimpleItemInfo {

	Q_GADGET

		Q_PROPERTY(QString name READ GetName)
		Q_PROPERTY(QString soapType READ GetSoapTypeQname)
		Q_PROPERTY(PrimitiveType type READ GetPrimitiveType)

public:

	enum PrimitiveType {

		PRIMITIVE_UNKNOWN,
		PRIMITIVE_BOOL,
		PRIMITIVE_STRING,
		PRIMITIVE_INTEGER,
		PRIMITIVE_REAL
	};
	Q_ENUM(PrimitiveType)

		enum SimpleItemType {

		NONE,
		KEY,
		DATA,
		SOURCE
	};
	Q_ENUM(SimpleItemType)

		SimpleItemInfo() :
		mName(),
		mSoapTypeQname(),
		mType(NONE),
		mPrimitiveType(PRIMITIVE_UNKNOWN) {
	}

	SimpleItemInfo(const QString &rName, PrimitiveType primType, QString soapTypeQname, SimpleItemType type) :
		mName(rName),
		mSoapTypeQname(soapTypeQname),
		mType(type),
		mPrimitiveType(primType) {
	}

	QString GetName() const { return mName; }
	QString GetSoapTypeQname() const { return mSoapTypeQname; }
	PrimitiveType GetPrimitiveType() const { return mPrimitiveType; }
	void SetPrimitiveType(PrimitiveType type) { mPrimitiveType = type; }

private:

	QString mName;
	QString mSoapTypeQname;
	SimpleItemType mType;
	PrimitiveType mPrimitiveType;
};


/*!
*
* \brief A topic which contains details of its simple items
*
*/
class ONVIFEVENT_EXPORT Topic {

	Q_GADGET
		Q_PROPERTY(QString name READ GetName)
		Q_PROPERTY(QStringList path READ GetTopicPath)
		Q_PROPERTY(QList<SimpleItemInfo> items READ GetItems)

public:

	void PopulateItems(const tt__MessageDescription *pMessageDescr);
	QStringList GetTopicPath() const { return mTopicPath; }
	void SetTopicPath(const QStringList &rTopicPath) { mTopicPath = rTopicPath; }
	QString GetName() const { return mName; }
	void SetName(const QString &rName) { mName = rName; };
	void AppendTopicPath(const QString &rName) { mTopicPath.push_back(rName); }

	const QList<SimpleItemInfo>& GetItems() const { return mItems; }
	void SetItemPrimitiveType(SimpleItemInfo::PrimitiveType type, const QString &rName);
	Q_INVOKABLE SimpleItemInfo GetItemByName(const QString &rName) const;

private:

	static SimpleItemInfo::PrimitiveType GetPrimitiveType(soap *pSoap, const QString &rQname);

	QList<SimpleItemInfo> mItems;
	QStringList mTopicPath;
	QString mName;
};


/*!
 *
 * \brief A topic set holding all topics a devices provides
 *
 */
class ONVIFEVENT_EXPORT TopicSet {

public:

	TopicSet() : mTopics() {}
	static TopicSet FromXml(const wstop__TopicSetType *pTopicSet);
	const QList<Topic>& GetTopics() const { return mTopics; }
	Topic GetTopicByName(const QString &rTopicName) const;

private:
	void fromDom(soap_dom_element *pDom, QString topicPath = QString());

	QList<Topic> mTopics;
};
