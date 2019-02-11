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
 *  @file       iosft_isp16_ti.h
 *
 *  @brief      This file defines the ivision interface for channel generation
 *  @version 0.0 (March 2017) : Base version.
 */

/** @ingroup    iSoftIsp16 */
/*@{*/
#ifndef ISOFT_ISP16_H
#define ISOFT_ISP16_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>

#define SOFT_ISP16_TI_RAW2RGB_G_NEIGHBORHOOD_SIZE  4U
#define SOFT_ISP16_TI_RAW2RGB_RB_NEIGHBORHOOD_SIZE 3U

#define SOFT_ISP16_TI_RAW2RGB_NEIGHBORHOOD_SIZE 7U

/**
 * @brief Macro symbols used as command passed to the control API
 */
#define SOFT_ISP16_TI_GET_OUTPUT_BLOCK_DIM 0x0 /* Get output block's dimensions (width & height) derived during applet creation */
#define SOFT_ISP16_TI_SET_PARAMS 0x1 /* set dynamic parameteres through control API  */

/**
 * @brief Macro symbols used as error code returned by the alloc init, process, control or deinit APIs.
 *
 *  SOFT_ISP16_TI_ERROR_INVALID_ROI_DIM: One of the ROI dimensions (width/height) passed to process API is not multiple of the output block width/height
 *
 */
typedef enum
{
    SOFT_ISP16_TI_ERROR_INVALID_ROI_DIM = IALG_CUSTOMFAILBASE
} SOFT_ISP16_TI_ErrorCodes ;
#define SOFT_ISP16_TI_ERROR_INVALID_ROI_DIM (-256) /* One of the ROI dimensions (width/height) passed to process API is not multiple of the output block width/height */
/**
 * @brief The unique const funtion table for the SOFT_ISP16.
 */
extern const IVISION_Fxns SOFT_ISP16_TI_VISION_FXNS;

/**
 * @brief IRES interface of the SOFT_ISP16_TI_ algorithm
 */
extern const IRES_Fxns SOFT_ISP16_TI_IRES;

/**
    @brief  User provides most of the information through buffer descriptor
            during process call. Below enums define the purpose of buffer
            There is 1 input buffers descriptor

            SOFT_ISP16_TI_BUFDESC_IN: This buffer descriptor provides the
            actual image data required by algorithm. The data is composed of 16-bits data

*/
typedef enum
{
    SOFT_ISP16_TI_BUFDESC_IN = 0,
    SOFT_ISP16_TI_BUFDESC_IN_TOTAL
} SOFT_ISP16_TI_InBufOrder ;

/**
    @brief  User provides most of the information through buffer descriptor
            during process call. Below enums define the purpose of out buffer
            There is 1 output buffers descriptor

            SOFT_ISP16_TI_BUFDESC_OUT: This buffer is filled up by the algorithm and will contain
            the difference of gaussian output. Each output element is 2 bytes.
*/
typedef enum
{
    SOFT_ISP16_TI_BUFDESC_OUT = 0,
    SOFT_ISP16_TI_BUFDESC_OUT_TOTAL
} SOFT_ISP16_TI_OutBufOrder ;

typedef enum {
    SOFT_ISP16_BAYER_PATTERN_GBRG = 0,
    SOFT_ISP16_BAYER_PATTERN_GRBG,
    SOFT_ISP16_BAYER_PATTERN_BGGR,
    SOFT_ISP16_BAYER_PATTERN_RGGB,
    SOFT_ISP16_BAYER_PATTERN_TOTAL
} SOFT_ISP16_TI_BayerPattern;

/**

  @struct SOFT_ISP16_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          census transform applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imgFrameWidth
          Width in pixels for the input image, must be multiple of 16

  @param  imgFrameHeight
          Height in number of lines for the input image, must be multiple of 8

 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t imgFrameWidth;
    uint16_t imgFrameHeight;
    int32_t  bayerPattern;
} SOFT_ISP16_TI_CreateParams;


/**

  @struct SOFT_ISP16_TI_inArgs
  @brief  This structure contains all the parameters which are given as an input to the applet at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivision based modules

*/

typedef struct
{
  IVISION_InArgs iVisionInArgs;
} SOFT_ISP16_TI_InArgs;


/**

  @struct SOFT_ISP16_TI_outArgs
  @brief  This structure contains all the parameters are given as an output by the applet at frame level

  @param  visionParams
          Common outArgs for all ivison based modules

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
    uint16_t activeImgWidth;
    uint16_t activeImgHeight;
    uint16_t outputBlockWidth;
    uint16_t outputBlockHeight;

} SOFT_ISP16_TI_OutArgs;

/**

  @struct SOFT_ISP16_TI_ControlInParams
  @brief  This structure contains all the input parameters which controls
          the applet after creation.
          In the case of DiffOfGauss transform, it does not have any additional parameters
          than the default algParams from which it inherits the content.

  @param  algParams
          Common params for all IALG based modules

 */
typedef struct
{
    IALG_Params algParams;
} SOFT_ISP16_TI_ControlInParams;

/**

  @struct SOFT_ISP16_TI_ControlOutputParams
  @brief  This structure contains all the output parameters written by the control function
          the applet after creation. Mainly it contains output block dimensions which can be queried
          after graph creation. The application should use these values to make sure that any ROI's width and height
          are multiple of the output block's width and height.

  @param  algParams
          Common params for all IALG based modules

  @param  outputBlockWidth
          output block width

  @param  outputBlockHeight
          output block height

 */
typedef struct
{
    IALG_Params algParams;
    uint16_t outputBlockWidth;
    uint16_t outputBlockHeight;

} SOFT_ISP16_TI_ControlOutParams;

/*@}*/
/* iSOFT_ISP16 */

#endif /*ISOFT_ISP16_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


