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
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
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

#ifndef VLIB_NORMALFLOW_CN_H_
#define VLIB_NORMALFLOW_CN_H_ 1

void VLIB_normalFlow_16_cn(int16_t *imDiff,          /* SQ15.0 */
                           int16_t *Emag,         /* SQ15.0 */
                           int16_t *Ex,           /* SQ15.0 */
                           int16_t *Ey,           /* SQ15.0 */
                           int16_t *LUT,          /* QS0.15 */
                           int16_t T,             /* SQ15.0 */
                           int32_t numEls,          /* SQ31.0 */
                           int16_t *normalFlowU,  /* SQ8.7 */
                           int16_t *normalFlowV);  /* SQ8.7 */


#endif

/* ======================================================================== */
/*  End of file:  VLIB_normalFlow_16_cn.h                                   */
/* ======================================================================== */

