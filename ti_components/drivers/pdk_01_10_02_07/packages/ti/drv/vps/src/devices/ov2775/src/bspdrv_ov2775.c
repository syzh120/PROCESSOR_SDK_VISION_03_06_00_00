/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file bspdrv_ov2775.c
 *
 *  \brief OV2775 video sensor FVID2 driver API file.
 *
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <string.h>

#include <stdlib.h>
#include <stdio.h>

#include <ov2775/src/bspdrv_ov2775Priv.h>

Int32 Bsp_ov2775SetExpParams(const Bsp_ov2775HandleObj         *pObj,
                             const Bsp_VidSensorExposureParams *expPrms)
{

    Int32  status = FVID2_SOK;
    UInt32 nDeviceAddr;
    UInt32 nI2cInstId;
    UInt16 nAddr;
    Float32 numLinesFloat;
    UInt16  numLinesLong;


    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (NULL == expPrms)
    {
        status = FVID2_EBADARGS;
    }


    if (FVID2_SOK == status)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];

        /* Long exposure time */
        numLinesFloat = expPrms->exposureTime / pObj->lineIntgTimeInMs;
        numLinesLong       = (UInt16) numLinesFloat;


        if (numLinesLong > (UInt16) BSP_VID_SENSOR_OV2775_MAX_EXP_ROWS)
        {
            numLinesLong = (UInt16) BSP_VID_SENSOR_OV2775_MAX_EXP_ROWS;
        }

        nAddr = BSP_OV2775_DGC_COARSE_EXP_REG;
        status = Bsp_deviceWrite16(nI2cInstId,
                               nDeviceAddr,
                               &nAddr,
                               &numLinesLong,
                               (UInt32) 1);

    }	
	
    return (status);
}

Int32 Bsp_ov2775SetGainParams(const Bsp_ov2775HandleObj     *pObj,
                              const Bsp_VidSensorGainParams *gainPrms)
{
    Int32  status = FVID2_SOK;

    UInt16 nAddr;
    UInt8 nValue;
    UInt32 nValueTemp;
    UInt8 longAnalogGain;
    UInt8 shortAnalogGain;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;

    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (NULL == gainPrms)
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
        nValueTemp = (gainPrms->analogGain)/1000U;
        nValue = (UInt8) nValueTemp;

        if(nValue >= (UInt8) 8U)
        {
                longAnalogGain       = (UInt8) 3U;
        }
        else if(nValue >= (UInt8) 4U)
        {
                longAnalogGain      = (UInt8) 2U;
        }
        else if(nValue >= (UInt8) 2U)
        {
                longAnalogGain      = (UInt8) 1U;
        }
        else
        {
                longAnalogGain      = (UInt8) 0;
        }

        shortAnalogGain = longAnalogGain;

        /* Write CG_AGAIN register*/
        nAddr = BSP_OV2775_ANALOG_GAIN_REG;
        nValue = (UInt8) (longAnalogGain | ((UInt8)(shortAnalogGain<<2)) );

        status = Bsp_deviceWrite_Custom_16A8D(nI2cInstId,
                                   nDeviceAddr,
                                   &nAddr,
                                   &nValue,
                                   (UInt32) 1);
    }

    return (status);
}

