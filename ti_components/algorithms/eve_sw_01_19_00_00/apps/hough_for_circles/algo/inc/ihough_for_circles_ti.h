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
 *  @file    ihough_for_circles_ti.h
 *
 *  @brief   This file defines the ivision interface for Hough for Circles
 *           applet
 *  @version 0.1 (Sept 2014) : Base version.
 */

/** @ingroup    ti_ivision_HOUGH_FOR_CIRCLES */
/*@{*/
#ifndef IHOUGH_FOR_CIRCLES_TI_H_
#define IHOUGH_FOR_CIRCLES_TI_H_

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the HOUGH_FOR_CIRCLES_TI.
 */
extern const IVISION_Fxns HOUGH_FOR_CIRCLES_TI_VISION_FXNS;

/**
* @brief IRES interface of the HOUGH_FOR_CIRCLES_TI algorithm
*/
extern const IRES_Fxns HOUGH_FOR_CIRCLES_TI_IRES;

/**
* @brief Maximum number of Circles detected for a single radius
*/
#define HOUGH_FOR_CIRCLES_TI_MAX_NUM_CIRCLE_PER_RADIUS  (1000)


/**
* @brief Maximum number of radii for which circle detection using Hough
         transform can be performed in a single process call of this
         applet
*/
#define HOUGH_FOR_CIRCLES_TI_MAX_NUM_RADIUS   (32U)


typedef enum
{
  HOUGH_FOR_CIRCLES_TI_ERRORTYPE_RADIUS_BEYOND_RANGE = IALG_CUSTOMFAILBASE,
  HOUGH_FOR_CIRCLES_TI_ERRORTYPE_NUM_RADIUS_UNSUPPORTED,
  HOUGH_FOR_CIRCLES_TI_ERRORTYPE_MAX_ERROR_CODE
} HOUGH_FOR_CIRCLES_TI_ErrorType;


/**
  @brief The voting scheme in the Hough for Circles implementation depends
         on the type of circle being analysed - whether the circular object
         to be detected is 'bright' or 'dark'. By 'bright' we mean a bright
         circular object on a dark background. The enum list a possible set
         of options user can specify the type of circular objects to be
         detected by the applet.

  HOUGH_FOR_CIRCLES_TI_CIRCLE_DARK: Dark circular object on a bright background.
  HOUGH_FOR_CIRCLES_TI_CIRCLE_BRIGHT: Bright circular object on a dark background.
  HOUGH_FOR_CIRCLES_TI_CIRCLE_BOTH: Both bright and dark circular objects.

*/
typedef enum
{
  HOUGH_FOR_CIRCLES_TI_CIRCLE_DARK   = 0,
  HOUGH_FOR_CIRCLES_TI_CIRCLE_BRIGHT = 1,
  HOUGH_FOR_CIRCLES_TI_CIRCLE_BOTH    = 2
} HOUGH_FOR_CIRCLES_TI_CircleType;


/**
  @brief Downscaling to be performed in the output Hough space during analysis.

  HOUGH_FOR_CIRCLES_TI_NO_SCALING : No averaging in Hough space
  HOUGH_FOR_CIRCLES_TI_SCALE_2x2  : Averaging on a 2x2 grid.
  HOUGH_FOR_CIRCLES_TI_SCALE_4x4  : Averaging on a 4x4 grid.

*/
typedef enum
{
  HOUGH_FOR_CIRCLES_TI_NO_SCALING = 0,
  HOUGH_FOR_CIRCLES_TI_SCALE_2x2  = 1,
  HOUGH_FOR_CIRCLES_TI_SCALE_4x4  = 2
} HOUGH_FOR_CIRCLES_TI_HoughSpaceScaling;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_IMAGE:
  This buffer descriptor (inBufs->bufDesc[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_IMAGE])
  should point to a buffer descriptor containing the image in which circles need
  to be detected.

  HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_EDGEMAP:
  This buffer descriptor (inBufs->bufDesc[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_EDGEMAP])
  should point to a buffer descriptor containing a 8 bit grayscale image
  indicating positions of the edge points in the image.
*/
typedef enum
{
  HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_IMAGE   = 0,
  HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_EDGEMAP,
  HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_TOTAL
} HOUGH_FOR_CIRCLES_TI_InBufOrder;


/**
  @brief Following are the control commands supported by this applet

  HOUGH_FOR_CIRCLES_TI_CONTROLCMD_GET_EFFECTIVE_IMAGEDIMENSION:
    This control command ID can be used to query the effective image dimension
    needed by this applet. User is expected to allocate atleast this much buffer for edgeMap and Image buffer
    and should fill the padded region with zeros for edgeMap. This is an optional control command
    to determine the exact amount of padding required. If user doesnt want to find the exact padding
    then it is expected that user pad the edgeMap with zeros for the 48 border on  both sides ( right and bottom of edge image).
*/
typedef enum
{
  HOUGH_FOR_CIRCLES_TI_CONTROLCMD_GET_EFFECTIVE_IMAGEDIMENSION,
  HOUGH_FOR_CIRCLES_TI_CONTROLCMD_MAX
} HOUGH_FOR_CIRCLES_TI_ControlCmdIdType;

/**

  @struct HOUGH_FOR_CIRCLES_TI_CircleInfo
  @brief  This is the structure to describe detected circle of
              a given radius

  @param  centerY
          Y coordinate of detected center.

  @param  centerX
          X coordinate of detected center
*/
typedef struct
{
  uint16_t centerY;
  uint16_t centerX;
} HOUGH_FOR_CIRCLES_TI_CircleInfo;


/**

  @struct HOUGH_FOR_CIRCLES_TI_CircleProperties
  @brief  This structure contains all the parameters needed for specifying
          properties of circles to be detected by this applet

  @param  radius
          Radius of the circle to be detected. The maximum value supported
          is HOUGH_FOR_CIRCLES_TI_MAX_NUM_RADIUS.

  @param  houghScoreThreshold
          The threshold to be used in hough space to declare a circle for
          the given radius.

*/
typedef struct
{
  uint8_t radius;
  uint8_t houghScoreThreshold;
} HOUGH_FOR_CIRCLES_TI_CircleProperties;


/**

  @struct HOUGH_FOR_CIRCLES_TI_CreateParams
  @brief  This structure contains all the parameters needed at create time
          for this applet

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  maxPercentageEdges
          Maximum percentage of edge points that is expected per frame. In case
          user does not have this information apriori, set the value to zero.
          If the value is set to zero the applet will ask for worst case
          memory for it's internal memtab.

  @param  circleType
          This parameter specifies whether the applet needs to detect 'bright'
          or 'dark' circular object or both. Here 'bright' means bright circular
          object on a dark background. Refer to HOUGH_FOR_CIRCLES_TI_CircleType.

  @param  houghSpaceScaling
          This parameter specifies the amount of down-scaling to be
          performed in output hough space for ananlysis for this particular
          radius. Refer to IHOUGH_FOR_CIRCLE_HoughSpaceScaling.

@param  maxNumRadius
        Maximum number of radius user wants to work with.

*/
typedef struct
{
  IVISION_Params visionParams;
  uint8_t maxPercentageEdges;
  uint8_t  circleType;
  uint8_t  houghSpaceScaling;
  uint8_t  maxNumRadius;
} HOUGH_FOR_CIRCLES_TI_CreateParams;


/**

  @struct HOUGH_FOR_CIRCLES_TI_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to the applet at frame level

  @param  iVisionInArgs
          Common InArgs for all ivison based modules

  @param  numRadius
          Number of different radii for which hough transform based detection
          need to be performed for the current frame.

  @param  circleProps
          This parameter describes the properties to be used for circle detection
          for each radius

*/
typedef struct
{
  IVISION_InArgs  iVisionInArgs;
  uint8_t  numRadius;
  HOUGH_FOR_CIRCLES_TI_CircleProperties circleProps[HOUGH_FOR_CIRCLES_TI_MAX_NUM_RADIUS];

} HOUGH_FOR_CIRCLES_TI_InArgs;


/**

  @struct HOUGH_FOR_CIRCLES_TI_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by applet at frame level.

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  numCircles
          List of number of circles detected for each radius for the
          current frame

  @param  circleInfo
           Coordinates of the centers detected for all radius

  @param  circleInfo
         Hough Score of the centers detected for all radius

  @remark It is important to note that when circle type is HOUGH_FOR_CIRCLES_TI_CIRCLE_BOTH
         then the actual number following arrays will contain double the number of radius requested with
         initial enteries being for the BRIGHT circle followed by DARK circles.
         For example if circleType is HOUGH_FOR_CIRCLES_TI_CIRCLE_BOTH and numRadius =3,
         numCircles array will contain 6 valid enteries with first 3 for BRIGHT circles and next 3
         for DARK circles. circleInfo and houghScore array also follow the same behavior
*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  uint16_t numCircles[HOUGH_FOR_CIRCLES_TI_MAX_NUM_RADIUS];
  HOUGH_FOR_CIRCLES_TI_CircleInfo circleInfo[HOUGH_FOR_CIRCLES_TI_MAX_NUM_RADIUS][HOUGH_FOR_CIRCLES_TI_MAX_NUM_CIRCLE_PER_RADIUS];
  uint8_t                         houghScore[HOUGH_FOR_CIRCLES_TI_MAX_NUM_RADIUS][HOUGH_FOR_CIRCLES_TI_MAX_NUM_CIRCLE_PER_RADIUS];
} HOUGH_FOR_CIRCLES_TI_OutArgs;

/**

  @struct HOUGH_FOR_CIRCLES_TI_ControlInArgs
  @brief  This structure contains all the parameters needed
             for control call of this applet. Control call is used to
             get the input buffer requirement by this applet. It is
             important that input buffer is allocated with the correct
             size returned by control call.

  @param  imageWidth
          Input image buffer pointer

  @param  imageHeight
          Input arguments for the current frame

  @param  maxRadius
          Maximum Radius for all the set of radius being searched

  @remark It is important that  the extra padded region for edgemap
                should be filled with zero by the user to avoid voting for those
                points by this applet

*/
typedef struct
{
  uint16_t imageWidth;
  uint16_t imageHeight;
  uint8_t  maxRadius;
}HOUGH_FOR_CIRCLES_TI_ControlInArgs;

/**

  @struct HOUGH_FOR_CIRCLES_TI_ControlOutArgs
  @brief  This structure contains all the parameters that are
             returned by  control call of this applet

  @param  effImageWidth
          Effective image width needed by this applet.

  @param  effImageHeight
         Effective image height needed by this applet.

  @remark It is important that  the extra padded region for edgemap
              should be filled with zero by the user to avoid voting for those
              points by this applet

*/
typedef struct
{
  uint16_t effImageWidth;
  uint16_t effImageHeight;
}HOUGH_FOR_CIRCLES_TI_ControlOutArgs;

/*@}*/
/* ti_ivision_HOUGH_FOR_CIRCLES */

#endif /*IHOUGH_FOR_CIRCLES_TI_H_ */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/

