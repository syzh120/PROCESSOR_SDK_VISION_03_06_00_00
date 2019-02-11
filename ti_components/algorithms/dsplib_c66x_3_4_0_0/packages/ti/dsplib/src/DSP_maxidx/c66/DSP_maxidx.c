/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  DSPLIB  DSP Signal Processing Library                                  */
/*                                                                         */
/*  This library contains proprietary intellectual property of Texas       */
/*  Instruments, Inc.  The library and its source code are protected by    */
/*  various copyrights, and portions may also be protected by patents or   */
/*  other legal protections.                                               */
/*                                                                         */
/*  This software is licensed for use with Texas Instruments TMS320        */
/*  family DSPs.  This license was provided to you prior to installing     */
/*  the software.  You may review this license by consulting the file      */
/*  TI_license.PDF which accompanies the files in this library.            */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*                                                                         */
/* DSP_maxidx.c -- Maximum Vector Value                                    */
/*                 Intrinsic C Implementation                              */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/*    USAGE                                                                */
/*        This routine is C callable, and has the following C prototype:   */
/*                                                                         */
/*        int DSP_maxidx (                                                 */
/*            const short *x,                                              */
/*            int nx                                                       */
/*        );                                                               */
/*                                                                         */
/*        x       = pointer to input data                                  */
/*        nx      = number of samples                                      */
/*        return  = max index                                              */
/*                                                                         */
/*    DESCRIPTION                                                          */
/*       This routine finds the maximum value of the vector x[ ] and       */
/*       returns the index of that value.                                  */
/*       The input array is treated as 16 separate "columns" that are      */
/*       interleaved throughout the array.  If values in different columns */
/*       are equal to the maximum value, then the element in the leftmost  */
/*       column is returned.  If two values within a column are equal to   */
/*       the maximum, then the one with the lower index is returned.       */
/*       Column takes precedence over index.                               */
/*                                                                         */
/*       int maxidx(short *x, int nInputs);                                */
/*       {                                                                 */
/*        int    i;                                                        */
/*        int    maxLocation;                                              */
/*        short  maxValue;                                                 */
/*        maxLocation = nInputs - 1;                                       */
/*        maxValue = Input[maxLocation];                                   */
/*        for (i = nInputs-2; i >= 0; i--) {                               */
/*                if (maxValue < Input[i]) {                               */
/*                        maxValue = Input[i];                             */
/*                        maxLocation = i;                                 */
/*                }                                                        */
/*        }                                                                */
/*        return  maxLocation;                                             */
/*       }                                                                 */
/*                                                                         */
/*       The above C code is a general implementation without restrictions */
/*       The assembly code may have some restrictions, as noted below.     */
/*                                                                         */
/*    TECHNIQUES                                                           */
/*       The code is unrolled 16 times to enable full bandwidth of LDDW    */
/*       and MAX2 instructions to be utilized. This splits the search into */
/*       16 subranges. The global maximum is then found from the list of   */
/*       maximums of the subsranges.                                       */
/*       Then using this offset from the subranges, the global maximum and */
/*       the index of it are found using a simple match.                   */
/*       For common maximums in multiple ranges, the index will be         */
/*       different to the above C code.                                    */
/*                                                                         */
/*    ASSUMPTIONS                                                          */
/*       The input data are stored on double-word aligned boundaries.      */
/*       nx must be a multiple of 16 and >= 32                             */
/*                                                                         */
/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/  */ 
/*                                                                         */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*                                                                         */
/*    Redistributions of source code must retain the above copyright       */
/*    notice, this list of conditions and the following disclaimer.        */
/*                                                                         */
/*    Redistributions in binary form must reproduce the above copyright    */
/*    notice, this list of conditions and the following disclaimer in the  */
/*    documentation and/or other materials provided with the               */
/*    distribution.                                                        */
/*                                                                         */
/*    Neither the name of Texas Instruments Incorporated nor the names of  */
/*    its contributors may be used to endorse or promote products derived  */
/*    from this software without specific prior written permission.        */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                         */
/* ======================================================================= */

#pragma CODE_SECTION(DSP_maxidx, ".text:optimized");

#include "DSP_maxidx.h"

int DSP_maxidx (
    const short * x,
    int           nx
)
{
    short Max[16];
    int   i, maxLocation, maxIndex, maxValue;

    long long m3m2m1m0, m7m6m5m4, mbmam9m8, mfmemdmc;
    long long input_dword0, input_dword1, input_dword2, input_dword3;

    /*--------------------------------------------------------------------*/
    /* Infrom the compiler that the "x", "Max" arrays are double word     */
    /* aligned.                                                           */
    /*--------------------------------------------------------------------*/
    _nassert((int) x % 16 == 0);
    _nassert((int) Max % 16 == 0);

    /*--------------------------------------------------------------------*/
    /* Load the data from the first 16 values, to initialize the maximums */
    /* for 16 parallel searches. The individual words within a double     */
    /* word are accessed using the _lo and _hi intrinsics.                */
    /*--------------------------------------------------------------------*/
    m3m2m1m0 = _amem8_const(&x[0]);
    m7m6m5m4 = _amem8_const(&x[4]);
    mbmam9m8 = _amem8_const(&x[8]);
    mfmemdmc = _amem8_const(&x[12]);

    /*--------------------------------------------------------------------*/
    /* For all inputs past the first 16, perform parallel searches for    */
    /* the maximums. Each iteration of the loop loads 16 new values and   */
    /* updates the maximum within each of the 16 columns. Inform the co-  */
    /* mpiler that the following loop iterates at least twice.            */
    /*--------------------------------------------------------------------*/

    #pragma MUST_ITERATE(1,,1);
    for (i = 16; i < nx; i += 16) {
        /*----------------------------------------------------------------*/
        /* Load input data as double words and access low and high words  */
        /* using the _lo and _hi intrinsic.                               */
        /*----------------------------------------------------------------*/

        input_dword0 = _amem8_const(&x[i +  0]);
        input_dword1 = _amem8_const(&x[i +  4]);
        input_dword2 = _amem8_const(&x[i +  8]);
        input_dword3 = _amem8_const(&x[i + 12]);

        /*---------------------------------------------------------------*/
        /* Update current set of maximums using the max2 instruction     */
        /*---------------------------------------------------------------*/
        m3m2m1m0 = _dmax2(m3m2m1m0, input_dword0);
        m7m6m5m4 = _dmax2(m7m6m5m4, input_dword1);
        mbmam9m8 = _dmax2(mbmam9m8, input_dword2);
        mfmemdmc = _dmax2(mfmemdmc, input_dword3);
    }

    /*-------------------------------------------------------------------*/
    /* Store local maximums within each of the 16 columns to the Max     */
    /* array.                                                            */
    /*-------------------------------------------------------------------*/
    _amem8(&Max[0])  = m3m2m1m0;
    _amem8(&Max[4])  = m7m6m5m4;
    _amem8(&Max[8])  = mbmam9m8;
    _amem8(&Max[12]) = mfmemdmc;

    /*-------------------------------------------------------------------*/
    /* Search for largest value, global max and where it occurs, 1 of 16 */
    /*-------------------------------------------------------------------*/
    maxValue = Max[0];
    maxIndex = 0;

    for (i = 1; i < 16; i++) {
        if (Max[i] > maxValue) {
            maxValue = Max[i];
            maxIndex = i;
        }
    }

    /*-------------------------------------------------------------------*/
    /* Use maxIndex to find the column to search within. Search within   */
    /* the column to find the index of the element in the vector.        */
    /*-------------------------------------------------------------------*/
    maxLocation = maxIndex;

    #pragma MUST_ITERATE(1,,1);
    for (i = nx - 16 + maxIndex; i >= 0; i -= 16)
        if (x[i] == maxValue) maxLocation = i;

    /*-------------------------------------------------------------------*/
    /* Return the location where the maximum value was found             */
    /*-------------------------------------------------------------------*/
    return maxLocation;
}

/* ======================================================================== */
/*  End of file:  DSP_maxidx.c                                              */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

