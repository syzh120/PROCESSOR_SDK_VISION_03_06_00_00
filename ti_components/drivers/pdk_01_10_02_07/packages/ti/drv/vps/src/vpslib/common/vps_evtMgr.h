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
 *  \file   vps_evtMgr.h
 *
 *  \brief  Event Manager Header File.
 *
 *  This file contains Data Structures and Functions definitions for
 *  Event Manager. It exposes these API and data structures to its clients.
 *
 */

#ifndef VPS_EVTMGR_H_
#define VPS_EVTMGR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  enum Vem_InstId
 *  \brief Event manager instance ID.
 */
typedef enum
{
    VEM_INST_ID_VIP1 = 0,
    /**< VIP 1. */
    VEM_INST_ID_VIP2,
    /**< VIP 2. */
    VEM_INST_ID_VIP3,
    /**< VIP 3. */
    VEM_INST_ID_VPE1,
    /**< VPE. */

    /*
     * Below instances are applicable only to TI81xx platforms.
     */
    VEM_INST_ID_GENERIC,
    /**< Event manager ID common to all modules. */
    VEM_INST_ID_MAX
    /**< Max - used for error check. */
} Vem_InstId;

/**
 *  \brief Event Manager maximum number of instances for any given platform -
 *  used for memory allocation.
 */
#define VEM_MAX_INST                    (4U)

/**
 *  enum Vem_EventGroup
 *  \brief Events are grouped into multiple groups. These
 *  groups are channels interrupts, client interrupts, list complete interrupts,
 *  list notify interrupts, send interrupts sources, error interrupts and other
 *  interrupts. This enum data type defines the event groups. This enum data
 *  type is typecast to unsigned int so it must not have any negative value
 */
typedef enum
{
    VEM_EG_CHANNEL = 0,
    /**< Event Group for Channel interrupts. */
    VEM_EG_CLIENT = 7,
    /**< Event Group for VIP overflow */
    VEM_EG_LISTCOMPLETE = 9,
    /**< Event group for List complete interrupts. */
    VEM_EG_LISTNOTIFY = 10,
    /**< Event group for List notify interrupts. */
    VEM_EG_SI = 11,
    /**< Event group for Send interrupts. */
    VEM_EG_ERROR = 12,
    /**< Event group for Error interrupts. */
    VEM_EG_OTHERS = 13,
    /**< Event group for the other interrupts not included in above interrupts
     *   like FMD interrupt etc. */
    VEM_EG_OVERFLOW = 14,
    /**< Event Group for Client interrupts. */
    VEM_EG_MAX = 15
} Vem_EventGroup;

/**
 *  enum Vem_ErrorEvent
 *  \brief This enum defines the error interrupts from the VPS sub modules.
 *  VPS specs defines many error events but there are not register
 *  bits available in the register so these error events are commented out here.
 *  They will be uncommented when register bits for them will be added in the
 *  VPS main specs. This enum data type defines the event groups. This enum data
 *  type is typecast to unsigned int so it must not have any negative
 *  value.
 */
typedef enum
{
    VEM_EE_DEI = 0,
    /**< Error interrupt from DEI indicating framing error between input video
     *   data and expected framing set. */

    VEM_EE_GRPX0,
    VEM_EE_GRPX1,
    VEM_EE_GRPX2,
    /**< Following three error interrupts from graphics pipelines indicates
     *   error condition has been found in the setup of GRPX module. */

    VEM_EE_COMP,
    /**< Error interrupt from COMP module indicating error condition has been
     *   found in the setup of COMP module. */

    VEM_EE_NF_CHR_DS_CHROMA,
    /**< Following two Error interrupt from NF CHR_DS indicating
     *   error condition has been found in the setup of NF CHR_DS module. */
    /* VEM_EE_NF_CHR_DS_LUMA, */

    /* VEM_EE_VIP0_CHA_OVERFLOW, */
    /* VEM_EE_VIP0_CHB_OVERFLOW, */
    /* VEM_EE_VIP0_CHR_DS0_LUMA, */
    VEM_EE_VIP0_CHR_DS0_CHROMA,
    /* VEM_EE_VIP0_CHR_DS1_LUMA, */
    VEM_EE_VIP0_CHR_DS1_CHROMA,

    /* VEM_EE_VIP1_CHA_OVERFLOW, */
    /* VEM_EE_VIP1_CHB_OVERFLOW, */
    /* VEM_EE_VIP1_CHR_DS0_LUMA, */
    VEM_EE_VIP1_CHR_DS0_CHROMA,
    /* VEM_EE_VIP1_CHR_DS1_LUMA, */
    VEM_EE_VIP1_CHR_DS1_CHROMA,

    VEM_EE_MAX
} Vem_ErrorEvent;

/**
 *  enum Vem_OtherEvent
 *  \brief There are specific interrupts from the VPS
 *  sub-modules. This enum data type defines the event groups. This enum data
 *  type is type casted to unsigned int so it must not have any negative
 *  value
 */
typedef enum
{
    VEM_OE_FMD_DEI = 0U,
    /**< Film Mode Detection interrupt from DEI. */
    VEM_OE_CPROC,
    /**< CPROC Histogram status ready interrupt. */
    VEM_OE_VIP0,
    /**< VIP0 format change interrupt. */
    VEM_OE_VIP1,
    /**< VIP1 format change interrupt. */
    VEM_OE_HDMI_VBI_START,
    /**< DVO1 Start of vertical blanking interval interrupt. */
    VEM_OE_HDMI_VBI_END,
    /**< DVO1 End of vertical blanking interval interrupt. */
    VEM_OE_HDMI_FRAME_START,
    /**< DVO1 Start of frame interrupt. */
    VEM_OE_HDCOMP_VBI_START,
    /**< HDCOMP Start of vertical blanking interval interrupt. */
    VEM_OE_HDCOMP_VBI_END,
    /**< HDCOMP End of vertical blanking interval interrupt. */
    VEM_OE_HDCOMP_FRAME_START,
    /**< HDCOMP Start of frame interrupt. */
    VEM_OE_DVO2_VBI_START,
    /**< DVO2 Start of vertical blanking interval interrupt. */
    VEM_OE_DVO2_VBI_END,
    /**< DVO2 End of vertical blanking interval interrupt. */
    VEM_OE_DVO2_FRAME_START,
    /**< DVO2 Start of frame interrupt. */
    VEM_OE_SDVENC_VSYNC,
    /**< SDVENC VSYNC interrupt. */
    VEM_OE_MAX
} Vem_OtherEvent;

/**
 *  enum Vem_VipOverflow
 *  \brief This is to enable the interrupts from VIP parser.
 *    First two members are of slice 0, for port A and B and
 *     rest two for slice 1.
 */

typedef enum
{
    VEM_SLICE0_PARSER_INT_RAW_PORTA = 0,
    /**<VIP1 Parser port A Interrupt Status */
    VEM_SLICE0_PARSER_INT_RAW_PORTB,
    /**<VIP1 Parser port B Interrupt Status */
    VEM_SLICE1_PARSER_INT_RAW_PORTA,
    /**<VIP2 Parser port AInterrupt Status */
    VEM_SLICE1_PARSER_INT_RAW_PORTB,
    /**<VIP1 Parser port B Interrupt Status */
    VEM_VIP_PARSER_MAX
    /**< Max value */
}Vem_VipOverflow;

/**
 *  enum Vem_VipOverflow
 *  \brief Mapping for the VIP_FIQ_MASK
 *  fields. It contails only the overflow fields.
 */

typedef enum
{
    /**<These are the overflow fields with value as corrosponding
     *      bitfields*/
    VEM_ASYNC_FIFO_PRTA_OF      = 2,
    VEM_ASYNC_FIFO_PRTB_OF      = 3,
    VEM_OUTPUT_FIFO_PRTA_YUV_OF = 4,
    VEM_OUTPUT_FIFO_PRTA_ANC_OF = 6,
    VEM_OUTPUT_FIFO_PRTB_YUV_OF = 7,
    VEM_OUTPUT_FIFO_PRTB_ANC_OF = 9
}Vem_FiqMask;

/**
 *  enum Vem_Priority
 *  \brief enum for specifying the priority of the client. Event
 *  Manager always calls the callback functions of the clients in the order of
 *  priority so that highest priority callback will get executed much earlier.
 *  When client registers itself to the event manager, it also specifies the
 *  priority of itself. Event manager puts the client in the appropriate
 *  location in the linked list as per the given priority. This enum data
 *  type defines the event groups. This enum data type is typecast to
 *  unsigned int so it must not have any negative value
 */
typedef enum
{
    VEM_PRIORITY0 = 0U,
    /**< Highest. */
    VEM_PRIORITY1,
    VEM_PRIORITY2,
    VEM_PRIORITY3,
    VEM_PRIORITY4
    /**< Lowest. */
} Vem_Priority;

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
typedef void (*Vem_ClientCbFxn)(const UInt32 *event,
                                UInt32        numEvents,
                                Ptr           arg);

typedef void (*Vem_VipCbFxn)(void);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vem_InstParams
 *  \brief Structure containing instance specific parameters used at the init.
 */
typedef struct
{
    UInt32 instId;
    /**< VEM Instance ID. */
    UInt32 irqNumber;
    /**< IRQ number at CPU level INTC. */
    UInt32 intcNum;
    /**< Defines the INTC number of the INTC to be used. */
    UInt32 intcBaseAddr;
    /**< Top level INTC base address of the instance. */
    UInt32 vpdmaBaseAddr;
    /**< VPDMA base address of the instance. */
} Vem_InstParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Vem_init
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
Int32 Vem_init(UInt32 numInst, const Vem_InstParams *instPrms);

/**
 *  Vem_deInit
 *  \brief This function de-initializes the event manager.
 *
 *  \return             Returns 0 on success else returns error value
 */
Int32 Vem_deInit(void);

/**
 *  Vem_register
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
void *Vem_register(Vem_InstId      instId,
                   Vem_EventGroup  eventGroup,
                   const UInt32   *event,
                   UInt32          numEvents,
                   Vem_Priority    priority,
                   Vem_ClientCbFxn callback,
                   void           *arg);

/**
 *  Vem_unRegister
 *  \brief Function to un-register callback from the event manager. It removes
 *  node from the linked list and frees up memory allocated to the node
 *  and client info structure. It takes handle to the callback and
 *  returns status of the whether callback is removed.
 *
 *  \param handle           Handle to the callback
 *  \return                 Returns 0 on success else returns error value
 */
Int32 Vem_unRegister(void *handle);

#ifdef __cplusplus
}
#endif

#endif  /* End of #ifndef VPS_EVTMGR_H_ */
