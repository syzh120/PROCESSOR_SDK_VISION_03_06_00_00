/*
 *  @file   VAYUIpuMmu.c
 *
 *  @brief      ipu mmu code
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



#include <ti/syslink/Std.h>
/* OSAL & Utils headers */
#include <OsalDelay.h>

#include <ti/syslink/utils/Trace.h>
#include <OsalThread.h>

#include <PwrDefs.h>
#include <PwrMgr.h>
#include <VAYUIpuPwr.h>
#include <ti/syslink/inc/knl/Qnx/VAYUIpuMmu.h>
#include <ti/syslink/inc/Bitops.h>

#define REG(x)              *((volatile UInt32 *) (x))

#if defined (__cplusplus)
extern "C" {
#endif

/* =============================================================================
 *  Macros and types
 * =============================================================================
 */


Void VAYUIPUMMU_enable(PwrMgr_Handle handle)
{
    PwrMgr_Object *      pwrMgrHandle = (PwrMgr_Object *) handle;
    VAYUIPUPWR_Object * object    = NULL;

    GT_1trace (curTrace, GT_ENTER, "VAYUIPUMMU_enable", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
        if (handle == NULL) {
            /*! @retval PWRMGR_E_HANDLE Invalid argument */
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUIPUMMU_enable",
                                 PWRMGR_E_FAIL,
                                 "Invalid handle specified");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            object = (VAYUIPUPWR_Object *) pwrMgrHandle->object;
            GT_assert (curTrace, (object != NULL));
#if 0 // TODO: move enabling of MMU to this phase?
            /*Enable the Ipu Logic*/
            CLEAR_BIT(REG(object->prcmVA + RM_DEFAULT_RSTCTRL), 0x4);
            while((((REG(object->prcmVA + RM_DEFAULT_RSTST)&0x10))!=0x10));
            /* Write a while(1) so that even if m3 comes out of reset
             * m3 wont crash  */
            REG(object->ipubaseVA)        = 0x10000;
            REG(object->ipubaseVA + 0x04) = 0x9;
            REG(object->ipubaseVA + 0x08) = 0xE7FEE7FE;

            /* M4_0 and M4_1 should be taken out of reset after this
               and that is done is reset code*/
#endif
#if !defined(IPC_BUILD_OPTIMIZE)

    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    GT_0trace (curTrace, GT_LEAVE, "VAYUIPUMMU_enable");
}


Void VAYUIPUMMU_disable(PwrMgr_Handle handle)
{
    PwrMgr_Object *      pwrMgrHandle = (PwrMgr_Object *) handle;
    VAYUIPUPWR_Object * object    = NULL;

    GT_1trace (curTrace, GT_ENTER, "VAYUIPUMMU_disable", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
        if (handle == NULL) {
            /*! @retval PWRMGR_E_HANDLE Invalid argument */
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUIPUMMU_enable",
                                 PWRMGR_E_FAIL,
                                 "Invalid handle specified");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            object = (VAYUIPUPWR_Object *) pwrMgrHandle->object;
            GT_assert (curTrace, (object != NULL));
#if 0 // TODO: Move disabling of MMU to here?
            /* This code is specific for apps to run  */
            REG(object->ipubaseVA)        = 0x10000;
            REG(object->ipubaseVA + 0x04) = 0x9;
            REG(object->ipubaseVA + 0x08) = 0xE7FEE7FE;
            /* Flush the unicache so as to succeed in subsequent runs */
            REG(object->ipuMmuVA + 0x0CA8) = 0x400;

            /* DO NOT Disable the Ipu Logic*/
#endif
#if !defined(IPC_BUILD_OPTIMIZE)

    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    GT_0trace (curTrace, GT_LEAVE, "VAYUIPUMMU_disable");
}


#if defined (__cplusplus)
}
#endif
