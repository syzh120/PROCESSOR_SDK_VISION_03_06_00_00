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
 *  @file    iedge_detector_ti.h
 *
 *  @brief   This file defines the ivision interface for Edge Detector
 *           applet
 *  @version 0.1 (Dec 2014) : Base version.
 */

/** @ingroup    ti_ivision_EDGE_DETECTOR */
/*@{*/
#ifndef IEDGE_DETECTOR_TI_H_
#define IEDGE_DETECTOR_TI_H_

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the EDGE_DETECTOR_TI.
 */
extern const IVISION_Fxns EDGE_DETECTOR_TI_VISION_FXNS;

/**
* @brief IRES interface of the EDGE_DETECTOR_TI algorithm
*/
extern const IRES_Fxns EDGE_DETECTOR_TI_IRES;


typedef enum
{
  EDGE_DETECTOR_TI_ERRORTYPE_ = IALG_CUSTOMFAILBASE,
  EDGE_DETECTOR_TI_ERRORTYPE_MAX_ERROR_CODE
} EDGE_DETECTOR_TI_ErrorType;


/**
  @brief Edge detection can be done using different methods. Following is the
  enum for all the supported methods by this applet

  EDGE_DETECTOR_TI_METHOD_SOBEL: Use Sobel Edge Detector

  EDGE_DETECTOR_TI_METHOD_CANNY: Use Canny edge detection method for edge detection


*/
typedef enum
{
  EDGE_DETECTOR_TI_METHOD_SOBEL= 0,
  EDGE_DETECTOR_TI_METHOD_CANNY,
  EDGE_DETECTOR_TI_METHOD_MAX
} EDGE_DETECTOR_TI_Method;


/**
   @brief The format in which edge detection output is expected to come

  EDGE_DETECTOR_TI_OUTPUT_FORMAT_BYTE_EDGEMAP: Output edge map image whose
      each pixel  value is 255  if its an edge and 0 if its  not an edge

  EDGE_DETECTOR_TI_OUTPUT_FORMAT_BINARY_PACK : Output edge map as a binary image
     with following mapping
     Byte0 -> Bit0 (LSB of the byte in binary image)
     Byte7 -> Bit7 (MSB of the byte in binary image)

     pixels :0 1 2 3 4 5 6 7 8 9 10 will be present as
     Binary : 7 6 5 4 3 2 1 0 15 14 23 12 11 10 9 8 .... and so on


*/
typedef enum
{
  EDGE_DETECTOR_TI_OUTPUT_FORMAT_BYTE_EDGEMAP = 0,
  EDGE_DETECTOR_TI_OUTPUT_FORMAT_BINARY_PACK
} EDGE_DETECTOR_TI_OutputFormat;

/**
   @brief  Which norm to be used for edge detection

   EDGE_DETECTOR_TI_NORM_L1: Use L1 Norm ie.Mag =abs(X)+abs(Y)



*/
typedef enum
{
  EDGE_DETECTOR_TI_NORM_L1= 0
} EDGE_DETECTOR_TI_NormType;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE:
  This buffer descriptor (inBufs->bufDesc[EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE])
  should point to a buffer descriptor containing image for which edge detection needs to  be
  performed

*/
typedef enum
{
  EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE   = 0,
  EDGE_DETECTOR_TI_BUFDESC_IN_TOTAL
} EDGE_DETECTOR_TI_InBufOrder;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  EDGE_DETECTOR_TI_BUFDESC_OUT_IMAGE_BUFFER:
  This buffer will return edge detected image based in the format
  specified by the user using the enum. It is important to note
  that when method used is Canny the output is not the edges detectd. Instead
  output is an image with each pixel classified into three states:
  Pixel value 0 : For non edge pixels
  Pixel value 1 : For Pixels which are above low threshold and beloe the high threshold
  Pixel value 255 : For Pixels which are edge pixels
*/

typedef enum
{
  EDGE_DETECTOR_TI_BUFDESC_OUT_IMAGE_BUFFER = 0,
  EDGE_DETECTOR_TI_BUFDESC_OUT_TOTAL
} EDGE_DETECTOR_TI_OutBufOrder ;

/**
  @brief Following are the control commands supported by this applet

  EDGE_DETECTOR_TI_CONTROLCMD_GET_INPUT_BUFFER_SIZE:
    This control command ID can be used to optionally query the memory needed for
    input buffer.
*/
typedef enum
{
  EDGE_DETECTOR_TI_CONTROLCMD_GET_INPUT_BUFFER_SIZE,
  EDGE_DETECTOR_TI_CONTROLCMD_MAX
} EDGE_DETECTOR_TI_ControlCmdIdType;

/**

  @struct EDGE_DETECTOR_TI_CreateParams
  @brief  This structure contains all the parameters needed at create time
          for this applet

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  method
          The method to be used for edge detection. Refer to EDGE_DETECTOR_TI_Method
          for supported methods

  @param  outputFormat
          The output format for the edge detector output. Refer to EDGE_DETECTOR_TI_OutputFormat
          for supported formats

  @param  normType
          Which type of norm to use to calculate magnitude. Refer to EDGE_DETECTOR_TI_NormType
          for supported norms

*/
typedef struct
{
  IVISION_Params visionParams;
  uint8_t method;
  uint8_t outputFormat;
  uint8_t normType;
} EDGE_DETECTOR_TI_CreateParams;


/**

  @struct EDGE_DETECTOR_TI_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to the applet at frame level

  @param  iVisionInArgs
          Common InArgs for all ivison based modules

  @param  threshold1
          If sobel edge detector is used then this is the only threshold applied. But if
          Canny Edge detector is used then this is the first threshold for the hysteresis procedure.

  @param  threshold2
          If sobel edge detector is used then this field is a dont care. But if
          Canny Edge detector is used then this is the second threshold for the hysteresis procedure.

*/
typedef struct
{
  IVISION_InArgs  iVisionInArgs;
  uint8_t         threshold1;
  uint8_t         threshold2;
} EDGE_DETECTOR_TI_InArgs;


/*@}*/
/* ti_ivision_EDGE_DETECTOR */

#endif /*IEDGE_DETECTOR_TI_H_ */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/

