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
#include <QVariant>
#include <QString>
#include <QList>
#include <QStringList>
#include "OnvifEventExport.h"


class wstop__TopicSetType;
class tt__MessageDescription;
struct soap_dom_element;

enum SimpleItemType {

	NONE,
	KEY,
	DATA,
	SOURCE
};


class SimpleItem {

	Q_GADGET
		Q_PROPERTY(QString name READ GetName)
		Q_PROPERTY(QVariant value READ GetValue)
		Q_PROPERTY(SimpleItemType type READ GetType)

public:

	SimpleItem() :
		mType(NONE),
		mName(),
		mValue() {
	}

	SimpleItem(const QString &rName, const QVariant &rValue, SimpleItemType type) :
		mType(type),
		mName(rName),
		mValue(rValue) {
	}

	QString GetName() const { return mName; }
	void SetName(const QString &rName) { mName = rName; }
	QVariant GetValue() const { return mValue; }
	void SetValue(const QVariant &rValue) { mValue = rValue; }
	SimpleItemType GetType() const { return mType; }
	void SetType(SimpleItemType type) { mType = type; }
	bool IsValid() const { return mType != NONE; }

private:

	SimpleItemType mType;
	QString mName;
	QVariant mValue;
};


class ONVIFEVENT_EXPORT SimpleItemInfo {

public:

	SimpleItemInfo() :
		mName(),
		mSoapType(),
		mSoapTypeQname(),
		mType(NONE) {
	}

	SimpleItemInfo(const QString &rName, int soapType, QString soapTypeQname, SimpleItemType type) :
		mName(rName),
		mSoapType(soapType),
		mSoapTypeQname(soapTypeQname),
		mType(type) {
	}

	QString GetName() const { return mName; }
	QString GetSoapTypeQname() const { return mSoapTypeQname; }
	int GetType() const { return mSoapType; }

private:

	const QString mName;
	const int mSoapType;
	const QString mSoapTypeQname;
	const SimpleItemType mType;
};


class ONVIFEVENT_EXPORT Topic {

	Q_GADGET

public:

	void PopulateItems(const tt__MessageDescription *pMessageDescr);
	QStringList GetTopicPath() const { return mTopicPath; }
	void SetTopicPath(const QStringList &rTopicPath) { mTopicPath = rTopicPath; }
	QString GetName() const { return mName; }
	void SetName(const QString &rName) { mName = rName; };
	void AppendTopicPath(const QString &rName) { mTopicPath.push_back(rName); }

	QList<SimpleItemInfo> GetItems() const { return mItems; }
	SimpleItemInfo GetItemByName(const QString &rName) const {

		for(auto item : mItems) {
			if(item.GetName() == rName) {
				return item;
			}
		}
		return SimpleItemInfo();
	}

private:

	QList<SimpleItemInfo> mItems;
	QStringList mTopicPath;
	QString mName;
};


class ONVIFEVENT_EXPORT TopicSet {

public:

	TopicSet() : mTopics() {}
	static TopicSet FromXml(const wstop__TopicSetType *pTopicSet);
	static int GetTypeId(const QString &rQName);
	QList<Topic> GetTopics() const { return mTopics; }

private:
	void fromDom(soap_dom_element *pDom, QString topicPath = QString());

	QList<Topic> mTopics;
};
