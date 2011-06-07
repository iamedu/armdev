#ifndef _ARMLDER_UTILS_H
#define _ARMLDER_UTILS_H

#define write_register(address, value) \
	(*((int *)address)) = value

#define read_register(address) \
	(*((int *)address))

#endif

