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
 * \file issM2mIspLink_drv_process_frame.c
 *
 * \brief  This file communicates with driver for iss M2m isp link.
 *
 *         This file calls the driver commands and APIs for the application
 *         commands and APIs. All application commands and APIs finally gets
 *         translated to driver APIs and commands by this file.
 *
 * \version 0.0 (Jul 2014) : [PS] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "issM2mIspLink_priv.h"

/*******************************************************************************
 *  Local Functions
 *******************************************************************************
 */
static UInt32 issM2mIspLinkCalculateEvRatio(UInt32 exposureRatio);
static UInt32 issM2mIspLinkPower2(UInt32 k);
static Void issMemIspLinkCopyIspConfig(
        IssIspConfigurationParameters *pIspCfgTar,
        const IssIspConfigurationParameters *pIspCfgSrc);
static Void issMemIspLinkSaveFrame(
    IssM2mIspLink_Obj *pObj,
    UInt32 chId,
    System_Buffer *pOutputBuffer[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);

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
Int32 IssM2mIspLink_drvCallBack(Fvid2_Handle handle,
        Ptr appData,
        Ptr reserved)
{
    IssM2mIspLink_Obj *pObj;
    Int32 status = FVID2_SOK;

    pObj = (IssM2mIspLink_Obj *)appData;

    if ((NULL == pObj) || (NULL == pObj->linkStatsInfo))
    {
        status = FVID2_EFAIL;
    }
    else
    {

        pObj->linkStatsInfo->linkStats.notifyEventCount++;

        BspOsal_semPost(pObj->semProcessCall);

        status = FVID2_SOK;
    }
    return status;
}

/*#define _DEBUG_PRC_FRM_ */
#ifdef _DEBUG_PRC_FRM_
/*
Functon to print frame level information on UART console . Debug only.
 */
volatile Int32 g_debug_proces_frame = 0;
Int32 debug_proces_frame(
        System_VideoFrameBuffer *pVideoOutFrameRszA,
        System_VideoFrameBuffer *pVideoOutFrameRszB,
        System_MetaDataBuffer *pH3aOutFrame
)
{
    Int32 status = 0;
    if(g_debug_proces_frame)
    {
        Vps_printf("pVideoOutFrameRszA = %x\n", pVideoOutFrameRszA->bufAddr);
        Vps_printf("pVideoOutFrameRszB = %x\n", pVideoOutFrameRszB->bufAddr);
        Vps_printf("pH3aOutFrame = %x\n", pH3aOutFrame->bufAddr);
    }

    return status;
}
#endif



/**
 *******************************************************************************
 *
 * \brief Process the given frame
 *
 * This function performs the actual driver call to process a given frame
 *
 * \param  pObj                 [IN]
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mIspLink_drvProcessFrame(
        IssM2mIspLink_Obj *pObj,
        const System_Buffer *pInputBuffer,
        System_Buffer     *pOutputBuffer[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM],
        UInt32             passId)

{
    Fvid2_Frame     inputFrame;
    Fvid2_Frame     intermedFrame;
    Fvid2_Frame     outputFrame[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM];
    Fvid2_FrameList inFrmList;
    Fvid2_FrameList outFrmList;

    System_VideoFrameBuffer *pVideoInFrame;
    System_VideoFrameBuffer *pVideoOutFrameRszA;
    System_VideoFrameBuffer *pVideoOutFrameRszB;
    System_MetaDataBuffer   *pH3aOutFrame;

    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM] = { FALSE };

    IssM2mIspLink_OperatingMode operatingMode;

    Int32 status;
    UInt32 chId, queId, i;

    pVideoOutFrameRszA  = NULL;
    pVideoOutFrameRszB  = NULL;
    pH3aOutFrame        = NULL;

    chId = pInputBuffer->chNum;
    operatingMode = pObj->createArgs.channelParams[chId].operatingMode;

    inputFrame.chNum = 0;
    intermedFrame.chNum = 0;
    for(queId=0; queId<ISSM2MISP_LINK_OUTPUTQUE_MAXNUM; queId++)
    {
        outputFrame[queId].chNum = 0;
    }

    for(i=0; i<VPS_ISS_STREAM_ID_MAX ; i++)
    {
        inFrmList.frames[i] = NULL;
        outFrmList.frames[i] = NULL;
    }

    pVideoInFrame = (System_VideoFrameBuffer*)pInputBuffer->payload;

    inputFrame.addr[0][0] = pVideoInFrame->bufAddr[0];

    inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] = &inputFrame;

    queId = ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A;
    if(pOutputBuffer[queId])
    {
        pVideoOutFrameRszA
        = (System_VideoFrameBuffer*)
        pOutputBuffer[queId]->payload;

        enableOut[queId] = (Bool)TRUE;

        /* For monochrome mode, resizer operates only on chroma portion and
           buffers are allocated for YUV420 format, so swapping luma
           and chroma buffers here so that chroma buffer pointer will have
           full frame buffer and luma buffer pointer points to half size buffer.

           This swapped FVID2 frame is not forwarded to next link,
           next link gets original non-swapped buffer pointers, so it is ok
           to swap pointers here. */
        if (ISSM2MISP_LINK_OPMODE_12BIT_MONOCHROME == operatingMode)
        {
            outputFrame[queId].addr[0][1] = pVideoOutFrameRszA->bufAddr[0];
            outputFrame[queId].addr[0][0] = pVideoOutFrameRszA->bufAddr[1];
        }
        else
        {
            outputFrame[queId].addr[0][0] = pVideoOutFrameRszA->bufAddr[0];
            outputFrame[queId].addr[0][1] = pVideoOutFrameRszA->bufAddr[1];
        }

        outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A] = &outputFrame[queId];

        pVideoOutFrameRszA->metaBufAddr = pVideoInFrame->metaBufAddr;
        pVideoOutFrameRszA->metaBufSize = pVideoInFrame->metaBufSize;
        pVideoOutFrameRszA->metaFillLength = pVideoInFrame->metaFillLength;
    }

    queId = ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B;
    if(pOutputBuffer[queId])
    {
        pVideoOutFrameRszB
        = (System_VideoFrameBuffer*)
        pOutputBuffer[queId]->payload;

        enableOut[queId] = (Bool)TRUE;

        /* for monochrome, resizer b is not enabled, but if it is enabled,
            addresses of luma and chroma are swapped here */
        if (ISSM2MISP_LINK_OPMODE_12BIT_MONOCHROME == operatingMode)
        {
            outputFrame[queId].addr[0][1] = pVideoOutFrameRszB->bufAddr[0];
            outputFrame[queId].addr[0][0] = pVideoOutFrameRszB->bufAddr[1];
        }
        else
        {
            outputFrame[queId].addr[0][0] = pVideoOutFrameRszB->bufAddr[0];
            outputFrame[queId].addr[0][1] = pVideoOutFrameRszB->bufAddr[1];
        }

        outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_B] = &outputFrame[queId];

        pVideoOutFrameRszB->metaBufAddr = pVideoInFrame->metaBufAddr;
        pVideoOutFrameRszB->metaBufSize = pVideoInFrame->metaBufSize;
        pVideoOutFrameRszB->metaFillLength = pVideoInFrame->metaFillLength;
    }

    queId = ISSM2MISP_LINK_OUTPUTQUE_H3A;
    if(pOutputBuffer[queId])
    {
        pH3aOutFrame
        = (System_MetaDataBuffer*)
        pOutputBuffer[queId]->payload;

        if ((Bool)TRUE == IssM2mIspLink_isWdrMode(operatingMode))
        {
            /* H3A Output is enabled only for the second pass */
            if (passId == ISSM2MISP_LINK_SECOND_PASS)
            {
                enableOut[queId] = (Bool)TRUE;
                /* Use 0th index buffer for the H3A output,
                   since that's index AEWB algorithm uses */
                outputFrame[queId].addr[0][0] = pH3aOutFrame->bufAddr[0U];
                outFrmList.frames[VPS_ISS_STREAM_ID_AEWB] = &outputFrame[queId];
            }
        }
        else
        {
            enableOut[queId] = (Bool)TRUE;
            outputFrame[queId].addr[0][0] = pH3aOutFrame->bufAddr[passId];
            outFrmList.frames[VPS_ISS_STREAM_ID_AEWB] = &outputFrame[queId];
        }
    }

    queId = ISSM2MISP_LINK_OUTPUTQUE_H3A_AF;
    if(pOutputBuffer[queId])
    {
        pH3aOutFrame
        = (System_MetaDataBuffer*)
        pOutputBuffer[queId]->payload;

        if ((Bool)TRUE == IssM2mIspLink_isWdrMode(operatingMode))
        {
            /* H3A Output is enabled only for the second pass to get statistics for short-expusre frame*/
            if (passId == ISSM2MISP_LINK_SECOND_PASS)
            {
                enableOut[queId] = (Bool)TRUE;
                outputFrame[queId].addr[0][0] = pH3aOutFrame->bufAddr[0U];
                outFrmList.frames[VPS_ISS_STREAM_ID_AF] = &outputFrame[queId];
            }
        }
        else
        {
            enableOut[queId] = (Bool)TRUE;
            outputFrame[queId].addr[0][0] = pH3aOutFrame->bufAddr[passId];
            outFrmList.frames[VPS_ISS_STREAM_ID_AF] = &outputFrame[queId];
        }

    }

    /* Change offset of the current input frame for
       the line interleaved WDR mode */
    if ((IssM2mIspLink_OperatingMode)ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED == operatingMode)
    {
        UInt32 addr;
        System_LinkChInfo *pPrevLinkChInfo;
        IssM2mIspLink_WdrOffsetParams_t *wdrOffsetPrms =
                &pObj->createArgs.channelParams[chId].wdrOffsetPrms;

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004 Rule 11.3
         * Cast between a pointer and an integral type
         * MISRAC_WAIVER:
         * For the line interleaved mode, typecasting buffer pointer to uint
         * to move buffer pointer to the exact location of the short/long
         & exposures.
         */
        addr =
                (UInt32)inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0]->addr[0][0];
        pPrevLinkChInfo = &pObj->inQueInfo.chInfo[chId];

        /* First pass is for the long channel */
        if (passId == ISSM2MISP_LINK_SECOND_PASS)
        {
            addr = addr + (wdrOffsetPrms->longLineOffset * pPrevLinkChInfo->pitch[0U]);
            addr = addr + wdrOffsetPrms->longPixelOffset;
        }
        else /* Second pass is for the short channel */
        {
            addr = addr + (wdrOffsetPrms->shortLineOffset * pPrevLinkChInfo->pitch[0U]);
            addr = addr + wdrOffsetPrms->shortPixelOffset;
        }

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004 Rule 11.3
         * Cast between a pointer and an integral type
         * MISRAC_WAIVER:
         * Typecasting buffer offset from int to pointer, offset is
         * location of the long/short exposure within captured buffer
         */
        inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0]->addr[0][0] = (Ptr)addr;
    }

#ifdef _DEBUG_PRC_FRM_
    debug_proces_frame(pVideoOutFrameRszA, pVideoOutFrameRszB, pH3aOutFrame);
#endif

    IssM2mIspLink_drvApplyConfig (pObj, chId, passId, enableOut);

    status = IssM2mIspLink_drvRestoreContext(pObj, chId, passId, enableOut);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    if(((Bool)TRUE == IssM2mIspLink_isWdrMode(operatingMode)) &&
            (passId == ISSM2MISP_LINK_FIRST_PASS))
    {
        intermedFrame.addr[0][0] = pObj->pIntermediateBufAddr;

        outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_B] = NULL;
        outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A] = &intermedFrame;
    }
    if(((Bool)TRUE == IssM2mIspLink_isWdrMode(operatingMode)) &&
            (passId == ISSM2MISP_LINK_SECOND_PASS))
    {
        intermedFrame.addr[0][0] = pObj->pIntermediateBufAddr;
        inFrmList.frames[VPS_ISS_STREAM_ID_INPUT_N1] = &intermedFrame;
    }

    inFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;
    outFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

    /*
     * Submit Processing Request to the driver, wait on a semaphore and
     * get processed frame
     */
    status = Fvid2_processRequest(
            pObj->chObj[chId].passCfg[passId].drvHandle,
            &inFrmList,
            &outFrmList);
    UTILS_assert(status==0);

    BspOsal_semWait(pObj->semProcessCall, BSP_OSAL_WAIT_FOREVER);

    status = Fvid2_getProcessedRequest(
            pObj->chObj[chId].passCfg[passId].drvHandle,
            &inFrmList,
            &outFrmList,
            FVID2_TIMEOUT_NONE);
    UTILS_assert(status==0);

    status = IssM2mIspLink_drvSaveContext(pObj, chId, passId, enableOut);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Update AE and AWB results in ISP
 *
 * This function gets called in response to
 *  ISSM2MISP_LINK_CMD_SET_AEWB_PARAMS command.
 *
 * \param  pObj           [IN] Capture link global handle
 * \param  pParams        [IN] Structure containing results of AE and AWB
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mIspLink_drvUpdateAwbResults(
        IssM2mIspLink_Obj *pObj,
        Void *pParams)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i, chId;
    IssM2mIspLink_ChannelObject *pChObj;
    IssM2mIspLink_PassObj *pPassCfg;
    IssAewbAlgOutParams *pAlgOut = (Void *)pParams;
    UInt32 idx;

    UTILS_assert(NULL != pAlgOut);
    UTILS_assert(NULL != pParams);

    chId = pAlgOut->channelId;
    UTILS_assert(chId < ISSM2MISP_LINK_MAX_CH);

    pChObj = &pObj->chObj[chId];
    if ((Bool)TRUE ==
            IssM2mIspLink_isWdrMode(pObj->createArgs.channelParams[chId].
                    operatingMode))
    {
        /* Use Second pass for the 20Bit WDR case*/
        pPassCfg = &pChObj->passCfg[ISSM2MISP_LINK_SECOND_PASS];
    }
    else
    {
        /* Use First Pass parameters for the 12bit linear mode */
        pPassCfg = &pChObj->passCfg[ISSM2MISP_LINK_FIRST_PASS];
    }

    /* Assuming output params index has all the output parameters
       from the Algorithm, Need to change this when H3a data from
       the passes of WDR are used */
    for(i = 0; i < FVID2_BAYER_COLOR_COMP_MAX; i ++)
    {
        /* Digital Gain is used in the ISIF */
        if ((pAlgOut->outPrms[0U].useAeCfg != 0U) &&
            (ISSM2MISP_LINK_OPMODE_1PASS_WDR != pObj->createArgs.channelParams[chId].operatingMode))
        {
            pPassCfg->isifWbCfg.gain[i] = pAlgOut->outPrms[0U].digitalGain;
        }

        if (pAlgOut->outPrms[0U].useWbCfg)
        {
            /* For 20BIT WDR Mode, apply White balance parameters
               in the IPIPEIF */
            if ((Bool)TRUE == IssM2mIspLink_isWdrMode(pObj->createArgs.
                    channelParams[chId].operatingMode))
            {
                idx = Fvid2_BayerColorIndex(
                        pPassCfg->ispPrms.inFmt.dataFormat, i);
                pPassCfg->wdrCfg.lwb[idx] = pAlgOut->outPrms[0U].gain[i] * 4u;
                pPassCfg->wdrCfg.swb[idx] = pAlgOut->outPrms[0U].gain[i] * 4u;
            }
            else /* For normal 12bit linear mode, apply white balance
                    parameters in IPIPE */
            {
                /* Multiplying by 4 since for New AWB algorithm,
                   unity is 128 whereas for IPIPE, unity gain is 512. */
                pPassCfg->ipipeWbCfg.gain[i] = pAlgOut->outPrms[0U].gain[i] * 4U;
            }
        }
    }

    /* Copy ISP Configuration, this also update the DCC multi-photo-space
       parameters */
    issMemIspLinkCopyIspConfig(&pChObj->ispCfgParams, &pAlgOut->ispCfg);

    /* Copy AEWB RGB2RGB params in the Pass config as pass config is set
       for every channel for every path */
    if (NULL != pAlgOut->ispCfg.rgb2rgb1Cfg)
    {
        pPassCfg->rgb2rgb1 = *pAlgOut->ispCfg.rgb2rgb1Cfg;
    }
    if (NULL != pAlgOut->ispCfg.rgb2rgb2Cfg)
    {
        pPassCfg->rgb2rgb2 = *pAlgOut->ispCfg.rgb2rgb2Cfg;
    }

    if ((Bool)TRUE == IssM2mIspLink_isWdrMode(
            pObj->createArgs.channelParams[chId].operatingMode))
    {
        memcpy(&pChObj->passCfg[ISSM2MISP_LINK_FIRST_PASS].isifWbCfg,
                &pPassCfg->isifWbCfg,
                sizeof(vpsissIsifGainOfstConfig_t));
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Update WDR Merge parameters based on exposure ratio
 *
 * This function gets called in response to
 *  ISSM2MISP_LINK_CMD_SET_WDR_MERGE_PARAMS command.
 *
 * \param  pObj           [IN] Capture link global handle
 * \param  pParams        [IN] Structure containing Exposure Ratio
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mIspLink_drvUpdateWdrMergeParams(
        IssM2mIspLink_Obj *pObj,
        Void *pParams)
{
    IssM2mIspLink_PassObj *pPassCfg = NULL;
    IssAewbAlgOutParams *pAlgOut = (Void *)pParams;
    UInt32 evRatio, chId;
    System_BitsPerPixel inBpp;
    UInt32 mergeWidth, bitWidth = 0U, wtDsf, wdrClip, cfg4Dst, wdrThrThr;
    vpsissIpipeifSaturaInsts_t *satCfg;
    vpsissIpipeifWdrCfg_t      *wdrConfig;
    vpsissIpipeifDeCompandInsts_t *compDecompCfg;
    Int32 dcOffset;

    UTILS_assert(NULL != pAlgOut);
    UTILS_assert(NULL != pParams);

    chId = pAlgOut->channelId;
    UTILS_assert(chId < ISSM2MISP_LINK_MAX_CH);

    /* Supported only when WDR Merge is enabled */
    if ((Bool)TRUE == IssM2mIspLink_isWdrMode(pObj->createArgs.
            channelParams[chId].operatingMode))
    {
        /* Calculate EV Ratio from Exposure ratio
           evRatio = log2(exposureRatio) */

        /* When dgain is applied only to long after split, there is a
            different ratio for split and merge */
        UInt32 exposureRatio_merge =
                (UInt32) ((pAlgOut->exposureRatio*pAlgOut->outPrms[0].digitalGain) / 512);
        UInt32 evRatio_merge = (UInt32)issM2mIspLinkCalculateEvRatio(
                exposureRatio_merge);

        evRatio = issM2mIspLinkCalculateEvRatio(pAlgOut->exposureRatio);

        pObj->chObj[chId].expRatio = pAlgOut->exposureRatio;
        pObj->chObj[chId].evRatio = evRatio;

        pPassCfg = &pObj->chObj[chId].passCfg[ISSM2MISP_LINK_FIRST_PASS];
        inBpp =(System_BitsPerPixel) pPassCfg->ispPrms.inFmt.bpp;

        /* by default assume 12-bits */
        if ((inBpp == SYSTEM_BPP_BITS12)||
            (inBpp == SYSTEM_BPP_BITS12_PACKED_MIPI))
        {
            bitWidth = 12U;
        }
        else if(inBpp == SYSTEM_BPP_BITS10)
        {
            bitWidth = 10U;
        }
        else if(inBpp == SYSTEM_BPP_BITS14)
        {
            bitWidth = 14U;
        }
        else
        {
            UTILS_assert((Bool)0);
        }

        /* Change Saturation configuration in the first pass configuration  */
        pPassCfg = &pObj->chObj[chId].passCfg[ISSM2MISP_LINK_FIRST_PASS];
        satCfg = &pPassCfg->satCfg;

        satCfg->modInstId = VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_VCOMP;
        satCfg->vportSatCfg.sat = (UInt32)
                    ((issM2mIspLinkPower2(bitWidth) - 1U) * pAlgOut->exposureRatio);
        satCfg->vportSatCfg.dsf = (UInt32)evRatio;

        /* Change Saturation and merge configuration in second pass
           configuration */
        pPassCfg = &pObj->chObj[chId].passCfg[ISSM2MISP_LINK_SECOND_PASS];
        satCfg = &pPassCfg->satCfg;
        wdrConfig = &pPassCfg->wdrCfg;
        compDecompCfg = &pPassCfg->compDecompCfg;

        satCfg->modInstId = VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_VCOMP;
        satCfg->vportSatCfg.sat = (UInt32)(issM2mIspLinkPower2(bitWidth) - 1U);
        satCfg->vportSatCfg.dsf = (UInt32)0;

        compDecompCfg->modInstId =
                VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_WDR_COMP;

        mergeWidth = bitWidth + evRatio_merge;
        if (mergeWidth > (UInt32)16U)
        {
            compDecompCfg->compandCfg.enable = (UInt32)TRUE;
            compDecompCfg->compandCfg.size = mergeWidth - 9U;

            wtDsf = mergeWidth - 16U;
            cfg4Dst = 15U;

            wdrClip = issM2mIspLinkPower2(mergeWidth) - 1U;
        }
        else
        {
            /* Post merge companding is not required since total
               bitsize is less than or equal to 16 bits*/
            compDecompCfg->compandCfg.enable = (UInt32)FALSE;
            wtDsf = 0U;
            cfg4Dst = mergeWidth - 1u;
            wdrClip = 65535U;
        }

        /* Always enable  companding for smoother transition between
           different lighting conditions */
        compDecompCfg->compandCfg.enable = (UInt32)TRUE;
        compDecompCfg->compandCfg.size = mergeWidth - 9U;

        /* Reconfigure WDR Merge parameters */
        wdrConfig->dst = cfg4Dst;
        wdrConfig->lbit = mergeWidth - bitWidth;
        wdrConfig->sbit = wdrConfig->lbit;

        wdrConfig->gshort = 32768U;
        wdrConfig->glong = wdrConfig->gshort/exposureRatio_merge;
        dcOffset = pPassCfg->isifBlkClampCfg.dcOffset;

        {
            UInt64 temp64 =  (UInt64)1U;
            temp64 =  (UInt64)((temp64<<bitWidth) - 1U);
            temp64 =  (UInt64)(temp64 * (UInt64)ISSM2MISP_LINK_THRESHOLD_PERCENTAGE);
            temp64 =  (UInt64)(temp64 * wdrConfig->glong);
            wdrThrThr = (UInt32)(temp64 >> (31U - wdrConfig->lbit));
        }

        {
            Int32 temp32 = (Int32)wdrThrThr;
            temp32 += (dcOffset*2);
            if(temp32 < 0)
            {
                temp32 = 0;
            }
            wdrThrThr = (UInt32)temp32;
        }
        wdrThrThr = wdrThrThr >> wtDsf;

        wdrConfig->mergeShift = wtDsf;
        wdrConfig->mergeClip = wdrClip;

        wdrConfig->afe =0U;
        wdrConfig->afm = 0U;
        wdrConfig->bf = 0U;
        wdrConfig->wgt_sel = 1;
        wdrConfig->thr = wdrThrThr;
        if (ISSM2MISP_LINK_OPMODE_2PASS_WDR ==
                pObj->createArgs.channelParams[chId].operatingMode)
        {
            /* Recalculate the dcOffset */
            Int32 tempS32;
            tempS32 =(Int32)(dcOffset * -(Int32)1);
            dcOffset = (Int32) ( (Int32)tempS32/(Int32)pAlgOut->exposureRatio);
            dcOffset = (Int32)(dcOffset * -(Int32)1);
            pObj->chObj[chId].passCfg[ISSM2MISP_LINK_FIRST_PASS].
            isifBlkClampCfg.dcOffset = (UInt32)dcOffset;
        }
        else /* For Line Interleaved mode, dc offset is same for
                both the passes */
        {
            pObj->chObj[chId].passCfg[ISSM2MISP_LINK_FIRST_PASS].
            isifBlkClampCfg.dcOffset = dcOffset;
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Process the new input data
 *
 * This function gets called in response to SYSTEM_CMD_NEW_DATA command from
 * previous link.
 *
 * \param  pObj           [IN] Capture link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mIspLink_drvProcessData(IssM2mIspLink_Obj * pObj)
{
    UInt32 bufId;
    System_LinkInQueParams *pInQueParams;
    System_BufferList bufList;
    Int32 status;
    UInt32 chId, queId;
    System_Buffer *pInputBuffer;
    System_Buffer *pOutputBuffer[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM];
    IssM2mIspLink_ChannelParams *pChParams;
    Bool sendCmdToNextLink[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM] = { FALSE };
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    if(pObj->isFirstFrameRecv==FALSE)
    {
        pObj->isFirstFrameRecv = (Bool)TRUE;

        Utils_resetLinkStatistics(
                &linkStatsInfo->linkStats,
                pObj->inQueInfo.numCh,
                ISSM2MISP_LINK_OUTPUTQUE_MAXNUM);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    pInQueParams = &pObj->createArgs.inQueParams
            [ISSM2MISP_LINK_INPUTQUE_RAW_IMAGE];

    System_getLinksFullBuffers(pInQueParams->prevLinkId,
            pInQueParams->prevLinkQueId, &bufList);

    if (bufList.numBuf)
    {
        for (bufId = 0; bufId < bufList.numBuf; bufId++)
        {
            pInputBuffer = bufList.buffers[bufId];

            chId = pInputBuffer->chNum;

            /*
             * Checks on sanity of input buffer
             */
            if (chId >= pObj->inQueInfo.numCh)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
            }
            else
            {

                linkStatsInfo->linkStats.chStats[chId].inBufRecvCount++;

                pChParams = &pObj->createArgs.channelParams[chId];

                /*
                 * Fetch empty output buffer for image and H3A
                 */
                for( queId = 0U;
                        queId < ISSM2MISP_LINK_OUTPUTQUE_MAXNUM;
                        queId++
                )
                {
                    pOutputBuffer[queId] = NULL;

                    if(pChParams->enableOut[queId])
                    {
                        /* MISRA.CAST.PTR:MISRAC_2004 Rule_11.4
                       MISRAC_WAIVER:
                       Generic implementation of queue expects data in Ptr* type,
                       so typecasted it to Ptr *. */
                        Utils_queGet(&pObj->linkOutObj[queId].emptyBufQue[chId],
                                (Ptr *) & pOutputBuffer[queId],
                                (UInt32)1U,
                                (UInt32)BSP_OSAL_NO_WAIT);
                    }
                    if(pOutputBuffer[queId])
                    {
                        pOutputBuffer[queId]->srcTimestamp
                        = pInputBuffer->srcTimestamp;
                    pOutputBuffer[queId]->frameId
                        = pInputBuffer->frameId;
                    pOutputBuffer[queId]->linkLocalTimestamp
                        = Utils_getCurGlobalTimeInUsec();
                    }
                }

                if( (pOutputBuffer[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A] != NULL)
                        ||
                        (pOutputBuffer[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] != NULL)
                )
                {

                    Utils_pendIspLock();

                    /*
                     * Reaching here means an error free input and empty output buffers
                     * are available
                     */
                    IssM2mIspLink_drvProcessFrame(pObj,
                            pInputBuffer,
                            pOutputBuffer,
                            ISSM2MISP_LINK_FIRST_PASS);

                    /*
                     * Attempt second pass, only if first pass is successful
                     */
                    if((Bool)TRUE == IssM2mIspLink_isWdrMode(pChParams->operatingMode))
                    {
                        IssM2mIspLink_drvProcessFrame(pObj,
                                pInputBuffer,
                                pOutputBuffer,
                                ISSM2MISP_LINK_SECOND_PASS);
                    }

                    Utils_postIspLock();

                    linkStatsInfo->linkStats.chStats[chId].inBufProcessCount++;

                    for( queId = 0;
                            queId < ISSM2MISP_LINK_OUTPUTQUE_MAXNUM;
                            queId++
                    )
                    {
                        if(pOutputBuffer[queId])
                        {
                            Utils_updateLatency(
                                    &linkStatsInfo->linkLatency,
                                    pOutputBuffer[queId]->linkLocalTimestamp);
                            Utils_updateLatency(
                                    &linkStatsInfo->srcToLinkLatency,
                                    pOutputBuffer[queId]->srcTimestamp);

                            sendCmdToNextLink[queId] = (Bool)TRUE;

                            linkStatsInfo->linkStats.chStats[chId].
                            outBufCount[queId]++;

                            status = Utils_quePut(
                                    &pObj->linkOutObj[queId].fullBufQue,
                                    (Ptr)pOutputBuffer[queId],
                                    (UInt32)BSP_OSAL_NO_WAIT);
                            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                        }
                        else
                        {
                            linkStatsInfo->linkStats.chStats[chId].
                            outBufDropCount[queId]++;
                        }
                    }

                    if (pObj->saveFrame)
                    {
                        issMemIspLinkSaveFrame(pObj, chId, pOutputBuffer);
                    }
                }
                else
                {
                    linkStatsInfo->linkStats.chStats[chId].inBufDropCount++;

                    /* drop the frames */
                    for( queId = 0;
                            queId < ISSM2MISP_LINK_OUTPUTQUE_MAXNUM;
                            queId++
                    )
                    {
                        if(pOutputBuffer[queId])
                        {
                            status = Utils_quePut(
                                    &pObj->linkOutObj[queId].emptyBufQue[chId],
                                    (Ptr)pOutputBuffer[queId],
                                    (UInt32)BSP_OSAL_NO_WAIT);
                            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                        }
                        linkStatsInfo->linkStats.chStats[chId].
                        outBufDropCount[queId]++;
                    }
                }
            }
        }

        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                pInQueParams->prevLinkQueId,
                &bufList);

    }

    /*
     * Send command to next link for putting the buffer in output queue of the buffer
     */
    for(queId=0 ; queId<ISSM2MISP_LINK_OUTPUTQUE_MAXNUM ; queId++)
    {
        if(sendCmdToNextLink[queId])
        {
            System_sendLinkCmd(pObj->createArgs.outQueParams[queId].nextLink,
                    SYSTEM_CMD_NEW_DATA,
                    NULL);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief API for setting ISP parameters for the link.
 *
 *  In this function, configuration provided by the use case is just recorded
 *  inside the link. Providing this to driver happens before process call.
 *
 * \param  pObj        [IN] Link global handle
 * \param  pCfgPrm     [IN] ISP configuration parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mIspLink_drvSetIspConfig(IssM2mIspLink_Obj                 * pObj,
        const IssIspConfigurationParameters *pCfgPrm,
        UInt32                              isDccSetCfg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(pCfgPrm->channelId < ISSM2MISP_LINK_MAX_CH);
    if(pCfgPrm->channelId < pObj->linkInfo.queInfo[0].numCh)
    {
        issMemIspLinkCopyIspConfig(
                &pObj->chObj[pCfgPrm->channelId].ispCfgParams,
                pCfgPrm);
    }
    else
    {
        Vps_printf("ISS M2M Isp Link: Incorrect Channel Id\n");
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;
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
Int32 IssM2mIspLink_drvPrintStatus(const IssM2mIspLink_Obj * pObj)
{
    UTILS_assert(NULL != pObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats, "ISSM2MISP", (Bool)TRUE);

    Utils_printLatency("ISSM2MISP",
            &pObj->linkStatsInfo->linkLatency,
            &pObj->linkStatsInfo->srcToLinkLatency,
            (Bool)TRUE);

    return 0;
}

/* Function to calculate EV Ratio from exposure ratio,
   evRatio = log2(exposureRatio)
   No check are done in this function. */
static UInt32 issM2mIspLinkCalculateEvRatio(UInt32 exposureRatio)
{
    UInt32 i = 0U;
    UInt32 cnt = 1U;
    UInt32 evRatio = 0U;

    while (1u)
    {
        if (exposureRatio <= cnt)
        {
            evRatio = i;
            break;
        }

        i ++;
        cnt = cnt * 2U;
    }

    return (evRatio);
}

/* Function to calculate power2 of a given value,
   No check are done in this function. */
static UInt32 issM2mIspLinkPower2(UInt32 k)
{
    UInt32 i;
    UInt32 t = (UInt32)1U;
    for (i = 0; i < k; i ++)
    {
        t = t<<1;
    }

    return (t);
}

/* Function to copy ISP configuration from one source to another.
 * It makes sure that the null pointer is not copied to non null source
 * pointer.
 */
static Void issMemIspLinkCopyIspConfig(
        IssIspConfigurationParameters *pIspCfgTar,
        const IssIspConfigurationParameters *pIspCfgSrc)
{
    UTILS_assert(NULL != pIspCfgTar);
    UTILS_assert(NULL != pIspCfgSrc);

    if (!((NULL != pIspCfgTar->cnfCfg) && (NULL == pIspCfgSrc->cnfCfg)))
    {
        pIspCfgTar->cnfCfg = pIspCfgSrc->cnfCfg;
    }
    if (!((NULL != pIspCfgTar->glbceCfg) && (NULL == pIspCfgSrc->glbceCfg)))
    {
        pIspCfgTar->glbceCfg = pIspCfgSrc->glbceCfg;
    }
    if (!((NULL != pIspCfgTar->glbceFwdPerCfg) &&
            (NULL == pIspCfgSrc->glbceFwdPerCfg)))
    {
        pIspCfgTar->glbceFwdPerCfg = pIspCfgSrc->glbceFwdPerCfg;
    }
    if (!((NULL != pIspCfgTar->glbceRevPerCfg) &&
            (NULL == pIspCfgSrc->glbceRevPerCfg)))
    {
        pIspCfgTar->glbceRevPerCfg = pIspCfgSrc->glbceRevPerCfg;
    }
    if (!((NULL != pIspCfgTar->glbceWdrCfg) &&
            (NULL == pIspCfgSrc->glbceWdrCfg)))
    {
        pIspCfgTar->glbceWdrCfg = pIspCfgSrc->glbceWdrCfg;
    }
    if (!((NULL != pIspCfgTar->afCfg) && (NULL == pIspCfgSrc->afCfg)))
    {
        pIspCfgTar->afCfg = pIspCfgSrc->afCfg;
    }
    if (!((NULL != pIspCfgTar->aewbCfg) && (NULL == pIspCfgSrc->aewbCfg)))
    {
        pIspCfgTar->aewbCfg = pIspCfgSrc->aewbCfg;
    }

    if (!((NULL != pIspCfgTar->ipipeInputCfg) &&
            (NULL == pIspCfgSrc->ipipeInputCfg)))
    {
        pIspCfgTar->ipipeInputCfg = pIspCfgSrc->ipipeInputCfg;
    }
    if (!((NULL != pIspCfgTar->yuvPhsCfg) && (NULL == pIspCfgSrc->yuvPhsCfg)))
    {
        pIspCfgTar->yuvPhsCfg = pIspCfgSrc->yuvPhsCfg;
    }
    if (!((NULL != pIspCfgTar->rgb2rgb1Cfg) &&
            (NULL == pIspCfgSrc->rgb2rgb1Cfg)))
    {
        pIspCfgTar->rgb2rgb1Cfg = pIspCfgSrc->rgb2rgb1Cfg;
    }
    if (!((NULL != pIspCfgTar->rgb2rgb2Cfg) &&
            (NULL == pIspCfgSrc->rgb2rgb2Cfg)))
    {
        pIspCfgTar->rgb2rgb2Cfg = pIspCfgSrc->rgb2rgb2Cfg;
    }
    if (!((NULL != pIspCfgTar->rgb2yuvCfg) && (NULL == pIspCfgSrc->rgb2yuvCfg)))
    {
        pIspCfgTar->rgb2yuvCfg = pIspCfgSrc->rgb2yuvCfg;
    }
    if (!((NULL != pIspCfgTar->wbCfg) && (NULL == pIspCfgSrc->wbCfg)))
    {
        pIspCfgTar->wbCfg = pIspCfgSrc->wbCfg;
    }
    if (!((NULL != pIspCfgTar->cfaCfg) && (NULL == pIspCfgSrc->cfaCfg)))
    {
        pIspCfgTar->cfaCfg = pIspCfgSrc->cfaCfg;
    }
    if (!((NULL != pIspCfgTar->dpcOtfCfg) && (NULL == pIspCfgSrc->dpcOtfCfg)))
    {
        pIspCfgTar->dpcOtfCfg = pIspCfgSrc->dpcOtfCfg;
    }
    if (!((NULL != pIspCfgTar->dpcLutCfg) && (NULL == pIspCfgSrc->dpcLutCfg)))
    {
        pIspCfgTar->dpcLutCfg = pIspCfgSrc->dpcLutCfg;
    }
    if (!((NULL != pIspCfgTar->gammaCfg) && (NULL == pIspCfgSrc->gammaCfg)))
    {
        pIspCfgTar->gammaCfg = pIspCfgSrc->gammaCfg;
    }
    if (!((NULL != pIspCfgTar->lut3d) && (NULL == pIspCfgSrc->lut3d)))
    {
        pIspCfgTar->lut3d = pIspCfgSrc->lut3d;
        pIspCfgTar->ipipe3dLutFormat = pIspCfgSrc->ipipe3dLutFormat;
    }
    if (!((NULL != pIspCfgTar->eeCfg) && (NULL == pIspCfgSrc->eeCfg)))
    {
        pIspCfgTar->eeCfg = pIspCfgSrc->eeCfg;
    }
    if (!((NULL != pIspCfgTar->gicCfg) && (NULL == pIspCfgSrc->gicCfg)))
    {
        pIspCfgTar->gicCfg = pIspCfgSrc->gicCfg;
    }
    if (!((NULL != pIspCfgTar->lscCfg) && (NULL == pIspCfgSrc->lscCfg)))
    {
        pIspCfgTar->lscCfg = pIspCfgSrc->lscCfg;
    }
    if (!((NULL != pIspCfgTar->nf1Cfg) && (NULL == pIspCfgSrc->nf1Cfg)))
    {
        pIspCfgTar->nf1Cfg = pIspCfgSrc->nf1Cfg;
    }
    if (!((NULL != pIspCfgTar->nf2Cfg) && (NULL == pIspCfgSrc->nf2Cfg)))
    {
        pIspCfgTar->nf2Cfg = pIspCfgSrc->nf2Cfg;
    }
    if (!((NULL != pIspCfgTar->ipipeifLut) && (NULL == pIspCfgSrc->ipipeifLut)))
    {
        pIspCfgTar->ipipeifLut = pIspCfgSrc->ipipeifLut;
    }
    if (!((NULL != pIspCfgTar->ipipeifWdrCfg) &&
            (NULL == pIspCfgSrc->ipipeifWdrCfg)))
    {
        pIspCfgTar->ipipeifWdrCfg = pIspCfgSrc->ipipeifWdrCfg;
    }
    if (!((NULL != pIspCfgTar->ipipeifCmpDecmpCfg) &&
            (NULL == pIspCfgSrc->ipipeifCmpDecmpCfg)))
    {
        pIspCfgTar->ipipeifCmpDecmpCfg = pIspCfgSrc->ipipeifCmpDecmpCfg;
    }
    if (!((NULL != pIspCfgTar->isifWbCfg) && (NULL == pIspCfgSrc->isifWbCfg)))
    {
        pIspCfgTar->isifWbCfg = pIspCfgSrc->isifWbCfg;
    }
    if (!((NULL != pIspCfgTar->isif2DLscCfg) &&
            (NULL == pIspCfgSrc->isif2DLscCfg)))
    {
        pIspCfgTar->isif2DLscCfg = pIspCfgSrc->isif2DLscCfg;
    }
    if (!((NULL != pIspCfgTar->isifBlkClampCfg) &&
            (NULL == pIspCfgSrc->isifBlkClampCfg)))
    {
        pIspCfgTar->isifBlkClampCfg = pIspCfgSrc->isifBlkClampCfg;
    }
    if (!((NULL != pIspCfgTar->nsf3vCfg) && (NULL == pIspCfgSrc->nsf3vCfg)))
    {
        pIspCfgTar->nsf3vCfg = pIspCfgSrc->nsf3vCfg;
    }
}

static Void issMemIspLinkSaveFrame(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    System_Buffer     *pOutputBuffer[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status;
    UInt32 bufSize;
    System_VideoFrameBuffer *pVideoOutFrameRszA;
    Utils_DmaCopyFill2D dmaPrm;
    Fvid2_Format *fmt;

    if(chId == pObj->saveFrameChId)
    {
        pVideoOutFrameRszA
            = (System_VideoFrameBuffer*)
            pOutputBuffer[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A]->payload;

        fmt = &pObj->chObj[chId].passCfg[ISSM2MISP_LINK_FIRST_PASS].
            rszCfg.instCfg[0].outFmt;

        if (((Bool)TRUE == IssM2mIspLink_isWdrMode(
            pObj->createArgs.channelParams[chId].operatingMode)) &&
            (pObj->chObj[chId].outputTapModule !=
                    ISSM2MISP_LINK_ISP_TAP_INTERMED_OUTPUT))
        {
            /* Get the Format from the last pass */
            fmt = &pObj->chObj[chId].passCfg[ISSM2MISP_LINK_MAXNUM_PASS - 1U].
                rszCfg.instCfg[0].outFmt;
        }

        if (TRUE == pObj->createArgs.allocBufferForDump)
        {
            if (pObj->chObj[chId].outputTapModule ==
                    ISSM2MISP_LINK_ISP_TAP_RESIZER_OUTPUT)
            {
                dmaPrm.dataFormat = fmt->dataFormat;
            }
            else
            {
                dmaPrm.dataFormat = SYSTEM_DF_RAW16;
            }

            if (pObj->chObj[chId].outputTapModule ==
                    ISSM2MISP_LINK_ISP_TAP_INTERMED_OUTPUT)
            {
                dmaPrm.srcAddr[0]   = pObj->pIntermediateBufAddr;

                dmaPrm.destAddr[0]  = pObj->saveFrameBufAddr;

                /* MISRA.PTR.ARITH
                 * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                 * MISRAC_WAIVER:
                 * Pointer is added with the chroma offset to get the chroma
                 * buffer location.
                 * saveFrameBufAddr is checked agains null at alloc time
                 */
                dmaPrm.destAddr[1]  = pObj->saveFrameBufAddr +
                                        (fmt->pitch[0] * fmt->height);
                dmaPrm.destPitch[0] = fmt->width * 2U;
                dmaPrm.destPitch[1] = fmt->width * 2U;
                dmaPrm.destStartX   = 0;
                dmaPrm.destStartY   = 0;
                dmaPrm.width        = fmt->width;
                dmaPrm.height       = fmt->height;
                dmaPrm.srcPitch[0]  = fmt->width * 2U;
                dmaPrm.srcPitch[1]  = fmt->width * 2U;
                dmaPrm.srcStartX    = 0;
                dmaPrm.srcStartY    = 0;

                pObj->saveFramePlaneSize[0] =
                            dmaPrm.destPitch[0] * dmaPrm.height;
            }
            else
            {
                dmaPrm.srcAddr[0]   = pVideoOutFrameRszA->bufAddr[0];
                dmaPrm.srcAddr[1]   = pVideoOutFrameRszA->bufAddr[1];

                dmaPrm.destAddr[0]  = pObj->saveFrameBufAddr;

                /* MISRA.PTR.ARITH
                 * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                 * MISRAC_WAIVER:
                 * Pointer is added with the chroma offset to get the chroma
                 * buffer location.
                 * saveFrameBufAddr is checked agains null at alloc time
                 */
                dmaPrm.destAddr[1]  = pObj->saveFrameBufAddr +
                                        (fmt->pitch[0] * fmt->height);
                dmaPrm.destPitch[0] = fmt->pitch[0];
                dmaPrm.destPitch[1] = fmt->pitch[1];
                dmaPrm.destStartX   = 0;
                dmaPrm.destStartY   = 0;
                dmaPrm.width        = fmt->width;
                dmaPrm.height       = fmt->height;
                dmaPrm.srcPitch[0]  = fmt->pitch[0];
                dmaPrm.srcPitch[1]  = fmt->pitch[1];
                dmaPrm.srcStartX    = 0;
                dmaPrm.srcStartY    = 0;

                pObj->saveFramePlaneSize[0] =
                                dmaPrm.destPitch[0] * dmaPrm.height;
                pObj->saveFramePlaneSize[1] =
                                dmaPrm.destPitch[1] * (dmaPrm.height >> 1U);
            }

            pObj->saveFramePlaneAddr[0] = dmaPrm.destAddr[0];
            pObj->saveFramePlaneAddr[1] = dmaPrm.destAddr[1];

            status = Utils_dmaCopy2D(&pObj->dumpFramesDmaObj, &dmaPrm, 1U);
            UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

            /* Reset the flag */
            pObj->saveFrame = FALSE;

            Vps_printf(" **************************************************** \n");
            Vps_printf(" ####### Save Frame from location 0x%x ####### \n",
                pObj->saveFrameBufAddr);
            if (SYSTEM_DF_YUV420SP_UV == dmaPrm.dataFormat)
            {
                bufSize = (fmt->pitch[0]*fmt->height) +
                    ((fmt->pitch[1]*fmt->height) / 2U);
            }
            else
            {
                if (pObj->chObj[chId].outputTapModule ==
                    ISSM2MISP_LINK_ISP_TAP_INTERMED_OUTPUT)
                {
                    bufSize = fmt->width*fmt->height*2U;
                }
                else
                {
                    bufSize = fmt->pitch[0]*fmt->height;
                }

            }
            Vps_printf(" saveRaw(0, 0x%x, filename, %d, 32, false); ",
                pObj->saveFrameBufAddr,
                bufSize / 4U);
            Vps_printf(" **************************************************** \n");
        }
    }
}

