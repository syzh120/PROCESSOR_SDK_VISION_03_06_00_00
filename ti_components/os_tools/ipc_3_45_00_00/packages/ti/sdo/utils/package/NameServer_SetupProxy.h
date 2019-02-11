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

#ifndef ti_sdo_utils_NameServer_SetupProxy__include
#define ti_sdo_utils_NameServer_SetupProxy__include

#ifndef __nested__
#define __nested__
#define ti_sdo_utils_NameServer_SetupProxy__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_utils_NameServer_SetupProxy___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/utils/package/package.defs.h>

#include <ti/sdo/utils/INameServerRemote.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Status */
typedef ti_sdo_utils_INameServerRemote_Status ti_sdo_utils_NameServer_SetupProxy_Status;


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_utils_NameServer_SetupProxy_Args__create {
    xdc_UInt16 procId;
} ti_sdo_utils_NameServer_SetupProxy_Args__create;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_utils_NameServer_SetupProxy_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__diagsEnabled ti_sdo_utils_NameServer_SetupProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_utils_NameServer_SetupProxy_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__diagsIncluded ti_sdo_utils_NameServer_SetupProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_utils_NameServer_SetupProxy_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__diagsMask ti_sdo_utils_NameServer_SetupProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_utils_NameServer_SetupProxy_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__gateObj ti_sdo_utils_NameServer_SetupProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_utils_NameServer_SetupProxy_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__gatePrms ti_sdo_utils_NameServer_SetupProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_utils_NameServer_SetupProxy_Module__id;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__id ti_sdo_utils_NameServer_SetupProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerDefined ti_sdo_utils_NameServer_SetupProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerObj ti_sdo_utils_NameServer_SetupProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn0 ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn1 ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn2 ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn4 ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn8 ti_sdo_utils_NameServer_SetupProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_utils_NameServer_SetupProxy_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Module__startupDoneFxn ti_sdo_utils_NameServer_SetupProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_utils_NameServer_SetupProxy_Object__count;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Object__count ti_sdo_utils_NameServer_SetupProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_utils_NameServer_SetupProxy_Object__heap;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Object__heap ti_sdo_utils_NameServer_SetupProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_utils_NameServer_SetupProxy_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Object__sizeof ti_sdo_utils_NameServer_SetupProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_utils_NameServer_SetupProxy_Object__table;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_SetupProxy_Object__table ti_sdo_utils_NameServer_SetupProxy_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_utils_NameServer_SetupProxy_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_utils_NameServer_SetupProxy_Struct {
    const ti_sdo_utils_NameServer_SetupProxy_Fxns__ *__fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_utils_NameServer_SetupProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*attach)(xdc_UInt16, xdc_Ptr);
    xdc_Int (*detach)(xdc_UInt16);
    xdc_SizeT (*sharedMemReq)(xdc_Ptr);
    xdc_Int (*get)(ti_sdo_utils_NameServer_SetupProxy_Handle, xdc_String, xdc_String, xdc_Ptr, xdc_UInt32*, xdc_runtime_knl_ISync_Handle, xdc_runtime_Error_Block*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_utils_NameServer_SetupProxy_Fxns__ ti_sdo_utils_NameServer_SetupProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_utils_NameServer_SetupProxy_Module_startup( state ) (-1)

/* Handle__label__S */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_Handle__label__S, "ti_sdo_utils_NameServer_SetupProxy_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_utils_NameServer_SetupProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_Module__startupDone__S, "ti_sdo_utils_NameServer_SetupProxy_Module__startupDone__S")
__extern xdc_Bool ti_sdo_utils_NameServer_SetupProxy_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_Object__create__S, "ti_sdo_utils_NameServer_SetupProxy_Object__create__S")
__extern xdc_Ptr ti_sdo_utils_NameServer_SetupProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_create, "ti_sdo_utils_NameServer_SetupProxy_create")
__extern ti_sdo_utils_NameServer_SetupProxy_Handle ti_sdo_utils_NameServer_SetupProxy_create( xdc_UInt16 procId, const ti_sdo_utils_NameServer_SetupProxy_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_Object__delete__S, "ti_sdo_utils_NameServer_SetupProxy_Object__delete__S")
__extern xdc_Void ti_sdo_utils_NameServer_SetupProxy_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_delete, "ti_sdo_utils_NameServer_SetupProxy_delete")
__extern void ti_sdo_utils_NameServer_SetupProxy_delete(ti_sdo_utils_NameServer_SetupProxy_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_Object__destruct__S, "ti_sdo_utils_NameServer_SetupProxy_Object__destruct__S")
__extern xdc_Void ti_sdo_utils_NameServer_SetupProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_Object__get__S, "ti_sdo_utils_NameServer_SetupProxy_Object__get__S")
__extern xdc_Ptr ti_sdo_utils_NameServer_SetupProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_Object__first__S, "ti_sdo_utils_NameServer_SetupProxy_Object__first__S")
__extern xdc_Ptr ti_sdo_utils_NameServer_SetupProxy_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_Object__next__S, "ti_sdo_utils_NameServer_SetupProxy_Object__next__S")
__extern xdc_Ptr ti_sdo_utils_NameServer_SetupProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_Params__init__S, "ti_sdo_utils_NameServer_SetupProxy_Params__init__S")
__extern xdc_Void ti_sdo_utils_NameServer_SetupProxy_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_Proxy__abstract__S, "ti_sdo_utils_NameServer_SetupProxy_Proxy__abstract__S")
__extern xdc_Bool ti_sdo_utils_NameServer_SetupProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_Proxy__delegate__S, "ti_sdo_utils_NameServer_SetupProxy_Proxy__delegate__S")
__extern xdc_Ptr ti_sdo_utils_NameServer_SetupProxy_Proxy__delegate__S( void );

/* attach__E */
#define ti_sdo_utils_NameServer_SetupProxy_attach ti_sdo_utils_NameServer_SetupProxy_attach__E
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_attach__E, "ti_sdo_utils_NameServer_SetupProxy_attach")
__extern xdc_Int ti_sdo_utils_NameServer_SetupProxy_attach__E( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* detach__E */
#define ti_sdo_utils_NameServer_SetupProxy_detach ti_sdo_utils_NameServer_SetupProxy_detach__E
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_detach__E, "ti_sdo_utils_NameServer_SetupProxy_detach")
__extern xdc_Int ti_sdo_utils_NameServer_SetupProxy_detach__E( xdc_UInt16 remoteProcId );

/* sharedMemReq__E */
#define ti_sdo_utils_NameServer_SetupProxy_sharedMemReq ti_sdo_utils_NameServer_SetupProxy_sharedMemReq__E
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_sharedMemReq__E, "ti_sdo_utils_NameServer_SetupProxy_sharedMemReq")
__extern xdc_SizeT ti_sdo_utils_NameServer_SetupProxy_sharedMemReq__E( xdc_Ptr sharedAddr );

/* get__E */
#define ti_sdo_utils_NameServer_SetupProxy_get ti_sdo_utils_NameServer_SetupProxy_get__E
xdc__CODESECT(ti_sdo_utils_NameServer_SetupProxy_get__E, "ti_sdo_utils_NameServer_SetupProxy_get")
__extern xdc_Int ti_sdo_utils_NameServer_SetupProxy_get__E( ti_sdo_utils_NameServer_SetupProxy_Handle __inst, xdc_String instanceName, xdc_String name, xdc_Ptr value, xdc_UInt32 *valueLen, xdc_runtime_knl_ISync_Handle syncHandle, xdc_runtime_Error_Block *eb );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_utils_INameServerRemote_Module ti_sdo_utils_NameServer_SetupProxy_Module_upCast( void )
{
    return (ti_sdo_utils_INameServerRemote_Module)ti_sdo_utils_NameServer_SetupProxy_Proxy__delegate__S();
}

/* Module_to_ti_sdo_utils_INameServerRemote */
#define ti_sdo_utils_NameServer_SetupProxy_Module_to_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServer_SetupProxy_Module_upCast

/* Handle_upCast */
static inline ti_sdo_utils_INameServerRemote_Handle ti_sdo_utils_NameServer_SetupProxy_Handle_upCast( ti_sdo_utils_NameServer_SetupProxy_Handle i )
{
    return (ti_sdo_utils_INameServerRemote_Handle)i;
}

/* Handle_to_ti_sdo_utils_INameServerRemote */
#define ti_sdo_utils_NameServer_SetupProxy_Handle_to_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServer_SetupProxy_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_utils_NameServer_SetupProxy_Handle ti_sdo_utils_NameServer_SetupProxy_Handle_downCast( ti_sdo_utils_INameServerRemote_Handle i )
{
    ti_sdo_utils_INameServerRemote_Handle i2 = (ti_sdo_utils_INameServerRemote_Handle)i;
    if (ti_sdo_utils_NameServer_SetupProxy_Proxy__abstract__S()) {
        return (ti_sdo_utils_NameServer_SetupProxy_Handle)i;
    }
    return (const void*)i2->__fxns == (const void*)ti_sdo_utils_NameServer_SetupProxy_Proxy__delegate__S() ? (ti_sdo_utils_NameServer_SetupProxy_Handle)i : (ti_sdo_utils_NameServer_SetupProxy_Handle)0;
}

/* Handle_from_ti_sdo_utils_INameServerRemote */
#define ti_sdo_utils_NameServer_SetupProxy_Handle_from_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServer_SetupProxy_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_utils_NameServer_SetupProxy_Module_startupDone() ti_sdo_utils_NameServer_SetupProxy_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_utils_NameServer_SetupProxy_Object_heap() ti_sdo_utils_NameServer_SetupProxy_Object__heap__C

/* Module_heap */
#define ti_sdo_utils_NameServer_SetupProxy_Module_heap() ti_sdo_utils_NameServer_SetupProxy_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_utils_NameServer_SetupProxy_Module__id ti_sdo_utils_NameServer_SetupProxy_Module_id( void ) 
{
    return ti_sdo_utils_NameServer_SetupProxy_Module__id__C;
}

/* Proxy_abstract */
#define ti_sdo_utils_NameServer_SetupProxy_Proxy_abstract() ti_sdo_utils_NameServer_SetupProxy_Proxy__abstract__S()

/* Proxy_delegate */
#define ti_sdo_utils_NameServer_SetupProxy_Proxy_delegate() ((ti_sdo_utils_INameServerRemote_Module)ti_sdo_utils_NameServer_SetupProxy_Proxy__delegate__S())

/* Params_init */
static inline void ti_sdo_utils_NameServer_SetupProxy_Params_init( ti_sdo_utils_NameServer_SetupProxy_Params *prms ) 
{
    if (prms) {
        ti_sdo_utils_NameServer_SetupProxy_Params__init__S(prms, 0, sizeof(ti_sdo_utils_NameServer_SetupProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_utils_NameServer_SetupProxy_Params_copy(ti_sdo_utils_NameServer_SetupProxy_Params *dst, const ti_sdo_utils_NameServer_SetupProxy_Params *src) 
{
    if (dst) {
        ti_sdo_utils_NameServer_SetupProxy_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_utils_NameServer_SetupProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_utils_NameServer_SetupProxy__top__
#undef __nested__
#endif

#endif /* ti_sdo_utils_NameServer_SetupProxy__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_utils_NameServer_SetupProxy__nolocalnames)

#ifndef ti_sdo_utils_NameServer_SetupProxy__localnames__done
#define ti_sdo_utils_NameServer_SetupProxy__localnames__done

/* module prefix */
#define NameServer_SetupProxy_Instance ti_sdo_utils_NameServer_SetupProxy_Instance
#define NameServer_SetupProxy_Handle ti_sdo_utils_NameServer_SetupProxy_Handle
#define NameServer_SetupProxy_Module ti_sdo_utils_NameServer_SetupProxy_Module
#define NameServer_SetupProxy_Object ti_sdo_utils_NameServer_SetupProxy_Object
#define NameServer_SetupProxy_Struct ti_sdo_utils_NameServer_SetupProxy_Struct
#define NameServer_SetupProxy_Status ti_sdo_utils_NameServer_SetupProxy_Status
#define NameServer_SetupProxy_Params ti_sdo_utils_NameServer_SetupProxy_Params
#define NameServer_SetupProxy_attach ti_sdo_utils_NameServer_SetupProxy_attach
#define NameServer_SetupProxy_detach ti_sdo_utils_NameServer_SetupProxy_detach
#define NameServer_SetupProxy_sharedMemReq ti_sdo_utils_NameServer_SetupProxy_sharedMemReq
#define NameServer_SetupProxy_get ti_sdo_utils_NameServer_SetupProxy_get
#define NameServer_SetupProxy_Module_name ti_sdo_utils_NameServer_SetupProxy_Module_name
#define NameServer_SetupProxy_Module_id ti_sdo_utils_NameServer_SetupProxy_Module_id
#define NameServer_SetupProxy_Module_startup ti_sdo_utils_NameServer_SetupProxy_Module_startup
#define NameServer_SetupProxy_Module_startupDone ti_sdo_utils_NameServer_SetupProxy_Module_startupDone
#define NameServer_SetupProxy_Module_hasMask ti_sdo_utils_NameServer_SetupProxy_Module_hasMask
#define NameServer_SetupProxy_Module_getMask ti_sdo_utils_NameServer_SetupProxy_Module_getMask
#define NameServer_SetupProxy_Module_setMask ti_sdo_utils_NameServer_SetupProxy_Module_setMask
#define NameServer_SetupProxy_Object_heap ti_sdo_utils_NameServer_SetupProxy_Object_heap
#define NameServer_SetupProxy_Module_heap ti_sdo_utils_NameServer_SetupProxy_Module_heap
#define NameServer_SetupProxy_construct ti_sdo_utils_NameServer_SetupProxy_construct
#define NameServer_SetupProxy_create ti_sdo_utils_NameServer_SetupProxy_create
#define NameServer_SetupProxy_handle ti_sdo_utils_NameServer_SetupProxy_handle
#define NameServer_SetupProxy_struct ti_sdo_utils_NameServer_SetupProxy_struct
#define NameServer_SetupProxy_Handle_label ti_sdo_utils_NameServer_SetupProxy_Handle_label
#define NameServer_SetupProxy_Handle_name ti_sdo_utils_NameServer_SetupProxy_Handle_name
#define NameServer_SetupProxy_Instance_init ti_sdo_utils_NameServer_SetupProxy_Instance_init
#define NameServer_SetupProxy_Object_count ti_sdo_utils_NameServer_SetupProxy_Object_count
#define NameServer_SetupProxy_Object_get ti_sdo_utils_NameServer_SetupProxy_Object_get
#define NameServer_SetupProxy_Object_first ti_sdo_utils_NameServer_SetupProxy_Object_first
#define NameServer_SetupProxy_Object_next ti_sdo_utils_NameServer_SetupProxy_Object_next
#define NameServer_SetupProxy_Object_sizeof ti_sdo_utils_NameServer_SetupProxy_Object_sizeof
#define NameServer_SetupProxy_Params_copy ti_sdo_utils_NameServer_SetupProxy_Params_copy
#define NameServer_SetupProxy_Params_init ti_sdo_utils_NameServer_SetupProxy_Params_init
#define NameServer_SetupProxy_Instance_State ti_sdo_utils_NameServer_SetupProxy_Instance_State
#define NameServer_SetupProxy_Proxy_abstract ti_sdo_utils_NameServer_SetupProxy_Proxy_abstract
#define NameServer_SetupProxy_Proxy_delegate ti_sdo_utils_NameServer_SetupProxy_Proxy_delegate
#define NameServer_SetupProxy_delete ti_sdo_utils_NameServer_SetupProxy_delete
#define NameServer_SetupProxy_destruct ti_sdo_utils_NameServer_SetupProxy_destruct
#define NameServer_SetupProxy_Module_upCast ti_sdo_utils_NameServer_SetupProxy_Module_upCast
#define NameServer_SetupProxy_Module_to_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServer_SetupProxy_Module_to_ti_sdo_utils_INameServerRemote
#define NameServer_SetupProxy_Handle_upCast ti_sdo_utils_NameServer_SetupProxy_Handle_upCast
#define NameServer_SetupProxy_Handle_to_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServer_SetupProxy_Handle_to_ti_sdo_utils_INameServerRemote
#define NameServer_SetupProxy_Handle_downCast ti_sdo_utils_NameServer_SetupProxy_Handle_downCast
#define NameServer_SetupProxy_Handle_from_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServer_SetupProxy_Handle_from_ti_sdo_utils_INameServerRemote

#endif /* ti_sdo_utils_NameServer_SetupProxy__localnames__done */
#endif
