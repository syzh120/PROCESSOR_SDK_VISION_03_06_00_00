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
 *  \file isshal_isslvdsrx.c
 *
 *  \brief File containing the ISS LVDSRX HAL init, deinit and other common
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
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/csl/cslr_iss.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_iss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_isslvdsrx.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define LVDSRX_CAMERA_CFG_DIFF      (LVDSRX_CAM2_CFG - LVDSRX_CAM1_CFG)

#define LVDSRX_CAM_CFG              (0x0U)
#define LVDSRX_CAM_FRMSIZE          (0x4U)
#define LVDSRX_CAM_MAXWIDTH         (0x8U)
#define LVDSRX_CAM_SYNCSOF          (0xCU)
#define LVDSRX_CAM_SYNCEOF          (0x10U)
#define LVDSRX_CAM_SYNCSOL          (0x14U)
#define LVDSRX_CAM_SYNCEOL          (0x18U)
#define LVDSRX_CAM_SYNCSOV          (0x1CU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct isshallvdsrxInstObj
{
    uint32_t isInitDone;
    /**< Flag to indicate whether init is done or not */
    uint32_t instId;
    /**< Id of the instance */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t openCnt;
    /**< Open count */
    uint32_t maxPhys;
    /**< Maximum number of PHY supported */
    uint32_t maxLanesPerPhy;
    /**< Maximum number of lanes supported per phy */
} isshallvdsrxInstObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void LvdsrxReset(VpsHal_Handle handle);
static inline uint32_t LvdsRxCameraOffset(uint32_t n);

static inline uint32_t LvdsRxCameraOffset(uint32_t n)
{
    return (LVDSRX_CAM1_CFG + (LVDSRX_CAMERA_CFG_DIFF * n));
}

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshallvdsrxInstObj_t gIsshallvdsrxInstObjs[ISSHAL_LVDSRX_MAX_INST] =
{
    (uint32_t)FALSE
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_isslvdsrxInit(UInt32                          numInst,
                             const isshallvdsrxInstParams_t *instPrms,
                             Ptr                             arg)
{
    uint32_t instCnt;
    isshallvdsrxInstObj_t *pInstObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= ISSHAL_LVDSRX_MAX_INST));
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
         * lvdsrx number of instances. The size of this number of instances
         * is never more than ISSHAL_LVDSRX_MAX_INST.
         */
        GT_assert(VpsHalTrace,
                  (instPrms[instCnt].instId < ISSHAL_LVDSRX_INST_MAX_ID));

        pInstObj = &gIsshallvdsrxInstObjs[instCnt];

        if((uint32_t)FALSE == pInstObj->isInitDone)
        {
            pInstObj->openCnt        = 0U;
            pInstObj->instId         = instPrms[instCnt].instId;
            pInstObj->baseAddress    = instPrms[instCnt].baseAddress;
            pInstObj->maxPhys        = instPrms[instCnt].maxPhys;
            pInstObj->maxLanesPerPhy = instPrms[instCnt].maxLanesPerPhy;
            pInstObj->isInitDone     = (uint32_t)TRUE;
        }
    }

    return (FVID2_SOK);
}

int32_t VpsHal_isslvdsrxDeInit(Ptr arg)
{
    uint32_t instCnt;
    isshallvdsrxInstObj_t *pInstObj;

    for(instCnt = 0U; instCnt < ISSHAL_LVDSRX_INST_MAX_ID; instCnt++)
    {
        pInstObj = &gIsshallvdsrxInstObjs[instCnt];

        /* None of the instance should be opened at this time */
        if(pInstObj->openCnt != 0)
        {
            GT_0trace(VpsHalTrace, GT_INFO,
                      "WARNING: ISS_LVDSRX: Instance openCnt is NOT zero !!!\r\n");
        }

        /* Reset instance id and base address */
        pInstObj->instId      = 0x0U;
        pInstObj->baseAddress = 0x0U;
        pInstObj->isInitDone  = (uint32_t)FALSE;
    }

    return (FVID2_SOK);
}

VpsHal_Handle VpsHal_isslvdsrxOpen(
    const isshallvdsrxOpenParams_t *openPrms,
    Ptr                             arg)
{
    int32_t                status;
    uint32_t               instCnt;
    VpsHal_Handle          handle   = NULL;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, (NULL != openPrms));

    for(instCnt = 0U; instCnt < ISSHAL_LVDSRX_MAX_INST; instCnt++)
    {
        pInstObj = &(gIsshallvdsrxInstObjs[instCnt]);

        /* Return the matching instance handle */
        if(openPrms->instId == pInstObj->instId)
        {
            handle = (VpsHal_Handle) (pInstObj);

            /* Check whether some one has already opened this instance */
            if(0 == pInstObj->openCnt)
            {
                /* For the very first time, power up and reset */
                status = VpsHal_issPowerCtrl(SUB_MODULE_LVDSRX, (uint32_t) TRUE);
                if(FVID2_SOK == status)
                {
                    /* LvdsrxReset(pInstObj); */
                }
                else
                {
                    GT_assert(VpsHalTrace, FALSE);
                    handle = NULL;
                }
            }

            pInstObj->openCnt++;
            break;
        }
    }

    return (handle);
}

int32_t VpsHal_isslvdsrxClose(VpsHal_Handle handle, Ptr arg)
{
    int32_t status = FVID2_EFAIL;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshallvdsrxInstObj_t *) handle;

    /* Decrement the open count */
    if(pInstObj->openCnt > 0)
    {
        pInstObj->openCnt--;
        status = FVID2_SOK;
    }

    if(0U == pInstObj->openCnt)
    {
        status = VpsHal_issPowerCtrl(SUB_MODULE_LVDSRX, (uint32_t) FALSE);
        GT_assert(VpsHalTrace, (FVID2_SOK == status));
    }

    return (status);
}

int32_t VpsHal_isslvdsrxSetConfig(VpsHal_Handle               handle,
                                  const isshallvdsrxConfig_t *cfg,
                                  Ptr                         arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal, temp;
    uint32_t cnt;
    uint32_t tempMask, diffMask;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));

    pInstObj = (isshallvdsrxInstObj_t *) handle;

    /* Check for the maximum number of phys and lanes per phy */
    if(pInstObj->maxPhys < cfg->numPhys)
    {
        status = FVID2_EINVALID_PARAMS;
    }
    else
    {
        for(cnt = 0U; cnt < cfg->numPhys; cnt++)
        {
            if(pInstObj->maxLanesPerPhy < cfg->numLanes[cnt])
            {
                status = FVID2_EINVALID_PARAMS;
                break;
            }
        }
    }

    /* Check the Bits per pixel */
    if((FVID2_BPP_BITS8 != cfg->bpp) &&
       (FVID2_BPP_BITS10 != cfg->bpp) &&
       (FVID2_BPP_BITS12 != cfg->bpp) &&
       (FVID2_BPP_BITS14 != cfg->bpp) &&
       (FVID2_BPP_BITS16 != cfg->bpp))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    /* Check for the maximum size */
    if((cfg->frameWidth >
        (LVDSRX_CAM1_FRMSIZE_LNWIDTH_MASK >>
         LVDSRX_CAM1_FRMSIZE_LNWIDTH_SHIFT)) ||
       (cfg->frameHeight >
        (LVDSRX_CAM1_FRMSIZE_FRWIDTH_MASK >>
         LVDSRX_CAM1_FRMSIZE_FRWIDTH_SHIFT)) ||
       (cfg->maxWidth >
        (LVDSRX_CAM1_MAXWIDTH_MASK >>
         LVDSRX_CAM1_MAXWIDTH_SHIFT)))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        /* Set the Start VBlanking sync pattern */
        regVal =
            (cfg->sovblkPtn.bitMask << LVDSRX_CAM1_SYNCSOV_BITMASK_SHIFT) &
            LVDSRX_CAM1_SYNCSOV_BITMASK_MASK;
        regVal |=
            (cfg->sovblkPtn.pattern << LVDSRX_CAM1_SYNCSOV_SOFPTN_SHIFT) &
            LVDSRX_CAM1_SYNCSOV_SOFPTN_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_SYNCSOV, regVal);

        /* Set the End of Line sync pattern */
        regVal = (cfg->eolPtn.bitMask << LVDSRX_CAM1_SYNCEOL_BITMASK_SHIFT) &
                 LVDSRX_CAM1_SYNCEOL_BITMASK_MASK;
        regVal |= (cfg->eolPtn.pattern << LVDSRX_CAM1_SYNCEOL_SOFPTN_SHIFT) &
                  LVDSRX_CAM1_SYNCEOL_SOFPTN_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_SYNCEOL, regVal);

        /* Set the Start of Line sync pattern */
        regVal = (cfg->solPtn.bitMask << LVDSRX_CAM1_SYNCSOL_BITMASK_SHIFT) &
                 LVDSRX_CAM1_SYNCSOL_BITMASK_MASK;
        regVal |= (cfg->solPtn.pattern << LVDSRX_CAM1_SYNCSOL_SOFPTN_SHIFT) &
                  LVDSRX_CAM1_SYNCSOL_SOFPTN_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_SYNCSOL, regVal);

        /* Set the End of Frame sync pattern */
        regVal = (cfg->eofPtn.bitMask << LVDSRX_CAM1_SYNCEOF_BITMASK_SHIFT) &
                 LVDSRX_CAM1_SYNCEOF_BITMASK_MASK;
        regVal |= (cfg->eofPtn.pattern << LVDSRX_CAM1_SYNCEOF_SOFPTN_SHIFT) &
                  LVDSRX_CAM1_SYNCEOF_SOFPTN_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_SYNCEOF, regVal);

        /* Set the Start of Frame sync pattern */
        regVal = (cfg->sofPtn.bitMask << LVDSRX_CAM1_SYNCSOF_BITMASK_SHIFT) &
                 LVDSRX_CAM1_SYNCSOF_BITMASK_MASK;
        regVal |= (cfg->sofPtn.pattern << LVDSRX_CAM1_SYNCSOF_SOFPTN_SHIFT) &
                  LVDSRX_CAM1_SYNCSOF_SOFPTN_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_SYNCSOF, regVal);

        /* Set the frame size */
        regVal = (cfg->frameWidth << LVDSRX_CAM1_FRMSIZE_LNWIDTH_SHIFT) &
                 LVDSRX_CAM1_FRMSIZE_LNWIDTH_MASK;
        regVal |= (cfg->frameHeight << LVDSRX_CAM1_FRMSIZE_FRWIDTH_SHIFT) &
                  LVDSRX_CAM1_FRMSIZE_FRWIDTH_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_FRMSIZE, regVal);

        /* Set the Max Frame width */
        regVal = HW_RD_REG32(pInstObj->baseAddress +
                             LvdsRxCameraOffset(cfg->inputCamId) +
                             LVDSRX_CAM_MAXWIDTH);
        regVal &= ~((UInt32) LVDSRX_CAM1_MAXWIDTH_MASK);
        regVal |= (cfg->maxWidth << LVDSRX_CAM1_MAXWIDTH_SHIFT) &
                  LVDSRX_CAM1_MAXWIDTH_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_MAXWIDTH, regVal);

        regVal = HW_RD_REG32(pInstObj->baseAddress +
                             LvdsRxCameraOffset(cfg->inputCamId) +
                             LVDSRX_CAM_CFG);

        regVal &= ~((UInt32) LVDSRX_CAM1_CFG_OP_MODE_MASK);
        regVal |= (cfg->opMode << LVDSRX_CAM1_CFG_OP_MODE_SHIFT) &
                  LVDSRX_CAM1_CFG_OP_MODE_MASK;

        regVal &= ~((UInt32) LVDSRX_CAM1_CFG_NUMPHY_MASK);
        regVal |= (cfg->numPhys << LVDSRX_CAM1_CFG_NUMPHY_SHIFT) &
                  LVDSRX_CAM1_CFG_NUMPHY_MASK;

        regVal &= ~((UInt32) LVDSRX_CAM1_CFG_PIX_WIDTH_MASK);
        if(FVID2_BPP_BITS8 == cfg->bpp)
        {
            temp   = ((UInt32)0x0U << (UInt32)LVDSRX_CAM1_CFG_PIX_WIDTH_SHIFT);
            regVal = regVal | temp;
        }
        else if(FVID2_BPP_BITS10 == cfg->bpp)
        {
            temp    = ((UInt32)0x1U << (UInt32)LVDSRX_CAM1_CFG_PIX_WIDTH_SHIFT);
            regVal |= temp;
        }
        else if(FVID2_BPP_BITS12 == cfg->bpp)
        {
            temp    = ((UInt32)0x2U << (UInt32)LVDSRX_CAM1_CFG_PIX_WIDTH_SHIFT);
            regVal |= temp;
        }
        else if(FVID2_BPP_BITS14 == cfg->bpp)
        {
            temp    = ((UInt32)0x3U << (UInt32)LVDSRX_CAM1_CFG_PIX_WIDTH_SHIFT);
            regVal |= temp;
        }
        else /* 16bpp */
        {
            temp    = ((UInt32)0x4U << (UInt32)LVDSRX_CAM1_CFG_PIX_WIDTH_SHIFT);
            regVal |= temp;
        }

        for(cnt = 0U; cnt < cfg->numPhys; cnt++)
        {
            diffMask = (LVDSRX_CAM1_CFG_NUM_LANE2_SHIFT -
                        LVDSRX_CAM1_CFG_NUM_LANE1_SHIFT) * cnt;

            tempMask =
                LVDSRX_CAM1_CFG_NUM_LANE1_MASK << diffMask;

            regVal &= ~tempMask;

            regVal |= (cfg->numLanes[cnt] <<
                       (LVDSRX_CAM1_CFG_NUM_LANE1_SHIFT + diffMask)) &
                      tempMask;
        }

        regVal &= ~((UInt32) LVDSRX_CAM1_CFG_CRCEN_MASK);
        if(TRUE == cfg->enableCrcCheck)
        {
            regVal |= LVDSRX_CAM1_CFG_CRCEN_MASK;
        }

        regVal &= ~((UInt32) LVDSRX_CAM1_CFG_DENDIAN_MASK);
        if(TRUE == cfg->enableDataBigEndian)
        {
            regVal |= LVDSRX_CAM1_CFG_DENDIAN_MASK;
        }

        regVal &= ~((UInt32) LVDSRX_CAM1_CFG_SENDIAN_MASK);
        if(TRUE == cfg->enableSyncBigEndian)
        {
            regVal |= LVDSRX_CAM1_CFG_SENDIAN_MASK;
        }

        regVal &= ~((UInt32) LVDSRX_CAM1_CFG_FILEN_MASK);
        if(TRUE == cfg->enableFiller)
        {
            regVal |= LVDSRX_CAM1_CFG_FILEN_MASK;
        }

        regVal &= ~((UInt32) LVDSRX_CAM1_CFG_ALIGN_MASK);
        if(TRUE == cfg->enableMsbAlign)
        {
            regVal |= LVDSRX_CAM1_CFG_ALIGN_MASK;
        }

        /* TODO: Configure SENDIAN, DENDIAN, FRSTATE ?? */

        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_CFG, regVal);
    }

    return (status);
}

int32_t VpsHal_isslvdsrxControl(VpsHal_Handle handle,
                                UInt32        cmd,
                                Ptr           cmdArgs,
                                Ptr           arg)
{
    return (FVID2_SOK);
}

int32_t VpsHal_isslvdsrxStart(
    VpsHal_Handle               handle,
    issCtrlProcMode_t           procMode,
    isshallvdsrxInputCameraId_t inputCamId)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshallvdsrxInstObj_t *) handle;

    regVal = HW_RD_REG32(pInstObj->baseAddress + LVDSRX_CAMCFG);

    if(ISSHAL_LVDSRX_INPUT_CAM_ID0 == inputCamId)
    {
        regVal |= LVDSRX_CAMCFG_CAM1ENA_ENABLE;
    }
    else if(ISSHAL_LVDSRX_INPUT_CAM_ID1 == inputCamId)
    {
        regVal |= LVDSRX_CAMCFG_CAM2ENA_ENABLE;
    }
    else if(ISSHAL_LVDSRX_INPUT_CAM_ID2 == inputCamId)
    {
        regVal |= LVDSRX_CAMCFG_CAM3ENA_ENABLE;
    }
    else
    {
        regVal |= LVDSRX_CAMCFG_CAM4ENA_ENABLE;
    }

    HW_WR_REG32(pInstObj->baseAddress + LVDSRX_CAMCFG, regVal);

    return (status);
}

int32_t VpsHal_isslvdsrxStop(
    VpsHal_Handle               handle,
    isshallvdsrxInputCameraId_t inputCamId)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshallvdsrxInstObj_t *) handle;

    regVal = HW_RD_REG32(pInstObj->baseAddress + LVDSRX_CAMCFG);

    if(ISSHAL_LVDSRX_INPUT_CAM_ID0 == inputCamId)
    {
        regVal &= ~((UInt32) LVDSRX_CAMCFG_CAM1ENA_ENABLE);
    }
    else if(ISSHAL_LVDSRX_INPUT_CAM_ID1 == inputCamId)
    {
        regVal &= ~((UInt32) LVDSRX_CAMCFG_CAM2ENA_ENABLE);
    }
    else if(ISSHAL_LVDSRX_INPUT_CAM_ID2 == inputCamId)
    {
        regVal &= ~((UInt32) LVDSRX_CAMCFG_CAM3ENA_ENABLE);
    }
    else
    {
        regVal &= ~((UInt32) LVDSRX_CAMCFG_CAM4ENA_ENABLE);
    }

    HW_WR_REG32(pInstObj->baseAddress + LVDSRX_CAMCFG, regVal);

    return (status);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

void LvdsrxReset(VpsHal_Handle handle)
{
    uint32_t tempCnt;
    uint32_t regVal;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshallvdsrxInstObj_t *) handle;

    /* Assert the reset */
    regVal = HW_RD_REG32(pInstObj->baseAddress + LVDSRX_SYSCONFIG);
    regVal = regVal | LVDSRX_SYSCONFIG_RESERVED_MASK;
    HW_WR_REG32(pInstObj->baseAddress + LVDSRX_SYSCONFIG, regVal);

    regVal = HW_RD_REG32(pInstObj->baseAddress + LVDSRX_SYSCONFIG);

    /* Waits until reset is done */
    tempCnt = 0xFFFFU;
    while((0x0U != tempCnt) &&
          (regVal != LVDSRX_SYSCONFIG_RESERVED_PENDING))
    {
        tempCnt--;
        regVal = HW_RD_REG32(pInstObj->baseAddress + LVDSRX_SYSCONFIG);
    }

    GT_assert(VpsHalTrace, (0U < tempCnt));
}

