/*
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/** ============================================================================
 *  @file       prcm\V1\PowerDevice.h
 *
 *  @brief      Power manager interface for the following devices:
 *                  SOC_TDA2EX
 *                  SOC_AM571X
 *
 *  The Power header file should be included in an application as follows:
 *  @code
 *  #include <ti/drv/pm/Power.h>
 *  #include <ti/drv/pm/PowerExtended.h>
 *  #include <ti/drv/pm/PowerDevice.h>
 *  @endcode
 *
 *  Refer to @ref Power.h and @ref PowerExtended.h for a complete description
 *  of APIs.
 *
 *  ============================================================================
 */

#ifndef POWERDEVICE_H_
#define POWERDEVICE_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include <stdint.h>
#include <ti/osal/HwiP.h>
#include <ti/drv/pm/PowerExtended.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/*!< device-specific power capabilities:
 *       0 - not supported on device
 *       1 - supported on device */
#define PowerDevice_CAPABILITY_Thermal        (1U)

/*!< base value for device-specific error return codes */
#define PowerDevice_EBASE                     (2048U)
/*!< invalid thermal set point index */
#define Power_EINVALID_SET_POINT_INDEX        (PowerDevice_EBASE + 0U)
/*!< API unimplemented */
#define Power_EUNIMPLEMENTED                  (PowerDevice_EBASE + 1U)

#if defined (__TI_ARM_V7M4__)
/* latency times in microseconds for M4 */
#define PowerDevice_RESUMETIMESLEEP           (182U)
#define PowerDevice_TOTALTIMESLEEP            (335U)
#define PowerDevice_RESUMETIMEDEEPSLEEP       (183U)
#define PowerDevice_TOTALTIMEDEEPSLEEP        (337U)
#elif defined (__ARM_ARCH_7A__)
/* latency times in microseconds for A15 */
#define PowerDevice_RESUMETIMESLEEP           (154U)
#define PowerDevice_TOTALTIMESLEEP            (320U)
#define PowerDevice_RESUMETIMEDEEPSLEEP       (156U)
#define PowerDevice_TOTALTIMEDEEPSLEEP        (324U)
#elif defined (_TMS320C6X)
/* latency times in microseconds for DSP */
#define PowerDevice_RESUMETIMESLEEP           (182U)
#define PowerDevice_TOTALTIMESLEEP            (339U)
#define PowerDevice_RESUMETIMEDEEPSLEEP       (183U)
#define PowerDevice_TOTALTIMEDEEPSLEEP        (354U)
#endif

#if defined (__ARM_ARCH_7A__)
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x)
#define PowerDevice_FREQ_OPP_LOW              (0U)
#define PowerDevice_FREQ_OPP_NOM              (800000000U)
#define PowerDevice_FREQ_OPP_OD               (800000000U)
#define PowerDevice_FREQ_OPP_HIGH             (800000000U)
#endif
#if defined (SOC_AM571x)
#define PowerDevice_FREQ_OPP_LOW              (0U)
#define PowerDevice_FREQ_OPP_NOM              (1000000000U)
#define PowerDevice_FREQ_OPP_OD               (1176000000U)
#define PowerDevice_FREQ_OPP_HIGH             (1500000000U)
#endif
#endif

/* Power events - Device specific.  Base events from PowerExtended.h */
#define PowerDevice_THERMAL_LOW               (1024U)
#define PowerDevice_THERMAL_HIGH              (2048U)

#define PowerDevice_NUMEVENTS                 (Power_NUMEVENTS + 2U)
#define PowerDevice_EVENT_ALL                 (4095U)

/* Thermal set points indices */
#define PowerDevice_SET_POINT_IDX_LOW_MPU     (0U)
#define PowerDevice_SET_POINT_IDX_HIGH_MPU    (1U)
#define PowerDevice_SET_POINT_IDX_LOW_CORE    (2U)
#define PowerDevice_SET_POINT_IDX_HIGH_CORE   (3U)
#define PowerDevice_SET_POINT_IDX_LOW_IVA     (4U)
#define PowerDevice_SET_POINT_IDX_HIGH_IVA    (5U)
#define PowerDevice_SET_POINT_IDX_LOW_DSPEVE  (6U)
#define PowerDevice_SET_POINT_IDX_HIGH_DSPEVE (7U)
#define PowerDevice_SET_POINT_IDX_LOW_GPU     (8U)
#define PowerDevice_SET_POINT_IDX_HIGH_GPU    (9U)

#define PowerDevice_NUMSETPOINTS              (10U)

#define PowerDevice_SET_POINT_MIN_TEMP        (-40)
#define PowerDevice_SET_POINT_MAX_TEMP        (125)

#define PowerDevice_DSP_SYS_HWINFO            (SOC_DSP_SYSTEM_BASE + DSP_HWINFO)

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/*! @brief  Device thermal management configuration */
typedef struct PowerDevice_ThermalCfg {
    bool         cfgThermalAlert;  /* enables configuration of thermal
                                    * interrupt */
    unsigned int alertIntPriority; /* thermal alert interrupt priority */
    unsigned int eventId;          /* processor event ID to tie to interrupt
                                    * (not used on ARM) */
    unsigned int xbarCpuIrq;       /* chosen eventId's XBAR_INST index according
                                    * to cslr_interrupt.h */
    int          intNum;           /* processor interrupt number to tie to
                                    * eventId */
} PowerDevice_ThermalCfg_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* default policy init function for config structure */
void PowerDevice_policyInitFxn(void);

/* default policy deinit function for config structure */
void PowerDevice_policyDeinitFxn(void);

/* default power policy function for config structure */
void PowerDevice_policyFxn(void);

#ifdef __cplusplus
}
#endif

#endif /* POWERDEVICE_H_ */
