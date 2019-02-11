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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "deWarp_algPlugin.h"
#include <include/link_api/issIspConfiguration.h>

/*******************************************************************************
 *  Local Defines
 *******************************************************************************
 */
#define ALG_DEWARP_LDC_DOWN_SAMPLE_DEF (VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)
/**< Default down scale factor */
#define ALG_DEWARP_GET_LDC_MESH_TABLE_PITCH(w, r) \
                                    ((((((w)/(r))+1) + 15U) & ~15U) * (4U))
/**< Used to determine the LDC LUT pitch. w = width and r = down scale factor */
#define ALG_DEWARP_LDC_BLOCK_WIDTH_DEF      (16U)
/**< When LDC block width / height computations is bypassed, this is used
        by default */
#define ALG_DEWARP_LDC_BLOCK_HEIGHT_DEF     (16U)
/**< When LDC block width / height computations is bypassed, this is used
        by default */

/* ========================================================================== */
/*                        Local Function Definitions                          */
/* ========================================================================== */
/** \brief Checks create arguments */
static Int32 deWarpCheckCreateArgs(AlgLink_DeWarpObj *pObj,
                                    AlgLink_DeWarpCreateParams *pPrm,
                                    System_LinkChInfo *pChInfo,
                                    UInt32 numCh);
/** \brief Allocates output buffers and queues them up */
static Int32 deWarpAllocOutputBuffersOneCh(void *pObj, AlgLink_DeWarpObj *pAlgObj);

static Int32 deWarpAllocOutputBuffers(void *pObj, AlgLink_DeWarpObj *pAlgObj,
                                        UInt32 numChannels);
/** \brief Create SIMCOP/LDC driver instances */
static Int32 deWarpCreateDrv(AlgLink_DeWarpObj *pAlgObj, UInt32 chId);
/** \brief configures LDC and SIMCOP */
static Int32 deWarpSetConfig(AlgLink_DeWarpObj *pAlgObj,
                                const AlgLink_DeWarpConfigParams *pCfg);
/** \brief Update LDC Luts with supplied LUTs */
static Int32 deWarpUpdateLdcCfg(AlgLink_DeWarpObj *pAlgObj,
                                AlgLink_DeWarpViewPointParams *pViewParams,
                                UInt32 numChannels);
/** \brief Process all input frame given in a composite frame */
static Int32 deWarpProcessFrame4AllCh(AlgLink_DeWarpObj *pAlgObj,
                                        const System_Buffer *pInputBuffer,
                                        System_Buffer       *pOutputBuffer,
                                        AlgLink_DeWarpViewPointParams
                                                            *pViewParams);

static Int32 deWarpProcessFrameOneCh(AlgLink_DeWarpObj *pAlgObj,
                                        const System_Buffer *pInputBuffer,
                                        System_Buffer       *pOutputBuffer,
                                        AlgLink_DeWarpViewPointParams
                                                            *pViewParams);

/** \brief Prints the plugin stats */
static Int32 deWarpPrintStats(const AlgLink_DeWarpObj *pAlgObj);
/** \brief Configures to save next processed frame of a given channel */
static Int32 deWarpSaveFrame4Ch(AlgLink_DeWarpObj *pAlgObj, UInt32 chId);
/** \brief Returns the current status of frame save operation */
static Int32 deWarpGetSaveFrameStatus(AlgLink_DeWarpObj *pAlgObj,
                                        AlgLink_DeWarpSaveFrame *pPrm);
/** \brief Callback function, called by driver on completion of frame
        processing */
static Int32 deWarpFrameProcessedCb(Fvid2_Handle handle, Ptr appData,
                                    Ptr reserved);
/** \brief Pre fill the output buffers with the user provided values */
static Int32 deWarpPreFillOutBuf(
                    AlgLink_DeWarpObj *pAlgObj,
                    System_VideoFrameCompositeBuffer *pVideoInFrame,
                    System_VideoFrameCompositeBuffer *pVideoOutFrame);
/** \brief Process the Frame slices */
static Int32 deWarpProcessFrameSlices(
                        AlgLink_DeWarpObj *pAlgObj,
                        UInt32 chId,
                        Fvid2_FrameList *pInFrmList,
                        Fvid2_FrameList *pOutFrmList);
/* ========================================================================== */
/*                     Interface Function Definitions                         */
/* ========================================================================== */
static Int32 AlgPluginDeWarpCreateInst(void *pObj, void *pCreateParams);
static Int32 AlgPluginDeWarpDoNothing(void *pObj);
static Int32 AlgPluginDeWarpProcess(void *pObj);
static Int32 AlgLinkDeWarpControl(void *pObj, void *pControlParams);
static Int32 AlgLink_DeWarpDelete(void *pPObj);

/* ========================================================================== */
/*                          Interface Functions                               */
/* ========================================================================== */
/**
 *******************************************************************************
 *
 * \brief Initilizes the plugin
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of deWarp
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgLink_DeWarpPlugin_init(void)
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate  = &AlgPluginDeWarpCreateInst;
    pluginFunctions.AlgorithmLink_AlgPluginProcess = &AlgPluginDeWarpProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl = &AlgLinkDeWarpControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop    = &AlgPluginDeWarpDoNothing;
    pluginFunctions.AlgorithmLink_AlgPluginDelete  = &AlgLink_DeWarpDelete;

#ifdef BUILD_M4
    algId = ALGORITHM_LINK_IPU_ALG_DEWARP;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Create API for the plugin
 *
 *      Handles all plugin creation time functionality
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 AlgPluginDeWarpCreateInst(void *pObj, void *pCreateParams)
{
    Int32 status;
    UInt32 chId, numChannels, inputQId;
    System_LinkInfo prevLinkInfo;
    System_LinkChInfo *pIpChInfo, *pOutChInfo;
    AlgPluginDeWarpChObj *pChObj;
    AlgLink_DeWarpChannelParams *pChPrms;
    AlgLink_DeWarpObj *pAlgObj;
    AlgorithmLink_OutputQueueInfo *pOutQinfo;
    AlgLink_DeWarpCreateParams *pPrm =
                                (AlgLink_DeWarpCreateParams *) pCreateParams;

    UTILS_assert(NULL != pPrm);
    UTILS_assert(NULL != pObj);

    /*  . Alloc space for instance object
        . Register the same
        . Get previous link info and validate params(including plugin params)
        . Setup the output info
        . Allocate output buffers
        . Create driver handles, one for each channel
    */
    pAlgObj = (AlgLink_DeWarpObj *)Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                                                    sizeof(AlgLink_DeWarpObj),
                                                    128U);
    UTILS_assert(NULL != pAlgObj);

    memset(pAlgObj, 0x00, sizeof(AlgLink_DeWarpObj));

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAlgObj);

    inputQId = pPrm->inQueParams.prevLinkQueId;
    status = System_linkGetInfo(pPrm->inQueParams.prevLinkId, &prevLinkInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    numChannels = prevLinkInfo.queInfo[inputQId].numCh;
    status = deWarpCheckCreateArgs(pAlgObj, pPrm,
                                    &prevLinkInfo.queInfo[inputQId].chInfo[0U],
                                    numChannels);
    memcpy(&pAlgObj->createArgs, pPrm, sizeof(AlgLink_DeWarpCreateParams));
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    pAlgObj->numInputCh = numChannels;

    pAlgObj->inputQInfo.qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pAlgObj->outputQInfo.qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutQinfo = &pAlgObj->outputQInfo;
    /* Override the number of channels as 1, as this plugin will output 1
        composite buffer. However, ensure channel parameters are setup for all
        valid channels */
    pOutQinfo->queInfo.numCh = numChannels;

    for (chId = 0U; chId < numChannels; chId ++)
    {
        pOutChInfo = &pOutQinfo->queInfo.chInfo[chId];
        pChObj = &pAlgObj->chObj[chId];
        pIpChInfo = &prevLinkInfo.queInfo[inputQId].chInfo[chId];
        pChPrms = &pPrm->channelParams[chId];

        /* set the output queue info same as input */
        pOutChInfo->flags       = pIpChInfo->flags;
        pOutChInfo->pitch[0U]   = pIpChInfo->pitch[0U];
        pOutChInfo->pitch[1U]   = pIpChInfo->pitch[1U];
        pOutChInfo->pitch[2U]   = pIpChInfo->pitch[2U];
        pOutChInfo->startX      = pIpChInfo->startX;
        pOutChInfo->startY      = pIpChInfo->startY;
        pOutChInfo->width       = pIpChInfo->width;
        pOutChInfo->height      = pIpChInfo->height;

        /* Over ride output info, if required */
        if (0U != pChPrms->useOutputFrameSize)
        {
            pOutChInfo->width = pPrm->channelParams[chId].outputFrameWidth;
            pOutChInfo->height = pPrm->channelParams[chId].outputFrameHeight;
            pOutChInfo->pitch[0U] = SystemUtils_align(pOutChInfo->width,
                                            ALG_PLUGIN_DEWARP_PITCH_ALIGNMENT);
            pOutChInfo->pitch[1U] = pOutChInfo->pitch[0U];
            pOutChInfo->pitch[2U] = pOutChInfo->pitch[0U];
        }
        if (0U != pChPrms->useMaxOutputFrameSize)
        {
            pOutChInfo->width = pPrm->channelParams[chId].maxOutputFrameWidth;
            pOutChInfo->height = pPrm->channelParams[chId].maxOutputFrameHeight;
            pOutChInfo->pitch[0U] = SystemUtils_align(pOutChInfo->width,
                                            ALG_PLUGIN_DEWARP_PITCH_ALIGNMENT);
            pOutChInfo->pitch[1U] = pOutChInfo->pitch[0U];
            pOutChInfo->pitch[2U] = pOutChInfo->pitch[0U];
        }

        /* Update channel object with input parameters & override if required */
        pChObj->inputFrameWidth = pChObj->outputFrameWidth =
                                                        pOutChInfo->width;
        pChObj->inputFrameHeight = pChObj->outputFrameHeight =
                                                        pOutChInfo->height;
        pChObj->inputFramePitch[0U] = pChObj->outputFramePitch[0U] =
                                                        pOutChInfo->pitch[0U];
        pChObj->inputFramePitch[1U] = pChObj->outputFramePitch[1U] =
                                                        pOutChInfo->pitch[1U];
        pChObj->inputFramePitch[2U] = pChObj->outputFramePitch[2U] =
                                                        pOutChInfo->pitch[2U];

        /* Cautio : Do not update the pIpChInfo, as we dont own that */
        if (pChPrms->overrideInFrmSize != 0U)
        {
            pChObj->inputFrameWidth =
                                    pPrm->channelParams[chId].inputFrameWidth;
            pChObj->inputFrameHeight =
                                    pPrm->channelParams[chId].inputFrameHeight;
            pChObj->inputFramePitch[0U] = SystemUtils_align(
                                            pChObj->inputFrameWidth,
                                            ALG_PLUGIN_DEWARP_PITCH_ALIGNMENT);
            pChObj->inputFramePitch[1U] = pChObj->inputFramePitch[0U];
            pChObj->inputFramePitch[2U] = pChObj->inputFramePitch[0U];
        }
    }

    /* Create output, input q and set plugins outQinfo */
    status = AlgorithmLink_queueInfoInit(pObj, 1U, &pAlgObj->inputQInfo,
                                               1U, pOutQinfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* allocate output buffer */
    if (numChannels == 1)
    {
        status = deWarpAllocOutputBuffersOneCh(pObj, pAlgObj);
    } else {
        status = deWarpAllocOutputBuffers(pObj, pAlgObj, numChannels);
    }

    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    pAlgObj->pPrevOutBuffer = NULL;

    for (chId = 0U; chId < numChannels; chId++)
    {
        status = deWarpCreateDrv(pAlgObj, chId);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }

    pAlgObj->drvFrameProcessed = BspOsal_semCreate((Int32)0, (Bool)TRUE);
    UTILS_assert(NULL != pAlgObj->drvFrameProcessed);

    /* Assign pointer to link stats object */
    pAlgObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
                                AlgorithmLink_getLinkId(pObj), "ALG_DEWARP");
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    pAlgObj->isFirstFrameRecv = (Bool)FALSE;
    pAlgObj->processedFrameCount = 0U;

    pAlgObj->activeViewPointId = ALG_PLUGIN_DEWARP_INVALID_VIEW_ID;

    pAlgObj->fillBuf = (UInt32)Utils_memAlloc(
                                    UTILS_HEAPID_DDR_CACHED_SR,
                                    ALG_PLUGIN_DEWARP_MAX_OUT_WIDTH * 2,
                                    128U);
    UTILS_assert (NULL != pAlgObj->fillBuf);

    memset(
        (Ptr)pAlgObj->fillBuf,
        pAlgObj->createArgs.fillValueY,
        ALG_PLUGIN_DEWARP_MAX_OUT_WIDTH);

    pAlgObj->fillBufUV = pAlgObj->fillBuf + ALG_PLUGIN_DEWARP_MAX_OUT_WIDTH;
    memset(
        (Ptr)pAlgObj->fillBufUV,
        pAlgObj->createArgs.fillValueUV,
        ALG_PLUGIN_DEWARP_MAX_OUT_WIDTH);

    Cache_wb(
       (Ptr)pAlgObj->fillBuf,
       ALG_PLUGIN_DEWARP_MAX_OUT_WIDTH,
       Cache_Type_ALL,
       TRUE);

    Cache_wb(
       (Ptr)pAlgObj->fillBufUV,
       ALG_PLUGIN_DEWARP_MAX_OUT_WIDTH,
       Cache_Type_ALL,
       TRUE);

    if (TRUE == pAlgObj->createArgs.useOcmcLdcLut)
    {
        /*
         *  OCMC alloc
         */
        Utils_cbufOcmcInit(UTILS_OCMC_RAM1);

        pAlgObj->createArgs.maxLdcLutSize = \
            SystemUtils_align (pAlgObj->createArgs.maxLdcLutSize + 127U, 128U);

        for (chId = 0U; chId < numChannels; chId ++)
        {
            pChObj = &pAlgObj->chObj[chId];
            pChObj->ocmcLdcLutAddr = (UInt32)Utils_cbufOcmcAlloc(
                                        UTILS_OCMC_RAM1,
                                        1U,
                                        /* bpp */
                                        1U,
                                        /* width */
                                        pAlgObj->createArgs.maxLdcLutSize + 128U,
                                        /* height */
                                        pAlgObj->createArgs.maxLdcLutSize,
                                        /* numLinesPerSlice */
                                        1U);
                                        /* numSlicesPerCbuf */
            UTILS_assert (NULL != pChObj->ocmcLdcLutAddr);
        }
    }

    pAlgObj->curViewParams = NULL;

    return status;
}

static Int32 AlgPluginDeWarpDoNothing(void *pObj)
{
    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Delete ISS M2M SIMCOP Link and driver handle.
 *
 *
 * \param  pObj         [IN] Algorithm plugin handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 AlgLink_DeWarpDelete(void *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool useMemAllocInfo;
    UInt32 numFrames, frmIdx, chId;
    System_VideoFrameCompositeBuffer *pCompBuf;
    System_VideoFrameBuffer *pFrameBuf;
    AlgPluginDeWarpChObj *pChObj;
    AlgLink_DeWarpObj *pAlgObj;

    pAlgObj = (AlgLink_DeWarpObj *) AlgorithmLink_getAlgorithmParamsObj(pObj);
    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    numFrames = pAlgObj->createArgs.channelParams[0U].numBuffersPerCh;
    useMemAllocInfo =
                System_useLinkMemAllocInfo(&pAlgObj->createArgs.memAllocInfo);

    for (frmIdx = 0U; frmIdx < numFrames; frmIdx++)
    {

        if (pAlgObj->numInputCh == 1)
        {
            pFrameBuf = &pAlgObj->frameBuffers[frmIdx];
            UTILS_assert(NULL != pFrameBuf->bufAddr[0U]);

            if(FALSE == useMemAllocInfo)
            {
                status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                       pCompBuf->bufAddr[0U],
                                       pAlgObj->outBufSize[frmIdx]);
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
            }
        } else
        {
            pCompBuf = &pAlgObj->compBuffers[frmIdx];
            UTILS_assert(NULL != pCompBuf->bufAddr[0U][0U]);

            if(FALSE == useMemAllocInfo)
            {
                status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                       pCompBuf->bufAddr[0U][0U],
                                       pAlgObj->outBufSize[frmIdx]);
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
            }
        }
    }

    for (chId = 0; chId < pAlgObj->numInputCh; chId++)
    {
        pChObj = &pAlgObj->chObj[chId];

        status = Fvid2_delete(pChObj->drvHandle, NULL);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        if (pAlgObj->createArgs.allocBufferForDump != 0U)
        {
            pChObj->saveFrame = 0xFF;
            if (FALSE == useMemAllocInfo)
            {
                status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                        pChObj->saveFrameBufAddr,
                                        pChObj->outBufSize);

                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
            }
            pChObj->saveFrameBufAddr = NULL;
        }
    }

    /* Free up the DMA channel object */
    Utils_dmaDeleteCh(&pAlgObj->dumpFramesDmaObj);

    if(pAlgObj->fillBuf != NULL)
    {
        Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                (Ptr)pAlgObj->fillBuf,
                ALG_PLUGIN_DEWARP_MAX_OUT_WIDTH * 2);

    }

    BspOsal_semDelete(&pAlgObj->drvFrameProcessed);
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL, pAlgObj,
                    sizeof(AlgLink_DeWarpObj));

    if (TRUE == pAlgObj->createArgs.useOcmcLdcLut)
    {
        /*
         *  OCMC free
         */
        for (chId = 0; chId < pAlgObj->numInputCh; chId++)
        {
            pChObj = &pAlgObj->chObj[chId];
            Utils_cbufOcmcFree(
                    UTILS_OCMC_RAM1,
                    (Ptr)pChObj->ocmcLdcLutAddr);
        }

        Utils_cbufOcmcDeInit(UTILS_OCMC_RAM1);
    }

    return status;
}

static Int32 AlgLinkDeWarpControl(void *pObj, void *pControlParams)
{
    AlgLink_DeWarpObj *pAlgObj;
    AlgorithmLink_ControlParams *pAlgLinkControlPrm;
    AlgLink_DeWarpConfigParams *pCfgPrm;
    AlgLink_DeWarpSaveFrame *pSaveFrameArg;
    AlgLink_DeWarpSetLdcRouteCfg *pLdcRouteCfg;
    AlgLink_DeWarpTaskPriority *pTaskPriority;
    vpsissRoutingConfig_t simcopRoutingConfig;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pAlgObj = (AlgLink_DeWarpObj *) AlgorithmLink_getAlgorithmParamsObj(pObj);

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    switch(pAlgLinkControlPrm->controlCmd)
    {

        case SYSTEM_CMD_PRINT_STATISTICS:
            status = deWarpPrintStats(pAlgObj);
            break;
        case ALG_LINK_DEWARP_CMD_SET_LDCCONFIG:
            if(sizeof(AlgLink_DeWarpConfigParams) != pAlgLinkControlPrm->size)
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pCfgPrm = (AlgLink_DeWarpConfigParams *)pControlParams;
                status = deWarpSetConfig(pAlgObj, pCfgPrm);
            }
            break;
        case ALG_LINK_DEWARP_CMD_SAVE_FRAME:
            if(sizeof(AlgLink_DeWarpSaveFrame) != pAlgLinkControlPrm->size)
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pSaveFrameArg = (AlgLink_DeWarpSaveFrame *)pControlParams;
                status = deWarpSaveFrame4Ch(pAlgObj, pSaveFrameArg->chId);
            }
            break;
        case ALG_LINK_DEWARP_CMD_GET_SAVE_FRAME_STATUS:
            if(sizeof(AlgLink_DeWarpSaveFrame) != pAlgLinkControlPrm->size)
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pSaveFrameArg = (AlgLink_DeWarpSaveFrame *)pControlParams;
                status = deWarpGetSaveFrameStatus(pAlgObj, pSaveFrameArg);
            }
            break;
        case ALG_LINK_DEWARP_CMD_LDC_ROUTECFG:
            if(sizeof(AlgLink_DeWarpSetLdcRouteCfg) \
                                                    != pAlgLinkControlPrm->size)
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pLdcRouteCfg = \
                            (AlgLink_DeWarpSetLdcRouteCfg *)pControlParams;

                simcopRoutingConfig.numStreams = 0U;

                simcopRoutingConfig.source[0U] = VPS_ISS_INIT_SIMCOP_LDC;

                if (ALG_PLUGIN_DEWARP_LDC_ROUTE_NRT1 == pLdcRouteCfg->route)
                {
                    simcopRoutingConfig.priority[0U] = VPS_ISS_L3_ROUTING_OCPM2;
                }
                else if (ALG_PLUGIN_DEWARP_LDC_ROUTE_NRT2 == \
                                                            pLdcRouteCfg->route)
                {
                    simcopRoutingConfig.priority[0U] = VPS_ISS_L3_ROUTING_OCPM3;
                }

                simcopRoutingConfig.cportId[0U] = 0U;

                simcopRoutingConfig.numStreams ++;

                status = Fvid2_control(
                                pAlgObj->chObj[0U].drvHandle,
                                VPS_ISS_SIMCOP_IOCTL_STREAM_ROUTING,
                                &simcopRoutingConfig,
                                NULL);
                UTILS_assert(0U == status);
            }
            break;
        case ALG_LINK_DEWARP_CMD_GET_TASKPRI:
            pTaskPriority = (AlgLink_DeWarpTaskPriority*)pControlParams;
            pTaskPriority->taskPriority = \
                                BspOsal_taskGetPri(BspOsal_taskGetSelfHandle());
            break;
        case ALG_LINK_DEWARP_CMD_SET_TASKPRI:
            pTaskPriority = (AlgLink_DeWarpTaskPriority*)pControlParams;
            BspOsal_taskSetPri(
                        BspOsal_taskGetSelfHandle(),
                        pTaskPriority->taskPriority);
            break;
        default:
            break;
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
static Int32 AlgPluginDeWarpProcess(void *pObj)
{
    System_LinkInQueParams *pInQueParams;
    System_BufferList inBufList, returnBufList;
    Int32 status;
    UInt32 numChannels, bufId;
    System_Buffer *pInputBuffer, *pOutputBuffer;
    System_LinkStatistics *linkStatsInfo;
    AlgLink_DeWarpViewPointParams *pViewParams = NULL;
    AlgLink_DeWarpObj *pAlgObj = NULL;
    Bool bufDropFlag;

    pAlgObj = (AlgLink_DeWarpObj *) AlgorithmLink_getAlgorithmParamsObj(pObj);
    UTILS_assert(NULL != pAlgObj);

    linkStatsInfo = pAlgObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);
    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pAlgObj->isFirstFrameRecv == (Bool) FALSE)
    {
        pAlgObj->isFirstFrameRecv = (Bool) TRUE;

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1U, 1U);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    pInQueParams = &pAlgObj->createArgs.inQueParams;
    numChannels = pAlgObj->numInputCh;

    System_getLinksFullBuffers(pInQueParams->prevLinkId,
                               pInQueParams->prevLinkQueId, &inBufList);

    if (inBufList.numBuf != 0U)
    {
        for (bufId = 0U; bufId < inBufList.numBuf; bufId++)
        {
            pInputBuffer = inBufList.buffers[bufId];
            if(pInputBuffer == NULL)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }
            linkStatsInfo->linkStats.chStats[0U].inBufRecvCount++;

            status = AlgorithmLink_getEmptyOutputBuffer(pObj, 0U, 0U,
                                                        &pOutputBuffer);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                linkStatsInfo->linkStats.chStats[0U].inBufDropCount++;
                linkStatsInfo->linkStats.chStats[0U].outBufDropCount[0U]++;
            }
            else
            {
                if (pInputBuffer->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER)
                {
                    /*
                     * It is very specifit to 3D SRV usecase, for which bufType is
                     * SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER. So we call it only when
                     * bufType is SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER.
                     * For other usecases other than 3D SRV, for which bufType is
                     * SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER, fillOutBuf should be disabled.
                     */
                    deWarpPreFillOutBuf(
                        pAlgObj,
                        (System_VideoFrameCompositeBuffer *)pInputBuffer->payload,
                        (System_VideoFrameCompositeBuffer *)pOutputBuffer->payload);
                }

                pOutputBuffer->srcTimestamp = pInputBuffer->srcTimestamp;
                pOutputBuffer->frameId = pInputBuffer->frameId;
                pOutputBuffer->linkLocalTimestamp =
                                            Utils_getCurGlobalTimeInUsec();

                linkStatsInfo->linkStats.chStats[0U].inBufProcessCount++;
                /*
                 * Reaching here means an error free input and empty output
                 *  buffers are available
                 */
                /* Get the LDC Config, LUTs and other parameters from apps */
                pViewParams = pAlgObj->createArgs.provideViewPointParams(
                                                pAlgObj->processedFrameCount);
                if (NULL != pViewParams)
                {
                    if (pViewParams->viewPointId != pAlgObj->activeViewPointId)
                    {
                        status = deWarpUpdateLdcCfg(pAlgObj, pViewParams,
                                                    numChannels);
                        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                    }

                    pAlgObj->curViewParams = pViewParams;
                }


                if (pInputBuffer->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME)
                {
                    deWarpProcessFrameOneCh(pAlgObj, pInputBuffer, pOutputBuffer,
                                                pViewParams);
                } else
                {
                    deWarpProcessFrame4AllCh(pAlgObj, pInputBuffer, pOutputBuffer,
                                                 pViewParams);
                }


                pAlgObj->processedFrameCount++;

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                                    pOutputBuffer->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                    pOutputBuffer->srcTimestamp);
                linkStatsInfo->linkStats.chStats[0U].outBufCount[0U]++;


                status = AlgorithmLink_putFullOutputBuffer(pObj, 0U,
                                                                pOutputBuffer);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                System_sendLinkCmd(pAlgObj->createArgs.outQueParams.nextLink,
                                    SYSTEM_CMD_NEW_DATA, NULL);


                returnBufList.numBuf = 1U;
                returnBufList.buffers[0U] = pOutputBuffer;
                status = AlgorithmLink_releaseOutputBuffer(pObj, 0U,
                                                            &returnBufList);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
            bufDropFlag = FALSE;
            returnBufList.numBuf = 1U;
            returnBufList.buffers[0U] = pInputBuffer;
            AlgorithmLink_releaseInputBuffer(pObj, 0U, pInQueParams->prevLinkId,
                                                pInQueParams->prevLinkQueId,
                                                &returnBufList, &bufDropFlag);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/* ========================================================================== */
/*                              Local Functions                               */
/* ========================================================================== */

Int32 deWarpPrintStats(const AlgLink_DeWarpObj *pAlgObj)
{
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(&pAlgObj->linkStatsInfo->linkStats,
                                "ALG_DEWARP", (Bool) TRUE);
    Utils_printLatency("ALG_DEWARP",
                       &pAlgObj->linkStatsInfo->linkLatency,
                       &pAlgObj->linkStatsInfo->srcToLinkLatency,
                       (Bool) TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

static Int32 deWarpGetSaveFrameStatus(AlgLink_DeWarpObj *pAlgObj,
                                        AlgLink_DeWarpSaveFrame *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    AlgPluginDeWarpChObj *pChObj;
    UInt32 chId;

    UTILS_assert(NULL != pAlgObj);
    UTILS_assert(NULL != pPrm);

    chId = pPrm->chId;

    UTILS_assert(chId < pAlgObj->numInputCh);

    pChObj = &pAlgObj->chObj[chId];

    pPrm->isSaveFrameComplete = FALSE;
    pPrm->bufAddr = 0;
    pPrm->bufSize = 0;

    if (0U != pAlgObj->createArgs.allocBufferForDump)
    {
        if(FALSE == pChObj->saveFrame)
        {
            pPrm->isSaveFrameComplete = (UInt32) TRUE;

            /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3
               MISRAC_WAIVER:
               Save Frame address is checked againts null at create time
               Assert to uint as expected by saveFrameStatus structure. */
            pPrm->bufAddr = (UInt32)pChObj->saveFrameBufAddr;

            pPrm->bufSize =
                ((pAlgObj->outputQInfo.queInfo.chInfo[chId].pitch[0] *
                pAlgObj->outputQInfo.queInfo.chInfo[chId].height) * 3U) / 2U;
        }

        status = SYSTEM_LINK_STATUS_SOK;
    }

    return (status);
}


static Int32 deWarpSaveFrame4Ch(AlgLink_DeWarpObj *pAlgObj, UInt32 chId)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    if ((pAlgObj->createArgs.allocBufferForDump != 0U) &&
        (chId < pAlgObj->numInputCh))
    {
        pAlgObj->chObj[chId].saveFrame = TRUE;

        status = SYSTEM_LINK_STATUS_SOK;
    }

    return (status);
}

static Int32 deWarpProcessFrame4AllCh(AlgLink_DeWarpObj *pAlgObj,
                                        const System_Buffer *pInputBuffer,
                                        System_Buffer       *pOutputBuffer,
                                        AlgLink_DeWarpViewPointParams
                                                            *pViewParams)
{
    Fvid2_Frame     ldcMeshTable, inputFrame, prevOutputFrame, outputFrame;
    Fvid2_FrameList inFrmList, outFrmList;

    System_VideoFrameCompositeBuffer *pVideoInFrame, *pVideoOutFrame;
    System_VideoFrameCompositeBuffer *pVideoPrevOutFrame;

    Int32 status;
    AlgPluginDeWarpChObj *pChObj;
    UInt32 chId, tempAddr, mappedCh;

    pVideoInFrame  = (System_VideoFrameCompositeBuffer *)pInputBuffer->payload;
    pVideoOutFrame = (System_VideoFrameCompositeBuffer *)pOutputBuffer->payload;
    pVideoOutFrame->numFrames = pVideoInFrame->numFrames;

    if (NULL != pAlgObj->pPrevOutBuffer)
    {
        pVideoPrevOutFrame = (System_VideoFrameCompositeBuffer*) pAlgObj->pPrevOutBuffer;
    }
    else
    {
        pVideoPrevOutFrame = pVideoInFrame;
    }
    pAlgObj->pPrevOutBuffer = pVideoOutFrame;

    pVideoOutFrame->metaBufAddr[0U] = (void*)pViewParams;
    pVideoOutFrame->metaBufSize = sizeof (void *);
    pVideoOutFrame->metaFillLength = sizeof (void *);

    for (chId = 0U; chId < pVideoInFrame->numFrames; chId++)
    {
        pChObj = &pAlgObj->chObj[chId];

        mappedCh = chId;
        if (TRUE == pViewParams->remapChannels)
        {
            mappedCh = pViewParams->remappedCh[chId];
        }

        ldcMeshTable.chNum      = 0U;
        inputFrame.chNum        = 0U;
        outputFrame.chNum       = 0U;
        prevOutputFrame.chNum   = 0U;

        /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3
           MISRAC_WAIVER:
           LDC Lut table address is typecasted to Ptr, as expected by the driver
           Driver checks for the null address for the lut table
           This is read dma address. */
        ldcMeshTable.addr[0U][0U] =
            (Ptr)pChObj->drvSimcopCfg.ldcCfg.lutCfg.address;

        inputFrame.addr[0U][0U] = pVideoInFrame->bufAddr[0U][mappedCh];
        inputFrame.addr[0U][1U] = pVideoInFrame->bufAddr[1U][mappedCh];

        tempAddr = (UInt32) pVideoOutFrame->bufAddr[0][chId];
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
        pVideoOutFrame->bufAddr[1][chId] = (void*)(tempAddr);

        outputFrame.addr[0][0] = pVideoOutFrame->bufAddr[0][chId];
        outputFrame.addr[0][1] = pVideoOutFrame->bufAddr[1][chId];

        prevOutputFrame.addr[0][0] = pVideoPrevOutFrame->bufAddr[0][chId];
        prevOutputFrame.addr[0][1] = pVideoPrevOutFrame->bufAddr[1][chId];

        inFrmList.frames[VPS_SIMCOP_STREAM_ID_CUR_FRAME]  = &inputFrame;
        inFrmList.frames[VPS_SIMCOP_STREAM_ID_PREV_FRAME] = &prevOutputFrame;
        inFrmList.frames[VPS_SIMCOP_STREAM_ID_MESH_TABLE] = &ldcMeshTable;
        outFrmList.frames[VPS_SIMCOP_STREAM_ID_OUT_FRAME] = &outputFrame;

        inFrmList.numFrames = VPS_SIMCOP_STREAM_ID_MAX + 1;
        outFrmList.numFrames = VPS_SIMCOP_STREAM_ID_MAX + 1;

        deWarpProcessFrameSlices(
                            pAlgObj,
                            chId,
                            &inFrmList,
                            &outFrmList);

        if ((TRUE == pAlgObj->createArgs.allocBufferForDump) &&
            (TRUE == pChObj->saveFrame))
        {
            Utils_DmaCopyFill2D dmaPrm;
            System_LinkChInfo *pChInfo;

            pChInfo = &pAlgObj->outputQInfo.queInfo.chInfo[chId];

            UTILS_assert(ALGLINK_DEWARP_OPMODE_LDC ==
                        pAlgObj->createArgs.channelParams[chId].operatingMode);
            UTILS_assert(VPS_ISS_LDC_MODE_YUV420_LDC ==
                                            pChObj->drvSimcopCfg.ldcCfg.mode);
            dmaPrm.dataFormat = SYSTEM_DF_YUV420SP_UV;

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
            dmaPrm.srcAddr[0]   = pVideoOutFrame->bufAddr[0][chId];
            dmaPrm.srcAddr[1]   = pVideoOutFrame->bufAddr[1][chId];
            dmaPrm.srcPitch[0]  = pChInfo->pitch[0];
            dmaPrm.srcPitch[1]  = pChInfo->pitch[1];
            dmaPrm.srcStartX    = 0;
            dmaPrm.srcStartY    = 0;

            status = Utils_dmaCopy2D(&pAlgObj->dumpFramesDmaObj, &dmaPrm, 1U);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            Vps_printf(" ************************************************* \n");
            Vps_printf(" Frame Parameters Width : %d Height : %d \n",
                        pChInfo->width, pChInfo->height);
            Vps_printf(" ####### Save Frame from location 0x%x ####### \n",
                pChObj->saveFrameBufAddr);
            if (SYSTEM_DF_YUV420SP_UV == dmaPrm.dataFormat)
            {
                Vps_printf(" saveRaw(0, 0x%x, filename, %d, 32, false); ",
                            pChObj->saveFrameBufAddr,
                            ((pChInfo->pitch[0] * pChInfo->height) * 3U) / 8U);
            }
            else
            {
                Vps_printf(" saveRaw(0, 0x%x, filename, %d, 32, false); ",
                            pChObj->saveFrameBufAddr,
                            (pChInfo->pitch[0] * pChInfo->height) / 4U);
            }
            Vps_printf(" ************************************************* \n");
            pChObj->saveFrame = FALSE;
        }
    }
    return status;
}


static Int32 deWarpProcessFrameOneCh(AlgLink_DeWarpObj *pAlgObj,
                                        const System_Buffer *pInputBuffer,
                                        System_Buffer       *pOutputBuffer,
                                        AlgLink_DeWarpViewPointParams
                                                            *pViewParams)
{
    Fvid2_Frame     ldcMeshTable, inputFrame, prevOutputFrame, outputFrame;
    Fvid2_FrameList inFrmList, outFrmList;

    System_VideoFrameBuffer *pVideoInFrame, *pVideoOutFrame;
    System_VideoFrameBuffer *pVideoPrevOutFrame;


    Int32 status;
    AlgPluginDeWarpChObj *pChObj;
    UInt32 chId, tempAddr;

    pVideoInFrame  = (System_VideoFrameBuffer *)pInputBuffer->payload;
    pVideoOutFrame = (System_VideoFrameBuffer *)pOutputBuffer->payload;

    if (NULL != pAlgObj->pPrevOutBuffer)
    {
        pVideoPrevOutFrame = (System_VideoFrameBuffer *) pAlgObj->pPrevOutBuffer;
    }
    else
    {
        pVideoPrevOutFrame = (System_VideoFrameBuffer*)pVideoInFrame;
    }
    pAlgObj->pPrevOutBuffer = pVideoOutFrame;

    pVideoOutFrame->metaBufAddr = (void*)pViewParams;
    pVideoOutFrame->metaBufSize = sizeof (void *);
    pVideoOutFrame->metaFillLength = sizeof (void *);


    for (chId = 0U; chId < 1; chId++)
    {
        pChObj = &pAlgObj->chObj[chId];


        ldcMeshTable.chNum      = 0U;
        inputFrame.chNum        = 0U;
        outputFrame.chNum       = 0U;
        prevOutputFrame.chNum   = 0U;

        /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3
           MISRAC_WAIVER:
           LDC Lut table address is typecasted to Ptr, as expected by the driver
           Driver checks for the null address for the lut table
           This is read dma address. */
        ldcMeshTable.addr[0U][0U] =
            (Ptr)pChObj->drvSimcopCfg.ldcCfg.lutCfg.address;


        inputFrame.addr[0U][0U] = pVideoInFrame->bufAddr[0U];
        inputFrame.addr[0U][1U] = pVideoInFrame->bufAddr[1U];


        tempAddr = (UInt32) pVideoOutFrame->bufAddr[0];
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
        pVideoOutFrame->bufAddr[1] = (void*)(tempAddr);


        outputFrame.addr[0][0] = pVideoOutFrame->bufAddr[0];
        outputFrame.addr[0][1] = pVideoOutFrame->bufAddr[1];

        prevOutputFrame.addr[0][0] = pVideoPrevOutFrame->bufAddr[0];
        prevOutputFrame.addr[0][1] = pVideoPrevOutFrame->bufAddr[1];

        inFrmList.frames[VPS_SIMCOP_STREAM_ID_CUR_FRAME]  = &inputFrame;
        inFrmList.frames[VPS_SIMCOP_STREAM_ID_PREV_FRAME] = &prevOutputFrame;
        inFrmList.frames[VPS_SIMCOP_STREAM_ID_MESH_TABLE] = &ldcMeshTable;
        outFrmList.frames[VPS_SIMCOP_STREAM_ID_OUT_FRAME] = &outputFrame;

        inFrmList.numFrames = VPS_SIMCOP_STREAM_ID_MAX + 1;
        outFrmList.numFrames = VPS_SIMCOP_STREAM_ID_MAX + 1;

        deWarpProcessFrameSlices(
                            pAlgObj,
                            chId,
                            &inFrmList,
                            &outFrmList);


        if ((TRUE == pAlgObj->createArgs.allocBufferForDump) &&
            (TRUE == pChObj->saveFrame))
        {
            Utils_DmaCopyFill2D dmaPrm;
            System_LinkChInfo *pChInfo;

            pChInfo = &pAlgObj->outputQInfo.queInfo.chInfo[chId];

            UTILS_assert(ALGLINK_DEWARP_OPMODE_LDC ==
                        pAlgObj->createArgs.channelParams[chId].operatingMode);
            UTILS_assert(VPS_ISS_LDC_MODE_YUV420_LDC ==
                                            pChObj->drvSimcopCfg.ldcCfg.mode);
            dmaPrm.dataFormat = SYSTEM_DF_YUV420SP_UV;

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

            status = Utils_dmaCopy2D(&pAlgObj->dumpFramesDmaObj, &dmaPrm, 1U);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            Vps_printf(" ************************************************* \n");
            Vps_printf(" Frame Parameters Width : %d Height : %d \n",
                        pChInfo->width, pChInfo->height);
            Vps_printf(" ####### Save Frame from location 0x%x ####### \n",
                pChObj->saveFrameBufAddr);
            if (SYSTEM_DF_YUV420SP_UV == dmaPrm.dataFormat)
            {
                Vps_printf(" saveRaw(0, 0x%x, filename, %d, 32, false); ",
                            pChObj->saveFrameBufAddr,
                            ((pChInfo->pitch[0] * pChInfo->height) * 3U) / 8U);
            }
            else
            {
                Vps_printf(" saveRaw(0, 0x%x, filename, %d, 32, false); ",
                            pChObj->saveFrameBufAddr,
                            (pChInfo->pitch[0] * pChInfo->height) / 4U);
            }
            Vps_printf(" ************************************************* \n");
            pChObj->saveFrame = FALSE;
        }
    }
    return status;
}


static Int32 deWarpUpdateLdcCfg(AlgLink_DeWarpObj *pAlgObj,
                                AlgLink_DeWarpViewPointParams *pViewParams,
                                UInt32 numChannels)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chId, xPad, yPad, viewId;
    AlgPluginDeWarpChObj *pChObj;
    UInt32 isViewIdValid = FALSE;
    System_LinkChInfo *pChInfo = NULL;
    vpsissldcAdvConfig_t *pLdcAdvCfg = NULL;
    System_VideoFrameCompositeBuffer *pCompBuf = NULL;
    Utils_DmaCopy1D dmaPrm;


    viewId = pViewParams->viewPointId;
    pCompBuf = pViewParams->pCompBuf;

    /* Not required to invalidate the view point parameters */

    if (numChannels >= pCompBuf->numFrames)
    {
        isViewIdValid = TRUE;
    }
    for (chId = 0U; ((chId < pCompBuf->numFrames) && (TRUE == isViewIdValid));
            chId ++)
    {
        pChObj = &pAlgObj->chObj[chId];

        if (TRUE == pAlgObj->createArgs.useOcmcLdcLut)
        {
            dmaPrm.srcAddr = (Ptr)(pCompBuf->metaBufAddr[chId]);
            dmaPrm.destAddr = (Ptr)(pChObj->ocmcLdcLutAddr);
            dmaPrm.length = pAlgObj->createArgs.maxLdcLutSize;

            status = Utils_dmaCopy1D(
                            &pAlgObj->dumpFramesDmaObj,
                            &dmaPrm);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            pChObj->drvSimcopCfg.ldcCfg.lutCfg.address = \
                                        pChObj->ocmcLdcLutAddr;
        }
        else
        {
            pChObj->drvSimcopCfg.ldcCfg.lutCfg.address =
                (UInt32)pCompBuf->metaBufAddr[chId];
        }

        pChObj->xPad = xPad = pViewParams->ldcOutPadX[chId];
        pChObj->yPad = yPad = pViewParams->ldcOutPadY[chId];

        /* Update channel object with new width, height
            pitch, block width & height */
        pChObj->outputFrameWidth = pViewParams->ldcOutFrameWidth[chId];
        pChObj->outputFrameHeight = pViewParams->ldcOutFrameHeight[chId];

        pChObj->outputFramePitch[0U] = SystemUtils_align(
                                            pChObj->outputFrameWidth,
                                            ALG_PLUGIN_DEWARP_PITCH_ALIGNMENT);

        pChObj->outputFramePitch[1U] = pChObj->outputFramePitch[0U];
        pChObj->outputFramePitch[2U] = pChObj->outputFramePitch[0U];
        pChObj->drvSimcopCfg.outFrmPitch = pChObj->outputFramePitch[0U];

        /* Just to be consistent, update the output Qs
            channel information */
        pChInfo = &pAlgObj->outputQInfo.queInfo.chInfo[chId];
        pChInfo->width = pChObj->outputFrameWidth;
        pChInfo->height = pChObj->outputFrameHeight;
        pChInfo->pitch[0U] = pChObj->outputFramePitch[0U];
        pChInfo->pitch[1U] = pChObj->outputFramePitch[1U];
        pChInfo->pitch[2U] = pChObj->outputFramePitch[2U];

        pChObj->drvSimcopCfg.blkWidth = pViewParams->ldcOutBlockWidth[chId];
        pChObj->drvSimcopCfg.blkHeight = pViewParams->ldcOutBlockHeight[chId];

        /* Update the configuration, which would be
            applied to h/w before processing the frame*/
        pLdcAdvCfg = &pChObj->drvSimcopCfg.ldcCfg.advCfg;

        pLdcAdvCfg->outputFrameWidth = pChObj->outputFrameWidth - xPad;
        pLdcAdvCfg->outputFrameHeight = pChObj->outputFrameHeight - yPad;

        pAlgObj->activeViewPointId = viewId;
    }
    return status;
}

static Int32 deWarpSetConfig(AlgLink_DeWarpObj *pAlgObj,
                                const AlgLink_DeWarpConfigParams *pCfg)
{
    AlgPluginDeWarpChObj *pChObj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chId;

    chId = pCfg->chNum;

    /* Check for errors */
    if(chId >= pAlgObj->numInputCh)
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        pChObj = &pAlgObj->chObj[chId];
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

        pChObj->drvSimcopCfg.blkWidth = ALG_DEWARP_LDC_BLOCK_WIDTH_DEF;
        pChObj->drvSimcopCfg.blkHeight = ALG_DEWARP_LDC_BLOCK_HEIGHT_DEF;
        if (NULL != pCfg->ldcConfig)
        {
            if (TRUE == pCfg->ldcConfig->isAdvCfgValid)
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
        pChObj->drvSimcopCfg.ldcCfg.advCfg.outputStartX = 0;
        pChObj->drvSimcopCfg.ldcCfg.advCfg.outputStartY = 0;
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

static Int32 deWarpCreateDrv(AlgLink_DeWarpObj *pAlgObj, UInt32 chId)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    vpsissSimcopOpenParams_t    drvSimcopOpenParams;
    Vps_M2mIntfCreateParams     drvCreatePrms;
    Fvid2_CbParams              drvCbPrms;
    Vps_M2mIntfCreateStatus     drvCreateStatusPrms;
    AlgLink_DeWarpConfigParams  drvConfig;
    vpsissldcConfig_t           ldcCfg;
    vpsissvtnfConfig_t          vtnfCfg;

    AlgPluginDeWarpChObj *pChObj;

    pChObj = &pAlgObj->chObj[chId];

    VpsM2mIntfCreateParams_init(&drvCreatePrms);
    VpsM2mIntfCreateStatus_init(&drvCreateStatusPrms);
    Fvid2CbParams_init(&drvCbPrms);
    drvSimcopOpenParams.arg = NULL;
    drvSimcopOpenParams.mode = VPS_ISS_SIMCOP_LDC;
    drvSimcopOpenParams.ldcRdMaxTagCnt = pAlgObj->createArgs.ldcRdMaxTagCnt;

    /* set default driver config */
    AlgLink_DeWarpConfigParams_Init(&drvConfig);

    vpsissVtnfCfg_init(&vtnfCfg);
    vpsissLdcCfg_init(&ldcCfg);

    drvConfig.ldcConfig = &ldcCfg;
    drvConfig.vtnfConfig = &vtnfCfg;

    drvConfig.chNum = chId;

    /* Initialize lineOffset and down scale factor from the previous link id */
    ldcCfg.lutCfg.lineOffset = ALG_DEWARP_GET_LDC_MESH_TABLE_PITCH(
                                    pChObj->inputFramePitch[0U],
                                    (UInt32)ALG_DEWARP_LDC_DOWN_SAMPLE_DEF);
    ldcCfg.lutCfg.downScaleFactor = ALG_DEWARP_LDC_DOWN_SAMPLE_DEF;

    if (0U != pAlgObj->createArgs.channelParams[chId].useMaxOutputFrameSize)
    {
        ldcCfg.lutCfg.lineOffset = ALG_DEWARP_GET_LDC_MESH_TABLE_PITCH(
                    pAlgObj->createArgs.channelParams[chId].outputFrameWidth,
                    (UInt32)ALG_DEWARP_LDC_DOWN_SAMPLE_DEF);
    }


    deWarpSetConfig(pAlgObj, &drvConfig);

    drvCbPrms.cbFxn   = &deWarpFrameProcessedCb;
    drvCbPrms.appData = pAlgObj;

    drvCreatePrms.numCh           = 1U;
    drvCreatePrms.chInQueueLength = 1U;
    drvCreatePrms.pAdditionalArgs = (Ptr)&drvSimcopOpenParams;

    UTILS_assert(ALGLINK_DEWARP_OPMODE_LDC ==
                    pAlgObj->createArgs.channelParams[chId].operatingMode);
    drvSimcopOpenParams.mode = VPS_ISS_SIMCOP_LDC;

    drvSimcopOpenParams.arg = NULL;

    pChObj->drvHandle = Fvid2_create(
                            FVID2_VPS_COMMON_M2M_INTF_DRV,
                            VPS_M2M_ISS_INST_SIMCOP,
                            &drvCreatePrms,
                            &drvCreateStatusPrms,
                            &drvCbPrms);

    if(NULL == pChObj->drvHandle)
    {
        Vps_printf(" ALG_DEWARP: CH%d: FVID2 Create failed !!!",
                    chId);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;
}


static Int32 deWarpAllocOutputBuffersOneCh(void *pObj, AlgLink_DeWarpObj *pAlgObj)
{
    UInt32 outBufferSize, numFrames, frmIdx, tempAddr;
    UInt32 useMemAllocInfo;
    AlgPluginDeWarpChObj *pChObj;
    AlgLink_DeWarpChannelParams *pCreateChPrms;
    Utils_DmaChCreateParams dmaParams;
    System_Buffer *pSysBuf;
    System_VideoFrameBuffer *pVideoBuf;
    Int32 status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    pChObj = &pAlgObj->chObj[0U];
    pCreateChPrms = &pAlgObj->createArgs.channelParams[0U];

    useMemAllocInfo =
                System_useLinkMemAllocInfo(&pAlgObj->createArgs.memAllocInfo);
    outBufferSize  =
        (pChObj->outputFrameHeight * pChObj->outputFramePitch[0U]) +
        ((pChObj->outputFrameHeight / 2U) * pChObj->outputFramePitch[1U]);


    numFrames = pCreateChPrms->numBuffersPerCh;

    for (frmIdx = 0U; frmIdx < numFrames; frmIdx++)
    {
        pSysBuf     = &pAlgObj->sysBuffers[frmIdx];
        pVideoBuf    = &pAlgObj->frameBuffers[frmIdx];

        pSysBuf->payload     = pVideoBuf;
        pSysBuf->payloadSize = sizeof(System_VideoFrameBuffer);
        pSysBuf->bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        pSysBuf->chNum       = 0U;

        if(FALSE == useMemAllocInfo)
        {
            pVideoBuf->bufAddr[0U] = Utils_memAlloc(
                                                UTILS_HEAPID_DDR_CACHED_SR,
                                                (outBufferSize),
                                                128U);
        }
        else
        {
            pVideoBuf->bufAddr[0U] = System_allocLinkMemAllocInfo(
                                            &pAlgObj->createArgs.memAllocInfo,
                                            (outBufferSize),
                                            128U);
        }
        UTILS_assert(NULL != pVideoBuf->bufAddr[0U]);

        //for (chIdx = 0U; chIdx < numChannels; chIdx++)
        {
            pChObj = &pAlgObj->chObj[0];

            tempAddr = (UInt32) pVideoBuf->bufAddr[0U];
            /* Y */
            pVideoBuf->bufAddr[0U] = (void *)tempAddr;
            /* UV */
            tempAddr = tempAddr + (pChObj->outputFrameHeight *
                                                pChObj->outputFramePitch[0U]);
            pVideoBuf->bufAddr[1U] = (void *)(tempAddr);

            /* Not required */
            pVideoBuf->bufAddr[2U] = (void *)NULL;
        }
        status = AlgorithmLink_putEmptyOutputBuffer(pObj, 0U, pSysBuf);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        pAlgObj->outBufSize[frmIdx] = outBufferSize;
    }


    /* Allocate Extra frame for saving processed frame */
    if (0 != pAlgObj->createArgs.allocBufferForDump)
    {

        pChObj = &pAlgObj->chObj[0];

        if(FALSE == useMemAllocInfo)
        {
            pChObj->saveFrameBufAddr = Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    outBufferSize,
                                                    SYSTEM_BUFFER_ALIGNMENT);
        }
        else
        {
            pChObj->saveFrameBufAddr = System_allocLinkMemAllocInfo(
                                                &pAlgObj->createArgs.memAllocInfo,
                                                outBufferSize,
                                                SYSTEM_BUFFER_ALIGNMENT);
        }
        UTILS_assert(pChObj->saveFrameBufAddr != NULL);



        pChObj->outBufSize = outBufferSize;
        pChObj->saveFrame = 0xFF;
    }

    /* Initialize DMA parameters and create object for Frame Dumping */
    Utils_DmaChCreateParams_Init(&dmaParams);
    status = Utils_dmaCreateCh(&pAlgObj->dumpFramesDmaObj, &dmaParams);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}


static Int32 deWarpAllocOutputBuffers(void *pObj, AlgLink_DeWarpObj *pAlgObj,
                                        UInt32 numChannels)
{
    UInt32 outBufferSize, numFrames, frmIdx, chIdx, tempAddr;
    UInt32 useMemAllocInfo;
    AlgPluginDeWarpChObj *pChObj;
    AlgLink_DeWarpChannelParams *pCreateChPrms;
    Utils_DmaChCreateParams dmaParams;
    System_Buffer *pSysBuf;
    System_VideoFrameCompositeBuffer *pCompBuf;
    Int32 status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    pChObj = &pAlgObj->chObj[0U];
    pCreateChPrms = &pAlgObj->createArgs.channelParams[0U];

    useMemAllocInfo =
                System_useLinkMemAllocInfo(&pAlgObj->createArgs.memAllocInfo);
    outBufferSize  =
        (pChObj->outputFrameHeight * pChObj->outputFramePitch[0U]) +
        ((pChObj->outputFrameHeight / 2U) * pChObj->outputFramePitch[1U]);

    numFrames = pCreateChPrms->numBuffersPerCh;

    for (frmIdx = 0U; frmIdx < numFrames; frmIdx++)
    {
        pSysBuf     = &pAlgObj->sysBuffers[frmIdx];
        pCompBuf    = &pAlgObj->compBuffers[frmIdx];

        pSysBuf->payload     = pCompBuf;
        pSysBuf->payloadSize = sizeof(System_VideoFrameCompositeBuffer);
        pSysBuf->bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER;
        pSysBuf->chNum       = 0U;

        if(FALSE == useMemAllocInfo)
        {
            pCompBuf->bufAddr[0U][0U] = Utils_memAlloc(
                                                UTILS_HEAPID_DDR_CACHED_SR,
                                                (outBufferSize * numChannels),
                                                128U);
        }
        else
        {
            pCompBuf->bufAddr[0U][0U] = System_allocLinkMemAllocInfo(
                                            &pAlgObj->createArgs.memAllocInfo,
                                            (outBufferSize * numChannels),
                                            128U);
        }
        UTILS_assert(NULL != pCompBuf->bufAddr[0U][0U]);

        for (chIdx = 0U; chIdx < numChannels; chIdx++)
        {
            pChObj = &pAlgObj->chObj[chIdx];

            tempAddr = (UInt32) pCompBuf->bufAddr[0U][0U] +
                                                        (outBufferSize * chIdx);
            /* Y */
            pCompBuf->bufAddr[0U][chIdx] = (void *)tempAddr;
            /* UV */
            tempAddr = tempAddr + (pChObj->outputFrameHeight *
                                                pChObj->outputFramePitch[0U]);
            pCompBuf->bufAddr[1U][chIdx] = (void *)(tempAddr);

            /* Not required */
            pCompBuf->bufAddr[2U][chIdx] = (void *)NULL;
        }
        status = AlgorithmLink_putEmptyOutputBuffer(pObj, 0U, pSysBuf);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        pAlgObj->outBufSize[frmIdx] = outBufferSize * numChannels;
    }

    /* Allocate Extra frame for saving processed frame */
    for (chIdx = 0U;((0 != pAlgObj->createArgs.allocBufferForDump) &&
                     (chIdx < numChannels)); chIdx++)
    {
        pChObj = &pAlgObj->chObj[chIdx];

        if(FALSE == useMemAllocInfo)
        {
            pChObj->saveFrameBufAddr = Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    outBufferSize,
                                                    SYSTEM_BUFFER_ALIGNMENT);
        }
        else
        {
            pChObj->saveFrameBufAddr = System_allocLinkMemAllocInfo(
                                                &pAlgObj->createArgs.memAllocInfo,
                                                outBufferSize,
                                                SYSTEM_BUFFER_ALIGNMENT);
        }
        UTILS_assert(pChObj->saveFrameBufAddr != NULL);

        pChObj->outBufSize = outBufferSize;
        pChObj->saveFrame = 0xFF;
    }

    /* Initialize DMA parameters and create object for Frame Dumping */
    Utils_DmaChCreateParams_Init(&dmaParams);
    status = Utils_dmaCreateCh(&pAlgObj->dumpFramesDmaObj, &dmaParams);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

static Int32 deWarpCheckCreateArgs(AlgLink_DeWarpObj *pObj,
                                    AlgLink_DeWarpCreateParams *pPrm,
                                    System_LinkChInfo *pChInfo,
                                    UInt32 numCh)
{
    UInt32 chIdx;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    /* Check number of channels it should not be > 4
        Number of buffers per channel should be same
        */
    if ((NULL != pObj) && (NULL != pPrm))
    {
        if ((1U < pPrm->numInQue) || (0U == pPrm->numInQue))
        {
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }

        if ((ALG_LINK_DEWARP_MAX_CH < numCh) &&
            (SYSTEM_LINK_STATUS_SOK == status))
        {
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }

        for (chIdx = 0U; chIdx < numCh; chIdx++)
        {
            if (pPrm->channelParams[chIdx].numBuffersPerCh !=
                pPrm->channelParams[0U].numBuffersPerCh)
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                break;
            }

            if (ALG_PLUGIN_DEWARP_MAX_FRAMES_PER_CH <
                                    pPrm->channelParams[chIdx].numBuffersPerCh)
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                break;
            }

            if (ALGLINK_DEWARP_OPMODE_LDC !=
                                    pPrm->channelParams[chIdx].operatingMode)
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                break;
            }

            /* The input pitch should be same for all channels */
            if (pChInfo->pitch[0U] != pChInfo->pitch[1U])
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                break;
            }

            if (SYSTEM_DF_YUV420SP_UV !=
                    System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags))
            {
                /* only YUV420 input format supported as of now */
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                break;
            }
        }
    }
    return (status);
}

static Int32 deWarpFrameProcessedCb(Fvid2_Handle handle,
                                     Ptr appData,
                                     Ptr reserved)
{
    AlgLink_DeWarpObj *pAlgObj = (AlgLink_DeWarpObj *)appData;
    Int32 status = FVID2_SOK;

    if (NULL != pAlgObj)
    {
        BspOsal_semPost(pAlgObj->drvFrameProcessed);
    }
    else
    {
        status = FVID2_EFAIL;
    }
    return status;
}

static Int32 deWarpPreFillOutBuf(
                    AlgLink_DeWarpObj *pAlgObj,
                    System_VideoFrameCompositeBuffer *pVideoInFrame,
                    System_VideoFrameCompositeBuffer *pVideoOutFrame)
{
    Int32 status;
    UInt32 chId;
    AlgPluginDeWarpChObj *pChObj;
    System_LinkChInfo *pChInfo;
    UInt32 tempAddr;
    Utils_DmaCopyFill2D dmaCopyFill2D;
    UInt32 dstStartX, dstStartY, fillWidth, fillHeight;
    Fvid2_Frame outputFrame;

    /*
     *  Pre fill the output buffers if valid
     */
    for (chId = 0U; chId < pVideoInFrame->numFrames; chId++)
    {
        pChObj = &pAlgObj->chObj[chId];
        pChInfo = &pAlgObj->outputQInfo.queInfo.chInfo[chId];

        if (ALGLINK_DEWARP_FILLTYPE_NONE != \
                                        pAlgObj->createArgs.fillOutBuf[chId])
        {
            tempAddr = (UInt32)pVideoOutFrame->bufAddr[0][chId];
            tempAddr = tempAddr + (pChObj->outputFrameHeight * \
                                    pChObj->outputFramePitch[0U]);
            pVideoOutFrame->bufAddr[1][chId] = (void*)(tempAddr);

            outputFrame.addr[0][0] = \
                                pVideoOutFrame->bufAddr[0][chId];
            outputFrame.addr[0][1] = \
                                pVideoOutFrame->bufAddr[1][chId];

            switch (pAlgObj->createArgs.fillOutBuf[chId])
            {
                case ALGLINK_DEWARP_FILLTYPE_HORZ_DOWN:
                    fillWidth = pChInfo->width;
                    fillHeight = \
                    pChInfo->height/pAlgObj->createArgs.fillRatio;
                    dstStartX = 0U;
                    dstStartY = (pChInfo->height - fillHeight);
                    break;
                case ALGLINK_DEWARP_FILLTYPE_VERT_LEFT:
                    fillWidth = \
                    pChInfo->width/pAlgObj->createArgs.fillRatio;
                    fillHeight = pChInfo->height;
                    dstStartX = 0U;
                    dstStartY = 0U;
                    break;
                case ALGLINK_DEWARP_FILLTYPE_HORZ_TOP:
                    fillWidth = pChInfo->width;
                    fillHeight = \
                    pChInfo->height/pAlgObj->createArgs.fillRatio;
                    dstStartX = 0U;
                    dstStartY = 0U;
                    break;
                case ALGLINK_DEWARP_FILLTYPE_VERT_RIGHT:
                    fillWidth = \
                    pChInfo->width/pAlgObj->createArgs.fillRatio;
                    fillHeight = pChInfo->height;
                    dstStartX = (pChInfo->width - fillWidth);
                    dstStartY = 0U;
                    break;
                default:
                    UTILS_assert (0);
                    break;
            }

            dmaCopyFill2D.dataFormat = SYSTEM_DF_YUV420SP_UV;
            dmaCopyFill2D.destAddr[0] = outputFrame.addr[0][0];
            dmaCopyFill2D.destAddr[1] = outputFrame.addr[0][1];
            dmaCopyFill2D.destPitch[0] = pChInfo->pitch[0];
            dmaCopyFill2D.destPitch[1] = pChInfo->pitch[1];
            dmaCopyFill2D.destStartX = \
                                SystemUtils_align(dstStartX, 4U);
            dmaCopyFill2D.destStartY = \
                                SystemUtils_align(dstStartY, 4U);
            dmaCopyFill2D.width = \
                                SystemUtils_align(fillWidth, 4U);
            dmaCopyFill2D.height = \
                                SystemUtils_align(fillHeight, 4U);
            dmaCopyFill2D.srcAddr[0] = (Ptr)pAlgObj->fillBuf;
            dmaCopyFill2D.srcAddr[1] = (Ptr)pAlgObj->fillBufUV;
            dmaCopyFill2D.srcPitch[0] = 0;
            dmaCopyFill2D.srcPitch[1] = 0;
            dmaCopyFill2D.srcStartX = 0;
            dmaCopyFill2D.srcStartY = 0;

            status = Utils_dmaFill2D(
                                &pAlgObj->dumpFramesDmaObj,
                                &dmaCopyFill2D,
                                1U);
            UTILS_assert (SYSTEM_LINK_STATUS_SOK == status);
        }
    }

    return status;
}

static Int32 deWarpProcessFrameSlices(
                        AlgLink_DeWarpObj *pAlgObj,
                        UInt32 chId,
                        Fvid2_FrameList *pInFrmList,
                        Fvid2_FrameList *pOutFrmList)
{
    Int32 status;
    vpsissldcAdvConfig_t *pLdcAdvCfg;
    UInt32 sliceNum;
    Fvid2_Frame *pOutFrame, outFrame;
    AlgPluginDeWarpChObj *pChObj;
    System_LinkChInfo *pChInfo;
    AlgLink_DeWarpViewPointParams *pViewParams;
    AlgorithmLink_slicePrm *pSlicePrm;
    UInt32 offset, diff;

    pChObj = &pAlgObj->chObj[chId];
    pChInfo = &pAlgObj->outputQInfo.queInfo.chInfo[chId];
    pLdcAdvCfg = &pChObj->drvSimcopCfg.ldcCfg.advCfg;
    pOutFrame = pOutFrmList->frames[VPS_SIMCOP_STREAM_ID_OUT_FRAME];
    pViewParams = pAlgObj->curViewParams;

    /*
     *  Save the output frame address for dumping the slice output.
     */
    memcpy (&outFrame, pOutFrame, sizeof (Fvid2_Frame));

    pSlicePrm = &pViewParams->slicePrm[chId].slice[0];

    /*
     *  IMP:    The LDC doesn't work properly if the first slice doesn't start
     *          at (0,0).
     *          Below is the dummy slice starting at (0, 0) of very small size
     */
    if((pSlicePrm->sliceX != 0) || (pSlicePrm->sliceY != 0))
    {
        UTILS_assert (0U == (pSlicePrm->blockWidth % 16U));
        UTILS_assert (0U == (pSlicePrm->blockHeight % 2U));

        pChObj->drvSimcopCfg.blkWidth = pLdcAdvCfg->outputBlockWidth = \
                                                    pSlicePrm->blockWidth;

        pChObj->drvSimcopCfg.blkHeight = pLdcAdvCfg->outputBlockHeight = \
                                                    pSlicePrm->blockHeight;


        /* Slice parameters are absolute values */
        pLdcAdvCfg->outputStartX = 0U;
        pLdcAdvCfg->outputStartY = 0U;
        pLdcAdvCfg->outputFrameWidth = pSlicePrm->blockWidth;
        pLdcAdvCfg->outputFrameHeight = pSlicePrm->blockHeight;

        /* Y plane address */
        pOutFrame->addr[0][0] = (Ptr)(outFrame.addr[0][0]);

        /* UV plane address */
        pOutFrame->addr[0][1] = (Ptr)(outFrame.addr[0][1]);

        status = Fvid2_control(pChObj->drvHandle,
                                IOCTL_VPS_SIMCOP_M2M_SET_PARAMS,
                                &pChObj->drvSimcopCfg, NULL);
        UTILS_assert(status == 0);

        status = Fvid2_processRequest(pChObj->drvHandle, pInFrmList,
                                        pOutFrmList);
        UTILS_assert(status == 0);

        BspOsal_semWait(pAlgObj->drvFrameProcessed, BSP_OSAL_WAIT_FOREVER);

        status = Fvid2_getProcessedRequest(pChObj->drvHandle, pInFrmList,
                                            pOutFrmList, FVID2_TIMEOUT_NONE);
        UTILS_assert(status == 0);
    }

    for (sliceNum = 0;sliceNum < \
                        pViewParams->slicePrm[chId].numSlices;sliceNum++)
    {
        /*
         *  Multi pass support
         */

        /* The input address remains SAME for all the slices */
        /* The outputBlockWidth and outputBlockHeight varies */
        /* The outputStartX and outputStartY varies */
        /* The outputFrameWidth and outputFrameHeight varies */
        /* The output address should be modifies to fit the slice in the
           complete frame */
        /* The output luma and chroma addresses should be multiple of 16 */
        /* The outputFrameWidth should be multiple of outputBlockWidth */
        /* The outputFrameHeight should be multiple of outputBlockHeight */
        /* The minimum block width for YUV420 should be 16 */
        /* The minimum block height for YUV420 should be 2 */
        /* The slice size is passed as a percent of the width/height */

        pSlicePrm = &pViewParams->slicePrm[chId].slice[sliceNum];

        UTILS_assert (0U == (pSlicePrm->blockWidth % 16U));
        UTILS_assert (0U == (pSlicePrm->blockHeight % 2U));

        pChObj->drvSimcopCfg.blkWidth = pLdcAdvCfg->outputBlockWidth = \
                                                    pSlicePrm->blockWidth;

        pChObj->drvSimcopCfg.blkHeight = pLdcAdvCfg->outputBlockHeight = \
                                                    pSlicePrm->blockHeight;

        if (ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT == \
                                                    pSlicePrm->slicePrmType)
        {
            /* Slice parameters are in percent */
            pLdcAdvCfg->outputStartX = \
                            (pChInfo->width * pSlicePrm->sliceX)/100U;
            pLdcAdvCfg->outputStartY = \
                            (pChInfo->height * pSlicePrm->sliceY)/100U;
            pLdcAdvCfg->outputFrameWidth = \
                            (pChInfo->width * pSlicePrm->sliceW)/100U;
            pLdcAdvCfg->outputFrameHeight = \
                            (pChInfo->height * pSlicePrm->sliceH)/100U;

            /*
             *  StartX and StartY are made multiples of the OBW and OBH
             */
            pLdcAdvCfg->outputStartX =
                SystemUtils_align(pLdcAdvCfg->outputStartX, \
                                            pLdcAdvCfg->outputBlockWidth);
            pLdcAdvCfg->outputStartY =
                SystemUtils_align(pLdcAdvCfg->outputStartY, \
                                            pLdcAdvCfg->outputBlockHeight);

            /*
             *  Width and Height are made multiples of the OBW and OBH
             */
            pLdcAdvCfg->outputFrameWidth =
                SystemUtils_align(pLdcAdvCfg->outputFrameWidth, \
                                            pLdcAdvCfg->outputBlockWidth);
            pLdcAdvCfg->outputFrameHeight =
                SystemUtils_align(pLdcAdvCfg->outputFrameHeight, \
                                            pLdcAdvCfg->outputBlockHeight);
        }
        else
        {
            /* Slice parameters are absolute values */
            pLdcAdvCfg->outputStartX = pSlicePrm->sliceX;
            pLdcAdvCfg->outputStartY = pSlicePrm->sliceY;
            pLdcAdvCfg->outputFrameWidth = pSlicePrm->sliceW;
            pLdcAdvCfg->outputFrameHeight = pSlicePrm->sliceH;
        }

        /*
         *  LDC needs padding at the end of the frame
         */
        if ((pChInfo->width - pChObj->xPad) <= \
            (pLdcAdvCfg->outputStartX + pLdcAdvCfg->outputFrameWidth))
        {
            diff = \
            (pLdcAdvCfg->outputStartX + pLdcAdvCfg->outputFrameWidth) - \
            (pChInfo->width - pChObj->xPad);
            pLdcAdvCfg->outputFrameWidth -= diff;
        }

        if ((pChInfo->height - pChObj->yPad) <= \
            (pLdcAdvCfg->outputStartY + pLdcAdvCfg->outputFrameHeight))
        {
            diff = \
            (pLdcAdvCfg->outputStartY + pLdcAdvCfg->outputFrameHeight) - \
            (pChInfo->height - pChObj->yPad);
            pLdcAdvCfg->outputFrameHeight -= diff;
        }

        /* Y plane address */
        offset = (pLdcAdvCfg->outputStartY * pChInfo->pitch[0]) + \
                    pLdcAdvCfg->outputStartX;
        pOutFrame->addr[0][0] = \
            (Ptr)((UInt32)outFrame.addr[0][0] + offset);

        /* UV plane address */
        offset = ((pLdcAdvCfg->outputStartY >> 1) * pChInfo->pitch[1]) + \
                    pLdcAdvCfg->outputStartX;
        pOutFrame->addr[0][1] = \
            (Ptr)((UInt32)outFrame.addr[0][1] + offset);

        status = Fvid2_control(pChObj->drvHandle,
                                IOCTL_VPS_SIMCOP_M2M_SET_PARAMS,
                                &pChObj->drvSimcopCfg, NULL);
        UTILS_assert(status == 0);

        status = Fvid2_processRequest(pChObj->drvHandle, pInFrmList,
                                        pOutFrmList);
        UTILS_assert(status == 0);

        BspOsal_semWait(pAlgObj->drvFrameProcessed, BSP_OSAL_WAIT_FOREVER);

        status = Fvid2_getProcessedRequest(pChObj->drvHandle, pInFrmList,
                                            pOutFrmList, FVID2_TIMEOUT_NONE);
        UTILS_assert(status == 0);
    }

    return status;
}
