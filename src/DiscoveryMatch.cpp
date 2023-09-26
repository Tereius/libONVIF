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
#include "DiscoveryMatch.h"
#include <algorithm>


DiscoveryMatch::DiscoveryMatch() : mDeviceEndpoints(), mTypes(), mScopes(), mEndpointReference() {}

DiscoveryMatch::~DiscoveryMatch() = default;

QList<QUrl> DiscoveryMatch::GetDeviceEndpoints() const {

	return mDeviceEndpoints;
}

void DiscoveryMatch::SetDeviceEndpoints(const QList<QUrl> &rDeviceEndpoint) {

	mDeviceEndpoints = rDeviceEndpoint;
}

QStringList DiscoveryMatch::GetTypes() const {

	return mTypes;
}

void DiscoveryMatch::SetTypes(const QStringList &rTypes) {

	mTypes = rTypes;
}

QStringList DiscoveryMatch::GetScopes() const {

	return mScopes;
}

void DiscoveryMatch::SetScopes(const QStringList &rScopes) {

	mScopes = rScopes;
}

QUuid DiscoveryMatch::GetEndpointReference() const {

	return mEndpointReference;
}

void DiscoveryMatch::SetEndpointReference(const QUuid &rReference) {

	mEndpointReference = rReference;
}

bool DiscoveryMatch::operator==(const DiscoveryMatch &rOther) const {

	if(!GetEndpointReference().isNull() && !rOther.GetEndpointReference().isNull())
		return GetEndpointReference() == rOther.GetEndpointReference();
	auto endpoints = GetDeviceEndpoints();
	auto otherEndpoints = rOther.GetDeviceEndpoints();
	return std::find_first_of(endpoints.constBegin(), endpoints.constEnd(), otherEndpoints.constBegin(), otherEndpoints.constEnd()) !=
	       endpoints.constEnd();
}

bool DiscoveryMatch::operator!=(const DiscoveryMatch &rOther) const {

	return !operator==(rOther);
}
