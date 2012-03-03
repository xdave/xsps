#include <stdlib.h>
#include <string.h>

#include "xsps.h"

char** xstrcpy(char** s1, char* s2) {
	size_t size = strlen(s2) + 1;
	if((*s1 != NULL) && (strlen(*s1) != 0)) free(*s1);
	if((*s1 = malloc(size)) != NULL) {
		strncpy(*s1, s2, size);
		return s1;
	}
	return NULL;
}

