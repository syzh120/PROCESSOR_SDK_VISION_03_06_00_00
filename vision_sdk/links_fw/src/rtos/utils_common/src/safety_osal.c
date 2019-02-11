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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <stdint.h>
#include <xdc/std.h>
#include <ti/drv/vps/include/osal/bsp_safety_osal.h>

#ifdef BUILD_DSP
#include <ti/csl/arch/csl_arch.h>
#include "utils_common/include/utils_l3fw.h"
#include <ti/sysbios/family/c66/Cache.h>
#endif
#if defined(BUILD_ARP32) && defined(ECC_FFI_INCLUDE)
#include <ti/csl/soc.h>
#include <ti/csl/csl_l3fw.h>
#include "utils_common/include/utils_l3fw.h"
#endif

UInt32 BspSafetyOsal_setSafetyMode(UInt32 safetyMode)
{
    UInt32 curSafetyMode;
    curSafetyMode = BspSafetyOsal_getSafetyMode();

#ifdef ECC_FFI_INCLUDE
    /* This check avoids recursion */
    if(curSafetyMode != safetyMode)
    {
#ifdef BUILD_DSP
        if (BSP_SAFETY_OSAL_MODE_ASIL == safetyMode)
        {
            DSP_setCpuMode(DSP_CPU_MODE_SPV);
            Utils_l3FwSwitchSafetyMode(safetyMode);
        }
        if (BSP_SAFETY_OSAL_MODE_QM == safetyMode)
        {
            Utils_l3FwSwitchSafetyMode(safetyMode);
            DSP_setCpuMode(DSP_CPU_MODE_USR);
        }
#endif

#ifdef BUILD_ARP32
        Utils_l3FwSwitchSafetyMode(safetyMode);
#endif
    } /* (curSafetyMode != safetyMode) */
#endif /* ECC_FFI_INCLUDE */

    return curSafetyMode;
}

UInt32 BspSafetyOsal_getSafetyMode(void)
{
    UInt32 safetyMode = 0U;

#ifdef ECC_FFI_INCLUDE

#ifdef BUILD_ARP32
    /* There is no USR/SPV in EVE, utils_l3fw.c will identify current
     * safetyMode based on current values of firewall register
     */
    safetyMode = Utils_l3FwGetSafetyMode();
#endif

#ifdef BUILD_DSP
    UInt32 cpuMode = DSP_getCpuMode();
    if (DSP_CPU_MODE_SPV == cpuMode)
    {
        safetyMode = BSP_SAFETY_OSAL_MODE_ASIL;
    }
    if (DSP_CPU_MODE_USR == cpuMode)
    {
        safetyMode = BSP_SAFETY_OSAL_MODE_QM;
    }
#endif

#endif /* ECC_FFI_INCLUDE */

    return safetyMode;
}
