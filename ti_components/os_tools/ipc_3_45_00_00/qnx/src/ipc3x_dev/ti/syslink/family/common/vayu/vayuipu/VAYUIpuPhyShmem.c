/*
 *  @file   VAYUIpuPhyShmem.c
 *
 *  @brief      Shared memory physical interface file for VAYUIPU.
 *
 *              This module is responsible for handling boot-related hardware-
 *              specific operations.
 *              The implementation is specific to VAYUIPU.
 *
 *
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



/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL and utils */
#include <ti/syslink/utils/Memory.h>

#include <ti/syslink/utils/Trace.h>

/* Module headers */
#include <_ProcDefs.h>
#include <Processor.h>
#include <_MultiProc.h>

/* Hardware Abstraction Layer headers */
#include <VAYUIpuHal.h>
#include <VAYUIpuHalBoot.h>
#include <VAYUIpuPhyShmem.h>
#include <VAYUIpuHalMmu.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */


/* =============================================================================
 * APIs called by VAYUIPUPROC module
 * =============================================================================
 */
/*!
 *  @brief      Function to initialize Shared Driver/device.
 *
 *  @param      halObj  Pointer to the HAL object
 *
 *  @sa         VAYUIPU_phyShmemExit
 *              Memory_map
 */
Int
VAYUIPU_phyShmemInit (Ptr halObj)
{
    Int                 status    = PROCESSOR_SUCCESS;
    VAYUIPU_HalObject * halObject = NULL;
    Memory_MapInfo      mapInfo;
    UInt16              ipu1ProcId = MultiProc_getId("IPU1");

    GT_1trace (curTrace, GT_ENTER, "VAYUIPU_phyShmemInit", halObj);

    GT_assert (curTrace, (halObj != NULL));

    halObject = (VAYUIPU_HalObject *) halObj;

    if (halObject->procId == ipu1ProcId) {
        mapInfo.src      = IPU1_CM_BASE_ADDR;
    }
    else {
        mapInfo.src      = IPU2_CM_BASE_ADDR;
    }

    mapInfo.size     = CM_SIZE;
    mapInfo.isCached = FALSE;
    status = Memory_map (&mapInfo);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPU_phyShmemInit",
                             status,
                             "Failure in Memory_map for MMU base registers");
        halObject->cmBase = 0;
    }
    else {
        halObject->cmBase = mapInfo.dst;
    }

    if (halObject->procId == ipu1ProcId) {
        mapInfo.src      = IPU1_PRCM_BASE_ADDR;
    }
    else {
        mapInfo.src      = IPU2_PRCM_BASE_ADDR;
    }
    mapInfo.size     = PRCM_SIZE;
    mapInfo.isCached = FALSE;
    status = Memory_map (&mapInfo);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPU_phyShmemInit",
                             status,
                             "Failure in Memory_map for MMU base registers");
        halObject->prmBase = 0;
    }
    else {
        halObject->prmBase = mapInfo.dst;
    }

    if (halObject->procId == ipu1ProcId) {
        mapInfo.src      = IPU1_MMU_BASE;
    }
    else {
        mapInfo.src      = IPU2_MMU_BASE;
    }

    mapInfo.size     = MMU_SIZE;
    mapInfo.isCached = FALSE;
    status = Memory_map (&mapInfo);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPU_phyShmemInit",
                             status,
                             "Failure in Memory_map for MMU base registers");
        halObject->mmuBase = 0;
    }
    else {
        halObject->mmuBase = mapInfo.dst;
    }

    mapInfo.src      = CTRL_MODULE_BASE;
    mapInfo.size     = CTRL_MODULE_SIZE;
    mapInfo.isCached = FALSE;
    status = Memory_map (&mapInfo);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPU_phyShmemInit",
                             status,
                             "Failure in Memory_map for Ctrl Module base registers");
        halObject->ctrlModBase = 0;
    }
    else {
        halObject->ctrlModBase = mapInfo.dst;
    }

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPU_phyShmemInit", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to finalize Shared Driver/device.
 *
 *  @param      halObj  Pointer to the HAL object
 *
 *  @sa         VAYUIPU_phyShmemInit
 *              Memory_Unmap
 */
Int
VAYUIPU_phyShmemExit (Ptr halObj)
{
    Int                 status    = PROCESSOR_SUCCESS;
    VAYUIPU_HalObject * halObject = NULL;
    Memory_UnmapInfo    unmapInfo;

    GT_1trace (curTrace, GT_ENTER, "VAYUIPU_phyShmemExit", halObj);

    GT_assert (curTrace, (halObj != NULL));

    halObject = (VAYUIPU_HalObject *) halObj;

    unmapInfo.addr = halObject->ctrlModBase;
    unmapInfo.size = CTRL_MODULE_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUIPU_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for Ctrl Module base registers");
        }
        halObject->ctrlModBase = 0 ;
    }

    unmapInfo.addr = halObject->mmuBase;
    unmapInfo.size = MMU_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUIPU_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for MMU base registers");
        }
        halObject->mmuBase = 0 ;
    }

    unmapInfo.addr = halObject->cmBase;
    unmapInfo.size = CM_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUIPU_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for CM base registers");
        }
        halObject->cmBase = 0 ;
    }

    unmapInfo.addr = halObject->prmBase;
    unmapInfo.size = PRCM_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUIPU_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for PRCM base registers");
        }
        halObject->prmBase = 0 ;
    }

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPU_phyShmemExit",status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)

}
#endif
