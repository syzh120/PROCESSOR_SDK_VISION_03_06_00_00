/*
 *  Copyright (C) 2017 - 2018 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     dcan_loopback_app.h
 *
 *  \brief    This file contains prototypes and definitions for DCAN test
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include <string.h>
#if defined (SOC_AM572x) || defined (SOC_AM574x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/osal/RegisterIntr.h>
#endif
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_dcan.h>
#include <ti/csl/arch/csl_arch.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/** \brief DCAN bit time calculation maximum error value. */
#define DCAN_APP_CALC_MAX_ERROR         (50U)

/** \brief Macro used to extract bit rate prescaler value. */
#define DCAN_APP_EXTRACT_BRPE_VAL       (0x3C0U)

/** \brief Shift value used for bit rate prescaler. */
#define DCAN_APP_BRPE_SHIFT             (6U)

/** \brief DCAN input clock - 20MHz */
#define DCAN_APP_INPUT_CLK              (20000000U)
/** \brief DCAN output bit rate - 1MHz */
#define DCAN_APP_BIT_RATE               (1000000U)

/** \brief DCAN TX message object used */
#define DCAN_TX_MSG_OBJ                 (0x1U)
/** \brief DCAN RX message object used */
#define DCAN_RX_MSG_OBJ                 (0x9U)

/** \brief DCAN TX interface register used */
#define DCAN_APP_TX_IF_REG              (DCAN_IF_REG_NUM_1)
/** \brief DCAN RX interface register used */
#define DCAN_APP_RX_IF_REG              (DCAN_IF_REG_NUM_2)

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
/** \brief DRM SUSPEND Source as C66 */
#define DRM_SUSPEND_SRC_C66_C0         (0x0)

/** \brief DCAN Message Object */
#define DCAN_MSG_OBJ                    (0x1)

#define DCAN_EXT_LOOPBACK_TEST      ('1')
#define DCAN_INT_LOOPBACK_TEST      ('2')
#define DCAN_PARITY_ECC_TEST        ('3')
#define EXIT(opt)                   (('x' == opt) || ('X' == opt))

#if (defined (SOC_AM572x)) || (defined (SOC_AM574x)) || (defined (SOC_AM571x))
/** \brief DCAN instance used */
#define DCAN1_APP_INST                   (CSL_MPU_DCAN1_REGS)
#define DCAN2_APP_INST                   (CSL_MPU_DCAN2_REGS)
#undef SOC_I_DRM_BASE
#define SOC_I_DRM_BASE CSL_MPU_I_DRM_REGS
#endif

#if defined (SOC_TDA3XX)
/** \brief DCAN Message Object used for ECC Test */
#define DCAN_NUM_MSG_OBJ                 (0x2)
#endif
#if defined (SOC_TDA2EX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
/** \brief DCAN Message Object used for PARITY Test */
#define DCAN_NUM_MSG_OBJ                 (0x1)
#endif

#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
#define DCAN1_APP_INST                   (SOC_DCAN1_BASE)
#define DCAN2_APP_INST                   (SOC_DCAN2_BASE)
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#define DCAN1_APP_INST                   (SOC_DCAN1_BASE)
#define DCAN2_APP_INST                   (SOC_DCAN2_BASE)
#endif

#if defined (SOC_TDA2EX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA3XX)
#if defined (__TI_ARM_V7M4__)
    #define APP_DCAN_INT                  (28U)
    #define XBAR_CPU                      (CSL_XBAR_IRQ_CPU_ID_IPU1)
    #define XBAR_INST                     (CSL_XBAR_INST_IPU1_IRQ_28)
#endif
#if defined (__ARM_ARCH_7A__)
    #define APP_DCAN_INT                  (77U)
    #define XBAR_CPU                      (CSL_XBAR_IRQ_CPU_ID_MPU)
    #define XBAR_INST                     (CSL_XBAR_INST_MPU_IRQ_77)
#endif
#endif

#ifdef RTOS_BUILD
#define PRINT_MSG UART_printf
#define SCAN_MSG  UART_scanFmt
#else
#define PRINT_MSG(STR)   UARTConfigPuts(uartBaseAddr, STR, -1)
#define PRINT_HEX(STR)   UARTConfigPutHexNum(uartBaseAddr, STR)
#define SCAN_MSG(VAL, STR) UARTConfigGets(uartBaseAddr, STR, 1)
#endif

/* ========================================================================== */
/*                         Global Variables                                   */
/* ========================================================================== */

extern uint32_t uartBaseAddr;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief    Enumerates the values used to represent the DCAN bit time
 *            calculation error values.
 */
typedef enum dcanBitTimeCalcErrType
{
    DCAN_BIT_RATE_ERR_MAX = 1,
    /**< Bitrate error maximum value */
    DCAN_BIT_RATE_ERR_WARN = 2,
    /**< Bitrate error warning value */
    DCAN_BIT_RATE_ERR_NONE = 3
                             /**< No bit rate error */
} dcanBitTimeCalcErrType_t;

/** \brief Structure holding Bit Time parameters for DCAN application. */
typedef struct dcanBitTimeParamsLocal
{
    uint32_t samplePnt;
    uint32_t timeQuanta;
    uint32_t propSeg;
    uint32_t phaseSeg1;
    uint32_t phaseSeg2;
    uint32_t syncJumpWidth;
    uint32_t bitRatePrescaler;
    uint32_t tseg1Min;
    uint32_t tseg1Max;
    uint32_t tseg2Min;
    uint32_t tseg2Max;
    uint32_t syncJumpWidthMax;
    uint32_t bitRatePrescalerMin;
    uint32_t bitRatePrescalerMax;
    uint32_t bitRatePrescalerInc;
    uint32_t bitRate;
} dcanBitTimeParamsLocal_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if defined (SOC_TDA2EX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA3XX)

/**
 * \brief   Configures the DCAN Parity Error interrupt to interrupt controller.
 *
 */
void DCANAppConfigParityIntr(void);

#endif

/**
 * \brief   This function retrieves Data from the message object and
 *          validates the received data
 *
 * \param   msgLstErrCnt        Received message is Valid or not
 *                              Valid values: TRUE or FALSE
 * \param   dataMissMatchErrCnt Data miss-match count
 * \param	buffIndex			Message Object Number to store the
 *								received data
 *
 * \return  STW_SOK             Receive Data Success
 * \return  STW_EFAIL           Receive Data Failed
 *
 **/
#ifdef RTOS_BUILD
uint32_t dcanReceiveData(uint32_t msgLstErrCnt, uint32_t dataMissMatchErrCnt, int16_t buffIndex);
#else
uint32_t dcanReceiveData(uint32_t msgLstErrCnt, uint32_t dataMissMatchErrCnt);
#endif

/**
 * \brief   This function executes the DCAN Loopback and
 *          DCAN ParityEcc Test functions
 *
 * \return  Returns STW_SOK on Success
 * \return  Returns Error Value on Failure
 *
 **/
int32_t execTest(void);

/**
 * \brief   This function displays the menu options and gets the user
 *          input to select DCAN instance1 or DCAN instance2
 *
 * \param   option  User option selected DCAN1 or DCAN2
 *
 */
void mainMenu(char *option);

/**
 * \brief   Board and UART configuration initialization function.
 *
 */
void padConfig_prcmEnable(void);

/**
 * \brief   DCAN Loopback Test Function
 *
 * \return  STW_SOK    DCAN Loopback Test Success
 * \return  STW_EFAIL  DCAN Loopback Test Failed
 *
 **/
int32_t dcanLoopbackTest(void);

/**
 * \brief   Clock configuration and Pin muxing function
 *          for DCAN instance1
 *
 **/
void DCAN1Prcm_clck_ram(void);

/**
 * \brief   Clock configuration and Pin muxing function
 *          for DCAN instance2
 *
 **/
void DCAN2Prcm_clck_ram(void);

/**
 * \brief    DCAN IP configuration initialization function.
 *
 * \details  This function configures the DCAN controller with the user
 *           selected DCAN instance.
 *
 * \param    pDcanCfgPrms   Pointer to the DCAN configuration object.
 * \param    pDcanTxCfgPrms Pointer to the DCAN Tx configuration object.
 * \param    pDcanRxCfgPrms Pointer to the DCAN Rx configuration object.
 * \param    menuOption     Points to the User option
 *
 */
void DCANAppInitParams(dcanCfgParams_t       *pDcanCfgPrms,
                       dcanMsgObjCfgParams_t *pDcanTxCfgPrms,
                       dcanMsgObjCfgParams_t *pDcanRxCfgPrms,
                       dcanTxParams_t        *pDcanTxPrms,
					   char                  menuOption);

/**
 * \brief     This Function checks if DCAN IF Register is busy
 *
 * \param     baseAddr       Base Address of the DCAN module register
 * \param     ifRegNum       DCAN interface register number
 *                           For valid values refer enum #dcanIfRegNum_t
 *
 */
void DCANAppWaitForIfReg(uint32_t baseAddr, uint32_t ifRegNum);

/**
 * \brief   This function takes I/P Clk frequency, required bit-rate on the
 *          CAN bus and calculates the value to be programmed for DCAN BTR
 *          register. This API doesn't do the actual programming. This is
 *          intended to be used as a utility function. And the application
 *          should call the #DCANSetBitTime function to do the actual
 *          programming.
 *
 * \param   clkFreq        I/P clock frequency to DCAN controller in Hz.
 * \param   bitRate        Required bit-rate on the CAN bus in bits per second.
 * \param   pBitTimePrms   Pointer to params where the calculated register
 *                         fields are populated
 *
 * \return  Returns Bit Time calculation error
 *          For valid values refer enum #dcanBitTimeCalcErrType_t
 */
uint32_t DCANCalculateBitTimeParams(uint32_t             clkFreq,
                                    uint32_t             bitRate,
                                    dcanBitTimeParams_t *pBitTimePrms);

/********************************* End of file ******************************/
#ifdef __cplusplus
}
#endif
