/* Copyright(C) 2021 Björn Stresing
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
#include "Client.h"
#include "Response.h"
#include <QObject>
#include <QUrl>


struct OnvifDevicePrivate;

class OnvifDevice : public QObject {

	Q_OBJECT

 public:
	explicit OnvifDevice(const QUrl &rDeviceEndpoint, QObject *pParent = nullptr);
	~OnvifDevice() override;

	void SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode = AUTO);
	SimpleResponse Initialize();
	SimpleResponse InitializeTopicSet();
	void SubscribePullPoint();

 private:
	void UnsuccessfulPull(int unsuccessfulPullcount, const SimpleResponse &rCause);
	void MessageReceived(const Response<wsnt__NotificationMessageHolderType> &rResponse);
	void LostPullPoint(const SimpleResponse &rCause);
	void ResumedPullPoint();
	static void PrintItemList(tt__ItemList *list);

	OnvifDevicePrivate *mpD;
};