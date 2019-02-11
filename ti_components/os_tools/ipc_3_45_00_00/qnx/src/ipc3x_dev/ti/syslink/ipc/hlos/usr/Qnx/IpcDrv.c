/*
 *  @file   IpcDrv.c
 *
 *  @brief      OS-specific implementation of Ipc driver for Qnx
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2013, Texas Instruments Incorporated
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
#include <ti/ipc/Ipc.h>
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
 *  Macros and types
 *  ============================================================================
 */
/*!
 *  @brief  Driver name for Ipc.
 */
#define IPC_DRIVER_NAME         "/dev/ipc"


/** ============================================================================
 *  Globals
 *  ============================================================================
 */
/*!
 *  @brief  Driver handle for Ipc in this process.
 */

/*  Making this a global as it will be used as the single device handle
 *  for resMgr
 */
Int32 IpcDrv_handle = 0;

/*!
 *  @brief  Reference count for the driver handle.
 */
static UInt32 IpcDrv_refCount = 0;


/** ============================================================================
 *  Functions
 *  ============================================================================
 */
/*!
 *  @brief  Function to open the Ipc driver.
 *
 *  @sa     IpcDrv_close
 */
Int
IpcDrv_open (Void)
{
    Int status      = Ipc_S_SUCCESS;
    int osStatus    = 0;

    GT_0trace (curTrace, GT_ENTER, "IpcDrv_open");

    if (IpcDrv_refCount == 0) {

        IpcDrv_handle = open (IPC_DRIVER_NAME,
                                       O_SYNC | O_RDWR);
        if (IpcDrv_handle < 0) {
            /*! @retval Ipc_E_OSFAILURE Failed to open Ipc driver with OS
             */
            status = Ipc_E_OSFAILURE;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "IpcDrv_open",
                                 status,
                                 "Failed to open Ipc driver with OS!");
        }
        else {
            osStatus = fcntl (IpcDrv_handle, F_SETFD, FD_CLOEXEC);
            if (osStatus != 0) {
                /*! @retval Ipc_E_OSFAILURE Failed to set file descriptor flags
                 */
                status = Ipc_E_OSFAILURE;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "IpcDrv_open",
                                     status,
                                     "Failed to set file descriptor flags!");
            }
            else {
                /* TBD: Protection for refCount. */
                IpcDrv_refCount++;
            }
        }
    }
    else {
        IpcDrv_refCount++;
    }

    GT_1trace (curTrace, GT_LEAVE, "IpcDrv_open", status);

    return status;
}


/*!
 *  @brief  Function to close the Ipc driver.
 *
 *  @sa     IpcDrv_open
 */
Int
IpcDrv_close (Void)
{
    Int status      = Ipc_S_SUCCESS;
    int osStatus    = 0;

    GT_0trace (curTrace, GT_ENTER, "IpcDrv_close");

    /* TBD: Protection for refCount. */
    IpcDrv_refCount--;
    if (IpcDrv_refCount == 0) {
        osStatus = close (IpcDrv_handle);
        if (osStatus != 0) {
            perror ("Ipc driver close: ");
            /*! @retval Ipc_E_OSFAILURE Failed to open Ipc driver with OS */
            status = Ipc_E_OSFAILURE;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "IpcDrv_close",
                                 status,
                                 "Failed to close Ipc driver with OS!");
        }
        else {
            IpcDrv_handle = 0;
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "IpcDrv_close", status);
    return status;
}