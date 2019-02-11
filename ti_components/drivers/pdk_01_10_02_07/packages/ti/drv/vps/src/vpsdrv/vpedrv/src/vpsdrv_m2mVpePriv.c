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
 *  \file vpsdrv_m2mVpePriv.c
 *
 *  \brief VPS VPE M2M driver internal file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <vpedrv/src/vpsdrv_m2mVpePriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief This is the max descriptor mem required per ch calculated as below.
 *  In desc (data) (7) = VCORE_VPE_NUM_DESC_PER_WINDOW(2) +
 *                       numPrevFld(2) * VCORE_VPE_NUM_DESC_PER_FIELD(2) +
 *                       numMvIn(1)
 *  out Desc (data) (3) = numCurFldOut(1) * VCORE_VPE_NUM_DESC_PER_FIELD(2) +
 *                        numMvOut(1) = (3)
 *  cfg desc (4) = VPSMDRV_VPE_MAX_SHW_CFG_DESC(1) +
 *                 VPSMDRV_VPE_MAX_NSHW_CFG_DESC(1) +
 *                 VPS_M2M_SCALER_ID_MAX(1) *
 *                 VPSMDRV_VPE_RT_COEFF_CFG_DESC_PER_SC(2)
 *  ctrl desc (18) = VCORE_VPE_MAX_VPDMA_CH(17) + VPSMDRV_VPE_MAX_RLD_DESC (1)
 *
 *  Data descriptor size = 32, Config/Control descriptor size = 16
 *
 *  total descriptor size = (7 + 3) * 32 + (4 + 18) * 16 = 672
 */
#define VPS_M2M_VPE_TOTAL_DESC_MEM_PER_CH  (672)

/** \brief This is calculated as per the current register map. */
#define VPS_M2M_VPE_NSHW_OVLY_DESC_MEM     (128)

/** \brief This is calculated as per the current register map. */
#define VPS_M2M_VPE_SHW_OVLY_DESC_MEM      (512)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 vpsMdrvVpeAllocChObjs(VpsMdrv_VpeHandleObj *hObj, UInt32 numCh);
static Int32 vpsMdrvVpeFreeChObjs(VpsMdrv_VpeHandleObj *hObj, UInt32 numCh);

static Int32 vpsMdrvVpeAllocChDescMem(VpsMdrv_VpeHandleObj *hObj,
                                      VpsMdrv_VpeChObj     *chObj);
static Int32 vpsMdrvVpeFreeChDescMem(VpsMdrv_VpeChObj *chObj);
static Int32 vpsMdrvVpeCalcChCtxMem(const VpsMdrv_VpeHandleObj *hObj,
                                    VpsMdrv_VpeChObj           *chObj);

static Int32 vpsMdrvVpeFreeChCtxMem(VpsMdrv_VpeChObj *chObj);

static Int32 vpsMdrvVpeSplitChDescMem(VpsMdrv_VpeHandleObj *hObj,
                                      VpsMdrv_VpeChObj     *chObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief VPE M2M driver instance objects. */
static VpsMdrv_VpeInstObj VpsMdrvVpeInstObjects[VPS_M2M_VPE_INST_MAX];

/**
 *  \brief VPE M2M driver pool objects used for storing pool memories, pool
 *  flags and pool handles.
 */
VpsMdrv_VpePoolObj        gVpsMdrvVpePoolObj;

/* Align descriptor memory with that of VPDMA requirement. */
/* Place the descriptor in non-cached section. */
#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsMdrvVpeCoeffDescMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsMdrvVpeCoeffDescMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt8 gVpsMdrvVpeCoeffDescMem[VPSMDRV_VPE_MAX_COEFF_DESC_MEM];
/* Align descriptor memory with that of VPDMA requirement. */
/* Place the descriptor in non-cached section. */
#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsMdrvVpeTotalDescMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsMdrvVpeTotalDescMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt8 gVpsMdrvVpeTotalDescMem[VPSMDRV_VPE_MAX_CH_MEM_POOL][
    VPS_M2M_VPE_TOTAL_DESC_MEM_PER_CH];

/* Align descriptor memory with that of VPDMA requirement. */
/* Place the descriptor in non-cached section. */
#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsMdrvVpeNshwOvlyDescMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsMdrvVpeNshwOvlyDescMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt8 gVpsMdrvVpeNshwOvlyDescMem[VPSMDRV_VPE_MAX_CH_MEM_POOL][
    VPS_M2M_VPE_NSHW_OVLY_DESC_MEM];

/* Align descriptor memory with that of VPDMA requirement. */
/* Place the descriptor in non-cached section. */
#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsMdrvVpeShwOvlyDescMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsMdrvVpeShwOvlyDescMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt8 gVpsMdrvVpeShwOvlyDescMem[VPSMDRV_VPE_MAX_CH_MEM_POOL][
    VPS_M2M_VPE_SHW_OVLY_DESC_MEM];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  vpsMdrvVpeInit
 *  Initializes VPE M2M driver objects, allocates memory etc.
 *  Returns BSP_SOK on success else returns error value.
 */
Int32 vpsMdrvVpeInit(UInt32                       numInst,
                     const VpsMdrv_VpeInitParams *initPrms)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt, coreCnt, scalerId;
    VpsMdrv_VpeInstObj *instObj;
    Int32  initValue;

    /* Check for errors */
    GT_assert(VpsMdrvVpeTrace, (numInst <= VPS_M2M_VPE_INST_MAX));
    GT_assert(VpsMdrvVpeTrace, (NULL != initPrms));

    /* Initialize driver objects to zero */
    BspUtils_memset(VpsMdrvVpeInstObjects, 0U, sizeof (VpsMdrvVpeInstObjects));
    BspUtils_memset(&gVpsMdrvVpePoolObj, 0U, sizeof (gVpsMdrvVpePoolObj));

    /* Init pool objects */
    BspUtils_initPool(
        &gVpsMdrvVpePoolObj.handlePoolPrm,
        (void *) gVpsMdrvVpePoolObj.handleMemPool,
        VPSMDRV_VPE_MAX_HANDLE_MEM_POOL,
        sizeof (VpsMdrv_VpeHandleObj),
        gVpsMdrvVpePoolObj.handleMemFlag,
        VpsMdrvVpeTrace);
    BspUtils_initPool(
        &gVpsMdrvVpePoolObj.chPoolPrm,
        (void *) gVpsMdrvVpePoolObj.chMemPool,
        VPSMDRV_VPE_MAX_CH_MEM_POOL,
        sizeof (VpsMdrv_VpeChObj),
        gVpsMdrvVpePoolObj.chMemFlag,
        VpsMdrvVpeTrace);

    BspUtils_initPool(
        &gVpsMdrvVpePoolObj.totalDescMemPoolPrm,
        (void *) gVpsMdrvVpeTotalDescMem,
        VPSMDRV_VPE_MAX_CH_MEM_POOL,
        (sizeof (gVpsMdrvVpeTotalDescMem) / VPSMDRV_VPE_MAX_CH_MEM_POOL),
        gVpsMdrvVpePoolObj.totalDescMemFlag,
        VpsMdrvVpeTrace);
    BspUtils_initPool(
        &gVpsMdrvVpePoolObj.nshwOvlyDescMemPoolPrm,
        (void *) gVpsMdrvVpeNshwOvlyDescMem,
        VPSMDRV_VPE_MAX_CH_MEM_POOL,
        (sizeof (gVpsMdrvVpeNshwOvlyDescMem) / VPSMDRV_VPE_MAX_CH_MEM_POOL),
        gVpsMdrvVpePoolObj.nshwOvlyDescMemFlag,
        VpsMdrvVpeTrace);
    BspUtils_initPool(
        &gVpsMdrvVpePoolObj.shwOvlyDescMemPoolPrm,
        (void *) gVpsMdrvVpeShwOvlyDescMem,
        VPSMDRV_VPE_MAX_CH_MEM_POOL,
        (sizeof (gVpsMdrvVpeShwOvlyDescMem) / VPSMDRV_VPE_MAX_CH_MEM_POOL),
        gVpsMdrvVpePoolObj.shwOvlyDescMemFlag,
        VpsMdrvVpeTrace);

    /* Initialize instance object members */
    for (instCnt = 0U; instCnt < numInst; instCnt++)
    {
        /* VPE path core should be present */
        GT_assert(VpsMdrvVpeTrace,
                  (NULL != initPrms->coreOps[VPSMDRV_VPE_VPE_CORE_IDX]));

        instObj = &VpsMdrvVpeInstObjects[instCnt];

        /* Allocate instance semaphore */
        initValue        = 1;
        instObj->instSem = BspOsal_semCreate(initValue, (Bool) TRUE);
        if (NULL == instObj->instSem)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Instance semaphore create failed!!\r\n");
            retVal = FVID2_EALLOC;
            break;
        }

        /* Copy the information */
        instObj->drvInstId = initPrms->drvInstId;
        for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
        {
            instObj->coreInstId[coreCnt] = initPrms->coreInstId[coreCnt];
            instObj->coreOps[coreCnt]    = initPrms->coreOps[coreCnt];
            /* If core ops is NULL then that particular core is not used */
            if (NULL == instObj->coreOps[coreCnt])
            {
                instObj->isCoreReq[coreCnt] = (UInt32) FALSE;
            }
            else
            {
                instObj->isCoreReq[coreCnt] = (UInt32) TRUE;
            }
        }

        /* Figure out how many input framelists are required for an instance */
        instObj->numInListReq = 0U;
        if ((UInt32) TRUE == instObj->isCoreReq[VPSMDRV_VPE_VPE_CORE_IDX])
        {
            instObj->numInListReq++;
        }

        /* Figure out how many output framelists are required for an instance */
        instObj->numOutListReq = 0U;
        if ((UInt32) TRUE == instObj->isCoreReq[VPSMDRV_VPE_VWB_CORE_IDX])
        {
            instObj->numOutListReq++;
        }

        /* Initialize other variables */
        instObj->openCnt = 0U;
        for (scalerId = 0U; scalerId < VPS_M2M_SCALER_ID_MAX; scalerId++)
        {
            /* VPE core is always present in all driver paths. Hence set it
             * here. */
            instObj->lazyLoadingEnable[scalerId] = (UInt32) FALSE;
            instObj->scalerCoreId[scalerId]      = VPSMDRV_VPE_VPE_CORE_IDX;

            /* Set the current scaling factor configuration values to invalid so
             * that the first call to process the frames will result in setting
             * coefficients to the scaler configuration of that frame (channel).
             */
            instObj->curScFactor[scalerId].hScalingSet = VPS_SC_SET_MAX;
            instObj->curScFactor[scalerId].vScalingSet = VPS_SC_SET_MAX;
        }
        instObj->initDone       = (UInt32) TRUE;
        instObj->numChAllocated = 0U;

        /* Move to next parameter */
        initPrms++;
    }

    /* Deinit if error occurs */
    if (FVID2_SOK != retVal)
    {
        vpsMdrvVpeDeInit();
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeDeInit
 *  Deallocates memory allocated by init function.
 *  Returns BSP_SOK on success else returns error value.
 */
Int32 vpsMdrvVpeDeInit(void)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt, coreCnt;
    VpsMdrv_VpeInstObj *instObj;

    for (instCnt = 0U; instCnt < VPS_M2M_VPE_INST_MAX; instCnt++)
    {
        instObj = &VpsMdrvVpeInstObjects[instCnt];
        if (TRUE == instObj->initDone)
        {
            /* Check if all the handles of the driver are closed */
            if (0U != instObj->openCnt)
            {
                GT_2trace(VpsMdrvVpeTrace, GT_ERR,
                          "%d handles of driver inst %d not closed!\r\n",
                          instObj->openCnt,
                          instCnt);
                retVal = FVID2_EDRIVER_INUSE;
                break;
            }

            /* Init variables to zero */
            instObj->drvInstId = 0U;
            for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
            {
                instObj->coreInstId[coreCnt] = 0U;
                instObj->coreOps[coreCnt]    = NULL;
                instObj->isCoreReq[coreCnt]  = (UInt32) FALSE;
            }

            /* Delete the instance semaphore */
            if (NULL != instObj->instSem)
            {
                BspOsal_semDelete(&instObj->instSem);
                instObj->instSem = NULL;
            }

            /* Reset the init flag */
            instObj->initDone = (UInt32) FALSE;
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeGetInstObj
 *  Returns the instance object pointer for the instance id.
 */
VpsMdrv_VpeInstObj *vpsMdrvVpeGetInstObj(UInt32 instId)
{
    UInt32 instCnt;
    VpsMdrv_VpeInstObj *instObj = NULL;

    /* Find out the instance to which this channel belongs to */
    for (instCnt = 0U; instCnt < VPS_M2M_VPE_INST_MAX; instCnt++)
    {
        if (VpsMdrvVpeInstObjects[instCnt].drvInstId == instId)
        {
            instObj = &VpsMdrvVpeInstObjects[instCnt];
            break;
        }
    }

    return (instObj);
}

/**
 *  vpsMdrvVpeAllocHandleObj
 *  Allocates handle object and all other memories of the handle like handle
 *  queues, descriptor/shadow overlay memories, channel objects etc.
 *  Returns the handle object pointer on success else returns NULL.
 */
VpsMdrv_VpeHandleObj *vpsMdrvVpeAllocHandleObj(
    const Vps_M2mCreateParams *createPrms,
    VpsMdrv_VpeInstObj        *instObj,
    const Fvid2_DrvCbParams   *fdmCbPrms)
{
    Int32  retVal = FVID2_SOK;
    UInt32 qCnt, chCnt, descSet;
    VpsMdrv_VpeQueueObj  *qObj;
    VpsMdrv_VpeHandleObj *hObj = NULL;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != createPrms));
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != fdmCbPrms));

    /* Allocate handle memory */
    hObj = (VpsMdrv_VpeHandleObj *) BspUtils_alloc(
        &gVpsMdrvVpePoolObj.handlePoolPrm,
        sizeof (VpsMdrv_VpeHandleObj),
        VpsMdrvVpeTrace);
    if (NULL == hObj)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                  "Handle object memory alloc failed!!\r\n");
        retVal = FVID2_EALLOC;
    }
    else
    {
        BspUtils_memcpy(
            &hObj->createPrms,
            createPrms,
            sizeof (hObj->createPrms));
        hObj->instObj = instObj;
        /* Reset some of the important fields used by free function so that
         * when error occurs, we won't free un-allocated pointers!! */
        hObj->createPrms.numCh = 0U;
        hObj->reqQ              = NULL;
        hObj->doneQ             = NULL;
        hObj->freeQ             = NULL;
        hObj->ctrlSem           = NULL;
        hObj->stopSyncSem       = NULL;
        hObj->isStopped         = (UInt32) FALSE;
        hObj->numPendReq        = 0U;
        hObj->numUnProcessedReq = 0U;
        for (chCnt = 0U; chCnt < VPS_M2M_MAX_CH_PER_HANDLE; chCnt++)
        {
            hObj->chObjs[chCnt] = NULL;
        }
        for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
        {
            /* Mark both descriptor set is free for use */
            hObj->isDescSetFree[descSet] = (UInt32) TRUE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Create the different queues - request, done and free queues */
        retVal = BspUtils_constructQ(&hObj->freeLlObj);
        GT_assert(VpsMdrvVpeTrace, (retVal == BSP_SOK));
        hObj->freeQ = &hObj->freeLlObj;

        retVal = BspUtils_constructQ(&hObj->reqLlObj);
        GT_assert(VpsMdrvVpeTrace, (retVal == BSP_SOK));
        hObj->reqQ = &hObj->reqLlObj;

        retVal = BspUtils_constructQ(&hObj->doneLlObj);
        GT_assert(VpsMdrvVpeTrace, (retVal == BSP_SOK));
        hObj->doneQ = &hObj->doneLlObj;
    }

    if (FVID2_SOK == retVal)
    {
        /* Create semaphore */
        hObj->ctrlSem = BspOsal_semCreate(0, (Bool) TRUE);
        if (NULL == hObj->ctrlSem)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Control semaphore create failed!!\r\n");
            retVal = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Create semaphore */
        hObj->stopSyncSem = BspOsal_semCreate(0, (Bool) TRUE);
        if (NULL == hObj->stopSyncSem)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Stop sync semaphore create failed!!\r\n");
            retVal = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == retVal)
    {
        if (hObj->createPrms.chInQueueLength > BSP_CFG_M2M_VPE_QUEUE_LEN_PER_CH)
        {
            GT_2trace(
                VpsMdrvVpeTrace, GT_ERR,
                "Cant create %d m2m vpe queue objects!!. Maximum supported m2m vpe queue objects are %d\r\n",
                hObj->createPrms.chInQueueLength, VPS_M2M_DEF_QUEUE_LEN_PER_CH);
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Allocate queue object memory and queue them to free queue */
        for (qCnt = 0U; qCnt < hObj->createPrms.chInQueueLength; qCnt++)
        {
            /* Allocate queue object memory */
            qObj = &hObj->m2mVpeQObj[qCnt];
            /* Initialize and queue the allocate queue object to free Q */
            qObj->hObj         = hObj;
            qObj->descSetInUse = VPSMDRV_VPE_INVALID_DESC_SET;
            BspUtils_queue(hObj->freeQ, &qObj->qElem, qObj);
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Allocate channel object */
        retVal = vpsMdrvVpeAllocChObjs(hObj, createPrms->numCh);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Channel object memory alloc failed!!\r\n");
        }
        else
        {
            /* Copy the handle parameters */
            hObj->createPrms.numCh = createPrms->numCh;

            /* Copy the callback params */
            BspUtils_memcpy(
                &hObj->fdmCbPrms,
                fdmCbPrms,
                sizeof (hObj->fdmCbPrms));
        }
    }

    /* Deallocate if error occurs */
    if (FVID2_SOK != retVal)
    {
        if (NULL != hObj)
        {
            vpsMdrvVpeFreeHandleObj(hObj);
            hObj = NULL;
        }
    }

    return (hObj);
}

/**
 *  vpsMdrvVpeFreeHandleObj
 *  Frees the handle object and all other memories of the handle like handle
 *  queues, descriptor/shadow overlay memories, channel objects etc.
 */
Int32 vpsMdrvVpeFreeHandleObj(VpsMdrv_VpeHandleObj *hObj)
{
    Int32 retVal = FVID2_SOK, tempRetVal;
    VpsMdrv_VpeQueueObj *qObj;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));

    /* Free channel objects */
    retVal = vpsMdrvVpeFreeChObjs(hObj, hObj->createPrms.numCh);
    hObj->createPrms.numCh = 0U;

    if (NULL != hObj->freeQ)
    {
        /* Free-up all the queued free queue objects */
        while (1U)
        {
            qObj = (VpsMdrv_VpeQueueObj *) BspUtils_dequeue(hObj->freeQ);
            if (NULL == qObj)
            {
                /* No more in queue */
                break;
            }

            /* Free queue object memory */
            qObj->hObj = NULL;
        }
    }

    if (NULL != hObj->reqQ)
    {
        /* Delete the request Q */
        BspUtils_destructQ(hObj->reqQ);
        hObj->reqQ = NULL;
    }

    if (NULL != hObj->doneQ)
    {
        /* Delete the done Q */
        BspUtils_destructQ(hObj->doneQ);
        hObj->doneQ = NULL;
    }

    if (NULL != hObj->freeQ)
    {
        /* Delete the free Q */
        BspUtils_destructQ(hObj->freeQ);
        hObj->freeQ = NULL;
    }

    if (NULL != hObj->ctrlSem)
    {
        /* Delete the control semaphore */
        BspOsal_semDelete(&hObj->ctrlSem);
        hObj->ctrlSem = NULL;
    }

    if (NULL != hObj->stopSyncSem)
    {
        /* Delete the stop sync semaphore */
        BspOsal_semDelete(&hObj->stopSyncSem);
        hObj->stopSyncSem = NULL;
    }

    /* Reset the variables */
    hObj->instObj = NULL;
    hObj->fdmCbPrms.fdmCbFxn    = NULL;
    hObj->fdmCbPrms.fdmData     = NULL;
    hObj->fdmCbPrms.fdmErrCbFxn = NULL;
    hObj->fdmCbPrms.handle      = NULL;
    hObj->fdmCbPrms.errList     = NULL;

    /* Free handle object memory */
    tempRetVal = BspUtils_free(
        &gVpsMdrvVpePoolObj.handlePoolPrm,
        hObj,
        VpsMdrvVpeTrace);
    GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == tempRetVal));

    return (retVal);
}

/**
 *  vpsMdrvVpeAllocCoreMem
 *  Allocates the required descriptor and overlay memories for the channel
 *  and for all the cores for this handle. It also slices the descriptors and
 *  overlay memory and init the core desc memory structure.
 *  It also allocates the context buffer required by VPE core.
 */
Int32 vpsMdrvVpeAllocCoreMem(VpsMdrv_VpeHandleObj *hObj,
                             VpsMdrv_VpeChObj     *chObj)
{
    Int32 retVal = FVID2_SOK;
    VpsMdrv_VpeInstObj *instObj;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    /* Allocate desc memory for the channel */
    retVal = vpsMdrvVpeAllocChDescMem(hObj, chObj);
    if (FVID2_SOK != retVal)
    {
        GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                  "Could not allocate descrioptor for channel: %d!\r\n",
                  chObj->chNum);
    }

    if (FVID2_SOK == retVal)
    {
        /* Split the allocated descriptors across cores */
        retVal = vpsMdrvVpeSplitChDescMem(hObj, chObj);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                      "Error slicing descrioptor for channel: %d!\r\n",
                      chObj->chNum);
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Figure out context memory for each channel */
        retVal = vpsMdrvVpeCalcChCtxMem(hObj, chObj);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                      "Could not allocate context buffers for channel: %d!\r\n",
                      chObj->chNum);
        }
    }

    /* Deallocate if error occurs */
    if (FVID2_SOK != retVal)
    {
        vpsMdrvVpeFreeCoreMem(hObj, chObj);
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeFreeCoreMem
 *  Frees the allocated descriptors and overlay memories for the channel
 *  and for all the cores for this handle.
 *  It also frees the context buffer allocated for VPE core.
 */
Int32 vpsMdrvVpeFreeCoreMem(const VpsMdrv_VpeHandleObj *hObj,
                            VpsMdrv_VpeChObj           *chObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 descSet, coreCnt, cnt, i;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

    /* Free channel descriptor memory */
    retVal = vpsMdrvVpeFreeChDescMem(chObj);
    GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == retVal));

    /* Free channel context buffer memory */
    retVal = vpsMdrvVpeFreeChCtxMem(chObj);
    GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == retVal));

    /* Reset the dependent pointers */
    for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
    {
        chObj->firstDesc[descSet] = NULL;
        for (i = 0U; i < VPSMDRV_VPE_MAX_RT_COEFF_CFG_DESC; i++)
        {
            chObj->coeffDesc[descSet][i] = NULL;
        }
        chObj->nshwCfgDesc[descSet] = NULL;
        chObj->shwCfgDesc[descSet]  = NULL;
        chObj->sochDesc[descSet]    = NULL;
        chObj->rldDesc[descSet]     = NULL;
        for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
        {
            for (cnt = 0U; cnt < VCORE_M2M_MAX_IN_DESC; cnt++)
            {
                chObj->coreDescMem[descSet][coreCnt].inDataDesc[cnt] = NULL;
            }
            for (cnt = 0U; cnt < VCORE_M2M_MAX_OUT_DESC; cnt++)
            {
                chObj->coreDescMem[descSet][coreCnt].outDataDesc[cnt] = NULL;
            }
            chObj->coreDescMem[descSet][coreCnt].shadowOvlyMem = NULL;
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeProgramDesc
 *  Program the core descriptors and overlay memories for a channel.
 */
Int32 vpsMdrvVpeProgramDesc(VpsMdrv_VpeHandleObj *hObj,
                            VpsMdrv_VpeChObj     *chObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 chCnt, descSet, coreCnt;
    UInt8 *tempPtr;
    VpsMdrv_VpeInstObj *instObj;
    const Vcore_M2mOps *coreOps;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
    {
        /* Program cores only if needed for that instance */
        if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
        {
            coreOps = instObj->coreOps[coreCnt];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->programDesc));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->programReg));

            for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
            {
                /* Program the core descriptors */
                retVal = coreOps->programDesc(
                    hObj->coreHandle[coreCnt],
                    chObj->chNum,
                    &chObj->coreDescMem[descSet][coreCnt]);
                if (FVID2_SOK != retVal)
                {
                    GT_3trace(
                        VpsMdrvVpeTrace, GT_ERR,
                        "Could not program desc set %d of channel "
                        "%d for core %d!\r\n", descSet, chObj->chNum,
                        coreCnt);
                }
                else
                {
                    /* Program the overlay memory */
                    retVal = coreOps->programReg(
                        hObj->coreHandle[coreCnt],
                        chObj->chNum,
                        &chObj->coreDescMem[descSet][coreCnt]);
                    if (FVID2_SOK != retVal)
                    {
                        GT_3trace(
                            VpsMdrvVpeTrace, GT_ERR,
                            "Could not program overlay set %d of channel "
                            "%d for core %d!\r\n",
                            descSet, chObj->chNum, coreCnt);
                    }
                }

                if (FVID2_SOK != retVal)
                {
                    break;
                }
            }

            /* Break if error occurs */
            if (FVID2_SOK != retVal)
            {
                break;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
        {
            /* Program frame start event of VPE core in overlay memory */
            coreOps = instObj->coreOps[VPSMDRV_VPE_VPE_CORE_IDX];
            GT_assert(VpsMdrvVpeTrace,
                ((UInt32) TRUE == instObj->isCoreReq[VPSMDRV_VPE_VPE_CORE_IDX]));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->setFsEvent));

            retVal =
                coreOps->setFsEvent(
                    hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
                    chObj->chNum,
                    VPSHAL_VPDMA_FSEVENT_CHANNEL_ACTIVE,
                    &chObj->coreDescMem[descSet][VPSMDRV_VPE_VPE_CORE_IDX]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Could not set frame start for VPE Core!\r\n");
                break;
            }

            /* Program non-shadow config descriptor. Point to the first
             * cores overlay memory */
            GT_assert(VpsMdrvVpeTrace, (NULL != chObj->nshwCfgDesc[descSet]));
            GT_assert(VpsMdrvVpeTrace, (NULL !=
                                        chObj->coreDescMem[descSet][0U].
                                        nonShadowOvlyMem));
            GT_assert(VpsMdrvVpeTrace, (0U != chObj->totalNshwOvlyMem));
            VpsHal_vpdmaCreateConfigDesc(
                chObj->nshwCfgDesc[descSet],
                VPSHAL_VPDMA_CONFIG_DEST_MMR,
                VPSHAL_VPDMA_CPT_ADDR_DATA_SET,
                VPSHAL_VPDMA_CCT_INDIRECT,
                (chObj->totalNshwOvlyMem / VPSMDRV_VPE_MAX_DESC_SET),
                chObj->coreDescMem[descSet][0U].nonShadowOvlyMem,
                NULL,
                0);

            /* Program non-shadow config descriptor. Point to the first
             * cores overlay memory */
            GT_assert(VpsMdrvVpeTrace, (NULL != chObj->shwCfgDesc[descSet]));
            GT_assert(VpsMdrvVpeTrace, (NULL !=
                                        chObj->coreDescMem[descSet][0U].
                                        shadowOvlyMem));
            GT_assert(VpsMdrvVpeTrace, (0U != chObj->totalShwOvlyMem));
            VpsHal_vpdmaCreateConfigDesc(
                chObj->shwCfgDesc[descSet],
                VPSHAL_VPDMA_CONFIG_DEST_MMR,
                VPSHAL_VPDMA_CPT_ADDR_DATA_SET,
                VPSHAL_VPDMA_CCT_INDIRECT,
                (chObj->totalShwOvlyMem / VPSMDRV_VPE_MAX_DESC_SET),
                chObj->coreDescMem[descSet][0U].shadowOvlyMem,
                NULL,
                0);

            /* Program the SOCH descriptors */
            tempPtr = (UInt8 *) chObj->sochDesc[descSet];
            for (chCnt = 0U; chCnt < chObj->numVpdmaChannels; chCnt++)
            {
                VpsHal_vpdmaCreateSOCHCtrlDesc(
                    tempPtr,
                    chObj->socChNum[chCnt]);
                tempPtr += VPSHAL_VPDMA_CTRL_DESC_SIZE;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Mark the dirty flags as clean */
        for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
        {
            chObj->isDescDirty[descSet] = (UInt32) FALSE;
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeAllocCoeffDesc
 */
void *vpsMdrvVpeAllocCoeffDesc(void)
{
    void *coeffDesc;

    /* Allocate coeff descriptor memory */
    coeffDesc = gVpsMdrvVpeCoeffDescMem;

    return (coeffDesc);
}

/**
 *  vpsMdrvVpeFreeCoeffDesc
 */
Int32 vpsMdrvVpeFreeCoeffDesc(void *coeffDesc)
{
    return (FVID2_SOK);
}

/**
 *  vpsMdrvVpeCopyVpePrms
 *  Copies the VPE parameters to channel object.
 */
Int32 vpsMdrvVpeCopyVpePrms(VpsMdrv_VpeChObj       *chObj,
                            const Vps_M2mVpeParams *vpePrms)
{
    Int32 retVal = FVID2_SOK;
    VpsMdrv_SubFrameChInst *slcObjPtr;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != vpePrms));

    BspUtils_memcpy(
        &chObj->vpePrms,
        vpePrms,
        sizeof (chObj->vpePrms));
    /* Use driver memory for advance config pointer */
    if (NULL != vpePrms->scCfg.advCfg)
    {
        chObj->vpePrms.scCfg.advCfg = &chObj->scAdvCfg;
        BspUtils_memcpy(
            chObj->vpePrms.scCfg.advCfg,
            vpePrms->scCfg.advCfg,
            sizeof (Vps_ScAdvConfig));
    }

    /* Copy SubFrame procesing config parameters and initialize subframe
     * Instance of the channel */
    slcObjPtr = &chObj->slcChObj;

    /* Update sliceInstance in chObj required for scPh and offset
     * calculation*/
    slcObjPtr->subFrameEnable = vpePrms->subFramePrms.subFrameEnable;
    slcObjPtr->srcFrmH        = vpePrms->inFmt.height;
    slcObjPtr->dataFmt        = vpePrms->inFmt.dataFormat;
    slcObjPtr->tarFrmH        = vpePrms->outFmt.height;
    slcObjPtr->srcFrmW        = vpePrms->inFmt.width;
    slcObjPtr->tarFrmW        = vpePrms->outFmt.width;
    slcObjPtr->filtType       = VPS_SC_VST_POLYPHASE;
    if (TRUE == vpePrms->subFramePrms.subFrameEnable)
    {
        /* Check if sliceSize divides frame into Integer number of
         * subframes */
        slcObjPtr->slcSz = vpePrms->subFramePrms.numLinesPerSubFrame;
        if (0U == (slcObjPtr->srcFrmH % slcObjPtr->slcSz))
        {
            slcObjPtr->noOfSlcs = (slcObjPtr->srcFrmH / slcObjPtr->slcSz);
        }
        else
        {
            GT_0trace(
                VpsMdrvVpeTrace, GT_ERR,
                "EBADARGS: NoOfSubFrames not integer, adjust sliceSize \r\n");
            retVal = FVID2_EBADARGS;
        }
    }
    else
    {
        slcObjPtr->slcSz    = vpePrms->inFmt.height;
        slcObjPtr->noOfSlcs = (slcObjPtr->srcFrmH / slcObjPtr->slcSz);
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeAllocChDescMem
 *  Allocate the required descriptors and overlay memories for the channel
 *  according to the requirement of all the cores.
 */
static Int32 vpsMdrvVpeAllocChDescMem(VpsMdrv_VpeHandleObj *hObj,
                                      VpsMdrv_VpeChObj     *chObj)
{
    Int32  retVal = FVID2_SOK, tempRetVal;
    UInt32 coreCnt;
    UInt32 scalerId;
    Vcore_M2mDescInfo descInfo;
    const Vcore_M2mOps *coreOps;
    VpsMdrv_VpeInstObj *instObj;
    UInt32 totalDescMem, totalCoeffDescMem;
    UInt32 totalNshwOvlyMem, totalShwOvlyMem;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    /* Reset variables */
    totalDescMem      = 0U;
    totalCoeffDescMem = 0U;
    totalNshwOvlyMem  = 0U;
    totalShwOvlyMem   = 0U;
    GT_assert(VpsMdrvVpeTrace, (NULL == chObj->descMem));
    GT_assert(VpsMdrvVpeTrace, (NULL == chObj->nshwOvlyMem));
    GT_assert(VpsMdrvVpeTrace, (NULL == chObj->shwOvlyMem));

    for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
    {
        if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
        {
            coreOps = instObj->coreOps[coreCnt];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->getDescInfo));

            /* Get the descriptor info for each core */
            retVal = coreOps->getDescInfo(
                hObj->coreHandle[coreCnt],
                chObj->chNum,
                &descInfo);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                          "Could not get core info for core %d!\r\n", coreCnt);
                break;
            }

            /* Accumulate the info in total info variable */
            totalDescMem +=
                (descInfo.numInDataDesc * VPSHAL_VPDMA_DATA_DESC_SIZE);
            totalDescMem +=
                (descInfo.numOutDataDesc * VPSHAL_VPDMA_DATA_DESC_SIZE);
            totalNshwOvlyMem += descInfo.nonShadowOvlySize;
            totalShwOvlyMem  += descInfo.shadowOvlySize;
            /* Get the coefficient information */
            chObj->coeffConfigDest[coreCnt] =
                descInfo.coeffConfigDest;
            chObj->horzCoeffOvlySize[coreCnt] =
                descInfo.horzCoeffOvlySize;
            chObj->vertCoeffOvlySize[coreCnt] =
                descInfo.vertCoeffOvlySize;
            chObj->vertBilinearCoeffOvlySize[coreCnt] =
                descInfo.vertBilinearCoeffOvlySize;
        }
    }

    if (FVID2_SOK == retVal)
    {
        totalDescMem +=
            (VPSMDRV_VPE_MAX_SHW_CFG_DESC * VPSHAL_VPDMA_CONFIG_DESC_SIZE);
        totalDescMem +=
            (VPSMDRV_VPE_MAX_NSHW_CFG_DESC * VPSHAL_VPDMA_CONFIG_DESC_SIZE);

        /* There are VPSMDRV_VPE_RT_COEFF_CFG_DESC_PER_SC coeff
         * descriptors needed for each core in the path that has a scaler.
         */
        chObj->numCoeffDesc = 0U;
        for (scalerId = 0U; scalerId < VPS_M2M_SCALER_ID_MAX; scalerId++)
        {
            if (VPSMDRV_VPE_MAX_CORE != instObj->scalerCoreId[scalerId])
            {
                if ((UInt32) TRUE == instObj->lazyLoadingEnable[scalerId])
                {
                    chObj->numCoeffDesc += VPSMDRV_VPE_RT_COEFF_CFG_DESC_PER_SC;
                    totalCoeffDescMem   +=
                        (VPSMDRV_VPE_RT_COEFF_CFG_DESC_PER_SC *
                         VPSHAL_VPDMA_CONFIG_DESC_SIZE);
                }
            }
        }
        totalDescMem += totalCoeffDescMem;

        /* Allocate for SOCH control descriptors.
         * Use all channels returned by the cores as SOCH */
        totalDescMem += (chObj->numVpdmaChannels * VPSHAL_VPDMA_CTRL_DESC_SIZE);

        /* Allocate for reload descriptor in main descriptor memory */
        totalDescMem += (VPSMDRV_VPE_MAX_RLD_DESC * VPSHAL_VPDMA_CTRL_DESC_SIZE);

        /* Allocate descriptor and overlay memory per channel for all
         * the sets. */
        totalDescMem      *= VPSMDRV_VPE_MAX_DESC_SET;
        totalCoeffDescMem *= VPSMDRV_VPE_MAX_DESC_SET;
        totalNshwOvlyMem  *= VPSMDRV_VPE_MAX_DESC_SET;
        totalShwOvlyMem   *= VPSMDRV_VPE_MAX_DESC_SET;

        /* Allocate memory */
        chObj->descMem =
            BspUtils_alloc(&gVpsMdrvVpePoolObj.totalDescMemPoolPrm,
                           totalDescMem,
                           VpsMdrvVpeTrace);
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj->descMem));
        chObj->totalDescMem = totalDescMem;

        chObj->nshwOvlyMem = BspUtils_alloc(
            &gVpsMdrvVpePoolObj.nshwOvlyDescMemPoolPrm, totalNshwOvlyMem,
            VpsMdrvVpeTrace);
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj->nshwOvlyMem));
        chObj->totalNshwOvlyMem = totalNshwOvlyMem;

        chObj->shwOvlyMem = BspUtils_alloc(
            &gVpsMdrvVpePoolObj.shwOvlyDescMemPoolPrm, totalShwOvlyMem,
            VpsMdrvVpeTrace);
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj->shwOvlyMem));
        chObj->totalShwOvlyMem = totalShwOvlyMem;
    }

    /* Deallocate if error occurs */
    if (FVID2_SOK != retVal)
    {
        tempRetVal = vpsMdrvVpeFreeChDescMem(chObj);
        GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == tempRetVal));
    }
    else
    {
        chObj->totalCoeffDescMem = totalCoeffDescMem;
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeFreeChDescMem
 *  Frees the allocated descriptors and overlay memories for the channel.
 */
static Int32 vpsMdrvVpeFreeChDescMem(
    VpsMdrv_VpeChObj *chObj)
{
    Int32 retVal = FVID2_SOK;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

    if (NULL != chObj->descMem)
    {
        retVal += BspUtils_free(
            &gVpsMdrvVpePoolObj.totalDescMemPoolPrm, chObj->descMem,
            VpsMdrvVpeTrace);
        chObj->descMem      = NULL;
        chObj->totalDescMem = 0U;
    }

    if (NULL != chObj->nshwOvlyMem)
    {
        retVal +=
            BspUtils_free(&gVpsMdrvVpePoolObj.nshwOvlyDescMemPoolPrm,
                          chObj->nshwOvlyMem,
                          VpsMdrvVpeTrace);
        chObj->nshwOvlyMem      = NULL;
        chObj->totalNshwOvlyMem = 0U;
    }

    if (NULL != chObj->shwOvlyMem)
    {
        retVal +=
            BspUtils_free(&gVpsMdrvVpePoolObj.shwOvlyDescMemPoolPrm,
                          chObj->shwOvlyMem,
                          VpsMdrvVpeTrace);
        chObj->shwOvlyMem      = NULL;
        chObj->totalShwOvlyMem = 0U;
    }

    chObj->totalCoeffDescMem = 0U;

    return (retVal);
}

/**
 *  vpsMdrvVpeCalcChCtxMem
 *  Calculate the required DEI context buffers for the channel according to the
 *  requirement of VPE core.
 */
static Int32 vpsMdrvVpeCalcChCtxMem(const VpsMdrv_VpeHandleObj *hObj,
                                    VpsMdrv_VpeChObj           *chObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 fldCnt, ptrCnt, mvCnt;
    VpsMdrv_VpeInstObj     *instObj;
    UInt32 width, height, lineStride;
    Vcore_M2mDeiCtxInfo    *vpeCoreCtxInfo;
    Vcore_VpeUpdateContext *vpeCoreCtxBuf;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    vpeCoreCtxInfo = &chObj->vpeCoreCtxInfo;
    vpeCoreCtxBuf  = &chObj->vpeCoreCtxBuf;

    width  = chObj->vpePrms.inFmt.width;
    height = chObj->vpePrms.inFmt.height;

    if (FVID2_SF_PROGRESSIVE == chObj->vpePrms.inFmt.scanFormat)
    {
        /* For the progressive mode, height from the format is
         * frame height, so for the previous fields, it should
         * be field size. */
        height = height / 2U;
    }

    /* Reset variables */
    for (fldCnt = 0U; fldCnt < VCORE_VPE_MAX_PREV_FLD; fldCnt++)
    {
        for (ptrCnt = 0U; ptrCnt < VCORE_VPE_NUM_DESC_PER_FIELD; ptrCnt++)
        {
            GT_assert(VpsMdrvVpeTrace,
                      (NULL == vpeCoreCtxBuf->prevInBuf[fldCnt][ptrCnt]));
            vpeCoreCtxBuf->prevInBuf[fldCnt][ptrCnt] = NULL;
        }
    }
    for (fldCnt = 0U; fldCnt < VCORE_VPE_MAX_OUT_FLD; fldCnt++)
    {
        for (ptrCnt = 0U; ptrCnt < VCORE_VPE_NUM_DESC_PER_FIELD; ptrCnt++)
        {
            GT_assert(VpsMdrvVpeTrace,
                      (NULL == vpeCoreCtxBuf->curOutBuf[fldCnt][ptrCnt]));
            vpeCoreCtxBuf->curOutBuf[fldCnt][ptrCnt] = NULL;
        }
    }
    for (mvCnt = 0U; mvCnt < VCORE_VPE_MAX_MV_IN; mvCnt++)
    {
        GT_assert(VpsMdrvVpeTrace, (NULL == vpeCoreCtxBuf->mvInBuf[mvCnt]));
        vpeCoreCtxBuf->mvInBuf[mvCnt] = NULL;
    }
    GT_assert(VpsMdrvVpeTrace, (NULL == vpeCoreCtxBuf->mvOutBuf));
    vpeCoreCtxBuf->mvOutBuf = NULL;

    for (mvCnt = 0U; mvCnt < (VCORE_VPE_MAX_MVSTM_IN + 1U); mvCnt++)
    {
        GT_assert(VpsMdrvVpeTrace, (NULL == vpeCoreCtxBuf->mvstmInBuf[mvCnt]));
        vpeCoreCtxBuf->mvstmInBuf[mvCnt] = NULL;
    }
    GT_assert(VpsMdrvVpeTrace, (NULL == vpeCoreCtxBuf->mvstmOutBuf));
    vpeCoreCtxBuf->mvstmOutBuf = NULL;

    chObj->isDeiCtxBufSet = (UInt32) FALSE;
    if (FVID2_SF_PROGRESSIVE == chObj->vpePrms.inFmt.scanFormat)
    {
        /* For the progressive mode, fld index should start from 0 */
        chObj->fldIdx = 0U;
    }
    else
    {
        chObj->fldIdx = 1U;
    }
    chObj->mvIdx            = 1U;
    chObj->mvstmIdx         = 1U;
    chObj->prevFldState     = 0U;
    chObj->dontRotateCtxBuf = (UInt32) FALSE;

    /* Fill the number of context buffer information */
    chObj->deiCtxInfo.chNum  = chObj->chNum;
    chObj->deiCtxInfo.numFld =
        vpeCoreCtxInfo->numPrevFld + vpeCoreCtxInfo->numCurFldOut;
    chObj->deiCtxInfo.numMv =
        vpeCoreCtxInfo->numMvIn + vpeCoreCtxInfo->numMvOut;
    chObj->deiCtxInfo.numMvstm =
        vpeCoreCtxInfo->numMvstmIn + vpeCoreCtxInfo->numMvstmOut;

    /*
     * Fill the context buffer size. Align to VPDMA line stride
     * requirement.
     */
    /* Field buffers are Y and CbCr separate (NV16 format).
     * Hence line stride equal to width. */
    lineStride = width;
    lineStride = VpsUtils_align(lineStride, VPSHAL_VPDMA_LINE_STRIDE_ALIGN);
    /* Allocate for both Y and C - multiply by 2. */
    chObj->deiCtxInfo.fldBufSize = (lineStride * height * 2U);

    /* MV and MVSTM are 4-bits per pixel. Hence line stride equal to
     * width by 2 */
    lineStride = width / 2U;
    lineStride = VpsUtils_align(lineStride, VPSHAL_VPDMA_LINE_STRIDE_ALIGN);
    chObj->deiCtxInfo.mvBufSize    = (lineStride * height);
    chObj->deiCtxInfo.mvstmBufSize = (lineStride * height);

    return (retVal);
}

/**
 *  vpsMdrvVpeFreeChCtxMem
 *  Frees the allocated DEI context buffers of the channel.
 */
static Int32 vpsMdrvVpeFreeChCtxMem(VpsMdrv_VpeChObj *chObj)
{
    Int32 retVal = FVID2_SOK;

    /* TODO: In case if we decide to allocate context buffer in driver,
     * free them here */

    return (retVal);
}

/**
 *  vpsMdrvVpeSplitChDescMem
 *  Splits the allocated descriptor and shadow overlay memories of a channel
 *  according to the requirement of each core.
 */
static Int32 vpsMdrvVpeSplitChDescMem(VpsMdrv_VpeHandleObj *hObj,
                                      VpsMdrv_VpeChObj     *chObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 descSet, coreCnt, cnt, i;
    Vcore_M2mDescInfo   descInfo[VPSMDRV_VPE_MAX_CORE];
    const Vcore_M2mOps *coreOps;
    VpsMdrv_VpeInstObj *instObj;
    UInt8              *descPtr;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj->descMem));

    /* Get the descriptor info of all cores only once */
    for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
    {
        if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
        {
            coreOps = instObj->coreOps[coreCnt];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->getDescInfo));

            /* Get the descriptor info of each core */
            retVal = coreOps->getDescInfo(
                hObj->coreHandle[coreCnt],
                chObj->chNum,
                &descInfo[coreCnt]);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                          "Could not get core info for core %d!\r\n", coreCnt);
                break;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Assign main data descriptor memory pointers */
        descPtr = (UInt8 *) chObj->descMem;
        GT_assert(VpsMdrvVpeTrace, (NULL != descPtr));
        for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
        {
            for (i = 0U; i < chObj->numCoeffDesc; i++)
            {
                chObj->coeffDesc[descSet][i] = descPtr;
                /* Create a dummy descriptor to initialize. */
                VpsHal_vpdmaCreateDummyDesc(descPtr);
                descPtr += VPSHAL_VPDMA_CONFIG_DESC_SIZE;
                if (VPS_M2M_VPE_SCALER_ID_SC0 == i)
                {
                    /* TODO: slcChObj should be one for each scaler Id.
                     * Currently assuming VPE SC only. */
                    chObj->slcChObj.filtType =
                        chObj->scFactor[VPS_M2M_VPE_SCALER_ID_SC0].vsType;
                }
            }

            /* Assign shadow and non-shadow config descriptors if needed */
            chObj->nshwCfgDesc[descSet] = descPtr;
            descPtr += (VPSMDRV_VPE_MAX_NSHW_CFG_DESC *
                        VPSHAL_VPDMA_CONFIG_DESC_SIZE);

            chObj->shwCfgDesc[descSet] = descPtr;
            descPtr += (VPSMDRV_VPE_MAX_SHW_CFG_DESC *
                        VPSHAL_VPDMA_CONFIG_DESC_SIZE);

            /* Set the first descriptor in the layout to the appropriate
             * descriptor depending on the configuration. This value is
             * used for configuring the reload descriptor at runtime.
             */
            if (chObj->numCoeffDesc > 0U)
            {
                /* Lazy loading is enabled */
                chObj->firstDesc[descSet] = chObj->coeffDesc[descSet][0U];
            }
            else
            {
                /* Lazy loading is disabled */
                chObj->firstDesc[descSet] = chObj->nshwCfgDesc[descSet];
            }

            /*
             * Split the main descriptor and overlay memory for each core.
             */
            /* First assign out data descriptor for all cores */
            for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
            {
                if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
                {
                    for (cnt = 0U;
                         cnt < descInfo[coreCnt].numOutDataDesc;
                         cnt++)
                    {
                        chObj->coreDescMem[descSet][coreCnt].outDataDesc[cnt]
                                 = descPtr;
                        descPtr += VPSHAL_VPDMA_DATA_DESC_SIZE;
                    }
                }
            }

            /* Then assign in data descriptor for all cores */
            for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
            {
                if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
                {
                    for (cnt = 0U;
                         cnt < descInfo[coreCnt].numInDataDesc;
                         cnt++)
                    {
                        chObj->coreDescMem[descSet][coreCnt].inDataDesc[cnt]
                                 = descPtr;
                        descPtr += VPSHAL_VPDMA_DATA_DESC_SIZE;
                    }
                }
            }

            /* Assign SOCH descriptor */
            chObj->sochDesc[descSet] = descPtr;
            /* Use all channels returned by the cores as SOCH */
            descPtr += (chObj->numVpdmaChannels * VPSHAL_VPDMA_CTRL_DESC_SIZE);

            /* Assign reload descriptor */
            chObj->rldDesc[descSet] = descPtr;
            descPtr += VPSHAL_VPDMA_CTRL_DESC_SIZE;
        }

        /* Assign non-shadow overlay memory pointers */
        descPtr = (UInt8 *) chObj->nshwOvlyMem;
        GT_assert(VpsMdrvVpeTrace, (NULL != descPtr));
        for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
        {
            for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
            {
                if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
                {
                    if (descInfo[coreCnt].nonShadowOvlySize > 0U)
                    {
                        chObj->coreDescMem[descSet][coreCnt].nonShadowOvlyMem
                                 = descPtr;
                        descPtr += descInfo[coreCnt].nonShadowOvlySize;
                    }
                    else
                    {
                        chObj->coreDescMem[descSet][coreCnt].nonShadowOvlyMem
                            = NULL;
                    }
                }
            }
        }

        /* Assign shadow overlay memory pointers */
        descPtr = (UInt8 *) chObj->shwOvlyMem;
        GT_assert(VpsMdrvVpeTrace, (NULL != descPtr));
        for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
        {
            for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
            {
                if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
                {
                    if (descInfo[coreCnt].shadowOvlySize > 0U)
                    {
                        chObj->coreDescMem[descSet][coreCnt].shadowOvlyMem
                                 = descPtr;
                        descPtr += descInfo[coreCnt].shadowOvlySize;
                    }
                    else
                    {
                        chObj->coreDescMem[descSet][coreCnt].shadowOvlyMem
                            = NULL;
                    }
                }
            }
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeAllocChObjs
 *  Allocate channel objects for the handle.
 */
static Int32 vpsMdrvVpeAllocChObjs(VpsMdrv_VpeHandleObj *hObj, UInt32 numCh)
{
    Int32  retVal = FVID2_SOK, tempRetVal;
    UInt32 chCnt, errCnt, ctxIndex;
    VpsMdrv_VpeChObj   *chObj;
    VpsMdrv_VpeInstObj *instObj;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    /* Check for out of bound */
    GT_assert(VpsMdrvVpeTrace, (numCh <= VPS_M2M_MAX_CH_PER_HANDLE));

    /* Allocate channel objects */
    for (chCnt = 0U; chCnt < numCh; chCnt++)
    {
        chObj = (VpsMdrv_VpeChObj *) BspUtils_alloc(
            &gVpsMdrvVpePoolObj.chPoolPrm,
            sizeof (VpsMdrv_VpeChObj),
            VpsMdrvVpeTrace);
        if (NULL == chObj)
        {
            GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                      "Channel memory alloc failed: %d!!\r\n", chCnt);
            retVal = FVID2_EALLOC;
        }

        if (FVID2_SOK == retVal)
        {
            hObj->chObjs[chCnt] = chObj;
            chObj->chNum        = chCnt;
            VpsM2mVpeParams_init(&chObj->vpePrms);
            chObj->vpePrms.chNum    = chCnt;
            chObj->isParamSet       = (UInt32) FALSE;
            chObj->numVpdmaChannels = 0U;
            chObj->descMem          = NULL;
            chObj->nshwOvlyMem      = NULL;
            chObj->shwOvlyMem       = NULL;

            /* Initialize field context buffer, Will be updated
             *  1. Set to the first field - for the very first field
             *  2. When user gives new field for de-interlacing - current field
             *     moved to fieldCtxBufs[0] and contents of fieldCtxBufs[0] to
             *     fieldCtxBufs[1] and contenct of fieldCtxBufs[1] to
             *     fieldCtxBufs[2] and until VPSMDRV_VPE_MAX_FIELD_CONTEXT - 1
             **/
            for (ctxIndex = 0U;
                 ctxIndex <= VPSMDRV_VPE_MAX_FIELD_CONTEXT;
                 ctxIndex++)
            {
                chObj->ctxFieldFifo[ctxIndex].fieldCtxBuf = NULL;
                chObj->ctxFieldFifo[ctxIndex].tth         = 0U;
            }
            chObj->isCtxFieldInit = (UInt32) FALSE;

            /* Check for hObj->createPrms.chInQueueLength to be less than
             * VPS_M2M_DEF_QUEUE_LEN_PER_CH is already done. */
            chObj->space4AgedCtxFieldQ = &chObj->AgedCtxFieldQ[0];
        }

        if (FVID2_SOK == retVal)
        {
            retVal = BspUtils_queCreate(
                &(chObj->agedCtxFieldQ),
                (UInt32) (hObj->createPrms.chInQueueLength + 1U),
                chObj->space4AgedCtxFieldQ,
                BSPUTILS_QUE_FLAG_NO_BLOCK_QUE);
            if (retVal != FVID2_SOK)
            {
                GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                          "Channel memory alloc - alloc of agedQ fails %d!!\r\n",
                          chCnt);
            }
        }

        if (retVal != FVID2_SOK)
        {
            break;
        }
    }

    if (FVID2_SOK != retVal)
    {
        /* Free-up the already allocated channel memories */
        for (errCnt = 0U; errCnt < chCnt; errCnt++)
        {
            hObj->chObjs[errCnt]->chNum = 0U;
            tempRetVal = BspUtils_free(
                &gVpsMdrvVpePoolObj.chPoolPrm,
                hObj->chObjs[errCnt],
                VpsMdrvVpeTrace);
            GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == tempRetVal));
            hObj->chObjs[errCnt] = NULL;
        }
    }
    else
    {
        instObj->numChAllocated += numCh;
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeFreeChObjs
 *  Frees the channel and scratch pad objects of the handle.
 */
static Int32 vpsMdrvVpeFreeChObjs(VpsMdrv_VpeHandleObj *hObj, UInt32 numCh)
{
    Int32  retVal = FVID2_SOK, tempRetVal;
    UInt32 chCnt;
    VpsMdrv_VpeChObj *chObj;
    VpsMdrv_VpeInstObj *instObj;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    /* Check for out of bound */
    GT_assert(VpsMdrvVpeTrace, (numCh <= VPS_M2M_MAX_CH_PER_HANDLE));

    for (chCnt = 0U; chCnt < numCh; chCnt++)
    {
        chObj = hObj->chObjs[chCnt];
        if (NULL != chObj)
        {
            chObj->chNum = 0U;
            tempRetVal   = BspUtils_free(
                &gVpsMdrvVpePoolObj.chPoolPrm,
                chObj,
                VpsMdrvVpeTrace);
            GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == tempRetVal));
            hObj->chObjs[chCnt] = NULL;
        }
    }

    GT_assert(VpsMdrvVpeTrace, (instObj->numChAllocated >= numCh));
    instObj->numChAllocated -= numCh;

    return (retVal);
}

