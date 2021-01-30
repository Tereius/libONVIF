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
#include "CmdLineParser.h"


void CmdLineParser::setup(QCommandLineParser &parser) {

	parser.setApplicationDescription("ONVIFinfo is a command line ONVIF client");
	parser.addHelpOption();
	parser.addVersionOption();

	parser.addOption(QCommandLineOption(
	 {"d", "discover"},
	 QCoreApplication::translate(
	  "main", "Search ONVIF devices for 10 seconds (change timespan via --discover-timespan option). Ignores the host if specified.")));
	parser.addOption(QCommandLineOption(QString("discover-timespan"),
	                                    QCoreApplication::translate("main", "Set discover timespan in seconds for ONVIF devices."),
	                                    QCoreApplication::translate("main", "timespan"), QString("10")));
	parser.addOption(QCommandLineOption(
	 QString("host"),
	 QCoreApplication::translate("main", "The ONVIF <host>: e.g.: http://localhost. Leave empty if you want to search for ONVIF hosts."),
	 QCoreApplication::translate("main", "host")));
	parser.addOption(
	 QCommandLineOption(QString("verbose"), QCoreApplication::translate("main", "Prints all the raw SOAP messages. Very noisy.")));
	parser.addOption(QCommandLineOption(QString("path"),
	                                    QCoreApplication::translate("main", "The ONVIF 'device' web service endpoint <path>."),
	                                    QCoreApplication::translate("main", "path"), QString("/onvif/device_service")));
	parser.addOption(QCommandLineOption(
	 QString("port"),
	 QCoreApplication::translate("main", "The <port> of the 'device' web service endpoint. Defaults to 80 for http and 443 for https."),
	 QCoreApplication::translate("main", "port")));
	parser.addOption(QCommandLineOption({"u", "user"},
	                                    QCoreApplication::translate("main", "The <user> to authenticate against the ONVIF device."),
	                                    QCoreApplication::translate("main", "user")));
	parser.addOption(QCommandLineOption({"p", "pwd"},
	                                    QCoreApplication::translate("main", "The <password> to authenticate against the ONVIF device."),
	                                    QCoreApplication::translate("main", "password")));
}

ArbitraryResponse<CmdOptions> CmdLineParser::parse(const QCommandLineParser &parser) {

	auto response = ArbitraryResponse<CmdOptions>();
	auto options = CmdOptions();

	if(parser.isSet("host")) {
		options.capabilities = true;
		options.discover = false;
		options.host = parser.value("host");
		if(options.host.endsWith('/')) options.host = options.host.remove(options.host.length() - 2, 1);
		auto url = QUrl::fromUserInput(options.host);
		options.host = url.host();
		if(url.scheme().startsWith("https:")) {
			options.scheme = "https://";
			options.port = 443;
		} else if(url.scheme().startsWith("http:")) {
			options.scheme = "http://";
			options.port = 80;
		} else {
			options.scheme = "http://";
			options.port = 8080;
		}
	} else {
		options.discover = true;
		options.capabilities = false;
	}

	if(parser.isSet("discover")) {
		options.discover = true;
		options.capabilities = false;
	}

	if(parser.isSet("verbose")) {
		options.verbose = true;
	} else {
		options.verbose = false;
	}

	if(options.discover) {
		bool success = false;
		options.discoverTime = 1000 * parser.value("discover-timespan").toInt(&success);
		if(!success) {
			return ArbitraryResponse<CmdOptions>(
			 GENERIC_FAULT, QCoreApplication::translate("main", "Couldn't parse discovery time span: %1").arg(parser.value("discover-timespan")));
		}
		if(options.discoverTime < 0) {
			return ArbitraryResponse<CmdOptions>(GENERIC_FAULT, QCoreApplication::translate("main", "Discovery time span must be positive"));
		}
	}

	if(!options.discover) {
		if(parser.isSet("path")) {
			options.path = parser.value("path");
			if(!options.path.startsWith('/')) options.path = "/" + options.path;
		} else {
			options.path = "/onvif/device_service";
		}

		if(parser.isSet("port")) {
			bool success = false;
			options.port = parser.value("port").toInt(&success);
			if(!success) {
				return ArbitraryResponse<CmdOptions>(GENERIC_FAULT,
				                                     QCoreApplication::translate("main", "Couldn't parse port: %1").arg(parser.value("port")));
			}
		}

		if(parser.isSet("user")) {
			options.user = parser.value("user");
		}

		if(parser.isSet("pwd")) {
			options.pwd = parser.value("pwd");
		}

		options.endpointUrl = QUrl::fromUserInput(options.scheme + options.host + ":" + QString::number(options.port) + options.path);
		if(!options.endpointUrl.isValid()) {
			return ArbitraryResponse<CmdOptions>(
			 GENERIC_FAULT, QCoreApplication::translate("main", "The endpoint is invalid: %1").arg(options.endpointUrl.errorString()));
		}
	}

	response.SetResultObject(options);
	return response;
}
