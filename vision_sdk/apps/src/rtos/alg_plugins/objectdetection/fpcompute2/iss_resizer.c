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
 * \file iss_resizer.c
 *
 * \brief This implements resizer module using ISS for objdetect+fpcompute2
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
#include <ti/drv/vps/include/iss/vps_m2mIss.h>
#include "imgPyramid_priv.h"



/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define ALG_IMG_PMD_ISS_RSZ_NORMAL_SCALE_MUL                        (256U)

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
 *   \brief ISS resizer object, contains ISS driver data structures
 *
 *******************************************************************************
*/
typedef struct
{
    FVID2_Handle fvidHandle;
    /**< VPE/ISS driver instance - FVID2 driver handle */
    FVID2_ProcessList errProcessList;
    /**< VPS error process list */

    Vps_M2mIntfCreateParams drvCreatePrms;
    /**< Create Parameters */
    Vps_M2mIntfCreateStatus drvCreateStatusPrms;
    /**< Create Status Parameters */
    vpsissIspOpenParams_t drvOpenPrms;
    /**< Core Open Parameters */
    vpsissIspOpenRetParams_t drvRetPrms;
    /**< Core Returns Parameters */
    Vps_M2mIntfStats drvStats;
    /**< Core Status */

    vpsissIspParams_t drvIspPrms;
    /**< VPS driver channel wise ISP parameters */
    vpsissRszCfg_t drvRszCfg;
    /**< VPS driver channel wise Re-sizer configuration parameters */
    vpsissIpipeInConfig_t drvIpipeInputCfg;
    /**< VPS driver channel wise Ipipe Input configuration parameters */
    vpsissIsifBlackClampConfig_t isifBlkClampCfg;
    /**< ISIF Black Clamping Configuration */

    FVID2_FrameList inFrameList;
    /**< Input frame list, to hold the input frames */
    FVID2_FrameList outFrameList;
    /**< Output frame list, to hold the output frames */
    FVID2_Frame inFrame;
    /**< FVID2 frame - VPE link input side common frame */
    FVID2_Frame outFrame1;
    /**< FVID2 frame -  */
    FVID2_Frame outFrame2;
    /**< FVID2 frame -  */
    BspOsal_SemHandle complete;
    /**< Semaphore for the VPE process complete */

    AlgorithmLink_ImgPmdObj *pImgPmdObj;
    /**< Pointer to the Image Pyramid object */
} Alg_ImgPmdIssResizer;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

Int32 Alg_imgPmdIssRszDrvFvidCb(FVID2_Handle handle, Ptr appData, Ptr reserved);
Int32 Alg_imgPmdIssRszDrvFvidErrCb(FVID2_Handle handle,
                           Ptr appData, Ptr errList, Ptr reserved);
Int32 Alg_imgPmdIssRszSetIspPrms(AlgorithmLink_ImgPmdObj * pImgPmdObj,
    Alg_ImgPmdIssResizer *pIssRszObj);
Int32 Alg_imgPmdIssRszSetRszPrms(AlgorithmLink_ImgPmdObj * pImgPmdObj,
    Alg_ImgPmdIssResizer *pIssRszObj);
Void Alg_imgPmdIssRszUpdatePrmsTwoOutputs(
    Alg_ImgPmdIssResizer *pIssRszObj,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc1,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc1,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc2,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc2);
Void Alg_imgPmdIssRszUpdatePrmsOneOutput(
    Alg_ImgPmdIssResizer *pIssRszObj,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc);


/* ========================================================================== */
/*                 Function Definitions                                       */
/* ========================================================================== */

/**
 *******************************************************************************
 *
 * \brief Function to create the ISS Resizer driver handle
 *
 *        Create the ISS Resizer instances.
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
Void * Alg_imgPyramidIssRszCreateDrv(AlgorithmLink_ImgPmdObj *pObj, Void *data)
{
    Alg_ImgPmdIssResizer *pIssRszObj = NULL;
    FVID2_CbParams cbParams;

    if(System_useLinkMemAllocInfo(
            &pObj->algLinkCreateParams.memAllocInfo)==FALSE)
    {
        pIssRszObj = (Alg_ImgPmdIssResizer *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(Alg_ImgPmdIssResizer),
                        128);
    }
    else
    {
        pIssRszObj = (Alg_ImgPmdIssResizer *)
                    System_allocLinkMemAllocInfo(
                        &pObj->algLinkCreateParams.memAllocInfo,
                        sizeof(Alg_ImgPmdIssResizer),
                        128);
    }
    UTILS_assert(pIssRszObj!=NULL);

    /* Reset complete resizer Object */
    memset(pIssRszObj, 0x0, sizeof(Alg_ImgPmdIssResizer));

    pIssRszObj->pImgPmdObj = pObj;

    /* Create semaphores */
    pIssRszObj->complete = BspOsal_semCreate(0, (Bool)TRUE);
    UTILS_assert(pIssRszObj->complete != NULL);

    Fvid2CbParams_init(&cbParams);
    cbParams.cbFxn    = &Alg_imgPmdIssRszDrvFvidCb;
    cbParams.errCbFxn = &Alg_imgPmdIssRszDrvFvidErrCb;
    cbParams.errList  = &pIssRszObj->errProcessList;
    cbParams.appData  = pIssRszObj;

    VpsM2mIntfCreateParams_init(&pIssRszObj->drvCreatePrms);
    pIssRszObj->drvCreatePrms.numCh           = 1U;
    pIssRszObj->drvCreatePrms.chInQueueLength = 4;
    pIssRszObj->drvCreatePrms.maxStatsInst    = 0U;
    pIssRszObj->drvCreatePrms.pAdditionalArgs = (Ptr) & pIssRszObj->drvOpenPrms;

    VpsM2mIntfCreateStatus_init(&pIssRszObj->drvCreateStatusPrms);
    pIssRszObj->drvCreateStatusPrms.pAdditionalStatus =
        (Ptr) & pIssRszObj->drvRetPrms;

    pIssRszObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPEIF] = TRUE;
    pIssRszObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_NSF3]    = FALSE;
    pIssRszObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_GLBCE]   = FALSE;
    pIssRszObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_ISIF]    = TRUE;
    pIssRszObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPE]   = FALSE;
    pIssRszObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_RSZ]     = TRUE;
    pIssRszObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_CNF]     = FALSE;
    pIssRszObj->drvOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_H3A]     = FALSE;
    pIssRszObj->drvOpenPrms.arg = NULL;

    pIssRszObj->fvidHandle = Fvid2_create(
        FVID2_VPS_COMMON_M2M_INTF_DRV,
        VPS_M2M_ISS_INST_CAL_ISP,
        &pIssRszObj->drvCreatePrms,
        &pIssRszObj->drvCreateStatusPrms,
        &cbParams);

    UTILS_assert(NULL != pIssRszObj->fvidHandle);

    Alg_imgPmdIssRszSetIspPrms(pObj, pIssRszObj);
    Alg_imgPmdIssRszSetRszPrms(pObj, pIssRszObj);

    /* Initialize Frame List, ProcessList and Fvid2_Frame */
    Fvid2FrameList_init(&pIssRszObj->inFrameList);
    Fvid2FrameList_init(&pIssRszObj->outFrameList);
    Fvid2Frame_init(&pIssRszObj->inFrame);
    Fvid2Frame_init(&pIssRszObj->outFrame1);
    Fvid2Frame_init(&pIssRszObj->outFrame2);

    pIssRszObj->inFrameList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] =
        &pIssRszObj->inFrame;
    pIssRszObj->outFrameList.frames[VPS_ISS_STREAM_ID_RSZ_A] =
        &pIssRszObj->outFrame1;
    pIssRszObj->outFrameList.frames[VPS_ISS_STREAM_ID_RSZ_B] =
        &pIssRszObj->outFrame2;

    pIssRszObj->inFrameList.numFrames = VPS_ISS_STREAM_ID_MAX;
    pIssRszObj->outFrameList.numFrames = VPS_ISS_STREAM_ID_MAX;

    return pIssRszObj;
}

/**
 *******************************************************************************
 *
 * \brief Function to delete the ISS Resizer driver handle
 *
 *       - Closes driver handle, deletes objects
 *
 * \param   pObj     [IN] Resizer driver handle object
 *
 * \return  None
 *
 *******************************************************************************
 */
Void Alg_imgPyramidIssRszDeleteDrv(Void *pObj, Void *data)
{
    Int32 status;
    Alg_ImgPmdIssResizer *pIssRszObj = NULL;
    AlgorithmLink_ImgPmdObj *pImgPmd;

    pIssRszObj = (Alg_ImgPmdIssResizer *)pObj;
    UTILS_assert(NULL != pIssRszObj);
    pImgPmd = pIssRszObj->pImgPmdObj;
    UTILS_assert(NULL != pImgPmd);

    status = FVID2_delete(pIssRszObj->fvidHandle, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* Delete semaphores */
    BspOsal_semDelete(&pIssRszObj->complete);

    if(System_useLinkMemAllocInfo(
            &pImgPmd->algLinkCreateParams.memAllocInfo)==FALSE)
    {
        status = Utils_memFree(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        pIssRszObj,
                        sizeof(Alg_ImgPmdIssResizer));
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

        pImgPmd->pRszObj = NULL;
    }
}

/**
 *******************************************************************************
 *
 * \brief Function to delete the ISS Resizer driver handle
 *
 *       - Closes driver handle, deletes objects
 *
 * \param   pObj     [IN] Resizer driver handle object
 *
 * \return  None
 *
 *******************************************************************************
 */
Void Alg_imgPyramidIssRszProcessFrame(
    Void *pObj,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc1,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc1,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc2,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc2,
    Void *data)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Alg_ImgPmdIssResizer *pIssRszObj = NULL;

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

    pIssRszObj = (Alg_ImgPmdIssResizer *)pObj;

    #ifdef ISS_INCLUDE
    Utils_pendIspLock();
    #endif

    if ((NULL != inFrmDesc1) && (NULL != inFrmDesc2))
    {
        Alg_imgPmdIssRszUpdatePrmsTwoOutputs(pIssRszObj, inFrmDesc1,
            outFrmDesc1, inFrmDesc2, outFrmDesc2);
    }
    else if (NULL != inFrmDesc1)
    {
        Alg_imgPmdIssRszUpdatePrmsOneOutput(pIssRszObj,
            inFrmDesc1, outFrmDesc1);
    }
    else
    {
        Alg_imgPmdIssRszUpdatePrmsOneOutput(pIssRszObj,
            inFrmDesc2, outFrmDesc2);
    }


    status = Fvid2_processRequest(
        pIssRszObj->fvidHandle,
        &pIssRszObj->inFrameList,
        &pIssRszObj->outFrameList);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    BspOsal_semWait(pIssRszObj->complete, BSP_OSAL_WAIT_FOREVER);

    status = Fvid2_getProcessedRequest(
        pIssRszObj->fvidHandle,
        &pIssRszObj->inFrameList,
        &pIssRszObj->outFrameList,
        BSP_OSAL_NO_WAIT);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    #ifdef ISS_INCLUDE
    Utils_postIspLock();
    #endif
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

Int32 Alg_imgPmdIssRszDrvFvidCb(FVID2_Handle handle, Ptr appData, Ptr reserved)
{
    Alg_ImgPmdIssResizer *pIssRszObj = (Alg_ImgPmdIssResizer *)appData;

    BspOsal_semPost(pIssRszObj->complete);

    UTILS_assert(NULL != pIssRszObj->pImgPmdObj);
    UTILS_assert(NULL != pIssRszObj->pImgPmdObj->linkStatsInfo);

    pIssRszObj->pImgPmdObj->linkStatsInfo->linkStats.notifyEventCount++;

    return SYSTEM_LINK_STATUS_SOK;
}


Int32 Alg_imgPmdIssRszDrvFvidErrCb(FVID2_Handle handle,
                           Ptr appData, Ptr errList, Ptr reserved)
{
    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Function to create the isp params for given channel
 *
 * \param   pObj     [IN] VPE Link Instance handle
 * \param   chId     [IN] channel number
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 Alg_imgPmdIssRszSetIspPrms(AlgorithmLink_ImgPmdObj * pImgPmdObj,
    Alg_ImgPmdIssResizer *pIssRszObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_LinkChInfo *pInChInfo = NULL;

    pInChInfo = &pImgPmdObj->inputChInfo;

    /* Set the ISP Params */
    pIssRszObj->drvIspPrms.inFmt.width         = pInChInfo->width;
    pIssRszObj->drvIspPrms.inFmt.height        = pInChInfo->height;
    pIssRszObj->drvIspPrms.inFmt.pitch[0U]     = pInChInfo->pitch[0];
    pIssRszObj->drvIspPrms.inFmt.pitch[1U]     = pInChInfo->pitch[1];
    pIssRszObj->drvIspPrms.inFmt.pitch[2U]     = pInChInfo->pitch[2];
    pIssRszObj->drvIspPrms.inFmt.bpp           = SYSTEM_BPP_BITS16; /* For both 420SP and 422I */
    pIssRszObj->drvIspPrms.inFmt.dataFormat    =
        System_Link_Ch_Info_Get_Flag_Data_Format(pInChInfo->flags);

    /* N_1 frame settings are redundant */
    memcpy(&pIssRszObj->drvIspPrms.inFmtN_1,
        &pIssRszObj->drvIspPrms.inFmt, sizeof(Fvid2_Format));

    pIssRszObj->drvIspPrms.enableWdrMerge            = FALSE;
    pIssRszObj->drvIspPrms.enableVportCompInput      = FALSE;
    pIssRszObj->drvIspPrms.enableDfs                 = FALSE;
    pIssRszObj->drvIspPrms.glbcePath                 = VPS_ISS_GLBCE_PATH_DISABLED;
    pIssRszObj->drvIspPrms.nsf3Path                  = VPS_ISS_NSF3_PATH_DISABLED;
    pIssRszObj->drvIspPrms.enableDpcPreNsf3          = FALSE;
    pIssRszObj->drvIspPrms.enableCnf                 = FALSE;
    pIssRszObj->drvIspPrms.enableRszInputFromIpipeif = TRUE;

    pIssRszObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_CAL_RD_INPUT_0] = TRUE;
    pIssRszObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_A]       = TRUE;
    pIssRszObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_INPUT_N1]    = FALSE;
    pIssRszObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B]       = TRUE;
    pIssRszObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_AF]          = FALSE;
    pIssRszObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_AEWB]        = FALSE;

    pIssRszObj->drvIspPrms.useWen = FALSE;
    pIssRszObj->drvIspPrms.hdPol  = FVID2_POL_HIGH;
    pIssRszObj->drvIspPrms.vdPol  = FVID2_POL_HIGH;

    status = Fvid2_control(
        pIssRszObj->fvidHandle,
        IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS,
        &pIssRszObj->drvIspPrms,
        NULL);
    UTILS_assert(status == FVID2_SOK);

    return status;
}

Int32 Alg_imgPmdIssRszSetRszPrms(AlgorithmLink_ImgPmdObj * pImgPmdObj,
    Alg_ImgPmdIssResizer *pIssRszObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i;
    vpsissRszCtrl_t rszCtrl;
    vpsissIsifCtrl_t isifCtrl;
    System_LinkChInfo *pInChInfo = NULL;

    pInChInfo  = &pImgPmdObj->inputChInfo;

    memset(&rszCtrl, 0x0, sizeof (vpsissRszCtrl_t));
    memset(&pIssRszObj->drvRszCfg,
           0x0,
           sizeof (vpsissRszCfg_t));

    rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
    rszCtrl.rszCfg = &pIssRszObj->drvRszCfg;

    status = Fvid2_control(
        pIssRszObj->fvidHandle,
        VPS_ISS_RSZ_IOCTL_GET_CONFIG,
        &rszCtrl,
        NULL);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pIssRszObj->drvRszCfg.inCfg.opMode = VPS_ISS_RSZ_OP_MODE_RESIZING;
    pIssRszObj->drvRszCfg.inCfg.procWin.cropStartX = 0U;
    pIssRszObj->drvRszCfg.inCfg.procWin.cropStartY = 0U;
    pIssRszObj->drvRszCfg.inCfg.procWin.cropWidth  = pInChInfo->width;
    pIssRszObj->drvRszCfg.inCfg.procWin.cropHeight = pInChInfo->height;

    for (i = 0; i < 2; i ++)
    {
        pIssRszObj->drvRszCfg.instCfg[i].enable = TRUE;

        pIssRszObj->drvRszCfg.instCfg[i].outFmt.dataFormat =
            System_Link_Ch_Info_Get_Flag_Data_Format(pInChInfo->flags);

        pIssRszObj->drvRszCfg.instCfg[i].outFmt.width      = pInChInfo->width;
        pIssRszObj->drvRszCfg.instCfg[i].outFmt.height     = pInChInfo->height;
        pIssRszObj->drvRszCfg.instCfg[i].outFmt.pitch[0U]  = pInChInfo->pitch[0];
        pIssRszObj->drvRszCfg.instCfg[i].outFmt.pitch[1U]  = pInChInfo->pitch[1];
        pIssRszObj->drvRszCfg.instCfg[i].outFmt.pitch[2U]  = pInChInfo->pitch[2];

        pIssRszObj->drvRszCfg.instCfg[i].flipCtrl =
            VPS_ISS_RSZ_STR_MODE_NORMAL;
        pIssRszObj->drvRszCfg.instCfg[i].startPos.startX = 0U;
        pIssRszObj->drvRszCfg.instCfg[i].startPos.startY = 0U;
        pIssRszObj->drvRszCfg.instCfg[i].scaleMode       =
            VPS_ISS_RSZ_SCALE_MODE_NORMAL;
        pIssRszObj->drvRszCfg.instCfg[i].filtCfg.horzLumaFilter =
            VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
        pIssRszObj->drvRszCfg.instCfg[i].filtCfg.vertLumaFilter =
            VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
        pIssRszObj->drvRszCfg.instCfg[i].filtCfg.horzChromaFilter =
            VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
        pIssRszObj->drvRszCfg.instCfg[i].filtCfg.vertChromaFilter =
            VPS_ISS_RSZ_FILTER_4TAP_CUBIC;

        pIssRszObj->drvRszCfg.instCfg[i].intensityCfg.horzLumaIntensity   = 21u;
        pIssRszObj->drvRszCfg.instCfg[i].intensityCfg.horzChromaIntensity = 22u;
        pIssRszObj->drvRszCfg.instCfg[i].intensityCfg.vertLumaIntensity   = 14u;
        pIssRszObj->drvRszCfg.instCfg[i].intensityCfg.vertChromaIntensity = 15u;
    }

    status = Fvid2_control(
        pIssRszObj->fvidHandle,
        VPS_ISS_RSZ_IOCTL_SET_CONFIG,
        &rszCtrl,
        NULL);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pIssRszObj->isifBlkClampCfg.dcOffset = 0x0;
    isifCtrl.module = VPS_ISS_ISIF_MODULE_BLACK_CLAMP;
    isifCtrl.blkClampCfg  = &pIssRszObj->isifBlkClampCfg;
    status = Fvid2_control(
        pIssRszObj->fvidHandle,
        VPS_ISS_ISIF_IOCTL_SET_CONFIG,
        &isifCtrl,
        NULL);
    UTILS_assert(status == FVID2_SOK);

    return status;
}

Void Alg_imgPmdIssRszUpdatePrmsTwoOutputs(
    Alg_ImgPmdIssResizer *pIssRszObj,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc1,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc1,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc2,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc2)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    vpsissRszCtrl_t rszCtrl;

    /* Updated new isp parameters,
       Here the assumption is that the output frame descriptor2 will
       always be of higher size, so output frame descriptor2 is
       considered to be super set of both the frame descriptor */
    pIssRszObj->drvIspPrms.inFmt.width     = inFrmDesc2->width;
    pIssRszObj->drvIspPrms.inFmt.height    = inFrmDesc2->height;
    pIssRszObj->drvIspPrms.inFmt.pitch[0U] = inFrmDesc2->pitch[0];
    pIssRszObj->drvIspPrms.inFmt.pitch[1U] = inFrmDesc2->pitch[1];
    pIssRszObj->drvIspPrms.inFmt.pitch[2U] = inFrmDesc2->pitch[2];

    /* Since this api generates two outputs, both the resizers are enabled */
    pIssRszObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_A] = TRUE;
    pIssRszObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B] = TRUE;

    status = Fvid2_control(
        pIssRszObj->fvidHandle,
        IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS,
        &pIssRszObj->drvIspPrms,
        NULL);
    UTILS_assert(status == FVID2_SOK);

    /* Update Resizer parameters */
    pIssRszObj->drvRszCfg.inCfg.procWin.cropStartX = 0U;
    pIssRszObj->drvRszCfg.inCfg.procWin.cropStartY = 0U;
    pIssRszObj->drvRszCfg.inCfg.procWin.cropWidth  = inFrmDesc2->width;
    pIssRszObj->drvRszCfg.inCfg.procWin.cropHeight = inFrmDesc2->height;

    /* Resizer A outputs frames for frame descriptor1 */
    pIssRszObj->drvRszCfg.instCfg[0U].enable = TRUE;
    pIssRszObj->drvRszCfg.instCfg[0U].outFmt.width      = outFrmDesc1->width;
    pIssRszObj->drvRszCfg.instCfg[0U].outFmt.height     = outFrmDesc1->height;
    pIssRszObj->drvRszCfg.instCfg[0U].outFmt.pitch[0U]  = outFrmDesc1->pitch[0];
    pIssRszObj->drvRszCfg.instCfg[0U].outFmt.pitch[1U]  = outFrmDesc1->pitch[1];
    pIssRszObj->drvRszCfg.instCfg[0U].outFmt.pitch[2U]  = outFrmDesc1->pitch[2];

    pIssRszObj->drvRszCfg.instCfg[0U].overrideScaleFactor = FALSE;
    if (TRUE == pIssRszObj->pImgPmdObj->algLinkCreateParams.enableRoi)
    {
        if (0U == inFrmDesc2->startY)
        {
            pIssRszObj->drvRszCfg.instCfg[0U].startPos.startY =
                inFrmDesc1->startY;
        }
        else
        {
            pIssRszObj->drvRszCfg.instCfg[0U].startPos.startY =
                inFrmDesc1->startY - inFrmDesc2->startY;
        }

        if (0U == inFrmDesc2->startX)
        {
            pIssRszObj->drvRszCfg.instCfg[0U].startPos.startX =
                inFrmDesc1->startX;
        }
        else
        {
            pIssRszObj->drvRszCfg.instCfg[0U].startPos.startX =
                inFrmDesc1->startX - inFrmDesc2->startX;
        }

        pIssRszObj->drvRszCfg.instCfg[0U].overrideScaleFactor = TRUE;

        pIssRszObj->drvRszCfg.instCfg[0U].hRatio =
            (ALG_IMG_PMD_ISS_RSZ_NORMAL_SCALE_MUL * inFrmDesc1->width) /
                outFrmDesc1->width;
        pIssRszObj->drvRszCfg.instCfg[0U].vRatio =
            (ALG_IMG_PMD_ISS_RSZ_NORMAL_SCALE_MUL * inFrmDesc1->height) /
                outFrmDesc1->height;
    }

    pIssRszObj->drvRszCfg.instCfg[1U].enable = TRUE;
    pIssRszObj->drvRszCfg.instCfg[1U].outFmt.width      = outFrmDesc2->width;
    pIssRszObj->drvRszCfg.instCfg[1U].outFmt.height     = outFrmDesc2->height;
    pIssRszObj->drvRszCfg.instCfg[1U].outFmt.pitch[0U]  = outFrmDesc2->pitch[0];
    pIssRszObj->drvRszCfg.instCfg[1U].outFmt.pitch[1U]  = outFrmDesc2->pitch[1];
    pIssRszObj->drvRszCfg.instCfg[1U].outFmt.pitch[2U]  = outFrmDesc2->pitch[2];
    pIssRszObj->drvRszCfg.instCfg[1U].overrideScaleFactor = FALSE;

    rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
    rszCtrl.rszCfg = &pIssRszObj->drvRszCfg;
    status = Fvid2_control(
        pIssRszObj->fvidHandle,
        VPS_ISS_RSZ_IOCTL_SET_CONFIG,
        &rszCtrl,
        NULL);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Assuming input frame address is same in both the input
       frame descriptors */
    pIssRszObj->inFrame.addr[0][0] = inFrmDesc2->bufAddr[0];
    pIssRszObj->inFrame.addr[0][1] = inFrmDesc2->bufAddr[1];
    pIssRszObj->inFrame.addr[0][2] = inFrmDesc2->bufAddr[2];

    pIssRszObj->outFrame1.addr[0][0] = outFrmDesc1->bufAddr[0];
    pIssRszObj->outFrame1.addr[0][1] = outFrmDesc1->bufAddr[1];
    pIssRszObj->outFrame1.addr[0][2] = outFrmDesc1->bufAddr[2];

    pIssRszObj->outFrame2.addr[0][0] = outFrmDesc2->bufAddr[0];
    pIssRszObj->outFrame2.addr[0][1] = outFrmDesc2->bufAddr[1];
    pIssRszObj->outFrame2.addr[0][2] = outFrmDesc2->bufAddr[2];

    /* update the frame address to point to start location
       in the input frame.
       Using input frame descriptor2 here, since position for the
       frame descriptor2 is assumed to be lower than frame that of
       frame descriptor1 */
    pIssRszObj->inFrame.addr[0][0] =
        (Ptr)((UInt32)pIssRszObj->inFrame.addr[0][0] +
        inFrmDesc2->pitch[0] * inFrmDesc2->startY + inFrmDesc2->startX);
    pIssRszObj->inFrame.addr[0][1] =
        (Ptr)((UInt32)pIssRszObj->inFrame.addr[0][1] +
        inFrmDesc2->pitch[1] * (inFrmDesc2->startY / 2) + inFrmDesc2->startX);
}

Void Alg_imgPmdIssRszUpdatePrmsOneOutput(
    Alg_ImgPmdIssResizer *pIssRszObj,
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc,
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    vpsissRszCtrl_t rszCtrl;

    /* Updated new isp parameters */
    pIssRszObj->drvIspPrms.inFmt.width         = inFrmDesc->width;
    pIssRszObj->drvIspPrms.inFmt.height        = inFrmDesc->height;
    pIssRszObj->drvIspPrms.inFmt.pitch[0U]     = inFrmDesc->pitch[0];
    pIssRszObj->drvIspPrms.inFmt.pitch[1U]     = inFrmDesc->pitch[1];
    pIssRszObj->drvIspPrms.inFmt.pitch[2U]     = inFrmDesc->pitch[2];

    /* Enable Streams based on the input descriptor pointer */
    pIssRszObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_A] = TRUE;
    pIssRszObj->drvIspPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B] = FALSE;

    status = Fvid2_control(
        pIssRszObj->fvidHandle,
        IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS,
        &pIssRszObj->drvIspPrms,
        NULL);
    UTILS_assert(status == FVID2_SOK);

    /* Update Resizer parameters */
    pIssRszObj->drvRszCfg.inCfg.procWin.cropStartX = 0U;
    pIssRszObj->drvRszCfg.inCfg.procWin.cropStartY = 0U;
    pIssRszObj->drvRszCfg.inCfg.procWin.cropWidth  = inFrmDesc->width;
    pIssRszObj->drvRszCfg.inCfg.procWin.cropHeight = inFrmDesc->height;

    pIssRszObj->drvRszCfg.instCfg[0U].enable = TRUE;

    pIssRszObj->drvRszCfg.instCfg[0U].outFmt.width      = outFrmDesc->width;
    pIssRszObj->drvRszCfg.instCfg[0U].outFmt.height     = outFrmDesc->height;
    pIssRszObj->drvRszCfg.instCfg[0U].outFmt.pitch[0U]  = outFrmDesc->pitch[0];
    pIssRszObj->drvRszCfg.instCfg[0U].outFmt.pitch[1U]  = outFrmDesc->pitch[1];
    pIssRszObj->drvRszCfg.instCfg[0U].outFmt.pitch[2U]  = outFrmDesc->pitch[2];
    pIssRszObj->drvRszCfg.instCfg[0U].startPos.startX   = 0U;
    pIssRszObj->drvRszCfg.instCfg[0U].startPos.startY   = 0U;
    pIssRszObj->drvRszCfg.instCfg[0U].overrideScaleFactor = FALSE;

    pIssRszObj->drvRszCfg.instCfg[1U].enable = FALSE;
    pIssRszObj->drvRszCfg.instCfg[1U].outFmt.width      = outFrmDesc->width;
    pIssRszObj->drvRszCfg.instCfg[1U].outFmt.height     = outFrmDesc->height;
    pIssRszObj->drvRszCfg.instCfg[1U].outFmt.pitch[0U]  = outFrmDesc->pitch[0];
    pIssRszObj->drvRszCfg.instCfg[1U].outFmt.pitch[1U]  = outFrmDesc->pitch[1];
    pIssRszObj->drvRszCfg.instCfg[1U].outFmt.pitch[2U]  = outFrmDesc->pitch[2];
    pIssRszObj->drvRszCfg.instCfg[1U].startPos.startX   = 0U;
    pIssRszObj->drvRszCfg.instCfg[1U].startPos.startY   = 0U;
    pIssRszObj->drvRszCfg.instCfg[1U].overrideScaleFactor = FALSE;

    rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
    rszCtrl.rszCfg = &pIssRszObj->drvRszCfg;
    status = Fvid2_control(
        pIssRszObj->fvidHandle,
        VPS_ISS_RSZ_IOCTL_SET_CONFIG,
        &rszCtrl,
        NULL);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pIssRszObj->inFrame.addr[0][0] = inFrmDesc->bufAddr[0];
    pIssRszObj->inFrame.addr[0][1] = inFrmDesc->bufAddr[1];
    pIssRszObj->inFrame.addr[0][2] = inFrmDesc->bufAddr[2];

    pIssRszObj->outFrame1.addr[0][0] = outFrmDesc->bufAddr[0];
    pIssRszObj->outFrame1.addr[0][1] = outFrmDesc->bufAddr[1];
    pIssRszObj->outFrame1.addr[0][2] = outFrmDesc->bufAddr[2];

    pIssRszObj->outFrame2.addr[0][0] = outFrmDesc->bufAddr[0];
    pIssRszObj->outFrame2.addr[0][1] = outFrmDesc->bufAddr[1];
    pIssRszObj->outFrame2.addr[0][2] = outFrmDesc->bufAddr[2];

    pIssRszObj->inFrame.addr[0][0] =
        (Ptr)((UInt32)pIssRszObj->inFrame.addr[0][0] +
        inFrmDesc->pitch[0] * inFrmDesc->startY + inFrmDesc->startX);
    pIssRszObj->inFrame.addr[0][1] =
        (Ptr)((UInt32)pIssRszObj->inFrame.addr[0][1] +
        inFrmDesc->pitch[1] * (inFrmDesc->startY / 2) + inFrmDesc->startX);
}

