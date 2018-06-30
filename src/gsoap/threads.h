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
#include <QMutex>
#include <QSharedPointer>


#define MUTEX_TYPE				QSharedPointer<QMutex>
#define MUTEX_INITIALIZER	QSharedPointer<QMutex>(new QMutex())
#define MUTEX_LOCK(x)			x->lock()
#define MUTEX_UNLOCK(x)		x->unlock()
