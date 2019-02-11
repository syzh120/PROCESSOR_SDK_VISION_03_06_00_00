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
 *  \file vpshal_isslvdsrx.h
 *
 *  \brief HAL Header file for LVDSRX
 *  This file exposes the HAL APIs for ISS LVDSRX module
 *
 */

#ifndef VPSHAL_ISS_LVDSRX_H_
#define VPSHAL_ISS_LVDSRX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* Notes:
 * 1, Since LVDSRX doesn't have control interface such as port, serial
 *    communication, CSI2 Rx module takes the responsibility for
 *    configuration of each D-PHY module as needed.
 * TODO: Add an ioctl to set the knee and gains for the decompounding block
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief LVDSRX maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define ISSHAL_LVDSRX_MAX_INST              (1U)

/**
 *  \brief Maximum number of PHY supported by LVDS Rx module.
 */
#define ISSHAL_LVDSRX_MAX_PHYS              (4U)

/**
 *  \brief Maximum number of lanes supported in each PHY.
 */
#define ISSHAL_LVDSRX_MAX_LANES_PER_PHY     (4U)

/**
 *  \brief Maximum number of independent input supported.
 */
#define ISSHAL_LVDSRX_MAX_INPUT             (4U)

/**
 *  \brief Number of knee points supported for Compounding block.
 */
#define ISSHAL_LVDSRX_NUM_KNEE_POINTS       (2U)

/**
 *  \brief Number of gains supported for Compounding block.
 */
#define ISSHAL_LVDSRX_NUM_GAINS             (2U)

/**
 *  \brief Enum to define LVDS input camera id.
 *         LVDS supports at 4 camera input.
 */
typedef enum isshallvdsrxInputCameraId
{
    ISSHAL_LVDSRX_INPUT_CAM_ID0 = 0x0,
    /**< LVDS Camera - 1 */
    ISSHAL_LVDSRX_INPUT_CAM_ID1 = 0x1,
    /**< LVDS Camera - 2 */
    ISSHAL_LVDSRX_INPUT_CAM_ID2 = 0x2,
    /**< LVDS Camera - 3 */
    ISSHAL_LVDSRX_INPUT_CAM_ID3 = 0x3,
    /**< LVDS Camera - 4 */
    ISSHAL_LVDSRX_INPUT_MAX_CAM = 0x4,
    /**< LVDS Camera ID max */
    ISSHAL_LVDSRX_INPUT_FORCE_INT = 0x7FFFFFFF
                                    /**< This will ensure enum is not packed, will always be contained in int */
} isshallvdsrxInputCameraId_t;

/**
 *  \brief Enum to define LVDS Protocol Mode.
 */
typedef enum isshallvdsrxOpMode
{
    ISSHAL_LVDSRX_OP_MODE1 = 0x0,
    /**< Serial LVDS mode 1 */
    ISSHAL_LVDSRX_OP_MODE2 = 0x1,
    /**< Serial LVDS mode 2 */
    ISSHAL_LVDSRX_OP_MODE3 = 0x2,
    /**< Serial LVDS mode 3 */
    ISSHAL_LVDSRX_OP_MODE4 = 0x3,
    /**< Serial LVDS mode 4 */
    ISSHAL_LVDSRX_OP_MODE5 = 0x4,
    /**< Serial LVDS mode 5 */
    ISSHAL_LVDSRX_OP_MODE6 = 0x5,
    /**< Serial LVDS mode 6 */
    ISSHAL_LVDSRX_OP_MODE7 = 0x6,
    /**< Serial LVDS mode 7 */
    ISSHAL_LVDSRX_OP_MODE8 = 0x7,
    /**< Serial LVDS mode 8 */
    ISSHAL_LVDSRX_OP_MODE9 = 0x8,
    /**< Serial LVDS mode 9 */
    ISSHAL_LVDSRX_PARALLEL_EMB = 0xe,
    /**< Parallel LVDS mode */
    ISSHAL_LVDSRX_PARALLEL_DISC = 0xF,
    /**< Parallel LVDS mode */
    ISSHAL_LVDSRX_OP_MODE_FORCE_INT = 0x7FFFFFFF
                                      /**< This will ensure enum is not packed, will always be contained in int */
} isshallvdsrxOpMode_t;

/**
 *  \brief Enum to define the various LVDSRX instance.
 */
typedef enum isshallvdsrxInstId
{
    ISSHAL_LVDSRX_INST_0 = 0,
    /**< Vtnf Instance Id 0. */
    ISSHAL_LVDSRX_INST_MAX_ID = 1,
    /**< Max - used for error check. */
    ISSHAL_LVDSRX_INST_FORCE_INT = 0x7FFFFFFF
                                   /**< This will ensure enum is not packed, will always be contained in int */
} isshallvdsrxInstId_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief struct for defining sync pattern fields
 */
typedef struct isshallvdsrxSyncPattern
{
    uint32_t bitMask;
    /**< Specifies the mask bit to be compared.
     *   Ex. set 0x3ff when does pattern matching for low 10bit */
    uint32_t pattern;
    /**< Used to specify sync pattern */
} isshallvdsrxSyncPattern_t;

/**
 *  \brief struct for defining Input Camera config
 */
typedef struct isshallvdsrxConfig
{
    isshallvdsrxInputCameraId_t inputCamId;
    /**< Camera Id, used to configure camera instance in the LVDS Rx */

    isshallvdsrxOpMode_t        opMode;
    /**< LVDS Protocol Mode */
    Fvid2_BitsPerPixel          bpp;
    /**< Pixels size in terms of bits,
     *   only 8, 10, 12, 14, 16 bps are supported by LVDSRX */

    uint32_t                    frameWidth;
    /**< Image line width in number of data words */
    uint32_t                    frameHeight;
    /**< Frame size in number of image lines */
    uint32_t                    maxWidth;
    /**< The maximum line width expected in number of pixels */

    isshallvdsrxSyncPattern_t   sofPtn;
    /**< Start of Frame sync pattern */
    isshallvdsrxSyncPattern_t   eofPtn;
    /**< End of Frame sync pattern */
    isshallvdsrxSyncPattern_t   solPtn;
    /**< Start of Line sync pattern */
    isshallvdsrxSyncPattern_t   eolPtn;
    /**< End of Line sync pattern */
    isshallvdsrxSyncPattern_t   sovblkPtn;
    /**< Start of vertical blanking pattern */

    uint32_t                    enableWdrDecomound;
    /**< Enable/Disable WDR Decompounding */
    uint32_t                    enableMsbAlign;
    /**< MSB, LSB alignment for output pixel data
     *   1: MSB align
     *   0: LSB align */
    uint32_t                    enableDataBigEndian;
    /**< Transmit Format for Data
     *   1: Big Endian Format
     *   0: Little Endian Format */
    uint32_t                    enableSyncBigEndian;
    /**< Transmit Format for Sync
     *   1: Big Endian Format
     *   0: Little Endian Format */
    uint32_t                    enableCrcCheck;
    /**< enables checking of the checksum transmitted from the Sensor */
    uint32_t                    enableFiller;
    /**< Transmitted data includes filier codes,
     *   so it should be removed by enabling this */
    uint32_t                    numPhys;
    /**< Number of PHYs used */
    uint32_t                    numLanes[ISSHAL_LVDSRX_MAX_PHYS];
    /**< Number of lanes in each PHYs */
} isshallvdsrxConfig_t;

/**
 *  struct isshallvdsrxInstParams
 *  \brief Instance specific parameters used at the init.
 */
typedef struct isshallvdsrxInstParams
{
    uint32_t instId;
    /**< Instand Id. For valid values see #isshallvdsrxInstId. */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t maxPhys;
    /**< Maximum number of PHY supported */
    uint32_t maxLanesPerPhy;
    /**< Maximum number of lanes supported per phy */
} isshallvdsrxInstParams_t;

/**
 *  struct isshallvdsrxOpenParams
 *  \brief Structure to identify a LVDSRX HAL instance.
 */
typedef struct isshallvdsrxOpenParams
{
    uint32_t instId;
    /**< Instance ID. For valid values see #isshallvdsrxInstId. */
} isshallvdsrxOpenParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  VpsHal_isslvdsrxInit
 *  \brief LVDSRX init function.
 *
 *  Initializes LVDSRX objects. Also resets the LVDS
 *  This function should be called before calling any of LVDSRX HAL API's.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshallvdsrxInstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
int32_t VpsHal_isslvdsrxInit(UInt32                          numInst,
                             const isshallvdsrxInstParams_t *instPrms,
                             Ptr                             arg);

/**
 *  VpsHal_isslvdsrxDeInit
 *  \brief LVDSRX HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_isslvdsrxDeInit(Ptr arg);

/**
 *  VpsHal_isslvdsrxOpen
 *  \brief This function should be called prior to calling any of the LVDSRX HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters
 */
VpsHal_Handle VpsHal_isslvdsrxOpen(
    const isshallvdsrxOpenParams_t *openPrms,
    Ptr                             arg);

/**
 *  VpsHal_isslvdsrxClose
 *  \brief This functions closes the lvdsrx handle and after call to this
 *  function, lvdsrx handle is not valid.
 *
 *  \param handle         Requested LVDSRX instance
 */
int32_t VpsHal_isslvdsrxClose(VpsHal_Handle handle, Ptr arg);

/**
 *  \brief Sets the entire LVDSRX configuration to the LVDSRX registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_isslvdsrxConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_isslvdsrxSetConfig(VpsHal_Handle               handle,
                                  const isshallvdsrxConfig_t *cfg,
                                  Ptr                         arg);

/**
 *  VpsHal_isslvdsrxGetConfig
 *  \brief Gets the entire LVDSRX configuration from the registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_isslvdsrxConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_isslvdsrxGetConfig(
    VpsHal_Handle         handle,
    isshallvdsrxConfig_t *config);

/**
 *  VpsHal_isslvdsrxControl
 *  \brief LVDSRX specific control commands.
 *
 *  \param handle           Instance handle
 *  \param cmd              Control Command
 *  \param cmdArgs          Arguments for the control command, could be null
 *                          depends on the control command
 *  \param arg              not used. should be null
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_isslvdsrxControl(VpsHal_Handle handle,
                                UInt32        cmd,
                                Ptr           cmdArgs,
                                Ptr           arg);

/**
 *  VpsHal_isslvdsrxStart
 *  \brief LCDSRx Start a Camera.
 *
 *  \param handle           Instance handle
 *  \param procMode         Processing Mode, oneShot or FreeRun
 *  \param inputCamId       InputCameraId
 *
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_isslvdsrxStart(
    VpsHal_Handle               handle,
    issCtrlProcMode_t           procMode,
    isshallvdsrxInputCameraId_t inputCamId);

/**
 *  VpsHal_isslvdsrxStart
 *  \brief LCDSRx Stop a Camera.
 *
 *  \param handle           Instance handle
 *  \param inputCamId       InputCameraId
 *
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_isslvdsrxStop(
    VpsHal_Handle               handle,
    isshallvdsrxInputCameraId_t inputCamId);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_ISS_LVDSRX_H_ */

