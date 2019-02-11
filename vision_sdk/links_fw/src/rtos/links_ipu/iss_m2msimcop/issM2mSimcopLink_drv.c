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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "issM2mSimcopLink_priv.h"
#include <include/link_api/issIspConfiguration.h>


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *******************************************************************************
 *
 * \brief This function is the call back function, which gets called when
 *        ISS completes processing and interrupts driver
 *
 * \param  handle            [IN] FVID handle of buffer which was operated upon
 * \param  appData           [IN] App object
 * \param  reserved          [IN]
 *
 * \return  FVID2_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_drvCallBack(Fvid2_Handle handle,
                                       Ptr appData,
                                       Ptr reserved)
{
    IssM2mSimcopLink_Obj *pObj;
    Int32 status = FVID2_SOK;

    pObj = (IssM2mSimcopLink_Obj *)appData;

    if (NULL == pObj)
    {
        status = FVID2_EFAIL;
    }
    else
    {
        BspOsal_semPost(pObj->drvSemProcessComplete);
    }

    return status;

}

Int32 IssM2mSimcopLink_drvCreateDrv(IssM2mSimcopLink_Obj *pObj,
                                    UInt32             chId)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    vpsissSimcopOpenParams_t    drvSimcopOpenParams;
    Vps_M2mIntfCreateParams     drvCreatePrms;
    Fvid2_CbParams              drvCbPrms;
    Vps_M2mIntfCreateStatus     drvCreateStatusPrms;
    IssM2mSimcopLink_ConfigParams drvConfig;
    vpsissldcConfig_t           ldcCfg;
    vpsissvtnfConfig_t          vtnfCfg;

    IssM2mSimcopLink_ChObj *pChObj;

    pChObj = &pObj->chObj[chId];

    VpsM2mIntfCreateParams_init(&drvCreatePrms);
    VpsM2mIntfCreateStatus_init(&drvCreateStatusPrms);
    Fvid2CbParams_init(&drvCbPrms);

    /* set default driver config */
    IssM2mSimcopLink_ConfigParams_Init(&drvConfig);

    vpsissVtnfCfg_init(&vtnfCfg);
    vpsissLdcCfg_init(&ldcCfg);

    drvConfig.ldcConfig = &ldcCfg;
    drvConfig.vtnfConfig = &vtnfCfg;

    drvConfig.chNum = chId;

    /* Initialize lineOffset and down scale factor from the previous link id */
    if (1U < pObj->createArgs.numInQue)
    {
        ldcCfg.lutCfg.lineOffset =
            pObj->prevLinkInfo[1U].queInfo[0U].chInfo[chId].pitch[0U];
        ldcCfg.lutCfg.downScaleFactor =
            (vpsissldcLutDownScFactor_t)
            pObj->prevLinkInfo[1U].queInfo[0U].chInfo[chId].flags;
    }
    IssM2mSimcopLink_drvSetSimcopConfig(pObj, &drvConfig);

    drvCbPrms.cbFxn   = &IssM2mSimcopLink_drvCallBack;
    drvCbPrms.appData = pObj;

    drvCreatePrms.numCh           = 1U;
    drvCreatePrms.chInQueueLength = 1U;
    drvCreatePrms.pAdditionalArgs = (Ptr)&drvSimcopOpenParams;

    if(pObj->createArgs.channelParams[chId].operatingMode
        ==
       ISSM2MSIMCOP_LINK_OPMODE_LDC
    )
    {
        drvSimcopOpenParams.mode = VPS_ISS_SIMCOP_LDC;
    }
    else
    if(pObj->createArgs.channelParams[chId].operatingMode
        ==
       ISSM2MSIMCOP_LINK_OPMODE_VTNF
    )
    {
        drvSimcopOpenParams.mode = VPS_ISS_SIMCOP_VTNF;
    }
    else
    if(pObj->createArgs.channelParams[chId].operatingMode
        ==
       ISSM2MSIMCOP_LINK_OPMODE_LDC_VTNF
    )
    {
        drvSimcopOpenParams.mode = VPS_ISS_SIMCOP_LDC_VTNF;
    }
    else
    {
        drvSimcopOpenParams.mode = VPS_ISS_SIMCOP_LDC_VTNF;
    }

    drvSimcopOpenParams.arg = NULL;
    drvSimcopOpenParams.ldcRdMaxTagCnt = pObj->createArgs.ldcRdMaxTagCnt;

    pChObj->drvHandle = Fvid2_create(
                            FVID2_VPS_COMMON_M2M_INTF_DRV,
                            VPS_M2M_ISS_INST_SIMCOP,
                            &drvCreatePrms,
                            &drvCreateStatusPrms,
                            &drvCbPrms);

    if(NULL == pChObj->drvHandle)
    {
        Vps_printf(" ISSM2MSIMCOP: CH%d: FVID2 Create failed !!!",
                    chId);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Allocate frame buffers and do the necessary initializations
 *
 *  \param pObj   [IN] link obj
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_drvAllocBuffer(IssM2mSimcopLink_Obj * pObj, UInt32 chId)
{
    UInt32 numFrames;
    UInt32 frameIdx, tempAddr;
    Int32 status;
    System_Buffer *pSystemBuffer;
    System_VideoFrameBuffer *pSystemVideoFrameBuffer;
    IssM2mSimcopLink_CreateParams * pPrm;
    System_LinkChInfo *pChInfo;
    IssM2mSimcopLink_ChObj *pChObj;
    Utils_DmaChCreateParams dmaParams;

    pChObj = &pObj->chObj[chId];
    pChInfo = &pObj->linkInfo.queInfo[0].chInfo[chId];

    pPrm = &pObj->createArgs;

    pChObj->pPrevOutBuffer = NULL;

    if(pPrm->channelParams[chId].numBuffersPerCh >
        ISSM2MSIMCOP_LINK_MAX_FRAMES_PER_CH)
    {
        pPrm->channelParams[chId].numBuffersPerCh
            =
            ISSM2MSIMCOP_LINK_MAX_FRAMES_PER_CH;
    }

    status = Utils_queCreate(
                    &pChObj->emptyBufQue,
                    ISSM2MSIMCOP_LINK_MAX_FRAMES_PER_CH,
                    pChObj->emptyBufsMem,
                    UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    numFrames  = pPrm->channelParams[chId].numBuffersPerCh;

    /* driver assumes outPitch[0] == outPitch[1] */
    UTILS_assert(pChObj->outputFramePitch[0U] == pChObj->outputFramePitch[1U]);

    pChObj->outBufSize  =
        (pChObj->outputFrameHeight * pChObj->outputFramePitch[0U]) +
        ((pChObj->outputFrameHeight / 2U) * pChObj->outputFramePitch[1U]);

    for(frameIdx = 0; frameIdx < numFrames; frameIdx++)
    {
        pSystemBuffer           = &pChObj->buffers[frameIdx];
        pSystemVideoFrameBuffer = &pChObj->videoFrames[frameIdx];

        /*
        * Properties of pSystemBuffer
        */
        pSystemBuffer->payload     = pSystemVideoFrameBuffer;
        pSystemBuffer->payloadSize = sizeof(System_VideoFrameBuffer);
        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        pSystemBuffer->chNum       = chId;

        if(System_Link_Ch_Info_Get_Flag_Data_Format(
                    pChInfo->flags
                )
                != SYSTEM_DF_YUV420SP_UV
           )
        {
            /* only YUV420 input format suported as of now */
            UTILS_assert((Bool)FALSE);
        }

        pSystemVideoFrameBuffer->chInfo
            =
                pObj->linkInfo.queInfo[0].chInfo[chId];

        if(System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo)==FALSE)
        {
            pSystemVideoFrameBuffer->bufAddr[0] = Utils_memAlloc(
                                            UTILS_HEAPID_DDR_CACHED_SR,
                                            pChObj->outBufSize,
                                            SYSTEM_BUFFER_ALIGNMENT);
        }
        else
        {
            pSystemVideoFrameBuffer->bufAddr[0] =
                                     System_allocLinkMemAllocInfo(
                                            &pObj->createArgs.memAllocInfo,
                                            pChObj->outBufSize,
                                            SYSTEM_BUFFER_ALIGNMENT);
        }
        UTILS_assert(pSystemVideoFrameBuffer->bufAddr[0] != NULL);

        /*
         * Carving out memory pointer for chroma which will get used in case of
         * SYSTEM_DF_YUV420SP_UV
         */
        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004 Rule 11.3
         * Cast between a pointer and an integral type
         * MISRAC_WAIVER:
         * Pointer address is typecasted to int to calculate and to
         * get the offset of the chroma buffer.
         * allocated buffer address is already checked using
         * Utils_assert
         */
        tempAddr = (UInt32) pSystemVideoFrameBuffer->bufAddr[0];
        tempAddr = tempAddr + (pChObj->outputFrameHeight *
            pChObj->outputFramePitch[0U]);
        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004 Rule 11.3
         * Cast between a pointer and an integral type
         * MISRAC_WAIVER:
         * Calculated chroma buffer offset is assigned to
         * chroma buffer pointer, luma buffer pointer is already
         * checked againts null using UTILS_assert
         */
        pSystemVideoFrameBuffer->bufAddr[1] = (void*)(tempAddr);

        status = Utils_quePut(&pChObj->emptyBufQue,
                                pSystemBuffer,
                                BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /* Allocate Extra frame for saving captured frame */
    if (pObj->createArgs.allocBufferForDump != 0U)
    {
        if(System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo)==FALSE)
        {
            pChObj->saveFrameBufAddr =
                Utils_memAlloc(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    pChObj->outBufSize,
                    SYSTEM_BUFFER_ALIGNMENT);
        }
        else
        {
            pChObj->saveFrameBufAddr =
                    System_allocLinkMemAllocInfo(
                            &pObj->createArgs.memAllocInfo,
                            pChObj->outBufSize,
                            SYSTEM_BUFFER_ALIGNMENT);
        }
        UTILS_assert(pChObj->saveFrameBufAddr != NULL);

        /* Initialize DMA parameters and create object for Frame Dumping */
        Utils_DmaChCreateParams_Init(&dmaParams);
        status = Utils_dmaCreateCh(
                        &pChObj->dumpFramesDmaObj,
                        &dmaParams);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        pChObj->saveFrame = 0xFF;
    }

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Create API for link. Link gets created using this function.
 *
 *      Handles all link creation time functionality.
 *
 * \param  pObj     [IN] Link global handle
 * \param  pPrm     [IN] Link create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_drvCreate(IssM2mSimcopLink_Obj          * pObj,
                              IssM2mSimcopLink_CreateParams * pPrm)
{
    Int32 status;
    UInt32 chId, numChannels;
    System_LinkChInfo *pChInfo;
    IssM2mSimcopLink_ChObj *pChObj;
    IssM2mSimcopLink_ChannelParams *pChPrms;

#ifdef SYSTEM_DEBUG_ISSM2M
    Vps_printf(" ISSM2MSIMCOP: Create in progress !!!\n");
#endif

    UTILS_assert(pPrm->numInQue <= ISSM2MSIMCOP_LINK_MAX_IN_QUE);
    UTILS_assert(pPrm->numInQue != 0U);

    UTILS_MEMLOG_USED_START();

    memcpy(&pObj->createArgs, pPrm, sizeof(IssM2mSimcopLink_CreateParams));

    System_resetLinkMemAllocInfo(&pObj->createArgs.memAllocInfo);

    status = System_linkGetInfo(
        pObj->createArgs.inQueParams[0U].prevLinkId,
        &pObj->prevLinkInfo[0U]);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    UTILS_assert(pObj->createArgs.inQueParams[0U].prevLinkQueId <
                 pObj->prevLinkInfo[0U].numQue);

    numChannels = pObj->prevLinkInfo[0U].queInfo
        [pObj->createArgs.inQueParams[0U].prevLinkQueId].numCh;

    UTILS_assert(numChannels<=ISSM2MSIMCOP_LINK_MAX_CH);

    if (1U < pObj->createArgs.numInQue)
    {
        status = System_linkGetInfo(
            pObj->createArgs.inQueParams[1U].prevLinkId,
            &pObj->prevLinkInfo[1U]);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        UTILS_assert(pObj->createArgs.inQueParams[1U].prevLinkQueId <
                     pObj->prevLinkInfo[1U].numQue);

        numChannels = pObj->prevLinkInfo[1U].queInfo
            [pObj->createArgs.inQueParams[1U].prevLinkQueId].numCh;

        UTILS_assert(numChannels<=ISSM2MSIMCOP_LINK_MAX_CH);
    }

    status = Utils_queCreate(&pObj->fullBufQue,
                              ISSM2MSIMCOP_LINK_MAX_FRAMES,
                              pObj->fullBufsMem,
                              UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /*
     * Population of link info, which will be queried by successor link
     * Only Queue Id 0 is used for frame data
     */
    numChannels = pObj->prevLinkInfo[0U].queInfo
        [pObj->createArgs.inQueParams[0U].prevLinkQueId].numCh;
    pObj->linkInfo.numQue = 1;
    pObj->linkInfo.queInfo[0]
        =
        pObj->prevLinkInfo[0U].
            queInfo[pObj->createArgs.inQueParams[0U].prevLinkQueId];

    pObj->pLastSysBufForLdcLut = NULL;
    for (chId = 0U; chId < numChannels; chId ++)
    {
        pChObj = &pObj->chObj[chId];
        pChInfo = &pObj->linkInfo.queInfo[0].chInfo[chId];
        pChPrms = &pPrm->channelParams[chId];

        pChObj->inputFrameWidth     = pChObj->outputFrameWidth     =
            pChInfo->width;
        pChObj->inputFrameHeight    = pChObj->outputFrameHeight    =
            pChInfo->height;
        pChObj->inputFramePitch[0U] = pChObj->outputFramePitch[0U] =
            pChInfo->pitch[0U];
        pChObj->inputFramePitch[1U] = pChObj->outputFramePitch[1U] =
            pChInfo->pitch[1U];
        pChObj->inputFramePitch[2U] = pChObj->outputFramePitch[2U] =
            pChInfo->pitch[2U];

        if (pChPrms->useOutputFrameSize != 0U)
        {
            pChObj->outputFrameWidth =
                pPrm->channelParams[chId].outputFrameWidth;
            pChObj->outputFrameHeight =
                pPrm->channelParams[chId].outputFrameHeight;

            if (System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags) ==
                SYSTEM_DF_YUV420SP_UV)
            {
                pChObj->outputFramePitch[0U] =
                    SystemUtils_align(pChObj->outputFrameWidth,
                                    ISSM2MSIMCOP_LINK_BUF_ALIGNMENT);

                pChObj->outputFramePitch[1U] = pChObj->outputFramePitch[0U];
                pChObj->outputFramePitch[2U] = pChObj->outputFramePitch[0U];
            }

            /* Output Frame size is different, so change channel info as well */
            pChInfo->width = pChObj->outputFrameWidth;
            pChInfo->height = pChObj->outputFrameHeight;
            pChInfo->pitch[0U] = pChObj->outputFramePitch[0U];
            pChInfo->pitch[1U] = pChObj->outputFramePitch[1U];
            pChInfo->pitch[2U] = pChObj->outputFramePitch[2U];
        }

        if (pChPrms->overrideInFrmSize != 0U)
        {
            pChObj->inputFrameWidth =
                pPrm->channelParams[chId].inputFrameWidth;
            pChObj->inputFrameHeight =
                pPrm->channelParams[chId].inputFrameHeight;
        }
    }

    for (chId=0; chId < numChannels; chId++)
    {
        IssM2mSimcopLink_drvAllocBuffer(pObj, chId);
        status = IssM2mSimcopLink_drvCreateDrv(pObj, chId);
        UTILS_assert(status==0);
    }

    pObj->drvSemProcessComplete = BspOsal_semCreate((Int32) 0, (Bool) TRUE);
    UTILS_assert(pObj->drvSemProcessComplete != NULL);

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->linkId, "ISSM2MSIMCOP");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->isFirstFrameRecv = (Bool) FALSE;

    System_assertLinkMemAllocOutOfMem(
        &pObj->createArgs.memAllocInfo,
        "ISSM2MSIMCOP"
        );

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("ISSM2MSIMCOP:",
                       pObj->memUsed,
                       UTILS_ARRAYSIZE(pObj->memUsed));
#ifdef SYSTEM_DEBUG_ISSM2M
    Vps_printf(" ISSM2MSIMCOP: Create Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete ISS M2M SIMCOP Link and driver handle.
 *
 *
 * \param  pObj         [IN] Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_drvDelete(IssM2mSimcopLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_VideoFrameBuffer *pSystemVideoFrameBuffer;
    UInt32 chId, frameIdx;
    IssM2mSimcopLink_ChObj * pChObj;

#ifdef SYSTEM_DEBUG_ISSM2M
    Vps_printf(" ISSM2MSIMCOP: Delete in progress !!!\n");
#endif

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status==0);

    for(chId=0; chId<pObj->linkInfo.queInfo[0].numCh; chId++)
    {
        pChObj = &pObj->chObj[chId];

        status = Utils_queDelete(&pChObj->emptyBufQue);
        UTILS_assert(status==0);

        for(frameIdx = 0;
            frameIdx < pObj->createArgs.channelParams[chId].numBuffersPerCh;
            frameIdx++)
        {
            pSystemVideoFrameBuffer = &pChObj->videoFrames[frameIdx];

            if(System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo)==FALSE)
            {
                status = Utils_memFree(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        pSystemVideoFrameBuffer->bufAddr[0],
                        pChObj->outBufSize
                     );
                UTILS_assert(status==0);
            }
        }

        status = Fvid2_delete(pChObj->drvHandle, NULL);
        UTILS_assert(status==0);

        /* Free up Extra frame for saving captured frame */
        if (pObj->createArgs.allocBufferForDump != 0U)
        {
            /* Initialize this flag to 0 so that it can't be used */
            pChObj->saveFrame = 0xFF;

            if(System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo)==FALSE)
            {
                /* Free up the extra buffer memory space */
                status = Utils_memFree(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        pChObj->saveFrameBufAddr,
                        pChObj->outBufSize);

                UTILS_assert(status==0);
            }
            pChObj->saveFrameBufAddr = NULL;

            /* Free up the DMA channel object */
            Utils_dmaDeleteCh(&pChObj->dumpFramesDmaObj);
        }
    }

    BspOsal_semDelete(&pObj->drvSemProcessComplete);

#ifdef SYSTEM_DEBUG_ISSM2M
    Vps_printf(" ISSM2MSIMCOP: Delete Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief API for setting SIMCOP parameters for the link.
 *
 *  In this function, configuration provided by the use case is just recorded
 *  inside the link. Providing this to driver happens before process call.
 *
 * \param  pObj        [IN] Link global handle
 * \param  pCfgPrm     [IN] SIMCOP configuration parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_drvSetSimcopConfig(
        IssM2mSimcopLink_Obj             *pObj,
        const IssM2mSimcopLink_ConfigParams *pCfg)
{
    IssM2mSimcopLink_ChObj *pChObj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_LinkChInfo *pChInfo;
    UInt32 chId, i;

    chId = pCfg->chNum;

    /* Check for errors */
    if(chId >= pObj->linkInfo.queInfo[0].numCh)
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        pChObj = &pObj->chObj[chId];
        pChInfo = &pObj->linkInfo.queInfo[0].chInfo[chId];

        /* Check if the pitch and down scaling factor are correct */
        if ((1U < pObj->createArgs.numInQue) &&
            (pObj->createArgs.channelParams[chId].operatingMode !=
                ISSM2MSIMCOP_LINK_OPMODE_VTNF) &&
            (NULL != pCfg->ldcConfig))
        {
            #if 0
            pChInfo = &pObj->prevLinkInfo[1U].queInfo[0U].chInfo[chId];
            if ((pCfg->ldcConfig->lutCfg.lineOffset != pChInfo->pitch[0U]) ||
                (pCfg->ldcConfig->lutCfg.downScaleFactor !=
                    (vpsissldcLutDownScFactor_t)pChInfo->flags))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            #endif

            pChInfo = &pObj->linkInfo.queInfo[0].chInfo[chId];
        }
    }

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        if (NULL != pCfg->ldcConfig)
        {
            memcpy(&pChObj->drvSimcopCfg.ldcCfg,
                         pCfg->ldcConfig,
                         sizeof(vpsissldcConfig_t));
        }
        if (NULL != pCfg->vtnfConfig)
        {
            memcpy(&pChObj->drvSimcopCfg.vtnfCfg,
                         pCfg->vtnfConfig,
                         sizeof(vpsissvtnfConfig_t));
        }

        /* over-ride user set values with values that can be
         * derived by the link
         */
        pChObj->drvSimcopCfg.inpFrmPitch        = pChObj->inputFramePitch[0];
        pChObj->drvSimcopCfg.prevFrmPitch       = pChObj->inputFramePitch[0];
        pChObj->drvSimcopCfg.outFrmPitch        = pChObj->outputFramePitch[0];
        pChObj->drvSimcopCfg.inFrameWidth       = pChObj->inputFrameWidth;
        pChObj->drvSimcopCfg.inFrameHeight      = pChObj->inputFrameHeight;
        pChObj->drvSimcopCfg.cropCfg.cropStartX = 0;
        pChObj->drvSimcopCfg.cropCfg.cropStartY = 0;
        pChObj->drvSimcopCfg.cropCfg.cropWidth  = pChObj->inputFrameWidth;
        pChObj->drvSimcopCfg.cropCfg.cropHeight = pChObj->inputFrameHeight;
        pChObj->drvSimcopCfg.arg                = NULL;

        if (NULL != pCfg->ldcConfig)
        {
            if (FALSE == pCfg->ldcConfig->isAdvCfgValid)
            {
                /* auto-calc block WxH */

                /* by default assume 16x4, increase upto 32x36 depending on input WxH */
                pChObj->drvSimcopCfg.blkWidth      = 16;
                pChObj->drvSimcopCfg.blkHeight     = 4;

                for(i=32U; i>=16U; i-=16U)
                {
                    if((pChInfo->width%i)==0)
                    {
                        pChObj->drvSimcopCfg.blkWidth = i;
                        break;
                    }
                }
                for(i=36U; i>=4U; i-=4U)
                {
                    if((pChInfo->height%i)==0)
                    {
                        pChObj->drvSimcopCfg.blkHeight = i;
                        break;
                    }
                }
            }
            else
            {
                pChObj->drvSimcopCfg.blkWidth =
                    pCfg->ldcConfig->advCfg.outputBlockWidth;
                pChObj->drvSimcopCfg.blkHeight =
                    pCfg->ldcConfig->advCfg.outputBlockHeight;
            }
        }

        pChObj->drvSimcopCfg.ldcCfg.inputFrameWidth  = pChObj->inputFrameWidth;
        pChObj->drvSimcopCfg.ldcCfg.inputFrameHeight = pChObj->inputFrameHeight;
        pChObj->drvSimcopCfg.ldcCfg.isAdvCfgValid    = TRUE;
        pChObj->drvSimcopCfg.ldcCfg.advCfg.outputBlockWidth
                = pChObj->drvSimcopCfg.blkWidth;
        pChObj->drvSimcopCfg.ldcCfg.advCfg.outputBlockHeight
                = pChObj->drvSimcopCfg.blkHeight;
        pChObj->drvSimcopCfg.ldcCfg.advCfg.outputFrameWidth =
            pChObj->outputFrameWidth;
        pChObj->drvSimcopCfg.ldcCfg.advCfg.outputFrameHeight =
            pChObj->outputFrameHeight;
        if (NULL != pCfg->ldcConfig)
        {
            pChObj->drvSimcopCfg.ldcCfg.advCfg.outputStartX = pCfg->ldcConfig->advCfg.outputStartX;
            pChObj->drvSimcopCfg.ldcCfg.advCfg.outputStartY = pCfg->ldcConfig->advCfg.outputStartY;
        }
        pChObj->drvSimcopCfg.ldcCfg.advCfg.enableCircAddrMode = FALSE;
        pChObj->drvSimcopCfg.ldcCfg.advCfg.circBuffSize = 0;
        pChObj->drvSimcopCfg.ldcCfg.advCfg.enableConstOutAddr = FALSE;

        pChObj->drvSimcopCfg.vtnfCfg.outDataFormat = SYSTEM_DF_YUV420SP_UV;
        pChObj->drvSimcopCfg.vtnfCfg.isAdvCfgValid = TRUE;
        pChObj->drvSimcopCfg.vtnfCfg.advCfg.blockWidth
            = pChObj->drvSimcopCfg.blkWidth;
        pChObj->drvSimcopCfg.vtnfCfg.advCfg.blockHeight
            = pChObj->drvSimcopCfg.blkHeight;
        pChObj->drvSimcopCfg.vtnfCfg.advCfg.triggerSource
            = ISSHAL_VTNF_TRG_SRC_HWSEQ;
        pChObj->drvSimcopCfg.vtnfCfg.advCfg.intrEnable      = TRUE;


    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Process the given frame
 *
 * This function performs the actual driver call to process a given frame
 *
 * \param  pObj                 [IN]
 * \param  pInputBuffer         [IN]
 * \param  pOutputImageBuffer   [IN]
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_drvProcessFrame(IssM2mSimcopLink_Obj * pObj,
                                    UInt32 chId,
                                    const System_Buffer     * pInputBuffer,
                                    System_Buffer     * pOutputBuffer)

{
    Fvid2_Frame                 inputMeshTableFrame;
    Fvid2_Frame                 inputFrame;
    Fvid2_Frame                 prevOutputFrame;
    Fvid2_Frame                 outputFrame;
    Fvid2_FrameList             inFrmList;
    Fvid2_FrameList             outFrmList;

    System_VideoFrameBuffer *pVideoInFrame;
    System_VideoFrameBuffer *pVideoOutFrame;
    System_VideoFrameBuffer *pVideoPrevOutFrame;
    Int32 status;
    IssM2mSimcopLink_ChObj *pChObj;

    chId = pInputBuffer->chNum;
    pChObj = &pObj->chObj[chId];

    pVideoInFrame  = (System_VideoFrameBuffer*)pInputBuffer->payload;
    pVideoOutFrame = (System_VideoFrameBuffer*)pOutputBuffer->payload;

    if(pChObj->pPrevOutBuffer!=NULL)
    {
        pVideoPrevOutFrame = (System_VideoFrameBuffer*)
                                pChObj->pPrevOutBuffer->payload;
    }
    else
    {
        pVideoPrevOutFrame = (System_VideoFrameBuffer*)pInputBuffer->payload;
    }

    inputMeshTableFrame.chNum      = 0;
    inputFrame.chNum               = 0;
    outputFrame.chNum              = 0;
    prevOutputFrame.chNum          = 0;

    /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3
       MISRAC_WAIVER:
       LDC Lut table address is typecasted to Ptr, as expected by fvid2 frame
       drivder checks for the null address for the lut table
       This is read dma address. */
    inputMeshTableFrame.addr[0][0] =
        (Ptr)pChObj->drvSimcopCfg.ldcCfg.lutCfg.address;

    inputFrame.addr[0][0] = pVideoInFrame->bufAddr[0];
    inputFrame.addr[0][1] = pVideoInFrame->bufAddr[1];

    outputFrame.addr[0][0] = pVideoOutFrame->bufAddr[0];
    outputFrame.addr[0][1] = pVideoOutFrame->bufAddr[1];

    pVideoOutFrame->metaBufAddr = pVideoInFrame->metaBufAddr;
    pVideoOutFrame->metaBufSize = pVideoInFrame->metaBufSize;
    pVideoOutFrame->metaFillLength = pVideoInFrame->metaFillLength;

    prevOutputFrame.addr[0][0] = pVideoPrevOutFrame->bufAddr[0];
    prevOutputFrame.addr[0][1] = pVideoPrevOutFrame->bufAddr[1];

    pChObj->pPrevOutBuffer = pOutputBuffer;

    inFrmList.frames[VPS_SIMCOP_STREAM_ID_CUR_FRAME]  = &inputFrame;
    inFrmList.frames[VPS_SIMCOP_STREAM_ID_PREV_FRAME] = &prevOutputFrame;
    inFrmList.frames[VPS_SIMCOP_STREAM_ID_MESH_TABLE] = &inputMeshTableFrame;
    outFrmList.frames[VPS_SIMCOP_STREAM_ID_OUT_FRAME] = &outputFrame;

    inFrmList.numFrames = VPS_SIMCOP_STREAM_ID_MAX + 1;
    outFrmList.numFrames = VPS_SIMCOP_STREAM_ID_MAX + 1;

    status = Fvid2_control(
                pChObj->drvHandle,
                IOCTL_VPS_SIMCOP_M2M_SET_PARAMS,
                &pChObj->drvSimcopCfg,
                NULL);

    UTILS_assert(status==0);

    /*
     * Submit Processing Request to the driver, wait on a semaphore and
     * get processed frame
     */
    status = Fvid2_processRequest(
                pChObj->drvHandle,
                &inFrmList,
                &outFrmList);

    UTILS_assert(status==0);

    BspOsal_semWait(pObj->drvSemProcessComplete, BSP_OSAL_WAIT_FOREVER);

    status = Fvid2_getProcessedRequest(
                pChObj->drvHandle,
                &inFrmList,
                &outFrmList,
                FVID2_TIMEOUT_NONE);

    UTILS_assert(status==0);

    if ((TRUE == pObj->createArgs.allocBufferForDump) &&
        (TRUE == pChObj->saveFrame))
    {
        Utils_DmaCopyFill2D dmaPrm;
        System_LinkChInfo *pChInfo;

        pChInfo = &pObj->linkInfo.queInfo[0].chInfo[chId];

        if (pObj->createArgs.channelParams[chId].operatingMode !=
            ISSM2MSIMCOP_LINK_OPMODE_LDC)
        {
            /* VTNF supports only YUV420 output format*/
            dmaPrm.dataFormat = SYSTEM_DF_YUV420SP_UV;
        }
        else
        {
            if (pChObj->drvSimcopCfg.ldcCfg.mode == VPS_ISS_LDC_MODE_YUV420_LDC)
            {
                dmaPrm.dataFormat = SYSTEM_DF_YUV420SP_UV;
            }
            else
            {
                dmaPrm.dataFormat = SYSTEM_DF_RAW16;
            }
        }

        dmaPrm.destAddr[0]  = pChObj->saveFrameBufAddr;

        /* MISRA.PTR.ARITH
         * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
         * MISRAC_WAIVER:
         * Pointer is added with the chroma offset to get the chroma
         * buffer location.
         * saveFrameBufAddr is checked agains null at alloc time
         */
        dmaPrm.destAddr[1]  = pChObj->saveFrameBufAddr +
                                (pChInfo->pitch[0] * pChInfo->height);
        dmaPrm.destPitch[0] = pChInfo->pitch[0];
        dmaPrm.destPitch[1] = pChInfo->pitch[1];
        dmaPrm.destStartX   = 0;
        dmaPrm.destStartY   = 0;
        dmaPrm.width        = pChInfo->width;
        dmaPrm.height       = pChInfo->height;
        dmaPrm.srcAddr[0]   = pVideoOutFrame->bufAddr[0];
        dmaPrm.srcAddr[1]   = pVideoOutFrame->bufAddr[1];
        dmaPrm.srcPitch[0]  = pChInfo->pitch[0];
        dmaPrm.srcPitch[1]  = pChInfo->pitch[1];
        dmaPrm.srcStartX    = 0;
        dmaPrm.srcStartY    = 0;

        status = Utils_dmaCopy2D(&pChObj->dumpFramesDmaObj, &dmaPrm, 1U);
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

        /* Reset the flag */
        pChObj->saveFrame = FALSE;

        Vps_printf(" **************************************************** \n");
        Vps_printf(" ####### Save Frame from location 0x%x ####### \n",
            pChObj->saveFrameBufAddr);
        if (SYSTEM_DF_YUV420SP_UV == dmaPrm.dataFormat)
        {
            Vps_printf(" saveRaw(0, 0x%x, filename, %d, 32, false); ",
                pChObj->saveFrameBufAddr,
                ((pChInfo->pitch[0] *
                pChInfo->height) * 3U) / 8U);
        }
        else
        {
            Vps_printf(" saveRaw(0, 0x%x, filename, %d, 32, false); ",
                pChObj->saveFrameBufAddr,
                (pChInfo->pitch[0] *
                pChInfo->height) / 4U);
        }
        Vps_printf(" **************************************************** \n");
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Process the new input data
 *
 * This function gets called in response to SYSTEM_CMD_NEW_DATA command from
 * previous link.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_drvProcessData(IssM2mSimcopLink_Obj * pObj)
{
    UInt32 bufId;
    System_LinkInQueParams *pInQueParams;
    System_BufferList bufList, bufListLdcLut;
    Int32 status;
    UInt32 chId;
    System_Buffer *pInputBuffer;
    System_Buffer *pOutputBuffer;
    IssM2mSimcopLink_ChObj *pChObj;
    Bool sendCmdToNextLink = FALSE;
    System_LinkStatistics *linkStatsInfo;
    System_VideoFrameCompositeBuffer *pCompBuf;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    if(pObj->isFirstFrameRecv == (Bool) FALSE)
    {
        pObj->isFirstFrameRecv = (Bool) TRUE;

        Utils_resetLinkStatistics(
                &linkStatsInfo->linkStats,
                pObj->linkInfo.queInfo[0].numCh,
                1U);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    pInQueParams = &pObj->createArgs.inQueParams[0U];

    System_getLinksFullBuffers(pInQueParams->prevLinkId,
                               pInQueParams->prevLinkQueId, &bufList);

    if (bufList.numBuf != 0U)
    {
        for (bufId = 0; bufId < bufList.numBuf; bufId++)
        {
            pInputBuffer = bufList.buffers[bufId];

            chId = pInputBuffer->chNum;

            /*
             * Checks on sanity of input buffer
             */
            if (chId >= pObj->linkInfo.queInfo[0].numCh)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
            }
            else
            {
                linkStatsInfo->linkStats.chStats[chId].inBufRecvCount++;

                pChObj = &pObj->chObj[chId];

                /* MISRA.CAST.PTR:MISRAC_2004 Rule_11.4
                   MISRAC_WAIVER:
                   Generic implementation of queue expects data in Ptr* type,
                   so typecasted it to Ptr *. */
                status = Utils_queGet(&pChObj->emptyBufQue,
                                      (Ptr *) &pOutputBuffer,
                                      1U,
                                      BSP_OSAL_NO_WAIT);

                if (status != SYSTEM_LINK_STATUS_SOK)
                {
                    linkStatsInfo->linkStats.chStats[chId].inBufDropCount++;
                }
                else
                {
                    pOutputBuffer->srcTimestamp = pInputBuffer->srcTimestamp;
                    pOutputBuffer->frameId = pInputBuffer->frameId;
                    pOutputBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                    /*
                     * Reaching here means an error free input and empty output buffers
                     * are available
                     */
                    IssM2mSimcopLink_drvProcessFrame(
                                            pObj,
                                            chId,
                                            pInputBuffer,
                                            pOutputBuffer
                                          );

                    Utils_updateLatency(&linkStatsInfo->linkLatency,
                                      pOutputBuffer->linkLocalTimestamp);
                    Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                      pOutputBuffer->srcTimestamp);

                    linkStatsInfo->linkStats.chStats[chId].inBufProcessCount++;
                    linkStatsInfo->linkStats.chStats[chId].outBufCount[0]++;

                    status = Utils_quePut(
                                  &pObj->fullBufQue,
                                  pOutputBuffer,
                                  BSP_OSAL_NO_WAIT);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    sendCmdToNextLink = (Bool) TRUE;
                }
            }
        }

        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                    pInQueParams->prevLinkQueId,
                                    &bufList);

        if(sendCmdToNextLink)
        {
            /*
             * Send command to next link for putting the buffer in output
             * queue of the buffer
             */
            System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                               SYSTEM_CMD_NEW_DATA,
                               NULL);
        }
    }

    /* Process the buffers containing LDC Lut information */
    if(1 <= pObj->createArgs.numInQue)
    {
        pInQueParams = &pObj->createArgs.inQueParams[1U];

        System_getLinksFullBuffers(pInQueParams->prevLinkId,
                                   pInQueParams->prevLinkQueId, &bufList);

        bufListLdcLut.numBuf = 0U;
        if (bufList.numBuf)
        {
            for (bufId = 0U; bufId < bufList.numBuf; bufId++)
            {
                pInputBuffer = bufList.buffers[bufId];

                if (SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER == pInputBuffer->bufType)
                {
                    pCompBuf = (System_VideoFrameCompositeBuffer*) pInputBuffer->payload;

                    UTILS_assert(NULL != pCompBuf);

                    if (pCompBuf->numFrames !=
                        pObj->linkInfo.queInfo[0].numCh)
                    {
                        linkStatsInfo->linkStats.inBufErrorCount++;

                        bufListLdcLut.buffers[bufListLdcLut.numBuf] =
                            pInputBuffer;
                        bufListLdcLut.numBuf ++;
                    }
                    else
                    {
                        for (chId = 0U; chId < pCompBuf->numFrames;
                            chId ++)
                        {
                            linkStatsInfo->linkStats.chStats[chId].
                                inBufRecvCount++;

                            pChObj = &pObj->chObj[chId];

                            /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3
                               MISRAC_WAIVER:
                               LDC Lut table address is typecasted to int, as driver
                               expects this address in uint variable */
                            /* Change the LUT address in the LDC config */
                            pChObj->drvSimcopCfg.ldcCfg.lutCfg.address =
                                (UInt32)pCompBuf->metaBufAddr[chId];
                        }

                        if (NULL != pObj->pLastSysBufForLdcLut)
                        {
                            pOutputBuffer = pObj->pLastSysBufForLdcLut;

                            bufListLdcLut.buffers[bufListLdcLut.numBuf] =
                                pOutputBuffer;
                            bufListLdcLut.numBuf ++;
                        }

                        pObj->pLastSysBufForLdcLut = pInputBuffer;
                    }
                }
            }

            if (0U != bufListLdcLut.numBuf)
            {
                System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                            pInQueParams->prevLinkQueId,
                                            &bufListLdcLut);
            }
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Print statistics like FPS, callback time etc.
 *
 *  \param pObj         [IN] Capture link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_drvPrintStatus(const IssM2mSimcopLink_Obj * pObj)
{
    UTILS_assert(NULL != pObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats, "ISSM2MSIMCOP", (Bool) TRUE);

    Utils_printLatency("ISSM2MSIMCOP",
                       &pObj->linkStatsInfo->linkLatency,
                       &pObj->linkStatsInfo->srcToLinkLatency,
                       (Bool) TRUE);

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief This function returns information about the saved raw frame
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_drvGetSaveFrameStatus(IssM2mSimcopLink_Obj *pObj,
                    IssM2mSimcopLink_GetSaveFrameStatus *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    IssM2mSimcopLink_ChObj *pChObj;
    UInt32 isYuv420Fmt;
    UInt32 chId;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pPrm);

    chId = pPrm->chId;

    /* Only 0th queue id is used for frame data */
    UTILS_assert(chId < pObj->prevLinkInfo[0U].queInfo
                        [pObj->createArgs.inQueParams[0U].prevLinkQueId].numCh);

    pChObj = &pObj->chObj[chId];

    pPrm->isSaveFrameComplete = FALSE;
    pPrm->bufAddr = 0;
    pPrm->bufSize = 0;

    isYuv420Fmt = FALSE;
    if (pObj->createArgs.channelParams[chId].operatingMode !=
        ISSM2MSIMCOP_LINK_OPMODE_LDC)
    {
        isYuv420Fmt = (UInt32) TRUE;
    }
    else
    {
        if (pChObj->drvSimcopCfg.ldcCfg.mode == VPS_ISS_LDC_MODE_YUV420_LDC)
        {
            isYuv420Fmt = (UInt32) TRUE;
        }
        else
        {
            isYuv420Fmt = (UInt32) FALSE;
        }
    }

    if (pObj->createArgs.allocBufferForDump != 0U)
    {
        if(pChObj->saveFrame==FALSE)
        {
            pPrm->isSaveFrameComplete = (UInt32) TRUE;

            /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3
               MISRAC_WAIVER:
               Save Frame address is checked againts null at create time
               Assert to uint as expected by saveFrameStatus structure. */
            pPrm->bufAddr = (UInt32)pChObj->saveFrameBufAddr;

            if ((UInt32) TRUE == isYuv420Fmt)
            {
                pPrm->bufSize =
                    ((pObj->linkInfo.queInfo[0].chInfo[chId].pitch[0] *
                    pObj->linkInfo.queInfo[0].chInfo[chId].height) * 3U) / 2U;
            }
            else
            {
                pPrm->bufSize =
                    pObj->linkInfo.queInfo[0].chInfo[chId].pitch[0] *
                    pObj->linkInfo.queInfo[0].chInfo[chId].height;
            }
        }

        status = SYSTEM_LINK_STATUS_SOK;
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This function save a raw frame into a fixed location
 *
 * \param   pObj     [IN] Capture Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_drvSaveFrame(IssM2mSimcopLink_Obj *pObj, UInt32 chId)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    if ((pObj->createArgs.allocBufferForDump != 0U) &&
        (chId < pObj->linkInfo.queInfo[0].numCh))
    {
        pObj->chObj[chId].saveFrame = TRUE;

        status = SYSTEM_LINK_STATUS_SOK;
    }

    return (status);
}

