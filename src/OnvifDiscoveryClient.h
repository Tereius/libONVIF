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
#include "DeleterDuplicator.h"
#include "Request.h"
#include "Response.h"
#include "Client.h"
#include "OnvifDiscoveryExport.h"
#include <QVector>
#include <QUrl>


using ProbeMatchesResponse =
 Response<__wsdd__ProbeMatches, ProbeMatchesDeleter<__wsdd__ProbeMatches>, ProbeMatchesDuplicator<__wsdd__ProbeMatches>>;
using ResolveTypeResponse = Response<wsdd__ResolveType, ResolveTypeDeleter<wsdd__ResolveType>, ResolveTypeDuplicator<wsdd__ResolveType>>;
using ProbeMatchTypeResponse =
 Response<wsdd__ProbeMatchesType, ProbeMatchTypeDeleter<wsdd__ProbeMatchesType>, ProbeMatchTypeDuplicator<wsdd__ProbeMatchesType>>;
using HelloTypeRequest = Request<wsdd__HelloType, HelloTypeDeleterReq<wsdd__HelloType>>;
using ProbeTypeRequest = Request<wsdd__ProbeType, ProbeTypeDeleterReq<wsdd__ProbeType>>;
using ByeTypeRequest = Request<wsdd__ByeType, ByeTypeDeleterReq<wsdd__ByeType>>;

struct OnvifDiscoveryClientPrivate;

/*!
 *
 * \brief Client side service implementations of WS discovery
 *
 */
class ONVIFDISCOVERY_EXPORT OnvifDiscoveryClient : public Client {

	Q_OBJECT

public:
	explicit OnvifDiscoveryClient(const QUrl &rEndpoint = QUrl("soap.udp://239.255.255.250:3702"),
	                              QSharedPointer<SoapCtx> sharedCtx = QSharedPointer<SoapCtx>::create(), QObject *pParent = nullptr);
	~OnvifDiscoveryClient() override;

	DetailedResponse Hello(HelloTypeRequest &rRequest);
	DetailedResponse Bye(ByeTypeRequest &rRequest);
	DetailedResponse Probe(ProbeTypeRequest &rRequest, const QString &rMessageId);
	ProbeMatchesResponse ReceiveProbeMatches();

	virtual void SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode = AUTO) final;
	virtual void DisableAuth() final;

private:
	Q_DISABLE_COPY(OnvifDiscoveryClient);

	OnvifDiscoveryClientPrivate *mpD;
};