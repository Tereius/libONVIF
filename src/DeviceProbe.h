/* Copyright(C) 2022 Björn Stresing
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
#include "global.h"
#include <QUrl>
#include <QUuid>
#include "OnvifProbeExport.h"

struct DeviceProbePrivate;

class ONVIFPROBE_EXPORT DeviceProbe {

	Q_GADGET
	Q_PROPERTY(QUrl deviceEndpoint READ GetDeviceEndpoint CONSTANT)
	Q_PROPERTY(QString initializationError READ GetError CONSTANT)
	Q_PROPERTY(QString firmwareVersion READ GetFirmwareVersion CONSTANT)
	Q_PROPERTY(QString hardwareId READ GetHardwareId CONSTANT)
	Q_PROPERTY(QString manufacturer READ GetManufacturer CONSTANT)
	Q_PROPERTY(QString model READ GetModel CONSTANT)
	Q_PROPERTY(QString serialNumber READ GetSerialNumber CONSTANT)
	Q_PROPERTY(qint64 dateTimeOffset READ GetDateTimeOffset CONSTANT)
	Q_PROPERTY(QUuid endpointReference READ GetEndpointReference CONSTANT)
	Q_PROPERTY(QList<OnvifServicesTye> services READ GetServices CONSTANT)

public:
	static DeviceProbe create(const QUrl &rDeviceEndpoint);

	DeviceProbe();
	~DeviceProbe();
	DeviceProbe(const DeviceProbe &rOther);
	DeviceProbe &operator=(const DeviceProbe &rOther);

	enum OnvifServicesTye {
		ONVIF_DEVICE = 1 << 0,
		ONVIF_EVENT = 1 << 1,
		ONVIF_MEDIA = 1 << 2,
		ONVIF_MEDIA2 = 1 << 3,
		ONVIF_ANALYTICS = 1 << 4,
		ONVIF_DISPLAY = 1 << 5,
		ONVIF_IMAGING = 1 << 6,
		ONVIF_PTZ = 1 << 7,
		ONVIF_RECEIVER = 1 << 8,
		ONVIF_RECORDING = 1 << 9,
		ONVIF_REPLAY = 1 << 10
	};
	QML_ENUM(OnvifServicesTye)

	bool IsValid() const;

	QUrl GetDeviceEndpoint() const;
	QString GetError() const;
	QString GetFirmwareVersion() const;
	QString GetHardwareId() const;
	QString GetManufacturer() const;
	QString GetModel() const;
	QString GetSerialNumber() const;
	qint64 GetDateTimeOffset() const;
	QUuid GetEndpointReference() const;
	QList<OnvifServicesTye> GetServices() const;

private:
	DeviceProbe(const QUrl &rDeviceEndpoint);
	DeviceProbePrivate *mpD;
};
