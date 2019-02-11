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
 *  @file       ieve_fast9_best_feature_to_front_ti.h
 *
 *  @brief      This file defines the interface for fast9 best feature to front Applet
 *  @version 0.0 (Dec 2013) : Base version.
 *  @version 0.1 (Jan 2014) : Updated version - Added enum for Score
 * @version  0.2 (April 2014) : Updated version - Added enum for suppression and create param for bestN max features
 */

/** @ingroup    ti_ivision_FAST9_BEST_FEATURE_TO_FRONT */
/*@{*/
#ifndef IFAST9_BEST_FEATURE_TO_FRONT_TI_H
#define IFAST9_BEST_FEATURE_TO_FRONT_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>


/**
* @brief Using iVISION buf planes to get multiple pyramid so max value
         allowed (4) is depedant on iVISION
*/
#define FAST9_BFFT_TI_MAXLEVELS   (IVISION_MAX_NUM_PLANES)


#define FAST9_BFFT_TI_MAXNUMFEATURES  (2048)

/**
 * @brief The unique const funtion table for the FAST9_BEST_FEATURE_TO_FRONT_TI.
 */
extern const IVISION_Fxns FAST9_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS;

/**
* @brief IRES interface of the INTEGRAL_IMAGE_TI_ algorithm
*/
extern const IRES_Fxns FAST9_BEST_FEATURE_TO_FRONT_TI_IRES;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by applet. This applet works on multi level so
  user can provide multiple buffers. Lets say this applet is used for
  3 levels of image pyramid. then user should provide
  inBufs->bufDesc[FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_IMAGEBUFFER]->numPlanes = 3
  and
  inBufs->bufDesc[FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[level] contains
  the details of each planes buffer pointer and dimensions

  FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST:
  This buffer descriptor (inBufs->bufDesc[FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST])
  should point to a  buf descriptor containing XY planes for different levels. This applet works
  on multi level so user can provide multiple buffers. Lets say this applet is used for
  3 levels of image pyramid. then user should provide
  inBufs->bufDesc[FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST]->numPlanes = 3
  and  inBufs->bufDesc[FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST]->bufPlanes[level]
  contains the pointers to that particuar level's XY list

  It is user responsbility to have the X and Y list to have valid data which points in
  image region excluding 3 pixels boarder on each side. The applet doesn't perfrom any check
  for this condition and the behavior is undefined if it is not satisfied.
  Since it is a 1D buffer, The size of list has to be indicated by
  inBufs->bufDesc[FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST]->bufPlanes[level].width* height
  for a 100 points - it should be 4*100 or 400*1

*/

typedef enum
{
  FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST,
  FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_TOTAL
} IFAST9_BFTF_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_OUT_XY_LIST:
  This buffer descriptor (outBufs->bufDesc[FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_OUT_XY_LIST]) should
  point to a plane capable of holding XY list of bestNFeaturesOut. so the size of this buffer is
  bestNFeaturesOut*(4) bytes

*/

typedef enum
{
  FAST9_BFTF_TI_BUFDESC_OUT_XY_LIST = 0,
  FAST9_BFTF_TI_BUFDESC_OUT_TOTAL
} IFAST9_BFTF_OutBufOrder ;

/** 
@brief 
  There are 2 methods to compute Fast9 score.
  (1) Threshold based method: This is similar to Opencv method
  (2) SAD based method
*/


typedef enum
{
   FAST9_BFTF_TI_THRESH_METHOD = 0,
   FAST9_BFTF_TI_SAD_METHOD
} IFAST9_BFTF_SCORE_METHOD ; 

/** 
@brief 
  There are 2 suppression methods.
  (1) 4-way suppression: Suppression along only top, bottom, left and right
  (2) 8-way suppression: Suppression along diagonal direction as well
*/


typedef enum
{
  FAST9_BFTF_TI_SUPPRESSION_4WAY = 0,
  FAST9_BFTF_TI_SUPPRESSION_8WAY
} IFAST9_BFTF_SUPPRESSION_METHOD ;

/**

  @struct FAST9_BEST_FEATURE_TO_FRONT_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          Fast9 best feature to front applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  maxFeatures
          Maximum number of features to be processed

   
  @param  maxbestNFeatures
            Maximum bestN features to be processed

  @param xyInIntMem
          If set to 1, then the XY list is in DMEM. If 0, then XY list in DDR

  @param  fast9Threshold
          The threshold used for Fast9 detect and fast9 score computation

  @param scoreMethod
          The method used to compute fast9 score

*/

typedef struct
{
  IVISION_Params visionParams;
  uint16_t  maxFeatures;
  uint16_t  maxbestNFeatures;
  uint8_t   xyInIntMem;
  uint8_t   fast9Threshold;
  uint8_t scoreMethod;
} FAST9_BEST_FEATURE_TO_FRONT_TI_CreateParams;


/**

  @struct FAST9_BEST_FEATURE_TO_FRONT_TI_InArgs
  @brief  This structure contains all the parameters which are given
             as an input to Fast9 Best feature to front applet

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  numFeaturesIn[FAST9_BTFT_TI_MAXLEVELS]
            Number of features to be processed at each level

  @param  bestNFeatures[FAST9_BTFT_TI_MAXLEVELS]
           Best N features to be output based on the Fast9 score
           after suppression at each level

*/

typedef struct
{
  IVISION_InArgs iVisionInArgs;
  uint8_t   suppressionMethod;
  uint16_t  numFeaturesIn[FAST9_BFFT_TI_MAXLEVELS];
  uint16_t  bestNFeatures[FAST9_BFFT_TI_MAXLEVELS];
} FAST9_BEST_FEATURE_TO_FRONT_TI_InArgs;


/**

  @struct FAST9_BEST_FEATURE_TO_FRONT_TI_OutArgs
  @brief  This structure contains all the parameters which are given
             as an input to Fast9 Best feature to front applet

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  bestNFeaturesOut[FAST9_BTFT_TI_MAXLEVELS]
            Number of features to features output at each level
            This can be lesser than number of features requested
            by the user (bestNFeatures)

*/


typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  uint16_t  bestNFeaturesOut[FAST9_BFFT_TI_MAXLEVELS];
} FAST9_BEST_FEATURE_TO_FRONT_TI_OutArgs;


/*@}*/
/* ti_ivision_FAST9_BEST_FEATURE_TO_FRONT */

#endif /*IFAST9_BEST_FEATURE_TO_FRONT_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


