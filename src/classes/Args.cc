#include <xsps_string.h>
#include <classes/Args.h>

namespace xsps {

	Args::Args(int& argc, char**& argv) {
		int i = 0;
		for (; i < argc; i++) {
			args.push_back(argv[i]);
		}
	}

	Args::~Args() {}

} // namespace xsps

