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
 * \file Chains_iss.c
 *
 *
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <iss_sensor_if.h>
/**< ISS AEWB plugin is included here to get the default AEWB configuration
     from each sensor */
#include <algorithmLink_issAewb.h>

#include <iss_sensor_priv.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define ISS_SENSORS_MAX_SUPPORTED_SENSOR               (20U)


/*******************************************************************************
 *  Data Structures
 *******************************************************************************
 */
typedef struct
{
    UInt32                      isUsed;
    /**< Flag to indicate if given instance is free or not */
    IssSensor_CreateParams      createPrms;
    /**< Create Parameters */
    IssSensorIf_Params          sensorPrms;
    /**< Registered Sensor's parameters */
} IssSensors_Table;



/*******************************************************************************
 *  Globals
 *******************************************************************************
 */
IssSensors_Table gIssSensorTable[ISS_SENSORS_MAX_SUPPORTED_SENSOR];

/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
static Int32 checkForHandle(Ptr handle);

/*******************************************************************************
 *  Function Definition
 *******************************************************************************
 */

Void IssSensor_Init()
{
    UInt32 cnt;

    memset (&gIssSensorTable, 0x0,
        sizeof(IssSensors_Table)*ISS_SENSORS_MAX_SUPPORTED_SENSOR);

    for (cnt = 0U; cnt < ISS_SENSORS_MAX_SUPPORTED_SENSOR; cnt ++)
    {
        gIssSensorTable[cnt].isUsed = FALSE;
    }

    IssSensor_AR0132_Init();
    IssSensor_AR0140_Init();
    IssSensor_OV10640_Init();
    IssSensor_IMX224_Init();
    IssSensor_OV10640_imi_Init();
    IssSensor_AR0140_TIDA_Init();
    IssSensor_OV2775_Init();
    IssSensor_OV2775_Tida1130_Init();
    IssSensor_AR0143_Init();
    IssSensor_AR0143_MARS_Init();
    IssSensor_IMX390_Init();
    IssSensor_AR0233_Init();
    IssSensor_AR0233_MARS_Init();
}

Int32 IssSensorIf_RegisterSensor(IssSensorIf_Params *pSensorPrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 cnt = 0U;
    IssSensors_Table *pSensorTable;

    if (NULL == pSensorPrms)
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        /* Find a free entry in the sensor table */
        for (cnt = 0U; cnt < ISS_SENSORS_MAX_SUPPORTED_SENSOR; cnt ++)
        {
            pSensorTable = &gIssSensorTable[cnt];
            if (FALSE == pSensorTable->isUsed)
            {
                /* Copy sensor params */
                memcpy(&pSensorTable->sensorPrms, pSensorPrms,
                    sizeof(IssSensorIf_Params));
                strncpy(pSensorTable->sensorPrms.name, pSensorPrms->name,
                    ISS_SENSORS_MAX_NAME);
                pSensorTable->isUsed = TRUE;
                break;
            }
        }

        if (cnt == ISS_SENSORS_MAX_SUPPORTED_SENSOR)
        {
            Vps_printf(" ISS_SENSOR: Could not register sensor \n");
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    return (status);
}

Int32 IssSensor_GetSensorInfo(char name[], IssSensor_Info *pInfo)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt;
    IssSensors_Table *pSensorTable = NULL;

    /* Check For Errors */
    if ((NULL == pInfo) || (NULL == name))
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        for (cnt = 0U; cnt < ISS_SENSORS_MAX_SUPPORTED_SENSOR; cnt ++)
        {
            pSensorTable = &gIssSensorTable[cnt];

            if (0 == strncmp(pSensorTable->sensorPrms.name, name,
                        ISS_SENSORS_MAX_NAME))
            {
                memcpy(pInfo, &pSensorTable->sensorPrms.info,
                    sizeof(IssSensor_Info));
                status = SYSTEM_LINK_STATUS_SOK;
                break;
            }
        }
    }

    return (status);
}

Int32 IssSensor_GetSensorInfoFromDccId(UInt32 dccId, IssSensor_Info *pInfo)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt;
    IssSensors_Table *pSensorTable = NULL;

    /* Check For Errors */
    if (NULL == pInfo)
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        for (cnt = 0U; cnt < ISS_SENSORS_MAX_SUPPORTED_SENSOR; cnt ++)
        {
            pSensorTable = &gIssSensorTable[cnt];

            if (pSensorTable->sensorPrms.dccId == dccId)
            {
                memcpy(pInfo, &pSensorTable->sensorPrms.info,
                    sizeof(IssSensor_Info));
                status = SYSTEM_LINK_STATUS_SOK;
                break;
            }
        }
    }

    return (status);
}

Ptr IssSensor_GetSensorHandle(char name[])
{
    UInt32 cnt;
    IssSensors_Table *pSensorTable = NULL;

    /* Check For Errors */
    if (NULL != name)
    {
        for (cnt = 0U; cnt < ISS_SENSORS_MAX_SUPPORTED_SENSOR; cnt ++)
        {
            pSensorTable = &gIssSensorTable[cnt];

            if ((TRUE == pSensorTable->isUsed) &&
                (0 == strncmp(pSensorTable->sensorPrms.name, name,
                        ISS_SENSORS_MAX_NAME)))
            {
                break;
            }
        }
    }

    return (Ptr)(pSensorTable);
}

Ptr IssSensor_Create(IssSensor_CreateParams *pCreatePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 cnt, fCnt;
    UInt32 found = FALSE, numCh;
    IssSensors_Table *pSensorTable = NULL;

    /* Check For Errors */
    if (NULL == pCreatePrms)
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        for (cnt = 0U; cnt < ISS_SENSORS_MAX_SUPPORTED_SENSOR; cnt ++)
        {
            pSensorTable = &gIssSensorTable[cnt];

            if ((TRUE == pSensorTable->isUsed) &&
                (0 == strncmp(pSensorTable->sensorPrms.name,
                        pCreatePrms->name,
                        ISS_SENSORS_MAX_NAME)))
            {
                found = TRUE;
                break;
            }
        }
    }

    if (found)
    {
        /* Check for errors */
        numCh = pCreatePrms->numChan;
        if (pCreatePrms->numChan > ISS_SENSORS_MAX_CHANNEL)
        {
            numCh = ISS_SENSORS_MAX_CHANNEL;
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }

        for (cnt = 0U; (cnt < numCh) &&
                (SYSTEM_LINK_STATUS_SOK == status); cnt ++)
        {
            /* UnSupported features must not be enabled */
            for (fCnt = 1; fCnt < ISS_SENSOR_MAX_FEATURES; fCnt = fCnt * 2)
            {
                if (((fCnt & pCreatePrms->enableFeatures[cnt]) == fCnt) &&
                    ((pSensorTable->sensorPrms.info.features & fCnt) == 0))
                {
                    status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                    break;
                }
            }

            /* Only one of Linear/TwoPassWDR/OnePassWDR can be enabled */
            fCnt = (pCreatePrms->enableFeatures[cnt] &
                (ISS_SENSOR_FEATURE_LINEAR_MODE |
                 ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE |
                 ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE));
            if ((fCnt != ISS_SENSOR_FEATURE_LINEAR_MODE) &&
                (fCnt != ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE) &&
                (fCnt != ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
        }
    }
    else
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        /* Copy Sensor parameters in the table */
        memcpy(&pSensorTable->createPrms, pCreatePrms,
            sizeof(IssSensor_CreateParams));
    }

    if (status != SYSTEM_LINK_STATUS_SOK)
    {
        pSensorTable = NULL;
    }

    return (Ptr)(pSensorTable);
}

Int32 IssSensor_Delete(Ptr handle)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssSensors_Table *pSensorTable;

    /* Check if the handle is valid or not */
    status = checkForHandle(handle);

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        pSensorTable = (IssSensors_Table *)handle;

        memset(&pSensorTable->createPrms, 0,
            sizeof(IssSensor_CreateParams));
    }

    return (status);
}

Int32 IssSensor_Start(Ptr handle, UInt32 chId)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    IssSensors_Table *pSensorTable;

    /* Check if the handle is valid or not */
    status = checkForHandle(handle);

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        pSensorTable = (IssSensors_Table *)handle;

        if ((NULL != pSensorTable->sensorPrms.start) &&
            (chId < pSensorTable->createPrms.numChan))
        {
            status = pSensorTable->sensorPrms.start(chId,
                &pSensorTable->createPrms);
        }
    }

    return (status);
}

Int32 IssSensor_Stop(Ptr handle, UInt32 chId)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    IssSensors_Table *pSensorTable;

    /* Check if the handle is valid or not */
    status = checkForHandle(handle);

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        pSensorTable = (IssSensors_Table *)handle;

        if ((NULL != pSensorTable->sensorPrms.stop) &&
            (chId < pSensorTable->createPrms.numChan))
        {
            status = pSensorTable->sensorPrms.stop(chId,
                &pSensorTable->createPrms);
        }
    }

    return (status);
}

Int32 IssSensor_Control(Ptr handle, UInt32 cmd,
    Ptr cmdArgs, Ptr cmdRetArgs)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssSensors_Table *pSensorTable;

    /* Check if the handle is valid or not */
    status = checkForHandle(handle);

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        pSensorTable = (IssSensors_Table *)handle;

        switch (cmd)
        {
            case ISS_SENSORS_IOCTL_GET_EXPOSURE_PARAMS:
                status = SYSTEM_LINK_STATUS_EFAIL;
                if (NULL != cmdArgs)
                {
                    IssSensor_ExposureParams *pExpPrms =
                        (IssSensor_ExposureParams *)cmdArgs;

                    if ((NULL != pSensorTable->sensorPrms.getExpParams) &&
                        (pExpPrms->chId < pSensorTable->createPrms.numChan))
                    {
                        status = pSensorTable->sensorPrms.getExpParams(
                            &pSensorTable->createPrms, pExpPrms);
                    }
                }

                break;
            case ISS_SENSORS_IOCTL_SET_AE_PARAMS:
                status = SYSTEM_LINK_STATUS_EFAIL;
                if (NULL != cmdArgs)
                {
                    IssSensor_AeParams *pAePrms =
                        (IssSensor_AeParams *)cmdArgs;

                    if ((NULL != pSensorTable->sensorPrms.setAeParams) &&
                        (pAePrms->chId < pSensorTable->createPrms.numChan))
                    {
                        status = pSensorTable->sensorPrms.setAeParams(
                            &pSensorTable->createPrms, pAePrms);
                    }
                }

                break;
            case ISS_SENSORS_IOCTL_GET_DCC_PARAMS:
                status = SYSTEM_LINK_STATUS_EFAIL;
                if (NULL != cmdArgs)
                {
                    IssSensor_DccParams *pDccPrms =
                        (IssSensor_DccParams *)cmdArgs;

                    if ((NULL != pSensorTable->sensorPrms.getDccParams) &&
                        (pDccPrms->chId < pSensorTable->createPrms.numChan))
                    {
                        status = pSensorTable->sensorPrms.getDccParams(
                            &pSensorTable->createPrms, pDccPrms);
                    }
                }

                break;
            case ISS_SENSORS_IOCTL_INIT_AEWB_CONFIG:
                status = SYSTEM_LINK_STATUS_EFAIL;
                if (NULL != cmdArgs)
                {
                    AlgorithmLink_IssAewbCreateParams *pAewbPrms =
                        (AlgorithmLink_IssAewbCreateParams *)cmdArgs;

                    if (NULL != pSensorTable->sensorPrms.initAewbConfig)
                    {
                        pSensorTable->sensorPrms.initAewbConfig(
                            &pSensorTable->createPrms, pAewbPrms);
                        status = SYSTEM_LINK_STATUS_SOK;
                    }
                }

                break;
            case ISS_SENSORS_IOCTL_GET_ISP_CONFIG:
                status = SYSTEM_LINK_STATUS_EFAIL;
                if (NULL != cmdArgs)
                {
                    IssIspConfigurationParameters *pIspCfg =
                        (IssIspConfigurationParameters *)cmdArgs;

                    if (NULL != pSensorTable->sensorPrms.getIspConfig)
                    {
                        pSensorTable->sensorPrms.getIspConfig(
                            &pSensorTable->createPrms, pIspCfg);
                        status = SYSTEM_LINK_STATUS_SOK;
                    }
                }

                break;

            case ISS_SENSORS_IOCTL_READ_REG:
                status = SYSTEM_LINK_STATUS_EFAIL;
                if (NULL != cmdArgs)
                {
                    IssSensor_ReadWriteReg *pReg =
                        (IssSensor_ReadWriteReg *)cmdArgs;

                    if ((NULL != pSensorTable->sensorPrms.readWriteReg) &&
                        (pReg->chId < pSensorTable->createPrms.numChan))
                    {
                        status = pSensorTable->sensorPrms.readWriteReg(
                            &pSensorTable->createPrms, 0, pReg);
                    }
                }

                break;
            case ISS_SENSORS_IOCTL_WRITE_REG:
                status = SYSTEM_LINK_STATUS_EFAIL;
                if (NULL != cmdArgs)
                {
                    IssSensor_ReadWriteReg *pReg =
                        (IssSensor_ReadWriteReg *)cmdArgs;

                    if ((NULL != pSensorTable->sensorPrms.readWriteReg) &&
                        (pReg->chId < pSensorTable->createPrms.numChan))
                    {
                        status = pSensorTable->sensorPrms.readWriteReg(
                            &pSensorTable->createPrms, 1, pReg);
                    }
                }

                break;
            default:
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
        }
    }

    return (status);
}

/*******************************************************************************
 *  Local Functions Definition
 *******************************************************************************
 */

static Int32 checkForHandle(Ptr handle)
{
    Int32 found = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt;

    /* Find a free entry in the sensor table */
    for (cnt = 0U; cnt < ISS_SENSORS_MAX_SUPPORTED_SENSOR; cnt ++)
    {
        if (handle == (Ptr)&gIssSensorTable[cnt])
        {
            found = SYSTEM_LINK_STATUS_SOK;
            break;
        }
    }

    return (found);
}

