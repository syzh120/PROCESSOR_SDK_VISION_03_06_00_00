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
 * \ingroup DISPLAY_LINK_API
 * \defgroup DISPLAY_LINK_IMPL Display Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file displayLink_priv.h Display Link private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Display link instance/handle object
 *         - All the local data structures
 *         - Display driver interfaces
 *
 * \version 0.0 (Jun 2013) : [SS] First version
 * \version 0.1 (Jul 2013) : [SS] Updates as per code review comments
 *
 *******************************************************************************
 */

#ifndef DISPLAY_LINK_PRIV_H_
#define DISPLAY_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/displayLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Max Number of display link instances supported
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DISPLAY_LINK_OBJ_MAX                           (4U)

/**
 *******************************************************************************
 *
 *   \brief Link local CMD: Releases displayed frames to previous link
 *
 *******************************************************************************
 */
#define DISPLAY_LINK_CMD_RELEASE_FRAMES                (0x0500U)



/**
 *******************************************************************************
 *
 *   \brief The MAX number of FVID2 frames to be allocated in the display link
 *
 *          This is set to max number of frames queued. Though display link
 *          can support multiple channels, only one channel is selected
 *          and active.
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DISPLAY_LINK_MAX_FRAMES_PER_HANDLE      (SYSTEM_LINK_MAX_FRAMES_PER_CH)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Display link instance object
 *
 *          This structure contains
 *          - All the local data structures
 *          - VPS Data structures required for Display driver interfaces
 *          - All fields to support the Link stats and status information
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 tskId;
    /**< placeholder to store the Display link task Id */
    char name[32];
    /**< Link name */
    Utils_TskHndl tsk;
    /**< placeholder to store the Display link task handler */
    DisplayLink_CreateParams createArgs;
    /**< placeholder to store the Display link create parameters */
    System_LinkInfo inTskInfo;
    /**< Specifies a place holder that describe the LINK information */
    System_LinkQueInfo inQueInfo;
    /**< place holder that describe the output information of the LINK */
    UInt32 curDisplayChannelNum;
    /**< The active input channel selected for display */
    FVID2_Handle displayHndl;
    /**< FVID2 display driver handle */
    Vps_DispCreateParams displayCreateArgs;
    /**< VPS driver Create time parameters */
    Vps_DispDssParams dssPrms;
    /**< DSS driver parameters */
    Vps_DssDispcVidConfig vidCfg;
    /**< DSS driver video pipe configuration structure */
    Vps_DssDispcGfxConfig gfxCfg;
    /**< DSS driver graphics pipe configuration structure */
    Vps_DssDispcAdvDmaConfig dmaCfg;
    /**< DSS advanced DMA configuration */
    UInt32 displayInstId;
    /**< Display driver ID used in this link instance */
    FVID2_Frame frames[DISPLAY_LINK_MAX_FRAMES_PER_HANDLE];
    /**< FVID2 Frames to interface with the display driver */
    Utils_QueHandle fvidFrameQueue;
    /**< Free FVID2 Frames queue for mapping system buffers from input queue */
    FVID2_Frame *fvidFrameQueueMem[DISPLAY_LINK_MAX_FRAMES_PER_HANDLE];
    /**< Free FVID2 Frames Queue Mem */
    Utils_QueHandle systemBufferQueue;
    /**< Free FVID2 Frames queue for mapping system buffers from input queue */
    System_Buffer *systemBufferQueueMem[DISPLAY_LINK_MAX_FRAMES_PER_HANDLE];
    /**< Free FVID2 Frames Queue Mem */
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

    UInt32 isDisplayRunning;
    /**< Flag to indicate if display is running or not */

    UInt32 queueCount;
    /**< Queue count */

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Memory used by this link */

    Bool firstFrameQueue;
    /**< Is first frame queued */

    Vps_DispStatus dispStatus;
} DisplayLink_Obj;


/*******************************************************************************
 *  Display Link Private Functions
 *******************************************************************************
 */
Int32 DisplayLink_updateChInfo(DisplayLink_Obj *pObj,
                              const DisplayLink_SetCfgParams *prm);
Int32 DisplayLink_drvCreate(DisplayLink_Obj *pObj,
                            const DisplayLink_CreateParams *pPrm);
Int32 DisplayLink_drvStart(DisplayLink_Obj *pObj);
Int32 DisplayLink_drvProcessData(DisplayLink_Obj *pObj);
Int32 DisplayLink_drvReleaseData(DisplayLink_Obj *pObj);
Int32 DisplayLink_drvStop(DisplayLink_Obj *pObj);
Int32 DisplayLink_drvDelete(DisplayLink_Obj *pObj);
Int32 DisplayLink_drvSwitchCh(DisplayLink_Obj *pObj,
                              const DisplayLink_SwitchChannelParams *prm);
Int32 DisplayLink_drvPrintStatistics(DisplayLink_Obj *pObj);
Int32 DisplayLink_drvGetStatistics(const DisplayLink_Obj *pObj,
                                   DisplayLink_Statistics *pPrm);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
