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
 * \file utils_emif_ecc.c
 *
 * \brief  This file has the implementation for utility function for using
 *         EMIF ECC on TDA2x and TDA3x
 *
 * \version 0.0 (Dec 2015) : [CSG] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <xdc/std.h>
#include <string.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/irq_xbar_interrupt_ids.h>
#include <ti/csl/csl_emif.h>
#include "utils_common/include/utils_emif_ecc.h"
#include <ti/sysbios/family/shared/vayu/IntXbar.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define EMIF_ECC_IPU_INTR_ID (40U)
#define EMIF_START_ADDR      (0x80000000U)

/*******************************************************************************
 *  Global variables
 *******************************************************************************
 */

static BspOsal_IntrHandle gEmifErrHwiHandle = NULL;

/*******************************************************************************
 *  Function prototypes
 *******************************************************************************
 */

static Void Utils_emifEccISR(UArg ctx);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

static Void Utils_emifEccISR(UArg ctx)
{
    UInt32           errStat, i;
    emifEccErrInfo_t emifErrInfo;

    errStat = EMIFGetIntrStatus(SOC_EMIF1_CONF_REGS_BASE);
    Vps_printf(" UTILS: ECC: EMIF Error interrupt received !!!");

    if(errStat & EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK)
    {
        Vps_printf(" UTILS: ECC: Unaligned write detected !!!");
    }

    if(errStat & EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK)
    {
        Vps_printf(" UTILS: ECC: Two bit error detected !!!");
        EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                                   EMIF_ERR_ECC_TWOBIT,
                                   &emifErrInfo);
        Vps_printf(" UTILS: ECC: Two bit error location = 0x%x !!!",
                   emifErrInfo.errAddr[0] + EMIF_START_ADDR);
    }

    if(errStat & EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ONEBIT_ECC_ERR_SYS_MASK)
    {
        Vps_printf(" UTILS: ECC: Single bit error detected and corrected !!!");
        EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                                   EMIF_ERR_ECC_ONEBIT,
                                   &emifErrInfo);
        Vps_printf(" UTILS: ECC: One bit error count = %d !!!",
                   emifErrInfo.errCnt);
        for(i = 0U; i < emifErrInfo.numValidErrAddr; i++)
        {
            Vps_printf(" UTILS: ECC: One bit error location = 0x%x !!!",
                       emifErrInfo.errAddr[i] + EMIF_START_ADDR);
        }
    }

    EMIFClearIntrStatus(SOC_EMIF1_CONF_REGS_BASE, errStat);
}

/*
 * \brief Setup EMIF ECC error handlers
 *
 * \param  None
 *
 * \return None
 */
void Utils_emifEccInit(void)
{
    if(NULL == gEmifErrHwiHandle)
    {
        /* MISRA.CAST.Func.Ptr
         * MISRAC_2004_Rule_11.1
         * MISRAC_WAIVER:
         * Casting it to BspOsal_IntrFuncPtr as required by the OSAL API
         */
        /* Enable interrupt in XBAR and register ISR */
        IntXbar_connectIRQ(EMIF_ECC_IPU_INTR_ID, EMIF1_IRQ);
        gEmifErrHwiHandle =
            BspOsal_registerIntr(EMIF_ECC_IPU_INTR_ID,
                                 (BspOsal_IntrFuncPtr) &Utils_emifEccISR,
                                 NULL);
        EMIFEnableIntr(SOC_EMIF1_CONF_REGS_BASE, EMIF_INTR_STATUS_ALL);
    }
}

/*
 * \brief Unregister EMIF ECC error handlers
 *
 * \param  None
 *
 * \return None
 */
void Utils_emifEccDeInit(void)
{
    if(NULL != gEmifErrHwiHandle)
    {
        IntXbar_disconnectIRQ(EMIF_ECC_IPU_INTR_ID);
        /* Disable interrupts and Un-register ISR */
        EMIFDisableIntr(SOC_EMIF1_CONF_REGS_BASE, EMIF_INTR_STATUS_ALL);
        BspOsal_unRegisterIntr(&gEmifErrHwiHandle);
        gEmifErrHwiHandle = NULL;
    }
}
