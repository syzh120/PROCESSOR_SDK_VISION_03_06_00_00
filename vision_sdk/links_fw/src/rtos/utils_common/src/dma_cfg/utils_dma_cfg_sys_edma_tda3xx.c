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
 * \file utils_dma_cfg_sys_edma_tda3xx.c
 *
 * \brief This file has the configuration for System EDMA controller on TDA3xx
 *
 * \version 0.0 (Aug 2013) : [KC] First version
 * \version 0.1 (Dec 2016) : [PYJ] Created separate files for TDA2 and TDA3
 *
 *******************************************************************************
 */

#ifndef UTILS_DMA_CFG_SYS_EDMA_TDA3XX_
#define UTILS_DMA_CFG_SYS_EDMA_TDA3XX_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/src/dma_cfg/utils_dma_edma3cc.h>

/*
 *******************************************************************************
 *
 *   This file in included in
 *   - utils_dma_cfg_ipu1_0.c
 *   - utils_dma_cfg_ipu1_1.c
 *   - utils_dma_cfg_dsp1.c
 *   - utils_dma_cfg_dsp2.c
 *
 *******************************************************************************
 */

/* EDMA3 LLD macro - abbreviated */
#define NO_CHTCC_MAP        (EDMA3_DRV_CH_NO_TCC_MAP)
#define NO_CHPARAM_MAP      (EDMA3_DRV_CH_NO_PARAM_MAP)

/*******************************************************************************
 *  EDMA controller region allocation based on CPU ID
 *
 *  Region ID's MUST be unique across different CPUs
 *
 *  Max number of regions can be 8
 *******************************************************************************
 */
#define UTILS_DMA_SYSTEM_DMA_IPU1_0_REGION      (1U)
#define UTILS_DMA_SYSTEM_DMA_IPU1_1_REGION      (2U)
#define UTILS_DMA_SYSTEM_DMA_DSP1_REGION        (3U)
#define UTILS_DMA_SYSTEM_DMA_DSP2_REGION        (4U)

/*******************************************************************************
 *  IPU1_0 EDMA channel allocation
 *******************************************************************************
 */
#define UTILS_IPU1_0_EDMACH_ALLOC_0     (0x00000000U)
#define UTILS_IPU1_0_EDMACH_ALLOC_1     (0xFFFF0000U)

/*******************************************************************************
 *  IPU1_1 EDMA channel allocation
 *******************************************************************************
 */
#define UTILS_IPU1_1_EDMACH_ALLOC_0     (0x00F00000U)
#define UTILS_IPU1_1_EDMACH_ALLOC_1     (0x00000000U)

/*******************************************************************************
 *  DSP1 EDMA channel allocation
 *******************************************************************************
 */
#define UTILS_DSP1_EDMACH_ALLOC_0     (0x0F000000U)
#define UTILS_DSP1_EDMACH_ALLOC_1     (0x00000000U)

/*******************************************************************************
 *  DSP2 EDMA channel allocation
 *******************************************************************************
 */
#define UTILS_DSP2_EDMACH_ALLOC_0     (0xF0000000U)
#define UTILS_DSP2_EDMACH_ALLOC_1     (0x00000000U)

/*******************************************************************************
 *  IPU1_0 EDMA allocation
 *******************************************************************************
 */
#ifdef NDK_PROC_TO_USE_IPU1_0
#define UTILS_IPU1_0_QDMACH_ALLOC_0     (0x0000000FU) /* required for AVB */
#else
#define UTILS_IPU1_0_QDMACH_ALLOC_0     (0x00000000U)
#endif

#define UTILS_IPU1_0_PARAM_ALLOC_0      (0xFFFFFFFFU)
#define UTILS_IPU1_0_PARAM_ALLOC_1      (0xFFFFFFFFU)
#define UTILS_IPU1_0_PARAM_ALLOC_2      (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_3      (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_4      (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_5      (0x00000000U)

#ifdef NDK_PROC_TO_USE_IPU1_0
#if defined (NSP_TFDTP_INCLUDE) || defined (AVB_INCLUDE)
#define UTILS_IPU1_0_PARAM_ALLOC_6      (0xFFFFFFFFU)/* required for AVB/TFDTP */
#define UTILS_IPU1_0_PARAM_ALLOC_7      (0xFFFFFFFFU)/* required for AVB/TFDTP */
#define UTILS_IPU1_0_PARAM_ALLOC_8      (0xFFFFFFFFU)/* required for AVB/TFDTP */
#define UTILS_IPU1_0_PARAM_ALLOC_9      (0xFFFFFFFFU)/* required for AVB/TFDTP */
#else
#define UTILS_IPU1_0_PARAM_ALLOC_6      (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_7      (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_8      (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_9      (0x00000000U)
#endif
#if defined (NSP_TFDTP_INCLUDE)
#define UTILS_IPU1_0_PARAM_ALLOC_10     (0xFFFFFFFFU) /* required for TFDTP */
#define UTILS_IPU1_0_PARAM_ALLOC_11     (0xFFFFFFFFU) /* required for TFDTP */
#define UTILS_IPU1_0_PARAM_ALLOC_12     (0xFFFFFFFFU) /* required for TFDTP */
#define UTILS_IPU1_0_PARAM_ALLOC_13     (0xFFFFFFFFU) /* required for TFDTP */
#else
#define UTILS_IPU1_0_PARAM_ALLOC_10     (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_11     (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_12     (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_13     (0x00000000U)
#endif
#else
#define UTILS_IPU1_0_PARAM_ALLOC_6      (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_7      (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_8      (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_9      (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_10     (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_11     (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_12     (0x00000000U)
#define UTILS_IPU1_0_PARAM_ALLOC_13     (0x00000000U)
#endif

/*******************************************************************************
 *  IPU1_1 EDMA allocation
 *******************************************************************************
 */
#ifdef NDK_PROC_TO_USE_IPU1_1
#define UTILS_IPU1_1_QDMACH_ALLOC_0     (0x0000000FU) /* required for AVB */
#else
#define UTILS_IPU1_1_QDMACH_ALLOC_0     (0x00000000U)
#endif

#define UTILS_IPU1_1_PARAM_ALLOC_0      (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_1      (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_2      (0x0000FF00U)
#define UTILS_IPU1_1_PARAM_ALLOC_3      (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_4      (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_5      (0x00000000U)
#ifdef NDK_PROC_TO_USE_IPU1_1
#if defined (NSP_TFDTP_INCLUDE) || defined (AVB_INCLUDE)
#define UTILS_IPU1_1_PARAM_ALLOC_6      (0xFFFFFFFFU)/* required for AVB/TFDTP */
#define UTILS_IPU1_1_PARAM_ALLOC_7      (0xFFFFFFFFU)/* required for AVB/TFDTP */
#define UTILS_IPU1_1_PARAM_ALLOC_8      (0xFFFFFFFFU)/* required for AVB/TFDTP */
#define UTILS_IPU1_1_PARAM_ALLOC_9      (0xFFFFFFFFU)/* required for AVB/TFDTP */
#else
#define UTILS_IPU1_1_PARAM_ALLOC_6      (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_7      (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_8      (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_9      (0x00000000U)
#endif
#if defined (NSP_TFDTP_INCLUDE)
#define UTILS_IPU1_1_PARAM_ALLOC_10     (0xFFFFFFFFU) /* required for TFDTP */
#define UTILS_IPU1_1_PARAM_ALLOC_11     (0xFFFFFFFFU) /* required for TFDTP */
#define UTILS_IPU1_1_PARAM_ALLOC_12     (0xFFFFFFFFU) /* required for TFDTP */
#define UTILS_IPU1_1_PARAM_ALLOC_13     (0xFFFFFFFFU) /* required for TFDTP */
#else
#define UTILS_IPU1_1_PARAM_ALLOC_10     (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_11     (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_12     (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_13     (0x00000000U)
#endif
#else
#define UTILS_IPU1_1_PARAM_ALLOC_6      (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_7      (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_8      (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_9      (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_10     (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_11     (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_12     (0x00000000U)
#define UTILS_IPU1_1_PARAM_ALLOC_13     (0x00000000U)
#endif

/*******************************************************************************
 *  DSP1 EDMA allocation
 *******************************************************************************
 */
#define UTILS_DSP1_QDMACH_ALLOC_0     (0x00000000U)

#define UTILS_DSP1_PARAM_ALLOC_0      (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_1      (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_2      (0xFFFF0000U)
#define UTILS_DSP1_PARAM_ALLOC_3      (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_4      (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_5      (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_6      (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_7      (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_8      (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_9      (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_10     (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_11     (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_12     (0x00000000U)
#define UTILS_DSP1_PARAM_ALLOC_13     (0x00000000U)

/*******************************************************************************
 *  DSP2 EDMA allocation
 *******************************************************************************
 */
#define UTILS_DSP2_QDMACH_ALLOC_0     (0x00000000U)

#define UTILS_DSP2_PARAM_ALLOC_0      (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_1      (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_2      (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_3      (0x0000FFFFU)
#define UTILS_DSP2_PARAM_ALLOC_4      (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_5      (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_6      (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_7      (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_8      (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_9      (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_10     (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_11     (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_12     (0x00000000U)
#define UTILS_DSP2_PARAM_ALLOC_13     (0x00000000U)


/**
 *******************************************************************************
 * XBAR interrupt source index numbers for EDMA interrupts
 *******************************************************************************
 */
#define UTILS_DMA_XBAR_SYS_EDMA_TPCC_IRQ_REGION0    (361U)
#define UTILS_DMA_XBAR_SYS_EDMA_TPCC_IRQ_REGION1    (362U)
#define UTILS_DMA_XBAR_SYS_EDMA_TPCC_IRQ_REGION2    (363U)
#define UTILS_DMA_XBAR_SYS_EDMA_TPCC_IRQ_REGION3    (364U)
#define UTILS_DMA_XBAR_SYS_EDMA_TPCC_IRQ_REGION4    (365U)

#define UTILS_DMA_XBAR_SYS_EDMA_TPCC_IRQ_ERR        (359U)
#define UTILS_DMA_XBAR_SYS_EDMA_TC0_IRQ_ERR         (370U)
#define UTILS_DMA_XBAR_SYS_EDMA_TC1_IRQ_ERR         (371U)

/**
 *******************************************************************************
 * \brief System EDMA global information
 *******************************************************************************
 */
/* MISRA.ONEDEFRULE.VAR:MISRAC_2004 Rule_8.5
   MISRAC_WAIVER:
   Tool Issue: Klockwork is wrongly reporting this issue in some of the C files
   */
#define UTILS_DMASYSEDMAGBLCFGPARAMS                                           \
{                                                                              \
    /** Total number of DMA Channels supported by the EDMA3 Controller */      \
    64u,                                                                       \
                                                                               \
    /** Total number of QDMA Channels supported by the EDMA3 Controller */     \
    8u,                                                                        \
                                                                               \
    /** Total number of TCCs supported by the EDMA3 Controller */              \
    64u,                                                                       \
                                                                               \
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */        \
    512u,                                                                      \
                                                                               \
    /** Total number of Event Queues in the EDMA3 Controller */                \
    4u,                                                                        \
                                                                               \
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */  \
    2u,                                                                        \
                                                                               \
    /** Number of Regions on this EDMA3 controller */                          \
    8u,                                                                        \
                                                                               \
    /**                                                                        \
     * Channel mapping existence.                                              \
     * A value of 0 (No channel mapping) implies that there is fixed           \
     * association                                                             \
     * for a channel number to a parameter entry number or, in other words,    \
     * PaRAM entry n corresponds to channel n.                                 \
     */                                                                        \
    1u,                                                                        \
                                                                               \
    /** Existence of memory protection feature */                              \
    1u,                                                                        \
                                                                               \
    /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3                             \
       MISRAC_WAIVER:                                                          \
       Typecasted memory mapped register address to pointer,                   \
       Macro is defined for each core in core specific DMA file.               \
       This macro is non-null. */                                              \
    /** Global Register Region of CC Registers */                              \
    (void *)UTILS_DMA_SYSTEM_DMA_BASE_ADDR,                                    \
                                                                               \
    /** Transfer Controller (TC) Registers */                                  \
    {                                                                          \
        /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3                         \
           MISRAC_WAIVER:                                                      \
           Typecasted memory mapped register address to pointer,               \
           Macro is defined for each core in core specific DMA file.           \
           This macro is non-null. */                                          \
        (void *)(UTILS_DMA_SYSTEM_DMA_BASE_ADDR+0x100000U),                    \
        /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3                         \
           MISRAC_WAIVER:                                                      \
           Typecasted memory mapped register address to pointer,               \
           Macro is defined for each core in core specific DMA file.           \
           This macro is non-null. */                                          \
        (void *)(UTILS_DMA_SYSTEM_DMA_BASE_ADDR+0x200000U),                    \
        (void *)NULL,                                                          \
        (void *)NULL,                                                          \
        (void *)NULL,                                                          \
        (void *)NULL,                                                          \
        (void *)NULL,                                                          \
        (void *)NULL                                                           \
    },                                                                         \
                                                                               \
    /** Interrupt no. for Transfer Completion */                               \
    UTILS_DMA_SYS_EDMA_CCXFER_COMPLETION_INT,                                  \
                                                                               \
    /** Interrupt no. for CC Error */                                          \
    UTILS_DMA_SYS_EDMA_CCERROR_INT,                                            \
                                                                               \
    /** Interrupt no. for TCs Error */                                         \
    {                                                                          \
        UTILS_DMA_SYS_EDMA_TC0_ERROR_INT,                                      \
        UTILS_DMA_SYS_EDMA_TC1_ERROR_INT,                                      \
        UTILS_DMA_SYS_EDMA_TC2_ERROR_INT,                                      \
        UTILS_DMA_SYS_EDMA_TC3_ERROR_INT,                                      \
        UTILS_DMA_SYS_EDMA_TC4_ERROR_INT,                                      \
        UTILS_DMA_SYS_EDMA_TC5_ERROR_INT,                                      \
        UTILS_DMA_SYS_EDMA_TC6_ERROR_INT,                                      \
        UTILS_DMA_SYS_EDMA_TC7_ERROR_INT                                       \
    },                                                                         \
                                                                               \
    /**                                                                        \
     * EDMA3 TC priority setting                                               \
     *                                                                         \
     * User can program the priority of the Event Queues                       \
     * at a system-wide level.  This means that the user can set the           \
     * priority of an IO initiated by either of the TCs (Transfer Controllers) \
     * relative to IO initiated by the other bus masters on the                \
     * device (ARM, DSP, USB, etc)                                             \
     */                                                                        \
    {                                                                          \
        4u,                                                                    \
        4u,                                                                    \
        0u,                                                                    \
        0u,                                                                    \
        0u,                                                                    \
        0u,                                                                    \
        0u,                                                                    \
        0u                                                                     \
    },                                                                         \
                                                                               \
    /**                                                                        \
     * To Configure the Threshold level of number of events                    \
     * that can be queued up in the Event queues. EDMA3CC error register       \
     * (CCERR) will indicate whether or not at any instant of time the         \
     * number of events queued up in any of the event queues exceeds           \
     * or equals the threshold/watermark value that is set                     \
     * in the queue watermark threshold register (QWMTHRA).                    \
     */                                                                        \
    {                                                                          \
        16u,                                                                   \
        16u,                                                                   \
        16u,                                                                   \
        16u,                                                                   \
        0u,                                                                    \
        0u,                                                                    \
        0u,                                                                    \
        0u                                                                     \
    },                                                                         \
                                                                               \
    /**                                                                        \
     * To Configure the Default Burst Size (DBS) of TCs.                       \
     * An optimally-sized command is defined by the transfer controller        \
     * default burst size (DBS). Different TCs can have different              \
     * DBS values. It is defined in Bytes.                                     \
     */                                                                        \
    {                                                                          \
        16u,                                                                   \
        16u,                                                                   \
        0u,                                                                    \
        0u,                                                                    \
        0u,                                                                    \
        0u,                                                                    \
        0u,                                                                    \
        0u                                                                     \
    },                                                                         \
                                                                               \
    /**                                                                        \
     * Mapping from each DMA channel to a Parameter RAM set,                   \
     * if it exists, otherwise of no use.                                      \
     */                                                                        \
    {                                                                          \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
        NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP, NO_CHPARAM_MAP,        \
    },                                                                         \
                                                                               \
     /**                                                                       \
      * Mapping from each DMA channel to a TCC. This specific                  \
      * TCC code will be returned when the transfer is completed               \
      * on the mapped channel.                                                 \
      */                                                                       \
    {                                                                          \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
        NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP, NO_CHTCC_MAP,                \
    },                                                                         \
                                                                               \
                                                                               \
    /**                                                                        \
     * Mapping of DMA channels to Hardware Events from                         \
     * various peripherals, which use EDMA for data transfer.                  \
     * All channels need not be mapped, some can be free also.                 \
     */                                                                        \
    {                                                                          \
        0x00000000u,                                                           \
        0xFF000000u                                                            \
    },                                                                         \
}

/*******************************************************************************
 *  Local Function Declaration
 *******************************************************************************
 */
static inline void Utils_edma3CheckAllocationConlficts(
                        UInt32 maskIpu1_0,
                        UInt32 maskIpu1_1,
                        UInt32 maskDsp1,
                        UInt32 maskDsp2
                        );
static inline void Utils_edma3CheckStaticAllocationConlficts(void);

/**
 *******************************************************************************
 *
 * \brief Utility APIs to detect allocation conflicts given a channel allocation
 *        mask
 *
 * \param maskIpu1_0    [IN] Allocation mask
 * \param maskIpu1_1    [IN] Allocation mask
 * \param maskDsp1      [IN] Allocation mask
 * \param maskDsp2      [IN] Allocation mask
 *
 *******************************************************************************
 */
/* MISRA.ONEDEFRULE.FUNC:MISRAC_2004 Rule_8.5
 * Fix in later release -> Case by case
 * Waiver for static inline functions defined in header file doing init of
 * interface structure and small functions for performance reasons
 */
static inline void Utils_edma3CheckAllocationConlficts(
                        UInt32 maskIpu1_0,
                        UInt32 maskIpu1_1,
                        UInt32 maskDsp1,
                        UInt32 maskDsp2
                        )
{
    UInt32 mask[16];
    UInt32 numMask = 0;

    mask[numMask] = maskIpu1_0 & maskIpu1_1;
    numMask++;
    UTILS_assert(numMask <= UTILS_ARRAYSIZE(mask));

    mask[numMask] = maskIpu1_0 & maskDsp1;
    numMask++;
    UTILS_assert(numMask <= UTILS_ARRAYSIZE(mask));

    mask[numMask] = maskIpu1_0 & maskDsp2;
    numMask++;
    UTILS_assert(numMask <= UTILS_ARRAYSIZE(mask));

    mask[numMask] = maskIpu1_1 & maskDsp1;
    numMask++;
    UTILS_assert(numMask <= UTILS_ARRAYSIZE(mask));

    mask[numMask] = maskIpu1_1 & maskDsp2;
    numMask++;
    UTILS_assert(numMask <= UTILS_ARRAYSIZE(mask));

    mask[numMask] = maskDsp1   & maskDsp2;
    numMask++;
    UTILS_assert(numMask <= UTILS_ARRAYSIZE(mask));

    while(numMask--)
    {
        if(0U != mask[numMask])
        {
            Vps_printf(
             " #### ERROR: UTILS: DMA: Conflict in EDMA static allocation !!!\n"
             " ####        Check static EDMA allocation and try again.\n"
             " ####        See file %s\n", __FILE__
            );
            UTILS_assert((Bool)FALSE);
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief Utility APIs to detect EDMA CH/PaRAM allocation conflicts across
 *        processor's
 *
 *******************************************************************************
 */
/* MISRA.ONEDEFRULE.FUNC:MISRAC_2004 Rule_8.5
 * Fix in later release -> Case by case
 * Waiver for static inline functions defined in header file doing init of
 * interface structure and small functions for performance reasons
 */
static inline void Utils_edma3CheckStaticAllocationConlficts(void)
{
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_QDMACH_ALLOC_0,
        UTILS_IPU1_1_QDMACH_ALLOC_0,
        UTILS_DSP1_QDMACH_ALLOC_0,
        UTILS_DSP2_QDMACH_ALLOC_0
        );

    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_EDMACH_ALLOC_1,
        UTILS_IPU1_1_EDMACH_ALLOC_1,
        UTILS_DSP1_EDMACH_ALLOC_1,
        UTILS_DSP2_EDMACH_ALLOC_1
        );

    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_0,
        UTILS_IPU1_1_PARAM_ALLOC_0,
        UTILS_DSP1_PARAM_ALLOC_0,
        UTILS_DSP2_PARAM_ALLOC_0
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_1,
        UTILS_IPU1_1_PARAM_ALLOC_1,
        UTILS_DSP1_PARAM_ALLOC_1,
        UTILS_DSP2_PARAM_ALLOC_1
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_2,
        UTILS_IPU1_1_PARAM_ALLOC_2,
        UTILS_DSP1_PARAM_ALLOC_2,
        UTILS_DSP2_PARAM_ALLOC_2
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_3,
        UTILS_IPU1_1_PARAM_ALLOC_3,
        UTILS_DSP1_PARAM_ALLOC_3,
        UTILS_DSP2_PARAM_ALLOC_3
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_4,
        UTILS_IPU1_1_PARAM_ALLOC_4,
        UTILS_DSP1_PARAM_ALLOC_4,
        UTILS_DSP2_PARAM_ALLOC_4
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_5,
        UTILS_IPU1_1_PARAM_ALLOC_5,
        UTILS_DSP1_PARAM_ALLOC_5,
        UTILS_DSP2_PARAM_ALLOC_5
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_6,
        UTILS_IPU1_1_PARAM_ALLOC_6,
        UTILS_DSP1_PARAM_ALLOC_6,
        UTILS_DSP2_PARAM_ALLOC_6
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_7,
        UTILS_IPU1_1_PARAM_ALLOC_7,
        UTILS_DSP1_PARAM_ALLOC_7,
        UTILS_DSP2_PARAM_ALLOC_7
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_8,
        UTILS_IPU1_1_PARAM_ALLOC_8,
        UTILS_DSP1_PARAM_ALLOC_8,
        UTILS_DSP2_PARAM_ALLOC_8
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_9,
        UTILS_IPU1_1_PARAM_ALLOC_9,
        UTILS_DSP1_PARAM_ALLOC_9,
        UTILS_DSP2_PARAM_ALLOC_9
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_10,
        UTILS_IPU1_1_PARAM_ALLOC_10,
        UTILS_DSP1_PARAM_ALLOC_10,
        UTILS_DSP2_PARAM_ALLOC_10
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_11,
        UTILS_IPU1_1_PARAM_ALLOC_11,
        UTILS_DSP1_PARAM_ALLOC_11,
        UTILS_DSP2_PARAM_ALLOC_11
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_12,
        UTILS_IPU1_1_PARAM_ALLOC_12,
        UTILS_DSP1_PARAM_ALLOC_12,
        UTILS_DSP2_PARAM_ALLOC_12
        );
    Utils_edma3CheckAllocationConlficts(
        UTILS_IPU1_0_PARAM_ALLOC_13,
        UTILS_IPU1_1_PARAM_ALLOC_13,
        UTILS_DSP1_PARAM_ALLOC_13,
        UTILS_DSP2_PARAM_ALLOC_13
        );
}

#endif /* UTILS_DMA_CFG_SYS_EDMA_TDA3XX_*/

