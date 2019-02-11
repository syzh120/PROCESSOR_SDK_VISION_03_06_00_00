/*
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 *  @file       ti/sdo/fc/edma3/edma3_config.h
 *
 *  @brief      EDMA3 Interface Definitions - Meta-config module to manage
 *              EDMA3 resources for all Framework Component modules that
 *              will use them.
 */

/**
 *  @defgroup   ti_sdo_fc_edma3_EDMA3 EDMA3
 *
 *              EDMA3 module is a Meta-config module that manages all the EDMA3
 *              resources including DMA channels, QDMA channels, PaRams, Tccs
 *              required by various users of the EDMA3 device.
 *              It also supports the notion of scratch sharing of the resources,
 *              and allows for distribution of these resources into various
 *              scratch groups for allocation to algorithms.
 *              Internally it uses the EDMA3 Low Level Driver package for
 *              managing the resources.
 *
 *  @remark     For additional information on the EDMA3 Low Level Driver, refer  *              to its documentation.
 */

#ifndef ti_sdo_fc_edma3_EDMA3_CONFIG
#define ti_sdo_fc_edma3_EDMA3_CONFIG

/** @ingroup    ti_sdo_fc_edma3_EDMA3 */
/*@{*/

#include <ti/xdais/xdas.h>
#include <ti/sdo/fc/ires/iresman.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief       Name to pass to Diags_setMask() to enable logging for EDMA3
 *              functions. For example,
 *                  Diags_setMask(EDMA3_MODNAME"+EX1234567");
 *              turns on all Log statements in this module.
 *              Diags_setMask() must be called after EDMA3_init() to take
 *              effect.
 */
#define EDMA3_MODNAME "ti.sdo.fc.edma3"

#define EDMA3_SOK           0           /**< EDMA3 Resource Manager result OK*/


/**
 * @brief       EDMA3 Error Codes base define
 */
#define EDMA3_E_BASE        (-155)      /**< EDMA3 Error Codes base define */

/**
 * Resource Manager Object Not Deleted yet.
 * So the object cannot be created.
 */
#define EDMA3_E_OBJ_NOT_DELETED                  (EDMA3_E_BASE)

/**
 * Resource Manager Object Not Closed yet.
 * So the object cannot be deleted.
 */
#define EDMA3_E_OBJ_NOT_CLOSED               (EDMA3_E_BASE-1)

/**
 * Resource Manager Object Not Opened yet
 * So the object cannot be closed.
 */
#define EDMA3_E_OBJ_NOT_OPENED                  (EDMA3_E_BASE-2)

/** Invalid Parameter passed to API */
#define EDMA3_E_INVALID_PARAM                   (EDMA3_E_BASE-3)

/** Resource requested for freeing is already free */
#define EDMA3_E_RES_ALREADY_FREE                (EDMA3_E_BASE-4)

/** Resource requested for allocation/freeing is not owned */
#define EDMA3_E_RES_NOT_OWNED                   (EDMA3_E_BASE-5)

/** Resource is not available */
#define EDMA3_E_SPECIFIED_RES_NOT_AVAILABLE     (EDMA3_E_BASE-6)

/** No Resource of specified type is available */
#define EDMA3_E_ALL_RES_NOT_AVAILABLE           (EDMA3_E_BASE-7)

/** Invalid State of EDMA3 Obj */
#define EDMA3_E_INVALID_STATE                   (EDMA3_E_BASE-8)

/** Maximum no of Res Mgr Instances already Opened */
#define EDMA3_E_MAX_INST_OPENED              (EDMA3_E_BASE-9)

/**
 * More than one Res Mgr Master Instance NOT supported.
 * Only 1 master can exist.
 */
#define EDMA3_E_MASTER_ALREADY_EXISTS         (EDMA3_E_BASE-10)

/** Callback function already registered. */
#define EDMA3_E_CALLBACK_ALREADY_REGISTERED      (EDMA3_E_BASE-11)

/** Semaphore related error */
#define EDMA3_E_SEMAPHORE                        (EDMA3_E_BASE-12)

/** Hardware feature NOT supported */
#define EDMA3_E_FEATURE_UNSUPPORTED              (EDMA3_E_BASE-13)

/** EDMA3 Resource NOT allocated */
#define EDMA3_E_RES_NOT_ALLOCATED                (EDMA3_E_BASE-14)

/** EDMA3 Memory allocation failed */
#define EDMA3_E_MEMORY                           (EDMA3_E_BASE-15)



#define EDMA3_GTNAME "ti.sdo.fc.edma3"   /**< Name to identify the GT module*/

#define EDMA3_MAXGROUPS     20           /**< Maximum number of groups for
                                            sharing EDMA3 resources. */

#define EDMA3_PHYSICALID    0            /**< Physical ID identifying the EDMA3
                                            device being managed */

/*
 * The next several #defines are _typically_ defined by EDMA3 LLD headers.
 * In cases where the EDMA3 LLD isn't present (e.g. devices not supported by
 * EDMA3 LLD), we define them here.
 */
#ifndef EDMA3_MAX_DMA_CH
#define EDMA3_MAX_DMA_CH    (64u)        /**< Maximum DMA channels supported
                                            by the EDMA3 Controller */
#endif

#ifndef EDMA3_MAX_QDMA_CH
#define EDMA3_MAX_QDMA_CH   (8u)         /**< Maximum QDMA channels supported
                                            by the EDMA3 Controller */
#endif

#ifndef EDMA3_MAX_PARAM_SETS
#define EDMA3_MAX_PARAM_SETS (512u)      /**< Maximum PaRAM Sets supported by
                                            the EDMA3 Controller */
#endif

#ifndef EDMA3_MAX_TCC
#define EDMA3_MAX_TCC       (64u)        /**< Maximum TCCs (Interrupt Channels)
                                            supported by the EDMA3 Controller */
#endif

#ifndef EDMA3_MAX_EVT_QUE
#define EDMA3_MAX_EVT_QUE   (8u)         /**< Maximum Event Queues supported by                                             the EDMA3 Controller */
#endif

#ifndef EDMA3_MAX_TC
#define EDMA3_MAX_TC        (8u)         /**< Maximum Transfer Controllers
                                            supported by the EDMA3 Controller */
#endif

#ifndef EDMA3_MAX_REGIONS
#define EDMA3_MAX_REGIONS   (8u)         /**< Maximum Shadow Regions supported
                                            by the EDMA3 Controller */
#endif

/**
 * Maximum Words (4-bytes region) required for the book-keeping information
 * specific to the maximum possible DMA channels.
 */
#ifndef EDMA3_MAX_DMA_CHAN_DWRDS
#define EDMA3_MAX_DMA_CHAN_DWRDS                (EDMA3_MAX_DMA_CH / 32u)
#endif

/**
 * Maximum Words (4-bytes region) required for the book-keeping information
 * specific to the maximum possible QDMA channels.
 */
#ifndef EDMA3_MAX_QDMA_CHAN_DWRDS
#define EDMA3_MAX_QDMA_CHAN_DWRDS               (1u)
#endif

/**
 * Maximum Words (4-bytes region) required for the book-keeping information
 * specific to the maximum possible PaRAM Sets.
 */
#ifndef EDMA3_MAX_PARAM_DWRDS
#define EDMA3_MAX_PARAM_DWRDS                   (EDMA3_MAX_PARAM_SETS / 32u)
#endif

/**
 * Maximum Words (4-bytes region) required for the book-keeping information
 * specific to the maximum possible TCCs.
 */
#ifndef EDMA3_MAX_TCC_DWRDS
#define EDMA3_MAX_TCC_DWRDS                     (EDMA3_MAX_TCC / 32u)
#endif

/**
 * Defines that identify different types of memory writes supported by EDMA3
 * Used to identify the event queue number that will be used to write to
 * a particular memory.
 */
#define EDMA3_INTMEMQ0          0

#define EDMA3_INTMEMQ1          1

#define EDMA3_INTMEMQ2          2

#define EDMA3_EXTMEMQ0          3

#define EDMA3_EXTMEMQ1          4

#define EDMA3_EXTMEMQ2          5

#define EDMA3_OTHERQ0           6

#define EDMA3_OTHERQ1           7

/**
 * @brief       Result of calls to EDMA3 APIs
 */
typedef int     EDMA3_Result;

/**
 * @brief       EDMA3 Resource Manager Handle.
 *              Passed as argument to other Resource Manager APIs.
 */
typedef void    *EDMA3_Handle;


typedef void    *EDMA3_SemHandle;

/**
 * @brief       Used to specify any available Resource Id
 *              (EDMA3_ResDesc.resId)
 */
#define EDMA3_RES_ANY            (1010u)


/**
 * @brief       EDMA3 Resource Type
 */
typedef enum
{
    EDMA3_RES_DMA_CHANNEL        = 1,        /**< DMA Channel resource */

    EDMA3_RES_QDMA_CHANNEL       = 2,        /**< QDMA Channel resource*/

    EDMA3_RES_TCC                = 3,        /**< TCC resource*/

    EDMA3_RES_PARAM_SET          = 4         /**< ParameterRAM Set resource*/

} EDMA3_ResType;

/** Handle to a resource granted */
typedef struct EDMA3_ResDesc {

    unsigned int resId;                 /*  Id of the resource requested */

    EDMA3_ResType type;              /*  Type of the resource requested */

} EDMA3_ResDesc;

/*
 *  @brief          Use this enum to get the physical address of the
 *                  Channel Controller or the Transfer Controller.
 *                  The address returned could be used by the advanced
 *                  users to set/get some specific registers direclty.
 */
typedef enum
{
    /** Channel Controller Physical Address */
    EDMA3_CC_PHY_ADDR = 0,
    /** Transfer Controller 0 Physical Address */
    EDMA3_TC0_PHY_ADDR,
    /** Transfer Controller 1 Physical Address */
    EDMA3_TC1_PHY_ADDR,
    /** Transfer Controller 2 Physical Address */
    EDMA3_TC2_PHY_ADDR,
    /** Transfer Controller 3 Physical Address */
    EDMA3_TC3_PHY_ADDR,
    /** Transfer Controller 4 Physical Address */
    EDMA3_TC4_PHY_ADDR,
    /** Transfer Controller 5 Physical Address */
    EDMA3_TC5_PHY_ADDR,
    /** Transfer Controller 6 Physical Address */
    EDMA3_TC6_PHY_ADDR,
    /** Transfer Controller 7 Physical Address */
    EDMA3_TC7_PHY_ADDR
} EDMA3_Cntrlr_PhyAddr;


/**
 *  @brief      Init-time Configuration structure for EDMA3
 *              controller, to provide Global SoC specific Information.
 *              For e.g. number of DMA/QDMA channels,
 *              number of PaRAM sets, TCCs, event queues, transfer controllers,  *              base addresses of CC global registers and TC registers,
 *              interrupt number for EDMA3 transfer completion, CC error, event  *              queues' priority, watermark threshold level etc.
 */
typedef struct EDMA3_GblConfigParams {

    unsigned int        numDmaChannels;     /**< Number of DMA Channels
                                            supported by the underlying EDMA3
                                            Controller. */

    unsigned int        numQdmaChannels;    /**< Number of QDMA Channels
                                            supported by underlying EDMA3
                                            Controller */

    unsigned int        numTccs;            /**< Number of Interrupt Channels
                                            supported by the underlying EDMA3
                                            Controller */

    unsigned int        numPaRAMSets;       /**< Number of PaRAM Sets supported
                                            by the underlying EDMA3 Controller*/

    unsigned int        numEvtQueue;        /** Number of Event Queues in the
                                            underlying EDMA3 Controller */

    unsigned int        numTcs;             /**< Number of Transfer Controllers
                                            (TCs) underlying EDMA3 Controller */

    unsigned int        numRegions;         /**< Number of Regions in the
                                            underlying EDMA3 Controller  */

    /**
     * @brief       Channel mapping existence
     *              A value of 0 (No channel mapping) implies that there is
     *              fixed association between a DMA channel and a PaRAM Set
     *              A value of 1 implies the presence of DCHMAP registers for
     *              the DMA channels and hence the flexibility of associating
     *              any DMA channel to any PaRAM Set. In other words, ANY PaRAM      *              Set can be used for ANY DMA channel (like QDMA Channels).
     */
    unsigned int      dmaChPaRAMMapExists;

    unsigned int      memProtectionExists; /**< Existence of memory protection
                                             feature */

    void                *globalRegs;         /**< Base address of EDMA3 CC
                                             memory mapped registers. */

    void                *tcRegs[EDMA3_MAX_TC];
                                            /**< Base address of EDMA3 TCs
                                               memory mapped registers. */

    unsigned int        xferCompleteInt;    /**< EDMA3 transfer completion
                                            interrupt line (could be different
                                            for ARM and DSP) */

    unsigned int        ccError;            /**< EDMA3 CC error interrupt line
                                            (could be different for ARM and
                                            DSP) */

    unsigned int        tcError[EDMA3_MAX_TC];
                                            /** EDMA3 TCs error interrupt line
                                            (could be different for ARM and
                                            DSP) */

    /**
     * @brief       EDMA3 TC priority setting
     *              User can program the priority of the Event Queues
     *              at a system-wide level.  This means that the user can set
     *              priority of an IO initiated by either of the TCs
     *              (Transfer Controllers) relative to IO initiated by the
     *              other bus masters on the device (ARM, DSP, USB, etc)
     */
    unsigned int        evtQPri [EDMA3_MAX_EVT_QUE];

    /**
     * @brief       Event Queues Watermark Levels
     *              To Configure the Threshold level of number of events
     *              that can be queued up in the Event queues. EDMA3CC error
     *              register (CCERR) will indicate whether or not at any
     *              instant of time the number of events queued up in any of
     *              the event queues exceeds or equals the threshold/watermark
     *              value that is set in the queue watermark threshold register      *              (QWMTHRA).
     */
    unsigned int        evtQueueWaterMarkLvl [EDMA3_MAX_EVT_QUE];

    /**
     * @brief       Default Burst Size (DBS) of TCs.
     *              An optimally-sized command is defined by the transfer
     *              controller default burst size (DBS). Different TCs can have      *              different DBS values. It is defined in Bytes.
     */
    unsigned int        tcDefaultBurstSize[EDMA3_MAX_TC];

    /**
     * @brief       Mapping from DMA channels to PaRAM Sets
     *              If channel mapping exists (DCHMAP registers are present),
     *              this array stores the respective PaRAM Set for each DMA
     *              channel. User can initialize each array member with a
     *              specific PaRAM Set or with EDMA3_DRV_CH_NO_PARAM_MAP.
     *              If channel mapping doesn't exist, it is of no use as the
     *              EDMA3 RM automatically uses the right PaRAM Set for that
     *              DMA channel. Useful only if mapping exists, else of no use.
     */
    unsigned int        dmaChannelPaRAMMap [EDMA3_MAX_DMA_CH];

     /**
      * @brief      Mapping from DMA channels to TCCs
      *             This array stores the respective TCC (interrupt channel)
      *             for each DMA channel. User can initialize each array member       *             with a specific TCC or with EDMA3_DRV_CH_NO_TCC_MAP.
      *             This specific TCC code will be returned when the transfer is      *             completed on the mapped DMA channel.
      */
     unsigned int       dmaChannelTccMap [EDMA3_MAX_DMA_CH];

    /**
     * @brief       Mapping from DMA channels to Hardware Events
     *              Each bit in this array corresponds to one DMA channel and
     *              tells whether this DMA channel is tied to any peripheral.
     *              That is whether any peripheral can send the synch event on
     *              this DMA channel or not. 1 means the channel is tied to
     *              some peripheral; 0 means it is not.
     *              DMA channels which are tied to some peripheral are RESERVED      *              for that peripheral only. They are not allocated when user
     *              asks for 'ANY' DMA channel.
     *              All channels need not be mapped, some can be free also.
     */
    unsigned int        dmaChannelHwEvtMap [EDMA3_MAX_DMA_CHAN_DWRDS];

} EDMA3_GblConfigParams;

/**
 * @brief           Init-time Region Specific Configuration structure for
 *                  EDMA3 , to provide region specific Information.
 *                  Used to specify which EDMA3 resources are owned and
 *                  reserved by the EDMA3 instance. This configuration
 *                  structure is shadow region specific and will be provided by  *                  the user at run-time.
 */
typedef struct
{
    unsigned int        ownPaRAMSets[EDMA3_MAX_PARAM_DWRDS];
                            /**< PaRAM Sets owned by the EDMA3 RM Instance. */

    unsigned int        ownDmaChannels[EDMA3_MAX_DMA_CHAN_DWRDS];
                            /**< DMA Channels owned by the EDMA3 RM Instance. */

    unsigned int        ownQdmaChannels[EDMA3_MAX_QDMA_CHAN_DWRDS];
                            /**< QDMA Channels owned by the EDMA3 RM Instance.*/

    unsigned int        ownTccs[EDMA3_MAX_TCC_DWRDS];
                            /**< TCCs owned by the EDMA3 RM Instance. */

    /**
     * @brief       Reserved PaRAM Sets
     */
    unsigned int        resvdPaRAMSets[EDMA3_MAX_PARAM_DWRDS];

    /**
     * @brief       Reserved DMA channels
     */
    unsigned int        resvdDmaChannels[EDMA3_MAX_DMA_CHAN_DWRDS];

    /**
     * @brief       Reserved QDMA channels
     */
    unsigned int        resvdQdmaChannels[EDMA3_MAX_QDMA_CHAN_DWRDS];

    /**
     * @brief       Reserved TCCs
     */
    unsigned int        resvdTccs[EDMA3_MAX_TCC_DWRDS];

} EDMA3_InstanceInitConfig;



/**
 *  @brief      The module configuration structure for EDMA3 implementation.
 *              It is set at design time by the system integrator to allow
 *              setting up of the EDMA3 Low Level Resource Manager for acquiring
 *              EDMA3 resources.
 *
 *  @remarks    Typically, system integrators configure these settings using
 *              XDC config scripts.  System integrators that use that method
 *              of configuration can ignore this structure definition.  It's
 *              auto-generated during the config step by the XDC Tools.
 */
typedef struct EDMA3_Params {

    /**
     *  @brief      Region Number of the region that is being configured by this
     *              Module
     */
    unsigned int   regionId;

    /**
     *  @brief      Boolean value indicating if initialization of EDMA3 Global
     *              Registers should be handled by this module
     */
    Bool globalInit;

    /**
     *  @brief      Function used to allocate Memory required by this module
     */
    IRESMAN_PersistentAllocFxn *  allocFxn;

    /**
     *  @brief      Function used to free Memory used by this module
     */
    IRESMAN_PersistentFreeFxn *  freeFxn;

    /**
     *  @brief      Optional configuration information used to initialize
     *              the SOC specific EDMA3 resource information required by
     *              the EDMA3 Low Level Resource Manager.
     */
    EDMA3_GblConfigParams * globalConfig;

    /**
     *  @brief      Optional configuration information used to initialize
     *              the region specific EDMA3 resource information required by
     *              the EDMA3 Low Level Resource Manager.
     */
    EDMA3_InstanceInitConfig * regionConfig;

    /**
     *  @brief      Number of Scratch Groups into which the EDMA3 resources
     *              will be distributed.
     */
    Int numGroups;

    /**
     *  @brief      Boolean value indicating in Contiguous paRams are required
     *              to be allocated to the Scratch Groups
     */
    Bool contigParams;

} EDMA3_Params;

/**
 *  @brief      Scratch Group specific configuration information for the EDMA3
 *              module. It is set at design time by the system integrator to
 *              allow sharing of the EDMA3 resources among scratch groups.
 *
 *  @remarks    Typically, system integrators configure these settings using
 *              XDC config scripts.  System integrators that use that method
 *              of configuration can ignore this structure definition.  It's
 *              auto-generated during the config step by the XDC Tools.
 */
/*@{*/

extern __FAR__ Uns ti_sdo_fc_edma3_EDMA3_physicalId;

extern __FAR__ Uns ti_sdo_fc_edma3_Settings_defaultQ;

/**
 *  @brief      Maximum EDMA channel requirements of all scratch groups
 */
extern __FAR__ Uns EDMA3_edmaChanScratchSizes[EDMA3_MAXGROUPS];

/**
 *  @brief      Maximum QDMA channel requirements of all scratch groups
 */
extern __FAR__ Uns EDMA3_qdmaChanScratchSizes[EDMA3_MAXGROUPS];

/**
 *  @brief      Maximum PaRam requirements of all scratch groups
 */
extern __FAR__ Uns EDMA3_paRamScratchSizes[EDMA3_MAXGROUPS];

/**
 *  @brief      Maximum TCC requirements of all scratch groups
 */
extern __FAR__ Uns EDMA3_tccScratchSizes[EDMA3_MAXGROUPS];

/*@}*/

/**
 *  @brief      Initialization information to create EDMA3 Low Level Resource
 *              Manager handles for each scratch group
 */
extern __FAR__ EDMA3_InstanceInitConfig EDMA3_scratchResourceConfig[EDMA3_MAXGROUPS];

/**
 *  @brief      Initialization information to create the system-level EDMA3 Low  *              Level Resource Manager handle.
 */
extern __FAR__ EDMA3_InstanceInitConfig EDMA3_systemResourceConfig;

/*
 * TC and Queue setup data structures
 */
extern __FAR__ Bool ti_sdo_fc_edma3_Settings_eventQueueSetup;

extern __FAR__ Int ti_sdo_fc_edma3_Settings_queueTCMap[EDMA3_MAX_TC];

extern __FAR__ Int ti_sdo_fc_edma3_Settings_queuePriority[EDMA3_MAX_TC];

extern __FAR__ Int ti_sdo_fc_edma3_Settings_memTypeTCMap[8];

/**
 *  @brief      Default module configuration structure
 *              (defined in edma3_config.c).
 */
extern __FAR__ EDMA3_Params EDMA3_PARAMS;


/**
 *  @brief      Function to create the EDMA3 Low Level Resource Manager object
 *
 *  @retval     EDMA3_SOK or EDMA3_ Error Code
 *
 *  @pre        EDMA3_init() has been called.
 *
 *  @remarks    Typically, system integrators configure these settings using
 *              XDC config scripts.  System integrators that use that method
 *              of configuration can ignore this structure definition.  It's
 *              auto-generated during the config step by the XDC Tools.
 */
extern EDMA3_Result EDMA3_createResourceManagerObject();

/**
 *  @brief      Function to delete the EDMA3 Low Level Resource Manager object
 *
 *  @retval     EDMA3_SOK or EDMA3_ Error Code
 *
 *  @pre        EDMA3_init() has been called.
 *
 *  @remarks    Typically, system integrators configure these settings using
 *              XDC config scripts.  System integrators that use that method
 *              of configuration can ignore this structure definition.  It's
 *              auto-generated during the config step by the XDC Tools.
 */
extern EDMA3_Result EDMA3_deleteResourceManagerObject();

/**
 *  @brief      Function to obtain a handle to the EDMA3 Low Level Resource
 *              Manager instance corresponding to a particular algorithm in a
 *              scratch group.
 *  @param[in]  algHandle       Algorithm Handle
 *  @param[in]  scratchGroupId  Scratch Group Id
 *
 *  @pre        EDMA3_init() has been called.
 *
 *  @retval     NULL or valid handle
 */
EDMA3_Handle EDMA3_getResourceManager(IALG_Handle algHandle,
        Int scratchGroupId);

/**
 *  @brief      Function to release the EDMA3 Resource Manager handle
 *              corresponding to a particular algorithm in a scratch group.
 *
 *  @param[in]  algHandle       Algorithm Handle
 *  @param[in]  scratchGroupId  Scratch Group Id
 *
 *  @retval     EDMA3_SOK or EDMA3_ Error Code
 *
 *  @pre        EDMA3_init() has been called.
 */
EDMA3_Result EDMA3_releaseResourceManager(IALG_Handle algHandle,
        Int scratchGroupId);

/*
 *  @brief      Allocate a particular resource, on this resource handle
 *
 *  @param[in]   hEdmaResMgr      Handle to the previously opened Resource
 *                               Manager Instance.
 *  @param[in/out] resObj         Handle to the resource descriptor
 *                                object, which needs to be allocated.
 *                                In case user passes a specific resource
 *                                Id, resObj value is left unchanged.
 *                                In case user requests ANY available
 *                                resource, the allocated resource id is
 *                                returned in resObj.
 *
 *  @retaval     EDMA3_SOK or EDMA3_ Error Code
 *
 *  @pre        EDMA3_init() has been called.
 */
EDMA3_Result EDMA3_allocResource(EDMA3_Handle hEdmaResMgr,
                                        EDMA3_ResDesc *resObj);

/**
 *  @brief      Frees previously allocated EDMA3 Resources like
 *              DMA/QDMA channel, PaRAM Set or TCC.
 *
 *  @param[in] hEdmaResMgr         Handle to the previously opened Resource
 *                                 Manager Instance.
 *  @param[in] resObj              Handle to the resource descriptor
 *                                 object, which needs to be freed.
 *
 *  @retval EDMA3_SOK or EDMA3_ Error Code
 *
 *  @pre        EDMA3_init() has been called.
 */
EDMA3_Result EDMA3_freeResource(EDMA3_Handle hEdmaResMgr,
        const EDMA3_ResDesc *resObj);

/**
 * @brief       Allocate a contiguous region of specified EDMA3 Resource
 *
 * @param[in] hEdmaResMgr         Handle to the previously opened Resource
 *                                Manager Instance.
 * @param[in] firstResIdObj         Handle to the first resource descriptor
 *                                object, which needs to be allocated.
 *                                firstResIdObject->resId could be a valid
 *                                resource id in case user wants to
 *                                allocate specific resources OR it could
 *                                be EDMA3_RES_ANY in case user wants
 *                                only the required number of resources
 *                                and doesn't care about which resources
 *                                      were allocated.
 * @param[in] numResources        Number of contiguous resources user
 *                                wants to allocate.
 *
 * @retval  EDMA3_SOK or EDMA3_ Error Code
 *
 * @pre        EDMA3_init() has been called.
 */
EDMA3_Result EDMA3_allocContiguousResource(EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *firstResIdObj, unsigned int numResources);

/**
 * @brief       Free a contiguously allocated region of specified EDMA3 Resource
 *
 * @param[in] hEdmaResMgr         Handle to the previously opened Resource
 *                                Manager Instance.
 * @param[in] firstResIdObj       Handle to the first resource descriptor
 *                                descriptor object, which needs to be
 *                                freed. In case of an error while
 *                                freeing any particular resource,
 *                                the last resource id whose freeing has
 *                                failed is returned in this resource
 *                                descriptor object.
 *
 * @param[in] numResources        Number of contiguous resources allocated
 *                                previously that need to be freed.
 *
 * @retval  EDMA3_SOK or EDMA3_ Error Code

 *  @pre        EDMA3_init() has been called.
 */
EDMA3_Result EDMA3_freeContiguousResource(EDMA3_Handle hEdmaResMgr,
                                           EDMA3_ResDesc *firstResIdObj,
                                           unsigned int numResources);
/**
 * @brief   Request a logical DMA/QDMA channels
 *          This API is used to allocate a logical channel (DMA/QDMA/Link)
 *          along with the associated resources. For DMA and QDMA channels, TCC
 *          and PaRAM Set are also allocated along with the requested channel.
 *
 * @param[in] hEdmaResMgr       Handle to the previously opened Resource
 *                              Manager Instance.
 * @param[in] lChObj            Handle to the requested logical channel
 *                              object, which needs to be allocated.
 *                              It could be a specific logical channel
 *                              or ANY available logical channel of the
 *                              requested type.
 * @param[in/out] pParam        PaRAM Set for a particular logical
 *                              (DMA/QDMA) channel.
 *                              In case user passes a specific PaRAM
 *                              Set value, pParam value is left
 *                              unchanged. In case user requests ANY
 *                              available PaRAM Set by passing
 *                              'EDMA3_PARAM_ANY' in pParam,
 *                              the allocated one is returned in pParam.
 *
 * @param[in/out]  pTcc         TCC for a particular logical (DMA/QDMA)
 *                              channel.
 *                              In case user passes a specific TCC
 *                              value, pTcc value is left unchanged.
 *                              In case user requests ANY
 *                              available TCC by passing
 *                              'EDMA3_TCC_ANY' in pTcc,
 *                              the allocated one is returned in pTcc.
 *
 * @return  EDMA3_SOK or EDMA_ Error Code
 *
 * @pre        EDMA3_init() has been called.
 */
EDMA3_Result EDMA3_allocLogicalChannel(EDMA3_Handle hEdmaResMgr,
                            EDMA3_ResDesc *lChObj,
                            unsigned int *pParam,
                            unsigned int *pTcc);


/**
 *  @brief      Exit EDMA3 module. Call this function when done using the
 *              EDMA3 module. This frees any resources allocated in
 *              EDMA3_init().
 *
 *  @retval     EDMA3_SOK or EDMA3_ Error Code
 */
EDMA3_Result EDMA3_exit();

/**
 *  @brief  This API is used to free the specified channel (DMA/QDMA/Link) and
 *          its associated resources (PaRAM Set, TCC etc).
 *
 *  @param[in]      hEdmaResMgr      Handle to the previously opened Resource
 *                                   Manager Instance.
 *  @param[in]      lChObj           Handle to the logical channel object,
 *                                   which needs to be freed
 *  @return  EDMA3_SOK or EDMA_ Error Code
 *
 *  @pre        EDMA3_init() has been called.
 */
EDMA3_Result EDMA3_freeLogicalChannel (EDMA3_Handle hEdmaResMgr,
                                                EDMA3_ResDesc *lChObj);


/**
 *  @brief      Function to obtain the base address of the EDMA3 Controller
 *
 *  @param[in]  hEdmaResMgr      EDMA3 Handle
 *  @param[in]  controllerId     0 for the first EDMA3CC
 *  @param[out] phyAddress       Process-specific address of the EDMA3CC
 *  @retval     EDMA3_SOK or EDMA3_ Error Code
 *
 *  @pre        EDMA3_init() has been called.
 */
EDMA3_Result EDMA3_getBaseAddress(EDMA3_Handle hEdmaResMgr,
        EDMA3_Cntrlr_PhyAddr controllerId, unsigned int *phyAddress);

/**
 *  @brief      Function to obtain the value of a particular register  of the
 *              EDMA3 Controller
 *
 *  @param[in]  hEdmaResMgr     EDMA3 Handle
 *  @param[in]  regOffset       0ffset of the register from the base of
 *                              config space of EDMA3CC
 *  @param[out] regValue        Value in that particular register
 *  @retval     EDMA3_SOK or EDMA3_ Error Code
 *
 *  @pre        EDMA3_init() has been called.
 */
EDMA3_Result EDMA3_getCCRegister(EDMA3_Handle hEdmaResMgr,
        unsigned int regOffset, unsigned int *regValue);

/**
 *  @brief      Initialize EDMA3 module. This function should be called before
 *              any other EDMA3 functions.
 *
 *  @retval     EDMA3_SOK or EDMA3_ Error Code
 */
EDMA3_Result EDMA3_init();

/**
 *  @brief      Function prototype for creation of Semaphore required to create
 *              the EDMA3 Low level Resource Manager Handles
 *  @param[in]  key             Key on which to create the Semaphore.
 *  @param[in]  count           Count to initialize the Semaphore.
 *  @retval     NULL or Handle to a valid Semaphore
 */
Void * EDMA3_semCreate(Int key, Int count);

/**
 *  @brief      Function prototype for deletion of Semaphores created to acquire
 *              EDMA3 Low level Resource Manager Handles
 *  @param[in]  hSem            Handle to a valid semaphore
 */
Void EDMA3_semDelete(EDMA3_SemHandle hSem);

/**
 *  @brief      Function for getting information about mapping of DMA Dest.
 *              types and Event Queues.
 *  @param[in]  hSem            Table to hold the information
 */
Void EDMA3_getDestTypeQueueMap(XDAS_Int32 * table);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/

#endif
