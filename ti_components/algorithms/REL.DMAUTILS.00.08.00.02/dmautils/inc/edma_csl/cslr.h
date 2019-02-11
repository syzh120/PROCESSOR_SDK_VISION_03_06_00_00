/*
*
* Copyright (c) 2003-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/*****************************************************\
 *  Restricted rights to use, duplicate or disclose  *
 *  this   code   are  granted   through  contract.  *
 *                                                   *
 * "@(#) PSP/CSL  3.0.0.0  (2003-09-30)              *
\*****************************************************/

/* Register layer central -- contains field-manipulation macro definitions */

#ifndef CSLR_H_
#define CSLR_H_

/* the "expression" macros */

/* the Field MaKe macro */

/* CHECK_MISRA("-19.13")  -> Disable rule 19.13  */
/* MISRA.DEFINE.SHARP:  The # and ## operators should not be used  */
/*  The places in which order of evaluation has no side effects could be a waiver.    */
#define CSL_FMK(PER_REG_FIELD, val)                                         \
    (((val) << (CSL_##PER_REG_FIELD##_SHIFT)) & (CSL_##PER_REG_FIELD##_MASK))

/* the Field EXTract macro */
#define CSL_FEXT(reg, PER_REG_FIELD)                                        \
    (((reg) & CSL_##PER_REG_FIELD##_MASK) >> CSL_##PER_REG_FIELD##_SHIFT)

/* the Field INSert macro */
#define CSL_FINS(reg, PER_REG_FIELD, val)                                   \
    ((reg) = ((reg) & (~CSL_##PER_REG_FIELD##_MASK))                          \
    | CSL_FMK(PER_REG_FIELD, val))


/* the "token" macros */

/* the Field MaKe (Token) macro */
#define CSL_FMKT(PER_REG_FIELD, TOKEN)                                      \
    CSL_FMK(PER_REG_FIELD, (CSL_##PER_REG_FIELD##_##TOKEN))

/* the Field INSert (Token) macro */
#define CSL_FINST(reg, PER_REG_FIELD, TOKEN)                                \
    CSL_FINS((reg), (PER_REG_FIELD), (CSL_##PER_REG_FIELD##_##TOKEN))
/*RESET_MISRA("19.13")  -> Reset rule 19.13 for MISRA.DEFINE.SHARP */


/* the "raw" macros */

/* the Field MaKe (Raw) macro */
#define CSL_FMKR(msb, lsb, val)                                             \
    ((uint32_t)((uint32_t)((val) & ((uint32_t)((uint32_t)1U << ((msb) - (lsb) + 1U)) - 1U)) << (lsb)))

/* the Field EXTract (Raw) macro */
#define CSL_FEXTR(reg, msb, lsb)                                            \
    (((reg) >> (lsb)) & ((1 << ((msb) - (lsb) + 1)) - 1))

/* the Field INSert (Raw) macro */
#define CSL_FINSR(reg, msb, lsb, val)                                       \
    ((reg) = ((reg) &~ (((1 << ((msb) - (lsb) + 1)) - 1) << (lsb)))         \
    | CSL_FMKR(msb, lsb, val))

#endif /* CSLR_H_ */

/* Rev.No.   Date/Time               ECN No.          Modifier      */
/* -------   ---------               -------          --------      */

/* 4          Aug 10:09:12 9         2272             xkeshavm      */
/*                                                                  */
/* To upload API CSL 0.51 Release                                   */
/********************************************************************/
