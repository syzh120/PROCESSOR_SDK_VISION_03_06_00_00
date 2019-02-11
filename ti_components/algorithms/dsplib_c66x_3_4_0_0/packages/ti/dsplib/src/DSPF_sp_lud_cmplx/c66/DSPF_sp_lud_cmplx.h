/* ======================================================================= */
/* DSPF_sp_lud_cmplx.h -- complex lower/upper decompostion                 */
/*                 Optimized C Implementation                              */
/*                                                                         */
/* Rev 1.0.0                                                               */
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
#ifndef DSPF_SP_LUD_CMPLX_H_
#define DSPF_SP_LUD_CMPLX_H_

#ifndef __TI_COMPILER_VERSION__           // for non TI compiler
#include "assert.h"                       // intrinsics prototypes
#include "C6xSimulator.h"                 // intrinsics prototypes
#include "C6xSimulator_type_modifiers.h"  // define/undefine typing keywords
#endif

/*===========================================================================*/
/* External Function Prototypes and Documentation                            */
/*===========================================================================*/

/** @ingroup MATRIX */
/* @{ */

/** @defgroup  DSPF_sp_lud_cmplx */
/** @ingroup DSPF_sp_lud_cmplx */
/* @{ */

/**
 *      This function decomposes the square complex matrix A into a lower triangular matrix L,
 *      upper triangular matrix U, and a permutation matrix P where A=transpose(P)*L*U.
 *      The band Gaussian elimination outer product algorithm is used. The permutation
 *      matrix P keeps track of the reordering of rows in  the A matrix such that the
 *      first element of the permuted matrix is maximum and nonzero. The values stored
 *      in the matrices are assumed to be float precision floating point values. This
 *      code is suitable for dense matrices. No optimizations are made for sparse matrices.
 *
 *     @param  Nrows       = number of square complex matrix A
 *     @param  A           = pointer to complex matrix A[2*Nrows*Nrows]
 *     @param  L           = pointer to lower triangular complex matrix L[2*Nrows*Nrows]
 *     @param  U           = pointer to upper triangular complex matrix U[2*Nrows*Nrows]
 *     @param  P           = pointer to permutation complex matrix P[2*Nrows*Nrows]
 *
 *
 * @par Algorithm:
 * DSPF_sp_lud.c is the natural C equivalent of the optimized intrinsic
 * C code without restrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.
 *
 * @par Assumptions:
 *  1. The arrays A, L, U, and P are stored in distinct arrays. In-place processing is not allowed. <BR>
 *  2. The arrays consist of complex number entries with alternating real and imaginary parts:
 *     real0,imag0,real1,imag1,... <BR>
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */

int DSPF_sp_lud_cmplx(const int order,float *restrict A,float *restrict L,float *restrict U,unsigned short *restrict P);

/* @} */ /* ingroup */
/* @} */ /* ingroup */

#endif /* DSPF_SP_LUD_CMPLX_H_ */

/* ======================================================================= */
/*  End of file:  DSPF_sp_lud_cmplx.h                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
