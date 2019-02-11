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
 * \ingroup ISSM2MSIMCOP_LINK_API
 * \defgroup ISSM2MSIMCOP_LINK_IMPL Iss M2m Simcop Link Implementation
 *
 * @{
 */


#ifndef ISSM2MSIMCOP_LINK_PRIV_H_
#define ISSM2MSIMCOP_LINK_PRIV_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/issM2mSimcopLink.h>
#include <include/link_api/issSimcopConfiguration.h>
#include <ti/drv/vps/include/iss/vps_m2mIss.h>
#include <ti/drv/vps/include/vps_m2mIntf.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Maximum number of frames getting allocated for iss M2m Simcop link.
 *******************************************************************************
 */
#define ISSM2MSIMCOP_LINK_MAX_FRAMES_PER_CH     (SYSTEM_LINK_MAX_FRAMES_PER_CH)

/**
 *******************************************************************************
 * \brief Maximum number of link objects
 *******************************************************************************
 */
#define ISSM2MSIMCOP_LINK_OBJ_MAX (5U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of frames getting allocated for entire Link.
 *
 *******************************************************************************
 */
#define ISSM2MSIMCOP_LINK_MAX_FRAMES \
    ( ISSM2MSIMCOP_LINK_MAX_CH* \
      ISSM2MSIMCOP_LINK_MAX_FRAMES_PER_CH \
    )

#define ISSM2MSIMCOP_LINK_LDC_LUT_QUE_ID    (1U)

/**
 *******************************************************************************
 *
 * \brief Specifies the alignment of allocated buffer boundary
 *
 *******************************************************************************
 */
#define ISSM2MSIMCOP_LINK_BUF_ALIGNMENT              (VPS_BUFFER_ALIGNMENT*2U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Structure containing attributes for each channel operation
 *
 *******************************************************************************
*/
typedef struct {

    vpsissSimcopCfgPrms_t drvSimcopCfg;
    /**< SIMCOP configuration parameters */

    Utils_QueHandle emptyBufQue;
    /**< Link output side empty buffer queue */

    System_Buffer  *emptyBufsMem[ISSM2MSIMCOP_LINK_MAX_FRAMES_PER_CH];
   /** Holds individual channel empty buffers */

    System_Buffer *pPrevOutBuffer;
    /**< Previous frame's output to be given as input to next frame */

    System_Buffer buffers[ISSM2MSIMCOP_LINK_MAX_FRAMES_PER_CH];
    /**< System buffers for image output */

    System_VideoFrameBuffer videoFrames[ISSM2MSIMCOP_LINK_MAX_FRAMES_PER_CH];
    /**< Payload for System buffers for image output */

    Fvid2_Handle                drvHandle;
    /**< FVID2 driver handle. */

    UInt32 outBufSize;
    /**< Size of output buffer */

    UInt8           *saveFrameBufAddr;
    /**< Frame buffer used for saving captured frame */
    volatile UInt32  saveFrame;
    /**< Flag to indicate saving of the frame from process callback */
    Utils_DmaChObj   dumpFramesDmaObj;
    /**< DMA object to use when dumping frames to memory */

    UInt32           inputFrameWidth;
    UInt32           inputFrameHeight;
    UInt32           inputFramePitch[3];

    UInt32           outputFrameWidth;
    UInt32           outputFrameHeight;
    UInt32           outputFramePitch[3];

} IssM2mSimcopLink_ChObj;

/**
 *******************************************************************************
 *
 *  \brief  Structure containing information for each instance of
 *          Iss capture link.
 *
 *******************************************************************************
*/
typedef struct {

    UInt32 linkId;
    /**< Link ID */

    Utils_TskHndl tsk;
    /**< Handle to link task */

    IssM2mSimcopLink_CreateParams createArgs;
    /**< Create params link */

    System_LinkInfo prevLinkInfo[ISSM2MSIMCOP_LINK_MAX_IN_QUE];
    /**< Information of previous link */

    System_LinkInfo linkInfo;
    /**< Link information, which will be given to next link */

    BspOsal_SemHandle            drvSemProcessComplete;
    /**< Semaphore for tracking process call of the driver */

    IssM2mSimcopLink_ChObj  chObj[ISSM2MSIMCOP_LINK_MAX_CH];
    /**< Attributes for operating each channel */

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Used to log the memory usage of the VPE link */

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

    Utils_QueHandle fullBufQue;
    /**< Link output side full buffer queue */

    System_Buffer   *fullBufsMem[ISSM2MSIMCOP_LINK_MAX_FRAMES];
    /**< Memory for full buff queue */

    System_Buffer   *pLastSysBufForLdcLut;
} IssM2mSimcopLink_Obj;

extern IssM2mSimcopLink_Obj gIssM2mSimcopLink_obj[ISSM2MSIMCOP_LINK_OBJ_MAX];

Int32 IssM2mSimcopLink_getInfo(Void * ptr, System_LinkInfo * info);
Int32 IssM2mSimcopLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList);
Int32 IssM2mSimcopLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList * pBufList);

Int32 IssM2mSimcopLink_drvCreate(IssM2mSimcopLink_Obj * pObj,
                            IssM2mSimcopLink_CreateParams * pPrm);

Int32 IssM2mSimcopLink_drvStart(IssM2mSimcopLink_Obj * pObj);
Int32 IssM2mSimcopLink_drvProcessData(IssM2mSimcopLink_Obj * pObj);
Int32 IssM2mSimcopLink_drvStop(IssM2mSimcopLink_Obj * pObj);
Int32 IssM2mSimcopLink_drvDelete(IssM2mSimcopLink_Obj * pObj);

Int32 IssM2mSimcopLink_drvPutEmptyBuffers(IssM2mSimcopLink_Obj * pObj,
                                     System_BufferList * pBufList);

Int32 IssM2mSimcopLink_drvPrintStatus(const IssM2mSimcopLink_Obj * pObj);

Int32 IssM2mSimcopLink_drvSetSimcopConfig(
        IssM2mSimcopLink_Obj             *pObj,
        const IssM2mSimcopLink_ConfigParams    *pCfg);

Int32 IssM2mSimcopLink_drvSaveFrame(IssM2mSimcopLink_Obj *pObj, UInt32 chId);

Int32 IssM2mSimcopLink_drvGetSaveFrameStatus(IssM2mSimcopLink_Obj *pObj,
                    IssM2mSimcopLink_GetSaveFrameStatus *pPrm);
Int32 IssM2mSimcopLink_drvAllocBuffer(IssM2mSimcopLink_Obj * pObj, UInt32 chId);
Int32 IssM2mSimcopLink_drvCreateDrv(IssM2mSimcopLink_Obj *pObj, UInt32 chId);
Int32 IssM2mSimcopLink_drvProcessFrame(IssM2mSimcopLink_Obj * pObj,
                                    UInt32 chId,
                                    const System_Buffer     * pInputBuffer,
                                    System_Buffer     * pOutputBuffer);
Int32 IssM2mSimcopLink_drvCallBack(Fvid2_Handle handle,
                                       Ptr appData,
                                       Ptr reserved);

#endif

/* @} */
