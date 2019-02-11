/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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
 * \file devControl_tsk.c
 *
 * \brief  This file contains device control APIs
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "devControl_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>


/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
static Void devCtrlCmdHandler(UInt32 cmd, Void *pPrm);


/**
 *******************************************************************************
 *
 * \brief   NetworkCtrl_devCtrlCmdHandler_Init
 *
 *          This function registers command handler in system
 *          link for file IO comands.
 *
 * \param   NULL
 *
  *******************************************************************************
 */
Void DevCtrl_init()
{
    SystemLink_registerHandler(devCtrlCmdHandler);
}

/**
 *******************************************************************************
 *
 * \brief   NetworkCtrl_devCtrlCmdHandler_DeInit
 *
 *          This function deregisters command handler in system
 *          link for file IO comands.
 *
 * \param   NULL
 *
 *******************************************************************************
 */
Void DevCtrl_deInit()
{
    SystemLink_unregisterHandler(devCtrlCmdHandler);
}

/**
 *******************************************************************************
 *
 * \brief   callback to handle file IO using system link
 *
 *  \param  cmd [IN] Command that needs to be handled
 *               pPrm [IN/OUT] Parameters for this command
 *
 *******************************************************************************
 */
static Void devCtrlCmdHandler(UInt32 cmd, Void *pPrm)
{
    DevComm_NetworkCtrlReqPrms *devCtrlPrms;

    if (NULL != pPrm)
    {
        devCtrlPrms = (DevComm_NetworkCtrlReqPrms *)pPrm;

        if (SYSTEM_LINK_CMD_DEV_COMM == cmd)
        {
#if (DEBUG == (1U))
            UInt32 i = 0U;
            Vps_printf(" DEVCTRL: Received command for device communication \n");
            Vps_printf(" ReqParams = %x\n", devCtrlPrms->reqParam);
            Vps_printf(" ReqParam Size = %x \n", devCtrlPrms->reqParamSize);
            for (i = 0U; i < devCtrlPrms->reqParamSize/4U; i++)
            {
                Vps_printf(" %x \n", *(uint32_t*)(devCtrlPrms->reqParam + i));
            }
#endif
            *(uint32_t*)(devCtrlPrms->respParam) = 0xABCDEF01;
            devCtrlPrms->respParamSize = 0x4U;
        }
    }
}

/* Nothing beyond this point */
