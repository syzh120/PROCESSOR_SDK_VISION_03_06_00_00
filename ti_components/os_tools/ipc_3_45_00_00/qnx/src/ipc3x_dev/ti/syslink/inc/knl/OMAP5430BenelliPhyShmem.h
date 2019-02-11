/**
 *  @file   OMAP5430BenelliPhyShmem.h
 *
 *  @brief      Physical Interface Abstraction Layer for OMAP5430.
 *
 *              This file contains the definitions for shared memory physical
 *              link being used with OMAP5430.
 *              The implementation is specific to OMAP5430.
 *
 *
 *  @ver        02.00.00.44_pre-alpha3
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2011, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */

#ifndef OMAP5430BenelliPhyShmem_H_0xbbec
#define OMAP5430BenelliPhyShmem_H_0xbbec


/* Module level headers */
#include <_ProcDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 *  See _ProcDefs.h
 * =============================================================================
 */
#define SHAREDMEMORY_PHY_CODE0_BASEADDR        0x9D000000
#define SHAREDMEMORY_PHY_CODE0_BASESIZE        0x00200000

/*! @brief Start of IPC shared memory for IPU0 */
#define SHAREDMEMORY_PHY_BASEADDR_IPU0         0x9CF00000
#define SHAREDMEMORY_PHY_BASESIZE_IPU0         0x00054000

/*! @brief Start of Const section for IUP0 */
#define SHAREDMEMORY_PHY_CONST0_BASEADDR       0x9E000000
#define SHAREDMEMORY_PHY_CONST0_BASESIZE       0x00100000


/*! @brief Start of Code section for IPU0 */
#define SHAREDMEMORY_PHY_CODE1_BASEADDR        0x9D800000
#define SHAREDMEMORY_PHY_CODE1_BASESIZE        0x00200000

/*! @brief Start of IPC shared memory IPU1 */
#define SHAREDMEMORY_PHY_BASEADDR_IPU1         0x9CF54000
#define SHAREDMEMORY_PHY_BASESIZE_IPU1         0x000AC000

/*! @brief Start of Const section for IPU1 */
#define SHAREDMEMORY_PHY_CONST1_BASEADDR       0x9E100000
#define SHAREDMEMORY_PHY_CONST1_BASESIZE       0x00100000

#define OMAP5_MMU1_BASE                        0x55082000
#define OMAP5_MMU1_SIZE                        0x00001000

#define OMAP5_MMU2_BASE                        0x4A066000
#define OMAP5_MMU2_SIZE                        0x00001000


#define MMU_BASE                               0x5D000000
/*!
 *  @brief  size to be ioremapped.
 */
#define MMU_SIZE                               0x1000


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Initializes Shared Driver/device. */
Int OMAP5430BENELLI_phyShmemInit (Ptr halObj, ProcMgr_AddrInfo *addrInfo);

/* Finalizes Shared Driver/device. */
Int OMAP5430BENELLI_phyShmemExit (Ptr halObj, ProcMgr_AddrInfo *addrInfo);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* OMAP5430BenelliPhyShmem_H_0xbbec */
