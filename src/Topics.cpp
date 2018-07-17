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
#include "Topics.h"
#include "soapStub.h"
#include "SoapCtx.h"
#include "GsoapResolver.h"
#include <QDebug>
#include <string>


TopicSet TopicSet::FromXml(const wstop__TopicSetType *pTopicSet) {

	TopicSet ret;
	if(pTopicSet) {
		for(auto topic : pTopicSet->__any) {
			if(topic) {
				ret.fromDom(topic);
			}
			else {
				qDebug() << "Empty topic -> Skipping";
			}
		}
	}
	else {
		qWarning() << "Couldn't initialize Topic Set from empty xml";
	}
	return ret;
}

Topic TopicSet::GetTopicByName(const QString &rTopicName) const {

	for(auto topic : mTopics) {
		if(topic.GetName() == rTopicName) {
			return topic;
		}
	}
	return Topic();
}

void TopicSet::fromDom(soap_dom_element *pDom, QString topicPath /*= QString()*/) {

	topicPath.append("/");
	auto isTopicAttr = pDom->att_get("wstop:topic");
	auto isPropertyAttr = pDom->att_get("IsProperty");
	auto messageDescrChild = pDom->elt_get("tt:MessageDescription");
	if(messageDescrChild && isTopicAttr && isTopicAttr->is_true()) {
		// Leaf topic node
		Topic topic;
		topic.SetName(QString::fromUtf8(pDom->tag()));
		topic.SetTopicPath(topicPath.split("/", QString::SkipEmptyParts));
		auto pMessageDescr = (tt__MessageDescription*)messageDescrChild->get_node(SOAP_TYPE_tt__MessageDescription);
		pMessageDescr->soap = pDom->soap;
		topic.PopulateItems(pMessageDescr);
		mTopics.push_back(topic);
	}
	else if(isTopicAttr && isTopicAttr->is_true()) {
		topicPath.append(QString::fromUtf8(pDom->tag()));
		for(xsd__anyType::iterator it = pDom->elt_begin(); it != pDom->elt_end(); ++it) {
			fromDom(it.iter, topicPath);
		}
	}
}

void Topic::PopulateItems(const tt__MessageDescription *pMessageDescr) {

	if(pMessageDescr) {
		if(pMessageDescr->Key) {
			for(auto item : pMessageDescr->Key->SimpleItemDescription) {
				auto futureItem = SimpleItemInfo(item.Name, GetPrimitiveType(pMessageDescr->soap, QString::fromLocal8Bit(item.Type.c_str())), QString(item.Type.c_str()), SimpleItemInfo::KEY);
				mItems.push_back(futureItem);
			}
		}
		if(pMessageDescr->Source) {
			for(auto item : pMessageDescr->Source->SimpleItemDescription) {
				auto futureItem = SimpleItemInfo(item.Name, GetPrimitiveType(pMessageDescr->soap, QString::fromLocal8Bit(item.Type.c_str())), QString(item.Type.c_str()), SimpleItemInfo::SOURCE);
				mItems.push_back(futureItem);
			}
		}
		if(pMessageDescr->Data) {
			for(auto item : pMessageDescr->Data->SimpleItemDescription) {
				auto futureItem = SimpleItemInfo(item.Name, GetPrimitiveType(pMessageDescr->soap, QString::fromLocal8Bit(item.Type.c_str())), QString(item.Type.c_str()), SimpleItemInfo::DATA);
				mItems.push_back(futureItem);
			}
		}
	}
	else {
		qWarning() << "Couldn't populate items from empty xml";
	}
}

void Topic::SetItemPrimitiveType(SimpleItemInfo::PrimitiveType type, const QString &rName) {
	for(auto &item : mItems) {
		if(item.GetName() == rName) {
			return item.SetPrimitiveType(type);
			break;
		}
	}
}

SimpleItemInfo Topic::GetItemByName(const QString &rName) const {
	for(auto item : mItems) {
		if(item.GetName() == rName) {
			return item;
		}
	}
	return SimpleItemInfo();
}

SimpleItemInfo::PrimitiveType Topic::GetPrimitiveType(soap *pSoap, const QString &rQname) {

	if(pSoap) {
		auto test = soap_lookup_ns(pSoap, qPrintable(rQname), rQname.indexOf(':'));
		if(test) {

			auto qName = rQname;
			if(test->ns) {
				// The prefixes don't match. Find the prefix by namespace
				auto prefix = SoapCtx::GetPrefix(QString::fromLocal8Bit(test->ns));
				qName.replace(0, qName.indexOf(':'), prefix);
			}

			if(GsoapResolver::isStringDerived(qName)) {
				return SimpleItemInfo::PRIMITIVE_STRING;
			}
			else if(qName == "xsd:boolean") {
				return SimpleItemInfo::PRIMITIVE_BOOL;
			}
			else if(qName == "xsd:integer"
							|| qName == "xsd:nonNegativeInteger"
							|| qName == "xsd:nonPositiveInteger"
							|| qName == "xsd:positiveInteger"
							|| qName == "xsd:negativeInteger") {
				return SimpleItemInfo::PRIMITIVE_INTEGER;
			}
			else if(qName == "xsd:decimal") {
				return SimpleItemInfo::PRIMITIVE_REAL;
			}
		}
	}
	return SimpleItemInfo::PRIMITIVE_UNKNOWN;
}

