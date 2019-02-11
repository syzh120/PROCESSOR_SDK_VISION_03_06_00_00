/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 *  @file       NameServerDrvDefs.h
 *
 *  @brief      Definitions of NameServerDrv types and structures.
 *
 */


#ifndef NAMESERVER_DRVDEFS_H
#define NAMESERVER_DRVDEFS_H


#include <ti/ipc/NameServer.h>
#include "UtilsCmdBase.h"
#include "_NameServer.h"
#include "_MultiProc.h"
#include <ti/syslink/inc/IoctlDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif


/*  ----------------------------------------------------------------------------
 *  IOCTL command IDs for NameServer
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Base command ID for NameServer
 */
#define NAMESERVER_BASE_CMD                 (0x130)

/*!
 *  @brief  Command for NameServer_setup
 */
#define CMD_NAMESERVER_SETUP                _IOWR(UTILSCMDBASE,\
                                            NAMESERVER_BASE_CMD + 2u,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_setup
 */
#define CMD_NAMESERVER_DESTROY                _IOWR(UTILSCMDBASE,\
                                            NAMESERVER_BASE_CMD + 3u,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_destroy
 */
#define CMD_NAMESERVER_PARAMS_INIT          _IOWR(UTILSCMDBASE,\
                                            NAMESERVER_BASE_CMD + 4u,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_create
 */
#define CMD_NAMESERVER_CREATE                _IOWR(UTILSCMDBASE,\
                                            NAMESERVER_BASE_CMD + 5u,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_delete
 */
#define CMD_NAMESERVER_DELETE                _IOWR(UTILSCMDBASE,\
                                            NAMESERVER_BASE_CMD + 6u,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_addUInt32
 */
#define CMD_NAMESERVER_ADDUINT32                _IOWR(UTILSCMDBASE,\
                                            NAMESERVER_BASE_CMD + 7u,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_remove
 */
#define CMD_NAMESERVER_REMOVE                _IOWR(UTILSCMDBASE,\
                                            NAMESERVER_BASE_CMD + 8u,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_removeEntry
 */
#define CMD_NAMESERVER_REMOVEENTRY          _IOWR(UTILSCMDBASE,\
                                            NAMESERVER_BASE_CMD + 9u,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_getUInt32
 */
#define CMD_NAMESERVER_GETUINT32            _IOWR(UTILSCMDBASE,\
                                            NAMESERVER_BASE_CMD + 10u,\
                                            NameServerDrv_CmdArgs)

/*!
 *  @brief  Command for NameServer_add
 */
#define CMD_NAMESERVER_ADD                  _IOWR(UTILSCMDBASE,\
                                            NAMESERVER_BASE_CMD + 11u,\
                                            NameServerDrv_CmdArgs)

/*!
 *  @brief  Command for NameServer_get
 */
#define CMD_NAMESERVER_GET                  _IOWR(UTILSCMDBASE,\
                                            NAMESERVER_BASE_CMD + 12u,\
                                            NameServerDrv_CmdArgs)

/*  ----------------------------------------------------------------------------
 *  Command arguments for NameServer
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Command arguments for NameServer
 */
typedef struct NameServerDrv_CmdArgs {
    union {
        struct {
            NameServer_Params * params;
        } ParamsInit;

        struct {
            NameServer_Handle   handle;
            String              name;
            UInt32              nameLen;
            NameServer_Params * params;
        } create;

        struct {
            NameServer_Handle   handle;
        } delete;

        struct {
            NameServer_Handle   handle;
            String              name;
            UInt32              nameLen;
            Ptr                 buf;
            UInt32              len;
            Ptr                 entry;
        } add;

        struct {
            NameServer_Handle   handle;
            String              name;
            UInt32              nameLen;
            Ptr                 buf;
            UInt32              len;
            UInt16 *            procId;
            UInt32              procLen;
        } get;

        struct {
            NameServer_Handle   handle;
            String              name;
            UInt32              nameLen;
            UInt32              value;
            Ptr                 entry;
        } addUInt32;

        struct {
            NameServer_Handle   handle;
            String              name;
            UInt32              value;
            UInt16              procId[MultiProc_MAXPROCESSORS];
        } getUInt32;

        struct {
            NameServer_Handle   handle;
            String              name;
            UInt32              nameLen;
        } remove;

        struct {
            NameServer_Handle   handle;
            Ptr                 entry;
        } removeEntry;
    } args;

    Int32 apiStatus;
} NameServerDrv_CmdArgs;


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* NameServer_DrvDefs_H */
