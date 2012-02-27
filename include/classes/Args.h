#include <xsps_string.h>
#include <Log.h>
#include <map>
#ifndef XSPS_ARGS_H
#define XSPS_ARGS_H 1

namespace xsps {

	class Args {
	public:
		static String HELP_TEXT;
		String progname;
		std::map<String, String> pairs;

		Args(int&, char**&, LogTypes&);
		~Args();

		void show_help();
		void collect_pairs(LogTypes&, String, String, String);

	}; // class Args

} // namespace xsps

#endif // XSPS_ARGS_H
