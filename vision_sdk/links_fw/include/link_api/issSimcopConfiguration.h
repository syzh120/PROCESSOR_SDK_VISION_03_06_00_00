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
 *   \ingroup FRAMEWORK_MODULE_API
 *   \defgroup ISSM2MSIMCOP_LINK_API ISS M2M SIMCOP (LDC+VTNF) Link API
 *
 *   ISS M2M SIMCOP Link is used for SIMCOP operations available in ISS
 *   This link operates in M2M mode (Input Data read from memory, operation by
 *   SIMCOP (LDC and VTNF) and Output Data written back to memory)
 *
 *   This link can be operated in three primary modes
 *   - LDC only: Lens Distortion correction
 *   - VTNF only: Temporal noise filter
 *   - LDC + VTNF only: Both LDC and VTNF are active
 *
 *   This link can operate on multiple channels.
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file issSimcopConfiguration.h
 *
 * \brief ISS Simcop Configuration link API public header file.
 *
 * \version 0.0 (Aug 2017) : [BJ] First version
 *
 *******************************************************************************
 */

#ifndef ISSCONFIGURATION_LINK_H_
#define ISSCONFIGURATION_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/systemLink_ipu1_0_params.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/include/iss/vps_cfgldc.h>
#include <ti/drv/vps/include/iss/vps_cfgvtnf.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
*/

typedef struct
{
    UInt32  chNum;
    /**< Channel ID for which these parameters are valid */

    /**< If the pointer is NULL: Indicates application is not interested
     *   in configuring or changing values.
     *   If the pointer is non-NULL:  Indicates application is providing new
     *   configuration.
     *   Note that, the structure (Memory) area pointed to these buffers are
     *   available for the link and they are not over-written,
     *   while the link is active.
     */

    vpsissldcConfig_t *ldcConfig;
    /**< Only Valid if
     *  IssM2mSimcopLink_CreateParams.channelParams
     *       [IssM2mSimcopLink_ConfigParams.chNum].operatingMode
     *           = ISSM2MSIMCOP_LINK_OPMODE_LDC
     *              or
     *             ISSM2MSIMCOP_LINK_OPMODE_LDC_VTNF
     *
     *  Following field in ldcConfig, need not be set by user
     *   and link implementation will over-ride user set values,
     *    vpsissldcConfig_t.isAdvCfgValid
     *    vpsissldcConfig_t.advCfg
     *    vpsissldcConfig_t.inputFrameWidth
     *    vpsissldcConfig_t.inputFrameHeight
     *
     *  Other fields in vpsissldcConfig_t MUST be set by user
     *
     */

    vpsissvtnfConfig_t *vtnfConfig;
    /**< Only Valid if
     *  IssM2mSimcopLink_CreateParams.channelParams
     *       [IssM2mSimcopLink_ConfigParams.chNum].operatingMode
     *           = ISSM2MSIMCOP_LINK_OPMODE_VTNF
     *              or
     *             ISSM2MSIMCOP_LINK_OPMODE_LDC_VTNF
     *
     *  Following fields in vtnfConfig, need not be set by user
     *   and link implementation will over-ride user set values,
     *    vpsissvtnfConfig_t.outDataFormat
     *    vpsissvtnfConfig_t.isAdvCfgValid
     *    vpsissvtnfConfig_t.advCfg.blockWidth
     *    vpsissvtnfConfig_t.advCfg.blockHeight
     *    vpsissvtnfConfig_t.advCfg.triggerSource
     *    vpsissvtnfConfig_t.advCfg.intrEnable
     *
     *  Below MUST be set by user,
     *   vpsissvtnfConfig_t.advCfg.roundBitCount
     *   vpsissvtnfConfig_t.advCfg.colorWeight1
     *   vpsissvtnfConfig_t.advCfg.colorWeight2
     *   vpsissvtnfConfig_t.advCfg.lut1[]
     *   vpsissvtnfConfig_t.advCfg.lut2[]
     */

} IssM2mSimcopLink_ConfigParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void IssM2mSimcopLink_ConfigParams_Init(
    IssM2mSimcopLink_ConfigParams *pPrm);

static inline void IssM2mSimcopLink_ConfigParams_Init(
    IssM2mSimcopLink_ConfigParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(IssM2mSimcopLink_ConfigParams));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
