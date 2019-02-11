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

#ifndef VLIB_HAARDETECTOBJECT_H_
#define VLIB_HAARDETECTOBJECT_H_ 1

#include "../../common/VLIB_haarDetectObjects_types.h"

/** @defgroup VLIB_haarDetectObjectsDense */
/** @ingroup  VLIB_haarDetectObjectsDense */
/* @{ */

/**
 * @par Description:
 *  This function implements object detection based on Haar features with
 *  Ada-boost classifier.
 *
 * @par
 *    @param [in]  integralImgAlign      Pointer to 8 byte aligned integral image buffer                 (UQ32.0)
 *    @param [in] integralImgNonAlign    Pointer to 4 byte (but not 8 byte) aligned integral image,
 *                                       it can be NULL also  useful for optimization with data in L2   (UQ32.0)
 *    @param [in]  integralImgWidth      Width of integral image                                         (UQ32.0)
 *    @param [in]  integralImgPitch      Pitch of integral image                                         (UQ32.0)
 *    @param [in]  integralImgHeight     Height of integral image                                        (UQ32.0)
 *    @param [in]  startStage            classifier stage number to start the dense searching            (UQ32.0)
 *    @param [in]  endStage              classifier stage number to end the dense processing             (UQ32.0)
 *    @param [in]  maxObjects            Maximum number of objects to output (raster order FCFS)         (UQ32.0)
 *    @param [in]  yDirJump              Jump in 'y' co-ordinate direction while search                  (UQ32.0)
 *    @param [in]  classifier            Classifier Data Structure                                       (VLIB_HAARDETOBJ_sClassifier)
 *    @param [out] objListOut            Output List holding the co-ordinates for objects, where each
 *                                       position is given by Y|X in packed format, each being 16 bit
 *                                       quantity                                                        (VLIB_HAARDETOBJ_sObjectList)
 *    @param [in]  scratch1              Scratch buffer of size 16 * (integralImgWidth + 4)              (UQ8.0)
 *    @param [in]  scratch2              Scratch buffer of size 4 * ((integralImgWidth + 7)/8)           (UQ8.0)
 *
 * @par Assumptions:
 *    - Integral image is calculated outside this kernel.
 *    - \c maxObjects can be used to control the size of the output buffer \c objListOut
 *    - \c integralImgPitch should be multiple of 2
 *    - returns total number of trees for which processing happened
 *
 * @par Implementation Notes:
 *    - \c integralImgNonAlign can be set to Null to optimize L2 space, however there will be impact on cycle performance.
 *    - It's recommended to put all the data into internal memory for better cycle perforamnce.
 *    - To facilitate the placement of all the input and output into internal memory, image can be divided into multiple
 *      smaller set of rows for a single call of this API.
 *
 */

int32_t    VLIB_haarDetectObjectsDense(uint32_t integralImgAlign[restrict],
                                       uint32_t integralImgNonAlign[restrict],
                                       uint32_t integralImgWidth,
                                       uint32_t integralImgPitch,
                                       uint32_t integralImgHeight,
                                       uint32_t startStage,
                                       uint32_t endStage,
                                       uint32_t maxObjects,
                                       uint32_t yDirJump,
                                       VLIB_HAARDETOBJ_sClassifier classifier[restrict],
                                       VLIB_HAARDETOBJ_sObjectList objListOut[restrict],
                                       uint8_t scratch1[restrict],
                                       uint8_t scratch2[restrict]);
/** @} */
#endif

/* ======================================================================== */
/*  End of file:  VLIB_haarDetectObjectsDense.h                             */
/* ======================================================================== */

