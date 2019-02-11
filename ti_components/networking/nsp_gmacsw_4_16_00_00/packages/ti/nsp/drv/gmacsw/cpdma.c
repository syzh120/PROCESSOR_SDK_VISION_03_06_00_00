/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 *   \file  cpdma.c
 *
 *   \brief
 *          CPDMA Host Port functionality
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Project dependency headers */
#if defined(USE_CSLR)
#include "cslr.h"
#include "cslr_gmacsw.h"
#else
#include "soc.h"
#include "gmac_sw.h"
#endif
#include "gmacsw_al.h"
#include "private/debug_.h"

/* This module's private header */
#include "private/cpdma_.h"

/* This module's header */
#include "cpdma.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static uint32_t         LOCAL_openRxChannel(CPDMA_Handle hCpdma, const CPDMA_RxChannelConfig *pCPDMAChannelConfig, CPDMA_ChannelHandle *pChannelHandle);
static uint32_t         LOCAL_closeRxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);
static uint32_t         LOCAL_startRxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);
static uint32_t         LOCAL_stopRxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);

static uint32_t         LOCAL_openTxChannel(CPDMA_Handle hCpdma, const CPDMA_TxChannelConfig *pCPDMAChannelConfig, CPDMA_ChannelHandle *pChannelHandle);
static uint32_t         LOCAL_closeTxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);
static uint32_t         LOCAL_startTxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);
static uint32_t         LOCAL_stopTxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);

static CPDMA_Packet     *LOCAL_packetDequeueWithDescUnlink(CPDMA_PacketQueue *pCPDMAPacketQueue);

static void             LOCAL_buffDescEnqueue(CPDMA_BuffDescQueue *pCPDMABuffDescQueue, CPDMA_BuffDesc *pCPDMABuffDesc);
static CPDMA_BuffDesc   *LOCAL_buffDescDequeue(CPDMA_BuffDescQueue *pCPDMABuffDescQueue);

static uint32_t         LOCAL_retrievePacketQueueFromChannel(CPDMA_ChannelHandle hCPDMAChannel, CPDMA_PacketQueue *pFromChannelQueue);
static uint32_t         LOCAL_submitPacketQueueToChannel(CPDMA_ChannelHandle hCPDMAChannel, CPDMA_PacketQueue *pToChannelQueue);
static void             LOCAL_deliverPackets(CPDMA_Channel *pChannel);

static uint32_t         LOCAL_isBitSet(uint32_t bitNum, uint32_t bitVector);


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(NSP_DYNAMIC_ALLOCATION)
static CPDMA_State CPDMA_stateObj;
#endif

/* Data to keep track of open references to the CPDMA */
static uint32_t     LOCAL_cpdmaRefCount = 0;
static CPDMA_State  *LOCAL_cpdmaRef     = NULL;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

#if defined(NSP_INSTRUMENTATION_ENABLED)
CPDMA_Stats cpdmaStats;
#endif


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

/*! ============================================================================
 *  @n@b CPDMA_open()
 *
 *  @b Description
 *  @n This function opens and sets up the DMA port and channel for communication.
 *
 *  @b Arguments
 *  @verbatim
 *      hPort               Handle to the Port object to setup
    @endverbatim
 *
 *  <b> Return Value </b>
 *      CPSWG3_SUCCESS      DMA open successful
 *      error value         DMA open failed
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b> None
 *
 *  @b Example
    @endverbatim
 * ============================================================================
 */
CPDMA_Handle CPDMA_open(CPDMA_Config *pCPDMAConfig)
{
    CPDMA_State     *pCPDMAState    = NULL;
    uint32_t        dmaControlVal   = 0;
    uint32_t        channelNum;
    uint32_t        i;

    uint32_t        key = GMACSW_AL_globalInterruptDisable();

    /* Increment the reference count */
    LOCAL_cpdmaRefCount++;

    if ((uint32_t)1U == LOCAL_cpdmaRefCount)
    {
        /*  Validate the supplied configuration structure */
        if (NULL != pCPDMAConfig)
        {

#if defined(NSP_DYNAMIC_ALLOCATION)
            pCPDMAState = (CPDMA_State *) calloc(1U, sizeof(CPDMA_State));
#else
            pCPDMAState = &CPDMA_stateObj;
#endif

            /* Zero init the CPDMA_State structure */
            memset(pCPDMAState, 0, sizeof(CPDMA_State));

#if defined(NSP_INSTRUMENTATION_ENABLED)
            /* Zero init the CPDMA instrumentation structure */
            memset(&cpdmaStats, 0, sizeof(CPDMA_Stats));
#endif

            /*
             *  Initialize the CPDMA and STATERAM Hardware Registers
             *  to a known state
             */

            /* CPDMA soft reset */
            GMACSW_REGS->CPDMA.CPDMA_SOFT_RESET =
                CSL_FMK(GMACSW_CPDMA_SOFT_RESET_SOFT_RESET, CSL_GMACSW_CPDMA_SOFT_RESET_SOFT_RESET_RESET);

            /* wait for reset complete */
            {
                uint32_t hasReset = CSL_FEXT(GMACSW_REGS->CPDMA.CPDMA_SOFT_RESET, GMACSW_CPDMA_SOFT_RESET_SOFT_RESET);
                while (hasReset != 0U)
                {
                    hasReset = CSL_FEXT(GMACSW_REGS->CPDMA.CPDMA_SOFT_RESET, GMACSW_CPDMA_SOFT_RESET_SOFT_RESET);
                }
            }


            /* Init the CPDMA StateRam buffer descriptor pointers */
            for (channelNum = 0; channelNum < CPDMA_MAX_TX_CHANNELS; channelNum++)
            {
                GMACSW_REGS->STATERAM.TX_HDP[channelNum] = 0;
                GMACSW_REGS->STATERAM.TX_CP[channelNum] = 0;

            }
            for (channelNum = 0; channelNum < CPDMA_MAX_RX_CHANNELS; channelNum++)
            {
                GMACSW_REGS->STATERAM.RX_HDP[channelNum] = 0;
                GMACSW_REGS->STATERAM.RX_CP[channelNum] = 0;
            }

            /* Set the DMACONTROL register */
            dmaControlVal = 0;
            if (NOT_ZERO(pCPDMAConfig->dmaModeFlags & CPDMA_CONFIG_MODEFLG_PASSERROR))
            {
                dmaControlVal |= CSL_FMK(GMACSW_CPDMA_DMACONTROL_RX_CEF, 1U);
            }
            if (NOT_ZERO(pCPDMAConfig->dmaModeFlags & CPDMA_CONFIG_MODEFLG_CMDIDLE))
            {
                dmaControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_CMD_IDLE, 1U);
            }
            if (NOT_ZERO(pCPDMAConfig->dmaModeFlags & CPDMA_CONFIG_MODEFLG_RXOFFLENBLOCK))
            {
                dmaControlVal |= CSL_FMK(GMACSW_CPDMA_DMACONTROL_RX_OFFLEN_BLOCK, 1U);
            }
            if (NOT_ZERO(pCPDMAConfig->dmaModeFlags & CPDMA_CONFIG_MODEFLG_RXOWNERSHIP))
            {
                dmaControlVal |= CSL_FMK(GMACSW_CPDMA_DMACONTROL_RX_OWNERSHIP, 1U);
            }
            if (NOT_ZERO(pCPDMAConfig->dmaModeFlags & CPDMA_CONFIG_MODEFLG_CHPRIORITY))
            {
                dmaControlVal |= CSL_FMK(GMACSW_CPDMA_DMACONTROL_TX_PTYPE, 1U);
            }

            GMACSW_REGS->CPDMA.CPDMA_DMACONTROL = dmaControlVal;

            /* Set the rx buffer offset */
            GMACSW_REGS->CPDMA.CPDMA_RX_BUFFER_OFFSET = pCPDMAConfig->rxBufferOffset;

            /* Disable interrupts TX_INTMASK_CLEAR,RX_INTMASK_CLEAR & DMA_INTMASK_CLEAR */
            GMACSW_REGS->CPDMA.CPDMA_TX_INTMASK_CLEAR   = CSL_GMACSW_CPDMA_TX_INTMASK_CLEAR_RESETVAL;
            GMACSW_REGS->CPDMA.CPDMA_RX_INTMASK_CLEAR   = CSL_GMACSW_CPDMA_RX_INTMASK_CLEAR_RESETVAL;
            GMACSW_REGS->CPDMA.CPDMA_DMA_INTMASK_CLEAR  = CSL_GMACSW_CPDMA_DMA_INTMASK_CLEAR_RESETVAL;

            /* Enable TX/RX DMA */
            GMACSW_REGS->CPDMA.CPDMA_TX_CONTROL |=
                CSL_FMK(GMACSW_CPDMA_TX_CONTROL_TX_EN, CSL_GMACSW_CPDMA_TX_CONTROL_TX_EN_ENABLE);
            GMACSW_REGS->CPDMA.CPDMA_RX_CONTROL |=
                CSL_FMK(GMACSW_CPDMA_RX_CONTROL_RX_EN, CSL_GMACSW_CPDMA_RX_CONTROL_RX_EN_ENABLE);

            /* Enable host port error interrupts */
            GMACSW_REGS->CPDMA.CPDMA_DMA_INTMASK_SET |=
                CSL_FMK(GMACSW_CPDMA_DMA_INTMASK_SET_HOST_ERR_INT_MASK, 1);

            /* Enable host error interrupt in GMACSW subsystem wrapper */
            GMACSW_REGS->WR.WR_C0_MISC_EN |=
                CSL_FMK(GMACSW_WR_C0_MISC_EN_HOST_PEND,0x1U);

            /* Enable CPDMA Rx and/or Tx interrupt pacing */
            if ( (pCPDMAConfig->rxInterruptPacingEnabled != 0U) || (pCPDMAConfig->txInterruptPacingEnabled != 0U))
            {
                uint32_t intPaceEnField = 0;
                /* Calculate prescale count to get 5us pulse from MAIN_CLK */
                /* TODO: Check generated ASM code to make sure the formula is calculated correctly */
#if (1)
                CSL_FINS(GMACSW_REGS->WR.WR_INT_CONTROL, GMACSW_WR_INT_CONTROL_INT_PRESCALE, ((pCPDMAConfig->pacingClkFreq * (uint32_t) 5U) / (uint32_t)1000000U));
#else
                CSL_FINS(GMACSW_REGS->WR.WR_INT_CONTROL, GMACSW_WR_INT_CONTROL_INT_PRESCALE,(uint32_t) ((pCPDMAConfig->pacingClkFreq * 5.0F) / 1000000.0));
#endif

                if (pCPDMAConfig->rxInterruptPacingEnabled)
                {
                    CSL_FINS(GMACSW_REGS->WR.WR_C0_RX_IMAX, GMACSW_WR_C0_RX_IMAX_RX_IMAX, pCPDMAConfig->rxInterruptsPerMsec);
                    intPaceEnField |= CSL_GMACSW_WR_INT_CONTROL_INT_PACE_EN_C0_RX;
                }

                if (pCPDMAConfig->txInterruptPacingEnabled)
                {
                    CSL_FINS(GMACSW_REGS->WR.WR_C0_TX_IMAX, GMACSW_WR_C0_TX_IMAX_TX_IMAX, pCPDMAConfig->txInterruptsPerMsec);
                    intPaceEnField |= CSL_GMACSW_WR_INT_CONTROL_INT_PACE_EN_C0_TX;
                }
                CSL_FINS(GMACSW_REGS->WR.WR_INT_CONTROL, GMACSW_WR_INT_CONTROL_INT_PACE_EN, intPaceEnField);
            }

            /*
             * Populate the CPDMA State Object based on the configuration input
             */

            /* Initialize the free buffer descriptor queue */
            CPDMA_buffDescQueueInit(&pCPDMAState->freeDescriptorQueue);

            /*
             * Add all descriptors to the CPDMA free descriptor queue.  These
             * descriptors will then be given out to particular channels when
             * those channels are opened.
             */
            {
                if(NULL != pCPDMAConfig->buffDescMemCfg.buffDescMem)
                {
                    /* Use application provided buff desc. memory */
                    CPDMA_BuffDesc *pFreeDesc = pCPDMAConfig->buffDescMemCfg.buffDescMem;

                    for (i=0; i < pCPDMAConfig->buffDescMemCfg.buffDescCnt; i++)
                    {
                        LOCAL_buffDescEnqueue(&pCPDMAState->freeDescriptorQueue, &pFreeDesc[i]);
                    }
                }
                else
                {
                    /*
                     * Use CPPI internal RAM as application has not provided any
                     * buffer descriptor memory
                     */
                    /* Double cast to avoid MISRA-C:2004 11.4 */
                    CPDMA_BuffDesc *pFreeDesc = (CPDMA_BuffDesc *) ((void *)&(GMACSW_REGS->CPPI_RAM.RAM));

                    for (i=0; i < CPDMA_CPPI_BUF_DESC_MAX_COUNT; i++)
                    {
                        LOCAL_buffDescEnqueue(&pCPDMAState->freeDescriptorQueue, &pFreeDesc[i]);
                    }
                }
            }

            /* Save a pointer to the initial config structure used to open the CPDMA */
            pCPDMAState->pCPDMAConfig = pCPDMAConfig;

            /* Save a pointer to the state structure to be used to provide a reference for future open calls */
            LOCAL_cpdmaRef = pCPDMAState;
        }
        else
        {
            /* Decrement ref count as we are returning NULL */
            LOCAL_cpdmaRefCount--;
        }
    }
    else
    {
        /*
         * If reference count at entry was non-zero, CPDMA was already opened, so
         * we just return a pointer to the state structure and increment the reference count
         */
        pCPDMAState = LOCAL_cpdmaRef;
    }

    GMACSW_AL_globalInterruptEnable(key);

    return pCPDMAState;
}

/*! ============================================================================
 *  @n@b CPDMA_close()
 *
 *  @b Description
 *  @n This function closes and de-initializes up the DMA port and channels.
 *
 *  @b Arguments
 *  @verbatim
 *      hPort               Handle to the Port object to close
    @endverbatim
 *
 *  <b> Return Value </b>
 *      CPSWG3_SUCCESS      DMA close successful
 *      error value         DMA close failed
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b> None
 *
 *  @b Example
    @endverbatim
 * ============================================================================
 */
uint32_t CPDMA_close(CPDMA_Handle hCpdma)
{
    CPDMA_State *pCPDMAState = (CPDMA_State *) hCpdma;
    uint32_t retVal = CPDMA_SUCCESS;
    uint32_t key = GMACSW_AL_globalInterruptDisable();

    /* Decrement reference counter and return if still non-zero */
    LOCAL_cpdmaRefCount--;

    if (0 == LOCAL_cpdmaRefCount)
    {
        uint32_t channelNum;

        /*
         *  Finalize the CPDMA and STATERAM Hardware Registers
         */

        /* Disable TX/RX DMA */
        GMACSW_REGS->CPDMA.CPDMA_TX_CONTROL = 0;
        GMACSW_REGS->CPDMA.CPDMA_RX_CONTROL = 0;

        /* Disable Adapter check interrupts - Disable stats interupt */
        GMACSW_REGS->CPDMA.CPDMA_DMA_INTMASK_CLEAR =
            CSL_FMK(GMACSW_CPDMA_DMA_INTMASK_CLEAR_HOST_ERR_INT_MASK, 0x1U) |
            CSL_FMK(GMACSW_CPDMA_DMA_INTMASK_CLEAR_STAT_INT_MASK, 0x1U);

        /* Disable host,stats interrupt in the GMACSW subsystem wrapper */
        GMACSW_REGS->WR.WR_C0_MISC_EN &=
            ~(CSL_FMK(GMACSW_WR_C0_MISC_EN_HOST_PEND,0x1U) |
              CSL_FMK(GMACSW_WR_C0_MISC_EN_STAT_PEND,0x1U));

        /* CPDMA soft reset */
        GMACSW_REGS->CPDMA.CPDMA_SOFT_RESET =
            CSL_FMK(GMACSW_CPDMA_SOFT_RESET_SOFT_RESET, CSL_GMACSW_CPDMA_SOFT_RESET_SOFT_RESET_RESET);

        /* wait for reset complete */
        {
            uint32_t hasReset = CSL_FEXT(GMACSW_REGS->CPDMA.CPDMA_SOFT_RESET, GMACSW_CPDMA_SOFT_RESET_SOFT_RESET);
            while (hasReset != 0U)
            {
                hasReset = CSL_FEXT(GMACSW_REGS->CPDMA.CPDMA_SOFT_RESET, GMACSW_CPDMA_SOFT_RESET_SOFT_RESET);
            }
        }


        /*
         * Clean up the CPDMA State Object and channel book keeping structures
         */

        /* Stop and close any open TX Channels */
        for (channelNum = 0; channelNum < CPDMA_MAX_TX_CHANNELS; channelNum++)
        {
            /* Double cast to avoid MISRA-C:2004 11.4 */
            CPDMA_Channel *pChannel = (CPDMA_Channel *) ((void *)&pCPDMAState->txChannel[channelNum]);
            if (pChannel->isStarted == 1U)
            {
                LOCAL_stopTxChannel(hCpdma, pChannel);
            }
            if (pChannel->isOpened == 1U)
            {
                LOCAL_closeTxChannel(hCpdma, pChannel);
            }
        }

        /* Stop and close any open RX Channels */
        for (channelNum = 0; channelNum < CPDMA_MAX_RX_CHANNELS; channelNum++)
        {
            /* Double cast to avoid MISRA-C:2004 11.4 */
            CPDMA_Channel *pChannel = (CPDMA_Channel *) ((void *)&pCPDMAState->rxChannel[channelNum]);
            if (pChannel->isStarted == 1U)
            {
                LOCAL_stopRxChannel(hCpdma, pChannel);
            }
            if (pChannel->isOpened == 1U)
            {
                LOCAL_closeRxChannel(hCpdma, pChannel);
            }
        }

        /* Reset the local reference holder */
        LOCAL_cpdmaRef = NULL;

#if defined(NSP_DYNAMIC_ALLOCATION)
        free(pCPDMAState);
#else
        memset(pCPDMAState, 0 , sizeof(CPDMA_State));
#endif
    }

    GMACSW_AL_globalInterruptEnable(key);

    return retVal;
}

/*! ============================================================================
 *  @n@b CPDMA_ioctl()
 *
 *  @b Description
 *  @n This function is used to perform IOCTL calls against the CPDMA instance.
 *
 *  @b Arguments
 *  @verbatim
 *      hCpdma              Handle to the CPDMA object
    @endverbatim
 *
 *  <b> Return Value </b>
 *      CPDMA_UNKNOWN_IOCTL     IOCTL code/operation unknown
 *      CPDMA_MALFORMED_IOCTL   IOCTL code valid, but param/size are wrong
 *      return value            IOCTL result for the specified operation
 *
 *  <b> Pre Condition </b> None
 *
 *  <b> Post Condition </b> None
 *
 *  @b Example
    @endverbatim
 * ============================================================================
 */
uint32_t CPDMA_ioctl(CPDMA_Handle hCpdma, uint32_t cmd, void *param, uint32_t size)
{
    uint32_t retVal = CPDMA_FAILURE;

    /* Decode the command and act on it */
    switch (cmd)
    {
        case GMACSW_IOCTL_CPDMA_OPEN_RX_CHANNEL:
        {
            if ((sizeof(CPDMA_OpenRxChannelIoctlCmd) != size) || (NULL == param))
            {
                retVal = CPDMA_MALFORMED_IOCTL;
            }
            else
            {
                CPDMA_OpenRxChannelIoctlCmd *pCmd   = (CPDMA_OpenRxChannelIoctlCmd *) param;
                CPDMA_RxChannelConfig *pConfig      = pCmd->pRxChannelConfig;
                CPDMA_ChannelHandle *pChannelHandle = pCmd->pRxChannelHandle;
                retVal = LOCAL_openRxChannel(hCpdma, pConfig, pChannelHandle);
            }
            break;
        }
        case GMACSW_IOCTL_CPDMA_CLOSE_RX_CHANNEL:
        {
            if ((sizeof(CPDMA_ChannelHandle) != size) || (NULL == param))
            {
                retVal = CPDMA_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_closeRxChannel(hCpdma, * ((CPDMA_ChannelHandle *) param));
            }
            break;
        }
        case GMACSW_IOCTL_CPDMA_START_RX_CHANNEL:
        {
            if ((sizeof(CPDMA_ChannelHandle) != size) || (NULL == param))
            {
                retVal = CPDMA_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_startRxChannel(hCpdma, *((CPDMA_ChannelHandle *) param));
            }
            break;
        }
        case GMACSW_IOCTL_CPDMA_STOP_RX_CHANNEL:
        {
            if ((sizeof(CPDMA_ChannelHandle) != size) || (NULL == param))
            {
                retVal = CPDMA_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_stopRxChannel(hCpdma, *((CPDMA_ChannelHandle *) param));
            }
            break;
        }
        case GMACSW_IOCTL_CPDMA_OPEN_TX_CHANNEL:
        {
            if ((sizeof(CPDMA_OpenTxChannelIoctlCmd) != size) || (NULL == param))
            {
                retVal = CPDMA_MALFORMED_IOCTL;
            }
            else
            {
                CPDMA_OpenTxChannelIoctlCmd *pCmd   = (CPDMA_OpenTxChannelIoctlCmd *) param;
                CPDMA_TxChannelConfig *pConfig      = pCmd->pTxChannelConfig;
                CPDMA_ChannelHandle *pChannelHandle = pCmd->pTxChannelHandle;
                retVal = LOCAL_openTxChannel(hCpdma, pConfig, pChannelHandle);
            }
            break;
        }
        case GMACSW_IOCTL_CPDMA_CLOSE_TX_CHANNEL:
        {
            if ((sizeof(CPDMA_ChannelHandle) != size) || (NULL == param))
            {
                retVal = CPDMA_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_closeTxChannel(hCpdma, * ((CPDMA_ChannelHandle *) param));
            }
            break;
        }
        case GMACSW_IOCTL_CPDMA_START_TX_CHANNEL:
        {
            if ((sizeof(CPDMA_ChannelHandle) != size) || (NULL == param))
            {
                retVal = CPDMA_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_startTxChannel(hCpdma, *((CPDMA_ChannelHandle *) param));
            }
            break;
        }
        case GMACSW_IOCTL_CPDMA_STOP_TX_CHANNEL:
        {
            if ((sizeof(CPDMA_ChannelHandle) != size) || (NULL == param))
            {
                retVal = CPDMA_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_stopTxChannel(hCpdma, *((CPDMA_ChannelHandle *) param));
            }
            break;
        }
        case GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS:
        {
            if ((sizeof(CPDMA_RetrievePacketQueueIoctlCmd) != size) || (NULL == param))
            {
                retVal = CPDMA_MALFORMED_IOCTL;
            }
            else
            {
                CPDMA_RetrievePacketQueueIoctlCmd *pCmd = (CPDMA_RetrievePacketQueueIoctlCmd *) param;
                CPDMA_ChannelHandle hCPDMAChannel       = pCmd->hChannel;
                CPDMA_PacketQueue *pPacketQueue         = pCmd->pFromChannelQueue;
                retVal = LOCAL_retrievePacketQueueFromChannel(hCPDMAChannel, pPacketQueue);
            }
            break;
        }
        case GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS:
        {
            if ((sizeof(CPDMA_SubmitPacketQueueIoctlCmd) != size) || (NULL == param))
            {
                retVal = CPDMA_MALFORMED_IOCTL;
            }
            else
            {
                CPDMA_SubmitPacketQueueIoctlCmd *pCmd   = (CPDMA_SubmitPacketQueueIoctlCmd *) param;
                CPDMA_ChannelHandle hCPDMAChannel       = pCmd->hChannel;
                CPDMA_PacketQueue *pPacketQueue         = pCmd->pToChannelQueue;
                retVal = LOCAL_submitPacketQueueToChannel(hCPDMAChannel, pPacketQueue);
            }
            break;
        }
        default:
        {
            retVal = CPDMA_UNKNOWN_IOCTL;
            break;
        }
    }

    return retVal;
}

void CPDMA_packetEnqueue(CPDMA_PacketQueue *pCPDMAPacketQueue, CPDMA_Packet *pCPDMAPacket)
{
    uint32_t key = GMACSW_AL_globalInterruptDisable();

    pCPDMAPacket->pNextPacket = NULL;

    if (NULL == pCPDMAPacketQueue->pHead)
    {
        /* Queue is empty, make head point to new packet */
        pCPDMAPacketQueue->pHead = pCPDMAPacket;
    }
    else
    {
        /* Queue is not empty, make previous tail point to new packet */
        pCPDMAPacketQueue->pTail->pNextPacket = pCPDMAPacket;
    }

    /* Make tail of queue point to new */
    pCPDMAPacketQueue->count++;
    pCPDMAPacketQueue->pTail = pCPDMAPacket;

    GMACSW_AL_globalInterruptEnable(key);
}

CPDMA_Packet *CPDMA_packetDequeue(CPDMA_PacketQueue *pCPDMAPacketQueue)
{
    CPDMA_Packet *pCPDMAPacket = NULL;

    if (NULL != pCPDMAPacketQueue)
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();
        pCPDMAPacket = pCPDMAPacketQueue->pHead;

        if (NULL != pCPDMAPacket)
        {
            pCPDMAPacketQueue->pHead = pCPDMAPacket->pNextPacket;
            if (NULL == pCPDMAPacketQueue->pHead)
            {
                pCPDMAPacketQueue->pTail = NULL;
            }
            pCPDMAPacketQueue->count--;
            pCPDMAPacket->pNextPacket = NULL;
        }
        GMACSW_AL_globalInterruptEnable(key);
    }

    return (pCPDMAPacket);
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

/* LOCAL IOCTL implementations */
static uint32_t LOCAL_openRxChannel(CPDMA_Handle hCpdma, const CPDMA_RxChannelConfig *pCPDMAChannelConfig, CPDMA_ChannelHandle *pChannelHandle)
{
    CPDMA_State *pCPDMAState = (CPDMA_State *) hCpdma;
    uint32_t retVal = CPDMA_FAILURE;

    if ((NULL != pCPDMAState) &&
        (NULL != pCPDMAChannelConfig) &&
        (NULL != pChannelHandle))
    {
        uint32_t channelNum = 0;

        /* Find first open channel */
        {
            uint32_t key = GMACSW_AL_globalInterruptDisable();

            while ( (LOCAL_isBitSet(channelNum, pCPDMAState->rxChannelBitVector) == 1U) &&
                    (channelNum < CPDMA_MAX_RX_CHANNELS))
            {
                channelNum++;
            }

            if (CPDMA_MAX_RX_CHANNELS <= channelNum)
            {
                retVal =  CPDMA_NO_RX_CHANNELS_AVAILABLE;
            }
            else
            {
                pCPDMAState->rxChannelBitVector |= ((uint32_t)0x1U << channelNum);
            }
            GMACSW_AL_globalInterruptEnable(key);
        }

        if (retVal != CPDMA_NO_RX_CHANNELS_AVAILABLE)
        {
            CPDMA_RxChannel *pRxChannel = &(pCPDMAState->rxChannel[channelNum]);
            CPDMA_Channel *pChannel     = (CPDMA_Channel *)((void *)&(pCPDMAState->rxChannel[channelNum]));

            /* Check to make sure the callback functions are all defined */
            if ((NULL == pCPDMAChannelConfig->callbacks.pFxnCbCloseChannel) ||
                (NULL == pCPDMAChannelConfig->callbacks.pFxnCbUsedPacketNotify))
            {
                retVal = CPDMA_INVALID_PARAM;
            }
            else
            {
                uint32_t packetCount;

                /* Fill in channel fields */
                pChannel->channelDir            = CPDMA_DIRECTION_RX;
                pChannel->channelNum            = channelNum;
                pChannel->isOpened              = 1U;
                pChannel->packetCount           = pCPDMAChannelConfig->packetCount;
                pChannel->packetMem             = (CPDMA_Packet *)pCPDMAChannelConfig->packetMem;
                pRxChannel->rxThreshCount       = pCPDMAChannelConfig->rxThreshCount;

                /* Save the callback configuration info to the channel structure*/
                memcpy(&pChannel->callbacks, &pCPDMAChannelConfig->callbacks, sizeof(CPDMA_Callbacks));

                /* Initialize the toHardware, InUse and fromHardware queue */
                CPDMA_packetQueueInit(&pChannel->toHardwarePacketQueue);
                CPDMA_packetQueueInit(&pChannel->inUsePacketQueue);
                CPDMA_packetQueueInit(&pChannel->fromHardwarePacketQueue);

                /* Try to allocate all packets and their descriptors for this channel */
                for (packetCount = 0U; packetCount < (uint32_t)pChannel->packetCount; packetCount++)
                {
                    uint32_t descCount = 0;
                    CPDMA_Packet *pCPDMAPacket = &((pChannel->packetMem)[packetCount]);

                    /* Zero init the packet */
                    CPDMA_packetInit(pCPDMAPacket);

                    /* Zero init the packet buffer descriptor queue */
                    CPDMA_buffDescQueueInit(&pCPDMAPacket->buffDescQueue);

                    /* Allocate buffer descriptors from the CPDMA state object */
                    while (descCount < (uint32_t)pCPDMAChannelConfig->buffersPerPacketCount)
                    {
                        CPDMA_BuffDesc *pCPDMABuffDesc = LOCAL_buffDescDequeue(&pCPDMAState->freeDescriptorQueue);

                        if (pCPDMABuffDesc != NULL)
                        {
                            /* Clear the buffer descriptor out of the free queue */
                            CPDMA_buffDescInit(pCPDMABuffDesc);
                            LOCAL_buffDescEnqueue(&pCPDMAPacket->buffDescQueue, pCPDMABuffDesc);
                            descCount++;
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (pCPDMAChannelConfig->buffersPerPacketCount == descCount)
                    {
                        CPDMA_packetEnqueue(&pChannel->fromHardwarePacketQueue, pCPDMAPacket);
                    }
                    else
                    {
                        /* Mark the failure so we can clean up */
                        retVal = CPDMA_INSUFFICENT_BUFF_DESC;
                        break;
                    }
                }

                /* If the allocation appears to have failed, clean up as best we can */
                if (CPDMA_INSUFFICENT_BUFF_DESC == retVal)
                {
                    /* Free the ones were able to allocate before the failure back to the global pool */
                    for (packetCount = 0U; packetCount < (uint32_t)pChannel->packetCount; packetCount++)
                    {
                        uint32_t descCount = 0;
                        CPDMA_Packet *pCPDMAPacket = &((pChannel->packetMem)[packetCount]);

                        while (descCount < (uint32_t)pCPDMAChannelConfig->buffersPerPacketCount)
                        {
                            CPDMA_BuffDesc *pCPDMABuffDesc = LOCAL_buffDescDequeue(&pCPDMAPacket->buffDescQueue);

                            if (pCPDMABuffDesc != NULL)
                            {
                                /* Clear the buffer descriptor out of the free queue */
                                CPDMA_buffDescInit(pCPDMABuffDesc);
                                LOCAL_buffDescEnqueue(&pCPDMAState->freeDescriptorQueue, pCPDMABuffDesc);
                                descCount++;
                            }
                            else
                            {
                                break;
                            }
                        }

                        if (descCount != pCPDMAChannelConfig->buffersPerPacketCount)
                        {
                            break;
                        }
                        else
                        {
                            CPDMA_packetInit(pCPDMAPacket);
                        }
                    }
                }
                else
                {
                    /* Set the return handle */
                    *pChannelHandle = (CPDMA_ChannelHandle) pChannel;

                    /*
                     * If RX_THRESH interrupts are enabled for this channel, setup the
                     * PENDTHRESH and FREEBUFFER registers.
                     */
                    if (0U != pRxChannel->rxThreshCount)
                    {
                        /* Set the threshold for the RX_THRESH interrupt trigger */
                        GMACSW_REGS->CPDMA.CPDMA_RX_PENDTHRESH[channelNum] =
                            CSL_FMK(GMACSW_CPDMA_RX_PENDTHRESH_RX_PENDTHRESH,pRxChannel->rxThreshCount);

                        /*
                         * Reset the free buffer count for this channel
                         * (it is write to increment, force to rollover to zero)
                         */
                        GMACSW_REGS->CPDMA.CPDMA_RX_FREEBUFFER[channelNum] =
                            ((0x0000FFFFU - GMACSW_REGS->CPDMA.CPDMA_RX_FREEBUFFER[channelNum]) + 1U) & 0x0000FFFFU;
                    }

                    retVal = CPDMA_SUCCESS;
                }
            }
        }
    }
    else
    {
        retVal = CPDMA_INVALID_PARAM;
    }

    return retVal;
}

static uint32_t LOCAL_closeRxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel)
{
    CPDMA_State     *pCPDMAState    = (CPDMA_State *) hCpdma;
    CPDMA_Channel   *pChannel       = (CPDMA_Channel *) hChannel;
    uint32_t retVal                 = CPDMA_FAILURE;

    if ((NULL != pCPDMAState) && (NULL != pChannel))
    {
        if (1U == pChannel->isOpened)
        {
            uint32_t        packetCount = 0;
            CPDMA_Packet    *pCPDMAPacket;
            CPDMA_BuffDesc  *pCPDMABuffDesc;

            /* If channel still running, stop it */
            if (1U == pChannel->isStarted)
            {
                LOCAL_stopRxChannel(hCpdma, pChannel);
            }

            /* Move all packets out of the inUse or toHardware queues and into the fromHardware queue */
            pCPDMAPacket = LOCAL_packetDequeueWithDescUnlink(&pChannel->inUsePacketQueue);
            while (pCPDMAPacket != NULL)
            {
                CPDMA_packetEnqueue(&pChannel->fromHardwarePacketQueue, pCPDMAPacket);
                pCPDMAPacket = LOCAL_packetDequeueWithDescUnlink(&pChannel->inUsePacketQueue);
            }
            pCPDMAPacket = LOCAL_packetDequeueWithDescUnlink(&pChannel->toHardwarePacketQueue);
            while (pCPDMAPacket != NULL )
            {
                CPDMA_packetEnqueue(&pChannel->fromHardwarePacketQueue, pCPDMAPacket);
                pCPDMAPacket = LOCAL_packetDequeueWithDescUnlink(&pChannel->toHardwarePacketQueue);
            }

            /*
             * Call back to the translation layer to deconstruct and free up the packets in the
             * fromHardware queue.
             */
            (*pChannel->callbacks.pFxnCbCloseChannel)(pChannel->callbacks.hCallbackArg);

            /* Free all buffer descriptors in this channel's packets */
            for (packetCount = 0U; packetCount < (uint32_t)pChannel->packetCount; packetCount++)
            {
                pCPDMAPacket = &((pChannel->packetMem)[packetCount]);
                pCPDMABuffDesc = LOCAL_buffDescDequeue(&pCPDMAPacket->buffDescQueue);
                while (NULL != pCPDMABuffDesc)
                {
                    /* Clear the buffer descriptor and give back to the global CPDMA free queue */
                    CPDMA_buffDescInit(pCPDMABuffDesc);
                    LOCAL_buffDescEnqueue(&pCPDMAState->freeDescriptorQueue, pCPDMABuffDesc);
                    pCPDMABuffDesc = LOCAL_buffDescDequeue(&pCPDMAPacket->buffDescQueue);
                }
            }

            /* Mark the channel as NOT open */
            pChannel->isOpened = 0U;

            /* Adjust the Channel bit vector to indicate this channel is closed */
            pCPDMAState->rxChannelBitVector &= ~((uint32_t)0x1U << pChannel->channelNum);

            retVal = CPDMA_SUCCESS;
        }
        else
        {
            retVal = CPDMA_CHANNEL_NOT_OPEN;
        }
    }
    else
    {
        retVal = CPDMA_INVALID_PARAM;
    }

    return retVal;
}

static uint32_t LOCAL_startRxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel)
{
    CPDMA_Channel *pChannel         = (CPDMA_Channel *) hChannel;
    /* Double cast to avoid MISRA-C:2004 11.4 */
    CPDMA_RxChannel *pRxChannel     = (CPDMA_RxChannel *) ((void *)hChannel);
    uint32_t retVal                 = CPDMA_FAILURE;
    uint32_t key                    = GMACSW_AL_globalInterruptDisable();

    if ((NULL != pChannel) && (0U == pChannel->isStarted))
    {
        uint32_t        channelNum      = pChannel->channelNum;
        CPDMA_Packet    *firstPacket    = CPDMA_getFirstPacketOfPacketQueue(&pChannel->inUsePacketQueue);

        /* Enable the corresponding channel interrupt via the interrupt mask register */
        GMACSW_REGS->CPDMA.CPDMA_RX_INTMASK_SET = (uint32_t)1U << channelNum;

        /* Enable the channel Rx interrupt in GMACSW subsystem wrapper */
        GMACSW_REGS->WR.WR_C0_RX_EN |= (uint32_t)1U << channelNum;

        if (0U != pRxChannel->rxThreshCount)
        {
            /* Enable the corresponding channel interrupt via the interrupt mask register */
            GMACSW_REGS->CPDMA.CPDMA_RX_INTMASK_SET = (uint32_t)1U << (channelNum + CPDMA_MAX_RX_CHANNELS);

            /* Enable the channel Rx threshold interrupt in GMACSW subsystem wrapper */
            GMACSW_REGS->WR.WR_C0_RX_THRESH_EN |= (uint32_t)1U << channelNum;
        }

        if (NULL != firstPacket)
        {
            /* Set head descriptor pointer */
            GMACSW_REGS->STATERAM.RX_HDP[pChannel->channelNum] = (uint32_t) CPDMA_packetGetFirstDesc(firstPacket);
        }

        /* Mark channel as started */
        pChannel->isStarted = 1U;

        retVal = CPDMA_SUCCESS;
    }
    else
    {
        retVal = CPDMA_INVALID_PARAM;
    }

    GMACSW_AL_globalInterruptEnable(key);

    return retVal;
}

static uint32_t LOCAL_stopRxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel)
{
    CPDMA_Channel *pChannel = (CPDMA_Channel *) hChannel;
    uint32_t retVal         = CPDMA_FAILURE;
    uint32_t key            = GMACSW_AL_globalInterruptDisable();

    if ((NULL != pChannel) && (1U == pChannel->isStarted))
    {
        uint32_t channelNum   = pChannel->channelNum;

        /* command teardown  */
        GMACSW_REGS->CPDMA.CPDMA_RX_TEARDOWN = channelNum;

        /* wait for ack, examine CP for 0xFFFFFFFCU */
        {
            uint32_t cp = GMACSW_REGS->STATERAM.RX_CP[channelNum];
            while (cp != 0xFFFFFFFCU)
            {
                cp = GMACSW_REGS->STATERAM.RX_CP[channelNum];
            }
        }

        /* Disable Rx Interrupt on this channel */
        GMACSW_REGS->CPDMA.CPDMA_RX_INTMASK_CLEAR = (uint32_t)1U << channelNum;

        /* Also disable in the wrapper */
        GMACSW_REGS->WR.WR_C0_RX_EN &= ~((uint32_t)1U << channelNum);

        /* Mark channel as not started */
        pChannel->isStarted = 0U;

        retVal = CPDMA_SUCCESS;
    }
    else
    {
        retVal = CPDMA_INVALID_PARAM;
    }

    GMACSW_AL_globalInterruptEnable(key);

    return retVal;
}

static uint32_t LOCAL_openTxChannel(CPDMA_Handle hCpdma, const CPDMA_TxChannelConfig *pCPDMAChannelConfig, CPDMA_ChannelHandle *pChannelHandle)
{
    CPDMA_State *pCPDMAState = (CPDMA_State *) hCpdma;
    uint32_t retVal = CPDMA_FAILURE;

    if ((NULL != pCPDMAState) &&
        (NULL != pCPDMAChannelConfig) &&
        (NULL != pChannelHandle))
    {
        uint32_t channelNum = 0;

        /* Find first open channel */
        {
            uint32_t key = GMACSW_AL_globalInterruptDisable();

            while ( (LOCAL_isBitSet(channelNum, pCPDMAState->txChannelBitVector) == 1U) &&
                    (channelNum < CPDMA_MAX_TX_CHANNELS))
            {
                channelNum++;
            }

            if (CPDMA_MAX_TX_CHANNELS <= channelNum)
            {
                retVal =  CPDMA_NO_TX_CHANNELS_AVAILABLE;
            }
            else
            {
                pCPDMAState->txChannelBitVector |= ((uint32_t)0x1U << channelNum);
            }
            GMACSW_AL_globalInterruptEnable(key);
        }

        if (retVal != CPDMA_NO_TX_CHANNELS_AVAILABLE)
        {
            /* Double cast to avoid MISRA-C:2004 11.4 */
            CPDMA_Channel *pChannel = (CPDMA_Channel *) ((void *)&(pCPDMAState->txChannel[channelNum]));

            /* Check to make sure the callback functions are all defined */
            if ((NULL == pCPDMAChannelConfig->callbacks.pFxnCbCloseChannel) ||
                (NULL == pCPDMAChannelConfig->callbacks.pFxnCbUsedPacketNotify))
            {
                retVal = CPDMA_INVALID_PARAM;
            }
            else
            {
                uint32_t packetCount;

                /* Fill in channel fields */
                pChannel->channelDir            = CPDMA_DIRECTION_TX;
                pChannel->channelNum            = channelNum;
                pChannel->isOpened              = 1U;
                pChannel->packetCount           = pCPDMAChannelConfig->packetCount;
                pChannel->packetMem             = (CPDMA_Packet *)pCPDMAChannelConfig->packetMem;

                /* Save the callback configuration info to the channel structure*/
                memcpy(&pChannel->callbacks, &pCPDMAChannelConfig->callbacks, sizeof(CPDMA_Callbacks));

                /* Initialize the toHardware, inUse and fromHardware queue */
                CPDMA_packetQueueInit(&pChannel->toHardwarePacketQueue);
                CPDMA_packetQueueInit(&pChannel->inUsePacketQueue);
                CPDMA_packetQueueInit(&pChannel->fromHardwarePacketQueue);

                /* Try to allocate all the desired descriptors for this channel */
                for (packetCount = 0U; packetCount < (uint32_t)pChannel->packetCount; packetCount++)
                {
                    uint32_t descCount = 0;
                    CPDMA_Packet *pCPDMAPacket = &((pChannel->packetMem)[packetCount]);

                    /* Zero init the packet */
                    CPDMA_packetInit(pCPDMAPacket);

                    /* Zero init the packet buffer descriptor queue */
                    CPDMA_buffDescQueueInit(&pCPDMAPacket->buffDescQueue);

                    /* Allocate buffer descriptors from the CPDMA state object */
                    while (descCount < (uint32_t)pCPDMAChannelConfig->buffersPerPacketCount)
                    {
                        CPDMA_BuffDesc *pCPDMABuffDesc = LOCAL_buffDescDequeue(&pCPDMAState->freeDescriptorQueue);

                        if (pCPDMABuffDesc != NULL)
                        {
                            /* Clear the buffer descriptor out of the free queue */
                            CPDMA_buffDescInit(pCPDMABuffDesc);
                            LOCAL_buffDescEnqueue(&pCPDMAPacket->buffDescQueue, pCPDMABuffDesc);
                            descCount++;
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (pCPDMAChannelConfig->buffersPerPacketCount == descCount)
                    {
                        CPDMA_packetEnqueue(&pChannel->fromHardwarePacketQueue, pCPDMAPacket);
                    }
                    else
                    {
                        /* Mark the failure so we can clean up */
                        retVal = CPDMA_INSUFFICENT_BUFF_DESC;
                        break;
                    }
                }

                /* If the allocation appears to have failed, clean up as best we can */
                if (CPDMA_INSUFFICENT_BUFF_DESC == retVal)
                {
                    /* Free the ones were able to allocate before the failure back to the global pool */
                    for (packetCount = 0U; packetCount < (uint32_t)pChannel->packetCount; packetCount++)
                    {
                        uint32_t descCount = 0;
                        CPDMA_Packet *pCPDMAPacket = &((pChannel->packetMem)[packetCount]);

                        while (descCount < (uint32_t)pCPDMAChannelConfig->buffersPerPacketCount)
                        {
                            CPDMA_BuffDesc *pCPDMABuffDesc = LOCAL_buffDescDequeue(&pCPDMAPacket->buffDescQueue);

                            if (pCPDMABuffDesc != NULL)
                            {
                                /* Clear the buffer descriptor out of the free queue */
                                CPDMA_buffDescInit(pCPDMABuffDesc);
                                LOCAL_buffDescEnqueue(&pCPDMAState->freeDescriptorQueue, pCPDMABuffDesc);
                                descCount++;
                            }
                            else
                            {
                                break;
                            }
                        }

                        if (descCount != pCPDMAChannelConfig->buffersPerPacketCount)
                        {
                            break;
                        }
                        else
                        {
                            CPDMA_packetInit(pCPDMAPacket);
                        }
                    }
                }
                else
                {
                    *pChannelHandle = (CPDMA_ChannelHandle) pChannel;
                    retVal = CPDMA_SUCCESS;
                }
            }
        }
    }
    else
    {
        retVal = CPDMA_INVALID_PARAM;
    }

    return retVal;
}

static uint32_t LOCAL_closeTxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel)
{
    CPDMA_State     *pCPDMAState    = (CPDMA_State *) hCpdma;
    CPDMA_Channel   *pChannel       = (CPDMA_Channel *) hChannel;
    uint32_t retVal                 = CPDMA_FAILURE;

    if ((NULL != pCPDMAState) && (NULL != pChannel))
    {
        if (1U == pChannel->isOpened)
        {
            uint32_t        packetCount = 0;
            CPDMA_Packet    *pCPDMAPacket;
            CPDMA_BuffDesc  *pCPDMABuffDesc;

            /* If channel still running, stop it */
            if (1U == pChannel->isStarted)
            {
                LOCAL_stopTxChannel(hCpdma, pChannel);
            }

            /* Move all packets out of the inUse or toHardware queues and into the fromHardware queue */
            pCPDMAPacket = LOCAL_packetDequeueWithDescUnlink(&pChannel->inUsePacketQueue);
            while (pCPDMAPacket != NULL)
            {
                CPDMA_packetEnqueue(&pChannel->fromHardwarePacketQueue, pCPDMAPacket);
                pCPDMAPacket = LOCAL_packetDequeueWithDescUnlink(&pChannel->inUsePacketQueue);
            }
            pCPDMAPacket = LOCAL_packetDequeueWithDescUnlink(&pChannel->toHardwarePacketQueue);
            while (pCPDMAPacket != NULL )
            {
                CPDMA_packetEnqueue(&pChannel->fromHardwarePacketQueue, pCPDMAPacket);
                pCPDMAPacket = LOCAL_packetDequeueWithDescUnlink(&pChannel->toHardwarePacketQueue);
            }

            /*
             * Call back to the translation layer to deconstruct and free up the packets in the
             * fromHardware queue.
             */
            (*pChannel->callbacks.pFxnCbCloseChannel)(pChannel->callbacks.hCallbackArg);

            /* Free all buffer descriptors in this channel's packets */
            for (packetCount = 0U; packetCount < (uint32_t)pChannel->packetCount; packetCount++)
            {
                pCPDMAPacket = &((pChannel->packetMem)[packetCount]);
                pCPDMABuffDesc = LOCAL_buffDescDequeue(&pCPDMAPacket->buffDescQueue);
                while (NULL != pCPDMABuffDesc)
                {
                    /* Clear the buffer descriptor and give back to the global CPDMA free queue */
                    CPDMA_buffDescInit(pCPDMABuffDesc);
                    LOCAL_buffDescEnqueue(&pCPDMAState->freeDescriptorQueue, pCPDMABuffDesc);
                    pCPDMABuffDesc = LOCAL_buffDescDequeue(&pCPDMAPacket->buffDescQueue);
                }
            }

            /* Mark the channel as NOT open */
            pChannel->isOpened = 0U;

            /* Adjust the Channel bit vector to indicate this channel is closed */
            pCPDMAState->txChannelBitVector &= ~((uint32_t)0x1U << pChannel->channelNum);

            retVal = CPDMA_SUCCESS;
        }
        else
        {
            retVal = CPDMA_CHANNEL_NOT_OPEN;
        }
    }
    else
    {
        retVal = CPDMA_INVALID_PARAM;
    }

    return retVal;
}

static uint32_t LOCAL_startTxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel)
{
    CPDMA_Channel *pChannel  = (CPDMA_Channel *) hChannel;
    uint32_t retVal                 = CPDMA_FAILURE;
    uint32_t key                    = GMACSW_AL_globalInterruptDisable();

    if ((NULL != pChannel) && (0U == pChannel->isStarted))
    {
        uint32_t        channelNum      = pChannel->channelNum;
        CPDMA_Packet    *firstPacket    = CPDMA_getFirstPacketOfPacketQueue(&pChannel->inUsePacketQueue);

        /* Init head descriptor pointer for this channel to 0 */
        GMACSW_REGS->STATERAM.TX_HDP[channelNum] = (uint32_t) NULL;

        /* Enable the corresponding channel interrupt via the interrupt mask */
        GMACSW_REGS->CPDMA.CPDMA_TX_INTMASK_SET = (uint32_t)1U << channelNum;

        /* Enable the channel interrupt in GMACSW subsystem wrapper */
        GMACSW_REGS->WR.WR_C0_TX_EN |= (uint32_t)1U << channelNum;

        if (NULL != firstPacket)
        {
            GMACSW_REGS->STATERAM.TX_HDP[channelNum] = (uint32_t) CPDMA_packetGetFirstDesc(firstPacket);
        }

        /* Mark channel as started */
        pChannel->isStarted = 1U;

        retVal = CPDMA_SUCCESS;
    }
    else
    {
        retVal = CPDMA_INVALID_PARAM;
    }

    GMACSW_AL_globalInterruptEnable(key);

    return retVal;
}

static uint32_t LOCAL_stopTxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel)
{
    CPDMA_Channel *pChannel         = (CPDMA_Channel *) hChannel;
    uint32_t retVal                 = CPDMA_FAILURE;
    uint32_t key                    = GMACSW_AL_globalInterruptDisable();

    if ((NULL != pChannel) && (1U == pChannel->isStarted))
    {
        uint32_t channelNum = pChannel->channelNum;

        /* command teardown  */
        GMACSW_REGS->CPDMA.CPDMA_TX_TEARDOWN = channelNum;

        /* wait for ack ,examine CP for 0xFFFFFFFCU */
        {
            uint32_t cp = GMACSW_REGS->STATERAM.TX_CP[channelNum];
            while (cp != 0xFFFFFFFCU)
            {
                cp = GMACSW_REGS->STATERAM.TX_CP[channelNum];
            }
        }

        /* Disable Tx Interrupt on this channel */
        GMACSW_REGS->CPDMA.CPDMA_TX_INTMASK_CLEAR = (uint32_t)1U <<  channelNum;

        /* Also disable in the wrapper */
        GMACSW_REGS->WR.WR_C0_TX_EN &= ~((uint32_t)1U << channelNum);

        /* Mark channel as not started */
        pChannel->isStarted = 0U;

        retVal = CPDMA_SUCCESS;
    }
    else
    {
        retVal = CPDMA_INVALID_PARAM;
    }

    GMACSW_AL_globalInterruptEnable(key);

    return retVal;
}

static uint32_t LOCAL_retrievePacketQueueFromChannel(CPDMA_ChannelHandle hCPDMAChannel, CPDMA_PacketQueue *pFromChannelQueue)
{
    CPDMA_Channel *pCPDMAChannel    = (CPDMA_Channel *) hCPDMAChannel;
    uint32_t retVal                 = CPDMA_FAILURE;

    if ((NULL != pCPDMAChannel) && (NULL != pFromChannelQueue))
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();

        /* Append the the channel's fromHardwarePacketQueue onto the output queue */
        CPDMA_appendPacketQueue(pFromChannelQueue, &pCPDMAChannel->fromHardwarePacketQueue);

        /* Clear the fromHardware queue */
        CPDMA_packetQueueInit(&pCPDMAChannel->fromHardwarePacketQueue);

        GMACSW_AL_globalInterruptEnable(key);

        retVal = CPDMA_SUCCESS;
    }

    return retVal;
}

static uint32_t LOCAL_submitPacketQueueToChannel(CPDMA_ChannelHandle hCPDMAChannel, CPDMA_PacketQueue *pToChannelQueue)
{
    CPDMA_Channel *pCPDMAChannel    = (CPDMA_Channel *) hCPDMAChannel;
    uint32_t retVal                 = CPDMA_FAILURE;

    if ((NULL != pCPDMAChannel) && (NULL != pToChannelQueue))
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();

        /* Append the input queue onto the channel's toHardwarePacketQueue */
        CPDMA_appendPacketQueue(&pCPDMAChannel->toHardwarePacketQueue, pToChannelQueue);

        /* Clear the input queue */
        CPDMA_packetQueueInit(pToChannelQueue);

        /*
         * Give the packets to the hardware (kicks hardware into motion if
         * if no transfers are currently in progress).
         */
        if (pCPDMAChannel->toHardwarePacketQueue.count != 0U)
        {
            LOCAL_deliverPackets(pCPDMAChannel);
        }

        GMACSW_AL_globalInterruptEnable(key);

        retVal = CPDMA_SUCCESS;
    }

    return retVal;
}

/* LOCAL helper functions */
static CPDMA_Packet *LOCAL_packetDequeueWithDescUnlink(CPDMA_PacketQueue *pCPDMAPacketQueue)
{
    CPDMA_Packet *pCPDMAPacket = NULL;

    if (NULL != pCPDMAPacketQueue)
    {
        pCPDMAPacket = CPDMA_packetDequeue(pCPDMAPacketQueue);
        if (NULL != pCPDMAPacket)
        {
            CPDMA_BuffDesc *pCPDMABuffDesc;

            pCPDMABuffDesc = CPDMA_packetGetLastDesc(pCPDMAPacket);
            pCPDMABuffDesc->pNextBufferDescriptor = NULL;
        }
    }

    return pCPDMAPacket;
}

/* Add a buffer descriptor to the tail of the descriptor queue */
static void LOCAL_buffDescEnqueue(CPDMA_BuffDescQueue *pCPDMABuffDescQueue, CPDMA_BuffDesc *pCPDMABuffDesc)
{
    if ( (NULL != pCPDMABuffDescQueue) && (NULL != pCPDMABuffDesc))
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();

        pCPDMABuffDesc->pNextBufferDescriptor = NULL;

        if (NULL == pCPDMABuffDescQueue->pHead)
        {
            /* Queue is empty, make head point to new descriptor*/
            pCPDMABuffDescQueue->pHead = pCPDMABuffDesc;
        }
        else
        {
            /* Queue is not empty, make previous tail point to new descriptor */
            pCPDMABuffDescQueue->pTail->pNextBufferDescriptor = pCPDMABuffDesc;
        }

        /* Make tail of queue point to new */
        pCPDMABuffDescQueue->pTail = pCPDMABuffDesc;
        pCPDMABuffDescQueue->count++;

        GMACSW_AL_globalInterruptEnable(key);
    }
}

/* Remove a buffer descriptor from the head of the descriptor queue */
static CPDMA_BuffDesc *LOCAL_buffDescDequeue(CPDMA_BuffDescQueue *pCPDMABuffDescQueue)
{
    CPDMA_BuffDesc *pCPDMABuffDesc = NULL;

    if (NULL != pCPDMABuffDescQueue)
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();

        pCPDMABuffDesc = pCPDMABuffDescQueue->pHead;

        if (NULL != pCPDMABuffDesc)
        {
            pCPDMABuffDescQueue->count--;
            /*
             * Use the count as an indicator since the queues associated with each
             * packet can be linked together
             */

            if (pCPDMABuffDescQueue->count)
            {
                pCPDMABuffDescQueue->pHead = pCPDMABuffDesc->pNextBufferDescriptor;
            }
            else
            {
                pCPDMABuffDescQueue->pHead = NULL;
            }
            pCPDMABuffDesc->pNextBufferDescriptor = NULL;
            /* Check if queue is now empty */
            if (NULL == pCPDMABuffDescQueue->pHead)
            {
                pCPDMABuffDescQueue->pTail = NULL;
            }
        }

        GMACSW_AL_globalInterruptEnable(key);
    }

    return (pCPDMABuffDesc);
}

static void LOCAL_deliverPackets(CPDMA_Channel *pChannel)
{
    CPDMA_PacketQueue *pToHardwareQueue = &pChannel->toHardwarePacketQueue;
    CPDMA_PacketQueue *pInUsePacketQueue = &pChannel->inUsePacketQueue;

    if (NULL == pInUsePacketQueue->pHead)
    {
        /* InUse queue is empty - Initialize it with the free packet queue */
        CPDMA_packetQueueCopy(pInUsePacketQueue,pToHardwareQueue);

        /* Since the inUse queue was empty the CPDMA hardware needs to be (re)started */
        if (1U == pChannel->isStarted)
        {
            CPDMA_BuffDesc *pFirstBuffDesc = pInUsePacketQueue->pHead->buffDescQueue.pHead;

            if (CPDMA_DIRECTION_RX == pChannel->channelDir)
            {
                GMACSW_REGS->STATERAM.RX_HDP[pChannel->channelNum] = (uint32_t) pFirstBuffDesc;
            }
            else
            {
                GMACSW_REGS->STATERAM.TX_HDP[pChannel->channelNum] = (uint32_t) pFirstBuffDesc;
            }
        }
    }
    else
    {
        /* InUse queue is not empty - Add free queue contents onto end of InUse queue */
        pInUsePacketQueue->pTail->pNextPacket = pToHardwareQueue->pHead;

        pInUsePacketQueue->pTail->buffDescQueue.pTail->pNextBufferDescriptor =
            pToHardwareQueue->pHead->buffDescQueue.pHead;
        pInUsePacketQueue->pTail = pToHardwareQueue->pTail;
        pInUsePacketQueue->count += pToHardwareQueue->count;
    }

    if (CPDMA_DIRECTION_RX == pChannel->channelDir)
    {
        /* Double cast to avoid MISRA-C:2004 11.4 */
        CPDMA_RxChannel *pRxChannel = (CPDMA_RxChannel *) ((void *)pChannel);
        if (0U != pRxChannel->rxThreshCount)
        {
            /* FREEBUFFER is write to increment */
            GMACSW_REGS->CPDMA.CPDMA_RX_FREEBUFFER[pChannel->channelNum] = pToHardwareQueue->count;

            /* Reset the PENDTHRESH since it may have been cleared in the RX_THRESH ISR */
            GMACSW_REGS->CPDMA.CPDMA_RX_PENDTHRESH[pChannel->channelNum] =
                CSL_FMK(GMACSW_CPDMA_RX_PENDTHRESH_RX_PENDTHRESH,pRxChannel->rxThreshCount);
        }
    }

    /* Clear the ToHardware queue since we took everything out and added it to the InUse queue */
    CPDMA_packetQueueInit(pToHardwareQueue);
}

static uint32_t LOCAL_isBitSet(uint32_t bitNum, uint32_t bitVector)
{
    return (((((uint32_t)1U << bitNum) & bitVector) == 0) ? 0U : 1U);
}


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

