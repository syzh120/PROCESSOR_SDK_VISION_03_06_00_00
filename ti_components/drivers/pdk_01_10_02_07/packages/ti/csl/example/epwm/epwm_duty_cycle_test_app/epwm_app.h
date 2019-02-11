/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
 *
 */

#ifndef EPWM_APP_H_
#define EPWM_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_epwm.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/* None */


/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Structure holding the EPWM configuration parameters. */
typedef struct CSL_EpwmAppPwmCfg
{
    CSL_EpwmTimebaseCfg_t       tbCfg;
    /**< Timebase Sub-module configuration data structure. */
    CSL_EpwmCounterCmpCfg_t     ccCfg;
    /**< Counter comparator values . */
    CSL_EpwmAqActionCfg_t       aqCfg;
    /**< Action Qualifier Sub-module configuration data structure. */
    CSL_EpwmDeadbandCfg_t       dbCfg;
    /**< Dead band Sub-module configuration data structure. */
    CSL_EpwmChopperCfg_t        chpCfg;
    /**< Chopper sub-module configuration data structure. */
    CSL_EpwmTripzoneCfg_t       tzCfg;
    /**< Trip-zone sub-module configuration data structure. */
    CSL_EpwmEtCfg_t             etCfg;
    /**< Event Trigger sub-module configuration data structure. */
    CSL_EpwmHighResolutionCfg_t hrCfg;
    /**< High Resolution sub-module configuration data structure. */
} CSL_EpwmAppPwmCfg_t;

/**< \brief Structure holding the EPWM object data structure. */
typedef struct CSL_EpwmAppPwmObj
{
    uint32_t                pwmCh;
    /**< EPWM channel [A or B]. */
    uint32_t                instAddr;
    /**< EPWM instance address. */
    uint32_t                funcClk;
    /**< Functional clock(in Hz) input to the PWMSS. */
    uint32_t                enableDeadband;
    /**< Enable dead band sub-module processing. */
    uint32_t                enableChopper;
    /**< Enable chopper sub-module processing. */
    uint32_t                enableTripZone;
    /**< Enable Trip zone processing. */
    uint32_t                enableEventTrigger;
    /**< Enable Event trigger. */
    uint32_t                enableHighResolution;
    /**< Enable High resolution pwm feature. */
    CSL_EpwmAppPwmCfg_t     pwmCfg;
    /**< EPWM configuration data structure. */
} CSL_EpwmAppPwmObj_t;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef EPWM_APP_H_ */
