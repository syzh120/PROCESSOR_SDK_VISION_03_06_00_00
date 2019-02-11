/*
 *  @file   omap5430BenelliHal.c
 *
 *  @brief      Top-level Hardware Abstraction Module implementation
 *
 *              This module implements the top-level Hardware Abstraction Layer
 *              for OMAP5430.
 *              The implementation is specific to OMAP5430.
 *
 *
 *  @ver        02.00.00.44_pre-alpha3
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2015, Texas Instruments Incorporated
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

/* OSAL & utils headers */
#include <ti/syslink/utils/Trace.h>

/* Hardware Abstraction Layer headers */
#include <_ProcDefs.h>
#include <Processor.h>
#include <OMAP5430BenelliHal.h>
#include <OMAP5430BenelliPhyShmem.h>
#include <ti/syslink/utils/OsalPrint.h>
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
 * APIs called by OMAP5430BENELLIPROC module
 * =============================================================================
 */
/*!
 *  @brief      Function to initialize the HAL object
 *
 *  @param      halObj      Return parameter: Pointer to the HAL object
 *  @param      initParams  Optional initialization parameters
 *
 *  @sa         OMAP5430BENELLI_halExit
 *              OMAP5430BENELLI_phyShmemInit
 */
Int
OMAP5430BENELLI_halInit (Ptr * halObj, Ptr params,UInt16 procId)
{
    Int                  status    = PROCESSOR_SUCCESS;
    OMAP5430BENELLI_HalObject * halObject = NULL;
    OMAP5430BENELLIPROC_Params *lpParams = params;
    GT_2trace (curTrace, GT_ENTER, "OMAP5430BENELLI_halInit", halObj, params);

    GT_assert (curTrace, (halObj != NULL));


    halObject = (OMAP5430BENELLI_HalObject *) halObj ;
    *halObj = Memory_calloc (NULL, sizeof (OMAP5430BENELLI_HalObject), 0, NULL);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (halObject == NULL) {
        /*! @retval PROCESSOR_E_MEMORY Memory allocation failed */
        status = PROCESSOR_E_MEMORY;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OMAP5430BENELLI_halInit",
                             status,
                             "Memory allocation failed for HAL object!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        halObject = (OMAP5430BENELLI_HalObject *) *halObj ;
        halObject->procId = procId;
        halObject->procHandle = lpParams->procHandle;

        status = OMAP5430BENELLI_phyShmemInit (*halObj,lpParams->memEntries);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "OMAP5430BENELLI_halInit",
                                 status,
                                 "OMAP5430BENELLI_phyShmemInit failed!");
            Memory_free (NULL, *halObj, sizeof (OMAP5430BENELLI_HalObject));
            *halObj = NULL;
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OMAP5430BENELLI_halInit", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to finalize the HAL object
 *
 *  @param      halObj      Pointer to the HAL object
 *
 *  @sa         OMAP5430BENELLI_halInit
 *              OMAP5430BENELLI_phyShmemExit
 */
Int
OMAP5430BENELLI_halExit (Ptr halObj, Ptr params)
{
    Int                  status    = PROCESSOR_SUCCESS;
    OMAP5430BENELLI_HalObject * halObject = NULL;
    OMAP5430BENELLIPROC_Params *lpParams = params;

    GT_1trace (curTrace, GT_ENTER, "OMAP5430BENELLI_halExit", halObj);

    GT_assert (curTrace, (halObj != NULL));

    halObject = (OMAP5430BENELLI_HalObject *) halObj ;
    status = OMAP5430BENELLI_phyShmemExit(halObj, lpParams->memEntries);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OMAP5430BENELLI_halExit",
                             status,
                             "OMAP5430BENELLI_phyShmemExit failed!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    if (halObj != NULL) {
        /* Free the memory for the HAL object. */
        Memory_free (NULL, halObj, sizeof (OMAP5430BENELLI_HalObject));
    }

    GT_1trace (curTrace, GT_LEAVE, "OMAP5430BENELLI_halExit", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)
}
#endif
