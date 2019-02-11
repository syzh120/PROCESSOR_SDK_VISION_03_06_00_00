/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|        Copyright (c) 2007 - 2013 Texas Instruments Incorporated          |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef VLIB_SIMPLEX_H_
#define VLIB_SIMPLEX_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_simplex*/
/** @ingroup  VLIB_simplex */
/* @{ */

/**
 * @par Description
 *  This function accepts as input a pointer to the cost function to be minimized and an N-dimensional
 *  coordinate vector indicating the starting point of the search. The function returns the coordinates
 *  of the found minima and the actual minimum value.
 *
 * @par
 *    @param [in]  *func          Pointer to cost function.
 *    @param [in]  *start         Pointer to array containing starting coordinates                         User-defined
 *    @param [in]  *init_step     Pointer to array containing the size of the initial step to be taken
 *                                 in each dimension to form the initial simplex                            User-defined
 *    @param [in]   N             Dimensionality of the coordinate space                                     (SQ31.0)
 *    @param [in]   N_INV         Value equal to the reciprocal of N                                         (SQ0.15)
 *    @param [in]   MaxIteration  Maximum number of allowed iterations to find the minima                    (SQ31.0)
 *    @param [in]   EPSILON       Stopping criterion corresponding to a threshold on the difference        User-defined
 *                                 between the largest and smallest values in the simplex at any iteration
 *    @param [in]  *v             Pointer to array of size N*(N+1). For internal use.
 *    @param [in]  *f             Pointer to array of size N+1. For internal use.
 *    @param [in]  *vr            Pointer to array of size N. For internal use.
 *    @param [in]  *ve            Pointer to array of size N. For internal use.
 *    @param [in]  *vc            Pointer to array of size N. For internal use.
 *    @param [in]  *vm            Pointer to array of size N. For internal use.
 *    @param [in]  *addtlArgs     Pointer to structure containing additional arguments to cost function
 *    @param [out] *minPoint      Pointer to array to hold the coordinates of the found minima
 *    @param [out] *minValue      Pointer to variable to hold the minimum found value
 *
 * @par Assumptions:
 *  - All arrays should be double word aligned.
 *  - The stopping condition works as follows: If the difference between the largest and smallest values in the simplex at any iteration
 *    is smaller than EPSILON, the function terminates.
 *  - It is assumed that the cost function will have a 32-bit return value, and, as input, it will take 16-bit representation of the coordinates.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void    VLIB_simplex(int32_t (*func)(int16_t a[], const void *b), /* function handle */
                     const int16_t * restrict start,          /* start point */
                     const int16_t * restrict init_step,      /* step size for init simplex */
                     int32_t N,                               /* number of dimensions */
                     int16_t N_INV,                           /* 1/N*/
                     int32_t MaxIteration,
                     int32_t EPSILON,                         /* convergence threshold */
                     int16_t * restrict v,                    /* pointer to buffer */
                     int32_t * restrict f,                    /* pointer to buffer */
                     int16_t * restrict vr,                   /* pointer to buffer */
                     int16_t * restrict ve,                   /* pointer to buffer */
                     int16_t * restrict vc,                   /* pointer to buffer */
                     int16_t * restrict vm,                   /* pointer to buffer */
                     const void *addtlArgs,               /* arguments to func */
                     int16_t * restrict minPoint,             /* stop point */
                     int32_t * restrict minValue              /* minimum value */
                     );

/** @} */

#endif /* VLIB_SIMPLEX_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_simplex.h                                            */
/* ======================================================================== */

