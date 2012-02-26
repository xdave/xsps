#include <xsps_string.h>
#include <Log.h>
#ifndef XSPS_PARSE_ARGS_H
#define XSPS_PARSE_ARGS_H 1

namespace xsps {

	int print_usage(LogTypes, String);
	int parse_args(LogTypes, int, char **);

}; // namespace xsps

#endif // XSPS_PARSE_ARGS_H
