#include <xsps_string.h>
#include <Color.h>
#include <Log.h>
#include <stdio.h>
#include <string.h>

namespace xsps {

	void Log(LogType type, String msg, String context, FILE *log_file) {
		if(strcmp(type.name, "DEBUG") == 0) {
			#ifndef XSPS_DEBUG
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

		fprintf(type.target, "%s", result);

		if(log_file != NULL) {
			fprintf(log_file, "%s", result);
		}

	}

};
