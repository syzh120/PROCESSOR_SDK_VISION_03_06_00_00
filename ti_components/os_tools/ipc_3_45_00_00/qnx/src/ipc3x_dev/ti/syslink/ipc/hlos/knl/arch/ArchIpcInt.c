/*
 *  @file   ArchIpcInt.c
 *
 *  @brief      Generic file for architecture specific interrupts
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2009, Texas Instruments Incorporated
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
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/Memory.h>
#include <Bitops.h>
#include <_MultiProc.h>
#include <ti/ipc/MultiProc.h>

/* Hardware Abstraction Layer */
#include <_ArchIpcInt.h>
#include <ArchIpcInt.h>


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @brief  Array of device specific objects
 */

ArchIpcInt_Object ArchIpcInt_object;


/*!
 *  @brief      Function to register the interrupt.
 *
 *  @param      procId  destination procId.
 *  @param      intId   interrupt id.
 *  @param      fxn     allback funxction to be called on receiving interrupt.
 *  @param      fxnArgs arguments to the callback function.
 *
 *  @sa         ArchIpcInt_interruptEnable
 */

Int32
ArchIpcInt_interruptRegister  (UInt16                 procId,
                               UInt32                 intId,
                               ArchIpcInt_CallbackFxn fxn,
                               Ptr                    fxnArgs)
{
    Int32          status = ARCHIPCINT_SUCCESS;
    GT_4trace (curTrace,
               GT_ENTER,
               "ArchIpcInt_interruptRegister",
               procId,
               intId,
               fxn,
               fxnArgs);

    GT_assert (curTrace, procId < MultiProc_MAXPROCESSORS);
    GT_assert (curTrace, (ArchIpcInt_object.isSetup == TRUE));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the calling level.
     */
    GT_assert (curTrace,
              (ArchIpcInt_object.fxnTable->interruptRegister != NULL));

    status = ArchIpcInt_object.fxnTable->interruptRegister (procId,
                                                            intId,
                                                            fxn,
                                                            fxnArgs);

    GT_1trace (curTrace, GT_LEAVE, "ArchIpcInt_interruptRegister", status);
    return status;
}


/*!
 *  @brief      Function to unregister interrupt.
 *
 *  @param      procId  destination procId
 *
 *  @sa         ArchIpcInt_interruptDisable
 */
Int32
ArchIpcInt_interruptUnregister  (UInt16 procId)
{
    Int32  status = ARCHIPCINT_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "ArchIpcInt_interruptUnregister", procId);

    GT_assert (curTrace, procId < MultiProc_MAXPROCESSORS);
    GT_assert (curTrace, (ArchIpcInt_object.isSetup == TRUE));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the calling level.
     */
    GT_assert (curTrace,
              (ArchIpcInt_object.fxnTable->interruptUnregister != NULL));

    status = ArchIpcInt_object.fxnTable->interruptUnregister (procId);

    GT_1trace (curTrace, GT_LEAVE, "ArchIpcInt_interruptUnregister", status);
    return status;
}


/*!
 *  @brief      Function to enable interrupt.
 *
 *  @param      intId  interrupt id
 *
 *  @sa         ArchIpcInt_interruptDisable
 */
Void
ArchIpcInt_interruptEnable (UInt16 procId, UInt32 intId)
{
    GT_2trace (curTrace, GT_ENTER, "ArchIpcInt_interruptEnable", procId, intId);

    GT_assert(curTrace, procId < MultiProc_MAXPROCESSORS);
    GT_assert(curTrace, (ArchIpcInt_object.isSetup == TRUE));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the calling level.
     */
    GT_assert (curTrace,
              (ArchIpcInt_object.fxnTable->interruptEnable != NULL));

    ArchIpcInt_object.fxnTable->interruptEnable (procId, intId);

    GT_0trace (curTrace, GT_LEAVE, "ArchIpcInt_interruptEnable");
}


/*!
 *  @brief      Function to enable interrupt.
 *
 *  @param      intId  interrupt id
 *
 *  @sa         ArchIpcInt_interruptEnable
 */
Void
ArchIpcInt_interruptDisable (UInt16 procId, UInt32 intId)
{
    GT_2trace (curTrace, GT_ENTER, "ArchIpcInt_interruptDisable",procId, intId);

    GT_assert(curTrace, procId < MultiProc_MAXPROCESSORS);
    GT_assert(curTrace, (ArchIpcInt_object.isSetup == TRUE));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the calling level.
     */
    GT_assert (curTrace,
              (ArchIpcInt_object.fxnTable->interruptDisable != NULL));

    ArchIpcInt_object.fxnTable->interruptDisable(procId,intId);

    GT_0trace (curTrace, GT_LEAVE, "ArchIpcInt_interruptDisable");
}


/*!
 *  @brief      Function to wait to clear interrupt.
 *
 *  @param      intId  interrupt id
 *
 *  @sa
 */
Int32
ArchIpcInt_waitClearInterrupt (UInt16 procId, UInt32 intId)
{
    Int32 status = ARCHIPCINT_SUCCESS;

    GT_2trace (curTrace,
               GT_ENTER,
               "ArchIpcInt_waitClearInterrupt",
               procId,
               intId);

    GT_assert(curTrace, procId < MultiProc_MAXPROCESSORS);
    GT_assert(curTrace, (ArchIpcInt_object.isSetup == TRUE));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the calling level.
     */
    GT_assert (curTrace,
              (ArchIpcInt_object.fxnTable->waitClearInterrupt!= NULL));

    status = ArchIpcInt_object.fxnTable->waitClearInterrupt(procId,
                                                                     intId);

    GT_1trace (curTrace, GT_LEAVE, "ArchIpcInt_waitClearInterrupt", status);
    return (status);
}


/*!
 *  @brief      Function to send an interrupt to other processor.
 *
 *  @param      intId  interrupt id
 *
 *  @sa
 */
Int32
ArchIpcInt_sendInterrupt    (UInt16 procId, UInt32 intId, UInt32 value)
{
    Int32 status = ARCHIPCINT_SUCCESS;

    GT_3trace (curTrace,
               GT_ENTER,
               "ArchIpcInt_sendInterrupt",
               procId,
               intId,
               value);

    GT_assert(curTrace, procId < MultiProc_MAXPROCESSORS);
    GT_assert(curTrace, (ArchIpcInt_object.isSetup == TRUE));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the calling level.
     */
    GT_assert (curTrace,
              (ArchIpcInt_object.fxnTable->sendInterrupt != NULL));

    status = ArchIpcInt_object.fxnTable->sendInterrupt(procId,
                                                       intId,
                                                       value);

    GT_1trace (curTrace, GT_LEAVE, "ArchIpcInt_sendInterrupt", status);
    return (status);
}


/*!
 *  @brief      Function to clear the interrupt.
 *
 *  @param      intId  interrupt id
 *
 *  @sa
 */
UInt32
ArchIpcInt_clearInterrupt  (UInt16 procId, UInt32 intId)
{
    UInt32 retVal ;

    GT_2trace (curTrace, GT_ENTER, "ArchIpcInt_clearInterrupt", procId, intId);

    GT_assert (curTrace, procId < MultiProc_MAXPROCESSORS);
    GT_assert (curTrace, (ArchIpcInt_object.isSetup == TRUE));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the calling level.
     */
    GT_assert (curTrace,
              (ArchIpcInt_object.fxnTable->clearInterrupt != NULL));

    retVal = ArchIpcInt_object.fxnTable->clearInterrupt(procId, intId);

    GT_1trace (curTrace, GT_LEAVE, "ArchIpcInt_clearInterrupt", retVal);
    return (retVal);
}

#if defined (__cplusplus)
}
#endif


