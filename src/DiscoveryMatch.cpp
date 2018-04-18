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
