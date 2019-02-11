/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
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
 * */
/*
 * ======== mem_data.c ========
 */

#include <xdc/std.h>
#include <netmain.h>
#include <_oskern.h>

/* Raw Memory Configuration */

/* Total MAX Memory Allocation */

/* These sizes may be overridden by defining _NDK_MIN_PAGE_SIZE.  If defined, */
/* the values for RAW_PAGE_SIZE and RAW_PAGE_COUNT must be defined elsewhere. */
#ifndef _NDK_MIN_PAGE_SIZE
#define RAW_PAGE_SIZE           3072
#define RAW_PAGE_COUNT          16
#endif

const int ti_ndk_config_Global_rawPageSize  = RAW_PAGE_SIZE;
const int ti_ndk_config_Global_rawPageCount = RAW_PAGE_COUNT;

/* P.I.T. */
#ifdef __TI_COMPILER_VERSION__
#if defined(_TMS320C6X)
#pragma DATA_SECTION(ti_ndk_config_Global_pit, ".far:NDK_MMBUFFER");
#pragma DATA_SECTION(ti_ndk_config_Global_pitBuffer, ".far:NDK_MMBUFFER");
#else
#pragma DATA_SECTION(ti_ndk_config_Global_pit, ".bss:NDK_MMBUFFER");
#pragma DATA_SECTION(ti_ndk_config_Global_pitBuffer, ".bss:NDK_MMBUFFER");
#endif
#endif
PITENTRY ti_ndk_config_Global_pit[RAW_PAGE_COUNT];
UINT8    ti_ndk_config_Global_pitBuffer[RAW_PAGE_SIZE*RAW_PAGE_COUNT];

/* Memory Bucket Information */

#define SMALLEST                48
#define LARGEST                 (RAW_PAGE_SIZE)

const int ti_ndk_config_Global_smallest = SMALLEST;
const int ti_ndk_config_Global_largest  = LARGEST;

/* Memory Slot Tracking */
uint ti_ndk_config_Global_Id2Size[]  =
        {SMALLEST, 96, 128, 256, 512, 1536, LARGEST};

