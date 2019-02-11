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
 * \file utils_ipu_ecc.c
 *
 * \brief  This file has the implementation for utility function for using
 *         IPU ECC on TDA3x
 *
 * \version 0.0 (Feb 2016) : [CSG] First version
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
#include "utils_common/include/utils_ipu_ecc.h"
#include <ti/csl/arch/csl_arch.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define IPU_L1TAG_SEC_ERR_INT             (80U)
#define IPU_L1TAG_DED_ERR_INT             (81U)
#define IPU_L1DATA_SEC_ERR_INT            (82U)
#define IPU_L1DATA_DED_ERR_INT            (83U)
#define IPU_L2RAM_SEC_ERR_INT             (84U)
#define IPU_L2RAM_DED_ERR_INT             (85U)

#define IPU_ECC_IRQ_NUM                   (6U)

static Void Utils_ipuEccISR(UArg ctx);

/*******************************************************************************
 *  Global variables
 *******************************************************************************
 */
/**
 * \brief Interrupt lines used on IPU1_C0/IPU1_C1
 */
const UInt32 gIpuEccErrIntrId[IPU_ECC_IRQ_NUM] =
{
    IPU_L1TAG_SEC_ERR_INT,
    IPU_L1TAG_DED_ERR_INT,
    IPU_L1DATA_SEC_ERR_INT,
    IPU_L1DATA_DED_ERR_INT,
    IPU_L2RAM_SEC_ERR_INT,
    IPU_L2RAM_DED_ERR_INT
};

static BspOsal_IntrHandle gIpuEccErrHwiHandle[IPU_ECC_IRQ_NUM] = {NULL};

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

static Void Utils_ipuEccISR(UArg ctx)
{
    UInt32 errId = (UInt32)ctx;
    UInt32 errStat, errType, errAddr = 0U;

    Vps_printf(" UTILS: IPU ECC: Error interrupt received !!!");

    switch (errId)
    {
        case IPU_L1TAG_SEC_ERR_INT:
            Vps_printf(" UTILS: IPU ECC: L1TAG SEC Interrupt received !!!");
            errType = ECC_IPU_MEM_TYPE_L1TAG;
            break;
        case IPU_L1TAG_DED_ERR_INT:
            Vps_printf(" UTILS: IPU ECC: L1TAG DED Interrupt received !!!");
            errType = ECC_IPU_MEM_TYPE_L1TAG;
            break;
        case IPU_L1DATA_SEC_ERR_INT:
            Vps_printf(" UTILS: IPU ECC: L1D SEC Interrupt received !!!");
            errType = ECC_IPU_MEM_TYPE_L1DATA;
            break;
        case IPU_L1DATA_DED_ERR_INT:
            Vps_printf(" UTILS: IPU ECC: L1D DED Interrupt received !!!");
            errType = ECC_IPU_MEM_TYPE_L1DATA;
            break;
        case IPU_L2RAM_SEC_ERR_INT:
            Vps_printf(" UTILS: IPU ECC: L2RAM SEC Interrupt received !!!");
            errType = ECC_IPU_MEM_TYPE_L2RAM;
            break;
        case IPU_L2RAM_DED_ERR_INT:
            Vps_printf(" UTILS: IPU ECC: L2RAM DED Interrupt received !!!");
            errType = ECC_IPU_MEM_TYPE_L2RAM;
            break;
        default:
            Vps_printf(" UTILS: IPU ECC: Invalid Interrupt received !!!");
            errType = ECC_IPU_MEM_TYPE_L2RAM;
            break;
    }

    errStat =
        ECCIPUMemGetErrStatus(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE, errType);
    ECCIPUMemGetErrInfo(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                        &errAddr,
                        errType);
    Vps_printf(" UTILS: IPU ECC: Error location: 0x%08x !!!", errAddr);

    ECCIPUMemClrErrStatus(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                          errStat,
                          errType);
}

/*
 * \brief Setup IPU ECC error handlers
 *
 * \param  None
 *
 * \return None
 */
void Utils_ipuEccInit(Void)
{
    UInt32 i;
    for(i = 0U; i < IPU_ECC_IRQ_NUM; i++)
    {
        if(NULL == gIpuEccErrHwiHandle[i])
        {
            /* MISRA.CAST.Func.Ptr
            * MISRAC_2004_Rule_11.1
            * MISRAC_WAIVER:
            * Casting it to BspOsal_IntrFuncPtr as required by the OSAL API
            */
            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004 Rule_11.3
             * MISRAC_WAIVER:
             * Passing pointer arguments to ISR and callback functions which 
             * takes arguments as UInt32 for legacy reasons and vice-versa.
             */
            gIpuEccErrHwiHandle[i] =
                BspOsal_registerIntr(gIpuEccErrIntrId[i],
                                    (BspOsal_IntrFuncPtr) &Utils_ipuEccISR,
                                    (Void *)gIpuEccErrIntrId[i]);
        }
    }
}

/*
 * \brief Unregister IPU ECC error handlers
 *
 * \param  None
 *
 * \return None
 */
void Utils_ipuEccDeInit(Void)
{
    UInt32 i;
    for(i = 0U; i < IPU_ECC_IRQ_NUM; i++)
    {
        if(NULL != gIpuEccErrHwiHandle)
        {
            BspOsal_unRegisterIntr(&gIpuEccErrHwiHandle[i]);
            gIpuEccErrHwiHandle[i] = NULL;
        }
    }
}
