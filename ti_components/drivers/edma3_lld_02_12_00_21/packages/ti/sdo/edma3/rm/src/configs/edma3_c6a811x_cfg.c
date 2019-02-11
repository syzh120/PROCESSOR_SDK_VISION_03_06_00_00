/*
 * edma3_c6a811x_cfg.c
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

/* Number of EDMA3 controllers present in the system */
#define NUM_EDMA3_INSTANCES         1u

/**
 * \brief Mapping of DMA channels 0-31 to Hardware Events from
 * various peripherals, which use EDMA for data transfer.
 * All channels need not be mapped, some can be free also.
 * 1: Mapped
 * 0: Not mapped
 *
 * This mapping will be used to allocate DMA channels when user passes
 * EDMA3_RM_DMA_CHANNEL_ANY as dma channel id (for eg to do memory-to-memory
 * copy). The same mapping is used to allocate the TCC when user passes
 * EDMA3_RM_TCC_ANY as tcc id (for eg to do memory-to-memory copy).
 *
 * To allocate more DMA channels or TCCs, one has to modify the event mapping.
 */
/* EDMA3 0 */
                                                /* 31     0 */
#define EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0        (0xFCFF3F0Cu)	/* TBD */

/**
 * \brief Mapping of DMA channels 32-63 to Hardware Events from
 * various peripherals, which use EDMA for data transfer.
 * All channels need not be mapped, some can be free also.
 * 1: Mapped
 * 0: Not mapped
 *
 * This mapping will be used to allocate DMA channels when user passes
 * EDMA3_RM_DMA_CHANNEL_ANY as dma channel id (for eg to do memory-to-memory
 * copy). The same mapping is used to allocate the TCC when user passes
 * EDMA3_RM_TCC_ANY as tcc id (for eg to do memory-to-memory copy).
 *
 * To allocate more DMA channels or TCCs, one has to modify the event mapping.
 */
#define EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1        (0xFF003C00u)    /* TBD */

/** Number of PaRAM Sets available                                            */
#define EDMA3_NUM_PARAMSET                              (512u)

/** Number of TCCS available                                                  */
#define EDMA3_NUM_TCC                                   (64u)

/** Number of DMA Channels available                                          */
#define EDMA3_NUM_DMA_CHANNELS                          (64u)

/** Number of QDMA Channels available                                         */
#define EDMA3_NUM_QDMA_CHANNELS                         (8u)

/** Number of Event Queues available                                          */
#define EDMA3_NUM_EVTQUE                              (4u)

/** Number of Transfer Controllers available                                  */
#define EDMA3_NUM_TC                                  (4u)

/** Number of Regions                                                         */
#define EDMA3_NUM_REGIONS                             (6u)


/** Interrupt no. for Transfer Completion                                     */
#define EDMA3_CC_XFER_COMPLETION_INT_A8                 (12u)
#define EDMA3_CC_XFER_COMPLETION_INT_DSP                (20u)
#define EDMA3_CC_XFER_COMPLETION_INT_M3VPSS             (63u)
#define EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO            (62u)

#ifdef BUILD_C6A811X_A8
#define EDMA3_CC_XFER_COMPLETION_INT                    EDMA3_CC_XFER_COMPLETION_INT_A8
#elif defined BUILD_C6A811X_DSP
#define EDMA3_CC_XFER_COMPLETION_INT                    EDMA3_CC_XFER_COMPLETION_INT_DSP
#elif defined BUILD_C6A811X_M3VIDEO
#define EDMA3_CC_XFER_COMPLETION_INT                    EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO
#elif defined BUILD_C6A811X_M3VPSS
#define EDMA3_CC_XFER_COMPLETION_INT                    EDMA3_CC_XFER_COMPLETION_INT_M3VPSS
#else
#define EDMA3_CC_XFER_COMPLETION_INT                    (0u)
#endif

/** Interrupt no. for CC Error                                                */
#define EDMA3_CC_ERROR_INT_A8                           (14u)
#define EDMA3_CC_ERROR_INT_DSP                          (21u)

#ifdef BUILD_C6A811X_A8
#define EDMA3_CC_ERROR_INT                              EDMA3_CC_ERROR_INT_A8
#elif defined BUILD_C6A811X_DSP
#define EDMA3_CC_ERROR_INT                              EDMA3_CC_ERROR_INT_DSP
#else
#define EDMA3_CC_ERROR_INT                              (0u)
#endif

/** Interrupt no. for TCs Error                                               */
#define EDMA3_TC0_ERROR_INT_DSP                         (22u)
#define EDMA3_TC1_ERROR_INT_DSP                         (27u)
#define EDMA3_TC2_ERROR_INT_DSP                         (28u)
#define EDMA3_TC3_ERROR_INT_DSP                         (29u)
#define EDMA3_TC0_ERROR_INT_A8                          (112u)
#define EDMA3_TC1_ERROR_INT_A8                          (113u)
#define EDMA3_TC2_ERROR_INT_A8                          (114u)
#define EDMA3_TC3_ERROR_INT_A8                          (115u)

#ifdef BUILD_C6A811X_A8
#define EDMA3_TC0_ERROR_INT                             EDMA3_TC0_ERROR_INT_A8
#define EDMA3_TC1_ERROR_INT                             EDMA3_TC1_ERROR_INT_A8
#define EDMA3_TC2_ERROR_INT                             EDMA3_TC2_ERROR_INT_A8
#define EDMA3_TC3_ERROR_INT                             EDMA3_TC3_ERROR_INT_A8
#elif defined BUILD_C6A811X_DSP
#define EDMA3_TC0_ERROR_INT                             EDMA3_TC0_ERROR_INT_DSP
#define EDMA3_TC1_ERROR_INT                             EDMA3_TC1_ERROR_INT_DSP
#define EDMA3_TC2_ERROR_INT                             EDMA3_TC2_ERROR_INT_DSP
#define EDMA3_TC3_ERROR_INT                             EDMA3_TC3_ERROR_INT_DSP
#else
#define EDMA3_TC0_ERROR_INT                             (0u)
#define EDMA3_TC1_ERROR_INT                             (0u)
#define EDMA3_TC2_ERROR_INT                             (0u)
#define EDMA3_TC3_ERROR_INT                             (0u)
#endif

#define EDMA3_TC4_ERROR_INT                             (0u)
#define EDMA3_TC5_ERROR_INT                             (0u)
#define EDMA3_TC6_ERROR_INT                             (0u)
#define EDMA3_TC7_ERROR_INT                             (0u)

/**
 * \brief Base address as seen from the different cores may be different
 * And is defined based on the core
 */
#ifdef BUILD_C6A811X_DSP
#define EDMA3_CC_BASE_ADDR                          ((void *)(0x09000000))
#define EDMA3_TC0_BASE_ADDR                          ((void *)(0x09800000))
#define EDMA3_TC1_BASE_ADDR                          ((void *)(0x09900000))
#define EDMA3_TC2_BASE_ADDR                          ((void *)(0x09A00000))
#define EDMA3_TC3_BASE_ADDR                          ((void *)(0x09B00000))
#else
#define EDMA3_CC_BASE_ADDR                          ((void *)(0x49000000))
#define EDMA3_TC0_BASE_ADDR                          ((void *)(0x49800000))
#define EDMA3_TC1_BASE_ADDR                          ((void *)(0x49900000))
#define EDMA3_TC2_BASE_ADDR                          ((void *)(0x49A00000))
#define EDMA3_TC3_BASE_ADDR                          ((void *)(0x49B00000))
#endif

EDMA3_RM_GblConfigParams edma3GblCfgParams [EDMA3_MAX_EDMA3_INSTANCES] =
{
    /* EDMA3 INSTANCE# 0 */
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    EDMA3_NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    EDMA3_NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    EDMA3_NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    EDMA3_NUM_PARAMSET,
    /** Total number of Event Queues in the EDMA3 Controller */
    EDMA3_NUM_EVTQUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    EDMA3_NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    EDMA3_NUM_REGIONS,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    0u,

    /** Existence of memory protection feature */
    0u,

        /** Global Register Region of CC Registers */
        EDMA3_CC_BASE_ADDR,
        /** Transfer Controller (TC) Registers */
        {
	        EDMA3_TC0_BASE_ADDR,
	        EDMA3_TC1_BASE_ADDR,
	        EDMA3_TC2_BASE_ADDR,
	        EDMA3_TC3_BASE_ADDR,
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
        0u,
        1u,
        2u,
        3u,
        0u,
        0u,
        0u,
        0u
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
        16u,
        16u,
        16u,
        16u,
        0u,
        0u,
        0u,
        0u
        },

    /**
     * \brief To Configure the Default Burst Size (DBS) of TCs.
     * An optimally-sized command is defined by the transfer controller
     * default burst size (DBS). Different TCs can have different
     * DBS values. It is defined in Bytes.
     */
        {
        16u,
        16u,
        16u,
        16u,
        0u,
        0u,
        0u,
        0u
        },

    /**
     * \brief Mapping from each DMA channel to a Parameter RAM set,
     * if it exists, otherwise of no use.
     */
        {
            0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
            8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u,
            16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u,
            24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u,
            32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u, 
            40u, 41u, 42u, 43u, 44u, 45u, 46u, 47u,
            48u, 49u, 50u, 51u, 52u, 53u, 54u, 55u,
            56u, 57u, 58u, 59u, 60u, 61u, 62u, 63u
        },

     /**
      * \brief Mapping from each DMA channel to a TCC. This specific
      * TCC code will be returned when the transfer is completed
      * on the mapped channel.
      */
        {
            0u, 1u, 2u, 3u,
            4u, 5u, 6u, 7u,
            8u, 9u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
            12u, 13u, 14u, 15u,
            16u, 17u, 18u, 19u,
            20u, 21u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
            24u, 25u, 26u, 27u,
            28u, 29u, 30u, 31u,
            32u, 33u, 34u, 35u,
            36u, 37u, 38u, 39u,
            40u, 41u, 42u, 43u,
            44u, 45u, 46u, 47u,
            48u, 49u, 50u, 51u,
            52u, 53u, 54u, 55u,
            56u, 57u, 58u, 59u,
            60u, 61u, 62u, 63u
        },

    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0,
        EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    },
};
/* Defines for Own DMA channels For different cores */
/* channels  0 to 31 */
#define EDMA3_OWN_DMA_CHANNELS_0_A8    (0xFFFFFFFFu)
#define EDMA3_OWN_DMA_CHANNELS_0_DSP   (0xFFFFFFFFu)
#define EDMA3_OWN_DMA_CHANNELS_0_M3VIDEO    (0xFFFFFFFFu)
#define EDMA3_OWN_DMA_CHANNELS_0_M3VPSS    (0xFFFFFFFFu)
/* Channels 32 to 63 */
#define EDMA3_OWN_DMA_CHANNELS_1_A8    (0xFFFFFFFFu)
#define EDMA3_OWN_DMA_CHANNELS_1_DSP   (0xFFFFFFFFu)
#define EDMA3_OWN_DMA_CHANNELS_1_M3VIDEO    (0xFFFFFFFFu)
#define EDMA3_OWN_DMA_CHANNELS_1_M3VPSS    (0xFFFFFFFFu)

/* Defines for Own QDMA channels For different cores */
#define EDMA3_OWN_QDMA_CHANNELS_0_A8    (0x000000FFu)
#define EDMA3_OWN_QDMA_CHANNELS_0_DSP   (0x000000FFu)
#define EDMA3_OWN_QDMA_CHANNELS_0_M3VIDEO    (0x000000FFu)
#define EDMA3_OWN_QDMA_CHANNELS_0_M3VPSS    (0x000000FFu)

/* Defines for Own TCCs For different cores */
#define EDMA3_OWN_TCC_0_A8    (0xFFFFFFFFu)
#define EDMA3_OWN_TCC_0_DSP   (0xFFFFFFFFu)
#define EDMA3_OWN_TCC_0_M3VIDEO    (0xFFFFFFFFu)
#define EDMA3_OWN_TCC_0_M3VPSS    (0xFFFFFFFFu)
/* Channels 32 to 63 */
#define EDMA3_OWN_TCC_1_A8    (0xFFFFFFFFu)
#define EDMA3_OWN_TCC_1_DSP   (0xFFFFFFFFu)
#define EDMA3_OWN_TCC_1_M3VIDEO    (0xFFFFFFFFu)
#define EDMA3_OWN_TCC_1_M3VPSS    (0xFFFFFFFFu)

/* Defines for Reserved DMA channels For different cores */
/* channels  0 to 31 */
#define EDMA3_RESERVED_DMA_CHANNELS_0_A8    EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0
#define EDMA3_RESERVED_DMA_CHANNELS_0_DSP   EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0
#define EDMA3_RESERVED_DMA_CHANNELS_0_M3VIDEO    (0x00u)
#define EDMA3_RESERVED_DMA_CHANNELS_0_M3VPSS    (0x00u)
/* Channels 32 to 63 */
#define EDMA3_RESERVED_DMA_CHANNELS_1_A8    EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1
#define EDMA3_RESERVED_DMA_CHANNELS_1_DSP   EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1
#define EDMA3_RESERVED_DMA_CHANNELS_1_M3VIDEO    (0x00u)
#define EDMA3_RESERVED_DMA_CHANNELS_1_M3VPSS    (0x00u)

/* Defines for RESERVED QDMA channels For different cores */
#define EDMA3_RESERVED_QDMA_CHANNELS_0_A8    (0x00u)
#define EDMA3_RESERVED_QDMA_CHANNELS_0_DSP   (0x00u)
#define EDMA3_RESERVED_QDMA_CHANNELS_0_M3VIDEO    (0x00u)
#define EDMA3_RESERVED_QDMA_CHANNELS_0_M3VPSS    (0x00u)

/* Defines for RESERVED TCCs For different cores */
#define EDMA3_RESERVED_TCC_0_A8    EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0
#define EDMA3_RESERVED_TCC_0_DSP   EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0
#define EDMA3_RESERVED_TCC_0_M3VIDEO    (0x00u)
#define EDMA3_RESERVED_TCC_0_M3VPSS    (0x00u)
/* Channels 32 to 63 */
#define EDMA3_RESERVED_TCC_1_A8    EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1
#define EDMA3_RESERVED_TCC_1_DSP   EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1
#define EDMA3_RESERVED_TCC_1_M3VIDEO    (0x00u)
#define EDMA3_RESERVED_TCC_1_M3VPSS    (0x00u)

/* Default RM Instance Initialization Configuration */
EDMA3_RM_InstanceInitConfig defInstInitConfig [EDMA3_MAX_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] =
{
        /* EDMA3 INSTANCE# 0 */
        {
			/* Resources owned/reserved by region 0 (Configuration for A8 Core)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_OWN_DMA_CHANNELS_0_A8, EDMA3_OWN_DMA_CHANNELS_1_A8},

				/* ownQdmaChannels */
				/* 31     0 */
				{EDMA3_OWN_QDMA_CHANNELS_0_A8},

				/* ownTccs */
				/* 31     0     63    32 */
				{EDMA3_OWN_TCC_0_A8, EDMA3_OWN_TCC_1_A8},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_RESERVED_DMA_CHANNELS_0_A8, EDMA3_RESERVED_DMA_CHANNELS_1_A8},

				/* resvdQdmaChannels */
				/* 31     0 */
				{EDMA3_RESERVED_QDMA_CHANNELS_0_A8},

				/* resvdTccs */
				/* 31     0     63    32 */
				{EDMA3_RESERVED_TCC_0_A8, EDMA3_RESERVED_TCC_1_A8},
			},

	        /* Resources owned/reserved by region 1 (Configuration for DSP Core)*/
		    {
		        /* ownPaRAMSets */
		        /* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu},

		        /* ownDmaChannels */
		        /* 31     0     63    32 */
		       	{EDMA3_OWN_DMA_CHANNELS_0_DSP, EDMA3_OWN_DMA_CHANNELS_1_DSP},

		        /* ownQdmaChannels */
		        /* 31     0 */
		        {EDMA3_OWN_QDMA_CHANNELS_0_DSP},

		        /* ownTccs */
		        /* 31     0     63    32 */
		        {EDMA3_OWN_TCC_0_DSP, EDMA3_OWN_TCC_1_DSP},

		        /* resvdPaRAMSets */
		        /* 31     0     63    32     95    64     127   96 */
		        {0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u,
		        /* 159  128     191  160     223  192     255  224 */
		         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		        /* 287  256     319  288     351  320     383  352 */
		         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		        /* 415  384     447  416     479  448     511  480 */
		         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		        /* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_RESERVED_DMA_CHANNELS_0_DSP, EDMA3_RESERVED_DMA_CHANNELS_1_DSP},

		        /* resvdQdmaChannels */
		        /* 31     0 */
		        {EDMA3_RESERVED_QDMA_CHANNELS_0_DSP},

		        /* resvdTccs */
				/* 31     0     63    32 */
				{EDMA3_RESERVED_TCC_0_DSP, EDMA3_RESERVED_TCC_1_DSP},
		    },

	        /* Resources owned/reserved by region 2 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},
			},

	        /* Resources owned/reserved by region 3 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},
			},

	        /* Resources owned/reserved by region 4 (Configuration for M3VIDEO Core)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_OWN_DMA_CHANNELS_0_M3VIDEO, EDMA3_OWN_DMA_CHANNELS_1_M3VIDEO},

				/* ownQdmaChannels */
				/* 31     0 */
				{EDMA3_OWN_QDMA_CHANNELS_0_M3VIDEO},

				/* ownTccs */
				/* 31     0     63    32 */
				{EDMA3_OWN_TCC_0_M3VIDEO, EDMA3_OWN_TCC_0_M3VIDEO},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_RESERVED_DMA_CHANNELS_0_M3VIDEO, EDMA3_RESERVED_DMA_CHANNELS_1_M3VIDEO},

				/* resvdQdmaChannels */
				/* 31     0 */
				{EDMA3_RESERVED_QDMA_CHANNELS_0_M3VIDEO},

				/* resvdTccs */
				/* 31     0     63    32 */
				{EDMA3_RESERVED_TCC_0_M3VIDEO, EDMA3_RESERVED_TCC_1_M3VIDEO},
			},

	        /* Resources owned/reserved by region 5 (Configuration for M3VPSS Core)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_OWN_DMA_CHANNELS_0_M3VPSS, EDMA3_OWN_DMA_CHANNELS_1_M3VPSS},

				/* ownQdmaChannels */
				/* 31     0 */
				{EDMA3_OWN_QDMA_CHANNELS_0_M3VPSS},

				/* ownTccs */
				/* 31     0     63    32 */
				{EDMA3_OWN_TCC_0_M3VPSS, EDMA3_OWN_TCC_1_M3VPSS},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{EDMA3_RESERVED_DMA_CHANNELS_0_M3VPSS, EDMA3_RESERVED_DMA_CHANNELS_1_M3VPSS},

				/* resvdQdmaChannels */
				/* 31     0 */
				{EDMA3_RESERVED_QDMA_CHANNELS_0_M3VPSS},

				/* resvdTccs */
				/* 31     0     63    32 */
				{EDMA3_RESERVED_TCC_0_M3VPSS, EDMA3_RESERVED_TCC_1_M3VPSS},
			},

	        /* Resources owned/reserved by region 6 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},
			},

	        /* Resources owned/reserved by region 7 (Not Associated to any core supported)*/
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},
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
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1
        },
        /* Event to channel map for region 1 */
        {
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1
        },
        /* Event to channel map for region 2 */
        {
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1
        },
        /* Event to channel map for region 3 */
        {
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1
        },
        /* Event to channel map for region 4 */
        {
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1
        },
        /* Event to channel map for region 5 */
        {
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1
        },
        /* Event to channel map for region 6 */
        {
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1
        },
        /* Event to channel map for region 7 */
        {
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1
        },
    }
};

/* End of File */



