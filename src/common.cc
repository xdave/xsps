#include <common.h>

namespace xsps {

	bool streq(const char* s1, const char* s2) {
		if(strcmp(s1, s2) == 0) return true;
		else return false;
	}

}
