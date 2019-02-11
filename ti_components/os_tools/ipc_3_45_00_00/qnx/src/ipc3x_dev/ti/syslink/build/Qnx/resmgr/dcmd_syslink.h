/*
 * Copyright (c) 2013-2015, Texas Instruments Incorporated
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
 *  @file       dcmd_syslink.h
 *
 *  @brief      DCMD definitions for ipc device
 *
 *  @ver        0001
 */
#ifndef DCMD_SYSLINK_H
#define DCMD_SYSLINK_H

#include <devctl.h>

#if defined (__cplusplus)
extern "C" {
#endif

#define _DCMD_IPC   _DCMD_MISC

typedef enum {
    _DCMD_IPC_NAMESERVER = 0x2A,
    _DCMD_IPC_MESSAGEQ,
    _DCMD_IPC_MULTIPROC,
    _DCMD_IPC_GATEMP,
    _DCMD_IPC_GATEHWSPINLOCK
} dcmd_class_t_val;

/*  ----------------------------------------------------------------------------
 *  DEVCTL command IDs for Nameserver
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Command for NameServer_setup
 */
#define DCMD_NAMESERVER_SETUP               __DIOTF(_DCMD_IPC_NAMESERVER,\
                                            2,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_setup
 */
#define DCMD_NAMESERVER_DESTROY             __DIOTF(_DCMD_IPC_NAMESERVER,\
                                            3,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_destroy
 */
#define DCMD_NAMESERVER_PARAMS_INIT         __DIOTF(_DCMD_IPC_NAMESERVER,\
                                            4,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_create
 */
#define DCMD_NAMESERVER_CREATE              __DIOTF(_DCMD_IPC_NAMESERVER,\
                                            5,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_delete
 */
#define DCMD_NAMESERVER_DELETE              __DIOTF(_DCMD_IPC_NAMESERVER,\
                                            6,\
                                            NameServerDrv_CmdArgs)

/*!
 *  @brief  Command for NameServer_addUInt32
 */
#define DCMD_NAMESERVER_ADDUINT32           __DIOTF(_DCMD_IPC_NAMESERVER,\
                                            7,\
                                            NameServerDrv_CmdArgs)

/*!
 *  @brief  Command for NameServer_remove
 */
#define DCMD_NAMESERVER_REMOVE              __DIOTF(_DCMD_IPC_NAMESERVER,\
                                            8,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_removeEntry
 */
#define DCMD_NAMESERVER_REMOVEENTRY         __DIOTF(_DCMD_IPC_NAMESERVER,\
                                            9,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_getUInt32
 */
#define DCMD_NAMESERVER_GETUINT32           __DIOTF(_DCMD_IPC_NAMESERVER,\
                                            10, \
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_add
 */
#define DCMD_NAMESERVER_ADD                 __DIOTF(_DCMD_IPC_NAMESERVER,\
                                            11,\
                                            NameServerDrv_CmdArgs)
/*!
 *  @brief  Command for NameServer_get
 */
#define DCMD_NAMESERVER_GET                 __DIOTF(_DCMD_IPC_NAMESERVER,\
                                            12, \
                                            NameServerDrv_CmdArgs)


/*  ----------------------------------------------------------------------------
*   IOCTL command IDs for MessageQ
*   ----------------------------------------------------------------------------
*/

/*!
 *  @brief  Command for MessageQ_getConfig
*/
#define DCMD_MESSAGEQ_GETCONFIG             __DIOTF(_DCMD_IPC_MESSAGEQ,\
                                            1,\
                                            MessageQDrv_CmdArgs)
/*!
 *  @brief  Command for MessageQ_setup
*/
#define DCMD_MESSAGEQ_SETUP                 __DIOTF(_DCMD_IPC_MESSAGEQ,\
                                            2,\
                                            MessageQDrv_CmdArgs)
/*!
 *  @brief  Command for MessageQ_setup
*/
#define DCMD_MESSAGEQ_DESTROY               __DIOTF(_DCMD_IPC_MESSAGEQ,\
                                            3,\
                                            MessageQDrv_CmdArgs)
/*!
 *  @brief  Command for MessageQ_create
*/
#define DCMD_MESSAGEQ_CREATE                __DIOTF(_DCMD_IPC_MESSAGEQ,\
                                            4,\
                                            MessageQDrv_CmdArgs)
/*!
 *  @brief  Command for MessageQ_delete
*/
#define DCMD_MESSAGEQ_DELETE                __DIOTF(_DCMD_IPC_MESSAGEQ,\
                                            5,\
                                            MessageQDrv_CmdArgs)

/*  ----------------------------------------------------------------------------
*   IOCTL command IDs for MultiProc
*   ----------------------------------------------------------------------------
*/

/*!
 *  @brief  Command for MultiProc_getConfig
*/
#define DCMD_MULTIPROC_GETCONFIG            __DIOTF(_DCMD_IPC_MULTIPROC,\
                                            1,\
                                            MultiProcDrv_CmdArgs)

/*  ----------------------------------------------------------------------------
*   IOCTL command IDs for GateMP
*   ----------------------------------------------------------------------------
*/

/*!
 *  @brief  Command for GateMP_getFreeResource
 */
#define DCMD_GATEMP_GETFREERES              __DIOTF(_DCMD_IPC_GATEMP,\
                                            1,\
                                            GateMPDrv_CmdArgs)

/*!
 *  @brief  Command for GateMP_releaseResource
 */
#define DCMD_GATEMP_RELRES                  __DIOTF(_DCMD_IPC_GATEMP,\
                                            2,\
                                            GateMPDrv_CmdArgs)

/*!
 *  @brief  Command for GateMP_getNumResources
 */
#define DCMD_GATEMP_GETNUMRES               __DIOTF(_DCMD_IPC_GATEMP,\
                                            3,\
                                            GateMPDrv_CmdArgs)

/*!
 *  @brief  Command for GateMP_start
 */
#define DCMD_GATEMP_START                   __DIOTF(_DCMD_IPC_GATEMP,\
                                            4,\
                                            GateMPDrv_CmdArgs)

/*!
 *  @brief  Command for GateMP_stop
 */
#define DCMD_GATEMP_STOP                    __DIOTF(_DCMD_IPC_GATEMP,\
                                            5,\
                                            GateMPDrv_CmdArgs)

/*!
 *  @brief  Command for GateMP_isSetup
 */
#define DCMD_GATEMP_ISSETUP                 __DIOTF(_DCMD_IPC_GATEMP,\
                                            6,\
                                            GateMPDrv_CmdArgs)

/*  ----------------------------------------------------------------------------
*   IOCTL command IDs for GateHWSpinlock
*   ----------------------------------------------------------------------------
*/

/*!
 *  @brief  Command for GateHWSpinlock_getConfig
*/
#define DCMD_GATEHWSPINLOCK_GETCONFIG       __DIOTF(_DCMD_IPC_GATEHWSPINLOCK,\
                                            1,\
                                            GateHWSpinlockDrv_CmdArgs)

#if defined (__cplusplus)
}
#endif

#endif
