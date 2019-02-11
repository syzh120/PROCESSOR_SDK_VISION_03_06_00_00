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
 *  \ingroup BSP_DRV_VPS_API
 *  \defgroup BSP_DRV_VPS_M2M_API M2M API
 *
 *  This modules define APIs to VPE memory to memory driver in VPS.
 *
 *  M2M VPE driver supports the following FVID2 APIs
 *  (see also \ref BSP_DRV_FVID2_API)
 *
 * - <b> Creating the driver </b> - Fvid2_create()
 *   <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>drvId</td>
 *      <td>\ref FVID2_VPS_M2M_DRV</td>
 *    </tr>
 *    <tr>
 *      <td>instanceId</td>
 *      <td>
 *          In case of VPE, instance ID is \ref VPS_M2M_INST_VPE1
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>createArgs</td>
 *      <td>
 *      Vps_M2mCreateParams *
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>createStatusArgs</td>
 *      <td>
 *      Vps_M2mCreateStatus *
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>cbParams</td>
 *      <td>
 *      Fvid2_CbParams *
 *
 *      When Fvid2_CbParams.cbFxn is set, Fvid2_CbParams.cbFxn
 *      gets called for every request completion.
 *
 *      </td>
 *    </tr>
 *  </table>
 *  \ref Fvid2_Handle returned by Fvid2_create() is used in subsequent FVID2
 *  APIs
 *
 * - <b> Deleting the driver </b> - Fvid2_delete()
 *  <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>handle</td>
 *      <td>M2M driver handle</td>
 *    </tr>
 *    <tr>
 *      <td>deleteArgs</td>
 *      <td>NOT USED, set to NULL</td>
 *    </tr>
 *  </table>
 *
 * - <b> Stopping the driver </b> - Fvid2_stop()
 *  <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>handle</td>
 *      <td>M2M driver handle</td>
 *    </tr>
 *    <tr>
 *      <td>cmdArgs</td>
 *      <td>NOT USED, set to NULL</td>
 *    </tr>
 *  </table>
 *
 *  - <b> Controlling the driver </b> - Fvid2_control() <br>
 *  See \ref BSP_DRV_IOCTL_VPS_M2M_VPE for the list of IOCTLs supported by the
 *  driver.
 *
 *  M2M driver application flow is as follows
 *
 *  - <b> Init all required modules by calling respective module init
 *    functions </b>
 *  - <b> Create driver using Fvid2_create() </b>
 *  - <b> Set driver specific parameters using Fvid2_control() </b> <br>
 *        In case of M2M VPE driver, set the VPE parameters using
 *        \ref IOCTL_VPS_M2M_SET_VPE_PARAMS
 *  - <b> Set Scaler coefficient using Fvid2_control() using
 *        \ref IOCTL_VPS_SET_COEFFS </b>
 *  - <b> Allocate DEI context buffers when DEI is enabled using
 *        \ref IOCTL_VPS_GET_DEI_CTX_INFO and
 *        \ref IOCTL_VPS_SET_DEI_CTX_BUF </b>
 *  - <b> Provide frames for processing using Fvid2_processFrames() </b>
 *  - <b> Dequeue processed frame using Fvid2_getProcessedFrames() </b>
 *  - <b> Stop capture using Fvid2_stop() and flush the input frames
 *        using Fvid2_getProcessedFrames() </b>
 *  - <b> Free the DEI context buffers when DEI is enabled using
 *        \ref IOCTL_VPS_GET_DEI_CTX_INFO and
 *        \ref IOCTL_VPS_GET_DEI_CTX_BUF </b>
 *  - <b> Delete M2M driver using Fvid2_delete() </b>
 *  - <b> De-Init modules by calling respective module de-init functions </b>
 *
 *  @{
 */

/**
 *  \file vps_m2m.h
 *
 *  \brief Interface generic memory to memory driver.
 */

#ifndef VPS_M2M_H_
#define VPS_M2M_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/drv/vps/include/common/bsp_cfgMem.h>

/* ========================================================================== */
/* Include HW specific config constants, structures                           */
/* ========================================================================== */
#ifdef VPS_VPE_BUILD
#include <ti/drv/vps/include/vpe/vps_m2mVpe.h>
#endif  /* #ifdef VPS_VIP_BUILD */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Maximum number of handles supported by M2M driver per
 *  driver instance.
 *  Note: This is a read only macro. Don't modify the value of this macro.
 */
#define VPS_M2M_MAX_HANDLE_PER_INST     (16U)

/**
 *  \brief Maximum number of channels that could be allocated per instance.
 *  This macro is used in allocation of memory pool objects and
 *  is assumed that if more that one handle is opened per instance, then the
 *  channel memory will be shared across handles.
 *  Note: This is a read only macro. Don't modify the value of this macro.
 */
#define VPS_M2M_MAX_CH_PER_INST         (40U)

/**
 *  \brief Maximum number of channels that could be allocated per handle.
 *  The total number of channels that could be allocated for all the handles
 *  for an instance should be less than VPS_M2M_MAX_CH_PER_INST.
 *  Note: This is a read only macro. Don't modify the value of this macro.
 */
#define VPS_M2M_MAX_CH_PER_HANDLE       (20U)

/** \brief Default max number of frames that can be queued per channel. */
#define VPS_M2M_DEF_QUEUE_LEN_PER_CH    (BSP_CFG_M2M_VPE_QUEUE_LEN_PER_CH)

/** \brief VPE M2M driver IOCTL base. */
#define VPS_M2M_VPE_IOCTL_BASE          (VPS_M2M_IOCTL_BASE + 0x0100U)

/** \brief Maximum number of M2M scaler instances. */
#define VPS_M2M_SCALER_ID_MAX           (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vps_M2mCreateParams
 *  \brief M2M create parameter structure to be passed to the
 *  driver at the time of mem to mem driver create call.
 */
typedef struct
{
    UInt32 chInQueueLength;
    /**< [IN] Maximum number of request/frame per channel that can be submitted
     *   for M2M operation without having to dequeue the requests. */
    UInt32 numCh;
    /**< Number of channels to be supported by handle. */
    UInt32 isDeiFmdEnable;
    /**< Flag to indicate whether DEI FMD is enabled or not so that driver
     *   could use this to register for FMD interrupt.
     *   Possible values are TRUE/FALSE.
     *   Only the first handle of an instance takes effect and the
     *   sunsequent handle should set the same value as that of the first
     *   handle. */
} Vps_M2mCreateParams;

/**
 *  sturct Vps_M2mCreateStatus
 *  \brief Create status for the M2M create call. This should be
 *  passed to the create function as a create status argument while creating
 *  the driver.
 */
typedef struct
{
    Int32  retVal;
    /**< Return value of create call. */
    UInt32 maxHandles;
    /**< Maximum number of handles supported by driver per instance. */
    UInt32 maxChPerHandle;
    /**< Maximum number of channels that can be supported/submitted per
     *   handle. Note that the the maximum number of channels will be
     *   shared between handles if more than one handle is opened.
     *   This is to avoid unnecessary wastage memory allocation. */
    UInt32 maxSameChPerRequest;
    /**< Maximum number of same channels that can be submitted for processing
     *   per request. */
} Vps_M2mCreateStatus;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_M2mCreateParams structure init function.
 *
 *  \param createPrms   [IN] Pointer to #Vps_M2mCreateParams structure.
 *
 */
static inline void VpsM2mCreateParams_init(Vps_M2mCreateParams *createPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsM2mCreateParams_init(Vps_M2mCreateParams *createPrms)
{
    if (NULL != createPrms)
    {
        createPrms->chInQueueLength = VPS_M2M_DEF_QUEUE_LEN_PER_CH;
        createPrms->numCh           = 1U;
        createPrms->isDeiFmdEnable  = (UInt32) FALSE;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_M2M_H_ */

/*  @}  */
