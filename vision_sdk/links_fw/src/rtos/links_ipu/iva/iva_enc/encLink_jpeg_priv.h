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
 * \file encLink_jpeg_priv.h MJPEG codec private API/Data structures
 *
 * \brief  MJPEG codec private API/Data structures are defined here
 *         - MJPEG codec handle object
 *         - All the codec static/dynamic data structures
 *
 * \version 0.0 (April 2014) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef _ENC_LINK_JPEG_PRIV_H_
#define _ENC_LINK_JPEG_PRIV_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/encLink.h>
#include <ti/sdo/codecs/jpegvenc/ijpegenc.h>

#include "encLink_algIf.h"

/**
 *******************************************************************************
 *  Analytic info output buffer size, this buffer is used to place MV & SAD of
 *  encoded frame, should be big enough to hold the size of  typical HD sequence
 *******************************************************************************
 */
#define ANALYTICINFO_OUTPUT_BUFF_SIZE      (0x00028000)
typedef struct IJPEGVENC_Obj *JPEGVENC_Handle;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the MJPEG Alg/Codec object
 *          This contains the MJPEG codec handle and other
 *          codec private parameters
 *
 *******************************************************************************
 */
typedef struct EncLink_JPEGObj {
    JPEGVENC_Handle algHandle;
    Int8 versionInfo[ENC_LINK_ALG_VERSION_STRING_MAX_LEN];
    Int linkID;
    Int channelID;
    Int scratchID;
    UInt32 ivaChID;
    IJPEGVENC_DynamicParams dynamicParams;
    IJPEGVENC_Status status;
    IJPEGVENC_Params staticParams;
    IJPEGVENC_InArgs inArgs;
    IJPEGVENC_OutArgs outArgs;
    IVIDEO2_BufDesc inBufs;
    XDM2_BufDesc outBufs;
    System_IVideoFormat format;
    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
} EncLink_JPEGObj;

/*******************************************************************************
 *  Encode Link - MJPEG Private Functions
 *******************************************************************************
 */
Int EncLinkJPEG_algCreate(EncLink_JPEGObj * hObj,
                          EncLink_AlgCreateParams * algCreateParams,
                          EncLink_AlgDynamicParams * algDynamicParams,
                          Int linkID, Int channelID, Int scratchGroupID);
Void EncLinkJPEG_algDelete(EncLink_JPEGObj * hObj);

#endif

/* Nothing beyond this point */
