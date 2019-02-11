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
 *  \file vpscore_captureapi.c
 *
 *  \brief This file implements core functions required by CAL. Primarily will
 *          be used by drivers.
 *
 *  TODO - The start / stop mechanism should be changed. Currently, we are
 *          relying on starting PPI for start / stop.
 *          In Start start PPI is not started already, start DMA write streams.
 *          In stop, stop just the DMA write. If the number of opens == 1
 *              then stop the PPI also. - Done
 *
 *          Handle error interrupt
 *
 *          When the last stream is stopped, ensure to turn OFF PPI
 *
 *          streamType - Supplied by apps, is not handled by APPs. This is
 *              required when meta data is to be received.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>

#include <ti/drv/vps/src/vpslib/common/cal_evtmgr.h>
#include <ti/drv/vps/src/vpslib/common/irm_resrcMgr.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>

#include <ti/drv/vps/src/vpslib/common/vps_common.h>

#include <ti/drv/vps/src/vpslib/calcore/vpscore_capture.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_isscal.h>

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */

/** \brief All sub modules of CAL */
#define CAL_ALL_SUB_MODULE  (VPS_ISS_CAPT_CAL_SUB_PPI_ID_0          | \
                             VPS_ISS_CAPT_CAL_SUB_PPI_ID_1          | \
                             VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID    | \
                             VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID       | \
                             VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID       | \
                             VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID       | \
                             VPS_ISS_CAPT_CAL_SUB_BYS_OUT_ID        | \
                             VPS_ISS_CAPT_CAL_SUB_BYS_IN_ID         | \
                             VPS_ISS_CAPT_CAL_SUB_VPORT_ID          | \
                             VPS_ISS_CAPT_CAL_SUB_DMA_RD_ID         | \
                             VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID         | \
                             VPS_ISS_CAPT_CAL_SUB_CPORT_ID)

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief Its possible to get 2 interrupts,
                1 when when DMA writes first byte of a given frame
                other when DMA writes last byte of a given frame

            By default we rely on start-of-frame interrupt to notify successful
            capture of previous frame.

            In cases where applications requires to be notified as soon a frame
            is captured, the end-of-frame notification can be enabled with
            VCORE_ISS_CAPT_CAL_SET_SUB_FRM_PRMS

            This is a per instance flag, either CAL operates with dual
                interrupt or single interrupt */
#define CAL_USE_DUAL_INTERRUPT      ((uint32_t)FALSE)

/** \brief When defined, application will have follow below steps to start
            1. Init, Create & set config
            2. Prime with 1 buffer for each stream
            3. Start
                - Driver will request new "empty" frame when required.
            When un defined
            1. Init, Create & set config
            2. Start
                - Driver will request new "empty" frame when required.
                - Note no priming is required.
            */
/* #define VPS_CAL_SEPERATE_API_FOR_PRIME */

/** \brief When this macro is defined,
            The core frames that is currently programmed and frame under
            reception, will be returned on stop.
            when undefined, the caller will have to explicitly keep track of
            frames in the core. Core will not return the same, when stopped.
            */
/* #define VPS_CAL_FLUSH_ON_STOP */

/** \brief Maximum virtual channel, used to log virtual channel errors */
#define CAL_MAX_VIRTUAL_CHAN        (0x4U)
/** \brief Poistion at which BYS_IN overflow error is logged */
#define CAL_BYS_IN_POSITION         (0x4U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**< Forward Declaration */
typedef struct vpscoreissCaptInstObj vpscoreissCaptInstObj_t;

/** \brief Possible streams mode with in CAL. A given stream could be
            1. written out by CAL
            2. processed but not written
            3. processed by ISP (an entity outside CAL)*/
typedef enum vpscoreissCaptStreamMode
{
    VCORE_CAL_STREAM_MODE_NONE = 0x0,
    /**< The stream is not destined to any. Invalid */
    VCORE_CAL_STREAM_MODE_CAL_WRITE = 0x1,
    /**< Is a valid stream within CAL, will be written by CAL to memory */
    VCORE_CAL_STREAM_MODE_CAL = 0x2,
    /**< Is a valid stream with CAL, but CAL will not write it to memory */
    VCORE_CAL_STREAM_MODE_ISP = 0x3,
    /**< Is a valid stream will be processed by ISP. No CAL operation required
            will be processed/written by ISP */
    VCORE_CAL_STREAM_MODE_MAX = 0x4,
    /**< Max stream, end marker */
    VCORE_CAL_STREAM_MODE_FORCE_INT = 0x7FFFFFFF
                                      /**< This will ensure enum is not packed,
                                          will always be contained in int */
} vpscoreissCaptStreamMode_t;

/** \brief Error configuration */
typedef struct vpscoreissCaptErrObj
{
    uint32_t                cmplxIoId;
    /**< Complex IO ID */
    vpscoreissCaptInstObj_t *pInstObj;
    /**< Pointer back to instance object */
    vpsissCalErrorCfg_t     errCfg;
    /**< Error configuration */
    void                    *emErrorHndl;
    /**< Event manager handle for CAL errors */
    uint32_t                fifoOverFlow[CAL_MAX_VIRTUAL_CHAN + 1U];
    /**< The PPI FIFO overflowed, +1 for BYS_IN port */
    uint32_t                eccCouldNotCorrect[CAL_MAX_VIRTUAL_CHAN + 1U];
    /**< There were more than 1 bit errors, could not be corrected */
    uint32_t                crcMisMatch[CAL_MAX_VIRTUAL_CHAN + 1U];
    /**< CRC mismatch occurred, +1 for BYS_IN port  */
    uint32_t                eccCorrected[CAL_MAX_VIRTUAL_CHAN + 1U];
    /**< 1 Bit ECC error was corrected, +1 for BYS_IN port  */
} vpscoreissCaptErrObj_t;

/** \brief Capture Instance object */
struct vpscoreissCaptInstObj
{
    uint32_t                    isInited;
    /**< Flag to specify if an instance is initialized */
    vpsissCaptInstId_t          instId;
    /**< Platform data */
    uint32_t                    useDmaEndIntr;
    /**< TRUE: Enables DMA Frame End Interrupt
     *   FALSE: No DMA Frame End Interrupt,
     *          all processing is done in DMA Frame Start interrupt */
    BspOsal_SemHandle           instLock;
    /**< Instance mutual exclusion */

    vcoreissCaptInitParams_t    initPrms;
    /**< Init Parameters for post initialization references. */

    VpsHal_Handle               calHalHandle;
    /**< CAL hal handle */
    isshalCalCfg_t              calCfg;
    /**< Current configuration, as supplied by driver / application. */
    isshalCalInstCfg_t          instCfg;
    /**< Current instance config */

    UInt32                      isStarted;
    /**< Flag to indicate if capture on this instance has started */
    UInt32                      numOpens;
    /**< Number of handles opened */
    vpscoreissCaptErrObj_t      errObj[VPS_ISS_CAL_MAX_CMPLXIO_INST];
    /**< Instance error handling configuration */
    uint32_t                    streamIdToVcMap[VPS_ISS_CAL_MAX_STREAMS];
    /**< Maps stream ID to virtual channel. Value 0x4 is used to indicate
            data is sourced from BYS_IN */
    uint32_t                    streamIdToPpiMap[VPS_ISS_CAL_MAX_STREAMS];
    /**< Stream ID and it's associated PPI/PHY ID */
    isshalCalLineEventCfg_t  lineEventCfg;
    /**< Place holder for line event configurations */

} ;

/** \brief Capture CAL handle object */
typedef struct vpscoreissCaptCalHndlObj
{
    UInt32                     isAllocated;
    /**< Flag to keep track if the handle object is allocated or not */
    vpscoreissCaptInstObj_t   *pInstObj;
    /**< Instance object */
    VpsCore_OpenPrms           openPrms;
    /**< Core Open Parameters containing callbacks
     *   for requesting a new frame and for submitting completed frame
     *   to the upper layer
     *   It also has callback to mark completion of the frame */
    UInt32                     numStreams;
    /**< Number of streams allocated */
    vpsissCaptureBlocks_t      allocatedRes[VPS_ISS_CAL_MAX_STREAMS];
    /**< Instances of resource allocated */

    void                      *emDmaStartHndl[VPS_ISS_CAL_MAX_STREAMS];
    /**< Event manager handle for DMA start */
    void                      *emDmaCmpltHndl[VPS_ISS_CAL_MAX_STREAMS];
    /**< Event manager handle for DMA completion */
    UInt32                     dmaStartEvent[VPS_ISS_CAL_MAX_STREAMS];
    /**< Events associated with this instance and streams that are active */
    UInt32                     eventToStreamIdMap[VPS_ISS_CAL_MAX_STREAMS];
    /**< Map between event to associated stream id */
    UInt32                     dmaCmpltEvent[VPS_ISS_CAL_MAX_STREAMS];
    /**< Events associated with this instance and streams that are active */

    UInt32                     bitsPerPix[VPS_ISS_CAL_MAX_STREAMS];
    /**< Actual bits per pixel required, computed from Fvid2_BitsPerPixel
     *      specified as part of setParams */

    UInt32                     fvid2DataType;
    /**< FVID2 dataType computed / owned by the core
     *   Unused currently - TBD: use in getParams */
    UInt32                     fvid2bpp;
    /**< FVID2 bpp computed / owned by the core
     *   Unused currently - TBD: use in getParams */
    isshalCalDmaVcCfg_t        calDmaVcCfg;
    /**< CAL configurations computed / owned by the core */

    isshalCalBufferAddr_t      bufCfg;
    /**< Buffer to be used to update HAL with new buffers */
    volatile VpsCore_Frame    *currBufs[VPS_ISS_CAL_MAX_STREAMS][2U];
    /**< Pointer to buffer that is currently owned by this core */
    volatile UInt32            curr[VPS_ISS_CAL_MAX_STREAMS];
    /**< Index indicating the buffer that's is currently being captured into */
    volatile UInt32            next[VPS_ISS_CAL_MAX_STREAMS];
    /**< Index indicating the next buffer that programmed to be received into */
    uint32_t                   firstDmaStartIntr[VPS_ISS_CAL_MAX_STREAMS];
    /**< Flag to indicate whether this is first DMA start Interrupt
     *   First DMA start interrupt should not mark frame as done as it is
     *   just started capturing. */
    vcoreissCaptOpenParams_t   coreOpenPrms;
    /**< Copy of the core open parameters, containing request frame
     *   and frame done callback. This will be used by the ISP layer */
    uint32_t                   bysOutCportId;
    /**< Cport id of the Bys output */
    uint32_t                   vportCportId;
    /**< Cport id of the vport output */

    vpscoreissCaptStreamMode_t streamMode[VPS_ISS_CAL_MAX_STREAMS];
    /**< Each of stream could be processed by CAL or other entity. Each stream
            when created will be associated an entity that processes it. */

    void                      *emSubFrmCmpltHndl;
    /**< Event manager handle for Sub Frame reception completion */
    uint32_t                   subFrmstreamId;
    /**< Stream ID, for which X line callback is enabled */
    Fvid2_SubFrameInfo         currSubFrame[VPS_ISS_CAL_MAX_STREAMS][2U];
    /**< Place holder for sub-frame Info */
    uint32_t                   isSubFrameCfgValid;
    /**< Flag indicating valid / in valid sub-frame config. FALSE is invalid
        and TRUE is valid */
    vcoreissCaptSubFrameCfg_t   subFrameCfg;
    /**< Configuration for sub-frame and end of frame */
} vpscoreissCaptCalHndlObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if typecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
/** \brief Function to get the core properties
 *
 *  \param instObj     Pointer to instance Object
 *  \param property    Pointer to property, out parameter
 *
 *  \return            return FVID2_SOK on success
 *                     error code on fail
 */
Int32 vcoreCaptGetProperty(VpsCore_Inst      instObj,
                           VpsCore_Property *property);

/** \brief Opens the Core, in turn, opens the required hals, sets the defaults
 *         parameters
 *
 *  \param inst        Pointer to instance id
 *  \param openPrms    Core open parameters containing get/put frame
 *                     function pointers
 *  \param coreOpenPrms Core Specific Open Parameter, contains list of
 *                     modules required for this instance
 *  \param coreRetPrms Returns Params
 *
 *  \return            Valid core handle on success
 *                     NULL on Failure
 */
VpsCore_Handle vcoreCaptOpen(VpsCore_Inst            inst,
                             const VpsCore_OpenPrms *openPrms,
                             const void             *coreOpenPrms,
                             void                   *coreReturnPrms);

/** \brief Closes the core
 *
 *  \param handle      core handle
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreCaptClose(VpsCore_Handle handle);

/** \brief Sets the parameters, used to enable specific streams,
 *         frame size, frame dataformat etc.
 *
 *  \param handle      core handle
 *  \param params      Pointer to the parameters
 *  \param argsNotUsed Return parameters
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreCaptSetParams(VpsCore_Handle handle,
                           const void    *params,
                           void          *argsNotUsed);

/** \brief Start the capture
 *
 *  \param handle      core handle
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreCaptStart(VpsCore_Handle handle);

/** \brief Stop the capture
 *
 *  \param handle      core handle
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreCaptStop(VpsCore_Handle handle);

/** \brief Configures the frame to be received. Should be called only once
 *          before CAL is started, should rely on requestFrame and frameComplete
 *          supplied during open.
 *
 *  \param handle                   Core handle
 *  \param frame                    Pointer to frame
 *  \param bypassLowLatencyCheck    Low latency check bypass/enable
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
Int32 vcoreCaptProgBuf(VpsCore_Handle handle,
                       VpsCore_Frame *frame,
                       UInt32         bypassLowLatencyCheck);

/** \brief Get the current parameters
 *
 *  \param handle      core handle
 *  \param params      Pointer to the parameters
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreCaptGetParams(VpsCore_Handle handle,
                           void          *params);

/**  \brief Function to process control commands
 *
 *  \param handle      core handle
 *  \param cmd         control command
 *  \param appArgs     Command specific arguments
 *  \param drvArgs     Extra arguments
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreCaptControl(VpsCore_Handle handle,
                         UInt32         cmd,
                         void          *appArgs,
                         void          *drvArgs);

/**  \brief Write DMA has started writing, called by event manager.
 *              This ISR would be called only in case CAL is writing to memory.
 *
 *  \param event       Arrays of events which occurred
 *  \param numEvents   number of valid entries in event
 *  \param arg         Not used
 *
 */
static void vcoreCaptDmaStartCb(const UInt32 *event,
                                UInt32        numEvents,
                                Ptr           arg);

/** \brief Write DMA has completed writing, called by event manager
 *              This ISR would be called only in case CAL is writing to memory.
 *
 *  \param event       Arrays of events which occurred
 *  \param numEvents   number of valid entries in event
 *  \param arg         Not used
 *
 */
static void vcoreCaptDmaCmpltCb(const UInt32 *event,
                                UInt32        numEvents,
                                Ptr           arg);

/** \brief Configured line has been received, called by event manager
 *          This ISR would be called only when X line event is configured.
 *
 *  \param event       Arrays of events which occurred
 *  \param numEvents   number of valid entries in event
 *  \param arg         Not used
 *
 */
static void vcoreCaptXlineCmpltCb(const UInt32 *event,
                                UInt32        numEvents,
                                Ptr           arg);

/** \brief Frame Done Processing - provide frame info and execute callback
 *  function
 */
static int32_t vcoreCaptFrameDoneProc(vpscoreissCaptCalHndlObj_t *pHndlObj,
                                      uint32_t                    streamId);
/** \brief Sub Frame completed - Will check for errors and issue callback's.
 *          Is expected to be called on write DMA completion also (end-of-frame)
 *
 */
static int32_t vcoreCaptSubFrameDoneProc(vpscoreissCaptCalHndlObj_t *pHndlObj,
                                        uint32_t                    streamId,
                                        uint32_t                    isEof);
/** \brief Function to deallocate CAL sub modules
 *
 *  \param calId        CAL Id
 *  \param resDeAlloc   Pointers to array of size "cnt"
 *  \param cnt          Number of resources pointed by resDeAlloc
 *
 *  \return             FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptDeAllocCalRes(
    Irm_Modules_t         calId,
    vpsissCaptureBlocks_t resDeAlloc[
        VPS_ISS_CAL_MAX_STREAMS],
    UInt32                cnt);

/** \brief Function to allocate CAL handle and sub modules required. Also
 *          determines if a given stream is to be processed by CAL / Others
 *
 *  \param calId        CAL Id
 *  \param pInstObj     Pointer to instance
 *  \param pOpenParams  Application specified parameters
 *  \param pOpenRtnPrms Application specified return values
 *
 *  \return             FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptAllocCalRes(
    Irm_Modules_t                   calId,
    vpscoreissCaptCalHndlObj_t     *pHndlObj,
    const vcoreissCaptOpenParams_t *pOpenParams,
    vcoreissCaptOpenRetParams_t    *pOpenRtnPrms);

/** \brief Function to open all required HALs
 *
 *  \param calId        CAL Id
 *  \param pInstObj     Pointer to handle
 *
 *  \return            FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptOpenHals(Irm_Modules_t                    calId,
                                 const vpscoreissCaptCalHndlObj_t *pHndlObj);

/** \brief Function to close all required HALs
 *
 *  \param pInstObj     Pointer to instance object
 *
 *  \return            FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptCloseHals(const vpscoreissCaptCalHndlObj_t *pHndlObj);

/** \brief Function to check if the config supplied is alright.
 *
 *  \param pHndl        Pointer to handle object
 *  \param pInstObj     Pointer to CAL configuration.
 *
 *  \return            FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptCheckCalCfg(const vpscoreissCaptCalHndlObj_t *pHndl,
                                    const isshalCalCfg_t             *pCalCfg);

/** \brief Function to prepare cal core config
 *
 *  \param pHndl        Pointer to handle object
 *  \param pInstObj     Pointer to CAL configuration.
 *
 *  \return            FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptMakeCalCoreCfg(vpscoreissCaptCalHndlObj_t *pHndl,
                                       isshalCalCfg_t             *pCalCfg);

/** \brief Function to associate allocated instances
 *
 *  \param pHndl        Pointer to handle object
 *  \param pInstObj     Pointer to CAL configuration.
 *
 *  \return            FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptDetermineInst(const vpscoreissCaptCalHndlObj_t *pHndl,
                                      isshalCalCfg_t                   *pCalCfg);

/** \brief Function to initialize the defaults
 *
 *  \param pCalCfg     Pointer to CAL config
 *  \param pCalCoreCfg Pointer to CAL core config / derived config
 *
 *  \return            FVID2_SOK on success, appropriate error code otherwise.
 */
static void vcoreCaptSetDefaultParams(isshalCalCfg_t      *pCalCfg,
                                      isshalCalDmaVcCfg_t *pCalCoreCfg);

/** \brief Allocates a handle object from pool of handle objects.
 *
 *  \param pInstObj Pointer to instance Object, used to identify CAL instance
 *
 *  \return         FVID2_SOK on success, appropriate error code otherwise.
 */
static vpscoreissCaptCalHndlObj_t *vcoreCaptAllocHndlObj(
    vpscoreissCaptInstObj_t *pInstObj);

/** \brief Registers interrupt handler for DMA writes and ISP writes
 *
 *  \param pInstObj Pointer to handle object, with valid IRQ no, and others
 *
 *  \return         FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptRegisterIsr(vpscoreissCaptCalHndlObj_t *pHndlObj);

/** \brief Validates open time configurations.
 *
 *  \param hObj     Pointer to handle object.
 *  \param openPrms Pointer to open parameters
 *
 *  \return         FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptCheckOpenParams(
    const vpscoreissCaptInstObj_t  *pInstObj,
    const vcoreissCaptOpenParams_t *pOpenParams);

/**  \brief Checks if the specified CSI2 data formats is YUV420 variant
 *  This will be used to increase the line count in CAL configuration
 */
static inline int32_t vcoreCaptCsi2IsDataYuv420(UInt32 dataFmt);

/**
 *  \brief Checks if the specified CSI2 data formats is pixel data
 */
static inline int32_t vcoreCaptCsi2IsPixData(UInt32 dataFmt);

/**
 *  \brief Checks and applies the given config. Essentially converts the config
 *          specified via vpsissCalCfg_t to config based on isshalCalCfg_t
 */
static int32_t vcoreIssSetCalConfig(vpscoreissCaptCalHndlObj_t *pHndlObj,
                                    const vpsissCalCfg_t       *pCfg);

/**
 *  \brief Primes CAL module with 1 buffer and starts CAL based reception.
 */
static int32_t vcoreIssPrimeStartCal(vpscoreissCaptCalHndlObj_t *pHndlObj,
                                     void                       *argsNotUsed);

/**  \brief Write DMA has started writing, called by event manager.
 *              This ISR would be called only in case CAL is writing to memory.
 *
 *  \param event       Arrays of events which occurred
 *  \param numEvents   number of valid entries in event
 *  \param arg         Not used
 *
 */
static void vcoreCaptErrCb(const UInt32 *event,
                           UInt32        numEvents,
                           Ptr           arg);
/** \brief Registers error interrupt handler
 *
 *  \param pInstObj Pointer to handle object
 *
 *  \return         FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptRegisterErrorIsr(const vpscoreissCaptCalHndlObj_t
                                                                   *pHndlObj,
                                         const vpsissCalErrorCfg_t *pErrCfg);

/** \brief Configure sub-frame parameters and End of frame notification.
 *
 *  \param pInstObj Pointer to handle object
 *
 *  \return         FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptCfgSubEof(
                                vpscoreissCaptCalHndlObj_t *pHndlObj,
                                const vcoreissCaptSubFrameCfg_t *pSubFrmCfg);

/** \brief Registers end of frame and x line interrupt handler
 *
 *  \param pInstObj Pointer to handle object
 *
 *  \return         FVID2_SOK on success, appropriate error code otherwise.
 */
static int32_t vcoreCaptRegisterSubEofIsr(
                                vpscoreissCaptCalHndlObj_t *pHndlObj,
                                const vcoreissCaptSubFrameCfg_t *pSubFrmCfg);
#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Core handles */
static vpscoreissCaptCalHndlObj_t
    gCaptHndlObjs[VPS_ISS_CAPT_INST_MAX_ID][VCORE_ISS_CAPT_MAX_OPEN];

/** \brief Capture Instance object */
static vpscoreissCaptInstObj_t gCaptInstObjs[VPS_ISS_CAPT_INST_MAX_ID] =
{
    {(uint32_t) FALSE, /* We really require to set this to FALSE. */
     VPS_ISS_CAPT_INST_MAX_ID},
    {(uint32_t) FALSE, /* We really require to set this to FALSE. */
     VPS_ISS_CAPT_INST_MAX_ID},
    {(uint32_t) FALSE, /* We really require to set this to FALSE. */
     VPS_ISS_CAPT_INST_MAX_ID},
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/** Initializes the data structures as per the init parameters,
 *  Also initializes the hal as per the driver instance
 */
int32_t VpsCore_issCaptInit(
    uint32_t                        numInst,
    const vcoreissCaptInitParams_t *initParams,
    Ptr                             arg)
{
    vpscoreissCaptInstObj_t          *pInstObj;
    const VpsLib_PlatformData        *platData;
    const vpshalissCalPlatformData_t *pCalPlatData;
    isshalCalInstParams_t            *pCalInstParams;
    int32_t          rtnVal = FVID2_SOK;
    UInt32           inst, i;
    Irm_InitParams_t irmInitParams;

    platData = NULL;

    /* Args check */
    if((NULL == initParams) || (VPS_ISS_CAPT_INST_MAX_ID < numInst))
    {
        rtnVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == rtnVal)
    {
        for(inst = 0x0U; inst < numInst; inst++)
        {
            pInstObj = NULL;

            /* Args check */
            if((FVID2_SOK == rtnVal) && (NULL == initParams->halPlatformData))
            {
                rtnVal = FVID2_EBADARGS;
            }

            if((FVID2_SOK == rtnVal) &&
               (initParams->instId >= VPS_ISS_CAPT_INST_MAX_ID))
            {
                rtnVal = FVID2_EBADARGS;
            }

            if(FVID2_SOK == rtnVal)
            {
                pInstObj = &gCaptInstObjs[initParams->instId];
                if(TRUE == pInstObj->isInited)
                {
                    /* already initialized */
                    pInstObj = NULL;
                }
                else
                {
                    BspUtils_memset((Ptr)&gCaptInstObjs[initParams->instId], 0x0,
                                    sizeof(vpscoreissCaptInstObj_t));
                    gCaptInstObjs[initParams->instId].instId = initParams->instId;
                }
            }

            if((FVID2_SOK == rtnVal) && (NULL != pInstObj))
            {
                platData = initParams->halPlatformData;
                GT_assert(VpsIssCalCoreTrace, (NULL != platData));

    /* MISRA.CAST.PTR_TO_INT
     * Rule 11.4: Cast between a pointer to object type and a different pointer to
     * object type
     * Name 'pCalPlatData'
     * KW State: Not A Problem -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Pointers to different layer's handles are stored as void*.
     */
                pCalPlatData = ((const vpshalissCalPlatformData_t *)
                                platData->calHal);
                GT_assert(VpsIssCalCoreTrace, (NULL != pCalPlatData));
                GT_assert(VpsIssCalCoreTrace, (NULL != pCalPlatData->calInstPrms));

                pCalInstParams = pCalPlatData->calInstPrms;
                GT_assert(VpsIssCalCoreTrace, (NULL != pCalInstParams));
                pInstObj->instId = initParams->instId;

                /* For each instance,
                 *  . initialize isscontrol
                 *  . cal hal
                 *  . copy the initparams
                 *  . create instance lock */
                irmInitParams.numCalBlocks = pCalPlatData->numCalInst;
                irmInitParams.arg          = NULL;
                rtnVal = Irm_init(0x0, &irmInitParams);

                if(FVID2_SOK == rtnVal)
                {
                    rtnVal = VpsHal_isscalInit(pCalPlatData->numCalInst,
                                               pCalInstParams, NULL);
                }

                if(FVID2_SOK == rtnVal)
                {
                    rtnVal = FVID2_EALLOC;
                    pInstObj->instLock = BspOsal_semCreate(1, TRUE);
                    if(NULL != pInstObj->instLock)
                    {
                        BspUtils_memcpy((Ptr) (&pInstObj->initPrms),
                                        (const void *) (initParams),
                                        sizeof(vcoreissCaptInitParams_t));
                        BspUtils_memset((Ptr)&gCaptHndlObjs[inst][0U], 0x0,
                                        (sizeof(vpscoreissCaptCalHndlObj_t) *
                                         VCORE_ISS_CAPT_MAX_OPEN));
    /* C & C++ INVARIANT_CONDITION.GEN
     * Expression 'cnt < (1)' used in the condition always yields the same result.
     * Name 'VCORE_ISS_CAPT_MAX_OPEN'
     * KW State: Ignore -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * In this perticular case, core can be opned only once. When multiple open is
     *  supported (other i/f support, logical handles, etc...) this is required.
     *  By having this check, no unintended operation is caused.
     */
                        for(i = 0U; i < VCORE_ISS_CAPT_MAX_OPEN; i++)
                        {
                            gCaptHndlObjs[inst][i].pInstObj = pInstObj;
                        }
                        pInstObj->isInited = (uint32_t)TRUE;
                        rtnVal = FVID2_SOK;
                    }
                }
            }

    /* MISRA.PTR.ARITH
     * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
     * Name 'initParams'
     * KW State: Ignore -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Pointer arithmetic is required for performance like auto increment in loop.
     * The harmful side effect of violating this rule (accessing outside valid
     *  memory) shall be checked by another code checker like klockwork
     */
            initParams++;
        }

    }
    return (rtnVal);
}

/* Function to de-initialize all instances, it also de-initializes the hals */
int32_t VpsCore_issCaptDeInit(Ptr arg)
{
    int32_t rtnVal = FVID2_SOK;
    vpscoreissCaptInstObj_t     *pInstObj;
    UInt32  i;

    for(i = 0U; i < VPS_ISS_CAPT_INST_MAX_ID; i++)
    {
        pInstObj = &gCaptInstObjs[i];
        if(TRUE == pInstObj->isInited)
        {
            rtnVal = VpsHal_isscalDeInit(NULL);
            GT_assert(VpsIssCalCoreTrace, (FVID2_SOK == rtnVal));

            BspOsal_semDelete(&pInstObj->instLock);
        }
    }
/* C & C++ INVARIANT_CONDITION.GEN
 * Expression 'rtnVal == (0)' used in the condition always yields the same
 * result.
 * Name 'rtnVal'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable.
 */
    if(FVID2_SOK == rtnVal)
    {
        Irm_deInit();
    }

    return (rtnVal);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/** API to return the property of the instance
 */
Int32 vcoreCaptGetProperty(VpsCore_Inst      instObj,
                           VpsCore_Property *property)
{
    Int32 retVal = BSP_EFAIL;
    if(NULL != property)
    {
        property->name = VPSCORE_CAPT_ISS;
        property->isDropDataSupport = FALSE;
        retVal = BSP_SOK;
    }
    return (retVal);
}

/** Returns the core operations
 */
const VpsCore_Ops *VpsCore_issCaptGetCoreOps(void)
{
    /** \brief Capture core function pointers. */
    static const VpsCore_Ops gCaptureCoreOps = {       \
        &vcoreCaptGetProperty,  /* Get property */     \
        &vcoreCaptOpen,         /* Open function */    \
        &vcoreCaptClose,        /* Close function */   \
        &vcoreCaptSetParams,    /* Set Params */       \
        NULL,                   /* Get Params */       \
        &vcoreCaptControl,      /* Control */          \
        &vcoreCaptStart,        /* Start Required */   \
        &vcoreCaptStop,         /* Stop Required */    \
        NULL,                   /* Process */          \
        &vcoreCaptProgBuf,      /* Core prog Buffer */ \
        NULL,                   /* putFrames */        \
        NULL,                   /* getFrames */        \
        NULL                    /* getErrorStat */     \
    };

    return (&gCaptureCoreOps);
}

/**
 *  A Valid pointer on success else a NULL pointer.
 */
VpsCore_Inst VpsCore_issCaptGetCoreInstObj(vpsissCaptInstId_t inst)
{
    VpsCore_Inst rtnVal = NULL;
    if(inst < VPS_ISS_CAPT_INST_MAX_ID)
    {
        rtnVal = (VpsCore_Inst)&gCaptInstObjs[inst];
    }
    return (rtnVal);
}

/* MISRA.PPARAM.NEEDS.CONST
 * MISRAC_2004_Rule_16.7
 * Function parameter 'coreOpenPrms' is not declared as a pointer to const
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Klocwork is not able to analyse pointers which are declared as const and
 *  reporting this issue.This is a false positive.
 */

/** \brief Typedef for core open function pointer. */
VpsCore_Handle vcoreCaptOpen(VpsCore_Inst            inst,
                             const VpsCore_OpenPrms *openPrms,
                             const void             *coreOpenPrms,
                             void                   *coreReturnPrms)
{
    const vcoreissCaptOpenParams_t *pOpenParams;
    vpscoreissCaptInstObj_t        *pInstObj;
    vpscoreissCaptCalHndlObj_t     *pHndlObj;
    Int32         rtnVal;
    UInt32        i;
    uint32_t      stepStatus;
    Irm_Modules_t calId;

    /*  Steps
     *  . Args check
     *  . Config check
     *  . Acquire Instance lock
     *  . alloc Handle Object
     *  . alloc resource
     *  . open hals
     *  . Set Defaults
     *  . Register with event manager, for the frame start interrupt of
     *      DMA write.
     *  . set instance config, enable PPI & complex IO
     *  . Set Vmux settings for LVDS Rx Capture
     *  . Update status if all steps are successful.
     */

    /* Init */
    pHndlObj   = NULL;
    rtnVal     = FVID2_EBADARGS;
    stepStatus = 0x0U;

    /* .Args Check */
    if(NULL != inst)
    {
        rtnVal   = FVID2_SOK;
        pInstObj = (vpscoreissCaptInstObj_t *) inst;
        GT_assert(VpsIssCalCoreTrace, (NULL != pInstObj));

/* C & C++ INVARIANT_CONDITION.GEN
 * Expression '0 == (pInstObj)' used in the condition always yields the same
 * result.
 * Name 'pInstObj'
 * KW State: Ignore -> Waiver -> Case by case
 * WAIVER:
 * In this perticular case, if an wrong inst is provided by the caller, the
 * pInstObj could be NULL and hence this check is required.
 */
        if(((NULL == openPrms) || (NULL == coreOpenPrms)) ||
           ((NULL == coreReturnPrms) || (NULL == pInstObj)))
        {
            rtnVal = FVID2_EBADARGS;
        }

        /* .Config checks */
        if(FVID2_SOK == rtnVal)
        {
            if(FALSE == pInstObj->isInited)
            {
                rtnVal = FVID2_EUNSUPPORTED_OPS;
            }
            else if(TRUE == pInstObj->isStarted)
            {
                /* Should be the second check */
                rtnVal = FVID2_EDEVICE_INUSE;
            }
            else if(VCORE_ISS_CAPT_MAX_OPEN <= pInstObj->numOpens)
            {
                rtnVal = FVID2_EALLOC;
            }
            else
            {
/* MISRA.CAST.CONST
 * MISRAC_2004_Rule_11.8
 * Name 'pOpenParams'
 * Cast operation removes const or volatile modifier from a pointer or reference
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  KW is reporting this issue for the above case which is not an issue.
 */
                pOpenParams = (const vcoreissCaptOpenParams_t *) coreOpenPrms;
                rtnVal      = vcoreCaptCheckOpenParams(pInstObj, pOpenParams);
            }
        }

        BspOsal_semWait(pInstObj->instLock, BSP_OSAL_WAIT_FOREVER);

        /* . Alloc handle Object */
        if((FVID2_SOK == rtnVal) &&
           (VPS_ISS_CAPT_INST_MAX_ID > pInstObj->instId))
        {
            pHndlObj = vcoreCaptAllocHndlObj(pInstObj);

            if(NULL != pHndlObj)
            {
                stepStatus |= 0x1U;
            }
            else
            {
                rtnVal = FVID2_EALLOC;
            }
        }
        else
        {
            if((FVID2_SOK == rtnVal) &&
               (VPS_ISS_CAPT_INST_MAX_ID <= pInstObj->instId))
            {
                rtnVal = FVID2_EBADARGS;
            }
        }

        /* . Alloc resources */
        if(FVID2_SOK == rtnVal)
        {
            /* Event group is DMA Write start CAL A */
            calId = IRM_MODULE_CAL_A;

            rtnVal = vcoreCaptAllocCalRes(
                calId,
                pHndlObj,
                pOpenParams,
                (vcoreissCaptOpenRetParams_t *) coreReturnPrms);

            if(FVID2_SOK == rtnVal)
            {
                stepStatus |= 0x2U;

                BspUtils_memcpy((Ptr) (&pHndlObj->openPrms),
                                (const void *) (openPrms),
                                sizeof(VpsCore_OpenPrms));
                BspUtils_memcpy((Ptr) (&pHndlObj->coreOpenPrms),
                                (const void *) (pOpenParams),
                                sizeof(vcoreissCaptOpenParams_t));
            }
            else
            {
                rtnVal = FVID2_EALLOC;
            }
        }

        /* . Open Required HALs */
        if((FVID2_SOK == rtnVal) && (0x0 == pInstObj->numOpens))
        {
            rtnVal = vcoreCaptOpenHals(calId, pHndlObj);
            if(FVID2_SOK == rtnVal)
            {
                stepStatus |= 0x4U;
            }
        }

        /* Set Defaults */
        if(FVID2_SOK == rtnVal)
        {
            if(0x0 == pInstObj->numOpens)
            {
                vcoreCaptSetDefaultParams(&pInstObj->calCfg,
                                          &pHndlObj->calDmaVcCfg);
            }
            else
            {
                vcoreCaptSetDefaultParams(NULL, &pHndlObj->calDmaVcCfg);
            }
        }

        /* . Register Event Handle */
        if(FVID2_SOK == rtnVal)
        {
            rtnVal = vcoreCaptRegisterIsr(pHndlObj);

            if(FVID2_SOK == rtnVal)
            {
                stepStatus |= 0x8U;
            }
        }

        /* . Configure Phy/Complex IO */
        if(FVID2_SOK == rtnVal)
        {
            /* Except for the LVDS parallel interface,
               Phy configuration is required for all instance */
            if(VPS_ISS_CAPT_CAL_A_CPI != pInstObj->instId)
            {
                /* Check if opening for the first time, if so set
                 * the instance cfg
                 * HAL TODO. Ensure to not update m2m instance config */
                if (0x0 == pInstObj->numOpens)
                {
                    rtnVal = VpsHal_isscalControl(
                        pInstObj->calHalHandle,
                        VPS_HAL_ISS_IOCTL_CAL_GET_INSTANCECFG,
                        (Ptr) & pInstObj->instCfg, NULL);

                    for (i = 0; ((i < VPS_ISS_CAL_MAX_CMPLXIO_INST) &&
                                 (FVID2_SOK == rtnVal)); i++)
                    {
                        pInstObj->instCfg.ppiCfg[i].enable = (uint32_t)FALSE;

                        if(TRUE == pOpenParams->isCmplxIoCfgValid[i])
                        {
                            pInstObj->instCfg.ppiCfg[i].enable = (uint32_t)TRUE;
                            pInstObj->instCfg.ppiCfg[i].instance = i;
                            /* Complex IO configuration is done in the HAL */
                            BspUtils_memcpy(
                                (Ptr) (&pInstObj->instCfg.cmplxIoCfg[i]),
                                (const void *) (&pOpenParams->cmplxIoCfg[i]),
                                (sizeof(vpsissCalCmplxIoCfg_t)));
                        }
                        else
                        {
                            pInstObj->instCfg.cmplxIoCfg[i].enable =
                                                                (uint32_t)FALSE;
                        }
                        if(pInstObj->instCfg.csi2PhyClock[i] !=
                                                pOpenParams->csi2PhyClock[i])
                        {
                            pInstObj->instCfg.csi2PhyClock[i] =
                                                pOpenParams->csi2PhyClock[i];
                        }
                    }

                    if (FVID2_SOK == rtnVal)
                    {
                        rtnVal = VpsHal_isscalControl(
                                        pInstObj->calHalHandle,
                                        VPS_HAL_ISS_IOCTL_CAL_SET_INSTANCECFG,
                                        (Ptr) & pInstObj->instCfg, NULL);
                    }
                }
            }
        }

        if(FVID2_SOK == rtnVal)
        {
            vcoreissCaptOpenRetParams_t *rtnPrms =
                (vcoreissCaptOpenRetParams_t *) coreReturnPrms;
            /* We have indeed opened for reception */
            pInstObj->numOpens++;

            /* Let the apps / driver know about allocated resources */
            rtnPrms->numStreamsAlloc = pOpenParams->numStreams;
            for(i = 0; i < pOpenParams->numStreams; i++)
            {
                pHndlObj->curr[i]          = 0U;
                pHndlObj->next[i]          = 1U;
                pHndlObj->currBufs[i][0x0] = NULL;
                pHndlObj->currBufs[i][0x1] = NULL;

                Fvid2SubFrameInfo_init(&pHndlObj->currSubFrame[i][0x0]);
                Fvid2SubFrameInfo_init(&pHndlObj->currSubFrame[i][0x1]);

                rtnPrms->cportIdAlloc[i]   = pHndlObj->allocatedRes[i].cport;
                if((VCORE_CAL_STREAM_MODE_CAL_WRITE ==
                    pHndlObj->streamMode[i]) ||
                   (VCORE_CAL_STREAM_MODE_ISP == pHndlObj->streamMode[i]))
                {
                    rtnPrms->isStreamOpt[i] = (uint32_t)FALSE;
                }
                else
                {
                    rtnPrms->isStreamOpt[i] = (uint32_t)TRUE;
                }
            }

            pHndlObj->isSubFrameCfgValid = FALSE;
        }
        else
        {
            /* One of the Step is failed, so undo the changes and return
             * null handle */
            if(0x8U == (stepStatus & 0x8U))
            {
                for(i = 0; i < pOpenParams->numStreams; i++)
                {
                    if(0U != (pOpenParams->subModules[i] &
                              VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID))
                    {
                        if(NULL != pHndlObj->emDmaStartHndl[i])
                        {
                            Vps_calEmUnRegister(pHndlObj->emDmaStartHndl[i]);
                        }
                        if(NULL != pHndlObj->emDmaCmpltHndl[i])
                        {
                            Vps_calEmUnRegister(pHndlObj->emDmaCmpltHndl[i]);
                        }
                    }
                }
            }

            if(0x4U == (stepStatus & 0x4U))
            {
                vcoreCaptCloseHals(pHndlObj);
            }

            if(0x2U == (stepStatus & 0x2U))
            {
                vcoreCaptDeAllocCalRes(
                    calId,
                    pHndlObj->allocatedRes,
                    pHndlObj->numStreams);
            }

            if(0x1U == (stepStatus & 0x1U))
            {
                pHndlObj->isAllocated = (uint32_t)FALSE;
                pHndlObj = NULL;
            }
        }

        BspOsal_semPost(pInstObj->instLock);
    }

    return ((VpsCore_Handle) pHndlObj);
}

int32_t vcoreCaptClose(VpsCore_Handle handle)
{
    vpscoreissCaptInstObj_t    *pInstObj;
    vpscoreissCaptCalHndlObj_t *pHndlObj;
    vpscoreissCaptErrObj_t     *pErrObj;
    Irm_Modules_t calId;
    int32_t       rtnVal = FVID2_EBADARGS;
    uint32_t      strmId, cmplxIoId;
    /*  Steps
     *  . Args check
     *  . Acquire Instance lock
     *  . DeAlloc resources
     *      . Close HALs - relying on HAL to ensure stop has been called.
     *      . DeRegister with event manager
     *  . If its the last close, power down - done by closeHals
     */

    /* .Args Check */
    pHndlObj = (vpscoreissCaptCalHndlObj_t *) handle;
    if(NULL != pHndlObj)
    {
        rtnVal   = FVID2_SOK;
        pInstObj = pHndlObj->pInstObj;
        if(NULL != pInstObj)
        {
            if(TRUE == pInstObj->isStarted)
            {
                rtnVal = FVID2_EDEVICE_INUSE;
            }
            else if(0x0 != pInstObj->numOpens)
            {
                BspOsal_semWait(pInstObj->instLock, BSP_OSAL_WAIT_FOREVER);
            }
            else
            {
                /* Otherwise we can close it */
                rtnVal = FVID2_EBADARGS;
            }
        }
        else
        {
            rtnVal = FVID2_EBADARGS;
        }
    }

    if(FVID2_SOK == rtnVal)
    {
        if(FVID2_SOK == rtnVal)
        {
            /* Capture only through CAL A */
            calId  = IRM_MODULE_CAL_A;
            rtnVal = vcoreCaptDeAllocCalRes(
                calId,
                pHndlObj->allocatedRes,
                pHndlObj->numStreams);
        }

        if(FVID2_SOK == rtnVal)
        {
            for(strmId = 0; strmId < pHndlObj->numStreams; strmId++)
            {
                if(VCORE_CAL_STREAM_MODE_CAL_WRITE ==
                   pHndlObj->streamMode[strmId])
                {
                    if(NULL != pHndlObj->emDmaStartHndl[strmId])
                    {
                        rtnVal = Vps_calEmUnRegister(
                            pHndlObj->emDmaStartHndl[strmId]);
                        GT_assert(VpsIssCalCoreTrace, (FVID2_SOK == rtnVal));
                    }

                    if(NULL != pHndlObj->emDmaCmpltHndl[strmId])
                    {
                        rtnVal = Vps_calEmUnRegister(
                            pHndlObj->emDmaCmpltHndl[strmId]);
                        GT_assert(VpsIssCalCoreTrace, (FVID2_SOK == rtnVal));
                    }

                    if (NULL != pHndlObj->emSubFrmCmpltHndl)
                    {
                        rtnVal = Vps_calEmUnRegister(pHndlObj->emSubFrmCmpltHndl);
                        GT_assert(VpsIssCalCoreTrace, (FVID2_SOK == rtnVal));
                        pHndlObj->emSubFrmCmpltHndl = NULL;
                    }
                }
            }
        }

        if((FVID2_SOK == rtnVal) && (1U == pInstObj->numOpens))
        {
            for(strmId = 0U; strmId < VPS_ISS_CAL_MAX_STREAMS; strmId++)
            {
                pInstObj->streamIdToVcMap[strmId] = 0U;
                pInstObj->streamIdToPpiMap[strmId] = 0U;
            }

            for (cmplxIoId = 0; cmplxIoId < VPS_ISS_CAL_MAX_CMPLXIO_INST; cmplxIoId ++)
            {
                pErrObj = &pInstObj->errObj[cmplxIoId];

                for(strmId = 0U; strmId <= CAL_MAX_VIRTUAL_CHAN; strmId++)
                {
                    pErrObj->fifoOverFlow[strmId]       = 0U;
                    pErrObj->eccCouldNotCorrect[strmId] = 0U;
                    pErrObj->crcMisMatch[strmId]        = 0U;
                    pErrObj->eccCorrected[strmId]       = 0U;
                }

                if (NULL != pErrObj->emErrorHndl)
                {
                    rtnVal = Vps_calEmUnRegister(
                        pErrObj->emErrorHndl);
                    if(rtnVal == FVID2_SOK)
                    {
                        pErrObj->emErrorHndl = NULL;
                    }
                }
            }
        }

        if(FVID2_SOK == rtnVal)
        {
            rtnVal = vcoreCaptCloseHals(pHndlObj);
        }

        if(FVID2_SOK == rtnVal)
        {
            pInstObj->numOpens--;
            pHndlObj->isAllocated = (uint32_t)FALSE;
        }
        BspOsal_semPost(pInstObj->instLock);
    }

    return (rtnVal);
}

/* Function to set the Params,
 * Sets the initial fixed parameters like path selection,
 * frame size, frame format etc */
/* MISRA.PPARAM.NEEDS.CONST
 * MISRAC_2004_Rule_16.7
 * Function parameter 'params' is not declared as a pointer to const
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Klocwork is not able to analyze pointers which are declared as const and
 *  reporting this issue.This is a false positive.
 */

int32_t vcoreCaptSetParams(VpsCore_Handle handle,
                           const void    *params,
                           void          *argsNotUsed)
{
    vpscoreissCaptCalHndlObj_t *pHndlObj;
    vpscoreissCaptInstObj_t    *pInstObj;
    int32_t rtnVal = FVID2_EBADARGS, i;

/* MISRA.CAST.CONST
 * MISRAC_2004_Rule_11.8
 * Name 'pCalCfg'
 * Cast operation removes const or volatile modifier from a pointer or reference
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  KW is reporting this issue for the above case which is not an issue.
 */
    const isshalCalCfg_t       *pCalCfg = (const isshalCalCfg_t *) params;
    /*  . Validate the config
     *  . Compute / update the HAL specifics
     *  . Apply the config
     */

    pHndlObj = (vpscoreissCaptCalHndlObj_t *) handle;

    if((NULL != pCalCfg) && (NULL != pHndlObj))
    {
        pInstObj = pHndlObj->pInstObj;
        if(NULL != pInstObj)
        {
            rtnVal = FVID2_SOK;
            if(TRUE == pInstObj->isStarted)
            {
                rtnVal = FVID2_EDEVICE_INUSE;
                for(i = 0; i < pHndlObj->numStreams; i++)
                {
                    pHndlObj->firstDmaStartIntr[i] = (uint32_t)TRUE;
                }
            }
        }
    }

    if(FVID2_SOK == rtnVal)
    {
        rtnVal = vcoreCaptCheckCalCfg(pHndlObj, pCalCfg);
    }

    if(FVID2_SOK == rtnVal)
    {
        BspOsal_semWait(pInstObj->instLock, BSP_OSAL_WAIT_FOREVER);

        /* Compute the core config required */
/* MISRA.CAST.CONST
 * MISRAC_2004_Rule_11.8
 * Name 'pCalCfg'
 * Cast operation removes const or volatile modifier from a pointer or reference
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  This is required as instances are determined and updated in the config
 *  provided. As the caller will not know the DMA configurations, which will
 *  un-used variable in this structure. This function updates the structure with
 *  correct DMA configuration.
 *  This behaviour is documented in the structure i/f and will not result in
 *  un-desired operation.
 *
 */
        rtnVal = vcoreCaptMakeCalCoreCfg(pHndlObj,
                                         (isshalCalCfg_t *)pCalCfg);

        if(FVID2_SOK == rtnVal)
        {
/* MISRA.CAST.CONST
 * MISRAC_2004_Rule_11.8
 * Name 'pCalCfg'
 * Cast operation removes const or volatile modifier from a pointer or reference
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  This is required as instances are determined and updated in the config
 *  provided. As the caller will not know the PPI instance to be used.
 *  This behaviour is documented in the structure i/f and will not result in
 *  un-desired operation.
 */
            /* Get the instance ID of sub-blocks used/required. */
            rtnVal = vcoreCaptDetermineInst(pHndlObj,
                                            (isshalCalCfg_t *)pCalCfg);
        }

        if(FVID2_SOK == rtnVal)
        {
/* MISRA.CAST.CONST
 * MISRAC_2004_Rule_11.8
 * Name 'pCalCfg'
 * Cast operation removes const or volatile modifier from a pointer or reference
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  This is required as control API is general API that supports multiple
 *  commands. Some of the commands requires arguments to be modified. For this
 *  command, however no modifications of the arguments will be done.
 */
            /* Apply the config,
             *  Applying configuration after glbce start up sequence since
             *  glbce start up sequence code reset bysout/in configuration */
            rtnVal = VpsHal_isscalControl(
                pInstObj->calHalHandle,
                VPS_HAL_ISS_IOCTL_CAL_SETCFG,
                (Ptr) pCalCfg, NULL);
        }

        if(FVID2_SOK == rtnVal)
        {
            BspUtils_memcpy(&pInstObj->calCfg, pCalCfg, sizeof(isshalCalCfg_t));
        }

        BspOsal_semPost(pInstObj->instLock);
    }

    return (rtnVal);
}

int32_t vcoreCaptStart(VpsCore_Handle handle)
{
    int32_t  rtnVal = FVID2_EBADARGS;
    uint32_t cookie;
    vpscoreissCaptCalHndlObj_t *pHndlObj;
    vpscoreissCaptInstObj_t    *pInstObj;

    pHndlObj = (vpscoreissCaptCalHndlObj_t *) handle;

    if(NULL != pHndlObj)
    {
        pInstObj = pHndlObj->pInstObj;
        if(NULL != pInstObj)
        {
            rtnVal = FVID2_SOK;

            if(TRUE == pInstObj->isStarted)
            {
                rtnVal = FVID2_EDEVICE_INUSE;
            }
        }
    }
    if((FVID2_SOK == rtnVal) && (FALSE == pInstObj->isStarted))
    {
        BspOsal_semWait(pInstObj->instLock, BSP_OSAL_WAIT_FOREVER);

        rtnVal = vcoreIssPrimeStartCal(pHndlObj, NULL);

        if(FVID2_SOK == rtnVal)
        {
            cookie = BspOsal_disableInterrupt();
            pInstObj->isStarted = (uint32_t)TRUE;
            BspOsal_restoreInterrupt(cookie);
        }

        BspOsal_semPost(pInstObj->instLock);
    }

    return rtnVal;
}

int32_t vcoreCaptStop(VpsCore_Handle handle)
{
    int32_t  rtnVal = FVID2_EBADARGS;
    uint32_t cookie, i;
    vpscoreissCaptCalHndlObj_t *pHndlObj;
    vpscoreissCaptInstObj_t    *pInstObj;
    isshalCalDmaVcCfg_t        *pDmaVcCfg;

    pHndlObj = (vpscoreissCaptCalHndlObj_t *) handle;

    if(NULL != pHndlObj)
    {
        pInstObj = pHndlObj->pInstObj;
        if(NULL != pInstObj)
        {
            rtnVal = FVID2_SOK;
        }
    }

    if((FVID2_SOK == rtnVal) && (TRUE == pInstObj->isStarted))
    {
        cookie = BspOsal_disableInterrupt();
        if (NULL != pHndlObj->emSubFrmCmpltHndl)
        {
            rtnVal = Vps_calEmDisable(pHndlObj->emSubFrmCmpltHndl);
        }
        for(i = 0; i < pHndlObj->numStreams; i++)
        {
            if(NULL != pHndlObj->emDmaStartHndl[i])
            {
                rtnVal = Vps_calEmDisable(pHndlObj->emDmaStartHndl[i]);
            }

            if(NULL != pHndlObj->emDmaCmpltHndl[i])
            {
                rtnVal = Vps_calEmDisable(pHndlObj->emDmaCmpltHndl[i]);
            }
        }
        BspOsal_restoreInterrupt(cookie);
    }

    if((FVID2_SOK == rtnVal) && (TRUE == pInstObj->isStarted))
    {
        pDmaVcCfg = &pHndlObj->calDmaVcCfg;
        GT_assert(VpsIssCalCoreTrace, (NULL != pDmaVcCfg));
        BspOsal_semWait(pInstObj->instLock, BSP_OSAL_WAIT_FOREVER);

        rtnVal = FVID2_EBADARGS;
        for(i = 0; i < pHndlObj->numStreams; i++)
        {
            if(VCORE_CAL_STREAM_MODE_CAL_WRITE == pHndlObj->streamMode[i])
            {
                rtnVal = FVID2_SOK;
                pDmaVcCfg->wrDmaCfg[i].mode = VPS_HAL_ISS_CAL_DMA_WR_DISABLED;
            }
        }
        if(FVID2_SOK == rtnVal)
        {
            rtnVal = VpsHal_isscalCaptureStop(pInstObj->calHalHandle,
                                              pDmaVcCfg);
        }
        else
        {
            rtnVal = FVID2_SOK;
        }

        if(FVID2_SOK == rtnVal)
        {
            pInstObj->isStarted = (uint32_t)FALSE;
        }

        BspOsal_semPost(pInstObj->instLock);

#ifdef VPS_CAL_FLUSH_ON_STOP
        {
            uint32_t cookie, i, curr, next;
            volatile VpsCore_Frame *currBuf, *nextBuf;

            cookie = BspOsal_disableInterrupt();
            for(i = 0; i < pHndlObj->numStreams; i++)
            {
                pHndlObj->curr[i] = 0U;
                pHndlObj->next[i] = 1U;

                curr    = pHndlObj->curr[i];
                currBuf = pHndlObj->currBufs[i][curr];

                next    = pHndlObj->next[i];
                nextBuf = pHndlObj->currBufs[i][next];
                pHndlObj->currBufs[i][0x0] = NULL;
                pHndlObj->currBufs[i][0x1] = NULL;

                if((nextBuf != NULL) && (NULL != pHndlObj->openPrms.frmDoneCb))
                {
                    pHndlObj->openPrms.frmDoneCb(pHndlObj->openPrms.drvData,
                                                 (VpsCore_Frame *) nextBuf);
                }
                if((currBuf != NULL) && (NULL != pHndlObj->openPrms.frmDoneCb))
                {
                    pHndlObj->openPrms.frmDoneCb(pHndlObj->openPrms.drvData,
                                                 (VpsCore_Frame *) currBuf);
                }
            }
            BspOsal_restoreInterrupt(cookie);
        }
#endif  /* VPS_CAL_FLUSH_ON_STOP */
    }

    return rtnVal;
}

Int32 vcoreCaptProgBuf(VpsCore_Handle handle,
                       VpsCore_Frame *frame,
                       UInt32         bypassLowLatencyCheck)
{
    /* Condition before programming
     *  . Should not be running
     *  . Should not be called second time curr should be NULL*/
    int32_t rtnVal = FVID2_EBADARGS;
    vpscoreissCaptCalHndlObj_t  *pHndlObj;
    vpscoreissCaptInstObj_t     *pInstObj;
    isshalCalBufferAddr_t       *pBuf;
    UInt32  strmId;

    pHndlObj = (vpscoreissCaptCalHndlObj_t *) handle;

    if((NULL != pHndlObj) && (NULL != frame))
    {
        pInstObj = pHndlObj->pInstObj;
        if(NULL != pInstObj)
        {
            strmId = frame->streamId;
            if(strmId < VPS_ISS_CAL_MAX_STREAMS)
            {
                rtnVal = FVID2_SOK;
            }
        }
    }

    if((FVID2_SOK == rtnVal) && (TRUE != pInstObj->isStarted))
    {
        if(VCORE_CAL_STREAM_MODE_CAL_WRITE ==
           pHndlObj->streamMode[strmId])
        {
#ifdef VPS_CAL_SEPERATE_API_FOR_PRIME
            BspOsal_semWait(pInstObj->instLock, BSP_OSAL_WAIT_FOREVER);
#endif      /* VPS_CAL_SEPERATE_API_FOR_PRIME */

            if(NULL == pHndlObj->currBufs[frame->streamId]
               [pHndlObj->curr[frame->streamId]])
            {
                pBuf = &pHndlObj->bufCfg;
                pBuf->numBuff      = 0x1U;
                pBuf->cPortId[0U]  = pHndlObj->allocatedRes[strmId].cport;
                pBuf->wrDmaCtx[0U] = pHndlObj->allocatedRes[strmId].wrDma;
/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * Name 'buffAddr[0U] = (UInt32) newFrame->addr[0U][0U]'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Memory mapped registers and other hardware features access requires
 * typecasting of pointer to integer.  The address space is 32 bit and type
 * casting to integer will not result into any loss because of TI's compiler
 * treatment to integer.
 */
                pBuf->buffAddr[0U] = (UInt32) frame->addr[0U][0U];
                pBuf->pitch[0U]    =
                    pHndlObj->calDmaVcCfg.wrDmaCfg[strmId].format.pitch[0U];

                rtnVal = VpsHal_isscalUpdateBufAddr(pInstObj->calHalHandle,
                                                    pBuf);
                if(FVID2_SOK == rtnVal)
                {
                    pHndlObj->currBufs[frame->streamId]
                    [pHndlObj->curr[frame->streamId]] = frame;
                }
                else
                {
                    GT_assert(VpsIssCalCoreTrace, (FVID2_SOK == rtnVal));
                }
            }
            else
            {
                rtnVal = FVID2_EBADARGS;
            }

#ifdef VPS_CAL_SEPERATE_API_FOR_PRIME
            BspOsal_semPost(pInstObj->instLock);
#endif      /* VPS_CAL_SEPERATE_API_FOR_PRIME */
        }
        else
        {
            rtnVal = FVID2_EBADARGS;
        }
    }
    return rtnVal;
}

/* Get current parameters, copies it from local object */
int32_t vcoreCaptGetParams(VpsCore_Handle handle,
                           void          *params)
{
    int32_t status = FVID2_SOK;
    /* TODO Do we really required this? */
    return (status);
}

/* MISRA.PPARAM.NEEDS.CONST
 * MISRAC_2004_Rule_16.7
 * Function parameter 'appArgs' is not declared as a pointer to const
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  This is general control API, where in arguments might need modification.
 */

/* Function to process control commands */
int32_t vcoreCaptControl(VpsCore_Handle handle,
                         UInt32         cmd,
                         void          *appArgs,
                         void          *drvArgs)
{
    int32_t retVal = FVID2_EBADARGS;
    vpscoreissCaptCalHndlObj_t *pHndlObj;
    vpscoreissCaptInstObj_t    *pInstObj;

    pHndlObj = (vpscoreissCaptCalHndlObj_t *) handle;

    if(NULL != pHndlObj)
    {
        pInstObj = pHndlObj->pInstObj;
        if(NULL != pInstObj)
        {
            retVal = FVID2_SOK;
        }
    }

    if(FVID2_SOK == retVal)
    {
        switch(cmd)
        {
            case VCORE_ISS_CAPT_CAL_SET_PARAMS:
                if(NULL != appArgs)
                {
                    /* No need to check if CAL is started or config is valid
                        or instance lock
                        The functions within below function will do so.
                        Rely on it */
                    retVal = vcoreIssSetCalConfig(
                        pHndlObj,
                        (const vpsissCalCfg_t *)
                        appArgs);
                }
                else
                {
                    retVal = FVID2_EBADARGS;
                }
                break;

            case VCORE_ISS_CAPT_CAL_SET_ERR_PRMS:
                if(NULL != appArgs)
                {
                    retVal = vcoreCaptRegisterErrorIsr(
                        pHndlObj,
                        (const
                         vpsissCalErrorCfg_t *)
                        appArgs);
                }
                else
                {
                    retVal = FVID2_EBADARGS;
                }
                break;

            case VCORE_ISS_CAPT_CAL_SET_SUB_FRM_PRMS:
                if(NULL != appArgs)
                {
                    retVal = vcoreCaptCfgSubEof(pHndlObj,
                        (const vcoreissCaptSubFrameCfg_t *) appArgs);
                }
                else
                {
                    retVal = FVID2_EBADARGS;
                }
                break;

            default:
                retVal = FVID2_EBADARGS;
                break;
        }
    }

    return (retVal);
}

static void vcoreCaptDmaStartCb(const UInt32 *event,
                                UInt32        numEvents,
                                Ptr           arg)
{
    UInt32         i, eventNo, streamId, cookie;
    int32_t        rtnVal;
    VpsCore_Frame *newFrame;
    vpscoreissCaptInstObj_t    *pInstObj;
    vpscoreissCaptCalHndlObj_t *pHndlObj;

    rtnVal   = FVID2_EBADARGS;
    pHndlObj = (vpscoreissCaptCalHndlObj_t *) arg;

    if((NULL != pHndlObj) && (NULL != event))
    {
        pInstObj = pHndlObj->pInstObj;
        if(NULL != pInstObj)
        {
            rtnVal = FVID2_SOK;
        }
    }

    if(FVID2_SOK == rtnVal)
    {
        for(i = 0U; i < numEvents; i++)
        {
/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'event'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 */
            eventNo = event[i];

            /* Translate event number to stream ID */
            if((CAL_EM_EVENT_WDMA_START0 <= eventNo) &&
               (eventNo <= CAL_EM_EVENT_WDMA_START7))
            {
                eventNo -= CAL_EM_EVENT_WDMA_START0;
                streamId = pHndlObj->eventToStreamIdMap[eventNo];
            }
            else
            {
                rtnVal   = FVID2_EBADARGS;
                streamId = 0U;
            }

            if((streamId < VPS_ISS_CAL_MAX_STREAMS) && (FVID2_SOK == rtnVal))
            {
                if(VCORE_CAL_STREAM_MODE_CAL_WRITE !=
                   pHndlObj->streamMode[streamId])
                {
                    /* If CAL is not writing, we do not expect start of frame
                        interrupt at all */
                    GT_assert(VpsIssCalCoreTrace, FALSE);
                }
            }
            else
            {
                rtnVal = FVID2_EBADARGS;
            }

            if (FVID2_SOK == rtnVal)
            {
                if((FALSE == pHndlObj->firstDmaStartIntr[streamId]) &&
                   (NULL != pHndlObj->openPrms.frmDoneCb))
                {
                    rtnVal = vcoreCaptFrameDoneProc(pHndlObj, streamId);
                }
            }

            if((NULL != pHndlObj->openPrms.reqFrmCb) &&
               (FVID2_SOK == rtnVal))
            {
                newFrame = pHndlObj->openPrms.reqFrmCb(
                    pHndlObj->openPrms.drvData,
                    streamId, 0x0);
                if(NULL != newFrame)
                {
                    /* Program the frame for reception */
                    pHndlObj->bufCfg.numBuff     = 0x1U;
                    pHndlObj->bufCfg.cPortId[0U] =
                        pHndlObj->allocatedRes[streamId].cport;
                    pHndlObj->bufCfg.wrDmaCtx[0U] =
                        pHndlObj->allocatedRes[streamId].wrDma;
/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * Name 'buffAddr[0U] = (UInt32) newFrame->addr[0U][0U]'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Memory mapped registers and other hardware features access requires
 * typecasting of pointer to integer.  The address space is 32 bit and type
 * casting to integer will not result into any loss because of TI's compiler
 * treatment to integer.
 */
                    pHndlObj->bufCfg.buffAddr[0U] =
                        (UInt32) newFrame->addr[0U][0U];
                    pHndlObj->bufCfg.pitch[0U] =
                        pHndlObj->calDmaVcCfg.wrDmaCfg[streamId].format.pitch
                        [0U];

                    rtnVal = VpsHal_isscalUpdateBufAddr(pInstObj->calHalHandle,
                                                        &pHndlObj->bufCfg);
                    cookie = BspOsal_disableInterrupt();
                    pHndlObj->currBufs[streamId][pHndlObj->next[streamId]] =
                                                        newFrame;
                    /* Reset the sub-frame count */
                    pHndlObj->currSubFrame[streamId][pHndlObj->next[streamId]] \
                        .subFrameNum = 0xFFFFFFFFU;

                    BspOsal_restoreInterrupt(cookie);
                }
                else
                {
                    /* The driver should ensure that this condition
                     *  should not occur. */
                    GT_assert(VpsIssCalCoreTrace, FALSE);
                }
            }

            if(FVID2_SOK == rtnVal)
            {
                pHndlObj->firstDmaStartIntr[streamId] = (uint32_t)FALSE;
            }
        }
    }
}

static void vcoreCaptXlineCmpltCb(const UInt32 *event,
                                UInt32        numEvents,
                                Ptr           arg)
{
    UInt32  i, eventNo, streamId;
    vpscoreissCaptCalHndlObj_t *pHndlObj;
    int32_t rtnVal;

    rtnVal   = FVID2_SOK;
    pHndlObj = (vpscoreissCaptCalHndlObj_t *) arg;

    for(i = 0U; i < numEvents; i++)
    {
        eventNo = event[i];
        if (IEM_CAL_EVENT_LINE_NUMBER == eventNo)
        {
            if((TRUE == pHndlObj->isSubFrameCfgValid) && (FVID2_SOK == rtnVal))
            {
                streamId = pHndlObj->subFrmstreamId;

                rtnVal = vcoreCaptSubFrameDoneProc(pHndlObj, streamId,
                                                            (uint32_t)FALSE);
            }
        }
        else
        {
            rtnVal = FVID2_EBADARGS;
        }
    }

    return;
}

static void vcoreCaptDmaCmpltCb(const UInt32 *event,
                                UInt32        numEvents,
                                Ptr           arg)
{
    UInt32  i, eventNo, streamId;
    int32_t rtnVal;
    vpscoreissCaptInstObj_t    *pInstObj;
    vpscoreissCaptCalHndlObj_t *pHndlObj;

    rtnVal   = FVID2_EBADARGS;
    pHndlObj = (vpscoreissCaptCalHndlObj_t *) arg;

    if((NULL != pHndlObj) && (NULL != event))
    {
        pInstObj = pHndlObj->pInstObj;
        if(NULL != pInstObj)
        {
            rtnVal = FVID2_SOK;
        }
    }

    if(FVID2_SOK == rtnVal)
    {
        for(i = 0U; i < numEvents; i++)
        {
/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'event'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 */
            eventNo = event[i];

            /* Translate event number to stream ID */
            if((CAL_EM_EVENT_WDMA_END0 <= eventNo) &&
               (eventNo <= CAL_EM_EVENT_WDMA_END7))
            {
                eventNo -= CAL_EM_EVENT_WDMA_END0;
                streamId = pHndlObj->eventToStreamIdMap[eventNo];
            }
            else
            {
                rtnVal   = FVID2_EBADARGS;
                streamId = 0U;
            }

            if((streamId < VPS_ISS_CAL_MAX_STREAMS) && (FVID2_SOK == rtnVal))
            {
                if(VCORE_CAL_STREAM_MODE_CAL_WRITE !=
                   pHndlObj->streamMode[streamId])
                {
                    /* If CAL is not writing, we do not expect end of frame
                        interrupt at all */
                    GT_assert(VpsIssCalCoreTrace, FALSE);
                }
            }
            else
            {
                rtnVal = FVID2_EBADARGS;
            }

            if((NULL != pHndlObj->emDmaCmpltHndl[streamId]) &&
               (FVID2_SOK == rtnVal))
            {
                rtnVal = vcoreCaptSubFrameDoneProc(pHndlObj, streamId,
                                                            (uint32_t)TRUE);
            }
        }
    }
}

static int32_t vcoreCaptSubFrameDoneProc(vpscoreissCaptCalHndlObj_t *pHndlObj,
                                        uint32_t                    streamId,
                                        uint32_t                    isEof)
{
    uint32_t cookie, tmpVal, frmStatus, vc, curr, cmplxIdx;
    volatile VpsCore_Frame  *tmpBuf;
    Fvid2_SubFrameInfo *tmpSubFrmStatus;
    vpscoreissCaptInstObj_t *pInstObj = NULL;
    vpscoreissCaptErrObj_t  *pErrObj = NULL;

    cookie      = BspOsal_disableInterrupt();
    curr        = pHndlObj->curr[streamId];
    /* Pending as, frame is not yet ready to be de-queued */
    frmStatus   = FVID2_FRAME_STATUS_PENDING;
    tmpBuf      = pHndlObj->currBufs[streamId][curr];
    tmpSubFrmStatus =
                &pHndlObj->currSubFrame[streamId][curr];

    /* Get errors status if any */
    pInstObj = pHndlObj->pInstObj;
    vc       = pInstObj->streamIdToVcMap[streamId];
    cmplxIdx = pInstObj->streamIdToPpiMap[streamId];
    GT_assert(VpsIssCalCoreTrace, (cmplxIdx < VPS_ISS_CAL_MAX_CMPLXIO_INST));
    pErrObj = &pInstObj->errObj[cmplxIdx];

    if(CAL_MAX_VIRTUAL_CHAN >= vc)
    {
        /* Note that error status (stored locally in s/w : handleObject is not)
            cleared. This would be cleared while returning back the frame.

            The rational is, if there was one/more error in the first-n-lines,
            this error could be applicable for complete frame. Typically,
            applications want to know reception at end of frame also */
        tmpVal = pErrObj->fifoOverFlow[vc] | pErrObj->eccCouldNotCorrect[vc]
                    | pErrObj->crcMisMatch[vc] | pErrObj->eccCorrected[vc];
        if((uint32_t) FALSE != tmpVal)
        {
            if((uint32_t) TRUE == pErrObj->fifoOverFlow[vc])
            {
                frmStatus = FVID2_FRAME_STATUS_OVERFLOW;
            }
            else if((uint32_t) TRUE == pErrObj->eccCouldNotCorrect[vc])
            {
                frmStatus = FVID2_FRAME_STATUS_ECC_ERROR;
            }
            else if((uint32_t) TRUE == pErrObj->crcMisMatch[vc])
            {
                frmStatus = FVID2_FRAME_STATUS_CRC_ERROR;
            }
            else if((uint32_t) TRUE == pErrObj->eccCorrected[vc])
            {
                frmStatus = FVID2_FRAME_STATUS_ECC_CORRECTED;
            }
            else
            {
                frmStatus = FVID2_FRAME_STATUS_OVERFLOW;
            }
        }
        tmpSubFrmStatus->subFrameNum = 0U;
        tmpBuf->status = frmStatus;
        tmpSubFrmStatus->numOutLines =
                    (tmpSubFrmStatus->subFrameNum + 1U) *
                    pHndlObj->subFrameCfg.notifyAfterFirstXLines[streamId];
        if (TRUE == isEof)
        {
            tmpSubFrmStatus->subFrameNum = 1U;
            tmpSubFrmStatus->numOutLines =
                pHndlObj->calDmaVcCfg.csi2VcCfg[streamId].lines;
        }

        /* Let Applications know */
        pHndlObj->subFrameCfg.appCb(pHndlObj->subFrameCfg.pAppCbArgs,
                                 (VpsCore_Frame *) tmpBuf,
                                 (Fvid2_SubFrameInfo *) tmpSubFrmStatus);
        if (TRUE == isEof)
        {
            tmpSubFrmStatus->subFrameNum = 0xFFFFFFFFU;
        }
        BspOsal_restoreInterrupt(cookie);
    }
    return BSP_SOK;
}

static int32_t vcoreCaptFrameDoneProc(vpscoreissCaptCalHndlObj_t *pHndlObj,
                                      uint32_t                    streamId)
{
    uint32_t cookie, tmpVal, frmStatus, vc, cmplxIdx;
    volatile VpsCore_Frame  *tmpBuf;
    vpscoreissCaptInstObj_t *pInstObj = NULL;
    vpscoreissCaptErrObj_t  *pErrObj = NULL;

    cookie    = BspOsal_disableInterrupt();
    frmStatus = FVID2_FRAME_STATUS_COMPLETED;
    tmpBuf    = pHndlObj->currBufs[streamId][pHndlObj->curr[streamId]];
    tmpVal    = pHndlObj->curr[streamId];
    pHndlObj->currBufs[streamId][pHndlObj->curr[streamId]] = NULL;
    pHndlObj->curr[streamId] = pHndlObj->next[streamId];
    pHndlObj->next[streamId] = tmpVal;
    pInstObj = pHndlObj->pInstObj;
    vc       = pInstObj->streamIdToVcMap[streamId];
    cmplxIdx = pInstObj->streamIdToPpiMap[streamId];

    GT_assert(VpsIssCalCoreTrace, (cmplxIdx < VPS_ISS_CAL_MAX_CMPLXIO_INST));

    pErrObj = &pInstObj->errObj[cmplxIdx];
    /* Update error status if any */
    if(CAL_BYS_IN_POSITION >= vc)
    {
        tmpVal = pErrObj->fifoOverFlow[vc] |
                 pErrObj->eccCouldNotCorrect[vc] |
                 pErrObj->crcMisMatch[vc] |
                 pErrObj->eccCorrected[vc];

        if((uint32_t) FALSE != tmpVal)
        {
            if((uint32_t) TRUE == pErrObj->fifoOverFlow[vc])
            {
                frmStatus = FVID2_FRAME_STATUS_OVERFLOW;
                pErrObj->fifoOverFlow[vc] = (uint32_t) FALSE;
            }
            else if((uint32_t) TRUE == pErrObj->eccCouldNotCorrect[vc])
            {
                frmStatus = FVID2_FRAME_STATUS_ECC_ERROR;
                pErrObj->eccCouldNotCorrect[vc] = (uint32_t) FALSE;
            }
            else if((uint32_t) TRUE == pErrObj->crcMisMatch[vc])
            {
                frmStatus = FVID2_FRAME_STATUS_CRC_ERROR;
                pErrObj->crcMisMatch[vc] = (uint32_t) FALSE;
            }
            else if((uint32_t) TRUE == pErrObj->eccCorrected[vc])
            {
                frmStatus = FVID2_FRAME_STATUS_ECC_CORRECTED;
                pErrObj->eccCorrected[vc] = (uint32_t) FALSE;
            }
            else
            {
                frmStatus = FVID2_FRAME_STATUS_OVERFLOW;
            }
        }
    }

/* MISRA.CAST.CONST
 * MISRAC_2004_Rule_11.8
 * Name 'tmpBuf'
 * Cast operation removes const or volatile modifier from a pointer or reference
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  This buffer was allocated and queued by an entity outside this driver.
 *  This buffer might require modification in the ISR context itself and hence
 *  this is not marked as a pointer to a constant.
 */
    tmpBuf->status = frmStatus;
    BspOsal_restoreInterrupt(cookie);
    pHndlObj->openPrms.frmDoneCb(pHndlObj->openPrms.drvData,
                                 (VpsCore_Frame *) tmpBuf);
    return BSP_SOK;
}

static int32_t vcoreCaptDeAllocCalRes(
    Irm_Modules_t         calId,
    vpsissCaptureBlocks_t resDeAlloc[
        VPS_ISS_CAL_MAX_STREAMS],
    UInt32                cnt)
{
    UInt32  i;
    int32_t rtnVal = FVID2_EBADARGS;
    for(i = 0U; i < cnt; i++)
    {
        if(i >= VPS_ISS_CAL_MAX_STREAMS)
        {
            rtnVal = FVID2_EBADARGS;
            break;
        }
        rtnVal = Irm_releaseResource(0x0U, calId, &resDeAlloc[i]);
        GT_assert(VpsIssCalCoreTrace, (FVID2_SOK == rtnVal));
    }

    return (rtnVal);
}

static int32_t vcoreCaptAllocCalRes(
    Irm_Modules_t                   calId,
    vpscoreissCaptCalHndlObj_t     *pHndlObj,
    const vcoreissCaptOpenParams_t *pOpenParams,
    vcoreissCaptOpenRetParams_t    *pOpenRtnPrms)
{
    UInt32 i, j;
    Int32  rtnVal = FVID2_SOK;
    vpscoreissCaptInstObj_t *pInstObj;

    GT_assert(VpsIssCalCoreTrace, (NULL != pHndlObj));
    pInstObj = pHndlObj->pInstObj;
    GT_assert(VpsIssCalCoreTrace, (NULL != pInstObj));

    /* The ISR determines establishes the relation between stream id and event
     *  using a look up table.
     *  This implementation assume that there are equal number of DMA start &
     *  end events. Starting from 0 + offset.
     *  Where offset could vary for start & end events.
     *  If any of the above conditions is not met, the event handling in the
     *  ISR requires an update
     *  i.e. (CAL_EM_EVENT_WDMA_START7 - CAL_EM_EVENT_WDMA_START0) ==
     *  (CAL_EM_EVENT_WDMA_END7 - CAL_EM_EVENT_WDMA_END0)
     */

    /* TODO: Separate allocator for vport based capture and isp resources,
     *       Brijesh */
    for(i = 0U; ((i < pOpenParams->numStreams) && (FVID2_SOK == rtnVal));
        i++)
    {
        /*
            1. Assume this stream is not to be processed by CAL.
            2. Will be processed by CAL, if one of subModules is used
            3. Will be written out by CAL, if WR DMA module is used for this
                stream. As streams cannot be replicated with in CAL, the above
                conditions ensure correct mode of stream */
        pHndlObj->streamMode[i] = VCORE_CAL_STREAM_MODE_ISP;
        if(0x0U != pOpenParams->subModules[i])
        {
            rtnVal = Irm_allocResource(0x0, calId, pOpenParams->subModules[i],
                                       &pHndlObj->allocatedRes[i], (UInt32)
                                       (
                                           IRM_CAL_ALLOC_POLICY_CPORTID_0_LEAST_PREFFERED
                                           |
                                           IRM_CAL_ALLOC_POLICY_WRDMA_0_LEAST_PREFFERED));

            /* Check this only if Write DMA resource is requested */
            if(FVID2_SOK == rtnVal)
            {
                pHndlObj->streamMode[i] = VCORE_CAL_STREAM_MODE_CAL;

                if(0U != (pOpenParams->subModules[i] &
                          VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID))
                {
                    pHndlObj->streamMode[i] = VCORE_CAL_STREAM_MODE_CAL_WRITE;
                    j = pHndlObj->allocatedRes[i].wrDma;
                    if(j <=
                       (CAL_EM_EVENT_WDMA_START7 - CAL_EM_EVENT_WDMA_START0))
                    {
                        /* The DMA channel number is between 0U & 7.
                         * Anything else requires update! */
                        pHndlObj->dmaStartEvent[i] = j +
                                                     CAL_EM_EVENT_WDMA_START0;
                        pHndlObj->eventToStreamIdMap[j] = i;
                    }
                    else
                    {
                        /* ?? Resource manager allocated in valid DMA context*/
                        GT_assert(VpsIssCalCoreTrace, (FALSE));
                    }
                    /* Might seem redundant check, but required if the events
                     *  position is changed, this would require update! */
                    if(j <= (CAL_EM_EVENT_WDMA_END7 - CAL_EM_EVENT_WDMA_END0))
                    {
                        pHndlObj->dmaCmpltEvent[i] =
                            j + CAL_EM_EVENT_WDMA_END0;
                    }
                    else
                    {
                        /* ?? Resource manager allocated in valid DMA context*/
                        GT_assert(VpsIssCalCoreTrace, (FALSE));
                    }
                }
            }
            else
            {
                pOpenRtnPrms->streamAllocError = i;
                rtnVal = vcoreCaptDeAllocCalRes(
                    calId,
                    &pHndlObj->allocatedRes[0U],
                    i);
                GT_assert(VpsIssCalCoreTrace, (FVID2_SOK != rtnVal));
            }
        }
    }

    if(FVID2_SOK == rtnVal)
    {
        pHndlObj->numStreams    = pOpenParams->numStreams;
        pHndlObj->bysOutCportId = VPS_ISS_CAPT_MOD_MAX_ID;
        pHndlObj->vportCportId  = VPS_ISS_CAPT_MOD_MAX_ID;

        /* Store the cport ids for the bys out and vport output ports */
        for(i = 0U; i < pOpenParams->numStreams; i++)
        {
            if(0U != (pOpenParams->subModules[i] &
                      VPS_ISS_CAPT_CAL_SUB_BYS_OUT_ID))
            {
                pHndlObj->bysOutCportId = pHndlObj->allocatedRes[i].cport;
            }
            if(0U != (pOpenParams->subModules[i] &
                      VPS_ISS_CAPT_CAL_SUB_VPORT_ID))
            {
                pHndlObj->vportCportId = pHndlObj->allocatedRes[i].cport;
            }
        }
    }

    return (rtnVal);
}

static int32_t vcoreCaptOpenHals(Irm_Modules_t                    calId,
                                 const vpscoreissCaptCalHndlObj_t *pHndlObj)
{
    int32_t  rtnVal = FVID2_SOK;
    uint32_t halCalId;
    isshalCalOpenParams_t     openParms;
    vpscoreissCaptInstObj_t  *pInstObj;

    GT_assert(VpsIssCalCoreTrace, (NULL != pHndlObj));
    pInstObj = pHndlObj->pInstObj;
    GT_assert(VpsIssCalCoreTrace, (NULL != pInstObj));

    if (VPS_ISS_CAPT_CAL_A_CPI != pInstObj->instId)
    {
        /* CAL A by default */
        halCalId = 0;
        if(IRM_MODULE_CAL_B == calId)
        {
            halCalId = 1U;
        }

        openParms.instId = halCalId;
        openParms.mode   = VPS_HAL_ISS_CAL_MODE_CAPTURE;

        pInstObj->calHalHandle = VpsHal_isscalOpen(&openParms, NULL);
        if(NULL != pInstObj->calHalHandle)
        {
            rtnVal = FVID2_SOK;
        }
        else
        {
            GT_assert(VpsIssCalCoreTrace, (FALSE));
            rtnVal = FVID2_EALLOC;
        }
    }

    return (rtnVal);
}

static int32_t vcoreCaptCloseHals(const vpscoreissCaptCalHndlObj_t *pHndlObj)
{
    int32_t rtnVal = FVID2_EBADARGS;
    vpscoreissCaptInstObj_t *pInstObj;

    GT_assert(VpsIssCalCoreTrace, (NULL != pHndlObj));
    pInstObj = pHndlObj->pInstObj;
    GT_assert(VpsIssCalCoreTrace, (NULL != pInstObj));

    if(NULL != pInstObj)
    {
        if(NULL != pInstObj->calHalHandle)
        {
            rtnVal = VpsHal_isscalClose(pInstObj->calHalHandle, NULL);
            pInstObj->calHalHandle = NULL;
        }

        if((FVID2_SOK == rtnVal) && (0x1U == pInstObj->numOpens))
        {
            /* Nothing much to do now!!! */
        }
    }

    return (rtnVal);
}

static int32_t vcoreCaptCheckCalCfg(const vpscoreissCaptCalHndlObj_t *pHndl,
                                    const isshalCalCfg_t             *pCalCfg)
{
    int32_t rtnVal = FVID2_SOK;
    UInt32  i, j, isCalStreamsDone;

    GT_assert(VpsIssCalCoreTrace, (NULL != pHndl));
    GT_assert(VpsIssCalCoreTrace, (NULL != pCalCfg));
    isCalStreamsDone = (uint32_t)FALSE;

    for(i = 0U; ((i < pHndl->numStreams) && (FVID2_SOK == rtnVal)); i++)
    {
        /* For all valid CAL streams, check if CPORT ID match up */
        if((VCORE_CAL_STREAM_MODE_CAL == pHndl->streamMode[i]) ||
           (VCORE_CAL_STREAM_MODE_CAL_WRITE == pHndl->streamMode[i]))
        {
            rtnVal = FVID2_EBADARGS;
            if(TRUE == isCalStreamsDone)
            {
                /* We expect all CAL streams to be specified first,
                    followed by other streams */
                break;
            }

            for(j = 0U; j < pHndl->numStreams; j++)
            {
                if(pCalCfg->cportId[i] == pHndl->allocatedRes[j].cport)
                {
                    rtnVal = FVID2_SOK;
                    break;
                }
            }
        }
        else if(VCORE_CAL_STREAM_MODE_ISP == pHndl->streamMode[i])
        {
            /* No checks for other streams here, right now! */
            isCalStreamsDone = (uint32_t)TRUE;
            rtnVal           = FVID2_SOK;
        }
        else
        {
            isCalStreamsDone = (uint32_t)TRUE;
            rtnVal           = FVID2_EBADARGS;
        }
    }

    /* TODO check what has been allocated and what's being configured */

    return (rtnVal);
}

static int32_t vcoreCaptMakeCalCoreCfg(vpscoreissCaptCalHndlObj_t *pHndl,
                                       isshalCalCfg_t             *pCalCfg)
{
    int32_t rtnVal;
    UInt32  i, j;
    isshalCalDmaVcCfg_t         *pDmaVcCfg;
    const vpsissCaptureBlocks_t *allocRes;

    GT_assert(VpsIssCalCoreTrace, (NULL != pHndl));
    GT_assert(VpsIssCalCoreTrace, (NULL != pCalCfg));
    pDmaVcCfg = &pHndl->calDmaVcCfg;
    GT_assert(VpsIssCalCoreTrace, (NULL != pDmaVcCfg));

    rtnVal = FVID2_SOK;

    pDmaVcCfg->numCPortId = 0x0U;
    for(i = 0U; ((i < pHndl->numStreams) && (FVID2_SOK == rtnVal)); i++)
    {
        rtnVal = FVID2_EBADARGS;
        /* If CAL is processing a given stream, compute the core config
            required, else ignore it */
        if((VCORE_CAL_STREAM_MODE_CAL_WRITE == pHndl->streamMode[i])
           ||
           (VCORE_CAL_STREAM_MODE_CAL == pHndl->streamMode[i]))
        {
            /* Find associated cport ID */
            for(j = 0U; j < pHndl->numStreams; j++)
            {
                if(pCalCfg->cportId[i] == pHndl->allocatedRes[j].cport)
                {
                    rtnVal = FVID2_SOK;
                    pDmaVcCfg->numCPortId++;
                    allocRes = &pHndl->allocatedRes[j];
                    break;
                }
            }

            if(FVID2_SOK == rtnVal)
            {
                pDmaVcCfg->cportId[i] = allocRes->cport;
                if(TRUE == pCalCfg->isCsi2BasedCapture[i])
                {
                    pDmaVcCfg->isCsi2VcCfgValid[i] = (uint32_t)TRUE;
                    if (0xFFFFFFFFU != allocRes->ppi0Inst)
                    {
                        pDmaVcCfg->csi2VcCfg[i].instance        = 0x0;
                    }
                    else if (0xFFFFFFFFU != allocRes->ppi1Inst)
                    {
                        pDmaVcCfg->csi2VcCfg[i].instance        = 0x1;
                    }
                    else
                    {
                        rtnVal = FVID2_EBADARGS;
                    }
                    pDmaVcCfg->csi2VcCfg[i].contextToBeUsed = allocRes->csi2Ctx;
                    pDmaVcCfg->csi2VcCfg[i].virtualChanNum  =
                        pCalCfg->virtualChanNum[i];

                    /* Generate FVID2 format and bpp from MIPI data type */
                    pDmaVcCfg->csi2VcCfg[i].dt  = pCalCfg->csiDataType[i];
                    pDmaVcCfg->csi2VcCfg[i].att = (uint32_t)TRUE;
                    if((int32_t) TRUE ==
                       vcoreCaptCsi2IsPixData(pCalCfg->csiDataType[i]))
                    {
                        pDmaVcCfg->csi2VcCfg[i].att = (uint32_t)FALSE;
                    }
#ifdef PLATFORM_SIM
                    pDmaVcCfg->csi2VcCfg[i].att = (uint32_t)FALSE;
#endif
                    if((int32_t)FALSE == vcoreCaptCsi2IsDataYuv420
                           (pDmaVcCfg->csi2VcCfg[i].dt))
                    {
                        pDmaVcCfg->csi2VcCfg[i].lines =
                            pCalCfg->streamFmt[i].height;
                    }
                    else
                    {
                        pDmaVcCfg->csi2VcCfg[i].lines =
                            ((uint32_t)(pCalCfg->streamFmt[i].height * 3) >> 1);
                    }
                }
                else
                {
                    pDmaVcCfg->isCsi2VcCfgValid[i] = (uint32_t)FALSE;
                }

                pDmaVcCfg->isWrDmaCfgValid[i] = (uint32_t)FALSE;
                if (TRUE == pCalCfg->writeToMem[i])
                {
                    pDmaVcCfg->isWrDmaCfgValid[i]          = (uint32_t)TRUE;
                    pDmaVcCfg->wrDmaCfg[i].contextToBeUsed = allocRes->wrDma;
                    pDmaVcCfg->wrDmaCfg[i].mode =
                        VPS_HAL_ISS_CAL_DMA_WR_DISABLED;

                    pDmaVcCfg->wrDmaCfg[i].stream = VPS_ISS_CAL_TAG_ATT_HDR;

                    if(((int32_t) TRUE ==
                        vcoreCaptCsi2IsPixData(pCalCfg->csiDataType[i]))
                       || (((uint32_t)TRUE == pCalCfg->isBysInCfgValid[i]) &&
                           ((uint32_t)TRUE == pCalCfg->bysInEnable[i])))
                    {
                        pDmaVcCfg->wrDmaCfg[i].stream =
                            VPS_ISS_CAL_TAG_PIX_DATA;
                    }

                    pDmaVcCfg->wrDmaCfg[i].stallM2MRd = (uint32_t)TRUE;
                    /* No Support for skip mode now TODO */
                    pDmaVcCfg->wrDmaCfg[i].ySkipMode  = 0x0;
                    pDmaVcCfg->wrDmaCfg[i].xPixelSkip = 0x0;

                    /* Width expressed in-terms of 64 bit words. */
                    if(FVID2_BPP_BITS32 == pCalCfg->streamFmt[i].bpp)
                    {
                        pDmaVcCfg->wrDmaCfg[i].format.width =
                            ((4U * pCalCfg->streamFmt[i].width) + 7U) / 8U;
                    }
                    else if(FVID2_BPP_BITS24 == pCalCfg->streamFmt[i].bpp)
                    {
                        pDmaVcCfg->wrDmaCfg[i].format.width =
                            ((3U * pCalCfg->streamFmt[i].width) + 7U) / 8U;
                    }
                    else if((FVID2_BPP_BITS10 == pCalCfg->streamFmt[i].bpp) ||
                            (FVID2_BPP_BITS11 == pCalCfg->streamFmt[i].bpp) ||
                            (FVID2_BPP_BITS12 == pCalCfg->streamFmt[i].bpp) ||
                            (FVID2_BPP_BITS13 == pCalCfg->streamFmt[i].bpp) ||
                            (FVID2_BPP_BITS14 == pCalCfg->streamFmt[i].bpp) ||
                            (FVID2_BPP_BITS15 == pCalCfg->streamFmt[i].bpp) ||
                            (FVID2_BPP_BITS16 == pCalCfg->streamFmt[i].bpp))
                    {
                        pDmaVcCfg->wrDmaCfg[i].format.width =
                            ((2U * pCalCfg->streamFmt[i].width) + 7U) / 8U;
                    }
                    else
                    {
                        pDmaVcCfg->wrDmaCfg[i].format.width =
                            ((1U * pCalCfg->streamFmt[i].width) + 7U) / 8U;
                    }

                    pDmaVcCfg->wrDmaCfg[i].format.height =
                        pCalCfg->streamFmt[i].height;
                    pDmaVcCfg->wrDmaCfg[i].format.pitch[0U] =
                        pCalCfg->streamFmt[i].pitch[0U];
                }
                else
                {
                    pDmaVcCfg->isWrDmaCfgValid[i] = (uint32_t)FALSE;
                }
            }
        }
        else if(VCORE_CAL_STREAM_MODE_ISP == pHndl->streamMode[i])
        {
            rtnVal = FVID2_SOK;
        }
        else
        {
            /* In valid stream */
            break;
        }
    }

    if(FVID2_SOK == rtnVal)
    {
        pCalCfg->pDmaVcCfg = &pHndl->calDmaVcCfg;
    }
    return rtnVal;
}

static int32_t vcoreCaptDetermineInst(const vpscoreissCaptCalHndlObj_t *pHndl,
                                      isshalCalCfg_t                   *pCalCfg)
{
    int32_t rtnVal;
    UInt32  i, j;
    const vpsissCaptureBlocks_t *allocRes;

    GT_assert(VpsIssCalCoreTrace, (NULL != pHndl));
    GT_assert(VpsIssCalCoreTrace, (NULL != pCalCfg));

    rtnVal = FVID2_SOK;

    for(i = 0U; ((i < pCalCfg->numCPortId) && (FVID2_SOK == rtnVal)); i++)
    {
        rtnVal = FVID2_EBADARGS;
        /* Find associated cport ID */
        for(j = 0U; j < pHndl->numStreams; j++)
        {
            if(pCalCfg->cportId[i] == pHndl->allocatedRes[j].cport)
            {
                allocRes = &pHndl->allocatedRes[j];
                rtnVal   = FVID2_SOK;
                break;
            }
        }

        if(FVID2_SOK == rtnVal)
        {
            if(TRUE == pCalCfg->isPixProcCfgValid[i])
            {
                if((allocRes->pixExtract != allocRes->dpmDecode) ||
                   (allocRes->dpmEncode != allocRes->pixPack))
                {
                    GT_assert(VpsIssCalCoreTrace, FALSE);
                }
                pCalCfg->pixProcCfg[i].contextToBeUsed = allocRes->pixExtract;
            }
            /* TODO for bys out/in & vport */
        }
    }
    return rtnVal;
}

static void vcoreCaptSetDefaultParams(isshalCalCfg_t      *pCalCfg,
                                      isshalCalDmaVcCfg_t *pCalCoreCfg)
{
    if(NULL != pCalCfg)
    {
        BspUtils_memset((Ptr) pCalCfg, 0x0, sizeof(isshalCalCfg_t));
        pCalCfg->numCPortId    = 0x01U;
        pCalCfg->cportId[0x0U] = 0x01U;

        pCalCfg->streamFmt[0x0].chNum      = 0x0;    /* Do not care not used */
        pCalCfg->streamFmt[0x0].width      = 640U;
        pCalCfg->streamFmt[0x0].height     = 480U;
        pCalCfg->streamFmt[0x0].pitch[0x0] = 640U * 3U;
        pCalCfg->streamFmt[0x0].dataFormat = FVID2_DF_RGB24_888;
        pCalCfg->streamFmt[0x0].bpp        = FVID2_BPP_BITS24;
        pCalCfg->csiDataType[0x0]          = VPS_ISS_CAL_CSI2_RGB888;

        pCalCfg->isCsi2BasedCapture[0x0] = (uint32_t)TRUE;
        pCalCfg->virtualChanNum[0x0]     = 0x03U;

        pCalCfg->isPixProcCfgValid[0x0] = (uint32_t)FALSE;
        pCalCfg->isBysOutCfgValid[0x0]  = (uint32_t)FALSE;
        pCalCfg->isBysInCfgValid[0x0]   = (uint32_t)FALSE;
        pCalCfg->isVportCfgValid[0x0]   = (uint32_t)FALSE;
    }
    if(NULL != pCalCoreCfg)
    {
        pCalCoreCfg->isCsi2VcCfgValid[0x0]         = (uint32_t)TRUE;
        pCalCoreCfg->csi2VcCfg[0U].instance        = 0x0;
        pCalCoreCfg->csi2VcCfg[0U].contextToBeUsed = 0x0;
        pCalCoreCfg->csi2VcCfg[0U].virtualChanNum  = 0x3U;
        pCalCoreCfg->csi2VcCfg[0U].dt              = 0x24; /* RGB 888 */
        pCalCoreCfg->csi2VcCfg[0U].att             = (uint32_t)FALSE;
        pCalCoreCfg->csi2VcCfg[0U].lines           = 480U;

        pCalCoreCfg->isWrDmaCfgValid[0U]          = (uint32_t)TRUE;
        pCalCoreCfg->wrDmaCfg[0U].contextToBeUsed = 0x1;
        pCalCoreCfg->wrDmaCfg[0U].mode =
            VPS_HAL_ISS_CAL_DMA_WR_CONST;
        pCalCoreCfg->wrDmaCfg[0U].stream           = VPS_ISS_CAL_TAG_PIX_DATA;
        pCalCoreCfg->wrDmaCfg[0U].stallM2MRd       = (uint32_t)TRUE;
        pCalCoreCfg->wrDmaCfg[0U].ySkipMode        = 0x0;
        pCalCoreCfg->wrDmaCfg[0U].xPixelSkip       = 0x0;
        pCalCoreCfg->wrDmaCfg[0U].format.width     = 640U;
        pCalCoreCfg->wrDmaCfg[0U].format.height    = 480U;
        pCalCoreCfg->wrDmaCfg[0U].format.pitch[0U] = 640U * 3U;

        pCalCoreCfg->isRdDmaCfgValid[0U] = (uint32_t)FALSE;
    }
}

static int32_t vcoreCaptCsi2IsPixData(UInt32 dataFmt)
{
    int32_t retVal;
    switch(dataFmt)
    {
        case VPS_ISS_CAL_CSI2_YUV420_8B:
        case VPS_ISS_CAL_CSI2_YUV420_10B:
        case VPS_ISS_CAL_CSI2_YUV420_8B_LEGACY:
        case VPS_ISS_CAL_CSI2_YUV420_8B_CHROMA_SHIFT:
        case VPS_ISS_CAL_CSI2_YUV420_10B_CHROMA_SHIFT:
        case VPS_ISS_CAL_CSI2_YUV422_8B:
        case VPS_ISS_CAL_CSI2_YUV422_10B:
        case VPS_ISS_CAL_CSI2_RGB444:
        case VPS_ISS_CAL_CSI2_RGB555:
        case VPS_ISS_CAL_CSI2_RGB565:
        case VPS_ISS_CAL_CSI2_RGB666:
        case VPS_ISS_CAL_CSI2_RGB888:
        case VPS_ISS_CAL_CSI2_RAW6:
        case VPS_ISS_CAL_CSI2_RAW7:
        case VPS_ISS_CAL_CSI2_RAW8:
        case VPS_ISS_CAL_CSI2_RAW10:
        case VPS_ISS_CAL_CSI2_RAW12:
        case VPS_ISS_CAL_CSI2_RAW14:
        case VPS_ISS_CAL_CSI2_ANY:
            retVal = (int32_t)TRUE;
            break;
        default:
            retVal = (int32_t)FALSE;
            break;
    }

    return retVal;
}

static inline int32_t vcoreCaptCsi2IsDataYuv420(UInt32 dataFmt)
{
    Int32 retVal;

    switch(dataFmt)
    {
        case VPS_ISS_CAL_CSI2_YUV420_8B:
        case VPS_ISS_CAL_CSI2_YUV420_10B:
        case VPS_ISS_CAL_CSI2_YUV420_8B_LEGACY:
        case VPS_ISS_CAL_CSI2_YUV420_8B_CHROMA_SHIFT:
        case VPS_ISS_CAL_CSI2_YUV420_10B_CHROMA_SHIFT:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static int32_t vcoreCaptCheckOpenParams(
    const vpscoreissCaptInstObj_t  *pInstObj,
    const vcoreissCaptOpenParams_t *pOpenParams)
{
    int32_t  retVal = FVID2_SOK;
    uint32_t i, lSubModules;

    GT_assert(VpsIssCalCoreTrace, (NULL != pInstObj));
    GT_assert(VpsIssCalCoreTrace, (NULL != pOpenParams));

    if(pOpenParams->numStreams > VPS_ISS_CAL_MAX_STREAMS)
    {
        retVal = FVID2_EBADARGS;
    }

    if((VPS_ISS_CAPT_CAL_A_CPI == pInstObj->instId) &&
       (VPSCORE_ISS_CAPT_IF_CPI != pOpenParams->captIf))
    {
        /* Only Parallel interface is supported on Vport instance */
        retVal = FVID2_EBADARGS;
    }

    for(i = 0U; ((i < pOpenParams->numStreams) && (FVID2_SOK == retVal));
        i++)
    {
        lSubModules = pOpenParams->subModules[i];
        if((VPS_ISS_CAPT_CAL_A_CPI == pInstObj->instId) && (0U != lSubModules))
        {
            /* No CAL modules supported for the VPort instance */
            retVal = FVID2_EBADARGS;
        }
    }

    return (retVal);
}

static vpscoreissCaptCalHndlObj_t *vcoreCaptAllocHndlObj(
    vpscoreissCaptInstObj_t *pInstObj)
{
    uint32_t cnt;
    vpscoreissCaptCalHndlObj_t *hObj = NULL;

    GT_assert(VpsIssCalCoreTrace, (NULL != pInstObj));

/* C & C++ INVARIANT_CONDITION.GEN
 * Expression 'cnt < (1)' used in the condition always yields the same result.
 * Name 'VCORE_ISS_CAPT_MAX_OPEN'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In this perticular case, core can be opned only once. When multiple open is
 *  supported (other i/f support, logical handles, etc...) this is required.
 *  By having this check, no unintended operation is caused.
 */
    for(cnt = 0U; cnt < VCORE_ISS_CAPT_MAX_OPEN; cnt++)
    {
        if(FALSE == gCaptHndlObjs[pInstObj->instId][cnt].isAllocated)
        {
            gCaptHndlObjs[pInstObj->instId][cnt].isAllocated = (uint32_t)TRUE;
            hObj = &gCaptHndlObjs[pInstObj->instId][cnt];
            BspUtils_memset((Ptr)
                            &gCaptHndlObjs[pInstObj->instId][cnt].allocatedRes,
                            (UInt8) 0xFF,
                            (sizeof(vpsissCaptureBlocks_t) *
                             VPS_ISS_CAL_MAX_STREAMS));
            hObj->pInstObj = pInstObj;
            break;
        }
    }

    return (hObj);
}

static int32_t vcoreCaptRegisterIsr(vpscoreissCaptCalHndlObj_t *pHndlObj)
{
    int32_t                   rtnVal = FVID2_SOK;
    uint32_t                  i;
    calemEventGroup_t         eventGroup;
    vpscoreissCaptInstObj_t  *pInstObj;
    vcoreissCaptOpenParams_t *pOpenParams;

    GT_assert(VpsIssCalCoreTrace, (NULL != pHndlObj));
    pInstObj = pHndlObj->pInstObj;
    GT_assert(VpsIssCalCoreTrace, (NULL != pInstObj));

    /* Assumes open parameters are already copied to handle object */
    pOpenParams = &pHndlObj->coreOpenPrms;
    GT_assert(VpsIssCalCoreTrace, (NULL != pOpenParams));

    eventGroup = CAL_EM_EG_CAL;

    /* Register DMA write start and DMA write end interrupts */
    for(i = 0; ((i < pOpenParams->numStreams) && (FVID2_SOK == rtnVal));
        i++)
    {
        if(VCORE_CAL_STREAM_MODE_CAL_WRITE == pHndlObj->streamMode[i])
        {
            pHndlObj->emDmaStartHndl[i] = Vps_calEmRegister(
                pInstObj->initPrms.irqNum,
                eventGroup,
                &pHndlObj->dmaStartEvent[i],
                1U,
                CAL_EM_PRIORITY4,
                vcoreCaptDmaStartCb,
                (Ptr) pHndlObj);
            if(NULL == pHndlObj->emDmaStartHndl[i])
            {
                rtnVal = FVID2_EFAIL;
            }

            if(TRUE == pInstObj->useDmaEndIntr)
            {
                pHndlObj->emDmaCmpltHndl[i] = Vps_calEmRegister(
                    pInstObj->initPrms.irqNum,
                    eventGroup,
                    &pHndlObj->dmaCmpltEvent[i],
                    1U,
                    CAL_EM_PRIORITY4,
                    vcoreCaptDmaCmpltCb,
                    (Ptr) pHndlObj);
                if(NULL == pHndlObj->emDmaCmpltHndl[i])
                {
                    rtnVal = FVID2_EFAIL;
                }
            }
        }
    }

    return (rtnVal);
}


static int32_t vcoreIssSetCalConfig(vpscoreissCaptCalHndlObj_t *pHndlObj,
                                    const vpsissCalCfg_t       *pCfg)
{
    /* Static to minimize stack requirement, config computed by this function
        and supplied to local function to be applied. */
    static isshalCalCfg_t    halCfg;
    int32_t retVal = FVID2_SOK;
    uint32_t i, strmId, cmplxIoId;
    vpscoreissCaptInstObj_t *pInstObj = NULL;

    /* Check for NULL done by the caller, just assert */
    GT_assert(VpsIssCalCoreTrace, (NULL != pHndlObj));
    GT_assert(VpsIssCalCoreTrace, (NULL != pCfg));
    pInstObj = pHndlObj->pInstObj;
    GT_assert(VpsIssCalCoreTrace, (NULL != pInstObj));

    /* Steps
        . Get the current config for all the streams that were created
        . Updated the streams, for which config is given
        . For non-cal streams, nothing much to do ignore
        . For CAL streams, construct the config required as understood by core
        . Update the config for all the streams
        */
    BspUtils_memcpy((Ptr) (&halCfg), (const void *) (&pInstObj->calCfg),
                    sizeof(isshalCalCfg_t));
    halCfg.numCPortId = 0;

    for (i = 0;i < pCfg->numStream; i ++)
    {
        cmplxIoId = pCfg->cmplxIoId[i];
        if ((cmplxIoId >= VPS_ISS_CAL_MAX_CMPLXIO_INST) ||
            ((uint32_t)(TRUE) !=
                pHndlObj->coreOpenPrms.isCmplxIoCfgValid[cmplxIoId]))
        {
            retVal = FVID2_EINVALID_PARAMS;
            break;
        }
    }

    for(i = 0; ((i < pCfg->numStream) && (FVID2_SOK == retVal)); i++)
    {
        retVal = FVID2_EINVALID_PARAMS;
        strmId = pCfg->streamId[i];
        if(strmId < VPS_ISS_CAL_MAX_STREAMS)
        {
            /* In case of OTF, we could have streams that need not go to ISP
                for processing. It could directly written to memory via CAL
                write */

            if((VCORE_CAL_STREAM_MODE_CAL_WRITE ==
                pHndlObj->streamMode[strmId]) ||
               (VCORE_CAL_STREAM_MODE_CAL == pHndlObj->streamMode[strmId]))
            {
                GT_assert(VpsIssCalCoreTrace, (IRM_RES_CAL_INVALID !=
                                               pHndlObj->allocatedRes[strmId].
                                               cport));

                retVal = FVID2_SOK;
                halCfg.cportId[strmId] = pHndlObj->allocatedRes[strmId].cport;

                halCfg.streamFmt[strmId].width      = pCfg->inFmt[i].width;
                halCfg.streamFmt[strmId].height     = pCfg->inFmt[i].height;
                halCfg.streamFmt[strmId].pitch[0]   = pCfg->inFmt[i].pitch[0];
                halCfg.streamFmt[strmId].pitch[1U]  = pCfg->inFmt[i].pitch[1U];
                halCfg.streamFmt[strmId].pitch[2U]  = pCfg->inFmt[i].pitch[2U];
                halCfg.streamFmt[strmId].bpp        = pCfg->inFmt[i].bpp;
                halCfg.streamFmt[strmId].dataFormat = pCfg->inFmt[i].dataFormat;

                if((VPSCORE_ISS_CAPT_IF_CSI2 == pHndlObj->coreOpenPrms.captIf)
                   && (VPS_ISS_CAL_CSI2_DISABLE_CONTEXT !=
                       pCfg->csi2DataFormat[i]))
                {
                    halCfg.isCsi2BasedCapture[strmId] = (uint32_t)TRUE;
                }
                else
                {
                    halCfg.isCsi2BasedCapture[strmId] = (uint32_t)FALSE;
                }

                halCfg.stream[strmId]         = pCfg->streamType[i];
                halCfg.csiDataType[strmId]    = pCfg->csi2DataFormat[i];
                halCfg.virtualChanNum[strmId] = pCfg->csi2VirtualChanNo[i];
                if(VPSCORE_ISS_CAPT_IF_CSI2 == pHndlObj->coreOpenPrms.captIf)
                {
                    pInstObj->streamIdToVcMap[strmId] =
                        halCfg.virtualChanNum[strmId];
                    pInstObj->streamIdToPpiMap[strmId] =
                        pCfg->cmplxIoId[i];
                }

                halCfg.isPixProcCfgValid[strmId] = pCfg->isPixProcCfgValid[i];
                BspUtils_memcpy((Ptr) (&halCfg.pixProcCfg[strmId]),
                                (const void *) (&pCfg->pixProcCfg[i]),
                                sizeof(vpsissCalPixProc_t));

                halCfg.isBysOutCfgValid[strmId] = pCfg->isBysOutCfgValid[i];
                BspUtils_memcpy((Ptr) (&halCfg.bysOutCfg[strmId]),
                                (const void *) (&pCfg->bysOutCfg[i]),
                                sizeof(vpsissCalBysOut_t));

                halCfg.isBysInCfgValid[strmId] = halCfg.bysInEnable[strmId] =
                                                     pCfg->bysInEnable[i];
                if((uint32_t)TRUE == halCfg.isBysInCfgValid[strmId])
                {
                    pInstObj->streamIdToVcMap[strmId] = CAL_BYS_IN_POSITION;
                }

                halCfg.isVportCfgValid[strmId] = pCfg->isVportCfgValid[i];
                BspUtils_memcpy((Ptr) (&halCfg.vportCfg[strmId]),
                                (const void *) (&pCfg->vportCfg[i]),
                                sizeof(vpsissCalVPort_t));

                halCfg.writeToMem[strmId] = pCfg->writeToMem[i];

                halCfg.numCPortId++;
            }
            else if(VCORE_CAL_STREAM_MODE_ISP == pHndlObj->streamMode[strmId])
            {
                halCfg.otfPrms = pCfg->pIspArgs;
                retVal         = FVID2_SOK;
            }
            else
            {
                break;
            }
        }
    }

    if(FVID2_SOK == retVal)
    {
        retVal = vcoreCaptSetParams((VpsCore_Handle)pHndlObj, &halCfg, NULL);
    }

    return(retVal);
}

static int32_t vcoreIssPrimeStartCal(vpscoreissCaptCalHndlObj_t *pHndlObj,
                                     void                       *argsNotUsed)
{
    int32_t  retVal = FVID2_SOK;
    VpsCore_Frame           *newFrame = NULL;
    vpscoreissCaptInstObj_t *pInstObj = NULL;
    isshalCalDmaVcCfg_t   *pDmaVcCfg  = NULL;
    uint32_t i, cookie;

    /* Check for NULL done by the caller, just assert */
    GT_assert(VpsIssCalCoreTrace, (NULL != pHndlObj));
    pInstObj = pHndlObj->pInstObj;
    GT_assert(VpsIssCalCoreTrace, (NULL != pInstObj));
    pDmaVcCfg = &pHndlObj->calDmaVcCfg;
    GT_assert(VpsIssCalCoreTrace, (NULL != pDmaVcCfg));

    /* . Only for streams that CAL / ISP would write
        .. Request a frame
        .. Program the frame
       . Start CAL
        */
    for(i = 0; ((i < pHndlObj->numStreams) && (FVID2_SOK == retVal)); i++)
    {
        if((VCORE_CAL_STREAM_MODE_CAL_WRITE == pHndlObj->streamMode[i]) ||
           ((VCORE_CAL_STREAM_MODE_ISP == pHndlObj->streamMode[i])))
        {
            newFrame = pHndlObj->openPrms.reqFrmCb(pHndlObj->openPrms.drvData,
                                                   i, 0x0);
            if(NULL == newFrame)
            {
                retVal = FVID2_EAGAIN;
            }
            if(FVID2_SOK == retVal)
            {
                retVal = vcoreCaptProgBuf(pHndlObj, newFrame, (uint32_t) FALSE);
            }
            if(VCORE_CAL_STREAM_MODE_CAL_WRITE == pHndlObj->streamMode[i])
            {
                pDmaVcCfg->wrDmaCfg[i].mode    = VPS_HAL_ISS_CAL_DMA_WR_CONST;
                pHndlObj->firstDmaStartIntr[i] = (uint32_t)TRUE;
#ifdef PLATFORM_SIM
                pDmaVcCfg->wrDmaCfg[i].mode = VPS_HAL_ISS_CAL_DMA_WR_CONST;
#endif

                cookie = BspOsal_disableInterrupt();
                if(NULL != pHndlObj->emDmaStartHndl[i])
                {
                    retVal = Vps_calEmEnable(pHndlObj->emDmaStartHndl[i]);
                }
                if((NULL != pHndlObj->emDmaCmpltHndl[i]) &&
                    (FVID2_SOK == retVal))
                {
                    retVal = Vps_calEmEnable(pHndlObj->emDmaCmpltHndl[i]);
                }
                if((TRUE == pHndlObj->isSubFrameCfgValid) &&
                   (FVID2_SOK == retVal))
                {
                    retVal = Vps_calEmEnable(pHndlObj->emSubFrmCmpltHndl);
                }
                BspOsal_restoreInterrupt(cookie);
            }
        }
    }

    if(FVID2_SOK == retVal)
    {
        retVal = VpsHal_isscalCaptureStart(pInstObj->calHalHandle, pDmaVcCfg);
    }

    return (retVal);
}

static void vcoreCaptErrCb(const UInt32 *event,
                           UInt32        numEvents,
                           Ptr           arg)
{
    /* The top level CAL interrupt is the same and same priority, so this
        ISR WILL not be pre-empted. Hence its OK to have local static */
    static uint32_t          localEvent[VPS_ISS_CAL_MAX_ERROR_INTERRUPTS];
    uint32_t                 idx, vc;
    int32_t                  retVal;
    vpscoreissCaptErrObj_t  *pErrObj = (vpscoreissCaptErrObj_t *) arg;

    if(((NULL == pErrObj) || (NULL == event)) || (NULL == pErrObj->pInstObj) ||
       (VPS_ISS_CAL_MAX_ERROR_INTERRUPTS <= numEvents))
    {
        retVal = FVID2_EFAIL;
    }
    else
    {
        retVal = FVID2_SOK;
    }

    for(idx = 0U; ((idx < numEvents) && (FVID2_SOK == retVal)); idx++)
    {
/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'event'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 *
 * In this particular case, the event manager has allocated enough memory
 *  to hold numEvents
 */
        localEvent[idx] = event[idx];
        if(VPS_CAL_CSI2_PPI_CMPLXIO_FIFO_OVR == localEvent[idx])
        {
            /* All virtual channels requires to know about this overflow
                as we cannot determine which VC caused this */
            for(vc = 0U; vc < CAL_MAX_VIRTUAL_CHAN; vc++)
            {
                pErrObj->fifoOverFlow[vc] = (uint32_t)TRUE;
            }
        }
        else if(VPS_CAL_CSI2_PPI_CMPLXIO_ECC_NO_CORRECTION == localEvent[idx])
        {
            for(vc = 0U; vc < CAL_MAX_VIRTUAL_CHAN; vc++)
            {
                pErrObj->eccCouldNotCorrect[vc] = (uint32_t)TRUE;
            }
        }
        else if(CAL_EM_EVENT_BYSIN_OVR == localEvent[idx])
        {
            pErrObj->fifoOverFlow[CAL_BYS_IN_POSITION] = (uint32_t)TRUE;
            localEvent[idx] = VPS_CAL_BYSIN_OVR;
        }
        else
        {
            if(((VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC1 == localEvent[idx]) ||
                (VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC2 == localEvent[idx])) ||
               ((VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC3 == localEvent[idx]) ||
                (VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC4 == localEvent[idx])))
            {
                vc = (localEvent[idx] - VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC1)
                     / 8U;
                pErrObj->crcMisMatch[vc] = (uint32_t)TRUE;
            }

            if(((VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC1 == localEvent[idx]) ||
                (VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC2 == localEvent[idx])) ||
               ((VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC3 == localEvent[idx]) ||
                (VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC4 == localEvent[idx])))
            {
                vc = (localEvent[idx] - VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC1)
                     / 8U;
                pErrObj->eccCorrected[vc] = (uint32_t)TRUE;
            }
        }
    }

    if(FVID2_SOK == retVal)
    {
        if(NULL != pErrObj->errCfg.appCb)
        {
            pErrObj->errCfg.appCb(&localEvent[0U], numEvents,
                                   pErrObj->errCfg.pAppCbArgs);
        }
    }
    return;
}

static int32_t vcoreCaptCfgSubEof(
                                vpscoreissCaptCalHndlObj_t *pHndlObj,
                                const vcoreissCaptSubFrameCfg_t *pSubFrmCfg)
{
    UInt32 streamId, idx, xLineIntCnt, cportId;
    int32_t retVal = FVID2_EBADARGS;
    vpscoreissCaptInstObj_t *pInstObj = pHndlObj->pInstObj;

    /*  Steps
        1. Error Checks
        2. Set the CAL for Line event notification
        3. Register Line event and end-of-frame interrupts handlers
    */
    /* Step 1. Error Checks */
    /*
        1. Ensure valid stream id
        2. Ensure x line interrupt is being enabled for only 1 vc/stream
    */
    if ((NULL != pSubFrmCfg->appCb) &&
        (VPS_ISS_CAL_MAX_STREAMS > pSubFrmCfg->numStream))
    {
        retVal = FVID2_SOK;
        xLineIntCnt = 0U;
        for (idx = 0U;
            ((idx < pSubFrmCfg->numStream) && (FVID2_SOK == retVal)); idx++)
        {
            streamId = pSubFrmCfg->streamId[idx];
            if (VPS_ISS_CAL_MAX_STREAMS <= streamId)
            {
                retVal = FVID2_EBADARGS;
            }
            else if (VCORE_CAL_STREAM_MODE_CAL_WRITE !=
                                                pHndlObj->streamMode[streamId])
            {
                retVal = FVID2_EBADARGS;
            }
            else
            {
                if (0U != pSubFrmCfg->notifyAfterFirstXLines[idx])
                {
                    xLineIntCnt++;
                    if (pInstObj->calCfg.streamFmt[streamId].height <
                            pSubFrmCfg->notifyAfterFirstXLines[idx])
                    {
                        retVal = FVID2_EBADARGS;
                    }

                    if (VPS_ISS_CAL_MAX_X_LINE_MONITOR_CNT < xLineIntCnt)
                    {
                        retVal = FVID2_EBADARGS;
                    }
                }
            }
        }
    }
    /* Step 2. Set the CAL for Line event notification */
    if (FVID2_SOK == retVal)
    {
        pInstObj->lineEventCfg.numCPortId = 0U;
        for (idx = 0U;
            ((idx < pSubFrmCfg->numStream) && (FVID2_SOK == retVal)); idx++)
        {
            xLineIntCnt = pSubFrmCfg->notifyAfterFirstXLines[idx];
            if (0U != xLineIntCnt)
            {
                streamId = pSubFrmCfg->streamId[idx];
                cportId = pHndlObj->allocatedRes[streamId].cport;

                /* Always, 0, as we can enable line event only for 1 channel
                    and it should be present at first entry */
                pInstObj->lineEventCfg.cportId[0U] = cportId;

                pInstObj->lineEventCfg.lineNumber[cportId] = xLineIntCnt;
                pInstObj->lineEventCfg.numCPortId++;
            }
        }

        retVal = VpsHal_isscalControl(
                        pInstObj->calHalHandle,
                        VPS_HAL_ISS_IOCTL_CAL_LINE_EVENT_CFG,
                        (Ptr) &pInstObj->lineEventCfg, NULL);
    }
    /* Step 3. Register Line event and end-of-frame interrupts handlers */
    if (FVID2_SOK == retVal)
    {
        retVal = vcoreCaptRegisterSubEofIsr(pHndlObj, pSubFrmCfg);
        if (FVID2_SOK == retVal)
        {
            BspUtils_memcpy((Ptr) (&pHndlObj->subFrameCfg),
                            (const void *) (pSubFrmCfg),
                            sizeof(vcoreissCaptSubFrameCfg_t));
        }
    }

    return (retVal);
}

static int32_t vcoreCaptRegisterSubEofIsr(
                                vpscoreissCaptCalHndlObj_t *pHndlObj,
                                const vcoreissCaptSubFrameCfg_t *pSubFrmCfg)
{
    UInt32 streamId, idx;
    int32_t retVal = FVID2_SOK;
    vpscoreissCaptInstObj_t *pInstObj = NULL;
    UInt32 lineNumEvent = (UInt32) IEM_CAL_EVENT_LINE_NUMBER;
    /*  Register ISR's and don't yet enable them (enable at start) */
    pInstObj = pHndlObj->pInstObj;

    for (idx = 0U;
        ((idx < pSubFrmCfg->numStream) && (FVID2_SOK == retVal)); idx++)
    {
        streamId = pSubFrmCfg->streamId[idx];

        if (TRUE == pSubFrmCfg->notifyAfterEndOfFrame[idx])
        {
            pHndlObj->emDmaCmpltHndl[streamId] = Vps_calEmRegister(
                pInstObj->initPrms.irqNum,
                CAL_EM_EG_CAL,
                &pHndlObj->dmaCmpltEvent[streamId],
                1U,
                CAL_EM_PRIORITY4,
                vcoreCaptDmaCmpltCb,
                (Ptr) pHndlObj);

            if(NULL == pHndlObj->emDmaCmpltHndl[streamId])
            {
                retVal = FVID2_EFAIL;
            }
        }

        /* Need not check if multiple streams are enabled for X line
            callback, as the caller has already checked this */
        if (0U != pSubFrmCfg->notifyAfterFirstXLines[idx])
        {
            pHndlObj->emSubFrmCmpltHndl = Vps_calEmRegister(
                pInstObj->initPrms.irqNum,
                CAL_EM_EG_CAL,
                &lineNumEvent,
                1U,
                CAL_EM_PRIORITY4,
                vcoreCaptXlineCmpltCb,
                (Ptr) pHndlObj);
            if(NULL == pHndlObj->emSubFrmCmpltHndl)
            {
                retVal = FVID2_EFAIL;
            }
            else
            {
                pHndlObj->isSubFrameCfgValid = TRUE;
            }
        }

    }
    if (FVID2_SOK == retVal)
    {
        pHndlObj->subFrameCfg.appCb = pSubFrmCfg->appCb;
        pHndlObj->subFrameCfg.pAppCbArgs = pSubFrmCfg->pAppCbArgs;
    }

    return retVal;
}

static int32_t vcoreCaptRegisterErrorIsr(const vpscoreissCaptCalHndlObj_t
                                                                   *pHndlObj,
                                         const vpsissCalErrorCfg_t *pErrCfg)
{
    uint32_t idx, cmplxIoId;
    int32_t  rtnVal = FVID2_SOK;
    vpscoreissCaptInstObj_t *pInstObj;
    vpscoreissCaptErrObj_t *pErrObj;
    calemEventGroup_t eventGrp;

    GT_assert(VpsIssCalCoreTrace, (NULL != pHndlObj));
    pInstObj = pHndlObj->pInstObj;
    GT_assert(VpsIssCalCoreTrace, (NULL != pInstObj));
    GT_assert(VpsIssCalCoreTrace, (NULL != pErrCfg));

    /*
        . Check for errors in the configuration, including double registration
        . Register ISR
    */
    if ((VPS_ISS_CAL_MAX_ERROR_INTERRUPTS <= pErrCfg->numErrorsToMonitor) ||
        (VPS_ISS_CAL_MAX_CMPLXIO_INST <= pErrCfg->cmplxIoId))
    {
        rtnVal = FVID2_EBADARGS;
    }
    else
    {
        cmplxIoId = pErrCfg->cmplxIoId;

        /* Check for multiple registration and valid errors */
        if(NULL != pInstObj->errObj[cmplxIoId].emErrorHndl)
        {
            rtnVal = FVID2_EDEVICE_INUSE;
        }
    }

    for(idx = 0U; ((idx < pErrCfg->numErrorsToMonitor) &&
                   (FVID2_SOK == rtnVal)); idx++)
    {
        if((VPS_CAL_CSI2_PPI_CMPLXIO_ERRSOTHS1 == pErrCfg->errSrc[idx]) ||
           (VPS_CAL_CSI2_FORCE_INT == pErrCfg->errSrc[idx]))
        {
            rtnVal = FVID2_EOUT_OF_RANGE;
        }
    }

    if(FVID2_SOK == rtnVal)
    {
        pErrObj = &pInstObj->errObj[cmplxIoId];

        /* Initialize Error Object */
        pErrObj->cmplxIoId = cmplxIoId;
        pErrObj->pInstObj = pInstObj;

        BspUtils_memcpy((Ptr) (&pErrObj->errCfg),
                        (const void *) (pErrCfg),
                        sizeof(vpsissCalErrorCfg_t));
        for(idx = 0U; idx < pErrObj->errCfg.numErrorsToMonitor; idx++)
        {
            if(VPS_CAL_BYSIN_OVR == pErrObj->errCfg.errSrc[idx])
            {
                pErrObj->errCfg.errSrc[idx] =
                    (vpsissCalErrorSource_t)CAL_EM_EVENT_BYSIN_OVR;
            }
        }
/* MISRA.CAST.PTR
 * Rule 11.4: Cast between a pointer to object type and a different pointer to
 * object type
 * Name 'pInstObj->errCfg.errSrc'
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Error source is an enum, which is cast to uint32, this will not be an issue
 *  as enum values are positive integers only in this case
 */
        eventGrp = CAL_EM_EG_CAL_PPI0_CSI2;
        if (1U == cmplxIoId)
        {
            eventGrp = CAL_EM_EG_CAL_PPI1_CSI2;
        }

        pErrObj->emErrorHndl = Vps_calEmRegister(
            pInstObj->initPrms.irqNum,
            eventGrp,
            (const uint32_t *)
            &pErrObj->errCfg.errSrc[0U],
            pErrObj->errCfg.numErrorsToMonitor,
            CAL_EM_PRIORITY1,
            vcoreCaptErrCb,
            (Ptr) pErrObj);
        if(NULL == pErrObj->emErrorHndl)
        {
            rtnVal = FVID2_EFAIL;
        }
    }
    return (rtnVal);
}

