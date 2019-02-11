/*
*
* Copyright (c) 2015-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/**
 *  @file       iSceneObstructionDetect_ti.h
 *  @brief     This file defines ivision interface for TI scene obstruction detection algorithm              
 *  @version 1.0 (December 2015) : Base version.
 */

/** @ingroup    ti_ivision_sceneObstructionDetect*/
/*@{*/
#ifndef ISCENEOBSTRUCTIONDETECT_TI_H
#define ISCENEOBSTRUCTIONDETECT_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/*#define _TEST_EDMA */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The unique const funtion table for the Scene Obstruction Detect algorithm.
 */
extern const IVISION_Fxns SCENE_OBSTRUCTION_DETECT_TI_VISION_FXNS;

/**
 * @brief IRES interface of the Scene Obstruction Detect algorithm
 */
extern const IRES_Fxns SCENE_OBSTRUCTION_DETECT_TI_IRES;

/**
 * @brief Macro symbols used in the Scene Obstruction Detect algorithm
 */
#define SCENE_OBSTRUCTION_DETECT_TI_MAX_PAXNUMH (9U)
#define SCENE_OBSTRUCTION_DETECT_TI_MAX_PAXNUMV (9U)
#define SCENE_OBSTRUCTION_DETECT_TI_NUM_COEFS (11U)

/**
  @brief Error code returned by the Scene Obstruction Detect algorithm

  ISCENE_OBSTRUCTION_DETECT_ERRORTYPE: 

  ISCENE_OBSTRUCTION_DETECT_ERRORTYPE_INVALID_IMAGE_DIMS: Image dimensions are
  beyond supported

  ISCENE_OBSTRUCTION_DETECT_ERRORTYPE_INVALID_NUM_INPUTS: Invalid number of input frames

  ISCENE_OBSTRUCTION_DETECT_TI_ERRORTYPE_INVALID_NUM_INPUTS: Invalid mumber of input buffers

  ISCENE_OBSTRUCTION_DETECT_ERRORTYPE_CREATE_FAIL: algorithm creation failed


 */
typedef enum
{
    SCENE_OBSTRUCTION_DETECT_TI_ERRORTYPE_0 = IVISION_CUSTOMFAILBASE,
    SCENE_OBSTRUCTION_DETECT_TI_ERRORTYPE_INVALID_NUM_INPUTS,
    SCENE_OBSTRUCTION_DETECT_TI_ERRORTYPE_CREATE_FAIL,
    SCENE_OBSTRUCTION_DETECT_TI_ERRORTYPE_MAX_ERROR_CODE
} SCENE_OBSTRUCTION_DETECT_TI_ErrorType;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There is 1 input buffers descriptor

  SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_IN_FV_STATS: This buffer descriptor provides the input focus values generated by the H3A engine 

 */
typedef enum
{
    SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_IN_FV_STATS= 0,
    SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_IN_TOTAL
} SCENE_OBSTRUCTION_DETECT_TI_InBufOrder ;


/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of out buffer
            There are 2 output buffers descriptor

            SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_OUT: This buffer is a single 32-bits word filled up by the algorithm. A value of 0 means the scene is not obstructed and a value of 1 means it is obstructed.
 */
typedef enum 
{
    SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_OUT = 0,
    SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_OUT_TOTAL
} SCENE_OBSTRUCTION_DETECT_TI_OutBufOrder;


/**

  @struct SCENE_OBSTRUCTION_DETECT_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          SCENE_OBSTRUCTION_DETECT algorithm at create time

  @param  visionParams
          Common parmeters for all ivison based modules

 *  @params paxNumH         : Number of AF paxels in H-direction
 *  @params paxNumV         : Number of AF paxels in V-direction
 *  @params vfEnable        : 0: vertical focus disabled, 1: vertical focus enabled
 *  @params classifierCoef  :  Coefficients of the classifier
 *  @params scaleFactor     : Scale factor that will be applied to the feature vector
 *  @params sensitivity     : sensitivity
 *  @params frameSkipInterval : Number of frames to be skipped between each execution of the algorithm
 *                              0 means the algorithm runs everyframe
 *                              1 means the algorithm runs every other frame
 *                              etc
 *  @params numBlockedFramesThreshold: Number of frames that have to be obstructed before outputting the scene obstruction event
 *  
  @param edma3RmLldHandle
          Pointer to the edma3lld resource manager handle
 */

typedef struct
{
    IVISION_Params visionParams;
    uint32_t wdrEnable;
    /**< Is WDR enabled, if yes then AF data of second/long exposure follows the first exposure */
    uint32_t paxNumH;
    /**< Number of AF paxels in H-direction, must be smaller or equal to SCENE_OBSTRUCTION_TI_DETECT_MAX_PAXNUMH*/
    uint32_t paxNumV;
    /**< Number of AF pacxels in V-direction, must be smaller or equal to SCENE_OBSTRUCTION_TI_DETECT_MAX_PAXNUMV*/
    uint32_t vfEnable;
    /**< 0: vertical focus disabled, 1: vertical focus enabled */
    float classifierCoef[SCENE_OBSTRUCTION_DETECT_TI_NUM_COEFS];
    /**< Coefficients of the classifier */
    float scaleFactor;
    /**< Scale factor that will be applied to the feature vector */
    float sensitivity;
    /**< Sensitivity value, 0: less sensitive, 10: most sensitive */
    uint32_t frameSkipInterval;
    /**< Number of frames to be skipped between each execution of the algorithm
     * 0 means the algorithm runs everyframe
     * 1 means the algorithm runs every other frame
     * etc
     */
    uint32_t numBlockedFramesThreshold;
    /** < Number of frames that have to be obstructed before outputting the scene obstruction event */
    void    * edma3RmLldHandle;
} SCENE_OBSTRUCTION_DETECT_TI_CreateParams;


/**

  @struct SCENE_OBSTRUCTION_DETECT_TI_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to SCENE_OBSTRUCTION_DETECT algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules
 */
typedef struct
{
    IVISION_InArgs iVisionInArgs;
} SCENE_OBSTRUCTION_DETECT_TI_InArgs;


/**

  @struct SCENE_OBSTRUCTION_DETECT_TI_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by Stereovision algorithm at frame level.
          They provide useful statistics pertaining to the disparity map.

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules
 */
typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
    int32_t rsvd1;
} SCENE_OBSTRUCTION_DETECT_TI_OutArgs;


/*@}*/
/* ti_ivision_SCENE_OBSTRUCTION_DETECT */

#ifdef __cplusplus
}
#endif

#endif /*ISCENE_OBSTRUCTION_DETECT_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                                                                           */
/*==========================================================================*/


