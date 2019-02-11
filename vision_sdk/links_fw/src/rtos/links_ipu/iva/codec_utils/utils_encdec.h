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
 * \file utils_encdec.h
 *
 * \brief  IVA Encode/Decode utils functions are defined
 *
 * \version 0.0 (Jan 2014) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef _UTILS_ENCDEC_H_
#define _UTILS_ENCDEC_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ivideo.h>
//#include <include/link_api/encLink.h>
#include <include/link_api/decLink.h>

/* =============================================================================
 * All success and failure codes for the module
 * ========================================================================== */

/** @brief Operation successful. */
#define UTILS_ENCDEC_S_SUCCESS               (0)

/** @brief General Failure */
#define UTILS_ENCDEC_E_FAIL                  (-1)

/** @brief Unknow coding type */
#define UTILS_ENCDEC_E_UNKNOWNCODINGTFORMAT  (-2)

/** @brief Internal error: unknown resolution class */
#define UTILS_ENCDEC_E_INT_UNKNOWNRESOLUTIONCLASS    (-64)

#define UTILS_ENCDEC_ACTIVITY_LOG_LENGTH     (64)

#define UTILS_ENCDEC_MAX_IVACH               (16)

#define IVACODEC_VDMA_BUFFER_ALIGNMENT       (32)

#    if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
#        define  NUM_HDVICP_RESOURCES        (1)
#    else
#    if defined(TDA2EX_BUILD)
#        define  NUM_HDVICP_RESOURCES        (1)
#    else 
#        error "Unknow Device.."
#    endif
#    endif

typedef enum Utils_EncDec_LinkState {
    UTILS_ENCDEC_STATE_START = 0,
    UTILS_ENCDEC_STATE_STOP
} Utils_EncDec_LinkState;

/** @enum EncDec_ResolutionClass
 *  @brief Enumeration of different resolution class.
 */
typedef enum EncDec_ResolutionClass {
    UTILS_ENCDEC_RESOLUTION_CLASS_FIRST = 0,
    UTILS_ENCDEC_RESOLUTION_CLASS_16MP = UTILS_ENCDEC_RESOLUTION_CLASS_FIRST,
    UTILS_ENCDEC_RESOLUTION_CLASS_9MP,
    UTILS_ENCDEC_RESOLUTION_CLASS_5MP,
    UTILS_ENCDEC_RESOLUTION_CLASS_4MP,
    UTILS_ENCDEC_RESOLUTION_CLASS_1080P,
    UTILS_ENCDEC_RESOLUTION_CLASS_720P,
    UTILS_ENCDEC_RESOLUTION_CLASS_D1,
    UTILS_ENCDEC_RESOLUTION_CLASS_CIF,
    UTILS_ENCDEC_RESOLUTION_CLASS_LAST = UTILS_ENCDEC_RESOLUTION_CLASS_CIF,
    UTILS_ENCDEC_RESOLUTION_CLASS_COUNT =
        (UTILS_ENCDEC_RESOLUTION_CLASS_LAST + 1)
} EncDec_ResolutionClass;


typedef enum EncDec_AlgorithmType {
    UTILS_ALGTYPE_NONE = 0,
    UTILS_ALGTYPE_H264_ENC,
    UTILS_ALGTYPE_H264_DEC,
    UTILS_ALGTYPE_MJPEG_ENC,
    UTILS_ALGTYPE_MJPEG_DEC,
    UTILS_ALGTYPE_MPEG4_DEC,
    UTILS_ALGTYPE_LAST = UTILS_ALGTYPE_MPEG4_DEC,
    UTILS_ALGTYPE_COUNT =
        (UTILS_ALGTYPE_LAST + 1)
} EncDec_AlgorithmType;


typedef struct EncDec_AlgorithmActivityLog {
    EncDec_AlgorithmType algType[UTILS_ENCDEC_ACTIVITY_LOG_LENGTH];
    UInt32 writeIdx;
} EncDec_AlgorithmActivityLog;

#define UTILS_ENCDEC_RESOLUTION_CLASS_16MP_WIDTH                        (4*1024)
#define UTILS_ENCDEC_RESOLUTION_CLASS_16MP_HEIGHT                       (4*1024)

#define UTILS_ENCDEC_RESOLUTION_CLASS_9MP_WIDTH                         (3*1024)
#define UTILS_ENCDEC_RESOLUTION_CLASS_9MP_HEIGHT                        (3*1024)

#define UTILS_ENCDEC_RESOLUTION_CLASS_5MP_WIDTH                           (2592)
#define UTILS_ENCDEC_RESOLUTION_CLASS_5MP_HEIGHT                        (2*1024)

#define UTILS_ENCDEC_RESOLUTION_CLASS_4MP_WIDTH                         (2*1024)
#define UTILS_ENCDEC_RESOLUTION_CLASS_4MP_HEIGHT                        (2*1024)

#define UTILS_ENCDEC_RESOLUTION_CLASS_1080P_WIDTH                         (1920)
#define UTILS_ENCDEC_RESOLUTION_CLASS_1080P_HEIGHT                        (1088)

#define UTILS_ENCDEC_RESOLUTION_CLASS_720P_WIDTH                          (1280)
#define UTILS_ENCDEC_RESOLUTION_CLASS_720P_HEIGHT                          (720)

#define UTILS_ENCDEC_RESOLUTION_CLASS_D1_WIDTH                             (720)
#define UTILS_ENCDEC_RESOLUTION_CLASS_D1_HEIGHT                            (576)

#define UTILS_ENCDEC_RESOLUTION_CLASS_CIF_WIDTH                            (368)
#define UTILS_ENCDEC_RESOLUTION_CLASS_CIF_HEIGHT                           (288)

/**
    \brief Check if coding type is H264

    This checks the IVIDEO format to see if it is H264 codec
    \param format        [IN] System_IVideoFormat enum

    \return TRUE if codec type is H264
*/
static inline Bool Utils_encdecIsH264(System_IVideoFormat format)
{
    Bool isH264;

    switch (format)
    {
        case SYSTEM_IVIDEO_H264BP:
        case SYSTEM_IVIDEO_H264MP:
        case SYSTEM_IVIDEO_H264HP:
            isH264 = TRUE;
            break;
        default:
            isH264 = FALSE;
            break;
    }
    return isH264;
}
/**
    \brief Check if coding type is MPEG4

    This checks the IVIDEO format to see if it is MPEG4 codec
    \param format        [IN] System_IVideoFormat enum

    \return TRUE if codec type is MPEG4
*/
static inline Bool Utils_encdecIsMPEG4(System_IVideoFormat format)
{
    Bool isMPEG4;

    switch (format)
    {
        case SYSTEM_IVIDEO_MPEG4SP:
        case SYSTEM_IVIDEO_MPEG4ASP:
            isMPEG4 = TRUE;
            break;
        default:
            isMPEG4 = FALSE;
            break;
    }
    return isMPEG4;
}

/**
    \brief Check if coding type is MJPEG

    This checks the IVIDEO format to see if it is MJPEG codec
    \param format        [IN] System_IVideoFormat enum

    \return TRUE if codec type is MJPEG
*/
static inline Bool Utils_encdecIsJPEG(System_IVideoFormat format)
{
    Bool isjpeg;

    switch (format)
    {
        case SYSTEM_IVIDEO_MJPEG:
            isjpeg = TRUE;
            break;
        default:
            isjpeg = FALSE;
            break;
    }
    return isjpeg;
}


static inline UInt32 Utils_encdecMapSYS2XDMContentType(UInt32 scanFormat)
{
    return ((scanFormat == SYSTEM_SF_INTERLACED) ? SYSTEM_IVIDEO_INTERLACED :
            SYSTEM_IVIDEO_PROGRESSIVE);
}

static inline UInt32 Utils_encdecMapSYS2XDMChromaFormat(UInt32 chromaFormat)
{
    UInt32 xdmChromaFormat;

    UTILS_assert((chromaFormat == SYSTEM_DF_YUV420SP_UV) ||
                 (chromaFormat == SYSTEM_DF_YUV420SP_VU) ||
                 (chromaFormat == SYSTEM_DF_YUV422I_YUYV) ||
                 (chromaFormat == SYSTEM_DF_YUV422I_UYVY));
    if ((chromaFormat == SYSTEM_DF_YUV420SP_UV)
        ||
        (chromaFormat == SYSTEM_DF_YUV420SP_VU))
    {
        xdmChromaFormat = XDM_YUV_420SP;
    }
    else
    {
        xdmChromaFormat = XDM_YUV_422IBE;
    }
    return xdmChromaFormat;
}

static inline UInt32 Utils_encdecMapXDMContentType2SYSFID(UInt32 contentType)
{
    System_Fid fid = SYSTEM_FID_MAX;

    switch (contentType)
    {
        case SYSTEM_IVIDEO_INTERLACED_TOPFIELD:
            fid = SYSTEM_FID_TOP;
            break;
        case SYSTEM_IVIDEO_INTERLACED_BOTTOMFIELD:
            fid = SYSTEM_FID_BOTTOM;
            break;
        default:
            // fid = SYSTEM_FID_FRAME;
            /* For progressive frame driver expects fid to be set to
             * SYSTEM_FID_TOP */
            fid = SYSTEM_FID_TOP;
            break;
    }
    return fid;
}

static inline System_IVideoContentType Utils_encdecMapSYSFID2XDMContentType(System_Fid fid)
{
    System_IVideoContentType contentType = SYSTEM_IVIDEO_PROGRESSIVE;

    switch (fid)
    {
        case SYSTEM_FID_TOP:
            contentType = SYSTEM_IVIDEO_INTERLACED_TOPFIELD;
            break;
        case SYSTEM_FID_BOTTOM:
            contentType = SYSTEM_IVIDEO_INTERLACED_BOTTOMFIELD;
            break;
        case SYSTEM_FID_FRAME:
            contentType = SYSTEM_IVIDEO_PROGRESSIVE_FRAME;
            break;
        default:
            contentType = SYSTEM_IVIDEO_PROGRESSIVE_FRAME;
            break;
    }
    return contentType;
}

static inline Bool Utils_encdecIsGopStart(UInt32 frameType, UInt32 contentType)
{
    Bool isGopStart = FALSE;

    switch (frameType)
    {
        case SYSTEM_IVIDEO_I_FRAME:
        case SYSTEM_IVIDEO_IDR_FRAME:
        case SYSTEM_IVIDEO_II_FRAME:
        case SYSTEM_IVIDEO_MBAFF_I_FRAME:
        case SYSTEM_IVIDEO_MBAFF_IDR_FRAME:
            isGopStart = TRUE;
            break;
        case SYSTEM_IVIDEO_IP_FRAME:
        case SYSTEM_IVIDEO_IB_FRAME:
            if (contentType == SYSTEM_IVIDEO_INTERLACED_TOPFIELD)
            {
                isGopStart = TRUE;
            }
            break;
        case SYSTEM_IVIDEO_PI_FRAME:
        case SYSTEM_IVIDEO_BI_FRAME:
            if (contentType == SYSTEM_IVIDEO_INTERLACED_BOTTOMFIELD)
            {
                isGopStart = TRUE;
            }
            break;
        default:
            isGopStart = FALSE;
            break;
    }
    return isGopStart;
}

/** @def   UTILS_ENCDEC_BITBUF_SCALING_FACTOR
 *  @brief Define that controls the size of bitbuf in realtion to its resoltuion
 */
#define UTILS_ENCDEC_BITBUF_SCALING_FACTOR                         (2)

/** @enum UTILS_ENCDEC_GET_BITBUF_SIZE
 *  @brief Macro that returns max size of encoded bitbuffer for a given resolution
 */

#define UTILS_ENCDEC_GET_BITBUF_SIZE(width,height,bitrate,framerate)           \
                    (((width) * (height))*3/2)

#define UTILS_ENCDEC_PADX                                          (32)
#define UTILS_ENCDEC_PADY                                          (24)

/** @enum UTILS_ENCDEC_GET_PADDED_WIDTH
 *  @brief Macro that padded width for given width */
#define UTILS_ENCDEC_GET_PADDED_WIDTH(width)                                   \
                     (((width) + (2 * UTILS_ENCDEC_PADX) + 127) & 0xFFFFFF80)

/** @enum UTILS_ENCDEC_GET_PADDED_HEIGHT
 *  @brief Macro that padded height for given height */
#define UTILS_ENCDEC_GET_PADDED_HEIGHT(height)                                 \
                                      ((height) + (4 * UTILS_ENCDEC_PADY))

Int Utils_encdecGetCodecLevel(UInt32 codingFormat,
                              UInt32 maxWidth,
                              UInt32 maxHeight,
                              UInt32 maxFrameRate,
                              UInt32 maxBitRate, Int32 * pLevel,
                              Bool isEnc);

Int Utils_encdecInit(void);

Int Utils_encdecDeInit(void);

#endif

/* Nothing beyond this point */


