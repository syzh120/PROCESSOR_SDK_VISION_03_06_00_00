/*
 *  @file   GateSpinlock.c
 *
 *  @brief      Gate based on Spinlock
 *
 *
 *  @ver        02.00.00.46_alpha1
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



/* Standard headers */
#include <ti/syslink/Std.h>

/* Osal & Utility headers */
#include <OsalSpinlock.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/Trace.h>

/* Module level headers */
#include <IObject.h>
#include <ti/syslink/utils/IGateProvider.h>
#include <ti/syslink/utils/GateSpinlock.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Structs & Enums
 * =============================================================================
 */
/*! @brief  Object for Gate Spinlock */
struct GateSpinlock_Object {
        IGateProvider_SuperObject; /* For inheritance from IGateProvider */
        IOBJECT_SuperObject;       /* For inheritance for IObject */
    OsalSpinlock_Handle       sHandle;
    /*!< Handle to OSAL Spinlock object */
};

/* =============================================================================
 *  Forward declarations
 * =============================================================================
 */
/* Function to enter a Gate Spinlock */
UInt32 GateSpinlock_enter (GateSpinlock_Handle handle);

/* Function to leave a Gate Spinlock */
Void GateSpinlock_leave (GateSpinlock_Handle handle, UInt32 key);


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/*!
 *  @brief      Function to create a Gate based on Spinlock.
 *
 *  @sa         GateSpinlock_Instance_finalize
 */
Int
GateSpinlock_Instance_init (      GateSpinlock_Object * obj,
                            const GateSpinlock_Params * params)
{
    Int status = 0;

    GT_2trace (curTrace, GT_ENTER, "GateSpinlock_Instance_init", obj, params);

    (Void) params; /* params are not used. */

        IGateProvider_ObjectInitializer (obj, GateSpinlock);

        obj->sHandle = OsalSpinlock_create (OsalSpinlock_Type_Normal);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (obj->sHandle == NULL) {
                status = 1;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "GateSpinlock_Instance_init",
                                 GateSpinlock_E_FAIL,
                                 "Unable to create Osal Spinlock object!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "GateSpinlock_Instance_init", status);

    /*! @retval 0 Operation was successful */
    return status;
}


/*!
 *  @brief      Function to delete a Gate based on Spinlock.
 *
 *  @param      handle  Handle to previously created gate Spinlock instance.
 *
 *  @sa         GateSpinlock_Instance_init
 */
Void
GateSpinlock_Instance_finalize (GateSpinlock_Handle handle, Int status)
{
    GT_2trace (curTrace, GT_ENTER, "GateSpinlock_Instance_finalize",
               handle, status);

    GT_assert (curTrace, (handle != NULL));

    switch (status) {
        /* No break here. Fall through to the next. */
        case 0:
        {
            if (handle->sHandle != NULL) {
                OsalSpinlock_delete (&handle->sHandle);
            }
        }
        /* No break here. Fall through to the next. */

        case 1:
        {
            /* Nothing to be done. */
        }
    }

    GT_0trace (curTrace, GT_LEAVE, "GateSpinlock_Instance_finalize");
}


/*!
 *  @brief      Function to enter a Gate Spinlock.
 *
 *  @param      handle  Handle to previously created gate Spinlock instance.
 *
 *  @sa         GateSpinlock_leave
 */
UInt32
GateSpinlock_enter (GateSpinlock_Handle handle)
{
    UInt32 key = 0x0;

    GT_1trace (curTrace, GT_ENTER, "GateSpinlock_enter", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (handle == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "GateSpinlock_enter",
                             GateSpinlock_E_INVALIDARG,
                             "Handle passed is invalid!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        key = OsalSpinlock_enter ((OsalSpinlock_Handle) handle->sHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "GateSpinlock_enter", key);

    /*! @retval Flags Operation successful */
    return key;
}


/*!
 *  @brief      Function to leave a Gate Spinlock.
 *
 *  @param      handle  Handle to previously created gate Spinlock instance.
 *  @param      key       Flags.
 *
 *  @sa         GateSpinlock_enter
 */
Void
GateSpinlock_leave (GateSpinlock_Handle handle, UInt32 key)
{
    GT_1trace (curTrace, GT_ENTER, "GateSpinlock_leave", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (handle == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "GateSpinlock_leave",
                             GateSpinlock_E_INVALIDARG,
                             "Handle passed is invalid!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        OsalSpinlock_leave ((OsalSpinlock_Handle) handle->sHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "GateSpinlock_leave");
}


/* Override the IObject interface to define craete and delete APIs */
IOBJECT_CREATE0 (GateSpinlock);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
