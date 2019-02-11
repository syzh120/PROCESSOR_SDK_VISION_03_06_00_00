/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 */

/**
 *  \file isshal_h3a.c
 *
 *  \brief File containing the ISS H3A HAL init, deinit and other common
 *  functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/csl/cslr_iss.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_iss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issh3a.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct isshalh3aInstObj
{
    uint32_t isInitDone;
    /**< Flag to indicate whether init is done or not */
    uint32_t instId;
    /**< Id of the instance */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t openCnt;
    /**< Open count */
} isshalh3aInstObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t H3aCheckPaxelWinConfig(const vpsissH3aPaxelConfig_t *cfg);

static void H3aSetIirCoeff(
    const isshalh3aInstObj_t         *instObj,
    const vpsissH3aAfIirFiltConfig_t *iirCfg1,
    const vpsissH3aAfIirFiltConfig_t *iirCfg2);

static void H3aSetFirCoeff(
    const isshalh3aInstObj_t         *instObj,
    const vpsissH3aAfFirFilrConfig_t *firCfg1,
    const vpsissH3aAfFirFilrConfig_t *firCfg2);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshalh3aInstObj_t      gIssHalH3aInstObjs[ISSHAL_H3A_MAX_INST] =
{(uint32_t)FALSE};

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gIssHalGlbceDefCfg' visibility is too wide.
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * static global variable used in many functions, but not accessed by any
 * other file.
 */
static const isshalh3aConfig_t gIssHalH3aDefCfg =
{
    {0U,      0U   },
    /* AF Configuration */
    {
        FALSE,                              /* enableALowCompr */
        FALSE,                              /* enableMedFilt */
        0x0U,                               /* midFiltThreshold */
        VPS_ISS_H3A_AF_RGBPOS_GR_BG,        /* rgbPos */
        /* Paxel Configuration */
        {
            {32U,     8U   },        /* Position */
            30U, 10,                 /* Size */
            2U, 2U,                  /* Count */
            6U, 6U                   /* Increment */
        },
        VPS_ISS_H3A_AF_FV_MODE_PEAK, /* AF FV Mode */
        VPS_ISS_H3A_AF_VF_VERT_HORZ, /* AF VF Mode */
        /* IIR1 Coeff */
        {
            {0x0008U, 0x0fa1U, 0x0fcfU, 0x0026U, 0x004cU, 0x0026U,
             0x0f91U, 0x0fcaU, 0x0011U, 0x0fdeU, 0x0011U},
            0x64U
        },
        /* IIR2 Coeff */
        {
            {0x000bU, 0x0fb8U, 0x0fceU, 0x001aU, 0x00233U, 0x001aU,
             0x0fa4U, 0x0fcbU, 0x0013U, 0x0fdaU, 0x0013U},
            0x64U
        },
        /* FIR1 Coeff */
        {
            {0x02U,   0x02U, 0x02U, 0x02U, 0x02U},
            0x1F4U
        },
        /* FIR2 Coeff */
        {
            {0x02U,   0x02U, 0x02U, 0x02U, 0x02U},
            0x1F4U
        },
        /* 0x1EU, */
        0x0U,
        VPS_ISS_H3A_MODE_NORMAL
    },
    /* AEW Configuration */
    {
        FALSE,                              /* enableALowCompr */
        FALSE,                              /* enableMedFilt */
        0xFFFU,                             /* midFiltThreshold */
        /* Window Configuration */
        {
            {32U,     16U  },             /* Position */
            64U,                          /* width */
            24U,                          /* height */
            16U,                          /* horzCount */
            32U,                          /* vertCount */
            4U,                           /* horzIncr */
            4U,                           /* vertIncr */
        },
        798U,                             /* Black Line Vertical Start */
        2U,                               /* Black Line Height */
        VPS_ISS_H3A_OUTPUT_MODE_SUM_ONLY, /* vpsissH3aOutputMode_t outMode; */
        0,                                /* sumShift */
        1023U,                            /* satLimit */
        VPS_ISS_H3A_MODE_NORMAL           /* vpsissH3aMode_t mode */
    }
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_issh3aInit(
    uint32_t                     numInst,
    const isshalh3aInstParams_t *instPrms,
    Ptr                          arg)
{
    uint32_t instCnt;
    isshalh3aInstObj_t *pInstObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= ISSHAL_H3A_MAX_INST));
    GT_assert(VpsHalTrace, (NULL != instPrms));

    /* Set the default Values for non-changing parameters */
    for(instCnt = 0U; instCnt < numInst; instCnt++)
    {
        /* MISRA.PTR.ARITH
         * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
         * Pointer is accessed as an array
         * KW State: Defer -> Waiver -> Case by case
         * MISRAC_WAIVER: Pointer is accessed as an array.
         * This function is called by init function, which passes
         * h3a number of instances. The size of this number of instances
         * is never more than ISSHAL_H3A_MAX_INST.
         */
        GT_assert(VpsHalTrace,
                  (instPrms[instCnt].instId < ISSHAL_H3A_INST_MAX_ID));
        GT_assert(VpsHalTrace,
                  (NULL != instPrms[instCnt].baseAddress));

        pInstObj = &gIssHalH3aInstObjs[instCnt];

        if((uint32_t)FALSE == pInstObj->isInitDone)
        {
            pInstObj->openCnt     = 0U;
            pInstObj->instId      = instPrms[instCnt].instId;
            pInstObj->baseAddress = instPrms[instCnt].baseAddress;
            pInstObj->isInitDone  = (uint32_t)TRUE;
        }
    }

    return (BSP_SOK);
}

int32_t VpsHal_issh3aDeInit(Ptr arg)
{
    uint32_t instCnt;
    isshalh3aInstObj_t *pInstObj;

    for(instCnt = 0U; instCnt < ISSHAL_H3A_INST_MAX_ID; instCnt++)
    {
        pInstObj = &gIssHalH3aInstObjs[instCnt];

        GT_assert(VpsHalTrace, (0U == pInstObj->openCnt));

        pInstObj->instId      = 0x0U;
        pInstObj->baseAddress = 0x0U;
        pInstObj->isInitDone  = (uint32_t)FALSE;
    }

    return (FVID2_SOK);
}

/**
 *  \brief This function should be called prior to calling any of the H3A HAL
 *  configuration APIs to get the instance handle.
 */
VpsHal_Handle VpsHal_issh3aOpen(const isshalOpenParams_t *openPrms,
                                Ptr                       arg)
{
    uint32_t            instCnt;
    VpsHal_Handle       handle   = NULL;
    isshalh3aInstObj_t *pInstObj = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, (NULL != openPrms));

    for(instCnt = 0; instCnt < ISSHAL_H3A_MAX_INST; instCnt++)
    {
        pInstObj = &(gIssHalH3aInstObjs[instCnt]);

        /* Return the matching instance handle */
        if(openPrms->instId == pInstObj->instId)
        {
            handle = (VpsHal_Handle) pInstObj;

            /* Enable Module clock on first open */
            if(0 == pInstObj->openCnt)
            {
                /* Enable H3A Clock at the ISS Level */
                GT_assert(
                    VpsHalTrace,
                    (FVID2_SOK ==
                     VpsHal_issEnableModule(ISSHAL_ISS_MODULE_H3A,
                        (uint32_t) TRUE)));
            }

            pInstObj->openCnt++;
            break;
        }
    }

    return (handle);
}

/**
 *  \brief This functions closes the h3a handle and after call to this
 *  function, h3a handle is not valid.
 */
int32_t VpsHal_issh3aClose(VpsHal_Handle handle,
                           Ptr           arg)
{
    int32_t status = FVID2_EFAIL;
    isshalh3aInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalh3aInstObj_t *) handle;

    /* Decrement the open count */
    if(pInstObj->openCnt > 0)
    {
        pInstObj->openCnt--;

        if(0U == pInstObj->openCnt)
        {
            /* Disable H3A Clock at the ISS Level */
            GT_assert(
                VpsHalTrace,
                (FVID2_SOK ==
                 VpsHal_issEnableModule(ISSHAL_ISS_MODULE_H3A,
                    (uint32_t) FALSE)));
        }

        status = FVID2_SOK;
    }

    return (status);
}

int32_t VpsHal_issh3aSetConfig(
    VpsHal_Handle            handle,
    const isshalh3aConfig_t *cfg,
    Ptr                      arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalh3aInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));

    instObj = (isshalh3aInstObj_t *) handle;

    regVal = (cfg->pos.startX << H3A_LINE_START_SHIFT) &
             H3A_LINE_START_MASK;
    regVal |= (cfg->pos.startY << H3A_LINE_START_SLV_SHIFT) &
              H3A_LINE_START_SLV_MASK;
    HW_WR_REG32(instObj->baseAddress + H3A_LINE_START, regVal);

    status = VpsHal_issh3aSetAfConfig(handle, &cfg->afCfg, arg);

    if(FVID2_SOK == status)
    {
        status = VpsHal_issh3aSetAewbConfig(handle, &cfg->aewbCfg, arg);
    }

    return (status);
}

int32_t VpsHal_issh3aGetConfig(
    VpsHal_Handle      handle,
    isshalh3aConfig_t *config)
{
    return (FVID2_SOK);
}

/* Function to process any command */
int32_t VpsHal_issh3aControl(
    VpsHal_Handle handle,
    uint32_t      cmd,
    Ptr           cmdArgs,
    Ptr           arg)
{
    int32_t status = FVID2_SOK;
    isshalh3aInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalh3aInstObj_t *) handle;

    switch(cmd)
    {
        case ISSHAL_IOCTL_H3A_SET_AFCFG:
            status = VpsHal_issh3aSetAfConfig(
                (VpsHal_Handle)instObj,
                (const vpsissH3aAfConfig_t *)cmdArgs,
                NULL);
            break;
        case ISSHAL_IOCTL_H3A_SET_AEWBCFG:
            status = VpsHal_issh3aSetAewbConfig(
                (VpsHal_Handle)instObj,
                (const vpsissH3aAewbConfig_t *)cmdArgs,
                NULL);
            break;
        case ISSHAL_IOCTL_H3A_GET_DEFAULTCFG:
            if(NULL != cmdArgs)
            {
                BspUtils_memcpy(
                    (isshalh3aConfig_t *) cmdArgs,
                    &gIssHalH3aDefCfg,
                    sizeof(isshalh3aConfig_t));
            }
            else
            {
                status = FVID2_EBADARGS;
            }
            break;
        default:
            status = FVID2_EUNSUPPORTED_CMD;
            break;
    }

    return (status);
}

/* Function to start the H3A AF module either in one shot or in free
 * running mode */
int32_t VpsHal_issh3aAfStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg)
{
    int32_t status = FVID2_SOK;
    isshalh3aInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalh3aInstObj_t *) handle;

    /* Enable AF engine, all the parameters must be set before
     * enabling this */
    HW_WR_REG32(pInstObj->baseAddress + H3A_PCR,
                HW_RD_REG32(
                    pInstObj->baseAddress + H3A_PCR) | H3A_PCR_AF_EN_MASK);

    return (status);
}

/* Function to start the H3A AE/AWB module either in one shot or in free
 * running mode */
int32_t VpsHal_issh3aAewbStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalh3aInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalh3aInstObj_t *) handle;

    /* Enable AF engine, all the parameters must be set before
     * enabling this */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + H3A_PCR);
    regVal |= H3A_PCR_AEW_EN_MASK;
    HW_WR_REG32(pInstObj->baseAddress + H3A_PCR, regVal);

    return (status);
}

/* Function to start the H3A AF module either in one shot or in free
 * running mode */
int32_t VpsHal_issh3aAfStop(
    VpsHal_Handle handle,
    Ptr           arg)
{
    int32_t status = FVID2_SOK;
    isshalh3aInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalh3aInstObj_t *) handle;

    /* Enable AF engine, all the parameters must be set before
     * enabling this */
    HW_WR_REG32(pInstObj->baseAddress + H3A_PCR,
                HW_RD_REG32(pInstObj->baseAddress + H3A_PCR) &
                    ~((UInt32) H3A_PCR_AF_EN_MASK));

    return (status);
}

/* Function to start the H3A AE/AWB module either in one shot or in free
 * running mode */
int32_t VpsHal_issh3aAewbStop(
    VpsHal_Handle handle,
    Ptr           arg)
{
    int32_t status = FVID2_SOK;
    isshalh3aInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalh3aInstObj_t *) handle;

    /* Enable AF engine, all the parameters must be set before
     * enabling this */
    HW_WR_REG32(pInstObj->baseAddress + H3A_PCR,
                HW_RD_REG32(
                    pInstObj->baseAddress + H3A_PCR) & ~H3A_PCR_AEW_EN_MASK);

    return (status);
}

int32_t VpsHal_issh3aSetAfAddress(
    VpsHal_Handle handle,
    Ptr           address,
    Ptr           arg)
{
    int32_t status = FVID2_SOK;
    isshalh3aInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalh3aInstObj_t *) handle;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * Casting between a pointer to an integral type
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Pointer containing frame buffer address type casted for
     * setting memory mapped register, address is alrady checked for
     * null condition in the core layer
     */
    HW_WR_REG32(pInstObj->baseAddress + H3A_AFBUFST,
                (uint32_t) address & H3A_AFBUFST_MASK);

    return (status);
}

int32_t VpsHal_issh3aSetAewbAddress(
    VpsHal_Handle handle,
    Ptr           address,
    Ptr           arg)
{
    int32_t status = FVID2_SOK;
    isshalh3aInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalh3aInstObj_t *) handle;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * Casting between a pointer to an integral type
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Pointer containing frame buffer address type casted for
     * setting memory mapped register, address is alrady checked for
     * null condition in the core layer
     */
    HW_WR_REG32(pInstObj->baseAddress + H3A_AEWBUFST,
                (uint32_t) address & H3A_AEWBUFST_MASK);

    return (status);
}

/* Set the AF Configuration */
int32_t VpsHal_issh3aSetAfConfig(
    VpsHal_Handle              handle,
    const vpsissH3aAfConfig_t *cfg,
    Ptr                        arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalh3aInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalh3aInstObj_t *) handle;

    if(NULL == cfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        /* Check for errors */
        status = H3aCheckPaxelWinConfig(&cfg->paxelCfg);
    }

    if((FVID2_SOK == status) &&
       (cfg->paxelCfg.pos.startX < (cfg->iirFiltStartPos + 2U)))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        if(VPS_ISS_H3A_AF_VF_VERT_HORZ == cfg->vfMode)
        {
            if(8U > cfg->paxelCfg.pos.startY)
            {
                status = FVID2_EINVALID_PARAMS;
            }

            if((cfg->paxelCfg.pos.startX & 0x1U) !=
               (cfg->iirFiltStartPos & 0x1U))
            {
                status = FVID2_EINVALID_PARAMS;
            }

            if((cfg->iirFiltStartPos%2U) != 0U)
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }
        else
        {
            if(0U != (cfg->paxelCfg.pos.startX%2U))
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }
    }

    if(FVID2_SOK == status)
    {
        /* Set the Window Configuration */
        regVal = ((UInt32)((cfg->paxelCfg.width / 2U) - 1U) <<
                            (UInt32) H3A_AFPAX1_PAXW_SHIFT) &
                 H3A_AFPAX1_PAXW_MASK;
        regVal |= (((UInt32) ((cfg->paxelCfg.height / 2U) - 1U)) <<
                   H3A_AFPAX1_PAXH_SHIFT) &
                  H3A_AFPAX1_PAXH_MASK;
        HW_WR_REG32(instObj->baseAddress + H3A_AFPAX1, regVal);

        regVal = (((UInt32) ((cfg->paxelCfg.horzIncr / 2U) - 1U)) <<
                  H3A_AFPAX2_AFINCH_SHIFT) &
                 H3A_AFPAX2_AFINCH_MASK;
        regVal |= ((UInt32) ((cfg->paxelCfg.vertIncr / 2U) - 1U) <<
                   H3A_AFPAX2_AFINCV_SHIFT) &
                  H3A_AFPAX2_AFINCV_MASK;
        regVal |= ((UInt32) (cfg->paxelCfg.horzCount - 1U) <<
                   H3A_AFPAX2_PAXHC_SHIFT) &
                  H3A_AFPAX2_PAXHC_MASK;
        regVal |= ((UInt32) (cfg->paxelCfg.vertCount - 1U) <<
                   H3A_AFPAX2_PAXVC_SHIFT) &
                  H3A_AFPAX2_PAXVC_MASK;
        HW_WR_REG32(instObj->baseAddress + H3A_AFPAX2, regVal);

        regVal = (cfg->paxelCfg.pos.startX << H3A_AFPAXSTART_PAXSH_SHIFT) &
                 H3A_AFPAXSTART_PAXSH_MASK;
        regVal |= (cfg->paxelCfg.pos.startY << H3A_AFPAXSTART_PAXSV_SHIFT) &
                  H3A_AFPAXSTART_PAXSV_MASK;
        HW_WR_REG32(instObj->baseAddress + H3A_AFPAXSTART, regVal);

        HW_WR_REG32(instObj->baseAddress + H3A_AFIIRSH,
                    ((cfg->iirFiltStartPos << H3A_AFIIRSH_IIRSH_SHIFT) &
                     H3A_AFIIRSH_IIRSH_MASK));

        /* Set the IIR and FIR coefficients */
        H3aSetIirCoeff(instObj, &cfg->iirCfg1, &cfg->iirCfg2);
        H3aSetFirCoeff(instObj, &cfg->firCfg1, &cfg->firCfg2);

        regVal = HW_RD_REG32(instObj->baseAddress + H3A_PCR);

        regVal &= ~H3A_PCR_AF_VF_EN_MASK;
        if(VPS_ISS_H3A_AF_VF_VERT_HORZ == cfg->vfMode)
        {
            regVal |= H3A_PCR_AF_VF_EN_MASK;
        }

        regVal &= ~((UInt32) H3A_PCR_FVMODE_MASK);
        if(VPS_ISS_H3A_AF_FV_MODE_PEAK == cfg->fvMode)
        {
            regVal |= H3A_PCR_FVMODE_MASK;
        }

        regVal &= ~((UInt32) H3A_PCR_AF_ALAW_EN_MASK);
        if(TRUE == cfg->enableALowCompr)
        {
            regVal |= H3A_PCR_AF_ALAW_EN_MASK;
        }

        regVal &= ~((UInt32) H3A_PCR_AF_MED_EN_MASK);
        if(TRUE == cfg->enableMedFilt)
        {
            regVal |= H3A_PCR_AF_MED_EN_MASK;

            regVal &= ~((UInt32) H3A_PCR_MED_TH_MASK);
            regVal |= (cfg->midFiltThreshold << H3A_PCR_MED_TH_SHIFT) &
                      H3A_PCR_MED_TH_MASK;
        }

        regVal &= ~((UInt32) H3A_PCR_RGBPOS_MASK);
        regVal |= ((uint32_t) cfg->rgbPos << H3A_PCR_RGBPOS_SHIFT) &
                  H3A_PCR_RGBPOS_MASK;

        HW_WR_REG32(instObj->baseAddress + H3A_PCR, regVal);

        /* Set the AF Mode in Advanced Config register */
        regVal  = HW_RD_REG32(instObj->baseAddress + H3A_ADVANCED);
        regVal &= ~((UInt32) H3A_ADVANCED_AF_MODE_MASK);

        if(VPS_ISS_H3A_MODE_ADVANCED == cfg->mode)
        {
            /* First write ID to 0xCA00 */
            regVal &= ~((UInt32) H3A_ADVANCED_ID_MASK);
            regVal |= ((uint32_t)0xCA00U << H3A_ADVANCED_ID_SHIFT) &
                      H3A_ADVANCED_ID_MASK;
            regVal |= (cfg->mode << H3A_ADVANCED_AF_MODE_SHIFT) &
                      H3A_ADVANCED_AF_MODE_MASK;
        }
        HW_WR_REG32(instObj->baseAddress + H3A_ADVANCED, regVal);
    }

    return (status);
}

/* Set the AEWB Configuration */
int32_t VpsHal_issh3aSetAewbConfig(
    VpsHal_Handle                handle,
    const vpsissH3aAewbConfig_t *cfg,
    Ptr                          arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalh3aInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalh3aInstObj_t *) handle;

    if(NULL == cfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        /* Check for errors */
        status = H3aCheckPaxelWinConfig(&cfg->winCfg);
    }

    /*if((cfg->blackLinePos.startY > 127) ||
       (cfg->blackLinePos.startX >
        (H3A_AEWINBLK_WINSV_MASK >> H3A_AEWINBLK_WINSV_SHIFT)))
    {
        status = FVID2_EINVALID_PARAMS;
    }*/

    if(FVID2_SOK == status)
    {
        /* Set the output format and shift value for the saturation */
        regVal = HW_RD_REG32(instObj->baseAddress + H3A_AEWCFG);

        regVal &= ~((UInt32) H3A_AEWCFG_AEFMT_MASK);
        regVal &= ~((UInt32) H3A_AEWCFG_SUMSHFT_MASK);

        regVal |= (cfg->outMode << H3A_AEWCFG_AEFMT_SHIFT) &
                  H3A_AEWCFG_AEFMT_MASK;
        regVal |= (cfg->sumShift << H3A_AEWCFG_SUMSHFT_SHIFT) &
                  H3A_AEWCFG_SUMSHFT_MASK;

        HW_WR_REG32(instObj->baseAddress + H3A_AEWCFG, regVal);

        /* Set the Saturation limit and enable aLaw compression and
         * median filter */
        regVal = HW_RD_REG32(instObj->baseAddress + H3A_PCR);

        regVal &= ~((UInt32) H3A_PCR_AVE2LMT_MASK);
        regVal |= (cfg->satLimit << H3A_PCR_AVE2LMT_SHIFT) &
                  H3A_PCR_AVE2LMT_MASK;

        regVal &= ~((UInt32) H3A_PCR_AEW_MED_EN_MASK);
        if(TRUE == cfg->enableMedFilt)
        {
            regVal |= H3A_PCR_AEW_MED_EN_MASK;

            regVal &= ~((UInt32) H3A_PCR_MED_TH_MASK);
            regVal |= cfg->midFiltThreshold;
        }

        regVal &= ~((UInt32) H3A_PCR_AEW_ALAW_EN_MASK);
        if(TRUE == cfg->enableALowComp)
        {
            regVal |= H3A_PCR_AEW_ALAW_EN_MASK;
        }

        HW_WR_REG32(instObj->baseAddress + H3A_PCR, regVal);

        /* Set the Window parameters */
        regVal = (((UInt32) ((cfg->winCfg.width / 2U) - 1U)) <<
                  H3A_AEWWIN1_WINW_SHIFT) &
                 H3A_AEWWIN1_WINW_MASK;
        regVal |= (((UInt32) ((cfg->winCfg.height / 2U) - 1U)) <<
                   H3A_AEWWIN1_WINH_SHIFT) &
                  H3A_AEWWIN1_WINH_MASK;
        regVal |= (((UInt32) (cfg->winCfg.horzCount - 1U)) <<
                   H3A_AEWWIN1_WINHC_SHIFT) &
                  H3A_AEWWIN1_WINHC_MASK;
        regVal |= (((UInt32) (cfg->winCfg.vertCount - 1U)) <<
                   H3A_AEWWIN1_WINVC_SHIFT) &
                  H3A_AEWWIN1_WINVC_MASK;
        HW_WR_REG32(instObj->baseAddress + H3A_AEWWIN1, regVal);

        /* Set the Window Start Position */
        regVal = (cfg->winCfg.pos.startX << H3A_AEWINSTART_WINSH_SHIFT) &
                 H3A_AEWINSTART_WINSH_MASK;
        regVal |= (cfg->winCfg.pos.startY << H3A_AEWINSTART_WINSV_SHIFT) &
                  H3A_AEWINSTART_WINSV_MASK;
        HW_WR_REG32(instObj->baseAddress + H3A_AEWINSTART, regVal);

        /* Set the black window start position */
        regVal = (cfg->blackLineVertStart << H3A_AEWINBLK_WINSV_SHIFT) &
                 H3A_AEWINBLK_WINSV_MASK;
        regVal |= (((UInt32) ((cfg->blackLineHeight / 2U) + 1U)) <<
                   H3A_AEWINBLK_WINH_SHIFT) &
                  H3A_AEWINBLK_WINH_MASK;
        HW_WR_REG32(instObj->baseAddress + H3A_AEWINBLK, regVal);

        /* Set the subwindow sampling point increment */
        regVal = (((UInt32) ((cfg->winCfg.horzIncr / 2U) - 1U)) <<
                  H3A_AEWSUBWIN_AEWINCH_SHIFT) &
                 H3A_AEWSUBWIN_AEWINCH_MASK;
        regVal |= (((UInt32) ((cfg->winCfg.vertIncr / 2U) - 1U)) <<
                   H3A_AEWSUBWIN_AEWINCV_SHIFT) &
                  H3A_AEWSUBWIN_AEWINCV_MASK;
        HW_WR_REG32(instObj->baseAddress + H3A_AEWSUBWIN, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + H3A_ADVANCED);
        regVal &= ~((UInt32) H3A_ADVANCED_AEW_MODE_MASK);

        if(VPS_ISS_H3A_MODE_ADVANCED == cfg->mode)
        {
            /* First write ID to 0xDA00 */
            regVal &= ~H3A_ADVANCED_ID_MASK;
            regVal |= ((uint32_t)0xDA00U << H3A_ADVANCED_ID_SHIFT) &
                      H3A_ADVANCED_ID_MASK;
            regVal |= (cfg->mode << H3A_ADVANCED_AEW_MODE_SHIFT) &
                      H3A_ADVANCED_AEW_MODE_MASK;
        }
        HW_WR_REG32(instObj->baseAddress + H3A_ADVANCED, regVal);
    }

    return (status);
}

uint32_t VpsHal_issh3aIsAfBusy(VpsHal_Handle handle)
{
    uint32_t status = FALSE;
    isshalh3aInstObj_t *instObj = NULL;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalh3aInstObj_t *) handle;

    regVal = HW_RD_REG32(instObj->baseAddress + H3A_PCR);
    if((regVal & H3A_PCR_BUSYAF_MASK) == H3A_PCR_BUSYAF_MASK)
    {
        status = (uint32_t)TRUE;
    }
    else
    {
        status = (uint32_t)FALSE;
    }

    return (status);
}

uint32_t VpsHal_issh3aIsAewbBusy(VpsHal_Handle handle)
{
    uint32_t status = FALSE;
    isshalh3aInstObj_t *instObj = NULL;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalh3aInstObj_t *) handle;

    regVal = HW_RD_REG32(instObj->baseAddress + H3A_PCR);
    if((regVal & H3A_PCR_BUSYAEAWB_MASK) == H3A_PCR_BUSYAEAWB_MASK)
    {
        status = (uint32_t)TRUE;
    }
    else
    {
        status = (uint32_t)FALSE;
    }

    return (status);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void H3aSetFirCoeff(
    const isshalh3aInstObj_t         *instObj,
    const vpsissH3aAfFirFilrConfig_t *firCfg1,
    const vpsissH3aAfFirFilrConfig_t *firCfg2)
{
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (NULL != firCfg1));
    GT_assert(VpsHalTrace, (NULL != firCfg2));

    /* Set the FIR coefficients */
    regVal = ((uint32_t) firCfg1->coeff[0U] << H3A_VFV_CFG1_VCOEF1_0_SHIFT) &
             H3A_VFV_CFG1_VCOEF1_0_MASK;
    regVal |= ((uint32_t) firCfg1->coeff[1U] << H3A_VFV_CFG1_VCOEF1_1_SHIFT) &
              H3A_VFV_CFG1_VCOEF1_1_MASK;
    regVal |= ((uint32_t) firCfg1->coeff[2U] << H3A_VFV_CFG1_VCOEF1_2_SHIFT) &
              H3A_VFV_CFG1_VCOEF1_2_MASK;
    regVal |= ((uint32_t) firCfg1->coeff[3U] << H3A_VFV_CFG1_VCOEF1_3_SHIFT) &
              H3A_VFV_CFG1_VCOEF1_3_MASK;
    HW_WR_REG32(instObj->baseAddress + H3A_VFV_CFG1, regVal);

    regVal = ((uint32_t) firCfg1->coeff[4U] << H3A_VFV_CFG2_VCOEF1_4_SHIFT) &
             H3A_VFV_CFG2_VCOEF1_4_MASK;
    regVal |= ((uint32_t) firCfg1->threshold << H3A_VFV_CFG2_VTHR1_SHIFT) &
              H3A_VFV_CFG2_VTHR1_MASK;
    HW_WR_REG32(instObj->baseAddress + H3A_VFV_CFG2, regVal);

    /* Set the FIR coefficients */
    regVal = ((uint32_t) firCfg2->coeff[0U] << H3A_VFV_CFG3_VCOEF2_0_SHIFT) &
             H3A_VFV_CFG3_VCOEF2_0_MASK;
    regVal |= ((uint32_t) firCfg2->coeff[1U] << H3A_VFV_CFG3_VCOEF2_1_SHIFT) &
              H3A_VFV_CFG3_VCOEF2_1_MASK;
    regVal |= ((uint32_t) firCfg2->coeff[2U] << H3A_VFV_CFG3_VCOEF2_2_SHIFT) &
              H3A_VFV_CFG3_VCOEF2_2_MASK;
    regVal |= ((uint32_t) firCfg2->coeff[3U] << H3A_VFV_CFG3_VCOEF2_3_SHIFT) &
              H3A_VFV_CFG3_VCOEF2_3_MASK;
    HW_WR_REG32(instObj->baseAddress + H3A_VFV_CFG3, regVal);

    regVal = ((uint32_t) firCfg2->coeff[4U] << H3A_VFV_CFG4_VCOEF2_4_SHIFT) &
             H3A_VFV_CFG4_VCOEF2_4_MASK;
    regVal |= (firCfg2->threshold << H3A_VFV_CFG4_VTHR2_SHIFT) &
              H3A_VFV_CFG4_VTHR2_MASK;
    HW_WR_REG32(instObj->baseAddress + H3A_VFV_CFG4, regVal);
}

static void H3aSetIirCoeff(
    const isshalh3aInstObj_t         *instObj,
    const vpsissH3aAfIirFiltConfig_t *iirCfg1,
    const vpsissH3aAfIirFiltConfig_t *iirCfg2)
{
    uint32_t cnt;
    uint32_t iirCnt;
    uint32_t coeffRegAddr;
    uint32_t regVal;
    const vpsissH3aAfIirFiltConfig_t *tempIirCfg;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (NULL != iirCfg1));
    GT_assert(VpsHalTrace, (NULL != iirCfg2));

    for(cnt = 0U; cnt < 2U; cnt++)
    {
        if(0U == cnt)
        {
            coeffRegAddr = instObj->baseAddress + H3A_AFCOEF010;
            tempIirCfg   = iirCfg1;
        }
        else
        {
            coeffRegAddr = instObj->baseAddress + H3A_AFCOEF110;
            tempIirCfg   = iirCfg2;
        }

        for(iirCnt = 0U; iirCnt < VPS_ISS_H3A_AF_IIR_COEFF_MAX; iirCnt += 2U)
        {
            regVal =
                ((uint32_t) tempIirCfg->coeff[iirCnt] <<
                    H3A_AFCOEF010_COEFF0_SHIFT) &
                H3A_AFCOEF010_COEFF0_MASK;

            if(iirCnt < (VPS_ISS_H3A_AF_IIR_COEFF_MAX - 2U))
            {
                regVal |= ((uint32_t) tempIirCfg->coeff[iirCnt + 1U]
                           << H3A_AFCOEF010_COEFF1_SHIFT) &
                          H3A_AFCOEF010_COEFF1_MASK;
            }

            HW_WR_REG32(coeffRegAddr, regVal);

            coeffRegAddr += 4U;
        }
    }

    /* Set the IIR coefficients Threshold */
    regVal = (iirCfg1->threshold << H3A_HVF_THR_HTHR1_SHIFT) &
             H3A_HVF_THR_HTHR1_MASK;
    regVal |= (iirCfg2->threshold << H3A_HVF_THR_HTHR2_SHIFT) &
              H3A_HVF_THR_HTHR2_MASK;
    HW_WR_REG32(instObj->baseAddress + H3A_HVF_THR, regVal);
}

static int32_t H3aCheckPaxelWinConfig(const vpsissH3aPaxelConfig_t *cfg)
{
    int32_t status = FVID2_SOK;

    if((cfg->width < 8U) ||
       (cfg->height < 2U) ||
       (cfg->height > 512U))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if((cfg->horzCount < 2U) ||
       (cfg->horzCount > 35U) ||
       (cfg->vertCount > 127U))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if((cfg->horzIncr < 2U) ||
       (cfg->horzIncr > 32U) ||
       (cfg->vertIncr < 2U) ||
       (cfg->vertIncr > 32U))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    return (status);
}

