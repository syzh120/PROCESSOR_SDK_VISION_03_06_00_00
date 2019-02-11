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
 *  \file vps_evtMgr.c
 *
 *  \brief Event Manager file
 *  This file implements Event Manager for VPS
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>
#endif
#include <ti/drv/vps/src/vpslib/common/src/vps_intcRegOffset.h>
#include <ti/drv/vps/src/vpslib/common/vps_evtMgr.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VEM_REGSIZE_SHIFT               (5U)

/** \brief Maximum number of clients for Event Manager. */
#define VEM_MAX_CLIENTS                 (50U)
#define VEM_MAX_CLIENT_EVENTS           (10U)

/**
 *  \brief Flags used by clientinfo structures memory pool manager to
 *  indicate availability of pool memory
 */
#define VEM_MEM_FLAG_FREE               (0xFFFFFFFFU)
#define VEM_MEM_FLAG_ALLOC              (0x00000000U)

/** \brief Bit position that would be used to enable client interrupts. */
#define VEM_CLIENT_EVENT_ENABLE_MASK    (0x7U)

#define VIP_SLICE0_OFFSET               ((UInt32) 0x5500U)
#define VIP_SLICE1_OFFSET               ((UInt32) 0x5A00U)
#define VIP_SLICE0_BIT_OFFSET           (0U)
#define VIP_SLICE1_BIT_OFFSET           (1U)

/* ========================================================================== */
/*                      static Function Declaration                           */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      static Function Definition                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef enum
{
    VEM_INTR_TYPE_DSS_ONLY = 0,
    VEM_INTR_TYPE_DSS_VPDMA,
    VEM_INTR_TYPE_VIP,
    VEM_INTR_TYPE_MAX
}Vem_InterruptType;
/**
 *  struct Vem_EventGroupInfo
 *  \brief Structure to keep track of the information related to a group. One
 *  instance of eventGroupinfo will be used for list of events of single group
 *  stored in a single register. It keeps bit position where event group starts
 *  in the register, difference between bit position of two events and registers
 *  to set event, clear event, enable event, disable event.
 */
typedef struct
{
    Vem_InterruptType interruptType;
    /**< Flag to indicate that a event is only INTC level alone or also present
     *   at VPDMA level. */

    UInt32            maxEvents;
    /**< Maximum number of events in this event group. */

    UInt32            startBit;
    /**< Location of the event group within the register. */
    UInt32            bitOffset;
    /**< Defines the offset between two consecutive events within the
     *   register. For some group events like list complete, the events are
     *   spaced between notify event and hence this offset is needed to jump
     *   to the next bit position of the event group. */

    UInt32            statusReg;
    /**< Status register offset. */

    UInt32            vpdmaStatClrReg;
    /**< VPDMA level status clear register offset. */
    UInt32            dssStatClrReg;
    /**< Top level INTC level status clear register offset. */

    UInt32            vpdmaEnableReg;
    /**< VPDMA level interrupt enable register offset. */
    UInt32            dssEnableReg;
    /**< Top level INTC level interrupt enable register offset. */

    UInt32            vpdmaDisableReg;
    /**< VPDMA level interrupt disable register offset. */
    UInt32            dssDisableReg;
    /**< VPDMA level interrupt disable register offset. */

    UInt32            numClients;
    /**< Number of clients registered to this event group so that the event
     *   could be disabled once all num clients become 0. */
} Vem_EventGroupInfo;

/**
 *  struct Vem_InstObj
 *  \brief structure to keep track of information regarding
 *  event manager.
 */
typedef struct
{
    UInt32             instId;
    /**< VEM Instance ID. */
    UInt32             irqNumber;
    /**< IRG number at CPU level INTC. */
    UInt32             intcNum;
    /**< Defines the INTC number of the INTC to be used. */
    UInt32             intcBaseAddr;
    /**< Top level INTC base address of the instance. */
    UInt32             vpdmaBaseAddr;
    /**< VPDMA base address of the instance. */
    UInt32             eoiAddr;
    /**< Address of EOI register. */
    Vem_EventGroupInfo egInfo[VEM_EG_MAX];
    /**< Event group info after adding the specific base address of instance. */
    BspUtils_Node     *headNode;
    /**< Pointer to the head node of the priority linked list. */
    BspOsal_IntrHandle intrHandle;
    /**< Handle to Hardware Interrupt. */
    UInt32             numIntr;
    /**< Total number of interrupts occured since last init. */
    UInt32             referenceCount[VEM_EG_MAX];
    /**< There could be cases where in an event could span across multiple
     *   registers. However, the control for this interrupt could be just 1 bit
     *   (As in case of client interrupt). Use this count to determine, if the
     *   interrupt could be disabled. */
    BspUtils_TsPrfLog  isrPrfLog;
    /**< ISR duration performance log. */
} Vem_InstObj;

/**
 *  struct Vem_ClientInfo
 *  \brief This structure keeps track of the client information.
 *  It will be filled up when client registers for the event callback to the
 *  event manager. Client can register one or multiple events of a single event
 *  group with a callback. So if any of one or multiple events occurs, event
 *  manager calls the callback function of the client. For each client, this
 *  structure keeps track of register to be checked for the event, register in
 *  which event is to cleared. It also keeps track of eventGroup, priority,
 *  client callback etc.
 *
 *  rawSetReg - Pointer to array containing register addresses in which event
 *               manager will check for the event. Size of this array will be
 *               the number of event for which client has registered the
 *               callback.
 *  rawClearReg - Pointer to array containing register addresses in which event
 *                manager will clear the event. Size of this array will be
 *                the number of event for which client has registered the
 *                callback.
 */
typedef struct
{
    UInt32            statusReg[VEM_MAX_CLIENT_EVENTS];
    UInt32            vpdmaStatClrReg[VEM_MAX_CLIENT_EVENTS];
    UInt32            vpdmaEnableReg[VEM_MAX_CLIENT_EVENTS];
    UInt32            vpdmaDisableReg[VEM_MAX_CLIENT_EVENTS];
    UInt32            dssStatClrReg[VEM_MAX_CLIENT_EVENTS];
    UInt32            statMask[VEM_MAX_CLIENT_EVENTS];
    UInt32            dssMask[VEM_MAX_CLIENT_EVENTS];
    UInt32            vpdmaMask[VEM_MAX_CLIENT_EVENTS];
    Vem_InterruptType interruptType[VEM_MAX_CLIENT_EVENTS];
    /**< Pointer to the array containing the masks using which event in
     *   the rawSetReg will be checked or will be cleared in the rawClearReg */
    Vem_ClientCbFxn   clientCb;
    /**< Client's callback function. This function will be called by the
     *   event manager whenever client registered event occurs */
    Ptr               arg;
    /**< client's private data to be passed to it when callback function is
     *   called */
    Vem_EventGroup    eventGroup;
    /**< This tells the event group into which registered event belongs */
    UInt32            allEvents[VEM_MAX_CLIENT_EVENTS];
    /**< List of events for which client has registered callback */
    UInt32            setEvents[VEM_MAX_CLIENT_EVENTS];
    /**< This array contains the list of events occurred at the time of
     *   interrupt. It will be passed down to the clients.*/
    UInt32            numEvents;
    /**< Count of events for client has registered callback. */
    Vem_Priority      priority;
    /**< Priority of the client */
    Vem_InstObj      *instObj;
    /**< Pointer to the instance of the event manager to which this client
     *   is registered. */
    UInt32            numIntr;
    /**< Keeps track of number of interrupts occured for this client */
} Vem_ClientInfo;

/**
 *  struct Vem_CommonObj
 *  \brief structure to keep track of commonly used variables in event manager.
 */
typedef struct
{
    Vem_ClientInfo    clientMemPool[VEM_MAX_CLIENTS];
    /**< Pool of memory for the clientinfo structure. */
    UInt32            clientMemFlag[VEM_MAX_CLIENTS];
    /**< Flags for each instance to indicate whether it is free or allocated. */
    BspUtils_Node     nodePool[VEM_MAX_CLIENTS];
    /**< Pool of memory for the node. */
    BspOsal_SemHandle lockSem;
    /**< Semaphore handle. */
} Vem_CommonObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void vemFillClientInfo(Vem_ClientInfo *clientInfo,
                              Vem_EventGroup  eventGroup,
                              const UInt32   *event,
                              UInt32          numEvents,
                              Vem_Priority    priority,
                              Vem_ClientCbFxn callback,
                              void           *arg);

static void vemDeleteClientInfo(const Vem_ClientInfo *clientInfo);

static Vem_ClientInfo *vemCreateClientInfo(BspUtils_Node **node);

static void vemDeleteNode(const BspUtils_Node *emNode);

static void vemAddNode(BspUtils_Node *newNode, Vem_Priority priority);
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static void Vem_masterISR(UInt32 arg);
#ifdef __cplusplus
}
#endif
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Event group infor common to all instance. */
static const Vem_EventGroupInfo gVemEgInfo[VEM_EG_MAX] =
{
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    /* VEM_EG_CHANNEL0 */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_CHANNEL_NUM_CHANNELS,      /* maxEvents */
        0, 1,                                   /* startBit, bitOffset */
        VPDMA_INT_CHANNEL0_INT_STAT,            /* statusReg */
        VPDMA_INT_CHANNEL0_INT_STAT,            /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,              /* dssStatClrReg */
        VPDMA_INT_CHANNEL0_INT_MASK,            /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,               /* dssEnableReg */
        VPDMA_INT_CHANNEL0_INT_MASK,            /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,               /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_CHANNEL1 */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_CHANNEL_NUM_CHANNELS,      /* maxEvents */
        0, 1,                                   /* startBit, bitOffset */
        VPDMA_INT_CHANNEL1_INT_STAT,            /* statusReg */
        VPDMA_INT_CHANNEL1_INT_STAT,            /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,              /* dssStatClrReg */
        VPDMA_INT_CHANNEL1_INT_MASK,            /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,               /* dssEnableReg */
        VPDMA_INT_CHANNEL1_INT_MASK,            /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,               /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_CHANNEL2 */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_CHANNEL_NUM_CHANNELS,      /* maxEvents */
        0, 1,                                   /* startBit, bitOffset */
        VPDMA_INT_CHANNEL2_INT_STAT,            /* statusReg */
        VPDMA_INT_CHANNEL2_INT_STAT,            /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,              /* dssStatClrReg */
        VPDMA_INT_CHANNEL2_INT_MASK,            /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,               /* dssEnableReg */
        VPDMA_INT_CHANNEL2_INT_MASK,            /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,               /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_CHANNEL3 */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_CHANNEL_NUM_CHANNELS,      /* maxEvents */
        0, 1,                                   /* startBit, bitOffset */
        VPDMA_INT_CHANNEL3_INT_STAT,            /* statusReg */
        VPDMA_INT_CHANNEL3_INT_STAT,            /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,              /* dssStatClrReg */
        VPDMA_INT_CHANNEL3_INT_MASK,            /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,               /* dssEnableReg */
        VPDMA_INT_CHANNEL3_INT_MASK,            /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,               /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_CHANNEL4 */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_CHANNEL_NUM_CHANNELS,      /* maxEvents */
        0, 1,                                   /* startBit, bitOffset */
        VPDMA_INT_CHANNEL4_INT_STAT,            /* statusReg */
        VPDMA_INT_CHANNEL4_INT_STAT,            /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,              /* dssStatClrReg */
        VPDMA_INT_CHANNEL4_INT_MASK,            /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,               /* dssEnableReg */
        VPDMA_INT_CHANNEL4_INT_MASK,            /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,               /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_CHANNEL5 */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_CHANNEL_NUM_CHANNELS,      /* maxEvents */
        0, 1,                                   /* startBit, bitOffset */
        VPDMA_INT_CHANNEL5_INT_STAT,            /* statusReg */
        VPDMA_INT_CHANNEL5_INT_STAT,            /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,              /* dssStatClrReg */
        VPDMA_INT_CHANNEL5_INT_MASK,            /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,               /* dssEnableReg */
        VPDMA_INT_CHANNEL5_INT_MASK,            /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,               /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_CHANNEL6 */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_CHANNEL_NUM_CHANNELS,      /* maxEvents */
        0, 1,                                   /* startBit, bitOffset */
        VPDMA_INT_CHANNEL6_INT_STAT,            /* statusReg */
        VPDMA_INT_CHANNEL6_INT_STAT,            /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,              /* dssStatClrReg */
        VPDMA_INT_CHANNEL6_INT_MASK,            /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,               /* dssEnableReg */
        VPDMA_INT_CHANNEL6_INT_MASK,            /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,               /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_CLIENT0 */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_MAX_CLIENTS,               /* maxEvents */
        0, 1,                                   /* startBit, bitOffset */
        VPDMA_INT_CLIENT0_INT_STAT,             /* statusReg */
        VPDMA_INT_CLIENT0_INT_STAT,             /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,              /* dssStatClrReg */
        VPDMA_INT_CLIENT0_INT_MASK,             /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,               /* dssEnableReg */
        VPDMA_INT_CLIENT0_INT_MASK,             /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,               /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_CLIENT1 */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_MAX_CLIENTS,               /* maxEvents */
        0, 1,                                   /* startBit, bitOffset */
        VPDMA_INT_CLIENT1_INT_STAT,             /* statusReg */
        VPDMA_INT_CLIENT1_INT_STAT,             /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,              /* dssStatClrReg */
        VPDMA_INT_CLIENT1_INT_MASK,             /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,               /* dssEnableReg */
        VPDMA_INT_CLIENT1_INT_MASK,             /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,               /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_LISTCOMPLETE */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_MAX_LIST,                  /* maxEvents */
        0, 2,                                   /* startBit, bitOffset */
        VPDMA_INT_LIST0_INT_STAT,               /* statusReg */
        VPDMA_INT_LIST0_INT_STAT,               /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG0,              /* dssStatClrReg */
        VPDMA_INT_LIST0_INT_MASK,               /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG0,               /* dssEnableReg */
        VPDMA_INT_LIST0_INT_MASK,               /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG0,               /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_LISTNOTIFY */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_MAX_LIST,                  /* maxEvents */
        1, 2,                                   /* startBit, bitOffset */
        VPDMA_INT_LIST0_INT_STAT,               /* statusReg */
        VPDMA_INT_LIST0_INT_STAT,               /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG0,              /* dssStatClrReg */
        VPDMA_INT_LIST0_INT_MASK,               /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG0,               /* dssEnableReg */
        VPDMA_INT_LIST0_INT_MASK,               /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG0,               /* dssDisableReg */
        0                                       /* numClients */
    },
    /* VEM_EG_SI */
    {
        VEM_INTR_TYPE_DSS_VPDMA,                /* interruptType */
        VPSHAL_VPDMA_MAX_SI_SOURCE,             /* maxEvents */
        16, 1,                                  /* startBit, bitOffset */
        VPDMA_INT_LIST0_INT_STAT,               /* statusReg */
        VPDMA_INT_LIST0_INT_STAT,               /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG0,              /* dssStatClrReg */
        VPDMA_INT_LIST0_INT_MASK,               /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG0,               /* dssEnableReg */
        VPDMA_INT_LIST0_INT_MASK,               /* vpdmaDisableReg */
        VPS_INTC_ENABLED_CLR_REG0,              /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_ERROR */
    {
        VEM_INTR_TYPE_DSS_ONLY,                 /* interruptType */
        VEM_EE_MAX,                             /* maxEvents */
        16, 1,                                  /* startBit, bitOffset */
        VPS_INTC_ENABLED_CLR_REG1,              /* statusReg */
        0U,                                     /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,              /* dssStatClrReg */
        0U,                                     /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,               /* dssEnableReg */
        0U,                                     /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,               /* dssDisableReg */
        0U                                      /* numClients */
    },
    /* VEM_EG_OTHERS */
    {
        VEM_INTR_TYPE_DSS_ONLY,                 /* interruptType */
        VEM_OE_MAX,                             /* maxEvents */
        17, 1,                                  /* startBit, bitOffset */
        VPS_INTC_ENABLED_CLR_REG0,              /* statusReg */
        0U,                                     /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG0,              /* dssStatClrReg */
        0U,                                     /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG0,               /* dssEnableReg */
        0U,                                     /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG0,               /* dssDisableReg */
        0U                                      /* numClients */
    },

    /* VEM_EG_OVERFLOW */
    {
        VEM_INTR_TYPE_VIP,                 /* interruptType */
        VEM_VIP_PARSER_MAX,                /* maxEvents */
        20, 1,                             /* startBit, bitOffset */
        VPS_INTC_ENABLED_CLR_REG0,         /* statusReg */
        VIP_FIQ_CLEAR,                     /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG0,         /* dssStatClrReg */
        VIP_FIQ_MASK,                      /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG0,          /* dssEnableReg */
        VIP_FIQ_MASK,                      /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG0,          /* dssDisableReg */
        0U                                 /* numClients */
    },

#endif
    /* This is Just To avoid DSS only Build error */
#ifdef VPS_DSS_BUILD
    #ifndef VPS_VIP_BUILD
     #ifndef VPS_VPE_BUILD
    {
        VEM_INTR_TYPE_DSS_VPDMA,     /* interruptType */
        0,                           /* maxEvents */
        0, 1,                        /* startBit, bitOffset */
        VPDMA_INT_CHANNEL0_INT_STAT, /* statusReg */
        VPDMA_INT_CHANNEL0_INT_STAT, /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,   /* dssStatClrReg */
        VPDMA_INT_CHANNEL0_INT_MASK, /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,    /* dssEnableReg */
        VPDMA_INT_CHANNEL0_INT_MASK, /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,    /* dssDisableReg */
        0U                           /* numClients */
    },
      #endif
    #endif
#endif
#if !(defined (VPS_VIP_BUILD)) && !(defined (VPS_VPE_BUILD)) && \
    !(defined (VPS_DSS_BUILD))
    {
        VEM_INTR_TYPE_MAX,           /* VPS Event manager not used. Default to
                                      *  invalid */
        0,                           /* maxEvents */
        0, 0,                        /* startBit, bitOffset */
        VPDMA_INT_CHANNEL0_INT_STAT, /* statusReg */
        VPDMA_INT_CHANNEL0_INT_STAT, /* vpdmaStatClrReg */
        VPS_INTC_ENABLED_CLR_REG1,   /* dssStatClrReg */
        VPDMA_INT_CHANNEL0_INT_MASK, /* vpdmaEnableReg */
        VPS_INTC_ENABLE_SET_REG1,    /* dssEnableReg */
        VPDMA_INT_CHANNEL0_INT_MASK, /* vpdmaDisableReg */
        VPS_INTC_ENABLE_CLR_REG1,    /* dssDisableReg */
        0U                           /* numClients */
    }
#endif
};

/**
 *  \brief Array group info structure to keep track of group information. One
 *  instance of eventGroupinfo will be used for list of events of single group
 *  stored in a single register.
 */
Vem_InstObj          gVemInstObj[VEM_MAX_INST];

static Vem_CommonObj gVemCommonObj;

/* ========================================================================== */
/*                     Internal Function Declarations                         */
/* ========================================================================== */
static Vem_InstObj *vemGetInstObj(Vem_InstId instId);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief Initializes the VPS Event Manager. It marks all the client info
 *  instances in the memory as available and register interrupt handler
 */
Int32 Vem_init(UInt32 numInst, const Vem_InstParams *instPrms)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt, instCnt, setOffset;
    Vem_InstObj        *instObj;
    Vem_EventGroupInfo *egInfo;

    /* Check for errors */
    GT_assert(VpsVemTrace, (numInst <= VEM_MAX_INST));
    GT_assert(VpsVemTrace, (NULL != instPrms));

    /* Init objects and mark flags as free */
    BspUtils_memset(gVemInstObj, 0, sizeof (gVemInstObj));
    BspUtils_memset(&gVemCommonObj, 0, sizeof (gVemCommonObj));
    for (instCnt = 0U; instCnt < VEM_MAX_INST; instCnt++)
    {
        gVemInstObj[instCnt].instId = VEM_INST_ID_MAX;
        BspUtils_initTsPrfLog(&gVemInstObj[instCnt].isrPrfLog);
    }
    for (cnt = 0U; cnt < VEM_MAX_CLIENTS; cnt++)
    {
        gVemCommonObj.clientMemFlag[cnt] = VEM_MEM_FLAG_FREE;
    }

    /* Initialise the semaphore parameters and create Pool Semaphore */
    gVemCommonObj.lockSem = BspOsal_semCreate((Int32) 1, TRUE);
    if (NULL == gVemCommonObj.lockSem)
    {
        retVal = BSP_EALLOC;
    }

    if (BSP_SOK == retVal)
    {
        for (instCnt = 0U; instCnt < numInst; instCnt++)
        {
            /* Initialize instance object members */
            instObj                = &gVemInstObj[instCnt];
            instObj->instId        = instPrms[instCnt].instId;
            instObj->irqNumber     = instPrms[instCnt].irqNumber;
            instObj->intcNum       = instPrms[instCnt].intcNum;
            instObj->intcBaseAddr  = instPrms[instCnt].intcBaseAddr;
            instObj->vpdmaBaseAddr = instPrms[instCnt].vpdmaBaseAddr;
            instObj->eoiAddr       = instObj->intcBaseAddr + VPS_INTC_EOI_ADDR;

            BspUtils_memcpy(
                &instObj->egInfo[0],
                &gVemEgInfo[0],
                sizeof (gVemEgInfo));

            /* Add the instance specific offsets */
            for (cnt = 0U; cnt < VEM_EG_MAX; cnt++)
            {
                egInfo = &instObj->egInfo[cnt];

                /* Add the DSS interrupt set offset */

                setOffset = (UInt32) (VPS_INTC_SET_START_OFFSET +
                                      (instObj->intcNum * VPS_INTC_SET_SIZE));
                if ((VEM_INTR_TYPE_DSS_ONLY == egInfo->interruptType) ||
                    (VEM_INTR_TYPE_VIP == egInfo->interruptType))
                {
                    egInfo->statusReg += (instObj->intcBaseAddr + setOffset);
                }
                egInfo->dssStatClrReg += (instObj->intcBaseAddr + setOffset);
                egInfo->dssEnableReg  += (instObj->intcBaseAddr + setOffset);
                egInfo->dssDisableReg += (instObj->intcBaseAddr + setOffset);

                /* Add the VPDMA interrupt set offset */
                setOffset = (UInt32) (VPS_VPDMA_INT_SET_START_OFFSET +
                                      (instObj->intcNum *
                                       VPS_VPDMA_INT_SET_SIZE));
                if (VEM_INTR_TYPE_DSS_VPDMA == egInfo->interruptType)
                {
                    egInfo->statusReg += (instObj->vpdmaBaseAddr + setOffset);

                    egInfo->vpdmaStatClrReg += (instObj->vpdmaBaseAddr +
                                                setOffset);
                    egInfo->vpdmaEnableReg += (instObj->vpdmaBaseAddr +
                                               setOffset);
                    egInfo->vpdmaDisableReg += (instObj->vpdmaBaseAddr +
                                                setOffset);
                }
                if (VEM_INTR_TYPE_VIP == egInfo->interruptType)
                {
                    egInfo->vpdmaStatClrReg += instObj->intcBaseAddr;

                    egInfo->vpdmaEnableReg += instObj->intcBaseAddr;

                    egInfo->vpdmaDisableReg += instObj->intcBaseAddr;
                }
            }

            /* Clear out any pending interrupts */
            BspOsal_clearIntr(instObj->irqNumber);

            /* Clear out pending interrupts at DSS and VPDMA Level and disable
             * all interrupts */
            for (cnt = 0U; cnt < VEM_EG_MAX; cnt++)
            {
                egInfo = &instObj->egInfo[cnt];

                /* Disable Interrupts at the DSS and VPDMA level */
                if (VEM_INTR_TYPE_DSS_VPDMA == egInfo->interruptType)
                {
                    HW_WR_REG32(egInfo->vpdmaDisableReg, (UInt32) 0x0U);
                    /* Clean the pending interrupts */
                    HW_WR_REG32(egInfo->vpdmaStatClrReg, 0xFFFFFFFFU);
                }
                if (VEM_INTR_TYPE_VIP == egInfo->interruptType)
                {
                    /*This register works only when you first make it zero*/
                    HW_WR_REG32((egInfo->vpdmaStatClrReg + VIP_SLICE0_OFFSET),
                                0x0U);
                    HW_WR_REG32((egInfo->vpdmaStatClrReg + VIP_SLICE1_OFFSET),
                                0x0U);
                    HW_WR_REG32((egInfo->vpdmaEnableReg + VIP_SLICE0_OFFSET),
                                0xFFFFFFFFU);
                    HW_WR_REG32((egInfo->vpdmaEnableReg + VIP_SLICE1_OFFSET),
                                0xFFFFFFFFU);
                    /* Clean the pending interrupts */
                    HW_WR_REG32((egInfo->vpdmaStatClrReg + VIP_SLICE0_OFFSET),
                                0xFFFFFFFFU);
                    HW_WR_REG32((egInfo->vpdmaStatClrReg + VIP_SLICE1_OFFSET),
                                0xFFFFFFFFU);
                }

                HW_WR_REG32(egInfo->dssDisableReg, 0xFFFFFFFFU);

                /* Clean the pending interrupts */
                HW_WR_REG32(egInfo->dssStatClrReg, 0xFFFFFFFFU);

                instObj->referenceCount[cnt] = 0U;
            }

            instObj->headNode = NULL;
            instObj->numIntr  = 0U;

            /* ----------------- Register ISR --------------- */
            instObj->intrHandle = BspOsal_registerIntr(
                instObj->irqNumber,
                &Vem_masterISR,
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
        Vem_deInit();
    }

    return (retVal);
}

/**
 *  \brief De-Initializes event Manager. It deletes semaphore and un-registers
 *  the IRQ handle and removes all the client info instance from the linked
 *  list.
 */
Int32 Vem_deInit(void)
{
    UInt32         instCnt;
    Vem_InstObj   *instObj;
    BspUtils_Node *tempNode, *emNode;

    for (instCnt = 0U; instCnt < VEM_MAX_INST; instCnt++)
    {
        instObj = &gVemInstObj[instCnt];

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
            vemDeleteClientInfo((Vem_ClientInfo *) emNode->data);
            vemDeleteNode(emNode);
        }
    }

    if (gVemCommonObj.lockSem != NULL)
    {
        BspOsal_semDelete(&(gVemCommonObj.lockSem));
        gVemCommonObj.lockSem = NULL;
    }

    return (BSP_SOK);
}

/**
 *  \brief Master ISR function. This is interrupt handler registered for the
 *  interrupt. When called, it will search for all events of all
 *  clients to see if it has occurred. If any event is occurred, it will
 *  clear that event and call the callback function of the client.
 */
static void Vem_masterISR(UInt32 arg)
{
    UInt32          cnt;
    UInt32          regValue, numEvents;
    UInt32          numClients = 0;
    BspUtils_Node  *tempNode;
    Vem_ClientInfo *clientInfo = NULL;
    Vem_InstObj    *instObj;

    instObj  = (Vem_InstObj *) arg;
    tempNode = instObj->headNode;

    BspUtils_startTsPrfLog(&instObj->isrPrfLog);

    /*
     * Note:
     * ----
     * Clear all DSS (level 1) interrupt status for VPDMA interrupts (level 2)
     * first. This is required because if we clear this interrupt at the
     * time of servicing VPDMA interrupts (level 2), we might miss to service
     * some of VPDMA interrupts which occurs after checking them in the while
     * loop of client and before clearing the DSS and the next VPDMA interrupt.
     *
     * For example, assume we check for VPDMA SI0 and SI1 in this ISR and SI0 is
     * checked first. Now at time t0, SI1 occurred and we enter this ISR.
     * After we check SI0 has occurred or not, SI0 happens. This will
     * set the already set DSS interrupt to 1. But since we have already
     * checked for this event, we go ahead and service SI1 and at that time
     * clear the DSS interupt which was set for both SI0 and SI1. Hence
     * SI0 will not be serviced again till we get this ISR for some other
     * event!!
     */
    /* Traverse through the entire list of registered clients */
    tempNode = instObj->headNode;
    while (NULL != tempNode)
    {
        clientInfo = (Vem_ClientInfo *) tempNode->data;
        GT_assert(VpsVemTrace, (NULL != clientInfo));
        for (cnt = 0; cnt < clientInfo->numEvents; cnt++)
        {
            /* Clear the status only for 2 level interrupts. Let the
             * single level interrupts be handled as is in the next
             * while loop. */
            if (VEM_INTR_TYPE_DSS_ONLY != clientInfo->interruptType[cnt])
            {
                regValue = HW_RD_REG32(clientInfo->dssStatClrReg[cnt]);
                if ((UInt32) 0U != (regValue & (clientInfo->dssMask[cnt])))
                {
                    HW_WR_REG32(clientInfo->dssStatClrReg[cnt],
                                clientInfo->dssMask[cnt]);
                }
            }
        }

        /* Move to the next client */
        tempNode = tempNode->next;
    }

    /* Traverse through the entire list of registered clients */
    tempNode = instObj->headNode;
    while (NULL != tempNode)
    {
        numEvents  = 0U;
        clientInfo = (Vem_ClientInfo *) tempNode->data;
        GT_assert(VpsVemTrace, (NULL != clientInfo));
        for (cnt = 0; cnt < clientInfo->numEvents; cnt++)
        {
            /* See if any of registered events has occurred */
            regValue = HW_RD_REG32(clientInfo->statusReg[cnt]);
            if ((UInt32) 0U != (regValue & (clientInfo->statMask[cnt])))
            {
                /* Make an array of events which has occurred. */
                clientInfo->setEvents[numEvents] =
                    clientInfo->allEvents[cnt];
                numEvents++;

                /* Clear the event */
                if (VEM_INTR_TYPE_DSS_VPDMA == clientInfo->interruptType[cnt])
                {
                    /* We have already cleared DSS interrupts (level 1),
                     * just clear VPDMA interrupts (level 2) */
                    HW_WR_REG32(clientInfo->vpdmaStatClrReg[cnt],
                                clientInfo->vpdmaMask[cnt]);
                }
                else if (VEM_INTR_TYPE_VIP ==
                         clientInfo->interruptType[cnt])
                {
                    /* For VIP registers, need to write 0 first for changes to
                     *take effect*/
                    HW_WR_REG32(clientInfo->vpdmaStatClrReg[cnt],
                                0x0U);

                    HW_WR_REG32(clientInfo->vpdmaStatClrReg[cnt],
                                clientInfo->vpdmaMask[cnt]);
                }
                else
                {
                    /* Clear DSS only interrupts */
                    HW_WR_REG32(clientInfo->dssStatClrReg[cnt],
                                clientInfo->dssMask[cnt]);
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

    HW_WR_REG32(instObj->eoiAddr, instObj->intcNum);

    /* Increment total number of interrupts */
    instObj->numIntr++;

    BspUtils_endTsPrfLog(&instObj->isrPrfLog);

    return;
}

static Vem_InstObj *vemGetInstObj(Vem_InstId instId)
{
    UInt32       instCnt;
    Vem_InstObj *instObj = NULL;

    if (instId < VEM_INST_ID_MAX)
    {
        for (instCnt = 0U; instCnt < VEM_MAX_INST; instCnt++)
        {
            if (gVemInstObj[instCnt].instId == instId)
            {
                instObj = &gVemInstObj[instCnt];
                break;
            }
        }
    }

    return (instObj);
}

/**
 *  \brief This function is used to register call back function for a specific
 *  event. It takes group number and event number within the group as the
 *  argument and returns handle.
 */
void *Vem_register(Vem_InstId      instId,
                   Vem_EventGroup  eventGroup,
                   const UInt32   *event,
                   UInt32          numEvents,
                   Vem_Priority    priority,
                   Vem_ClientCbFxn callback,
                   void           *arg)
{
    UInt32 cnt;
    Vem_InstObj        *instObj;
    BspUtils_Node      *newNode    = NULL;
    Vem_ClientInfo     *clientInfo = NULL;
    Vem_EventGroupInfo *egInfo;

    /* Check for the error conditions */
    GT_assert(VpsVemTrace, (NULL != event));
    GT_assert(VpsVemTrace, (0U != numEvents));
    GT_assert(VpsVemTrace, (NULL != callback));

    instObj = vemGetInstObj(instId);
    GT_assert(VpsVemTrace, (NULL != instObj));
    egInfo = &instObj->egInfo[0];
    GT_assert(VpsVemTrace, (NULL != egInfo));
    GT_assert(VpsVemTrace, (numEvents <= egInfo[eventGroup].maxEvents));

    for (cnt = 0U; cnt < numEvents; cnt++)
    {
        GT_assert(VpsVemTrace,
                  (event[cnt] < egInfo[eventGroup].maxEvents));
    }

    BspOsal_semWait(gVemCommonObj.lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Allocate memory for the client info structure */
    clientInfo = vemCreateClientInfo(&newNode);

    if ((NULL != clientInfo) && (NULL != newNode))
    {
        newNode->data = (void *) clientInfo;

        clientInfo->instObj = instObj;
        clientInfo->numIntr = 0U;

        /* Fill up the details about events in the client info structure */
        vemFillClientInfo(
            clientInfo,
            eventGroup,
            event,
            numEvents,
            priority,
            callback,
            arg);

        /* Add the node in the linked list as per the priority */
        vemAddNode(newNode, priority);

        /* Since there are multiple clients that depend on the single client
         * interrupt source in DSS, maintain a reference count */
        if (VEM_EG_CLIENT == eventGroup)
        {
            instObj->referenceCount[VEM_EG_CLIENT]++;
        }
    }

    BspOsal_semPost(gVemCommonObj.lockSem);

    return ((void *) newNode);
}

/**
 *  \brief  Function to un-register callback from the event manager. It removes
 *          node from the linked list and frees up memory allocated to the node
 *          and client info structure. It takes handle to the callback and
 *          returns status of the whether callback is removed.
 *          must be valid handle to the callback already registered
 *
 *  \param  handle      Handle to the callback
 *
 *  \return             Indicates whether callback is removed or not.
 */
Int32 Vem_unRegister(void *handle)
{
    Int32  retVal = BSP_SOK;
    Int32  found  = 0;
    UInt32 cnt, regValue, index = 0;
    Vem_InstObj        *instObj    = NULL;
    BspUtils_Node      *tempNode   = NULL, *emNode = NULL;
    Vem_ClientInfo     *clientInfo = NULL;
    Vem_EventGroupInfo *egInfo     = NULL;

    /* Error condition Checking */
    GT_assert(VpsVemTrace, (NULL != handle));
    tempNode = (BspUtils_Node *) handle;
    GT_assert(VpsVemTrace, (NULL != tempNode->data));
    instObj = ((Vem_ClientInfo *) (tempNode->data))->instObj;
    GT_assert(VpsVemTrace, (NULL != instObj));

    egInfo = instObj->egInfo;
    GT_assert(VpsVemTrace, (NULL != egInfo));
    /* Check to see if the node given is in the linked list */
    emNode = instObj->headNode;
    GT_assert(VpsVemTrace, (NULL != emNode));
    found = 0;
    while (NULL != emNode)
    {
        if (tempNode == emNode)
        {
            found = 1;
            break;
        }
        emNode = emNode->next;
    }
    GT_assert(VpsVemTrace, (0 != found));

    clientInfo = (Vem_ClientInfo *) tempNode->data;
    GT_assert(VpsVemTrace, (NULL != clientInfo));

    BspOsal_semWait(gVemCommonObj.lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Delete the Node */
    vemDeleteNode(tempNode);

    /* Disable events in the VPS registers */
    for (cnt = 0U; cnt < clientInfo->numEvents; cnt++)
    {
        if ((VEM_EG_CHANNEL == clientInfo->eventGroup) ||
            (VEM_EG_CLIENT == clientInfo->eventGroup))
        {
            index = clientInfo->eventGroup +
                    (UInt32) (clientInfo->allEvents[cnt] >> 5U);
        }
        else
        {
            index = clientInfo->eventGroup;
        }

        egInfo[index].numClients--;
        /* Disable the event at the VPDMA */
        if (VEM_INTR_TYPE_DSS_ONLY != egInfo[index].interruptType)
        {
            regValue  = HW_RD_REG32(egInfo[index].vpdmaDisableReg);
            regValue &= (~clientInfo->vpdmaMask[cnt]);
            HW_WR_REG32(egInfo[index].vpdmaDisableReg, regValue);

            /* Clear the any pending event at the VPDMA */
            HW_WR_REG32(egInfo[index].vpdmaStatClrReg,
                        clientInfo->vpdmaMask[cnt]);
        }

        if ((VEM_EG_LISTCOMPLETE == clientInfo->eventGroup) ||
            (VEM_EG_LISTNOTIFY == clientInfo->eventGroup))
        {
            HW_WR_REG32(egInfo[index].dssDisableReg, clientInfo->dssMask[cnt]);

            /* Clear the any pending event at the DSS. For the
             * ListComplete and ListNotify interrupts, there are no
             * groups in dss register, so it can be cleared here */
            HW_WR_REG32(egInfo[index].dssStatClrReg, clientInfo->dssMask[cnt]);
        }
        else if (VEM_EG_SI == clientInfo->eventGroup)
        {
            /* Disable At the DSS only if there are no clients registered */
            if (0 == egInfo[index].numClients)
            {
                HW_WR_REG32(egInfo[index].dssDisableReg,
                            clientInfo->dssMask[cnt]);
                /* Clear any pending status register */
                HW_WR_REG32(egInfo[index].dssStatClrReg,
                            clientInfo->dssMask[cnt]);
            }
        }
        else if ((VEM_EG_CHANNEL == clientInfo->eventGroup) ||
                 (VEM_EG_CLIENT == clientInfo->eventGroup))
        {
            /* Disable At the DSS only if there are no clients registered */
            if (0 == egInfo[index].numClients)
            {
                /* In case of client interrupt, check if there are any other
                 * clients which are still registered with VEM */
                if (VEM_EG_CLIENT == clientInfo->eventGroup)
                {
                    if (instObj->referenceCount[VEM_EG_CLIENT] == 0x01U)
                    {
                        HW_WR_REG32(egInfo[index].dssDisableReg,
                                    clientInfo->dssMask[cnt]);
                        /* Clear any pending status register */
                        HW_WR_REG32(egInfo[index].dssStatClrReg,
                                    clientInfo->dssMask[cnt]);
                    }
                    instObj->referenceCount[VEM_EG_CLIENT]--;
                }
                else
                {
                    HW_WR_REG32(egInfo[index].dssDisableReg,
                                clientInfo->dssMask[cnt]);
                    /* Clear any pending status register */
                    HW_WR_REG32(egInfo[index].dssStatClrReg,
                                clientInfo->dssMask[cnt]);
                }
            }
        }
        else if ((VEM_EG_OTHERS == clientInfo->eventGroup) ||
                 (VEM_EG_ERROR == clientInfo->eventGroup))
        {
            /* Disable At the DSS only if there are no clients registered */
            if (0 == egInfo[index].numClients)
            {
                HW_WR_REG32(egInfo[index].dssDisableReg,
                            clientInfo->dssMask[cnt]);
                /* Clear any pending status register */
                HW_WR_REG32(egInfo[index].dssStatClrReg,
                            clientInfo->dssMask[cnt]);
            }
        }
        else if (VEM_EG_OVERFLOW == clientInfo->eventGroup)
        {
            /* Disable At the DSS only if there are no clients registered */
            if (0 == egInfo[index].numClients)
            {
                HW_WR_REG32(egInfo[index].dssDisableReg,
                            clientInfo->dssMask[cnt]);
                /* Clear any pending status register */
                HW_WR_REG32(egInfo[index].dssStatClrReg,
                            clientInfo->dssMask[cnt]);
            }
        }
        else
        {
            /*
             * Do nothing
             */
        }

        clientInfo->dssMask[cnt]   = 0U;
        clientInfo->vpdmaMask[cnt] = 0U;
        clientInfo->statMask[cnt]  = 0U;
    }

    /* Free up memory allocated to event arrays and clientInfo structure */
    vemDeleteClientInfo(clientInfo);

    BspOsal_semPost(gVemCommonObj.lockSem);

    return (retVal);
}

/**
 *  \brief Function to add a node to the linked list of clients at the
 *  appropriate position as per the given priority.
 */
static void vemAddNode(BspUtils_Node *newNode, Vem_Priority priority)
{
    Vem_InstObj   *instObj = NULL;
    BspUtils_Node *curr    = NULL, *prev = NULL;

    GT_assert(VpsVemTrace, (NULL != newNode));

    instObj = ((Vem_ClientInfo *) (newNode->data))->instObj;
    GT_assert(VpsVemTrace, (NULL != instObj));

    newNode->prev = newNode->next = NULL;
    curr          = instObj->headNode;
    prev          = NULL;

    /* Search for place to insert new node as per priority */
    while ((NULL != curr) &&
           (((Vem_ClientInfo *) curr->data)->priority < priority))
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
static void vemDeleteNode(const BspUtils_Node *emNode)
{
    Vem_InstObj   *instObj = NULL;
    BspUtils_Node *curr    = NULL, *prev = NULL;

    GT_assert(VpsVemTrace, (NULL != emNode));

    instObj = ((Vem_ClientInfo *) (emNode->data))->instObj;
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

/**
 *  \brief Function to allocate memory for the client information structure
 *  and other arrays.
 */
static Vem_ClientInfo *vemCreateClientInfo(BspUtils_Node **node)
{
    UInt32          cnt;
    Vem_ClientInfo *clientInfo = NULL;

    for (cnt = 0U; cnt < VEM_MAX_CLIENTS; cnt++)
    {
        if (VEM_MEM_FLAG_FREE == gVemCommonObj.clientMemFlag[cnt])
        {
            clientInfo = &(gVemCommonObj.clientMemPool[cnt]);
            *node      = &gVemCommonObj.nodePool[cnt];
            gVemCommonObj.clientMemFlag[cnt] = VEM_MEM_FLAG_ALLOC;
            break;
        }
    }

    return (clientInfo);
}

/**
 *  \brief Function to free up memory for the client information structure
 *  and other arrays.
 */
static void vemDeleteClientInfo(const Vem_ClientInfo *clientInfo)
{
    UInt32 cnt;

    GT_assert(VpsVemTrace, (NULL != clientInfo));

    for (cnt = 0U; cnt < VEM_MAX_CLIENTS; cnt++)
    {
        if (clientInfo == &(gVemCommonObj.clientMemPool[cnt]))
        {
            gVemCommonObj.clientMemFlag[cnt] = VEM_MEM_FLAG_FREE;
            break;
        }
    }

    return;
}

/**
 *  \brief Function to fill up client information structure.
 */
static void vemFillClientInfo(Vem_ClientInfo *clientInfo,
                              Vem_EventGroup  eventGroup,
                              const UInt32   *event,
                              UInt32          numEvents,
                              Vem_Priority    priority,
                              Vem_ClientCbFxn callback,
                              void           *arg)
{
    UInt32 cnt, index, eventOffset;
    UInt32 regValue = 0;
    Vem_EventGroupInfo *egInfo = clientInfo->instObj->egInfo;

    GT_assert(VpsVemTrace, (NULL != clientInfo));
    GT_assert(VpsVemTrace, (NULL != event));
    GT_assert(VpsVemTrace, (NULL != callback));
    GT_assert(VpsVemTrace, (NULL != egInfo));

    clientInfo->eventGroup = eventGroup;
    clientInfo->numEvents  = numEvents;
    for (cnt = 0U; cnt < numEvents; cnt++)
    {
        if ((VEM_EG_CHANNEL == eventGroup) ||
            (VEM_EG_CLIENT == eventGroup))
        {
            index = eventGroup +
                    (UInt32) (event[cnt] >> VEM_REGSIZE_SHIFT);
            eventOffset = event[cnt] & (((UInt32) 1U << VEM_REGSIZE_SHIFT) - 1U);
        }
        else
        {
            index       = (UInt32) eventGroup;
            eventOffset = event[cnt];
        }
        clientInfo->allEvents[cnt] = event[cnt];
        /* Store the registers from which event status can be checked or into
         * which event status can be cleared */
        clientInfo->statusReg[cnt]       = egInfo[index].statusReg;
        clientInfo->vpdmaStatClrReg[cnt] = egInfo[index].vpdmaStatClrReg;
        clientInfo->vpdmaEnableReg[cnt]  = egInfo[index].vpdmaEnableReg;
        clientInfo->vpdmaDisableReg[cnt] = egInfo[index].vpdmaDisableReg;
        clientInfo->dssStatClrReg[cnt]   = egInfo[index].dssStatClrReg;

        clientInfo->statMask[cnt] = ((UInt32) 1U << ((eventOffset *
                                            egInfo[index].bitOffset) +
                                           egInfo[index].startBit));

        /* Enable the event interrupt in the enable set register */
        GT_3trace(VpsVemTrace,
                  GT_INFO,
                  "%s: Enable Reg %x mask %x",
                  __FUNCTION__,
                  egInfo[index].vpdmaEnableReg,
                  clientInfo->statMask[cnt]);

        if ((VEM_EG_LISTCOMPLETE == eventGroup) ||
            (VEM_EG_LISTNOTIFY == eventGroup))
        {
            /* Since the list complete and list notify are at the
             * same position in DSS as well in VPDMA, second mask
             * is same as the first mask */
            clientInfo->dssMask[cnt] = clientInfo->statMask[cnt];

            GT_3trace(VpsVemTrace,
                      GT_INFO,
                      "%s: Enable Reg %x mask %x",
                      __FUNCTION__,
                      egInfo[index].dssEnableReg,
                      clientInfo->dssMask[cnt]);

            /* Clean any pending interrupts on this event */
            HW_WR_REG32(egInfo[index].dssStatClrReg, clientInfo->dssMask[cnt]);

            /* Enable the event interrupt in the enable set register */
            /* DSS registers can written directly as writing 0 has no effect */
            HW_WR_REG32(egInfo[index].dssEnableReg, clientInfo->dssMask[cnt]);
        }
        else if ((VEM_EG_SI == eventGroup))
        {
            clientInfo->dssMask[cnt] = ((UInt32) 1U << egInfo[index].startBit);

            /* Clean any pending interrupts on this event */
            HW_WR_REG32(egInfo[index].dssStatClrReg, clientInfo->dssMask[cnt]);

            /* Enable interrupt */
            HW_WR_REG32(egInfo[index].dssEnableReg, clientInfo->dssMask[cnt]);
            GT_4trace(VpsVemTrace,
                      GT_INFO,
                      "%s: Enable Reg %x Value %x RegValue %x",
                      __FUNCTION__,
                      egInfo[index].dssEnableReg,
                      regValue,
                      HW_RD_REG32(egInfo[index].dssEnableReg));
        }
        else if ((VEM_EG_CHANNEL == eventGroup) ||
                 (VEM_EG_CLIENT == eventGroup))
        {
            if (VEM_EG_CLIENT == eventGroup)
            {
                /* Unlike channel interrupts, there is 1 bit that controls
                 * clients interrupt generation */
                clientInfo->dssMask[cnt] =
                    ((UInt32) 1U << VEM_CLIENT_EVENT_ENABLE_MASK);
            }
            else
            {
                clientInfo->dssMask[cnt] = ((UInt32) 1U << index);
            }

            /* Clean any pending interrupts on this event */
            HW_WR_REG32(egInfo[index].dssStatClrReg, clientInfo->dssMask[cnt]);

            /* Enable interrupt */
            HW_WR_REG32(egInfo[index].dssEnableReg, clientInfo->dssMask[cnt]);
            GT_4trace(VpsVemTrace,
                      GT_INFO,
                      "%s: Enable Reg %x Value %x RegValue %x",
                      __FUNCTION__,
                      egInfo[index].dssEnableReg,
                      regValue,
                      HW_RD_REG32(egInfo[index].dssEnableReg));
        }
        else if ((VEM_EG_OTHERS == eventGroup) ||
                 (VEM_EG_ERROR == eventGroup))
        {
            clientInfo->dssMask[cnt] = clientInfo->statMask[cnt];

            /* Clean any pending interrupts on this event */
            HW_WR_REG32(egInfo[index].dssStatClrReg, clientInfo->dssMask[cnt]);

            /* Enable interrupt */
            HW_WR_REG32(egInfo[index].dssEnableReg, clientInfo->dssMask[cnt]);
            GT_4trace(VpsVemTrace,
                      GT_INFO,
                      "%s: Enable Reg %x Value %x RegValue %x",
                      __FUNCTION__,
                      egInfo[index].dssEnableReg,
                      regValue,
                      HW_RD_REG32(egInfo[index].dssEnableReg));
        }
        else if (VEM_EG_OVERFLOW == eventGroup)
        {
            if (VEM_SLICE0_PARSER_INT_RAW_PORTA == event[cnt])
            {
                /*Slice0*/
                eventOffset = VIP_SLICE0_BIT_OFFSET;
                /*Vpdma mask to enable the overflow in VIP FIQ registers*/
                clientInfo->vpdmaMask[cnt] =
                    ((UInt32) 1U <<
                     VEM_ASYNC_FIFO_PRTA_OF) |
                    ((UInt32) 1U <<
                     VEM_OUTPUT_FIFO_PRTA_YUV_OF) |
                    ((UInt32) 1U << VEM_OUTPUT_FIFO_PRTA_ANC_OF);
                /* Registers are init to dss baseaddress. To get the correct
                 * address, add the corrosponding offset according to Slice 0 or
                 *1*/
                clientInfo->vpdmaStatClrReg[cnt] += VIP_SLICE0_OFFSET;
                clientInfo->vpdmaEnableReg[cnt]  += VIP_SLICE0_OFFSET;
                clientInfo->vpdmaDisableReg[cnt] += VIP_SLICE0_OFFSET;
            }
            else if (VEM_SLICE0_PARSER_INT_RAW_PORTB == event[cnt])
            {
                /*Slice0*/
                eventOffset = VIP_SLICE0_BIT_OFFSET;
                /*Vpdma mask to enable the overflow in VIP FIQ registers*/
                clientInfo->vpdmaMask[cnt] =
                    ((UInt32) 1U <<
                     VEM_ASYNC_FIFO_PRTB_OF) |
                    ((UInt32) 1U <<
                     VEM_OUTPUT_FIFO_PRTB_YUV_OF) |
                    ((UInt32) 1U << VEM_OUTPUT_FIFO_PRTB_ANC_OF);
                /* Registers are init to dss baseaddress. To get the correct
                 * address, add the corrosponding offset according to Slice 0 or
                 *1*/
                clientInfo->vpdmaStatClrReg[cnt] += VIP_SLICE0_OFFSET;
                clientInfo->vpdmaEnableReg[cnt]  += VIP_SLICE0_OFFSET;
                clientInfo->vpdmaDisableReg[cnt] += VIP_SLICE0_OFFSET;
            }
            else if (VEM_SLICE1_PARSER_INT_RAW_PORTA == event[cnt])
            {
                /*Slice1*/
                eventOffset = VIP_SLICE1_BIT_OFFSET;
                /*Vpdma mask to enable the overflow in VIP FIQ registers*/
                clientInfo->vpdmaMask[cnt] =
                    ((UInt32) 1U <<
                     VEM_ASYNC_FIFO_PRTA_OF) |
                    ((UInt32) 1U <<
                     VEM_OUTPUT_FIFO_PRTA_YUV_OF) |
                    ((UInt32) 1U << VEM_OUTPUT_FIFO_PRTA_ANC_OF);
                /* Registers are init to dss baseaddress. To get the correct
                 * address, add the corrosponding offset according to Slice 0 or
                 *1*/
                clientInfo->vpdmaStatClrReg[cnt] += VIP_SLICE1_OFFSET;
                clientInfo->vpdmaEnableReg[cnt]  += VIP_SLICE1_OFFSET;
                clientInfo->vpdmaDisableReg[cnt] += VIP_SLICE1_OFFSET;
            }
            else if (VEM_SLICE1_PARSER_INT_RAW_PORTB == event[cnt])
            {
                /*Slice0*/
                eventOffset = VIP_SLICE1_BIT_OFFSET;
                /*Vpdma mask to enable the overflow in VIP FIQ registers*/
                clientInfo->vpdmaMask[cnt] =
                    ((UInt32) 1U <<
                     VEM_ASYNC_FIFO_PRTB_OF) |
                    ((UInt32) 1U <<
                     VEM_OUTPUT_FIFO_PRTB_YUV_OF) |
                    ((UInt32) 1U << VEM_OUTPUT_FIFO_PRTB_ANC_OF);
                /* Registers are init to dss baseaddress. To get the correct
                 * address, add the corrosponding offset according to Slice 0 or
                 *1*/
                clientInfo->vpdmaStatClrReg[cnt] += VIP_SLICE1_OFFSET;
                clientInfo->vpdmaEnableReg[cnt]  += VIP_SLICE1_OFFSET;
                clientInfo->vpdmaDisableReg[cnt] += VIP_SLICE1_OFFSET;
            }
            else
            {
                /*Do nothing*/
            }
            clientInfo->vpdmaMask[cnt] = ~(clientInfo->vpdmaMask[cnt]);
            clientInfo->statMask[cnt]  = ((UInt32) 1U << ((eventOffset *
                                                 egInfo[index].bitOffset) +
                                                egInfo[index].startBit));
            clientInfo->dssMask[cnt] = clientInfo->statMask[cnt];

            /*Update the clientInfo with proper register addresses*/
            clientInfo->statusReg[cnt] = egInfo[index].statusReg;

            /* Clean any pending interrupts on this event */
            HW_WR_REG32(egInfo[index].dssStatClrReg, clientInfo->dssMask[cnt]);

            /* Enable interrupt */
            HW_WR_REG32(egInfo[index].dssEnableReg, clientInfo->dssMask[cnt]);
            GT_4trace(VpsVemTrace,
                      GT_INFO,
                      "%s: Enable Reg %x Value %x RegValue %x",
                      __FUNCTION__,
                      egInfo[index].dssEnableReg,
                      regValue,
                      HW_RD_REG32(egInfo[index].dssEnableReg));
        }
        else
        {
            /*Do nothing*/
        }

        /* Enable Event at the Vpdma Level */
        if (VEM_INTR_TYPE_DSS_VPDMA == egInfo[index].interruptType)
        {
            clientInfo->vpdmaMask[cnt] = clientInfo->statMask[cnt];

            /* Clean any pending interrupts on this event */
            HW_WR_REG32(egInfo[index].vpdmaStatClrReg,
                        clientInfo->vpdmaMask[cnt]);

            /* VPDMA interrupt registers are read-modify-write registers */
            regValue  = HW_RD_REG32(egInfo[index].vpdmaEnableReg);
            regValue |= clientInfo->vpdmaMask[cnt];

            /* Enable interrupt */
            HW_WR_REG32(egInfo[index].vpdmaEnableReg, regValue);

            /* VPDMA mask is same as the statMask for these interrupts */
            clientInfo->vpdmaMask[cnt] = clientInfo->statMask[cnt];
        }
        if (VEM_INTR_TYPE_VIP == egInfo[index].interruptType)
        {
            /* Clean any pending interrupts on this event */
            /*Changes will take effect only if you write 0 first*/
            HW_WR_REG32(clientInfo->vpdmaStatClrReg[cnt], 0x0U);
            HW_WR_REG32(clientInfo->vpdmaStatClrReg[cnt],
                        ~(clientInfo->vpdmaMask[cnt]));

            /* VPDMA interrupt registers are read-modify-write registers */
            regValue = HW_RD_REG32(clientInfo->vpdmaEnableReg[cnt]);

            regValue &= clientInfo->vpdmaMask[cnt];

            /* Enable interrupt */
            HW_WR_REG32(clientInfo->vpdmaEnableReg[cnt], regValue);

            clientInfo->vpdmaMask[cnt] = ~(clientInfo->vpdmaMask[cnt]);
        }
        GT_4trace(VpsVemTrace,
                  GT_INFO,
                  "%s: Enable Reg %x mask %x RegValue %x",
                  __FUNCTION__,
                  egInfo[index].vpdmaEnableReg,
                  clientInfo->vpdmaMask[cnt],
                  HW_RD_REG32(egInfo[index].vpdmaEnableReg));

        /* Increment the number of clients for this event */
        egInfo[index].numClients++;
        clientInfo->interruptType[cnt] = egInfo[index].interruptType;
    }

    clientInfo->clientCb = callback;
    clientInfo->priority = priority;

    if (NULL != arg)
    {
        clientInfo->arg = arg;
    }
    else
    {
        clientInfo->arg = NULL;
    }

    return;
}

