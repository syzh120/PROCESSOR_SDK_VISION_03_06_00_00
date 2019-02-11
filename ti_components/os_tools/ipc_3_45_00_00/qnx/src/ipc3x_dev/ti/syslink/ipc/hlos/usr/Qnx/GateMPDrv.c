/*
 * Copyright (c) 2013-2014 Texas Instruments Incorporated - http://www.ti.com
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== GateMPDrv.c ========
 *
 */

/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>
#include <ti/ipc/GateMP.h>
#include <_MultiProc.h>
#include <ti/syslink/inc/GateMPDrvDefs.h>

#include <ti/syslink/build/Qnx/resmgr/dcmd_syslink.h>

/** ============================================================================
 *  Globals
 *  ============================================================================
 */

extern Int32 IpcDrv_handle;


/** ============================================================================
 *  Functions
 *  ============================================================================
 */
/*!
 *  @brief  Function to open the GateMP driver.
 *
 *  @sa     GateMPDrv_close
 */
Int GateMPDrv_open (Void)
{
    Int status      = GateMP_S_SUCCESS;

    return status;
}


/*!
 *  @brief  Function to close the GateMP driver.
 *
 *  @sa     GateMPDrv_open
 */
Int GateMPDrv_close (Void)
{
    Int status      = GateMP_S_SUCCESS;

    return status;
}


/*!
 *  @brief  Function to invoke the APIs through ioctl.
 *
 *  @param  cmd     Command for driver ioctl
 *  @param  args    Arguments for the ioctl command
 *
 *  @sa
 */
Int GateMPDrv_ioctl(UInt32 cmd, Ptr args)
{
    Int                     status = GateMP_S_SUCCESS;
    Int                     osStatus = 0;
    GateMPDrv_CmdArgs * cargs = (GateMPDrv_CmdArgs *)args;

    GT_2trace (curTrace, GT_ENTER, "GateMPDrv_ioctl", cmd, args);

    switch (cmd) {

      case CMD_GATEMP_GETFREERES:
      {
          osStatus = devctl(IpcDrv_handle, DCMD_GATEMP_GETFREERES, cargs,
              sizeof(GateMPDrv_CmdArgs), NULL);

          if (osStatus != 0) {
              status = GateMP_E_OSFAILURE;
          }
      }
      break;

      case CMD_GATEMP_RELRES:
      {
          osStatus = devctl(IpcDrv_handle, DCMD_GATEMP_RELRES, cargs,
              sizeof(GateMPDrv_CmdArgs), NULL);

          if (osStatus != 0) {
              status = GateMP_E_OSFAILURE;
          }
      }
      break;

      case CMD_GATEMP_GETNUMRES:
      {
          osStatus = devctl(IpcDrv_handle, DCMD_GATEMP_GETNUMRES, cargs,
              sizeof(GateMPDrv_CmdArgs), NULL);

          if (osStatus != 0) {
              status = GateMP_E_OSFAILURE;
          }
      }
      break;

      case CMD_GATEMP_START:
      {
          osStatus = devctl(IpcDrv_handle, DCMD_GATEMP_START, cargs,
              sizeof(GateMPDrv_CmdArgs), NULL);

          if (osStatus != 0) {
              status = GateMP_E_OSFAILURE;
          }
      }
      break;

      case CMD_GATEMP_STOP:
      {
          osStatus = devctl(IpcDrv_handle, DCMD_GATEMP_STOP, cargs,
              sizeof(GateMPDrv_CmdArgs), NULL);

          if (osStatus != 0) {
              status = GateMP_E_OSFAILURE;
          }
      }
      break;

      case CMD_GATEMP_ISSETUP:
      {
          osStatus = devctl(IpcDrv_handle, DCMD_GATEMP_ISSETUP, cargs,
              sizeof(GateMPDrv_CmdArgs), NULL);

          if (osStatus != 0) {
              status = GateMP_E_OSFAILURE;
          }
      }
      break;

      default:
      {
          status = GateMP_E_INVALIDARG;
          GT_setFailureReason (curTrace,
                               GT_4CLASS,
                               "GateMPDrv_ioctl",
                               status,
                               "Unsupported ioctl command specified");
      }
      break;
    }

    if (status == GateMP_S_SUCCESS) {
        status = cargs->apiStatus;
    }

    GT_1trace(curTrace, GT_LEAVE, "GateMPDrv_ioctl", status);

    return (status);
}
