/******************************************************************************
Copyright (c) 2017 Texas Instruments Incorporated

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

#ifndef _RADAR_PKDETECT_WORK_IF_H_
#define _RADAR_PKDETECT_WORK_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/system_work_queue_if.h>
#include <src/rtos/alg_plugins/common/include/alg_ivision.h>
#include <include/alg_fxns/radarPkDetect_if.h>
#include "ipeak_detection_ti.h"

#define RADAR_PKDETECT_WORK_FXN_ID           (0x0002U)

#define RADAR_PKDETECT_WORK_FXN_CMD_CREATE   (0U)
#define RADAR_PKDETECT_WORK_FXN_CMD_PROCESS  (1U)
#define RADAR_PKDETECT_WORK_FXN_CMD_DELETE   (2U)

typedef struct {

    PEAK_DETECTION_TI_CreateParams   pkDetcreateParams;

} RadarPkDetectWork_CreateInArgs;

typedef struct {

    Void*    pkDetAlghandle;

} RadarPkDetectWork_CreateOutArgs;


typedef struct {
    PEAK_DETECTION_TI_InArgs  inArgs;

    IVISION_InBufs            inBufs;
    IVISION_OutBufs           outBufs;

    IVISION_BufDesc           inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc          *inBufDescList[PEAK_DETECTION_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc           outBufDesc[PEAK_DETECTION_TI_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc          *outBufDescList[PEAK_DETECTION_TI_BUFDESC_OUT_TOTAL];
} RadarPkDetectWork_ProcessInAlgArgs;

typedef struct {

    Void*    pkDetAlghandle;

    RadarPkDetectWork_ProcessInAlgArgs inAlgArgs;

} RadarPkDetectWork_ProcessInArgs;

typedef struct {

    PEAK_DETECTION_TI_OutArgs outArgs;

} RadarPkDetectWork_ProcessOutArgs;

typedef struct {

    UInt32 numObjs;

    Void*    pkDetAlghandle;

} RadarPkDetectWork_DeleteInArgs;



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
