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
} LogType;

class Log {
public:
	static LogType Info, Warn, Debug, Err;

	Log();
	~Log();

	void print(LogType type, String msg, String context = "Main");

}; // class Log

}; // namespace xsps

#endif // XSPS_LOG_H