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
 *  \file bspdrv_ov2659_Reg.c
 *
 *  \brief OV2659 sensor Register file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ov2659/src/bspdrv_ov2659Priv.h>

/* Ov2659 recommended setting */
Bsp_VidSensorConfigRegs gBsp_Ov2659SensorsDefault[BSP_OV2659_NUM_REGS] =
{
    { BSP_OV2659_SOFTWARE_RESET, 0x1, 0x0},    /** Software Reset */
    { BSP_OV2659_IO_CTRL00, 0x03, 0x00 },
    { BSP_OV2659_IO_CTRL01, 0xff, 0x00 },
    { BSP_OV2659_IO_CTRL02, 0xe0, 0x00 },
    { 0x3633, 0x3d, 0x00 },
    { 0x3620, 0x02, 0x00 },
    { 0x3631, 0x11, 0x00 },
    { 0x3612, 0x04, 0x00 },
    { 0x3630, 0x20, 0x00 },
    { 0x4702, 0x02, 0x00 },
    { 0x370c, 0x34, 0x00 },
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
    { BSP_OV2659_DVP_CTRL02, 0x01, 0x00 },
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
    { BSP_OV2659_FORMAT_CTRL00, 0x32, 0x00 },
    { 0x5086, 0x02, 0x00 },
    { BSP_OV2659_ISP_CTRL00, 0xfb, 0x00 },
    { BSP_OV2659_ISP_CTRL01, 0x1f, 0x00 },
    { BSP_OV2659_ISP_CTRL02, 0x00, 0x00 },
    { 0x5025, 0x0e, 0x00 },
    { 0x5026, 0x18, 0x00 },
    { 0x5027, 0x34, 0x00 },
    { 0x5028, 0x4c, 0x00 },
    { 0x5029, 0x62, 0x00 },
    { 0x502a, 0x74, 0x00 },
    { 0x502b, 0x85, 0x00 },
    { 0x502c, 0x92, 0x00 },
    { 0x502d, 0x9e, 0x00 },
    { 0x502e, 0xb2, 0x00 },
    { 0x502f, 0xc0, 0x00 },
    { 0x5030, 0xcc, 0x00 },
    { 0x5031, 0xe0, 0x00 },
    { 0x5032, 0xee, 0x00 },
    { 0x5033, 0xf6, 0x00 },
    { 0x5034, 0x11, 0x00 },
    { 0x5070, 0x1c, 0x00 },
    { 0x5071, 0x5b, 0x00 },
    { 0x5072, 0x05, 0x00 },
    { 0x5073, 0x20, 0x00 },
    { 0x5074, 0x94, 0x00 },
    { 0x5075, 0xb4, 0x00 },
    { 0x5076, 0xb4, 0x00 },
    { 0x5077, 0xaf, 0x00 },
    { 0x5078, 0x05, 0x00 },
    { BSP_OV2659_CMX_SIGN, 0x98, 0x00 },
    { BSP_OV2659_CMX_MISC_CTRL, 0x21, 0x00 },
    { BSP_OV2659_AWB_CTRL00, 0x6a, 0x00 },
    { BSP_OV2659_AWB_CTRL01, 0x11, 0x00 },
    { BSP_OV2659_AWB_CTRL02, 0x92, 0x00 },
    { BSP_OV2659_AWB_CTRL03, 0x21, 0x00 },
    { BSP_OV2659_AWB_CTRL04, 0xe1, 0x00 },
    { BSP_OV2659_AWB_LOCAL_LIMIT, 0x01, 0x00 },
    { 0x503c, 0x05, 0x00 },
    { 0x503d, 0x08, 0x00 },
    { 0x503e, 0x08, 0x00 },
    { 0x503f, 0x64, 0x00 },
    { 0x5040, 0x58, 0x00 },
    { 0x5041, 0x2a, 0x00 },
    { 0x5042, 0xc5, 0x00 },
    { 0x5043, 0x2e, 0x00 },
    { 0x5044, 0x3a, 0x00 },
    { 0x5045, 0x3c, 0x00 },
    { 0x5046, 0x44, 0x00 },
    { 0x5047, 0xf8, 0x00 },
    { 0x5048, 0x08, 0x00 },
    { BSP_OV2659_AWB_CTRL12, 0x70, 0x00 },
    { BSP_OV2659_AWB_CTRL13, 0xf0, 0x00 },
    { BSP_OV2659_AWB_CTRL14, 0xf0, 0x00 },
    { BSP_OV2659_LENC_RED_X0_H, 0x03, 0x00 },
    { BSP_OV2659_LENC_RED_X0_L, 0x20, 0x00 },
    { BSP_OV2659_LENC_RED_Y0_H, 0x02, 0x00 },
    { BSP_OV2659_LENC_RED_Y0_L, 0x5c, 0x00 },
    { BSP_OV2659_LENC_RED_A1, 0x48, 0x00 },
    { BSP_OV2659_LENC_RED_B1, 0x00, 0x00 },
    { BSP_OV2659_LENC_RED_A2_B2, 0x66, 0x00 },
    { BSP_OV2659_LENC_GREEN_X0_H, 0x03, 0x00 },
    { BSP_OV2659_LENC_GREEN_X0_L, 0x30, 0x00 },
    { BSP_OV2659_LENC_GREEN_Y0_H, 0x02, 0x00 },
    { BSP_OV2659_LENC_GREEN_Y0_L, 0x7c, 0x00 },
    { BSP_OV2659_LENC_GREEN_A1, 0x40, 0x00 },
    { BSP_OV2659_LENC_GREEN_B1, 0x00, 0x00 },
    { BSP_OV2659_LENC_GREEN_A2_B2, 0x66, 0x00 },
    { BSP_OV2659_LENC_BLUE_X0_H, 0x03, 0x00 },
    { BSP_OV2659_LENC_BLUE_X0_L, 0x10, 0x00 },
    { BSP_OV2659_LENC_BLUE_Y0_H, 0x02, 0x00 },
    { BSP_OV2659_LENC_BLUE_Y0_L, 0x7c, 0x00 },
    { BSP_OV2659_LENC_BLUE_A1, 0x3a, 0x00 },
    { BSP_OV2659_LENC_BLUE_B1, 0x00, 0x00 },
    { BSP_OV2659_LENC_BLUE_A2_B2, 0x66, 0x00 },
    { BSP_OV2659_CIP_CTRL00, 0x44, 0x00 },
    { BSP_OV2659_SHARPENMT_THRESH1, 0x08, 0x00 },
    { BSP_OV2659_SHARPENMT_THRESH2, 0x10, 0x00 },
    { BSP_OV2659_SHARPENMT_OFFSET1, 0x12, 0x00 },
    { BSP_OV2659_SHARPENMT_OFFSET2, 0x02, 0x00 },
    { BSP_OV2659_SHARPEN_THRESH1, 0x08, 0x00 },
    { BSP_OV2659_SHARPEN_THRESH2, 0x10, 0x00 },
    { BSP_OV2659_CIP_CTRL01, 0xa6, 0x00 },
    { BSP_OV2659_DENOISE_THRESH1, 0x08, 0x00 },
    { BSP_OV2659_DENOISE_THRESH2, 0x10, 0x00 },
    { BSP_OV2659_DENOISE_OFFSET1, 0x04, 0x00 },
    { BSP_OV2659_DENOISE_OFFSET2, 0x12, 0x00 },
    { 0x507e, 0x40, 0x00 },
    { 0x507f, 0x20, 0x00 },
    { 0x507b, 0x02, 0x00 },
    { BSP_OV2659_CMX_MISC_CTRL, 0x01, 0x00 },
    { 0x5084, 0x0c, 0x00 },
    { 0x5085, 0x3e, 0x00 },
    { 0x5005, 0x80, 0x00 },
    { 0x3a0f, 0x30, 0x00 },
    { 0x3a10, 0x28, 0x00 },
    { 0x3a1b, 0x32, 0x00 },
    { 0x3a1e, 0x26, 0x00 },
    { 0x3a11, 0x60, 0x00 },
    { 0x3a1f, 0x14, 0x00 },
    { 0x5060, 0x69, 0x00 },
    { 0x5061, 0x7d, 0x00 },
    { 0x5062, 0x7d, 0x00 },
    { 0x5063, 0x69, 0x00 },
};

