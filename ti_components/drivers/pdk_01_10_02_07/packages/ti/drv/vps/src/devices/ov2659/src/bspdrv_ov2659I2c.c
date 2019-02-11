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
 *  \file bspdrv_ov2659I2c.c
 *
 *  \brief OV2659 sensor driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ov2659/src/bspdrv_ov2659Priv.h>
#include <stdlib.h>
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Bsp_VidSensorConfigRegs     gBsp_Ov2659SensorsDefault[
    BSP_OV2659_NUM_REGS];

static const UInt32 nRestoPllMapping[][5] =
{
  /* Standard, frame rate, pre-divide, multiply, sys divide *
   * PCLK = (((XVCLK)/pre-divide) * (Multiplier))/(2*sys divide)
   * XVCLK = 20 MHz
   * Hence PCLK = 70 MHz for PD = 1, M = 7 and SD = 1
   */
  {FVID2_STD_UXGA_60, FVID2_FPS_30, 1, 7, 1 },
  {FVID2_STD_720P_60, FVID2_FPS_30, 1, 7, 1 },
  {FVID2_STD_VGA_60,  FVID2_FPS_30, 1, 7, 1 },
  {FVID2_STD_WXGA_60, FVID2_FPS_30, 1, 7, 1 },
  {FVID2_STD_SVGA_60, FVID2_FPS_30, 1, 7, 1 },
  {FVID2_STD_XGA_60,  FVID2_FPS_30, 1, 7, 1 },
  {FVID2_STD_SXGA_60, FVID2_FPS_30, 1, 7, 1 }

};

static const Bsp_VidSensorFeatures gBspOv2659SensorFeatures =
{
    0,                             /* SensorId */
    0U,                            /* Chip Id, read from register */
    0U,                            /* Revision Id, read from register */
    0U,                            /* firmware version, read from register */
    FVID2_DF_BAYER_BGGR,           /* Bayer format */
    BSP_OV2659_ACTIVE_PIXELS_H,    /* Active Width */
    BSP_OV2659_ACTIVE_PIXELS_V,    /* Active Height */
    TRUE,                          /* isEmbededDataSupported */
    TRUE,                          /* isManualExposureSupported */
    FALSE,                         /* isEepromDataSupported */
    TRUE,                          /* isSoftStandbySupported */
    TRUE,                          /* isFlipSupported */
    FALSE,                         /* isManualAnalogGainSupported */
    FALSE,                         /* isWdrModeSupported */
    FALSE,                         /* isSetCfgSupported */
    FALSE,                         /* isDccCfgSupported */
    FALSE                          /* isOnePassWdrSupported */
};

/* 1280X720 720p */
static Bsp_VidSensorConfigRegs ov2659_720p[] = {
    { BSP_OV2659_TIMING_HS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HS_L, 0xa0, 0x00 },
    { BSP_OV2659_TIMING_VS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_L, 0xf0, 0x00 },
    { BSP_OV2659_TIMING_HW_H, 0x05, 0x00 },
    { BSP_OV2659_TIMING_HW_L, 0xbf, 0x00 },
    { BSP_OV2659_TIMING_VH_H, 0x03, 0x00 },
    { BSP_OV2659_TIMING_VH_L, 0xcb, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_H, 0x05, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_H, 0x02, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_L, 0xd0, 0x00 },
    { BSP_OV2659_TIMING_HTS_H, 0x06, 0x00 },
    { BSP_OV2659_TIMING_HTS_L, 0x4c, 0x00 },
    { BSP_OV2659_TIMING_VTS_H, 0x02, 0x00 },
    { BSP_OV2659_TIMING_VTS_L, 0xe8, 0x00 },
    { BSP_OV2659_TIMING_HOFFS_L, 0x10, 0x00 },
    { BSP_OV2659_TIMING_VOFFS_L, 0x06, 0x00 },
    { BSP_OV2659_TIMING_XINC, 0x11, 0x00 },
    { BSP_OV2659_TIMING_YINC, 0x11, 0x00 },
    { BSP_OV2659_TIMING_VERT_FORMAT, 0x80, 0x00 },
    { BSP_OV2659_TIMING_HORIZ_FORMAT, 0x00, 0x00 },
    { BSP_OV2659_AEC_CTRL03, 0xe8, 0x00 },
    { BSP_OV2659_AEC_CTRL09, 0x6f, 0x00 },
    { BSP_OV2659_AEC_CTRL0B, 0x5d, 0x00 },
    { BSP_OV2659_AEC_CTRL15, 0x9a, 0x00 },
    { BSP_OV2659_REG_NULL,   0x00, 0x00 }
};

/* 1600X1200 UXGA */
static Bsp_VidSensorConfigRegs ov2659_uxga[] = {
    { BSP_OV2659_TIMING_HS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HW_H, 0x06, 0x00 },
    { BSP_OV2659_TIMING_HW_L, 0x5f, 0x00 },
    { BSP_OV2659_TIMING_VH_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_VH_L, 0xbb, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_H, 0x06, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_L, 0x40, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_L, 0xb0, 0x00 },
    { BSP_OV2659_TIMING_HTS_H, 0x07, 0x00 },
    { BSP_OV2659_TIMING_HTS_L, 0x9f, 0x00 },
    { BSP_OV2659_TIMING_VTS_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_VTS_L, 0xd0, 0x00 },
    { BSP_OV2659_TIMING_HOFFS_L, 0x10, 0x00 },
    { BSP_OV2659_TIMING_VOFFS_L, 0x06, 0x00 },
    { BSP_OV2659_TIMING_XINC, 0x11, 0x00 },
    { BSP_OV2659_TIMING_YINC, 0x11, 0x00 },
    { 0x3a02, 0x04, 0x00 },
    { 0x3a03, 0xd0, 0x00 },
    { 0x3a08, 0x00, 0x00 },
    { 0x3a09, 0xb8, 0x00 },
    { 0x3a0a, 0x00, 0x00 },
    { 0x3a0b, 0x9a, 0x00 },
    { 0x3a0d, 0x08, 0x00 },
    { 0x3a0e, 0x06, 0x00 },
    { 0x3a14, 0x04, 0x00 },
    { 0x3a15, 0x50, 0x00 },
    { 0x3623, 0x00, 0x00 },
    { 0x3634, 0x44, 0x00 },
    { 0x3701, 0x44, 0x00 },
    { 0x3702, 0x30, 0x00 },
    { 0x3703, 0x48, 0x00 },
    { 0x3704, 0x48, 0x00 },
    { 0x3705, 0x18, 0x00 },
    { BSP_OV2659_TIMING_VERT_FORMAT, 0x80, 0x00 },
    { BSP_OV2659_TIMING_HORIZ_FORMAT, 0x00, 0x00 },
    { 0x370a, 0x12, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_H, 0x00, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_L, 0x80, 0x00 },
    { BSP_OV2659_ISP_CTRL02, 0x00, 0x00 },
    { BSP_OV2659_REG_NULL, 0x00, 0x00 }
};

/* 1280X1024 SXGA */
static Bsp_VidSensorConfigRegs ov2659_sxga[] = {
    { BSP_OV2659_TIMING_HS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HW_H, 0x06, 0x00 },
    { BSP_OV2659_TIMING_HW_L, 0x5f, 0x00 },
    { BSP_OV2659_TIMING_VH_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_VH_L, 0xb7, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_H, 0x05, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HTS_H, 0x07, 0x00 },
    { BSP_OV2659_TIMING_HTS_L, 0x9c, 0x00 },
    { BSP_OV2659_TIMING_VTS_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_VTS_L, 0xd0, 0x00 },
    { BSP_OV2659_TIMING_HOFFS_L, 0x10, 0x00 },
    { BSP_OV2659_TIMING_VOFFS_L, 0x06, 0x00 },
    { BSP_OV2659_TIMING_XINC, 0x11, 0x00 },
    { BSP_OV2659_TIMING_YINC, 0x11, 0x00 },
    { 0x3a02, 0x02, 0x00 },
    { 0x3a03, 0x68, 0x00 },
    { 0x3a08, 0x00, 0x00 },
    { 0x3a09, 0x5c, 0x00 },
    { 0x3a0a, 0x00, 0x00 },
    { 0x3a0b, 0x4d, 0x00 },
    { 0x3a0d, 0x08, 0x00 },
    { 0x3a0e, 0x06, 0x00 },
    { 0x3a14, 0x02, 0x00 },
    { 0x3a15, 0x28, 0x00 },
    { 0x3623, 0x00, 0x00 },
    { 0x3634, 0x76, 0x00 },
    { 0x3701, 0x44, 0x00 },
    { 0x3702, 0x18, 0x00 },
    { 0x3703, 0x24, 0x00 },
    { 0x3704, 0x24, 0x00 },
    { 0x3705, 0x0c, 0x00 },
    { BSP_OV2659_TIMING_VERT_FORMAT, 0x80, 0x00 },
    { BSP_OV2659_TIMING_HORIZ_FORMAT, 0x00, 0x00 },
    { 0x370a, 0x52, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_H, 0x00, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_L, 0x80, 0x00 },
    { BSP_OV2659_ISP_CTRL02, 0x00, 0x00 },
    { BSP_OV2659_REG_NULL, 0x00, 0x00 }
};

/* 1024X768 SXGA */
static Bsp_VidSensorConfigRegs ov2659_xga[] = {
    { BSP_OV2659_TIMING_HS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HW_H, 0x06, 0x00 },
    { BSP_OV2659_TIMING_HW_L, 0x5f, 0x00 },
    { BSP_OV2659_TIMING_VH_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_VH_L, 0xb7, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_H, 0x03, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HTS_H, 0x07, 0x00 },
    { BSP_OV2659_TIMING_HTS_L, 0x9c, 0x00 },
    { BSP_OV2659_TIMING_VTS_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_VTS_L, 0xd0, 0x00 },
    { BSP_OV2659_TIMING_HOFFS_L, 0x10, 0x00 },
    { BSP_OV2659_TIMING_VOFFS_L, 0x06, 0x00 },
    { BSP_OV2659_TIMING_XINC, 0x11, 0x00 },
    { BSP_OV2659_TIMING_YINC, 0x11, 0x00 },
    { 0x3a02, 0x02, 0x00 },
    { 0x3a03, 0x68, 0x00 },
    { 0x3a08, 0x00, 0x00 },
    { 0x3a09, 0x5c, 0x00 },
    { 0x3a0a, 0x00, 0x00 },
    { 0x3a0b, 0x4d, 0x00 },
    { 0x3a0d, 0x08, 0x00 },
    { 0x3a0e, 0x06, 0x00 },
    { 0x3a14, 0x02, 0x00 },
    { 0x3a15, 0x28, 0x00 },
    { 0x3623, 0x00, 0x00 },
    { 0x3634, 0x76, 0x00 },
    { 0x3701, 0x44, 0x00 },
    { 0x3702, 0x18, 0x00 },
    { 0x3703, 0x24, 0x00 },
    { 0x3704, 0x24, 0x00 },
    { 0x3705, 0x0c, 0x00 },
    { BSP_OV2659_TIMING_VERT_FORMAT, 0x80, 0x00 },
    { BSP_OV2659_TIMING_HORIZ_FORMAT, 0x00, 0x00 },
    { 0x370a, 0x52, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_H, 0x00, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_L, 0x80, 0x00 },
    { BSP_OV2659_ISP_CTRL02, 0x00, 0x00 },
    { BSP_OV2659_REG_NULL, 0x00, 0x00 }
};

/* 800X600 SVGA */
static Bsp_VidSensorConfigRegs ov2659_svga[] = {
    { BSP_OV2659_TIMING_HS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HW_H, 0x06, 0x00 },
    { BSP_OV2659_TIMING_HW_L, 0x5f, 0x00 },
    { BSP_OV2659_TIMING_VH_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_VH_L, 0xb7, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_H, 0x03, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_L, 0x20, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_H, 0x02, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_L, 0x58, 0x00 },
    { BSP_OV2659_TIMING_HTS_H, 0x05, 0x00 },
    { BSP_OV2659_TIMING_HTS_L, 0x14, 0x00 },
    { BSP_OV2659_TIMING_VTS_H, 0x02, 0x00 },
    { BSP_OV2659_TIMING_VTS_L, 0x68, 0x00 },
    { BSP_OV2659_TIMING_HOFFS_L, 0x08, 0x00 },
    { BSP_OV2659_TIMING_VOFFS_L, 0x02, 0x00 },
    { BSP_OV2659_TIMING_XINC, 0x31, 0x00 },
    { BSP_OV2659_TIMING_YINC, 0x31, 0x00 },
    { 0x3a02, 0x02, 0x00 },
    { 0x3a03, 0x68, 0x00 },
    { 0x3a08, 0x00, 0x00 },
    { 0x3a09, 0x5c, 0x00 },
    { 0x3a0a, 0x00, 0x00 },
    { 0x3a0b, 0x4d, 0x00 },
    { 0x3a0d, 0x08, 0x00 },
    { 0x3a0e, 0x06, 0x00 },
    { 0x3a14, 0x02, 0x00 },
    { 0x3a15, 0x28, 0x00 },
    { 0x3623, 0x00, 0x00 },
    { 0x3634, 0x76, 0x00 },
    { 0x3701, 0x44, 0x00 },
    { 0x3702, 0x18, 0x00 },
    { 0x3703, 0x24, 0x00 },
    { 0x3704, 0x24, 0x00 },
    { 0x3705, 0x0c, 0x00 },
    { BSP_OV2659_TIMING_VERT_FORMAT, 0x81, 0x00 },
    { BSP_OV2659_TIMING_HORIZ_FORMAT, 0x01, 0x00 },
    { 0x370a, 0x52, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_H, 0x00, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_L, 0x80, 0x00 },
    { BSP_OV2659_ISP_CTRL02, 0x00, 0x00 },
    { BSP_OV2659_REG_NULL, 0x00, 0x00 }
};

/* 640X480 VGA */
static Bsp_VidSensorConfigRegs ov2659_vga[] = {
    { BSP_OV2659_TIMING_HS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HW_H, 0x06, 0x00 },
    { BSP_OV2659_TIMING_HW_L, 0x5f, 0x00 },
    { BSP_OV2659_TIMING_VH_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_VH_L, 0xb7, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_H, 0x02, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_L, 0x80, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_H, 0x01, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_L, 0xe0, 0x00 },
    { BSP_OV2659_TIMING_HTS_H, 0x05, 0x00 },
    { BSP_OV2659_TIMING_HTS_L, 0x14, 0x00 },
    { BSP_OV2659_TIMING_VTS_H, 0x02, 0x00 },
    { BSP_OV2659_TIMING_VTS_L, 0x68, 0x00 },
    { BSP_OV2659_TIMING_HOFFS_L, 0x08, 0x00 },
    { BSP_OV2659_TIMING_VOFFS_L, 0x02, 0x00 },
    { BSP_OV2659_TIMING_XINC, 0x31, 0x00 },
    { BSP_OV2659_TIMING_YINC, 0x31, 0x00 },
    { 0x3a02, 0x02, 0x00 },
    { 0x3a03, 0x68, 0x00 },
    { 0x3a08, 0x00, 0x00 },
    { 0x3a09, 0x5c, 0x00 },
    { 0x3a0a, 0x00, 0x00 },
    { 0x3a0b, 0x4d, 0x00 },
    { 0x3a0d, 0x08, 0x00 },
    { 0x3a0e, 0x06, 0x00 },
    { 0x3a14, 0x02, 0x00 },
    { 0x3a15, 0x28, 0x00 },
    { 0x3623, 0x00, 0x00 },
    { 0x3634, 0x76, 0x00 },
    { 0x3701, 0x44, 0x00 },
    { 0x3702, 0x18, 0x00 },
    { 0x3703, 0x24, 0x00 },
    { 0x3704, 0x24, 0x00 },
    { 0x3705, 0x0c, 0x00 },
    { BSP_OV2659_TIMING_VERT_FORMAT, 0x81, 0x00 },
    { BSP_OV2659_TIMING_HORIZ_FORMAT, 0x01, 0x00 },
    { 0x370a, 0x52, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_H, 0x00, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_L, 0xa0, 0x00 },
    { BSP_OV2659_ISP_CTRL02, 0x10, 0x00 },
    { BSP_OV2659_REG_NULL, 0x00, 0x00 }
};

#if 0
/* 320X240 QVGA */
static  Bsp_VidSensorConfigRegs ov2659_qvga[] = {
    { BSP_OV2659_TIMING_HS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_VS_L, 0x00, 0x00 },
    { BSP_OV2659_TIMING_HW_H, 0x06, 0x00 },
    { BSP_OV2659_TIMING_HW_L, 0x5f, 0x00 },
    { BSP_OV2659_TIMING_VH_H, 0x04, 0x00 },
    { BSP_OV2659_TIMING_VH_L, 0xb7, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_H, 0x01, 0x00 },
    { BSP_OV2659_TIMING_DVPHO_L, 0x40, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_H, 0x00, 0x00 },
    { BSP_OV2659_TIMING_DVPVO_L, 0xf0, 0x00 },
    { BSP_OV2659_TIMING_HTS_H, 0x05, 0x00 },
    { BSP_OV2659_TIMING_HTS_L, 0x14, 0x00 },
    { BSP_OV2659_TIMING_VTS_H, 0x02, 0x00 },
    { BSP_OV2659_TIMING_VTS_L, 0x68, 0x00 },
    { BSP_OV2659_TIMING_HOFFS_L, 0x08, 0x00 },
    { BSP_OV2659_TIMING_VOFFS_L, 0x02, 0x00 },
    { BSP_OV2659_TIMING_XINC, 0x31, 0x00 },
    { BSP_OV2659_TIMING_YINC, 0x31, 0x00 },
    { 0x3a02, 0x02, 0x00 },
    { 0x3a03, 0x68, 0x00 },
    { 0x3a08, 0x00, 0x00 },
    { 0x3a09, 0x5c, 0x00 },
    { 0x3a0a, 0x00, 0x00 },
    { 0x3a0b, 0x4d, 0x00 },
    { 0x3a0d, 0x08, 0x00 },
    { 0x3a0e, 0x06, 0x00 },
    { 0x3a14, 0x02, 0x00 },
    { 0x3a15, 0x28, 0x00 },
    { 0x3623, 0x00, 0x00 },
    { 0x3634, 0x76, 0x00 },
    { 0x3701, 0x44, 0x00 },
    { 0x3702, 0x18, 0x00 },
    { 0x3703, 0x24, 0x00 },
    { 0x3704, 0x24, 0x00 },
    { 0x3705, 0x0c, 0x00 },
    { BSP_OV2659_TIMING_VERT_FORMAT, 0x81, 0x00 },
    { BSP_OV2659_TIMING_HORIZ_FORMAT, 0x01, 0x00 },
    { 0x370a, 0x52, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_H, 0x00, 0x00 },
    { BSP_OV2659_VFIFO_READ_START_L, 0xa0, 0x00 },
    { BSP_OV2659_ISP_CTRL02, 0x10, 0x00 },
    { BSP_OV2659_REG_NULL, 0x00, 0x00 }
};
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Get OV2659 chip ID and Manufacturer ID
 */
Int32 Bsp_ov2659GetChipId(Bsp_Ov2659HandleObj            *pObj,
                           const Bsp_VidSensorChipIdParams *pPrm,
                           Bsp_VidSensorChipIdStatus       *pStatus)
{
    Int32  status = FVID2_SOK;
    Bsp_VidSensorCreateParams *pCreateArgs;
    UInt16 regAddr[8];
    UInt16 regValue[8];
    UInt32 numRegs;
    UInt32 idx;

    if ((pStatus == NULL) || (pPrm == NULL))
    {
        status = FVID2_EBADARGS;
    }
    if (status == FVID2_SOK)
    {
        BspUtils_memset(pStatus, 0, sizeof (*pStatus));

        pCreateArgs = &pObj->createPrms;

        if (pPrm->deviceNum >= pCreateArgs->numDevicesAtPort)
        {
            status = FVID2_EBADARGS;
        }
    }
    if (status == FVID2_SOK)
    {
        numRegs = 0;

        regAddr[numRegs]  = BSP_OV2659_SC_CHIP_ID_H;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV2659_SC_CHIP_ID_L;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV2659_SC_SUB_ID;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV2659_SC_SCCB_ID;
        regValue[numRegs] = 0;
        numRegs++;

        status = Bsp_deviceRead16(pCreateArgs->deviceI2cInstId,
                                  pCreateArgs->deviceI2cAddr[0],
                                  regAddr,
                                  regValue,
                                  numRegs);

        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }
    if (status == FVID2_SOK)
    {
        for (idx = 0; idx < numRegs; idx++)
        {
            regValue[idx] = regValue[idx] & 0x00FFU;
        }

        pStatus->chipId          = ((UInt32) regValue[0] << 8) | regValue[1];
        pStatus->chipRevision    = 0;
        pStatus->firmwareVersion = ((UInt32) regValue[2] << 8) | regValue[3];
    }

    return status;
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_ov2659RegWrite(Bsp_Ov2659HandleObj             *pObj,
                          const Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 status = FVID2_SOK;
    Bsp_VidSensorCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue16) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pCreatePrms = &pObj->createPrms;
        status      = Bsp_deviceWrite16_Custom(pCreatePrms->deviceI2cInstId,
                                               pCreatePrms->deviceI2cAddr[0],
                                               pPrm->regAddr,
                                               pPrm->regValue16,
                                               pPrm->numRegs);
    }

    return (status);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_ov2659RegRead(Bsp_Ov2659HandleObj       *pObj,
                         Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 status = FVID2_SOK;
    Bsp_VidSensorCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue16) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pCreatePrms = &pObj->createPrms;

        status      = Bsp_deviceRead16_Custom(pCreatePrms->deviceI2cInstId,
                                              pCreatePrms->deviceI2cAddr[0],
                                              pPrm->regAddr,
                                              pPrm->regValue16,
                                              pPrm->numRegs);
    }

    return (status);
}

Int32 Bsp_ov2659SensorStartStop(const Bsp_Ov2659HandleObj *pObj,
                                 UInt32                      bStartSensor)
{
    Int32  status = FVID2_SOK;
    UInt8  nRegValue[3];
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 numRegs;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }
    if (status == FVID2_SOK)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
        /* MSB of address 0x0100 */
        nRegValue[0] = (UInt8) ((UInt16) ((BSP_OV2659_SOFTWARE_STANDBY) &
                                           0xFFFFU) >> 8);
        /* LSB of address 0x0100 */
        nRegValue[1] = (UInt8) ((BSP_OV2659_SOFTWARE_STANDBY) & 0x00FFU);

        if ((UInt32) TRUE == bStartSensor)
        {
            nRegValue[2] = 0x01U;
        }
        else
        {
            nRegValue[2] = 0x00;
        }
        numRegs = 3U;

        status = Bsp_deviceRawWrite8(nI2cInstId,
                                     nDeviceAddr,
                                     nRegValue,
                                     numRegs);
        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }

    return status;
}

/* Ov2659 Sensor Software reset  */
Int32 Bsp_ov2659SoftwareReset(const Bsp_Ov2659HandleObj *pObj)
{
    Int32  status = FVID2_SOK;
    UInt8  nRegValue[3];
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt16 nRegAddr16;
    UInt16 nRegValue16;
    UInt32 numRegs, delay;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }

    if (status == FVID2_SOK)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
        /* MSB of address 0x0103 */
        nRegValue[0] = (UInt8) ((UInt16) ((BSP_OV2659_SOFTWARE_RESET) &
                                           0xFFFFU) >> 8);
        /* LSB of address 0x0103 */
        nRegValue[1] = (UInt8) ((BSP_OV2659_SOFTWARE_RESET) & 0x00FFU);
        /* Reset value 0x01 */
        nRegValue[2] = 0x01U;
        numRegs      = 3U;
        status       = Bsp_deviceRawWrite8(nI2cInstId,
                                           nDeviceAddr,
                                           nRegValue,
                                           numRegs);
        if (status == FVID2_SOK)
        {
            nRegAddr16 = BSP_OV2659_SOFTWARE_RESET;
            do
            {
                numRegs = 1U;
                status  = Bsp_deviceRead16(nI2cInstId,
                                           nDeviceAddr,
                                           &nRegAddr16,
                                           &nRegValue16,
                                           numRegs);
                if (status != FVID2_SOK)
                {
                    status = FVID2_ETIMEOUT;
                    break;
                }
                delay = 1U;
                BspOsal_sleep(delay);
            } while (nRegValue16 != 0);
        }
        else
        {
            status = FVID2_ETIMEOUT;
        }
    }

    return status;
}

Int32 Bsp_ov2659GetSensorFeatures(const Bsp_Ov2659HandleObj *pObj,
                                   Bsp_VidSensorFeatures      *pSenFeature)
{
    Int32  status = FVID2_SOK;
    UInt16 regAddr[8];
    UInt16 regValue[8];
    UInt32 numRegs;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 idx;

    if ((pObj == NULL) || (pSenFeature == NULL))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }
    if (status == FVID2_SOK)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(pSenFeature, &gBspOv2659SensorFeatures,
                        sizeof (Bsp_VidSensorFeatures));

        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
        numRegs     = 0;

        regAddr[numRegs]  = BSP_OV2659_SC_CHIP_ID_H;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV2659_SC_CHIP_ID_L;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV2659_SC_SUB_ID;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV2659_SC_SCCB_ID;
        regValue[numRegs] = 0;
        numRegs++;

        status = Bsp_deviceRead16(nI2cInstId,
                                  nDeviceAddr,
                                  regAddr,
                                  regValue,
                                  numRegs);

        if (status == FVID2_SOK)
        {
            for (idx = 0; idx < numRegs; idx++)
            {
                regValue[idx] = regValue[idx] & 0x00FFU;
            }

            pSenFeature->chipId = ((UInt32) regValue[0] << 8) |
                                  regValue[1];
            pSenFeature->chipRevision    = 0;
            pSenFeature->firmwareVersion = ((UInt32) regValue[2] << 8) |
                                           regValue[3];

            if ((regValue[0] == BSP_VID_SENSOR_OV2659_PID_MSB) &&
                (regValue[1] == BSP_VID_SENSOR_OV2659_PID_LSB))
            {
                pSenFeature->sensorId = BSP_VID_SENSOR_OV2659;
            }
        }
        else
        {
            status = FVID2_ETIMEOUT;
        }
    }

    return (status);
}

/* Ov2659 Sensor Config  */
Int32 Bsp_ov2659SensorConfig(
    const Bsp_Ov2659HandleObj *pObj,
    Bsp_VidSensorConfigRegs    *sensorConfig,
    UInt32
    numSensorConfigEntries)
{
    Bsp_VidSensorConfigRegs *sensorConfiguration = NULL;
    UInt16 nAddr;
    UInt8  nRegValue[5];
    UInt32 nValue, nMask;
    UInt32 nIndex, nArraySize;
    Int32  status = FVID2_SOK;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 regValue;
    UInt32 numRegs;

    /* Check for sensor configuration to be used */
    if (sensorConfig != NULL)
    {
        /* User provided configuration  */
        sensorConfiguration = (Bsp_VidSensorConfigRegs *) sensorConfig;
        nArraySize          = numSensorConfigEntries;
    }
    else
    {
        if (pObj->nDrvId == FVID2_VID_SENSOR_OV2659_DRV)
        {
            /* Use the default configuration if user has passed NULL */
            sensorConfiguration =
                (Bsp_VidSensorConfigRegs *) gBsp_Ov2659SensorsDefault;

            nArraySize =
                (sizeof (gBsp_Ov2659SensorsDefault) /
                 sizeof (gBsp_Ov2659SensorsDefault[0]));
        }
        else
        {
            status = FVID2_EBADARGS;
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid Driver ID!!\r\n");
        }
    }

    nI2cInstId  = pObj->createPrms.deviceI2cInstId;
    nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];

    if (FVID2_SOK == status)
    {
        for (nIndex = 0; nIndex < nArraySize; nIndex++)
        {
            /* For OV sensor the address is 16-bit long */
            nAddr = sensorConfiguration[nIndex].regAddr & (UInt16) 0xFFFFU;

            /* For OV sensor the value is 8-bit long */
            nValue = ((UInt32) sensorConfiguration[nIndex].regValue &
                      0x00FFU);

            /* For OV sensor the mask is 8-bit long */
            nMask = ((UInt32) sensorConfiguration[nIndex].regMask & 0x00FFU);

            /* MSB of the address */
            nRegValue[0] = (UInt8) ((UInt16) (nAddr & 0xFFFFU) >> 8);
            /* LSB of the address */
            nRegValue[1] = (UInt8) (nAddr & 0x00FFU);
            /* Data */

            if (nMask != 0)
            {
                regValue     = ((nValue & 0xFFU) & nMask);
                nRegValue[2] = (UInt8) (regValue);
            }
            else
            {
                regValue     = (nValue & 0xFFU);
                nRegValue[2] = (UInt8) (regValue);
            }
            numRegs = 3U;

            status  = Bsp_deviceRawWrite8(nI2cInstId,
                                          nDeviceAddr,
                                          nRegValue,
                                          numRegs);
        }
    }

    return (status);
}

Int32 Bsp_ov2659SetFlipParams(const Bsp_Ov2659HandleObj    *pObj,
                               const Bsp_VidSensorFlipParams *pPrm)
{
    UInt8  nRegValue[5];
    Int32  status = FVID2_SOK;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 numRegs;
    UInt16 nAddr, nValue;

    nI2cInstId  = pObj->createPrms.deviceI2cInstId;
    nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
    numRegs     = 3U;

    nAddr  = (UInt16) BSP_OV2659_TIMING_HORIZ_FORMAT;
    nValue = (UInt16) 0x40;
    if (pPrm->hFlip)
    {
        nValue |= (UInt16) 0x3; /* enable H flip in sensor */
    }

    /* MSB of the address */
    nRegValue[0] = (UInt8) ((UInt16) (nAddr & 0xFFFFU) >> 8);
    /* LSB of the address */
    nRegValue[1] = (UInt8) (nAddr & 0x00FFU);
    /* Data */
    nRegValue[2] = (UInt8) (nValue);

    status += Bsp_deviceRawWrite8(nI2cInstId,
                                  nDeviceAddr,
                                  nRegValue,
                                  numRegs);

    nAddr  = (UInt16) BSP_OV2659_TIMING_VERT_FORMAT;
    nValue = 0;
    if (pPrm->vFlip)
    {
        nValue |= (UInt16) (((UInt16) 0x3) << 6); /* enable V flip in sensor */
    }

    /* MSB of the address */
    nRegValue[0] = (UInt8) ((UInt16) (nAddr & 0xFFFFU) >> 8);
    /* LSB of the address */
    nRegValue[1] = (UInt8) (nAddr & 0x00FFU);
    /* Data */
    nRegValue[2] = (UInt8) (nValue);

    status += Bsp_deviceRawWrite8(nI2cInstId,
                                  nDeviceAddr,
                                  nRegValue,
                                  numRegs);

    return status;
}

Int32 Bsp_ov2659SetConfig(Bsp_Ov2659HandleObj            *pObj,
                           const Bsp_VidSensorConfigParams *configParams)
{
    Int32  status = FVID2_SOK;
    UInt32 idx      = 0U;
    UInt32 regCount = 0U;

    UInt32 preDivider  = 1U;
    UInt32 multiplier  = 7U;
    UInt32 sClkDivider = 1U;
    UInt8  ctrl1, ctrl2, ctrl3;
    Bsp_VidSensorConfigRegs sensorConfigReg[50];
    Bsp_VidSensorConfigRegs *sCfgReg;

    if ((pObj == NULL) || (configParams == NULL))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }

    if (status == FVID2_SOK)
    {
        pObj->sensorConfig = *configParams;
    }

    if (status == FVID2_SOK)
    {
        for (idx = 0; idx <
             (sizeof (nRestoPllMapping) / sizeof (nRestoPllMapping[0])); idx++)
        {
            if ((configParams->standard == nRestoPllMapping[idx][0]) &&
                (configParams->fps == nRestoPllMapping[idx][1]))
            {
                preDivider  = nRestoPllMapping[idx][2];
                multiplier  = nRestoPllMapping[idx][3];
                sClkDivider = nRestoPllMapping[idx][4];
                break;
            }
        }

        regCount = 0;

        /* Configure YUV422 output format */
        sensorConfigReg[regCount].regAddr = BSP_OV2659_FORMAT_CTRL00;
        switch (configParams->dataformat)
        {
            case FVID2_DF_YUV422I_YUYV:
                sensorConfigReg[regCount].regValue = 0x30;
                break;
            case FVID2_DF_BAYER_BGGR:
                sensorConfigReg[regCount].regValue = 0x00;
                break;
            case FVID2_DF_YUV422I_UYVY:
                sensorConfigReg[regCount].regValue = 0x32;
                break;
            case FVID2_DF_RGB16_565:
                sensorConfigReg[regCount].regValue = 0x60;
                break;
            default:
                GT_0trace(
                    BspDeviceTrace, GT_ERR,
                    "Unsupported dataformat,using default as YUYV format\r\n");
                sensorConfigReg[regCount].regValue = 0x30;
                break;
        }
        sensorConfigReg[regCount].regMask = 0x00;

        ctrl1 = ctrl2 = ctrl3 = 0x00U;

        switch (preDivider)
        {
            case 4U:
                ctrl3 |= 0x06U;
                break;

            case 2U:
                ctrl3 |= 0x04U;
                break;

            case 3U:
                ctrl3 |= 0x05U;
                break;

            case 1U:
            case 0U:
            default:
                break;
        }

        switch (sClkDivider)
        {
            case 1U:
                ctrl1 |= (UInt8) (sClkDivider << 0x04U);
                break;

            default:
                break;
        }

        ctrl2 = (UInt8) multiplier & 0x3FU;

        /* Configure PLL multipliers and dividers */
        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV2659_SC_PLL_CTRL1;
        sensorConfigReg[regCount].regValue = ctrl1;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV2659_SC_PLL_CTRL2;
        sensorConfigReg[regCount].regValue = ctrl2;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV2659_SC_PLL_CTRL3;
        sensorConfigReg[regCount].regValue = ctrl3;
        sensorConfigReg[regCount].regMask  = 0x0;

        switch (configParams->standard)
        {
           case FVID2_STD_UXGA_60:
             sCfgReg = ov2659_uxga;
             break;

           case FVID2_STD_VGA_60:
             sCfgReg = ov2659_vga;
             break;

           case FVID2_STD_SVGA_60:
             sCfgReg = ov2659_svga;
             break;

           case FVID2_STD_XGA_60:
             sCfgReg = ov2659_xga;
             break;

           case FVID2_STD_SXGA_60:
             sCfgReg = ov2659_sxga;
             break;

           case FVID2_STD_720P_60:
           default:
             sCfgReg = ov2659_720p;
             break;
        }

        do
        {
          regCount++;
          sensorConfigReg[regCount] = *sCfgReg;
          sCfgReg++;
        } while (sCfgReg->regAddr != BSP_OV2659_REG_NULL);

        /* Total number of registers = array index + 1 */
        regCount = regCount + 1U;
        status   = Bsp_ov2659SensorConfig(
            pObj,
            &sensorConfigReg[0],
            regCount);
    }
    return status;
}

