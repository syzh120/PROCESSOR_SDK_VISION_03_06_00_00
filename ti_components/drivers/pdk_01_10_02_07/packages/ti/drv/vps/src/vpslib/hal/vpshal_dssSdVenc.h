/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file vpshal_dssSdVenc.h
 *
 *  \brief HAL Header file for SD-VENC
 *  This file exposes the HAL APIs of the SD-VENC module
 *
 */

#ifndef VPSHAL_SDVENC_H_
#define VPSHAL_SDVENC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/**
 *  VpsHal_dssSdVencInit
 *  \brief SDVENC HAL init function.
 *  This function should be called before calling any of SD-VENC HAL API's.
 *
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */

Int32 VpsHal_dssSdVencInit(void);

/**
 *  VpsHal_dssSdVencDeInit
 *  \brief SDVENC HAL Deinit function.
 *
 *  \return                success    0
 *                            failure    error value
 *
 */
Int32 VpsHal_dssSdVencDeInit(void);

/**
 *  VpsHal_dssSdVencConfigure
 *  \brief Configures SDVENC for a particular video standard
 *  This function will configure the SD-VENC for a particular video mode.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsHal_dssSdVencConfigure(UInt32 videoStandard);

/**
 *  VpsHal_dssGetDefAdvSdVencParams
 *  \brief Initialize the config object with default parameters.
 *  This function will initialize the Vps_DssDispcSdVencAdvConfig object with
 *  the default settings based on the config.videoStandard variable.
 *  The initialized object can be passed to the
 *  VpsHal_dssSetAdvSdVencParams function.
 *
 *  \param                  pointer to Vps_DssDispcSdVencAdvConfig structure
 *                          Vps_DssDispcSdVencAdvConfig->videoStandard
 *                          should be set to get proper default values
 *  \return                 success    0
 *                          failure    error value
 *
 */
Int32 VpsHal_dssGetDefAdvSdVencParams(Vps_DssDispcSdVencAdvConfig *config);

/**
 *  VpsHal_dssSetAdvSdVencParams
 *  \brief Configures SDVENC with the user passed configuration
 *  This function will configure the SD-VENC for user passed settings.
 *
 *  \param                  pointer to Vps_DssDispcSdVencAdvConfig structure
 *  \return                 success    0
 *                          failure    error value
 *
 */
Int32 VpsHal_dssSetAdvSdVencParams(const Vps_DssDispcSdVencAdvConfig *config);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSHAL_SDVENC_H_ */
