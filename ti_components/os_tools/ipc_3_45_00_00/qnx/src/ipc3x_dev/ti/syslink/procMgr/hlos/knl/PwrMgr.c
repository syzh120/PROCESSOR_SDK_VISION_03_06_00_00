/*
 *  @file   PwrMgr.c
 *
 *  @brief      Generic Power Manager that calls into specific PwrMgr instance
 *              through function table interface.
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2015, Texas Instruments Incorporated
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



/*-------------------------   Standard headers   -----------------------------*/
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>

/* Module level headers */
#include <PwrDefs.h>
#include <PwrMgr.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 * Functions called by ProcMgr
 * =============================================================================
 */
/*!
 *  @brief      Function to attach to the PwrMgr.
 *
 *              This function calls into the specific PwrMgr implementation
 *              to attach to it.
 *              This function is called from the ProcMgr attach function, and
 *              hence is used to perform any activities that may be required
 *              to attach to the PwrMgr before it can be powered up.
 *              Depending on the type of PwrMgr, this function may or may not
 *              perform any activities.
 *
 *  @param      handle     Handle to the PwrMgr object
 *  @param      params     Attach parameters
 *
 *  @sa         PwrMgr_detach
 */
inline
Int
PwrMgr_attach (PwrMgr_Handle handle, PwrMgr_AttachParams * params)
{
    Int             status    = PWRMGR_SUCCESS;
    PwrMgr_Object * pwrHandle = (PwrMgr_Object *) handle;

    GT_2trace (curTrace, GT_ENTER, "PwrMgr_attach", handle, params);

    GT_assert (curTrace, (params != NULL));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the ProcMgr level.
     */
    if (pwrHandle != NULL) {
        pwrHandle->bootMode = params->params->bootMode;

        if ((pwrHandle->bootMode == ProcMgr_BootMode_Boot) ||
            (pwrHandle->bootMode == ProcMgr_BootMode_NoLoad_Pwr)) {
            GT_assert (curTrace, (pwrHandle->pwrFxnTable.attach != NULL));
            status = pwrHandle->pwrFxnTable.attach (handle, params);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "PwrMgr_attach",
                                     status,
                                     "Failed to power up the slave processor!");
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                /* Power up the slave processor. */
                GT_assert (curTrace, (pwrHandle->pwrFxnTable.on != NULL));
                status = pwrHandle->pwrFxnTable.on (handle);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (status < 0) {
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "PwrMgr_attach",
                                         status,
                                         "Failed to power up the slave processor!");
                }
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }

    }
    GT_1trace (curTrace, GT_LEAVE, "PwrMgr_attach", status);

    /*! @retval PWRMGR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to detach from the PwrMgr.
 *
 *              This function calls into the specific PwrMgr implementation
 *              to detach from it.
 *              This function is called from the ProcMgr detach function, and
 *              hence is useful to perform any activities that may be required
 *              to detach from the PwrMgr once the slave is powered down.
 *              Depending on the type of PwrMgr, this function may or may not
 *              perform any activities.
 *
 *  @param      handle     Handle to the PwrMgr object
 *
 *  @sa         PwrMgr_attach
 */
inline
Int
PwrMgr_detach (PwrMgr_Handle handle)
{
    Int             status    = PWRMGR_SUCCESS;
    Int             tmpStatus = PWRMGR_SUCCESS;
    PwrMgr_Object * pwrHandle = (PwrMgr_Object *) handle;

    GT_1trace (curTrace, GT_ENTER, "PwrMgr_detach", handle);

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the ProcMgr level.
     */

    if (pwrHandle != NULL) {
        /* Power-down the slave processor. */
        if ((pwrHandle->bootMode == ProcMgr_BootMode_Boot) ||
            (pwrHandle->bootMode == ProcMgr_BootMode_NoLoad_Pwr)) {
            /* Power up the slave processor. */
            GT_assert (curTrace, (pwrHandle->pwrFxnTable.off != NULL));
            status = pwrHandle->pwrFxnTable.off (handle, TRUE);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "PwrMgr_detach",
                                     status,
                                     "Failed to power down the slave processor!");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

            GT_assert (curTrace, (pwrHandle->pwrFxnTable.detach != NULL));
            tmpStatus = pwrHandle->pwrFxnTable.detach (handle);
            if ((tmpStatus < 0) && (status >= 0)) {
                status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "PwrMgr_detach",
                                     status,
                                     "Failed to detach from the specific PwrMgr!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            }
        }

    }

    GT_1trace (curTrace, GT_LEAVE, "PwrMgr_detach", status);

    /*! @retval PWRMGR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to turn on power for the Slave processor.
 *
 *              This function calls into the specific PwrMgr implementation
 *              to turn on the power to the slave processor.
 *              The handle specifies the specific PwrMgr instance to be used.
 *
 *  @param      handle     Handle to the PwrMgr object
 *
 *  @sa         PwrMgr_off
 */
inline
Int
PwrMgr_on (PwrMgr_Handle handle)
{
    Int             status    = PWRMGR_SUCCESS;
    PwrMgr_Object * pwrHandle = (PwrMgr_Object *) handle;

    GT_1trace (curTrace, GT_ENTER, "PwrMgr_on", handle);

    GT_assert (curTrace, (handle != NULL));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the ProcMgr level.
     */
    GT_assert (curTrace, (pwrHandle->pwrFxnTable.on != NULL));
    status = pwrHandle->pwrFxnTable.on (handle);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "PwrMgr_on",
                             status,
                             "Failed to power on the slave processor!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "PwrMgr_on", status);

    /*! @retval PWRMGR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to turn off power for the Slave processor.
 *
 *              This function calls into the specific PwrMgr implementation
 *              to turn off the power to the slave processor.
 *              The handle specifies the specific PwrMgr instance to be used.
 *
 *  @param      handle     Handle to the PwrMgr object
 *
 *  @sa         PwrMgr_on
 */
inline
Int
PwrMgr_off (PwrMgr_Handle handle, Bool force)
{
    Int             status    = PWRMGR_SUCCESS;
    PwrMgr_Object * pwrHandle = (PwrMgr_Object *) handle;

    GT_2trace (curTrace, GT_ENTER, "PwrMgr_off", handle, force);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, ((force == TRUE) || (force == FALSE)));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the ProcMgr level.
     */
    GT_assert (curTrace, (pwrHandle->pwrFxnTable.off != NULL));
    status = pwrHandle->pwrFxnTable.off (handle, force);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "PwrMgr_off",
                             status,
                             "Failed to power off the slave processor!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "PwrMgr_off", status);

    /*! @retval PWRMGR_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
