/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file vpshal_vpdmaPriv.h
 *
 *  \brief Private HAL Header file for VPDMA
 *  This file defines internal data-structures for VPDMA
 *
 */

#ifndef VPSHAL_VPDMA_PRIV_H_
#define VPSHAL_VPDMA_PRIV_H_

/* TODO: Interrupt related API pending */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Control the size of trace buffer */
#define VPSHAL_VPDMA_MAX_TRACE_COUNT           (10U)
/* Number of loops to run before time-out */
#define VPSHAL_VPDMA_BUSY_TIMEOUT              (500000U)
/* Number of loops to run when waiting for VPDMA to become free */
#define VPSHAL_VPDMA_BUSY_WAIT                 (5000U)

/**
 *  Macros for limits on various VPDMA features
 */
#define VPSHAL_VPDMA_MAX_LIST                  (8U)
#define VPSHAL_VPDMA_MAX_CLIENTS               (63U)
#define VPSHAL_VPDMA_MAX_SI_SOURCE             (16U)
#define VPSHAL_VPDMA_MAX_LM_FID                (3U)

/**
 *  enum VpsHal_VpdmaDescType
 *  \brief Types of descriptors supported by VPDMA.
 */
typedef enum
{
    VPSHAL_VPDMA_PT_DATA = (0xAU),
    /**< VPDMA Data descriptor */

    VPSHAL_VPDMA_PT_CONFIG = (0xBU),
    /**< VPDMA Config descriptor */

    VPSHAL_VPDMA_PT_CONTROL = (0xCU)
                              /**< VPDMA Control descriptor */
} VpsHal_VpdmaDescType;

/**
 *  enum VpsHal_VpdmaCtrlDescType
 *  \brief This defines the different types of control descriptors supported
 *  by VPDMA.
 *  This can be directly used in descriptor to the set the control
 *  descriptor type */
typedef enum
{
    VPSHAL_VPDMA_CDT_SOC = 0,
    /**< Sync on Client */
    VPSHAL_VPDMA_CDT_SOL,
    /**< Sync on List */
    VPSHAL_VPDMA_CDT_SOR,
    /**< Sync on Register */
    VPSHAL_VPDMA_CDT_SOT,
    /**< Sync on LM Timer */
    VPSHAL_VPDMA_CDT_SOCH,
    /**< Sync on Channel */
    VPSHAL_VPDMA_CDT_INTR_CHANGE,
    /**< Client interrupt change */
    VPSHAL_VPDMA_CDT_SI,
    /**< Send Interrupt */
    VPSHAL_VPDMA_CDT_RL,
    /**< Reload List */
    VPSHAL_VPDMA_CDT_ABT_CHANNEL,
    /**< Abort Channel */
    VPSHAL_VPDMA_CDT_TOGGLE_FID
    /**< Toggle LM Fid */
} VpsHal_VpdmaCtrlDescType;

/**
 *  enum VpsHal_VpdmaDescDirection
 *  \brief Values used in direction field of a VPDMA descriptor
 */
typedef enum
{
    VPSHAL_VPDMA_INBOUND_DATA_DESC = (0x0U),
    /**< Data to be read from memory by the descriptor*/

    VPSHAL_VPDMA_OUTBOUND_DATA_DESC = (0x1U)
                                      /**< Data to be written out to
                                       * memory by the descriptor*/
} VpsHal_VpdmaDescDirection;

/**
 * Overlay creation related macros
 */
#define VPSHAL_VPDMA_ADDR_SET_SIZE                       (4U)
#define VPSHAL_VPDMA_WORD_SIZE                           (4U)
#define VPSHAL_VPDMA_MIN_REG_SET_SIZE                    (4U)
#define VPSHAL_VPDMA_REG_OFFSET_DIFF                     (4U)
/* Maximum number of register in a block in MMR configured */
#define VPSHAL_VPDMA_CONFIG_MMR_MAX_BLOCK_REG            (28U)

#define VPSHAL_VPDMA_FVID2_DT_MAPPING_SIZE 55U
#define VPSHAL_VPDMA_FVID2_DT_MAPPING                         \
    {                                                         \
        {FVID2_DF_RGB16_565, VPSHAL_VPDMA_CHANDT_BGR565},     \
        {FVID2_DF_ARGB16_1555, VPSHAL_VPDMA_CHANDT_BGRA5551}, \
        {FVID2_DF_ARGB16_4444, VPSHAL_VPDMA_CHANDT_BGRA4444}, \
        {FVID2_DF_RGBA16_5551, VPSHAL_VPDMA_CHANDT_ABGR1555}, \
        {FVID2_DF_RGBA16_4444, VPSHAL_VPDMA_CHANDT_ABGR4444}, \
        {FVID2_DF_ARGB24_6666, VPSHAL_VPDMA_CHANDT_BGRA6666}, \
        /* Note: The R and B lines are connected to B and R ports of
         * VPDMA. Hence need to use BGR datatype to capture RGB data and
         * viceversa.
         * Same applies for YUV444 output as well - Y and V are
         * swapped. */                                        \
        {FVID2_DF_RGB24_888, VPSHAL_VPDMA_CHANDT_BGR888},     \
        {FVID2_DF_ARGB32_8888, VPSHAL_VPDMA_CHANDT_BGRA8888}, \
        {FVID2_DF_RGBA24_6666, VPSHAL_VPDMA_CHANDT_ABGR6666}, \
        {FVID2_DF_RGBA32_8888, VPSHAL_VPDMA_CHANDT_ABGR8888}, \
        {FVID2_DF_BGR16_565, VPSHAL_VPDMA_CHANDT_RGB565},     \
        {FVID2_DF_ABGR16_1555, VPSHAL_VPDMA_CHANDT_RGBA5551}, \
        {FVID2_DF_ABGR16_4444, VPSHAL_VPDMA_CHANDT_RGBA4444}, \
        {FVID2_DF_BGRA16_5551, VPSHAL_VPDMA_CHANDT_ARGB1555}, \
        {FVID2_DF_BGRA16_4444, VPSHAL_VPDMA_CHANDT_ARGB4444}, \
        {FVID2_DF_ABGR24_6666, VPSHAL_VPDMA_CHANDT_RGBA6666}, \
        /* Note: The R and B lines are connected to B and R ports of
         * VPDMA. Hence need to use BGR datatype to capture RGB data and
         * viceversa.
         * Same applies for YUV444 output as well - Y and V are
         * swapped. */                                                   \
        {FVID2_DF_BGR24_888, VPSHAL_VPDMA_CHANDT_RGB888},                \
        {FVID2_DF_ABGR32_8888, VPSHAL_VPDMA_CHANDT_RGBA8888},            \
        {FVID2_DF_BGRA24_6666, VPSHAL_VPDMA_CHANDT_ARGB6666},            \
        {FVID2_DF_BGRA32_8888, VPSHAL_VPDMA_CHANDT_ARGB8888},            \
                                                                         \
        {FVID2_DF_BITMAP8, VPSHAL_VPDMA_CHANDT_BITMAP8},                 \
        {FVID2_DF_BITMAP4_LOWER, VPSHAL_VPDMA_CHANDT_BITMAP4_LOWER},     \
        {FVID2_DF_BITMAP4_UPPER, VPSHAL_VPDMA_CHANDT_BITMAP4_UPPER},     \
        {FVID2_DF_BITMAP2_OFFSET0, VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET0}, \
        {FVID2_DF_BITMAP2_OFFSET1, VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET1}, \
        {FVID2_DF_BITMAP2_OFFSET2, VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET2}, \
        {FVID2_DF_BITMAP2_OFFSET3, VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET3}, \
        {FVID2_DF_BITMAP1_OFFSET0, VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET0}, \
        {FVID2_DF_BITMAP1_OFFSET1, VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET1}, \
        {FVID2_DF_BITMAP1_OFFSET2, VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET2}, \
        {FVID2_DF_BITMAP1_OFFSET3, VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET3}, \
        {FVID2_DF_BITMAP1_OFFSET4, VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET4}, \
        {FVID2_DF_BITMAP1_OFFSET5, VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET5}, \
        {FVID2_DF_BITMAP1_OFFSET6, VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET6}, \
        {FVID2_DF_BITMAP1_OFFSET7, VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET7}, \
                                                                         \
        {FVID2_DF_BITMAP8_BGRA32, VPSHAL_VPDMA_CHANDT_BITMAP8_BGRA32},   \
        {FVID2_DF_BITMAP4_BGRA32_LOWER,                                  \
         VPSHAL_VPDMA_CHANDT_BITMAP4_LOWER_BGRA32},                      \
        {FVID2_DF_BITMAP4_BGRA32_UPPER,                                  \
         VPSHAL_VPDMA_CHANDT_BITMAP4_UPPER_BGRA32},                      \
        {FVID2_DF_BITMAP2_BGRA32_OFFSET0,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET0_BGRA32},                    \
        {FVID2_DF_BITMAP2_BGRA32_OFFSET1,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET1_BGRA32},                    \
        {FVID2_DF_BITMAP2_BGRA32_OFFSET2,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET2_BGRA32},                    \
        {FVID2_DF_BITMAP2_BGRA32_OFFSET3,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET3_BGRA32},                    \
        {FVID2_DF_BITMAP1_BGRA32_OFFSET0,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET0_BGRA32},                    \
        {FVID2_DF_BITMAP1_BGRA32_OFFSET1,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET1_BGRA32},                    \
        {FVID2_DF_BITMAP1_BGRA32_OFFSET2,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET2_BGRA32},                    \
        {FVID2_DF_BITMAP1_BGRA32_OFFSET3,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET3_BGRA32},                    \
        {FVID2_DF_BITMAP1_BGRA32_OFFSET4,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET4_BGRA32},                    \
        {FVID2_DF_BITMAP1_BGRA32_OFFSET5,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET5_BGRA32},                    \
        {FVID2_DF_BITMAP1_BGRA32_OFFSET6,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET6_BGRA32},                    \
        {FVID2_DF_BITMAP1_BGRA32_OFFSET7,                                \
         VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET7_BGRA32},                    \
                                                                         \
        {FVID2_DF_YUV422I_YUYV, VPSHAL_VPDMA_CHANDT_YC422},              \
        /* Note: The R and B lines are connected to B and R ports of
         * VPDMA. Hence need to use BGR datatype to capture RGB data and
         * viceversa.
         * Same applies for YUV444 output as well - Y and V are
         * swapped. Since there is no special format for CY444 we are
         * using BGR format itself. */                       \
        {FVID2_DF_YUV444I, VPSHAL_VPDMA_CHANDT_BGR888},      \
        {FVID2_DF_YUV422I_YVYU, VPSHAL_VPDMA_CHANDT_YCb422}, \
        {FVID2_DF_YUV422I_UYVY, VPSHAL_VPDMA_CHANDT_CY422},  \
        {FVID2_DF_YUV422I_VYUY, VPSHAL_VPDMA_CHANDT_CbY422}, \
                                                             \
    }

/* Used to check validity of a write-descriptor */
#define VPSHAL_VPDMA_ERR_PATTERN  ((UInt32) 0xDEADBEEFU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct Vpdma_ListPostTrace
 *  \brief Object to store the trace information about each list post for a
 *  particular list number.
 */
typedef struct
{
    UInt32               totalPosts;
    /**< Total number of list post. */
    UInt32               curIdx;
    /**< Current index - Points to the next element to the last update in the
     *   below arrays. This will be used like a circular array index. */
    Ptr                  listAddr[VPSHAL_VPDMA_MAX_TRACE_COUNT];
    /**< List address. */
    UInt32               listSize[VPSHAL_VPDMA_MAX_TRACE_COUNT];
    /**< List size. */
    Int32                retVal[VPSHAL_VPDMA_MAX_TRACE_COUNT];
    /**< Return value of the post function. */
    VpsHal_VpdmaListType listType[VPSHAL_VPDMA_MAX_TRACE_COUNT];
    /**< Type of list submitted. */
    UInt32               timeStamp[VPSHAL_VPDMA_MAX_TRACE_COUNT];
    /**< Timestamp when the list post happens. */
    UInt32               listStatus[VPSHAL_VPDMA_MAX_TRACE_COUNT];
    /**< List Status */
    UInt32               listWaitCnt;
    /**< Total number of times list has to wait before posting */
    UInt32               maxListWait;
} Vpdma_ListPostTrace;

/**
 *  struct Vpdma_TraceObj
 *  \brief Object to store the trace information of VPDMA HAL.
 */
typedef struct
{
    Vpdma_ListPostTrace listPost[VPSHAL_VPDMA_MAX_LIST];
} Vpdma_TraceObj;

/**
 *  struct Vpdma_Fvid2DTmapping
 *  \brief Structure to maintain FVID2-VPDMA data-type mapping
 */
typedef struct
{
    Fvid2_DataFormat   fvid2DT;
    /**< FVID2 data-type */
    VpsHal_VpdmaChanDT vpdmaDT;
    /**< Vpdma data-type corresponding to FVID2 data-type */
} Vpdma_Fvid2DTmapping;

/**
 *  struct VpsHal_VpdmaOutDataDesc
 *  \brief This is the actual structure of an outbound data descriptor.
 */
typedef struct
{
    UInt32 lineStride      : 16;
    UInt32 oddSkip         : 3;
    UInt32 reserved1       : 1;
    UInt32 evenSkip        : 3;
    UInt32 oneD            : 1;
    UInt32 reserved2       : 1;
    UInt32 notify          : 1;
    UInt32 dataType        : 6;
    UInt32 reserved3       : 32;
    UInt32 address         : 32;
    UInt32 nextChannel     : 9;
    UInt32 priority        : 3;
    UInt32 reserved4       : 3;
    UInt32 descSkip        : 1;
    UInt32 channel         : 9;
    UInt32 direction       : 1;
    UInt32 memType         : 1;
    UInt32 descType        : 5;
    UInt32 useDescReg      : 1;
    UInt32 dropData        : 1;
    UInt32 writeDesc       : 1;
    UInt32 reserved5       : 2;
    UInt32 outDescAddress  : 27;
    UInt32 maxHeight       : 3;
    /**< The Maximum allowable lines per frame */
    UInt32 reserved6       : 1;
    UInt32 maxWidth        : 3;
    /**< The Maximum allowable pixels per line */
    UInt32 reserved7       : 25;
    UInt32 clientSpecific1 : 32;
    UInt32 clientSpecific2 : 32;
} VpsHal_VpdmaOutDataDesc;

/**
 *  struct VpsHal_VpdmaInDataDesc
 *  \brief This is the actual structure of an inbound data descriptor.
 */
typedef struct
{
    UInt32 lineStride      : 16;
    UInt32 oddSkip         : 3;
    UInt32 reserved1       : 1;
    UInt32 evenSkip        : 3;
    UInt32 oneD            : 1;
    UInt32 fieldId         : 1;
    UInt32 notify          : 1;
    UInt32 dataType        : 6;
    UInt32 transferHeight  : 16;
    /**< Maximum transfer height is 2048 */
    UInt32 transferWidth   : 16;
    /**< Maximum transfer width is 4096 */
    UInt32 address         : 32;
    UInt32 nextChannel     : 9;
    UInt32 priority        : 3;
    UInt32 reserved2       : 2;
    UInt32 mosaicMode      : 1;
    UInt32 reserved3       : 1;
    UInt32 channel         : 9;
    UInt32 direction       : 1;
    UInt32 memType         : 1;
    UInt32 descType        : 5;
    UInt32 frameHeight     : 16;
    /**< Maximum transfer height is 2048 */
    UInt32 frameWidth      : 16;
    /**< Maximum transfer width is 4096 */
    UInt32 verticalStart   : 16;
    UInt32 horizontalStart : 16;
    UInt32 clientSpecific1 : 32;
    UInt32 clientSpecific2 : 32;
} VpsHal_VpdmaInDataDesc;

/**
 *  struct VpsHal_VpdmaConfigDesc
 *  \brief This is the actual structure of a Configuration Descriptor.
 *  Used for set configuration for different modules.
 *  This configuration can be used to setting MMR registers or
 *  scaler coefficients.
 */
typedef struct
{
    UInt32 destAddr       : 32;
    UInt32 dataLength     : 16;
    UInt32 reserved1      : 16;
    UInt32 payloadAddress : 32;
    UInt32 payloadLength  : 16;
    UInt32 destination    : 8;
    UInt32 classVal       : 2;
    UInt32 direct         : 1;
    UInt32 descType       : 5;
} VpsHal_VpdmaConfigDesc;

/**
 *  \brief VPDMA address data sub block header in configuration overlay memory.
 */
typedef struct
{
    UInt32 nextClientAddr : 32;
    UInt32 subBlockLength : 16;
    UInt32 reserved1      : 16;
    UInt32 reserved2      : 32;
    UInt32 reserved3      : 32;
} VpsHal_VpdmaSubBlockHeader;

/**
 *  struct VpsHal_VpdmaSyncOnClientDesc
 *  \brief This is the actual structure of a Sync On Client control descriptor.
 *  Used for changing interrupt generation event and then waiting for
 *  that event to occur.
 */
typedef struct
{
    UInt32 reserved1  : 32;
    UInt32 lineCount  : 16;
    UInt32 pixelCount : 16;
    UInt32 event      : 4;
    UInt32 reserved2  : 28;
    UInt32 ctrl       : 4;
    UInt32 reserved3  : 12;
    UInt32 channel    : 9;
    UInt32 reserved4  : 2;
    UInt32 descType   : 5;
} VpsHal_VpdmaSyncOnClientDesc;

/**
 *  struct VpsHal_VpdmaSyncOnListDesc
 *  \brief This is the actual structure of a Sync On List control descriptor.
 *  Used to ensure that multiple lists have all reached a common point.
 *  Need to specify the bit-mask of all the lists to wait for.
 */
typedef struct
{
    UInt32 reserved1 : 32;
    UInt32 reserved2 : 32;
    UInt32 reserved3 : 32;
    UInt32 ctrl      : 4;
    UInt32 reserved4 : 12;
    UInt32 lists     : 9;
    UInt32 reserved5 : 2;
    UInt32 descType  : 5;
} VpsHal_VpdmaSyncOnListDesc;

/**
 *  struct VpsHal_VpdmaSyncOnRegDesc
 *  \brief This is the actual structure of a Sync On Register Ctrl Descriptor.
 *  Used to stall the list till a write to field for specified LIST in the
 *  LIST_STAT_SYNC register is done
 */
typedef struct
{
    UInt32 reserved1 : 32;
    UInt32 reserved2 : 32;
    UInt32 reserved3 : 32;
    UInt32 ctrl      : 4;
    UInt32 reserved4 : 12;
    UInt32 listNum   : 9;
    UInt32 reserved5 : 2;
    UInt32 descType  : 5;
} VpsHal_VpdmaSyncOnRegDesc;

/**
 *  struct VpsHal_VpdmaSyncOnLmTimerDesc
 *  \brief This is the actual structure of a Sync on List Manager Timer Control
 *  Descriptor.
 *  Used to wait for specified number of cycles to elapse from the
 *  current time position.
 */
typedef struct
{
    UInt32 numCycles : 16;
    UInt32 reserved1 : 16;
    UInt32 reserved2 : 32;
    UInt32 reserved3 : 32;
    UInt32 ctrl      : 4;
    UInt32 reserved4 : 23;
    UInt32 descType  : 5;
} VpsHal_VpdmaSyncOnLmTimerDesc;

/**
 *  struct VpsHal_VpdmaSyncOnChannelDesc
 *  \brief This is the actual structure of a Sync on Channel Control Descriptor.
 *  Used to wait for the specified channel to become free.
 *  TODO: (Check) For an outbound descriptor, this ensure data is available in
 *  memory
 */
typedef struct
{
    UInt32 reserved1 : 32;
    UInt32 reserved2 : 32;
    UInt32 reserved3 : 32;
    UInt32 ctrl      : 4;
    UInt32 reserved4 : 12;
    UInt32 channel   : 9;
    UInt32 reserved5 : 2;
    UInt32 descType  : 5;
} VpsHal_VpdmaSyncOnChannelDesc;

/**
 *  struct VpsHal_VpdmaSendIntrDesc
 * \brief  This is the actual structure of a Send Interrupt Control Descriptor.
 *  It causes the VPDMA to generate an interrupt on the list manager controlled
 *  interrupts as specified by the Source Field.
 */
typedef struct
{
    UInt32 reserved1 : 32;
    UInt32 reserved2 : 32;
    UInt32 reserved3 : 32;
    UInt32 ctrl      : 4;
    UInt32 reserved4 : 12;
    UInt32 source    : 9;
    UInt32 reserved5 : 2;
    UInt32 descType  : 5;
} VpsHal_VpdmaSendIntrDesc;

/**
 *  struct VpsHal_VpdmaReloadDesc
 *  \brief This is the actual structure of a Reload Control Descriptor.
 *  It causes descriptors after this descriptor in the original list to be
 *  dropped and a new list to be loaded as specified by the location and size
 *  fields in the descriptor
 */
typedef struct
{
    UInt32 reloadAddr : 32;
    UInt32 listSize   : 16;
    UInt32 reserved1  : 16;
    UInt32 reserved2  : 32;
    UInt32 ctrl       : 4;
    UInt32 reserved3  : 23;
    UInt32 descType   : 5;
} VpsHal_VpdmaReloadDesc;

/**
 *  struct VpsHal_VpdmaAbortDesc
 *  \brief This is the actual structure of a Abort Control Descriptor.
 *  Used to clear channel from issuing further requests.
 *  Any outstanding requests for that channel will complete as originally
 *  scheduled. The ongoing transfer will be aborted within a frame.
 */
typedef struct
{
    UInt32 reserved1 : 32;
    UInt32 reserved2 : 32;
    UInt32 reserved3 : 32;
    UInt32 ctrl      : 4;
    UInt32 reserved4 : 12;
    UInt32 channel   : 9;
    UInt32 reserved5 : 2;
    UInt32 descType  : 5;
} VpsHal_VpdmaAbortDesc;

/**
 *  struct VpsHal_VpdmaToggleLmFidDesc
 *  \brief This is the actual structure of a Toggle LM FID control descriptor.
 *  Used if the clients set their frame source to LM FID.
 *  The read clients will start transmitting data based on the FID signal
 *  inside the LM changing value.
 *  This descriptor will cause the LM to toggle the value of the internal FID.
 */
typedef struct
{
    UInt32 reserved1  : 32;
    UInt32 reserved2  : 32;
    UInt32 lmFidCtrl0 : 2;
    UInt32 lmFidCtrl1 : 2;
    UInt32 lmFidCtrl2 : 2;
    UInt32 reserved3  : 26;
    UInt32 ctrl       : 4;
    UInt32 reserved4  : 23;
    UInt32 descType   : 5;
} VpsHal_VpdmaToggleLmFidDesc;

/**
 *  struct VpsHal_VpdmaChangeClientIntSrc
 *  \brief This is the actual structure Change Client Interrupt Source
 *         control descriptor.
 *         Expected to be used to configure the VPDMA to generate interrupt
 *         after specified number of lines or specified number of pixels.
 *         To get an interrupt after specified number of lines, update
 *         lineCount and set pixelCount to 0x0
 */
typedef struct
{
    UInt32 reserved1  : 32;
    UInt32 lineCount  : 16;
    UInt32 pixelCount : 16;
    UInt32 event      : 4;
    UInt32 reserved2  : 28;
    UInt32 ctrl       : 4;
    UInt32 reserved3  : 12;
    UInt32 source     : 9;
    UInt32 reserved4  : 2;
    UInt32 descType   : 5;
} VpsHal_VpdmaChangeClientIntSrc;

/* ========================================================================== */
/*                        Private Function Declarations                       */
/* ========================================================================== */
/**
 *  VpsHal_vpdmaLoadFirmware
 *  \brief Load VPDMA firmware
 *
 *  This function will be called as part of VpsHal_vpdmaOpen()
 *
 *  If firmware is loaded, it will exit immediately
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param firmwareAddr     Pointer to firmware buffer. TODO: Alignment ???
 *  \param timeout          Loop-count to wait while loading. Set 0 for default.
 *
 *  \return              success     VIP instance's HAL handle
 *                       failure     NULL
 */
Int32 VpsHal_vpdmaLoadFirmware(VpsHal_Handle handle,
                               Ptr firmwareAddr, UInt32 timeout);

/**
 *  VPSHAL_VPDMA_ISREADY
 *  \brief Check if VPDMA is ready or busy loading a list.
 *  This check is required before posting a new list.
 *
 *  \param  regBase    VPDMA register base address
 *
 *  \return            0: If VPDMA is busy; 1: If VPDMA is ready
 *
 */
static inline UInt32 VPSHAL_VPDMA_ISREADY(UInt32 regBase);
static inline UInt32 VPSHAL_VPDMA_ISREADY(UInt32 regBase)
{
    return (HW_RD_FIELD32((regBase) + (UInt32) VPDMA_LIST_ATTR,
                          VPDMA_LIST_ATTR_RDY));
}

/**
 *  VPSHAL_VPDMA_ISLISTBUSY
 *  \brief Check if the specified VPDMA list is busy
 *
 *  \param  regBase    VPDMA register base address
 *  \param  listNum    List to check
 *
 *  \return            0: List is free; 1: List is busy
 *
 */
static inline UInt32 VPSHAL_VPDMA_ISLISTBUSY(UInt32 regBase, UInt32 listNum);
static inline UInt32 VPSHAL_VPDMA_ISLISTBUSY(UInt32 regBase, UInt32 listNum)
{
    return ((HW_RD_REG32((regBase) + (UInt32) VPDMA_LIST_STAT_SYNC) >> \
             ((UInt32) VPDMA_LIST_STAT_SYNC_LIST0_BUSY_SHIFT +
              (listNum))) & 0x1U);
}

/**
 *  VPSHAL_VPDMA_FW_IS_LOADED
 *  \brief Check if the specified VPDMA list is busy
 *
 *  \param  regBase    VPDMA register base address
 *  \param  listNum    List to check
 *
 *  \return            0: List is free; 1: List is busy
 *
 */
static inline UInt32 VPSHAL_VPDMA_FW_IS_LOADED(UInt32 regBase);
static inline UInt32 VPSHAL_VPDMA_FW_IS_LOADED(UInt32 regBase)
{
    return (HW_RD_REG32((regBase) + \
                        (UInt32) VPDMA_PID) &
            VPDMA_PID_VPDMA_LOAD_COMPLETE_MASK);
}

/**
 *  VpsHal_vpdmaCalcBlockInfo
 *  \brief Function to calculate block information for the VPDMA Register
 *  Overlay
 */
void VpsHal_vpdmaCalcBlockInfo(UInt32 *const *regOffset,
                               UInt32         numReg,
                               UInt32        *blockSize,
                               UInt32        *numBlockReg);

/**
 *  VpsHal_vpdmaGetFirmwareAddr
 *  \brief Internal function to select the appropriate firmware version
 */
static UInt16 *VpsHal_vpdmaGetFirmwareAddr(
    VpsHal_VpdmaFirmwareVersion ver,
    UInt32                     *
    vpdmaFirmwareSize);

/**
 *  VpsHal_vpdmaSetTopHandle
 *  \brief Internal function to identify the clock control module which will
 *  be required for the current use-case
 */
static void VpsHal_vpdmaSetTopHandle(VpsHal_Handle handle);

/**
 *  VpsHal_vpdmaReset
 *  \brief Internal function to call VPDMA reset/un-reset by selecting the
 *  appropriate clock control module
 */
static void VpsHal_vpdmaReset(VpsHal_Handle handle, UInt32 enable);

/**
 *  VpsHal_vpdmaClkEn
 *  \brief Internal function to call VPDMA clk enable/disable by selecting the
 *  appropriate clock control module
 */
static void VpsHal_vpdmaClkEn(VpsHal_Handle handle, UInt32 enable);

/**
 *  VpsHal_vpdmaTopEnableVpdmaListCompleteInterrupt
 *  \brief Enable/Disable List loading completion interrupt
 *  in the appropriate Top INTC module
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
static Int32 VpsHal_vpdmaTopEnableVpdmaListCompleteInterrupt(
    VpsHal_Handle handle, UInt32 intrLine, UInt32 listNum, UInt32 enable);

/**
 *  VpsHal_vpdmaTopClearVpdmaListCompleteInterrupt
 *  \brief Clear interrupt for list loading completion
 *  in the appropriate Top INTC module
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
static Int32 VpsHal_vpdmaTopClearVpdmaListCompleteInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum);

/**
 *  VpsHal_vpdmaTopEnableVpdmaListNotifyInterrupt
 *  \brief Enable/Disable interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor) in the appropriate
 *  Top INTC module
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
static Int32 VpsHal_vpdmaTopEnableVpdmaListNotifyInterrupt(
    VpsHal_Handle handle, UInt32 intrLine, UInt32 listNum, UInt32 enable);

/**
 *  VpsHal_vpdmaTopClearVpdmaListNotifyInterrupt
 *  \brief Clear interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor) in the appropriate
 *  Top INTC module
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
static Int32 VpsHal_vpdmaTopClearVpdmaListNotifyInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPSHAL_VPDMA_PRIV_H_ */
