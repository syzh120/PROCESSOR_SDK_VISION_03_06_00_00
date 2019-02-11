/*
 * edma3_tda2xx_cfg.c
 *
 * EDMA3 Driver Adaptation Configuration File (Soc Specific) for OMAPL138.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
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
 *
*/

#include <ti/sdo/edma3/rm/edma3_rm.h>
#ifdef BUILD_TDA2XX_IPU
#include <ti/sysbios/family/arm/ducati/Core.h> 
#endif
#define NUM_SHADOW_REGIONS                      (8U)

/* Number of EDMA3 controllers present in the system */
#define NUM_EDMA3_INSTANCES         3U

/** Number of PaRAM Sets available                                            */
#define EDMA3_NUM_PARAMSET                              (512U)

/** Number of TCCS available                                                  */
#define EDMA3_NUM_TCC                                   (64U)

/** Number of DMA Channels available                                          */
#define EDMA3_NUM_DMA_CHANNELS                          (64U)

/** Number of QDMA Channels available                                         */
#define EDMA3_NUM_QDMA_CHANNELS                         (8U)

/** Number of Event Queues available                                          */
#define EDMA3_NUM_EVTQUE                                (4U)

/** Number of Transfer Controllers available                                  */
#define EDMA3_NUM_TC                                    (2U)

/** Number of Regions                                                         */
#define EDMA3_NUM_REGIONS                               (8U)

/* EDMA3 configuaration for EVE */

/** Number of PaRAM Sets available                                            */
#define EDMA3_NUM_PARAMSET_EVE                          (64U)

/** Number of TCCS available                                                  */
#define EDMA3_NUM_TCC_EVE                               (16U)

/** Number of DMA Channels available                                          */
#define EDMA3_NUM_DMA_CHANNELS_EVE                      (16U)

/** Number of QDMA Channels available                                         */
#define EDMA3_NUM_QDMA_CHANNELS_EVE                     (8U)

/** Number of Event Queues available                                          */
#define EDMA3_NUM_EVTQUE_EVE                            (2U)

/** Number of Transfer Controllers available                                  */
#define EDMA3_NUM_TC_EVE                                (2U)

/** Number of Regions                                                         */
#define EDMA3_NUM_REGIONS_EVE                           (8U)


/** Interrupt no. for Transfer Completion */
#define EDMA3_CC_XFER_COMPLETION_INT_A15                (66U)
#define EDMA3_CC_XFER_COMPLETION_INT_DSP                (38U)
#define EDMA3_CC_XFER_COMPLETION_INT_IPU_C0             (34U)
#define EDMA3_CC_XFER_COMPLETION_INT_IPU_C1             (33U)
#define EDMA3_CC_XFER_COMPLETION_INT_EVE                (8U)

/** Based on the interrupt number to be mapped define the XBAR instance number */
#define COMPLETION_INT_A15_XBAR_INST_NO                 (29U)
#define COMPLETION_INT_DSP_XBAR_INST_NO                 (7U)
#define COMPLETION_INT_IPU_C0_XBAR_INST_NO              (12U)
#define COMPLETION_INT_IPU_C1_XBAR_INST_NO              (11U)

/** Interrupt no. for CC Error */
#define EDMA3_CC_ERROR_INT_A15                          (67U)
#define EDMA3_CC_ERROR_INT_DSP                          (39U)
#define EDMA3_CC_ERROR_INT_IPU                          (35U)
#define EDMA3_CC_ERROR_INT_EVE                          (23U)

/** Based on the interrupt number to be mapped define the XBAR instance number */
#define CC_ERROR_INT_A15_XBAR_INST_NO                   (30U)
#define CC_ERROR_INT_DSP_XBAR_INST_NO                   (8U)
#define CC_ERROR_INT_IPU_XBAR_INST_NO                   (13U)

/** Interrupt no. for TCs Error */
#define EDMA3_TC0_ERROR_INT_A15                         (68U)
#define EDMA3_TC0_ERROR_INT_DSP                         (40U)
#define EDMA3_TC0_ERROR_INT_IPU                         (36U)
#define EDMA3_TC0_ERROR_INT_EVE                         (24U)
#define EDMA3_TC1_ERROR_INT_A15                         (69U)
#define EDMA3_TC1_ERROR_INT_DSP                         (41U)
#define EDMA3_TC1_ERROR_INT_IPU                         (37U)
#define EDMA3_TC1_ERROR_INT_EVE                         (25U)

/** Based on the interrupt number to be mapped define the XBAR instance number */
#define TC0_ERROR_INT_A15_XBAR_INST_NO                  (31U)
#define TC0_ERROR_INT_DSP_XBAR_INST_NO                  (9U) 
#define TC0_ERROR_INT_IPU_XBAR_INST_NO                  (14U)
#define TC1_ERROR_INT_A15_XBAR_INST_NO                  (32U)
#define TC1_ERROR_INT_DSP_XBAR_INST_NO                  (10U)
#define TC1_ERROR_INT_IPU_XBAR_INST_NO                  (15U)

#ifdef BUILD_TDA2XX_MPU
#define EDMA3_CC_XFER_COMPLETION_INT                    (EDMA3_CC_XFER_COMPLETION_INT_A15)
#define EDMA3_CC_ERROR_INT                              (EDMA3_CC_ERROR_INT_A15)
#define CC_ERROR_INT_XBAR_INST_NO                       (CC_ERROR_INT_A15_XBAR_INST_NO)
#define EDMA3_TC0_ERROR_INT                             (EDMA3_TC0_ERROR_INT_A15)
#define EDMA3_TC1_ERROR_INT                             (EDMA3_TC1_ERROR_INT_A15)
#define TC0_ERROR_INT_XBAR_INST_NO                      (TC0_ERROR_INT_A15_XBAR_INST_NO)
#define TC1_ERROR_INT_XBAR_INST_NO                      (TC1_ERROR_INT_A15_XBAR_INST_NO)

#elif defined BUILD_TDA2XX_DSP
#define EDMA3_CC_XFER_COMPLETION_INT                    (EDMA3_CC_XFER_COMPLETION_INT_DSP)
#define EDMA3_CC_ERROR_INT                              (EDMA3_CC_ERROR_INT_DSP)
#define CC_ERROR_INT_XBAR_INST_NO                       (CC_ERROR_INT_DSP_XBAR_INST_NO)
#define EDMA3_TC0_ERROR_INT                             (EDMA3_TC0_ERROR_INT_DSP)
#define EDMA3_TC1_ERROR_INT                             (EDMA3_TC1_ERROR_INT_DSP)
#define TC0_ERROR_INT_XBAR_INST_NO                      (TC0_ERROR_INT_DSP_XBAR_INST_NO)
#define TC1_ERROR_INT_XBAR_INST_NO                      (TC1_ERROR_INT_DSP_XBAR_INST_NO)

#elif defined BUILD_TDA2XX_IPU
#define EDMA3_CC_XFER_COMPLETION_INT                    (EDMA3_CC_XFER_COMPLETION_INT_IPU_C0)
#define EDMA3_CC_ERROR_INT                              (EDMA3_CC_ERROR_INT_IPU)
#define CC_ERROR_INT_XBAR_INST_NO                       (CC_ERROR_INT_IPU_XBAR_INST_NO)
#define EDMA3_TC0_ERROR_INT                             (EDMA3_TC0_ERROR_INT_IPU)
#define EDMA3_TC1_ERROR_INT                             (EDMA3_TC1_ERROR_INT_IPU)
#define TC0_ERROR_INT_XBAR_INST_NO                      (TC0_ERROR_INT_IPU_XBAR_INST_NO)
#define TC1_ERROR_INT_XBAR_INST_NO                      (TC1_ERROR_INT_IPU_XBAR_INST_NO)

#elif defined BUILD_TDA2XX_EVE
#define EDMA3_CC_XFER_COMPLETION_INT                    (EDMA3_CC_XFER_COMPLETION_INT_EVE)
#define EDMA3_CC_ERROR_INT                              (EDMA3_CC_ERROR_INT_EVE)
#define EDMA3_TC0_ERROR_INT                             (EDMA3_TC0_ERROR_INT_EVE)
#define EDMA3_TC1_ERROR_INT                             (EDMA3_TC1_ERROR_INT_EVE)
/* For accessing EVE internal edma, there is no need to configure Xbar */
#define CC_ERROR_INT_XBAR_INST_NO                       (0U)
#define TC0_ERROR_INT_XBAR_INST_NO                      (0U)
#define TC1_ERROR_INT_XBAR_INST_NO                      (0U)

#else
#define EDMA3_CC_XFER_COMPLETION_INT                    (0U)
#define EDMA3_CC_ERROR_INT                              (0U)
#define CC_ERROR_INT_XBAR_INST_NO                       (0U)
#define EDMA3_TC0_ERROR_INT                             (0U)
#define EDMA3_TC1_ERROR_INT                             (0U)
#define TC0_ERROR_INT_XBAR_INST_NO                      (TC0_ERROR_INT_A15_XBAR_INST_NO)
#define TC1_ERROR_INT_XBAR_INST_NO                      (TC1_ERROR_INT_A15_XBAR_INST_NO)
#endif

#define EDMA3_TC2_ERROR_INT                             (0U)
#define EDMA3_TC3_ERROR_INT                             (0U)
#define EDMA3_TC4_ERROR_INT                             (0U)
#define EDMA3_TC5_ERROR_INT                             (0U)
#define EDMA3_TC6_ERROR_INT                             (0U)
#define EDMA3_TC7_ERROR_INT                             (0U)

#define DSP1_EDMA3_CC_XFER_COMPLETION_INT               (19U)
#define DSP2_EDMA3_CC_XFER_COMPLETION_INT               (20U)
#define DSP1_EDMA3_CC_ERROR_INT                         (27U)
#define DSP1_EDMA3_TC0_ERROR_INT                        (28U)
#define DSP1_EDMA3_TC1_ERROR_INT                        (29U)

/** XBAR interrupt source index numbers for EDMA interrupts */
#define XBAR_EDMA_TPCC_IRQ_REGION0                      (361U)
#define XBAR_EDMA_TPCC_IRQ_REGION1                      (362U)
#define XBAR_EDMA_TPCC_IRQ_REGION2                      (363U)
#define XBAR_EDMA_TPCC_IRQ_REGION3                      (364U)
#define XBAR_EDMA_TPCC_IRQ_REGION4                      (365U)
#define XBAR_EDMA_TPCC_IRQ_REGION5                      (366U)
#define XBAR_EDMA_TPCC_IRQ_REGION6                      (367U)
#define XBAR_EDMA_TPCC_IRQ_REGION7                      (368U)

#define XBAR_EDMA_TPCC_IRQ_ERR                          (359U)
#define XBAR_EDMA_TC0_IRQ_ERR                           (370U)
#define XBAR_EDMA_TC1_IRQ_ERR                           (371U)

/**
 * EDMA3 interrupts (transfer completion, CC error etc.) correspond to different
 * ECM events (SoC specific). These ECM events come
 * under ECM block XXX (handling those specific ECM events). Normally, block
 * 0 handles events 4-31 (events 0-3 are reserved), block 1 handles events
 * 32-63 and so on. This ECM block XXX (or interrupt selection number XXX)
 * is mapped to a specific HWI_INT YYY in the tcf file.
 * Define EDMA3_HWI_INT_XFER_COMP to specific HWI_INT, corresponding
 * to transfer completion interrupt.
 * Define EDMA3_HWI_INT_CC_ERR to specific HWI_INT, corresponding
 * to CC error interrupts.
 * Define EDMA3_HWI_INT_TC_ERR to specific HWI_INT, corresponding
 * to TC error interrupts.
 */
/* EDMA 0 */

#define EDMA3_HWI_INT_XFER_COMP                           (7U)
#define EDMA3_HWI_INT_CC_ERR                              (7U)
#define EDMA3_HWI_INT_TC0_ERR                             (10U)
#define EDMA3_HWI_INT_TC1_ERR                             (10U)
#define EDMA3_HWI_INT_TC2_ERR                             (10U)
#define EDMA3_HWI_INT_TC3_ERR                             (10U)

/**
 * \brief Mapping of DMA channels 0-31 to Hardware Events from
 * various peripherals, which use EDMA for data transfer.
 * All channels need not be mapped, some can be free also.
 * 1: Mapped
 * 0: Not mapped (channel available)
 *
 * This mapping will be used to allocate DMA channels when user passes
 * EDMA3_RM_DMA_CHANNEL_ANY as dma channel id (for eg to do memory-to-memory
 * copy). The same mapping is used to allocate the TCC when user passes
 * EDMA3_RM_TCC_ANY as tcc id (for eg to do memory-to-memory copy).
 *
 * To allocate more DMA channels or TCCs, one has to modify the event mapping.
 */
                                                      /* 31     0 */
#define EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_SYSTEDMA       (0x3FC0C06EU)  /* TBD */
#define EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_DSPEDMA        (0x000FFFFFU)  /* TBD */
#define EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_EVEEDMA        (0x00000000U)  /* TBD */

/**
 * \brief Mapping of DMA channels 32-63 to Hardware Events from
 * various peripherals, which use EDMA for data transfer.
 * All channels need not be mapped, some can be free also.
 * 1: Mapped
 * 0: Not mapped (channel available)
 *
 * This mapping will be used to allocate DMA channels when user passes
 * EDMA3_RM_DMA_CHANNEL_ANY as dma channel id (for eg to do memory-to-memory
 * copy). The same mapping is used to allocate the TCC when user passes
 * EDMA3_RM_TCC_ANY as tcc id (for eg to do memory-to-memory copy).
 *
 * To allocate more DMA channels or TCCs, one has to modify the event mapping.
 */
#define EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_SYSTEDMA       (0xF3FFFFFCU) /* TBD */
#define EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_DSPEDMA        (0x00000000U) /* TBD */
#define EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_EVEEDMA        (0x00000000U) /* TBD */




/**
 * \brief Base address as seen from the different cores may be different
 * And is defined based on the core
 */
#if ((defined BUILD_TDA2XX_MPU) || (defined BUILD_TDA2XX_DSP))
#define EDMA3_CC_BASE_ADDR                          ((void *)(0x43300000))
#define EDMA3_TC0_BASE_ADDR                         ((void *)(0x43400000))
#define EDMA3_TC1_BASE_ADDR                         ((void *)(0x43500000))
#elif (defined BUILD_TDA2XX_IPU)
#define EDMA3_CC_BASE_ADDR                          ((void *)(0x63300000))
#define EDMA3_TC0_BASE_ADDR                         ((void *)(0x63400000))
#define EDMA3_TC1_BASE_ADDR                         ((void *)(0x63500000))
#elif (defined BUILD_TDA2XX_EVE)
#define EDMA3_CC_BASE_ADDR                          ((void *)(0x400A0000))
#define EDMA3_TC0_BASE_ADDR                         ((void *)(0x40086000))
#define EDMA3_TC1_BASE_ADDR                         ((void *)(0x40087000))
#else
#define EDMA3_CC_BASE_ADDR                          ((void *)(0x0))
#define EDMA3_TC0_BASE_ADDR                         ((void *)(0x0))
#define EDMA3_TC1_BASE_ADDR                         ((void *)(0x0))
#endif

#define DSP1_EDMA3_CC_BASE_ADDR                     ((void *)(0x01D10000))
#define DSP1_EDMA3_TC0_BASE_ADDR                    ((void *)(0x01D05000))
#define DSP1_EDMA3_TC1_BASE_ADDR                    ((void *)(0x01D06000))

/* Driver Object Initialization Configuration */
EDMA3_RM_GblConfigParams edma3GblCfgParams [NUM_EDMA3_INSTANCES] =
{
    {
        /* EDMA3 INSTANCE# 0 */
        /** Total number of DMA Channels supported by the EDMA3 Controller    */
        EDMA3_NUM_DMA_CHANNELS,
        /** Total number of QDMA Channels supported by the EDMA3 Controller   */
        EDMA3_NUM_QDMA_CHANNELS,
        /** Total number of TCCs supported by the EDMA3 Controller            */
        EDMA3_NUM_TCC,
        /** Total number of PaRAM Sets supported by the EDMA3 Controller      */
        EDMA3_NUM_PARAMSET,
        /** Total number of Event Queues in the EDMA3 Controller              */
        EDMA3_NUM_EVTQUE,
        /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller*/
        EDMA3_NUM_TC,
        /** Number of Regions on this EDMA3 controller                        */
        EDMA3_NUM_REGIONS,

        /**
         * \brief Channel mapping existence
         * A value of 0 (No channel mapping) implies that there is fixed association
         * for a channel number to a parameter entry number or, in other words,
         * PaRAM entry n corresponds to channel n.
         */
        1U,

        /** Existence of memory protection feature */
        0U,

        /** Global Register Region of CC Registers */
        EDMA3_CC_BASE_ADDR,
        /** Transfer Controller (TC) Registers */
        {
	        EDMA3_TC0_BASE_ADDR,
	        EDMA3_TC1_BASE_ADDR,
	        (void *)NULL,
	        (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL
        },
        /** Interrupt no. for Transfer Completion */
        EDMA3_CC_XFER_COMPLETION_INT,
        /** Interrupt no. for CC Error */
        EDMA3_CC_ERROR_INT,
        /** Interrupt no. for TCs Error */
        {
            EDMA3_TC0_ERROR_INT,
            EDMA3_TC1_ERROR_INT,
            EDMA3_TC2_ERROR_INT,
            EDMA3_TC3_ERROR_INT,
            EDMA3_TC4_ERROR_INT,
            EDMA3_TC5_ERROR_INT,
            EDMA3_TC6_ERROR_INT,
            EDMA3_TC7_ERROR_INT
        },

        /**
         * \brief EDMA3 TC priority setting
         *
         * User can program the priority of the Event Queues
         * at a system-wide level.  This means that the user can set the
         * priority of an IO initiated by either of the TCs (Transfer Controllers)
         * relative to IO initiated by the other bus masters on the
         * device (ARM, DSP, USB, etc)
         */
        {
            0U,
            1U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
        },
        /**
         * \brief To Configure the Threshold level of number of events
         * that can be queued up in the Event queues. EDMA3CC error register
         * (CCERR) will indicate whether or not at any instant of time the
         * number of events queued up in any of the event queues exceeds
         * or equals the threshold/watermark value that is set
         * in the queue watermark threshold register (QWMTHRA).
         */
        {
            16U,
            16U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
        },

        /**
         * \brief To Configure the Default Burst Size (DBS) of TCs.
         * An optimally-sized command is defined by the transfer controller
         * default burst size (DBS). Different TCs can have different
         * DBS values. It is defined in Bytes.
         */
            {
            16U,
            16U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
            },

        /**
         * \brief Mapping from each DMA channel to a Parameter RAM set,
         * if it exists, otherwise of no use.
         */
            {
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP
			},

         /**
          * \brief Mapping from each DMA channel to a TCC. This specific
          * TCC code will be returned when the transfer is completed
          * on the mapped channel.
          */
            {
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
            },

        /**
         * \brief Mapping of DMA channels to Hardware Events from
         * various peripherals, which use EDMA for data transfer.
         * All channels need not be mapped, some can be free also.
         */
            {
            EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_SYSTEDMA,
            EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_SYSTEDMA
            }
        },
    {
        /* EDMA3 INSTANCE# 1 */
        /** Total number of DMA Channels supported by the EDMA3 Controller    */
        EDMA3_NUM_DMA_CHANNELS,
        /** Total number of QDMA Channels supported by the EDMA3 Controller   */
        EDMA3_NUM_QDMA_CHANNELS,
        /** Total number of TCCs supported by the EDMA3 Controller            */
        EDMA3_NUM_TCC,
        /** Total number of PaRAM Sets supported by the EDMA3 Controller      */
        EDMA3_NUM_PARAMSET,
        /** Total number of Event Queues in the EDMA3 Controller              */
        EDMA3_NUM_EVTQUE,
        /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller*/
        EDMA3_NUM_TC,
        /** Number of Regions on this EDMA3 controller                        */
        EDMA3_NUM_REGIONS,

        /**
         * \brief Channel mapping existence
         * A value of 0 (No channel mapping) implies that there is fixed association
         * for a channel number to a parameter entry number or, in other words,
         * PaRAM entry n corresponds to channel n.
         */
        1U,

        /** Existence of memory protection feature */
        0U,

        /** Global Register Region of CC Registers */
        DSP1_EDMA3_CC_BASE_ADDR,
        /** Transfer Controller (TC) Registers */
        {
	        DSP1_EDMA3_TC0_BASE_ADDR,
	        DSP1_EDMA3_TC1_BASE_ADDR,
	        (void *)NULL,
	        (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL
        },
        /** Interrupt no. for Transfer Completion */
        DSP1_EDMA3_CC_XFER_COMPLETION_INT,
        /** Interrupt no. for CC Error */
        DSP1_EDMA3_CC_ERROR_INT,
        /** Interrupt no. for TCs Error */
        {
            DSP1_EDMA3_TC0_ERROR_INT,
            DSP1_EDMA3_TC1_ERROR_INT,
            EDMA3_TC2_ERROR_INT,
            EDMA3_TC3_ERROR_INT,
            EDMA3_TC4_ERROR_INT,
            EDMA3_TC5_ERROR_INT,
            EDMA3_TC6_ERROR_INT,
            EDMA3_TC7_ERROR_INT
        },

        /**
         * \brief EDMA3 TC priority setting
         *
         * User can program the priority of the Event Queues
         * at a system-wide level.  This means that the user can set the
         * priority of an IO initiated by either of the TCs (Transfer Controllers)
         * relative to IO initiated by the other bus masters on the
         * device (ARM, DSP, USB, etc)
         */
        {
            0U,
            1U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
        },
        /**
         * \brief To Configure the Threshold level of number of events
         * that can be queued up in the Event queues. EDMA3CC error register
         * (CCERR) will indicate whether or not at any instant of time the
         * number of events queued up in any of the event queues exceeds
         * or equals the threshold/watermark value that is set
         * in the queue watermark threshold register (QWMTHRA).
         */
        {
            16U,
            16U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
        },

        /**
         * \brief To Configure the Default Burst Size (DBS) of TCs.
         * An optimally-sized command is defined by the transfer controller
         * default burst size (DBS). Different TCs can have different
         * DBS values. It is defined in Bytes.
         */
            {
            16U,
            16U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
            },

        /**
         * \brief Mapping from each DMA channel to a Parameter RAM set,
         * if it exists, otherwise of no use.
         */
            {
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP
            },

         /**
          * \brief Mapping from each DMA channel to a TCC. This specific
          * TCC code will be returned when the transfer is completed
          * on the mapped channel.
          */
            {
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
            },

        /**
         * \brief Mapping of DMA channels to Hardware Events from
         * various peripherals, which use EDMA for data transfer.
         * All channels need not be mapped, some can be free also.
         */
            {
            EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_DSPEDMA,
            EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_DSPEDMA
            }
    },
    {
        /* EDMA3 INSTANCE# 2 */
        /** Total number of DMA Channels supported by the EDMA3 Controller    */
        EDMA3_NUM_DMA_CHANNELS_EVE,
        /** Total number of QDMA Channels supported by the EDMA3 Controller   */
        EDMA3_NUM_QDMA_CHANNELS_EVE,
        /** Total number of TCCs supported by the EDMA3 Controller            */
        EDMA3_NUM_TCC_EVE,
        /** Total number of PaRAM Sets supported by the EDMA3 Controller      */
        EDMA3_NUM_PARAMSET_EVE,
        /** Total number of Event Queues in the EDMA3 Controller              */
        EDMA3_NUM_EVTQUE_EVE,
        /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller*/
        EDMA3_NUM_TC_EVE,
        /** Number of Regions on this EDMA3 controller                        */
        EDMA3_NUM_REGIONS_EVE,

        /**
         * \brief Channel mapping existence
         * A value of 0 (No channel mapping) implies that there is fixed association
         * for a channel number to a parameter entry number or, in other words,
         * PaRAM entry n corresponds to channel n.
         */
        1U,

        /** Existence of memory protection feature */
        0U,

        /** Global Register Region of CC Registers */
        EDMA3_CC_BASE_ADDR,
        /** Transfer Controller (TC) Registers */
        {
	        EDMA3_TC0_BASE_ADDR,
	        EDMA3_TC1_BASE_ADDR,
	        (void *)NULL,
	        (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL
        },
        /** Interrupt no. for Transfer Completion */
        EDMA3_CC_XFER_COMPLETION_INT,
        /** Interrupt no. for CC Error */
        EDMA3_CC_ERROR_INT,
        /** Interrupt no. for TCs Error */
        {
            EDMA3_TC0_ERROR_INT,
            EDMA3_TC1_ERROR_INT,
            EDMA3_TC2_ERROR_INT,
            EDMA3_TC3_ERROR_INT,
            EDMA3_TC4_ERROR_INT,
            EDMA3_TC5_ERROR_INT,
            EDMA3_TC6_ERROR_INT,
            EDMA3_TC7_ERROR_INT
        },

        /**
         * \brief EDMA3 TC priority setting
         *
         * User can program the priority of the Event Queues
         * at a system-wide level.  This means that the user can set the
         * priority of an IO initiated by either of the TCs (Transfer Controllers)
         * relative to IO initiated by the other bus masters on the
         * device (ARM, DSP, USB, etc)
         */
        {
            0U,
            1U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
        },
        /**
         * \brief To Configure the Threshold level of number of events
         * that can be queued up in the Event queues. EDMA3CC error register
         * (CCERR) will indicate whether or not at any instant of time the
         * number of events queued up in any of the event queues exceeds
         * or equals the threshold/watermark value that is set
         * in the queue watermark threshold register (QWMTHRA).
         */
        {
            16U,
            16U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
        },

        /**
         * \brief To Configure the Default Burst Size (DBS) of TCs.
         * An optimally-sized command is defined by the transfer controller
         * default burst size (DBS). Different TCs can have different
         * DBS values. It is defined in Bytes.
         */
            {
            16U,
            16U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
            },

        /**
         * \brief Mapping from each DMA channel to a Parameter RAM set,
         * if it exists, otherwise of no use.
         */
            {
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
			EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP
            },

         /**
          * \brief Mapping from each DMA channel to a TCC. This specific
          * TCC code will be returned when the transfer is completed
          * on the mapped channel.
          */
            {
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
			EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
            },

        /**
         * \brief Mapping of DMA channels to Hardware Events from
         * various peripherals, which use EDMA for data transfer.
         * All channels need not be mapped, some can be free also.
         */
            {
            EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_EVEEDMA,
            EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_EVEEDMA
            }
    },

};

/**
 * \brief Resource splitting defines for Own/Reserved DMA/QDMA channels and TCCs
 * For PaRAMs explicit defines are not present but should be replaced in the structure sampleInstInitConfig
 * Default configuration has all resources owned by all cores and none reserved except for first 64 PaRAMs corrosponding to DMA channels
 * Resources to be Split properly by application and rebuild the sample library to avoid resource conflict
 *
 * Only Resources owned by a perticular core are allocated by Driver
 * Reserved resources are not allocated if requested for any available resource
 */
 
/* Default RM Instance Initialization Configuration */
EDMA3_RM_InstanceInitConfig defInstInitConfig [NUM_EDMA3_INSTANCES][NUM_SHADOW_REGIONS] =
{
		/* EDMA3 INSTANCE# 0 */
		{
			/* Resources owned/reserved by region 0 (Associated to MPU core 0)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000FFU},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_SYSTEDMA, EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_SYSTEDMA},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00U, 0x00U},
			},

			/* Resources owned/reserved by region 1 (Associated to MPU core 1) */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU},
/* 
 * This instance 0 and region 1 is only accessible to MPU core 1.
 * So other cores should not be access.
 */
#ifdef BUILD_TDA2XX_MPU
				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},
#else
				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
#endif
				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000FFU},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_SYSTEDMA, EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_SYSTEDMA},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00U, 0x00U},
			},

	        /* Resources owned/reserved by region 2 (Associated to any DSP1)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000FFU},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_SYSTEDMA, EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_SYSTEDMA},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00U, 0x00U},
			},

	        /* Resources owned/reserved by region 3 (Associated to any DSP2)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000FFU},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_SYSTEDMA, EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_SYSTEDMA},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00U, 0x00U},
			},

	        /* Resources owned/reserved by region 4 (Associated to any IPU1 core 0)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000FFU},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_SYSTEDMA, EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_SYSTEDMA},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00U, 0x00U},
			},

	        /* Resources owned/reserved by region 5 (Associated to any IPU1 core 1)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000FFU},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_SYSTEDMA, EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_SYSTEDMA},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00U, 0x00U},
			},

	        /* Resources owned/reserved by region 6 (Associated to any IPU2 core 0)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000FFU},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_SYSTEDMA, EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_SYSTEDMA},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00U, 0x00U},
			},

	        /* Resources owned/reserved by region 7 (Associated to any IPU2 core 1)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000FFU},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_SYSTEDMA, EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_SYSTEDMA},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00U, 0x00U},
			},
	    },
		/* EDMA3 INSTANCE# 1 DSP1 EDMA*/
		{
	        /* Resources owned/reserved by region 0 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},

			/* Resources owned/reserved by region 1 (Not Associated to any core supported) */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},

	        /* Resources owned/reserved by region 2 (Associated to any DSP core 0)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000FFU},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_DSPEDMA, EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_DSPEDMA},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00U, 0x00U},
			},

	        /* Resources owned/reserved by region 3 (Associated to any DSP core 1)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000FFU},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_DSPEDMA, EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_DSPEDMA},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00U, 0x00U},
			},

	        /* Resources owned/reserved by region 4 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},

	        /* Resources owned/reserved by region 5 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},

	        /* Resources owned/reserved by region 6 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},

	        /* Resources owned/reserved by region 7 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},
	    },
		/* EDMA3 INSTANCE# 2 EVE EDMA*/
		{
	        /* Resources owned/reserved by region 0 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},

	        /* Resources owned/reserved by region 1 (Associated to any EVE core)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000FFU},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFFFFFFU, 0xFFFFFFFFU},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0_EVEEDMA, EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1_EVEEDMA},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00U, 0x00U},
			},

	        /* Resources owned/reserved by region 2 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},

	        /* Resources owned/reserved by region 3 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},

	        /* Resources owned/reserved by region 4 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},

	        /* Resources owned/reserved by region 5 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},

	        /* Resources owned/reserved by region 6 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},

	        /* Resources owned/reserved by region 7 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000U},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000U, 0x00000000U},
			},
	    },
};

/* Driver Instance Cross bar event to channel map Initialization Configuration */
EDMA3_RM_GblXbarToChanConfigParams defXbarChanInitConfig[NUM_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] =
{
    /* EDMA3 INSTANCE# 0 */
    {
        /* Event to channel map for region 0 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 1 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 2 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 3 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 4 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 5 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 6 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 7 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
    },
    
    /* EDMA3 INSTANCE# 1 */
    {
        /* Event to channel map for region 0 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 1 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 2 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 3 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 4 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 5 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 6 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 7 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
    },
    
    /* EDMA3 INSTANCE# 2 */
    {
        /* Event to channel map for region 0 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 1 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 2 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 3 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 4 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 5 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 6 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
        /* Event to channel map for region 7 */
        {
            {-1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1}
        },
    }
};

/* End of File */



