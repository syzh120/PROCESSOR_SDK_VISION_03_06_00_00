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

#ifndef ti_sdo_ipc_GateMP_RemoteCustom1Proxy__include
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy___VERS 160


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
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Q_BLOCKING (1)

/* Q_PREEMPTING */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Q_PREEMPTING (2)


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Args__create {
    xdc_runtime_IGateProvider_Handle localGate;
} ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Args__create;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__diagsEnabled ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__diagsIncluded ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__diagsMask ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__gateObj ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__gatePrms ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__id ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerDefined ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerObj ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn0 ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn1 ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn2 ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn4 ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn8 ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__startupDoneFxn ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__count ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__heap ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__sizeof ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__table ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params {
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
struct ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Struct {
    const ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Fxns__ *__fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle);
    xdc_Void (*leave)(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle, xdc_IArg);
    xdc_Bits32 *(*getReservedMask)(void);
    xdc_SizeT (*sharedMemReq)(const ti_sdo_ipc_interfaces_IGateMPSupport_Params*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Fxns__ ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_startup( state ) (-1)

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle__label__S, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__startupDone__S, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__create__S, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_create, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_create")
__extern ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle ti_sdo_ipc_GateMP_RemoteCustom1Proxy_create( xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__delete__S, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_delete, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_delete")
__extern void ti_sdo_ipc_GateMP_RemoteCustom1Proxy_delete(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__destruct__S, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__get__S, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__first__S, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__next__S, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params__init__S, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params__init__S")
__extern xdc_Void ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__abstract__S, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__abstract__S")
__extern xdc_Bool ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__delegate__S, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__delegate__S")
__extern xdc_Ptr ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__delegate__S( void );

/* query__E */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_query ti_sdo_ipc_GateMP_RemoteCustom1Proxy_query__E
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_query__E, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_query")
__extern xdc_Bool ti_sdo_ipc_GateMP_RemoteCustom1Proxy_query__E( xdc_Int qual );

/* enter__E */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_enter ti_sdo_ipc_GateMP_RemoteCustom1Proxy_enter__E
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_enter__E, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_enter")
__extern xdc_IArg ti_sdo_ipc_GateMP_RemoteCustom1Proxy_enter__E( ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle __inst );

/* leave__E */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_leave ti_sdo_ipc_GateMP_RemoteCustom1Proxy_leave__E
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_leave__E, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_leave")
__extern xdc_Void ti_sdo_ipc_GateMP_RemoteCustom1Proxy_leave__E( ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle __inst, xdc_IArg key );

/* getReservedMask__E */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_getReservedMask ti_sdo_ipc_GateMP_RemoteCustom1Proxy_getReservedMask__E
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_getReservedMask__E, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_getReservedMask")
__extern xdc_Bits32 *ti_sdo_ipc_GateMP_RemoteCustom1Proxy_getReservedMask__E( void );

/* sharedMemReq__E */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_sharedMemReq ti_sdo_ipc_GateMP_RemoteCustom1Proxy_sharedMemReq__E
xdc__CODESECT(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_sharedMemReq__E, "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_GateMP_RemoteCustom1Proxy_sharedMemReq__E( const ti_sdo_ipc_interfaces_IGateMPSupport_Params *params );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Module ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_upCast( void )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Module)ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__delegate__S();
}

/* Module_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_upCast

/* Handle_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Handle ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_upCast( ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle i )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_downCast( ti_sdo_ipc_interfaces_IGateMPSupport_Handle i )
{
    ti_sdo_ipc_interfaces_IGateMPSupport_Handle i2 = (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
    if (ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__abstract__S()) {
        return (ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle)i;
    }
    return (const void*)i2->__fxns == (const void*)ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__delegate__S() ? (ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle)i : (ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle)0;
}

/* Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_downCast

/* Module_upCast2 */
static inline xdc_runtime_IGateProvider_Module ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_upCast2( void )
{
    return (xdc_runtime_IGateProvider_Module)ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__delegate__S();
}

/* Module_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_upCast2

/* Handle_upCast2 */
static inline xdc_runtime_IGateProvider_Handle ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_upCast2( ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_upCast2

/* Handle_downCast2 */
static inline ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_downCast2( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
    if (ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__abstract__S()) {
        return (ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle)i;
    }
    return (const void*)i2->__fxns == (const void*)ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__delegate__S() ? (ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle)i : (ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle)0;
}

/* Handle_from_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_downCast2


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_startupDone() ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object_heap() ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_heap() ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__id ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_id( void ) 
{
    return ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module__id__C;
}

/* Proxy_abstract */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy_abstract() ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__abstract__S()

/* Proxy_delegate */
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy_delegate() ((ti_sdo_ipc_interfaces_IGateMPSupport_Module)ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy__delegate__S())

/* Params_init */
static inline void ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params_init( ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params_copy(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params *dst, const ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_GateMP_RemoteCustom1Proxy__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_GateMP_RemoteCustom1Proxy__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_GateMP_RemoteCustom1Proxy__nolocalnames)

#ifndef ti_sdo_ipc_GateMP_RemoteCustom1Proxy__localnames__done
#define ti_sdo_ipc_GateMP_RemoteCustom1Proxy__localnames__done

/* module prefix */
#define GateMP_RemoteCustom1Proxy_Instance ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Instance
#define GateMP_RemoteCustom1Proxy_Handle ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle
#define GateMP_RemoteCustom1Proxy_Module ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module
#define GateMP_RemoteCustom1Proxy_Object ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object
#define GateMP_RemoteCustom1Proxy_Struct ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Struct
#define GateMP_RemoteCustom1Proxy_Q_BLOCKING ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Q_BLOCKING
#define GateMP_RemoteCustom1Proxy_Q_PREEMPTING ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Q_PREEMPTING
#define GateMP_RemoteCustom1Proxy_Params ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params
#define GateMP_RemoteCustom1Proxy_query ti_sdo_ipc_GateMP_RemoteCustom1Proxy_query
#define GateMP_RemoteCustom1Proxy_enter ti_sdo_ipc_GateMP_RemoteCustom1Proxy_enter
#define GateMP_RemoteCustom1Proxy_leave ti_sdo_ipc_GateMP_RemoteCustom1Proxy_leave
#define GateMP_RemoteCustom1Proxy_getReservedMask ti_sdo_ipc_GateMP_RemoteCustom1Proxy_getReservedMask
#define GateMP_RemoteCustom1Proxy_sharedMemReq ti_sdo_ipc_GateMP_RemoteCustom1Proxy_sharedMemReq
#define GateMP_RemoteCustom1Proxy_Module_name ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_name
#define GateMP_RemoteCustom1Proxy_Module_id ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_id
#define GateMP_RemoteCustom1Proxy_Module_startup ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_startup
#define GateMP_RemoteCustom1Proxy_Module_startupDone ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_startupDone
#define GateMP_RemoteCustom1Proxy_Module_hasMask ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_hasMask
#define GateMP_RemoteCustom1Proxy_Module_getMask ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_getMask
#define GateMP_RemoteCustom1Proxy_Module_setMask ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_setMask
#define GateMP_RemoteCustom1Proxy_Object_heap ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object_heap
#define GateMP_RemoteCustom1Proxy_Module_heap ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_heap
#define GateMP_RemoteCustom1Proxy_construct ti_sdo_ipc_GateMP_RemoteCustom1Proxy_construct
#define GateMP_RemoteCustom1Proxy_create ti_sdo_ipc_GateMP_RemoteCustom1Proxy_create
#define GateMP_RemoteCustom1Proxy_handle ti_sdo_ipc_GateMP_RemoteCustom1Proxy_handle
#define GateMP_RemoteCustom1Proxy_struct ti_sdo_ipc_GateMP_RemoteCustom1Proxy_struct
#define GateMP_RemoteCustom1Proxy_Handle_label ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_label
#define GateMP_RemoteCustom1Proxy_Handle_name ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_name
#define GateMP_RemoteCustom1Proxy_Instance_init ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Instance_init
#define GateMP_RemoteCustom1Proxy_Object_count ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object_count
#define GateMP_RemoteCustom1Proxy_Object_get ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object_get
#define GateMP_RemoteCustom1Proxy_Object_first ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object_first
#define GateMP_RemoteCustom1Proxy_Object_next ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object_next
#define GateMP_RemoteCustom1Proxy_Object_sizeof ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Object_sizeof
#define GateMP_RemoteCustom1Proxy_Params_copy ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params_copy
#define GateMP_RemoteCustom1Proxy_Params_init ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params_init
#define GateMP_RemoteCustom1Proxy_Instance_State ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Instance_State
#define GateMP_RemoteCustom1Proxy_Proxy_abstract ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy_abstract
#define GateMP_RemoteCustom1Proxy_Proxy_delegate ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Proxy_delegate
#define GateMP_RemoteCustom1Proxy_delete ti_sdo_ipc_GateMP_RemoteCustom1Proxy_delete
#define GateMP_RemoteCustom1Proxy_destruct ti_sdo_ipc_GateMP_RemoteCustom1Proxy_destruct
#define GateMP_RemoteCustom1Proxy_Module_upCast ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_upCast
#define GateMP_RemoteCustom1Proxy_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateMP_RemoteCustom1Proxy_Handle_upCast ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_upCast
#define GateMP_RemoteCustom1Proxy_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateMP_RemoteCustom1Proxy_Handle_downCast ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_downCast
#define GateMP_RemoteCustom1Proxy_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateMP_RemoteCustom1Proxy_Module_upCast2 ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_upCast2
#define GateMP_RemoteCustom1Proxy_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module_to_xdc_runtime_IGateProvider
#define GateMP_RemoteCustom1Proxy_Handle_upCast2 ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_upCast2
#define GateMP_RemoteCustom1Proxy_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_to_xdc_runtime_IGateProvider
#define GateMP_RemoteCustom1Proxy_Handle_downCast2 ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_downCast2
#define GateMP_RemoteCustom1Proxy_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_from_xdc_runtime_IGateProvider

#endif /* ti_sdo_ipc_GateMP_RemoteCustom1Proxy__localnames__done */
#endif
