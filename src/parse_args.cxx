#include <common.h>
#include <xsps_string.h>
#include <parse_args.h>
#include <cstdio>
#include <cstdlib>
#include <getopt.h>

namespace xsps {

int print_usage(LogTypes l, String progname) {
	char buf[80];
	sprintf(buf, "%s [OPTIONS...] [TEMPLATE]", progname);
	Log(l.INFO, buf, "Usage");
	Log(l.INFO, "Options:", "Usage");
	Log(l.INFO, "  -c --config FILE\tUse config file FILE.", "Usage");
	Log(l.INFO, "  -i --install\tPerform the install action.", "Usage");
	Log(l.INFO, "  -h --help\t\tDisplay this help information.", "Usage");
	Log(l.INFO, "Defaults:", "Usage");
	Log(l.INFO, "  `-c' default: `./config/xsps.conf'.", "Usage");
	Log(l.INFO, "  `-i' default: `bootstrap'.", "Usage");
	return 1;
}

int parse_args(LogTypes l, int argc, char **argv) {
	if(argc < 2) {
		return print_usage(l, argv[0]);
	}
	int c = 0;

	while (true) {
		int option_index = 0;
		static struct option long_options[] = {
			{ "config",	required_argument,	NULL, 'c' },
			{ "install",	optional_argument,	NULL, 'i' },
			{ "help",	no_argument,		NULL, 'h' },
			{ NULL,		0,			NULL,  0  }
		};

		c = getopt_long (argc, argv, "c:ih",
			long_options, &option_index);

		if(c == -1) { break; }

		switch(c) {
		char buf[80];
		case 0:
			// I don't understand this:
			if(long_options[option_index].flag != 0) { break; }
			printf("option %s", long_options[option_index].name);
			if (optarg) { printf(" with arg %s", optarg); }
			printf("\n");
			break;
		case 'h':
			sprintf(buf, "+option: -%c", c);
			Log(l.DEBUG, buf, "parse_args");
			return print_usage(l, argv[0]);
			break;
		case 'c':
			sprintf(buf, "+option: -%c", c);
			Log(l.DEBUG, buf, "parse_args");
			printf("TODO: Set config file\n");
			break;
		case 'i':
			sprintf(buf, "+option: -%c", c);
			Log(l.DEBUG, buf, "parse_args");
			printf("TODO: Perform install action.\n");
			break;
		case '?':
			return print_usage(l, argv[0]);
			break;
		default:
			abort();

		} // switch
	} // while

	if (optind < argc) {
		printf("non-option argv stuff: ");
		while (optind < argc) {
			printf("%s ", argv[optind++]);
		}
		putchar('\n');
	}
	return 0;

} // parse_args

}; // namespace xsps
