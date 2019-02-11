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
 * \file issResizer_drvIss.c
 *
 * \brief  This file has the implementation of ISS Resizer Link which uses ISS
 *         sub system as the processing core.
 *
 *   ISS Resizer Link can be used to do processing on video input frames. These
 *   frames may be from capture or decoded video frames coming over network.
 *
 *   ISS Resizer Link (Using ISS) can do
 *   - Color space conversion on input frames (422I -> 420SP)
 *   - Resizing of input frames
 *
 *     The ISS Resizer link receives the input frames, submits them into
 *     ISS driver along with a output frame to which the ISS driver
 *     writes the output. once the processing is over
 *     the driver invoke a call back. On call back ISS Resizer Link reclaim these
 *     frames which are already processed and send back to the previous link.
 *     Also send out the output frames to the next link
 *
 *
 *     ISS Resizer link also supports the run time input and output resolution
 *     change - This feature is NOT verified in this version.
 *
 * \version 0.0 (Aug 2017) : [BJ] First version
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "issResizer_priv.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

Int32 IssRszLink_drvCreateIspPrms(IssRszLink_Obj *pObj, UInt32 chId);
Int32 IssRszLink_drvCreateRszCfgPrms(IssRszLink_Obj *pObj, UInt32 chId);
Int32 IssRszLink_drvCreateIpipeInputPrms(IssRszLink_Obj *pObj, UInt32 chId);
Int32 IssRszLink_drvSetChannelIssConfig(IssRszLink_Obj * pObj, UInt32 chId,
    System_Buffer *pOutputBuffer[ISSRSZ_LINK_OUTPUTQUE_MAXNUM]);

/**
 *******************************************************************************
 *
 * \brief This is the Call back function registered with resizer driver
 *
 *        This call back function will be invoked by resizer driver once it
 *        processed the frames from a FVID2_frame list
 *
 * \param  handle    [IN] resizer driver handle
 * \param  appData   [IN] Set with link instance handle address
 * \param  reserved  [IN] Not used
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssRszLink_drvFvidCb(FVID2_Handle handle, Ptr appData, Ptr reserved)
{
    IssRszLink_Obj *pObj = (IssRszLink_Obj *) appData;

    BspOsal_semPost(pObj->complete);

    pObj->linkStatsInfo->linkStats.notifyEventCount++;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This is the Error Call back function registered with ISS driver
 *
 *        This call back function will be invoked by driver once the
 *        processed frames from a FVID2_frame list are in error state
 *
 * \param  handle    [IN] ISS driver handle
 * \param  appData   [IN] Set with link instance handle address
 * \param  errList   [IN] Set with link instance handle address
 * \param  reserved  [IN] Not used
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssRszLink_drvFvidErrCb(FVID2_Handle handle,
                              Ptr appData, Ptr errList, Ptr reserved)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to create the isp params for given channel
 *
 * \param   pObj     [IN] ISS Resizer Link Instance handle
 * \param   chId     [IN] channel number
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssRszLink_drvCreateIspPrms(IssRszLink_Obj *pObj, UInt32 chId)
{
    IssRszLink_ChObj *pChObj;
    System_LinkChInfo *pInChInfo;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(chId < pObj->inQueInfo.numCh);
    pChObj = &pObj->chObj[chId];

    pInChInfo = &pObj->inQueInfo.chInfo[chId];

    /* Set the ISP Params */
    pChObj->drvIspPrms.inFmt.width         = pInChInfo->width;
    pChObj->drvIspPrms.inFmt.height        = pInChInfo->height;
    pChObj->drvIspPrms.inFmt.pitch[0U]     = pInChInfo->pitch[0];
    pChObj->drvIspPrms.inFmt.pitch[1U]     = pInChInfo->pitch[1];
    pChObj->drvIspPrms.inFmt.pitch[2U]     = pInChInfo->pitch[2];
    pChObj->drvIspPrms.inFmt.bpp           = SYSTEM_BPP_BITS16;
    pChObj->drvIspPrms.inFmt.dataFormat    =
        System_Link_Ch_Info_Get_Flag_Data_Format(pInChInfo->flags);
    /* N_1 frame settings are redundant */
    pChObj->drvIspPrms.inFmtN_1 = pChObj->drvIspPrms.inFmt;

    pChObj->drvIspPrms.enableWdrMerge            = FALSE;
    pChObj->drvIspPrms.enableVportCompInput      = FALSE;
    pChObj->drvIspPrms.enableDfs                 = FALSE;
    pChObj->drvIspPrms.glbcePath                 = VPS_ISS_GLBCE_PATH_DISABLED;
    pChObj->drvIspPrms.nsf3Path                  = VPS_ISS_NSF3_PATH_DISABLED;
    pChObj->drvIspPrms.enableDpcPreNsf3          = FALSE;
    pChObj->drvIspPrms.enableCnf                 = FALSE;
    pChObj->drvIspPrms.enableRszInputFromIpipeif = FALSE;

    pChObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_CAL_RD_INPUT_0] =
        (UInt32)TRUE;
    pChObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_A] = (UInt32)TRUE;
    pChObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_INPUT_N1] = (UInt32)FALSE;
    pChObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B] = (UInt32)FALSE;
    pChObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_AF] = (UInt32)FALSE;
    pChObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_AEWB] = (UInt32)FALSE;

    if((UInt32)TRUE == \
        pObj->createArgs.channelParams[chId].enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_B])
    {
        pChObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B] = (UInt32)TRUE;
    }

    pChObj->drvIspPrms.useWen = FALSE;
    pChObj->drvIspPrms.hdPol  = FVID2_POL_HIGH;
    pChObj->drvIspPrms.vdPol  = FVID2_POL_HIGH;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Function to create the resizer configuration parameters for given channel
 *
 * \param   pObj     [IN] ISS Resizer Link Instance handle
 * \param   chId     [IN] channel number
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssRszLink_drvCreateRszCfgPrms(IssRszLink_Obj * pObj, UInt32 chId)
{
    UInt32 cnt;
    IssRszLink_ChObj *pChObj;
    System_LinkChInfo *pInChInfo;
    System_LinkChInfo *pOutChInfo;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    vpsissRszCtrl_t rszCtrl;

    UTILS_assert(chId < pObj->inQueInfo.numCh);
    pChObj = &pObj->chObj[chId];

    pInChInfo  = &pObj->inQueInfo.chInfo[chId];

    memset(&rszCtrl, 0x0, sizeof (vpsissRszCtrl_t));
    memset(&pChObj->drvRszCfg, 0x0, sizeof (vpsissRszCfg_t));

    rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
    rszCtrl.rszCfg = &pChObj->drvRszCfg;

    status = Fvid2_control(
        pObj->fvidHandle,
        VPS_ISS_RSZ_IOCTL_GET_CONFIG,
        &rszCtrl,
        NULL);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for (cnt = 0u; cnt < ISSRSZ_LINK_OUTPUTQUE_MAXNUM; cnt ++)
    {
        pOutChInfo = &pObj->info.queInfo[cnt].chInfo[chId];

        pChObj->drvRszCfg.inCfg.opMode = VPS_ISS_RSZ_OP_MODE_RESIZING;

        if ((UInt32)TRUE == pObj->createArgs.channelParams[chId].enableCrop)
        {
            pChObj->drvRszCfg.inCfg.procWin.cropStartX =
                pObj->createArgs.channelParams[chId].inCropCfg.cropStartX;
            pChObj->drvRszCfg.inCfg.procWin.cropStartY =
                pObj->createArgs.channelParams[chId].inCropCfg.cropStartY;
            pChObj->drvRszCfg.inCfg.procWin.cropWidth  =
                pObj->createArgs.channelParams[chId].inCropCfg.cropWidth;
            pChObj->drvRszCfg.inCfg.procWin.cropHeight =
                pObj->createArgs.channelParams[chId].inCropCfg.cropHeight;
        }
        else
        {
            pChObj->drvRszCfg.inCfg.procWin.cropStartX = 0U;
            pChObj->drvRszCfg.inCfg.procWin.cropStartY = 0U;
            pChObj->drvRszCfg.inCfg.procWin.cropWidth  = pInChInfo->width;
            pChObj->drvRszCfg.inCfg.procWin.cropHeight = pInChInfo->height;
        }

        pChObj->drvRszCfg.instCfg[cnt].outFmt.dataFormat =
            System_Link_Ch_Info_Get_Flag_Data_Format(pOutChInfo->flags);
        pChObj->drvRszCfg.instCfg[cnt].outFmt.width      = pOutChInfo->width;
        pChObj->drvRszCfg.instCfg[cnt].outFmt.height     = pOutChInfo->height;
        pChObj->drvRszCfg.instCfg[cnt].outFmt.pitch[0U]  = pOutChInfo->pitch[0];
        pChObj->drvRszCfg.instCfg[cnt].outFmt.pitch[1U]  = pOutChInfo->pitch[1];
        pChObj->drvRszCfg.instCfg[cnt].outFmt.pitch[2U]  = pOutChInfo->pitch[2];

        pChObj->drvRszCfg.instCfg[cnt].flipCtrl =
            VPS_ISS_RSZ_STR_MODE_NORMAL;
        pChObj->drvRszCfg.instCfg[cnt].startPos.startX = 0U;
        pChObj->drvRszCfg.instCfg[cnt].startPos.startY = 0U;
        pChObj->drvRszCfg.instCfg[cnt].scaleMode       =
            VPS_ISS_RSZ_SCALE_MODE_NORMAL;
        pChObj->drvRszCfg.instCfg[cnt].filtCfg.horzLumaFilter =
            VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
        pChObj->drvRszCfg.instCfg[cnt].filtCfg.vertLumaFilter =
            VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
        pChObj->drvRszCfg.instCfg[cnt].filtCfg.horzChromaFilter =
            VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
        pChObj->drvRszCfg.instCfg[cnt].filtCfg.vertChromaFilter =
            VPS_ISS_RSZ_FILTER_4TAP_CUBIC;

        pChObj->drvRszCfg.instCfg[cnt].intensityCfg.horzLumaIntensity   = 21u;
        pChObj->drvRszCfg.instCfg[cnt].intensityCfg.horzChromaIntensity = 22u;
        pChObj->drvRszCfg.instCfg[cnt].intensityCfg.vertLumaIntensity   = 14u;
        pChObj->drvRszCfg.instCfg[cnt].intensityCfg.vertChromaIntensity = 15u;
        pChObj->drvRszCfg.instCfg[cnt].overrideScaleFactor = FALSE;
        pChObj->drvRszCfg.instCfg[cnt].yuvRszMode =
            VPS_ISS_RSZ_YUV_RSZ_MODE_LUMA_AND_CHROMA;

        if ((UInt32)TRUE == pObj->createArgs.channelParams[chId].enableOut[cnt])
        {
            pChObj->drvRszCfg.instCfg[cnt].enable = TRUE;
        }
        else
        {
            pChObj->drvRszCfg.instCfg[cnt].enable = FALSE;
        }

		pChObj->drvRszCfg.instCfg[cnt].alpha = 0xFFu;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Function to create the IPIPE Input parameters for given channel
 *
 * \param   pObj     [IN] ISS Resizer Link Instance handle
 * \param   chId     [IN] channel number
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssRszLink_drvCreateIpipeInputPrms(IssRszLink_Obj * pObj, UInt32 chId)
{
    vpsissIpipeCtrl_t ipipeCtrl;
    IssRszLink_ChObj *pChObj;
    System_LinkChInfo *pInChInfo;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(chId < pObj->inQueInfo.numCh);
    pChObj = &pObj->chObj[chId];

    pInChInfo  = &pObj->inQueInfo.chInfo[chId];

    memset(&pChObj->drvIpipeInputCfg, 0x0, sizeof (vpsissIpipeInConfig_t));
    memset(&ipipeCtrl, 0x0, sizeof (vpsissIpipeCtrl_t));

    ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_INPUT;
    ipipeCtrl.inCfg  = &pChObj->drvIpipeInputCfg;

    status = Fvid2_control(
        pObj->fvidHandle,
        VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
        &ipipeCtrl,
        NULL);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pChObj->drvIpipeInputCfg.dataPath =
        VPS_ISS_IPIPE_DATA_PATH_YUV422_YUV422;

    pChObj->drvIpipeInputCfg.procWin.cropStartX = 0U;
    pChObj->drvIpipeInputCfg.procWin.cropStartY = 0U;
    pChObj->drvIpipeInputCfg.procWin.cropWidth  = pInChInfo->width;
    pChObj->drvIpipeInputCfg.procWin.cropHeight = pInChInfo->height;

    return status;

}

/**
 *******************************************************************************
 *
 * \brief Function to create the ISS Resizer driver handle
 *
 *        Create the ISS Resizer link driver object/instance.
 *        - Populates the VPS driver create and control parameters
 *        - Create and configure the VPS ISS Resizer driver
 *
 * \param   pObj     [IN] ISS Resizer Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssRszLink_drvCreateFvidObj(IssRszLink_Obj *pObj)
{
    FVID2_CbParams cbParams;
    Uint32 chId;

    Fvid2CbParams_init(&cbParams);
    cbParams.cbFxn    = &IssRszLink_drvFvidCb;
    cbParams.errCbFxn = &IssRszLink_drvFvidErrCb;
    cbParams.errList  = &pObj->errProcessList;
    cbParams.appData  = pObj;

    VpsM2mIntfCreateParams_init(&pObj->drvCreatePrms);
    pObj->drvCreatePrms.numCh           = 1U;
    pObj->drvCreatePrms.chInQueueLength = 4;
    pObj->drvCreatePrms.maxStatsInst    = 0U;
    pObj->drvCreatePrms.pAdditionalArgs = (Ptr) & pObj->drvOpenPrms;

    VpsM2mIntfCreateStatus_init(&pObj->drvCreateStatusPrms);
    pObj->drvCreateStatusPrms.pAdditionalStatus = (Ptr) & pObj->drvRetPrms;

    pObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPEIF] = (UInt32)TRUE;
    pObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_NSF3]    = (UInt32)FALSE;
    pObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_GLBCE]   = (UInt32)FALSE;
    pObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_ISIF]    = (UInt32)TRUE;
    pObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPE]   = (UInt32)TRUE;
    pObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_RSZ]     = (UInt32)TRUE;
    pObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_CNF]     = (UInt32)FALSE;
    pObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_H3A]     = (UInt32)FALSE;
    pObj->drvOpenPrms.arg = NULL;

    pObj->fvidHandle = Fvid2_create(
        FVID2_VPS_COMMON_M2M_INTF_DRV,
        VPS_M2M_ISS_INST_CAL_ISP,
        &pObj->drvCreatePrms,
        &pObj->drvCreateStatusPrms,
        &cbParams);

    UTILS_assert(NULL != pObj->fvidHandle);

    /* To capture ISS Driver parameters at create time */
    for (chId = 0u; chId <  pObj->inQueInfo.numCh; chId++)
    {
        IssRszLink_drvCreateIspPrms(pObj, chId);
        IssRszLink_drvCreateRszCfgPrms(pObj, chId);
        IssRszLink_drvCreateIpipeInputPrms(pObj, chId);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function sets the ISS configuration for the given channel
 *
 * \param   pObj   [IN]  ISS Resizer Link Instance handle
 * \param   chId   [IN]  Channel Id to be configured
 *
 * \param   status [OUT] Return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssRszLink_drvSetChannelIssConfig(IssRszLink_Obj * pObj, UInt32 chId,
    System_Buffer *pOutputBuffer[ISSRSZ_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status;
    IssRszLink_ChObj *pChObj;
    vpsissRszCtrl_t rszCtrl;
    vpsissIpipeCtrl_t ipipeCtrl;
    vpsissIsifCtrl_t isifCtrl;

    pChObj = &pObj->chObj[chId];

    status = Fvid2_control(
        pObj->fvidHandle,
        IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS,
        &pChObj->drvIspPrms,
        NULL);

    UTILS_assert(status == FVID2_SOK);

    if (NULL != pOutputBuffer[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A])
    {
        pChObj->drvRszCfg.instCfg[0u].enable = TRUE;
    }
    else
    {
        pChObj->drvRszCfg.instCfg[0u].enable = FALSE;
    }
    if (NULL != pOutputBuffer[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_B])
    {
        pChObj->drvRszCfg.instCfg[1u].enable = TRUE;
    }
    else
    {
        pChObj->drvRszCfg.instCfg[1u].enable = FALSE;
    }

    rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
    rszCtrl.rszCfg = &pChObj->drvRszCfg;

    status = Fvid2_control(
        pObj->fvidHandle,
        VPS_ISS_RSZ_IOCTL_SET_CONFIG,
        &rszCtrl,
        NULL);

    UTILS_assert(status == FVID2_SOK);

    ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_INPUT;
    ipipeCtrl.inCfg  = &pChObj->drvIpipeInputCfg;

    status = Fvid2_control(
        pObj->fvidHandle,
        VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
        &ipipeCtrl,
        NULL);

    UTILS_assert(status == FVID2_SOK);

    pChObj->isifBlkClampCfg.dcOffset = 0x0;

    isifCtrl.module = VPS_ISS_ISIF_MODULE_BLACK_CLAMP;
    isifCtrl.blkClampCfg  = &pChObj->isifBlkClampCfg;
    status = Fvid2_control(
        pObj->fvidHandle,
        VPS_ISS_ISIF_IOCTL_SET_CONFIG,
        &isifCtrl,
        NULL);

    UTILS_assert(status == FVID2_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

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
Int32 IssRszLink_drvProcessFrame(
        IssRszLink_Obj      *pObj,
        const System_Buffer *pInputBuffer,
        System_Buffer       *pOutputBuffer[ISSRSZ_LINK_OUTPUTQUE_MAXNUM])

{
    Int32           status;
    UInt32          i;
    Fvid2_Frame     *inFrm;
    Fvid2_Frame     *outFrm;
    Fvid2_FrameList *inFrmList;
    Fvid2_FrameList *outFrmList;
    System_VideoFrameBuffer *pVideoFrame;

    inFrmList = &pObj->reqObj.inFrameList;
    outFrmList = &pObj->reqObj.outFrameList;
    for(i = 0u; i < VPS_ISS_STREAM_ID_MAX; i ++)
    {
        inFrmList->frames[i] = NULL;
        outFrmList->frames[i] = NULL;
    }

    /* Initialize Input Frame */
    inFrm = &pObj->reqObj.inputFrame;
    pVideoFrame = (System_VideoFrameBuffer *)pInputBuffer->payload;

    inFrm->chNum = 0;
    inFrm->addr[0u][0u] = pVideoFrame->bufAddr[0u];
    inFrm->addr[0u][1u] = pVideoFrame->bufAddr[1u];
    inFrmList->frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] = inFrm;

    /* Initialize Output Frames */
    if (NULL != pOutputBuffer[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A])
    {
        outFrm = &pObj->reqObj.outputFrame[0u];
        pVideoFrame = (System_VideoFrameBuffer *)pOutputBuffer[
            ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A]->payload;

        outFrm->chNum = 0;
        outFrm->addr[0U][0U] = pVideoFrame->bufAddr[0u];
        outFrm->addr[0U][1U] = pVideoFrame->bufAddr[1u];

        outFrmList->frames[VPS_ISS_STREAM_ID_RSZ_A] = outFrm;
    }
    if (NULL != pOutputBuffer[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_B])
    {
        outFrm = &pObj->reqObj.outputFrame[1u];
        pVideoFrame = (System_VideoFrameBuffer *)pOutputBuffer[
            ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_B]->payload;

        outFrm->chNum = 0;
        outFrm->addr[0U][0U] = pVideoFrame->bufAddr[0u];
        outFrm->addr[0U][1U] = pVideoFrame->bufAddr[1u];

        outFrmList->frames[VPS_ISS_STREAM_ID_RSZ_B] = outFrm;
    }

    IssRszLink_drvSetChannelIssConfig(pObj, pInputBuffer->chNum, pOutputBuffer);

    inFrmList->numFrames = VPS_ISS_STREAM_ID_MAX;
    outFrmList->numFrames = VPS_ISS_STREAM_ID_MAX;

    /*
     * Submit Processing Request to the driver, wait on a semaphore and
     * get processed frame
     */
    status = Fvid2_processRequest(pObj->fvidHandle, inFrmList, outFrmList);
    UTILS_assert(status==0);

    BspOsal_semWait(pObj->complete, BSP_OSAL_WAIT_FOREVER);

    status = Fvid2_getProcessedRequest(
            pObj->fvidHandle, inFrmList, outFrmList, FVID2_TIMEOUT_NONE);
    UTILS_assert(status==0);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function submit the job to the ISS driver to perform resizing
 *
 *        VPS driver defines certain input and output frame data structure
 *        and this need to be populated to submit any job to the driver
 *        - Call IssRszLink_drvQueueFramesToChQue to put the input buffers
 *          into the link internal input buffer queue
 *        - Get the input frame list
 *        - Get the output frame List
 *        - Populate VPS driver the process List
 *        - Call the function to create the in/out frame List
 *        - Call IOCTL if useOverridePrevFldBuf == TRUE
 *        - Submit the job to driver by invoking FVID2_processFrames
 *        - Wait for the process/job completion
 *        - Call FVID2_getProcessedFrames once the completion
 *        Repeat above until all input frames are processed
 *
 * \param   pObj   [IN]  ISS Resizer Link Instance handle
 *
 * \param   status [OUT] Return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssRszLink_drvProcessData(IssRszLink_Obj * pObj)
{
    Int32 status;
    UInt32 chId, freeBufNum, bufId, queId;
    System_LinkInQueParams *pInQueParams;
    System_BufferList bufList;
    System_LinkStatistics *linkStatsInfo;
    System_Buffer *pInputBuffer;
    System_Buffer *pOutputBuffer[ISSRSZ_LINK_OUTPUTQUE_MAXNUM];
    IssRszLink_ChannelParams *pChParams;
    Bool sendCmdToNextLink[ISSRSZ_LINK_OUTPUTQUE_MAXNUM] = { FALSE };
    IssRszLink_OutObj *pOutObj;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    if(pObj->isFirstFrameRecv == FALSE)
    {
        pObj->isFirstFrameRecv = (Bool)TRUE;

        Utils_resetLinkStatistics(
                &linkStatsInfo->linkStats,
                pObj->inQueInfo.numCh,
                ISSRSZ_LINK_OUTPUTQUE_MAXNUM);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    pInQueParams = &pObj->createArgs.inQueParams;

    System_getLinksFullBuffers(pInQueParams->prevLinkId,
                               pInQueParams->prevLinkQueId, &bufList);

    if (bufList.numBuf)
    {
        freeBufNum = 0;

        for (bufId = 0; bufId < bufList.numBuf; bufId++)
        {
            pInputBuffer = bufList.buffers[bufId];
            chId = pInputBuffer->chNum;

            if (pInputBuffer->chNum >= pObj->inQueInfo.numCh)
            {
                bufList.buffers[freeBufNum] = pInputBuffer;
                freeBufNum++;
                linkStatsInfo->linkStats.inBufErrorCount++;
            }
            else
            {
                linkStatsInfo->linkStats.chStats[chId].inBufRecvCount++;
                pChParams = &pObj->createArgs.channelParams[chId];

                /*
                 * Fetch empty output buffer for image and H3A
                 */
                for( queId = 0U; queId < ISSRSZ_LINK_OUTPUTQUE_MAXNUM; queId++)
                {
                    pOutputBuffer[queId] = NULL;

                    if(pChParams->enableOut[queId])
                    {
                        /* MISRA.CAST.PTR:MISRAC_2004 Rule_11.4
                           MISRAC_WAIVER:
                           Generic implementation of queue expects data in
                           Ptr* type,
                           so typecasted it to Ptr *. */
                        pOutObj = &pObj->outObj[queId];
                        status  = Utils_queGet(
                                        &pOutObj->emptyBufQue[chId],
                                        (Ptr *)&pOutputBuffer[queId],
                                        1U,
                                        BSP_OSAL_NO_WAIT);

                        if(pOutputBuffer[queId])
                        {
                            pOutputBuffer[queId]->srcTimestamp =
                                pInputBuffer->srcTimestamp;
                            pOutputBuffer[queId]->frameId =
                                pInputBuffer->frameId;
                            pOutputBuffer[queId]->linkLocalTimestamp =
                                Utils_getCurGlobalTimeInUsec();
                        }
                        else
                        {
                            linkStatsInfo->linkStats.chStats[chId].
                                outBufDropCount[queId]++;
                        }
                    }
                }

                if ((pOutputBuffer[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] != NULL) ||
                    (pOutputBuffer[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_B] != NULL))
                {
                    Utils_pendIspLock();

                    /*
                     * Reaching here means an error free input and empty
                     * output buffers are available
                     */
                    IssRszLink_drvProcessFrame(pObj, pInputBuffer,
                        pOutputBuffer);

                    Utils_postIspLock();

                    linkStatsInfo->linkStats.chStats[chId].inBufProcessCount++;

                    for (queId = 0U; queId < ISSRSZ_LINK_OUTPUTQUE_MAXNUM;
                        queId++)
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

                            status = Utils_bufPutFullBuffer(
                                &pObj->outObj[queId].bufOutQue,
                                (Ptr)pOutputBuffer[queId]);
                            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                        }
                    }
                }
                else
                {
                    linkStatsInfo->linkStats.chStats[chId].inBufDropCount++;
                }
            }
        }

        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                pInQueParams->prevLinkQueId,
                &bufList);
    }

    /*
     * Send command to next link for putting the buffer in output queue
     * of the buffer
     */
    for(queId=0 ; queId<ISSRSZ_LINK_OUTPUTQUE_MAXNUM ; queId++)
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
 * \brief Function to create the ISS Resizer link output object and Allocate
 *        the output buffers.
 *
 *        Create the ISS link Output object, one per output queue
 *        - Create the Output Buffer Queue
 *        - populates the output frame parameters
 *        - Allocate the memory for the output frame buffers
 *
 * \param   pObj     [IN] ISS Resizer Link Instance handle
 *
 * \return  status   [OUT] return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssRszLink_drvCreateOutAndAllocBuffers(IssRszLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId, chId, frameIdx, numFrames, temp;
    System_LinkChInfo *pInChInfo;
    IssRszLink_ChannelParams *chParams;
    System_LinkChInfo *pOutChInfo;
    IssRszLink_OutputParams *pChOutParams;
    System_Buffer *pSystemBuffer;
    System_VideoFrameBuffer *pSystemVideoFrameBuffer;
    IssRszLink_OutObj *pOutObj;

    pObj->info.numQue = ISSRSZ_LINK_OUTPUTQUE_MAXNUM;

    for (queId = 0u; queId < ISSRSZ_LINK_OUTPUTQUE_MAXNUM; queId++)
    {
        pObj->info.queInfo[queId].numCh = pObj->inQueInfo.numCh;

        /* Create Buffer Output Queue */
        status = Utils_bufCreate(&pObj->outObj[queId].bufOutQue,
            (Bool)TRUE, (Bool)FALSE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        /* Initialize output channel information */
        for (chId = 0u; chId < pObj->inQueInfo.numCh; chId++)
        {
            pInChInfo = &pObj->inQueInfo.chInfo[chId];
            pOutChInfo = &pObj->info.queInfo[queId].chInfo[chId];
            chParams = &pObj->createArgs.channelParams[chId];
            pChOutParams = &chParams->outParams;

            pOutChInfo->startX = 0;
            pOutChInfo->startY = 0;

            if(queId == ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A)
            {
                pOutChInfo->width  = pChOutParams->widthRszA;
                pOutChInfo->height  = pChOutParams->heightRszA;
            }
            else
            {
                pOutChInfo->width  = pChOutParams->widthRszB;
                pOutChInfo->height  = pChOutParams->heightRszB;
            }

            if (0U == pOutChInfo->width)
            {
                pOutChInfo->width = pInChInfo->width;
            }
            if (0U == pOutChInfo->height)
            {
                pOutChInfo->height = pInChInfo->height;
            }

            if ((pChOutParams->dataFormat == SYSTEM_DF_YUV422I_YUYV) ||
                (pChOutParams->dataFormat == SYSTEM_DF_YUV422I_UYVY))
            {
                pOutChInfo->pitch[0U] = (UInt32)SystemUtils_align(
                    pOutChInfo->width*2U,
                    (UInt32)ISS_RSZ_LINK_BUF_ALIGNMENT);
                pOutChInfo->pitch[1] = (UInt32)0;
                pOutChInfo->pitch[2] = (UInt32)0;
            }
            if(pChOutParams->dataFormat == SYSTEM_DF_YUV420SP_UV)
            {
                pOutChInfo->pitch[0U] = (UInt32)SystemUtils_align(
                    pOutChInfo->width, (UInt32)ISS_RSZ_LINK_BUF_ALIGNMENT);
                pOutChInfo->pitch[1] = (UInt32)pOutChInfo->pitch[0U];
                pOutChInfo->pitch[2] = (UInt32)pOutChInfo->pitch[0U];
            }
            if(pChOutParams->dataFormat == SYSTEM_DF_ARGB32_8888)
            {
                pOutChInfo->pitch[0U] = (UInt32)SystemUtils_align(
                    pOutChInfo->width*4U,
                    (UInt32)ISS_RSZ_LINK_BUF_ALIGNMENT);
                pOutChInfo->pitch[1] = (UInt32)0;
                pOutChInfo->pitch[2] = (UInt32)0;
            }

            pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(
                pOutChInfo->flags, pChOutParams->dataFormat);

            pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(
                pOutChInfo->flags, SYSTEM_SF_PROGRESSIVE);

            pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(
                pOutChInfo->flags, SYSTEM_BUFFER_TYPE_VIDEO_FRAME);

            /* Allocate Buffers and initialize Video Frames */
            if ((UInt32)FALSE != chParams->enableOut[queId])
            {
                UTILS_assert(0U != chParams->numBuffersPerCh);
                UTILS_assert(ISS_RSZ_LINK_MAX_OUT_FRAMES_PER_CH >=
                    chParams->numBuffersPerCh);

                numFrames = chParams->numBuffersPerCh;

                pOutObj = &pObj->outObj[queId];
                pOutObj->numFrames[chId] = chParams->numBuffersPerCh;

                /* Create empty queue per channel */
                status = Utils_queCreate(
                                &pOutObj->emptyBufQue[chId],
                                pOutObj->numFrames[chId],
                                pOutObj->bufsMem[chId],
                                UTILS_QUE_FLAG_NO_BLOCK_QUE);
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                for(frameIdx = 0; frameIdx < numFrames; frameIdx++)
                {
                    pSystemBuffer = &pObj->outObj[queId].
                        buffers[chId][frameIdx];
                    pSystemVideoFrameBuffer = &pObj->outObj[queId].
                        videoFrames[chId][frameIdx];

                    pSystemBuffer->payload = pSystemVideoFrameBuffer;
                    pSystemBuffer->payloadSize = sizeof(System_VideoFrameBuffer);
                    pSystemBuffer->bufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
                    pSystemBuffer->chNum = chId;

                    pSystemVideoFrameBuffer->chInfo = *pOutChInfo;

                    pObj->outObj[queId].bufSize[chId] =
                        pOutChInfo->height*pOutChInfo->pitch[0U];

                    if(System_Link_Ch_Info_Get_Flag_Data_Format(
                            pOutChInfo->flags) == SYSTEM_DF_YUV420SP_UV)
                    {
                        pObj->outObj[queId].bufSize[chId]
                            += ((pOutChInfo->height/2U)*pOutChInfo->pitch[0U]);
                    }

                    if(System_useLinkMemAllocInfo(
                            &pObj->createArgs.memAllocInfo)==FALSE)
                    {
                        pSystemVideoFrameBuffer->bufAddr[0]
                            = Utils_memAlloc(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                pObj->outObj[queId].bufSize[chId],
                                SYSTEM_BUFFER_ALIGNMENT);
                    }
                    else
                    {
                        pSystemVideoFrameBuffer->bufAddr[0]
                            = System_allocLinkMemAllocInfo(
                                &pObj->createArgs.memAllocInfo,
                                pObj->outObj[queId].bufSize[chId],
                                SYSTEM_BUFFER_ALIGNMENT);
                    }
                    UTILS_assert(pSystemVideoFrameBuffer->bufAddr[0]!=NULL);

                    temp = pOutChInfo->height * pOutChInfo->pitch[0U];
                    /* MISRA.CAST.PTR_TO_INT
                     * MISRAC_2004 Rule 11.3
                     * Cast between a pointer and an integral type
                     * MISRAC_WAIVER:
                     * Pointer address is typecasted to int to calculate and to
                     * get the offset of the chroma buffer.
                     * allocated buffer address is already checked using
                     * Utils_assert
                     */
                    temp = (UInt32)pSystemVideoFrameBuffer->bufAddr[0] + temp;

                    /* MISRA.CAST.PTR_TO_INT
                     * MISRAC_2004 Rule 11.3
                     * Cast between a pointer and an integral type
                     * MISRAC_WAIVER:
                     * Calculated chroma buffer offset is assigned to
                     * chroma buffer pointer, luma buffer pointer is already
                     * checked againts null using UTILS_assert
                     */
                    pSystemVideoFrameBuffer->bufAddr[1] = (Void *)temp;

                    status = Utils_quePut(
                                    &pOutObj->emptyBufQue[chId],
                                    pSystemBuffer,
                                    BSP_OSAL_NO_WAIT);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
            }
        }
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief ISS Resizer link create function
 *
 *        This Set the Link and driver create time parameters.
 *        - Get the channel info from previous link
 *        - create the semaphore required for ISS Resizer link
 *        - Set the internal data structures
 *        - Create the output object per output queue
 *        - Create the Link channel object per channel
 *        - Create the ISS Resizer driver instance
 *        - Allocate the DEI context buffers
 *        - Choose the scalar coefficients and configure the driver
 *        - Create the link intermediate request object
 *
 * \param   pObj     [IN] ISS Resizer Link Instance handle
 * \param   pPrm     [IN] ISS Resizer link create parameters
 *                        This need to be configured by the application
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssRszLink_drvCreate(IssRszLink_Obj *pObj,
    const IssRszLink_CreateParams * pPrm)
{
    Int32 status;
    UInt32 cnt;
    System_LinkChInfo *pInChInfo;

    Vps_printf(" ISS Resizer: Create in progress !!!\n");

    UTILS_MEMLOG_USED_START();
    memcpy(&pObj->createArgs, pPrm, sizeof(*pPrm));

    System_resetLinkMemAllocInfo(&pObj->createArgs.memAllocInfo);

    status = System_linkGetInfo(pPrm->inQueParams.prevLinkId, &pObj->inTskInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    UTILS_assert(pPrm->inQueParams.prevLinkQueId < pObj->inTskInfo.numQue);

    memcpy(&pObj->inQueInfo,
           &pObj->inTskInfo.queInfo[pPrm->inQueParams.prevLinkQueId],
           sizeof(pObj->inQueInfo));
    UTILS_assert(pObj->inQueInfo.numCh <= ISS_RSZ_LINK_MAX_CH);

    for (cnt = 0u; cnt < pObj->inQueInfo.numCh; cnt ++)
    {
        pInChInfo = &pObj->inQueInfo.chInfo[cnt];

        if ((UInt32)TRUE == pObj->createArgs.channelParams[cnt].enableCrop)
        {
            if (((pObj->createArgs.channelParams[cnt].inCropCfg.cropStartX +
                 pObj->createArgs.channelParams[cnt].inCropCfg.cropWidth) >
                 pInChInfo->width) ||
                ((pObj->createArgs.channelParams[cnt].inCropCfg.cropStartY +
                 pObj->createArgs.channelParams[cnt].inCropCfg.cropHeight) >
                 pInChInfo->height))
            {
                Vps_printf(" ISS Resizer: Crop Size incorrect\n");
                UTILS_assert(FALSE);
            }
        }
    }

    /* Create semaphores */
    pObj->complete = BspOsal_semCreate(0, (Bool)TRUE);
    UTILS_assert(pObj->complete != NULL);

    IssRszLink_drvCreateOutAndAllocBuffers(pObj);

    IssRszLink_drvCreateFvidObj(pObj);

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->linkId, "ISS Resizer");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->isFirstFrameRecv = (Bool)FALSE;

    System_assertLinkMemAllocOutOfMem(
        &pObj->createArgs.memAllocInfo,
        "ISS Resizer");

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("ISS Resizer", pObj->memUsed,
        UTILS_ARRAYSIZE(pObj->memUsed));

    Vps_printf(" ISS RESIZER: Create Done !!!\n");

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Delete iss M2m isp link and driver handle.
 *
 *
 * \param  pObj         [IN] Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssRszLink_drvDelete(IssRszLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId, chId, frameIdx, numFrames;
    IssRszLink_ChannelParams *chParams;
    System_VideoFrameBuffer *pSystemVideoFrameBuffer;
    IssRszLink_OutObj *pOutObj;

    Vps_printf(" ISS Resizer: Delete in progress !!!\n");

    status = FVID2_delete(pObj->fvidHandle, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* Delete semaphores */
    BspOsal_semDelete(&pObj->complete);

    for (queId = 0u; queId < ISSRSZ_LINK_OUTPUTQUE_MAXNUM; queId++)
    {
        status = Utils_bufDelete(&pObj->outObj[queId].bufOutQue);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        /* Initialize output channel information */
        for (chId = 0u; chId < pObj->inQueInfo.numCh; chId++)
        {
            chParams = &pObj->createArgs.channelParams[chId];

            /* Allocate Buffers and initialize Video Frames */
            if ((UInt32)FALSE != chParams->enableOut[queId])
            {
                numFrames = chParams->numBuffersPerCh;

                for(frameIdx = 0; frameIdx < numFrames; frameIdx++)
                {
                    pSystemVideoFrameBuffer = &pObj->outObj[queId].
                        videoFrames[chId][frameIdx];

                    if(System_useLinkMemAllocInfo(
                            &pObj->createArgs.memAllocInfo)==FALSE)
                    {
                        status = Utils_memFree(
                            UTILS_HEAPID_DDR_CACHED_SR,
                            pSystemVideoFrameBuffer->bufAddr[0],
                            pObj->outObj[queId].bufSize[chId]);
                        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
                    }
                }

                /* Delete the channel empty queue */
                pOutObj = &pObj->outObj[queId];
                status = Utils_queDelete(&pOutObj->emptyBufQue[chId]);
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
            }
        }
    }

    /* Free up Link stats instance */
    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(0 == status);

    Vps_printf(" ISS Resizer: Delete Done !!!\n");

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Function to prints the ISS Resizer link statistics
 *
 *        Also reset the Link statistics after the print controlled by a flag
 *
 * \param   pObj            [IN] Display Link Instance handle
 * \param   resetAfterPrint [IN] Flag to reset the statistics after print
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssRszLink_printStatistics (const IssRszLink_Obj *pObj, Bool resetAfterPrint)
{
    UTILS_assert(NULL != pObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats, "ISS Resizer", (Bool)TRUE);

    Utils_printLatency("ISS Resizer",
                       &pObj->linkStatsInfo->linkLatency,
                       &pObj->linkStatsInfo->srcToLinkLatency,
                       (Bool)TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to prints the ISS Resizer link output buffer status
 *
 * \param   pObj            [IN] Display Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssRszLink_printBufferStatus(IssRszLink_Obj * pObj)
{
    UInt32 i;
    UInt8 str[32];

    for (i=0U; i<ISSRSZ_LINK_OUTPUTQUE_MAXNUM; i++)
    {
        snprintf ((char *)str, 32U, "ISS RSZ OUT%d", i);
        Utils_bufPrintStatus(str, &pObj->outObj[i].bufOutQue);
    }

    return SYSTEM_LINK_STATUS_SOK;
}
