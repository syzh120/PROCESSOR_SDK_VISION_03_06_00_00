/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_ctrl_core_pad_io.h
 *
 *  \brief  Register-level header file for CTRL_CORE_PAD_IO
 *
**/

#ifndef HW_CTRL_CORE_PAD_IO_H_
#define HW_CTRL_CORE_PAD_IO_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define CTRL_CORE_PAD_IO_GPMC_CLK                                   (uint32_t)(0x0U)
#define CTRL_CORE_PAD_IO_GPMC_BEN0                                  (uint32_t)(0x4U)
#define CTRL_CORE_PAD_IO_GPMC_BEN1                                  (uint32_t)(0x8U)
#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE                              (uint32_t)(0xcU)
#define CTRL_CORE_PAD_IO_GPMC_OEN_REN                               (uint32_t)(0x10U)
#define CTRL_CORE_PAD_IO_GPMC_WEN                                   (uint32_t)(0x14U)
#define CTRL_CORE_PAD_IO_GPMC_CS0                                   (uint32_t)(0x18U)
#define CTRL_CORE_PAD_IO_GPMC_CS1                                   (uint32_t)(0x1cU)
#define CTRL_CORE_PAD_IO_GPMC_CS2                                   (uint32_t)(0x20U)
#define CTRL_CORE_PAD_IO_GPMC_CS3                                   (uint32_t)(0x24U)
#define CTRL_CORE_PAD_IO_GPMC_CS4                                   (uint32_t)(0x28U)
#define CTRL_CORE_PAD_IO_GPMC_CS5                                   (uint32_t)(0x2cU)
#define CTRL_CORE_PAD_IO_GPMC_CS6                                   (uint32_t)(0x30U)
#define CTRL_CORE_PAD_IO_GPMC_WAIT0                                 (uint32_t)(0x34U)
#define CTRL_CORE_PAD_IO_GPMC_AD0                                   (uint32_t)(0x38U)
#define CTRL_CORE_PAD_IO_GPMC_AD1                                   (uint32_t)(0x3cU)
#define CTRL_CORE_PAD_IO_GPMC_AD2                                   (uint32_t)(0x40U)
#define CTRL_CORE_PAD_IO_GPMC_AD3                                   (uint32_t)(0x44U)
#define CTRL_CORE_PAD_IO_GPMC_AD4                                   (uint32_t)(0x48U)
#define CTRL_CORE_PAD_IO_GPMC_AD5                                   (uint32_t)(0x4cU)
#define CTRL_CORE_PAD_IO_GPMC_AD6                                   (uint32_t)(0x50U)
#define CTRL_CORE_PAD_IO_GPMC_AD7                                   (uint32_t)(0x54U)
#define CTRL_CORE_PAD_IO_GPMC_AD8                                   (uint32_t)(0x58U)
#define CTRL_CORE_PAD_IO_GPMC_AD9                                   (uint32_t)(0x5cU)
#define CTRL_CORE_PAD_IO_GPMC_AD10                                  (uint32_t)(0x60U)
#define CTRL_CORE_PAD_IO_GPMC_AD11                                  (uint32_t)(0x64U)
#define CTRL_CORE_PAD_IO_GPMC_AD12                                  (uint32_t)(0x68U)
#define CTRL_CORE_PAD_IO_GPMC_AD13                                  (uint32_t)(0x6cU)
#define CTRL_CORE_PAD_IO_GPMC_AD14                                  (uint32_t)(0x70U)
#define CTRL_CORE_PAD_IO_GPMC_AD15                                  (uint32_t)(0x74U)
#define CTRL_CORE_PAD_IO_VIN1A_CLK0                                 (uint32_t)(0x78U)
#define CTRL_CORE_PAD_IO_VIN1A_DE0                                  (uint32_t)(0x7cU)
#define CTRL_CORE_PAD_IO_VIN1A_FLD0                                 (uint32_t)(0x80U)
#define CTRL_CORE_PAD_IO_VIN1A_HSYNC0                               (uint32_t)(0x84U)
#define CTRL_CORE_PAD_IO_VIN1A_VSYNC0                               (uint32_t)(0x88U)
#define CTRL_CORE_PAD_IO_VIN1A_D0                                   (uint32_t)(0x8cU)
#define CTRL_CORE_PAD_IO_VIN1A_D1                                   (uint32_t)(0x90U)
#define CTRL_CORE_PAD_IO_VIN1A_D2                                   (uint32_t)(0x94U)
#define CTRL_CORE_PAD_IO_VIN1A_D3                                   (uint32_t)(0x98U)
#define CTRL_CORE_PAD_IO_VIN1A_D4                                   (uint32_t)(0x9cU)
#define CTRL_CORE_PAD_IO_VIN1A_D5                                   (uint32_t)(0xa0U)
#define CTRL_CORE_PAD_IO_VIN1A_D6                                   (uint32_t)(0xa4U)
#define CTRL_CORE_PAD_IO_VIN1A_D7                                   (uint32_t)(0xa8U)
#define CTRL_CORE_PAD_IO_VIN1A_D8                                   (uint32_t)(0xacU)
#define CTRL_CORE_PAD_IO_VIN1A_D9                                   (uint32_t)(0xb0U)
#define CTRL_CORE_PAD_IO_VIN1A_D10                                  (uint32_t)(0xb4U)
#define CTRL_CORE_PAD_IO_VIN1A_D11                                  (uint32_t)(0xb8U)
#define CTRL_CORE_PAD_IO_VIN1A_D12                                  (uint32_t)(0xbcU)
#define CTRL_CORE_PAD_IO_VIN1A_D13                                  (uint32_t)(0xc0U)
#define CTRL_CORE_PAD_IO_VIN1A_D14                                  (uint32_t)(0xc4U)
#define CTRL_CORE_PAD_IO_VIN1A_D15                                  (uint32_t)(0xc8U)
#define CTRL_CORE_PAD_IO_VIN2A_CLK0                                 (uint32_t)(0xccU)
#define CTRL_CORE_PAD_IO_VIN2A_DE0                                  (uint32_t)(0xd0U)
#define CTRL_CORE_PAD_IO_VIN2A_FLD0                                 (uint32_t)(0xd4U)
#define CTRL_CORE_PAD_IO_VOUT1_CLK                                  (uint32_t)(0xd8U)
#define CTRL_CORE_PAD_IO_VOUT1_DE                                   (uint32_t)(0xdcU)
#define CTRL_CORE_PAD_IO_VOUT1_FLD                                  (uint32_t)(0xe0U)
#define CTRL_CORE_PAD_IO_VOUT1_HSYNC                                (uint32_t)(0xe4U)
#define CTRL_CORE_PAD_IO_VOUT1_VSYNC                                (uint32_t)(0xe8U)
#define CTRL_CORE_PAD_IO_VOUT1_D0                                   (uint32_t)(0xecU)
#define CTRL_CORE_PAD_IO_VOUT1_D1                                   (uint32_t)(0xf0U)
#define CTRL_CORE_PAD_IO_VOUT1_D2                                   (uint32_t)(0xf4U)
#define CTRL_CORE_PAD_IO_VOUT1_D3                                   (uint32_t)(0xf8U)
#define CTRL_CORE_PAD_IO_VOUT1_D4                                   (uint32_t)(0xfcU)
#define CTRL_CORE_PAD_IO_VOUT1_D5                                   (uint32_t)(0x100U)
#define CTRL_CORE_PAD_IO_VOUT1_D6                                   (uint32_t)(0x104U)
#define CTRL_CORE_PAD_IO_VOUT1_D7                                   (uint32_t)(0x108U)
#define CTRL_CORE_PAD_IO_VOUT1_D8                                   (uint32_t)(0x10cU)
#define CTRL_CORE_PAD_IO_VOUT1_D9                                   (uint32_t)(0x110U)
#define CTRL_CORE_PAD_IO_VOUT1_D10                                  (uint32_t)(0x114U)
#define CTRL_CORE_PAD_IO_VOUT1_D11                                  (uint32_t)(0x118U)
#define CTRL_CORE_PAD_IO_VOUT1_D12                                  (uint32_t)(0x11cU)
#define CTRL_CORE_PAD_IO_VOUT1_D13                                  (uint32_t)(0x120U)
#define CTRL_CORE_PAD_IO_VOUT1_D14                                  (uint32_t)(0x124U)
#define CTRL_CORE_PAD_IO_VOUT1_D15                                  (uint32_t)(0x128U)
#define CTRL_CORE_PAD_IO_VOUT1_D16                                  (uint32_t)(0x12cU)
#define CTRL_CORE_PAD_IO_VOUT1_D17                                  (uint32_t)(0x130U)
#define CTRL_CORE_PAD_IO_VOUT1_D18                                  (uint32_t)(0x134U)
#define CTRL_CORE_PAD_IO_VOUT1_D19                                  (uint32_t)(0x138U)
#define CTRL_CORE_PAD_IO_VOUT1_D20                                  (uint32_t)(0x13cU)
#define CTRL_CORE_PAD_IO_VOUT1_D21                                  (uint32_t)(0x140U)
#define CTRL_CORE_PAD_IO_VOUT1_D22                                  (uint32_t)(0x144U)
#define CTRL_CORE_PAD_IO_VOUT1_D23                                  (uint32_t)(0x148U)
#define CTRL_CORE_PAD_IO_DCAN2_TX                                   (uint32_t)(0x14cU)
#define CTRL_CORE_PAD_IO_DCAN2_RX                                   (uint32_t)(0x150U)
#define CTRL_CORE_PAD_IO_MDIO_MCLK                                  (uint32_t)(0x154U)
#define CTRL_CORE_PAD_IO_MDIO_D                                     (uint32_t)(0x158U)
#define CTRL_CORE_PAD_IO_RGMII0_TXC                                 (uint32_t)(0x15cU)
#define CTRL_CORE_PAD_IO_RGMII0_TXCTL                               (uint32_t)(0x160U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD3                                (uint32_t)(0x164U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD2                                (uint32_t)(0x168U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD1                                (uint32_t)(0x16cU)
#define CTRL_CORE_PAD_IO_RGMII0_TXD0                                (uint32_t)(0x170U)
#define CTRL_CORE_PAD_IO_RGMII0_RXC                                 (uint32_t)(0x174U)
#define CTRL_CORE_PAD_IO_RGMII0_RXCTL                               (uint32_t)(0x178U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD3                                (uint32_t)(0x17cU)
#define CTRL_CORE_PAD_IO_RGMII0_RXD2                                (uint32_t)(0x180U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD1                                (uint32_t)(0x184U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD0                                (uint32_t)(0x188U)
#define CTRL_CORE_PAD_IO_XREF_CLK0                                  (uint32_t)(0x18cU)
#define CTRL_CORE_PAD_IO_SPI1_SCLK                                  (uint32_t)(0x190U)
#define CTRL_CORE_PAD_IO_SPI1_D1                                    (uint32_t)(0x194U)
#define CTRL_CORE_PAD_IO_SPI1_D0                                    (uint32_t)(0x198U)
#define CTRL_CORE_PAD_IO_SPI1_CS0                                   (uint32_t)(0x19cU)
#define CTRL_CORE_PAD_IO_SPI1_CS1                                   (uint32_t)(0x1a0U)
#define CTRL_CORE_PAD_IO_SPI2_SCLK                                  (uint32_t)(0x1a4U)
#define CTRL_CORE_PAD_IO_SPI2_D1                                    (uint32_t)(0x1a8U)
#define CTRL_CORE_PAD_IO_SPI2_D0                                    (uint32_t)(0x1acU)
#define CTRL_CORE_PAD_IO_SPI2_CS0                                   (uint32_t)(0x1b0U)
#define CTRL_CORE_PAD_IO_DCAN1_TX                                   (uint32_t)(0x1b4U)
#define CTRL_CORE_PAD_IO_DCAN1_RX                                   (uint32_t)(0x1b8U)
#define CTRL_CORE_PAD_IO_UART1_RXD                                  (uint32_t)(0x1bcU)
#define CTRL_CORE_PAD_IO_UART1_TXD                                  (uint32_t)(0x1c0U)
#define CTRL_CORE_PAD_IO_UART1_CTSN                                 (uint32_t)(0x1c4U)
#define CTRL_CORE_PAD_IO_UART1_RTSN                                 (uint32_t)(0x1c8U)
#define CTRL_CORE_PAD_IO_UART2_RXD                                  (uint32_t)(0x1ccU)
#define CTRL_CORE_PAD_IO_UART2_TXD                                  (uint32_t)(0x1d0U)
#define CTRL_CORE_PAD_IO_UART2_CTSN                                 (uint32_t)(0x1d4U)
#define CTRL_CORE_PAD_IO_UART2_RTSN                                 (uint32_t)(0x1d8U)
#define CTRL_CORE_PAD_IO_I2C1_SDA                                   (uint32_t)(0x1dcU)
#define CTRL_CORE_PAD_IO_I2C1_SCL                                   (uint32_t)(0x1e0U)
#define CTRL_CORE_PAD_IO_I2C2_SDA                                   (uint32_t)(0x1e4U)
#define CTRL_CORE_PAD_IO_I2C2_SCL                                   (uint32_t)(0x1e8U)
#define CTRL_CORE_PAD_IO_TMS                                        (uint32_t)(0x1ecU)
#define CTRL_CORE_PAD_IO_TDI                                        (uint32_t)(0x1f0U)
#define CTRL_CORE_PAD_IO_TDO                                        (uint32_t)(0x1f4U)
#define CTRL_CORE_PAD_IO_TCLK                                       (uint32_t)(0x1f8U)
#define CTRL_CORE_PAD_IO_TRSTN                                      (uint32_t)(0x1fcU)
#define CTRL_CORE_PAD_IO_RTCK                                       (uint32_t)(0x200U)
#define CTRL_CORE_PAD_IO_EMU0                                       (uint32_t)(0x204U)
#define CTRL_CORE_PAD_IO_EMU1                                       (uint32_t)(0x208U)
#define CTRL_CORE_PAD_IO_RESETN                                     (uint32_t)(0x20cU)
#define CTRL_CORE_PAD_IO_NMIN                                       (uint32_t)(0x210U)
#define CTRL_CORE_PAD_IO_RSTOUTN                                    (uint32_t)(0x214U)
#define CTRL_CORE_PAD_IO_SMA_SW_10                                  (uint32_t)(0x1C68U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CTRL_CORE_PAD_IO_GPMC_CLK_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_CLK_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_CLK_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_CLK_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_CLK_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_CLK_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_CLK_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_CLK_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_CLK_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_CLK_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_CLK_MUXMODE_RGMII1_TXC_1                                  (1U)

#define CTRL_CORE_PAD_IO_GPMC_BEN0_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_GPMC_BEN0_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_BEN0_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_GPMC_BEN0_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_BEN0_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_GPMC_BEN0_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_BEN0_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_GPMC_BEN0_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_BEN0_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_GPMC_BEN0_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_BEN0_MUXMODE_GPMC_BEN0_0                                  (0U)
#define CTRL_CORE_PAD_IO_GPMC_BEN0_MUXMODE_RGMII1_TXCTL_1                               (1U)

#define CTRL_CORE_PAD_IO_GPMC_BEN1_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_GPMC_BEN1_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_BEN1_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_GPMC_BEN1_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_BEN1_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_GPMC_BEN1_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_BEN1_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_GPMC_BEN1_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_BEN1_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_GPMC_BEN1_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_BEN1_MUXMODE_RGMII1_TXD3_1                                (1U)

#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_SLEWCONTROL_SHIFT                                (19U)
#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_SLEWCONTROL_MASK                                 (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_INPUTENABLE_SHIFT                                (18U)
#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_INPUTENABLE_MASK                                 (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_PULLTYPESELECT_SHIFT                             (17U)
#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_PULLTYPESELECT_MASK                              (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_PULLUDENABLE_SHIFT                               (16U)
#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_PULLUDENABLE_MASK                                (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_MUXMODE_SHIFT                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_MUXMODE_MASK                                     (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_MUXMODE_GPMC_ADVN_ALE_0                          (0U)
#define CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_MUXMODE_RGMII1_TXD2_1                            (1U)

#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_SLEWCONTROL_SHIFT                                 (19U)
#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_SLEWCONTROL_MASK                                  (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_INPUTENABLE_SHIFT                                 (18U)
#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_INPUTENABLE_MASK                                  (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_PULLTYPESELECT_SHIFT                              (17U)
#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_PULLTYPESELECT_MASK                               (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_PULLUDENABLE_SHIFT                                (16U)
#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_PULLUDENABLE_MASK                                 (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_MUXMODE_SHIFT                                     (0U)
#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_MUXMODE_MASK                                      (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_MUXMODE_GPMC_OEN_REN_0                            (0U)
#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_MUXMODE_RGMII1_TXD1_1                             (1U)
#define CTRL_CORE_PAD_IO_GPMC_OEN_REN_MUXMODE_GPIO1_14                                  (14U)

#define CTRL_CORE_PAD_IO_GPMC_WEN_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_WEN_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_WEN_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_WEN_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_WEN_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_WEN_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_WEN_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_WEN_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_WEN_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_WEN_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_WEN_MUXMODE_GPMC_WEN_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_WEN_MUXMODE_RGMII1_TXD0_1                                 (1U)
#define CTRL_CORE_PAD_IO_GPMC_WEN_MUXMODE_GPIO1_5                                       (14U)

#define CTRL_CORE_PAD_IO_GPMC_CS0_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_CS0_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_CS0_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_CS0_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_CS0_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_CS0_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_CS0_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_CS0_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_CS0_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS0_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_CS0_MUXMODE_GPMC_CS0_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS0_MUXMODE_RGMII1_RXCTL_1                                (1U)
#define CTRL_CORE_PAD_IO_GPMC_CS0_MUXMODE_GPIO1_6                                       (14U)

#define CTRL_CORE_PAD_IO_GPMC_CS1_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_CS1_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_CS1_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_CS1_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_CS1_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_CS1_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_CS1_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_CS1_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_CS1_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS1_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_CS1_MUXMODE_GPMC_CS1_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS1_MUXMODE_QSPI1_CS0_1                                   (1U)
#define CTRL_CORE_PAD_IO_GPMC_CS1_MUXMODE_GPIO1_7_14                                    (14U)

#define CTRL_CORE_PAD_IO_GPMC_CS2_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_CS2_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_CS2_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_CS2_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_CS2_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_CS2_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_CS2_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_CS2_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_CS2_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS2_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_CS2_MUXMODE_GPMC_CS2_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS2_MUXMODE_QSPI1_D3_1                                    (1U)
#define CTRL_CORE_PAD_IO_GPMC_CS2_MUXMODE_GPIO1_8_14                                    (14U)

#define CTRL_CORE_PAD_IO_GPMC_CS3_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_CS3_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_CS3_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_CS3_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_CS3_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_CS3_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_CS3_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_CS3_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_CS3_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS3_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_CS3_MUXMODE_GPMC_CS3_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS3_MUXMODE_QSPI1_D2_1                                    (1U)
#define CTRL_CORE_PAD_IO_GPMC_CS3_MUXMODE_GPIO1_9_14                                    (14U)

#define CTRL_CORE_PAD_IO_GPMC_CS4_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_CS4_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_CS4_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_CS4_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_CS4_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_CS4_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_CS4_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_CS4_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_CS4_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS4_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_CS4_MUXMODE_GPMC_CS4_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS4_MUXMODE_QSPI1_D1_1                                    (1U)
#define CTRL_CORE_PAD_IO_GPMC_CS4_MUXMODE_GPIO1_10_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_CS5_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_CS5_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_CS5_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_CS5_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_CS5_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_CS5_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_CS5_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_CS5_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_CS5_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS5_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_CS5_MUXMODE_GPMC_CS5_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS5_MUXMODE_QSPI1_D0_1                                    (1U)
#define CTRL_CORE_PAD_IO_GPMC_CS5_MUXMODE_GPIO1_11_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_CS6_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_CS6_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_CS6_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_CS6_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_CS6_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_CS6_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_CS6_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_CS6_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_CS6_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS6_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_CS6_MUXMODE_GPMC_CS6_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_CS6_MUXMODE_QSPI1_SCLK_1                                  (1U)
#define CTRL_CORE_PAD_IO_GPMC_CS6_MUXMODE_GPIO1_12_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_WAIT0_SLEWCONTROL_SHIFT                                   (19U)
#define CTRL_CORE_PAD_IO_GPMC_WAIT0_SLEWCONTROL_MASK                                    (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_WAIT0_INPUTENABLE_SHIFT                                   (18U)
#define CTRL_CORE_PAD_IO_GPMC_WAIT0_INPUTENABLE_MASK                                    (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_WAIT0_PULLTYPESELECT_SHIFT                                (17U)
#define CTRL_CORE_PAD_IO_GPMC_WAIT0_PULLTYPESELECT_MASK                                 (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_WAIT0_PULLUDENABLE_SHIFT                                  (16U)
#define CTRL_CORE_PAD_IO_GPMC_WAIT0_PULLUDENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_WAIT0_MUXMODE_SHIFT                                       (0U)
#define CTRL_CORE_PAD_IO_GPMC_WAIT0_MUXMODE_MASK                                        (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_WAIT0_MUXMODE_GPMC_WAIT0_0                                (0U)
#define CTRL_CORE_PAD_IO_GPMC_WAIT0_MUXMODE_RGMII1_RXD3_1                               (1U)
#define CTRL_CORE_PAD_IO_GPMC_WAIT0_MUXMODE_QSPI1_RTCLK_2                               (2U)

#define CTRL_CORE_PAD_IO_GPMC_AD0_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD0_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD0_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD0_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD0_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD0_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD0_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD0_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD0_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD0_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD0_MUXMODE_GPMC_AD0_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD0_MUXMODE_RGMII1_RXD2_1                                 (1U)
#define CTRL_CORE_PAD_IO_GPMC_AD0_MUXMODE_GPIO1_14_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_AD1_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD1_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD1_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD1_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD1_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD1_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD1_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD1_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD1_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD1_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD1_MUXMODE_GPMC_AD1_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD1_MUXMODE_RGMII1_RXD1_1                                 (1U)
#define CTRL_CORE_PAD_IO_GPMC_AD1_MUXMODE_GPIO1_15_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_AD2_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD2_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD2_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD2_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD2_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD2_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD2_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD2_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD2_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD2_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD2_MUXMODE_GPMC_AD2_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD2_MUXMODE_RGMII1_RXD0_1                                 (1U)
#define CTRL_CORE_PAD_IO_GPMC_AD2_MUXMODE_GPIO1_16_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_AD3_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD3_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD3_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD3_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD3_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD3_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD3_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD3_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD3_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD3_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD3_MUXMODE_GPMC_AD3_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD3_MUXMODE_QSPI1_RTCLK_1                                 (1U)
#define CTRL_CORE_PAD_IO_GPMC_AD3_MUXMODE_GPIO1_17_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_AD4_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD4_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD4_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD4_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD4_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD4_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD4_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD4_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD4_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD4_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD4_MUXMODE_GPMC_AD4_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD4_MUXMODE_CAM_STROBE_1                                  (1U)
#define CTRL_CORE_PAD_IO_GPMC_AD4_MUXMODE_GPIO1_18_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_AD5_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD5_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD5_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD5_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD5_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD5_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD5_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD5_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD5_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD5_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD5_MUXMODE_GPMC_AD5_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD5_MUXMODE_UART2_TXD_2                                   (2U)
#define CTRL_CORE_PAD_IO_GPMC_AD5_MUXMODE_TIMER6_3                                      (3U)
#define CTRL_CORE_PAD_IO_GPMC_AD5_MUXMODE_SPI3_D1_4                                     (4U)
#define CTRL_CORE_PAD_IO_GPMC_AD5_MUXMODE_GPIO1_19_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_AD6_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD6_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD6_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD6_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD6_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD6_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD6_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD6_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD6_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD6_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD6_MUXMODE_GPMC_AD6_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD6_MUXMODE_UART2_RXD_2                                   (2U)
#define CTRL_CORE_PAD_IO_GPMC_AD6_MUXMODE_TIMER5_3                                      (3U)
#define CTRL_CORE_PAD_IO_GPMC_AD6_MUXMODE_SPI3_D0_4                                     (4U)
#define CTRL_CORE_PAD_IO_GPMC_AD6_MUXMODE_GPIO1_20_14                                   (14U)


#define CTRL_CORE_PAD_IO_GPMC_AD7_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD7_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD7_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD7_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD7_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD7_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD7_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD7_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD7_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD7_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD7_MUXMODE_GPMC_AD7_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD7_MUXMODE_CAM_SHUTTER_1                                 (1U)
#define CTRL_CORE_PAD_IO_GPMC_AD7_MUXMODE_TIMER4_3                                      (3U)
#define CTRL_CORE_PAD_IO_GPMC_AD7_MUXMODE_SPI3_SCLK_4                                   (4U)
#define CTRL_CORE_PAD_IO_GPMC_AD7_MUXMODE_GPIO1_21_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_AD8_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD8_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD8_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD8_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD8_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD8_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD8_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD8_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD8_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD8_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD8_MUXMODE_GPMC_AD8_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD8_MUXMODE_TIMER7_3                                      (3U)
#define CTRL_CORE_PAD_IO_GPMC_AD8_MUXMODE_SPI3_CS0_4                                    (4U)
#define CTRL_CORE_PAD_IO_GPMC_AD8_MUXMODE_GPIO1_22_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_AD9_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD9_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD9_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD9_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD9_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD9_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD9_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD9_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD9_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD9_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD9_MUXMODE_GPMC_AD9_0                                    (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD9_MUXMODE_ECAP1_IN_PWM1_OUT_3                           (3U)
#define CTRL_CORE_PAD_IO_GPMC_AD9_MUXMODE_SPI3_CS1_4                                    (4U)
#define CTRL_CORE_PAD_IO_GPMC_AD9_MUXMODE_GPIO1_23_14                                   (14U)

#define CTRL_CORE_PAD_IO_GPMC_AD10_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD10_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD10_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD10_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD10_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD10_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD10_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD10_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD10_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD10_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD10_MUXMODE_GPMC_AD10_0                                  (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD10_MUXMODE_TIMER2_3                                     (3U)
#define CTRL_CORE_PAD_IO_GPMC_AD10_MUXMODE_GPIO1_24_14                                  (14U)

#define CTRL_CORE_PAD_IO_GPMC_AD11_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD11_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD11_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD11_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD11_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD11_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD11_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD11_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD11_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD11_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD11_MUXMODE_GPMC_AD11_0                                  (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD11_MUXMODE_TIMER3_3                                     (3U)
#define CTRL_CORE_PAD_IO_GPMC_AD11_MUXMODE_GPIO1_25_14                                  (14U)

#define CTRL_CORE_PAD_IO_GPMC_AD12_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD12_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD12_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD12_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD12_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD12_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD12_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD12_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD12_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD12_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD12_MUXMODE_GPMC_AD12_0                                  (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD12_MUXMODE_RMII1_RXER_2                                 (2U)
#define CTRL_CORE_PAD_IO_GPMC_AD12_MUXMODE_MII1_RXER_3                                  (3U)
#define CTRL_CORE_PAD_IO_GPMC_AD12_MUXMODE_GPIO1_26_14                                  (EU)
#define CTRL_CORE_PAD_IO_GPMC_AD12_MUXMODE_SYSBOOT12_15                                 (FU)

#define CTRL_CORE_PAD_IO_GPMC_AD13_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD13_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD13_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD13_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD13_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD13_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD13_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD13_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD13_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD13_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD13_MUXMODE_GPMC_AD13_0                                  (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD13_MUXMODE_RGMII1_RXC_1                                 (1U)

#define CTRL_CORE_PAD_IO_GPMC_AD14_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD14_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD14_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD14_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD14_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD14_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD14_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD14_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD14_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD14_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD14_MUXMODE_GPMC_AD14_0                                  (0U)

#define CTRL_CORE_PAD_IO_GPMC_AD15_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_GPMC_AD15_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_GPMC_AD15_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_GPMC_AD15_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_GPMC_AD15_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_GPMC_AD15_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_GPMC_AD15_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_GPMC_AD15_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_GPMC_AD15_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_GPMC_AD15_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_GPMC_AD15_MUXMODE_GPMC_AD15_0                                  (0U)

#define CTRL_CORE_PAD_IO_VIN1A_CLK0_SLEWCONTROL_SHIFT                                   (19U)
#define CTRL_CORE_PAD_IO_VIN1A_CLK0_SLEWCONTROL_MASK                                    (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_CLK0_INPUTENABLE_SHIFT                                   (18U)
#define CTRL_CORE_PAD_IO_VIN1A_CLK0_INPUTENABLE_MASK                                    (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_CLK0_PULLTYPESELECT_SHIFT                                (17U)
#define CTRL_CORE_PAD_IO_VIN1A_CLK0_PULLTYPESELECT_MASK                                 (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_CLK0_PULLUDENABLE_SHIFT                                  (16U)
#define CTRL_CORE_PAD_IO_VIN1A_CLK0_PULLUDENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_CLK0_MUXMODE_SHIFT                                       (0U)
#define CTRL_CORE_PAD_IO_VIN1A_CLK0_MUXMODE_MASK                                        (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN1A_DE0_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VIN1A_DE0_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_DE0_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VIN1A_DE0_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_DE0_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VIN1A_DE0_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_DE0_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VIN1A_DE0_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_DE0_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VIN1A_DE0_MUXMODE_MASK                                         (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN1A_FLD0_SLEWCONTROL_SHIFT                                   (19U)
#define CTRL_CORE_PAD_IO_VIN1A_FLD0_SLEWCONTROL_MASK                                    (0x00080000U)
#define CTRL_CORE_PAD_IO_VIN1A_FLD0_MUXMODE_CLKOUT2                                     (4U)

#define CTRL_CORE_PAD_IO_VIN1A_FLD0_INPUTENABLE_SHIFT                                   (18U)
#define CTRL_CORE_PAD_IO_VIN1A_FLD0_INPUTENABLE_MASK                                    (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_FLD0_PULLTYPESELECT_SHIFT                                (17U)
#define CTRL_CORE_PAD_IO_VIN1A_FLD0_PULLTYPESELECT_MASK                                 (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_FLD0_PULLUDENABLE_SHIFT                                  (16U)
#define CTRL_CORE_PAD_IO_VIN1A_FLD0_PULLUDENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_FLD0_MUXMODE_SHIFT                                       (0U)
#define CTRL_CORE_PAD_IO_VIN1A_FLD0_MUXMODE_MASK                                        (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN1A_HSYNC0_SLEWCONTROL_SHIFT                                 (19U)
#define CTRL_CORE_PAD_IO_VIN1A_HSYNC0_SLEWCONTROL_MASK                                  (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_HSYNC0_INPUTENABLE_SHIFT                                 (18U)
#define CTRL_CORE_PAD_IO_VIN1A_HSYNC0_INPUTENABLE_MASK                                  (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_HSYNC0_PULLTYPESELECT_SHIFT                              (17U)
#define CTRL_CORE_PAD_IO_VIN1A_HSYNC0_PULLTYPESELECT_MASK                               (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_HSYNC0_PULLUDENABLE_SHIFT                                (16U)
#define CTRL_CORE_PAD_IO_VIN1A_HSYNC0_PULLUDENABLE_MASK                                 (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_HSYNC0_MUXMODE_SHIFT                                     (0U)
#define CTRL_CORE_PAD_IO_VIN1A_HSYNC0_MUXMODE_MASK                                      (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN1A_VSYNC0_SLEWCONTROL_SHIFT                                 (19U)
#define CTRL_CORE_PAD_IO_VIN1A_VSYNC0_SLEWCONTROL_MASK                                  (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_VSYNC0_INPUTENABLE_SHIFT                                 (18U)
#define CTRL_CORE_PAD_IO_VIN1A_VSYNC0_INPUTENABLE_MASK                                  (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_VSYNC0_PULLTYPESELECT_SHIFT                              (17U)
#define CTRL_CORE_PAD_IO_VIN1A_VSYNC0_PULLTYPESELECT_MASK                               (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_VSYNC0_PULLUDENABLE_SHIFT                                (16U)
#define CTRL_CORE_PAD_IO_VIN1A_VSYNC0_PULLUDENABLE_MASK                                 (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_VSYNC0_MUXMODE_SHIFT                                     (0U)
#define CTRL_CORE_PAD_IO_VIN1A_VSYNC0_MUXMODE_MASK                                      (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN1A_D0_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D0_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D0_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D0_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D0_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D0_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D0_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D0_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D0_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D0_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN1A_D1_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D1_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D1_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D1_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D1_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D1_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D1_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D1_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D1_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D1_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN1A_D2_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D2_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D2_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D2_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D2_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D2_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D2_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D2_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D2_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D2_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_VIN1A_D2_MUXMODE_GPIO2_5                                       (14U)

#define CTRL_CORE_PAD_IO_VIN1A_D3_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D3_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D3_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D3_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D3_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D3_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D3_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D3_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D3_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D3_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_VIN1A_D3_MUXMODE_GPIO2_6                                       (14U)

#define CTRL_CORE_PAD_IO_VIN1A_D4_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D4_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D4_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D4_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D4_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D4_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D4_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D4_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D4_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D4_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_VIN1A_D4_MUXMODE_GPIO2_7                                       (14U)

#define CTRL_CORE_PAD_IO_VIN1A_D5_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D5_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D5_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D5_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D5_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D5_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D5_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D5_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D5_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D5_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN1A_D6_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D6_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D6_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D6_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D6_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D6_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D6_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D6_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D6_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D6_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN1A_D7_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D7_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D7_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D7_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D7_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D7_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D7_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D7_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D7_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D7_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN1A_D8_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D8_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D8_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D8_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D8_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D8_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D8_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D8_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D8_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D8_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_VIN1A_D8_MUXMODE_GPMC_A8_3                                     (3U)

#define CTRL_CORE_PAD_IO_VIN1A_D9_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D9_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D9_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D9_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D9_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D9_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D9_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D9_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D9_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D9_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_VIN1A_D9_MUXMODE_GPMC_A9_3                                     (3U)

#define CTRL_CORE_PAD_IO_VIN1A_D10_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D10_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D10_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D10_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D10_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D10_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D10_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D10_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D10_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D10_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VIN1A_D10_MUXMODE_GPMC_A10_3                                   (3U)

#define CTRL_CORE_PAD_IO_VIN1A_D11_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D11_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D11_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D11_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D11_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D11_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D11_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D11_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D11_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D11_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VIN1A_D11_MUXMODE_GPMC_A11_3                                   (3U)

#define CTRL_CORE_PAD_IO_VIN1A_D12_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D12_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D12_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D12_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D12_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D12_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D12_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D12_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D12_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D12_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VIN1A_D12_MUXMODE_GPMC_A12_3                                   (3U)

#define CTRL_CORE_PAD_IO_VIN1A_D13_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D13_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D13_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D13_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D13_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D13_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D13_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D13_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D13_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D13_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VIN1A_D13_MUXMODE_GPMC_A13_3                                   (3U)

#define CTRL_CORE_PAD_IO_VIN1A_D14_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D14_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D14_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D14_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D14_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D14_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D14_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D14_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D14_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D14_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VIN1A_D14_MUXMODE_GPMC_A14_3                                   (3U)

#define CTRL_CORE_PAD_IO_VIN1A_D15_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VIN1A_D15_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN1A_D15_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VIN1A_D15_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN1A_D15_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VIN1A_D15_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN1A_D15_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VIN1A_D15_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN1A_D15_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VIN1A_D15_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VIN1A_D15_MUXMODE_GPMC_A15_3                                   (3U)

#define CTRL_CORE_PAD_IO_VIN2A_CLK0_SLEWCONTROL_SHIFT                                   (19U)
#define CTRL_CORE_PAD_IO_VIN2A_CLK0_SLEWCONTROL_MASK                                    (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN2A_CLK0_INPUTENABLE_SHIFT                                   (18U)
#define CTRL_CORE_PAD_IO_VIN2A_CLK0_INPUTENABLE_MASK                                    (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN2A_CLK0_PULLTYPESELECT_SHIFT                                (17U)
#define CTRL_CORE_PAD_IO_VIN2A_CLK0_PULLTYPESELECT_MASK                                 (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN2A_CLK0_PULLUDENABLE_SHIFT                                  (16U)
#define CTRL_CORE_PAD_IO_VIN2A_CLK0_PULLUDENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN2A_CLK0_MUXMODE_SHIFT                                       (0U)
#define CTRL_CORE_PAD_IO_VIN2A_CLK0_MUXMODE_MASK                                        (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN2A_DE0_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VIN2A_DE0_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN2A_DE0_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VIN2A_DE0_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN2A_DE0_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VIN2A_DE0_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN2A_DE0_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VIN2A_DE0_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN2A_DE0_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VIN2A_DE0_MUXMODE_MASK                                         (0x0000000fU)

#define CTRL_CORE_PAD_IO_VIN2A_FLD0_SLEWCONTROL_SHIFT                                   (19U)
#define CTRL_CORE_PAD_IO_VIN2A_FLD0_SLEWCONTROL_MASK                                    (0x00080000U)

#define CTRL_CORE_PAD_IO_VIN2A_FLD0_INPUTENABLE_SHIFT                                   (18U)
#define CTRL_CORE_PAD_IO_VIN2A_FLD0_INPUTENABLE_MASK                                    (0x00040000U)

#define CTRL_CORE_PAD_IO_VIN2A_FLD0_PULLTYPESELECT_SHIFT                                (17U)
#define CTRL_CORE_PAD_IO_VIN2A_FLD0_PULLTYPESELECT_MASK                                 (0x00020000U)

#define CTRL_CORE_PAD_IO_VIN2A_FLD0_PULLUDENABLE_SHIFT                                  (16U)
#define CTRL_CORE_PAD_IO_VIN2A_FLD0_PULLUDENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_PAD_IO_VIN2A_FLD0_MUXMODE_SHIFT                                       (0U)
#define CTRL_CORE_PAD_IO_VIN2A_FLD0_MUXMODE_MASK                                        (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_CLK_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_CLK_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_CLK_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_CLK_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_CLK_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_CLK_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_CLK_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_CLK_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_CLK_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_CLK_MUXMODE_MASK                                         (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_DE_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VOUT1_DE_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_DE_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VOUT1_DE_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_DE_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VOUT1_DE_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_DE_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VOUT1_DE_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_DE_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VOUT1_DE_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_DE_MUXMODE_VOUT1_DE_0                                    (0x00000000U)
#define CTRL_CORE_PAD_IO_VOUT1_DE_MUXMODE_MCASP1_ACLKX_1                                (0x00000001U)
#define CTRL_CORE_PAD_IO_VOUT1_DE_MUXMODE_VIN1A_D13_2                                   (0x00000002U)
#define CTRL_CORE_PAD_IO_VOUT1_DE_MUXMODE_CLKOUT1_4                                     (0x00000004U)
#define CTRL_CORE_PAD_IO_VOUT1_DE_MUXMODE_GPIO2_21_14                                   (0x0000000EU)

#define CTRL_CORE_PAD_IO_VOUT1_FLD_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_FLD_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_FLD_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_FLD_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_FLD_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_FLD_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_FLD_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_FLD_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_FLD_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_FLD_MUXMODE_MASK                                         (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_FLD_MUXMODE_VOUT1_FLD_0                                  (0x00000000U)
#define CTRL_CORE_PAD_IO_VOUT1_FLD_MUXMODE_MCASP1_FSX_1                                 (0x00000001U)
#define CTRL_CORE_PAD_IO_VOUT1_FLD_MUXMODE_VIN1A_D14_2                                  (0x00000002U)
#define CTRL_CORE_PAD_IO_VOUT1_FLD_MUXMODE_CLKOUT2_4                                    (0x00000004U)
#define CTRL_CORE_PAD_IO_VOUT1_FLD_MUXMODE_GPIO2_22_14                                  (0x0000000EU)

#define CTRL_CORE_PAD_IO_VOUT1_HSYNC_SLEWCONTROL_SHIFT                                  (19U)
#define CTRL_CORE_PAD_IO_VOUT1_HSYNC_SLEWCONTROL_MASK                                   (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_HSYNC_INPUTENABLE_SHIFT                                  (18U)
#define CTRL_CORE_PAD_IO_VOUT1_HSYNC_INPUTENABLE_MASK                                   (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_HSYNC_PULLTYPESELECT_SHIFT                               (17U)
#define CTRL_CORE_PAD_IO_VOUT1_HSYNC_PULLTYPESELECT_MASK                                (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_HSYNC_PULLUDENABLE_SHIFT                                 (16U)
#define CTRL_CORE_PAD_IO_VOUT1_HSYNC_PULLUDENABLE_MASK                                  (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_HSYNC_MUXMODE_SHIFT                                      (0U)
#define CTRL_CORE_PAD_IO_VOUT1_HSYNC_MUXMODE_MASK                                       (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_VSYNC_SLEWCONTROL_SHIFT                                  (19U)
#define CTRL_CORE_PAD_IO_VOUT1_VSYNC_SLEWCONTROL_MASK                                   (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_VSYNC_INPUTENABLE_SHIFT                                  (18U)
#define CTRL_CORE_PAD_IO_VOUT1_VSYNC_INPUTENABLE_MASK                                   (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_VSYNC_PULLTYPESELECT_SHIFT                               (17U)
#define CTRL_CORE_PAD_IO_VOUT1_VSYNC_PULLTYPESELECT_MASK                                (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_VSYNC_PULLUDENABLE_SHIFT                                 (16U)
#define CTRL_CORE_PAD_IO_VOUT1_VSYNC_PULLUDENABLE_MASK                                  (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_VSYNC_MUXMODE_SHIFT                                      (0U)
#define CTRL_CORE_PAD_IO_VOUT1_VSYNC_MUXMODE_MASK                                       (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_D0_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D0_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D0_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D0_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D0_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D0_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D0_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D0_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D0_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D0_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_D0_MUXMODE_VOUT1_D0_0                                    (0x00000000U)
#define CTRL_CORE_PAD_IO_VOUT1_D0_MUXMODE_MCASP1_AXR0_1                                 (0x00000001U)
#define CTRL_CORE_PAD_IO_VOUT1_D0_MUXMODE_VIN1A_D17_2                                   (0x00000002U)
#define CTRL_CORE_PAD_IO_VOUT1_D0_MUXMODE_MMC_CLK_5                                     (0x00000005U)
#define CTRL_CORE_PAD_IO_VOUT1_D0_MUXMODE_GPIO2_25_14                                   (0x0000000EU)

#define CTRL_CORE_PAD_IO_VOUT1_D1_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D1_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D1_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D1_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D1_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D1_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D1_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D1_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D1_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D1_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_D1_MUXMODE_VOUT1_D1_0                                    (0x00000000U)
#define CTRL_CORE_PAD_IO_VOUT1_D1_MUXMODE_MCASP1_AXR1_1                                 (0x00000001U)
#define CTRL_CORE_PAD_IO_VOUT1_D1_MUXMODE_VIN1A_D18_2                                   (0x00000002U)
#define CTRL_CORE_PAD_IO_VOUT1_D1_MUXMODE_MMC_CMD_5                                     (0x00000005U)
#define CTRL_CORE_PAD_IO_VOUT1_D1_MUXMODE_GPIO2_26_14                                   (0x0000000EU)

#define CTRL_CORE_PAD_IO_VOUT1_D2_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D2_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D2_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D2_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D2_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D2_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D2_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D2_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D2_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D2_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_D3_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D3_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D3_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D3_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D3_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D3_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D3_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D3_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D3_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D3_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_D4_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D4_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D4_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D4_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D4_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D4_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D4_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D4_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D4_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D4_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_D5_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D5_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D5_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D5_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D5_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D5_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D5_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D5_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D5_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D5_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_D6_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_SLEWCONTROL_MASK                                      (0x00080000U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_SLEWCONTROL_SLOW                                      (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_SLEWCONTROL_FAST                                      (1U)

#define CTRL_CORE_PAD_IO_VOUT1_D6_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_INPUTENABLE_MASK                                      (0x00040000U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_INPUTENABLE_DISABLE                                   (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_INPUTENABLE_ENABLE                                    (1U)


#define CTRL_CORE_PAD_IO_VOUT1_D6_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_PULLTYPESELECT_MASK                                   (0x00020000U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_PULLTYPESELECT_PULL_DOWN                              (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_PULLTYPESELECT_PULL_UP                                (1U)

#define CTRL_CORE_PAD_IO_VOUT1_D6_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_PULLUDENABLE_MASK                                     (0x00010000U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_PULLUDENABLE_DISABLE                                  (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_PULLUDENABLE_ENABLE                                   (1U)

#define CTRL_CORE_PAD_IO_VOUT1_D6_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D6_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D6_MUXMODE_ESM_ERROR_5                                   (5U)

#define CTRL_CORE_PAD_IO_VOUT1_D7_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D7_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D7_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D7_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D7_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D7_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D7_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D7_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D7_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D7_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_VOUT1_D8_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D8_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D8_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D8_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D8_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D8_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D8_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D8_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D8_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D8_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D8_MUXMODE_GPMC_A20_3                                    (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D9_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D9_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D9_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D9_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D9_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D9_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D9_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D9_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D9_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D9_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D9_MUXMODE_GPMC_A21_3                                    (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D10_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D10_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D10_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D10_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D10_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D10_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D10_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D10_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D10_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D10_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D10_MUXMODE_GPMC_A22_3                                   (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D11_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D11_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D11_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D11_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D11_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D11_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D11_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D11_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D11_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D11_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D11_MUXMODE_GPMC_A23_3                                   (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D12_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D12_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D12_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D12_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D12_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D12_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D12_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D12_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D12_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D12_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D12_MUXMODE_GPMC_A24_3                                   (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D13_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D13_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D13_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D13_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D13_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D13_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D13_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D13_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D13_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D13_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D13_MUXMODE_GPMC_A25_3                                   (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D14_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D14_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D14_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D14_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D14_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D14_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D14_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D14_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D14_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D14_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D14_MUXMODE_GPMC_A26_3                                   (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D15_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D15_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D15_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D15_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D15_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D15_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D15_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D15_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D15_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D15_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D15_MUXMODE_GPMC_A27_3                                   (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D16_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D16_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D16_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D16_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D16_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D16_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D16_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D16_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D16_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D16_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D16_MUXMODE_GPMC_A0_3                                    (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D17_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D17_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D17_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D17_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D17_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D17_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D17_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D17_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D17_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D17_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D17_MUXMODE_GPMC_A1_3                                    (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D18_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D18_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D18_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D18_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D18_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D18_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D18_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D18_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D18_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D18_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D18_MUXMODE_GPMC_A2_3                                    (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D19_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D19_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D19_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D19_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D19_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D19_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D19_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D19_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D19_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D19_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D19_MUXMODE_GPMC_A3_3                                    (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D20_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D20_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D20_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D20_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D20_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D20_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D20_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D20_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D20_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D20_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D20_MUXMODE_GPMC_A4_3                                    (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D21_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D21_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D21_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D21_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D21_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D21_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D21_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D21_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D21_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D21_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D21_MUXMODE_GPMC_A5_3                                    (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D22_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D22_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D22_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D22_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D22_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D22_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D22_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D22_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D22_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D22_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D22_MUXMODE_GPMC_A6_3                                    (3U)

#define CTRL_CORE_PAD_IO_VOUT1_D23_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_VOUT1_D23_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_VOUT1_D23_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_VOUT1_D23_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_VOUT1_D23_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_VOUT1_D23_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_VOUT1_D23_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_VOUT1_D23_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_VOUT1_D23_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_VOUT1_D23_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_VOUT1_D23_MUXMODE_GPMC_A7_3                                    (3U)

#define CTRL_CORE_PAD_IO_DCAN2_TX_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_DCAN2_TX_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_DCAN2_TX_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_DCAN2_TX_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_DCAN2_TX_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_DCAN2_TX_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_DCAN2_TX_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_DCAN2_TX_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_DCAN2_TX_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_DCAN2_TX_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_DCAN2_RX_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_DCAN2_RX_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_DCAN2_RX_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_DCAN2_RX_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_DCAN2_RX_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_DCAN2_RX_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_DCAN2_RX_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_DCAN2_RX_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_DCAN2_RX_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_DCAN2_RX_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_MDIO_MCLK_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_MDIO_MCLK_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_MDIO_MCLK_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_MDIO_MCLK_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_MDIO_MCLK_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_MDIO_MCLK_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_MDIO_MCLK_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_MDIO_MCLK_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_MDIO_MCLK_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_MDIO_MCLK_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_MDIO_MCLK_MUXMODE_MDIO_MCLK_0                                  (0U)

#define CTRL_CORE_PAD_IO_MDIO_D_SLEWCONTROL_SHIFT                                       (19U)
#define CTRL_CORE_PAD_IO_MDIO_D_SLEWCONTROL_MASK                                        (0x00080000U)
#define CTRL_CORE_PAD_IO_MDIO_D_SLEWCONTROL_SLOW                                        (0U)
#define CTRL_CORE_PAD_IO_MDIO_D_SLEWCONTROL_FAST                                        (1U)

#define CTRL_CORE_PAD_IO_MDIO_D_INPUTENABLE_SHIFT                                       (18U)
#define CTRL_CORE_PAD_IO_MDIO_D_INPUTENABLE_MASK                                        (0x00040000U)
#define CTRL_CORE_PAD_IO_MDIO_D_INPUTENABLE_DISABLE                                     (0U)
#define CTRL_CORE_PAD_IO_MDIO_D_INPUTENABLE_ENABLE                                      (1U)

#define CTRL_CORE_PAD_IO_MDIO_D_PULLTYPESELECT_SHIFT                                    (17U)
#define CTRL_CORE_PAD_IO_MDIO_D_PULLTYPESELECT_MASK                                     (0x00020000U)
#define CTRL_CORE_PAD_IO_MDIO_D_PULLTYPESELECT_PULL_DOWN                                (0U)
#define CTRL_CORE_PAD_IO_MDIO_D_PULLTYPESELECT_PULL_UP                                  (1U)

#define CTRL_CORE_PAD_IO_MDIO_D_PULLUDENABLE_SHIFT                                      (16U)
#define CTRL_CORE_PAD_IO_MDIO_D_PULLUDENABLE_MASK                                       (0x00010000U)
#define CTRL_CORE_PAD_IO_MDIO_D_PULLUDENABLE_DISABLE                                    (0U)
#define CTRL_CORE_PAD_IO_MDIO_D_PULLUDENABLE_ENABLE                                     (1U)

#define CTRL_CORE_PAD_IO_MDIO_D_MUXMODE_SHIFT                                           (0U)
#define CTRL_CORE_PAD_IO_MDIO_D_MUXMODE_MASK                                            (0x0000000fU)
#define CTRL_CORE_PAD_IO_MDIO_D_MUXMODE_MDIO_D_0                                        (0U)
#define CTRL_CORE_PAD_IO_MDIO_D_MUXMODE_ESM_ERROR_5                                     (5U)

#define CTRL_CORE_PAD_IO_RGMII0_TXC_SLEWCONTROL_SHIFT                                   (19U)
#define CTRL_CORE_PAD_IO_RGMII0_TXC_SLEWCONTROL_MASK                                    (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXC_INPUTENABLE_SHIFT                                   (18U)
#define CTRL_CORE_PAD_IO_RGMII0_TXC_INPUTENABLE_MASK                                    (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXC_PULLTYPESELECT_SHIFT                                (17U)
#define CTRL_CORE_PAD_IO_RGMII0_TXC_PULLTYPESELECT_MASK                                 (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXC_PULLUDENABLE_SHIFT                                  (16U)
#define CTRL_CORE_PAD_IO_RGMII0_TXC_PULLUDENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXC_MUXMODE_SHIFT                                       (0U)
#define CTRL_CORE_PAD_IO_RGMII0_TXC_MUXMODE_MASK                                        (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_TXC_MUXMODE_RGMII0_TXC_0                                (0U)

#define CTRL_CORE_PAD_IO_RGMII0_TXCTL_SLEWCONTROL_SHIFT                                 (19U)
#define CTRL_CORE_PAD_IO_RGMII0_TXCTL_SLEWCONTROL_MASK                                  (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXCTL_INPUTENABLE_SHIFT                                 (18U)
#define CTRL_CORE_PAD_IO_RGMII0_TXCTL_INPUTENABLE_MASK                                  (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXCTL_PULLTYPESELECT_SHIFT                              (17U)
#define CTRL_CORE_PAD_IO_RGMII0_TXCTL_PULLTYPESELECT_MASK                               (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXCTL_PULLUDENABLE_SHIFT                                (16U)
#define CTRL_CORE_PAD_IO_RGMII0_TXCTL_PULLUDENABLE_MASK                                 (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXCTL_MUXMODE_SHIFT                                     (0U)
#define CTRL_CORE_PAD_IO_RGMII0_TXCTL_MUXMODE_MASK                                      (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_TXCTL_MUXMODE_RGMII0_TXCTL_0                            (0U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD3_SLEWCONTROL_SHIFT                                  (19U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD3_SLEWCONTROL_MASK                                   (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD3_INPUTENABLE_SHIFT                                  (18U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD3_INPUTENABLE_MASK                                   (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD3_PULLTYPESELECT_SHIFT                               (17U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD3_PULLTYPESELECT_MASK                                (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD3_PULLUDENABLE_SHIFT                                 (16U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD3_PULLUDENABLE_MASK                                  (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD3_MUXMODE_SHIFT                                      (0U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD3_MUXMODE_MASK                                       (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_TXD3_MUXMODE_RGMII0_TXD3_0                              (0U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD2_SLEWCONTROL_SHIFT                                  (19U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD2_SLEWCONTROL_MASK                                   (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD2_INPUTENABLE_SHIFT                                  (18U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD2_INPUTENABLE_MASK                                   (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD2_PULLTYPESELECT_SHIFT                               (17U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD2_PULLTYPESELECT_MASK                                (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD2_PULLUDENABLE_SHIFT                                 (16U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD2_PULLUDENABLE_MASK                                  (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD2_MUXMODE_SHIFT                                      (0U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD2_MUXMODE_MASK                                       (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_TXD2_MUXMODE_RGMII0_TXD2_0                              (0U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD1_SLEWCONTROL_SHIFT                                  (19U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD1_SLEWCONTROL_MASK                                   (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD1_INPUTENABLE_SHIFT                                  (18U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD1_INPUTENABLE_MASK                                   (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD1_PULLTYPESELECT_SHIFT                               (17U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD1_PULLTYPESELECT_MASK                                (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD1_PULLUDENABLE_SHIFT                                 (16U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD1_PULLUDENABLE_MASK                                  (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD1_MUXMODE_SHIFT                                      (0U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD1_MUXMODE_MASK                                       (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_TXD1_MUXMODE_RGMII0_TXD1_0                              (0U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD0_SLEWCONTROL_SHIFT                                  (19U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD0_SLEWCONTROL_MASK                                   (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD0_INPUTENABLE_SHIFT                                  (18U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD0_INPUTENABLE_MASK                                   (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD0_PULLTYPESELECT_SHIFT                               (17U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD0_PULLTYPESELECT_MASK                                (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD0_PULLUDENABLE_SHIFT                                 (16U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD0_PULLUDENABLE_MASK                                  (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_TXD0_MUXMODE_SHIFT                                      (0U)
#define CTRL_CORE_PAD_IO_RGMII0_TXD0_MUXMODE_MASK                                       (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_TXD0_MUXMODE_RGMII0_TXD0_0                              (0U)

#define CTRL_CORE_PAD_IO_RGMII0_RXC_SLEWCONTROL_SHIFT                                   (19U)
#define CTRL_CORE_PAD_IO_RGMII0_RXC_SLEWCONTROL_MASK                                    (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXC_INPUTENABLE_SHIFT                                   (18U)
#define CTRL_CORE_PAD_IO_RGMII0_RXC_INPUTENABLE_MASK                                    (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXC_PULLTYPESELECT_SHIFT                                (17U)
#define CTRL_CORE_PAD_IO_RGMII0_RXC_PULLTYPESELECT_MASK                                 (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXC_PULLUDENABLE_SHIFT                                  (16U)
#define CTRL_CORE_PAD_IO_RGMII0_RXC_PULLUDENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXC_MUXMODE_SHIFT                                       (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXC_MUXMODE_MASK                                        (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_RXC_MUXMODE_RGMII0_RXC_0                                (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXC_MUXMODE_MMC4_CLK_5                                  (5U)

#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_SLEWCONTROL_SHIFT                                 (19U)
#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_SLEWCONTROL_MASK                                  (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_INPUTENABLE_SHIFT                                 (18U)
#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_INPUTENABLE_MASK                                  (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_PULLTYPESELECT_SHIFT                              (17U)
#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_PULLTYPESELECT_MASK                               (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_PULLUDENABLE_SHIFT                                (16U)
#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_PULLUDENABLE_MASK                                 (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_MUXMODE_SHIFT                                     (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_MUXMODE_MASK                                      (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_MUXMODE_RGMII0_RXCTL_0                            (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXCTL_MUXMODE_MMC4_CMD_5                                (5U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD3_SLEWCONTROL_SHIFT                                  (19U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD3_SLEWCONTROL_MASK                                   (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD3_INPUTENABLE_SHIFT                                  (18U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD3_INPUTENABLE_MASK                                   (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD3_PULLTYPESELECT_SHIFT                               (17U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD3_PULLTYPESELECT_MASK                                (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD3_PULLUDENABLE_SHIFT                                 (16U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD3_PULLUDENABLE_MASK                                  (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD3_MUXMODE_SHIFT                                      (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD3_MUXMODE_MASK                                       (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_RXD3_MUXMODE_RGMII0_RXD3_0                              (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD3_MUXMODE_MMC4_DAT0_5                                (5U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD2_SLEWCONTROL_SHIFT                                  (19U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD2_SLEWCONTROL_MASK                                   (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD2_INPUTENABLE_SHIFT                                  (18U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD2_INPUTENABLE_MASK                                   (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD2_PULLTYPESELECT_SHIFT                               (17U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD2_PULLTYPESELECT_MASK                                (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD2_PULLUDENABLE_SHIFT                                 (16U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD2_PULLUDENABLE_MASK                                  (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD2_MUXMODE_SHIFT                                      (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD2_MUXMODE_MASK                                       (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_RXD2_MUXMODE_RGMII0_RXD2_0                              (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD2_MUXMODE_MMC4_DAT1_5                                (5U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD1_SLEWCONTROL_SHIFT                                  (19U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD1_SLEWCONTROL_MASK                                   (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD1_INPUTENABLE_SHIFT                                  (18U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD1_INPUTENABLE_MASK                                   (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD1_PULLTYPESELECT_SHIFT                               (17U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD1_PULLTYPESELECT_MASK                                (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD1_PULLUDENABLE_SHIFT                                 (16U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD1_PULLUDENABLE_MASK                                  (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD1_MUXMODE_SHIFT                                      (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD1_MUXMODE_MASK                                       (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_RXD1_MUXMODE_RGMII0_RXD1_0                              (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD1_MUXMODE_MMC4_DAT2_5                                (5U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD0_SLEWCONTROL_SHIFT                                  (19U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD0_SLEWCONTROL_MASK                                   (0x00080000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD0_INPUTENABLE_SHIFT                                  (18U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD0_INPUTENABLE_MASK                                   (0x00040000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD0_PULLTYPESELECT_SHIFT                               (17U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD0_PULLTYPESELECT_MASK                                (0x00020000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD0_PULLUDENABLE_SHIFT                                 (16U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD0_PULLUDENABLE_MASK                                  (0x00010000U)

#define CTRL_CORE_PAD_IO_RGMII0_RXD0_MUXMODE_SHIFT                                      (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD0_MUXMODE_MASK                                       (0x0000000fU)
#define CTRL_CORE_PAD_IO_RGMII0_RXD0_MUXMODE_RGMII0_RXD0_0                              (0U)
#define CTRL_CORE_PAD_IO_RGMII0_RXD0_MUXMODE_MMC4_DAT3_5                                (5U)

#define CTRL_CORE_PAD_IO_XREF_CLK0_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_XREF_CLK0_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_XREF_CLK0_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_XREF_CLK0_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_XREF_CLK0_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_XREF_CLK0_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_XREF_CLK0_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_XREF_CLK0_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_XREF_CLK0_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_XREF_CLK0_MUXMODE_MASK                                         (0x0000000fU)

#define CTRL_CORE_PAD_IO_SPI1_SCLK_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_SPI1_SCLK_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_SPI1_SCLK_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_SPI1_SCLK_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_SPI1_SCLK_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_SPI1_SCLK_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_SPI1_SCLK_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_SPI1_SCLK_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_SPI1_SCLK_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_SPI1_SCLK_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_SPI1_SCLK_MUXMODE_SPI1_SCLK_0                                  (0U)
#define CTRL_CORE_PAD_IO_SPI1_SCLK_MUXMODE_UART3_RXD_1                                  (1U)
#define CTRL_CORE_PAD_IO_SPI1_SCLK_MUXMODE_GPIO4_0_14                                   (14U)

#define CTRL_CORE_PAD_IO_SPI1_D1_SLEWCONTROL_SHIFT                                      (19U)
#define CTRL_CORE_PAD_IO_SPI1_D1_SLEWCONTROL_MASK                                       (0x00080000U)

#define CTRL_CORE_PAD_IO_SPI1_D1_INPUTENABLE_SHIFT                                      (18U)
#define CTRL_CORE_PAD_IO_SPI1_D1_INPUTENABLE_MASK                                       (0x00040000U)

#define CTRL_CORE_PAD_IO_SPI1_D1_PULLTYPESELECT_SHIFT                                   (17U)
#define CTRL_CORE_PAD_IO_SPI1_D1_PULLTYPESELECT_MASK                                    (0x00020000U)

#define CTRL_CORE_PAD_IO_SPI1_D1_PULLUDENABLE_SHIFT                                     (16U)
#define CTRL_CORE_PAD_IO_SPI1_D1_PULLUDENABLE_MASK                                      (0x00010000U)

#define CTRL_CORE_PAD_IO_SPI1_D1_MUXMODE_SHIFT                                          (0U)
#define CTRL_CORE_PAD_IO_SPI1_D1_MUXMODE_MASK                                           (0x0000000fU)
#define CTRL_CORE_PAD_IO_SPI1_D1_MUXMODE_SPI1_D1_0                                      (0U)
#define CTRL_CORE_PAD_IO_SPI1_D1_MUXMODE_UART3_CTSN_1                                   (1U)
#define CTRL_CORE_PAD_IO_SPI1_D1_MUXMODE_GPIO4_1_14                                     (14U)

#define CTRL_CORE_PAD_IO_SPI1_D0_SLEWCONTROL_SHIFT                                      (19U)
#define CTRL_CORE_PAD_IO_SPI1_D0_SLEWCONTROL_MASK                                       (0x00080000U)

#define CTRL_CORE_PAD_IO_SPI1_D0_INPUTENABLE_SHIFT                                      (18U)
#define CTRL_CORE_PAD_IO_SPI1_D0_INPUTENABLE_MASK                                       (0x00040000U)

#define CTRL_CORE_PAD_IO_SPI1_D0_PULLTYPESELECT_SHIFT                                   (17U)
#define CTRL_CORE_PAD_IO_SPI1_D0_PULLTYPESELECT_MASK                                    (0x00020000U)

#define CTRL_CORE_PAD_IO_SPI1_D0_PULLUDENABLE_SHIFT                                     (16U)
#define CTRL_CORE_PAD_IO_SPI1_D0_PULLUDENABLE_MASK                                      (0x00010000U)

#define CTRL_CORE_PAD_IO_SPI1_D0_MUXMODE_SHIFT                                          (0U)
#define CTRL_CORE_PAD_IO_SPI1_D0_MUXMODE_MASK                                           (0x0000000fU)
#define CTRL_CORE_PAD_IO_SPI1_D0_MUXMODE_SPI1_D0_0                                      (0U)
#define CTRL_CORE_PAD_IO_SPI1_D0_MUXMODE_UART3_RTSN_1                                   (1U)
#define CTRL_CORE_PAD_IO_SPI1_D0_MUXMODE_GPIO4_2_14                                     (14U)

#define CTRL_CORE_PAD_IO_SPI1_CS0_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_SPI1_CS0_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_SPI1_CS0_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_SPI1_CS0_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_SPI1_CS0_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_SPI1_CS0_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_SPI1_CS0_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_SPI1_CS0_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_SPI1_CS0_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_SPI1_CS0_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_SPI1_CS0_MUXMODE_SPI1_CS0_0                                    (0U)
#define CTRL_CORE_PAD_IO_SPI1_CS0_MUXMODE_UART3_TXD_1                                   (1U)
#define CTRL_CORE_PAD_IO_SPI1_CS0_MUXMODE_GPIO4_3_14                                    (14U)

#define CTRL_CORE_PAD_IO_SPI1_CS1_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_SPI1_CS1_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_SPI1_CS1_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_SPI1_CS1_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_SPI1_CS1_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_SPI1_CS1_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_SPI1_CS1_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_SPI1_CS1_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_SPI1_CS1_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_SPI1_CS1_MUXMODE_MASK                                          (0x0000000fU)

#define CTRL_CORE_PAD_IO_SPI2_SCLK_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_SPI2_SCLK_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_SPI2_SCLK_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_SPI2_SCLK_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_SPI2_SCLK_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_SPI2_SCLK_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_SPI2_SCLK_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_SPI2_SCLK_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_SPI2_SCLK_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_SPI2_SCLK_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_SPI2_SCLK_MUXMODE_SPI2_SCLK_0                                  (0U)

#define CTRL_CORE_PAD_IO_SPI2_D1_SLEWCONTROL_SHIFT                                      (19U)
#define CTRL_CORE_PAD_IO_SPI2_D1_SLEWCONTROL_MASK                                       (0x00080000U)

#define CTRL_CORE_PAD_IO_SPI2_D1_INPUTENABLE_SHIFT                                      (18U)
#define CTRL_CORE_PAD_IO_SPI2_D1_INPUTENABLE_MASK                                       (0x00040000U)

#define CTRL_CORE_PAD_IO_SPI2_D1_PULLTYPESELECT_SHIFT                                   (17U)
#define CTRL_CORE_PAD_IO_SPI2_D1_PULLTYPESELECT_MASK                                    (0x00020000U)

#define CTRL_CORE_PAD_IO_SPI2_D1_PULLUDENABLE_SHIFT                                     (16U)
#define CTRL_CORE_PAD_IO_SPI2_D1_PULLUDENABLE_MASK                                      (0x00010000U)

#define CTRL_CORE_PAD_IO_SPI2_D1_MUXMODE_SHIFT                                          (0U)
#define CTRL_CORE_PAD_IO_SPI2_D1_MUXMODE_MASK                                           (0x0000000fU)
#define CTRL_CORE_PAD_IO_SPI2_D1_MUXMODE_SPI2_D1_0                                      (0U)

#define CTRL_CORE_PAD_IO_SPI2_D0_SLEWCONTROL_SHIFT                                      (19U)
#define CTRL_CORE_PAD_IO_SPI2_D0_SLEWCONTROL_MASK                                       (0x00080000U)

#define CTRL_CORE_PAD_IO_SPI2_D0_INPUTENABLE_SHIFT                                      (18U)
#define CTRL_CORE_PAD_IO_SPI2_D0_INPUTENABLE_MASK                                       (0x00040000U)

#define CTRL_CORE_PAD_IO_SPI2_D0_PULLTYPESELECT_SHIFT                                   (17U)
#define CTRL_CORE_PAD_IO_SPI2_D0_PULLTYPESELECT_MASK                                    (0x00020000U)

#define CTRL_CORE_PAD_IO_SPI2_D0_PULLUDENABLE_SHIFT                                     (16U)
#define CTRL_CORE_PAD_IO_SPI2_D0_PULLUDENABLE_MASK                                      (0x00010000U)

#define CTRL_CORE_PAD_IO_SPI2_D0_MUXMODE_SHIFT                                          (0U)
#define CTRL_CORE_PAD_IO_SPI2_D0_MUXMODE_MASK                                           (0x0000000fU)
#define CTRL_CORE_PAD_IO_SPI2_D0_MUXMODE_SPI2_D0_0                                      (0U)

#define CTRL_CORE_PAD_IO_SPI2_CS0_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_SPI2_CS0_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_SPI2_CS0_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_SPI2_CS0_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_SPI2_CS0_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_SPI2_CS0_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_SPI2_CS0_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_SPI2_CS0_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_SPI2_CS0_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_SPI2_CS0_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_SPI2_CS0_MUXMODE_SPI2_CS0_0                                    (0U)

#define CTRL_CORE_PAD_IO_DCAN1_TX_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_DCAN1_TX_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_DCAN1_TX_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_DCAN1_TX_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_DCAN1_TX_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_DCAN1_TX_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_DCAN1_TX_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_DCAN1_TX_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_DCAN1_TX_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_DCAN1_TX_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_DCAN1_TX_MUXMODE_DCAN1_TX_0                                    (0U)
#define CTRL_CORE_PAD_IO_DCAN1_TX_MUXMODE_GPIO4_9_14                                    (14U)

#define CTRL_CORE_PAD_IO_DCAN1_RX_SLEWCONTROL_SHIFT                                     (19U)
#define CTRL_CORE_PAD_IO_DCAN1_RX_SLEWCONTROL_MASK                                      (0x00080000U)

#define CTRL_CORE_PAD_IO_DCAN1_RX_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_DCAN1_RX_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_DCAN1_RX_PULLTYPESELECT_SHIFT                                  (17U)
#define CTRL_CORE_PAD_IO_DCAN1_RX_PULLTYPESELECT_MASK                                   (0x00020000U)

#define CTRL_CORE_PAD_IO_DCAN1_RX_PULLUDENABLE_SHIFT                                    (16U)
#define CTRL_CORE_PAD_IO_DCAN1_RX_PULLUDENABLE_MASK                                     (0x00010000U)

#define CTRL_CORE_PAD_IO_DCAN1_RX_MUXMODE_SHIFT                                         (0U)
#define CTRL_CORE_PAD_IO_DCAN1_RX_MUXMODE_MASK                                          (0x0000000fU)
#define CTRL_CORE_PAD_IO_DCAN1_RX_MUXMODE_DCAN1_RX_0                                    (0U)
#define CTRL_CORE_PAD_IO_DCAN1_RX_MUXMODE_GPIO4_10_14                                   (14U)

#define CTRL_CORE_PAD_IO_UART1_RXD_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_UART1_RXD_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_UART1_RXD_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_UART1_RXD_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_UART1_RXD_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_UART1_RXD_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_UART1_RXD_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_UART1_RXD_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_UART1_RXD_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_UART1_RXD_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_UART1_RXD_MUXMODE_UART1_RXD_0                                  (0U)
#define CTRL_CORE_PAD_IO_UART1_RXD_MUXMODE_SPI4_D1                                      (4U)
#define CTRL_CORE_PAD_IO_UART1_RXD_MUXMODE_DCAN2_TX_12                                  (12U)

#define CTRL_CORE_PAD_IO_UART1_TXD_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_UART1_TXD_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_UART1_TXD_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_UART1_TXD_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_UART1_TXD_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_UART1_TXD_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_UART1_TXD_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_UART1_TXD_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_UART1_TXD_0                                  (0U)
#define CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_SPI4_D0                                      (4U)
#define CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_DCAN2_RX_12                                  (12U)
#define CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_GPIO4_14_14                                  (14U)

#define CTRL_CORE_PAD_IO_UART1_CTSN_SLEWCONTROL_SHIFT                                   (19U)
#define CTRL_CORE_PAD_IO_UART1_CTSN_SLEWCONTROL_MASK                                    (0x00080000U)

#define CTRL_CORE_PAD_IO_UART1_CTSN_INPUTENABLE_SHIFT                                   (18U)
#define CTRL_CORE_PAD_IO_UART1_CTSN_INPUTENABLE_MASK                                    (0x00040000U)

#define CTRL_CORE_PAD_IO_UART1_CTSN_PULLTYPESELECT_SHIFT                                (17U)
#define CTRL_CORE_PAD_IO_UART1_CTSN_PULLTYPESELECT_MASK                                 (0x00020000U)

#define CTRL_CORE_PAD_IO_UART1_CTSN_PULLUDENABLE_SHIFT                                  (16U)
#define CTRL_CORE_PAD_IO_UART1_CTSN_PULLUDENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_PAD_IO_UART1_CTSN_MUXMODE_SHIFT                                       (0U)
#define CTRL_CORE_PAD_IO_UART1_CTSN_MUXMODE_MASK                                        (0x0000000fU)
#define CTRL_CORE_PAD_IO_UART1_CTSN_MUXMODE_UART1_CTSN_0                                (0U)
#define CTRL_CORE_PAD_IO_UART1_CTSN_MUXMODE_GPMC_A16_3                                  (3U)
#define CTRL_CORE_PAD_IO_UART1_CTSN_MUXMODE_SPI4_SCLK                                   (4U)
#define CTRL_CORE_PAD_IO_UART1_CTSN_MUXMODE_GPIO4_15                                    (14U)

#define CTRL_CORE_PAD_IO_UART1_RTSN_SLEWCONTROL_SHIFT                                   (19U)
#define CTRL_CORE_PAD_IO_UART1_RTSN_SLEWCONTROL_MASK                                    (0x00080000U)

#define CTRL_CORE_PAD_IO_UART1_RTSN_INPUTENABLE_SHIFT                                   (18U)
#define CTRL_CORE_PAD_IO_UART1_RTSN_INPUTENABLE_MASK                                    (0x00040000U)

#define CTRL_CORE_PAD_IO_UART1_RTSN_PULLTYPESELECT_SHIFT                                (17U)
#define CTRL_CORE_PAD_IO_UART1_RTSN_PULLTYPESELECT_MASK                                 (0x00020000U)

#define CTRL_CORE_PAD_IO_UART1_RTSN_PULLUDENABLE_SHIFT                                  (16U)
#define CTRL_CORE_PAD_IO_UART1_RTSN_PULLUDENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_PAD_IO_UART1_RTSN_MUXMODE_SHIFT                                       (0U)
#define CTRL_CORE_PAD_IO_UART1_RTSN_MUXMODE_MASK                                        (0x0000000fU)
#define CTRL_CORE_PAD_IO_UART1_RTSN_MUXMODE_UART1_RTSN_0                                (0U)
#define CTRL_CORE_PAD_IO_UART1_CTSN_MUXMODE_GPMC_A17_3                                  (3U)
#define CTRL_CORE_PAD_IO_UART1_RTSN_MUXMODE_QSPI1_RTCLK_8                               (8U)
#define CTRL_CORE_PAD_IO_UART1_RTSN_MUXMODE_SPI4_CS0                                    (4U)

#define CTRL_CORE_PAD_IO_UART2_RXD_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_UART2_RXD_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_UART2_RXD_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_UART2_RXD_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_UART2_RXD_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_UART2_RXD_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_UART2_RXD_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_UART2_RXD_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_UART2_RXD_0                                  (0U)
#define CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_SPI3_D1_1                                    (4U)
#define CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_QSPI1_RTCLK_5                                (5U)
#define CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_TIMER1_6                                     (6U)
#define CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_EHRPWM1A_7                                   (7U)
#define CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_GPMC_CLK_10                                  (10U)
#define CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_GPMC_A12_11                                  (11U)
#define CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_DCAN1_TX_12                                  (12U)
#define CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_GPIO4_17_14                                  (14U)

#define CTRL_CORE_PAD_IO_UART2_TXD_SLEWCONTROL_SHIFT                                    (19U)
#define CTRL_CORE_PAD_IO_UART2_TXD_SLEWCONTROL_MASK                                     (0x00080000U)

#define CTRL_CORE_PAD_IO_UART2_TXD_INPUTENABLE_SHIFT                                    (18U)
#define CTRL_CORE_PAD_IO_UART2_TXD_INPUTENABLE_MASK                                     (0x00040000U)

#define CTRL_CORE_PAD_IO_UART2_TXD_PULLTYPESELECT_SHIFT                                 (17U)
#define CTRL_CORE_PAD_IO_UART2_TXD_PULLTYPESELECT_MASK                                  (0x00020000U)

#define CTRL_CORE_PAD_IO_UART2_TXD_PULLUDENABLE_SHIFT                                   (16U)
#define CTRL_CORE_PAD_IO_UART2_TXD_PULLUDENABLE_MASK                                    (0x00010000U)

#define CTRL_CORE_PAD_IO_UART2_TXD_MUXMODE_SHIFT                                        (0U)
#define CTRL_CORE_PAD_IO_UART2_TXD_MUXMODE_MASK                                         (0x0000000fU)
#define CTRL_CORE_PAD_IO_UART2_TXD_MUXMODE_UART2_TXD_0                                  (0U)
#define CTRL_CORE_PAD_IO_UART2_TXD_MUXMODE_SPI3_D0_4                                    (4U)
#define CTRL_CORE_PAD_IO_UART2_TXD_MUXMODE_TIMER2_6                                     (6U)
#define CTRL_CORE_PAD_IO_UART2_TXD_MUXMODE_EHRPWM1B_7                                   (7U)
#define CTRL_CORE_PAD_IO_UART2_TXD_MUXMODE_GPMC_A13_11                                  (11U)
#define CTRL_CORE_PAD_IO_UART2_TXD_MUXMODE_DCAN1_RX_12                                  (12U)
#define CTRL_CORE_PAD_IO_UART2_TXD_MUXMODE_GPIO4_17_14                                  (14U)

#define CTRL_CORE_PAD_IO_UART2_CTSN_SLEWCONTROL_SHIFT                                   (19U)
#define CTRL_CORE_PAD_IO_UART2_CTSN_SLEWCONTROL_MASK                                    (0x00080000U)

#define CTRL_CORE_PAD_IO_UART2_CTSN_INPUTENABLE_SHIFT                                   (18U)
#define CTRL_CORE_PAD_IO_UART2_CTSN_INPUTENABLE_MASK                                    (0x00040000U)

#define CTRL_CORE_PAD_IO_UART2_CTSN_PULLTYPESELECT_SHIFT                                (17U)
#define CTRL_CORE_PAD_IO_UART2_CTSN_PULLTYPESELECT_MASK                                 (0x00020000U)

#define CTRL_CORE_PAD_IO_UART2_CTSN_PULLUDENABLE_SHIFT                                  (16U)
#define CTRL_CORE_PAD_IO_UART2_CTSN_PULLUDENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_PAD_IO_UART2_CTSN_MUXMODE_SHIFT                                       (0U)
#define CTRL_CORE_PAD_IO_UART2_CTSN_MUXMODE_MASK                                        (0x0000000fU)
#define CTRL_CORE_PAD_IO_UART2_CTSN_MUXMODE_GPMC_A18_3                                  (3U)

#define CTRL_CORE_PAD_IO_UART2_RTSN_SLEWCONTROL_SHIFT                                   (19U)
#define CTRL_CORE_PAD_IO_UART2_RTSN_SLEWCONTROL_MASK                                    (0x00080000U)

#define CTRL_CORE_PAD_IO_UART2_RTSN_INPUTENABLE_SHIFT                                   (18U)
#define CTRL_CORE_PAD_IO_UART2_RTSN_INPUTENABLE_MASK                                    (0x00040000U)

#define CTRL_CORE_PAD_IO_UART2_RTSN_PULLTYPESELECT_SHIFT                                (17U)
#define CTRL_CORE_PAD_IO_UART2_RTSN_PULLTYPESELECT_MASK                                 (0x00020000U)

#define CTRL_CORE_PAD_IO_UART2_RTSN_PULLUDENABLE_SHIFT                                  (16U)
#define CTRL_CORE_PAD_IO_UART2_RTSN_PULLUDENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_PAD_IO_UART2_RTSN_MUXMODE_SHIFT                                       (0U)
#define CTRL_CORE_PAD_IO_UART2_RTSN_MUXMODE_MASK                                        (0x0000000fU)
#define CTRL_CORE_PAD_IO_UART2_RTSN_MUXMODE_GPMC_A19_3                                  (3U)

#define CTRL_CORE_PAD_IO_I2C1_SDA_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_I2C1_SDA_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_I2C1_SCL_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_I2C1_SCL_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_I2C2_SDA_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_I2C2_SDA_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_I2C2_SCL_INPUTENABLE_SHIFT                                     (18U)
#define CTRL_CORE_PAD_IO_I2C2_SCL_INPUTENABLE_MASK                                      (0x00040000U)

#define CTRL_CORE_PAD_IO_TMS_SLEWCONTROL_SHIFT                                          (19U)
#define CTRL_CORE_PAD_IO_TMS_SLEWCONTROL_MASK                                           (0x00080000U)

#define CTRL_CORE_PAD_IO_TMS_INPUTENABLE_SHIFT                                          (18U)
#define CTRL_CORE_PAD_IO_TMS_INPUTENABLE_MASK                                           (0x00040000U)

#define CTRL_CORE_PAD_IO_TMS_MUXMODE_SHIFT                                              (0U)
#define CTRL_CORE_PAD_IO_TMS_MUXMODE_MASK                                               (0x0000000fU)

#define CTRL_CORE_PAD_IO_TDI_SLEWCONTROL_SHIFT                                          (19U)
#define CTRL_CORE_PAD_IO_TDI_SLEWCONTROL_MASK                                           (0x00080000U)

#define CTRL_CORE_PAD_IO_TDI_INPUTENABLE_SHIFT                                          (18U)
#define CTRL_CORE_PAD_IO_TDI_INPUTENABLE_MASK                                           (0x00040000U)

#define CTRL_CORE_PAD_IO_TDI_PULLTYPESELECT_SHIFT                                       (17U)
#define CTRL_CORE_PAD_IO_TDI_PULLTYPESELECT_MASK                                        (0x00020000U)

#define CTRL_CORE_PAD_IO_TDI_PULLUDENABLE_SHIFT                                         (16U)
#define CTRL_CORE_PAD_IO_TDI_PULLUDENABLE_MASK                                          (0x00010000U)

#define CTRL_CORE_PAD_IO_TDI_MUXMODE_SHIFT                                              (0U)
#define CTRL_CORE_PAD_IO_TDI_MUXMODE_MASK                                               (0x0000000fU)

#define CTRL_CORE_PAD_IO_TDO_SLEWCONTROL_SHIFT                                          (19U)
#define CTRL_CORE_PAD_IO_TDO_SLEWCONTROL_MASK                                           (0x00080000U)

#define CTRL_CORE_PAD_IO_TDO_INPUTENABLE_SHIFT                                          (18U)
#define CTRL_CORE_PAD_IO_TDO_INPUTENABLE_MASK                                           (0x00040000U)

#define CTRL_CORE_PAD_IO_TDO_PULLTYPESELECT_SHIFT                                       (17U)
#define CTRL_CORE_PAD_IO_TDO_PULLTYPESELECT_MASK                                        (0x00020000U)

#define CTRL_CORE_PAD_IO_TDO_PULLUDENABLE_SHIFT                                         (16U)
#define CTRL_CORE_PAD_IO_TDO_PULLUDENABLE_MASK                                          (0x00010000U)

#define CTRL_CORE_PAD_IO_TDO_MUXMODE_SHIFT                                              (0U)
#define CTRL_CORE_PAD_IO_TDO_MUXMODE_MASK                                               (0x0000000fU)

#define CTRL_CORE_PAD_IO_TCLK_INPUTENABLE_SHIFT                                         (18U)
#define CTRL_CORE_PAD_IO_TCLK_INPUTENABLE_MASK                                          (0x00040000U)

#define CTRL_CORE_PAD_IO_TCLK_PULLTYPESELECT_SHIFT                                      (17U)
#define CTRL_CORE_PAD_IO_TCLK_PULLTYPESELECT_MASK                                       (0x00020000U)

#define CTRL_CORE_PAD_IO_TCLK_PULLUDENABLE_SHIFT                                        (16U)
#define CTRL_CORE_PAD_IO_TCLK_PULLUDENABLE_MASK                                         (0x00010000U)

#define CTRL_CORE_PAD_IO_TCLK_MUXMODE_SHIFT                                             (0U)
#define CTRL_CORE_PAD_IO_TCLK_MUXMODE_MASK                                              (0x0000000fU)

#define CTRL_CORE_PAD_IO_TRSTN_SLEWCONTROL_SHIFT                                        (19U)
#define CTRL_CORE_PAD_IO_TRSTN_SLEWCONTROL_MASK                                         (0x00080000U)

#define CTRL_CORE_PAD_IO_TRSTN_INPUTENABLE_SHIFT                                        (18U)
#define CTRL_CORE_PAD_IO_TRSTN_INPUTENABLE_MASK                                         (0x00040000U)

#define CTRL_CORE_PAD_IO_TRSTN_PULLTYPESELECT_SHIFT                                     (17U)
#define CTRL_CORE_PAD_IO_TRSTN_PULLTYPESELECT_MASK                                      (0x00020000U)

#define CTRL_CORE_PAD_IO_TRSTN_PULLUDENABLE_SHIFT                                       (16U)
#define CTRL_CORE_PAD_IO_TRSTN_PULLUDENABLE_MASK                                        (0x00010000U)

#define CTRL_CORE_PAD_IO_RTCK_SLEWCONTROL_SHIFT                                         (19U)
#define CTRL_CORE_PAD_IO_RTCK_SLEWCONTROL_MASK                                          (0x00080000U)

#define CTRL_CORE_PAD_IO_RTCK_INPUTENABLE_SHIFT                                         (18U)
#define CTRL_CORE_PAD_IO_RTCK_INPUTENABLE_MASK                                          (0x00040000U)

#define CTRL_CORE_PAD_IO_RTCK_PULLTYPESELECT_SHIFT                                      (17U)
#define CTRL_CORE_PAD_IO_RTCK_PULLTYPESELECT_MASK                                       (0x00020000U)

#define CTRL_CORE_PAD_IO_RTCK_PULLUDENABLE_SHIFT                                        (16U)
#define CTRL_CORE_PAD_IO_RTCK_PULLUDENABLE_MASK                                         (0x00010000U)

#define CTRL_CORE_PAD_IO_RTCK_MUXMODE_SHIFT                                             (0U)
#define CTRL_CORE_PAD_IO_RTCK_MUXMODE_MASK                                              (0x0000000fU)

#define CTRL_CORE_PAD_IO_EMU0_SLEWCONTROL_SHIFT                                         (19U)
#define CTRL_CORE_PAD_IO_EMU0_SLEWCONTROL_MASK                                          (0x00080000U)

#define CTRL_CORE_PAD_IO_EMU0_INPUTENABLE_SHIFT                                         (18U)
#define CTRL_CORE_PAD_IO_EMU0_INPUTENABLE_MASK                                          (0x00040000U)

#define CTRL_CORE_PAD_IO_EMU0_PULLTYPESELECT_SHIFT                                      (17U)
#define CTRL_CORE_PAD_IO_EMU0_PULLTYPESELECT_MASK                                       (0x00020000U)

#define CTRL_CORE_PAD_IO_EMU0_PULLUDENABLE_SHIFT                                        (16U)
#define CTRL_CORE_PAD_IO_EMU0_PULLUDENABLE_MASK                                         (0x00010000U)

#define CTRL_CORE_PAD_IO_EMU0_MUXMODE_SHIFT                                             (0U)
#define CTRL_CORE_PAD_IO_EMU0_MUXMODE_MASK                                              (0x0000000fU)

#define CTRL_CORE_PAD_IO_EMU1_SLEWCONTROL_SHIFT                                         (19U)
#define CTRL_CORE_PAD_IO_EMU1_SLEWCONTROL_MASK                                          (0x00080000U)

#define CTRL_CORE_PAD_IO_EMU1_INPUTENABLE_SHIFT                                         (18U)
#define CTRL_CORE_PAD_IO_EMU1_INPUTENABLE_MASK                                          (0x00040000U)

#define CTRL_CORE_PAD_IO_EMU1_PULLTYPESELECT_SHIFT                                      (17U)
#define CTRL_CORE_PAD_IO_EMU1_PULLTYPESELECT_MASK                                       (0x00020000U)

#define CTRL_CORE_PAD_IO_EMU1_PULLUDENABLE_SHIFT                                        (16U)
#define CTRL_CORE_PAD_IO_EMU1_PULLUDENABLE_MASK                                         (0x00010000U)

#define CTRL_CORE_PAD_IO_EMU1_MUXMODE_SHIFT                                             (0U)
#define CTRL_CORE_PAD_IO_EMU1_MUXMODE_MASK                                              (0x0000000fU)

#define CTRL_CORE_PAD_IO_RESETN_PULLTYPESELECT_SHIFT                                    (17U)
#define CTRL_CORE_PAD_IO_RESETN_PULLTYPESELECT_MASK                                     (0x00020000U)

#define CTRL_CORE_PAD_IO_RESETN_PULLUDENABLE_SHIFT                                      (16U)
#define CTRL_CORE_PAD_IO_RESETN_PULLUDENABLE_MASK                                       (0x00010000U)

#define CTRL_CORE_PAD_IO_NMIN_PULLTYPESELECT_SHIFT                                      (17U)
#define CTRL_CORE_PAD_IO_NMIN_PULLTYPESELECT_MASK                                       (0x00020000U)

#define CTRL_CORE_PAD_IO_NMIN_PULLUDENABLE_SHIFT                                        (16U)
#define CTRL_CORE_PAD_IO_NMIN_PULLUDENABLE_MASK                                         (0x00010000U)

#define CTRL_CORE_PAD_IO_RSTOUTN_PULLTYPESELECT_SHIFT                                   (17U)
#define CTRL_CORE_PAD_IO_RSTOUTN_PULLTYPESELECT_MASK                                    (0x00020000U)

#define CTRL_CORE_PAD_IO_RSTOUTN_PULLUDENABLE_SHIFT                                     (16U)
#define CTRL_CORE_PAD_IO_RSTOUTN_PULLUDENABLE_MASK                                      (0x00010000U)


#ifdef __cplusplus
}
#endif
#endif  /* HW_CTRL_CORE_PAD_IO_H_ */

