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

#ifndef ti_sdo_ipc_ListMP__include
#define ti_sdo_ipc_ListMP__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_ListMP__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_ListMP___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <ti/sdo/utils/NameServer.h>
#include <xdc/runtime/IModule.h>
#include <ti/sdo/ipc/GateMP.h>
#include <ti/sdo/ipc/SharedRegion.h>
#include <ti/sdo/ipc/Ipc.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* CREATED */
#define ti_sdo_ipc_ListMP_CREATED (0x12181964)

/* Elem */
struct ti_sdo_ipc_ListMP_Elem {
    volatile ti_sdo_ipc_SharedRegion_SRPtr next;
    volatile ti_sdo_ipc_SharedRegion_SRPtr prev;
};

/* Attrs */
struct ti_sdo_ipc_ListMP_Attrs {
    xdc_Bits32 status;
    ti_sdo_ipc_SharedRegion_SRPtr gateMPAddr;
    ti_sdo_ipc_ListMP_Elem head;
};


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_ListMP_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__diagsEnabled ti_sdo_ipc_ListMP_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_ListMP_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__diagsIncluded ti_sdo_ipc_ListMP_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_ListMP_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__diagsMask ti_sdo_ipc_ListMP_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_ListMP_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__gateObj ti_sdo_ipc_ListMP_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_ListMP_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__gatePrms ti_sdo_ipc_ListMP_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_ListMP_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__id ti_sdo_ipc_ListMP_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_ListMP_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__loggerDefined ti_sdo_ipc_ListMP_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_ListMP_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__loggerObj ti_sdo_ipc_ListMP_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_ListMP_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__loggerFxn0 ti_sdo_ipc_ListMP_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_ListMP_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__loggerFxn1 ti_sdo_ipc_ListMP_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_ListMP_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__loggerFxn2 ti_sdo_ipc_ListMP_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_ListMP_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__loggerFxn4 ti_sdo_ipc_ListMP_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_ListMP_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__loggerFxn8 ti_sdo_ipc_ListMP_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_ListMP_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Module__startupDoneFxn ti_sdo_ipc_ListMP_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_ListMP_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Object__count ti_sdo_ipc_ListMP_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_ListMP_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Object__heap ti_sdo_ipc_ListMP_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_ListMP_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Object__sizeof ti_sdo_ipc_ListMP_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_ListMP_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_ListMP_Object__table ti_sdo_ipc_ListMP_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_ListMP_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    ti_sdo_ipc_GateMP_Handle gate;
    xdc_Bool openFlag;
    xdc_Ptr sharedAddr;
    xdc_String name;
    xdc_UInt16 regionId;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_ListMP_Struct {
    ti_sdo_ipc_ListMP_Attrs *__f0;
    xdc_Ptr __f1;
    ti_sdo_ipc_Ipc_ObjType __f2;
    ti_sdo_ipc_GateMP_Handle __f3;
    xdc_SizeT __f4;
    xdc_UInt16 __f5;
    xdc_Bool __f6;
    xdc_SizeT __f7;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_ListMP_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_ListMP_Instance_init__E, "ti_sdo_ipc_ListMP_Instance_init")
__extern xdc_Int ti_sdo_ipc_ListMP_Instance_init__E(ti_sdo_ipc_ListMP_Object *, const ti_sdo_ipc_ListMP_Params *, xdc_runtime_Error_Block *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_ListMP_Instance_finalize__E, "ti_sdo_ipc_ListMP_Instance_finalize")
__extern void ti_sdo_ipc_ListMP_Instance_finalize__E( ti_sdo_ipc_ListMP_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_ListMP_Handle__label__S, "ti_sdo_ipc_ListMP_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_ListMP_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_ListMP_Module__startupDone__S, "ti_sdo_ipc_ListMP_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_ListMP_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_ListMP_Object__create__S, "ti_sdo_ipc_ListMP_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_ListMP_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_ListMP_create, "ti_sdo_ipc_ListMP_create")
__extern ti_sdo_ipc_ListMP_Handle ti_sdo_ipc_ListMP_create( const ti_sdo_ipc_ListMP_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_ListMP_construct, "ti_sdo_ipc_ListMP_construct")
__extern void ti_sdo_ipc_ListMP_construct( ti_sdo_ipc_ListMP_Struct *__obj, const ti_sdo_ipc_ListMP_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_ListMP_Object__delete__S, "ti_sdo_ipc_ListMP_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_ListMP_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_ListMP_delete, "ti_sdo_ipc_ListMP_delete")
__extern void ti_sdo_ipc_ListMP_delete(ti_sdo_ipc_ListMP_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_ListMP_Object__destruct__S, "ti_sdo_ipc_ListMP_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_ListMP_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_ListMP_destruct, "ti_sdo_ipc_ListMP_destruct")
__extern void ti_sdo_ipc_ListMP_destruct(ti_sdo_ipc_ListMP_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_ListMP_Object__get__S, "ti_sdo_ipc_ListMP_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_ListMP_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_ListMP_Object__first__S, "ti_sdo_ipc_ListMP_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_ListMP_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_ListMP_Object__next__S, "ti_sdo_ipc_ListMP_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_ListMP_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_ListMP_Params__init__S, "ti_sdo_ipc_ListMP_Params__init__S")
__extern xdc_Void ti_sdo_ipc_ListMP_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* elemClear__I */
#define ti_sdo_ipc_ListMP_elemClear ti_sdo_ipc_ListMP_elemClear__I
xdc__CODESECT(ti_sdo_ipc_ListMP_elemClear__I, "ti_sdo_ipc_ListMP_elemClear")
__extern xdc_Void ti_sdo_ipc_ListMP_elemClear__I( ti_sdo_ipc_ListMP_Elem *elem );

/* postInit__I */
#define ti_sdo_ipc_ListMP_postInit ti_sdo_ipc_ListMP_postInit__I
xdc__CODESECT(ti_sdo_ipc_ListMP_postInit__I, "ti_sdo_ipc_ListMP_postInit")
__extern xdc_Void ti_sdo_ipc_ListMP_postInit__I( ti_sdo_ipc_ListMP_Object *obj, xdc_runtime_Error_Block *eb );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_ListMP_Module_startupDone() ti_sdo_ipc_ListMP_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_ListMP_Object_heap() ti_sdo_ipc_ListMP_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_ListMP_Module_heap() ti_sdo_ipc_ListMP_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_ListMP_Module__id ti_sdo_ipc_ListMP_Module_id( void ) 
{
    return ti_sdo_ipc_ListMP_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_ListMP_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_ListMP_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_ListMP_Module_getMask( void ) 
{
    return ti_sdo_ipc_ListMP_Module__diagsMask__C != NULL ? *ti_sdo_ipc_ListMP_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_ListMP_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_ListMP_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_ListMP_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_ListMP_Params_init( ti_sdo_ipc_ListMP_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_ListMP_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_ListMP_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_ListMP_Params_copy(ti_sdo_ipc_ListMP_Params *dst, const ti_sdo_ipc_ListMP_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_ListMP_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_ListMP_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_ListMP_Object_count() ti_sdo_ipc_ListMP_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_ListMP_Object_sizeof() ti_sdo_ipc_ListMP_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_ListMP_Handle ti_sdo_ipc_ListMP_Object_get(ti_sdo_ipc_ListMP_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_ListMP_Handle)ti_sdo_ipc_ListMP_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_ListMP_Handle ti_sdo_ipc_ListMP_Object_first( void )
{
    return (ti_sdo_ipc_ListMP_Handle)ti_sdo_ipc_ListMP_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_ListMP_Handle ti_sdo_ipc_ListMP_Object_next( ti_sdo_ipc_ListMP_Object *obj )
{
    return (ti_sdo_ipc_ListMP_Handle)ti_sdo_ipc_ListMP_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_ListMP_Handle_label( ti_sdo_ipc_ListMP_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_ListMP_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_ListMP_Handle_name( ti_sdo_ipc_ListMP_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_ListMP_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_ListMP_Handle ti_sdo_ipc_ListMP_handle( ti_sdo_ipc_ListMP_Struct *str )
{
    return (ti_sdo_ipc_ListMP_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_ListMP_Struct *ti_sdo_ipc_ListMP_struct( ti_sdo_ipc_ListMP_Handle inst )
{
    return (ti_sdo_ipc_ListMP_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_ListMP__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_ListMP__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_ListMP__internalaccess))

#ifndef ti_sdo_ipc_ListMP__include_state
#define ti_sdo_ipc_ListMP__include_state

/* Module_State */
struct ti_sdo_ipc_ListMP_Module_State {
    ti_sdo_utils_NameServer_Handle nameServer;
};

/* Module__state__V */
extern struct ti_sdo_ipc_ListMP_Module_State__ ti_sdo_ipc_ListMP_Module__state__V;

/* Object */
struct ti_sdo_ipc_ListMP_Object {
    ti_sdo_ipc_ListMP_Attrs *attrs;
    xdc_Ptr nsKey;
    ti_sdo_ipc_Ipc_ObjType objType;
    ti_sdo_ipc_GateMP_Handle gate;
    xdc_SizeT allocSize;
    xdc_UInt16 regionId;
    xdc_Bool cacheEnabled;
    xdc_SizeT cacheLineSize;
};

#endif /* ti_sdo_ipc_ListMP__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_ListMP__nolocalnames)

#ifndef ti_sdo_ipc_ListMP__localnames__done
#define ti_sdo_ipc_ListMP__localnames__done

/* module prefix */
#define ListMP_Instance ti_sdo_ipc_ListMP_Instance
#define ListMP_Handle ti_sdo_ipc_ListMP_Handle
#define ListMP_Module ti_sdo_ipc_ListMP_Module
#define ListMP_Object ti_sdo_ipc_ListMP_Object
#define ListMP_Struct ti_sdo_ipc_ListMP_Struct
#define ListMP_CREATED ti_sdo_ipc_ListMP_CREATED
#define ListMP_Elem ti_sdo_ipc_ListMP_Elem
#define ListMP_Attrs ti_sdo_ipc_ListMP_Attrs
#define ListMP_Instance_State ti_sdo_ipc_ListMP_Instance_State
#define ListMP_Module_State ti_sdo_ipc_ListMP_Module_State
#define ListMP_Params ti_sdo_ipc_ListMP_Params
#define ListMP_Module_name ti_sdo_ipc_ListMP_Module_name
#define ListMP_Module_id ti_sdo_ipc_ListMP_Module_id
#define ListMP_Module_startup ti_sdo_ipc_ListMP_Module_startup
#define ListMP_Module_startupDone ti_sdo_ipc_ListMP_Module_startupDone
#define ListMP_Module_hasMask ti_sdo_ipc_ListMP_Module_hasMask
#define ListMP_Module_getMask ti_sdo_ipc_ListMP_Module_getMask
#define ListMP_Module_setMask ti_sdo_ipc_ListMP_Module_setMask
#define ListMP_Object_heap ti_sdo_ipc_ListMP_Object_heap
#define ListMP_Module_heap ti_sdo_ipc_ListMP_Module_heap
#define ListMP_construct ti_sdo_ipc_ListMP_construct
#define ListMP_create ti_sdo_ipc_ListMP_create
#define ListMP_handle ti_sdo_ipc_ListMP_handle
#define ListMP_struct ti_sdo_ipc_ListMP_struct
#define ListMP_Handle_label ti_sdo_ipc_ListMP_Handle_label
#define ListMP_Handle_name ti_sdo_ipc_ListMP_Handle_name
#define ListMP_Instance_init ti_sdo_ipc_ListMP_Instance_init
#define ListMP_Object_count ti_sdo_ipc_ListMP_Object_count
#define ListMP_Object_get ti_sdo_ipc_ListMP_Object_get
#define ListMP_Object_first ti_sdo_ipc_ListMP_Object_first
#define ListMP_Object_next ti_sdo_ipc_ListMP_Object_next
#define ListMP_Object_sizeof ti_sdo_ipc_ListMP_Object_sizeof
#define ListMP_Params_copy ti_sdo_ipc_ListMP_Params_copy
#define ListMP_Params_init ti_sdo_ipc_ListMP_Params_init
#define ListMP_Instance_finalize ti_sdo_ipc_ListMP_Instance_finalize
#define ListMP_delete ti_sdo_ipc_ListMP_delete
#define ListMP_destruct ti_sdo_ipc_ListMP_destruct

#endif /* ti_sdo_ipc_ListMP__localnames__done */
#endif
