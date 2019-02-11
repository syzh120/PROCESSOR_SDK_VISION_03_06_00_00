/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file bspdrv_adv7611Priv.h
 *
 *  \brief ADV7611 decoder internal header file.
 */

#ifndef BSPDRV_ADV7611_PRIV_H_
#define BSPDRV_ADV7611_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/devices/bsp_videoDecoder.h>
#include <adv7611/bspdrv_adv7611.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_ADV7611_OBJ_STATE_UNUSED        (UInt32) (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_ADV7611_OBJ_STATE_IDLE          (UInt32) (1U)

/* ADV7611 IO registers @ I2C 0x4C or 0x4D */
#define BSP_ADV7611_REG_IO_VIDEO_STANDARD               ((UInt32) 0x00U)
#define BSP_ADV7611_REG_IO_PRIMARY_MODE                 ((UInt32) 0x01U)
#define BSP_ADV7611_REG_IO_REG_02                       ((UInt32) 0x02U)
#define BSP_ADV7611_REG_IO_REG_03                       ((UInt32) 0x03U)
#define BSP_ADV7611_REG_IO_REG_04                       ((UInt32) 0x04U)
#define BSP_ADV7611_REG_IO_REG_05                       ((UInt32) 0x05U)
#define BSP_ADV7611_REG_IO_REG_06                       ((UInt32) 0x06U)
#define BSP_ADV7611_REG_IO_REG_0B                       ((UInt32) 0x0BU)
#define BSP_ADV7611_REG_IO_REG_0C                       ((UInt32) 0x0CU)
#define BSP_ADV7611_REG_IO_REG_12                       ((UInt32) 0x12U)
#define BSP_ADV7611_REG_IO_REG_14                       ((UInt32) 0x14U)
#define BSP_ADV7611_REG_IO_REG_15                       ((UInt32) 0x15U)
#define BSP_ADV7611_REG_IO_LLC_DLL                      ((UInt32) 0x19U)
#define BSP_ADV7611_REG_IO_ALSB_CONTROL                 ((UInt32) 0x1BU)
#define BSP_ADV7611_REG_IO_HPA_REG1                     ((UInt32) 0x20U)
#define BSP_ADV7611_REG_IO_HPA_REG2                     ((UInt32) 0x21U)
#define BSP_ADV7611_REG_IO_REG_33                       ((UInt32) 0x33U)
#define BSP_ADV7611_REG_IO_INT_STATUS                   ((UInt32) 0x3FU)
#define BSP_ADV7611_REG_IO_INT1_CONFIGURATION           ((UInt32) 0x40U)
#define BSP_ADV7611_REG_IO_INT2_CONFIGURATION           ((UInt32) 0x41U)
#define BSP_ADV7611_REG_IO_RAW_STATUS_1                 ((UInt32) 0x42U)
#define BSP_ADV7611_REG_IO_INTERRUPT_STATUS_1           ((UInt32) 0x43U)
#define BSP_ADV7611_REG_IO_INTERRUPT_CLEAR_1            ((UInt32) 0x44U)
#define BSP_ADV7611_REG_IO_INTERRUPT2_MAS               ((UInt32) 0x45U)
#define BSP_ADV7611_REG_IO_INTERRUPT_MASKB_1            ((UInt32) 0x46U)
#define BSP_ADV7611_REG_IO_RAW_STATUS_2                 ((UInt32) 0x47U)
#define BSP_ADV7611_REG_IO_INTERRUPT_STATUS_2           ((UInt32) 0x48U)
#define BSP_ADV7611_REG_IO_INTERRUPT_CLEAR_2            ((UInt32) 0x49U)
#define BSP_ADV7611_REG_IO_INTERRUPT2_MASKB_2           ((UInt32) 0x4AU)
#define BSP_ADV7611_REG_IO_INTERRUPT_MASKB_2            ((UInt32) 0x4BU)
#define BSP_ADV7611_REG_IO_RAW_STATUS_6                 ((UInt32) 0x5BU)
#define BSP_ADV7611_REG_IO_INTERRUPT_STATUS_6           ((UInt32) 0x5CU)
#define BSP_ADV7611_REG_IO_INTERRUPT_CLEAR_6            ((UInt32) 0x5DU)
#define BSP_ADV7611_REG_IO_INTERRUPT2_MASKB_6           ((UInt32) 0x5EU)
#define BSP_ADV7611_REG_IO_INTERRUPT_MASKB_6            ((UInt32) 0x5FU)
#define BSP_ADV7611_REG_IO_HDMI_LVL_RAW_STATUS_1        ((UInt32) 0x60U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_STATUS_1        ((UInt32) 0x61U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_CLR_1           ((UInt32) 0x62U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT2_MASKB_1        ((UInt32) 0x63U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_MASKB_1         ((UInt32) 0x64U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_RAW_STATUS_2        ((UInt32) 0x65U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_STATUS_2        ((UInt32) 0x66U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_CLR_2           ((UInt32) 0x67U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT2_MASKB_2        ((UInt32) 0x68U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_MASKB_2         ((UInt32) 0x69U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_RAW_STATUS_3        ((UInt32) 0x6AU)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_STATUS_3        ((UInt32) 0x6BU)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_CLR_3           ((UInt32) 0x6CU)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT2_MASKB_3        ((UInt32) 0x6DU)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_MASKB_3         ((UInt32) 0x6EU)
#define BSP_ADV7611_REG_IO_HDMI_LVL_RAW_STATUS_4        ((UInt32) 0x6FU)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_STATUS_4        ((UInt32) 0x70U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_CLR_4           ((UInt32) 0x71U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT2_MASKB_4        ((UInt32) 0x72U)
#define BSP_ADV7611_REG_IO_HDMI_LVL_INT_MASKB_4         ((UInt32) 0x73U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_RAW_STATUS_1        ((UInt32) 0x79U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_STATUS_1        ((UInt32) 0x7AU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_CLR_1           ((UInt32) 0x7BU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT2_MASKB_1        ((UInt32) 0x7CU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_MASKB_1         ((UInt32) 0x7DU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_RAW_STATUS_2        ((UInt32) 0x7EU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_STATUS_2        ((UInt32) 0x7FU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_CLR_2           ((UInt32) 0x80U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT2_MASKB_2        ((UInt32) 0x81U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_MASKB_2         ((UInt32) 0x82U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_RAW_STATUS_3        ((UInt32) 0x83U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_STATUS_3            ((UInt32) 0x84U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_CLR_3           ((UInt32) 0x85U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT2_MASKB_3        ((UInt32) 0x86U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_MASKB_3         ((UInt32) 0x87U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_RAW_STATUS_4        ((UInt32) 0x88U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_STATUS_4            ((UInt32) 0x89U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_CLR_4           ((UInt32) 0x8AU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT2_MASKB_4        ((UInt32) 0x8BU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_MASKB_4         ((UInt32) 0x8CU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_RAW_STATUS_5        ((UInt32) 0x8DU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_STATUS_5            ((UInt32) 0x8EU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_CLR_5           ((UInt32) 0x8FU)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT2_MASKB_5        ((UInt32) 0x90U)
#define BSP_ADV7611_REG_IO_HDMI_EDG_INT_MASKB_5         ((UInt32) 0x91U)
#define BSP_ADV7611_REG_IO_CEC_STATUS1_RAW              ((UInt32) 0x92U)
#define BSP_ADV7611_REG_IO_CEC_STATUS1_INT_STATUS       ((UInt32) 0x93U)
#define BSP_ADV7611_REG_IO_CEC_STATUS1_INT_CLEAR        ((UInt32) 0x94U)
#define BSP_ADV7611_REG_IO_CEC_STATUS1_INT2_MASKB       ((UInt32) 0x95U)
#define BSP_ADV7611_REG_IO_CEC_STATUS1_INT1_MASKB       ((UInt32) 0x96U)
#define BSP_ADV7611_REG_IO_CEC_RAW_STATUS2              ((UInt32) 0x97U)
#define BSP_ADV7611_REG_IO_CEC_INTERRUPT_STATUS2        ((UInt32) 0x98U)
#define BSP_ADV7611_REG_IO_CEC_INTERRUPT_CLEAR2         ((UInt32) 0x99U)
#define BSP_ADV7611_REG_IO_CEC_INTERRUPT2_MASKB         ((UInt32) 0x9AU)
#define BSP_ADV7611_REG_IO_CEC_INTERRUPT_MASKB          ((UInt32) 0x9BU)
#define BSP_ADV7611_REG_IO_REG_D6                       ((UInt32) 0xD6U)
#define BSP_ADV7611_REG_IO_REG_D7                       ((UInt32) 0xD7U)
#define BSP_ADV7611_REG_IO_RD_INFO_H                    ((UInt32) 0xEAU)
#define BSP_ADV7611_REG_IO_RD_INFO_L                    ((UInt32) 0xEBU)
#define BSP_ADV7611_REG_IO_CEC_SLAVE_ADDR               ((UInt32) 0xF4U)
#define BSP_ADV7611_REG_IO_INFOFRAME_SLAVE_ADDR         ((UInt32) 0xF5U)
#define BSP_ADV7611_REG_IO_DPLL_SLAVE_ADDR              ((UInt32) 0xF8U)
#define BSP_ADV7611_REG_IO_KSV_SLAVE_ADDR               ((UInt32) 0xF9U)
#define BSP_ADV7611_REG_IO_EDID_SLAVE_ADDR              ((UInt32) 0xFAU)
#define BSP_ADV7611_REG_IO_HDMI_SLAVE_ADDR              ((UInt32) 0xFBU)
#define BSP_ADV7611_REG_IO_CP_SLAVE_ADDR                ((UInt32) 0xFDU)
#define BSP_ADV7611_REG_IO_REG_FF                       ((UInt32) 0xFFU)

/* ADV7611 DPLL registers @ I2C 0x26 - configurable through IO reg 0xF8 */
#define BSP_ADV7611_REG_DPLL_AUDIO_MISC                 ((UInt32) 0xA0U)
#define BSP_ADV7611_REG_DPLL_MCLK_FS                    ((UInt32) 0xB5U)

/* ADV7611 HDMI registers @ I2C 0x34 - configurable through IO reg 0xFB */
#define BSP_ADV7611_REG_HDMI_REG_00H                    ((UInt32) 0x00U)
#define BSP_ADV7611_REG_HDMI_REG_01H                    ((UInt32) 0x01U)
#define BSP_ADV7611_REG_HDMI_REG_03H                    ((UInt32) 0x03U)
#define BSP_ADV7611_REG_HDMI_REG_04H                    ((UInt32) 0x04U)
#define BSP_ADV7611_REG_HDMI_REG_05H                    ((UInt32) 0x05U)
#define BSP_ADV7611_REG_HDMI_LINE_WIDTH_1               ((UInt32) 0x07U)
#define BSP_ADV7611_REG_HDMI_LINE_WIDTH_2               ((UInt32) 0x08U)
#define BSP_ADV7611_REG_HDMI_FIELD0_HEIGHT_1            ((UInt32) 0x09U)
#define BSP_ADV7611_REG_HDMI_FIELD0_HEIGHT_2            ((UInt32) 0x0AU)
#define BSP_ADV7611_REG_HDMI_FIELD1_HEIGHT_1            ((UInt32) 0x0BU)
#define BSP_ADV7611_REG_HDMI_FIELD1_HEIGHT_2            ((UInt32) 0x0CU)
#define BSP_ADV7611_REG_HDMI_REG_0DH                    ((UInt32) 0x0DU)
#define BSP_ADV7611_REG_HDMI_AUDIO_MUTE_SPEED           ((UInt32) 0x0FU)
#define BSP_ADV7611_REG_HDMI_REG_10H                    ((UInt32) 0x10U)
#define BSP_ADV7611_REG_HDMI_AUDIO_FIFO_FULL_THRLD      ((UInt32) 0x11U)
#define BSP_ADV7611_REG_HDMI_AUDIO_FIFO_EMPTY_THRLD     ((UInt32) 0x12U)
#define BSP_ADV7611_REG_HDMI_AUDIO_COAST_MASK           ((UInt32) 0x13U)
#define BSP_ADV7611_REG_HDMI_MUTE_MASK_21_16            ((UInt32) 0x14U)
#define BSP_ADV7611_REG_HDMI_MUTE_MASK_15_8             ((UInt32) 0x15U)
#define BSP_ADV7611_REG_HDMI_MUTE_MASK_7_0              ((UInt32) 0x16U)
#define BSP_ADV7611_REG_HDMI_PACKETS_DETECTED_2         ((UInt32) 0x18U)
#define BSP_ADV7611_REG_HDMI_PACKETS_DETECTED_3         ((UInt32) 0x19U)
#define BSP_ADV7611_REG_HDMI_MUTE_CTRL                  ((UInt32) 0x1AU)
#define BSP_ADV7611_REG_HDMI_DEEPCOLOR_FIFO_DEBUG_1     ((UInt32) 0x1BU)
#define BSP_ADV7611_REG_HDMI_DEEPCOLOR_FIFO_DEBUG_2     ((UInt32) 0x1CU)
#define BSP_ADV7611_REG_HDMI_REG_1DH                    ((UInt32) 0x1DU)
#define BSP_ADV7611_REG_HDMI_TOTAL_LINE_WIDTH_1         ((UInt32) 0x1EU)
#define BSP_ADV7611_REG_HDMI_TOTAL_LINE_WIDTH_2         ((UInt32) 0x1FU)
#define BSP_ADV7611_REG_HDMI_HSYNC_FRONT_PORCH_1        ((UInt32) 0x20U)
#define BSP_ADV7611_REG_HDMI_HSYNC_FRONT_PORCH_2        ((UInt32) 0x21U)
#define BSP_ADV7611_REG_HDMI_HSYNC_PULSE_WIDTH_1        ((UInt32) 0x22U)
#define BSP_ADV7611_REG_HDMI_HSYNC_PULSE_WIDTH_2        ((UInt32) 0x23U)
#define BSP_ADV7611_REG_HDMI_HSYNC_BACK_PORCH_1         ((UInt32) 0x24U)
#define BSP_ADV7611_REG_HDMI_HSYNC_BACK_PORCH_2         ((UInt32) 0x25U)
#define BSP_ADV7611_REG_HDMI_FIELD0_TOTAL_HEIGHT_1      ((UInt32) 0x26U)
#define BSP_ADV7611_REG_HDMI_FIELD0_TOTAL_HEIGHT_2      ((UInt32) 0x27U)
#define BSP_ADV7611_REG_HDMI_FIELD1_TOTAL_HEIGHT_1      ((UInt32) 0x28U)
#define BSP_ADV7611_REG_HDMI_FIELD1_TOTAL_HEIGHT_2      ((UInt32) 0x29U)
#define BSP_ADV7611_REG_HDMI_FIELD0_VS_FRONT_PORCH_1    ((UInt32) 0x2AU)
#define BSP_ADV7611_REG_HDMI_FIELD0_VS_FRONT_PORCH_2    ((UInt32) 0x2BU)
#define BSP_ADV7611_REG_HDMI_FIELD1_VS_FRONT_PORCH_1    ((UInt32) 0x2CU)
#define BSP_ADV7611_REG_HDMI_FIELD1_VS_FRONT_PORCH_2    ((UInt32) 0x2DU)
#define BSP_ADV7611_REG_HDMI_FIELD0_VS_PULSE_WIDTH_1    ((UInt32) 0x2EU)
#define BSP_ADV7611_REG_HDMI_FIELD0_VS_PULSE_WIDTH_2    ((UInt32) 0x2FU)
#define BSP_ADV7611_REG_HDMI_FIELD1_VS_PULSE_WIDTH_1    ((UInt32) 0x30U)
#define BSP_ADV7611_REG_HDMI_FIELD1_VS_PULSE_WIDTH_2    ((UInt32) 0x31U)
#define BSP_ADV7611_REG_HDMI_FIELD0_VS_BACK_PORCH_1     ((UInt32) 0x32U)
#define BSP_ADV7611_REG_HDMI_FIELD0_VS_BACK_PORCH_2     ((UInt32) 0x33U)
#define BSP_ADV7611_REG_HDMI_FIELD1_VS_BACK_PORCH_1     ((UInt32) 0x34U)
#define BSP_ADV7611_REG_HDMI_FIELD1_VS_BACK_PORCH_2     ((UInt32) 0x35U)
#define BSP_ADV7611_REG_HDMI_CHANNEL_STATUS_DATA_1      ((UInt32) 0x36U)
#define BSP_ADV7611_REG_HDMI_CHANNEL_STATUS_DATA_2      ((UInt32) 0x37U)
#define BSP_ADV7611_REG_HDMI_CHANNEL_STATUS_DATA_3      ((UInt32) 0x38U)
#define BSP_ADV7611_REG_HDMI_CHANNEL_STATUS_DATA_4      ((UInt32) 0x39U)
#define BSP_ADV7611_REG_HDMI_CHANNEL_STATUS_DATA_5      ((UInt32) 0x3AU)
#define BSP_ADV7611_REG_HDMI_REG_3CH                    ((UInt32) 0x3CU)
#define BSP_ADV7611_REG_HDMI_REG_40H                    ((UInt32) 0x40U)
#define BSP_ADV7611_REG_HDMI_REG_41H                    ((UInt32) 0x41U)
#define BSP_ADV7611_REG_HDMI_REG_47H                    ((UInt32) 0x47U)
#define BSP_ADV7611_REG_HDMI_REG_48H                    ((UInt32) 0x48U)
#define BSP_ADV7611_REG_HDMI_REG_4CH                    ((UInt32) 0x4CU)
#define BSP_ADV7611_REG_HDMI_REG_50                     ((UInt32) 0x50U)
#define BSP_ADV7611_REG_HDMI_COLORSPACE                 ((UInt32) 0x53U)
#define BSP_ADV7611_REG_HDMI_FILT_5V_DET_REG            ((UInt32) 0x56U)
#define BSP_ADV7611_REG_HDMI_REG_5A                     ((UInt32) 0x5AU)
#define BSP_ADV7611_REG_HDMI_CTS_N_1                    ((UInt32) 0x5BU)
#define BSP_ADV7611_REG_HDMI_CTS_N_2                    ((UInt32) 0x5CU)
#define BSP_ADV7611_REG_HDMI_CTS_N_3                    ((UInt32) 0x5DU)
#define BSP_ADV7611_REG_HDMI_CTS_N_4                    ((UInt32) 0x5EU)
#define BSP_ADV7611_REG_HDMI_CTS_N_5                    ((UInt32) 0x5FU)
#define BSP_ADV7611_REG_HDMI_REG_6CH                    ((UInt32) 0x6CU)
#define BSP_ADV7611_REG_HDMI_DDC_PAD                    ((UInt32) 0x73U)
#define BSP_ADV7611_REG_HDMI_REG_02H                    ((UInt32) 0x83U)
#define BSP_ADV7611_REG_HDMI_EQ_DYNAMIC_FREQ            ((UInt32) 0x8CU)
#define BSP_ADV7611_REG_HDMI_EQ_DYN1_LF                 ((UInt32) 0x8DU)
#define BSP_ADV7611_REG_HDMI_EQ_DYN1_HF                 ((UInt32) 0x8EU)
#define BSP_ADV7611_REG_HDMI_EQ_DYN2_LF                 ((UInt32) 0x90U)
#define BSP_ADV7611_REG_HDMI_EQ_DYN2_HF                 ((UInt32) 0x91U)
#define BSP_ADV7611_REG_HDMI_EQ_DYN3_LF                 ((UInt32) 0x93U)
#define BSP_ADV7611_REG_HDMI_EQ_DYN3_HF                 ((UInt32) 0x94U)
#define BSP_ADV7611_REG_HDMI_EQ_DYNAMIC_ENABLE          ((UInt32) 0x96U)

/* ADV7611 CP registers @ I2C 0x22 - configurable through IO reg 0xFD */
#define BSP_ADV7611_REG_CP_DE_POS_CTRL_5                ((UInt32) 0x2AU)
#define BSP_ADV7611_REG_CP_DE_POS_CTRL_6                ((UInt32) 0x2BU)
#define BSP_ADV7611_REG_CP_DE_POS_CTRL_7                ((UInt32) 0x2CU)
#define BSP_ADV7611_REG_CP_DE_POS_CTRL_8                ((UInt32) 0x2DU)
#define BSP_ADV7611_REG_CP_DE_POS_CTRL_9                ((UInt32) 0x2EU)
#define BSP_ADV7611_REG_CP_DE_POS_CTRL_10               ((UInt32) 0x2FU)
#define BSP_ADV7611_REG_CP_DE_POS_ADJ_1                 ((UInt32) 0x30U)
#define BSP_ADV7611_REG_CP_DE_POS_ADJ_2                 ((UInt32) 0x31U)
#define BSP_ADV7611_REG_CP_BIT_REDUCTION_DITHER         ((UInt32) 0x36U)
#define BSP_ADV7611_REG_CP_CONTRAST_CTRL                ((UInt32) 0x3AU)
#define BSP_ADV7611_REG_CP_SATURATION_CTRL              ((UInt32) 0x3BU)
#define BSP_ADV7611_REG_CP_BRIGHTNESS_CTRL              ((UInt32) 0x3CU)
#define BSP_ADV7611_REG_CP_HUE_CTRL                     ((UInt32) 0x3DU)
#define BSP_ADV7611_REG_CP_REG_3EH                      ((UInt32) 0x3EU)
#define BSP_ADV7611_REG_CP_PRE_GAIN_CTRL                ((UInt32) 0x40U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_1                 ((UInt32) 0x52U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_2                 ((UInt32) 0x53U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_3                 ((UInt32) 0x54U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_4                 ((UInt32) 0x55U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_5                 ((UInt32) 0x56U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_6                 ((UInt32) 0x57U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_7                 ((UInt32) 0x58U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_8                 ((UInt32) 0x59U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_9                 ((UInt32) 0x5AU)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_10                ((UInt32) 0x5BU)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_11                ((UInt32) 0x5CU)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_12                ((UInt32) 0x5DU)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_13                ((UInt32) 0x5EU)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_14                ((UInt32) 0x5FU)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_15                ((UInt32) 0x60U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_16                ((UInt32) 0x61U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_17                ((UInt32) 0x62U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_18                ((UInt32) 0x63U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_19                ((UInt32) 0x64U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_20                ((UInt32) 0x65U)
#define BSP_ADV7611_REG_CP_CSC_COEFFS_21                ((UInt32) 0x66U)
#define BSP_ADV7611_REG_CP_CSC_DECIM_CTRL               ((UInt32) 0x68U)
#define BSP_ADV7611_REG_CP_REG_69H                      ((UInt32) 0x69U)
#define BSP_ADV7611_REG_CP_CLMP_FREEZE                  ((UInt32) 0x6CU)
#define BSP_ADV7611_REG_CP_OFFSET_CTRL_1                ((UInt32) 0x77U)
#define BSP_ADV7611_REG_CP_AVCODE_CTRL                  ((UInt32) 0x7BU)
#define BSP_ADV7611_REG_CP_SYNC_CTRL_1                  ((UInt32) 0x7CU)
#define BSP_ADV7611_REG_CP_SYNC_CTRL_2                  ((UInt32) 0x7DU)
#define BSP_ADV7611_REG_CP_SYNC_CTRL_3                  ((UInt32) 0x7EU)
#define BSP_ADV7611_REG_CP_SYNC_CTRL_4                  ((UInt32) 0x7FU)
#define BSP_ADV7611_REG_CP_SYNC_CTRL_5                  ((UInt32) 0x80U)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_3          ((UInt32) 0x86U)
#define BSP_ADV7611_REG_CP_DE_POS_ADJ_3                 ((UInt32) 0x88U)
#define BSP_ADV7611_REG_CP_SYNC_CTRL_6                  ((UInt32) 0x89U)
#define BSP_ADV7611_REG_CP_DE_POS_ADJ_4                 ((UInt32) 0x8BU)
#define BSP_ADV7611_REG_CP_DE_POS_ADJ_5                 ((UInt32) 0x8CU)
#define BSP_ADV7611_REG_CP_DE_POS_ADJ_6                 ((UInt32) 0x8DU)
#define BSP_ADV7611_REG_CP_DE_POS_ADJ_7                 ((UInt32) 0x8EU)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_4_1        ((UInt32) 0x8FU)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_4_2        ((UInt32) 0x90U)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_1       ((UInt32) 0xA3U)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_2       ((UInt32) 0xA4U)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_4          ((UInt32) 0xABU)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_5          ((UInt32) 0xACU)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_3       ((UInt32) 0xB1U)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_4       ((UInt32) 0xB2U)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_5       ((UInt32) 0xB3U)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_6_1     ((UInt32) 0xB8U)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_6_2     ((UInt32) 0xB9U)
#define BSP_ADV7611_REG_CP_HDMI_CP_CTRL_1               ((UInt32) 0xBAU)
#define BSP_ADV7611_REG_CP_FR_COLOR_SEL_1               ((UInt32) 0xBFU)
#define BSP_ADV7611_REG_CP_FR_COLOR_SEL_2               ((UInt32) 0xC0U)
#define BSP_ADV7611_REG_CP_FR_COLOR_SEL_3               ((UInt32) 0xC1U)
#define BSP_ADV7611_REG_CP_FR_COLOR_SEL_4               ((UInt32) 0xC2U)
#define BSP_ADV7611_REG_CP_CLMP_POS_CTRL_4              ((UInt32) 0xC9U)
#define BSP_ADV7611_REG_CP_HDMI_CP_CTRL_2               ((UInt32) 0xCBU)
#define BSP_ADV7611_REG_CP_REG_F2H                      ((UInt32) 0xF2U)
#define BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_6          ((UInt32) 0xF3U)
#define BSP_ADV7611_REG_CP_CSC_COEFF_SEL_RB             ((UInt32) 0xF4U)
#define BSP_ADV7611_REG_CP_REG_FFH                      ((UInt32) 0xFFU)

/* ADV7611 repeater registers @ I2C 0x56 - configurable through IO reg 0xF9 */
#define BSP_ADV7611_REG_KSV_HDCP_EDID_CTRL              ((UInt32) 0x74U)
#define BSP_ADV7611_REG_KSV_EDID_DEBUG_2                ((UInt32) 0x76U)

/*
 * HDMI AVI InfoFrame Packet info
 */
/* color space */
#define BSP_ADV7611_AVI_INFO_COLOR_RGB444               ((UInt32) 0U)
#define BSP_ADV7611_AVI_INFO_COLOR_YUV444               ((UInt32) 1U)
#define BSP_ADV7611_AVI_INFO_COLOR_YUV422               ((UInt32) 2U)

/* color imetric */
#define BSP_ADV7611_AVI_INFO_CMETRIC_NO_DATA            ((UInt32) 0U)
#define BSP_ADV7611_AVI_INFO_CMETRIC_ITU601             ((UInt32) 1U)
#define BSP_ADV7611_AVI_INFO_CMETRIC_ITU709             ((UInt32) 2U)

/* pixel repition */
#define BSP_ADV7611_AVI_INFO_PIXREP_NONE                ((UInt32) 0U)
#define BSP_ADV7611_AVI_INFO_PIXREP_2X                  ((UInt32) 1U)
#define BSP_ADV7611_AVI_INFO_PIXREP_4X                  ((UInt32) 3U)

/* AVI packet info values */
#define BSP_ADV7611_AVI_INFO_PACKET_CODE                ((UInt8) 0x82U)
#define BSP_ADV7611_AVI_INFO_VERSION_CODE               ((UInt8) 0x02U)
#define BSP_ADV7611_AVI_INFO_PACKET_LENGTH              ((UInt8) 0x0DU)

/*
 * Reconfigured 7-bit I2C address of all the ports.
 * This can be changed to avoid I2C conflicts.
 * As of now DPLL, KSV and EDID addresses are re-mapped to 0x55, 0x56 and 0x57
 * instead of the default values of 0x26, 0x32 and 0x36 respectively.
 */
#define BSP_ADV7611_IO_I2C_ADDR                 (0x4CU)
#define BSP_ADV7611_CEC_I2C_ADDR                (0x40U)
#define BSP_ADV7611_INFOFRAME_I2C_ADDR          (0x3EU)
#define BSP_ADV7611_DPLL_I2C_ADDR               (0x55U)
#define BSP_ADV7611_KSV_I2C_ADDR                (0x56U)
#define BSP_ADV7611_EDID_I2C_ADDR               (0x57U)
#define BSP_ADV7611_HDMI_I2C_ADDR               (0x34U)
#define BSP_ADV7611_CP_I2C_ADDR                 (0x22U)

/* XTAL frequency in Hz */
#define BSP_ADV7611_XTAL_FREQ_HZ                ((UInt32) 28636300U)

/* TMDSPLL_LCK_A_RAW (bit 6), TMDS_CLK_A_RAW (bit 4) and V_LOCKED_RAW (bit 1) */
#define BSP_ADV7611_VID_DETECT_MASK             ((UInt32) 0x52U)

#define BSP_ADV7611_VID_INTERLACE_MASK          ((UInt32) 0x10U)
#define BSP_ADV7611_CH1_STDI_DVALID_MASK        (0x80U)

#define BSP_ADV7611_OP_FMT_8_BIT_SDR_ITU_656    (0x00U)
#define BSP_ADV7611_OP_FMT_12_BIT_SDR_ITU_MODE2 (0x0AU)
#define BSP_ADV7611_OP_FMT_8_BIT_DDR_422        (0x20U)
#define BSP_ADV7611_OP_FMT_12_BIT_DDR_422_MODE2 (0x2AU)
#define BSP_ADV7611_OP_FMT_24_BIT_SDR_444       (0x40U)
#define BSP_ADV7611_OP_FMT_24_BIT_DDR_444       (0x60U)
#define BSP_ADV7611_OP_FMT_16_BIT_SDR_ITU_656   (0x80U)
#define BSP_ADV7611_OP_FMT_24_BIT_SDR_ITU_MODE2 (0x8AU)

/* Channel Map: 23:16_15:08_07:00 */
#define BSP_ADV7611_OP_CH_SEL_YG_UCRCB_VR       (0x02U)
#define BSP_ADV7611_OP_CH_SEL_YG_VR_UCRCB       (0x22U)
#define BSP_ADV7611_OP_CH_SEL_UCRCB_YG_VR       (0x42U)
#define BSP_ADV7611_OP_CH_SEL_VR_YG_UCRCB       ((UInt8) 0x62U)
#define BSP_ADV7611_OP_CH_SEL_UCRCB_VR_YG       (0x82U)
#define BSP_ADV7611_OP_CH_SEL_VR_UCRCB_YG       ((UInt8) 0xA2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief ADV7611 driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidDecCreateParams    createPrms;
    /**< Create time arguments. */
    Bsp_VidDecVideoModeParams modePrms;
    /**< Video decoder mode parameters. */
} Bsp_Adv7611HandleObj;

/**
 *  \brief ADV7611 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle    lock;
    /**< Global driver lock. */
    Bsp_Adv7611HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_Adv7611Obj;

/**
 *  \brief Information that is parsed from HDMI AVIInfoFrame packet.
 */
typedef struct
{
    UInt32 colorSpace;
    /**< RGB444 or YUV422 or YUV422. */
    UInt32 colorImetric;
    /**< BT709 or BT601. */
    UInt32 pixelRepeat;
    /**< 1x, 2x, 4x. */
} Bsp_Adv7611AviInfoFrame;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 Bsp_adv7611Reset(Bsp_Adv7611HandleObj *pObj);
Int32 Bsp_adv7611GetChipId(Bsp_Adv7611HandleObj         *pObj,
                           const Bsp_VidDecChipIdParams *pPrm,
                           Bsp_VidDecChipIdStatus       *pStatus);

Int32 Bsp_adv7611SetVideoMode(Bsp_Adv7611HandleObj            *pObj,
                              const Bsp_VidDecVideoModeParams *pPrm);
Int32 Bsp_adv7611GetVideoStatus(Bsp_Adv7611HandleObj              *pObj,
                                const Bsp_VidDecVideoStatusParams *pPrm,
                                Bsp_VidDecVideoStatus             *pStatus);

Int32 Bsp_adv7611Start(Bsp_Adv7611HandleObj *pObj);
Int32 Bsp_adv7611Stop(Bsp_Adv7611HandleObj *pObj);

Int32 Bsp_adv7611RegWrite(Bsp_Adv7611HandleObj          *pObj,
                          const Bsp_VidDecRegRdWrParams *pPrm);
Int32 Bsp_adv7611RegRead(Bsp_Adv7611HandleObj    *pObj,
                         Bsp_VidDecRegRdWrParams *pPrm);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSPDRV_ADV7611_PRIV_H_ */
