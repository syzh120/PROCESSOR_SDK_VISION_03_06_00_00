/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
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
 *  \file   chip_config.h
 *
 *  \brief  Chip Configuration Hardware Abstraction Layer
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

#ifndef CHIP_CONFIG_H
#define CHIP_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

extern uint32_t  CHIPCONFIGGetNumMPUs(void);

extern uint32_t  CHIPCONFIGGetNumIPUs(void);

extern uint32_t  CHIPCONFIGGetNumDSPs(void);

extern uint32_t  CHIPCONFIGGetNumEVEs(void);

extern uint32_t  CHIPCONFIGGetNumPRUSSs(void);

typedef enum
{
    CPU_MPUSS,
    CPU_IPU1,
    CPU_IPU2,
    CPU_DSP1,
#if defined (SOC_TDA2EX)
    /* Not applicable */
#else
    CPU_DSP2,
    CPU_EVE1,
    CPU_EVE2,
    CPU_EVE3,
    CPU_EVE4,
#endif
    CPU_PRUSS1
} cpu_id_t;

typedef enum
{
    EDMA,
#if defined (SOC_TDA2EX)
    EDMA_DSP1
#else
    EDMA_DSP1,
    EDMA_DSP2
#endif
} dma_id_t;

#ifdef __cplusplus
}
#endif

#endif
