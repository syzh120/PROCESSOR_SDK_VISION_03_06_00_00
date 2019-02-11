/*
 *  @file   VAYUDspHalBoot.c
 *
 *  @brief      Boot control module.
 *
 *              This module is responsible for handling boot-related hardware-
 *              specific operations.
 *              The implementation is specific to VAYUDSP.
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2013-2015, Texas Instruments Incorporated
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


#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>

/* Module headers */
#include <_ProcDefs.h>
#include <Processor.h>

/* Hardware Abstraction Layer headers */
#include <VAYUDspHal.h>
#include <VAYUDspHalBoot.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Offsets of the DSP BOOT ADDR register
 */
#define CONTROL_IVA2_BOOTADDR_OFFSET  0x190
#define CONTROL_IVA2_BOOTMOD_OFFSET   0x194

/*!
 *  @brief  Register access method.
 */
#define REG(x)              *((volatile UInt32 *) (x))

/* =============================================================================
 * APIs called by VAYUDSPPROC module
 * =============================================================================
 */
/*!
 *  @brief      Function to control boot operations
 *
 *  @param      halObj  Pointer to the HAL object
 *  @param      cmd     Boot command
 *  @param      arg     Arguments specific to the boot command
 *
 *  @sa
 */
Int
VAYUDSP_halBootCtrl (Ptr halObj, Processor_BootCtrlCmd cmd, Ptr args)
{
    Int                  status    = PROCESSOR_SUCCESS;
    VAYUDSP_HalObject * halObject = NULL;

    GT_3trace (curTrace, GT_ENTER, "VAYUDSP_halBootCtrl", halObj, cmd, args);

    GT_assert (curTrace, (halObj != NULL));
    GT_assert (curTrace, (cmd < Processor_BootCtrlCmd_EndValue));

    halObject = (VAYUDSP_HalObject *) halObj;

    switch (cmd) {
        case Processor_BootCtrlCmd_SetEntryPoint:
        {
            /* copy _c_int00 addresses to dsp boot address*/
            REG (halObject->generalCtrlBase) =
                             ((((UInt32) args & 0xFFFFFC00) >> 10) | 0x2000000);
        }
        break ;

        case Processor_BootCtrlCmd_SetBootComplete:
        {
            /* set boot complete bit in boot stat reg */
            //REG (halObject->bootStatBase) |= 0x1;
        }
        break ;

        case Processor_BootCtrlCmd_ResetBootComplete:
        {
            /* Do nothing here for VAYUDSP gem */
        }
        break ;

        default:
        {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSP_halBootCtrl",
                                 status,
                                 "Unsupported boot ctrl cmd specified");
        }
        break ;
    }

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSP_halBootCtrl",status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)
}
#endif
