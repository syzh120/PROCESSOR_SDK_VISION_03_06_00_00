/* =============================================================================
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

/*
 * \file vpshalVpdmaDefaultsTda3xx.h
 *
 * \brief VPS VPDMA HAL default configuration file
 * This file contains default configuration for VPDMA.
 *
 */

#ifndef VPSSHALVPDMADEFAULTS_TDA3XX_H_
#define VPSSHALVPDMADEFAULTS_TDA3XX_H_

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

/**
 * Expert value for the anchor and interpolated pixel
 */
#define VPSHAL_VPDMA_DEFAULT_CHANNEL_INFO                                     \
    {                                                                         \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC0,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC1,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC2,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC3,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC4,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC5,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC6,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC7,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC8,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC9,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC10,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC11,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC12,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC13,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC14,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC15,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC0,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC1,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC2,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC3,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC4,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC5,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC6,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC7,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC8,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC9,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC10,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC11,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC12,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC13,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC14,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC15,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC0,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC1,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC2,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC3,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC4,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC5,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC6,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC7,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC8,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC9,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC10,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC11,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC12,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC13,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC14,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC15,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC0,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC1,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC2,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC3,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC4,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC5,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC6,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC7,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC8,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC9,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC10,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC11,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC12,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC13,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC14,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC15,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTA_LUMA,                                  \
         VPDMA_S0_UP_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTA_CHROMA,                                \
         VPDMA_S0_UP_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTB_LUMA,                                  \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTB_CHROMA,                                \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTA_RGB,                                   \
         VPDMA_S0_UP_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTB_RGB,                                   \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC0,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC1,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC2,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC3,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC4,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC5,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC6,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC7,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC8,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC9,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC10,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC11,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC12,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC13,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC14,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC15,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC0,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC1,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC2,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC3,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC4,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC5,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC6,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC7,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC8,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC9,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC10,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC11,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC12,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC13,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC14,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC15,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC0,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC1,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC2,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC3,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC4,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC5,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC6,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC7,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC8,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC9,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC10,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC11,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC12,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC13,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC14,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC15,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC0,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC1,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC2,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC3,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC4,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC5,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC6,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC7,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC8,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC9,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC10,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC11,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC12,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC13,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC14,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC15,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTA_LUMA,                                  \
         VPDMA_S1_UP_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTA_CHROMA,                                \
         VPDMA_S1_UP_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTB_LUMA,                                  \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTB_CHROMA,                                \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTA_RGB,                                   \
         VPDMA_S1_UP_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTB_RGB,                                   \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
    }

#define VPSHAL_VPDMA_DEFAULT_PATH_INFO                          \
    {                                                           \
        {VPSHAL_VPDMA_PATH_VIP0_LO_UV, TRUE, 1920, 4096, 4096}, \
        {VPSHAL_VPDMA_PATH_VIP0_LO_Y, TRUE, 1920, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_VIP0_UP_UV, TRUE, 1920, 4096, 4096}, \
        {VPSHAL_VPDMA_PATH_VIP0_UP_Y, TRUE, 1920, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_VIP1_LO_UV, TRUE, 1920, 4096, 4096}, \
        {VPSHAL_VPDMA_PATH_VIP1_LO_Y, TRUE, 1920, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_VIP1_UP_UV, TRUE, 1920, 4096, 4096}, \
        {VPSHAL_VPDMA_PATH_VIP1_UP_Y, TRUE, 1920, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_VIP0_ANCA, FALSE, 0, 4096, 4096},    \
        {VPSHAL_VPDMA_PATH_VIP0_ANCB, FALSE, 0, 4096, 4096},    \
        {VPSHAL_VPDMA_PATH_VIP1_ANCA, FALSE, 0, 4096, 4096},    \
        {VPSHAL_VPDMA_PATH_VIP1_ANCB, FALSE, 0, 4096, 4096},    \
        {VPSHAL_VPDMA_PATH_SEC0, TRUE, 1920, 1920, 4096},       \
        {VPSHAL_VPDMA_PATH_SEC1, TRUE, 1920, 1920, 4096},       \
        {VPSHAL_VPDMA_PATH_PRI, TRUE, 1920, 1920, 4096},        \
        {VPSHAL_VPDMA_PATH_WB0, FALSE, 0, 4096, 4096},          \
        {VPSHAL_VPDMA_PATH_AUX, TRUE, 1920, 1920, 4096},        \
        {VPSHAL_VPDMA_PATH_WB1, FALSE, 0, 4096, 4096},          \
        {VPSHAL_VPDMA_PATH_BP0, FALSE, 0, 4096, 4096},          \
        {VPSHAL_VPDMA_PATH_BP1, FALSE, 0, 4096, 4096},          \
        {VPSHAL_VPDMA_PATH_WB2, FALSE, 0, 4096, 4096},          \
        {VPSHAL_VPDMA_PATH_GRPX0, FALSE, 0, 4096, 4096},        \
        {VPSHAL_VPDMA_PATH_GRPX0_STENC, FALSE, 0, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_GRPX1, FALSE, 0, 4096, 4096},        \
        {VPSHAL_VPDMA_PATH_GRPX1_STENC, FALSE, 0, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_GRPX2, FALSE, 0, 4096, 4096},        \
        {VPSHAL_VPDMA_PATH_GRPX2_STENC, FALSE, 0, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_VBI_HD, FALSE, 0, 4096, 4096},       \
        {VPSHAL_VPDMA_PATH_VBI_SD, FALSE, 0, 4096, 4096},       \
        {VPSHAL_VPDMA_PATH_NF, TRUE, 1920, 4096, 4096}          \
    }

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None*/

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSSHALVPDMADEFAULTS_TDA3XX_H_ */
