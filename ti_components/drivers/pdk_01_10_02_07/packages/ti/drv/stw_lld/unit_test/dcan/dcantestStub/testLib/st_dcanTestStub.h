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
 *  \file st_dcanTestStub.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the DCAN Test Stub applications.
 */

#ifndef STW_DCAN_TEST_STUB_H_
#define STW_DCAN_TEST_STUB_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_dcan.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/* Application name string used in print statements. */
#define APP_NAME                        "STW_DCAN"
#define TEST_ENABLE                     (TRUE)
#define TEST_DISABLE                    (FALSE)
#define PRINT_ENABLE                    (TRUE)
#define PRINT_DISABLE                   (FALSE)

#define PARITY_ENABLE                   (TRUE)
#define PARITY_DISABLE                  (FALSE)
#define ECC_MODE_ENABLE                 (TRUE)
#define ECC_MODE_DISABLE                (FALSE)
#define ECC_DIAG_MODE_ENABLE            (TRUE)
#define ECC_DIAG_MODE_DISABLE           (FALSE)
#define SBE_EVENT_ENABLE                (TRUE)
#define SBE_EVENT_DISABLE               (FALSE)
#define INTR_LINE_0_ENABLE              (TRUE)
#define INTR_LINE_0_DISABLE             (FALSE)
#define INTR_LINE_1_ENABLE              (TRUE)
#define INTR_LINE_1_DISABLE             (FALSE)
#define STAT_CHG_INT_ENABLE             (TRUE)
#define STAT_CHG_INT_DISABLE            (FALSE)
#define ERR_INT_ENABLE                  (TRUE)
#define ERR_INT_DISABLE                 (FALSE)
#define IF1_DMA_ENABLE                  (TRUE)
#define IF1_DMA_DISABLE                 (FALSE)
#define IF2_DMA_ENABLE                  (TRUE)
#define IF2_DMA_DISABLE                 (FALSE)
#define IF3_DMA_ENABLE                  (TRUE)
#define IF3_DMA_DISABLE                 (FALSE)

#define AUTO_RETX_ENABLE                (TRUE)
#define AUTO_RETX_DISABLE               (FALSE)
#define AUTO_BUS_ON_ENABLE              (TRUE)
#define AUTO_BUS_ON_DISABLE             (FALSE)
#define TEST_MODE_ENABLE                (TRUE)
#define TEST_MODE_DISABLE               (FALSE)
#define RAM_ACCESS_ENABLE               (TRUE)
#define RAM_ACCESS_DISABLE              (FALSE)
#define MSG_VALID                       (TRUE)
#define MSG_INVALID                     (FALSE)
#define EXT_FRAME                       (TRUE)
#define STD_FRAME                       (FALSE)
#define UMASK_ENABLE                    (TRUE)
#define UMASK_DISABLE                   (FALSE)
#define INT_ENABLE                      (TRUE)
#define INT_DISABLE                     (FALSE)
#define RMT_ENABLE                      (TRUE)
#define RMT_DISABLE                     (FALSE)
#define FIFO_EOB_ENABLE                 (TRUE)
#define FIFO_EOB_DISABLE                (FALSE)

/*      Default values      */
#define DEF_DATA_SIZE                   ((uint32_t) 8U)
#define DEF_MSG_LOST_STAT               (FALSE)
#define DEF_FRAME_TYPE                  (DCAN_DATA_FRAME)

/** \brief DCAN1 instance */
#define DCAN1_APP_INST                   (SOC_DCAN1_BASE)
#define DCAN2_APP_INST                   (SOC_DCAN2_BASE)

#define MAX_ARG_LEN                     (30)

/** \brief Offset of DRM SUSPEND_CTRL1 register */
#define DRM_SUSPEND_CTRL1               (0x204)
/** \brief DRM_SUSPEND_CTRL1 is mapped to DCAN1 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN1          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL1)

/** \brief Offset of DRM SUSPEND_CTRL2 register */
#define DRM_SUSPEND_CTRL2               (0x208)
/** \brief DRM_SUSPEND_CTRL2 is mapped to DCAN2 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN2          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL2)

/** \brief DRM SUSPEND Source as A15 */
#define DRM_SUSPEND_SRC_MPU_C0          (0x5)
/** \brief DRM SUSPEND Source as M4 */
#define DRM_SUSPEND_SRC_IPU1_C0         (0x3)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

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
 *  \brief Test case type.
 */
typedef enum
{
    ST_TCT_DCAN_TX = 0x01,
    ST_TCT_DCAN_RX = 0x02
} st_TestCaseType;

/* ========================================================================== */
/*                          Structure Declarations
 *                            */
/* ========================================================================== */

/**
 *  \brief Test case parameter structure.
 */
typedef struct
{
    int32_t               testcaseId;
    /**< Test case ID. */
    uint32_t              clkFreq;
    /**< DCAN I/P clock frequency */
    uint32_t              bitrate;
    /**< DCAN Bit rate */
    uint32_t              refSamplePoint;
    /**< Dcan Reference Sample point in terms of %*/
    uint32_t              propDelay;
    /**< DCAN Propagation Delay in terms of ns */
    uint32_t              dcanAppMsgObj;
    /**< DCAN MessageObject */
    dcanCfgParams_t       dcanCfgPrms;
    /**< DCAN configuration params */
    dcanMsgObjCfgParams_t dcanTxCfgPrms;
    /**< DCAN TX configuration params */
    dcanMsgObjCfgParams_t dcanRxCfgPrms;
    /**< DCAN RX configuration params */
    dcanTxParams_t        dcanTxPrms;
    /**< DCAN Transfer params */
    dcanRxParams_t        dcanRxPrms;
    /**< DCAN RX params */
    Bool                  printEnable;
    /**< Enable/disable print statements, used for stress testing. */
    uint32_t              testType;
    /**< Type of test  - like BFT, stress etc... */
    uint32_t              numMsg;
} st_DCANTestcaseParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void st_dcanAppTestStubConfigIntr(st_DCANTestcaseParams_t *testParams);
uint32_t st_dcanAppTestStubCalculateBitTimeParams(
    uint32_t             clkFreq,
    uint32_t             bitRate,
    uint32_t             refSamplePnt,
    uint32_t             propDelay,
    dcanBitTimeParams_t *pBitTimePrms);
void st_dcanAppTestStubWaitForIfReg(uint32_t baseAddr, uint32_t ifRegNum);
/**
 * \brief   Parse the testcase data
 *
 * \param   None.
 *
 * \return  None
 */
int32_t st_dcanTestStubParser(void);
void sampleDelay(int32_t delay);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
