/* ======================================================================= */
/* DSPF_sp_urand_cn.h -- Natural C source interface header file            */
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


#ifndef DSPF_SP_URAND_CN_H_
#define DSPF_SP_URAND_CN_H_

#include "..\..\DSP_urand32\c66\DSP_urand32_cn.h"

/*
 *     This function is used to fill an array with uniformly distributed
 *     random @b floats on the interval [0, 1).
 *
 *          @param size = The size of the array to be filled.
 *
 *          @param vector = The array of type @b float which the user wants to
 *          fill with random values.
 *
 *          @param state = The array which was initialized with the
 *          "DSP_urand32_init" function and maintained (but NEVER modified) by
 *          the user between subsequent calls to this function.
 *
 * @par Algorithm:
 * The random number generator is based on "DSP_urand32." Random integers
 * are generated in the same manner and then multiplied by 1/(2^32)
 * (rounded to  to 2.3283064e-010 for single-precision arithmetic)
 * and then cast to @b float to ensure a proper range of [0,1).
 *
 * @par Assumptions:
 *     The user has previously called the "DSP_urand32_init"
 *     function at least once, has maintained the state array, and allocated
 *     an array of @b float types of the desired width.
 *
 * @par Implementation notes:
 * @b Endian Support: The code supports both big and little endian modes. <BR>
 * @b Interruptibility: The code is not interruptible. <BR>
 *
 */
void DSPF_sp_urand_cn(unsigned int size,   /*Size of the vector to be filled*/
                      float* vector,      /*Pointer to the destination vector*/
                      void* state);        /*State vector maintained by user*/

#endif /* DSPF_SP_URAND_CN_H_ */

/* ======================================================================== */
/*  End of file:  DSPF_sp_urand_cn.h                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
