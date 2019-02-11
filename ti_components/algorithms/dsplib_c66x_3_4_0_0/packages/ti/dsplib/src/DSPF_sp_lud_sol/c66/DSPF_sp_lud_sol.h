/* ======================================================================= */
/* DSPF_sp_lud_sol.h -- linear solver by LUD                               */
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
#ifndef DSPF_SP_LUD_SOL_H
#define DSPF_SP_LUD_SOL_H

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

/** @defgroup  DSPF_sp_lud_solver */
/** @ingroup DSPF_sp_lud_solver */
/* @{ */

/**
 *      This function solves the system of linear equations A*x=b for x using the inputs produced by DSPF_sp_lud where
 *      A*x=transpose(P)*L*U*x=b.  The following procedure is performed.
 *
 *         1. Modify b using permutation matrix:          b_mod = L*U*x = P*b <BR>
 *         2. Use forward substitution to solve for y:        y = U*x = inv(L)*b_mod <BR>
 *         3. Use backward substitution for solve for x:      x = inv(U)*y <BR>
 *
 *
 *      The values stored in the matrices are assumed to be single precision floating point values.
 *      This code is suitable for dense matrices. No optimizations are made for sparse matrices.
 *
 *     @param  order       = order of matrix A
 *     @param  P           = pointer to permutation matrix P[order*order]
 *     @param  L           = pointer to lower triangular matrix L[order*order]
 *     @param  U           = pointer to upper triangular matrix U[order*order]
 *     @param  b           = pointer to vector b[order]
 *     @param  b_mod       = pointer to modified vector b_mod[order]
 *     @param  y           = pointer to temporary vector y[order]
 *     @param  x           = pointer to final solver output vector x[order]
 *
 *
 * @par Algorithm:
 * DSPF_sp_lud_solver.c is the natural C equivalent of the optimized intrinsic
 * C code without restrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.
 *
 * @par Assumptions:
 *  The arrays P, L, U, and inv_A are stored in distinct arrays. 
 *  In-place processing is not done. <BR>
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */

int DSPF_sp_lud_solver(const int order,unsigned short *restrict P,float *restrict L,
                       float *restrict U,float *restrict b,float *restrict b_mod,
					   float *restrict y,float *restrict x);

/* @} */ /* ingroup */
/* @} */ /* ingroup */

#endif /* DSPF_SP_LUD_SOL_H */

/* ======================================================================= */
/*  End of file:  DSPF_sp_lud_sol.h                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
