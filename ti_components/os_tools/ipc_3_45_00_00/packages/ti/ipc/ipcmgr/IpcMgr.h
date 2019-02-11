/*
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com
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
/**
 *  @file       ti/ipc/ipcmgr/IpcMgr.h
 *
 *  @brief      Ipc Manager
 *
 *  This header file should be included as follows:
 *  @code
 *  #include <ti/ipc/ipcmgr/IpcMgr.h>
 *  @endcode
 */

#ifndef ti_ipc_ipcmgr_IpcMgr__include
#define ti_ipc_ipcmgr_IpcMgr__include

#if defined (__cplusplus)
extern "C" {
#endif

/* =============================================================================
 *  Ipc Module-wide Functions
 * =============================================================================
 */

/*!
 *  @brief      Initialize the RPMessage module
 *
 *  Use for stacks built on RPMessage.
 */
Void IpcMgr_rpmsgStartup(Void);

/*!
 *  @brief      Initialize MessageQ transport stack built over RPMessage
 *
 *  Use for stacks built on MessageQ/TransportRpmsg.
 */
Void IpcMgr_ipcStartup(Void);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ti_ipc_ipcmgr_IpcMgr__include */
