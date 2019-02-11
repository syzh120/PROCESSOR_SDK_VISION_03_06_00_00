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
**|         Copyright (c) 2015 Texas Instruments Incorporated                |**
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

#ifndef VLIB_HAARDETECTOBJECT_CN_H_
#define VLIB_HAARDETECTOBJECT_CN_H_ 1

#include "../common/VLIB_haarDetectObjects_types.h"

int32_t VLIB_haarDetectObjectsSparse_cn(uint32_t *integralImgAlign,
                                        int32_t integralImgPitch,
                                        int32_t startStage,
                                        int32_t endStage,
                                        VLIB_HAARDETOBJ_sObjectList   *objListIn,
                                        VLIB_HAARDETOBJ_sClassifier   *classifier,
                                        VLIB_HAARDETOBJ_sObjectList   *objListOut,
                                        uint8_t *scratch1,
                                        uint8_t *scratch2);


#endif

/* ======================================================================== */
/*  End of file:  VLIB_haarDetectObjectsSparse_cn.h                         */
/* ======================================================================== */

