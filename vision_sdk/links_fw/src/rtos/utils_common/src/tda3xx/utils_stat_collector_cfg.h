/*
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
*/

/**
 *******************************************************************************
 * \file utils_stat_collector_cfg.c
 *
 * \brief  This file has the implementataion of statCollector task.
 *
 *
 * \version 0.0 (Jan 2014) : [FM] First version
 *
 *******************************************************************************
*/

#define UTILS_STAT_COLLECTOR_MSTR_CFG_ARRAY_0               \
{                                                           \
    /* set 0 */                                             \
    {                                                       \
        "SCI_EMIF_SYS",                                     \
        UTILS_STATCOLL_DATA_BW_MOD_EMIF1_RD_WR,                   \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_EMIF_SYS,                                   \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_IPU",                                          \
        UTILS_STATCOLL_DATA_BW_MOD_IPU1,                          \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_IPU,                                        \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_DSP1_MDMA",                                    \
        UTILS_STATCOLL_DATA_BW_MOD_DSP1_MDMA,                     \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_DSP1_MDMA,                                  \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_DSP2_MDMA",                                    \
        UTILS_STATCOLL_DATA_BW_MOD_DSP2_MDMA,                     \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_DSP2_MDMA,                                  \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_DSS",                                          \
        UTILS_STATCOLL_DATA_BW_MOD_DSS,                           \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_DSS,                                        \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_MMU",                                          \
        UTILS_STATCOLL_DATA_BW_MOD_MMU,                           \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_MMU,                                        \
            0                                               \
        }                                                   \
    },                                                      \
                                                            \
    {                                                       \
        "SCI_EDMA_TC0_RD",                                  \
        UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_RD,                   \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_EDMA_TC0_RD,                                \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_EDMA_TC0_WR",                                  \
        UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_WR,                   \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_EDMA_TC0_WR,                                \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_VIP_P1",                                       \
        UTILS_STATCOLL_DATA_BW_MOD_VIP1_P1,                       \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_VIP_P1,                                     \
            0                                               \
        }                                                   \
    },                                                      \
                                                            \
    {                                                       \
        "SCI_VIP_P2",                                       \
        UTILS_STATCOLL_DATA_BW_MOD_VIP1_P2,                       \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_VIP_P2,                                     \
            0                                               \
        }                                                   \
    },                                                      \
                                                            \
    {                                                       \
        "SCI_ISS_RT",                                       \
        UTILS_STATCOLL_DATA_BW_MOD_ISS_RT,                        \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_ISS_RT,                                     \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_ISS_NRT2",                                     \
        UTILS_STATCOLL_DATA_BW_MOD_ISS_NRT2,                      \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_ISS_NRT2,                                   \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_EVE_P1",                                       \
        UTILS_STATCOLL_DATA_BW_MOD_EVE1_P1,                       \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_EVE_P1,                                     \
            0                                               \
        }                                                   \
    },                                                      \
                                                            \
    {                                                       \
        "SCI_EVE_P2",                                       \
        UTILS_STATCOLL_DATA_BW_MOD_EVE1_P2,                       \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_EVE_P2,                                     \
            0                                               \
        }                                                   \
    },                                                      \
}

#define UTILS_STAT_COLLECTOR_MSTR_CFG_ARRAY_1               \
{                                                           \
    /* set 1 */                                             \
    {                                                       \
        "SCI_GMAC_SW",                                      \
        UTILS_STATCOLL_DATA_BW_MOD_GMAC_SW,                       \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_GMAC_SW,                                    \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_ISS_NRT1",                                     \
        UTILS_STATCOLL_DATA_BW_MOD_ISS_NRT1,                      \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_ISS_NRT1,                                   \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_DSP2_CFG",                                     \
        UTILS_STATCOLL_DATA_BW_MOD_DSP2_CFG,                      \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_DSP2_CFG,                                   \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_DSP2_EDMA",                                    \
        UTILS_STATCOLL_DATA_BW_MOD_DSP2_EDMA,                     \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_DSP2_EDMA,                                  \
            0                                               \
        }                                                   \
    },                                                      \
                                                            \
    {                                                       \
        "SCI_OCMC_RAM",                                     \
        UTILS_STATCOLL_DATA_BW_MOD_OCMC_RAM,                      \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_OCMC_RAM,                                   \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_DSP1_CFG",                                     \
        UTILS_STATCOLL_DATA_BW_MOD_DSP1_CFG,                      \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_DSP1_CFG,                                   \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_DSP1_EDMA",                                    \
        UTILS_STATCOLL_DATA_BW_MOD_DSP1_EDMA,                     \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_DSP1_EDMA,                                  \
            0                                               \
        }                                                   \
    },                                                      \
                                                            \
    {                                                       \
        "SCI_GPMC",                                         \
        UTILS_STATCOLL_DATA_BW_MOD_GPMC,                          \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_GPMC,                                       \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_MCASP",                                        \
        UTILS_STATCOLL_DATA_BW_MOD_MCASP,                         \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_MCASP,                                      \
            0                                               \
        }                                                   \
    },                                                      \
    {                                                       \
        "SCI_EDMA_TC1_RD",                                  \
        UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_RD,                   \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_EDMA_TC1_RD,                                \
            0                                               \
        }                                                   \
    },                                                      \
                                                            \
    {                                                       \
        "SCI_EDMA_TC1_WR",                                  \
        UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_WR,                   \
        {                                                   \
            SCI_MSTR_THROUGHPUT,                            \
            SCI_EDMA_TC1_WR,                                \
            0                                               \
        }                                                   \
    },                                                      \
}



