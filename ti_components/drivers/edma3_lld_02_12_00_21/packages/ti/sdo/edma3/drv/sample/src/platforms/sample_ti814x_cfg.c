/*
 * sample_ti814x_cfg.c
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
#define NUM_EDMA3_INSTANCES         1U
const uint32_t numEdma3Instances = NUM_EDMA3_INSTANCES;

/* Number of DSPs present in the system */
#define NUM_DSPS                    1U
const uint32_t numDsps = NUM_DSPS;

int8_t*  getGlobalAddr(int8_t* addr);

uint16_t isGblConfigRequired(uint32_t dspNum);

/* Determine the processor id by reading DNUM register. */
uint16_t determineProcId(void);

/* Determine the processor id by reading DNUM register. */
uint16_t determineProcId(void)
{
#ifdef BUILD_CENTAURUS_A8
	return 0U;
#elif defined BUILD_CENTAURUS_DSP
	return 1U;
#elif defined BUILD_CENTAURUS_M3VPSS
	return 5U;
#elif defined BUILD_CENTAURUS_M3VIDEO
	return 4U;
#else
	return 1U;
#endif
}

int8_t*  getGlobalAddr(int8_t* addr)
{
     return (addr); /* The address is already a global address */
}
uint16_t isGblConfigRequired(uint32_t dspNum)
{
    (void) dspNum;
#ifdef BUILD_CENTAURUS_DSP
	return 1U;
#else
	return 0U;
#endif
}

/* Semaphore handles */
EDMA3_OS_Sem_Handle semHandle[NUM_EDMA3_INSTANCES] = {NULL};

/** Number of PaRAM Sets available                                            */
#define EDMA3_NUM_PARAMSET                              (512U)

/** Number of TCCS available                                                  */
#define EDMA3_NUM_TCC                                   (64U)

/** Number of DMA Channels available                                          */
#define EDMA3_NUM_DMA_CHANNELS                          (64U)

/** Number of QDMA Channels available                                         */
#define EDMA3_NUM_QDMA_CHANNELS                         (8U)

/** Number of Event Queues available                                          */
#define EDMA3_NUM_EVTQUE                              (4U)

/** Number of Transfer Controllers available                                  */
#define EDMA3_NUM_TC                                  (4U)

/** Number of Regions                                                         */
#define EDMA3_NUM_REGIONS                             (6U)


/** Interrupt no. for Transfer Completion */
#define EDMA3_CC_XFER_COMPLETION_INT_A8                 (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_DSP                (20U)
#define EDMA3_CC_XFER_COMPLETION_INT_M3VPSS             (63U)
#define EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO            (62U)

#ifdef BUILD_CENTAURUS_A8
#define EDMA3_CC_XFER_COMPLETION_INT                    (EDMA3_CC_XFER_COMPLETION_INT_A8)
#elif defined BUILD_CENTAURUS_DSP
#define EDMA3_CC_XFER_COMPLETION_INT                    (EDMA3_CC_XFER_COMPLETION_INT_DSP)
#elif defined BUILD_CENTAURUS_M3VIDEO
#define EDMA3_CC_XFER_COMPLETION_INT                    (EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO)
#elif defined BUILD_CENTAURUS_M3VPSS
#define EDMA3_CC_XFER_COMPLETION_INT                    (EDMA3_CC_XFER_COMPLETION_INT_M3VPSS)
#else
#define EDMA3_CC_XFER_COMPLETION_INT                    (0U)
#endif

/** Interrupt no. for CC Error */
#define EDMA3_CC_ERROR_INT_A8                           (14U)
#define EDMA3_CC_ERROR_INT_DSP                          (21U)

#ifdef BUILD_CENTAURUS_A8
#define EDMA3_CC_ERROR_INT                              (EDMA3_CC_ERROR_INT_A8)
#elif defined BUILD_CENTAURUS_DSP
#define EDMA3_CC_ERROR_INT                              (EDMA3_CC_ERROR_INT_DSP)
#else
#define EDMA3_CC_ERROR_INT                              (0U)
#endif

/** Interrupt no. for TCs Error */
#define EDMA3_TC0_ERROR_INT_DSP                         (22U)
#define EDMA3_TC1_ERROR_INT_DSP                         (27U)
#define EDMA3_TC2_ERROR_INT_DSP                         (28U)
#define EDMA3_TC3_ERROR_INT_DSP                         (29U)
#define EDMA3_TC0_ERROR_INT_A8                          (112U)
#define EDMA3_TC1_ERROR_INT_A8                          (113U)
#define EDMA3_TC2_ERROR_INT_A8                          (114U)
#define EDMA3_TC3_ERROR_INT_A8                          (115U)

#ifdef BUILD_CENTAURUS_A8
#define EDMA3_TC0_ERROR_INT                             (EDMA3_TC0_ERROR_INT_A8)
#define EDMA3_TC1_ERROR_INT                             (EDMA3_TC1_ERROR_INT_A8)
#define EDMA3_TC2_ERROR_INT                             (EDMA3_TC2_ERROR_INT_A8)
#define EDMA3_TC3_ERROR_INT                             (EDMA3_TC3_ERROR_INT_A8)
#elif defined BUILD_CENTAURUS_DSP
#define EDMA3_TC0_ERROR_INT                             (EDMA3_TC0_ERROR_INT_DSP)
#define EDMA3_TC1_ERROR_INT                             (EDMA3_TC1_ERROR_INT_DSP)
#define EDMA3_TC2_ERROR_INT                             (EDMA3_TC2_ERROR_INT_DSP)
#define EDMA3_TC3_ERROR_INT                             (EDMA3_TC3_ERROR_INT_DSP)
#else
#define EDMA3_TC0_ERROR_INT                             (0U)
#define EDMA3_TC1_ERROR_INT                             (0U)
#define EDMA3_TC2_ERROR_INT                             (0U)
#define EDMA3_TC3_ERROR_INT                             (0U)
#endif

#define EDMA3_TC4_ERROR_INT                             (0U)
#define EDMA3_TC5_ERROR_INT                             (0U)
#define EDMA3_TC6_ERROR_INT                             (0U)
#define EDMA3_TC7_ERROR_INT                             (0U)

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
#define EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0       (0xFCFF3F0CU)  /* TBD */


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
#define EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1       (0xFF003C00U) /* TBD */


/* Variable which will be used internally for referring number of Event Queues*/
uint32_t numEdma3EvtQue[NUM_EDMA3_INSTANCES] =  {
                                                        EDMA3_NUM_EVTQUE,
                                                    };

/* Variable which will be used internally for referring number of TCs.        */
uint32_t numEdma3Tc[NUM_EDMA3_INSTANCES] =  {
                                                    EDMA3_NUM_TC,
                                                };

/**
 * Variable which will be used internally for referring transfer completion
 * interrupt.
 */
uint32_t ccXferCompInt[NUM_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] =
{
    {
        EDMA3_CC_XFER_COMPLETION_INT_A8, EDMA3_CC_XFER_COMPLETION_INT_DSP, 0U, 0U,
        EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO, EDMA3_CC_XFER_COMPLETION_INT_M3VPSS, 0U, 0U,
    },
};

/**
 * Variable which will be used internally for referring channel controller's
 * error interrupt.
 */
uint32_t ccErrorInt[NUM_EDMA3_INSTANCES] = {
                                                    EDMA3_CC_ERROR_INT,
                                               };

/**
 * Variable which will be used internally for referring transfer controllers'
 * error interrupts.
 */
uint32_t tcErrorInt[NUM_EDMA3_INSTANCES][8] =
{
   {
       EDMA3_TC0_ERROR_INT, EDMA3_TC1_ERROR_INT,
       EDMA3_TC2_ERROR_INT, EDMA3_TC3_ERROR_INT,
       EDMA3_TC4_ERROR_INT, EDMA3_TC5_ERROR_INT,
       EDMA3_TC6_ERROR_INT, EDMA3_TC7_ERROR_INT,
   }
};

/**
 * Variables which will be used internally for referring the hardware interrupt
 * for various EDMA3 interrupts.
 */
uint32_t hwIntXferComp[NUM_EDMA3_INSTANCES] = {
                                                    EDMA3_HWI_INT_XFER_COMP
                                                  };

uint32_t hwIntCcErr[NUM_EDMA3_INSTANCES] = {
                                                   EDMA3_HWI_INT_CC_ERR
                                               };

uint32_t hwIntTcErr[NUM_EDMA3_INSTANCES][8] = {
                                                     {
                                                        EDMA3_HWI_INT_TC0_ERR,
                                                        EDMA3_HWI_INT_TC1_ERR,
                                                        EDMA3_HWI_INT_TC2_ERR,
                                                        EDMA3_HWI_INT_TC3_ERR,
                                                        0,
                                                        0,
                                                        0,
                                                        0
                                                     }
                                               };

/**
 * \brief Base address as seen from the different cores may be different
 * And is defined based on the core
 */
#ifdef BUILD_CENTAURUS_DSP
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

/* Driver Object Initialization Configuration */
EDMA3_DRV_GblConfigParams sampleEdma3GblCfgParams[NUM_EDMA3_INSTANCES] =
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
            0U,
            1U,
            2U,
            3U,
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
            16U,
            16U,
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
            16U,
            16U,
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
            EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0,
            EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1
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
 
/* Defines for Own DMA channels For different cores */
/* channels  0 to 31 */
#define EDMA3_OWN_DMA_CHANNELS_0_A8    (0xFFFFFFFFU)
#define EDMA3_OWN_DMA_CHANNELS_0_DSP   (0xFFFFFFFFU)
#define EDMA3_OWN_DMA_CHANNELS_0_M3VIDEO    (0xFFFFFFFFU)
#define EDMA3_OWN_DMA_CHANNELS_0_M3VPSS    (0xFFFFFFFFU)
/* Channels 32 to 63 */
#define EDMA3_OWN_DMA_CHANNELS_1_A8    (0xFFFFFFFFU)
#define EDMA3_OWN_DMA_CHANNELS_1_DSP   (0xFFFFFFFFU)
#define EDMA3_OWN_DMA_CHANNELS_1_M3VIDEO    (0xFFFFFFFFU)
#define EDMA3_OWN_DMA_CHANNELS_1_M3VPSS    (0xFFFFFFFFU)

/* Defines for Own QDMA channels For different cores */
#define EDMA3_OWN_QDMA_CHANNELS_0_A8    (0x000000FFU)
#define EDMA3_OWN_QDMA_CHANNELS_0_DSP   (0x000000FFU)
#define EDMA3_OWN_QDMA_CHANNELS_0_M3VIDEO    (0x000000FFU)
#define EDMA3_OWN_QDMA_CHANNELS_0_M3VPSS    (0x000000FFU)

/* Defines for Own TCCs For different cores */
#define EDMA3_OWN_TCC_0_A8    (0xFFFFFFFFU)
#define EDMA3_OWN_TCC_0_DSP   (0xFFFFFFFFU)
#define EDMA3_OWN_TCC_0_M3VIDEO    (0xFFFFFFFFU)
#define EDMA3_OWN_TCC_0_M3VPSS    (0xFFFFFFFFU)
/* Channels 32 to 63 */
#define EDMA3_OWN_TCC_1_A8    (0xFFFFFFFFU)
#define EDMA3_OWN_TCC_1_DSP   (0xFFFFFFFFU)
#define EDMA3_OWN_TCC_1_M3VIDEO    (0xFFFFFFFFU)
#define EDMA3_OWN_TCC_1_M3VPSS    (0xFFFFFFFFU)

/* Defines for Reserved DMA channels For different cores */
/* channels  0 to 31 */
#define EDMA3_RESERVED_DMA_CHANNELS_0_A8    (EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0)
#define EDMA3_RESERVED_DMA_CHANNELS_0_DSP   (EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0)
#define EDMA3_RESERVED_DMA_CHANNELS_0_M3VIDEO    (0x00U)
#define EDMA3_RESERVED_DMA_CHANNELS_0_M3VPSS    (0x00U)
/* Channels 32 to 63 */
#define EDMA3_RESERVED_DMA_CHANNELS_1_A8    (EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1)
#define EDMA3_RESERVED_DMA_CHANNELS_1_DSP   (EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1)
#define EDMA3_RESERVED_DMA_CHANNELS_1_M3VIDEO    (0x00U)
#define EDMA3_RESERVED_DMA_CHANNELS_1_M3VPSS    (0x00U)

/* Defines for RESERVED QDMA channels For different cores */
#define EDMA3_RESERVED_QDMA_CHANNELS_0_A8    (0x00U)
#define EDMA3_RESERVED_QDMA_CHANNELS_0_DSP   (0x00U)
#define EDMA3_RESERVED_QDMA_CHANNELS_0_M3VIDEO    (0x00U)
#define EDMA3_RESERVED_QDMA_CHANNELS_0_M3VPSS    (0x00U)

/* Defines for RESERVED TCCs For different cores */
#define EDMA3_RESERVED_TCC_0_A8    (EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0)
#define EDMA3_RESERVED_TCC_0_DSP   (EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_0)
#define EDMA3_RESERVED_TCC_0_M3VIDEO    (0x00U)
#define EDMA3_RESERVED_TCC_0_M3VPSS    (0x00U)
/* Channels 32 to 63 */
#define EDMA3_RESERVED_TCC_1_A8    (EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1)
#define EDMA3_RESERVED_TCC_1_DSP   (EDMA3_DMA_CHANNEL_TO_EVENT_MAPPING_1)
#define EDMA3_RESERVED_TCC_1_M3VIDEO    (0x00U)
#define EDMA3_RESERVED_TCC_1_M3VPSS    (0x00U)

/* Driver Instance Initialization Configuration */
EDMA3_DRV_InstanceInitConfig sampleInstInitConfig[NUM_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] =
    {
		/* EDMA3 INSTANCE# 0 */
		{
			/* Resources owned/reserved by region 0 (Configuration for Ti814x A8 Core)*/
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
				{EDMA3_OWN_DMA_CHANNELS_0_A8, EDMA3_OWN_DMA_CHANNELS_1_A8},

				/* ownQdmaChannels */
				/* 31     0 */
				{EDMA3_OWN_QDMA_CHANNELS_0_A8},

				/* ownTccs */
				/* 31     0     63    32 */
				{EDMA3_OWN_TCC_0_A8, EDMA3_OWN_TCC_1_A8},

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
				{EDMA3_RESERVED_DMA_CHANNELS_0_A8, EDMA3_RESERVED_DMA_CHANNELS_1_A8},

				/* resvdQdmaChannels */
				/* 31     0 */
				{EDMA3_RESERVED_QDMA_CHANNELS_0_A8},

				/* resvdTccs */
				/* 31     0     63    32 */
				{EDMA3_RESERVED_TCC_0_A8, EDMA3_RESERVED_TCC_1_A8},
			},

	        /* Resources owned/reserved by region 1 (Configuration for Ti814x DSP Core)*/
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
		       	{EDMA3_OWN_DMA_CHANNELS_0_DSP, EDMA3_OWN_DMA_CHANNELS_1_DSP},

		        /* ownQdmaChannels */
		        /* 31     0 */
		        {EDMA3_OWN_QDMA_CHANNELS_0_DSP},

		        /* ownTccs */
		        /* 31     0     63    32 */
		        {EDMA3_OWN_TCC_0_DSP, EDMA3_OWN_TCC_1_DSP},

		        /* resvdPaRAMSets */
		        /* 31     0     63    32     95    64     127   96 */
		        {0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
		        /* 159  128     191  160     223  192     255  224 */
		         0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
		        /* 287  256     319  288     351  320     383  352 */
		         0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
		        /* 415  384     447  416     479  448     511  480 */
		         0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,},

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

	        /* Resources owned/reserved by region 4 (Configuration for Ti814x M3VIDEO Core)*/
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
				{EDMA3_OWN_DMA_CHANNELS_0_M3VIDEO, EDMA3_OWN_DMA_CHANNELS_1_M3VIDEO},

				/* ownQdmaChannels */
				/* 31     0 */
				{EDMA3_OWN_QDMA_CHANNELS_0_M3VIDEO},

				/* ownTccs */
				/* 31     0     63    32 */
				{EDMA3_OWN_TCC_0_M3VIDEO, EDMA3_OWN_TCC_0_M3VIDEO},

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
				{EDMA3_RESERVED_DMA_CHANNELS_0_M3VIDEO, EDMA3_RESERVED_DMA_CHANNELS_1_M3VIDEO},

				/* resvdQdmaChannels */
				/* 31     0 */
				{EDMA3_RESERVED_QDMA_CHANNELS_0_M3VIDEO},

				/* resvdTccs */
				/* 31     0     63    32 */
				{EDMA3_RESERVED_TCC_0_M3VIDEO, EDMA3_RESERVED_TCC_1_M3VIDEO},
			},

	        /* Resources owned/reserved by region 5 (Configuration for Ti814x M3VPSS Core)*/
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
				{EDMA3_OWN_DMA_CHANNELS_0_M3VPSS, EDMA3_OWN_DMA_CHANNELS_1_M3VPSS},

				/* ownQdmaChannels */
				/* 31     0 */
				{EDMA3_OWN_QDMA_CHANNELS_0_M3VPSS},

				/* ownTccs */
				/* 31     0     63    32 */
				{EDMA3_OWN_TCC_0_M3VPSS, EDMA3_OWN_TCC_1_M3VPSS},

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
EDMA3_DRV_GblXbarToChanConfigParams sampleXbarChanInitConfig[NUM_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] =
{
    /* EDMA3 INSTANCE# 0 */
    {
        /* Event to channel map for region 0 */
        {
            {-((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), 26, 27, -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1)}
        },
        /* Event to channel map for region 1 */
        {
            {-((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), 26, 27, -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1)}
        },
        /* Event to channel map for region 2 */
        {
            {-((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1)}
        },
        /* Event to channel map for region 3 */
        {
            {-((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1)}
        },
        /* Event to channel map for region 4 */
        {
            {-((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1)}
        },
        /* Event to channel map for region 5 */
        {
            {-((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1)}
        },
        /* Event to channel map for region 6 */
        {
            {-((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1)}
        },
        /* Event to channel map for region 7 */
        {
            {-((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1),
            -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1), -((int32_t)1)}
        },
    }
};

/* End of File */

