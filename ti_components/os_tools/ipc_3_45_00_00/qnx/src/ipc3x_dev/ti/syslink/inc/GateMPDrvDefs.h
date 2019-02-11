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
 *  @file       GateMPDrvDefs.h
 *
 *  @brief      Definitions of GateMPDrv types and structures.
 *
 */


#ifndef GATEMP_DRVDEFS_H
#define GATEMP_DRVDEFS_H


#include <ti/ipc/GateMP.h>
#include <ti/ipc/NameServer.h>

#include "UtilsCmdBase.h"
#include "_GateMP.h"
#include "_MultiProc.h"
#include <ti/syslink/inc/IoctlDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif


/*  ----------------------------------------------------------------------------
 *  IOCTL command IDs for GateMP
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Base command ID for GateMP
 */
#define GATEMP_BASE_CMD                 (0x160)

/*!
 *  @brief  Command for GateMP_getFreeResource
 */
#define CMD_GATEMP_GETFREERES           _IOWR(UTILSCMDBASE,\
                                            GATEMP_BASE_CMD + 1u,\
                                            GateMPDrv_CmdArgs)
/*!
 *  @brief  Command for GateMP_releaseResource
 */
#define CMD_GATEMP_RELRES               _IOWR(UTILSCMDBASE,\
                                            GATEMP_BASE_CMD + 2u,\
                                            GateMPDrv_CmdArgs)
/*!
 *  @brief  Command for GateMP_getNumResource
 */
#define CMD_GATEMP_GETNUMRES            _IOWR(UTILSCMDBASE,\
                                            GATEMP_BASE_CMD + 3u,\
                                            GateMPDrv_CmdArgs)
/*!
 *  @brief  Command for GateMP_start
 */
#define CMD_GATEMP_START                _IOWR(UTILSCMDBASE,\
                                            GATEMP_BASE_CMD + 4u,\
                                            GateMPDrv_CmdArgs)
/*!
 *  @brief  Command for GateMP_stop
 */
#define CMD_GATEMP_STOP                 _IOWR(UTILSCMDBASE,\
                                            GATEMP_BASE_CMD + 5u,\
                                            GateMPDrv_CmdArgs)
/*!
 *  @brief  Command for GateMP_isSetup
 */
#define CMD_GATEMP_ISSETUP              _IOWR(UTILSCMDBASE,\
                                            GATEMP_BASE_CMD + 6u,\
                                            GateMPDrv_CmdArgs)



/*  ----------------------------------------------------------------------------
 *  Command arguments for GateMP
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Command arguments for GateMP
 */
typedef struct GateMPDrv_CmdArgs {
    union {
        struct {
            GateMP_RemoteProtect type;
            Int32                id;
        } getFreeResource;

        struct {
            GateMP_RemoteProtect type;
            Int32                id;
        } releaseResource;

        struct {
            GateMP_RemoteProtect type;
            Int32                value;
        } getNumResources;

        struct {
            NameServer_Handle   nameServerHandle;
        } start;

        struct {
            Bool                 result;
        } isSetup;
    } args;

    Int32 apiStatus;
} GateMPDrv_CmdArgs;


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* GateMP_DrvDefs_H */
