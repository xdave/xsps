#include <common.h>
#include <xsps_string.h>
#include <parse_args.h>
#include <cstdio>
#include <cstdlib>
#include <getopt.h>

namespace xsps {

void print_usage(String progname) {
	fprintf(stdout, "Usage: %s %s%s%s%s%s",
		progname,
		"[OPTIONS...] ACTION TEMPLATE\n",
		"Options:\n",
		"  -h --help		Display this usage information.\n",
		"  -c --config FILE	Use an alternate config file.\n",
		"  -i --install		Perform the install action.\n");
	exit(1);
}

void parse_args(int argc, char **argv) {
	int c = 0;

	while (true) {
		int option_index = 0;
		static struct option long_options[] = {
			{ "help",	no_argument,		NULL, 'h' },
			{ "config",	required_argument,	NULL, 'c' },
			{ "install",	optional_argument,	NULL, 'i' },
			{ NULL,		0,			NULL,	0 }
		};

		c = getopt_long (argc, argv, "hc:i",
			long_options, &option_index);

		if(c == -1) { break; }

		switch(c) {
		case 0:
			// I don't understand this:
			if(long_options[option_index].flag != 0) { break; }
			printf("option %s", long_options[option_index].name);
			if (optarg) { printf(" with arg %s", optarg); }
			printf("\n");
			break;
		case 'h':
			print_usage(argv[0]);
			break;
		case 'c':
			printf("TODO: Set config file\n");
			break;
		case 'i':
			printf("TODO: Perform install action.\n");
			break;
		case '?':
			print_usage(argv[0]);
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

} // parse_args

}; // namespace xsps
