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
 * \file tlb_config_eve1.c
 *
 * \brief  This file implements common MMU configuration for all EVE
 *         in TDA2x as per VisionSDK requirments
 *
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <tlb_config_eve_common.h>

/*******************************************************************************
 *  DEFINES
 ***************************************************************************** */

/* To allow skipping of configuration for some TLB entries */
#define INVALID_PG          (0xFFFFFFFFU)

/* Memory section sizes */
#define SIZE_16MB           (0x01000000U)
#define SIZE_1GB            (0x40000000U)

/*
 *  The offset into the Translation Table Buffer (TTB) is calculated as:
 *      eg. if virtAddr = 0x12345678 then offset = (0x123 << 2) bytes.
 *  For address space ending at 0xC0000000 which is end of 1 GB starting
 *  from 0x80000000:
 *      Translation Table Size = (0xC00 << 2) = 12288 bytes = 3072 entries
 *  The TTB should be aligned to the size of the Translation Table,
 *  and for table size of 12288 bytes the next immediate power of 2 is 16384.
 */
#pragma DATA_ALIGN(gTtbAddress, 16384)
#pragma DATA_SECTION(gTtbAddress, ".ttbSection")
UInt32 gTtbAddress[3072U];

/* Locked TLB entries */
const UInt32 tlbMapping[] =
{
    /* PHYS   ,  VIRT   */
    0x41000000U, 0x41000000U,   /* 00 - OCMC CBUF1 */
    INVALID_PG, INVALID_PG,     /* 01 - Programmed by SBL 0x0 - entry point */
    INVALID_PG, INVALID_PG,     /* 02 - Programmed by SBL for entry point page */
    INVALID_PG, INVALID_PG,     /* 03 - Programmed by SBL 0x40000000 - 0x40000000 */
    INVALID_PG, INVALID_PG,     /* 04 - Programmed by SBL 0x48000000 - 0x48000000 */
    0x42000000U, 0x42000000U,   /* 05 - Required for IPC mailboxes */
    0x54000000U, 0x54000000U,   /* 06 - Required for DRM registers */
};

/* TTB buffer entries */
const UInt32 ttbMapping[] =
{
    /* PHYS,     VIRT,        SIZE */
    0x49000000U, 0x49000000U, SIZE_16MB,    /* 01 - OCMC CBUF2, CBUF3 */
    0x4A000000U, 0x4A000000U, SIZE_16MB,    /* 02 - VIP and peripheral accesses */
    0x80000000U, 0x80000000U, SIZE_1GB,     /* 03 - 1 GB DDR */
};

/**
 *******************************************************************************
 *
 * \brief This function implements the MMU configuration common for all EVEs
 *        in TDA2x as required by VisionSDK
 *
 * \return  void
 *
 *******************************************************************************
 */
void eveCommonMmuConfig()
{
    UInt32 i, numTlbEntries;
    MMU_TlbEntry_t  tlbEntry;
    UInt32 baseAddr = SOC_EVE_MMU0_BASE;
    UInt32 j;
    UInt32 ttbSize, numSuperSections, numTtbEntries;
    UInt32 ttbEntryBaseVirt, ttbEntryBasePhy;

    tlbEntry.valid          = 1U;
    tlbEntry.pageSize       = MMU_PAGESIZE_16MB;
    tlbEntry.endianness     = MMU_Little_Endian;
    tlbEntry.elementSize    = MMU_Byte_ElementSize; /* Unsupported - keep 0 */
    tlbEntry.tlbElementSize = MMU_TLB_ElementSize;  /* Unsupported - keep 0 */
    tlbEntry.preserve       = 1U;   /* 0 => No protection against flush */
                                    /* 1 => protection against flush */

    /* Max num of TLB entries is 32 */
    numTlbEntries = sizeof(tlbMapping)/(2 * sizeof(UInt32));

    for ( i = 0; i < numTlbEntries; i++)
    {
        if(INVALID_PG == tlbMapping[i*2U])
        {
            continue;
        }
        tlbEntry.phyAddr        = tlbMapping[i*2U];
        tlbEntry.virtAddr       = tlbMapping[(i*2U) + 1U];
        MMUTlbEntrySet(baseAddr,
                       i,
                       (const MMU_TlbEntry_t *) &tlbEntry);
    }

    /* Lock the first 'numTlbEntries' */
    MMUTlbLockSet(baseAddr, numTlbEntries);

    numTtbEntries = sizeof(ttbMapping)/(3 * sizeof(UInt32));

    for(i = 0; i < numTtbEntries; i++)
    {
        ttbEntryBasePhy = ttbMapping[i * 3U];
        ttbEntryBaseVirt = ttbMapping[(i * 3U) + 1U];
        ttbSize = ttbMapping[(i * 3U) + 2U];

        numSuperSections = ttbSize/SIZE_16MB;

        for(j = 0; j < numSuperSections; j++)
        {
            MMUSuperSection(
                ttbEntryBasePhy + (j * SIZE_16MB),      /* physicalAddr */
                ttbEntryBaseVirt + (j * SIZE_16MB),     /* virtualAddr */
                (UInt32)&gTtbAddress[0],                /* TTB */
                MMU_Little_Endian,                      /* endianism */
                MMU_NoTranslation_ElementSize,          /* elementSize */
                MMU_CPUES,                              /* mixedSize */
                MMU_NO_FAULT);                          /* faultType */
        }
    }

    /* Set TTB buffer Address */
    MMUTTBSet(baseAddr, (UInt32)&gTtbAddress[0]);

    /* Enable Table Walking Logic */
    MMUWtlEnable(baseAddr);

    /*Enable MMU*/
    MMUEnable(baseAddr);
}
