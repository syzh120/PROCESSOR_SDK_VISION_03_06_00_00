/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *
 * \ingroup UTILS_API
 * \defgroup UTILS_VIP_INTERRUPT_API APIs to register VIP interrupt from EVE
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils_vip_interrupt.h
 *
 * \brief  APIs to register VIP interrupt from EVE
 *
 * \version 0.0 (Jul 2014) : [VT] First version
 *
 *
 *******************************************************************************
 */

#ifndef UTILS_VIP_INTERRUPT_PRV_H
#define UTILS_VIP_INTERRUPT_PRV_H

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>
#include <ti/sysbios/family/shared/vayu/IntXbar.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief VIP Interrupt no. for frame and Subframe Completion
 *******************************************************************************
 */
#define UTILS_IRQ_XBAR_VIP1_IRQ_2                   (392U)


/**
 *******************************************************************************
 * \brief EVE Interrupt no. for frame and Subframe Completion
 *******************************************************************************
 */
#define UTILS_IRQ_XBAR_EVE_VIP                      (0U)


/**
 *******************************************************************************
 * \brief All the register locations and mask values for enabling and clearing
 * List complete and subframe interrupts from VIP
 *******************************************************************************
 */

#define UTILS_EVE_VIPTOP_LC_EVENT_ENABLE_ADDR       (0x48970050U)
#define UTILS_EVE_VIPTOP_LC_EVENT_ENABLE_MASK       (0x01U)

#define UTILS_EVE_VPDMA_LC_EVENT_ENABLE_ADDR        (0x4897D0DCU)
#define UTILS_EVE_VPDMA_LC_EVENT_ENABLE_MASK        (0x01U)

#define UTILS_EVE_VIPTOP_SUBFRAME_EVENT_ENABLE_ADDR (0x48970054U)
#define UTILS_EVE_VIPTOP_SUBFRAME_EVENT_ENABLE_MASK (0x80U)

/* Enable interrupts for VIP1_SLICE0_UP_Y (TDA2XX_EVM)  */
#define UTILS_EVE_VPDMA_SUBFRAME_EVENT_ENABLE_ADDR  (0x4897D0D4U)
#define UTILS_EVE_VPDMA_SUBFRAME_EVENT_ENABLE_MASK  (0x110U)


#define UTILS_EVE_VIPTOP_LC_EVENT_CLEAR_ADDR        (0x48970048U)
#define UTILS_EVE_VIPTOP_LC_EVENT_CLEAR_MASK        (0x01U)

#define UTILS_EVE_VPDMA_LC_EVENT_CLEAR_ADDR         (0x4897D0D8U)
#define UTILS_EVE_VPDMA_LC_EVENT_CLEAR_MASK         (0x01U)

#define UTILS_EVE_VIPTOP_SUBFRAME_EVENT_CLEAR_ADDR  (0x4897004CU)
#define UTILS_EVE_VIPTOP_SUBFRAME_EVENT_CLEAR_MASK  (0x80U)

/* Check interrupts for VIP1_SLICE0_UP_Y (TDA2XX_EVM)  */
#define UTILS_EVE_VPDMA_SUBFRAME_EVENT_CLEAR_ADDR   (0x4897D0D0U)
#define UTILS_EVE_VPDMA_SUBFRAME_EVENT_CLEAR_MASK   (0x110U)

#define UTILS_EVE_END_OF_INTERRUPT_ADDR             (0x489700A0U)
#define UTILS_EVE_END_OF_INTERRUPT_MASK             (0x01U)


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
BspOsal_IntrHandle Utils_EVE_RegisterInterrupts_FromVIP(
                UInt xbarSrc, UInt32 intrId, Hwi_FuncPtr iSRfunc, void *pPtr);

void Utils_EVE_UnregisterInterrupts_FromVIP(BspOsal_IntrHandle *hwi);

void Utils_VIP_Interrupt_EndOfInterrupt(void);

Bool Utils_VIP_Interrupt_IsSubframe(void);

void Utils_VIP_Interrupt_ClearSubframe_Interrupts(void);

Bool Utils_VIP_Interrupt_IsFrame(void);

void Utils_VIP_Interrupt_Clearframe_Interrupts(void);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_VIP_INTERRUPT_PRV_H */

/*@}*/
