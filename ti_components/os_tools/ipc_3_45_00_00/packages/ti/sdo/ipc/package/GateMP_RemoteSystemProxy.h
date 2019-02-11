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
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_sdo_ipc_GateMP_RemoteSystemProxy__include
#define ti_sdo_ipc_GateMP_RemoteSystemProxy__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_GateMP_RemoteSystemProxy__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_GateMP_RemoteSystemProxy___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/package/package.defs.h>

#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Q_BLOCKING (1)

/* Q_PREEMPTING */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Q_PREEMPTING (2)


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_GateMP_RemoteSystemProxy_Args__create {
    xdc_runtime_IGateProvider_Handle localGate;
} ti_sdo_ipc_GateMP_RemoteSystemProxy_Args__create;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__diagsEnabled ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__diagsIncluded ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__diagsMask ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__gateObj ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__gatePrms ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__id ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerDefined ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerObj ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn0 ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn1 ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn2 ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn4 ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn8 ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__startupDoneFxn ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__count ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__heap ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__sizeof ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__table ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_GateMP_RemoteSystemProxy_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_UInt resourceId;
    xdc_Bool openFlag;
    xdc_UInt16 regionId;
    xdc_Ptr sharedAddr;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_GateMP_RemoteSystemProxy_Struct {
    const ti_sdo_ipc_GateMP_RemoteSystemProxy_Fxns__ *__fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_GateMP_RemoteSystemProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle);
    xdc_Void (*leave)(ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle, xdc_IArg);
    xdc_Bits32 *(*getReservedMask)(void);
    xdc_SizeT (*sharedMemReq)(const ti_sdo_ipc_interfaces_IGateMPSupport_Params*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_GateMP_RemoteSystemProxy_Fxns__ ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_startup( state ) (-1)

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle__label__S, "ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__startupDone__S, "ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__create__S, "ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_create, "ti_sdo_ipc_GateMP_RemoteSystemProxy_create")
__extern ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle ti_sdo_ipc_GateMP_RemoteSystemProxy_create( xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_GateMP_RemoteSystemProxy_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__delete__S, "ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_delete, "ti_sdo_ipc_GateMP_RemoteSystemProxy_delete")
__extern void ti_sdo_ipc_GateMP_RemoteSystemProxy_delete(ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__destruct__S, "ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__get__S, "ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__first__S, "ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__next__S, "ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_Params__init__S, "ti_sdo_ipc_GateMP_RemoteSystemProxy_Params__init__S")
__extern xdc_Void ti_sdo_ipc_GateMP_RemoteSystemProxy_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__abstract__S, "ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__abstract__S")
__extern xdc_Bool ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__delegate__S, "ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__delegate__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__delegate__S( void );

/* query__E */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_query ti_sdo_ipc_GateMP_RemoteSystemProxy_query__E
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_query__E, "ti_sdo_ipc_GateMP_RemoteSystemProxy_query")
__extern xdc_Bool ti_sdo_ipc_GateMP_RemoteSystemProxy_query__E( xdc_Int qual );

/* enter__E */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_enter ti_sdo_ipc_GateMP_RemoteSystemProxy_enter__E
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_enter__E, "ti_sdo_ipc_GateMP_RemoteSystemProxy_enter")
__extern xdc_IArg ti_sdo_ipc_GateMP_RemoteSystemProxy_enter__E( ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle __inst );

/* leave__E */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_leave ti_sdo_ipc_GateMP_RemoteSystemProxy_leave__E
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_leave__E, "ti_sdo_ipc_GateMP_RemoteSystemProxy_leave")
__extern xdc_Void ti_sdo_ipc_GateMP_RemoteSystemProxy_leave__E( ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle __inst, xdc_IArg key );

/* getReservedMask__E */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_getReservedMask ti_sdo_ipc_GateMP_RemoteSystemProxy_getReservedMask__E
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_getReservedMask__E, "ti_sdo_ipc_GateMP_RemoteSystemProxy_getReservedMask")
__extern xdc_Bits32 *ti_sdo_ipc_GateMP_RemoteSystemProxy_getReservedMask__E( void );

/* sharedMemReq__E */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_sharedMemReq ti_sdo_ipc_GateMP_RemoteSystemProxy_sharedMemReq__E
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteSystemProxy_sharedMemReq__E, "ti_sdo_ipc_GateMP_RemoteSystemProxy_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_GateMP_RemoteSystemProxy_sharedMemReq__E( const ti_sdo_ipc_interfaces_IGateMPSupport_Params *params );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Module ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_upCast( void )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Module)ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__delegate__S();
}

/* Module_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_upCast

/* Handle_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Handle ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_upCast( ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle i )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_downCast( ti_sdo_ipc_interfaces_IGateMPSupport_Handle i )
{
    ti_sdo_ipc_interfaces_IGateMPSupport_Handle i2 = (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
    if (ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__abstract__S()) {
        return (ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle)i;
    }
    return (const void*)i2->__fxns == (const void*)ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__delegate__S() ? (ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle)i : (ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle)0;
}

/* Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_downCast

/* Module_upCast2 */
static inline xdc_runtime_IGateProvider_Module ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_upCast2( void )
{
    return (xdc_runtime_IGateProvider_Module)ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__delegate__S();
}

/* Module_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_upCast2

/* Handle_upCast2 */
static inline xdc_runtime_IGateProvider_Handle ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_upCast2( ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_upCast2

/* Handle_downCast2 */
static inline ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_downCast2( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
    if (ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__abstract__S()) {
        return (ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle)i;
    }
    return (const void*)i2->__fxns == (const void*)ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__delegate__S() ? (ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle)i : (ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle)0;
}

/* Handle_from_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_downCast2


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_startupDone() ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Object_heap() ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_heap() ti_sdo_ipc_GateMP_RemoteSystemProxy_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__id ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_id( void ) 
{
    return ti_sdo_ipc_GateMP_RemoteSystemProxy_Module__id__C;
}

/* Proxy_abstract */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy_abstract() ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__abstract__S()

/* Proxy_delegate */
#define ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy_delegate() ((ti_sdo_ipc_interfaces_IGateMPSupport_Module)ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy__delegate__S())

/* Params_init */
static inline void ti_sdo_ipc_GateMP_RemoteSystemProxy_Params_init( ti_sdo_ipc_GateMP_RemoteSystemProxy_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_GateMP_RemoteSystemProxy_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_GateMP_RemoteSystemProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_GateMP_RemoteSystemProxy_Params_copy(ti_sdo_ipc_GateMP_RemoteSystemProxy_Params *dst, const ti_sdo_ipc_GateMP_RemoteSystemProxy_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_GateMP_RemoteSystemProxy_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_GateMP_RemoteSystemProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_GateMP_RemoteSystemProxy__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_GateMP_RemoteSystemProxy__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_GateMP_RemoteSystemProxy__nolocalnames)

#ifndef ti_sdo_ipc_GateMP_RemoteSystemProxy__localnames__done
#define ti_sdo_ipc_GateMP_RemoteSystemProxy__localnames__done

/* module prefix */
#define GateMP_RemoteSystemProxy_Instance ti_sdo_ipc_GateMP_RemoteSystemProxy_Instance
#define GateMP_RemoteSystemProxy_Handle ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle
#define GateMP_RemoteSystemProxy_Module ti_sdo_ipc_GateMP_RemoteSystemProxy_Module
#define GateMP_RemoteSystemProxy_Object ti_sdo_ipc_GateMP_RemoteSystemProxy_Object
#define GateMP_RemoteSystemProxy_Struct ti_sdo_ipc_GateMP_RemoteSystemProxy_Struct
#define GateMP_RemoteSystemProxy_Q_BLOCKING ti_sdo_ipc_GateMP_RemoteSystemProxy_Q_BLOCKING
#define GateMP_RemoteSystemProxy_Q_PREEMPTING ti_sdo_ipc_GateMP_RemoteSystemProxy_Q_PREEMPTING
#define GateMP_RemoteSystemProxy_Params ti_sdo_ipc_GateMP_RemoteSystemProxy_Params
#define GateMP_RemoteSystemProxy_query ti_sdo_ipc_GateMP_RemoteSystemProxy_query
#define GateMP_RemoteSystemProxy_enter ti_sdo_ipc_GateMP_RemoteSystemProxy_enter
#define GateMP_RemoteSystemProxy_leave ti_sdo_ipc_GateMP_RemoteSystemProxy_leave
#define GateMP_RemoteSystemProxy_getReservedMask ti_sdo_ipc_GateMP_RemoteSystemProxy_getReservedMask
#define GateMP_RemoteSystemProxy_sharedMemReq ti_sdo_ipc_GateMP_RemoteSystemProxy_sharedMemReq
#define GateMP_RemoteSystemProxy_Module_name ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_name
#define GateMP_RemoteSystemProxy_Module_id ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_id
#define GateMP_RemoteSystemProxy_Module_startup ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_startup
#define GateMP_RemoteSystemProxy_Module_startupDone ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_startupDone
#define GateMP_RemoteSystemProxy_Module_hasMask ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_hasMask
#define GateMP_RemoteSystemProxy_Module_getMask ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_getMask
#define GateMP_RemoteSystemProxy_Module_setMask ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_setMask
#define GateMP_RemoteSystemProxy_Object_heap ti_sdo_ipc_GateMP_RemoteSystemProxy_Object_heap
#define GateMP_RemoteSystemProxy_Module_heap ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_heap
#define GateMP_RemoteSystemProxy_construct ti_sdo_ipc_GateMP_RemoteSystemProxy_construct
#define GateMP_RemoteSystemProxy_create ti_sdo_ipc_GateMP_RemoteSystemProxy_create
#define GateMP_RemoteSystemProxy_handle ti_sdo_ipc_GateMP_RemoteSystemProxy_handle
#define GateMP_RemoteSystemProxy_struct ti_sdo_ipc_GateMP_RemoteSystemProxy_struct
#define GateMP_RemoteSystemProxy_Handle_label ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_label
#define GateMP_RemoteSystemProxy_Handle_name ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_name
#define GateMP_RemoteSystemProxy_Instance_init ti_sdo_ipc_GateMP_RemoteSystemProxy_Instance_init
#define GateMP_RemoteSystemProxy_Object_count ti_sdo_ipc_GateMP_RemoteSystemProxy_Object_count
#define GateMP_RemoteSystemProxy_Object_get ti_sdo_ipc_GateMP_RemoteSystemProxy_Object_get
#define GateMP_RemoteSystemProxy_Object_first ti_sdo_ipc_GateMP_RemoteSystemProxy_Object_first
#define GateMP_RemoteSystemProxy_Object_next ti_sdo_ipc_GateMP_RemoteSystemProxy_Object_next
#define GateMP_RemoteSystemProxy_Object_sizeof ti_sdo_ipc_GateMP_RemoteSystemProxy_Object_sizeof
#define GateMP_RemoteSystemProxy_Params_copy ti_sdo_ipc_GateMP_RemoteSystemProxy_Params_copy
#define GateMP_RemoteSystemProxy_Params_init ti_sdo_ipc_GateMP_RemoteSystemProxy_Params_init
#define GateMP_RemoteSystemProxy_Instance_State ti_sdo_ipc_GateMP_RemoteSystemProxy_Instance_State
#define GateMP_RemoteSystemProxy_Proxy_abstract ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy_abstract
#define GateMP_RemoteSystemProxy_Proxy_delegate ti_sdo_ipc_GateMP_RemoteSystemProxy_Proxy_delegate
#define GateMP_RemoteSystemProxy_delete ti_sdo_ipc_GateMP_RemoteSystemProxy_delete
#define GateMP_RemoteSystemProxy_destruct ti_sdo_ipc_GateMP_RemoteSystemProxy_destruct
#define GateMP_RemoteSystemProxy_Module_upCast ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_upCast
#define GateMP_RemoteSystemProxy_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateMP_RemoteSystemProxy_Handle_upCast ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_upCast
#define GateMP_RemoteSystemProxy_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateMP_RemoteSystemProxy_Handle_downCast ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_downCast
#define GateMP_RemoteSystemProxy_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateMP_RemoteSystemProxy_Module_upCast2 ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_upCast2
#define GateMP_RemoteSystemProxy_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteSystemProxy_Module_to_xdc_runtime_IGateProvider
#define GateMP_RemoteSystemProxy_Handle_upCast2 ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_upCast2
#define GateMP_RemoteSystemProxy_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_to_xdc_runtime_IGateProvider
#define GateMP_RemoteSystemProxy_Handle_downCast2 ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_downCast2
#define GateMP_RemoteSystemProxy_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_from_xdc_runtime_IGateProvider

#endif /* ti_sdo_ipc_GateMP_RemoteSystemProxy__localnames__done */
#endif
