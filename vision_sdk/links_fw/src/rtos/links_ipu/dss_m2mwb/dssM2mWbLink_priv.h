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
 * \ingroup DSSM2MWB_LINK_API
 * \defgroup DSSM2MWB_LINK_IMPL DSSM2MWB Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file dssM2mWbLink_priv.h DSSM2MWB Link private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - DSSM2MWB link instance/handle object
 *         - All the local data structures
 *         - DSSM2MWB BSP driver interfaces
 *
 * \version 0.0 (Sept 2013) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef DSSM2MWB_LINK_PRIV_H_
#define DSSM2MWB_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/dssM2mWbLink.h>
#include <ti/drv/vps/include/dss/vps_m2mDss.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Max Number of DSSM2MWB link instances supported
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DSSM2MWB_LINK_OBJ_MAX                     (1U)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief DSSM2MWB link instance object
 *
 *          This structure contains
 *          - All the local data structures
 *          - VPS/BSP Data structures required for DSSM2MWB BSP driver interfaces
 *          - All fields to support the Link stats and status information
 *
 *******************************************************************************
*/
typedef struct {
    UInt32 linkId;
    /**< placeholder to store the link task Id */
    char name[32];
    /**< Link name */
    Utils_TskHndl tsk;
    /**< placeholder to store the link task handler */
    DssM2mWbLink_CreateParams createArgs;
    /**< DSSM2MWB link create time parameters */
    System_LinkInfo inTskInfo;
    /**< Specifies a place holder that describe the LINK information */
    System_LinkQueInfo inQueInfo;
    /**< Input Q channel specific info, read from the outQ of previous LINK */
    System_LinkInfo info;
    /**< DSSM2MWB link output queue info, the next link query & use this info */
    Utils_BufHndl bufOutQue;
    /**< DSSM2MWB link output buffer queue */
    BspOsal_SemHandle complete;
    /**< Process complete semaphore */
    UInt32 outPitch[SYSTEM_MAX_PLANES];
    /**< Output frame pitch */
    UInt32 outBufSize;
    /**< Output buffer size */
    System_Buffer sysBuf[DSSM2MWB_LINK_NUM_BUFS_PER_CH_DEFAULT];
    /**< OutputSystem buffer */
    System_VideoFrameBuffer vidFrame[DSSM2MWB_LINK_NUM_BUFS_PER_CH_DEFAULT];
    /**< Output Video Frame buffer */
    FVID2_Handle drvHndl;
    /**< DSSM2MWB driver instance - FVID2 driver handle */
    Fvid2_CbParams drvCbPrm;
    /**< DSSM2MWB driver call back parameters */
    Vps_M2mDssCreateParams drvCreatePrm;
    /**< DSSM2MWB driver create parameters */
    Vps_M2mDssParams dssPrms;
    /**< DSS parameters */
    Vps_M2mDssCreateStatus drvCreateStatus;
    /**< DSS status parameters */
    Vps_DssDispcWbInNode drvWbInNode;
    /**< Driver WB input node */
    Vps_DssDispcPipes drvInPipelines[DSSM2MWB_LINK_MAX_IN_CH];
    /**< Driver Input pipelines */
    Fvid2_Frame inFrame[DSSM2MWB_LINK_MAX_IN_CH];
    /**< Input Fvid2 frames */
    Fvid2_Frame outFrame;
    /**< Input Fvid2 frames */
    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Used to log the memory usage of the DSSM2MWB link */
    System_LinkStatistics *linkStatsInfo;
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
} DssM2mWbLink_Obj;

/*******************************************************************************
 *  DSSM2MWB Link Private Functions
 *******************************************************************************
 */
Int32 DssM2mWbLink_getLinkInfo(Void *pTsk, System_LinkInfo *info);
Int32 DssM2mWbLink_getFullBuffers(
                        Void *ptr,
                        UInt16 queId,
                        System_BufferList *pBufList);
Int32 DssM2mWbLink_putEmptyBuffers(
                        Void *ptr,
                        UInt16 queId,
                        System_BufferList *pBufList);
Int32 DssM2mWbLink_drvCreate(
                DssM2mWbLink_Obj *pObj,
                const DssM2mWbLink_CreateParams *pPrm);
Int32 DssM2mWbLink_drvDelete(DssM2mWbLink_Obj *pObj);
Int32 DssM2mWbLink_drvProcessData(DssM2mWbLink_Obj *pObj);
Int32 DssM2mWbLink_printStatistics(const DssM2mWbLink_Obj *pObj, Bool resetAfterPrint);
Int32 DssM2mWbLink_printBufferStatus(DssM2mWbLink_Obj *pObj);
Int32 DssM2mWbLink_drvSetChannelInfo(DssM2mWbLink_Obj *pObj,
                                const DssM2mWbLink_ChannelInfo *channelInfo);
Int32 dssM2mWbDrvCb(FVID2_Handle handle, Ptr appData, Ptr reserved);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
