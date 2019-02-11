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
 *  \defgroup BSP_DRV_FVID2_API FVID2 API
 *
 *  FVID2 API is an interface which is used to create, control and use different
 *  video drivers. FVID2 API is used not only for on-chip
 *  peripherals drivers like capture, display but also for external off-chip
 *  video device peripherals like video decoders, video encoders and
 *  video sensors.
 *
 *  All BSP video drivers and external video peripherals implement the FVID2
 *  API.
 *  Many drivers also extend the FVID2 interface by defining their own driver
 *  specific IOCTLs.
 *
 *  <b> All FVID2 API must be called from task context </b>. Some examples
 *  in the BSP package maybe calling FVID2 APIs from callback and/or
 *  interrupt context. Such examples will be modified in subsequent releases
 *  and in order that user application do not have to do special migration it
 *  is strongly recommended to use FVID2 APIs only from task context.
 *
 *  A FVID2 API can be of two kinds,
 *
 *  - <b> Blocking API </b> <br>
 *    Here the FVID2 API call returns only after completing the request or
 *    functionality or if timed out or if some other error occurs.
 *    The below APIs are always blocking, unless specified otherwise by
 *    specific driver.
 *    - Fvid2_create()
 *    - Fvid2_delete()
 *    - Fvid2_start()
 *    - Fvid2_stop()
 *    - Fvid2_control()
 *    - Fvid2_setFormat()
 *    - Fvid2_getFormat()
 *
 *  - <b> Non-blocking API </b> <br>
 *    Here FVID2 API call queues the request to the driver and returns
 *    immediately before the request is processed or completed.
 *    Application should use the completion callback to wait for request
 *    completion.
 *    The below APIs are always non-blocking, unless specified otherwise by
 *    specific driver.
 *    - Fvid2_queue()
 *    - Fvid2_dequeue()
 *    - Fvid2_processFrames()
 *    - Fvid2_getProcessedFrames()
 *
 *  A FVID2 Driver can belong to one the below categories. The FVID2 APIs
 *  applicable to driver in a category are also listed below. The below is
 *  true for most driver unless specified otherwise by a specific driver.
 *  - <b> Streaming interface drivers </b> <br>
 *  Examples include, capture, display, graphics.
 *  Below FVID2 APIs are implemented by such drivers.
 *    - Fvid2_create()
 *    - Fvid2_delete()
 *    - Fvid2_start()
 *    - Fvid2_stop()
 *    - Fvid2_queue()
 *    - Fvid2_dequeue()
 *    - Fvid2_control()
 *    - Fvid2_setFormat() - OPTIONAL
 *    - Fvid2_getFormat() - OPTIONAL
 *
 *  - <b> Memory to memory processing interface drivers </b> <br>
 *   Examples include, M2M VPE.
 *   Below FVID2 APIs are implemented by such drivers.
 *    - Fvid2_create()
 *    - Fvid2_delete()
 *    - Fvid2_processFrames()
 *    - Fvid2_getProcessedFrames()
 *    - Fvid2_control()
 *    - Fvid2_setFormat() - OPTIONAL
 *    - Fvid2_getFormat() - OPTIONAL
 *
 *  - <b> Control interface drivers </b> <br>
 *   Examples include, display controller, external video devices.
 *   Below FVID2 APIs are implemented by such drivers.
 *    - Fvid2_create()
 *    - Fvid2_delete()
 *    - Fvid2_control()
 *    - Fvid2_start()
 *    - Fvid2_stop()
 *    - Fvid2_setFormat() - OPTIONAL
 *    - Fvid2_getFormat() - OPTIONAL
 *
 *  Before making any FVID2 API calls, Fvid2_init() must be called.
 *  Fvid2_deInit() must be called during system shutdown.
 *
 *  Fvid2_getVersionString() and Fvid2_getVersionNumber() can be used to get
 *  information about current driver version number.
 *
 *  All FVID2 drivers are of type Fvid2_Handle, which gets created when
 *  Fvid2_create() is called. This handle is used for all subsequent FVID2
 *  API calls. This handle and its associated resources are free'ed when
 *  Fvid2_delete() is called.
 *
 *  All FVID2 APIs make use of Fvid2_Frame, Fvid2_FrameList and/or
 *  Fvid2_ProcessList for exchanging and processing video frames via a driver.
 *  Further all drivers use a common user callback mechanism via Fvid2_CbParams
 *  to indicate to the user that a frame is ready. Many drivers, but not all,
 *  use the Fvid2_Format data structure to describe video input, output data
 *  formats.
 *
 *  All drivers use the constants, enum's, error codes defined in this file to
 *  control and configure a driver.
 *
 *  In addition, most drivers define driver specific create time parameters
 *  and IOCTLs to allow the user to control and configure the driver in driver
 *  specific ways. Further a driver may define driver specific run-time
 *  parameters which are passed by user to the driver via
 *  Fvid2_Frame.perFrameCfg and/or Fvid2_FrameList.perListCfg.
 *
 *  Also user application can associate user specific app data with a
 *  driver handle via Fvid2_CbParams.appData or with every frame via
 *  FIVD2_Frame.appData. The app data set as part of Fvid2_CbParams returned
 *  back to user when callback occurs. The app data set as part of Fvid2_Frame
 *  is returned back to the user when the Fvid2_Frame itself is returned back to
 *  user via Fvid2_dequeue() or Fvid2_getProcessedFrames(). The driver will not
 *  modify this app data. This could be used by the application to store any
 *  application specific data like application object info and so on.
 *
 *  Many FVID2 APIs define 'reserved' fields. These are meant for future use
 *  and should be set to NULL/zero by user.
 *
 *  @{
 */

/**
 *  \file fvid2.h
 *
 *  \brief FVID2 API
 */

/*
 *  \author  BSP, TI
 *
 *  \version 0.1    Created.
 *           0.2    Changes for BIOS 6 and new FVID2 interface.
 *           0.2.1  Merged color and data format enums to data format enums.
 *                  Added process list structure to support M2M
 *                  (memory to memory) drivers.
 *                  Removed FVID2_Buf structure and directly used address array
 *                  in Fvid2_Frame structure.
 *                  Defined proper signature for FVID2 APIs.
 *           0.2.2  Added proper comments.
 *           0.3    Added subframe callback and added reserved fields in all the
 *                  structures.
 *           0.4    Made frames pointer to pointer to array of frame pointer in
 *                  framelist to simplify application allocation and ease of
 *                  use.
 *           0.5    Added FVID2 standard enums.
 *           0.6    Split into two files. fvid2.h will contain only FVID2 driver
 *                  specific defintions/declarations. It will include
 *                  fvid2_dataTypes.h for data type defintions
 *
 */

#ifndef FVID2_H_
#define FVID2_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief FVID2 driver version string.
 *  Version is of the form mm_nn_xx_yy where,
 *      mm - Product version (02 for FVID2). This increments for any new FVID2
 *           versions.
 *      nn - Major number - Increments if any backward compatibility is broken
 *           or major change within a product version.
 *      xx - Minor number - Increments for any minor change or any additions
 *           done without breaking backward compatibility.
 *      yy - Build number - Increments for every release.
 */
#define FVID2_VERSION_STRING            "FVID_02_01_00_01"

/** \brief FVID2 driver version number. */
#define FVID2_VERSION_NUMBER            (0x02010001U)

/** \brief FVID2 Driver handle. */
typedef Ptr Fvid2_Handle;

/**
 *  \brief FVID2 driver callback function prototype.
 *
 *  This callback is used by the drivers which implement non-blocking
 *  FVID2 APIs.
 *
 *  User should assume that callbacks happen in ISR context and hence should
 *  apply rules relevant to ISR context when implementing callback functions,
 *  i.e blocking APIs should not be called from callback. Users should also
 *  assume that interrupts are enabled when in callback context, i.e other
 *  interrupt / callbacks can occur when a callback is under execution.
 *  User callback implementation should not be very long, since callback
 *  execution may block other drivers from executing. Typically it is
 *  recommended to set a semaphore or flag when callback happens and do the
 *  more involved callback handling in task context.
 *
 *  This callback is typically called by the driver as mentioned below,
 *  unless specified otherwise by specific drivers.
 *
 *  In case of display drivers, this callback function will be called
 *  when a frame(s) is/are completed displayed. Then the application can
 *  dequeue the displayed buffer back from the driver.
 *
 *  In case of capture drivers, this callback function will be called
 *  when a frame(s) is/are captured. Then the application can dequeue the
 *  captured buffer back from the driver.
 *
 *  In case of M2M drivers, this callback function will be called
 *  when a request from the application is completed by the driver. Then the
 *  application can dequeue the completed request buffers back from the driver.
 *
 *  In case of control drivers, callbacks are typically not used since mostly
 *  FVID2 APIs implemented by control drivers are of blocking nature.
 *
 *  \param handle   [OUT] FVID2 handle for which the callback has occurred.
 *  \param appData  [OUT] Application data provided to the driver at the
 *                        time of Fvid2_create().
 *  \param reserved [OUT] For future use. Set to NULL.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
typedef Int32 (*Fvid2_CbFxn)(Fvid2_Handle handle, Ptr appData, Ptr reserved);

/**
 *  \brief FVID2 error callback function prototype.
 *
 *  Error callback is called by driver when it encounters a error during
 *  processing of frames in its internal queue.
 *
 *  When user submits frames to the driver it does minimal error checks and
 *  stores the the frames in its internal queues. In case of any error at
 *  this point the FVID2 API will simply return error and error callback
 *  will not be called.
 *
 *  The driver will later (depending on how its request queue is full) process
 *  these frames submitted by the user. If driver finds any error in either
 *  the input frame information or hardware itself then it will call this error
 *  callback to notify the user about this error. As part of the callback
 *  information it also returns the frames or request for which error happened
 *  so that user can take appropriate action.
 *
 *  Users should apply same rules as that of Fvid2_CbFxn when implementing
 *  error callbacks.
 *
 *  \param handle   [OUT] FVID2 handle for which the callback has occurred.
 *  \param appData  [OUT] Application data provided to the driver at the time
 *                        of Fvid2_create().
 *  \param errList  [OUT] Pointer to a valid framelist (Fvid2_FrameList)
 *                        in case of capture and display drivers or a pointer
 *                        to a valid processlist (Fvid2_ProcessList) in case of
 *                        M2M drivers. The driver copies the aborted/error
 *                        frames in this frame list or process list.
 *  \param reserved [OUT] For future use. Set to NULL.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
typedef Int32 (*Fvid2_ErrCbFxn)(Fvid2_Handle handle,
                                Ptr          appData,
                                Ptr          errList,
                                Ptr          reserved);

/**
 *  \brief FVID2 callback that is called by subframe mode Capture driver.
 *
 *  This callback is called for every subframe of frame that
 *  is captured. This function is used by Capture Driver and not meant for M2M
 *  drivers.
 *
 *  Users should apply same rules as that of Fvid2_CbFxn when implementing
 *  subframe callbacks.
 *
 *  \param handle       [OUT] FVID2 handle for which this callback happened.
 *  \param subFrameInfo [OUT] SubFrame information.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
typedef Int32 (*Fvid2_SubFrameCbFxn)(Fvid2_Handle handle,
                                     Fvid2_Frame *subFrame);

/**
 *  \name FVID2 Max limits
 *  @{
 */

/** \brief Number of IN/OUT frame list per process list - Used for array
 * allocation in process list structure. */
#define FVID2_MAX_IN_OUT_PROCESS_LISTS  (4U)

/** \brief Decide the streamid based on channel number.  */
#define FVID2_STREAM_ID_ANY             (0xFFFFFFFFU)

/* @} */

/*
 * =========== Command codes for Submit call =============
 */
/** \brief Control command base address. */
#define FVID2_CTRL_BASE                 (0x00000000U)
/** \brief User command base address. */
#define FVID2_USER_BASE                 (0x10000000U)

/**
 *  \addtogroup BSP_DRV_IOCTL_FVID2
 *  @{
 */

/**
 *  \brief Control command used by Fvid2_setFormat()
 *
 *  \param cmdArgs       [IN]  const Fvid2_Format *
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define FVID2_SET_FORMAT                ((UInt32)FVID2_CTRL_BASE + 3U)

/**
 *  \brief Control command used by Fvid2_getFormat()
 *
 *  \param cmdArgs       [IN]  Fvid2_Format *
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define FVID2_GET_FORMAT                ((UInt32)FVID2_CTRL_BASE + 4U)

/**
 *  \brief Control command used by Fvid2_start()
 *
 *  \param cmdArgs       [IN]  Driver specific
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define FVID2_START                     ((UInt32)FVID2_CTRL_BASE + 5U)

/**
 *  \brief Control command used by Fvid2_stop()
 *
 *  \param cmdArgs       [IN]  Driver specific
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define FVID2_STOP                      ((UInt32)FVID2_CTRL_BASE + 6U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief FVID2 callback parameters that are setup during Fvid2_create().
 */
typedef struct
{
    Fvid2_CbFxn    cbFxn;
    /**< Application callback function used by the driver to intimate any
     *   operation has completed or not. This is an optional parameter
     *   in case application decides to use polling method and so could be
     *   set to NULL. */

    Fvid2_ErrCbFxn errCbFxn;
    /**< Application error callback function used by the driver to intimate
     *   any error occurs at the time of streaming. This is an optional
     *   parameter in case application decides not to get any error callback
     *   and so could be set to NULL. */

    Ptr            errList;
    /**< Pointer to a valid Fvid2_FrameList in case of capture
     *   and display drivers or a pointer to a valid Fvid2_ProcessList
     *   in case of M2M drivers where the driver copies
     *   the aborted/error packet. The memory of this list should be
     *   allocated by the application and provided to the driver at the time
     *   of driver creation. When the application gets this callback, it has
     *   to empty this list and taken necessary action like freeing up memories
     *   etc. The driver will then reuse the same list for future error
     *   callback.
     *   This could be NULL if errCbFxn is NULL. Otherwise this should be
     *   non-NULL. */

    Ptr appData;
    /**< Application specific data which is returned in the callback function
     *   as it is. This could be set to NULL if not used. */
    Ptr reserved;
    /**< For future use. Not used currently. Set this to NULL. */
} Fvid2_CbParams;

/**
 *  \brief FVID2 process list containing frame list's used to exchange multiple
 *  input/output buffers in M2M (memory to memory) operation.
 *
 *  Each of the frame list in turn can have multiple frames/request.
 *
 *  This is typically used by Fvid2_processFrames(), Fvid2_getProcessedFrames().
 */
typedef struct
{
    Fvid2_FrameList *inFrameList[FVID2_MAX_IN_OUT_PROCESS_LISTS];
    /**< Pointer to an array of FVID2 frame list pointers.
     *
     *   Each frame list points to a seqeuence of input frame pointers
     *   that are to be processed.
     *
     *   For drivers that take multiple input there could be more that one
     *   input frame list. Example, noise filter driver takes two frame as
     *   inputs, current frame and previous output frame.
     *   In this case numInList = 2.
     *
     *   [IN]  for Fvid2_processFrames()
     *   as well as Fvid2_getProcessedFrames() operation.
     *
     *   For Fvid2_processFrames(), the frame pointers that the frame list
     *   points to should be provided by the application.
     *
     *   For Fvid2_getProcessedFrames(), the frame pointers that the frame list
     *   points to are filled by the driver and returned to the application. */

    Fvid2_FrameList *outFrameList[FVID2_MAX_IN_OUT_PROCESS_LISTS];
    /**< Pointer to an array of FVID2 frame list pointers.
     *
     *   Each frame list points to a seqeuence of output frame pointers
     *   that point to where the output should go after processing.
     *
     *   For drivers that generate multiple outputs there could be more that one
     *   output frame list. Example, deinterlacer driver outputs two frames as
     *   for one input frame, VIP-SC output frame and DEI-SC output frame.
     *   In this case numOutList = 2.
     *
     *   [IN]  for Fvid2_processFrames()
     *   as well as Fvid2_getProcessedFrames() operation.
     *
     *   For Fvid2_processFrames(), the frame pointers that the frame list
     *   points to should be provided by the application.
     *
     *   For Fvid2_getProcessedFrames(), the frame pointers that the frame
     *   list points to are filled by the driver and returned to the
     *   application. */

    UInt32 numInLists;
    /**< Number of input frame lists.
     *
     *   [IN]  for Fvid2_processFrames()
     *   [OUT]  for Fvid2_getProcessedFrames(). */
    UInt32 numOutLists;
    /**< Number of output frame lists.
     *
     *   [IN]  for Fvid2_processFrames()
     *   [OUT]  for Fvid2_getProcessedFrames(). */

    Ptr    drvData;
    /**< Used by driver. Application should not modify this. */

    Ptr    reserved;
    /**< For future use. Not used currently. Set this to NULL. */
} Fvid2_ProcessList;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief FVID2 init function.
 *
 *  Initializes the FVID2 layer.
 *  This function should be called before calling any of FVID2 API's and
 *  should be called only once.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return FVID2_SOK on success else appropriate FVID2 error code on failure.
 */
Int32 Fvid2_init(Ptr args);

/**
 *  \brief FVID2 deinit function.
 *
 *  Uninitializes the FVID2 layer and should be called during system shutdown.
 *  Should not be called if Fvid2_init() is not called.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Fvid2_deInit(Ptr args);

/**
 *  \brief Get the version string for FVID2 interface.
 *
 *  This is the version number for the FVID2 interface. This
 *  function can be called prior to #Fvid2_init() to get the version number.
 *
 *  \return Pointer to FVID2 version string.
 */
const Char *Fvid2_getVersionString(void);

/**
 *  \brief Same as #Fvid2_getVersionString() except it returns the version in
 *  UInt32 form.
 *
 *  Example, v1.0.1.17 will be 0x01000117
 *
 *  \return FVID2 version number.
 */
UInt32 Fvid2_getVersionNumber(void);

/**
 *  \brief Creates the driver identified by the driver ID.
 *
 *  This will allocate HW and/or SW resources and return a Fvid2_Handle
 *  for this driver. This handle will be used for subsequent FVID2 API calls
 *
 *  \param drvId        [IN] Driver to open. Driver ID is driver specific.
 *
 *  \param instanceId   [IN] Instance of the driver to open and is used
 *                      to differentiate multiple instance support on a
 *                      single driver. Instance ID is driver specific.
 *
 *  \param createArgs   [IN] Pointer to the create argument structure. The type
 *                      of the structure is defined by the specific driver.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \param createStatusArgs [OUT] Pointer to status argument structure where the
 *                      driver returns any status information. The type
 *                      of the structure is defined by the specific driver.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \param cbParams     [IN] Application callback parameters.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \return non-NULL Fvid2_Handle object pointer on success else returns NULL
 *  on error.
 */
Fvid2_Handle Fvid2_create(UInt32                drvId,
                          UInt32                instanceId,
                          Ptr                   createArgs,
                          Ptr                   createStatusArgs,
                          const Fvid2_CbParams *cbParams);

/**
 *  \brief Deletes a previously created FVID2 driver handle.
 *
 *  This free's the HW/SW resources allocated during create
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *
 *  \param deleteArgs   [IN] Pointer to the delete argument structure. The type
 *                      of the structure is defined by the specific driver.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Fvid2_delete(Fvid2_Handle handle, Ptr deleteArgs);

/**
 *  \brief Send control commands (IOCTLs) to the driver.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *
 *  \param cmd          [IN] IOCTL command. The type of command supported
 *                      is defined by the specific driver.
 *
 *  \param cmdArgs      [IN] Pointer to the command argument structure. The type
 *                      of the structure is defined by the specific driver
 *                      for each of the supported IOCTL.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \param cmdStatusArgs [OUT] Pointer to status argument structure where the
 *                      driver returns any status information. The type
 *                      of the structure is defined by the specific driver
 *                      for each of the supported IOCTL.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Fvid2_control(Fvid2_Handle handle,
                    UInt32       cmd,
                    Ptr          cmdArgs,
                    Ptr          cmdStatusArgs);

/**
 *  \brief An application calls Fvid2_queue to submit a video buffer to the
 *  video device driver.
 *
 *  - This is used in capture/display drivers.
 *  - This function could be called from task or ISR context unless the specific
 *  driver restricts from doing so.
 *  - This is a non-blocking API unless the specific driver restricts from
 *  doing so.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param frameList    [IN] Pointer to the frame list structure containing the
 *                      information about the FVID2 frames that has to be
 *                      queued in the driver.
 *  \param streamId     [IN] Stream ID to which the frames should be queued
 *                      This is used in drivers where they could support
 *                      multiple streams for the same handle. Otherwise this
 *                      should be set to zero.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Fvid2_queue(Fvid2_Handle     handle,
                  Fvid2_FrameList *frameList,
                  UInt32           streamId);

/**
 *  \brief An application calls Fvid2_dequeue to request the video device
 *  driver to give ownership of a video buffer.
 *
 *  - This is used in capture/display drivers.
 *  - This is a non-blocking API if timeout is FVID2_TIMEOUT_NONE and could be
 *  called by task and ISR context unless the specific driver restricts from
 *  doing so.
 *  - This is blocking API if timeout is FVID2_TIMEOUT_FOREVER if supported by
 *  specific driver implementation.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param frameList    [OUT] Pointer to the frame list structure where the
 *                      dequeued frame pointer will be stored.
 *  \param streamId     [IN] Stream ID from where frames should be dequeued.
 *                      This is used in drivers where it could support multiple
 *                      streams for the same handle. Otherwise this
 *                      should be set to zero.
 *  \param timeout      [IN] FVID2 timeout in units of OS ticks. This will
 *                      determine the timeout value till the driver will block
 *                      for a free or completed buffer is available.
 *                      For non-blocking drivers this parameter might be
 *                      ignored.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Fvid2_dequeue(Fvid2_Handle     handle,
                    Fvid2_FrameList *frameList,
                    UInt32           streamId,
                    UInt32           timeout);

/**
 *  \brief An application calls Fvid2_processFrames to submit a video buffer
 *  to the video device driver.
 *
 *  This API is very similar to the Fvid2_queue API except that this is
 *  used in M2M drivers only.
 *  - This function could be called from task or ISR context unless the specific
 *  driver restricts from doing so.
 *  - This is a non-blocking API unless the specific driver restricts from
 *  doing so.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param processList  [IN] Pointer to the process list structure containing
 *                      the information about the FVID2 frame lists and frames
 *                      that has to be queued to the driver for processing.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Fvid2_processFrames(Fvid2_Handle       handle,
                          Fvid2_ProcessList *processList);

/**
 *  \brief An application calls Fvid2_getProcessedFrames to request the video
 *  device driver to give ownership of a video buffer.
 *
 *  This API is very similar to the Fvid2_dequeue API except that this is
 *  used in M2M drivers only.
 *  - This is a non-blocking API if timeout is FVID2_TIMEOUT_NONE and could be
 *  called by task and ISR context unless the specific driver restricts from
 *  doing so.
 *  - This is blocking API if timeout is FVID2_TIMEOUT_FOREVER if supported by
 *  specific driver implementation.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param processList  [OUT] Pointer to the process list structure where the
 *                      driver will copy the references to the dequeued FVID2
 *                      frame lists and frames.
 *  \param timeout      [IN] FVID2 timeout. This will determine the timeout
 *                      value till the driver will block for a free or completed
 *                      buffer is available. For non-blocking drivers this
 *                      parameter might be ignored.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Fvid2_getProcessedFrames(Fvid2_Handle       handle,
                               Fvid2_ProcessList *processList,
                               UInt32             timeout);

/**
 *  \brief An application calls Fvid2_processRequest to submit a video buffer
 *  to the video device driver.
 *
 *  This API is used for submitting a single channel video processing request
 *  to the video device driver. It uses framelist to submit multiple
 *  frames of different stream ids of the same request.
 *
 *  - This function could be called from task or ISR context unless the specific
 *  driver restricts from doing so.
 *  - This is a non-blocking API unless the specific driver restricts from
 *  doing so.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param inFrameList  [IN] Pointer to the array of input frames with
 *                           different stream ids.
 *  \param outFrameList [IN] Pointer to the array of output frames with
 *                           different stream ids
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Fvid2_processRequest(Fvid2_Handle          handle,
                           Fvid2_FrameList      *inFrameList,
                           Fvid2_FrameList      *outFrameList);

/**
 *  \brief An application calls Fvid2_getProcessedRequest to get the
 *  processed request back from the driver and thus to get the
 *  ownership of request back from the driver.
 *
 *  - This is a non-blocking API if timeout is FVID2_TIMEOUT_NONE and could be
 *  called by task and ISR context unless the specific driver restricts from
 *  doing so.
 *  - This is blocking API if timeout is FVID2_TIMEOUT_FOREVER if supported by
 *  specific driver implementation.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param inFrameList  [OUT] Pointer to frame list in which input frames with
 *                            different stream ids will be returned
 *                            by the driver.
 *  \param outFrameList [OUT] Pointer to frame list in which output frames with
 *                            different stream ids will be returned by
 *                            the driver.
 *  \param timeout      [IN] FVID2 timeout. This will determine the timeout
 *                           value till the driver will block for a
 *                           free or completed buffer is available.
 *                           For non-blocking drivers this parameter
 *                           might be ignored.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Fvid2_getProcessedRequest(Fvid2_Handle          handle,
                                Fvid2_FrameList      *inFrameList,
                                Fvid2_FrameList      *outFrameList,
                                UInt32                timeout);
/**
 *  \brief An application calls Fvid2_start to request the video device
 *  driver to start the video display or capture operation.
 *  This function should be called from task context only and should not be
 *  called from ISR context.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param cmdArgs      [IN] Pointer to the start argument structure. The type
 *                      of the structure is defined by the specific driver.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
static inline Int32 Fvid2_start(Fvid2_Handle handle, Ptr cmdArgs);

/**
 *  \brief An application calls Fvid2_stop to request the video device
 *  driver to stop the video display or capture operation.
 *  This function should be called from task context only and should not be
 *  called from ISR context.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param cmdArgs      [IN] Pointer to the stop argument structure. The type
 *                      of the structure is defined by the specific driver.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
static inline Int32 Fvid2_stop(Fvid2_Handle handle, Ptr cmdArgs);

/**
 *  \brief An application calls Fvid2_setFormat to request the video device
 *  driver to set the format for a given channel.
 *  This function should be called from task context only and should not be
 *  called from ISR context.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param fmt          [IN] Pointer to the FVID2 format structure.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
static inline Int32 Fvid2_setFormat(Fvid2_Handle handle, Fvid2_Format *fmt);

/**
 *  \brief An application calls Fvid2_getFormat to request the video device
 *  driver to get the current format for a given channel.
 *  This function should be called from task context only and should not be
 *  called from ISR context.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param fmt          [OUT] Pointer to the FVID2 format structure.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
static inline Int32 Fvid2_getFormat(Fvid2_Handle handle, Fvid2_Format *fmt);

/**
 *  \brief Fvid2_CbParams structure init function.
 *
 *  \param cbPrms       [IN] Pointer to #Fvid2_CbParams structure.
 *
 */
static inline void Fvid2CbParams_init(Fvid2_CbParams *cbPrms);

/**
 *  \brief Fvid2_ProcessList structure init function.
 *
 *  \param pList        [IN] Pointer to #Fvid2_ProcessList structure.
 *
 */
static inline void Fvid2ProcessList_init(Fvid2_ProcessList *pList);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline Int32 Fvid2_start(Fvid2_Handle handle, Ptr cmdArgs)
{
    return Fvid2_control(handle, FVID2_START, cmdArgs, NULL);
}

static inline Int32 Fvid2_stop(Fvid2_Handle handle, Ptr cmdArgs)
{
    return Fvid2_control(handle, FVID2_STOP, cmdArgs, NULL);
}

static inline Int32 Fvid2_setFormat(Fvid2_Handle handle, Fvid2_Format *fmt)
{
    return Fvid2_control(handle, FVID2_SET_FORMAT, fmt, NULL);
}

static inline Int32 Fvid2_getFormat(Fvid2_Handle handle, Fvid2_Format *fmt)
{
    return Fvid2_control(handle, FVID2_GET_FORMAT, fmt, NULL);
}

static inline void Fvid2CbParams_init(Fvid2_CbParams *cbPrms)
{
    if (NULL != cbPrms)
    {
        cbPrms->cbFxn    = NULL;
        cbPrms->errCbFxn = NULL;
        cbPrms->errList  = NULL;
        cbPrms->appData  = NULL;
        cbPrms->reserved = NULL;
    }

    return;
}

static inline void Fvid2ProcessList_init(Fvid2_ProcessList *pList)
{
    UInt32 i;

    if (NULL != pList)
    {
        for (i = 0U; i < FVID2_MAX_IN_OUT_PROCESS_LISTS; i++)
        {
            pList->inFrameList[i]  = NULL;
            pList->outFrameList[i] = NULL;
        }
        pList->numInLists  = 0U;
        pList->numOutLists = 0U;
        pList->drvData     = NULL;
        pList->reserved    = NULL;
    }

    return;
}

/*
 *  The deprecated structures and API FVID2_* has been replaced with
 *  Fvid2_*.
 *  This has been done to follow coding guidelines and have a uniform
 *  naming convention.
 *  If backward compatibility is required, use could enable the below
 *  macro.
 *  By default this macro is not enabled.
 */
#ifdef FVID2_BACKWARD_COMPATIBLE

/*
 * Deprecated structures.
 */
/** \brief Macro for deprecated structure FVID2_Handle. */
#define FVID2_Handle                    Fvid2_Handle
/** \brief Macro for deprecated structure FVID2_CbFxn. */
#define FVID2_CbFxn                     Fvid2_CbFxn
/** \brief Macro for deprecated structure FVID2_ErrCbFxn. */
#define FVID2_ErrCbFxn                  Fvid2_ErrCbFxn
/** \brief Macro for deprecated structure FVID2_DataFormat. */
#define FVID2_DataFormat                Fvid2_DataFormat
/** \brief Macro for deprecated structure FVID2_ScanFormat. */
#define FVID2_ScanFormat                Fvid2_ScanFormat
/** \brief Macro for deprecated structure FVID2_Standard. */
#define FVID2_Standard                  Fvid2_Standard
/** \brief Macro for deprecated structure FVID2_Fid. */
#define FVID2_Fid                       Fvid2_Fid
/** \brief Macro for deprecated structure FVID2_Polarity. */
#define FVID2_Polarity                  Fvid2_Polarity
/** \brief Macro for deprecated structure FVID2_EdgePolarity. */
#define FVID2_EdgePolarity              Fvid2_EdgePolarity
/** \brief Macro for deprecated structure FVID2_BufferFormat. */
#define FVID2_BufferFormat              Fvid2_BufferFormat
/** \brief Macro for deprecated structure FVID2_BitsPerPixel. */
#define FVID2_BitsPerPixel              Fvid2_BitsPerPixel
/** \brief Macro for deprecated structure FVID2_CbParams. */
#define FVID2_CbParams                  Fvid2_CbParams
/** \brief Macro for deprecated structure FVID2_Format. */
#define FVID2_Format                    Fvid2_Format
/** \brief Macro for deprecated structure FVID2_Frame. */
#define FVID2_Frame                     Fvid2_Frame
/** \brief Macro for deprecated structure FVID2_FrameList. */
#define FVID2_FrameList                 Fvid2_FrameList
/** \brief Macro for deprecated structure FVID2_ProcessList. */
#define FVID2_ProcessList               Fvid2_ProcessList
/** \brief Macro for deprecated structure FVID2_ModeInfo. */
#define FVID2_ModeInfo                  Fvid2_ModeInfo

/*
 * Deprecated functions.
 */
/** \brief Macro for deprecated function FVID2_init. */
#define FVID2_init                      Fvid2_init
/** \brief Macro for deprecated function FVID2_deInit. */
#define FVID2_deInit                    Fvid2_deInit
/** \brief Macro for deprecated function FVID2_getVersionString. */
#define FVID2_getVersionString          Fvid2_getVersionString
/** \brief Macro for deprecated function FVID2_getVersionNumber. */
#define FVID2_getVersionNumber          Fvid2_getVersionNumber
/** \brief Macro for deprecated function FVID2_create. */
#define FVID2_create                    Fvid2_create
/** \brief Macro for deprecated function FVID2_delete. */
#define FVID2_delete                    Fvid2_delete
/** \brief Macro for deprecated function FVID2_control. */
#define FVID2_control                   Fvid2_control
/** \brief Macro for deprecated function FVID2_queue. */
#define FVID2_queue                     Fvid2_queue
/** \brief Macro for deprecated function FVID2_dequeue. */
#define FVID2_dequeue                   Fvid2_dequeue
/** \brief Macro for deprecated function FVID2_processFrames. */
#define FVID2_processFrames             Fvid2_processFrames
/** \brief Macro for deprecated function FVID2_getProcessedFrames. */
#define FVID2_getProcessedFrames        Fvid2_getProcessedFrames
/** \brief Macro for deprecated function FVID2_start. */
#define FVID2_start                     Fvid2_start
/** \brief Macro for deprecated function FVID2_stop. */
#define FVID2_stop                      Fvid2_stop
/** \brief Macro for deprecated function FVID2_setFormat. */
#define FVID2_setFormat                 Fvid2_setFormat
/** \brief Macro for deprecated function FVID2_getFormat. */
#define FVID2_getFormat                 Fvid2_getFormat
/** \brief Macro for deprecated function FVID2_getModeInfo. */
#define FVID2_getModeInfo               Fvid2_getModeInfo
/** \brief Macro for deprecated function FVID2_getDataFmtString. */
#define FVID2_getDataFmtString          Fvid2_getDataFmtString
/** \brief Macro for deprecated function FVID2_getStandardString. */
#define FVID2_getStandardString         Fvid2_getStandardString
/** \brief Macro for deprecated function FVID2_isDataFmtYuv422. */
#define FVID2_isDataFmtYuv422           Fvid2_isDataFmtYuv422
/** \brief Macro for deprecated function FVID2_isDataFmtYuv420. */
#define FVID2_isDataFmtYuv420           Fvid2_isDataFmtYuv420
/** \brief Macro for deprecated function FVID2_isDataFmtSemiPlanar. */
#define FVID2_isDataFmtSemiPlanar       Fvid2_isDataFmtSemiPlanar
/** \brief Macro for deprecated function FVID2_isDataFmtYuv422I. */
#define FVID2_isDataFmtYuv422I          Fvid2_isDataFmtYuv422I
/** \brief Macro for deprecated function FVID2_isStandardVesa. */
#define FVID2_isStandardVesa            Fvid2_isStandardVesa
/** \brief Macro for deprecated function FVID2CbParams_init. */
#define FVID2CbParams_init              Fvid2CbParams_init
/** \brief Macro for deprecated function FVID2Format_init. */
#define FVID2Format_init                Fvid2Format_init
/** \brief Macro for deprecated function FVID2SubFrameInfo_init. */
#define FVID2SubFrameInfo_init          Fvid2SubFrameInfo_init
/** \brief Macro for deprecated function FVID2Frame_init. */
#define FVID2Frame_init                 Fvid2Frame_init
/** \brief Macro for deprecated function FVID2FrameList_init. */
#define FVID2FrameList_init             Fvid2FrameList_init
/** \brief Macro for deprecated function FVID2ProcessList_init. */
#define FVID2ProcessList_init           Fvid2ProcessList_init
/** \brief Macro for deprecated function FVID2ModeInfo_init. */
#define FVID2ModeInfo_init              Fvid2ModeInfo_init

#endif  /* #ifdef FVID2_BACKWARD_COMPATIBLE */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef FVID2_H_ */

/* @} */
