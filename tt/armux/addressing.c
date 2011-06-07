#include <armux/types.h>
#include <armux/addressing.h>
#include <stdlib.h>
#include <stdio.h>

ARMAddr *new_addr(UWord bitmask, UWord expected, void *func) {
	ARMAddr *inst = malloc(sizeof(ARMAddr));
	inst->bitmask = bitmask;
	inst->expected = expected;
	inst->execute = func;
	inst->next = NULL;
	return inst;
}

void append_addr(ARMAddr *root, ARMAddr *node) {
	ARMAddr*tmp;
	tmp = root;
	while(tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = node;
}

//Do not delete this functions
ARMAddr *addr_modes_dp() {
	ARMAddr *root;

	root = new_addr(0x0e000000, 0x02000000, dp_addr1);
	append_addr(root, new_addr(0x0e000ff0, 0x00000000, dp_addr2));
	append_addr(root, new_addr(0x0e000070, 0x00000000, dp_addr3));
	append_addr(root, new_addr(0x0e0000f0, 0x00000010, dp_addr4));
	append_addr(root, new_addr(0x0e000070, 0x00000020, dp_addr5));
	append_addr(root, new_addr(0x0e0000f0, 0x00000030, dp_addr6));
	append_addr(root, new_addr(0x0e000070, 0x00000040, dp_addr7));
	append_addr(root, new_addr(0x0e0000f0, 0x00000050, dp_addr8));
	append_addr(root, new_addr(0x0e000ff0, 0x00000060, dp_addr11));
	append_addr(root, new_addr(0x0e000070, 0x00000060, dp_addr9));
	append_addr(root, new_addr(0x0e0000f0, 0x00000070, dp_addr10));

	return root;
}

ARMAddr *addr_modes_ls() {
	ARMAddr *root;

	root = new_addr(0x0f200000, 0x05000000, ls_addr1);
	append_addr(root, new_addr(0x0f200ff0, 0x07000000, ls_addr2));
	append_addr(root, new_addr(0x0f200010, 0x07000000, ls_addr3));
	append_addr(root, new_addr(0x0f200000, 0x05200000, ls_addr4));
	append_addr(root, new_addr(0x0f200ff0, 0x07200000, ls_addr5));
	append_addr(root, new_addr(0x0f200010, 0x07200000, ls_addr6));
	append_addr(root, new_addr(0x0f200000, 0x04000000, ls_addr7));
	append_addr(root, new_addr(0x0f200ff0, 0x06000000, ls_addr8));
	append_addr(root, new_addr(0x0f200010, 0x06000000, ls_addr9));

	return root;
}

ARMAddr *addr_modes_mls() {
	ARMAddr *root;

	root = new_addr(0x0f600090, 0x01400090, mls_addr1);
	append_addr(root, new_addr(0x0f600f90, 0x01000090, mls_addr2));
	append_addr(root, new_addr(0x0f600090, 0x01600090, mls_addr3));
	append_addr(root, new_addr(0x0f600f90, 0x01200090, mls_addr4));
	append_addr(root, new_addr(0x0f600090, 0x00400090, mls_addr5));
	append_addr(root, new_addr(0x0f600f90, 0x00000090, mls_addr6));

	return root;
}

ARMAddr *addr_modes_lsm() {
	ARMAddr *root;
	
	root = new_addr(0x0f800000, 0x08800000, lsm_addr1);
	append_addr(root, new_addr(0x0f800000, 0x09800000, lsm_addr2));
	append_addr(root, new_addr(0x0f800000, 0x08000000, lsm_addr3));
	append_addr(root, new_addr(0x0f800000, 0x09000000, lsm_addr4));

	return root;
}

ARMAddr *addr_modes_lsc() {
	ARMAddr *root;
	root = new_addr(0x0f200000, 0x0d000000,lsc_addr1);
	append_addr(root, new_addr(0x0f200000, 0x0d200000, lsc_addr2));
	append_addr(root, new_addr(0x0f200000, 0x0c200000, lsc_addr3));
	append_addr(root, new_addr(0x0f200000, 0x0c000000, lsc_addr4));
	return root;
}

ARMAddr *fetch_addr(ARMAddr *root, UWord inst) {
	ARMAddr *tmp;

	tmp = root;
	while(tmp != NULL) {
		if((inst & tmp->bitmask) == tmp->expected)
			return tmp;
		tmp = tmp->next;
	}

	return NULL;
}

