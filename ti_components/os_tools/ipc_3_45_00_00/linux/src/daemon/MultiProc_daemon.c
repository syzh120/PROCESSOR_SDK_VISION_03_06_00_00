/*
 * Copyright (c) 2013-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  @file	MultiProc_daemon.c
 *
 *  @brief	Handles processor id management in multi processor systems. Used
 *		to set/get processor ids for their oprations.
 *
 */

/* Standard IPC headers */
#include <ti/ipc/Std.h>

/* Linux specific header files */
#include <assert.h>
#include <string.h>

/* Module level headers */
#include <ti/ipc/MultiProc.h>
#include <_MultiProc.h>

/* for Logging */
#include <_lad.h>


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Get the default configuration for the MultiProc module. */
Void MultiProc_getConfig (MultiProc_Config * cfg)
{
    int i;
    UInt16 baseId;

    assert (cfg != NULL);

    /* Setup MultiProc config */
    memcpy (cfg, &_MultiProc_cfg, sizeof(MultiProc_Config));

    LOG1("MultiProc_getConfig() - %d procs\n", _MultiProc_cfg.numProcessors);
    LOG1("# processors in cluster: %d\n", _MultiProc_cfg.numProcsInCluster);
    baseId = _MultiProc_cfg.baseIdOfCluster;
    LOG1("cluster baseId: %d\n", baseId);

    for (i = 0; i < _MultiProc_cfg.numProcsInCluster; i++) {
        LOG2("\tProcId %d - \"%s\"\n", baseId + i, _MultiProc_cfg.nameList[i]);
    }
}
