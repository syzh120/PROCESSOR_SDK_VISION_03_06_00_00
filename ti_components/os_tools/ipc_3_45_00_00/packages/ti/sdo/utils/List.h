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

#ifndef ti_sdo_utils_List__include
#define ti_sdo_utils_List__include

#ifndef __nested__
#define __nested__
#define ti_sdo_utils_List__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_utils_List___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/utils/package/package.defs.h>

#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Elem */
struct ti_sdo_utils_List_Elem {
    ti_sdo_utils_List_Elem *volatile next;
    ti_sdo_utils_List_Elem *volatile prev;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_utils_List_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__diagsEnabled ti_sdo_utils_List_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_utils_List_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__diagsIncluded ti_sdo_utils_List_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_utils_List_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__diagsMask ti_sdo_utils_List_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_utils_List_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__gateObj ti_sdo_utils_List_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_utils_List_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__gatePrms ti_sdo_utils_List_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_utils_List_Module__id;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__id ti_sdo_utils_List_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_utils_List_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__loggerDefined ti_sdo_utils_List_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_utils_List_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__loggerObj ti_sdo_utils_List_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_utils_List_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__loggerFxn0 ti_sdo_utils_List_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_utils_List_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__loggerFxn1 ti_sdo_utils_List_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_utils_List_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__loggerFxn2 ti_sdo_utils_List_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_utils_List_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__loggerFxn4 ti_sdo_utils_List_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_utils_List_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_utils_List_Module__loggerFxn8 ti_sdo_utils_List_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_utils_List_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_utils_List_Module__startupDoneFxn ti_sdo_utils_List_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_utils_List_Object__count;
__extern __FAR__ const CT__ti_sdo_utils_List_Object__count ti_sdo_utils_List_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_utils_List_Object__heap;
__extern __FAR__ const CT__ti_sdo_utils_List_Object__heap ti_sdo_utils_List_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_utils_List_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_utils_List_Object__sizeof ti_sdo_utils_List_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_utils_List_Object__table;
__extern __FAR__ const CT__ti_sdo_utils_List_Object__table ti_sdo_utils_List_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_utils_List_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_utils_List_Struct {
    ti_sdo_utils_List_Elem __f0;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_utils_List_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_utils_List_Instance_init__E, "ti_sdo_utils_List_Instance_init")
__extern xdc_Void ti_sdo_utils_List_Instance_init__E(ti_sdo_utils_List_Object *, const ti_sdo_utils_List_Params *);

/* Handle__label__S */
xdc__CODESECT(ti_sdo_utils_List_Handle__label__S, "ti_sdo_utils_List_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_utils_List_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_utils_List_Module__startupDone__S, "ti_sdo_utils_List_Module__startupDone__S")
__extern xdc_Bool ti_sdo_utils_List_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_utils_List_Object__create__S, "ti_sdo_utils_List_Object__create__S")
__extern xdc_Ptr ti_sdo_utils_List_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_utils_List_create, "ti_sdo_utils_List_create")
__extern ti_sdo_utils_List_Handle ti_sdo_utils_List_create( const ti_sdo_utils_List_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_utils_List_construct, "ti_sdo_utils_List_construct")
__extern void ti_sdo_utils_List_construct( ti_sdo_utils_List_Struct *__obj, const ti_sdo_utils_List_Params *__prms );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_utils_List_Object__delete__S, "ti_sdo_utils_List_Object__delete__S")
__extern xdc_Void ti_sdo_utils_List_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_utils_List_delete, "ti_sdo_utils_List_delete")
__extern void ti_sdo_utils_List_delete(ti_sdo_utils_List_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_utils_List_Object__destruct__S, "ti_sdo_utils_List_Object__destruct__S")
__extern xdc_Void ti_sdo_utils_List_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_utils_List_destruct, "ti_sdo_utils_List_destruct")
__extern void ti_sdo_utils_List_destruct(ti_sdo_utils_List_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_utils_List_Object__get__S, "ti_sdo_utils_List_Object__get__S")
__extern xdc_Ptr ti_sdo_utils_List_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_utils_List_Object__first__S, "ti_sdo_utils_List_Object__first__S")
__extern xdc_Ptr ti_sdo_utils_List_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_utils_List_Object__next__S, "ti_sdo_utils_List_Object__next__S")
__extern xdc_Ptr ti_sdo_utils_List_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_utils_List_Params__init__S, "ti_sdo_utils_List_Params__init__S")
__extern xdc_Void ti_sdo_utils_List_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* elemClear__E */
#define ti_sdo_utils_List_elemClear ti_sdo_utils_List_elemClear__E
xdc__CODESECT(ti_sdo_utils_List_elemClear__E, "ti_sdo_utils_List_elemClear")
__extern xdc_Void ti_sdo_utils_List_elemClear__E( ti_sdo_utils_List_Elem *elem );

/* empty__E */
#define ti_sdo_utils_List_empty ti_sdo_utils_List_empty__E
xdc__CODESECT(ti_sdo_utils_List_empty__E, "ti_sdo_utils_List_empty")
__extern xdc_Bool ti_sdo_utils_List_empty__E( ti_sdo_utils_List_Handle __inst );

/* get__E */
#define ti_sdo_utils_List_get ti_sdo_utils_List_get__E
xdc__CODESECT(ti_sdo_utils_List_get__E, "ti_sdo_utils_List_get")
__extern xdc_Ptr ti_sdo_utils_List_get__E( ti_sdo_utils_List_Handle __inst );

/* put__E */
#define ti_sdo_utils_List_put ti_sdo_utils_List_put__E
xdc__CODESECT(ti_sdo_utils_List_put__E, "ti_sdo_utils_List_put")
__extern xdc_Void ti_sdo_utils_List_put__E( ti_sdo_utils_List_Handle __inst, ti_sdo_utils_List_Elem *elem );

/* putHead__E */
#define ti_sdo_utils_List_putHead ti_sdo_utils_List_putHead__E
xdc__CODESECT(ti_sdo_utils_List_putHead__E, "ti_sdo_utils_List_putHead")
__extern xdc_Void ti_sdo_utils_List_putHead__E( ti_sdo_utils_List_Handle __inst, ti_sdo_utils_List_Elem *elem );

/* next__E */
#define ti_sdo_utils_List_next ti_sdo_utils_List_next__E
xdc__CODESECT(ti_sdo_utils_List_next__E, "ti_sdo_utils_List_next")
__extern xdc_Ptr ti_sdo_utils_List_next__E( ti_sdo_utils_List_Handle __inst, ti_sdo_utils_List_Elem *elem );

/* prev__E */
#define ti_sdo_utils_List_prev ti_sdo_utils_List_prev__E
xdc__CODESECT(ti_sdo_utils_List_prev__E, "ti_sdo_utils_List_prev")
__extern xdc_Ptr ti_sdo_utils_List_prev__E( ti_sdo_utils_List_Handle __inst, ti_sdo_utils_List_Elem *elem );

/* insert__E */
#define ti_sdo_utils_List_insert ti_sdo_utils_List_insert__E
xdc__CODESECT(ti_sdo_utils_List_insert__E, "ti_sdo_utils_List_insert")
__extern xdc_Void ti_sdo_utils_List_insert__E( ti_sdo_utils_List_Handle __inst, ti_sdo_utils_List_Elem *newElem, ti_sdo_utils_List_Elem *curElem );

/* remove__E */
#define ti_sdo_utils_List_remove ti_sdo_utils_List_remove__E
xdc__CODESECT(ti_sdo_utils_List_remove__E, "ti_sdo_utils_List_remove")
__extern xdc_Void ti_sdo_utils_List_remove__E( ti_sdo_utils_List_Handle __inst, ti_sdo_utils_List_Elem *elem );

/* dequeue__E */
#define ti_sdo_utils_List_dequeue ti_sdo_utils_List_dequeue__E
xdc__CODESECT(ti_sdo_utils_List_dequeue__E, "ti_sdo_utils_List_dequeue")
__extern xdc_Ptr ti_sdo_utils_List_dequeue__E( ti_sdo_utils_List_Handle __inst );

/* enqueue__E */
#define ti_sdo_utils_List_enqueue ti_sdo_utils_List_enqueue__E
xdc__CODESECT(ti_sdo_utils_List_enqueue__E, "ti_sdo_utils_List_enqueue")
__extern xdc_Void ti_sdo_utils_List_enqueue__E( ti_sdo_utils_List_Handle __inst, ti_sdo_utils_List_Elem *elem );

/* enqueueHead__E */
#define ti_sdo_utils_List_enqueueHead ti_sdo_utils_List_enqueueHead__E
xdc__CODESECT(ti_sdo_utils_List_enqueueHead__E, "ti_sdo_utils_List_enqueueHead")
__extern xdc_Void ti_sdo_utils_List_enqueueHead__E( ti_sdo_utils_List_Handle __inst, ti_sdo_utils_List_Elem *elem );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_utils_List_Module_startupDone() ti_sdo_utils_List_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_utils_List_Object_heap() ti_sdo_utils_List_Object__heap__C

/* Module_heap */
#define ti_sdo_utils_List_Module_heap() ti_sdo_utils_List_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_utils_List_Module__id ti_sdo_utils_List_Module_id( void ) 
{
    return ti_sdo_utils_List_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_utils_List_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_utils_List_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_utils_List_Module_getMask( void ) 
{
    return ti_sdo_utils_List_Module__diagsMask__C != NULL ? *ti_sdo_utils_List_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_utils_List_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_utils_List_Module__diagsMask__C != NULL) {
        *ti_sdo_utils_List_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_utils_List_Params_init( ti_sdo_utils_List_Params *prms ) 
{
    if (prms) {
        ti_sdo_utils_List_Params__init__S(prms, 0, sizeof(ti_sdo_utils_List_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_utils_List_Params_copy(ti_sdo_utils_List_Params *dst, const ti_sdo_utils_List_Params *src) 
{
    if (dst) {
        ti_sdo_utils_List_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_utils_List_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_utils_List_Object_count() ti_sdo_utils_List_Object__count__C

/* Object_sizeof */
#define ti_sdo_utils_List_Object_sizeof() ti_sdo_utils_List_Object__sizeof__C

/* Object_get */
static inline ti_sdo_utils_List_Handle ti_sdo_utils_List_Object_get(ti_sdo_utils_List_Instance_State *oarr, int i) 
{
    return (ti_sdo_utils_List_Handle)ti_sdo_utils_List_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_utils_List_Handle ti_sdo_utils_List_Object_first( void )
{
    return (ti_sdo_utils_List_Handle)ti_sdo_utils_List_Object__first__S();
}

/* Object_next */
static inline ti_sdo_utils_List_Handle ti_sdo_utils_List_Object_next( ti_sdo_utils_List_Object *obj )
{
    return (ti_sdo_utils_List_Handle)ti_sdo_utils_List_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_utils_List_Handle_label( ti_sdo_utils_List_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_utils_List_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_utils_List_Handle_name( ti_sdo_utils_List_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_utils_List_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_utils_List_Handle ti_sdo_utils_List_handle( ti_sdo_utils_List_Struct *str )
{
    return (ti_sdo_utils_List_Handle)str;
}

/* struct */
static inline ti_sdo_utils_List_Struct *ti_sdo_utils_List_struct( ti_sdo_utils_List_Handle inst )
{
    return (ti_sdo_utils_List_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_utils_List__top__
#undef __nested__
#endif

#endif /* ti_sdo_utils_List__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_utils_List__internalaccess))

#ifndef ti_sdo_utils_List__include_state
#define ti_sdo_utils_List__include_state

/* Object */
struct ti_sdo_utils_List_Object {
    ti_sdo_utils_List_Elem elem;
};

#endif /* ti_sdo_utils_List__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_utils_List__nolocalnames)

#ifndef ti_sdo_utils_List__localnames__done
#define ti_sdo_utils_List__localnames__done

/* module prefix */
#define List_Instance ti_sdo_utils_List_Instance
#define List_Handle ti_sdo_utils_List_Handle
#define List_Module ti_sdo_utils_List_Module
#define List_Object ti_sdo_utils_List_Object
#define List_Struct ti_sdo_utils_List_Struct
#define List_Elem ti_sdo_utils_List_Elem
#define List_Instance_State ti_sdo_utils_List_Instance_State
#define List_Params ti_sdo_utils_List_Params
#define List_elemClear ti_sdo_utils_List_elemClear
#define List_empty ti_sdo_utils_List_empty
#define List_get ti_sdo_utils_List_get
#define List_put ti_sdo_utils_List_put
#define List_putHead ti_sdo_utils_List_putHead
#define List_next ti_sdo_utils_List_next
#define List_prev ti_sdo_utils_List_prev
#define List_insert ti_sdo_utils_List_insert
#define List_remove ti_sdo_utils_List_remove
#define List_dequeue ti_sdo_utils_List_dequeue
#define List_enqueue ti_sdo_utils_List_enqueue
#define List_enqueueHead ti_sdo_utils_List_enqueueHead
#define List_Module_name ti_sdo_utils_List_Module_name
#define List_Module_id ti_sdo_utils_List_Module_id
#define List_Module_startup ti_sdo_utils_List_Module_startup
#define List_Module_startupDone ti_sdo_utils_List_Module_startupDone
#define List_Module_hasMask ti_sdo_utils_List_Module_hasMask
#define List_Module_getMask ti_sdo_utils_List_Module_getMask
#define List_Module_setMask ti_sdo_utils_List_Module_setMask
#define List_Object_heap ti_sdo_utils_List_Object_heap
#define List_Module_heap ti_sdo_utils_List_Module_heap
#define List_construct ti_sdo_utils_List_construct
#define List_create ti_sdo_utils_List_create
#define List_handle ti_sdo_utils_List_handle
#define List_struct ti_sdo_utils_List_struct
#define List_Handle_label ti_sdo_utils_List_Handle_label
#define List_Handle_name ti_sdo_utils_List_Handle_name
#define List_Instance_init ti_sdo_utils_List_Instance_init
#define List_Object_count ti_sdo_utils_List_Object_count
#define List_Object_get ti_sdo_utils_List_Object_get
#define List_Object_first ti_sdo_utils_List_Object_first
#define List_Object_next ti_sdo_utils_List_Object_next
#define List_Object_sizeof ti_sdo_utils_List_Object_sizeof
#define List_Params_copy ti_sdo_utils_List_Params_copy
#define List_Params_init ti_sdo_utils_List_Params_init
#define List_delete ti_sdo_utils_List_delete
#define List_destruct ti_sdo_utils_List_destruct

#endif /* ti_sdo_utils_List__localnames__done */
#endif
