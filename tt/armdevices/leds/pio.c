#include <pio.h>
#include <devices.h>

void pioa_overwrite_per(int value) {
	int *pioa = (int *)PIOA_BASE;
	*pioa = value;
}

void pioa_overwrite_oer(int value) {
	int *pioa_oer = (int *)(PIOA_BASE + PIO_OER);
	*pioa_oer = value;
}

void pioa_overwrite_odsr(int value) {
	int *pioa_odsr = (int *)(PIOA_BASE + PIO_ODSR);
	*pioa_odsr = value;
}

void pioa_overwrite_ower(int value) {
	int *pioa_ower = (int *)(PIOA_BASE + PIO_OWER);
	*pioa_ower = value;
}

void pioa_overwrite_owdr(int value) {
	int *pioa_owdr = (int *)(PIOA_BASE + PIO_OWDR);
	*pioa_owdr = value;
}

