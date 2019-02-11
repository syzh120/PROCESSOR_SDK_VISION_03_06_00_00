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
 *  @file       iImagePyramid_u8_ti.h
 *
 *  @brief      This file defines the ivision interface for image pyramid detection Applet
 *  @version 0.0 (Dec 2013) : Base version.
 */

/** @ingroup    iIMAGEPYRAMID_U8 */
/*@{*/
#ifndef IIMAGE_PYRAMID_U8_TI_H
#define IIMAGE_PYRAMID_U8_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>

#define IMGPYRAMID_MAX_NUM_LEVELS (5U)

/**
 * @brief The unique const funtion table for the IMAGE_PYRAMID_U8_TI.
 */
extern const IVISION_Fxns IMAGE_PYRAMID_U8_TI_VISION_FXNS;

/**
 * @brief IRES interface of the IMAGE_PYRAMID_U8_TI_ algorithm
 */
extern const IRES_Fxns IMAGE_PYRAMID_U8_TI_IRES;

typedef enum {
    IMAGE_PYRAMID_U8_TI_2x2_AVERAGE= 0,
    IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN= 1,
    IMAGE_PYRAMID_U8_TI_MAX= 2
} IMAGE_PYRAMID_U8_TI_FilterType;
/**

  @struct IMAGE_PYRAMID_U8_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          FAST9 corner detect applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imgFrameWidth
          Width in bytes for the input image

  @param  imgFrameHeight
          height in number of lines for the input image

  @param  numLevels
          Number of image pyramid levels

  @param  filterType
          Filter type can be IMAGE_PYRAMID_U8_TI_2x2_AVERAGE or IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN

 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t imgFrameWidth;
    uint16_t imgFrameHeight;
    uint8_t numLevels;
    uint8_t filterType;
} IMAGE_PYRAMID_U8_TI_CreateParams;


/**

  @struct IMAGE_PYRAMID_U8_TI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

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

} IMAGE_PYRAMID_U8_TI_outArgs;

/*@}*/
/* iIMAGE_PYRAMID_U8 */

#endif /*IIMAGE_PYRAMID_U8_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


