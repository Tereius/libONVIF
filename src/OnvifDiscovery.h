#pragma once
#include "onvifdiscoveryExport.h"
#include "OnvifDiscoveryClient.h"
#include <QObject>
#include <QStringList>
#include <QUrl>
#include <QThread>
#include <QMutex>
#include <QList>


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

private:

	QUrl mDeviceEndpoint;
	QStringList mTypes;
	QStringList mScopes;
};

class OnvifDiscoveryWorker : public QThread {

	Q_OBJECT

public:
	OnvifDiscoveryWorker(const QStringList &rScopes, const QStringList &rTypes, QObject *pParent);
	virtual ~OnvifDiscoveryWorker();
	bool StartDiscovery();
	// Blocking
	void StopDiscovery();
	void run() override;

signals:
	void Match(const DiscoveryMatch &rMatch);

private:
	Q_DISABLE_COPY(OnvifDiscoveryWorker);
	DetailedResponse Probe(const QString &rMessageId);

	OnvifDiscoveryClient *mpClient;
	QStringList mTypes;
	QStringList mScopes;
	QString mMesssageId;
};

//! Thread safe
class ONVIFDISCOVERY_EXPORT OnvifDiscovery : public QObject {

	Q_OBJECT
		Q_PROPERTY(QList<DiscoveryMatch> matches READ GetMatches NOTIFY MatchesChanged)
		Q_PROPERTY(bool active READ Active NOTIFY ActiveChanged)

public:
	OnvifDiscovery(const QStringList &rScopes = {}, const QStringList &rTypes = {"tds:Device", "tdn:NetworkVideoTransmitter"}, QObject *pParent = nullptr);
	virtual ~OnvifDiscovery();
	Q_INVOKABLE void ClearMatches();
	Q_INVOKABLE void SetMatchScopes(const QStringList &rScopesToMatch);
	Q_INVOKABLE void SetMatchTypes(const QStringList &rTypesToMatch);
	QList<DiscoveryMatch> GetMatches();
	bool Active();

signals:
	//! As long as a matchable device is in the network this signal will be triggered periodically containing the same match.
	void Match(const DiscoveryMatch &rMatch);
	//! Triggered if a NEW match is found that is unique since Start()
	// was called the first time or ClearMatches() was called.
	void NewMatch(const DiscoveryMatch &rMatch);
	void MatchesChanged();
	void ActiveChanged();

	public slots:
	void Start();
	void Stop();

private:
	Q_DISABLE_COPY(OnvifDiscovery);
	void Restart();

	QStringList mTypes;
	QStringList mScopes;
	OnvifDiscoveryWorker *mpWorker;
	QMutex mMutex;
	QList<DiscoveryMatch> mMatches;
	bool mActive;
};

Q_DECLARE_METATYPE(DiscoveryMatch);
