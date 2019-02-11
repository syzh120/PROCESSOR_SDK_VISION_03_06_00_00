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
 * \ingroup ISSCAPTURE_LINK_API
 * \defgroup ISSCAPTURE_LINK_IMPL Iss Capture Link Implementation
 *
 * @{
 */

 /**
 *******************************************************************************
 *
 * \file issCaptureLink_priv.h Iss Capture link private header file.
 *
 * \brief  This file is a private header file for isscapture link implementation
 *
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of iss capture link.
 *
 *         Links and chains operate on channel number to identify the buffers
 *         from different sources and streams.
 *
 *         Output of Iss Capture link is single queue and one or more channels.
 *         If multiple input sources (CSI2 / LVDS / parallel port) need to be
 *         used in the system simultaneously, then multiple instances of
 *         Iss iss capture link needs to be used. This is not yet supported.
 *
 * \version 0.0 (Apr 2014) : [PS] First version
 * \version 0.1 (Apr 2015) : [Suj] Updated to support multiple channel
 *                                  reception on CSI2 interface.
 *
 *******************************************************************************
 */

#ifndef ISSCAPTURE_LINK_PRIV_H_
#define ISSCAPTURE_LINK_PRIV_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/system_linkId.h>
#include <include/link_api/issCaptureLink.h>

#include <ti/drv/vps/include/iss/vps_cfgcal.h>
#include <ti/drv/vps/include/iss/vps_captureIss.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Maximum number of output queues that iss capture link supports.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ISSCAPTURE_LINK_MAX_OUT_QUE         (1U)


/**
 *******************************************************************************
 *
 * \brief Maximum number of Iss capture link objects
 *
 *******************************************************************************
 */
#define ISSCAPTURE_LINK_OBJ_MAX             (1U)

/**
 *******************************************************************************
 *
 * \brief Specifies the alignment of allocated buffer boundary
 *
 *******************************************************************************
 */
#define ISSCAPTURE_LINK_BUF_ALIGNMENT       (VPS_BUFFER_ALIGNMENT*2U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of frames getting allocated for entire capture Link.
 *
 *        This is to allocate frame container statically, which will point to
 *        actual frames. Frames will be allocated based on application requests
 *        but frame containers are always allocated at init time that is max
 *        of frames possible for all the channels.
 *
 *******************************************************************************
 */
#define ISSCAPTURE_LINK_MAX_FRAMES_PER_HANDLE (SYSTEM_LINK_MAX_FRAMES_PER_CH *\
                                                ISSCAPT_LINK_MAX_CH)


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 *  \brief  Structure containing information for each instance of
 *          Iss capture link.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 linkId;
    /**< Iss Capture Link ID */

    Utils_TskHndl tsk;
    /**< Handle to iss capture link task */

    UInt32                  drvInstId;
    /**< As defined in <bsp>\include\vps\vps_capture.h*/
    Vps_CaptCreateParams    drvCreatePrms;
    /**< FVID2 Create time parameters. */
    Vps_CaptIssOpenParams_t drvIssCaptureCreatePrms;
    /**< Additional args passed to driver during FVID2 create */
    Vps_CaptCreateStatus    drvCreateStatus;
    /**< Create status returned by driver during Fvid2_create(). */
    Fvid2_Handle            drvHandle;
    /**< FVID2 capture driver handle. */
    Fvid2_CbParams          drvCbPrms;
    /**< Callback params. */
    vpsissCalCfg_t          drvCalCfg;
    /**< CAL config */

    Fvid2_Frame fvid2Frames[ISSCAPTURE_LINK_MAX_FRAMES_PER_HANDLE];
    /**< FVID2 Frames that will be used for capture. */

    System_Buffer buffers[ISSCAPTURE_LINK_MAX_FRAMES_PER_HANDLE];
    /**< System buffer data structure to exchange buffers between links */

    System_VideoFrameBuffer videoFrames[ISSCAPTURE_LINK_MAX_FRAMES_PER_HANDLE];
    /**< Payload for System buffers */

    UInt32 outBufSize;
    /**< Size of output buffer */

    IssCaptureLink_CreateParams createArgs;
    /**< Create params for iss capture link */

    Utils_BufHndl bufQue;
    /**< Output buffer queue */

    System_LinkInfo info;
    /**< Capture link information */

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Memory used by iss capture link */

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */

    UInt32  statsStartTime;
    /**< Time at which capture is started */

    UInt8           *saveFrameBufAddr;
    /**< Frame buffer used for saving captured frame */
    volatile UInt32  saveFrame;
    /**< Flag to indicate saving of the frame from process callback */
    Utils_DmaChObj   dumpFramesDmaObj;
    /**< DMA object to use when dumping frames to memory */
    IssCaptureLink_SetErrorNotification errCfg;
    /**< Local copy of the errors enabled and associate callbacks */
    vpsissCalErrorCfg_t drvErrCfg;
    /**< Used to configure error to be monitered in the driver */
    UInt32 saveChId;
} IssCaptureLink_Obj;

extern IssCaptureLink_Obj gIssCaptureLink_obj[ISSCAPTURE_LINK_OBJ_MAX];

Int32 IssCaptureLink_getInfo(Void * ptr, System_LinkInfo * info);
Int32 IssCaptureLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList);
Int32 IssCaptureLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList);

Int32 IssCaptureLink_drvCreate(IssCaptureLink_Obj * pObj,
                               const IssCaptureLink_CreateParams * pPrm);

Int32 IssCaptureLink_drvStart(IssCaptureLink_Obj * pObj);
Int32 IssCaptureLink_drvProcessData(IssCaptureLink_Obj * pObj);
Int32 IssCaptureLink_drvStop(IssCaptureLink_Obj * pObj);
Int32 IssCaptureLink_drvDelete(IssCaptureLink_Obj * pObj);

Int32 IssCaptureLink_drvPutEmptyBuffers(IssCaptureLink_Obj * pObj,
                                        const System_BufferList * pBufList);

Int32 IssCaptureLink_drvPrintStatus(const IssCaptureLink_Obj * pObj);

Int32 IssCaptureLink_drvPrintBufferStatus(IssCaptureLink_Obj * pObj);

Void IssCaptureLink_enumAssertCheck(void);

Int32 IssCaptureLink_drvSaveFrame(IssCaptureLink_Obj *pObj, UInt32 *chId);

Int32 IssCaptureLink_drvGetSaveFrameStatus(const IssCaptureLink_Obj *pObj,
                    IssCaptureLink_GetSaveFrameStatus *pPrm);
Int32 IssCaptureLink_cfgErrorHandling(IssCaptureLink_Obj * pObj,
    const IssCaptureLink_SetErrorNotification *pErrCfg);

#endif

/* @} */
