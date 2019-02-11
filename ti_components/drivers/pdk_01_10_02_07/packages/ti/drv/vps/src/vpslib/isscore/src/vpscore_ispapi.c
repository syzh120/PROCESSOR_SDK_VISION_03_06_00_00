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
 *  \file vpscore_ispapi.c
 *
 *  \brief This file implements ISP M2M core.
 *
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

#include <ti/drv/vps/src/vpslib/common/iem_evtmgr.h>
#include <ti/drv/vps/src/vpslib/common/irm_resrcMgr.h>
#include <ti/drv/vps/src/vpslib/isscore/vpscore_m2m.h>
#include <ti/drv/vps/src/vpslib/isscore/src/vpscore_isppriv.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/src/vpslib/isscore/src/vpscore_isscommon.h>

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */
#define VPS_CORE_ISS_M2M_420SP_NONE         (0x0U)
/**< When input is frame is not 420 SP, or when LUMA / CHROMA is processed */
#define VPS_CORE_ISS_M2M_420SP_LUMA         (0x1U)
/**< When input frame is 402SP and LUMA scaling is being done */
#define VPS_CORE_ISS_M2M_420SP_CHROMA       (0x2U)
/**< When input frame is 402SP and CHROMA scaling is being done */
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* Forward Declaration */
typedef struct vpscoreissM2mHandleObj vpscoreissM2mHandleObj_t;

/** \brief ISS M2M driver instance object.
 *         One instance is for one independent ISP path.
 *         Instance object keeps/stores instance global information
 *         like number of open count, init parameters etc.
 */
typedef struct vpscoreissM2mInstObj
{
    uint32_t                  isInit;
    /**< Flag to indicate whether instance is inited or not */
    vcoreissM2mDrvInstId_t    instId;
    /**< Id of this instance */
    isshalissStartModuleFxn   startModuleFxn[VPS_ISS_ISP_MAX_MODULE];
    /**< Array of function pointer to the start/stop functions
     *   of the modules */
    vcoreIspInitParams_t      initPrms;
    /**< Init Parameters stored in the instance object */
    BspOsal_SemHandle         lockSem;
    /**< Semaphore for protection */
    uint32_t                  isRequestActive;
    /**< Flag to indicate if there is any active request,
     *   this is used to protect multiple request submission,
     *   core allows only one request to be processed at a time */
    uint32_t                  openCnt;
    /**< Number of open for this instance */
    vpscoreissM2mHandleObj_t *activeHandleObj;
    /**< Pointer to handle object, for which request is submitted */
    vpsissCaptureBlocks_t     captRes;
    /**< Cal Resource structure contains Cportid and vport allocated */
    uint32_t                  curr420State;
    /**< Applicable when processing YUV420 SP frames only. We support re-sizing
            of YUV420 frames in 2 step process, step 1, process luma & step 2
            process chroma. This variable indicate which step is completed.
            Not applicable for other input data type */
    VpsCore_Frame           **frm;
    /**< Used only when input format is YUV420 SP.
            Temporary place holder to hold frame buffers supplied by apps */
    uint32_t                  isGlbceInitDone;
    /**< Flag used to ensure GLBCE initialization sequence is done only once.
            No harm is doing it multiple time though */
} vpscoreissM2mInstObj_t;

/** \brief ISS M2M driver handle object.
 *         One handle object for one open of a given instance.
 *         Handle object keeps/stores individual module parameters for
 *         this handle.
 */
struct vpscoreissM2mHandleObj
{
    uint32_t                isAllocated;
    /**< Flag indicates whether this handle object is allocated or not */
    uint32_t                isModuleReq[VPS_ISS_ISP_MAX_MODULE];
    /**< modules which will opened for this instance,
     *   TRUE: module will be used for this instance
     *   FALSE: module will not be used and hence will not be opened
     *   here #vpscodecalispModuleId_t is used as an index into this array
     *   Depending on the instance, some of the modules are must,
     *   for example, CAL input is required for all the instances.
     *   But some of the modules can be optional like glbce, so these modules
     *   may not be required and so may not openened, saving the power/clock */
    VpsHal_Handle           calHalHandle;
    /**< Handle to the CAL Hal */
    VpsCore_OpenPrms        openPrms;
    /**< Core Open Parameters containing callbacks
     *   for requesting a new frame and for submitting completed frame
     *   to the upper layer
     *   It also has callback to mark completion of the frame */
    isshalCalCfg_t          calCfg;
    /**< Structure containing CAL configuration */
    isshalCalDmaVcCfg_t     calDrvCfg;
    /**< Configuration expected to updated by core / driver */
    isshalGlbceSwitchCtrl_t glbceSwitchNsf3Input;
    /**< Nsf3 input path in GLBCE Switch */
    isshalGlbceSwitchCtrl_t glbceSwitchGlbceInput;
    /**< Glbce input path in GLBCE Switch */
    isshalIpipeifRtCfg_t    ipipeifRtCfg;
    /**< Ipipeif RunTime configuration, used to enable/disable WDR merging */
    isshalIpipeifFrameCfg_t ipipeifFrmCfg;
    /**< IPIEPIF Frame Configuration */
    isshalVMuxSrcPorts_t    vmuxSrc;
    /**< Video Mux Source */
    isshalVMuxSinkPorts_t   vmuxSink;
    /**< Video Mux Sink */
    vcoreIspHandleObj_t    *hIspObj;
    /**< Handle to ISP Object, ISP portion will be configured/taken
         care by the ISP layer */
    vpscoreissM2mInstObj_t *instObj;
    /**< Pointer to the instance object */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*  \brief Frame Completion callback, called by event manager
 *
 *  \param event       Arrays of events which occured
 *  \param numEvents   number of valid entries in event
 *  \param arg         Not used
 *
 */
static void vcoreIssM2mFrmCmplCb(const UInt32 *event,
                                UInt32        numEvents,
                                Ptr           arg);

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif

/*  \brief Function to get the core properties
 *
 *  \param instObj     Pointer to instance Object
 *  \param property    Pointer to propery, out parameter
 *
 *  \return            return FVID2_SOK on success
 *                     error code on fail
 */
Int32 vcoreIssM2mGetProperty(VpsCore_Inst      instObj,
                             VpsCore_Property *property);

/*  \brief Opens the Core, in turn, opens the required hals, sets the defaults
 *         parameters
 *
 *  \param inst        Pointer to instance id
 *  \param openPrms    Core open parameters containing get/put frame
 *                     function pointers
 *  \param coreOpenPrms Core Specific Open Parameter, contains list of
 *                     modules required for this instance
 *  \param coreReturnPrms Returns Params
 *
 *  \return            Valid core handle on success
 *                     NULL on Failure
 */
VpsCore_Handle vcoreIssM2mOpen(VpsCore_Inst            inst,
                               const VpsCore_OpenPrms *openPrms,
                               const void             *coreOpenPrms,
                               void                   *coreReturnPrms);

/*  \brief Closes the core handle, in turn, closes the hals, cleans
 *         out the handle
 *
 *  \param handle      core handle
 *
 *  \return            FVID2_SOK on success
 *                     FVID2 error code on failure
 */
int32_t vcoreIssM2mClose(VpsCore_Handle handle);

/*  \brief Sets the parameters, used to set the input frame size/frame format,
 *         enable/disable output streams, enable/disable specific
 *         modules like nsf3/glbce. This call resets many of the
 *         default parameters, so they need to be changed after this call
 *         to the required configuration
 *
 *  \param handle      core handle
 *  \param params      Pointer to the parameters
 *  \param subFrmRetPrms Return parameters
 *
 *  \return            FVID2_SOK on success
 *                     FVID2 error code on failure
 */
int32_t vcoreIssM2mSetParams(VpsCore_Handle handle,
                             const void *params,
                             void       *args);

/*  \brief Get the current parameters
 *
 *  \param handle      core handle
 *  \param params      Pointer to the parameters
 *
 *  \return            FVID2_SOK on success
 *                     FVID2 error code on failure
 */
int32_t vcoreIssM2mGetParams(VpsCore_Handle handle,
                             void          *params);

/*  \brief Function to get/set control commands
 *
 *  \param handle      core handle
 *  \param cmd         Command ID
 *  \param cmdArgs     Command Specific Arguments
 *  \param drvArgs     Driver specific arguments
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreIssM2mControl(VpsCore_Handle handle,
                           uint32_t       cmd,
                           void          *appArgs,
                           void          *drvArgs);

/*  \brief Function to set the buffer addresses for all enabled outputs
 *
 *  \param handle      core handle
 *  \param frm         list of frame pointers containing buffer addresses
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreIssM2mPutFrames(VpsCore_Handle  handle,
                             VpsCore_Frame **frm);

/*  \brief Function to put the lock
 *
 *  \param instObj     Pointer to instance object
 *
 *  \return            None
 */
static void IspLock(vpscoreissM2mInstObj_t *instObj);

/*  \brief Function to release the lock
 *
 *  \param instObj     Pointer to instance object
 *
 *  \return            None
 */
static void IspUnLock(vpscoreissM2mInstObj_t *instObj);

/*  \brief Function to allocate the handle object from the global
 *         pool of handle objects
 *
 *  \return            pointer to allocated handle object
 *                     NULL if there is no free handle object
 */
static vpscoreissM2mHandleObj_t *IssM2mAllocHandleObj(void);

/*  \brief Function to free up allocated handle object
 *
 *  \param hObj        Pointer to handle object
 *
 *  \return            None
 */
static void IssM2mFreeHandleObj(const vpscoreissM2mHandleObj_t *hObj);

/*  \brief Function to connect CAL Bys output to GLBCE through GLBCE mux.
 *         This function is used while performing GLBCE startup sequence
 *
 *  \param hObj        Pointer to handle object
 *  \param flag        TRUE connects Bys output to GBLCE
 *                     FALSE disconnects them
 *
 *  \return            FVID2_SOK on success
 *                     FVID2 error code on failure
 */
static int32_t vcoreIssM2mSetVmuxGlbce(const vpscoreissM2mHandleObj_t *hObj,
                                       uint32_t                       flag);

/*  \brief Function to connect CAL Vport out to ISP using Video Mux
 *
 *  \param hObj        Pointer to handle object
 *
 *  \return            FVID2_SOK on success
 *                     FVID2 error code on failure
 */
static int32_t vcoreIssM2mSetVmuxIspSrcAsCalBVp(
    vpscoreissM2mHandleObj_t *hObj,
    uint32_t
    isConnected);

/*  \brief Function to set the GLBCE mux for GLBCE and NSF3 module
 *         depending on whether GLBCE and NSF3 are enabled or not in parameters
 *         It also enables the DPC module before NSF3
 *         It also sets the VP1 and VP2 configurations
 *
 *  \param hObj        Pointer to handle object
 *
 *  \return            FVID2_SOK on success
 *                     FVID2 error code on failure
 */
static void vcoreIssM2mSetGlbceMux(const vpscoreissM2mHandleObj_t *hObj);

/*  \brief Function to set the IPIPEIF run time configuration,
 *         these configuration is mainly source1 and source2 mux
 *         value. Depending on the path selected, this function sets
 *         these muxes.
 *
 *  \param hObj        Pointer to handle object
 *
 *  \return            FVID2_SOK on success
 *                     FVID2 error code on failure
 */
static void vcoreIssM2mSetIpipeifMux(vpscoreissM2mHandleObj_t *hObj);

/*  \brief Function to configure ISIF.
 *         Special handling required for VFDC update.
 *
 *  \param hObj        Pointer to handle object
 *
 *  \return            FVID2_SOK on success
 *                     FVID2 error code on failure
 */
static int32_t vcoreIssM2mCfgIsif(vpscoreissM2mHandleObj_t *hObj,
                                  uint32_t                  cmd,
                                  void                     *appArgs,
                                  void                     *drvArgs);

/** \brief To programe VFDC defect pixel table, the pixel clock is required.
 *          This function configures CAL for dummy read and sets the free run
 *          of pixel clock on Vport.
 *
 *  \param  hObj - handle object
 *  \param  freeRunMode - configure the free run mode of VPORT.
 *
 *  \return FVID2_SOK, if everything went well. Appropriate error code otherwise
 *
 */
static int32_t vcoreIssM2mIsifVfdcDummyCalRead(
    vpscoreissM2mHandleObj_t *hObj,
    uint32_t
    freeRunMode);

/** \brief Function to prepare the CAL config required for WDR pass1 / pass2
 *
 *  \param  hObj
 *
 *  \return FVID2_SOK, if everything went well. Appropriate error code otherwise
 *
 */
static int32_t vcoreIssM2mCalMakeCfg(vpscoreissM2mHandleObj_t *hObj,
                                     const vpsissIspParams_t  *prms);

/** \brief Function to configure for chroma scaling in YUV420 resizing mode.
 *
 *  \param  hIspObj
 *  \param  instObj
 *
 *  \return FVID2_SOK, if everything went well. Appropriate error code otherwise
 *
 */
static int32_t vcoreIssM2mProcYuv420SPChroma(vcoreIspHandleObj_t    *hIspObj,
                                        const vpscoreissM2mInstObj_t *instObj);

/** \brief Configure ISP with update configuration. Following modules are
 *          Updated as below
 *  \param  hIspObj
 *  \param  instObj
 *
 *  \return FVID2_SOK, if everything went well. Appropriate error code otherwise
 *
 *  CAL Read configuration - as the width of read could vary
 *  IPIPE IF, NSF3, GLBCE - Input frame size is updated
 *  ISIF - Source configuration - as i/f width, msbPos, frame size could change
 *  IPIPE - Source configuration - as input path, frame size
 */
static int32_t vcoreIssM2mSetSrcSize(vpscoreissM2mHandleObj_t *hObj);

/** \brief Enables / disables processing sub-blocks with in each sub blocks.
 *          Depending on the configuration specified in the handle.
 *          Right now, for WDR flow & ReSizer flow, we update only IPIPE IFs
 *          companding / decompanding, saturation is handled.
 *
 *  \param  hObj
 *
 *  \return FVID2_SOK, if everything went well. Appropriate error code otherwise
 *
 */
static int32_t vcoreIssM2mEnDisProc(const vpscoreissM2mHandleObj_t *hObj);

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * Instance Objects
 */
static vpscoreissM2mInstObj_t   gIssM2mInstObjs[VPSCORE_ISS_M2M_MAX_INST] =
{
    {FALSE}
};

/**
 * Pool of Handle Objects
 */
static vpscoreissM2mHandleObj_t gIssM2mHandleObjs
[VPSCORE_ISS_M2M_ISP_MAX_HANDLES];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/** API to return the property of the instance
 */
Int32 vcoreIssM2mGetProperty(VpsCore_Inst      instObj,
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
const VpsCore_Ops *VpsCore_issM2mGetCoreOps(void)
{
    /** \brief ISS path core function pointer. */
    static const VpsCore_Ops        gIssCoreOps =
    {
        &vcoreIssM2mGetProperty, /* Get property */
        &vcoreIssM2mOpen,        /* Open function */
        &vcoreIssM2mClose,       /* Close function */
        &vcoreIssM2mSetParams,   /* Set Params */
        &vcoreIssM2mGetParams,   /* Get Params */
        &vcoreIssM2mControl,     /* Control */
        NULL,                    /* Start */
        NULL,                    /* Stop */
        NULL,                    /* Process */
        NULL,                    /* Core prog Buffer */
        &vcoreIssM2mPutFrames,   /* Update the buffer and start */
        NULL,                    /* getFrames */
        NULL                     /* getErrorStat */
    };

    return (&gIssCoreOps);
}

/**
 *  A Valid pointer on success else a NULL pointer.
 */
VpsCore_Inst VpsCore_issM2mGetCoreInstObj(vcoreissM2mDrvInstId_t instId)
{
    VpsCore_Inst status = NULL;
    if(instId < VPSCORE_ISS_M2M_MAX_INST)
    {
        status = (VpsCore_Inst)&gIssM2mInstObjs[instId];
    }
    return (status);
}

/** Initializes the data structures as per the init parameters,
 *  Also initializes the hal as per the driver instance
 */
int32_t VpsCore_issM2mInit(
    uint32_t                    numInst,
    const vcoreIspInitParams_t *initPrms,
    Ptr                         arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t instCnt;
    uint32_t hCnt;
    uint32_t stepStatus;
    vpscoreissM2mInstObj_t     *instObj = NULL;
    VpsLib_PlatformData        *platData;
    const vpshalissIspPlatformData_t *halPlt;

    /* Check for the null pointer */
    GT_assert(VpsIssCoreTrace, (NULL != initPrms));
    GT_assert(VpsIssCoreTrace, (NULL != initPrms->halPlatformData));
    GT_assert(VpsIssCoreTrace, (VPSCORE_ISS_M2M_MAX_INST >= numInst));

    for(instCnt = 0U; ((instCnt < numInst) && (FVID2_SOK == status)); instCnt++)
    {
        GT_assert(VpsIssCoreTrace,
                  (VPSCORE_ISS_M2M_MAX_INST >= initPrms->instId));

        instObj = &gIssM2mInstObjs[instCnt];

        if((uint32_t)FALSE == instObj->isInit)
        {
            BspUtils_memset(
                instObj,
                0x0,
                sizeof(vpscoreissM2mInstObj_t));

            instObj->openCnt = 0U;
            instObj->instId  = initPrms->instId;

            /* Create instance Semaphore for protecting instance parameters */
            instObj->lockSem = BspOsal_semCreate(1, TRUE);
            if(NULL == instObj->lockSem)
            {
/* UNREACH.GEN
 * Code Un Reachable
 * Name 'instObj->lockSem', cannot be NULL
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes,
 * it will not be unreachable
 */
                GT_0trace(VpsIssCoreTrace, GT_ERR, "Sem create failed!!\r\n");
                status = FVID2_EALLOC;
            }

            platData = (VpsLib_PlatformData *) initPrms->halPlatformData;
            if(NULL == platData)
            {
                status = FVID2_EBADARGS;
            }
            else
            {
/* MISRA.CAST.PTR
 * Rule 11.4: Cast between a pointer to object type and a different pointer to
 * object type
 * Name 'halPlt'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointers to different layer's handles are stored as void*.
 */
                halPlt = (const vpshalissIspPlatformData_t *)platData->ispHal;
                if(NULL == halPlt)
                {
                    status = FVID2_EBADARGS;
                }
            }

            /* Initialize HAL */
            if(FVID2_SOK == status)
            {
                status = VpsHal_issctrlInit(halPlt->issCtrlInitPrms, NULL);
            }

            stepStatus = 0x0;
            /* Power on the sub-modules, so that HAL can access the registers */
            if(FVID2_SOK == status)
            {
                stepStatus = 0x4U;
                status     = VpsHal_issPowerCtrl(
                    (isshalSubModules_t) initPrms->subModules,
                    (uint32_t) TRUE);
            }

            if(FVID2_SOK == status)
            {
                stepStatus = 0x1U;
                status     = VpsHal_isscalInit(
                    halPlt->numCalInst,
                    halPlt->calInstPrms,
                    NULL);
            }
            if(FVID2_SOK == status)
            {
                stepStatus = 0x2U;
                status     = vcoreIspInit(platData);
            }

            if(FVID2_SOK != status)
            {
                if(0x4U == (stepStatus & 0x4U))
                {
                    vcoreIspDeInit(NULL);
                }
                if(0x2U == (stepStatus & 0x2U))
                {
                    VpsHal_isscalDeInit(NULL);
                }
                if(0x1U == (stepStatus & 0x1U))
                {
                    VpsHal_issctrlDeInit(NULL);
                }

                break;
            }
            else
            {
                /* Copy the params */
                BspUtils_memcpy(
                    &instObj->initPrms,
                    initPrms,
                    sizeof(vcoreIspInitParams_t));
                instObj->isInit          = (uint32_t) TRUE;
                instObj->isGlbceInitDone = (uint32_t) FALSE;
            }

            instObj->curr420State = VPS_CORE_ISS_M2M_420SP_NONE;
/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'initPrms'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 */
            initPrms++;
        }
    }

    if(FVID2_SOK == status)
    {
        for(hCnt = 0U; hCnt < VPSCORE_ISS_M2M_ISP_MAX_HANDLES; hCnt++)
        {
            BspUtils_memset(
                &gIssM2mHandleObjs[hCnt],
                0x0,
                sizeof(vpscoreissM2mHandleObj_t));
            gIssM2mHandleObjs[hCnt].isAllocated = (uint32_t) FALSE;
        }
    }

    return (status);
}

/* Function to de ininitialize all instances, it also deinitializes the hals */
int32_t VpsCore_issM2mDeInit(Ptr arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t instCnt, hCnt;
    vpscoreissM2mInstObj_t *instObj = NULL;

    for(hCnt = 0U; hCnt < VPSCORE_ISS_M2M_ISP_MAX_HANDLES; hCnt++)
    {
        gIssM2mHandleObjs[hCnt].isAllocated = (uint32_t) FALSE;
    }

    for(instCnt = 0U; instCnt < VPSCORE_ISS_M2M_MAX_INST; instCnt++)
    {
        instObj = &gIssM2mInstObjs[instCnt];
        if(TRUE == instObj->isInit)
        {
            status = VpsHal_isscalDeInit(NULL);
            GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

            /* Deinitialize ISS Control HAL */
            status = VpsHal_issctrlDeInit(NULL);
            GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

            status = vcoreIspDeInit(NULL);
            GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

            /* Disable ISS modules */
            status = VpsHal_issPowerCtrl(
                (isshalSubModules_t) instObj->initPrms.subModules,
                (uint32_t) FALSE);
            GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

            /* Delete the Semaphore created for pool objects */
            if(NULL != instObj->lockSem)
            {
                BspOsal_semDelete(&instObj->lockSem);
                instObj->lockSem = NULL;
            }

            GT_assert(VpsIssCoreTrace, (0U == instObj->openCnt));
        }
    }

    return (status);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* MISRA.PPARAM.NEEDS.CONST
 * MISRAC_2004_Rule_16.7
 * Function parameter 'coreOpenPrms' is not declared as a pointer to const
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Klocwork is not able to analyse pointers which are declared as const and
 *  reporting this issue.This is a false positive.
 */

/** \brief Function to open the a given core */
VpsCore_Handle vcoreIssM2mOpen(VpsCore_Inst            inst,
                               const VpsCore_OpenPrms *openPrms,
                               const void             *coreOpenPrms,
                               void                   *coreReturnPrms)
{
    int32_t                   status = FVID2_SOK;
    uint32_t                  cnt;
    uint32_t                  stepStatus;
    uint32_t                  ispModules;
    uint32_t                  isLockTaken = (uint32_t) FALSE;
    VpsCore_Handle            handle      = NULL;
    vpscoreissM2mInstObj_t   *instObj     = NULL;
    vpscoreissM2mHandleObj_t *hObj        = NULL;
    const vpsissIspOpenParams_t *ispOpenPrms;
    isshalCalOpenParams_t     calOpenPrms;
    isshalCalCfg_t           *calCfg;
    isshalCalDmaVcCfg_t      *calDmaCfg;

    /*
     * Check Arguments
     * Allocate the Handle Object
     * Allocate the ISP resource
     * Open Cal and ISP Hals
     * Register Interrupt
     * Set defaults for CAL and ISP modules
     * Setup VMUX and GLBCE Mux
     */
    stepStatus = 0x0U;
    if((NULL == openPrms) || (NULL == coreOpenPrms) ||
       (NULL == coreReturnPrms))
    {
        status = FVID2_EBADARGS;
    }

    instObj = (vpscoreissM2mInstObj_t *) (inst);

    for(cnt = 0U; ((FVID2_SOK == status) && (cnt < VPSCORE_ISS_M2M_MAX_INST));
        cnt++)
    {
        status = FVID2_EBADARGS;
        if(&gIssM2mInstObjs[cnt] == instObj)
        {
            status = FVID2_SOK;
            break;
        }
    }

    /* Check for Null value */
    if (FVID2_SOK == status)
    {
        if((NULL == instObj) || (FALSE == instObj->isInit))
        {
            status      = FVID2_EFAIL;
            isLockTaken = (uint32_t) FALSE;
        }
    }

    if(FVID2_SOK == status)
    {
        IspLock(instObj);
        isLockTaken = (uint32_t) TRUE;
    }

    /* Allocate Handle Object */
    if(FVID2_SOK == status)
    {
        hObj = IssM2mAllocHandleObj();
        if(NULL == hObj)
        {
            status = FVID2_EALLOC;
        }
        else
        {
            stepStatus = 0x1U;
        }
    }

    /* Allocate the resources required for this path */
    if((FVID2_SOK == status) && (0U == instObj->openCnt))
    {
        stepStatus |= 0x2U;
    }

    /* Allocate the resource for the CAL */
    if((FVID2_SOK == status) && (0U == instObj->openCnt))
    {
        /* We are allocating DPCM decode, encode and pixel packing, even though
             its not used.
             This just to ensure easy resource management. i.e. each sub block
             instance ID allocated / to be used need not be remembered */
        /* Assuming Irm is already initialized */
        status = Irm_allocResource(
            0U,
            (Irm_Modules_t)instObj->initPrms.calIrmId,
            VPS_ISS_CAPT_CAL_SUB_VPORT_ID |
            VPS_ISS_CAPT_CAL_SUB_DMA_RD_ID |
            VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
            VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
            VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
            VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
            VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID,
            &instObj->captRes, (UInt32) IRM_CAL_ALLOC_POLICY_NONE);

        if(FVID2_SOK == status)
        {
            stepStatus |= 0x4U;
        }
    }

    if(FVID2_SOK == status)
    {
        hObj->instObj = instObj;

        /* Open CAL HAL,
         * Assuming CAL HAL is always requires, all supported m2m drivers
         * require cal */
        calOpenPrms.instId = instObj->initPrms.calInstId;
        calOpenPrms.mode   = VPS_HAL_ISS_CAL_MODE_M2M;
        hObj->calHalHandle = VpsHal_isscalOpen(&calOpenPrms, NULL);
        if(NULL == hObj->calHalHandle)
        {
            status = FVID2_EFAIL;
        }
        else
        {
            stepStatus |= 0x8U;
        }
    }

    if(FVID2_SOK == status)
    {
/* MISRA.PPARAM.NEEDS.CONST
 * MISRAC_2004_Rule_16.7
 * Variable 'ispOpenPrms' is not declared as a pointer to const
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Klocwork is not able to analyse pointers which are declared as const and
 *  reporting this issue.This is a false positive.
 */
        ispOpenPrms = (const vpsissIspOpenParams_t *) coreOpenPrms;

        ispModules = 0U;
        for(cnt = 0U; cnt < VPS_ISS_ISP_MAX_MODULE; cnt++)
        {
            hObj->isModuleReq[cnt] = ispOpenPrms->isModuleReq[cnt];

            if(TRUE == hObj->isModuleReq[cnt])
            {
                ispModules |= ((uint32_t)1U << cnt);
            }
        }

        /* Open the All required HALs */
        hObj->hIspObj = vcoreIspOpenHals(
            ispOpenPrms,
            VCORE_ISP_OPEN_MODE_M2M,
            NULL,
            (vpsissIspOpenRetParams_t *)coreReturnPrms,
            NULL);
        if(NULL == hObj->hIspObj)
        {
            status = FVID2_EALLOC;
        }
        else
        {
            stepStatus |= 0x10U;
        }
    }

    /* Register the frame Completion interrupt to the Event manager */
    if((FVID2_SOK == status) && (0U == instObj->openCnt))
    {
        /* ISP uses Resizer End interrupt for the processing, register
           callback for the resizer end interrupt */
        status = vcoreIspRegisterIsr(
            hObj->hIspObj,
            instObj->initPrms.irqNum,
            &vcoreIssM2mFrmCmplCb,
            IEM_PRIORITY4,
            instObj);
        if(FVID2_SOK == status)
        {
            stepStatus |= 0x20U;
        }
    }

    /* Get the default configuration from the HALs */
    if(FVID2_SOK == status)
    {
        /* TOOD: Change this mux sources depending on instances
            currently only one instance is supported which uses
            both the sources */
        hObj->ipipeifRtCfg.inpSrc1  = ISSHAL_IPIPEIF_ISIF_OUT_RAW_VPORT;
        hObj->ipipeifRtCfg.inpSrc2  = ISSHAL_IPIPEIF_IPIPE_OUT_ISIF;
        hObj->glbceSwitchNsf3Input  = ISSHAL_GLBCE_SWITCH_ISP;
        hObj->glbceSwitchGlbceInput = ISSHAL_GLBCE_SWITCH_ISP;

        status = vcoreIspSetDefaultConfig(hObj->hIspObj);
        /* If the Default Configuration does not work, should change
           the default instead of returning null handle */
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }

    if(FVID2_SOK == status)
    {
        /* Set the Cal Configuration */
        calCfg    = &hObj->calCfg;
        calDmaCfg = &hObj->calDrvCfg;

        /* Set the Read DMA configuration */
        calDmaCfg->isRdDmaCfgValid[0U]       = (uint32_t) TRUE;
        calDmaCfg->rdDmaCfg[0U].enable       = (uint32_t) TRUE;
        calDmaCfg->rdDmaCfg[0U].format.width =
            VPSCORE_ISS_M2M_DEF_FRAME_WIDTH;
        calDmaCfg->rdDmaCfg[0U].format.height =
            VPSCORE_ISS_M2M_DEF_FRAME_HEIGHT;
        calDmaCfg->rdDmaCfg[0U].format.dataFormat = FVID2_DF_BAYER_RGGB;
        calDmaCfg->rdDmaCfg[0U].format.bpp        = FVID2_BPP_BITS10;
        calDmaCfg->rdDmaCfg[0U].format.pitch[0U]  =
            VPSCORE_ISS_M2M_DEF_FRAME_WIDTH * 2U;
        calDmaCfg->rdDmaCfg[0U].format.pitch[1U] =
            VPSCORE_ISS_M2M_DEF_FRAME_WIDTH * 2U;
        calDmaCfg->rdDmaCfg[0U].format.pitch[2U] =
            VPSCORE_ISS_M2M_DEF_FRAME_WIDTH * 2U;

        calDmaCfg->rdDmaCfg[0U].pixClock     = 65536; /* Setting the
                                                      max pix clock */
        calDmaCfg->rdDmaCfg[0U].bwLimit      = 0x0U;  /* Setting it to
                                                     minimum value */
        calDmaCfg->rdDmaCfg[0U].ocpTagCnt    = 0xF;
        calDmaCfg->rdDmaCfg[0U].bysOutLeWait = (uint32_t) FALSE;
        calDmaCfg->rdDmaCfg[0U].ySkipMode    = 0;    /* No Line Skip */

        /* Set the Video Port configuration */
        calCfg->isVportCfgValid[0U]   = (uint32_t) TRUE;
        calCfg->vportCfg[0U].enable   = (uint32_t) TRUE;
        calCfg->vportCfg[0U].pixClock = 32768U;

        /* Note: Always Sending 2pixels/cycle as CAL cannot send 1pixel/cycle to
         * VP port */
        calCfg->vportCfg[0U].width = 1U;

        /* TODO: Get this blanking requirement from the HAL */
        calCfg->vportCfg[0U].xBlk    = 6U;
        calCfg->vportCfg[0U].yBlk    = 50U;
        calCfg->vportCfg[0U].rdyThr  = 128U;
        calCfg->vportCfg[0U].fsReset = (uint32_t) TRUE;
                                        /* By default, reset SM on every FS */
        calCfg->vportCfg[0U].freeRun = (uint32_t) FALSE;

        calCfg->pDmaVcCfg = calDmaCfg;

        status = VpsHal_isscalControl(
            hObj->calHalHandle,
            VPS_HAL_ISS_IOCTL_CAL_SETCFG,
            calCfg,
            NULL);

        /* If the Default Configuration does not work, should change
           the default instead of returning null handle */
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }

    if(FVID2_SOK == status)
    {
        /* Set the Path in the Video Mux */
        status = vcoreIssM2mSetVmuxIspSrcAsCalBVp(hObj, (uint32_t) TRUE);

        if(FVID2_SOK == status)
        {
            stepStatus |= 0x40U;
        }
    }

    /* Store all open parameters */
    if(FVID2_SOK == status)
    {
        if(0U == instObj->openCnt)
        {
            instObj->curr420State = VPS_CORE_ISS_M2M_420SP_NONE;
        }
        BspUtils_memcpy(
            &hObj->openPrms,
            openPrms,
            sizeof(VpsCore_OpenPrms));
        instObj->openCnt++;
        handle = (VpsCore_Handle) hObj;
    }
    else
    {
        if(0x20U == (stepStatus & 0x20U))
        {
            vcoreIspUnRegisterIsr(hObj->hIspObj);
        }
        if(0x10U == (stepStatus & 0x10U))
        {
            vcoreIspCloseHals(hObj->hIspObj, NULL);
            hObj->hIspObj = NULL;
        }
        if(0x8U == (stepStatus & 0x8U))
        {
            VpsHal_isscalClose(hObj->calHalHandle, NULL);
            hObj->calHalHandle = NULL;
        }
        if(0x4U == (stepStatus & 0x4U))
        {
            /* Deallocate the CAL Resources */
            Irm_releaseResource(
                0U,
                (Irm_Modules_t)instObj->initPrms.calIrmId,
                &instObj->captRes);
        }
        if(0x2U == (stepStatus & 0x2U))
        {
            /* Deallocate resources */
        }
        if(0x1U == (stepStatus & 0x1U))
        {
            IssM2mFreeHandleObj(hObj);
            hObj = NULL;
        }
    }

    if(TRUE == isLockTaken)
    {
        IspUnLock(instObj);
    }

    return (handle);
}

int32_t vcoreIssM2mClose(VpsCore_Handle handle)
{
    int32_t status = FVID2_SOK;
    vpscoreissM2mInstObj_t   *instObj = NULL;
    vpscoreissM2mHandleObj_t *hObj    = NULL;

    /* Check for Null value */
    GT_assert(VpsIssCoreTrace, (NULL != handle));

    hObj    = (vpscoreissM2mHandleObj_t *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsIssCoreTrace, (NULL != instObj));
    GT_assert(VpsIssCoreTrace, (0U != instObj->openCnt));

    IspLock(instObj);

    BspUtils_memset(&hObj->openPrms, 0x0, sizeof(VpsCore_OpenPrms));

    instObj->openCnt--;

    /* Free up the Event Manager Handle */
    if(0U == instObj->openCnt)
    {
        status = vcoreIspUnRegisterIsr(hObj->hIspObj);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

        /* Free up the resources */
        status = Irm_releaseResource(
            0U,
            (Irm_Modules_t)instObj->initPrms.calIrmId,
            &instObj->captRes);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }

    /* Close Hals */
    status = vcoreIspCloseHals(hObj->hIspObj, NULL);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    status = VpsHal_isscalClose(hObj->calHalHandle, NULL);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    hObj->calHalHandle = NULL;

    IssM2mFreeHandleObj(hObj);

    IspUnLock(instObj);

    return (status);
}

/* MISRA.PPARAM.NEEDS.CONST
 * MISRAC_2004_Rule_16.7
 * Variable 'params' & 'prms' is not declared as a pointer to const
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Klocwork is not able to analyse pointers which are declared as const and
 *  reporting this issue.This is a false positive.
 */

/* Function to set the Params,
 * Sets the initial fixed parameters like path selection,
 * frame size, frame format etc */
int32_t vcoreIssM2mSetParams(VpsCore_Handle handle,
                             const void *params,
                             void       *args)
{
    int32_t status = FVID2_SOK;
    vpscoreissM2mInstObj_t   *instObj = NULL;
    vpscoreissM2mHandleObj_t *hObj    = NULL;
    const vpsissIspParams_t  *prms    = (const vpsissIspParams_t *) params;
    uint32_t cnt;

    /* Check for Null value */
    GT_assert(VpsIssCoreTrace, (NULL != handle));
    GT_assert(VpsIssCoreTrace, (NULL != params));

    hObj    = (vpscoreissM2mHandleObj_t *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsIssCoreTrace, (NULL != instObj));

    /*
     * Perform GLBCE startup sequence if it is enabled
     * Set the Configuration in CAL
     * Set the Configuration in ISP
     * Store IPIPEIF Rt Configuration
     * Copy Parameters
     */

    /* Only RSZ A & RSZ B output streams can be enabled */
    if(FVID2_DF_YUV420SP_UV == prms->inFmt.dataFormat)
    {
        for(cnt = 0U; cnt < VPS_ISS_STREAM_ID_MAX; cnt++)
        {
            if(((VPS_ISS_STREAM_CAL_RD_INPUT_0 != cnt) &&
                (VPS_ISS_STREAM_ID_RSZ_A != cnt)) &&
               (VPS_ISS_STREAM_ID_RSZ_B != cnt))
            {
                if(TRUE == prms->enableStreams[cnt])
                {
                    status = FVID2_EBADARGS;
                    break;
                }
            }
        }
    }

    if(TRUE == prms->enableWdrMerge)
    {
        /* enableWdrMerge and enableVportComp cannot be enabled at the
           same time */
        if (TRUE == prms->enableVportCompInput)
        {
            status = FVID2_EINVALID_PARAMS;
        }

        if ((uint32_t) TRUE != prms->enableStreams[VPS_ISS_STREAM_ID_INPUT_N1])
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }
    else
    {
        if((uint32_t) FALSE != prms->enableStreams[VPS_ISS_STREAM_ID_INPUT_N1])
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }

    if(((FVID2_SOK == status) &&
        (VPS_ISS_GLBCE_PATH_ISP == prms->glbcePath)) &&
       (FALSE == instObj->isGlbceInitDone))
    {
        /* Disable Vport->ISP Mux */
        vcoreIssM2mSetVmuxIspSrcAsCalBVp(hObj, (uint32_t) FALSE);

        status = vcore_issGlbceDoInit(
            (isshalCalInstId_t)instObj->initPrms.calInstId,
            hObj->calHalHandle,
            &hObj->calCfg,
            &hObj->calDrvCfg);

        vcoreIssM2mSetVmuxGlbce(hObj, (uint32_t) FALSE);
        vcoreIssM2mSetVmuxIspSrcAsCalBVp(hObj, (uint32_t) TRUE);
        instObj->isGlbceInitDone = (uint32_t) TRUE;
    }

    if((FVID2_SOK == status) && (NULL != hObj->calHalHandle))
    {
        vcoreIssM2mCalMakeCfg(hObj, prms);
        /* The handle configuration is update, which will later be applied
            (when we receive a frame to be processed for this handle */
    }
    else
    {
        /* CAL Hal Handle should never be null */
        GT_assert(VpsIssCoreTrace, FALSE);
    }

    if(FVID2_SOK == status)
    {
        /* Set the parameters in ISP */
        status = vcoreIspSetParams(hObj->hIspObj, prms);
    }

    if(FVID2_SOK == status)
    {
        if(TRUE == prms->enableVportCompInput)
        {
            hObj->ipipeifRtCfg.inpSrc1 = ISSHAL_IPIPEIF_ISIF_OUT_WDR_DFS;
        }
        else
        {
            /* For the both the WDR passes, input is coming from VPORT,
             * so source1 is from VPORT.  */
            hObj->ipipeifRtCfg.inpSrc1 = ISSHAL_IPIPEIF_ISIF_OUT_RAW_VPORT;
        }
        if(TRUE == prms->enableWdrMerge)
        {
            hObj->ipipeifRtCfg.enableWdr = (uint32_t) TRUE;

            /* When WDR Merge is enabled, Mux2 source is coming from wdr
             * merge module */
            hObj->ipipeifRtCfg.inpSrc2 = ISSHAL_IPIPEIF_IPIPE_OUT_WDR_DFS;

            /* Set the IPIPEIF Frame config */
            hObj->ipipeifFrmCfg.ppln = 0x0;
            hObj->ipipeifFrmCfg.lpfr = VCORE_ISS_IPIPEIF_WDR_DELAY_LINES;
            hObj->ipipeifFrmCfg.hnum = prms->inFmt.width;
            hObj->ipipeifFrmCfg.vnum = prms->inFmt.height;
        }
        else
        {
            hObj->ipipeifRtCfg.enableWdr = (uint32_t) FALSE;

            /* When WDR Merge is enabled, Mux2 source is
               coming from isif module */
            hObj->ipipeifRtCfg.inpSrc2 = ISSHAL_IPIPEIF_IPIPE_OUT_ISIF;

            /* Set the IPIPEIF Frame config */
            hObj->ipipeifFrmCfg.ppln = prms->inFmt.width;
            hObj->ipipeifFrmCfg.lpfr = prms->inFmt.height;
            hObj->ipipeifFrmCfg.hnum = prms->inFmt.width;
            hObj->ipipeifFrmCfg.vnum = prms->inFmt.height;
        }
    }

    return (status);
}

/* Get current parameters, copies it from local object */
int32_t vcoreIssM2mGetParams(VpsCore_Handle handle,
                             void          *params)
{
    int32_t status = FVID2_SOK;
    vpscoreissM2mHandleObj_t *hObj = NULL;
    vpsissIspParams_t *prms        = NULL;

    /* Check for Null value */
    GT_assert(VpsIssCoreTrace, (NULL != handle));
    GT_assert(VpsIssCoreTrace, (NULL != params));

    hObj = (vpscoreissM2mHandleObj_t *) handle;
    GT_assert(VpsIssCoreTrace, (NULL != hObj->hIspObj));

    prms = (vpsissIspParams_t *) params;

    BspUtils_memcpy(prms, &hObj->hIspObj->params, sizeof(vpsissIspParams_t));

    return (status);
}

/* Program the buffers and start all modules for m2m processing in
   one-shot mode */
int32_t vcoreIssM2mPutFrames(VpsCore_Handle  handle,
                             VpsCore_Frame **frm)
{
    int32_t  status = FVID2_SOK;
    uint32_t cnt;
    vpscoreissM2mHandleObj_t *hObj;
    vpscoreissM2mInstObj_t   *instObj = NULL;
    vcoreIspHandleObj_t      *hIspObj;
    uint32_t cookie;
    isshalCalBufferAddr_t calBuff;

    /* Check for Null value */
    GT_assert(VpsIssCoreTrace, (NULL != handle));
    GT_assert(VpsIssCoreTrace, (NULL != frm));

    hObj    = (vpscoreissM2mHandleObj_t *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsIssCoreTrace, (NULL != instObj));

    GT_assert(VpsIssCoreTrace, (NULL != hObj->hIspObj));
    hIspObj = hObj->hIspObj;

    /* Check if any pending/active request */
    cookie = BspOsal_disableInterrupt();
    if((TRUE == instObj->isRequestActive) ||
       (VPS_CORE_ISS_M2M_420SP_NONE != instObj->curr420State))
    {
        status = FVID2_EDEVICE_INUSE;
    }
    BspOsal_restoreInterrupt(cookie);

    /* Set the flag so that no one else can submit the request */
    cookie = BspOsal_disableInterrupt();
    if(FVID2_SOK == status)
    {
        instObj->isRequestActive = (uint32_t) TRUE;
        if(FVID2_DF_YUV420SP_UV == hIspObj->params.inFmt.dataFormat)
        {
            instObj->curr420State = VPS_CORE_ISS_M2M_420SP_LUMA;
            instObj->frm          = frm;
        }
    }
    BspOsal_restoreInterrupt(cookie);

/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * Name 'buffAddr[0U] = (UInt32) newFrame->addr[0U][0U]'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Memory mapped registers and other hardware features access requires
 * typecasting of pointer to integer.  The address space is 32 bit and type
 * casting to integer will not result into any loss because of TI's compiler
 * treatment to integer.
 * In this particular case, we check if the buffer address are aligned or not.
 */
/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'frm'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 *
 * In this particular case, the frm[] is checked when its submitted for
 *  processing.
 */
/* The above two exceptions are applicable for statements with in the "for loop"
 * below
 */
    /* Check for null pointers in the frame */
    for(cnt = 0U; ((cnt < VPS_ISS_STREAM_ID_MAX) && (FVID2_SOK == status));
        cnt++)
    {
        if(TRUE == hIspObj->params.enableStreams[cnt])
        {
            if(NULL == frm[cnt])
            {
                status = FVID2_EBADARGS;
            }
            if((NULL == frm[cnt]->addr[0U][0U]) && (FVID2_SOK == status))
            {
                status = FVID2_EBADARGS;
            }
            if((((uint32_t)(frm[cnt]->addr[0U][0U]) %
                VPS_ISS_ISP_BUF_ADDR_ALIGN) != 0U) && (FVID2_SOK == status))
            {
                status = FVID2_EBADARGS;
            }
            if((FVID2_DF_YUV420SP_UV == hIspObj->params.inFmt.dataFormat)
                         && (FVID2_SOK == status))
            {
                if(NULL == frm[cnt]->addr[0U][1U])
                {
                    status = FVID2_EBADARGS;
                }

                if((((uint32_t)(frm[cnt]->addr[0U][1U]) %
                    VPS_ISS_ISP_BUF_ADDR_ALIGN) != 0U) && (FVID2_SOK == status))
                {
                    status = FVID2_EBADARGS;
                }
            }
        }
    }

#ifdef VPSCORE_ENABLE_ISIF_WRITE
    *(volatile unsigned int *)0x5204101CU =
        (hIspObj->params.inFmt.width - 1U);
    *(volatile unsigned int *)0x52041028U =
        (hIspObj->params.inFmt.height - 1U);
    *(volatile unsigned int *)0x52041034U =
        (hIspObj->params.inFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX] >> 5U);
    *(volatile unsigned int *)0x52041038U = 0x0U;
    *(volatile unsigned int *)0x52041040U =
        (((uint32_t)0x847e9000U >> 5U) & 0xFFFFU);
    *(volatile unsigned int *)0x5204103Cu =
        (((uint32_t)0x847e9000U >> 21U) & 0x7FFU);
#endif /* VPSCORE_ENABLE_ISIF_WRITE */

    if(FVID2_SOK == status)
    {
        /* Setup GLBCE Switch Mux */
        vcoreIssM2mSetGlbceMux(hObj);

        /* Setup the IPIPEIF Mux */
        vcoreIssM2mSetIpipeifMux(hObj);

        /* CNF configuration could be changed, so set it on every frame */
        status = VpsHal_issSetCnfConfig(&hIspObj->cnfPrms);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

        /* Set Rsz Configuration */
        status = VpsHal_issrszSetConfig(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ],
            &hIspObj->rszCfg,
            NULL);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
        /* Update the frame size and paths with in ISIF, IPIPE */
        status = vcoreIssM2mSetSrcSize(hObj);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

        status = vcoreIssM2mEnDisProc(hObj);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

        /* Program the buffer addresses first */
        calBuff.numBuff      = 1U;
        calBuff.cPortId[0U]  = instObj->captRes.cport;
        calBuff.wrDmaCtx[0U] = (uint32_t) FALSE;
/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * Name 'buffAddr[0U] = (UInt32) newFrame->addr[0U][0U]'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Memory mapped registers and other hardware features access requires
 * typecasting of pointer to integer.  The address space is 32 bit and type
 * casting to integer will not result into any loss because of TI's compiler
 * treatment to integer.
 * In this particular case, we have to program the buffer address. The buffer
 *  address is converted from pointer to uint32
 */
/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'frm'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 *
 * In this particular case, the frm[] is checked when its submitted for
 *  processing.
 */
        calBuff.buffAddr[0U] =
            (uint32_t) frm[VPS_ISS_STREAM_CAL_RD_INPUT_0]->addr[0U][0U];
        calBuff.pitch[0U] =
            (uint32_t) hIspObj->params.inFmt.pitch[FVID2_YUV_INT_ADDR_IDX];

        status = VpsHal_isscalUpdateBufAddr(hObj->calHalHandle, &calBuff);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

        for(cnt = VPS_ISS_STREAM_ID_RSZ_A; cnt < VPS_ISS_STREAM_ID_MAX; cnt++)
        {
            if(TRUE == hIspObj->params.enableStreams[cnt])
            {
/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'frm'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 *
 * In this particular case, the frm[] is checked when its submitted for
 *  processing.
 */
                status = vcoreIspProgBuf(hIspObj, cnt, frm[cnt]);

                if(FVID2_SOK != status)
                {
                    break;
                }
            }
        }

        if(FVID2_SOK == status)
        {
            /* Before Starting any module, store the pointer to handle
             * object in instance object, so that if interrupt comes,
             * interrupt handler could call application callback from
             * interrupt handler */
            instObj->activeHandleObj = hObj;

            /* First enable All ISP modules */
            status = vcoreIspStart(hIspObj, NULL);

            if(FVID2_SOK == status)
            {
                /* At the last enable Cal */
                status = VpsHal_isscalRdDmaStart(
                    hObj->calHalHandle,
                    ISSHAL_ISS_PROC_MODE_ONE_SHOT,
                    NULL);
            }
        }
    }

    /* Restore the flag if some error occurred and it is not device in use */
    if((FVID2_SOK != status) &&
       (FVID2_EDEVICE_INUSE != status))
    {
        cookie = BspOsal_disableInterrupt();
        if(TRUE == instObj->isRequestActive)
        {
            instObj->isRequestActive = (uint32_t) FALSE;
        }
        BspOsal_restoreInterrupt(cookie);
    }

    return (status);
}

/* Function to handle control commands */
int32_t vcoreIssM2mControl(VpsCore_Handle handle,
                           uint32_t       cmd,
                           void          *appArgs,
                           void          *drvArgs)
{
    int32_t status = FVID2_SOK;
    vpscoreissM2mHandleObj_t *hObj;

    /* Check for Null value */
    GT_assert(VpsIssCoreTrace, (NULL != handle));

    hObj = (vpscoreissM2mHandleObj_t *) handle;

    switch(cmd)
    {
        case VPS_ISS_ISIF_IOCTL_SET_CONFIG:
            status = vcoreIssM2mCfgIsif(hObj, cmd, appArgs, drvArgs);
            break;

        default:
            status = vcoreIspControl(hObj->hIspObj, cmd, appArgs, drvArgs);
            break;
    }

    return (status);
}

/* M2M frame completion callback */
static void vcoreIssM2mFrmCmplCb(const UInt32 *event,
                                UInt32        numEvents,
                                Ptr           arg)
{
    int32_t  status;
    uint32_t cookie, callBack;
    vpscoreissM2mHandleObj_t *hObj;
    vpscoreissM2mInstObj_t   *instObj = NULL;
    vcoreIspHandleObj_t      *hIspObj;

    callBack = (uint32_t) TRUE;
    /* NULL Pointer error checks */
    instObj = (vpscoreissM2mInstObj_t *) arg;
    GT_assert(VpsIssCoreTrace, (NULL != instObj));
    hObj = instObj->activeHandleObj;
    GT_assert(VpsIssCoreTrace, (NULL != hObj));
    hIspObj = hObj->hIspObj;
    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    /* Mark the Hw is free and no pending request */
    cookie = BspOsal_disableInterrupt();

    if(FVID2_DF_YUV420SP_UV == hIspObj->params.inFmt.dataFormat)
    {
        callBack = (uint32_t) FALSE;
        if(VPS_CORE_ISS_M2M_420SP_LUMA == instObj->curr420State)
        {
            /* Luma process completed, configure for chroma processing */
            instObj->curr420State = VPS_CORE_ISS_M2M_420SP_CHROMA;
            vcoreIssM2mProcYuv420SPChroma(hIspObj, instObj);
        }
        else if(VPS_CORE_ISS_M2M_420SP_CHROMA == instObj->curr420State)
        {
            /* Frame processing completed */
            instObj->curr420State    = VPS_CORE_ISS_M2M_420SP_NONE;
            instObj->isRequestActive = (uint32_t) FALSE;
            instObj->activeHandleObj = NULL;
            callBack = (uint32_t) TRUE;
        }
        else
        {
            /* This should not happen */
            GT_assert(VpsIssCoreTrace, (FALSE));
        }
    }
    else
    {
        instObj->isRequestActive = (uint32_t) FALSE;
        instObj->activeHandleObj = NULL;
    }
    BspOsal_restoreInterrupt(cookie);

    if((TRUE == callBack) && (NULL != hObj->openPrms.frmDoneNotifyCb))
    {
        /* Call the callback of the upper layer */
        hObj->openPrms.frmDoneNotifyCb(hObj->openPrms.drvData);
    }

    if(TRUE == hIspObj->params.enableStreams[VPS_ISS_STREAM_ID_AF])
    {
        GT_assert(VpsIssCoreTrace, (FALSE ==
                                    VpsHal_issh3aIsAfBusy(
                                        hIspObj->halHandles[
                                            VPS_ISS_ISP_MODULE_H3A])));

        status = VpsHal_issh3aAfStop(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A],
            NULL);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }
    if(TRUE == hIspObj->params.enableStreams[VPS_ISS_STREAM_ID_AEWB])
    {
        GT_assert(VpsIssCoreTrace, (FALSE ==
                                    VpsHal_issh3aIsAewbBusy(
                                        hIspObj->halHandles[
                                            VPS_ISS_ISP_MODULE_H3A])));

        status = VpsHal_issh3aAewbStop(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A],
            NULL);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }
}

static void IspLock(vpscoreissM2mInstObj_t *instObj)
{
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);
}

static void IspUnLock(vpscoreissM2mInstObj_t *instObj)
{
    BspOsal_semPost(instObj->lockSem);
}

/* Function to allocate a handle object from the pool of objects */
static vpscoreissM2mHandleObj_t *IssM2mAllocHandleObj(void)
{
    uint32_t hCnt;
    vpscoreissM2mHandleObj_t *hObj = NULL;

    for(hCnt = 0U; hCnt < VPSCORE_ISS_M2M_ISP_MAX_HANDLES; hCnt++)
    {
        if(FALSE == gIssM2mHandleObjs[hCnt].isAllocated)
        {
            gIssM2mHandleObjs[hCnt].isAllocated = (uint32_t) TRUE;
            hObj = &gIssM2mHandleObjs[hCnt];
            break;
        }
    }

    return (hObj);
}

/* Function to free a allocated handle object */
static void IssM2mFreeHandleObj(const vpscoreissM2mHandleObj_t *hObj)
{
    uint32_t hCnt, found = (uint32_t) FALSE;

    for(hCnt = 0U; hCnt < VPSCORE_ISS_M2M_ISP_MAX_HANDLES; hCnt++)
    {
        if(hObj == &gIssM2mHandleObjs[hCnt])
        {
            found = (uint32_t) TRUE;
            gIssM2mHandleObjs[hCnt].isAllocated = (uint32_t) FALSE;
            break;
        }
    }

    GT_assert(VpsIssCoreTrace, (TRUE == found));
}

/* Connects Source and Sink of the video mux */
static int32_t vcoreIssM2mSetVmuxIspSrcAsCalBVp(
    vpscoreissM2mHandleObj_t *hObj,
    uint32_t
    isConnected)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if(VPSCORE_ISS_M2M_ISP_INST_0 == hObj->instObj->instId)
    {
        hObj->vmuxSrc  = SRC_PORT_CAL_B_VP;
        hObj->vmuxSink = SINK_PORT_ISP_IN;

        /* Gate the clock first */
        status = VpsHal_issvmuxClkCtrl(
            hObj->vmuxSrc,
            hObj->vmuxSink,
            (uint32_t) FALSE);

        if(FVID2_SOK == status)
        {
            /* Setup the path */
            status = VpsHal_issvmuxSetPath(
                hObj->vmuxSrc,
                hObj->vmuxSink,
                isConnected);
        }

        if(FVID2_SOK == status)
        {
            /* Enable the clock */
            status = VpsHal_issvmuxClkCtrl(
                hObj->vmuxSrc,
                hObj->vmuxSink,
                (uint32_t) TRUE);
        }
    }

    return (status);
}

/* Connects Source and Sink of the video mux */
static int32_t vcoreIssM2mSetVmuxGlbce(
    const vpscoreissM2mHandleObj_t *hObj,
    uint32_t                       flag)
{
    int32_t status = FVID2_SOK;
    isshalVMuxSrcPorts_t  vmuxSrc;
    isshalVMuxSinkPorts_t vmuxSink;

    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if(VPSCORE_ISS_M2M_ISP_INST_0 == hObj->instObj->instId)
    {
        vmuxSrc  = SRC_PORT_CAL_B_BYS_OUT;
        vmuxSink = SINK_PORT_GLBCE_IN;

        /* Gate the clock first */
        status = VpsHal_issvmuxClkCtrl(
            vmuxSrc,
            vmuxSink,
            (uint32_t) FALSE);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

        if(FVID2_SOK == status)
        {
            if(FALSE == flag)
            {
                status = VpsHal_issvmuxSetPath(
                    vmuxSrc,
                    vmuxSink,
                    (uint32_t) FALSE);
                GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
            }
            else
            {
                /* Setup the path */
                status = VpsHal_issvmuxSetPath(
                    vmuxSrc,
                    vmuxSink,
                    (uint32_t) TRUE);
                GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
            }
        }

        if(FVID2_SOK == status)
        {
            /* Enable the clock */
            status = VpsHal_issvmuxClkCtrl(
                vmuxSrc,
                vmuxSink,
                (uint32_t) TRUE);
            GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
        }
    }

    return (status);
}

static void vcoreIssM2mSetGlbceMux(const vpscoreissM2mHandleObj_t *hObj)
{
    int32_t status = FVID2_SOK;
    vcoreIspHandleObj_t *hIspObj;

    GT_assert(VpsIssCoreTrace, (NULL != hObj));
    GT_assert(VpsIssCoreTrace, (NULL != hObj->hIspObj));
    hIspObj = hObj->hIspObj;

    if((VPS_ISS_NSF3_PATH_ISP == hIspObj->params.nsf3Path) ||
       (TRUE == hIspObj->params.enableDpcPreNsf3))
    {
        VpsHal_issSetGlbceSwitch(
            ISSHAL_GLBCE_SWITCH_NSF3,
            hObj->glbceSwitchNsf3Input);
    }
    else
    {
        VpsHal_issSetGlbceSwitch(
            ISSHAL_GLBCE_SWITCH_NSF3,
            ISSHAL_GLBCE_SWITCH_DISABLED);
    }

    if(VPS_ISS_GLBCE_PATH_ISP == hIspObj->params.glbcePath)
    {
        VpsHal_issSetGlbceSwitch(
            ISSHAL_GLBCE_SWITCH_GLBCE,
            hObj->glbceSwitchGlbceInput);
    }
    else
    {
        VpsHal_issSetGlbceSwitch(
            ISSHAL_GLBCE_SWITCH_GLBCE,
            ISSHAL_GLBCE_SWITCH_DISABLED);
    }

    VpsHal_issDpcBeforeNsf3(hIspObj->params.enableDpcPreNsf3);

    /* Set the VP1 configuration */
    status = VpsHal_issSetVp1Config(&hIspObj->vp1Cfg);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

    /* Set the VP2 configuration */
    status = VpsHal_issSetVp2Config(&hIspObj->vp2Cfg);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
}

static void vcoreIssM2mSetIpipeifMux(vpscoreissM2mHandleObj_t *hObj)
{
    int32_t status = FVID2_SOK;
    vcoreIspHandleObj_t *hIspObj;

    GT_assert(VpsIssCoreTrace, (NULL != hObj));
    GT_assert(VpsIssCoreTrace, (NULL != hObj->hIspObj));
    hIspObj = hObj->hIspObj;

    if(NULL != hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF])
    {
        status = VpsHal_issipipeifControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
            VPS_HAL_ISS_IOCTL_IPIPEIF_SETRTCFG,
            &hObj->ipipeifRtCfg,
            NULL);
    }
    else
    {
        GT_assert(VpsIssCoreTrace, (FALSE));
    }
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
}

static int32_t vcoreIssM2mCfgIsif(vpscoreissM2mHandleObj_t *hObj,
                                  uint32_t                  cmd,
                                  void                     *appArgs,
                                  void                     *drvArgs)
{
    int32_t status;
    vpsissIsifCtrl_t      *pIsifVfdcCfg;
    vpsissIsifVfdcMethod_t savedMode;

    status = FVID2_EBADARGS;
    if((NULL != hObj) && (NULL != appArgs))
    {
        pIsifVfdcCfg = (vpsissIsifCtrl_t *) appArgs;

        if((VPS_ISS_ISIF_MODULE_VDFC != pIsifVfdcCfg->module) ||
           (VPS_ISS_ISIF_VDFC_DISABLE == pIsifVfdcCfg->vfdcCfg->mode))
        {
            status = vcoreIspControl(hObj->hIspObj, cmd,
                                     appArgs, drvArgs);
        }
        else
        {
            savedMode = pIsifVfdcCfg->vfdcCfg->mode;

            /* Ensure VPort is connected to ISP */
            status = vcoreIssM2mSetVmuxIspSrcAsCalBVp(hObj, (uint32_t) TRUE);
            if(FVID2_SOK == status)
            {
                /* A dummy read to enable pixel clock in free run mode */
                status = vcoreIssM2mIsifVfdcDummyCalRead(hObj, (uint32_t) TRUE);

                /* Configure VFDC */
                if(FVID2_SOK == status)
                {
                    pIsifVfdcCfg->vfdcCfg->mode = VPS_ISS_ISIF_VDFC_DISABLE;

                    status += vcoreIspControl(hObj->hIspObj, cmd,
                                              appArgs, drvArgs);
                    /* A dummy read to ensure disable is latched - latches on
                            VD */
                    status += vcoreIssM2mIsifVfdcDummyCalRead(hObj,
                        (uint32_t) TRUE);

                    pIsifVfdcCfg->vfdcCfg->mode = savedMode;

                    status += vcoreIspControl(hObj->hIspObj, cmd,
                                              appArgs, drvArgs);

                    /* A dummy read to disable pixel clock in free run mode &
                        VFDC enable is latched */
                    status += vcoreIssM2mIsifVfdcDummyCalRead(hObj,
                        (uint32_t) FALSE);
                }

                /* Restore CAL config */
                vcoreIssM2mCalMakeCfg(hObj, &hObj->hIspObj->params);
                status += VpsHal_isscalControl(
                    hObj->calHalHandle,
                    VPS_HAL_ISS_IOCTL_CAL_SETCFG,
                    &hObj->calCfg,
                    NULL);
                status += vcoreIssM2mSetVmuxIspSrcAsCalBVp(hObj,
                    (uint32_t) TRUE);
            }
        }
    }
    return (status);
}

static int32_t vcoreIssM2mIsifVfdcDummyCalRead(
    vpscoreissM2mHandleObj_t *hObj,
    uint32_t
    freeRunMode)
{
    int32_t               status = FVID2_SOK;
    isshalCalCfg_t        calCfg;
    isshalCalDmaVcCfg_t   calDmaCfg;
    isshalCalBufferAddr_t calBuff;
    volatile uint32_t     reg, timeout;

    calDmaCfg.numCPortId          = 1U;
    calDmaCfg.cportId[0]          = 0;
    calDmaCfg.isCsi2VcCfgValid[0] = (uint32_t) FALSE;
    calDmaCfg.isWrDmaCfgValid[0]  = (uint32_t) FALSE;
    calDmaCfg.isRdDmaCfgValid[0]  = (uint32_t) TRUE;

    calDmaCfg.rdDmaCfg[0U].enable = (uint32_t) TRUE;
    calDmaCfg.rdDmaCfg[0U].pixClock          = 65536U; /*Setting the max pix
                                                    *clock*/
    calDmaCfg.rdDmaCfg[0U].bwLimit           = 0x0U;   /*Setting it to minimum
                                                    *value*/
    calDmaCfg.rdDmaCfg[0U].ocpTagCnt         = 0xF;
    calDmaCfg.rdDmaCfg[0U].bysOutLeWait      = (uint32_t) FALSE;
    calDmaCfg.rdDmaCfg[0U].ySkipMode         = 0; /* No Line Skip */
    calDmaCfg.rdDmaCfg[0U].format.width      = 0x8U;
    calDmaCfg.rdDmaCfg[0U].format.height     = 0x1U;
    calDmaCfg.rdDmaCfg[0U].format.dataFormat = FVID2_DF_BAYER_RAW;
    calDmaCfg.rdDmaCfg[0U].format.bpp        = FVID2_BPP_BITS12;
    calDmaCfg.rdDmaCfg[0U].format.pitch[0U]  = 0;
    calDmaCfg.rdDmaCfg[0U].format.pitch[1U]  = 0;
    calDmaCfg.rdDmaCfg[0U].format.pitch[2U]  = 0;

    calCfg.pDmaVcCfg           = &calDmaCfg;
    calCfg.numCPortId          = 1U;
    calCfg.cportId[0]          = 0;
    calCfg.isBysOutCfgValid[0] = (uint32_t) FALSE;
    calCfg.isBysInCfgValid[0]  = (uint32_t) FALSE;

    calCfg.isVportCfgValid[0]   = (uint32_t) TRUE;
    calCfg.vportCfg[0].enable   = (uint32_t) TRUE;
    calCfg.vportCfg[0].pixClock = 65536U;
    calCfg.vportCfg[0].width    = 0x0;
    calCfg.vportCfg[0].yBlk     = 0x0;
    calCfg.vportCfg[0].xBlk     = 0x0;
    calCfg.vportCfg[0].rdyThr   = 0x0;
    calCfg.vportCfg[0].fsReset  = (uint32_t) TRUE;
    calCfg.vportCfg[0].freeRun  = freeRunMode;

    calCfg.writeToMem[0] = (uint32_t) FALSE;

    status = VpsHal_isscalControl(
        hObj->calHalHandle,
        VPS_HAL_ISS_IOCTL_CAL_SETCFG,
        &calCfg,
        NULL);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

    calBuff.numBuff      = 1U;
    calBuff.cPortId[0U]  = 0U;
    calBuff.wrDmaCtx[0U] = (uint32_t) FALSE;
    calBuff.buffAddr[0U] = VCORE_ISS_READ_ADDR_GBLCE_STARTUP_SEQ;
    calBuff.pitch[0U]    = 0x0;

    /* Clear End of frame at vport */
    VpsHal_calClearVportEof(hObj->calHalHandle);

    status = VpsHal_isscalUpdateBufAddr(hObj->calHalHandle, &calBuff);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

    status = VpsHal_isscalRdDmaStart(
        hObj->calHalHandle,
        ISSHAL_ISS_PROC_MODE_ONE_SHOT,
        NULL);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

    /* Wait for End Of Frame at VPORT */
    timeout = 0xFFFFU;
    do
    {
        if (VpsHal_calIsVportEof(hObj->calHalHandle))
        {
            break;
        }
        timeout --;
    } while (timeout > 0U);

    if ((0U == timeout) && (0U == VpsHal_calIsVportEof(hObj->calHalHandle)))
    {
        status = FVID2_EFAIL;
    }

    return (status);
}

static int32_t vcoreIssM2mCalMakeCfg(vpscoreissM2mHandleObj_t *hObj,
                                     const vpsissIspParams_t  *prms)
{
    isshalCalCfg_t         *calCfg;
    isshalCalDmaVcCfg_t    *calDmaCfg;
    vpsissCalPixProc_t     *pPixProc;
    vpscoreissM2mInstObj_t *instObj;
    vpsissCalPixExtract_t   extract;
    uint32_t cportId;
    int32_t  status = FVID2_EBADARGS;

    if(NULL != hObj)
    {
        status  = FVID2_SOK;
        instObj = hObj->instObj;

        calCfg    = &hObj->calCfg;
        calDmaCfg = &hObj->calDrvCfg;

        cportId = instObj->captRes.cport;
        /* Set the Read DMA configuration */
        calCfg->numCPortId       = 1U;
        calCfg->cportId[cportId] = instObj->captRes.cport;

        calDmaCfg->isRdDmaCfgValid[cportId] = (uint32_t) TRUE;
        calDmaCfg->rdDmaCfg[cportId].enable = (uint32_t) TRUE;
        calDmaCfg->rdDmaCfg[cportId].format.width      = prms->inFmt.width;
        calDmaCfg->rdDmaCfg[cportId].format.height     = prms->inFmt.height;
        calDmaCfg->rdDmaCfg[cportId].format.dataFormat =
            (Fvid2_DataFormat) prms->inFmt.dataFormat;
        calDmaCfg->rdDmaCfg[cportId].format.bpp = prms->inFmt.bpp;
        /* YUV420 SP input is supported for re-sizing only, when YUV420 SP mode
            we process Luma & Chroma separately */
        if(FVID2_DF_YUV420SP_UV == prms->inFmt.dataFormat)
        {
            pPixProc = NULL;
            calDmaCfg->rdDmaCfg[cportId].format.dataFormat = FVID2_DF_RAW08;
            calDmaCfg->rdDmaCfg[cportId].format.bpp        = FVID2_BPP_BITS8;
            calCfg->isPixProcCfgValid[cportId] = (uint32_t) TRUE;
            pPixProc = &calCfg->pixProcCfg[cportId];

            /* Ideally, we should ensure dpmDecode, dpmEncode also match */
            GT_assert(VpsIssCoreTrace, (instObj->captRes.pixPack ==
                                        instObj->captRes.pixExtract));

            pPixProc->contextToBeUsed       = instObj->captRes.pixExtract;
            pPixProc->extract               = VPS_ISS_CAL_PIX_EXRCT_B8;
            pPixProc->decCodec              = VPS_ISS_CAL_DPCM_DEC_BYPASS;
            pPixProc->enableDpcmInitContext = (uint32_t) FALSE;
            pPixProc->addr                  = NULL;
            pPixProc->offSet                = NULL;
            pPixProc->encCodec              = VPS_ISS_CAL_DPCM_ENC_BYPASS;
            pPixProc->pack                  = VPS_ISS_CAL_PIX_PACK_B16;
        }
        else
        {
            pPixProc = NULL;
            calCfg->isPixProcCfgValid[cportId] = (uint32_t) TRUE;
            pPixProc = &calCfg->pixProcCfg[cportId];

            /* Ideally, we should ensure dpmDecode, dpmEncode also match */
            GT_assert(VpsIssCoreTrace, (instObj->captRes.pixPack ==
                                        instObj->captRes.pixExtract));

            pPixProc->contextToBeUsed = instObj->captRes.pixExtract;
            /* For BPP > 8 & <= 16, we assume that its not packed and its
                contained in a 16 bit container. If its packed, update below to
                extract required bits. */
            extract = VPS_ISS_CAL_PIX_EXRCT_B8;
            switch(prms->inFmt.bpp)
            {
                case FVID2_BPP_BITS8:
                    extract = VPS_ISS_CAL_PIX_EXRCT_B8;
                    break;
                case FVID2_BPP_BITS10:
                case FVID2_BPP_BITS12:
                case FVID2_BPP_BITS14:
                case FVID2_BPP_BITS16:
                    extract = VPS_ISS_CAL_PIX_EXRCT_B16_LE;
                    break;
                case FVID2_BPP_BITS12_PACKED_MIPI:
                    extract = VPS_ISS_CAL_PIX_EXRCT_B12_MIPI;
                    calDmaCfg->rdDmaCfg[cportId].format.width =
                        (calDmaCfg->rdDmaCfg[cportId].format.width * 3u) / 2u;
                    break;
                default:
                    status = FVID2_EBADARGS;
                    break;
            }
            pPixProc->extract  = extract;
            pPixProc->decCodec = VPS_ISS_CAL_DPCM_DEC_BYPASS;
            pPixProc->enableDpcmInitContext = (uint32_t) FALSE;
            pPixProc->addr     = NULL;
            pPixProc->offSet   = NULL;
            pPixProc->encCodec = VPS_ISS_CAL_DPCM_ENC_BYPASS;
            pPixProc->pack     = VPS_ISS_CAL_PIX_PACK_B16;
        }

        calDmaCfg->rdDmaCfg[cportId].format.pitch[0U] =
            prms->inFmt.pitch[cportId];
        calDmaCfg->rdDmaCfg[cportId].format.pitch[1U] =
            prms->inFmt.pitch[1U];
        calDmaCfg->rdDmaCfg[cportId].format.pitch[2U] =
            prms->inFmt.pitch[2U];

        calDmaCfg->rdDmaCfg[cportId].pixClock     = 65536; /* Setting the
                                                               max pix clock */
        calDmaCfg->rdDmaCfg[cportId].bwLimit      = 0x0U;  /* Setting it to
                                                            minimum value */
        calDmaCfg->rdDmaCfg[cportId].ocpTagCnt    = 0xFU;
        calDmaCfg->rdDmaCfg[cportId].bysOutLeWait = (uint32_t) FALSE;
        calDmaCfg->rdDmaCfg[cportId].ySkipMode    = 0U; /* No Line Skip */

        /* Set the Video Port configuration */
        calCfg->isVportCfgValid[cportId]   = (uint32_t) TRUE;
        calCfg->vportCfg[cportId].enable   = (uint32_t) TRUE;
        calCfg->vportCfg[cportId].pixClock = 32768U;

        /* Note: Always Sending 2pixels/cycle as CAL cannot send 1pixel/cycle to
         * VP port */
        calCfg->vportCfg[cportId].width = 1U;

        /* TODO: Get this blanking requirement from the HAL */
        calCfg->vportCfg[cportId].xBlk    = 6U;
        calCfg->vportCfg[cportId].yBlk    = 50U;
        calCfg->vportCfg[cportId].rdyThr  = 128U;
        calCfg->vportCfg[cportId].fsReset = (uint32_t) TRUE;
                                        /* By default, reset SM on every FS */
        calCfg->vportCfg[cportId].freeRun = (uint32_t) FALSE;

        calCfg->pDmaVcCfg = calDmaCfg;
    }
    return (status);
}

/**
    \brief Configure for chroma processing in YUV420 SP scaling operation
*/

static int32_t vcoreIssM2mProcYuv420SPChroma(vcoreIspHandleObj_t    *hIspObj,
                                        const vpscoreissM2mInstObj_t *instObj)
{
    int32_t  status;
    uint32_t cportId;
    isshalCalBufferAddr_t     calBuff;
    vpscoreissM2mHandleObj_t *hObj = NULL;
    /*
        For Chroma pass, the RSZ take input from ISIF, this done so to ensure
            YEE has no effect. Other option was to disable YEE. Its easier
            to change the path instead.
            If RSZ takes input from IPIPE, ensure to set the input frame height
            /2, config of IPIPE.
        . Update CAL - Height & buffer address for chroma
        . Update IPIPE IF for height - only if RSZ takes input from IPIPE
        . Update ISIF to not swap and input frame height
        . Update IPIPE input frame height
        . Update RSZ for chroma pass, buffer address for chroma & height
        . Start
    */
    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));
    GT_assert(VpsIssCoreTrace, (NULL != instObj));
    GT_assert(VpsIssCoreTrace, (NULL != instObj->activeHandleObj));
    hObj   = instObj->activeHandleObj;
    status = FVID2_SOK;

    /* CAL */
    cportId = instObj->captRes.cport;
    hObj->calDrvCfg.rdDmaCfg[cportId].format.height /= 2U;

    status = VpsHal_isscalControl(
        hObj->calHalHandle,
        VPS_HAL_ISS_IOCTL_CAL_RD_FMT_UPDATE,
        &hObj->calDrvCfg.rdDmaCfg[cportId].format,
        NULL);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

    if(FVID2_SOK == status)
    {
        calBuff.numBuff      = 1U;
        calBuff.cPortId[0U]  = instObj->captRes.cport;
        calBuff.wrDmaCtx[0U] = (uint32_t) FALSE;
/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * Name 'buffAddr[0U] = (UInt32) newFrame->addr[0U][0U]'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Memory mapped registers and other hardware features access requires
 * typecasting of pointer to integer.  The address space is 32 bit and type
 * casting to integer will not result into any loss because of TI's compiler
 * treatment to integer.
 * In this particular case, we have to program the buffer address. The buffer
 *  address is converted from pointer to uint32
 */
/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'frm'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 *
 * In this particular case, the frm[] is checked when its submitted for
 *  processing.
 */
        calBuff.buffAddr[0U] = (uint32_t)
                               instObj->frm[VPS_ISS_STREAM_CAL_RD_INPUT_0]->
                               addr[0U][1U];
        calBuff.pitch[0U] = (uint32_t)
                            hIspObj->params.inFmt.pitch[
            FVID2_YUV_PL_CB_ADDR_IDX];

        status = VpsHal_isscalUpdateBufAddr(hObj->calHalHandle, &calBuff);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }

    if(FVID2_SOK == status)
    {
        /* IPIPE IF */
        hIspObj->ipipeifCfg.ipFrameCfg.vnum /= 2U;
        status = VpsHal_issipipeifControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
            VPS_HAL_ISS_IOCTL_IPIPEIF_SET_FRAME_CFG,
            &hIspObj->ipipeifCfg.ipFrameCfg,
            NULL);
    }

    /* ISIF */
    if(FVID2_SOK == status)
    {
        hIspObj->isifCfg.srcCfg.vdWidth       /= 2U;
        hIspObj->isifCfg.srcCfg.linesPerFrame /= 2U;
        hIspObj->isifCfg.srcCfg.ycInSwap       = (uint32_t) FALSE;
        status = VpsHal_issisifControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF],
            ISSHAL_IOCTL_ISIF_SET_IP_FRM_SIZE,
            &hIspObj->isifCfg.srcCfg,
            NULL);
    }

#ifdef IF_IPIPE_INPUTS_TO_RSZ
    if(FVID2_SOK == status)
    {
        /* IPIPE */
        hIspObj->ipipeCfg.srcCfg.procWin.cropHeight /= 2U;
        status = VpsHal_issipipeControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
            ISSHAL_IOCTL_IPIPE_CROP_WIN_UPDATE,
            &hIspObj->ipipeCfg.srcCfg.procWin,
            NULL);
    }
#endif /* IF_IPIPE_INPUTS_TO_RSZ */

    /* RSZ */
    if(FVID2_SOK == status)
    {
#ifndef IF_IPIPE_INPUTS_TO_RSZ
        hIspObj->rszCfg.srcCfg.inpSrc = ISSHAL_RSZ_INP_SRC_IPIPEIF;
#endif  /* IF_IPIPE_INPUTS_TO_RSZ */
        hIspObj->rszCfg.srcCfg.procWin.cropStartY /= 2U;
        hIspObj->rszCfg.srcCfg.procWin.cropHeight /= 2U;
        hIspObj->rszCfg.srcCfg.rszLuma = (uint32_t) FALSE;

        if(TRUE == hIspObj->params.enableStreams[VPS_ISS_STREAM_ID_RSZ_A])
        {
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A].outFmt.height /= 2U;
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A].startPos.startY /= 2U;
/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'frm'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 *
 * In this particular case, the frm[] is checked when its submitted for
 *  processing.
 */
            vcoreIspProgBuf(hIspObj, VPS_ISS_STREAM_ID_RSZ_A,
                            instObj->frm[VPS_ISS_STREAM_ID_RSZ_A]);
        }

        if(TRUE == hIspObj->params.enableStreams[VPS_ISS_STREAM_ID_RSZ_B])
        {
/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'frm'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 *
 * In this particular case, the frm[] is checked when its submitted for
 *  processing.
 */
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B].outFmt.height /= 2U;
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B].startPos.startY /= 2U;
            vcoreIspProgBuf(hIspObj, VPS_ISS_STREAM_ID_RSZ_B,
                            instObj->frm[VPS_ISS_STREAM_ID_RSZ_B]);
        }

        status = VpsHal_issrszControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ],
            ISSHAL_IOCTL_RSZ_SET_CHROMA_PROCCFG,
            &hIspObj->rszCfg,
            NULL);
    }

    /* Start */
    if(FVID2_SOK == status)
    {
#ifndef IF_IPIPE_INPUTS_TO_RSZ
        uint32_t ipipeMod;
        /* We do not want to start IPIPE in case its not used */
        ipipeMod = hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE];
        hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE] = (uint32_t) FALSE;
#endif
        status = vcoreIspStart(hIspObj, NULL);

#ifndef IF_IPIPE_INPUTS_TO_RSZ
        hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE] = ipipeMod;
#endif  /* IF_IPIPE_INPUTS_TO_RSZ */
    }

    if(FVID2_SOK == status)
    {
        status = VpsHal_isscalRdDmaStart(
            hObj->calHalHandle,
            ISSHAL_ISS_PROC_MODE_ONE_SHOT,
            NULL);
    }

    return (status);
}

/**
    \brief Configure ISP with update configuration. Following modules are
            Updated as below
    CAL Read configuration - as the width of read could vary
    IPIPE IF, NSF3, GLBCE - Input frame size is updated
    ISIF - Source configuration - as i/f width, msbPos, frame size could change
    IPIE - Source configuration - as input path, frame size
*/

static int32_t vcoreIssM2mSetSrcSize(vpscoreissM2mHandleObj_t *hObj)
{
    int32_t status;
    vcoreIspHandleObj_t *hIspObj = NULL;
    /*  Configure the width, height & data format for all enabled IPs
        CAL B, IPIPE IF,  NSF NSF3 only, ISIF, GLBCE & IPIPE */
    /* ISS_TODO - Add flag to figure out if config has been updated.
        Put the flag in instance object, set that if any config updates have
        happened */
    GT_assert(VpsIssCoreTrace, (NULL != hObj->hIspObj));
    hIspObj = hObj->hIspObj;

    status = VpsHal_isscalControl(
        hObj->calHalHandle,
        VPS_HAL_ISS_IOCTL_CAL_SETCFG,
        &hObj->calCfg,
        NULL);

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPEIF]))
    {
        /* Set the Frame size in ipipeif */
        status = VpsHal_issipipeifControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
            VPS_HAL_ISS_IOCTL_IPIPEIF_SET_FRAME_CFG,
            &hObj->ipipeifFrmCfg,
            NULL);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }

    if(FVID2_SOK == status)
    {
        status = vcoreIspSetSrcSize(hIspObj);
    }

    return (status);
}

static int32_t vcoreIssM2mEnDisProc(const vpscoreissM2mHandleObj_t *hObj)
{
    int32_t status;
    vcoreIspHandleObj_t *hIspObj = NULL;
    vpsissIpipeifCtrl_t  ipipeifCtrl;

    GT_assert(VpsIssCoreTrace, (NULL != hObj));
    GT_assert(VpsIssCoreTrace, (NULL != hObj->hIspObj));
    hIspObj = hObj->hIspObj;
    status = FVID2_EBADARGS;

    /* IPIPE IF */
    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPEIF])
    {
        /* ISS_TODO - Right not 2 separate call to enable / disable
            companding/decompanding & saturation features.
            Should be one call */
        ipipeifCtrl.module         = VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG;
        ipipeifCtrl.pCompDecompCfg = &hIspObj->ipipeifCfg.compDecompCfg;
        status = VpsHal_issipipeifControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
            VPS_HAL_ISS_IOCTL_IPIPEIF_EN_DIS_COMP_DECOMP_SAT,
            &ipipeifCtrl,
            NULL);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

        ipipeifCtrl.module  = VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG;
        ipipeifCtrl.pSatCfg = &hIspObj->ipipeifCfg.satCfg;
        status = VpsHal_issipipeifControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
            VPS_HAL_ISS_IOCTL_IPIPEIF_EN_DIS_COMP_DECOMP_SAT,
            &ipipeifCtrl,
            NULL);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }

    /* Disable IPIPE - YEE */
    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE])
    {
        status = VpsHal_issipipeControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
            ISSHAL_IOCTL_IPIPE_EE_ENABLE_DISABLE,
            &hIspObj->ipipeCfg.eeCfg, NULL);
    }

    return status;
}

