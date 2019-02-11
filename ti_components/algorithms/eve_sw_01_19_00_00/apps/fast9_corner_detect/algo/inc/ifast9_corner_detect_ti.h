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
 *  @file       ifast9_corner_detect_ti.h
 *
 *  @brief      This file defines the ivision interface for FAST9 corner detect Applet
 *  @version 0.0 (Dec 2013) : Base version.
 */

/** @ingroup    ti_ivision_FAST9_CORNER_DETECT */
/*@{*/
#ifndef IFAST9_CORNER_DETECT_TI_H
#define IFAST9_CORNER_DETECT_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
* @brief Using iVISION buf planes to get multiple pyramid so max value
         allowed (4) is depedant on iVISION
*/
#define FAST9_CORNER_DETECT_TI_MAXLEVELS   (IVISION_MAX_NUM_PLANES)


/**
 * @brief The unique const funtion table for the FAST9_CORNER_DETECT_TI.
 */
extern const IVISION_Fxns FAST9_CORNER_DETECT_TI_VISION_FXNS;

/**
* @brief IRES interface of the FAST9_CORNER_DETECT_TI_ algorithm
*/
extern const IRES_Fxns FAST9_CORNER_DETECT_TI_IRES;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There only 1 input buffers descriptor needed by this applet

  FAST9_CORNER_DETECT_TI_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by applet.

*/
typedef enum
{
  FAST9_CORNER_DETECT_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  FAST9_CORNER_DETECT_TI_BUFDESC_IN_TOTAL
} IFAST9_CORNER_DECTECT_InBufOrder ;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  FAST9_CORNER_DETECT_TI_BUFDESC_OUT_LISTBUFFER:
  This  buffer is filled up by applet and contains the list of corners detected
  by this applet upper 16 bits containing X coordinate and lower 16 bit containing
  Y coordinate
*/

typedef enum
{
  FAST9_CORNER_DETECT_TI_BUFDESC_OUT_LISTBUFFER = 0,
  FAST9_CORNER_DETECT_TI_BUFDESC_OUT_TOTAL
} IFAST9_CORNER_DECTECT_OutBufOrder ;

/**
  @brief This enum is used to selectively call process for particular level.
  User can create a mask with more than one fields of this enum by ORing these
  fields to update more than one parameters

  FAST9_CORNER_DETECT_TI_LEVEL_0:
  Execute Applet only for level 0

  FAST9_CORNER_DETECT_TI_LEVEL_1:
  Execute Applet only for level 1

  FAST9_CORNER_DETECT_TI_LEVEL_2:
  Execute Applet only for level 2

  FAST9_CORNER_DETECT_TI_LEVEL_3:
  Execute Applet only for level 3

  FAST9_CORNER_DETECT_TI_LEVEL_ALL:
  Execute Applet for all levels

*/

typedef enum
{
  FAST9_CORNER_DETECT_TI_LEVEL_0 = 1U, /* 1u << 0u, */
  FAST9_CORNER_DETECT_TI_LEVEL_1 = 2U, /* 1u << 1u, */
  FAST9_CORNER_DETECT_TI_LEVEL_2 = 4U, /*1u << 2u, */
  FAST9_CORNER_DETECT_TI_LEVEL_3 = 8U, /*1u << 3u, */
  FAST9_CORNER_DETECT_TI_LEVEL_ALL = 0xFF
} IFAST9_CORNER_DECTECT_levelMask ;

/**

  @struct FAST9_CORNER_DETECT_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          FAST9 corner detect applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  numLevels
          Number of levels in the pyramid

  @param  imgFrameWidth[]
          Width in bytes for the input image for all levels

  @param  imgFrameHeight[]
          Height in bytes for the input image for all levels

  @param  excludeBorderX
          Border to be excluded in X direction. This information will be helpful
          for applet to improve performance by reducing the effective imgFrameWidth.
          Even if this value is set to zero, the activeImgWidth can be lesser than
          imgFrameWidth. Refer activeImgWidth details provided below

  @param  excludeBorderY
          Border to be excluded in Y direction. This information will be helpful
          for applet to improve performance by reducing the effective imgFrameHeight.
          Even if this value is set to zero, the activeImgHeight can be lesser than
          imgFrameHeight. Refer activeImgHeight details provided below

*/
typedef struct
{
  IVISION_Params visionParams;
  uint8_t  numLevels;
  uint16_t imgFrameWidth[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t imgFrameHeight[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t excludeBorderX;
  uint16_t excludeBorderY;
} FAST9_CORNER_DETECT_TI_CreateParams;

/**

  @struct FAST9_CORNER_DETECT_TI_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to  FAST9 corner detect applet.

  @param  iVisionInArgs
          Common inArgs for all ivison based modules


  @param  fast9Threshold
          Threshold on difference between intensity of the central pixel and pixels
          of a circle around this pixel for FAST9 corner detect applet. This threshold
          should be provided for all levels in pyramid

  @param  levelMask
          This indicates which of the levels in pyramid should be executed for a particular
          process call. Kindly refer to @IFAST9_CORNER_DECTECT_levelMask for valid values

*/

typedef struct
{
  IVISION_InArgs iVisionInArgs;
  uint8_t fast9Threshold[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint8_t levelMask;
} FAST9_CORNER_DETECT_TI_InArgs;


/**

  @struct FAST9_CORNER_DETECT_TI_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by FAST9 corner detect applet.

  @param  visionParams
          Common outArgs for all ivison based modules

  @param  numCorners
          Total number of Key points (corners) detected. This information is given
          for all levels.

  @param  activeImgWidth
          activeImgWidth is primarily <= imgFrameWidth and decided by
          applet to satisfy the internal DMA and kernel requirements. This
          is the actual number of horizontal pixels being processed. It is
          exported for user as informative. This information is given for
          all levels.

  @param  activeImgHeight
          activeImgHeight is primarily <= imgFrameHeight and decided by
          applet to satisfy the internal DMA and kernel requirements. This
          is the actual number of vertical lines being processed. It is
          exported for user as informative. This information is given for
          all levels.

*/

typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  uint16_t numCorners[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t activeImgWidth[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t activeImgHeight[FAST9_CORNER_DETECT_TI_MAXLEVELS];
} FAST9_CORNER_DETECT_TI_OutArgs;

/*@}*/
/* ti_ivision_FAST9_CORNER_DETECT */

#endif /*IFAST9_CORNER_DETECT_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


