/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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

/**
 *  \file st_esm.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the ESM UT applications.
 */

#ifndef STW_ESM_H_
#define STW_ESM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_esm.h>
#include <ti/csl/csl_esm.h>
#include <ti/csl/csl_edma.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/* Application name string used in print statements. */
#define APP_NAME                        "STW_ESM"
#define TEST_ENABLE                     (TRUE)
#define TEST_DISABLE                    (FALSE)
#define PRINT_ENABLE                    (TRUE)
#define PRINT_DISABLE                   (FALSE)

/*      Default values      */
#define DEF_ESM_MODULE                  ((uint32_t) SOC_ESM_BASE)
#define DEF_ESM_MODE                    ((uint32_t) ESM_OPERATION_MODE_NORMAL)
#define DEF_ESM_OUT_PIN                 ((uint32_t) 0U)
#define DEF_ESM_LTCPR                   ((uint32_t) 20U)

#define MAX_ARG_LEN                     (30)

/* Time-out value for AutoRun */
#define ESM_APP_UART_TIMEOUT_MSEC              (5000U)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
typedef enum
{
    IPU = 0,
    /**< Select IPU core0/core1 for execution */
    DSP1 = 1,
    /**< Select DSP 1 for execution */
    DSP2 = 2,
    /**< Select DSP 2 for execution */
    EVE = 3
          /**< Select EVE for execution */
}cpuID_t;

/**
 *  \brief Test types.
 */
typedef enum
{
    ST_TT_SANITY      = 0x01,
    ST_TT_REGRESSION  = 0x02,
    ST_TT_FULL        = 0x04,
    ST_TT_FUNCTIONAL  = 0x08,
    ST_TT_STRESS      = 0x10,
    ST_TT_NEGATIVE    = 0x20,
    ST_TT_PERFORMANCE = 0x40,
    ST_TT_MISC        = 0x80,
    ST_TT_API         = 0x100
} st_TestType;

/**
 *  \brief ESM indication path interrupt/esm_error pin.
 */
typedef enum
{
    ESM_OUT_ERROR_LOW_INTR  = 0x1U,
    ESM_OUT_ERROR_HIGH_INTR = 0x2U,
    ESM_OUT_ERROR_ERR_PIN   = 0x4U
} st_ESMOutError;

/**
 *  \brief ESM configuration parameter structure.
 */
typedef struct
{
    uint32_t esmModule;
    /**< ESM module instance. */
    uint32_t esmMode;
    /**< ESM operational mode. */
    uint32_t esmLTCPR;
    /**< Low Time Counter Pre-load value.*/
    uint32_t esmChannels[112][2];
    /**< Channels to monitor.
     *   First element indicates number of channels to be enabled for monitoring
     *   From second till last channel number to enable.
     *   2nd column represents error indication path for that channel
     */
    uint32_t numOfIntr;
    /**< How many interrupt will occur during this test.*/
} stw_ESMConfigParams_t;

/**
 *  \brief Test case parameter structure.
 */
typedef struct
{
    Bool                  enableTest;
    /**< Whether test case should be executed or not. */
    uint32_t              testcaseId;
    /**< Test case ID. */
    char                 *reqId;
    /**< Requirements covered by this test case. */
    char                 *testCaseName;
    /**< Test case name. */
    char                 *userInfo;
    /**< Test case user Info. */
    char                 *disableReason;
    /**< Reason string for disabling a test case. */
    char                 *passFailCriteria;
    /**< Test case pass/fail criteria. */
    cpuID_t               cpuID;
    /**< Specify core on which test case is running. */
    stw_ESMConfigParams_t esmConfigParams;
    /**< ESM configuration parameters Refer struct #stw_ESMConfigParams_t. */
    Bool                  printEnable;
    /**< Enable/disable print statements, used for stress testing. */
    uint32_t              testType;
    /**< Type of test  - like BFT, stress etc... */

    /*
     * Below variables are initialized in code and not in table!!
     */
    int32_t               isRun;
    /**< Flag to indicate whether the test case is run or not. */
    Int32                 testResult;
    /**< Test result. */
} st_ESMTestcaseParams_t;
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* None */

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
