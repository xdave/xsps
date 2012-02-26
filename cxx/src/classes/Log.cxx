#include <String.h>
#include <Color.h>
#include <classes/Log.h>
#include <stdio.h>
#include <string.h>

namespace xsps {

	Log::Log(){

		Info  = { "INFO ", Color::WHITE,  stdout };
		Warn  = { "WARN ", Color::YELLOW, stdout };
		Debug = { "DEBUG", Color::CYAN,   stdout };
		Err   = { "ERROR", Color::RED,    stderr };
	}

	Log::~Log(){}

	void Log::print(LogType type, String msg, String context) {
		if(strcmp(type.name, "DEBUG") == 0) {
			#ifndef DEBUG
			return;
			#endif
		}
		char bold[8], color[8], off[8];
		char result[256];
		sprintf(bold, "%c[%dm", Color::ESC, Color::BOLD);
		sprintf(color, "%c[%dm", Color::ESC, type.color);
		sprintf(off, "%c[%dm", Color::ESC, Color::OFF);

		sprintf(result, "%s%s[%s] => [%s]: %s%s\n",
			bold, color, type.name, context, msg, off);

		fprintf(type.target, result);

		if(type.logfile != NULL) {
			fprintf(type.logfile, result);
		}

	}

};
