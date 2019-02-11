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

#ifndef ti_sdo_utils_NameServerRemoteNull__include
#define ti_sdo_utils_NameServerRemoteNull__include

#ifndef __nested__
#define __nested__
#define ti_sdo_utils_NameServerRemoteNull__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_utils_NameServerRemoteNull___VERS 160


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
typedef ti_sdo_utils_INameServerRemote_Status ti_sdo_utils_NameServerRemoteNull_Status;

/* S_SUCCESS */
#define ti_sdo_utils_NameServerRemoteNull_S_SUCCESS ti_sdo_utils_INameServerRemote_S_SUCCESS

/* E_FAIL */
#define ti_sdo_utils_NameServerRemoteNull_E_FAIL ti_sdo_utils_INameServerRemote_E_FAIL

/* E_ERROR */
#define ti_sdo_utils_NameServerRemoteNull_E_ERROR ti_sdo_utils_INameServerRemote_E_ERROR


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_utils_NameServerRemoteNull_Args__create {
    xdc_UInt16 procId;
} ti_sdo_utils_NameServerRemoteNull_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_utils_NameServerRemoteNull_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__diagsEnabled ti_sdo_utils_NameServerRemoteNull_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_utils_NameServerRemoteNull_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__diagsIncluded ti_sdo_utils_NameServerRemoteNull_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_utils_NameServerRemoteNull_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__diagsMask ti_sdo_utils_NameServerRemoteNull_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_utils_NameServerRemoteNull_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__gateObj ti_sdo_utils_NameServerRemoteNull_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_utils_NameServerRemoteNull_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__gatePrms ti_sdo_utils_NameServerRemoteNull_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_utils_NameServerRemoteNull_Module__id;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__id ti_sdo_utils_NameServerRemoteNull_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerDefined ti_sdo_utils_NameServerRemoteNull_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerObj ti_sdo_utils_NameServerRemoteNull_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn0 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn1 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn2 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn4 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn8 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_utils_NameServerRemoteNull_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__startupDoneFxn ti_sdo_utils_NameServerRemoteNull_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_utils_NameServerRemoteNull_Object__count;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Object__count ti_sdo_utils_NameServerRemoteNull_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_utils_NameServerRemoteNull_Object__heap;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Object__heap ti_sdo_utils_NameServerRemoteNull_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_utils_NameServerRemoteNull_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Object__sizeof ti_sdo_utils_NameServerRemoteNull_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_utils_NameServerRemoteNull_Object__table;
__extern __FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Object__table ti_sdo_utils_NameServerRemoteNull_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_utils_NameServerRemoteNull_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_utils_NameServerRemoteNull_Struct {
    const ti_sdo_utils_NameServerRemoteNull_Fxns__ *__fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_utils_NameServerRemoteNull_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*attach)(xdc_UInt16, xdc_Ptr);
    xdc_Int (*detach)(xdc_UInt16);
    xdc_SizeT (*sharedMemReq)(xdc_Ptr);
    xdc_Int (*get)(ti_sdo_utils_NameServerRemoteNull_Handle, xdc_String, xdc_String, xdc_Ptr, xdc_UInt32*, xdc_runtime_knl_ISync_Handle, xdc_runtime_Error_Block*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_utils_NameServerRemoteNull_Fxns__ ti_sdo_utils_NameServerRemoteNull_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_utils_NameServerRemoteNull_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_Instance_init__E, "ti_sdo_utils_NameServerRemoteNull_Instance_init")
__extern xdc_Void ti_sdo_utils_NameServerRemoteNull_Instance_init__E(ti_sdo_utils_NameServerRemoteNull_Object *, xdc_UInt16 procId, const ti_sdo_utils_NameServerRemoteNull_Params *);

/* Handle__label__S */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_Handle__label__S, "ti_sdo_utils_NameServerRemoteNull_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_utils_NameServerRemoteNull_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_Module__startupDone__S, "ti_sdo_utils_NameServerRemoteNull_Module__startupDone__S")
__extern xdc_Bool ti_sdo_utils_NameServerRemoteNull_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_Object__create__S, "ti_sdo_utils_NameServerRemoteNull_Object__create__S")
__extern xdc_Ptr ti_sdo_utils_NameServerRemoteNull_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_create, "ti_sdo_utils_NameServerRemoteNull_create")
__extern ti_sdo_utils_NameServerRemoteNull_Handle ti_sdo_utils_NameServerRemoteNull_create( xdc_UInt16 procId, const ti_sdo_utils_NameServerRemoteNull_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_construct, "ti_sdo_utils_NameServerRemoteNull_construct")
__extern void ti_sdo_utils_NameServerRemoteNull_construct( ti_sdo_utils_NameServerRemoteNull_Struct *__obj, xdc_UInt16 procId, const ti_sdo_utils_NameServerRemoteNull_Params *__prms );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_Object__delete__S, "ti_sdo_utils_NameServerRemoteNull_Object__delete__S")
__extern xdc_Void ti_sdo_utils_NameServerRemoteNull_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_delete, "ti_sdo_utils_NameServerRemoteNull_delete")
__extern void ti_sdo_utils_NameServerRemoteNull_delete(ti_sdo_utils_NameServerRemoteNull_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_Object__destruct__S, "ti_sdo_utils_NameServerRemoteNull_Object__destruct__S")
__extern xdc_Void ti_sdo_utils_NameServerRemoteNull_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_destruct, "ti_sdo_utils_NameServerRemoteNull_destruct")
__extern void ti_sdo_utils_NameServerRemoteNull_destruct(ti_sdo_utils_NameServerRemoteNull_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_Object__get__S, "ti_sdo_utils_NameServerRemoteNull_Object__get__S")
__extern xdc_Ptr ti_sdo_utils_NameServerRemoteNull_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_Object__first__S, "ti_sdo_utils_NameServerRemoteNull_Object__first__S")
__extern xdc_Ptr ti_sdo_utils_NameServerRemoteNull_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_Object__next__S, "ti_sdo_utils_NameServerRemoteNull_Object__next__S")
__extern xdc_Ptr ti_sdo_utils_NameServerRemoteNull_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_Params__init__S, "ti_sdo_utils_NameServerRemoteNull_Params__init__S")
__extern xdc_Void ti_sdo_utils_NameServerRemoteNull_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* attach__E */
#define ti_sdo_utils_NameServerRemoteNull_attach ti_sdo_utils_NameServerRemoteNull_attach__E
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_attach__E, "ti_sdo_utils_NameServerRemoteNull_attach")
__extern xdc_Int ti_sdo_utils_NameServerRemoteNull_attach__E( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* detach__E */
#define ti_sdo_utils_NameServerRemoteNull_detach ti_sdo_utils_NameServerRemoteNull_detach__E
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_detach__E, "ti_sdo_utils_NameServerRemoteNull_detach")
__extern xdc_Int ti_sdo_utils_NameServerRemoteNull_detach__E( xdc_UInt16 remoteProcId );

/* sharedMemReq__E */
#define ti_sdo_utils_NameServerRemoteNull_sharedMemReq ti_sdo_utils_NameServerRemoteNull_sharedMemReq__E
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_sharedMemReq__E, "ti_sdo_utils_NameServerRemoteNull_sharedMemReq")
__extern xdc_SizeT ti_sdo_utils_NameServerRemoteNull_sharedMemReq__E( xdc_Ptr sharedAddr );

/* get__E */
#define ti_sdo_utils_NameServerRemoteNull_get ti_sdo_utils_NameServerRemoteNull_get__E
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_get__E, "ti_sdo_utils_NameServerRemoteNull_get")
__extern xdc_Int ti_sdo_utils_NameServerRemoteNull_get__E( ti_sdo_utils_NameServerRemoteNull_Handle __inst, xdc_String instanceName, xdc_String name, xdc_Ptr value, xdc_UInt32 *valueLen, xdc_runtime_knl_ISync_Handle syncHandle, xdc_runtime_Error_Block *eb );
xdc__CODESECT(ti_sdo_utils_NameServerRemoteNull_get__F, "ti_sdo_utils_NameServerRemoteNull_get")
__extern xdc_Int ti_sdo_utils_NameServerRemoteNull_get__F( ti_sdo_utils_NameServerRemoteNull_Object *__inst, xdc_String instanceName, xdc_String name, xdc_Ptr value, xdc_UInt32 *valueLen, xdc_runtime_knl_ISync_Handle syncHandle, xdc_runtime_Error_Block *eb );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_utils_INameServerRemote_Module ti_sdo_utils_NameServerRemoteNull_Module_upCast( void )
{
    return (ti_sdo_utils_INameServerRemote_Module)&ti_sdo_utils_NameServerRemoteNull_Module__FXNS__C;
}

/* Module_to_ti_sdo_utils_INameServerRemote */
#define ti_sdo_utils_NameServerRemoteNull_Module_to_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServerRemoteNull_Module_upCast

/* Handle_upCast */
static inline ti_sdo_utils_INameServerRemote_Handle ti_sdo_utils_NameServerRemoteNull_Handle_upCast( ti_sdo_utils_NameServerRemoteNull_Handle i )
{
    return (ti_sdo_utils_INameServerRemote_Handle)i;
}

/* Handle_to_ti_sdo_utils_INameServerRemote */
#define ti_sdo_utils_NameServerRemoteNull_Handle_to_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServerRemoteNull_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_utils_NameServerRemoteNull_Handle ti_sdo_utils_NameServerRemoteNull_Handle_downCast( ti_sdo_utils_INameServerRemote_Handle i )
{
    ti_sdo_utils_INameServerRemote_Handle i2 = (ti_sdo_utils_INameServerRemote_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_utils_NameServerRemoteNull_Module__FXNS__C ? (ti_sdo_utils_NameServerRemoteNull_Handle)i : (ti_sdo_utils_NameServerRemoteNull_Handle)0;
}

/* Handle_from_ti_sdo_utils_INameServerRemote */
#define ti_sdo_utils_NameServerRemoteNull_Handle_from_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServerRemoteNull_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_utils_NameServerRemoteNull_Module_startupDone() ti_sdo_utils_NameServerRemoteNull_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_utils_NameServerRemoteNull_Object_heap() ti_sdo_utils_NameServerRemoteNull_Object__heap__C

/* Module_heap */
#define ti_sdo_utils_NameServerRemoteNull_Module_heap() ti_sdo_utils_NameServerRemoteNull_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_utils_NameServerRemoteNull_Module__id ti_sdo_utils_NameServerRemoteNull_Module_id( void ) 
{
    return ti_sdo_utils_NameServerRemoteNull_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_utils_NameServerRemoteNull_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_utils_NameServerRemoteNull_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_utils_NameServerRemoteNull_Module_getMask( void ) 
{
    return ti_sdo_utils_NameServerRemoteNull_Module__diagsMask__C != NULL ? *ti_sdo_utils_NameServerRemoteNull_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_utils_NameServerRemoteNull_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_utils_NameServerRemoteNull_Module__diagsMask__C != NULL) {
        *ti_sdo_utils_NameServerRemoteNull_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_utils_NameServerRemoteNull_Params_init( ti_sdo_utils_NameServerRemoteNull_Params *prms ) 
{
    if (prms) {
        ti_sdo_utils_NameServerRemoteNull_Params__init__S(prms, 0, sizeof(ti_sdo_utils_NameServerRemoteNull_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_utils_NameServerRemoteNull_Params_copy(ti_sdo_utils_NameServerRemoteNull_Params *dst, const ti_sdo_utils_NameServerRemoteNull_Params *src) 
{
    if (dst) {
        ti_sdo_utils_NameServerRemoteNull_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_utils_NameServerRemoteNull_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_utils_NameServerRemoteNull_Object_count() ti_sdo_utils_NameServerRemoteNull_Object__count__C

/* Object_sizeof */
#define ti_sdo_utils_NameServerRemoteNull_Object_sizeof() ti_sdo_utils_NameServerRemoteNull_Object__sizeof__C

/* Object_get */
static inline ti_sdo_utils_NameServerRemoteNull_Handle ti_sdo_utils_NameServerRemoteNull_Object_get(ti_sdo_utils_NameServerRemoteNull_Instance_State *oarr, int i) 
{
    return (ti_sdo_utils_NameServerRemoteNull_Handle)ti_sdo_utils_NameServerRemoteNull_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_utils_NameServerRemoteNull_Handle ti_sdo_utils_NameServerRemoteNull_Object_first( void )
{
    return (ti_sdo_utils_NameServerRemoteNull_Handle)ti_sdo_utils_NameServerRemoteNull_Object__first__S();
}

/* Object_next */
static inline ti_sdo_utils_NameServerRemoteNull_Handle ti_sdo_utils_NameServerRemoteNull_Object_next( ti_sdo_utils_NameServerRemoteNull_Object *obj )
{
    return (ti_sdo_utils_NameServerRemoteNull_Handle)ti_sdo_utils_NameServerRemoteNull_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_utils_NameServerRemoteNull_Handle_label( ti_sdo_utils_NameServerRemoteNull_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_utils_NameServerRemoteNull_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_utils_NameServerRemoteNull_Handle_name( ti_sdo_utils_NameServerRemoteNull_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_utils_NameServerRemoteNull_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_utils_NameServerRemoteNull_Handle ti_sdo_utils_NameServerRemoteNull_handle( ti_sdo_utils_NameServerRemoteNull_Struct *str )
{
    return (ti_sdo_utils_NameServerRemoteNull_Handle)str;
}

/* struct */
static inline ti_sdo_utils_NameServerRemoteNull_Struct *ti_sdo_utils_NameServerRemoteNull_struct( ti_sdo_utils_NameServerRemoteNull_Handle inst )
{
    return (ti_sdo_utils_NameServerRemoteNull_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_utils_NameServerRemoteNull__top__
#undef __nested__
#endif

#endif /* ti_sdo_utils_NameServerRemoteNull__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_utils_NameServerRemoteNull__internalaccess))

#ifndef ti_sdo_utils_NameServerRemoteNull__include_state
#define ti_sdo_utils_NameServerRemoteNull__include_state

/* Object */
struct ti_sdo_utils_NameServerRemoteNull_Object {
    const ti_sdo_utils_NameServerRemoteNull_Fxns__ *__fxns;
};

#endif /* ti_sdo_utils_NameServerRemoteNull__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_utils_NameServerRemoteNull__nolocalnames)

#ifndef ti_sdo_utils_NameServerRemoteNull__localnames__done
#define ti_sdo_utils_NameServerRemoteNull__localnames__done

/* module prefix */
#define NameServerRemoteNull_Instance ti_sdo_utils_NameServerRemoteNull_Instance
#define NameServerRemoteNull_Handle ti_sdo_utils_NameServerRemoteNull_Handle
#define NameServerRemoteNull_Module ti_sdo_utils_NameServerRemoteNull_Module
#define NameServerRemoteNull_Object ti_sdo_utils_NameServerRemoteNull_Object
#define NameServerRemoteNull_Struct ti_sdo_utils_NameServerRemoteNull_Struct
#define NameServerRemoteNull_Status ti_sdo_utils_NameServerRemoteNull_Status
#define NameServerRemoteNull_Instance_State ti_sdo_utils_NameServerRemoteNull_Instance_State
#define NameServerRemoteNull_S_SUCCESS ti_sdo_utils_NameServerRemoteNull_S_SUCCESS
#define NameServerRemoteNull_E_FAIL ti_sdo_utils_NameServerRemoteNull_E_FAIL
#define NameServerRemoteNull_E_ERROR ti_sdo_utils_NameServerRemoteNull_E_ERROR
#define NameServerRemoteNull_Params ti_sdo_utils_NameServerRemoteNull_Params
#define NameServerRemoteNull_attach ti_sdo_utils_NameServerRemoteNull_attach
#define NameServerRemoteNull_detach ti_sdo_utils_NameServerRemoteNull_detach
#define NameServerRemoteNull_sharedMemReq ti_sdo_utils_NameServerRemoteNull_sharedMemReq
#define NameServerRemoteNull_get ti_sdo_utils_NameServerRemoteNull_get
#define NameServerRemoteNull_Module_name ti_sdo_utils_NameServerRemoteNull_Module_name
#define NameServerRemoteNull_Module_id ti_sdo_utils_NameServerRemoteNull_Module_id
#define NameServerRemoteNull_Module_startup ti_sdo_utils_NameServerRemoteNull_Module_startup
#define NameServerRemoteNull_Module_startupDone ti_sdo_utils_NameServerRemoteNull_Module_startupDone
#define NameServerRemoteNull_Module_hasMask ti_sdo_utils_NameServerRemoteNull_Module_hasMask
#define NameServerRemoteNull_Module_getMask ti_sdo_utils_NameServerRemoteNull_Module_getMask
#define NameServerRemoteNull_Module_setMask ti_sdo_utils_NameServerRemoteNull_Module_setMask
#define NameServerRemoteNull_Object_heap ti_sdo_utils_NameServerRemoteNull_Object_heap
#define NameServerRemoteNull_Module_heap ti_sdo_utils_NameServerRemoteNull_Module_heap
#define NameServerRemoteNull_construct ti_sdo_utils_NameServerRemoteNull_construct
#define NameServerRemoteNull_create ti_sdo_utils_NameServerRemoteNull_create
#define NameServerRemoteNull_handle ti_sdo_utils_NameServerRemoteNull_handle
#define NameServerRemoteNull_struct ti_sdo_utils_NameServerRemoteNull_struct
#define NameServerRemoteNull_Handle_label ti_sdo_utils_NameServerRemoteNull_Handle_label
#define NameServerRemoteNull_Handle_name ti_sdo_utils_NameServerRemoteNull_Handle_name
#define NameServerRemoteNull_Instance_init ti_sdo_utils_NameServerRemoteNull_Instance_init
#define NameServerRemoteNull_Object_count ti_sdo_utils_NameServerRemoteNull_Object_count
#define NameServerRemoteNull_Object_get ti_sdo_utils_NameServerRemoteNull_Object_get
#define NameServerRemoteNull_Object_first ti_sdo_utils_NameServerRemoteNull_Object_first
#define NameServerRemoteNull_Object_next ti_sdo_utils_NameServerRemoteNull_Object_next
#define NameServerRemoteNull_Object_sizeof ti_sdo_utils_NameServerRemoteNull_Object_sizeof
#define NameServerRemoteNull_Params_copy ti_sdo_utils_NameServerRemoteNull_Params_copy
#define NameServerRemoteNull_Params_init ti_sdo_utils_NameServerRemoteNull_Params_init
#define NameServerRemoteNull_delete ti_sdo_utils_NameServerRemoteNull_delete
#define NameServerRemoteNull_destruct ti_sdo_utils_NameServerRemoteNull_destruct
#define NameServerRemoteNull_Module_upCast ti_sdo_utils_NameServerRemoteNull_Module_upCast
#define NameServerRemoteNull_Module_to_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServerRemoteNull_Module_to_ti_sdo_utils_INameServerRemote
#define NameServerRemoteNull_Handle_upCast ti_sdo_utils_NameServerRemoteNull_Handle_upCast
#define NameServerRemoteNull_Handle_to_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServerRemoteNull_Handle_to_ti_sdo_utils_INameServerRemote
#define NameServerRemoteNull_Handle_downCast ti_sdo_utils_NameServerRemoteNull_Handle_downCast
#define NameServerRemoteNull_Handle_from_ti_sdo_utils_INameServerRemote ti_sdo_utils_NameServerRemoteNull_Handle_from_ti_sdo_utils_INameServerRemote

#endif /* ti_sdo_utils_NameServerRemoteNull__localnames__done */
#endif
