/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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

/**
 *  \file stw_device.c
 *
 *  \brief File containing the STW device functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/stw_lld/devices/stw_deviceIoexp.h>
#include <ioexp/stw_deviceIoexpPriv.h>
#include <stw_deviceI2cPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static deviceInitParams_t gDevInitPrm;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
 *  \brief STW Devices init function.
 */
int32_t DEVICEInit(const deviceInitParams_t *pPrm)
{
    int32_t  retVal = STW_SOK;
    uint32_t instCnt;
    const boardI2cData_t *i2cData;
    boardI2cInstData_t   *i2cInstData;

    /* Init global */
    DEVICEInitParams_init(&gDevInitPrm);
    gDevInitPrm.isI2cInitReq = (uint32_t) FALSE;

    if (NULL == pPrm)
    {
        UARTPuts("\r\nDevice Init: NULL init pointer", (-((int32_t) 1)));
        retVal = STW_EFAIL;
    }

    if ((STW_SOK == retVal) && (TRUE == pPrm->isI2cInitReq))
    {
        retVal = DEVICEI2cInit(pPrm);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nDevice Init: I2C init failed", (-((int32_t) 1)));
        }
        else
        {
            gDevInitPrm.isI2cInitReq = pPrm->isI2cInitReq;

            if (TRUE == pPrm->isI2cProbingReq)
            {
                i2cData = BOARDGetI2cData();
                if ((NULL != i2cData) && (NULL != i2cData->pInstData))
                {
                    for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
                    {
                        i2cInstData = &i2cData->pInstData[instCnt];
                        DEVICEI2cProbeAll(i2cInstData->instId);
                    }
                }
                else
                {
                    UARTPuts("\r\nDevice Init: NULL i2cData pointer", (-((int32_t) 1)));
                    retVal = STW_EFAIL;
                }
            }
        }
        retVal = DEVICEIoexpInit();
    }
    return (retVal);
}

/**
 *  \brief STW Devices deinit function.
 */
int32_t DEVICEDeInit(void *args)
{
    int32_t retVal = STW_SOK;

    if (TRUE == gDevInitPrm.isI2cInitReq)
    {
        retVal += DEVICEIoexpDeInit();
        retVal += DEVICEI2cDeInit();
    }

    return (retVal);
}

