/* ======================================================================
 *   Copyright (C) 2017 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     Cdd_Ipc.h
 *
 *  \brief    This file contains interface Mailbox / IPC as a complex device
 *              driver
 *
 */

/**
 *  \defgroup MCAL_IPC_API IPC Handler and Driver API's
 *
 *  IPC module is provided as an CDD and provides low level access to mailbox
 *  peripheral present on TDAXXX class of devices class of devices
 *
 *  The IPC Driver implements interfaces specified in MCAL_CDD_IPC_Design
 *  document.<br>
 *
 *  Provides methods to transport a 32 bit value across core's in TDAxx class
 *  of processors. Some of the abilities of this driver are
 *
 *  - Send an Event to other processor (s)
 *  - Send an Event with 32 bit payload to other processor (s)
 *  - Register and receive selected events from selected processor (s)
 *
 *
 *  \version 00.00.01
 *
 *  Revision History
 *      Version     : 00.09.00
 *      Author      : Sujith S
 *      Comment     : Created, used AR1x IPC CDD as reference and updated to
 *                      support TDAXXX class of processors
 *
 *  @sa MCAL_IPC_CFG
 *  @{
 */

/*
 * Below are the global requirements which are met by this IPC CDD
 * driver which can't be mapped to a particular source ID
 */

/*
 * Design : IPCCDD_DesignId_000, IPCCDD_DesignId_024
 */
/*
 * Requirements :   MCAL-213, MCAL-207, MCAL-224, MCAL-225, MCAL-230, MCAL-231,
 *                  MCAL-232, MCAL-233, MCAL-234, MCAL-235, MCAL-236, MCAL-237,
 *                  MCAL-238, MCAL-568, MCAL-569
 */

#ifndef CDD_IPC_H_
#define CDD_IPC_H_


/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "Cdd_Ipc_Cfg.h"
#include "Cdd_IpcIrq.h"


#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name CDD IPC Driver Module SW Version Info
 *
 *  Defines for CDD IPC Driver AUTOSAR version used for compatibility checks.
 *  Expected to change with each release of MCAL modules
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define CDD_IPC_SW_MAJOR_VERSION            (1U)
/** \brief Driver Implementation Minor Version */
#define CDD_IPC_SW_MINOR_VERSION            (9U)
/** \brief Driver Implementation patch Version */
#define CDD_IPC_SW_PATCH_VERSION            (0U)
/* @} */

/**
 *  \name CDD IPC Driver Module AUTOSAR Version Info
 *
 *  Defines for CDD Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by CDD Driver */
#define CDD_IPC_AR_RELEASE_MAJOR_VERSION        (4U)
/** \brief AUTOSAR Minor  version specification implemented by CDD Driver */
#define CDD_IPC_AR_RELEASE_MINOR_VERSION        (2U)
/** \brief AUTOSAR Patch version specification implemented by CDD Driver */
#define CDD_IPC_AR_RELEASE_REVISION_VERSION     (1U)
/* @} */

/**
 *  \name CDD IPC Driver Module, AUTOSAR Version Info
 *
 *  Defines for CDD IPC Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/*
 * Design : IPCCDD_DesignId_025
 */
/*
 * Requirements : MCAL-565
 */
/** \brief CDD Module ID */
#define CDD_IPC_MODULE_ID                       ((uint16) 255U)
/** \brief Texas Instruments Vendor ID */
#define CDD_IPC_VENDOR_ID                       ((uint16) 44U)
/** \brief IPC Instance ID */
#define CDD_IPC_INSTANCE_ID                     ((uint8) 0U)

/* @} */


/**
 *  \name CDD API Service ID
 *  @{
 */

/*
 * Design : IPCCDD_DesignId_027, IPCCDD_DesignId_032, IPCCDD_DesignId_033,
 *          IPCCDD_DesignId_034, IPCCDD_DesignId_029, IPCCDD_DesignId_028,
 *          IPCCDD_DesignId_031, IPCCDD_DesignId_034
 */
/*
 * Requirements : MCAL-587, MCAL-591, MCAL-620, MCAL-574, MCAL-603, MCAL-593,
 *                MCAL-618, MCAL-603
 */

/** \brief API Service ID for get version info */
#define CDD_IPC_SID_GETVERSIONINFO      (0x01U)
/** \brief API Service ID for initialization */
#define CDD_IPC_SID_INIT                (0x02U)
/** \brief API Service ID for registering for an event */
#define CDD_IPC_SID_REGISTER_EVENT      (0x03U)
/** \brief API Service ID to send an 32 bit value to remote processor */
#define CDD_IPC_SID_SEND_EVENT          (0x04U)
/** \brief API Service ID for de register event */
#define CDD_IPC_SID_UNREGISTER_EVENT    (0x05U)
/** \brief API Service ID for deinitialization */
#define CDD_IPC_SID_DEINIT              (0x06U)
/** \brief API Service ID for ISR */
#define CDD_IPC_SID_INTERNAL_ISR_ID     (0x07U)
/** \brief API Service ID for register read back */
#define CDD_IPC_SID_REG_READBACK        (0x08U)
/** \brief API Service ID for inject fault */
#define CDD_IPC_SID_INJECT_FAULT        (0x09U)
/* @} */

/**
 *  \name CDD IPC Error Codes
 *  @{
 */
/*
 * Design : IPCCDD_DesignId_025
 */
/*
 * Requirements :   MCAL-592, MCAL-593, MCAL-594, MCAL-595, MCAL-605, MCAL-606,
 *                  MCAL-608
 */
/** \brief No errors */
#define CDD_IPC_E_OK                            (0x00U)
/** \brief Error code indicating initialization failure */
#define CDD_IPC_E_INIT_FAILED                   (0x01U)
/** \brief Error code indicating the IPC is uninitialized */
#define CDD_IPC_E_UNINIT                        (0x02U)
/** \brief Error code indicating an invalid event */
#define CDD_IPC_E_INVALID_EVENT                 (0x03U)
/** \brief Error code indicating NULL initialization parameter */
#define CDD_IPC_E_PARAM_POINTER                 (0x04U)
/** \brief Error code indicating IPC has already been initialized */
#define CDD_IPC_E_ALREADY_INITIALIZED           (0x05U)
/** \brief Error code indicating wrong configuration */
#define CDD_IPC_E_INVALID_CONFIG                (0x06U)
/** \brief Error code indicating re registration for an event */
#define CDD_IPC_E_ALREADY_REGISTERED_EVENT      (0x07U)
/** \brief Error code indicating sending of an event failed */
#define CDD_IPC_E_SEND_EVENT                    (0x08U)
/** \brief Error code indicating sending of an event failed */
#define CDD_IPC_E_NOT_SUPPORTED                 (0x09U)
/** \brief Error code indicating invalid processor ID */
#define CDD_IPC_E_PROC_ID                       (0x0AU)
/** \brief Error code indicating reception of 32 bit payload did not complete
        in time. Please refer Cdd_IpcCfg.readTimeout for details */
#define CDD_IPC_E_RECV_EVENT                    (0x0BU)
/** \brief Error code indicating driver internal error, corrupted variables of
        the driver */
#define CDD_IPC_E_DRV_INTERNAL                  (0x0CU)

/* @} */

/*
 * Design : IPCCDD_DesignId_003, IPCCDD_DesignId_013, IPCCDD_DesignId_016,
 *          IPCCDD_DesignId_025
 */
/* Requirements : MCAL-634, MCAL-634 */
/**
 *  \name CDD IPC module software configurations
 *  @{
 */
/** \brief Maximum number of event id's supported. Range is between 0 to 31,
            inclusive of both 0 & 31.*/
#define CDD_IPC_MAX_EVENT_IDS_SUPPORTED         (0x20U)

/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 *  \addtogroup MCAL_CDD_IPC_CFG CDD_IPC Configuration
 *  @{
 */

/** \brief  Typedef for the MCAL module in the system */
typedef const char* Cdd_IpcModuleName;

/** \brief  Processing core identifiers.
 *
 *  @{
 */
typedef enum
{
   IPC_CORE_0 = 0x00U,
   /**< AUTOSAR Host Processor.
        IPU1_1 in case of TDA3x and IPU2_0 in case of TDA2x/TDA2ex */
   IPC_CORE_1,
   /**< Processing core 1, other processing entity in SOC */
   IPC_CORE_2,
   /**< Processing core 2, other processing entity in SOC */
   IPC_CORE_3,
   /**< Processing core 3, other processing entity in SOC */
   IPC_CORE_ID_MAX
   /**< Enum end marker */
}Cdd_IpcCoreId;
/* @} */


/**
 *  \brief Mailbox descriptor. Define instances of dependent modules to be used
 *          for either reception / transmission of interrutps.
 *  @{
 */
/*
 * Design : IPCCDD_DesignId_011, IPCCDD_DesignId_013, IPCCDD_DesignId_021,
 *          IPCCDD_DesignId_036
 */
/*
 * Requirements : MCAL-628, MCAL-632, MCAL-579, MCAL-580, MCAL-581, MCAL-579,
 *                MCAL-580, MCAL-581, MCAL-582
 */
typedef struct
{
    uint32  mailBoxId;
    /**< Mailbox to be used, 1 to N. N depends on the SoC varient.
            Please note that count starts from 1 same as in TRM */
    uint32  userId;
    /**< User ID associated with this FIFO, Valid range (0 to u), u depend on
            SoC varient. Please refer TRM for details */
    uint32  fifoToBeUsed;
    /**< FIFO to be used. Valid range (0 to m), m depend on SoC varient. Please
            refer TRM for details */
    uint32  reserved;
    /**< Future use if any */

} Cdd_IpcHwMailboxCfg;
/* @} */

/**
 *  \brief CDD IPC Configuration type
 *  @{
 */
/*
 * Design : IPCCDD_DesignId_011, IPCCDD_DesignId_013, IPCCDD_DesignId_021,
 *          IPCCDD_DesignId_026
 */
/*
 * Requirements : MCAL-577, MCAL-578, MCAL-628, MCAL-632, MCAL-582,
 */
typedef struct Cdd_IpcCfg_s
{
    Cdd_IpcCoreId       ownCoreId;
    /**< Core ID on which IPC CDD is hosted on / own processor ID. Value of
            this should be equals to IPC_CORE_0. */
    uint32              numCore;
    /**< IPC required between number of cores. Should be 1. */
    Cdd_IpcCoreId       remoteCoreId[IPC_CORE_ID_MAX];
    /**< Remote Core Identifier */

    Cdd_IpcHwMailboxCfg ownRxMbCfg[IPC_CORE_ID_MAX];
    /**< Reception mailbox configurations */
    Cdd_IpcHwMailboxCfg ownTxMbCfg[IPC_CORE_ID_MAX];
    /**< Transmission mailbox configurations */

    uint32              readTimeout;
    /**< Maximum time until which read API can wait for new data. While trying
            to receive 32 bit data */
    uint32              writeTimeout;
    /**< Maximum time until which transmit API can wait-for to write data */

    uint32              reserved;
    /**< Reserved field */
} Cdd_IpcCfg;

/* @} */

/**
 *  \brief CDD IPC register read back type. Used to read critical registers of
 *          IPC/Mailbox
 *  @{
 */
/*
 * Design : IPCCDD_DesignId_031
 */
/*
 * Requirements :  MCAL-618, MCAL-619
 */
typedef struct
{
    uint32  numRegisters;
    /**< Will specify number of registers values provided */
    uint32  regValues[IPC_CORE_ID_MAX];
    /**< Values of critical registers that's read and provided */
    uint32  reserved;
    /**< Reserved field */
} Cdd_IpcRegRbValues;

/* @} */
/* @} */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Service for getting CDD version.
 *
 *  \verbatim
 *  Service name        : Cdd_IpcGetVersionInfo
 *  Syntax              : void Cdd_IpcGetVersionInfo(Std_VersionInfoType
 *                                                              VersionInfoPtr)
 *  Service ID[hex]     : CDD_IPC_SID_GETVERSIONINFO
 *  Sync/Async          : Synchronous
 *  Reentrancy          : Non Reentrant
 *  Parameters (in)     : VersionInfoPtr - Pointer to version info element
 *  Parameters (inout)  : None
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service for getting CDD version.
 *  \endverbatim
 */
#if (STD_ON == CDD_IPC_VERSION_INFO_API)
FUNC(void, CDD_IPC_CODE) Cdd_IpcGetVersionInfo(
                                        P2VAR(Std_VersionInfoType, AUTOMATIC,
                                        CDD_APP_DATA) VersionInfoPtr);
#endif

/**
 *  \brief Service for CDD Initialization
 *
 *  \verbatim
 *  Service name        : Cdd_IpcInit
 *  Syntax              : void Cdd_IpcInit(Cdd_IpcCfg *ConfigPtr)
 *  Service ID[hex]     : CDD_IPC_SID_INIT
 *  Sync/Async          : Synchronous
 *  Reentrancy          : Non Reentrant
 *  Parameters (in)     : ConfigPtr - Pointer to configuration set
 *  Parameters (inout)  : None
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service for  CDD Initialization.
 *  \endverbatim
 */
FUNC(void, CDD_IPC_CODE) Cdd_IpcInit(
                    P2CONST(Cdd_IpcCfg, AUTOMATIC, CDD_PBCFG) ConfigPtr);

/**
 *  \brief Service for deinitializing CDD
 *
 *  \verbatim
 *  Service name        : Cdd_IpcDeinit
 *  Syntax              : Std_ReturnType Cdd_IpcDeinit(void* ConfigPtr)
 *  Service ID[hex]     : CDD_IPC_SID_DEINIT
 *  Sync/Async          : Synchronous
 *  Reentrancy          : Non-Reentrant
 *  Parameters (in)     : ConfigPtr - Not used for now, reserved for future
 *  Parameters (inout)  : None
 *  Parameters (out)    : None
 *  Return value        : Std_ReturnType
 *  Description         : Service for deinitializing the CDD and change the
 *                          driver state to uninitialized
 *  \endverbatim
 */
#if (STD_ON == CDD_IPC_DEINIT_API)
FUNC(Std_ReturnType, CDD_IPC_CODE) Cdd_IpcDeinit(
                        P2CONST(void, AUTOMATIC, CDD_APP_DATA) ConfigPtr);
#endif


/**
 *  \brief Service for registering the event callback function
 *
 *  \verbatim
 *  Service name        : Cdd_IpcRegisterEvent
 *  Syntax              : Std_ReturnType Cdd_IpcRegisterEvent(
 *                                              Cdd_IpcCoreId remoteCoreId,
 *                                              uint32 eventId,
 *                                              void *AppArgPtr)
 *  Service ID[hex]     : CDD_IPC_SID_REGISTER_EVENT
 *  Sync/Async          : Synchronous
 *  Reentrancy          : Non-Reentrant
 *  Parameters (in)     : remoteCoreId - Should not be equals to ownCoreId.
 *                                       Invalid remoteCoreId will return
 *                                       CDD_IPC_E_NOT_SUPPORTED
 *                      : eventId - Should be less than Max supported events,refer
 *                                  CDD_IPC_MAX_EVENT_IDS_SUPPORTED.
 *                                  For invalid event id, function returns
 *                                  CDD_IPC_E_INVALID_EVENT
 *                      : ipcEventCb - Callback function to be registered for
 *                                      the given event. Should not be NULL.
 *                      : pAppArgs - Argument to the callback function
 *  Parameters (inout)  : None
 *  Parameters (out)    : None
 *  Return value        : Std_ReturnType
 *  Description         : This API is used to registers callback function for a
 *                          given Event
 *  \endverbatim
 *
 */
FUNC(Std_ReturnType, CDD_IPC_CODE)Cdd_IpcRegisterEvent(
                            VAR(Cdd_IpcCoreId, AUTOMATIC) remoteCoreId,
                            VAR(uint32, AUTOMATIC) eventId,
                            P2CONST(void, AUTOMATIC, CDD_APP_DATA) PAppArgs);

/**
 *  \brief Service for sending an event
 *
 *  \verbatim
 *  Service name        : Cdd_IpcSendEvent
 *  Syntax              : Std_ReturnType Cdd_IpcSendEvent(
 *                                              Cdd_IpcCoreId remoteCoreId,
 *                                              uint32 eventId,
 *                                              uint32 payload,
 *                                              uint32 waitClear)
 *  Service ID[hex]     : CDD_IPC_SID_SEND_EVENT
 *  Sync/Async          : Synchronous
 *  Reentrancy          : Non-Reentrant
 *  Parameters (in)     : remoteCoreId - Should not be equals to ownCoreId.
 *                                       Invalid remoteCoreId will return
 *                                       CDD_IPC_E_NOT_SUPPORTED
 *                      : eventId - Should be less than Max supported events,refer
 *                                  CDD_IPC_MAX_EVENT_IDS_SUPPORTED.
 *                                  For invalid event id, function returns
 *                                  CDD_IPC_E_INVALID_EVENT
 *                      : payload - A value upto 32 bits, that requires to be
 *                                      transported to remote processor
 *                      : waitClear - Setting this 0x01 guarantees that value
 *                                      in payload is written into mailbox.
 *                                      Other values, not supported for now.
 *  Parameters (inout)  : None
 *  Parameters (out)    : None
 *  Return value        : Std_ReturnType
 *  Description         : This API is used to transport upto 32 bit values to
 *                          remote processors.
 *  \endverbatim
 *
 */
FUNC(Std_ReturnType, CDD_IPC_CODE) Cdd_IpcSendEvent(
                                    VAR(Cdd_IpcCoreId, AUTOMATIC) remoteCoreId,
                                    VAR(uint32, AUTOMATIC) eventId,
                                    VAR(uint32, AUTOMATIC) payload,
                                    VAR(uint32, AUTOMATIC) waitClear);

/**
 *  \brief Service for unregistering the event callback function
 *
 *  \verbatim
 *  Service name        : Cdd_IpcUnRegisterEvent
 *  Syntax              : Std_ReturnType Cdd_IpcRegisterEvent(
 *                                                  Cdd_IpcCoreId remoteCoreId,
 *                                                  uint32 eventId)
 *  Service ID[hex]     : CDD_IPC_SID_UNREGISTER_EVENT
 *  Sync/Async          : Synchronous
 *  Reentrancy          : Non-Reentrant
 *  Parameters (in)     : remoteCoreId - Should not equals to ownCoreId.
 *                                       Invalid remoteCoreId will return
 *                                       CDD_IPC_E_NOT_SUPPORTED
 *                      : eventId - Should be less than Max supported events,refer
 *                                  CDD_IPC_MAX_EVENT_IDS_SUPPORTED and should
 *                                  have registered earlier.
 *                                  For invalid event id, function returns
 *                                  CDD_IPC_E_INVALID_EVENT
 *  Parameters (inout)  : None
 *  Parameters (out)    : None
 *  Return value        : Std_ReturnType
 *  Description         : This API is used to registers event callback function
 *  \endverbatim
 *
 */
#if (STD_ON == CDD_IPC_UN_REGISTER_EVENT_API)
FUNC(Std_ReturnType, CDD_IPC_CODE)Cdd_IpcUnRegisterEvent(
                                    VAR(Cdd_IpcCoreId, AUTOMATIC) remoteCoreId,
                                    VAR(uint32, AUTOMATIC) eventId);
#endif

/**
 *  \brief Service for reading the configuration registers of the MCAL modules.
 *
 *  \verbatim
 *  Service name        : Cdd_RegisterReadBack
 *  Syntax              : Std_ReturnType Cdd_RegisterReadBack(uint8* mod_name)
 *  Service ID[hex]     : None
 *  Sync/Async          : Synchronous
 *  Reentrancy          : Reentrant
 *  Parameters (in)     : None
 *  Parameters (inout)  : pRegArgs - Pointer to structure that would hold values
 *                          of registers read back by this API
 *  Parameters (out)    : None
 *  Return value        : Std_ReturnType
 *  Description         : Service for reading the critical configuration
 *                          registers of the Mailbox/IPC
 *  \endverbatim
 *
 */
#if (STD_ON == CDD_IPC_REGISTER_READBACK_API)
FUNC(Std_ReturnType, CDD_IPC_CODE) Cdd_IpcRegisterReadBack(
                P2VAR(Cdd_IpcRegRbValues, AUTOMATIC, CDD_APP_DATA) pRegArgs);
#endif

/**
 *  \brief Function used to write a 32 bit value into any location
 *
 *  \verbatim
 *  Service name        : Cdd_IpcInjectFault
 *  Syntax              : Std_ReturnType Cdd_IpcInjectFault(
 *                                                  uint32 valueToBeWritten,
 *                                                  uint32* pRegAddr)
 *  Service ID[hex]     : None
 *  Sync/Async          : Synchronous
 *  Reentrancy          : Non-Reentrant
 *  Parameters (in)     : valueToBeWritten - Hardware key that can be written
 *                          to the device to generate faults.
 *                          pRegAddr - 32bit register value.
 *
 *  Parameters (inout)  : None
 *  Parameters (out)    : None
 *  Return value        : Std_ReturnType
 *  Description         : Service for managing the fault injection. Applications
 *                          are expected to define a function of type
 *                          Cdd_IpcFaultCallback
 *  \endverbatim
 *
 */
#if (STD_ON == CDD_IPC_FAULT_INJECTION_API)
FUNC(Std_ReturnType, CDD_IPC_CODE) Cdd_IpcInjectFault(
                                        VAR(uint32, AUTOMATIC) valueToBeWritten,
                                        VAR(uint32, AUTOMATIC) pRegAddr);
#endif



#ifdef __cplusplus
}
#endif

#endif  /* #ifndef CDD_IPC_H_ */

/* @} */
