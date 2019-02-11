/*
 *  @file   GateHWSpinlockDrv.c
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

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/inc/GateHWSpinlock.h>
#include <ti/syslink/inc/GateHWSpinlockDrvDefs.h>
#include <ti/syslink/build/Qnx/resmgr/dcmd_syslink.h>

/* QNX specific header files */
#include <sys/types.h>
#include <unistd.h>

/** ============================================================================
 *  Globals
 *  ============================================================================
 */
/*!
 *  @brief  Driver handle for GateHWSpinlock in this process.
 */
extern Int32 IpcDrv_handle;

/** ============================================================================
 *  Functions
 *  ============================================================================
 */
/*!
 *  @brief  Function to invoke the APIs through ioctl.
 *
 *  @param  cmd     Command for driver ioctl
 *  @param  args    Arguments for the ioctl command
 *
 *  @sa
 */
Int
GateHWSpinlockDrv_ioctl (UInt32 cmd, Ptr args)
{
    Int status      = GateHWSpinlock_S_SUCCESS;
    int osStatus    = -1;

    GT_2trace (curTrace, GT_ENTER, "GateHWSpinlockDrv_ioctl", cmd, args);

    switch (cmd) {
          case CMD_GATEHWSPINLOCK_GETCONFIG:
          {
              GateHWSpinlockDrv_CmdArgs *cargs = (GateHWSpinlockDrv_CmdArgs *)args;
              iov_t getconfig_iov[2];

              SETIOV(&getconfig_iov[0], cargs, sizeof(GateHWSpinlockDrv_CmdArgs));
              SETIOV(&getconfig_iov[1], cargs->args.getConfig.config,
                  sizeof(GateHWSpinlock_Config));
              osStatus = devctlv(IpcDrv_handle, DCMD_GATEHWSPINLOCK_GETCONFIG, 2, 2,
                  getconfig_iov, getconfig_iov, NULL);
          }
          break;

          default:
          {
              /* This does not impact return status of this function, so retVal
               * comment is not used.
               */
              status = GateHWSpinlock_E_INVALIDARG;
              GT_setFailureReason (curTrace,
                                   GT_4CLASS,
                                   "GateHWSpinlockDrv_ioctl",
                                   status,
                                   "Unsupported ioctl command specified");
          }
          break;
      }


    if (osStatus != 0) {
        /*! @retval GateHWSpinlock_E_OSFAILURE Driver ioctl failed */
        status = GateHWSpinlock_E_OSFAILURE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "GateHWSpinlockDrv_ioctl",
                             status,
                             "Driver ioctl failed!");
    }
    else {
        /* First field in the structure is the API status. */
        status = ((GateHWSpinlockDrv_CmdArgs *) args)->apiStatus;
    }

    GT_1trace (curTrace, GT_LEAVE, "GateHWSpinlockDrv_ioctl", status);

    return status;
}
