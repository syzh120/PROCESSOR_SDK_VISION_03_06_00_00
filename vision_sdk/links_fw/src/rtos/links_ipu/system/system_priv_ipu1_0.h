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
 * \ingroup SYSTEM_IMPL
 *
 * \defgroup SYSTEM_IPU1_0_IMPL System implementation for IPU1 Core 0
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file system_priv_ipu1_0.h IPU1 private file containing all the header files
 *                            util files required by ipu
 *
 *
 * \version 0.0 (Jun 2013) : [CM] First version
 * \version 0.1 (Jul 2013) : [CM] Updates as per code review comments
 *
 *******************************************************************************
 */

#ifndef SYSTEM_PRIV_IPU1_0_H_
#define SYSTEM_PRIV_IPU1_0_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/captureLink.h>
#include <include/link_api/displayLink.h>
#include <include/link_api/displayCtrlLink.h>
#include <include/link_api/dupLink.h>
#include <include/link_api/gateLink.h>
#include <include/link_api/nullLink.h>
#include <include/link_api/selectLink.h>
#include <include/link_api/syncLink.h>
#include <include/link_api/mergeLink.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/algorithmLink.h>
#include <include/link_api/nullSrcLink.h>
#ifdef IVAHD_INCLUDE
#include <include/link_api/decLink.h>
#include <include/link_api/encLink.h>
#endif
#ifdef CAL_INCLUDE
#include <include/link_api/issCaptureLink.h>
#endif
#ifdef ISS_INCLUDE
#ifndef RADAR_ONLY
#include <include/link_api/issM2mIspLink.h>
#include <include/link_api/issM2mSimcopLink.h>
#endif
#include <src/rtos/utils_common/include/utils_iss.h>
#endif
#include <src/rtos/utils_common/include/file_api.h>
#include <src/rtos/utils_common/include/utils_tsk.h>
#include <src/rtos/utils_common/include/utils_emif_ecc.h>
#include <include/link_api/systemLink_ipu1_0_params.h>
#include <src/rtos/links_common/system/system_priv_common.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/vps_capture.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_videoDecoder.h>
#include <ti/drv/vps/include/devices/bsp_videoSensor.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/vps_display.h>
#include <ti/drv/vps/include/vps_displayCtrl.h>
#include <ti/drv/vps/include/dss/vps_cfgDss.h>
#include <ti/drv/vps/include/dss/vps_displayDss.h>
#include <ti/drv/vps/include/vps_control.h>
#ifdef VPE_INCLUDE
#include <ti/drv/vps/include/vpe/vps_m2mVpe.h>
#include <include/link_api/vpeLink.h>
#endif
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/bsp_lld/i2c/bsp_i2c.h>
#include <src/rtos/utils_common/include/utils_stat_collector.h>
#ifdef AVB_INCLUDE
#include <include/link_api/avbRxLink.h>
#include <include/link_api/avbTxLink.h>
#endif
#include <ti/drv/vps/include/dss/vps_captureDssWb.h>
#include <include/link_api/tfdtpRxLink.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Structure to hold the IPU1_0 specific data structures
 *
 *******************************************************************************
*/
typedef struct {

    /* Place holder for IPUMM Task Handle */
    BspOsal_TaskHandle tsk_handle_ipumm;

    UInt32 reserved;

} System_Ipu1_0_Obj;

extern System_Ipu1_0_Obj gSystem_objIpu1_0;

UInt32 System_getVpdmaPhysAddr(void);
Int32 IPU_primary_core_init (void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*SYSTEM_PRIV_IPU1_0_H_*/

/* @} */
