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
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_sdo_ipc_nsremote_NameServerRemoteNotify__include
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_nsremote_NameServerRemoteNotify___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/nsremote/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sdo/ipc/GateMP.h>
#include <ti/sdo/utils/INameServerRemote.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Status */
typedef ti_sdo_utils_INameServerRemote_Status ti_sdo_ipc_nsremote_NameServerRemoteNotify_Status;

/* Message */
typedef xdc_Bits32 __T1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__instanceName;
typedef xdc_Bits32 __ARRAY1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__instanceName[8];
typedef __ARRAY1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__instanceName __TA_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__instanceName;
typedef xdc_Bits32 __T1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__name;
typedef xdc_Bits32 __ARRAY1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__name[8];
typedef __ARRAY1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__name __TA_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__name;
typedef xdc_Bits32 __T1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__valueBuf;
typedef xdc_Bits32 __ARRAY1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__valueBuf[77];
typedef __ARRAY1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__valueBuf __TA_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__valueBuf;
struct ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message {
    xdc_Bits32 requestStatus;
    xdc_Bits32 value;
    xdc_Bits32 valueLen;
    __TA_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__instanceName instanceName;
    __TA_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__name name;
    __TA_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message__valueBuf valueBuf;
};

/* S_SUCCESS */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_S_SUCCESS ti_sdo_utils_INameServerRemote_S_SUCCESS

/* E_FAIL */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_E_FAIL ti_sdo_utils_INameServerRemote_E_FAIL

/* E_ERROR */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_E_ERROR ti_sdo_utils_INameServerRemote_E_ERROR


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_nsremote_NameServerRemoteNotify_Args__create {
    xdc_UInt16 procId;
} ti_sdo_ipc_nsremote_NameServerRemoteNotify_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* IDLE */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_IDLE (0)

/* SEND_REQUEST */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_SEND_REQUEST (1)

/* RECEIVE_RESPONSE */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_RECEIVE_RESPONSE (2)

/* RECEIVE_REQUEST */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_RECEIVE_REQUEST (1)

/* SEND_RESPONSE */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_SEND_RESPONSE (2)

/* Instance_State */
typedef ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message *__T1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State__msg;
typedef ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message *__ARRAY1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State__msg[2];
typedef __ARRAY1_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State__msg __TA_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State__msg;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsEnabled ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsIncluded ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsMask ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__gateObj ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__gatePrms ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__id ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerDefined ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerObj ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn0 ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn1 ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn2 ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn4 ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn8 ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__startupDoneFxn ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__count ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__heap ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__sizeof ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__table ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__table__C;

/* A_invalidValueLen */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_invalidValueLen (ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_invalidValueLen__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_invalidValueLen;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_invalidValueLen ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_invalidValueLen__C;

/* A_messageSize */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_messageSize (ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_messageSize__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_messageSize;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_messageSize ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_messageSize__C;

/* notifyEventId */
#ifdef ti_sdo_ipc_nsremote_NameServerRemoteNotify_notifyEventId__D
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_notifyEventId (ti_sdo_ipc_nsremote_NameServerRemoteNotify_notifyEventId__D)
#else
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_notifyEventId (ti_sdo_ipc_nsremote_NameServerRemoteNotify_notifyEventId__C)
typedef xdc_UInt CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_notifyEventId;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_notifyEventId ti_sdo_ipc_nsremote_NameServerRemoteNotify_notifyEventId__C;
#endif

/* timeoutInMicroSecs */
#ifdef ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeoutInMicroSecs__D
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeoutInMicroSecs (ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeoutInMicroSecs__D)
#else
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeoutInMicroSecs (ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeoutInMicroSecs__C)
typedef xdc_UInt CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeoutInMicroSecs;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeoutInMicroSecs ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeoutInMicroSecs__C;
#endif

/* timeout */
#ifdef ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeout__D
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeout (ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeout__D)
#else
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeout (ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeout__C)
typedef xdc_UInt CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeout;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeout ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeout__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_Ptr sharedAddr;
    ti_sdo_ipc_GateMP_Handle gate;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_nsremote_NameServerRemoteNotify_Struct {
    const ti_sdo_ipc_nsremote_NameServerRemoteNotify_Fxns__ *__fxns;
    __TA_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State__msg __f0;
    xdc_UInt16 __f1;
    xdc_UInt8 __f2;
    xdc_UInt8 __f3;
    ti_sdo_ipc_GateMP_Handle __f4;
    xdc_UInt16 __f5;
    xdc_Bool __f6;
    ti_sysbios_knl_Semaphore_Struct __f7;
    ti_sysbios_knl_Semaphore_Struct __f8;
    ti_sysbios_knl_Swi_Struct __f9;
    ti_sysbios_knl_Swi_Struct __f10;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_nsremote_NameServerRemoteNotify_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*attach)(xdc_UInt16, xdc_Ptr);
    xdc_Int (*detach)(xdc_UInt16);
    xdc_SizeT (*sharedMemReq)(xdc_Ptr);
    xdc_Int (*get)(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle, xdc_String, xdc_String, xdc_Ptr, xdc_UInt32*, xdc_runtime_knl_ISync_Handle, xdc_runtime_Error_Block*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_nsremote_NameServerRemoteNotify_Fxns__ ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_init__E, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_init")
__extern xdc_Int ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_init__E(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object *, xdc_UInt16 procId, const ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params *, xdc_runtime_Error_Block *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_finalize__E, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_finalize")
__extern void ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_finalize__E( ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle__label__S, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__startupDone__S, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__create__S, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_create, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_create")
__extern ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_create( xdc_UInt16 procId, const ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_construct, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_construct")
__extern void ti_sdo_ipc_nsremote_NameServerRemoteNotify_construct( ti_sdo_ipc_nsremote_NameServerRemoteNotify_Struct *__obj, xdc_UInt16 procId, const ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__delete__S, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_delete, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_delete")
__extern void ti_sdo_ipc_nsremote_NameServerRemoteNotify_delete(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__destruct__S, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_destruct, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_destruct")
__extern void ti_sdo_ipc_nsremote_NameServerRemoteNotify_destruct(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__get__S, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__first__S, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__next__S, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params__init__S, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params__init__S")
__extern xdc_Void ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* attach__E */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_attach ti_sdo_ipc_nsremote_NameServerRemoteNotify_attach__E
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_attach__E, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_attach")
__extern xdc_Int ti_sdo_ipc_nsremote_NameServerRemoteNotify_attach__E( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* detach__E */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_detach ti_sdo_ipc_nsremote_NameServerRemoteNotify_detach__E
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_detach__E, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_detach")
__extern xdc_Int ti_sdo_ipc_nsremote_NameServerRemoteNotify_detach__E( xdc_UInt16 remoteProcId );

/* sharedMemReq__E */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_sharedMemReq ti_sdo_ipc_nsremote_NameServerRemoteNotify_sharedMemReq__E
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_sharedMemReq__E, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_nsremote_NameServerRemoteNotify_sharedMemReq__E( xdc_Ptr sharedAddr );

/* get__E */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_get ti_sdo_ipc_nsremote_NameServerRemoteNotify_get__E
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_get__E, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_get")
__extern xdc_Int ti_sdo_ipc_nsremote_NameServerRemoteNotify_get__E( ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle __inst, xdc_String instanceName, xdc_String name, xdc_Ptr value, xdc_UInt32 *valueLen, xdc_runtime_knl_ISync_Handle syncHandle, xdc_runtime_Error_Block *eb );
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_get__F, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_get")
__extern xdc_Int ti_sdo_ipc_nsremote_NameServerRemoteNotify_get__F( ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object *__inst, xdc_String instanceName, xdc_String name, xdc_Ptr value, xdc_UInt32 *valueLen, xdc_runtime_knl_ISync_Handle syncHandle, xdc_runtime_Error_Block *eb );

/* cbFxn__I */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_cbFxn ti_sdo_ipc_nsremote_NameServerRemoteNotify_cbFxn__I
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_cbFxn__I, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_cbFxn")
__extern xdc_Void ti_sdo_ipc_nsremote_NameServerRemoteNotify_cbFxn__I( xdc_UInt16 procId, xdc_UInt16 lineId, xdc_UInt32 eventId, xdc_UArg arg, xdc_UInt32 payload );

/* swiFxnRequest__I */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnRequest ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnRequest__I
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnRequest__I, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnRequest")
__extern xdc_Void ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnRequest__I( xdc_UArg arg );

/* swiFxnResponse__I */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnResponse ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnResponse__I
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnResponse__I, "ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnResponse")
__extern xdc_Void ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnResponse__I( xdc_UArg arg );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_utils_INameServerRemote_Module ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_upCast( void )
{
    return (ti_sdo_utils_INameServerRemote_Module)&ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__FXNS__C;
}

/* Module_to_ti_sdo_utils_INameServerRemote */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_to_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_upCast

/* Handle_upCast */
static inline ti_sdo_utils_INameServerRemote_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_upCast( ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle i )
{
    return (ti_sdo_utils_INameServerRemote_Handle)i;
}

/* Handle_to_ti_sdo_utils_INameServerRemote */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_to_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_downCast( ti_sdo_utils_INameServerRemote_Handle i )
{
    ti_sdo_utils_INameServerRemote_Handle i2 = (ti_sdo_utils_INameServerRemote_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__FXNS__C ? (ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle)i : (ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle)0;
}

/* Handle_from_ti_sdo_utils_INameServerRemote */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_from_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_startupDone() ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_heap() ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_heap() ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__id ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_id( void ) 
{
    return ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_getMask( void ) 
{
    return ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsMask__C != NULL ? *ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params_init( ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params_copy(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params *dst, const ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_count() ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_sizeof() ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_get(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle)ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_first( void )
{
    return (ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle)ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_next( ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object *obj )
{
    return (ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle)ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_label( ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_name( ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_handle( ti_sdo_ipc_nsremote_NameServerRemoteNotify_Struct *str )
{
    return (ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_nsremote_NameServerRemoteNotify_Struct *ti_sdo_ipc_nsremote_NameServerRemoteNotify_struct( ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle inst )
{
    return (ti_sdo_ipc_nsremote_NameServerRemoteNotify_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_nsremote_NameServerRemoteNotify__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_nsremote_NameServerRemoteNotify__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_nsremote_NameServerRemoteNotify__internalaccess))

#ifndef ti_sdo_ipc_nsremote_NameServerRemoteNotify__include_state
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify__include_state

/* Object */
struct ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object {
    const ti_sdo_ipc_nsremote_NameServerRemoteNotify_Fxns__ *__fxns;
    __TA_ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State__msg msg;
    xdc_UInt16 regionId;
    xdc_UInt8 localState;
    xdc_UInt8 remoteState;
    ti_sdo_ipc_GateMP_Handle gate;
    xdc_UInt16 remoteProcId;
    xdc_Bool cacheEnable;
    char __dummy;
};

/* Instance_State_semRemoteWait */
__extern __FAR__ const xdc_SizeT ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_semRemoteWait__O;
static inline ti_sysbios_knl_Semaphore_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_semRemoteWait(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object *obj)
{
    return (ti_sysbios_knl_Semaphore_Handle)(((char*)obj) + ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_semRemoteWait__O);
}

/* Instance_State_semMultiBlock */
__extern __FAR__ const xdc_SizeT ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_semMultiBlock__O;
static inline ti_sysbios_knl_Semaphore_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_semMultiBlock(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object *obj)
{
    return (ti_sysbios_knl_Semaphore_Handle)(((char*)obj) + ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_semMultiBlock__O);
}

/* Instance_State_swiRequest */
__extern __FAR__ const xdc_SizeT ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_swiRequest__O;
static inline ti_sysbios_knl_Swi_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_swiRequest(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object *obj)
{
    return (ti_sysbios_knl_Swi_Handle)(((char*)obj) + ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_swiRequest__O);
}

/* Instance_State_swiResponse */
__extern __FAR__ const xdc_SizeT ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_swiResponse__O;
static inline ti_sysbios_knl_Swi_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_swiResponse(ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object *obj)
{
    return (ti_sysbios_knl_Swi_Handle)(((char*)obj) + ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_swiResponse__O);
}

#endif /* ti_sdo_ipc_nsremote_NameServerRemoteNotify__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_nsremote_NameServerRemoteNotify__nolocalnames)

#ifndef ti_sdo_ipc_nsremote_NameServerRemoteNotify__localnames__done
#define ti_sdo_ipc_nsremote_NameServerRemoteNotify__localnames__done

/* module prefix */
#define NameServerRemoteNotify_Instance ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance
#define NameServerRemoteNotify_Handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle
#define NameServerRemoteNotify_Module ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module
#define NameServerRemoteNotify_Object ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object
#define NameServerRemoteNotify_Struct ti_sdo_ipc_nsremote_NameServerRemoteNotify_Struct
#define NameServerRemoteNotify_Status ti_sdo_ipc_nsremote_NameServerRemoteNotify_Status
#define NameServerRemoteNotify_Message ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message
#define NameServerRemoteNotify_IDLE ti_sdo_ipc_nsremote_NameServerRemoteNotify_IDLE
#define NameServerRemoteNotify_SEND_REQUEST ti_sdo_ipc_nsremote_NameServerRemoteNotify_SEND_REQUEST
#define NameServerRemoteNotify_RECEIVE_RESPONSE ti_sdo_ipc_nsremote_NameServerRemoteNotify_RECEIVE_RESPONSE
#define NameServerRemoteNotify_RECEIVE_REQUEST ti_sdo_ipc_nsremote_NameServerRemoteNotify_RECEIVE_REQUEST
#define NameServerRemoteNotify_SEND_RESPONSE ti_sdo_ipc_nsremote_NameServerRemoteNotify_SEND_RESPONSE
#define NameServerRemoteNotify_Instance_State ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State
#define NameServerRemoteNotify_S_SUCCESS ti_sdo_ipc_nsremote_NameServerRemoteNotify_S_SUCCESS
#define NameServerRemoteNotify_E_FAIL ti_sdo_ipc_nsremote_NameServerRemoteNotify_E_FAIL
#define NameServerRemoteNotify_E_ERROR ti_sdo_ipc_nsremote_NameServerRemoteNotify_E_ERROR
#define NameServerRemoteNotify_A_invalidValueLen ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_invalidValueLen
#define NameServerRemoteNotify_A_messageSize ti_sdo_ipc_nsremote_NameServerRemoteNotify_A_messageSize
#define NameServerRemoteNotify_notifyEventId ti_sdo_ipc_nsremote_NameServerRemoteNotify_notifyEventId
#define NameServerRemoteNotify_timeoutInMicroSecs ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeoutInMicroSecs
#define NameServerRemoteNotify_timeout ti_sdo_ipc_nsremote_NameServerRemoteNotify_timeout
#define NameServerRemoteNotify_Instance_State_semRemoteWait ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_semRemoteWait
#define NameServerRemoteNotify_Instance_State_semMultiBlock ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_semMultiBlock
#define NameServerRemoteNotify_Instance_State_swiRequest ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_swiRequest
#define NameServerRemoteNotify_Instance_State_swiResponse ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_State_swiResponse
#define NameServerRemoteNotify_Params ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params
#define NameServerRemoteNotify_attach ti_sdo_ipc_nsremote_NameServerRemoteNotify_attach
#define NameServerRemoteNotify_detach ti_sdo_ipc_nsremote_NameServerRemoteNotify_detach
#define NameServerRemoteNotify_sharedMemReq ti_sdo_ipc_nsremote_NameServerRemoteNotify_sharedMemReq
#define NameServerRemoteNotify_get ti_sdo_ipc_nsremote_NameServerRemoteNotify_get
#define NameServerRemoteNotify_Module_name ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_name
#define NameServerRemoteNotify_Module_id ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_id
#define NameServerRemoteNotify_Module_startup ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_startup
#define NameServerRemoteNotify_Module_startupDone ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_startupDone
#define NameServerRemoteNotify_Module_hasMask ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_hasMask
#define NameServerRemoteNotify_Module_getMask ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_getMask
#define NameServerRemoteNotify_Module_setMask ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_setMask
#define NameServerRemoteNotify_Object_heap ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_heap
#define NameServerRemoteNotify_Module_heap ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_heap
#define NameServerRemoteNotify_construct ti_sdo_ipc_nsremote_NameServerRemoteNotify_construct
#define NameServerRemoteNotify_create ti_sdo_ipc_nsremote_NameServerRemoteNotify_create
#define NameServerRemoteNotify_handle ti_sdo_ipc_nsremote_NameServerRemoteNotify_handle
#define NameServerRemoteNotify_struct ti_sdo_ipc_nsremote_NameServerRemoteNotify_struct
#define NameServerRemoteNotify_Handle_label ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_label
#define NameServerRemoteNotify_Handle_name ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_name
#define NameServerRemoteNotify_Instance_init ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_init
#define NameServerRemoteNotify_Object_count ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_count
#define NameServerRemoteNotify_Object_get ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_get
#define NameServerRemoteNotify_Object_first ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_first
#define NameServerRemoteNotify_Object_next ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_next
#define NameServerRemoteNotify_Object_sizeof ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object_sizeof
#define NameServerRemoteNotify_Params_copy ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params_copy
#define NameServerRemoteNotify_Params_init ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params_init
#define NameServerRemoteNotify_Instance_finalize ti_sdo_ipc_nsremote_NameServerRemoteNotify_Instance_finalize
#define NameServerRemoteNotify_delete ti_sdo_ipc_nsremote_NameServerRemoteNotify_delete
#define NameServerRemoteNotify_destruct ti_sdo_ipc_nsremote_NameServerRemoteNotify_destruct
#define NameServerRemoteNotify_Module_upCast ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_upCast
#define NameServerRemoteNotify_Module_to_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module_to_ti_sdo_utils_INameServerRemote
#define NameServerRemoteNotify_Handle_upCast ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_upCast
#define NameServerRemoteNotify_Handle_to_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_to_ti_sdo_utils_INameServerRemote
#define NameServerRemoteNotify_Handle_downCast ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_downCast
#define NameServerRemoteNotify_Handle_from_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle_from_ti_sdo_utils_INameServerRemote

#endif /* ti_sdo_ipc_nsremote_NameServerRemoteNotify__localnames__done */
#endif
