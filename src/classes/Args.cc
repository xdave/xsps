#include "common.h"
#include "xsps_string.h"
#include "classes/Args.h"
#include "Log.h"

#include <cstdlib>
#include <cstring>
#include <cerrno>

namespace xsps {

	Args::Args(int& count, char**& vector) {
		argc = count;
		argv = vector;
		progname = argv[0];
	}

	Args::~Args() {}

	int Args::parse() {
		Logger* Log = Logger::get_instance();
		if(argc == 1) {
			Log->print(LOG_ERROR, "No arguments given!", "Args");
			return show_help();
		}

		for (int i = 1; i < argc; i++) {
			String arg = argv[i];
			String next = argv[i+1];
			if(next == NULL) next = "NONE";
			if(streq(arg, "-h") || streq(arg, "--help")) {
				Log->print(LOG_DEBUG, arg, "+OPTION");
				return show_help();
			}
			else if(streq(arg, "-c") || streq(arg, "--config")) {
				collect_pairs(arg, next,
					"Config FILE not specified!");
				i++;
			}
			else if(streq(arg, "-i") || streq(arg, "--install")) {
				if(streq(next, "NONE")) next = "bootstrap";
				collect_pairs(arg, next,
					"No TEMPLATE specified!");
				i++;
			} else {
				char buf[LOG_BUFFER_SIZE];
				sprintf(buf, "Unrecognized option: %s", arg);
				Log->print(LOG_ERROR, buf, "Args");
				return show_help();
			}
		}
		return EXIT_SUCCESS;
	}

	int Args::show_help() {
		fprintf(stderr, HELP_TEXT, progname, XSPS_CONFIG_DIR);
		return EINVAL;
	}

	void Args::collect_pairs(String key, String value, String err_msg) {
		Logger* Log = Logger::get_instance();
		if(streq(value, "NONE")) {
			Log->print(LOG_ERROR, err_msg, "Args");
			show_help();
		}
		pairs.insert(std::pair<String,String>(key, value));
		Log->print(LOG_DEBUG, key, "+OPTION");
		Log->print(LOG_DEBUG, value, "+VALUE");
	}

	String Args::HELP_TEXT = "\
Usage: %s [OPTIONS...] ACTION [TEMPLATE] [ACTION TEMPLATE...]\n\n\
 Options:\n\
  -h --help			    Display this usage help message.\n\
  -c --config	FILE	 (optional) Select alternative configuration file.\n\
				    [default: %s/xsps.conf]\n\
 Actions:\n\
  -i --install	TEMPLATE (optional) Install package from a TEMPLATE file from\n\
				    the available package templates stored in\n\
				    the `SRCPKGS' directory (see config).\n\
				    [default: bootstrap]\n\n\
 The default action is --install\n";

} // namespace xsps
