#include <common.h>
#include <Log.h>
#include <parse_args.h>

int main(int argc, char **argv) {
	xsps::LogTypes LOG;
	xsps::Log(LOG.WARN, "This program is currently useless.", "FIXME");
	return xsps::parse_args(LOG, argc, argv);
}
