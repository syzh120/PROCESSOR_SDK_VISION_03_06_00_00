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
 *******************************************************************************/

/**
 *******************************************************************************
 * \file app_ctrl_radar.c
 *
 *
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/common/chains_radar.h>
#include <include/common/app_ctrl_radar.h>
#include <include/common/chains_radar_util_read_params.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/*******************************************************************************
 *  Data Structures
 *******************************************************************************
 */

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */
ChainsUtil_RlFrontEndConfig feCfgReq;


/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */


/*******************************************************************************
 *  Function Definition
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 * \brief   Boot and Config Radar
 *
 *******************************************************************************
*/
Void appCtrlRadarInit(ChainsCommon_Ar12xxConfigOut *pCfgObj,
                      AppCtrl_RadarConfigFiles *pConfigFiles)
{
    Int32 i, j;

    Chains_ar12xxGetSampleCascadeConfig(pCfgObj);
    if (pConfigFiles->fileParams != NULL)
    {
        UTILS_assert(pConfigFiles->numFiles <= CHAINS_MAX_NUM_RADARS);
        for (i = 0; i < pConfigFiles->numFiles; i++)
        {
            ChainsUtil_readFeParams(pConfigFiles->fileParams[i].pConfigBuf,
                                    pConfigFiles->fileParams[i].bufSize,
                                    &feCfgReq.cfg[i]);

            if (i == 0)
            {
                /* First file is the master config.
                 * It includes common settings for all radars.*/
                for (j = 0; j < pConfigFiles->numFiles; j++)
                {
                    ChainsUtil_setFeParams(&pCfgObj->radarParams[j].ar12xxConfig,
                                           &feCfgReq.cfg[0]);
                }
            }
            else
            {
                ChainsUtil_setFeParams(&pCfgObj->radarParams[i].ar12xxConfig,
                                       &feCfgReq.cfg[i]);
            }
        }
    }
    ChainsCommon_ar12xxConfig(pCfgObj);
}

/**
 *******************************************************************************
 *
 * \brief   Set IssCaptureLink_CreateParams for Radar
 *
 *******************************************************************************
*/
Void appCtrlSetRadarCaptureParamsRadar(Void *pPrm,
                                     ChainsCommon_Ar12xxConfigOut *pCfgObj)
{
    ChainsCommon_ar12xxSetMultiVipCaptureParams((CaptureLink_CreateParams *) pPrm,
                                                pCfgObj,
                                                NULL);
}

/**
 *******************************************************************************
 *
 * \brief   Start Radar
 *
 *******************************************************************************
*/
Void appCtrlRadarStart(Void)
{
    ChainsCommon_ar12xxStart();
}

/**
 *******************************************************************************
 *
 * \brief   Stop Radar
 *
 *******************************************************************************
*/
Void appCtrlRadarStop(ChainsCommon_Ar12xxConfigOut *pCfgObj)
{
    ChainsCommon_ar12xxStop(pCfgObj);
}
