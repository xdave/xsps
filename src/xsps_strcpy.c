#include <stdlib.h>
#include <string.h>

#include "xsps.h"

char** xstrcpy(char** s1, char* s2) {
	size_t size = strlen(s2);
	if(s2[size-1] != '\0') size++;
	if((*s1 != NULL) && (strlen(*s1) != 0)) free(*s1);
	if((*s1 = malloc(size)) != NULL) {
		strncpy(*s1, s2, size);
		if(size > 0) (*s1)[size-1] = '\0';
		return s1;
	}
	fprintf(stderr, "WARNING: \"%s\" not copied!\n", s2);
	return s1;
}

