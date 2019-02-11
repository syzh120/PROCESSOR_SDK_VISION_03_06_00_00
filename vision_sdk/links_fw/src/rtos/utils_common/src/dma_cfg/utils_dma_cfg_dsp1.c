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
 *
 * \file utils_dma_cfg_dsp1.c
 *
 * \brief This file has the configuration for DSP1 CPU
 *
 * \version 0.0 (Aug 2013) : [KC] First version
 *
 *******************************************************************************
 */


/** Offset from which CPU interrupts start in control module XBAR config */
#define UTILS_DSP1_XBAR_OFFSET                    (32U-1U)

/** Interrupt no. for Transfer Completion */
#define UTILS_DMA_SYS_EDMA_CCXFER_COMPLETION_INT  (38U)

/** Interrupt no. for CC Error */
#define UTILS_DMA_SYS_EDMA_CCERROR_INT            (39U)

/** Interrupt no. for TCs Error */
#define UTILS_DMA_SYS_EDMA_TC0_ERROR_INT          (40U)
#define UTILS_DMA_SYS_EDMA_TC1_ERROR_INT          (41U)
#define UTILS_DMA_SYS_EDMA_TC2_ERROR_INT          (0U)
#define UTILS_DMA_SYS_EDMA_TC3_ERROR_INT          (0U)
#define UTILS_DMA_SYS_EDMA_TC4_ERROR_INT          (0U)
#define UTILS_DMA_SYS_EDMA_TC5_ERROR_INT          (0U)
#define UTILS_DMA_SYS_EDMA_TC6_ERROR_INT          (0U)
#define UTILS_DMA_SYS_EDMA_TC7_ERROR_INT          (0U)

/**
 *******************************************************************************
 * EDMA3 interrupts (transfer completion, CC error etc.) correspond to different
 * ECM events (DSP specific).
 *
 * These ECM events come under ECM block XXX
 * (handling those specific ECM events).
 *
 * Normally, block 0 handles events 4-31 (events 0-3 are reserved),
 * block 1 handles events 32-63 and so on.
 *
 * This ECM block XXX (or interrupt selection number XXX)
 * is mapped to a specific HWI_INT YYY in the .cfg file.
 *
 * Define UTILS_DMA_SYS_EDMA_HWI_INT_XFER_COMP to specific HWI_INT,
 * corresponding to transfer completion interrupt.
 *
 * Define UTILS_DMA_SYS_EDMA_HWI_INT_CC_ERR to specific HWI_INT, corresponding
 * to CC error interrupts.
 *
 * Define UTILS_DMA_SYS_EDMA_HWI_INT_TC_ERR to specific HWI_INT, corresponding
 * to TC error interrupts.
 *******************************************************************************
 */
#define UTILS_DMA_SYS_EDMA_HWI_INT_XFER_COMP   (8U)
#define UTILS_DMA_SYS_EDMA_HWI_INT_CC_ERR      (8U)
#define UTILS_DMA_SYS_EDMA_HWI_INT_TC0_ERR     (8U)
#define UTILS_DMA_SYS_EDMA_HWI_INT_TC1_ERR     (8U)

#define UTILS_DMA_SYSTEM_DMA_BASE_ADDR         (0x43300000U)

#include "utils_dma_cfg_dsp_local_edma.c"
#ifdef TDA3XX_FAMILY_BUILD
#include "utils_dma_cfg_sys_edma_tda3xx.c"
#else
#include "utils_dma_cfg_sys_edma_tda2xx.c"
#endif

/**
 *******************************************************************************
 * \brief System EDMA resource allocation for this CPU
 *******************************************************************************
 */
EDMA3_DRV_InstanceInitConfig gUtils_dmaSysEdmaInstInitConfig =
{
    /* 31     0                     63    32                    95    64                    127   96 */
    {UTILS_DSP1_EDMACH_ALLOC_0, UTILS_DSP1_EDMACH_ALLOC_1, UTILS_DSP1_PARAM_ALLOC_0, UTILS_DSP1_PARAM_ALLOC_1,
    /* 159  128                     191  160                    223  192                    255  224 */
     UTILS_DSP1_PARAM_ALLOC_2 , UTILS_DSP1_PARAM_ALLOC_3 , UTILS_DSP1_PARAM_ALLOC_4, UTILS_DSP1_PARAM_ALLOC_5,
    /* 287  256                     319  288                    351  320                    383  352 */
     UTILS_DSP1_PARAM_ALLOC_6 , UTILS_DSP1_PARAM_ALLOC_7 , UTILS_DSP1_PARAM_ALLOC_8, UTILS_DSP1_PARAM_ALLOC_9,
    /* 415  384                     447  416                    479  448                    511  480 */
     UTILS_DSP1_PARAM_ALLOC_10, UTILS_DSP1_PARAM_ALLOC_11, UTILS_DSP1_PARAM_ALLOC_12, UTILS_DSP1_PARAM_ALLOC_13},

    /* ownDmaChannels */
    /* 31     0                     63    32 */
    {UTILS_DSP1_EDMACH_ALLOC_0, UTILS_DSP1_EDMACH_ALLOC_1},

    /* ownQdmaChannels */
    /* 31     0 */
    {UTILS_DSP1_QDMACH_ALLOC_0},

    /* ownTccs */
    /* 31     0                     63    32 */
    {UTILS_DSP1_EDMACH_ALLOC_0, UTILS_DSP1_EDMACH_ALLOC_1},


    /* resvdPaRAMSets */
    /* 31     0     63    32     95    64     127   96 */
    {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    /* 159  128     191  160     223  192     255  224 */
     0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    /* 287  256     319  288     351  320     383  352 */
     0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    /* 415  384     447  416     479  448     511  480 */
     0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

    /* resvdDmaChannels */
    /* 31     0    63     32 */
    {0x00000000u, 0x00000000u},

    /* resvdQdmaChannels */
    /* 31     0 */
    {0x00000000u},

    /* resvdTccs */
    /* 31     0    63     32 */
    {0x00000000u, 0x00000000u},
};

EDMA3_DRV_GblConfigParams gUtils_dmaSysEdmaGblCfgParams = UTILS_DMASYSEDMAGBLCFGPARAMS;

/**
 *******************************************************************************
 * \brief Interrupt related config for this CPU
 *******************************************************************************
 */
Utils_DmaIntrCfg gUtils_dmaSysEdmaIntrCfg;

/**
 *******************************************************************************
 * \brief See utils_dma_edma3cc.h for function description
 *******************************************************************************
 */
UInt32 Utils_edma3GetRegionId(UInt32 edmaInstId)
{
    Uint32 regId = 0;

    if(edmaInstId==UTILS_DMA_SYSTEM_EDMA_INST_ID)
    {
        regId = UTILS_DMA_SYSTEM_DMA_DSP1_REGION;
    }
    else
    if(edmaInstId==UTILS_DMA_LOCAL_EDMA_INST_ID)
    {
        regId = UTILS_DMA_DSP_LOCAL_DMA_REGION;
    }
    else
    {
        regId = 0U;
    }

    return regId;
}

/**
 *******************************************************************************
 * \brief See utils_dma_edma3cc.h for function description
 *******************************************************************************
 */
Bool Utils_edma3IsGblConfigRequired(UInt32 edmaInstId)
{
    (void)edmaInstId;

    return (Bool)TRUE;
}

/**
 *******************************************************************************
 * \brief See utils_dma_edma3cc.h for function description
 *******************************************************************************
 */
EDMA3_DRV_GblConfigParams *Utils_edma3GetGblCfg  (UInt32 edmaInstId)
{
    EDMA3_DRV_GblConfigParams *cfgPrms = NULL;

    /* check allocation config statically */
    Utils_edma3CheckStaticAllocationConlficts();

    if(edmaInstId==UTILS_DMA_SYSTEM_EDMA_INST_ID)
    {
        cfgPrms = &gUtils_dmaSysEdmaGblCfgParams;
    }
    else
    if(edmaInstId==UTILS_DMA_LOCAL_EDMA_INST_ID)
    {
        cfgPrms = &gUtils_dmaDspLocalEdmaGblCfgParams;
    }
    else
    {
        cfgPrms = NULL;
    }

    return cfgPrms;
}

/**
 *******************************************************************************
 * \brief See utils_dma_edma3cc.h for function description
 *******************************************************************************
 */
EDMA3_DRV_InstanceInitConfig *Utils_edma3GetInstCfg (UInt32 edmaInstId)
{
    EDMA3_DRV_InstanceInitConfig *initCfg = NULL;

    if(edmaInstId==UTILS_DMA_SYSTEM_EDMA_INST_ID)
    {
        initCfg = &gUtils_dmaSysEdmaInstInitConfig;
    }
    else
    if(edmaInstId==UTILS_DMA_LOCAL_EDMA_INST_ID)
    {
        initCfg = &gUtils_dmaDspLocalEdmaInstInitConfig;
    }
    else
    {
        initCfg = NULL;
    }

    return initCfg;
}

/**
 *******************************************************************************
 * \brief See utils_dma_edma3cc.h for function description
 *******************************************************************************
 */
Utils_DmaIntrCfg *Utils_edma3GetIntrCfg (UInt32 edmaInstId)
{
    Utils_DmaIntrCfg *intrCfg = NULL;

    if(edmaInstId==UTILS_DMA_SYSTEM_EDMA_INST_ID)
    {
        gUtils_dmaSysEdmaIntrCfg.ccXferCompCpuInt
            = UTILS_DMA_SYS_EDMA_CCXFER_COMPLETION_INT;

        /* region interrupt used MUST match region returned via
         * Utils_edma3GetRegionId() in this file
         */
        gUtils_dmaSysEdmaIntrCfg.ccXferCompXbarInt
            = UTILS_DMA_XBAR_SYS_EDMA_TPCC_IRQ_REGION0 +
                Utils_edma3GetRegionId(edmaInstId);
            ;

        gUtils_dmaSysEdmaIntrCfg.ccXferCompCtrlModXbarIndex
            = UTILS_DMA_SYS_EDMA_CCXFER_COMPLETION_INT - UTILS_DSP1_XBAR_OFFSET;

        gUtils_dmaSysEdmaIntrCfg.ccErrorCpuInt
            = UTILS_DMA_SYS_EDMA_CCERROR_INT;

        gUtils_dmaSysEdmaIntrCfg.ccErrorXbarInt
            = UTILS_DMA_XBAR_SYS_EDMA_TPCC_IRQ_ERR;

        gUtils_dmaSysEdmaIntrCfg.ccErrorCtrlModXbarIndex
            = UTILS_DMA_SYS_EDMA_CCERROR_INT - UTILS_DSP1_XBAR_OFFSET;

        gUtils_dmaSysEdmaIntrCfg.tc0ErrorCpuInt
            = UTILS_DMA_SYS_EDMA_TC0_ERROR_INT;

        gUtils_dmaSysEdmaIntrCfg.tc0ErrorXbarInt
            = UTILS_DMA_XBAR_SYS_EDMA_TC0_IRQ_ERR;

        gUtils_dmaSysEdmaIntrCfg.tc0ErrorCtrlModXbarIndex
            = UTILS_DMA_SYS_EDMA_TC0_ERROR_INT - UTILS_DSP1_XBAR_OFFSET;

        gUtils_dmaSysEdmaIntrCfg.tc1ErrorCpuInt
            = UTILS_DMA_SYS_EDMA_TC0_ERROR_INT;

        gUtils_dmaSysEdmaIntrCfg.tc1ErrorXbarInt
            = UTILS_DMA_XBAR_SYS_EDMA_TC0_IRQ_ERR;

        gUtils_dmaSysEdmaIntrCfg.tc1ErrorCtrlModXbarIndex
            = UTILS_DMA_SYS_EDMA_TC0_ERROR_INT - UTILS_DSP1_XBAR_OFFSET;

        gUtils_dmaSysEdmaIntrCfg.ccXferCompCpuHwiInt
            = UTILS_DMA_SYS_EDMA_HWI_INT_XFER_COMP;

        gUtils_dmaSysEdmaIntrCfg.ccErrorCpuHwiInt
            = UTILS_DMA_SYS_EDMA_HWI_INT_CC_ERR;

        gUtils_dmaSysEdmaIntrCfg.tc0ErrorCpuHwiInt
            = UTILS_DMA_SYS_EDMA_HWI_INT_TC0_ERR;

        gUtils_dmaSysEdmaIntrCfg.tc1ErrorCpuHwiInt
            = UTILS_DMA_SYS_EDMA_HWI_INT_TC1_ERR;

        intrCfg = &gUtils_dmaSysEdmaIntrCfg;
    }
    else
    /*
     * Interrupt mode not supported for this EDMA instance
     * NOTE: this is SW choice and not a HW limitation
     */
    if(edmaInstId==UTILS_DMA_LOCAL_EDMA_INST_ID)
    {
        intrCfg = NULL;
    }
    else
    {
        intrCfg = NULL;
    }

    return intrCfg;
}
