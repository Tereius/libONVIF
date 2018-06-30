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
#include "OnvifDiscoveryClient.h"
#include "DiscoveryMatch.h"
#include <QObject>
#include <QStringList>
#include <QUrl>
#include <QThread>
#include <QMutex>
#include <QList>


struct OnvifDiscoveryPrivate;

class OnvifDiscoveryWorker : public QThread {

	Q_OBJECT

public:
	OnvifDiscoveryWorker(const QStringList &rScopes, const QStringList &rTypes, QObject *pParent);
	virtual ~OnvifDiscoveryWorker();
	bool StartDiscovery();
	// Blocking
	void StopDiscovery();

signals:
	void Match(const DiscoveryMatch &rMatch);

protected:
	void run() override;

private:
	Q_DISABLE_COPY(OnvifDiscoveryWorker);

	DetailedResponse Probe(const QString &rMessageId);

	OnvifDiscoveryClient *mpClient;
	QStringList mTypes;
	QStringList mScopes;
	QString mMesssageId;
};


/*!
*
* \brief A WS discovery listener
*
* Use this class to listen (non blocking) for devices entering the network
*
*/
class ONVIFDISCOVERY_EXPORT OnvifDiscovery : public QObject {

	Q_OBJECT
		Q_PROPERTY(QList<DiscoveryMatch> matches READ GetMatches NOTIFY MatchesChanged)
		Q_PROPERTY(bool active READ Active NOTIFY ActiveChanged)

public:
	/*!
	*
	* \brief Construct a WS discovery listener
	*
	* \param rScopes The WS discovery scopes
	* \param rTypes The WS discovery types
	* \param pParent A QObject parent
	*
	*/
	OnvifDiscovery(const QStringList &rScopes = {}, const QStringList &rTypes = {"tds:Device", "tdn:NetworkVideoTransmitter"}, QObject *pParent = nullptr);
	virtual ~OnvifDiscovery();
	//! Clear all the matches that were found since start was called
	Q_INVOKABLE void ClearMatches();
	//! Set the WS discovery scopes
	Q_INVOKABLE void SetMatchScopes(const QStringList &rScopesToMatch);
	//! Set the WS discovery types
	Q_INVOKABLE void SetMatchTypes(const QStringList &rTypesToMatch);
	//! Get the number of unique matches
	int GetMatchesCount();
	//! Get the unique matches
	QList<DiscoveryMatch> GetMatches();
	//! Check if the listener is active and we listen for devices
	bool Active();

signals:
	//! Emitted if a match is found. As long as a matchable device is in the network this signal will be triggered periodically containing the same match
	void Match(const DiscoveryMatch &rMatch);
	//! Emitted if a NEW match is found that is unique since Start was called the first time or ClearMatches was called
	void NewMatch(const DiscoveryMatch &rMatch);
	//! Emitted if the numer of unique matches changed
	void MatchesChanged();
	//! Emitted if the active state changes
	void ActiveChanged();

	public slots:
	//! Start listening for devices. Non blocking
	void Start();
	//! Stop listening for devices
	void Stop();

private:
	Q_DISABLE_COPY(OnvifDiscovery);

	void Restart();

	OnvifDiscoveryPrivate *mpD;
};
