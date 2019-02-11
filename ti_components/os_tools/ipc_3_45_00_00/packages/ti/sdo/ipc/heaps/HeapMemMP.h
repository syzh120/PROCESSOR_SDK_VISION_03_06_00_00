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

#ifndef ti_sdo_ipc_heaps_HeapMemMP__include
#define ti_sdo_ipc_heaps_HeapMemMP__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_heaps_HeapMemMP__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_heaps_HeapMemMP___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/heaps/package/package.defs.h>

#include <ti/sdo/ipc/SharedRegion.h>
#include <ti/sdo/ipc/Ipc.h>
#include <ti/sdo/ipc/GateMP.h>
#include <ti/sdo/utils/NameServer.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/IHeap.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* ExtendedStats */
struct ti_sdo_ipc_heaps_HeapMemMP_ExtendedStats {
    xdc_Ptr buf;
    xdc_SizeT size;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* CREATED */
#define ti_sdo_ipc_heaps_HeapMemMP_CREATED (0x07041776)

/* Header */
struct ti_sdo_ipc_heaps_HeapMemMP_Header {
    ti_sdo_ipc_SharedRegion_SRPtr next;
    xdc_Bits32 size;
};

/* Attrs */
struct ti_sdo_ipc_heaps_HeapMemMP_Attrs {
    xdc_Bits32 status;
    ti_sdo_ipc_SharedRegion_SRPtr bufPtr;
    ti_sdo_ipc_heaps_HeapMemMP_Header head;
    ti_sdo_ipc_SharedRegion_SRPtr gateMPAddr;
};


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_heaps_HeapMemMP_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__diagsEnabled ti_sdo_ipc_heaps_HeapMemMP_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_heaps_HeapMemMP_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__diagsIncluded ti_sdo_ipc_heaps_HeapMemMP_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_heaps_HeapMemMP_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__diagsMask ti_sdo_ipc_heaps_HeapMemMP_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_heaps_HeapMemMP_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__gateObj ti_sdo_ipc_heaps_HeapMemMP_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_heaps_HeapMemMP_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__gatePrms ti_sdo_ipc_heaps_HeapMemMP_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_heaps_HeapMemMP_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__id ti_sdo_ipc_heaps_HeapMemMP_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerDefined ti_sdo_ipc_heaps_HeapMemMP_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerObj ti_sdo_ipc_heaps_HeapMemMP_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn0 ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn1 ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn2 ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn4 ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn8 ti_sdo_ipc_heaps_HeapMemMP_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_heaps_HeapMemMP_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Module__startupDoneFxn ti_sdo_ipc_heaps_HeapMemMP_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_heaps_HeapMemMP_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Object__count ti_sdo_ipc_heaps_HeapMemMP_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_heaps_HeapMemMP_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Object__heap ti_sdo_ipc_heaps_HeapMemMP_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_heaps_HeapMemMP_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Object__sizeof ti_sdo_ipc_heaps_HeapMemMP_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_heaps_HeapMemMP_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_Object__table ti_sdo_ipc_heaps_HeapMemMP_Object__table__C;

/* A_zeroBlock */
#define ti_sdo_ipc_heaps_HeapMemMP_A_zeroBlock (ti_sdo_ipc_heaps_HeapMemMP_A_zeroBlock__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_heaps_HeapMemMP_A_zeroBlock;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_A_zeroBlock ti_sdo_ipc_heaps_HeapMemMP_A_zeroBlock__C;

/* A_heapSize */
#define ti_sdo_ipc_heaps_HeapMemMP_A_heapSize (ti_sdo_ipc_heaps_HeapMemMP_A_heapSize__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_heaps_HeapMemMP_A_heapSize;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_A_heapSize ti_sdo_ipc_heaps_HeapMemMP_A_heapSize__C;

/* A_align */
#define ti_sdo_ipc_heaps_HeapMemMP_A_align (ti_sdo_ipc_heaps_HeapMemMP_A_align__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_heaps_HeapMemMP_A_align;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_A_align ti_sdo_ipc_heaps_HeapMemMP_A_align__C;

/* A_invalidFree */
#define ti_sdo_ipc_heaps_HeapMemMP_A_invalidFree (ti_sdo_ipc_heaps_HeapMemMP_A_invalidFree__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_heaps_HeapMemMP_A_invalidFree;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_A_invalidFree ti_sdo_ipc_heaps_HeapMemMP_A_invalidFree__C;

/* E_memory */
#define ti_sdo_ipc_heaps_HeapMemMP_E_memory (ti_sdo_ipc_heaps_HeapMemMP_E_memory__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_heaps_HeapMemMP_E_memory;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_E_memory ti_sdo_ipc_heaps_HeapMemMP_E_memory__C;

/* maxNameLen */
#ifdef ti_sdo_ipc_heaps_HeapMemMP_maxNameLen__D
#define ti_sdo_ipc_heaps_HeapMemMP_maxNameLen (ti_sdo_ipc_heaps_HeapMemMP_maxNameLen__D)
#else
#define ti_sdo_ipc_heaps_HeapMemMP_maxNameLen (ti_sdo_ipc_heaps_HeapMemMP_maxNameLen__C)
typedef xdc_UInt CT__ti_sdo_ipc_heaps_HeapMemMP_maxNameLen;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMemMP_maxNameLen ti_sdo_ipc_heaps_HeapMemMP_maxNameLen__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_heaps_HeapMemMP_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    ti_sdo_ipc_GateMP_Handle gate;
    xdc_Bool openFlag;
    xdc_String name;
    xdc_UInt16 regionId;
    xdc_Ptr sharedAddr;
    xdc_SizeT sharedBufSize;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_heaps_HeapMemMP_Struct {
    const ti_sdo_ipc_heaps_HeapMemMP_Fxns__ *__fxns;
    ti_sdo_ipc_heaps_HeapMemMP_Attrs *__f0;
    ti_sdo_ipc_GateMP_Handle __f1;
    ti_sdo_ipc_Ipc_ObjType __f2;
    xdc_Ptr __f3;
    xdc_Bool __f4;
    xdc_UInt16 __f5;
    xdc_SizeT __f6;
    xdc_Char *__f7;
    xdc_SizeT __f8;
    xdc_SizeT __f9;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_heaps_HeapMemMP_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Ptr (*alloc)(ti_sdo_ipc_heaps_HeapMemMP_Handle, xdc_SizeT, xdc_SizeT, xdc_runtime_Error_Block*);
    xdc_Void (*free)(ti_sdo_ipc_heaps_HeapMemMP_Handle, xdc_Ptr, xdc_SizeT);
    xdc_Bool (*isBlocking)(ti_sdo_ipc_heaps_HeapMemMP_Handle);
    xdc_Void (*getStats)(ti_sdo_ipc_heaps_HeapMemMP_Handle, xdc_runtime_Memory_Stats*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_heaps_HeapMemMP_Fxns__ ti_sdo_ipc_heaps_HeapMemMP_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_heaps_HeapMemMP_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_Instance_init__E, "ti_sdo_ipc_heaps_HeapMemMP_Instance_init")
__extern xdc_Int ti_sdo_ipc_heaps_HeapMemMP_Instance_init__E(ti_sdo_ipc_heaps_HeapMemMP_Object *, const ti_sdo_ipc_heaps_HeapMemMP_Params *, xdc_runtime_Error_Block *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_Instance_finalize__E, "ti_sdo_ipc_heaps_HeapMemMP_Instance_finalize")
__extern void ti_sdo_ipc_heaps_HeapMemMP_Instance_finalize__E( ti_sdo_ipc_heaps_HeapMemMP_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_Handle__label__S, "ti_sdo_ipc_heaps_HeapMemMP_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_heaps_HeapMemMP_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_Module__startupDone__S, "ti_sdo_ipc_heaps_HeapMemMP_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_heaps_HeapMemMP_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_Object__create__S, "ti_sdo_ipc_heaps_HeapMemMP_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_heaps_HeapMemMP_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_create, "ti_sdo_ipc_heaps_HeapMemMP_create")
__extern ti_sdo_ipc_heaps_HeapMemMP_Handle ti_sdo_ipc_heaps_HeapMemMP_create( const ti_sdo_ipc_heaps_HeapMemMP_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_construct, "ti_sdo_ipc_heaps_HeapMemMP_construct")
__extern void ti_sdo_ipc_heaps_HeapMemMP_construct( ti_sdo_ipc_heaps_HeapMemMP_Struct *__obj, const ti_sdo_ipc_heaps_HeapMemMP_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_Object__delete__S, "ti_sdo_ipc_heaps_HeapMemMP_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMemMP_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_delete, "ti_sdo_ipc_heaps_HeapMemMP_delete")
__extern void ti_sdo_ipc_heaps_HeapMemMP_delete(ti_sdo_ipc_heaps_HeapMemMP_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_Object__destruct__S, "ti_sdo_ipc_heaps_HeapMemMP_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMemMP_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_destruct, "ti_sdo_ipc_heaps_HeapMemMP_destruct")
__extern void ti_sdo_ipc_heaps_HeapMemMP_destruct(ti_sdo_ipc_heaps_HeapMemMP_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_Object__get__S, "ti_sdo_ipc_heaps_HeapMemMP_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_heaps_HeapMemMP_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_Object__first__S, "ti_sdo_ipc_heaps_HeapMemMP_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_heaps_HeapMemMP_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_Object__next__S, "ti_sdo_ipc_heaps_HeapMemMP_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_heaps_HeapMemMP_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_Params__init__S, "ti_sdo_ipc_heaps_HeapMemMP_Params__init__S")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMemMP_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* isBlocking__E */
#define ti_sdo_ipc_heaps_HeapMemMP_isBlocking ti_sdo_ipc_heaps_HeapMemMP_isBlocking__E
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_isBlocking__E, "ti_sdo_ipc_heaps_HeapMemMP_isBlocking")
__extern xdc_Bool ti_sdo_ipc_heaps_HeapMemMP_isBlocking__E( ti_sdo_ipc_heaps_HeapMemMP_Handle __inst );

/* getStats__E */
#define ti_sdo_ipc_heaps_HeapMemMP_getStats ti_sdo_ipc_heaps_HeapMemMP_getStats__E
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_getStats__E, "ti_sdo_ipc_heaps_HeapMemMP_getStats")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMemMP_getStats__E( ti_sdo_ipc_heaps_HeapMemMP_Handle __inst, xdc_runtime_Memory_Stats *stats );

/* alloc__E */
#define ti_sdo_ipc_heaps_HeapMemMP_alloc ti_sdo_ipc_heaps_HeapMemMP_alloc__E
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_alloc__E, "ti_sdo_ipc_heaps_HeapMemMP_alloc")
__extern xdc_Ptr ti_sdo_ipc_heaps_HeapMemMP_alloc__E( ti_sdo_ipc_heaps_HeapMemMP_Handle __inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block *eb );

/* free__E */
#define ti_sdo_ipc_heaps_HeapMemMP_free ti_sdo_ipc_heaps_HeapMemMP_free__E
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_free__E, "ti_sdo_ipc_heaps_HeapMemMP_free")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMemMP_free__E( ti_sdo_ipc_heaps_HeapMemMP_Handle __inst, xdc_Ptr block, xdc_SizeT size );

/* postInit__I */
#define ti_sdo_ipc_heaps_HeapMemMP_postInit ti_sdo_ipc_heaps_HeapMemMP_postInit__I
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMemMP_postInit__I, "ti_sdo_ipc_heaps_HeapMemMP_postInit")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMemMP_postInit__I( ti_sdo_ipc_heaps_HeapMemMP_Object *obj, xdc_runtime_Error_Block *eb );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_IHeap_Module ti_sdo_ipc_heaps_HeapMemMP_Module_upCast( void )
{
    return (xdc_runtime_IHeap_Module)&ti_sdo_ipc_heaps_HeapMemMP_Module__FXNS__C;
}

/* Module_to_xdc_runtime_IHeap */
#define ti_sdo_ipc_heaps_HeapMemMP_Module_to_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMemMP_Module_upCast

/* Handle_upCast */
static inline xdc_runtime_IHeap_Handle ti_sdo_ipc_heaps_HeapMemMP_Handle_upCast( ti_sdo_ipc_heaps_HeapMemMP_Handle i )
{
    return (xdc_runtime_IHeap_Handle)i;
}

/* Handle_to_xdc_runtime_IHeap */
#define ti_sdo_ipc_heaps_HeapMemMP_Handle_to_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMemMP_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_heaps_HeapMemMP_Handle ti_sdo_ipc_heaps_HeapMemMP_Handle_downCast( xdc_runtime_IHeap_Handle i )
{
    xdc_runtime_IHeap_Handle i2 = (xdc_runtime_IHeap_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_heaps_HeapMemMP_Module__FXNS__C ? (ti_sdo_ipc_heaps_HeapMemMP_Handle)i : (ti_sdo_ipc_heaps_HeapMemMP_Handle)0;
}

/* Handle_from_xdc_runtime_IHeap */
#define ti_sdo_ipc_heaps_HeapMemMP_Handle_from_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMemMP_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_heaps_HeapMemMP_Module_startupDone() ti_sdo_ipc_heaps_HeapMemMP_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_heaps_HeapMemMP_Object_heap() ti_sdo_ipc_heaps_HeapMemMP_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_heaps_HeapMemMP_Module_heap() ti_sdo_ipc_heaps_HeapMemMP_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_heaps_HeapMemMP_Module__id ti_sdo_ipc_heaps_HeapMemMP_Module_id( void ) 
{
    return ti_sdo_ipc_heaps_HeapMemMP_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_heaps_HeapMemMP_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_heaps_HeapMemMP_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_heaps_HeapMemMP_Module_getMask( void ) 
{
    return ti_sdo_ipc_heaps_HeapMemMP_Module__diagsMask__C != NULL ? *ti_sdo_ipc_heaps_HeapMemMP_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_heaps_HeapMemMP_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_heaps_HeapMemMP_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_heaps_HeapMemMP_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_heaps_HeapMemMP_Params_init( ti_sdo_ipc_heaps_HeapMemMP_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_heaps_HeapMemMP_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_heaps_HeapMemMP_Params_copy(ti_sdo_ipc_heaps_HeapMemMP_Params *dst, const ti_sdo_ipc_heaps_HeapMemMP_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_heaps_HeapMemMP_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_heaps_HeapMemMP_Object_count() ti_sdo_ipc_heaps_HeapMemMP_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_heaps_HeapMemMP_Object_sizeof() ti_sdo_ipc_heaps_HeapMemMP_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_heaps_HeapMemMP_Handle ti_sdo_ipc_heaps_HeapMemMP_Object_get(ti_sdo_ipc_heaps_HeapMemMP_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_heaps_HeapMemMP_Handle)ti_sdo_ipc_heaps_HeapMemMP_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_heaps_HeapMemMP_Handle ti_sdo_ipc_heaps_HeapMemMP_Object_first( void )
{
    return (ti_sdo_ipc_heaps_HeapMemMP_Handle)ti_sdo_ipc_heaps_HeapMemMP_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_heaps_HeapMemMP_Handle ti_sdo_ipc_heaps_HeapMemMP_Object_next( ti_sdo_ipc_heaps_HeapMemMP_Object *obj )
{
    return (ti_sdo_ipc_heaps_HeapMemMP_Handle)ti_sdo_ipc_heaps_HeapMemMP_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_heaps_HeapMemMP_Handle_label( ti_sdo_ipc_heaps_HeapMemMP_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_heaps_HeapMemMP_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_heaps_HeapMemMP_Handle_name( ti_sdo_ipc_heaps_HeapMemMP_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_heaps_HeapMemMP_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_heaps_HeapMemMP_Handle ti_sdo_ipc_heaps_HeapMemMP_handle( ti_sdo_ipc_heaps_HeapMemMP_Struct *str )
{
    return (ti_sdo_ipc_heaps_HeapMemMP_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_heaps_HeapMemMP_Struct *ti_sdo_ipc_heaps_HeapMemMP_struct( ti_sdo_ipc_heaps_HeapMemMP_Handle inst )
{
    return (ti_sdo_ipc_heaps_HeapMemMP_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_heaps_HeapMemMP__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_heaps_HeapMemMP__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_heaps_HeapMemMP__internalaccess))

#ifndef ti_sdo_ipc_heaps_HeapMemMP__include_state
#define ti_sdo_ipc_heaps_HeapMemMP__include_state

/* Module_State */
struct ti_sdo_ipc_heaps_HeapMemMP_Module_State {
    ti_sdo_utils_NameServer_Handle nameServer;
};

/* Module__state__V */
extern struct ti_sdo_ipc_heaps_HeapMemMP_Module_State__ ti_sdo_ipc_heaps_HeapMemMP_Module__state__V;

/* Object */
struct ti_sdo_ipc_heaps_HeapMemMP_Object {
    const ti_sdo_ipc_heaps_HeapMemMP_Fxns__ *__fxns;
    ti_sdo_ipc_heaps_HeapMemMP_Attrs *attrs;
    ti_sdo_ipc_GateMP_Handle gate;
    ti_sdo_ipc_Ipc_ObjType objType;
    xdc_Ptr nsKey;
    xdc_Bool cacheEnabled;
    xdc_UInt16 regionId;
    xdc_SizeT allocSize;
    xdc_Char *buf;
    xdc_SizeT minAlign;
    xdc_SizeT bufSize;
};

#endif /* ti_sdo_ipc_heaps_HeapMemMP__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_heaps_HeapMemMP__nolocalnames)

#ifndef ti_sdo_ipc_heaps_HeapMemMP__localnames__done
#define ti_sdo_ipc_heaps_HeapMemMP__localnames__done

/* module prefix */
#define HeapMemMP_Instance ti_sdo_ipc_heaps_HeapMemMP_Instance
#define HeapMemMP_Handle ti_sdo_ipc_heaps_HeapMemMP_Handle
#define HeapMemMP_Module ti_sdo_ipc_heaps_HeapMemMP_Module
#define HeapMemMP_Object ti_sdo_ipc_heaps_HeapMemMP_Object
#define HeapMemMP_Struct ti_sdo_ipc_heaps_HeapMemMP_Struct
#define HeapMemMP_ExtendedStats ti_sdo_ipc_heaps_HeapMemMP_ExtendedStats
#define HeapMemMP_CREATED ti_sdo_ipc_heaps_HeapMemMP_CREATED
#define HeapMemMP_Header ti_sdo_ipc_heaps_HeapMemMP_Header
#define HeapMemMP_Attrs ti_sdo_ipc_heaps_HeapMemMP_Attrs
#define HeapMemMP_Instance_State ti_sdo_ipc_heaps_HeapMemMP_Instance_State
#define HeapMemMP_Module_State ti_sdo_ipc_heaps_HeapMemMP_Module_State
#define HeapMemMP_A_zeroBlock ti_sdo_ipc_heaps_HeapMemMP_A_zeroBlock
#define HeapMemMP_A_heapSize ti_sdo_ipc_heaps_HeapMemMP_A_heapSize
#define HeapMemMP_A_align ti_sdo_ipc_heaps_HeapMemMP_A_align
#define HeapMemMP_A_invalidFree ti_sdo_ipc_heaps_HeapMemMP_A_invalidFree
#define HeapMemMP_E_memory ti_sdo_ipc_heaps_HeapMemMP_E_memory
#define HeapMemMP_maxNameLen ti_sdo_ipc_heaps_HeapMemMP_maxNameLen
#define HeapMemMP_Params ti_sdo_ipc_heaps_HeapMemMP_Params
#define HeapMemMP_isBlocking ti_sdo_ipc_heaps_HeapMemMP_isBlocking
#define HeapMemMP_getStats ti_sdo_ipc_heaps_HeapMemMP_getStats
#define HeapMemMP_alloc ti_sdo_ipc_heaps_HeapMemMP_alloc
#define HeapMemMP_free ti_sdo_ipc_heaps_HeapMemMP_free
#define HeapMemMP_Module_name ti_sdo_ipc_heaps_HeapMemMP_Module_name
#define HeapMemMP_Module_id ti_sdo_ipc_heaps_HeapMemMP_Module_id
#define HeapMemMP_Module_startup ti_sdo_ipc_heaps_HeapMemMP_Module_startup
#define HeapMemMP_Module_startupDone ti_sdo_ipc_heaps_HeapMemMP_Module_startupDone
#define HeapMemMP_Module_hasMask ti_sdo_ipc_heaps_HeapMemMP_Module_hasMask
#define HeapMemMP_Module_getMask ti_sdo_ipc_heaps_HeapMemMP_Module_getMask
#define HeapMemMP_Module_setMask ti_sdo_ipc_heaps_HeapMemMP_Module_setMask
#define HeapMemMP_Object_heap ti_sdo_ipc_heaps_HeapMemMP_Object_heap
#define HeapMemMP_Module_heap ti_sdo_ipc_heaps_HeapMemMP_Module_heap
#define HeapMemMP_construct ti_sdo_ipc_heaps_HeapMemMP_construct
#define HeapMemMP_create ti_sdo_ipc_heaps_HeapMemMP_create
#define HeapMemMP_handle ti_sdo_ipc_heaps_HeapMemMP_handle
#define HeapMemMP_struct ti_sdo_ipc_heaps_HeapMemMP_struct
#define HeapMemMP_Handle_label ti_sdo_ipc_heaps_HeapMemMP_Handle_label
#define HeapMemMP_Handle_name ti_sdo_ipc_heaps_HeapMemMP_Handle_name
#define HeapMemMP_Instance_init ti_sdo_ipc_heaps_HeapMemMP_Instance_init
#define HeapMemMP_Object_count ti_sdo_ipc_heaps_HeapMemMP_Object_count
#define HeapMemMP_Object_get ti_sdo_ipc_heaps_HeapMemMP_Object_get
#define HeapMemMP_Object_first ti_sdo_ipc_heaps_HeapMemMP_Object_first
#define HeapMemMP_Object_next ti_sdo_ipc_heaps_HeapMemMP_Object_next
#define HeapMemMP_Object_sizeof ti_sdo_ipc_heaps_HeapMemMP_Object_sizeof
#define HeapMemMP_Params_copy ti_sdo_ipc_heaps_HeapMemMP_Params_copy
#define HeapMemMP_Params_init ti_sdo_ipc_heaps_HeapMemMP_Params_init
#define HeapMemMP_Instance_finalize ti_sdo_ipc_heaps_HeapMemMP_Instance_finalize
#define HeapMemMP_delete ti_sdo_ipc_heaps_HeapMemMP_delete
#define HeapMemMP_destruct ti_sdo_ipc_heaps_HeapMemMP_destruct
#define HeapMemMP_Module_upCast ti_sdo_ipc_heaps_HeapMemMP_Module_upCast
#define HeapMemMP_Module_to_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMemMP_Module_to_xdc_runtime_IHeap
#define HeapMemMP_Handle_upCast ti_sdo_ipc_heaps_HeapMemMP_Handle_upCast
#define HeapMemMP_Handle_to_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMemMP_Handle_to_xdc_runtime_IHeap
#define HeapMemMP_Handle_downCast ti_sdo_ipc_heaps_HeapMemMP_Handle_downCast
#define HeapMemMP_Handle_from_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMemMP_Handle_from_xdc_runtime_IHeap

#endif /* ti_sdo_ipc_heaps_HeapMemMP__localnames__done */
#endif
