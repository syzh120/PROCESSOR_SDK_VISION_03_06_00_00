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

#ifndef VLIB_BHATTACHARYADISTANCE_U32_CN_H_
#define VLIB_BHATTACHARYADISTANCE_U32_CN_H_ 1
/**
* @par
*  @param   *X         Pointer to array containing first probability distribution    (UQ16.0)
*   @param   *Y        Pointer to array containing second probability distribution    (UQ16.0)
*   @param   N        Number of elements in the probability distributions       (SQ31.0)
*   @param  *D        Pointer to variable to store the computed Bhattacharya Distance (SQ32.0)
* @par Benchmarks:
*  See VLIB_Test_Report.html for cycle and memory information.
*
*/
void VLIB_bhattacharyaDistance_U32_cn(uint16_t *X,
                                      uint16_t *Y,
                                      uint32_t N,
                                      uint32_t *D);


#endif

/* ======================================================================== */
/*  End of file:  VLIB_bhattacharyaDistance_U32_cn.h                        */
/* ======================================================================== */

