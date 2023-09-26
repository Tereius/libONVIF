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
#include "OnvifDiscoveryExport.h"
#include "global.h"
#include <QMetaType>
#include <QStringList>
#include <QUrl>
#include <QUuid>


/*!
 *
 * \brief DTO representing a discovery match
 *
 */
class ONVIFDISCOVERY_EXPORT DiscoveryMatch {

 public:
	DiscoveryMatch();
	virtual ~DiscoveryMatch();

	QList<QUrl> GetDeviceEndpoints() const;
	void SetDeviceEndpoints(const QList<QUrl> &rDeviceEndpoint);
	QStringList GetTypes() const;
	void SetTypes(const QStringList &rTypes);
	QStringList GetScopes() const; // Can be url/percent encoded
	void SetScopes(const QStringList &rScopes);
	QUuid GetEndpointReference() const;
	void SetEndpointReference(const QUuid &rReference);
	bool operator==(const DiscoveryMatch &rOther) const;
	bool operator!=(const DiscoveryMatch &rOther) const;

 private:
	QList<QUrl> mDeviceEndpoints;
	QStringList mTypes;
	QStringList mScopes;
	QUuid mEndpointReference;
};

REGISTER_METATYPE(DiscoveryMatch)
