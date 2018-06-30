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
#include "OnvifCommonExport.h"
#include <QDateTime>


/*!
 *
 * \brief DTO that holds a duration or a date time
 *
 */
class ONVIFCOMMON_EXPORT AbsoluteOrRelativeTime {

public:
	AbsoluteOrRelativeTime() :
		mDuration(-1),
		mDateTime() {
	}

	AbsoluteOrRelativeTime(qint64 duration) :
		mDuration(duration),
		mDateTime() {
	}

	AbsoluteOrRelativeTime(QDateTime dateTime) :
		mDuration(-1),
		mDateTime(dateTime) {
	}

	bool IsDuration() const {

		return !IsDateTime();
	}

	bool IsDateTime() const {

		return !mDateTime.isNull();
	}

	void SetDateTime(const QDateTime &rDateTime) {

		mDateTime = rDateTime;
		mDuration = -1;
	}

	const QDateTime& GetDateTime() const {

		return mDateTime;
	}

	void SetDuration(qint64 duration) {

		mDuration = duration;
		mDateTime = QDateTime();
	}

	qint64 GetDuration() const {

		return mDuration;
	}

private:

	qint64 mDuration;
	QDateTime mDateTime;
};
