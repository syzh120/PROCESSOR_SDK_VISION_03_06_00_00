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
 *  \file vpshal_issrsz.h
 *
 *  \brief HAL Header file for RSZ
 *  This file exposes the HAL APIs for ISS RSZ module
 *
 */

#ifndef VPSHAL_ISS_RSZ_H_
#define VPSHAL_ISS_RSZ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/**
 * DownScaling Ratio = 1/(2raisedto(H or B) + 1) Range is 1/2 to 1/256
 * Interpolation = 256/N, Init Phase is p/256
 * Interpolation Method is 2-tap Linear or 4-tap Cubic
 * TODO
 *  1, Add support for DownScaling mode and its configuration,
 *     current hal supports only normal mode of scaling
 *
 */
#include <ti/drv/vps/include/iss/vps_cfgrsz.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief RSZ maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define ISSHAL_RSZ_MAX_INST             (1U)

/**
 *  \brief Maximum number of independent resized output possible from
 *         same input. Essintially defines the number of independent resizers
 *         present in the RSZ module
 */
#define ISSHAL_RSZ_MAX_RSZ_OUTPUT       (2U)

/* Control IOCTLs supported by Resizer */

/**
 *  \brief Ioctl for setting Resizer input Source,
 *         this ioctl takes pointer to isshalrszInputSrc_t as an argument
 */
#define ISSHAL_IOCTL_RSZ_SET_INSRC         (VPS_HAL_ISS_IOCTL_RSZ_BEGIN + \
                                            0U)

/**
 *  \brief Ioctl for Getting Default Configuration, this ioctl fills
 *         up complete isshalrszConfig_t structure and returns.
 */
#define ISSHAL_IOCTL_RSZ_GET_DEFAULTCFG    (VPS_HAL_ISS_IOCTL_RSZ_BEGIN + \
                                            1U)

/**
 *  \brief YUV420 Resizer command.
 *          YUV420 resizer is implemented as 2 step process. First luma is
 *          processed followed by chroma. This command configures RSZ for
 *          processing chroma.
 */
#define ISSHAL_IOCTL_RSZ_SET_CHROMA_PROCCFG (VPS_HAL_ISS_IOCTL_RSZ_BEGIN + \
                                             2U)

#if (ISSHAL_IOCTL_RSZ_SET_CHROMA_PROCCFG > VPS_HAL_ISS_IOCTL_RSZ_END)
    #error "Increase VPS_HAL_ISS_IOCTL_RSZ_NUM in vpshal_iss.h file"
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Enum for Input source for the Resizer
 */
typedef enum isshalrszInputSrc
{
    ISSHAL_RSZ_INP_SRC_IPIPE = 0x0,
    /**< Resizer Input source is IPIPE */
    ISSHAL_RSZ_INP_SRC_IPIPEIF = 0x1,
    /**< Resizer Input source is IPIPE Interface */
    ISSHAL_RSZ_INP_SRC_MAX = 0x2,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    ISSHAL_RSZ_INP_SRC_FORCE_INT = 0x7FFFFFFF
                                   /**< This will ensure enum is not packed, will always be contained in int */
} isshalrszInputSrc_t;

/**
 *  \brief Enum to define the various RSZ instance.
 */
typedef enum isshalrszInstId
{
    ISSHAL_RSZ_INST_0 = 0,
    /**< Rsz Instance Id 0. */
    ISSHAL_RSZ_INST_MAX_ID = 1,
    /**< Max - used for error check. */
    ISSHAL_RSZ_INST_FORCE_INT = 0x7FFFFFFF
                                /**< This will ensure enum is not packed, will always be contained in int */
} isshalrszInstId_t;

/**
 *  \brief Structure containing resizer input/source configuration like
 *         input dataformat, input source, processing window etc.
 */
typedef struct isshalrszSrcConfig
{
    Fvid2_DataFormat      inputDataFormat;
    /**< Input DataFormat can be
     *      FVID2_DF_YUV422I_YUYV,
     *      FVID2_DF_BAYER_RAW,
     *      FVID2_DF_YUV420SP_UV */

    vpsissRszOpMode_t     opMode;
    /**< Resizer Operation Mode, can be bypass, pass through or resizing
     *   resizing mode is supported only for the YUV input format.
     *   For the Raw */

    isshalrszInputSrc_t   inpSrc;
    /**< Selects the Resizer input source, ie IPIPEIF or IPIPE */

    Fvid2_CropConfig      procWin;
    /**< Window to be processed, RSZ module crops input image to this
     *   size and uses this size for all its processing */

    uint32_t              wrtEnable;
    /**< Enables the use of the wrt signal from the IPIPEIF/IPIPE */

    isshalCtrlClipValue_t lumaClip;
    /**< Clip the Luma Value,
     *   After vertical rescaling and before color conversion,
     *   the output data is saturated (clipped) to this value,
     *   the range is from 0 to 255
     *   it should be set to default value, which is 0 and 255, in
     *   pass-through/bypass modes */
    isshalCtrlClipValue_t chromaClip;
    /**< Clip the Chroma value,
     *   the range is from 0 to 255,
     *   it should be set to default value, which is 0 and 255, in
     *   pass-through/bypass modes */
    Fvid2_ChromaPos       chromaPos;
    /**< The phase position of the output of the chrominance */
    uint32_t              thrLow;
    /**< Low Threshold Value */
    uint32_t              thrHigh;
    /**< High Threshold Value */
    uint32_t              rszLuma;
    /**< When input to resizer is YUV420, its to be handled in two pass process
            where luma is resized one pass and chroma in another.
        Use this flag to configure luma / chroma processing.
        TRUE configure to resize luma, FALSE for chroma
        Valid only when inputDataFormat = FVID2_DF_YUV420SP_UV */
} isshalrszSrcConfig_t;

/**
 *  \brief Configuration parameters of RSZ.
 */
typedef struct isshalrszConfig
{
    isshalrszSrcConfig_t  srcCfg;
    /**< Resizer input configuration */
    uint32_t              numInst;
    /**< Number of valid entries in instCfg */
    vpsissRszInstConfig_t instCfg[VPS_ISS_RSZ_SCALER_MAX];
    /**< Resizer Instance Configuration, Instance */
} isshalrszConfig_t;

/**
 *  \brief Instance specific parameters used at the init.
 */
typedef struct isshalrszInstParams
{
    uint32_t instId;
    /**< Instand Id. For valid values see #isshalrszInstId. */
    uint32_t baseAddress;
    /**< Register base address */
} isshalrszInstParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  VpsHal_issrszInit
 *  \brief RSZ init function.
 *
 *  Initializes RSZ objects.
 *  This function should be called before calling any of RSZ HAL API's.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshalrszInstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
int32_t VpsHal_issrszInit(UInt32                       numInst,
                          const isshalrszInstParams_t *instPrms,
                          Ptr                          arg);

/**
 *  VpsHal_issrszDeInit
 *  \brief RSZ HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_issrszDeInit(Ptr arg);

/**
 *  VpsHal_issrszOpen
 *  \brief This function should be called prior to calling any of the RSZ HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters
 */
VpsHal_Handle VpsHal_issrszOpen(const isshalOpenParams_t *openPrms,
                                Ptr                       arg);

/**
 *  VpsHal_issrszClose
 *  \brief This functions closes the rsz handle and after call to this
 *  function, rsz handle is not valid.
 *
 *  \param handle         Requested RSZ instance
 */
int32_t VpsHal_issrszClose(VpsHal_Handle handle,
                           Ptr           arg);

/**
 *  \brief Sets the entire RSZ configuration to the RSZ registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issrszConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issrszSetConfig(VpsHal_Handle            handle,
                               const isshalrszConfig_t *cfg,
                               Ptr                      arg);

/**
 *  VpsHal_issrszGetConfig
 *  \brief Gets the entire RSZ configuration from the registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issrszConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issrszGetConfig(VpsHal_Handle handle, isshalrszConfig_t *config);

/**
 *  VpsHal_issrszControl
 *  \brief RSZ specific control commands.
 *
 *  \param handle           Instance handle
 *  \param cmd              Control Command
 *  \param cmdArgs          Arguments for the control command, could be null
 *                          depends on the control command
 *  \param arg              not used. should be null
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issrszControl(VpsHal_Handle handle,
                             UInt32        cmd,
                             Ptr           cmdArgs,
                             Ptr           arg);

/**
 *  VpsHal_issrszSetAddress
 *  \brief RSZ Api for setting resizer output address for the given instance.
 *         Still does not support circular buffer addressing.
 *
 *  \param handle           Instance handle
 *  \param instId           Resizer instance Id
 *  \param lumaAddr         Luma Address, must be 16byte aligned
 *  \param chromaAddr       Chroma Address, must be 16byte aligned
 *  \param lumaPitch        LineOffset for Luma buffer, must be 16byte aligned
 *  \param chromaPitch      Line Offset/pitch for chroma buffer must be
 *                          even and 16byte aligned
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issrszSetAddress(VpsHal_Handle           handle,
                                vpsissRszScalerInstId_t instId,
                                Ptr                     lumaAddr,
                                Ptr                     chromaAddr,
                                uint32_t                lumaPitch,
                                uint32_t                chromaPitch);

/**
 *  \brief RSZ Api for enabling the complete resizer module.
 *
 *  \param handle           Instance handle
 *  \param procMode         Processing Mode ie oneshot or free running
 *  \param arg              not used currently
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issrszStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg);

/**
 *  \brief RSZ Api for enabling the given resizer instance.
 *
 *  \param handle           Instance handle
 *  \param instId           Resizer instance id
 *  \param procMode         Processing Mode ie oneshot or free running
 *  \param arg              not used currently
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issrszStartInst(
    VpsHal_Handle           handle,
    vpsissRszScalerInstId_t instId,
    issCtrlProcMode_t       procMode,
    Ptr                     arg);

/**
 *  \brief RSZ Api for stopping the complete resizer module. Used only when
 *         resizer module is enabled in free running mode.
 *
 *  \param handle           Instance handle
 *  \param arg              not used currently
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issrszStop(VpsHal_Handle handle, Ptr arg);

/**
 *  \brief RSZ Api for stopping the resizer instance. Used only when
 *         resizer module is enabled in free running mode.
 *
 *  \param handle           Instance handle
 *  \param arg              not used currently
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issrszStopInst(
    VpsHal_Handle           handle,
    vpsissRszScalerInstId_t instId);

/**
 *  \brief Used to set the clock dividor valua.
 *
 *  The fractional clock divider gates the read requests made to the
 *  input data buffer such that the input data buffer is read at an
 *  average frequency equal to FFCLK instead of FCLK. The value of FFCLK
 *  depends upon the upscaling ratios as well as the input pixel clock:
 *  refer to the functional spec.
 *  We have FFCLK = FCLK / (65536/fractClk) MHz
 *
 *
 *  This function should be called only after calling rszInit Function.
 *
 *  \param handle           Instance handle
 *  \param fractClk         Fractional Clock Value.
 *
 *  \return              Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_issrszSetFractClkDiv(VpsHal_Handle handle, uint32_t fractClk);

/**
 *  \brief Used to set FIFO Threshold level.
 *
 *  The Resizer Stall signal is asserted if 2 lines of circular
 *  buffer are full and the third line has more pixels than
 *  highThrLevel. The Stall signal stays high as long as one
 *  full line is not free for receiving further data.
 *  highThrLevel is in terms of line size and can at max be
 *  programmed equal to the input line size
 *  The Stall signal stays high as long as the sum of the data
 *  in the input buffer FIFOs is greater than or equal to
 *  lowThrLevel. When highThrLevel = lowThrLevel, stall signal will not be
 *  asserted
 *
 *  This function should be called only after calling rszInit Function.
 *
 *  \param handle           Instance handle
 *  \param highThrLevel     Threshold High Level
 *  \param lowThrLevel      Threshold Low Level
 *
 *  \return              Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_issrszSetFifoThresholdLevel(
    VpsHal_Handle handle,
    uint32_t      highThrLevel,
    uint32_t      lowThrLevel);

/**
 *  \brief Used to set DMA Interval.
 *
 *  Used to set the minimum interval btw two consecutive memory
 *  request for resizer #A. Specified in number of interface clock cycles.
 *  Values of 0, 1, and 2 are used as a condition to keep the
 *  bandwidth limiter off. When this function is enabled, this value
 *  must be greater than 10 cycles.
 *
 *  This function should be called only after calling rszInit Function.
 *
 *  \param handle           Instance handle
 *  \param rescaleInstId    Rescale instance Id
 *  \param dmaInt           DMA interval
 *
 *  \return              Returns FVID2_SOK on success else returns error value.
 *
 */
int32_t VpsHal_issrszSetBwLimit(
    VpsHal_Handle           handle,
    vpsissRszScalerInstId_t scaleInstId,
    uint32_t                dmaInt);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_ISS_RSZ_H_ */
