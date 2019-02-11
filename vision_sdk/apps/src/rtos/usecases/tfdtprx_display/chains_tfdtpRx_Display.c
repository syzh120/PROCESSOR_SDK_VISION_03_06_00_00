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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_tfdtpRx_Display_priv.h"
#include <src/include/chains_common.h>
#include <ti/nsp/drv/inc/tfdtp.h>

#define TFDTP_CH_MAX_FRAME_WIDTH 1280
#define TFDTP_CH_MAX_FRAME_HEIGHT 720
#define MAX_NUMBER_OF_CHANNELS 1

/**
 *******************************************************************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define SYNC_DELTA_IN_MSEC              (66)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DROP_THRESHOLD_IN_MSEC     (150)

/**
 *******************************************************************************
 *
 *  \brief  Use-case object
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_tfdtpRx_DisplayObj ucObj;

    UInt32  numOfChannels;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;

    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

} chains_tfdtpRxDisplayAppObj;

/**
 *******************************************************************************
 *
 * \brief   Set TFDTP RX link Create Parameters
 *
 *          It is called in Create function.
 *          All TFDTP channel parameters are set.
 *
 * \param   pPrm         [IN]    TfdtpRxLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_tfdtpRx_Display_SetTfdtpRxPrm(chains_tfdtpRxDisplayAppObj *pObj,
                                TfdtpRxLink_CreateParams *pTfdtpPrm)
{
    UInt32 chId;
    System_LinkChInfo *pChInfo;


    pTfdtpPrm->numChannels = pObj->numOfChannels;
    pTfdtpPrm->numBufs = TFDTP_MAX_APP_BUF_CNT;
    pTfdtpPrm->outQueInfo.numCh = 1;

    pTfdtpPrm->videoDataFormat = SYSTEM_DF_YUV422I_YUYV;

    for (chId = 0; chId < pTfdtpPrm->outQueInfo.numCh; chId++)
    {
        pChInfo = &pTfdtpPrm->outQueInfo.chInfo[chId];

        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pChInfo->flags,
                                                    SYSTEM_SF_PROGRESSIVE);
        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pChInfo->flags,
                                               SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
        pChInfo->width = pObj->captureOutWidth;
        pChInfo->height = pObj->captureOutHeight;
        pChInfo->startX = 0;
        pChInfo->startY = 0;
        if (SYSTEM_DF_YUV420SP_UV == pTfdtpPrm->videoDataFormat)
        {
            pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pChInfo->flags,
                                                        SYSTEM_DF_YUV420SP_UV);
            pChInfo->pitch[0] = SystemUtils_align(pChInfo->width, 32);
            pChInfo->pitch[1] = SystemUtils_align(pChInfo->width, 32);
        }
        else if (SYSTEM_DF_YUV422I_YUYV == pTfdtpPrm->videoDataFormat)
        {
            pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pChInfo->flags,
                                                        SYSTEM_DF_YUV422I_YUYV);
            pChInfo->pitch[0] = SystemUtils_align(pChInfo->width*2, 32);
            pChInfo->pitch[1] = SystemUtils_align(pChInfo->width*2, 32);
        }
        else
        {
            /* For future additions */
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_tfdtpRx_Display_SetAppPrms(chains_tfdtpRx_DisplayObj *pUcObj, Void *appObj)
{
    chains_tfdtpRxDisplayAppObj *pObj
        = (chains_tfdtpRxDisplayAppObj*)appObj;

    pObj->numOfChannels = 1;

    if(pObj->numOfChannels > MAX_NUMBER_OF_CHANNELS);
        pObj->numOfChannels = MAX_NUMBER_OF_CHANNELS;

    pObj->captureOutWidth  = TFDTP_CH_MAX_FRAME_WIDTH;
    pObj->captureOutHeight = TFDTP_CH_MAX_FRAME_HEIGHT;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    chains_tfdtpRx_Display_SetTfdtpRxPrm( pObj,&pUcObj->TfdtpRxPrm);

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                              );

    ChainsCommon_SetDisplayPrms(&pUcObj->Display_VideoPrm,
                                               &pUcObj->Display_GrpxPrm,
                                               pObj->chainsCfg->displayType,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                                );

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );
}

/**
 *******************************************************************************
 *
 * \brief   Start the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_AvbRx_Dec_DisplayObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_tfdtpRx_Display_StartApp(chains_tfdtpRxDisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

/*Select Ethernet port depending on TDA2ex board revision*/
#if defined (TDA2EX_BUILD) && !defined(TDA2EX_ETHSRV_BOARD)
    ChainsCommon_tda2exSelectPHY(pObj->chainsCfg->captureSrc);
#endif

    chains_tfdtpRx_Display_Start(&pObj->ucObj);

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Delete the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   Chains_AvbRx_Dec_DisplayObj
 *
 *******************************************************************************
*/
Void chains_tfdtpRx_Display_StopAndDeleteApp(chains_tfdtpRxDisplayAppObj *pObj)
{
    chains_tfdtpRx_Display_Stop(&pObj->ucObj);
    chains_tfdtpRx_Display_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase function
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_tfdtpRx_Display(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    chains_tfdtpRxDisplayAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chains_tfdtpRx_Display_Create(&chainsObj.ucObj, &chainsObj);

    chains_tfdtpRx_Display_StartApp(&chainsObj);

    while(!done)
    {
        ch = Chains_menuRunTime();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_tfdtpRx_Display_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_tfdtpRx_Display_StopAndDeleteApp(&chainsObj);
}

