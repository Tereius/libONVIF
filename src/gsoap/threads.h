#pragma once
#include <QMutex>
#include <QSharedPointer>

#define MUTEX_TYPE				QSharedPointer<QMutex>
#define MUTEX_INITIALIZER	QSharedPointer<QMutex>(new QMutex())
#define MUTEX_LOCK(x)			x->lock()
#define MUTEX_UNLOCK(x)		x->unlock()
