/*
 *  Copyright (c) 2008-2013, Texas Instruments Incorporated
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
 *  @file       MultiProcQDrvDefs.h
 *
 *  @brief      Definitions of MultiProcDrv types and structures.
 */


#ifndef MULTIPROC_DRVDEFS_H_0xf2ba
#define MULTIPROC_DRVDEFS_H_0xf2ba


#include <ti/syslink/inc/_MultiProc.h>
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
 *  IOCTL command IDs for MultiProc
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Base command ID for MultiProc
 */
#define MULTIPROC_BASE_CMD                 0x130

/*!
 *  @brief  Command for MultiProc_getConfig
 */
#define CMD_MULTIPROC_GETCONFIG             _IOWR(IPCCMDBASE,\
                                            MULTIPROC_BASE_CMD + 1u,\
                                            MultiProcDrv_CmdArgs)
/*  ----------------------------------------------------------------------------
 *  Command arguments for MultiProc
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Command arguments for MultiProc
 */
typedef struct MultiProcDrv_CmdArgs {
    union {
        struct {
            MultiProc_Config * config;
        } getConfig;
        /*
         * Technically we do not need this union but left it there for
         * consistency and in case we need to add commands in the future.
         */
    } args;

    Int32 apiStatus;
} MultiProcDrv_CmdArgs;


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* MultiProc_DrvDefs_H_0xf2ba */
