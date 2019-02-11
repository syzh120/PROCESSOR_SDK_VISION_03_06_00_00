/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
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
 *  \file   dma_xbar.h
 *
 *  \brief  This module contains the DMA XBAR hardware abstraction layer
 *
 *   This file contains the DMA XBAR HAL API prototypes and macro definitions.
 */

#ifndef DMA_XBAR_H
#define DMA_XBAR_H

#include "dma_xbar_event_ids.h"
#include "chip_config.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/**
 * \enum   dma_xbar_ret_type_t
 * \brief  Enumeration that specifies all possible return values from the DMA
 *         XBAR
 *
 */
typedef enum
{
    dma_xbar_success,
    invalid_dma_id,
    invalid_dma_xbar_inst_id,
    invalid_event_source_id
} dma_xbar_ret_type_t;

extern dma_xbar_ret_type_t DMAXBARValidateArgs(dma_id_t   dma,
                                               uint32_t   xbarInst,
                                               xbar_evt_t eventSource);

extern uint32_t DMAXBARGetOffset(dma_id_t dma, uint32_t xbarInst);

extern dma_xbar_ret_type_t DMAXBARConnect(uint32_t baseAddr, dma_id_t dma,
                                          uint32_t xbarInst,
                                          xbar_evt_t eventSource);

extern dma_xbar_ret_type_t DMAXBARDisconnect(uint32_t baseAddr,
                                             dma_id_t dma,
                                             uint32_t xbarInst);

extern dma_xbar_ret_type_t DMAXBARIsConnected(uint32_t   baseAddr,
                                              dma_id_t   dma,
                                              uint32_t   xbarInst,
                                              xbar_evt_t eventSource,
                                              uint8_t   *status);

extern dma_xbar_ret_type_t DMAXBARGetConnection(uint32_t    baseAddr,
                                                dma_id_t    dma,
                                                uint32_t    xbarInst,
                                                xbar_evt_t *eventSource);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
