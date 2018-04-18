#pragma once
#include "OnvifDiscoveryExport.h"
#include <QStringList>
#include <QUrl>
#include <QUuid>
#include <QMetaType>


class ONVIFDISCOVERY_EXPORT DiscoveryMatch {

public:
	DiscoveryMatch();
	virtual ~DiscoveryMatch();

	QUrl GetDeviceEndpoint() const;
	void SetDeviceEndpoint(const QUrl &rDeviceEndpoint);
	QStringList GetTypes() const;
	void SetTypes(const QStringList &rTypes);
	QStringList GetScopes() const;
	void SetScopes(const QStringList &rScopes);
	QUuid GetEndpointReference() const;
	void SetEndpointReference(const QUuid &rReference);


private:

	QUrl mDeviceEndpoint;
	QStringList mTypes;
	QStringList mScopes;
	QUuid mEndpointReference;
};

Q_DECLARE_METATYPE(DiscoveryMatch);
