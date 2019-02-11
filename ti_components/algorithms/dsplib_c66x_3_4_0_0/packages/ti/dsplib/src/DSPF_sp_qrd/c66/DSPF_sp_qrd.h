/* ======================================================================= */
/* DSPF_sp_qrd.h -- QR decomposition single precision                      */
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
#ifndef DSPF_SP_QRD_H_
#define DSPF_SP_QRD_H_

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

/** @defgroup  DSPF_sp_qrd */
/** @ingroup DSPF_sp_qrd */
/* @{ */

/**
 *      This function decomposes the rectangular matrix A into an orthogonal Q matrix and
 *      an upper right triangular matrix R such that A=Q*R.  The Householder algorithm is
 *      used to zero columns below the diagonal in the original A matrix to produce the R
 *      matrix. The Q matrix is generated during the process.  The values stored in the
 *      matrices are assumed to be single precision floating point values. This code is
 *      suitable for dense matrices. No optimizations are made for sparse matrices.
 *
 *     @param  Nrows       = number of rows of matrix A
 *     @param  Ncols       = number of columns of matrix A
 *     @param  A           = pointer to matrix A[Nrows*Ncols]
 *     @param  Q           = pointer to matrix Q[Nrows*Nrows]
 *     @param  R           = pointer to upper triangular matrix R[Nrows*Ncols]
 *     @param  u           = pointer to temporary vector u[max(Nrows,Ncols)]
 *
 *
 * @par Algorithm:
 * DSPF_sp_qrd_cn.c is the natural C equivalent of the optimized intrinsic
 * C code without restrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.
 *
 * @par Assumptions:
 *  The arrays A, Q, R, u, and Q1 are stored in distinct arrays. In-place processing is not done. <BR>
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */

int DSPF_sp_qrd(const int Nrows,const int Ncols,float *restrict A,float *restrict Q,float *restrict R,float *restrict u);

/* @} */ /* ingroup */


/** @defgroup  DSPF_sp_qrd_inverse */
/** @ingroup DSPF_sp_qrd_inverse */
/* @{ */

/**
 *      This function processes an orthogonal matrix Q, and an upper triangular matrix R generated
 *      by DSPF_sp_qrd and generates the inverse of the A matrix where inv_A=inv(R)*inv(Q).
 *      In place processing is performed on the R matrix such that its original contents are
 *      modified. The values stored in the matrices are assumed to be single precision floating point values.
 *      This code is suitable for dense matrices. No optimizations are made for sparse matrices.
 *
 *     @param  Nrows       = number of rows in matrix A
 *     @param  Ncols       = number of columns in matrix A
 *     @param  Q           = pointer to lower triangular matrix Q[Nrows*Nrows]
 *     @param  R           = pointer to upper triangular matrix R[Nrows*Ncols]
 *     @param  inv_A       = pointer to inverse of matrix A[Nrows*Ncols]
 *
 *
 * @par Algorithm:
 * DSPF_sp_qrd_cn.c is the natural C equivalent of the optimized intrinsic
 * C code without restrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.
 *
 * @par Assumptions:
 *  The arrays Q, R, and inv_A are stored in distinct arrays. In-place processing of R is done. <BR>
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */

int DSPF_sp_qrd_inverse(const int Nrows,const int Ncols,float *restrict Q,float *restrict R,float *restrict inv_A);

/* @} */ /* ingroup */


/** @defgroup  DSPF_sp_qrd_solver */
/** @ingroup DSPF_sp_qrd_solver */
/* @{ */

/**
 *      This function solves the system of linear equations A*x=b for x using the inputs produced by
 *      DSPF_sp_qrd where A*x=Q*R*x=b.  The following procedure is performed.
 *
 *         1. Use matrix multiplication to generate y:        y = transpose(Q)*b  <BR>
 *         2. Use backward substitution for solve for x:      x = inv(R)*y  <BR>
 *
 *
 *      The values stored in the matrices are assumed to be single precision floating point values.
 *      This code is suitable for dense matrices. No optimizations are made for sparse matrices.
 *
 *     @param  Nrows       = number of rows in matrix A
 *     @param  Ncols       = number of columns in matrix A
 *     @param  Q           = pointer to lower triangular matrix Q[Nrows*Nrows]
 *     @param  R           = pointer to upper triangular matrix R[Nrows*Ncols]
 *     @param  b           = pointer to vector b[Nrows]
 *     @param  y           = pointer to temporary vector y[Nrows]
 *     @param  x           = pointer to final solver output vector x[Ncols]
 *
 *
 * @par Algorithm:
 * DSPF_sp_qrd_cn.c is the natural C equivalent of the optimized intrinsic
 * C code without restrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.
 *
 * @par Assumptions:
 *  The arrays P, L, U, and inv_A are stored in distinct arrays. In-place processing is not done. <BR>
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */


int DSPF_sp_qrd_solver(const int Nrows,const int Ncols,float *restrict Q,float *restrict R,float *restrict b,float *restrict y,float *restrict x);

/* @} */ /* ingroup */
/* @} */ /* ingroup */

#endif /* DSPF_sp_qrd_H_ */

/* ======================================================================= */
/*  End of file:  DSPF_sp_qrd.h                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
