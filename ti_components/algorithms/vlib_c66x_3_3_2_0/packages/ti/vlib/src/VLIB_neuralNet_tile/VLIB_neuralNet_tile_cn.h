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
**|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/
#ifndef VLIB_NEURALNET_TILE_CN_H_
#define VLIB_NEURALNET_TILE_CN_H_ 1

#include "../common/VLIB_types.h"
#include "../common/VLIB_tiler.h"

/** @defgroup VLIB_neuralNet_tile_cn */
/** @ingroup  VLIB_neuralNet_tile_cn */
/* @{ */

/**
 * @par Description:
 *  Produces L dotproduct values where each dotproduct is of multiplication and addition
 *  of N 16-bit inputs and N 16-bit weights. Each dotproduct value is biased, rounded
 *  then shifted down to a signed 16-bit range. Depending on the user defined mode
 *  different activation functions such as ReLU, Sigmoid, Tanh are performed prior to
 *  storing in the output array.
 *  This process is repeated for M outputs. <BR>
 *  @verbatim
    Data usage example (cols x rows):
                Input           : 1152 x 1          : N x M
                Weight          : 1152 x 92         : N x L
                Output          : 92 x 1            : L x M
    @endverbatim
 * @par
 *   @param [in]      *pInNodes        Pointer to N x M 16-bit input nodes
 *   @param [in]      *pWeight         Pointer to N x L 16-bit weights
 *   @param [in]      *pBias           Pointer to L 16-bit bias values
 *   @param [out]     *pOutNodes       Pointer to L x M 16-bit ouput nodes
 *   @param [in]       mode            Q-factor to adjust Coefficient value
 *   @param [in]       shiftQ          Q-factor to adjust shift value to get output in required range
 *   @param [in]       coeffQ          Q-factor to adjust Coefficient value
 *   @param [in]       dropOutQ        Q-factor to adjust dropout value
 *
 * @par Algorithm:
 * VLIB_neuralNet_tile_cn.c is the natural C equivalent of the optimized
 * intrinsics code.
 *
 * @par Assumptions:
 *   All buffer starting and each line starting addresses of input/output/weights
 *   are assumed to be aligned to 8-bytes.
 *
 * @par Implementation Notes:
 *      The code is interruptible. <BR>
 *
 */

void VLIB_neuralNet_tile_cn(sBuffer_t *pInNodes,
                            sBuffer_t *pWeight,
                            sBuffer_t *pBias,
                            sBuffer_t *pOutNodes,
                            uint32_t mode,
                            uint32_t shiftQ,
                            uint32_t coeffQ,
                            uint32_t dropOutQ);
/** @} */

#endif /* VLIB_NEURALNET_TILE_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_neuralNet_tile_cn.h                                  */
/* ======================================================================== */

