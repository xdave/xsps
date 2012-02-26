#include <common.h>
#include <Log.h>
#include <parse_args.h>

using namespace xsps;

int main(int argc, char **argv) {
	LogTypes l;
	Log(l.WARN, "This program is currently useless.", "FIXME");
	return parse_args(l, argc, argv);
}
