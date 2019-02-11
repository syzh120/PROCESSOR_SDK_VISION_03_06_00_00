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

#ifndef ti_sdo_ipc_Notify_Module_GateProxy__include
#define ti_sdo_ipc_Notify_Module_GateProxy__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_Notify_Module_GateProxy__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_Notify_Module_GateProxy___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/package/package.defs.h>

#include <xdc/runtime/IGateProvider.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */
#define ti_sdo_ipc_Notify_Module_GateProxy_Q_BLOCKING (1)

/* Q_PREEMPTING */
#define ti_sdo_ipc_Notify_Module_GateProxy_Q_PREEMPTING (2)


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__diagsEnabled ti_sdo_ipc_Notify_Module_GateProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__diagsIncluded ti_sdo_ipc_Notify_Module_GateProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__diagsMask ti_sdo_ipc_Notify_Module_GateProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__gateObj ti_sdo_ipc_Notify_Module_GateProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__gatePrms ti_sdo_ipc_Notify_Module_GateProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__id ti_sdo_ipc_Notify_Module_GateProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerDefined ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerObj ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn0 ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn1 ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn2 ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn4 ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn8 ti_sdo_ipc_Notify_Module_GateProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__startupDoneFxn ti_sdo_ipc_Notify_Module_GateProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_Notify_Module_GateProxy_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Object__count ti_sdo_ipc_Notify_Module_GateProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_Notify_Module_GateProxy_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Object__heap ti_sdo_ipc_Notify_Module_GateProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_Notify_Module_GateProxy_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Object__sizeof ti_sdo_ipc_Notify_Module_GateProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_Notify_Module_GateProxy_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module_GateProxy_Object__table ti_sdo_ipc_Notify_Module_GateProxy_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_Notify_Module_GateProxy_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_Notify_Module_GateProxy_Struct {
    const ti_sdo_ipc_Notify_Module_GateProxy_Fxns__ *__fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_Notify_Module_GateProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(ti_sdo_ipc_Notify_Module_GateProxy_Handle);
    xdc_Void (*leave)(ti_sdo_ipc_Notify_Module_GateProxy_Handle, xdc_IArg);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_Notify_Module_GateProxy_Fxns__ ti_sdo_ipc_Notify_Module_GateProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_Notify_Module_GateProxy_Module_startup( state ) (-1)

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_Handle__label__S, "ti_sdo_ipc_Notify_Module_GateProxy_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_Notify_Module_GateProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_Module__startupDone__S, "ti_sdo_ipc_Notify_Module_GateProxy_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_Notify_Module_GateProxy_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_Object__create__S, "ti_sdo_ipc_Notify_Module_GateProxy_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_Notify_Module_GateProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_create, "ti_sdo_ipc_Notify_Module_GateProxy_create")
__extern ti_sdo_ipc_Notify_Module_GateProxy_Handle ti_sdo_ipc_Notify_Module_GateProxy_create( const ti_sdo_ipc_Notify_Module_GateProxy_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_Object__delete__S, "ti_sdo_ipc_Notify_Module_GateProxy_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_Notify_Module_GateProxy_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_delete, "ti_sdo_ipc_Notify_Module_GateProxy_delete")
__extern void ti_sdo_ipc_Notify_Module_GateProxy_delete(ti_sdo_ipc_Notify_Module_GateProxy_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_Object__destruct__S, "ti_sdo_ipc_Notify_Module_GateProxy_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_Notify_Module_GateProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_Object__get__S, "ti_sdo_ipc_Notify_Module_GateProxy_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_Notify_Module_GateProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_Object__first__S, "ti_sdo_ipc_Notify_Module_GateProxy_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_Notify_Module_GateProxy_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_Object__next__S, "ti_sdo_ipc_Notify_Module_GateProxy_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_Notify_Module_GateProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_Params__init__S, "ti_sdo_ipc_Notify_Module_GateProxy_Params__init__S")
__extern xdc_Void ti_sdo_ipc_Notify_Module_GateProxy_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_Proxy__abstract__S, "ti_sdo_ipc_Notify_Module_GateProxy_Proxy__abstract__S")
__extern xdc_Bool ti_sdo_ipc_Notify_Module_GateProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_Proxy__delegate__S, "ti_sdo_ipc_Notify_Module_GateProxy_Proxy__delegate__S")
__extern xdc_Ptr ti_sdo_ipc_Notify_Module_GateProxy_Proxy__delegate__S( void );

/* query__E */
#define ti_sdo_ipc_Notify_Module_GateProxy_query ti_sdo_ipc_Notify_Module_GateProxy_query__E
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_query__E, "ti_sdo_ipc_Notify_Module_GateProxy_query")
__extern xdc_Bool ti_sdo_ipc_Notify_Module_GateProxy_query__E( xdc_Int qual );

/* enter__E */
#define ti_sdo_ipc_Notify_Module_GateProxy_enter ti_sdo_ipc_Notify_Module_GateProxy_enter__E
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_enter__E, "ti_sdo_ipc_Notify_Module_GateProxy_enter")
__extern xdc_IArg ti_sdo_ipc_Notify_Module_GateProxy_enter__E( ti_sdo_ipc_Notify_Module_GateProxy_Handle __inst );

/* leave__E */
#define ti_sdo_ipc_Notify_Module_GateProxy_leave ti_sdo_ipc_Notify_Module_GateProxy_leave__E
xdc__CODESECT(ti_sdo_ipc_Notify_Module_GateProxy_leave__E, "ti_sdo_ipc_Notify_Module_GateProxy_leave")
__extern xdc_Void ti_sdo_ipc_Notify_Module_GateProxy_leave__E( ti_sdo_ipc_Notify_Module_GateProxy_Handle __inst, xdc_IArg key );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_IGateProvider_Module ti_sdo_ipc_Notify_Module_GateProxy_Module_upCast( void )
{
    return (xdc_runtime_IGateProvider_Module)ti_sdo_ipc_Notify_Module_GateProxy_Proxy__delegate__S();
}

/* Module_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_Notify_Module_GateProxy_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_Notify_Module_GateProxy_Module_upCast

/* Handle_upCast */
static inline xdc_runtime_IGateProvider_Handle ti_sdo_ipc_Notify_Module_GateProxy_Handle_upCast( ti_sdo_ipc_Notify_Module_GateProxy_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_Notify_Module_GateProxy_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_Notify_Module_GateProxy_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_Notify_Module_GateProxy_Handle ti_sdo_ipc_Notify_Module_GateProxy_Handle_downCast( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
    if (ti_sdo_ipc_Notify_Module_GateProxy_Proxy__abstract__S()) {
        return (ti_sdo_ipc_Notify_Module_GateProxy_Handle)i;
    }
    return (const void*)i2->__fxns == (const void*)ti_sdo_ipc_Notify_Module_GateProxy_Proxy__delegate__S() ? (ti_sdo_ipc_Notify_Module_GateProxy_Handle)i : (ti_sdo_ipc_Notify_Module_GateProxy_Handle)0;
}

/* Handle_from_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_Notify_Module_GateProxy_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_Notify_Module_GateProxy_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_Notify_Module_GateProxy_Module_startupDone() ti_sdo_ipc_Notify_Module_GateProxy_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_Notify_Module_GateProxy_Object_heap() ti_sdo_ipc_Notify_Module_GateProxy_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_Notify_Module_GateProxy_Module_heap() ti_sdo_ipc_Notify_Module_GateProxy_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_Notify_Module_GateProxy_Module__id ti_sdo_ipc_Notify_Module_GateProxy_Module_id( void ) 
{
    return ti_sdo_ipc_Notify_Module_GateProxy_Module__id__C;
}

/* Proxy_abstract */
#define ti_sdo_ipc_Notify_Module_GateProxy_Proxy_abstract() ti_sdo_ipc_Notify_Module_GateProxy_Proxy__abstract__S()

/* Proxy_delegate */
#define ti_sdo_ipc_Notify_Module_GateProxy_Proxy_delegate() ((xdc_runtime_IGateProvider_Module)ti_sdo_ipc_Notify_Module_GateProxy_Proxy__delegate__S())

/* Params_init */
static inline void ti_sdo_ipc_Notify_Module_GateProxy_Params_init( ti_sdo_ipc_Notify_Module_GateProxy_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_Notify_Module_GateProxy_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_Notify_Module_GateProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_Notify_Module_GateProxy_Params_copy(ti_sdo_ipc_Notify_Module_GateProxy_Params *dst, const ti_sdo_ipc_Notify_Module_GateProxy_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_Notify_Module_GateProxy_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_Notify_Module_GateProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_Notify_Module_GateProxy__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_Notify_Module_GateProxy__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_Notify_Module_GateProxy__nolocalnames)

#ifndef ti_sdo_ipc_Notify_Module_GateProxy__localnames__done
#define ti_sdo_ipc_Notify_Module_GateProxy__localnames__done

/* module prefix */
#define Notify_Module_GateProxy_Instance ti_sdo_ipc_Notify_Module_GateProxy_Instance
#define Notify_Module_GateProxy_Handle ti_sdo_ipc_Notify_Module_GateProxy_Handle
#define Notify_Module_GateProxy_Module ti_sdo_ipc_Notify_Module_GateProxy_Module
#define Notify_Module_GateProxy_Object ti_sdo_ipc_Notify_Module_GateProxy_Object
#define Notify_Module_GateProxy_Struct ti_sdo_ipc_Notify_Module_GateProxy_Struct
#define Notify_Module_GateProxy_Q_BLOCKING ti_sdo_ipc_Notify_Module_GateProxy_Q_BLOCKING
#define Notify_Module_GateProxy_Q_PREEMPTING ti_sdo_ipc_Notify_Module_GateProxy_Q_PREEMPTING
#define Notify_Module_GateProxy_Params ti_sdo_ipc_Notify_Module_GateProxy_Params
#define Notify_Module_GateProxy_query ti_sdo_ipc_Notify_Module_GateProxy_query
#define Notify_Module_GateProxy_enter ti_sdo_ipc_Notify_Module_GateProxy_enter
#define Notify_Module_GateProxy_leave ti_sdo_ipc_Notify_Module_GateProxy_leave
#define Notify_Module_GateProxy_Module_name ti_sdo_ipc_Notify_Module_GateProxy_Module_name
#define Notify_Module_GateProxy_Module_id ti_sdo_ipc_Notify_Module_GateProxy_Module_id
#define Notify_Module_GateProxy_Module_startup ti_sdo_ipc_Notify_Module_GateProxy_Module_startup
#define Notify_Module_GateProxy_Module_startupDone ti_sdo_ipc_Notify_Module_GateProxy_Module_startupDone
#define Notify_Module_GateProxy_Module_hasMask ti_sdo_ipc_Notify_Module_GateProxy_Module_hasMask
#define Notify_Module_GateProxy_Module_getMask ti_sdo_ipc_Notify_Module_GateProxy_Module_getMask
#define Notify_Module_GateProxy_Module_setMask ti_sdo_ipc_Notify_Module_GateProxy_Module_setMask
#define Notify_Module_GateProxy_Object_heap ti_sdo_ipc_Notify_Module_GateProxy_Object_heap
#define Notify_Module_GateProxy_Module_heap ti_sdo_ipc_Notify_Module_GateProxy_Module_heap
#define Notify_Module_GateProxy_construct ti_sdo_ipc_Notify_Module_GateProxy_construct
#define Notify_Module_GateProxy_create ti_sdo_ipc_Notify_Module_GateProxy_create
#define Notify_Module_GateProxy_handle ti_sdo_ipc_Notify_Module_GateProxy_handle
#define Notify_Module_GateProxy_struct ti_sdo_ipc_Notify_Module_GateProxy_struct
#define Notify_Module_GateProxy_Handle_label ti_sdo_ipc_Notify_Module_GateProxy_Handle_label
#define Notify_Module_GateProxy_Handle_name ti_sdo_ipc_Notify_Module_GateProxy_Handle_name
#define Notify_Module_GateProxy_Instance_init ti_sdo_ipc_Notify_Module_GateProxy_Instance_init
#define Notify_Module_GateProxy_Object_count ti_sdo_ipc_Notify_Module_GateProxy_Object_count
#define Notify_Module_GateProxy_Object_get ti_sdo_ipc_Notify_Module_GateProxy_Object_get
#define Notify_Module_GateProxy_Object_first ti_sdo_ipc_Notify_Module_GateProxy_Object_first
#define Notify_Module_GateProxy_Object_next ti_sdo_ipc_Notify_Module_GateProxy_Object_next
#define Notify_Module_GateProxy_Object_sizeof ti_sdo_ipc_Notify_Module_GateProxy_Object_sizeof
#define Notify_Module_GateProxy_Params_copy ti_sdo_ipc_Notify_Module_GateProxy_Params_copy
#define Notify_Module_GateProxy_Params_init ti_sdo_ipc_Notify_Module_GateProxy_Params_init
#define Notify_Module_GateProxy_Instance_State ti_sdo_ipc_Notify_Module_GateProxy_Instance_State
#define Notify_Module_GateProxy_Proxy_abstract ti_sdo_ipc_Notify_Module_GateProxy_Proxy_abstract
#define Notify_Module_GateProxy_Proxy_delegate ti_sdo_ipc_Notify_Module_GateProxy_Proxy_delegate
#define Notify_Module_GateProxy_delete ti_sdo_ipc_Notify_Module_GateProxy_delete
#define Notify_Module_GateProxy_destruct ti_sdo_ipc_Notify_Module_GateProxy_destruct
#define Notify_Module_GateProxy_Module_upCast ti_sdo_ipc_Notify_Module_GateProxy_Module_upCast
#define Notify_Module_GateProxy_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_Notify_Module_GateProxy_Module_to_xdc_runtime_IGateProvider
#define Notify_Module_GateProxy_Handle_upCast ti_sdo_ipc_Notify_Module_GateProxy_Handle_upCast
#define Notify_Module_GateProxy_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_Notify_Module_GateProxy_Handle_to_xdc_runtime_IGateProvider
#define Notify_Module_GateProxy_Handle_downCast ti_sdo_ipc_Notify_Module_GateProxy_Handle_downCast
#define Notify_Module_GateProxy_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_Notify_Module_GateProxy_Handle_from_xdc_runtime_IGateProvider

#endif /* ti_sdo_ipc_Notify_Module_GateProxy__localnames__done */
#endif
