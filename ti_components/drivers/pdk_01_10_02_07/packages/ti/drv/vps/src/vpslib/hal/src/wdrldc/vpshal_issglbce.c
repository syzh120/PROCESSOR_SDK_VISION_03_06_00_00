/**
 *  \file isshal_glbce.c
 *
 *  \brief File containing the ISS GLBCE HAL init, deinit and other common
 *  functions.
 *
 */

/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 */
/*
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
#include "hw_iss_glbce.h"
#include <ti/csl/hw_types.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_iss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issglbce.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Minimum width supported by GLBCE
 */
#define ISS_HAL_GLBCE_MIN_WIDTH         (480U)

/* Minimum height supported by GLBCE
 */
#define ISS_HAL_GLBCE_MIN_HEIGHT        (240U)

/* Macro for FWD Perceptual table
 */
#define ISS_HAL_FWD_PERCEPT_CFG         (1U)

/* Macro for REV Perceptual table
 */
#define ISS_HAL_REV_PERCEPT_CFG         (2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct isshalglbceInstObj
{
    uint32_t isInitDone;
    /**< Flag to indicate whether init is done or not */
    uint32_t instId;
    /**< Id of the instance */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t glbceStatMemAddress;
    /**< GLBCE Statistics memory based address */
    uint32_t glbceStatMemSize;
    /**< GLBCE Statistics memory size */
    uint32_t openCnt;
    /**< Open count */
} isshalglbceInstObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t VpsHal_issglbceSetGlbceCfg(VpsHal_Handle              handle,
                                          const vpsissGlbceConfig_t *cfg);
static int32_t VpsHal_issglbceSetWdrConfig(VpsHal_Handle                 handle,
                                           const vpsissGlbceWdrConfig_t *cfg);
static int32_t VpsHal_issglbceSetPerceptConfig(
    VpsHal_Handle                     handle,
    const vpsissGlbcePerceptConfig_t *cfg,
    uint32_t                          perceptDir);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshalglbceInstObj_t      gIssHalGlbceInstObjs[ISSHAL_GLBCE_MAX_INST] =
{(uint32_t)FALSE};

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gIssHalGlbceDefCfg' visibility is too wide.
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * static global variable used in many functions, but not accessed by any
 * other file.
 */
static const isshalglbceConfig_t gIssHalGlbceDefCfg =
{
    720U,
    480U,
    {
        FALSE,                         /* Disables GLBCE processing */
        32U,                           /* IR Strength */
        0x0U,                          /* Blank Level */
        0xFFFFU,                       /* White Level */
        0x3U,                          /* Intensity Variance */
        0x6U,                          /* Space Variance */
        0x6U,                          /* Bright Amplification Limit */
        0x6U,                          /* Dark Amplification Limit */
        VPS_ISS_GLBCE_DITHER_FOUR_BIT, /* Dither Four Bits */
        64U,                           /* Slope Max Limit */
        128U,                          /* Slope Min Limit */
        /* Asymmetry Table */
        {
            0x0000U, 0x49f1U, 0x74d2U, 0x90d1U, 0xa487U, 0xb329U, 0xbe73U,
            0xc76eU, 0xcebdU, 0xd4ceU, 0xd9ebU, 0xde4bU, 0xe212U, 0xe55fU,
            0xe847U, 0xeadbU, 0xed29U, 0xef3bU, 0xf11aU, 0xf2cdU, 0xf45aU,
            0xf5c5U, 0xf714U, 0xf848U, 0xf965U, 0xfa6dU, 0xfb63U, 0xfc49U,
            0xfd20U, 0xfde9U, 0xfea6U, 0xff58U, 0xffffU
        }
    },
    {   /* Forward  Percept Configuration */
        TRUE,
        {
            0U,     4622U,  8653U,  11684U, 14195U, 16380U, 18335U,
            20118U, 21766U, 23304U, 24751U, 26119U, 27422U, 28665U,
            29857U, 31003U, 32108U, 33176U, 34209U, 35211U, 36185U,
            37132U, 38055U, 38955U, 39834U, 40693U, 41533U, 42355U,
            43161U, 43951U, 44727U, 45488U, 46236U, 46971U, 47694U,
            48405U, 49106U, 49795U, 50475U, 51145U, 51805U, 52456U,
            53099U, 53733U, 54360U, 54978U, 55589U, 56193U, 56789U,
            57379U, 57963U, 58539U, 59110U, 59675U, 60234U, 60787U,
            61335U, 61877U, 62414U, 62946U, 63473U, 63996U, 64513U,
            65026U, 65535U
        }
    },
    {   /* Reverse Percept Configuration */
        TRUE,
        {
            0U,     228U,   455U,   683U,   910U,   1138U,  1369U,
            1628U,  1912U,  2221U,  2556U,  2916U,  3304U,  3717U,
            4158U,  4626U,  5122U,  5645U,  6197U,  6777U,  7386U,
            8024U,  8691U,  9387U,  10113U, 10869U, 11654U, 12471U,
            13317U, 14194U, 15103U, 16042U, 17012U, 18014U, 19048U,
            20113U, 21210U, 22340U, 23501U, 24696U, 25922U, 27182U,
            28475U, 29800U, 31159U, 32552U, 33977U, 35437U, 36930U,
            38458U, 40019U, 41615U, 43245U, 44910U, 46609U, 48343U,
            50112U, 51916U, 53755U, 55630U, 57539U, 59485U, 61466U,
            63482U, 65535U
        }
    },
    {   /* WDR Configuration */
        FALSE,
        {
            0x0000U, 0x0100U, 0x0200U, 0x0300U, 0x0400U, 0x0500U, 0x0600U,
            0x0700U, 0x0800U, 0x0900U, 0x0A00U, 0x0B00U, 0x0C00U, 0x0D00U,
            0x0E00U, 0x0F00U, 0x1000U, 0x1100U, 0x1200U, 0x1300U, 0x1400U,
            0x1500U, 0x1600U, 0x1700U, 0x1800U, 0x1900U, 0x1A00U, 0x1B00U,
            0x1C00U, 0x1D00U, 0x1E00U, 0x1F00U, 0x2000U, 0x2100U, 0x2200U,
            0x2300U, 0x2400U, 0x2500U, 0x2600U, 0x2700U, 0x2800U, 0x2900U,
            0x2A00U, 0x2B00U, 0x2C00U, 0x2D00U, 0x2E00U, 0x2F00U, 0x3000U,
            0x3100U, 0x3200U, 0x3300U, 0x3400U, 0x3500U, 0x3600U, 0x3700U,
            0x3800U, 0x3900U, 0x3A00U, 0x3B00U, 0x3C00U, 0x3D00U, 0x3E00U,
            0x3F00U, 0x4000U, 0x4100U, 0x4200U, 0x4300U, 0x4400U, 0x4500U,
            0x4600U, 0x4700U, 0x4800U, 0x4900U, 0x4A00U, 0x4B00U, 0x4C00U,
            0x4D00U, 0x4E00U, 0x4F00U, 0x5000U, 0x5100U, 0x5200U, 0x5300U,
            0x5400U, 0x5500U, 0x5600U, 0x5700U, 0x5800U, 0x5900U, 0x5A00U,
            0x5B00U, 0x5C00U, 0x5D00U, 0x5E00U, 0x5F00U, 0x6000U, 0x6100U,
            0x6200U, 0x6300U, 0x6400U, 0x6500U, 0x6600U, 0x6700U, 0x6800U,
            0x6900U, 0x6A00U, 0x6B00U, 0x6C00U, 0x6D00U, 0x6E00U, 0x6F00U,
            0x7000U, 0x7100U, 0x7200U, 0x7300U, 0x7400U, 0x7500U, 0x7600U,
            0x7700U, 0x7800U, 0x7900U, 0x7A00U, 0x7B00U, 0x7C00U, 0x7D00U,
            0x7E00U, 0x7F00U, 0x8000U, 0x8100U, 0x8200U, 0x8300U, 0x8400U,
            0x8500U, 0x8600U, 0x8700U, 0x8800U, 0x8900U, 0x8A00U, 0x8B00U,
            0x8C00U, 0x8D00U, 0x8E00U, 0x8F00U, 0x9000U, 0x9100U, 0x9200U,
            0x9300U, 0x9400U, 0x9500U, 0x9600U, 0x9700U, 0x9800U, 0x9900U,
            0x9A00U, 0x9B00U, 0x9C00U, 0x9D00U, 0x9E00U, 0x9F00U, 0xA000U,
            0xA100U, 0xA200U, 0xA300U, 0xA400U, 0xA500U, 0xA600U, 0xA700U,
            0xA800U, 0xA900U, 0xAA00U, 0xAB00U, 0xAC00U, 0xAD00U, 0xAE00U,
            0xAF00U, 0xB000U, 0xB100U, 0xB200U, 0xB300U, 0xB400U, 0xB500U,
            0xB600U, 0xB700U, 0xB800U, 0xB900U, 0xBA00U, 0xBB00U, 0xBC00U,
            0xBD00U, 0xBE00U, 0xBF00U, 0xC000U, 0xC100U, 0xC200U, 0xC300U,
            0xC400U, 0xC500U, 0xC600U, 0xC700U, 0xC800U, 0xC900U, 0xCA00U,
            0xCB00U, 0xCC00U, 0xCD00U, 0xCE00U, 0xCF00U, 0xD000U, 0xD100U,
            0xD200U, 0xD300U, 0xD400U, 0xD500U, 0xD600U, 0xD700U, 0xD800U,
            0xD900U, 0xDA00U, 0xDB00U, 0xDC00U, 0xDD00U, 0xDE00U, 0xDF00U,
            0xE000U, 0xE100U, 0xE200U, 0xE300U, 0xE400U, 0xE500U, 0xE600U,
            0xE700U, 0xE800U, 0xE900U, 0xEA00U, 0xEB00U, 0xEC00U, 0xED00U,
            0xEE00U, 0xEF00U, 0xF000U, 0xF100U, 0xF200U, 0xF300U, 0xF400U,
            0xF500U, 0xF600U, 0xF700U, 0xF800U, 0xF900U, 0xFA00U, 0xFB00U,
            0xFC00U, 0xFD00U, 0xFE00U, 0xFF00U, 0xFFFFU
        }
    }
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_issglbceInit(
    uint32_t                       numInst,
    const isshalglbceInstParams_t *instPrms,
    Ptr                            arg)
{
    uint32_t instCnt;
    isshalglbceInstObj_t *instObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= ISSHAL_GLBCE_MAX_INST));
    GT_assert(VpsHalTrace, (NULL != instPrms));

    /* Set the default Values for non-changing parameters */
    for(instCnt = 0U; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  (NULL != instPrms));
        GT_assert(VpsHalTrace,
                  (instPrms->instId < ISSHAL_GLBCE_INST_MAX_ID));
        GT_assert(VpsHalTrace,
                  (NULL != instPrms->baseAddress));

        instObj = &gIssHalGlbceInstObjs[instCnt];

        if((uint32_t)FALSE == instObj->isInitDone)
        {
            instObj->openCnt     = 0U;
            instObj->instId      = instPrms->instId;
            instObj->baseAddress = instPrms->baseAddress;
            instObj->glbceStatMemAddress = instPrms->glbceStatMemAddress;
            instObj->glbceStatMemSize = instPrms->glbceStatMemSize;
            instObj->isInitDone  = (uint32_t)TRUE;
        }

        /* MISRA.PTR.ARITH
         * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
         * Pointer is accessed as an array
         * KW State: Defer -> Waiver -> Case by case
         * MISRAC_WAIVER: Pointer is accessed as an array.
         * This function is called by init function, which passes
         * glbce number of instances. The size of this number of instances
         * is never more than ISSHAL_GLBCE_INST_MAX_ID.
         */
        instPrms++;
    }

    return (BSP_SOK);
}

int32_t VpsHal_issglbceDeInit(Ptr arg)
{
    uint32_t instCnt;
    isshalglbceInstObj_t *instObj;

    for(instCnt = 0U; instCnt < ISSHAL_GLBCE_INST_MAX_ID; instCnt++)
    {
        instObj = &gIssHalGlbceInstObjs[instCnt];

        GT_assert(VpsHalTrace, (0U == instObj->openCnt));

        instObj->instId      = 0x0U;
        instObj->baseAddress = 0x0U;
        instObj->isInitDone  = (uint32_t)FALSE;
    }

    return (FVID2_SOK);
}

/**
 *  \brief This function should be called prior to calling any of the GLBCE HAL
 *  configuration APIs to get the instance handle.
 */
VpsHal_Handle VpsHal_issglbceOpen(const isshalOpenParams_t *openPrms,
                                  Ptr                       arg)
{
    uint32_t              instCnt;
    VpsHal_Handle         handle  = NULL;
    isshalglbceInstObj_t *instObj = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, (NULL != openPrms));

    for(instCnt = 0U; instCnt < ISSHAL_GLBCE_MAX_INST; instCnt++)
    {
        instObj = &(gIssHalGlbceInstObjs[instCnt]);

        /* Return the matching instance handle */
        if(openPrms->instId == instObj->instId)
        {
            handle = (VpsHal_Handle) instObj;

            /* Enable Module clock on first open */
            if(0U == instObj->openCnt)
            {
                /* Enable GLBCE Clock at the ISS Level */
                GT_assert(
                    VpsHalTrace,
                    (FVID2_SOK ==
                     VpsHal_issEnableModule(ISSHAL_ISS_MODULE_GLBCE,
                                            (uint32_t) TRUE)));

                /* TODO: Reset GLBCE here to reset statistics */
            }

            instObj->openCnt++;
            break;
        }
    }

    return (handle);
}

/**
 *  \brief This functions closes the glbce handle and after call to this
 *  function, glbce handle is not valid.
 */
int32_t VpsHal_issglbceClose(VpsHal_Handle handle,
                             Ptr           arg)
{
    int32_t status = FVID2_EFAIL;
    isshalglbceInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalglbceInstObj_t *) handle;

    /* Decrement the open count */
    if(instObj->openCnt > 0U)
    {
        instObj->openCnt--;

        if(0U == instObj->openCnt)
        {
            /* Disable GLBCE Clock at the ISS Level */
            GT_assert(
                VpsHalTrace,
                (FVID2_SOK ==
                 VpsHal_issEnableModule(ISSHAL_ISS_MODULE_GLBCE,
                                        (uint32_t) FALSE)));
        }

        status = FVID2_SOK;
    }

    return (status);
}

int32_t VpsHal_issglbceSetConfig(
    VpsHal_Handle              handle,
    const isshalglbceConfig_t *cfg,
    Ptr                        arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalglbceInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));

    instObj = (isshalglbceInstObj_t *) handle;

    /* Check for errors */
    if((ISS_HAL_GLBCE_MIN_WIDTH > cfg->width) ||
       (ISS_HAL_GLBCE_MIN_HEIGHT > cfg->height) ||
       (cfg->width > (ISS_GLBCE_FRAME_WIDTH_VAL_MASK >>
                      ISS_GLBCE_FRAME_WIDTH_VAL_SHIFT)) ||
       (cfg->height > (ISS_GLBCE_FRAME_HEIGHT_VAL_MASK >>
                       ISS_GLBCE_FRAME_HEIGHT_VAL_SHIFT)))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_FRAME_WIDTH);
        regVal &= ~((UInt32) ISS_GLBCE_FRAME_WIDTH_VAL_MASK);
        regVal |= (cfg->width << ISS_GLBCE_FRAME_WIDTH_VAL_SHIFT) &
                  ISS_GLBCE_FRAME_WIDTH_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_FRAME_WIDTH, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_FRAME_HEIGHT);
        regVal &= ~((UInt32) ISS_GLBCE_FRAME_HEIGHT_VAL_MASK);
        regVal |= (cfg->height << ISS_GLBCE_FRAME_HEIGHT_VAL_SHIFT) &
                  ISS_GLBCE_FRAME_HEIGHT_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_FRAME_HEIGHT, regVal);
    }

    if(FVID2_SOK == status)
    {
        status = VpsHal_issglbceSetGlbceCfg(handle, &cfg->glbceCfg);
    }

    if(FVID2_SOK == status)
    {
        status = VpsHal_issglbceSetWdrConfig(handle, &cfg->wdrCfg);
    }

    if(FVID2_SOK == status)
    {
        status = VpsHal_issglbceSetPerceptConfig(
            handle,
            &cfg->fwdPrcptCfg,
            ISS_HAL_FWD_PERCEPT_CFG);
    }

    if(FVID2_SOK == status)
    {
        status = VpsHal_issglbceSetPerceptConfig(
            handle,
            &cfg->revPrcptCfg,
            ISS_HAL_REV_PERCEPT_CFG);
    }
    return (status);
}

int32_t VpsHal_issglbceGetConfig(
    VpsHal_Handle        handle,
    isshalglbceConfig_t *config)
{
    return (FVID2_SOK);
}

/* Function to process any command */
int32_t VpsHal_issglbceControl(
    VpsHal_Handle handle,
    uint32_t      cmd,
    Ptr           cmdArgs,
    Ptr           arg)
{
    int32_t               status  = FVID2_SOK;
    isshalglbceInstObj_t *instObj = NULL;
    volatile uint32_t     regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    instObj = (isshalglbceInstObj_t *) handle;

    switch(cmd)
    {
        case VPS_HAL_ISS_IOCTL_START:
        {
            issCtrlProcMode_t procMode;

            /* NULL Parameter Check */
            GT_assert(VpsHalTrace, (NULL != cmdArgs));

            procMode = *(issCtrlProcMode_t *)cmdArgs;

            /* Set the processing mode */
            regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_MODE);
            regVal &= ~((UInt32) ISS_GLBCE_MODE_OST_MASK);
            if(ISSHAL_ISS_PROC_MODE_ONE_SHOT == procMode)
            {
                regVal |= ISS_GLBCE_MODE_OST_MASK;
            }
            HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_MODE, regVal);

            /* Enable Glbce engine, all the parameters must be set before
             * enabling this */
            regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0);
            regVal |= ISS_GLBCE_CONTROL0_ONOFF_MASK;
            HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0, regVal);

            break;
        }
        case ISSHAL_IOCTL_GLBCE_SET_FRAME_CFG:
        {
            GT_assert(VpsHalTrace, (NULL != cmdArgs));
            isshalglbceConfig_t *cfg = (isshalglbceConfig_t *)cmdArgs;

            regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_FRAME_WIDTH);
            regVal &= ~((UInt32) ISS_GLBCE_FRAME_WIDTH_VAL_MASK);
            regVal |= (cfg->width << ISS_GLBCE_FRAME_WIDTH_VAL_SHIFT) &
                      ISS_GLBCE_FRAME_WIDTH_VAL_MASK;
            HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_FRAME_WIDTH, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_FRAME_HEIGHT);
            regVal &= ~((UInt32) ISS_GLBCE_FRAME_HEIGHT_VAL_MASK);
            regVal |= (cfg->height << ISS_GLBCE_FRAME_HEIGHT_VAL_SHIFT) &
                      ISS_GLBCE_FRAME_HEIGHT_VAL_MASK;
            HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_FRAME_HEIGHT, regVal);
            break;
        }

        case ISSHAL_IOCTL_GLBCE_SET_GLBCECFG:
            status = VpsHal_issglbceSetGlbceCfg(
                     handle,
                     (const vpsissGlbceConfig_t *) cmdArgs);
            break;
        case ISSHAL_IOCTL_GLBCE_SET_FWDPRCPT_CFG:
            status = VpsHal_issglbceSetPerceptConfig(
                handle,
                (const vpsissGlbcePerceptConfig_t *) cmdArgs,
                ISS_HAL_FWD_PERCEPT_CFG);
            break;
        case ISSHAL_IOCTL_GLBCE_SET_REVPRCPT_CFG:
            status = VpsHal_issglbceSetPerceptConfig(
                handle,
                (const vpsissGlbcePerceptConfig_t *) cmdArgs,
                ISS_HAL_REV_PERCEPT_CFG);
            break;
        case ISSHAL_IOCTL_GLBCE_SET_WDRCFG:
            status = VpsHal_issglbceSetWdrConfig(
                handle,
                (const vpsissGlbceWdrConfig_t *) cmdArgs);
            break;
        case ISSHAL_IOCTL_GLBCE_GET_DEFAULTCFG:
            if(NULL != cmdArgs)
            {
                BspUtils_memcpy(
                    (isshalglbceConfig_t *) cmdArgs,
                    &gIssHalGlbceDefCfg,
                    sizeof(isshalglbceConfig_t));
            }
            else
            {
                status = FVID2_EBADARGS;
            }
            break;
        case VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO:
        {
            isshalglbceConfig_t     *cfg =
                (isshalglbceConfig_t *) arg;
            isshalissBlankingInfo_t *blankInfo =
                (isshalissBlankingInfo_t *) cmdArgs;

            GT_assert(VpsHalTrace, (NULL != cfg));
            GT_assert(VpsHalTrace, (NULL != blankInfo));

            /* TODO: change this blanking requirement based
             *       on the configuration.
             *       Currently Set to maximm */
            blankInfo->hBlank = 4U;
            blankInfo->vBlank = 10U;

            break;
        }
        case VPS_HAL_ISS_IOCTL_STOP:
        {
            /* Disable GLBCE */
            regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0);
            regVal &= ~((UInt32) ISS_GLBCE_CONTROL0_ONOFF_MASK);
            HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0, regVal);
            break;
        }
        case ISSHAL_IOCTL_GLBCE_GET_STATS_INFO:
        {
            vpsissGlbceStatsInfo_t *statsInfo =
                (vpsissGlbceStatsInfo_t *)cmdArgs;

            if(NULL != cmdArgs)
            {
                statsInfo->size = instObj->glbceStatMemSize;
                statsInfo->addr = instObj->glbceStatMemAddress;
            }
            else
            {
                status = FVID2_EBADARGS;
            }
            break;
        }
        default:
            status = FVID2_EUNSUPPORTED_CMD;
            break;
    }

    return (status);
}

/* Function to start the GLBCE AF module either in one shot or in free
 * running mode */
int32_t VpsHal_issglbceStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg)
{
    int32_t               status  = FVID2_SOK;
    isshalglbceInstObj_t *instObj = NULL;
    volatile uint32_t     regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalglbceInstObj_t *) handle;

    /* Set the processing mode */
    regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_MODE);
    regVal &= ~((UInt32) ISS_GLBCE_MODE_OST_MASK);
    if(ISSHAL_ISS_PROC_MODE_ONE_SHOT == procMode)
    {
        regVal |= ISS_GLBCE_MODE_OST_MASK;
    }
    HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_MODE, regVal);

    /* Enable Glbce engine, all the parameters must be set before
     * enabling this */
    regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0);
    regVal |= ISS_GLBCE_CONTROL0_ONOFF_MASK;
    HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0, regVal);

    return (status);
}

/* Function to start the GLBCE AF module either in one shot or in free
 * running mode */
int32_t VpsHal_issglbceStop(
    VpsHal_Handle handle,
    Ptr           arg)
{
    int32_t               status  = FVID2_SOK;
    isshalglbceInstObj_t *instObj = NULL;
    volatile uint32_t     regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalglbceInstObj_t *) handle;

    /* Disable GLBCE */
    regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0);
    regVal &= ~((UInt32) ISS_GLBCE_CONTROL0_ONOFF_MASK);
    HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0, regVal);

    return (status);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t VpsHal_issglbceSetGlbceCfg(VpsHal_Handle              handle,
                                          const vpsissGlbceConfig_t *cfg)
{
    int32_t               status  = FVID2_SOK;
    isshalglbceInstObj_t *instObj = NULL;
    volatile uint32_t     regVal, regAddr, regVal1;
    uint32_t              cnt;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalglbceInstObj_t *) handle;

    regVal = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0);

    if(TRUE == cfg->enable)
    {
        /* Configure Asymmetry LUT */
        regAddr = instObj->baseAddress + ISS_GLBCE_LUT_FI_00;
        for(cnt = 0U; cnt < VPS_ISS_GLBCE_ASYMMETRY_LUT_SIZE; cnt++)
        {
            regVal1 =
                ((uint32_t)cfg->asymLut[cnt] <<
                 ISS_GLBCE_LUT_FI_00_VAL_SHIFT) &
                ISS_GLBCE_LUT_FI_00_VAL_MASK;
            HW_WR_REG32(regAddr, regVal1);
            regAddr += 4U;
        }

        /* Configure tone mapping slope limit */
        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_SLOPE_MAX);
        regVal &= ~((UInt32) ISS_GLBCE_SLOPE_MAX_SLOPEMAXLIMIT_MASK);
        regVal |= ((uint32_t)cfg->maxSlopeLimit <<
                   ISS_GLBCE_SLOPE_MAX_SLOPEMAXLIMIT_SHIFT) &
                  ISS_GLBCE_SLOPE_MAX_SLOPEMAXLIMIT_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_SLOPE_MAX, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_SLOPE_MIN);
        regVal &= ~((UInt32) ISS_GLBCE_SLOPE_MIN_SLOPEMINLIMIT_MASK);
        regVal |= (cfg->minSlopeLimit <<
                   ISS_GLBCE_SLOPE_MIN_SLOPEMINLIMIT_SHIFT) &
                  ISS_GLBCE_SLOPE_MIN_SLOPEMINLIMIT_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_SLOPE_MIN, regVal);

        /* Configure Dithering, it will also disable dithering
         * if not required */
        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_DITHER);
        regVal &= ~((UInt32) ISS_GLBCE_DITHER_MASK);
        regVal |= (cfg->dither << ISS_GLBCE_DITHER_SHIFT) &
                  ISS_GLBCE_DITHER_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_DITHER, regVal);

        /* Configure tone-mapping curve limit */
        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_LIMIT_AMPL);
        regVal &= ~((UInt32) (ISS_GLBCE_LIMIT_AMPL_BRIGHTAMPLIFICATIONLIMIT_MASK |
                              ISS_GLBCE_LIMIT_AMPL_DARKAMPLIFICATIONLIMIT_MASK));
        regVal |= (cfg->darkAmplLimit <<
                   ISS_GLBCE_LIMIT_AMPL_DARKAMPLIFICATIONLIMIT_SHIFT) &
                  ISS_GLBCE_LIMIT_AMPL_DARKAMPLIFICATIONLIMIT_MASK;
        regVal |= (cfg->brightAmplLimit <<
                   ISS_GLBCE_LIMIT_AMPL_BRIGHTAMPLIFICATIONLIMIT_SHIFT) &
                  ISS_GLBCE_LIMIT_AMPL_BRIGHTAMPLIFICATIONLIMIT_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_LIMIT_AMPL, regVal);

        /* Configure Space and Intensity Variance */
        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_VARIANCE);
        regVal &= ~((UInt32) (ISS_GLBCE_VARIANCE_VARIANCESPACE_MASK |
                              ISS_GLBCE_VARIANCE_VARIANCEINTENSITY_MASK));
        regVal |= (cfg->spaceVariance <<
                   ISS_GLBCE_VARIANCE_VARIANCESPACE_SHIFT) &
                  ISS_GLBCE_VARIANCE_VARIANCESPACE_MASK;
        regVal |= (cfg->intensityVariance <<
                   ISS_GLBCE_VARIANCE_VARIANCEINTENSITY_SHIFT) &
                  ISS_GLBCE_VARIANCE_VARIANCEINTENSITY_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_VARIANCE, regVal);

        /* Configure White and Blank Level */
        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_BLACK_LEVEL);
        regVal &= ~((UInt32) ISS_GLBCE_BLACK_LEVEL_VAL_MASK);
        regVal |= (cfg->blackLevel << ISS_GLBCE_BLACK_LEVEL_VAL_SHIFT) &
                  ISS_GLBCE_BLACK_LEVEL_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_BLACK_LEVEL, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_WHITE_LEVEL);
        regVal &= ~((UInt32) ISS_GLBCE_WHITE_LEVEL_VAL_MASK);
        regVal |= (cfg->whiteLevel << ISS_GLBCE_WHITE_LEVEL_VAL_SHIFT) &
                  ISS_GLBCE_WHITE_LEVEL_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_WHITE_LEVEL, regVal);

        /* Configure IR Strength */
        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_STRENGTH_IR);
        regVal &= ~((UInt32) ISS_GLBCE_STRENGTH_IR_VAL_MASK);
        regVal |= (cfg->irStrength << ISS_GLBCE_STRENGTH_IR_VAL_SHIFT) &
                  ISS_GLBCE_STRENGTH_IR_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_STRENGTH_IR, regVal);

        /* Enable GLBCE Module */
        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0);
        regVal |= ISS_GLBCE_CONTROL0_ONOFF_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0, regVal);
    }
    else
    {
        regVal &= ~((UInt32) ISS_GLBCE_CONTROL0_ONOFF_MASK);
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_CONTROL0, regVal);
    }

    return (status);
}

static int32_t VpsHal_issglbceSetWdrConfig(VpsHal_Handle                 handle,
                                           const vpsissGlbceWdrConfig_t *cfg)
{
    int32_t               status  = FVID2_SOK;
    isshalglbceInstObj_t *instObj = NULL;
    volatile uint32_t     regVal, regAddr;
    uint32_t              cnt;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalglbceInstObj_t *) handle;

    regVal = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_WDR_GAMMA_EN);

    if(TRUE == cfg->enable)
    {
        /* Set the WDR LUT */
        regAddr = instObj->baseAddress + ISS_GLBCE_WDR_GAMMA_LUT_00;
        for(cnt = 0U; cnt < VPS_ISS_GLBCE_WDR_LUT_SIZE; cnt++)
        {
            /* ALL Tables entries are of same size, so using macros of LUT_00 */
            regVal  = HW_RD_REG32(regAddr);
            regVal &= ~((UInt32) ISS_GLBCE_WDR_GAMMA_LUT_00_VAL_MASK);
            regVal |=
                (cfg->table[cnt] << ISS_GLBCE_WDR_GAMMA_LUT_00_VAL_SHIFT) &
                ISS_GLBCE_WDR_GAMMA_LUT_00_VAL_MASK;
            HW_WR_REG32(regAddr, regVal);

            regAddr += 4U;
        }

        /* Enable the Module */
        regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_WDR_GAMMA_EN);
        regVal |= ISS_GLBCE_WDR_GAMMA_EN_MASK;
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_WDR_GAMMA_EN, regVal);
    }
    else
    {
        regVal &= ~((UInt32) ISS_GLBCE_WDR_GAMMA_EN_MASK);
        HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_WDR_GAMMA_EN, regVal);
    }

    return (status);
}

static int32_t VpsHal_issglbceSetPerceptConfig(
    VpsHal_Handle                     handle,
    const vpsissGlbcePerceptConfig_t *cfg,
    uint32_t                          perceptDir)
{
    int32_t               status  = FVID2_SOK;
    isshalglbceInstObj_t *instObj = NULL;
    volatile uint32_t     regVal, regAddr;
    uint32_t              mask, shift, cnt;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalglbceInstObj_t *) handle;

    if(TRUE == cfg->enable)
    {
        if(ISS_HAL_FWD_PERCEPT_CFG == perceptDir)
        {
            regAddr = instObj->baseAddress + ISS_GLBCE_FWD_PERCEPT_LUT_00;
            mask    = ISS_GLBCE_FWD_PERCEPT_LUT_00_VAL_MASK;
            shift   = ISS_GLBCE_FWD_PERCEPT_LUT_00_VAL_SHIFT;

            regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_PERCEPT_EN);
            regVal |= ISS_GLBCE_PERCEPT_EN_FWD_MASK;
            HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_PERCEPT_EN, regVal);
        }
        else
        {
            regAddr = instObj->baseAddress + ISS_GLBCE_REV_PERCEPT_LUT_00;
            mask    = ISS_GLBCE_REV_PERCEPT_LUT_00_VAL_MASK;
            shift   = ISS_GLBCE_REV_PERCEPT_LUT_00_VAL_SHIFT;

            regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_PERCEPT_EN);
            regVal |= ISS_GLBCE_PERCEPT_EN_REV_MASK;
            HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_PERCEPT_EN, regVal);
        }

        for(cnt = 0U; cnt < VPS_ISS_GLBCE_PERCEPT_LUT_SIZE; cnt++)
        {
            regVal  = HW_RD_REG32(regAddr);
            regVal &= ~mask;
            regVal |= (cfg->table[cnt] << shift) & mask;
            HW_WR_REG32(regAddr, regVal);

            regAddr += 4U;
        }
    }
    else
    {
        if(ISS_HAL_FWD_PERCEPT_CFG == perceptDir)
        {
            regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_PERCEPT_EN);
            regVal &= ~((UInt32) ISS_GLBCE_PERCEPT_EN_FWD_MASK);
            HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_PERCEPT_EN, regVal);
        }
        else
        {
            regVal  = HW_RD_REG32(instObj->baseAddress + ISS_GLBCE_PERCEPT_EN);
            regVal &= ~((UInt32) ISS_GLBCE_PERCEPT_EN_REV_MASK);
            HW_WR_REG32(instObj->baseAddress + ISS_GLBCE_PERCEPT_EN, regVal);
        }
    }
    return (status);
}

