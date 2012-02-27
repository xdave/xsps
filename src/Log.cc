#include "common.h"
#include "xsps_string.h"
#include "Color.h"
#include "Log.h"

#include <cstdio>


namespace xsps {
	Logger* Logger::instance = NULL;

	Logger::Logger() {
		types[LOG_INFO].name    = "INFO ";
		types[LOG_INFO].color   = Color::WHITE;
		types[LOG_INFO].target  = stdout;
		types[LOG_WARN].name    = "WARN ";
		types[LOG_WARN].color   = Color::YELLOW;
		types[LOG_WARN].target  = stdout;
		types[LOG_DEBUG].name   = "DEBUG";
		types[LOG_DEBUG].color   = Color::CYAN;
		types[LOG_DEBUG].target  = stderr;
		types[LOG_ERROR].name    = "ERROR";
		types[LOG_ERROR].color   = Color::RED;
		types[LOG_ERROR].target  = stderr;
	}

	Logger* Logger::get_instance() {
		if(instance == NULL) {
			instance = new Logger();
		}
		return instance;
	}

	Logger::~Logger() {
		delete instance;
	}

	void Logger::print(int type, String msg, String context) {
		if(type == LOG_DEBUG) {
			#ifndef XSPS_DEBUG
			return;
			#endif
		}

		LogType t = types[type];
		char bold[Color::SIZE],
		     color[Color::SIZE],
		     off[Color::SIZE];
		char result[LOG_BUFFER_SIZE];
		sprintf(bold, "%c[%dm", Color::ESC, Color::BOLD);
		sprintf(color, "%c[%dm", Color::ESC, t.color);
		sprintf(off, "%c[%dm", Color::ESC, Color::OFF);

		sprintf(result, "%s%s[%s] => [%s]: %s%s\n",
			bold, color, t.name, context, msg, off);

		fprintf(t.target, "%s", result);

		if(log_file != NULL) {
			fprintf(log_file, "%s", result);
		}

	}

}
