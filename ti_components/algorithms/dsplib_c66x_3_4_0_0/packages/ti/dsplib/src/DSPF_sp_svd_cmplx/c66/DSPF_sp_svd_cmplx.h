/* ======================================================================= */
/* DSPF_sp_svd_cmplx.h -- Singular Value Decomposition                     */
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
#ifndef DSPF_SP_SVD_CMPLX_H_
#define DSPF_SP_SVD_CMPLX_H_

#ifndef __TI_COMPILER_VERSION__           // for non TI compiler
#include "assert.h"                       // intrinsics prototypes
#include "C6xSimulator.h"                 // intrinsics prototypes
#include "C6xSimulator_type_modifiers.h"  // define/undefine typing keywords
#endif

/** @ingroup MATRIX */
/* @{ */

/** @defgroup  DSPF_sp_svd_cmplx */
/** @ingroup DSPF_sp_svd_cmplx */
/* @{ */

/**
 *      This routine decomposes a complex matrix A into a product of three
 *      matrices:  A = U * D * V' where U and V are orthogonal matrices, V' is the
 *      Hermitian of V, and D is a diagonal matrix.  If the define constant
 *      ENABLE_REDUCED_FORM is defined then the reduced form is generated else
 *      the full form is generated as shown below for the case Nrows>=Ncols. Note 
 *      that the symbol ' is the Hermitian or complex conjugate transpose.
 *
 *      full form               <BR>
 *         U [Nrows x 2*Nrows]  <BR>
 *         D [Nrows x 2*Ncols]  <BR>
 *         V'[Ncols x 2*Ncols]  <BR>
 *      reduced form            <BR>
 *         U [Nrows x 2*Ncols]  <BR>
 *         D [Ncols x 2*Ncols]  <BR>
 *         V'[Ncols x2*Ncols]  <BR>
 *
 *      The singular values are the diagonal elements of D and correspond to the
 *      positive square roots of the eigenvalues of the matrix A' * A.  This code
 *      is suitable for dense matrices.  No optimizations are made for sparse matrices.
 *      This routine calls the following routines.
 *
 *        1. DSPF_sp_convert_to_bidiag: converts A to bidiagonal matrix using Householder
 *           transformations.  <BR>
 *        2. DSPF_sp_bidiag_to_diag: converts bidiagonal matrix to diagonal using Givens
 *           transformations (works only for Nrows>=Ncols).  <BR>
 *        3. DSPF_sp_sort_singular_values: sorts singular values in descending order and
 *           modifies U and V matrices accordingly.  <BR>
 *
 *     If Nrows<Ncols then the transpose of the input is generated A'=V*D'*U' and input to steps
 *     1,2, and 3. Then the U and V matrices are switched and the D matrix is generated based
 *     on the list on singular values.  The table shown below illustrates the processing for
 *     the case Nrows<Ncols.
 *
 *     full form
 *       V [Ncols x 2*Ncols]
 *       D'[Ncols x 2*Nrows]
 *       U'[Nrows x 2*Nrows]
 *     reduced form
 *       V [Ncols x 2*Nrows]
 *       D'[Nrows x 2*Nrows]
 *       U'[Nrows x 2*Nrows]
 *
 *     @param  Nrows    = Number of rows in A matrix
 *     @param  Ncols    = Number of columns in A matrix
 *     @param  A        = Pointer of matrix A
 *     @param  U        = Pointer to matrix U
 *     @param  V        = Pointer to matrix V
 *     @param  U1       = Pointer to scratch pad matrix U1[max(Nrows,Ncols)^2]
 *     @param  diag     = Pointer to vector of diagonal elements diag[max(Nrows,Ncols)]
 *     @param superdiag = Pointer to vector of superdiagonal elements superdiag[max(Nrows,Ncols)]
 *
 * @par Algorithm:
 * DSPF_sp_svd_cmplx_cn.c is the natural C equivalent of the optimized intrinsic
 * C code without restrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.
 *
 * @par Assumptions:
 *  1. The arrays A,U,D,V,U1,diag,and superdiag are stored in distinct arrays. In-place processing of A is not allowed. <BR>
 *  2. The arrays consist of complex number entries with alternating real and imaginary parts:
 *      real0,imag0,real1,imag1,... <BR>
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */

int DSPF_sp_svd_cmplx(const int Nrows,const int Ncols,float *restrict A,float *restrict U,float *restrict V,float *restrict U1,float *restrict diag,float *restrict superdiag);

/* @} */ /* ingroup */
/* @} */ /* ingroup */

#endif /* DSPF_SP_SVD_CMPLX_H_ */

/* ======================================================================= */
/*  End of file:  DSPF_sp_svd_cmplx.h                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
