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
 * \file vps_mlm.c
 *
 * \brief Mem2Mem List Manager
 * This file implements List Manager for the Memory to Memory driver.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>
#include <ti/drv/vps/src/vpslib/common/vps_resrcMgr.h>
#include <ti/drv/vps/src/vpslib/common/vps_evtMgr.h>
#include <vpedrv/vps_mlm.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Number of Memory2Memory driver List Manager Instances. Current MLM
 *  implementation supports 6 mem2mem drivers so this is fixed to 6.
 *  Note: This macro can be changed as and when requirement changes.
 */
#define MLM_NUM_INSTANCES               ((UInt32) 6U)

/**
 *  \brief This enum defines maximum number of handles an mlm instance can
 *  support. This enum is mainly used in allocating control descriptor memory.
 *  Instead of using a single free pool of free control descriptors, MLM
 *  reserves set of free control descriptors per instance. This is because
 *  all the required set of control descriptors are created when client calls
 *  register API, so that it is not required to create these descriptors when
 *  mlm_submit API is called. Also, mem2mem driver is never going to enqueue
 *  more than these number of requests. This needs to be changed when number
 *  handles supported by the mem2mem driver is changed.
 */
#define MLM_NUM_REQ_PER_INST            ((UInt32) 10U)

/**
 * \brief Defined maximum number of Send Interrupt control descriptor.
 */
#define MLM_NUM_SI_CTRL_DESC            ((UInt32) 1U)

/**
 * \brief Defined maximum number of Reload Control descriptor in the MLM's
 *  descriptor memory.
 */
#define MLM_NUM_RL_CTRL_DESC            ((UInt32) 1U)

#define MLM_SOC_EVENT                   ((UInt32) VPSHAL_VPDMA_SOC_NOTACTIVE)
#define MLM_SOC_LINE_COUNT              ((UInt32) 0U)
#define MLM_SOC_PIXEL_COUNT             ((UInt32) 0U)

/**
 *  \brief VEM client priority for the Send interrupt and list
 *  complete interrupt
 */
#define MLM_VEM_SI_PRIORITY             (VEM_PRIORITY0)
#define MLM_VEM_LC_PRIORITY             (VEM_PRIORITY1)

/**
 *  \brief MLM keeps a list of control descriptos, which it attaches at
 *  the end of every request. This macro is used for defining size of these
 *  set of control descriptors.
 */
#define MLM_CTRL_DESC_MEMORY         (UInt32) (                \
        (MLM_NUM_SI_CTRL_DESC * VPSHAL_VPDMA_CTRL_DESC_SIZE) + \
        (MLM_MAX_CHANNELS * VPSHAL_VPDMA_CTRL_DESC_SIZE) +     \
        (MLM_NUM_RL_CTRL_DESC * VPSHAL_VPDMA_CTRL_DESC_SIZE))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Mlm_InstInfo
 * \brief Structure containing information regarding each instances of mlm.
 */
typedef struct Mlm_InstInfo_t
{
    UInt32               instNum;
    /**< MLM Instance Number. Each instance of the MLM is given an instance
     *   number. */
    UInt32               listNum;
    /**< VPDMA List Number. Each MLM instance requires a dedicated list.
     *   It uses this list to submit the request memory to memory driver
     *   request for the operations to the VPDMA.*/
    UInt32               isListAllocated;
    /**< Flag to indicate whether the list is allocated or not for this mlm
     *   instance. */
    UInt32               siEventNum[MLM_NUM_SI_CTRL_DESC];
    /**< VPDMA Send Interrupt number. Mlm uses send interrupt control
     *   descriptor to give request completion callback to the clients. */
    UInt32               numSiSrc;
    /**< Number of send interrupt sources to be used for this instance of
     *   the mlm */
    Mlm_ClientInfo       clientInfo;
    /**< Client Information Structure */
    UInt8               *descPtr;
    /**< Pointer to the start of the instance descriptors */
    UInt32               ctrlDescSize;
    /**< This keeps track of ctrl descriptor size. Depending on the
     *   linking Si and reload descriptor is available or not and
     *   number of sync on channel control descriptors, size
     *   of the descriptors will change */
    UInt32               isRegistered;
    /**< Indicates whethe client is registered or not. It is also used to
     *   indicate the free MLM instance, so if the client is not registered
     *   to an instance, that instance is free and client can register to
     *   this MLM instance. */
    BspUtilsLinkListObj *freeCtrlDesc;
    /**< Queue of free control descriptor memory. MLM keeps a pool of
     *   memory for control descriptors. This queue is a list of free
     *   control descriptor pool. */
    BspUtilsLinkListObj *requestQueue;
    /**< Queue of allocated control descriptor memory. MLM keeps a pool of
     *   memory for control descriptors. This queue is a list of allocated
     *   control descriptor pool. */
    BspUtilsLinkListObj *activeQueue;
    /**< Queue of requests, which are submitted for the processing to
     *   the VPDMA */
    BspUtilsLinkListObj  freeCtrlDescObj;
    /**< Linked List object for freeCtrlDesc. */
    BspUtilsLinkListObj  requestQueueObj;
    /**< Linked List object for requestQueue. */
    BspUtilsLinkListObj  activeQueueObj;
    /**< Linked List object for activeQueue. */
    UInt32               isListActive;
    /**< Indicates whether list is active or not. Flag to indicate
     *   whether the given list is submitted to the VPDMA
     *   or not. This is mainly used when there are no request in the
     *   queue and client calls submit function. Since this flag will be set
     *   in this case, list can be directly submitted to the VPDMA. */
    void                *vemSendIntrHandle;
    /**< Vem Handle for the Send Interrupt event handler */
    void                *vemListCmplHandle;
    /**< Vem Handle for the List Complete event handler */
    void                *vemFmdHandle;
    /**< Vem Handle for the FMD event handler */
} Mlm_InstInfo;

/**
 *  \brief Structure defining the queue object used in queue/dequeue operation.
 */
typedef struct Mlm_QueueObj_t
{
    BspUtils_Node      qElem;
    /**< VPS utils queue element used in node addition. */
    UInt8             *descPtr;
    /**< Pointer to the start of the complete control descriptors */
    Ptr                ctrlDescPtr;
    /**< Pointer to the memory where control descriptors for this
     *   queue elements will be stored */
    Ptr                siDescPtr;
    /**< Points the memory location where Send Interrupt descriptor
     *   is to be created */
    Ptr                rlDescPtr;
    /**< Points the memory location where reload descriptor is to be created */
    UInt32             ctrlDescSize;
    /**< Keeps track of the size of the control descriptors */
    Mlm_SubmitReqInfo *submitReqInfo;
    /**< Structure containing submit request information */
    Mlm_InstInfo      *mlmInstInfo;
    /**< Pointer to the mlmInstInfo structure */
} Mlm_QueueObj;

typedef struct Mlm_Obj_t
{
    VpsHal_Handle     vpdmaHandle;
    /**< VPDMA handle. */
    Vem_InstId        vemInstId;
    /**< Event Manager instance ID. */
    Vrm_InstId        vrmInstId;
    /**< Resource Manager instance ID. */
    BspOsal_SemHandle lockSem;
    /**< Semaphore handle for protecting register/unregister API */
} Mlm_Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Mlm_InstInfo *mlmGetFreeMlmInstance(void);

static Int32 mlmAllocResource(Mlm_InstInfo *mlmInstInfo);

static void mlmFreeResource(Mlm_InstInfo *mlmInstInfo);

static Int32 mlmAllocQueues(Mlm_InstInfo *mlmInstInfo);

static Int32 mlmFreeQueues(Mlm_InstInfo *mlmInstInfo);

static void mlmCreateCtrlDescs(const Mlm_InstInfo *mlmInstInfo);
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static void mlmSendIntrIsr(const UInt32 *event, UInt32 numEvents, Ptr arg);
static void mlmListCompleteIsr(const UInt32 *event, UInt32 numEvents, Ptr arg);
static void mlmDeiFmdIsr(const UInt32 *event, UInt32 numEvents, Ptr arg);
#ifdef __cplusplus
}
#endif

static void mlmGetRlDescInfo(const Mlm_InstInfo *mlmInstInfo,
                             Mlm_QueueObj       *qObj);

/* ========================================================================== */
/*                        Global Variables                                    */
/* ========================================================================== */

/**
 * \brief global object of mlm containing all parameters not specific to
 *  any instance
 */
static Mlm_Obj             MlmObj;

/**
 *  \brief Global variables of MLM Instaces
 */
static Mlm_InstInfo        MlmInstInfo[MLM_NUM_INSTANCES];

/**
 *  \brief A fixed set of queue objests are available for mlm instances.
 *  This has been pre-allocated in order to avoid changing utils file
 *  for number of queue objects. Also these are allocated per instances
 *  instead of set of queue objects.
 */
static Mlm_QueueObj        MlmQueueObj[MLM_NUM_INSTANCES][MLM_NUM_REQ_PER_INST];

/* Align descriptor memory with that of VPDMA requirement. */
/* Place the descriptor in non-cached section. */
#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsMlmDrvDescMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsMlmDrvDescMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt8               gVpsMlmDrvDescMem[MLM_NUM_INSTANCES][
    MLM_NUM_REQ_PER_INST * MLM_CTRL_DESC_MEMORY];

static UInt32              gVpsMlmDrvDescMemFlag[MLM_NUM_INSTANCES];
/**< The flag variable represents whether a handle object is allocated
 *   or not. */
static BspUtils_PoolParams gVpsMlmDrvDescMemPoolPrm;
/**< Pool params for handle memory. */

/* ========================================================================== */
/*                        FUNCTION DEFINITIONS                                */
/* ========================================================================== */

/**
 *  Mlm_init
 *  \brief Function to initialize VPS Memory List Manager. It initializes
 *  all global variables and keeps it ready.
 *
 *  \param initPrms     Init parameters.
 *
 *  \return             Returns 0 on success else returns error value.
 */
Int32 Mlm_init(const Mlm_InitParams *initPrms)
{
    Int32         retVal = BSP_SOK;
    UInt32        instCnt;
    Mlm_InstInfo *mlmInstInfo = NULL;
    Int32         initValue;

    GT_assert(VpsMlmTrace, (NULL != initPrms));
    GT_assert(VpsMlmTrace, (NULL != initPrms->vpdmaHandle));
    MlmObj.vpdmaHandle = initPrms->vpdmaHandle;
    MlmObj.vemInstId   = initPrms->vemInstId;
    MlmObj.vrmInstId   = initPrms->vrmInstId;

    BspUtils_initPool(&gVpsMlmDrvDescMemPoolPrm,
                      (void *) gVpsMlmDrvDescMem,
                      MLM_NUM_INSTANCES,
                      MLM_NUM_REQ_PER_INST * MLM_CTRL_DESC_MEMORY,
                      gVpsMlmDrvDescMemFlag,
                      VpsMlmTrace);

    /* For each of instances of MLM, create a queue of free control
     * descriptor and allocated descriptor */
    for (instCnt = 0U; instCnt < MLM_NUM_INSTANCES; instCnt++)
    {
        mlmInstInfo = &(MlmInstInfo[instCnt]);

        GT_assert(VpsMlmTrace, (NULL != mlmInstInfo));

        /* Initialize the instance with zero */
        BspUtils_memset(mlmInstInfo, 0U, sizeof (Mlm_InstInfo));

        /* Initialize all bool variables to FALSE */
        mlmInstInfo->isRegistered    = (UInt32) FALSE;
        mlmInstInfo->isListAllocated = (UInt32) FALSE;
        mlmInstInfo->isListActive    = (UInt32) FALSE;
        mlmInstInfo->instNum         = instCnt;
    }

    /* Get the semaphore handle */
    initValue      = 1;
    MlmObj.lockSem = BspOsal_semCreate(initValue, (Bool) TRUE);
    if (NULL == MlmObj.lockSem)
    {
        retVal = BSP_EALLOC;
    }

    return (retVal);
}

/**
 *  Mlm_deInit
 *  \brief Function to de-initialize VPS Memory List Manager.
 *
 *  \return              Returns 0 on success else returns error value.
 */
Int32 Mlm_deInit(void)
{
    BspOsal_semDelete(&(MlmObj.lockSem));

    return (BSP_SOK);
}

/**
 *  Mlm_register
 *  \brief Function to register memory driver to the MLM.
 *
 *  \param clientInfo    Pointer to client Info structure
 *  \param arg           Currently not used. For the future reference
 *
 *  \return              returns handle to the mlm client in case of success
 *                       returns null in case of error.
 */
Mlm_Handle Mlm_register(const Mlm_ClientInfo *clientInfo, Ptr arg)
{
    Int32         retVal      = BSP_SOK;
    Mlm_Handle    mlmHandle   = NULL;
    Mlm_InstInfo *mlmInstInfo = NULL;
    UInt32        fmdDeiInterruptId;
    UInt32        numEvents;

    GT_assert(VpsMlmTrace, (NULL != clientInfo));

    /* Get the semaphore */
    BspOsal_semWait(MlmObj.lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Find a free mlm instance */
    mlmInstInfo = mlmGetFreeMlmInstance();

    if (NULL != mlmInstInfo)
    {
        mlmInstInfo->vemFmdHandle = NULL;
        /* Since only one send interrupt is used in the set of control
         * descriptors, Following is set to one. This should be changed
         * when using multiple send interrupts per control descriptor set. */
        mlmInstInfo->numSiSrc = MLM_NUM_SI_CTRL_DESC;

        /* Get the free VPDMA list and Send Interrupt source number from
         * the resource manager */
        retVal = mlmAllocResource(mlmInstInfo);
    }
    else
    {
        GT_setFailureReason(VpsMlmTrace,
                            GT_INFO,
                            (const Char *) __FUNCTION__,
                            (UInt32) retVal,
                            (const Char *) "There are no free Mlm Instances\r\n");
        /* Since there are no free mlm instances, return value should be
         * negative so that no other processing will be done */
        retVal = BSP_EALLOC;
    }

    if (BSP_SOK == retVal)
    {
        /* Register Event Handles for the Send interrupts with the
         * higher priority than list complete */
        mlmInstInfo->vemSendIntrHandle = Vem_register(
            MlmObj.vemInstId,
            VEM_EG_SI,
            mlmInstInfo->siEventNum,
            mlmInstInfo->numSiSrc,
            MLM_VEM_SI_PRIORITY,
            &mlmSendIntrIsr,
            (Ptr) mlmInstInfo);
        /* Register List Complete Event Handler */
        numEvents = 1U;
        mlmInstInfo->vemListCmplHandle = Vem_register(
            MlmObj.vemInstId,
            VEM_EG_LISTCOMPLETE,
            &(mlmInstInfo->listNum),
            numEvents,
            MLM_VEM_LC_PRIORITY,
            &mlmListCompleteIsr,
            (Ptr) mlmInstInfo);

        if ((NULL == mlmInstInfo->vemSendIntrHandle) ||
            (NULL == mlmInstInfo->vemListCmplHandle))
        {
            GT_setFailureReason(VpsMlmTrace,
                                GT_INFO,
                                (const Char *) __FUNCTION__,
                                (UInt32) retVal,
                                (const Char *) "VEM Registration Failed\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Register FMD Event Handler */
        fmdDeiInterruptId = VEM_OE_MAX;
        if (MLM_CT_VPE == clientInfo->clientType)
        {
            fmdDeiInterruptId = VEM_OE_FMD_DEI;
        }

        if ((VEM_OE_MAX != fmdDeiInterruptId) && (NULL != clientInfo->deiFmdCb))
        {
            numEvents = 1U;
            mlmInstInfo->vemFmdHandle =
                Vem_register(
                    MlmObj.vemInstId,
                    VEM_EG_OTHERS,      /* Event group */
                    &fmdDeiInterruptId, /* pointer to event */
                    numEvents,          /* number of events */
                    VEM_PRIORITY0,      /* priority */
                    &mlmDeiFmdIsr,      /* call back */
                    (Ptr) mlmInstInfo);
            if (NULL == mlmInstInfo->vemFmdHandle)
            {
                GT_setFailureReason(VpsMlmTrace,
                                    GT_INFO,
                                    (const Char *) __FUNCTION__,
                                    (UInt32) retVal,
                                    (const Char *) "VEM FMD Registration Failed\r\n");
                retVal = BSP_EFAIL;
            }
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Create two queues, one for storing free memory pool and other
         * for allocated memory pools.
         * Get the nodes from the BspUtils for this mlm instance and add
         * them as the free queue.
         * This will also set pointer in the queue object at the
         * appropriate location in mlm control descriptors */
        retVal = mlmAllocQueues(mlmInstInfo);
        if (BSP_SOK != retVal)
        {
            GT_setFailureReason(VpsMlmTrace,
                                GT_INFO,
                                (const Char *) __FUNCTION__,
                                (UInt32) retVal,
                                (const Char *) "Queue Allocation Failed\r\n");
        }
    }

    if (BSP_SOK == retVal)
    {
        /* *Store client information structure in mlm instance structure */
        BspUtils_memcpy(&(mlmInstInfo->clientInfo),
                        clientInfo,
                        sizeof (Mlm_ClientInfo));

        mlmInstInfo->isRegistered = (UInt32) TRUE;

        mlmInstInfo->ctrlDescSize = MLM_CTRL_DESC_MEMORY;

        /* Create Send Interrupt control descriptor in the descriptor memory */
        mlmCreateCtrlDescs(mlmInstInfo);

        mlmHandle = (Mlm_InstInfo *) mlmInstInfo;
    }

    /* Free up the resources if return value is negative */
    if (BSP_SOK != retVal)
    {
        if (NULL != mlmInstInfo)
        {
            mlmFreeQueues(mlmInstInfo);

            mlmFreeResource(mlmInstInfo);

            if (NULL != mlmInstInfo->vemSendIntrHandle)
            {
                Vem_unRegister(mlmInstInfo->vemSendIntrHandle);
            }
            if (NULL != mlmInstInfo->vemListCmplHandle)
            {
                Vem_unRegister(mlmInstInfo->vemListCmplHandle);
            }
            if (NULL != mlmInstInfo->vemFmdHandle)
            {
                Vem_unRegister(mlmInstInfo->vemFmdHandle);
                mlmInstInfo->vemFmdHandle = NULL;
            }
        }
    }

    /* Release Semaphore */
    BspOsal_semPost(MlmObj.lockSem);

    return (mlmHandle);
}

/**
 *  Mlm_unRegister
 *  \brief Function to un-register memory driver to the MLM.
 *
 *  \param mlmHandle     Handle to Memory to Memory driver client
 *
 *  \return              Returns 0 on success else returns error value.
 */
Int32 Mlm_unRegister(Mlm_Handle mlmHandle)
{
    Int32         retVal      = BSP_SOK;
    Mlm_InstInfo *mlmInstInfo = NULL;

    GT_assert(VpsMlmTrace, (NULL != mlmHandle));

    /* Get the semaphore */
    BspOsal_semWait(MlmObj.lockSem, BSP_OSAL_WAIT_FOREVER);

    mlmInstInfo = (Mlm_InstInfo *) mlmHandle;

    /* Note: Make sure that there are no request, which are active or
     * submitted to mlm but no active. If it is the case, currently
     * mlm asserts for these case. This should be taken care by the
     * memory driver. */
    GT_assert(VpsMlmTrace,
              ((UInt32) TRUE == BspUtils_isListEmpty(mlmInstInfo->activeQueue)));
    GT_assert(VpsMlmTrace,
              ((UInt32) TRUE == BspUtils_isListEmpty(mlmInstInfo->requestQueue)));

    /* Free up the queues */
    mlmFreeQueues(mlmInstInfo);

    /* FRee the resources */
    mlmFreeResource(mlmInstInfo);

    /* Clear the clientInfo structure */
    BspUtils_memset((Ptr) & (mlmInstInfo->clientInfo),
                    0,
                    sizeof (Mlm_ClientInfo));

    if (NULL != mlmInstInfo->vemSendIntrHandle)
    {
        Vem_unRegister(mlmInstInfo->vemSendIntrHandle);
        mlmInstInfo->vemSendIntrHandle = NULL;
    }
    if (NULL != mlmInstInfo->vemListCmplHandle)
    {
        Vem_unRegister(mlmInstInfo->vemListCmplHandle);
        mlmInstInfo->vemListCmplHandle = NULL;
    }
    if (NULL != mlmInstInfo->vemFmdHandle)
    {
        Vem_unRegister(mlmInstInfo->vemFmdHandle);
        mlmInstInfo->vemFmdHandle = NULL;
    }

    mlmInstInfo->isRegistered = (UInt32) FALSE;

    /* Release Semaphore */
    BspOsal_semPost(MlmObj.lockSem);

    return (retVal);
}

/**
 *  Mlm_submit
 *  \brief Function to submit a requst to the MLM.
 *
 *  \param mlmHandle     Handle to Memory to Memory driver client
 *  \param submitReq     Pointer to submitRequestInfo structure containing
 *                       pointer to the list to be submitted.
 *
 *  \return              Returns 0 on success else returns error value.
 */
Int32 Mlm_submit(Mlm_Handle mlmHandle, Mlm_SubmitReqInfo *submitReq)
{
    Int32  retVal = BSP_SOK;
    UInt32 cookie;
    UInt8               *ctrlDescPtr;
    Mlm_InstInfo        *mlmInstInfo = NULL;
    BspUtils_Node       *qElem       = NULL, *prevQElem = NULL;
    Mlm_QueueObj        *qObj        = NULL, *prevQObj = NULL;
    Mlm_SubmitReqInfo   *prevSmReq;
    UInt32 isEmpty = FALSE;

    GT_assert(VpsMlmTrace, (NULL != mlmHandle));
    GT_assert(VpsMlmTrace, (NULL != submitReq));

    mlmInstInfo = (Mlm_InstInfo *) mlmHandle;

    /* Disable the interrupts */
    cookie = BspOsal_disableInterrupt();

    if (MLM_SRT_USE_SOC == submitReq->submitReqType)
    {
        /* This condition checking is needed only if mlm adds sync
         * on channel control descritor */
        if ((FALSE == mlmInstInfo->clientInfo.isChannelStatic) &&
            ((submitReq->numChannels > MLM_MAX_CHANNELS) ||
             (0U == submitReq->numChannels)))
        {
            GT_setFailureReason(VpsMlmTrace,
                                GT_INFO,
                                (const Char *) __FUNCTION__,
                                (UInt32) retVal,
                                (const Char *) "Wrong Number of Channels\r\n");
            retVal = BSP_EFAIL;
        }
    }

    /* Get a free Queue element from the element queue */
    qElem = BspUtils_unLinkNodeFromHead(mlmInstInfo->freeCtrlDesc);

    if (NULL == qElem)
    {
        GT_setFailureReason(VpsMlmTrace,
                            GT_INFO,
                            (const Char *) __FUNCTION__,
                            (UInt32) retVal,
                            (const Char *) "No Free Control Desc Memory\r\n");
        retVal = BSP_EALLOC;
    }

    if (BSP_SOK == retVal)
    {
        qObj = (Mlm_QueueObj *) (qElem->data);

        GT_assert(VpsMlmTrace, (NULL != qObj));

        /* Assign pointer to requestinfo to qObject */
        qObj->submitReqInfo = submitReq;

        /* Create Dummy descriptor for the last client */
        VpsHal_vpdmaCreateDummyDesc(qObj->rlDescPtr);

        /* Calculate the Control Descriptor pointer and size of the
         * mlm control descriptors and store them in the queue object */
        mlmGetRlDescInfo(mlmInstInfo, qObj);

        /* Create Reload Descriptor in the last request to point
         * to mlm control descriptors */
        VpsHal_vpdmaCreateRLCtrlDesc(submitReq->lastRlDescAddr,
                                     qObj->ctrlDescPtr,
                                     qObj->ctrlDescSize);

        if (TRUE == mlmInstInfo->isListActive)
        {
            /* Check to see if requests can be linked or not */
            isEmpty = BspUtils_isListEmpty(mlmInstInfo->requestQueue);

            /* if request queue is not empty, link this request with the
             * other request */
            if ((UInt32) FALSE == isEmpty)
            {
                /* Get the tail node from the request queue */
                prevQElem = BspUtils_getTailNode(mlmInstInfo->requestQueue);
                GT_assert(VpsMlmTrace, (NULL != prevQElem));

                prevQObj = (Mlm_QueueObj *) (prevQElem->data);
                GT_assert(VpsMlmTrace, (NULL != prevQObj));

                prevSmReq = prevQObj->submitReqInfo;
                GT_assert(VpsMlmTrace, (NULL != prevSmReq));

                /* Add size of the reload descriptor to the last requests
                 * reload descriptor */
                if (MLM_SRT_USE_SOC == prevSmReq->submitReqType)
                {
                    /* Update the size of the descriptors here */
                    /* If the previous request requires use of Soc,
                     * point reload to soc control descriptor and size should
                     * be all descriptors. */
                    ctrlDescPtr = (UInt8 *) prevQObj->ctrlDescPtr;
                    prevQObj->ctrlDescSize += ((MLM_NUM_SI_CTRL_DESC *
                                                VPSHAL_VPDMA_CTRL_DESC_SIZE) +
                                               (MLM_NUM_RL_CTRL_DESC *
                                                VPSHAL_VPDMA_CTRL_DESC_SIZE));
                }
                else
                {
                    /* If the previous request does not require use of Soc,
                     * point reload to Send Interrupt control descriptor
                     * and size should be one less control descriptor. */
                    ctrlDescPtr = (UInt8 *) prevQObj->siDescPtr;
                    prevQObj->ctrlDescSize +=
                        (MLM_NUM_SI_CTRL_DESC * VPSHAL_VPDMA_CTRL_DESC_SIZE);
                }

                VpsHal_vpdmaCreateRLCtrlDesc(
                    prevQObj->submitReqInfo->lastRlDescAddr,
                    ctrlDescPtr,
                    prevQObj->ctrlDescSize);

                /* Point to reload descriptor of the control descriptor set
                 * to this new request */
                VpsHal_vpdmaCreateRLCtrlDesc(
                    prevQObj->rlDescPtr,
                    submitReq->reqStartAddr,
                    submitReq->firstChannelSize);
            }
            /* Add this request into the request queue */
            BspUtils_linkNodeToTail(mlmInstInfo->requestQueue, qElem);
        }
        else /* Submit the request as the list is not active */
        {
            /* Request and active Queue should be empty when list
             * is not active */
            GT_assert(VpsMlmTrace,
                      ((UInt32) TRUE ==
                       BspUtils_isListEmpty(mlmInstInfo->requestQueue)));
            GT_assert(VpsMlmTrace,
                      ((UInt32) TRUE ==
                       BspUtils_isListEmpty(mlmInstInfo->activeQueue)));

            /* Put the request into the active queue */
            BspUtils_linkNodeToTail(mlmInstInfo->activeQueue, qElem);

            /* Submit the list to the VPDMA */
            VpsHal_vpdmaPostList(MlmObj.vpdmaHandle,
                                 mlmInstInfo->listNum,
                                 VPSHAL_VPDMA_LT_NORMAL,
                                 submitReq->reqStartAddr,
                                 submitReq->firstChannelSize,
                                 (UInt32) TRUE);

            /* Mark the list as active now */
            mlmInstInfo->isListActive = (UInt32) TRUE;
        }
    }

    /* Enable interrupts */
    BspOsal_restoreInterrupt(cookie);

    return (retVal);
}

/**
 * \brief Function to get the free mlm instance from the list of mlm instances
 */
static Mlm_InstInfo *mlmGetFreeMlmInstance(void)
{
    UInt32        mlmInstCnt;
    Mlm_InstInfo *mlmInstInfo = NULL;

    /* Find free mlm instance structure */
    for (mlmInstCnt = 0U; mlmInstCnt < MLM_NUM_INSTANCES; mlmInstCnt++)
    {
        mlmInstInfo = &(MlmInstInfo[mlmInstCnt]);

        if (FALSE == mlmInstInfo->isRegistered)
        {
            /* Found a free mlm Instace */
            break;
        }
    }

    return (mlmInstInfo);
}

/**
 *  \brief Function to allocate required resources from the resource
 *  manager for given mlm instance.
 */
static Int32 mlmAllocResource(Mlm_InstInfo *mlmInstInfo)
{
    Int32  retVal = BSP_SOK;
    UInt32 listNum;

    GT_assert(VpsMlmTrace, (NULL != mlmInstInfo));
    GT_assert(VpsMlmTrace, (TRUE != mlmInstInfo->isListAllocated));

    retVal = Vrm_allocList(MlmObj.vrmInstId, &listNum, VRM_LIST_TYPE_M2M);

    if (BSP_SOK == retVal)
    {
        mlmInstInfo->listNum = listNum;

        retVal = Vrm_allocSendIntr(MlmObj.vrmInstId,
                                   mlmInstInfo->siEventNum,
                                   mlmInstInfo->numSiSrc);
        if (BSP_SOK != retVal)
        {
            /* There is some error occured so free up the list and return
             * error */
            Vrm_releaseList(MlmObj.vrmInstId, mlmInstInfo->listNum);
        }
        else
        {
            mlmInstInfo->isListAllocated = (UInt32) TRUE;
        }
    }

    return (retVal);
}

static void mlmFreeResource(Mlm_InstInfo *mlmInstInfo)
{
    GT_assert(VpsMlmTrace, (NULL != mlmInstInfo));

    if (TRUE == mlmInstInfo->isListAllocated)
    {
        Vrm_releaseList(MlmObj.vrmInstId, mlmInstInfo->listNum);

        Vrm_releaseSendIntr(
            MlmObj.vrmInstId,
            mlmInstInfo->siEventNum,
            mlmInstInfo->numSiSrc);

        mlmInstInfo->isListAllocated = (UInt32) FALSE;
    }

    return;
}

/**
 *  \brief Function to allocate the queues and queue elements for the given
 *  mlm instance
 */
static Int32 mlmAllocQueues(Mlm_InstInfo *mlmInstInfo)
{
    Int32         retVal = BSP_EALLOC;
    UInt32        elemCnt, mlmInstNum;
    UInt32        rlDescOffset, siDescOffset, ctrlDescOffset;
    Mlm_QueueObj *qObj = NULL;

    GT_assert(VpsMlmTrace, (NULL != mlmInstInfo));

    /* Create free, allocated and active queues for this mlm instance */
    BspUtils_constructLinkList(&mlmInstInfo->freeCtrlDescObj,
                               BSPUTILS_LLT_DOUBLE,
                               BSPUTILS_LAM_PRIORITY);
    mlmInstInfo->freeCtrlDesc = &mlmInstInfo->freeCtrlDescObj;
    BspUtils_constructLinkList(&mlmInstInfo->requestQueueObj,
                               BSPUTILS_LLT_DOUBLE,
                               BSPUTILS_LAM_PRIORITY);
    mlmInstInfo->requestQueue = &mlmInstInfo->requestQueueObj;
    BspUtils_constructLinkList(&mlmInstInfo->activeQueueObj,
                               BSPUTILS_LLT_DOUBLE,
                               BSPUTILS_LAM_PRIORITY);
    mlmInstInfo->activeQueue = &mlmInstInfo->activeQueueObj;

    mlmInstInfo->descPtr = (UInt8 *) BspUtils_alloc(
        &gVpsMlmDrvDescMemPoolPrm,
        MLM_NUM_REQ_PER_INST * MLM_CTRL_DESC_MEMORY,
        VpsMlmTrace);

    /* Calculate Offsets for the Send interrupt control desc. and reload
     * ctrl desc. Reload Control Descriptor is stored at the end of
     * control descripor memory and Send interrupt control descriptor
     * is just before Reload Control Descriptor */
    rlDescOffset = MLM_CTRL_DESC_MEMORY - (MLM_NUM_RL_CTRL_DESC *
                                           VPSHAL_VPDMA_CTRL_DESC_SIZE);
    siDescOffset = rlDescOffset - (MLM_NUM_SI_CTRL_DESC *
                                   VPSHAL_VPDMA_CTRL_DESC_SIZE);
    /* Assuming atleast single control descriptor is available */
    ctrlDescOffset = siDescOffset - VPSHAL_VPDMA_CTRL_DESC_SIZE;

    if ((NULL != mlmInstInfo->freeCtrlDesc) &&
        (NULL != mlmInstInfo->requestQueue) &&
        (NULL != mlmInstInfo->activeQueue) &&
        (NULL != mlmInstInfo->descPtr))
    {
        /* Get the mlm instace number */
        mlmInstNum = mlmInstInfo->instNum;

        for (elemCnt = 0U; elemCnt < MLM_NUM_REQ_PER_INST; elemCnt++)
        {
            /* Get the Queue Object */
            qObj = &(MlmQueueObj[mlmInstNum][elemCnt]);

            GT_assert(VpsMlmTrace, (NULL != qObj));

            /* Assign Memory Pool as the data to the queue element */
            qObj->qElem.data = (void *) (qObj);

            qObj->descPtr = mlmInstInfo->descPtr +
                            (elemCnt * MLM_CTRL_DESC_MEMORY);

            /* Store the Pointer to sync on channel, send interrupt and
             * reload control descriptor. Assuming there is atleast
             * single control descriptor. */
            qObj->ctrlDescPtr = (Ptr) (qObj->descPtr + ctrlDescOffset);
            qObj->siDescPtr   = (Ptr) (qObj->descPtr + siDescOffset);
            qObj->rlDescPtr   = (Ptr) (qObj->descPtr + rlDescOffset);

            /* Initialize pointer to instance info structure in the
             * queue object */
            qObj->mlmInstInfo = mlmInstInfo;

            /* Add these control descriptors memories to the queue of
             * free descriptors */
            BspUtils_linkNodeToHead(mlmInstInfo->freeCtrlDesc, &(qObj->qElem));

            retVal = BSP_SOK;
        }
    }

    return (retVal);
}

/**
 *  \brief Function to free the queues and queue elements for the given
 *  mlm instance
 */
static Int32 mlmFreeQueues(Mlm_InstInfo *mlmInstInfo)
{
    Int32           retVal = BSP_EFAIL;
    UInt32          qElemCnt;
    BspUtils_QElem *qElem = NULL;
    Mlm_QueueObj   *qObj  = NULL;

    GT_assert(VpsMlmTrace, (NULL != mlmInstInfo));
    GT_assert(VpsMlmTrace, (NULL != mlmInstInfo->freeCtrlDesc));
    GT_assert(VpsMlmTrace, (NULL != mlmInstInfo->requestQueue));
    GT_assert(VpsMlmTrace, (NULL != mlmInstInfo->activeQueue));

    /* Free up the Queues */
    if (NULL != mlmInstInfo->freeCtrlDesc)
    {
        for (qElemCnt = 0U; qElemCnt < MLM_NUM_REQ_PER_INST; qElemCnt++)
        {
            /* Assumption here is that when this function is called, all the
             * requests are completed and all control descriptors memory for
             * all request are free and queued in the free queue so that they
             * can be dequeued here from the free queue and released. */
            qElem = BspUtils_unLinkNodeFromHead(mlmInstInfo->freeCtrlDesc);
            GT_assert(VpsMlmTrace, (NULL != qElem));

            qObj = (Mlm_QueueObj *) (qElem->data);
            GT_assert(VpsMlmTrace, (NULL != qObj));

            qObj->descPtr       = NULL;
            qObj->ctrlDescPtr   = NULL;
            qObj->submitReqInfo = NULL;
            qObj->rlDescPtr     = NULL;
            qObj->siDescPtr     = NULL;
            qObj->ctrlDescSize  = 0U;

            qElem->data = NULL;
        }

        BspUtils_destructLinkList(mlmInstInfo->freeCtrlDesc);
        mlmInstInfo->freeCtrlDesc = NULL;
    }
    if (NULL != mlmInstInfo->requestQueue)
    {
        BspUtils_destructLinkList(mlmInstInfo->requestQueue);
        mlmInstInfo->requestQueue = NULL;
    }
    if (NULL != mlmInstInfo->activeQueue)
    {
        BspUtils_destructLinkList(mlmInstInfo->activeQueue);
        mlmInstInfo->activeQueue = NULL;
    }
    if (NULL != mlmInstInfo->descPtr)
    {
        BspUtils_free(
            &gVpsMlmDrvDescMemPoolPrm,
            mlmInstInfo->descPtr,
            VpsMlmTrace);
        mlmInstInfo->descPtr = NULL;
    }

    return (retVal);
}

/**
 *  \brief Function to create Control descriptors in the descriptors memory.
 *  This is created once because these control descriptors will not be changed
 *  after client is registered. Only Reload Control descriptor at the
 *  end of the mlm control descriptor will be changed to point to new memory
 */
static void mlmCreateCtrlDescs(const Mlm_InstInfo *mlmInstInfo)
{
    UInt32        elemCnt, siCnt;
    Mlm_QueueObj *qObj        = NULL;
    UInt8        *ctrlDescPtr = NULL;
    UInt32        mlmInst, chanCnt;

    GT_assert(VpsMlmTrace, (NULL != mlmInstInfo));

    mlmInst = mlmInstInfo->instNum;

    for (elemCnt = 0U; elemCnt < MLM_NUM_REQ_PER_INST; elemCnt++)
    {
        qObj = &(MlmQueueObj[mlmInst][elemCnt]);

        ctrlDescPtr = (UInt8 *) qObj->siDescPtr;
        for (siCnt = 0U; siCnt < mlmInstInfo->numSiSrc; siCnt++)
        {
            /* Create Send Interrupt Control Descriptor */
            VpsHal_vpdmaCreateSICtrlDesc((Ptr) ctrlDescPtr,
                                         (UInt16) mlmInstInfo->siEventNum[0U]);
            ctrlDescPtr = ctrlDescPtr + VPSHAL_VPDMA_CTRL_DESC_SIZE;
        }

        /* If the channels are static, create the control descriptors
         * here itself, so that there is no need to create them everytime */
        if (TRUE == mlmInstInfo->clientInfo.isChannelStatic)
        {
            ctrlDescPtr = (UInt8 *) qObj->siDescPtr;
            GT_assert(VpsMlmTrace, (NULL != ctrlDescPtr));

            /* Create Sync on Channel Control descriptors */
            for (chanCnt = 0U; chanCnt < mlmInstInfo->clientInfo.numChannels;
                 chanCnt++)
            {
                ctrlDescPtr = ctrlDescPtr - VPSHAL_VPDMA_CTRL_DESC_SIZE;
                GT_assert(VpsMlmTrace, (NULL != ctrlDescPtr));

                VpsHal_vpdmaCreateSOCHCtrlDesc(
                    (Ptr) ctrlDescPtr,
                    mlmInstInfo->clientInfo.chNum[chanCnt]);
            }
            /* Store Pointer to the control descriptors */
            qObj->ctrlDescPtr = ctrlDescPtr;

            /* Store the size of the control descriptors. Here the
             * size includes only set of sync on channel control
             * descriptors. It is because if this is the last
             * request, there is no need to have SI control
             * descriptor. List Complete Interrupt will provide
             * client callback. */
            qObj->ctrlDescSize =
                (UInt8 *) qObj->siDescPtr - (UInt8 *) ctrlDescPtr;
        }

        /* Here Configuration descriptor is used as a dummy control
         * descriptor. For the last request, these is no need to have a
         * relead control descriptor. So instead of reload
         * descriptor, dummy configuration descriptor is created. */
        VpsHal_vpdmaCreateDummyDesc(qObj->rlDescPtr);
    }

    return;
}

static void mlmSendIntrIsr(const UInt32 *event, UInt32 numEvents, Ptr arg)
{
    Mlm_InstInfo  *mlmInstInfo = (Mlm_InstInfo *) arg;
    BspUtils_Node *qElem       = NULL;

    if (TRUE == mlmInstInfo->isListActive)
    {
        /* Just call the callback function of the client */
        /* Remove the request from the active queue */
        qElem = BspUtils_unLinkNodeFromHead(mlmInstInfo->activeQueue);
        GT_assert(VpsMlmTrace, (NULL != qElem));
        GT_assert(VpsMlmTrace, (NULL != mlmInstInfo->clientInfo.reqCompleteCb));

        /* Call the request completion callback function of
         * the client */
        mlmInstInfo->clientInfo.reqCompleteCb(
            ((Mlm_QueueObj *) (qElem->data))->submitReqInfo);
        /* Set the request pointer to null */
        ((Mlm_QueueObj *) (qElem->data))->submitReqInfo = NULL;

        /* Add the free queue node to the free list */
        BspUtils_linkNodeToHead(mlmInstInfo->freeCtrlDesc, qElem);
    }
    else
    {
        /* TODO: How to handle a situation where List Complete happens
         * first then send Interrupt */

        /* There is some problem */
    }

    return;
}

static void mlmListCompleteIsr(const UInt32 *event, UInt32 numEvents, Ptr arg)
{
    Mlm_InstInfo  *mlmInstInfo = (Mlm_InstInfo *) arg;
    UInt32         isEmpty;
    BspUtils_Node *qElem = NULL;
    Mlm_QueueObj  *qObj  = NULL;

    /* There is no need to disable interrupts here as VPS gives single
     * interrupt to the processor and VEM gives callback to its client
     * one by one. If there are multiple interrupts, this should be
     * protected */
    if (TRUE == mlmInstInfo->isListActive)
    {
        /* If active queue is not free, either the send interrupt missed or
         * list complete interrupt callback called before send interrupt.
         * In this case, just call callback api for all the active requests
         * and free up the queue */
        isEmpty = BspUtils_isListEmpty(mlmInstInfo->activeQueue);
        if ((UInt32) FALSE == isEmpty)
        {
            do
            {
                /* Remove the request from the active queue */
                qElem = BspUtils_unLinkNodeFromHead(mlmInstInfo->activeQueue);
                GT_assert(VpsMlmTrace, (NULL != qElem));

                qObj = (Mlm_QueueObj *) (qElem->data);
                GT_assert(VpsMlmTrace, (NULL != qObj));

                GT_assert(VpsMlmTrace,
                          (NULL != mlmInstInfo->clientInfo.reqCompleteCb));

                /* Call the request completion callback function of
                 * the client */
                mlmInstInfo->clientInfo.reqCompleteCb(
                    qObj->submitReqInfo);
                /* Set the request pointer to null */
                qObj->submitReqInfo = NULL;

                /* Add the free queue node to the free list */
                BspUtils_linkNodeToHead(mlmInstInfo->freeCtrlDesc, qElem);

                isEmpty = BspUtils_isListEmpty(mlmInstInfo->activeQueue);
            } while ((UInt32) FALSE == isEmpty);

            /* Active queue is free now */
        }

        /* If the request queue is not free, submit new request to the VPDMA
         * and mode all queue elements from request queue to active queue */
        isEmpty = BspUtils_isListEmpty(mlmInstInfo->requestQueue);
        if ((UInt32) FALSE == isEmpty)
        {
            do
            {
                /* Remove the request from the active queue */
                qElem = BspUtils_unLinkNodeFromHead(mlmInstInfo->requestQueue);
                GT_assert(VpsMlmTrace, (NULL != qElem));

                BspUtils_linkNodeToTail(mlmInstInfo->activeQueue, qElem);

                isEmpty = BspUtils_isListEmpty(mlmInstInfo->requestQueue);
            } while ((UInt32) FALSE == isEmpty);

            qElem = BspUtils_getHeadNode(mlmInstInfo->activeQueue);

            qObj = (Mlm_QueueObj *) (qElem->data);

            /* Submit the list to the VPDMA */
            VpsHal_vpdmaPostList(
                MlmObj.vpdmaHandle,
                mlmInstInfo->listNum,
                VPSHAL_VPDMA_LT_NORMAL,
                qObj->submitReqInfo->reqStartAddr,
                qObj->submitReqInfo->firstChannelSize,
                (UInt32) TRUE);
        }
        else
        {
            /* Since there are no request in the request queue, mark
             * the list as nonactive */
            mlmInstInfo->isListActive = (UInt32) FALSE;
        }
    }
    else
    {
        /* There is some problem */
    }

    return;
}

/* SOR FMD intterrupt */
static void mlmDeiFmdIsr(const UInt32 *event, UInt32 numEvents, Ptr arg)
{
    BspUtils_Node *qElem       = NULL;
    Mlm_InstInfo  *mlmInstInfo = (Mlm_InstInfo *) arg;

    if (TRUE == mlmInstInfo->isListActive)
    {
        /* Just call the callback function of the client */
        /* Get the request from the active queue */
        qElem = BspUtils_getHeadNode(mlmInstInfo->activeQueue);

        GT_assert(VpsMlmTrace, (NULL != qElem));
        GT_assert(VpsMlmTrace, (NULL != mlmInstInfo->clientInfo.deiFmdCb));

        /* Call the FMD callback function of the client */
        mlmInstInfo->clientInfo.deiFmdCb(
            ((Mlm_QueueObj *) (qElem->data))->submitReqInfo);
    }
    else
    {
        /* What I need to do here? */
    }

    /* Signal Sync On Register from Master DLM ISR so that the list continues */
    VpsHal_vpdmaSetSyncList(MlmObj.vpdmaHandle, mlmInstInfo->listNum);

    return;
}

static void mlmGetRlDescInfo(const Mlm_InstInfo *mlmInstInfo,
                             Mlm_QueueObj       *qObj)
{
    UInt8 *tempDescPtr;
    UInt32 chanCnt;
    UInt32 numChannels;
    Mlm_SubmitReqInfo *submitReq;

    GT_assert(VpsMlmTrace, (NULL != mlmInstInfo));
    GT_assert(VpsMlmTrace, (NULL != qObj));

    submitReq = qObj->submitReqInfo;

    /* Create Reload Descriptor in the last reload descriptor of
     * the request */
    if (MLM_SRT_USE_SOC == submitReq->submitReqType)
    {
        /* Get the number of channels either from clientInfo structure
         * or from submitreqInfo depending on whether channels are static
         * or not. */
        if (FALSE == mlmInstInfo->clientInfo.isChannelStatic)
        {
            numChannels = submitReq->numChannels;
        }
        else
        {
            numChannels = mlmInstInfo->clientInfo.numChannels;
        }

        /* Get the pointer to the Send Interrupt control descriptor */
        tempDescPtr = (UInt8 *) qObj->siDescPtr;
        GT_assert(VpsMlmTrace, (NULL != tempDescPtr));

        for (chanCnt = 0U; chanCnt < numChannels; chanCnt++)
        {
            tempDescPtr = tempDescPtr - VPSHAL_VPDMA_CTRL_DESC_SIZE;
            GT_assert(VpsMlmTrace, (NULL != tempDescPtr));

            /* Create SyncOnChannel Control Descriptor at this
             * pointer only if channels are non-static */
            if (FALSE == mlmInstInfo->clientInfo.isChannelStatic)
            {
                VpsHal_vpdmaCreateSOCHCtrlDesc(
                    (Ptr) tempDescPtr,
                    submitReq->chNum[chanCnt]);
            }
        }
        /* Store Pointer to the control descriptors */
        qObj->ctrlDescPtr = tempDescPtr;

        /* Store the size of the control descriptors. Here the
         * size includes only set of sync on channel control
         * descriptors. It is because if this is the last
         * request, there is no need to have SI control
         * descriptor. List Complete Interrupt will provide
         * client callback. */
        qObj->ctrlDescSize = (UInt8 *) qObj->siDescPtr - tempDescPtr;
    }
    else if (MLM_SRT_USE_SOR_NO_SOC == submitReq->submitReqType)
    {
        /* Get the pointer to the SOR control descriptor */
        tempDescPtr = (UInt8 *) qObj->siDescPtr;
        GT_assert(VpsMlmTrace, (NULL != tempDescPtr));

        VpsHal_vpdmaCreateSORCtrlDesc((Ptr) tempDescPtr, mlmInstInfo->listNum);

        /* Store Pointer to SOR descriptor */
        qObj->ctrlDescPtr = qObj->siDescPtr;
        /* Control Descriptor size is one SOR descriptor plus one
         * reload descriptor */
        qObj->ctrlDescSize =
            VPSHAL_VPDMA_CTRL_DESC_SIZE + VPSHAL_VPDMA_CTRL_DESC_SIZE;
    }
    else
    {
        /* Store Pointer where Reload Pointer should point */
        qObj->ctrlDescPtr = qObj->rlDescPtr;
        /* Control Descriptor size is just one reload descriptor */
        qObj->ctrlDescSize = VPSHAL_VPDMA_CTRL_DESC_SIZE;
    }

    return;
}

