/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B21
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_sdo_ipc_MessageQ__include
#define ti_sdo_ipc_MessageQ__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_MessageQ__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_MessageQ___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/package/package.defs.h>

#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/knl/ISync.h>
#include <ti/sysbios/syncs/SyncSem.h>
#include <ti/sdo/ipc/interfaces/ITransport.h>
#include <ti/sdo/ipc/interfaces/IMessageQTransport.h>
#include <ti/sdo/utils/NameServer.h>
#include <ti/sdo/utils/List.h>
#include <xdc/runtime/IModule.h>
#include <ti/sdo/ipc/interfaces/ITransportSetup.h>
#include <ti/sdo/ipc/package/MessageQ_SetupTransportProxy.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* FreeHookFxn */
typedef xdc_Void (*ti_sdo_ipc_MessageQ_FreeHookFxn)(xdc_Bits16, xdc_Bits16);

/* PutHookFxn */
typedef xdc_Void (*ti_sdo_ipc_MessageQ_PutHookFxn)(xdc_Bits32, xdc_Ptr);

/* QueueId */
typedef xdc_UInt32 ti_sdo_ipc_MessageQ_QueueId;

/* NORMALPRI */
#define ti_sdo_ipc_MessageQ_NORMALPRI (0)

/* HIGHPRI */
#define ti_sdo_ipc_MessageQ_HIGHPRI (1)

/* RESERVEDPRI */
#define ti_sdo_ipc_MessageQ_RESERVEDPRI (2)

/* URGENTPRI */
#define ti_sdo_ipc_MessageQ_URGENTPRI (3)

/* ANY */
#define ti_sdo_ipc_MessageQ_ANY (~(0))


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_MessageQ_Args__create {
    xdc_String name;
} ti_sdo_ipc_MessageQ_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* VERSIONMASK */
#define ti_sdo_ipc_MessageQ_VERSIONMASK (0xE000)

/* HEADERVERSION */
#define ti_sdo_ipc_MessageQ_HEADERVERSION (0x2000)

/* TRACEMASK */
#define ti_sdo_ipc_MessageQ_TRACEMASK (0x1000)

/* TRACESHIFT */
#define ti_sdo_ipc_MessageQ_TRACESHIFT (12)

/* PRIORITYMASK */
#define ti_sdo_ipc_MessageQ_PRIORITYMASK (0x3)

/* TRANSPORTPRIORITYMASK */
#define ti_sdo_ipc_MessageQ_TRANSPORTPRIORITYMASK (0x1)

/* PROXY_FAILURE */
#define ti_sdo_ipc_MessageQ_PROXY_FAILURE (1)

/* STATICMSG */
#define ti_sdo_ipc_MessageQ_STATICMSG (0xFFFF)

/* MsgHeader */
struct ti_sdo_ipc_MessageQ_MsgHeader {
    xdc_Bits32 reserved0;
    xdc_Bits32 reserved1;
    xdc_Bits32 msgSize;
    xdc_Bits16 flags;
    xdc_Bits16 msgId;
    xdc_Bits16 dstId;
    xdc_Bits16 dstProc;
    xdc_Bits16 replyId;
    xdc_Bits16 replyProc;
    xdc_Bits16 srcProc;
    xdc_Bits16 heapId;
    xdc_Bits16 seqNum;
    xdc_Bits16 reserved;
};

/* HeapEntry */
struct ti_sdo_ipc_MessageQ_HeapEntry {
    xdc_runtime_IHeap_Handle heap;
    xdc_UInt16 heapId;
};

/* TransportEntry */
struct ti_sdo_ipc_MessageQ_TransportEntry {
    ti_sdo_ipc_interfaces_IMessageQTransport_Handle transport;
    xdc_UInt16 procId;
};

/* TransportType */
enum ti_sdo_ipc_MessageQ_TransportType {
    ti_sdo_ipc_MessageQ_TransportType_IMessageQTransport,
    ti_sdo_ipc_MessageQ_TransportType_INetworkTransport,
    ti_sdo_ipc_MessageQ_TransportType_Invalid
};
typedef enum ti_sdo_ipc_MessageQ_TransportType ti_sdo_ipc_MessageQ_TransportType;

/* RegisteredTransport */
struct ti_sdo_ipc_MessageQ_RegisteredTransport {
    ti_sdo_ipc_interfaces_ITransport_Handle transport;
    ti_sdo_ipc_MessageQ_TransportType type;
};

/* Module_State */
typedef ti_sdo_ipc_interfaces_IMessageQTransport_Handle __T1_ti_sdo_ipc_MessageQ_Module_State__transports;
typedef ti_sdo_ipc_interfaces_IMessageQTransport_Handle __ARRAY1_ti_sdo_ipc_MessageQ_Module_State__transports[2];
typedef __ARRAY1_ti_sdo_ipc_MessageQ_Module_State__transports __T2_ti_sdo_ipc_MessageQ_Module_State__transports;
typedef struct { int length; __T2_ti_sdo_ipc_MessageQ_Module_State__transports* elem; } __ARRAY2_ti_sdo_ipc_MessageQ_Module_State__transports;
typedef __ARRAY2_ti_sdo_ipc_MessageQ_Module_State__transports __TA_ti_sdo_ipc_MessageQ_Module_State__transports;
typedef ti_sdo_ipc_MessageQ_Handle __T1_ti_sdo_ipc_MessageQ_Module_State__queues;
typedef ti_sdo_ipc_MessageQ_Handle *__ARRAY1_ti_sdo_ipc_MessageQ_Module_State__queues;
typedef __ARRAY1_ti_sdo_ipc_MessageQ_Module_State__queues __TA_ti_sdo_ipc_MessageQ_Module_State__queues;
typedef xdc_runtime_IHeap_Handle __T1_ti_sdo_ipc_MessageQ_Module_State__heaps;
typedef xdc_runtime_IHeap_Handle *__ARRAY1_ti_sdo_ipc_MessageQ_Module_State__heaps;
typedef __ARRAY1_ti_sdo_ipc_MessageQ_Module_State__heaps __TA_ti_sdo_ipc_MessageQ_Module_State__heaps;
typedef ti_sdo_ipc_MessageQ_RegisteredTransport __T1_ti_sdo_ipc_MessageQ_Module_State__regTrans;
typedef ti_sdo_ipc_MessageQ_RegisteredTransport __ARRAY1_ti_sdo_ipc_MessageQ_Module_State__regTrans[8];
typedef __ARRAY1_ti_sdo_ipc_MessageQ_Module_State__regTrans __TA_ti_sdo_ipc_MessageQ_Module_State__regTrans;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_MessageQ_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__diagsEnabled ti_sdo_ipc_MessageQ_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_MessageQ_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__diagsIncluded ti_sdo_ipc_MessageQ_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_MessageQ_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__diagsMask ti_sdo_ipc_MessageQ_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_MessageQ_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__gateObj ti_sdo_ipc_MessageQ_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_MessageQ_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__gatePrms ti_sdo_ipc_MessageQ_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_MessageQ_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__id ti_sdo_ipc_MessageQ_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_MessageQ_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__loggerDefined ti_sdo_ipc_MessageQ_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_MessageQ_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__loggerObj ti_sdo_ipc_MessageQ_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_MessageQ_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__loggerFxn0 ti_sdo_ipc_MessageQ_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_MessageQ_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__loggerFxn1 ti_sdo_ipc_MessageQ_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_MessageQ_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__loggerFxn2 ti_sdo_ipc_MessageQ_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_MessageQ_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__loggerFxn4 ti_sdo_ipc_MessageQ_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_MessageQ_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__loggerFxn8 ti_sdo_ipc_MessageQ_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_MessageQ_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Module__startupDoneFxn ti_sdo_ipc_MessageQ_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_MessageQ_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Object__count ti_sdo_ipc_MessageQ_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_MessageQ_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Object__heap ti_sdo_ipc_MessageQ_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_MessageQ_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Object__sizeof ti_sdo_ipc_MessageQ_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_MessageQ_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_Object__table ti_sdo_ipc_MessageQ_Object__table__C;

/* LM_setTrace */
#define ti_sdo_ipc_MessageQ_LM_setTrace (ti_sdo_ipc_MessageQ_LM_setTrace__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_MessageQ_LM_setTrace;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_LM_setTrace ti_sdo_ipc_MessageQ_LM_setTrace__C;

/* LM_alloc */
#define ti_sdo_ipc_MessageQ_LM_alloc (ti_sdo_ipc_MessageQ_LM_alloc__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_MessageQ_LM_alloc;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_LM_alloc ti_sdo_ipc_MessageQ_LM_alloc__C;

/* LM_staticMsgInit */
#define ti_sdo_ipc_MessageQ_LM_staticMsgInit (ti_sdo_ipc_MessageQ_LM_staticMsgInit__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_MessageQ_LM_staticMsgInit;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_LM_staticMsgInit ti_sdo_ipc_MessageQ_LM_staticMsgInit__C;

/* LM_free */
#define ti_sdo_ipc_MessageQ_LM_free (ti_sdo_ipc_MessageQ_LM_free__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_MessageQ_LM_free;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_LM_free ti_sdo_ipc_MessageQ_LM_free__C;

/* LM_putLocal */
#define ti_sdo_ipc_MessageQ_LM_putLocal (ti_sdo_ipc_MessageQ_LM_putLocal__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_MessageQ_LM_putLocal;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_LM_putLocal ti_sdo_ipc_MessageQ_LM_putLocal__C;

/* LM_putRemote */
#define ti_sdo_ipc_MessageQ_LM_putRemote (ti_sdo_ipc_MessageQ_LM_putRemote__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_MessageQ_LM_putRemote;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_LM_putRemote ti_sdo_ipc_MessageQ_LM_putRemote__C;

/* LM_rcvByTransport */
#define ti_sdo_ipc_MessageQ_LM_rcvByTransport (ti_sdo_ipc_MessageQ_LM_rcvByTransport__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_MessageQ_LM_rcvByTransport;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_LM_rcvByTransport ti_sdo_ipc_MessageQ_LM_rcvByTransport__C;

/* LM_get */
#define ti_sdo_ipc_MessageQ_LM_get (ti_sdo_ipc_MessageQ_LM_get__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_MessageQ_LM_get;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_LM_get ti_sdo_ipc_MessageQ_LM_get__C;

/* A_invalidContext */
#define ti_sdo_ipc_MessageQ_A_invalidContext (ti_sdo_ipc_MessageQ_A_invalidContext__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_MessageQ_A_invalidContext;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_A_invalidContext ti_sdo_ipc_MessageQ_A_invalidContext__C;

/* A_cannotFreeStaticMsg */
#define ti_sdo_ipc_MessageQ_A_cannotFreeStaticMsg (ti_sdo_ipc_MessageQ_A_cannotFreeStaticMsg__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_MessageQ_A_cannotFreeStaticMsg;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_A_cannotFreeStaticMsg ti_sdo_ipc_MessageQ_A_cannotFreeStaticMsg__C;

/* A_invalidMsg */
#define ti_sdo_ipc_MessageQ_A_invalidMsg (ti_sdo_ipc_MessageQ_A_invalidMsg__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_MessageQ_A_invalidMsg;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_A_invalidMsg ti_sdo_ipc_MessageQ_A_invalidMsg__C;

/* A_invalidQueueId */
#define ti_sdo_ipc_MessageQ_A_invalidQueueId (ti_sdo_ipc_MessageQ_A_invalidQueueId__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_MessageQ_A_invalidQueueId;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_A_invalidQueueId ti_sdo_ipc_MessageQ_A_invalidQueueId__C;

/* A_heapIdInvalid */
#define ti_sdo_ipc_MessageQ_A_heapIdInvalid (ti_sdo_ipc_MessageQ_A_heapIdInvalid__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_MessageQ_A_heapIdInvalid;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_A_heapIdInvalid ti_sdo_ipc_MessageQ_A_heapIdInvalid__C;

/* A_procIdInvalid */
#define ti_sdo_ipc_MessageQ_A_procIdInvalid (ti_sdo_ipc_MessageQ_A_procIdInvalid__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_MessageQ_A_procIdInvalid;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_A_procIdInvalid ti_sdo_ipc_MessageQ_A_procIdInvalid__C;

/* A_invalidObj */
#define ti_sdo_ipc_MessageQ_A_invalidObj (ti_sdo_ipc_MessageQ_A_invalidObj__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_MessageQ_A_invalidObj;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_A_invalidObj ti_sdo_ipc_MessageQ_A_invalidObj__C;

/* A_invalidParam */
#define ti_sdo_ipc_MessageQ_A_invalidParam (ti_sdo_ipc_MessageQ_A_invalidParam__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_MessageQ_A_invalidParam;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_A_invalidParam ti_sdo_ipc_MessageQ_A_invalidParam__C;

/* A_unregisteredTransport */
#define ti_sdo_ipc_MessageQ_A_unregisteredTransport (ti_sdo_ipc_MessageQ_A_unregisteredTransport__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_MessageQ_A_unregisteredTransport;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_A_unregisteredTransport ti_sdo_ipc_MessageQ_A_unregisteredTransport__C;

/* A_invalidUnblock */
#define ti_sdo_ipc_MessageQ_A_invalidUnblock (ti_sdo_ipc_MessageQ_A_invalidUnblock__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_MessageQ_A_invalidUnblock;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_A_invalidUnblock ti_sdo_ipc_MessageQ_A_invalidUnblock__C;

/* E_maxReached */
#define ti_sdo_ipc_MessageQ_E_maxReached (ti_sdo_ipc_MessageQ_E_maxReached__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_MessageQ_E_maxReached;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_E_maxReached ti_sdo_ipc_MessageQ_E_maxReached__C;

/* E_unregisterHeapId */
#define ti_sdo_ipc_MessageQ_E_unregisterHeapId (ti_sdo_ipc_MessageQ_E_unregisterHeapId__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_MessageQ_E_unregisterHeapId;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_E_unregisterHeapId ti_sdo_ipc_MessageQ_E_unregisterHeapId__C;

/* E_nameFailed */
#define ti_sdo_ipc_MessageQ_E_nameFailed (ti_sdo_ipc_MessageQ_E_nameFailed__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_MessageQ_E_nameFailed;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_E_nameFailed ti_sdo_ipc_MessageQ_E_nameFailed__C;

/* E_indexNotAvailable */
#define ti_sdo_ipc_MessageQ_E_indexNotAvailable (ti_sdo_ipc_MessageQ_E_indexNotAvailable__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_MessageQ_E_indexNotAvailable;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_E_indexNotAvailable ti_sdo_ipc_MessageQ_E_indexNotAvailable__C;

/* traceFlag */
#ifdef ti_sdo_ipc_MessageQ_traceFlag__D
#define ti_sdo_ipc_MessageQ_traceFlag (ti_sdo_ipc_MessageQ_traceFlag__D)
#else
#define ti_sdo_ipc_MessageQ_traceFlag (ti_sdo_ipc_MessageQ_traceFlag__C)
typedef xdc_Bool CT__ti_sdo_ipc_MessageQ_traceFlag;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_traceFlag ti_sdo_ipc_MessageQ_traceFlag__C;
#endif

/* numHeaps */
#ifdef ti_sdo_ipc_MessageQ_numHeaps__D
#define ti_sdo_ipc_MessageQ_numHeaps (ti_sdo_ipc_MessageQ_numHeaps__D)
#else
#define ti_sdo_ipc_MessageQ_numHeaps (ti_sdo_ipc_MessageQ_numHeaps__C)
typedef xdc_UInt16 CT__ti_sdo_ipc_MessageQ_numHeaps;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_numHeaps ti_sdo_ipc_MessageQ_numHeaps__C;
#endif

/* maxRuntimeEntries */
#ifdef ti_sdo_ipc_MessageQ_maxRuntimeEntries__D
#define ti_sdo_ipc_MessageQ_maxRuntimeEntries (ti_sdo_ipc_MessageQ_maxRuntimeEntries__D)
#else
#define ti_sdo_ipc_MessageQ_maxRuntimeEntries (ti_sdo_ipc_MessageQ_maxRuntimeEntries__C)
typedef xdc_UInt CT__ti_sdo_ipc_MessageQ_maxRuntimeEntries;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_maxRuntimeEntries ti_sdo_ipc_MessageQ_maxRuntimeEntries__C;
#endif

/* numReservedEntries */
#ifdef ti_sdo_ipc_MessageQ_numReservedEntries__D
#define ti_sdo_ipc_MessageQ_numReservedEntries (ti_sdo_ipc_MessageQ_numReservedEntries__D)
#else
#define ti_sdo_ipc_MessageQ_numReservedEntries (ti_sdo_ipc_MessageQ_numReservedEntries__C)
typedef xdc_UInt CT__ti_sdo_ipc_MessageQ_numReservedEntries;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_numReservedEntries ti_sdo_ipc_MessageQ_numReservedEntries__C;
#endif

/* nameTableGate */
#define ti_sdo_ipc_MessageQ_nameTableGate (ti_sdo_ipc_MessageQ_nameTableGate__C)
typedef xdc_runtime_IGateProvider_Handle CT__ti_sdo_ipc_MessageQ_nameTableGate;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_nameTableGate ti_sdo_ipc_MessageQ_nameTableGate__C;

/* maxNameLen */
#ifdef ti_sdo_ipc_MessageQ_maxNameLen__D
#define ti_sdo_ipc_MessageQ_maxNameLen (ti_sdo_ipc_MessageQ_maxNameLen__D)
#else
#define ti_sdo_ipc_MessageQ_maxNameLen (ti_sdo_ipc_MessageQ_maxNameLen__C)
typedef xdc_UInt CT__ti_sdo_ipc_MessageQ_maxNameLen;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_maxNameLen ti_sdo_ipc_MessageQ_maxNameLen__C;
#endif

/* freeHookFxn */
#define ti_sdo_ipc_MessageQ_freeHookFxn (ti_sdo_ipc_MessageQ_freeHookFxn__C)
typedef ti_sdo_ipc_MessageQ_FreeHookFxn CT__ti_sdo_ipc_MessageQ_freeHookFxn;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_freeHookFxn ti_sdo_ipc_MessageQ_freeHookFxn__C;

/* putHookFxn */
#define ti_sdo_ipc_MessageQ_putHookFxn (ti_sdo_ipc_MessageQ_putHookFxn__C)
typedef ti_sdo_ipc_MessageQ_PutHookFxn CT__ti_sdo_ipc_MessageQ_putHookFxn;
__extern __FAR__ const CT__ti_sdo_ipc_MessageQ_putHookFxn ti_sdo_ipc_MessageQ_putHookFxn__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_MessageQ_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_runtime_knl_ISync_Handle synchronizer;
    xdc_UInt16 queueIndex;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_MessageQ_Struct {
    ti_sdo_ipc_MessageQ_QueueId __f0;
    xdc_runtime_knl_ISync_Handle __f1;
    xdc_Ptr __f2;
    ti_sysbios_syncs_SyncSem_Handle __f3;
    xdc_Bool __f4;
    ti_sdo_utils_List_Struct __f5;
    ti_sdo_utils_List_Struct __f6;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_MessageQ_Module_startup ti_sdo_ipc_MessageQ_Module_startup__E
xdc__CODESECT(ti_sdo_ipc_MessageQ_Module_startup__E, "ti_sdo_ipc_MessageQ_Module_startup")
__extern xdc_Int ti_sdo_ipc_MessageQ_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_sdo_ipc_MessageQ_Module_startup__F, "ti_sdo_ipc_MessageQ_Module_startup")
__extern xdc_Int ti_sdo_ipc_MessageQ_Module_startup__F( xdc_Int state );

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_MessageQ_Instance_init__E, "ti_sdo_ipc_MessageQ_Instance_init")
__extern xdc_Int ti_sdo_ipc_MessageQ_Instance_init__E(ti_sdo_ipc_MessageQ_Object *, xdc_String name, const ti_sdo_ipc_MessageQ_Params *, xdc_runtime_Error_Block *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_MessageQ_Instance_finalize__E, "ti_sdo_ipc_MessageQ_Instance_finalize")
__extern void ti_sdo_ipc_MessageQ_Instance_finalize__E( ti_sdo_ipc_MessageQ_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_MessageQ_Handle__label__S, "ti_sdo_ipc_MessageQ_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_MessageQ_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_MessageQ_Module__startupDone__S, "ti_sdo_ipc_MessageQ_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_MessageQ_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_MessageQ_Object__create__S, "ti_sdo_ipc_MessageQ_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_MessageQ_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_MessageQ_create, "ti_sdo_ipc_MessageQ_create")
__extern ti_sdo_ipc_MessageQ_Handle ti_sdo_ipc_MessageQ_create( xdc_String name, const ti_sdo_ipc_MessageQ_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_MessageQ_construct, "ti_sdo_ipc_MessageQ_construct")
__extern void ti_sdo_ipc_MessageQ_construct( ti_sdo_ipc_MessageQ_Struct *__obj, xdc_String name, const ti_sdo_ipc_MessageQ_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_MessageQ_Object__delete__S, "ti_sdo_ipc_MessageQ_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_MessageQ_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_MessageQ_delete, "ti_sdo_ipc_MessageQ_delete")
__extern void ti_sdo_ipc_MessageQ_delete(ti_sdo_ipc_MessageQ_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_MessageQ_Object__destruct__S, "ti_sdo_ipc_MessageQ_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_MessageQ_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_MessageQ_destruct, "ti_sdo_ipc_MessageQ_destruct")
__extern void ti_sdo_ipc_MessageQ_destruct(ti_sdo_ipc_MessageQ_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_MessageQ_Object__get__S, "ti_sdo_ipc_MessageQ_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_MessageQ_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_MessageQ_Object__first__S, "ti_sdo_ipc_MessageQ_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_MessageQ_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_MessageQ_Object__next__S, "ti_sdo_ipc_MessageQ_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_MessageQ_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_MessageQ_Params__init__S, "ti_sdo_ipc_MessageQ_Params__init__S")
__extern xdc_Void ti_sdo_ipc_MessageQ_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* registerTransport__E */
#define ti_sdo_ipc_MessageQ_registerTransport ti_sdo_ipc_MessageQ_registerTransport__E
xdc__CODESECT(ti_sdo_ipc_MessageQ_registerTransport__E, "ti_sdo_ipc_MessageQ_registerTransport")
__extern xdc_Bool ti_sdo_ipc_MessageQ_registerTransport__E( ti_sdo_ipc_interfaces_IMessageQTransport_Handle transport, xdc_UInt16 procId, xdc_UInt priority );
xdc__CODESECT(ti_sdo_ipc_MessageQ_registerTransport__F, "ti_sdo_ipc_MessageQ_registerTransport")
__extern xdc_Bool ti_sdo_ipc_MessageQ_registerTransport__F( ti_sdo_ipc_interfaces_IMessageQTransport_Handle transport, xdc_UInt16 procId, xdc_UInt priority );

/* unregisterTransport__E */
#define ti_sdo_ipc_MessageQ_unregisterTransport ti_sdo_ipc_MessageQ_unregisterTransport__E
xdc__CODESECT(ti_sdo_ipc_MessageQ_unregisterTransport__E, "ti_sdo_ipc_MessageQ_unregisterTransport")
__extern xdc_Void ti_sdo_ipc_MessageQ_unregisterTransport__E( xdc_UInt16 procId, xdc_UInt priority );
xdc__CODESECT(ti_sdo_ipc_MessageQ_unregisterTransport__F, "ti_sdo_ipc_MessageQ_unregisterTransport")
__extern xdc_Void ti_sdo_ipc_MessageQ_unregisterTransport__F( xdc_UInt16 procId, xdc_UInt priority );

/* grow__I */
#define ti_sdo_ipc_MessageQ_grow ti_sdo_ipc_MessageQ_grow__I
xdc__CODESECT(ti_sdo_ipc_MessageQ_grow__I, "ti_sdo_ipc_MessageQ_grow")
__extern xdc_UInt16 ti_sdo_ipc_MessageQ_grow__I( ti_sdo_ipc_MessageQ_Object *obj, xdc_runtime_Error_Block *eb );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_MessageQ_Module_startupDone() ti_sdo_ipc_MessageQ_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_MessageQ_Object_heap() ti_sdo_ipc_MessageQ_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_MessageQ_Module_heap() ti_sdo_ipc_MessageQ_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_MessageQ_Module__id ti_sdo_ipc_MessageQ_Module_id( void ) 
{
    return ti_sdo_ipc_MessageQ_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_MessageQ_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_MessageQ_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_MessageQ_Module_getMask( void ) 
{
    return ti_sdo_ipc_MessageQ_Module__diagsMask__C != NULL ? *ti_sdo_ipc_MessageQ_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_MessageQ_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_MessageQ_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_MessageQ_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_MessageQ_Params_init( ti_sdo_ipc_MessageQ_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_MessageQ_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_MessageQ_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_MessageQ_Params_copy(ti_sdo_ipc_MessageQ_Params *dst, const ti_sdo_ipc_MessageQ_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_MessageQ_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_MessageQ_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_MessageQ_Object_count() ti_sdo_ipc_MessageQ_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_MessageQ_Object_sizeof() ti_sdo_ipc_MessageQ_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_MessageQ_Handle ti_sdo_ipc_MessageQ_Object_get(ti_sdo_ipc_MessageQ_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_MessageQ_Handle)ti_sdo_ipc_MessageQ_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_MessageQ_Handle ti_sdo_ipc_MessageQ_Object_first( void )
{
    return (ti_sdo_ipc_MessageQ_Handle)ti_sdo_ipc_MessageQ_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_MessageQ_Handle ti_sdo_ipc_MessageQ_Object_next( ti_sdo_ipc_MessageQ_Object *obj )
{
    return (ti_sdo_ipc_MessageQ_Handle)ti_sdo_ipc_MessageQ_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_MessageQ_Handle_label( ti_sdo_ipc_MessageQ_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_MessageQ_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_MessageQ_Handle_name( ti_sdo_ipc_MessageQ_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_MessageQ_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_MessageQ_Handle ti_sdo_ipc_MessageQ_handle( ti_sdo_ipc_MessageQ_Struct *str )
{
    return (ti_sdo_ipc_MessageQ_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_MessageQ_Struct *ti_sdo_ipc_MessageQ_struct( ti_sdo_ipc_MessageQ_Handle inst )
{
    return (ti_sdo_ipc_MessageQ_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_MessageQ__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_MessageQ__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_MessageQ__internalaccess))

#ifndef ti_sdo_ipc_MessageQ__include_state
#define ti_sdo_ipc_MessageQ__include_state

/* Module_State */
struct ti_sdo_ipc_MessageQ_Module_State {
    __TA_ti_sdo_ipc_MessageQ_Module_State__transports transports;
    __TA_ti_sdo_ipc_MessageQ_Module_State__queues queues;
    __TA_ti_sdo_ipc_MessageQ_Module_State__heaps heaps;
    xdc_runtime_IGateProvider_Handle gate;
    xdc_UInt16 numQueues;
    xdc_UInt16 numHeaps;
    ti_sdo_utils_NameServer_Handle nameServer;
    ti_sdo_ipc_MessageQ_FreeHookFxn freeHookFxn;
    ti_sdo_ipc_MessageQ_PutHookFxn putHookFxn;
    xdc_Bool canFreeQueues;
    xdc_UInt16 seqNum;
    __TA_ti_sdo_ipc_MessageQ_Module_State__regTrans regTrans;
};

/* Module__state__V */
extern struct ti_sdo_ipc_MessageQ_Module_State__ ti_sdo_ipc_MessageQ_Module__state__V;

/* Object */
struct ti_sdo_ipc_MessageQ_Object {
    ti_sdo_ipc_MessageQ_QueueId queue;
    xdc_runtime_knl_ISync_Handle synchronizer;
    xdc_Ptr nsKey;
    ti_sysbios_syncs_SyncSem_Handle syncSemHandle;
    xdc_Bool unblocked;
    char __dummy;
};

/* Instance_State_normalList */
__extern __FAR__ const xdc_SizeT ti_sdo_ipc_MessageQ_Instance_State_normalList__O;
static inline ti_sdo_utils_List_Handle ti_sdo_ipc_MessageQ_Instance_State_normalList(ti_sdo_ipc_MessageQ_Object *obj)
{
    return (ti_sdo_utils_List_Handle)(((char*)obj) + ti_sdo_ipc_MessageQ_Instance_State_normalList__O);
}

/* Instance_State_highList */
__extern __FAR__ const xdc_SizeT ti_sdo_ipc_MessageQ_Instance_State_highList__O;
static inline ti_sdo_utils_List_Handle ti_sdo_ipc_MessageQ_Instance_State_highList(ti_sdo_ipc_MessageQ_Object *obj)
{
    return (ti_sdo_utils_List_Handle)(((char*)obj) + ti_sdo_ipc_MessageQ_Instance_State_highList__O);
}

#endif /* ti_sdo_ipc_MessageQ__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_MessageQ__nolocalnames)

#ifndef ti_sdo_ipc_MessageQ__localnames__done
#define ti_sdo_ipc_MessageQ__localnames__done

/* module prefix */
#define MessageQ_Instance ti_sdo_ipc_MessageQ_Instance
#define MessageQ_Handle ti_sdo_ipc_MessageQ_Handle
#define MessageQ_Module ti_sdo_ipc_MessageQ_Module
#define MessageQ_Object ti_sdo_ipc_MessageQ_Object
#define MessageQ_Struct ti_sdo_ipc_MessageQ_Struct
#define MessageQ_FreeHookFxn ti_sdo_ipc_MessageQ_FreeHookFxn
#define MessageQ_PutHookFxn ti_sdo_ipc_MessageQ_PutHookFxn
#define MessageQ_QueueId ti_sdo_ipc_MessageQ_QueueId
#define MessageQ_NORMALPRI ti_sdo_ipc_MessageQ_NORMALPRI
#define MessageQ_HIGHPRI ti_sdo_ipc_MessageQ_HIGHPRI
#define MessageQ_RESERVEDPRI ti_sdo_ipc_MessageQ_RESERVEDPRI
#define MessageQ_URGENTPRI ti_sdo_ipc_MessageQ_URGENTPRI
#define MessageQ_ANY ti_sdo_ipc_MessageQ_ANY
#define MessageQ_VERSIONMASK ti_sdo_ipc_MessageQ_VERSIONMASK
#define MessageQ_HEADERVERSION ti_sdo_ipc_MessageQ_HEADERVERSION
#define MessageQ_TRACEMASK ti_sdo_ipc_MessageQ_TRACEMASK
#define MessageQ_TRACESHIFT ti_sdo_ipc_MessageQ_TRACESHIFT
#define MessageQ_PRIORITYMASK ti_sdo_ipc_MessageQ_PRIORITYMASK
#define MessageQ_TRANSPORTPRIORITYMASK ti_sdo_ipc_MessageQ_TRANSPORTPRIORITYMASK
#define MessageQ_PROXY_FAILURE ti_sdo_ipc_MessageQ_PROXY_FAILURE
#define MessageQ_STATICMSG ti_sdo_ipc_MessageQ_STATICMSG
#define MessageQ_MsgHeader ti_sdo_ipc_MessageQ_MsgHeader
#define MessageQ_HeapEntry ti_sdo_ipc_MessageQ_HeapEntry
#define MessageQ_TransportEntry ti_sdo_ipc_MessageQ_TransportEntry
#define MessageQ_TransportType ti_sdo_ipc_MessageQ_TransportType
#define MessageQ_RegisteredTransport ti_sdo_ipc_MessageQ_RegisteredTransport
#define MessageQ_Instance_State ti_sdo_ipc_MessageQ_Instance_State
#define MessageQ_Module_State ti_sdo_ipc_MessageQ_Module_State
#define MessageQ_TransportType_IMessageQTransport ti_sdo_ipc_MessageQ_TransportType_IMessageQTransport
#define MessageQ_TransportType_INetworkTransport ti_sdo_ipc_MessageQ_TransportType_INetworkTransport
#define MessageQ_TransportType_Invalid ti_sdo_ipc_MessageQ_TransportType_Invalid
#define MessageQ_LM_setTrace ti_sdo_ipc_MessageQ_LM_setTrace
#define MessageQ_LM_alloc ti_sdo_ipc_MessageQ_LM_alloc
#define MessageQ_LM_staticMsgInit ti_sdo_ipc_MessageQ_LM_staticMsgInit
#define MessageQ_LM_free ti_sdo_ipc_MessageQ_LM_free
#define MessageQ_LM_putLocal ti_sdo_ipc_MessageQ_LM_putLocal
#define MessageQ_LM_putRemote ti_sdo_ipc_MessageQ_LM_putRemote
#define MessageQ_LM_rcvByTransport ti_sdo_ipc_MessageQ_LM_rcvByTransport
#define MessageQ_LM_get ti_sdo_ipc_MessageQ_LM_get
#define MessageQ_A_invalidContext ti_sdo_ipc_MessageQ_A_invalidContext
#define MessageQ_A_cannotFreeStaticMsg ti_sdo_ipc_MessageQ_A_cannotFreeStaticMsg
#define MessageQ_A_invalidMsg ti_sdo_ipc_MessageQ_A_invalidMsg
#define MessageQ_A_invalidQueueId ti_sdo_ipc_MessageQ_A_invalidQueueId
#define MessageQ_A_heapIdInvalid ti_sdo_ipc_MessageQ_A_heapIdInvalid
#define MessageQ_A_procIdInvalid ti_sdo_ipc_MessageQ_A_procIdInvalid
#define MessageQ_A_invalidObj ti_sdo_ipc_MessageQ_A_invalidObj
#define MessageQ_A_invalidParam ti_sdo_ipc_MessageQ_A_invalidParam
#define MessageQ_A_unregisteredTransport ti_sdo_ipc_MessageQ_A_unregisteredTransport
#define MessageQ_A_invalidUnblock ti_sdo_ipc_MessageQ_A_invalidUnblock
#define MessageQ_E_maxReached ti_sdo_ipc_MessageQ_E_maxReached
#define MessageQ_E_unregisterHeapId ti_sdo_ipc_MessageQ_E_unregisterHeapId
#define MessageQ_E_nameFailed ti_sdo_ipc_MessageQ_E_nameFailed
#define MessageQ_E_indexNotAvailable ti_sdo_ipc_MessageQ_E_indexNotAvailable
#define MessageQ_traceFlag ti_sdo_ipc_MessageQ_traceFlag
#define MessageQ_numHeaps ti_sdo_ipc_MessageQ_numHeaps
#define MessageQ_maxRuntimeEntries ti_sdo_ipc_MessageQ_maxRuntimeEntries
#define MessageQ_numReservedEntries ti_sdo_ipc_MessageQ_numReservedEntries
#define MessageQ_nameTableGate ti_sdo_ipc_MessageQ_nameTableGate
#define MessageQ_maxNameLen ti_sdo_ipc_MessageQ_maxNameLen
#define MessageQ_freeHookFxn ti_sdo_ipc_MessageQ_freeHookFxn
#define MessageQ_putHookFxn ti_sdo_ipc_MessageQ_putHookFxn
#define MessageQ_Instance_State_normalList ti_sdo_ipc_MessageQ_Instance_State_normalList
#define MessageQ_Instance_State_highList ti_sdo_ipc_MessageQ_Instance_State_highList
#define MessageQ_Params ti_sdo_ipc_MessageQ_Params
#define MessageQ_registerTransport ti_sdo_ipc_MessageQ_registerTransport
#define MessageQ_unregisterTransport ti_sdo_ipc_MessageQ_unregisterTransport
#define MessageQ_Module_name ti_sdo_ipc_MessageQ_Module_name
#define MessageQ_Module_id ti_sdo_ipc_MessageQ_Module_id
#define MessageQ_Module_startup ti_sdo_ipc_MessageQ_Module_startup
#define MessageQ_Module_startupDone ti_sdo_ipc_MessageQ_Module_startupDone
#define MessageQ_Module_hasMask ti_sdo_ipc_MessageQ_Module_hasMask
#define MessageQ_Module_getMask ti_sdo_ipc_MessageQ_Module_getMask
#define MessageQ_Module_setMask ti_sdo_ipc_MessageQ_Module_setMask
#define MessageQ_Object_heap ti_sdo_ipc_MessageQ_Object_heap
#define MessageQ_Module_heap ti_sdo_ipc_MessageQ_Module_heap
#define MessageQ_construct ti_sdo_ipc_MessageQ_construct
#define MessageQ_create ti_sdo_ipc_MessageQ_create
#define MessageQ_handle ti_sdo_ipc_MessageQ_handle
#define MessageQ_struct ti_sdo_ipc_MessageQ_struct
#define MessageQ_Handle_label ti_sdo_ipc_MessageQ_Handle_label
#define MessageQ_Handle_name ti_sdo_ipc_MessageQ_Handle_name
#define MessageQ_Instance_init ti_sdo_ipc_MessageQ_Instance_init
#define MessageQ_Object_count ti_sdo_ipc_MessageQ_Object_count
#define MessageQ_Object_get ti_sdo_ipc_MessageQ_Object_get
#define MessageQ_Object_first ti_sdo_ipc_MessageQ_Object_first
#define MessageQ_Object_next ti_sdo_ipc_MessageQ_Object_next
#define MessageQ_Object_sizeof ti_sdo_ipc_MessageQ_Object_sizeof
#define MessageQ_Params_copy ti_sdo_ipc_MessageQ_Params_copy
#define MessageQ_Params_init ti_sdo_ipc_MessageQ_Params_init
#define MessageQ_Instance_finalize ti_sdo_ipc_MessageQ_Instance_finalize
#define MessageQ_delete ti_sdo_ipc_MessageQ_delete
#define MessageQ_destruct ti_sdo_ipc_MessageQ_destruct

/* proxies */
#include <ti/sdo/ipc/package/MessageQ_SetupTransportProxy.h>

#endif /* ti_sdo_ipc_MessageQ__localnames__done */
#endif
