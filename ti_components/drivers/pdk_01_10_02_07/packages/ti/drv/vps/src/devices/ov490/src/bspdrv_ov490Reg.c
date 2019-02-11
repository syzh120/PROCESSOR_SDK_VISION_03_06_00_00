/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file bspdrv_ov490_Reg.c
 *
 *  \brief OV490 sensor Register file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ov490/src/bspdrv_ov490Priv.h>

#ifdef __cplusplus
extern "C" {
#endif

Bsp_VidSensorConfigRegs gBsp_Ov490SensorsDefault[] =
{
    { BSP_OV490_BANK_HIGH, 0x80, 0x00 },
    { BSP_OV490_BANK_LOW,  0x19, 0x00 },
    { 0x5000, 0x01, 0x00 },
    { 0x5001, 0x01, 0x00 },
    { 0x5002, 0x05, 0x00 },
    { 0x5003, 0x08, 0x00 },
    { 0x5004, 0x04, 0x00 },
    { 0x5005, 0x40, 0x00 },
    { 0x5006, 0x05, 0x00 },
    { 0x5007, 0x08, 0x00 },
    { 0x5008, 0x04, 0x00 },
    { 0x5009, 0x40, 0x00 },
    { 0x500A, 0x00, 0x00 },
    { 0x5000, 0x31, 0x00 },

    { BSP_OV490_BANK_LOW,  0x80, 0x00 },
    { 0x00C0, 0x39, 0x00 },
    { 0x00C0, 0xE2, 0x00 },

    { BSP_OV490_BANK_LOW,  0x82, 0x00 },
    { 0x000A, 0x92, 0x00 },
};

Bsp_VidSensorConfigRegs gBsp_Ov490UYVY[] =
{
    { BSP_OV490_BANK_HIGH, (BSP_OV490_IMAGE_CONTROL_REGISTER >> 24U) & 0xFFU, 0x00 },
    { BSP_OV490_BANK_LOW,  (BSP_OV490_IMAGE_CONTROL_REGISTER >> 16U) & 0xFFU, 0x00 },
    { BSP_OV490_IMAGE_CONTROL_REGISTER & 0xFFFFU, 0x01, 0x00 },
};

Bsp_VidSensorConfigRegs gBsp_Ov490YUYV[] =
{
    { BSP_OV490_BANK_HIGH, (BSP_OV490_IMAGE_CONTROL_REGISTER >> 24U) & 0xFFU, 0x00 },
    { BSP_OV490_BANK_LOW,  (BSP_OV490_IMAGE_CONTROL_REGISTER >> 16U) & 0xFFU, 0x00 },
    { BSP_OV490_IMAGE_CONTROL_REGISTER & 0xFFFFU, 0x11, 0x00 },
};

#ifdef __cplusplus
}
#endif
