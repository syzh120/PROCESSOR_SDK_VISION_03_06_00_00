/*
 *  Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
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
 */
/*!
 *  @file       GateHWSpinlockDrvDefs.h
 *
 *  @brief      Definitions of GateHWSpinlockDrv types and structures.
 */


#ifndef GATEHWSPINLOCK_DRVDEFS_H
#define GATEHWSPINLOCK_DRVDEFS_H


#include <ti/syslink/inc/GateHWSpinlock.h>
#include "IpcCmdBase.h"
#include <ti/syslink/inc/IoctlDefs.h>

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*  ----------------------------------------------------------------------------
 *  IOCTL command IDs for GateHWSpinlock
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Base command ID for GateHWSpinlock
 */
#define GATEHWSPINLOCK_BASE_CMD                 0x170

/*!
 *  @brief  Command for GateHWSpinlock_getConfig
 */
#define CMD_GATEHWSPINLOCK_GETCONFIG             _IOWR(IPCCMDBASE,\
                                            GATEHWSPINLOCK_BASE_CMD + 1u,\
                                            GateHWSpinlockDrv_CmdArgs)

/*  ----------------------------------------------------------------------------
 *  Command arguments for GateHWSpinlock
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Command arguments for GateHWSpinlock
 */
typedef struct GateHWSpinlockDrv_CmdArgs {
    union {
        struct {
            GateHWSpinlock_Config * config;
        } getConfig;
        /*
         * Technically we do not need this union but left it there for
         * consistency and in case we need to add commands in the future.
         */
    } args;

    Int32 apiStatus;
} GateHWSpinlockDrv_CmdArgs;


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* GateHWSpinlock_DrvDefs_H */
