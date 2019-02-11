/*
 * Copyright (c) 2015, Texas Instruments Incorporated
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
 *  @file       IpcPowerDsp_null.c
 *
 *  @brief      Stubs for IpcPower API when power management is not wanted.
 *
 *  ============================================================================
 */

#include <xdc/std.h>

#include <ti/pm/IpcPower.h>

/*
 *  ======== IpcPower_getWugenEvtMask ========
 */
Void IpcPower_getWugenEvtMask(IpcPower_WugenEvtMask *mask)
{
}

/*
 *  ======== IpcPower_setWugenEvtMask ========
 */
Void IpcPower_setWugenEvtMask(IpcPower_WugenEvtMask *mask)
{
}

/*
 *  ======== IpcPower_init ========
 */
Void IpcPower_init()
{
}

/*
 *  ======== IpcPower_exit ========
 */
Void IpcPower_exit()
{
}

/*
 *  ======== IpcPower_suspend ========
 */
Void IpcPower_suspend()
{
}

/*
 *  ======== IpcPower_idle ========
 */
Void IpcPower_idle()
{
}

/*
 *  ======== IpcPower_wakeLock ========
 */
Void IpcPower_wakeLock()
{
}

/*
 *  ======== IpcPower_wakeUnlock ========
 */
Void IpcPower_wakeUnlock()
{
}

/*
 *  ======== IpcPower_hibernateLock ========
 */
UInt IpcPower_hibernateLock()
{
    return (0);
}

/*
 *  ======== IpcPower_hibernateUnlock ========
 */
UInt IpcPower_hibernateUnlock()
{
    return (0);
}


/*
 *  ======== IpcPower_canHibernate ========
 */
Bool IpcPower_canHibernate()
{
    return (FALSE);
}

/*
 *  ======== IpcPower_registerCallback ========
 */
Int IpcPower_registerCallback(Int event, IpcPower_CallbackFuncPtr cbck,
                              Ptr data)
{
    return (IpcPower_E_FAIL);
}

/*
 *  ======== IpcPower_unregisterCallback ========
 */
Int IpcPower_unregisterCallback(Int event, IpcPower_CallbackFuncPtr cbck)
{
    return (IpcPower_E_FAIL);
}
