/*
 *  Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/*
 * \file dsp_ecc.c
 *
 * \brief  This file contains ECC configurations of DSP Internal memory(L1P& L2)
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t ECCDspL2CfgPrm_init(eccDspL2CfgPrm_t *eccDspL2Param)
{
    int32_t retVal = STW_SOK;
    if (NULL == eccDspL2Param)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* By default the L2 is configured to be able to perform EDC on
         * all L1D Cache, RAM, L1P Cache, RAM and SDMA accesses.
         */
        eccDspL2Param->l1DCacheReadEccEn = ECC_ENABLE;
        eccDspL2Param->l1PCacheReadEccEn = ECC_ENABLE;
        eccDspL2Param->l1DRamReadEccEn   = ECC_ENABLE;
        eccDspL2Param->l1PRamReadEccEn   = ECC_ENABLE;
        eccDspL2Param->sdmaReadEccEn     = ECC_ENABLE;
    }
    return retVal;
}

int32_t ECCDspL2Configure(const eccDspL2CfgPrm_t *eccDspL2Param)
{
    int32_t retVal = STW_SOK;
    uint32_t regVal = (uint32_t) 0U;

    if (NULL == eccDspL2Param)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Configure the DSP_L2EDCEN register bits based on the input structure
         * Writing 0 makes the feature of EDC disabled for L2.
         */
        regVal =
            ((((uint32_t) (eccDspL2Param->l1DCacheReadEccEn & 0x1U)) <<
              DSP_L2EDCEN_DL2CEN_SHIFT) |
             (((uint32_t) (eccDspL2Param->l1PCacheReadEccEn & 0x1U)) <<
              DSP_L2EDCEN_PL2CEN_SHIFT) |
             (((uint32_t) (eccDspL2Param->l1DRamReadEccEn & 0x1U)) <<
              DSP_L2EDCEN_DL2SEN_SHIFT) |
             (((uint32_t) (eccDspL2Param->l1PRamReadEccEn & 0x1U)) <<
              DSP_L2EDCEN_PL2SEN_SHIFT) |
             (((uint32_t) (eccDspL2Param->sdmaReadEccEn & 0x1U)) <<
              DSP_L2EDCEN_SDMAEN_SHIFT));
        HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCEN, regVal);
    }
    return retVal;
}

int32_t ECCDspEnable(uint32_t memType, uint32_t eccEnable, uint32_t timeout)
{
    int32_t  retVal = STW_SOK;
    uint32_t status;
    uint32_t timeToWait = timeout;
    if (ECC_DSP_MEM_TYPE_L2 == memType)
    {
        switch (eccEnable)
        {
            /* Enable calculating parity for L2 RAM and Cache */
            case ECC_ENABLE:
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD,
                            ((uint32_t) 1U) << DSP_L2EDCMD_EN_SHIFT);
                /* Wait for ECC to be enabled in the status register */
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT,
                                           DSP_L2EDSTAT_EN);
                    timeToWait--;
                } while ((0U == status) && (timeToWait > 0));
                if ((0U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                break;
            /* Disable calculating parity for L2 RAM and Cache */
            case ECC_DISABLE:
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD,
                            ((uint32_t) 1U) << DSP_L2EDCMD_DIS_SHIFT);
                /* Wait for ECC to be disabled in the status register */
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT,
                                           DSP_L2EDSTAT_DIS);
                    timeToWait--;
                } while ((0U == status) && (timeToWait > 0));
                if ((0U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                break;
            default:
                retVal = STW_EFAIL;
                break;
        }
    }
    else if (ECC_DSP_MEM_TYPE_L1P == memType)
    {
        switch (eccEnable)
        {
            /* Enable calculating parity for L1 Program RAM and Cache */
            case ECC_ENABLE:
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1PEDCMD,
                            ((uint32_t) 1U) << DSP_L1PEDCMD_EN_SHIFT);
                /* Wait for ECC to be enabled in the status register */
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDSTAT,
                                           DSP_L1PEDSTAT_EN);
                    timeToWait--;
                } while ((0U == status) && (timeToWait > 0));
                if ((0U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                /* Enable the L1P Tag for J6 Plus */
                #if defined (SOC_TDA2PX)
                HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_EDCINTMSK,
                    DSP_EDCINTMSK_L1PTAG, 1U);
                /* Need to have DSP_L1PEDCMD_NCCLR set when enabling or
                 * disabling */
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1PTEDCMD,
                            (((uint32_t) 1U) << DSP_L1PTEDCMD_NCCLR_SHIFT) |
                            (((uint32_t) 1U) << DSP_L1PTEDCMD_EN_SHIFT));
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1PTEDCMD,
                            (((uint32_t) 1U) << DSP_L1PTEDCMD_EN_SHIFT));
                /* Wait for ECC to be enabled in the status register */
                timeToWait = timeout;
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PTEDSTAT,
                                           DSP_L1PTEDSTAT_EN);
                    timeToWait--;
                } while ((0U == status) && (timeToWait > 0));
                if ((0U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                #endif
                break;
            /* Disable calculating parity for L1 Program RAM and Cache */
            case ECC_DISABLE:
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1PEDCMD,
                    ((uint32_t) 1U) << DSP_L1PEDCMD_DIS_SHIFT);
                /* Wait for ECC to be disabled in the status register */
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDSTAT,
                                           DSP_L1PEDSTAT_DIS);
                    timeToWait--;
                } while ((0U == status) && (timeToWait > 0));
                if ((0U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                /* Disable the L1P Tag for J6 Plus */
                #if defined (SOC_TDA2PX)
                HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_EDCINTMSK,
                    DSP_EDCINTMSK_L1PTAG, 0U);
                /* Need to have DSP_L1PEDCMD_NCCLR set when enabling or
                 * disabling */
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1PTEDCMD,
                            ((uint32_t) 1U) << DSP_L1PTEDCMD_NCCLR_SHIFT);
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1PTEDCMD, 0U);
                /* Wait for ECC to be disabled in the status register */
                timeToWait = timeout;
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PTEDSTAT,
                                           DSP_L1PTEDSTAT_EN);
                    timeToWait--;
                } while ((0U == status) && (timeToWait > 0));
                if ((1U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                #endif
                break;
            default:
                retVal = STW_EFAIL;
                break;
        }
    }
    #if defined (SOC_TDA2PX)
    else if (ECC_DSP_MEM_TYPE_L1D == memType)
    {
        switch (eccEnable)
        {
            /* Enable calculating parity for L1 Data RAM and Cache */
            case ECC_ENABLE:
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_EDCINTMSK,
                            (((uint32_t) 1U) << DSP_EDCINTMSK_L1DDATA_SHIFT) |
                            (((uint32_t) 1U) << DSP_EDCINTMSK_L1DTAG_SHIFT));
                /* Need to have DSP_L1DEDCMD_NCCLRDATA set when enabling or
                 * disabling */
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD,
                            (((uint32_t) 1U) << DSP_L1DEDCMD_NCCLRDATA_SHIFT) |
                            (((uint32_t) 1U) << DSP_L1DEDCMD_ENDATA_SHIFT) |
                            (((uint32_t) 1U) << DSP_L1DEDCMD_ENTAG_SHIFT));
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD,
                            (((uint32_t) 1U) << DSP_L1DEDCMD_ENDATA_SHIFT) |
                            (((uint32_t) 1U) << DSP_L1DEDCMD_ENTAG_SHIFT));

                /* Wait for ECC to be enabled in the status register */
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DDNCSTAT,
                                           DSP_L1DDNCSTAT_EN);
                    timeToWait--;
                } while ((0U == status) && (timeToWait > 0));
                if ((0U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                break;
            /* Disable calculating parity for L1 Data RAM and Cache */
            case ECC_DISABLE:
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_EDCINTMSK, 0U);
                /* Need to have DSP_L1DEDCMD_NCCLRDATA set when enabling or
                 * disabling */
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD,
                           (((uint32_t) 1U) << DSP_L1DEDCMD_NCCLRDATA_SHIFT));
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD, 0U);
                /* Wait for ECC to be disabled in the status register */
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DDNCSTAT,
                                           DSP_L1DDNCSTAT_EN);
                    timeToWait--;
                } while ((1U == status) && (timeToWait > 0));
                if ((1U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                break;
            default:
                retVal = STW_EFAIL;
                break;
        }
    }
    #endif
    else
    {
        retVal = STW_EFAIL;
    }
    return retVal;
}

int32_t ECCDspSuspend(uint32_t memType, uint32_t timeout)
{
    int32_t  retVal     = STW_SOK;
    uint32_t status     = 0U;
    uint32_t timeToWait = timeout;
    if (ECC_DSP_MEM_TYPE_L2 == memType)
    {
        /* Suspend ECC for test purpose to inject errors */
        HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD,
                    ((uint32_t) 1U) << DSP_L2EDCMD_SUSP_SHIFT);
        /* Wait for ECC to be disabled in the status register */
        do
        {
            status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT,
                                   DSP_L2EDSTAT_SUSP);
            timeToWait--;
        } while ((0U == status) && (timeToWait > 0));
        if ((0U == status) && (0U == timeToWait))
        {
            retVal = STW_EFAIL;
        }
    }
    else if (ECC_DSP_MEM_TYPE_L1P == memType)
    {
        /* Suspend ECC for test purpose to inject errors */
        HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1PEDCMD,
                    ((uint32_t) 1U) << DSP_L1PEDCMD_SUSP_SHIFT);
        /* Wait for ECC to be suspended in the status register */
        do
        {
            status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDSTAT,
                                   DSP_L1PEDSTAT_SUSP);
            timeToWait--;
        } while ((0U == status) && (timeToWait > 0));
        if ((0U == status) && (0U == timeToWait))
        {
            retVal = STW_EFAIL;
        }
    }
    #if defined (SOC_TDA2PX)
    else if (ECC_DSP_MEM_TYPE_L1D == memType)
    {
        /* Suspend ECC for test purpose to inject errors */
        HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD,
                            HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD) |
                            (((uint32_t) 1U) << DSP_L1DEDCMD_SUSPDATA_SHIFT) |
                            (((uint32_t) 1U) << DSP_L1DEDCMD_SUSPTAG_SHIFT));
        /* Wait for ECC to be suspended in the status register */
        do
        {
            status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DDNCSTAT,
                                   DSP_L1DDNCSTAT_SUSP);
            timeToWait--;
        } while ((0U == status) && (timeToWait > 0));
        if ((0U == status) && (0U == timeToWait))
        {
            retVal = STW_EFAIL;
        }
    }
    #endif
    else
    {
        retVal = STW_EFAIL;
    }
    return retVal;
}

int32_t ECCDspIntrGetErrStatus(eccDspErrStatus_t *errStatus)
{
    int32_t  retVal   = STW_SOK;
    uint32_t regValL2 = 0U, regValL1 = 0U;
#if defined (SOC_TDA2PX)
    uint32_t regValL3 = 0U, regValL4 = 0U;
    uint32_t regValL5 = 0U, regValL6 = 0U;
    uint32_t regValL7 = 0U, regValL8 = 0U;
    uint32_t regValL9 = 0U;
#endif

    if (NULL == errStatus)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        regValL2 = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT);
        regValL1 = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1PEDSTAT);
    #if defined (SOC_TDA2PX)
        regValL3 = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1DDCSTAT);
        regValL4 = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1DDNCSTAT);
        regValL5 = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1DTCSTAT);
        regValL6 = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1DTNCSTAT);
        regValL7 = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1PTEDSTAT);
        regValL8 = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L2TCSTAT);
        regValL9 = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L2TNCSTAT);
    #endif
        /* Populate the structure fields based on the read register. 1
         * indicates that the error occurred and 0 indicates that the
         * error did not occur.
         */
        errStatus->l1PProgramFetchErr =
            HW_GET_FIELD(regValL1, DSP_L1PEDSTAT_PERR);
        errStatus->l1PDmaAccessErr =
            HW_GET_FIELD(regValL1, DSP_L1PEDSTAT_DMAERR);
        errStatus->l2L1DAccessErr =
            HW_GET_FIELD(regValL2, DSP_L2EDSTAT_DERR);
        errStatus->l2L1PAccessErr =
            HW_GET_FIELD(regValL2, DSP_L2EDSTAT_PERR);
        errStatus->l2DmaAccessErr =
            HW_GET_FIELD(regValL2, DSP_L2EDSTAT_DMAERR);
        errStatus->l2VictimsErr =
            HW_GET_FIELD(regValL2, DSP_L2EDSTAT_VERR);
    #if defined (SOC_TDA2PX)
        errStatus->l1DDataCorrectableError =
            ((HW_GET_FIELD(regValL3, DSP_L1DDCSTAT_CERR1)) |
             (HW_GET_FIELD(regValL3, DSP_L1DDCSTAT_CERR2)));
        errStatus->l1DDataNonCorrectableError =
            ((HW_GET_FIELD(regValL4, DSP_L1DDNCSTAT_CERR1)) |
             (HW_GET_FIELD(regValL4, DSP_L1DDNCSTAT_CERR2)));
        errStatus->l1DTagCorrectableError =
            ((HW_GET_FIELD(regValL5, DSP_L1DTCSTAT_CERR1)) |
             (HW_GET_FIELD(regValL5, DSP_L1DTCSTAT_CERR2)));
        errStatus->l1DTagNonCorrectableError =
            ((HW_GET_FIELD(regValL6, DSP_L1DTNCSTAT_NCERR1)) |
             (HW_GET_FIELD(regValL6, DSP_L1DTNCSTAT_NCERR2)));
        errStatus->l1PTagNonCorrectableError =
            ((HW_GET_FIELD(regValL7, DSP_L1PTEDCMD_NCERR1)) |
             (HW_GET_FIELD(regValL7, DSP_L1PTEDCMD_NCERR2)));
        errStatus->l2TagCorrectableError =
            ((HW_GET_FIELD(regValL8, DSP_L2TCSTAT_CERR1)) |
             (HW_GET_FIELD(regValL8, DSP_L2TCSTAT_CERR2)));
        errStatus->l2TagNonCorrectableError =
            ((HW_GET_FIELD(regValL9, DSP_L2TNCSTAT_NCERR1)) |
             (HW_GET_FIELD(regValL9, DSP_L2TNCSTAT_NCERR2)));
    #endif
    }
    return retVal;
}

int32_t ECCDspIntrClrErrStatus(const eccDspErrStatus_t *errClr)
{
    int32_t retVal = STW_SOK;
    if (NULL == errClr)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Writing 1 clears the bit, writing 0 has no effect */
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDCMD, DSP_L1PEDCMD_PCLR,
                      errClr->l1PProgramFetchErr);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDCMD, DSP_L1PEDCMD_DMACLR,
                      errClr->l1PDmaAccessErr);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD, DSP_L2EDCMD_DCLR,
                      errClr->l2L1DAccessErr);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD, DSP_L2EDCMD_PCLR,
                      errClr->l2L1PAccessErr);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD, DSP_L2EDCMD_DMACLR,
                      errClr->l2DmaAccessErr);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD, DSP_L2EDCMD_VCLR,
                      errClr->l2VictimsErr);
    #if defined (SOC_TDA2PX)
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD, DSP_L1DEDCMD_CCLRDATA,
                      errClr->l1DDataCorrectableError);
        /* Error bits are not self clearing. Clear by writing 0 to them. */
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD, DSP_L1DEDCMD_CCLRDATA,
                      0U);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD, DSP_L1DEDCMD_NCCLRDATA,
                      errClr->l1DDataNonCorrectableError);
        /* Error bits are not self clearing. Clear by writing 0 to them. */
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD, DSP_L1DEDCMD_NCCLRDATA,
                      0U);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD, DSP_L1DEDCMD_CCLRTAG,
                      errClr->l1DTagCorrectableError);
        /* Error bits are not self clearing. Clear by writing 0 to them. */
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD, DSP_L1DEDCMD_CCLRTAG,
                      0U);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD, DSP_L1DEDCMD_NCCLRTAG,
                      errClr->l1DTagNonCorrectableError);
        /* Error bits are not self clearing. Clear by writing 0 to them. */
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DEDCMD, DSP_L1DEDCMD_NCCLRTAG,
                      0U);

        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PTEDCMD, DSP_L1PTEDCMD_NCCLR,
                      errClr->l1PTagNonCorrectableError);
        /* Error bits are not self clearing. Clear by writing 0 to them. */
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PTEDCMD, DSP_L1PTEDCMD_NCCLR,
                      0U);

        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2TEDCMD, DSP_L2TEDCMD_CCLRTAG,
                      errClr->l2TagCorrectableError);
        /* Error bits are not self clearing. Clear by writing 0 to them. */
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PTEDCMD, DSP_L2TEDCMD_CCLRTAG,
                      0U);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2TEDCMD, DSP_L2TEDCMD_NCCLRTAG,
                      errClr->l2TagNonCorrectableError);
        /* Error bits are not self clearing. Clear by writing 0 to them. */
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PTEDCMD, DSP_L2TEDCMD_NCCLRTAG,
                      0U);
    #endif
    }
    return retVal;
}

int32_t ECCDspGetErrInfo(uint32_t memType, eccDspErrInfo_t *eccDspInfo)
{
    int32_t retVal = STW_SOK;
    if (NULL == eccDspInfo)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        if (ECC_DSP_MEM_TYPE_L2 == memType)
        {
            /* Read all the parameters which give further details about the
             * L2 ECC errors.
             * This includes the address, bit position, SEC/DED information,
             * L2 Cache Way number etc.
             */
            eccDspInfo->errAddress =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDADDR,
                              DSP_L2EDADDR_ADDR) << DSP_L2EDADDR_ADDR_SHIFT;
            eccDspInfo->errRamOrCache =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDADDR,
                              DSP_L2EDADDR_RAM);
            eccDspInfo->errL2BitPosition =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT,
                              DSP_L2EDSTAT_BITPOS);
            eccDspInfo->errL2Type =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT,
                              DSP_L2EDSTAT_NERR);
            eccDspInfo->errL2way =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDADDR,
                              DSP_L2EDADDR_L2WAY);
            eccDspInfo->errL2CorrectableCount =
                HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCPEC);
            /* This address is generated as the macro is not defined in the
             * HW header file.
             */
            eccDspInfo->errL2NonCorrectableCount =
                HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCPEC + 0x4U);
        }
        else if (ECC_DSP_MEM_TYPE_L1P == memType)
        {
            eccDspInfo->errAddress =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDADDR,
                              DSP_L1PEDADDR_ADDR) << DSP_L1PEDADDR_ADDR_SHIFT;
            eccDspInfo->errRamOrCache =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDADDR,
                              DSP_L1PEDADDR_RAM);
            /* The following fields do not exist for L1P ECC so populating
             * them with 0 always.
             */
            eccDspInfo->errL2BitPosition         = 0U;
            eccDspInfo->errL2Type                = 0U;
            eccDspInfo->errL2way                 = 0U;
            eccDspInfo->errL2CorrectableCount    = 0U;
            eccDspInfo->errL2NonCorrectableCount = 0U;
        }

        else
        {
            retVal = STW_EFAIL;
        }
    }
    return retVal;
}

#if defined (SOC_TDA2PX)
int32_t ECCDspGetL1DErrInfo(eccDspL1DErrInfo_t *eccDspInfo)
{
    int32_t retVal = STW_SOK;
    uint32_t regVal = 0U;
    if (NULL == eccDspInfo)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        eccDspInfo->dataCErrAddr =
            HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DDEDADDR,
                          DSP_L1DDEDADDR_CADDR);
        regVal = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1DDCSTAT);
        eccDspInfo->dataCErrStat =
            (HW_GET_FIELD(regVal, DSP_L1DDCSTAT_CERR1)) |
            (HW_GET_FIELD(regVal, DSP_L1DDCSTAT_CERR2) << 1U);
        eccDspInfo->dataCErrBitPos =
            HW_GET_FIELD(regVal, DSP_L1DDCSTAT_BITPOS);
        eccDspInfo->dataCErrByte = HW_GET_FIELD(regVal, DSP_L1DDCSTAT_BYTE);
        eccDspInfo->dataCErrBank = HW_GET_FIELD(regVal, DSP_L1DDCSTAT_BANK);

        eccDspInfo->dataNCErrAddr =
            HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DDEDADDR,
                          DSP_L1DDEDADDR_NCADDR);
        regVal = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1DDNCSTAT);
        eccDspInfo->dataNCErrStat =
            (HW_GET_FIELD(regVal, DSP_L1DDNCSTAT_CERR1)) |
            (HW_GET_FIELD(regVal, DSP_L1DDNCSTAT_CERR2) << 1U);
        regVal = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1DDNCSTAT);
        eccDspInfo->dataNCErrByte = HW_GET_FIELD(regVal, DSP_L1DDNCSTAT_BYTE);
        eccDspInfo->dataNCErrBank = HW_GET_FIELD(regVal, DSP_L1DDNCSTAT_BANK);

        eccDspInfo->tagCErrAddr =
            HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DTEDADDR,
                          DSP_L1DTEDADDR_CADDR);
        regVal = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1DTCSTAT);
        eccDspInfo->tagCErrStat =
            (HW_GET_FIELD(regVal, DSP_L1DTCSTAT_CERR1)) |
            (HW_GET_FIELD(regVal, DSP_L1DTCSTAT_CERR2) << 1U);
        regVal = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1DTCSTAT);
        eccDspInfo->tagCErrBitPos = HW_GET_FIELD(regVal, DSP_L1DDCSTAT_BITPOS);
        eccDspInfo->tagCErrChan   = HW_GET_FIELD(regVal, DSP_L1DTCSTAT_CHAN);
        eccDspInfo->tagCErrBank   = HW_GET_FIELD(regVal, DSP_L1DTCSTAT_BANK);

        eccDspInfo->tagNCErrAddr =
            HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1DTEDADDR,
                          DSP_L1DTEDADDR_NCADDR);
        regVal = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1DTNCSTAT);
        eccDspInfo->tagNCErrStat =
            (HW_GET_FIELD(regVal, DSP_L1DTNCSTAT_NCERR1)) |
            (HW_GET_FIELD(regVal, DSP_L1DTNCSTAT_NCERR2) << 1U);
        eccDspInfo->tagNCErrChan = HW_GET_FIELD(regVal, DSP_L1DTNCSTAT_CHAN);
        eccDspInfo->tagNCErrBank = HW_GET_FIELD(regVal, DSP_L1DTNCSTAT_BANK);
    }
    return retVal;
}

int32_t ECCDspGetL2TagErrInfo(eccDspL2TagErrInfo_t *eccDspInfo)
{
    int32_t retVal = STW_SOK;
    uint32_t regVal = 0U;
    if (NULL == eccDspInfo)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        eccDspInfo->tagCErrAddr =
            HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2TEDADDR,
                          DSP_L2TEDADDR_CADDR);
        regVal = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L2TCSTAT);
        eccDspInfo->tagCErrStat =
            (HW_GET_FIELD(regVal, DSP_L2TCSTAT_CERR1)) |
            (HW_GET_FIELD(regVal, DSP_L2TCSTAT_CERR2) << 1U);
        regVal = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L2TCSTAT);
        eccDspInfo->tagCErrBitPos = HW_GET_FIELD(regVal, DSP_L1DDCSTAT_BITPOS);
        eccDspInfo->tagCErrChan   = HW_GET_FIELD(regVal, DSP_L2TCSTAT_CHAN);
        eccDspInfo->tagCErrBank   = HW_GET_FIELD(regVal, DSP_L2TCSTAT_BANK);

        eccDspInfo->tagNCErrAddr =
            HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2TEDADDR,
                          DSP_L2TEDADDR_NCADDR);
        regVal = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L2TNCSTAT);
        eccDspInfo->tagNCErrStat =
            (HW_GET_FIELD(regVal, DSP_L2TNCSTAT_NCERR1)) |
            (HW_GET_FIELD(regVal, DSP_L2TNCSTAT_NCERR2) << 1U);
        eccDspInfo->tagNCErrBank = HW_GET_FIELD(regVal, DSP_L2TNCSTAT_BANK);
    }
    return retVal;
}

int32_t ECCDspGetL1PTagErrInfo(eccDspL1PTagErrInfo_t *eccDspInfo)
{
    int32_t retVal = STW_SOK;
    uint32_t regVal = 0U;
    if (NULL == eccDspInfo)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        eccDspInfo->tagNCErrAddr =
            HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PTEDADDR,
                          DSP_L1PTEDADDR_NCADDR);
        regVal = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1PTEDSTAT);
        eccDspInfo->tagNCErrStat =
            (HW_GET_FIELD(regVal, DSP_L1PTEDSTAT_CERR1)) |
            (HW_GET_FIELD(regVal, DSP_L1PTEDSTAT_CERR2) << 1U);
    }
    return retVal;
}

#endif

