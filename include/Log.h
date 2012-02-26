#include <xsps_string.h>
#include <Color.h>
#include <stdio.h>

#ifndef XSPS_LOGGER_H
#define XSPS_LOGGER_H 1

namespace xsps {

	typedef struct LogType {
		String name;
		int color;
		FILE *target;
	} LogType;

	typedef struct LogTypes {
		LogTypes() :
			INFO ({ "INFO ", Color::WHITE,  stdout }),
			WARN ({ "WARN ", Color::YELLOW, stdout }),
			DEBUG({ "DEBUG", Color::CYAN,   stderr }),
			ERROR({ "ERROR", Color::RED,    stderr }) {}
		LogType INFO;
		LogType WARN;
		LogType DEBUG;
		LogType ERROR;
	} LogTypes;

	void Log(LogType type,
		String msg,
		String context = "Default",
		FILE *log_file = NULL);

}; // namespace xsps

#endif // XSPS_LOGGER_H
