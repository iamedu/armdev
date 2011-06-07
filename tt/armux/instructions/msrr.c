#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void msrr_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un msrr\n");
#endif
        UWord mask;
        Word operand, _bit_immediate, rotate_imm, Rm, field_mask, R, status_mode, byte_mask, byte1, byte2, byte3, byte4;
        if( !cond(proc, instruction) )
                return;
        _bit_immediate = get_bits(instruction, 0, 8);
        rotate_imm = get_bits(instruction, 8, 4);
        Rm = get_bits(instruction, 0, 4);
        field_mask = get_bits(instruction, 16, 4);
        R = get_bits(instruction, 22, 1);
        if( get_bits(instruction, 25, 1, 0))
                operand = ror(_bit_immediate, rotate_imm * 2);
        else
                operand = Rm;
        if( (operand & 0x06FFFF00) != 0 )
#ifdef DEBUG
                printf("UNPREDICTABLE\n");
#endif
        if( get_bits(field_mask, 0, 1) ) byte1 = 0x000000FF; else byte1 = 0x00000000;
        if( get_bits(field_mask, 1, 1) ) byte2 = 0x0000FF00; else byte2 = 0x00000000;
        if( get_bits(field_mask, 2, 1) ) byte3 = 0x00FF0000; else byte3 = 0x00000000;
        if( get_bits(field_mask, 3, 1) ) byte4 = 0xFF000000; else byte4 = 0x00000000;
        byte_mask = byte1 | byte2 | byte3 | byte4;
        status_mode = get_status(proc, status_m);
        if( !R ){
                if( status_mode == mode_fiq || status_mode == mode_irq || status_mode == mode_svc || status_mode == mode_abt || status_mode == mode_und )
                        if( (operand & 0x01000020) != 0){
#ifdef DEBUG
                                printf("UNPREDICTABLE\n");
#endif
                        }else
                                mask = byte_mask & (0xF8000000 | 0x0000000F);
                else
                        mask = byte_mask & 0xF8000000;
                *proc->cpsr = ( *proc->cpsr & ~mask ) | (operand & mask);
        }else
                if( proc->spsr != NULL ){
                        mask = byte_mask & (0xF8000000 | 0x0000000F | 0x01000020);
                        *proc->spsr = (*proc->spsr & ~mask) | (operand & mask);
                }else{
#ifdef DEBUG
                        printf("UNPREDICTABLE\n");
#endif
                }
}

