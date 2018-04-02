#pragma once
#include "Response.h"
#include <QCommandLineParser>
#include <QUrl>


struct CmdOptions {

	bool verbose = false;
	bool discover = false;
	bool capabilities = false;
	int discoverTime = 10000;
	QString host = "";
	QString scheme = "";
	QString path = "";
	int port = 0;
	QUrl endpointUrl = QUrl();
	QString pwd = "";
	QString user = "";
};

class CmdLineParser {

public:
	static void setup(QCommandLineParser &parser);
	static ArbitraryResponse<CmdOptions> parse(const QCommandLineParser &parser);
};