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
 *  \file iem_evtmgr.c
 *
 *  \brief File containing the ISS ISIF HAL init, deinit and other common
 *  functions.
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
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_iss.h>

#include <ti/drv/vps/include/iss/vps_isscommon.h>
#include <ti/drv/vps/include/iss/vps_cfgcal.h>
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Maximum number of clients for Event Manager. */
#define IEM_MAX_CLIENTS                 (50U)
#define IEM_MAX_CLIENT_EVENTS           (15U)

/**
 *  \brief Flags used by clientinfo structures memory pool manager to
 *  indicate availability of pool memory
 */
#define IEM_MEM_FLAG_FREE               (0xFFFFFFFFU)
#define IEM_MEM_FLAG_ALLOC              (0x00000000U)

/**
 *  \brief Interrupt max level.
 *          For most of the ISS events, will have 2 levels, as shown below
 *          0 Used for ISS top level interrupt (enable/disable/status/clear)
 *          1 Used module specific interrupt (enable/disable/status/clear)
 *          For some cases (such as CAL errors) there could additional level
 *          2 Used for low level errors / warning (such as CRC, ECC, FS, etc...)
 */
#define IEM_MAX_LEVELS                  (3U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief structure containing instance specific information, there should be
 *         one instance object for each independent irq
 */
typedef struct issemInstObj
{
    uint32_t           isInitDone;
    /**< Flag to indicate that the instance is initialized */
    uint32_t           instId;
    /**< IEM Instance ID. */
    uint32_t           irqNumber;
    /**< IRQ number at CPU level INTC. */
    uint32_t           eoiAddr;
    /**< Address of EOI register. */
    BspUtils_Node     *headNode;
    /**< Pointer to the head node of the priority linked list. */
    BspOsal_IntrHandle intrHandle;
    /**< Handle to Hardware Interrupt. */
    uint32_t           numIntr;
    /**< Total number of interrupts occured since last init. */
    BspUtils_TsPrfLog  isrPrfLog;
    /**< ISR duration performance log. */
} issemInstObj_t;

typedef struct issemClientInfo
{
    uint32_t          statusReg[IEM_MAX_CLIENT_EVENTS][IEM_MAX_LEVELS];
    /**< Address of the status register for multiple levels,
     *   Level0 provides the actual IRQ,
     *   status is checked at the last level,
     *   status is cleared from level0 to last level in sequence */
    uint32_t          statusClrReg[IEM_MAX_CLIENT_EVENTS][IEM_MAX_LEVELS];
    /**< Address of the status clear register */
    uint32_t          mask[IEM_MAX_CLIENT_EVENTS][IEM_MAX_LEVELS];
    /**< Bitmask for checking and clearing the status of the event/irq */
    Bool              isThirdLevelReq[IEM_MAX_CLIENT_EVENTS];
    /**< Flag to indicate if third level of interrupt handling is required.
            FALSE for most of the ISS events, with CAL error being the
            exception */
    issemClientCbFxn  clientCb;
    /**< Client's callback function. This function will be called by the
     *   event manager whenever client registered event occurs */
    Ptr               arg;
    /**< client's private data to be passed to it when callback function is
     *   called */
    issemEventGroup_t eventGroup;
    /**< This tells the event group into which registered event belongs */
    uint32_t          numIntr;
    /**< Number of interrupts occurred for this client */
    issemPriority_t   priority;
    /**< Priority of these events */
    uint32_t          subModuleEoiAddr[IEM_MAX_CLIENT_EVENTS];
    /**< Need to see if we could set this register */
    uint32_t          subModuleEoiLine[IEM_MAX_CLIENT_EVENTS];
    /**< IRQ Id */
    issemInstObj_t   *instObj;
    /**< Pointer to the Instance Object */
    uint32_t          allEvents[IEM_MAX_CLIENT_EVENTS];
    /**< List of events for which client has registered callback */
    uint32_t          setEvents[IEM_MAX_CLIENT_EVENTS];
    /**< This array contains the list of events occurred at the time of
     *   interrupt. It will be passed down to the clients.*/
    uint32_t          numEvents;
    /**< Count of events for client has registered callback. */
} issemClientInfo_t;

/**
 *  \brief structure to keep track of commonly used variables in event manager.
 */
typedef struct issemCommonObj
{
    issemClientInfo_t clientMemPool[IEM_MAX_CLIENTS];
    /**< Pool of memory for the clientinfo structure. */
    uint32_t          clientMemFlag[IEM_MAX_CLIENTS];
    /**< Flags for each instance to indicate whether it is free or allocated. */
    BspUtils_Node     nodePool[IEM_MAX_CLIENTS];
    /**< Pool of memory for the node. */
    BspOsal_SemHandle lockSem;
    /**< Semaphore handle. */
    uint32_t          baseAddress[IEM_MODULE_ISS_MAX];
    /**< Base Addresses for different modules */
} issemCommonObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t IssemFillClientInfo(issemClientInfo_t *clientInfo,
                                   issemEventGroup_t  eventGroup,
                                   const uint32_t    *event,
                                   uint32_t           numEvents,
                                   issemPriority_t    priority,
                                   issemClientCbFxn   callback,
                                   void              *arg);

static void IssemDeleteClientInfo(const issemClientInfo_t *clientInfo);

static issemClientInfo_t *IssemCreateClientInfo(BspUtils_Node **node);

static void IssemDeleteNode(const BspUtils_Node *emNode);

static void IssemAddNode(BspUtils_Node *newNode, issemPriority_t priority);

static void IssemMasterIsr(uint32_t arg);

static issemInstObj_t *IemGetInstObj(issemInstId_t instId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  \brief Global Instance objects
 */
static issemInstObj_t   gIemInstObj[IEM_MAX_INST] = {{FALSE},                   \
                                                     {FALSE}, {FALSE}, {FALSE}, \
                                                     {FALSE}, {FALSE}};

/**
 *  \brief Global Common object
 */
static issemCommonObj_t gIemCommonObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief Initializes the ISS Event Manager. It marks all the client info
 *  instances in the memory as available and register interrupt handler
 */
int32_t Vps_iemInit(const issemInitParams_t *initPrms)
{
    int32_t         retVal = BSP_SOK;
    uint32_t        cnt;
    uint32_t        instCnt;
    issemInstObj_t *instObj;

    /* Check for errors */
    GT_assert(VpsVemTrace, (NULL != initPrms));
    GT_assert(VpsVemTrace, (initPrms->numIrq <= IEM_MAX_INST));
    GT_assert(VpsVemTrace, (initPrms->numBaseAddress <= IEM_MODULE_ISS_MAX));

    if (FALSE == gIemInstObj[0U].isInitDone)
    {
        /* Init objects and mark flags as free */
        BspUtils_memset(gIemInstObj, 0, sizeof (gIemInstObj));
        BspUtils_memset(&gIemCommonObj, 0, sizeof (gIemCommonObj));
        for (instCnt = 0U; instCnt < IEM_MAX_INST; instCnt++)
        {
            gIemInstObj[instCnt].instId = IEM_INST_ID_MAX;
            BspUtils_initTsPrfLog(&gIemInstObj[instCnt].isrPrfLog);
        }
        for (cnt = 0U; cnt < IEM_MAX_CLIENTS; cnt++)
        {
            gIemCommonObj.clientMemFlag[cnt] = IEM_MEM_FLAG_FREE;
        }

        /* Initialise the semaphore parameters and create Pool Semaphore */
        gIemCommonObj.lockSem = BspOsal_semCreate((int32_t) 1, TRUE);
/* C & C++ INVARIANT_CONDITION.GEN
 * Expression '(NULL == gIemCommonObj.lockSem)' used in the condition
 * always yields the same result.
 * Name if (NULL == gIemCommonObj.lockSem)
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable.
 */
        if (NULL == gIemCommonObj.lockSem)
        {
            retVal = BSP_EALLOC;
/* MISRA.UNREACH.GEN
 * Un Reachable code
 * Name 'retVal = BSP_EALLOC;'
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable
 */
        }

/* C & C++ INVARIANT_CONDITION.GEN
 * Expression '(BSP_SOK == retVal)' used in the condition
 * always yields the same result.
 * Name if (BSP_SOK == retVal)
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable.
 */
        if (BSP_SOK == retVal)
        {
            for (cnt = 0U; cnt < initPrms->numBaseAddress; cnt++)
            {
                gIemCommonObj.baseAddress[cnt] = initPrms->baseAddress[cnt];
            }

            for (instCnt = 0U; instCnt < initPrms->numIrq; instCnt++)
            {
                /* Initialize instance object members */
                instObj             = &gIemInstObj[instCnt];
                instObj->instId     = initPrms->instId[instCnt];
                instObj->irqNumber  = initPrms->irqNum[instCnt];
                instObj->isInitDone = (uint32_t) TRUE;

                /* Clear out any pending interrupts */
                BspOsal_clearIntr(instObj->irqNumber);

                instObj->headNode = NULL;
                instObj->numIntr  = 0U;

                instObj->eoiAddr =
                    gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS1] +
                    ISS_HL_IRQ_EOI;

                /* ----------------- Register ISR --------------- */
                instObj->intrHandle = BspOsal_registerIntr(
                    instObj->irqNumber,
                    (BspOsal_IntrFuncPtr) & IssemMasterIsr,
                    instObj);
                if (NULL == instObj->intrHandle)
                {
                    GT_1trace(VpsVemTrace, GT_ERR,
                              "%s: Cannot Register IRQ", __FUNCTION__);
                    retVal = BSP_EALLOC;
                    break;
                }
            }
        }

        if (retVal != BSP_SOK)
        {
            Vps_iemDeInit();
        }
    }
    return (retVal);
}

/**
 *  \brief De-Initializes event Manager. It deletes semaphore and un-registers
 *  the IRQ handle and removes all the client info instance from the linked
 *  list.
 */
int32_t Vps_iemDeInit(void)
{
    uint32_t        instCnt;
    issemInstObj_t *instObj;
    BspUtils_Node  *tempNode;
    BspUtils_Node  *emNode;

    for (instCnt = 0U; instCnt < IEM_MAX_INST; instCnt++)
    {
        instObj = &gIemInstObj[instCnt];

        instObj->isInitDone = (uint32_t) FALSE;

        if (instObj->intrHandle != NULL)
        {
            /* ------------- Un-register ISR ------------- */
            BspOsal_unRegisterIntr(&instObj->intrHandle);
            instObj->intrHandle = NULL;
        }

        /* Free Entire Linked List */
        tempNode = instObj->headNode;
        while (NULL != tempNode)
        {
            emNode   = tempNode;
            tempNode = tempNode->next;
            IssemDeleteClientInfo((issemClientInfo_t *) emNode->data);
            IssemDeleteNode(emNode);
        }
    }

    if (gIemCommonObj.lockSem != NULL)
    {
        BspOsal_semDelete(&(gIemCommonObj.lockSem));
        gIemCommonObj.lockSem = NULL;
    }

    return (BSP_SOK);
}

/**
 *  \brief This function is used to register call back function for a specific
 *  event. It takes group number and event number within the group as the
 *  argument and returns handle.
 */
void *Vps_iemregister(issemInstId_t     instId,
                      issemEventGroup_t eventGroup,
                      const uint32_t   *event,
                      uint32_t          numEvents,
                      issemPriority_t   priority,
                      issemClientCbFxn  callback,
                      void             *arg)
{
    int32_t status = BSP_SOK;
    issemInstObj_t    *instObj;
    BspUtils_Node     *newNode    = NULL;
    issemClientInfo_t *clientInfo = NULL;

    /* Check for the error conditions */
    GT_assert(VpsVemTrace, (NULL != event));
    GT_assert(VpsVemTrace, (0U != numEvents));
    GT_assert(VpsVemTrace, (NULL != callback));

    instObj = IemGetInstObj(instId);
    GT_assert(VpsVemTrace, (NULL != instObj));

    if (TRUE != instObj->isInitDone)
    {
        status = BSP_EBADARGS;
    }

    if (BSP_SOK == status)
    {
        BspOsal_semWait(gIemCommonObj.lockSem, BSP_OSAL_WAIT_FOREVER);

        /* Allocate memory for the client info structure */
        clientInfo = IssemCreateClientInfo(&newNode);

        if ((NULL != clientInfo) && (NULL != newNode))
        {
            newNode->data = (void *) clientInfo;

            clientInfo->instObj = instObj;
            clientInfo->numIntr = 0U;

            /* Fill up the details about events in the client info structure */
            IssemFillClientInfo(
                clientInfo,
                eventGroup,
                event,
                numEvents,
                priority,
                callback,
                arg);

            /* Add the node in the linked list as per the priority */
            IssemAddNode(newNode, priority);
        }

        BspOsal_semPost(gIemCommonObj.lockSem);
    }

    return ((void *) newNode);
}

/**
 *  \brief  Function to un-register callback from the event manager. It removes
 *          node from the linked list and frees up memory allocated to the node
 *          and client info structure. It takes handle to the callback and
 *          returns status of the whether callback is removed.
 *          must be valid handle to the callback already registered
 */
int32_t Vps_iemUnRegister(void *handle)
{
    uint32_t           found = FALSE;
    uint32_t           cnt, regAddr, event, regVal;
    uint32_t           moduleIdx, calIrqNum, calEvent;
    issemEventGroup_t  eventGroup;
    issemInstObj_t    *instObj    = NULL;
    BspUtils_Node     *tempNode   = NULL;
    BspUtils_Node     *emNode     = NULL;
    issemClientInfo_t *clientInfo = NULL;

    /* Error condition Checking */
    GT_assert(VpsVemTrace, (NULL != handle));
    tempNode = (BspUtils_Node *) handle;
    GT_assert(VpsVemTrace, (NULL != tempNode->data));
    instObj = ((issemClientInfo_t *) (tempNode->data))->instObj;
    GT_assert(VpsVemTrace, (NULL != instObj));

    /* Check to see if the node given is in the linked list */
    emNode = instObj->headNode;
    GT_assert(VpsVemTrace, (NULL != emNode));

    found = (uint32_t) FALSE;
    while (NULL != emNode)
    {
        if (tempNode == emNode)
        {
            found = (uint32_t) TRUE;
            break;
        }
        emNode = emNode->next;
    }
    GT_assert(VpsVemTrace, (FALSE != found));

    clientInfo = (issemClientInfo_t *) tempNode->data;
    GT_assert(VpsVemTrace, (NULL != clientInfo));

    BspOsal_semWait(gIemCommonObj.lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Delete the Node */
    IssemDeleteNode(tempNode);

    /* Disable events in the VPS registers */
    eventGroup = clientInfo->eventGroup;
    for (cnt = 0U; cnt < clientInfo->numEvents; cnt++)
    {
        event = clientInfo->allEvents[cnt];

        if (IEM_EG_ISP3 >= eventGroup)
        {
            /* Disable the interrupt first */
            regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS1] +
                      ISP5_IRQENABLE_CLR(0U);
            regAddr = regAddr +
                      ((ISP5_IRQENABLE_CLR(1U) - ISP5_IRQENABLE_CLR(0U)) *
                       (eventGroup - IEM_EG_ISP0));
            HW_WR_REG32(regAddr, ((uint32_t) 1 << event));

            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);
        }
        else if ((IEM_EG_SIMCOP0 <= eventGroup) &&
                 (IEM_EG_SIMCOP3 >= eventGroup))
        {
            /* Disable the interrupt first */
            regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS_SIMCOP] +
                      SIMCOP_HL_IRQENABLE_CLR(0U);
            regAddr = regAddr +
                      ((SIMCOP_HL_IRQENABLE_CLR(1U) -
                        SIMCOP_HL_IRQENABLE_CLR(0U)) *
                       (eventGroup - IEM_EG_SIMCOP0));
            HW_WR_REG32(regAddr, ((uint32_t) 1 << event));

            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);
        }
        else if ((IEM_EG_LVDSRX0 <= eventGroup) &&
                 (IEM_EG_LVDSRX3 >= eventGroup))
        {
            /* Disable the interrupts at the SIMCOP level */
            regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS_LVDSRX] +
                      LVDSRX_IRQENABLE_CLR_0;
            regAddr = regAddr +
                      ((LVDSRX_IRQENABLE_CLR_1 -
                        LVDSRX_IRQENABLE_CLR_0) *
                       (eventGroup - IEM_EG_LVDSRX0));
            HW_WR_REG32(regAddr, ((uint32_t) 1 << event));

            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);
        }
        else if ((IEM_EG_CAL_A == eventGroup) ||
                 (IEM_EG_CAL_B == eventGroup))
        {
            if (IEM_EG_CAL_A == eventGroup)
            {
                moduleIdx = IEM_MODULE_ISS_CAL_A;
            }
            else
            {
                moduleIdx = IEM_MODULE_ISS_CAL_B;
            }

            if (IEM_CAL_EVENT_LL_SOF4 <= event)
            {
                calIrqNum = 4U;
                calEvent  = event - IEM_CAL_EVENT_LL_SOF4;
            }
            else if (IEM_CAL_EVENT_LL_SOF0 <= event)
            {
                calIrqNum = 3U;
                calEvent  = event - IEM_CAL_EVENT_LL_SOF0;
            }
            else if (IEM_CAL_EVENT_WDMA_START0 <= event)
            {
                calIrqNum = 2U;
                calEvent  = event - IEM_CAL_EVENT_WDMA_START0;
            }
            else if (IEM_CAL_EVENT_WDMA_END0 <= event)
            {
                calIrqNum = 1U;
                calEvent  = event - IEM_CAL_EVENT_WDMA_END0;
            }
            else
            {
                calIrqNum = 0U;
                calEvent  = event;
            }

            /* Disable the interrupts at the CAL level */
            regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                      CAL_HL_IRQENABLE_CLR(calIrqNum);
            HW_WR_REG32(regAddr, ((uint32_t) 1 << calEvent));

            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);
        }
        else if (IEM_EG_CAL_A_CSI2 == eventGroup)
        {
            moduleIdx = IEM_MODULE_ISS_CAL_A;
            if (VPS_CAL_CSI2_PPI_CMPLXIO_RSERVED_31 > event)
            {
                calEvent = IEM_CAL_EVENT_PPIO;
                /* Disable the interrupts at the CAL level */
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_HL_IRQENABLE_CLR(0U);
                HW_WR_REG32(regAddr, ((uint32_t) 1 << calEvent));

                /* Clear the status of the interrupt */
                HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                            clientInfo->mask[cnt][1U]);
                clientInfo->isThirdLevelReq[cnt] = FALSE;

                /* Disable the interrupt and clear status */
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_CSI2_COMPLEXIO_IRQENABLE(0U);
                regVal  = HW_RD_REG32(regAddr);
                regVal &= ~((uint32_t) 1 << event);
                HW_WR_REG32(regAddr, regVal);

                regAddr = clientInfo->statusReg[cnt][2U];
                regVal  = clientInfo->mask[cnt][2U];
                HW_WR_REG32(regAddr, regVal);

            }
            else if ((VPS_CAL_CSI2_PPI_VC_SOF1 <= event) &&
                   (VPS_CAL_CSI2_PPI_VC_RESERVED_31 > event))
            {

                calEvent = IEM_CAL_EVENT_PPIO_VC;
                /* Disable the interrupts at the CAL level */
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_HL_IRQENABLE_CLR(0U);
                HW_WR_REG32(regAddr, ((uint32_t) 1 << calEvent));

                /* Clear the status of the interrupt */
                HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                            clientInfo->mask[cnt][1U]);
                clientInfo->isThirdLevelReq[cnt] = FALSE;

                calEvent = event - VPS_CAL_CSI2_PPI_VC_SOF1;

                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_CSI2_VC_IRQENABLE(0U);
                regVal  = HW_RD_REG32(regAddr);
                regVal &= ~((uint32_t) 1 << calEvent);
                HW_WR_REG32(regAddr, regVal);

                regAddr = clientInfo->statusReg[cnt][2U];
                regVal  = clientInfo->mask[cnt][2U];
                HW_WR_REG32(regAddr, regVal);
            }
            else
            {
                GT_assert(VpsVemTrace, FALSE);
            }
        }
        else
        {
            GT_assert(VpsVemTrace, FALSE);
        }

        clientInfo->statusReg[cnt][0U]    = 0x0U;
        clientInfo->statusClrReg[cnt][0U] = 0x0U;
        clientInfo->mask[cnt][0U]         = 0x0U;
        clientInfo->statusReg[cnt][1U]    = 0x0U;
        clientInfo->statusClrReg[cnt][1U] = 0x0U;
        clientInfo->mask[cnt][1U]         = 0x0U;

        clientInfo->subModuleEoiAddr[cnt] = 0x0U;
        clientInfo->subModuleEoiLine[cnt] = 0x0U;
        clientInfo->isThirdLevelReq[cnt]  = FALSE;
    }

    clientInfo->clientCb  = NULL;
    clientInfo->arg       = NULL;
    clientInfo->instObj   = NULL;
    clientInfo->numEvents = 0;

    /* Free up memory allocated to event arrays and clientInfo structure */
    IssemDeleteClientInfo(clientInfo);

    BspOsal_semPost(gIemCommonObj.lockSem);

    return (BSP_SOK);
}

int32_t Vps_iemDisable(void *handle)
{
    uint32_t           found = FALSE;
    uint32_t           cnt, regAddr, regVal;
    uint32_t           eventGroup, event;
    uint32_t           moduleIdx, calIrqNum, calEvent;
    issemInstObj_t    *instObj    = NULL;
    BspUtils_Node     *tempNode   = NULL;
    BspUtils_Node     *emNode     = NULL;
    issemClientInfo_t *clientInfo = NULL;

    /* Error condition Checking */
    GT_assert(VpsVemTrace, (NULL != handle));
    tempNode = (BspUtils_Node *) handle;
    GT_assert(VpsVemTrace, (NULL != tempNode->data));
    instObj = ((issemClientInfo_t *) (tempNode->data))->instObj;
    GT_assert(VpsVemTrace, (NULL != instObj));

    /* Check to see if the node given is in the linked list */
    emNode = instObj->headNode;
    GT_assert(VpsVemTrace, (NULL != emNode));

    found = (uint32_t) FALSE;
    while (NULL != emNode)
    {
        if (tempNode == emNode)
        {
            found = (uint32_t) TRUE;
            break;
        }
        emNode = emNode->next;
    }
    GT_assert(VpsVemTrace, (FALSE != found));

    clientInfo = (issemClientInfo_t *) tempNode->data;
    GT_assert(VpsVemTrace, (NULL != clientInfo));

    BspOsal_semWait(gIemCommonObj.lockSem, BSP_OSAL_WAIT_FOREVER);

    eventGroup = (uint32_t) (clientInfo->eventGroup);
    for (cnt = 0U; cnt < clientInfo->numEvents; cnt++)
    {
        event = clientInfo->allEvents[cnt];

        if (IEM_EG_ISP3 >= eventGroup)
        {
            /* Disable the interrupt first */
            regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS1] +
                      ISP5_IRQENABLE_CLR(0U);
            regAddr = regAddr +
                      ((ISP5_IRQENABLE_CLR(1U) - ISP5_IRQENABLE_CLR(0U)) *
                       (eventGroup - IEM_EG_ISP0));
            HW_WR_REG32(regAddr, ((uint32_t) 1 << event));

            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);
        }
        else if ((IEM_EG_SIMCOP0 <= eventGroup) &&
                 (IEM_EG_SIMCOP3 >= eventGroup))
        {
            /* Disable the interrupt first */
            regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS_SIMCOP] +
                      SIMCOP_HL_IRQENABLE_CLR(0U);
            regAddr = regAddr +
                      ((SIMCOP_HL_IRQENABLE_CLR(1U) -
                        SIMCOP_HL_IRQENABLE_CLR(0U)) *
                       (eventGroup - IEM_EG_SIMCOP0));
            HW_WR_REG32(regAddr, ((uint32_t) 1 << event));

            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);
        }
        else if ((IEM_EG_LVDSRX0 <= eventGroup) &&
                 (IEM_EG_LVDSRX3 >= eventGroup))
        {
            /* Disable the interrupts at the SIMCOP level */
            regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS_LVDSRX] +
                      LVDSRX_IRQENABLE_CLR_0;
            regAddr = regAddr +
                      ((LVDSRX_IRQENABLE_CLR_1 -
                        LVDSRX_IRQENABLE_CLR_0) *
                       (eventGroup - IEM_EG_LVDSRX0));
            HW_WR_REG32(regAddr, ((uint32_t) 1 << event));

            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);
        }
        else if ((IEM_EG_CAL_A == eventGroup) ||
                 (IEM_EG_CAL_B == eventGroup))
        {
            if (IEM_EG_CAL_A == eventGroup)
            {
                moduleIdx = IEM_MODULE_ISS_CAL_A;
            }
            else
            {
                moduleIdx = IEM_MODULE_ISS_CAL_B;
            }

            if (IEM_CAL_EVENT_LL_SOF4 <= event)
            {
                calIrqNum = 4U;
                calEvent  = event - IEM_CAL_EVENT_LL_SOF4;
            }
            else if (IEM_CAL_EVENT_LL_SOF0 <= event)
            {
                calIrqNum = 3U;
                calEvent  = event - IEM_CAL_EVENT_LL_SOF0;
            }
            else if (IEM_CAL_EVENT_WDMA_START0 <= event)
            {
                calIrqNum = 2U;
                calEvent  = event - IEM_CAL_EVENT_WDMA_START0;
            }
            else if (IEM_CAL_EVENT_WDMA_END0 <= event)
            {
                calIrqNum = 1U;
                calEvent  = event - IEM_CAL_EVENT_WDMA_END0;
            }
            else
            {
                calIrqNum = 0U;
                calEvent  = event;
            }

            /* Disable the interrupts at the CAL level */
            regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                      CAL_HL_IRQENABLE_CLR(calIrqNum);
            HW_WR_REG32(regAddr, ((uint32_t) 1 << calEvent));

            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);
        }
        else if (IEM_EG_CAL_A_CSI2 == eventGroup)
        {
            /* Disable the event at the CAL TOP */
            moduleIdx = IEM_MODULE_ISS_CAL_A;
            if (VPS_CAL_CSI2_PPI_CMPLXIO_RSERVED_31 > event)
            {
                calEvent = IEM_CAL_EVENT_PPIO;
                /* Disable the interrupts at the CAL level */
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_HL_IRQENABLE_CLR(0U);
                HW_WR_REG32(regAddr, ((uint32_t) 1 << calEvent));

                /* Clear the status of the interrupt */
                HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                            clientInfo->mask[cnt][1U]);

                /* Disable the interrupt and clear status */
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_CSI2_COMPLEXIO_IRQENABLE(0U);
                regVal  = HW_RD_REG32(regAddr);
                regVal &= ~((uint32_t) 1 << event);
                HW_WR_REG32(regAddr, regVal);

                regAddr = clientInfo->statusReg[cnt][2U];
                regVal  = clientInfo->mask[cnt][2U];
                HW_WR_REG32(regAddr, regVal);

            }
            else if ((VPS_CAL_CSI2_PPI_VC_SOF1 <= event) &&
                     (VPS_CAL_CSI2_PPI_VC_RESERVED_31 > event))
            {
                calEvent = IEM_CAL_EVENT_PPIO_VC;
                /* Disable the interrupts at the CAL level */
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_HL_IRQENABLE_CLR(0U);
                HW_WR_REG32(regAddr, ((uint32_t) 1 << calEvent));

                /* Clear the status of the interrupt */
                HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                            clientInfo->mask[cnt][1U]);

                calEvent = event - VPS_CAL_CSI2_PPI_VC_SOF1;
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_CSI2_VC_IRQENABLE(0U);
                regVal  = HW_RD_REG32(regAddr);
                regVal &= ~((uint32_t) 1 << calEvent);
                HW_WR_REG32(regAddr, regVal);

                regAddr = clientInfo->statusReg[cnt][2U];
                regVal  = clientInfo->mask[cnt][2U];
                HW_WR_REG32(regAddr, regVal);
            }
            else
            {
                GT_assert(VpsVemTrace, FALSE);
            }
        }
        else
        {
            GT_assert(VpsVemTrace, FALSE);
        }
    }

    BspOsal_semPost(gIemCommonObj.lockSem);

    return (BSP_SOK);
}

int32_t Vps_iemEnable(void *handle)
{
    uint32_t           found = FALSE;
    uint32_t           cnt, regAddr, regVal;
    uint32_t           eventGroup, event;
    uint32_t           moduleIdx, calIrqNum, calEvent;
    issemInstObj_t    *instObj    = NULL;
    BspUtils_Node     *tempNode   = NULL;
    BspUtils_Node     *emNode     = NULL;
    issemClientInfo_t *clientInfo = NULL;

    /* Error condition Checking */
    GT_assert(VpsVemTrace, (NULL != handle));
    tempNode = (BspUtils_Node *) handle;
    GT_assert(VpsVemTrace, (NULL != tempNode->data));
    instObj = ((issemClientInfo_t *) (tempNode->data))->instObj;
    GT_assert(VpsVemTrace, (NULL != instObj));

    /* Check to see if the node given is in the linked list */
    emNode = instObj->headNode;
    GT_assert(VpsVemTrace, (NULL != emNode));

    found = (uint32_t) FALSE;
    while (NULL != emNode)
    {
        if (tempNode == emNode)
        {
            found = (uint32_t) TRUE;
            break;
        }
        emNode = emNode->next;
    }
    GT_assert(VpsVemTrace, (FALSE != found));

    clientInfo = (issemClientInfo_t *) tempNode->data;
    GT_assert(VpsVemTrace, (NULL != clientInfo));

    BspOsal_semWait(gIemCommonObj.lockSem, BSP_OSAL_WAIT_FOREVER);

    eventGroup = (uint32_t) (clientInfo->eventGroup);
    for (cnt = 0U; cnt < clientInfo->numEvents; cnt++)
    {
        event = clientInfo->allEvents[cnt];

        if (IEM_EG_ISP3 >= eventGroup)
        {
            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);

            /* Enable the interrupt first */
            regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS1] +
                      ISP5_IRQENABLE_SET(0U);
            regAddr = regAddr +
                      ((ISP5_IRQENABLE_SET(1U) - ISP5_IRQENABLE_SET(0U)) *
                       (eventGroup - IEM_EG_ISP0));
            HW_WR_REG32(regAddr, ((uint32_t) 1 << event));
        }
        else if ((IEM_EG_SIMCOP0 <= eventGroup) &&
                 (IEM_EG_SIMCOP3 >= eventGroup))
        {
            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);

            /* Enable the interrupt first */
            regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS_SIMCOP] +
                      SIMCOP_HL_IRQENABLE_SET(0U);
            regAddr = regAddr +
                      ((SIMCOP_HL_IRQENABLE_SET(1U) -
                        SIMCOP_HL_IRQENABLE_SET(0U)) *
                       (eventGroup - IEM_EG_SIMCOP0));
            HW_WR_REG32(regAddr, ((uint32_t) 1 << event));
        }
        else if ((IEM_EG_LVDSRX0 <= eventGroup) &&
                 (IEM_EG_LVDSRX3 >= eventGroup))
        {
            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);

            /* Enable the interrupts at the SIMCOP level */
            regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS_LVDSRX] +
                      LVDSRX_IRQENABLE_SET_0;
            regAddr = regAddr +
                      ((LVDSRX_IRQENABLE_SET_1 -
                        LVDSRX_IRQENABLE_SET_0) *
                       (eventGroup - IEM_EG_LVDSRX0));
            HW_WR_REG32(regAddr, ((uint32_t) 1 << event));
        }
        else if ((IEM_EG_CAL_A == eventGroup) ||
                 (IEM_EG_CAL_B == eventGroup))
        {
            if (IEM_EG_CAL_A == eventGroup)
            {
                moduleIdx = IEM_MODULE_ISS_CAL_A;
            }
            else
            {
                moduleIdx = IEM_MODULE_ISS_CAL_B;
            }

            if (IEM_CAL_EVENT_LL_SOF4 <= event)
            {
                calIrqNum = 4U;
                calEvent  = event - IEM_CAL_EVENT_LL_SOF4;
            }
            else if (IEM_CAL_EVENT_LL_SOF0 <= event)
            {
                calIrqNum = 3U;
                calEvent  = event - IEM_CAL_EVENT_LL_SOF0;
            }
            else if (IEM_CAL_EVENT_WDMA_START0 <= event)
            {
                calIrqNum = 2U;
                calEvent  = event - IEM_CAL_EVENT_WDMA_START0;
            }
            else if (IEM_CAL_EVENT_WDMA_END0 <= event)
            {
                calIrqNum = 1U;
                calEvent  = event - IEM_CAL_EVENT_WDMA_END0;
            }
            else
            {
                calIrqNum = 0U;
                calEvent  = event;
            }
            /* Enable the interrupts at the CAL level */
            regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                      CAL_HL_IRQENABLE_SET(calIrqNum);

            /* Clear the status of the interrupt */
            HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                        clientInfo->mask[cnt][1U]);

            HW_WR_REG32(regAddr, ((uint32_t) 1 << calEvent));
        }
        else if (IEM_EG_CAL_A_CSI2 == eventGroup)
        {
            /* Disable the event at the CAL TOP */
            moduleIdx = IEM_MODULE_ISS_CAL_A;
            if (VPS_CAL_CSI2_PPI_CMPLXIO_RSERVED_31 > event)
            {
                calEvent = IEM_CAL_EVENT_PPIO;
                /* Disable the interrupts at the CAL level */
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_HL_IRQENABLE_SET(0U);
                HW_WR_REG32(regAddr, ((uint32_t) 1 << calEvent));

                /* Clear the status of the interrupt */
                HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                            clientInfo->mask[cnt][1U]);

                /* Disable the interrupt and clear status */
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_CSI2_COMPLEXIO_IRQENABLE(0U);
                regVal  = HW_RD_REG32(regAddr);
                regVal |= ((uint32_t) 1 << event);
                HW_WR_REG32(regAddr, regVal);

                regAddr = clientInfo->statusReg[cnt][2U];
                regVal  = clientInfo->mask[cnt][2U];
                HW_WR_REG32(regAddr, regVal);
            }
            else if ((VPS_CAL_CSI2_PPI_VC_SOF1 <= event) &&
                     (VPS_CAL_CSI2_PPI_VC_RESERVED_31 > event))
            {
                calEvent = IEM_CAL_EVENT_PPIO_VC;
                /* Disable the interrupts at the CAL level */
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_HL_IRQENABLE_SET(0U);
                HW_WR_REG32(regAddr, ((uint32_t) 1 << calEvent));

                /* Clear the status of the interrupt */
                HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                            clientInfo->mask[cnt][1U]);

                calEvent = event - VPS_CAL_CSI2_PPI_VC_SOF1;

                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_CSI2_VC_IRQENABLE(0U);
                regVal  = HW_RD_REG32(regAddr);
                regVal |= ((uint32_t) 1 << calEvent);
                HW_WR_REG32(regAddr, regVal);

                regAddr = clientInfo->statusReg[cnt][2U];
                regVal  = clientInfo->mask[cnt][2U];
                HW_WR_REG32(regAddr, regVal);
            }
            else
            {
                GT_assert(VpsVemTrace, FALSE);
            }
        }
        else
        {
            GT_assert(VpsVemTrace, FALSE);
        }
    }

    BspOsal_semPost(gIemCommonObj.lockSem);

    return (BSP_SOK);
}

int32_t Iem_disableAll(void *handle)
{
    return (BSP_SOK);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* Sujith : Handle interrupts which are not know. Call the CB provided during
    create/init */
static void IssemMasterIsr(uint32_t arg)
{
    uint32_t           cnt;
    uint32_t           regVal, numEvents;
    uint32_t           numClients = 0;
    BspUtils_Node     *tempNode;
    issemClientInfo_t *clientInfo = NULL;
    issemInstObj_t    *instObj;
    Bool               isThirdLevelValid = FALSE;
    instObj  = (issemInstObj_t *) arg;
    tempNode = instObj->headNode;

    BspUtils_startTsPrfLog(&instObj->isrPrfLog);

    /* Traverse through the entire list of registered clients and
     * clear the top level interrupts */
    tempNode = instObj->headNode;
    while (NULL != tempNode)
    {
        clientInfo = (issemClientInfo_t *) tempNode->data;
        GT_assert(VpsVemTrace, (NULL != clientInfo));

        for (cnt = 0; cnt < clientInfo->numEvents; cnt++)
        {
            regVal = HW_RD_REG32(clientInfo->statusReg[cnt][0U]);
            if (clientInfo->mask[cnt][0U] ==
                (clientInfo->mask[cnt][0U] & regVal))
            {
                HW_WR_REG32(clientInfo->statusClrReg[cnt][0U],
                            clientInfo->mask[cnt][0U]);
            }
        }

        /* Move to the next client */
        tempNode = tempNode->next;
    }

    /* Traverse through the entire list of registered clients */
    tempNode = instObj->headNode;
    while (NULL != tempNode)
    {
        isThirdLevelValid = FALSE;
        numEvents  = 0U;
        clientInfo = (issemClientInfo_t *) tempNode->data;
        GT_assert(VpsVemTrace, (NULL != clientInfo));

        for (cnt = 0; cnt < clientInfo->numEvents; cnt++)
        {
            /* See if any of registered events has occurred */
            regVal = HW_RD_REG32(clientInfo->statusReg[cnt][1U]);
            if ((uint32_t) 0 != (regVal & (clientInfo->mask[cnt][1U])))
            {
                /* Make an array of events which has occurred. */
                clientInfo->setEvents[numEvents] =
                    clientInfo->allEvents[cnt];
                numEvents++;
                /* Clear the status and call the callback */
                HW_WR_REG32(clientInfo->statusClrReg[cnt][1U],
                            clientInfo->mask[cnt][1U]);

                /* TODO: Check if this can be done early here or
                 *       is it really required to clear eoi at submodule
                 *      level
                 */
                if (FALSE == clientInfo->isThirdLevelReq[cnt])
                {
                    HW_WR_REG32(clientInfo->subModuleEoiAddr[cnt],
                                clientInfo->subModuleEoiLine[cnt]);
                }
                else
                {
                    /* Third level of interrupt handling */
                    isThirdLevelValid = TRUE;
                    numEvents--;
                    break;
                }
            }
        }

        if (TRUE == isThirdLevelValid)
        {
            /* Level 2 events is cleared, handle 3rd level events */
            for (; cnt < clientInfo->numEvents; cnt++)
            {
                regVal = HW_RD_REG32(clientInfo->statusReg[cnt][2U]);
                if ((uint32_t) 0 != (regVal & (clientInfo->mask[cnt][2U])))
                {
                    clientInfo->setEvents[numEvents] =
                        clientInfo->allEvents[cnt];
                    numEvents++;
                    HW_WR_REG32(clientInfo->statusClrReg[cnt][2U],
                                clientInfo->mask[cnt][2U]);
                }
            }
        }

        /* Call callback if any event occurs for the client */
        if (0U != numEvents)
        {
            clientInfo->clientCb(
                clientInfo->setEvents,
                numEvents,
                clientInfo->arg);

            /* Increment total number of interrupts */
            clientInfo->numIntr++;

            numClients++;
        }

        /* Move to next client */
        tempNode = tempNode->next;
    }

    HW_WR_REG32(instObj->eoiAddr, instObj->instId);

    /* Increment total number of interrupts */
    instObj->numIntr++;

    BspUtils_endTsPrfLog(&instObj->isrPrfLog);

    return;
}

/**
 *  \brief Function to allocate memory for the client information structure
 *  and other arrays.
 */
static issemClientInfo_t *IssemCreateClientInfo(BspUtils_Node **node)
{
    uint32_t           cnt;
    issemClientInfo_t *clientInfo = NULL;

    for (cnt = 0U; cnt < IEM_MAX_CLIENTS; cnt++)
    {
        if (IEM_MEM_FLAG_FREE == gIemCommonObj.clientMemFlag[cnt])
        {
            clientInfo = &(gIemCommonObj.clientMemPool[cnt]);
            *node      = &gIemCommonObj.nodePool[cnt];
            gIemCommonObj.clientMemFlag[cnt] = IEM_MEM_FLAG_ALLOC;
            break;
        }
    }

    return (clientInfo);
}

/**
 *  \brief Function to free up memory for the client information structure
 *  and other arrays.
 */
static void IssemDeleteClientInfo(const issemClientInfo_t *clientInfo)
{
    uint32_t cnt;

    GT_assert(VpsVemTrace, (NULL != clientInfo));

    for (cnt = 0U; cnt < IEM_MAX_CLIENTS; cnt++)
    {
        if (clientInfo == &(gIemCommonObj.clientMemPool[cnt]))
        {
            gIemCommonObj.clientMemFlag[cnt] = IEM_MEM_FLAG_FREE;
            break;
        }
    }

    return;
}

/**
 *  \brief Function to add a node to the linked list of clients at the
 *  appropriate position as per the given priority.
 */
static void IssemAddNode(BspUtils_Node *newNode, issemPriority_t priority)
{
    issemInstObj_t *instObj = NULL;
    BspUtils_Node  *curr    = NULL;
    BspUtils_Node  *prev    = NULL;

    GT_assert(VpsVemTrace, (NULL != newNode));

    instObj = ((issemClientInfo_t *) (newNode->data))->instObj;
    GT_assert(VpsVemTrace, (NULL != instObj));

    newNode->prev = newNode->next = NULL;
    curr          = instObj->headNode;
    prev          = NULL;

    /* Search for place to insert new node as per priority */
    while ((NULL != curr) &&
           (((issemClientInfo_t *) curr->data)->priority < priority))
    {
        prev = curr;
        curr = curr->next;
    }

    /* Update pointers */
    newNode->next = curr;
    newNode->prev = prev;

    if (NULL == prev)
    {
        instObj->headNode = newNode;
    }
    else
    {
        prev->next = newNode;
    }

    if (NULL != curr)
    {
        curr->prev = newNode;
    }

    return;
}

/**
 *  \brief Function to remove the node from the linked list and delete memory
 *  allocated to it.
 */
static void IssemDeleteNode(const BspUtils_Node *emNode)
{
    issemInstObj_t *instObj = NULL;
    BspUtils_Node  *curr    = NULL;
    BspUtils_Node  *prev    = NULL;

    GT_assert(VpsVemTrace, (NULL != emNode));

    instObj = ((issemClientInfo_t *) (emNode->data))->instObj;
    prev    = emNode->prev;
    curr    = emNode->next;

    if (NULL != prev)
    {
        if (NULL != curr)
        {
            prev->next = curr;
        }
        else
        {
            prev->next = NULL;
        }
    }
    else
    {
        instObj->headNode = curr;
        if (NULL != instObj->headNode)
        {
            instObj->headNode->prev = NULL;
        }
    }
    if (NULL != curr)
    {
        curr->prev = prev;
    }

    return;
}

/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'event'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 *
 * In this particular case, the caller of this function (typically ISS Core)
 *  has allocated enough memory to hold at least numEvents
 */
static int32_t IssemFillClientInfo(issemClientInfo_t *clientInfo,
                                   issemEventGroup_t  eventGroup,
                                   const uint32_t    *event,
                                   uint32_t           numEvents,
                                   issemPriority_t    priority,
                                   issemClientCbFxn   callback,
                                   void              *arg)
{
    int32_t         status = BSP_SOK;
    uint32_t        cnt;
    uint32_t        regAddr, regVal;
    uint32_t        moduleIdx, calEvent, calIrqNum, ispEvent;
    issemEventGroup_t  correctedEventGrp;
    issemInstObj_t *instObj = NULL;

    GT_assert(VpsVemTrace, (NULL != clientInfo));
    GT_assert(VpsVemTrace, (NULL != event));
    GT_assert(VpsVemTrace, (NULL != callback));

    correctedEventGrp = eventGroup;
    clientInfo->eventGroup = eventGroup;
    clientInfo->numEvents  = numEvents;
    instObj = clientInfo->instObj;

    for (cnt = 0U; cnt < numEvents; cnt++)
    {
        if (IEM_EG_ISP3 >= eventGroup)
        {
            if ((0U == gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS1]) ||
                (0U == gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS2]))
            {
                status = BSP_EFAIL;
            }
        }
        else if ((IEM_EG_SIMCOP0 <= eventGroup) &&
                 (IEM_EG_SIMCOP3 >= eventGroup))
        {
            if (0U == gIemCommonObj.baseAddress[IEM_MODULE_ISS_SIMCOP])
            {
                status = BSP_EFAIL;
            }
        }
        else if ((IEM_EG_LVDSRX0 <= eventGroup) &&
                 (IEM_EG_LVDSRX3 >= eventGroup))
        {
            if (0U == gIemCommonObj.baseAddress[IEM_MODULE_ISS_LVDSRX])
            {
                status = BSP_EFAIL;
            }
        }
        else if (IEM_EG_CAL_A == eventGroup)
        {
            if (0U == gIemCommonObj.baseAddress[IEM_MODULE_ISS_CAL_A])
            {
                status = BSP_EFAIL;
            }
        }
        else if (IEM_EG_CAL_B == eventGroup)
        {
            if (0U == gIemCommonObj.baseAddress[IEM_MODULE_ISS_CAL_B])
            {
                status = BSP_EFAIL;
            }
        }
        else if (IEM_EG_CAL_A_CSI2 == eventGroup)
        {
            if (0U == gIemCommonObj.baseAddress[IEM_MODULE_ISS_CAL_A])
            {
                status = BSP_EFAIL;
            }
            else
            {
                correctedEventGrp = (issemEventGroup_t)
                                    (correctedEventGrp - IEM_EG_RESERVED_31);
            }
        }
        else
        {
            status = BSP_EFAIL;
        }

        if (status == BSP_EFAIL)
        {
            break;
        }
    }

    if (BSP_SOK == status)
    {
        for (cnt = 0U; cnt < numEvents; cnt++)
        {
            clientInfo->isThirdLevelReq[cnt] = FALSE;

            /* Enable Interrupt at the ISS top level */
            regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS] +
                      ISS_HL_IRQENABLE_SET(0U);
            regAddr = regAddr +
                      ((ISS_HL_IRQENABLE_SET(1U) - ISS_HL_IRQENABLE_SET(0U)) *
                       ((uint32_t) instObj->instId));
            regVal  = HW_RD_REG32(regAddr);
            regVal |= ((uint32_t) 1 << (correctedEventGrp));
            HW_WR_REG32(regAddr, regVal);

            /* Store the register address in clientInfo instance */
            regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS] +
                      ISS_HL_IRQSTATUS(0U);
            regAddr = regAddr +
                      ((ISS_HL_IRQSTATUS(1U) - ISS_HL_IRQSTATUS(0U)) *
                       ((uint32_t) instObj->instId));
            clientInfo->statusReg[cnt][0U]    = regAddr;
            clientInfo->statusClrReg[cnt][0U] = regAddr;
            clientInfo->mask[cnt][0U]         =
                                 ((uint32_t) 1U << ((uint32_t) correctedEventGrp));
            clientInfo->allEvents[cnt] = event[cnt];

            if (IEM_EG_ISP3 >= eventGroup)
            {
                if (event[cnt] <= 31U)
                {
                    /* Enable the interrupts at the ISP level */
                    regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS1] +
                              ISP5_IRQENABLE_SET(0U);
                    regAddr = regAddr +
                              ((ISP5_IRQENABLE_SET(1U) -
                                ISP5_IRQENABLE_SET(0U)) *
                               (eventGroup - IEM_EG_ISP0));
                    regVal  = HW_RD_REG32(regAddr);
                    regVal |= ((uint32_t) 1 << event[cnt]);
                    HW_WR_REG32(regAddr, regVal);

                    /* Store the register address in clientInfo instance */
                    regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS1] +
                              ISP5_IRQSTATUS(0U);
                    regAddr = regAddr +
                              ((ISP5_IRQSTATUS(1U) - ISP5_IRQSTATUS(0U)) *
                               (eventGroup - IEM_EG_ISP0));
                    clientInfo->statusReg[cnt][1U]    = regAddr;
                    clientInfo->statusClrReg[cnt][1U] = regAddr;
                    clientInfo->mask[cnt][1U]         =
                         ((uint32_t) 1U << event[cnt]);

                    clientInfo->subModuleEoiAddr[cnt] =
                        gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS1] +
                        ISP5_IRQ_EOI;
                    clientInfo->subModuleEoiLine[cnt] =
                        (eventGroup - IEM_EG_ISP0);
                }
                else
                {
                    ispEvent = event[cnt] - (uint32_t) 32;

                    /* Enable the interrupts at the ISP level */
                    regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS2] +
                              ISP5_IRQENABLE_SET2(0U);
                    regAddr = regAddr +
                              ((ISP5_IRQENABLE_SET2(1U) -
                                ISP5_IRQENABLE_SET2(0U)) *
                               (eventGroup - IEM_EG_ISP0));
                    regVal  = HW_RD_REG32(regAddr);
                    regVal |= ((uint32_t) 1 << ispEvent);
                    HW_WR_REG32(regAddr, regVal);

                    /* Store the register address in clientInfo instance */
                    regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS2] +
                              ISP5_IRQSTATUS2(0U);
                    regAddr = regAddr +
                              ((ISP5_IRQSTATUS2(1U) - ISP5_IRQSTATUS2(0U)) *
                               (eventGroup - IEM_EG_ISP0));
                    clientInfo->statusReg[cnt][1U]    = regAddr;
                    clientInfo->statusClrReg[cnt][1U] = regAddr;
                    clientInfo->mask[cnt][1U]         = ((uint32_t) 1U << ispEvent);

                    clientInfo->subModuleEoiAddr[cnt] =
                        gIemCommonObj.baseAddress[IEM_MODULE_ISP_SYS2] +
                        ISP5_IRQ_EOI;
                    clientInfo->subModuleEoiLine[cnt] =
                        (eventGroup - IEM_EG_ISP0);
                }
            }
            else if ((IEM_EG_SIMCOP0 <= eventGroup) &&
                     (IEM_EG_SIMCOP3 >= eventGroup))
            {
                /* Enable the interrupts at the SIMCOP level */
                regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS_SIMCOP] +
                          SIMCOP_HL_IRQENABLE_SET(0U);
                regAddr = regAddr +
                          ((SIMCOP_HL_IRQENABLE_SET(1U) -
                            SIMCOP_HL_IRQENABLE_SET(0U)) *
                           (eventGroup - IEM_EG_SIMCOP0));
                regVal  = HW_RD_REG32(regAddr);
                regVal |= ((uint32_t) 1 << event[cnt]);
                HW_WR_REG32(regAddr, regVal);

                /* Store the register address in clientInfo instance */
                regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS_SIMCOP] +
                          SIMCOP_HL_IRQSTATUS(0U);
                regAddr = regAddr +
                          ((SIMCOP_HL_IRQSTATUS(1U) -
                            SIMCOP_HL_IRQSTATUS(0U)) *
                           (eventGroup - IEM_EG_SIMCOP0));
                clientInfo->statusReg[cnt][1U]    = regAddr;
                clientInfo->statusClrReg[cnt][1U] = regAddr;
                clientInfo->mask[cnt][1U]         = ((uint32_t) 1U << event[cnt]);

                clientInfo->subModuleEoiAddr[cnt] =
                    gIemCommonObj.baseAddress[IEM_MODULE_ISS_SIMCOP] +
                    SIMCOP_HL_IRQ_EOI;
                clientInfo->subModuleEoiLine[cnt] = (eventGroup -
                                                     IEM_EG_SIMCOP0);
            }
            else if ((IEM_EG_LVDSRX0 <= eventGroup) &&
                     (IEM_EG_LVDSRX3 >= eventGroup))
            {
                /* Enable the interrupts at the SIMCOP level */
                regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS_LVDSRX] +
                          LVDSRX_IRQENABLE_SET_0;
                regAddr = regAddr +
                          ((LVDSRX_IRQENABLE_SET_1 -
                            LVDSRX_IRQENABLE_SET_0) *
                           (eventGroup - IEM_EG_LVDSRX0));
                regVal  = HW_RD_REG32(regAddr);
                regVal |= ((uint32_t) 1 << event[cnt]);
                HW_WR_REG32(regAddr, regVal);

                /* Store the register address in clientInfo instance */
                regAddr = gIemCommonObj.baseAddress[IEM_MODULE_ISS_LVDSRX] +
                          LVDSRX_IRQSTATUS_0;
                regAddr = regAddr +
                          ((LVDSRX_IRQSTATUS_1 - LVDSRX_IRQSTATUS_0) *
                           (eventGroup - IEM_EG_LVDSRX0));
                clientInfo->statusReg[cnt][1U]    = regAddr;
                clientInfo->statusClrReg[cnt][1U] = regAddr;
                clientInfo->mask[cnt][1U]         = ((uint32_t) 1U << event[cnt]);

                clientInfo->subModuleEoiAddr[cnt] =
                    gIemCommonObj.baseAddress[IEM_MODULE_ISS_LVDSRX] +
                    LVDSRX_IRQ_EOI;
                clientInfo->subModuleEoiLine[cnt] =
                    (eventGroup - IEM_EG_LVDSRX0);
            }
            else if ((IEM_EG_CAL_A == eventGroup) ||
                     (IEM_EG_CAL_B == eventGroup))
            {
                if (IEM_EG_CAL_A == eventGroup)
                {
                    moduleIdx = IEM_MODULE_ISS_CAL_A;
                }
                else
                {
                    moduleIdx = IEM_MODULE_ISS_CAL_B;
                }

                if (IEM_CAL_EVENT_LL_SOF4 <= event[cnt])
                {
                    calIrqNum = 4U;
                    calEvent  = event[cnt] - IEM_CAL_EVENT_LL_SOF4;
                }
                else if (IEM_CAL_EVENT_LL_SOF0 <= event[cnt])
                {
                    calIrqNum = 3U;
                    calEvent  = event[cnt] - IEM_CAL_EVENT_LL_SOF0;
                }
                else if (IEM_CAL_EVENT_WDMA_START0 <= event[cnt])
                {
                    calIrqNum = 2U;
                    calEvent  = event[cnt] - IEM_CAL_EVENT_WDMA_START0;
                }
                else if (IEM_CAL_EVENT_WDMA_END0 <= event[cnt])
                {
                    calIrqNum = 1U;
                    calEvent  = event[cnt] - IEM_CAL_EVENT_WDMA_END0;
                }
                else
                {
                    calIrqNum = 0U;
                    calEvent  = event[cnt];
                }
                /* Enable the interrupts at the CAL level */
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_HL_IRQENABLE_SET(calIrqNum);
                regVal  = HW_RD_REG32(regAddr);
                regVal |= ((uint32_t) 1 << calEvent);
                HW_WR_REG32(regAddr, regVal);

                /* Store the register address in clientInfo instance */
                regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                          CAL_HL_IRQSTATUS(calIrqNum);
                clientInfo->statusReg[cnt][1U]    = regAddr;
                clientInfo->statusClrReg[cnt][1U] = regAddr;
                clientInfo->mask[cnt][1U]         = ((uint32_t) 1U << calEvent);

                clientInfo->subModuleEoiAddr[cnt] =
                    gIemCommonObj.baseAddress[moduleIdx] +
                    CAL_HL_IRQ_EOI;
                clientInfo->subModuleEoiLine[cnt] = 0U;
            }
            else if (IEM_EG_CAL_A_CSI2 == eventGroup)
            {
                /* Handled in section below */
            }
            else
            {
                GT_assert(VpsVemTrace, FALSE);
            }
        }


        /* These events are to processed at 3 levels
            0 : Top ISS level - Above for loop address this
            1 : At CAL level either PPI, PPI_VC or BYS_OVR
            2 : Instance specific errors CAL_CSI2_COMPLEXIO_IRQSTATUS &
                    per virtual channel CAL_CSI2_VC_IRQENABLE */
        if (IEM_EG_CAL_A_CSI2 == eventGroup)
        {
            for (cnt = 0U; cnt < numEvents; cnt++)
            {
                /* Enable the event at the CAL TOP */
                moduleIdx = IEM_MODULE_ISS_CAL_A;
                if (VPS_CAL_CSI2_PPI_CMPLXIO_RSERVED_31 > event[cnt])
                {
                    calEvent = IEM_CAL_EVENT_PPIO;
                }
                else if ((VPS_CAL_CSI2_PPI_VC_SOF1 <= event[cnt]) &&
                         (VPS_CAL_CSI2_PPI_VC_RESERVED_31 > event[cnt]))
                {
                    calEvent = IEM_CAL_EVENT_PPIO_VC;
                }
                else
                {
                    status = BSP_EBADARGS;
                    GT_assert(VpsVemTrace, FALSE);
                }
                if (FVID2_SOK == status)
                {
                    regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                              CAL_HL_IRQENABLE_SET(0U);
                    regVal  = HW_RD_REG32(regAddr);
                    regVal |= ((uint32_t) 1 << calEvent);
                    HW_WR_REG32(regAddr, regVal);

                    /* Store the register address in clientInfo instance */
                    regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                              CAL_HL_IRQSTATUS(0U);
                    clientInfo->statusReg[cnt][1U]    = regAddr;
                    clientInfo->statusClrReg[cnt][1U] = regAddr;
                    clientInfo->mask[cnt][1U]         = ((uint32_t) 1U << calEvent);

                    clientInfo->isThirdLevelReq[cnt] = TRUE;

                    if (VPS_CAL_CSI2_PPI_CMPLXIO_RSERVED_31 > event[cnt])
                    {
                        calEvent = event[cnt];
                        regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                                  CAL_CSI2_COMPLEXIO_IRQENABLE(0U);
                        regVal  = HW_RD_REG32(regAddr);
                        regVal |= ((uint32_t) 1 << calEvent);
                        HW_WR_REG32(regAddr, regVal);

                        /* Store the register address in clientInfo instance */
                        regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                                  CAL_CSI2_COMPLEXIO_IRQSTATUS(0U);
                        clientInfo->statusReg[cnt][2U]    = regAddr;
                        clientInfo->statusClrReg[cnt][2U] = regAddr;
                        clientInfo->mask[cnt][2U]         =
                            ((uint32_t) 1U << calEvent);
                    }
                    else if ((VPS_CAL_CSI2_PPI_VC_SOF1 <= event[cnt]) &&
                           (VPS_CAL_CSI2_PPI_VC_RESERVED_31 > event[cnt]))
                    {
                        calEvent = event[cnt] - VPS_CAL_CSI2_PPI_VC_SOF1;

                        regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                                  CAL_CSI2_VC_IRQENABLE(0U);
                        regVal  = HW_RD_REG32(regAddr);
                        regVal |= ((uint32_t) 1 << calEvent);
                        HW_WR_REG32(regAddr, regVal);

                        /* Store the register address in clientInfo instance */
                        regAddr = gIemCommonObj.baseAddress[moduleIdx] +
                                  CAL_CSI2_VC_IRQSTATUS(0U);
                        clientInfo->statusReg[cnt][2U]    = regAddr;
                        clientInfo->statusClrReg[cnt][2U] = regAddr;
                        clientInfo->mask[cnt][2U]         =
                            ((uint32_t) 1U << calEvent);
                    }
                    else
                    {
                        GT_assert(VpsVemTrace, FALSE);
                    }

                    clientInfo->subModuleEoiAddr[cnt] =
                        gIemCommonObj.baseAddress[moduleIdx] +
                        CAL_HL_IRQ_EOI;
                    clientInfo->subModuleEoiLine[cnt] = 0U;
                }
            }
        }

        clientInfo->arg      = arg;
        clientInfo->clientCb = callback;
        clientInfo->priority = priority;
    }

    return (status);
}

static issemInstObj_t *IemGetInstObj(issemInstId_t instId)
{
    uint32_t        instCnt;
    issemInstObj_t *instObj = NULL;

    if (instId < IEM_INST_ID_MAX)
    {
        for (instCnt = 0U; instCnt < IEM_MAX_INST; instCnt++)
        {
            if (gIemInstObj[instCnt].instId == instId)
            {
                instObj = &gIemInstObj[instCnt];
                break;
            }
        }
    }

    return (instObj);
}

