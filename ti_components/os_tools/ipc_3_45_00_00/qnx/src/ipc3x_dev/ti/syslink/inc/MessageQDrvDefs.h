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
 *  @file       MessageQDrvDefs.h
 *
 *  @brief      Definitions of MessageQDrv types and structures.
 */


#ifndef MESSAGEQ_DRVDEFS_H_0xf653
#define MESSAGEQ_DRVDEFS_H_0xf653

/* Module headers */
#include <ti/ipc/MessageQ.h>
#include "_MessageQ.h"
#include "IpcCmdBase.h"
#include <ti/syslink/inc/IoctlDefs.h>

#if defined (__cplusplus)
extern "C" {
#endif


/*  ----------------------------------------------------------------------------
 *  IOCTL command IDs for MessageQ
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Base command ID for MessageQ
 */
#define MESSAGEQ_BASE_CMD                 0x150

/*!
 *  @brief  Command for MessageQ_getConfig
 */
#define CMD_MESSAGEQ_GETCONFIG              _IOWR(IPCCMDBASE,\
                                            MESSAGEQ_BASE_CMD + 1u,\
                                            MessageQDrv_CmdArgs)
/*!
 *  @brief  Command for MessageQ_setup
 */
#define CMD_MESSAGEQ_SETUP                  _IOWR(IPCCMDBASE,\
                                            MESSAGEQ_BASE_CMD + 2u,\
                                            MessageQDrv_CmdArgs)
/*!
 *  @brief  Command for MessageQ_setup
 */
#define CMD_MESSAGEQ_DESTROY                _IOWR(IPCCMDBASE,\
                                            MESSAGEQ_BASE_CMD + 3u,\
                                            MessageQDrv_CmdArgs)
/*!
 *  @brief  Command for MessageQ_create
 */
#define CMD_MESSAGEQ_CREATE                 _IOWR(IPCCMDBASE,\
                                            MESSAGEQ_BASE_CMD + 4u,\
                                            MessageQDrv_CmdArgs)

/*!
 *  @brief  Command for MessageQ_delete
 */
#define CMD_MESSAGEQ_DELETE                 _IOWR(IPCCMDBASE,\
                                            MESSAGEQ_BASE_CMD + 5u,\
                                            MessageQDrv_CmdArgs)

/*  ----------------------------------------------------------------------------
 *  Command arguments for MessageQ
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Command arguments for MessageQ
 */
typedef struct MessageQDrv_CmdArgs_Tag {
    union {
        struct {
            MessageQ_Config     * config;
        } getConfig;

        struct {
            MessageQ_Config     * config;
            NameServer_Handle     nameServerHandle;
        } setup;

        struct {
            Ptr                   handle;
            String                name;
            MessageQ_Params     * params;
            UInt32                nameLen;
            MessageQ_QueueId      queueId;
        } create;

        struct {
            Ptr                  handle;
        } deleteMessageQ;

    } args;

    Int32 apiStatus;
} MessageQDrv_CmdArgs;


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* MESSAGEQ_DRVDEFS_H_0xf653 */
