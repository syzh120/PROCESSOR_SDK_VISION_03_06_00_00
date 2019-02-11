/*
 *  @file   OMAP5430BenelliPhyShmem.c
 *
 *  @brief      Qnx shared memory physical interface file for OMAP5430Benelli.
 *
 *              This module is responsible for handling boot-related hardware-
 *              specific operations.
 *              The implementation is specific to OMAP5430Benelli.
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




/* Standard headers */
#include <ti/syslink/Std.h>

/* Module headers */
#include <_ProcDefs.h>
#include <Processor.h>

/* OSAL and utils */
#include <ti/syslink/utils/Trace.h>

/* Hardware Abstraction Layer headers */
#include <OMAP5430BenelliHal.h>
#include <OMAP5430BenelliHalReset.h>
#include <OMAP5430BenelliPhyShmem.h>
#include <OMAP5430BenelliHalMmu.h>
#include <hw/inout.h>

#define INREG32(x) in32(x)
#define OUTREG32(x, y) out32(x, y)


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */


/* =============================================================================
 * APIs called by OMAP5430BenelliPROC module
 * =============================================================================
 */
/*!
 *  @brief      Function to initialize Shared Driver/device.
 *
 *  @param      halObj      Pointer to the HAL object
 *  @param      addrInfo    Pointer to address info
 *
 *  @sa         OMAP5430BENELLI_phyShmemExit
 *              Memory_map
 */
Int
OMAP5430BENELLI_phyShmemInit (Ptr halObj,ProcMgr_AddrInfo *addrInfo)
{
    Int                         status    = PROCESSOR_SUCCESS;
    OMAP5430BENELLI_HalObject * halObject = NULL;
    Memory_MapInfo              mapInfo;

    GT_1trace (curTrace, GT_ENTER, "OMAP5430BENELLI_phyShmemInit", halObj);

    GT_assert (curTrace, (halObj != NULL));
    GT_assert (curTrace, (addrInfo != NULL));

    halObject = (OMAP5430BENELLI_HalObject *) halObj;
    if(halObject->procId != PROCTYPE_DSP){
        /* Map MMU base */
        mapInfo.src      = OMAP5_MMU1_BASE;
        mapInfo.size     = OMAP5_MMU1_SIZE;
        mapInfo.isCached = FALSE;
        status = Memory_map (&mapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "OMAP5430BENELLI_phyShmemInit",
                                 status,
                                 "Failure in Memory_map for MMU base");
            halObject->mmuBase = 0;
        }
        else {
            halObject->mmuBase = mapInfo.dst;
        }
    }
    if(halObject->procId == PROCTYPE_DSP){
        /* Map MMU base */
        mapInfo.src      = OMAP5_MMU2_BASE;
        mapInfo.size     = OMAP5_MMU2_SIZE;
        mapInfo.isCached = FALSE;
        status = Memory_map (&mapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "OMAP5430BENELLI_phyShmemInit",
                                 status,
                                 "Failure in Memory_map for MMU base");
            halObject->mmuBase = 0;
        }
        else {
            halObject->mmuBase = mapInfo.dst;
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "OMAP5430BENELLI_phyShmemInit", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to finalize Shared Driver/device.
 *
 *  @param      halObj      Pointer to the HAL object
 *  @param      addrInfo    Pointer to addr info
 *
 *  @sa         OMAP5430BENELLI_phyShmemInit
 *              Memory_Unmap
 */
Int OMAP5430BENELLI_phyShmemExit (Ptr halObj, ProcMgr_AddrInfo *addrInfo)
{
    Int                         status    = PROCESSOR_SUCCESS;
    OMAP5430BENELLI_HalObject * halObject = NULL;
    Memory_UnmapInfo            unmapInfo;

    GT_1trace (curTrace, GT_ENTER, "OMAP5430BENELLI_phyShmemExit", halObj);

    GT_assert (curTrace, (halObj != NULL));
    GT_assert (curTrace, (addrInfo != NULL));

    halObject = (OMAP5430BENELLI_HalObject *) halObj;

    unmapInfo.addr = halObject->mmuBase;
    unmapInfo.size = MMU_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "OMAP5430BENELLI_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for MMU base");
        }
        halObject->mmuBase = 0;
    }

    GT_1trace (curTrace, GT_LEAVE, "OMAP5430BENELLI_phyShmemExit",status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)

}
#endif
