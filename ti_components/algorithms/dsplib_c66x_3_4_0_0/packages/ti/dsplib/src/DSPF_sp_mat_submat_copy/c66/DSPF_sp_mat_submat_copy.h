/* ======================================================================= */
/* DSPF_sp_mat_submat_copy.h -- Sub-Matrix Copy                            */
/*              Optimized C Implementation (w/ Intrinsics)                 */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/  */ 
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

#ifndef DSPF_SP_MAT_SUBMAT_COPY_H_
#define DSPF_SP_MAT_SUBMAT_COPY_H_

#ifndef __TI_COMPILER_VERSION__           // for non TI compiler
#include "assert.h"                       // intrinsics prototypes
#include "C6xSimulator.h"                 // intrinsics prototypes
#include "C6xSimulator_type_modifiers.h"  // define/undefine typing keywords
#endif

/** @ingroup MATRIX */
/* @{ */

/** @defgroup  DSPF_sp_mat_submat_copy */
/** @ingroup DSPF_sp_mat_submat_copy */
/* @{ */

/**
 *      If dir = 0, this function copies n rows starting from st row of matrix x to form matrix y;
 *      If dir != 0, this function copies n rows of y to matrix x;
 *      The values stored in x and y is single-precision floating values.
 *
 *      @param  x    = Pointer to r1 by c1 input matrix.
 *      @param  rows = Number of rows in x.
 *      @param  cols = Number of columns in x.
 *      @param  st   = start index of rows in x to be copied.
 *      @param  n    = Number of rows to be copied.
 *      @param  y    = Pointer to the output matrix.
 *      @param  dir  = data flow direction.
 *
 * @par Algorithm:
 * DSPF_sp_mat_submat_copy_cn.c is the natural C equivalent of the optimized intrinsic
 * C code withoutrestrictions. Note that the intrinsic C code is optimized
 * and restrictions may apply.  
 *
 * @par Assumptions:
 *  The arrays x and y are stored in distinct arrays. In-place processing is not allowed. <BR>
 *  Rows, cols, st and n are assumed to be even. <BR>
 *  x and y are aligned on double-word boundaries. <BR>
 *
 * @par Implementation Notes:
 * @b Interruptibility : The code is interruptible.  <BR>
 * @b Endian support   : supports both Little and Big endian modes.  <BR>
 *
 */

void DSPF_sp_mat_submat_copy(float* x, int rows, int cols, int st, int n, float *restrict y, int dir);

#endif /* DSPF_SP_MAT_SUBMAT_COPY_H_*/

/* ======================================================================= */
/*  End of file:  DSPF_sp_mat_submat_copy.h                                */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

