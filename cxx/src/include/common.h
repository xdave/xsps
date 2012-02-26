#include <classes/Log.h>
#ifndef COMMON_H
#define COMMON_H

namespace xsps {
	Log log;
	static void LOG(LogType type, String msg, String context = "Default") {
		log.print(type, msg, context);
	}

}; // namespace xsps

#endif // COMMON_H
