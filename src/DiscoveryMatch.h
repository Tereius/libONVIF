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
#include <QStringList>
#include <QUrl>
#include <QUuid>
#include <QMetaType>


/*!
 *
 * \brief DTO representing a discovery match
 *
 */
class ONVIFDISCOVERY_EXPORT DiscoveryMatch {

public:
	DiscoveryMatch();
	virtual ~DiscoveryMatch();

	/*!
	 * \deprecated Use DiscoveryMatch::GetDeviceEndpoints instead
	 */
	Q_DECL_DEPRECATED
	QUrl GetDeviceEndpoint() const;
	/*!
	 * \deprecated Use DiscoveryMatch::SetDeviceEndpoints instead
	 */
	Q_DECL_DEPRECATED
	void SetDeviceEndpoint(const QUrl &rDeviceEndpoint);
	QList<QUrl> GetDeviceEndpoints() const;
	void SetDeviceEndpoints(const QList<QUrl> &rDeviceEndpoint);
	QStringList GetTypes() const;
	void SetTypes(const QStringList &rTypes);
	QStringList GetScopes() const;
	void SetScopes(const QStringList &rScopes);
	QUuid GetEndpointReference() const;
	void SetEndpointReference(const QUuid &rReference);

private:
	QList<QUrl> mDeviceEndpoints;
	QStringList mTypes;
	QStringList mScopes;
	QUuid mEndpointReference;
};

Q_DECLARE_METATYPE(DiscoveryMatch);
