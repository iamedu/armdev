#ifdef _ASSERT_H
#undef _ASSERT_H
#undef assert
#endif

#define _ASSERT_H

#include <stdlib.h>

#ifdef NDEBUG
//Define assert if NDEBUG
#define assert(ignore)((void) 0)
#else
//We want to debug
#define assert(expression) \
	if(((int)(expression)) == 0) { \
		abort(); \
	}
#endif


