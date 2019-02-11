/*
 *  @file   TraceDrv.c
 *
 *  @brief      OS-specific implementation of Trace driver for Linux
 *
 *
 *  @ver        02.00.00.53_alpha2
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


/*  Defined to include MACROS EXPORT_SYMBOL. This must be done before including
 *  module.h
 */
#if !defined (EXPORT_SYMTAB)
#define EXPORT_SYMTAB
#endif

/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>

/*QNX specific header include */
//#include <proto.h>
#include <errno.h>
#include <unistd.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <devctl.h>

/* Module specific header files */
#include <TraceDrv.h>
#include <TraceDrvDefs.h>

/** ============================================================================
 *  Export kernel utils functions
 *  ============================================================================
 */


#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/** ============================================================================
 *  Macros and types
 *  ============================================================================
 */


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
Void
TraceDrv_ioctl (UInt32 cmd, Ptr args)
{
#if defined (IPC_TRACE_ENABLE)
    TraceDrv_CmdArgs * cmdArgs = (TraceDrv_CmdArgs *) args;
#endif /* if defined (IPC_TRACE_ENABLE) */

    GT_2trace (curTrace, GT_ENTER, "TraceDrv_ioctl", cmd, args);

#if defined (IPC_TRACE_ENABLE)
    if (cmd == CMD_TRACEDRV_SETTRACE) {
        if (cmdArgs->args.setTrace.type == GT_TraceType_Kernel) {
            cmdArgs->args.setTrace.oldMask = curTrace;
            curTrace = cmdArgs->args.setTrace.mask;
        }
    }
#endif /* if defined (IPC_TRACE_ENABLE) */

    GT_0trace (curTrace, GT_LEAVE, "TraceDrv_ioctl");
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
