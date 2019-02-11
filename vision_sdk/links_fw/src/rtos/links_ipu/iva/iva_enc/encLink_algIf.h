/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *
 * \file encLink_algIf.h Encode Link codec private interface structures
 *
 * \brief  Defines Encode Link codec private interface structures
 *
 * \version 0.0 (April 2014) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef _ENC_LINK_ALG_IF_H_
#define _ENC_LINK_ALG_IF_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/encLink.h>
#include <ti/sdo/codecs/jpegvenc/ijpegenc.h>
#include "encLink_priv.h"

#define ENC_LINK_ALG_VERSION_STRING_MAX_LEN                               (255)

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Encode link Alg/Codec private create
 *          time parameters
 *
 *******************************************************************************
 */
typedef struct EncLink_AlgCreateParams {
    System_IVideoFormat format;
    IVIDEO_VideoLayout dataLayout;
    Bool singleBuf;
    Int32 maxWidth;
    Int32 maxHeight;
    Int32 maxInterFrameInterval;
    Int32 inputContentType;
    Int32 inputChromaFormat;
    Int32 profile;
    Int32 level;
    Int32 enableAnalyticinfo;
    Int32 enableSVCExtensionFlag;
    Int32 enableWaterMarking;
    Int32 mvDataSize;
    Int32 maxBitRate;
    Int32 encodingPreset;
    Int32 rateControlPreset;
    Bool enableHighSpeed;
    Int32 numTemporalLayer;
    Int32 IDRFrameInterval;

} EncLink_AlgCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Encode link Alg/Codec ROI parameters
 *
 *******************************************************************************
 */
typedef struct EncLink_AlgROIDynamicParams
{
    Int32 roiNumOfRegion;
    /**< Number of ROI's */
    Int32 roiStartX[ENC_LINK_CURRENT_MAX_ROI];
    /**< starting location X coordinate of this region */
    Int32 roiStartY[ENC_LINK_CURRENT_MAX_ROI];
    /**< starting location Y coordinate of this region */
    Int32 roiWidth[ENC_LINK_CURRENT_MAX_ROI];
    /**< Width of this ROI */
    Int32 roiHeight[ENC_LINK_CURRENT_MAX_ROI];
    /**< Height of this ROI */
    Int32 roiType[ENC_LINK_CURRENT_MAX_ROI];
    /**< ROI type */
    Int32 roiPriority[ENC_LINK_CURRENT_MAX_ROI];
} EncLink_AlgROIDynamicParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Encode link Alg/Codec private run-time
 *          or dynamic parameters
 *
 *******************************************************************************
 */
typedef struct EncLink_AlgDynamicParams {
    Int32 startX;
    Int32 startY;
    Int32 inputWidth;
    Int32 inputHeight;
    Int32 inputPitch;
    Int32 targetBitRate;
    Int32 targetFrameRate;
    Int32 intraFrameInterval;
    Int32 interFrameInterval;
    Int32 rcAlg;
    Int32 qpMinI;
    Int32 qpMaxI;
    Int32 qpInitI;
    Int32 qpMinP;
    Int32 qpMaxP;
    Int32 qpInitP;
    Int32 forceFrame;
    Int32 vbrDuration;
    Int32 vbrSensitivity;
    Bool  forceFrameStatus;
    Int32 mvAccuracy;
    Int32 refFrameRate;
    Int32 maxPicSizeRatioI;

    EncLink_AlgROIDynamicParams roiParams;
} EncLink_AlgDynamicParams;

#endif

/* Nothing beyond this point */

