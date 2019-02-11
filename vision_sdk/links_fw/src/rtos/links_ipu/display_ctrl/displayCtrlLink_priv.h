/*
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
*/

/**
 *******************************************************************************
 *
 * \ingroup DISPLAYCTRL_LINK_API
 * \defgroup DISPLAYCTRL_LINK_IMPL Display Controller Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file displayCtrlLink_priv.h
 *
 * \brief Display Controller Private Header File
 *
 *        This file has the structures, enums, function prototypes
 *        for display controller link, which are not exposed to the application
 *
 * \version 0.0 (Jun 2013) : [PS] First version
 * \version 0.1 (Jul 2013) : [PS] Updates as per code review comments
 *
 *******************************************************************************
 */

#ifndef DISPLAYCTRL_LINK_PRIV_H_
#define DISPLAYCTRL_LINK_PRIV_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/displayCtrlLink.h>
#include <include/link_api/system_const.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */
/**< Every 30 seconds Display controller wil get the sync lost status
     from driver and store it in shared memory */
#define DCTRL_LINK_TIME_OUT_IN_MS           (1000U*30U)


/**
 *******************************************************************************
 *
 *  \brief  Display Controller Link Object
 *
 *          This is the object for dislay controller link.
 *
 *******************************************************************************
*/
typedef struct {
    /* DisplayCtrl link task */
    Utils_TskHndl tsk;

    UInt32 state;
    /**< Link state, one of SYSTEM_LINK_STATE_xxx */

    /* Global displayCtrl driver handle */
    FVID2_Handle fvidHandleDisplayCtrl;

    BspOsal_ClockHandle timer;
    /**<Timer used to generate new data at a set interval*/

    Vps_DctrlErrorSyncLostStats dctrlStat;
    /**< Display Control Sync Lost status */
} DisplayCtrlLink_Obj;

extern DisplayCtrlLink_Obj gDisplayCtrlLink_obj;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Int32 DisplayCtrlLink_drvCreate(DisplayCtrlLink_Obj * pObj);

Int32 DisplayCtrlLink_drvDelete(DisplayCtrlLink_Obj * pObj);

Int32 DisplayCtrlLink_drvConfigInit(const DisplayCtrlLink_VencInfo *pVencInfo,
                                    Vps_DctrlConfig *pDctrlCfg,
                                    UInt32 vencCntr,
                                    UInt32 *pEdgeCntr,
                                    UInt32 *pipeUsedFlag);

Int32 DisplayCtrlLink_drvSetConfig(DisplayCtrlLink_Obj *pObj,
                                   DisplayCtrlLink_ConfigParams *pConfigParams);

Int32 DisplayCtrlLink_drvClrConfig(DisplayCtrlLink_Obj *pObj,
                                   DisplayCtrlLink_ConfigParams *pConfigParams);

Int32 DisplayCtrlLink_drvSetOvlyParams(DisplayCtrlLink_Obj * pObj,
                                       const DisplayCtrlLink_OvlyParams *pOvlyParams);

Int32 DisplayCtrlLink_drvSetOvlyPipelineParams(
          DisplayCtrlLink_Obj *pObj,
          const DisplayCtrlLink_OvlyPipeParams *pOvlyPipeParams);

Int32 DisplayCtrlLink_drvPrintStatus(DisplayCtrlLink_Obj * pObj);

Int32 DisplayCtrlLink_drvHdmiFlipDataPNOrder(DisplayCtrlLink_Obj *pObj);

#endif

/* @} */
