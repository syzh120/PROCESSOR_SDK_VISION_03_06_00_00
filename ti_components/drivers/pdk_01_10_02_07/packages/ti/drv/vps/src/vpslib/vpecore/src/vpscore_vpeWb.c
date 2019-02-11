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
 *  \file vpscore_vpeWb.c
 *
 *  \brief VPS VPE write back path core file.
 *  This file implements the core layer for VPE write back paths.
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
#include <ti/drv/vps/src/vpslib/common/vps_common.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpeTop.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_csc.h>
#include <ti/drv/vps/src/vpslib/vpecore/vpscore_m2m.h>
#include <ti/drv/vps/src/vpslib/vpecore/vpscore_vpeWb.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Max number of descriptors needed - 2 for YUV420/422SP outputs. */
#define VCORE_VWB_MAX_DESC_PER_WINDOW   (2U)

/**
 *  \brief Maximum number of channel objects to be statically allocated for all
 *  the instances. Each of the channels in an instance is assumed to be
 *  shared across all handles of that instance.
 *  All the handles will allocate channel objects from this pool only.
 *  Instead of allocating VCORE_VWB_MAX_HANDLES * VCORE_VWB_MAX_CHANNELS
 *  objects per instance, only the below number of objects are allocated
 *  to save memory.
 */
#define VCORE_VWB_MAX_CHANNEL_OBJECTS   (VCORE_VWB_MAX_CHANNELS \
                                         * VCORE_VWB_NUM_INST)

/** \brief Default width used for initializing format structure. */
#define VCORE_VWB_DEFAULT_WIDTH         (720U)
/** \brief Default height used for initializing format structure. */
#define VCORE_VWB_DEFAULT_HEIGHT        (480U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Typedef for VWB path instance object. */
typedef struct Vcore_VwbInstObj_t Vcore_VwbInstObj;

/**
 *  struct Vcore_VwbChObj
 *  \brief Per channel information.
 */
typedef struct
{
    Vcore_M2mStates     state;
    /**< Current state. */
    Vcore_M2mFormat     coreFmt;
    /**< Buffer formats and other formats. */
    Vcore_M2mDescInfo   descInfo;
    /**< Data descriptor information to be used by driver to allocate
     *   data and config descriptor memories required by this core. */

    Vps_CscConfig       cscHalCfg;
    /**< CSC HAL configuration. */
    VpsHal_VpeTopConfig vpeTopHalCfg;
    /**< VPE top HAL configuration. */

    UInt32              numDataDesc;
    /**< Number of data descriptors needed for a particular output.
     *   1 for YUV422I and RGB/YUV444
     *   2 for YUV420SP and YUV422SP
     */
    VpsHal_VpdmaChannel vpdmaCh[VCORE_VWB_MAX_DESC_PER_WINDOW];
    /**< VPDMA channel number required for a particular output. */
    VpsHal_VpdmaChanDT  vpdmaDataType[VCORE_VWB_MAX_DESC_PER_WINDOW];
    /**< VPDMA data type required for a particular output. */
} Vcore_VwbChObj;

/**
 *  struct Vcore_VwbHandleObj
 *  \brief Per handle information.
 */
typedef struct
{
    UInt32            isUsed;
    /**< Flag to indicate whether the handle object is already used. */
    Vcore_VwbInstObj *instObj;
    /**< Pointer to the instance object. */
    Vcore_VwbChObj   *chObjs[VCORE_VWB_MAX_CHANNELS];
    /**< Pointer to the channel information. Array of pointers is used so that
     *   memory for each channel could be allocated from the pool. */
    UInt32            numCh;
    /**< Number of channels for this handle. This determines the number of
     *   valid pointers in channel array. */
} Vcore_VwbHandleObj;

/**
 *  struct Vcore_VwbInstObj_t
 *  \brief Structure containing per instance information.
 */
struct Vcore_VwbInstObj_t
{
    UInt32                instId;
    /**< Instance number/ID. */
    UInt32                numHandle;
    /**< Number of handles for this instance. This determines the size of
     *   handle array. */
    VpsHal_VpdmaChannel   vpdmaCh[VCORE_VWB_MAX_VPDMA_CH];
    /**< VPE writeback VPDMA channel number required by core. */
    VpsHal_Handle         halHandle[VCORE_VWB_MAX_HAL];
    /**< Array to pass the HAL handles required by core. */

    UInt32                openCnt;
    /**< Counter to keep track of number of open calls for an instance. */
    Vcore_VwbHandleObj    hObjs[VCORE_VWB_MAX_HANDLES];
    /**< Handle object pool. */

    UInt32                halShadowOvlySize[VCORE_VWB_MAX_HAL];
    /**< Array to store the shadow overlay size for each module. */
    VpsHal_GetCfgOvlySize getCfgOvlySize[VCORE_VWB_MAX_HAL];
    /**< Array to store the overlay size function pointer for each HAL. */
    VpsHal_CreateCfgOvly  createCfgOvly[VCORE_VWB_MAX_HAL];
    /**< Array to store the create overlay function pointer for each HAL. */
    UInt32                ovlyOffset[VCORE_VWB_MAX_HAL];
    /**< Byte offset to overlay memory for each HAL. */
};

/**
 *  struct Vcore_VwbPoolObj
 *  Memory pool object containing all the statically allocated
 *  objects - used structure to avoid multiple global variables.
 */
typedef struct
{
    Vcore_VwbChObj      chMemPool[VCORE_VWB_MAX_CHANNEL_OBJECTS];
    /**< Memory pool for the channel objects. */
    UInt32              chMemFlag[VCORE_VWB_MAX_CHANNEL_OBJECTS];
    /**< The flag variable represents whether a channel memory is allocated
     *   or not. */
    BspUtils_PoolParams chPoolPrm;
    /**< Pool params for descriptor pool memory. */

    BspOsal_SemHandle   lockSem;
    /**< Semaphore for protecting allocation and freeing of memory pool
     *   objects at open/close time. */
} Vcore_VwbPoolObj;

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

static Vcore_M2mHandle Vcore_vwbOpen(UInt32 instId, UInt32 numCh);
static Int32 Vcore_vwbClose(Vcore_M2mHandle handle);

static Int32 Vcore_vwbGetProperty(Vcore_M2mHandle    handle,
                                  Vcore_M2mProperty *property);

static Int32 Vcore_vwbSetFormat(Vcore_M2mHandle        handle,
                                UInt32                 chNum,
                                const Vcore_M2mFormat *coreFmt);
static Int32 Vcore_vwbGetFormat(Vcore_M2mHandle  handle,
                                UInt32           chNum,
                                Vcore_M2mFormat *coreFmt);

static Int32 Vcore_vwbGetDescInfo(Vcore_M2mHandle    handle,
                                  UInt32             chNum,
                                  Vcore_M2mDescInfo *descInfo);

static Int32 Vcore_vwbSetFsEvent(Vcore_M2mHandle         handle,
                                 UInt32                  chNum,
                                 VpsHal_VpdmaFSEvent     fsEvent,
                                 const Vcore_M2mDescMem *descMem);

static Int32 Vcore_vwbProgramDesc(Vcore_M2mHandle         handle,
                                  UInt32                  chNum,
                                  const Vcore_M2mDescMem *descMem);
static Int32 Vcore_vwbProgramReg(Vcore_M2mHandle         handle,
                                 UInt32                  chNum,
                                 const Vcore_M2mDescMem *descMem);

static Int32 Vcore_vwbUpdateDesc(Vcore_M2mHandle         handle,
                                 const Vcore_M2mDescMem *descMem,
                                 const Fvid2_Frame      *frame,
                                 UInt32                  fid);
static Int32 Vcore_vwbUpdateRtMem(Vcore_M2mHandle         handle,
                                  const Vcore_M2mDescMem *descMem,
                                  UInt32                  chNum,
                                  const void             *rtPrms,
                                  UInt32                  frmIdx);

#ifdef __cplusplus
}
#endif

static Int32 vcoreVwbSetHalCfg(const Vcore_VwbInstObj *instObj,
                               Vcore_VwbChObj         *chObj);
static Int32 vcoreVwbSetCscHalCfg(Vcore_VwbChObj *chObj);
static Int32 vcoreVwbSetVpeTopCfg(Vcore_VwbChObj *chObj);

static Int32 vcoreVwbProgramReg(const Vcore_VwbInstObj *instObj,
                                const Vcore_VwbChObj   *chObj,
                                const Vcore_M2mDescMem *descMem);
static Int32 vcoreVwbProgramDesc(const Vcore_VwbHandleObj *hObj,
                                 const Vcore_VwbChObj     *chObj,
                                 const Vcore_M2mDescMem   *descMem);

static Int32 vcoreVwbCheckFmt(const Vcore_M2mFormat *coreFmt);

static Vcore_VwbHandleObj *vcoreVwbAllocHandleObj(UInt32 instId);
static Int32 vcoreVwbFreeHandleObj(Vcore_VwbHandleObj *hObj);
static Int32 vcoreVwbAllocChObj(Vcore_VwbChObj **chObjs, UInt32 numCh);
static Int32 vcoreVwbFreeChObj(Vcore_VwbChObj **chObjs, UInt32 numCh);

static void vcoreVwbSetDefChInfo(Vcore_VwbChObj *chObj, UInt32 chNum);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief VWB path core function pointer. */
static const Vcore_M2mOps gVwbCoreOps =
{
    &Vcore_vwbGetProperty, /* Get property */
    &Vcore_vwbOpen,        /* Open function */
    &Vcore_vwbClose,       /* Close function */
    &Vcore_vwbSetFormat,   /* Set format */
    &Vcore_vwbGetFormat,   /* Get format */
    &Vcore_vwbGetDescInfo, /* Get descriptor info */
    &Vcore_vwbSetFsEvent,  /* Set frame */
    NULL,                  /* Set parameters */
    NULL,                  /* Get parameters */
    NULL,                  /* Control */
    &Vcore_vwbProgramDesc, /* Program descriptor */
    &Vcore_vwbProgramReg,  /* Program register */
    &Vcore_vwbUpdateDesc,  /* Update descriptor */
    NULL,                  /* Get DEI context info */
    NULL,                  /* Update context descriptor **/
    &Vcore_vwbUpdateRtMem, /* Update runtime params */
    NULL,                  /* Program user scaler coefficient */
    NULL,                  /* Get scaler coefficient */
    NULL,                  /* Update the mode in DEI */
    NULL,                  /* Get scaling factor config **/
    NULL,                  /* Program FMD register */
    NULL                   /* Program FMD update register */
};

/** \brief Properties of this core. */
static Vcore_M2mProperty  VwbProperty;

/** \brief VWB path objects. */
static Vcore_VwbInstObj   VwbInstObjects[VCORE_VWB_NUM_INST];

/**
 *  \brief Pool objects used for storing pool memories, pool flags and pool
 *  handles.
 */
static Vcore_VwbPoolObj   VcoreVwbPoolObjs;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  Vcore_vwbInit
 *  \brief VWB core init function.
 *  Initializes VWB core objects, allocates memory etc.
 *  This function should be called before calling any of VWB core API's.
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
Int32 Vcore_vwbInit(UInt32                     numInst,
                    const Vcore_VwbInitParams *initPrms)
{
    Int32  retVal = BSP_SOK;
    UInt32 ovlyOffset;
    UInt32 instCnt, hCnt, chCnt, halCnt;
    Vcore_VwbInstObj *instObj;

    /* Check for errors */
    GT_assert(VpsVwbCoreTrace, numInst <= VCORE_VWB_NUM_INST);
    GT_assert(VpsVwbCoreTrace, NULL != initPrms);

    /* Init pool objects */
    BspUtils_initPool(
        &VcoreVwbPoolObjs.chPoolPrm,
        (void *) VcoreVwbPoolObjs.chMemPool,
        (UInt32) VCORE_VWB_MAX_CHANNEL_OBJECTS,
        sizeof (Vcore_VwbChObj),
        VcoreVwbPoolObjs.chMemFlag,
        VpsVwbCoreTrace);

    /* Create Pool Semaphore */
    VcoreVwbPoolObjs.lockSem = BspOsal_semCreate((Int32) 1, TRUE);
    if (NULL == VcoreVwbPoolObjs.lockSem)
    {
        GT_0trace(VpsVwbCoreTrace, GT_ERR, "Sem create failed!!\r\n");
        retVal = BSP_EALLOC;
    }
    else
    {
        for (instCnt = 0U; instCnt < numInst; instCnt++)
        {
            /* Initialize instance object members */
            instObj         = &VwbInstObjects[instCnt];
            instObj->instId = initPrms[instCnt].instId;
            /* Get the VPDMA channels */
            for (chCnt = 0U; chCnt < VCORE_VWB_MAX_VPDMA_CH; chCnt++)
            {
                instObj->vpdmaCh[chCnt] = initPrms[instCnt].vpdmaCh[chCnt];
            }

            /* Assign get overlay size function pointer */
            instObj->getCfgOvlySize[VCORE_VWB_CSC_IDX] =
                &VpsHal_cscGetConfigOvlySize;
            instObj->getCfgOvlySize[VCORE_VWB_VPETOP_IDX] = NULL;
            if (VpsLib_platformIsTda2xxFamilyBuild())
            {
                /* Mux programming is not required for TI814X family */
                instObj->getCfgOvlySize[VCORE_VWB_VPETOP_IDX] =
                    &VpsHal_vpeTopGetConfigOvlySize;
            }
            instObj->getCfgOvlySize[VCORE_VWB_VPDMA_IDX] = NULL;

            /* Assign create overlay function pointer */
            instObj->createCfgOvly[VCORE_VWB_CSC_IDX] =
                &VpsHal_cscCreateConfigOvly;
            instObj->createCfgOvly[VCORE_VWB_VPETOP_IDX] = NULL;
            if (VpsLib_platformIsTda2xxFamilyBuild())
            {
                /* Mux programming is not required for TI814X family */
                instObj->createCfgOvly[VCORE_VWB_VPETOP_IDX] =
                    &VpsHal_vpeTopCreateConfigOvly;
            }
            instObj->createCfgOvly[VCORE_VWB_VPDMA_IDX] = NULL;

            /* Initialize HAL variables */
            ovlyOffset = 0U;
            for (halCnt = 0U; halCnt < VCORE_VWB_MAX_HAL; halCnt++)
            {
                instObj->halHandle[halCnt]  = initPrms->halHandle[halCnt];
                instObj->ovlyOffset[halCnt] = ovlyOffset;

                /* Get the overlay size for each of the modules */
                if ((NULL != instObj->halHandle[halCnt]) &&
                    (NULL != instObj->getCfgOvlySize[halCnt]))
                {
                    instObj->halShadowOvlySize[halCnt] =
                        instObj->getCfgOvlySize[halCnt](
                            instObj->halHandle[halCnt]);
                    ovlyOffset += instObj->halShadowOvlySize[halCnt];
                }
                else
                {
                    instObj->halShadowOvlySize[halCnt] = 0U;
                }
            }
            instObj->openCnt   = 0U;
            instObj->numHandle = initPrms[instCnt].maxHandle;

            /* VPDMA HAL can't be NULL */
            GT_assert(VpsVwbCoreTrace,
                      NULL != initPrms->halHandle[VCORE_VWB_VPDMA_IDX]);

            /* Mark all handles as free */
            for (hCnt = 0U; hCnt < VCORE_VWB_MAX_HANDLES; hCnt++)
            {
                instObj->hObjs[hCnt].isUsed = (UInt32) FALSE;
            }
        }

        /* Initialize VWB path core properties */
        VwbProperty.numInstance     = numInst;
        VwbProperty.name            = VCORE_M2M_DWB;
        VwbProperty.type            = VCORE_M2M_TYPE_OUTPUT;
        VwbProperty.internalContext = FALSE;
    }

    return (retVal);
}

/**
 *  Vcore_vwbDeInit
 *  \brief VWB core exit function.
 *  Deallocates memory allocated by init function.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 Vcore_vwbDeInit(void)
{
    UInt32 instCnt, halCnt;
    Vcore_VwbInstObj *instObj;

    /* Free-up handle objects for each instance if already allocated */
    for (instCnt = 0U; instCnt < VCORE_VWB_NUM_INST; instCnt++)
    {
        instObj            = &VwbInstObjects[instCnt];
        instObj->instId    = VCORE_VWB_INST_WB0;
        instObj->numHandle = 0U;
        for (halCnt = 0U; halCnt < VCORE_VWB_MAX_HAL; halCnt++)
        {
            instObj->halHandle[halCnt]         = NULL;
            instObj->halShadowOvlySize[halCnt] = 0U;
            instObj->ovlyOffset[halCnt]        = 0U;
        }
    }

    /* Delete the Semaphore created for pool objects */
    if (NULL != VcoreVwbPoolObjs.lockSem)
    {
        BspOsal_semDelete(&VcoreVwbPoolObjs.lockSem);
        VcoreVwbPoolObjs.lockSem = NULL;
    }

    VwbProperty.numInstance = 0U;

    return (BSP_SOK);
}

/**
 *  Vcore_vwbGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const Vcore_M2mOps *Vcore_vwbGetCoreOps(void)
{
    return &(gVwbCoreOps);
}

/**
 *  Vcore_vwbOpen
 *  \brief Opens a particular instance of VWB path in either capture
 *  or in M2M mode and returns the handle to the handle object.
 *  When opened in capture mode, only one handle could be opened. Also
 *  only one channel is supported.
 *  When opened in M2M mode, the same instance could be opened more than
 *  once. The number of handles supported per instance is determined by
 *  VCORE_VWB_MAX_HANDLES macro. Also each of the handles could have multiple
 *  channel to support more than one M2M operation is a single request.
 *
 *  \param instId       [IN] Instance to open - VPE instance.
 *  \param numCh        [IN] Number of channel to be associated with this open.
 *                      For capture operation only one channel is allowed.
 *                      For M2M operation, more than one channel could
 *                      be associated with a handle.
 *                      The maximum supported channel per handle depends on
 *                      VCORE_VWB_MAX_CHANNELS macro.
 *
 *  \return             If success returns the handle else returns NULL.
 */
static Vcore_M2mHandle Vcore_vwbOpen(UInt32 instId, UInt32 numCh)
{
    Int32 retVal = BSP_SOK;
    Vcore_VwbHandleObj *hObj = NULL;

    /* Check for maximum channel supported per handle */
    GT_assert(VpsVwbCoreTrace, numCh <= VCORE_VWB_MAX_CHANNELS);
    /* There should be atleast one channel */
    GT_assert(VpsVwbCoreTrace, 0U != numCh);

    /* Allocate a handle object */
    hObj = vcoreVwbAllocHandleObj(instId);
    if (NULL != hObj)
    {
        /* Allocate channel objects */
        retVal = vcoreVwbAllocChObj(hObj->chObjs, numCh);
        if (BSP_SOK != retVal)
        {
            GT_0trace(VpsVwbCoreTrace, GT_ERR, "Channel allocation failed!!\r\n");
            /* Free-up handle object if channel allocation failed */
            vcoreVwbFreeHandleObj(hObj);
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
        GT_0trace(VpsVwbCoreTrace, GT_ERR, "Handle allocation failed!!\r\n");
    }

    if (BSP_SOK == retVal)
    {
        /* Important: It is not required to set the frame start
         *            event for writeback client. This event is just used for
         *            client event generation. It is not used for outputting
         *            data. VPDMA will output data from this client
         *            whenever there is input data.
         *            Also these clients might be used in the display as free
         *            write back client */
        /* Needed only for simulator */
#if defined (PLATFORM_SIM) || defined (PLATFORM_VIRTIO)
        {
            /* Program it directly in VPDMA regsiter */
            VpsHal_vpdmaSetFrameStartEvent(
                hObj->instObj->halHandle[VCORE_VWB_VPDMA_IDX],
                hObj->instObj->vpdmaCh[VCORE_VWB_LUMA_IDX],
                VPSHAL_VPDMA_FSEVENT_CHANNEL_ACTIVE,
                VPSHAL_VPDMA_LM_0,
                0U,
                NULL,
                0U);
        }
#endif
    }

    return ((Vcore_M2mHandle) hObj);
}

/**
 *  Vcore_vwbClose
 *  \brief Closes the already opened handle.
 *
 *  \param handle       [IN] VPE Writeback Path Core handle.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vwbClose(Vcore_M2mHandle handle)
{
    Int32 retVal = BSP_EFAIL;
    Vcore_VwbHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != handle);
    hObj = (Vcore_VwbHandleObj *) handle;

    /* Free channel and handle objects */
    retVal  = vcoreVwbFreeChObj(hObj->chObjs, hObj->numCh);
    retVal += vcoreVwbFreeHandleObj(hObj);
    if (BSP_SOK != retVal)
    {
        GT_0trace(VpsVwbCoreTrace, GT_ERR, "Free memory failed!!\r\n");
    }

    return (retVal);
}

/**
 *  Vcore_vwbGetProperty
 *  \brief Gets the core properties of the VWB path core.
 *
 *  \param handle       [IN] VPE Writeback Path Core handle.
 *  \param property     [OUT] Pointer to which the VWB path core properties
 *                      to be copied.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vwbGetProperty(Vcore_M2mHandle    handle,
                                  Vcore_M2mProperty *property)
{
    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != handle);
    GT_assert(VpsVwbCoreTrace, NULL != property);

    BspUtils_memcpy(property, &VwbProperty, sizeof (Vcore_M2mProperty));

    return (BSP_SOK);
}

/**
 *  Vcore_vwbSetFormat
 *  \brief Sets the format for a given channel.
 *
 *  \param handle       [IN] VPE Writeback Path Core handle.
 *  \param chNum        [IN] Channel to which the params should be applied.
 *                      When opened in capture mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param coreFmt      [IN] Pointer to the format information. This should
 *                      point to a valid Vcore_M2mFormat structure.
 *                      This parameter should be non-NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vwbSetFormat(Vcore_M2mHandle        handle,
                                UInt32                 chNum,
                                const Vcore_M2mFormat *coreFmt)
{
    Int32  retVal = BSP_SOK;
    UInt32 halCnt, chCnt;
    Vcore_VwbChObj     *chObj;
    Vcore_VwbHandleObj *hObj;
    Vcore_VwbInstObj   *instObj;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != handle);
    GT_assert(VpsVwbCoreTrace, NULL != coreFmt);
    hObj    = (Vcore_VwbHandleObj *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsVwbCoreTrace, NULL != instObj);

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVwbCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        /* Check whether the requested format is valid */
        retVal = vcoreVwbCheckFmt(coreFmt);
        if (BSP_SOK != retVal)
        {
            GT_0trace(VpsVwbCoreTrace, GT_ERR, "Invalid Format!!\r\n");
        }
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVwbCoreTrace, NULL != chObj);

        /* Copy the format to the local structure */
        BspUtils_memcpy(&chObj->coreFmt, coreFmt, sizeof (Vcore_M2mFormat));

        /* Set the configuration for each of the HALs */
        retVal = vcoreVwbSetHalCfg(instObj, chObj);
    }

    if (BSP_SOK == retVal)
    {
        /*
         *  Set the channel information depending on VWBs requirement.
         */
        chObj->numDataDesc = 1U;
        if ((Int32) 0 !=
            Fvid2_isDataFmtSemiPlanar(chObj->coreFmt.fmt.dataFormat))
        {
            /* Two channels/descriptors for YUV422SP and YUV420SP formats */
            chObj->numDataDesc = 2U;
            chObj->vpdmaCh[0U] = instObj->vpdmaCh[VCORE_VWB_LUMA_IDX];
            chObj->vpdmaCh[1U] = instObj->vpdmaCh[VCORE_VWB_CHROMA_IDX];
        }
        else if ((Int32) 0 !=
                 Fvid2_isDataFmtYuv422I(chObj->coreFmt.fmt.dataFormat))
        {
            chObj->vpdmaCh[0U] = instObj->vpdmaCh[VCORE_VWB_LUMA_IDX];
        }
        else if ((FVID2_DF_YUV444I == chObj->coreFmt.fmt.dataFormat) ||
                 (FVID2_DF_RGB24_888 == chObj->coreFmt.fmt.dataFormat))
        {
            chObj->vpdmaCh[0U] = instObj->vpdmaCh[VCORE_VWB_RGB_IDX];
        }
        else
        {
            /* This can't happen as we have already checked for valid
             * data format */
            GT_assert(VpsVwbCoreTrace, FALSE);
        }

        /* Select VPDMA data type */
        switch (chObj->coreFmt.fmt.dataFormat)
        {
            case FVID2_DF_YUV422I_YUYV:
                chObj->vpdmaDataType[0U] = VPSHAL_VPDMA_CHANDT_YC422;
                break;

            case FVID2_DF_YUV422I_YVYU:
                chObj->vpdmaDataType[0U] = VPSHAL_VPDMA_CHANDT_YCb422;
                break;

            case FVID2_DF_YUV422I_UYVY:
                chObj->vpdmaDataType[0U] = VPSHAL_VPDMA_CHANDT_CY422;
                break;

            case FVID2_DF_YUV422I_VYUY:
                chObj->vpdmaDataType[0U] = VPSHAL_VPDMA_CHANDT_CbY422;
                break;

            case FVID2_DF_YUV420SP_UV:
                chObj->vpdmaDataType[0U] = VPSHAL_VPDMA_CHANDT_Y420;
                chObj->vpdmaDataType[1U] = VPSHAL_VPDMA_CHANDT_C420;
                break;

            case FVID2_DF_YUV420SP_VU:
                chObj->vpdmaDataType[0U] = VPSHAL_VPDMA_CHANDT_Y420;
                chObj->vpdmaDataType[1U] = VPSHAL_VPDMA_CHANDT_Cb420;
                break;

            case FVID2_DF_YUV422SP_UV:
                chObj->vpdmaDataType[0U] = VPSHAL_VPDMA_CHANDT_Y422;
                chObj->vpdmaDataType[1U] = VPSHAL_VPDMA_CHANDT_C422;
                break;

            case FVID2_DF_YUV422SP_VU:
                chObj->vpdmaDataType[0U] = VPSHAL_VPDMA_CHANDT_Y422;
                chObj->vpdmaDataType[1U] = VPSHAL_VPDMA_CHANDT_Cb422;
                break;

            /* Even for YUV444 we need to use RGB888 data type */
            case FVID2_DF_YUV444I:
            case FVID2_DF_RGB24_888:
                /* Note: The R and B lines are connected to B and R ports of
                 * VPDMA. Hence need to use BGR datatype to capture RGB data and
                 * viceversa.
                 * Same applies for YUV444 output as well - Y and V are
                 * swapped. */
                chObj->vpdmaDataType[0U] = VPSHAL_VPDMA_CHANDT_BGR888;
                break;

            default:
                /* This can't happen as we have already checked for valid
                 * data format */
                GT_assert(VpsVwbCoreTrace, FALSE);
                break;
        }

        chObj->descInfo.numOutDataDesc = chObj->numDataDesc;
        for (chCnt = 0U; chCnt < chObj->numDataDesc; chCnt++)
        {
            chObj->descInfo.socChNum[chCnt] = chObj->vpdmaCh[chCnt];
        }
        chObj->descInfo.numChannels = chObj->numDataDesc;

        /* Calculate the size of shadow overlay memory required by adding
         * the shadow overlay size of each HAL */
        chObj->descInfo.shadowOvlySize = 0U;
        for (halCnt = 0U; halCnt < VCORE_VWB_MAX_HAL; halCnt++)
        {
            chObj->descInfo.shadowOvlySize +=
                instObj->halShadowOvlySize[halCnt];
        }

        /* Set proper state - format is set */
        chObj->state.isFormatSet = (UInt32) TRUE;
    }

    return (retVal);
}

/**
 *  Vcore_vwbGetFormat
 *  \brief Gets the format for a given channel.
 *
 *  \param handle       [IN] VPE Writeback Path Core handle.
 *  \param chNum        [IN] Channel from which the params should be read.
 *                      When opened in capture mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param coreFmt      [OUT] Pointer to the copied format information. This
 *                      should point to a valid Vcore_M2mFormat structure.
 *                      This parameter should be non-NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vwbGetFormat(Vcore_M2mHandle  handle,
                                UInt32           chNum,
                                Vcore_M2mFormat *coreFmt)
{
    Int32 retVal = BSP_SOK;
    Vcore_VwbChObj *chObj;
    Vcore_VwbHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != handle);
    GT_assert(VpsVwbCoreTrace, NULL != coreFmt);
    hObj = (Vcore_VwbHandleObj *) handle;

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVwbCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVwbCoreTrace, NULL != chObj);

        /* Copy the format */
        BspUtils_memcpy(coreFmt, &chObj->coreFmt, sizeof (Vcore_M2mFormat));
    }

    return (retVal);
}

/**
 *  Vcore_vwbGetDescInfo
 *  \brief Depending on the format set, returns the number of data
 *  descriptors and config overlay memory needed for the actual driver to
 *  allocate memory.
 *  Format should have be set for each of the channel before calling this
 *  function.
 *
 *  \param handle       [IN] VPE Writeback Path Core handle.
 *  \param chNum        [IN] Channel to which the info is required.
 *                      When opened in capture mode, this should be always set
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
static Int32 Vcore_vwbGetDescInfo(Vcore_M2mHandle    handle,
                                  UInt32             chNum,
                                  Vcore_M2mDescInfo *descInfo)
{
    Int32 retVal = BSP_SOK;
    Vcore_VwbChObj     *chObj;
    Vcore_VwbHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != handle);
    GT_assert(VpsVwbCoreTrace, NULL != descInfo);
    hObj = (Vcore_VwbHandleObj *) handle;

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVwbCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVwbCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isFormatSet)
        {
            GT_0trace(VpsVwbCoreTrace, GT_ERR,
                      "Set the format before getting the descriptor info!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Copy the data descriptor information */
        BspUtils_memcpy(
            (Ptr) descInfo,
            &chObj->descInfo,
            sizeof (Vcore_M2mDescInfo));
    }

    return (retVal);
}

/**
 *  Vcore_vwbSetFsEvent
 *  \brief Program the client's frame start.
 *
 *  \param handle       [IN] VPE Writeback Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in capture mode, this should be always set
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
 *                      Note: In the current implementation only direct register
 *                      write is performed as the line mode is always the same.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vwbSetFsEvent(Vcore_M2mHandle         handle,
                                 UInt32                  chNum,
                                 VpsHal_VpdmaFSEvent     fsEvent,
                                 const Vcore_M2mDescMem *descMem)
{
    Int32 retVal = BSP_SOK;
    Vcore_VwbChObj     *chObj;
    Vcore_VwbHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != handle);
    hObj = (Vcore_VwbHandleObj *) handle;

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        retVal = BSP_EOUT_OF_RANGE;
        GT_0trace(VpsVwbCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVwbCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isFormatSet)
        {
            GT_0trace(
                VpsVwbCoreTrace, GT_ERR,
                "Set the parameter before setting the frame start event!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Important: It is not required to set the frame start
         *            event for writeback client. This event is just used for
         *            client event generation. It is not used for outputting
         *            data. VPDMA will output data from this client
         *            whenever there is input data.
         *            Also these clients might be used in the display as free
         *            write back client */
        /* Needed only for simulator */
#if defined (PLATFORM_SIM) || defined (PLATFORM_VIRTIO)
        {
            /* Program it directly in VPDMA regsiter */
            VpsHal_vpdmaSetFrameStartEvent(
                hObj->instObj->halHandle[VCORE_VWB_VPDMA_IDX],
                hObj->instObj->vpdmaCh[VCORE_VWB_LUMA_IDX],
                fsEvent,
                VPSHAL_VPDMA_LM_0,
                0U,
                NULL,
                0U);
        }
#endif
    }

    return (BSP_SOK);
}

/**
 *  Vcore_vwbProgramDesc
 *  \brief Programs the data descriptor for a given channel.
 *  Only after programming the data descriptor for each of the channel,
 *  the actual driver is supposed to call the update buffer function.
 *
 *  \param handle       [IN] VPE Writeback Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in capture mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param descMem      [IN] Pointer to the data descriptor memory information.
 *                      This parameter should be non-NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vwbProgramDesc(Vcore_M2mHandle         handle,
                                  UInt32                  chNum,
                                  const Vcore_M2mDescMem *descMem)
{
    Int32 retVal = BSP_SOK;
    Vcore_VwbChObj     *chObj;
    Vcore_VwbHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != handle);
    GT_assert(VpsVwbCoreTrace, NULL != descMem);
    hObj = (Vcore_VwbHandleObj *) handle;

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVwbCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVwbCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isFormatSet)
        {
            GT_0trace(VpsVwbCoreTrace, GT_ERR,
                      "Set the format before programming the descriptors!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        retVal = vcoreVwbProgramDesc(hObj, chObj, descMem);
    }

    return (retVal);
}

/**
 *  Vcore_vwbProgramReg
 *  \brief Programs the registers for each of the HALs through direct
 *  register programming if descMem is NULL else creates and programs the
 *  overlay memory. The upper driver has to submit the programmed overlay
 *  to the VPDMA to do the actual register programming.
 *
 *  \param handle       [IN] VPE Writeback Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in capture mode, this should be always set
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
static Int32 Vcore_vwbProgramReg(Vcore_M2mHandle         handle,
                                 UInt32                  chNum,
                                 const Vcore_M2mDescMem *descMem)
{
    Int32  retVal = BSP_SOK;
    UInt32 halCnt;
    void  *cfgOvlyPtr = NULL;
    Vcore_VwbChObj     *chObj;
    Vcore_VwbInstObj   *instObj;
    Vcore_VwbHandleObj *hObj;
    UInt32 cfgOvlyPtrValue;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != handle);
    hObj    = (Vcore_VwbHandleObj *) handle;
    instObj = hObj->instObj;
    GT_assert(VpsVwbCoreTrace, NULL != instObj);

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVwbCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVwbCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isFormatSet)
        {
            GT_0trace(
                VpsVwbCoreTrace, GT_ERR,
                "Set the parameter before programming the overlay memory!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        if (NULL != descMem)
        {
            /* Check if overlay pointers are non-NULL for required overlay */
            GT_assert(VpsVwbCoreTrace,
                      !((0U != chObj->descInfo.shadowOvlySize)
                        && (NULL == descMem->shadowOvlyMem)));

            /* Create overlay memory for each of the HAL */
            for (halCnt = 0U; halCnt < VCORE_VWB_MAX_HAL; halCnt++)
            {
                cfgOvlyPtrValue = (UInt32) descMem->shadowOvlyMem +
                                  instObj->ovlyOffset[halCnt];
                cfgOvlyPtr = (void *) cfgOvlyPtrValue;
                if ((NULL != instObj->halHandle[halCnt]) &&
                    (NULL != instObj->createCfgOvly[halCnt]))
                {
                    retVal = instObj->createCfgOvly[halCnt](
                        instObj->halHandle[halCnt],
                        cfgOvlyPtr);
                    if (BSP_SOK != retVal)
                    {
                        GT_1trace(
                            VpsVwbCoreTrace, GT_ERR,
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
        retVal = vcoreVwbProgramReg(instObj, chObj, descMem);
    }

    return (retVal);
}

/**
 *  Vcore_vwbUpdateDesc
 *  \brief Updates the buffer addresses provided in the frame structure
 *  to the descriptor memories.
 *
 *  \param handle       [IN] VPE Writeback Path Core handle.
 *  \param descMem      [IN] Pointer to the data descriptor memory information.
 *                      This parameter should be non-NULL.
 *  \param frame        [IN] Pointer to the FVID frame containing the buffer
 *                      address. This parameter should be non-NULL.
 *  \param fid          [IN] FID to be programmed in the descriptor.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
static Int32 Vcore_vwbUpdateDesc(Vcore_M2mHandle         handle,
                                 const Vcore_M2mDescMem *descMem,
                                 const Fvid2_Frame      *frame,
                                 UInt32                  fid)
{
    Int32  retVal = BSP_SOK;
    UInt32 chNum, chCnt;
    Vcore_VwbChObj     *chObj;
    Vcore_VwbHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != handle);
    GT_assert(VpsVwbCoreTrace, NULL != descMem);
    GT_assert(VpsVwbCoreTrace, NULL != frame);
    hObj = (Vcore_VwbHandleObj *) handle;

    /* Check if the channel is within the range allocated during open */
    chNum = frame->chNum;
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVwbCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVwbCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isFormatSet)
        {
            GT_0trace(VpsVwbCoreTrace, GT_ERR,
                      "Set the format before updating the descriptors!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Update data descriptor */
        for (chCnt = 0U; chCnt < chObj->numDataDesc; chCnt++)
        {
            GT_assert(VpsVwbCoreTrace, NULL != descMem->outDataDesc[chCnt]);
            VpsHal_vpdmaSetAddress(
                descMem->outDataDesc[chCnt],
                0U,             /* FID is reserved for outbound descriptors */
                frame->addr[fid][chCnt]);

            /* For outbound descriptors if frame address is NULL,
             * drop the data - don't return error */
            if (NULL == frame->addr[fid][chCnt])
            {
                VpsHal_vpdmaSetDropData(descMem->outDataDesc[chCnt],
                                        (UInt8) TRUE);

                /* Workaround: Drop data and Mode bit can not both be set.
                 * So clear memType when setting drop data */
                VpsHal_vpdmaSetMemType(
                    descMem->outDataDesc[chCnt],
                    VPSHAL_VPDMA_MT_NONTILEDMEM);
            }
            else
            {
                VpsHal_vpdmaSetDropData(descMem->outDataDesc[chCnt],
                                        (UInt8) FALSE);

                /* Set memory type back to original because of above
                 * workaround */
                VpsHal_vpdmaSetMemType(
                    descMem->outDataDesc[chCnt],
                    (VpsHal_VpdmaMemoryType) chObj->coreFmt.memType);
            }
        }
    }

    return (retVal);
}

/**
 *  Vcore_vwbUpdateRtMem
 *  \brief Updates the VWB runtime parameters in the descriptor as well as
 *  in register overlay memories.
 *
 *  \param handle       [IN] VPE Writeback Path Core handle.
 *  \param chNum        [IN] Channel to which the memory should be used for.
 *                      When opened in display mode, this should be always set
 *                      to 0. When opened in M2M mode, this represents the
 *                      channel to which this has to be applied. This
 *                      varies from 0 to the (number of channel - 1) provided
 *                      at the time of open.
 *  \param descMem      [IN] Pointer to the data descriptor memory information.
 *                      This parameter should be non-NULL.
 *  \param rtPrms       [IN] Pointer to the Vcore_VwbRtParams structure
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
static Int32 Vcore_vwbUpdateRtMem(Vcore_M2mHandle         handle,
                                  const Vcore_M2mDescMem *descMem,
                                  UInt32                  chNum,
                                  const void             *rtPrms,
                                  UInt32                  frmIdx)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt, chCnt;
    void  *descPtr;
    Vcore_VwbChObj          *chObj = NULL;
    Vcore_VwbHandleObj      *hObj;
    Vcore_M2mFormat         *coreFmt;
    const Vcore_VwbRtParams *vwbRtPrms;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != handle);
    GT_assert(VpsVwbCoreTrace, NULL != descMem);
    hObj = (Vcore_VwbHandleObj *) handle;

    /* Check if the channel is within the range allocated during open */
    if (chNum >= hObj->numCh)
    {
        GT_0trace(VpsVwbCoreTrace, GT_ERR, "Invalid channel number!!\r\n");
        retVal = BSP_EOUT_OF_RANGE;
    }

    if (BSP_SOK == retVal)
    {
        chObj = hObj->chObjs[chNum];
        /* NULL pointer check */
        GT_assert(VpsVwbCoreTrace, NULL != chObj);

        if (TRUE != chObj->state.isFormatSet)
        {
            GT_0trace(
                VpsVwbCoreTrace, GT_ERR,
                "Set the parameter before updating the descriptors!!\r\n");
            retVal = BSP_EFAIL;
        }

        /* First update the configuration if present */
        coreFmt = &chObj->coreFmt;
        if (NULL != rtPrms)
        {
            vwbRtPrms = (const Vcore_VwbRtParams *) rtPrms;

            /* Copy the out frame params to core format */
            if (NULL != vwbRtPrms->outFrmPrms)
            {
                coreFmt->fmt.width   = vwbRtPrms->outFrmPrms->width;
                coreFmt->fmt.height  = vwbRtPrms->outFrmPrms->height;
                coreFmt->frameWidth  = coreFmt->fmt.width;
                coreFmt->frameHeight = coreFmt->fmt.height;
                for (cnt = 0U; cnt < FVID2_MAX_PLANES; cnt++)
                {
                    coreFmt->fmt.pitch[cnt] =
                        vwbRtPrms->outFrmPrms->pitch[cnt];
                }
                coreFmt->memType = vwbRtPrms->outFrmPrms->memType;
            }
        }
    }

    /* Update out frame parameters in the descriptor descriptors. */
    if (BSP_SOK == retVal)
    {
        for (chCnt = 0U; chCnt < chObj->numDataDesc; chCnt++)
        {
            descPtr = descMem->outDataDesc[chCnt];
            GT_assert(VpsVwbCoreTrace, NULL != descPtr);

            /* Update pitch and memory type in VPDMA descriptor memory */
            GT_assert(VpsVwbCoreTrace, NULL != chObj);
            VpsHal_vpdmaSetLineStride(
                descPtr,
                (UInt16) chObj->coreFmt.fmt.pitch[chCnt]);
            VpsHal_vpdmaSetMemType(
                descPtr,
                (VpsHal_VpdmaMemoryType) chObj->coreFmt.memType);
        }
    }

    return (retVal);
}

static Int32 vcoreVwbSetHalCfg(const Vcore_VwbInstObj *instObj,
                               Vcore_VwbChObj         *chObj)
{
    Int32 retVal;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != instObj);
    GT_assert(VpsVwbCoreTrace, NULL != chObj);

    retVal  = vcoreVwbSetCscHalCfg(chObj);
    retVal += vcoreVwbSetVpeTopCfg(chObj);

    return (retVal);
}

static Int32 vcoreVwbSetCscHalCfg(Vcore_VwbChObj *chObj)
{
    Int32          retVal = BSP_SOK;
    Vps_CscConfig *cscHalCfg;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != chObj);

    cscHalCfg         = &chObj->cscHalCfg;
    cscHalCfg->mode   = VPS_CSC_MODE_HDTV_FULL_RANGE_Y2R;
    cscHalCfg->coeff  = NULL;
    cscHalCfg->bypass = (UInt32) TRUE;
    if (FVID2_DF_RGB24_888 == chObj->coreFmt.fmt.dataFormat)
    {
        cscHalCfg->bypass = (UInt32) FALSE;
    }

    return (retVal);
}

static Int32 vcoreVwbSetVpeTopCfg(Vcore_VwbChObj *chObj)
{
    Int32 retVal = BSP_SOK;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != chObj);

    chObj->vpeTopHalCfg.dataFmt =
        (Fvid2_DataFormat) chObj->coreFmt.fmt.dataFormat;

    return (retVal);
}

/**
 *  vcoreVwbProgramReg
 *  \brief Programs all the HAL registers either through direct register writes
 *  or update them in overlay memory.
 */
static Int32 vcoreVwbProgramReg(const Vcore_VwbInstObj *instObj,
                                const Vcore_VwbChObj   *chObj,
                                const Vcore_M2mDescMem *descMem)
{
    Int32  retVal     = BSP_SOK;
    void  *cfgOvlyPtr = NULL;
    Bool   isTda2xx;
    UInt32 cfgOvlyPtrValue;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != instObj);
    GT_assert(VpsVwbCoreTrace, NULL != chObj);

    /* Configure CSC module */
    if (BSP_SOK == retVal)
    {
        if (NULL != instObj->halHandle[VCORE_VWB_CSC_IDX])
        {
            cfgOvlyPtr = NULL;
            if (NULL != descMem)
            {
                cfgOvlyPtrValue = (UInt32) descMem->shadowOvlyMem +
                                  instObj->ovlyOffset[VCORE_VWB_CSC_IDX];
                cfgOvlyPtr = (void *) cfgOvlyPtrValue;
            }
            retVal = VpsHal_cscSetConfig(
                instObj->halHandle[VCORE_VWB_CSC_IDX],
                &chObj->cscHalCfg,
                cfgOvlyPtr);
            if (BSP_SOK != retVal)
            {
                GT_0trace(VpsVwbCoreTrace, GT_ERR,
                          "CSC HAL Config Overlay Failed!!\r\n");
            }
        }
    }

    /* Configure VPE TOP module */
    if (BSP_SOK == retVal)
    {
        isTda2xx = VpsLib_platformIsTda2xxFamilyBuild();
        /* Mux programming is not required for TI814X family */
        if ((TRUE == isTda2xx) &&
            (NULL != instObj->halHandle[VCORE_VWB_VPETOP_IDX]))
        {
            cfgOvlyPtr = NULL;
            if (NULL != descMem)
            {
                cfgOvlyPtrValue = (UInt32) descMem->shadowOvlyMem +
                                  instObj->ovlyOffset[VCORE_VWB_VPETOP_IDX];
                cfgOvlyPtr = (void *) cfgOvlyPtrValue;
            }
            retVal = VpsHal_vpeTopSetConfig(
                instObj->halHandle[VCORE_VWB_VPETOP_IDX],
                &chObj->vpeTopHalCfg,
                cfgOvlyPtr);
            if (BSP_SOK != retVal)
            {
                GT_0trace(VpsVwbCoreTrace, GT_ERR,
                          "VPE top HAL Config Overlay Failed!!\r\n");
            }
        }
    }

    return (retVal);
}

/**
 *  vcoreVwbProgramDesc
 *  \brief Programs the data descriptor depending on the format set.
 *  This is used in case of non-mosaic mode of operation.
 */
static Int32 vcoreVwbProgramDesc(const Vcore_VwbHandleObj *hObj,
                                 const Vcore_VwbChObj     *chObj,
                                 const Vcore_M2mDescMem   *descMem)
{
    Int32  retVal = BSP_SOK;
    UInt32 descCnt;
    Vcore_VwbInstObj         *instObj;
    VpsHal_VpdmaOutDescParams outDescPrm;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != hObj);
    GT_assert(VpsVwbCoreTrace, NULL != chObj);
    GT_assert(VpsVwbCoreTrace, NULL != descMem);
    instObj = hObj->instObj;
    GT_assert(VpsVwbCoreTrace, NULL != instObj);

    for (descCnt = 0U; descCnt < chObj->numDataDesc; descCnt++)
    {
        outDescPrm.lineStride = chObj->coreFmt.fmt.pitch[descCnt];
        outDescPrm.lineSkip   = VPSHAL_VPDMA_LS_1;
        outDescPrm.notify     = (UInt32) FALSE;
        outDescPrm.priority   = VPS_CFG_M2M_VPDMA_PRIORITY_WR;
        outDescPrm.memType    =
            (VpsHal_VpdmaMemoryType) chObj->coreFmt.memType;
        outDescPrm.maxWidth    = VPS_VPDMA_MAX_OUT_WIDTH_UNLIMITED;
        outDescPrm.maxHeight   = VPS_VPDMA_MAX_OUT_HEIGHT_UNLIMITED;
        outDescPrm.is1DData    = (UInt32) FALSE;
        outDescPrm.dataType    = chObj->vpdmaDataType[descCnt];
        outDescPrm.channel     = chObj->vpdmaCh[descCnt];
        outDescPrm.nextChannel = chObj->vpdmaCh[descCnt];
        outDescPrm.lineSkip    = VPSHAL_VPDMA_LS_1;

        /* Program descriptor */
        GT_assert(VpsVwbCoreTrace, NULL != descMem->outDataDesc[descCnt]);
        retVal = VpsHal_vpdmaCreateOutBoundDataDesc(
            descMem->outDataDesc[descCnt],
            &outDescPrm);
        if (BSP_SOK != retVal)
        {
            GT_0trace(VpsVwbCoreTrace, GT_ERR,
                      "VPDMA Descriptor Creation Failed!!\r\n");
        }
    }

    return retVal;
}

/**
 *  vcoreVwbCheckFmt
 *  \brief Checks whether a given format if valid or not.
 *  Returns BSP_SOK if everything is fine else returns error value.
 */
static Int32 vcoreVwbCheckFmt(const Vcore_M2mFormat *coreFmt)
{
    Int32 retVal = BSP_SOK;
    Bool  isDataFmtYuv422I, isDataFmtYuv420Sp, isDataFmtYuv422Sp;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != coreFmt);

    /* Check whether data format is supported or not */
    isDataFmtYuv422I  = (Bool) Fvid2_isDataFmtYuv422I(coreFmt->fmt.dataFormat);
    isDataFmtYuv420Sp = (Bool) Fvid2_isDataFmtYuv420Sp(coreFmt->fmt.dataFormat);
    isDataFmtYuv422Sp = (Bool) Fvid2_isDataFmtYuv422Sp(coreFmt->fmt.dataFormat);
    if (!((TRUE == isDataFmtYuv422I) ||
          (TRUE == isDataFmtYuv420Sp) ||
          (TRUE == isDataFmtYuv422Sp) ||
          (FVID2_DF_YUV444I == coreFmt->fmt.dataFormat) ||
          (FVID2_DF_RGB24_888 == coreFmt->fmt.dataFormat)))
    {
        GT_1trace(VpsVwbCoreTrace, GT_ERR,
                  "Data format (%d) not supported!!\r\n", coreFmt->fmt.dataFormat);
        retVal = BSP_EINVALID_PARAMS;
    }

    if ((Int32) 0 != Fvid2_isDataFmtYuv422I(coreFmt->fmt.dataFormat))
    {
        /* Check whether the pitch is valid */
        if (coreFmt->fmt.pitch[FVID2_YUV_INT_ADDR_IDX]
            < (coreFmt->fmt.width * 2U))
        {
            GT_2trace(VpsVwbCoreTrace, GT_ERR,
                      "Pitch (%d) less than Width (%d) in bytes!!\r\n",
                      coreFmt->fmt.pitch[FVID2_YUV_INT_ADDR_IDX],
                      (coreFmt->fmt.width * 2U));
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    else if ((Int32) 0 != Fvid2_isDataFmtSemiPlanar(coreFmt->fmt.dataFormat))
    {
        /* Check whether the pitch is valid */
        if (coreFmt->fmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX] < coreFmt->fmt.width)
        {
            GT_2trace(VpsVwbCoreTrace, GT_ERR,
                      "Y Pitch (%d) less than Width (%d) in bytes!!\r\n",
                      coreFmt->fmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX],
                      coreFmt->fmt.width);
            retVal = BSP_EINVALID_PARAMS;
        }
        if (coreFmt->fmt.pitch[FVID2_YUV_SP_CBCR_ADDR_IDX]
            < coreFmt->fmt.width)
        {
            GT_2trace(VpsVwbCoreTrace, GT_ERR,
                      "CbCr Pitch (%d) less than Width (%d) in bytes!!\r\n",
                      coreFmt->fmt.pitch[FVID2_YUV_SP_CBCR_ADDR_IDX],
                      coreFmt->fmt.width);
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    else if ((FVID2_DF_YUV444I == coreFmt->fmt.dataFormat) ||
             (FVID2_DF_RGB24_888 == coreFmt->fmt.dataFormat))
    {
        /* Check whether the pitch is valid */
        if (coreFmt->fmt.pitch[FVID2_RGB_ADDR_IDX] < (coreFmt->fmt.width * 3U))
        {
            GT_2trace(VpsVwbCoreTrace, GT_ERR,
                      "Pitch (%d) less than Width (%d) in bytes!!\r\n",
                      coreFmt->fmt.pitch[FVID2_RGB_ADDR_IDX],
                      (coreFmt->fmt.width * 3U));
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    else
    {
        /* Dummy Else */
    }

    /* Check whether window width is even */
    if (0U != (coreFmt->fmt.width & 0x01U))
    {
        GT_1trace(VpsVwbCoreTrace, GT_ERR,
                  "Width(%d) can't be odd!!\r\n", coreFmt->fmt.width);
        retVal = BSP_EINVALID_PARAMS;
    }

    if ((Int32) 0 != Fvid2_isDataFmtYuv420Sp(coreFmt->fmt.dataFormat))
    {
        /* Check whether window height/startY is even for YUV420 format */
        if ((0U != (coreFmt->fmt.height & 0x01U)) ||
            (0U != (coreFmt->startY & 0x01U)))
        {
            GT_2trace(
                VpsVwbCoreTrace, GT_ERR,
                "Height(%d)/StartY(%d) can't be odd for YUV420 format!!\r\n",
                coreFmt->fmt.height,
                coreFmt->startY);
            retVal = BSP_EINVALID_PARAMS;
        }
    }

    return (retVal);
}

/**
 *  vcoreVwbAllocHandleObj
 *  \brief Allocates handle object from the available pool of handle objects.
 *  Returns error if allocation failed or if invalid mode is requested.
 */
static Vcore_VwbHandleObj *vcoreVwbAllocHandleObj(UInt32 instId)
{
    UInt32 instCnt, hCnt;
    Vcore_VwbInstObj   *instObj = NULL;
    Vcore_VwbHandleObj *hObj    = NULL;

    /* Find out the instance to which this handle belongs to */
    for (instCnt = 0U; instCnt < VCORE_VWB_NUM_INST; instCnt++)
    {
        if (VwbInstObjects[instCnt].instId == instId)
        {
            instObj = &VwbInstObjects[instCnt];
            break;
        }
    }

    BspOsal_semWait(VcoreVwbPoolObjs.lockSem, BSP_OSAL_WAIT_FOREVER);

    if (NULL != instObj)
    {
        /* Use a free handle object */
        for (hCnt = 0U; hCnt < instObj->numHandle; hCnt++)
        {
            if (FALSE == instObj->hObjs[hCnt].isUsed)
            {
                hObj = &instObj->hObjs[hCnt];
                break;
            }
        }
    }

    if (NULL != hObj)
    {
        /* Update the state and return the handle */
        hObj->isUsed  = (UInt32) TRUE;
        hObj->instObj = instObj;
        instObj->openCnt++;
    }

    BspOsal_semPost(VcoreVwbPoolObjs.lockSem);

    return (hObj);
}

/**
 *  vcoreVwbFreeHandleObj
 *  \brief Frees-up the handle object and resets the variables.
 */
static Int32 vcoreVwbFreeHandleObj(Vcore_VwbHandleObj *hObj)
{
    UInt32 hCnt;
    Int32  retVal = BSP_EFAIL;
    Vcore_VwbInstObj *instObj;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != hObj);
    instObj = hObj->instObj;
    GT_assert(VpsVwbCoreTrace, NULL != instObj);

    BspOsal_semWait(VcoreVwbPoolObjs.lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Free the handle object */
    for (hCnt = 0U; hCnt < instObj->numHandle; hCnt++)
    {
        if (hObj == &instObj->hObjs[hCnt])
        {
            /* Check if the handle is already allocated */
            GT_assert(VpsVwbCoreTrace, TRUE == instObj->hObjs[hCnt].isUsed);

            /* Reset the variables */
            hObj->isUsed  = (UInt32) FALSE;
            hObj->instObj = NULL;
            hObj->numCh   = 0U;

            /* If last handle of the instance, then set mode to invalid */
            if (instObj->openCnt > 0U)
            {
                instObj->openCnt--;
            }

            retVal = BSP_SOK;
            break;
        }
    }

    BspOsal_semPost(VcoreVwbPoolObjs.lockSem);

    return (retVal);
}

/**
 *  vcoreVwbAllocChObj
 *  \brief Allocates channel objects.
 *  Returns error if allocation failed.
 */
static Int32 vcoreVwbAllocChObj(Vcore_VwbChObj **chObjs, UInt32 numCh)
{
    Int32  retVal = BSP_SOK;
    UInt32 chCnt;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != chObjs);

    for (chCnt = 0U; chCnt < numCh; chCnt++)
    {
        /* Allocate channel objects one at a time */
        chObjs[chCnt] = (Vcore_VwbChObj *)
                        BspUtils_alloc(
            &VcoreVwbPoolObjs.chPoolPrm,
            sizeof (Vcore_VwbChObj),
            VpsVwbCoreTrace);
        if (NULL == chObjs[chCnt])
        {
            GT_1trace(VpsVwbCoreTrace, GT_ERR,
                      "Channel Object memory alloc failed for channel %d!!\r\n",
                      chCnt);
            retVal = BSP_EALLOC;
            break;
        }

        /* Set default values for the channel object */
        vcoreVwbSetDefChInfo(chObjs[chCnt], chCnt);
    }

    /* If error, free-up the already allocated objects */
    if (BSP_SOK != retVal)
    {
        vcoreVwbFreeChObj(chObjs, chCnt);
    }

    return (retVal);
}

/**
 *  vcoreVwbFreeChObj
 *  \brief Frees-up the channel objects.
 */
static Int32 vcoreVwbFreeChObj(Vcore_VwbChObj **chObjs, UInt32 numCh)
{
    UInt32          chCnt;
    Int32           retVal = BSP_SOK;
    Vcore_VwbChObj *chObj;

    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != chObjs);

    for (chCnt = 0U; chCnt < numCh; chCnt++)
    {
        chObj = chObjs[chCnt];
        GT_assert(VpsVwbCoreTrace, NULL != chObj);

        /* Memset the channel object before freeing */
        BspUtils_memset(chObj, 0U, sizeof (Vcore_VwbChObj));
        retVal += BspUtils_free(
            &VcoreVwbPoolObjs.chPoolPrm,
            chObj,
            VpsVwbCoreTrace);
        chObjs[chCnt] = NULL;
    }

    return (retVal);
}

/**
 *  vcoreVwbSetDefChInfo
 *  \brief Resets the channel information with default values.
 */
static void vcoreVwbSetDefChInfo(Vcore_VwbChObj *chObj, UInt32 chNum)
{
    /* NULL pointer check */
    GT_assert(VpsVwbCoreTrace, NULL != chObj);

    /* Set proper states */
    chObj->state.isFormatSet = (UInt32) FALSE;
    chObj->state.isParamsSet = (UInt32) FALSE;

    /* Initialize core format - Assumes YUV422 720x480 progressive */
    chObj->coreFmt.frameWidth  = VCORE_VWB_DEFAULT_WIDTH;
    chObj->coreFmt.frameHeight = VCORE_VWB_DEFAULT_HEIGHT;
    chObj->coreFmt.startX      = 0U;
    chObj->coreFmt.startY      = 0U;
    chObj->coreFmt.secScanFmt  = FVID2_SF_PROGRESSIVE;
    chObj->coreFmt.memType     = (UInt32) VPSHAL_VPDMA_MT_NONTILEDMEM;

    chObj->coreFmt.fmt.chNum  = chNum;
    chObj->coreFmt.fmt.width  = VCORE_VWB_DEFAULT_WIDTH;
    chObj->coreFmt.fmt.height = VCORE_VWB_DEFAULT_HEIGHT;
    chObj->coreFmt.fmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
        VCORE_VWB_DEFAULT_WIDTH * 2U;
    chObj->coreFmt.fmt.fieldMerged[FVID2_YUV_INT_ADDR_IDX] = (UInt32) FALSE;
    chObj->coreFmt.fmt.dataFormat = FVID2_DF_YUV422I_YUYV;
    chObj->coreFmt.fmt.scanFormat = FVID2_SF_PROGRESSIVE;
    chObj->coreFmt.fmt.bpp        = FVID2_BPP_BITS16;
    chObj->coreFmt.fmt.reserved   = NULL;

    /* Initialize channel descriptor info structure */
    BspUtils_memset(&chObj->descInfo, 0U, sizeof (Vcore_M2mDescInfo));

    return;
}

