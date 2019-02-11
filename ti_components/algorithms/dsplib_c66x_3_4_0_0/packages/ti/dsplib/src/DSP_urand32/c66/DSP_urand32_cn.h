/* ======================================================================= */
/* DSP_urand32_cn.h -- Natural C source interface header file              */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (c) 2011 Mutsuo Saito, Makoto Matsumoto, Hiroshima            */
/* University and The University of Tokyo. All rights reserved.            */
/*                                                                         */
/* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/  */
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

#ifndef DSP_URAND32_CN_H_
#define DSP_URAND32_CN_H_

/*
 *     This function is used to seed the uniformly distributed
 *     random number generator (RNG). It must be called prior to
 *     using any of the 32-bit RNG's provided in DSPLIB
 *
 *          @param seed = An arbitrary unsigned integer chosen by the user.
 *
 *          @param polynomial = Array of 3 non-arbitrary unsigned integers,
 *          previously generated using the included TinyMTDC program and/or
 *          from the provided text file; numbers from different sets @b MUST
 *          @b NOT be mixed and matched. Should the user provide a NULL
 *          pointer instead, default values will be used instead. These
 *          parameters ensure (mostly) statistically independent random
 *          numbers among different generators. Users should place numbers in
 *          the polynomial parameter in the order in which they appear in the
 *          text file or TinyMTDC program. That is columns 0, 1, and 2 (mat1,
 *          mat2, and tmat of TinyMTDC) correspond to positions 0, 1, and 2 of
 *          the polynomial.
 *
 *          @param state = An array of 7 unsigned 32-bit integers which need
 *          not be initialized to any values by the user; the user is only
 *          required to allocate such space and maintain (but @b NEVER modify)
 *          it.
 *
 * @par Algorithm:
 * The random number generator is based on the Tiny Mersenne Twister (TinyMT).
 * <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/TINYMT/"
 * >Click here for more information.</a>
 *
 * @par Assumptions:
 *     The user has properly initialized the "polynomial" and "state"
 *     parameters.
 *
 * @par Implementation notes:
 * @b Endian @b Support: The code supports both big and little endian modes. <BR>
 * @b Interruptibility: The code not interruptible. <BR>
 *
 */


void DSP_urand32_init_cn(
    unsigned int seed,         /*Arbitrary number used for initialization     */
    void* restrict polynomial, /*Array of length 3 containing polynomial data */
    void* restrict state);     /*Array of length 7 allocated and uninitialized*/

/*
 *     This function is used to fill an array with uniformly distributed
 *     random unsigned 32-bit integers on the interval [0,(2^32)-1].
 *
 *          @param size = The size of the array to be filled.
 *
 *          @param vector = The array which the user wants to fill with random
 *          values. Again, it should be of type @b unsigned @b int.
 *
 *          @param state = The array which was initialized with the
 *          "DSP_urand32_init" function and maintained (but @b NEVER modified)
 *          by the user between subsequent calls to this function.
 *
 * @par Algorithm:
 * The random number generator is based on the Tiny Mersenne Twister (TinyMT).
 * <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/TINYMT/"
 * >Click here for more information.</a>
 *
 * @par Assumptions:
 *     The user has previously called the "DSP_urand32_init"
 *     function at least once, has maintained the state array, and allocated
 *     an array of @b int types of the desired width.
 *
 * @par Implementation notes:
 * @b Endian Support: The code supports both big and little endian modes. <BR>
 * @b Interruptibility: The code is not interruptible. <BR>
 *
 */

void DSP_urand32_cn(unsigned int size,     /*Size of the vector to be filled*/
                    void* vector,        /*Pointer to the destination vector*/
                    void* state);          /*State vector maintained by user*/

/*===========================================================================*/
/* Internal Types                                                            */
/*===========================================================================*/

/* These types are for internal use only and should not be used publicly*/
#ifndef TI_UINT32_TYPE_
#define TI_UINT32_TYPE_

typedef unsigned int _ti_uint32;
typedef int _ti_int32;

#endif /* TI_UINT32_TYPE_ */

#endif /* DSP_URAND32_CN_H_ */

/* ======================================================================== */
/*  End of file:  DSP_urand32_cn.h                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
