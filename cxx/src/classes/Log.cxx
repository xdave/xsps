#include <String.h>
#include <Color.h>
#include <classes/Log.h>
#include <stdio.h>

namespace xsps {

	Log::Log(){}
	Log::~Log(){}

	LogType Log::Info  = { "INFO",  Color::WHITE,  stdout };
	LogType Log::Warn  = { "WARN",  Color::YELLOW, stdout };
	LogType Log::Debug = { "DEBUG", Color::CYAN,   stdout };
	LogType Log::Err   = { "ERR",   Color::RED,    stderr };

	void Log::print(LogType type, String msg, String context/*="Main"*/) {
		if(type.name == "DEBUG") {
			#ifndef DEBUG
			return;
			#endif
		}
		char bold[7], color[7], off[7];
		sprintf(bold, "%c[%dm", Color::ESC, Color::BOLD);
		sprintf(color, "%c[%dm", Color::ESC, type.color);
		sprintf(off, "%c[%dm", Color::ESC, Color::OFF);

		fprintf(type.target, "%s%s[%s] => [%s]: %s%s\n",
			bold, color, type.name, context, msg, off);

	}

};
