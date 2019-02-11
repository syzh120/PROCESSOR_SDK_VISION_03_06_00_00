/*
 *  @file   OsalDrv.c
 *
 *  @brief      User-side OS-specific implementation of OsalDrv driver for Linux
 *
 *
 *  @ver        02.00.00.46_alpha1
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


/* Linux specific header files */
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>
#include <TraceDrvDefs.h>
#include <ti/syslink/utils/Memory.h>
#include <OsalDrv.h>
#include <stdint.h>

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/** ============================================================================
 *  Macros and types
 *  ============================================================================
 */
/*!
 *  @brief  Driver name for OsalDrv.
 */


/** ============================================================================
 *  Globals
 *  ============================================================================
 */
/*!
 *  @brief  Driver handle for OsalDrv in this process.
 */
/*static Int32 OsalDrv_handle = -1;*/

/*!
 *  @brief  Reference count for the driver handle.
 */
/*static UInt32 OsalDrv_refCount = 0;*/


/** ============================================================================
 *  Functions
 *  ============================================================================
 */
/*!
 *  @brief  Function to open the OsalDrv driver.
 *
 *  @sa     OsalDrv_close
 */


UInt32
OsalDrv_ioMap (UInt32 addr, UInt32 size)
{
    UInt32 pageSize = getpagesize ();
    UInt32 taddr;
    UInt32 tsize;
    uintptr_t * userAddr = NULL;

    GT_0trace (curTrace, GT_ENTER, "OsalDrv_map");

    taddr = addr;
    tsize = size;
    /* Align the physical address to page boundary */
    tsize = tsize + (taddr % pageSize);
    taddr = taddr - (taddr % pageSize);
    userAddr = (uintptr_t *)mmap_device_io(tsize, taddr);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (userAddr == (uintptr_t *) MAP_FAILED) {
        userAddr = NULL;
        taddr = 0;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalDrv_map",
                             OSALDRV_E_MAP,
                             "Failed to map memory to user space!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        /* Change the user address to reflect the actual user address of
         * memory block mapped. This is done since during mmap memory block
         * was shifted (+-) so that it is aligned to page boundary.
         */
        taddr = (UInt32)userAddr;
        taddr = taddr + (addr % pageSize);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalDrv_map", userAddr);

    /*! @retval NULL Operation was successful. */
    /*! @retval valid-address Operation successfully completed. */
    return taddr;
}


/*!
 *  @brief  Function to unmap a memory region specific to the driver.
 *
 *  @sa     OsalDrv_close,OsalDrv_open,OsalDrv_map
 */
Void
OsalDrv_ioUnmap (UInt32 addr, UInt32 size)
{
    UInt32 pageSize = getpagesize ();
    UInt32 taddr;
    UInt32 tsize;
    UInt32 status;

    GT_0trace (curTrace, GT_ENTER, "OsalDrv_unmap");

    taddr = addr;
    tsize = size;

    /* Get the actual user address and size. Since these are modified at the
     * time of mmaping, to have memory block page boundary aligned.
     */
    tsize = tsize + (taddr % pageSize);
    taddr = taddr - (taddr % pageSize);
    status = munmap_device_io((uintptr_t) taddr, tsize);
    if (status == -1) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalDrv_unmap",
                             OSALDRV_E_MAP,
                             "Failed to unmap memory !");
    }

    GT_0trace (curTrace, GT_LEAVE, "OsalDrv_unmap");
}



#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
