#include "Response.h"


QDebug operator<<(QDebug debug, const SimpleResponse &c) {

	QDebugStateSaver saver(debug);
	debug.nospace() << c.GetCompleteFault();
	return debug;
}
