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
 *
 * \ingroup ULTRASONIC_CAPTURE_LINK_API
 * \defgroup ULTRASONIC_CAPTURE_LINK_IMPL UltrasonicCapture Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file ultrasonicCaptureLink_priv.h UltrasonicCapture Link private API/Data structures
 *
 *******************************************************************************
 */

#ifndef _ULTRASONIC_CAPTURE_LINK_PRIV_H_
#define _ULTRASONIC_CAPTURE_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/ultrasonicCaptureLink.h>
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <ti/drv/vps/include/devices/bsp_pga450.h>
#include <ti/drv/vps/include/devices/bsp_pga460.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Maximum frmaes an output queue can support
 *
 *******************************************************************************
 */
#define ULTRASONIC_CAPTURE_LINK_MAX_OUT_BUFFERS     (1)

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 * \brief Structure to hold all UltrasonicCapture link related information
 *
 *******************************************************************************
 */
typedef struct {
    UInt32 tskId;
    /**< Placeholder to store ultrasonicCapture link task id */

    Utils_TskHndl tsk;
    /**< Handle to capture link task */

    UltrasonicCaptureLink_CreateParams createArgs;
    /**< Create params for ultrasonicCapture link */

    System_LinkInfo info;
    /**< Output queue information of this link */

    Bool deviceIsDetected[BSP_PGA450_MAX_DEVICE+1];
    /**< TRUE: Device is detected during create,
     *   FALSE: Device is not detected during create
     */

    Utils_BufHndl outFrameQue;
    /**< Handles to each of the output queues */

    System_Buffer
                sysBufs[ULTRASONIC_CAPTURE_LINK_MAX_OUT_BUFFERS];
    /**< Placeholder to store the incoming buffers */

    System_MetaDataBuffer
                metaBufs[ULTRASONIC_CAPTURE_LINK_MAX_OUT_BUFFERS];

} UltrasonicCaptureLink_Obj;


void UltrasonicCaptureLink_hwSetup();

Void UltrasonicCaptureLink_PGA450_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);
Void UltrasonicCaptureLink_PGA460_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


