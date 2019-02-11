/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  \file bspdrv_ov2659Priv.h
 *
 *  \brief ov2659 decoder internal header file.
 */

#ifndef BSPDRV_OV2659_PRIV_H_
#define BSPDRV_OV2659_PRIV_H_

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
#include <ti/drv/vps/include/devices/bsp_videoSensor.h>
#include <ov2659/bspdrv_ov2659.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_OV2659_OBJ_STATE_UNUSED                    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_OV2659_OBJ_STATE_IDLE                      (1U)

/** Default value @ 0x3005 is read. The value at 0x3005 should be 0x24. */
#define BSP_VID_SENSOR_OV2659_DEFAULT_RD               (0x24U)
#define BSP_VID_SENSOR_OV2659_PID_MSB                  (0x26U)
#define BSP_VID_SENSOR_OV2659_PID_LSB                  (0x56U)

#define BSP_OV2659_ACTIVE_PIXELS_H                     (1632U)
/** < NUmber of active pixel in sensor array width*/

#define BSP_OV2659_ACTIVE_PIXELS_V                     (1212U)
/** <Number of active pixel in sensor array height */

#define BSP_VID_SENSOR_OV2659_DUMMY_LINES_TOP          (3U)
/** < NUmber of dummy lines from the top*/
#define BSP_VID_SENSOR_OV2659_DUMMY_LINES_BOTTOM       (3U)
/** < NUmber of dummy lines from the Bottom*/

#define BSP_OV2659_X_CLK                               (20000000U)
/**< XCLK 20MHz */

#define BSP_VID_SENSOR_OV2659_MAX_LINES_OUTPUT         (1200U)
/**< Max number of lines that can be output */

#define BSP_OV2659_NUM_REGS                  (158U)

#define BSP_OV2659_VTS_CONST                 (17820U)

/* Array end token */
#define BSP_OV2659_REG_NULL                  (0x0000U)


/* OmniVision OV2659 registers */
#define BSP_OV2659_SOFTWARE_STANDBY          (0x0100U)
#define BSP_OV2659_SOFTWARE_RESET            (0x0103U)
#define BSP_OV2659_IO_CTRL00                 (0x3000U)
#define BSP_OV2659_IO_CTRL01                 (0x3001U)
#define BSP_OV2659_IO_CTRL02                 (0x3002U)
#define BSP_OV2659_OUTPUT_VALUE00            (0x3008U)
#define BSP_OV2659_OUTPUT_VALUE01            (0x3009U)
#define BSP_OV2659_OUTPUT_VALUE02            (0x300DU)
#define BSP_OV2659_OUTPUT_SELECT00           (0x300EU)
#define BSP_OV2659_OUTPUT_SELECT01           (0x300FU)
#define BSP_OV2659_OUTPUT_SELECT02           (0x3010U)
#define BSP_OV2659_OUTPUT_DRIVE              (0x3011U)
#define BSP_OV2659_INPUT_READOUT00           (0x302DU)
#define BSP_OV2659_INPUT_READOUT01           (0x302EU)
#define BSP_OV2659_INPUT_READOUT02           (0x302FU)

#define BSP_OV2659_SC_PLL_CTRL0              (0x3003U)
#define BSP_OV2659_SC_PLL_CTRL1              (0x3004U)
#define BSP_OV2659_SC_PLL_CTRL2              (0x3005U)
#define BSP_OV2659_SC_PLL_CTRL3              (0x3006U)
#define BSP_OV2659_SC_CHIP_ID_H              (0x300AU)
#define BSP_OV2659_SC_CHIP_ID_L              (0x300BU)
#define BSP_OV2659_SC_PWC                    (0x3014U)
#define BSP_OV2659_SC_CLKRST0                (0x301AU)
#define BSP_OV2659_SC_CLKRST1                (0x301BU)
#define BSP_OV2659_SC_CLKRST2                (0x301CU)
#define BSP_OV2659_SC_CLKRST3                (0x301DU)
#define BSP_OV2659_SC_SUB_ID                 (0x302AU)
#define BSP_OV2659_SC_SCCB_ID                (0x302BU)

#define BSP_OV2659_GROUP_ADDRESS_00          (0x3200U)
#define BSP_OV2659_GROUP_ADDRESS_01          (0x3201U)
#define BSP_OV2659_GROUP_ADDRESS_02          (0x3202U)
#define BSP_OV2659_GROUP_ADDRESS_03          (0x3203U)
#define BSP_OV2659_GROUP_ACCESS              (0x3208U)

#define BSP_OV2659_AWB_R_GAIN_H              (0x3400U)
#define BSP_OV2659_AWB_R_GAIN_L              (0x3401U)
#define BSP_OV2659_AWB_G_GAIN_H              (0x3402U)
#define BSP_OV2659_AWB_G_GAIN_L              (0x3403U)
#define BSP_OV2659_AWB_B_GAIN_H              (0x3404U)
#define BSP_OV2659_AWB_B_GAIN_L              (0x3405U)
#define BSP_OV2659_AWB_MANUAL_CONTROL        (0x3406U)

#define BSP_OV2659_TIMING_HS_H               (0x3800U)
#define BSP_OV2659_TIMING_HS_L               (0x3801U)
#define BSP_OV2659_TIMING_VS_H               (0x3802U)
#define BSP_OV2659_TIMING_VS_L               (0x3803U)
#define BSP_OV2659_TIMING_HW_H               (0x3804U)
#define BSP_OV2659_TIMING_HW_L               (0x3805U)
#define BSP_OV2659_TIMING_VH_H               (0x3806U)
#define BSP_OV2659_TIMING_VH_L               (0x3807U)
#define BSP_OV2659_TIMING_DVPHO_H            (0x3808U)
#define BSP_OV2659_TIMING_DVPHO_L            (0x3809U)
#define BSP_OV2659_TIMING_DVPVO_H            (0x380AU)
#define BSP_OV2659_TIMING_DVPVO_L            (0x380BU)
#define BSP_OV2659_TIMING_HTS_H              (0x380CU)
#define BSP_OV2659_TIMING_HTS_L              (0x380DU)
#define BSP_OV2659_TIMING_VTS_H              (0x380EU)
#define BSP_OV2659_TIMING_VTS_L              (0x380FU)
#define BSP_OV2659_TIMING_HOFFS_H            (0x3810U)
#define BSP_OV2659_TIMING_HOFFS_L            (0x3811U)
#define BSP_OV2659_TIMING_VOFFS_H            (0x3812U)
#define BSP_OV2659_TIMING_VOFFS_L            (0x3813U)
#define BSP_OV2659_TIMING_XINC               (0x3814U)
#define BSP_OV2659_TIMING_YINC               (0x3815U)
#define BSP_OV2659_TIMING_VERT_FORMAT        (0x3820U)
#define BSP_OV2659_TIMING_HORIZ_FORMAT       (0x3821U)

#define BSP_OV2659_AEC_PK_EXPOSURE_H         (0x3500U)
#define BSP_OV2659_AEC_PK_EXPOSURE_M         (0x3501U)
#define BSP_OV2659_AEC_PK_EXPOSURE_L         (0x3502U)
#define BSP_OV2659_AEC_PK_MANUAL             (0x3503U)
#define BSP_OV2659_AEC_MANUAL_GAIN_H         (0x3504U)
#define BSP_OV2659_AEC_MANUAL_GAIN_L         (0x3505U)
#define BSP_OV2659_AEC_ADD_VTS_H             (0x3506U)
#define BSP_OV2659_AEC_ADD_VTS_L             (0x3507U)
#define BSP_OV2659_AEK_PK_CTRL_08            (0x3508U)
#define BSP_OV2659_AEK_PK_CTRL_09            (0x3509U)
#define BSP_OV2659_AEC_PK_REAL_GAIN_H        (0x350AU)
#define BSP_OV2659_AEC_PK_REAL_GAIN_L        (0x350BU)
#define BSP_OV2659_AEC_REAL_GAIN_READ_H      (0x3510U)
#define BSP_OV2659_AEC_REAL_GAIN_READ_L      (0x3511U)
#define BSP_OV2659_AEC_SNR_GAIN_READ_H       (0x3512U)
#define BSP_OV2659_AEC_SNR_GAIN_READ_L       (0x3513U)
#define BSP_OV2659_AEC_CTRL00                (0x3A00U)
#define BSP_OV2659_AEC_CTRL01                (0x3A01U)
#define BSP_OV2659_AEC_CTRL02                (0x3A02U)
#define BSP_OV2659_AEC_CTRL03                (0x3A03U)
#define BSP_OV2659_AEC_CTRL04                (0x3A04U)
#define BSP_OV2659_AEC_CTRL05                (0x3A05U)
#define BSP_OV2659_AEC_CTRL06                (0x3A06U)
#define BSP_OV2659_AEC_CTRL07                (0x3A07U)
#define BSP_OV2659_AEC_CTRL08                (0x3A08U)
#define BSP_OV2659_AEC_CTRL09                (0x3A09U)
#define BSP_OV2659_AEC_CTRL0A                (0x3A0AU)
#define BSP_OV2659_AEC_CTRL0B                (0x3A0BU)
#define BSP_OV2659_AEC_CTRL0C                (0x3A0CU)
#define BSP_OV2659_AEC_CTRL0D                (0x3A0DU)
#define BSP_OV2659_AEC_CTRL0E                (0x3A0EU)
#define BSP_OV2659_AEC_CTRL0F                (0x3A0FU)
#define BSP_OV2659_AEC_CTRL10                (0x3A10U)
#define BSP_OV2659_AEC_CTRL11                (0x3A11U)
#define BSP_OV2659_AEC_CTRL12                (0x3A12U)
#define BSP_OV2659_AEC_CTRL13                (0x3A13U)
#define BSP_OV2659_AEC_CTRL14                (0x3A14U)
#define BSP_OV2659_AEC_CTRL15                (0x3A15U)
#define BSP_OV2659_AEC_CTRL16                (0x3A16U)
#define BSP_OV2659_AEC_CTRL17                (0x3A17U)
#define BSP_OV2659_AEC_CTRL18                (0x3A18U)
#define BSP_OV2659_AEC_CTRL19                (0x3A19U)
#define BSP_OV2659_AEC_CTRL1A                (0x3A1AU)
#define BSP_OV2659_AEC_CTRL1B                (0x3A1BU)
#define BSP_OV2659_AEC_CTRL1C                (0x3A1CU)
#define BSP_OV2659_AEC_CTRL1D                (0x3A1DU)
#define BSP_OV2659_AEC_CTRL1E                (0x3A1EU)
#define BSP_OV2659_AEC_CTRL1F                (0x3A1FU)
#define BSP_OV2659_AEC_CTRL20                (0x3A20U)
#define BSP_OV2659_AEC_CTRL21                (0x3A21U)
#define BSP_OV2659_AEC_CTRL25                (0x3A25U)
#define BSP_OV2659_AEC_CTRL26                (0x3A26U)

#define BSP_OV2659_FRAME_CTRL00              (0x4201U)
#define BSP_OV2659_FRAME_CTRL01              (0x4202U)
#define BSP_OV2659_CLIPPING_CTRL             (0x4301U)
#define BSP_OV2659_FORMAT_CTRL00             (0x4300U)

#define BSP_OV2659_VFIFO_READ_CTRL           (0x4601U)
#define BSP_OV2659_VFIFO_CTRL05              (0x4605U)
#define BSP_OV2659_VFIFO_READ_START_H        (0x4608U)
#define BSP_OV2659_VFIFO_READ_START_L        (0x4609U)

#define BSP_OV2659_DVP_CTRL01                (0x4704U)
#define BSP_OV2659_DVP_CTRL02                (0x4708U)
#define BSP_OV2659_DVP_CTRL03                (0x4709U)

#define BSP_OV2659_ISP_CTRL00                (0x5000U)
#define BSP_OV2659_ISP_CTRL01                (0x5001U)
#define BSP_OV2659_ISP_CTRL02                (0x5002U)
#define BSP_OV2659_ISP_CTRL07                (0x5007U)
#define BSP_OV2659_ISP_PRE_CTRL00            (0x50A0U)

#define BSP_OV2659_BLC_CTRL00                (0x4000U)
#define BSP_OV2659_BLC_START_LINE            (0x4001U)
#define BSP_OV2659_BLC_CTRL02                (0x4002U)
#define BSP_OV2659_BLC_CTRL03                (0x4003U)
#define BSP_OV2659_BLC_LINE_NUM              (0x4004U)
#define BSP_OV2659_BLC_TARGET                (0x4009U)

#define BSP_OV2659_LENC_RED_X0_H             (0x500CU)
#define BSP_OV2659_LENC_RED_X0_L             (0x500DU)
#define BSP_OV2659_LENC_RED_Y0_H             (0x500EU)
#define BSP_OV2659_LENC_RED_Y0_L             (0x500FU)
#define BSP_OV2659_LENC_RED_A1               (0x5010U)
#define BSP_OV2659_LENC_RED_B1               (0x5011U)
#define BSP_OV2659_LENC_RED_A2_B2            (0x5012U)
#define BSP_OV2659_LENC_GREEN_X0_H           (0x5013U)
#define BSP_OV2659_LENC_GREEN_X0_L           (0x5014U)
#define BSP_OV2659_LENC_GREEN_Y0_H           (0x5015U)
#define BSP_OV2659_LENC_GREEN_Y0_L           (0x5016U)
#define BSP_OV2659_LENC_GREEN_A1             (0x5017U)
#define BSP_OV2659_LENC_GREEN_B1             (0x5018U)
#define BSP_OV2659_LENC_GREEN_A2_B2          (0x5019U)
#define BSP_OV2659_LENC_BLUE_X0_H            (0x501AU)
#define BSP_OV2659_LENC_BLUE_X0_L            (0x501BU)
#define BSP_OV2659_LENC_BLUE_Y0_H            (0x501CU)
#define BSP_OV2659_LENC_BLUE_Y0_L            (0x501DU)
#define BSP_OV2659_LENC_BLUE_A1              (0x501EU)
#define BSP_OV2659_LENC_BLUE_B1              (0x501FU)
#define BSP_OV2659_LENC_BLUE_A2_B2           (0x5020U)
#define BSP_OV2659_LENC_CTRL00               (0x5021U)
#define BSP_OV2659_LENC_CTRL01               (0x5022U)
#define BSP_OV2659_COEFFICIENT_THRESH        (0x5023U)
#define BSP_OV2659_COEFFICIENT_MANUAL_VAL    (0x5024U)

#define BSP_OV2659_GAMMA_YST1                (0x5025U)
#define BSP_OV2659_GAMMA_YST2                (0x5026U)
#define BSP_OV2659_GAMMA_YST3                (0x5027U)
#define BSP_OV2659_GAMMA_YST4                (0x5028U)
#define BSP_OV2659_GAMMA_YST5                (0x5029U)
#define BSP_OV2659_GAMMA_YST6                (0x502AU)
#define BSP_OV2659_GAMMA_YST7                (0x502BU)
#define BSP_OV2659_GAMMA_YST8                (0x502CU)
#define BSP_OV2659_GAMMA_YST9                (0x502DU)
#define BSP_OV2659_GAMMA_YST10               (0x502EU)
#define BSP_OV2659_GAMMA_YST11               (0x502FU)
#define BSP_OV2659_GAMMA_YST12               (0x5030U)
#define BSP_OV2659_GAMMA_YST13               (0x5031U)
#define BSP_OV2659_GAMMA_YST14               (0x5032U)
#define BSP_OV2659_GAMMA_YST15               (0x5033U)
#define BSP_OV2659_GAMMA_YSLP                (0x5034U)

#define BSP_OV2659_AWB_CTRL00                (0x5035U)
#define BSP_OV2659_AWB_CTRL01                (0x5036U)
#define BSP_OV2659_AWB_CTRL02                (0x5037U)
#define BSP_OV2659_AWB_CTRL03                (0x5038U)
#define BSP_OV2659_AWB_CTRL04                (0x5039U)
#define BSP_OV2659_AWB_LOCAL_LIMIT           (0x503AU)
#define BSP_OV2659_AWB_CTRL12                (0x5049U)
#define BSP_OV2659_AWB_CTRL13                (0x504AU)
#define BSP_OV2659_AWB_CTRL14                (0x504BU)

#define BSP_OV2659_AVG_CTRL00                (0x5060U)
#define BSP_OV2659_AVG_CTRL01                (0x5061U)
#define BSP_OV2659_AVG_CTRL02                (0x5062U)
#define BSP_OV2659_AVG_CTRL03                (0x5063U)
#define BSP_OV2659_AVG_READOUT               (0x5237U)

#define BSP_OV2659_SHARPENMT_THRESH1         (0x5064U)
#define BSP_OV2659_SHARPENMT_THRESH2         (0x5065U)
#define BSP_OV2659_SHARPENMT_OFFSET1         (0x5066U)
#define BSP_OV2659_SHARPENMT_OFFSET2         (0x5067U)
#define BSP_OV2659_DENOISE_THRESH1           (0x5068U)
#define BSP_OV2659_DENOISE_THRESH2           (0x5069U)
#define BSP_OV2659_DENOISE_OFFSET1           (0x506AU)
#define BSP_OV2659_DENOISE_OFFSET2           (0x506BU)
#define BSP_OV2659_SHARPEN_THRESH1           (0x506CU)
#define BSP_OV2659_SHARPEN_THRESH2           (0x506DU)
#define BSP_OV2659_CIP_CTRL00                (0x506EU)
#define BSP_OV2659_CIP_CTRL01                (0x506FU)

#define BSP_OV2659_CMX1                      (0x5070U)
#define BSP_OV2659_CMX2                      (0x5071U)
#define BSP_OV2659_CMX3                      (0x5072U)
#define BSP_OV2659_CMX4                      (0x5073U)
#define BSP_OV2659_CMX5                      (0x5074U)
#define BSP_OV2659_CMX6                      (0x5075U)
#define BSP_OV2659_CMX7                      (0x5076U)
#define BSP_OV2659_CMX8                      (0x5077U)
#define BSP_OV2659_CMX9                      (0x5078U)
#define BSP_OV2659_CMX_SIGN                  (0x5079U)
#define BSP_OV2659_CMX_MISC_CTRL             (0x507AU)

#define BSP_OV2659_SDE_CTRL                  (0x507BU)

#define BSP_OV2659_SCALE_CTRL0               (0x5600U)
#define BSP_OV2659_SCALE_CTRL1               (0x5601U)
#define BSP_OV2659_XSC_H                     (0x5602U)
#define BSP_OV2659_XSC_L                     (0x5603U)
#define BSP_OV2659_YSC_H                     (0x5604U)
#define BSP_OV2659_YSC_L                     (0x5605U)
#define BSP_OV2659_VOFFSET                   (0x5606U)


/**
 *  \brief OV1063x driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    UInt32                    nDrvId;
    /**< Driver Id - LI_OV,MULDES_OV, OV */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidSensorCreateParams createPrms;
    /**< Create time arguments. */
    Bsp_VidSensorFeatures     sensorFeature;
    /**< Sensor capabilities */
    Bsp_VidSensorConfigParams sensorConfig;
} Bsp_Ov2659HandleObj;

/**
 *  \brief OV1063x Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle    lock;
    /* Global driver lock. */
    Bsp_Ov2659HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_Ov2659Obj;

Int32 Bsp_ov2659GetChipId(Bsp_Ov2659HandleObj            *pObj,
                           const Bsp_VidSensorChipIdParams *pPrm,
                           Bsp_VidSensorChipIdStatus       *pStatus);

Int32 Bsp_ov2659GetSensorFeatures(const Bsp_Ov2659HandleObj *pObj,
                                   Bsp_VidSensorFeatures      *pSenFeature);

Int32 Bsp_ov2659SoftwareReset(const Bsp_Ov2659HandleObj *pObj);

Int32 Bsp_ov2659SensorStartStop(const Bsp_Ov2659HandleObj *pObj,
                                 UInt32                      bStartSensor);

Int32 Bsp_ov2659SetConfig(Bsp_Ov2659HandleObj            *pObj,
                           const Bsp_VidSensorConfigParams *configParams);

Int32 Bsp_ov2659SensorConfig(
    const Bsp_Ov2659HandleObj *pObj,
    Bsp_VidSensorConfigRegs    *sensorConfig,
    UInt32
    numSensorConfigEntries);

Int32 Bsp_ov2659RegWrite(Bsp_Ov2659HandleObj             *pObj,
                          const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ov2659RegRead(Bsp_Ov2659HandleObj       *pObj,
                         Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ov2659SetFlipParams(const Bsp_Ov2659HandleObj    *pObj,
                               const Bsp_VidSensorFlipParams *pPrm);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_OV2659_PRIV_H_  */

