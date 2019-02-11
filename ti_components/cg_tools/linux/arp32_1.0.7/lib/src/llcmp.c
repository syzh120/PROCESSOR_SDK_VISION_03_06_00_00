/*****************************************************************************/
/* LLCMP.C   v1.0.7 - Long Long int compare                                  */
/*                                                                           */
/* Copyright (c) 2010-2015 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

#include <limits.h>
#include <stdio.h>
#include <stdint.h>

typedef unsigned int uint;

/* return <0 if left <  right                                                */
/* return  0 if left == right                                                */
/* return >0 if left >  right                                                */
int __arp32abi_cmpllu(uint64_t x1, uint64_t x2)
{
    unsigned int x1_lo, x1_hi, x2_lo, x2_hi;

    /* Split off 32-bit values */
    x1_lo = (uint) x1;
    x2_lo = (uint) x2;
    x1_hi = x1 >> 32;
    x2_hi = x2 >> 32;

    if      (x1_hi > x2_hi) return 1;
    else if (x1_hi < x2_hi) return -1;
    else if (x1_lo > x2_lo) return 1;
    else if (x1_lo < x2_lo) return -1;

    return 0;
}

int __arp32abi_cmplls(int64_t x1, int64_t x2)
{
    int x1_hi, x2_hi;
    unsigned int x1_lo, x2_lo;

    /* Split off 32-bit values */
    x1_lo = (uint) x1;
    x2_lo = (uint) x2;
    x1_hi = x1 >> 32;
    x2_hi = x2 >> 32;

    if      (x1_hi > x2_hi) return 1;
    else if (x1_hi < x2_hi) return -1;
    else if (x1_lo > x2_lo) return 1;
    else if (x1_lo < x2_lo) return -1;

    return 0;
}
