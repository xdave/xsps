#include <common.h>
#include <xsps_string.h>
#include <classes/Args.h>
#include <Log.h>
#include <cstdlib>
#include <cstring>

namespace xsps {

	Args::Args(int& argc, char**& argv, LogTypes& LOG) {
		progname = argv[0];
		if(argc == 1) {
			Log(LOG.ERROR, "No arguments given!", "Args");
			show_help();
		}

		for (int i = 1; i < argc; i++) {
			String arg = argv[i];
			String next = argv[i+1];
			if(next == NULL) next = "NONE";
			if(streq(arg, "-h") || streq(arg, "--help")) {
				Log(LOG.DEBUG, arg, "+OPTION");
				show_help();
			}
			else if(streq(arg, "-c") || streq(arg, "--config")) {
				collect_pairs(LOG, arg, next,
					"Config FILE not specified!");
				i++;
			}
			else if(streq(arg, "install")) {
				if(streq(next, "NONE")) next = "bootstrap";
				collect_pairs(LOG, arg, next,
					"No TEMPLATE specified!");
				i++;
			} else {
				char buf[80];
				sprintf(buf, "Unrecognized option: %s", arg);
				Log(LOG.ERROR, buf, "Args");
				show_help();
			}
		}

	}

	void Args::show_help() {
		printf(HELP_TEXT, progname, XSPS_CONFIG_DIR);
		exit(1);
	}

	void Args::collect_pairs(LogTypes& LOG, String key, String value,
				String err_msg) {
		if(streq(value, "NONE")) {
			Log(LOG.ERROR, err_msg, "Args");
			show_help();
		}
		pairs.insert(std::pair<String,String>(key, value));
		Log(LOG.DEBUG, key, "+OPTION");
		Log(LOG.DEBUG, value, "+VALUE");
	}

	String Args::HELP_TEXT = "\
Usage: %s [OPTIONS...] ACTION [TEMPLATE] [ACTION TEMPLATE...]\n\
Options:\n\
  -h --help		 (optional) Display this usage help message.\n\
  -c --config	FILE	 (optional) Select alternative configuration file.\n\
				    [default: %s/xsps.conf]\n\
Actions:\n\
  install	TEMPLATE (optional) Install package from a TEMPLATE file from\n\
				    the available package templates stored in\n\
				    the `SRCPKGS' directory (see config).\n\
				    [default: bootstrap]\n\
  ... etc, etc..\n";

	Args::~Args() {}


} // namespace xsps
