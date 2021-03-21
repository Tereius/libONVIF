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
#include "OnvifDiscovery.h"
#include "SoapHelper.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QLoggingCategory>
#if(QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
#define HAS_QT_RECURSIVEMUTEX
#include <QRecursiveMutex>
#else
#include <QMutex>
#endif

Q_LOGGING_CATEGORY(dd, "DeviceDiscovery")

OnvifDiscoveryWorker::OnvifDiscoveryWorker(const QStringList &rScopes, const QStringList &rTypes, QObject *pParent) :
 QThread(pParent),
 mpClient(new OnvifDiscoveryClient(QUrl("soap.udp://239.255.255.250:3702"), QSharedPointer<SoapCtx>::create(), this)),
 mTypes(rTypes),
 mScopes(rScopes),
 mMesssageId(QString("uuid:%1").arg(SoapHelper::GenerateUuid())) {}

OnvifDiscoveryWorker::~OnvifDiscoveryWorker() {

	StopDiscovery();
}

bool OnvifDiscoveryWorker::StartDiscovery() {

	if(!isRunning()) {
		qDebug(dd) << "Starting discovery worker";
		auto probeResponse = Probe(mMesssageId);
		if(probeResponse) {
			start();
			qDebug(dd) << "Discovery worker successfully started";
			return true;
		}
		qWarning(dd) << "Couldn't start discovery worker - initial probe failed:" << probeResponse.GetCompleteFault();
		return false;
	}
	return true;
}

void OnvifDiscoveryWorker::StopDiscovery() {

	if(!isInterruptionRequested() && isRunning()) {
		qDebug(dd) << "Stopping discovery worker";
		requestInterruption();
		mpClient->GetCtx()->ForceSocketClose();
		const auto waitTimespan = 20000UL;
		auto terminated = wait(waitTimespan);
		if(!terminated)
			qWarning(dd) << "Discovery worker couldn't be terminated within time:" << waitTimespan << "ms";
		else
			qDebug(dd) << "Discovery worker successfully stopped";
	}
}

DetailedResponse OnvifDiscoveryWorker::Probe(const QString &rMessageId) {

	ProbeTypeRequest request;
	auto typesString = mTypes.join(' ');
	auto typesUtf8 = typesString.toUtf8();
	request.Types = typesUtf8.data();
	if(!mScopes.empty()) {
		auto scopesString = mScopes.join(' ');
		auto scopesUtf8 = scopesString.toUtf8();
		request.Scopes = new wsdd__ScopesType();
		request.Scopes->__item = scopesUtf8.data();
	}
	return mpClient->Probe(request, rMessageId);
}

void OnvifDiscoveryWorker::run() {

	auto probeResponse = DetailedResponse();
	QElapsedTimer timer;
	timer.start();
	while(!isInterruptionRequested()) {
		if(probeResponse) {
			auto matchResp = mpClient->ReceiveProbeMatches();
			if(matchResp) {
				auto relatesTo = matchResp.GetSoapHeaderRelatesTo();
				if(!relatesTo.isNull() && mMesssageId.compare(relatesTo) == 0) {
					if(auto matchs = matchResp.GetResultObject()) {
						if(matchs->wsdd__ProbeMatches) {
							for(auto i = 0; i < matchs->wsdd__ProbeMatches->__sizeProbeMatch; ++i) {
								wsdd__ProbeMatchesType match = matchs->wsdd__ProbeMatches[i];
								for(auto ii = 0; ii < match.__sizeProbeMatch; ++ii) {
									auto probe = match.ProbeMatch[ii];
									DiscoveryMatch discoveryMatch;
									if(probe.XAddrs) {
#if(QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
										auto urlsStr = QString::fromUtf8(probe.XAddrs).split(' ', Qt::SkipEmptyParts);
#else
										auto urlsStr = QString::fromUtf8(probe.XAddrs).split(' ', String::SkipEmptyParts);
#endif
										QList<QUrl> endpoints = QUrl::fromStringList(urlsStr);
										for(auto iter = endpoints.begin(); iter != endpoints.end();) {
											if(iter->isEmpty()) {
												qDebug(dd) << "Removing empty endpoint url:" << *iter;
												iter = endpoints.erase(iter);
											} else if(!iter->isValid()) {
												qDebug(dd) << "Removing invalid endpoint url:" << *iter;
												iter = endpoints.erase(iter);
											} else {
												qWarning() << "url" << *iter;
												++iter;
											}
										}
										if(endpoints.isEmpty()) {
											qInfo(dd) << "Got a match which doesn't provide a valid device endpoint - skipping";
											continue;
										}
										discoveryMatch.SetDeviceEndpoints(endpoints);
										if(probe.wsa5__EndpointReference.Address) {
											discoveryMatch.SetEndpointReference(SoapHelper::QuuidFromString(QString::fromUtf8(probe.wsa5__EndpointReference.Address)));
										}
									} else {
										qInfo(dd) << "Got a match which doesn't provide a device endpoint - skipping";
										continue;
									}
									if(probe.Types) {
#if(QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
										discoveryMatch.SetTypes(QString::fromUtf8(probe.Types).split(' ', Qt::SkipEmptyParts));
#else
										discoveryMatch.SetTypes(QString::fromUtf8(probe.Types).split(' ', QString::SkipEmptyParts));
#endif
									} else {
										qInfo(dd) << "Got a match which doesn't provide a type - skipping";
										continue;
									}
									if(probe.Scopes && probe.Scopes->__item) {
#if(QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
										discoveryMatch.SetScopes(QString::fromLocal8Bit(probe.Scopes->__item).split(' ', Qt::SkipEmptyParts));
#else
										discoveryMatch.SetScopes(QString::fromLocal8Bit(probe.Scopes->__item).split(' ', QString::SkipEmptyParts));
#endif
									} else
										qInfo(dd) << "Got a match which doesn't provide a scope:" << discoveryMatch.GetDeviceEndpoints();
									qDebug(dd) << "Got a match:" << discoveryMatch.GetDeviceEndpoints();
									emit Match(discoveryMatch);
								}
							}
						}
					}
				} else {
					qInfo(dd) << "Skipping non related message with id:" << relatesTo;
				}
			} else if(matchResp.GetErrorCode() != SOAP_EOF) {
				qWarning(dd) << "The discovery match failed:" << matchResp.GetCompleteFault();
			}
		} else {
			qWarning(dd) << "The discovery probe failed:" << probeResponse.GetCompleteFault();
			// Sleeping
			for(auto i = 1; i <= 10 && !QThread::isInterruptionRequested(); ++i)
				QThread::msleep(1000);
		}
		// Send a new probe earliest 20 seconds after the last probe
		if(timer.hasExpired(20000)) {
			mMesssageId = QString("uuid:%1").arg(SoapHelper::GenerateUuid());
			probeResponse = Probe(mMesssageId);
			timer.start();
		}
	} // end while
	timer.invalidate();
}

struct OnvifDiscoveryPrivate {

	explicit OnvifDiscoveryPrivate(OnvifDiscovery *pQ) :
	 mpQ(pQ),
	 mTypes(),
	 mScopes(),
	 mpWorker(nullptr),
#if defined(HAS_QT_RECURSIVEMUTEX)
	 mMutex(),
#else
	 mMutex(QMutex::Recursive),
#endif
	 mMatches(),
	 mActive(false) {
	}

	OnvifDiscovery *mpQ;
	QStringList mTypes;
	QStringList mScopes;
	OnvifDiscoveryWorker *mpWorker;
	QMutex mMutex;
	QList<DiscoveryMatch> mMatches;
	bool mActive;
};

OnvifDiscovery::OnvifDiscovery(const QStringList &rScopes /*= {}*/,
                               const QStringList &rTypes /*= {"tds:Device", "tdn:NetworkVideoTransmitter"}*/,
                               QObject *pParent /*= nullptr*/) :
 QObject(pParent), mpD(new OnvifDiscoveryPrivate(this)) {

	mpD->mTypes = rTypes;
	mpD->mScopes = rScopes;
}

OnvifDiscovery::~OnvifDiscovery() {

	Stop();
	delete mpD;
}

void OnvifDiscovery::Start() {

	bool activeBackup = mpD->mActive;
	mpD->mMutex.lock();
	if(!mpD->mpWorker) {
		mpD->mpWorker = new OnvifDiscoveryWorker(mpD->mScopes, mpD->mTypes, this);
		connect(mpD->mpWorker, &OnvifDiscoveryWorker::Match, this, &OnvifDiscovery::Match);
		connect(mpD->mpWorker, &OnvifDiscoveryWorker::Match, [this](const DiscoveryMatch &rMatch) {
			auto found = false;
			this->mpD->mMutex.lock();
			for(const auto &match : this->mpD->mMatches) {
				for(const auto &endpoint : rMatch.GetDeviceEndpoints()) {
					if(match.GetDeviceEndpoints().contains(endpoint)) {
						found = true;
						break;
					}
				}
				if(found) break;
			}
			if(!found) {
				this->mpD->mMatches << rMatch;
			}
			this->mpD->mMutex.unlock();
			if(!found) {
				emit NewMatch(rMatch);
				emit MatchesChanged();
			}
		});
		mpD->mActive = mpD->mpWorker->StartDiscovery();
		if(!mpD->mActive) {
			Stop();
		}
	}
	mpD->mMutex.unlock();
	if(activeBackup != mpD->mActive) emit ActiveChanged();
}

void OnvifDiscovery::Stop() {

	auto activeBackup = mpD->mActive;
	mpD->mMutex.lock();
	if(mpD->mpWorker) {
		mpD->mpWorker->StopDiscovery();
		mpD->mpWorker->deleteLater();
		mpD->mpWorker = nullptr;
		mpD->mActive = false;
	}
	mpD->mMutex.unlock();
	if(activeBackup != mpD->mActive) emit ActiveChanged();
}

void OnvifDiscovery::SetMatchScopes(const QStringList &rScopesToMatch) {

	QMutexLocker lock(&mpD->mMutex);
	mpD->mScopes = rScopesToMatch;
	Restart();
}

void OnvifDiscovery::SetMatchTypes(const QStringList &rTypesToMatch) {

	QMutexLocker lock(&mpD->mMutex);
	mpD->mTypes = rTypesToMatch;
	Restart();
}

void OnvifDiscovery::Restart() {

	QMutexLocker lock(&mpD->mMutex);
	Stop();
	Start();
}

QList<DiscoveryMatch> OnvifDiscovery::GetMatches() {

	QMutexLocker lock(&mpD->mMutex);
	return mpD->mMatches;
}

int OnvifDiscovery::GetMatchesCount() {

	QMutexLocker lock(&mpD->mMutex);
	return mpD->mMatches.size();
}

void OnvifDiscovery::ClearMatches() {

	mpD->mMutex.lock();
	mpD->mMatches.clear();
	mpD->mMutex.unlock();
	emit MatchesChanged();
}

bool OnvifDiscovery::Active() {

	QMutexLocker lock(&mpD->mMutex);
	return mpD->mActive;
}
