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
 * \file utils_ecc_c66x.c
 *
 * \brief  APIs from this file are used to enable the ECC for C66x.
 *
 * \version 0.0 (Feb 2016) : [RG] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "stdint.h"
#include <ti/csl/hw_types.h>
#include <xdc/std.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/csl/arch/csl_arch.h>
#include <src/rtos/utils_common/include/utils_ecc_c66x.h>
#include <include/link_api/system_trace.h>
#include <ti/sysbios/family/c66/Cache.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define DSP_L1P_ED_INTR_ID (113U)
#define DSP_L2_ED1_INTR_ID (116U)
#define DSP_L2_ED2_INTR_ID (117U)

#define DSP_ECC_TIMEOUT    (1000U)

/*******************************************************************************
 *  Global variables
 *******************************************************************************
 */

/*******************************************************************************
 *  Function prototypes
 *******************************************************************************
 */
static Void Utils_dspL1PEccErrISR(UArg ctx);
static Void Utils_dspL2CorrEccErrISR(UArg ctx);
static Void Utils_dspL2UncorrEccErrISR(UArg ctx);

/**
 *******************************************************************************
 *
 * \brief This function divids DSPL2  into a cache and heap
 *
 *******************************************************************************
 */

static Void Utils_dspL1PEccErrISR(UArg ctx)
{
    eccDspErrStatus_t errStatus = {0U};
    eccDspErrInfo_t   eccDspInfo = {0U};

    ECCDspIntrGetErrStatus(&errStatus);
    ECCDspGetErrInfo(ECC_DSP_MEM_TYPE_L1P, &eccDspInfo);

    if (1U == errStatus.l1PProgramFetchErr)
    {
        if (0U == eccDspInfo.errRamOrCache)
        {
            Vps_printf(" UTILS: ECC: DSP L1P Cache Error interrupt received !!!");
            Vps_printf(" UTILS: ECC: DSP L1P Cache Error address = 0x%x",
                        eccDspInfo.errAddress);
            DSPICFGCacheInvalidateAll(SOC_DSP_ICFG_BASE, DSPICFG_MEM_L1P);
        }
    }

    if (1U == errStatus.l1PDmaAccessErr)
    {
        if (1U == eccDspInfo.errRamOrCache)
        {
            Vps_printf(" UTILS: ECC: DSP L1P RAM Error interrupt received !!!");
            Vps_printf(" UTILS: ECC: DSP L1P RAM Error address = 0x%x",
                        eccDspInfo.errAddress);
        }
    }

    ECCDspIntrClrErrStatus(&errStatus);
}

static Void Utils_dspL2CorrEccErrISR(UArg ctx)
{
    eccDspErrStatus_t errStatus = {0U};
    eccDspErrInfo_t   eccDspInfo = {0U};

    ECCDspIntrGetErrStatus(&errStatus);
    ECCDspGetErrInfo(ECC_DSP_MEM_TYPE_L2, &eccDspInfo);

    if (1U == errStatus.l2L1PAccessErr)
    {
        Vps_printf(" UTILS: ECC: DSP L2 L1P Access Error interrupt received !!!");
        DSPICFGCacheInvalidateAll(SOC_DSP_ICFG_BASE, DSPICFG_MEM_L1P);
    }

    if (1U == errStatus.l2L1DAccessErr)
    {
        Vps_printf(" UTILS: ECC: DSP L2 L1D Access Error interrupt received !!!");
    }

    if (1U == errStatus.l2DmaAccessErr)
    {
        Vps_printf(" UTILS: ECC: DSP L2 DMA Access Error interrupt received !!!");
    }

    if (1U == errStatus.l2VictimsErr)
    {
        Vps_printf(" UTILS: ECC: DSP L2 Victim Error interrupt received !!!");
    }

    Vps_printf(" UTILS: ECC: DSP L2 correctable error address = 0x%x",
                eccDspInfo.errAddress);
    Vps_printf(" UTILS: ECC: DSP L2 correctable error occured @ Ram(1)/Cache(0) = %d",
                eccDspInfo.errRamOrCache);
    Vps_printf(" UTILS: ECC: DSP L2 correctable error bit position = %d",
                eccDspInfo.errL2BitPosition);
    Vps_printf(" UTILS: ECC: DSP L2 correctable error type @ Single Bit(0)/Double Bit(1)/Parity(3) = %d",
                eccDspInfo.errL2Type);
    Vps_printf(" UTILS: ECC: DSP L2 correctable error way = %d",
                eccDspInfo.errL2way);
    Vps_printf(" UTILS: ECC: DSP L2 correctable error count = %d",
                eccDspInfo.errL2CorrectableCount);

    ECCDspIntrClrErrStatus(&errStatus);
}

static Void Utils_dspL2UncorrEccErrISR(UArg ctx)
{
    eccDspErrStatus_t errStatus = {0U};
    eccDspErrInfo_t   eccDspInfo = {0U};

    ECCDspIntrGetErrStatus(&errStatus);
    ECCDspGetErrInfo(ECC_DSP_MEM_TYPE_L2, &eccDspInfo);

    if (1U == errStatus.l2L1PAccessErr)
    {
        Vps_printf(" UTILS: ECC: DSP L2 L1P Access Error interrupt received !!!");
        DSPICFGCacheInvalidateAll(SOC_DSP_ICFG_BASE, DSPICFG_MEM_L1P);
    }

    if (1U == errStatus.l2L1DAccessErr)
    {
        Vps_printf(" UTILS: ECC: DSP L2 L1D Access Error interrupt received !!!");
    }

    if (1U == errStatus.l2DmaAccessErr)
    {
        Vps_printf(" UTILS: ECC: DSP L2 DMA Access Error interrupt received !!!");
    }

    if (1U == errStatus.l2VictimsErr)
    {
        Vps_printf(" UTILS: ECC: DSP L2 Victim Error interrupt received !!!");
    }

    Vps_printf(" UTILS: ECC: DSP L2 uncorrectable error address = 0x%x",
                eccDspInfo.errAddress);
    Vps_printf(" UTILS: ECC: DSP L2 uncorrectable error occured @ Ram(1)/Cache(0) = %d",
                eccDspInfo.errRamOrCache);
    Vps_printf(" UTILS: ECC: DSP L2 uncorrectable error bit position = %d",
                eccDspInfo.errL2BitPosition);
    Vps_printf(" UTILS: ECC: DSP L2 uncorrectable error type @ Single Bit(0)/Double Bit(1)/Parity(3) = %d",
                eccDspInfo.errL2Type);
    Vps_printf(" UTILS: ECC: DSP L2 uncorrectable error way = %d",
                eccDspInfo.errL2way);
    Vps_printf(" UTILS: ECC: DSP L2 uncorrectable error count = %d",
                eccDspInfo.errL2NonCorrectableCount);

    ECCDspIntrClrErrStatus(&errStatus);
}

Void Utils_dspEccEnable(Void)
{
    /* Enable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 DSP_ECC_TIMEOUT);

    /* Disable Cache */
    Cache_disable(Cache_Type_L1P);

    /* Invalidate L1P Cache */
    Cache_invL1pAll();

    /* Enable ECC for L1P */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_ENABLE,
                 DSP_ECC_TIMEOUT);

    /* Enable cache */
    Cache_enable(Cache_Type_L1P);
}

/*
 * \brief Setup DSP ECC error handlers
 *
 * \param  None
 *
 * \return None
 */
Void Utils_dspEccInit(Void)
{
    /* Register ISR */
    /* MISRA.CAST.Func.Ptr
     * MISRAC_2004_Rule_11.1
     * MISRAC_WAIVER:
     * Casting it to EventCombiner_FuncPtr as required by the OSAL API
     */
    EventCombiner_dispatchPlug(
                    DSP_L1P_ED_INTR_ID,
                    (EventCombiner_FuncPtr)(&Utils_dspL1PEccErrISR),
                    NULL,
                    (Bool)TRUE
                    );
    EventCombiner_enableEvent(DSP_L1P_ED_INTR_ID);

    /* MISRA.CAST.Func.Ptr
     * MISRAC_2004_Rule_11.1
     * MISRAC_WAIVER:
     * Casting it to EventCombiner_FuncPtr as required by the OSAL API
     */
    EventCombiner_dispatchPlug(
                    DSP_L2_ED1_INTR_ID,
                    (EventCombiner_FuncPtr)(&Utils_dspL2CorrEccErrISR),
                    NULL,
                    (Bool)TRUE
                    );
    EventCombiner_enableEvent(DSP_L2_ED1_INTR_ID);

    /* MISRA.CAST.Func.Ptr
     * MISRAC_2004_Rule_11.1
     * MISRAC_WAIVER:
     * Casting it to EventCombiner_FuncPtr as required by the OSAL API
     */
    EventCombiner_dispatchPlug(
                    DSP_L2_ED2_INTR_ID,
                    (EventCombiner_FuncPtr)(&Utils_dspL2UncorrEccErrISR),
                    NULL,
                    (Bool)TRUE
                    );
    EventCombiner_enableEvent(DSP_L2_ED2_INTR_ID);
}

/*
 * \brief Unregister DSP ECC error handlers
 *
 * \param  None
 *
 * \return None
 */
Void Utils_dspEccDeInit(Void)
{
    /* Un-register ISR */
    EventCombiner_disableEvent(DSP_L1P_ED_INTR_ID);
    EventCombiner_disableEvent(DSP_L2_ED1_INTR_ID);
    EventCombiner_disableEvent(DSP_L2_ED2_INTR_ID);
}

/* Nothing beyond this point */
