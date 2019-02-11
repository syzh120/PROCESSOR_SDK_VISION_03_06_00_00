/*
 *  @file   MessageQCopyApp.c
 *
 *  @brief      Sample application for MessageQCopy module
 *
 *
 *  @ver        02.00.00.53_alpha2
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2009, Texas Instruments Incorporated
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
#include <ti/syslink/utils/OsalPrint.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/String.h>

/* Module level headers */
#include <ti/ipc/MessageQCopy.h>
#include <_MessageQCopy.h>

#include "MessageQCopyApp.h"

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

/** ============================================================================

 *  Globals
 *  ============================================================================
 */


/** ============================================================================
 *  Functions
 *  ============================================================================
 */

/*!
 *  @brief  Function to execute the startup for MessageQCopyApp sample application
 *
 *  @sa     MessageQCopyApp_shutdown
 */
Int
MessageQCopyApp_startup (Void)
{
    Int32                status  = 0;

    Osal_printf ("Entered MessageQCopyApp_startup\n");

    status = MessageQCopy_setup (NULL);

    Osal_printf ("Leaving MessageQCopyApp_startup. Status [0x%x]\n", status);

    return (status);
}


/*!
 *  @brief  Function to execute the MessageQCopyApp sample application
 *
 */
Int
MessageQCopyApp_execute (testNo)
{
    Int status = MessageQCopy_S_SUCCESS;

    Osal_printf ("Entered MessageQCopyApp_execute\n");

    status = MessageQCopy_runtest (testNo);

    Osal_printf ("Leaving MessageQCopyApp_execute. Status [0x%x]\n", status);

    return(status);
}


/*!
 *  @brief  Function to execute the shutdown for MessageQCopyApp sample application
 *
 *  @sa     MessageQCopyApp_startup
 */
Int
MessageQCopyApp_shutdown (Void)
{
    Int status = MessageQCopy_S_SUCCESS;

    Osal_printf ("Entered MessageQCopyApp_shutdown\n");

    status = MessageQCopy_destroy();

    Osal_printf ("Leaving MessageQCopyApp_shutdown. Status [0x%x]\n", status);

    return(status);

}
