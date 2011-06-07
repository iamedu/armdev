#ifndef ADDRESSING_H
#define ADDRESSING_H

#include <armux/processor.h>
#include <armux/types.h>

typedef struct ARMAddr {
	UWord bitmask;
	UWord expected;
	void (*execute)(ARMProc *, UWord, void *);
	struct ARMAddr *next;
} ARMAddr;

typedef struct ARMAddrDPReturn {
	Word shifter_operand;
	Word shifter_carry_out;
} ARMAddrDPReturn;

typedef struct ARMAddrLSCReturn {
	Word address;
	Word end_address;
	Word start_address;
} ARMAddrLSCReturn;

typedef struct ARMAddrLSReturn {
	Word address;
} ARMAddrLSReturn;

typedef struct ARMAddrMLSReturn {
	Word address;
} ARMAddrMLSReturn;

typedef struct ARMAddrLSMReturn {
	Word start_address;
	Word end_address;
} ARMAddrLSMReturn;

ARMAddr *new_addr(UWord, UWord, void *);
void append_addr(ARMAddr *, ARMAddr *);
ARMAddr *addr_modes_dp();
ARMAddr *addr_modes_ls();
ARMAddr *addr_modes_lsm();
ARMAddr *addr_modes_mls();
ARMAddr *addr_modes_lsc();
ARMAddr *fetch_addr(ARMAddr *, UWord);

//First DP addressing mode
void dp_addr1(ARMProc *, UWord, void *);
void dp_addr2(ARMProc *, UWord, void *);
void dp_addr3(ARMProc *, UWord, void *);
void dp_addr4(ARMProc *, UWord, void *);
void dp_addr5(ARMProc *, UWord, void *);
void dp_addr6(ARMProc *, UWord, void *);
void dp_addr7(ARMProc *, UWord, void *);
void dp_addr8(ARMProc *, UWord, void *);
void dp_addr9(ARMProc *, UWord, void *);
void dp_addr10(ARMProc *, UWord, void *);
void dp_addr11(ARMProc *, UWord, void *);

//LS addressing mode by Draidens"The Man'"(draiden.wordpress.com)
void ls_addr1(ARMProc *, UWord, void *);
void ls_addr2(ARMProc *, UWord, void *);
void ls_addr3(ARMProc *, UWord, void *);
void ls_addr4(ARMProc *, UWord, void *);
void ls_addr5(ARMProc *, UWord, void *);
void ls_addr6(ARMProc *, UWord, void *);
void ls_addr7(ARMProc *, UWord, void *);
void ls_addr8(ARMProc *, UWord, void *);
void ls_addr9(ARMProc *, UWord, void *);
//End LS addressing mode by Draidens"The Man'"(draiden.wordpress.com)

//MLS addressing mode by Draidens"The Man'"(draiden.wordpress.com)
void mls_addr1(ARMProc *, UWord, void *);
void mls_addr2(ARMProc *, UWord, void *);
void mls_addr3(ARMProc *, UWord, void *);
void mls_addr4(ARMProc *, UWord, void *);
void mls_addr5(ARMProc *, UWord, void *);
void mls_addr6(ARMProc *, UWord, void *);
//End MLS addressing mode by Draidens"The Man'"(draiden.wordpress.com)

//LSM addressing mode by Draidens"The Man'"(draiden.wordpress.com)
void lsm_addr1(ARMProc *, UWord, void *);
void lsm_addr2(ARMProc *, UWord, void *);
void lsm_addr3(ARMProc *, UWord, void *);
void lsm_addr4(ARMProc *, UWord, void *);
//End LSM addressing mode by Draidens"The Man'"(draiden.wordpress.com)

//LSC addresing mode

void lsc_addr1(ARMProc *, UWord, void *);
void lsc_addr2(ARMProc *, UWord, void *);
void lsc_addr3(ARMProc *, UWord, void *);
void lsc_addr4(ARMProc *, UWord, void *);

#endif

