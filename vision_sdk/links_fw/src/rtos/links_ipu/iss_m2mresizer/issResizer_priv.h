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
 * \ingroup ISS_RESIZER_LINK_API
 * \defgroup ISS_RESIZER_LINK_IMPL VPE Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file vpeLink_priv.h VPE Link private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - VPE link instance/handle object
 *         - All the local data structures
 *         - VPE BSP driver interfaces
 *
 * \version 0.0 (Sept 2013) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef ISS_RESIZER_LINK_PRIV_H_
#define ISS_RESIZER_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/issM2mResizerLink.h>

#include <ti/drv/vps/include/vpe/vps_m2m.h>

#include <ti/drv/vps/include/vps_m2mIntf.h>
#include <ti/drv/vps/include/iss/vps_m2mIss.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Max Number of VPE link instances supported
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ISS_RSZ_LINK_OBJ_MAX                     (4U)

/**
 *******************************************************************************
 *
 *   \brief Define the Max Number of output buffers per channel of VPE link
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ISS_RSZ_LINK_MAX_OUT_FRAMES_PER_CH       (10U)


/**
 *******************************************************************************
 *
 * \brief Specifies the alignment of allocated buffer boundary
 *
 *******************************************************************************
 */
#define ISS_RSZ_LINK_BUF_ALIGNMENT              (ISS_RSZ_LINK_RSZ_BUF_ALIGN)


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Data Structure for the VPE link Output object
 *
 *          This includes the output side
 *          - Queues
 *          - System buffers
 *          - FVID2 frames
 *
 *******************************************************************************
*/
typedef struct {
    Utils_BufHndl               bufOutQue;
    /**< Output buffer queue */
    System_Buffer               buffers[ISS_RSZ_LINK_MAX_CH]
        [ISS_RSZ_LINK_MAX_OUT_FRAMES_PER_CH];
    /**< System buffer data structure to exchange buffers between links */
    System_VideoFrameBuffer     videoFrames[ISS_RSZ_LINK_MAX_CH]
        [ISS_RSZ_LINK_MAX_OUT_FRAMES_PER_CH];
    /**< Payload for System buffers */
    UInt32                      numFrames[ISS_RSZ_LINK_MAX_CH];
    /**< Number of output buffers per channel */
    Utils_QueHandle             emptyBufQue[ISS_RSZ_LINK_MAX_CH];
    /**< VPE link output side empty buffer queue */
    System_Buffer               *bufsMem[ISS_RSZ_LINK_MAX_CH]
        [ISS_RSZ_LINK_MAX_OUT_FRAMES_PER_CH];
    /** Holds individual channel empty buffers */
    UInt8                       *bufBaseAddr[ISS_RSZ_LINK_MAX_CH]
        [ISS_RSZ_LINK_MAX_OUT_FRAMES_PER_CH];
    /**< Base address of buffer for this output and this CH */
    UInt32                      bufSize[ISS_RSZ_LINK_MAX_CH];
    /**< Total buffer size for this for this output and this CH */
} IssRszLink_OutObj;

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
    Bool                            enableOut[ISSRSZ_LINK_OUTPUTQUE_MAXNUM];
    /**< Output Queue enable/disable flag */
    vpsissIspParams_t               drvIspPrms;
    /**< VPS driver channel wise ISP parameters */
    vpsissRszCfg_t                  drvRszCfg;
    /**< VPS driver channel wise Re-sizer configuration parameters */
    vpsissIpipeInConfig_t           drvIpipeInputCfg;
    /**< VPS driver channel wise Ipipe Input configuration parameters */
    vpsissIsifBlackClampConfig_t    isifBlkClampCfg;
    /**< ISIF Black Clamping Configuration */
} IssRszLink_ChObj;

/**
 *******************************************************************************
 *
 *   \brief Data Structure for VPE request object,
 *          This is for the Link internal, and is the object hold all the
 *          required informations to invoking the BSP driver processing call
 *
 *******************************************************************************
*/
typedef struct {
    FVID2_FrameList inFrameList;
    /**< Input frame list, to hold the input frames */
    FVID2_FrameList outFrameList;
    /**< Output frame list, to hold the output frames */
    Fvid2_Frame     inputFrame;
    Fvid2_Frame     outputFrame[ISSRSZ_LINK_OUTPUTQUE_MAXNUM];
} IssRszLink_ReqObj;

/**
 *******************************************************************************
 *
 *   \brief VPE link instance object
 *
 *          This structure contains
 *          - All the local data structures
 *          - VPS/BSP Data structures required for VPE BSP driver interfaces
 *          - All fields to support the Link stats and status information
 *
 *******************************************************************************
*/
typedef struct {
    UInt32                          linkId;
    /**< placeholder to store the link task Id */
    char                            name[32];
    /**< Link name */
    Utils_TskHndl                   tsk;
    /**< placeholder to store the link task handler */
    IssRszLink_CreateParams         createArgs;
    /**< VPE link create time parameters */
    System_LinkInfo                 inTskInfo;
    /**< Specifies a place holder that describe the LINK information */
    System_LinkQueInfo              inQueInfo;
    /**< Input Q channel specific info, read from the outQ of previous LINK */
    IssRszLink_ReqObj               reqObj;
    /**< Link internal data structure, object hold all the required
     *   informations to invoking the BSP driver processing call */
    IssRszLink_OutObj               outObj[ISSRSZ_LINK_OUTPUTQUE_MAXNUM];
    /**<  Data Structure to hold the VPE link Output object*/
    System_LinkInfo                 info;
    /**< VPE link output queue info, the next link query & use this info */
    Vps_M2mIntfCreateParams         drvCreatePrms;
    /**< Create Parameters */
    Vps_M2mIntfCreateStatus         drvCreateStatusPrms;
    /**< Create Status Parameters */
    vpsissIspOpenParams_t           drvOpenPrms;
    /**< Core Open Parameters */
    vpsissIspOpenRetParams_t        drvRetPrms;
    /**< Core Returns Parameters */
    Vps_M2mIntfStats                drvStats;
    /**< Core Status */
    FVID2_Handle                    fvidHandle;
    /**< VPE/ISS driver instance - FVID2 driver handle */
    FVID2_ProcessList               errProcessList;
    /**< VPS error process list */
    IssRszLink_ChObj                chObj[ISS_RSZ_LINK_MAX_CH];
    /**< VPE link channel specific Object */
    BspOsal_SemHandle               complete;
    /**< Semaphore for the VPE process complete */

    UInt32                          memUsed[UTILS_MEM_MAXHEAPS];
    /**< Used to log the memory usage of the VPE link */
    System_LinkStatistics           *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool                            isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */
} IssRszLink_Obj;

/*******************************************************************************
 *  VPE Link Private Functions
 *******************************************************************************
 */
Int32 IssRszLink_getLinkInfo(Void * pTsk, System_LinkInfo * info);
Int32 IssRszLink_getFullBuffers(Void * ptr, UInt16 queId,
                             System_BufferList * pBufList);
Int32 IssRszLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList);
Int32 IssRszLink_drvCreate(IssRszLink_Obj * pObj,const IssRszLink_CreateParams * pPrm);
Int32 IssRszLink_drvProcessData(IssRszLink_Obj * pObj);
Int32 IssRszLink_drvDelete(IssRszLink_Obj * pObj);
Int32 IssRszLink_printStatistics (const IssRszLink_Obj *pObj, Bool resetAfterPrint);
Int32 IssRszLink_printBufferStatus(IssRszLink_Obj * pObj);
Int32 IssRszLink_drvCreateFvidObj(IssRszLink_Obj *pObj);
Int32 IssRszLink_drvProcessFrame(
        IssRszLink_Obj      *pObj,
        const System_Buffer *pInputBuffer,
        System_Buffer       *pOutputBuffer[ISSRSZ_LINK_OUTPUTQUE_MAXNUM]);
Int32 IssRszLink_drvFvidCb(FVID2_Handle handle, Ptr appData, Ptr reserved);
Int32 IssRszLink_drvFvidErrCb(FVID2_Handle handle,
                              Ptr appData, Ptr errList, Ptr reserved);
Int32 IssRszLink_drvCreateOutAndAllocBuffers(IssRszLink_Obj *pObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
