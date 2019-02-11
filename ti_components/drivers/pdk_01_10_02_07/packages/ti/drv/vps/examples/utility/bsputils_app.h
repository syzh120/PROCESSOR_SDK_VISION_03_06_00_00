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
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_APP_API Application helper APIs
 *  @{
 */

/**
 *  \file bsputils_app.h
 *
 *  \brief Header file to use application level helper functions.
 */

#ifndef BSPUTILS_APP_H_
#define BSPUTILS_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/vps.h>
#if defined (VPS_VIP_BUILD) || defined (VPS_CAL_BUILD)
#include <ti/drv/vps/include/vps_capture.h>
#endif
#ifdef VPS_VPE_BUILD
#include <ti/drv/vps/include/vpe/vps_m2m.h>
#endif
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/vps_display.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined(BARE_METAL)
/** \brief for bare metal there is no XDC and hence map System_printf to printf */
#define System_printf printf

/** \brief for bare metal there is no System_flush implementation */
#define System_flush()
#endif


/** \brief Magic String for App Test Status : PASS */
#define BSPUTILS_APP_TST_STATUS_PASS    (0x50415353U)

/** \brief  Magic String for App Test Status : FAIL */
#define BSPUTILS_APP_TST_STATUS_FAIL    (0x46417376U)

/** \brief  Magic String for App Test Status : Started */
#define BSPUTILS_APP_TST_STATUS_INIT    (0x494E4954U)

/** \brief  Magic String for App Test Status : AppImage not found*/
#define BSPUTILS_APP_TST_STATUS_AINF    (0x41494E46U)

/** \brief  OCMC Address used to store App Test Status */
#define BSPUTILS_APP_TST_ADDR           (0x4033B100U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief BSP application utils init function.
 *
 *  Init function which allocates semaphore and initializes
 *  global objects.
 *
 *  This function should be called before calling any of the below API's and
 *  should be called only once after doing all other module initialization
 *  like FIVD2 init, device init and platform init.
 *
 *  \return BSP_SOK on success else appropiate error code on failure.
 */
Int32 BspUtils_appInit(void);

/**
 *  \brief BSP application utils deinit function.
 *
 *  De-init function which frees already allocated objects.
 *
 *  \return BSP_SOK on success else appropriate error code on failure.
 */
Int32 BspUtils_appDeInit(void);

/**
 *  \brief BSP application utils function to call all the default init
 *  functions.
 *
 *  Note that this function calls the BspUtils_appInit() as well
 *  and hence the application should not call BspUtils_appInit() separately.
 *
 *  \param isI2cInitReq     [IN]    TRUE  -> Calls I2C/device init.
 *                                  FALSE -> I2C and device init are not called.
 *                                  This will be overridden for non-EVM based
 *                                  platforms and FALSE will be used.
 *
 *  \return BSP_SOK on success else appropriate error code on failure.
 */
Int32 BspUtils_appDefaultInit(UInt32 isI2cInitReq);

/**
 *  \brief BSP application utils function to call all the default de-init
 *  functions.
 *
 *  Note that this function calls the BspUtils_appDeInit() as well
 *  and hence the application should not call BspUtils_appDeInit() separately.
 *
 *  \param isI2cDeInitReq   [IN]    TRUE  -> Calls I2C/device init.
 *                                  FALSE -> I2C/device deinit are not called.
 *                                  This will be overridden for non-EVM based
 *                                  platforms and FALSE will be used.
 *
 *  \return BSP_SOK on success else appropriate error code on failure.
 */
Int32 BspUtils_appDefaultDeInit(UInt32 isI2cDeInitReq);

/**
 *  \brief BSP application utils function to call all the default init
 *  functions related to serial driver. This doesn't call VPS init.
 *
 *  Note that this function calls the BspUtils_appInit() as well
 *  and hence the application should not call BspUtils_appInit() separately.
 *
 *  \param isI2cInitReq     [IN]    TRUE  -> Calls I2C/device init.
 *                                  FALSE -> I2C and device init are not called.
 *                                  This will be overridden for non-EVM based
 *                                  platforms and FALSE will be used.
 *
 *  \return BSP_SOK on success else appropriate error code on failure.
 */
Int32 BspUtils_appDefaultSerialInit(UInt32 isI2cInitReq);

/**
 *  \brief BSP application utils function to call all the default de-init
 *  functions related to serial driver. This doesn't call VPS de-init.
 *
 *  Note that this function calls the BspUtils_appDeInit() as well
 *  and hence the application should not call BspUtils_appDeInit() separately.
 *
 *  \param isI2cDeInitReq   [IN]    TRUE  -> Calls I2C/device init.
 *                                  FALSE -> I2C/device deinit are not called.
 *                                  This will be overridden for non-EVM based
 *                                  platforms and FALSE will be used.
 *
 *  \return BSP_SOK on success else appropriate error code on failure.
 */
Int32 BspUtils_appDefaultSerialDeInit(UInt32 isI2cDeInitReq);

/**
 *  \brief Prints memory status liek OSAL objects, peak mem used etc...
 */
void BspUtils_appPrintMemStatus(void);

/**
 *  \brief Function to create filename based on the data format buffer width and
 *  buffer height
 *
 *  \param fileNameString   [IN]    char ptr to store File name.
 *  \param fileNameSize     [IN]    Size of File name string.
 *  \param fileStr          [IN]    File name prefix string.
 *  \param dataFormat       [IN]    FVID2 Data format.
 *  \param width            [IN]    Width of buffer in pixels.
 *  \param height           [IN]    Height of buffer in lines.
 */
void BspUtils_appGetFileName(Char       *fileNameString,
                             UInt32      fileNameSize,
                             const Char *fileStr,
                             UInt32      dataFormat,
                             UInt32      width,
                             UInt32      height);

/**
 *  \brief Function to print the loadRaw command used to load buffers from file
 *  through CCS scripting console.
 *
 *  \param fileStr          [IN]    File name string.
 *  \param bufAddr          [IN]    Buffer address.
 *  \param dataFormat       [IN]    FVID2 Data format.
 *  \param width            [IN]    Width of buffer in pixels.
 *  \param height           [IN]    Height of buffer in lines.
 */
void BspUtils_appPrintLoadRawCmd(const Char *fileStr,
                                 const void *bufAddr,
                                 UInt32      dataFormat,
                                 UInt32      width,
                                 UInt32      height);

/**
 *  \brief Function to print the saveRaw command used to save buffers to file
 *  through CCS scripting console.
 *
 *  \param fileStr          [IN]    File name string.
 *  \param bufAddr          [IN]    Buffer address.
 *  \param dataFormat       [IN]    FVID2 Data format.
 *  \param width            [IN]    Width of buffer in pixels.
 *  \param height           [IN]    Height of buffer in lines.
 *  \param bufSize          [IN]    Buffer size in bytes so that multiple
 *                                  buffers could be saved.
 */
void BspUtils_appPrintSaveRawCmd(const Char *fileStr,
                                 const void *bufAddr,
                                 UInt32      dataFormat,
                                 UInt32      width,
                                 UInt32      height,
                                 UInt32      bufSize);

/**
 * \brief   This function used to log the test result of Examples
 *
 * \param  testResult   Status of testResult
 */
void BspUtils_appLogTestResult(UInt32 testResult);

/**
 * \brief This function returns the CRC of the provided buffer
 *
 * \param  bufPtr   Buffer pointer
 * \param  numBytes Buffer size in bytes
 *
 * \return Calculated CRC.
 */
UInt32 BspUtils_appGetCrc(const UInt8 *bufPtr, UInt32 numBytes);

/* ========================================================================== */
/*                VIP Capture Driver Related Helper functions                 */
/* ========================================================================== */

#if defined (VPS_VIP_BUILD) || defined (VPS_CAL_BUILD)

/**
 *  \brief Prints the capture instance status information by calling the
 *  driver get status IOCTL.
 *
 *  \param fvidHandle   [IN] Valid capture driver handle.
 *  \param instId       [IN] Instance ID used for print.
 *  \param numStream    [IN] Number of stream opened.
 *  \param numCh        [IN] Number of channels per stream.
 *  \param execTime     [IN] Execution time from capture start to capture
 *                           stop in msec.
 *
 */
void BspUtils_appPrintCaptStatus(Fvid2_Handle fvidHandle,
                                 UInt32       instId,
                                 UInt32       numStream,
                                 UInt32       numCh,
                                 UInt32       execTime);

#endif

/* ========================================================================== */
/*                  M2M VPE Driver Related Helper functions                   */
/* ========================================================================== */

#ifdef VPS_VPE_BUILD
/**
 *  \brief Allocate context buffer according to the VPE driver need and
 *  provide it to the driver.
 *
 *  This function internally uses BspUtils_memAlloc() to allocate buffer memory.
 *
 *  \param fvidHandle   [IN] Valid M2M VPE driver handle.
 *  \param numCh        [IN] Number of channel to configure. This is typically
 *                      the number of channels provided at create time.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 BspUtils_appAllocDeiCtxBuffer(Fvid2_Handle fvidHandle, UInt32 numCh);

/**
 *  \brief Get the context buffers back from the VPE driver and free them.
 *
 *  This function internally uses BspUtils_memFree() to free buffer memory.
 *
 *  \param fvidHandle   [IN] Valid M2M VPE driver handle.
 *  \param numCh        [IN] Number of channel to configure. This is typically
 *                      the number of channels provided at create time.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 BspUtils_appFreeDeiCtxBuffer(Fvid2_Handle fvidHandle, UInt32 numCh);

/**
 *  \brief Prints the M2M VPE driver create status information.
 *
 *  \param createStatus [IN] Pointer to M2M VPE driver create status.
 */
void BspUtils_appPrintM2mVpeCreateStatus(
    const Vps_M2mCreateStatus *createStatus);

/**
 *  \brief Sets the VPE lazy loading parameters through the VPS control driver.
 *
 *  \param vpeInstId    [IN] VPE driver instance ID.
 *  \param scalerId     [IN] Scaler ID.
 *  \param lazyLoadingEnable [IN] Indicates whether lazy loading is to be
 *                                enabled.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 BspUtils_appSetVpeLazyLoad(UInt32 vpeInstId,
                                 UInt32 scalerId,
                                 Bool   lazyLoadingEnable);

#endif  /* #ifdef VPS_VPE_BUILD */

/* ========================================================================== */
/*                DSS Display Driver Related Helper functions                 */
/* ========================================================================== */

#ifdef VPS_DSS_BUILD

/**
 *  \brief Prints the display instance status information by calling the
 *  driver get status IOCTL.
 *
 *  \param fvidHandle   [IN] Valid display driver handle.
 *  \param instId       [IN] Instance ID used for print.
 *  \param execTime     [IN] Execution time from display start to display
 *                           stop in msec.
 *
 */
void BspUtils_appPrintDispStatus(Fvid2_Handle fvidHandle,
                                 UInt32       instId,
                                 UInt32       execTime);

/**
 *  \brief Prints the display controller error status information by calling the
 *  driver get error stat IOCTL.
 *
 *  \param fvidHandle   [IN] Valid display controller driver handle.
 *
 */
void BspUtils_appPrintDctrlStatus(Fvid2_Handle fvidHandle);
/**
 *  \brief Prints the display driver create status information.
 *
 *  \param createStatus [IN] Pointer to display driver create status.
 */
void BspUtils_appPrintDispCreateStatus(
    const Vps_DispCreateStatus *createStatus);

#endif  /* #ifdef VPS_DSS_BUILD */

/**
 *  \brief Services the watchdog timer set by SBL.
 *         For TDA2x/TDA2Ex wd timer 2 is refreshed.
 *         For TDA3xx RTI instance 4 is refreshed if enabled.
 *
 */
void BspUtils_appServiceWatchdog(void);

/**
 *  \brief API to get access to the application default EDMA handle as a pointer
 *         to void.
 *
 *  \return EDMA3_DRV_Handle
 */
void * BspUtils_appGetEdmaHandle(void);

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_APP_H_ */

/* @} */

/**
 *  \defgroup BSPEXAMPLE_API Sample Example API
 *
 *  The API defined in this module are utility APIs OUTSIDE of the device
 *  drivers.
 *
 *  Example code makes use of these APIs to implement sample application which
 *  demonstrate the driver in different ways.
 */

/**
 *  \ingroup BSPEXAMPLE_API
 *  \defgroup BSPUTILS_API Sample Example - Utility library API
 */
