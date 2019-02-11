/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2016
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

#ifndef LLD_HSI2C_EDMA_H_
#define LLD_HSI2C_EDMA_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *                             INCLUDE FILES
 *******************************************************************************/
#include <stdint.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>

/******************************************************************************
 *                        LOCAL MACRO DEFINITIONS
 ******************************************************************************/
#if defined (TI814X_BUILD)
#define LLD_I2C_EDMA_CHA_I2CTXEVT0    ((uint32_t) 58U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT0    ((uint32_t) 59U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT1    ((uint32_t) 60U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT1    ((uint32_t) 61U)

/*Cross Bar mapped*/
#define LLD_I2C_EDMA_CHA_I2CTXEVT2    ((uint32_t) 66U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT2    ((uint32_t) 67U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT3    ((uint32_t) 68U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT3    ((uint32_t) 69U)

#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#define LLD_I2C_EDMA_CHA_I2CTXEVT0    ((uint32_t) 26U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT0    ((uint32_t) 27U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT1    ((uint32_t) 28U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT1    ((uint32_t) 29U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT2    ((uint32_t) 24U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT2    ((uint32_t) 25U)

/*Cross bar mapped need to take care depending on the cross bar mapping */
#define LLD_I2C_EDMA_CHA_I2CTXEVT3    ((uint32_t) 124U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT3    ((uint32_t) 125U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT4    ((uint32_t) 152U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT4    ((uint32_t) 153U)
#if defined (SOC_TDA2EX)
#define LLD_I2C_EDMA_CHA_I2CTXEVT5    ((uint32_t) 203U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT5    ((uint32_t) 204U)
#endif
#endif

#if defined (SOC_TDA3XX)
#define LLD_I2C_EDMA_CHA_I2CTXEVT0    ((uint32_t) 26U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT0    ((uint32_t) 27U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT1    ((uint32_t) 28U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT1    ((uint32_t) 29U)
#endif

typedef struct
{
    /*void *                     hEdma;
     * int32_t                   edma3EventQueue;*/
    uint32_t baseAddr;
    uint32_t channelType;
    uint32_t eventQueue;
    uint32_t intNum;
}LLD_hsi2cEdmaParam;

LLD_hsi2cEdmaStatus EDMA_requestChannel(hsI2cHandle          handle,
                                        uint32_t            *i2cEventNo,
                                        lldHsi2cEdmaCallback i2cCallback,
                                        void                *edmaParam);
LLD_hsi2cEdmaStatus EDMA_freeChannel(uint32_t i2cEventNo, void *edmaParam);
LLD_hsi2cEdmaStatus EDMA_disableLogicalChannel(uint32_t tcc, void *edmaParam);
LLD_hsi2cEdmaStatus EDMA_clearErrorBits(uint32_t tcc, void *edmaParam);
LLD_hsi2cEdmaStatus EDMA_setPaRAM(const void *srcPtr, const void *dstPtr,
                                  uint32_t rdWrflag,
                                  uint32_t chan, uint32_t bufLen,
                                  void *edmaParam,
                                  uint8_t fifoThreshold);
LLD_hsi2cEdmaStatus EDMA_enableTransfer(uint32_t chan, void *edmaParam);
void EDMA_callbackFn(void *arg);
#ifdef __cplusplus
}
#endif

#endif
