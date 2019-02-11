/*
 * Copyright (c) 2013-2014, Texas Instruments Incorporated
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
/*!
 *  @file	GateHwSpinlock_daemon.c
 *
 *  @brief	GateHWSpinlock to get the base address, size and offset for the
 *              device's spinlock registers.
 *
 */

/* Standard IPC headers */
#include <ti/ipc/Std.h>

/* Linux specific header files */
#include <assert.h>
#include <string.h>

/* Module level headers */
#include <GateHWSpinlock.h>

/* for Logging */
#include <_lad.h>


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Get the default config address & sizes of the GateHWSpinlock module. */
Void GateHWSpinlock_getConfig (GateHWSpinlock_Config * cfgParams)
{
    int i;

    assert (cfgParams != NULL);

    /* Setup MultiProc config */
    memcpy (cfgParams, &_GateHWSpinlock_cfgParams,
        sizeof(GateHWSpinlock_Config));

    LOG1("GateHWSpinlock_getConfig()\tbaseAddr = 0x%x\n",
        _GateHWSpinlock_cfgParams.baseAddr);
    LOG2("\tsize = 0x%x\n\toffset = 0x%x\n",
         _GateHWSpinlock_cfgParams.size, _GateHWSpinlock_cfgParams.offset);
}
