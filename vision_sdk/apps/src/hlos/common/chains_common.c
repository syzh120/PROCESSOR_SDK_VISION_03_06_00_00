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
 * \file chains_common.c
 *
 * \brief  Board specific initializations through APP_CTRL link.
 *
 *         All peripherals thats are controlled from IPU like video sensors, d
 *         displays etc are controlled from A15 through APP_CTRL link commands
 *
 * \version 0.0 (Jun 2014) : [YM] First version implemented.
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/hlos/common/chains_common.h>

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#if !defined (QNX_BUILD)
#include <stropts.h>
#include <linux/i2c-dev.h>
#endif

#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)
#define MAX_INPUT_STR_SIZE        (80)

#define AVB_TALKER_MAX_FRAME_SIZE (1000000)

/* AVBTP Subtype for compressed video format */
#define AVB_TX_LINK_SUBTYPE_CVF             (0x3)

/* CV format subtype */
/* CVF - format subtypes */
#define AVB_TX_LINK_CVF_SUBTYPE_MJPEG       (0x0)
#define AVB_TX_LINK_CVF_SUBTYPE_H264        (0x1)
#define AVB_TX_LINK_CVF_SUBTYPE_JPEG2000    (0x2)

/**
 *******************************************************************************
 *
 *  \brief  Common information related to all use-case
 *
 *******************************************************************************
*/
typedef struct {

    UInt32  displayCtrlLinkId;

    DisplayCtrlLink_ConfigParams    dctrlCfgPrms;
    DisplayCtrlLink_OvlyPipeParams  pipeParams[4];
    DisplayCtrlLink_OvlyParams      ovlyParams;
#if defined (BOARD_TYPE_TDA2XX_RVP)
    AppCtrl_BoardIds boardIds;
#endif
} Chains_CommonObj;

Chains_CommonObj gChains_commonObj;

static Int32 int_power(Int32 base, Int32 exp)
{
    Int32 result = 1;
    while (exp)
    {
        if (exp & 1)
        {
            result *= base;
        }
        exp /= 2;
        base *= base;
    }
    return result;
}

#if defined (BOARD_TYPE_TDA2XX_RVP)
static uint16_t Chains_getBoardIdRvp(UInt8 address) {
    int file;
    int adapterNum = 0;
    char filename[20];
    int err;

    UInt8 id = KID_FAIL;
    UInt8 regs[1];
    UInt8 vals[1] = {0};

    regs[0] = (address == KTCA9539_I2CADDR_SOM ? 0x00 : 0x01);

    Vps_printf("Connecting to I2C %X.%X!!!", adapterNum, address);

    snprintf(filename, 19, "/dev/i2c-%d", adapterNum);
    file = open(filename, O_RDWR);
    if(file < 0) {
        err = errno;
        Vps_printf("File failed to open with errno %d!!!", err);
        return KID_FAIL;
    }

    if(ioctl(file, I2C_SLAVE_FORCE, address) < 0) {
        err = errno;
        Vps_printf("Failed to set slave address with errno %d!!!", err);
    } else {
        if(write(file, regs, 1) != 1) {
            err = errno;
            Vps_printf("Failed to write to device with errno %d!!!", err);
        } else {
            if(read(file, vals, 1) != 1) {
                err = errno;
                Vps_printf("Failed to read from device with errno %d!!!", err);
            } else {
                id = vals[0];
            }
        }
    }

    close(file);
    return id;
}
#endif

/**
 *******************************************************************************
 *
 * \brief   Read a charater from UART or CCS console
 *
 * \return character that is read
 *
 *******************************************************************************
*/
char Chains_readChar()
{
    Int8 ch[80];

    fflush(stdin);
    fgets((char*)ch, MAX_INPUT_STR_SIZE, stdin);
    if(ch[1] != '\n' || ch[0] == '\n')
    ch[0] = '\n';

    return ch[0];
}

/**
 *******************************************************************************
 *
 * \brief   Read an integer from UART or CCS console
 *
 * \return character that is read
 *
 *******************************************************************************
*/
Int32 Chains_readInt()
{
    Int8 ch[80];
    Int32 retVal = 0;
    UInt16 digits = 0, i;

    fflush(stdin);
    fgets((char*)ch, MAX_INPUT_STR_SIZE, stdin);

    /* Checking escape value ? */
    if ((69 == ch[0]) || (101 == ch[0]))
    {
        retVal = -1;
    }

    for (i = 0; i < 80; i++)
    {
        if (10 == ch[i])
        {
            digits = i;
            break;
        }
    }

    if (45 == ch[0])
    {
        for (i = 1; i < digits; i++)
        {
            /* Check to see if value is a number */
            if ((ch[i] > 57) || (ch[i] < 48))
            {
                retVal = 0;
                break;
            }
            else
            {
                retVal = retVal + (ch[i]-48)*int_power(10, digits-i-1);
            }
        }
        retVal = -1*retVal;
    }
    else
    {
        for (i = 0; i < digits; i++)
        {
            if ((ch[i] > 57) || (ch[i] < 48))
            {
                retVal = 0;
                break;
            }
            else
            {
                retVal = retVal + (ch[i]-48)*int_power(10, digits-i-1);
            }
        }
    }

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief   Initializes / starts peripherals remotely with APP_CTRL commands
 *
 *
 *******************************************************************************
 */
Int32 ChainsCommon_appCtrlCommonInit()
{

    Int32 status = SYSTEM_LINK_STATUS_SOK;

    status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                APP_CTRL_LINK_CMD_SET_DMM_PRIORITIES,
                                NULL,
                                0,
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

#ifndef EARLY_USECASE_ENABLE 
    /* In-case of the early use-cases the statistics thread is already
     initialized */
    status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                APP_CTRL_LINK_CMD_STAT_COLLECTOR_INIT,
                                NULL,
                                0,
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
#endif

#if defined (BOARD_TYPE_TDA2XX_RVP)
    Vps_printf("  Reading Board IDs!!!");

    gChains_commonObj.boardIds.boardIdSOM = Chains_getBoardIdRvp(KTCA9539_I2CADDR_SOM);
    gChains_commonObj.boardIds.boardIdBaseboard = Chains_getBoardIdRvp(KTCA9539_I2CADDR_BASEBOARD);

    Vps_printf("        Board Detect SOM: %X", gChains_commonObj.boardIds.boardIdSOM);
    Vps_printf("  Board Detect Baseboard: %X", gChains_commonObj.boardIds.boardIdBaseboard);

    status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                APP_CTRL_LINK_CMD_SET_BOARD_IDS,
                                &gChains_commonObj.boardIds,
                                sizeof(gChains_commonObj.boardIds),
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   DeInitializes and stops peripheral remotely with APP_CTRL commands
 *
 *
 *******************************************************************************
 */
Int32 ChainsCommon_appCtrlCommonDeInit()
{

    Int32 status = SYSTEM_LINK_STATUS_SOK;

    status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                APP_CTRL_LINK_CMD_STAT_COLLECTOR_DEINIT,
                                NULL,
                                0,
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}
/**
 *******************************************************************************
 *
 * \brief   Set Capture Create Parameters for single camera capture mode
 *
 * \param   pPrm         [IN]  CaptureLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SingleCam_SetCapturePrms(
                        CaptureLink_CreateParams *pPrm,
                        UInt32 captureInWidth,
                        UInt32 captureInHeight,
                        UInt32 captureOutWidth,
                        UInt32 captureOutHeight,
                        Chains_CaptureSrc captureSrc
                        )
{
    UInt32 i, streamId;

    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InParams *pInprms;
    CaptureLink_OutParams *pOutprms;
    CaptureLink_VipScParams *pScPrms;
    CaptureLink_VipPortConfig    *pPortCfg;

    memset(pPrm, 0, sizeof(*pPrm));
    /* For SCV usecase number of camera is always 1 */
    pPrm->numVipInst = 1;
    pPrm->numDssWbInst = 0;

    for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
    {
        pInstPrm = &pPrm->vipInst[i];
        pInprms = &pInstPrm->inParams;
#ifdef BUILD_INFOADAS
#ifdef QNX_BUILD
        pInstPrm->vipInstId     =   i;
#else
        pInstPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
#endif
#else
        pInstPrm->vipInstId     =   i;
#endif
#ifdef TDA2EX_BUILD
        //This change is done for supporting tda2ex
        pInstPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
#endif

#ifdef BOARD_TYPE_TDA2XX_RVP
        pInstPrm->vipInstId = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
#endif

        if(captureSrc == CHAINS_CAPTURE_SRC_OV10635)
        {


            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_8BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

        }
        else if(captureSrc == CHAINS_CAPTURE_SRC_IMX290ISP)
        {


            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_8BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

        }
        else if (captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P)
        {


            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_AVID_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   1280;
            pInprms->height     =    720;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

        }
        else if (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P)
        {


            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_AVID_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   1920;
            pInprms->height     =   1080;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;
        }
        else if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
        {
            pInstPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight;
            pInprms->dataFormat =   SYSTEM_DF_YUV422I_YUYV;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;
        }
        else
        {
            /* Nothing here. To avoid MISRA C warnings */
        }

        for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                streamId++)
        {
            pOutprms = &pInstPrm->outParams[streamId];
            pOutprms->width         =   captureOutWidth;
            pOutprms->height        =   captureOutHeight;
            pOutprms->dataFormat    =   SYSTEM_DF_YUV420SP_UV;
            pOutprms->maxWidth      =   pOutprms->width;
            pOutprms->maxHeight     =   pOutprms->height;
            if((pInprms->width != pOutprms->width) ||
                (pInprms->height != pOutprms->height))
            {
                pOutprms->scEnable      =   TRUE;
            }
            else
            {
                pOutprms->scEnable      =   FALSE;
            }
            pOutprms->subFrmPrms.subFrameEnable = FALSE;
            pOutprms->subFrmPrms.numLinesPerSubFrame = 0;

            if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
            {
                pOutprms->dataFormat    =   SYSTEM_DF_YUV422I_UYVY;
            }
        }
        pScPrms = &pInstPrm->scPrms;
        pScPrms->inCropCfg.cropStartX = 0;
        pScPrms->inCropCfg.cropStartY = 0;
        pScPrms->inCropCfg.cropWidth = pInprms->width;
        pScPrms->inCropCfg.cropHeight = pInprms->height;

        pScPrms->scCfg.bypass       = FALSE;
        pScPrms->scCfg.nonLinear    = FALSE;
        pScPrms->scCfg.stripSize    = 0;

        pScPrms->userCoeff = FALSE;

        /* pScPrms->scCoeffCfg is not reuquired in case
         * pScPrms->userCoeff is FALSE
         */
        pPortCfg = &pInstPrm->vipPortCfg;
        pPortCfg->syncType          =   SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
        pPortCfg->ancCropEnable     =   FALSE;



        pPortCfg->intfCfg.clipActive    =   FALSE;
        pPortCfg->intfCfg.clipBlank     =   FALSE;
        pPortCfg->intfCfg.intfWidth     =   SYSTEM_VIFW_16BIT;

        pPortCfg->disCfg.fidSkewPostCnt     =   0;
        pPortCfg->disCfg.fidSkewPreCnt      =   0;
        pPortCfg->disCfg.lineCaptureStyle   =
                                SYSTEM_VIP_LINE_CAPTURE_STYLE_ACTVID;
        pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_PIN;
        pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.discreteBasicMode  =   TRUE;

        pPortCfg->comCfg.ctrlChanSel        =   SYSTEM_VIP_CTRL_CHAN_SEL_7_0;
        pPortCfg->comCfg.ancChSel8b         =
                                SYSTEM_VIP_ANC_CH_SEL_8B_LUMA_SIDE;
        pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_RISING;
        pPortCfg->comCfg.invertFidPol       =   FALSE;
        pPortCfg->comCfg.enablePort         =   FALSE;
        pPortCfg->comCfg.expectedNumLines   =   pInprms->height;
        pPortCfg->comCfg.expectedNumPix     =   pInprms->width;
        pPortCfg->comCfg.repackerMode       =   SYSTEM_VIP_REPACK_CBA_TO_CBA;
        pPortCfg->actCropEnable             =   TRUE;

        if ((captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P) ||
            (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P))
        {
            pPortCfg->actCropEnable         =   FALSE;
        }

        pPortCfg->actCropCfg.srcNum                     =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->actCropCfg.cropCfg.cropWidth          =   pInprms->width;
        pPortCfg->actCropCfg.cropCfg.cropHeight         =   pInprms->height;

        pPortCfg->ancCropCfg.srcNum                     =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropWidth          =   0;
        pPortCfg->ancCropCfg.cropCfg.cropHeight         =   0;

        if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
        {
            pPortCfg->disCfg.lineCaptureStyle   =   SYSTEM_VIP_LINE_CAPTURE_STYLE_HSYNC;
            pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_VSYNC;
            pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_LOW;
            pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_LOW;
            pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
            pPortCfg->comCfg.ancChSel8b         =   SYSTEM_VIP_ANC_CH_SEL_DONT_CARE;
            pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_FALLING;
        }

        pInstPrm->numBufs = CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT + 2;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Capture Create Parameters
 *
 *          This function is used to set the capture params.
 *          It is called in Create function. It is advisable to have
 *          Chains_LvdsVipMultiCameraSgxDisplay_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Capture Link Input,Output, Vip parameters are set here.
 *
 * \param   pPrm      [OUT]  CaptureLink_CreateParams
 * \param   portId    [IN]   VIP ports which needs to be configured
 *
 *******************************************************************************
*/
Void ChainsCommon_MultiCam_SetCapturePrms(
                        CaptureLink_CreateParams *pPrm,
                        UInt32 numLvdsCh)
{
    UInt32 i, streamId;

    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InParams *pInprms;
    CaptureLink_OutParams *pOutprms;
    CaptureLink_VipScParams *pScPrm;
    CaptureLink_VipPortConfig    *pPortCfg;
    UInt32 portId[10];


    memset(pPrm, 0, sizeof(*pPrm));

    pPrm->numVipInst = numLvdsCh;
    pPrm->numDssWbInst = 0;

    portId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    portId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    portId[2] = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
    portId[3] = SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
    portId[4] = SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
    portId[5] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTB;

#ifdef BOARD_TYPE_TDA2XX_RVP
    portId[0] = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
    portId[1] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTA;
    portId[2] = SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
    portId[3] = SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
    portId[4] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    portId[5] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    portId[6] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
    portId[7] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTB;

#endif
#ifdef TDA2EX_BUILD
    portId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    portId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    portId[2] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTB;
    portId[3] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
#endif

#ifdef TDA2PX_BUILD
    portId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    portId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    portId[2] = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
    portId[3] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTB;
#endif

    for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
    {
        pInstPrm = &pPrm->vipInst[i];
        pInstPrm->vipInstId     =   portId[i];
        pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
        pInstPrm->videoIfWidth  =   SYSTEM_VIFW_8BIT;
        pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
        pInstPrm->numStream     =   1;

        pInprms = &pInstPrm->inParams;

        pInprms->width      =   CAPTURE_SENSOR_WIDTH;
        pInprms->height     =   CAPTURE_SENSOR_HEIGHT;
        pInprms->dataFormat =   SYSTEM_DF_YUV422P;
        pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

        for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                streamId++)
        {
            pOutprms = &pInstPrm->outParams[streamId];
            pOutprms->width         =   pInprms->width;
            pOutprms->height        =   pInprms->height;
            pOutprms->dataFormat    =   SYSTEM_DF_YUV420SP_UV;
            pOutprms->maxWidth      =   pOutprms->width;
            pOutprms->maxHeight     =   pOutprms->height;
            pOutprms->scEnable      =   FALSE;

            /* sub-frame not supported, set to FALSE */
            pOutprms->subFrmPrms.subFrameEnable = FALSE;
            pOutprms->subFrmPrms.numLinesPerSubFrame = 0;

        }
        pScPrm = &pInstPrm->scPrms;
        pScPrm->inCropCfg.cropStartX = 0;
        pScPrm->inCropCfg.cropStartY = 0;
        pScPrm->inCropCfg.cropWidth = pInprms->width;
        pScPrm->inCropCfg.cropHeight = pInprms->height;

        pScPrm->scCfg.bypass       = FALSE;
        pScPrm->scCfg.nonLinear    = FALSE;
        pScPrm->scCfg.stripSize    = 0;

        pScPrm->userCoeff = FALSE;

        /* pScPrm->scCoeffCfg is not reuquired in case
         * pScPrm->userCoeff is FALSE
         */
        pPortCfg = &pInstPrm->vipPortCfg;
        pPortCfg->syncType          =   SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
        pPortCfg->ancCropEnable     =   FALSE;

        pPortCfg->intfCfg.clipActive    =   FALSE;
        pPortCfg->intfCfg.clipBlank     =   FALSE;
        pPortCfg->intfCfg.intfWidth     =   SYSTEM_VIFW_16BIT;

        pPortCfg->disCfg.fidSkewPostCnt     =   0;
        pPortCfg->disCfg.fidSkewPreCnt      =   0;
        pPortCfg->disCfg.lineCaptureStyle   =
                                SYSTEM_VIP_LINE_CAPTURE_STYLE_ACTVID;
        pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_PIN;
        pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.discreteBasicMode  =   TRUE;

        pPortCfg->comCfg.ctrlChanSel        =   SYSTEM_VIP_CTRL_CHAN_SEL_7_0;
        pPortCfg->comCfg.ancChSel8b         =
                            SYSTEM_VIP_ANC_CH_SEL_8B_LUMA_SIDE;
        pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_RISING;
        pPortCfg->comCfg.invertFidPol       =   FALSE;
        pPortCfg->comCfg.enablePort         =   FALSE;
        pPortCfg->comCfg.expectedNumLines   =   pInprms->height;
        pPortCfg->comCfg.expectedNumPix     =   pInprms->width;
        pPortCfg->comCfg.repackerMode       =   SYSTEM_VIP_REPACK_CBA_TO_CBA;

        pPortCfg->actCropEnable                         =   TRUE;
        pPortCfg->actCropCfg.srcNum                     =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->actCropCfg.cropCfg.cropWidth          =   pInprms->width;
        pPortCfg->actCropCfg.cropCfg.cropHeight         =   pInprms->height;

        pPortCfg->ancCropCfg.srcNum                     =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropWidth          =   0;
        pPortCfg->ancCropCfg.cropCfg.cropHeight         =   0;

        pInstPrm->numBufs = CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT + 2;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Print Statistics
 *
 *******************************************************************************
*/
Void ChainsCommon_PrintStatistics()
{
#if !defined (QNX_BUILD)
    System_linkControl(
        SYSTEM_LINK_ID_IPU1_0,
        SYSTEM_LINK_CMD_PRINT_CORE_PRF_LOAD,
        NULL,
        0,
        TRUE);

    ChainsCommon_statCollectorPrint();
    System_printDisplayErrorStats();
#endif
}

/**
 *******************************************************************************
 *
 * \brief   Load Calculation enable/disable
 *
 *          This functions enables load profiling. A control command
 *          SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START is passed to chianed links.
 *          If parameter Enable is set true Load profiling is enabled.
 *          If printStatus is set true a System CMD to Print CPU load,
 *          Task Laod and Heap status information is sent
 *          While creating enable = TRUE , printStatus & printTskLoad = FALSE
 *          While deleting enable = FALSE , printStatus & printTskLoad = TRUE
 *
 * \param   enable               [IN]   is set true Load profiling
 *
 * \param   printStatus          [IN] true a System CMD
 *
 * \param   printTskLoad         [IN]  true a Print CPU load
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 ChainsCommon_prfLoadCalcEnable(Bool enable, Bool printStatus, Bool printTskLoad)
{
    UInt32 procId, linkId;


    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(    System_isProcEnabled(procId)==FALSE
            || procId == System_getSelfProcId()
           )
        {
            continue;
        }

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        if(enable)
        {
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START,
                NULL,
                0,
                TRUE
            );
        }
        else
        {
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_STOP,
                NULL,
                0,
                TRUE
            );
            if(printStatus)
            {
                SystemCommon_PrintStatus printStatus;

                memset(&printStatus, 0, sizeof(printStatus));

                printStatus.printCpuLoad = TRUE;
                printStatus.printTskLoad = printTskLoad;
                System_linkControl(
                    linkId,
                    SYSTEM_COMMON_CMD_PRINT_STATUS,
                    &printStatus,
                    sizeof(printStatus),
                    TRUE
                );
                OSA_waitMsecs(100);
            }
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_RESET,
                NULL,
                0,
                TRUE
            );
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Print Load Calculation.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 ChainsCommon_prfCpuLoadPrint()
{
    UInt32 procId, linkId;
    SystemCommon_PrintStatus printStatus;

    memset(&printStatus, 0, sizeof(printStatus));

    printStatus.printCpuLoad = TRUE;
    printStatus.printTskLoad = TRUE;

    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(    System_isProcEnabled(procId)==FALSE
            || procId == System_getSelfProcId()
           )
        {
            continue;
        }

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_PRINT_STATUS,
            &printStatus,
            sizeof(printStatus),
            TRUE
        );
        OSA_waitMsecs(100);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Print Memory Heap Statistics
 *
 *          This function send a system control message
 *          SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START to all cores.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 ChainsCommon_memPrintHeapStatus()
{
    UInt32 procId, linkId;
    SystemCommon_PrintStatus printStatus;

    memset(&printStatus, 0, sizeof(printStatus));

    printStatus.printHeapStatus = TRUE;

    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(    System_isProcEnabled(procId)==FALSE
            || procId == System_getSelfProcId()
           )
        {
            continue;
        }

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_PRINT_STATUS,
                &printStatus,
                sizeof(printStatus),
                TRUE
            );
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   This function Print the statCollector output
 *          SYSTEM_COMMON_CMD_PRINT_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 ChainsCommon_statCollectorPrint()
{
#if !defined (QNX_BUILD)
    UInt32 linkId;

    linkId = IPU1_0_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_PRINT_STAT_COLL,
            NULL,
            0,
            TRUE
        );
        OSA_waitMsecs(100);
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   This function Reset the statCollector registers
 *          SYSTEM_COMMON_CMD_RESET_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 ChainsCommon_statCollectorReset()
{
#if !defined (QNX_BUILD)
    UInt32 linkId;

    linkId = IPU1_0_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_RESET_STAT_COLL,
            NULL,
            0,
            TRUE
        );
        OSA_waitMsecs(100);
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Show CPU status from remote CPUs
 *
 *******************************************************************************
 */
void ChainsCommon_printCpuStatus()
{
    if(System_isProcEnabled(SYSTEM_IPU_PROC_PRIMARY))
    {
        System_linkControl(
            SYSTEM_LINK_ID_IPU1_0,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_DSP1))
    {
        System_linkControl(
            SYSTEM_LINK_ID_DSP1,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_DSP2))
    {
        System_linkControl(
            SYSTEM_LINK_ID_DSP2,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_EVE1))
    {
        System_linkControl(
            SYSTEM_LINK_ID_EVE1,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_EVE2))
    {
        System_linkControl(
            SYSTEM_LINK_ID_EVE2,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_EVE3))
    {
        System_linkControl(
            SYSTEM_LINK_ID_EVE3,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_EVE4))
    {
        System_linkControl(
            SYSTEM_LINK_ID_EVE4,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
}

/**
 *******************************************************************************
 *
 * \brief   Return W x H of a given display type
 *
 *******************************************************************************
*/
Void ChainsCommon_GetDisplayWidthHeight(
        Chains_DisplayType displayType,
        UInt32 *displayWidth,
        UInt32 *displayHeight)
{
    switch(displayType)
    {
        case CHAINS_DISPLAY_TYPE_LCD_7_INCH:
            *displayWidth = 800;
            *displayHeight = 480;
            break;
        case CHAINS_DISPLAY_TYPE_LCD_10_INCH:
            *displayWidth = 1280;
            *displayHeight = 800;
            break;
        case CHAINS_DISPLAY_TYPE_LDC_10_INCH_LCDCTRL_TC358778_MIPI_DSI_1920_1200:
            *displayWidth = 1920;
            *displayHeight = 1200;
            break;
        case CHAINS_DISPLAY_TYPE_HDMI_720P:
            *displayWidth = 1280;
            *displayHeight = 720;
            break;
        case CHAINS_DISPLAY_TYPE_HDMI_1080P:
            *displayWidth = 1920;
            *displayHeight = 1080;
            break;
        case CHAINS_DISPLAY_TYPE_FPD:
            *displayWidth = 1280;
            *displayHeight = 720;
            break;
        default:
            OSA_assert(0);
            break;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Setups Display Controller to dual display on On-chip HDMI and
 *          LCD
 *
 *          Configure such that VID2 and VID3 pipe goto LCD
 *          And VID1 and GRPX pipe goes to HDMI
 *
 *          HDMI is hardcoded to 1080p60 resolution
 *          LCD is hardcoded to 800x480 resolution
 *
 *          NOTE, this is just a sample config use by example use-cases
 *          User's can configure it different in their use-case
 *
 *******************************************************************************
*/


Int32 ChainsCommon_DualDisplay_StartDisplayCtrl(
Chains_DisplayType lcdType, UInt32 displayLCDWidth, UInt32 displayLCDHeight)
{
    Int32 status;
    DisplayCtrlLink_ConfigParams *pPrm = &gChains_commonObj.dctrlCfgPrms;
    DisplayCtrlLink_VencInfo *pVInfo;
    DisplayCtrlLink_OvlyParams *pOvlyPrms;
    DisplayCtrlLink_OvlyPipeParams *pPipeOvlyPrms;
    DisplayCtrlLink_OvlyParams ovlyPrms[2];

    /* Set the link id */
    gChains_commonObj.displayCtrlLinkId = SYSTEM_LINK_ID_DISPLAYCTRL;

    /* Number of valid entries in vencInfo array */
    pPrm->numVencs = 2;
    /* Bitmask of tied vencs. Two vencs, which uses same pixel clock and whose vsync are synchronized, can be tied together. */
    pPrm->tiedVencs = 0;
    /* Activate the HDMI BSP layer in the Dctrl link. This is not required if there is no HDMI display in use. */
    pPrm->deviceId = DISPLAYCTRL_LINK_USE_HDMI;

    /* Configure HDMI display */
    pVInfo                                  = &pPrm->vencInfo[0];
    pVInfo->vencId                          = SYSTEM_DCTRL_DSS_VENC_HDMI;
    pVInfo->outputPort                      = SYSTEM_DCTRL_DSS_HDMI_OUTPUT;
    pVInfo->vencOutputInfo.vsPolarity       = SYSTEM_DCTRL_POLARITY_ACT_HIGH;
    pVInfo->vencOutputInfo.hsPolarity       = SYSTEM_DCTRL_POLARITY_ACT_HIGH;

    /* Below are of dont care for EVM LCD */
    pVInfo->vencOutputInfo.fidPolarity      = SYSTEM_DCTRL_POLARITY_ACT_LOW;
    pVInfo->vencOutputInfo.actVidPolarity   = SYSTEM_DCTRL_POLARITY_ACT_HIGH;

    /* We use 1080p60 - set to SYSTEM_STD_720P_60 for 720p! */
    pVInfo->mInfo.standard                  = SYSTEM_STD_1080P_60;

    /* Configure HDMI overlay parameters */
    pVInfo->mode                            = 0;
    pVInfo->isInputPipeConnected[0]         = TRUE;
    pVInfo->isInputPipeConnected[1]         = FALSE;
    pVInfo->isInputPipeConnected[2]         = FALSE;
    pVInfo->isInputPipeConnected[3]         = TRUE;
    pVInfo->writeBackEnabledFlag            = FALSE;

    pVInfo->vencOutputInfo.dataFormat       = SYSTEM_DF_RGB24_888;
    pVInfo->vencOutputInfo.dvoFormat        = SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
    pVInfo->vencOutputInfo.videoIfWidth     = SYSTEM_VIFW_24BIT;

    pVInfo->vencOutputInfo.pixelClkPolarity = SYSTEM_DCTRL_POLARITY_ACT_HIGH;
    pVInfo->vencOutputInfo.aFmt             = SYSTEM_DCTRL_A_OUTPUT_MAX;

    pOvlyPrms                               = &ovlyPrms[0];
    pOvlyPrms->vencId                       = pVInfo->vencId;
    pOvlyPrms->deltaLinesPerPanel           = 0;
    pOvlyPrms->alphaBlenderEnable           = 0;
    pOvlyPrms->backGroundColor              = 0x10;
    pOvlyPrms->colorKeyEnable               = 1;
    pOvlyPrms->colorKeySel                  = SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    pOvlyPrms->ovlyOptimization             = SYSTEM_DSS_DISPC_OVLY_FETCH_ALLDATA;
    pOvlyPrms->transColorKey                = DRAW2D_TRANSPARENT_COLOR;

/* Configure LCD */
    pVInfo                                  = &pPrm->vencInfo[1];
    pVInfo->vencId                          = SYSTEM_DCTRL_DSS_VENC_LCD1;
    pVInfo->outputPort                      = SYSTEM_DCTRL_DSS_DPI1_OUTPUT;
    pVInfo->vencOutputInfo.vsPolarity       = SYSTEM_DCTRL_POLARITY_ACT_LOW;
    pVInfo->vencOutputInfo.hsPolarity       = SYSTEM_DCTRL_POLARITY_ACT_LOW;

    /* Below are of dont care for EVM LCD */
    pVInfo->vencOutputInfo.fidPolarity      = SYSTEM_DCTRL_POLARITY_ACT_HIGH;
    pVInfo->vencOutputInfo.actVidPolarity   = SYSTEM_DCTRL_POLARITY_ACT_HIGH;

    pVInfo->mInfo.standard                  = SYSTEM_STD_CUSTOM;
    pVInfo->mInfo.scanFormat                = SYSTEM_SF_PROGRESSIVE;
    pVInfo->mInfo.width                     = displayLCDWidth;
    pVInfo->mInfo.height                    = displayLCDHeight;

    if(lcdType == CHAINS_DISPLAY_TYPE_LCD_7_INCH)
    {
    pVInfo->mInfo.pixelClock                = 29232u;
    pVInfo->mInfo.fps                       = 60U;
    pVInfo->mInfo.hFrontPorch               = 40u;
    pVInfo->mInfo.hBackPorch                = 40u;
    pVInfo->mInfo.hSyncLen                  = 48u;
    pVInfo->mInfo.vFrontPorch               = 13u;
    pVInfo->mInfo.vBackPorch                = 29u;
    pVInfo->mInfo.vSyncLen                  = 3u;
    pVInfo->vencDivisorInfo.divisorLCD      = 1;
    pVInfo->vencDivisorInfo.divisorPCD      = 4;
    }
    else if(lcdType == CHAINS_DISPLAY_TYPE_LCD_10_INCH)
    {
        pVInfo->mInfo.pixelClock                =   74500U;
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hBackPorch                =   80U;
        pVInfo->mInfo.hSyncLen                  =   62U;
        pVInfo->mInfo.hFrontPorch               =   48U;
        pVInfo->mInfo.vBackPorch                =   12U;
        pVInfo->mInfo.vSyncLen                  =   35U;
        pVInfo->mInfo.vFrontPorch               =   6U;
        pVInfo->vencDivisorInfo.divisorLCD      =   1;
        pVInfo->vencDivisorInfo.divisorPCD      =   1;
    }
    else if (lcdType ==
    CHAINS_DISPLAY_TYPE_LDC_10_INCH_LCDCTRL_TC358778_MIPI_DSI_1920_1200)
    {
        pVInfo->mInfo.pixelClock                =   147000U;
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hBackPorch                =   30U;
        pVInfo->mInfo.hSyncLen                  =   16U;
        pVInfo->mInfo.hFrontPorch               =   32U;
        pVInfo->mInfo.vBackPorch                =   16U;
        pVInfo->mInfo.vSyncLen                  =   2U;
        pVInfo->mInfo.vFrontPorch               =   7U;
        pVInfo->vencDivisorInfo.divisorLCD      =   1;
        pVInfo->vencDivisorInfo.divisorPCD      =   1;
    }
    else if (lcdType == CHAINS_DISPLAY_TYPE_FPD)
    {
        pPrm->deviceId = DISPLAYCTRL_LINK_USE_LCD;
        pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD3;
        pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI3_OUTPUT;
        pVInfo->mInfo.width                     =   displayLCDWidth;
        pVInfo->mInfo.height                    =   displayLCDHeight;
        pVInfo->mInfo.pixelClock                =   69300; /* modified as per panel-tlc59108.c form linux*/
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hBackPorch                =   44U;
        pVInfo->mInfo.hSyncLen                  =   32U;
        pVInfo->mInfo.hFrontPorch               =   48U;
        pVInfo->mInfo.vBackPorch                =   12U;
        pVInfo->mInfo.vSyncLen                  =   7U;
        pVInfo->mInfo.vFrontPorch               =   4U;
        pVInfo->vencDivisorInfo.divisorLCD      =   1;
        pVInfo->vencDivisorInfo.divisorPCD      =   1;
        pVInfo->vencOutputInfo.vsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.hsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_LOW;

        /* Below are of dont care for EVM LCD */
        pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

        pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
        pVInfo->vencOutputInfo.dvoFormat        =
                                    SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
        pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

        pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

        /* Configure overlay params */
        pOvlyPrms                               = &ovlyPrms[1];
        pOvlyPrms->vencId                       = pVInfo->vencId;
        pOvlyPrms->deltaLinesPerPanel           = 0;
        pOvlyPrms->alphaBlenderEnable           = 0;
        pOvlyPrms->backGroundColor              = 0x10;
        pOvlyPrms->colorKeyEnable               = 1;
        pOvlyPrms->colorKeySel                  = SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_SRC;
        pOvlyPrms->ovlyOptimization             = SYSTEM_DSS_DISPC_OVLY_FETCH_ALLDATA;
        pOvlyPrms->transColorKey                = DRAW2D_TRANSPARENT_COLOR;
    }
    else
    {
        UTILS_assert(NULL);
    }
    /* Configure LCD overlay params */
    pVInfo->mode = 0;
    pVInfo->isInputPipeConnected[0]         = FALSE;
    pVInfo->isInputPipeConnected[1]         = TRUE;
    pVInfo->isInputPipeConnected[2]         = TRUE;
    pVInfo->isInputPipeConnected[3]         = FALSE;
    pVInfo->writeBackEnabledFlag            = FALSE;

    pVInfo->vencOutputInfo.dataFormat       = SYSTEM_DF_RGB24_888;
    pVInfo->vencOutputInfo.dvoFormat        = SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
    pVInfo->vencOutputInfo.videoIfWidth     = SYSTEM_VIFW_24BIT;

    pVInfo->vencOutputInfo.pixelClkPolarity = SYSTEM_DCTRL_POLARITY_ACT_LOW;
    pVInfo->vencOutputInfo.aFmt             = SYSTEM_DCTRL_A_OUTPUT_MAX;

    if(lcdType != CHAINS_DISPLAY_TYPE_FPD)
    {
        pOvlyPrms                               = &ovlyPrms[1];
        pOvlyPrms->vencId                       = pVInfo->vencId;
        pOvlyPrms->deltaLinesPerPanel           = 0;
        pOvlyPrms->alphaBlenderEnable           = 0;
        pOvlyPrms->backGroundColor              = 0x10;
        pOvlyPrms->colorKeyEnable               = 1;
        pOvlyPrms->colorKeySel                  = SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_SRC;
        pOvlyPrms->ovlyOptimization             = SYSTEM_DSS_DISPC_OVLY_FETCH_ALLDATA;
        pOvlyPrms->transColorKey                = DRAW2D_TRANSPARENT_COLOR;
    }
    /* Setting HDMI overlay pipe parameters */
    pPipeOvlyPrms                           = &gChains_commonObj.pipeParams[0];
    pPipeOvlyPrms->pipeLine                 = SYSTEM_DSS_DISPC_PIPE_VID1;
    pPipeOvlyPrms->globalAlpha              = 0xFF;
    pPipeOvlyPrms->preMultiplyAlpha         = 0;
    pPipeOvlyPrms->zorderEnable             = TRUE;
    pPipeOvlyPrms->zorder                   = SYSTEM_DSS_DISPC_ZORDER0;

    /* Setting LCD overlay pipe parameters */
    pPipeOvlyPrms                           = &gChains_commonObj.pipeParams[1];
    pPipeOvlyPrms->pipeLine                 = SYSTEM_DSS_DISPC_PIPE_VID2;
    pPipeOvlyPrms->globalAlpha              = 0xFF;
    pPipeOvlyPrms->preMultiplyAlpha         = 0;
    pPipeOvlyPrms->zorderEnable             = TRUE;
    pPipeOvlyPrms->zorder                   = SYSTEM_DSS_DISPC_ZORDER0;

    /* Setting PIP overlay pipe parameters on LCD */
    pPipeOvlyPrms                           = &gChains_commonObj.pipeParams[2];
    pPipeOvlyPrms->pipeLine                 = SYSTEM_DSS_DISPC_PIPE_VID3;
    pPipeOvlyPrms->globalAlpha              = 0xFF;
    pPipeOvlyPrms->preMultiplyAlpha         = 0;
    pPipeOvlyPrms->zorderEnable             = TRUE;
    pPipeOvlyPrms->zorder                   = SYSTEM_DSS_DISPC_ZORDER2;

    /* Configure graphics overlay for HDMI */
    pPipeOvlyPrms                           = &gChains_commonObj.pipeParams[3];
    pPipeOvlyPrms->pipeLine                 = SYSTEM_DSS_DISPC_PIPE_GFX1;
    pPipeOvlyPrms->globalAlpha              = 0xFF;
    pPipeOvlyPrms->preMultiplyAlpha         = 0;
    pPipeOvlyPrms->zorderEnable             = TRUE;
    pPipeOvlyPrms->zorder                   = SYSTEM_DSS_DISPC_ZORDER3;

/* Create, configure and start the Display Ctrl link */
    status = System_linkCreate(gChains_commonObj.displayCtrlLinkId,
                                NULL,
                                0);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_CONFIG,
                                &gChains_commonObj.dctrlCfgPrms,
                                sizeof(DisplayCtrlLink_ConfigParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PARAMS,
                                &ovlyPrms[0],
                                sizeof(DisplayCtrlLink_OvlyParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PARAMS,
                                &ovlyPrms[1],
                                sizeof(DisplayCtrlLink_OvlyParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[0],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[1],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[2],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[3],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}


/**
 *******************************************************************************
 *
 * \brief   Set display link parameters in the case of single video pipe
 *          and one graphics pipe
 *
 *******************************************************************************
*/
Void ChainsCommon_SetDisplayPrms(
                                DisplayLink_CreateParams *pPrm_Video,
                                DisplayLink_CreateParams *pPrm_Grpx,
                                Chains_DisplayType displayType,
                                UInt32 displayWidth,
                                UInt32 displayHeight)
{
    if(pPrm_Video)
    {
        pPrm_Video->rtParams.tarWidth         = displayWidth;
        pPrm_Video->rtParams.tarHeight        = displayHeight;
        pPrm_Video->displayId                 = DISPLAY_LINK_INST_DSS_VID1;
    }

    if(pPrm_Grpx)
    {
        pPrm_Grpx->displayId                  = DISPLAY_LINK_INST_DSS_GFX1;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Display Controller Create Parameters
 *
 * \param   pPrm         [IN]    DisplayCtrlLink_ConfigParams
 *
 *******************************************************************************
*/
static Void ChainsCommon_SetDctrlConfig(
                                DisplayCtrlLink_ConfigParams *pPrm,
                                DisplayCtrlLink_OvlyParams *ovlyPrms,
                                DisplayCtrlLink_OvlyPipeParams *pipeOvlyPrms,
                                UInt32 displayType,
                                UInt32 displayWidth,
                                UInt32 displayHeight)
{
    DisplayCtrlLink_VencInfo *pVInfo;

    pPrm->numVencs = 1;
    pPrm->tiedVencs = 0;

    pVInfo = &pPrm->vencInfo[0];

    pVInfo->tdmMode = DISPLAYCTRL_LINK_TDM_DISABLE;
    if(displayType == CHAINS_DISPLAY_TYPE_LCD_7_INCH)
    {
        pPrm->deviceId = DISPLAYCTRL_LINK_USE_LCD;
        pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD1;
        pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI1_OUTPUT;
        pVInfo->vencOutputInfo.vsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.hsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;

        /* Below are of dont care for EVM LCD */
        pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_LOW;

        pVInfo->mInfo.standard                  =   SYSTEM_STD_CUSTOM;
        pVInfo->mInfo.width                     =   displayWidth;
        pVInfo->mInfo.height                    =   displayHeight;
        pVInfo->mInfo.scanFormat                =   SYSTEM_SF_PROGRESSIVE;
        pVInfo->mInfo.pixelClock                =   29232u;
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hFrontPorch               =   40u;
        pVInfo->mInfo.hBackPorch                =   40u;
        pVInfo->mInfo.hSyncLen                  =   48u;
        pVInfo->mInfo.vFrontPorch               =   13u;
        pVInfo->mInfo.vBackPorch                =   29u;
        pVInfo->mInfo.vSyncLen                  =   3u;
        pVInfo->vencDivisorInfo.divisorLCD      =   1;
        pVInfo->vencDivisorInfo.divisorPCD      =   4;

        pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
        pVInfo->vencOutputInfo.dvoFormat        =
                                    SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
        pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

        pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

        /* Configure overlay params */

        ovlyPrms->vencId                       = SYSTEM_DCTRL_DSS_VENC_LCD1;
    }
    else if(displayType == CHAINS_DISPLAY_TYPE_LCD_10_INCH)
    {
        pPrm->deviceId = DISPLAYCTRL_LINK_USE_LCD;
        pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD1;
        pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI1_OUTPUT;
        pVInfo->vencOutputInfo.vsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.hsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;

        /* Below are of dont care for EVM LCD */
        pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

        pVInfo->mInfo.standard                  =   SYSTEM_STD_CUSTOM;
        pVInfo->mInfo.width                     =   displayWidth;
        pVInfo->mInfo.height                    =   displayHeight;
        pVInfo->mInfo.scanFormat                =   SYSTEM_SF_PROGRESSIVE;
        pVInfo->mInfo.pixelClock                =   74500U;
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hBackPorch                =   80U;
        pVInfo->mInfo.hSyncLen                  =   62U;
        pVInfo->mInfo.hFrontPorch               =   48U;
        pVInfo->mInfo.vBackPorch                =   12U;
        pVInfo->mInfo.vSyncLen                  =   35U;
        pVInfo->mInfo.vFrontPorch               =   6U;
        pVInfo->vencDivisorInfo.divisorLCD      =   1;
        pVInfo->vencDivisorInfo.divisorPCD      =   1;

        pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
        pVInfo->vencOutputInfo.dvoFormat        =
                                    SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
        pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

        pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

        /* Configure overlay params */

        ovlyPrms->vencId                       = SYSTEM_DCTRL_DSS_VENC_LCD1;
    }
    else if (displayType ==
        CHAINS_DISPLAY_TYPE_LDC_10_INCH_LCDCTRL_TC358778_MIPI_DSI_1920_1200)
    {
        pPrm->deviceId = DISPLAYCTRL_LINK_USE_LCD;
        pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD1;
        pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI1_OUTPUT;
        pVInfo->vencOutputInfo.vsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.hsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;

        /* Below are of dont care for EVM LCD */
        pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

        pVInfo->mInfo.standard                  =   SYSTEM_STD_CUSTOM;
        pVInfo->mInfo.width                     =   displayWidth;
        pVInfo->mInfo.height                    =   displayHeight;
        pVInfo->mInfo.scanFormat                =   SYSTEM_SF_PROGRESSIVE;
        pVInfo->mInfo.pixelClock                =   147000U;
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hBackPorch                =   32U;
        pVInfo->mInfo.hSyncLen                  =   16U;
        pVInfo->mInfo.hFrontPorch               =   32U;
        pVInfo->mInfo.vBackPorch                =   16U;
        pVInfo->mInfo.vSyncLen                  =   2U;
        pVInfo->mInfo.vFrontPorch               =   7U;
        pVInfo->vencDivisorInfo.divisorLCD      =   1;
        pVInfo->vencDivisorInfo.divisorPCD      =   1;

        pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
        pVInfo->vencOutputInfo.dvoFormat        =
                                    SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
        pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

        pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

        /* Configure overlay params */

        ovlyPrms->vencId                       = SYSTEM_DCTRL_DSS_VENC_LCD1;
    }
    else if(displayType == CHAINS_DISPLAY_TYPE_HDMI_720P
            || displayType == CHAINS_DISPLAY_TYPE_HDMI_1080P)
    {
        pPrm->deviceId = DISPLAYCTRL_LINK_USE_HDMI;
        pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_HDMI;
        pVInfo->outputPort = SYSTEM_DCTRL_DSS_HDMI_OUTPUT;
        pVInfo->vencOutputInfo.vsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.hsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

        /* Below are of dont care for EVM LCD */
        pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

        pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
        pVInfo->vencOutputInfo.dvoFormat        =
                                    SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
        pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

        pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

        /* Configure overlay params */

        ovlyPrms->vencId                        = pVInfo->vencId;
    }
    else if(displayType == CHAINS_DISPLAY_TYPE_FPD)
    {
        pPrm->deviceId = DISPLAYCTRL_LINK_USE_LCD;
        pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD3;
        pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI3_OUTPUT;
        pVInfo->mInfo.width                     =   displayWidth;
        pVInfo->mInfo.height                    =   displayHeight;
        pVInfo->mInfo.pixelClock                =   74250;
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hBackPorch                =   148U;
        pVInfo->mInfo.hSyncLen                  =   44U;
        pVInfo->mInfo.hFrontPorch               =   88U;
        pVInfo->mInfo.vBackPorch                =   15U;
        pVInfo->mInfo.vSyncLen                  =   5U;
        pVInfo->mInfo.vFrontPorch               =   2U;
        pVInfo->vencDivisorInfo.divisorLCD      =   1;
        pVInfo->vencDivisorInfo.divisorPCD      =   1;
        pVInfo->vencOutputInfo.vsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.hsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

        /* Below are of dont care for EVM LCD */
        pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

        pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
        pVInfo->vencOutputInfo.dvoFormat        =
                                    SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
        pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

        pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

        /* Configure overlay params */

        ovlyPrms->vencId                        = pVInfo->vencId;
    }
    else
    {
        OSA_assert(0);
    }

    if(displayType == CHAINS_DISPLAY_TYPE_HDMI_720P)
    {
        pVInfo->mInfo.standard                  =   SYSTEM_STD_720P_60;

    }
    else if (displayType == CHAINS_DISPLAY_TYPE_HDMI_1080P)
    {
        pVInfo->mInfo.standard                  =   SYSTEM_STD_1080P_60;
    }
    else if (displayType == CHAINS_DISPLAY_TYPE_FPD)
    {
        pVInfo->mInfo.standard                  =   SYSTEM_STD_720P_60;
    }

    /* TODO Dont know what to set here */
    pVInfo->mode = 0;
    pVInfo->isInputPipeConnected[0] =
                    TRUE;
    pVInfo->isInputPipeConnected[1] =
                    TRUE;
    pVInfo->isInputPipeConnected[2] =
                    TRUE;
    pVInfo->isInputPipeConnected[3] =
                    TRUE;
    pVInfo->writeBackEnabledFlag = FALSE;


    /* Setting other overlay parameters common to both Venc */

    ovlyPrms->deltaLinesPerPanel   = 0;
    ovlyPrms->alphaBlenderEnable   = 0;
    ovlyPrms->backGroundColor      = 0x10;
    ovlyPrms->colorKeyEnable       = 1;
    ovlyPrms->colorKeySel          = SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    ovlyPrms->ovlyOptimization     = SYSTEM_DSS_DISPC_OVLY_FETCH_ALLDATA;
    ovlyPrms->transColorKey        = DRAW2D_TRANSPARENT_COLOR;

    /* Setting overlay pipe parameters */

    pipeOvlyPrms[0].pipeLine = SYSTEM_DSS_DISPC_PIPE_VID1;
    pipeOvlyPrms[0].globalAlpha = 0xFF;
    pipeOvlyPrms[0].preMultiplyAlpha = 0;
    pipeOvlyPrms[0].zorderEnable = TRUE;
    pipeOvlyPrms[0].zorder = SYSTEM_DSS_DISPC_ZORDER0;

    pipeOvlyPrms[1].pipeLine = SYSTEM_DSS_DISPC_PIPE_VID2;
    pipeOvlyPrms[1].globalAlpha = 0xFF;
    pipeOvlyPrms[1].preMultiplyAlpha = 0;
    pipeOvlyPrms[1].zorderEnable = TRUE;
    pipeOvlyPrms[1].zorder = SYSTEM_DSS_DISPC_ZORDER1;

    pipeOvlyPrms[2].pipeLine = SYSTEM_DSS_DISPC_PIPE_VID3;
    pipeOvlyPrms[2].globalAlpha = 0xFF;
    pipeOvlyPrms[2].preMultiplyAlpha = 0;
    pipeOvlyPrms[2].zorderEnable = TRUE;
    pipeOvlyPrms[2].zorder = SYSTEM_DSS_DISPC_ZORDER2;

    pipeOvlyPrms[3].pipeLine = SYSTEM_DSS_DISPC_PIPE_GFX1;
    pipeOvlyPrms[3].globalAlpha = 0xFF;
    pipeOvlyPrms[3].preMultiplyAlpha = 0;
    pipeOvlyPrms[3].zorderEnable = TRUE;
    pipeOvlyPrms[3].zorder = SYSTEM_DSS_DISPC_ZORDER3;

}

/**
 *******************************************************************************
 *
 * \brief   Configure and start display controller
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StartDisplayCtrl(UInt32 displayType,
                                UInt32 displayWidth,
                                UInt32 displayHeight)
{
    Int32 status=0;

    gChains_commonObj.displayCtrlLinkId = SYSTEM_LINK_ID_DISPLAYCTRL;

    ChainsCommon_SetDctrlConfig(
        &gChains_commonObj.dctrlCfgPrms,
        &gChains_commonObj.ovlyParams,
        &gChains_commonObj.pipeParams[0],
        displayType,
        displayWidth,
        displayHeight
        );

    /* There are no createtime Params for display controller */
    status = System_linkCreate(gChains_commonObj.displayCtrlLinkId,
                                NULL,
                                0);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_CONFIG,
                                &gChains_commonObj.dctrlCfgPrms,
                                sizeof(DisplayCtrlLink_ConfigParams),
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PARAMS,
                                &gChains_commonObj.ovlyParams,
                                sizeof(DisplayCtrlLink_OvlyParams),
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[0],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[1],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                            DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                            &gChains_commonObj.pipeParams[2],
                            sizeof(DisplayCtrlLink_OvlyPipeParams),
                            TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[3],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

#ifdef BOARD_TYPE_TDA2XX_RVP
    if (0x01 == gChains_commonObj.boardIds.boardIdSOM || // TDA2xx RVP SOM Rev 1
        0x06 == gChains_commonObj.boardIds.boardIdSOM || // TDA2xx RVP SOM Rev 2
        0x09 == gChains_commonObj.boardIds.boardIdSOM)   // TDA2xx RVP SOM Rev 3
    {
          status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                      DISPLAYCTRL_LINK_CMD_HDMI_FLIP_DATA_P_N_ORDER,
                                      NULL,
                                      0,
                                      TRUE);
          OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Stop and Delete display controller
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StopDisplayCtrl()
{
    Int32 status=0;

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_CLR_CONFIG,
                                &gChains_commonObj.dctrlCfgPrms,
                                sizeof(DisplayCtrlLink_ConfigParams),
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkDelete(gChains_commonObj.displayCtrlLinkId);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Set display link parameters in the case of single video pipe
 *          and one graphics pipe
 *
 *******************************************************************************
*/
Void ChainsCommon_SetGrpxSrcPrms(
                                GrpxSrcLink_CreateParams *pPrm,
                                UInt32 displayWidth,
                                UInt32 displayHeight
                                )
{
    pPrm->grpxBufInfo.dataFormat  = SYSTEM_DF_BGR16_565;
    pPrm->grpxBufInfo.height   = displayHeight;
    pPrm->grpxBufInfo.width    = displayWidth;

    pPrm->logoDisplayEnable = TRUE;
    pPrm->logoParams.startX = 40;
    pPrm->logoParams.startY = 40;

    pPrm->statsDisplayEnable = TRUE;

    pPrm->statsPrintParams.startX = pPrm->logoParams.startX;
    pPrm->statsPrintParams.startY = displayHeight - 134 - pPrm->logoParams.startY;
}

/**
 *******************************************************************************
 *
 * \brief   Set AVBRX Create Parameters
 *
 *          It is called in Create function.
 *          All AVBRX parameters are set.
 *
 * \param   pPrm         [IN]    AvbRxLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SetAvbRxPrm(       AvbRxLink_CreateParams *pAvbPrm,
                                     UInt32 maxWidth,
                                     UInt32 maxHeight,
                                     UInt32 numCh)
{
    UInt32 nIdx;
    UInt8 stream_ID[][8] =
    {
        {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xE0},
        {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xE1},
        {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xE2},
        {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xE3},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x03},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x04}
    };
    UInt8 SrcMACAdd[][6] =
    {
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05}
    };

    for (nIdx = 0; nIdx < numCh; nIdx++)
    {
        memcpy(pAvbPrm->streamId[nIdx], stream_ID[nIdx],sizeof(stream_ID[nIdx]));
        memcpy(pAvbPrm->srcMacId[nIdx], SrcMACAdd[nIdx],sizeof(SrcMACAdd[nIdx]));
    }
    pAvbPrm->numCameras = numCh;
    pAvbPrm->numBufs = AVB_RX_LINK_NUM_BUFS_PER_TALKER_DEFAULT;
    pAvbPrm->buffSize = AVB_TALKER_MAX_FRAME_SIZE;
    pAvbPrm->width  = maxWidth;
    pAvbPrm->height = maxHeight;
}

/**
 *******************************************************************************
 *
 * \brief   Set AVBTX Create Parameters
 *
 *          It is called in Create function.
 *          All AVBTX parameters are set.
 *
 * \param   pPrm         [IN]    AvbTxLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SetAvbTxPrm(       AvbTxLink_CreateParams *pAvbPrm,
                                     UInt32 numCh,
                                     System_IVideoFormat codecType)
{
    UInt32 nIdx;
    UInt8 dstMacId[][8] =
    {
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
    };

    /*
     * Current AVB Implementation doesn't use configurable stream id, streamId
     * for the different AVB talkers is made using src address and talker index
     * combination.
     */
    UInt8 stream_ID[][8] =
    {
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x02},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x03},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x04}
    };

    UInt8 SrcMACAdd[][6] =
    {
        {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
        {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
        {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
        {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
        {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
    };

    /* Set default Subtype - Compressed Video Format (0x3) */
    UInt32 avbTpSubType[AVB_TX_LINK_MAX_TALKERS_DEFAULT] = {AVB_TX_LINK_SUBTYPE_CVF,
                                                            AVB_TX_LINK_SUBTYPE_CVF,
                                                            AVB_TX_LINK_SUBTYPE_CVF,
                                                            AVB_TX_LINK_SUBTYPE_CVF};

    UInt32 cvFormatSubType[AVB_TX_LINK_MAX_TALKERS_DEFAULT] = {AVB_TX_LINK_CVF_SUBTYPE_H264,
                                                            AVB_TX_LINK_CVF_SUBTYPE_H264,
                                                            AVB_TX_LINK_CVF_SUBTYPE_H264,
                                                            AVB_TX_LINK_CVF_SUBTYPE_H264};
    for (nIdx = 0; nIdx < numCh; nIdx++)
    {
        memcpy(pAvbPrm->streamId[nIdx], stream_ID[nIdx],sizeof(stream_ID[nIdx]));
        memcpy(pAvbPrm->srcMacId[nIdx], SrcMACAdd[nIdx],sizeof(SrcMACAdd[nIdx]));
        memcpy(pAvbPrm->dstMacId[nIdx], dstMacId[nIdx],sizeof(dstMacId[nIdx]));
        pAvbPrm->avbTpSubType[nIdx] = avbTpSubType[nIdx];
        /* Set AVBTP cvFormattype as per encoding format */
        if (SYSTEM_IVIDEO_H264HP == codecType)
        {
            pAvbPrm->cvFormatSubType[nIdx] = AVB_TX_LINK_CVF_SUBTYPE_H264;
        }
        else if (SYSTEM_IVIDEO_MJPEG == codecType)
        {
            pAvbPrm->cvFormatSubType[nIdx] = AVB_TX_LINK_CVF_SUBTYPE_MJPEG;
        }
        else
        {
            pAvbPrm->cvFormatSubType[nIdx] = cvFormatSubType[nIdx];
        }
    }

}

/**
 *******************************************************************************
 *
 * \brief   Set Decode Create Parameters
 *
 *          It is called in Create function.
 *          All decoder parameters are set.
 *
 * \param   pPrm         [IN]    DecodeLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SetDecodePrm(     DecLink_CreateParams *pDecPrm,
                                     UInt32 maxWidth,
                                     UInt32 maxHeight,
                                     UInt32 numCh,
                                     System_IVideoFormat codecType)
{
    UInt32 chId;
    DecLink_ChCreateParams *decPrm;

    for (chId = 0; chId<numCh; chId++)
    {
        UTILS_assert (chId < DEC_LINK_MAX_CH);
        decPrm = &pDecPrm->chCreateParams[chId];

        decPrm->dpbBufSizeInFrames  = DEC_LINK_DPB_SIZE_IN_FRAMES_DEFAULT;
        decPrm->algCreateStatus     = DEC_LINK_ALG_CREATE_STATUS_CREATE;
        decPrm->decodeFrameType     = DEC_LINK_DECODE_ALL;

        decPrm->processCallLevel    = DEC_LINK_FRAMELEVELPROCESSCALL;
        decPrm->targetMaxWidth      = maxWidth;
        decPrm->targetMaxHeight     = maxHeight;
        decPrm->numBufPerCh         = DEC_LINK_NUM_BUFFERS_PER_CHANNEL;
        decPrm->defaultDynamicParams.targetBitRate = 10 * 1000 * 1000;
        decPrm->defaultDynamicParams.targetFrameRate = 30;
        decPrm->fieldMergeDecodeEnable = FALSE;

        switch (codecType)
        {
            case SYSTEM_IVIDEO_MJPEG: /* MJPEG */
                decPrm->format = SYSTEM_IVIDEO_MJPEG;
                decPrm->profile = 0;
                decPrm->displayDelay = 0;
                break;

            case SYSTEM_IVIDEO_H264HP: /* H264 */
                decPrm->format = SYSTEM_IVIDEO_H264HP;
                decPrm->profile = 3;
                decPrm->displayDelay = 0;
                break;

            default: /* D1 */
                printf("\r\nCodec Type: %d, returning \n", codecType);
                UTILS_assert(FALSE);
                break;
        }
    }
}
