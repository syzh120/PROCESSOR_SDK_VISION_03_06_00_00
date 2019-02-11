/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file bsp_device.c
 *
 *  \brief File containing the BSP devices functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <bsp_devicePriv.h>
#include <tvp5158/bspdrv_tvp5158.h>
#include <sii9127/bspdrv_sii9127.h>
#include <ov1063x/bspdrv_ov1063x.h>
#include <ar0132/bspdrv_ar0132.h>
#include <ar0140/bspdrv_ar0140.h>
#include <ar0132rccc/bspdrv_ar0132rccc.h>
#include <lcdCtrl/bspdrv_lcdCtrl.h>
#include <sii9022a/bspdrv_sii9022a.h>
#include <ds90uh925/bspdrv_ds90uh925.h>
#include <ds90uh926/bspdrv_ds90uh926.h>
#include <ioexp/bspdrv_ioexp.h>
#include <adv7611/bspdrv_adv7611.h>
#include <ov10640/bspdrv_ov10640.h>
#include <imx224/bspdrv_imx224.h>
#include <imx290/bspdrv_imx290.h>
#include <ov2775/bspdrv_ov2775.h>
#include <ov2659/bspdrv_ov2659.h>
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
#include <ov490/bspdrv_ov490.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bsp_DeviceInitParams gDevInitPrm;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief BSP Devices init function.
 */
Int32 Bsp_deviceInit(const Bsp_DeviceInitParams *pPrm)
{
    Int32  retVal = BSP_SOK;
    UInt32 instCnt;
    const Bsp_BoardI2cData *i2cData;
    Bsp_BoardI2cInstData   *i2cInstData;

    /* Init global */
    BspDeviceInitParams_init(&gDevInitPrm);
    gDevInitPrm.isI2cInitReq = FALSE;

    if (NULL == pPrm)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Device Init: NULL init pointer\n");
        retVal = BSP_EBADARGS;
    }

    if ((BSP_SOK == retVal) && (TRUE == pPrm->isI2cInitReq))
    {
        retVal = Bsp_deviceI2cInit();
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Device Init: I2C init failed\r\n");
        }
        else
        {
            gDevInitPrm.isI2cInitReq = pPrm->isI2cInitReq;

            if (TRUE == pPrm->isI2cProbingReq)
            {
                i2cData = Bsp_boardGetI2cData();
                GT_assert(BspDeviceTrace, (NULL != i2cData));
                GT_assert(BspDeviceTrace, (NULL != i2cData->instData));
                for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
                {
                    i2cInstData = &i2cData->instData[instCnt];
                    Bsp_deviceI2cProbeAll(i2cInstData->instId);
                }
            }

            retVal += Bsp_tvp5158Init();
            retVal += Bsp_sii9127Init();
            retVal += Bsp_ov1063xInit();
            retVal += Bsp_ar0132Init();
            retVal += Bsp_ar0140Init();
            retVal += Bsp_ar0132rcccInit();
            retVal += Bsp_lcdCtrlInit();
            retVal += Bsp_sii9022aInit();
            retVal += Bsp_ds90uh925Init();
            retVal += Bsp_ds90uh926Init();
            retVal += Bsp_ioexpInit();
            retVal += Bsp_adv7611Init();
            retVal += Bsp_ov10640Init();
            retVal += Bsp_ov2775Init();
            retVal += Bsp_imx224Init();
            retVal += Bsp_imx290Init();
            retVal += Bsp_ov2659Init();
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
            retVal += Bsp_ov490Init();
#endif
        }
    }

    return (retVal);
}

/**
 *  \brief BSP Devices deinit function.
 */
Int32 Bsp_deviceDeInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

    if (TRUE == gDevInitPrm.isI2cInitReq)
    {
        retVal += Bsp_ov2659DeInit();
        retVal += Bsp_imx290DeInit();
        retVal += Bsp_imx224DeInit();
        retVal += Bsp_ov10640DeInit();
        retVal += Bsp_adv7611DeInit();
        retVal += Bsp_ioexpDeInit();
        retVal += Bsp_ds90uh926DeInit();
        retVal += Bsp_ds90uh925DeInit();
        retVal += Bsp_sii9022aDeInit();
        retVal += Bsp_lcdCtrlDeInit();
        retVal += Bsp_ar0132rcccDeInit();
        retVal += Bsp_ar0140DeInit();
        retVal += Bsp_ar0132DeInit();
        retVal += Bsp_ov1063xDeInit();
        retVal += Bsp_sii9127DeInit();
        retVal += Bsp_tvp5158DeInit();
        retVal += Bsp_deviceI2cDeInit();
        retVal += Bsp_ov2775DeInit();
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
        retVal += Bsp_ov490DeInit();
#endif
    }

    return (retVal);
}

