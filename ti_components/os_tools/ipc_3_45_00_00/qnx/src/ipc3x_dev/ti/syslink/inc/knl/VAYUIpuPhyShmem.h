/**
 *  @file   VAYUIpuPhyShmem.h
 *
 *  @brief      Physical Interface Abstraction Layer for VAYUIPU.
 *
 *              This file contains the definitions for shared memory physical
 *              link being used with VAYUIPU.
 *              The implementation is specific to VAYUIPU.
 *
 *
 */
/*
 *  ============================================================================
 *
 *  Copyright (c) 2013-2014, Texas Instruments Incorporated
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


#ifndef VAYUIPUPHYSHMEM_H_0xbbed
#define VAYUIPUPHYSHMEM_H_0xbbed


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
/*!
 *  @brief  Base addresses and size of PRCM module.
 */
#define IPU1_PRCM_BASE_ADDR             0x4AE06300
#define IPU2_PRCM_BASE_ADDR             0x4AE06700

#define PRCM_SIZE                  0x00002000

/*!
 *  @brief  Base addresses and size of control module.
 */
#define IPU1_CM_BASE_ADDR          0x4A005300
#define IPU2_CM_BASE_ADDR          0x4A008700

#define CM_SIZE                    0x00002000

/*!
 *  @brief  Base addresses and size of MMU registers.
 */
#define IPU1_MMU_BASE              0x58882000
#define IPU2_MMU_BASE              0x55082000

#define MMU_SIZE                   0x1000

/*!
 *  @def    CTRL_MODULE_BASE
 *  @brief  configuration address.
 */
#define CTRL_MODULE_BASE           0x4A002000

/*!
 *  @def    CTRL_MODULE_SIZE
 *  @brief  size to be ioremapped.
 */
#define CTRL_MODULE_SIZE           0x1000

/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Initializes Shared Driver/device. */
Int VAYUIPU_phyShmemInit (Ptr halObj);

/* Finalizes Shared Driver/device. */
Int VAYUIPU_phyShmemExit (Ptr halObj);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* vayuipu_phy_shmem_H_0xbbec */
