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

#ifndef ti_sdo_ipc_GateMP__include
#define ti_sdo_ipc_GateMP__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_GateMP__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_GateMP___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>
#include <ti/sdo/utils/NameServer.h>
#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>
#include <xdc/runtime/IModule.h>
#include <ti/sdo/ipc/SharedRegion.h>
#include <ti/sdo/ipc/Ipc.h>
#include <ti/sdo/ipc/package/GateMP_RemoteSystemProxy.h>
#include <ti/sdo/ipc/package/GateMP_RemoteCustom1Proxy.h>
#include <ti/sdo/ipc/package/GateMP_RemoteCustom2Proxy.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Reserved */
struct ti_sdo_ipc_GateMP_Reserved {
    xdc_Bits32 version;
};

/* LocalProtect */
enum ti_sdo_ipc_GateMP_LocalProtect {
    ti_sdo_ipc_GateMP_LocalProtect_NONE = 0,
    ti_sdo_ipc_GateMP_LocalProtect_INTERRUPT = 1,
    ti_sdo_ipc_GateMP_LocalProtect_TASKLET = 2,
    ti_sdo_ipc_GateMP_LocalProtect_THREAD = 3,
    ti_sdo_ipc_GateMP_LocalProtect_PROCESS = 4
};
typedef enum ti_sdo_ipc_GateMP_LocalProtect ti_sdo_ipc_GateMP_LocalProtect;

/* RemoteProtect */
enum ti_sdo_ipc_GateMP_RemoteProtect {
    ti_sdo_ipc_GateMP_RemoteProtect_NONE = 0,
    ti_sdo_ipc_GateMP_RemoteProtect_SYSTEM = 1,
    ti_sdo_ipc_GateMP_RemoteProtect_CUSTOM1 = 2,
    ti_sdo_ipc_GateMP_RemoteProtect_CUSTOM2 = 3
};
typedef enum ti_sdo_ipc_GateMP_RemoteProtect ti_sdo_ipc_GateMP_RemoteProtect;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* VERSION */
#define ti_sdo_ipc_GateMP_VERSION (1)

/* CREATED */
#define ti_sdo_ipc_GateMP_CREATED (0x11202009)

/* ProxyOrder_SYSTEM */
#define ti_sdo_ipc_GateMP_ProxyOrder_SYSTEM (0)

/* ProxyOrder_CUSTOM1 */
#define ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM1 (1)

/* ProxyOrder_CUSTOM2 */
#define ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM2 (2)

/* ProxyOrder_NUM */
#define ti_sdo_ipc_GateMP_ProxyOrder_NUM (3)

/* LocalGate */
struct ti_sdo_ipc_GateMP_LocalGate {
    xdc_runtime_IGateProvider_Handle localGate;
    xdc_Int refCount;
};

/* Attrs */
struct ti_sdo_ipc_GateMP_Attrs {
    xdc_Bits16 mask;
    xdc_Bits16 creatorProcId;
    xdc_Bits32 arg;
    xdc_Bits32 status;
};

/* Module_State */
typedef xdc_UInt8 __T1_ti_sdo_ipc_GateMP_Module_State__remoteSystemInUse;
typedef xdc_UInt8 *__ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteSystemInUse;
typedef __ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteSystemInUse __TA_ti_sdo_ipc_GateMP_Module_State__remoteSystemInUse;
typedef xdc_UInt8 __T1_ti_sdo_ipc_GateMP_Module_State__remoteCustom1InUse;
typedef xdc_UInt8 *__ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteCustom1InUse;
typedef __ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteCustom1InUse __TA_ti_sdo_ipc_GateMP_Module_State__remoteCustom1InUse;
typedef xdc_UInt8 __T1_ti_sdo_ipc_GateMP_Module_State__remoteCustom2InUse;
typedef xdc_UInt8 *__ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteCustom2InUse;
typedef __ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteCustom2InUse __TA_ti_sdo_ipc_GateMP_Module_State__remoteCustom2InUse;
typedef ti_sdo_ipc_GateMP_Handle __T1_ti_sdo_ipc_GateMP_Module_State__remoteSystemGates;
typedef ti_sdo_ipc_GateMP_Handle *__ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteSystemGates;
typedef __ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteSystemGates __TA_ti_sdo_ipc_GateMP_Module_State__remoteSystemGates;
typedef ti_sdo_ipc_GateMP_Handle __T1_ti_sdo_ipc_GateMP_Module_State__remoteCustom1Gates;
typedef ti_sdo_ipc_GateMP_Handle *__ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteCustom1Gates;
typedef __ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteCustom1Gates __TA_ti_sdo_ipc_GateMP_Module_State__remoteCustom1Gates;
typedef ti_sdo_ipc_GateMP_Handle __T1_ti_sdo_ipc_GateMP_Module_State__remoteCustom2Gates;
typedef ti_sdo_ipc_GateMP_Handle *__ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteCustom2Gates;
typedef __ARRAY1_ti_sdo_ipc_GateMP_Module_State__remoteCustom2Gates __TA_ti_sdo_ipc_GateMP_Module_State__remoteCustom2Gates;
typedef xdc_Int __T1_ti_sdo_ipc_GateMP_Module_State__proxyMap;
typedef xdc_Int __ARRAY1_ti_sdo_ipc_GateMP_Module_State__proxyMap[3];
typedef __ARRAY1_ti_sdo_ipc_GateMP_Module_State__proxyMap __TA_ti_sdo_ipc_GateMP_Module_State__proxyMap;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_GateMP_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__diagsEnabled ti_sdo_ipc_GateMP_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_GateMP_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__diagsIncluded ti_sdo_ipc_GateMP_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_GateMP_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__diagsMask ti_sdo_ipc_GateMP_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__gateObj ti_sdo_ipc_GateMP_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__gatePrms ti_sdo_ipc_GateMP_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_GateMP_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__id ti_sdo_ipc_GateMP_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_GateMP_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__loggerDefined ti_sdo_ipc_GateMP_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__loggerObj ti_sdo_ipc_GateMP_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_GateMP_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__loggerFxn0 ti_sdo_ipc_GateMP_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_GateMP_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__loggerFxn1 ti_sdo_ipc_GateMP_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_GateMP_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__loggerFxn2 ti_sdo_ipc_GateMP_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_GateMP_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__loggerFxn4 ti_sdo_ipc_GateMP_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_GateMP_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__loggerFxn8 ti_sdo_ipc_GateMP_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_GateMP_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Module__startupDoneFxn ti_sdo_ipc_GateMP_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_GateMP_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Object__count ti_sdo_ipc_GateMP_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_GateMP_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Object__heap ti_sdo_ipc_GateMP_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_GateMP_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Object__sizeof ti_sdo_ipc_GateMP_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_Object__table ti_sdo_ipc_GateMP_Object__table__C;

/* E_gateUnavailable */
#define ti_sdo_ipc_GateMP_E_gateUnavailable (ti_sdo_ipc_GateMP_E_gateUnavailable__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_GateMP_E_gateUnavailable;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_E_gateUnavailable ti_sdo_ipc_GateMP_E_gateUnavailable__C;

/* E_localGate */
#define ti_sdo_ipc_GateMP_E_localGate (ti_sdo_ipc_GateMP_E_localGate__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_GateMP_E_localGate;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_E_localGate ti_sdo_ipc_GateMP_E_localGate__C;

/* A_invalidClose */
#define ti_sdo_ipc_GateMP_A_invalidClose (ti_sdo_ipc_GateMP_A_invalidClose__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_GateMP_A_invalidClose;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_A_invalidClose ti_sdo_ipc_GateMP_A_invalidClose__C;

/* A_invalidDelete */
#define ti_sdo_ipc_GateMP_A_invalidDelete (ti_sdo_ipc_GateMP_A_invalidDelete__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_GateMP_A_invalidDelete;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_A_invalidDelete ti_sdo_ipc_GateMP_A_invalidDelete__C;

/* LM_enter */
#define ti_sdo_ipc_GateMP_LM_enter (ti_sdo_ipc_GateMP_LM_enter__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_GateMP_LM_enter;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_LM_enter ti_sdo_ipc_GateMP_LM_enter__C;

/* LM_leave */
#define ti_sdo_ipc_GateMP_LM_leave (ti_sdo_ipc_GateMP_LM_leave__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_GateMP_LM_leave;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_LM_leave ti_sdo_ipc_GateMP_LM_leave__C;

/* LM_create */
#define ti_sdo_ipc_GateMP_LM_create (ti_sdo_ipc_GateMP_LM_create__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_GateMP_LM_create;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_LM_create ti_sdo_ipc_GateMP_LM_create__C;

/* LM_open */
#define ti_sdo_ipc_GateMP_LM_open (ti_sdo_ipc_GateMP_LM_open__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_GateMP_LM_open;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_LM_open ti_sdo_ipc_GateMP_LM_open__C;

/* LM_delete */
#define ti_sdo_ipc_GateMP_LM_delete (ti_sdo_ipc_GateMP_LM_delete__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_GateMP_LM_delete;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_LM_delete ti_sdo_ipc_GateMP_LM_delete__C;

/* LM_close */
#define ti_sdo_ipc_GateMP_LM_close (ti_sdo_ipc_GateMP_LM_close__C)
typedef xdc_runtime_Log_Event CT__ti_sdo_ipc_GateMP_LM_close;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_LM_close ti_sdo_ipc_GateMP_LM_close__C;

/* maxNameLen */
#ifdef ti_sdo_ipc_GateMP_maxNameLen__D
#define ti_sdo_ipc_GateMP_maxNameLen (ti_sdo_ipc_GateMP_maxNameLen__D)
#else
#define ti_sdo_ipc_GateMP_maxNameLen (ti_sdo_ipc_GateMP_maxNameLen__C)
typedef xdc_UInt CT__ti_sdo_ipc_GateMP_maxNameLen;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_maxNameLen ti_sdo_ipc_GateMP_maxNameLen__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_GateMP_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_String name;
    xdc_Bool openFlag;
    xdc_Bits32 resourceId;
    xdc_UInt16 regionId;
    xdc_Ptr sharedAddr;
    ti_sdo_ipc_GateMP_LocalProtect localProtect;
    ti_sdo_ipc_GateMP_RemoteProtect remoteProtect;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_GateMP_Struct {
    ti_sdo_ipc_GateMP_RemoteProtect __f0;
    ti_sdo_ipc_GateMP_LocalProtect __f1;
    xdc_Ptr __f2;
    xdc_Int __f3;
    xdc_Bool __f4;
    ti_sdo_ipc_GateMP_Attrs *__f5;
    xdc_UInt16 __f6;
    xdc_SizeT __f7;
    ti_sdo_ipc_Ipc_ObjType __f8;
    xdc_Ptr __f9;
    xdc_UInt __f10;
    xdc_runtime_IGateProvider_Handle __f11;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_GateMP_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_GateMP_Instance_init__E, "ti_sdo_ipc_GateMP_Instance_init")
__extern xdc_Int ti_sdo_ipc_GateMP_Instance_init__E(ti_sdo_ipc_GateMP_Object *, const ti_sdo_ipc_GateMP_Params *, xdc_runtime_Error_Block *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_GateMP_Instance_finalize__E, "ti_sdo_ipc_GateMP_Instance_finalize")
__extern void ti_sdo_ipc_GateMP_Instance_finalize__E( ti_sdo_ipc_GateMP_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_Handle__label__S, "ti_sdo_ipc_GateMP_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_GateMP_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_Module__startupDone__S, "ti_sdo_ipc_GateMP_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_GateMP_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_Object__create__S, "ti_sdo_ipc_GateMP_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_GateMP_create, "ti_sdo_ipc_GateMP_create")
__extern ti_sdo_ipc_GateMP_Handle ti_sdo_ipc_GateMP_create( const ti_sdo_ipc_GateMP_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_GateMP_construct, "ti_sdo_ipc_GateMP_construct")
__extern void ti_sdo_ipc_GateMP_construct( ti_sdo_ipc_GateMP_Struct *__obj, const ti_sdo_ipc_GateMP_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_Object__delete__S, "ti_sdo_ipc_GateMP_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_GateMP_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_GateMP_delete, "ti_sdo_ipc_GateMP_delete")
__extern void ti_sdo_ipc_GateMP_delete(ti_sdo_ipc_GateMP_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_Object__destruct__S, "ti_sdo_ipc_GateMP_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_GateMP_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_GateMP_destruct, "ti_sdo_ipc_GateMP_destruct")
__extern void ti_sdo_ipc_GateMP_destruct(ti_sdo_ipc_GateMP_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_Object__get__S, "ti_sdo_ipc_GateMP_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_Object__first__S, "ti_sdo_ipc_GateMP_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_Object__next__S, "ti_sdo_ipc_GateMP_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_Params__init__S, "ti_sdo_ipc_GateMP_Params__init__S")
__extern xdc_Void ti_sdo_ipc_GateMP_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* createLocal__E */
#define ti_sdo_ipc_GateMP_createLocal ti_sdo_ipc_GateMP_createLocal__E
xdc__CODESECT(ti_sdo_ipc_GateMP_createLocal__E, "ti_sdo_ipc_GateMP_createLocal")
__extern xdc_runtime_IGateProvider_Handle ti_sdo_ipc_GateMP_createLocal__E( ti_sdo_ipc_GateMP_LocalProtect localProtect );
xdc__CODESECT(ti_sdo_ipc_GateMP_createLocal__F, "ti_sdo_ipc_GateMP_createLocal")
__extern xdc_runtime_IGateProvider_Handle ti_sdo_ipc_GateMP_createLocal__F( ti_sdo_ipc_GateMP_LocalProtect localProtect );

/* attach__E */
#define ti_sdo_ipc_GateMP_attach ti_sdo_ipc_GateMP_attach__E
xdc__CODESECT(ti_sdo_ipc_GateMP_attach__E, "ti_sdo_ipc_GateMP_attach")
__extern xdc_Int ti_sdo_ipc_GateMP_attach__E( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );
xdc__CODESECT(ti_sdo_ipc_GateMP_attach__F, "ti_sdo_ipc_GateMP_attach")
__extern xdc_Int ti_sdo_ipc_GateMP_attach__F( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* detach__E */
#define ti_sdo_ipc_GateMP_detach ti_sdo_ipc_GateMP_detach__E
xdc__CODESECT(ti_sdo_ipc_GateMP_detach__E, "ti_sdo_ipc_GateMP_detach")
__extern xdc_Int ti_sdo_ipc_GateMP_detach__E( xdc_UInt16 remoteProcId );
xdc__CODESECT(ti_sdo_ipc_GateMP_detach__F, "ti_sdo_ipc_GateMP_detach")
__extern xdc_Int ti_sdo_ipc_GateMP_detach__F( xdc_UInt16 remoteProcId );

/* getRegion0ReservedSize__E */
#define ti_sdo_ipc_GateMP_getRegion0ReservedSize ti_sdo_ipc_GateMP_getRegion0ReservedSize__E
xdc__CODESECT(ti_sdo_ipc_GateMP_getRegion0ReservedSize__E, "ti_sdo_ipc_GateMP_getRegion0ReservedSize")
__extern xdc_SizeT ti_sdo_ipc_GateMP_getRegion0ReservedSize__E( void );
xdc__CODESECT(ti_sdo_ipc_GateMP_getRegion0ReservedSize__F, "ti_sdo_ipc_GateMP_getRegion0ReservedSize")
__extern xdc_SizeT ti_sdo_ipc_GateMP_getRegion0ReservedSize__F( void );

/* setRegion0Reserved__E */
#define ti_sdo_ipc_GateMP_setRegion0Reserved ti_sdo_ipc_GateMP_setRegion0Reserved__E
xdc__CODESECT(ti_sdo_ipc_GateMP_setRegion0Reserved__E, "ti_sdo_ipc_GateMP_setRegion0Reserved")
__extern xdc_Void ti_sdo_ipc_GateMP_setRegion0Reserved__E( xdc_Ptr sharedAddr );
xdc__CODESECT(ti_sdo_ipc_GateMP_setRegion0Reserved__F, "ti_sdo_ipc_GateMP_setRegion0Reserved")
__extern xdc_Void ti_sdo_ipc_GateMP_setRegion0Reserved__F( xdc_Ptr sharedAddr );

/* openRegion0Reserved__E */
#define ti_sdo_ipc_GateMP_openRegion0Reserved ti_sdo_ipc_GateMP_openRegion0Reserved__E
xdc__CODESECT(ti_sdo_ipc_GateMP_openRegion0Reserved__E, "ti_sdo_ipc_GateMP_openRegion0Reserved")
__extern xdc_Void ti_sdo_ipc_GateMP_openRegion0Reserved__E( xdc_Ptr sharedAddr );
xdc__CODESECT(ti_sdo_ipc_GateMP_openRegion0Reserved__F, "ti_sdo_ipc_GateMP_openRegion0Reserved")
__extern xdc_Void ti_sdo_ipc_GateMP_openRegion0Reserved__F( xdc_Ptr sharedAddr );

/* setDefaultRemote__E */
#define ti_sdo_ipc_GateMP_setDefaultRemote ti_sdo_ipc_GateMP_setDefaultRemote__E
xdc__CODESECT(ti_sdo_ipc_GateMP_setDefaultRemote__E, "ti_sdo_ipc_GateMP_setDefaultRemote")
__extern xdc_Void ti_sdo_ipc_GateMP_setDefaultRemote__E( ti_sdo_ipc_GateMP_Handle handle );
xdc__CODESECT(ti_sdo_ipc_GateMP_setDefaultRemote__F, "ti_sdo_ipc_GateMP_setDefaultRemote")
__extern xdc_Void ti_sdo_ipc_GateMP_setDefaultRemote__F( ti_sdo_ipc_GateMP_Handle handle );

/* start__E */
#define ti_sdo_ipc_GateMP_start ti_sdo_ipc_GateMP_start__E
xdc__CODESECT(ti_sdo_ipc_GateMP_start__E, "ti_sdo_ipc_GateMP_start")
__extern xdc_Int ti_sdo_ipc_GateMP_start__E( xdc_Ptr sharedAddr );
xdc__CODESECT(ti_sdo_ipc_GateMP_start__F, "ti_sdo_ipc_GateMP_start")
__extern xdc_Int ti_sdo_ipc_GateMP_start__F( xdc_Ptr sharedAddr );

/* stop__E */
#define ti_sdo_ipc_GateMP_stop ti_sdo_ipc_GateMP_stop__E
xdc__CODESECT(ti_sdo_ipc_GateMP_stop__E, "ti_sdo_ipc_GateMP_stop")
__extern xdc_Int ti_sdo_ipc_GateMP_stop__E( void );
xdc__CODESECT(ti_sdo_ipc_GateMP_stop__F, "ti_sdo_ipc_GateMP_stop")
__extern xdc_Int ti_sdo_ipc_GateMP_stop__F( void );

/* getSharedAddr__E */
#define ti_sdo_ipc_GateMP_getSharedAddr ti_sdo_ipc_GateMP_getSharedAddr__E
xdc__CODESECT(ti_sdo_ipc_GateMP_getSharedAddr__E, "ti_sdo_ipc_GateMP_getSharedAddr")
__extern ti_sdo_ipc_SharedRegion_SRPtr ti_sdo_ipc_GateMP_getSharedAddr__E( ti_sdo_ipc_GateMP_Handle __inst );
xdc__CODESECT(ti_sdo_ipc_GateMP_getSharedAddr__F, "ti_sdo_ipc_GateMP_getSharedAddr")
__extern ti_sdo_ipc_SharedRegion_SRPtr ti_sdo_ipc_GateMP_getSharedAddr__F( ti_sdo_ipc_GateMP_Object *__inst );

/* getFreeResource__I */
#define ti_sdo_ipc_GateMP_getFreeResource ti_sdo_ipc_GateMP_getFreeResource__I
xdc__CODESECT(ti_sdo_ipc_GateMP_getFreeResource__I, "ti_sdo_ipc_GateMP_getFreeResource")
__extern xdc_UInt ti_sdo_ipc_GateMP_getFreeResource__I( xdc_UInt8 *inUse, xdc_Int num, xdc_runtime_Error_Block *eb );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_GateMP_Module_startupDone() ti_sdo_ipc_GateMP_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_GateMP_Object_heap() ti_sdo_ipc_GateMP_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_GateMP_Module_heap() ti_sdo_ipc_GateMP_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_GateMP_Module__id ti_sdo_ipc_GateMP_Module_id( void ) 
{
    return ti_sdo_ipc_GateMP_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_GateMP_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_GateMP_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_GateMP_Module_getMask( void ) 
{
    return ti_sdo_ipc_GateMP_Module__diagsMask__C != NULL ? *ti_sdo_ipc_GateMP_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_GateMP_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_GateMP_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_GateMP_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_GateMP_Params_init( ti_sdo_ipc_GateMP_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_GateMP_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_GateMP_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_GateMP_Params_copy(ti_sdo_ipc_GateMP_Params *dst, const ti_sdo_ipc_GateMP_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_GateMP_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_GateMP_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_GateMP_Object_count() ti_sdo_ipc_GateMP_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_GateMP_Object_sizeof() ti_sdo_ipc_GateMP_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_GateMP_Handle ti_sdo_ipc_GateMP_Object_get(ti_sdo_ipc_GateMP_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_GateMP_Handle)ti_sdo_ipc_GateMP_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_GateMP_Handle ti_sdo_ipc_GateMP_Object_first( void )
{
    return (ti_sdo_ipc_GateMP_Handle)ti_sdo_ipc_GateMP_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_GateMP_Handle ti_sdo_ipc_GateMP_Object_next( ti_sdo_ipc_GateMP_Object *obj )
{
    return (ti_sdo_ipc_GateMP_Handle)ti_sdo_ipc_GateMP_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_GateMP_Handle_label( ti_sdo_ipc_GateMP_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_GateMP_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_GateMP_Handle_name( ti_sdo_ipc_GateMP_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_GateMP_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_GateMP_Handle ti_sdo_ipc_GateMP_handle( ti_sdo_ipc_GateMP_Struct *str )
{
    return (ti_sdo_ipc_GateMP_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_GateMP_Struct *ti_sdo_ipc_GateMP_struct( ti_sdo_ipc_GateMP_Handle inst )
{
    return (ti_sdo_ipc_GateMP_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_GateMP__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_GateMP__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_GateMP__internalaccess))

#ifndef ti_sdo_ipc_GateMP__include_state
#define ti_sdo_ipc_GateMP__include_state

/* Module_State */
struct ti_sdo_ipc_GateMP_Module_State {
    ti_sdo_utils_NameServer_Handle nameServer;
    xdc_Int numRemoteSystem;
    xdc_Int numRemoteCustom1;
    xdc_Int numRemoteCustom2;
    __TA_ti_sdo_ipc_GateMP_Module_State__remoteSystemInUse remoteSystemInUse;
    __TA_ti_sdo_ipc_GateMP_Module_State__remoteCustom1InUse remoteCustom1InUse;
    __TA_ti_sdo_ipc_GateMP_Module_State__remoteCustom2InUse remoteCustom2InUse;
    __TA_ti_sdo_ipc_GateMP_Module_State__remoteSystemGates remoteSystemGates;
    __TA_ti_sdo_ipc_GateMP_Module_State__remoteCustom1Gates remoteCustom1Gates;
    __TA_ti_sdo_ipc_GateMP_Module_State__remoteCustom2Gates remoteCustom2Gates;
    xdc_runtime_IGateProvider_Handle gateAll;
    xdc_runtime_IGateProvider_Handle gateSwi;
    xdc_runtime_IGateProvider_Handle gateMutexPri;
    xdc_runtime_IGateProvider_Handle gateNull;
    ti_sdo_ipc_GateMP_Handle defaultGate;
    xdc_Ptr nsKey;
    xdc_Bool hostSupport;
    __TA_ti_sdo_ipc_GateMP_Module_State__proxyMap proxyMap;
};

/* Module__state__V */
extern struct ti_sdo_ipc_GateMP_Module_State__ ti_sdo_ipc_GateMP_Module__state__V;

/* Object */
struct ti_sdo_ipc_GateMP_Object {
    ti_sdo_ipc_GateMP_RemoteProtect remoteProtect;
    ti_sdo_ipc_GateMP_LocalProtect localProtect;
    xdc_Ptr nsKey;
    xdc_Int numOpens;
    xdc_Bool cacheEnabled;
    ti_sdo_ipc_GateMP_Attrs *attrs;
    xdc_UInt16 regionId;
    xdc_SizeT allocSize;
    ti_sdo_ipc_Ipc_ObjType objType;
    xdc_Ptr proxyAttrs;
    xdc_UInt resourceId;
    xdc_runtime_IGateProvider_Handle gateHandle;
};

#endif /* ti_sdo_ipc_GateMP__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_GateMP__nolocalnames)

#ifndef ti_sdo_ipc_GateMP__localnames__done
#define ti_sdo_ipc_GateMP__localnames__done

/* module prefix */
#define GateMP_Instance ti_sdo_ipc_GateMP_Instance
#define GateMP_Handle ti_sdo_ipc_GateMP_Handle
#define GateMP_Module ti_sdo_ipc_GateMP_Module
#define GateMP_Object ti_sdo_ipc_GateMP_Object
#define GateMP_Struct ti_sdo_ipc_GateMP_Struct
#define GateMP_Reserved ti_sdo_ipc_GateMP_Reserved
#define GateMP_LocalProtect ti_sdo_ipc_GateMP_LocalProtect
#define GateMP_RemoteProtect ti_sdo_ipc_GateMP_RemoteProtect
#define GateMP_VERSION ti_sdo_ipc_GateMP_VERSION
#define GateMP_CREATED ti_sdo_ipc_GateMP_CREATED
#define GateMP_ProxyOrder_SYSTEM ti_sdo_ipc_GateMP_ProxyOrder_SYSTEM
#define GateMP_ProxyOrder_CUSTOM1 ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM1
#define GateMP_ProxyOrder_CUSTOM2 ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM2
#define GateMP_ProxyOrder_NUM ti_sdo_ipc_GateMP_ProxyOrder_NUM
#define GateMP_LocalGate ti_sdo_ipc_GateMP_LocalGate
#define GateMP_Attrs ti_sdo_ipc_GateMP_Attrs
#define GateMP_Instance_State ti_sdo_ipc_GateMP_Instance_State
#define GateMP_Module_State ti_sdo_ipc_GateMP_Module_State
#define GateMP_LocalProtect_NONE ti_sdo_ipc_GateMP_LocalProtect_NONE
#define GateMP_LocalProtect_INTERRUPT ti_sdo_ipc_GateMP_LocalProtect_INTERRUPT
#define GateMP_LocalProtect_TASKLET ti_sdo_ipc_GateMP_LocalProtect_TASKLET
#define GateMP_LocalProtect_THREAD ti_sdo_ipc_GateMP_LocalProtect_THREAD
#define GateMP_LocalProtect_PROCESS ti_sdo_ipc_GateMP_LocalProtect_PROCESS
#define GateMP_RemoteProtect_NONE ti_sdo_ipc_GateMP_RemoteProtect_NONE
#define GateMP_RemoteProtect_SYSTEM ti_sdo_ipc_GateMP_RemoteProtect_SYSTEM
#define GateMP_RemoteProtect_CUSTOM1 ti_sdo_ipc_GateMP_RemoteProtect_CUSTOM1
#define GateMP_RemoteProtect_CUSTOM2 ti_sdo_ipc_GateMP_RemoteProtect_CUSTOM2
#define GateMP_E_gateUnavailable ti_sdo_ipc_GateMP_E_gateUnavailable
#define GateMP_E_localGate ti_sdo_ipc_GateMP_E_localGate
#define GateMP_A_invalidClose ti_sdo_ipc_GateMP_A_invalidClose
#define GateMP_A_invalidDelete ti_sdo_ipc_GateMP_A_invalidDelete
#define GateMP_LM_enter ti_sdo_ipc_GateMP_LM_enter
#define GateMP_LM_leave ti_sdo_ipc_GateMP_LM_leave
#define GateMP_LM_create ti_sdo_ipc_GateMP_LM_create
#define GateMP_LM_open ti_sdo_ipc_GateMP_LM_open
#define GateMP_LM_delete ti_sdo_ipc_GateMP_LM_delete
#define GateMP_LM_close ti_sdo_ipc_GateMP_LM_close
#define GateMP_maxNameLen ti_sdo_ipc_GateMP_maxNameLen
#define GateMP_Params ti_sdo_ipc_GateMP_Params
#define GateMP_createLocal ti_sdo_ipc_GateMP_createLocal
#define GateMP_attach ti_sdo_ipc_GateMP_attach
#define GateMP_detach ti_sdo_ipc_GateMP_detach
#define GateMP_getRegion0ReservedSize ti_sdo_ipc_GateMP_getRegion0ReservedSize
#define GateMP_setRegion0Reserved ti_sdo_ipc_GateMP_setRegion0Reserved
#define GateMP_openRegion0Reserved ti_sdo_ipc_GateMP_openRegion0Reserved
#define GateMP_setDefaultRemote ti_sdo_ipc_GateMP_setDefaultRemote
#define GateMP_start ti_sdo_ipc_GateMP_start
#define GateMP_stop ti_sdo_ipc_GateMP_stop
#define GateMP_getSharedAddr ti_sdo_ipc_GateMP_getSharedAddr
#define GateMP_Module_name ti_sdo_ipc_GateMP_Module_name
#define GateMP_Module_id ti_sdo_ipc_GateMP_Module_id
#define GateMP_Module_startup ti_sdo_ipc_GateMP_Module_startup
#define GateMP_Module_startupDone ti_sdo_ipc_GateMP_Module_startupDone
#define GateMP_Module_hasMask ti_sdo_ipc_GateMP_Module_hasMask
#define GateMP_Module_getMask ti_sdo_ipc_GateMP_Module_getMask
#define GateMP_Module_setMask ti_sdo_ipc_GateMP_Module_setMask
#define GateMP_Object_heap ti_sdo_ipc_GateMP_Object_heap
#define GateMP_Module_heap ti_sdo_ipc_GateMP_Module_heap
#define GateMP_construct ti_sdo_ipc_GateMP_construct
#define GateMP_create ti_sdo_ipc_GateMP_create
#define GateMP_handle ti_sdo_ipc_GateMP_handle
#define GateMP_struct ti_sdo_ipc_GateMP_struct
#define GateMP_Handle_label ti_sdo_ipc_GateMP_Handle_label
#define GateMP_Handle_name ti_sdo_ipc_GateMP_Handle_name
#define GateMP_Instance_init ti_sdo_ipc_GateMP_Instance_init
#define GateMP_Object_count ti_sdo_ipc_GateMP_Object_count
#define GateMP_Object_get ti_sdo_ipc_GateMP_Object_get
#define GateMP_Object_first ti_sdo_ipc_GateMP_Object_first
#define GateMP_Object_next ti_sdo_ipc_GateMP_Object_next
#define GateMP_Object_sizeof ti_sdo_ipc_GateMP_Object_sizeof
#define GateMP_Params_copy ti_sdo_ipc_GateMP_Params_copy
#define GateMP_Params_init ti_sdo_ipc_GateMP_Params_init
#define GateMP_Instance_finalize ti_sdo_ipc_GateMP_Instance_finalize
#define GateMP_delete ti_sdo_ipc_GateMP_delete
#define GateMP_destruct ti_sdo_ipc_GateMP_destruct

/* proxies */
#include <ti/sdo/ipc/package/GateMP_RemoteSystemProxy.h>

/* proxies */
#include <ti/sdo/ipc/package/GateMP_RemoteCustom1Proxy.h>

/* proxies */
#include <ti/sdo/ipc/package/GateMP_RemoteCustom2Proxy.h>

#endif /* ti_sdo_ipc_GateMP__localnames__done */
#endif
