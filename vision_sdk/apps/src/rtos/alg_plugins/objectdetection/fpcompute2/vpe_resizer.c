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
 * \file vpe_resizer.c
 *
 * \brief This implements resizer module using VPE for objdetect+fpcompute2
 *
 * \version 0.0 (May 2015) : [SS] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <ti/drv/vps/include/vpe/vps_m2m.h>
#include <ti/drv/vps/include/vps_m2mIntf.h>
#include <ti/drv/vps/include/vpe/vps_m2mVpe.h>
#include "imgPyramid_priv.h"



/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define ALG_IMG_PMD_VPE_RSZ_NORMAL_SCALE_MUL                        (256U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief VPE resizer object, contains VPE driver data structures
 *
 *******************************************************************************
*/
typedef struct
{
    FVID2_Handle fvidHandle;
    /**< VPE driver instance - FVID2 driver handle */
    FVID2_ProcessList errProcessList;
    /**< VPS error process list */
    UInt32 drvInstId;
    /**< VPE driver instance ID */

    Vps_M2mVpeParams drvChArgs[1];
    /**< VPS driver channel vise create time parameters */
    Vps_M2mCreateParams drvCreateArgs;
    /**< VPS driver create parameters */
    Vps_M2mCreateStatus drvCreateStatus;
    /**< VPS driver create status */

    Vps_M2mVpeRtParams vpeRtPrm;
    /**< Data structure used for VPE RT parameters update */

    Vps_FrameParams vpeInFrmPrms;
    /**< Structure to hold the VPE input frame RT parameters */
    Vps_FrameParams vpeRtOutFrmPrm;
    /**< Structure to hold the VPE output frame RT parameters */

    FVID2_FrameList inFrameList;
    /**< Input frame list, to hold the input frames */
    FVID2_FrameList outFrameList;
    /**< Output frame list, to hold the output frames */
    FVID2_Frame inFrame;
    /**< FVID2 frame - VPE link input side common frame */
    FVID2_Frame outFrame1;
    /**< FVID2 frame -  */
    BspOsal_SemHandle complete;
    /**< Semaphore for the VPE process complete */

    AlgorithmLink_ImgPmdObj *pImgPmdObj;
    /**< Pointer to the Image Pyramid object */
} Alg_ImgPmdVpeResizer;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

Int32 Alg_imgPmdVpeRszDrvFvidCb(FVID2_Handle handle, Ptr appData, Ptr reserved);
Int32 Alg_imgPmdVpeRszDrvFvidErrCb(FVID2_Handle handle,
                           Ptr appData, Ptr errList, Ptr reserved);
Void Alg_imgPmdVpeRszUpdatePrmsOneOutput(
    Alg_ImgPmdVpeResizer *pVpeRszObj,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc);


/* ========================================================================== */
/*                 Function Definitions                                       */
/* ========================================================================== */

/**
 *******************************************************************************
 *
 * \brief Function to create the VPE Resizer driver handle
 *
 *        Create the VPE Resizer instances.
 *        - Populates the ISP parameters and sets them
 *        - Populates the Resizer parameters and set them
 *        - Sets the other modules, isif, ipipe etc. parameters
 *
 * \param   pObj     [IN] Image Pyramid object
 *
 * \return  Handle to the resizer object
 *
 *******************************************************************************
 */
Void * Alg_imgPyramidVpeRszCreateDrv(AlgorithmLink_ImgPmdObj *pObj, Void *data)
{
    Alg_ImgPmdVpeResizer *pVpeRszObj = NULL;
    FVID2_CbParams cbParams;
    UInt32 chId;
    Int32 retVal;
    Vps_M2mVpeParams *pChParams;
    Vps_ScCoeffParams coeffPrms;
    System_LinkChInfo *pInChInfo = NULL;

    if(System_useLinkMemAllocInfo(
            &pObj->algLinkCreateParams.memAllocInfo)==FALSE)
    {
        pVpeRszObj = (Alg_ImgPmdVpeResizer *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(Alg_ImgPmdVpeResizer),
                        128);
    }
    else
    {
        pVpeRszObj = (Alg_ImgPmdVpeResizer *)
                    System_allocLinkMemAllocInfo(
                        &pObj->algLinkCreateParams.memAllocInfo,
                        sizeof(Alg_ImgPmdVpeResizer),
                        128);
    }
    UTILS_assert(pVpeRszObj!=NULL);

    /* Reset complete resizer Object */
    memset(pVpeRszObj, 0x0, sizeof(Alg_ImgPmdVpeResizer));

    pVpeRszObj->pImgPmdObj = pObj;

    /* Create semaphores */
    pVpeRszObj->complete = BspOsal_semCreate(0, (Bool)TRUE);
    UTILS_assert(pVpeRszObj->complete != NULL);


    /* Init create params */
    VpsM2mCreateParams_init(&pVpeRszObj->drvCreateArgs);
    pVpeRszObj->drvCreateArgs.numCh = 1;
    pVpeRszObj->drvCreateArgs.isDeiFmdEnable = FALSE;
    pVpeRszObj->drvCreateArgs.chInQueueLength = 4;

    pInChInfo  = &pObj->inputChInfo;
    for (chId = 0U; chId < pVpeRszObj->drvCreateArgs.numCh; chId++)
    {
        pVpeRszObj->drvInstId = VPS_M2M_INST_VPE1;

        pChParams = &pVpeRszObj->drvChArgs[chId];
        VpsM2mVpeParams_init(pChParams);

        pChParams->chNum = chId;

        pChParams->deiCfg.bypass = TRUE;
        pChParams->deiCfg.inpMode = VPE_DEI_EDIMODE_LINE_AVG;
        pChParams->deiCfg.tempInpEnable = FALSE;
        pChParams->deiCfg.tempInpChromaEnable = FALSE;
        pChParams->deiCfg.spatMaxBypass = TRUE;
        pChParams->deiCfg.tempMaxBypass = TRUE;

        pChParams->scCfg.bypass = FALSE;
        pChParams->scCfg.nonLinear = FALSE;
        pChParams->scCfg.stripSize = 0U;
        pChParams->scCfg.enablePeaking = TRUE;
        pChParams->scCfg.enableEdgeDetect = TRUE;
        pChParams->scCfg.advCfg = NULL;

        pChParams->outFmt.width  = pInChInfo->width;
        pChParams->outFmt.height = pInChInfo->height;
        pChParams->outFmt.fieldMerged[0] = FALSE;
        pChParams->outFmt.fieldMerged[1] = FALSE;
        pChParams->outFmt.fieldMerged[2] = FALSE;
        pChParams->outFmt.pitch[0] = pInChInfo->pitch[0];
        pChParams->outFmt.pitch[1] = pInChInfo->pitch[1];
        pChParams->outFmt.pitch[2] = pInChInfo->pitch[2];
        pChParams->outFmt.dataFormat =
            System_Link_Ch_Info_Get_Flag_Data_Format(pInChInfo->flags);
        pChParams->outFmt.dataFormat =
            System_Link_Ch_Info_Get_Flag_Data_Format(pInChInfo->flags);
        pChParams->outFmt.scanFormat = FVID2_SF_PROGRESSIVE;
        pChParams->outFmt.bpp = FVID2_BPP_BITS16;

        pChParams->inFmt.width  = pInChInfo->width;
        pChParams->inFmt.height = pInChInfo->height;
        pChParams->inFmt.fieldMerged[0] = FALSE;
        pChParams->inFmt.fieldMerged[1] = FALSE;
        pChParams->inFmt.fieldMerged[2] = FALSE;
        pChParams->inFmt.pitch[0] = pInChInfo->pitch[0];
        pChParams->inFmt.pitch[1] = pInChInfo->pitch[1];
        pChParams->inFmt.pitch[2] = pInChInfo->pitch[2];
        pChParams->inFmt.dataFormat =
            System_Link_Ch_Info_Get_Flag_Data_Format(pInChInfo->flags);
        pChParams->inFmt.dataFormat =
            System_Link_Ch_Info_Get_Flag_Data_Format(pInChInfo->flags);
        pChParams->inFmt.scanFormat = FVID2_SF_PROGRESSIVE;
        pChParams->inFmt.bpp = FVID2_BPP_BITS16;

        pChParams->inMemType =
            System_Link_Ch_Info_Get_Flag_Mem_Type(pInChInfo->flags);
        pChParams->outMemType = VPS_VPDMA_MT_NONTILEDMEM;

    }

    memset(&cbParams, 0, sizeof(cbParams));
    cbParams.cbFxn    = &Alg_imgPmdVpeRszDrvFvidCb;
    cbParams.errCbFxn = &Alg_imgPmdVpeRszDrvFvidErrCb;
    cbParams.errList  = &pVpeRszObj->errProcessList;
    cbParams.appData  = pVpeRszObj;

    pVpeRszObj->fvidHandle = FVID2_create(FVID2_VPS_M2M_DRV,
                                    pVpeRszObj->drvInstId,
                                    &pVpeRszObj->drvCreateArgs,
                                    &pVpeRszObj->drvCreateStatus, &cbParams);
    UTILS_assert(pVpeRszObj->fvidHandle != NULL);

    /* Set VPE params for each channel */
    for (chId = 0U; chId < pVpeRszObj->drvCreateArgs.numCh; chId++)
    {
        retVal = Fvid2_control(pVpeRszObj->fvidHandle,
                               IOCTL_VPS_M2M_SET_VPE_PARAMS,
                               &pVpeRszObj->drvChArgs[chId], NULL);

        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
    }

    VpsScCoeffParams_init(&coeffPrms);
    coeffPrms.scalerId    = VPS_M2M_VPE_SCALER_ID_SC0;
    coeffPrms.hScalingSet = VPS_SC_DS_SET_8_16;
    coeffPrms.vScalingSet = VPS_SC_DS_SET_8_16;
    /* Program VPE scalar coefficient - Always used */
    retVal = FVID2_control(pVpeRszObj->fvidHandle,
                           IOCTL_VPS_SET_COEFFS, &coeffPrms, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

    /* Initialize Frame List, ProcessList and Fvid2_Frame */
    Fvid2FrameList_init(&pVpeRszObj->inFrameList);
    Fvid2FrameList_init(&pVpeRszObj->outFrameList);
    Fvid2Frame_init(&pVpeRszObj->inFrame);
    Fvid2Frame_init(&pVpeRszObj->outFrame1);

    pVpeRszObj->inFrameList.frames[0] =
        &pVpeRszObj->inFrame;
    pVpeRszObj->outFrameList.frames[0] =
        &pVpeRszObj->outFrame1;

    pVpeRszObj->inFrameList.numFrames = 1;
    pVpeRszObj->outFrameList.numFrames = 1;

    return pVpeRszObj;
}

/**
 *******************************************************************************
 *
 * \brief Function to delete the VPE Resizer driver handle
 *
 *       - Closes driver handle, deletes objects
 *
 * \param   pObj     [IN] Resizer driver handle object
 *
 * \return  None
 *
 *******************************************************************************
 */
Void Alg_imgPyramidVpeRszDeleteDrv(Void *pObj, Void *data)
{
    Int32 status;
    Alg_ImgPmdVpeResizer *pVpeRszObj = NULL;
    AlgorithmLink_ImgPmdObj *pImgPmd;

    pVpeRszObj = (Alg_ImgPmdVpeResizer *)pObj;
    UTILS_assert(NULL != pVpeRszObj);
    pImgPmd = pVpeRszObj->pImgPmdObj;
    UTILS_assert(NULL != pImgPmd);

    status = FVID2_delete(pVpeRszObj->fvidHandle, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* Delete semaphores */
    BspOsal_semDelete(&pVpeRszObj->complete);

    if(System_useLinkMemAllocInfo(
            &pImgPmd->algLinkCreateParams.memAllocInfo)==FALSE)
    {
        status = Utils_memFree(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        pVpeRszObj,
                        sizeof(Alg_ImgPmdVpeResizer));
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

        pImgPmd->pRszObj = NULL;
    }
}

/**
 *******************************************************************************
 *
 * \brief Function to delete the VPE Resizer driver handle
 *
 *       - Closes driver handle, deletes objects
 *
 * \param   pObj     [IN] Resizer driver handle object
 *
 * \return  None
 *
 *******************************************************************************
 */
Void Alg_imgPyramidVpeRszProcessFrame(
    Void *pObj,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc1,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc1,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc2,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc2,
    Void *data)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Alg_ImgPmdVpeResizer *pVpeRszObj = NULL;
    UInt32 procCnt;
    Vps_M2mVpeParams *pChParams;
    AlgorithmLink_ImgPyramidFrameDesc * curInFrmDesc;
    AlgorithmLink_ImgPyramidFrameDesc * curOutFrmDesc;
    FVID2_ProcessList inProcessList;
    FVID2_ProcessList outProcessList;

    /* Error checking,
       Both the input and output frame descriptors must not be null */
    if (((NULL == inFrmDesc1) && (NULL != outFrmDesc1)) ||
        ((NULL != inFrmDesc1) && (NULL == outFrmDesc1)))
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else if (((NULL == inFrmDesc2) && (NULL != outFrmDesc2)) ||
             ((NULL != inFrmDesc2) && (NULL == outFrmDesc2)))
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else if ((NULL == inFrmDesc1) && (NULL == outFrmDesc1) &&
             (NULL == inFrmDesc2) && (NULL == outFrmDesc2))
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        status = SYSTEM_LINK_STATUS_SOK;
    }

    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    pVpeRszObj = (Alg_ImgPmdVpeResizer *)pObj;

    for(procCnt = 0; procCnt < 2U; procCnt++)
    {
        UInt32 skip = 0;
        if(0 == procCnt)
        {
            if (NULL != inFrmDesc1)
            {
                Alg_imgPmdVpeRszUpdatePrmsOneOutput(pVpeRszObj,
                    inFrmDesc1, outFrmDesc1);
                curInFrmDesc = inFrmDesc1;
                curOutFrmDesc = outFrmDesc1;
            }
        }
        else if(1 == procCnt)
        {
            if (NULL != inFrmDesc2)
            {
                Alg_imgPmdVpeRszUpdatePrmsOneOutput(pVpeRszObj,
                    inFrmDesc2, outFrmDesc2);
                curInFrmDesc = inFrmDesc2;
                curOutFrmDesc = outFrmDesc2;
            }
        }
        else
        {
            skip = 1;
        }

        if(0 == skip)
        {
            /* Set VPE params for each channel */
            pChParams = &pVpeRszObj->drvChArgs[0];

            inProcessList.inFrameList[0]  = &pVpeRszObj->inFrameList;
            inProcessList.outFrameList[0] = &pVpeRszObj->outFrameList;
            inProcessList.numInLists  = 1U;
            inProcessList.numOutLists = 1U;
            pVpeRszObj->inFrameList.appData = pVpeRszObj;

            pVpeRszObj->vpeRtPrm.deiRtCfg              = NULL;
            pVpeRszObj->vpeRtPrm.scCropCfg             = NULL;
            pVpeRszObj->vpeRtPrm.scRtCfg               = NULL;

            pVpeRszObj->vpeRtPrm.inFrmPrms             = &pVpeRszObj->vpeInFrmPrms;
            pVpeRszObj->vpeRtPrm.inFrmPrms->width      = curInFrmDesc->width;
            pVpeRszObj->vpeRtPrm.inFrmPrms->height     = curInFrmDesc->height;
            pVpeRszObj->vpeRtPrm.inFrmPrms->pitch[0]   = curInFrmDesc->pitch[0];
            pVpeRszObj->vpeRtPrm.inFrmPrms->pitch[1]   = curInFrmDesc->pitch[1];
            pVpeRszObj->vpeRtPrm.inFrmPrms->pitch[2]   = curInFrmDesc->pitch[2];
            pVpeRszObj->vpeRtPrm.inFrmPrms->dataFormat = pChParams->outFmt.dataFormat;
            pVpeRszObj->vpeRtPrm.inFrmPrms->memType    = VPS_VPDMA_MT_NONTILEDMEM;

            pVpeRszObj->vpeRtPrm.outFrmPrms             = &pVpeRszObj->vpeRtOutFrmPrm;
            pVpeRszObj->vpeRtPrm.outFrmPrms->width      = curOutFrmDesc->width;
            pVpeRszObj->vpeRtPrm.outFrmPrms->height     = curOutFrmDesc->height;
            pVpeRszObj->vpeRtPrm.outFrmPrms->pitch[0]   = curOutFrmDesc->pitch[0];
            pVpeRszObj->vpeRtPrm.outFrmPrms->pitch[1]   = curOutFrmDesc->pitch[1];
            pVpeRszObj->vpeRtPrm.outFrmPrms->pitch[2]   = curOutFrmDesc->pitch[2];
            pVpeRszObj->vpeRtPrm.outFrmPrms->dataFormat = pChParams->outFmt.dataFormat;
            pVpeRszObj->vpeRtPrm.outFrmPrms->memType    = VPS_VPDMA_MT_NONTILEDMEM;

            pVpeRszObj->inFrameList.frames[0]->perFrameCfg =
                &pVpeRszObj->vpeRtPrm;
            pVpeRszObj->outFrameList.frames[0]->perFrameCfg =
                &pVpeRszObj->vpeRtPrm;

            status = FVID2_processFrames(
                pVpeRszObj->fvidHandle,
                &inProcessList);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            BspOsal_semWait(pVpeRszObj->complete, BSP_OSAL_WAIT_FOREVER);

            status = FVID2_getProcessedFrames(
                pVpeRszObj->fvidHandle,
                &outProcessList,
                BSP_OSAL_NO_WAIT);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

Int32 Alg_imgPmdVpeRszDrvFvidCb(FVID2_Handle handle, Ptr appData, Ptr reserved)
{
    Alg_ImgPmdVpeResizer *pVpeRszObj = (Alg_ImgPmdVpeResizer *)appData;

    BspOsal_semPost(pVpeRszObj->complete);

    UTILS_assert(NULL != pVpeRszObj->pImgPmdObj);
    UTILS_assert(NULL != pVpeRszObj->pImgPmdObj->linkStatsInfo);

    pVpeRszObj->pImgPmdObj->linkStatsInfo->linkStats.notifyEventCount++;

    return SYSTEM_LINK_STATUS_SOK;
}


Int32 Alg_imgPmdVpeRszDrvFvidErrCb(FVID2_Handle handle,
                           Ptr appData, Ptr errList, Ptr reserved)
{
    return SYSTEM_LINK_STATUS_SOK;
}

Void Alg_imgPmdVpeRszUpdatePrmsOneOutput(
    Alg_ImgPmdVpeResizer *pVpeRszObj,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc)
{
    pVpeRszObj->inFrame.addr[0][0] = inFrmDesc->bufAddr[0];
    pVpeRszObj->inFrame.addr[0][1] = inFrmDesc->bufAddr[1];
    pVpeRszObj->inFrame.addr[0][2] = inFrmDesc->bufAddr[2];

    pVpeRszObj->outFrame1.addr[0][0] = outFrmDesc->bufAddr[0];
    pVpeRszObj->outFrame1.addr[0][1] = outFrmDesc->bufAddr[1];
    pVpeRszObj->outFrame1.addr[0][2] = outFrmDesc->bufAddr[2];

    pVpeRszObj->inFrame.addr[0][0] =
        (Ptr)((UInt32)pVpeRszObj->inFrame.addr[0][0] +
        inFrmDesc->pitch[0] * inFrmDesc->startY + inFrmDesc->startX);
    pVpeRszObj->inFrame.addr[0][1] =
        (Ptr)((UInt32)pVpeRszObj->inFrame.addr[0][1] +
        inFrmDesc->pitch[1] * (inFrmDesc->startY / 2) + inFrmDesc->startX);
}

