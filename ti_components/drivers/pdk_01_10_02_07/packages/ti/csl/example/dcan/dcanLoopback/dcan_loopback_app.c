/*
 *  Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     dcan_loopback_app.c
 *
 *  \brief    This file contains core test of DCAN external loopback test mode
 *
 *  \details  DCAN external loopback which tests the internal feedback
 *            from Tx output to Rx input. Transmitted messages are treated as
 *            received messages and can be stored into message objects if they
 *            pass acceptance filtering.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "dcan_loopback_app.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#if defined (SOC_TDA2EX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA3XX)
#define DCAN_MSG_OBJ_1                   (0x4)
#define DCAN_MSG_OBJ_2                   (0x6)

/** \brief DCAN Message Object RAM Address */
#define DCAN_MSG_OBJ_RAM_ADDR_1         ((SOC_DCAN1_MESSAGERAM_BASE) + \
                                         (DCAN_MSG_OBJ_1 * DCAN_MSG_OBJ_SIZE))
#define DCAN_MSG_OBJ_RAM_ADDR_2         ((SOC_DCAN1_MESSAGERAM_BASE) + \
                                         (DCAN_MSG_OBJ_2 * DCAN_MSG_OBJ_SIZE))
#else
#define DCAN_MSG_OBJ_RAM_ADDR           ((SOC_DCAN1_MESSAGERAM_BASE) + \
                                         (DCAN_MSG_OBJ * DCAN_MSG_OBJ_SIZE))
#endif

/* ========================================================================== */
/*                         Global Variables                                   */
/* ========================================================================== */

extern uint32_t gDcanAppInstance;
char gMainMenuOption;

/*To use UARTConfigPuts function for prints*/
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_AM572x) || defined (SOC_AM574x) || defined (SOC_AM571x)
uint32_t uartBaseAddr = CSL_MPU_UART3_REGS;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

#if defined (SOC_TDA3XX)
dcanEccErrStatus_t     gErrClr;
uint32_t               gMsgObjSBE;
uint32_t               gMsgObjDBE;
#endif
#if defined (SOC_TDA2EX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
uint32_t               gMsgObj;
uint32_t               gWordNum;
#endif

#if defined (SOC_TDA2EX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA3XX)
static int32_t dcanParityEccTest(void);
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function will calculate the bit-timing parameters for the
 *          DCAN controller based on the input frequency and required bit-rate
 *          on the CAN bus.
 *
 * \param   pBitTimeParam  Pointer to dcanBitTimeParams_t structure.
 * \param   clkFreq        Clock frequency to DCAN controller in MHz.
 *
 * \return  Returns the error value if error is present.
 */
static uint32_t DCANAppBitTimeCalculator(
    dcanBitTimeParamsLocal_t *pBitTimeParam,
    uint32_t                  clkFreq);

/**
 * \brief   This function will update the sampling point based on CAN time
 *          segment values
 *
 * \param   pBitTimeParam  Pointer to dcanBitTimeParams_t structure.
 * \param   samplePnt      Sample point value.
 * \param   tseg           Time segment value.
 * \param   tseg1          Pointer to store time segment 1 value.
 * \param   tseg2          Pointer to store time segment 2 value.
 *
 * \return  Returns the updated sample point value.
 **/
static int32_t DCANAppUpdateSamplePnt(dcanBitTimeParamsLocal_t *pBitTimeParam,
                                      int32_t                   samplePnt,
                                      int32_t                   tseg,
                                      int32_t                  *tseg1,
                                      int32_t                  *tseg2);

extern void DCANAppConfigIntr(void);
									  
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
 * \brief   Initializes UART with the required UART parameters
 *
 */
void uartInit()
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8,
                    UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8,
                    UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
}

/*
 * ======== Board Initialization ========
 */

void padConfig_prcmEnable()
{
#if defined (SOC_AM572x) || defined (SOC_AM574x) || defined (SOC_AM571x)
    /*Pad configurations */
    Board_initCfg boardCfg;
    boardCfg = BOARD_INIT_UNLOCK_MMR | BOARD_INIT_UART_STDIO |
               BOARD_INIT_MODULE_CLOCK | BOARD_INIT_PINMUX_CONFIG;
    Board_init(boardCfg);
#endif
    uartInit();
}

/*
 * ======== Clock configuration and Pin Muxing for DCAN1 ========
 */
void DCAN1Prcm_clck_ram()
{
    uint32_t status;
#if defined (SOC_AM572x) || defined (SOC_AM574x) || defined (SOC_AM571x)
    HW_WR_FIELD32(CSL_MPU_WKUPAON_CM_REGS + CM_WKUPAON_CLKSTCTRL,
              CM_WKUPAON_CLKSTCTRL_CLKTRCTRL,
              CM_WKUPAON_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

	HW_WR_FIELD32( CSL_MPU_CORE_CM_CORE_REGS + CM_L4CFG_CLKSTCTRL,
                    CM_L4CFG_CLKSTCTRL_CLKTRCTRL,
                    CM_L4CFG_CLKSTCTRL_CLKTRCTRL_NO_SLEEP);

    /*pin mux for dcan1_tx*/
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_DCAN1_TX,0x000E0000);
	/*pin mux with default muxmode for dcan1_rx*/
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_DCAN1_RX,0x0000000E);

    /*CM_WKUPAON_DCAN1_CLKCTRL*/
    HW_WR_FIELD32(CSL_MPU_WKUPAON_CM_REGS + CM_WKUPAON_DCAN1_CLKCTRL,
              CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE,
              CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_ENABLE);
	while ((HW_RD_FIELD32(CSL_MPU_WKUPAON_CM_REGS + CM_WKUPAON_DCAN1_CLKCTRL,
                     CM_WKUPAON_DCAN1_CLKCTRL_IDLEST)) ==
                    CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_DISABLE)
            {
                ;
            }

   /* Clear the start bit so that pulse is generated when run second time */
    HW_WR_FIELD32((uint32_t) CSL_MPU_CTRL_MODULE_CORE_CORE_REGISTERS_REGS +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                0U);

    HW_WR_FIELD32((uint32_t) CSL_MPU_CTRL_MODULE_CORE_CORE_REGISTERS_REGS +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET);
    status =((uint32_t) 0x1 <<
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_MASK;

    while (status !=((status &
                    HW_RD_REG32(CSL_MPU_CTRL_MODULE_CORE_CORE_REGISTERS_REGS +
                                CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

    /*pin mux for dcan1_rx*/
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_DCAN1_RX,0x000E0000);

    /* Clear the done bit */
    HW_WR_FIELD32((uint32_t) CSL_MPU_CTRL_MODULE_CORE_CORE_REGISTERS_REGS +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE,
                1U);
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*CM_WKUPAON_DCAN1_CLKCTRL*/
    HW_WR_FIELD32(SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL,
                CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE,
                CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_ENABLE);

    while ((HW_RD_FIELD32(SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL,
                CM_WKUPAON_DCAN1_CLKCTRL_IDLEST)) ==
                CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_DISABLE)
            {
                ;
            }
    /*pin mux for dcan1*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_DCAN1_TX,0x000E0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_WAKEUP0,0x00010001);

    /* Clear the start bit so that pulse is generated when run second time */
    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                0U);

    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET);
    status =((uint32_t) 0x1 << CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_MASK;

    while (status != ((status & HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

    /* Clear the done bit */
    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE,
                1U);
#endif

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*CM_WKUPAON_DCAN1_CLKCTRL*/
    HW_WR_FIELD32(SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL,
                CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE,
                CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_ENABLE);

    while ((HW_RD_FIELD32(SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL,
                CM_WKUPAON_DCAN1_CLKCTRL_IDLEST)) ==
                CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_DISABLE)
            {
                ;
            }
    /*pin mux for dcan1*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_DCAN1_TX,0x000E0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_DCAN1_RX,0x000E0000);

    /* Clear the start bit so that pulse is generated when run second time */
    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                0U);

    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET);

    status = ((uint32_t) 0x1 <<
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_MASK;

    while (status != ((status &
                HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

    /* Clear the done bit */
    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE,
                1U);
#endif
}

/*
 * ======== Clock configuration and Pin Muxing for DCAN2 ========
 */
void DCAN2Prcm_clck_ram()
{
    uint32_t status;

#if defined (SOC_AM572x) || defined (SOC_AM574x) || defined (SOC_AM571x)
	/*CM_L4PER2_DCAN2_CLKCTRL*/
    HW_WR_FIELD32(CSL_MPU_L4PER_CM_CORE_REGS + CM_L4PER2_CLKSTCTRL,
                CM_L4PER2_CLKSTCTRL_CLKTRCTRL,
                CM_L4PER2_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

	HW_WR_FIELD32( CSL_MPU_CORE_CM_CORE_REGS + CM_L4CFG_CLKSTCTRL,
					CM_L4CFG_CLKSTCTRL_CLKTRCTRL,
					CM_L4CFG_CLKSTCTRL_CLKTRCTRL_NO_SLEEP);

	/*pin mux for dcan2_tx*/
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPIO6_14,0x2);
	/*pin mux to default muxmode for dcan2_rx*/
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPIO6_15,0x0);

    /*CM_L4PER2_DCAN2_CLKCTRL*/
    HW_WR_FIELD32(CSL_MPU_L4PER_CM_CORE_REGS + CM_L4PER2_DCAN2_CLKCTRL,
                CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE,
                CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE_ENABLE);

    while ((HW_RD_FIELD32(CSL_MPU_L4PER_CM_CORE_REGS + CM_L4PER2_DCAN2_CLKCTRL,
                CM_L4PER2_DCAN2_CLKCTRL_IDLEST)) ==
                CM_L4PER2_DCAN2_CLKCTRL_IDLEST_DISABLE)
           {
               ;
           }

    /* Clear the start bit so that pulse is generated when run second time */
    HW_WR_FIELD32((uint32_t) CSL_MPU_CTRL_MODULE_CORE_CORE_REGISTERS_REGS +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                0U);

    HW_WR_FIELD32((uint32_t) CSL_MPU_CTRL_MODULE_CORE_CORE_REGISTERS_REGS +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET);
    status =((uint32_t) 0x1 <<
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_MASK;

    while (status !=((status &
                HW_RD_REG32(CSL_MPU_CTRL_MODULE_CORE_CORE_REGISTERS_REGS +
                CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

    /* Write one to clear done bit */
    HW_WR_FIELD32((uint32_t) CSL_MPU_CTRL_MODULE_CORE_CORE_REGISTERS_REGS +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE,1U);
	/*pin mux for dcan2_rx*/
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPIO6_15,0x2);
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*CM_L4PER2_DCAN2_CLKCTRL*/
    HW_WR_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL,
               CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE,
               CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE_ENABLE);

    while ((HW_RD_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL,
                CM_L4PER2_DCAN2_CLKCTRL_IDLEST)) ==
                CM_L4PER2_DCAN2_CLKCTRL_IDLEST_DISABLE)
            {
                ;
            }
    /*pin mux for dcan2*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPIO6_14,0x2);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPIO6_15,0x2);

    /* Clear the start bit so that pulse is generated when run second time */
    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                0U);

    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET);
    status =((uint32_t) 0x1 <<
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_MASK;

    while (status !=((status &
                HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

    /* Clear the done bit */
    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE,
                1U);
#endif

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*CM_WKUPAON_DCAN2_CLKCTRL*/
    HW_WR_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL,
                CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE,
                CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE_ENABLE);

    while ((HW_RD_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL,
                CM_L4PER2_DCAN2_CLKCTRL_IDLEST)) ==
                CM_L4PER2_DCAN2_CLKCTRL_IDLEST_DISABLE)
            {
                ;
            }
    /*pin mux for dcan2*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_RXD,0xc);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_TXD,0xc);

    /* Clear the start bit so that pulse is generated when run second time */
    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                0U);

    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET);
    status = ((uint32_t) 0x1 <<
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_MASK;

    while (status != ((status &
                HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

    /* Clear the done bit */
    HW_WR_FIELD32((uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE,
                1U);
#endif

}

/*
 * This function configures the DCAN controller with the user
 * selected DCAN instance.
 */
void DCANAppInitParams(dcanCfgParams_t       *pDcanCfgPrms,
                              dcanMsgObjCfgParams_t *pDcanTxCfgPrms,
                              dcanMsgObjCfgParams_t *pDcanRxCfgPrms,
                              dcanTxParams_t        *pDcanTxPrms,
							  char     pMainMenuOption)
{
    /*Initialize DCAN Config Params*/

    if (DCAN_PARITY_ECC_TEST == pMainMenuOption)
    {
        pDcanCfgPrms->parityEnable    = TRUE;
        pDcanCfgPrms->intrLine0Enable = FALSE;
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        pDcanCfgPrms->eccModeEnable     = TRUE;
        pDcanCfgPrms->eccDiagModeEnable = FALSE;
        pDcanCfgPrms->sbeEventEnable    = TRUE;
#endif
        pDcanCfgPrms->testModeEnable = FALSE;
    }
    else
    {
        pDcanCfgPrms->parityEnable    = FALSE;
        pDcanCfgPrms->intrLine0Enable = TRUE;
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        pDcanCfgPrms->eccModeEnable = FALSE;
#endif
        pDcanCfgPrms->testModeEnable = TRUE;
        if (pMainMenuOption == DCAN_INT_LOOPBACK_TEST)
        {
            pDcanCfgPrms->testMode = DCAN_TEST_MODE_LPBACK;
        }
        else
        {
            pDcanCfgPrms->testMode = DCAN_TEST_MODE_EXT_LPBACK;
        }
    }

    pDcanCfgPrms->autoRetransmitDisable = TRUE;
    pDcanCfgPrms->autoBusOnEnable       = FALSE;
    pDcanCfgPrms->intrLine1Enable       = FALSE;
    pDcanCfgPrms->errIntrEnable         = FALSE;
    pDcanCfgPrms->stsChangeIntrEnable   = FALSE;
    pDcanCfgPrms->autoBusOnTimerVal     = FALSE;
    pDcanCfgPrms->if1DmaEnable          = FALSE;
    pDcanCfgPrms->if2DmaEnable          = FALSE;
    pDcanCfgPrms->if3DmaEnable          = FALSE;
    pDcanCfgPrms->ramAccessEnable       = FALSE;

    /*Initialize DCAN tx Config Params*/
    pDcanTxCfgPrms->xIdFlagMask       = 0x1;
    pDcanTxCfgPrms->dirMask           = 0x1;
    pDcanTxCfgPrms->msgIdentifierMask = 0x1FFFFFFF;

    pDcanTxCfgPrms->msgValid      = TRUE;
    pDcanTxCfgPrms->xIdFlag       = TRUE;
    pDcanTxCfgPrms->direction     = DCAN_DIR_TX;
    pDcanTxCfgPrms->msgIdentifier = 0xC1;

    pDcanTxCfgPrms->uMaskUsed    = TRUE;
    pDcanTxCfgPrms->intEnable    = TRUE;
    pDcanTxCfgPrms->remoteEnable = FALSE;
    pDcanTxCfgPrms->fifoEOBFlag  = TRUE;

    /*Initialize DCAN Rx Config Params*/
    pDcanRxCfgPrms->xIdFlagMask       = 0x1;
    pDcanRxCfgPrms->msgIdentifierMask = 0x1FFFFFFF;
    pDcanRxCfgPrms->dirMask           = 0x1;

    pDcanRxCfgPrms->msgValid      = TRUE;
    pDcanRxCfgPrms->xIdFlag       = TRUE;
    pDcanRxCfgPrms->direction     = DCAN_DIR_RX;
    pDcanRxCfgPrms->msgIdentifier = 0xC1;

    pDcanRxCfgPrms->uMaskUsed    = TRUE;
    pDcanRxCfgPrms->intEnable    = TRUE;
    pDcanRxCfgPrms->remoteEnable = FALSE;
    pDcanRxCfgPrms->fifoEOBFlag  = TRUE;

    /*Initialize DCAN Tx transfer Params*/
    pDcanTxPrms->dataLength = DCAN_MAX_MSG_LENGTH;
#ifndef RTOS_BUILD
    pDcanTxPrms->msgData[0] = 0xA5;
    pDcanTxPrms->msgData[1] = 0x5A;
    pDcanTxPrms->msgData[2] = 0xFF;
    pDcanTxPrms->msgData[3] = 0xFF;
    pDcanTxPrms->msgData[4] = 0xC3;
    pDcanTxPrms->msgData[5] = 0x3C;
    pDcanTxPrms->msgData[6] = 0xB4;
    pDcanTxPrms->msgData[7] = 0x4B;
#endif
}

/*
 * This function takes I/P Clk frequency, required bit-rate on the
 * CAN bus and calculates the value to be programmed for DCAN BTR
 * register. This API doesn't do the actual programming. This is
 * intended to be used as a utility function. And the application
 * should call the #DCANSetBitTime function to do the actual
 * programming.
 */
extern uint32_t DCANCalculateBitTimeParams(uint32_t             clkFreq,
                                           uint32_t             bitRate,
                                           dcanBitTimeParams_t *pBitTimePrms)
{
    uint32_t errVal;
    dcanBitTimeParamsLocal_t bitTimePrms;

    bitTimePrms.samplePnt           = 0U;
    bitTimePrms.timeQuanta          = 0U;
    bitTimePrms.propSeg             = 0U;
    bitTimePrms.phaseSeg1           = 0U;
    bitTimePrms.phaseSeg2           = 0U;
    bitTimePrms.syncJumpWidth       = 0U;
    bitTimePrms.bitRatePrescaler    = 0U;
    bitTimePrms.tseg1Min            = 1U;
    bitTimePrms.tseg1Max            = 16U;
    bitTimePrms.tseg2Min            = 1U;
    bitTimePrms.tseg2Max            = 8U;
    bitTimePrms.syncJumpWidthMax    = 4U;
    bitTimePrms.bitRatePrescalerMin = 1U;
    bitTimePrms.bitRatePrescalerMax = 1024U;
    bitTimePrms.bitRatePrescalerInc = 1U;
    bitTimePrms.bitRate             = bitRate;

    errVal = DCANAppBitTimeCalculator(&bitTimePrms, clkFreq);

    pBitTimePrms->baudRatePrescaler =
        ((bitTimePrms.bitRatePrescaler - 1U) & DCAN_BTR_BRP_MASK);
    pBitTimePrms->syncJumpWidth = bitTimePrms.syncJumpWidth;
    pBitTimePrms->timeSegment1  =
        (bitTimePrms.phaseSeg1 + bitTimePrms.propSeg - 1U);
    pBitTimePrms->timeSegment2         = (bitTimePrms.phaseSeg2 - 1U);
    pBitTimePrms->baudRatePrescalerExt =
        (((bitTimePrms.bitRatePrescaler -
            1U) & DCAN_APP_EXTRACT_BRPE_VAL) >> DCAN_APP_BRPE_SHIFT);

    return (errVal);
}

/*
 * ======== DCAN BitTimeParameters Calculation ========
 */
static uint32_t DCANAppBitTimeCalculator(
    dcanBitTimeParamsLocal_t *pBitTimeParam,
    uint32_t                  clkFreq)
{
    int32_t  samplePnt = 0U, samplePntErr = 1000U, tsegAll = 0U;
    int32_t  tseg      = 0U, tseg1 = 0U, tseg2 = 0U;
    int32_t  brp       = 0U, samplePntNew = 0U, bestTseg = 0U, bestBrp = 0U;
    long     err       = 0U, bestErr = 1000000000U;
    uint32_t errVal    = DCAN_BIT_RATE_ERR_NONE;
    uint32_t rate      = 0U, timeQuanta = 0U;

    if (pBitTimeParam->bitRate > 800000U)
    {
        samplePnt = 750U;
    }
    else if (pBitTimeParam->bitRate > 500000U)
    {
        samplePnt = 800U;
    }
    else
    {
        samplePnt = 875U;
    }

    for (tseg = (pBitTimeParam->tseg1Max + pBitTimeParam->tseg2Max) * 2 + 1;
        tseg >= (pBitTimeParam->tseg1Min + pBitTimeParam->tseg2Min) * 2;
        tseg--)
    {
        tsegAll = 1 + tseg / 2;

        /* Compute all possible tseg choices (tseg = tseg1+tseg2) */
        brp = clkFreq / (tsegAll * pBitTimeParam->bitRate) + tseg % 2;

        /* chose brp step which is possible in system */
        brp = (brp / pBitTimeParam->bitRatePrescalerInc) *
            pBitTimeParam->bitRatePrescalerInc;

        if ((brp < pBitTimeParam->bitRatePrescalerMin) ||
           (brp > pBitTimeParam->bitRatePrescalerMax))
        {
            continue;
        }

        rate = clkFreq / (brp * tsegAll);
        err  = pBitTimeParam->bitRate - rate;

        /* tseg brp biterror */
        if (err < 0)
        {
            err = -err;
        }
        if (err > bestErr)
        {
            continue;
        }
        bestErr = err;
        if (err == 0)
        {
            samplePntNew = DCANAppUpdateSamplePnt(pBitTimeParam,
                                                  samplePnt,
                                                  tseg / 2,
                                                  &tseg1,
                                                  &tseg2);

            err = samplePnt - samplePntNew;
            if (err < 0)
            {
                err = -err;
            }
            if (err > samplePntErr)
            {
                continue;
            }
            samplePntErr = err;
        }
        bestTseg = tseg / 2;
        bestBrp  = brp;
        if (err == 0)
        {
            break;
        }
    }

    if (bestErr)
    {
        /* Error in one-tenth of a percent */
        err = (bestErr * 1000) / pBitTimeParam->bitRate;
        if (err > DCAN_APP_CALC_MAX_ERROR)
        {
            errVal = DCAN_BIT_RATE_ERR_MAX;
        }
        else
        {
            errVal = DCAN_BIT_RATE_ERR_WARN;
        }
    }

    /* real sample point */
    pBitTimeParam->samplePnt = DCANAppUpdateSamplePnt(pBitTimeParam,
                                                      samplePnt,
                                                      bestTseg,
                                                      &tseg1,
                                                      &tseg2);

    /* Calculate the time quanta value. */
    timeQuanta = bestBrp * 1000000000UL;

    pBitTimeParam->timeQuanta       = timeQuanta;
    pBitTimeParam->propSeg          = tseg1 / 2;
    pBitTimeParam->phaseSeg1        = tseg1 - pBitTimeParam->propSeg;
    pBitTimeParam->phaseSeg2        = tseg2;
    pBitTimeParam->syncJumpWidth    = 1;
    pBitTimeParam->bitRatePrescaler = bestBrp;

    /* Real bit-rate */
    pBitTimeParam->bitRate =
        clkFreq / (pBitTimeParam->bitRatePrescaler * (tseg1 + tseg2 + 1));

    return (errVal);
}

/*
 * ======== DCAN Sampling Point Update ========
 */
static int32_t DCANAppUpdateSamplePnt(dcanBitTimeParamsLocal_t *pBitTimeParam,
                                      int32_t                   samplePnt,
                                      int32_t                   tseg,
                                      int32_t                  *tseg1,
                                      int32_t                  *tseg2)
{
    *tseg2 = tseg + 1 - (samplePnt * (tseg + 1)) / 1000;

    if (*tseg2 < pBitTimeParam->tseg2Min)
    {
        *tseg2 = pBitTimeParam->tseg2Min;
    }

    if (*tseg2 > pBitTimeParam->tseg2Max)
    {
        *tseg2 = pBitTimeParam->tseg2Max;
    }

    *tseg1 = tseg - *tseg2;

    if (*tseg1 > pBitTimeParam->tseg1Max)
    {
        *tseg1 = pBitTimeParam->tseg1Max;
        *tseg2 = tseg - *tseg1;
    }
    return (1000 * (tseg + 1 - *tseg2) / (tseg + 1));
}

/*
 * ======== DCAN IF Busy Check ========
 */
extern void DCANAppWaitForIfReg(uint32_t baseAddr, uint32_t ifRegNum)
{
    do
    {
        if (TRUE != DCANIsIfRegBusy(baseAddr, ifRegNum))
        {
            break;
        }
    }
    while (1);
}

/*
 * ======== UserInterface to Display MenuOptions ========
 */
void mainMenu(char *option)
{
    while (1)
    {
        PRINT_MSG("\n\n**** DCAN APPLICATION TEST ****");
        PRINT_MSG("\nMenu:");
        PRINT_MSG("\n1. DCAN External Loopback test - DCAN1 Instance");
        PRINT_MSG("\n2. DCAN Internal Loopback test - DCAN2 Instance");
#if defined (SOC_TDA3XX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
		PRINT_MSG("\n3. DCAN PARITY/ECC test - DCAN1 Instance");
#endif
        PRINT_MSG("\nx. Exit");
        PRINT_MSG("\nSelect DCAN APPLICATION TEST : ");

        /* Get User option to select DCAN instance1 or DCAN instance2 */
        SCAN_MSG("%c", option);

        if ((DCAN_EXT_LOOPBACK_TEST == *option) ||
            (DCAN_PARITY_ECC_TEST == *option) ||
            (DCAN_INT_LOOPBACK_TEST == *option) || EXIT(*option))
        {
            break;
        }
        else
        {
            PRINT_MSG("\nEnter Valid option\n");
        }
    }
}

/*
 * ======== Executes DCAN Tests ========
 */
int32_t execTest(void)
{
    uint32_t skipTestCase = 0;
    int32_t retVal = STW_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_AM574x) || (SOC_TDA3XX) || defined (SOC_DRA78x)
    uint32_t          siliconRev;
#endif
    /* Board Initialization */
    padConfig_prcmEnable();

#if defined (SOC_TDA2XX) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_AM574x) || (SOC_TDA3XX) || defined (SOC_DRA78x)
    siliconRev = CSL_getSocSiliconRev();
#endif

#if defined (SOC_TDA2XX) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_AM574x)
    if (CSL_SOC_SILICON_REV_1_0 == siliconRev)
    {
        PRINT_MSG("\nDCAN Loopback is not supported for Tda2xx/AM57xx PG1.0 Silicon...");
        return 0;
    }
#endif
    while (1)
    {
        /* Get the User input to select DCAN instance1 or DCAN instance2 */
        mainMenu(&gMainMenuOption);
        if ((DCAN_EXT_LOOPBACK_TEST == gMainMenuOption) ||
        (DCAN_INT_LOOPBACK_TEST == gMainMenuOption))
        {
            if (DCAN_EXT_LOOPBACK_TEST == gMainMenuOption)
            {
                /* DCAN instance1 is opted */
                gDcanAppInstance = DCAN1_APP_INST;
            }
            else
            {
                /* DCAN instance2 is opted */
                #if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
                if (siliconRev == CSL_SOC_SILICON_REV_2_0)
                {
                    PRINT_MSG("\r\nDCAN2 Instance is not supported for Tda3xx PG2.0 Silicon...");
                    PRINT_MSG("\r\nSkipping DCAN Internal Loopback Test...");
                    skipTestCase = 1;
                }
                #endif
                gDcanAppInstance = DCAN2_APP_INST;
            }
            if(skipTestCase == 0)
            {
#ifdef RTOS_BUILD
                /* DCAN Tx/Rx Interrupt Configuration */
                DCANAppConfigIntr();
#endif
                /* Execute DCAN Loopback Test */
                retVal = dcanLoopbackTest();
            }
        }
        #if defined (SOC_TDA3XX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        else if(DCAN_PARITY_ECC_TEST == gMainMenuOption)
        {
            gDcanAppInstance = DCAN1_APP_INST;
            /* Execute DCAN ParityECC Test */
            retVal = dcanParityEccTest();
        }
        #endif
        else
        {
            PRINT_MSG("\nDCAN Application Test exiting...");
            break;
        }
    }
    return retVal;
}

#if defined (SOC_TDA2EX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA3XX)
void DcanMessageRamInit(uint32_t instance)
{
    uint32_t status = 0U;

    switch (instance)
    {
        case 0U:
            /* Clear the start bit so that pulse is generated
             * when run second time */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_CLEAR);
            /* Set the start bit so that pulse is generated
             * when run second time.
             * CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET
             * causes Init pulse to happen and SW not needed to write */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET);
            status =
                ((uint32_t) 0x1 <<
                 CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_MASK;

            while (status !=
                   ((status &
                     HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                 CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

            /* Write one to clear done bit */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_CLEAR);
            break;

        case 1U:
            /* Clear the start bit so that pulse is generated
             * when run second time */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_CLEAR);
            /* Set the start bit so that pulse is generated
             * when run second time.
             * CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET
             * causes Init pulse to happen and SW not needed to write */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET);
            status =
                ((uint32_t) 0x1 <<
                 CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_MASK;

            while (status !=
                   ((status &
                     HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                 CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

            /* Write one to clear done bit */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_CLEAR);
            break;

        default:
            break;
    }
}
#endif

#if defined (SOC_TDA3XX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
/*
 * ======== DCAN ParityEcc Test ========
 */
static int32_t dcanParityEccTest(void)
{
    int32_t               retVal    = STW_SOK;
#if defined (SOC_TDA3XX)
    int32_t               errStatus = STW_SOK;
#endif
    dcanCfgParams_t       appDcanCfgPrms;
    dcanMsgObjCfgParams_t appDcanTxCfgPrms;
    dcanMsgObjCfgParams_t appDcanRxCfgPrms;
    dcanTxParams_t        appDcanTxPrms;
    dcanBitTimeParams_t   appDcanBitTimePrms;
    uint32_t              timeOut = 100U;
    int32_t              *pMsgObj;
    uint32_t              msgObj, i;
    dcanRxParams_t        appDcanRxPrms[2];
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    uint32_t              dataLength    = 0U;
    uint32_t              msgLstErrCnt  = 0U;
    uint32_t              missMatchdata = 0U;
    uint32_t              actualdata    = 0U;
    dcanEccErrStatus_t    eccDiagErrClr;
#endif

    PRINT_MSG("\r\nDCAN PARITY/ECC Test App\r\n");

#if defined (__TI_ARM_V7M4__)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as IPU1_C0
     * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach the
     * peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1, ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));
#endif
#if defined (__ARM_ARCH_7A__)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as MPU_C0
     * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach the
     * peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1, ((DRM_SUSPEND_SRC_MPU_C0 << 4) | 0x1));
#endif
    DCANAppInitParams(&appDcanCfgPrms,
                      &appDcanTxCfgPrms,
                      &appDcanRxCfgPrms,
                      &appDcanTxPrms,
                      gMainMenuOption);


    DCAN1Prcm_clck_ram();

    /* Reset the DCAN IP */
    retVal = DCANReset(gDcanAppInstance, timeOut);
    if (retVal == STW_SOK)
    {
        /* Set the desired bit rate based on input clock */
        DCANSetMode(gDcanAppInstance, DCAN_MODE_INIT);

        if (DCAN_BIT_RATE_ERR_NONE !=
                            DCANCalculateBitTimeParams(DCAN_APP_INPUT_CLK,
                                                       DCAN_APP_BIT_RATE,
                                                       &appDcanBitTimePrms))
        {
            return ((int32_t)STW_EFAIL);
        }
        DCANSetBitTime(gDcanAppInstance, &appDcanBitTimePrms);
        DCANSetMode(gDcanAppInstance, DCAN_MODE_NORMAL);

        /* Configure DCAN controller */
        DCANConfig(gDcanAppInstance, &appDcanCfgPrms);
    }

    if (appDcanCfgPrms.parityEnable == TRUE)
    {
        /* DCAN message RAM to generate ECC/Parity Bits*/
        DcanMessageRamInit(0);
    }

    DCANAppConfigParityIntr();

    for (i = 0; i < DCAN_NUM_MSG_OBJ; i++)
    {
        if (i == 0)
        {
            msgObj = DCAN_MSG_OBJ_1;
        }
        else
        {
            msgObj = DCAN_MSG_OBJ_2;
        }

        if (retVal == STW_SOK)
        {
            /* Wait for interface to become free */
            DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
            retVal = DCANConfigMsgObj(gDcanAppInstance,
                                      msgObj,
                                      DCAN_APP_TX_IF_REG,
                                      &appDcanTxCfgPrms);
            /* Wait for config to be copied to internal message RAM */
            DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
        }
        if (retVal == STW_SOK)
        {
            /* Wait for interface to become free */
            DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
            retVal = DCANTransmitData(gDcanAppInstance,
                                      msgObj,
                                      DCAN_APP_TX_IF_REG,
                                      &appDcanTxPrms,
                                      timeOut);
            /* Wait for config to be copied to internal message RAM */
            DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
        }
    }

    /* Disable SECDED to corrupt the RAM */
    DCANParityEnable(gDcanAppInstance, FALSE);

#if defined (SOC_TDA3XX)
    /* Enable ECCDIAG mode */
    DCANEccDiagModeEnable(gDcanAppInstance, TRUE);
#endif

    /* RDA mode is enabled to ACCESS the MessageRAM */
    DCANTestModeEnable(gDcanAppInstance, TRUE, DCAN_TEST_RDA_MASK);

    pMsgObj = (int32_t *) (DCAN_MSG_OBJ_RAM_ADDR_1);

    /* Corrupting the data in Message RAM in RDA Mode :
     * as 0xC343B44A instead of 0xC343B44B which introduces
     * single bit error for ECC test / Parity Error for Parity test.
     */
    *pMsgObj = (*pMsgObj ^ 0x1);

#if defined (SOC_TDA3XX)
    pMsgObj = (int32_t *) (DCAN_MSG_OBJ_RAM_ADDR_2);

    /* Corrupting the data in Message RAM in RDA Mode :
     * as 0xC343B448 instead of 0xC343B44B which introduces single bit error.
     */
    *pMsgObj = (*pMsgObj ^ 0x3);
#endif

    /* RDA mode is disabled to ACCESS the MessageRAM */
    DCANTestModeEnable(gDcanAppInstance, FALSE, DCAN_TEST_RDA_MASK);
    /* Enable SECDED */
    DCANParityEnable(gDcanAppInstance, TRUE);

    for (i = 0; i < DCAN_NUM_MSG_OBJ; i++)
    {
        if (i == 0)
        {
            msgObj = DCAN_MSG_OBJ_1;
        }
        else
        {
            msgObj = DCAN_MSG_OBJ_2;
        }

        if (retVal == STW_SOK)
        {
            /* Wait for interface to become free */
            DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
            retVal = DCANGetData(gDcanAppInstance,
                                 msgObj,
                                 DCAN_APP_RX_IF_REG,
                                 &appDcanRxPrms[i],
                                 timeOut);
            /* Wait for config to be copied to internal message RAM */
            DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
        }

#if defined (SOC_TDA3XX)
        errStatus = DCANGetEccDiagErrStatus(gDcanAppInstance);

        eccDiagErrClr.singleBitErr = (errStatus &
                                      DCAN_ECC_DIAG_STATUS_SE_FLAG_MASK);
        eccDiagErrClr.doubleBitErr = ((errStatus &
                                       DCAN_ECC_DIAG_STATUS_DE_FLAG_MASK) >>
                                      DCAN_ECC_DIAG_STATUS_DE_FLAG_SHIFT);

        DCANClrEccDiagErrStatus(gDcanAppInstance, &eccDiagErrClr);
#endif
    }
#if defined (SOC_TDA3XX)
    DCANEccDiagModeEnable(gDcanAppInstance, FALSE);
#endif
    DCANParityEnable(gDcanAppInstance, FALSE);

#if defined (SOC_TDA3XX)
    if ((gMsgObjSBE == DCAN_MSG_OBJ_1) && (gMsgObjDBE == DCAN_MSG_OBJ_2))
    {
        PRINT_MSG("\r\nDCAN -- ECC test Passed!! \r\n");
    }
    else
    {
        PRINT_MSG("\r\nDCAN -- ECC test Failed!! \r\n");
        retVal = STW_EFAIL;
    }

    if ((gMsgObjSBE == DCAN_MSG_OBJ_1) && (gMsgObjDBE == DCAN_MSG_OBJ_2))
    {
        for (i = 0; i < DCAN_NUM_MSG_OBJ; i++)
        {
            dataLength = 0;
            if (retVal == STW_SOK)
            {
                /* Check if sent data is lost or not */
                if (appDcanRxPrms[i].msgLostFlag == TRUE)
                {
                    msgLstErrCnt++;
                }

                /* Check if sent data has been received */
                if (appDcanRxPrms[i].dataLength == appDcanTxPrms.dataLength)
                {
                    while (dataLength < appDcanRxPrms[i].dataLength)
                    {
                        if (appDcanRxPrms[i].msgData[dataLength] !=
                            appDcanTxPrms.msgData[dataLength])
                        {
                            retVal        = STW_EFAIL;
                            missMatchdata =
                                appDcanRxPrms[i].msgData[dataLength];
                            actualdata = appDcanTxPrms.msgData[dataLength];
                        }
                        dataLength++;
                    }
                }
                else
                {
                    retVal = STW_EFAIL;
                }

                if ((i == 0) && (retVal == STW_SOK))
                {
                    PRINT_MSG("\r\nSingle bit ECC Error is autocorrected at message object : ");
                    PRINT_HEX(gMsgObjSBE);
                }

                if ((i == 1) && (retVal == STW_EFAIL))
                {
                    PRINT_MSG("\r\n Double bit ECC Error is detected at message object :  ");
                    PRINT_HEX(gMsgObjDBE);
                    PRINT_MSG("\r\n Missmatch Data of Double bit ECC Error:  ");
                    PRINT_HEX(missMatchdata);
                    PRINT_MSG("\r\n Actual Data of Double bit ECC Error:  ");
                    PRINT_HEX(actualdata);
                }
            }
        }
    }
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    if (gMsgObj == DCAN_MSG_OBJ_1)
    {
        PRINT_MSG("\r\nDCAN -- PARITY test Passed!! \r\n");
        PRINT_MSG("\r\n Parity Error is detected at message object:");
        PRINT_HEX(gMsgObj);
        PRINT_MSG(" Word Number:");
        PRINT_HEX(gWordNum);
    }
    else
    {
        PRINT_MSG("\r\nDCAN -- PARITY test Failed!! \r\n");
        retVal = STW_EFAIL;
    }
#endif

    return retVal;
}
#endif
/********************************* End of file ******************************/
