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

#if ( defined(FATFS_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(FATFS_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

#include <src/rtos/utils_common/src/file_api_priv.h>

static void HSMMCSDEdmaCallback(uint32_t tcc, EDMA3_RM_TccStatus status,
                            void *appData)
{
    BspOsal_semPost(gFileSys_obj.edmaDone);
}

static EDMA3_DRV_Result HSMMCSDEdmaAllocCh(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    EDMA3_RM_TccCallback tccCb;
    UInt32 edmaChId, tccId;

    tccId       = pEdmaParam->chan;
    edmaChId    = pEdmaParam->chan;

    /* MISRA.CAST.FUNC_PTR:MISRAC_2004 Rule_11.1
       MISRAC_WAIVER:
       Typecasting callback function to EDMA callback function */
    tccCb = (EDMA3_RM_TccCallback)&HSMMCSDEdmaCallback;

    edma3Result = EDMA3_DRV_requestChannel(
                                    gFileSys_obj.hEdma,
                                    (uint32_t*)&edmaChId,
                                    (uint32_t*)&tccId,
                                    (EDMA3_RM_EventQueue)UTILS_DMA_DEFAULT_EVENT_Q,
                                    tccCb, (void *)edmaChId);

    UTILS_assert(edma3Result==EDMA3_DRV_SOK);

#if defined (TDA2XX_BUILD) || defined (TDA3XX_BUILD) || defined (TDA2EX_BUILD) || defined (TDA2PX_BUILD)
    {
        int32_t status;

        /* DMA XBar instance number is (channel number +1) in this case.
         * This might be different in other cases. Please refer TRM.
         */
        status = DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                                EDMA, pEdmaParam->chan + 1,
                                (xbar_evt_t) (pEdmaParam->dreq + 1));
        UTILS_assert(status == dma_xbar_success);
    }
#endif

    return edma3Result;

}

static EDMA3_DRV_Result HSMMCSDEdmaTrigger(const hsmmcsdEdmaParam_t *pEdmaParam, EDMA3_DRV_TrigMode mode)
{
    EDMA3_DRV_Result edma3Result;
    uint16_t tccStatus;

    edma3Result = EDMA3_DRV_checkAndClearTcc(gFileSys_obj.hEdma,
                                pEdmaParam->chan,
                                &tccStatus);
    if (EDMA3_DRV_SOK == edma3Result)
    {
        edma3Result = EDMA3_DRV_clearErrorBits (gFileSys_obj.hEdma,pEdmaParam->chan);

        if (EDMA3_DRV_SOK == edma3Result)
        {
            /* clear pending status, if any */
            BspOsal_semWait(gFileSys_obj.edmaDone, BSP_OSAL_NO_WAIT);

            edma3Result = EDMA3_DRV_enableTransfer (
                gFileSys_obj.hEdma,
                pEdmaParam->chan,
                mode);
        }
    }

    return edma3Result;
}

/*
 * This file implements function which enable EDMA with MMCSD drivers
 * used with FAT filesystem
 */

uint32_t HSMMCSDEdmaCopy(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    EDMA3_DRV_Result edma3Result;
    EDMA3_DRV_PaRAMRegs edmaParam;

    HSMMCSDEdmaAllocCh(pEdmaParam);

    edmaParam.srcAddr    = pEdmaParam->srcBfr;
    edmaParam.destAddr   = pEdmaParam->dstBfr;
    edmaParam.aCnt       = pEdmaParam->length;
    edmaParam.bCnt       = 1;
    edmaParam.cCnt       = 1;
    edmaParam.linkAddr   = 0xFFFF;
    edmaParam.opt        =
                 ((pEdmaParam->chan << EDMA3_CCRL_OPT_TCC_SHIFT)
                        & EDMA3_CCRL_OPT_TCC_MASK
                 )
               | (EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT)
               | ( EDMA3_CCRL_OPT_TCINTEN_ENABLE
                    << EDMA3_CCRL_OPT_TCINTEN_SHIFT)
                    ;

    edma3Result = EDMA3_DRV_setPaRAM(
                    gFileSys_obj.hEdma,
                    pEdmaParam->chan,
                    &edmaParam
                    );
    if (EDMA3_DRV_SOK == edma3Result)
    {
        edma3Result = HSMMCSDEdmaTrigger(pEdmaParam, EDMA3_DRV_TRIG_MODE_MANUAL);
        if (EDMA3_DRV_SOK == edma3Result)
        {
            HSMMCSDEdmaWaitTransfer(pEdmaParam->chan);
        }
    }
    UTILS_assert(EDMA3_DRV_SOK == edma3Result);

    HSMMCSDEdmaClose(pEdmaParam);

    return 1U;
}

uint32_t HSMMCSDEdmaTransfer(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    EDMA3_DRV_Result edma3Result;
    EDMA3_DRV_PaRAMRegs edmaParam;
    uint32_t          aCntValue, bCntValue, cCntValue;

    HSMMCSDEdmaAllocCh(pEdmaParam);

    /*calculate the aCnt, bCnt & cCnt values for AB-SYNC mode*/
    if (pEdmaParam->length < pEdmaParam->blockSize)
    {
        aCntValue = 4;
        bCntValue = pEdmaParam->length / 4;
        cCntValue = 1;
    }
    else
    {
        aCntValue = 4;
        bCntValue = pEdmaParam->blockSize / 4;
        cCntValue = pEdmaParam->length / pEdmaParam->blockSize;
    }

    /* Program the PaRam set*/
    edmaParam.srcAddr    = pEdmaParam->srcBfr;
    edmaParam.destAddr   = pEdmaParam->dstBfr;
    edmaParam.aCnt       = aCntValue;
    edmaParam.bCnt       = bCntValue;
    edmaParam.cCnt       = cCntValue;
    if(pEdmaParam->rwflag == FLAG_READ)
    {
        edmaParam.srcBIdx    = 0;
        edmaParam.destBIdx   = 4;
        edmaParam.srcCIdx    = 0;
        edmaParam.destCIdx   = aCntValue * bCntValue;
    }
    else
    {
        edmaParam.srcBIdx    = 4;
        edmaParam.destBIdx   = 0;
        edmaParam.srcCIdx    = aCntValue * bCntValue;
        edmaParam.destCIdx   = 0;
    }
    edmaParam.bCntReload = bCntValue;
    edmaParam.linkAddr   = 0xFFFF;
    edmaParam.opt        =
                ((pEdmaParam->chan << EDMA3_CCRL_OPT_TCC_SHIFT)
                        & EDMA3_CCRL_OPT_TCC_MASK
                 )
               | (EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT)
               | ( EDMA3_CCRL_OPT_TCINTEN_ENABLE
                    << EDMA3_CCRL_OPT_TCINTEN_SHIFT)
                    ;


    edma3Result = EDMA3_DRV_setPaRAM(
                    gFileSys_obj.hEdma,
                    pEdmaParam->chan,
                    &edmaParam
                    );
    if (EDMA3_DRV_SOK == edma3Result)
    {
        edma3Result = HSMMCSDEdmaTrigger(pEdmaParam, EDMA3_DRV_TRIG_MODE_EVENT);
    }
    UTILS_assert(EDMA3_DRV_SOK == edma3Result);

    return 1U;
}

uint32_t HSMMCSDEdmaClose(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    EDMA3_DRV_Result edma3Result;
    uint16_t tccStatus;

#ifdef TDA2XX_FAMILY_BUILD

    /* Disconnect the event source & channel map */
    DMAXBARDisconnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                      pEdmaParam->chan + 1);
#endif

    EDMA3_DRV_checkAndClearTcc(
                    gFileSys_obj.hEdma,
                    pEdmaParam->chan,
                    &tccStatus);
    EDMA3_DRV_clearErrorBits(
                    gFileSys_obj.hEdma,
                    pEdmaParam->chan
                );

    edma3Result = EDMA3_DRV_freeChannel(
                            gFileSys_obj.hEdma,
                            pEdmaParam->chan
                      );
    UTILS_assert(edma3Result==EDMA3_DRV_SOK);

    return 1U;
}

void HSMMCSDEdmaWaitTransfer(uint32_t edmaChan)
{
    BspOsal_semWait(gFileSys_obj.edmaDone, BSP_OSAL_WAIT_FOREVER);
}

void HSMMCSDUartPuts(const char *string)
{
    #ifdef UTILS_FILE_API_DEBUG
    Vps_printf(string);
    #endif
}

void HSMMCSDUARTPutNum(int32_t value)
{
    #ifdef UTILS_FILE_API_DEBUG
    Vps_printf("%d", value);
    #endif
}

#else
#include <src/rtos/utils_common/src/file_api_priv.h>

/* Dummy APIs for FATFS_PROC = none */
uint32_t HSMMCSDEdmaClose(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    return 1U;
}

uint32_t HSMMCSDEdmaTransfer(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    return 1U;
}

void HSMMCSDEdmaWaitTransfer(uint32_t edmaChan)
{
    return;
}

void HSMMCSDUARTPutNum(int32_t value)
{
    return;
}

void HSMMCSDUartPuts(const char *string)
{
    return;
}

#endif

