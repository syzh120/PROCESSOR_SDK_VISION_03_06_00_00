/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 */

/**
 *  \file vpshal_isssimcop.h
 *
 *  \brief Common HAL Header file for the SIMCOP.
 *  This file exposes API for the SIMCOP Top and Simcop HW Sequencer.
 *  It is dependent on ISSCtrl file for enabling SIMCOP.
 *
 */

#ifndef VPSHAL_ISS_SIMCOP_H_
#define VPSHAL_ISS_SIMCOP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Maximum number instances of SIMCOP
 */
#define ISSHAL_SIMCOP_MAX_INST                  (1U)

/**
 *  \brief Maximum number of steps supported by hw sequencer.
 */
#define ISSHAL_SIMCOP_HW_SEQ_MAX_STEPS          (4U)

/**
 *  \brief Enum SIMCOP Module Id, used for enabling module.
 */
typedef enum isshalsimcopModule
{
    ISSHAL_SIMCOP_MODULE_DMA = 0x0,
    /*< SIMCOP DMA Module */
    ISSHAL_SIMCOP_MODULE_LDC = 0x1,
    /*< SIMCOP LDC Module */
    ISSHAL_SIMCOP_MODULE_VTNF = 0x9,
    /*< SIMCOP VTNF Module */
    ISSHAL_SIMCOP_MODULE_FORCE_INT = 0x7FFFFFFF
                                     /**< This will ensure enum is not packed,
                                      *will always be contained in int*/
} isshalsimcopModule_t;

/**
 *  \brief Configuration options for interrupt mode
 */
typedef enum isshalsimcopIrqMode
{
    ISSHAL_SIMCOP_IRQ_MODE_OR = 0,
    /**< OR mode of IRQ, The interrupt line is asserted
     *      when one of the events enabled is pending */
    ISSHAL_SIMCOP_IRQ_MODE_AND = 1,
    /**< AND mode of IRQ, The interrupt line is asserted
     *      when all the events enabled are pending */
    ISSHAL_SIMCOP_IRQ_MODE_FORCE_INT = 0x7FFFFFFF
                                       /**< This will ensure enum is not packed,
                                        *will always be contained in int*/
} isshalsimcopIrqMode_t;

/**
 *  \brief Enum for selecting the max burst lenght for LDC input DMA.
 */
typedef enum isshalsimcopLdcMaxBurstLength
{
    ISSHAL_SIMCOP_LDC_MAX_BURST_LEN_B128 = 0x0,
    /**< Max burst length is 128 */
    ISSHAL_SIMCOP_LDC_MAX_BURST_LEN_B96 = 0x1,
    /**< Max burst length is 96 */
    ISSHAL_SIMCOP_LDC_MAX_BURST_LEN_B64 = 0x2,
    /**< Max burst length is 64 */
    ISSHAL_SIMCOP_LDC_MAX_BURST_LEN_B32 = 0x3,
    /**< Max burst length is 32 */
    ISSHAL_SIMCOP_LDC_MAX_BURST_LEN_FORCE_INT = 0x7FFFFFFF
                                                /**< This will ensure enum is
                                                 * *not packed, will always be
                                                 *contained in int*/
} isshalsimcopLdcMaxBurstLength_t;

/**
 *  \brief Enum for selecting DMA Channel.
 */
typedef enum isshalsimcopDmaChan
{
    ISSHAL_SIMCOP_DMA_CHAN_0 = 0x0,
    /**< SIMCOP DMA Channel 0 */
    ISSHAL_SIMCOP_DMA_CHAN_1 = 0x1,
    /**< SIMCOP DMA Channel 1 */
    ISSHAL_SIMCOP_DMA_CHAN_2 = 0x2,
    /**< SIMCOP DMA Channel 2 */
    ISSHAL_SIMCOP_DMA_CHAN_3 = 0x3,
    /**< SIMCOP DMA Channel 3 */
    ISSHAL_SIMCOP_DMA_CHAN_4 = 0x4,
    /**< SIMCOP DMA Channel 4 */
    ISSHAL_SIMCOP_DMA_CHAN_5 = 0x5,
    /**< SIMCOP DMA Channel 5 */
    ISSHAL_SIMCOP_DMA_CHAN_6 = 0x6,
    /**< SIMCOP DMA Channel 6 */
    ISSHAL_SIMCOP_DMA_CHAN_7 = 0x7,
    /**< SIMCOP DMA Channel 7 */
    ISSHAL_SIMCOP_DMA_CHAN_FORCE_INT = 0x7FFFFFFF
                                       /**< This will ensure enum is not packed,
                                        *will always be contained in int*/
} isshalsimcopDmaChan_t;

/**
 *  \brief Enum for selecting DMA Sync for HW Seq.
 */
typedef enum isshalsimcopHwSeqDmaSync
{
    ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_DISABLED = 0x0,
    /**< HW Sequencer DMA sync is disabled */
    ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0_1 = 0x1,
    /**< HW Sequencer: Sync DMA channel 0 and 1 */
    ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0_1_2 = 0x2,
    /**< HW Sequencer: Sync DMA channel 0, 1 and 2 */
    ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0_1_2_3 = 0x3,
    /**< HW Sequencer: Sync DMA channel 0, 1, 2 and 3 */
    ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0 = 0x4,
    /**< HW Sequencer: Sync DMA channel 0 */
    ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_1 = 0x5,
    /**< HW Sequencer: Sync DMA channel 1 */
    ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_2 = 0x6,
    /**< HW Sequencer: Sync DMA channel 2 */
    ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_3 = 0x7,
    /**< HW Sequencer: Sync DMA channel 3 */
    ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_FORCE_INT = 0x7FFFFFFF
                                                     /**< This will ensure enum
                                                      * *is not packed, will
                                                      * *always be contained in
                                                      *int */
} isshalsimcopHwSeqDmaSync_t;

/**
 *  \brief Enum for selecting DMA Offset for HW Sequencer.
 *         Controls DMA bus mapping to image buffers
 *      Do we have image buffer ABCD? Sujith - requires an spec update?
 */
typedef enum isshalsimcopHwSeqDmaOffset
{
    ISSHAL_SIMCOP_HWSEQ_DMA_OFST_ABCDEFGH = 0x0,
    /**< Address offset 0x0000 is mapped to buffer A and 0x7000 to H */
    ISSHAL_SIMCOP_HWSEQ_DMA_OFST_BCDEFGHA = 0x1,
    /**< Address offset 0x0000 is mapped to buffer B and 0x7000 to A */
    ISSHAL_SIMCOP_HWSEQ_DMA_OFST_CDEFGHAB = 0x2,
    /**< Address offset 0x0000 is mapped to buffer C and 0x7000 to B */
    ISSHAL_SIMCOP_HWSEQ_DMA_OFST_DEFGHABC = 0x3,
    /**< Address offset 0x0000 is mapped to buffer D and 0x7000 to C */
    ISSHAL_SIMCOP_HWSEQ_DMA_OFST_EFGHABCD = 0x4,
    /**< Address offset 0x0000 is mapped to buffer E and 0x7000 to D */
    ISSHAL_SIMCOP_HWSEQ_DMA_OFST_FGHABCDE = 0x5,
    /**< Address offset 0x0000 is mapped to buffer F and 0x7000 to E */
    ISSHAL_SIMCOP_HWSEQ_DMA_OFST_GHABCDEF = 0x6,
    /**< Address offset 0x0000 is mapped to buffer G and 0x7000 to F */
    ISSHAL_SIMCOP_HWSEQ_DMA_OFST_HABCDEFG = 0x7,
    /**< Address offset 0x0000 is mapped to buffer H and 0x7000 to G */
    ISSHAL_SIMCOP_HWSEQ_DMA_OFST_FORCE_INT = 0x7FFFFFFF
                                             /**< This will ensure enum is not
                                              * *packed, will always be
                                              * contained
                                              *in int */
} isshalsimcopHwSeqDmaOffset_t;

/**
 *  \brief Enum for selecting DMA Offset for LDC_output.
 *         Controls DMA bus mapping to image buffers
 */
typedef enum isshalsimcopHwSeqLdcImgBufMap
{
    ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_EFGH = 0x0,
    /**< Address offset 0x0000 is mapped to buffer E and 0x3000 to H */
    ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_FGHE = 0x1,
    /**< Address offset 0x0000 is mapped to buffer F and 0x3000 to E */
    ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_GHEF = 0x2,
    /**< Address offset 0x0000 is mapped to buffer G and 0x3000 to F */
    ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_HEFG = 0x3,
    /**< Address offset 0x0000 is mapped to buffer H and 0x3000 to G */
    ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_FORCE_INT = 0x7FFFFFFF
                                                  /**< This will ensure enum is
                                                   * *not packed, will always be
                                                   *contained in int */
} isshalsimcopHwSeqLdcImgBufMap_t;

/**
 *  \brief Enum for selecting DMA Offset for VTNF.
 *         Controls DMA bus mapping to image buffers
 */
typedef enum isshalsimcopHwSeqVtnfImgBufMap
{
    ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_EF = 0x0,
    /**< Address offset 0x0000 is mapped to buffer E and 0x1000 to F */
    ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_FG = 0x1,
    /**< Address offset 0x0000 is mapped to buffer F and 0x1000 to G */
    ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_GH = 0x2,
    /**< Address offset 0x0000 is mapped to buffer G and 0x1000 to H */
    ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_HE = 0x3,
    /**< Address offset 0x0000 is mapped to buffer H and 0x1000 to R */
    ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_FORCE_INT = 0x7FFFFFFF
                                                   /**< This will ensure enum is
                                                    * *not packed, will always
                                                    * be
                                                    *contained in int */
} isshalsimcopHwSeqVtnfImgBufMap_t;

/**
 *  \brief Enum for defining HW Sequencer image buffers
 */
typedef enum isshalsimcopHwSeqImgBuf
{
    ISSHAL_SIMCOP_HWSEQ_IMG_BUF_E = 0x0,
    /**< Image Buffer E */
    ISSHAL_SIMCOP_HWSEQ_IMG_BUF_F = 0x1,
    /**< Image Buffer F */
    ISSHAL_SIMCOP_HWSEQ_IMG_BUF_G = 0x2,
    /**< Image Buffer G */
    ISSHAL_SIMCOP_HWSEQ_IMG_BUF_H = 0x3,
    /**< Image Buffer H */
    ISSHAL_SIMCOP_HWSEQ_MAX_IMG_BUF = 0x4,
    /**< Should be the last macro */
    ISSHAL_SIMCOP_HWSEQ_IMG_BUF_FORCE_INT = 0x7FFFFFFF
                                            /**< This will ensure enum is not
                                             * *packed, will always be contained
                                             *in int */
} isshalsimcopHwSeqImgBuf_t;

/**
 *  \brief Enum for selecting DMA Offset for HW Seq.
 *         Controls DMA bus mapping to image buffers
 */
typedef enum isshalsimcopHwSeqImgBufMap
{
    ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_COPROC_BUS = 0x0,
    /**< Map Image buffers to Co-Processor Bus, so that it can be
     *   accessed by slave port over config bus. */
    ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA = 0x1,
    /**< Map Image buffers to SIMCOP DMA */
    ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O = 0x2,
    /**< Map Image buffers to LDC Output port */
    ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO = 0x3,
    /**< Map Image buffers to VTNF io port */
    ISSHAL_SIMCOP_HWSEQ_IMBUF_MAX_PORT = 0x4,
    /**< Should be the last enum */
    ISSHAL_SIMCOP_HWSEQ_IMBUF_MAX_PORT_FORCE_INT = 0x7FFFFFFF
                                                   /**< This will ensure enum is
                                                    * *not packed, will always
                                                    * be
                                                    *contained in int */
} isshalsimcopHwSeqImgBufMap_t;

/**
 *  \brief Enum for selecting generating/syncing with
 *         START/DONE pulse
 */
typedef enum isshalsimcopDmaHwSyncChan
{
    ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED = 0x0,
    /**< Channel Sync is disabled */
    ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0 = 0x4,
    /**< Sync on channel 0 */
    ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_1 = 0x5,
    /**< Sync on channel 1 */
    ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_2 = 0x6,
    /**< Sync on channel 2 */
    ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_3 = 0x7,
    /**< Sync on channel 3 */
    ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_FORCE_INT = 0x7FFFFFFF
                                                  /**< This will ensure enum is
                                                   * *not packed, will always be
                                                   *contained in int*/
} isshalsimcopDmaHwSyncChan_t;

/**
 *  \brief Enum for selecting channel to link to.
 */
typedef enum isshalsimcopDmaLinkChannel
{
    ISSHAL_SIMCOP_DMA_LINK_DISABLED = 0x0,
    /**< No new channel is linked with this channel */
    ISSHAL_SIMCOP_DMA_LINK_CHANNEL_0 = 0x10,
    /**< Start channel 0 when current channel finishes */
    ISSHAL_SIMCOP_DMA_LINK_CHANNEL_1 = 0x11,
    /**< Start channel 1 when current channel finishes */
    ISSHAL_SIMCOP_DMA_LINK_CHANNEL_2 = 0x12,
    /**< Start channel 2 when current channel finishes */
    ISSHAL_SIMCOP_DMA_LINK_CHANNEL_3 = 0x13,
    /**< Start channel 3 when current channel finishes */
    ISSHAL_SIMCOP_DMA_LINK_CHANNEL_4 = 0x14,
    /**< Start channel 4 when current channel finishes */
    ISSHAL_SIMCOP_DMA_LINK_CHANNEL_5 = 0x15,
    /**< Start channel 5 when current channel finishes */
    ISSHAL_SIMCOP_DMA_LINK_CHANNEL_6 = 0x16,
    /**< Start channel 6 when current channel finishes */
    ISSHAL_SIMCOP_DMA_LINK_CHANNEL_7 = 0x17,
    /**< Start channel 7 when current channel finishes */
    ISSHAL_SIMCOP_DMA_LINK_CHANNEL_FORCE_INT = 0x7FFFFFFF
                                               /**< This will ensure enum is not
                                                * *packed, will always be
                                                *contained in int */
} isshalsimcopDmaLinkChannel_t;

/**
 *  \brief Enum for selecting DMA transfer direction
 */
typedef enum isshalsimcopDmaTransferDirection
{
    ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP = 0x0,
    /**< Direction is System memory -> SIMCOP buffers*/
    ISSHAL_SIMCOP_DMA_DIR_SIMCOP_TO_SYS = 0x1,
    /**< Direction is SIMCOP buffers -> System memory */
    ISSHAL_SIMCOP_DMA_DIR_FORCE_INT = 0x7FFFFFFF
                                      /**< This will ensure enum is not packed,
                                       *will always be contained in int */
} isshalsimcopDmaTransferDirection_t;

/**
 *  enum isshalsimcopInstId_t
 *  \brief Enum to define the various SIMCOP instance.
 */
typedef enum isshalsimcopInstId
{
    ISSHAL_SIMCOP_INST_0 = 0,
    /**< SIMCOP Instance Id 0. */
    ISSHAL_SIMCOP_INST_MAX_ID = 1,
    /**< Max - used for error check. */
    ISSHAL_SIMCOP_INST_FORCE_INT = 0x7FFFFFFF
                                   /**< This will ensure enum is not packed,
                                    *will always be contained in int */
} isshalsimcopInstId_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Instance specific parameters used at the init.
 */
typedef struct isshalsimcopInstParams
{
    uint32_t instId;
    /**< Instance ID for the SIMCOP instance */
    uint32_t simcopBaseAddress;
    /**< BaseAddress of the SIMCOP module */
    uint32_t simcopDmaBaseAddress;
    /**< BaseAddress of the SIMCOP DMA module */
    uint32_t numActiveContext;
    /**< Defines the number of contexts that can be active simultaneously */
    uint32_t numDmaChannels;
    /**< Defined the number of DMA channels supported by SIMCOP DMA */
    uint32_t numIrq;
    /**< Number of IRQ lines supproted by SIMCOP Module */
    uint32_t maxHwSeqSteps;
    /**< Maximum number of hwSeq steps supported */
} isshalsimcopInstParams_t;

/**
 *  struct isshalsimcopOpenParams
 *  \brief Structure to identify a SIMCOP HAL instance.
 */
typedef struct isshalsimcopOpenParams
{
    uint32_t instId;
    /**< Instance ID. For valid values see #isshalsimcopInstId_t. */
} isshalsimcopOpenParams_t;

/**
 *  \brief SIMCOP Hw Sequencer, step parameters.
 */
typedef struct isshalsimcopHwSeqStepParams
{
    uint32_t                         nextStep;
    /**< Next step to be executed after current step.
     *   must be less than ISSHAL_SIMCOP_HW_SEQ_MAX_STEPS
     *   Also used as index into the stepParams array to get
     *   the step configuration for the next step. */
    uint32_t                         enableLdcSync;
    /**< Enable HW synchronization with the LDC module */
    uint32_t                         enableVtnfSync;
    /**< Enable HW synchronization with the VTNF module */
    isshalsimcopHwSeqDmaSync_t       dmaSync;
    /**< Enable HW synchronization with the SIMCOP DMA */
    isshalsimcopHwSeqDmaOffset_t     dmaOfst;
    /**< Controls DMA bus mapping to image buffers */
    isshalsimcopHwSeqImgBufMap_t     imgMap[ISSHAL_SIMCOP_HWSEQ_MAX_IMG_BUF];
    /**< Image buffer switch control */
    isshalsimcopHwSeqLdcImgBufMap_t  ldcImBufMap;
    /**< Image buffer mapping for LDC output buffer */
    isshalsimcopHwSeqVtnfImgBufMap_t vtnfImBufMap;
    /**< Image buffer mapping for VTNF io buffer */

    /* TODO: Add configuration for CPU_SYNC and EXT_SYNC */
} isshalsimcopHwSeqStepParams_t;

/**
 *  \brief SIMCOP Hw Sequencer parameters. Used for executing multiple steps
 *         one by one without sw intervention.
 */
typedef struct isshalsimcopHwSeqParams
{
    uint32_t                      useHwSeq;
    /**< Flag to enable/disabe use of HW Seq
     *   0: no use of hw sequence, manual sequencing
     *   1: use hw sequencer */
    uint32_t                      stepCnt;
    /**< Number of steps executed by the HW sequencer.
     *   must be greater than 0 when useHwSeq is 1 */
    uint32_t                      startStep;
    /**< Used to select the first step number of a sequence,
     *   Also could be used to activate content of a given
     *   set of step registers,
     *   must be less than ISSHAL_SIMCOP_HW_SEQ_MAX_STEPS
     *   Also used as index into the stepParams array to get
     *   the step configuration */
    uint32_t                      numSteps;
    /**< The number of Independent steps.
     *   Essentially, it provides number of valid entries in stepParams array */
    isshalsimcopHwSeqStepParams_t stepParams[ISSHAL_SIMCOP_HW_SEQ_MAX_STEPS];
    /**< HWSEQ Steps parameters */
} isshalsimcopHwSeqParams_t;

/**
 *  \brief SIMCOP DMA Channel parameters.
 *          Depends on the video frames / streams. Configured once for a given
 *          stream.
 */
typedef struct isshalsimcopDmaChannelParams
{
    uint32_t                           channelNum;
    /**< Channel number */
    isshalsimcopDmaHwSyncChan_t        hwStopChCtrl;
    /**< DMA logical channel hardware synchronization.
     *   Generates the DONE pulse on configured channel when current
     *   channel finishes */
    isshalsimcopDmaHwSyncChan_t        hwStartChCtrl;
    /**< DMA logical channel hardware synchronization.
     *   Starts tranfer for this channel when DONE signal is
     *   received on the configured channel */
    isshalsimcopDmaLinkChannel_t       nextChannel;
    /**< Next channel to transfer when current channel finishes */
    isshalsimcopDmaTransferDirection_t direction;
    /**< Direction of transfer,
     *   could be either from memory to simcop buffers or
     *   from simcop buffers to memory */

    uint32_t                           blkWidth;
    /**< Transfer Block Width */
    uint32_t                           blkHeight;
    /**< Transfer Block Height
     *   BlockWidth x blockHeight must be multiple of 16 bytes */
    uint32_t                           numHorzBlks;
    /**< Number of horizontal block to transfer */
    uint32_t                           numVertBlks;
    /**< Number of vertical block to transfer */
    uint32_t                           horzStep;
    /**< Horizontal step counter */
    uint32_t                           vertStep;
    /**< Vertical step counter,
     *   For normal case, step size = block size,
     *   But for overlapping case, step size < block size,
     *   for skipping, step size > block size */
    uint32_t                           initX;
    /**< Initial count for Horizontal step counter */
    uint32_t                           initY;
    /**< Initial count for Vertical step counter */
    Ptr                                sysmemAddr;
    /**< Base address for data in System memory */
    uint32_t                           sysmemStride;
    /**< Stride for data in System memory */
    uint32_t                           simcopmemAddr;
    /**< Base address for data in SIMCOP memory */
    uint32_t                           simcopmemStride;
    /**< Stride for data  in SIMCOP memory */
} isshalsimcopDmaChannelParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  \brief SIMCOP init function. Initializes SIMCOP objects.
 *      This function should be called before calling any of SIMCOP HAL API's.
 *      All global variables are initialized, powers up sub-modules
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshalsimcopInstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopInit(UInt32                          numInst,
                             const isshalsimcopInstParams_t *instPrms,
                             Ptr                             arg);

/**
 *  \brief SIMCOP HAL exit function. Powers down sub-modules of SIMCOP
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopDeInit(VpsHal_Handle handle, Ptr arg);

/**
 *  \brief Function to open given instance for operations.
 *  This function should be called before calling and functional APIs.
 *
 *  \param instPrms      Instance initialization parameters.
 *
 *  \return              Returns handle of type VpsHal_Handle
 *
 */
VpsHal_Handle VpsHal_isssimcopOpen(
    const isshalsimcopOpenParams_t *instPrms,
    Ptr                             arg);

/** TBD
 */
int32_t VpsHal_isssimcopClose(VpsHal_Handle handle);

/* ========================================================================== */
/*                           SIMCOP TOP Functions                             */
/* ========================================================================== */

/**
 *  \brief SIMCOP Module Enable function. Used to power on SIMCOP Modules
 *         like VTNF and LDC.
 *
 *  \param module   Id of the Module
 *  \param flag     TRUE: turn on the module, FALSE: turn off module
 *
 *  \return         Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopEnableModule(VpsHal_Handle        handle,
                                     isshalsimcopModule_t module,
                                     uint32_t             flag);

/**
 *  \brief Used to reset complete SIMCOP module.
 *         Before resetting SIMCOP, must ensure that all requests by VTNF/LDC
 *         are completed. That can be done by
 *         1, Configuring LDC and SIMCOMP DMA in ForceStandBy Mode
 *         2, Call this api
 *
 */
int32_t VpsHal_isssimcopReset(VpsHal_Handle handle);

/**
 *  \brief Function used to set misc LDC Read DMA configuration
 *
 *  \param tagCnt       Limits the maximum number of outstanding LDC
 *                      requests to tagCnt+1 Max Value suported is 15
 *  \param maxBrstLn    the maximum burst length that could be used by LDC
 *  \param isBurstBreak Controls if bursts issued by LDC could cross
 *                      burst length boundaries. When this register is
 *                      set, the LDC module only issues OCP aligned bursts.
 *                      Register can only be used when maxBrstLn is 32, 64
 *                      or 128 bytes
 *
 *  \return         Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopSetLdcReadDmaCfg(
    VpsHal_Handle                   handle,
    uint32_t                        tagCnt,
    isshalsimcopLdcMaxBurstLength_t maxBrstLn,
    uint32_t                        enableBurstBreak);

/**
 *  \brief Function to set the Irq Mode.
 *         Used to set OR and AND mode of IRQ.
 *         OR: The interrupt line is asserted when one of the events
 *             enabled is pending
 *         AND: The interrupt line is asserted when all events enabled
 *              are pending
 *
 *  \param irqNum   IRQ number, it could be 0 to max Irq supporte by
 *                  SIMCOMP Module. Max irq supported by SIMCOP is one
 *                  of the init parameter
 *
 *  \param flag     TRUE: turn on the module, FALSE: turn off module
 *
 *  \return         Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopSetIrqMode(VpsHal_Handle         handle,
                                   uint32_t              irqNum,
                                   isshalsimcopIrqMode_t irqMode);

/**
 *  \brief Used to set the mean bandwidth for LDC Read.
 *
 *  Used to the limit on mean bandwidth (computed over one block)
 *  that the LDC module can request for read from system memory.
 *  0: BW limiter is bypassed
 *  1 to 4095 : maximum number of bytes per cycle multiplied by 2^8
 *
 *  This function should be called only after calling simcopInit Function.
 *
 *  \param bwLimit       Bandwidth Limit.
 *
 *  \return              Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopSetLdcReadBwCtrl(VpsHal_Handle handle,
                                         uint32_t      bwLimit);

/* ========================================================================== */
/*                           HW SEQ Functions                                 */
/* ========================================================================== */

/**
 *  \brief Used to set HW sequencer.
 *
 *  This function should be called only after calling simcopInit Function.
 *
 *  \param hwseqCfg      HW Seq Config.
 *
 *  \return              Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopHwSeqSetConfig(
    VpsHal_Handle handle,
    const isshalsimcopHwSeqParams_t *
    hwSeqCfg);

/**
 *  \brief Used to enable HW sequencer.
 *
 *  This function should be called only after calling simcopInit Function.
 *
 *  \return              Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopHwSeqStart(VpsHal_Handle handle);

/**
 *  \brief Used to stop HW sequencer. Should be used typically to recover
 *         from an error condition
 *
 *  This function should be called only after calling simcopInit Function.
 *
 *  \return              Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopHwSeqStop(VpsHal_Handle handle);

/* ========================================================================== */
/*                           SIMCOP DMA Functions                             */
/* ========================================================================== */

/**
 *  VpsHal_isssimcopDmaSetChannelConfig
 *  \brief Configure DMA parameters for specified SIMCOP instance and
 *         specified channel
 *
 *  \param handle      Valid SIMCOP HAL handle returned by
 *                     VpsHal_isssimcopOpen
 *  \param cfg         DMA channel configuration #isshalsimcopDmaChannelParams_t
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopDmaSetChannelConfig(
    VpsHal_Handle                         handle,
    const isshalsimcopDmaChannelParams_t *cfg);

/**
 *  VpsHal_isssimcopCfgDma
 *  \brief Configure instance specific DMA parameters.
 *
 *  \param instId      Specifies the instance id
 *  \param pInstDmaCfg A non NULL pointer that describes DMA config.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopCfgDma(uint32_t                           instId,
                               const vpsisssimcopDmaCtrlParams_t *pInstDmaCfg);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_ISS_SIMCOP_H_ */
