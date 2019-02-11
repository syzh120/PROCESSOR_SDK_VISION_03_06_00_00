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
 * \file video_sensor.c
 *
 * \brief  This file has the implementataion of Sensor Control API
 *
 *         Sensor APIs can be used to control external sensors.
 *         Drivers for sensors can be part of BSP or any other package.
 *
 *
 * \version 0.0 (Jun 2013) : [CM] First version
 * \version 0.1 (Jul 2013) : [CM] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#if defined(BIOS_BUILD)
#include <xdc/std.h>
#endif

#include <src/sensor_priv.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/vps.h>

#include <src/rtos/utils_common/include/utils_mem.h>



/**
 *******************************************************************************
 *
 * \brief Set the default Create Params for OVI sensor params .
 *
 * \param  createParams   [IN] Create parameters for Sensor
 *
 *******************************************************************************
*/
Void VidSensor_CreateParams_Init(VidSensor_CreateParams *createParams)
{
    UInt32 i;

    createParams->sensorId       = VID_SENSOR_OV10635;
    createParams->vipInstId[0]   = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    createParams->standard       = SYSTEM_STD_720P_60;
    createParams->dataformat     = SYSTEM_DF_YUV422I_UYVY;
    createParams->videoIfWidth   = SYSTEM_VIFW_8BIT;
    createParams->fps            = SYSTEM_FPS_30;
    createParams->isLVDSCaptMode = FALSE;
    createParams->numChan        = 1;
    createParams->videoIfMode    = SYSTEM_VIFM_SCH_DS_AVID_VSYNC;

    for (i = 0u; i < VIDEO_SENSOR_MAX_LVDS_CAMERAS; i ++)
    {
        createParams->sensorHandle[i] = NULL;
    }
}

/**
 *******************************************************************************
 *
 * \brief Create function to create video sensor.
 *
 *        Creates the sensor handle using bsp function calls.
 *
 * \param  createParams   [IN] Create parameters for Sensor
 * \param  createStatus   [OUT] Status
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 VidSensor_create(VidSensor_CreateParams *createParams,
                        VidSensor_CreateStatus *createStatus)
{
    Int32  retVal = SYSTEM_LINK_STATUS_EFAIL,chanNum;
    UInt32 sensorInstId, sensorI2cInstId, sensorI2cAddr, sensorDrvId;
    Bsp_VidSensorChipIdParams sensorChipIdPrms;
    Bsp_VidSensorChipIdStatus sensorChipIdStatus;
    Bsp_VidSensorCreateStatus sensorCreateStatus;
    Bsp_VidSensorCreateParams sensorCreateParams;
    Bsp_BoardMode   boardMode;
    BspUtils_Ub960SourceI2cAddr ub964I2cAddr;
    BspUtils_Ub960Status        ub964Status;
    
    createStatus->retVal = SYSTEM_LINK_STATUS_EFAIL;
    sensorDrvId = VID_SENSOR_MAX;
    if(createParams->sensorId==VID_SENSOR_OV10635
        ||
        createParams->sensorId==VID_SENSOR_OV10630
        )
    {
        sensorDrvId = FVID2_VID_SENSOR_OV1063X_DRV;
    }
    else if(createParams->sensorId==VID_SENSOR_MT9M024)
    {
        sensorDrvId = BSP_VID_SENSOR_MT9M024;
    }
    else if(createParams->sensorId==VID_SENSOR_MULDES_OV1063X)
    {
        sensorDrvId = FVID2_VID_SENSOR_MULDES_OV1063X_DRV;
    }
    else if(createParams->sensorId==VID_SENSOR_MULDES_AR0132RCCC)
    {
        sensorDrvId = FVID2_VID_SENSOR_APT_AR0132RCCC_DRV;
    }
    else if(createParams->sensorId==VID_SENSOR_SAT0088_OV1063X)
    {
        sensorDrvId = FVID2_VID_SENSOR_MULDES_OV1063X_DRV;
    }
    else if(createParams->sensorId==VID_SENSOR_MULDES_IMX290)
    {
        sensorDrvId = FVID2_VID_SENSOR_GW4200_IMX290_DRV;
    }
    else if(createParams->sensorId==VID_SENSOR_MULDES_OV490)
    {
        sensorDrvId = FVID2_VID_SENSOR_MULDES_OV490_DRV;
    }
    else
    {
        /* unsupported sensor */
        UTILS_assert(0);
    }


    retVal = SYSTEM_LINK_STATUS_SOK;
    /* Initialize UB964 */
    if(VID_SENSOR_SAT0088_OV1063X == createParams->sensorId)
    {
        retVal = Bsp_boardSetPinMux(BSP_DRV_ID_I2C,
                                    BSP_DEVICE_I2C_INST_ID_4,
                                    BSP_BOARD_MODE_DEFAULT);

        ub964I2cAddr.slaveAddr       = UB960_SLAVE_ADDR;
        ub964I2cAddr.numSource       = createParams->numChan;

        for(chanNum = 0 ; chanNum < createParams->numChan ;chanNum++)
        {
            sensorI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
                                        sensorDrvId,
                                        FVID2_VPS_CAPT_VID_DRV,
                                        createParams->vipInstId[chanNum]);

            ub964I2cAddr.rSlave2Addr[chanNum] = sensorI2cAddr;
            ub964I2cAddr.rSlave1Addr[chanNum] =
                                            BspUtils_getSerAddrSat0088(chanNum);
        }
        retVal = BspUtils_appInitUb960(0U, sensorDrvId, &ub964I2cAddr,
                                                        &ub964Status);
        UTILS_assert (retVal == 0);
        Vps_printf(" VIDEO_SENSOR: Detected %d Camera modules !!!\n",
                        ub964Status.numDetected);
    }

    for(chanNum = 0 ; ((chanNum < createParams->numChan) &&
                       (SYSTEM_LINK_STATUS_SOK == retVal)) ;chanNum++)
    {
        sensorInstId = Bsp_boardGetVideoDeviceInstId(
                sensorDrvId,
                FVID2_VPS_CAPT_VID_DRV,
                createParams->vipInstId[chanNum]);
        sensorI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
                sensorDrvId,
                FVID2_VPS_CAPT_VID_DRV,
                createParams->vipInstId[chanNum]);
        sensorI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
                    sensorDrvId,
                    FVID2_VPS_CAPT_VID_DRV,
                    createParams->vipInstId[chanNum]);

        /* set capture port pinmux based on video interface bus width */
        if(createParams->videoIfWidth==SYSTEM_VIFW_8BIT)
        {
            boardMode = BSP_BOARD_MODE_VIDEO_8BIT;
        }
        else
        if(createParams->videoIfWidth==SYSTEM_VIFW_10BIT)
        {
            boardMode = BSP_BOARD_MODE_VIDEO_10BIT;
        }
        else
        if(createParams->videoIfWidth==SYSTEM_VIFW_12BIT)
        {
            boardMode = BSP_BOARD_MODE_VIDEO_12BIT;
        }
        else
        if(createParams->videoIfWidth==SYSTEM_VIFW_14BIT)
        {
            boardMode = BSP_BOARD_MODE_VIDEO_14BIT;
        }
        else
        if(createParams->videoIfWidth==SYSTEM_VIFW_16BIT)
        {
            boardMode = BSP_BOARD_MODE_VIDEO_16BIT;
        }
        else
        if(createParams->videoIfWidth==SYSTEM_VIFW_24BIT)
        {
            boardMode = BSP_BOARD_MODE_VIDEO_24BIT;
        }
        else if ((SYSTEM_VIFW_4LANES == createParams->videoIfWidth) ||
                 (SYSTEM_VIFW_3LANES == createParams->videoIfWidth)||
                 (SYSTEM_VIFW_2LANES == createParams->videoIfWidth)||
                 (SYSTEM_VIFW_1LANES == createParams->videoIfWidth))
        {
            boardMode = BSP_BOARD_MODE_NONE;
        }
        else
        {
            /* assume 8-bit mode if no match found */
            boardMode = BSP_BOARD_MODE_VIDEO_8BIT;
        }

        if(VID_SENSOR_SAT0088_OV1063X != createParams->sensorId)
        {
            retVal = Bsp_boardSetPinMux(FVID2_VPS_CAPT_VID_DRV,
                                    createParams->vipInstId[chanNum],
                                    boardMode);
            UTILS_assert (retVal == 0);

             /* Power on video sensor at board level mux */
            retVal = Bsp_boardPowerOnDevice(sensorDrvId, sensorInstId, TRUE);
            UTILS_assert (retVal == 0);

            if (SYSTEM_LINK_STATUS_SOK == retVal)
            {
                /* select video sensor at board level mux */
                retVal = Bsp_boardSelectDevice(sensorDrvId, sensorInstId);
                if (SYSTEM_LINK_STATUS_SOK != retVal)
                {
                    Vps_printf(" VIDEO_SENSOR: Device select failed !!!\n");
                }
            }

            retVal = Bsp_boardSelectMode(
                             sensorDrvId,
                             sensorInstId,
                             boardMode);
            if (SYSTEM_LINK_STATUS_SOK != retVal)
            {
                Vps_printf(" VIDEO_SENSOR: Board select failed !!!\n");
            }

            Vps_printf(" VIDEO_SENSOR: INST%d : I2C%d : I2C Addr = 0x%x\n",
                    sensorInstId, sensorI2cInstId, sensorI2cAddr);

            if (SYSTEM_LINK_STATUS_SOK == retVal)
            {
                if (Bsp_boardIsTda2xxRvp() || 
                    ((BSP_BOARD_MULTIDES == Bsp_boardGetId()) &&
                    (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == sensorDrvId)))
                {
                    retVal = BspUtils_appConfSerDeSer(sensorDrvId, sensorInstId);
                    if (retVal != SYSTEM_LINK_STATUS_SOK)
                    {
                        Vps_printf(" VIDEO_SENSOR: MULTI_DES: Configuring instance %d failed !!!\n",sensorInstId);
                    }
                }
                if ((BSP_BOARD_MULTIDES == Bsp_boardGetId()) &&
                    (FVID2_VID_SENSOR_GW4200_IMX290_DRV == sensorDrvId))
                {
                    retVal = BspUtils_appConfSerDeSer(sensorDrvId, sensorInstId);
                    if (retVal != SYSTEM_LINK_STATUS_SOK)
                    {
                        Vps_printf(" VIDEO_SENSOR: MULTI_DES: Configuring instance %d failed !!!\n",sensorInstId);
                    }
                }
            }
            sensorCreateParams.deviceI2cInstId    = sensorI2cInstId;
            sensorCreateParams.numDevicesAtPort   = 1u;
            sensorCreateParams.deviceI2cAddr[0]   = sensorI2cAddr;
            sensorCreateParams.deviceResetGpio[0] = BSP_VID_SENSOR_GPIO_NONE;
            sensorCreateParams.sensorCfg          = NULL;
            sensorCreateParams.numSensorCfg       = 0U;
        }
        else
        {
            sensorCreateParams.deviceI2cInstId    = sensorI2cInstId;
            sensorCreateParams.numDevicesAtPort   = 1u;
            sensorCreateParams.deviceI2cAddr[0]   =
                                            ub964I2cAddr.rSlave2Addr[chanNum];
            sensorCreateParams.deviceResetGpio[0] = BSP_VID_SENSOR_GPIO_NONE;
            sensorCreateParams.sensorCfg          = NULL;
            sensorCreateParams.numSensorCfg       = 0U;
        }

        createParams->sensorHandle[chanNum] = Fvid2_create(
                                                        sensorDrvId,
                                                        sensorInstId,
                                                        &sensorCreateParams,
                                                        &sensorCreateStatus,
                                                        NULL);
        if (createParams->sensorHandle[chanNum] == NULL)
        {
            if (chanNum != 4)
            {
                createStatus->retVal = SYSTEM_LINK_STATUS_EFAIL;
            }
            else
            {
                /* Continue the use case if the front camera sensor is not connected. */
                createStatus->retVal = SYSTEM_LINK_STATUS_SOK;
                Vps_printf(
                " VIDEO_SENSOR: WARNING: Front Camera Sensor is NOT Connected !!! \n");
                /* Avoid sending any more command to front camera sensor. */
                createParams->numChan -= 1;
            }
        }
        else
        {
            /* Get the Features supported by Sensor */
            retVal = Fvid2_control(createParams->sensorHandle[chanNum],
                                   IOCTL_BSP_VID_SENSOR_GET_FEATURES,
                                   &createParams->sensorFeatures[chanNum],
                                   NULL);
            UTILS_assert (retVal == 0);

            if(Bsp_platformIsTda3xxFamilyBuild())
            {
                if(sensorDrvId==FVID2_VID_SENSOR_OV1063X_DRV)
                {
                    Bsp_VidSensorFlipParams flipParams;

                    flipParams.hFlip = TRUE;
                    flipParams.vFlip = TRUE;

                    retVal = Fvid2_control( createParams->sensorHandle[chanNum],
                                        IOCTL_BSP_VID_SENSOR_SET_FLIP_PARAMS,
                                        &flipParams,
                                        NULL);
                    UTILS_assert (retVal == 0);

                    Vps_printf(
                        " VIDEO_SENSOR: Flipping sensor output in H and V direction\n");
                }
            }
            sensorChipIdPrms.deviceNum = 0;
            retVal = Fvid2_control( createParams->sensorHandle[chanNum],
                                    IOCTL_BSP_VID_SENSOR_GET_CHIP_ID,
                                    &sensorChipIdPrms,
                                    &sensorChipIdStatus);
            UTILS_assert (retVal == 0);

            Vps_printf(
                " VIDEO_SENSOR: VIP %d: DRV ID %04x (I2C ADDR 0x%02x): %04x:%04x:%04x\n",
                    createParams->vipInstId[chanNum],
                    sensorDrvId,
                    sensorCreateParams.deviceI2cAddr[0],
                    sensorChipIdStatus.chipId,
                    sensorChipIdStatus.chipRevision,
                    sensorChipIdStatus.firmwareVersion);

            /* In case of VID_SENSOR_SAT0088_OV1063X, the data format change
                to FVID2_DF_YUV422I_YUYV is supported */
            if ((TRUE == createParams->sensorFeatures[chanNum].isSetCfgSupported)
                ||
                (VID_SENSOR_SAT0088_OV1063X == createParams->sensorId))
            {
                Bsp_VidSensorConfigParams configParams;
                configParams.videoIfWidth = createParams->videoIfWidth;
                configParams.dataformat   = createParams->dataformat;
                configParams.standard     = createParams->standard;
                configParams.fps          = createParams->fps;
                retVal =
                    Fvid2_control(createParams->sensorHandle[chanNum], IOCTL_BSP_VID_SENSOR_SET_CONFIG,
                                &configParams,
                                NULL);
                UTILS_assert (retVal == 0);

            }

            createStatus->retVal = retVal;
        }
    }
    return (createStatus->retVal);
}
/*******************************************************************************
 *
 * \brief Delete function to delete video sensor.
 *
 *        Deletes the sensor handle using Fvid2_delete function calls.
 *
 * \param  handle         [IN] Handle to delete the sensor
 *
 * \param  deleteArgs      Not used.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 VidSensor_delete(VidSensor_CreateParams *createParams,
                       Ptr deleteArgs)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Int32 chanNum, sensorInstId, sensorDrvId;

    sensorDrvId = VID_SENSOR_MAX;
    if(createParams->sensorId==VID_SENSOR_OV10635
        ||
        createParams->sensorId==VID_SENSOR_OV10630
        )
    {
        sensorDrvId = FVID2_VID_SENSOR_OV1063X_DRV;
    }
    else if(createParams->sensorId==VID_SENSOR_MT9M024)
    {
        sensorDrvId = BSP_VID_SENSOR_MT9M024;
    }
    else if(createParams->sensorId==VID_SENSOR_MULDES_OV1063X)
    {
        sensorDrvId = FVID2_VID_SENSOR_MULDES_OV1063X_DRV;
    }
    else if(createParams->sensorId==VID_SENSOR_MULDES_AR0132RCCC)
    {
        sensorDrvId = FVID2_VID_SENSOR_APT_AR0132RCCC_DRV;
    }
    else if(createParams->sensorId==VID_SENSOR_SAT0088_OV1063X)
    {
        sensorDrvId = FVID2_VID_SENSOR_MULDES_OV1063X_DRV;
    }
    else if(createParams->sensorId==VID_SENSOR_MULDES_IMX290)
    {
        sensorDrvId = FVID2_VID_SENSOR_GW4200_IMX290_DRV;
    }
    else if(createParams->sensorId==VID_SENSOR_MULDES_OV490)
    {
        sensorDrvId = FVID2_VID_SENSOR_MULDES_OV490_DRV;
    }
    else
    {
        UTILS_assert(0);
        /* For Misra C */
    }
    UTILS_assert(sensorDrvId != VID_SENSOR_MAX);

    for(chanNum = 0; chanNum < createParams->numChan; chanNum++)
    {
        sensorInstId = Bsp_boardGetVideoDeviceInstId(
                        sensorDrvId,
                        FVID2_VPS_CAPT_VID_DRV,
                        createParams->vipInstId[chanNum]);

        if(createParams->sensorHandle[chanNum] != NULL)
        {
            status = Fvid2_delete(
                        (Fvid2_Handle)createParams->sensorHandle[chanNum],
                        NULL);
        }

        if (Bsp_boardIsTda2xxRvp() || 
            ((BSP_BOARD_MULTIDES == Bsp_boardGetId()) &&
            (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == sensorDrvId)))
        {
            status   =  BspUtils_appDeConfSerDeSer(sensorDrvId, sensorInstId);
        }

        /* In case of SAT0088_OV1063X, we reset the sensor from UB964 and hence
            skipping the de-initialization of sensor via 913 */
    }

    if (VID_SENSOR_SAT0088_OV1063X == createParams->sensorId)
    {
        status = BspUtils_appDeInitUb960(0U, createParams->sensorId);
    }
    return status;
}

/*******************************************************************************
 *
 * \brief Control function to start stop and reset video sensor.
 *
 *        Control the sensor operation liske start and stop of the sensor using
 *        Fvid2 calls.
 *        Sensor reset is performed using IOCTL call IOCTL_BSP_VID_SENSOR_RESET
 *
 * \param  handle        [IN] Handle to control the sensor.
 *
 * \param  cmd           [IN] Control command for sensor
 *
 * \param  cmdArgs       [IN] Arguments for command if any.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 VidSensor_control(VidSensor_CreateParams *createParams,
                        UInt32 cmd,
                        Ptr    cmdArgs,
                        UInt32 cmdStatusArgs)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Int32 chanNum;

    if(cmd==VID_SENSOR_CMD_START)
    {
        for(chanNum = 0; chanNum < createParams->numChan; chanNum++)
        {
            status = Fvid2_start(
                            (Fvid2_Handle)createParams->sensorHandle[chanNum],
                             NULL);
        }
    }
    else if(cmd==VID_SENSOR_CMD_STOP)
    {
        for(chanNum = 0; chanNum < createParams->numChan; chanNum++)
        {
            status = Fvid2_stop(
                        (Fvid2_Handle)createParams->sensorHandle[chanNum],
                         NULL);
        }
    }
    else if(cmd==VID_SENSOR_CMD_RESET)
    {
        for(chanNum = 0; chanNum < createParams->numChan; chanNum++)
        {
            status = Fvid2_control(
                        (Fvid2_Handle)createParams->sensorHandle[chanNum],
                        IOCTL_BSP_VID_SENSOR_RESET,
                        NULL, NULL);
        }
    }

    return status;
}
