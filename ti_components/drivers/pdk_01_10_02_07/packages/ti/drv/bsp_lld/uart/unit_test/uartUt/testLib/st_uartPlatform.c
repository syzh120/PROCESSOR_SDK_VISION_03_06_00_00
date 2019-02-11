/*
 *  Copyright (c) Texas Instruments Incorporated 2012
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
 *  \file st_uartPlatform.c
 *
 *  \brief Platform specific code.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_uart.h>
#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/stw_lld/platform/dma_xbar.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define PULLUDENABLE_ENABLE             ((UInt32) 0x00U)
#define PULLUDENABLE_DISABLE            ((UInt32) 0x01U)
#define PULLTYPESELECT_DOWN             ((UInt32) 0x00U)
#define PULLTYPESELECT_UP               ((UInt32) 0x02U)
#define INPUTENABLE_OUT                 ((UInt32) 0x00U)
#define INPUTENABLE_BI                  ((UInt32) 0x04U)
#define DEFAULT                         ((UInt32) 0xFF)

#define PRCM_ENABLE                     ((UInt32) 2U)

#define BOARD_IO_EXP_I2C_ADDR_1         (0x21U)

/*  Base board PCF8575 2 (on I2C1) - mappings
 *  P1_4 - UART_SEL1_3
 *  P1_6 - SEL_UART3_SPI2
 */
#define BOARD_PCF8575_UART_SEL1_3       (0x10U)
#define BOARD_PCF8575_SEL_UART3_SPI2    (0x40U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 st_uartEnableUartModule(const st_UartUtObj *utObj, Int32 devId);
static Int32 st_uartEnableUartPinMux(const st_UartUtObj *utObj, Int32 devId);
static Int32 st_uartSelectUartOnBoard(const st_UartUtObj *utObj, Int32 devId);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
static Int32 setPinmuxRegs(UInt32 mode_index, UInt32 offset, UInt32 pupd_info);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 st_uartEnableUartInstance(const st_UartUtObj *utObj, Int32 devId)
{
    Int32   retVal = BSP_SOK;

    retVal += st_uartEnableUartModule(utObj, devId);
    retVal += st_uartEnableUartPinMux(utObj, devId);
    if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
    {
        retVal += st_uartSelectUartOnBoard(utObj, devId);
    }

    return (retVal);
}

Int32 st_uartDisableUartInstance(const st_UartUtObj *utObj, Int32 devId)
{
    Int32   retVal = BSP_SOK;

    switch (devId)
    {
        case ST_INSTANCE_ID_UART1:
            break;

        case ST_INSTANCE_ID_UART2:
            break;

        case ST_INSTANCE_ID_UART3:
            break;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
        case ST_INSTANCE_ID_UART4:
            break;

        case ST_INSTANCE_ID_UART5:
            break;

        case ST_INSTANCE_ID_UART6:
            break;
#endif  /* Tda2xx || TI814x */

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        case ST_INSTANCE_ID_UART7:
            break;

        case ST_INSTANCE_ID_UART8:
            break;

        case ST_INSTANCE_ID_UART9:
            break;

        case ST_INSTANCE_ID_UART10:
            break;
#endif  /* Tda2xx */

        default:
            GT_0trace(utObj->traceMask, GT_ERR, "Invalid device ID!!\r\n");
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

static Int32 st_uartEnableUartModule(const st_UartUtObj *utObj, Int32 devId)
{
    Int32   retVal = BSP_SOK;

    switch (devId)
    {
        case ST_INSTANCE_ID_UART1:
            /* Enable module */
            HW_WR_REG32(
                SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART1_CLKCTRL, PRCM_ENABLE);
            while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER_UART1_CLKCTRL) & ((UInt32) (0x00030000)))
                            != 0x0)
            {
                /* Do nothing - Busy wait */
            }

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
            /* IRQ XBAR UART1_IRQ to IPU1_IRQ_44 */
            IRQXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                CPU_IPU1,
                XBAR_INST_IPU1_IRQ_44,
                UART1_IRQ);

            /* UART1 TX EDMA CH - 48 and UART1 RX EDMA CH - 49 */
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_48,
                UART1_DREQ_TX);
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_49,
                UART1_DREQ_RX);
#endif
            break;

        case ST_INSTANCE_ID_UART2:
            /* Enable module */
            HW_WR_REG32(
                SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART2_CLKCTRL, PRCM_ENABLE);
            while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER_UART2_CLKCTRL) & ((UInt32) (0x00030000)))
                            != 0x0)
            {
                /* Do nothing - Busy wait */
            }

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            /* IRQ XBAR UART2_IRQ to IPU1_IRQ_60 */
            IRQXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                CPU_IPU1,
                XBAR_INST_IPU1_IRQ_60,
                UART2_IRQ);
#endif
#if defined (SOC_TDA3XX)
            /* IRQ XBAR UART2_IRQ to IPU1_IRQ_43 */
            IRQXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                CPU_IPU1,
                XBAR_INST_IPU1_IRQ_43,
                UART2_IRQ);
#endif

            /* UART2 TX EDMA CH - 50 and UART1 RX EDMA CH - 51 */
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_50,
                UART2_DREQ_TX);
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_51,
                UART2_DREQ_RX);
#endif
            break;

        case ST_INSTANCE_ID_UART3:
            /* Enable module */
            HW_WR_REG32(
                SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART3_CLKCTRL, PRCM_ENABLE);
            while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER_UART3_CLKCTRL) & ((UInt32) (0x00030000)))
                            != 0x0)
            {
                /* Do nothing - Busy wait */
            }

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
            /* IRQ XBAR UART3_IRQ to IPU1_IRQ_45 */
            IRQXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                CPU_IPU1,
                XBAR_INST_IPU1_IRQ_45,
                UART3_IRQ);

            /* UART3 TX EDMA CH - 52 and UART3 RX EDMA CH - 53 */
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_52,
                UART3_DREQ_TX);
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_53,
                UART3_DREQ_RX);
#endif
            break;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
        case ST_INSTANCE_ID_UART4:
            /* Enable module */
            HW_WR_REG32(
                SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART4_CLKCTRL, PRCM_ENABLE);
            while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER_UART4_CLKCTRL) & ((UInt32) (0x00030000)))
                            != 0x0)
            {
                /* Do nothing - Busy wait */
            }

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            /* IRQ XBAR UART4_IRQ to IPU1_IRQ_61 */
            IRQXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                CPU_IPU1,
                XBAR_INST_IPU1_IRQ_61,
                UART4_IRQ);

            /* UART4 TX EDMA CH - 54 and UART4 RX EDMA CH - 55 */
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_54,
                UART4_DREQ_TX);
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_55,
                UART4_DREQ_RX);
#endif
            break;

        case ST_INSTANCE_ID_UART5:
            /* Enable module */
            HW_WR_REG32(
                SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART5_CLKCTRL, PRCM_ENABLE);
            while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER_UART5_CLKCTRL) & ((UInt32) (0x00030000)))
                            != 0x0)
            {
                /* Do nothing - Busy wait */
            }

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            /* IRQ XBAR UART5_IRQ to IPU1_IRQ_62 */
            IRQXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                CPU_IPU1,
                XBAR_INST_IPU1_IRQ_62,
                UART5_IRQ);

            /* UART4 TX EDMA CH - 62 and UART4 RX EDMA CH - 63 */
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_62,
                UART5_DREQ_TX);
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_63,
                UART5_DREQ_RX);
#endif
            break;

        case ST_INSTANCE_ID_UART6:
            /* Enable module */
            HW_WR_REG32(
                SOC_IPU_CM_CORE_AON_BASE + CM_IPU_UART6_CLKCTRL, PRCM_ENABLE);
            while ((HW_RD_REG32(SOC_IPU_CM_CORE_AON_BASE +
                        CM_IPU_UART6_CLKCTRL) & ((UInt32) (0x00030000)))
                            != 0x0)
            {
                /* Do nothing - Busy wait */
            }

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            /* IRQ XBAR UART6_IRQ to IPU1_IRQ_63 */
            IRQXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                CPU_IPU1,
                XBAR_INST_IPU1_IRQ_63,
                UART6_IRQ);

            /* UART6 TX EDMA CH - 50 and UART6 RX EDMA CH - 51 */
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_50,
                UART6_DREQ_TX);
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_51,
                UART6_DREQ_RX);
#endif
            break;
#endif  /* Tda2xx || TI814x */

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        case ST_INSTANCE_ID_UART7:
            /* Enable module */
            HW_WR_REG32(
                SOC_L4PER_CM_CORE_BASE + CM_L4PER2_UART7_CLKCTRL, PRCM_ENABLE);
            while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER2_UART7_CLKCTRL) & ((UInt32) (0x00030000)))
                            != 0x0)
            {
                /* Do nothing - Busy wait */
            }

            /* IRQ XBAR UART7_IRQ to IPU1_IRQ_64 */
            IRQXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                CPU_IPU1,
                XBAR_INST_IPU1_IRQ_64,
                UART7_IRQ);

            /* UART7 TX EDMA CH - 50 and UART7 RX EDMA CH - 51 */
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_50,
                UART7_DREQ_TX);
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_51,
                UART7_DREQ_RX);
            break;

        case ST_INSTANCE_ID_UART8:
            /* Enable module */
            HW_WR_REG32(
                SOC_L4PER_CM_CORE_BASE + CM_L4PER2_UART8_CLKCTRL, PRCM_ENABLE);
            while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER2_UART8_CLKCTRL) & ((UInt32) (0x00030000)))
                            != 0x0)
            {
                /* Do nothing - Busy wait */
            }

            /* IRQ XBAR UART8_IRQ to IPU1_IRQ_65 */
            IRQXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                CPU_IPU1,
                XBAR_INST_IPU1_IRQ_65,
                UART8_IRQ);

            /* UART8 TX EDMA CH - 50 and UART8 RX EDMA CH - 51 */
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_50,
                UART8_DREQ_TX);
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_51,
                UART8_DREQ_RX);
            break;

        case ST_INSTANCE_ID_UART9:
            /* Enable module */
            HW_WR_REG32(
                SOC_L4PER_CM_CORE_BASE + CM_L4PER2_UART9_CLKCTRL, PRCM_ENABLE);
            while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER2_UART9_CLKCTRL) & ((UInt32) (0x00030000)))
                            != 0x0)
            {
                /* Do nothing - Busy wait */
            }

            /* IRQ XBAR UART9_IRQ to IPU1_IRQ_69 */
            IRQXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                CPU_IPU1,
                XBAR_INST_IPU1_IRQ_69,
                UART9_IRQ);

            /* UART9 TX EDMA CH - 50 and UART9 RX EDMA CH - 51 */
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_50,
                UART9_DREQ_TX);
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_51,
                UART9_DREQ_RX);
            break;

        case ST_INSTANCE_ID_UART10:
            /* Enable module */
            HW_WR_REG32(
                SOC_WKUPAON_CM_BASE + CM_WKUPAON_UART10_CLKCTRL, PRCM_ENABLE);
            while ((HW_RD_REG32(SOC_WKUPAON_CM_BASE +
                        CM_WKUPAON_UART10_CLKCTRL) & ((UInt32) (0x00030000)))
                            != 0x0)
            {
                /* Do nothing - Busy wait */
            }

            /* IRQ XBAR UART10_IRQ to IPU1_IRQ_70 */
            IRQXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                CPU_IPU1,
                XBAR_INST_IPU1_IRQ_70,
                UART10_IRQ);

            /* UART10 TX EDMA CH - 50 and UART10 RX EDMA CH - 51 */
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_50,
                UART10_DREQ_TX);
            DMAXBARConnect(
                SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                EDMA,
                XBAR_INST_DMA_EDMA_DREQ_51,
                UART10_DREQ_RX);
            break;
#endif  /* Tda2xx */

        default:
            GT_0trace(utObj->traceMask, GT_ERR, " Invalid device ID!!\r\n");
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

static Int32 st_uartEnableUartPinMux(const st_UartUtObj *utObj, Int32 devId)
{
    Int32   retVal = BSP_SOK;

    switch (devId)
    {
        case ST_INSTANCE_ID_UART1:
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            /* Set pin mux */
            setPinmuxRegs(
                CTRL_CORE_PAD_UART1_RXD_UART1_RXD_MUXMODE_UART1_RXD_0,
                (UInt32) CTRL_CORE_PAD_UART1_RXD,
                DEFAULT);
            setPinmuxRegs(
                CTRL_CORE_PAD_UART1_TXD_UART1_TXD_MUXMODE_UART1_TXD_0,
                (UInt32) CTRL_CORE_PAD_UART1_TXD,
                DEFAULT);
            setPinmuxRegs(
                CTRL_CORE_PAD_UART1_CTSN_UART1_CTSN_MUXMODE_UART1_CTSN_0,
                (UInt32) CTRL_CORE_PAD_UART1_CTSN,
                DEFAULT);
            setPinmuxRegs(
                CTRL_CORE_PAD_UART1_RTSN_UART1_RTSN_MUXMODE_UART1_RTSN_0,
                (UInt32) CTRL_CORE_PAD_UART1_RTSN,
                DEFAULT);
#endif
#if defined (SOC_TDA3XX)
            Bsp_boardSetPinMux(BSP_DRV_ID_UART, devId, BSP_BOARD_MODE_DEFAULT);
#endif
            break;

        case ST_INSTANCE_ID_UART2:
#if defined (SOC_TDA3XX)
            Bsp_boardSetPinMux(BSP_DRV_ID_UART, devId, BSP_BOARD_MODE_DEFAULT);
#endif
            break;

        case ST_INSTANCE_ID_UART3:
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
            /* Set pin mux */
            setPinmuxRegs(
                CTRL_CORE_PAD_SPI2_SCLK_SPI2_SCLK_MUXMODE_UART3_RXD_1,
                (UInt32) CTRL_CORE_PAD_SPI2_SCLK,
                DEFAULT);
            setPinmuxRegs(
                CTRL_CORE_PAD_SPI2_D1_SPI2_D1_MUXMODE_UART3_TXD_1,
                (UInt32) CTRL_CORE_PAD_SPI2_D1,
                DEFAULT);
#endif
#if defined (SOC_TDA2EX)
            /* Set pin mux */
            setPinmuxRegs(
                CTRL_CORE_PAD_UART2_CTSN_UART2_CTSN_MUXMODE_UART3_RXD_2,
                (UInt32) CTRL_CORE_PAD_UART2_CTSN,
                (INPUTENABLE_BI | PULLTYPESELECT_UP));
            setPinmuxRegs(
                CTRL_CORE_PAD_UART2_RTSN_UART2_RTSN_MUXMODE_UART3_TXD_1,
                (UInt32) CTRL_CORE_PAD_UART2_RTSN,
                DEFAULT);
#endif
#if defined (SOC_TDA3XX)
            Bsp_boardSetPinMux(BSP_DRV_ID_UART, devId, BSP_BOARD_MODE_DEFAULT);
#endif
            break;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
        case ST_INSTANCE_ID_UART4:
            break;

        case ST_INSTANCE_ID_UART5:
            break;

        case ST_INSTANCE_ID_UART6:
            break;
#endif  /* Tda2xx || TI814x */

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        case ST_INSTANCE_ID_UART7:
            break;

        case ST_INSTANCE_ID_UART8:
            break;

        case ST_INSTANCE_ID_UART9:
            break;

        case ST_INSTANCE_ID_UART10:
            break;
#endif  /* Tda2xx */

        default:
            GT_0trace(utObj->traceMask, GT_ERR, " Invalid device ID!!\r\n");
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

static Int32 st_uartSelectUartOnBoard(const st_UartUtObj *utObj, Int32 devId)
{
    Int32   retVal = BSP_SOK;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    UInt8  regValue[2];
    UInt32 i2cInst, ioExpAddr, numRegs;
#endif

    switch (devId)
    {
        case ST_INSTANCE_ID_UART1:
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            /* Configuring U57 IO Expander for UART1 Input*/
            i2cInst   = BSP_DEVICE_I2C_INST_ID_0;
            ioExpAddr = BOARD_IO_EXP_I2C_ADDR_1;
            numRegs   = 2U;
            retVal =
                Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR, " I2C read failed!!\r\n");
            }

            /*
             * This selects UART1 signals over UART1
             * UART_SEL1_3 to 0
             */
            regValue[1U] &= (UInt8) (~((UInt8) BOARD_PCF8575_UART_SEL1_3));

            retVal +=
                Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR, " I2C write failed!!\r\n");
            }
#endif
#if defined (SOC_TDA3XX)
            Bsp_boardSelectDevice(BSP_DRV_ID_UART, devId);
#endif
            break;

        case ST_INSTANCE_ID_UART2:
#if defined (SOC_TDA3XX)
            Bsp_boardSelectDevice(BSP_DRV_ID_UART, devId);
#endif
            break;

        case ST_INSTANCE_ID_UART3:
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            /* Configuring U57 IO Expander for UART3 Input*/
            i2cInst   = BSP_DEVICE_I2C_INST_ID_0;
            ioExpAddr = BOARD_IO_EXP_I2C_ADDR_1;
            numRegs   = 2U;
            retVal =
                Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR, " I2C read failed!!\r\n");
            }

            /*
             * This selects UART3 signals over SPI2 and UART1
             * SEL_UART3_SPI2 to 0
             * UART_SEL1_3 to 1
             */
            regValue[1U] &= (UInt8) (~((UInt8) BOARD_PCF8575_SEL_UART3_SPI2));
            regValue[1U] |= (UInt8) (BOARD_PCF8575_UART_SEL1_3);

            retVal +=
                Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR, " I2C write failed!!\r\n");
            }
#endif
#if defined (SOC_TDA3XX)
            Bsp_boardSelectDevice(BSP_DRV_ID_UART, devId);
#endif
            break;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
        case ST_INSTANCE_ID_UART4:
            break;

        case ST_INSTANCE_ID_UART5:
            break;

        case ST_INSTANCE_ID_UART6:
            break;
#endif  /* Tda2xx || TI814x */

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        case ST_INSTANCE_ID_UART7:
            break;

        case ST_INSTANCE_ID_UART8:
            break;

        case ST_INSTANCE_ID_UART9:
            break;

        case ST_INSTANCE_ID_UART10:
            break;
#endif  /* Tda2xx */

        default:
            GT_0trace(utObj->traceMask, GT_ERR, " Invalid device ID!!\r\n");
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
static Int32 setPinmuxRegs(UInt32 mode_index, UInt32 offset, UInt32 pupd_info)
{
    UInt32 muxVal;

    if (offset != (UInt32) 0xffff)
    {
        muxVal  = HW_RD_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset);
        muxVal &= ~(0x0FU);
        muxVal |= (mode_index & 0x0000000FU);

        if (pupd_info != (UInt32) DEFAULT)
        {
            muxVal &= ~(0x70000U);
            muxVal |= ((pupd_info & 0x07U) << 16U);
        }
        HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset, muxVal);
    }

    return (BSP_SOK);
}
#endif
