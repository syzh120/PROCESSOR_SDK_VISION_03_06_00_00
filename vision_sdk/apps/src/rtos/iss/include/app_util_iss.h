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

/*
 *******************************************************************************
 *
 * \file iss_utils.h
 *
 * \brief This file contains utility functions for initializing ISS
 *        data structures.
 *
 *******************************************************************************
 */


#ifndef APP_UTIL_ISS_H_
#define APP_UTIL_ISS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/issCaptureLink.h>
#include <include/link_api/issM2mIspLink.h>
#include <include/link_api/issM2mSimcopLink.h>
#include <src/rtos/iss/include/algorithmLink_issAewb.h>
#include <src/rtos/iss/include/iss_sensors.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define ISSUTILS_UB960EVM_MAX_PORTS     (0x4U)
/**< Number of receive ports supported */

#define ISSUTILS_UB960_MAX_INSTANCE     (0x2U)
/**< Number of maximum csi2 instances supported */

#define ISSUTILS_UB960EVM_NO_SOURCE_DETECTED     (0xFFFFFFFFU)
/**< Identifier to indicate no source detected at a given port */
#define DESERIALIZER_INST0_MAX_OUT_CHANNEL   (4)
#define DESERIALIZER_INST1_MAX_OUT_CHANNEL   (2)


/*******************************************************************************
 *  Structure declaration
 *******************************************************************************
 */

/*  \brief Structure used for describing sensor interfacing.
 *
 */
typedef struct
{
    /*< To store sensor handle created */
    char                            sensorName[ISS_SENSORS_MAX_NAME];
    IssM2mIspLink_OperatingMode     ispOpMode;
    IssM2mSimcopLink_OperatingMode  simcopOpMode;
    UInt32                          numCh;
    UInt32                          numCSI2Inst; /* number of csi2 instances used */
} AppUtils_Obj;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 * \brief   Sensor Creation
 *
 *******************************************************************************
*/
Void appCreateISSSensor(AppUtils_Obj *pObj);

Void appStartISSSensor(AppUtils_Obj *pObj,UInt32 numCh);

Void appStartIssSensorSerDes(AppUtils_Obj *pObj);

Void appStopISSSensor(AppUtils_Obj *pObj);

Void appDeleteISSSensor(AppUtils_Obj *pObj);

Void appGetUB96xRegVal(AppUtils_Obj *pObj);


Void appInitIssCaptParams(AppUtils_Obj *pObj, UInt32 issCaptLinkId,
    IssCaptureLink_CreateParams *pCapturePrm);
Void appInitIssIspParams(AppUtils_Obj *pObj, UInt32 issIspLinkId,
    IssM2mIspLink_CreateParams *pPrm);
Void appInitIssSimcopParams(AppUtils_Obj *pObj, UInt32 issSimcopLinkId,
    IssM2mSimcopLink_CreateParams *pPrm);
Void appInitIssAewbParams(AppUtils_Obj *pObj, UInt32 issAewbLinkId,
    AlgorithmLink_IssAewbCreateParams *pPrm);
Void appSetDefaultIspParams(AppUtils_Obj *pObj);
Void appSetIspParamsFromDCC(AppUtils_Obj *pObj);
Void appSetDefaultSimcopParams(void);
Void appDccParseAndSetIspParamsFromSensor(AppUtils_Obj *pObj);
Void appParserAndSetDccProfile(Ptr pDccCfg, UInt32 size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* end of APP_UTILS_H_ */

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */
