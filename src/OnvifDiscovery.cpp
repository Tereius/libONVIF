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
		qDebug() << "Starting discovery worker";
		auto probeResponse = Probe(mMesssageId);
		if(probeResponse) {
			start();
			qDebug() << "Discovery worker successfully started";
			return true;
		}
		qWarning() << "Couldn't start discovery worker - initial probe failed:" << probeResponse.GetCompleteFault();
		return false;
	}
	return true;
}

void OnvifDiscoveryWorker::StopDiscovery() {

	if(!isInterruptionRequested() && isRunning()) {
		qDebug() << "Stopping discovery worker";
		requestInterruption();
		mpClient->GetCtx()->ForceSocketClose();
		const auto waitTimespan = 20000UL;
		auto terminated = wait(waitTimespan);
		if(!terminated)
			qWarning() << "Discovery worker couldn't be terminated within time:" << waitTimespan << "ms";
		else
			qDebug() << "Discovery worker successfully stopped";
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
										discoveryMatch.SetDeviceEndpoint(QString::fromUtf8(probe.XAddrs).trimmed());
										if(probe.wsa5__EndpointReference.Address) {
											discoveryMatch.SetEndpointReference(SoapHelper::QuuidFromString(QString::fromUtf8(probe.wsa5__EndpointReference.Address)));
										}
									} else {
										qDebug() << "Got a match which doesn't provide an endpoint - skipping";
										continue;
									}
									if(probe.Types)
										discoveryMatch.SetTypes(QString::fromUtf8(probe.Types).split(' ', QString::SkipEmptyParts));
									else {
										qWarning() << "Got a match which doesn't provide a type - skipping";
										continue;
									}
									if(probe.Scopes && probe.Scopes->__item)
										discoveryMatch.SetScopes(QString::fromLocal8Bit(probe.Scopes->__item).split(' ', QString::SkipEmptyParts));
									else
										qWarning() << "Got a match which doesn't provide a scope:" << discoveryMatch.GetDeviceEndpoint();
									qDebug() << "Got a match:" << discoveryMatch.GetDeviceEndpoint();
									emit Match(discoveryMatch);
								}
							}
						}
					}
				} else {
					qWarning() << "Skipping non related message with id:" << relatesTo;
				}
			} else if(matchResp.GetErrorCode() != SOAP_EOF) {
				qWarning() << "The discovery match failed:" << matchResp.GetCompleteFault();
			}
		} else {
			qWarning() << "The discovery probe failed:" << probeResponse.GetCompleteFault();
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

	OnvifDiscoveryPrivate(OnvifDiscovery *pQ) :
	 mpQ(pQ), mTypes(), mScopes(), mpWorker(nullptr), mMutex(QMutex::Recursive), mMatches(), mActive(false) {}

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
			for(auto match : this->mpD->mMatches) {
				if(match.GetDeviceEndpoint() == rMatch.GetDeviceEndpoint()) {
					found = true;
					break;
				}
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
