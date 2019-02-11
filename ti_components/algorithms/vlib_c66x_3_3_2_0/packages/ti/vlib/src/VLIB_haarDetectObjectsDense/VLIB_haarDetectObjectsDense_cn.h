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

int32_t VLIB_haarDetectObjectsDense_cn(uint32_t *integralImgAlign,
                                       uint32_t *integralImgNonAlign,
                                       uint32_t integralImgWidth,
                                       uint32_t integralImgPitch,
                                       uint32_t IntegralImgHeight,
                                       uint32_t startStage,
                                       uint32_t endStage,
                                       uint32_t maxObjects,
                                       uint32_t yDirJump,
                                       VLIB_HAARDETOBJ_sClassifier   *classifier,
                                       VLIB_HAARDETOBJ_sObjectList   *outObjListOut,
                                       uint8_t *scratch1,
                                       uint8_t *scratch2);

#endif
/* ======================================================================== */
/*  End of file:  VLIB_haarDetectObjectsDense_cn.h                          */
/* ======================================================================== */

