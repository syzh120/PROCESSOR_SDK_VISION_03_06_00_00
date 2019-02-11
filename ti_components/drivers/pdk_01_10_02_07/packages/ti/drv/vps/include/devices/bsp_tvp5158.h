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
 *  \ingroup BSP_DRV_DEVICE_VID_DEC_API
 *  \defgroup BSP_DRV_DEVICE_VID_DEC_TVP5158_API TVP5158 Video Decoder API
 *
 *  This modules define API specific to TVP5158.
 *
 *  @{
 */

/**
 *  \file bsp_tvp5158.h
 *
 *  \brief TVP5158 Video Decoder API.
 */

#ifndef BSP_TVP5158_H_
#define BSP_TVP5158_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/devices/bsp_videoDecoder.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \addtogroup BSP_DRV_IOCTL_TVP5158
 *  @{
 */

/**
 *  \brief Set TVP5158 video noise filter parameters.
 *
 *  This IOCTL can be called separetly for each channel.
 *
 *  \param cmdArgs       [IN]   Bsp_Tvp5158VideoNfParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_TVP5158_SET_VIDEO_NF      (BSP_VID_DEC_IOCTL_BASE + 0x1000U)

/**
 *  \brief Set TVP5158 video noise filter parameters.
 *
 *  This IOCTL can be called separetly for each channel.
 *
 *  \param cmdArgs       [IN]   Bsp_Tvp5158AudioModeParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_TVP5158_SET_AUDIO_MODE    (BSP_VID_DEC_IOCTL_BASE + 0x1001U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Arguments for IOCTL_BSP_TVP5158_SET_VIDEO_NF.
 */
typedef struct
{
    UInt32 channelNum;
    /**< Channel number for which these parameters are to be applied. */
    UInt32 nfEnable;
    /**< TRUE: Noise filter ON, FALSE: Noise filter OFF. */
    UInt32 colorKillerEnable;
    /**< TRUE: Reduce color when noise is HIGH, FALSE: Do not reduce color. */
    UInt32 maxNoise;
    /**< Max noise level. */
} Bsp_Tvp5158VideoNfParams;

/**
 *  \brief Arguments for IOCTL_BSP_TVP5158_SET_AUDIO_MODE.
 *
 *  The audio mode is applicable for all channels associated with the
 *  device 'deviceNum'.
 */
typedef struct
{
    UInt32 deviceNum;
    /**< Device number for which to apply the audio parameters. */
    UInt32 samplingHz;
    /**< Audio sampling rate in Hz, Valid values: 8000, 16000. */
    UInt32 masterModeEnable;
    /**< TRUE: Master mode of operation, FALSE: Slave mode of operation. */
    UInt32 dspModeEnable;
    /**< TRUE: DSP data format mode, FALSE: I2S data format mode. */
    UInt32 ulawEnable;
    /**< TRUE: 8-bit ulaw data format mode, FALSE: 16-bit PCM data
     *   format mode. */
    UInt32 cascadeStage;
    /**< Cascade stage number, Valid values: 0..3. */
    UInt32 audioVolume;
    /**< Audio volume, Valid values: 0..8. Refer to TVP5158 datasheet
     *   for details. */
    UInt32 tdmChannelNum;
    /**< Number of TDM channels: 0: 2CH, 1: 4CH, 2: 8CH, 3: 12CH 4: 16CH. */
} Bsp_Tvp5158AudioModeParams;

/* ========================================================================== */
/*                         Functions                                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_TVP5158_H_ */

/* @} */
