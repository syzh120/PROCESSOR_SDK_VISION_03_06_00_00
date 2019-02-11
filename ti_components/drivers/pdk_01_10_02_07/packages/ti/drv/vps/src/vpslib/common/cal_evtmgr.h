/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015-2016
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
 *  \file cal_evtmngt.h
 *
 *  \brief CAL Event Manager
 *  This file implements functions to to handle CAL interrupts,
 *  It also provides mechanism to get callback on CAL events
 *
 */

#ifndef VPS_CAL_EVENT_MNGR_H_
#define VPS_CAL_EVENT_MNGR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Event Manager maximum number of instances for any given platform -
 *  used for memory allocation. This should come from SOC file TODO
 */
#define CAL_EM_MAX_INST                    (2U)

/**
 *  \brief Event manager instance ID.
 */
typedef enum calemInstId
{
    CAL_EM_INST_ID_CAL0 = 0x0,
    /**< Interrupt 0 */
    CAL_EM_INST_ID_MAX = 0x1,
    /**< Max - used for error check. */
    CAL_EM_INST_ID_FORCE_INT = 0x7FFFFFFF
    /**< This will ensure enum is not packed, will
     *always be contained in int */
} calemInstId_t;

/**
 *  \brief All ISS Events are logically grouped under one of the following
 *          categories.
 */
typedef enum calemEventGroup
{
    CAL_EM_EG_BYS = 0,
    /**< Event Group for BYS */
    CAL_EM_EG_CAL = 1,
    /**< Event Group for CAL */
    CAL_EM_EG_LVDSRX0 = 2,
    /**< Event Group for LVDSRX0 */
    CAL_EM_EG_LVDSRX1 = 3,
    /**< Event Group for LVDSRX1 */
    CAL_EM_EG_LVDSRX2 = 4,
    /**< Event Group for LVDSRX2 */
    CAL_EM_EG_LVDSRX3 = 5,
    /**< Event Group for LVDSRX3 */

    /* Events group below do not directly map to ISS top level event source bit
        positions. ISS_HL_XXX (XXX = IRQENABLE_SET/IRQENABLE_CLR/STATUS)
        Event Manager takes care of handling these separately. */

    CAL_EM_EG_CAL_PPI0_CSI2 = 6,
    /**< CSI2 specific events refer calemCalEvents_t for events supported
            in this group */
    CAL_EM_EG_CAL_PPI1_CSI2 = 7,
    /**< CSI2 specific events refer calemCalEvents_t for events supported
            in this group */
    CAL_EM_EG_MAX = 8,
    /**< Should be the last number */
    CAL_EM_EG_FORCE_INT = 0x7FFFFFFF
    /**< This will ensure enum is not packed, will always be
     *contained in int */
} calemEventGroup_t;

/**
 *  \brief Enums for CAL internal modules,
 *         Mainly used for getting base addresses for internal modules
 */
typedef enum calemModules
{
    CAL_EM_MODULE_CAL       = 0,
    /**< Main CAL Module */
    CAL_EM_MODULE_LVDSRX    = 1,
    /**< LVDS Rx module */
    CAL_EM_MODULE_MAX       = 2,
    /**< Max Modules */
    CAL_EM_MODULE_FORCE_INT = 0x7FFFFFFF
    /**< This will ensure enum is not packed, will
     *always be contained in int */
} calemModules_t;


/**
 *  \brief Possible LVDS events, expected to be used when event group is
 *          CAL_EM_EG_LVDSRX0.
 */
typedef enum calemLvdsrxEvents
{
    CAL_EM_LVDSRX_EVENT_CAM1_SOF = 0,
    /**< Start of frame timing */
    CAL_EM_LVDSRX_EVENT_CAM1_ERR_EOX = 1,
    /**< EOX not received */
    CAL_EM_LVDSRX_EVENT_CAM1_ERR_SOV = 2,
    /**< Unexpected SOV */
    CAL_EM_LVDSRX_EVENT_CAM1_ERR_EOL = 3,
    /**< unexpected EOL */
    CAL_EM_LVDSRX_EVENT_CAM1_ERR_EOF = 4,
    /**< unexpected EOF */
    CAL_EM_LVDSRX_EVENT_CAM1_ERR_SOL = 5,
    /**< unexpected SOL */
    CAL_EM_LVDSRX_EVENT_CAM1_ERR_SOF = 6,
    /**< unexpected SOF */
    CAL_EM_LVDSRX_EVENT_CAM1_ERR_CRC = 7,
    /**< CRC Error */
    CAL_EM_LVDSRX_EVENT_CAM1_ERR_TIMEOUT = 8,
    /**< sync detected timeout reached */
    CAL_EM_LVDSRX_EVENT_FORCE_INT = 0x7FFFFFFF
    /**< This will ensure enum is not packed, will
     *always be contained in int */
} calemLvdsrxEvents_t;

/**
 *  \brief Possible CAL events, expected to be used when event group is
 *          CAL_EM_EG_CAL
 */
typedef enum calemEvents
{
    CAL_EM_EVENT_RDMA_END          = 0,
    /**< Event triggered when CAL read is completed */
    CAL_EM_EVENT_BYSIN_OVR         = 1,
    /**< Event triggered when CAL BYS IN overflows */
    CAL_EM_EVENT_VPORT_EOF         = 2,
    /**< Event triggered when CAL End Of Frame seen at VPORT port */
    CAL_EM_EVENT_BYSOUT_EOF        = 3,
    /**< Event triggered when CAL End Of Frame seen at BYS_OUT port */
    CAL_EM_EVENT_BYSIN_SOF         = 4,
    /**< Event triggered when CAL Start Of Frame seen at BYS_IN port */
    CAL_EM_EVENT_BYSIN_EOF         = 5,
    /**< Event triggered when CAL End Of Frame seen at BYS_OUT port */
    CAL_EM_EVENT_OCPO_ERR          = 6,
    /**< Internal write failure error */
    CAL_EM_EVENT_RDMA_CIRC         = 7,
    /**< Event triggered when configured number of lines received into circular
            buffer. */
    CAL_EM_EVENT_LINE_NUMBER       = 8,
    /**< Event triggered when configured number of lines is received by CAL */
    CAL_EM_EVENT_BYSOUT_VBLANK_END = 9,
    /**< Event triggered when at the end of VBLANK period on BYS_OUT port */
    CAL_EM_EVENT_PPIO              = 16,
    /**< This is aggregate event, which when set indicates that there 1 or more
            events CSI2 events. Please DO NOT USE this.
            Use event group CAL_EM_EG_CAL_CSI2 and events calemCalEvents_t*/
    CAL_EM_EVENT_PPIO_VC           = 17,
    /**< This is aggregate event, which when set indicates that there 1 or more
            events CSI2 events. Please DO NOT USE this.
            Use event group CAL_EM_EG_CAL_CSI2 and events calemCalEvents_t*/
    CAL_EM_EVENT_PPIO1             = 24,
    /**< Not applicable for now */
    CAL_EM_EVENT_PPIO1_VC          = 25,
    /**< Not applicable for now */

    /**< Event triggered when DMA Write completes */
    CAL_EM_EVENT_WDMA_END0  = 32 + 0,
    CAL_EM_EVENT_WDMA_END1  = 32 + 1,
    CAL_EM_EVENT_WDMA_END2  = 32 + 2,
    CAL_EM_EVENT_WDMA_END3  = 32 + 3,
    CAL_EM_EVENT_WDMA_END4  = 32 + 4,
    CAL_EM_EVENT_WDMA_END5  = 32 + 5,
    CAL_EM_EVENT_WDMA_END6  = 32 + 6,
    CAL_EM_EVENT_WDMA_END7  = 32 + 7,
    CAL_EM_EVENT_WDMA_CICR0 = 32 + 16,
    CAL_EM_EVENT_WDMA_CICR1 = 32 + 17,
    CAL_EM_EVENT_WDMA_CICR2 = 32 + 18,
    CAL_EM_EVENT_WDMA_CICR3 = 32 + 19,
    CAL_EM_EVENT_WDMA_CICR4 = 32 + 20,
    CAL_EM_EVENT_WDMA_CICR5 = 32 + 21,
    CAL_EM_EVENT_WDMA_CICR6 = 32 + 22,
    CAL_EM_EVENT_WDMA_CICR7 = 32 + 23,

    /**< Event triggered when DMA read starts */
    CAL_EM_EVENT_WDMA_START0 = 64 + 0,
    CAL_EM_EVENT_WDMA_START1 = 64 + 1,
    CAL_EM_EVENT_WDMA_START2 = 64 + 2,
    CAL_EM_EVENT_WDMA_START3 = 64 + 3,
    CAL_EM_EVENT_WDMA_START4 = 64 + 4,
    CAL_EM_EVENT_WDMA_START5 = 64 + 5,
    CAL_EM_EVENT_WDMA_START6 = 64 + 6,
    CAL_EM_EVENT_WDMA_START7 = 64 + 7,

    /**< CSI3 Specific, not applicable for now !!! */
    CAL_EM_EVENT_LL_SOF0     = 96 + 0,
    CAL_EM_EVENT_LL_SOF1     = 96 + 1,
    CAL_EM_EVENT_LL_SOF2     = 96 + 2,
    CAL_EM_EVENT_LL_SOF3     = 96 + 3,
    CAL_EM_EVENT_ATTR_CTRL0  = 96 + 4,
    CAL_EM_EVENT_ATTR_CTRL1  = 96 + 5,
    CAL_EM_EVENT_ATTR_CTRL2  = 96 + 6,
    CAL_EM_EVENT_ATTR_CTRL3  = 96 + 7,
    CAL_EM_EVENT_PIX_CTRL0   = 96 + 8,
    CAL_EM_EVENT_PIX_CTRL1   = 96 + 9,
    CAL_EM_EVENT_PIX_CTRL2   = 96 + 10,
    CAL_EM_EVENT_PIX_CTRL3   = 96 + 11,
    CAL_EM_EVENT_TX_OVR0     = 96 + 12,
    CAL_EM_EVENT_TX_OVR1     = 96 + 13,
    CAL_EM_EVENT_TX_OVR2     = 96 + 14,
    CAL_EM_EVENT_TX_OVR3     = 96 + 15,
    CAL_EM_EVENT_LL_INVALID0 = 96 + 16,
    CAL_EM_EVENT_LL_INVALID1 = 96 + 17,
    CAL_EM_EVENT_LL_INVALID2 = 96 + 18,
    CAL_EM_EVENT_LL_INVALID3 = 96 + 19,
    CAL_EM_EVENT_LL_EOF0     = 96 + 20,
    CAL_EM_EVENT_LL_EOF1     = 96 + 21,
    CAL_EM_EVENT_LL_EOF2     = 96 + 22,
    CAL_EM_EVENT_LL_EOF3     = 96 + 23,
    CAL_EM_EVENT_LL_SOF4     = 218 + 0,
    CAL_EM_EVENT_LL_SOF5     = 218 + 1,
    CAL_EM_EVENT_LL_SOF6     = 218 + 2,
    CAL_EM_EVENT_LL_SOF7     = 218 + 3,
    CAL_EM_EVENT_ATTR_CTRL4  = 218 + 4,
    CAL_EM_EVENT_ATTR_CTRL5  = 218 + 5,
    CAL_EM_EVENT_ATTR_CTRL6  = 218 + 6,
    CAL_EM_EVENT_ATTR_CTRL7  = 218 + 7,
    CAL_EM_EVENT_PIX_CTRL4   = 218 + 8,
    CAL_EM_EVENT_PIX_CTRL5   = 218 + 9,
    CAL_EM_EVENT_PIX_CTRL6   = 218 + 10,
    CAL_EM_EVENT_PIX_CTRL7   = 218 + 11,
    CAL_EM_EVENT_TX_OVR4     = 218 + 12,
    CAL_EM_EVENT_TX_OVR5     = 218 + 13,
    CAL_EM_EVENT_TX_OVR6     = 218 + 14,
    CAL_EM_EVENT_TX_OVR7     = 218 + 15,
    CAL_EM_EVENT_LL_INVALID4 = 218 + 16,
    CAL_EM_EVENT_LL_INVALID5 = 218 + 17,
    CAL_EM_EVENT_LL_INVALID6 = 218 + 18,
    CAL_EM_EVENT_LL_INVALID7 = 218 + 19,
    CAL_EM_EVENT_LL_EOF4     = 218 + 20,
    CAL_EM_EVENT_LL_EOF5     = 218 + 21,
    CAL_EM_EVENT_LL_EOF6     = 218 + 22,
    CAL_EM_EVENT_LL_EOF7     = 218 + 23,

    CAL_EM_EVENT_FORCE_INT = 0x7FFFFFFF
                              /**< This will ensure enum is not packed, will
                               *always be contained in int */
} calemCalEvents_t;


/**
 *  \brief enum for specifying the priority of the client. Event
 *  Manager always calls the callback functions of the clients in the order of
 *  priority so that highest priority callback will get executed much earlier.
 *  When client registers itself to the event manager, it also specifies the
 *  priority of itself. Event manager puts the client in the appropriate
 *  location in the linked list as per the given priority. This enum data
 *  type defines the event groups. This enum data type is typecast to
 *  unsigned int so it must not have any negative value
 */
typedef enum calemPriority
{
    CAL_EM_PRIORITY0 = 0U,
    /**< Highest. Typically used for error handling */
    CAL_EM_PRIORITY1,
    CAL_EM_PRIORITY2,
    CAL_EM_PRIORITY3,
    CAL_EM_PRIORITY4,
    /**< Lowest. For normal operations, frame completion, etc... */
    CAL_EM_PRIORITY_FORCE_INT
    /**< This will ensure enum is not packed, will
     *always be contained in int */
} calemPriority_t;

/**
 *  \brief This typedef defines the VPS Event manager callback function
 *  prototype. Client registers this callback with the event manager and when
 *  event occurs, event manager calls this callback.
 *
 *  \param  event       This is an array of events occurred when interrupt came.
 *                      Event manager passes this list to the client.
 *  \param  numEvents   This tells number of events occurred.
 *  \param  arg         Client's Private Data
 */
typedef void (*calemClientCbFxn)(const UInt32 *event,
                                 UInt32        numEvents,
                                 Ptr           arg);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct calemInitParams
{
    calemInstId_t   instId;
    /**< Cal Instance Id */
    uint32_t        irqNum;
    /**< irq number */
    uint32_t        baseAddress[CAL_EM_MODULE_MAX];
    /**< Base Addresses for different modules */
} calemInitParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  \brief This function initializes event manager. It creates the semaphore,
 *  initializes pointers and sets the memory to zero. It also register ISR
 *  for the VPS interrupt. It returns pass or fail based on initialization
 *  passed or failed.
 *
 *  \param numInst      Number of VEM Instances and number of
 *                      array elements in the second argument.
 *  \param instPrms     Instance specific parameters.
 *
 *  \return             Returns 0 on success else returns error value
 */
int32_t Vps_calEmInit(uint32_t numInst, const calemInitParams_t *initPrms);

/**
 *  \brief This function de-initializes the event manager.
 *
 *  \return             Returns 0 on success else returns error value
 */
int32_t Vps_calEmDeInit(void);

/**
 *  \brief Function to register callback to the Event Manager. Client passes
 *  the set of events of a group with the callback and priority and
 *  this function adds a new node at the appropriate position as per
 *  the priority in the list of nodes. It also stores the list of
 *  events, registers for the events and masks in the the client info
 *  structure. It returns handle of the registered callback.
 *
 *  \param instId           Instance ID to register with.
 *  \param eventGroup       Group of the event passed in the second argument
 *  \param event            List of event for which client requested callback
 *  \param numEvents        Number of events in the second argument
 *  \param priority         Priority of this callback
 *  \param callback         Callback function of the client
 *  \param arg              Private Data of the client
 *
 *  \return                 It returns the handle of the registered callback.
 */
void *Vps_calEmRegister(calemInstId_t     instId,
                        calemEventGroup_t eventGroup,
                        const uint32_t   *event,
                        uint32_t          numEvents,
                        calemPriority_t   priority,
                        calemClientCbFxn  callback,
                        void             *arg);

/**
 *  \brief Function to un-register callback from the event manager. It removes
 *  node from the linked list and frees up memory allocated to the node
 *  and client info structure. It takes handle to the callback and
 *  returns status of the whether callback is removed.
 *
 *  \param handle           Handle to the callback
 *  \return                 Returns 0 on success else returns error value
 */
int32_t Vps_calEmUnRegister(void *handle);

int32_t Vps_calEmDisable(void *handle);

int32_t Vps_calEmEnable(void *handle);

int32_t Vps_calEmDisableAll(void *handle);

#ifdef __cplusplus
}
#endif

#endif  /* _VPS_IRQ_EVENT_MNGR_H_ */
