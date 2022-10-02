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
#include <QMetaType>
#include <qglobal.h>

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
#define QML_ENUM Q_ENUMS
#else
#define QML_ENUM Q_ENUM
#endif

#if QT_VERSION < QT_VERSION_CHECK(5, 4, 0)
#define qUtf8Printable(string) QString(string).toUtf8().constData()
#endif

#define HTTP_CONTINUE 100
#define HTTP_SWITCHING_PROTOCOLS 101
#define HTTP_PROCESSING 102
#define HTTP_OK 200
#define HTTP_CREATED 201
#define HTTP_ACCEPTED 202
#define HTTP_NON_AUTHORITATIVE 203
#define HTTP_NO_CONTENT 204
#define HTTP_RESET_CONTENT 205
#define HTTP_PARTIAL_CONTENT 206
#define HTTP_MULTI_STATUS 207
#define HTTP_ALREADY_REPORTED 208
#define HTTP_IM_USED 226
#define HTTP_MULTIPLE_CHOICES 300
#define HTTP_MOVED_PERMANENTLY 301
#define HTTP_MOVED_TEMPORARILY 302
#define HTTP_SEE_OTHER 303
#define HTTP_NOT_MODIFIED 304
#define HTTP_USE_PROXY 305
#define HTTP_TEMPORARY_REDIRECT 307
#define HTTP_PERMANENT_REDIRECT 308
#define HTTP_BAD_REQUEST 400
#define HTTP_UNAUTHORIZED 401
#define HTTP_PAYMENT_REQUIRED 402
#define HTTP_FORBIDDEN 403
#define HTTP_NOT_FOUND 404
#define HTTP_METHOD_NOT_ALLOWED 405
#define HTTP_NOT_ACCEPTABLE 406
#define HTTP_PROXY_AUTHENTICATION_REQUIRED 407
#define HTTP_REQUEST_TIME_OUT 408
#define HTTP_CONFLICT 409
#define HTTP_GONE 410
#define HTTP_LENGTH_REQUIRED 411
#define HTTP_PRECONDITION_FAILED 412
#define HTTP_REQUEST_ENTITY_TOO_LARGE 413
#define HTTP_REQUEST_URI_TOO_LARGE 414
#define HTTP_UNSUPPORTED_MEDIA_TYPE 415
#define HTTP_RANGE_NOT_SATISFIABLE 416
#define HTTP_EXPECTATION_FAILED 417
#define HTTP_IM_A_TEAPOT 418
#define HTTP_MISDIRECTED_REQUEST 421
#define HTTP_UNPROCESSABLE_ENTITY 422
#define HTTP_LOCKED 423
#define HTTP_FAILED_DEPENDENCY 424
#define HTTP_UPGRADE_REQUIRED 426
#define HTTP_PRECONDITION_REQUIRED 428
#define HTTP_TOO_MANY_REQUESTS 429
#define HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE 431
#define HTTP_UNAVAILABLE_FOR_LEGAL_REASONS 451
#define HTTP_INTERNAL_SERVER_ERROR 500
#define HTTP_NOT_IMPLEMENTED 501
#define HTTP_BAD_GATEWAY 502
#define HTTP_SERVICE_UNAVAILABLE 503
#define HTTP_GATEWAY_TIME_OUT 504
#define HTTP_VERSION_NOT_SUPPORTED 505
#define HTTP_VARIANT_ALSO_VARIES 506
#define HTTP_INSUFFICIENT_STORAGE 507
#define HTTP_LOOP_DETECTED 508
#define HTTP_NOT_EXTENDED 510


// calls qRegisterMetaType once for your custom Type T - use like so:
//   static QMetaTypeRegistrar<T> RegisterMyType;
// or so:
//   static QMetaTypeRegistrar<T> RegisterMyType("MyTypesName");
template<class T>
class QMetaTypeRegistrar {
 public:
	QMetaTypeRegistrar() { qRegisterMetaType<T>(); };
	explicit QMetaTypeRegistrar(const char *metaTypeName) { qRegisterMetaType<T>(metaTypeName); }
};

#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)

// combines Q_DECLARE_METATYPE and qRegisterMetaType in one macro
#define REGISTER_METATYPE(TYPE) REGISTER_METATYPE_IMPL(TYPE) // NOLINT
#define REGISTER_METATYPE_IMPL(TYPE) \
	Q_DECLARE_METATYPE(TYPE)           \
	static QMetaTypeRegistrar<TYPE> CONCAT(Registrar_, __COUNTER__); // NOLINT
