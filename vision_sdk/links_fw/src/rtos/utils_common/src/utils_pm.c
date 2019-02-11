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
 * \file utils_pm.c
 *
 * \brief  APIs from this file are used as util functions in SDK
 *
 * \version 0.0 (Jan 2016) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <stdint.h>
#include <src/rtos/utils_common/include/utils_pm.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmhal.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Util function to return the Module id for corresponding PROC Id.
 *        This function maps the SDK macro for proc id to prcm module id
 *
 * \return Module-Id prcm module id corresponding to the procId.
 *
 *******************************************************************************
 */
UInt32 Utils_pmGetModId(UInt32 ProcId)
{
    pmhalPrcmModuleId_t moduleId;

    switch(ProcId)
    {
        case SYSTEM_PROC_IPU1_0:
                moduleId = PMHAL_PRCM_MOD_IPU1;
             break;
        case SYSTEM_PROC_IPU1_1:
                moduleId = PMHAL_PRCM_MOD_IPU1;
             break;
#ifndef TDA3XX_BUILD /* Cores is not a present in TDA3xx */
        case SYSTEM_PROC_A15_0:
                moduleId = PMHAL_PRCM_MOD_MPU;
             break;
#endif
        case SYSTEM_PROC_DSP1:
                moduleId = PMHAL_PRCM_MOD_DSP1;
             break;
#ifndef TDA2EX_BUILD  /* Cores is not a present in TDA2ex */
        case SYSTEM_PROC_DSP2:
                moduleId = PMHAL_PRCM_MOD_DSP2;
             break;
        case SYSTEM_PROC_EVE1:
                moduleId = PMHAL_PRCM_MOD_EVE1;
             break;
#ifndef TDA3XX_BUILD  /* Cores is not a present in TDA3xx */
        case SYSTEM_PROC_EVE2:
                moduleId = PMHAL_PRCM_MOD_EVE2;
            break;
#ifndef TDA2PX_BUILD  /* Cores is not a present in TDA2Px */
        case SYSTEM_PROC_EVE3:
                moduleId = PMHAL_PRCM_MOD_EVE3;
            break;
        case SYSTEM_PROC_EVE4:
                moduleId = PMHAL_PRCM_MOD_EVE4;
            break;
#endif
#endif
#endif
#ifndef TDA3XX_BUILD /* Cores is not a present in TDA3xx */
        case SYSTEM_PROC_IPU2:
                moduleId = PMHAL_PRCM_MOD_IPU2;
            break;
#endif
        default:
                moduleId = PMHAL_PRCM_MOD_UNDEF;
             break;
    }
    return (UInt32)moduleId;
}

/* Nothing beyond this point */
