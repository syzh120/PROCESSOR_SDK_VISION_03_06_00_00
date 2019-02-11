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
 *  \file st_qspi.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the QSPI UT applications.
 */

#ifndef STW_QSPI_H_
#define STW_QSPI_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/cslr_qspi.h>
#include <ti/csl/csl_qspi.h>
#include <ti/csl/csl_edma.h>
#include <ti/boot/sbl_auto/qspiflash/qspi_flash.h>
#include <ti/boot/sbl_auto/qspiflash/qspi_cmd_init.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

#define ST_INSTANCE_ID_QSPI1            (0x0)
#define ST_INSTANCE_NAME_QSPI1          "/qspi0"

/* Application name string used in print statements. */
#define APP_NAME                        "STW_QSPI_UT"
#define TEST_ENABLE                     (TRUE)
#define TEST_DISABLE                    (FALSE)
#define PRINT_ENABLE                    (TRUE)
#define PRINT_DISABLE                   (FALSE)
#define MEM_MAP_MODE_ENABLE             (TRUE)
#define MEM_MAP_MODE_DISABLE            (FALSE)

/* Default values */
#define ST_QSPI_USE_DEF                 (0xFAFAU)
#define DEF_LOOP_CNT                    (1U)
/* DEF_FLASH_SIZE: ST_QSPI_FLASH_BLOCK_SIZE is in words*/
#define DEF_FLASH_SIZE                  (16U * 1024U)

#define ST_QSPI_PRINT_BUFSIZE           (4000U)

/** \brief RX/TX buffer size for allocation in words */
#define RX_TX_BUF_SIZE_WORD             (10000U)

/** \brief Default RX/TX transfer length in words */
#define ST_QSPI_RX_TX_LENGTH            (RX_TX_BUF_SIZE_WORD)

#define ST_QSPI_FLASH_BLOCK_SIZE        (64U * 1024U)
/* ST_QSPI_READ_LENGTH: ST_QSPI_FLASH_BLOCK_SIZE is in words*/
#define ST_QSPI_READ_LENGTH             (16U * 1024U)
#define ST_QSPI_FLASH_SIZE              (32U * 1024U * 1024U)  /* 32MB */
#define ST_QSPI_FLASH_PAGE_SIZE         (256U)

#define ST_QSPI_FLASH_DEFAULT_SIZE      (1U * 1024U)

#define ST_QSPI_CLKSRC_QSPI_CLK        (0U)
#define ST_QSPI_CLKSRC_128M_CLK        (1U)

#define DEF_QSPI_MODULE                ((uint32_t) SOC_QSPI_ADDRSP0_BASE)
#define DEF_QSPI_CHANNEL               ((uint32_t) QSPI_CHANNEL_0)
#define DEF_DATA_WIDTH                 ((uint32_t) 32U)
#define DEF_ERASE_BLOCK_NO             ((uint32_t) 0U)
#define DEF_ERASE_SECTOR_NO            ((uint32_t) 0U)
#define DEF_OFFSET_ADDR                ((uint32_t) 0U)

#define DEF_CLK_FREQUENCY              ((uint32_t) QSPI_SCLK_FREQ_12MHz)
#define DEF_CLK_MODE                   ((uint32_t) ST_QSPI_CLK_MODE_0)
#define DEF_DATA_TRANSFER_MODE         ((uint32_t) ST_QSPI_POLLED_MODE)
/* Smart Idle Mode*/
#define DEF_IDLE_MODE                   ((uint32_t) 2U)
#define DEF_CHIP_SELECT                 ((uint32_t) 0U)

#define MAX_ARG_LEN                     (30)

#define APP_QSPI_INT_M4                 (34U)
#define XBAR_CPU                        (CPU_IPU1)
#define XBAR_INST                       (XBAR_INST_IPU1_IRQ_34)
#define XBAR_INTR_SOURCE                (QSPI_IRQ)

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


typedef enum
{
    ST_QSPI_TEST_TYPE_QUICK,
    ST_QSPI_TEST_TYPE_EXTENDED
} st_QspiTestType;

typedef enum
{
    ST_QSPI_BLOCK_ERASE,
    ST_QSPI_SECTOR_ERASE,
    ST_QSPI_FULL_ERASE
} st_QspiEraseType;

typedef enum
{
    ST_QSPI_CLK_MODE_0,
    ST_QSPI_CLK_MODE_1,
    ST_QSPI_CLK_MODE_2,
    ST_QSPI_CLK_MODE_3
} st_QspiClockMode;

typedef enum
{
    ST_QSPI_POLLED_MODE,
    ST_QSPI_INTERRUPT_MODE,
    ST_QSPI_DMA_MODE
} st_QspiDataTransferMode;

typedef enum
{
    ST_QSPI_FLASH_IDCMD_CFGID_DEFAULT,

    ST_QSPI_FLASH_RDCMD_CFGID_DEFAULT,
    ST_QSPI_FLASH_RDCMD_CFGID_QREAD,
    ST_QSPI_FLASH_RDCMD_CFGID_FASTREAD,
    ST_QSPI_FLASH_RDCMD_CFGID_DREAD,

    ST_QSPI_FLASH_WRCMD_CFGID_DEFAULT,

    ST_QSPI_FLASH_SECTERASECMD_CFGID_DEFAULT,

    ST_QSPI_FLASH_SUBSECTERASECMD_CFGID_DEFAULT,

    ST_QSPI_FLASH_FULLERASECMD_CFGID_DEFAULT,

    ST_QSPI_FLASH_STATCMD_CFGID_DEFAULT,

    ST_QSPI_FLASH_WRENCMD_CFGID_DEFAULT,
} st_QspiFlashCmdCfgId;


/* Forward declaration. */
typedef struct st_SystemCtrl_t st_SystemCtrl;

/**
 *  \brief QSPI flash command Test configuration parameters
 */
typedef struct
{
    st_QspiFlashCmdCfgId     cfgId;
    /**< Flash Command Configuration ID */
    QSPI_FlashCmd_t      cmd;
    /**< Flash Command */
}st_QSPIFlashCmdCfg;

/**
 *  \brief QSPI Module Test parameters configuration structure
 */
typedef struct
{
    uint32_t    flashTestType;
    /**< Flash test type : For valid values refer enum #st_QspiTestType */
    uint32_t    flashType;
    /**< Device type : For valid values refer enum #qspi_DeviceType_e */
    uint32_t    eraseType;
    /**< Erase type : For valid values refer enum #st_QspiEraseType */
    uint32_t    eraseBlockNo;
    /**< Erase Block Number. Valid in case of Block Erase */
    uint32_t    eraseSectorNo;
    /**< Erase Sector Number. Valid in case of Sector Erase */
    uint32_t    flashSize;
    /**< Size of the flash in terms of bytes to be tested
     *   Valid only in case of Quick flash test
     */
    uint32_t    offsetAddr;
    /**< Flash offset Address. Valid only in case of Quick flash test*/
    Bool       enableReadMemMapMode;
    /**< Enable memory mapped mode for read */
    uint32_t    dataWidth;
    /**< Write/Read data width - 8, 16, 32, 64, 128 */
    uint32_t    clockFrequency;
    /**< clockFrequency:For valid values refer enum #qspi_ClockFreq_e  */
    uint32_t    clockMode;
    /**< clockMode :For valid values refer enum #st_QspiClockMode  */
    uint32_t    dataTransferMode;
    /**< dataTransferMode :For valid values refer enum #st_QspiDataTransferMode  */
    uint32_t    numDataLines;
    /**< Number of Data Lines Used */
    uint32_t    enableWcInt;
    /**< Enable Word Complete Interrupt */
    uint32_t    enableFcInt;
    /**< Enable Frame Complete Interrupt */
    st_QSPIFlashCmdCfg      idCmdCfg;
    /**< Flash ID Command */
    st_QSPIFlashCmdCfg      rdCmdCfg;
    /**< Flash Read Command */
    st_QSPIFlashCmdCfg      wrCmdCfg;
    /**< Flash Write Command */
    st_QSPIFlashCmdCfg      sectEraseCmdCfg;
    /**< Flash sectorErase Command */
    st_QSPIFlashCmdCfg      subSectEraseCmdCfg;
    /**< Flash  subSectorErase Command */
    st_QSPIFlashCmdCfg      fullEraseCmdCfg;
    /**< Flash fullErase Command */
    st_QSPIFlashCmdCfg      statCmdCfg;
    /**< Flash Status Command */
    st_QSPIFlashCmdCfg      wrEnCmdCfg;
    /**< Flash writeEnable Command */
} st_QspiTestCfgPrms;

/* Forward Declarations */
typedef struct st_QSPITestcaseParams st_QSPITestcaseParams_t;

/**
 * \brief Typedef for test case type function pointer.
 */
typedef void (*qspiTestCaseFxnPtr)(st_QSPITestcaseParams_t *testPrms);

/**
 *  \brief Test case parameter structure.
 */
struct st_QSPITestcaseParams
{
    Bool                  enableTest;
    /**< Whether test case should be executed or not. */
    uint32_t              testcaseId;
    /**< Test case ID. */
    qspiTestCaseFxnPtr testCaseFxnPtr;
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
    Bool                  printEnable;
    /**< Enable/disable print statements, used for stress testing. */
    uint32_t              testType;
    /**< Type of test  - like BFT, stress etc... */
    uint32_t              loopCnt;
    /**< Loop count for test. */
    st_QspiTestCfgPrms    testCfg;
    /**< QSPI Test Configuration Parameters */

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
 * QSPI Test Case Functions
 */
void st_qspiTest_quickFlash(st_QSPITestcaseParams_t *testPrms);
void st_qspiTest_fullFlash(st_QSPITestcaseParams_t *testPrms);
Int32 st_qspiEnableQspiInstance();
void st_qspiTest_fullFlash_Test(st_QSPITestcaseParams_t *testPrms);
void st_qspiTest_GetMemMapCfg(st_QSPITestcaseParams_t *testPrms);
void st_qspiTest_writeCfgMode(uint32_t dstOffsetAddr,
                              uint32_t srcAddr,
                              uint32_t length);
void st_qspiTest_readCfgMode(uint32_t dstAddr,
                             uint32_t srcOffsetAddr,
                             uint32_t length);

void st_qspiTest_quickFlash_Interrupt(st_QSPITestcaseParams_t *testPrms);
void st_qspiTest_WrNullDataCheck(st_QSPITestcaseParams_t *testPrms);
void st_qspiTest_RdNullDataCheck(st_QSPITestcaseParams_t *testPrms);
void st_qspiTest_RdCorruptionCheckFor16BitData(st_QSPITestcaseParams_t *testPrms);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif

