/******************************************************************************
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
******************************************************************************/

/**
 *******************************************************************************
 *
 * \ingroup ALGORITHM_LINK_DMA_SW_MS_API
 * \defgroup ALGORITHM_LINK_DMA_SW_MS_IMPL Algorithm Link Plugin : DMA SW Mosaic
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file dmaSwMsLink_priv.h Algorithm Link Plugin : DMA SW Mosaic private
 *                            API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.0 (Sept 2013) : [KC] First version
 *
 *******************************************************************************
 */

#ifndef _DMA_SWMS_LINK_PRIV_H_
#define _DMA_SWMS_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/system_common.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_vpeSwMs.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/utils_common/include/utils_dma.h>
#include <ti/sysbios/hal/Cache.h>
#include <src/rtos/utils_common/include/utils_link_stats_if.h>
#include <ti/drv/vps/include/vpe/vps_m2m.h>
#include <ti/drv/vps/include/vpe/vps_m2mVpe.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Max number of video frames needed for DMA SW MS algorithm
 *
 *******************************************************************************
 */
#define VPE_SWMS_LINK_MAX_OUT_BUF (8)

/**
 *******************************************************************************
 *
 *   \brief Define the Max Number of output buffers per channel of VPE link
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define VPE_SWMS_MAX_OUT_FRAMES_PER_CH       (10U)

/**
 *******************************************************************************
 *
 *   \brief Define the Max Number of temp output buffers of VPE link
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_VPE_SW_MS_TEMP_BUFF_CNT       (10U)
/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 *   \brief Data Structure for the VPE link Input side object
 *
 *          This includes the Input side FVID2 free Queues
 *          and the FVID2 frames
 *
 *******************************************************************************
*/
typedef struct {
    Utils_QueHandle fvidFrameQueue;
    /**< Free FVID2 Frames queue for mapping system buffers from input queue */
    FVID2_Frame frames[VPE_SWMS_MAX_OUT_FRAMES_PER_CH];
    /**< FVID2 Frames to interface with the VPE driver */
    FVID2_Frame *fvidFrameQueueMem[VPE_SWMS_MAX_OUT_FRAMES_PER_CH];
    /**< FVID2 Frames Queue Mem */
} AlgorithmLink_VpeSwMsInObj;

/**
 *******************************************************************************
 *
 *   \brief VPE link Channel specific instance object
 *
 *          This structure contains
 *          - All the channel specific local data structures
 *          - VPS/BSP Data structures required for VPE BSP driver interfaces
 *          - All fields to support the CH vise stats and status information
 *
 *******************************************************************************
*/
typedef struct {
    Bool enableOut[ALGORITHM_LINK_VPE_SW_MS_OUT_QUE_ID_MAX];
    /**< Output Queue enable/disable flag */
    Utils_BufHndl inQue;
    /**< CH specific intermediate Queue */
    UInt32 nextFid;
    /**< Expected FID info for the next field */
    FVID2_Format outFormat[ALGORITHM_LINK_VPE_SW_MS_OUT_QUE_ID_MAX];
    /**< Structure to hold the output buffer format,
     *   such as width, height, pitch, data format, scan format etc */
    Vps_ScConfig scCfg[ALGORITHM_LINK_VPE_SW_MS_OUT_QUE_ID_MAX];
    /**< Structure to hold the scalar config parameters */
    Fvid2_CropConfig scCropCfg[ALGORITHM_LINK_VPE_SW_MS_OUT_QUE_ID_MAX];
    /**< Structure to hold the scalar crop config parameters */
    Vps_DeiRtConfig deiRtCfg;
    /**< Structure to hold the VPE DEI RT parameters */
} AlgorithmLink_VpeSwMsChObj;

/**
 *******************************************************************************
 *
 *   \brief Structure containing frame copy algorithm link specific parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef  struct
{
    AlgorithmLink_VpeSwMsCreateParams   createArgs;
    /**< Create time arguments */

    System_LinkQueInfo          prevLinkQueInfo;
    /**< channel info of input queue */

    System_LinkInfo info;
    /**< VPE link output queue info, the next link query & use this info */

    UInt32                      dataFormat;
    /**< Data format, YUV422 or YUV420 */

    UInt32                      outPitch[2];
    /**< Pitch of output buffer */

    System_Buffer buffers[VPE_SWMS_LINK_MAX_OUT_BUF];
    /**< System buffer data structure to exchange buffers between links */

    System_VideoFrameBuffer videoFrames[VPE_SWMS_LINK_MAX_OUT_BUF];
    /**< Payload for System buffers */

    UInt32 outBufSize;
    /**< Size of output buffer in bytes */

    Ptr *dmaFillLineAddr[UTILS_DMA_MAX_PLANES];
    /**< Address of fill data line */

    UInt32 dmaFillLineSize;
    /**< Size of fill data line in bytes */

    AlgorithmLink_VpeSwMsLayoutParams   curLayoutPrm;
    /**< Current layout parameters */

    Bool                         isLayoutSwitch;
    /**< Layout is switched, may need to fill output buffer */

    UInt32                       doFillBuf;
    /**< if > 0 then fill the output buffer with blank color */

    Utils_LatencyStats  linkLatency;
    /**< Structure to find out min, max and average latency of the link */

    Utils_LatencyStats  srcToLinkLatency;
    /**< Structure to find out min, max and average latency from
     *   source to this link
     */

    System_LinkStatistics      * linkStatsInfo;
    /**< link specific statistics */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */
    Bool loadUpsampleCoeffs;
    /**< Flag to load the up scaling coefficients */
    UInt32 drvInstId;
    /**< VPE driver instance ID */
    BspOsal_SemHandle complete;
    /**< Semaphore for the VPE process complete */
    FVID2_Handle fvidHandle;
    /**< VPE/ISS driver instance - FVID2 driver handle */
    FVID2_ProcessList errProcessList;
    /**< VPS error process list */
    AlgorithmLink_VpeSwMsChObj chObj[ALGORITHM_LINK_VPE_SW_MS_MAX_CH];
    /**< VPE link channel specific Object */
    Vps_M2mVpeParams drvChArgs[ALGORITHM_LINK_VPE_SW_MS_MAX_CH];
    /**< VPS driver channel vise create time parameters */
    Vps_M2mCreateParams drvCreateArgs;
    /**< VPS driver create parameters */
    Vps_M2mCreateStatus drvCreateStatus;
    /**< VPS driver create status */
    FVID2_ProcessList processList;
    /**< FVID2 process list - BSP data structure, hold the in/out frame lists */
    Fvid2_FrameList     frameList[ALGORITHM_LINK_VPE_SW_MS_TEMP_BUFF_CNT];
    /**< Frame list used for queue/dequeue operations. */
    Fvid2_Frame         frames[ALGORITHM_LINK_VPE_SW_MS_TEMP_BUFF_CNT][ALGORITHM_LINK_VPE_SW_MS_TEMP_BUFF_CNT];
} AlgorithmLink_VpeSwMsObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_VpeSwMsCreate(void * pObj, void * pCreateParams);
Int32 AlgorithmLink_VpeSwMsProcess(void * pObj);
Int32 AlgorithmLink_VpeSwMsControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_VpeSwMsStop(void * pObj);
Int32 AlgorithmLink_VpeSwMsDelete(void * pObj);

Int32 AlgorithmLink_VpeSwMsPrintStatistics(void * pObj,
                    AlgorithmLink_VpeSwMsObj *pVpeSwMsObj);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
