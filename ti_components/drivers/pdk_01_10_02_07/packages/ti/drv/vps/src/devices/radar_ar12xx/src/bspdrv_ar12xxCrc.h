/*
 *   Copyright (c) Texas Instruments Incorporated 2016-2017
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
 */

/**
 *  \file bspdrv_ar12xxCrc.c
 *
 *  \brief This file defines the functions related to CRC16-CCITT algorithms.
 *
 */

#ifndef BSPDRV_AR12_CRC_H
#define BSPDRV_AR12_CRC_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */



/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
 
/*! \brief
 * Standard MACROs
 */
#define BSPDRV_AR12XX_CRC_M_CRC_TABLE_SIZE       (256U)

/**
 *  \anchor CCITT-CRC16
 *  \name CCITT-CRC16 details
 *  @{
 *  The CCITT-CRC16 uses: x16 + x12 + x5 + 1 polynomial i.e 0x11021,
 *  the 17th bit of polynomial is comes in the next  half word boundary and
 *  it is simulated by testing the MSB before shifting the data, which affords
 *  us the luxury  of specify the polynomial as a 16 bit value 0x1021 for
 *  perform 16 bit CRC. In each data use the top 16th bit to  polynomial divide
 */
#define BSPDRV_AR12XX_CRC_M_CRC16CCITT_POLY (0x1021U)
#define BSPDRV_AR12XX_CRC_M_CRC_WIDTH       (16U)
#define BSPDRV_AR12XX_CRC_M_CRC_TOP_BIT     \
    (0x1U << (BSPDRV_AR12XX_CRC_M_CRC_WIDTH - 1))
/* @} */

/*! \brief
 * Initial remainder for computing CRC must be 0xFFFFF which avoids the leading zero problem.
 */
#define BSPDRV_AR12XX_CRC_INITIAL_REMAINDER                 (0xFFFFU)

/**
 *  \anchor CRC-ValueNumbers
 *  \name CRC-ValueNumbers
 *  @{
 *  Numbers are represented in their macro equivalent.
 */
#define BSPDRV_AR12XX_CRC_M_ZERO                 (0U)
#define BSPDRV_AR12XX_CRC_M_ONE                  (1U)
#define BSPDRV_AR12XX_CRC_M_TWO                  (2U)
#define BSPDRV_AR12XX_CRC_M_THREE                (3U)
#define BSPDRV_AR12XX_CRC_M_FOUR                 (4U)
#define BSPDRV_AR12XX_CRC_M_FIVE                 (5U)
#define BSPDRV_AR12XX_CRC_M_SIX                  (6U)
#define BSPDRV_AR12XX_CRC_M_SEVEN                (7U)
#define BSPDRV_AR12XX_CRC_M_EIGHT                (8U)
#define BSPDRV_AR12XX_CRC_M_NINE                 (9U)
#define BSPDRV_AR12XX_CRC_M_TEN                  (10U)
#define BSPDRV_AR12XX_CRC_M_ELEVEN               (11U)
#define BSPDRV_AR12XX_CRC_M_TWELVE               (12U)
#define BSPDRV_AR12XX_CRC_M_THIRTEEN             (13U)
#define BSPDRV_AR12XX_CRC_M_FOURTEEN             (14U)
#define BSPDRV_AR12XX_CRC_M_FIVETEEN             (15U)
#define BSPDRV_AR12XX_CRC_M_SIXTEEN              (16U)
#define BSPDRV_AR12XX_CRC_M_SEVENTEEN            (17U)
#define BSPDRV_AR12XX_CRC_M_EIGHTEEN             (18U)
#define BSPDRV_AR12XX_CRC_M_NINETEEN             (19U)
#define BSPDRV_AR12XX_CRC_M_TWENTY               (20U)
#define BSPDRV_AR12XX_CRC_M_TWENTY_ONE           (21U)
#define BSPDRV_AR12XX_CRC_M_TWENTY_TWO           (22U)
#define BSPDRV_AR12XX_CRC_M_TWENTY_THREE         (23U)
#define BSPDRV_AR12XX_CRC_M_TWENTY_FOUR          (24U)
#define BSPDRV_AR12XX_CRC_M_TWENTY_FIVE          (25U)
#define BSPDRV_AR12XX_CRC_M_TWENTY_SIX           (26U)
#define BSPDRV_AR12XX_CRC_M_TWENTY_SEVEN         (27U)
#define BSPDRV_AR12XX_CRC_M_TWENTY_EIGHT         (28U)
#define BSPDRV_AR12XX_CRC_M_TWENTY_NINE          (29U)
#define BSPDRV_AR12XX_CRC_M_THIRTY               (30U)
#define BSPDRV_AR12XX_CRC_M_THIRTY_ONE           (31U)
#define BSPDRV_AR12XX_CRC_M_THIRTY_TWO           (32U)
/* @} */

/**
 *  \anchor CRC-WordMasks
 *  \name CRC-WordMasks
 *  @{
 *  Masks for Word, Half word and Byte.
 */
#define BSPDRV_AR12XX_CRC_M_MAX_WORD_VALUE        (0xFFFFFFFFU)
#define BSPDRV_AR12XX_CRC_M_MAX_HWORD_VALUE       (0xFFFFU)
#define BSPDRV_AR12XX_CRC_M_MAX_BYTE_VALUE        (0xFFU)
/* @} */

/**
 *  \anchor CRC-MemoryWriteMacros
 *  \name CRC-MemoryWriteMacros
 *  @{
 *  Memory write functions for writing 8, 16, 32 and 64 bits.
 */
#define BSPDRV_AR12XX_CRC_M_REG_WRITE8(w_addr, c_data)       \
    (*((uint8_t *)(w_addr))  = (uint8_t)(c_data))
#define BSPDRV_AR12XX_CRC_M_REG_WRITE16(w_addr, h_data)      \
    (*((uint16_t *)(w_addr)) = (uint16_t)(h_data))
#define BSPDRV_AR12XX_CRC_M_REG_WRITE32(w_addr, w_data)      \
    (*((uint32_t *)(w_addr)) = (uint32_t)(w_data))
#define BSPDRV_AR12XX_CRC_M_REG_WRITE64(w_addr, l_data)      \
    (*((uint64_t *)(w_addr)) = (uint64_t)(l_data))
/* @} */

/**
 *  \anchor CRC-MemoryReadMacros
 *  \name CRC-MemoryReadMacros
 *  @{
 *  Memory Read functions for writing 8, 16, 32 and 64 bits.
 */
#define BSPDRV_AR12XX_CRC_M_REG_READ8(w_addr)                \
    ((uint8_t)(*((uint8_t *)(w_addr))))
#define BSPDRV_AR12XX_CRC_M_REG_READ16(w_addr)               \
    ((uint16_t)(*((uint16_t *)(w_addr))))
#define BSPDRV_AR12XX_CRC_M_REG_READ32(w_addr)               \
    ((uint32_t)(*((uint32_t *)(w_addr))))
#define BSPDRV_AR12XX_CRC_M_REG_READ64(w_addr)               \
    ((uint64_t)(*((uint64_t *)(w_addr))))
/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */


/**
 * \brief
 *<b>Function Name</b> : Bsp_ar12xxComputeCrc
 *
 *<b>Description</b>   : This function computes CRC16-CCITT computation.
 *   The mailbox data is is read 64bits (8 bytes) at one shot using LDMA
 *   instruction to reduce the access time, each bytes of the message is passed
 *   to LUT based CRC algorithm.
 *
 * \param wMbDataBaseAdd[in]  - The message data source base address
 * \param hNBytes       [in]  - Num of bytes to read for CRC computation
 * \param crcLen        [in]  - Length/Type of CRC
 * \param outCrc        [out] - Pointer to CRC output buffer
 *
 * \return          0:Success, negative value:Failure
 *
 *<b>Assumptions</b>   : The Message in Mailbox is in big-endian format and
 *                       BSS R4 runs in little-endian mode.
 *
 */
int32_t Bsp_ar12xxComputeCrc(uint8_t* wMbDataBaseAdd,
                             uint32_t hNBytes,
                             uint8_t crcLen, 
                             uint8_t* outCrc);

#endif
/*
 * END OF BSPDRV_AR12_CRC_H
 */

