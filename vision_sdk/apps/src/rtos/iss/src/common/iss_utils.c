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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
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
#include <iss_dcc_nw_handler.h>
#include <iss_sensors.h>
#include <iss_utils.h>
#include <algorithmLink_issAewb.h>
#include <src/rtos/utils_common/include/utils_qspi.h>
#include "iss_vtnf_defaults.h"


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define ISS_UTILS_MESH_TABLE_PITCH(w, r) ((((((w)/(r))+1) + 15U) & ~15U) * (4U))

/*******************************************************************************
 *  Data Structures
 *******************************************************************************
 */
typedef struct
{
    char sensorName[ISS_SENSORS_MAX_NAME];
    IssSensor_Info sensorInfo;
    ChainsCommon_IssSensorIf sensorIf;
} IssUtils_Obj;


/*******************************************************************************
 *  Globals
 *******************************************************************************
 */

static vpsissvtnfConfig_t gVtnfDefBypassed = ISS_VTNF_DEFAULT_BYPASS;
static vpsissvtnfConfig_t gVtnfDefEnabled = ISS_VTNF_DEFAULT_ENABLED;
static IssUtils_Obj gIssUtilsObj;

#ifdef ISS_INCLUDE /* LDC table included only if ISS is included */
#pragma DATA_ALIGN(gChainsCommonIssLdcTable_1920x1080, 32)
UInt8 gChainsCommonIssLdcTable_1920x1080[] =
{
    #include "iss_tables/iss_tables_ldc_lut_1920x1080.h"
};
#else
UInt8 gChainsCommonIssLdcTable_1920x1080[1];
#endif


/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
static getSensorInfo(char name[], IssSensor_Info *pSensorInfo,
    ChainsCommon_IssSensorIf *pSensorIf);
static Void issCmdHandler(UInt32 cmd, Void *pPrm);
static System_VideoFrameStatus chainsCommonCsi2ErrorCb(Void *appObj,
                                System_Buffer *pBuffer,
                                System_VideoFrameStatus error);
static Void IssUtils_SetCaptureCreateParams(const IssSensor_Info *pSensorInfo,
    const ChainsCommon_IssSensorIf *pSensorIf,
    IssCaptureLink_CreateParams *pCapturePrm,
    IssM2mIspLink_OperatingMode ispOpMode);
static Void IssUtils_SetIspCreateParams(const IssSensor_Info *pSensorInfo,
     IssM2mIspLink_CreateParams *pPrm,
     IssM2mIspLink_OperatingMode ispOpMode);
static Void IssUtils_SetSimcopCreateParams(IssM2mSimcopLink_CreateParams *pPrm,
     IssM2mSimcopLink_OperatingMode opMode);



/*******************************************************************************
 *  Function Definition
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief   ChainsCommon_Iss_Init
 *
 *          This function registers command handler in system
 *          link for iss comands.
 *
 * \param   NULL
 *
  *******************************************************************************
 */
Void Iss_DccCmdHandler_Init()
{
    SystemLink_registerHandler(issCmdHandler);
}

/**
 *******************************************************************************
 *
 * \brief   ChainsCommon_Iss_DeInit
 *
 *          This function deregisters command handler in system
 *          link for iss comands.
 *
 * \param   NULL
 *
 *******************************************************************************
 */
Void Iss_DccCmdHandler_DeInit()
{
    SystemLink_unregisterHandler(issCmdHandler);
}

Void IssUtils_CopySensorName(char name[])
{
	if (NULL != name)
	{
		strncpy(gIssUtilsObj.sensorName, name, ISS_SENSORS_MAX_NAME);
	}
}

Void IssUtils_SetCreateParams(char name[],
        IssCaptureLink_CreateParams *pCapturePrm,
        IssM2mIspLink_CreateParams *pIspPrm,
        IssM2mSimcopLink_CreateParams *pSimcopPrm,
        IssM2mIspLink_OperatingMode ispOpMode,
        IssM2mSimcopLink_OperatingMode simcopOpMode)
{
    strncpy(gIssUtilsObj.sensorName, name, ISS_SENSORS_MAX_NAME);

    getSensorInfo(name, &gIssUtilsObj.sensorInfo, &gIssUtilsObj.sensorIf);

    if (NULL != pCapturePrm)
    {
        IssUtils_SetCaptureCreateParams(&gIssUtilsObj.sensorInfo,
            &gIssUtilsObj.sensorIf, pCapturePrm, ispOpMode);
    }
    if (NULL != pIspPrm)
    {
        IssUtils_SetIspCreateParams(&gIssUtilsObj.sensorInfo, pIspPrm,
            ispOpMode);
    }
    if (NULL != pSimcopPrm)
    {
        IssUtils_SetSimcopCreateParams(pSimcopPrm, simcopOpMode);
    }
}

Void IssUtils_InitSimcopConfig(
        IssM2mSimcopLink_ConfigParams *pSimcopCfg,
        Bool bypassLdc,
        Bool bypassVtnf)
{
    vpsissldcConfig_t  *ldcCfg;
    vpsissvtnfConfig_t *vtnfCfg;

    UTILS_assert(NULL != pSimcopCfg);

    ldcCfg = pSimcopCfg->ldcConfig;
    vtnfCfg = pSimcopCfg->vtnfConfig;

    if (NULL != ldcCfg)
    {
        vpsissLdcCfg_init(pSimcopCfg->ldcConfig);

        ldcCfg->enableBackMapping         = FALSE;
        ldcCfg->isAdvCfgValid             = TRUE;
        ldcCfg->pixelPad                  = 2;
        ldcCfg->advCfg.outputBlockWidth   = 32;
        ldcCfg->advCfg.outputBlockHeight  = 20;
        ldcCfg->advCfg.outputStartX       = 0;
        ldcCfg->advCfg.outputStartY       = 0;
        ldcCfg->advCfg.enableCircAddrMode = FALSE;
        ldcCfg->advCfg.circBuffSize       = 0;
        ldcCfg->advCfg.enableConstOutAddr = TRUE;

        /* Using LDC Lut table of 1920x1080 size with 4x down scaling factor
           Using LDC table from the offset ((1920x1080) - (1280x720))/2 */
        ldcCfg->lutCfg.address = (UInt32)&gChainsCommonIssLdcTable_1920x1080
        [
            (ISS_UTILS_MESH_TABLE_PITCH(1920,
                (1 <<VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_4)) * 15) + 320
        ];
        ldcCfg->lutCfg.downScaleFactor = VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_4;
        ldcCfg->lutCfg.lineOffset = ISS_UTILS_MESH_TABLE_PITCH(1920,
            (1U << ldcCfg->lutCfg.downScaleFactor));
    }
    if (NULL != vtnfCfg)
    {
        vpsissVtnfCfg_init(vtnfCfg);
    }

    IssUtils_SetimcopLdcVtnfRtConfig(ldcCfg, vtnfCfg, bypassLdc, bypassVtnf);
}

Void IssUtils_InitConfig(
        IssIspConfigurationParameters *pIspCfg,
        IssM2mSimcopLink_ConfigParams *pSimcopCfg,
        Bool bypassLdc,
        Bool bypassVtnf)
{
    vpsissldcConfig_t  *ldcCfg;
    vpsissvtnfConfig_t *vtnfCfg;

    UTILS_assert(NULL != pIspCfg);
    UTILS_assert(NULL != pSimcopCfg);

    ldcCfg = pSimcopCfg->ldcConfig;
    vtnfCfg = pSimcopCfg->vtnfConfig;

    if (NULL != ldcCfg)
    {
        vpsissLdcCfg_init(pSimcopCfg->ldcConfig);

        ldcCfg->enableBackMapping         = FALSE;
        ldcCfg->isAdvCfgValid             = TRUE;
        ldcCfg->pixelPad                  = 2;
        ldcCfg->advCfg.outputBlockWidth   = 32;
        ldcCfg->advCfg.outputBlockHeight  = 20;
        ldcCfg->advCfg.outputStartX       = 0;
        ldcCfg->advCfg.outputStartY       = 0;
        ldcCfg->advCfg.enableCircAddrMode = FALSE;
        ldcCfg->advCfg.circBuffSize       = 0;
        ldcCfg->advCfg.enableConstOutAddr = TRUE;

        /* Using LDC Lut table of 1920x1080 size with 4x down scaling factor
           Using LDC table from the offset ((1920x1080) - (1280x720))/2 */
        ldcCfg->lutCfg.address = (UInt32)&gChainsCommonIssLdcTable_1920x1080
        [
            (ISS_UTILS_MESH_TABLE_PITCH(1920,
                (1 <<VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_4)) * 15) + 320
        ];
        ldcCfg->lutCfg.downScaleFactor = VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_4;
        ldcCfg->lutCfg.lineOffset = ISS_UTILS_MESH_TABLE_PITCH(1920,
            (1U << ldcCfg->lutCfg.downScaleFactor));
    }
    if (NULL != vtnfCfg)
    {
        vpsissVtnfCfg_init(vtnfCfg);
    }

    IssUtils_SetimcopLdcVtnfRtConfig(ldcCfg, vtnfCfg, bypassLdc, bypassVtnf);
}

/**
 *******************************************************************************
 *
 * \brief   Function to get default ISP and Simcop Configuration,
 *          It uses DCC Profile either from driver or from qspi,
 *          parses it using AEWB plugin layer (uses linkid) and sets the
 *          default ISP/Simcop configuration
 *
 * \param   ispOpMode         ISP Operation Mode,
 *                            For monochrom mode, DCC profile is not used,
 *                            This is just used for informing whether it
 *                            is monochrome mode or not.
 * \param   pIspCfg        Pointer to ISP config, where default
 *                            values will be stored.
 * \param   pSimcopCfg        Pointer to Simcop config, where default
 *                            values will be stored.
 * \param   linkId            AEWB Link id, used for parsing DCC profile
 *
 *******************************************************************************
 */
Void IssUtils_ReadAndParseDccConfig(
        UInt32 qSpiOffset,
        UInt8 *pSensorDccCfg,
        UInt32 sensorDccCfgSize,
        UInt32 linkId)
{
    Int32                                    status;
    UInt32                                  *header = NULL;
    AlgorithmLink_IssAewbDccControlParams    dccCtrlPrms;

    UTILS_assert(0 != qSpiOffset);
    UTILS_assert(0 != sensorDccCfgSize);
    UTILS_assert(NULL != pSensorDccCfg);

    /* DCC is supported only if this flag is set in the driver,
       even dcc profile from qspi is supported only if this flag is set.
       Otherwise DCC parameters will not be used at all and configuration
       from the video sensor laye will be used */
    {
        /* Steps:
            1, Get the Default DCC Profile the sensor
            2, Get the DCC Profile Memory from the AEWB algorithms
            3, Read DCC file from Qspi if available
            4, If not available, copy dcc profile from sensor
            5, Parse the DCC and set the output */

        /* 2, Get the DCC Profile Memory from the AEWB algorithms */
        memset(&dccCtrlPrms, 0x0, sizeof(dccCtrlPrms));

        /* Get the DCC Buffer */
        dccCtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_AEWB_LINK_CMD_GET_DCC_BUF_PARAMS;
        dccCtrlPrms.baseClassControl.size = sizeof(dccCtrlPrms);

        dccCtrlPrms.dccBuf = NULL;

        status = System_linkControl(
            linkId,
            ALGORITHM_LINK_CMD_CONFIG,
            &dccCtrlPrms,
            sizeof(dccCtrlPrms),
            TRUE);
        UTILS_assert(0 == status);

        /* 3, Read DCC file from Qspi if available */

        if (NULL != dccCtrlPrms.dccBuf)
        {
            /* Check if the binary file in QSPI is valid, then use it instead
               of binary file form the driver */
             if(!System_isFastBootEnabled())
             {
                 /* Read the Header first */
                 System_qspiReadSector((UInt32)dccCtrlPrms.dccBuf,
                                       qSpiOffset,
                                       SystemUtils_align(
                                       CHAINS_COMMON_ISS_DCC_BIN_HEADER_SIZE,
                                       SYSTEM_QSPI_READ_WRITE_SIZE));
             }

            header = (UInt32 *)dccCtrlPrms.dccBuf;
            if(System_isFastBootEnabled())
            {
                 *header = 0x00000000;
            }
            if (CHAINS_COMMON_ISS_DCC_BIN_FILE_TAG_ID == *header)
            {
                /* Read bin file size */
                header ++;
                dccCtrlPrms.dccBufSize = *header;

                /* Read the binary file */
                System_qspiReadSector(
                    (UInt32)dccCtrlPrms.dccBuf,
                    qSpiOffset + CHAINS_COMMON_ISS_DCC_BIN_HEADER_SIZE,
                    SystemUtils_align(dccCtrlPrms.dccBufSize,
                                      SYSTEM_QSPI_READ_WRITE_SIZE));
                Vps_printf(" CHAINS: Using DCC Profile from QSPI \n");
            }
            else /* 4, If not available, copy dcc profile from sensor */
            {
                memcpy(dccCtrlPrms.dccBuf, pSensorDccCfg, sensorDccCfgSize);
                dccCtrlPrms.dccBufSize = sensorDccCfgSize;

                Vps_printf(" CHAINS: DCC Tag ID check failed for QSPI \n");
                Vps_printf(" CHAINS: Using DCC Profile from Driver \n");
            }

            {
                /* 5, Parse the DCC and set the output */
                dccCtrlPrms.baseClassControl.controlCmd =
                    ALGORITHM_AEWB_LINK_CMD_PARSE_AND_SET_DCC_PARAMS;
                dccCtrlPrms.baseClassControl.size = sizeof(dccCtrlPrms);

                status = System_linkControl(
                    linkId,
                    ALGORITHM_LINK_CMD_CONFIG,
                    &dccCtrlPrms,
                    sizeof(dccCtrlPrms),
                    TRUE);
                UTILS_assert(0 == status);
            }
        }
        else
        {
            Vps_printf(" CHAINS: DCC buffer is NULL \n");
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to enable/disable VTNF/LDC at run time,
 *          It copies default VTNF parameters based on the flag and also
 *          enables/disables back mapping based on the flag
 *
 * \param   ldcCfg          Pointer to LDC configuration
 * \param   vtnfCfg         Pointer to VTNF configuration
 * \param   bypassVtnf      Flag to indicate whether enable/bypass VTNF
 * \param   bypassLdc       Flag to indicate whether enable/bypass LDC
 *
 *******************************************************************************
 */
Void IssUtils_SetimcopLdcVtnfRtConfig(
                        vpsissldcConfig_t *ldcCfg,
                        vpsissvtnfConfig_t *vtnfCfg,
                        Bool bypssLdc,
                        Bool bypssVtnf)
{
    /* LDC and VTNF Config pointers must not be null */
    UTILS_assert(NULL != ldcCfg);
    UTILS_assert(NULL != vtnfCfg);

    if(bypssLdc)
    {
        ldcCfg->enableBackMapping = FALSE;
    }
    else
    {
        ldcCfg->enableBackMapping = TRUE;
    }

    if (bypssVtnf)
    {
        memcpy(vtnfCfg, &gVtnfDefBypassed, sizeof(vpsissvtnfConfig_t));
    }
    else
    {
        memcpy(vtnfCfg, &gVtnfDefEnabled, sizeof(vpsissvtnfConfig_t));
    }
}

/*  \brief Function to enables detection of CRC error on CSI2 interface
 *
 *  params captSrc      Source from which CAL is used to capture.
 *  params issCaptureLinkId  Capture Link identifier. Required to configure
 *                          the link to detect errors.
 *  returns none.
 */
Void ChainsCommon_SetIssCaptureErrorHandlingCb(UInt32 issCaptureLinkId)
{
    IssCaptureLink_SetErrorNotification calCsi2ErrCfg;

    calCsi2ErrCfg.errorCallback = &chainsCommonCsi2ErrorCb;
    calCsi2ErrCfg.errorsToDetect =
        ISSCAPTURE_LINK_ENABLE_ERROR_CRC_MISMATCH;
    calCsi2ErrCfg.appObj = NULL;

    System_linkControl(issCaptureLinkId,
                        ISSCAPTURE_LINK_CMD_SET_ERROR_NOTIFICATION,
                        &calCsi2ErrCfg,
                        0,
                        TRUE);
    return;
}

/*******************************************************************************
 *  Local Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief   callback to handle user defined commands reaching system link
 *
 *  \param  cmd [IN] Command that needs to be handled
 *               pPrm [IN/OUT] Parameters for this command
 *
 *******************************************************************************
 */
static Void issCmdHandler(UInt32 cmd, Void *pPrm)
{
    Int32 status;
    UInt32 dccCameraId;
    AlgorithmLink_IssAewbDccControlParams *dccCtrlPrms;
    IssSensor_Info info;
    IssSensor_ReadWriteReg reg;

    if (NULL != pPrm)
    {
        if (SYSTEM_LINK_CMD_SAVE_DCC_FILE == cmd)
        {
            dccCtrlPrms = (AlgorithmLink_IssAewbDccControlParams *)pPrm;

            /* Get the Sensor DCC Id from the header */
            dccCameraId = *(((UInt32 *)dccCtrlPrms->dccBuf) +
                CHAINS_COMMON_ISS_DCC_BIN_DCC_ID_OFFSET);

            /* Get the Sensor QSPI offset for the given sensors DCC ID */
            status = IssSensor_GetSensorInfoFromDccId(dccCameraId, &info);
            if (SYSTEM_LINK_STATUS_SOK == status)
            {
                /* Offset 0 cannot be used, so it is used as
                   error value here */
                if (0 != info.ramOffset)
                {
                    /* Write complete bin file */
                    System_qspiWriteSector(info.ramOffset,
                                           (UInt32)dccCtrlPrms->dccBuf,
                                           ALGORITHM_AEWB1_DCC_IN_BUF_SIZE);
                }
            }
        }
        if (SYSTEM_LINK_CMD_CLEAR_DCC_QSPI_MEM == cmd)
        {
            dccCameraId = *(UInt32 *)pPrm;

            /* Get the Sensor QSPI offset for the given sensors DCC ID */
            /* Get the Sensor QSPI offset for the given sensors DCC ID */
            status = IssSensor_GetSensorInfoFromDccId(dccCameraId, &info);
            if (SYSTEM_LINK_STATUS_SOK == status)
            {
                if (0 != info.ramOffset)
                {
                    /* Write complete bin file */
                    System_qspiEraseSector(info.ramOffset,
                                           ALGORITHM_AEWB1_DCC_IN_BUF_SIZE);
                }
            }
        }

        if ((SYSTEM_LINK_CMD_WRITE_SENSOR_REG == cmd) ||
            (SYSTEM_LINK_CMD_READ_SENSOR_REG == cmd))
        {
            UInt32 *prms = (UInt32 *)pPrm;
            Ptr sensorHandle;

            sensorHandle = IssSensor_GetSensorHandle(gIssUtilsObj.sensorName);
            if (NULL != sensorHandle)
            {
                reg.chId = *prms;
                prms ++;
                reg.regAddr = *prms;
                prms ++;

                if (SYSTEM_LINK_CMD_WRITE_SENSOR_REG == cmd)
                {
                    reg.regValue = *prms;
                    status = IssSensor_Control(sensorHandle,
                        ISS_SENSORS_IOCTL_WRITE_REG, &reg, NULL);
                }
                else
                {
                    status = IssSensor_Control(sensorHandle,
                        ISS_SENSORS_IOCTL_READ_REG, &reg, NULL);
                    if (SYSTEM_LINK_STATUS_SOK == status)
                    {
                        *prms = reg.regValue;
                    }
                }

                UTILS_assert (status == 0);
            }
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Callback attached to the link. Will be called if an configured error
 *          is detected. If an frame has CRC error, the link would be instructed
 *          not to process that particular frame.
 *
 *  \param  cmd [IN] Command that needs to be handled
 *               pPrm [IN/OUT] Parameters for this command
 *
 *******************************************************************************
 */
static System_VideoFrameStatus chainsCommonCsi2ErrorCb(Void *appObj,
                                System_Buffer *pBuffer,
                                System_VideoFrameStatus error)
{
    System_VideoFrameStatus status = SYSTEM_FRAME_STATUS_COMPLETED;

    if (SYSTEM_FRAME_STATUS_CRC_ERROR == error)
    {
        /* Causes the capture link to not process this (pBuffer) frame */
        /* Change the status to SYSTEM_FRAME_STATUS_COMPLETED if you require to
            ignore the detected CRC errors */
        status = SYSTEM_FRAME_STATUS_ABORTED;
    }

    return status;
}


/**
 *******************************************************************************
 *
 * \brief   Function to initialize Capture Link Create Params from
 *          given sensor information
 *
 * \param   pSensorInfo     Pointer to sensor information, containing
 *                          sensor output frame size and format
 * \param   pSensorIf       Pointer to sensor interface information
 * \param   pCaptureParams  Capture Parameter to be initialized
 *
 *******************************************************************************
 */
static Void IssUtils_SetCaptureCreateParams(const IssSensor_Info *pSensorInfo,
    const ChainsCommon_IssSensorIf *pSensorIf,
    IssCaptureLink_CreateParams *pCapturePrm,
    IssM2mIspLink_OperatingMode ispOpMode)
{
    UInt32 i = 0;

    UTILS_assert(NULL != pSensorInfo);
    UTILS_assert(NULL != pSensorIf);
    UTILS_assert(NULL != pCapturePrm);

    /* Initialize capture parameters from sensor information */
    pCapturePrm->outParams[0U].dataFormat =
        (System_VideoDataFormat)pSensorInfo->dataFormat;
    pCapturePrm->outParams[0U].width = pSensorInfo->width;
    pCapturePrm->outParams[0U].height = pSensorInfo->height;

    if (ispOpMode == ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED)
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
        (System_VideoIfMode)pSensorIf->videoIfMode;
    pCapturePrm->videoIfWidth =
        (System_VideoIfWidth)pSensorIf->videoIfWidth;

    pCapturePrm->outParams[0U].inCsi2DataFormat = pSensorIf->inCsi2DataFormat;
    pCapturePrm->outParams[0U].inCsi2VirtualChanNum =
        pSensorIf->inCsi2VirtualChanNum;

    for(i = 0 ; i < ISSCAPT_LINK_MAX_CMPLXIO_INST; i++)
    {
        pCapturePrm->csi2Params[i] = pSensorIf->csi2Prms[i];
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to initialize ISP Link Create Params
 *
 * \param   pCapturePrm     Pointer to ISP link create params
 * \param   outWidthRszA    Resizer A Output Width
 * \param   outHeightRszA   Resizer A Output Height
 * \param   outWidthRszB    Resizer B Output Width
 * \param   outHeightRszB   Resizer B Output Height
 * \param   ispOpMode       ISP Operation Mode
 * \param   wdrOffsetPrms   WDR Offset params used for Line interleaved wdr mode
 *
 *******************************************************************************
 */
static Void IssUtils_SetIspCreateParams(const IssSensor_Info *pSensorInfo,
     IssM2mIspLink_CreateParams *pPrm,
     IssM2mIspLink_OperatingMode ispOpMode)
{
    UInt32 chId;

    for(chId = 0; chId < ISSM2MISP_LINK_MAX_CH; chId++)
    {
        pPrm->channelParams[chId].operatingMode   = ispOpMode;
        pPrm->channelParams[chId].inBpp           = pSensorInfo->bpp;

        pPrm->channelParams[chId].numBuffersPerCh = 2;

        pPrm->channelParams[chId].outParams.widthRszA  = pSensorInfo->width;
        pPrm->channelParams[chId].outParams.heightRszA = pSensorInfo->height;
        pPrm->channelParams[chId].outParams.widthRszB  = pSensorInfo->width;
        pPrm->channelParams[chId].outParams.heightRszB = pSensorInfo->height;
        pPrm->channelParams[chId].outParams.winWidthH3a = 16;
        pPrm->channelParams[chId].outParams.winHeightH3a = 16;
        pPrm->channelParams[chId].outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;

        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A]  = 1;
        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B]  = 0;
        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_H3A]  = 1;
        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_H3A_AF]  = 0;

        {
            pPrm->channelParams[chId].enableOut[
                ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B]  = 1;
        }

        if (ispOpMode == ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED)
        {
            pPrm->channelParams[chId].outParams.widthRszA  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].width;
            pPrm->channelParams[chId].outParams.heightRszA =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].height;

            pPrm->channelParams[chId].wdrOffsetPrms.longLineOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].starty;
            pPrm->channelParams[chId].wdrOffsetPrms.longPixelOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].startx;
            pPrm->channelParams[chId].wdrOffsetPrms.shortLineOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_SHORT].starty;
            pPrm->channelParams[chId].wdrOffsetPrms.shortPixelOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_SHORT].startx;
            pPrm->channelParams[chId].wdrOffsetPrms.width  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].width;
            pPrm->channelParams[chId].wdrOffsetPrms.height  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].height;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to initialize Simcop Link Create Params
 *
 * \param   pPrm            Pointer to Simcop link create params
 * \param   opMode          Simcop Operation mode
 *
 *******************************************************************************
 */
static Void IssUtils_SetSimcopCreateParams(IssM2mSimcopLink_CreateParams *pPrm,
     IssM2mSimcopLink_OperatingMode opMode)
{
    int chId;

    if(System_isFastBootEnabled())
    {
        pPrm->allocBufferForDump = 0;
    }

    for(chId=0; chId<ISSM2MSIMCOP_LINK_MAX_CH; chId++)
    {
        pPrm->channelParams[chId].operatingMode
            = opMode;

        pPrm->channelParams[chId].numBuffersPerCh
            = ISSM2MSIMCOP_LINK_NUM_BUFS_PER_CH_DEFAULT;
    }
}

static getSensorInfo(char name[], IssSensor_Info *pSensorInfo,
    ChainsCommon_IssSensorIf *pSensorIf)
{
    Int32 status;

    status = IssSensor_GetSensorInfo(name, pSensorInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    status = ChainsPlatform_GetSensorIntfInfo(name, pSensorIf);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}
