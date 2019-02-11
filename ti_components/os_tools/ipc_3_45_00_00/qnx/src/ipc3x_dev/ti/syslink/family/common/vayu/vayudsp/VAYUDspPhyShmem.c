/*
 *  @file   VAYUDspPhyShmem.c
 *
 *  @brief      Shared memory physical interface file for VAYUDSP.
 *
 *              This module is responsible for handling boot-related hardware-
 *              specific operations.
 *              The implementation is specific to VAYUDSP.
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2013-2015, Texas Instruments Incorporated
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


/* Hardware Abstraction Layer headers */
#include <VAYUDspHal.h>
#include <VAYUDspHalBoot.h>
#include <VAYUDspHalReset.h>
#include <VAYUDspPhyShmem.h>
#include <VAYUDspHalMmu.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */


/* =============================================================================
 * APIs called by VAYUDSPPROC module
 * =============================================================================
 */
/*!
 *  @brief      Function to initialize Shared Driver/device.
 *
 *  @param      halObj  Pointer to the HAL object
 *
 *  @sa         VAYUDSP_phyShmemExit
 *              Memory_map
 */
Int
VAYUDSP_phyShmemInit (Ptr halObj)
{
    Int                  status    = PROCESSOR_SUCCESS;
    VAYUDSP_HalObject *  halObject = NULL;
    Memory_MapInfo       mapInfo;
    UInt16              dsp1ProcId = MultiProc_getId("DSP1");

    GT_1trace (curTrace, GT_ENTER, "VAYUDSP_phyShmemInit", halObj);

    GT_assert (curTrace,(halObj != NULL));

    halObject = (VAYUDSP_HalObject *) halObj;

    if (halObject->procId == dsp1ProcId) {
        mapInfo.src = DSP1_BOOT_ADDR;
    }
    else {
        mapInfo.src = DSP2_BOOT_ADDR;
    }
    mapInfo.size = DSP_BOOT_ADDR_SIZE;
    mapInfo.isCached = FALSE;

    status = Memory_map (&mapInfo);

    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSP_phyShmemInit",
                             status,
                             "Failure in Memory_map for MMU base registers");
        halObject->generalCtrlBase = 0;
    }
    else {
        halObject->generalCtrlBase = mapInfo.dst;
    }

    /* Not used */
    halObject->bootStatBase = 0;
    halObject->l2ClkBase = 0;

    if (halObject->procId == dsp1ProcId) {
        mapInfo.src      = CM_DSP1_BASE_ADDR;
    }
    else {
        mapInfo.src      = CM_DSP2_BASE_ADDR;
    }
    mapInfo.size     = CM_SIZE;
    mapInfo.isCached = FALSE;
    status = Memory_map (&mapInfo);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSP_phyShmemInit",
                             status,
                             "Failure in Memory_map for MMU base registers");
        halObject->cmBase = 0;
    }
    else {
        halObject->cmBase = mapInfo.dst;
    }

    if (halObject->procId == dsp1ProcId) {
        mapInfo.src      = PRM_DSP1_BASE_ADDR;
    }
    else {
        mapInfo.src      = PRM_DSP2_BASE_ADDR;
    }
    mapInfo.size     = PRM_SIZE;
    mapInfo.isCached = FALSE;
    status = Memory_map (&mapInfo);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSP_phyShmemInit",
                             status,
                             "Failure in Memory_map for MMU base registers");
        halObject->prmBase = 0;
    }
    else {
        halObject->prmBase = mapInfo.dst;
    }

    if (halObject->procId == dsp1ProcId) {
        mapInfo.src      = MMU0_DSP1_BASE;
    }
    else {
        mapInfo.src      = MMU0_DSP2_BASE;
    }
    mapInfo.size     = MMU0_SIZE;
    mapInfo.isCached = FALSE;
    status = Memory_map (&mapInfo);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSP_phyShmemInit",
                             status,
                             "Failure in Memory_map for MMU0 base registers");
        halObject->mmu0Base = 0;
    }
    else {
        halObject->mmu0Base = mapInfo.dst;
    }

    if (halObject->procId == dsp1ProcId) {
        mapInfo.src      = MMU1_DSP1_BASE;
    }
    else {
        mapInfo.src      = MMU1_DSP2_BASE;
    }
    mapInfo.size     = MMU1_SIZE;
    mapInfo.isCached = FALSE;
    status = Memory_map (&mapInfo);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSP_phyShmemInit",
                             status,
                             "Failure in Memory_map for MMU1 base registers");
        halObject->mmu1Base = 0;
    }
    else {
        halObject->mmu1Base = mapInfo.dst;
    }

    if (halObject->procId == dsp1ProcId) {
        mapInfo.src      = DSP1_SYS_MMU_CONFIG_BASE;
        }
    else {
        mapInfo.src      = DSP2_SYS_MMU_CONFIG_BASE;
    }
    mapInfo.size     = DSP_SYS_MMU_CONFIG_SIZE;
    mapInfo.isCached = FALSE;
    status = Memory_map (&mapInfo);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSP_phyShmemInit",
                             status,
                             "Failure in Memory_map for SYS MMU base registers");
        halObject->mmuSysBase = 0;
    }
    else {
        halObject->mmuSysBase = mapInfo.dst;
    }

    mapInfo.src      = CTRL_MODULE_BASE;
    mapInfo.size     = CTRL_MODULE_SIZE;
    mapInfo.isCached = FALSE;
    status = Memory_map (&mapInfo);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSP_phyShmemInit",
                             status,
                             "Failure in Memory_map for Ctrl Module base registers");
        halObject->ctrlModBase = 0;
    }
    else {
        halObject->ctrlModBase = mapInfo.dst;
    }

    GT_1trace(curTrace, GT_LEAVE, "<-- VAYUDSP_phyShmemInit: 0x%x", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to finalize Shared Driver/device.
 *
 *  @param      halObj  Pointer to the HAL object
 *
 *  @sa         VAYUDSP_phyShmemInit
 *              Memory_Unmap
 */
Int
VAYUDSP_phyShmemExit (Ptr halObj)
{
    Int                  status    = PROCESSOR_SUCCESS;
    VAYUDSP_HalObject *  halObject = NULL;
    Memory_UnmapInfo     unmapInfo;

    GT_1trace (curTrace, GT_ENTER, "VAYUDSP_phyShmemExit", halObj);

    GT_assert (curTrace, (halObj != NULL));

    halObject = (VAYUDSP_HalObject *) halObj;

    unmapInfo.addr = halObject->ctrlModBase;
    unmapInfo.size = CTRL_MODULE_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUDSP_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for Ctrl Module base registers");
        }
        halObject->ctrlModBase = 0 ;
    }

    unmapInfo.addr = halObject->mmu1Base;
    unmapInfo.size = MMU1_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUDSP_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for MMU base registers");
        }
        halObject->mmu1Base = 0 ;
    }

    unmapInfo.addr = halObject->mmu0Base;
    unmapInfo.size = MMU0_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUDSP_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for MMU base registers");
        }
        halObject->mmu0Base = 0 ;
    }

    unmapInfo.addr = halObject->mmuSysBase;
    unmapInfo.size = DSP_SYS_MMU_CONFIG_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUDSP_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for SYS MMU base registers");
        }
        halObject->mmuSysBase = 0 ;
    }

    unmapInfo.addr = halObject->cmBase;
    unmapInfo.size = CM_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUDSP_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for CM base registers");
        }
        halObject->cmBase = 0 ;
    }

    unmapInfo.addr = halObject->prmBase;
    unmapInfo.size = PRM_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUDSP_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for MMU base registers");
        }
        halObject->prmBase = 0 ;
    }

    /* Not used */
    halObject->l2ClkBase = 0 ;
    halObject->bootStatBase = 0 ;

    unmapInfo.addr = halObject->generalCtrlBase;
    unmapInfo.size = DSP_BOOT_ADDR_SIZE;
    unmapInfo.isCached = FALSE;
    if (unmapInfo.addr != 0) {
        status = Memory_unmap (&unmapInfo);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUDSP_phyShmemExit",
                              status,
                              "Failure in Memory_Unmap for MMU base registers");
        }
        halObject->generalCtrlBase = 0 ;
    }


    GT_1trace (curTrace, GT_LEAVE, "VAYUDSP_phyShmemExit",status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)

}
#endif
