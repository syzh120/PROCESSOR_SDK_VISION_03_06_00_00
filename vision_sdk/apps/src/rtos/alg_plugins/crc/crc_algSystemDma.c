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
 * \file crc_algSystemDmaCrc.c
 *
 * \brief Algorithm for Alg_Crc with system DMA & HW CRC
 *
 *        This implementation uses DMA to copy the frames to CRC HW module
 *        EDMA3LLD APIs are used to copy the frames.
 *        EDMA3LLD is initialized via Utils_dmaInit() during system init.
 *
 * \version 0.0 (May 2015) : [SS] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "icrc_algo.h"
#include <ti/drv/pm/pmlib.h>
#include <include/alglink_api/algorithmLink_crc.h>


/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

/**
 *******************************************************************************
 *
 * \brief Function to enable CRC module & clock
 *
 *******************************************************************************
 */
static void crcAlg_CRCClockEnable (void)
{
#if 1
   pmlibSysConfigPowerStateParams_t inputTable[] =
   {
        {PMHAL_PRCM_MOD_CRC, PMLIB_SYS_CONFIG_ALWAYS_ENABLED}};

   const uint32_t numTableEntries = sizeof (inputTable) /
                                    sizeof (pmlibSysConfigPowerStateParams_t);

   pmlibSysConfigErrReturn_t resultReturn[sizeof (inputTable) /
                                          sizeof (pmlibSysConfigPowerStateParams_t)];
   PMLIBSysConfigSetPowerState(inputTable, (uint32_t) numTableEntries,
                                           PM_TIMEOUT_INFINITE,
                                           resultReturn);
#else
    HW_WR_FIELD32(SOC_CORE_CM_CORE_BASE + CM_CRC_CLKSTCTRL,
                  CM_CRC_CLKSTCTRL_CLKTRCTRL,
                  CM_CRC_CLKSTCTRL_CLKTRCTRL_SW_WKUP);
    HW_WR_FIELD32(SOC_CORE_CM_CORE_BASE + CM_CRC_CRC_CLKCTRL,
                  CM_CRC_CRC_CLKCTRL_MODULEMODE,
                  CM_CRC_CRC_CLKCTRL_MODULEMODE_ENABLE);
#endif
}

/**
 *******************************************************************************
 *
 * \brief Implementation of create for CRC & system DMA
 *
 * \param  algHandle        [IN] Algorithm object handle
 *
 * \param  pCreateParams    [IN] Creation parameters for CRC Algorithm
 *
 * \return  Handle to algorithm
 *
 *******************************************************************************
 */
Int32 Alg_CrcCreate (Alg_CrcDma_Obj *algHandle,
                     Alg_CrcCreateParams *pCreateParams)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    UInt32 paramPhyAddr;
    Alg_Crc_Obj * crcObj;
    Alg_CrcDma_Obj * pAlgHandle;

    pAlgHandle = (Alg_CrcDma_Obj *) algHandle;
    UTILS_assert(pAlgHandle != NULL);

    crcObj = &pAlgHandle->crcObj;

    crcObj->crcPrms.startX     = pCreateParams->startX;
    crcObj->crcPrms.startY     = pCreateParams->startY;
    crcObj->crcPrms.roiHeight  = pCreateParams->roiHeight;
    crcObj->crcPrms.roiWidth   = pCreateParams->roiWidth;
    crcObj->crcPrms.dataFormat = pCreateParams->dataFormat;

    pAlgHandle->hEdma     =
        Utils_dmaGetEdma3Hndl(UTILS_DMA_SYSTEM_EDMA_INST_ID);

    UTILS_assert(pAlgHandle->hEdma!=NULL);

    pAlgHandle->tccId       = EDMA3_DRV_TCC_ANY;
    pAlgHandle->edmaChId    = EDMA3_DRV_DMA_CHANNEL_ANY;

    edma3Result = EDMA3_DRV_requestChannel(
                                    pAlgHandle->hEdma,
                                    (uint32_t*)&pAlgHandle->edmaChId,
                                    (uint32_t*)&pAlgHandle->tccId,
                                    (EDMA3_RM_EventQueue)0,
                                    NULL, (void *)pAlgHandle);

    if (edma3Result == EDMA3_DRV_SOK)
    {
        Vps_printf(" ALG_CRC: DMA: Allocated CH (TCC) = %d (%d)\n",
                        pAlgHandle->edmaChId,
                        pAlgHandle->tccId);

        edma3Result = EDMA3_DRV_clearErrorBits(
                            pAlgHandle->hEdma,
                            pAlgHandle->edmaChId
                        );
    }
    else
    {
        Vps_printf(" ALG_CRC: DMA: ERROR in EDMA CH allocation\n");
    }

    if (edma3Result == EDMA3_DRV_SOK)
    {
        edma3Result = EDMA3_DRV_getPaRAMPhyAddr(
                                pAlgHandle->hEdma,
                                pAlgHandle->edmaChId,
                                &paramPhyAddr);

        pAlgHandle->pParamSet = (EDMA3_DRV_PaRAMRegs*)paramPhyAddr;
    }

    UTILS_assert(edma3Result == EDMA3_DRV_SOK);


    /* Configure CRC parameters */
    crcObj->baseAddr           = SOC_CRC_BASE;
    crcObj->chNumber           = CRC_CHANNEL_1;
    crcObj->watchdogPreloadVal = ((UInt32) 0U);
    crcObj->blockPreloadVal    = ((UInt32) 0U);
    /* Enable CRC clock */
    crcAlg_CRCClockEnable();
    /* Get CRC PSA signature register address */
    CRCGetPSASigRegAddr(crcObj->baseAddr,
                        crcObj->chNumber,
                        &crcObj->psaSignRegAddr);
    /* Configure CRC channel */
    CRCInitialize(crcObj->baseAddr,
                  crcObj->chNumber,
                  crcObj->watchdogPreloadVal,
                  crcObj->blockPreloadVal);

    Vps_printf(" ALG_CRC: CRC Allocated CH = %d \n",
                          crcObj->chNumber);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process call for CRC algo
 *
 *        Supported formats are SYSTEM_DF_YUV422I_YUYV, SYSTEM_DF_YUV420SP_UV,
 *        SYSTEM_DF_RGB24_888 & SYSTEM_DF_BRG24_888
 *        It is assumed that the width of the image in bytes will
 *        be multiple of 8 and buffer pointers are 32-bit aligned.
 *
 * \param  algHandle    [IN] Algorithm object handle
 * \param  inPtr[]      [IN] Array of input pointers
 *                           Index 0 - Pointer to Y data in case of YUV420SP,
 *                                   - Single pointer for YUV422I or RGB
 *                           Index 1 - Pointer to UV data in case of YUV420SP
 * \param  inWidth      [IN] width of input image
 * \param  inheight     [IN] height of input image
 * \param  inPitch[]    [IN] Array of pitch of input image (Address offset
 *                           b.n. two  consecutive lines, interms of bytes)
 *                           Indexing similar to array of input pointers
 * \param  dataFormat   [IN] Different image data formats. Refer
 *                           System_VideoDataFormat
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_CrcProcess (Alg_CrcDma_Obj *algHandle,
                          UInt32 *inPtr[],
                          UInt32  inWidth,
                          UInt32  inHeight,
                          UInt32  inPitch[],
                          UInt32  dataFormat
                         )
{
    UInt32 numPlanes;
    UInt32 opt;
    UInt16 tccStatus;
    UInt32 patternCnt1, patternCnt2;
    UInt32 frameSize1, frameSize2;
    UInt32 roiWidthInBytes, startXInBytes;
    Alg_Crc_Obj * crcObj;
    Alg_CrcDma_Obj * pAlgHandle;

    pAlgHandle = (Alg_CrcDma_Obj *)algHandle;
    crcObj = &pAlgHandle->crcObj;

    UTILS_assert (inWidth >= crcObj->crcPrms.roiWidth+crcObj->crcPrms.startX);
    UTILS_assert (inHeight >= crcObj->crcPrms.roiHeight+crcObj->crcPrms.startY);
    UTILS_assert (dataFormat == crcObj->crcPrms.dataFormat);

    crcObj->patternSize = ((UInt32) 8U);
    crcObj->sectCnt     = ((UInt32) 1U);
    crcObj->mode        = CRC_OPERATION_MODE_SEMICPU;

    opt  =
        (EDMA3_CCRL_OPT_ITCCHEN_ENABLE << EDMA3_CCRL_OPT_ITCCHEN_SHIFT)
           |
        ((pAlgHandle->tccId << EDMA3_CCRL_OPT_TCC_SHIFT)
                    & EDMA3_CCRL_OPT_TCC_MASK
         )
           |
        (EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT)
           |
        (EDMA3_CCRL_OPT_TCINTEN_ENABLE
                    << EDMA3_CCRL_OPT_TCINTEN_SHIFT)
        ;

    patternCnt1 = 0;
    patternCnt2 = 0;

    switch (dataFormat)
    {
    case SYSTEM_DF_YUV422I_YUYV:
        numPlanes = 1;
        frameSize1  = (crcObj->crcPrms.roiWidth * crcObj->crcPrms.roiHeight) *2;
        patternCnt1 = frameSize1/crcObj->patternSize;
        roiWidthInBytes = crcObj->crcPrms.roiWidth * 2;
        startXInBytes = crcObj->crcPrms.startX * 2;
        break;

    case SYSTEM_DF_BGR24_888:
    case SYSTEM_DF_RGB24_888:
        numPlanes = 1;
        frameSize1  = (crcObj->crcPrms.roiWidth * crcObj->crcPrms.roiHeight) *3;
        patternCnt1 = frameSize1/crcObj->patternSize;
        roiWidthInBytes = crcObj->crcPrms.roiWidth * 3;
        startXInBytes = crcObj->crcPrms.startX * 3;
        break;

    case SYSTEM_DF_YUV420SP_UV:
        numPlanes = 2;
        /* Luma plane */
        frameSize1  = crcObj->crcPrms.roiWidth * crcObj->crcPrms.roiHeight;
        patternCnt1 = frameSize1/crcObj->patternSize;
        /* Chroma plane */
        frameSize2  = (crcObj->crcPrms.roiWidth * crcObj->crcPrms.roiHeight) /2;
        patternCnt2 = frameSize2/crcObj->patternSize;
        roiWidthInBytes = crcObj->crcPrms.roiWidth;
        startXInBytes = crcObj->crcPrms.startX;
        break;

    default:
        Vps_printf (" ALG CRC: Unsupported Data format !!! \n");
        UTILS_assert (0);
    }

    /* CRC channel RESET before initialization/configuration */
    CRCChannelReset(crcObj->baseAddr, crcObj->chNumber);
    /* Initialize CRC channel */
    CRCConfigure(crcObj->baseAddr, crcObj->chNumber,
                 (patternCnt1 + patternCnt2), crcObj->sectCnt,
                 crcObj->mode);

    EDMA3_DRV_checkAndClearTcc(pAlgHandle->hEdma,
                               pAlgHandle->tccId,
                               &tccStatus);
    EDMA3_DRV_clearErrorBits (pAlgHandle->hEdma,pAlgHandle->edmaChId);

    pAlgHandle->pParamSet->srcAddr    =
        (UInt32)inPtr[0] + startXInBytes + crcObj->crcPrms.startY*inPitch[0];
    pAlgHandle->pParamSet->destAddr   = (UInt32)crcObj->psaSignRegAddr.regL;
    pAlgHandle->pParamSet->aCnt       = crcObj->patternSize;
    pAlgHandle->pParamSet->bCnt       = roiWidthInBytes/crcObj->patternSize;
    pAlgHandle->pParamSet->srcBIdx    = crcObj->patternSize;
    pAlgHandle->pParamSet->destBIdx   = 0;
    pAlgHandle->pParamSet->bCntReload = roiWidthInBytes/crcObj->patternSize;
    pAlgHandle->pParamSet->cCnt       = crcObj->crcPrms.roiHeight;
    pAlgHandle->pParamSet->destCIdx   = 0;
    pAlgHandle->pParamSet->srcCIdx    = inPitch[0];
    pAlgHandle->pParamSet->opt        = opt;
    pAlgHandle->pParamSet->linkAddr   = 0xFFFF;

    EDMA3_DRV_enableTransfer (pAlgHandle->hEdma,pAlgHandle->edmaChId,
                                           EDMA3_DRV_TRIG_MODE_MANUAL);
    EDMA3_DRV_waitAndClearTcc(pAlgHandle->hEdma,pAlgHandle->tccId);

    /*
     * For chroma plane of 420SP
     */
    if(numPlanes == 2)
    {
        EDMA3_DRV_checkAndClearTcc(pAlgHandle->hEdma,
                                   pAlgHandle->tccId,
                                   &tccStatus);
        EDMA3_DRV_clearErrorBits (pAlgHandle->hEdma,pAlgHandle->edmaChId);

        pAlgHandle->pParamSet->srcAddr    =
           (UInt32)inPtr[1] + startXInBytes + crcObj->crcPrms.startY*inPitch[1];
        pAlgHandle->pParamSet->destAddr   = (UInt32)crcObj->psaSignRegAddr.regL;
        pAlgHandle->pParamSet->aCnt       = crcObj->patternSize;
        pAlgHandle->pParamSet->bCnt       = roiWidthInBytes/crcObj->patternSize;
        pAlgHandle->pParamSet->srcBIdx    = crcObj->patternSize;
        pAlgHandle->pParamSet->destBIdx   = 0;
        pAlgHandle->pParamSet->bCntReload = roiWidthInBytes/crcObj->patternSize;
        pAlgHandle->pParamSet->cCnt       = crcObj->crcPrms.roiHeight/2;
        pAlgHandle->pParamSet->destCIdx   = 0;
        pAlgHandle->pParamSet->srcCIdx    = inPitch[1];
        pAlgHandle->pParamSet->opt        = opt;
        pAlgHandle->pParamSet->linkAddr   = 0xFFFF;

        EDMA3_DRV_enableTransfer (pAlgHandle->hEdma,pAlgHandle->edmaChId,
                                  EDMA3_DRV_TRIG_MODE_MANUAL);
        EDMA3_DRV_waitAndClearTcc(pAlgHandle->hEdma,pAlgHandle->tccId);
    }

    EDMA3_DRV_clearErrorBits (pAlgHandle->hEdma,pAlgHandle->edmaChId);

    while ((CRCGetIntrStatus(crcObj->baseAddr,
                             crcObj->chNumber)
                             & CRC_INTR_CH1_CCITENR_MASK) != 0x1U)
    {
        /* Wait here till CRC compression complete is set. */
    }

    /* Fetch CRC signature value */
    CRCGetPSASectorSig(crcObj->baseAddr, crcObj->chNumber,
                       &crcObj->sectSignVal);

    CRCClearIntr(crcObj->baseAddr,
                 crcObj->chNumber,
                 CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control for CRC algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  pControlParams        [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_CrcControl (Alg_CrcDma_Obj *algHandle,
                      Alg_CrcControlParams *pControlParams)
{
    /*
     * Any alteration of algorithm behavior
     */
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop for CRC algo
 *
 * \param  algHandle    [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_CrcStop (Alg_CrcDma_Obj *algHandle)
{
      return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for CRC algo
 *
 * \param  algHandle    [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_CrcDelete (Alg_CrcDma_Obj *algHandle)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    Alg_CrcDma_Obj * pAlgHandle;

    pAlgHandle = (Alg_CrcDma_Obj *)algHandle;

    edma3Result = EDMA3_DRV_freeChannel(
                        pAlgHandle->hEdma,
                        pAlgHandle->edmaChId
                  );

    return edma3Result;
}

/* Nothing beyond this point */
