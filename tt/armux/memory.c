#include <armux/memory.h>
#include <stdlib.h>
#include <stdio.h>

Byte readMemBlockByte(void *memBlock, UWord addr) {
	ARMMemBlock *block;
	block = (ARMMemBlock *)memBlock;

	return block->memory[addr - block->base_addr];
}

Halfword readMemBlockHalfword(void *memBlock, UWord addr, Endianess end) {
	ARMMemBlock *block;
	block = (ARMMemBlock *)memBlock;
	UWord result = 0;
	UWord initAddr = addr - block->base_addr;
	UWord currAddr;
	int i;

	currAddr = initAddr;

	if(end == LittleEndian) {
		for(i = 0; i < 2; i++) {
			result |= block->memory[currAddr + i] << i * 8;
		}
	} else { 
		for(i = 1; i >= 0; i--) {
			result |= block->memory[currAddr + 1 - i] << i * 8;
		}
	}

	return result;
}

Word readMemBlockWord(void *memBlock, UWord addr, Endianess end) {
	ARMMemBlock *block;
	block = (ARMMemBlock *)memBlock;
	UWord result = 0;
	UWord initAddr = addr - block->base_addr;
	UWord currAddr;
	int i;

	currAddr = initAddr;

	if(end == LittleEndian) {
		for(i = 0; i < 4; i++) {
			result |= (block->memory[currAddr + i] << i * 8) &
			          (0xff << (i * 8));
		}
	} else { 
		for(i = 3; i >= 0; i--) {
			result |= (block->memory[currAddr + 3 - i] << i * 8) &
			          (0xff << (i * 8));
		}
	}

	return result;
}

void writeMemBlockByte(void *memBlock, UWord addr, Byte value) {
	ARMMemBlock *block;

	block = (ARMMemBlock *)memBlock;

	block->memory[addr - block->base_addr] = value;

}

void writeMemBlockHalfword(void *memBlock, UWord addr, Halfword value,
                   Endianess end) {
	ARMMemBlock *block;
	block = (ARMMemBlock *)memBlock;
	UWord initAddr = addr - block->base_addr;
	UWord currAddr;
	int i;
	currAddr = initAddr;

	if(end == LittleEndian) {
		for(i = 0; i < 2; i++) {
			block->memory[initAddr + i] = 
			          (value & (0x000000FF << (i * 8))) >> (i * 8);
		}
	} else { 
		for(i = 1; i >= 0; i--) {
			block->memory[initAddr + 1 - i] = 
			          (value & (0x000000FF << (i * 8))) >> (i * 8);
		}
	}
}

void writeMemBlockWord(void *memBlock, UWord addr, Word value,
                   Endianess end) {
	ARMMemBlock *block;
	block = (ARMMemBlock *)memBlock;
	UWord initAddr = addr - block->base_addr;
	UWord currAddr;
	int i;
	currAddr = initAddr;

	if(end == LittleEndian) {
		for(i = 0; i < 4; i++) {
			block->memory[currAddr + i] = 
			          (value & (0x000000FF << (i * 8))) >> (i * 8);
		}
	} else { 
		for(i = 3; i >= 0; i--) {
			block->memory[currAddr + 3 - i] = 
			          (value & (0x000000FF << (i * 8))) >> (i * 8);
		}
	}
}

ARMMemBlock *new_mem_block(Word base_addr, UWord size) {
	int i;
	ARMMemBlock *block = malloc(sizeof(ARMMemBlock));
	block->base_addr = base_addr;
	block->size = size;
	block->memory = malloc(sizeof(size));
	block->device = NULL;

	for(i = 0; i < size; i++) {
		block->memory[i] = 0;
	}

	block->readByte = &readMemBlockByte;
	block->readHalfword = &readMemBlockHalfword;
	block->readWord = &readMemBlockWord;

	block->writeByte = &writeMemBlockByte;
	block->writeHalfword = &writeMemBlockHalfword;
	block->writeWord = &writeMemBlockWord;

	return block;
}

ARMMemBlock *new_mem_block_shm(Word base_addr, Word size, char *addr) {
	ARMMemBlock *block = malloc(sizeof(ARMMemBlock));
	block->base_addr = base_addr;
	block->size = size;
	block->memory = addr;
	block->device = NULL;

	block->readByte = &readMemBlockByte;
	block->readHalfword = &readMemBlockHalfword;
	block->readWord = &readMemBlockWord;

	block->writeByte = &writeMemBlockByte;
	block->writeHalfword = &writeMemBlockHalfword;
	block->writeWord = &writeMemBlockWord;

	return block;
}

ARMMemNode *new_mem_node(void *node) {
	ARMMemNode *root;

	root = malloc(sizeof(ARMMemNode));

	root->value = node;
	root->next = NULL;

	return root;
}

void add_mem_block(ARMMemNode* root, void *mem_block) {
	ARMMemNode *node;

	node = root;

	while(node->next != NULL) 
		node = node->next;


	node->next = mem_block;
}

/*
 * Implementation for ARM memory system
 */
Byte readInterByte(MemInterface *inter, UWord addr) {
	ARMMemNode *iter = inter->root;
	ARMMemInterface *mem;
	Byte result;

	while(iter != NULL) {
		mem = iter->value;
		if(mem->base_addr <= addr &&
		  (addr < (mem->base_addr + mem->size))) {
		  	if(mem->device != NULL) {
				mem->device->lock(mem->device);
			}
			result = mem->readByte(mem, addr);
		  	if(mem->device != NULL) {
				mem->device->unlock(mem->device);
			}
			return result;
		}
		iter = iter->next;
	}

	return 0;
}

Halfword readInterHalfword(MemInterface *inter, UWord addr,
                               Endianess end) {
	ARMMemNode *iter = inter->root;
	ARMMemInterface *mem;
	Halfword result;

	while(iter != NULL) {
		mem = iter->value;
		if(mem->base_addr <= addr &&
		   addr < (mem->base_addr + mem->size)) {
		  	if(mem->device != NULL) {
				mem->device->lock(mem->device);
			}
			result = mem->readHalfword(mem, addr, end);
		  	if(mem->device != NULL) {
				mem->device->unlock(mem->device);
			}
			return result;
		}
		iter = iter->next;
	}

	return 0;
}

Word readInterWord(MemInterface *inter, UWord addr,
                   Endianess end) {
	ARMMemNode *iter = inter->root;
	ARMMemInterface *mem;
	Word result;

	while(iter != NULL) {
		mem = iter->value;
		if(mem->base_addr <= addr &&
		   addr < (mem->base_addr + mem->size)) {
		  	if(mem->device != NULL) {
				mem->device->lock(mem->device);
			}
			result = mem->readWord(mem, addr, end);
		  	if(mem->device != NULL) {
				mem->device->unlock(mem->device);
			}
			return result;

		}
		iter = iter->next;
	}

	return 0;
}

void writeInterByte(MemInterface *inter, UWord addr, Byte value) {
	ARMMemNode *iter = inter->root;
	ARMMemInterface *mem;

	while(iter != NULL) {
		mem = iter->value;
		if(mem->base_addr <= addr &&
		   addr < (mem->base_addr + mem->size)) {
		  	if(mem->device != NULL) {
				mem->device->lock(mem->device);
			}
			mem->writeByte(mem, addr, value);
		  	if(mem->device != NULL) {
				mem->device->unlock(mem->device);
				mem->device->tellWritten(mem->device, addr - mem->base_addr);
			}
			return;
		}
		iter = iter->next;
	}

}

void writeInterHalfword(MemInterface *inter, UWord addr, Halfword value,
                        Endianess end) {
	ARMMemNode *iter = inter->root;
	ARMMemInterface *mem;

	while(iter != NULL) {
		mem = iter->value;
		if(mem->base_addr <= addr &&
		   addr < (mem->base_addr + mem->size)) {
		  	if(mem->device != NULL) {
				mem->device->lock(mem->device);
			}
			mem->writeHalfword(mem, addr, value, end);
		  	if(mem->device != NULL) {
				mem->device->unlock(mem->device);
				mem->device->tellWritten(mem->device, addr - mem->base_addr);
			}
			return;
		}
		iter = iter->next;
	}

}

void writeInterWord(MemInterface *inter, UWord addr, Word value,
                    Endianess end) {
	ARMMemNode *iter = inter->root;
	ARMMemInterface *mem;

	while(iter != NULL) {
		mem = iter->value;
		if(mem->base_addr <= addr &&
		   addr < (mem->base_addr + mem->size)) {
		  	if(mem->device != NULL) {
				mem->device->lock(mem->device);
			}
			mem->writeWord(mem, addr, value, end);
		  	if(mem->device != NULL) {
				mem->device->unlock(mem->device);
				mem->device->tellWritten(mem->device, addr - mem->base_addr);
			}
			return;
		}
		iter = iter->next;
	}

}

MemInterface *memInterface() {
	MemInterface *inter;
	inter = malloc(sizeof(MemInterface));

	inter->root = new_mem_node(new_mem_block(0, 65536 * 2));

	inter->readByte = readInterByte;
	inter->readHalfword = readInterHalfword;
	inter->readWord = readInterWord;
	inter->writeByte = writeInterByte;
	inter->writeHalfword = writeInterHalfword;
	inter->writeWord = writeInterWord;

	return inter;
}

