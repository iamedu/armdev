#include <string.h>

char *strcpy(char *dest, const char *src) {
	char *it_src;
	char *it_dest;

	it_src  = (char *)src;
	it_dest = dest;

	while(1) {
		*it_dest = *it_src;

		if(*it_dest = '\0') {
			break;
		}

		it_src++;
		it_dest++;
	}

	return dest;
}

size_t strlen(const char *s) {
	size_t count;
	char *it;

	count = 0;
	it = (char *)s;

	while(*it != '\0') {
		count++;
	}

	return count;
}

int strcmp(const char *s1, const char *s2) {
	int i;
	size_t l1;
	size_t l2;
	size_t max;
	
	l1 = strlen(s1);
	l2 = strlen(s2);

	max = (l1>l2)?l1:l2;

	for(i = 0; i < max; i++) {
		if(s1[i] != s2[i]) {
			return s1[i] - s2[i];
		}
	}

	return l1 - l2;
}

void *memset(void *s, int c, size_t n) {
	int i;
	unsigned char *it;

	it = (unsigned char *)s;
	for(i = 0; i < n; i++) {
		it[i] = (unsigned char)c;
	}

}

void *memcpy(void *s1, const void *s2, size_t n) {
	int i;

	unsigned char *c1;
	unsigned char *c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;

	for(i = 0; i < n; i++) {
		c1[i] = c2[i];
	}

	return s1;
}

