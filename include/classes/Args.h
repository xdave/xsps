#include "xsps_string.h"
#include <map>
#ifndef XSPS_ARGS_H
#define XSPS_ARGS_H 1

namespace xsps {

	class Args {
	public:
		static String HELP_TEXT;
		int argc;
		char** argv;
		String progname;
		std::map<String, String> pairs;

		Args(int&, char**&);
		~Args();

		int parse();
		int validate();
		int show_help();
		void collect_pairs(String, String, String);

	}; // class Args

} // namespace xsps

#endif // XSPS_ARGS_H
