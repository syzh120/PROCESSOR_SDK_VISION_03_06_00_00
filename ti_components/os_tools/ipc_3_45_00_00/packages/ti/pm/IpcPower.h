/*
 * Copyright (c) 2011-2013, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/** ============================================================================
 *  @file       IpcPower.h
 *  ============================================================================
 */

#ifndef ti_pm_IpcPower__include
#define ti_pm_IpcPower__include

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Structures & Definitions
 * =============================================================================
 */

/*!
 *  @def    IpcPower_S_SUCCESS
 *  @brief  Operation is successful.
 */
#define IpcPower_S_SUCCESS               (0)

/*!
 *  @def    IpcPower_E_FAIL
 *  @brief  Operation is not successful.
 */
#define IpcPower_E_FAIL                  (-1)

/*!
 *  @def    IpcPower_E_MEMORY
 *  @brief  Operation resulted in memory failure.
 */
#define IpcPower_E_MEMORY                (-2)

/*!
 *  @brief  Event types for power management callbacks
 */
typedef enum IpcPower_Event {
    IpcPower_Event_SUSPEND  = 0, /*! Callback event for Power suspend */
    IpcPower_Event_RESUME   = 1  /*! Callback event for Power resume  */
} IpcPower_Event;

/*!
 *  @brief  Power Event Callback function type definition
 */
typedef Void (*IpcPower_CallbackFuncPtr)(Int event, Ptr data);

/*!
 *  @brief  Type representing OMAP's WUGEN_MEVT[0|1] registers
 *
 *  For APIs IpcPower_getWugenEvtMask() and IpcPower_setWugenEvtMask()
 */
typedef struct IpcPower_WugenEvtMask {
    UInt32 mevt0;
    UInt32 mevt1;
} IpcPower_WugenEvtMask;

/* =============================================================================
 *  IpcPower Functions:
 * =============================================================================
 */

/*!
 *  @brief      Initialize the IpcPower module
 *
 *  @sa         IpcPower_exit
 */
Void IpcPower_init();

/*!
 *  @brief      Finalize the IpcPower module
 *
 *  @sa         IpcPower_init
 */
Void IpcPower_exit();

/*!
 *  @brief      Initiate the suspend procedure
 */
Void IpcPower_suspend();

/*!
 *  @brief      Disable the deep sleep mode in the core
 *
 *  @sa         IpcPower_wakeUnlock
 */
Void IpcPower_wakeLock();

/*!
 *  @brief      Enable the core to go to deep sleep mode
 *
 *  @sa         IpcPower_wakeLock
 */
Void IpcPower_wakeUnlock();

/*!
 *  @brief      Disable the core to go to suspend / hibernate
 *
 *  @sa         IpcPower_hibernateUnlock, IpcPower_canHibernate
 */
UInt IpcPower_hibernateLock();

/*!
 *  @brief      Enable the core to go to suspend / hibernate
 *
 *  @sa         IpcPower_hibernateLock, IpcPower_canHibernate
 */
UInt IpcPower_hibernateUnlock();

/*!
 *  @brief      Return TRUE if hibernation is allowed
 *
 *  @sa         IpcPower_hibernateLock, IpcPower_hibernateUnlock
 */
Bool IpcPower_canHibernate();

/*!
 *  @brief      Register callback function for a Power event
 *
 *  @param[in]  event  Power Management callback event type.
 *  @param[in]  fxn    Function being registered.
 *  @param[in]  data   Data to be passed as argument to function.
 *
 *  @return     SUCCESS or FAIL
 *
 *  @sa         IpcPower_registerCallback
 */
Int IpcPower_registerCallback(Int event, IpcPower_CallbackFuncPtr fxn,
                              Ptr data);

/*!
 *  @brief      Unregister callback function for a Power event
 *
 *  @param[in]  event  Power Management callback event type.
 *  @param[in]  fxn    Function being unregistered.
 *
 *  @return     SUCCESS or FAIL
 *
 *  @sa         IpcPower_unregisterCallback
 */
Int IpcPower_unregisterCallback(Int event, IpcPower_CallbackFuncPtr fxn);

/*!
 *  @brief      Retrieve current WUGEN mask used for suspend
 *
 *  @param[in]  mask  Pointer to structure for holding WUGEN event mask
 *
 *  @sa         IpcPower_suspend, IpcPower_setWugenEvtMask
 */
Void IpcPower_getWugenEvtMask(IpcPower_WugenEvtMask *mask);

/*!
 *  @brief      Set WUGEN mask used for suspend
 *
 *  The values in the passed structure are copied into the internal
 *  WUGEN event mask. To achieve an ORing of certain bits in the mask,
 *  first retrieve the current mask with IpcPower_getWugenEvtMask() and
 *  then OR in the bits you want to enable.
 *
 *  @param[in]  mask  Pointer to WUGEN event mask structure
 *
 *  @sa         IpcPower_suspend, IpcPower_getWugenEvtMask
 */
Void IpcPower_setWugenEvtMask(IpcPower_WugenEvtMask *mask);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ti_ipc_IpcPower__include */
