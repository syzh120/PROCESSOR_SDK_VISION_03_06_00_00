/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *  \file imx224_dol_1312x2164_config.h
 *
 *  \brief imx224 sensor register file for dol mode
 *
 */

#ifndef IMX224_DOL_1312X2164_CONFIG_H_
#define IMX224_DOL_1312X2164_CONFIG_H_

/* imx224 recommended setting */
#define IMX224_DOL_1312X2164_CONFIG                                            \
{                                                                              \
    {0x3000,0x1, 0x0},                                                         \
    {0x3001,0x0, 0x0},                                                         \
    {0x3002,0x0, 0x0},                                                         \
    {0x3003,0x0, 0x0},                                                         \
    {0x3004,0x10, 0x0},                                                        \
    {0x3005,0x1, 0x0},                                                         \
    {0x3006,0x0, 0x0},                                                         \
    {0x3007,0x3, 0x0},  /* [0:1] V/H reverse [4:7] Winmode , 0x0}, */          \
    {0x3008,0x0, 0x0},                                                         \
    {0x3009,0x11, 0x0},  /* [0:1] FRSEL changed [4] FDG_SEL, 0x0}, */          \
    {0x300a,0xf0, 0x0},                                                        \
    {0x300b,0x0, 0x0},                                                         \
    {0x300c,0x11, 0x0},/* WDSEL WDmode changed, 0x0}, */                       \
    {0x300d,0x0, 0x0},                                                         \
    {0x300e,0x1, 0x0},                                                         \
    {0x300f,0x0, 0x0},                                                         \
    {0x3010,0x1, 0x0},                                                         \
    {0x3011,0x0, 0x0},                                                         \
    {0x3012,0x2c, 0x0},                                                        \
    {0x3013,0x1, 0x0},                                                         \
    {0x3014,0x0, 0x0},                                                         \
    {0x3015,0x0, 0x0},                                                         \
    {0x3016,0x9, 0x0},                                                         \
    {0x3017,0x0, 0x0},                                                         \
    {0x3018,0x44c&0xFFU, 0x0},  /* VMAX  , 0x0}, */                            \
    {0x3019,0x44c>>8U, 0x0}, /* VMAX , 0x0}, */                                \
    {0x301a,0x0, 0x0},                                                         \
    {0x301b,0xCA, 0x0},  /* HMAX changed, 0x0}, */                             \
    {0x301c,0x08, 0x0},  /* HMAX changed, 0x0}, */                             \
    {0x301d,0xc2, 0x0},                                                        \
    {0x301e,0x1, 0x0},                                                         \
    {0x301f,0x0, 0x0},                                                         \
    {0x3020,0x65, 0x0},  /* SHS1, 0x0}, 64X */                                 \
    {0x3021,0x0, 0x0},  /* SHS1, 0x0}, */                                      \
    {0x3022,0x0, 0x0},  /* SHS1, 0x0}, */                                      \
    {0x3023,0x97, 0x0},  /* SHS2, 0x0}, */                                     \
    {0x3024,0x0, 0x0},  /* SHS2, 0x0}, */                                      \
    {0x3025,0x0, 0x0},  /* SHS2, 0x0}, */                                      \
    {0x3026,0x0, 0x0},                                                         \
    {0x3027,0x0, 0x0},                                                         \
    {0x3028,0x0, 0x0},                                                         \
    {0x3029,0x0, 0x0},                                                         \
    {0x302a,0x0, 0x0},                                                         \
    {0x302b,0x0, 0x0},                                                         \
    {0x302c,0x85U&0xFFU, 0x0},  /* RHS1, 0x0}, */                              \
    {0x302d,0x85U>>8U, 0x0},  /* RHS1, 0x0}, */                                \
    {0x302e,0x0, 0x0},  /* RHS1, 0x0}, */                                      \
    {0x302f,0x0, 0x0},                                                         \
    {0x3030,0x0, 0x0},                                                         \
    {0x3031,0x0, 0x0},                                                         \
    {0x3032,0x0, 0x0},                                                         \
    {0x3033,0x0, 0x0},                                                         \
    {0x3034,0x0, 0x0},                                                         \
    {0x3035,0x0, 0x0},                                                         \
    {0x3036,0x10, 0x0},  /* winwv_ob, 0x0}, */                                 \
    {0x3037,0x0, 0x0},                                                         \
    {0x3038,0x0, 0x0},  /* Winpv, 0x0}, */                                     \
    {0x3039,0x0, 0x0},                                                         \
    {0x303a,0xd1, 0x0},  /* winwv, 0x0}, */                                    \
    {0x303b,0x3, 0x0},                                                         \
    {0x303c,0x0, 0x0},  /* winph, 0x0}, */                                     \
    {0x303d,0x0, 0x0},                                                         \
    {0x303e,0x1c, 0x0},  /* winwh, 0x0}, */                                    \
    {0x303f,0x5, 0x0},                                                         \
    {0x3040,0x1, 0x0},                                                         \
    {0x3041,0x0, 0x0},                                                         \
    {0x3042,0x1, 0x0},                                                         \
    {0x3043,0x1, 0x0},  /* 05h , 0x0}, */                                      \
    {0x3044,0x1, 0x0},  /* [1]odbit [4:7]oprtsel, 0x0}, */                     \
    {0x3045,0x1, 0x0},                                                         \
    {0x3046,0x0, 0x0},                                                         \
    {0x3047,0x8, 0x0},                                                         \
    {0x3048,0x0, 0x0},                                                         \
    {0x3049,0xa, 0x0},                                                         \
    {0x304a,0x0, 0x0},                                                         \
    {0x304b,0x0, 0x0},                                                         \
    {0x304c,0x0, 0x0},                                                         \
    {0x304d,0x0, 0x0},                                                         \
    {0x304e,0x0, 0x0},                                                         \
    {0x304f,0x0, 0x0},                                                         \
    {0x3050,0x26, 0x0},                                                        \
    {0x3051,0x0, 0x0},                                                         \
    {0x3052,0x1, 0x0},                                                         \
    {0x3053,0x0, 0x0},                                                         \
    {0x3054,0x66, 0x0},                                                        \
    {0x3055,0x0, 0x0},                                                         \
    {0x3056,0x13, 0x0},                                                        \
    {0x3057,0x15, 0x0},                                                        \
    {0x3058,0x5, 0x0},                                                         \
    {0x3059,0x0, 0x0},                                                         \
    {0x305a,0x0, 0x0},                                                         \
    {0x305b,0x0, 0x0},                                                         \
    {0x305c,0x2c, 0x0},  /* incksel1 20h, 0x0}, */                             \
    {0x305d,0x0, 0x0}, /* incksel2 00h, 0x0}, */                               \
    {0x305e,0x2c, 0x0},  /* incksel3 20h, 0x0}, */                             \
    {0x305f,0x0, 0x0}, /* incksel4 00h, 0x0}, */                               \
    {0x3060,0x0, 0x0},                                                         \
    {0x3061,0x4a, 0x0},                                                        \
    {0x3062,0x41, 0x0},                                                        \
    {0x3063,0xb0, 0x0},                                                        \
    {0x3064,0x0, 0x0},                                                         \
    {0x3065,0x2, 0x0},                                                         \
    {0x3066,0x0, 0x0},                                                         \
    {0x3067,0x1, 0x0},                                                         \
    {0x3068,0x0, 0x0},                                                         \
    {0x3069,0xc, 0x0},                                                         \
    {0x306a,0x19, 0x0},                                                        \
    {0x306b,0x0, 0x0},                                                         \
    {0x306c,0x0, 0x0},                                                         \
    {0x306d,0x64, 0x0},                                                        \
    {0x306e,0x0, 0x0},                                                         \
    {0x306f,0x0, 0x0},                                                         \
    {0x3070,0x2, 0x0},                                                         \
    {0x3071,0x1, 0x0},                                                         \
    {0x3072,0x0, 0x0},                                                         \
    {0x3073,0x0, 0x0},                                                         \
    {0x3074,0x0, 0x0},                                                         \
    {0x3075,0x0, 0x0},                                                         \
    {0x3076,0x0, 0x0},                                                         \
    {0x3077,0x0, 0x0},                                                         \
    {0x3078,0x0, 0x0},                                                         \
    {0x3079,0x0, 0x0},                                                         \
    {0x307a,0x0, 0x0},                                                         \
    {0x307b,0x0, 0x0},                                                         \
    {0x307c,0x0, 0x0},                                                         \
    {0x307d,0x0, 0x0},                                                         \
    {0x307e,0x0, 0x0},                                                         \
    {0x307f,0x0, 0x0},                                                         \
    {0x3080,0x0, 0x0},                                                         \
    {0x3081,0x0, 0x0},                                                         \
    {0x3082,0x0, 0x0},                                                         \
    {0x3083,0x0, 0x0},                                                         \
    {0x3084,0x0, 0x0},                                                         \
    {0x3085,0x0, 0x0},                                                         \
    {0x3086,0x0, 0x0},                                                         \
    {0x3087,0x0, 0x0},                                                         \
    {0x3088,0x0, 0x0},                                                         \
    {0x3089,0xff, 0x0},                                                        \
    {0x308a,0x0, 0x0},                                                         \
    {0x308b,0x0, 0x0},                                                         \
    {0x308c,0x2, 0x0},                                                         \
    {0x308d,0x0, 0x0},                                                         \
    {0x308e,0x0, 0x0},                                                         \
    {0x308f,0x0, 0x0},                                                         \
    {0x3090,0x0, 0x0},                                                         \
    {0x3091,0x0, 0x0},                                                         \
    {0x3092,0x0, 0x0},                                                         \
    {0x3093,0x1, 0x0},                                                         \
    {0x3094,0x1, 0x0},                                                         \
    {0x3095,0x1, 0x0},                                                         \
    {0x3096,0x0, 0x0},                                                         \
    {0x3097,0x0, 0x0},                                                         \
    {0x3098,0x0, 0x0},                                                         \
    {0x3099,0x0, 0x0},                                                         \
    {0x309a,0x0, 0x0},                                                         \
    {0x309b,0x0, 0x0},                                                         \
    {0x309c,0x0, 0x0},                                                         \
    {0x309d,0x7d, 0x0},                                                        \
    {0x309e,0x22, 0x0},                                                        \
    {0x309f,0x0, 0x0},                                                         \
    {0x30a0,0x0, 0x0},                                                         \
    {0x30a1,0x4, 0x0},                                                         \
    {0x30a2,0x5a, 0x0},                                                        \
    {0x30a3,0x5a, 0x0},                                                        \
    {0x30a4,0x2a, 0x0},                                                        \
    {0x30a5,0xfb, 0x0},                                                        \
    {0x30a6,0x2, 0x0},                                                         \
    {0x30a7,0x22, 0x0},                                                        \
    {0x30a8,0x0, 0x0},                                                         \
    {0x30a9,0x0, 0x0},                                                         \
    {0x30aa,0x0, 0x0},                                                         \
    {0x30ab,0x10, 0x0},                                                        \
    {0x30ac,0x0, 0x0},                                                         \
    {0x30ad,0x10, 0x0},                                                        \
    {0x30ae,0x0, 0x0},                                                         \
    {0x30af,0x10, 0x0},                                                        \
    {0x30b0,0x0, 0x0},                                                         \
    {0x30b1,0x10, 0x0},                                                        \
    {0x30b2,0x0, 0x0},                                                         \
    {0x30b3,0xff, 0x0},                                                        \
    {0x30b4,0x1, 0x0},                                                         \
    {0x30b5,0x42, 0x0},                                                        \
    {0x30b6,0x0, 0x0},                                                         \
    {0x30b7,0x60, 0x0},                                                        \
    {0x30b8,0x10, 0x0},                                                        \
    {0x30b9,0x12, 0x0},                                                        \
    {0x30ba,0xf, 0x0},                                                         \
    {0x30bb,0x0, 0x0},                                                         \
    {0x30bc,0x0, 0x0},                                                         \
    {0x30bd,0x0, 0x0},                                                         \
    {0x30be,0x0, 0x0},                                                         \
    {0x30bf,0x10, 0x0},                                                        \
    {0x30c0,0x0, 0x0},                                                         \
    {0x30c1,0x0, 0x0},                                                         \
    {0x30c2,0x1, 0x0},                                                         \
    {0x30c3,0x4, 0x0},                                                         \
    {0x30c4,0x12, 0x0},                                                        \
    {0x30c5,0x10, 0x0},                                                        \
    {0x30c6,0x0, 0x0},                                                         \
    {0x30c7,0x0, 0x0},                                                         \
    {0x30c8,0x0, 0x0},                                                         \
    {0x30c9,0xff, 0x0},                                                        \
    {0x30ca,0x3, 0x0},                                                         \
    {0x30cb,0xd8, 0x0},                                                        \
    {0x30cc,0x7d, 0x0},                                                        \
    {0x30cd,0x0, 0x0},                                                         \
    {0x30ce,0xfb, 0x0},                                                        \
    {0x30cf,0xb, 0x0},                                                         \
    {0x30d0,0x1, 0x0},                                                         \
    {0x30d1,0xf0, 0x0},                                                        \
    {0x30d2,0x0, 0x0},                                                         \
    {0x30d3,0xb, 0x0},                                                         \
    {0x30d4,0xf0, 0x0},                                                        \
    {0x30d5,0x0, 0x0},                                                         \
    {0x30d6,0xb, 0x0},                                                         \
    {0x30d7,0xf0, 0x0},                                                        \
    {0x30d8,0x0, 0x0},                                                         \
    {0x30d9,0x13, 0x0},                                                        \
    {0x30da,0x70, 0x0},                                                        \
    {0x30db,0x1, 0x0},                                                         \
    {0x30dc,0x13, 0x0},                                                        \
    {0x30dd,0x70, 0x0},                                                        \
    {0x30de,0x1, 0x0},                                                         \
    {0x30df,0x0, 0x0},                                                         \
    {0x30e0,0x0, 0x0},                                                         \
    {0x30e1,0xff, 0x0},                                                        \
    {0x30e2,0xff, 0x0},                                                        \
    {0x30e3,0xff, 0x0},                                                        \
    {0x30e4,0xff, 0x0},                                                        \
    {0x30e5,0xff, 0x0},                                                        \
    {0x30e6,0xff, 0x0},                                                        \
    {0x30e7,0x0, 0x0},                                                         \
    {0x30e8,0x0, 0x0},                                                         \
    {0x30e9,0x0, 0x0},                                                         \
    {0x30ea,0x0, 0x0},                                                         \
    {0x30eb,0x1, 0x0},                                                         \
    {0x30ec,0x2, 0x0},                                                         \
    {0x30ed,0x43, 0x0},                                                        \
    {0x30ee,0x44, 0x0},                                                        \
    {0x30ef,0x0, 0x0},                                                         \
    {0x30f0,0xf0, 0x0},                                                        \
    {0x30f1,0x0, 0x0},                                                         \
    {0x30f2,0x0, 0x0},                                                         \
    {0x30f3,0x0, 0x0},                                                         \
    {0x30f4,0xf0, 0x0},                                                        \
    {0x30f5,0x0, 0x0},                                                         \
    {0x30f6,0x0, 0x0},                                                         \
    {0x30f7,0x0, 0x0},                                                         \
    {0x30f8,0xf0, 0x0},                                                        \
    {0x30f9,0x0, 0x0},                                                         \
    {0x30fa,0x0, 0x0},                                                         \
    {0x30fb,0x0, 0x0},                                                         \
    {0x30fc,0x0, 0x0},                                                         \
    {0x30fd,0x0, 0x0},                                                         \
    {0x30fe,0x0, 0x0},                                                         \
    {0x3100,0x0, 0x0},                                                         \
    {0x3101,0x0, 0x0},                                                         \
    {0x3102,0x80, 0x0},                                                        \
    {0x3103,0x0, 0x0},                                                         \
    {0x3104,0x0, 0x0},                                                         \
    {0x3105,0x0, 0x0},                                                         \
    {0x3106,0x0, 0x0},                                                         \
    {0x3107,0x0, 0x0},                                                         \
    {0x3108,0x11, 0x0},                                                        \
    {0x3109,0x1, 0x0},                                                         \
    {0x310a,0x0, 0x0},                                                         \
    {0x310b,0x4, 0x0},                                                         \
    {0x310c,0x0, 0x0},                                                         \
    {0x310d,0x0, 0x0},                                                         \
    {0x310e,0x1, 0x0},                                                         \
    {0x310f,0xf, 0x0},                                                         \
    {0x3110,0xe, 0x0},                                                         \
    {0x3111,0xe7, 0x0},                                                        \
    {0x3112,0x9c, 0x0},                                                        \
    {0x3113,0x83, 0x0},                                                        \
    {0x3114,0x10, 0x0},                                                        \
    {0x3115,0x42, 0x0},                                                        \
    {0x3116,0xbf, 0x0},                                                        \
    {0x3117,0x3, 0x0},                                                         \
    {0x3118,0x44, 0x0},                                                        \
    {0x3119,0x44, 0x0},                                                        \
    {0x311a,0x0, 0x0},                                                         \
    {0x311b,0x6, 0x0},                                                         \
    {0x311c,0x88, 0x0},                                                        \
    {0x311d,0xe, 0x0},                                                         \
    {0x311e,0x2, 0x0},                                                         \
    {0x311f,0x4, 0x0},                                                         \
    {0x3120,0x12, 0x0},                                                        \
    {0x3121,0x0, 0x0},                                                         \
    {0x3122,0x0, 0x0},                                                         \
    {0x3123,0x0, 0x0},                                                         \
    {0x3124,0x0, 0x0},                                                         \
    {0x3125,0x44, 0x0},                                                        \
    {0x3126,0x44, 0x0},                                                        \
    {0x3127,0x0, 0x0},                                                         \
    {0x3128,0x1e, 0x0},                                                        \
    {0x3129,0x1a, 0x0},                                                        \
    {0x312a,0x0, 0x0},                                                         \
    {0x312b,0x8, 0x0},                                                         \
    {0x312c,0x0, 0x0},                                                         \
    {0x312d,0x0, 0x0},                                                         \
    {0x312e,0x0, 0x0},                                                         \
    {0x312f,0x0, 0x0},                                                         \
    {0x3130,0x0, 0x0},                                                         \
    {0x3131,0x0, 0x0},                                                         \
    {0x3132,0x30, 0x0},                                                        \
    {0x3133,0x0, 0x0},                                                         \
    {0x3134,0x0, 0x0},                                                         \
    {0x3135,0x0, 0x0},                                                         \
    {0x3136,0x0, 0x0},                                                         \
    {0x3137,0x0, 0x0},                                                         \
    {0x3138,0x8, 0x0},                                                         \
    {0x3139,0x0, 0x0},                                                         \
    {0x313a,0x60, 0x0},                                                        \
    {0x313b,0x3, 0x0},                                                         \
    {0x313c,0x8, 0x0},                                                         \
    {0x313d,0x0, 0x0},                                                         \
    {0x313e,0x0, 0x0},                                                         \
    {0x313f,0x0, 0x0},                                                         \
    {0x3140,0x2, 0x0},                                                         \
    {0x3141,0x87, 0x0},                                                        \
    {0x3142,0x0, 0x0},                                                         \
    {0x3143,0x0, 0x0},                                                         \
    {0x3144,0x7, 0x0},                                                         \
    {0x3145,0xff, 0x0},                                                        \
    {0x3146,0x1f, 0x0},                                                        \
    {0x3147,0x0, 0x0},                                                         \
    {0x3148,0xff, 0x0},                                                        \
    {0x3149,0x1f, 0x0},                                                        \
    {0x314a,0x0, 0x0},                                                         \
    {0x314b,0x0, 0x0},                                                         \
    {0x314c,0x0, 0x0},                                                         \
    {0x314d,0x2, 0x0},                                                         \
    {0x314e,0x87, 0x0},                                                        \
    {0x314f,0x0, 0x0},                                                         \
    {0x3150,0x0, 0x0},                                                         \
    {0x3151,0x0, 0x0},                                                         \
    {0x3152,0x7, 0x0},                                                         \
    {0x3153,0x40, 0x0},                                                        \
    {0x3154,0x0, 0x0},                                                         \
    {0x3155,0x0, 0x0},                                                         \
    {0x3156,0x0, 0x0},                                                         \
    {0x3157,0x0, 0x0},                                                         \
    {0x3158,0x0, 0x0},                                                         \
    {0x3159,0x0, 0x0},                                                         \
    {0x315a,0x0, 0x0},                                                         \
    {0x315b,0x0, 0x0},                                                         \
    {0x315c,0x0, 0x0},                                                         \
    {0x315d,0x0, 0x0},                                                         \
    {0x315e,0x12, 0x0},                                                        \
    {0x315f,0x80, 0x0},                                                        \
    {0x3160,0x0, 0x0},                                                         \
    {0x3161,0x70, 0x0},                                                        \
    {0x3162,0x7, 0x0},                                                         \
    {0x3163,0x0, 0x0},                                                         \
    {0x3164,0x12, 0x0},                                                        \
    {0x3165,0x80, 0x0},                                                        \
    {0x3166,0x0, 0x0},                                                         \
    {0x3167,0x2, 0x0},                                                         \
    {0x3168,0x0, 0x0},                                                         \
    {0x3169,0x0, 0x0},                                                         \
    {0x316a,0x10, 0x0},                                                        \
    {0x316b,0x4, 0x0},                                                         \
    {0x316c,0x0, 0x0},                                                         \
    {0x316d,0x0, 0x0},                                                         \
    {0x316e,0x0, 0x0},                                                         \
    {0x316f,0xff, 0x0},                                                        \
    {0x3170,0x1, 0x0},                                                         \
    {0x3171,0x2, 0x0},                                                         \
    {0x3172,0x0, 0x0},                                                         \
    {0x3173,0x0, 0x0},                                                         \
    {0x3174,0x5, 0x0},                                                         \
    {0x3175,0x0, 0x0},                                                         \
    {0x3176,0x0, 0x0},                                                         \
    {0x3177,0x0, 0x0},                                                         \
    {0x3178,0x5, 0x0},                                                         \
    {0x3179,0x0, 0x0},                                                         \
    {0x317a,0xfb, 0x0},                                                        \
    {0x317b,0x77, 0x0},                                                        \
    {0x317c,0x1, 0x0},                                                         \
    {0x317d,0x17, 0x0},                                                        \
    {0x317e,0x0, 0x0},                                                         \
    {0x317f,0x0, 0x0},                                                         \
    {0x3180,0x0, 0x0},                                                         \
    {0x3181,0x0, 0x0},                                                         \
    {0x3182,0x0, 0x0},                                                         \
    {0x3183,0x0, 0x0},                                                         \
    {0x3184,0x4, 0x0},                                                         \
    {0x3185,0x0, 0x0},                                                         \
    {0x3186,0x13, 0x0},                                                        \
    {0x3187,0x0, 0x0},                                                         \
    {0x3188,0x2c, 0x0},                                                        \
    {0x3189,0x0, 0x0},                                                         \
    {0x318a,0xfc, 0x0},                                                        \
    {0x318b,0x3, 0x0},                                                         \
    {0x318c,0xfc, 0x0},                                                        \
    {0x318d,0x3, 0x0},                                                         \
    {0x318e,0xfc, 0x0},                                                        \
    {0x318f,0x3, 0x0},                                                         \
    {0x3190,0xa, 0x0},                                                         \
    {0x3191,0x0, 0x0},                                                         \
    {0x3192,0x0, 0x0},                                                         \
    {0x3193,0x4, 0x0},                                                         \
    {0x3194,0x8, 0x0},                                                         \
    {0x3195,0x10, 0x0},                                                        \
    {0x3196,0x11, 0x0},                                                        \
    {0x3197,0x0, 0x0},                                                         \
    {0x3198,0x7c, 0x0},                                                        \
    {0x3199,0x0, 0x0},                                                         \
    {0x319a,0xd0, 0x0},                                                        \
    {0x319b,0x7, 0x0},                                                         \
    {0x319c,0xe, 0x0},                                                         \
    {0x319d,0x4, 0x0},                                                         \
    {0x319e,0xd, 0x0},                                                         \
    {0x319f,0x4, 0x0},                                                         \
    {0x31a0,0x0, 0x0},                                                         \
    {0x31a1,0x0, 0x0},                                                         \
    {0x31a2,0x0, 0x0},                                                         \
    {0x31a3,0x4, 0x0},                                                         \
    {0x31a4,0x0, 0x0},                                                         \
    {0x31a5,0x4a, 0x0},                                                        \
    {0x31a6,0x1, 0x0},                                                         \
    {0x31a7,0x4d, 0x0},                                                        \
    {0x31a8,0x1, 0x0},                                                         \
    {0x31a9,0x0, 0x0},                                                         \
    {0x31aa,0x3, 0x0},                                                         \
    {0x31ab,0x3, 0x0},                                                         \
    {0x31ac,0x0, 0x0},                                                         \
    {0x31ad,0x0, 0x0},                                                         \
    {0x31ae,0x0, 0x0},                                                         \
    {0x31af,0x2, 0x0},                                                         \
    {0x31b0,0x1, 0x0},                                                         \
    {0x31b1,0x0, 0x0},                                                         \
    {0x31b2,0x0, 0x0},                                                         \
    {0x31b3,0x0, 0x0},                                                         \
    {0x31b4,0x0, 0x0},                                                         \
    {0x31b5,0x0, 0x0},                                                         \
    {0x31b6,0x0, 0x0},                                                         \
    {0x31b7,0x0, 0x0},                                                         \
    {0x31b8,0x0, 0x0},                                                         \
    {0x31b9,0xd, 0x0},                                                         \
    {0x31ba,0x4, 0x0},                                                         \
    {0x31bb,0x0, 0x0},                                                         \
    {0x31bc,0x0, 0x0},                                                         \
    {0x31bd,0x0, 0x0},                                                         \
    {0x31be,0x0, 0x0},                                                         \
    {0x31bf,0x0, 0x0},                                                         \
    {0x31c0,0x0, 0x0},                                                         \
    {0x31c1,0x1f, 0x0},                                                        \
    {0x31c2,0x53, 0x0},                                                        \
    {0x31c3,0x6, 0x0},                                                         \
    {0x31c4,0x16, 0x0},                                                        \
    {0x31c5,0x0, 0x0},                                                         \
    {0x31c6,0x0, 0x0},                                                         \
    {0x31c7,0x0, 0x0},                                                         \
    {0x31c8,0x0, 0x0},                                                         \
    {0x31c9,0x0, 0x0},                                                         \
    {0x31ca,0x0, 0x0},                                                         \
    {0x31cb,0x0, 0x0},                                                         \
    {0x31cc,0x0, 0x0},                                                         \
    {0x31cd,0x0, 0x0},                                                         \
    {0x31ce,0x0, 0x0},                                                         \
    {0x31cf,0x0, 0x0},                                                         \
    {0x31d0,0x0, 0x0},                                                         \
    {0x31d1,0x0, 0x0},                                                         \
    {0x31d2,0x0, 0x0},                                                         \
    {0x31d3,0x0, 0x0},                                                         \
    {0x31d4,0x0, 0x0},                                                         \
    {0x31d5,0x0, 0x0},                                                         \
    {0x31d6,0x0, 0x0},                                                         \
    {0x31d7,0x0, 0x0},                                                         \
    {0x31d8,0x0, 0x0},                                                         \
    {0x31d9,0x0, 0x0},                                                         \
    {0x31da,0x0, 0x0},                                                         \
    {0x31db,0x0, 0x0},                                                         \
    {0x31dc,0x0, 0x0},                                                         \
    {0x31dd,0x0, 0x0},                                                         \
    {0x31de,0x0, 0x0},                                                         \
    {0x31df,0x0, 0x0},                                                         \
    {0x31e0,0x0, 0x0},  /* 38h, 0x0}, */                                       \
    {0x31e1,0x0, 0x0},                                                         \
    {0x31e2,0x0, 0x0},                                                         \
    {0x31e3,0x0, 0x0},                                                         \
    {0x31e4,0x0, 0x0},                                                         \
    {0x31e5,0x0, 0x0},                                                         \
    {0x31e6,0x0, 0x0},                                                         \
    {0x31e7,0x0, 0x0},                                                         \
    {0x31e8,0x1, 0x0},                                                         \
    {0x31e9,0x53, 0x0},                                                        \
    {0x31ea,0xa, 0x0},                                                         \
    {0x31eb,0xd7, 0x0},                                                        \
    {0x31ec,0xf, 0x0},                                                         \
    {0x31ed,0x38, 0x0},                                                        \
    {0x31ee,0x0, 0x0},                                                         \
    {0x31ef,0x0, 0x0},                                                         \
    {0x31f0,0x0, 0x0},                                                         \
    {0x31f1,0x0, 0x0},                                                         \
    {0x31f2,0x0, 0x0},                                                         \
    {0x31f3,0x78, 0x0},                                                        \
    {0x31f4,0x4, 0x0},                                                         \
    {0x31f5,0x0, 0x0},                                                         \
    {0x31f6,0x0, 0x0},                                                         \
    {0x31f7,0x0, 0x0},                                                         \
    {0x31f8,0x0, 0x0},                                                         \
    {0x31f9,0x0, 0x0},                                                         \
    {0x31fa,0x0, 0x0},                                                         \
    {0x31fb,0x0, 0x0},                                                         \
    {0x31fc,0x0, 0x0},                                                         \
    {0x31fd,0x0, 0x0},                                                         \
    {0x31fe,0x0, 0x0},                                                         \
    {0x3200,0xaa, 0x0},                                                        \
    {0x3201,0x0, 0x0},                                                         \
    {0x3202,0x0, 0x0},                                                         \
    {0x3203,0x5a, 0x0},                                                        \
    {0x3204,0xe0, 0x0},                                                        \
    {0x3205,0x15, 0x0},                                                        \
    {0x3206,0x56, 0x0},                                                        \
    {0x3207,0xf0, 0x0},                                                        \
    {0x3208,0x23, 0x0},                                                        \
    {0x3209,0xff, 0x0},                                                        \
    {0x320a,0xf, 0x0},                                                         \
    {0x320b,0x0, 0x0},                                                         \
    {0x320c,0xcf, 0x0},                                                        \
    {0x320d,0x80, 0x0},                                                        \
    {0x320e,0x5, 0x0},                                                         \
    {0x320f,0x32, 0x0},                                                        \
    {0x3210,0x90, 0x0},                                                        \
    {0x3211,0x19, 0x0},                                                        \
    {0x3212,0x2c, 0x0},                                                        \
    {0x3213,0x41, 0x0},                                                        \
    {0x3214,0x6, 0x0},                                                         \
    {0x3215,0x13, 0x0},                                                        \
    {0x3216,0x50, 0x0},                                                        \
    {0x3217,0x13, 0x0},                                                        \
    {0x3218,0x1, 0x0},                                                         \
    {0x3219,0x40, 0x0},                                                        \
    {0x321a,0x8, 0x0},                                                         \
    {0x321b,0x31, 0x0},                                                        \
    {0x321c,0x2, 0x0},                                                         \
    {0x321d,0x30, 0x0},                                                        \
    {0x321e,0x0, 0x0},                                                         \
    {0x321f,0x0, 0x0},                                                         \
    {0x3220,0x32, 0x0},                                                        \
    {0x3221,0x6, 0x0},                                                         \
    {0x3222,0x71, 0x0},                                                        \
    {0x3223,0x10, 0x0},                                                        \
    {0x3224,0x0, 0x0},                                                         \
    {0x3225,0x21, 0x0},                                                        \
    {0x3226,0x5, 0x0},                                                         \
    {0x3227,0x0, 0x0},                                                         \
    {0x3228,0x0, 0x0},                                                         \
    {0x3229,0x0, 0x0},                                                         \
    {0x322a,0x1, 0x0},                                                         \
    {0x322b,0x0, 0x0},                                                         \
    {0x322c,0x0, 0x0},                                                         \
    {0x322d,0x3, 0x0},                                                         \
    {0x322e,0x6, 0x0},                                                         \
    {0x322f,0x40, 0x0},                                                        \
    {0x3230,0x3, 0x0},                                                         \
    {0x3231,0x6, 0x0},                                                         \
    {0x3232,0x60, 0x0},                                                        \
    {0x3233,0x1a, 0x0},                                                        \
    {0x3234,0x0, 0x0},                                                         \
    {0x3235,0xd7, 0x0},                                                        \
    {0x3236,0x50, 0x0},                                                        \
    {0x3237,0x10, 0x0},                                                        \
    {0x3238,0xd9, 0x0},                                                        \
    {0x3239,0xe0, 0x0},                                                        \
    {0x323a,0xf, 0x0},                                                         \
    {0x323b,0x0, 0x0},                                                         \
    {0x323c,0xd9, 0x0},                                                        \
    {0x323d,0xe0, 0x0},                                                        \
    {0x323e,0xf, 0x0},                                                         \
    {0x323f,0x0, 0x0},                                                         \
    {0x3240,0xda, 0x0},                                                        \
    {0x3241,0x80, 0x0},                                                        \
    {0x3242,0xf, 0x0},                                                         \
    {0x3243,0x0, 0x0},                                                         \
    {0x3244,0xf9, 0x0},                                                        \
    {0x3245,0xd0, 0x0},                                                        \
    {0x3246,0xf, 0x0},                                                         \
    {0x3247,0x0, 0x0},                                                         \
    {0x3248,0x7, 0x0},                                                         \
    {0x3249,0x40, 0x0},                                                        \
    {0x324a,0x1a, 0x0},                                                        \
    {0x324b,0x7, 0x0},                                                         \
    {0x324c,0x40, 0x0},                                                        \
    {0x324d,0x3, 0x0},                                                         \
    {0x324e,0xff, 0x0},                                                        \
    {0x324f,0xff, 0x0},                                                        \
    {0x3250,0xff, 0x0},                                                        \
    {0x3251,0x0, 0x0},                                                         \
    {0x3252,0xd8, 0x0},                                                        \
    {0x3253,0x40, 0x0},                                                        \
    {0x3254,0x10, 0x0},                                                        \
    {0x3255,0x0, 0x0},                                                         \
    {0x3256,0xd9, 0x0},                                                        \
    {0x3257,0xe0, 0x0},                                                        \
    {0x3258,0xf, 0x0},                                                         \
    {0x3259,0xff, 0x0},                                                        \
    {0x325a,0xff, 0x0},                                                        \
    {0x325b,0xff, 0x0},                                                        \
    {0x325c,0x0, 0x0},                                                         \
    {0x325d,0x8, 0x0},                                                         \
    {0x325e,0xe0, 0x0},                                                        \
    {0x325f,0x19, 0x0},                                                        \
    {0x3260,0x8, 0x0},                                                         \
    {0x3261,0xe0, 0x0},                                                        \
    {0x3262,0x2, 0x0},                                                         \
    {0x3263,0x0, 0x0},                                                         \
    {0x3264,0xff, 0x0},                                                        \
    {0x3265,0x30, 0x0},                                                        \
    {0x3266,0x10, 0x0},                                                        \
    {0x3267,0xff, 0x0},                                                        \
    {0x3268,0xff, 0x0},                                                        \
    {0x3269,0xff, 0x0},                                                        \
    {0x326a,0x0, 0x0},                                                         \
    {0x326b,0x9f, 0x0},                                                        \
    {0x326c,0x31, 0x0},                                                        \
    {0x326d,0x1a, 0x0},                                                        \
    {0x326e,0x2f, 0x0},                                                        \
    {0x326f,0x30, 0x0},                                                        \
    {0x3270,0x3, 0x0},                                                         \
    {0x3271,0x0, 0x0},                                                         \
    {0x3272,0xf9, 0x0},                                                        \
    {0x3273,0x0, 0x0},                                                         \
    {0x3274,0x1a, 0x0},                                                        \
    {0x3275,0x0, 0x0},                                                         \
    {0x3276,0x0, 0x0},                                                         \
    {0x3277,0x0, 0x0},                                                         \
    {0x3278,0x0, 0x0},                                                         \
    {0x3279,0x0, 0x0},                                                         \
    {0x327a,0x0, 0x0},                                                         \
    {0x327b,0x0, 0x0},                                                         \
    {0x327c,0x0, 0x0},                                                         \
    {0x327d,0x0, 0x0},                                                         \
    {0x327e,0x90, 0x0},                                                        \
    {0x327f,0x1a, 0x0},                                                        \
    {0x3280,0xff, 0x0},                                                        \
    {0x3281,0xff, 0x0},                                                        \
    {0x3282,0xff, 0x0},                                                        \
    {0x3283,0x0, 0x0},                                                         \
    {0x3284,0x5, 0x0},                                                         \
    {0x3285,0x90, 0x0},                                                        \
    {0x3286,0x1a, 0x0},                                                        \
    {0x3287,0xff, 0x0},                                                        \
    {0x3288,0xff, 0x0},                                                        \
    {0x3289,0xff, 0x0},                                                        \
    {0x328a,0x0, 0x0},                                                         \
    {0x328b,0x83, 0x0},                                                        \
    {0x328c,0x0, 0x0},                                                         \
    {0x328d,0x1a, 0x0},                                                        \
    {0x328e,0x0, 0x0},                                                         \
    {0x328f,0x0, 0x0},                                                         \
    {0x3290,0x0, 0x0},                                                         \
    {0x3291,0x0, 0x0},                                                         \
    {0x3292,0x0, 0x0},                                                         \
    {0x3293,0x0, 0x0},                                                         \
    {0x3294,0x0, 0x0},                                                         \
    {0x3295,0x0, 0x0},                                                         \
    {0x3296,0x0, 0x0},                                                         \
    {0x3297,0x88, 0x0},                                                        \
    {0x3298,0x0, 0x0},                                                         \
    {0x3299,0x8, 0x0},                                                         \
    {0x329a,0x12, 0x0},                                                        \
    {0x329b,0xf1, 0x0},                                                        \
    {0x329c,0xc, 0x0},                                                         \
    {0x329d,0x0, 0x0},                                                         \
    {0x329e,0xb, 0x0},                                                         \
    {0x329f,0x80, 0x0},                                                        \
    {0x32a0,0x0, 0x0},                                                         \
    {0x32a1,0xb, 0x0},                                                         \
    {0x32a2,0x80, 0x0},                                                        \
    {0x32a3,0x0, 0x0},                                                         \
    {0x32a4,0x7a, 0x0},                                                        \
    {0x32a5,0x40, 0x0},                                                        \
    {0x32a6,0x0, 0x0},                                                         \
    {0x32a7,0x0, 0x0},                                                         \
    {0x32a8,0x4, 0x0},                                                         \
    {0x32a9,0xc0, 0x0},                                                        \
    {0x32aa,0x6, 0x0},                                                         \
    {0x32ab,0x0, 0x0},                                                         \
    {0x32ac,0x4, 0x0},                                                         \
    {0x32ad,0x10, 0x0},                                                        \
    {0x32ae,0x8, 0x0},                                                         \
    {0x32af,0x0, 0x0},                                                         \
    {0x32b0,0x4, 0x0},                                                         \
    {0x32b1,0x10, 0x0},                                                        \
    {0x32b2,0x8, 0x0},                                                         \
    {0x32b3,0x0, 0x0},                                                         \
    {0x32b4,0xd9, 0x0},                                                        \
    {0x32b5,0x0, 0x0},                                                         \
    {0x32b6,0x0, 0x0},                                                         \
    {0x32b7,0x0, 0x0},                                                         \
    {0x32b8,0x8, 0x0},                                                         \
    {0x32b9,0x40, 0x0},                                                        \
    {0x32ba,0x0, 0x0},                                                         \
    {0x32bb,0x0, 0x0},                                                         \
    {0x32bc,0x84, 0x0},                                                        \
    {0x32bd,0x10, 0x0},                                                        \
    {0x32be,0x8, 0x0},                                                         \
    {0x32bf,0x0, 0x0},                                                         \
    {0x32c0,0x8, 0x0},                                                         \
    {0x32c1,0x50, 0x0},                                                        \
    {0x32c2,0x0, 0x0},                                                         \
    {0x32c3,0xdc, 0x0},                                                        \
    {0x32c4,0x90, 0x0},                                                        \
    {0x32c5,0xd, 0x0},                                                         \
    {0x32c6,0x0, 0x0},                                                         \
    {0x32c7,0x8, 0x0},                                                         \
    {0x32c8,0x50, 0x0},                                                        \
    {0x32c9,0x0, 0x0},                                                         \
    {0x32ca,0xa0, 0x0},                                                        \
    {0x32cb,0x1, 0x0},                                                         \
    {0x32cc,0x5, 0x0},                                                         \
    {0x32cd,0x0, 0x0},                                                         \
    {0x32ce,0x50, 0x0},                                                        \
    {0x32cf,0x0, 0x0},                                                         \
    {0x32d0,0x1a, 0x0},                                                        \
    {0x32d1,0x1, 0x0},                                                         \
    {0x32d2,0x0, 0x0},                                                         \
    {0x32d3,0x0, 0x0},                                                         \
    {0x32d4,0x0, 0x0},                                                         \
    {0x32d5,0x0, 0x0},                                                         \
    {0x32d6,0x9e, 0x0},                                                        \
    {0x32d7,0x1, 0x0},                                                         \
    {0x32d8,0x9, 0x0},                                                         \
    {0x32d9,0x0, 0x0},                                                         \
    {0x32da,0x9a, 0x0},                                                        \
    {0x32db,0xf0, 0x0},                                                        \
    {0x32dc,0xc, 0x0},                                                         \
    {0x32dd,0x30, 0x0},                                                        \
    {0x32de,0x41, 0x0},                                                        \
    {0x32df,0x19, 0x0},                                                        \
    {0x32e0,0x0, 0x0},                                                         \
    {0x32e1,0x1e, 0x0},                                                        \
    {0x32e2,0x30, 0x0},                                                        \
    {0x32e3,0x5, 0x0},                                                         \
    {0x32e4,0x5c, 0x0},                                                        \
    {0x32e5,0x0, 0x0},                                                         \
    {0x32e6,0xc, 0x0},                                                         \
    {0x32e7,0x96, 0x0},                                                        \
    {0x32e8,0x30, 0x0},                                                        \
    {0x32e9,0xd, 0x0},                                                         \
    {0x32ea,0x2c, 0x0},                                                        \
    {0x32eb,0x81, 0x0},                                                        \
    {0x32ec,0x19, 0x0},                                                        \
    {0x32ed,0x0, 0x0},                                                         \
    {0x32ee,0x1a, 0x0},                                                        \
    {0x32ef,0x70, 0x0},                                                        \
    {0x32f0,0x5, 0x0},                                                         \
    {0x32f1,0x58, 0x0},                                                        \
    {0x32f2,0x40, 0x0},                                                        \
    {0x32f3,0xc, 0x0},                                                         \
    {0x32f4,0x8c, 0x0},                                                        \
    {0x32f5,0x20, 0x0},                                                        \
    {0x32f6,0x9, 0x0},                                                         \
    {0x32f7,0x0, 0x0},                                                         \
    {0x32f8,0x84, 0x0},                                                        \
    {0x32f9,0x40, 0x0},                                                        \
    {0x32fa,0x7, 0x0},                                                         \
    {0x32fb,0x1a, 0x0},                                                        \
    {0x32fc,0xa1, 0x0},                                                        \
    {0x32fd,0x10, 0x0},                                                        \
    {0x32fe,0x0, 0x0},                                                         \
    {0x3300,0x0, 0x0},                                                         \
    {0x3301,0x85, 0x0},                                                        \
    {0x3302,0x50, 0x0},                                                        \
    {0x3303,0x7, 0x0},                                                         \
    {0x3304,0x1b, 0x0},                                                        \
    {0x3305,0xb1, 0x0},                                                        \
    {0x3306,0x10, 0x0},                                                        \
    {0x3307,0x0, 0x0},                                                         \
    {0x3308,0x7c, 0x0},                                                        \
    {0x3309,0xc0, 0x0},                                                        \
    {0x330a,0x8, 0x0},                                                         \
    {0x330b,0x12, 0x0},                                                        \
    {0x330c,0x21, 0x0},                                                        \
    {0x330d,0x12, 0x0},                                                        \
    {0x330e,0x0, 0x0},                                                         \
    {0x330f,0x7d, 0x0},                                                        \
    {0x3310,0xd0, 0x0},                                                        \
    {0x3311,0x8, 0x0},                                                         \
    {0x3312,0x13, 0x0},                                                        \
    {0x3313,0x31, 0x0},                                                        \
    {0x3314,0x12, 0x0},                                                        \
    {0x3315,0x0, 0x0},                                                         \
    {0x3316,0x7e, 0x0},                                                        \
    {0x3317,0x20, 0x0},                                                        \
    {0x3318,0x8, 0x0},                                                         \
    {0x3319,0x14, 0x0},                                                        \
    {0x331a,0x81, 0x0},                                                        \
    {0x331b,0x11, 0x0},                                                        \
    {0x331c,0x0, 0x0},                                                         \
    {0x331d,0x86, 0x0},                                                        \
    {0x331e,0xa0, 0x0},                                                        \
    {0x331f,0x8, 0x0},                                                         \
    {0x3320,0x1c, 0x0},                                                        \
    {0x3321,0x1, 0x0},                                                         \
    {0x3322,0x12, 0x0},                                                        \
    {0x3323,0x0, 0x0},                                                         \
    {0x3324,0x8c, 0x0},                                                        \
    {0x3325,0x20, 0x0},                                                        \
    {0x3326,0x9, 0x0},                                                         \
    {0x3327,0x0, 0x0},                                                         \
    {0x3328,0xcf, 0x0},                                                        \
    {0x3329,0x10, 0x0},                                                        \
    {0x332a,0xd, 0x0},                                                         \
    {0x332b,0x0, 0x0},                                                         \
    {0x332c,0x53, 0x0},                                                        \
    {0x332d,0x50, 0x0},                                                        \
    {0x332e,0x5, 0x0},                                                         \
    {0x332f,0x0, 0x0},                                                         \
    {0x3330,0x1, 0x0},                                                         \
    {0x3331,0x20, 0x0},                                                        \
    {0x3332,0x0, 0x0},                                                         \
    {0x3333,0x0, 0x0},                                                         \
    {0x3334,0x45, 0x0},                                                        \
    {0x3335,0xb1, 0x0},                                                        \
    {0x3336,0x19, 0x0},                                                        \
    {0x3337,0x1, 0x0},                                                         \
    {0x3338,0x0, 0x0},                                                         \
    {0x3339,0x0, 0x0},                                                         \
    {0x333a,0x0, 0x0},                                                         \
    {0x333b,0x0, 0x0},                                                         \
    {0x333c,0x0, 0x0},                                                         \
    {0x333d,0x0, 0x0},                                                         \
    {0x333e,0x0, 0x0},                                                         \
    {0x333f,0x0, 0x0},                                                         \
    {0x3340,0x0, 0x0},                                                         \
    {0x3341,0x11, 0x0},                                                        \
    {0x3342,0x11, 0x0},                                                        \
    {0x3343,0x0, 0x0},                                                         \
    {0x3344,0x10, 0x0},  /* repetition changed, 0x0}, */                       \
    {0x3345,0x0, 0x0},                                                         \
    {0x3346,0x3, 0x0}, /* physical lane num 01h, 0x0}, */                      \
    {0x3347,0x0, 0x0},                                                         \
    {0x3348,0x0, 0x0},                                                         \
    {0x3349,0x0, 0x0},                                                         \
    {0x334a,0x0, 0x0},                                                         \
    {0x334b,0x0, 0x0},                                                         \
    {0x334c,0x0, 0x0},                                                         \
    {0x334d,0x0, 0x0},                                                         \
    {0x334e,0xf, 0x0},                                                         \
    {0x334f,0x20, 0x0},                                                        \
    {0x3350,0x0, 0x0},                                                         \
    {0x3351,0xf, 0x0},                                                         \
    {0x3352,0x1, 0x0},                                                         \
    {0x3353,0xe, 0x0},  /* ob soze v 04h, 0x0}, */                             \
    {0x3354,0x1, 0x0},                                                         \
    {0x3355,0x0, 0x0},                                                         \
    {0x3356,0x0, 0x0},                                                         \
    {0x3357,0x64, 0x0},  /* pic size v changed, 0x0}, */                       \
    {0x3358,0x8, 0x0}, /* pic size v changed, 0x0}, */                         \
    {0x3359,0x1, 0x0},                                                         \
    {0x335a,0x0, 0x0},                                                         \
    {0x335b,0x40, 0x0},                                                        \
    {0x335c,0x0, 0x0},                                                         \
    {0x335d,0x0, 0x0},                                                         \
    {0x335e,0x0, 0x0},                                                         \
    {0x335f,0x0, 0x0},                                                         \
    {0x3360,0x0, 0x0},                                                         \
    {0x3361,0x0, 0x0},                                                         \
    {0x3362,0x0, 0x0},                                                         \
    {0x3363,0x0, 0x0},                                                         \
    {0x3364,0x0, 0x0},                                                         \
    {0x3365,0x16, 0x0},                                                        \
    {0x3366,0x0, 0x0},                                                         \
    {0x3367,0x0, 0x0},                                                         \
    {0x3368,0x0, 0x0},                                                         \
    {0x3369,0x0, 0x0},                                                         \
    {0x336a,0x0, 0x0},                                                         \
    {0x336b,0x37, 0x0},  /* thsexit changed, 0x0}, */                          \
    {0x336c,0x1f, 0x0},                                                        \
    {0x336d,0x3, 0x0},                                                         \
    {0x336e,0x0, 0x0},                                                         \
    {0x336f,0x0, 0x0},                                                         \
    {0x3370,0x0, 0x0},                                                         \
    {0x3371,0x0, 0x0},                                                         \
    {0x3372,0x0, 0x0},                                                         \
    {0x3373,0x0, 0x0},                                                         \
    {0x3374,0x0, 0x0},                                                         \
    {0x3375,0x0, 0x0},                                                         \
    {0x3376,0x0, 0x0},                                                         \
    {0x3377,0x0, 0x0},                                                         \
    {0x3378,0x0, 0x0},                                                         \
    {0x3379,0x0, 0x0},                                                         \
    {0x337a,0x0, 0x0},                                                         \
    {0x337b,0x0, 0x0},                                                         \
    {0x337c,0x0, 0x0},                                                         \
    {0x337d,0xc, 0x0},                                                         \
    {0x337e,0xc, 0x0},                                                         \
    {0x337f,0x3 , 0x0}, /* csi lane mode 01h, 0x0}, */                         \
    {0x3380,0x0 , 0x0}, /* inck freq1 20h, 0x0}, */                            \
    {0x3381,0x1b, 0x0}, /* inck freq1 25h, 0x0}, */                            \
    {0x3382,0x5F, 0x0}, /* tclkpost changed, 0x0}, */                          \
    {0x3383,0x17, 0x0}, /* thsprepare changed, 0x0}, */                        \
    {0x3384,0x37, 0x0}, /* thszero changed, 0x0}, */                           \
    {0x3385,0x17, 0x0}, /* thstrail changed, 0x0}, */                          \
    {0x3386,0x17, 0x0}, /* tclktrail changed, 0x0}, */                         \
    {0x3387,0x17, 0x0}, /* tclkprepare changed, 0x0}, */                       \
    {0x3388,0x4F, 0x0}, /* tclkzero changed, 0x0}, */                          \
    {0x3389,0x27, 0x0}, /* tlpx changed, 0x0}, */                              \
    {0x338a,0x30, 0x0},                                                        \
    {0x338b,0x30, 0x0},                                                        \
    {0x338c,0x30, 0x0},                                                        \
    {0x338d,0x3d, 0x0},  /* inck freq2 B4h, 0x0}, */                           \
    {0x338e,0x1, 0x0}, /* inck freq2 01h, 0x0}, */                             \
    {0x338f,0xba, 0x0},                                                        \
    {0x3390,0x2c, 0x0},                                                        \
    {0x3391,0x18, 0x0},                                                        \
    {0x3392,0x8, 0x0},                                                         \
    {0x3393,0x8, 0x0},                                                         \
    {0x3394,0x1, 0x0},                                                         \
    {0x3395,0x0, 0x0},                                                         \
    {0x3396,0x0, 0x0},                                                         \
    {0x3397,0x0, 0x0},                                                         \
    {0x3398,0x0, 0x0},                                                         \
    {0x3399,0x24, 0x0},                                                        \
    {0x339a,0x2, 0x0},                                                         \
    {0x339b,0x1, 0x0},                                                         \
    {0x339c,0x1, 0x0},                                                         \
    {0x339d,0x0, 0x0},                                                         \
    {0x339e,0x1, 0x0},                                                         \
    {0x339f,0xf0, 0x0},                                                        \
    {0x33a0,0x0, 0x0},                                                         \
    {0x33a1,0xc, 0x0},                                                         \
    {0x33a2,0xc, 0x0},                                                         \
    {0x33a3,0x0, 0x0},                                                         \
    {0x33a4,0x0, 0x0},                                                         \
    {0x33a5,0x0, 0x0},                                                         \
    {0x33a6,0xf0, 0x0},                                                        \
    {0x33a7,0x0, 0x0},                                                         \
    {0x33a8,0x1, 0x0},                                                         \
    {0x33a9,0x0, 0x0},                                                         \
    {0x33aa,0x0, 0x0},                                                         \
    {0x33ab,0x0, 0x0},                                                         \
    {0x33ac,0x0, 0x0},                                                         \
    {0x33ad,0xf0, 0x0},                                                        \
    {0x33ae,0x0, 0x0},                                                         \
    {0x33af,0x1, 0x0},                                                         \
    {0x33b0,0x0, 0x0},                                                         \
    {0x33b1,0xf0, 0x0},                                                        \
    {0x33b2,0x0, 0x0},                                                         \
    {0x33b3,0x0, 0x0},                                                         \
    {0x33b4,0x0, 0x0},                                                         \
    {0x33b5,0x0, 0x0},                                                         \
    {0x33b6,0x0, 0x0},                                                         \
    {0x33b7,0x0, 0x0},                                                         \
    {0x33b8,0x0, 0x0},                                                         \
    {0x33b9,0x0, 0x0},                                                         \
    {0x33ba,0x0, 0x0},                                                         \
    {0x33bb,0x0, 0x0},                                                         \
    {0x33bc,0x0, 0x0},                                                         \
    {0x33bd,0x0, 0x0},                                                         \
    {0x33be,0x0, 0x0},                                                         \
    {0x33bf,0x0, 0x0},                                                         \
    {0x33c0,0x0, 0x0},                                                         \
    {0x33c1,0x0, 0x0},                                                         \
    {0x33c2,0x0, 0x0},                                                         \
    {0x33c3,0x0, 0x0},                                                         \
    {0x33c4,0x0, 0x0},                                                         \
    {0x33c5,0x0, 0x0},                                                         \
    {0x33c6,0x0, 0x0},                                                         \
    {0x33c7,0x0, 0x0},                                                         \
    {0x33c8,0x0, 0x0},                                                         \
    {0x33c9,0x65, 0x0},                                                        \
    {0x33ca,0x4, 0x0},                                                         \
    {0x33cb,0x0, 0x0},                                                         \
    {0x33cc,0x98, 0x0},                                                        \
    {0x33cd,0x8, 0x0},                                                         \
    {0x33ce,0x0, 0x0},                                                         \
    {0x33cf,0x0, 0x0},                                                         \
    {0x33d0,0x0, 0x0},                                                         \
    {0x33d1,0x0, 0x0},                                                         \
    {0x33d2,0x9b, 0x0},                                                        \
    {0x33d3,0x7, 0x0},                                                         \
    {0x33d4,0xc8, 0x0},                                                        \
    {0x33d5,0x4, 0x0},                                                         \
    {0x33d6,0x9c, 0x0},                                                        \
    {0x33d7,0x7, 0x0},                                                         \
    {0x33d8,0xc9, 0x0},                                                        \
    {0x33d9,0x4, 0x0},                                                         \
    {0x33da,0x0, 0x0},                                                         \
    {0x33db,0x0, 0x0},                                                         \
    {0x33dc,0x0, 0x0},                                                         \
    {0x33dd,0x0, 0x0},                                                         \
    {0x33de,0x0, 0x0},                                                         \
    {0x33df,0x0, 0x0},                                                         \
    {0x33e0,0x1b, 0x0},                                                        \
    {0x33e1,0x5, 0x0},                                                         \
    {0x33e2,0xd0, 0x0},                                                        \
    {0x33e3,0x3, 0x0},                                                         \
    {0x33e4,0x7c, 0x0},                                                        \
    {0x33e5,0x1, 0x0},                                                         \
    {0x33e6,0x31, 0x0},                                                        \
    {0x33e7,0x1, 0x0},                                                         \
    {0x33e8,0x1c, 0x0},                                                        \
    {0x33e9,0x5, 0x0},                                                         \
    {0x33ea,0xd1, 0x0},                                                        \
    {0x33eb,0x3, 0x0},                                                         \
    {0x33ec,0x1, 0x0},                                                         \
    {0x33ed,0x3, 0x0},                                                         \
    {0x33ee,0x0, 0x0},                                                         \
    {0x33ef,0x0, 0x0},                                                         \
    {0x33f0,0xb, 0x0},                                                         \
    {0x33f1,0x0, 0x0},                                                         \
    {0x33f2,0xc, 0x0},                                                         \
    {0x33f3,0x0, 0x0},                                                         \
    {0x33f4,0x0, 0x0},                                                         \
    {0x33f5,0x0, 0x0},                                                         \
    {0x33f6,0xf, 0x0},                                                         \
    {0x33f7,0x0, 0x0},                                                         \
    {0x33f8,0x6, 0x0},                                                         \
    {0x33f9,0x0, 0x0},                                                         \
    {0x33fa,0x10, 0x0},                                                        \
    {0x33fb,0x0, 0x0},                                                         \
    {0x33fc,0x0, 0x0},                                                         \
    {0x33fd,0x0, 0x0},                                                         \
    {0x33fe,0x0, 0x0},                                                         \
    {0x3000,0x0, 0x0},                                                         \
}


#endif /* IMX224_LINEAR_1280X960_CONFIG_H_ */
