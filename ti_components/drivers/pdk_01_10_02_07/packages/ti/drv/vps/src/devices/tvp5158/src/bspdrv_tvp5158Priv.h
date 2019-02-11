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
 *  \file bspdrv_tvp5158Priv.h
 *
 *  \brief TVP5158 decoder internal header file.
 */

#ifndef BSP_TVP5158_PRIV_H_
#define BSP_TVP5158_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/devices/bsp_videoDecoder.h>
#include <ti/drv/vps/include/devices/bsp_tvp5158.h>
#include <tvp5158/bspdrv_tvp5158.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSP_TVP5158_DEBUG
/* #define BSP_TVP5158_VERBOSE_DEBUG */

/* #define BSP_TVP5158_ENABLE_NF */
#define BSP_TVP5158_ENABLE_FIRMWARE_PATCHES

#define BSP_TVP5158_ENABLE_COMB_FILTER_SETUP

/* Uncomment this to NOT download TVP5158 patch */
/*#define BSP_TVP5158_NO_PATCH_DOWNLOAD*/

/* Uncomment this to FORCE TVP5158 patch download each time
 * IOCTL_BSP_VID_DEC_SET_VIDEO_MODE is called
 */
/*#define BSP_TVP5158_FORCE_PATCH_DOWNLOAD*/

/* Max possible channel per TVP5158 device  */
#define BSP_TVP5158_CH_PER_DEVICE_MAX   ((UInt32) 4U)

/* Max possible devices cascade together to feed video data to one video port */
#define BSP_TVP5158_DEV_PER_PORT_MAX    ((UInt32) 2U)

/* Apply settings to all core's */
#define BSP_TVP5158_CORE_ALL            ((UInt32) 0x0FU)

/** \brief Driver object state - NOT IN USE. */
#define BSP_TVP5158_OBJ_STATE_UNUSED    ((UInt32) 0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_TVP5158_OBJ_STATE_IDLE      ((UInt32) 1U)

/*
 * TVP5158 Register Offsets.
 */
#define BSP_TVP5158_REG_STATUS_1        ((UInt32) 0x00U)
#define BSP_TVP5158_REG_STATUS_2        ((UInt32) 0x01U)
#define BSP_TVP5158_REG_ROM_VERSION     ((UInt32) 0x04U)
#define BSP_TVP5158_REG_RAM_VERSION_0   ((UInt32) 0x05U)
#define BSP_TVP5158_REG_RAM_VERSION_1   ((UInt32) 0x06U)
#define BSP_TVP5158_REG_CHIP_ID_MSB     ((UInt32) 0x08U)
#define BSP_TVP5158_REG_CHIP_ID_LSB     ((UInt32) 0x09U)
#define BSP_TVP5158_REG_VID_STD_STATUS  ((UInt32) 0x0CU)
#define BSP_TVP5158_REG_VID_STD_SELECT  ((UInt32) 0x0DU)
#define BSP_TVP5158_REG_AUTO_SW_MASK    ((UInt32) 0x0EU)
#define BSP_TVP5158_REG_Y_BRIGHTNESS    ((UInt32) 0x10U)
#define BSP_TVP5158_REG_Y_CONTRAST      ((UInt32) 0x11U)
#define BSP_TVP5158_REG_C_SATURATION    ((UInt32) 0x13U)
#define BSP_TVP5158_REG_C_HUE           ((UInt32) 0x14U)
#define BSP_TVP5158_REG_Y_CTRL_1        ((UInt32) 0x18U)
#define BSP_TVP5158_REG_Y_CTRL_2        ((UInt32) 0x19U)
#define BSP_TVP5158_REG_C_CTRL_1        ((UInt32) 0x1BU)
#define BSP_TVP5158_REG_C_CTRL_2        ((UInt32) 0x1CU)
#define BSP_TVP5158_REG_NR_MAX_NOISE    ((UInt32) 0x5CU)
#define BSP_TVP5158_REG_NR_CTRL         ((UInt32) 0x5DU)
#define BSP_TVP5158_REG_OP_MODE_CTRL    ((UInt32) 0x60U)
#define BSP_TVP5158_REG_FV_DEC_CTRL     ((UInt32) 0x88U)
#define BSP_TVP5158_REG_FV_CTRL         ((UInt32) 0x89U)
#define BSP_TVP5158_REG_FBIT_DURATION   ((UInt32) 0x8BU)
#define BSP_TVP5158_REG_ESYNC_OFFSET_1  ((UInt32) 0xAEU)
#define BSP_TVP5158_REG_ESYNC_OFFSET_2  ((UInt32) 0xAFU)
#define BSP_TVP5158_REG_AVD_OUT_CTRL_1  ((UInt32) 0xB0U)
#define BSP_TVP5158_REG_AVD_OUT_CTRL_2  ((UInt32) 0xB1U)
#define BSP_TVP5158_REG_OFM_MODE_CTRL   ((UInt32) 0xB2U)
#define BSP_TVP5158_REG_OFM_CH_SEL_1    ((UInt32) 0xB3U)
#define BSP_TVP5158_REG_OFM_CH_SEL_2    ((UInt32) 0xB4U)
#define BSP_TVP5158_REG_OFM_CH_SEL_3    ((UInt32) 0xB5U)
#define BSP_TVP5158_REG_OFM_SFRAME_LSB  ((UInt32) 0xB6U)
#define BSP_TVP5158_REG_OFM_SFRAME_MSB  ((UInt32) 0xB7U)
#define BSP_TVP5158_REG_OFM_HBLANK_LSB  ((UInt32) 0xB8U)
#define BSP_TVP5158_REG_OFM_HBLANK_MSB  ((UInt32) 0xB9U)
#define BSP_TVP5158_REG_MISC_OFM_CTRL   ((UInt32) 0xBAU)
#define BSP_TVP5158_REG_AUDIO_SAMPLE_HZ ((UInt32) 0xC0U)
#define BSP_TVP5158_REG_AUDIO_GAIN_1    ((UInt32) 0xC1U)
#define BSP_TVP5158_REG_AUDIO_GAIN_2    ((UInt32) 0xC2U)
#define BSP_TVP5158_REG_AUDIO_CTRL      ((UInt32) 0xC3U)
#define BSP_TVP5158_REG_AUDIO_MIXER     ((UInt32) 0xC4U)
#define BSP_TVP5158_REG_AUDIO_CASCADE   ((UInt32) 0xC8U)
#define BSP_TVP5158_REG_MIN_F1_ACT      ((UInt32) 0xD5U)
#define BSP_TVP5158_REG_DEC_WR_EN       ((UInt32) 0xFEU)
#define BSP_TVP5158_REG_DEC_RD_EN       ((UInt32) 0xFFU)

/*
 * TVP5158 Audio Control values.
 */
#define BSP_TVP5158_AUDIO_CTRL_SD_R_ENABLE  ((UInt32) 0x1U)
#define BSP_TVP5158_AUDIO_CTRL_64_FS        ((UInt32) 0x1U)

/*
 * TVP5158 register field values.
 */
/* Mode of operation  */
#define BSP_TVP5158_NON_INTERLEAVED_MODE            ((UInt32) 0U)
#define BSP_TVP5158_PIXEL_INTERLEAVED_MODE          ((UInt32) 1U)
#define BSP_TVP5158_LINE_INTERLEAVED_MODE           ((UInt32) 2U)
#define BSP_TVP5158_LINE_INTERLEAVED_HYBRID_MODE    ((UInt32) 3U)

/* Number of channels */
#define BSP_TVP5158_1CH_MUX             ((UInt32) 0U)
#define BSP_TVP5158_2CH_MUX             ((UInt32) 1U)
#define BSP_TVP5158_4CH_MUX             ((UInt32) 2U)
#define BSP_TVP5158_8CH_MUX             ((UInt32) 3U)

/* Resolution */
#define BSP_TVP5158_RES_D1              ((UInt32) 0U)
#define BSP_TVP5158_RES_HALF_D1         ((UInt32) 2U)
#define BSP_TVP5158_RES_CIF             ((UInt32) 3U)

/* 8-bit or 16-bit data width */
#define BSP_TVP5158_OUT_TYPE_8BIT       ((UInt32) 0U)
#define BSP_TVP5158_OUT_TYPE_16BIT      ((UInt32) 1U)

/* Super-frame size type  */
#define BSP_TVP5158_SUPER_FRAME_SIZE_525_STD    ((UInt32) 0U)
#define BSP_TVP5158_SUPER_FRAME_SIZE_625_STD    ((UInt32) 1U)
#define BSP_TVP5158_SUPER_FRAME_SIZE_MANUAL     ((UInt32) 3U)

/* Bit pattern to enable TVP5158 output */
#define BSP_TVP5158_OUT_ENABLE          ((UInt32) 0x05U)

/* TVP5158 status */
#define BSP_TVP5158_HSYNC_LOCKED        ((UInt32) 0x02U)
#define BSP_TVP5158_VSYNC_LOCKED        ((UInt32) 0x04U)
#define BSP_TVP5158_SIGNAL_DETECT       ((UInt32) 0x80U)
#define BSP_TVP5158_SIGNAL_60HZ         ((UInt32) 0x20U)
#define BSP_TVP5158_VID_STD_MASK        ((UInt32) 0x07U)

/* TVP5158 video standard's */
#define BSP_TVP5158_VID_STD_PAL_BDGHIN  ((UInt32) 0x02U)
#define BSP_TVP5158_VID_STD_PAL_M       ((UInt32) 0x03U)
#define BSP_TVP5158_VID_STD_PAL_COMB_N  ((UInt32) 0x04U)
#define BSP_TVP5158_VID_STD_PAL_60      ((UInt32) 0x07U)
#define BSP_TVP5158_VID_STD_NTSC_MJ     ((UInt32) 0x01U)
#define BSP_TVP5158_VID_STD_NTSC_4_43   ((UInt32) 0x05U)

#define BSP_TVP5158_NTSC_PAL_WIDTH      ((UInt32) 720U)
#define BSP_TVP5158_NTSC_HEIGHT         ((UInt32) 240U)
#define BSP_TVP5158_PAL_HEIGHT          ((UInt32) 288U)

/* Audio sampling rate  */
#define BSP_TVP5158_AUDIO_16KHZ         ((UInt32) 0U)
#define BSP_TVP5158_AUDIO_8KHZ          ((UInt32) 2U)

/* Audio TDM mode */
#define BSP_TVP5158_AUDIO_TDM_2CH       ((UInt32) 0x00U)
#define BSP_TVP5158_AUDIO_TDM_4CH       ((UInt32) 0x01U)
#define BSP_TVP5158_AUDIO_TDM_8CH       ((UInt32) 0x02U)
#define BSP_TVP5158_AUDIO_TDM_12CH      ((UInt32) 0x03U)
#define BSP_TVP5158_AUDIO_TDM_16CH      ((UInt32) 0x04U)

#define BSP_TVP5158_PATCH_NUMVAL        ((UInt32) 11176U)
#define BSP_TVP5158_VBUS_ADDRVALSET     ((UInt32) 124U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief TVP5158 driver handle object.
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
} Bsp_Tvp5158HandleObj;

/**
 *  \brief TVP5158 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle    lock;
    /* Global driver lock. */
    Bsp_Tvp5158HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_Tvp5158Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 Bsp_tvp5158Reset(Bsp_Tvp5158HandleObj *pObj);
Int32 Bsp_tvp5158GetChipId(Bsp_Tvp5158HandleObj         *pObj,
                           const Bsp_VidDecChipIdParams *pPrm,
                           Bsp_VidDecChipIdStatus       *pStatus);

Int32 Bsp_tvp5158SetVideoMode(Bsp_Tvp5158HandleObj            *pObj,
                              const Bsp_VidDecVideoModeParams *pPrm);
Int32 Bsp_tvp5158GetVideoStatus(Bsp_Tvp5158HandleObj              *pObj,
                                const Bsp_VidDecVideoStatusParams *pPrm,
                                Bsp_VidDecVideoStatus             *pStatus);

Int32 Bsp_tvp5158Start(Bsp_Tvp5158HandleObj *pObj);
Int32 Bsp_tvp5158Stop(Bsp_Tvp5158HandleObj *pObj);

Int32 Bsp_tvp5158RegWrite(Bsp_Tvp5158HandleObj          *pObj,
                          const Bsp_VidDecRegRdWrParams *pPrm);
Int32 Bsp_tvp5158RegRead(Bsp_Tvp5158HandleObj    *pObj,
                         Bsp_VidDecRegRdWrParams *pPrm);

Int32 Bsp_tvp5158SetVideoColor(Bsp_Tvp5158HandleObj        *pObj,
                               const Bsp_VidDecColorParams *pPrm);
Int32 Bsp_tvp5158SetVideoNf(Bsp_Tvp5158HandleObj           *pObj,
                            const Bsp_Tvp5158VideoNfParams *pPrm);

Int32 Bsp_tvp5158SetAudioMode(Bsp_Tvp5158HandleObj             *pObj,
                              const Bsp_Tvp5158AudioModeParams *pPrm);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern const UInt8  gBspTvp5158Patch[BSP_TVP5158_PATCH_NUMVAL];
extern const UInt32 gBspTvp5158VbusAddrValueSet[BSP_TVP5158_VBUS_ADDRVALSET];

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_TVP5158_PRIV_H_ */
