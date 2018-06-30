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


DiscoveryMatch::DiscoveryMatch() :
	mDeviceEndpoint(),
	mTypes(),
	mScopes(),
	mEndpointReference() {

}

DiscoveryMatch::~DiscoveryMatch() {

}

QUrl DiscoveryMatch::GetDeviceEndpoint() const {

	return mDeviceEndpoint;
}

void DiscoveryMatch::SetDeviceEndpoint(const QUrl &rDeviceEndpoint) {

	mDeviceEndpoint = rDeviceEndpoint;
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
