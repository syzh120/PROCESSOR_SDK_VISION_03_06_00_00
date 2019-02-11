/* ======================================================================= */
/* DSPF_sp_nrand.c -- Optimized C source interface header file             */
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

#ifndef DSPF_SP_NRAND_H_
#define DSPF_SP_NRAND_H_

#ifndef __TI_COMPILER_VERSION__           // for non TI compiler
#include "assert.h"                       // intrinsics prototypes
#include "C6xSimulator.h"                 // intrinsics prototypes
#include "C6xSimulator_type_modifiers.h"  // define/undefine typing keywords
#endif

#include "ti/dsplib/src/DSP_urand32/c66/DSP_urand32.h"

/** @ingroup MATH */
/* @{ */

/** @defgroup DSPF_sp_nrand */
/** @ingroup DSPF_sp_nrand */
/* @{ */


/**
 *     This function is used to fill an array with Gaussian normal distributed
 *     random numbers.These numbers are distributed assuming mean (mu) = 0 and
 *     standard deviation (sigma) = 1.
 *
 *     The output vector can be modified for an arbitrary mu and sigma by
 *     adding its contents by the desired value of mu and multiplying its
 *     contents by the desired value of sigma respectively as shown in the
 *     histogram below.
 *
 *          @param size The size of the array to be filled.
 *
 *          @param vector The array of type @b float which the user wants
 *          to fill with random values.
 *
 *          @param state The array which was initialized with the
 *          "DSP_urand32_init" function and maintained (but NEVER modified) by
 *          the user between subsequent calls to this function.
 *
 * @par Algorithm:
 * The RNG utilizes the Tiny Mersene Twister (TinyMT) as its underlying RNG
 * and an optimized version of George Marsaglia's Ziggurat algorithm as a
 * wrapper RNG to generate a Gaussian normal distribution from the uniformly
 * distributed TinyMT.
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
 * @image html DSPF_sp_nrand_histogram.png
 */

/* }@ */ /* ingroup */
/* }@ */ /* ingroup */

void DSPF_sp_nrand(int size, float *vector, void *state);


#endif /* DSPF_SP_NRAND_H_ */

/* ======================================================================== */
/*  End of file:  DSPF_sp_nrand.h                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
