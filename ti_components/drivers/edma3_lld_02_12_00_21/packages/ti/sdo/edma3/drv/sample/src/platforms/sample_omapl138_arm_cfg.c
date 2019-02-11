/*
 * sample_omapl138_cfg.c
 *
 * SoC specific EDMA3 hardware related information like number of transfer
 * controllers, various interrupt ids etc. It is used while interrupts
 * enabling / disabling. It needs to be ported for different SoCs.
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

#include <ti/sdo/edma3/drv/edma3_drv.h>

/* Number of EDMA3 controllers present in the system */
#define NUM_EDMA3_INSTANCES         2u
const unsigned int numEdma3Instances = NUM_EDMA3_INSTANCES;

/* Number of DSPs present in the system */
#define NUM_DSPS                    1u
const unsigned int numDsps = NUM_DSPS;

/* Determine the processor id by reading DNUM register. */
unsigned short determineProcId()
{
    return 0;
}

signed char*  getGlobalAddr(signed char* addr)
{
     return (addr); /* The address is already a global address */
}

unsigned short isGblConfigRequired(unsigned int dspNum)
{
    (void) dspNum;
    return 0;
}

/* Semaphore handles */
EDMA3_OS_Sem_Handle semHandle[NUM_EDMA3_INSTANCES] = {NULL,NULL};

/** Number of PaRAM Sets available */
#define EDMA3_NUM_PARAMSET                              (128u)
/** Number of TCCS available */
#define EDMA3_NUM_TCC                                   (32u)

/** Number of Event Queues available                                          */
#define EDMA3_0_NUM_EVTQUE                              (2u)
#define EDMA3_1_NUM_EVTQUE                              (1u)

/** Number of Transfer Controllers available                                  */
#define EDMA3_0_NUM_TC                                  (2u)
#define EDMA3_1_NUM_TC                                  (1u)


/** Interrupt no. for Transfer Completion                                     */
#define EDMA3_0_CC_XFER_COMPLETION_INT                  (11u)
#define EDMA3_1_CC_XFER_COMPLETION_INT                  (93u)

/** Interrupt no. for CC Error                                                */
#define EDMA3_0_CC_ERROR_INT                            (12u)
#define EDMA3_1_CC_ERROR_INT                            (94u)

/** Interrupt no. for TCs Error                                               */
#define EDMA3_0_TC0_ERROR_INT                           (13u)
#define EDMA3_0_TC1_ERROR_INT                           (32u)
#define EDMA3_0_TC2_ERROR_INT                           (0u)
#define EDMA3_0_TC3_ERROR_INT                           (0u)
#define EDMA3_0_TC4_ERROR_INT                           (0u)
#define EDMA3_0_TC5_ERROR_INT                           (0u)
#define EDMA3_0_TC6_ERROR_INT                           (0u)
#define EDMA3_0_TC7_ERROR_INT                           (0u)

#define EDMA3_1_TC0_ERROR_INT                           (95u)
#define EDMA3_1_TC1_ERROR_INT                           (0u)
#define EDMA3_1_TC2_ERROR_INT                           (0u)
#define EDMA3_1_TC3_ERROR_INT                           (0u)
#define EDMA3_1_TC4_ERROR_INT                           (0u)
#define EDMA3_1_TC5_ERROR_INT                           (0u)
#define EDMA3_1_TC6_ERROR_INT                           (0u)
#define EDMA3_1_TC7_ERROR_INT                           (0u)

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
#define EDMA3_0_HWI_INT_XFER_COMP                           (7u)
#define EDMA3_0_HWI_INT_CC_ERR                              (7u)
#define EDMA3_0_HWI_INT_TC0_ERR                             (7u)
#define EDMA3_0_HWI_INT_TC1_ERR                             (7u)

/* EDMA 1 */
#define EDMA3_1_HWI_INT_XFER_COMP                           (7u)
#define EDMA3_1_HWI_INT_CC_ERR                              (7u)
#define EDMA3_1_HWI_INT_TC0_ERR                             (7u)


/**
 * \brief Mapping of DMA channels 0-31 to Hardware Events from
 * various peripherals, which use EDMA for data transfer.
 * All channels need not be mapped, some can be free also.
 * 1: Mapped
 * 0: Not mapped
 *
 * This mapping will be used to allocate DMA channels when user passes
 * EDMA3_DRV_DMA_CHANNEL_ANY as dma channel id (for eg to do memory-to-memory
 * copy). The same mapping is used to allocate the TCC when user passes
 * EDMA3_DRV_TCC_ANY as tcc id (for eg to do memory-to-memory copy).
 *
 * To allocate more DMA channels or TCCs, one has to modify the event mapping.
 */
                                                      /* 31     0 */
#define EDMA3_0_DMA_CHANNEL_TO_EVENT_MAPPING_0       (0xFF3FF3FFu)
#define EDMA3_1_DMA_CHANNEL_TO_EVENT_MAPPING_0       (0x3F07FFFFu)

/**
 * \brief Mapping of DMA channels 32-63 to Hardware Events from
 * various peripherals, which use EDMA for data transfer.
 * All channels need not be mapped, some can be free also.
 * 1: Mapped
 * 0: Not mapped
 *
 * This mapping will be used to allocate DMA channels when user passes
 * EDMA3_DRV_DMA_CHANNEL_ANY as dma channel id (for eg to do memory-to-memory
 * copy). The same mapping is used to allocate the TCC when user passes
 * EDMA3_DRV_TCC_ANY as tcc id (for eg to do memory-to-memory copy).
 *
 * To allocate more DMA channels or TCCs, one has to modify the event mapping.
 */
/* DMA channels 32-63 DOES NOT exist in omapl138. */
#define EDMA3_0_DMA_CHANNEL_TO_EVENT_MAPPING_1       (0x0u)
#define EDMA3_1_DMA_CHANNEL_TO_EVENT_MAPPING_1       (0x0u)

/* Variable which will be used internally for referring number of Event Queues*/
unsigned int numEdma3EvtQue[NUM_EDMA3_INSTANCES] =  {
                                                        EDMA3_0_NUM_EVTQUE,
                                                        EDMA3_1_NUM_EVTQUE
                                                    };

/* Variable which will be used internally for referring number of TCs.        */
unsigned int numEdma3Tc[NUM_EDMA3_INSTANCES] =  {
                                                    EDMA3_0_NUM_TC,
                                                    EDMA3_1_NUM_TC
                                                };

/**
 * Variable which will be used internally for referring transfer completion
 * interrupt.
 */
unsigned int ccXferCompInt[NUM_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] = {
                {
                    EDMA3_0_CC_XFER_COMPLETION_INT, EDMA3_0_CC_XFER_COMPLETION_INT, 0u, 0u, 0u, 0u, 0u, 0u,
                },
                {
                    EDMA3_1_CC_XFER_COMPLETION_INT, EDMA3_1_CC_XFER_COMPLETION_INT, 0u, 0u, 0u, 0u, 0u, 0u,
                },
            };

/**
 * Variable which will be used internally for referring channel controller's
 * error interrupt.
 */
unsigned int ccErrorInt[NUM_EDMA3_INSTANCES] = {
                                                    EDMA3_0_CC_ERROR_INT,
                                                    EDMA3_1_CC_ERROR_INT
                                               };

/**
 * Variable which will be used internally for referring transfer controllers'
 * error interrupts.
 */
unsigned int tcErrorInt[NUM_EDMA3_INSTANCES][8] = {
                               {
                                   EDMA3_0_TC0_ERROR_INT, EDMA3_0_TC1_ERROR_INT,
                                   EDMA3_0_TC2_ERROR_INT, EDMA3_0_TC3_ERROR_INT,
                                   EDMA3_0_TC4_ERROR_INT, EDMA3_0_TC5_ERROR_INT,
                                   EDMA3_0_TC6_ERROR_INT, EDMA3_0_TC7_ERROR_INT,
                               },
                               {
                                   EDMA3_1_TC0_ERROR_INT, EDMA3_1_TC1_ERROR_INT,
                                   EDMA3_1_TC2_ERROR_INT, EDMA3_1_TC3_ERROR_INT,
                                   EDMA3_1_TC4_ERROR_INT, EDMA3_1_TC5_ERROR_INT,
                                   EDMA3_1_TC6_ERROR_INT, EDMA3_1_TC7_ERROR_INT,
                               }
                            };

/**
 * Variables which will be used internally for referring the hardware interrupt
 * for various EDMA3 interrupts.
 */
unsigned int hwIntXferComp[NUM_EDMA3_INSTANCES] = {
                                                    EDMA3_0_HWI_INT_XFER_COMP,
                                                    EDMA3_1_HWI_INT_XFER_COMP
                                                  };

unsigned int hwIntCcErr[NUM_EDMA3_INSTANCES] = {
                                                   EDMA3_0_HWI_INT_CC_ERR,
                                                   EDMA3_1_HWI_INT_CC_ERR
                                               };

unsigned int hwIntTcErr[NUM_EDMA3_INSTANCES][8] = {
                                                     {
                                                        EDMA3_0_HWI_INT_TC0_ERR,
                                                        EDMA3_0_HWI_INT_TC1_ERR,
                                                     },
                                                     {
                                                        EDMA3_1_HWI_INT_TC0_ERR,
                                                     }
                                               };

/* Driver Object Initialization Configuration */
EDMA3_DRV_GblConfigParams sampleEdma3GblCfgParams[NUM_EDMA3_INSTANCES] =
{
    {
        /* EDMA3 INSTANCE# 0 */
        /** Total number of DMA Channels supported by the EDMA3 Controller    */
        32u,
        /** Total number of QDMA Channels supported by the EDMA3 Controller   */
        8u,
        /** Total number of TCCs supported by the EDMA3 Controller            */
        32u,
        /** Total number of PaRAM Sets supported by the EDMA3 Controller      */
        128u,
        /** Total number of Event Queues in the EDMA3 Controller              */
        2u,
        /** Total number of Transfer Controllers (TCs) in the EDMA3 Controller*/
        2u,
        /** Number of Regions on this EDMA3 controller                        */
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
        (void *)0x01C00000u,
        /** Transfer Controller (TC) Registers */
        {
            (void *)0x01C08000u,
            (void *)0x01C08400u,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL
        },
        /** Interrupt no. for Transfer Completion */
        EDMA3_0_CC_XFER_COMPLETION_INT,
        /** Interrupt no. for CC Error */
        EDMA3_0_CC_ERROR_INT,
        /** Interrupt no. for TCs Error */
        {
            EDMA3_0_TC0_ERROR_INT,
            EDMA3_0_TC1_ERROR_INT,
            EDMA3_0_TC2_ERROR_INT,
            EDMA3_0_TC3_ERROR_INT,
            EDMA3_0_TC4_ERROR_INT,
            EDMA3_0_TC5_ERROR_INT,
            EDMA3_0_TC6_ERROR_INT,
            EDMA3_0_TC7_ERROR_INT
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
            /* DMA channels 32-63 DOES NOT exist in OMAPL138. */
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
            /* DMA channels 32-63 DOES NOT exist in OMAPL138. */
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
            EDMA3_0_DMA_CHANNEL_TO_EVENT_MAPPING_0,
            EDMA3_0_DMA_CHANNEL_TO_EVENT_MAPPING_1
            }
        },

        {
        /* EDMA3 INSTANCE# 1 */
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
        (void *)0x01E30000u,
        /** Transfer Controller (TC) Registers */
            {
            (void *)0x01E38000u,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL,
            (void *)NULL
            },
        /** Interrupt no. for Transfer Completion */
        EDMA3_1_CC_XFER_COMPLETION_INT,
        /** Interrupt no. for CC Error */
        EDMA3_1_CC_ERROR_INT,
        /** Interrupt no. for TCs Error */
            {
                EDMA3_1_TC0_ERROR_INT,
                EDMA3_1_TC1_ERROR_INT,
                EDMA3_1_TC2_ERROR_INT,
                EDMA3_1_TC3_ERROR_INT,
                EDMA3_1_TC4_ERROR_INT,
                EDMA3_1_TC5_ERROR_INT,
                EDMA3_1_TC6_ERROR_INT,
                EDMA3_1_TC7_ERROR_INT,
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
            /* DMA channels 32-63 DOES NOT exist in OMAPL138. */
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
            /* DMA channels 32-63 DOES NOT exist in OMAPL138. */
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
            EDMA3_1_DMA_CHANNEL_TO_EVENT_MAPPING_0,
            EDMA3_1_DMA_CHANNEL_TO_EVENT_MAPPING_1
        }
    },
};


/* Driver Instance Initialization Configuration */
EDMA3_DRV_InstanceInitConfig sampleInstInitConfig[NUM_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] =
{
    /* EDMA3 INSTANCE# 0 */
    {
        /* Resources owned/reserved by region 0 */
        {
            /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
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
            /* 31       0 */
            {0xFF3FF3FFu,
            /* 63..32 */
            0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31       0 */
            {EDMA3_0_DMA_CHANNEL_TO_EVENT_MAPPING_0,
            /* 63..32 */
            EDMA3_0_DMA_CHANNEL_TO_EVENT_MAPPING_1},
        },
        /* Resources owned/reserved by region 1 */
        {
            /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
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
            /* 31       0 */
            {0xFF3FF3FFu,
            /* 63..32 */
            0x00000000u},

            /* resvdQdmaChannels */
            /* 31     0 */
            {0x00000000u},

            /* resvdTccs */
            /* 31       0 */
            {EDMA3_0_DMA_CHANNEL_TO_EVENT_MAPPING_0,
            /* 63..32 */
            EDMA3_0_DMA_CHANNEL_TO_EVENT_MAPPING_1},
        },
        /* Resources owned/reserved by region 2 */
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

        /* Resources owned/reserved by region 3 */
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
    /* EDMA3 INSTANCE# 1 */
    {
        /* Resources owned/reserved by region 0 */
        {
            /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
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
            {
                0xFFFFFFFFu,
                0x00000000u
            },

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
                /* 31     0     63    32     95    64     127   96 */
            {
                0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
                /* 159  128     191  160     223  192     255  224 */
                0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                /* 287  256     319  288     351  320     383  352 */
                0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                /* 415  384     447  416     479  448     511  480 */
                0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            },

            /* resvdDmaChannels */
                /* 31      0  */
            {
                EDMA3_1_DMA_CHANNEL_TO_EVENT_MAPPING_0,
                /* 63..32   */
                EDMA3_1_DMA_CHANNEL_TO_EVENT_MAPPING_1
            },

            /* resvdQdmaChannels */
            /* 31     0  */
            {
                0x00000000u
            },

            /* resvdTccs */
            /* 31      0 */
            {
                0x3F07FFFFu,
                /* 63..32 */
                0x00000000u
            },
        },
        /* Resources owned by Region 1 */
        {
            /* ownPaRAMSets */
            /* 31     0     63    32     95    64     127   96 */
            {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
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
            {
                0xFFFFFFFFu,
                0x00000000u
            },

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
                /* 31     0     63    32     95    64     127   96 */
            {
                0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
                /* 159  128     191  160     223  192     255  224 */
                0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                /* 287  256     319  288     351  320     383  352 */
                0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                /* 415  384     447  416     479  448     511  480 */
                0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
            },

            /* resvdDmaChannels */
                /* 31      0  */
            {
                EDMA3_1_DMA_CHANNEL_TO_EVENT_MAPPING_0,
                /* 63..32   */
                EDMA3_1_DMA_CHANNEL_TO_EVENT_MAPPING_1
            },

            /* resvdQdmaChannels */
            /* 31     0  */
            {
                0x00000000u
            },

            /* resvdTccs */
            /* 31      0 */
            {
                0x3F07FFFFu,
                /* 63..32 */
                0x00000000u
            },
        },
        /* Resources owned/reserved by region 2 */
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

        /* Resources owned/reserved by region 3 */
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
        }
    }
};

/* End of File */

