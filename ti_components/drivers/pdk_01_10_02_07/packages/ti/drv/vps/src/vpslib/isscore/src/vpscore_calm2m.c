/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file vpscore_calm2m.c
 *
 *  \brief This file implements functions for SIMCOP and its sub-modules.
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

#include <ti/drv/vps/include/iss/vps_isscommon.h>

#include <ti/drv/vps/src/vpslib/common/iem_evtmgr.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_iss.h>

#include <ti/drv/vps/src/vpslib/isscore/vpscore_calm2m.h>

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */
/** \brief Number of instances of SIMCOP present */
#define VPSCORE_CALM2M_MAX_INST         (1U)

/** \brief Number of times simcop could be opened */
#define ISSCORE_CALM2M_MAX_SW_HANDLES   (8U)

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Handle object, defines a place holder for configuration for a given
 *          handle */
typedef struct vpscoreCalm2mHndlObj
{
    uint32_t                     instId;
    /**< Instance ID of the SIMCOP instance on which this handle was opened */
    uint32_t                     hndlIndex;
    /**< Index into pHndlObjs in #vpscoreCalm2mInstObj_t */
    vpsissCalm2mParams_t        cfg;
    /**< Configuration for this handle */
    vpsissCalm2mDmaCtrlParams_t  dmaCfg;
    /**< Dma Configuration for this handle */
    Ptr                          iemHandle;
    /**< Handle to event manager instance used */
    VpsCore_OpenPrms             openPrms;
    /**< Local copy of open parameters */
}vpscoreCalm2mHndlObj_t;

/** \brief Instance object, that defines place holder for sub-module handle and
 *          other instance specifics */

typedef struct vpscoreCalm2mInstObj
{
    vcoreCalm2mInitParams_t initPrms;
    /**< HAL information */
    uint32_t                instId;
    /**< SIMCOP Core instance ID */
    VpsCore_Handle          pHndlObjs[ISSCORE_CALM2M_MAX_SW_HANDLES];
    /**< Number of SW handles open on this SIMCOP instance */
    VpsHal_Handle           calm2mHalHandle;
    /**< HAL handle to current SIMCOP instance */
    vpscoreCalm2mHndlObj_t *pCurrHndl;
    /**< Used to determine if the configuration specified by the handle has to
     *      be applied or not.
     *  On the very first frame for a given handle, the config defined by the
     *      handle is applied.
     *  If there was no config change between two successive process frame
     *      calls config is not re-applied. */
    vpscoreCalm2mHndlObj_t  hndlObjsPool[ISSCORE_CALM2M_MAX_SW_HANDLES];
    /**< Pool of s/w handles */

    uint32_t                isRequestActive;
    /**< Flag to indicate if there is any active request,
     *   this is used to protect multiple request submission,
     *   core allows only one request to be processed at a time */
    vpscoreCalm2mHndlObj_t *pActiveHndlObj;
    /**< Used to determine which handle has currently programmed / using the
            h/w */
    uint32_t                regIsr;
    /**< Flag that indicates if an ISR has been registered for this instance.
            If so, re-registration is not allowed. */
}vpscoreCalm2mInstObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  vcoreCalm2mOpen
 *  \brief Open one driver instance on specified SIMCOP instance
 *  Sets up SIMCOP private objects as per specified mode of operation
 *  TBD: Fix Prototype
 *
 *  \param numInst      TBD
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
VpsCore_Handle vcoreCalm2mOpen(VpsCore_Inst            instId,
                               const VpsCore_OpenPrms *openPrms,
                               const void             *coreOpenPrms,
                               void                   *coreReturnPrms);

/**
 *  vcoreCalm2mClose
 *  \brief Close the specified handle
 *
 *  \param handle       Valid handle of type #VpsCore_Handle returned by
 *                      vcoreCalm2mOpen
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreCalm2mClose(VpsCore_Handle handle);

/**
 *  vcoreCalm2mSetConfig
 *  \brief Set configuration for specified SIMCOP handle
 *
 *  \param params      Configuration of type #vpsissSimcopCfgPrms_t
 *  \param rsvd        Unused argument. Value is don't care.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreCalm2mSetConfig(VpsCore_Handle handle,
                             const void    *params,
                             void          *rsvd);

/**
 *  vcoreCalm2mControl
 *  \brief Function to get/set control commands
 *
 *  \param handle      core handle
 *  \param cmd         Command ID
 *  \param cmdArgs     Command Specific Arguments
 *  \param drvArgs     Driver specific arguments
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreCalm2mControl(VpsCore_Handle handle,
                           UInt32         cmd,
                           void          *appArgs,
                           void          *drvArgs);

/**
 *  vcoreCalm2mPutFrames
 *  \brief Sets up the SIMCOP to perform required operation.
 *
 *  \param handle   Handle returned by open API
 *  \param frm      Pointer to array if VpsCore_Frame pointer, depending on the
 *                  requested operation, one or more frames should be valid.
 *                  Buffer are identified from array indices as specified by
 *                  #vpsissSimcopStreamId
 *
 *  \return         Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreCalm2mPutFrames(VpsCore_Handle  handle,
                             VpsCore_Frame **frm);

#ifdef __cplusplus
}
#endif

static void vcoreCalm2mIsr(const UInt32 *event,
                                   UInt32        numEvents,
                                   Ptr           handle);
/**
 *  \brief Function to process frame
 */
static int32_t vcoreCalm2mPutFramesInternal(VpsCore_Handle      handle,
                                            const VpsCore_Frame ** const frm);

/**
 *  \brief Function to validate the cfg params
 */
static int32_t vcoreCalm2mValidateParam (const vpsissCalm2mParams_t *pCalm2mPrm);

/**
 *  \brief Function to apply the cal config
 */
static int32_t vcoreCalm2mApplyConfig(VpsCore_Handle        handle,
                                      vpsissCalm2mParams_t cfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief SIMCOP Instance specific config / s/w states */
static vpscoreCalm2mInstObj_t         gInstObjs[VPSCORE_CALM2M_MAX_INST];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/** Returns the core operations
 */
const VpsCore_Ops *VpsCore_calm2mGetCoreOps(void)
{
    /** \brief Capture core function pointers. */
    static const VpsCore_Ops gCalm2mCoreOps =
    {
        NULL,                    /* Get property */
        &vcoreCalm2mOpen,        /* Open function */
        &vcoreCalm2mClose,       /* Close function */
        &vcoreCalm2mSetConfig,   /* Set Params */
        NULL,                    /* Get Params */
        &vcoreCalm2mControl,     /* Control */
        NULL,                    /* Start Required */
        NULL,                    /* Stop Required */
        NULL,                    /* Process */
        NULL,                    /* Core prog Buffer */
        &vcoreCalm2mPutFrames,   /* Update the buffer and start */
        NULL,                    /* getFrames */
        NULL                     /* getErrorStat */
    };

    return (&gCalm2mCoreOps);
}

/**
 *  VpsCore_simcopInit
 *  \brief SIMCOP core init function.
 *  Initializes core objects for all instances of SIMCOP.
 *  This function should be called before calling any of SIMCOP core API's.
 *
 *
 *  \param numInst      [IN] Number of SIMCOP instances to initialize
 *  \param initPrms     [IN] Array of type #vcoreSimcopInitParams_t and size
 *                      numInst containing init parameters with instance
 *                      numInst containing init parameters
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t VpsCore_calm2mInit(uint32_t                      numInst,
                         const vcoreCalm2mInitParams_t  *initPrms,
                         Ptr                             arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t i;
    vpscoreCalm2mInstObj_t     *pInstObj = NULL;
    vpshalissIspPlatformData_t *halPlt;

    /* Check for the null pointer */
    GT_assert(VpsIssCoreTrace, (NULL != initPrms));
    GT_assert(VpsIssCoreTrace, (VPSCORE_ISS_CALM2M_INST_MAX >= numInst));
    GT_assert(VpsIssCoreTrace, (NULL != initPrms->halPlatformData));

    halPlt = (vpshalissIspPlatformData_t *) VpsHal_getIspPlatformData();

    /* Initialize HAL */
    status = VpsHal_issctrlInit(halPlt->issCtrlInitPrms, NULL);

    /* Power up the simcop */
    VpsHal_issPowerCtrl(SUB_MODULE_CAL_A, (uint32_t) TRUE);

    for(i = 0u; i < numInst; i++)
    {
        pInstObj = &gInstObjs[i];

        BspUtils_memset(
            pInstObj,
            0x0,
            sizeof(vpscoreCalm2mInstObj_t));

        pInstObj->instId = i;

        /* Copy the params */
        BspUtils_memcpy(
            &pInstObj->initPrms,
            &initPrms[i],
            sizeof(vcoreCalm2mInitParams_t));

        if(FVID2_SOK == status)
        {
    
            status     = VpsHal_isscalInit(
                halPlt->numCalInst,
                halPlt->calInstPrms,
                NULL);
        }
    }

    return (status);
}

/**
 *  VpsCore_simcopDeInit
 *  \brief This function closes all HAL handles & power down SIMCOP
 *
 *  \param numInst      [IN] Number of SIMCOP instances to initialize
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t VpsCore_calm2mDeInit(void)
{
    int32_t  status = FVID2_SOK;
    vpscoreCalm2mInstObj_t *pInstObj = NULL;

    pInstObj = &gInstObjs[VPSCORE_ISS_CALM2M_INST_0];
    if(NULL != pInstObj->calm2mHalHandle)
    {
        status = VpsHal_isscalDeInit(NULL);
        if(FVID2_SOK == status)
        {
            /* For multiple instances of SIMCOP, this should be with in the
                loop above. */
            VpsHal_issPowerCtrl(SUB_MODULE_CAL_A, (uint32_t) FALSE);
    
            status = VpsHal_issctrlDeInit(NULL);
        }
    }
    return (status);
}

/**
 *  vcoreCalm2mClose
 *  \brief Close the specified handle
 *
 *  \param handle       Valid handle of type #VpsCore_Handle returned by
 *                      vcoreCalm2mOpen
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreCalm2mClose(VpsCore_Handle handle)
{
    int32_t  retVal = BSP_EFAIL;
    uint32_t hndlIndex;
    uint32_t instId;
    vpscoreCalm2mInstObj_t *pInstObj;
    vpscoreCalm2mHndlObj_t *pHndlObj;

    if(NULL != handle)
    {
        pHndlObj = (vpscoreCalm2mHndlObj_t *) (handle);

        hndlIndex = pHndlObj->hndlIndex;

        instId = pHndlObj->instId;
        GT_assert(VpsIssCoreTrace, (VPSCORE_CALM2M_MAX_INST > instId));
        pInstObj = &gInstObjs[instId];

        if(TRUE == pInstObj->isRequestActive)
        {
            if(NULL != pInstObj->pActiveHndlObj)
            {
                /* Trying to close while request is active */
                GT_assert(VpsIssCoreTrace, FALSE);
            }
        }

        if(NULL != pInstObj->pHndlObjs[hndlIndex])
        {
            pInstObj->pHndlObjs[hndlIndex] = NULL;
        }

        retVal           = Vps_iemUnRegister(pHndlObj->iemHandle);
        pInstObj->regIsr = (uint32_t) FALSE;
        if(NULL != pInstObj->calm2mHalHandle)
        {
            VpsHal_isscalClose(pInstObj->calm2mHalHandle, NULL);
        }

        retVal = BSP_SOK;
    }
    return retVal;
}

VpsCore_Handle vcoreCalm2mOpen(VpsCore_Inst            instId,
                               const VpsCore_OpenPrms *openPrms,
                               const void             *coreOpenPrms,
                               void                   *coreReturnPrms)
{
    int32_t                   status = FVID2_SOK;
    uint32_t                  i, hndlIndex;
    uint32_t                  inst;
    vpscoreCalm2mInstObj_t   *pInstObj     = NULL;
    vpscoreCalm2mHndlObj_t   *pHndlObj     = NULL;

    isshalCalOpenParams_t     calOpenPrms;
    issemClientCbFxn          isrPtr = NULL;

    if((NULL == openPrms) || (NULL == coreOpenPrms) ||
       (NULL == coreReturnPrms))
    {
        status = FVID2_EBADARGS;
    }

    inst = (uint32_t) instId;
    if(VPSCORE_CALM2M_MAX_INST > inst)
    {
        status   = BSP_SOK;
        pInstObj = &gInstObjs[inst];
    }
    else
    {
        status   = BSP_EFAIL;
        pInstObj = NULL;
    }
    if(BSP_SOK == status)
    {
        status = BSP_EFAIL;
        for(i = 0; ((i < ISSCORE_CALM2M_MAX_SW_HANDLES) && (NULL != pInstObj));
            i++)
        {
            if(NULL == pInstObj->pHndlObjs[i])
            {
                status    = BSP_SOK;
                hndlIndex = i;
                break;
            }
        }

        if(BSP_SOK == status)
        {
            pInstObj->pHndlObjs[hndlIndex] = (VpsCore_Handle)
                                             & pInstObj->hndlObjsPool[hndlIndex
                                             ];
            pHndlObj = &pInstObj->hndlObjsPool[hndlIndex];
        }
    }

    if(FVID2_SOK == status)
    {
        calOpenPrms.instId = 2;
        calOpenPrms.mode   = VPS_HAL_ISS_CAL_MODE_M2M;
        pInstObj->calm2mHalHandle = VpsHal_isscalOpen(&calOpenPrms, NULL);
        if(NULL == pInstObj->calm2mHalHandle)
        {
            status = FVID2_EFAIL;
        }
    }

    if(BSP_SOK == status)
    {
        pHndlObj->instId    = inst;
        pHndlObj->hndlIndex = hndlIndex;
        BspUtils_memcpy(&pHndlObj->openPrms,
                        openPrms,
                        sizeof(VpsCore_OpenPrms));

        /* Initialize the dma cfg params to default. */
        pHndlObj->dmaCfg.bwLimit    = 9U; /* Set to min value. */
        pHndlObj->dmaCfg.ocpTagCnt  = 0x1U;
        pHndlObj->dmaCfg.pixClock   = 0x10000U; /* Set to max value. */
        if(FALSE == pInstObj->regIsr)
        {
            isrPtr = &vcoreCalm2mIsr;
            pHndlObj->iemHandle = Vps_iemregister(
                pInstObj->initPrms.irqNum,
                pInstObj->initPrms.eventGroup,
                &pInstObj->initPrms.eventNum,
                1u,
                IEM_PRIORITY4,
                isrPtr,
                (Ptr) pInstObj);
            GT_assert(VpsIssCoreTrace, (NULL != pHndlObj->iemHandle));
            if(NULL != pHndlObj->iemHandle)
            {
                pInstObj->pCurrHndl = NULL;
            }
            else
            {
                /* TODO TBD Release resources */

                pHndlObj = NULL;
            }
        }
    }
    return (VpsCore_Handle) (pHndlObj);
}
static int32_t vcoreCalm2mValidateParam (const vpsissCalm2mParams_t *pCalm2mPrm)
{
    int32_t retVal = FVID2_SOK;
    if(pCalm2mPrm->inPixExtract != VPS_ISS_CAL_PIX_EXRCT_B12_MIPI)
    {
        /* Only supports 12 bit MIPI input format. */
        retVal = FVID2_EBADARGS;
    }
    if(pCalm2mPrm->outPixPack != VPS_ISS_CAL_PIX_PACK_B16)
    {
        /* Only supports Convertion to 16 bit unpacked format. */
        retVal = FVID2_EBADARGS;
    }
    return retVal;
}

/**
 *  vcoreCalm2mSetConfig
 *  \brief Set configuration for specified SIMCOP handle
 *
 *  \param params      Configuration of type #vpsissSimcopCfgPrms_t
 *  \param rsvd        Unused argument. Value is don't care.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreCalm2mSetConfig(VpsCore_Handle handle,
                             const void    *params,
                             void          *rsvd)
{
    int32_t status = BSP_EBADARGS;
    vpscoreCalm2mHndlObj_t      *pHndlObj;
    vpscoreCalm2mInstObj_t      *pInstObj;
    const vpsissCalm2mParams_t  *cfg;
    uint32_t cookie;

    /* Check active processing, Mark active */
    cookie = BspOsal_disableInterrupt();

    if(NULL != handle)
    {
        pHndlObj = (vpscoreCalm2mHndlObj_t *) (handle);

        if(VPSCORE_CALM2M_MAX_INST > pHndlObj->instId)
        {
            pInstObj = &gInstObjs[pHndlObj->instId];

            if(pHndlObj == pInstObj->pActiveHndlObj)
            {
                status = FVID2_EDEVICE_INUSE;
            }
            else
            {
                status = FVID2_SOK;
            }
        }
    }

    if(FVID2_SOK == status)
    {
        cfg = (const vpsissCalm2mParams_t *) (params);
        status = vcoreCalm2mValidateParam (cfg);
    }
    if(FVID2_SOK == status)
    {
        BspUtils_memcpy(&(pHndlObj->cfg),
                        params,
                        sizeof(vpsissCalm2mParams_t));

        /* Config has been updated, ensure to apply this when the first frame is
         *  received to be processed */
        pInstObj = &gInstObjs[pHndlObj->instId];
        if(pInstObj->pCurrHndl == pHndlObj)
        {
            pInstObj->pCurrHndl = NULL;
        }
        status = BSP_SOK;
    }
    BspOsal_restoreInterrupt(cookie);

    return status;
}

/**
 *  vcoreCalm2mControl
 *  \brief Function to get/set control commands
 *
 *  \param handle      core handle
 *  \param cmd         Command ID
 *  \param cmdArgs     Command Specific Arguments
 *  \param drvArgs     Driver specific arguments
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreCalm2mControl(VpsCore_Handle handle,
                           UInt32         cmd,
                           void          *appArgs,
                           void          *drvArgs)
{
    int32_t status = BSP_EBADARGS;
    vpscoreCalm2mHndlObj_t *pHndlObj;
    vpscoreCalm2mInstObj_t *pInstObj;
    vpsissCalm2mDmaCtrlParams_t  *pCalm2mDmaCfg;

    if(NULL != handle)
    {
        pHndlObj = (vpscoreCalm2mHndlObj_t *) (handle);

        if(VPSCORE_CALM2M_MAX_INST > pHndlObj->instId)
        {
            pInstObj = &gInstObjs[pHndlObj->instId];

            if(TRUE == pInstObj->isRequestActive)
            {
                status = FVID2_EDEVICE_INUSE;
            }
            else
            {
                status = FVID2_SOK;
            }
        }
    }

    if(FVID2_SOK == status)
    {
        switch (cmd)
        {
            case VPS_ISS_CALM2M_IOCTL_SET_DMA_PARAMS:
                pCalm2mDmaCfg = (vpsissCalm2mDmaCtrlParams_t*)appArgs;
                BspUtils_memcpy(&(pHndlObj->dmaCfg),
                                pCalm2mDmaCfg,
                                sizeof(vpsissCalm2mDmaCtrlParams_t));
                /* Config has been updated, ensure to apply this when the first frame is
                *  received to be processed */
                pInstObj = &gInstObjs[pHndlObj->instId];
                if(pInstObj->pCurrHndl == pHndlObj)
                {
                    pInstObj->pCurrHndl = NULL;
                }
                status = BSP_SOK;

                break;

            default:
                break;
        }
    }

    return status;
}

/**
 *  vcoreCalm2mPutFrames
 *  \brief Sets up the SIMCOP to perform required operation.
 *
 *  \param handle   Handle returned by open API
 *  \param frm      Pointer to array if VpsCore_Frame pointer, depending on the
 *                  requested operation, one or more frames should be valid
 *
 *  \return         Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreCalm2mPutFrames(VpsCore_Handle  handle,
                             VpsCore_Frame **frm)
{
    int32_t  retVal = FVID2_EBADARGS;
    vpscoreCalm2mHndlObj_t *pHndlObj;
    vpscoreCalm2mInstObj_t *pInstObj;
    uint32_t cookie;

    if((NULL != handle) && (NULL != frm))
    {
        if((NULL != frm[VPS_CALM2M_STREAM_ID_INPUT_FRAME]) &&
           (NULL != frm[VPS_CALM2M_STREAM_ID_OUT_FRAME]))
        {
            retVal = FVID2_SOK;
        }

        pHndlObj = (vpscoreCalm2mHndlObj_t *) (handle);
        if(VPSCORE_CALM2M_MAX_INST <= pHndlObj->instId)
        {
            retVal = FVID2_EBADARGS;
        }

        if(FVID2_SOK == retVal)
        {
            pInstObj = &gInstObjs[pHndlObj->instId];

            /* Check active processing, Mark active */
            cookie = BspOsal_disableInterrupt();
            if(TRUE != pInstObj->isRequestActive)
            {
                pInstObj->isRequestActive = (uint32_t) TRUE;
                pInstObj->pActiveHndlObj  = pHndlObj;
            }
            else
            {
                retVal = FVID2_EDEVICE_INUSE;
            }
            BspOsal_restoreInterrupt(cookie);
        }
    }

    if(FVID2_SOK == retVal)
    {
        retVal = vcoreCalm2mPutFramesInternal(handle,
                                              (const VpsCore_Frame **)frm);
        if(FVID2_SOK != retVal)
        {
            /* For some other reason, we could start processing */
            cookie = BspOsal_disableInterrupt();
            pInstObj->isRequestActive = (uint32_t) FALSE;
            pInstObj->pActiveHndlObj  = NULL;
            BspOsal_restoreInterrupt(cookie);
        }
    }
    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void vcoreCalm2mIsr(const UInt32 *event,
                                   UInt32        numEvents,
                                   Ptr           handle)
{
    uint32_t cookie;
    int32_t  retVal = BSP_SOK;
    vpscoreCalm2mHndlObj_t *pHndlObj;
    vpscoreCalm2mInstObj_t *pInstObj;

    GT_assert(VpsIssCoreTrace, (NULL != handle));
    GT_assert(VpsIssCoreTrace, (NULL != event));

    pInstObj = (vpscoreCalm2mInstObj_t *)(handle);
    GT_assert(VpsIssCoreTrace, (NULL != pInstObj->pActiveHndlObj));
    GT_assert(VpsIssCoreTrace, (FALSE != pInstObj->isRequestActive));
    pHndlObj = pInstObj->pActiveHndlObj;

    if(*event != pInstObj->initPrms.eventNum)
    {
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        cookie = BspOsal_disableInterrupt();
        pInstObj->isRequestActive = (uint32_t) FALSE;
        pInstObj->pActiveHndlObj  = NULL;
        BspOsal_restoreInterrupt(cookie);
        if(NULL != pHndlObj->openPrms.frmDoneNotifyCb)
        {
            /* Call the calback of the upper layer */
            pHndlObj->openPrms.frmDoneNotifyCb(pHndlObj->openPrms.drvData);
        }
    }
}

static int32_t vcoreCalm2mApplyConfig(VpsCore_Handle        handle,
                                      vpsissCalm2mParams_t cfg)
{
    int32_t retVal = FVID2_SOK;
    vpscoreCalm2mHndlObj_t *pHndlObj;
    vpscoreCalm2mInstObj_t *pInstObj;
    isshalCalCfg_t calCfg = {0};
    isshalCalDmaVcCfg_t dmaCfg = {0};

    pHndlObj = (vpscoreCalm2mHndlObj_t *) (handle);
    pInstObj = &gInstObjs[pHndlObj->instId];

    calCfg.numCPortId = 1U;
    calCfg.cportId[0] = 0U; /* For M2M Cport id is always 0. */
    calCfg.virtualChanNum[0] = 0U;

    /* Set Pix Proc Config. */
    calCfg.isPixProcCfgValid[0] = TRUE;
    calCfg.pixProcCfg[0].decCodec = VPS_ISS_CAL_DPCM_DEC_BYPASS;
    calCfg.pixProcCfg[0].encCodec = VPS_ISS_CAL_DPCM_ENC_BYPASS;
    calCfg.pixProcCfg[0].enableDpcmInitContext = FALSE;
    calCfg.pixProcCfg[0].extract = cfg.inPixExtract;
    calCfg.pixProcCfg[0].pack = cfg.outPixPack;

    calCfg.isBysOutCfgValid[0] = (uint32_t) FALSE;
    calCfg.isBysInCfgValid[0]  = (uint32_t) FALSE;
    calCfg.isVportCfgValid[0]  = (uint32_t) FALSE;

    /* Set dam Cfg params. */
    dmaCfg.numCPortId = calCfg.numCPortId;
    dmaCfg.cportId[0] = calCfg.cportId[0];
    dmaCfg.isCsi2VcCfgValid[0] = (uint32_t) FALSE; /* Not applicable for M2M mode. */

    dmaCfg.isWrDmaCfgValid[0] = (uint32_t) TRUE;
    dmaCfg.wrDmaCfg[0U].contextToBeUsed  = 0x0;
    dmaCfg.wrDmaCfg[0U].mode             = VPS_HAL_ISS_CAL_DMA_WR_CONST;
    dmaCfg.wrDmaCfg[0U].stream           = VPS_ISS_CAL_TAG_PIX_DATA;
    dmaCfg.wrDmaCfg[0U].stallM2MRd       = (uint32_t)TRUE;
    dmaCfg.wrDmaCfg[0U].ySkipMode        = 0x0;
    dmaCfg.wrDmaCfg[0U].xPixelSkip       = 0x0;
    dmaCfg.wrDmaCfg[0U].format.width     = cfg.outWidth;
    dmaCfg.wrDmaCfg[0U].format.height    = cfg.outHeight;
    dmaCfg.wrDmaCfg[0U].format.pitch[0U] = cfg.outPitch;

    dmaCfg.isRdDmaCfgValid[0] = (uint32_t) TRUE;
    dmaCfg.rdDmaCfg[0].enable = (uint32_t) TRUE;
    dmaCfg.rdDmaCfg[0].format.width      = cfg.inWidth;
    dmaCfg.rdDmaCfg[0].format.height     = cfg.inHeight;
    dmaCfg.rdDmaCfg[0].format.bpp        = cfg.inBpp;
    dmaCfg.rdDmaCfg[0].format.pitch[0]   = cfg.inPitch;
    dmaCfg.rdDmaCfg[0].bwLimit           = pHndlObj->dmaCfg.bwLimit;
    dmaCfg.rdDmaCfg[0].ocpTagCnt         = pHndlObj->dmaCfg.ocpTagCnt;
    dmaCfg.rdDmaCfg[0].pixClock          = pHndlObj->dmaCfg.pixClock;
    
    calCfg.pDmaVcCfg = &dmaCfg;

    retVal = VpsHal_isscalControl(pInstObj->calm2mHalHandle,
                                  VPS_HAL_ISS_IOCTL_CAL_SETCFG,
                                  &calCfg,
                                  NULL);
    return retVal;
}

static int32_t vcoreCalm2mPutFramesInternal(VpsCore_Handle      handle,
                                            const VpsCore_Frame ** const frm)
{
    int32_t retVal = FVID2_SOK;
    int32_t applyConfig = (int32_t) FALSE;
    vpscoreCalm2mHndlObj_t *pHndlObj;
    vpscoreCalm2mInstObj_t *pInstObj;
    isshalCalBufferAddr_t   calBuf;

    pHndlObj = (vpscoreCalm2mHndlObj_t *) (handle);
    pInstObj = &gInstObjs[pHndlObj->instId];

    if(pInstObj->pCurrHndl != pHndlObj)
    {
        applyConfig         = (int32_t) TRUE;
        pInstObj->pCurrHndl = pHndlObj;
    }
    if (applyConfig == (int32_t) TRUE)
    {
        /* Update the cal Configuration */
        retVal = vcoreCalm2mApplyConfig(pHndlObj, pHndlObj->cfg);
    }
    /* Update the buffers. */
    if(retVal == BSP_SOK)
    {
        calBuf.numBuff = 2U;
        /* One input buffer RDdma, one output buffer WRdma. */
        calBuf.wrDmaCtx[0] = 0U;
        calBuf.wrDmaCtx[1] = 0U;

        calBuf.cPortId[0]  = 0U; /* Input Buffer. */
        calBuf.cPortId[1]  = 1U; /* Output Buffer. */

        calBuf.buffAddr[0] = (UInt32) (frm[VPS_CALM2M_STREAM_ID_INPUT_FRAME]->addr[0][0]);
        calBuf.pitch[0]    = pHndlObj->cfg.inPitch;
        calBuf.buffAddr[1] = (UInt32) (frm[VPS_CALM2M_STREAM_ID_OUT_FRAME]->addr[0][0]);
        VpsHal_isscalUpdateBufAddr(pInstObj->calm2mHalHandle,
                                   &calBuf);
    }
    if(retVal == BSP_SOK)
    {
        retVal = VpsHal_isscalRdDmaStart(pInstObj->calm2mHalHandle,
                                         ISSHAL_ISS_PROC_MODE_ONE_SHOT,
                                         NULL);
    }
    return retVal;
}

