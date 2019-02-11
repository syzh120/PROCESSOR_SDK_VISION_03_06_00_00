/*
*
* Copyright (c) {2018} Texas Instruments Incorporated
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
-----------------------------------------------------------------------------
@file    iop_ti.h
@brief   This file defines ivision interface for TI object propagation module
@version 0.1 (July 2018) : Initial Code [EPR]
----------------------------------------------------------------------------
*/

/** @ingroup    iOP_TI */
/*@{*/
#ifndef IOP_TI_H
#define IOP_TI_H

#include <ivision.h>
#include <stdint.h>

/**
* @brief The unique const funtion table for the TI object propagation algorithm.
*/
extern const IVISION_Fxns TIOP_VISION_FXNS;

/**
 * Max number of detected objects in the frame.
 */
#define TIOP_MAX_DETECT_OBJECTS   200 

/**
  @brief Error codes returned by the TIOP algorithm

  TIOP_E_INVALID_MAXDETECTOBJECTS: The number of
  input detections are more than detections 
  allocated by TIOP algorithm

  TIOP_E_INVALID_MAXNUMLEVELS: The num levels
  is more than Max Num levels(5) supported by TIOP

  TIOP_E_INVALID_MAXLKITERS: The LK tracker iterations
  is more than Max LK tracker iterations(10) 
  supported by TIOP algorithm

  TIOP_E_INVALID_MAXKEYPOINTS: The total ketpoints 
  detected are more than TIOP_MAX_KEY_POINTS (2048) 
  supported by TIOP algorithm

  TIOP_E_INVALID_MAXL2SCRATCHMEM: The allocated 
  Internal scratch memory (L2SRAM) is not sufficient 
  for TIOP algorithm
  
*/
typedef enum
{
  TIOP_E_INVALID_MAXDETECTOBJECTS = IVISION_CUSTOMFAILBASE,
  TIOP_E_INVALID_MAXNUMLEVELS,
  TIOP_E_INVALID_MAXLKITERS,
  TIOP_E_INVALID_MAXKEYPOINTS,
  TIOP_E_INVALID_MAXL2SCRATCHMEM,
  ILD_ERRORTYPE_MAX_ERROR_CODE
} eTIOP_ErrorType;

/**
  @enum  TIOP_InBufOrder
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

         If 0, TIOP_IN_BUFDESC_INPUT_FRAME: This buffer descriptor provides one
               input frame in Y format.
         If 1, TIOP_IN_BUFDESC_DETECTION_LIST: This buffer descriptor provides the
               list of detected objects in the input frame
         If 2, TIOP_IN_BUFDESC_IPBUF_LEVEL1: This buffer descriptor provides the
               external computed image pyramidal buffer for level1
         If 3, TIOP_IN_BUFDESC_IPBUF_LEVEL2: This buffer descriptor provides the
               external computed image pyramidal buffers for level2
         If 4, TIOP_IN_BUFDESC_IPBUF_LEVEL3: This buffer descriptor provides the
               external computed image pyramidal buffers for level3
         If 5, TIOP_IN_BUFDESC_IPBUF_LEVEL4: This buffer descriptor provides the
               external computed image pyramidal buffers for level4
         If 6, TIOP_IN_BUFDESC_OPTICAL_FLOW: This buffer descriptor provides the 
               external computed dense optical flow buffer for the input
         If 7, TIOP_IN_BUFDESC_TOTAL
*/
typedef enum
{
  TIOP_IN_BUFDESC_INPUT_FRAME = 0,
  TIOP_IN_BUFDESC_DETECTION_LIST,
  TIOP_IN_BUFDESC_IPBUF_LEVEL1,
  TIOP_IN_BUFDESC_IPBUF_LEVEL2,
  TIOP_IN_BUFDESC_IPBUF_LEVEL3,
  TIOP_IN_BUFDESC_IPBUF_LEVEL4,
  TIOP_IN_BUFDESC_OPTICAL_FLOW,
  TIOP_IN_BUFDESC_TOTAL
} TIOP_InBufOrder;

/**
  @enum  TIOP_OutBufOrder
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

         If 0, TIOP_OUT_BUFDESC_OBJECT_LIST - Output buffer is a new list
               of detected objects.
         If 1, TIOP_OUT_BUFDESC_TOTAL
  */

typedef enum
{
  TIOP_OUT_BUFDESC_OBJECT_LIST = 0,
  TIOP_OUT_BUFDESC_TOTAL

} TIOP_OutBufOrder;

#define TIOP_MAX_ALG_IN_BUFS   TIOP_IN_BUFDESC_TOTAL
#define TIOP_MAX_ALG_OUT_BUFS  TIOP_OUT_BUFDESC_TOTAL

/**
  @enum  TIOP_InFrameOrder
  @brief User provides one frame at a time but algorithm needs two frames 
         for detecting propagated objects. So, algorithm holds previous 
         frame for processing current frame  
*/
typedef enum
{
  TIOP_INPUT_PREV_FRAME     = 0,
  TIOP_INPUT_CURR_FRAME     = 1,
  TIOP_INPUT_TOTAL_FRAMES   = 2  
} TIOP_InFrameOrder ;

/**
  @struct TIOP_CreateParams
  @brief  This structure contains all the parameters which TI OP
          library at create time
  @param  visionParams
          Common parmeters for all ivison based modules
  @param  inMaxWidth
          Maximum image Width of the input frame 
  @param  inMaxHeight
          Maximum image Height of the input frame 
  @param  numLevels
          Number of Levels for LK Tracker
  @param  maxItersLK
          Number of iterations for LK Tracker 
  @param  harrisScoreScalingFactor
          Harris Score Factor (k) in 0.15 format
  @param  nmsThresh
          Threshold for Harris Score for NMS
  @param  maxAgeThresh
          Threshold for max age of the propagted object
  @param  lkErrThresh
          Threshold for LK tracker error 
  @param  numClasses
          number of classes in input detected objects 
  @param  numInDetections
          Total number of detected objects in input frame
  @param  extImagePyramidal
          Flag to indicate externally calculted Image  
          pyramidal buffers are provided to TIOP module
  @param  extOpticalFlow
          Flag to indicate externally calculted dense  
          optical flow buffer is provided to TIOP module
  @param  l1MemSize
          Indicates the available l1MemSize for TIOP
  @param  l2MemSize
          Indicates available l2MemSize(L2SRAM) for TIOP
  @param  confScoreGoodObjs
          Confidence score for good objects 
  @param  confScoreModObjs
          Confidence score for Moderate objects 
  @param  maxOverlapThresh
          Threshold for overlap NMS
*/
typedef struct
{
  IVISION_Params visionParams;
  int32_t inMaxWidth  ;
  int32_t inMaxHeight ;
  int32_t numLevels      ;
  int32_t maxItersLK     ;
  int32_t harrisScoreScalingFactor ;
  int32_t nmsThresh ;
  int32_t maxAgeThresh ;
  int32_t lkErrThresh ;
  int32_t numClasses ;
  int32_t numInDetections;
  int32_t extImagePyramidal;
  int32_t extOpticalFlow;
  int32_t l1MemSize;
  int32_t l2MemSize;
  float confScoreGoodObjs ;
  float confScoreModObjs ;
  float maxOverlapThresh ;
} TIOP_CreateParams;

/**
  @struct TIOP_InArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time
  @param  iVisionInArgs
          Common inArgs for all ivison based modules
  @param  numInBufs
          Number of input buffers to TIOP module
  @param  numInObjects
          Number of detected objects in the input frame                     
*/

typedef struct
{
  IVISION_InArgs iVisionInArgs;
  int32_t numInBufs;
  int32_t numInObjects;  
} TIOP_InArgs;

/**
  @struct TIOP_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time
  @param  iVisionOutArgs
          Common outArgs for all ivison based modules
  @param  numOutBufs
          Number of output buffers from the TIOP module
  @param  numOutObjects
          Number of new list of detected objects by TIOP module          
*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  int32_t numOutBufs;
  int32_t numOutObjects;  
} TIOP_outArgs;


/**
  @struct TIOP_objectDescriptor

  @brief  This structure contains the detected object properties
          such as location-(xmin, ymin),(xmax, ymax), confidence (score)

  @param  objId
          Unique value to identify the number of detected object, this 
          value is >= 0 for valid objects, -1 means not valid objects and
          rest of the objects after "-1" in the list are not valid         
          
  @param  objClass
          Indicates the class of object detected.

  @param  objScore
          Indicates the score for the detected object.

  @param  xMin
          Location minimum (top left) of the detected object along X direction.
          In the inBuf and outBuf, these values are from 0 to 1 as they are  
          divided by width. 

  @param  yMin
          Location minimum (top left) of the detected object along Y direction.
          In the inBuf and outBuf, these values are from 0 to 1 as they are  
          divided by height. 

  @param  xMax
          Location maximum (bottom right) of the detected object along X direction.
          In the inBuf and outBuf, these values are from 0 to 1 as they are  
          divided by width. 

  @param  yMax
          Location maximum (bottom right) of the detected object along Y direction.
          In the inBuf and outBuf, these values are from 0 to 1 as they are  
          divided by height. 
*/
typedef struct
{
  float   objId;
  float   objClass;
  float   objScore;
  float   xMin;
  float   yMin;
  float   xMax;
  float   yMax;
} TIOP_objectDescriptor;

/**
  @struct TIOP_inputList
  @brief  This is input buffer structure given to object propagation
          module along with input frame buffer. It contains the 
          number of objects detected and TIOP_MAX_DETECT_OBJECTS 
          instances of TIOP_objectDescriptor structure. 
          The number of valid descriptors is governed by
          numInObjects variable.

  @param  numInObjects
          Number of detected objects in the input frame.

  @param  inObjDesc
          List of detected object descriptor for input.
          Max size TIOP_MAX_DETECT_OBJECTS

*/
typedef struct
{
  int32_t numInObjects;
  TIOP_objectDescriptor inObjDesc[TIOP_MAX_DETECT_OBJECTS];
} TIOP_inputList;

/**
  @struct TIOP_outputList
  @brief  This is output buffer structure given out by object propagation
          module. It contains the number of new list of objects and
          TIOP_MAX_DETECT_OBJECTS instances of TIOP_objectDescriptor
          structure. The number of valid descriptors is governed by
          numOutObjects variable.

  @param  numOutObjects
          Number of new list of objects by object propagation module.

  @param  outObjDesc
          List of detected object descriptor for output.
          Max size TIOP_MAX_DETECT_OBJECTS

*/
typedef struct
{
  int32_t numOutObjects;
  TIOP_objectDescriptor outObjDesc[TIOP_MAX_DETECT_OBJECTS];
} TIOP_outputList;

/*
 * Total input list size to be allocated by the application. This is
 * the second input buffer to be allocated by the application,
 * along with the first input buffer that is input frame. 
 */
#define TIOP_IN_BUFDESC_LIST_SIZE (sizeof(TIOP_inputList))

/*
 * Total size of the output buffer to be allocated by the application.
 */
#define TIOP_OUT_BUFDESC_LIST_SIZE (sizeof(TIOP_outputList))


/*@}*/
/* iOP_TI */

#endif /*IOP_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


