/*
 *   Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file bspdrv_ar12xxInternal.c
 *
 *  \brief This file defines the internal test functions.
 *
 */
#ifndef BSPDRV_AR12XX_INTERNAL_H
#define BSPDRV_AR12XX_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/*! \brief
* Radar Rf Internal configuration
*/
typedef struct rlRfInternalCfg
{
    uint16_t profileId;
    uint16_t reserved;
    uint32_t memAddr;
    uint32_t value;
}Bsp_ar12xxInternalCfg_t;

/*! \brief
* Radar Internal configuraiton
*/
typedef struct rlDevInternalCfg
{
    uint32_t memAddr;
    uint32_t value;
}Bsp_ar12xxDevInternalCfg_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t Bsp_ar12xxGetInternalConfig(uint8_t deviceMap, uint16_t profileId,
                                                          uint32_t memAddr, uint32_t* data);
int32_t Bsp_ar12xxSetInternalConfig(uint8_t deviceMap, uint16_t profileId,
                                                          uint32_t memAddr, uint32_t data);

int32_t Bsp_ar12xxDeviceSetInternalConf(uint8_t deviceMap,
                                uint32_t memAddr, uint32_t value);
int32_t Bsp_ar12xxDeviceGetInternalConf(uint8_t deviceMap,
                                uint32_t memAddr, uint32_t* value);

#ifdef __cplusplus
}
#endif

#endif

/*
 * END OF BSPDRV_AR12XX_INTERNAL_H FILE
 */


