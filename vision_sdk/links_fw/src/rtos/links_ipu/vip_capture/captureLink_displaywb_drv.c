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
 * \file captureLink_displaywb_drv.c
 *
 * \brief  This file communicates with driver for capture link.
 *
 *         This file calls the display write back driver commands and APIs.
 *         All application commands and APIs finally gets
 *         translated to driver APIs and commands by this file.
 *
 * \version 0.0 (May 2015) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "captureLink_priv.h"

void CaptureLink_dispWbCreateInst(CaptureLink_Obj * pObj, UInt16 instId)
{
    Int32  retVal = SYSTEM_LINK_STATUS_SOK;
    Vps_CaptCreateParams *createPrms;
    CaptureLink_InstObj *pInst;
    Vps_CaptDssWbParams *dssWbPrms;
    CaptureLink_DssWbInstParams *pDssWbInst;
    Vps_CaptVipOutInfo *pOutInfo;
    UInt32 outFrmPitch[FVID2_MAX_PLANES]={0};
    System_DssWbInputParams *pIpPrms;
    System_DssWbOutputParams *pOpPrms;
    UInt16 queChId, queId = 0;
    System_LinkChInfo *pQueChInfo;
    UInt32 dssWbBuffAllign;

    dssWbPrms = &pObj->instObj[instId].dssWbPrms;
    pDssWbInst = &pObj->createArgs.dssWbInst[instId];
    pInst = &pObj->instObj[instId];
    pIpPrms = &pDssWbInst->dssWbInputPrms;
    pOpPrms = &pDssWbInst->dssWbOutputPrms;

    pInst->instId = pDssWbInst->dssWbInstId;
    pObj->mapInstId[pDssWbInst->dssWbInstId] = instId;

    UTILS_assert (pObj->createArgs.numDssWbInst == SYSTEM_CAPTURE_DSSWB_INST_MAX);

#if defined (TDA3XX_BUILD)
    /* For tda3xx platform WB pipe bigger pitch is not supported. */
    dssWbBuffAllign = 1U;
#else
    dssWbBuffAllign = VPS_BUFFER_ALIGNMENT;
#endif

    if (Fvid2_isDataFmtSemiPlanar(pOpPrms->wbDataFmt))
    {
        outFrmPitch[FVID2_YUV_SP_Y_ADDR_IDX] =
            VpsUtils_align(pOpPrms->wbWidth, dssWbBuffAllign);
        outFrmPitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
            outFrmPitch[FVID2_YUV_SP_Y_ADDR_IDX];
    }
    else if (Fvid2_isDataFmtYuv422I(pOpPrms->wbDataFmt))
    {
        outFrmPitch[FVID2_YUV_INT_ADDR_IDX] =
            VpsUtils_align(pOpPrms->wbWidth * 2U, dssWbBuffAllign);
    }
    else if (Fvid2_isDataFmtRgb16bit(pOpPrms->wbDataFmt))
    {
        outFrmPitch[FVID2_YUV_INT_ADDR_IDX] =
            VpsUtils_align(pOpPrms->wbWidth * 2U, dssWbBuffAllign);
    }
    else if (Fvid2_isDataFmtRgb24bit(pOpPrms->wbDataFmt))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        outFrmPitch[FVID2_RGB_ADDR_IDX] =
            VpsUtils_align(pOpPrms->wbWidth * 3U,
                           (dssWbBuffAllign * 3U));
    }
    else if (Fvid2_isDataFmtRgb32bit(pOpPrms->wbDataFmt))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        outFrmPitch[FVID2_RGB_ADDR_IDX] =
            VpsUtils_align(pOpPrms->wbWidth * 4U,
                           (dssWbBuffAllign));
    }
    else
    {
        UTILS_assert((Bool)0);
    }

    createPrms = &pInst->createArgs;
    VpsCaptCreateParams_init(createPrms);
    createPrms->videoIfMode  = FVID2_VIFM_SCH_DS_HSYNC_VSYNC;
    createPrms->videoIfWidth = FVID2_VIFW_8BIT;
    createPrms->bufCaptMode  = VPS_CAPT_BCM_LAST_FRM_REPEAT;
    createPrms->numCh        = 1;
    createPrms->numStream    = 1;

    Fvid2CbParams_init(&pInst->cbPrm);
    pInst->cbPrm.appData = pInst;
    pInst->parent = pObj;
    pInst->cbPrm.cbFxn = &CaptureLink_drvCallback;

    /* assumes only one output at DSS WB */
    createPrms->chNumMap[0][0] =
        pObj->info.queInfo[queId].numCh + pObj->fvid2DrvChNumOffset;

    pInst->captureVipHandle = Fvid2_create(
                                    FVID2_VPS_CAPT_VID_DRV,
                                    pInst->instId,
                                    createPrms,
                                    &pInst->createStatus,
                                    &pInst->cbPrm);
    if ((NULL == pInst->captureVipHandle) ||
        (pInst->createStatus.retVal != SYSTEM_LINK_STATUS_SOK))
    {
        Vps_printf(" CAPTURE: DSS WB Capture Create Failed!!!\n");
        retVal = pInst->createStatus.retVal;
    }

    VpsCaptDssWbParams_init(dssWbPrms);

    dssWbPrms->inNode = (Vps_DssDispcWbInNode)pIpPrms->inNode;
    dssWbPrms->inFmt.dataFormat = pIpPrms->wbInSourceDataFmt;
    dssWbPrms->inFmt.width      = pIpPrms->wbInSourceWidth;
    dssWbPrms->inFmt.height     = pIpPrms->wbInSourceHeight;
    dssWbPrms->inFmt.scanFormat = pIpPrms->wbScanFormat;
    dssWbPrms->inFmt.fieldMerged[0] = FALSE;

    dssWbPrms->outStreamInfo[0].outFmt.chNum          = createPrms->chNumMap[0][0];
    dssWbPrms->outStreamInfo[0].outFmt.height         = pOpPrms->wbHeight;
    dssWbPrms->outStreamInfo[0].outFmt.width          = pOpPrms->wbWidth;
    dssWbPrms->outStreamInfo[0].outFmt.pitch[0]       = outFrmPitch[0];
    dssWbPrms->outStreamInfo[0].outFmt.dataFormat     = pOpPrms->wbDataFmt;
    dssWbPrms->outStreamInfo[0].outFmt.fieldMerged[0] = FALSE;
    dssWbPrms->outStreamInfo[0].outFmt.scanFormat = pOpPrms->wbScanFormat;
    dssWbPrms->outStreamInfo[0].advDmaCfg        = NULL;
    dssWbPrms->outStreamInfo[0].scEnable         = TRUE;
    dssWbPrms->outStreamInfo[0].cscFullRngEnable = TRUE;

    dssWbPrms->inCropCfg.cropHeight = pIpPrms->wbInHeight;
    dssWbPrms->inCropCfg.cropWidth  = pIpPrms->wbInWidth;
    dssWbPrms->inCropCfg.cropStartX = pIpPrms->wbPosx;
    dssWbPrms->inCropCfg.cropStartY = pIpPrms->wbPosy;
    if ((dssWbPrms->inFmt.width != dssWbPrms->inCropCfg.cropWidth) ||
        (dssWbPrms->inFmt.height != dssWbPrms->inCropCfg.cropHeight))
    {
        dssWbPrms->outStreamInfo[0].cropEnable = TRUE;
    }
    else
    {
        dssWbPrms->outStreamInfo[0].cropEnable = FALSE;
    }

    if (SYSTEM_LINK_STATUS_SOK == retVal)
    {
        retVal = Fvid2_control(
            pInst->captureVipHandle,
            IOCTL_VPS_CAPT_SET_DSSWB_PARAMS,
            dssWbPrms,
            NULL);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
    }

    pInst->numBufs         = pDssWbInst->numBufs;

    pInst->bufferWidth     = pOpPrms->wbWidth;
    pInst->bufferHeight[0] = pOpPrms->wbHeight;
    /* assume second plane will always be for YUV420SP data format */
    pInst->bufferHeight[1] = pOpPrms->wbHeight/2U;
    pInst->bufferHeight[2] = 0U;

    pOutInfo = &pInst->vipPrms.outStreamInfo[0];

    pOutInfo->outFmt.pitch[0]   = outFrmPitch[0];
    pOutInfo->outFmt.pitch[1]   = outFrmPitch[0];
    pOutInfo->outFmt.pitch[2]   = outFrmPitch[0];
    pOutInfo->outFmt.dataFormat = pOpPrms->wbDataFmt;

    /*
     * Initialize the channel information for the next link
     */
    queChId = pObj->info.queInfo[queId].numCh;

    pQueChInfo = &pObj->info.queInfo[queId].chInfo[queChId];

    pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(
            pQueChInfo->flags,
            pOpPrms->wbDataFmt);

    pQueChInfo->width = pOpPrms->wbWidth;
    pQueChInfo->height = pOpPrms->wbHeight;

    pQueChInfo->startX      = 0;
    pQueChInfo->startY      = 0;
    pQueChInfo->pitch[0]    = pOutInfo->outFmt.pitch[0];
    pQueChInfo->pitch[1]    = pOutInfo->outFmt.pitch[1];
    pQueChInfo->pitch[2]    = pOutInfo->outFmt.pitch[2];

    pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pQueChInfo->flags,
            pOpPrms->wbScanFormat);

    pObj->info.queInfo[queId].numCh++;
    pObj->chToInstMap[queChId] = instId;

    CaptureLink_drvAllocAndQueueFrames(pObj, pInst);

    #if 0
    {
        UInt32 cnt;
        /* THis is not required any more, test and remove once confirmed */
        /* Reinitializing Channel number in the output system buffer */
        for (cnt = 0U; cnt < pInst->numBufs; cnt ++)
        {
            pInst->buffers[cnt].chNum = 0U;
        }
    }
    #endif

    return;
}


