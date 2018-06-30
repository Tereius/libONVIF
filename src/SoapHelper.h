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
#include <QString>
#include <QUuid>


/*!
 *
 * \brief Provides some helper functions
 *
 */
class ONVIFCOMMON_EXPORT SoapHelper {

public:

	static QString GenerateUuid();
	static QUuid QuuidFromString(const QString &rUuidString);
};