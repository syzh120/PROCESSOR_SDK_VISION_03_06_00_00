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
 *  \file isshal_nsf3.c
 *
 *  \brief File containing the ISS NSF3 HAL init, deinit and other common
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
#include <ti/drv/vps/src/vpslib/hal/vpshal_issnsf3.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct isshalnsf3InstObj
{
    uint32_t isInitDone;
    /**< Flag to indicate whether init is done or not */
    uint32_t instId;
    /**< Id of the instance */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t openCnt;
    /**< Open count */
    uint32_t moduleId;
} isshalnsf3InstObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Function to set the Edge Enhancement parameters */
int32_t Nsf3SetEdgeEnhcConfig(
    const isshalnsf3InstObj_t          *pInstObj,
    const vpsissNsf3EdgeEnhnceConfig_t *eeCfg);

int32_t Nsf3SetShadGainConfig(
    const isshalnsf3InstObj_t         *pInstObj,
    const vpsissNsf3ShadeGainConfig_t *sgCfg);

int32_t Nsf3SetNsfThrsldConfig(
    const isshalnsf3InstObj_t            *pInstObj,
    const vpsissNsf3NoiseThrshldConfig_t *nsCfg);

/* Function to reset the NSF3 module, should be used only when dps is not
 * in pre-nsf3 path. Otherwise ISS reset should be used */
void Nsf3Reset(const isshalnsf3InstObj_t *instObj);

static inline uint32_t Nsf3GetThrKneeMask(uint32_t cnt);
static inline uint32_t Nsf3GetThrKneeShift(uint32_t cnt);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshalnsf3InstObj_t           gIssHalNsf3InstObjs[ISSHAL_NSF3_MAX_INST]
    = {(uint32_t)FALSE};

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gIssHalNsf3DefCfg' visibility is too wide.
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * static global variable used in many functions, but not accessed by any
 * other file.
 */
static const vpsissNsf3Config_t      gIssHalNsf3DefCfg =
{
    FALSE,                      /* Bypass */
    VPS_ISS_NSF3_OP_MODE_BAYER, /* mode */
    TRUE,                       /* border replicate */
    FALSE,                      /* chroma desaturation */
    /* ns Config */
    {
        /* hPos */
        {
            {0U,   16U,  128U, 1024U},
            {0U,   16U,  128U, 1024U},
            {0U,   16U,  128U, 1024U},
            {0U,   16U,  128U, 1024U}
        },
        /* vpos */
        {
            {2U,   3U,   6U,   8U   },
            {2U,   3U,   6U,   8U   },
            {2U,   3U,   6U,   8U   },
            {2U,   3U,   6U,   8U   }
        },
        /* Slope */
        {
            {128U, 54U,  4U,   2U   },
            {128U, 54U,  4U,   2U   },
            {128U, 54U,  4U,   2U   },
            {128U, 54U,  4U,   2U   }
        },
        64U, 16U,
        {
            32U, 80U, 128U
        }
    },
    {
        {128U, 128U, 128U},
        {128U, 128U, 128U},
        {128U, 128U, 128U},
        {128U, 128U, 128U}
    },
    {
        {128U, 128U, 128U},
        {128U, 128U, 128U},
        {128U, 128U, 128U},
        {128U, 128U, 128U}
    },
    /* EE Config */
    {
        FALSE,  /* ee_enable */
        {
            {64U,  64U,  64U},
            {64U,  64U,  64U},
            {64U,  64U,  64U},
            {64U,  64U,  64U}
        },
        {
            {64U,  64U,  64U},
            {64U,  64U,  64U},
            {64U,  64U,  64U},
            {64U,  64U,  64U}
        },
        0U, 0U, 0U, 0U
    },
    {
        FALSE,  /* shading gain enable */
        {0U,   0U},
        {0U,   0U},
        {0U,   0U},
        0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 99U
    }
};

static const isshalissBlankingInfo_t gIssHalNsf3BlankInfo
[VPS_ISS_NSF3_MAX_OP_MODE][2U] =
{
    {                                               /*
                                                     * *VPS_ISS_NSF3_OP_MODE_BAYER
                                                     **/
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 13U,  4U }, /* Blanking requirement
                                                     * without Border
                                                     * replication */
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 45U,  18U}  /* Blanking requirement
                                                     * with Border replication
                                                     * */
    },
    {                                               /*
                                                     * *VPS_ISS_NSF3_OP_MODE_BAYER_2x2
                                                     **/
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 13U,  4U },
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 77U,  18U}
    },
    {                   /* VPS_ISS_NSF3_OP_MODE_BAYER_3x3 */
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 13U,  4U },
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 109U, 18U}
    },
    {                   /* VPS_ISS_NSF3_OP_MODE_YUV422 */
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 26U,  2U },
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 90U,  9U }
    },
    {                   /* VPS_ISS_NSF3_OP_MODE_YUV420_LUMA */
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 26U,  2U },
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 42U,  9U }
    },
    {                   /* VPS_ISS_NSF3_OP_MODE_YUV420_CHROMA */
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 26U,  2U },
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 58U,  9U }
    },
    {                   /* VPS_ISS_NSF3_OP_MODE_YUV422_INTLD */
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 26U,  2U },
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 154U, 9U }
    },
    {                   /* VPS_ISS_NSF3_OP_MODE_YUV420_LUMA_INTLD */
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 13U,  4U },
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 45U,  18U}
    },
    {                   /* VPS_ISS_NSF3_OP_MODE_YUV420_CHROMA_INTLD */
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 26U,  2U },
        {ISSHAL_ISS_PROC_MODE_ONE_SHOT, 90U,  9U }
    }
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_issnsf3Init(
    UInt32                        numInst,
    const isshalnsf3InstParams_t *instPrms,
    Ptr                           arg)
{
    uint32_t instCnt;
    isshalnsf3InstObj_t *pInstObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= ISSHAL_NSF3_MAX_INST));
    GT_assert(VpsHalTrace, (NULL != instPrms));

    /* Set the default Values for non-changing parameters */
    for(instCnt = 0U; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  (NULL != instPrms));
        GT_assert(VpsHalTrace,
                  (instPrms->instId < ISSHAL_NSF3_INST_MAX_ID));
        GT_assert(VpsHalTrace,
                  (NULL != instPrms->baseAddress));

        pInstObj = &gIssHalNsf3InstObjs[instCnt];

        if((uint32_t)FALSE == pInstObj->isInitDone)
        {
            pInstObj->openCnt     = 0U;
            pInstObj->instId      = instPrms->instId;
            pInstObj->baseAddress = instPrms->baseAddress;
            pInstObj->isInitDone  = (uint32_t)TRUE;
            pInstObj->moduleId    = instPrms->moduleId;
        }

        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 and MISRAC_2004_Rule_17.4
         * Pointer is accessed as an array
         * KW State: Defer -> Waiver -> Case by case
         * MISRAC_WAIVER: Pointer is accessed as an array.
         * This function is called by init function, which passes
         * nsf3v number of instances. The size of this number of instances
         * is never more than ISSHAL_NSF3_MAX_INST.
         */
        instPrms++;
    }

    return (BSP_SOK);
}

int32_t VpsHal_issnsf3DeInit(Ptr arg)
{
    uint32_t instCnt;
    isshalnsf3InstObj_t *pInstObj;

    for(instCnt = 0U; instCnt < ISSHAL_NSF3_INST_MAX_ID; instCnt++)
    {
        pInstObj = &gIssHalNsf3InstObjs[instCnt];

        GT_assert(VpsHalTrace, (0U == pInstObj->openCnt));

        pInstObj->instId      = 0x0U;
        pInstObj->baseAddress = 0x0U;
        pInstObj->isInitDone  = (uint32_t)FALSE;
    }

    return (FVID2_SOK);
}

/**
 *  VpsHal_issnsf3Open
 *  \brief This function should be called prior to calling any of the NSF3 HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters
 */
VpsHal_Handle VpsHal_issnsf3Open(const isshalOpenParams_t *openPrms,
                                 Ptr                       arg)
{
    uint32_t             instCnt;
    VpsHal_Handle        handle   = NULL;
    isshalnsf3InstObj_t *pInstObj = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, (NULL != openPrms));

    for(instCnt = 0U; instCnt < ISSHAL_NSF3_MAX_INST; instCnt++)
    {
        pInstObj = &(gIssHalNsf3InstObjs[instCnt]);

        /* Return the matching instance handle */
        if(openPrms->instId == pInstObj->instId)
        {
            handle = (VpsHal_Handle) (pInstObj);

            /* Enable Module clock on first open */
            if(0 == pInstObj->openCnt)
            {
                /* Enable NSF3 Clock at the ISS Level */
                GT_assert(
                    VpsHalTrace,
                    (FVID2_SOK ==
                     VpsHal_issEnableModule(
                         (isshalIssModuleId_t) pInstObj->moduleId,
                         (uint32_t) TRUE)));

#ifdef NOT_YET
                /* TODO:
                    NSF3 reset is causing hang issue while running wdr
                   flow with the YUV420 resizer, Need to debug this issue
                   further. */
                /* Resetting NSF3 on first open */
                Nsf3Reset(pInstObj);
#endif
            }

            pInstObj->openCnt++;
            break;
        }
    }

    return (handle);
}

/**
 *  VpsHal_issnsf3Close
 *  \brief This functions closes the nsf3 handle and after call to this
 *  function, nsf3 handle is not valid.
 *
 *  \param handle         Requested NSF3 instance
 */
int32_t VpsHal_issnsf3Close(VpsHal_Handle handle,
                            Ptr           arg)
{
    int32_t status = FVID2_EFAIL;
    isshalnsf3InstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalnsf3InstObj_t *) handle;

    /* Decrement the open count */
    if(pInstObj->openCnt > 0)
    {
        pInstObj->openCnt--;

        if(0U == pInstObj->openCnt)
        {
            /* Disable NSF3 Clock at the ISS Level */
            GT_assert(
                VpsHalTrace,
                (FVID2_SOK ==
                 VpsHal_issEnableModule((isshalIssModuleId_t) pInstObj->
                                        moduleId, (uint32_t) FALSE)));
        }

        status = FVID2_SOK;
    }

    return (status);
}

int32_t VpsHal_issnsf3SetConfig(
    VpsHal_Handle             handle,
    const vpsissNsf3Config_t *cfg,
    Ptr                       arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t coeffRegAddr;
    uint32_t regVal;
    uint32_t cnt;
    isshalnsf3InstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));

    pInstObj = (isshalnsf3InstObj_t *) handle;

    /* Do Error checking */

    /* Set the Color Suppression Coefficients */
    coeffRegAddr = pInstObj->baseAddress + NSF3V_SUP_C00;
    for(cnt = 0U; cnt < ISSHAL_NSF3_MAX_COLOR; cnt++)
    {
        regVal = (cfg->lhSubbandMax[cnt][0U] <<
                  NSF3V_SUP_C00_L1_LH_SHIFT) &
                 NSF3V_SUP_C00_L1_LH_MASK;
        regVal |= (cfg->hhSubbandMax[cnt][0U] <<
                   NSF3V_SUP_C00_L1_HH_SHIFT) &
                  NSF3V_SUP_C00_L1_HH_MASK;
        regVal |= (cfg->lhSubbandMax[cnt][1U] <<
                   NSF3V_SUP_C00_L2_LH_SHIFT) &
                  NSF3V_SUP_C00_L2_LH_MASK;
        regVal |= (cfg->hhSubbandMax[cnt][1U] <<
                   NSF3V_SUP_C00_L2_HH_SHIFT) &
                  NSF3V_SUP_C00_L2_HH_MASK;
        HW_WR_REG32(coeffRegAddr, regVal);

        regVal  = HW_RD_REG32(coeffRegAddr + 4U);
        regVal &= ~((UInt32) (NSF3V_SUP_C01_L3_LH_MASK |
                              NSF3V_SUP_C01_L3_HH_MASK));
        regVal |= (cfg->lhSubbandMax[cnt][2U] <<
                   NSF3V_SUP_C01_L3_LH_SHIFT) &
                  NSF3V_SUP_C01_L3_LH_MASK;
        regVal |= (cfg->hhSubbandMax[cnt][2U] <<
                   NSF3V_SUP_C01_L3_HH_SHIFT) &
                  NSF3V_SUP_C01_L3_HH_MASK;
        HW_WR_REG32(coeffRegAddr + 4U, regVal);

        coeffRegAddr += (NSF3V_SUP_C10 - NSF3V_SUP_C00);
    }
    status = Nsf3SetNsfThrsldConfig(pInstObj, &cfg->nsCfg);
    if(FVID2_SOK == status)
    {
        status = Nsf3SetShadGainConfig(pInstObj, &cfg->sgCfg);
    }
    if(FVID2_SOK == status)
    {
        status = Nsf3SetEdgeEnhcConfig(pInstObj, &cfg->eeCfg);
    }

    if(FVID2_SOK == status)
    {
        regVal = HW_RD_REG32(pInstObj->baseAddress + NSF3V_CFG);

        regVal &= ~((UInt32) NSF3V_CFG_BYPASS_W_DELAY_MASK);
        if(TRUE == cfg->bypass)
        {
            regVal |= NSF3V_CFG_BYPASS_W_DELAY_MASK;
        }

        regVal &= ~((UInt32) (NSF3V_CFG_LBORDER_REP_MASK |
                              NSF3V_CFG_RBORDER_REP_MASK |
                              NSF3V_CFG_TBORDER_REP_MASK |
                              NSF3V_CFG_BBORDER_REP_MASK));
        if(TRUE == cfg->enableBorderReplicate)
        {
            regVal |=
                (NSF3V_CFG_LBORDER_REP_MASK | NSF3V_CFG_RBORDER_REP_MASK |
                 NSF3V_CFG_TBORDER_REP_MASK | NSF3V_CFG_BBORDER_REP_MASK);
        }

        regVal &= ~((UInt32) NSF3V_CFG_DESAT_EN_MASK);
        if(TRUE == cfg->enableChromaDeSatur)
        {
            regVal |= NSF3V_CFG_DESAT_EN_MASK;
        }

        regVal &= ~((UInt32) NSF3V_CFG_MODE_MASK);
        regVal |= (((uint32_t) cfg->opMode) << NSF3V_CFG_MODE_SHIFT) &
                  NSF3V_CFG_MODE_MASK;

        HW_WR_REG32(pInstObj->baseAddress + NSF3V_CFG, regVal);
    }

    return (status);
}

int32_t VpsHal_issnsf3GetConfig(
    VpsHal_Handle       handle,
    vpsissNsf3Config_t *config)
{
    return (FVID2_SOK);
}

/* Function to process any command */
int32_t VpsHal_issnsf3Control(
    VpsHal_Handle handle,
    UInt32        cmd,
    Ptr           cmdArgs,
    Ptr           arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t modeCnt;
    uint32_t regVal;
    isshalnsf3InstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalnsf3InstObj_t *) handle;

    switch(cmd)
    {
        case ISSHAL_IOCTL_NSF3_GET_DEFAULTCFG:
        {
            if(NULL != cmdArgs)
            {
                BspUtils_memcpy(
                    ((vpsissNsf3Config_t *) cmdArgs),
                    &gIssHalNsf3DefCfg,
                    sizeof(vpsissNsf3Config_t));
            }
            else
            {
                status = FVID2_EBADARGS;
            }
            break;
        }
        case VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO:
        {
            isshalissBlankingInfo_t *blankInfo =
                (isshalissBlankingInfo_t *) cmdArgs;
            vpsissNsf3Config_t      *cfg = (vpsissNsf3Config_t *) arg;

            GT_assert(VpsHalTrace, (NULL != cfg));
            GT_assert(VpsHalTrace, (NULL != blankInfo));

            for(modeCnt = 0U; modeCnt < VPS_ISS_NSF3_MAX_OP_MODE;
                modeCnt++)
            {
                if(modeCnt == (uint32_t) cfg->opMode)
                {
                    if(TRUE == cfg->enableBorderReplicate)
                    {
                        blankInfo->hBlank =
                            gIssHalNsf3BlankInfo[modeCnt][1U].hBlank;
                        blankInfo->vBlank =
                            gIssHalNsf3BlankInfo[modeCnt][1U].vBlank;
                    }
                    else
                    {
                        blankInfo->hBlank =
                            gIssHalNsf3BlankInfo[modeCnt][0U].hBlank;
                        blankInfo->vBlank =
                            gIssHalNsf3BlankInfo[modeCnt][0U].vBlank;
                    }
                    break;
                }
            }
            break;
        }
        case VPS_HAL_ISS_IOCTL_START:
        {
            issCtrlProcMode_t procMode;

            /* NULL Parameter Check */
            GT_assert(VpsHalTrace, (NULL != cmdArgs));

            procMode = *(issCtrlProcMode_t *)cmdArgs;

            /* Set the processing mode */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + NSF3V_CFG);
            regVal &= ~((UInt32) NSF3V_CFG_ONESHOT_MASK);
            if(ISSHAL_ISS_PROC_MODE_ONE_SHOT == procMode)
            {
                regVal |= NSF3V_CFG_ONESHOT_MASK;
            }
            HW_WR_REG32(pInstObj->baseAddress + NSF3V_CFG, regVal);

            /* TODO: Is this register shadow, can this be done at any time? */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + NSF3V_CTRL);
            regVal |= NSF3V_CTRL_EN_MASK;
            HW_WR_REG32(pInstObj->baseAddress + NSF3V_CTRL, regVal);

            break;
        }
        case VPS_HAL_ISS_IOCTL_STOP:
        {
            /* TODO: Is this register shadow, can this be done at any time? */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + NSF3V_CTRL);
            regVal &= ~((UInt32) NSF3V_CTRL_EN_MASK);
            HW_WR_REG32(pInstObj->baseAddress + NSF3V_CTRL, regVal);
            break;
        }
        default:
        {
            status = FVID2_EUNSUPPORTED_CMD;
            break;
        }
    }

    return (status);
}

/* Function to start the NSF3 module either in one shot or in free
 * running mode */
int32_t VpsHal_issnsf3Start(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg)
{
    int32_t              status = FVID2_SOK;
    volatile uint32_t    regVal;
    isshalnsf3InstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalnsf3InstObj_t *) handle;

    regVal  = HW_RD_REG32(pInstObj->baseAddress + NSF3V_CFG);
    regVal &= ~((UInt32) NSF3V_CFG_ONESHOT_MASK);
    if(ISSHAL_ISS_PROC_MODE_ONE_SHOT == procMode)
    {
        regVal |= NSF3V_CFG_ONESHOT_MASK;
    }
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_CFG, regVal);

    /* TODO: Is this register shadow, can this be done at any time? */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + NSF3V_CTRL);
    regVal |= NSF3V_CTRL_EN_MASK;
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_CTRL, regVal);

    return (status);
}

/* Function to stop the NSF3 module when it is operating in free running mode */
int32_t VpsHal_issnsf3Stop(
    VpsHal_Handle handle,
    Ptr           arg)
{
    int32_t              status = FVID2_SOK;
    volatile uint32_t    regVal;
    isshalnsf3InstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalnsf3InstObj_t *) handle;

    /* TODO: Is this register shadow, can this be done at any time? */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + NSF3V_CTRL);
    regVal &= ~((UInt32) NSF3V_CTRL_EN_MASK);
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_CTRL, regVal);

    return (status);
}

/* Function to set the Fractional Clock Divisor */
int32_t VpsHal_issnsf3SetFractClkDiv(VpsHal_Handle handle, uint32_t fractClk)
{
    int32_t              status   = FVID2_SOK;
    isshalnsf3InstObj_t *pInstObj = NULL;
    volatile uint32_t    regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalnsf3InstObj_t *) handle;

    if((fractClk >
        (NSF3V_VPOUT_CTRL_PCLK_MASK >> NSF3V_VPOUT_CTRL_PCLK_SHIFT)) ||
       (0U == fractClk))
    {
        status = FVID2_EINVALID_PARAMS;
    }
    else
    {
        regVal = HW_RD_REG32(pInstObj->baseAddress + NSF3V_VPOUT_CTRL);
        regVal = (fractClk << NSF3V_VPOUT_CTRL_PCLK_SHIFT) &
                 NSF3V_VPOUT_CTRL_PCLK_MASK;
        HW_WR_REG32(pInstObj->baseAddress + NSF3V_VPOUT_CTRL, regVal);
    }

    return (status);
}

int32_t VpsHal_issnsf3SetFrameSize(
    VpsHal_Handle                      handle,
    const isshalnsf3FrameSizeParams_t *cfg,
    Ptr                                arg)
{
    uint32_t regVal;
    isshalnsf3InstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));

    pInstObj = (isshalnsf3InstObj_t *) handle;

    /* Set the Image Size */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + NSF3V_DIM);
    regVal &= ~(NSF3V_DIM_IW_MASK | NSF3V_DIM_IH_MASK);
    regVal |= ((cfg->width << NSF3V_DIM_IW_SHIFT) &
               NSF3V_DIM_IW_MASK) |
              ((cfg->height << NSF3V_DIM_IH_SHIFT) &
               NSF3V_DIM_IH_MASK);
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_DIM, regVal);

    return (FVID2_SOK);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

void Nsf3Reset(const isshalnsf3InstObj_t *instObj)
{
    volatile uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));

    regVal  = HW_RD_REG32(instObj->baseAddress + NSF3V_SYSCONFIG);
    regVal |= NSF3V_SYSCONFIG_SOFTRESET_MASK;
    HW_WR_REG32(instObj->baseAddress + NSF3V_SYSCONFIG, regVal);

    BspOsal_sleep(1U);
}

int32_t Nsf3SetEdgeEnhcConfig(
    const isshalnsf3InstObj_t          *pInstObj,
    const vpsissNsf3EdgeEnhnceConfig_t *eeCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t coeffRegAddr;
    uint32_t regVal;
    uint32_t clCnt;
    uint32_t cnt;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != pInstObj));
    GT_assert(VpsHalTrace, (NULL != eeCfg));

    regVal = HW_RD_REG32(pInstObj->baseAddress + NSF3V_CFG);

    regVal &= ~((UInt32) NSF3V_CFG_EE_EN_MASK);
    if(TRUE == eeCfg->enable)
    {
        regVal |= NSF3V_CFG_EE_EN_MASK;
    }
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_CFG, regVal);

    coeffRegAddr = pInstObj->baseAddress + NSF3V_EE_C00;
    for(clCnt = 0U; clCnt < ISSHAL_NSF3_MAX_COLOR; clCnt++)
    {
        for(cnt = 0U; cnt < ISSHAL_NSF3_EE_MAX_LEVEL; cnt++)
        {
            regVal = HW_RD_REG32(coeffRegAddr);

            regVal &= ~(NSF3V_EE_C00_L1_LH_MASK | NSF3V_EE_C00_L1_HH_MASK);

            regVal |= (((eeCfg->hhSubbandMax[clCnt][cnt] <<
                         NSF3V_EE_C00_L1_HH_SHIFT) &
                        NSF3V_EE_C00_L1_HH_MASK) |
                       ((eeCfg->lhSubbandMax[clCnt][cnt] <<
                         NSF3V_EE_C00_L1_LH_SHIFT) &
                        NSF3V_EE_C00_L1_LH_MASK));

            HW_WR_REG32(coeffRegAddr, regVal);

            coeffRegAddr += 4U;
        }
    }

    regVal = HW_RD_REG32(pInstObj->baseAddress + NSF3V_DS_THR);

    regVal &= ~(NSF3V_DS_THR_THR1_MASK | NSF3V_DS_THR_THR2_MASK);
    regVal |= (((eeCfg->deSaturateThreshold1 << NSF3V_DS_THR_THR1_SHIFT) &
                NSF3V_DS_THR_THR1_MASK) |
               ((eeCfg->deSaturateThreshold2 << NSF3V_DS_THR_THR2_SHIFT) &
                NSF3V_DS_THR_THR2_MASK));

    HW_WR_REG32(pInstObj->baseAddress + NSF3V_DS_THR, regVal);

    regVal = HW_RD_REG32(pInstObj->baseAddress + NSF3V_DS_SLOPE);

    regVal &= ~(NSF3V_DS_SLOPE_SLOPE1_MASK | NSF3V_DS_SLOPE_SLOPE2_MASK);
    regVal |= (((eeCfg->deSaturateSlope1 << NSF3V_DS_SLOPE_SLOPE1_SHIFT) &
                NSF3V_DS_SLOPE_SLOPE1_MASK) |
               ((eeCfg->deSaturateSlope2 << NSF3V_DS_SLOPE_SLOPE2_SHIFT) &
                NSF3V_DS_SLOPE_SLOPE2_MASK));

    HW_WR_REG32(pInstObj->baseAddress + NSF3V_DS_SLOPE, regVal);

    return (status);
}

int32_t Nsf3SetShadGainConfig(
    const isshalnsf3InstObj_t         *pInstObj,
    const vpsissNsf3ShadeGainConfig_t *sgCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != pInstObj));
    GT_assert(VpsHalTrace, (NULL != sgCfg));

    regVal = HW_RD_REG32(pInstObj->baseAddress + NSF3V_CFG);

    regVal &= ~((UInt32) NSF3V_CFG_SHD_EN_MASK);
    if(TRUE == sgCfg->enable)
    {
        regVal |= NSF3V_CFG_SHD_EN_MASK;
    }
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_CFG, regVal);

    /* Set the Shading gain starting coordinates */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + NSF3V_SHD_ST);
    regVal &= ~(NSF3V_SHD_ST_X_MASK | NSF3V_SHD_ST_Y_MASK);

    regVal |= (((sgCfg->pos.startX << NSF3V_SHD_ST_X_SHIFT) &
                NSF3V_SHD_ST_X_MASK) |
               ((sgCfg->pos.startY << NSF3V_SHD_ST_Y_SHIFT) &
                NSF3V_SHD_ST_Y_MASK));
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_SHD_ST, regVal);

    /* Set the Shading gain HA1/2 Coefficients */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + NSF3V_SHD_HA);
    regVal &= ~(NSF3V_SHD_HA_HA1_MASK | NSF3V_SHD_HA_HA2_MASK);

    regVal |= (((sgCfg->haCoeff[0U] << NSF3V_SHD_HA_HA1_SHIFT) &
                NSF3V_SHD_HA_HA1_MASK) |
               ((sgCfg->haCoeff[1U] << NSF3V_SHD_HA_HA2_SHIFT) &
                NSF3V_SHD_HA_HA2_MASK));
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_SHD_HA, regVal);

    /* Set the Shading gain VA1/2 Coefficients */
    regVal = HW_RD_REG32(pInstObj->baseAddress + NSF3V_SHD_VA);

    regVal &= ~(NSF3V_SHD_VA_VA1_MASK | NSF3V_SHD_VA_VA2_MASK);

    regVal |= (((sgCfg->vaCoeff[0U] << NSF3V_SHD_VA_VA1_SHIFT) &
                NSF3V_SHD_VA_VA1_MASK) |
               ((sgCfg->vaCoeff[1U] << NSF3V_SHD_VA_VA2_SHIFT) &
                NSF3V_SHD_VA_VA2_MASK));
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_SHD_VA, regVal);

    regVal = HW_RD_REG32(pInstObj->baseAddress + NSF3V_SHD_HSVS);

    regVal &= ~((UInt32) NSF3V_SHD_HSVS_S0_MASK);
    regVal |= (sgCfg->s0ShiftCnt << NSF3V_SHD_HSVS_S0_SHIFT) &
              NSF3V_SHD_HSVS_S0_MASK;

    regVal &= ~((UInt32) NSF3V_SHD_HSVS_HS1_MASK);
    regVal |= (sgCfg->hs1ShiftCnt << NSF3V_SHD_HSVS_HS1_SHIFT) &
              NSF3V_SHD_HSVS_HS1_MASK;

    regVal &= ~((UInt32) NSF3V_SHD_HSVS_HS2_MASK);
    regVal |= (sgCfg->hs2BitCnt << NSF3V_SHD_HSVS_HS2_SHIFT) &
              NSF3V_SHD_HSVS_HS2_MASK;

    regVal &= ~((UInt32) NSF3V_SHD_HSVS_HCS_MASK);
    regVal |= (sgCfg->hscShiftCnt << NSF3V_SHD_HSVS_HCS_SHIFT) &
              NSF3V_SHD_HSVS_HCS_MASK;

    regVal &= ~((UInt32) NSF3V_SHD_HSVS_VS2_MASK);
    regVal |= (sgCfg->vs2ShiftCnt << NSF3V_SHD_HSVS_VS2_SHIFT) &
              NSF3V_SHD_HSVS_VS2_MASK;

    regVal &= ~((UInt32) NSF3V_SHD_HSVS_VS1_MASK);
    regVal |= (sgCfg->vs1BitCnt << NSF3V_SHD_HSVS_VS1_SHIFT) &
              NSF3V_SHD_HSVS_VS1_MASK;

    regVal &= ~((UInt32) NSF3V_SHD_HSVS_VCS_MASK);
    regVal |= (sgCfg->vcsShiftCnt << NSF3V_SHD_HSVS_VCS_SHIFT) &
              NSF3V_SHD_HSVS_VCS_MASK;

    HW_WR_REG32(pInstObj->baseAddress + NSF3V_SHD_HSVS, regVal);

    /* Set the Gain Adjustment and its offset */
    regVal = HW_RD_REG32(pInstObj->baseAddress + NSF3V_SHD_ADJ);

    regVal &= ~((UInt32) (NSF3V_SHD_ADJ_GADJ_MASK | NSF3V_SHD_ADJ_OADJ_MASK));
    regVal |= ((sgCfg->OfstAdj << NSF3V_SHD_ADJ_OADJ_SHIFT) &
               NSF3V_SHD_ADJ_OADJ_MASK) |
              ((sgCfg->adj << NSF3V_SHD_ADJ_GADJ_SHIFT) &
               NSF3V_SHD_ADJ_GADJ_MASK);

    HW_WR_REG32(pInstObj->baseAddress + NSF3V_SHD_ADJ, regVal);

    /* Set the Gain Limit */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + NSF3V_SHD_MAXG);
    regVal &= ~((UInt32) NSF3V_SHD_MAXG_MASK);
    regVal |= (sgCfg->maxShadGain << NSF3V_SHD_MAXG_SHIFT) &
              NSF3V_SHD_MAXG_MASK;
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_SHD_MAXG, regVal);

    return (status);
}

int32_t Nsf3SetNsfThrsldConfig(
    const isshalnsf3InstObj_t            *pInstObj,
    const vpsissNsf3NoiseThrshldConfig_t *nsCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t coeffRegAddr;
    uint32_t regVal;
    uint32_t cnt;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != pInstObj));
    GT_assert(VpsHalTrace, (NULL != nsCfg));

    coeffRegAddr = pInstObj->baseAddress + NSF3V_TN_C00;
    for(cnt = 0U; cnt < ISSHAL_NSF3_MAX_COLOR; cnt++)
    {
        /* Horizontal Pos0 is fixed to 0 */
        regVal  = HW_RD_REG32(coeffRegAddr);
        regVal &= ~NSF3V_TN_C00_S0_Y_MASK;
        regVal |= (nsCfg->vertPos[cnt][0U] << NSF3V_TN_C00_S0_Y_SHIFT) &
                  NSF3V_TN_C00_S0_Y_MASK;
        HW_WR_REG32(coeffRegAddr, regVal);

        regVal  = HW_RD_REG32(coeffRegAddr + 4U);
        regVal &= ~(NSF3V_TN_C01_S0_S_MASK | NSF3V_TN_C01_S1_X_MASK);

        regVal |= ((nsCfg->horzPos[cnt][1U] << NSF3V_TN_C01_S1_X_SHIFT) &
                   NSF3V_TN_C01_S1_X_MASK) |
                  ((nsCfg->slope[cnt][0U] << NSF3V_TN_C01_S0_S_SHIFT) &
                   NSF3V_TN_C01_S0_S_MASK);

        HW_WR_REG32(coeffRegAddr + 4U, regVal);

        regVal  = HW_RD_REG32(coeffRegAddr + 8U);
        regVal &= ~(NSF3V_TN_C02_S1_Y_MASK | NSF3V_TN_C02_S1_S_MASK);

        regVal |= ((nsCfg->slope[cnt][1U] << NSF3V_TN_C02_S1_S_SHIFT) &
                   NSF3V_TN_C02_S1_S_MASK) |
                  ((nsCfg->vertPos[cnt][1U] << NSF3V_TN_C02_S1_Y_SHIFT) &
                   NSF3V_TN_C02_S1_Y_MASK);
        HW_WR_REG32(coeffRegAddr + 8U, regVal);

        regVal  = HW_RD_REG32(coeffRegAddr + 0xCU);
        regVal &= ~(NSF3V_TN_C03_S2_X_MASK | NSF3V_TN_C03_S2_Y_MASK);

        regVal |= ((nsCfg->horzPos[cnt][2U] << NSF3V_TN_C03_S2_X_SHIFT) &
                   NSF3V_TN_C03_S2_X_MASK) |
                  ((nsCfg->vertPos[cnt][2U] << NSF3V_TN_C03_S2_Y_SHIFT) &
                   NSF3V_TN_C03_S2_Y_MASK);
        HW_WR_REG32(coeffRegAddr + 0xCU, regVal);

        regVal  = HW_RD_REG32(coeffRegAddr + 0x10U);
        regVal &= ~(NSF3V_TN_C04_S2_S_MASK | NSF3V_TN_C04_S3_X_MASK);
        regVal |= ((nsCfg->slope[cnt][2U] << NSF3V_TN_C04_S2_S_SHIFT) &
                   NSF3V_TN_C04_S2_S_MASK) |
                  ((nsCfg->horzPos[cnt][3U] << NSF3V_TN_C04_S3_X_SHIFT) &
                   NSF3V_TN_C04_S3_X_MASK);
        HW_WR_REG32(coeffRegAddr + 0x10U, regVal);

        regVal  = HW_RD_REG32(coeffRegAddr + 0x14U);
        regVal &= ~(NSF3V_TN_C05_S3_Y_MASK | NSF3V_TN_C05_S3_S_MASK);
        regVal |= ((nsCfg->vertPos[cnt][3U] << NSF3V_TN_C05_S3_Y_SHIFT) &
                   NSF3V_TN_C05_S3_Y_MASK) |
                  ((nsCfg->slope[cnt][3U] << NSF3V_TN_C05_S3_S_SHIFT) &
                   NSF3V_TN_C05_S3_S_MASK);
        HW_WR_REG32(coeffRegAddr + 0x14U, regVal);

        coeffRegAddr += (NSF3V_TN_C10 - NSF3V_TN_C00);
    }

    regVal  = HW_RD_REG32(pInstObj->baseAddress + NSF3V_TN_SCALE);
    regVal &= ~(NSF3V_TN_SCALE_TN1_TO_TN2_MASK |
                NSF3V_TN_SCALE_TN3_TO_TN2_MASK);
    regVal |= (((nsCfg->scaleFactorTn1 << NSF3V_TN_SCALE_TN1_TO_TN2_SHIFT) &
                NSF3V_TN_SCALE_TN1_TO_TN2_MASK) |
               ((nsCfg->scaleFactorTn3 << NSF3V_TN_SCALE_TN3_TO_TN2_SHIFT) &
                NSF3V_TN_SCALE_TN3_TO_TN2_MASK));
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_TN_SCALE, regVal);

    regVal = HW_RD_REG32(pInstObj->baseAddress + NSF3V_THR_KNEE);
    for(cnt = 0U; cnt < ISSHAL_NSF3_MAX_KNEE_POINTS; cnt++)
    {
        regVal &= ~Nsf3GetThrKneeMask(cnt);
        regVal |= (nsCfg->kneePoint[cnt] << Nsf3GetThrKneeShift(cnt)) &
                  Nsf3GetThrKneeMask(cnt);
    }
    HW_WR_REG32(pInstObj->baseAddress + NSF3V_THR_KNEE, regVal);

    return (status);
}

static inline uint32_t Nsf3GetThrKneeShift(uint32_t cnt)
{
    return (cnt * 8U);
}

static inline uint32_t Nsf3GetThrKneeMask(uint32_t cnt)
{
    return ((uint32_t)0x000000FFU << ((cnt) * (uint32_t)8U));
}

