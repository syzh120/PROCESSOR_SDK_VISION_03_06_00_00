/* ======================================================================= */
/* DSPF_sp_cholesky_cmplx.h -- Cholesky decomposition and solver           */
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

#ifndef DSPF_SP_CHOLESKY_CMPLX_H_
#define DSPF_SP_CHOLESKY_CMPLX_H_

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

/** @defgroup  DSPF_sp_cholesky_cmplx */
/** @ingroup DSPF_sp_cholesky_cmplx */
/* @{ */

/**
 *      This function tests the square complex matrix A for a symmetric positive definite and
 *      decomposes the matrix A into a lower triangular matrix L where A=L*U and
 *      U=Hermitian of L. The values stored in the matrices are assumed to be
 *      single precision floating point values. This code is suitable for
 *      dense matrices. No optimizations are made for sparse matrices.
 *
 *     @param  enable_test = enables test for symmetric positive definite matrix
 *     @param  Nrows       = Nrows of square matrix A
 *     @param  A           = pointer to square matrix A[Nrows*2*Nrows]
 *     @param  L           = pointer to lower triangular matrix L[Nrows*2*Nrows]
 *
 * @par Algorithm:
 * DSPF_sp_cholesky_cmplx_cn.c is the natural C equivalent of the optimized intrinsic
 * C code without restrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.
 *
 * @par Assumptions:
 *  1 .The arrays A and L are stored in distinct arrays. In-place processing is not allowed. <BR>
 *  2. The arrays consist of complex number entries with alternating real and imaginary parts:
 *     real0,imag0,real1,imag1,... <BR>
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */

int DSPF_sp_cholesky_cmplx(const int enable_test, const int Nrows, float *restrict A, float *restrict L);
/* }@ */ /* ingroup */

/** @defgroup  DSPF_sp_cholesky_in_place_cmplx */
/** @ingroup DSPF_sp_cholesky_in_place_cmplx */
/* @{ */

/**
 *      This function tests the square matrix A for a symmetric positive definite and
 *      decomposes the square matrix A into a lower triangular matrix L where A=L*U and
 *      U=transpose of L. The processing is done in place of the matrix A.
 *      The values stored in the matrices are assumed to be float precision
 *      floating point values. This code is suitable for dense matrices. No
 *      optimizations are made for sparse matrices.
 *
 *     @param  enable_test = enables test for symmetric positive definite matrix
 *     @param  Nrows       = Nrows of square matrix A
 *     @param  A           = pointer to input square matrix A[Nrows*2*Nrows] and output matrix L[Nrows*2*Nrows]
 *
 * @par Algorithm:
 * DSPF_sp_cholesky_cmplx_cn.c is the natural C equivalent of the optimized intrinsic
 * C code without restrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.
 *
 * @par Assumptions:
 *  1. In-place processing is done on the matrix A. <BR>
 *  2. The arrays consist of complex number entries with alternating real and imaginary parts:
 *     real0,imag0,real1,imag1,... <BR>
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */

int DSPF_sp_cholesky_in_place_cmplx(const int enable_test, const int Nrows, float *restrict A);
/* }@ */ /* ingroup */

/** @defgroup  DSPF_sp_cholesky_solver_cmplx */
/** @ingroup DSPF_sp_cholesky_solver_cmplx */
/* @{ */

/**
 *      This function solves A*x=b for x using forward and backward substitution
 *      using the decomposed lower triangular matrix L as shown in the following
 *      steps. The values stored in the matrices are assumed to be float precision
 *      floating point values.
 *        1. A*x = L*U*b = L*L_transpose*x = b
 *        2. y = inverse(L)*b - done using forward substitution
 *        3. x = inverse(L_transpose)*y - done using backward substitution
 *
 *     @param  Nrows       = Nrows of square matrix A
 *     @param  L           = pointer to input square matrix A[Nrows*2*Nrows]
 *     @param  y           = pointer to intermediate vector y[2*Nrows]
 *     @param  b           = pointer to input vector b[2*Nrows]
 *     @param  x           = pointer to output vector x[2*Nrows]
 *
 * @par Algorithm:
 * DSPF_sp_cholesky_cmplx_cn.c is the natural C equivalent of the optimized intrinsic
 * C code without restrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.
 *
 * @par Assumptions:
 *  1. The decomposed lower triangular matrix L is available as input. <BR>
 *  2. The arrays consist of complex number entries with alternating real and imaginary parts:
 *     real0,imag0,real1,imag1,... <BR>
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */

int DSPF_sp_cholesky_solver_cmplx(const int Nrows,float *restrict L,float *restrict y,float *restrict b,float *restrict x);

/* }@ */ /* ingroup */
/* }@ */ /* ingroup */

#endif /* DSPF_SP_CHOLESKY_CMPLX_H_ */

/* ======================================================================= */
/*  End of file:  DSPF_sp_cholesky_cmplx.h                                 */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

