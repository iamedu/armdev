#include <pio.h>

void init() {
	unsigned int i;
	pioa_overwrite_per(0x00000240);
	pioa_overwrite_oer(0x00000240);
	pioa_overwrite_owdr(0xffffffff);
	pioa_overwrite_ower(0x00000240);
	while(1) {
		pioa_overwrite_odsr(0x00000000);
		for(i = 0; i < 0xfffff; i++);
		pioa_overwrite_odsr(0xffffffff);
		for(i = 0; i < 0xfffff; i++);
	}
}

