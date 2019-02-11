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
 *  \file vpscore_vpeCommon.c
 *
 *  \brief VPS VPE Path Core internal file containing functiosn for allocation
 *  and freeing of handle/channel and other objects.
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

/**
 *  \brief Maximum number of channel objects to be statically allocated for all
 *  the instances. Each of the channels in an instance is assumed to be
 *  shared across all handles of that instance.
 *  All the handles will allocate channel objects from this pool only.
 *  Instead of allocating VCORE_VPE_MAX_HANDLES * VCORE_VPE_MAX_CHANNELS
 *  objects per instance, only the below number of objects are allocated
 *  to save memory.
 */
#define VCORE_VPE_MAX_CHANNEL_OBJECTS   (VCORE_VPE_MAX_CHANNELS * \
                                         VCORE_VPE_INST_MAX)

/** \brief Default width used for initializing format structure. */
#define VCORE_VPE_DEFAULT_WIDTH         (720U)
/** \brief Default height used for initializing format structure. */
#define VCORE_VPE_DEFAULT_HEIGHT        (480U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vcore_VpePoolObj
 *  Memory pool object containing all the statically allocated
 *  objects - used structure to avoid multiple global variables.
 */
typedef struct
{
    Vcore_VpeChObj      chMemPool[VCORE_VPE_MAX_CHANNEL_OBJECTS];
    /**< Memory pool for the channel objects. */
    UInt32              chMemFlag[VCORE_VPE_MAX_CHANNEL_OBJECTS];
    /**< The flag variable represents whether a channel memory is allocated
     *   or not. */
    BspUtils_PoolParams chPoolPrm;
    /**< Pool params for descriptor pool memory. */

    BspOsal_SemHandle   lockSem;
    /**< Semaphore for protecting allocation and freeing of memory pool
     *   objects at open/close time. */
} Vcore_VpePoolObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void vcoreVpeSetDefChInfo(Vcore_VpeChObj *chObj, UInt32 chNum);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief VPE path instance objects. */
static Vcore_VpeInstObj gVpeCoreInstObjs[VCORE_VPE_INST_MAX];

/**
 *  \brief Pool objects used for storing pool memories, pool flags and pool
 *  handles.
 */
static Vcore_VpePoolObj gVpeCorePoolObjs;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  vcoreVpeInit
 *  \brief Initializes VPE core objects, allocates memory etc.
 *  Returns BSP_SOK on success else returns error value.
 */
Int32 vcoreVpeInit(UInt32 numInst, const Vcore_VpeInitParams *initPrms)
{
    Int32  retVal = BSP_SOK;
    UInt32 instCnt, hCnt, chCnt;
    Vcore_VpeInstObj *instObj;

    /* Check for errors */
    GT_assert(VpsVpeCoreTrace, numInst <= VCORE_VPE_INST_MAX);
    GT_assert(VpsVpeCoreTrace, NULL != initPrms);

    /* Init pool objects */
    BspUtils_initPool(
        &gVpeCorePoolObjs.chPoolPrm,
        (void *) gVpeCorePoolObjs.chMemPool,
        (UInt32) VCORE_VPE_MAX_CHANNEL_OBJECTS,
        sizeof (Vcore_VpeChObj),
        gVpeCorePoolObjs.chMemFlag,
        VpsVpeCoreTrace);

    /* Create Pool Semaphore */
    gVpeCorePoolObjs.lockSem = BspOsal_semCreate((Int32) 1, TRUE);
    if (NULL == gVpeCorePoolObjs.lockSem)
    {
        GT_0trace(VpsVpeCoreTrace, GT_ERR, "Sem create failed!!\r\n");
        retVal = BSP_EALLOC;
    }
    else
    {
        for (instCnt = 0U; instCnt < numInst; instCnt++)
        {
            /* Initialize instance object members */
            instObj            = &gVpeCoreInstObjs[instCnt];
            instObj->instId    = initPrms[instCnt].instId;
            instObj->numHandle = initPrms[instCnt].maxHandle;
            instObj->vpdmaPath = initPrms[instCnt].vpdmaPath;
            /* Get the VPDMA channels */
            for (chCnt = 0U; chCnt < VCORE_VPE_MAX_VPDMA_CH; chCnt++)
            {
                instObj->vpdmaCh[chCnt] = initPrms[instCnt].vpdmaCh[chCnt];
            }

            instObj->openCnt          = 0U;
            instObj->numDescPerWindow = VCORE_VPE_NUM_DESC_PER_WINDOW;

            /* Mark all handles as free */
            for (hCnt = 0U; hCnt < VCORE_VPE_MAX_HANDLES; hCnt++)
            {
                instObj->hObjs[hCnt].isUsed = (UInt32) FALSE;
            }

            /* Assign HAL parmaters of instance object */
            vcoreVpeInitHalParams(instObj, &initPrms[instCnt]);
        }
    }

    return (retVal);
}

/**
 *  vcoreVpeDeInit
 *  \brief Deallocates memory allocated by init function.
 *  Returns BSP_SOK on success else returns error value.
 */
Int32 vcoreVpeDeInit(void)
{
    UInt32 instCnt;
    UInt32 halCnt;
    Vcore_VpeInstObj *instObj;

    for (instCnt = 0U; instCnt < VCORE_VPE_INST_MAX; instCnt++)
    {
        instObj            = &gVpeCoreInstObjs[instCnt];
        instObj->instId    = 0U;
        instObj->numHandle = 0U;
        for (halCnt = 0U; halCnt < VCORE_VPE_MAX_HAL; halCnt++)
        {
            instObj->halHandle[halCnt]         = NULL;
            instObj->halShadowOvlySize[halCnt] = 0U;
            instObj->ovlyOffset[halCnt]        = 0U;
        }
    }

    /* Delete the Semaphore created for pool objects */
    if (NULL != gVpeCorePoolObjs.lockSem)
    {
        BspOsal_semDelete(&gVpeCorePoolObjs.lockSem);
        gVpeCorePoolObjs.lockSem = NULL;
    }

    return (BSP_SOK);
}

/**
 *  vcoreVpeAllocHandleObj
 *  \brief Allocates handle object from the available pool of handle objects.
 *  Returns error if allocation failed or if invalid mode is requested.
 */
Vcore_VpeHandleObj *vcoreVpeAllocHandleObj(UInt32 instId)
{
    UInt32 instCnt, hCnt;
    Vcore_VpeInstObj   *instObj = NULL;
    Vcore_VpeHandleObj *hObj    = NULL;

    /* Find out the instance to which this handle belongs to */
    for (instCnt = 0U; instCnt < VCORE_VPE_INST_MAX; instCnt++)
    {
        if (gVpeCoreInstObjs[instCnt].instId == instId)
        {
            instObj = &gVpeCoreInstObjs[instCnt];
            break;
        }
    }

    BspOsal_semWait(gVpeCorePoolObjs.lockSem, BSP_OSAL_WAIT_FOREVER);

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
        /* Update the state and return the handle handle */
        hObj->isUsed  = (UInt32) TRUE;
        hObj->instObj = instObj;
        instObj->openCnt++;
    }

    BspOsal_semPost(gVpeCorePoolObjs.lockSem);

    return (hObj);
}

/**
 *  vcoreVpeFreeHandleObj
 *  \brief Frees-up the handle object and resets the variables.
 */
Int32 vcoreVpeFreeHandleObj(Vcore_VpeHandleObj *hObj)
{
    Int32  retVal = BSP_EFAIL;
    UInt32 hCnt;
    Vcore_VpeInstObj *instObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    BspOsal_semWait(gVpeCorePoolObjs.lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Free the handle object */
    for (hCnt = 0U; hCnt < instObj->numHandle; hCnt++)
    {
        if (hObj == &instObj->hObjs[hCnt])
        {
            /* Check if the handle is already allocated */
            GT_assert(VpsVpeCoreTrace, TRUE == instObj->hObjs[hCnt].isUsed);

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

    BspOsal_semPost(gVpeCorePoolObjs.lockSem);

    return (retVal);
}

/**
 *  vcoreVpeAllocChObjs
 *  \brief Allocates channel objects.
 *  Returns error if allocation failed.
 */
Int32 vcoreVpeAllocChObjs(Vcore_VpeHandleObj *hObj, UInt32 numCh)
{
    Int32  retVal = BSP_SOK;
    UInt32 chCnt;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);

    for (chCnt = 0U; chCnt < numCh; chCnt++)
    {
        /* Allocate channel objects one at a time */
        hObj->chObjs[chCnt] = (Vcore_VpeChObj *)
                              BspUtils_alloc(
            &gVpeCorePoolObjs.chPoolPrm,
            sizeof (Vcore_VpeChObj),
            VpsVpeCoreTrace);
        if (NULL == hObj->chObjs[chCnt])
        {
            GT_1trace(VpsVpeCoreTrace, GT_ERR,
                      "Channel Object memory alloc failed for channel %d!!\r\n",
                      chCnt);
            retVal = BSP_EALLOC;
            break;
        }

        /* Set default values for the channel object */
        vcoreVpeSetDefChInfo(hObj->chObjs[chCnt], chCnt);
    }

    /* If error, free-up the already allocated objects */
    if (BSP_SOK != retVal)
    {
        vcoreVpeFreeChObjs(hObj, chCnt);
    }

    return (retVal);
}

/**
 *  vcoreVpeFreeChObjs
 *  \brief Frees-up the channel objects.
 */
Int32 vcoreVpeFreeChObjs(Vcore_VpeHandleObj *hObj, UInt32 numCh)
{
    UInt32          retVal = (UInt32) BSP_SOK;
    UInt32          chCnt;
    Vcore_VpeChObj *chObj;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);

    for (chCnt = 0U; chCnt < numCh; chCnt++)
    {
        chObj = hObj->chObjs[chCnt];
        GT_assert(VpsVpeCoreTrace, NULL != chObj);

        /* Memset the channel object before freeing */
        BspUtils_memset(hObj->chObjs[chCnt], 0U, sizeof (Vcore_VpeChObj));
        retVal |= (UInt32) BspUtils_free(
            &gVpeCorePoolObjs.chPoolPrm,
            chObj,
            VpsVpeCoreTrace);
        hObj->chObjs[chCnt] = NULL;
    }

    return (Int32) retVal;
}

/**
 *  vcoreVpeCheckParams
 *  \brief Checks whether a given parameters are valid or not.
 *  Returns BSP_SOK if everything is fine else returns error value.
 */
Int32 vcoreVpeCheckParams(const Vcore_VpeInstObj *instObj,
                          const Vcore_VpeParams  *corePrms)
{
    Int32 retVal = BSP_SOK;
    Int32 isDataFmtYuv422I, isDataFmtYuv422Sp, isDataFmtYuv420Sp;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != corePrms);

    /* Check whether data format is supported or not */
    isDataFmtYuv422I  = Fvid2_isDataFmtYuv422I(corePrms->fmt.dataFormat);
    isDataFmtYuv422Sp = Fvid2_isDataFmtYuv422Sp(corePrms->fmt.dataFormat);
    isDataFmtYuv420Sp = Fvid2_isDataFmtYuv420Sp(corePrms->fmt.dataFormat);
    if (((Int32) FALSE == isDataFmtYuv422I) &&
        ((Int32) FALSE == isDataFmtYuv422Sp) &&
        ((Int32) FALSE == isDataFmtYuv420Sp))
    {
        GT_1trace(VpsVpeCoreTrace, GT_ERR,
                  "Data format (%d) not supported!!\r\n",
                  corePrms->fmt.dataFormat);
        retVal = BSP_EINVALID_PARAMS;
    }

    if (((Int32) TRUE == isDataFmtYuv422I))
    {
        /* Check whether the pitch is valid */
        if (corePrms->fmt.pitch[FVID2_YUV_INT_ADDR_IDX]
            < (corePrms->fmt.width * 2U))
        {
            GT_2trace(VpsVpeCoreTrace, GT_ERR,
                      "Pitch (%d) less than Width (%d) in bytes!!\r\n",
                      corePrms->fmt.pitch[FVID2_YUV_INT_ADDR_IDX],
                      (corePrms->fmt.width * 2U));
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    else if (((Int32) TRUE == isDataFmtYuv422Sp) ||
             ((Int32) TRUE == isDataFmtYuv420Sp))
    {
        /* Check whether the pitch is valid */
        if (corePrms->fmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX] < corePrms->fmt.width)
        {
            GT_2trace(VpsVpeCoreTrace, GT_ERR,
                      "Y Pitch (%d) less than Width (%d) in bytes!!\r\n",
                      corePrms->fmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX],
                      corePrms->fmt.width);
            retVal = BSP_EINVALID_PARAMS;
        }
        if (corePrms->fmt.pitch[FVID2_YUV_SP_CBCR_ADDR_IDX]
            < corePrms->fmt.width)
        {
            GT_2trace(VpsVpeCoreTrace, GT_ERR,
                      "CbCr Pitch (%d) less than Width (%d) in bytes!!\r\n",
                      corePrms->fmt.pitch[FVID2_YUV_SP_CBCR_ADDR_IDX],
                      corePrms->fmt.width);
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    else
    {
        /* Dummy else block */
    }

    /* Check whether window width/startX is even */
    if (((corePrms->fmt.width & 0x01U) == 0x01U) ||
        ((corePrms->startX & 0x01U) == 0x01U))
    {
        GT_2trace(VpsVpeCoreTrace, GT_ERR,
                  "Width(%d)/StartX(%d) can't be odd!!\r\n",
                  corePrms->fmt.width,
                  corePrms->startX);
        retVal = BSP_EINVALID_PARAMS;
    }

    if (instObj->halHandle[VCORE_VPE_DEI_IDX] == NULL)
    {
        if ((FVID2_SF_INTERLACED == corePrms->fmt.scanFormat) &&
            (FVID2_SF_PROGRESSIVE == corePrms->secScanFmt))
        {
            GT_0trace(
                VpsVpeCoreTrace, GT_ERR,
                "Interlaced to progressive is not supported for this instance\r\n");
            retVal = BSP_EINVALID_PARAMS;
        }
        if ((FVID2_SF_PROGRESSIVE == corePrms->fmt.scanFormat) &&
            (FVID2_SF_INTERLACED == corePrms->secScanFmt))
        {
            GT_0trace(
                VpsVpeCoreTrace, GT_ERR,
                "Progressive to interlaced is not supported for this instance\r\n");
            retVal = BSP_EINVALID_PARAMS;
        }
    }

    if (Fvid2_isDataFmtYuv420Sp(corePrms->fmt.dataFormat))
    {
        /* Check whether window height/startY is even for YUV420 format */
        if (((corePrms->fmt.height & 0x01U) == 0x01U) ||
            ((corePrms->startY & 0x01U) == 0x01U))
        {
            GT_2trace(
                VpsVpeCoreTrace, GT_ERR,
                "Height(%d)/StartY(%d) can't be odd for YUV420 format!!\r\n",
                corePrms->fmt.height,
                corePrms->startY);
            retVal = BSP_EINVALID_PARAMS;
        }
    }

    /* Check whether the active window is within frame limit */
    if (corePrms->frameWidth < (corePrms->startX + corePrms->fmt.width))
    {
        GT_2trace(VpsVpeCoreTrace, GT_ERR,
                  "Frame Width (%d) less than Width + HOffset (%d)!!\r\n",
                  corePrms->frameWidth,
                  (corePrms->startX + corePrms->fmt.width));
        retVal = BSP_EINVALID_PARAMS;
    }
    if (corePrms->frameHeight < (corePrms->startY + corePrms->fmt.height))
    {
        GT_2trace(VpsVpeCoreTrace, GT_ERR,
                  "Frame Height (%d) less than Height + VOffset (%d)!!\r\n",
                  corePrms->frameHeight,
                  (corePrms->startY + corePrms->fmt.height));
        retVal = BSP_EINVALID_PARAMS;
    }

    if (FVID2_SOK == retVal)
    {
        retVal = VpsHal_vpdmaIsValidSize(
            instObj->vpdmaPath,
            (Bool) Fvid2_isDataFmtYuv422I(corePrms->fmt.dataFormat),
            (VpsHal_VpdmaMemoryType) corePrms->memType,
            corePrms->fmt.width,
            corePrms->fmt.height);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR, "Wrong Input Size!!\r\n");
        }
    }

    return (retVal);
}

/**
 *  vcoreVpeSetDefChInfo
 *  \brief Resets the channel information with default values.
 */
static void vcoreVpeSetDefChInfo(Vcore_VpeChObj *chObj, UInt32 chNum)
{
    UInt32 chCnt, cnt;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    /* Set proper states */
    chObj->state.isFormatSet = (UInt32) FALSE;
    chObj->state.isParamsSet = (UInt32) FALSE;

    /* Initialize core parameters - Assumes YUV422 720x480 progressive */
    chObj->corePrms.frameWidth  = VCORE_VPE_DEFAULT_WIDTH;
    chObj->corePrms.frameHeight = VCORE_VPE_DEFAULT_HEIGHT;
    chObj->corePrms.startX      = 0U;
    chObj->corePrms.startY      = 0U;
    chObj->corePrms.secScanFmt  = FVID2_SF_PROGRESSIVE;
    chObj->corePrms.memType     =
        (UInt32) VPSHAL_VPDMA_MT_NONTILEDMEM;

    chObj->corePrms.fmt.chNum  = chNum;
    chObj->corePrms.fmt.width  = VCORE_VPE_DEFAULT_WIDTH;
    chObj->corePrms.fmt.height = VCORE_VPE_DEFAULT_HEIGHT;
    chObj->corePrms.fmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
        VCORE_VPE_DEFAULT_WIDTH * 2U;
    chObj->corePrms.fmt.fieldMerged[FVID2_YUV_INT_ADDR_IDX] = (UInt32) FALSE;
    chObj->corePrms.fmt.dataFormat = FVID2_DF_YUV422I_YUYV;
    chObj->corePrms.fmt.scanFormat = FVID2_SF_PROGRESSIVE;
    chObj->corePrms.fmt.bpp        = FVID2_BPP_BITS16;
    chObj->corePrms.fmt.reserved   = NULL;

    /* Initialize DEI HAL parameters */
    chObj->corePrms.deiCfg.bypass              = (UInt32) TRUE;
    chObj->corePrms.deiCfg.spatMaxBypass       = (UInt32) FALSE;
    chObj->corePrms.deiCfg.tempMaxBypass       = (UInt32) FALSE;
    chObj->corePrms.deiCfg.inpMode             = VPS_DEI_EDIMODE_LUMA_CHROMA;
    chObj->corePrms.deiCfg.tempInpEnable       = (UInt32) TRUE;
    chObj->corePrms.deiCfg.tempInpChromaEnable = (UInt32) TRUE;

    /* Initialize SC parameters */
    chObj->corePrms.scCfg.bypass       = (UInt32) TRUE;
    chObj->corePrms.cropCfg.cropStartX = 0U;
    chObj->corePrms.cropCfg.cropStartY = 0U;
    chObj->corePrms.cropCfg.cropWidth  = VCORE_VPE_DEFAULT_WIDTH;
    chObj->corePrms.cropCfg.cropHeight = VCORE_VPE_DEFAULT_HEIGHT;
    chObj->corePrms.scCfg.nonLinear    = (UInt32) FALSE;
    chObj->corePrms.scCfg.stripSize    = 0U;
    chObj->corePrms.tarWidth           = VCORE_VPE_DEFAULT_WIDTH;
    chObj->corePrms.tarHeight          = VCORE_VPE_DEFAULT_HEIGHT;

    /* Initialize channel descriptor info structure */
    BspUtils_memset(&chObj->descInfo, 0U, sizeof (Vcore_M2mDescInfo));
    BspUtils_memset(chObj->descOffset, 0U, sizeof (chObj->descOffset));
    chObj->numExtraDesc  = 0U;
    chObj->isDummyNeeded = FALSE;
    chObj->fsEvent       = VPSHAL_VPDMA_FSEVENT_CHANNEL_ACTIVE;

    /* Initialize DEI state machine */
    chObj->ctxInfo.isDeinterlacing = (UInt32) FALSE;
    chObj->ctxInfo.isTnrMode       = (UInt32) FALSE;
    chObj->ctxInfo.numPrevFld      = 0U;
    chObj->ctxInfo.numMvIn         = 0U;
    chObj->ctxInfo.numMvOut        = 0U;
    chObj->ctxInfo.numMvstmIn      = 0U;
    chObj->ctxInfo.numMvstmOut     = 0U;
    chObj->ctxInfo.numCurFldOut    = 0U;
    for (chCnt = 0U; chCnt < VCORE_VPE_MAX_VPDMA_CH; chCnt++)
    {
        chObj->isDescReq[chCnt]   = (UInt32) FALSE;
        chObj->isDescDummy[chCnt] = (UInt32) FALSE;
    }
    for (cnt = 0U; cnt < VCORE_VPE_NUM_DESC_PER_WINDOW; cnt++)
    {
        chObj->bufIndex[cnt] = FVID2_YUV_INT_ADDR_IDX;
    }

    return;
}

