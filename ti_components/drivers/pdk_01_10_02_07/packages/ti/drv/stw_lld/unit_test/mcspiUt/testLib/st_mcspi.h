/*
 *  Copyright (C) 2016 Texas Instruments Incorporated
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
 *  \file st_mcspi.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the McSPI UT applications.
 */

#ifndef STW_MCSPI_H_
#define STW_MCSPI_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_mcspi.h>
#include <ti/csl/csl_mcspi.h>
#include <ti/csl/csl_edma.h>
#include <ti/diag/diagLib_mcspi.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/* Application name string used in print statements. */
#define APP_NAME                        "STW_MCSPI"
#define TEST_ENABLE                     (TRUE)
#define TEST_DISABLE                    (FALSE)
#define PRINT_ENABLE                    (TRUE)
#define PRINT_DISABLE                   (FALSE)

/*      Default values      */
#define DEF_MCSPI_MODULE                  ((uint32_t) SOC_MCSPI1_BASE)
#define DEF_MCSPI_CHANNEL                    ((uint32_t) \
                                         MCSPI_CHANNEL_0)

#define MAX_ARG_LEN                     (30)
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

/* Forward Declarations */
typedef struct st_MCSPITestcaseParams st_MCSPITestcaseParams_t;

/**
 * \brief Typedef for test case type function pointer.
 */
typedef void (*mcspiTestCaseFxnPtr)(st_MCSPITestcaseParams_t *testPrms);

/**
 *  \brief Test case parameter structure.
 */
struct st_MCSPITestcaseParams
{
    Bool                  enableTest;
    /**< Whether test case should be executed or not. */
    uint32_t              testcaseId;
    /**< Test case ID. */
    mcspiTestCaseFxnPtr testCaseFxnPtr;
    /**< Type of test case to run. */
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
    DiagLib_McspiTestParams_t diagLibTestParams;
    /**< Diaglib McSPI test parameters structure */
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
};
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * MCSPI Test Case Functions
 */
/**
 * \brief   Fetch testcase data and run the testcase.
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \return  None
 */
void DiagLibMcspiTest_main(st_MCSPITestcaseParams_t *testPrms);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
