/*
 *   Copyright (c) Texas Instruments Incorporated 2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_CRC CRC
 *
 *  @{
 */
/**
 *  \file     crc.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of CRC.
 *            This also contains some related macros.
 */

/**
 *         CRC programming sequence:
 *         1. CRCChannelReset()
 *         2. CRCInitialize()
 *         2. CRCConfigure()
 *         3. CRCEnableIntr() - if needed
 *         6. Transfer data to PSA signature for generation of signature value
 *             - DMA is utilized in Semi-CPU mode
 *             - CPU need to pump data into PSA register in Full CPU mode.
 *         7. CRCGetPSASectorSig()
 *             - After complete transfer read CRC signature.
 */
/**
 *         CRC signature generated depends on amount of data copied into
 *         PSA register at a time/in single write. Though data pattern can be
 *         8, 16, 32, or 64 bit, data copied into PSA register is always 64 bit
 *         wide. If data pattern is less than 64 bit, then it is padded with
 *         zeros to make it 64 bit write.
 */
#ifndef CRC_H_
#define CRC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "ti/csl/cslr_crc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/**
 * \brief  Macro defines mask for all the interrupts for a channel.
 */
#define CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL   \
    (uint32_t) ((uint32_t)CRC_INTS_CH1_CCITENS_MASK |  \
                (uint32_t)CRC_INTR_CH1_FAILENR_MASK |  \
                (uint32_t)CRC_INTR_CH1_OVERENR_MASK |  \
                (uint32_t)CRC_INTR_CH1_UNDERENR_MASK | \
                (uint32_t)CRC_INTR_CH1_TIME_OUT_ENR_MASK)

/**
 * \brief  Macro defines maximum value of CRC Pattern Count.
 */
#define CRC_PATTERN_COUNT_MAX          (0x000FFFFFU)

/**
 * \brief  Macro defines maximum value of CRC Sector Count.
 */
#define CRC_SECTOR_COUNT_MAX           (0x0000FFFFU)

/**
 * \brief  Macro defines maximum value of CRC Block Complete Timeout Counter
 *         Preload.
 */
#define CRC_BCTOPLD_MAX                (0x00FFFFFFU)

/**
 * \brief  Macro defines maximum value of CRC Watchdog Timeout Counter Preload.
 */
#define CRC_WDTOPLD_MAX                (0x00FFFFFFU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum to select the CRC Operation Mode.
 *
 *         CRC can either operate in Semi-CPU or Full-CPU.
 *         Refer to CRC Modes Overview.
 */
typedef enum crcOperationMode
{
    CRC_OPERATION_MODE_SEMICPU = CRC_CTRL2_CH1_MODE_SEMICPU,
    /**< Configure CRC operation mode to Semi-CPU */
    CRC_OPERATION_MODE_FULLCPU = CRC_CTRL2_CH1_MODE_FULLCPU
    /**< Configure CRC operation mode to Full-CPU */
}crcOperationMode_t;

/**
 * \brief  Enum to select the CRC Channel.
 */
typedef enum crcChannel
{
    CRC_CHANNEL_1 = 0x1U,
    /**< Select channel 1 for operation */
    CRC_CHANNEL_2 = 0x2U,
    /**< Select channel 2 for operation */
    CRC_CHANNEL_3 = 0x3U,
    /**< Select channel 3 for operation */
    CRC_CHANNEL_4 = 0x4U
    /**< Select channel 4 for operation */
}crcChannel_t;

/**
 * \brief  Enum to define the offset for the highest priority interrupt
 *
 *         These interrupt offset returned #CRCGetHighestPriorityIntrStatus
 *         function
 */
typedef enum crcIntrPriority
{
    CRC_INTR_PRIORITY_CH1_COMPRESSION_DONE = 0x9U,
    /**< Offset return for channel 1 compression done interrupt */
    CRC_INTR_PRIORITY_CH2_COMPRESSION_DONE = 0xaU,
    /**< Offset return for channel 2 compression done interrupt */
    CRC_INTR_PRIORITY_CH3_COMPRESSION_DONE = 0xbU,
    /**< Offset return for channel 3 compression done interrupt */
    CRC_INTR_PRIORITY_CH4_COMPRESSION_DONE = 0xcU,
    /**< Offset return for channel 4 compression done interrupt */
    CRC_INTR_PRIORITY_CH1_OVERRUN = 0x11U,
    /**< Offset return for channel 1 overrun interrupt */
    CRC_INTR_PRIORITY_CH2_OVERRUN = 0x12U,
    /**< Offset return for channel 2 overrun interrupt */
    CRC_INTR_PRIORITY_CH3_OVERRUN = 0x13U,
    /**< Offset return for channel 3 overrun interrupt */
    CRC_INTR_PRIORITY_CH4_OVERRUN = 0x14U,
    /**< Offset return for channel 4 overrun interrupt */
    CRC_INTR_PRIORITY_CH1_TIMEOUT = 0x21U,
    /**< Offset return for channel 1 timeout interrupt */
    CRC_INTR_PRIORITY_CH2_TIMEOUT = 0x22U,
    /**< Offset return for channel 2 timeout interrupt */
    CRC_INTR_PRIORITY_CH3_TIMEOUT = 0x23U,
    /**< Offset return for channel 3 timeout interrupt */
    CRC_INTR_PRIORITY_CH4_TIMEOUT = 0x24U
    /**< Offset return for channel 4 timeout interrupt */
}crcIntrPriority_t;

/**
 * \brief  Structure for accessing CRC register data which are 64 bit wide.
 */
typedef struct crcSignature
{
    uint32_t regL;
    /**< Lower 32 bits of the 64 bit data of CRC Signature register */
    uint32_t regH;
    /**< Upper 32 bits of the 64 bit data of CRC Signature register */
}crcSignature_t;

/**
 * \brief  Structure for accessing CRC registers address which are 64 bit wide.
 */
typedef struct crcSigantureRegAddr
{
    uint32_t regL;
    /**< Lower 32 bits of the 64 bit CRC Signature register address */
    uint32_t regH;
    /**< Upper 32 bits of the 64 bit CRC Signature register address */
}crcSignatureRegAddr_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Initialize CRC channel and will configure watchdog and
 *          block preload value for given channel.
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 *
 * \param   channel         Channel number to be configured.
 *                          Values given by enum #crcChannel_t.
 * \param   crcWatchdogPreload
 *                          It is used to check if DMA does supply a block of
 *                          data responding to a request in a given time frame.
 * \param   crcBlockPreload
 *                          It is used to check if DMA does supply a block of
 *                          data responding to a request in a given time frame.
 *
 * \return  status          CRC Initialization status.
 */
int32_t CRCInitialize(uint32_t baseAddr,
                      uint32_t channel,
                      uint32_t crcWatchdogPreload,
                      uint32_t crcBlockPreload);

/**
 * \brief   This API will configure CRC mode, pattern and sector count for
 *          given channel.
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 * \param   channel         Channel number to be initialized.
 *                          Values given by enum #crcChannel_t.
 * \param   crcPatternCount It is used to check if DMA does supply a block of
 *                          data responding to a request in a given time frame.
 * \param   crcSectorCount  It is used to check if DMA does supply a block of
 *                          data responding to a request in a given time frame.
 * \param   crcMode         CRC operational mode.
 *                          Refer enum #crcOperationMode_t.
 *
 * \return  status          CRC configuration status
 */
int32_t CRCConfigure(uint32_t baseAddr,
                     uint32_t channel,
                     uint32_t crcPatternCount,
                     uint32_t crcSectorCount,
                     uint32_t crcMode);

/**
 * \brief   This API is used to reset the channel
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 * \param   channel         Channel number for which reset is to be done.
 *                          Values given by enum #crcChannel_t.
 *
 * \return  None
 */
void CRCChannelReset(uint32_t baseAddr,
                     uint32_t channel);

/**
 * \brief   This API is used to get the PSA register address for given Channel.
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 * \param   channel         Channel number whose PSA register address is
 *                          needed.
 *                          Values given by enum #crcChannel_t.
 * \param   crcRegAddr      PSA register Address for given Channel.
 *                          Refer structure #crcSignatureRegAddr_t.
 *
 * \return  None
 */
void CRCGetPSASigRegAddr(uint32_t               baseAddr,
                         uint32_t               channel,
                         crcSignatureRegAddr_t *crcRegAddr);

/**
 * \brief   This API is used to get the PSA Value.
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 * \param   channel         Channel number whose PSA register data is
 *                          needed.
 *                          Values given by enum #crcChannel_t.
 * \param   crcPSASign      CRC value for sector.
 *                          Refer struct #crcSignature_t.
 *
 * \return  None
 */
void CRCGetPSASig(uint32_t        baseAddr,
                  uint32_t        channel,
                  crcSignature_t *crcPSASign);

/**
 * \brief   This API is used to set the PSA Seed Value without compression.
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 * \param   channel         Channel number whose PSA Seed Value needs to be set.
 *                          Values given by enum #crcChannel_t.
 * \param   crcPSASeedSign  CRC value for sector.
 *                          Refer struct #crcSignature_t for details.
 *
 * \return  None
 */
void CRCSetPSASeedSig(uint32_t              baseAddr,
                      uint32_t              channel,
                      const crcSignature_t *crcPSASeedSign);

/**
 * \brief   This API is used to get Sector Signature Value/
 *          CRC value for given data.
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 * \param   channel         Channel number which was configured for CRC
 *                          calculation.
 *                          Values given by enum #crcChannel_t.
 * \param   crcSectorSign   Refer struct #crcSignature_t.
 *
 * \return  None
 *
 * \note    This API should be called after complete transfer of sector/data to
 *          PSA register.
 */
void CRCGetPSASectorSig(uint32_t        baseAddr,
                        uint32_t        channel,
                        crcSignature_t *crcSectorSign);

/**
 * \brief   This API is used to get the pending interrupt with highest priority.
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 *
 * \return  Interrupt vector address
 *                          Highest priority pending interrupt vector address
 *                          defined in enum #crcIntrPriority_t
 */
uint32_t CRCGetHighestPriorityIntrStatus(uint32_t baseAddr);

/**
 * \brief   This API is used to get the pending interrupts.
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 * \param   channel         Channel number for which pending interrupt is
 *                          to get.
 *                          Values given by enum #crcChannel_t.
 *
 * \return  status          Pending interrupt status/occurred.
 */
uint32_t CRCGetIntrStatus(uint32_t baseAddr,
                          uint32_t channel);

/**
 * \brief   This API is used to enable interrupts.
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 * \param   channel         Channel number for which interrupt is to enable.
 *                          Values given by enum #crcChannel_t.
 * \param   intrMask        Interrupt to enable.
 *
 * \return  None
 */
void CRCEnableIntr(uint32_t baseAddr,
                   uint32_t channel,
                   uint32_t intrMask);

/**
 * \brief   This API is used to disable interrupts.
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 * \param   channel         Channel number for which interrupt is to disable.
 *                          Values given by enum #crcChannel_t.
 * \param   intrMask        Interrupt to disable.
 *
 * \return  None
 */
void CRCDisableIntr(uint32_t baseAddr,
                    uint32_t channel,
                    uint32_t intrMask);

/**
 * \brief   This API is used to clear interrupts.
 *
 * \param   baseAddr        Base Address of the CRC Registers.
 * \param   channel         Channel number for which interrupt is to clear.
 *                          Values given by enum #crcChannel_t.
 * \param   intrMask        Interrupt to clear status.
 *
 * \return  None
 */
void CRCClearIntr(uint32_t baseAddr,
                  uint32_t channel,
                  uint32_t intrMask);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
 /** @} */
