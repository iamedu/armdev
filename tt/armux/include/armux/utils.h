#ifndef UTILS_H
#define UTILS_H
#define asr32(x,y) asr(x,y,32)
#define ror32(x,y) ror(x,32,y)
#define count32(x) count(x,32)

#include <armux/types.h>
#include <armux/processor.h>

Word get_bits(UWord, Word, Word);
UWord set_bits(UWord, Word, Word, UWord);
Word cond(ARMProc *, UWord);
Word ror(Word, Word, Word);
Word asr(Word, Word, Word);
Word count(Word, Word);
Word SignExtend(Word, Word);
Word SignExtend30(Word, Word);
Word AddCarryFrom(Word,Word,Word *);
Word OverflowFrom(Word,Word);
Word SubWithBorrow(Word,Word,Word *);
Word msb_position(Word);
void Mul64(Word,Word,Word *,Word *);
#endif

