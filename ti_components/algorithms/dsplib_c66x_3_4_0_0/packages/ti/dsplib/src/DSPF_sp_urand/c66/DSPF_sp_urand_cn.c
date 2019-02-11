/* ======================================================================= */
/* DSPF_sp_urand_cn.c -- Natural C Implementation                          */
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

/*=========================================================================*/
/* Includes                                                                */
/*=========================================================================*/
#include "DSPF_sp_urand_cn.h"

/*=========================================================================*/
/* Miscellaneous Constants                                                 */
/*=========================================================================*/
#define DSPF_sp_urand_UINT_TO_FLOAT 2.3283063e-010

/*=========================================================================*/
/* State Array Positions                                                   */
/*=========================================================================*/
extern const int DSP_urand32_cn_STATUS_0;
extern const int DSP_urand32_cn_STATUS_2;
extern const int DSP_urand32_cn_STATUS_3;
extern const int DSP_urand32_cn_TMAT;

/*=========================================================================*/
/* Internal Function prototypes                                            */
/*=========================================================================*/
float generate_random_float_cn(_ti_uint32 *state);

/*=========================================================================*/
/* External Function prototypes                                            */
/*=========================================================================*/
extern unsigned int generate_random_ti_uint32_cn(_ti_uint32 *state);

/*=========================================================================*/
/* Internal Functions                                                      */
/*=========================================================================*/

/*  Function Name: generate_random_float_cn
 *
 *  @Purpose: This function is used internally to generate individual
 *  uniformly-distributed random @b float values. It should not be
 *  called by the user.
 *
 *  @Precondition: The user has maintained the state array
 *
 *  @Postcondition: A uniformly-distributed random @b float has been
 *  generated
 *
 *  @param state The array which was initialized with the "DSP_urand32_init"
 *  function and maintained (but NEVER modified) by the user between
 *  subsequent calls to the "DSP_urand32" function.
 *
 *  @returns A uniformly distributed random @b float
 *
 */

#pragma CODE_SECTION(generate_random_float_cn,".text:ansi");
float generate_random_float_cn(_ti_uint32 *state)
{
    return generate_random_ti_uint32_cn(state) * DSPF_sp_urand_UINT_TO_FLOAT;
} /* generate_random_float_cn */

/*=========================================================================*/
/* User Functions                                                          */
/*=========================================================================*/
#pragma CODE_SECTION(DSPF_sp_urand_cn,".text:ansi");
void DSPF_sp_urand_cn(unsigned int size, float* vector, void* state)
{
    _ti_uint32* v_state = state;
    float* v_vector = vector;

    signed int i = 0;
    while (i < size)
    {
        v_vector[i++] = generate_random_float_cn((_ti_uint32*) v_state);
    }
} /* DSPF_sp_urand_cn */
/* ======================================================================== */
/*  End of file:  DSPF_sp_urand_cn.c                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
