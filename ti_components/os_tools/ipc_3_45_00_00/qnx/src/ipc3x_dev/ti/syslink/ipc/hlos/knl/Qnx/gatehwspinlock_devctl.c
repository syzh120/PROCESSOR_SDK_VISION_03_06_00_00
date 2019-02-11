/*
 *  @file   gatehwspinlock_devctl.c
 *
 *  @brief      OS-specific implementation of GateHWSpinlock driver for Qnx
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2015, Texas Instruments Incorporated
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


/* Standard headers */
#include <ti/syslink/Std.h>

/* QNX specific header include */
#include <ti/syslink/build/Qnx/resmgr/proto.h>
#include <ti/syslink/build/Qnx/resmgr/dcmd_syslink.h>

/* Module specific header files */
#include <ti/syslink/inc/GateHWSpinlock.h>
#include <ti/syslink/inc/GateHWSpinlockDrvDefs.h>

/* Function prototypes */
int ipc_gatehwspinlock_getconfig(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);

/**
 * Handler for devctl() messages for gatehwspinlock module.
 *
 * Handles special devctl() messages that we export for control.
 *
 * \param ctp   Thread's associated context information.
 * \param msg   The actual devctl() message.
 * \param ocb   OCB associated with client's session.
 *
 * \return POSIX errno value.
 *
 * \retval EOK      Success.
 * \retval ENOTSUP  Unsupported devctl().
 */
int ipc_gatehwspinlock_devctl(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    switch (msg->i.dcmd) {
        case DCMD_GATEHWSPINLOCK_GETCONFIG:
            return ipc_gatehwspinlock_getconfig(ctp, msg, ocb);
            break;

        default:
            fprintf(stderr, "Invalid DEVCTL for gatehwspinlock 0x%x \n", msg->i.
                dcmd);
            break;
    }

    return (_RESMGR_PTR(ctp, &msg->o, sizeof(msg->o) +
        sizeof(GateHWSpinlockDrv_CmdArgs)));
}

/**
 * Handler for gatehwspinlock getconfig API.
 *
 * \param ctp   Thread's associated context information.
 * \param msg   The actual devctl() message.
 * \param ocb   OCB associated with client's session.
 *
 * \return POSIX errno value.
 *
 * \retval EOK      Success.
 * \retval ENOTSUP  Unsupported devctl().
 */
int ipc_gatehwspinlock_getconfig(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    GateHWSpinlockDrv_CmdArgs * cargs = (GateHWSpinlockDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    GateHWSpinlock_Config *     config = (GateHWSpinlock_Config *)(cargs+1);

    GateHWSpinlock_getConfig(config);

    cargs->apiStatus = GateHWSpinlock_S_SUCCESS;
    SETIOV(&ctp->iov[0], &msg->o, sizeof(msg->o) +
        sizeof(GateHWSpinlockDrv_CmdArgs));
    SETIOV(&ctp->iov[1], config, sizeof(GateHWSpinlock_Config));

    return _RESMGR_NPARTS(2);
}
