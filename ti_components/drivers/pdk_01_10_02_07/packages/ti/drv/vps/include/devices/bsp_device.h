/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \defgroup BSP_DRV_DEVICE_API External Device Interface API
 *
 *  This module defines APIs for external video devices like video
 *  encoders, video decoders, video filters and sensors.
 *
 *  Typically I2C is used to send control commands to these external devices.
 *  The external device drivers make use of I2C wrapper APIs defined in
 *  this module.
 *  The I2C wrapper APIs in turn use the I2C driver to do the actual
 *  I2C transfer.
 *
 *  @{
 */

/**
 *  \file bsp_device.h
 *
 *  \brief External Video Device API.
 */

#ifndef BSP_DEVICE_H_
#define BSP_DEVICE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver ID base for video decoder driver class. */
#define DEVICE_VID_DEC_DRV_BASE         (0x00001000U)

/** \brief Driver ID base for video  encoder driver class. */
#define DEVICE_VID_ENC_DRV_BASE         (0x00001100U)

/** \brief Driver ID base for the sensor driver class. */
#define DEVICE_VID_SENSOR_DRV_BASE      (0x00001200U)

/** \brief Driver ID base for the lcd controller driver class. */
#define DEVICE_LCD_CTRL_DRV_BASE        (0x00001300U)

/**
 *  \name External Video Device Driver ID.
 *
 *  Used as drvId when calling Fvid2_create()
 *
 */

/* @{ */

/** \brief TVP5158 video decoder driver ID. */
#define FVID2_VID_DEC_TVP5158_DRV       (DEVICE_VID_DEC_DRV_BASE + 0x0000U)

/** \brief TVP7002 video decoder driver ID. */
#define FVID2_VID_DEC_TVP7002_DRV       (DEVICE_VID_DEC_DRV_BASE + 0x0001U)

/** \brief HDMI SII9135 video decoder driver ID. */
#define FVID2_VID_DEC_SII9135_DRV       (DEVICE_VID_DEC_DRV_BASE + 0x0002U)

/** \brief HDMI SII9127 video decoder driver ID. */
#define FVID2_VID_DEC_SII9127_DRV       (DEVICE_VID_DEC_DRV_BASE + 0x0003U)

/** \brief HDMI ADV7611 video decoder driver ID. */
#define FVID2_VID_DEC_ADV7611_DRV       (DEVICE_VID_DEC_DRV_BASE + 0x0004U)

/** \brief DS90UH926 video decoder (de-serializer) driver ID. */
#define FVID2_VID_DEC_DS90UH926_DRV     (DEVICE_VID_DEC_DRV_BASE + 0x0005U)

/** \brief HDMI SII9022a video encoder driver ID. */
#define FVID2_VID_ENC_SII9022A_DRV      (DEVICE_VID_ENC_DRV_BASE + 0x0000U)

/** \brief DS90UH925 video encoder (serializer) driver ID. */
#define FVID2_VID_ENC_DS90UH925_DRV     (DEVICE_VID_ENC_DRV_BASE + 0x0001U)

/** \brief OV10630 video sensor driver ID. */
#define FVID2_VID_SENSOR_OV10630_DRV    (DEVICE_VID_SENSOR_DRV_BASE + 0x0000U)

/** \brief MT9V022 video sensor driver ID. */
#define FVID2_VID_SENSOR_MT9V022_DRV    (DEVICE_VID_SENSOR_DRV_BASE + 0x0001U)

/** \brief MT9M024 video sensor driver ID. */
#define FVID2_VID_SENSOR_MT9M024_DRV    (DEVICE_VID_SENSOR_DRV_BASE + 0x0002U)

/** \brief OV10635 video sensor driver ID. */
#define FVID2_VID_SENSOR_OV1063X_DRV    (DEVICE_VID_SENSOR_DRV_BASE + 0x0003U)

/** \brief Leopard Imaging OV1063X video sensor driver ID. */
#define FVID2_VID_SENSOR_LI_OV1063X_DRV (DEVICE_VID_SENSOR_DRV_BASE + 0x0004U)

/** \brief Multi Deserializer OV1063X video sensor driver ID. */
#define FVID2_VID_SENSOR_MULDES_OV1063X_DRV     (DEVICE_VID_SENSOR_DRV_BASE + \
                                                 0x0005U)

/** \brief Aptina AR0132 video sensor driver ID. */
#define FVID2_VID_SENSOR_APT_AR0132_DRV (DEVICE_VID_SENSOR_DRV_BASE + 0x0006U)

/** \brief OV10640 video sensor driver ID for CSI2 output. */
#define FVID2_VID_SENSOR_OV10640_CSI2_DRV (DEVICE_VID_SENSOR_DRV_BASE + 0x0007U)

/** \brief AR0132 RCCC video sensor driver ID. */
#define FVID2_VID_SENSOR_APT_AR0132RCCC_DRV    (DEVICE_VID_SENSOR_DRV_BASE + \
                                                0x0008U)

/** \brief AR0132 + DM385 ISP video sensor driver ID. */
#define FVID2_VID_SENSOR_APT_AR0132ISP_DRV    (DEVICE_VID_SENSOR_DRV_BASE + \
                                               0x0009U)

/** \brief OV10640 video sensor driver ID for CPI output. */
#define FVID2_VID_SENSOR_OV10640_CPI_DRV (DEVICE_VID_SENSOR_DRV_BASE + 0x000AU)

/** \brief Aptina AR0140 video sensor driver ID. */
#define FVID2_VID_SENSOR_APT_AR0140_DRV (DEVICE_VID_SENSOR_DRV_BASE + 0x000BU)

/** \brief Sony IMX224 video sensor driver ID. */
#define FVID2_VID_SENSOR_SONY_IMX224_CSI2_DRV (DEVICE_VID_SENSOR_DRV_BASE + \
                                               0x000CU)

/** \brief TIDA00262 module, AR0140 video sensor driver ID. */
#define FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV (DEVICE_VID_SENSOR_DRV_BASE \
                                                   + 0x000DU)

/** \brief OV10640 video sensor driver ID for IMI. */
#define FVID2_VID_SENSOR_IMI_OV10640_DRV (DEVICE_VID_SENSOR_DRV_BASE \
                                          + 0x000FU)

/** \brief OV2659 video sensor driver ID for AM57x IDK */
#define FVID2_VID_SENSOR_OV2659_DRV     (DEVICE_VID_SENSOR_DRV_BASE + 0x0010U)

/** \brief IMX290 video sensor driver ID for GW4200 setup with 2 MP camera */
#define FVID2_VID_SENSOR_GW4200_IMX290_DRV     (DEVICE_VID_SENSOR_DRV_BASE + \
                                                0x0011U)

/** \brief OV2775 video sensor driver ID. */
#define FVID2_VID_SENSOR_OV2775_CSI2_DRV (DEVICE_VID_SENSOR_DRV_BASE \
                                                + 0x0012U)

/** \brief AR1243 Radar sensor driver ID used for 2Gbps mode */
#define FVID2_VID_SENSOR_AR1243_2G_DRV  (DEVICE_VID_SENSOR_DRV_BASE + 0x0013U)

/** \brief AR1243 Radar sensor driver ID used for 4Gbps mode */
#define FVID2_VID_SENSOR_AR1243_4G_DRV  (DEVICE_VID_SENSOR_DRV_BASE + 0x0014U)


/** \brief By Pass sensor configurations */
#define FVID2_VID_SENSOR_BYPASS_CSI2_DRV (DEVICE_VID_SENSOR_DRV_BASE \
                                                + 0x0014U)

/** \brief TDA2EX ETH board AVB Camera driver ID, used for power on Init */
#define FVID2_VID_ETHSRV_CAM_DRV     (DEVICE_VID_SENSOR_DRV_BASE + 0x0015U)

/** \brief Aptina AR0140 video sensor driver ID. */
#define FVID2_VID_SENSOR_APT_AR0143_DRV (DEVICE_VID_SENSOR_DRV_BASE + 0x0016U)

/** \brief MARS module, AR0140 + UB913. */
#define FVID2_VID_SENSOR_MARS_APT_AR0143_DRV (DEVICE_VID_SENSOR_DRV_BASE \
                                                   + 0x0017U)

/** \brief TDA2EX ETH board AVB Camera driver ID, used for power on Init */
#define FVID2_VID_SENSOR_OV2775_TIDA1130_DRV (DEVICE_VID_SENSOR_DRV_BASE + \
                                                    0x0018U)

#define FVID2_VID_SENSOR_D3_SONY_IMX390_DRV (DEVICE_VID_SENSOR_DRV_BASE + \
                                                    0x0019U)

/** \brief Camera + Radar sensor driver ID used for fusion */
#define FVID2_VID_SENSOR_FUSION_DRV (DEVICE_VID_SENSOR_DRV_BASE + \
                                                    0x001AU)

/** \brief OV490 video sensor driver ID. */
#define FVID2_VID_SENSOR_OV490_DRV        (DEVICE_VID_SENSOR_DRV_BASE + 0x00D4U)

/** \brief Multi Deserializer OV490 video sensor driver ID. */
#define FVID2_VID_SENSOR_MULDES_OV490_DRV (DEVICE_VID_SENSOR_DRV_BASE + 0x00D5U)

/** \brief LCD Controller driver ID. */
#define FVID2_LCD_CTRL_DRV              (DEVICE_LCD_CTRL_DRV_BASE + 0x0000U)

/* @} */

/*
 *  IOCTLs Base address.
 */
/** \brief IOCTL base address for the video decoder driver IOCTLs. */
#define BSP_VID_DEC_IOCTL_BASE          (FVID2_USER_BASE + 0x000A0000U)
/** \brief IOCTL base address for the video encoder driver IOCTLs. */
#define BSP_VID_ENC_IOCTL_BASE          (FVID2_USER_BASE + 0x000B0000U)
/** \brief IOCTL base address for the Sensor driver IOCTLs. */
#define BSP_VID_SENSOR_IOCTL_BASE       (FVID2_USER_BASE + 0x000C0000U)
/** \brief IOCTL base address for the Lcd Controller driver IOCTLs. */
#define BSP_LCD_CTRL_IOCTL_BASE         (FVID2_USER_BASE + 0x000D0000U)

/**
 *  \name I2C instance ID
 *
 *  Used with I2C APIs
 */

/* @{ */

/** \brief I2C instance 0. */
#define BSP_DEVICE_I2C_INST_ID_0        ((UInt32) 0U)

/** \brief I2C instance 1. */
#define BSP_DEVICE_I2C_INST_ID_1        ((UInt32) 1U)

/** \brief I2C instance 2. */
#define BSP_DEVICE_I2C_INST_ID_2        ((UInt32) 2U)

/** \brief I2C instance 3. */
#define BSP_DEVICE_I2C_INST_ID_3        ((UInt32) 3U)

/** \brief I2C instance 4. */
#define BSP_DEVICE_I2C_INST_ID_4        ((UInt32) 4U)

/* @} */

/**
 *  \name UART instance ID
 *
 *  Used as UART instance ID in the device driver APIs.
 */

/* @{ */

/** \brief UART instance 1 as per TRM. */
#define BSP_DEVICE_UART_INST_ID_0       ((UInt32) 0U)

/** \brief UART instance 2 per TRM. */
#define BSP_DEVICE_UART_INST_ID_1       ((UInt32) 1U)

/** \brief UART instance 3 as per TRM. */
#define BSP_DEVICE_UART_INST_ID_2       ((UInt32) 2U)

/** \brief UART instance 4 as per TRM. */
#define BSP_DEVICE_UART_INST_ID_3       ((UInt32) 3U)

/** \brief UART instance 5 as per TRM. */
#define BSP_DEVICE_UART_INST_ID_4       ((UInt32) 4U)

/** \brief UART instance 6 as per TRM. */
#define BSP_DEVICE_UART_INST_ID_5       ((UInt32) 5U)

/** \brief UART instance 7 as per TRM. */
#define BSP_DEVICE_UART_INST_ID_6       ((UInt32) 6U)

/** \brief UART instance 8 as per TRM. */
#define BSP_DEVICE_UART_INST_ID_7       ((UInt32) 7U)

/** \brief UART instance 9 as per TRM. */
#define BSP_DEVICE_UART_INST_ID_8       ((UInt32) 8U)

/** \brief UART instance 10 as per TRM. */
#define BSP_DEVICE_UART_INST_ID_9       ((UInt32) 9U)

/* @} */

/**
 *  \name McSPI instance ID
 *
 *  Used as McSPI instance ID in the device driver APIs.
 */

/* @{ */

/** \brief McSPI instance 1 as per TRM. */
#define BSP_DEVICE_MCSPI_INST_ID_0       ((UInt32) 0U)

/** \brief McSPI instance 2 per TRM. */
#define BSP_DEVICE_MCSPI_INST_ID_1       ((UInt32) 1U)

/** \brief McSPI instance 3 as per TRM. */
#define BSP_DEVICE_MCSPI_INST_ID_2       ((UInt32) 2U)

/** \brief McSPI instance 4 as per TRM. */
#define BSP_DEVICE_MCSPI_INST_ID_3       ((UInt32) 3U)

/* @} */

/**
 *  \name McAsp instance ID
 *
 *  Used as McAsp instance ID in the device driver APIs.
 */

/* @{ */

/** \brief McAsp instance 1 as per TRM. */
#define BSP_DEVICE_MCASP_INST_ID_0       ((UInt32) 0U)

/** \brief McAsp instance 2 per TRM. */
#define BSP_DEVICE_MCASP_INST_ID_1       ((UInt32) 1U)

/** \brief McAsp instance 3 as per TRM. */
#define BSP_DEVICE_MCASP_INST_ID_2       ((UInt32) 2U)

/** \brief McAsp instance 4 as per TRM. */
#define BSP_DEVICE_MCASP_INST_ID_3       ((UInt32) 3U)

/** \brief McAsp instance 5 as per TRM. */
#define BSP_DEVICE_MCASP_INST_ID_4       ((UInt32) 4U)

/** \brief McAsp instance 6 per TRM. */
#define BSP_DEVICE_MCASP_INST_ID_5       ((UInt32) 5U)

/** \brief McAsp instance 7 as per TRM. */
#define BSP_DEVICE_MCASP_INST_ID_6       ((UInt32) 6U)

/** \brief McAsp instance 8 as per TRM. */
#define BSP_DEVICE_MCASP_INST_ID_7       ((UInt32) 7U)

/* @} */

/**
 *  \name Ethernet Port (external port) instance ID
 *
 *  Used as Ethernet port instance ID in the device driver APIs.
 */
/* @{ */

/** \brief Ethernet port ID 0. */
#define BSP_DEVICE_ENET_PORT_INST_ID_0  ((UInt32) 0U)

/** \brief Ethernet port ID 1. */
#define BSP_DEVICE_ENET_PORT_INST_ID_1  ((UInt32) 1U)

/* @} */

/**
 *  \name Ethernet external phy instance ID
 *
 *  Used as Ethernet external phy ID in the device driver APIs.
 */
/* @{ */

/** \brief Ethernet Phy DP83865 ID 0. */
#define BSP_DEVICE_ENET_PHY_DP83865_INST_ID_0   ((UInt32) 0U)

/** \brief Ethernet Phy DP83865 ID 1. */
#define BSP_DEVICE_ENET_PHY_DP83865_INST_ID_1   ((UInt32) 1U)

/* @} */

/**
 *  \name MMC instance ID
 *
 *  Used as MMC ID in the device driver APIs.
 */
/* @{ */

/** \brief MMC ID 1. */
#define BSP_DEVICE_MMC_INST_ID_1   ((UInt32) 1U)

/** \brief MMC ID 2. */
#define BSP_DEVICE_MMC_INST_ID_2   ((UInt32) 2U)

/** \brief MMC ID 3. */
#define BSP_DEVICE_MMC_INST_ID_3   ((UInt32) 3U)

/** \brief MMC ID 4. */
#define BSP_DEVICE_MMC_INST_ID_4   ((UInt32) 4U)

/* @} */

/**
 *  \name Max limits
 */

/* @{ */

/** \brief Max I2C instance's. */
#define BSP_DEVICE_I2C_INST_ID_MAX      ((UInt32) 10U)

/** \brief Max UART instance's. */
#define BSP_DEVICE_UART_INST_ID_MAX     ((UInt32) 10U)

/** \brief Maximum number of encoder driver instance. */
#define VPS_DISP_ENC_INST_MAX           ((UInt32) 2U)

/** \brief Max handles per external device driver. */
#define BSP_DEVICE_MAX_HANDLES          ((UInt32) 8U)

/**
 *  \name SII9127 decoder instance ID
 *
 */
/** \brief SII9127 decoder instance 0. */
#define BSP_DEVICE_SII9127_INST_ID_0    ((UInt32) 0x0U)

/** \brief SII9127 decoder instance 1. */
#define BSP_DEVICE_SII9127_INST_ID_1    ((UInt32) 0x1U)

/**
 *  \name ADV7611 decoder instance ID
 *
 */
/** \brief ADV7611 decoder instance 0. */
#define BSP_DEVICE_ADV7611_INST_ID_0    ((UInt32) 0x0U)

/** \brief ADV7611 decoder instance 1. */
#define BSP_DEVICE_ADV7611_INST_ID_1    ((UInt32) 0x1U)

/**
 *  \name DS90UH926 de-serializer instance ID
 *
 */
/** \brief DS90UH926 de-serializer instance 0. */
#define BSP_DEVICE_DS90UH926_INST_ID_0  ((UInt32) 0x0U)

/** \brief DS90UH926 de-serializer instance 1. */
#define BSP_DEVICE_DS90UH926_INST_ID_1  ((UInt32) 0x1U)

/**
 *  \name OV1063X Sensor instance ID
 *
 */
/** \brief OV1063X Sensor instance 0. */
#define BSP_DEVICE_OV1063X_INST_ID_0   ((UInt32) 0x0U)
/** \brief OV1063X Sensor instance 1. */
#define BSP_DEVICE_OV1063X_INST_ID_1   ((UInt32) 0x1U)
/** \brief OV1063X Sensor instance 4. */
#define BSP_DEVICE_OV1063X_INST_ID_4   ((UInt32) 0x4U)


/**
 *  \name OV1063X Sensor instance ID used in multi deserializer board
 *
 */
/** \brief OV1063X Sensor instance 0 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV1063X_INST_ID_1 ((UInt32) 0x1U)

/** \brief OV1063X Sensor instance 1 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV1063X_INST_ID_2 ((UInt32) 0x2U)

/** \brief OV1063X Sensor instance 2 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV1063X_INST_ID_3 ((UInt32) 0x3U)

/** \brief OV1063X Sensor instance 3 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV1063X_INST_ID_4 ((UInt32) 0x4U)

/** \brief OV1063X Sensor instance 4 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV1063X_INST_ID_5 ((UInt32) 0x5U)

/** \brief OV1063X Sensor instance 5 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV1063X_INST_ID_6 ((UInt32) 0x6U)

/** \brief OV1063X Sensor instance 5 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV1063X_INST_ID_7 ((UInt32) 0x7U)

/** \brief OV1063X Sensor instance 5 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV1063X_INST_ID_8 ((UInt32) 0x8U)

/**
 *  \name IMX290 Sensor instance ID used in multi deserializer board
 *
 */
/** \brief IMX290 Sensor instance 0 in Multi Des board. */
#define BSP_DEVICE_MULDES_IMX290_INST_ID_1 ((UInt32) 0x1U)

/** \brief IMX290 Sensor instance 1 in Multi Des board. */
#define BSP_DEVICE_MULDES_IMX290_INST_ID_2 ((UInt32) 0x2U)

/** \brief IMX290 Sensor instance 2 in Multi Des board. */
#define BSP_DEVICE_MULDES_IMX290_INST_ID_3 ((UInt32) 0x3U)

/** \brief IMX290 Sensor instance 3 in Multi Des board. */
#define BSP_DEVICE_MULDES_IMX290_INST_ID_4 ((UInt32) 0x4U)

/** \brief IMX290 Sensor instance 4 in Multi Des board. */
#define BSP_DEVICE_MULDES_IMX290_INST_ID_5 ((UInt32) 0x5U)

/** \brief IMX290 Sensor instance 5 in Multi Des board. */
#define BSP_DEVICE_MULDES_IMX290_INST_ID_6 ((UInt32) 0x6U)

/**
 *  \name OV490 Sensor instance ID used in multi deserializer board
 *
 */
/** \brief OV490 Sensor instance 0 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV490_INST_ID_1 ((UInt32) 0x1U)

/** \brief OV490 Sensor instance 1 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV490_INST_ID_2 ((UInt32) 0x2U)

/** \brief OV490 Sensor instance 2 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV490_INST_ID_3 ((UInt32) 0x3U)

/** \brief OV490 Sensor instance 3 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV490_INST_ID_4 ((UInt32) 0x4U)

/** \brief OV490 Sensor instance 4 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV490_INST_ID_5 ((UInt32) 0x5U)

/** \brief OV490 Sensor instance 5 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV490_INST_ID_6 ((UInt32) 0x6U)

/** \brief OV490 Sensor instance 6 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV490_INST_ID_7 ((UInt32) 0x7U)

/** \brief OV490 Sensor instance 7 in Multi Des board. */
#define BSP_DEVICE_MULDES_OV490_INST_ID_8 ((UInt32) 0x8U)

/**
 *  \name LI OmniVision 1063X Sensor instance ID
 *
 */
/** \brief LI OmniVision 1063X Sensor instance 0. */
#define BSP_DEVICE_LI_OV1063X_INST_ID_0     ((UInt32) 0x0U)

/** \brief LI OmniVision 1063X Sensor instance 1. */
#define BSP_DEVICE_LI_OV1063X_INST_ID_1     ((UInt32) 0x1U)

/**
 *  \name OV2659 Sensor instance ID used in AM57x IDK board
 *
 */
/** \brief OV2659 Sensor instance 0 in AM57x IDK board. */
#define BSP_DEVICE_AM57XIDK_OV2659_INST_ID_0 ((UInt32) 0x0U)

/**
 *  \name Aptina AR0132 Sensor instance ID
 *
 */
/** \brief Aptina AR0132 Sensor instance 0. */
#define BSP_DEVICE_APT_AR0132_INST_ID_0     ((UInt32) 0x0U)

/** \brief Aptina AR0132 Sensor instance 1. */
#define BSP_DEVICE_APT_AR0132_INST_ID_1     ((UInt32) 0x1U)

/** \brief Aptina AR0132 Sensor instance 1. */
#define BSP_DEVICE_APT_AR0132_INST_ID_2_ISS ((UInt32) 0x2U)

/**
 *  \name Aptina AR0140 Sensor instance ID
 *
 */
/** \brief Aptina AR0140 Sensor instance 0. */
#define BSP_DEVICE_APT_AR0140_INST_ID_0_ISS ((UInt32) 0x0U)
/** \brief Aptina AR0140 Sensor instance 1. Primarily used for OTF capture */
#define BSP_DEVICE_APT_AR0140_INST_ID_1_ISS ((UInt32) 0x1U)

/**
 *  \name Aptina AR0143 Sensor instance ID
 *
 */
/** \brief Aptina AR0143 Sensor instance 0. */
#define BSP_DEVICE_APT_AR0143_INST_ID_0_ISS ((UInt32) 0x0U)
/** \brief Aptina AR0140 Sensor instance 1. Primarily used for OTF capture */
#define BSP_DEVICE_APT_AR0143_INST_ID_1_ISS ((UInt32) 0x1U)

/**
 *  \name Omnivision 10640 Sensor instance ID
 *
 */
/** \brief OmniVision 10640 Sensor instance 0 */
#define BSP_DEVICE_OV10640_INST_ID_0     ((UInt32) 0x0U)
/** \brief OmniVision 10640 Sensor instance 1
 *          Dummy instance - Its the same sensor */
#define BSP_DEVICE_OV10640_INST_ID_1     ((UInt32) 0x1U)

/**
 *  \name Sony IMX224 Sensor instance ID
 *
 */
/** \brief Sony IMX224 Sensor instance 0 */
#define BSP_DEVICE_IMX224_INST_ID_0     ((UInt32) 0x0U)

/** \brief OmniVision 2775 Sensor instance 0 */
#define BSP_DEVICE_OV2775_INST_ID_0     ((UInt32) 0x0U)

/* @} */

/**
 *  \name Ethernet *(AVB) Camera instance ID
 *
 *  Used as Video sensor instance ID in the device driver APIs.
 */
/* @{ */

/** \brief Ethernet camera 0. */
#define BSP_DEVICE_ETH_CAM_INST_ID_0  ((UInt32) 0U)
/** \brief Ethernet camera 1. */
#define BSP_DEVICE_ETH_CAM_INST_ID_1  ((UInt32) 1U)
/** \brief Ethernet camera 2. */
#define BSP_DEVICE_ETH_CAM_INST_ID_2  ((UInt32) 2U)
/** \brief Ethernet camera 3. */
#define BSP_DEVICE_ETH_CAM_INST_ID_3  ((UInt32) 3U)

/* @} */

/**
 *  \brief  BSP I2C bitRate
 *
 *  Specify one of the standardized I2C bus bit rates for I2C communications.
 *  The default is BSP_I2C_BITRATE_400KHZ.
 */
typedef enum
{
    BSP_I2C_BITRATE_100KHZ = 0,
    /**< 100 KHz bit rate */
    BSP_I2C_BITRATE_400KHZ = 1,
    /**< 400 KHz bit rate */
    BSP_I2C_BITRATE_3P4MHZ = 2
    /**< 3.4 MHz bit rate - not yet supported */
} Bsp_I2cBitRate;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief External video device sub-system init parameters
 */
typedef struct
{
    UInt32 isI2cInitReq;
    /**< Indicates whether I2C initialization is required. */
    UInt32 isI2cProbingReq;
    /**< If this is TRUE, THE INIT will try to probe all the I2C
     *   devices connected on a specific I2C bus. This should be FALSE for
     *   all production system/build since this is a time consuming function.
     *   For debugging this should be kept TRUE to probe all on-board I2C
     *   devices.
     *   This field is dont care if #isI2cInitReq is FALSE. */
} Bsp_DeviceInitParams;

/* ========================================================================== */
/*                         Functions                                          */
/* ========================================================================== */

/**
 *  \brief Initialize external video device subsystem.
 *
 *  - Call this API before creating any external video device driver.
 *  - Make sure Fvid2_init() is called before this API.
 *  - This API does not do any I2C communication with the external video
 *    devices.
 *  - This API initializes data structures, resources and I2C subsystem needed
 *    to use the external video devices.
 *
 *  \param pPrm         [IN] Pointer to init parameters.
 *
 *  \return BSP_SOK on success, else failure.
 */
Int32 Bsp_deviceInit(const Bsp_DeviceInitParams *pPrm);

/**
 *  \brief De-Initialize external video device subsystem.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return BSP_SOK on success, else failure.
 */
Int32 Bsp_deviceDeInit(Ptr args);

/**
 *  \brief Probes an I2C bus for all video devices.
 *
 *  Probes an I2C bus for all possibly connected slaves to it.
 *  Prints the detected slave address on the console.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceI2cProbeAll(UInt32 i2cInstId);

/**
 *  \brief Probes an I2C bus for a specific device slave address.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param slaveAddr    [IN] Slave I2C address
 *
 *  \return BSP_SOK slave device found, else slave device not found.
 */
Int32 Bsp_deviceI2cProbeDevice(UInt32 i2cInstId, UInt8 slaveAddr);

/**
 *  \brief Enable I2C debug prints.
 *
 *  \param enable       [IN] Enable/disable I2C debug prints
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceI2cDebugEnable(UInt32 enable);

/**
 *  \brief Read registers from device via I2C.
 *
 *  Make sure size of regAddr[] array and regValue[] array is
 *  greater than euqal to numRegs.
 *
 *  The value that gets read from the device is, <br>
 *  For regAddr[x], value read would be regValue[x]
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address Array
 *                           (regAddr[x] = 0 .. 0xFF)
 *  \param regValue     [OUT] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to read (<= sizeof regAddr[])
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceRead8(UInt32       i2cInstId,
                      UInt32       i2cDevAddr,
                      const UInt8 *regAddr,
                      UInt8       *regValue,
                      UInt32       numRegs);

/**
 *  \brief Raw Read from device via I2C.
 *
 *  Make sure regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regValue     [OUT] Device Register Value Array
 *  \param numRegs      [IN] Number of Registers to read
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceRawRead8(UInt32 i2cInstId,
                         UInt32 i2cDevAddr,
                         UInt8 *regValue,
                         UInt32 numRegs);

/**
 *  \brief Write registers to device via I2C.
 *
 *  Make sure size of regAddr array and regValue array is
 *  greater or equal to numRegs.
 *
 *  The value that gets written to the device is
 *
 *  For regAddr[x], value would be regValue[x]
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address Array
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceWrite8(UInt32       i2cInstId,
                       UInt32       i2cDevAddr,
                       const UInt8 *regAddr,
                       const UInt8 *regValue,
                       UInt32       numRegs);

/**
 *  \brief Raw Write to device via I2C.
 *
 *  Make sure size of regValue array is
 *  greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceRawWrite8(UInt32 i2cInstId,
                          UInt32 i2cDevAddr,
                          UInt8 *regValue,
                          UInt32 numRegs);

/**
 *  \brief Read registers from device via I2C.
 *
 *  Make sure size of regAddr[] array and regValue[] array is
 *  greater than euqal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address Array
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to read (<= sizeof regAddr[])
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceRead16(UInt32        i2cInstId,
                       UInt32        i2cDevAddr,
                       const UInt16 *regAddr,
                       UInt16       *regValue,
                       UInt32        numRegs);

/**
 *  \brief Write registers to device via I2C.
 *
 *  Make sure size of regAddr array and regValue array is
 *  greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address Array
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceWrite16(UInt32        i2cInstId,
                        UInt32        i2cDevAddr,
                        const UInt16 *regAddr,
                        const UInt16 *regValue,
                        UInt32        numRegs);

/**
 *  \brief Read registers from device via I2C.
 *
 *  Make sure size of regAddr[] array and regValue[] array is
 *  greater than euqal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address Array
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to read (<= sizeof regAddr[])
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceRead16_Custom(UInt32        i2cInstId,
                              UInt32        i2cDevAddr,
                              const UInt16 *regAddr,
                              UInt16       *regValue,
                              UInt32        numRegs);

/**
 *  \brief Write registers to device via I2C.
 *
 *  Make sure size of regAddr array and regValue array is
 *  greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address Array
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceWrite16_Custom(UInt32        i2cInstId,
                               UInt32        i2cDevAddr,
                               const UInt16 *regAddr,
                               const UInt16 *regValue,
                               UInt32        numRegs);

/**
 *  \brief Write registers to device via I2C.
 *
 *  Make sure size of regAddr array and regValue array is
 *  greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address (16 bits wide) Array
 *  \param regValue     [IN] Device Register Value Array, 8 bits each.
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceWrite_Custom_16A8D(UInt32        i2cInstId,
                                   UInt32        i2cDevAddr,
                                   const UInt16 *regAddr,
                                   const UInt8  *regValue,
                                   UInt32        numRegs);

/**
 *  \brief Read registers from device via I2C.
 *
 *  Make sure size of regAddr[] array and regValue[] array is
 *  greater than euqal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address Array
 *  \param regValue     [IN] Device Register Value Array in MSB format
 *  \param numRegs      [IN] Number of registers to read (<= sizeof regAddr[])
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceRead16Msb(UInt32        i2cInstId,
                          UInt32        i2cDevAddr,
                          const UInt16 *regAddr,
                          UInt16       *regValue,
                          UInt32        numRegs);

/**
 *  \brief Bsp_DeviceInitParams structure init function.
 *
 *  \param initPrms     [IN] Pointer to #Bsp_DeviceInitParams structure.
 *
 */
static inline void BspDeviceInitParams_init(Bsp_DeviceInitParams *initPrms);

/**
 *  \brief Set the I2C bus frequency.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_0 or
 *                           \ref BSP_DEVICE_I2C_INST_ID_1
 *  \param i2cBusFreq   [IN] I2C bus speed to set
 *
 */
Int32 Bsp_deviceSetBusSpeed(UInt32 i2cInstId, Bsp_I2cBitRate i2cBusFreq);

/**
 *  \brief Write registers to device via I2C. The address and data
 *         to be written forms a 3 byte packet written to the I2C
 *         line.
 *
 *  Make sure size of regAddr array and regValue array is
 *  greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_2
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address (16 bits wide) Array.
 *                           The LSB 8 bits are taken to create the
 *                           address.
 *  \param regValue     [IN] Device Register Value Array, 16 bits each.
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceWriteAddr8Data16(UInt32        i2cInstId,
                                 UInt32        i2cDevAddr,
                                 const UInt8  *regAddr,
                                 const UInt16 *regValue,
                                 UInt32        numRegs);

/**
 *  \brief  Read registers from device via I2C. The address is first sent as a
 *          single write command and then the 16 bit data is read in a single
 *          independent read command.
 *
 *  Make sure size of regAddr[] array and regValue[] array is
 *  greater than euqal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_2
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address Array
 *                           The LSB 8 bits are taken to create the
 *                           address.
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to read (<= sizeof regAddr[])
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceReadAddr8Data16(UInt32       i2cInstId,
                                UInt32       i2cDevAddr,
                                const UInt8 *regAddr,
                                UInt16      *regValue,
                                UInt32       numRegs);

/**
 *  \brief  Read registers from device via I2C. The address is first sent as a
 *          single 16 bit write command and then the 8 bit data is read in
 *          a single independent read command.
 *
 *  Make sure size of regAddr[] array and regValue[] array is
 *  greater than euqal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref BSP_DEVICE_I2C_INST_ID_2
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address Array
 *                           The LSB 16 bits are taken to create the
 *                           address.
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to read (<= sizeof regAddr[])
 *
 *  \return BSP_SOK on success else failure.
 */
Int32 Bsp_deviceReadAddr16Data8(UInt32       i2cInstId,
                                UInt32       i2cDevAddr,
                                const UInt16 *regAddr,
                                UInt8        *regValue,
                                UInt32       numRegs);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void BspDeviceInitParams_init(Bsp_DeviceInitParams *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->isI2cInitReq = (UInt32) TRUE;
#ifdef PROD_RELEASE_BUILD
        initPrms->isI2cProbingReq = (UInt32) FALSE;
#else
        initPrms->isI2cProbingReq = (UInt32) TRUE;
#endif
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_DEVICE_H_ */

/* @} */
