/*
 *  @file   GateMutex.c
 *
 *  @brief      Gate based on Mutex
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
#include <OsalMutex.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/Trace.h>

/* Module level headers */
#include <IObject.h>
#include <ti/syslink/utils/IGateProvider.h>
#include <ti/syslink/utils/GateMutex.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* -----------------------------------------------------------------------------
 *  Structs & Enums
 * -----------------------------------------------------------------------------
 */
/*! @brief  Object for Gate Mutex */
struct GateMutex_Object {
        IGateProvider_SuperObject; /* For inheritance from IGateProvider */
        IOBJECT_SuperObject;       /* For inheritance for IObject */
    OsalMutex_Handle          mHandle;
    /*!< Handle to OSAL Mutex object */
};


/* -----------------------------------------------------------------------------
 *  Forward declarations
 * -----------------------------------------------------------------------------
 */
/* Forward declaration of function */
IArg   GateMutex_enter (GateMutex_Handle gmhandle);

/* Forward declaration of function */
Void GateMutex_leave (GateMutex_Handle gmhandle, IArg   key);


/* -----------------------------------------------------------------------------
 *  APIs
 * -----------------------------------------------------------------------------
 */
/*!
 *  ======== GateMutex_Instance_init ========
 */
Int GateMutex_Instance_init (      GateMutex_Object * obj,
                             const GateMutex_Params * params)
{
    Int status = 0;

    GT_2trace (curTrace, GT_ENTER, "GateMutex_Instance_init", obj, params);

        IGateProvider_ObjectInitializer (obj, GateMutex);

        obj->mHandle = OsalMutex_create (OsalMutex_Type_Interruptible);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (obj->mHandle == NULL) {
                status = 1;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "GateMutex_Instance_init",
                                 GateMutex_E_FAIL,
                                 "Unable to create Osal mutex object!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "GateMutex_Instance_init", status);

    return status;
}


/*!
 *  @brief      Function to delete a Gate based on Mutex.
 *
 *  @param      gmhandle  Handle to previously created gate mutex instance.
 *
 *  @sa         GateMutex_create
 */
Void
GateMutex_Instance_finalize (GateMutex_Handle gmHandle, Int status)
{
    GT_2trace (curTrace, GT_ENTER, "GateMutex_Instance_finalize",
               gmHandle, status);

    switch (status) {
        /* No break here. Fall through to the next. */
        case 0:
        {
            if (gmHandle->mHandle != NULL) {
                OsalMutex_delete (&gmHandle->mHandle);
            }
        }
        /* No break here. Fall through to the next. */

        case 1:
        {
            /* Nothing to be done. */
        }
    }

    GT_0trace (curTrace, GT_LEAVE, "GateMutex_Instance_finalize");
}


/*!
 *  @brief      Function to enter a Gate Mutex.
 *
 *  @param      gmhandle  Handle to previously created gate mutex instance.
 *
 *  @sa         GateMutex_leave
 */
IArg
GateMutex_enter (GateMutex_Handle gmHandle)
{
    IArg   key = 0x0;

    GT_1trace (curTrace, GT_ENTER, "GateMutex_enter", gmHandle);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (gmHandle == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "GateMutex_enter",
                             GateMutex_E_INVALIDARG,
                             "Handle passed is invalid!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        key = OsalMutex_enter ((OsalMutex_Handle) gmHandle->mHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "GateMutex_enter", key);

    /*! @retval Flags Operation successful */
    return key;
}


/*!
 *  @brief      Function to leave a Gate Mutex.
 *
 *  @param      gmhandle  Handle to previously created gate mutex instance.
 *  @param      key       Flags.
 *
 *  @sa         GateMutex_enter
 */
Void
GateMutex_leave (GateMutex_Handle gmHandle, IArg   key)
{
    GT_1trace (curTrace, GT_ENTER, "GateMutex_leave", gmHandle);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (gmHandle == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "GateMutex_enter",
                             GateMutex_E_INVALIDARG,
                             "Handle passed is invalid!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        OsalMutex_leave ((OsalMutex_Handle) gmHandle->mHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "GateMutex_leave");
}


/* Override the IObject interface to define craete and delete APIs */
IOBJECT_CREATE0 (GateMutex);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
