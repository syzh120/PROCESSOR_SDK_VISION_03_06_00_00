/*
* common.c
*
* Demo sample application for the EDMA3 Driver for BIOS 6.
*
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
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

#include "sample.h"


/* Flag variable to check transfer completion on channel 1 */
volatile short irqRaised1 = 0;
/* Flag variable to check transfer completion on channel 2 */
volatile short irqRaised2 = 0;

/* Application Sem Handle */
void *AppSemHandle1 = NULL;
/* Application Sem Handle */
void *AppSemHandle2 = NULL;


/* Cache line aligned source buffer 1. */
#ifndef GCC_BUILD
#ifdef EDMA3_ENABLE_DCACHE
/**
* The DATA_ALIGN pragma aligns the symbol to an alignment boundary. The
* alignment boundary is the maximum of the symbol’s default alignment value
* or the value of the constant in bytes. The constant must be a power of 2.
* The syntax of the pragma in C is:
* #pragma DATA_ALIGN (symbol, constant);
*/
#pragma DATA_ALIGN(_srcBuff1, EDMA3_CACHE_LINE_SIZE_IN_BYTES);
#endif  /* #ifdef EDMA3_ENABLE_DCACHE */
#pragma DATA_SECTION(_srcBuff1, ".my_sect_ddr");
signed char   _srcBuff1[MAX_BUFFER_SIZE];
#else
#ifdef EDMA3_ENABLE_DCACHE
signed char   __attribute__((section(".my_sect_ddr"))) _srcBuff1[MAX_BUFFER_SIZE] __attribute__ ((aligned (EDMA3_CACHE_LINE_SIZE_IN_BYTES)));
#else
signed char   __attribute__((section(".my_sect_ddr"))) _srcBuff1[MAX_BUFFER_SIZE];
#endif
#endif

/* Cache line aligned destination buffer 1. */
#ifndef GCC_BUILD
#ifdef EDMA3_ENABLE_DCACHE
/**
* The DATA_ALIGN pragma aligns the symbol to an alignment boundary. The
* alignment boundary is the maximum of the symbol’s default alignment value
* or the value of the constant in bytes. The constant must be a power of 2.
* The syntax of the pragma in C is:
* #pragma DATA_ALIGN (symbol, constant);
*/
#pragma DATA_ALIGN(_dstBuff1, EDMA3_CACHE_LINE_SIZE_IN_BYTES);
#endif  /* #ifdef EDMA3_ENABLE_DCACHE */
#pragma DATA_SECTION(_dstBuff1, ".my_sect_ddr");
signed char   _dstBuff1[MAX_BUFFER_SIZE];
#else
#ifdef EDMA3_ENABLE_DCACHE
signed char   __attribute__((section(".my_sect_ddr"))) _dstBuff1[MAX_BUFFER_SIZE] __attribute__ ((aligned (EDMA3_CACHE_LINE_SIZE_IN_BYTES)));
#else
signed char   __attribute__((section(".my_sect_ddr"))) _dstBuff1[MAX_BUFFER_SIZE];
#endif
#endif

signed char *srcBuff1;
signed char *dstBuff1;



/* Cache line aligned source buffer 2. */
#ifndef GCC_BUILD
#ifdef EDMA3_ENABLE_DCACHE
/**
* The DATA_ALIGN pragma aligns the symbol to an alignment boundary. The
* alignment boundary is the maximum of the symbol’s default alignment value
* or the value of the constant in bytes. The constant must be a power of 2.
* The syntax of the pragma in C is:
* #pragma DATA_ALIGN (symbol, constant);
*/
#pragma DATA_ALIGN(_srcBuff2, EDMA3_CACHE_LINE_SIZE_IN_BYTES);
#endif  /* #ifdef EDMA3_ENABLE_DCACHE */
#pragma DATA_SECTION(_srcBuff2, ".my_sect_ddr");
signed char   _srcBuff2[MAX_BUFFER_SIZE];
#else
#ifdef EDMA3_ENABLE_DCACHE
signed char   __attribute__((section(".my_sect_ddr"))) _srcBuff2[MAX_BUFFER_SIZE] __attribute__ ((aligned (EDMA3_CACHE_LINE_SIZE_IN_BYTES)));
#else
signed char   __attribute__((section(".my_sect_ddr"))) _srcBuff2[MAX_BUFFER_SIZE];
#endif
#endif

#ifndef GCC_BUILD
#ifdef EDMA3_ENABLE_DCACHE
/* Cache line aligned destination buffer 2. */
/**
* The DATA_ALIGN pragma aligns the symbol to an alignment boundary. The
* alignment boundary is the maximum of the symbol’s default alignment value
* or the value of the constant in bytes. The constant must be a power of 2.
* The syntax of the pragma in C is:
* #pragma DATA_ALIGN (symbol, constant);
*/
#pragma DATA_ALIGN(_dstBuff2, EDMA3_CACHE_LINE_SIZE_IN_BYTES);
#endif  /* #ifdef EDMA3_ENABLE_DCACHE */
#pragma DATA_SECTION(_dstBuff2, ".my_sect_ddr");
signed char   _dstBuff2[MAX_BUFFER_SIZE];
#else
#ifdef EDMA3_ENABLE_DCACHE
signed char   __attribute__((section(".my_sect_ddr"))) _dstBuff2[MAX_BUFFER_SIZE] __attribute__ ((aligned (EDMA3_CACHE_LINE_SIZE_IN_BYTES)));
#else
signed char   __attribute__((section(".my_sect_ddr"))) _dstBuff2[MAX_BUFFER_SIZE];
#endif
#endif

signed char *srcBuff2;
signed char *dstBuff2;


/* Callback function 1 */
void callback1 (uint32_t tcc, EDMA3_RM_TccStatus status,
                void *appData)
{
    (void)tcc;
    (void)appData;

    switch (status)
    {
    case EDMA3_RM_XFER_COMPLETE:
        /* Transfer completed successfully */
        irqRaised1 = 1;
        break;
    case EDMA3_RM_E_CC_DMA_EVT_MISS:
        /* Transfer resulted in DMA event miss error. */
        irqRaised1 = -1;
        break;
    case EDMA3_RM_E_CC_QDMA_EVT_MISS:
        /* Transfer resulted in QDMA event miss error. */
        irqRaised1 = -2;
        break;
    default:
        break;
    }
    edma3OsSemGive(AppSemHandle1);
}


/* Callback function 2 */
void callback2 (uint32_t tcc, EDMA3_RM_TccStatus status,
                void *appData)
{
    (void)tcc;
    (void)appData;

    switch (status)
    {
    case EDMA3_RM_XFER_COMPLETE:
        /* Transfer completed successfully */
        irqRaised2 = 1;
        break;
    case EDMA3_RM_E_CC_DMA_EVT_MISS:
        /* Transfer resulted in DMA event miss error. */
        irqRaised2 = -1;
        break;
    case EDMA3_RM_E_CC_QDMA_EVT_MISS:
        /* Transfer resulted in QDMA event miss error. */
        irqRaised2 = -2;
        break;
    default:
        break;
    }
    edma3OsSemGive(AppSemHandle2);
}
