/*
 * Copyright (c) 2011-2014, Texas Instruments Incorporated
 * Copyright (c) 2011, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Google Inc. nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Copyright Iliyan Malchev Google Inc. 2011.
 */

/*
 *  ======== StackDbg.c ========
 */

#include <xdc/runtime/Startup.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "package/internal/StackDbg.xdc.h"

/*
 * We're looking for either a 32-bit BL <imm> or a 16-bit BLX Rm
 * instruction.  Since this code is not compiled with
 * internetworking and runs only in Thumb2 mode, the BLX Rm is
 * actually a BL Rm.  Also, the J bits in the 32-bit BL <imm>
 * instruction are both 1, because of Thumb2.
 *
 * If bits [15:11] of the halfword being decoded take any of the
 * following values, the halfword is the first halfword of a 32-bit
 * instruction:
 *    0b11101
 *    0b11110
 *    0b11111.
 *
 * The only 32-bit insruction we're interested in is BL <imm>
 *
 *   3                   2                   1                   0
 * 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * ---------------------------------------------------------------
 * 1 1 1 1 0 - - - - - - - x x x x 1 x x x x x x x x x x x x x x x
 *       op1 op2                   op
 *                                   1 x x
 *       1 0                       1 op1
 * 1 1 1 1 0 S a a a a a a a a a a 1 1 j 0 j a a a a a a a a a a 0
 * ---------------------------------------------------------------
 * 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 0 1 0 0 0 0 0 0 0 0 0 0 0 <-- set
 *                                       ^
 *                                       +-- 1: BL, 0: BLX
 * 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 <-- clr
 *
 * 32-bit set mask: common     0xf000e800 (both J bits are set--armv7)
 *                  BLX bit:   0x00001000
 * 32-bit clr mask: BLX: 0x08000000, BL: 0x08001001
 *
 *   3                   2                   1                   0
 * 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * ---------------------------------------------------------------
 * x x x x x S 1 1 1 1 1 1 1 1 1 1 x x x x x 1 1 1 1 1 1 1 1 1 1 x <-- BLX
 * x x x x x S 1 1 1 1 1 1 1 1 1 1 x x x x x 1 1 1 1 1 1 1 1 1 1 1 <-- BL
 *
 * value mask: BL: 0x03ff07fe, BLX: 0x03ff07fe
 *
 * imm10h:
 *   0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 *   imm10h_mask: 03ff0000
 *   imm10h_val      = imm10h_mask >> 4
 *
 * imm10l_bl:
 *   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1
 *   imm10l_bl_mask  = 000007ff
 *   imm10l_bl_val   = imm10l_bl_mask << 1
 *
 * imm10l_blx:
 *   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 0
 *   imm10l_blx_mask = 000007fe
 *   imm10l_blx_val  = imm10l_blx_mask << 1
 *
 * val_bl  = imm10h_val | imm10l_bl_val
 * val_blx = imm10h_val | imm10l_blx_val
 */
static Int __decode_bl32(UInt pc, UInt op, UInt *target)
{
    UInt imm;
    UInt sign;

    if ((op & 0xf000e800) == 0xf000e800) {
        /* BL or BLX */
        if (op & (1<<12)) {
            if (!(op & 0x08000000)) {
                /* BL */
                imm = ((op & 0x03ff0000) >> 4) | ((op & 0x000007ff) << 1);
            }
            else {
                return 0;
            }
        }
        else {
            if (!(op & 0x08001001)) {
                /* BLX */
                imm = ((op & 0x03ff0000) >> 4) | ((op & 0x000007fe) << 1);
            }
            else {
                return 0;
            }
        }

        sign = !!(op & 0x04000000);
        if (sign) {
            Int simm = (Int)(imm << 10);
            simm >>= 10;
            imm = (UInt)simm;
        }

        imm = (UInt)((Int)pc + (Int)imm);
        imm += 4;

        *target = imm;
        return 1;
    }

    return 0;
}

static Int decode_bl32(UInt pc, UInt op, UInt *target)
{
    if (__decode_bl32(pc, op, target)) {
        return 1;
    }
    op = (op >> 16) | (op << 16);
    return __decode_bl32(pc, op, target);
}

Void StackDbg_walkStack(UInt base, UInt size, UInt start,
                        StackDbg_VisitFuncPtr visit, Ptr user)
{
    UInt                top;
    UInt                *inst;
    UInt                op;
    StackDbg_StackEntry e;
    Bool more;

    size = (size + 3) & ~3;
    top = base + size;
    start = start & ~3;
    more = TRUE;

    for (; start < top && more; start += sizeof(UShort)) {
        UInt val = *((UInt *)start);
        if ((val & 1) && module->codeBegin <= val && val < module->codeEnd) {

            inst = (UInt *)((val - 4) & ~1);
            op = *inst;

            e.instr  = (UInt)inst;
            e.op     = op;
            e.ret    = val;
            e.sp     = (UInt)start;
            e.bogus  = 0;

            if (decode_bl32((UInt)inst, op, &e.target)) {
                more = visit(&e, user);
            }
            else if ((op & 0x47800000) == 0x47800000 ||
                     (op & 0x00004780) == 0x00004780) {
                e.target = 0;
                more = visit(&e, user);
            }
            else {
                e.bogus  = 1;
                more = visit(&e, user);
            }
        }
    }
}
