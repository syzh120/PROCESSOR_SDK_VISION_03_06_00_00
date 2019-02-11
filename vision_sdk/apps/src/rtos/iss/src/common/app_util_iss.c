/******************************************************************************
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
******************************************************************************/

/**
 *******************************************************************************
 * \file chains_common_iss.c
 *
 *
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <iss_sensors.h>
#include <iss_utils.h>
#include <algorithmLink_issAewb.h>
#include <app_util_iss.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/examples/utility/bsputils_ub960.h>
#include <src/rtos/utils_common/include/utils.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/csl/csl_gpio.h>
#include <src/rtos/iss/src/sensor/iss_sensor_serdes.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/*******************************************************************************
 *  Data Structures
 *******************************************************************************
 */
typedef struct
{
    UInt32                      isAlloc;
    AppUtils_Obj                appSensorInfo;
    ChainsCommon_IssSensorIf    sensorIntfInfo;
    IssSensor_Info              sensorInfo;
    IssSensor_CreateParams      sensorCreatePrms;

    Ptr                         sensorHandle;
    IssAewbAlgOutParams         issAewbPrms;

    UInt32                      issCaptLinkId;
    UInt32                      issIspLinkId;
    UInt32                      issSimcopLinkId;
    UInt32                      issAewbLinkId;

    IssM2mSimcopLink_ConfigParams   simcopCfg;
    vpsissldcConfig_t               ldcCfg;
    vpsissvtnfConfig_t              vtnfCfg;
} AppUtils_IssObj;

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */

AppUtils_IssObj gAppUtilsIssObj = {0};
static BspUtils_Ub960DebugRegData gAppUtilIssUB96xdebugStatus;
static BspUtils_Ub960SourceI2cAddr gAppUtilIssSlaveAliases[] =  { {0x3D, 0U, {0U, 0U, 0U, 0U}, \
                                                       {0U, 0U, 0U, 0U}},
                                                  {0x36, 0U, {0U, 0U, 0U, 0U}, \
                                                       {0U, 0U, 0U, 0U}},
                                               };

#ifdef BOARD_TYPE_TDA3XX_RVP
static BspUtils_Ub960I2cParams gAppUtilIssUB964AlphaInitCfg[] = {
    {0xB0, 0x1C, 0x64},
    {0xB1, 0x16, 0x64},
    {0xB2, 0x00, 0x64},
    {0xB1, 0x17, 0x64},
    {0xB2, 0x00, 0x64},
    {0xB1, 0x18, 0x64},
    {0xB2, 0x00, 0x64},
    {0xB1, 0x19, 0x64},
    {0xB2, 0x00, 0x64},
    {0xB0, 0x1C, 0x64},     /* digital share debug registers */
    {0xB1, 0x15, 0x64},
    {0xB2, 0x0A, 0x64},
    {0xB2, 0x00, 0x64},
    {0x1F, 0x02, 0x4FF},
    {0xB0, 0x1C, 0x64},
    {0xB1, 0x13, 0x64},
    {0xB2, 0x1F, 0x64},
    {0xB0, 0x14, 0x64},
    {0xB1, 0x04, 0x64},
    {0xB2, 0x04, 0x64},
    {0xB0, 0x18, 0x64},
    {0xB1, 0x14, 0x64},
    {0xB2, 0x1f, 0x64},
    {0xB0, 0x18, 0x64},
    {0xB1, 0x13, 0x64},
    {0xB2, 0x25, 0x64},
    {0xB0, 0x1C, 0x64},
    {0xB1, 0x1D, 0x64},
    {0xB2, 0x40, 0x64},
    {0xB0, 0x1C, 0x64},
    {0xB1, 0x1A, 0x64},
    {0xB2, 0x99, 0x64},
};

BspUtils_Ub960I2cParams gAppUtilIssUB960AlphaInitCfg[] = {
    {0x1F, 0x05, 0x32},
    {0xB0, 0x1C, 0x64},
    {0xB1, 0x13, 0x64},
    {0xB2, 0x1F, 0x64},
};
#endif

BspUtils_Ub960I2cParams gAppUtilIssUb960Cfg_updateSlaveAddr[] = {

    /* camera 1 */
    {0x4C, 0x01, 0x1},
    {0x65, ((UInt8)(PORT_0_SER_ADDR << 1U)), 0x0},
    {0x66, ((UInt8)(PORT_0_SENSOR_ADDR << 1U)), 0x0},

    /* camera 2 */
    {0x4C, 0x12, 0x1},
    {0x65, ((UInt8)(PORT_1_SER_ADDR << 1U)), 0x0},
    {0x66, ((UInt8)(PORT_1_SENSOR_ADDR << 1U)), 0x0},

    /* camera 3 */
    {0x4C, 0x24, 0x1},
    {0x65, ((UInt8)(PORT_2_SER_ADDR << 1U)), 0x0},
    {0x66, ((UInt8)(PORT_2_SENSOR_ADDR << 1U)), 0x0},

    /* camera 4 */
    {0x4C, 0x38, 0x1},
    {0x65, ((UInt8)(PORT_3_SER_ADDR << 1U)), 0x0},
    {0x66, ((UInt8)(PORT_3_SENSOR_ADDR << 1U)), 0x0},
};

/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
Void appSetDccParams(Ptr pIspCfg, Ptr pSimcopCfg, Void *appData);
Void appSetMergeParams(AlgorithmLink_IssAewbOutParams *pAewbAlgOut,
    Ptr pIspCfg, Void *appData);
Void appSetAewbOutputParams(
    AlgorithmLink_IssAewbOutParams *pAewbAlgOut, Ptr pCfg, Void *appData);


/*******************************************************************************
 *  Function Definition
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 * \brief   Sensor Creation
 *
 *******************************************************************************
*/
Void appCreateISSSensor(AppUtils_Obj *pSensorInfo)
{
    Int32 status;
    UInt32 ch;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;
    IssSensor_CreateParams *prms = NULL;
    ChainsCommon_IssSensorIf *ifInfo;

    if (pIssObj->isAlloc)
    {
        return;
    }
    else
    {
        prms = &pIssObj->sensorCreatePrms;
        ifInfo = &pIssObj->sensorIntfInfo;

        prms->numChan = pSensorInfo->numCh;
        strncpy(prms->name, pSensorInfo->sensorName, ISS_SENSORS_MAX_NAME);

        status = IssSensor_GetSensorInfo(prms->name, &pIssObj->sensorInfo);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        status = ChainsPlatform_GetSensorIntfInfo(prms->name, ifInfo);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        if(pSensorInfo->numCSI2Inst == 2 )
        {
            /*
             * When We are using two csi2 instance to capture,
             * If the first instance doesn't uses all four cameras,
             * below steps are done to keep the i2c address of sensors
             * in sequential order.
             */
            UInt32 numChDeserializer_0 = pSensorInfo->numCh - DESERIALIZER_INST1_MAX_OUT_CHANNEL;
            UInt32 cnt = 0;
            for(cnt = numChDeserializer_0; cnt < pSensorInfo->numCh; cnt++)
            {
                ifInfo->i2cAddr[cnt] = ifInfo->i2cAddr[cnt + (DESERIALIZER_INST0_MAX_OUT_CHANNEL - numChDeserializer_0)];
                ifInfo->i2cAddrSer[cnt] = ifInfo->i2cAddrSer[cnt + (DESERIALIZER_INST0_MAX_OUT_CHANNEL - numChDeserializer_0)];
            }
        }

        prms->i2cInstId = ifInfo->i2cInstId;

        for(ch = 0;ch < prms->numChan;ch++)
        {
            prms->i2cAddr[ch] = ifInfo->i2cAddr[ch];
            prms->videoIfWidth[ch] = ifInfo->videoIfWidth;

            prms->enableFeatures[ch] = 0;
            switch(pSensorInfo->ispOpMode)
            {
                default:
                case ISSM2MISP_LINK_OPMODE_12BIT_LINEAR:
                    prms->enableFeatures[ch] |= ISS_SENSOR_FEATURE_LINEAR_MODE;
                    break;
                case ISSM2MISP_LINK_OPMODE_1PASS_WDR:
                    prms->enableFeatures[ch] |= ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE;
                    break;
                case ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED:
                case ISSM2MISP_LINK_OPMODE_2PASS_WDR:
                    prms->enableFeatures[ch] |= ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE;
                    break;
            }

            if ((ALGORITHMS_ISS_AEWB_MODE_AE == pIssObj->sensorInfo.aewbMode) ||
                (ALGORITHMS_ISS_AEWB_MODE_AEWB == pIssObj->sensorInfo.aewbMode))
            {
                prms->enableFeatures[ch] |=
                    ISS_SENSOR_FEATURE_MANUAL_EXPOSURE |
                        ISS_SENSOR_FEATURE_MANUAL_GAIN;
            }

            if ((0 == strncmp(SENSOR_OMNIVISION_OV10640_CSI2, prms->name,
                ISS_SENSORS_MAX_NAME)) ||
                (0 == strncmp(SENSOR_OMNIVISION_OV10640_IMI, prms->name,
                ISS_SENSORS_MAX_NAME)))
            {
                prms->enableFeatures[ch] |= ISS_SENSOR_FEATURE_HFLIP;
            }
        }

        pIssObj->sensorHandle = IssSensor_Create(prms);
        UTILS_assert(NULL != pIssObj->sensorHandle);

        memcpy(&pIssObj->appSensorInfo, pSensorInfo, sizeof(AppUtils_Obj));
        pIssObj->isAlloc = 1;

        IssUtils_CopySensorName(prms->name);
    }
}

Void appStartIssSensorSerDes(AppUtils_Obj *pObj)
{
    Int32 status;
    UInt32 cnt;
    ChainsCommon_IssSensorIf sensorIntfInfo;
    IssUtils_Ub96xSerDesCfg sensorSerDesCfg;
    IssSensor_CreateParams sensorCreatePrms;
    BspUtils_Ub960SourceI2cAddr ub960I2cAddr;
    BspUtils_Ub960Status ub960Status;
    UInt32 start, end;
    UInt32 i = 0;
    UInt32 numChDeserializer[2] = {0};

    strncpy(sensorCreatePrms.name, pObj->sensorName,
        ISS_SENSORS_MAX_NAME);

    status = ChainsPlatform_GetSensorSerDesCfg(sensorCreatePrms.name,
        &sensorSerDesCfg);

    status = ChainsPlatform_GetSensorIntfInfo(sensorCreatePrms.name,
        &sensorIntfInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    if(TRUE == sensorIntfInfo.isMultiChannel)
    {
        start = Utils_getCurTimeInMsec();

        numChDeserializer[0] = pObj->numCh;

        /*
         * If the number of csi2 instance to be used is 2,
         * then we will take 2 channels from second ub960,
         * remaining will be taken from first ub960;
         */
        if(pObj->numCSI2Inst == 2)
        {
            numChDeserializer[0] = pObj->numCh - DESERIALIZER_INST1_MAX_OUT_CHANNEL;
            numChDeserializer[1] = DESERIALIZER_INST1_MAX_OUT_CHANNEL;
        }

        i = 0;
        do
        {
            /*  1. UB96x init */
            ub960I2cAddr.slaveAddr = sensorIntfInfo.deserializerAddr[i];
            ub960I2cAddr.numSource = numChDeserializer[i];

            if(ub960I2cAddr.slaveAddr == 0)
            {
                ub960I2cAddr.slaveAddr = UB960_SLAVE_ADDR;
            }

            for(cnt = (i * DESERIALIZER_INST0_MAX_OUT_CHANNEL) ; cnt < (i + 1) * DESERIALIZER_INST0_MAX_OUT_CHANNEL; cnt ++)
            {
                ub960I2cAddr.rSlave1Addr[cnt - (i * DESERIALIZER_INST0_MAX_OUT_CHANNEL)] = sensorIntfInfo.i2cAddrSer[cnt];

                if(TRUE == sensorIntfInfo.sensorBroadcast)
                {
                    /*  When broadcast is enabled then all the senors will have the
                        same alias i2c address */
                    ub960I2cAddr.rSlave2Addr[cnt - (i * DESERIALIZER_INST0_MAX_OUT_CHANNEL)] = sensorIntfInfo.i2cAddr[0];
                }
                else
                {
                    ub960I2cAddr.rSlave2Addr[cnt - (i * DESERIALIZER_INST0_MAX_OUT_CHANNEL)] = sensorIntfInfo.i2cAddr[cnt];
                }
            }

            status = IssUtils_appInitUb960(
                                i,
                                sensorIntfInfo.sensorDrvId,
                                &ub960I2cAddr,
                                &sensorSerDesCfg,
                                sensorIntfInfo.sensorBroadcast,
                                &ub960Status);
            UTILS_assert (status == 0);

            i++;

        } while(i < pObj->numCSI2Inst );

        if(sensorSerDesCfg.waitAfterPowerOn)
        {
            Task_sleep(sensorSerDesCfg.waitAfterPowerOn);
        }
        /*  2. Program the sensors */
        if(TRUE == sensorIntfInfo.sensorBroadcast)
        {
            /* Program only ONE sensor */
            appStartISSSensor(pObj, 0);
        }
        else
        {
            for(cnt = 0 ; cnt < pObj->numCh; cnt ++)
            {
                appStartISSSensor(pObj, cnt);
            }
        }

        /*  3. Disable sensor broadcast */
        if(TRUE == sensorIntfInfo.sensorBroadcast)
        {
            for(cnt = 0 ; cnt < pObj->numCh; cnt ++)
            {
                ub960I2cAddr.rSlave2Addr[cnt] = sensorIntfInfo.i2cAddr[cnt];
            }

            status = IssUtils_updateSlaveAddrUb960(0U, &ub960I2cAddr);
            UTILS_assert (status == 0);
        }

        /*  4.Enable FSIN for IMI camera */
        if(TRUE == sensorIntfInfo.enableFsin)
        {
            status = IssUtils_appUb960EnableFsin(
                                    0U,
                                    sensorIntfInfo.sensorDrvId,
                                    &ub960I2cAddr,
                                    &ub960Status);
            UTILS_assert (status == 0);
        }
        if (sensorIntfInfo.isEnableCSIPostConfig)
        {
            Vps_printf(" ### Enablig CSI output \n");
            BspUtils_enableUb960CsiOutput();
        }
    }
    else
    {
        appStartISSSensor(pObj, 0);
    }

    end = Utils_getCurTimeInMsec();
    Vps_printf(" #### Sensor Config time = %d msec ####\n",(end - start));
}

Void appGetUB96xRegVal(AppUtils_Obj *pObj)
{
    Int32 status;
    UInt32 cnt;
    ChainsCommon_IssSensorIf sensorIntfInfo;
    IssSensor_CreateParams sensorCreatePrms;
    BspUtils_Ub960SourceI2cAddr ub960I2cAddr;
    BspUtils_Ub960DebugRegData debugStatus;

    strncpy(sensorCreatePrms.name, pObj->sensorName,
        ISS_SENSORS_MAX_NAME);

    status = ChainsPlatform_GetSensorIntfInfo(sensorCreatePrms.name,
        &sensorIntfInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    ub960I2cAddr.slaveAddr = UB960_SLAVE_ADDR;
    ub960I2cAddr.numSource = pObj->numCh;

    if(TRUE == sensorIntfInfo.isMultiChannel)
    {
        for(cnt = 0; cnt < ub960I2cAddr.numSource; cnt ++)
        {
            ub960I2cAddr.rSlave1Addr[cnt] = sensorIntfInfo.i2cAddrSer[cnt];

            if(TRUE == sensorIntfInfo.sensorBroadcast)
            {
                /*  When broadcast is enabled then all the senors will have the
                    same alias i2c address */
                ub960I2cAddr.rSlave2Addr[cnt] = sensorIntfInfo.i2cAddr[0];
            }
            else
            {
                ub960I2cAddr.rSlave2Addr[cnt] = sensorIntfInfo.i2cAddr[cnt];
            }
        }
    }

    status = BspUtils_getDebugRegVal(
                                    0U,
                                    sensorIntfInfo.sensorDrvId,
                                    &ub960I2cAddr,
                                    &debugStatus);
    for(cnt = 0; cnt < debugStatus.numofReg; cnt ++)
    {
        Vps_printf(" Reg Addr 0x%02X -- Value 0x%x ",debugStatus.ub96xdebugData[cnt].regAddr,debugStatus.ub96xdebugData[cnt].regValue);
    }
}

Void appStartISSSensor(AppUtils_Obj *pObj,UInt32 numCh)
{
    Int32 status;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pIssObj->sensorHandle);

    status = IssSensor_Start(pIssObj->sensorHandle, numCh);
    UTILS_assert(0 == status);
}

Void appStopISSSensor(AppUtils_Obj *pObj)
{
    Int32 status, cnt;
    ChainsCommon_IssSensorIf sensorIntfInfo;
    IssSensor_CreateParams sensorCreatePrms;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pIssObj->sensorHandle);

    for (cnt = 0u; cnt < pObj->numCh; cnt ++)
    {
        status = IssSensor_Stop(pIssObj->sensorHandle, cnt);
        UTILS_assert(0 == status);
    }

    strncpy(sensorCreatePrms.name, pObj->sensorName,
        ISS_SENSORS_MAX_NAME);

    status = ChainsPlatform_GetSensorIntfInfo(sensorCreatePrms.name,
        &sensorIntfInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    if(TRUE == sensorIntfInfo.isMultiChannel)
    {
        cnt = 0;
        do
        {
            BspUtils_appDeInitUb960(cnt, sensorIntfInfo.sensorDrvId);
            cnt++;
        } while (cnt < pObj->numCSI2Inst );
    }
}

Void appDeleteISSSensor(AppUtils_Obj *pObj)
{
    Int32 status;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pIssObj->sensorHandle);

    status = IssSensor_Delete(pIssObj->sensorHandle);
    UTILS_assert(0 == status);

    pIssObj->sensorHandle = NULL;
    memset(&pIssObj->appSensorInfo, 0, sizeof(AppUtils_Obj));
    pIssObj->isAlloc = 0;
}

Void appInitIssCaptParams(AppUtils_Obj *pObj, UInt32 issCaptLinkId,
    IssCaptureLink_CreateParams *pCapturePrm)
{
    Int32 status;
    UInt32 i = 0;
    ChainsCommon_IssSensorIf *pSensorIntfInfo;
    IssSensor_Info *pSensorInfo;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pCapturePrm);

    pIssObj->issCaptLinkId = issCaptLinkId;

    pSensorInfo = &pIssObj->sensorInfo;
    pSensorIntfInfo = &pIssObj->sensorIntfInfo;

    status = IssSensor_GetSensorInfo(pObj->sensorName, pSensorInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    status = ChainsPlatform_GetSensorIntfInfo(pObj->sensorName,
        pSensorIntfInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    pCapturePrm->outParams[0U].dataFormat =
        (System_VideoDataFormat)pSensorInfo->dataFormat;
    pCapturePrm->outParams[0U].width = pSensorInfo->width;
    pCapturePrm->outParams[0U].height = pSensorInfo->height;

    if (pObj->ispOpMode == ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED)
    {
        pCapturePrm->outParams[0U].width  =
            pSensorInfo->lnIntrExpFrmInfo.totalWidth;
        pCapturePrm->outParams[0U].height =
            pSensorInfo->lnIntrExpFrmInfo.totalHeight;
    }

    pCapturePrm->bufCaptMode = SYSTEM_CAPT_BCM_LAST_FRM_REPEAT;
    pCapturePrm->outParams[0U].maxWidth = pCapturePrm->outParams[0U].width;
    pCapturePrm->outParams[0U].maxHeight = pCapturePrm->outParams[0U].height;
    pCapturePrm->outParams[0U].numOutBuf = 3;

    /* Initialize Capture parameters from sensor interface information */
    pCapturePrm->videoIfMode =
        (System_VideoIfMode)pSensorIntfInfo->videoIfMode;
    pCapturePrm->videoIfWidth =
        (System_VideoIfWidth)pSensorIntfInfo->videoIfWidth;

    pCapturePrm->outParams[0U].inCsi2DataFormat = pSensorIntfInfo->inCsi2DataFormat;
    pCapturePrm->outParams[0U].inCsi2VirtualChanNum =
        pSensorIntfInfo->inCsi2VirtualChanNum;


    for(i = 0 ; i < ISSCAPT_LINK_MAX_CMPLXIO_INST; i++)
    {
        pCapturePrm->csi2Params[i] = pSensorIntfInfo->csi2Prms[i];
    }
}

Void appInitIssIspParams(AppUtils_Obj *pObj, UInt32 issIspLinkId,
    IssM2mIspLink_CreateParams *pPrm)
{
    Int32 status;
    UInt32 chId;
    ChainsCommon_IssSensorIf *pSensorIntfInfo;
    IssSensor_Info *pSensorInfo;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pPrm);

    pIssObj->issIspLinkId = issIspLinkId;

    pSensorInfo = &pIssObj->sensorInfo;
    pSensorIntfInfo = &pIssObj->sensorIntfInfo;

    status = IssSensor_GetSensorInfo(pObj->sensorName, pSensorInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    status = ChainsPlatform_GetSensorIntfInfo(pObj->sensorName,
        pSensorIntfInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    for(chId = 0; chId < ISSM2MISP_LINK_MAX_CH; chId++)
    {
        pPrm->channelParams[chId].operatingMode   = pObj->ispOpMode;
        pPrm->channelParams[chId].inBpp           = pSensorInfo->bpp;
        pPrm->channelParams[chId].flipCtrl        = VPS_ISS_RSZ_STR_MODE_NORMAL;
        pPrm->channelParams[chId].numBuffersPerCh = 3;

        pPrm->channelParams[chId].outParams.widthRszA  = pSensorInfo->width;
        pPrm->channelParams[chId].outParams.heightRszA = pSensorInfo->height;
        pPrm->channelParams[chId].outParams.widthRszB  = pSensorInfo->width;
        pPrm->channelParams[chId].outParams.heightRszB = pSensorInfo->height;
        pPrm->channelParams[chId].outParams.winWidthH3a = 16;
        pPrm->channelParams[chId].outParams.winHeightH3a = 16;
        pPrm->channelParams[chId].outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;

        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A] = 1;
        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0;
        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_H3A]  = 1;
        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_H3A_AF]  = 0;

        {
            pPrm->channelParams[chId].enableOut[
                ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 1;
        }

        if (pObj->ispOpMode == ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED)
        {
            pPrm->channelParams[chId].outParams.widthRszA  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    width;
            pPrm->channelParams[chId].outParams.heightRszA =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    height;

            pPrm->channelParams[chId].wdrOffsetPrms.longLineOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    starty;
            pPrm->channelParams[chId].wdrOffsetPrms.longPixelOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    startx;
            pPrm->channelParams[chId].wdrOffsetPrms.shortLineOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_SHORT].
                    starty;
            pPrm->channelParams[chId].wdrOffsetPrms.shortPixelOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_SHORT].
                    startx;
            pPrm->channelParams[chId].wdrOffsetPrms.width  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    width;
            pPrm->channelParams[chId].wdrOffsetPrms.height  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    height;
        }
    }
}

Void appInitIssSimcopParams(AppUtils_Obj *pObj, UInt32 issSimcopLinkId,
    IssM2mSimcopLink_CreateParams *pPrm)
{
    int chId;

    gAppUtilsIssObj.issSimcopLinkId = issSimcopLinkId;

    for(chId=0; chId<ISSM2MSIMCOP_LINK_MAX_CH; chId++)
    {
        pPrm->channelParams[chId].operatingMode = pObj->simcopOpMode;;

        pPrm->channelParams[chId].numBuffersPerCh
            = ISSM2MSIMCOP_LINK_NUM_BUFS_PER_CH_DEFAULT;
    }
}

Void appSetDefaultIspParams(AppUtils_Obj *pObj)
{
    Int32 status;
    UInt32 cnt;
    IssIspConfigurationParameters ispConfig;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    IssM2mIspLink_ConfigParams_Init(&ispConfig);

    /* H3A and GLBCE configuration comes from the sensor layer
       Get ISP configuration for these modules from sensor */
    status = IssSensor_Control(pIssObj->sensorHandle,
        ISS_SENSORS_IOCTL_GET_ISP_CONFIG, &ispConfig, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    for (cnt = 0u; cnt < pObj->numCh; cnt ++)
    {
        ispConfig.channelId = cnt;
        /** Set the default Config received from the sensor layer
            MUST be called after link create and before link start */
        status = System_linkControl(
            pIssObj->issIspLinkId, ISSM2MISP_LINK_CMD_SET_ISPCONFIG,
            &ispConfig, sizeof(IssIspConfigurationParameters), TRUE);
        UTILS_assert(0 == status);
    }
}

Void appSetIspParamsFromDCC(AppUtils_Obj *pObj)
{
    Int32 status;
    IssSensor_DccParams sensorDccPrms;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    status = IssSensor_GetSensorInfo(pObj->sensorName, &pIssObj->sensorInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    if (ISS_SENSOR_FEATURE_DCC_SUPPORTED ==
        (ISS_SENSOR_FEATURE_DCC_SUPPORTED & pIssObj->sensorInfo.features))
    {
        sensorDccPrms.chId = 0;
        /* Get the default Profile from the sensor */
        status = IssSensor_Control(pIssObj->sensorHandle,
            ISS_SENSORS_IOCTL_GET_DCC_PARAMS, &sensorDccPrms, NULL);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        /* Reads default configuration from the sensor layer,
           then reads and parses DCC Profile and saves it in the isp and
           simcop config */
        IssUtils_ReadAndParseDccConfig(
                pIssObj->sensorInfo.ramOffset,
                sensorDccPrms.pDccCfg,
                sensorDccPrms.dccCfgSize,
                pIssObj->issAewbLinkId);
    }
}

Void appDccParseAndSetIspParamsFromSensor(AppUtils_Obj *pObj)
{
    Int32 status;
    IssSensor_DccParams sensorDccPrms;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;
    AlgorithmLink_IssAewbDccControlParams dccCtrlPrms;

    status = IssSensor_GetSensorInfo(pObj->sensorName, &pIssObj->sensorInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    if (ISS_SENSOR_FEATURE_DCC_SUPPORTED ==
        (ISS_SENSOR_FEATURE_DCC_SUPPORTED & pIssObj->sensorInfo.features))
    {
        sensorDccPrms.chId = 0;
        /* Get the default Profile from the sensor */
        status = IssSensor_Control(pIssObj->sensorHandle,
            ISS_SENSORS_IOCTL_GET_DCC_PARAMS, &sensorDccPrms, NULL);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        /* Get the DCC Profile Memory from the AEWB algorithms */
        memset(&dccCtrlPrms, 0x0, sizeof(dccCtrlPrms));

        /* Get the DCC Buffer */
        dccCtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_AEWB_LINK_CMD_GET_DCC_BUF_PARAMS;
        dccCtrlPrms.baseClassControl.size = sizeof(dccCtrlPrms);

        dccCtrlPrms.dccBuf = NULL;

        status = System_linkControl(
            pIssObj->issAewbLinkId,
            ALGORITHM_LINK_CMD_CONFIG,
            &dccCtrlPrms,
            sizeof(dccCtrlPrms),
            TRUE);
        UTILS_assert(0 == status);

        /* Read in cache correct memory */
        Cache_inv(sensorDccPrms.pDccCfg, sensorDccPrms.dccCfgSize,
            Cache_Type_ALLD, TRUE);

        memcpy(dccCtrlPrms.dccBuf, sensorDccPrms.pDccCfg,
            sensorDccPrms.dccCfgSize);
        dccCtrlPrms.dccBufSize = sensorDccPrms.dccCfgSize;

        /* Parse the DCC and set the output */
        dccCtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_AEWB_LINK_CMD_PARSE_AND_SET_DCC_PARAMS;
        dccCtrlPrms.baseClassControl.size = sizeof(dccCtrlPrms);

        status = System_linkControl(
            pIssObj->issAewbLinkId,
            ALGORITHM_LINK_CMD_CONFIG,
            &dccCtrlPrms,
            sizeof(dccCtrlPrms),
            TRUE);
        UTILS_assert(0 == status);
    }
}

Void appParserAndSetDccProfile(Ptr pDccCfg, UInt32 size)
{
    Int32 status;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;
    AlgorithmLink_IssAewbDccControlParams dccCtrlPrms;

    UTILS_assert(NULL != pDccCfg);

    {
        /* Get the DCC Profile Memory from the AEWB algorithms */
        memset(&dccCtrlPrms, 0x0, sizeof(dccCtrlPrms));

        /* Get the DCC Buffer */
        dccCtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_AEWB_LINK_CMD_GET_DCC_BUF_PARAMS;
        dccCtrlPrms.baseClassControl.size = sizeof(dccCtrlPrms);

        dccCtrlPrms.dccBuf = NULL;

        status = System_linkControl(
            pIssObj->issAewbLinkId,
            ALGORITHM_LINK_CMD_CONFIG,
            &dccCtrlPrms,
            sizeof(dccCtrlPrms),
            TRUE);
        UTILS_assert(0 == status);

        /* Read in cache correct memory */
        Cache_inv(pDccCfg, size, Cache_Type_ALLD, TRUE);

        memcpy(dccCtrlPrms.dccBuf, pDccCfg, size);
        dccCtrlPrms.dccBufSize = size;

        /* Parse the DCC and set the output */
        dccCtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_AEWB_LINK_CMD_PARSE_AND_SET_DCC_PARAMS;
        dccCtrlPrms.baseClassControl.size = sizeof(dccCtrlPrms);

        status = System_linkControl(
            pIssObj->issAewbLinkId,
            ALGORITHM_LINK_CMD_CONFIG,
            &dccCtrlPrms,
            sizeof(dccCtrlPrms),
            TRUE);
        UTILS_assert(0 == status);
    }
}

Void appInitIssAewbParams(AppUtils_Obj *pObj, UInt32 issAewbLinkId,
    AlgorithmLink_IssAewbCreateParams *pPrm)
{
    Int32 status;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pPrm);
    UTILS_assert(NULL != pIssObj->sensorHandle);

    pIssObj->issAewbLinkId = issAewbLinkId;

    status = IssSensor_Control(pIssObj->sensorHandle,
        ISS_SENSORS_IOCTL_INIT_AEWB_CONFIG, pPrm, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* Since we are operating in Linear mode, disable backlight compensation */
    if ((pObj->ispOpMode == ISSM2MISP_LINK_OPMODE_12BIT_LINEAR) ||
        (pObj->ispOpMode == ISSM2MISP_LINK_OPMODE_1PASS_WDR))
    {
        pPrm->aeDynParams.enableBlc = FALSE;
    }

    pPrm->appData = pIssObj;
    pPrm->dccAppData = pIssObj;
    pPrm->cfgCbFxn = appSetAewbOutputParams;

    /* No Need to enable merge function for single pass wdr flow */
    if (TRUE == IssM2mIspLink_IsWdrMergeMode(pObj->ispOpMode))
    {
        pPrm->mergeCbFxn = appSetMergeParams;
    }

    pPrm->dccIspCfgFxn = appSetDccParams;

    pPrm->numSteps = 6;
}

Void appSetAewbOutputParams(
    AlgorithmLink_IssAewbOutParams *pAewbAlgOut, Ptr pCfg, Void *appData)
{
    Int32 status, cnt;
    IssSensor_AeParams sensorAePrms;
    AppUtils_IssObj *pIssObj = (AppUtils_IssObj *)appData;
    IssAewbAlgOutParams *pIssAewbPrms;
    IssIspConfigurationParameters *pIspCfg =
        (IssIspConfigurationParameters *)pCfg;

    UTILS_assert(NULL != pIssObj);
    UTILS_assert(NULL != pAewbAlgOut);
    UTILS_assert(NULL != pIspCfg);

    pIssAewbPrms = &pIssObj->issAewbPrms;

    pIssAewbPrms->channelId = pAewbAlgOut->channelId;
    pIssAewbPrms->outPrms[0].useAeCfg = pAewbAlgOut->outPrms[0].useAeCfg;
    pIssAewbPrms->outPrms[0].exposureTime =
        pAewbAlgOut->outPrms[0].exposureTime;
    pIssAewbPrms->outPrms[0].analogGain = pAewbAlgOut->outPrms[0].analogGain;
    pIssAewbPrms->outPrms[0].digitalGain = pAewbAlgOut->outPrms[0].digitalGain;

    pIssAewbPrms->outPrms[0].useColorTemp =
        pAewbAlgOut->outPrms[0].useColorTemp;
    pIssAewbPrms->outPrms[0].colorTemparature =
        pAewbAlgOut->outPrms[0].colorTemparature;

    pIssAewbPrms->outPrms[0].useWbCfg = pAewbAlgOut->outPrms[0].useWbCfg;
    for (cnt = 0u; cnt < 4; cnt ++)
    {
        pIssAewbPrms->outPrms[0].gain[cnt] = pAewbAlgOut->outPrms[0].gain[cnt];
        pIssAewbPrms->outPrms[0].offset[cnt] =
            pAewbAlgOut->outPrms[0].offset[cnt];
    }

    pIssAewbPrms->numParams = 1U;

    memcpy(&pIssAewbPrms->ispCfg, pIspCfg,
        sizeof(IssIspConfigurationParameters));

    /* AEWB Output parameters are already converted and stored in
       ispCfg parameter of alg out, so set it in the ISP using ISP
       Link */
    System_linkControl(
        pIssObj->issIspLinkId, ISSM2MISP_LINK_CMD_SET_AEWB_PARAMS, pIssAewbPrms,
        sizeof(IssAewbAlgOutParams), TRUE);

    /* Set the Sensor exposure and analog Gain */
    if (pAewbAlgOut->outPrms[0].useAeCfg)
    {
        sensorAePrms.chId = pAewbAlgOut->channelId;
        sensorAePrms.analogGain = pAewbAlgOut->outPrms[0].analogGain;
        sensorAePrms.exposureTime[0] =
            pAewbAlgOut->outPrms[0].exposureTime;

        status = IssSensor_Control(pIssObj->sensorHandle,
            ISS_SENSORS_IOCTL_SET_AE_PARAMS, &sensorAePrms, NULL);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }
}

Void appSetMergeParams(AlgorithmLink_IssAewbOutParams *pAewbAlgOut,
    Ptr pIspCfg, Void *appData)
{
    Int32 status;
    AppUtils_IssObj *pIssObj = (AppUtils_IssObj *)appData;
    IssSensor_ExposureParams expPrms;

    UTILS_assert(NULL != pIssObj);
    UTILS_assert(NULL != pAewbAlgOut);

    /* Get Exposure ratio parameters from the sensor */
    expPrms.chId = pAewbAlgOut->channelId;
    status = IssSensor_Control(pIssObj->sensorHandle,
        ISS_SENSORS_IOCTL_GET_EXPOSURE_PARAMS, &expPrms, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* When dgain is applied only to long after split, there is a
        different ratio for split and merge */
    /* setting up merge parameters even for 2 pass wdr mode when AE is
       not enabled because merge parameter calculation uses digital gain
       for the calculation */
    if ((TRUE == pAewbAlgOut->outPrms[0].useAeCfg) ||
        ((TRUE == IssM2mIspLink_IsWdrMergeMode(
            pIssObj->appSensorInfo.ispOpMode)) &&
         (ALGORITHMS_ISS_AEWB_MODE_AWB == pIssObj->sensorInfo.aewbMode)))
    {
        pIssObj->issAewbPrms.exposureRatio = expPrms.expRatio;

        System_linkControl(
            pIssObj->issIspLinkId,
            ISSM2MISP_LINK_CMD_SET_WDR_MERGE_PARAMS,
            &pIssObj->issAewbPrms,
            sizeof(IssAewbAlgOutParams),
            TRUE);
    }
}

Void appSetDccParams(Ptr pIspCfg, Ptr pSimcopCfg, Void *appData)
{
    Int32 status;
    UInt32 cnt;
    AppUtils_IssObj *pIssObj = (AppUtils_IssObj *)appData;
    IssIspConfigurationParameters *ispCfg =
        (IssIspConfigurationParameters *)pIspCfg;
    IssM2mSimcopLink_ConfigParams *simcopCfg =
        (IssM2mSimcopLink_ConfigParams *)pSimcopCfg;

    UTILS_assert(NULL != pIssObj);
    UTILS_assert(NULL != ispCfg);
    UTILS_assert(NULL != simcopCfg);
    UTILS_assert(pIssObj->appSensorInfo.numCh > 0);

    /* Set the ISS configuration in ISP link */
    for (cnt = 0u; cnt < pIssObj->appSensorInfo.numCh; cnt ++)
    {
        ispCfg->channelId = cnt;
        simcopCfg->chNum = cnt;

        status = System_linkControl(
            pIssObj->issIspLinkId, ISSM2MISP_LINK_CMD_SET_ISPCONFIG, ispCfg,
            sizeof(IssIspConfigurationParameters), TRUE);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        if (NULL != simcopCfg->ldcConfig)
        {
            /* MUST be called after link create and before link start */
            status = System_linkControl(
                pIssObj->issSimcopLinkId,
                ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
                simcopCfg, sizeof(IssM2mSimcopLink_ConfigParams), TRUE);
            UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
        }
    }
}

Void appSetDefaultSimcopParams(void)
{
    Int32 status;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    pIssObj->simcopCfg.ldcConfig = &pIssObj->ldcCfg;
    pIssObj->simcopCfg.vtnfConfig = &pIssObj->vtnfCfg;

    IssUtils_InitSimcopConfig(&pIssObj->simcopCfg, TRUE, TRUE);

    /* MUST be called after link create and before link start */
    status = System_linkControl(
        pIssObj->issSimcopLinkId,
        ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
        &pIssObj->simcopCfg, sizeof(IssM2mSimcopLink_ConfigParams), TRUE);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}

Int32 IssUtils_appInitUb960(UInt32 instId,
                            UInt32 sensorDrvId,
                            const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                            IssUtils_Ub96xSerDesCfg * devSerDesCfg,
                            Bool sensorBroadcast,
                            BspUtils_Ub960Status *pStatus)
{
    Int32   retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 nIdx, i2cDevAddr;
    Bool initSerializer = FALSE;

    if ((NULL != pStatus) && (NULL != pSlaveAddr) && instId < BSPUTILS_UB960_MAX_INSTANCE)
    {
        retVal = SYSTEM_LINK_STATUS_SOK;
        gAppUtilIssSlaveAliases[instId].slaveAddr = pSlaveAddr->slaveAddr;
        gAppUtilIssSlaveAliases[instId].numSource = pSlaveAddr->numSource;
    }

        for (nIdx = 0U; nIdx < BSPUTILS_UB960EVM_MAX_PORTS; nIdx++)
        {
                gAppUtilIssSlaveAliases[instId].rSlave1Addr[nIdx] = pSlaveAddr->rSlave1Addr[nIdx];
                gAppUtilIssSlaveAliases[instId].rSlave2Addr[nIdx] = pSlaveAddr->rSlave2Addr[nIdx];
        }

    retVal = initDeserializer(instId);
    if(SYSTEM_LINK_STATUS_SOK != retVal)
    {
         Vps_printf("initDeserializer failed!!!\r\n");
    }else
    {
        retVal = configDeserializer(instId, devSerDesCfg->desCfgScript, devSerDesCfg->num_des_registers, sensorBroadcast);

        if(SYSTEM_LINK_STATUS_SOK != retVal)
        {
            Vps_printf("configDeserializer failed!!!\r\n");
        }else
        {
        /* Power ON the camera */
            Vps_printf("Setting Camera Power to %d!!!\r\n", devSerDesCfg->cam_pwr_level);
            retVal = setCameraPower(devSerDesCfg->cam_pwr_level);
            Vps_printf("Waiting for %d milliseconds!!!\r\n", devSerDesCfg->waitAfterPowerOn);
            if(devSerDesCfg->waitAfterPowerOn)
            {
                Task_sleep(devSerDesCfg->waitAfterPowerOn);
            }
        }

        if(SYSTEM_LINK_STATUS_SOK != retVal)
        {
            Vps_printf("Power ON failed!!!\r\n");
        }else
        {
            for (nIdx = 0U; nIdx < pSlaveAddr->numSource; nIdx++)
            {
                /*Init serializer*/
                if (BSPUTILS_UB960EVM_MAX_PORTS > nIdx)
                {
                      i2cDevAddr = pSlaveAddr->rSlave1Addr[nIdx];
                }
                else
                {
                    Vps_printf("Wrong instance of UB9xx Serializer !!!\r\n");
                    retVal = SYSTEM_LINK_STATUS_EFAIL;
                    break;
                }
                Vps_printf("Serilaizer # %d has I2CAddr %x !!!\r\n", nIdx, i2cDevAddr);

                                /*Only CAM 0 Serializer needs to be initialzed if braodcast is enabled*/
                if(0U == nIdx)
                {
                    initSerializer = TRUE;
                }else if(FALSE == sensorBroadcast)
                {
                    initSerializer = TRUE;
                }else
                {
                    initSerializer = FALSE;
                }

                if(TRUE == initSerializer)
                {
                    retVal = configSerializer(i2cDevAddr, devSerDesCfg->serCfgScript, devSerDesCfg->num_ser_registers);
                }

                if(SYSTEM_LINK_STATUS_SOK != retVal)
                {
                    Vps_printf("Failed to initialize the serializer on camera # %d!!!\r\n", nIdx);
                }
            }
        }
    }

    if(SYSTEM_LINK_STATUS_SOK == retVal)
    {
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[0].regAddr =  BSPUTILS_UB960_DEVICE_STS;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[1].regAddr =  BSPUTILS_UB960_GPIO_STS;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[2].regAddr =  BSPUTILS_UB960_INTERRUPT_STS_ADDR;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[3].regAddr =  BSPUTILS_UB960_TS_STATUS;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[4].regAddr =  BSPUTILS_UB960_CSI_CTL;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[5].regAddr =  BSPUTILS_UB960_CSI_CTL2;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[6].regAddr =  BSPUTILS_UB960_CSI_STS_ADDR;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[7].regAddr =  BSPUTILS_UB960_CSI_TX_ISR;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[8].regAddr =  BSPUTILS_UB960_RX_PORT_STS1;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[9].regAddr =  BSPUTILS_UB960_RX_PORT_STS2;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[10].regAddr = BSPUTILS_UB960_RX_FREQ_HIGH;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[11].regAddr = BSPUTILS_UB960_RX_FREQ_LOW;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[12].regAddr = BSPUTILS_UB960_RX_PAR_ERR_HI;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[13].regAddr = BSPUTILS_UB960_RX_PAR_ERR_LO;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[14].regAddr = BSPUTILS_UB960_BIST_ERR_COUNT;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[15].regAddr = BSPUTILS_UB960_LINE_COUNT_1;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[16].regAddr = BSPUTILS_UB960_LINE_COUNT_0;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[17].regAddr = BSPUTILS_UB960_LINE_LEN_1;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[18].regAddr = BSPUTILS_UB960_LINE_LEN_0;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[19].regAddr = BSPUTILS_UB960_CSI_RX_STS;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[20].regAddr = BSPUTILS_UB960_CSI_ERR_COUNTER;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[21].regAddr = BSPUTILS_UB960_PORT_CONFIG2;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[22].regAddr = BSPUTILS_UB960_MODE_IDX_STS;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[23].regAddr = BSPUTILS_UB960_PORT_ISR_HI;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[24].regAddr = BSPUTILS_UB960_AEQ_STATUS;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[25].regAddr = BSPUTILS_UB960_PORT_ISR_LO;
        gAppUtilIssUB96xdebugStatus.ub96xdebugData[26].regAddr = BSPUTILS_UB960_FPD3_RX_ID5;

        gAppUtilIssUB96xdebugStatus.numofReg = BSPUTILS_UB960_MAX_NUM_DEBUG_REG;
    }


    return retVal;
}

Int32 IssUtils_updateSlaveAddrUb960(UInt32 instId,
                            const BspUtils_Ub960SourceI2cAddr *pSlaveAddr)
{
    Int32   retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32  nIdx, numRegs;
    volatile UInt32 count;

    if (NULL != pSlaveAddr)
    {
        retVal = SYSTEM_LINK_STATUS_SOK;
        gAppUtilIssSlaveAliases[instId].slaveAddr = pSlaveAddr->slaveAddr;
        gAppUtilIssSlaveAliases[instId].numSource = pSlaveAddr->numSource;
    }

    if (SYSTEM_LINK_STATUS_SOK == retVal)
    {
        for (nIdx = 0U; nIdx < BSPUTILS_UB960EVM_MAX_PORTS; nIdx++)
        {
            gAppUtilIssSlaveAliases[instId].rSlave1Addr[nIdx] = pSlaveAddr->rSlave1Addr[nIdx];
            gAppUtilIssSlaveAliases[instId].rSlave2Addr[nIdx] = pSlaveAddr->rSlave2Addr[nIdx];
        }

        count = 0U;
        numRegs = (sizeof (gAppUtilIssUb960Cfg_updateSlaveAddr) / \
                                    sizeof (gAppUtilIssUb960Cfg_updateSlaveAddr[0U]));

        for (nIdx = 0U;nIdx < numRegs;nIdx++)
        {
            if (0x65 == gAppUtilIssUb960Cfg_updateSlaveAddr[nIdx].nRegAddr)
            {
                gAppUtilIssUb960Cfg_updateSlaveAddr[nIdx].nRegValue =
                        (gAppUtilIssSlaveAliases[instId].rSlave1Addr[count] << 1U);
            }
            if (0x66 == gAppUtilIssUb960Cfg_updateSlaveAddr[nIdx].nRegAddr)
            {
                gAppUtilIssUb960Cfg_updateSlaveAddr[nIdx].nRegValue =
                        (gAppUtilIssSlaveAliases[instId].rSlave2Addr[count] << 1U);
                count++;
            }
            UTILS_assert((BSPUTILS_UB960EVM_MAX_PORTS >= count));
        }

        for (nIdx = 0U;nIdx < numRegs;nIdx++)
        {
            retVal = Bsp_deviceWrite8(
                UB960_ACCESSIBLE_FROM_I2C_INST,
                gAppUtilIssSlaveAliases[instId].slaveAddr,
                &(gAppUtilIssUb960Cfg_updateSlaveAddr[nIdx].nRegAddr),
                &(gAppUtilIssUb960Cfg_updateSlaveAddr[nIdx].nRegValue),
                (UInt32) 1U);
            if (retVal != SYSTEM_LINK_STATUS_SOK)
            {
                Vps_printf("Could not configure UB960 !!!\n");
                break;
            }

            if (0 != gAppUtilIssUb960Cfg_updateSlaveAddr[nIdx].nDelay)
            {
                count = gAppUtilIssUb960Cfg_updateSlaveAddr[nIdx].nDelay;
                if(count)
                {
                    Task_sleep(count);
                }
            }
        }
    }

    return retVal;
}

Int32 IssUtils_getDebugRegVal(UInt32 instId,
                                  UInt32 sensorDrvId,
                                  const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                                  BspUtils_Ub960DebugRegData *pDebugStatus)
{
    Int32   retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt = 0;

    for (cnt = 0;cnt < gAppUtilIssUB96xdebugStatus.numofReg; cnt++)
    {
        /* read deserializer version number */
        retVal += Bsp_deviceRead8(
                    UB960_ACCESSIBLE_FROM_I2C_INST,
                    pSlaveAddr->slaveAddr,
                    &gAppUtilIssUB96xdebugStatus.ub96xdebugData[cnt].regAddr,
                    &pDebugStatus->ub96xdebugData[cnt].regValue,
                    (UInt32) 1U);
        pDebugStatus->ub96xdebugData[cnt].regAddr =
                gAppUtilIssUB96xdebugStatus.ub96xdebugData[cnt].regAddr;
    }
    pDebugStatus->numofReg = gAppUtilIssUB96xdebugStatus.numofReg;
    return retVal;
}

static Int32 configDeserializer(UInt32 instId, BspUtils_Ub960I2cParams * desCfgScript, UInt16 numDesRegs, Bool sensorBroadcast)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    UInt8 regAddr, regVal, delay;
    BspUtils_Ub960I2cParams *pUb960I2cPrm;
    UInt32 nIdx;
    UInt32 count = 0U;

    pUb960I2cPrm = desCfgScript;

    count = 0U;
    for (nIdx = 0U;nIdx < numDesRegs;nIdx++)
    {
        regAddr = ((pUb960I2cPrm + nIdx)->nRegAddr);
        regVal = ((pUb960I2cPrm + nIdx)->nRegValue);

        if(TRUE == sensorBroadcast)
        {
                /* Enable broadcast : Set all serializer aliases to cam0 */
                if (0x65 == regAddr)
                {
                        regVal = (gAppUtilIssSlaveAliases[instId].rSlave1Addr[0]) << 1U;
                }else if (0x66 == regAddr)
                {
                        /* Enable broadcast : Set all sensor aliases to cam0 */
                        regVal = (gAppUtilIssSlaveAliases[instId].rSlave2Addr[0]) << 1U;
                }
        }
        else
        {
            if (0x65 == regAddr)
            {
                    regVal = (gAppUtilIssSlaveAliases[instId].rSlave1Addr[count]) << 1U;
            }else if (0x66 == regAddr)
            {
                    /* Enable broadcast : Set all sensor aliases to cam0 */
                    regVal = (gAppUtilIssSlaveAliases[instId].rSlave2Addr[count]) << 1U;
                    count++;
            }
        }

        if (0x33 == regAddr)
        {
            if(instId == 0)
            {
                /* Use 4 lane for csi2-0 phy instance */
                regVal = 0x03;
            }
            else
            {
                /* use 2 lane for csi2-1 phy instance */
                regVal = 0x23;
            }
        }

        retVal = Bsp_deviceWrite8(
            UB960_ACCESSIBLE_FROM_I2C_INST,
            gAppUtilIssSlaveAliases[instId].slaveAddr,
            (const UInt8*)(&regAddr),
            (const UInt8*)(&regVal),
            (UInt32) 1U);
        if (retVal != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf("Could not configure deserializer !!!\r\n");
            break;
        }else
        {
            delay = (pUb960I2cPrm + nIdx)->nDelay;
            if(delay)
            {
                Task_sleep(delay);
            }
        }        
    }
    return retVal;
}

static Int32 configSerializer(UInt32 i2cDevAddr, BspUtils_Ub960I2cParams* serCfgScript, UInt16 numSerRegs)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    UInt8 regAddr, regVal, delay;
    BspUtils_Ub960I2cParams *pSerI2cPrm = serCfgScript;
    UInt32  nIdx;

    for (nIdx = 0U;nIdx < numSerRegs;nIdx++)
    {
        regAddr = (pSerI2cPrm + nIdx)->nRegAddr;
        regVal = (pSerI2cPrm + nIdx)->nRegValue;
        retVal = Bsp_deviceWrite8(
            UB960_ACCESSIBLE_FROM_I2C_INST,
            i2cDevAddr,
            (const UInt8*)(&regAddr),
            (const UInt8*)(&regVal),
            (UInt32) 1U);
        if (retVal != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf("Could not configure serializer !!!\r\n");
            break;
        }else
        {
            delay = (pSerI2cPrm + nIdx)->nDelay;
            if(delay)
            {
                Task_sleep(delay);
            }
        }        
    }
    return retVal;
}

static Int32 setCameraPower(BspUtils_FpdCamPowerLevel pwrlvl)
{
#ifdef BOARD_TYPE_TDA3XX_RVP
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    /*
    *	The UB960 power ON on RVP should be done only once.
    *	These flags prevent UB960 power ON for subsequent init sequences.
    */
    static Bool gSetPowerDone = (UInt32)FALSE;
    Bsp_BoardRev rvpBoardRev;

    if((UInt32)FALSE == gSetPowerDone)
    {
        rvpBoardRev = Bsp_boardGetBaseBoardRev();

        if((rvpBoardRev == BSP_BOARD_REV_BETA) ||
           (rvpBoardRev == BSP_BOARD_REV_A) ||
           (rvpBoardRev == BSP_BOARD_REV_A_4G) ||
           (rvpBoardRev == BSP_BOARD_REV_DASH_4G) ||
           (rvpBoardRev == BSP_BOARD_REV_DASH_2G_STP) ||
           (rvpBoardRev == BSP_BOARD_REV_DASH_4G_STP) ||
           (rvpBoardRev == BSP_BOARD_REV_A_2G))
        {
            uint32_t Enable_FPD_Power_Out_Base = SOC_GPIO2_BASE;
            uint32_t Enable_FPD_Power_Out_Pin  = 10; /* 0 = disable, 1 = enable */
            uint32_t Voltage_Select_5V12V_Base = SOC_GPIO2_BASE;
            uint32_t Voltage_Select_5V12V_Pin  = 12; /* 0 = 5v5, 1 = 12v */
            uint32_t LoadSwitch_IN_Base = SOC_GPIO2_BASE;
            uint32_t LoadSwitch_IN_Pin  = 13; /* 0 = disable, 1 = enable */

            Vps_printf("D3 RVP UB96x Power Up" );

            switch (pwrlvl)
            {
                case BSPUTILS_FPDCAMPOWERLEVEL_OFF:
                    GPIOPinWrite(Enable_FPD_Power_Out_Base, Enable_FPD_Power_Out_Pin, 0);
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 0);
                    break;

                case BSPUTILS_FPDCAMPOWERLEVEL_5V5:
                    /* disable power */
                    GPIOPinWrite(Enable_FPD_Power_Out_Base, Enable_FPD_Power_Out_Pin, 0);
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 0);
                    Task_sleep(10);

                    /* set 5v5 */
                    GPIOPinWrite(Voltage_Select_5V12V_Base, Voltage_Select_5V12V_Pin, 0);
                    Task_sleep(10);

                    /* enable VDD_FPD */
                    GPIOPinWrite(Enable_FPD_Power_Out_Base, Enable_FPD_Power_Out_Pin, 1);
                    Task_sleep(10);

                    /* enable output power */
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 1);
                    break;

                case BSPUTILS_FPDCAMPOWERLEVEL_12V0:
                    /* disable power */
                    GPIOPinWrite(Enable_FPD_Power_Out_Base, Enable_FPD_Power_Out_Pin, 0);
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 0);
                    Task_sleep(10);

                    /* set 12v0 */
                    GPIOPinWrite(Voltage_Select_5V12V_Base, Voltage_Select_5V12V_Pin, 1);
                    Task_sleep(10);

                    /* enable VDD_FPD */
                    GPIOPinWrite(Enable_FPD_Power_Out_Base, Enable_FPD_Power_Out_Pin, 1);
                    Task_sleep(10);

                    /* enable output power */
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 1);
                    break;

                default:
                    Vps_printf("Unknown power option\n");
                    retVal = SYSTEM_LINK_STATUS_EFAIL;
                    break;
            }
        }
        else if((rvpBoardRev == BSP_BOARD_REV_STARTER_KIT_REV_1) ||
                (rvpBoardRev == BSP_BOARD_REV_STARTER_KIT_REV_DASH))
        {
            uint32_t LoadSwitch_IN_Base = SOC_GPIO3_BASE;
            uint32_t LoadSwitch_IN_Pin  = 23; /* 0 = disable, 1 = enable */
            Vps_printf(" D3 Starter Kit UB96x Power Up" );

            switch (pwrlvl)
            {
                case BSPUTILS_FPDCAMPOWERLEVEL_OFF:
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 0);
                    break;

                case BSPUTILS_FPDCAMPOWERLEVEL_5V5: /* Unsupported in SK hardware */
                        Vps_printf("ERROR: 5V5 FPD Link power option not available!  Using 12V.\n");
                        /* fall through... */

                case BSPUTILS_FPDCAMPOWERLEVEL_12V0:
                    /* enable output power */
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 1);
                    break;

                default:
                    Vps_printf("Unknown power option\n");
                    retVal = SYSTEM_LINK_STATUS_EFAIL;
                    break;
            }
        }
        else if(rvpBoardRev == BSP_BOARD_MAX)
        {
            Vps_printf(
                    " Failed to detect board ID\n");
        }
        else
        {
            Vps_printf(
                    " Failed to detect board ID\n");
        }

        gSetPowerDone = (UInt32)TRUE;
    }
    else
    {
        retVal = SYSTEM_LINK_STATUS_SOK;
    }

    return retVal;
#else
    /*
     *  UB960 EVM: Selected using jumper.
     */
    return (SYSTEM_LINK_STATUS_SOK);
#endif
}

static Int32 initDeserializer(UInt32 instId)
{
#ifdef BOARD_TYPE_TDA3XX_RVP
    Int32 retVal;
    Uint8 tempAddr, tempData;
    static Bool gInitDeserDone = (UInt32)FALSE;

    if((UInt32)FALSE == gInitDeserDone)
    {
        retVal = resetDeserializer();
        if(retVal != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf("Failed to reset deserializer\n");
        }

        tempAddr = 0x03;
        tempData = 0x00;

        /* read deserializer version number */
        retVal = Bsp_deviceRead8(
                        UB960_ACCESSIBLE_FROM_I2C_INST,
                        gAppUtilIssSlaveAliases[instId].slaveAddr,
                        &tempAddr,
                        &tempData,
                        (UInt32) 1U);

        /* perform unique init based on deserializer version */
        if(retVal == SYSTEM_LINK_STATUS_SOK)
        {
            /* 960 Alpha */
            if(tempData == 0x10)
            {
                Vps_printf("Detected 960 DeSerializer\n");
                writeI2Cconfig(
                            sizeof(gAppUtilIssUB960AlphaInitCfg)/sizeof(gAppUtilIssUB960AlphaInitCfg[0]),
                            gAppUtilIssUB960AlphaInitCfg,
                            gAppUtilIssSlaveAliases[instId].slaveAddr);
            }
            else if(tempData == 0x20)
            {
                Vps_printf("Detected 964 v2 DeSerializer\n");
                writeI2Cconfig(
                            sizeof(gAppUtilIssUB964AlphaInitCfg)/sizeof(gAppUtilIssUB964AlphaInitCfg[0]),
                            gAppUtilIssUB964AlphaInitCfg,
                            gAppUtilIssSlaveAliases[instId].slaveAddr);
            }
            else if(tempData == 0x30)
            {
                Vps_printf("Detected 964 v3 DeSerializer\n");
            }
            else if(tempData == 0x40)
            {
                Vps_printf(" Detected 964 v4 DeSerializer\n");
            }
            else
            {
                Vps_printf(" Unknown DeSerializer Version\n");
            }
        }
        else
        {
            Vps_printf(" Failed to read from DeSerializer\n");
        }

        gInitDeserDone = (UInt32)TRUE;
    }
    else
    {
        retVal = SYSTEM_LINK_STATUS_SOK;
    }

    return retVal;
#else
    return (SYSTEM_LINK_STATUS_SOK);
#endif
}

Int32 IssUtils_appUb960EnableFsin(UInt32 instId,
                                  UInt32 sensorDrvId,
                                  const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                                  const BspUtils_Ub960Status *pStatus)
{
    Int32   retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32  nIdx, numRegs;
    BspUtils_Ub960I2cParams *pUb960I2cPrm;
    BspUtils_Ub960I2cParams ub960I2cPrm[] = {
        {0x19, 0x01, 0x0},
        {0x1A, 0x15, 0x0},
        {0x1B, 0x09, 0x0},
        {0x1C, 0xC3, 0x0},
        {0x18, 0x01, 0x64}, /* Start FSIN. Delay to allow it to stabilize */
        {0x4C, 0x01, 0x0},
        {0x6e, 0x9A, 0x0},   /* Send FSIN on BC_GPIO0 RX0 */
        {0x4C, 0x12, 0x0},
        {0x6e, 0x9A, 0x0},   /* Send FSIN on BC_GPIO0 RX1 */
        {0x4C, 0x24, 0x0},
        {0x6e, 0x9A, 0x0},   /* Send FSIN on BC_GPIO0 RX2 */
        {0x4C, 0x38, 0x0},
        {0x6e, 0x9A, 0x0}    /* Send FSIN on BC_GPIO0 RX3 */
    };
    Int32 count;

    pUb960I2cPrm = &ub960I2cPrm[0];
    numRegs = sizeof (ub960I2cPrm)/sizeof (ub960I2cPrm[0U]);

    if ((NULL != pStatus) && (NULL != pSlaveAddr))
    {
        retVal = SYSTEM_LINK_STATUS_SOK;
        gAppUtilIssSlaveAliases[instId].slaveAddr = pSlaveAddr->slaveAddr;
        gAppUtilIssSlaveAliases[instId].numSource = pSlaveAddr->numSource;
    }

    for (nIdx = 0U;nIdx < numRegs;nIdx++)
    {
        retVal = Bsp_deviceWrite8(
            UB960_ACCESSIBLE_FROM_I2C_INST,
            gAppUtilIssSlaveAliases[instId].slaveAddr,
            &((pUb960I2cPrm + nIdx)->nRegAddr),
            &((pUb960I2cPrm + nIdx)->nRegValue),
            (UInt32) 1U);

        if (retVal != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf("Could not configure UB960 !!!\r\n");
            break;
        }

        if (0 != (pUb960I2cPrm + nIdx)->nDelay)
        {
            count = (pUb960I2cPrm + nIdx)->nDelay;
            while (count)
            {
                count--;
            }
        }
    }

    for (nIdx = 0U; nIdx < gAppUtilIssSlaveAliases[instId].numSource; nIdx++)
    {
        IssUtils_appInitUB913PassThroughGPIO0(instId, nIdx);
    }

    return (retVal);
}

static Int32 IssUtils_appInitUB913PassThroughGPIO0(UInt32 instId, UInt32 portId)
{
    Int32   retVal = SYSTEM_LINK_STATUS_SOK;
    UInt32  nIdx;
    UInt32 i2cDevAddr = 0U, numRegs;
    volatile UInt32 count;
    BspUtils_Ub960I2cParams *pSerCfg = NULL;
    BspUtils_Ub960I2cParams gUB913PassThruGPIO0[] = {
        {0x0D, 0x9D, 0x0},
    };

    pSerCfg = &gUB913PassThruGPIO0[0U];
    numRegs = sizeof (gUB913PassThruGPIO0) /
                            sizeof (gUB913PassThruGPIO0[0U]);

    if (BSPUTILS_UB960EVM_MAX_PORTS > portId)
    {
        i2cDevAddr = gAppUtilIssSlaveAliases[instId].rSlave1Addr[portId];
    }
    else
    {
        Vps_printf("Wrong instance of UB913 Ser !!!\r\n");
        retVal = BSP_EFAIL;
    }

    for (nIdx = 0U; ((nIdx < numRegs) && (SYSTEM_LINK_STATUS_SOK == retVal)); nIdx++)
    {
        retVal = Bsp_deviceWrite8(
            UB960_ACCESSIBLE_FROM_I2C_INST,
            i2cDevAddr,
            &(pSerCfg[nIdx].nRegAddr),
            &(pSerCfg[nIdx].nRegValue),
            (UInt32) 1U);
        if (retVal != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf("Could not configure UB913 Ser !!!\r\n");
            break;
        }

        if (0 != (pSerCfg + nIdx)->nDelay)
        {
            count = (pSerCfg + nIdx)->nDelay;
            while (count)
            {
                count--;
            }
        }
    }

    return (retVal);
}

#ifdef BOARD_TYPE_TDA3XX_RVP
static Int32 resetDeserializer(void)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    Uint8 tempAddr, tempData;

    tempAddr = 7;
    tempData = 0;
    retVal |= Bsp_deviceRead8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);
    tempData &= 0xEF;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);

    /* Toggle expander bit 4 for reset */
    tempAddr  = 3;
    tempData = 0;
    retVal |= Bsp_deviceRead8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);
    tempData |= 0x10;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,1U);
    Task_sleep(100);
    tempData &= 0xEF;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);

    Task_sleep(100);
    tempData |= 0x10;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);
    Task_sleep(100);

    return (retVal);
}

static Int32 writeI2Cconfig(Int32 regCount, BspUtils_Ub960I2cParams *params, UInt32 slaveAddr)
{
    Int32   retVal = SYSTEM_LINK_STATUS_SOK;
    UInt32 nIdx;
    Int32 count;

    for (nIdx = 0U;nIdx < regCount; nIdx++)
    {
        retVal = Bsp_deviceWrite8(
                        UB960_ACCESSIBLE_FROM_I2C_INST,
                        slaveAddr,
                        &(params[nIdx].nRegAddr),
                        &(params[nIdx].nRegValue),
                        (UInt32) 1U);

        if (retVal != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf("Could not configure UB960 !!!\n");
            break;
        }

        if (0 != params[nIdx].nDelay)
        {
            count = params[nIdx].nDelay;
            while (count)
            {
                count --;
            }
        }
    }

    return retVal;
}
#endif /*BOARD_TYPE_TDA3XX_RVP*/



