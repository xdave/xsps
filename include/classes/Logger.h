/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include "xsps_string.h"
#include <cstdio>

#ifndef XSPS_LOGGER_H
#define XSPS_LOGGER_H 1

namespace xsps {

	enum { LOG_INFO, LOG_WARN, LOG_DEBUG, LOG_ERROR };

	static const size_t LOG_BUFFER_SIZE = 256;

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
