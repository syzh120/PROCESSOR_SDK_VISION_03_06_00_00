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

/**
 *  @file       ti/ipc/mm/MmServiceMgr.h
 *
 *  @brief      Multi-Media Service Manager
 *
 *  @note       MmServiceMgr is currently only available for SYS/BIOS, when
 *              providing services for an MmRpc client on Linux or QNX.
 *
 */

#ifndef ti_ipc_mm_MmServiceMgr__include
#define ti_ipc_mm_MmServiceMgr__include

#include <ti/grcm/RcmServer.h>
#include <ti/ipc/mm/MmType.h>
#include <ti/srvmgr/omaprpc/OmapRpc.h>

#if defined (__cplusplus)
extern "C" {
#endif

/*!
 *  @brief  Operation is successful
 */
#define MmServiceMgr_S_SUCCESS (0)

/*!
 *  @brief  Operation failed
 */
#define MmServiceMgr_E_FAIL (-1)

typedef Void (*MmServiceMgr_DelFxn)(Void);

/*!
 *  @brief      Initialize the MmServiceMgr module
 *
 */
Int MmServiceMgr_init(Void);

/*!
 *  @brief      Finalize the MmServiceMgr module
 *
 */
Void MmServiceMgr_exit(Void);

/*!
 *  @brief      Register a new service
 *
 */
Int MmServiceMgr_register(const String name, RcmServer_Params *params,
        MmType_FxnSigTab *fxnSigTab, MmServiceMgr_DelFxn delFxn);

/*! @cond */
/*!
 *  @brief      Start the service manager listener task
 *
 */
Int MmServiceMgr_start(const String name, Int aryLen,
        OmapRpc_FuncSignature *sigAry);
/*! @endcond */

/*!
 *  @brief      Get the ID of the current service instance
 *              This function can only be called in the context of skeleton
 *              functions or service deletion function registered for
 *              a service.
 *
 */
UInt32 MmServiceMgr_getId();

#if defined (__cplusplus)
}
#endif
#endif /* ti_ipc_mm_MmServiceMgr__include */
