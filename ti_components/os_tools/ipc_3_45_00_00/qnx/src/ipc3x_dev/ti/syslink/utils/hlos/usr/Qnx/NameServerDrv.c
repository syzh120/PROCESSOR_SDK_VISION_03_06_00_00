/*
 *  @file   NameServerDrv.c
 *
 *  @brief      OS-specific implementation of NameServer driver for Qnx
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2015, Texas Instruments Incorporated
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
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */


/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/Gate.h>
#include <ti/ipc/NameServer.h>
#include <_MultiProc.h>
#include <ti/syslink/inc/NameServerDrvDefs.h>

#include <ti/syslink/build/Qnx/resmgr/dcmd_syslink.h>

/* QNX specific header files */
#include <sys/types.h>
#include <sys/ioctl.h>
#include <inttypes.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

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
 *  @brief  Function to open the NameServer driver.
 *
 *  @sa     NameServerDrv_close
 */
Int
NameServerDrv_open (Void)
{
    Int status      = NameServer_S_SUCCESS;

    return status;
}


/*!
 *  @brief  Function to close the NameServer driver.
 *
 *  @sa     NameServerDrv_open
 */
Int
NameServerDrv_close (Void)
{
    Int status      = NameServer_S_SUCCESS;

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
Int
NameServerDrv_ioctl (UInt32 cmd, Ptr args)
{
    Int                     status = NameServer_S_SUCCESS;
    Int                     osStatus = 0;
    NameServerDrv_CmdArgs * cargs = (NameServerDrv_CmdArgs *)args;

    GT_2trace (curTrace, GT_ENTER, "NameServerDrv_ioctl", cmd, args);

    switch (cmd) {

      case CMD_NAMESERVER_ADD:
      {
          iov_t nameserver_add_iov[3];

          SETIOV(&nameserver_add_iov[0], cargs, sizeof(NameServerDrv_CmdArgs));
          SETIOV(&nameserver_add_iov[1], cargs->args.add.name,
              cargs->args.add.nameLen);
          SETIOV( &nameserver_add_iov[2], cargs->args.add.buf,
              cargs->args.add.len);

          osStatus = devctlv(IpcDrv_handle, DCMD_NAMESERVER_ADD, 3, 3,
              nameserver_add_iov, nameserver_add_iov, NULL);

          if ( osStatus != 0 ){
              status = NameServer_E_OSFAILURE;
          }
      }
      break;

      case CMD_NAMESERVER_GET:
      {
          iov_t           nameserver_get_iov[4];
          unsigned char   count = 0;

          SETIOV(&nameserver_get_iov[count], cargs,
              sizeof(NameServerDrv_CmdArgs));
          count++;
          SETIOV( &nameserver_get_iov[count], cargs->args.get.buf,
              cargs->args.get.len);
          count++;
          SETIOV( &nameserver_get_iov[count], cargs->args.get.name,
              cargs->args.get.nameLen);
          count++;

          if (cargs->args.get.procId != NULL) {
              SETIOV(&nameserver_get_iov[count], cargs->args.get.procId,
                  cargs->args.get.procLen);
              count++;
          }

          osStatus = devctlv(IpcDrv_handle, DCMD_NAMESERVER_GET, count,
              2, nameserver_get_iov, nameserver_get_iov, NULL);
          if (osStatus != 0) {
              status = NameServer_E_OSFAILURE;
          }
      }
      break;

      case CMD_NAMESERVER_ADDUINT32:
      {
          iov_t nameserver_add_iov[2];

          SETIOV(&nameserver_add_iov[0], cargs, sizeof(NameServerDrv_CmdArgs));
          SETIOV(&nameserver_add_iov[1], cargs->args.addUInt32.name,
              cargs->args.addUInt32.nameLen );
          osStatus = devctlv(IpcDrv_handle, DCMD_NAMESERVER_ADDUINT32, 2, 2,
              nameserver_add_iov, nameserver_add_iov, NULL);

          if ( osStatus != 0 ){
              status = NameServer_E_OSFAILURE;
          }
      }
      break;

      case CMD_NAMESERVER_GETUINT32:
      {
          iov_t     nameserver_get_iov[3];
          unsigned char   count = 0;

          SETIOV(&nameserver_get_iov[count], cargs,
              sizeof(NameServerDrv_CmdArgs));
          count++;
          SETIOV( &nameserver_get_iov[count], cargs->args.getUInt32.name,
              strlen(cargs->args.getUInt32.name) + 1);
          count++;

          if (cargs->args.getUInt32.procId != NULL) {
              SETIOV(&nameserver_get_iov[count], cargs->args.getUInt32.procId,
                  (sizeof(UInt16) * MultiProc_MAXPROCESSORS));
              count++;
          }

          osStatus = devctlv(IpcDrv_handle, DCMD_NAMESERVER_GETUINT32, count,
              count, nameserver_get_iov, nameserver_get_iov, NULL);
          if (osStatus != 0) {
              status = NameServer_E_OSFAILURE;
          }
      }
      break;

      case CMD_NAMESERVER_REMOVE:
      {
          iov_t nameserver_remove_iov[2];

          SETIOV(&nameserver_remove_iov[0], cargs,
              sizeof(NameServerDrv_CmdArgs));
          SETIOV(&nameserver_remove_iov[1], cargs->args.remove.name,
              cargs->args.remove.nameLen);
          osStatus = devctlv(IpcDrv_handle, DCMD_NAMESERVER_REMOVE, 2, 2,
              nameserver_remove_iov, nameserver_remove_iov, NULL);

          if (osStatus != 0) {
              status = NameServer_E_OSFAILURE;
          }
      }
      break;

      case CMD_NAMESERVER_REMOVEENTRY:
      {
          osStatus = devctl(IpcDrv_handle, DCMD_NAMESERVER_REMOVEENTRY, cargs,
              sizeof(NameServerDrv_CmdArgs), NULL);

          if ( osStatus != 0 ){
              status = NameServer_E_OSFAILURE;
          }
      }
      break;

      case CMD_NAMESERVER_PARAMS_INIT:
      {
          iov_t    nameserver_params_init[2];

          SETIOV(&nameserver_params_init[0], cargs,
              sizeof(NameServerDrv_CmdArgs));
          SETIOV(&nameserver_params_init[1], cargs->args.ParamsInit.params,
              sizeof(NameServer_Params));

          osStatus = devctlv(IpcDrv_handle, DCMD_NAMESERVER_PARAMS_INIT, 2, 2,
              nameserver_params_init, nameserver_params_init, NULL);

          if (osStatus != 0){
              status = NameServer_E_OSFAILURE;
          }
      }
      break;

      case CMD_NAMESERVER_CREATE:
      {
          iov_t    nameserver_create_iov[3];

          SETIOV(&nameserver_create_iov[0], cargs,
              sizeof(NameServerDrv_CmdArgs));
          SETIOV(&nameserver_create_iov[1], cargs->args.create.params,
              sizeof(NameServer_Params));
          SETIOV(&nameserver_create_iov[2], cargs->args.create.name,
              cargs->args.create.nameLen );
          osStatus = devctlv( IpcDrv_handle, DCMD_NAMESERVER_CREATE, 3, 3,
              nameserver_create_iov, nameserver_create_iov, NULL);

          if ( osStatus != 0 ){
              status = NameServer_E_OSFAILURE;
          }
      }
      break;

      case CMD_NAMESERVER_DELETE:
      {
          osStatus = devctl( IpcDrv_handle, DCMD_NAMESERVER_DELETE, cargs,
              sizeof(NameServerDrv_CmdArgs), NULL);

          if ( osStatus != 0 ){
              status = NameServer_E_OSFAILURE;
          }
      }
      break;

      case CMD_NAMESERVER_SETUP:
      {
          osStatus = devctl( IpcDrv_handle, DCMD_NAMESERVER_SETUP, cargs,
              sizeof(NameServerDrv_CmdArgs), NULL);

          if (osStatus != 0) {
              status = NameServer_E_OSFAILURE;
          }
      }
      break;

      case CMD_NAMESERVER_DESTROY:
      {
          osStatus = devctl( IpcDrv_handle, DCMD_NAMESERVER_DESTROY, cargs,
              sizeof(NameServerDrv_CmdArgs), NULL);

          if (osStatus != 0) {
              status = NameServer_E_OSFAILURE;
          }
      }
      break;

      default:
      {
          /* This does not impact return status of this function, so retVal
           * comment is not used.
           */
          status = NameServer_E_INVALIDARG;
          GT_setFailureReason (curTrace,
                               GT_4CLASS,
                               "NameServerDrv_ioctl",
                               status,
                               "Unsupported ioctl command specified");
      }
      break;
    }

    if (status == NameServer_S_SUCCESS) {
        status = cargs->apiStatus;
    }

    GT_1trace(curTrace, GT_LEAVE, "NameServerDrv_ioctl", status);

    return (status);
}
