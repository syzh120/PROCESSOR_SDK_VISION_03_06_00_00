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
 *  \file vpscore_vpeApi.c
 *
 *  \brief VPS VPE input path core file.
 *  This file implements the core layer for VPE path containing
 *  VC Range mapping, CHRUS, DEI, SC, CSC and CHR_DS.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/src/vpslib/vpecore/src/vpscore_vpePriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */

#ifdef __cplusplus
extern "C" {
#endif

static Vcore_M2mHandle Vcore_vpeOpen(UInt32 instId, UInt32 numCh);
static Int32 Vcore_vpeClose(Vcore_M2mHandle handle);

static Int32 Vcore_vpeGetProperty(Vcore_M2mHandle    handle,
                                  Vcore_M2mProperty *property);

static Int32 Vcore_vpeSetParams(Vcore_M2mHandle handle,
                                UInt32          chNum,
                                const void     *prms);
static Int32 Vcore_vpeGetParams(Vcore_M2mHandle handle,
                                UInt32          chNum,
                                void           *prms);

static Int32 Vcore_vpeGetDescInfo(Vcore_M2mHandle    handle,
                                  UInt32             chNum,
                                  Vcore_M2mDescInfo *descInfo);
static Int32 Vcore_vpeGetDeiCtxInfo(Vcore_M2mHandle      handle,
                                    UInt32               chNum,
                                    Vcore_M2mDeiCtxInfo *ctxInfo);
static Int32 Vcore_vpeSetFsEvent(Vcore_M2mHandle         handle,
                                 UInt32                  chNum,
                                 VpsHal_VpdmaFSEvent     fsEvent,
                                 const Vcore_M2mDescMem *descMem);

static Int32 Vcore_vpeControl(Vcore_M2mHandle handle, UInt32 cmd, Ptr args);

static Int32 Vcore_vpeProgramDesc(Vcore_M2mHandle         handle,
                                  UInt32                  chNum,
                                  const Vcore_M2mDescMem *descMem);
static Int32 Vcore_vpeProgramReg(Vcore_M2mHandle         handle,
                                 UInt32                  chNum,
                                 const Vcore_M2mDescMem *descMem);

static Int32 Vcore_vpeProgramFmdReg(Vcore_M2mHandle         handle,
                                    const Vps_DeiFmdConfig *fmdCfg,
                                    const Vcore_M2mDescMem *descMem);

static Int32 Vcore_vpeProgramFmdUpdateReg(Vcore_M2mHandle               handle,
                                          const Vps_DeiFmdUpdateConfig *fmdCfg,
                                          const Vcore_M2mDescMem       *descMem);

static Int32 Vcore_vpeUpdateDesc(Vcore_M2mHandle         handle,
                                 const Vcore_M2mDescMem *descMem,
                                 const Fvid2_Frame      *frame,
                                 UInt32                  fid);

static Int32 Vcore_vpeUpdateContext(Vcore_M2mHandle         handle,
                                    UInt32                  chNum,
                                    const Vcore_M2mDescMem *descMem,
                                    const void             *ctx);
static Int32 Vcore_vpeUpdateRtMem(Vcore_M2mHandle         handle,
                                  const Vcore_M2mDescMem *descMem,
                                  UInt32                  chNum,
                                  const void             *rtPrms,
                                  UInt32                  frmIdx);
static Int32 Vcore_vpeProgramUserCoeff(
    const Vcore_M2mHandle handle,
    UInt32                chNum,
    const Vcore_M2mScUserCoeffParams *
    userCoeffPrms);
static Int32 Vcore_vpeGetScCoeff(Vcore_M2mHandle            handle,
                                 UInt32                     chNum,
                                 Vcore_M2mScGetCoeffParams *getCoeffPrms);
static Int32 Vcore_vpeUpdateMode(Vcore_M2mHandle         handle,
                                 UInt32                  chNum,
                                 const Vcore_M2mDescMem *descMem,
                                 UInt32                  prevFldState);
static Int32 Vcore_vpeGetScFactorConfig(Vcore_M2mHandle        handle,
                                        UInt32                 chNum,
                                        VpsHal_ScFactorConfig *scFactorCfg);
#ifdef __cplusplus
}
#endif

static Int32 vcoreVpeUpdateRtPrms(const Vcore_VpeInstObj  *instObj,
                                  Vcore_VpeChObj          *chObj,
                                  const Vcore_VpeRtParams *rtPrms);
static Int32 vcoreVpeUpdateRtDescMem(const Vcore_VpeInstObj *instObj,
                                     const Vcore_VpeChObj   *chObj,
                                     const Vcore_M2mDescMem *descMem);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief VPE path core function pointer. */
static const Vcore_M2mOps gVpeCoreOps =
{
    &Vcore_vpeGetProperty,
    /* Get property */
    &Vcore_vpeOpen,
    /* Open function */
    &Vcore_vpeClose,
    /* Close function */
    NULL,
    /* Set format */
    NULL,
    /* Get format */
    &Vcore_vpeGetDescInfo,
    /* Get descriptor info */
    &Vcore_vpeSetFsEvent,
    /* Set frame */
    &Vcore_vpeSetParams,
    /* Set parameters */
    &Vcore_vpeGetParams,
    /* Get parameters */
    &Vcore_vpeControl,
    /* Control */
    &Vcore_vpeProgramDesc,
    /* Program descriptor */
    &Vcore_vpeProgramReg,
    /* Program register */
    &Vcore_vpeUpdateDesc,
    /* Update descriptor */
    &Vcore_vpeGetDeiCtxInfo,
    /* Get DEI context info */
    &Vcore_vpeUpdateContext,
    /* Update context descriptor */
    &Vcore_vpeUpdateRtMem,
    /* Update runtime params */
    &Vcore_vpeProgramUserCoeff,
    /* Program user scaler coefficient */
    &Vcore_vpeGetScCoeff,
    /* Get scaler coefficient */
    &Vcore_vpeUpdateMode,
    /* Update the mode in DEI */
    &Vcore_vpeGetScFactorConfig,
    /* Get scaling factor config */
    &Vcore_vpeProgramFmdReg,
    /* Program FMD register */
    &Vcore_vpeProgramFmdUpdateReg
    /* Program FMD update register */
};

/** \brief Properties of this core. */
static Vcore_M2mProperty  gVcoreVpeProperty;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  Vcore_vpeInit
 *  \brief VPE core init function.
 *  Initializes VPE core objects, allocates memory etc.
 *  This function should be called before calling any of VPE core API's.
 *
 *  \param numInst      [IN] Number of instance objects to be initialized.
 *  \param initPrms     [IN] Pointer to the init parameter containing
 *                      instance specific information. If the number of
 *                      instance is greater than 1, then this pointer
 *                      should point to an array of init parameter
 *                      structure of size numInst.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 Vcore_vpeInit(UInt32                     numInst,
                    const Vcore_VpeInitParams *initPrms)
{
    Int32 retVal = BSP_SOK;

    /* Check for errors */
    GT_assert(VpsVpeCoreTrace, numInst <= VCORE_VPE_INST_MAX);
    GT_assert(VpsVpeCoreTrace, NULL != initPrms);

    /* Initialize the internal objects */
    retVal = vcoreVpeInit(numInst, initPrms);
    if (BSP_SOK == retVal)
    {
        /* Initialize DEI path core properties */
        gVcoreVpeProperty.numInstance     = numInst;
        gVcoreVpeProperty.name            = VCORE_M2M_VPE;
        gVcoreVpeProperty.type            = VCORE_M2M_TYPE_INPUT;
        gVcoreVpeProperty.internalContext = TRUE;
    }

    /* Cleanup if error occurs */
    if (BSP_SOK != retVal)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Init Failed!!\r\n");
        Vcore_vpeDeInit();
    }

    return (retVal);
}

/**
 *  Vcore_vpeDeInit
 *  \brief DEI core exit function.
 *  Deallocates memory allocated by init function.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 Vcore_vpeDeInit(void)
{
    Int32 retVal = BSP_SOK;

    retVal = vcoreVpeDeInit();
    gVcoreVpeProperty.numInstance = 0U;

    return (retVal);
}

/**
 *  Vcore_vpeGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const Vcore_M2mOps *Vcore_vpeGetCoreOps(void)
{
    return &gVpeCoreOps;
}

/**
 *  Vcore_vpeOpen
 *  \brief Opens a particular instance of DEI path in either display
 *  or in M2M mode and returns the handle to the handle object.
 *  When opened in display mode, only one handle could be opened. Also
 *  only one channel is supported.
 *  When opened in M2M mode, the same instance could be opened more than
 *  once. The number of handles supported per instance is determined by
 *  VCORE_VPE_MAX_HANDLES macro. Also each of the handles could have multiple
 *  channel to support more than one M2M operation is a single request.
 *
 *  \param instId       [IN] Instance to open.
 *  \param numCh        [IN] Number of channel to be associated with this open.
 *                      For display operation only one channel is allowed.
 *                      For M2M operation, more than one channel could
 *                      be associated with a handle.
 *                      The maximum supported channel per handle depends on
 *                      VCORE_VPE_MAX_CHANNELS macro.
 *
 *  \return             If success returns the handle else returns NULL.
 */
static Vcore_M2mHandle Vcore_vpeOpen(UInt32 instId, UInt32 numCh)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeHandleObj *hObj = NULL;

    /* Only display and memory modes are supported */
    /* Check for maximum channel supported per handle */
    GT_assert(VpsVpeCoreTrace, numCh <= VCORE_VPE_MAX_CHANNELS);
    /* There should be atleast one channel */
    GT_assert(VpsVpeCoreTrace, 0U != numCh);

    /* Allocate a handle object */
    hObj = vcoreVpeAllocHandleObj(instId);
    if (NULL != hObj)
    {
        /* Allocate channel objects */
        retVal = vcoreVpeAllocChObjs(hObj, numCh);
        if (BSP_SOK != retVal)
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR, "Channel allocation failed!!\r\n");
            /* Free-up handle object if channel allocation failed */
            vcoreVpeFreeHandleObj(hObj);
            hObj = NULL;
        }
        else
        {
            /* Initialize variables */
            hObj->numCh = numCh;
        }
    }
    else
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Handle allocation failed!!\r\n");
    }

    return (Vcore_M2mHandle) hObj;
}

/**
 *  Vcore_vpeClose
 *  \brief Closes the already opened handle.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeClose(Vcore_M2mHandle handle)
{
    Int32 retVal = BSP_EFAIL;
    Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    hObj = (Vcore_VpeHandleObj *) handle;

    /* Free channel and handle objects */
    retVal  = vcoreVpeFreeChObjs(hObj, hObj->numCh);
    retVal += vcoreVpeFreeHandleObj(hObj);
    if (BSP_SOK != retVal)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Free memory failed!!\r\n");
    }

    return (retVal);
}

/**
 *  Vcore_vpeGetProperty
 *  \brief Gets the core properties of the VPE path core.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param property     [OUT] Pointer to which the VPE path core properties
 *                      to be copied.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeGetProperty(Vcore_M2mHandle    handle,
                                  Vcore_M2mProperty *property)
{
    Vcore_VpeInstObj *instObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != property);
    instObj = ((Vcore_VpeHandleObj *) handle)->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    BspUtils_memcpy(property, &gVcoreVpeProperty, sizeof (Vcore_M2mProperty));

    return (BSP_SOK);
}

/**
 *  Vcore_vpeSetParams
 *  \brief Sets the VPE core parameters for a given channel.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel to which the params should be applied.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param prms         [IN] Pointer to the params information. This should
 *                      point to a valid Vcore_VpeParams structure.
 *                      This parameter should be non-NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeSetParams(Vcore_M2mHandle handle,
                                UInt32          chNum,
                                const void     *prms)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeChObj        *chObj;
    Vcore_VpeInstObj      *instObj;
    Vcore_VpeHandleObj    *hObj;
    const Vcore_VpeParams *corePrms;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != prms);
    hObj     = (Vcore_VpeHandleObj *) handle;
    corePrms = (const Vcore_VpeParams *) prms;
    instObj  = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        /* Check whether the parameters are valid */
        retVal = vcoreVpeCheckParams(instObj, corePrms);
        if (BSP_SOK != retVal)
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid Parameters!!\r\n");
        }
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        /* Set the parameters for each channel */
        retVal = vcoreVpeSetChParams(instObj, chObj, corePrms);
        if (BSP_SOK != retVal)
        {
            GT_1trace(VpsVpeCoreTrace, GT_ERR,
                      "Set parameter failed for channel %d!!\r\n", chNum);
        }
    }

    return (retVal);
}

/**
 *  Vcore_vpeGetParams
 *  \brief Gets the VPE core parameters for a given channel.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel from which the params should be read.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param prms         [OUT] Pointer to the copied params information. This
 *                      should point to a valid Vcore_VpeParams structure.
 *                      This parameter should be non-NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeGetParams(Vcore_M2mHandle handle,
                                UInt32          chNum,
                                void           *prms)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeChObj *chObj;
    Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != prms);
    hObj = (Vcore_VpeHandleObj *) handle;

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        /* Copy the params */
        BspUtils_memcpy(prms, &chObj->corePrms, sizeof (Vcore_VpeParams));
    }

    return (retVal);
}

/**
 *  Vcore_vpeGetDescInfo
 *  \brief Depending on the params set and the layout ID, returns the number of
 *  data descriptors and config overlay memory needed for the actual driver to
 *  allocate memory.
 *  Params should have be set for each of the channel before calling this
 *  function.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel to which the info is required.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param descInfo     [OUT] Pointer to the number of data descriptor and
 *                      config overlay memory size information.
 *                      This parameter should be non-NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeGetDescInfo(Vcore_M2mHandle    handle,
                                  UInt32             chNum,
                                  Vcore_M2mDescInfo *descInfo)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeChObj     *chObj;
    Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != descInfo);
    hObj = (Vcore_VpeHandleObj *) handle;

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isParamsSet)
        {
            GT_0trace(
                VpsVpeCoreTrace, GT_ERR,
                "Set the parameter before getting the descriptor info!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Copy descriptor information from non-mosaic info */
        BspUtils_memcpy(
            (Ptr) descInfo,
            &chObj->descInfo,
            sizeof (Vcore_M2mDescInfo));
    }

    return (retVal);
}

/**
 *  Vcore_vpeGetDeiCtxInfo
 *  \brief Depending on the params set, returns the number of DEI context
 *  buffers needed for the actual driver to allocate memory.
 *  Params should have be set for each of the channel before calling this
 *  function.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel to which the info is required.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param ctxInfo      [OUT] Pointer to the context buffer information.
 *                      This parameter should be non-NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeGetDeiCtxInfo(Vcore_M2mHandle      handle,
                                    UInt32               chNum,
                                    Vcore_M2mDeiCtxInfo *ctxInfo)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeChObj     *chObj;
    Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != ctxInfo);
    hObj = (Vcore_VpeHandleObj *) handle;

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isParamsSet)
        {
            GT_0trace(
                VpsVpeCoreTrace, GT_ERR,
                "Set the parameter before getting the descriptor info!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Copy the context buffer information */
        BspUtils_memcpy(
            (Ptr) ctxInfo,
            &chObj->ctxInfo,
            sizeof (Vcore_M2mDeiCtxInfo));
    }

    return (retVal);
}

/**
 *  Vcore_vpeSetFsEvent
 *  \brief Program the client's frame start.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param fsEvent      [IN] Frame start event.
 *  \param descMem      [IN] Pointer to the overlay memory information.
 *                      If this parameter is NULL, then the configuration
 *                      is written to the actual registers. Otherwise the
 *                      configuration is updated in the overlay memory.
 *                      This parameter can be NULL depending on the
 *                      intended usage.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeSetFsEvent(Vcore_M2mHandle         handle,
                                 UInt32                  chNum,
                                 VpsHal_VpdmaFSEvent     fsEvent,
                                 const Vcore_M2mDescMem *descMem)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeChObj     *chObj;
    Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    hObj = (Vcore_VpeHandleObj *) handle;

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        retVal = BSP_EOUT_OF_RANGE;
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isParamsSet)
        {
            GT_0trace(
                VpsVpeCoreTrace, GT_ERR,
                "Set the parameter before setting the frame start event!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Set the frame start event */
        chObj->fsEvent = fsEvent;
        retVal         = vcoreVpeSetFsEvent(hObj->instObj, chObj, descMem);
    }

    return (retVal);
}

/**
 *  Vcore_vpeControl
 *  \brief To handle control Command.
 *
 *  \param handle       VPE Path Core handle.
 *  \param cmd          Control Command
 *  \param args         Command Specific Argument
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeControl(Vcore_M2mHandle handle, UInt32 cmd, Ptr args)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    hObj = (Vcore_VpeHandleObj *) handle;

    switch (cmd)
    {
        case VCORE_M2M_IOCTL_SET_DEI_CFG:
            GT_assert(VpsVpeCoreTrace, NULL != args);
            retVal = vcoreVpeSetAdvCfgIoctl(hObj, (Vps_DeiRdWrAdvCfg *) args);
            break;

        case VCORE_M2M_IOCTL_GET_DEI_CFG:
            GT_assert(VpsVpeCoreTrace, NULL != args);
            retVal = vcoreVpeGetAdvCfgIoctl(hObj, (Vps_DeiRdWrAdvCfg *) args);
            break;

        case VCORE_M2M_IOCTL_SET_SC_CFG:
            GT_assert(VpsVpeCoreTrace, NULL != args);
            retVal = vcoreVpeScSetAdvCfgIoctl(
                hObj,
                (Vcore_M2mScCfgParams *) args);
            break;

        case VCORE_M2M_IOCTL_GET_SC_CFG:
            GT_assert(VpsVpeCoreTrace, NULL != args);
            retVal = vcoreVpeScGetAdvCfgIoctl(
                hObj,
                (Vcore_M2mScCfgParams *) args);
            break;

        case VCORE_M2M_IOCTL_GET_DEI_FMD_STAT:
            retVal = vcoreVpeGetFmdStatIoctl(
                hObj,
                (Vps_DeiFmdStatusReg *) args);
            break;

        case VCORE_M2M_IOCTL_SET_RANGE_MAP_REDUCT_CFG:
            GT_assert(VpsVpeCoreTrace, NULL != args);
            retVal = vcoreVpeSetRangMapRedtCfgIoctl(
                hObj,
                (Vps_RngMapRdtCfg *) args);
            break;

        case VCORE_M2M_IOCTL_GET_RANGE_MAP_REDUCT_CFG:
            GT_assert(VpsVpeCoreTrace, NULL != args);
            retVal = vcoreVpeGetRangMapRedtCfgIoctl(
                hObj,
                (Vps_RngMapRdtCfg *) args);
            break;

        default:
            GT_0trace(VpsVpeCoreTrace, GT_ERR, "Unsupported IOCTL\r\n");
            retVal = BSP_EUNSUPPORTED_CMD;
            break;
    }

    return (retVal);
}

/**
 *  Vcore_vpeProgramDesc
 *  \brief Programs the data descriptor for a given channel depending on the
 *  layout ID passed. This will not program the internal context descriptors.
 *  Only after programming the data descriptor for each of the channel,
 *  the actual driver is supposed to call the update buffer function.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param descMem      [IN] Pointer to the data descriptor memory information.
 *                      This parameter should be non-NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeProgramDesc(Vcore_M2mHandle         handle,
                                  UInt32                  chNum,
                                  const Vcore_M2mDescMem *descMem)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeChObj     *chObj;
    Vcore_VpeInstObj   *instObj;
    Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);
    hObj    = (Vcore_VpeHandleObj *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isParamsSet)
        {
            GT_0trace(
                VpsVpeCoreTrace, GT_ERR,
                "Set the parameter before programming the descriptors!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    /* Program descriptors */
    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeProgramDesc(instObj, chObj, descMem);
    }

    /* Configure previous field descriptors */
    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeProgramPrevFldDesc(instObj, chObj, descMem);
    }
    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeProgramCurOutDesc(instObj, chObj, descMem);
    }
    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeProgramMvDesc(instObj, chObj, descMem);
    }
    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeProgramMvstmDesc(instObj, chObj, descMem);
    }
    return (retVal);
}

/**
 *  Vcore_vpeProgramReg
 *  \brief Programs the registers for each of the HALs through direct
 *  register programming if descMem is NULL else creates and programs the
 *  overlay memory. The upper driver has to submit the programmed overlay
 *  to the VPDMA to do the actual register programming.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param descMem      [IN] Pointer to the overlay memory information.
 *                      If this parameter is NULL, then the configuration
 *                      is written to the actual registers. Otherwise the
 *                      configuration is updated in the overlay memory.
 *                      This parameter can be NULL depending on the
 *                      intended usage.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeProgramReg(Vcore_M2mHandle         handle,
                                 UInt32                  chNum,
                                 const Vcore_M2mDescMem *descMem)
{
    Int32  retVal = BSP_SOK;
    UInt32 halCnt;
    void  *cfgOvlyPtr = NULL;
    Vcore_VpeChObj     *chObj;
    Vcore_VpeInstObj   *instObj;
    Vcore_VpeHandleObj *hObj;
    UInt32 ovlyPtrVal;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    hObj    = (Vcore_VpeHandleObj *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isParamsSet)
        {
            GT_0trace(
                VpsVpeCoreTrace, GT_ERR,
                "Set the parameter before programming the overlay memory!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        if (NULL != descMem)
        {
            /* Check if overlay pointers are non-NULL for required overlay */
            GT_assert(VpsVpeCoreTrace,
                      !((0U != chObj->descInfo.shadowOvlySize)
                        && (NULL == descMem->shadowOvlyMem)));

            /* Create overlay memory for each of the HAL */
            for (halCnt = 0U; halCnt < VCORE_VPE_MAX_HAL; halCnt++)
            {
                ovlyPtrVal = ((UInt32) descMem->shadowOvlyMem +
                              instObj->ovlyOffset[halCnt]);
                cfgOvlyPtr = (void *) ovlyPtrVal;
                if ((NULL != instObj->halHandle[halCnt]) &&
                    (NULL != instObj->createCfgOvly[halCnt]))
                {
                    retVal = instObj->createCfgOvly[halCnt](
                        instObj->halHandle[halCnt],
                        cfgOvlyPtr);
                    if (BSP_SOK != retVal)
                    {
                        GT_1trace(
                            VpsVpeCoreTrace, GT_ERR,
                            "HAL Create Overlay Failed for HAL Id: %d!!\r\n",
                            halCnt);
                        break;
                    }
                }
            }
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Program the registers */
        retVal = vcoreVpeProgramReg(instObj, chObj, descMem);
    }

    return (retVal);
}

/**
 *  Vcore_vpeProgramFmdReg
 *  \brief Programs the Fmd registers for the HAL through direct
 *  register programming if descMem is NULL else creates and programs the
 *  overlay memory. The upper driver has to submit the programmed overlay
 *  to the VPDMA to do the actual register programming.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param fmdCfg       [IN] Pointer to FMD configuration.
 *  \param descMem      [IN] Pointer to the overlay memory information.
 *                      If this parameter is NULL, then the configuration
 *                      is written to the actual registers. Otherwise the
 *                      configuration is updated in the overlay memory.
 *                      This parameter can be NULL depending on the
 *                      intended usage.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeProgramFmdReg(Vcore_M2mHandle         handle,
                                    const Vps_DeiFmdConfig *fmdCfg,
                                    const Vcore_M2mDescMem *descMem)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    hObj = (Vcore_VpeHandleObj *) handle;
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    GT_assert(VpsVpeCoreTrace, NULL != fmdCfg);

    /* Check if the channel is within the range allocated during open */
    if (fmdCfg->chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        /* Program the FMD registers */
        retVal = vcoreVpeProgramFmdReg(hObj, fmdCfg, descMem);
    }

    return (retVal);
}

/**
 *  Vcore_vpeProgramFmdUpdateReg
 *  \brief Programs the Fmd Update registers for the HAL through direct
 *  register programming if descMem is NULL else creates and programs the
 *  overlay memory. The upper driver has to submit the programmed overlay
 *  to the VPDMA to do the actual register programming.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param fmdCfg       [IN] Pointer to FMD Update configuration.
 *  \param descMem      [IN] Pointer to the overlay memory information.
 *                      If this parameter is NULL, then the configuration
 *                      is written to the actual registers. Otherwise the
 *                      configuration is updated in the overlay memory.
 *                      This parameter can be NULL depending on the
 *                      intended usage.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeProgramFmdUpdateReg(Vcore_M2mHandle               handle,
                                          const Vps_DeiFmdUpdateConfig *fmdCfg,
                                          const Vcore_M2mDescMem       *descMem)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    hObj = (Vcore_VpeHandleObj *) handle;
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    GT_assert(VpsVpeCoreTrace, NULL != fmdCfg);

    /* Check if the channel is within the range allocated during open */
    if (fmdCfg->chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        /* Program the FMD Update registers */
        retVal = vcoreVpeProgramFmdUpdateReg(hObj, fmdCfg, descMem);
    }

    return (retVal);
}

/**
 *  Vcore_vpeUpdateDesc
 *  \brief Updates the buffer addresses provided in the frame structure
 *  to the descriptor memories.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param descMem      [IN] Pointer to the data descriptor memory information.
 *                      This parameter should be non-NULL.
 *  \param frame        [IN] Pointer to the FVID frame containing the buffer
 *                      address. This parameter should be non-NULL.
 *  \param fid          [IN] FID to be programmed in the descriptor.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeUpdateDesc(Vcore_M2mHandle         handle,
                                 const Vcore_M2mDescMem *descMem,
                                 const Fvid2_Frame      *frame,
                                 UInt32                  fid)
{
    Int32  retVal = BSP_SOK;
    UInt32 chNum;
    void                   *descPtr;
    Vcore_VpeChObj         *chObj;
    Vcore_VpeInstObj       *instObj;
    Vcore_VpeHandleObj     *hObj;
    UInt32 descOffset;
    UInt32 cnt;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);
    GT_assert(VpsVpeCoreTrace, NULL != frame);
    hObj    = (Vcore_VpeHandleObj *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    chNum = frame->chNum;
    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isParamsSet)
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR,
                      "Set the parameter before updating the descriptors!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        for (cnt = 0U; cnt < instObj->numDescPerWindow; cnt++)
        {
            /*
             *  Caution:
             *  Next statement relies on the fact that VCORE_VPE_FLD0LUMA_IDX
             *  and VCORE_VPE_FLD0CHROMA_IDX are next to each other.
             */
            /* Update Y and C data descriptor */
            descOffset = chObj->descOffset[VCORE_VPE_FLD0LUMA_IDX + cnt];
            descPtr    = descMem->inDataDesc[descOffset];
            GT_assert(VpsVpeCoreTrace, NULL != descPtr);
            if (TRUE == chObj->ctxInfo.isDeinterlacing)
            {
                /* Use the field mode address index when deinterlacing */
                VpsHal_vpdmaSetAddress(
                    descPtr,
                    (UInt8) fid,
                    frame->addr[FVID2_FIELD_MODE_ADDR_IDX]
                    [chObj->bufIndex[cnt]]);
            }
            else
            {
                /* Use appropriate frame/field address index when in normal
                 * mode */
                VpsHal_vpdmaSetAddress(
                    descPtr,
                    (UInt8) fid,
                    frame->addr[fid][chObj->bufIndex[cnt]]);
            }
        }
    }

    return (retVal);
}

/**
 *  Vcore_vpeUpdateContext
 *  \brief Updates the DEI context buffer addresses provided in the
 *  update context structure to the descriptor memories.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param descMem      [IN] Pointer to the data descriptor memory information.
 *                      This parameter should be non-NULL.
 *  \param context      [IN] Pointer to the Vcore_VpeUpdateContext structure
 *                      containing the context buffer address and other
 *                      information.
 *                      This parameter should be non-NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeUpdateContext(Vcore_M2mHandle         handle,
                                    UInt32                  chNum,
                                    const Vcore_M2mDescMem *descMem,
                                    const void             *ctx)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt, mvCnt, fldCnt;
    UInt32 tempIdx, mvstmIdx;
    void                         *descPtr;
    UInt32 descOffset;
    Vcore_VpeChObj   *chObj;
    Vcore_VpeInstObj *instObj;
    Vcore_VpeHandleObj           *hObj;
    const Vcore_VpeUpdateContext *context;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);
    GT_assert(VpsVpeCoreTrace, NULL != ctx);
    hObj    = (Vcore_VpeHandleObj *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    context = (const Vcore_VpeUpdateContext *) ctx;

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isParamsSet)
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR,
                      "Set the parameter before updating the descriptors!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Update the previous field descriptors */
        for (fldCnt = 0U; fldCnt < VCORE_VPE_MAX_PREV_FLD; fldCnt++)
        {
            /*
             *  Caution:
             *  This relies on the fact that the previous fields are in order
             *  starting from VCORE_VPE_FLD1LUMA_IDX.
             */
            tempIdx = (UInt32) VCORE_VPE_FLD1LUMA_IDX +
                      (fldCnt * VCORE_VPE_NUM_DESC_PER_FIELD);
            for (cnt = 0U; cnt < VCORE_VPE_NUM_DESC_PER_FIELD; cnt++)
            {
                if (TRUE == chObj->isDescReq[tempIdx + cnt])
                {
                    /* Update data descriptor */
                    descOffset = chObj->descOffset[tempIdx + cnt];
                    descPtr    = descMem->inDataDesc[descOffset];
                    GT_assert(VpsVpeCoreTrace, NULL != descPtr);
                    if (0 !=
                        Fvid2_isDataFmtYuv422I(chObj->corePrms.fmt.dataFormat))
                    {
                        /* For YUV422I input, same address should be
                         * programmed for chroma descriptor */
                        GT_assert(VpsVpeCoreTrace,
                                  NULL != context->prevInBuf
                                  [fldCnt][FVID2_YUV_INT_ADDR_IDX]);
                        VpsHal_vpdmaSetAddress(
                            descPtr,
                            (UInt8) context->prevInFid[fldCnt],
                            context->prevInBuf[fldCnt][FVID2_YUV_INT_ADDR_IDX]);
                    }
                    else
                    {
                        GT_assert(VpsVpeCoreTrace,
                                  NULL != context->prevInBuf[fldCnt][cnt]);
                        VpsHal_vpdmaSetAddress(
                            descPtr,
                            (UInt8) context->prevInFid[fldCnt],
                            context->prevInBuf[fldCnt][cnt]);
                    }
                }
            }
        }

        /* Update the current field/frame out descriptors */
        for (fldCnt = 0U; fldCnt < VCORE_VPE_MAX_OUT_FLD; fldCnt++)
        {
            /*
             *  Caution:
             *  This relies on the fact that the previous fields are in order
             *  starting from VCORE_VPE_FLD1LUMA_IDX.
             */
            tempIdx = (UInt32) VCORE_VPE_WRLUMA_IDX +
                      (fldCnt * VCORE_VPE_NUM_DESC_PER_FIELD);
            for (cnt = 0U; cnt < VCORE_VPE_NUM_DESC_PER_FIELD; cnt++)
            {
                if (TRUE == chObj->isDescReq[tempIdx + cnt])
                {
                    /* Update current field out data descriptor */
                    descOffset = chObj->descOffset[tempIdx + cnt];
                    descPtr    = descMem->outDataDesc[descOffset];
                    GT_assert(VpsVpeCoreTrace, NULL != descPtr);
                    GT_assert(VpsVpeCoreTrace,
                              NULL != context->curOutBuf[fldCnt][cnt]);
                    VpsHal_vpdmaSetAddress(
                        descPtr,
                        0U,     /* FID is reserved for outbound descriptors */
                        context->curOutBuf[fldCnt][cnt]);
                }
            }
        }

        /* Update the MV In descriptors */
        for (mvCnt = 0U; mvCnt < VCORE_VPE_MAX_MV_IN; mvCnt++)
        {
            /*
             *  Caution:
             *  This relies on the fact that the MVs are in order
             *  starting from VCORE_VPE_MV1_IDX.
             */
            tempIdx = VCORE_VPE_MV1_IDX + mvCnt;
            if (TRUE == chObj->isDescReq[tempIdx])
            {
                /* Update MV In data descriptor */
                descOffset = chObj->descOffset[tempIdx];
                descPtr    = descMem->inDataDesc[descOffset];
                GT_assert(VpsVpeCoreTrace, NULL != descPtr);
                GT_assert(VpsVpeCoreTrace, NULL != context->mvInBuf[mvCnt]);
                VpsHal_vpdmaSetAddress(
                    descPtr,
                    (UInt8) context->mvInFid[mvCnt],
                    context->mvInBuf[mvCnt]);
            }
        }

        /* Update the MV Out descriptor */
        if (TRUE == chObj->isDescReq[VCORE_VPE_MVOUT_IDX])
        {
            /* Update MV Out data descriptor */
            descOffset = chObj->descOffset[VCORE_VPE_MVOUT_IDX];
            descPtr    = descMem->outDataDesc[descOffset];
            GT_assert(VpsVpeCoreTrace, NULL != descPtr);
            GT_assert(VpsVpeCoreTrace, NULL != context->mvOutBuf);
            VpsHal_vpdmaSetAddress(
                descPtr,
                0U,             /* FID is reserved for outbound descriptors */
                context->mvOutBuf);
        }

        /* Update the MVSTM In descriptors */
        mvstmIdx = 1U;
        for (mvCnt = 0U; mvCnt < VCORE_VPE_MAX_MVSTM_IN; mvCnt++)
        {
            /*
             *  Caution:
             *  This relies on the fact that the MVSTMs are in order
             *  starting from VCORE_VPE_MVSTM_IDX.
             */
            tempIdx = VCORE_VPE_MVSTM_IDX + mvCnt;
            if (TRUE == chObj->isDescReq[tempIdx])
            {
                /* Update MVSTM In data descriptor */
                descOffset = chObj->descOffset[tempIdx];
                descPtr    = descMem->inDataDesc[descOffset];
                GT_assert(VpsVpeCoreTrace, NULL != descPtr);
                GT_assert(VpsVpeCoreTrace,
                          NULL != context->mvstmInBuf[mvCnt + mvstmIdx]);

                /* Buffer at the index 0 is for storing mvstm of previous
                 * field. Since MVSTM needs two field delayed data, it should
                 * take buffer from index 1. */
                VpsHal_vpdmaSetAddress(
                    descPtr,
                    (UInt8) context->mvstmInFid[mvCnt + mvstmIdx],
                    context->mvstmInBuf[mvCnt + mvstmIdx]);
            }
        }

        /* Update the MVSTM Out descriptor */
        if (TRUE == chObj->isDescReq[VCORE_VPE_MVSTMOUT_IDX])
        {
            /* Update MV Out data descriptor */
            descOffset = chObj->descOffset[VCORE_VPE_MVSTMOUT_IDX];
            descPtr    = descMem->outDataDesc[descOffset];
            GT_assert(VpsVpeCoreTrace, NULL != descPtr);
            GT_assert(VpsVpeCoreTrace, NULL != context->mvstmOutBuf);
            VpsHal_vpdmaSetAddress(
                descPtr,
                0U,             /* FID is reserved for outbound descriptors */
                context->mvstmOutBuf);
        }
    }

    return (retVal);
}

/**
 *  Vcore_vpeUpdateRtMem
 *  \brief Updates the VPE runtime parameters in the descriptor as well as
 *  in register overlay memories.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param descMem      [IN] Pointer to the data descriptor memory information.
 *                      This parameter should be non-NULL.
 *  \param rtPrms       [IN] Pointer to the Vcore_VpeRtParams structure
 *                      containing the run time parameters.
 *                      If this parameter is NULL, then the run time
 *                      configuration is updated in the overlay/descriptor
 *                      memories using the previously set configuration.
 *                      Otherwise the run time configurations are updated in
 *                      the channel object as well as updated in overlay and
 *                      descriptor memories.
 *                      This parameter can be NULL depending on the
 *                      intended usage.
 *  \param frmIdx       [IN] Not used currently. Meant for future purpose.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeUpdateRtMem(Vcore_M2mHandle         handle,
                                  const Vcore_M2mDescMem *descMem,
                                  UInt32                  chNum,
                                  const void             *rtPrms,
                                  UInt32                  frmIdx)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeChObj     *chObj;
    Vcore_VpeInstObj   *instObj;
    Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);
    hObj    = (Vcore_VpeHandleObj *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isParamsSet)
        {
            GT_0trace(
                VpsVpeCoreTrace, GT_ERR,
                "Set the parameter before updating the descriptors!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        if (NULL != rtPrms)
        {
            retVal = vcoreVpeUpdateRtPrms(
                instObj,
                chObj,
                (const Vcore_VpeRtParams *) rtPrms);
            if (BSP_SOK != retVal)
            {
                GT_1trace(VpsVpeCoreTrace, GT_ERR,
                          "Update RT params failed for channel %d!!\r\n", chNum);
            }
        }
    }

    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeUpdateRtDescMem(instObj, chObj, descMem);
        if (BSP_SOK != retVal)
        {
            GT_1trace(VpsVpeCoreTrace, GT_ERR,
                      "Update RT memory failed for channel %d!!\r\n", chNum);
        }
    }

    return (retVal);
}

/**
 *  Vcore_vpeProgramUserCoeff
 *  \brief Programs the coefficient overlay memory with the scaler coefficients
 *  according to the parameter passed.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param userCoeffPrms    [IN] Pointer to the user coeff information.
 *                      This parameter should be non-NULL. The pointers to the
 *                      coeff overlays are returned in this structure.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeProgramUserCoeff(
    const Vcore_M2mHandle handle,
    UInt32                chNum,
    const Vcore_M2mScUserCoeffParams *
    userCoeffPrms)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeInstObj   *instObj;
    const Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != userCoeffPrms);
    hObj    = (const Vcore_VpeHandleObj *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        if (NULL != instObj->halHandle[VCORE_VPE_SC_IDX])
        {
            if (NULL != userCoeffPrms->userCoeffPtr)
            {
                retVal = VpsHal_scSetUserCoeff(
                    instObj->halHandle[VCORE_VPE_SC_IDX],
                    userCoeffPrms->userCoeffPtr);
            }
        }
        else
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR,
                      "Scaler is not present to be programmed!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    return (retVal);
}

/**
 *  Vcore_vpeGetScCoeff
 *  \brief Get the coefficient overlay memory with the scaler coefficients
 *  according to the parameter passed.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param getCoeffPrms [IN] Pointer to the coeff information.
 *                      This parameter should be non-NULL. The pointers to the
 *                      coeff overlays are returned in this structure.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeGetScCoeff(Vcore_M2mHandle            handle,
                                 UInt32                     chNum,
                                 Vcore_M2mScGetCoeffParams *getCoeffPrms)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeInstObj     *instObj;
    Vcore_VpeHandleObj   *hObj;
    VpsHal_ScFactorConfig coeffCfg;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != getCoeffPrms);
    hObj    = (Vcore_VpeHandleObj *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        if (NULL != instObj->halHandle[VCORE_VPE_SC_IDX])
        {
            coeffCfg.hScalingSet = getCoeffPrms->hScalingSet;
            coeffCfg.vScalingSet = getCoeffPrms->vScalingSet;
            retVal = VpsHal_scGetCoeffOvlyMemPtr(
                instObj->halHandle[VCORE_VPE_SC_IDX],
                &coeffCfg,
                &(getCoeffPrms->horzCoeffMemPtr),
                &(getCoeffPrms->vertCoeffMemPtr),
                &(getCoeffPrms->vertBilinearCoeffMemPtr));
        }
        else
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR,
                      "Scaler is not present to be programmed!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    return (retVal);
}

/**
 *  Vcore_vpeUpdateMode
 *  \brief Updates DEI Mode as per the number of Frames.
 *
 *  \param handle       [IN] VPE Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param descMem      [IN] Pointer to the data descriptor memory information.
 *                      This parameter should be non-NULL.
 *  \param prevFldState [IN] Represents the previous field state - used in
 *                      DEI reset sequence to build up the DEI context
 *                      and state.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vpeUpdateMode(Vcore_M2mHandle         handle,
                                 UInt32                  chNum,
                                 const Vcore_M2mDescMem *descMem,
                                 UInt32                  prevFldState)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeChObj     *chObj;
    Vcore_VpeInstObj   *instObj;
    Vcore_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);
    hObj    = (Vcore_VpeHandleObj *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        retVal = BSP_EOUT_OF_RANGE;
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isParamsSet)
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR,
                      "Set the parameter before updating the descriptors!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeUpdateMode(instObj, chObj, descMem, prevFldState);
    }

    return (retVal);
}

/**
 *  Vcore_vpeGetScFactorConfig
 *  \brief Returns information about the scaling factor configuration for a
 *  given channel.
 *
 *  \param handle       Scaler Writeback Path Core handle.
 *  \param chNum        Channel for which the information is to be returned.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in mem-mem mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param scFactorCfg  Pointer to the scaling factor configuration structure
 *                      in which the information is to be returned.
 *                      This parameter should be non-NULL.
 *
 *  \return             Returns 0 on success else returns error value.
 */
static Int32 Vcore_vpeGetScFactorConfig(Vcore_M2mHandle        handle,
                                        UInt32                 chNum,
                                        VpsHal_ScFactorConfig *scFactorCfg)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeHandleObj *hObj;
    Vcore_VpeChObj     *chObj;
    Vps_ScConfig       *scHalCfg;

    /* Check for errors */
    GT_assert(VpsVpeCoreTrace, NULL != handle);
    GT_assert(VpsVpeCoreTrace, NULL != scFactorCfg);

    hObj = (Vcore_VpeHandleObj *) handle;

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        retVal = BSP_EOUT_OF_RANGE;
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
    }
    else
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        if (NULL != hObj->instObj->halHandle[VCORE_VPE_SC_IDX])
        {
            /* Call the HAL function to get the scaling factor config. */
            scHalCfg = &chObj->scHalCfg;
            retVal   = VpsHal_scGetScFactorConfig(
                hObj->instObj->halHandle[VCORE_VPE_SC_IDX],
                scHalCfg,
                scFactorCfg);
        }
        else
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR,
                      "Scaler is not present to get the scaling factor!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    return (retVal);
}

/* ---------------------------------------------------------------------------
 * Internal functions
 * ---------------------------------------------------------------------------
 */
/**
 *  vcoreVpeUpdateRtPrms
 *  \brief Update runtime parameters into channel instance.
 */
static Int32 vcoreVpeUpdateRtPrms(const Vcore_VpeInstObj  *instObj,
                                  Vcore_VpeChObj          *chObj,
                                  const Vcore_VpeRtParams *rtPrms)
{
    Int32                    retVal;
    UInt32                   cnt;
    Vps_ScConfig            *scHalCfg;
    Vcore_VpeParams          corePrms;
    const Vcore_VpeRtParams *vpeRtPrms;
    Vps_FrameParams         *inFrmPrms;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);
    GT_assert(VpsVpeCoreTrace, NULL != rtPrms);

    scHalCfg  = &chObj->scHalCfg;
    vpeRtPrms = (const Vcore_VpeRtParams *) rtPrms;

    /* Copy the existing params and change only the required ones */
    BspUtils_memcpy(&corePrms, &chObj->corePrms, sizeof (Vcore_VpeParams));

    /* Allow input resolution change only if compressor is disabled */
    inFrmPrms = NULL;
    if (NULL != vpeRtPrms->inFrmPrms)
    {
        inFrmPrms = vpeRtPrms->inFrmPrms;
    }

    /* Copy the in frame params to core params */
    if (NULL != inFrmPrms)
    {
        corePrms.fmt.width  = inFrmPrms->width;
        corePrms.fmt.height = inFrmPrms->height;
        /* For M2M mode, when dimension changes, change the frame dimensions as
         * well. This should not be done for display mode as frame width and
         * frame height represents display resolution and they never change. */
        corePrms.frameWidth  = inFrmPrms->width;
        corePrms.frameHeight = inFrmPrms->height;
        for (cnt = 0U; cnt < FVID2_MAX_PLANES; cnt++)
        {
            corePrms.fmt.pitch[cnt] = inFrmPrms->pitch[cnt];
        }
        corePrms.memType        = inFrmPrms->memType;
        corePrms.fmt.dataFormat = inFrmPrms->dataFormat;
    }

    /* Copy the position params to core params */
    if (NULL != rtPrms->posCfg)
    {
        corePrms.startX = rtPrms->posCfg->startX;
        corePrms.startY = rtPrms->posCfg->startY;
    }

    /* Copy the out frame params to core params */
    if (NULL != vpeRtPrms->outFrmPrms)
    {
        corePrms.tarWidth  = vpeRtPrms->outFrmPrms->width;
        corePrms.tarHeight = vpeRtPrms->outFrmPrms->height;
    }

    /* Copy the crop config to core params */
    if (NULL != vpeRtPrms->scCropCfg)
    {
        corePrms.cropCfg.cropStartX = vpeRtPrms->scCropCfg->cropStartX;
        corePrms.cropCfg.cropStartY = vpeRtPrms->scCropCfg->cropStartY;
        corePrms.cropCfg.cropWidth  = vpeRtPrms->scCropCfg->cropWidth;
        corePrms.cropCfg.cropHeight = vpeRtPrms->scCropCfg->cropHeight;
    }
    else if (NULL != inFrmPrms)
    {
        /* When input changes and if user did not modify the scaler crop
         * configuration, use the modified input params. */
        corePrms.cropCfg.cropStartX = 0U;
        corePrms.cropCfg.cropStartY = 0U;
        corePrms.cropCfg.cropWidth  = inFrmPrms->width;
        if (TRUE == chObj->ctxInfo.isDeinterlacing)
        {
            corePrms.cropCfg.cropHeight = inFrmPrms->height * 2U;
        }
        else
        {
            corePrms.cropCfg.cropHeight = inFrmPrms->height;
        }
    }
    else
    {
        /* dummy else statement */
    }

    /* Copy the scaler runtime configuraton to core params */
    if (NULL != vpeRtPrms->scRtCfg)
    {
        corePrms.scCfg.bypass = vpeRtPrms->scRtCfg->scBypass;
    }

    /* Dummy data descriptor is not needed if frame size and buffer
     * bottom-right coordinates match */
    if (((corePrms.startX + corePrms.fmt.width) < corePrms.frameWidth) ||
        ((corePrms.startY + corePrms.fmt.height) < corePrms.frameHeight))
    {
        chObj->isDummyNeeded = TRUE;
    }
    else
    {
        chObj->isDummyNeeded = FALSE;
    }

    /* Check whether the updated RT params are valid */
    retVal = vcoreVpeCheckParams(instObj, &corePrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Invalid runtime parameters!!\r\n");
    }
    else
    {
        /* Update the new configuration */
        retVal = vcoreVpeSetChParams(instObj, chObj, &corePrms);
        GT_assert(VpsVpeCoreTrace, BSP_SOK == retVal);

        /* Update scaler phase info from application provided data.
         * Caution: This should be done after calling vcoreVpeSetChParams()
         * as this resets the phInfoMode to default mode. */
        if ((NULL != vpeRtPrms->scRtCfg) &&
            (TRUE == vpeRtPrms->scRtCfg->scSetPhInfo))
        {
            GT_assert(VpsVpeCoreTrace, NULL != scHalCfg->advCfg);
            scHalCfg->advCfg->phInfoMode = VPS_SC_SET_PHASE_INFO_FROM_APP;
            scHalCfg->advCfg->polyphasePhInfo.rowAccInc =
                vpeRtPrms->scRtCfg->rowAccInc;
            scHalCfg->advCfg->polyphasePhInfo.rowAccOffset =
                vpeRtPrms->scRtCfg->rowAccOffset;
            scHalCfg->advCfg->polyphasePhInfo.rowAccOffsetB =
                vpeRtPrms->scRtCfg->rowAccOffsetB;
            scHalCfg->advCfg->ravPhInfo.ravScFactor =
                vpeRtPrms->scRtCfg->ravScFactor;
            scHalCfg->advCfg->ravPhInfo.ravRowAccInit =
                vpeRtPrms->scRtCfg->ravRowAccInit;
            scHalCfg->advCfg->ravPhInfo.ravRowAccInitB =
                vpeRtPrms->scRtCfg->ravRowAccInitB;
        }
    }

    return (retVal);
}

/**
 *  vcoreVpeUpdateRtDescMem
 *  \brief Program vpdma inbound data descriptor based on channel instance
 *  parameters.
 */
static Int32 vcoreVpeUpdateRtDescMem(const Vcore_VpeInstObj *instObj,
                                     const Vcore_VpeChObj   *chObj,
                                     const Vcore_M2mDescMem *descMem)
{
    Int32 retVal = BSP_SOK;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);

    /* Check if overlay pointers are non-NULL for required overlay */
    GT_assert(VpsVpeCoreTrace,
              !((0U != chObj->descInfo.shadowOvlySize)
                && (NULL == descMem->shadowOvlyMem)));

    /* Re-program the registers */
    retVal = vcoreVpeProgramReg(instObj, chObj, descMem);

    /* Re-program the descriptors */
    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeProgramDesc(instObj, chObj, descMem);
    }

    /* Re-program context descriptors as well since we allow input
     * resolution change even if DEI is enabled. */
    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeProgramPrevFldDesc(instObj, chObj, descMem);
    }
    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeProgramCurOutDesc(instObj, chObj, descMem);
    }
    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeProgramMvDesc(instObj, chObj, descMem);
    }
    if (BSP_SOK == retVal)
    {
        retVal = vcoreVpeProgramMvstmDesc(instObj, chObj, descMem);
    }

    /* Update the frame start event only for M2M mode as we support runtime
     * change of input format through overlay memory.
     * This should not be done for display mode as this register is updated
     * directly using MMR access and could currupt the current frame because
     * this register is non-shadowed!! */
    if (BSP_SOK == retVal)
    {
        GT_assert(VpsVpeCoreTrace, NULL != descMem->nonShadowOvlyMem);
        retVal = vcoreVpeSetFsEvent(instObj, chObj, descMem);
    }

    return (retVal);
}

