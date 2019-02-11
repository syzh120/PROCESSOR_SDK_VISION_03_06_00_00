/* ======================================================================= */
/* DSPF_dp_lud_sol_cmplx.h -- complex linear solver by LUD                 */
/*                        optimized C Implementation                       */
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
#ifndef DSPF_DP_LUD_SOL_CMPLX_H_
#define DSPF_DP_LUD_SOL_CMPLX_H_

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

/** @defgroup  DSPF_dp_lud_solver_cmplx */
/** @ingroup DSPF_dp_lud_solver_cmplx */
/* @{ */

/**
 *      This function solves the system of linear equations A*x=b for x using the inputs produced by DSPF_dp_lud where
 *      A*x=transpose(P)*L*U*x=b.  The following procedure is performed.
 *
 *         1. Modify b using permutation matrix:          b_mod = L*U*x = P*b <BR>
 *         2. Use forward substitution to solve for y:        y = U*x = inv(L)*b_mod <BR>
 *         3. Use backward substitution for solve for x:      x = inv(U)*y <BR>
 *
 *
 *      The values stored in the matrices are assumed to be double precision floating point values.
 *      This code is suitable for dense matrices. No optimizations are made for sparse matrices.
 *
 *     @param  Nrows       = number of rows in square complex matrix A
 *     @param  P           = pointer to permutation matrix P[Nrows*Nrows]
 *     @param  L           = pointer to lower triangular matrix complex L[2*Nrows*Nrows]
 *     @param  U           = pointer to upper triangular matrix complex U[2*Nrows*Nrows]
 *     @param  b           = pointer to complex vector b[2*Nrows]
 *     @param  b_mod       = pointer to modified complex vector b_mod[2*Nrows]
 *     @param  y           = pointer to temporary complex vector y[2*Nrows]
 *     @param  x           = pointer to final solver output complex vector x[2*Nrows]
 *
 *
 * @par Algorithm:
 * DSPF_dp_lud_solver.c is the natural C equivalent of the optimized intrinsic
 * C code without restrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.
 *
 * @par Assumptions:
 *  1. The arrays P, L, U, and inv_A are stored in distinct arrays. In-place processing is not done. <BR>
 *  2. The arrays consist of complex number entries with alternating real and imaginary parts:
 *     real0,imag0,real1,imag1,... <BR>
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */

int DSPF_dp_lud_solver_cmplx(const int order,unsigned short *restrict P,
                             double *restrict L,double *restrict U,double *restrict b,
							 double *restrict b_mod,double *restrict y,double *restrict x);

/* @} */ /* ingroup */
/* @} */ /* ingroup */

#endif /* DSPF_DP_LUD_SOL_CMPLX_H_ */

/* ======================================================================= */
/*  End of file:  DSPF_dp_lud_sol_cmplx.h                                  */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
