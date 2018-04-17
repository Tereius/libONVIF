#include "OnvifDiscovery.h"
#include "SoapHelper.h"
#include <QElapsedTimer>


DiscoveryMatch::DiscoveryMatch() :
mDeviceEndpoint(),
mTypes(),
mScopes() {

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

OnvifDiscovery::OnvifDiscovery(const QStringList &rScopes /*= {}*/, const QStringList &rTypes /*= {"tds:Device", "tdn:NetworkVideoTransmitter"}*/, QObject *pParent /*= nullptr*/) :
QObject(pParent),
mTypes(rTypes),
mScopes(rScopes),
mpWorker(nullptr),
mMutex(QMutex::Recursive),
mMatches(),
mActive(false) {

}

OnvifDiscovery::~OnvifDiscovery() {

	Stop();
}

void OnvifDiscovery::Start() {

	bool activeBackup = mActive;
	mMutex.lock();
	if(!mpWorker) {
		mpWorker = new OnvifDiscoveryWorker(mScopes, mTypes, this);
		connect(mpWorker, &OnvifDiscoveryWorker::Match, this, &OnvifDiscovery::Match);
		connect(mpWorker, &OnvifDiscoveryWorker::Match, [this](const DiscoveryMatch &rMatch) {
			auto found = false;
			this->mMutex.lock();
			for(auto match : this->mMatches) {
				if(match.GetDeviceEndpoint() == rMatch.GetDeviceEndpoint()) {
					found = true;
					break;
				}
			}
			if(!found) {
				this->mMatches << rMatch;
			}
			this->mMutex.unlock();
			if(!found) {
				emit NewMatch(rMatch);
				emit MatchesChanged();
			}
		});
		mActive = mpWorker->StartDiscovery();
		if(!mActive) {
			Stop();
		}
	}
	mMutex.unlock();
	if(activeBackup != mActive) emit ActiveChanged();
}

void OnvifDiscovery::Stop() {

	auto activeBackup = mActive;
	mMutex.lock();
	if(mpWorker) {
		mpWorker->StopDiscovery();
		mpWorker->deleteLater();
		mpWorker = nullptr;
		mActive = false;
	}
	mMutex.unlock();
	if(activeBackup != mActive) emit ActiveChanged();
}

void OnvifDiscovery::SetMatchScopes(const QStringList &rScopesToMatch) {

	QMutexLocker lock(&mMutex);
	mScopes = rScopesToMatch;
	Restart();
}

void OnvifDiscovery::SetMatchTypes(const QStringList &rTypesToMatch) {

	QMutexLocker lock(&mMutex);
	mTypes = rTypesToMatch;
	Restart();
}

void OnvifDiscovery::Restart() {

	QMutexLocker lock(&mMutex);
	Stop();
	Start();
}

QList<DiscoveryMatch> OnvifDiscovery::GetMatches() {

	QMutexLocker lock(&mMutex);
	return mMatches;
}

int OnvifDiscovery::GetMatchesCount() {

	QMutexLocker lock(&mMutex);
	return mMatches.size();
}

void OnvifDiscovery::ClearMatches() {

	mMutex.lock();
	mMatches.clear();
	mMutex.unlock();
	emit MatchesChanged();
}

bool OnvifDiscovery::Active() {

	QMutexLocker lock(&mMutex);
	return mActive;
}

OnvifDiscoveryWorker::OnvifDiscoveryWorker(const QStringList &rScopes, const QStringList &rTypes, QObject *pParent) :
QThread(pParent),
mpClient(new OnvifDiscoveryClient(QUrl("soap.udp://239.255.255.250:3702"), QSharedPointer<SoapCtx>::create(), this)),
mTypes(rTypes),
mScopes(rScopes),
mMesssageId(QString("uuid:%1").arg(SoapHelper::GenerateUuid())) {

}

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
		if(!terminated) qWarning() << "Discovery worker couldn't be terminated within time:" << waitTimespan << "ms";
		else qDebug() << "Discovery worker successfully stopped";
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
	while(!QThread::isInterruptionRequested()) {
		if(probeResponse) {
			auto matchResp = mpClient->ReceiveProbeMatches();
			if(matchResp) {
				auto relatesTo = matchResp.GetSoapHeaderRelatesTo();
				if(!relatesTo.isNull() && mMesssageId.compare(relatesTo) == 0) {
					if(auto matchs = matchResp.getResultObject()) {
						if(matchs->wsdd__ProbeMatches) {
							for(auto i = 0; i < matchs->wsdd__ProbeMatches->__sizeProbeMatch; ++i) {
								wsdd__ProbeMatchesType match = matchs->wsdd__ProbeMatches[i];
								for(auto ii = 0; ii < match.__sizeProbeMatch; ++ii) {
									auto probe = match.ProbeMatch[ii];
									DiscoveryMatch discoveryMatch;
									if(probe.XAddrs) discoveryMatch.SetDeviceEndpoint(QString::fromUtf8(probe.XAddrs).trimmed());
									else {
										qInfo() << "Got a match which doesn't provide an endpoint - skipping";
										continue;
									}
									if(probe.Types) discoveryMatch.SetTypes(QString::fromUtf8(probe.Types).split(' ', QString::SkipEmptyParts));
									else {
										qInfo() << "Got a match which doesn't provide a type - skipping";
										continue;
									}
									if(probe.Scopes && probe.Scopes->__item) discoveryMatch.SetScopes(QString::fromLocal8Bit(probe.Scopes->__item).split(' ', QString::SkipEmptyParts));
									else qInfo() << "Got a match which doesn't provide a scope:" << discoveryMatch.GetDeviceEndpoint();
									qDebug() << "Got a match:" << discoveryMatch.GetDeviceEndpoint();
									emit Match(discoveryMatch);
								}
							}
						}
					}
				}
				else {
					qInfo() << "Skipping non related message with id:" << relatesTo;
				}
			}
			else if(matchResp.GetErrorCode() != SOAP_EOF) {
				qWarning() << "The discovery match failed:" << matchResp.GetCompleteFault();
			}
		}
		else {
			qWarning() << "The discovery probe failed:" << probeResponse.GetCompleteFault();
			// Sleeping
			for(auto i = 1; i <= 10 && !QThread::isInterruptionRequested(); ++i) QThread::msleep(1000);
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
