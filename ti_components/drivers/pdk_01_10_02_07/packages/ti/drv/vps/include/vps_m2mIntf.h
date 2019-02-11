/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014-2015
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
 *  \defgroup BSP_DRV_VPS_M2M_INTF_API M2M Interface API
 *
 *  This modules define APIs to generic memory to memory driver in VPS.
 *
 *  Generic M2M Interface driver supports the following FVID2 APIs
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
 *      <td>\ref FVID2_VPS_COMMON_M2M_INTF_DRV</td>
 *    </tr>
 *    <tr>
 *      <td>instanceId</td>
 *      <td>
 *          Driver specific instance id
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>createArgs</td>
 *      <td>
 *      Vps_M2mIntfCreateParams *
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>createStatusArgs</td>
 *      <td>
 *      Vps_M2mIntfCreateStatus *
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
 *  - <b> Controlling the driver </b> - Fvid2_control() <br>
 *  See \ref BSP_DRV_IOCTL_VPS_COMMON_M2M_INTF for the list of IOCTLs
 *  supported by the driver.
 *
 *  M2M driver application flow is as follows
 *
 *  - <b> Init all required modules by calling respective module init
 *    functions </b>
 *  - <b> Create driver using Fvid2_create() </b>
 *  - <b> Set driver specific parameters using Fvid2_control() </b> <br>
 *  - <b> Provide frames for processing using Fvid2_processRequest() </b>
 *  - <b> Dequeue processed frame using Fvid2_getProcessedRequest() </b>
 *  - <b> Abort the input frames using IOCTL_VPS_M2M_INTF_ABORT control
 *        command() </b>
 *  - <b> Delete M2M driver using Fvid2_delete() </b>
 *  - <b> De-Init modules by calling respective module de-init functions </b>
 *
 *  @{
 */

/**
 *  \file vps_m2mIntf.h
 *
 *  \brief Generic FVID2 Interface for the M2M operations.
 */

#ifndef VPS_M2M_INTF_H_
#define VPS_M2M_INTF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/drv/vps/include/common/bsp_cfgMem.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name M2M interface max limits or defaults.
 *
 *  @{
 */

/**
 *  \brief Maximum number of handles supported by M2M driver per
 *  driver instance.
 *  Note: This is a read only macro. Don't modify the value of this macro.
 */
#define VPS_M2M_INTF_MAX_HANDLE_PER_INST        (16U)

/** \brief Default max number of M2M operation request that can be
 *        queued per handle. */
#define VPS_M2M_INTF_DEF_QUEUE_LEN_PER_CH       ( \
        BSP_CFG_M2M_INTF_QUEUE_LEN_PER_CH)
/** \brief Default max number channels that is supported. */
#define VPS_M2M_INTF_MAX_CH_PER_HANDLE          (10U)

/** \brief M2M Generic Interface IOCTL base.
 *         VPS_M2M_IOCTL_BASE + 0x100U is already used by VPE M2M driver */
#define VPS_M2M_INTF_IOCTL_BASE                 (VPS_M2M_IOCTL_BASE + 0x0200U)

/* @} */

/* M2M IOCTL's */

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_COMMON_M2M_INTF
 *  @{
 */

/**
 *  \brief Abort m2m driver and dequeue all frames including those that
 *  are not processed.
 *
 *  \warning This command is not yet implemented.
 *  \warning This command cannot be called from an ISR context.
 *
 *  This IOCTL waits for current on going/processing frame to get completed and
 *  returns all the frames from input and output queue.
 *
 *  Typically, this ioctl should be called just before deleting the driver to
 *  get all frames back from the driver
 *
 *  Since maximum FVID2_MAX_FRAME_PTR frames can be returned at a time.
 *  This function should be called in a loop until Fvid2_FrameList.numFrames = 0
 *  is returned or the return value is FVID2_ENO_MORE_BUFFERS in order to get
 *  back all the frames from the M2M driver.
 *
 *  This IOCTL will return processed/non-processed frames as well as
 *  all frames held inside the hardware.
 *
 *  \param cmdArgs       [IN]  NULL
 *  \param cmdArgsStatus [OUT] Fvid2_FrameList
 *
 *  \return FVID2_SOK on success, FVID2_ENO_MORE_BUFFERS if all buffers are
 *  returned, other error values on failure.
 */
#define IOCTL_VPS_M2M_INTF_ABORT                (VPS_M2M_INTF_IOCTL_BASE + 1U)

/**
 *  \brief IOCTL to Enable/Disable statistics collection.
 *
 *  Once enabled, driver will start collecting different statistics and
 *  application can these statistics using #IOCTL_VPS_M2M_INTF_GET_STATS ioctl
 *
 *  The maximum m2m requests for which driver collects the sequence
 *  is specified at the create time in maxStatsInst member of the
 *  #Vps_M2mIntfCreateParams. If more requests are
 *  are submitted to the driver, driver will wrap around and start
 *  overwriting statistics.
 *
 *  Call #IOCTL_VPS_REGISTER_TIMESTAMP_FXN IOCTL to use App provided time
 *  function, other driver uses OSAL layer timer function
 *  BspOsal_getCurTimeInUsec.
 *
 *  \warning This command cannot be called from an ISR context.
 *
 *  \param cmdArgs       [IN]  Vps_M2mIntfStatsParams
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, other error values on failure.
 */
#define IOCTL_VPS_M2M_INTF_SET_STATS_PARAMS     (VPS_M2M_INTF_IOCTL_BASE + 2U)

/**
 *  \brief Get M2M driver status information like number of requests processed
 *
 *  \warning This command cannot be called from an ISR context.
 *
 *  \param cmdArgs       [IN]  Vps_M2mIntfStats
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, other error values on failure.
 */
#define IOCTL_VPS_M2M_INTF_GET_STATS            (VPS_M2M_INTF_IOCTL_BASE + 3U)

/**
 *  \brief Resets the statistics, essentially sets the number statistics to 0.
 *  This ioctl can be called when there are not active or pending request
 *  in the driver. Otherwise it returns error. This ioctl cannot be called
 *  from ISR context.
 *
 *  \warning This command cannot be called from an ISR context.
 *
 *  \param cmdArgs       [IN]  NULL
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, other error values on failure.
 */
#define IOCTL_VPS_M2M_INTF_RESET_STATS          (VPS_M2M_INTF_IOCTL_BASE + 4U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  sturct Vps_M2mIntfFrameStats
 *  \brief M2m runtime status for the m2m processing request. Used to get
 *  time at different processing step/point.
 */
typedef struct
{
    UInt32 queueTimeStamp;
    /**< time at which the request is submitted to the driver */
    UInt32 startProcTimeStamp;
    /**< time at which processing for the request is started,
     *   Typically when DMA engine or input/output modules is started
     *   for the processing */
    UInt32 endProcTimeStamp;
    /**< time at which processing for the request is completed and
     *   request complete ISR is called. This time is taken in the
     *   request complete ISR handler */
    UInt32 dequeueTimeStamp;
    /**< time at which the request is returned from the driver,
     *   essentially, when getProcessRequest is called */
} Vps_M2mIntfFrameStats;

/**
 *  struct Vps_M2mIntfCreateParams
 *  \brief M2M create parameter structure to be passed to the
 *  driver at the time of mem to mem driver create call.
 */
typedef struct
{
    UInt32                 numCh;
    /**< [IN] Number of channel for multi-channel modes */
    UInt32                 chInQueueLength;
    /**< [IN] Maximum number of request/frame per channel that can be submitted
     *   for M2M operation without having to dequeue the requests. */
    UInt32                 cfgUpdatePerReq;
    /**< [IN] Flag to enable/disable configuration update on each request
     *   TRUE: On each request submission, full configuration for
     *         each module is updated
     *   FALSE: Configuration will not be updated on each request submission
     *          To update the configuration, driver specific ioctl/api
     *          should be called.
     *   Global parameter, used for all handles
     *   Change the name */
    UInt32                 maxStatsInst;
    /**< [IN] maxStatsInst number of instance of the structure
     *        #Vps_M2mIntfFrameStats at create time to keep track of
     *        different statistics. */
    Vps_M2mIntfFrameStats *frmStats;
    /**< [IN] Application should allocate the memory for an array of
     *        structure #Vps_M2mIntfFrameStats and length maxStatsInst
     *        Driver will use this memory to keep track of different
     *        statistics. */
    void                  *pAdditionalArgs;
    /**< Driver specific additional create params,
     *   M2M driver could have additional create arguments, which could be
     *   passed to the driver using this pointer.
     *   This parameter is set to NULL in the init function */
    void                  *reserved;
    /**< For future use. Not used currently. Set this to NULL. */
} Vps_M2mIntfCreateParams;

/**
 *  sturct Vps_M2mIntfCreateStatus
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
    /**< Maximum number of channels supported by per handle. */
    void  *pAdditionalStatus;
    /**< Driver specific additional create status params */
} Vps_M2mIntfCreateStatus;

/**
 *  sturct Vps_M2MIntfStats
 *  \brief M2m status structure. Used to get different status information.
 *  Used as an argument for #IOCTL_VPS_M2M_INTF_GET_STATS ioctl
 */
typedef struct
{
    UInt32                 numProcessedReq;
    /**< Number of successfully processed request */
    UInt32                 numErrorReq;
    /**< Number of Erroneous request */
    UInt32                 numPendingReq;
    /**< Number of pending requests inside the driver */
    Vps_M2mIntfFrameStats *frmStats;
    /**< Pointer to the array of frame statistics */
    UInt32                 numStats;
    /**< Number of entries in #frmStats array */
} Vps_M2mIntfStats;

/**
 *  sturct Vps_M2mIntfStatsParams
 *  \brief Structure for timestamp parameters. Passed as an argument to
 *  IOCTL_VPS_M2M_INTF_REG_TS_FXN ioctl
 */
typedef struct
{
    UInt32 enable;
    /**< Enable/Disable Statistics collector inside the driver. */
    void  *reserved;
    /**< For future use. Not used currently. Set this to NULL. */
} Vps_M2mIntfStatsParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_M2mIntfCreateParams structure init function.
 *
 *  \param createPrms   [IN] Pointer to #Vps_M2mIntfCreateParams structure.
 *
 */
static inline void VpsM2mIntfCreateParams_init(
    Vps_M2mIntfCreateParams *createPrms);

/**
 *  \brief Vps_M2mIntfStats structure init function.
 *
 *  \param rtStatus     [IN] Pointer to #Vps_M2mIntfStats structure.
 *
 */
static inline void VpsM2mIntfStats_init(
    Vps_M2mIntfStats *rtStatus);

/**
 *  \brief Vps_M2mIntfStatsParams structure init function.
 *
 *  \param statPrms     [IN] Pointer to #Vps_M2mIntfStatsParams structure.
 *
 */
static inline void VpsM2mIntfStatsParams_init(
    Vps_M2mIntfStatsParams *statPrms);

/**
 *  \brief Vps_M2mIntfCreateStatus structure init function.
 *
 *  \param createStatus [IN] Pointer to #Vps_M2mIntfCreateStatus structure.
 *
 */
static inline void VpsM2mIntfCreateStatus_init(
    Vps_M2mIntfCreateStatus *createStatus);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsM2mIntfCreateParams_init(
    Vps_M2mIntfCreateParams *createPrms)
{
    if (NULL != createPrms)
    {
        createPrms->chInQueueLength = VPS_M2M_INTF_DEF_QUEUE_LEN_PER_CH;
        createPrms->numCh           = 1U;
        createPrms->cfgUpdatePerReq = (UInt32) FALSE;
        createPrms->maxStatsInst    = 0U;
        createPrms->frmStats        = NULL;
        createPrms->pAdditionalArgs = NULL;
        createPrms->reserved        = NULL;
    }

    return;
}

static inline void VpsM2mIntfStats_init(Vps_M2mIntfStats *rtStatus)
{
    if (NULL != rtStatus)
    {
        rtStatus->numProcessedReq = 0U;
        rtStatus->numErrorReq     = 0U;
        rtStatus->numPendingReq   = 0U;
        rtStatus->frmStats        = NULL;
        rtStatus->numStats        = 0U;
    }
}

static inline void VpsM2mIntfStatsParams_init(
    Vps_M2mIntfStatsParams *statPrms)
{
    if (NULL != statPrms)
    {
        statPrms->enable   = (UInt32) FALSE;
        statPrms->reserved = NULL;
    }
}

static inline void VpsM2mIntfCreateStatus_init(
    Vps_M2mIntfCreateStatus *createStatus)
{
    if (NULL != createStatus)
    {
        createStatus->retVal            = FVID2_SOK;
        createStatus->maxHandles        = 0U;
        createStatus->maxChPerHandle    = 0U;
        createStatus->pAdditionalStatus = NULL;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_M2M_INTF_H_ */

/*  @}  */
