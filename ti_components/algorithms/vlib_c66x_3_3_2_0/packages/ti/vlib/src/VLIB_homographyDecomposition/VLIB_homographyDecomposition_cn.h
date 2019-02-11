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

#ifndef VLIB_HOMOGRAPHY_DECOMPOSITION_CN_H_
#define VLIB_HOMOGRAPHY_DECOMPOSITION_CN_H_ 1

#include "../common/VLIB_types.h"

int32_t    VLIB_homographyDecomposition_cn(VLIB_D64 H[3][3],
                                           VLIB_D64 rot[3][3],
                                           VLIB_D64 trans[3],
                                           VLIB_D64 proj[3]);


#endif /* VLIB_HOMOGRAPHY_DECOMPOSITION_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_homographyDecomposition_cn.h                         */
/* ======================================================================== */

