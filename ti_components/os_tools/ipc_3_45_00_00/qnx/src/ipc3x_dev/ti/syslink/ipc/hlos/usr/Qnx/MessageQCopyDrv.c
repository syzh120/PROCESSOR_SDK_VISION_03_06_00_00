/*
 *  @file   MessageQCopyDrv.c
 *
 *  @brief      User-side OS-specific implementation of MessageQCopy driver for Qnx
 *
 *
 *  @ver        02.00.00.53_alpha2
 *
 *  ============================================================================
 *
 *  Copyright (c) 2011-2015, Texas Instruments Incorporated
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


/* Linux specific header files */
#include <signal.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>
#include <MessageQCopyDrv.h>

/* Module headers */
#include <MessageQCopyDrvDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/** ============================================================================
 *  Macros and types
 *  ============================================================================
 */
/*!
 *  @brief  Driver name for MessageQCopy.
 */
#define MESSAGEQCOPY_DRIVER_NAME         "/dev/ipc"


/** ============================================================================
 *  Globals
 *  ============================================================================
 */
/*!
 *  @brief  Driver handle for MessageQCopy in this process.
 */
static Int32 MessageQCopyDrv_handle = -1;

/*!
 *  @brief  Reference count for the driver handle.
 */
static UInt32 MessageQCopyDrv_refCount = 0;

/*!
 *  @brief  Indicates whether MessageQCopyDrv has been setup in this process.
 */
static UInt32 MessageQCopyDrv_setup = 0;


/** ============================================================================
 *  Functions
 *  ============================================================================
 */
/*!
 *  @brief  Function to open the MessageQCopy driver.
 *
 *  @param  None.
 *
 *  @sa     MessageQCopyDrv_close
 */
Int
MessageQCopyDrv_open (Void)
{
    Int    status   = MessageQCopy_S_SUCCESS;
    int    osStatus = 0;

    GT_0trace (curTrace, GT_ENTER, "MessageQCopyDrv_open");

    if (MessageQCopyDrv_refCount == 0) {
        /* TBD: Protection for refCount. */
        MessageQCopyDrv_refCount++;

        MessageQCopyDrv_handle = open (MESSAGEQCOPY_DRIVER_NAME, O_SYNC | O_RDWR);
        if (MessageQCopyDrv_handle < 0) {
            perror ("MessageQCopy driver open: " MESSAGEQCOPY_DRIVER_NAME);
            /*! @retval MessageQCopy_E_OSFAILURE Failed to open MessageQCopy
                        driver with OS */
            status = MessageQCopy_E_OSFAILURE;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopyDrv_open",
                                 status,
                                 "Failed to open MessageQCopy driver with OS!");
        }
        else {
            osStatus = fcntl (MessageQCopyDrv_handle, F_SETFD, FD_CLOEXEC);
            if (osStatus != 0) {
                /*! @retval MessaegQCopy_E_OSFAILURE Failed to set file descriptor
                                                flags */
                status = MessageQCopy_E_OSFAILURE;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "MessageQCopyDrv_open",
                                     status,
                                     "Failed to set file descriptor flags!");
            }
        }
    }
    else {
        if (MessageQCopyDrv_setup != getpid ()) {
            /* Indicates that this is a forked process - Ang - need to check this? */
            MessageQCopyDrv_setup = getpid ();
        }
        else {
            /* TBD: Protection for refCount. */
            MessageQCopyDrv_refCount++;
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopyDrv_open", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successfully completed. */
    return status;
}


/*!
 *  @brief  Function to close the MessageQCopy driver.
 *
 *  @param  None.
 *
 *  @sa     MessageQCopyDrv_open
 */
Int
MessageQCopyDrv_close (Void)
{
    Int    status      = MessageQCopy_S_SUCCESS;
    int    osStatus    = 0;

    GT_0trace (curTrace, GT_ENTER, "MessageQCopyDrv_close");
    /* TBD: Protection for refCount. */
    if (MessageQCopyDrv_refCount == 1) {
        MessageQCopyDrv_refCount--;

        osStatus = close (MessageQCopyDrv_handle);
        if (osStatus != 0) {
            perror ("MessageQCopy driver close: " MESSAGEQCOPY_DRIVER_NAME);
            /*! @retval MessageQCopy_E_OSFAILURE Failed to open MessageQCopy
                                            driver with OS */
            status = MessageQCopy_E_OSFAILURE;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopyDrv_close",
                                 status,
                                 "Failed to close MessageQCopy driver with OS!");
        }
        else {
            MessageQCopyDrv_handle = -1;
        }
    }
    else {
        MessageQCopyDrv_refCount--;
    }

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopyDrv_close", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successfully completed. */
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
MessageQCopyDrv_ioctl (UInt32 cmd, Ptr args)
{
    Int status      = MessageQCopy_S_SUCCESS;
    int osStatus    = 0;

    GT_2trace (curTrace, GT_ENTER, "MessageQCopyDrv_ioctl", cmd, args);

    GT_assert (curTrace, (MessageQCopyDrv_refCount > 0));

    osStatus = ioctl (MessageQCopyDrv_handle, cmd, args);
    if (osStatus < 0) {
        /*! @retval MessageQCopy_E_OSFAILURE Driver ioctl failed */
        status = MessageQCopy_E_OSFAILURE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopyDrv_ioctl",
                             status,
                             "Driver ioctl failed!");
    }
    else {
        /* First field in the structure is the API status. */
        status = ((MessageQCopyDrv_CmdArgs *) args)->apiStatus;
    }

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopyDrv_ioctl", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successfully completed. */
    return status;
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
