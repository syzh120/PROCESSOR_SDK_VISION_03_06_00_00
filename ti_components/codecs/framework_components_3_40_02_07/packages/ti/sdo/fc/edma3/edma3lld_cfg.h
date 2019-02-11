/*
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <ti/sdo/edma3/rm/edma3_rm.h>

#ifdef TI816X

#define GLOBAL_EDMA3_INSTANCES                  1u

/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (64u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (8u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (64u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (512u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (4u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (4u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (8u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (1u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (1u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x09000000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x09800000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x09900000u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        (0x09A00000u)
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        (0x09B00000u)
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        NULL
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        NULL
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Interrupt no. for Transfer Completion */
#define XFER_COMPLETION_INT                     (20u)
/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (21u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (22u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (0u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (0u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (0u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (0u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (0u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0xFFFFFFF0u)

#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x3C7FFFFFu)

EDMA3_GblConfigParams
        ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] = {
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        0u, 1u, 2u, 3u,
        4u, 5u, 6u, 7u,
        8u, 9u, 10u, 11u,
        12u, 13u, 14u, 15u,
        16u, 17u, 18u, 19u,
        20u, 21u, 22u, 23u,
        24u, 25u, 26u, 27u,
        28u, 29u, 30u, 31u,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP
        },

    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
                        /* Resources owned/reserved by region 0 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x03FFFFF0u, 0x03E0FFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                                /* 159  128     191  160     223  192     255  224 */
                                 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                                /* 287  256     319  288     351  320     383  352 */
                                 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                                /* 415  384     447  416     479  448     511  480 */
                                 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x03FFFFF0u, 0x03E0FFFFu},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x0000000Fu},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x03FFFFF0u, 0x03E0FFFFu},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x03FFFFF0u, 0x0060FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x03FFFFF0u, 0x0060FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x03FFFFF0u, 0x0060FFFFu},
                        },

                /* Resources owned/reserved by region 1 */
                    {
                        /* ownPaRAMSets */
                        /* 31     0     63    32     95    64     127   96 */
                        {0xFC00FF0Fu, 0xFC1F0000u, 0x00000000u, 0x00000000u,
                        /* 159  128     191  160     223  192     255  224 */
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        /* 287  256     319  288     351  320     383  352 */
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        /* 415  384     447  416     479  448     511  480 */
                         0x00000000u, 0x00000000u, 0x00000000u, 0xFFFFFFFFu,},

                        /* ownDmaChannels */
                        /* 31     0     63    32 */
                        {0xFC00FF0Fu, 0xFC1F0000u},

                        /* ownQdmaChannels */
                        /* 31     0 */
                        {0x000000F0u},

                        /* ownTccs */
                        /* 31     0     63    32 */
                        {0xFFFFFFFFu, 0xFC1F0000u},

                        /* resvdPaRAMSets */
                        /* 31     0     63    32     95    64     127   96 */
                        {0xFC00FF0Fu, 0x00000000u, 0x00000000u, 0x00000000u,
                        /* 159  128     191  160     223  192     255  224 */
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        /* 287  256     319  288     351  320     383  352 */
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        /* 415  384     447  416     479  448     511  480 */
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                        /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x0000FF00u, 0x00000000u},

                        /* resvdQdmaChannels */
                        /* 31     0 */
                        {0x00000000u},

                        /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x0000FF00u, 0x00000000u},
                    },

                /* Resources owned/reserved by region 2 */
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

                /* Resources owned/reserved by region 3 */
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

                /* Resources owned/reserved by region 4 */
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

                /* Resources owned/reserved by region 5 */
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

                /* Resources owned/reserved by region 6 */
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

                /* Resources owned/reserved by region 7 */
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

#endif

#ifdef TCI6608

#define GLOBAL_EDMA3_INSTANCES                  3u

#define NUM_REGION                      8u

/* Driver Object Initialization Configuration */
EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
        {
                {
                /* EDMA3 INSTANCE# 0 */
                /** Total number of DMA Channels supported by the EDMA3 Controller */
                16u,
                /** Total number of QDMA Channels supported by the EDMA3 Controller */
                8u,
                /** Total number of TCCs supported by the EDMA3 Controller */
                16u,
                /** Total number of PaRAM Sets supported by the EDMA3 Controller */
                128u,
                /** Total number of Event Queues in the EDMA3 Controller */
                2u,
                /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
                2u,
                /** Number of Regions on this EDMA3 controller */
                8u,

                /**
                 * \brief Channel mapping existence
                 * A value of 0 (No channel mapping) implies that there is fixed association
                 * for a channel number to a parameter entry number or, in other words,
                 * PaRAM entry n corresponds to channel n.
                 */
                1u,

                /** Existence of memory protection feature */
                1u,

                /** Global Register Region of CC Registers */
                (void *)0x02700000u,
                /** Transfer Controller (TC) Registers */
                {
                (void *)0x02760000u,
                (void *)0x02768000u,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL
                },
                /** Interrupt no. for Transfer Completion */
                38u,
                /** Interrupt no. for CC Error */
                32u,
                /** Interrupt no. for TCs Error */
                {
                34u,
                35u,
                0u,
                0u,
                0u,
                0u,
                0u,
                0u,
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
                0u,
                0u,
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
                0u,
                0u,
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
                128u,
                128u,
                0u,
                0u,
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
                /* DMA channels 16-63 DOES NOT exist */
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS
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
                /* DMA channels 16-63 DOES NOT exist */
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC
                },

                /**
                 * \brief Mapping of DMA channels to Hardware Events from
                 * various peripherals, which use EDMA for data transfer.
                 * All channels need not be mapped, some can be free also.
                 */
                {
                0x00000000u,
                0x00000000u
                }
                },

                {
                /* EDMA3 INSTANCE# 1 */
                /** Total number of DMA Channels supported by the EDMA3 Controller */
                64u,
                /** Total number of QDMA Channels supported by the EDMA3 Controller */
                8u,
                /** Total number of TCCs supported by the EDMA3 Controller */
                64u,
                /** Total number of PaRAM Sets supported by the EDMA3 Controller */
                512u,
                /** Total number of Event Queues in the EDMA3 Controller */
                4u,
                /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
                4u,
                /** Number of Regions on this EDMA3 controller */
                8u,

                /**
                 * \brief Channel mapping existence
                 * A value of 0 (No channel mapping) implies that there is fixed association
                 * for a channel number to a parameter entry number or, in other words,
                 * PaRAM entry n corresponds to channel n.
                 */
                1u,

                /** Existence of memory protection feature */
                1u,

                /** Global Register Region of CC Registers */
                (void *)0x02720000u,
                /** Transfer Controller (TC) Registers */
                {
                (void *)0x02770000u,
                (void *)0x02778000u,
                (void *)0x02780000u,
                (void *)0x02788000u,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL
                },
                /** Interrupt no. for Transfer Completion */
                8u,
                /** Interrupt no. for CC Error */
                0u,
                /** Interrupt no. for TCs Error */
                {
                2u,
                3u,
                4u,
                5u,
                0u,
                0u,
                0u,
                0u,
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
                128u,
                64u,
                128u,
                64u,
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
                0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
                8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u,
                16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u,
                24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u,
                32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u,
                40u, 41u, 42u, 43u, 44u, 45u, 46u, 47u,
                EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP
                },

                /**
                 * \brief Mapping of DMA channels to Hardware Events from
                 * various peripherals, which use EDMA for data transfer.
                 * All channels need not be mapped, some can be free also.
                 */
                {
                0xFFFFFFFFu,
                0xFFFF0000u
                }
                },

                {
                /* EDMA3 INSTANCE# 2 */
                /** Total number of DMA Channels supported by the EDMA3 Controller */
                64u,
                /** Total number of QDMA Channels supported by the EDMA3 Controller */
                8u,
                /** Total number of TCCs supported by the EDMA3 Controller */
                64u,
                /** Total number of PaRAM Sets supported by the EDMA3 Controller */
                512u,
                /** Total number of Event Queues in the EDMA3 Controller */
                4u,
                /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
                4u,
                /** Number of Regions on this EDMA3 controller */
                8u,

                /**
                 * \brief Channel mapping existence
                 * A value of 0 (No channel mapping) implies that there is fixed association
                 * for a channel number to a parameter entry number or, in other words,
                 * PaRAM entry n corresponds to channel n.
                 */
                1u,

                /** Existence of memory protection feature */
                1u,

                /** Global Register Region of CC Registers */
                (void *)0x02740000u,
                /** Transfer Controller (TC) Registers */
                {
                (void *)0x02790000u,
                (void *)0x02798000u,
                (void *)0x027A0000u,
                (void *)0x027A8000u,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL
                },
                /** Interrupt no. for Transfer Completion */
                24u,
                /** Interrupt no. for CC Error */
                16u,
                /** Interrupt no. for TCs Error */
                {
                18u,
                19u,
                20u,
                21u,
                0u,
                0u,
                0u,
                0u,
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
                128u,
                64u,
                64u,
                128u,
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
                0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
                8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u,
                16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u,
                24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u,
                32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u,
                40u, 41u, 42u, 43u, 44u, 45u, 46u, 47u,
                EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP
                },

                /**
                 * \brief Mapping of DMA channels to Hardware Events from
                 * various peripherals, which use EDMA for data transfer.
                 * All channels need not be mapped, some can be free also.
                 */
                {
                0xFFFFFFFFu,
                0xFFFF0000u
                }
                },
        };

EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig[GLOBAL_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] =
        {
                /* EDMA3 INSTANCE# 0 */
                {
                        /* Resources owned/reserved by region 0 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x3FFF0003u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000003u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000001u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000003u, 0x00000000u},

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
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00000000u},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00000000u},
                        },

                /* Resources owned/reserved by region 1 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xC000000Cu, 0x00000FFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x0000000Cu, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000002u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x0000000Cu, 0x00000000u},

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

                /* Resources owned/reserved by region 2 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000030u, 0x03FFF000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000030u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000004u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000030u, 0x00000000u},

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

                /* Resources owned/reserved by region 3 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x000000C0u, 0xFC000000u, 0x000000FFu, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x000000C0u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000008u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x000000C0u, 0x00000000u},

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

                /* Resources owned/reserved by region 4 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000300u, 0x00000000u, 0x003FFF00u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000300u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000010u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000300u, 0x00000000u},

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

                /* Resources owned/reserved by region 5 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000C00u, 0x00000000u, 0xFFC00000u, 0x0000000Fu,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000C00u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000020u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000C00u, 0x00000000u},

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

                /* Resources owned/reserved by region 6 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00003000u, 0x00000000u, 0x00000000u, 0x0003FFF0u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00003000u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000040u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00003000u, 0x00000000u},

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

                /* Resources owned/reserved by region 7 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000C000u, 0x00000000u, 0x00000000u, 0xFFFC0000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x0000C000u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000080u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x0000C000u, 0x00000000u},

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

                /* EDMA3 INSTANCE# 1 */
            {
                /* Resources owned/reserved by region 0 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x00030000u, 0xFFFFFFFFu, 0x00FFFFFFu,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00030000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000001u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00030000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 1 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x000C0000u, 0x00000000u, 0xFF000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x000C0000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000002u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x000C0000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 2 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x00300000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0xFFFF0000u, 0xFFFFFFFFu, 0x000000FFu,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00300000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000004u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00300000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 3 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x00C00000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0xFFFFFF00u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00C00000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000008u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00C00000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 4 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x03000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0xFFFFFFFFu, 0x00FFFFFFu, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x03000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000010u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x03000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 5 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x0C000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0xFF000000u, 0xFFFFFFFFu,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x0000FFFFu, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x0C000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000020u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x0C000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 6 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x30000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0xFFFF0000u, 0xFFFFFFFFu, 0x000000FFu, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x30000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000040u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x30000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 7 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0xC0000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0xFFFFFF00u, 0xFFFFFFFFu},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0xC0000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000080u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0xC0000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },
            },

                /* EDMA3 INSTANCE# 2 */
                {
                /* Resources owned/reserved by region 0 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x00030000u, 0xFFFFFFFFu, 0x00FFFFFFu,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00030000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000001u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00030000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 1 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x000C0000u, 0x00000000u, 0xFF000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x000C0000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000002u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x000C0000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 2 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x00300000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0xFFFF0000u, 0xFFFFFFFFu, 0x000000FFu,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00300000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000004u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00300000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 3 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x00C00000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0xFFFFFF00u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00C00000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000008u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00C00000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 4 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x03000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0xFFFFFFFFu, 0x00FFFFFFu, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x03000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000010u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x03000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 5 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x0C000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0xFF000000u, 0xFFFFFFFFu,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x0000FFFFu, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x0C000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000020u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x0C000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 6 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x30000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0xFFFF0000u, 0xFFFFFFFFu, 0x000000FFu, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x30000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000040u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x30000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },

                /* Resources owned/reserved by region 7 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0xC0000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0xFFFFFF00u, 0xFFFFFFFFu},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0xC0000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000080u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0xC0000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0xFFFFFFFFu, 0x0000FFFFu},
                        },
            },
        };


#endif

#ifdef TCI6616

#define GLOBAL_EDMA3_INSTANCES                  3u

#define NUM_REGION                      8u

/* Driver Object Initialization Configuration */
EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams[GLOBAL_EDMA3_INSTANCES] =
        {
                {
                /* EDMA3 INSTANCE# 0 */
                /** Total number of DMA Channels supported by the EDMA3 Controller */
                16u,
                /** Total number of QDMA Channels supported by the EDMA3 Controller */
                8u,
                /** Total number of TCCs supported by the EDMA3 Controller */
                16u,
                /** Total number of PaRAM Sets supported by the EDMA3 Controller */
                128u,
                /** Total number of Event Queues in the EDMA3 Controller */
                2u,
                /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
                2u,
                /** Number of Regions on this EDMA3 controller */
                8u,

                /**
                 * \brief Channel mapping existence
                 * A value of 0 (No channel mapping) implies that there is fixed association
                 * for a channel number to a parameter entry number or, in other words,
                 * PaRAM entry n corresponds to channel n.
                 */
                1u,

                /** Existence of memory protection feature */
                1u,

                /** Global Register Region of CC Registers */
                (void *)0x02700000u,
                /** Transfer Controller (TC) Registers */
                {
                (void *)0x02760000u,
                (void *)0x02768000u,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL
                },
                /** Interrupt no. for Transfer Completion */
                38u,
                /** Interrupt no. for CC Error */
                32u,
                /** Interrupt no. for TCs Error */
                {
                34u,
                35u,
                0u,
                0u,
                0u,
                0u,
                0u,
                0u,
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
                0u,
                0u,
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
                0u,
                0u,
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
                128u,
                128u,
                0u,
                0u,
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
                /* DMA channels 16-63 DOES NOT exist */
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
                EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS
                },

                 /**
                  * \brief Mapping from each DMA channel to a TCC. This specific
                  * TCC code will be returned when the transfer is completed
                  * on the mapped channel.
                  */
                {
                0u, 1u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                4u, 5u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                8u, 9u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                12u, 13u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                /* DMA channels 16-63 DOES NOT exist */
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
                EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC
                },

                /**
                 * \brief Mapping of DMA channels to Hardware Events from
                 * various peripherals, which use EDMA for data transfer.
                 * All channels need not be mapped, some can be free also.
                 */
                {
                0x00003333u,
                0x00000000u
                }
                },

                {
                /* EDMA3 INSTANCE# 1 */
                /** Total number of DMA Channels supported by the EDMA3 Controller */
                64u,
                /** Total number of QDMA Channels supported by the EDMA3 Controller */
                8u,
                /** Total number of TCCs supported by the EDMA3 Controller */
                64u,
                /** Total number of PaRAM Sets supported by the EDMA3 Controller */
                512u,
                /** Total number of Event Queues in the EDMA3 Controller */
                4u,
                /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
                4u,
                /** Number of Regions on this EDMA3 controller */
                8u,

                /**
                 * \brief Channel mapping existence
                 * A value of 0 (No channel mapping) implies that there is fixed association
                 * for a channel number to a parameter entry number or, in other words,
                 * PaRAM entry n corresponds to channel n.
                 */
                1u,

                /** Existence of memory protection feature */
                1u,

                /** Global Register Region of CC Registers */
                (void *)0x02720000u,
                /** Transfer Controller (TC) Registers */
                {
                (void *)0x02770000u,
                (void *)0x02778000u,
                (void *)0x02780000u,
                (void *)0x02788000u,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL
                },
                /** Interrupt no. for Transfer Completion */
                8u,
                /** Interrupt no. for CC Error */
                0u,
                /** Interrupt no. for TCs Error */
                {
                2u,
                3u,
                4u,
                5u,
                0u,
                0u,
                0u,
                0u,
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
                64u,
                64u,
                64u,
                64u,
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
                0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
                8u, 9u, 10u, 11u, 12u, 13u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u,
                24u, 25u, 26u, 27u, 28u, 29u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u,
                40u, 41u, 42u, 43u, 44u, 45u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                48u, 49u, 50u, 51u, 52u, 53u, 54u, 55u,
                56u, 57u, 58u, 59u, 60u, 61u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP
                },

                /**
                 * \brief Mapping of DMA channels to Hardware Events from
                 * various peripherals, which use EDMA for data transfer.
                 * All channels need not be mapped, some can be free also.
                 */
                {
                0x3FFF3FFFu,
                0x3FFF3FFFu
                }
                },

                {
                /* EDMA3 INSTANCE# 2 */
                /** Total number of DMA Channels supported by the EDMA3 Controller */
                64u,
                /** Total number of QDMA Channels supported by the EDMA3 Controller */
                8u,
                /** Total number of TCCs supported by the EDMA3 Controller */
                64u,
                /** Total number of PaRAM Sets supported by the EDMA3 Controller */
                512u,
                /** Total number of Event Queues in the EDMA3 Controller */
                4u,
                /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
                4u,
                /** Number of Regions on this EDMA3 controller */
                8u,

                /**
                 * \brief Channel mapping existence
                 * A value of 0 (No channel mapping) implies that there is fixed association
                 * for a channel number to a parameter entry number or, in other words,
                 * PaRAM entry n corresponds to channel n.
                 */
                1u,

                /** Existence of memory protection feature */
                1u,

                /** Global Register Region of CC Registers */
                (void *)0x02740000u,
                /** Transfer Controller (TC) Registers */
                {
                (void *)0x02790000u,
                (void *)0x02798000u,
                (void *)0x027A0000u,
                (void *)0x027A8000u,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL,
                (void *)NULL
                },
                /** Interrupt no. for Transfer Completion */
                24u,
                /** Interrupt no. for CC Error */
                16u,
                /** Interrupt no. for TCs Error */
                {
                18u,
                19u,
                20u,
                21u,
                0u,
                0u,
                0u,
                0u,
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
                64u,
                64u,
                64u,
                64u,
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
                0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
                8u, 9u, 10u, 11u, 12u, 13u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u,
                24u, 25u, 26u, 27u, 28u, 29u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u,
                40u, 41u, 42u, 43u, 44u, 45u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                48u, 49u, 50u, 51u, 52u, 53u, 54u, 55u,
                56u, 57u, 58u, 59u, 60u, 61u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP
                },

                /**
                 * \brief Mapping of DMA channels to Hardware Events from
                 * various peripherals, which use EDMA for data transfer.
                 * All channels need not be mapped, some can be free also.
                 */
                {
                0x3FFF3FFFu,
                0x3FFF3FFFu
                }
                },
        };

EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig[GLOBAL_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] =
        {
                /* EDMA3 INSTANCE# 0 */
                {
                        /* Resources owned/reserved by region 0 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFF000Fu, 0x00000FFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x0000000Fu, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000003u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x0000000Fu, 0x00000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000003u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31           0 */
                                {0x00000003u, 0x00000000u},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31           0 */
                                {0x00000003u, 0x00000000u},
                        },

                /* Resources owned/reserved by region 1 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x000000F0u, 0xFFFFF000u, 0x000000FFu, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x000000F0u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x0000000Cu},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x000000F0u, 0x00000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000030u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000030u, 0x00000000u},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x00000030u, 0x00000000u},
                        },

                /* Resources owned/reserved by region 2 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000F00u, 0x00000000u, 0xFFFFFF00u, 0x0000000Fu,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000F00u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000030u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000F00u, 0x00000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000300u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000300u, 0x00000000u},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x00000300u, 0x00000000u},
                        },

                /* Resources owned/reserved by region 3 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0xFFFFFFF0u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x0000F000u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x000000C0u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x0000F000u, 0x00000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00003000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x00003000u, 0x00000000u},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x00003000u, 0x00000000u},
                        },

                /* Resources owned/reserved by region 4 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

                /* Resources owned/reserved by region 5 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

                /* Resources owned/reserved by region 6 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

                /* Resources owned/reserved by region 7 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

                /* EDMA3 INSTANCE# 1 */
            {
                /* Resources owned/reserved by region 0 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000FFFFu, 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFFu,
                                /* 159  128     191  160     223  192     255  224 */
                                 0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x0000FFFFu, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000003u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x0000FFFFu, 0x00000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00003FFFu, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x00003FFFu, 0x00000000u},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x00003FFFu, 0x00000000u},
                        },

                /* Resources owned/reserved by region 1 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFF0000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0xFFFF0000u, 0xFFFFFFFFu, 0xFFFFFFFFu,
                                /* 287  256     319  288     351  320     383  352 */
                                 0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFF0000u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x0000000Cu},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0xFFFF0000u, 0x00000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x3FFF0000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x3FFF0000u, 0x00000000u},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x3FFF0000u, 0x00000000u},
                        },

                /* Resources owned/reserved by region 2 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x0000FFFFu, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x0000FFFFu},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000030u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x0000FFFFu},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x00003FFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00003FFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00003FFFu},
                        },

                /* Resources owned/reserved by region 3 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0xFFFF0000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0xFFFF0000u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0xFFFF0000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x000000C0u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0xFFFF0000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x3FFF0000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x3FFF0000u},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x3FFF0000u},
                        },

                /* Resources owned/reserved by region 4 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

                /* Resources owned/reserved by region 5 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

                /* Resources owned/reserved by region 6 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

                /* Resources owned/reserved by region 7 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

                /* EDMA3 INSTANCE# 2 */
                {
                /* Resources owned/reserved by region 0 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000FFFFu, 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFFu,
                                /* 159  128     191  160     223  192     255  224 */
                                 0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x0000FFFFu, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000003u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x0000FFFFu, 0x00000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00003FFFu, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x00003FFFu, 0x00000000u},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x00003FFFu, 0x00000000u},
                        },

                /* Resources owned/reserved by region 1 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0xFFFF0000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0xFFFF0000u, 0xFFFFFFFFu, 0xFFFFFFFFu,
                                /* 287  256     319  288     351  320     383  352 */
                                 0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0xFFFF0000u, 0x00000000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x0000000Cu},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0xFFFF0000u, 0x00000000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x3FFF0000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x3FFF0000u, 0x00000000u},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x3FFF0000u, 0x00000000u},
                        },

                /* Resources owned/reserved by region 2 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x0000FFFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x0000FFFFu, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x0000FFFFu},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x00000030u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x0000FFFFu},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x00003FFFu, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00003FFFu},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x00003FFFu},
                        },

                /* Resources owned/reserved by region 3 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0xFFFF0000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0xFFFF0000u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,},

                                /* ownDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0xFFFF0000u},

                                /* ownQdmaChannels */
                                /* 31     0 */
                                {0x000000C0u},

                                /* ownTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0xFFFF0000u},

                                /* resvdPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x00000000u, 0x3FFF0000u, 0x00000000u, 0x00000000u,
                                /* 159  128     191  160     223  192     255  224 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 287  256     319  288     351  320     383  352 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                                /* 415  384     447  416     479  448     511  480 */
                                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

                                /* resvdDmaChannels */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x3FFF0000u},

                                /* resvdQdmaChannels */
                                /* 31     0 */
                                {0x00000000u},

                                /* resvdTccs */
                                /* 31     0     63    32 */
                                {0x00000000u, 0x3FFF0000u},
                        },

                /* Resources owned/reserved by region 4 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

                /* Resources owned/reserved by region 5 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

                /* Resources owned/reserved by region 6 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

                /* Resources owned/reserved by region 7 */
                        {
                                /* ownPaRAMSets */
                                /* 31     0     63    32     95    64     127   96 */
                                {0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

#endif

#ifdef C642x

#define GLOBAL_EDMA3_INSTANCES 1


/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (64u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (8u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (64u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (128u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (3u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (3u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (4u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (0u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (0u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x01C00000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x01C10000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x01C10400u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        (0x01C10800u)
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        NULL
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        NULL
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        NULL
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Interrupt no. for Transfer Completion */
#define XFER_COMPLETION_INT                     (36u)
/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (37u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (38u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (39u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (40u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (0u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (0u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (0u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

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
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0x33FFFFFCu)
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
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x007F7FFFu)


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        0u,
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
        0u,
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
        32u,
        64u,
        0u,
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
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, 2u, 3u,
           4u, 5u, 6u, 7u,
           8u, 9u, 10u, 11u,
           12u, 13u, 14u, 15u,
           16u, 17u, 18u, 19u,
           20u, 21u, 22u, 23u,
           24u, 25u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           28u, 29u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           36u, 37u, 38u, 39u,
           40u, 41u, 42u, 43u,
           44u, 45u, 46u, EDMA3_RM_CH_NO_TCC_MAP,
           48u, 49u, 50u, 51u,
           52u, 53u, 54u, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP
        },

    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
          {
            /* Resources owned by Region 0*/
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 0*/
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000FFFu, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0xFFFFFFFFu, 0xFFFFFFF0u},

            /* ownQdmaChannels */
            {0x00000080u},

            /* ownTccs */
            {0xFFFFFFFFu, 0xFFFFFFF0u},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 2 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 2 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 3 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 3 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          }
        }
};

#endif

#ifdef C6452

#define GLOBAL_EDMA3_INSTANCES 1

/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (64u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (8u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (64u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (512u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (4u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (4u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (8u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (1u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (1u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x02A00000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x02A20000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x02A28000u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        (0x02A30000u)
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        (0x02A38000u)
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        NULL
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        NULL
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Interrupt no. for Transfer Completion */
#define XFER_COMPLETION_INT                     (72u)
/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (79u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (81u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (82u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (83u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (84u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (0u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (0u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

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
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0xFFFCFFBFu)
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
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x803FFFFFu)
/**
 * These channel mappings make 12 DMA channels FREE to be alloacted
 * by the Driver for ANY DMA channel type of requests.
 * To allocate 2 more ANY DMA channels (i.e. a total of 14),
 * use the following define. It will take 2 I2C DMA channels.
 * #define DMA_CHANNEL_TO_EVENT_MAPPING_1          0x803FCFFFu
 */


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        64u,
        64u,
        64u,
        64u,
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
        0u, 1u, 2u, 3u,
        4u, 5u, EDMA3_RM_CH_NO_TCC_MAP, 7u,
        8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, 18u, 19u,
        20u, 21u, 22u, 23u,
        24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u,
        32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u,
        40u, 41u, 42u, 43u, 44u, 45u, 46u, 47u,
        48u, 49u, 50u, 51u,
        52u, 53u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, 63u
/**
 * These channel mappings make 12 DMA channels FREE to be alloacted
 * by the Driver for ANY DMA channel type of requests.
 * To allocate 2 more ANY DMA channels (i.e. a total of 14), comment out
 * the above code and uncomment the following code.
 * It will take 2 I2C DMA channels also.

        0u, 1u, 2u, 3u,
        4u, 5u, EDMA3_RM_CH_NO_TCC_MAP, 7u,
        8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, 18u, 19u,
        20u, 21u, 22u, 23u,
        24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u,
        32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u,
        40u, 41u, 42u, 43u,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, 46u, 47u,
        48u, 49u, 50u, 51u,
        52u, 53u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, 63u
 */
        },

    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
          {
            /* Resources owned by Region 0 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 0 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            {0xFFFFFFC0u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0xFFFFFFC0u, 0xFFFFFFFFu},

            /* ownQdmaChannels */
            {0x00000080u},

            /* ownTccs */
            {0xFFFFFFC0u, 0xFFFFFFFFu},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 2 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 2 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 3 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 3 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 4 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 4 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 5 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 5 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 6 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 6 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 7 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 7 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          }
        }
};

#endif

#ifdef C6455

#define GLOBAL_EDMA3_INSTANCES 1

/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (64u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (4u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (64u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (256u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (4u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (4u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (8u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (1u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (1u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x02A00000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x02A20000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x02A28000u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        (0x02A30000u)
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        (0x02A38000u)
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        NULL
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        NULL
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Interrupt no. for Transfer Completion */
#define XFER_COMPLETION_INT                     (72u)
/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (79u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (81u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (82u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (83u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (84u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (0u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (0u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

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
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0xF013F007u)
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
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0xFFFF3101u)


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        64u,
        64u,
        64u,
        64u,
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
           0u, 1u, 2u, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           12u, 13u, 14u, 15u,
           16u, 17u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           20u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           28u, 29u, 30u, 31u,
           32u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           40u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP,
           44u, 45u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
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
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
          {
            /* Resources owned by Region 0*/
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 0*/
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0xFFFFFFFFu, 0xFFFFFFFFu},

            /* ownQdmaChannels */
            {0x0000000Fu},

            /* ownTccs */
            {0xFFFFFFFFu, 0xFFFFFFFFu},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 2 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 2 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 3 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 3 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 4 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 4 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 5 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 5 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 6 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 6 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 7 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 7 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          }
        }
};

#endif

#ifdef C6474

#define GLOBAL_EDMA3_INSTANCES 1

/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (64u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (8u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (64u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (256u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (6u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (6u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (8u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (1u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (1u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x02A00000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x02A20000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x02A28000u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        (0x02A30000u)
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        (0x02A38000u)
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        (0x02A40000u)
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        (0x02A48000u)
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Transfer Completion Interrupt for Shadow Region 0 */
#define XFER_COMPLETION_INT_0                                   (62u)
/** Transfer Completion Interrupt for Shadow Region 1 */
#define XFER_COMPLETION_INT_1                                   (63u)
/** Transfer Completion Interrupt for Shadow Region 2 */
#define XFER_COMPLETION_INT_2                                   (64u)
/** Transfer Completion Interrupt for Shadow Region 3 */
#define XFER_COMPLETION_INT_3                                   (65u)
/** Transfer Completion Interrupt for Shadow Region 4 */
#define XFER_COMPLETION_INT_4                                   (66u)
/** Transfer Completion Interrupt for Shadow Region 5 */
#define XFER_COMPLETION_INT_5                                   (67u)
/** Transfer Completion Interrupt for Shadow Region 6 */
#define XFER_COMPLETION_INT_6                                   (68u)
/** Transfer Completion Interrupt for Shadow Region 7 */
#define XFER_COMPLETION_INT_7                                   (69u)

/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (36u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (38u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (39u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (40u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (41u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (42u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (43u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

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
                                                                                                /* 31     0 */
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0xFF3FFFFCu)


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
                                                                                                /* 63    32 */
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0xFFFFE7F7u)


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT_0,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        4u,
        5u,
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
        16u,
        16u,
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
        64u,
        64u,
        64u,
        64u,
        64u,
        64u,
        0u,
        0u
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
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, 2u, 3u,
        4u, 5u, 6u, 7u,
        8u, 9u, 10u, 11u,
        12u, 13u, 14u, 15u,
        16u, 17u, 18u, 19u,
        20u, 21u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        24u, 25u, 26u, 27u,
        28u, 29u, 30, 31,
        32u, 33u, 34u, EDMA3_RM_CH_NO_TCC_MAP,
        36u, 37u, 38u, 39u,
        40u, 41u, 42u, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, 45u, 46u, 47u,
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
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
          {
            /* Resources owned by Region 0 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0x003FFFFFu, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x003FFFFEu, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000007u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x003FFFFEu, 0x00000000u},

            /* Resources reserved by Region 0 */
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
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
                    {0x00000000u, 0x00000000u, 0xFFC00000u, 0xFFFFFFFFu,
                    /* 159  128     191  160     223  192     255  224 */
                     0xFFFFFFFFu, 0x000007FFu, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
                        {0xFFC00000u, 0x000007FFu},

            /* ownQdmaChannels */
            /* 31     0 */
                {0x00000031u},

            /* ownTccs */
            /* 31     0     63    32 */
                        {0xFFC00000u, 0x000007FFu},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* resvdDmaChannels */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 2 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
                0x00000000u, 0xFFFFF800u, 0xFFFFFFFFu, 0xFFFFFFFFu,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
                {0x00000000u, 0xFFFFF800u},

            /* ownQdmaChannels */
            /* 31     0 */
                {0x000000C0u},

            /* ownTccs */
            /* 31     0     63    32 */
                {0x00000000u, 0xFFFFF800u},

            /* Resources reserved by Region 2 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 3 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 3 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 4 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 4 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 5 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 5 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 6 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 6 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 7 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 7 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          }
        }
};

#endif

#ifdef C6747

#define GLOBAL_EDMA3_INSTANCES 1

/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (32u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (8u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (32u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (128u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (2u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (2u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (4u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (0u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (0u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x01C00000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x01C08000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x01C08400u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        NULL
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        NULL
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        NULL
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        NULL
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Interrupt no. for Transfer Completion */
#define XFER_COMPLETION_INT                     (8u)
/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (56u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (57u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (58u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (0u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (0u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (0u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (0u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

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
                                                                                                /* 31     0 */
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0xFF3FFFFFu)
/**
 * EDMA channels 22 and 23, which correspond to GPIO
 * bank interrupts will be used for memory-to-memory data transfers.
 */


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
/* DMA channels 32-63 DOES NOT exist in C6747. */
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x0u)


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        0u,
        0u,
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
        0u,
        0u,
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
        0u,
        0u,
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
        /* DMA channels 32-63 DOES NOT exist in C6747. */
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS
        },

     /**
      * \brief Mapping from each DMA channel to a TCC. This specific
      * TCC code will be returned when the transfer is completed
      * on the mapped channel.
      */
        {
        0u, 1u, 2u, 3u,
        4u, 5u, 6u, 7u,
        8u, 9u, 10u, 11u,
        12u, 13u, 14u, 15u,
        16u, 17u, 18u, 19u,
        20u, 21u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        24u, 25u, 26u, 27u,
        28u, 29u, 30u, 31u,
        /* DMA channels 32-63 DOES NOT exist in C6747. */
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC
        },

    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
          {
            /* Resources owned by Region 0 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 0 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0x00FFFFFFu, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
                {0xFFFFFFFFu, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x0000000Fu},

            /* ownTccs */
            /* 31     0     63    32 */
            {0xFFFFFFFFu, 0x00000000u},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* resvdDmaChannels */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 2 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 2 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 3 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 3 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          }
        }
};

#endif

#ifdef DA830

#define GLOBAL_EDMA3_INSTANCES 1

/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (32u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (8u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (32u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (128u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (2u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (2u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (4u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (0u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (0u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x01C00000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x01C08000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x01C08400u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        NULL
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        NULL
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        NULL
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        NULL
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Interrupt no. for Transfer Completion */
#define XFER_COMPLETION_INT                     (8u)
/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (56u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (57u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (58u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (0u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (0u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (0u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (0u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

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
                                                                                                /* 31     0 */
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0xFF3FFFFFu)
/**
 * EDMA channels 22 and 23, which correspond to GPIO
 * bank interrupts will be used for memory-to-memory data transfers.
 */


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
/* DMA channels 32-63 DOES NOT exist in DA830. */
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x0u)


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        0u,
        0u,
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
        0u,
        0u,
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
        0u,
        0u,
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
        /* DMA channels 32-63 DOES NOT exist in DA830. */
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS
        },

     /**
      * \brief Mapping from each DMA channel to a TCC. This specific
      * TCC code will be returned when the transfer is completed
      * on the mapped channel.
      */
        {
        0u, 1u, 2u, 3u,
        4u, 5u, 6u, 7u,
        8u, 9u, 10u, 11u,
        12u, 13u, 14u, 15u,
        16u, 17u, 18u, 19u,
        20u, 21u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        24u, 25u, 26u, 27u,
        28u, 29u, 30u, 31u,
        /* DMA channels 32-63 DOES NOT exist in DA830. */
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC
        },

    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
          {
            /* Resources owned by Region 0 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 0 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0x00FFFFFFu, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
                {0xFFFFFFFFu, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x0000000Fu},

            /* ownTccs */
            /* 31     0     63    32 */
            {0xFFFFFFFFu, 0x00000000u},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* resvdDmaChannels */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 2 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 2 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 3 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 3 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          }
        }
};

#endif

#ifdef DM360

#define GLOBAL_EDMA3_INSTANCES 1

/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (64u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (8u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (64u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (256u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (4u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (4u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (4u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (0u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (0u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x01C00000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x01C10000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x01C10400u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        (0x01C10800u)
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        (0x01C10C00u)
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        NULL
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        NULL
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Interrupt no. for Transfer Completion */
#define XFER_COMPLETION_INT                     (16u)
/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (17u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (18u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (19u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (61u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (62u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (0u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (0u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

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
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0xFFFFFFFFu)
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
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0xFFFF0000u)


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        32u,
        64u,
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
        0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
        8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u,
        16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u,
        24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        48u, 49u, 50u, 51u, 52u, 53u, 54u, 55u,
        56u, 57u, 58u, 59u, 60u, 61u, 62u, 63u
        },


    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
          {
            /* Resources owned by Region 0 */
            /* ownPaRAMSets */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0xFFFFFFFFu, 0xFFFFFFFFu},

            /* ownQdmaChannels */
            {0x00000080u},

            /* ownTccs */
            {0xFFFFFFFFu, 0xFFFFFFFFu},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 0 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 2 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 2 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 3 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 3 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          }
        }
};

#endif

#ifdef DM643x

#define GLOBAL_EDMA3_INSTANCES 1

#include <ti/sdo/edma3/rm/edma3_rm.h>

/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (64u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (8u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (64u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (128u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (3u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (3u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (4u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (0u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (0u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x01C00000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x01C10000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x01C10400u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        (0x01C10800u)
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        NULL
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        NULL
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        NULL
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Interrupt no. for Transfer Completion */
#define XFER_COMPLETION_INT                     (36u)
/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (37u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (38u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (39u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (40u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (0u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (0u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (0u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

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
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0x33FFFFFCu)
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
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x007F7FFFu)


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        0u,
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
        0u,
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
        32u,
        64u,
        0u,
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
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, 2u, 3u,
           4u, 5u, 6u, 7u,
           8u, 9u, 10u, 11u,
           12u, 13u, 14u, 15u,
           16u, 17u, 18u, 19u,
           20u, 21u, 22u, 23u,
           24u, 25u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           28u, 29u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           36u, 37u, 38u, 39u,
           40u, 41u, 42u, 43u,
           44u, 45u, 46u, EDMA3_RM_CH_NO_TCC_MAP,
           48u, 49u, 50u, 51u,
           52u, 53u, 54u, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
           EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP
        },

    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
          {
            /* Resources owned by Region 0*/
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 0*/
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000FFFu, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0xFFFFFFFFu, 0xFFFFFFF0u},

            /* ownQdmaChannels */
            {0x00000080u},

            /* ownTccs */
            {0xFFFFFFFFu, 0xFFFFFFF0u},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 2 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 2 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 3 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 3 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          }
        }
};

#endif

#ifdef OMAP35xx

#define GLOBAL_EDMA3_INSTANCES 1

/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (64u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (8u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (64u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (128u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (2u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (2u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (8u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (1u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (1u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x01C00000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x01C10000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x01C10400u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        NULL
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        NULL
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        NULL
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        NULL
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Interrupt no. for Transfer Completion */
#define XFER_COMPLETION_INT                     (37u)
/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (38u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (39u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (40u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (0u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (0u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (0u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (0u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

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
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0x00000FFFu)
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
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x0u)


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        0u,
        0u,
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
        0u,
        0u,
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
        64u,
        64u,
        0u,
        0u,
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
        0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
        8u, 9u, 10u, 11u,
                EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
                EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP
        },

    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
          {
            /* Resources owned by Region 0 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 0 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0xFFFFFFFFu, 0xFFFFFFFFu},

            /* ownQdmaChannels */
            {0x000000FFu},

            /* ownTccs */
            {0xFFFFFFFFu, 0xFFFFFFFFu},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 2 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 2 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 3 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 3 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 4 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 4 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 5 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 5 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 6 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 6 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          },

          {
            /* Resources owned by Region 7 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* ownDmaChannels */
            {0x0u, 0x0u},

            /* ownQdmaChannels */
            {0x0u},

            /* ownTccs */
            {0x0u, 0x0u},

            /* Resources reserved by Region 7 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0u, 0x0u},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0u, 0x0u},
          }
        }
};

/* End of File */


#endif

#ifdef OMAPL137

#define GLOBAL_EDMA3_INSTANCES 1

/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (32u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (8u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (32u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (128u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (2u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (2u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (4u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (0u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (0u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x01C00000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x01C08000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x01C08400u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        NULL
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        NULL
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        NULL
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        NULL
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Interrupt no. for Transfer Completion */
#define XFER_COMPLETION_INT                     (8u)
/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (56u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (57u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (58u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (0u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (0u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (0u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (0u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

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
                                                                                                /* 31     0 */
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0xFF3FFFFFu)
/**
 * EDMA channels 22 and 23, which correspond to GPIO
 * bank interrupts will be used for memory-to-memory data transfers.
 */


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
/* DMA channels 32-63 DOES NOT exist in OMAPL137. */
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x0u)


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        0u,
        0u,
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
        0u,
        0u,
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
        0u,
        0u,
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
        /* DMA channels 32-63 DOES NOT exist in OMAPL137. */
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS
        },

     /**
      * \brief Mapping from each DMA channel to a TCC. This specific
      * TCC code will be returned when the transfer is completed
      * on the mapped channel.
      */
        {
        0u, 1u, 2u, 3u,
        4u, 5u, 6u, 7u,
        8u, 9u, 10u, 11u,
        12u, 13u, 14u, 15u,
        16u, 17u, 18u, 19u,
        20u, 21u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        24u, 25u, 26u, 27u,
        28u, 29u, 30u, 31u,
        /* DMA channels 32-63 DOES NOT exist in OMAPL137. */
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC
        },

    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
          {
            /* Resources owned by Region 0 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 0 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0x00FFFFFFu, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
                {0xFFFFFFFFu, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x0000000Fu},

            /* ownTccs */
            /* 31     0     63    32 */
            {0xFFFFFFFFu, 0x00000000u},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* resvdDmaChannels */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 2 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 2 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 3 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 3 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          }
        }
};

#endif

#ifdef OMAPL138

#define GLOBAL_EDMA3_INSTANCES 2

#define NUM_REGION                                      (4u)

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
#define DMA_CHANNEL_TO_EVENT_MAPPING_0_0                (0xFF3FF3FFu)
/**
 * EDMA channels 22 and 23, which correspond to GPIO
 * bank interrupts will be used for memory-to-memory data transfers.
 */

/* EDMA3 1 */
                                                                                                /* 31     0 */
#define DMA_CHANNEL_TO_EVENT_MAPPING_1_0                (0x3F07FFFFu)
/**
 * EDMA channels 19-23, 30 & 31, which donot correspond to any
 * peripheral will be used for memory-to-memory data transfers.
 */

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
/* DMA channels 32-63 DOES NOT exist in C6748. */
/* EDMA3 0 */
#define DMA_CHANNEL_TO_EVENT_MAPPING_0_1                (0x0u)
/* EDMA3 1 */
#define DMA_CHANNEL_TO_EVENT_MAPPING_1_1                (0x0u)


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
        /* EDMA3 INSTANCE# 0 */
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    32u,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    8u,
    /** Total number of TCCs supported by the EDMA3 Controller */
    32u,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    128u,
    /** Total number of Event Queues in the EDMA3 Controller */
    2u,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    2u,
    /** Number of Regions on this EDMA3 controller */
    4u,

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
    (void *)(0x01C00000u),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(0x01C08000u),
        (void *)(0x01C08400u),
        (void *)NULL,
        (void *)NULL,
        (void *)NULL,
        (void *)NULL,
        (void *)NULL,
        (void *)NULL,
        },
    /** Interrupt no. for Transfer Completion */
    8u,
    /** Interrupt no. for CC Error */
    56u,
    /** Interrupt no. for TCs Error */
        {
        57u,
        58u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
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
        0u,
        0u,
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
        0u,
        0u,
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
        0u,
        0u,
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
        /* DMA channels 32-63 DOES NOT exist in C6748. */
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS
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
        /* DMA channels 32-63 DOES NOT exist in C6748. */
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC
        },

    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        DMA_CHANNEL_TO_EVENT_MAPPING_0_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_0_1
        }
    },


                /* EDMA3 INSTANCE# 1 */
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    32u,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    8u,
    /** Total number of TCCs supported by the EDMA3 Controller */
    32u,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    128u,
    /** Total number of Event Queues in the EDMA3 Controller */
    1u,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    1u,
    /** Number of Regions on this EDMA3 controller */
    4u,

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
    (void *)(0x01E30000u),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(0x01E38000u),
        (void *)NULL,
        (void *)NULL,
        (void *)NULL,
        (void *)NULL,
        (void *)NULL,
        (void *)NULL,
        (void *)NULL,
        },
    /** Interrupt no. for Transfer Completion */
    91u,
    /** Interrupt no. for CC Error */
    92u,
    /** Interrupt no. for TCs Error */
        {
        93u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
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
        0u,
        0u,
        0u,
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
        0u,
        0u,
        0u,
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
        0u,
        0u,
        0u,
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
        /* DMA channels 32-63 DOES NOT exist in C6748. */
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
        EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS
        },

     /**
      * \brief Mapping from each DMA channel to a TCC. This specific
      * TCC code will be returned when the transfer is completed
      * on the mapped channel.
      */
        {
        0u, 1u, 2u, 3u,
        4u, 5u, 6u, 7u,
        8u, 9u, 10u, 11u,
        12u, 13u, 14u, 15u,
        16u, 17u, 18u, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        24u, 25u, 26u, 27u,
        28u, 29u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        /* DMA channels 32-63 DOES NOT exist in C6748. */
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
        EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC
        },

    /**
     * \brief Mapping of DMA channels to Hardware Events from
     * various peripherals, which use EDMA for data transfer.
     * All channels need not be mapped, some can be free also.
     */
        {
        DMA_CHANNEL_TO_EVENT_MAPPING_1_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1_1
        }
    },
};


/* Default RM Instance Initialization Configuration */
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
                /* EDMA3 INSTANCE# 0 */
        {
          {
            /* Resources owned by Region 0 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 0 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
                {0xFFFFFFFFu, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x000000FFu},

            /* ownTccs */
            /* 31     0     63    32 */
            {0xFFFFFFFFu, 0x00000000u},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* resvdDmaChannels */
            /* 31      0  63..32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0_0, DMA_CHANNEL_TO_EVENT_MAPPING_0_1},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31      0  63..32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0_0, DMA_CHANNEL_TO_EVENT_MAPPING_0_1},
          },

          {
            /* Resources owned by Region 2 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 2 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 3 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 3 */
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


                /* EDMA3 INSTANCE# 1 */
        {
          {
            /* Resources owned by Region 0 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 0 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0x00FFFFFFu,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
                {0xFFFFFFFFu, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x000000FFu},

            /* ownTccs */
            /* 31     0     63    32 */
            {0xFFFFFFFFu, 0x00000000u},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* resvdDmaChannels */
            /* 31      0  63..32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_1_0, DMA_CHANNEL_TO_EVENT_MAPPING_1_1},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31      0  63..32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_1_0, DMA_CHANNEL_TO_EVENT_MAPPING_1_1},
          },

          {
            /* Resources owned by Region 2 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 2 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 3 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 3 */
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

#endif

#ifdef TCI6488

#define GLOBAL_EDMA3_INSTANCES 1

/** Total number of DMA Channels supported by the EDMA3 Controller */
#define NUM_DMA_CHANNELS                        (64u)
/** Total number of QDMA Channels supported by the EDMA3 Controller */
#define NUM_QDMA_CHANNELS                       (8u)
/** Total number of TCCs supported by the EDMA3 Controller */
#define NUM_TCC                                 (64u)
/** Total number of PaRAM Sets supported by the EDMA3 Controller */
#define NUM_PARAM_SETS                          (256u)
/** Total number of Event Queues in the EDMA3 Controller */
#define NUM_EVENT_QUEUE                         (6u)
/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
#define NUM_TC                                  (6u)
/** Number of Regions on this EDMA3 controller */
#define NUM_REGION                              (8u)

/**
 * \brief Channel mapping existence
 * A value of 0 (No channel mapping) implies that there is fixed association
 * for a channel number to a parameter entry number or, in other words,
 * PaRAM entry n corresponds to channel n.
 */
#define CHANNEL_MAPPING_EXISTENCE               (1u)
/** Existence of memory protection feature */
#define MEM_PROTECTION_EXISTENCE                (1u)

/** Global Register Region of CC Registers */
#define CC_BASE_ADDRESS                         (0x02A00000u)
/** Transfer Controller 0 Registers */
#define TC0_BASE_ADDRESS                        (0x02A20000u)
/** Transfer Controller 1 Registers */
#define TC1_BASE_ADDRESS                        (0x02A28000u)
/** Transfer Controller 2 Registers */
#define TC2_BASE_ADDRESS                        (0x02A30000u)
/** Transfer Controller 3 Registers */
#define TC3_BASE_ADDRESS                        (0x02A38000u)
/** Transfer Controller 4 Registers */
#define TC4_BASE_ADDRESS                        (0x02A40000u)
/** Transfer Controller 5 Registers */
#define TC5_BASE_ADDRESS                        (0x02A48000u)
/** Transfer Controller 6 Registers */
#define TC6_BASE_ADDRESS                        NULL
/** Transfer Controller 7 Registers */
#define TC7_BASE_ADDRESS                        NULL

/** Transfer Completion Interrupt for Shadow Region 0 */
#define XFER_COMPLETION_INT_0                                   (62u)
/** Transfer Completion Interrupt for Shadow Region 1 */
#define XFER_COMPLETION_INT_1                                   (63u)
/** Transfer Completion Interrupt for Shadow Region 2 */
#define XFER_COMPLETION_INT_2                                   (64u)
/** Transfer Completion Interrupt for Shadow Region 3 */
#define XFER_COMPLETION_INT_3                                   (65u)
/** Transfer Completion Interrupt for Shadow Region 4 */
#define XFER_COMPLETION_INT_4                                   (66u)
/** Transfer Completion Interrupt for Shadow Region 5 */
#define XFER_COMPLETION_INT_5                                   (67u)
/** Transfer Completion Interrupt for Shadow Region 6 */
#define XFER_COMPLETION_INT_6                                   (68u)
/** Transfer Completion Interrupt for Shadow Region 7 */
#define XFER_COMPLETION_INT_7                                   (69u)

/** Interrupt no. for CC Error */
#define CC_ERROR_INT                            (36u)
/** Interrupt no. for TC 0 Error */
#define TC0_ERROR_INT                           (38u)
/** Interrupt no. for TC 1 Error */
#define TC1_ERROR_INT                           (39u)
/** Interrupt no. for TC 2 Error */
#define TC2_ERROR_INT                           (40u)
/** Interrupt no. for TC 3 Error */
#define TC3_ERROR_INT                           (41u)
/** Interrupt no. for TC 4 Error */
#define TC4_ERROR_INT                           (42u)
/** Interrupt no. for TC 5 Error */
#define TC5_ERROR_INT                           (43u)
/** Interrupt no. for TC 6 Error */
#define TC6_ERROR_INT                           (0u)
/** Interrupt no. for TC 7 Error */
#define TC7_ERROR_INT                           (0u)

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
                                                                                                /* 31     0 */
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0xFF3FFFFCu)


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
                                                                                                /* 63    32 */
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0xFFFFE7F7u)


EDMA3_GblConfigParams ti_sdo_fc_edma3_lld_globalConfigParams [GLOBAL_EDMA3_INSTANCES] =
{
    {
    /** Total number of DMA Channels supported by the EDMA3 Controller */
    NUM_DMA_CHANNELS,
    /** Total number of QDMA Channels supported by the EDMA3 Controller */
    NUM_QDMA_CHANNELS,
    /** Total number of TCCs supported by the EDMA3 Controller */
    NUM_TCC,
    /** Total number of PaRAM Sets supported by the EDMA3 Controller */
    NUM_PARAM_SETS,
    /** Total number of Event Queues in the EDMA3 Controller */
    NUM_EVENT_QUEUE,
    /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
    NUM_TC,
    /** Number of Regions on this EDMA3 controller */
    NUM_REGION,

    /**
     * \brief Channel mapping existence
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    CHANNEL_MAPPING_EXISTENCE,

    /** Existence of memory protection feature */
    MEM_PROTECTION_EXISTENCE,

    /** Global Register Region of CC Registers */
    (void *)(CC_BASE_ADDRESS),
    /** Transfer Controller (TC) Registers */
        {
        (void *)(TC0_BASE_ADDRESS),
        (void *)(TC1_BASE_ADDRESS),
        (void *)(TC2_BASE_ADDRESS),
        (void *)(TC3_BASE_ADDRESS),
        (void *)(TC4_BASE_ADDRESS),
        (void *)(TC5_BASE_ADDRESS),
        (void *)(TC6_BASE_ADDRESS),
        (void *)(TC7_BASE_ADDRESS)
        },
    /** Interrupt no. for Transfer Completion */
    XFER_COMPLETION_INT_0,
    /** Interrupt no. for CC Error */
    CC_ERROR_INT,
    /** Interrupt no. for TCs Error */
        {
        TC0_ERROR_INT,
        TC1_ERROR_INT,
        TC2_ERROR_INT,
        TC3_ERROR_INT,
        TC4_ERROR_INT,
        TC5_ERROR_INT,
        TC6_ERROR_INT,
        TC7_ERROR_INT
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
        4u,
        5u,
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
        16u,
        16u,
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
        64u,
        64u,
        64u,
        64u,
        64u,
        64u,
        0u,
        0u
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
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, 2u, 3u,
        4u, 5u, 6u, 7u,
        8u, 9u, 10u, 11u,
        12u, 13u, 14u, 15u,
        16u, 17u, 18u, 19u,
        20u, 21u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        24u, 25u, 26u, 27u,
        28u, 29u, 30, 31,
        32u, 33u, 34u, EDMA3_RM_CH_NO_TCC_MAP,
        36u, 37u, 38u, 39u,
        40u, 41u, 42u, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, 45u, 46u, 47u,
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
        DMA_CHANNEL_TO_EVENT_MAPPING_0,
        DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    }
};


/* Default RM Instance Initialization Configuration */

EDMA3_InstanceInitConfig ti_sdo_fc_edma3_lld_instInitConfig [GLOBAL_EDMA3_INSTANCES][NUM_REGION] =
{
        {
          {
            /* Resources owned by Region 0 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0x003FFFFFu, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x003FFFFFu, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000007u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x003FFFFFu, 0x00000000u},

            /* Resources reserved by Region 0 */
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
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
                    {0x00000000u, 0x00000000u, 0xFFC00000u, 0xFFFFFFFFu,
                    /* 159  128     191  160     223  192     255  224 */
                     0xFFFFFFFFu, 0x000007FFu, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
                        {0xFFC00000u, 0x000007FFu},

            /* ownQdmaChannels */
            /* 31     0 */
                {0x00000031u},

            /* ownTccs */
            /* 31     0     63    32 */
                        {0xFFC00000u, 0x000007FFu},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* resvdDmaChannels */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31                                         0  63                                                  32 */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          },

          {
            /* Resources owned by Region 2 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
                0x00000000u, 0xFFFFF800u, 0xFFFFFFFFu, 0xFFFFFFFFu,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
                {0x00000000u, 0xFFFFF800u},

            /* ownQdmaChannels */
            /* 31     0 */
                {0x000000C0u},

            /* ownTccs */
            /* 31     0     63    32 */
                {0x00000000u, 0xFFFFF800u},

            /* Resources reserved by Region 2 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 3 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 3 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 4 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 4 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 5 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 5 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 6 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 6 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          },

          {
            /* Resources owned by Region 7 */
             /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 159  128     191  160     223  192     255  224 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 287  256     319  288     351  320     383  352 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            /* 415  384     447  416     479  448     511  480 */
             0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

            /* ownDmaChannels */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* ownQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* ownTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* Resources reserved by Region 7 */
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
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31     0     63    32 */
            {0x00000000u, 0x00000000u},
          }
        }
};

#endif
