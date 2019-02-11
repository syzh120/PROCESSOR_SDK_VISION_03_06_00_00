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
 *  \file st_mcan.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the mcan UT applications.
 */

#ifndef ST_MCAN_H_
#define ST_MCAN_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_mcan.h>
#include <ti/csl/csl_mcan.h>
#include <ti/csl/csl_edma.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/* Application name string used in print statements. */
#define APP_NAME                        "STW_mcan"
#define TEST_ENABLE                     (TRUE)
#define TEST_DISABLE                    (FALSE)
#define PRINT_ENABLE                    (TRUE)
#define PRINT_DISABLE                   (FALSE)

/*      Default values      */
#if defined (SOC_TDA2PX)
/* For TDA2Px MCAN address is in bit band region. So use the virtual address. */
#define DEF_MCAN_MODULE                          (SOC_MCAN_BASE_VIRT)
#elif defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#define DEF_MCAN_MODULE                          (SOC_MCAN_BASE)
#endif

#define MAX_ARG_LEN                     (30)

/* Time-out value for AutoRun */
#define MCAN_APP_UART_TIMEOUT_MSEC              (20000U)

/* Time-out value for AutoRun */
#define MCAN_APP_32K_CNT_FREQ_KHZ               (32768U)
#define MCAN_THEOROTICAL_MAX                    (7430U)
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
 *  \brief mcan test type.
 */
typedef enum
{
    MCAN_TEST_TYPE_B2B  = 0x1U,
    MCAN_TEST_TYPE_INTERNAL_LOOBACK  = 0x2U,
    MCAN_TEST_TYPE_EXTERNAL_LOOBACK  = 0x4U
} st_mcanTestType;

/**
 *  \brief mcan configuration parameter structure.
 */
typedef struct
{
    MCAN_TxBufElement txElem;
    /**< tx Buffer elements/Tx message. */
    uint32_t storageId;
    /**< Storage Identifier- where message shall be stored:FIFO/Buffer
     *   Refer enum #MCAN_MemType
     */
    uint32_t bufferNum;
    /**< Buffer number where message is to be stored.
     *   Only valid if storageId is 'MCAN_MEM_TYPE_BUF'.
     */
    uint32_t rxMSGStorageId;
    /**< Storage Identifier- where received message shall be stored:FIFO/Buffer
     *   Refer enum #MCAN_MemType
     */
    uint32_t rxBuffNum;
    /**< Buffer/FIFO number where received message is to be stored. */
} st_mcanTxMSGParams_t;

/**
 *  \brief mcan configuration parameter structure.
 */
typedef struct
{
    uint32_t mcanTestType;
    /**< testType
     *   Refer to enum #st_mcanTestType
     */
    uint32_t txMSGInterationCnt;
    /**< tx number of messages to transmit. */
    uint32_t mcanModule;
    /**< mcan module base address. */
    MCAN_BitTimingParams *bitTimings;
    /**< mcan module bit timing parameters. */
    MCAN_InitParams *initParams;
    /**< mcan module initialization parameters. */
    MCAN_ConfigParams *configParams;
    /**< mcan module configuration parameters. */
    MCAN_MsgRAMConfigParams *ramConfig;
    /**< mcan module MSG RAM configuration parameters. */
    MCAN_ECCConfigParams *eccConfigParams;
    /**< mcan module ECC configuration parameters. */
    MCAN_ECCErrForceParams *eccFrcParams;
    /**< mcan module ECC Error Force parameters. */
    uint32_t txMsgNum;
    /**< tx message number. */
    uint32_t stdIdFiltNum;
    /**< standard ID message filter number. */
    uint32_t extIdFiltNum;
    /**< extended ID message filter number. */
    st_mcanTxMSGParams_t *txMsg;
    /**< tx Buffer elements/Tx message. */
    MCAN_StdMsgIDFilterElement *stdIDFilter;
    /**< standard message ID filters. */
    MCAN_ExtMsgIDFilterElement *extIDFilter;
    /**< extended message ID filters. */
    uint32_t intrEnable;
    /**< Interrupt Enable/Disable Mask. */
    uint32_t intrLineSelectMask;
    /**< Interrupt Line Select Mask. */
    uint32_t intrLine;
    /**< Interrupt Line Select. */
} st_mcanConfigParams_t;

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
    st_mcanConfigParams_t mcanConfigParams;
    /**< mcan configuration parameters Refer struct #st_mcanConfigParams_t. */
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
} st_mcanTestcaseParams_t;
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* None */

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
