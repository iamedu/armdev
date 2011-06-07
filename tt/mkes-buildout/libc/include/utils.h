#ifndef _UTILS_H
#define _UTILS_H

#ifndef WORD_TYPES
#define WORD_TYPES

typedef int Word;
typedef short int Halfword;
typedef char Byte;

typedef unsigned int UWord;
typedef unsigned short int UHalfword;
typedef unsigned char UByte;

#endif

void hash(UWord *lword, UWord *rword);

#endif

