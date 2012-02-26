#include <xsps_string.h>
#include <vector>
#ifndef XSPS_ARGS_H
#define XSPS_ARGS_H 1

namespace xsps {

	class Args {
	public:
		std::vector<String> args;

		Args(int&, char**&);
		~Args();

	}; // class Args

} // namespace xsps

#endif // XSPS_ARGS_H
