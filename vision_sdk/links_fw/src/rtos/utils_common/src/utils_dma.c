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
 * \file utils_dma.c
 *
 * \brief This file has the implementation of the system DMA APIs
 *
 * \version 0.0 (Aug 2013) : [KC] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_dma.h>
#include <src/rtos/utils_common/src/dma_cfg/utils_dma_edma3cc.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <ti/sysbios/hal/Cache.h>

/*******************************************************************************
 *  Defines - private to DMA API implementation
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Compile time flag to control PaRAM parameter checking
 *******************************************************************************
 */
#define SYSTEM_UTILS_DMA_PARAM_CHECK


/*******************************************************************************
 *  Local Function Declaration
 *******************************************************************************
 */
Int32 Utils_dmaCopyFill2D(Utils_DmaChObj *pObj, const Utils_DmaCopyFill2D *pInfo,
                        UInt32 numTransfers, Bool fillData);
Int32 Utils_dmaParamSetCheck(const EDMA3_DRV_PaRAMRegs *pParamSet);
Int32 Utils_dmaRun(Utils_DmaChObj *pObj, UInt32 *numTx);
Int32 Utils_dmaLinkDma(const Utils_DmaChObj *pObj, UInt32 numTx);
Int32 Utils_dmaPollWaitComplete(Utils_DmaChObj *pObj);
Int32 Utils_dmaFreeDmaChParam(Utils_DmaChObj *pObj);
Int32 Utils_dmaCreateSemaphores(Utils_DmaChObj *pObj);
Int32 Utils_dmaAllocDmaCh(Utils_DmaChObj *pObj);
Int32 Utils_dmaAllocParam(Utils_DmaChObj *pObj);
void Utils_dmaCallback(uint32_t tcc, EDMA3_RM_TccStatus status,
                            void *appData);

static Bool gDmaInit = FALSE;

void Utils_tfdtpDmaInit(void);

/**
 *******************************************************************************
 *
 * \brief DMA Init Function called from NDK stack Init hook function
 *        This needs to be called when TFDTP is enabled as it uses EDMA functions
 *
 * \return None
 *
 *******************************************************************************
 */

void Utils_tfdtpDmaInit(void)
{
    UTILS_assert (EDMA3_DRV_SOK == Utils_dmaInit());
    gDmaInit = (Bool)TRUE;
}

/**
 *******************************************************************************
 *
 * \brief Init DMA sub-system. MUST be called once before using the DMA APIs
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaInit(void)
{
    UInt32 edma3InstId;
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;

    if (gDmaInit == FALSE)
    {
        if((SYSTEM_PROC_DSP1 == System_getSelfProcId()) ||
        (SYSTEM_PROC_DSP2 == System_getSelfProcId()) ||
        (SYSTEM_PROC_EVE1 == System_getSelfProcId()) ||
        (SYSTEM_PROC_EVE2 == System_getSelfProcId()) ||
        (SYSTEM_PROC_EVE3 == System_getSelfProcId()) ||
        (SYSTEM_PROC_EVE4 == System_getSelfProcId()))
        {
            edma3InstId = UTILS_DMA_LOCAL_EDMA_INST_ID;

            edma3Result = Utils_edma3Init(edma3InstId);
            if (edma3Result != EDMA3_DRV_SOK)
            {
                Vps_printf(
                    " UTILS: DMA: Utils_dmaInit() for instance %d "
                    "... FAILED (%d) \n",
                        edma3InstId,
                        edma3Result
                );
            }
        }

        if ((SYSTEM_PROC_IPU1_0 == System_getSelfProcId()) ||
            (SYSTEM_PROC_IPU1_1 == System_getSelfProcId()) ||
            (SYSTEM_PROC_IPU2 == System_getSelfProcId()) ||
            (SYSTEM_PROC_A15_0 == System_getSelfProcId()) ||
            (SYSTEM_PROC_DSP1 == System_getSelfProcId()) ||
            (SYSTEM_PROC_DSP2 == System_getSelfProcId()))
        {
            edma3InstId = UTILS_DMA_SYSTEM_EDMA_INST_ID;

            edma3Result = Utils_edma3Init(edma3InstId);
            if (edma3Result != EDMA3_DRV_SOK)
            {
                Vps_printf(
                    " UTILS: DMA: Utils_dmaInit() for instance %d "
                    "... FAILED (%d) \n",
                        edma3InstId,
                        edma3Result
                );
            }
        }
    }

    return edma3Result;
}

/**
 *******************************************************************************
 *
 * \brief De-Init DMA sub-system.
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaDeInit(void)
{
    UInt32 edma3InstId;
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;

    if((SYSTEM_PROC_DSP1 == System_getSelfProcId()) ||
       (SYSTEM_PROC_DSP2 == System_getSelfProcId()) ||
       (SYSTEM_PROC_EVE1 == System_getSelfProcId()) ||
       (SYSTEM_PROC_EVE2 == System_getSelfProcId()) ||
       (SYSTEM_PROC_EVE3 == System_getSelfProcId()) ||
       (SYSTEM_PROC_EVE4 == System_getSelfProcId()))
    {
        edma3InstId = UTILS_DMA_LOCAL_EDMA_INST_ID;

        edma3Result = Utils_edma3DeInit(edma3InstId);
        if (edma3Result != EDMA3_DRV_SOK)
        {
            Vps_printf(
                   " UTILS: DMA: Utils_dmaDeInit() for instance %d "
                   "... FAILED (%d) \n",
                    edma3InstId,
                    edma3Result
            );
        }
    }

    if ((SYSTEM_PROC_IPU1_0 == System_getSelfProcId()) ||
        (SYSTEM_PROC_IPU1_1 == System_getSelfProcId()) ||
        (SYSTEM_PROC_IPU2 == System_getSelfProcId()) ||
        (SYSTEM_PROC_A15_0 == System_getSelfProcId()) ||
        (SYSTEM_PROC_DSP1 == System_getSelfProcId()) ||
        (SYSTEM_PROC_DSP2 == System_getSelfProcId()))
    {
        edma3InstId = UTILS_DMA_SYSTEM_EDMA_INST_ID;

        edma3Result = Utils_edma3DeInit(edma3InstId);
        if (edma3Result != EDMA3_DRV_SOK)
        {
            Vps_printf(
                   " UTILS: DMA: Utils_dmaDeInit() for instance %d "
                   "... FAILED (%d) \n",
                    edma3InstId,
                    edma3Result
            );
        }
    }
    return edma3Result;
}

/**
 *******************************************************************************
 *
 * \brief Create semaphore required for logical DMA channel
 *
 * \param pObj      [IN] Logical DMA channel handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaCreateSemaphores(Utils_DmaChObj *pObj)
{
    pObj->semComplete = BspOsal_semCreate(0, (Bool)TRUE);
    UTILS_assert(pObj->semComplete != NULL);

    pObj->semLock = BspOsal_semCreate(1, (Bool)TRUE);
    UTILS_assert(pObj->semLock != NULL);

    return EDMA3_DRV_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Cllback that is called with EDMA transfer completes
 *
 * \param tcc           [IN] TCC for which the tranfer completed
 * \param status        [IN] transfer completion status
 * \param appData       [IN] App data pointer set by user
 *                           during channel request
 *
 *******************************************************************************
 */
void Utils_dmaCallback(uint32_t tcc, EDMA3_RM_TccStatus status,
                            void *appData)
{
    (void)tcc;
    Utils_DmaChObj *pObj = (Utils_DmaChObj *)appData;

    switch (status)
    {
        case EDMA3_RM_XFER_COMPLETE:
            BspOsal_semPost(pObj->semComplete);
            break;
        case EDMA3_RM_E_CC_DMA_EVT_MISS:

            break;
        case EDMA3_RM_E_CC_QDMA_EVT_MISS:

            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 *
 * \brief Alloc EDMA channel for a logical DMA channel
 *
 * \param pObj      [IN] Logical DMA channel handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaAllocDmaCh(Utils_DmaChObj *pObj)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    EDMA3_RM_TccCallback tccCb;

    pObj->tccId        = EDMA3_DRV_TCC_ANY;
    pObj->edmaChId    = EDMA3_DRV_DMA_CHANNEL_ANY;

    if(pObj->enableIntCb)
    {
        /* MISRA.CAST.FUNC_PTR:MISRAC_2004 Rule_11.1
           MISRAC_WAIVER:
           Typecasting callback function to EDMA callback function */
        tccCb = (EDMA3_RM_TccCallback)&Utils_dmaCallback;
    }
    else
    {
        tccCb = NULL;
    }

    edma3Result = EDMA3_DRV_requestChannel(
                                    pObj->hEdma,
                                    (uint32_t*)&pObj->edmaChId,
                                    (uint32_t*)&pObj->tccId,
                                    (EDMA3_RM_EventQueue)pObj->eventQ,
                                    tccCb, (void *)pObj);

    if (edma3Result == EDMA3_DRV_SOK)
    {
        Vps_printf(" UTILS: DMA: Allocated CH (TCC) = %d (%d)\n",
                        pObj->edmaChId,
                        pObj->tccId);

        edma3Result = EDMA3_DRV_clearErrorBits(
                            pObj->hEdma,
                            pObj->edmaChId
                        );
    }
    else
    {
        Vps_printf(" UTILS: DMA: ERROR in EDMA CH allocation\n");
    }
    return edma3Result;
}

/**
 *******************************************************************************
 *
 * \brief Alloc PaRAM entry for a logical DMA channel
 *
 * \param pObj      [IN] Logical DMA channel handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaAllocParam(Utils_DmaChObj *pObj)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    UInt32 paramId, paramPhyAddr, edmaChId, tccId;
    Utils_DmaTxObj  *pTxObj;

    /* allocate PaRAM entries */
    for(paramId=0; paramId<pObj->maxTransfers; paramId++)
    {
        pTxObj = &pObj->txObj[paramId];

        edma3Result = EDMA3_DRV_SOK;

        if(paramId==0)
        {
            /* first PaRAM used is equal to EDMA CH ID no need to allcaote it */
            pTxObj->paramId = pObj->edmaChId;
        }
        else
        {
            edmaChId = EDMA3_DRV_LINK_CHANNEL;
            tccId    = EDMA3_DRV_TCC_ANY;

            edma3Result = EDMA3_DRV_requestChannel (
                                    pObj->hEdma,
                                    &edmaChId,
                                    &tccId,
                                    (EDMA3_RM_EventQueue)pObj->eventQ,
                                    NULL,
                                    NULL
                                  );

            pTxObj->paramId = edmaChId;
        }

        if (edma3Result == EDMA3_DRV_SOK)
        {
            edma3Result = EDMA3_DRV_getPaRAMPhyAddr(
                                    pObj->hEdma,
                                    pTxObj->paramId,
                                    &paramPhyAddr);

            if ((EDMA3_DRV_SOK == edma3Result) && (0U != paramPhyAddr))
            {
                pTxObj->pParamSet = (EDMA3_DRV_PaRAMRegs*)paramPhyAddr;
                /* MISRA.CAST.PTR_TO_INT
                 * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
                 * State: Fix in later release -> Waiver -> Case by case
                 * Function pointers converted to uint32_t
                 */
                pTxObj->pParamSet->destAddr   = 0;
                pTxObj->pParamSet->srcAddr    = 0;
                pTxObj->pParamSet->srcBIdx    = 0;
                pTxObj->pParamSet->destBIdx   = 0;
                pTxObj->pParamSet->srcCIdx    = 0;
                pTxObj->pParamSet->destCIdx   = 0;
                pTxObj->pParamSet->aCnt       = 0;
                pTxObj->pParamSet->bCnt       = 0;
                pTxObj->pParamSet->cCnt       = 1;
                pTxObj->pParamSet->bCntReload = 0;
                pTxObj->pParamSet->opt        = 0;
                pTxObj->pParamSet->linkAddr   = 0xFFFF;
            }
        }

        if (edma3Result == EDMA3_DRV_SOK)
        {
            Vps_printf(" UTILS: DMA: %d of %d: Allocated PaRAM = %d (0x%08X)\n",
                paramId,
                pObj->maxTransfers,
                pTxObj->paramId,
                pTxObj->pParamSet);
        }
        else
        {
            Vps_printf(" UTILS: DMA: %d of %d: ERROR in PaRAM allocation\n",
                paramId,
                pObj->maxTransfers);
            break;
        }
    }

    return edma3Result;
}

/**
 *******************************************************************************
 *
 * \brief Free a allocated EDMACH and PaRAM entry for a logical DMA channel
 *
 * \param pObj      [IN] Logical DMA channel handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaFreeDmaChParam(Utils_DmaChObj *pObj)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    UInt32 paramId;

    for(paramId=0; paramId<pObj->maxTransfers; paramId++)
    {
        edma3Result = EDMA3_DRV_freeChannel(
                            pObj->hEdma,
                            pObj->txObj[paramId].paramId
                      );
    }

    return edma3Result;
}


/**
 *******************************************************************************
 *
 * \brief Create a logical DMA channel
 *
 *        - Allcoates 1 EDMA CH + 1 PaRAM entry by default
 *        - Allocates more PaRAM entries depending on value of
 *          Utils_DmaChCreateParams.maxTransfers
 *
 * \param pObj      [OUT] Logical DMA channel handle
 * \param pPrm      [IN]  create time parameters
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaCreateCh(Utils_DmaChObj *pObj, const Utils_DmaChCreateParams *pPrm)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    UInt32 maxTransfers, edmaInstId;

    memset(pObj, 0, sizeof(Utils_DmaChObj));

    maxTransfers = pPrm->maxTransfers;
    edmaInstId   = pPrm->edmaInstId;

    if(maxTransfers<1U)
    {
        maxTransfers = 1U;
    }

    if(maxTransfers>UTILS_DMA_MAX_TX_OBJ)
    {
        maxTransfers = UTILS_DMA_MAX_TX_OBJ;
    }

    if(edmaInstId>=UTILS_DMA_MAX_EDMA_INST)
    {
        edmaInstId = UTILS_DMA_SYSTEM_EDMA_INST_ID;
    }

    pObj->maxTransfers= maxTransfers;
    pObj->eventQ      = pPrm->eventQ;

    if(Utils_dmaIsIntrSupported(edmaInstId))
    {
        pObj->enableIntCb = (Bool)pPrm->enableIntCb;
    }
    else
    {
        /* force dsiable interrupt mode if not supported */
        pObj->enableIntCb = (Bool)FALSE;
    }

    pObj->hEdma       = Utils_dmaGetEdma3Hndl(edmaInstId);

    UTILS_assert(pObj->hEdma!=NULL);

    memset(pObj->txObj, 0, sizeof(pObj->txObj));

    edma3Result = Utils_dmaCreateSemaphores(pObj);

    edma3Result += Utils_dmaAllocDmaCh(pObj);

    if (EDMA3_DRV_SOK == edma3Result)
    {
        edma3Result = Utils_dmaAllocParam(pObj);
    }

    return edma3Result;
}

/**
 *******************************************************************************
 *
 * \brief Delete a logical DMA channel
 *
 *        - Free's DMA's CH, PaRAM entries allocated during create
 *
 * \param pObj      [IN] Logical DMA channel handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaDeleteCh(Utils_DmaChObj *pObj)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;

    edma3Result = Utils_dmaFreeDmaChParam(pObj);

    BspOsal_semDelete(&pObj->semComplete);
    BspOsal_semDelete(&pObj->semLock);

    Vps_printf(" UTILS: DMA: Free'ed CH (TCC) = %d (%d)\n",
                    pObj->edmaChId,
                    pObj->tccId);

    return edma3Result;
}

/**
 *******************************************************************************
 *
 * \brief Polling based wait for completion
 *
 * \param pObj      [IN] Logical DMA channel handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaPollWaitComplete(Utils_DmaChObj *pObj)
{
    uint16_t tccStatus;

    EDMA3_DRV_waitAndClearTcc(pObj->hEdma,pObj->tccId);
    EDMA3_DRV_checkAndClearTcc(pObj->hEdma,pObj->tccId, &tccStatus);
    EDMA3_DRV_clearErrorBits (pObj->hEdma,pObj->edmaChId);

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Trigger EDMA channel and wait for completion
 *
 * \param pObj      [IN] Logical DMA channel handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaTriggerAndWait(Utils_DmaChObj *pObj)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    uint16_t tccStatus;

    edma3Result = EDMA3_DRV_checkAndClearTcc(pObj->hEdma,
                                    pObj->tccId,
                                    &tccStatus);

    if (EDMA3_DRV_SOK == edma3Result)
    {
        edma3Result = EDMA3_DRV_clearErrorBits (pObj->hEdma,pObj->edmaChId);

        if (EDMA3_DRV_SOK == edma3Result)
        {
            edma3Result = EDMA3_DRV_enableTransfer (
                pObj->hEdma,pObj->edmaChId,
                EDMA3_DRV_TRIG_MODE_MANUAL);
        }
    }

    if (edma3Result != EDMA3_DRV_SOK)
    {
        Vps_printf(
            " UTILS: DMA: Utils_dmaTrigger() ... FAILED (CH=%d) \n",
                pObj->edmaChId, edma3Result
            );
    }

    if (edma3Result == EDMA3_DRV_SOK)
    {
        if(pObj->enableIntCb)
        {
            BspOsal_semWait(pObj->semComplete, BSP_OSAL_WAIT_FOREVER);
        }
        else
        {
            Utils_dmaPollWaitComplete(pObj);
        }
    }

    return edma3Result;
}

/**
 *******************************************************************************
 *
 * \brief Check if PaRAM set values are valid
 *
 * \param pParamSet      [IN] PaRAM set pointer
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaParamSetCheck(const EDMA3_DRV_PaRAMRegs *pParamSet)
{
    Int32 status = FVID2_SOK;

    if((0 == pParamSet->aCnt) ||
       (0 == pParamSet->bCnt) ||
       (0 == pParamSet->cCnt) ||
       (0 == pParamSet->destAddr) ||
       (0 == pParamSet->srcAddr) ||
       (0 == pParamSet->bCntReload))
    {
        status = FVID2_EFAIL;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Link PaRAM entires to numTx transfers
 *
 * \param pObj      [IN] Logical DMA channel handle
 * \param numTx     [IN] Number of transfers to perform
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaLinkDma(const Utils_DmaChObj *pObj, UInt32 numTx)
{
    UInt32 i;
    EDMA3_DRV_PaRAMRegs *pParamSet;
    UInt32 opt;

    /* link the EDMAs */
    for(i=0; i<numTx; i++)
    {
        pParamSet   = pObj->txObj[i].pParamSet;

        opt  =
                 ((UInt32)((UInt32)EDMA3_CCRL_OPT_ITCCHEN_ENABLE << EDMA3_CCRL_OPT_ITCCHEN_SHIFT))
               | ((UInt32)((UInt32)pObj->tccId << EDMA3_CCRL_OPT_TCC_SHIFT)
                        & EDMA3_CCRL_OPT_TCC_MASK
                 )
               | ((UInt32)((UInt32)EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT))
                  ;

        if( i== (numTx-1U) )
        {
            /* last DMA */

            /* enable interrupt for last Transfer ONLY */
            opt |= (UInt32)((UInt32)EDMA3_CCRL_OPT_TCINTEN_ENABLE
                        << EDMA3_CCRL_OPT_TCINTEN_SHIFT);

            /* do not link DMA */
            pParamSet->linkAddr = 0xFFFF;
        }
        else
        {
            /* enable chaining after transfer complete */
            opt |= (UInt32)((UInt32)EDMA3_CCRL_OPT_TCCHEN_ENABLE
                        << EDMA3_CCRL_OPT_TCCHEN_SHIFT);

            /* link current DMA to next DMA */
            pParamSet->linkAddr = (UInt32)pObj->txObj[i+1U].pParamSet;
            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
             * State: Fix in later release -> Waiver -> Case by case
             * Memory mapped regsiters and other hardware features access requires typecasting
             * of pointer to integer.  The address space is 32 bit and type casting to integer
             * will not result into any loss because of TI's compiler treatment to integer.
             */

        }

        pParamSet->opt = opt;
    }

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Link PaRAM entires, trigger EDMA and wait fior completion
 *
 * \param pObj      [IN] Logical DMA channel handle
 * \param numTx     [IN] Number of transfer's to perform \n
 *                  [OUT] Number of transfer's remaining
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaRun(Utils_DmaChObj *pObj, UInt32 *numTx)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;

    if(0U != *numTx)
    {
        Utils_dmaLinkDma(pObj, *numTx);

        edma3Result = Utils_dmaTriggerAndWait(pObj);

        *numTx = 0;
    }

    return edma3Result;
}

/**
 *******************************************************************************
 *
 * \brief Copy data using EDMA
 *
 *        The API takes a mutual exclusion lock to allow the same API on the
 *        same logical channel be called from multiple thread contexts
 *
 * \param pObj             [IN] Logical DMA channel handle
 * \param pPrm             [IN] parameters for copy- srcAddr, dstAddr, length
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaCopy1D(Utils_DmaChObj *pObj, const Utils_DmaCopy1D *pPrm)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    EDMA3_DRV_PaRAMRegs *pParamSet;
    UInt32 opt;
    UInt32          bCntValue = 1U;
    UInt32          remBytes  = 0;
    UInt32          length    = pPrm->length;
    UInt32          aCntValue = length;
    UInt32          addr;
    UInt32          maxAcnt   = 0x7FF0U;

    if ((NULL == pPrm->destAddr) || (NULL == pPrm->srcAddr))
    {
        edma3Result = -(Int32)1;
    }
    else
    {
        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3
         * MISRAC_WAIVER:
         * Source address is type casted to uint as expected by edma
         */
        addr = (UInt32) pPrm->destAddr;
        BspOsal_semWait(pObj->semLock, BSP_OSAL_WAIT_FOREVER);

        if (length > maxAcnt)
        {
            bCntValue = length / maxAcnt;
            remBytes  = length % maxAcnt;
            aCntValue = maxAcnt;
        }

        /* Compute QSPI address and size */
        pParamSet             = pObj->txObj[0].pParamSet;
        pParamSet->opt        = 0;
        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3
         * MISRAC_WAIVER:
         * Source address is type casted to uint as expected by edma
         */
        pParamSet->srcAddr    = (UInt32)pPrm->srcAddr;
        pParamSet->destAddr   = addr;
        pParamSet->aCnt       = aCntValue;
        pParamSet->bCnt       = bCntValue;
        pParamSet->cCnt       = 1;
        pParamSet->srcBIdx    = aCntValue;
        pParamSet->destBIdx   = aCntValue;
        pParamSet->srcCIdx    = 0;
        pParamSet->destCIdx   = 0;
        pParamSet->linkAddr   = 0xFFFF;
        opt  =
                 ((UInt32)((UInt32)EDMA3_CCRL_OPT_ITCCHEN_ENABLE << EDMA3_CCRL_OPT_ITCCHEN_SHIFT))
               | ((UInt32)((UInt32)pObj->tccId << EDMA3_CCRL_OPT_TCC_SHIFT)
                        & EDMA3_CCRL_OPT_TCC_MASK
                 )
               | ((UInt32)((UInt32)EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT))
                  ;
        /* enable interrupt for last Transfer ONLY */
        opt |= (UInt32)((UInt32)EDMA3_CCRL_OPT_TCINTEN_ENABLE
                    << EDMA3_CCRL_OPT_TCINTEN_SHIFT);

        pParamSet->opt = opt;
        edma3Result = Utils_dmaTriggerAndWait(pObj);
        if (edma3Result != EDMA3_DRV_SOK)
        {
            Vps_printf(
                " UTILS: DMA: Utils_dmaTrigger() ... FAILED (CH=%d) \n",
                    pObj->edmaChId, edma3Result
                );
        }

        if ((remBytes != 0) && (edma3Result == EDMA3_DRV_SOK))
        {
            /* Compute QSPI address and size */
            pParamSet             = pObj->txObj[0].pParamSet;
            pParamSet->opt        = 0;
            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004_Rule_11.3
             * MISRAC_WAIVER:
             * Source address is type casted to uint as expected by edma
             */
            pParamSet->srcAddr    = (UInt32)((UInt32)pPrm->srcAddr + (bCntValue * aCntValue));
            pParamSet->destAddr   = (UInt32)(addr + (aCntValue * bCntValue));
            pParamSet->aCnt       = remBytes;
            pParamSet->bCnt       = 1;
            pParamSet->cCnt       = 1;
            pParamSet->srcBIdx    = remBytes;
            pParamSet->destBIdx   = remBytes;
            pParamSet->srcCIdx    = 0;
            pParamSet->destCIdx   = 0;
            pParamSet->linkAddr   = 0xFFFF;
            opt  =
                     ((UInt32)((UInt32)EDMA3_CCRL_OPT_ITCCHEN_ENABLE << EDMA3_CCRL_OPT_ITCCHEN_SHIFT))
                   | ((UInt32)((UInt32)pObj->tccId << EDMA3_CCRL_OPT_TCC_SHIFT)
                            & EDMA3_CCRL_OPT_TCC_MASK
                     )
                   | ((UInt32)((UInt32)EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT))
                      ;
            /* enable interrupt for last Transfer ONLY */
            opt |= (UInt32)((UInt32)EDMA3_CCRL_OPT_TCINTEN_ENABLE
                        << EDMA3_CCRL_OPT_TCINTEN_SHIFT);

            pParamSet->opt = opt;
            edma3Result = Utils_dmaTriggerAndWait(pObj);
            if (edma3Result != EDMA3_DRV_SOK)
            {
                Vps_printf(
                    " UTILS: DMA: Utils_dmaTrigger() ... FAILED (CH=%d) \n",
                        pObj->edmaChId, edma3Result
                    );
            }

        }

        BspOsal_semPost(pObj->semLock);
    }

    return edma3Result;
}

/**
 *******************************************************************************
 *
 * \brief Copy or fill data using EDMA
 *
 *        The API takes a mutual exclusion lock to allow the same API on the
 *        same logical channel be called from multiple thread contexts
 *
 * \param pObj          [IN] Logical DMA channel handle
 * \param pInfo         [IN] Array of DMA transfer parameter's
 * \param numTransfers  [IN] Number of transfers to perform
 * \param fillData      [IN] TRUE: Fill data in destination buffer, \n
 *                           FALSE: Copy data to destination buffer
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaCopyFill2D(Utils_DmaChObj *pObj, const Utils_DmaCopyFill2D *pInfo,
                        UInt32 numTransfers, Bool fillData)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    EDMA3_DRV_PaRAMRegs *pParamSet;
    UInt32 bpp; /* bytes per pixel */
    UInt32 i, numTx;

    BspOsal_semWait(pObj->semLock, BSP_OSAL_WAIT_FOREVER);

    numTx = 0U;

    for(i=0; i<numTransfers; i++)
    {
        pParamSet   = pObj->txObj[numTx].pParamSet;

        if(pInfo->dataFormat==SYSTEM_DF_RAW24)
        {
            bpp = 3U;
        }
        else
        if(pInfo->dataFormat==SYSTEM_DF_RAW16)
        {
            bpp = 2U;
        }
        else
        if(pInfo->dataFormat==SYSTEM_DF_RAW08)
        {
            bpp = 1U;
        }
        else
        if(pInfo->dataFormat==SYSTEM_DF_YUV420SP_UV)
        {
            bpp = 1U;
        }
        else
        if ((pInfo->dataFormat==SYSTEM_DF_ARGB32_8888) ||
            (pInfo->dataFormat==SYSTEM_DF_BGRA32_8888) ||
            (pInfo->dataFormat==SYSTEM_DF_ABGR32_8888) ||
            (pInfo->dataFormat==SYSTEM_DF_RGBA32_8888))
        {
            bpp = 4U;
        }
        else
        if ((pInfo->dataFormat==SYSTEM_DF_RGB24_888) ||
            (pInfo->dataFormat==SYSTEM_DF_BGR24_888))
        {
            bpp = 3U;
        }
        else
        {
            bpp = 1U;
        }

        pParamSet->destAddr   = (UInt32)pInfo->destAddr[0]
                              + (pInfo->destPitch[0]*pInfo->destStartY)
                              + (pInfo->destStartX * bpp);
        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
         * State: Fix in later release -> Waiver -> Case by case
         * IP reads data in a particular format. So pointer to int conversion
         * is required to put data in that format.
         */

        if(fillData)
        {
            pParamSet->srcAddr   = (UInt32)pInfo->srcAddr[0];
            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
             * State: Fix in later release -> Waiver -> Case by case
             * IP reads data in a particular format. So pointer to int conversion
             * is required to put data in that format.
             */
            pParamSet->srcBIdx   = 0;
        }
        else
        {
            pParamSet->srcAddr   = (UInt32)pInfo->srcAddr[0]
                                  + (pInfo->srcPitch[0]*pInfo->srcStartY)
                                  + (pInfo->srcStartX * bpp);
            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
             * State: Fix in later release -> Waiver -> Case by case
             * IP reads data in a particular format. So pointer to int conversion
             * is required to put data in that format.
             */
            pParamSet->srcBIdx    = pInfo->srcPitch[0];
        }

        pParamSet->destBIdx   = pInfo->destPitch[0];

        pParamSet->aCnt       = pInfo->width*bpp;
        pParamSet->bCnt       = pInfo->height;
        pParamSet->cCnt       = 1;

        pParamSet->bCntReload = pParamSet->bCnt;

        #ifdef SYSTEM_UTILS_DMA_PARAM_CHECK
        UTILS_assert(Utils_dmaParamSetCheck(pParamSet) == FVID2_SOK);
        #endif

        if(pInfo->dataFormat==SYSTEM_DF_YUV420SP_UV)
        {
            numTx++;

            if(numTx>=pObj->maxTransfers)
            {
                edma3Result += Utils_dmaRun(pObj, &numTx);
            }

            /* setup PaRAM for UV plane */
            pParamSet   = pObj->txObj[numTx].pParamSet;

            bpp = 1U;

            /*
             * For chroma plane when input or output is tiled we need to set
             * pitch as -32KB since other wise pitch value will overflow
             * the 16-bit register in EDMA.
             * Hence all for all Chroma TX's we set pitch as -pitch and DMA
             * from last line to first line
             *
             */

            pParamSet->destAddr = (UInt32)pInfo->destAddr[1]
                                + (pInfo->destPitch[1]
                                  *(((pInfo->destStartY+pInfo->height)/2U)-1U))
                                + (pInfo->destStartX * bpp);
            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
             * State: Fix in later release -> Waiver -> Case by case
             * IP reads data in a particular format. So pointer to int conversion
             * is required to put data in that format.
             */

            if(fillData)
            {
                pParamSet->srcAddr   = (UInt32)pInfo->srcAddr[1];
                /* MISRA.CAST.PTR_TO_INT
                 * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
                 * State: Fix in later release -> Waiver -> Case by case
                 * IP reads data in a particular format. So pointer to int conversion
                 * is required to put data in that format.
                 */

                pParamSet->srcBIdx   = 0;
            }
            else
            {
                pParamSet->srcAddr = (UInt32)pInfo->srcAddr[1]
                                   + (pInfo->srcPitch[1]
                                   * (((pInfo->srcStartY+pInfo->height)/2U)-1U))
                                   + (pInfo->srcStartX * bpp);
                /* MISRA.CAST.PTR_TO_INT
                 * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
                 * State: Fix in later release -> Waiver -> Case by case
                 * IP reads data in a particular format. So pointer to int conversion
                 * is required to put data in that format.
                 */
                pParamSet->srcBIdx   = -(Int32)1 * (Int32)pInfo->srcPitch[1];
            }

            pParamSet->destBIdx   = -(Int32)1 * (Int32)pInfo->destPitch[1];

            pParamSet->aCnt       = pInfo->width*bpp;
            pParamSet->bCnt       = pInfo->height/2U;
            pParamSet->cCnt       = 1U;

            pParamSet->bCntReload = pParamSet->bCnt;

            #ifdef SYSTEM_UTILS_DMA_PARAM_CHECK
            UTILS_assert(Utils_dmaParamSetCheck(pParamSet) == FVID2_SOK);
            #endif
        }

        /* goto next tranfer information */
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:Pointer is used in
         *                                             arithmetic or array
         *                                             index expression
         * State: Fix in later release -> Waiver -> Case by case
         * Pointer arithmetic is required for performance like auto
         * increment in loop.
         */
        pInfo++;
        numTx++;

        if(numTx>=pObj->maxTransfers)
        {
            edma3Result += Utils_dmaRun(pObj, &numTx);
        }
    }

    if(numTx)
    {
        edma3Result += Utils_dmaRun(pObj, &numTx);
    }

    BspOsal_semPost(pObj->semLock);

    return edma3Result;
}

/**
 *******************************************************************************
 *
 * \brief Fill data using EDMA
 *
 *        The API takes a mutual exclusion lock to allow the same API on the
 *        same logical channel be called from multiple thread contexts
 *
 * \param pObj          [IN] Logical DMA channel handle
 * \param pInfo         [IN] Array of DMA transfer parameter's
 * \param numTransfers  [IN] Number of transfers to perform
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaFill2D(Utils_DmaChObj *pObj, const Utils_DmaCopyFill2D *pInfo,
                        UInt32 numTransfers)
{
    return Utils_dmaCopyFill2D(pObj, pInfo, numTransfers, (Bool)TRUE);
}

/**
 *******************************************************************************
 *
 * \brief Copy data using EDMA
 *
 *        The API takes a mutual exclusion lock to allow the same API on the
 *        same logical channel be called from multiple thread contexts
 *
 * \param pObj          [IN] Logical DMA channel handle
 * \param pInfo         [IN] Array of DMA transfer parameter's
 * \param numTransfers  [IN] Number of transfers to perform
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaCopy2D(Utils_DmaChObj *pObj, const Utils_DmaCopyFill2D *pInfo,
                UInt32 numTransfers)
{
    return Utils_dmaCopyFill2D(pObj, pInfo, numTransfers, FALSE);
}

/**
 *******************************************************************************
 * \brief Max parameters to test DMA APIs for
 *******************************************************************************
 */
#define UTILS_DMA_TEST_MAX_PRM      (20U)

/**
 *******************************************************************************
 *
 * \brief Sample test routine to test the DMA APIs
 *
 *        This tests the APIs only from completion interrupt point of view
 *        Data transfer validity is not checked.
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_dmaTestCopyFill(Int32 doInitDeInit)
{
    Int32 status;
    Utils_DmaChObj  chDmaObj;
    Utils_DmaChCreateParams chDmaCreatePrm;
    Utils_DmaCopyFill2D dmaCopyFill2D[UTILS_DMA_TEST_MAX_PRM];
    UInt32 count, i, numTx;
    UInt32 *pCurAddr;
    Ptr srcAddr[2];
    Ptr dstAddr[2];
    UInt32 width, height, memSize, timeInMs;
    UInt32 mode, temp;

    if(doInitDeInit)
    {
        Utils_dmaInit();
    }

    count  = 10U;
    numTx  = UTILS_DMA_TEST_MAX_PRM;
    width  = 1920U;
    height = 1080U;

    memSize = width*height*6U;

    srcAddr[0U] = Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        memSize, 16U);
    UTILS_assert(srcAddr[0]!=NULL);
    temp = (UInt32)srcAddr[0U] + (width*height);
    srcAddr[1U] = (Ptr)temp;
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Fix in later release -> Waiver -> Case by case
     * To calculate pointer difference, we need to convert them
     */
    temp = (UInt32)srcAddr[0U] + (memSize/2U);
    dstAddr[0U] = (Ptr)temp;
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Fix in later release -> Waiver -> Case by case
     * To calculate pointer difference, we need to convert them
     */
    temp = (UInt32)dstAddr[0U] + (width*height);
    dstAddr[1U] = (Ptr)temp;
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Fix in later release -> Waiver -> Case by case
     * To calculate pointer difference, we need to convert them
     */

    memset(srcAddr[0U], 0, memSize/2U);

    pCurAddr = (Uint32*)srcAddr[0U];
    for(i=0U; i<((memSize/2U)/4U); i++) {
        *pCurAddr = i;
        pCurAddr++;
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:Pointer is used in
         *                                             arithmetic or array
         *                                             index expression
         * State: Fix in later release -> Waiver -> Case by case
         * Pointer arithmetic is required for performance like auto
         * increment in loop.
         */
    }

    memset(dstAddr[0], 0, memSize/2U);

    Cache_wbInv(srcAddr[0], memSize, Cache_Type_ALL, (Bool)TRUE);

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * MISRAC_WAIVER:
     * Source address is type casted to uint for printing
     */
    Vps_printf(" UTILS: DMA: DMA Test (SRC = 0x%08x, DST = 0x%08x)!!!\n",
                    (Uint32)srcAddr[0], (Uint32)dstAddr[0]
                );

    for(i=0U; i<UTILS_DMA_TEST_MAX_PRM; i++)
    {
        dmaCopyFill2D[i].dataFormat    = SYSTEM_DF_YUV420SP_UV;
        dmaCopyFill2D[i].destAddr[0]   = dstAddr[0U];
        dmaCopyFill2D[i].destAddr[1]   = dstAddr[1U];
        dmaCopyFill2D[i].destPitch[0]  = width;
        dmaCopyFill2D[i].destPitch[1]  = width;
        dmaCopyFill2D[i].destStartX    = 0U;
        dmaCopyFill2D[i].destStartY    = 0U;
        dmaCopyFill2D[i].width         = width;
        dmaCopyFill2D[i].height        = height;
        dmaCopyFill2D[i].srcAddr[0]    = srcAddr[0U];
        dmaCopyFill2D[i].srcAddr[1]    = srcAddr[1U];
        dmaCopyFill2D[i].srcPitch[0]   = width;
        dmaCopyFill2D[i].srcPitch[1]   = width;
        dmaCopyFill2D[i].srcStartX     = 0;
        dmaCopyFill2D[i].srcStartY     = 0;
    }

    Vps_printf(" UTILS: DMA: TEST: Started !!!"
               " (%d TXs per DMA API in a loop of %d)\r\n",
            numTx,
            count
        );

    for(mode=0U; mode<3U; mode++)
    {
        Utils_DmaChCreateParams_Init(&chDmaCreatePrm);

        chDmaCreatePrm.maxTransfers = numTx/3U;

        if(mode==0U)
        {
            Vps_printf(" UTILS: DMA: TEST: Test mode = Default EDMA, POLLED !!!");
            chDmaCreatePrm.enableIntCb = FALSE;
        }
        if(mode==1U)
        {
            Vps_printf(" UTILS: DMA: TEST: Test mode = Default EDMA, INTERRUPT !!!");
            chDmaCreatePrm.enableIntCb = TRUE;
        }
        if(mode==2U)
        {
            if((SYSTEM_PROC_DSP1 == System_getSelfProcId()) ||
               (SYSTEM_PROC_DSP2 == System_getSelfProcId()))
            {
                /* system and local EDMA only supported in DSP */
                Vps_printf(" UTILS: DMA: TEST: Test mode = System EDMA, POLLED mode !!!");
                chDmaCreatePrm.edmaInstId = UTILS_DMA_LOCAL_EDMA_INST_ID;
                chDmaCreatePrm.enableIntCb = FALSE;
            }
            else
            {
                Vps_printf(" UTILS: DMA: TEST: Test mode = Default EDMA, INTERRUPT !!!");
                chDmaCreatePrm.enableIntCb = TRUE;
            }
        }

        status = Utils_dmaCreateCh(&chDmaObj, &chDmaCreatePrm);
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

        timeInMs = (UInt32)Utils_getCurGlobalTimeInMsec();

        for(i=0U; i<count; i++)
        {
            status = Utils_dmaCopy2D(&chDmaObj, dmaCopyFill2D, numTx);
            UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

            status = Utils_dmaFill2D(&chDmaObj, dmaCopyFill2D, numTx);
            UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
        }

        timeInMs = (UInt32)Utils_getCurGlobalTimeInMsec() - timeInMs;

        Vps_printf(" UTILS: DMA: TEST: Completed in %d msecs \r\n", timeInMs);

        Utils_dmaDeleteCh(&chDmaObj);
    }
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, srcAddr[0], memSize);

     if(doInitDeInit)
     {
        Utils_dmaDeInit();
     }

    return status;
}

