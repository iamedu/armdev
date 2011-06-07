#ifndef _MEMORY_H
#define _MEMORY_H

#include <armux/types.h>
#include <armux/coprocessor.h>
#include <armux/connects.h>

typedef struct ARMMemNode {
	struct ARMMemNode *next;
	void *value;
} ARMMemNode;

typedef enum Endianess {
	LittleEndian,
	BigEndian,
} Endianess;

typedef struct MemInterface {
	ARMMemNode *root;
	Byte (*readByte)(struct MemInterface *, UWord);
	Halfword (*readHalfword)(struct MemInterface *, UWord, Endianess);
	Word (*readWord)(struct MemInterface *, UWord, Endianess);
	void (*writeByte)(struct MemInterface *, UWord, Byte);
	void (*writeHalfword)(struct MemInterface *, UWord, Halfword,
	                      Endianess);
	void (*writeWord)(struct MemInterface *, UWord, Word, Endianess);
} MemInterface;

typedef struct ARMMemInterface {
	Word base_addr;
	UWord size;
	Device *device;
	Byte (*readByte)(void *, UWord);
	Halfword (*readHalfword)(void *, UWord, Endianess);
	Word (*readWord)(void *, UWord, Endianess);
	void (*writeByte)(void *, UWord, Byte);
	void (*writeHalfword)(void *, UWord, Halfword, Endianess);
	void (*writeWord)(void *, UWord, Word, Endianess);
} ARMMemInterface;

typedef struct ARMMemBlock {
	Word base_addr;
	UWord size;
	Device *device;
	Byte (*readByte)(void *, UWord);
	Halfword (*readHalfword)(void *, UWord, Endianess);
	Word (*readWord)(void *, UWord, Endianess);
	void (*writeByte)(void *, UWord, Byte);
	void (*writeHalfword)(void *, UWord, Halfword, Endianess);
	void (*writeWord)(void *, UWord, Word, Endianess);
	char *memory;
} ARMMemBlock;

MemInterface *memInterface();

ARMMemBlock *new_mem_block(Word, UWord);
ARMMemBlock *new_mem_block_shm(Word, Word, char *);

ARMMemNode *new_mem_node(void *);
void add_mem_block(ARMMemNode*, void *);

#endif

