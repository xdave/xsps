#include <xsps_string.h>
#include <Color.h>
#include <cstdio>

#ifndef XSPS_LOGGER_H
#define XSPS_LOGGER_H 1

namespace xsps {

	enum { LOG_INFO, LOG_WARN, LOG_DEBUG, LOG_ERROR };

	typedef struct LogType {
		String name;
		int color;
		FILE *target;
	} LogType;

	class Logger {
	public:
		static Logger* get_instance();
		void print(int, String, String context = "Default");
		~Logger();
	protected:
		Logger();
	private:
		static Logger* instance;
		LogType types[4];
		FILE* log_file;
	};

} // namespace xsps

#endif // XSPS_LOGGER_H
