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
 *  @file       iHarrisCornerDetection32_ti.h
 *
 *  @brief      This file defines the ivision interface for Harros corner detection Applet
 *  @version 0.0 (Dec 2013) : Base version.
 */

/** @ingroup    iHARRIS_CORNER_DETECTION */
/*@{*/
#ifndef IHARRIS_CORNER_DETECTION_32_TI_H
#define IHARRIS_CORNER_DETECTION_32_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>

#define HARRIS_CORNER_DETECTION_MAX_NUM_CORNERS 1023

#define GRAD_FILTER_SZ    3u


/**
 * @brief Macro symbols used as command passed to the control API
 */
#define HARRIS_CORNER_DETECTION_GET_THRESHOLD 0x0 /* Get current NSM threshold */
#define HARRIS_CORNER_DETECTION_SET_THRESHOLD 0x1 /* Set NSM threshold */

/**
 * @brief The unique const funtion table for the HARRIS_CORNER_DETECTION_32_TI.
 */
extern const IVISION_Fxns HARRIS_CORNER_DETECTION_32_TI_VISION_FXNS;

/**
 * @brief IRES interface of the HARRIS_CORNER_DETECTION_32_TI_ algorithm
 */
extern const IRES_Fxns HARRIS_CORNER_DETECTION_32_TI_IRES;


/**
   @brief The format in which Harris corner detect applet output is expected to come

  HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_LIST: Output is the list of corners
    detected by this applet

  HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_BINARY_PACK : Output of corners
     in binary packed format where a bit value of 1 indicates a corner at that pixel location
     and 0 indicates its not a corner

     Byte0 -> Bit0 (LSB of the byte in binary image)
     Byte7 -> Bit7 (MSB of the byte in binary image)

     pixels : 0 1 2 3 4 5 6 7 8 9 10 will be present as
     Binary : 7 6 5 4 3 2 1 0 15 14 23 12 11 10 9 8 .... and so on
*/
typedef enum
{
  HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_LIST = 0,
  HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_BINARY_PACK
} HARRIS_CORNER_DETECTION_32_TI_OutputFormat;

/**
   @brief Supported size for Harris Score

  HARRIS_CORNER_DETECTION_32_TI_HARRIS_WINDOW_7x7: This enum is
  used to do Harris score calculation for a 7x7 window

  HARRIS_CORNER_DETECTION_32_TI_HARRIS_WINDOW_5x5: This enum is
  used to do Harris score calculation for a 5x5 window

  HARRIS_CORNER_DETECTION_32_TI_HARRIS_WINDOW_3x3: This enum is
  used to do Harris score calculation for a 3x3 window



*/
typedef enum
{
  HARRIS_CORNER_DETECTION_32_TI_HARRIS_WINDOW_7x7 = 0,
  HARRIS_CORNER_DETECTION_32_TI_HARRIS_WINDOW_5x5,
  HARRIS_CORNER_DETECTION_32_TI_HARRIS_WINDOW_3x3
} HARRIS_CORNER_DETECTION_32_TI_HarrisWindowSize;

/**
   @brief Method to be used for Suppression of corners

  HARRIS_CORNER_DETECTION_32_TI_SUPPRESSION_METHOD_NMS3x3: Use Non Maximum Suppresion
  in a window of size 3x3

  HARRIS_CORNER_DETECTION_32_TI_SUPPRESSION_METHOD_NMS5x5: Use Non Maximum Suppresion
  in a window of size 5x5

  HARRIS_CORNER_DETECTION_32_TI_SUPPRESSION_METHOD_NMS7x7: Use Non Maximum Suppresion
  in a window of size 7x7


*/
typedef enum
{
  HARRIS_CORNER_DETECTION_32_TI_SUPPRESSION_METHOD_NMS3x3= 0,
  HARRIS_CORNER_DETECTION_32_TI_SUPPRESSION_METHOD_NMS5x5,
  HARRIS_CORNER_DETECTION_32_TI_SUPPRESSION_METHOD_NMS7x7
} HARRIS_CORNER_DETECTION_32_TI_SuppressionMethod;

/**
   @brief Method to be used for Harris Score Calculation

  HARRIS_CORNER_DETECTION_32_TI_HARRIS_SCORE_METHOD_A: Score is defined as
    Harris Score = (Lamda1 * Lamda2) - k (Lamda1+ Lamda2)^2. This method is used
    to detect only corners in the image

 HARRIS_CORNER_DETECTION_32_TI_HARRIS_SCORE_METHOD_B : Score is defined as
    Harris Score = (Lamda1+ Lamda2). This method is used to detect  both corners and edges in the
    image

*/
typedef enum
{
  HARRIS_CORNER_DETECTION_32_TI_HARRIS_SCORE_METHOD_A= 0,
  HARRIS_CORNER_DETECTION_32_TI_HARRIS_SCORE_METHOD_B
} HARRIS_CORNER_DETECTION_32_TI_HarrisScoreMethod;


/**

  @struct HARRIS_CORNER_DETECTION_32_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          FAST9 corner detect applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imgFrameWidth
          Width in bytes for the input image

  @param  imgFrameHeight
          height in number of lines for the input image

  @param  maxNumCorners
          Maximum number of corners that the function can return

  @param  harrisScoreScalingFactor
          Scaling factor used by harris score kernel

  @param  nmsThresh
         Threshold used in non-maximum suppression. For exact format of the
         threshold kindly refer to harris score documentation in
         kernels/docs/vlib_on_EVE doc

@param harrisWindowSize
        Window size to be used for harris score calculation.  Considers a harrisWindowSize x harrisWindowSize
        neighborhood to calculate Harris Score. Kindly refer to HARRIS_CORNER_DETECTION_32_TI_HarrisWindowSize
        for valid values

 @param harrisScoreMethod
        Method to use for Harris Score calculation. Refer to
        HARRIS_CORNER_DETECTION_32_TI_HarrisScoreMethod for valid values

 @param suppressionMethod
        Suppression method to be used for non maximum suppression. Kindly refer to
        HARRIS_CORNER_DETECTION_32_TI_SuppressionMethod for valid values

 @param  outputFormat
        The format in which output is required. Kindly refer to
        HARRIS_CORNER_DETECTION_32_TI_OutputFormat for supported formats

 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t imgFrameWidth;
    uint16_t imgFrameHeight;
    uint16_t maxNumCorners;
    uint16_t harrisScoreScalingFactor;
    int32_t  nmsThresh;
    uint8_t  qShift;
    uint8_t  harrisWindowSize;
    uint8_t  harrisScoreMethod;
    uint8_t  suppressionMethod;
    uint8_t  outputFormat;
} HARRIS_CORNER_DETECTION_32_TI_CreateParams;


/**

  @struct HARRIS_CORNER_DETECTION_32_TI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  visionParams
          Common outArgs for all ivison based modules

  @param  numCorners
          Total number of Key points (corners) detected

  @param  activeImgWidth
          Width in bytes of the area that will be accessed by the EDMA when reading the frame.
          For this function, it should always be equal to (imgFrameWidth + TOTAL_FILTER_SZ)

  @param  activeImgHeight
          Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
          For this function, it should always be equal to (imgFrameHeight + TOTAL_FILTER_SZ)

  @param  outputBlockWidth
          Output block width in number of pixels returned by BAM_createGraph(). That's useful information to understand performance.

  @param  outputBlockheight
          Output block height in number of rows returned by BAM_createGraph(). That's useful information to understand performance.

 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
    uint16_t numCorners;
    uint16_t activeImgWidth;
    uint16_t activeImgHeight;
    uint16_t outputBlockWidth;
    uint16_t outputBlockHeight;

} HARRIS_CORNER_DETECTION_32_TI_outArgs;

/**

  @struct HARRIS_CORNER_DETECTION_32_TI_ControlInParams
  @brief  This structure contains all the input parameters which controls
          the applet after creation

  @param  algParams
          Common params for all IALG based modules

  @param  nmsThreshold
          Threshold for the NMS function that will be updated by the control function

 */
typedef struct
{
    IALG_Params algParams;
    int32_t nmsThreshold;

} HARRIS_CORNER_DETECTION_32_TI_ControlInParams;

/**

  @struct HARRIS_CORNER_DETECTION_32_TI_ControlOutputParams
  @brief  This structure contains all the output parameters written by the control function
          the applet after creation

  @param  algParams
          Common params for all IALG based modules

  @param  nmsThreshold
          Threshold for the NMS function, returned by the control function

 */
typedef struct
{
    IALG_Params algParams;
    int32_t nmsThreshold;

} HARRIS_CORNER_DETECTION_32_TI_ControlOutParams;

/*@}*/
/* iHARRIS_CORNER_DETECTION_32 */

#endif /*IHARRIS_CORNER_DETECTION_32_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


