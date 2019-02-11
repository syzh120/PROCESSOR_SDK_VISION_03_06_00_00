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
 *  \file bspdrv_ar0140_tida00262_1280x800_30fps_wdr.h
 *
 *  \brief TIDA00262 has a restriction on the pixel clock. This configuration
 *          ensures the pixel clock is as required. Other WDR configurations
 *          are common.
 *
 */

#ifndef BSPDRV_AR0140_TIDA00262_1280x800_30FPS_WDR_H_
#define BSPDRV_AR0140_TIDA00262_1280x800_30FPS_WDR_H_

#define BSP_AR0140_1650X1450_SENSORS \
{ \
    {0x301A, 0x10D8, 0xff},     /* RESET_REGISTER       */ \
    {BSP_VID_SENSOR_DLY_REG, BSP_AR0140_SENSOR_DLY_IN_MS_AFTER_RESET, \
        BSP_VID_SENSOR_DLY_REG_MASK}, /* Dummy register to pu Delay */ \
    /* PLL_configuration_Parallel */ \
    {0x302A, 0x0005, 0x00},     /* VT_PIX_CLK_DIV       */ \
    {0x302C, 0x0001, 0x00},     /* VT_SYS_CLK_DIV       */ \
    {0x302E, 0x0004, 0x00},     /* PRE_PLL_CLK_DIV      */ \
    {0x3030, 0x003C, 0x00},     /* PLL_MULTIPLIER       */ \
    {0x3036, 0x000C, 0x00},     /* OP_PIX_CLK_DIV       */ \
    {0x3038, 0x0001, 0x00},     /* OP_SYS_CLK_DIV       */ \
 \
    /* 1280x800 30fps_configuration */ \
    {0x3004, 0x0020, 0x00},     /* X_ADDR_START             */ \
    {0x3002, 0x0018, 0x00},     /* Y_ADDR_START             */ \
    {0x3008, 0x051F, 0x00},     /* X_ADDR_END               */ \
    {0x3006, 0x0337, 0x00},     /* Y_ADDR_END               */ \
    {0x300A, 0x05AA, 0x00},     /* FRAME_LENGTH_LINES       */ \
    {0x300C, 0x0672, 0x00},     /* LINE_LENGTH_PCK          */ \
    {0x3012, 0x0200, 0x00},     /* COARSE_INTEGRATION_TIME  */ \
}

#endif /* #ifndef BSPDRV_AR0140_TIDA00262_1280x800_30FPS_WDR_H_  */

