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
#include <QDebug>
#include <string>


static SoapCtx ctx;

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
		topic.PopulateItems((tt__MessageDescription*)messageDescrChild->get_node(SOAP_TYPE_tt__MessageDescription));
		mTopics.push_back(topic);
	}
	else if(isTopicAttr && isTopicAttr->is_true()) {
		topicPath.append(QString::fromUtf8(pDom->tag()));
		for(xsd__anyType::iterator it = pDom->elt_begin(); it != pDom->elt_end(); ++it) {
			fromDom(it.iter, topicPath);
		}
	}
}

int TopicSet::GetTypeId(const QString &rQName) {

	// TODO: Very hacky! Is there a better option?
	QString typeStr = rQName;
	ctx.EnableModeFlags(SOAP_XML_IGNORENS);
	auto pSoap = ctx.Acquire();
	auto peekBackup = pSoap->peeked;
	auto otherBackup = pSoap->other;
	//char typeBackup[SOAP_TAGLEN];
	//char tagBackup[SOAP_TAGLEN];
	//strcpy(typeBackup, pSoap->type);
	//strcpy(tagBackup, pSoap->tag);
	pSoap->peeked = true;
	pSoap->other = 1;
	pSoap->type[0] = '\0';
	strcpy(pSoap->tag, qPrintable(typeStr));
	int type = 0;
	soap_getelement(pSoap, &type);
	pSoap->peeked = peekBackup;
	pSoap->other = otherBackup;
	//strcpy(pSoap->type, typeBackup);
	//strcpy(pSoap->tag, tagBackup);
	ctx.Release();
	ctx.DisableIModeFlags(SOAP_XML_IGNORENS);
	return type;
}

void Topic::PopulateItems(const tt__MessageDescription *pMessageDescr) {

	if(pMessageDescr) {
		if(pMessageDescr->Key) {
			for(auto item : pMessageDescr->Key->SimpleItemDescription) {
				auto futureItem = SimpleItemInfo(item.Name, TopicSet::GetTypeId(QString(item.Type.c_str())), QString(item.Type.c_str()), KEY);
				mItems.push_back(futureItem);
			}
		}
		if(pMessageDescr->Source) {
			for(auto item : pMessageDescr->Source->SimpleItemDescription) {
				auto futureItem = SimpleItemInfo(item.Name, TopicSet::GetTypeId(QString(item.Type.c_str())), QString(item.Type.c_str()), SOURCE);
				mItems.push_back(futureItem);
			}
		}
		if(pMessageDescr->Data) {
			for(auto item : pMessageDescr->Data->SimpleItemDescription) {
				auto futureItem = SimpleItemInfo(item.Name, TopicSet::GetTypeId(QString(item.Type.c_str())), QString(item.Type.c_str()), DATA);
				mItems.push_back(futureItem);
			}
		}
	}
	else {
		qWarning() << "Couldn't populate items from empty xml";
	}
}
