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
 *  \file vpsdrv_m2mVpePriv.h
 *
 *  \brief VPS VPE M2M driver internal header file.
 */

/* Non Shadow and shadow config descriptors are updated by driver.
 * Non Shadow and Shadow overlay memories are updated by respective cores.
 * Data descriptors are updated by respective cores.
 * Sync on channels are updated by driver.
 * Send interrupt is added by the MLM to wait for the
 * request to get complete and trigger interrupt once the request gets
 * complete.
 * There are VPSMDRV_VPE_RT_COEFF_CFG_DESC_PER_SC coeff descriptors
 * needed for each core in the path that has a scaler.
 * See vps_m2mVpe.h: Core 0 (VPSMDRV_VPE_VPE_CORE_IDX) may have scaler enabled.
 * If scaler is enabled for the core, the horizontal and vertical scaler
 * coefficient descriptors are present. Otherwise they are not present in the
 * descriptor list.
 * Below layout is shown for per channel configuration
 *
 *    |------------|   |-----------------------------|
 *    |(optional)  |-->|Overlay memory: This is in   |
 *    |Ch 1 Core 0 |   |default coeffs memory in HAL |
 *    |coeff desc  |   |-----------------------------|
 *    |horizontal  |
 *    |------------|   |-----------------------------|
 *    |(optional)  |-->|Overlay memory: This is in   |
 *    |Ch 1 Core 0 |   |default coeffs memory in HAL |
 *    |coeff desc  |   |-----------------------------|
 *    |vertical    |
 *    |------------|   |-----------------------------|
 *    |(optional)  |-->|Overlay memory: This is in   |
 *    |Ch 1 Core 2 |   |default coeffs memory in HAL |
 *    |coeff desc  |   |-----------------------------|
 *    |horizontal  |
 *    |------------|   |-----------------------------|
 *    |(optional)  |-->|Overlay memory: This is in   |
 *    |Ch 1 Core 2 |   |default coeffs memory in HAL |
 *    |coeff desc  |   |-----------------------------|
 *    |vertical    |
 *    |------------|      |------------|
 *    |Ch 1        |----->|Non Shadow  |
 *    |Non-Shadow  |      |Ovly memory |
 *    |Config Desc |      |------------|
 *    |------------|   |------------------|
 *    |Ch 1 shadow |-->|Shadow overlay    |
 *    |config desc |   |memory for Core 1 |
 *    |            |   |and Core 2        |
 *    |------------|   |------------------|
 *    |-------------------|
 *    |Core 0             |
 *    |Ch1 out descriptors|
 *    |-------------------|
 *    |Core 1 (optional)  |
 *    |Ch1 out descriptors|
 *    |-------------------|
 *    |Core 2 (optional)  |
 *    |Ch1 out descriptors|
 *    |-------------------|
 *    |Core 0             |
 *    |Ch1 in  descriptors|
 *    |-------------------|
 *    |Core 1 (optional)  |
 *    |Ch1 in  descriptors|
 *    |-------------------|
 *    |Core 2 (optional)  |
 *    |Ch1 in  descriptors|
 *    |-------------------|
 *    |Core 0             |
 *    |Ch1 multi-window   |
 *    |descriptors        |
 *    |-------------------|
 *    |Core 1 (optional)  |
 *    |Ch1 multi-window   |
 *    |descriptors        |
 *    |-------------------|
 *    |Core 2 (optional)  |
 *    |Ch1 multi-window   |
 *    |descriptors        |
 *    |-------------------|
 *    |------------|
 *    |Ch1 SOCH    |
 *    |descriptors |
 *    |------------|
 *    |Ch1 rld desc|
 *    --------------
 *          |
 *          |
 *          |---->|------------|   |-----------------------------|
 *                |(optional)  |-->|Overlay memory: This is in   |
 *                |Ch 1 Core 0 |   |default coeffs memory in HAL |
 *                |coeff desc  |   |-----------------------------|
 *                |horizontal  |
 *                |------------|   |-----------------------------|
 *                |(optional)  |-->|Overlay memory: This is in   |
 *                |Ch 1 Core 0 |   |default coeffs memory in HAL |
 *                |coeff desc  |   |-----------------------------|
 *                |vertical    |
 *                |------------|   |-----------------------------|
 *                |(optional)  |-->|Overlay memory: This is in   |
 *                |Ch 1 Core 2 |   |default coeffs memory in HAL |
 *                |coeff desc  |   |-----------------------------|
 *                |horizontal  |
 *                |------------|   |-----------------------------|
 *                |(optional)  |-->|Overlay memory: This is in   |
 *                |Ch 1 Core 2 |   |default coeffs memory in HAL |
 *                |coeff desc  |   |-----------------------------|
 *                |vertical    |
 *                |------------|      |------------|
 *                |Ch 2        |----->|Non Shadow  |
 *                |Non-Shadow  |      |Ovly memory |
 *                |Config Desc |      |------------|
 *                |------------|   |------------------|
 *                |Ch 1 shadow |-->|Shadow overlay    |
 *                |config desc |   |memory for Core 1 |
 *                |            |   |and Core 2        |
 *                |------------|   |------------------|
 *                |-------------------|
 *                |Core 0             |
 *                |Ch2 out descriptors|
 *                |-------------------|
 *                |Core 1 (optional)  |
 *                |Ch2 out descriptors|
 *                |-------------------|
 *                |Core 2 (optional)  |
 *                |Ch2 out descriptors|
 *                |-------------------|
 *                |Core 0             |
 *                |Ch2 in  descriptors|
 *                |-------------------|
 *                |Core 1 (optional)  |
 *                |Ch2 in  descriptors|
 *                |-------------------|
 *                |Core 2 (optional)  |
 *                |Ch2 in  descriptors|
 *                |-------------------|
 *                |Core 0             |
 *                |Ch2 multi-window   |
 *                |descriptors        |
 *                |-------------------|
 *                |Core 1 (optional)  |
 *                |Ch2 multi-window   |
 *                |descriptors        |
 *                |-------------------|
 *                |Core 2 (optional)  |
 *                |Ch2 multi-window   |
 *                |descriptors        |
 *                |-------------------|
 *                |------------|
 *                |Ch2 SOCH    |
 *                |descriptors |
 *                |------------|
 *                |Ch2 rld desc|
 *                --------------
 *                      |
 *                      |
 *                      |--------|-----------------|
 *                               |Send Interrupt   |
 *                               |-----------------|
 */

#ifndef VPSDRV_M2MVPEPRIV_H_
#define VPSDRV_M2MVPEPRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_utilsQue.h>
#include <ti/drv/vps/src/vpslib/common/vps_resrcMgr.h>
#include <ti/drv/vps/include/common/bsp_cfgMem.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/vps_control.h>
#include <ti/drv/vps/include/vpe/vps_m2m.h>
#include <ti/drv/vps/src/vpslib/vpecore/vpscore_m2m.h>
#include <ti/drv/vps/src/vpslib/vpecore/vpscore_vpe.h>
#include <ti/drv/vps/src/vpslib/vpecore/vpscore_vpeWb.h>
#include <vpedrv/vps_mlm.h>
#include <vpedrv/vps_m2mInt.h>
#include <vpedrv/vpsdrv_m2mSlice.h>
#include <vpedrv/vpsdrv_m2mVpe.h>
#include <vpedrv/src/vpsdrv_m2mVpeFmd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Maximum number of effective driver instance - one VPE paths.
 */
#define VPSMDRV_VPE_MAX_EFF_INST        ((UInt32) 1U)

/** \brief Maximum number of inputs for this driver. */
#define VPSMDRV_VPE_MAX_INPUTS          ((UInt32) 1U)

/** \brief Maximum number of outputs for this driver. */
#define VPSMDRV_VPE_MAX_OUTPUTS         ((UInt32) 1U)

/**
 *  \brief Maximum number of descriptor set supported by driver per channel.
 *  If all the sets are consumed subsequent requests will be placed in driver
 *  queue.
 *
 *  Currently only one set is supported. This is because when in
 *  deinterlacing mode, a request can't have channel which is already submitted
 *  in previous requests as the compressed previous field size is unknown at
 *  the time of programming the second set. Since this is not taken care
 *  in the driver, restricting the set to 1 will make sure requests are
 *  automatically serialized.
 */
#define VPSMDRV_VPE_MAX_DESC_SET        ((UInt32) 1U)

/** \brief Macro representing invalid descriptor set. */
#define VPSMDRV_VPE_INVALID_DESC_SET    ((UInt32) 0xFFFFFFFFU)

/** \brief Maximum number of context fields required for de-interlacing. */
#define VPSMDRV_VPE_MAX_FIELD_CONTEXT   ((UInt32) 2U)

/**
 *  \brief Flag to indicate duplicated context fields. In cases where we do not
 *  enough context fields but would require to de-interlace, we used the
 *  current field as context.
 */
#define VPSMDRV_VPE_DUPE_FIELD_CONTEXT  ((UInt32) 0x0FFFFFFFU)

/**
 *  \brief Configures the instance of inFrameList to be used to return,
 *  context fields.
 */
#define VPSMDRV_VPE_INST_IN_FRAME_LIST_USED ((UInt32) 0U)

/**
 *  \brief Maximum number of shadow config descriptor required by driver
 *  to configure shadow memory per channel or per handle.
 */
#define VPSMDRV_VPE_MAX_SHW_CFG_DESC    ((UInt32) 1U)

/**
 *  \brief Maximum number of non-shadow config descriptor required by driver
 *  to configure non-shadow memory per channel or per handle.
 */
#define VPSMDRV_VPE_MAX_NSHW_CFG_DESC   ((UInt32) 1U)

/**
 *  \brief Maximum number of Reload descriptors required by driver
 *  to link multiple channels for each request.
 */
#define VPSMDRV_VPE_MAX_RLD_DESC        ((UInt32) 1U)

/**
 *  \brief Shadow config overlay memory (in bytes) needed by driver for
 *  programming shadow registers for each channel * number of sets
 *  per channel (2 for ping/pong, no scratch memory as same overlay memory
 *  is used for both channel and scratch pad channel).
 *  Caution: Make this a multiple of VPSHAL_VPDMA_CONFIG_PAYLOAD_BYTE_ALIGN so
 *  that each memory pool element will also be aligned to this alignment
 *  when defining the array for this pool.
 */
#define VPSMDRV_VPE_MAX_SHW_OVLY_MEM \
    ((UInt32) (864U * VPSMDRV_VPE_MAX_DESC_SET))

/**
 *  \brief Non shadow config overlay memory (in bytes) needed by driver for
 *  programming non shadow registers for each channel * number of sets
 *  per channel (2 for ping/pong, no scratch memory as same overlay memory
 *  is used for both channel and scratch pad channel).
 *  Caution: Make this a multiple of VPSHAL_VPDMA_CONFIG_PAYLOAD_BYTE_ALIGN so
 *  that each memory pool element will also be aligned to this alignment
 *  when defining the array for this pool.
 *  96  - for programming frame start event of input core
 */
#define VPSMDRV_VPE_MAX_NSHW_OVLY_MEM \
    ((UInt32) ((96U + 320U) * VPSMDRV_VPE_MAX_DESC_SET))

/**
 *  \brief Maximum number of coeff descriptors required by driver
 *  to configure the coefficient memory per channel. The coefficient
 *  configuration shall be done per channel in case config per channel is
 *  selected. One descriptor is used for horizontal, one for vertical, and one
 *  for bilinear scaling coefficients (if applicable).
 */
#define VPSMDRV_VPE_MAX_COEFF_CFG_DESC          ((UInt32) 3U)

/**
 *  \brief Number of coeff descriptors required by driver at runtime per scaler
 *  to configure the coefficient memory per channel. Since vertical
 *  bilinear coefficients are set (if applicable) only once in the beginning, at
 *  runtime only horizontal and vertical coefficient descriptors are required.
 */
#define VPSMDRV_VPE_RT_COEFF_CFG_DESC_PER_SC    ((UInt32) 2U)

/**
 *  \brief Maximum number of coeff descriptors required by driver
 *  at runtime to configure the coefficient memory per channel.
 */
#define VPSMDRV_VPE_MAX_RT_COEFF_CFG_DESC \
    ((UInt32) (VPSMDRV_VPE_RT_COEFF_CFG_DESC_PER_SC * VPS_M2M_SCALER_ID_MAX))

/** \brief Maximum number of handle to allocate. */
#define VPSMDRV_VPE_MAX_HANDLE_MEM_POOL \
    ((UInt32) (VPS_M2M_MAX_HANDLE_PER_INST * VPSMDRV_VPE_MAX_EFF_INST))

/**
 *  \brief Maximum number of channel memory pool to allocate.
 *  Maximum number of instance * maximum number of channels per instance.
 */
#define VPSMDRV_VPE_MAX_CH_MEM_POOL \
    ((UInt32) (VPSMDRV_VPE_MAX_EFF_INST * VPS_M2M_MAX_CH_PER_INST))

/**
 *  \brief Total coefficient descriptor memory required for each instance
 *  to configure the coefficient memory each time ioctl is fired to update
 *  the coefficients.
 */
#define VPSMDRV_VPE_MAX_COEFF_DESC_MEM                                          \
    ((UInt32) ((VPSMDRV_VPE_MAX_COEFF_CFG_DESC * VPSHAL_VPDMA_CONFIG_DESC_SIZE) \
               + VPSHAL_VPDMA_CTRL_DESC_SIZE))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for VPE instance object. */
typedef struct VpsMdrv_VpeInstObj_t VpsMdrv_VpeInstObj;

/** \brief Forward declaration for VPE handle object. */
typedef struct VpsMdrv_VpeHandleObj_t VpsMdrv_VpeHandleObj;

typedef struct
{
    Fvid2_Frame *fieldCtxBuf;
    /**< Application supplied frame Fvid2_Frame pointer, used as context
     *   field for next fields. */
    UInt32       tth;
    /**< Time To Hold - The current field would be used as context field for
     *   next VPSMDRV_VPE_MAX_FIELD_CONTEXT input fields.
     *   Will be initialized with VPSMDRV_VPE_MAX_FIELD_CONTEXT when
     *   de-interlacing operation is completed on the current field and moved
     *   to context buffer place holder.
     *   With evey new input field the tth would be decreased by one for all
     *   the context buffer objects in context FIFO. */
} VpsMdrv_VpeCtxBufObj;

/**
 *  struct VpsMdrv_VpeQueueObj
 *  \brief Structure defining the queue object used in queue/dequeue operation.
 *  Instead of creating process frame list objects, this is used so that
 *  any other information could be queued/dequeued along with the framelist.
 *  Already qElem is added to avoid dynamic allocation of Queue nodes.
 *  It will also hold the necessary MLM params structure instance to submit
 *  the request to the MLM.
 */
typedef struct
{
    BspUtils_QElem        qElem;
    /**< VPS utils queue element used in node addition. */
    VpsMdrv_VpeHandleObj *hObj;
    /**< Reference to the handle object for this queue object. */
    Fvid2_ProcessList     procList;
    /**< FVID2 process frame list to store the incoming/outgoing IO packets. */
    VpsMdrv_QueObjType    qObjType;
    /**< Request type whether it is a frame request or coefficient request. */
    UInt32                descSetInUse;
    /**< Descriptor set used by this queue object. */
    Mlm_SubmitReqInfo     mlmReqInfo;
    /**< MLM submit request info. */
} VpsMdrv_VpeQueueObj;

/**
 *  struct VpsMdrv_VpeChObj
 *  \brief Structure for storing the per channel information like configuration,
 *  descriptors pointers, number of descriptors etc.
 */
typedef struct
{
    UInt32                 chNum;
    /**< Channel Number. */

    Vps_M2mVpeParams       vpePrms;
    /**< VPE configuration parameters for the channel. */
    Vps_ScAdvConfig        scAdvCfg;
    /**< Memory to store the SC advance config. */
    UInt32                 isParamSet;
    /**< Flag to indicate whether the set params IOCTL set is called by
     *   application. */

    void                  *descMem;
    /**< Points to the descriptor memory containing the data, config,
     *   coeff and reload descriptors for all the sets.
     *   This is used for alloc/free call. */
    void                  *nshwOvlyMem;
    /**< Points to the non-shadow overlay memory of the channel for all the
     *   sets. This is used for alloc/free call. */
    void                  *shwOvlyMem;
    /**< Points to the shadow overlay memory of the channel for all the sets.
     *   This is used for alloc/free call. */
    UInt32                 totalDescMem;
    /**< Total descriptor memory in bytes used for all the cores. */
    UInt32                 totalCoeffDescMem;
    /**< Total coefficient descriptor memory in bytes. */
    UInt32                 totalNshwOvlyMem;
    /**< Total non-shadow overlay memory in bytes used for all the cores. */
    UInt32                 totalShwOvlyMem;
    /**< Total shadow overlay memory in bytes used for all the cores. */
    UInt32                 numCoeffDesc;
    /**< Number of coefficient descriptors required for the channel. If
     *   configuration is selected per handle only the first channel of the
     *   handle object will contain valid information for this field. */
    UInt32                 horzCoeffOvlySize[VPSMDRV_VPE_MAX_CORE];
    /**< Size (in bytes) of the coefficient overlay memory required to program
     *   horizontal scaling coefficients. This is required by cores which have
     *   scaler in their paths. */
    UInt32                 vertCoeffOvlySize[VPSMDRV_VPE_MAX_CORE];
    /**< Size (in bytes) of the coefficient overlay memory required to program
     *   vertical scaling coefficients. This is required by cores which have
     *   scaler in their paths. */
    UInt32                 vertBilinearCoeffOvlySize
    [VPSMDRV_VPE_MAX_CORE];
    /**< Size (in bytes) of the coefficient overlay memory required to program
     *   vertical bilinear scaling coefficients. This is required by cores which
     *   have HQ scaler in their paths. */
    Ptr                    horzCoeffMemPtr[VPSMDRV_VPE_MAX_CORE];
    /**< Pointer to the coefficient overlay memory required to program
     *   horizontal scaling coefficients. This is required by cores which have
     *   scaler in their paths. */
    Ptr                    vertCoeffMemPtr[VPSMDRV_VPE_MAX_CORE];
    /**< Pointer to the coefficient overlay memory required to program
     *   vertical scaling coefficients. This is required by cores which have
     *   scaler in their paths. */
    VpsHal_VpdmaConfigDest coeffConfigDest[VPSMDRV_VPE_MAX_CORE];
    /**< Config destination ID used to program the scaler coefficients. */

    Vcore_M2mDeiCtxInfo    vpeCoreCtxInfo;
    /**< DEI context information containing the number of field/MV/MVSTM
     *   buffers needed for deinterlacing operation. This is derived from
     *   cores during opening of cores. */
    Vcore_VpeUpdateContext vpeCoreCtxBuf;
    /**< Place holder for DEI context buffer pointers,
     *   used to program the core descriptors. */

    VpsHal_VpdmaChannel    socChNum[VCORE_M2M_MAX_VPDMA_CH];
    /**< Client on which MLM should wait for the end of frame signal. */
    UInt32                 numVpdmaChannels;
    /**< Size of socChNum array. */

    VpsMdrv_VpeCtxBufObj   ctxFieldFifo
    [VPSMDRV_VPE_MAX_FIELD_CONTEXT + 1U];
    /**< Place holder for context fields
     *   ctxFieldFifo[0] - holds N field - i.e. current field - would become
     *      N - 1 field for the next field
     *   ctxFieldFifo[1] - holds N - 1 context field
     *   ctxFieldFifo[2] - holds N - 2 context field and so on... */
    UInt32                 isCtxFieldInit;
    /**< Flag to indicate if context fields are initialized, Would be set to
     *   TRUE, when de-interlacing for the very first field. Would be
     *   initialized to FALSE at intilization. */
    BspUtils_QueHandle     agedCtxFieldQ;
    /**< Q that holds the context buffer that are no longer needed by the driver
     *   for de-interlacing operation. */
    UInt32                *space4AgedCtxFieldQ;
    /**< Place holder to implement the Q.
     *   Size should be max q depth + 1 as in case of stopping, there could
     *   be conditions where in user has queued max and wants to stop. */

    UInt32                 AgedCtxFieldQ[VPS_M2M_DEF_QUEUE_LEN_PER_CH + 1U];
    /**< Array to hold max q depth + 1 used by space4AgedCtxFieldQ. */

    Vps_DeiCtxInfo         deiCtxInfo;
    /**< DEI context buffer information to be given to application. */
    Vps_DeiCtxBuf          deiCtxBuf;
    /**< DEI context buffer provided by application. */
    UInt32                 isDeiCtxBufSet;
    /**< Flag to indicate whether the DEI context buffers are set by application
     *   or allocated by driver. Used as de-allocating flag in tear down. */
    UInt32                 fldIdx;
    /**< Field buffer index pointing to the N-1 field input. This is used for
     *   rotation of DEI context buffers. */
    UInt32                 mvIdx;
    /**< MV buffer index pointing to the N-1 MV input. This is used for
     *   rotation of DEI context buffers. */
    UInt32                 mvstmIdx;
    /**< MVSTM buffer index pointing to the N-1 MVSTM input. This is used for
     *   rotation of DEI context buffers. */
    UInt32                 prevFldState;
    /**< At the start up, DEI should operate in line-average mode for
     *   the few fields. This variable keeps track of number of frame
     *   submitted to the DEI. It will be initialized to zero at the
     *   start up or at the time of resetting DEI context. */
    UInt32                 dontRotateCtxBuf;
    /**< Flag to indicate whether the context buffers needs to be rotated.
     *   This flag will be set when the compressed buffer size reported by
     *   VPDMA is invalid and in the next frame submission for the channel,
     *   the invalid compressed frame size is not used by not rotating
     *   the context buffers. */

    void                  *firstDesc[VPSMDRV_VPE_MAX_DESC_SET];
    /**< Pointer to the first descriptor in the descriptor layout for the
     *   channel. */
    void                  *coeffDesc
    [VPSMDRV_VPE_MAX_DESC_SET]
    [VPSMDRV_VPE_MAX_RT_COEFF_CFG_DESC];
    /**< Points to the coefficient descriptor pointer. */
    void                  *nshwCfgDesc[VPSMDRV_VPE_MAX_DESC_SET];
    /**< Points to the non shadow config descriptor of the channel. */
    void                  *shwCfgDesc[VPSMDRV_VPE_MAX_DESC_SET];
    /**< Points to the shadow config descriptor of the channel. */
    void                  *sochDesc[VPSMDRV_VPE_MAX_DESC_SET];
    /**< Points to the SOCH control descriptor of the channel. */
    void                  *rldDesc[VPSMDRV_VPE_MAX_DESC_SET];
    /**< Points to the reload descriptor of the channel. */
    Vcore_M2mDescMem       coreDescMem[VPSMDRV_VPE_MAX_DESC_SET]
    [VPSMDRV_VPE_MAX_CORE];
    /**< Structure holding the data descriptor, overlay memory references
     *   for all the cores and for all the sets. */

    UInt32                 isDescDirty[VPSMDRV_VPE_MAX_DESC_SET];
    /**< Flag to indicate whether a descriptor is dirty or not. */

    VpsMdrv_SubFrameChInst slcChObj;
    /**< Instance memory for subframe based porcessing. */
    VpsHal_ScFactorConfig  scFactor[VPS_M2M_SCALER_ID_MAX];
    /**< Scaling factor for this channel based on required scaling ratio for
     *   each scaler for this channel. */
} VpsMdrv_VpeChObj;

/**
 *  struct VpsMdrv_VpeHandleObj_t
 *  \brief Structure for storing the per handle information.
 *  This structure represents the each handle of the driver instance.
 *  It will encapsulate the channel object instances equal to the maximum number
 *  of channels supported by handle and the handle specific elements like
 *  non shadow config descriptor and memory and coeff descriptor and memory.
 */
struct VpsMdrv_VpeHandleObj_t
{
    VpsMdrv_VpeInstObj  *instObj;
    /**< Instance object to which this handle belongs to. */
    VpsMdrv_VpeChObj    *chObjs[VPS_M2M_MAX_CH_PER_HANDLE];
    /**< Pointer to channel objects for this handle. */

    Vps_M2mCreateParams  createPrms;
    /**< Create parameters. */
    Fvid2_DrvCbParams    fdmCbPrms;
    /**< FVID2 driver manager callback function parameters. */

    BspUtilsLinkListObj *reqQ;
    /**< Queue object to put the input requests. */
    BspUtilsLinkListObj *doneQ;
    /**< Queue object to put the processed output requests. */
    BspUtilsLinkListObj *freeQ;
    /**< Queue for queueing all the free queue objects for this handle. */
    BspOsal_SemHandle    ctrlSem;
    /**< Semaphore to block the control command until they are finished.
     *   This will typically used for programming coefficients where the
     *   coefficient update request is submitted to MLM and control ioctl is
     *   waiting for the coefficient request to be completed. */
    BspOsal_SemHandle    stopSyncSem;
    /**< Semaphore to block the FIVD2 stop command until the current transfer
     *   is complete. After this no further pending requests will be
     *   processed. */
    volatile UInt32      numPendReq;
    /**< Number of pending requests to be dequeued by application once
     *   submitted to driver. */
    volatile UInt32      numUnProcessedReq;
    /**< Number of requests yet to be processed by driver. */

    UInt32               isDescSetFree[VPSMDRV_VPE_MAX_DESC_SET];
    /**< Flag to indicate whether the descriptor set is free or not. */

    Vcore_M2mHandle      coreHandle[VPSMDRV_VPE_MAX_CORE];
    /**< Core handles for VPE, VWB cores. */

    volatile UInt32      isStopped;
    /**< Flag to indicate if driver is being stopped, FALSE is normal operation
     *   TRUE to indicate mlmCb not to Q up new requests */
    Fvid2_FrameList      tempFrameList;
    /**< When driver is stopped, all the fields held as context fields would
     *   required to be released back to apps. On stop all the fields are copied
     *   into this frameList and put back as completed qObj. On de-q, the normal
     *   de-q operation is performed and qObj would be released.
     *   frameList required here, as qObj, has processList but not frameList.
     *   Currently assuming that we can have maximum of
     *   VPS_M2M_MAX_CH_PER_HANDLE channel at any time, so a maximum of
     *   VPS_M2M_MAX_CH_PER_HANDLE * 3 context fields requires to be
     *   released to apps. The below compilation gaurd is to ensure that. */
    UInt32               filmMode;
    /**< Flag for DEI FMD enable/disable operation. */
    fmd_reg_data         dei_fmd_reg_blck;
    /**< FMD register data struct. */
    fmd_data             dei_fmd_blck;
    /**< FMD data struct blocks. */

    BspUtilsLinkListObj  freeLlObj;
    /**< Linked List object for freeQ. */
    BspUtilsLinkListObj  reqLlObj;
    /**< Linked List object for reqQ. */
    BspUtilsLinkListObj  doneLlObj;
    /**< Linked List object for doneQ. */
    VpsMdrv_VpeQueueObj  m2mVpeQObj[BSP_CFG_M2M_VPE_QUEUE_LEN_PER_CH];
    /**< Display queue objects. */

#if ((VPS_M2M_MAX_CH_PER_HANDLE * 0x03) >= FVID2_MAX_FRAME_PTR)
#error "VPE M2M IOCTL STOP will not work - Require to increase space to hold " \
    "context fields"
#endif
};

/** \brief Driver structure per instance of driver */
struct VpsMdrv_VpeInstObj_t
{
    UInt32                openCnt;
    /**< Open count. */
    UInt32                initDone;
    /**< Flag to indicate intialization is done or not for an instance. */
    UInt32                numChAllocated;
    /**< Total number of channels allocated per instance. Used for error
     *   checking. */

    UInt32                drvInstId;
    /**< Driver instance ID. */
    UInt32                coreInstId[VPSMDRV_VPE_MAX_CORE];
    /**< VPE, VWB core instance number/ID. */
    const Vcore_M2mOps   *coreOps[VPSMDRV_VPE_MAX_CORE];
    /**< VPE, VWB core function pointers. */

    UInt32                isCoreReq[VPSMDRV_VPE_MAX_CORE];
    /**< Flag to indicate whether a core has to be included for a particular
     *   instance or not. */
    UInt32                numInListReq;
    /**< Number of input frame list required for an instance.
     *   Currently this will be 1 for VPE input core. */
    UInt32                numOutListReq;
    /**< Number of output frame list required for an instance.
     *   Currently this will be 1 for VPE WRBK core. */

    BspOsal_SemHandle     instSem;
    /**< Semaphore to protect the open/close calls. */

    Mlm_Handle            mlmHandle;
    /**< MLM handle. */
    Mlm_ClientInfo        mlmInfo;
    /**< MLM client information for registering to MLM. */

    UInt32                lazyLoadingEnable[VPS_M2M_SCALER_ID_MAX];
    /**< Indicates whether lazy loading of sclaer coefficients is to be enabled.
     *   If TRUE, lazy loading is to be enabled.
     *   If FALSE, lazy loading is to be disabled. */
    UInt32                scalerCoreId[VPS_M2M_SCALER_ID_MAX];
    /**< Indicates the core ID corresponding to the scaler ID passed for scaler
     *   functionality like setting coefficients or enabling/disabling Lazy
     *   Loading.
     *   If this instance of the driver does not have a core supporting either
     *   or both scalers, the value of scalerCoreId would be set to
     *   VPSMDRV_VPE_MAX_CORE, which indicates invalid core ID. */
    VpsHal_ScFactorConfig curScFactor[VPS_M2M_SCALER_ID_MAX];
    /**< Currently configured scaling factor for each scaler in this
     *   instance. */
};

/**
 *  struct VpsMdrv_VpePoolObj
 *  VPE M2M driver memory pool object containing all the statically allocated
 *  objects - used structure to avoid multiple global variables.
 */
typedef struct
{
    VpsMdrv_VpeHandleObj handleMemPool[VPSMDRV_VPE_MAX_HANDLE_MEM_POOL];
    /**< Memory pool for the handle objects. This memory is allocated
     *   statically and is common for all of the instance objects.
     *   Any instance can take any handle object. */
    UInt32               handleMemFlag[VPSMDRV_VPE_MAX_HANDLE_MEM_POOL];
    /**< The flag variable represents whether a handle object is allocated
     *   or not. */
    BspUtils_PoolParams  handlePoolPrm;
    /**< Pool params for handle memory. */

    VpsMdrv_VpeChObj     chMemPool[VPSMDRV_VPE_MAX_CH_MEM_POOL];
    /**< Memory pool for the channel objects. This memory is allocated
     *   statically and is common for all of the instance objects.
     *   Any instance can take any channel object. */
    UInt32               chMemFlag[VPSMDRV_VPE_MAX_CH_MEM_POOL];
    /**< The flag variable represents whether a channel object is allocated
     *   or not. */
    BspUtils_PoolParams  chPoolPrm;
    /**< Pool params for channel memory. */

    UInt32               totalDescMemFlag[VPSMDRV_VPE_MAX_CH_MEM_POOL];
    /**< The flag variable represents whether a handle object is allocated
     *   or not. */
    BspUtils_PoolParams  totalDescMemPoolPrm;
    /**< Pool params for handle memory. */

    UInt32               nshwOvlyDescMemFlag[VPSMDRV_VPE_MAX_CH_MEM_POOL];
    /**< The flag variable represents whether a handle object is allocated
     *   or not. */
    BspUtils_PoolParams  nshwOvlyDescMemPoolPrm;
    /**< Pool params for handle memory. */

    UInt32               shwOvlyDescMemFlag[VPSMDRV_VPE_MAX_CH_MEM_POOL];
    /**< The flag variable represents whether a handle object is allocated
     *   or not. */
    BspUtils_PoolParams  shwOvlyDescMemPoolPrm;
    /**< Pool params for handle memory. */
} VpsMdrv_VpePoolObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * M2M VPE process request APIs
 */
Int32 VpsMdrv_vpeMlmCbFxn(const Mlm_SubmitReqInfo *reqInfo);
Int32 vpsMdrvVpeProcessReq(VpsMdrv_VpeHandleObj *hObj,
                           VpsMdrv_VpeQueueObj  *qObj);
UInt32 vpsMdrvVpeAllocDescSet(VpsMdrv_VpeHandleObj *hObj);
Int32 vpsMdrvVpeFreeDescSet(VpsMdrv_VpeHandleObj *hObj, UInt32 descSet);

/*
 * M2M VPE core APIs
 */
Int32 vpsMdrvVpeOpenCores(VpsMdrv_VpeHandleObj *hObj);
Int32 vpsMdrvVpeCloseCores(VpsMdrv_VpeHandleObj *hObj);
Int32 vpsMdrvVpeConfigCores(VpsMdrv_VpeHandleObj *hObj,
                            VpsMdrv_VpeChObj     *chObj);
Int32 vpsMdrvVpeGetScFactorCfg(VpsMdrv_VpeHandleObj *hObj,
                               VpsMdrv_VpeChObj     *chObj,
                               UInt32                scalerId);
Int32 vpsMdrvVpeDeiRdAdvCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);
Int32 vpsMdrvVpeDeiWrAdvCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);
/* TODO */
#if 0
Int32 vpsMdrvVpeScRdAdvCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);
Int32 vpsMdrvVpeScWrAdvCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);
#endif
Int32 vpsMdrvVpeDeiSetFmdCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);
Int32 vpsMdrvVpeDeiRdFmdStatIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);
Int32 vpsMdrvVpeDeiUpdateFmdIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);
Int32 vpsMdrvVpeSetRangMapRedtCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);
Int32 vpsMdrvVpeGetRangMapRedtCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);

/*
 * M2M VPE private/common APIs
 */
Int32 vpsMdrvVpeInit(UInt32                       numInst,
                     const VpsMdrv_VpeInitParams *initPrms);
Int32 vpsMdrvVpeDeInit(void);

VpsMdrv_VpeInstObj *vpsMdrvVpeGetInstObj(UInt32 instId);

VpsMdrv_VpeHandleObj *vpsMdrvVpeAllocHandleObj(
    const Vps_M2mCreateParams *createPrms,
    VpsMdrv_VpeInstObj        *instObj,
    const Fvid2_DrvCbParams   *fdmCbPrms);
Int32 vpsMdrvVpeFreeHandleObj(VpsMdrv_VpeHandleObj *hObj);

Int32 vpsMdrvVpeAllocCoreMem(VpsMdrv_VpeHandleObj *hObj,
                             VpsMdrv_VpeChObj     *chObj);
Int32 vpsMdrvVpeFreeCoreMem(const VpsMdrv_VpeHandleObj *hObj,
                            VpsMdrv_VpeChObj           *chObj);

Int32 vpsMdrvVpeProgramDesc(VpsMdrv_VpeHandleObj *hObj,
                            VpsMdrv_VpeChObj     *chObj);

void *vpsMdrvVpeAllocCoeffDesc(void);
Int32 vpsMdrvVpeFreeCoeffDesc(void *coeffDesc);

Int32 vpsMdrvVpeCopyVpePrms(VpsMdrv_VpeChObj       *chObj,
                            const Vps_M2mVpeParams *vpePrms);

/*
 * M2M VPE FMD APIs
 */
void fmd_init(const fmd_reg_data *reg_blck, fmd_data *fmd_blck);
void reg_init(fmd_reg_data *reg_blck, const VpsMdrv_VpeHandleObj *hObj);
Int32 VpsMdrv_vpeMlmFmdCbFxn(const Mlm_SubmitReqInfo *reqInfo);

#ifdef __cplusplus
}
#endif

#endif /*  VPSDRV_M2MVPEPRIV_H_ */
