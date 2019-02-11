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
 *  \defgroup BSP_DRV_VPS_DISPLAY_API Display API
 *
 *  @{
 */

/**
 *  \file vps_display.h
 *
 *  \brief Display Driver
 *  Generic Display Driver Interface file.
 */

#ifndef VPS_DISPLAY_H_
#define VPS_DISPLAY_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/vps_dataTypes.h>

/* ========================================================================== */
/* Include HW specific config constants, structures                           */
/* ========================================================================== */
#include <ti/drv/vps/include/dss/vps_displayDss.h>
#include <ti/drv/vps/include/common/bsp_cfgMem.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name Display max limits or defaults.
 *
 *  @{
 */

/** \brief Maximum number of display driver instance. */
#define VPS_DISP_INST_MAX               (4U)

/** \brief Default max number of frames that can be queued per instance. */
#define VPS_DISP_DEF_QUEUE_LEN_PER_INST (BSP_CFG_DISP_QUEUE_LEN_PER_INST)

/* @} */

/**
 *  \brief Display driver buffer program callback function prototype.
 *
 *  This callback is called by the driver when it is about to program the
 *  already queued buffer to the hardware. The driver returns the current
 *  frame pointer and the application can use this information to check if
 *  the buffer to be programmed is too old to display. If it decides so,
 *  the application can give a new frame buffer (blank frame) in the return
 *  parameter. Then the driver swaps this FVID2 frame pointer in it's internal
 *  queue and program the new frame provided.
 *
 *  Note: Once the frame is swapped with the driver, the driver will not have
 *  any reference to the old frame. The ownership of the old frame is
 *  transferred to application and will not be returned in the driver dequeue
 *  operation.
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
 *  \param handle       [OUT] FVID2 handle for which the callback has occurred.
 *  \param curFrm       [OUT] Current FVID2 frame about to be programmed.
 *  \param isFrmRepeat  [OUT] Flag to indicate whether the current frame is
 *                            already programmed in the hardware.
 *  \param creditCnt    [OUT] If frame repeat, this indicates the frame repeat
 *                            count reflecting the hardware queue depth.
 *                            In case of DSS, we have actual register and shadow
 *                            register. Hence this value could be 1 or 2
 *                            for most of the cases. 1 means normal operating
 *                            mode without frame repeat. 2 means both the
 *                            shadow and current register have the same buffer
 *                            i.e. the frame is getting repeated.
 *                            There is a special case when this value is 0.
 *                            This means the driver is trying to program the
 *                            register in low latency mode in task context.
 *                            But the success of the buffer getting accepted
 *                            depends on when the queue is called with respect
 *                            to VSYNC. If the Queue call is very near the VSYNC
 *                            say 10 lines before VSYNC, the buffer programming
 *                            will not be accepted. And the application should
 *                            assume that the buffer will gets programmed in
 *                            the next VSYNC only.
 *
 *  \return The application can return the new FVID2 frame to be used for
 *  programming the hardware. If the application returns NULL no action is
 *  taken and the driver will go ahead and program the current frame to
 *  hardware.
 */
typedef Fvid2_Frame *(*Vps_DispBufPrgmCbFxn)(Fvid2_Handle handle,
                                             Fvid2_Frame *curFrm,
                                             UInt32       isFrmRepeat,
                                             UInt32       creditCnt);

/*
 *  Display driver IOCTLs.
 */

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_DISPLAY
 *  @{
 */

/**
 *  \brief Get display status IOCTL.
 *
 *  This IOCTL can be used to get the display status like number of frames
 *  displayed, number of frames repeated, number of frames queued/dequeued.
 *  Note: These counters will be reset either at the time of driver create or
 *  while starting the display operation. See respective counter comments for
 *  details.
 *
 *  \param cmdArgs       [OUT] Vps_DispStatus *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_DISP_GET_STATUS       (VPS_DISP_IOCTL_BASE + 0x0001U)

/**
 *  \brief Register buffer program callback function IOCTL.
 *
 *  This IOCTL can be used to register a callback when the actual buffer
 *  is getting programmed to the hardware. See #Vps_DispBufPrgmCbFxn for
 *  details.
 *
 *  This IOCTL is per display driver instance and hence should be called
 *  separately for each display pipeline.
 *
 *  Also this IOCTL should be called before starting the display.
 *
 *  \param cmdArgs       [OUT] const Vps_DispBufPrgmCbFxnParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_DISP_REGISTER_BUF_PRGM_CB (VPS_DISP_IOCTL_BASE + 0x0002U)

/**
 *  \brief Bypass low latency check IOCTL.
 *
 *  This IOCTL can be used to bypass the low latency check before programming
 *  the buffer to the hardware.
 *
 *  In order to support low latency display, the display driver provides a
 *  mechanism to program the buffer address in the Fivd2_queue() context. This
 *  will ensure that the recently given buffer is programmed directly in to the
 *  hardware register without waiting for the next VSYNC interrupt.
 *
 *  To avoid race condition between the hardware VSYNC occurring and the driver
 *  programming the buffer at the same time, the driver generally checks that
 *  the actual programming of the register is not near the VSYNC period.
 *  For this, the driver makes use of the current line count (relative to
 *  previous VSYNC) of the DSS hardware. But this hardware feature is not
 *  present for all the overlays/VENC. For example, for DSS LCD2 and LCD3, this
 *  feature is not present. Hence for these overlays, low latency display
 *  can't be supported using the above line check feature.
 *
 *  In order to work around this hardware limitation, the driver can bypass this
 *  "queue not near to VSYNC" check and let the application do this check using
 *  timestamp with respect to last VSYNC and the expected display FPS. To do
 *  so, application can check just before driver queue, that it is
 *  not near the (VSYNC period - 2 ms) and then queue the frame. From this point
 *  to the actual register programming takes less that 1 ms for the driver if
 *  no context switching happens. To ensure this the display task can be made
 *  the highest task in the system and other HWI events which take more than
 *  safe period (in this case 2ms).
 *
 *  This IOCTL is per display driver instance and hence should be called
 *  separately for each display pipeline.
 *
 *  Also this IOCTL should be called before starting the display.
 *
 *  \param cmdArgs       [OUT] const Vps_DispBypassLowLatencyCheckParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_DISP_BYPASS_LOW_LATENCY_CHECK (VPS_DISP_IOCTL_BASE + 0x0003U)

/* @} */

/** \brief DSS Display driver IOCTL base. */
#define VPS_DISP_DSS_IOCTL_BASE         (VPS_DISP_IOCTL_BASE + 0x0100U)

/** \brief DSS Display driver Advance IOCTL base. */
#define VPS_DISP_DSS_ADV_IOCTL_BASE     (VPS_DISP_IOCTL_BASE + 0x0200U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Display driver create arguments, used when calling Fvid2_create().
 */
typedef struct
{
    UInt32 periodicCbEnable;
    /**< TRUE: User callback passed during FVID2 create is called periodically.
     *   For progressive display, this interval is equal to VSYNC interval.
     *   For interlaced display, this interval is equal to twice the VSYNC
     *   interval as frames (two fields) are queued to the driver.
     *   FALSE: User callback passed during FVID2 create is called only
     *   if one or more frames (requests) are available in the driver output
     *   queue for the application to dequeue. */
    UInt32 instInQueueLength;
    /**< [IN] Maximum number of request/frame per instance that can be
     *   submitted for display without having to dequeue the displayed
     *   requests. */
} Vps_DispCreateParams;

/**
 *  \brief Create status for the display driver create call. This should be
 *  passed to the create function as a create status argument while creating
 *  the driver.
 */
typedef struct
{
    Int32  retVal;
    /**< [OUT] Return value of create call. */
    UInt32 standard;
    /**< [OUT] VENC Standard like NTSC, 1080p etc to which the display driver
     *   path is connected. For valid values see #Fvid2_Standard. */
    UInt32 dispWidth;
    /**< [OUT] Width of the display at the VENC in pixels to which the
     *   display driver path is connected. */
    UInt32 dispHeight;
    /**< [OUT] Height of the display at the VENC in linesto which the
     *   display driver path is connected. */
    UInt32 minNumPrimeBuf;
    /**< [OUT] Minimum number of buffers to prime before starting display
     *   operation.*/
} Vps_DispCreateStatus;

/**
 *  \brief Display status structure used to get the current status.
 */
typedef struct
{
    UInt32 queueCount;
    /**< [OUT] Counter to keep track of how many requests are queued to the
     *   driver.
     *   Note: This counter will be reset at the time of driver create. */
    UInt32 dequeueCount;
    /**< [OUT] Counter to keep track of how many requests are dequeued from the
     *   driver.
     *   Note: This counter will be reset at the time of driver create. */
    UInt32 dispFrmCount;
    /**< [OUT] Counter to keep track of how many frames are displayed.
     *   For interlaced display, this is half of the actual field display.
     *   Note: This counter will be reset at the time of display start. */
    UInt32 repeatFrmCount;
    /**< [OUT] Counter to keep track of how many frames are repeated when the
     *   application fails to queue buffer at the display rate.
     *   Note: This counter will be reset at the time of display start. */
    UInt32 underflowCount;
    /**< [OUT] Counter to keep track of number of underflows
     *   Note: This counter will be reset at the time of driver create. */
} Vps_DispStatus;

/**
 *  \brief Run time configuration structure for the display driver.
 *  This needs to be passed along with frame list to update any supported
 *  run time parameters.
 */
typedef struct
{
    Fvid2_PosConfig *posCfg;
    /**< [IN] Position configuration used to position the Frame in output
     *   window (overlay).
     *   Pass NULL if no change is required. */
    Vps_FrameParams *inFrmPrms;
    /**< [IN] Frame params for input frame - used to change the frame width and
     *   height at runtime.
     *   Note that this is used only when the buffer
     *   dimension is smaller than the VENC size.
     *   When changing the size, the application should ensure that the
     *   startX/startY + the frame size doesn't exceed the display resolution.
     *   Pass NULL if no change is required. */
    Vps_FrameParams *outFrmPrms;
    /**< [IN] Target image Size (o/p of pipeline).
     *   only Width and height is valid in this structure.
     *   Pass NULL if no change is required. */
} Vps_DispRtParams;

/**
 *  \brief Display buffer program callback parameter structure.
 */
typedef struct
{
    Vps_DispBufPrgmCbFxn bufPrgmCbFxn;
    /**< [IN] Application callback function to be called just before
     *   programming the hardware. A value of NULL will un register the
     *   callback. */
} Vps_DispBufPrgmCbFxnParams;

/**
 *  \brief Display buffer program callback parameter structure.
 */
typedef struct
{
    UInt32 bypassLowLatencyCheck;
    /**< TRUE  - Bypass the low latency check and directly program the
     *           buffer in hardware.
     *   FALSE - Enable low latency check - Normal operation. */
} Vps_DispBypassLowLatencyCheckParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Check if the display driver instance is of type Video pipeline.
 *
 *  \return TRUE if instance is Video pipeline else returns FALSE.
 */
static inline Bool Vps_dispIsVidInst(UInt32 instId);

/**
 *  \brief Check if the display driver instance is of type Graphics pipeline.
 *
 *  \return TRUE if instance is graphics pipeline else returns FALSE.
 */
static inline Bool Vps_dispIsGfxInst(UInt32 instId);

/**
 *  \brief Vps_DispCreateParams structure init function.
 *
 *  \param createPrms   [IN] Pointer to #Vps_DispCreateParams structure.
 *
 */
static inline void VpsDispCreateParams_init(Vps_DispCreateParams *createPrms);

/**
 *  \brief Vps_DispRtParams structure init function.
 *
 *  \param rtPrms       [IN] Pointer to #Vps_DispRtParams structure.
 *
 */
static inline void VpsDispRtParams_init(Vps_DispRtParams *rtPrms);

/**
 *  \brief Vps_DispBufPrgmCbFxnParams structure init function.
 *
 *  \param bufPrgmCbPrms [IN] Pointer to #Vps_DispBufPrgmCbFxnParams structure.
 *
 */
static inline void VpsDispBufPrgmCbFxnParams_init(
    Vps_DispBufPrgmCbFxnParams *bufPrgmCbPrms);

/**
 *  \brief Vps_DispBypassLowLatencyCheckParams structure init function.
 *
 *  \param bypassPrms    [IN] Pointer to #Vps_DispBypassLowLatencyCheckParams
 *                            structure.
 *
 */
static inline void VpsDispBypassLowLatencyCheckParams_init(
    Vps_DispBypassLowLatencyCheckParams *bypassPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline Bool Vps_dispIsVidInst(UInt32 instId)
{
    Bool isVidInst = FALSE;

    if ((VPS_DISP_INST_DSS_VID1 == instId) ||
        (VPS_DISP_INST_DSS_VID3 == instId) ||
        (VPS_DISP_INST_DSS_VID2 == instId))
    {
        isVidInst = (Bool) TRUE;
    }

    return (isVidInst);
}

static inline Bool Vps_dispIsGfxInst(UInt32 instId)
{
    Bool isGfxInst = FALSE;

    if (VPS_DISP_INST_DSS_GFX1 == instId)
    {
        isGfxInst = (Bool) TRUE;
    }

    return (isGfxInst);
}

static inline void VpsDispCreateParams_init(Vps_DispCreateParams *createPrms)
{
    if (NULL != createPrms)
    {
        createPrms->periodicCbEnable  = (UInt32) TRUE;
        createPrms->instInQueueLength = VPS_DISP_DEF_QUEUE_LEN_PER_INST;
    }

    return;
}

static inline void VpsDispRtParams_init(Vps_DispRtParams *rtPrms)
{
    if (NULL != rtPrms)
    {
        rtPrms->posCfg     = NULL;
        rtPrms->inFrmPrms  = NULL;
        rtPrms->outFrmPrms = NULL;
    }

    return;
}

static inline void VpsDispBufPrgmCbFxnParams_init(
    Vps_DispBufPrgmCbFxnParams *bufPrgmCbPrms)
{
    if (NULL != bufPrgmCbPrms)
    {
        bufPrgmCbPrms->bufPrgmCbFxn = NULL;
    }

    return;
}

static inline void VpsDispBypassLowLatencyCheckParams_init(
    Vps_DispBypassLowLatencyCheckParams *bypassPrms)
{
    if (NULL != bypassPrms)
    {
        bypassPrms->bypassLowLatencyCheck = (UInt32) FALSE;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_DISPLAY_H_ */

/* @} */
