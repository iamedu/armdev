#include <stdlib.h>

int atoi(const char *nptr) {
	char *ptr = (char *)nptr;
	int result = 0;

	while(1) {
		result += *ptr - '0';
		ptr++;
		if(*ptr == '\0')
			break;
		result *= 10;
	}

	return result;
}


