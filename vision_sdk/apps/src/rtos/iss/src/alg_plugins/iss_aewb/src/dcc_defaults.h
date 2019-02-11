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
#ifndef ALGORITHMS_LINK_AEWB_DCC_DEFAULTS
#define ALGORITHMS_LINK_AEWB_DCC_DEFAULTS

static const vpsissNsf3Config_t gIssDccNsf3DefCfg =
{
    FALSE,                      // Bypass
    VPS_ISS_NSF3_OP_MODE_BAYER, // mode
    TRUE,                       // border replicate
    FALSE,      // chroma desaturation
    {
        /* hPos */
        {
            {0u,16u,         128u, 1024u},
            {0u,16u,         128u, 1024u},
            {0u,16u,         128u, 1024u},
            {0u,16u,         128u, 1024u}
        },
        /* vpos */
        {
            {2u,3u,          6u,   8u   },
            {2u,3u,          6u,   8u   },
            {2u,3u,          6u,   8u   },
            {2u,3u,          6u,   8u   }
        },
        /* Slope */
        {
            {128u,54u,         4u,   2u   },
            {128u,54u,         4u,   2u   },
            {128u,54u,         4u,   2u   },
            {128u,54u,         4u,   2u   }
        },
        64u,    16u,
        {
            32u,80u,         128u
        }
    },
    {
        {128u,  128u,        128u},
        {128u,  128u,        128u},
        {128u,  128u,        128u},
        {128u,  128u,        128u}
    },
    {
        {128u,  128u,        128u},
        {128u,  128u,        128u},
        {128u,  128u,        128u},
        {128u,  128u,        128u}
    },
    {
        FALSE,  // ee_enable
        {
            {64u,64u,         64u},
            {64u,64u,         64u},
            {64u,64u,         64u},
            {64u,64u,         64u}
        },
        {
            {64u,64u,         64u},
            {64u,64u,         64u},
            {64u,64u,         64u},
            {64u,64u,         64u}
        },
        0u,     0u,          0u,   0u
    },
    {
        FALSE,  // shading gain enable
        {0u,    0u},
        {0u,    0u},
        {0u,    0u},
        0u,     0u,          0u,   0u, 0u,
        0u,     0u,          0u,   0u, 99u
    },
};

static const vpsissH3aAewbConfig_t gIssDccAewbDefCfg =
{
        FALSE,                              /* enableALowCompr */
        FALSE,                              /* enableMedFilt */
        0x0U,                               /* midFiltThreshold */
        /* Window Configuration */
        {
            {0x0U,    0x6U },             /* Position */
            64U, 8,                       /* Size */
            20U, 119U,                    /* Count */
            4U, 2U                        /* Increment */
        },
        1914U,                            /* Black Line Vertical Start */
        2U,                               /* Black Line height */
        VPS_ISS_H3A_OUTPUT_MODE_SUM_ONLY, /* Output Mode */
        0x0U,                             /* sumShift */
        1023U,                            /* Saturation Limit */
        VPS_ISS_H3A_MODE_NORMAL           /* Advanced mode */
};

static const vpsissIpipeifWdrCfg_t gIssDccDefWdrCfg =
{
    TRUE,       /* Enable */
    FALSE,      /* WDR Direction */
    15u,        /* DST */
    4u,         /* SBIT */
    4u,         /* LBIT */
    1u,         /* WGT_SEL */
    0,          /* AFE */
    0,          /* AFM */
    0,          /* BF */
    32768u,     /* GSHORT */
    2048u,      /* GLONG */
    4095,      /* Threshold */
    0u,         /* LBK00 */
    0u,         /* LBK01 */
    0u,         /* LBK10 */
    0u,         /* LBK11 */
    0u,         /* SBK00 */
    0u,         /* SBK01 */
    0u,         /* SBK10 */
    0u,         /* SBK11 */
    0x0u,       /* MAS */
    65535u,     /* MAD */
    512u,       /* LWB00 */
    512u,       /* LWB01 */
    512u,       /* LWB10 */
    512u,       /* LWB11 */
    512u,       /* SWB00 */
    512u,       /* SWB01 */
    512u,       /* SWB10 */
    512u,       /* SWB11 */
    0u,         /* Merge Shift */
    65535u     /* Merge Clip */
};

static const vpsissGlbceConfig_t gIssDccDefGlbceCfg =
{
    TRUE,           /* ENABLE */
    255u,           /* IR Strength */
    0,              /* blackLevel */
    65535,          /* White Level */
    12,             /* Intensity variance */
    7,              /* Spacial variance */
    6,              /* Bright Amplification Limit */
    6,              /* Dark Amplification Limit */
    VPS_ISS_GLBCE_DITHER_FOUR_BIT,
    64,             /* MAX Slope Limit */
    72,             /* MIN Slope Limit */
    {0,5377,10218,14600,18585,22224,25561,28631,31466,34092,36530,38801,40921,42904,44764,46511,48156,49706,51171,52557,53870,55116,56299,57425,58498,59520,60497,61429,62322,63176,63995,64781,65535}
};


#endif

