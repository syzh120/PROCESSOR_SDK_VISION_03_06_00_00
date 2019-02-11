/*
 *  @file   VAYUIpuHal.c
 *
 *  @brief      Top-level Hardware Abstraction Module implementation
 *
 *              This module implements the top-level Hardware Abstraction Layer
 *              for VAYUIPU.
 *              The implementation is specific to VAYUIPU.
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
#include <ti/syslink/utils/Memory.h>

#include <ti/syslink/utils/Trace.h>
/* Hardware Abstraction Layer headers */
#include <_ProcDefs.h>
#include <Processor.h>
#include <VAYUIpuHal.h>
#include <VAYUIpuHalBoot.h>
#include <VAYUIpuPhyShmem.h>


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
 *  @brief      Function to initialize the HAL object
 *
 *  @param      halObj      Return parameter: Pointer to the HAL object
 *  @param      initParams  Optional initialization parameters
 *
 *  @sa         VAYUIPU_halExit
 *              VAYUIPU_phyShmemInit
 */
Int
VAYUIPU_halInit (Ptr * halObj, Ptr params)
{
    Int                 status    = PROCESSOR_SUCCESS;
    VAYUIPU_HalObject * halObject = NULL;
    VAYUIPU_HalParams * halParams = NULL;

    GT_2trace (curTrace, GT_ENTER, "VAYUIPU_halInit", halObj, params);

    GT_assert (curTrace, (halObj != NULL));

    halObject = (VAYUIPU_HalObject *) halObj ;

    halParams = (VAYUIPU_HalParams *)params ;

    *halObj = Memory_calloc (NULL, sizeof (VAYUIPU_HalObject), 0, NULL);
    if (halObject == NULL) {
        /*! @retval PROCESSOR_E_MEMORY Memory allocation failed */
        status = PROCESSOR_E_MEMORY;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPU_halInit",
                             status,
                             "Memory allocation failed for HAL object!");
    }
    else {
        halObject = (VAYUIPU_HalObject *) *halObj ;
        halObject->procId = halParams->procId;

        status = VAYUIPU_phyShmemInit (*halObj);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUIPU_halInit",
                                 status,
                                 "VAYUIPU_phyShmemInit failed!");
            Memory_free (NULL, *halObj, sizeof (VAYUIPU_HalObject));
            *halObj = NULL;
        }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPU_halInit", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to finalize the HAL object
 *
 *  @param      halObj      Pointer to the HAL object
 *
 *  @sa         VAYUIPU_halInit
 *              VAYUIPU_phyShmemExit
 */
Int
VAYUIPU_halExit (Ptr halObj)
{
    Int                  status    = PROCESSOR_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "VAYUIPU_halExit", halObj);

    GT_assert (curTrace, (halObj != NULL));

    status = VAYUIPU_phyShmemExit (halObj);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPU_halExit",
                             status,
                             "VAYUIPU_phyShmemExit failed!");
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    if (halObj != NULL) {
        /* Free the memory for the HAL object. */
        Memory_free (NULL, halObj, sizeof (VAYUIPU_HalObject));
    }

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPU_halExit", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)
}
#endif
