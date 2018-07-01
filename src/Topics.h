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
		mType(NONE) {
	}

	SimpleItemInfo(const QString &rName, int soapType, SimpleItemType type) :
		mName(rName),
		mSoapType(soapType),
		mType(type) {
	}

	QString GetName() const { return mName; }
	int GetType() const { return mSoapType; }

private:

	const QString mName;
	const int mSoapType;
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

private:
	void fromDom(soap_dom_element *pDom, QString topicPath = QString());

	QList<Topic> mTopics;
};
