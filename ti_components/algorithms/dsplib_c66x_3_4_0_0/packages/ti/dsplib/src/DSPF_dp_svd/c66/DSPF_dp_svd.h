/* ======================================================================= */
/* DSPF_dp_svd.h -- Singular Value Decomposition                           */
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
#ifndef DSPF_DP_SVD_H_
#define DSPF_DP_SVD_H_

#define MAX_ITERATION_COUNT 30
//#define ENABLE_REDUCED_FORM 1

#ifndef __TI_COMPILER_VERSION__           // for non TI compiler
#include "assert.h"                       // intrinsics prototypes
#include "C6xSimulator.h"                 // intrinsics prototypes
#include "C6xSimulator_type_modifiers.h"  // define/undefine typing keywords
#endif

/** @ingroup MATRIX */
/* @{ */

/** @defgroup  DSPF_dp_svd */
/** @ingroup DSPF_dp_svd */
/* @{ */

/**
 *      This routine decomposes an Nrows x Ncols matrix A into a product of three
 *      matrices:  A = U * D * V' where U and V are orthogonal matrices, V' is the
 *      transpose of V, and D is a diagonal matrix.  If the define constant
 *      ENABLE_REDUCED_FORM is defined then the reduced form is generated else
 *      the full form is generated as shown below for the case Nrows>=Ncols.
 *
 *      full form             <BR>
 *         U [Nrows x Nrows]  <BR>
 *         D [Nrows x Ncols]  <BR>
 *         V'[Ncols x Ncols]  <BR>
 *      reduced form          <BR>
 *         U [Nrows x Ncols]  <BR>
 *         D [Ncols x Ncols]  <BR>
 *         V'[Ncols x Ncols]  <BR>
 *
 *      The singular values are the diagonal elements of D and correspond to the
 *      positive square roots of the eigenvalues of the matrix A' * A.  This code
 *      is suitable for dense matrices.  No optimizations are made for sparse matrices.
 *      This routine calls the following routines.
 *
 *        1. DSPF_dp_convert_to_bidiag: converts A to bidiagonal matrix using Householder
 *           transformations.  <BR>
 *        2. DSPF_dp_bidiag_to_diag: converts bidiagonal matrix to diagonal using Givens
 *           transformations (works only for Nrows>=Ncols).  <BR>
 *        3. DSPF_dp_sort_singular_values: sorts singular values in descending order and
 *           modifies U and V matrices accordingly.  <BR>
 *
 *     If Nrows<Ncols then the transpose of the input is generated A'=V*D'*U' and input to steps
 *     1,2, and 3. Then the U and V matrices are switched and the D matrix is generated based
 *     on the list on singular values.  The table shown below illustrates the processing for
 *     the case Nrows<Ncols.
 *
 *     full form
 *       V [Ncols x Ncols]
 *       D'[Ncols x Nrows]
 *       U'[Nrows x Nrows]
 *     reduced form
 *       V [Ncols x Nrows]
 *       D'[Nrows x Nrows]
 *       U'[Nrows x Nrows]
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
 * DSPF_dp_svd_cn.c is the natural C equivalent of the optimized intrinsic
 * C code without restrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.
 *
 * @par Assumptions:
 *  The arrays A,U,D,V,U1,diag,and superdiag are stored in distinct arrays. In-place processing of A is not allowed.
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */

int DSPF_dp_svd(const int Nrows,const int Ncols,double *restrict A,double *restrict U,double *restrict V,double *restrict U1,double *restrict diag,double *restrict superdiag);

/* @} */ /* ingroup */
/* @} */ /* ingroup */


#endif /* DSPF_DP_SVD_H_ */

/* ======================================================================= */
/*  End of file:  DSPF_dp_svd.h                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
