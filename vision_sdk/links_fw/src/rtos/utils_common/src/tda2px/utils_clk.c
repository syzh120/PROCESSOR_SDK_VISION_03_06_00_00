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
 * \file utils_clk.c
 *
 * \brief Utility functions implementation for gettin DPLL clock settings
 *
 * \version 0.0 (July 2013) : [KC] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/rtos/utils_common/include/utils.h>
#include <ti/drv/pm/pmlib.h>

#define UTILS_SYS_CLK1           (20U*1000U*1000U)

#define CM_CLKSEL_DPLL_OFFSET        (0x0CU)
#define CM_DIV_M2_DPLL_OFFSET        (0x10U)
#define CM_DIV_H22_DPLL_OFFSET       (0x34U)


/**
 *******************************************************************************
 * \brief DPLL clkout info
 *******************************************************************************
 */
typedef struct {

    UInt32 f_dpll;
    /**< DPLL clock output value */

    UInt32 clkout_M2;
    /**< M2 clock output value */

    UInt32 clkoutX2_M2;
    /**< X2_M2 clock output value */

    UInt32 isEnableClkout_M2;
    /**< TRUE, M2 clk out is enabled, else disabled */

} Utils_DpllClkOutInfo;

/**
 *******************************************************************************
 * \brief Function protoypes
 *******************************************************************************
 */

Void Utils_getDpllClkOutInfo(UInt32 base_address, Utils_DpllClkOutInfo *pPrm);
Void Utils_getDpllClkOutInfoA15(UInt32 base_address, Utils_DpllClkOutInfo *pPrm);
Void Utils_getDpllClkOutInfoAbe(UInt32 base_address, Utils_DpllClkOutInfo *pPrm);
UInt32 Utils_getDpllClkOutInfoIpu(void);
UInt32 Utils_getClkHz(Utils_ClkId clkId);

/**
 *******************************************************************************
 * \brief Get DPLL Clock out info
 *******************************************************************************
 */
Void Utils_getDpllClkOutInfo(UInt32 base_address, Utils_DpllClkOutInfo *pPrm)
{
    UInt32 temp = 0x0U, dpll_div_n, dpll_div_m;
    UInt32 dpll_div_m2;

    temp = base_address + CM_CLKSEL_DPLL_OFFSET;
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Defer -> Waiver -> Case by case
     * Memory mapped registers and other hardware features access requires typecasting of pointer to integer.
     * The address space is 32 bit and type casting to integer will not result into any loss because of TI's compiler
     * treatment to integer
     */
    temp = *(volatile UInt32*)temp;
    dpll_div_n = temp & (UInt32)0x7FU;
    dpll_div_m = (temp >> (UInt32)8U) & (UInt32)0x7FFU;
    pPrm->f_dpll = (UInt32)(((UInt32)UTILS_SYS_CLK1/((UInt32)(dpll_div_n+(UInt32)1U)))*dpll_div_m);

    temp = base_address + CM_DIV_M2_DPLL_OFFSET;
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Defer -> Waiver -> Case by case
     * Memory mapped registers and other hardware features access requires typecasting of pointer to integer.
     * The address space is 32 bit and type casting to integer will not result into any loss because of TI's compiler
     * treatment to integer
     */
    temp = *(volatile UInt32*)temp;
    dpll_div_m2 = temp & (UInt32)0xF;
    pPrm->isEnableClkout_M2 = (UInt32)((temp >> (UInt32)9U) & (UInt32)0x1U);

    pPrm->f_dpll = (UInt32)((((UInt32)2U * UTILS_SYS_CLK1) / (dpll_div_n + (UInt32)1U))*dpll_div_m);
    pPrm->clkout_M2 = (UInt32)((pPrm->f_dpll) / (dpll_div_m2 * (UInt32)2U));
    pPrm->clkoutX2_M2 = (UInt32)((pPrm->f_dpll)/(dpll_div_m2));
}

/**
 *******************************************************************************
 * \brief Get DPLL Clock out info for A15 DPLL
 *******************************************************************************
 */
Void Utils_getDpllClkOutInfoA15(UInt32 base_address,
                Utils_DpllClkOutInfo *pPrm)
{
    UInt32 temp = 0x0U,dpll_div_n,dpll_div_m,dpll_div_m2,dcc_en;

    temp = base_address + CM_CLKSEL_DPLL_OFFSET;
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Defer -> Waiver -> Case by case
     * Memory mapped registers and other hardware features access requires typecasting of pointer to integer.
     * The address space is 32 bit and type casting to integer will not result into any loss because of TI's compiler
     * treatment to integer
     */
    temp = *(volatile UInt32*)temp;
    dpll_div_n = temp & (UInt32)0x7FU;
    dpll_div_m = (UInt32)((temp >> (UInt32)8U) & (UInt32)0x7FFU);
    dcc_en = (UInt32)((temp >> (UInt32)22U ) & (UInt32)0x1U);

    temp = base_address + CM_DIV_M2_DPLL_OFFSET;
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Defer -> Waiver -> Case by case
     * Memory mapped registers and other hardware features access requires typecasting of pointer to integer.
     * The address space is 32 bit and type casting to integer will not result into any loss because of TI's compiler
     * treatment to integer
     */
    temp = *(volatile UInt32*)temp;
    dpll_div_m2 = temp & (UInt32)0xFU;
    pPrm->isEnableClkout_M2 = (UInt32)((temp >> (UInt32)9U) & (UInt32)0x1U);

    if(dcc_en == (UInt32)0x1U)
    {
        pPrm->f_dpll = (UInt32)((UTILS_SYS_CLK1 / (dpll_div_n + (UInt32)1U))*dpll_div_m);
        pPrm->clkout_M2 = (UInt32)(pPrm->f_dpll / dpll_div_m2);
    }
    else
    {
        pPrm->f_dpll = (UInt32)((((UInt32)2U * UTILS_SYS_CLK1) / (dpll_div_n + (UInt32)1U))*dpll_div_m);
        pPrm->clkout_M2 = (UInt32)(pPrm->f_dpll / (dpll_div_m2 * (UInt32)2U));
    }
}

/**
 *******************************************************************************
 * \brief Get DPLL Clock out info for ABE DPLL
 *******************************************************************************
 */
Void Utils_getDpllClkOutInfoAbe(UInt32 base_address,
                Utils_DpllClkOutInfo *pPrm)
{
    UInt32 temp = 0x0U,dpll_div_n,dpll_div_m;
    UInt32 dpll_div_m2;

    temp = base_address + CM_CLKSEL_DPLL_OFFSET;
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Defer -> Waiver -> Case by case
     * Memory mapped registers and other hardware features access requires typecasting of pointer to integer.
     * The address space is 32 bit and type casting to integer will not result into any loss because of TI's compiler
     * treatment to integer
     */
    temp = *(volatile UInt32*)temp;
    dpll_div_n = temp & (UInt32)0x7FU;
    dpll_div_m = (temp >> (UInt32)8U) & (UInt32)0x7FFU;
    pPrm->f_dpll = (UInt32)((UTILS_SYS_CLK1 / (dpll_div_n + (UInt32)1U))*dpll_div_m);

    temp = base_address + CM_DIV_M2_DPLL_OFFSET;
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Defer -> Waiver -> Case by case
     * Memory mapped registers and other hardware features access requires typecasting of pointer to integer.
     * The address space is 32 bit and type casting to integer will not result into any loss because of TI's compiler
     * treatment to integer
     */
    temp = *(volatile UInt32*)temp;
    dpll_div_m2 = temp & (UInt32)0xFU;
    pPrm->isEnableClkout_M2 = (UInt32)((temp >> (UInt32)9U) & (UInt32)0x1U);

    pPrm->f_dpll = (UInt32)((((UInt32)2U * UTILS_SYS_CLK1) / (dpll_div_n + (UInt32)1U)) * dpll_div_m);
    pPrm->clkout_M2 = (UInt32)(pPrm->f_dpll / (dpll_div_m2 * (UInt32)2U));
    pPrm->clkoutX2_M2 = (UInt32)(pPrm->f_dpll / dpll_div_m2);
}

/**
 *******************************************************************************
 * \brief Get IPU Clk Hz
 *******************************************************************************
 */
UInt32 Utils_getDpllClkOutInfoIpu(void)
{
    Utils_DpllClkOutInfo coreDpll;
    Utils_DpllClkOutInfo abeDpll;

    UInt32 temp,ipu_clksel,divhs, clkHz;
    UInt32 isEnableClkout_M2;

    clkHz = 0U;

    Utils_getDpllClkOutInfo(CM_CLKMODE_DPLL_CORE, &coreDpll);
    Utils_getDpllClkOutInfoAbe(CM_CLKMODE_DPLL_ABE, &abeDpll);

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Defer -> Waiver -> Case by case
     * Memory mapped registers and other hardware features access requires typecasting of pointer to integer.
     * The address space is 32 bit and type casting to integer will not result into any loss because of TI's compiler
     * treatment to integer
     */
    temp = (UInt32)*(volatile UInt32*)CM_IPU1_IPU1_CLKCTRL;
    ipu_clksel = (UInt32)((temp >> (UInt32)24U) & (UInt32)0x1U);

    if(ipu_clksel == 0)
    {
        if(abeDpll.isEnableClkout_M2)
        {
            clkHz = abeDpll.clkoutX2_M2;
        }
        else
        {
            /* Misra C fix */
        }
    }
    else
    {
        temp = CM_CLKMODE_DPLL_CORE + CM_DIV_H22_DPLL_OFFSET;
        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
         * State: Defer -> Waiver -> Case by case
         * Memory mapped registers and other hardware features access requires typecasting of pointer to integer.
         * The address space is 32 bit and type casting to integer will not result into any loss because of TI's compiler
         * treatment to integer
         */
        temp = *(volatile UInt32*)temp;
        divhs = temp & (UInt32)0x3F;
        isEnableClkout_M2 = (UInt32)((temp >> (UInt32)9U) & (UInt32)0x1U);
        if(isEnableClkout_M2)
        {
            clkHz = (UInt32) (coreDpll.f_dpll / (divhs * (UInt32)2U));
        }
        else
        {
            /* Misra C fix */
        }

    }

    return clkHz;
}

UInt32 Utils_getClkHz(Utils_ClkId clkId)
{
    UInt32 clkHz = 0;
    pmErrCode_t status = PM_FAIL;

    /**
     * \brief Holds the root clock frequencies specific for a given platform
     */
    UInt32 *rootClkFreqList;

    /**
     * \brief Holds the voltage domains information whose rails are shared
     */
    pmlibBoardVdRailShare_t *vdRailShareList;

    rootClkFreqList = PMLIBBoardConfigGetRootClks();
    vdRailShareList = PMLIBBoardConfigGetVdRailShareInfo();
    status = PMLIBClkRateInit(rootClkFreqList,vdRailShareList);

    if (PM_SUCCESS == status)
    {
        switch(clkId)
        {
            case UTILS_CLK_ID_EVE:
                status = PMLIBClkRateGet(PMHAL_PRCM_MOD_EVE1, PMHAL_PRCM_CLK_GENERIC, &clkHz);
                break;
            case UTILS_CLK_ID_DSP:
                status = PMLIBClkRateGet(PMHAL_PRCM_MOD_DSP1, PMHAL_PRCM_CLK_GENERIC, &clkHz);
                break;
            case UTILS_CLK_ID_IPU:
                status = PMLIBClkRateGet(PMHAL_PRCM_MOD_IPU1, PMHAL_PRCM_CLK_GENERIC, &clkHz);
                break;
            case UTILS_CLK_ID_A15:
                status = PMLIBClkRateGet(PMHAL_PRCM_MOD_MPU, PMHAL_PRCM_CLK_GENERIC, &clkHz);
                break;
            default:
                status = PM_FAIL;
                break;
        }
    }
    if (PM_SUCCESS != status)
    {
        clkHz = 0U;
    }


    return clkHz;
}

