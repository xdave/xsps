#include <String.h>
#include <Color.h>
#include <stdio.h>

#ifndef XSPS_LOG_H
#define XSPS_LOG_H

namespace xsps {

typedef struct LogType {
	String name;
	int color;
	FILE *target;
	FILE *logfile;
} LogType;

class Log {
public:
	LogType Info, Warn, Debug, Err;

	Log();
	~Log();

	void print(LogType type, String msg, String context = "Default");

}; // class Log

}; // namespace xsps

#endif // XSPS_LOG_H
