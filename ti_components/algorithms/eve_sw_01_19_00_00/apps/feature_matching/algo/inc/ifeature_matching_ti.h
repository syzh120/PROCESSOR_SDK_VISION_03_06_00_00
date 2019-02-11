/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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
 *  @file       ifeature_matching_ti.h
 *
 *  @brief      This file defines the ivision interface for Feature Matching
 *              applet
 *
 *  @version 0.1 (Aug 2014) : Base version.
 */

/** @ingroup    ti_ivision_FEATURE_MATCHING */
/*@{*/
#ifndef IFEATURE_MATCHING_TI_H_
#define IFEATURE_MATCHING_TI_H_

#include <ivision.h>
#include <ti/xdais/ires.h>


#define FEATURE_MATCHING_TI_MAX_DESCRIPTOR_LENGTH (512U)


/**
 * @brief The unique const funtion table for the FEATURE_MATCHING_TI.
 */
extern const IVISION_Fxns FEATURE_MATCHING_TI_VISION_FXNS;

/**
* @brief IRES interface of the FEATURE_MATCHING_TI algorithm
*/
extern const IRES_Fxns FEATURE_MATCHING_TI_IRES;

typedef enum
{
  FEATURE_MATCHING_TI_ERRORTYPE_MAX_DESCRIPTOR_LEN_EXCEEDED = IALG_CUSTOMFAILBASE,
  FEATURE_MATCHING_TI_ERRORTYPE_INSUFFICIENT_MEMORY

} FEATURE_MATCHING_TI_ErrorType;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1: This buffer descriptor provides the
  list of feature descriptors for which correspondence needs to be found.

  FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2: This buffer descriptor provides the
  list of feature descriptors from which correspondence needs to be searched for.

*/

typedef enum
{
  FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1 = 0,
  FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2,
  FEATURE_MATCHING_TI_BUFDESC_IN_TOTAL
} FEATURE_MATCHING_TI_InBufOrder;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  FEATURE_MATCHING_TI_BUFDESC_OUT_CORRESPONDENCE:
  This buffer descriptor should point to a buffer capable of holding the
  list of indices from second feature descriptor list which correspond to
  each feature descriptor in the first list.

*/

typedef enum
{
  FEATURE_MATCHING_TI_BUFDESC_OUT_CORRESPONDENCE = 0,
  FEATURE_MATCHING_TI_BUFDESC_OUT_TOTAL
} FEATURE_MATCHING_TI_OutBufOrder;


/**
  @brief Control Command indices for the FEATURE_MATCHING_TI algorithm

  FEATURE_MATCHING_TI_CONTROL_GET_BUF_SIZE
  The algorithm expects the input and output buffers to be satisfy certain
  contraints. These details are communicated to the user using a control
  call with this index. Given the input create time parameters, the control
  call return the buffer constraints through the output parameters of
  FEATURE_MATCHING_TI_CtrlParams structure. This control call is optional
  in case user can statically provide bigger input and output buffers. In
  case input buffer can have extra space for upto 128 descriptors and space
  for extra 128 indices (16-bit) in output buffer, the control call need not
  be made. The data in the padded region of input buffers does not effect
  the valid outputs. The data produced in extra region in output buffer can
  be ignored.

*/
typedef enum
{
  FEATURE_MATCHING_TI_CONTROL_GET_BUF_SIZE,
  FEATURE_MATCHING_TI_CONTROL_MAX
} FEATURE_MATCHING_TI_ControlCommand;


/**
  @struct FEATURE_MATCHING_TI_CreateParams

  @brief  This structure contains all the parameters which controls
          FEATURE_MATCHING applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  descriptorLength
          Length of each feature descriptor in bytes.

*/

typedef struct
{
  IVISION_Params visionParams;
  uint16_t       descriptorLength;

} FEATURE_MATCHING_TI_CreateParams;


/**
  @struct FEATURE_MATCHING_TI_CtrlParams

  @brief  This structure contains the input and output parameters for
          the FEATURE_MATCHING_TI_CONTROL_GET_BUF_SIZE control call of
          the FEATURE_MATCHING applet

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  numDescriptors1
          Number of feature descriptors in list 1

  @param  numDescriptors2
          Number of feature descriptors in list 2

  @param  in1BufSize
          Minimum size in bytes for the first feature descriptor list
          buffer

  @param  in2BufSize
          Minimum size in bytes for the second feature descriptor list
          buffer

  @param  outBufSize
          Minimum size in bytes for the output (feature correspondence)
          buffer

*/
typedef struct
{
  /* Input parameters */
  IVISION_Params visionParams;
  uint16_t   numDescriptors1;
  uint16_t   numDescriptors2;

  /* Output parameters */
  uint32_t   in1BufSize;
  uint32_t   in2BufSize;
  uint32_t   outBufSize;

} FEATURE_MATCHING_TI_CtrlParams;



/**
  @struct FEATURE_MATCHING_TI_InArgs

  @brief  This structure contains all the parameters which are given as an
          input to Feature Matching applet.

  @param  iVisionInArgs
          Common inArgs for all ivison based modules

  @param  minDistanceThres
          Minimum distance between features for declaring a match

  @param  matchConfidence
          Parameter to control ratio test used for eliminating matches that
          are ambiguous - i.e. the best match (minDist0) and next best match
          (minDist1) are very close to one another. A match is declared only
          if minDist0 <= (1 - matchConfidence)*minDist1.
          The parameter value can vary from 0 to 1 and should be provided in
          U1.15 format.

*/
typedef struct
{
  IVISION_InArgs iVisionInArgs;
  uint16_t       minDistanceThres;
  uint16_t       matchConfidence;

} FEATURE_MATCHING_TI_InArgs;


/**
  @struct FEATURE_MATCHING_TI_OutArgs

  @brief  This structure contains all the parameters which are given as an
          output by Feature Matching applet.

  @param  visionParams
          Common outArgs for all ivison based modules

*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
} FEATURE_MATCHING_TI_OutArgs;


/*@}*/
/* ti_ivision_FEATURE_MATCHING */

#endif /*_IFEATURE_MATCHING_TI_H_ */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/
