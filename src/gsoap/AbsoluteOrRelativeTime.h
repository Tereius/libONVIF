#pragma once
#include "OnvifCommonExport.h"
#include <QDateTime>


class ONVIFCOMMON_EXPORT AbsoluteOrRelativeTime {

public:
	AbsoluteOrRelativeTime() :
		mDuration(-1),
		mDateTime() {}

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
