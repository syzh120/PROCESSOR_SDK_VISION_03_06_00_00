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

#ifndef ti_sdo_utils_NameServer__include
#define ti_sdo_utils_NameServer__include

#ifndef __nested__
#define __nested__
#define ti_sdo_utils_NameServer__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_utils_NameServer___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/utils/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IHeap.h>
#include <ti/sysbios/gates/GateSwi.h>
#include <xdc/runtime/IModule.h>
#include <ti/sdo/utils/INameServerRemote.h>
#include <ti/sdo/utils/List.h>
#include <ti/sdo/utils/package/NameServer_SetupProxy.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* ALLOWGROWTH */
#define ti_sdo_utils_NameServer_ALLOWGROWTH ((~0))


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_utils_NameServer_Args__create {
    xdc_String name;
} ti_sdo_utils_NameServer_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* TableEntry */
struct ti_sdo_utils_NameServer_TableEntry {
    ti_sdo_utils_List_Elem elem;
    xdc_String name;
    xdc_UInt len;
    xdc_UArg value;
};

/* Instance_State */
typedef ti_sdo_utils_NameServer_TableEntry __T1_ti_sdo_utils_NameServer_Instance_State__table;
typedef ti_sdo_utils_NameServer_TableEntry *__ARRAY1_ti_sdo_utils_NameServer_Instance_State__table;
typedef __ARRAY1_ti_sdo_utils_NameServer_Instance_State__table __TA_ti_sdo_utils_NameServer_Instance_State__table;
typedef xdc_Char __T1_ti_sdo_utils_NameServer_Instance_State__names;
typedef xdc_Char *__ARRAY1_ti_sdo_utils_NameServer_Instance_State__names;
typedef __ARRAY1_ti_sdo_utils_NameServer_Instance_State__names __TA_ti_sdo_utils_NameServer_Instance_State__names;
typedef xdc_UInt8 __T1_ti_sdo_utils_NameServer_Instance_State__values;
typedef xdc_UInt8 *__ARRAY1_ti_sdo_utils_NameServer_Instance_State__values;
typedef __ARRAY1_ti_sdo_utils_NameServer_Instance_State__values __TA_ti_sdo_utils_NameServer_Instance_State__values;

/* Module_State */
typedef ti_sdo_utils_INameServerRemote_Handle __T1_ti_sdo_utils_NameServer_Module_State__nsRemoteHandle;
typedef struct { int length; ti_sdo_utils_INameServerRemote_Handle *elem; } __ARRAY1_ti_sdo_utils_NameServer_Module_State__nsRemoteHandle;
typedef __ARRAY1_ti_sdo_utils_NameServer_Module_State__nsRemoteHandle __TA_ti_sdo_utils_NameServer_Module_State__nsRemoteHandle;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_utils_NameServer_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__diagsEnabled ti_sdo_utils_NameServer_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_utils_NameServer_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__diagsIncluded ti_sdo_utils_NameServer_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_utils_NameServer_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__diagsMask ti_sdo_utils_NameServer_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_utils_NameServer_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__gateObj ti_sdo_utils_NameServer_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_utils_NameServer_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__gatePrms ti_sdo_utils_NameServer_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_utils_NameServer_Module__id;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__id ti_sdo_utils_NameServer_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_utils_NameServer_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__loggerDefined ti_sdo_utils_NameServer_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_utils_NameServer_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__loggerObj ti_sdo_utils_NameServer_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_utils_NameServer_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__loggerFxn0 ti_sdo_utils_NameServer_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_utils_NameServer_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__loggerFxn1 ti_sdo_utils_NameServer_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_utils_NameServer_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__loggerFxn2 ti_sdo_utils_NameServer_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_utils_NameServer_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__loggerFxn4 ti_sdo_utils_NameServer_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_utils_NameServer_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__loggerFxn8 ti_sdo_utils_NameServer_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_utils_NameServer_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Module__startupDoneFxn ti_sdo_utils_NameServer_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_utils_NameServer_Object__count;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Object__count ti_sdo_utils_NameServer_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_utils_NameServer_Object__heap;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Object__heap ti_sdo_utils_NameServer_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_utils_NameServer_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Object__sizeof ti_sdo_utils_NameServer_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_utils_NameServer_Object__table;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_Object__table ti_sdo_utils_NameServer_Object__table__C;

/* A_invalidLen */
#define ti_sdo_utils_NameServer_A_invalidLen (ti_sdo_utils_NameServer_A_invalidLen__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_utils_NameServer_A_invalidLen;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_A_invalidLen ti_sdo_utils_NameServer_A_invalidLen__C;

/* A_invArgument */
#define ti_sdo_utils_NameServer_A_invArgument (ti_sdo_utils_NameServer_A_invArgument__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_utils_NameServer_A_invArgument;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_A_invArgument ti_sdo_utils_NameServer_A_invArgument__C;

/* E_maxReached */
#define ti_sdo_utils_NameServer_E_maxReached (ti_sdo_utils_NameServer_E_maxReached__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_utils_NameServer_E_maxReached;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_E_maxReached ti_sdo_utils_NameServer_E_maxReached__C;

/* E_entryExists */
#define ti_sdo_utils_NameServer_E_entryExists (ti_sdo_utils_NameServer_E_entryExists__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_utils_NameServer_E_entryExists;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_E_entryExists ti_sdo_utils_NameServer_E_entryExists__C;

/* E_paramMismatch */
#define ti_sdo_utils_NameServer_E_paramMismatch (ti_sdo_utils_NameServer_E_paramMismatch__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_utils_NameServer_E_paramMismatch;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_E_paramMismatch ti_sdo_utils_NameServer_E_paramMismatch__C;

/* singleProcessor */
#ifdef ti_sdo_utils_NameServer_singleProcessor__D
#define ti_sdo_utils_NameServer_singleProcessor (ti_sdo_utils_NameServer_singleProcessor__D)
#else
#define ti_sdo_utils_NameServer_singleProcessor (ti_sdo_utils_NameServer_singleProcessor__C)
typedef xdc_Bool CT__ti_sdo_utils_NameServer_singleProcessor;
__extern __FAR__ const CT__ti_sdo_utils_NameServer_singleProcessor ti_sdo_utils_NameServer_singleProcessor__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_utils_NameServer_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_UInt maxRuntimeEntries;
    xdc_runtime_IHeap_Handle tableHeap;
    xdc_Bool checkExisting;
    xdc_UInt maxValueLen;
    xdc_UInt maxNameLen;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_utils_NameServer_Struct {
    xdc_String __f0;
    xdc_UInt __f1;
    xdc_UInt __f2;
    xdc_UInt __f3;
    xdc_UInt __f4;
    __TA_ti_sdo_utils_NameServer_Instance_State__table __f5;
    __TA_ti_sdo_utils_NameServer_Instance_State__names __f6;
    __TA_ti_sdo_utils_NameServer_Instance_State__values __f7;
    xdc_runtime_IHeap_Handle __f8;
    xdc_Bool __f9;
    xdc_UInt32 __f10;
    ti_sdo_utils_List_Struct __f11;
    ti_sdo_utils_List_Struct __f12;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_utils_NameServer_Module_startup ti_sdo_utils_NameServer_Module_startup__E
xdc__CODESECT(ti_sdo_utils_NameServer_Module_startup__E, "ti_sdo_utils_NameServer_Module_startup")
__extern xdc_Int ti_sdo_utils_NameServer_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_sdo_utils_NameServer_Module_startup__F, "ti_sdo_utils_NameServer_Module_startup")
__extern xdc_Int ti_sdo_utils_NameServer_Module_startup__F( xdc_Int state );

/* Instance_init__E */
xdc__CODESECT(ti_sdo_utils_NameServer_Instance_init__E, "ti_sdo_utils_NameServer_Instance_init")
__extern xdc_Int ti_sdo_utils_NameServer_Instance_init__E(ti_sdo_utils_NameServer_Object *, xdc_String name, const ti_sdo_utils_NameServer_Params *, xdc_runtime_Error_Block *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_utils_NameServer_Instance_finalize__E, "ti_sdo_utils_NameServer_Instance_finalize")
__extern void ti_sdo_utils_NameServer_Instance_finalize__E( ti_sdo_utils_NameServer_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_utils_NameServer_Handle__label__S, "ti_sdo_utils_NameServer_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_utils_NameServer_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_utils_NameServer_Module__startupDone__S, "ti_sdo_utils_NameServer_Module__startupDone__S")
__extern xdc_Bool ti_sdo_utils_NameServer_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_utils_NameServer_Object__create__S, "ti_sdo_utils_NameServer_Object__create__S")
__extern xdc_Ptr ti_sdo_utils_NameServer_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_utils_NameServer_create, "ti_sdo_utils_NameServer_create")
__extern ti_sdo_utils_NameServer_Handle ti_sdo_utils_NameServer_create( xdc_String name, const ti_sdo_utils_NameServer_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_utils_NameServer_construct, "ti_sdo_utils_NameServer_construct")
__extern void ti_sdo_utils_NameServer_construct( ti_sdo_utils_NameServer_Struct *__obj, xdc_String name, const ti_sdo_utils_NameServer_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_utils_NameServer_Object__delete__S, "ti_sdo_utils_NameServer_Object__delete__S")
__extern xdc_Void ti_sdo_utils_NameServer_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_utils_NameServer_delete, "ti_sdo_utils_NameServer_delete")
__extern void ti_sdo_utils_NameServer_delete(ti_sdo_utils_NameServer_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_utils_NameServer_Object__destruct__S, "ti_sdo_utils_NameServer_Object__destruct__S")
__extern xdc_Void ti_sdo_utils_NameServer_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_utils_NameServer_destruct, "ti_sdo_utils_NameServer_destruct")
__extern void ti_sdo_utils_NameServer_destruct(ti_sdo_utils_NameServer_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_utils_NameServer_Object__get__S, "ti_sdo_utils_NameServer_Object__get__S")
__extern xdc_Ptr ti_sdo_utils_NameServer_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_utils_NameServer_Object__first__S, "ti_sdo_utils_NameServer_Object__first__S")
__extern xdc_Ptr ti_sdo_utils_NameServer_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_utils_NameServer_Object__next__S, "ti_sdo_utils_NameServer_Object__next__S")
__extern xdc_Ptr ti_sdo_utils_NameServer_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_utils_NameServer_Params__init__S, "ti_sdo_utils_NameServer_Params__init__S")
__extern xdc_Void ti_sdo_utils_NameServer_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* isRegistered__E */
#define ti_sdo_utils_NameServer_isRegistered ti_sdo_utils_NameServer_isRegistered__E
xdc__CODESECT(ti_sdo_utils_NameServer_isRegistered__E, "ti_sdo_utils_NameServer_isRegistered")
__extern xdc_Bool ti_sdo_utils_NameServer_isRegistered__E( xdc_UInt16 procId );

/* registerRemoteDriver__E */
#define ti_sdo_utils_NameServer_registerRemoteDriver ti_sdo_utils_NameServer_registerRemoteDriver__E
xdc__CODESECT(ti_sdo_utils_NameServer_registerRemoteDriver__E, "ti_sdo_utils_NameServer_registerRemoteDriver")
__extern xdc_Int ti_sdo_utils_NameServer_registerRemoteDriver__E( ti_sdo_utils_INameServerRemote_Handle handle, xdc_UInt16 procId );

/* unregisterRemoteDriver__E */
#define ti_sdo_utils_NameServer_unregisterRemoteDriver ti_sdo_utils_NameServer_unregisterRemoteDriver__E
xdc__CODESECT(ti_sdo_utils_NameServer_unregisterRemoteDriver__E, "ti_sdo_utils_NameServer_unregisterRemoteDriver")
__extern xdc_Void ti_sdo_utils_NameServer_unregisterRemoteDriver__E( xdc_UInt16 procId );

/* getKey__E */
#define ti_sdo_utils_NameServer_getKey ti_sdo_utils_NameServer_getKey__E
xdc__CODESECT(ti_sdo_utils_NameServer_getKey__E, "ti_sdo_utils_NameServer_getKey")
__extern xdc_Ptr ti_sdo_utils_NameServer_getKey__E( ti_sdo_utils_NameServer_Handle __inst, xdc_UInt32 val );

/* postInit__I */
#define ti_sdo_utils_NameServer_postInit ti_sdo_utils_NameServer_postInit__I
xdc__CODESECT(ti_sdo_utils_NameServer_postInit__I, "ti_sdo_utils_NameServer_postInit")
__extern xdc_Int ti_sdo_utils_NameServer_postInit__I( ti_sdo_utils_NameServer_Object *obj );

/* findLocal__I */
#define ti_sdo_utils_NameServer_findLocal ti_sdo_utils_NameServer_findLocal__I
xdc__CODESECT(ti_sdo_utils_NameServer_findLocal__I, "ti_sdo_utils_NameServer_findLocal")
__extern ti_sdo_utils_NameServer_TableEntry *ti_sdo_utils_NameServer_findLocal__I( ti_sdo_utils_NameServer_Object *obj, xdc_String name );

/* removeLocal__I */
#define ti_sdo_utils_NameServer_removeLocal ti_sdo_utils_NameServer_removeLocal__I
xdc__CODESECT(ti_sdo_utils_NameServer_removeLocal__I, "ti_sdo_utils_NameServer_removeLocal")
__extern xdc_Void ti_sdo_utils_NameServer_removeLocal__I( ti_sdo_utils_NameServer_Object *obj, ti_sdo_utils_NameServer_TableEntry *entry );

/* editLocal__I */
#define ti_sdo_utils_NameServer_editLocal ti_sdo_utils_NameServer_editLocal__I
xdc__CODESECT(ti_sdo_utils_NameServer_editLocal__I, "ti_sdo_utils_NameServer_editLocal")
__extern xdc_Void ti_sdo_utils_NameServer_editLocal__I( ti_sdo_utils_NameServer_Object *obj, ti_sdo_utils_NameServer_TableEntry *entry, xdc_Ptr newValue );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_utils_NameServer_Module_startupDone() ti_sdo_utils_NameServer_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_utils_NameServer_Object_heap() ti_sdo_utils_NameServer_Object__heap__C

/* Module_heap */
#define ti_sdo_utils_NameServer_Module_heap() ti_sdo_utils_NameServer_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_utils_NameServer_Module__id ti_sdo_utils_NameServer_Module_id( void ) 
{
    return ti_sdo_utils_NameServer_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_utils_NameServer_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_utils_NameServer_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_utils_NameServer_Module_getMask( void ) 
{
    return ti_sdo_utils_NameServer_Module__diagsMask__C != NULL ? *ti_sdo_utils_NameServer_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_utils_NameServer_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_utils_NameServer_Module__diagsMask__C != NULL) {
        *ti_sdo_utils_NameServer_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_utils_NameServer_Params_init( ti_sdo_utils_NameServer_Params *prms ) 
{
    if (prms) {
        ti_sdo_utils_NameServer_Params__init__S(prms, 0, sizeof(ti_sdo_utils_NameServer_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_utils_NameServer_Params_copy(ti_sdo_utils_NameServer_Params *dst, const ti_sdo_utils_NameServer_Params *src) 
{
    if (dst) {
        ti_sdo_utils_NameServer_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_utils_NameServer_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_utils_NameServer_Object_count() ti_sdo_utils_NameServer_Object__count__C

/* Object_sizeof */
#define ti_sdo_utils_NameServer_Object_sizeof() ti_sdo_utils_NameServer_Object__sizeof__C

/* Object_get */
static inline ti_sdo_utils_NameServer_Handle ti_sdo_utils_NameServer_Object_get(ti_sdo_utils_NameServer_Instance_State *oarr, int i) 
{
    return (ti_sdo_utils_NameServer_Handle)ti_sdo_utils_NameServer_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_utils_NameServer_Handle ti_sdo_utils_NameServer_Object_first( void )
{
    return (ti_sdo_utils_NameServer_Handle)ti_sdo_utils_NameServer_Object__first__S();
}

/* Object_next */
static inline ti_sdo_utils_NameServer_Handle ti_sdo_utils_NameServer_Object_next( ti_sdo_utils_NameServer_Object *obj )
{
    return (ti_sdo_utils_NameServer_Handle)ti_sdo_utils_NameServer_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_utils_NameServer_Handle_label( ti_sdo_utils_NameServer_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_utils_NameServer_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_utils_NameServer_Handle_name( ti_sdo_utils_NameServer_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_utils_NameServer_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_utils_NameServer_Handle ti_sdo_utils_NameServer_handle( ti_sdo_utils_NameServer_Struct *str )
{
    return (ti_sdo_utils_NameServer_Handle)str;
}

/* struct */
static inline ti_sdo_utils_NameServer_Struct *ti_sdo_utils_NameServer_struct( ti_sdo_utils_NameServer_Handle inst )
{
    return (ti_sdo_utils_NameServer_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_utils_NameServer__top__
#undef __nested__
#endif

#endif /* ti_sdo_utils_NameServer__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_utils_NameServer__internalaccess))

#ifndef ti_sdo_utils_NameServer__include_state
#define ti_sdo_utils_NameServer__include_state

/* Module_State */
struct ti_sdo_utils_NameServer_Module_State {
    __TA_ti_sdo_utils_NameServer_Module_State__nsRemoteHandle nsRemoteHandle;
    ti_sysbios_gates_GateSwi_Handle gate;
};

/* Module__state__V */
extern struct ti_sdo_utils_NameServer_Module_State__ ti_sdo_utils_NameServer_Module__state__V;

/* Object */
struct ti_sdo_utils_NameServer_Object {
    xdc_String name;
    xdc_UInt maxNameLen;
    xdc_UInt maxValueLen;
    xdc_UInt numStatic;
    xdc_UInt numDynamic;
    __TA_ti_sdo_utils_NameServer_Instance_State__table table;
    __TA_ti_sdo_utils_NameServer_Instance_State__names names;
    __TA_ti_sdo_utils_NameServer_Instance_State__values values;
    xdc_runtime_IHeap_Handle tableHeap;
    xdc_Bool checkExisting;
    xdc_UInt32 refCount;
    char __dummy;
};

/* Instance_State_freeList */
__extern __FAR__ const xdc_SizeT ti_sdo_utils_NameServer_Instance_State_freeList__O;
static inline ti_sdo_utils_List_Handle ti_sdo_utils_NameServer_Instance_State_freeList(ti_sdo_utils_NameServer_Object *obj)
{
    return (ti_sdo_utils_List_Handle)(((char*)obj) + ti_sdo_utils_NameServer_Instance_State_freeList__O);
}

/* Instance_State_nameList */
__extern __FAR__ const xdc_SizeT ti_sdo_utils_NameServer_Instance_State_nameList__O;
static inline ti_sdo_utils_List_Handle ti_sdo_utils_NameServer_Instance_State_nameList(ti_sdo_utils_NameServer_Object *obj)
{
    return (ti_sdo_utils_List_Handle)(((char*)obj) + ti_sdo_utils_NameServer_Instance_State_nameList__O);
}

#endif /* ti_sdo_utils_NameServer__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_utils_NameServer__nolocalnames)

#ifndef ti_sdo_utils_NameServer__localnames__done
#define ti_sdo_utils_NameServer__localnames__done

/* module prefix */
#define NameServer_Instance ti_sdo_utils_NameServer_Instance
#define NameServer_Handle ti_sdo_utils_NameServer_Handle
#define NameServer_Module ti_sdo_utils_NameServer_Module
#define NameServer_Object ti_sdo_utils_NameServer_Object
#define NameServer_Struct ti_sdo_utils_NameServer_Struct
#define NameServer_ALLOWGROWTH ti_sdo_utils_NameServer_ALLOWGROWTH
#define NameServer_TableEntry ti_sdo_utils_NameServer_TableEntry
#define NameServer_Instance_State ti_sdo_utils_NameServer_Instance_State
#define NameServer_Module_State ti_sdo_utils_NameServer_Module_State
#define NameServer_A_invalidLen ti_sdo_utils_NameServer_A_invalidLen
#define NameServer_A_invArgument ti_sdo_utils_NameServer_A_invArgument
#define NameServer_E_maxReached ti_sdo_utils_NameServer_E_maxReached
#define NameServer_E_entryExists ti_sdo_utils_NameServer_E_entryExists
#define NameServer_E_paramMismatch ti_sdo_utils_NameServer_E_paramMismatch
#define NameServer_singleProcessor ti_sdo_utils_NameServer_singleProcessor
#define NameServer_Instance_State_freeList ti_sdo_utils_NameServer_Instance_State_freeList
#define NameServer_Instance_State_nameList ti_sdo_utils_NameServer_Instance_State_nameList
#define NameServer_Params ti_sdo_utils_NameServer_Params
#define NameServer_isRegistered ti_sdo_utils_NameServer_isRegistered
#define NameServer_registerRemoteDriver ti_sdo_utils_NameServer_registerRemoteDriver
#define NameServer_unregisterRemoteDriver ti_sdo_utils_NameServer_unregisterRemoteDriver
#define NameServer_getKey ti_sdo_utils_NameServer_getKey
#define NameServer_Module_name ti_sdo_utils_NameServer_Module_name
#define NameServer_Module_id ti_sdo_utils_NameServer_Module_id
#define NameServer_Module_startup ti_sdo_utils_NameServer_Module_startup
#define NameServer_Module_startupDone ti_sdo_utils_NameServer_Module_startupDone
#define NameServer_Module_hasMask ti_sdo_utils_NameServer_Module_hasMask
#define NameServer_Module_getMask ti_sdo_utils_NameServer_Module_getMask
#define NameServer_Module_setMask ti_sdo_utils_NameServer_Module_setMask
#define NameServer_Object_heap ti_sdo_utils_NameServer_Object_heap
#define NameServer_Module_heap ti_sdo_utils_NameServer_Module_heap
#define NameServer_construct ti_sdo_utils_NameServer_construct
#define NameServer_create ti_sdo_utils_NameServer_create
#define NameServer_handle ti_sdo_utils_NameServer_handle
#define NameServer_struct ti_sdo_utils_NameServer_struct
#define NameServer_Handle_label ti_sdo_utils_NameServer_Handle_label
#define NameServer_Handle_name ti_sdo_utils_NameServer_Handle_name
#define NameServer_Instance_init ti_sdo_utils_NameServer_Instance_init
#define NameServer_Object_count ti_sdo_utils_NameServer_Object_count
#define NameServer_Object_get ti_sdo_utils_NameServer_Object_get
#define NameServer_Object_first ti_sdo_utils_NameServer_Object_first
#define NameServer_Object_next ti_sdo_utils_NameServer_Object_next
#define NameServer_Object_sizeof ti_sdo_utils_NameServer_Object_sizeof
#define NameServer_Params_copy ti_sdo_utils_NameServer_Params_copy
#define NameServer_Params_init ti_sdo_utils_NameServer_Params_init
#define NameServer_Instance_finalize ti_sdo_utils_NameServer_Instance_finalize
#define NameServer_delete ti_sdo_utils_NameServer_delete
#define NameServer_destruct ti_sdo_utils_NameServer_destruct

/* proxies */
#include <ti/sdo/utils/package/NameServer_SetupProxy.h>

#endif /* ti_sdo_utils_NameServer__localnames__done */
#endif
