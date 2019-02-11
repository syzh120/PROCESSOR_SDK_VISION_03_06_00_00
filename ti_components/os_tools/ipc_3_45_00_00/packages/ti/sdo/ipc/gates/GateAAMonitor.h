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

#ifndef ti_sdo_ipc_gates_GateAAMonitor__include
#define ti_sdo_ipc_gates_GateAAMonitor__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_gates_GateAAMonitor__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_gates_GateAAMonitor___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/gates/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <ti/sdo/ipc/Ipc.h>
#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */
#define ti_sdo_ipc_gates_GateAAMonitor_Q_BLOCKING (1)

/* Q_PREEMPTING */
#define ti_sdo_ipc_gates_GateAAMonitor_Q_PREEMPTING (2)


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_gates_GateAAMonitor_Args__create {
    xdc_runtime_IGateProvider_Handle localGate;
} ti_sdo_ipc_gates_GateAAMonitor_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* CACHELINE_SIZE */
#define ti_sdo_ipc_gates_GateAAMonitor_CACHELINE_SIZE (64)

/* SL2_RANGE_BASE */
#define ti_sdo_ipc_gates_GateAAMonitor_SL2_RANGE_BASE (0x00200000)

/* SL2_RANGE_MAX */
#define ti_sdo_ipc_gates_GateAAMonitor_SL2_RANGE_MAX (0x002bffff)


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_gates_GateAAMonitor_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__diagsEnabled ti_sdo_ipc_gates_GateAAMonitor_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_gates_GateAAMonitor_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__diagsIncluded ti_sdo_ipc_gates_GateAAMonitor_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_gates_GateAAMonitor_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__diagsMask ti_sdo_ipc_gates_GateAAMonitor_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateAAMonitor_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__gateObj ti_sdo_ipc_gates_GateAAMonitor_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateAAMonitor_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__gatePrms ti_sdo_ipc_gates_GateAAMonitor_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_gates_GateAAMonitor_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__id ti_sdo_ipc_gates_GateAAMonitor_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerDefined ti_sdo_ipc_gates_GateAAMonitor_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerObj ti_sdo_ipc_gates_GateAAMonitor_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn0 ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn1 ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn2 ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn4 ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn8 ti_sdo_ipc_gates_GateAAMonitor_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_gates_GateAAMonitor_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Module__startupDoneFxn ti_sdo_ipc_gates_GateAAMonitor_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_gates_GateAAMonitor_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Object__count ti_sdo_ipc_gates_GateAAMonitor_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_gates_GateAAMonitor_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Object__heap ti_sdo_ipc_gates_GateAAMonitor_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_gates_GateAAMonitor_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Object__sizeof ti_sdo_ipc_gates_GateAAMonitor_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateAAMonitor_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_Object__table ti_sdo_ipc_gates_GateAAMonitor_Object__table__C;

/* A_invSharedAddr */
#define ti_sdo_ipc_gates_GateAAMonitor_A_invSharedAddr (ti_sdo_ipc_gates_GateAAMonitor_A_invSharedAddr__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_gates_GateAAMonitor_A_invSharedAddr;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_A_invSharedAddr ti_sdo_ipc_gates_GateAAMonitor_A_invSharedAddr__C;

/* numInstances */
#ifdef ti_sdo_ipc_gates_GateAAMonitor_numInstances__D
#define ti_sdo_ipc_gates_GateAAMonitor_numInstances (ti_sdo_ipc_gates_GateAAMonitor_numInstances__D)
#else
#define ti_sdo_ipc_gates_GateAAMonitor_numInstances (ti_sdo_ipc_gates_GateAAMonitor_numInstances__C)
typedef xdc_UInt CT__ti_sdo_ipc_gates_GateAAMonitor_numInstances;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateAAMonitor_numInstances ti_sdo_ipc_gates_GateAAMonitor_numInstances__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_gates_GateAAMonitor_Params {
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
struct ti_sdo_ipc_gates_GateAAMonitor_Struct {
    const ti_sdo_ipc_gates_GateAAMonitor_Fxns__ *__fxns;
    volatile xdc_UInt32 *__f0;
    xdc_UInt __f1;
    xdc_runtime_IGateProvider_Handle __f2;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_gates_GateAAMonitor_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(ti_sdo_ipc_gates_GateAAMonitor_Handle);
    xdc_Void (*leave)(ti_sdo_ipc_gates_GateAAMonitor_Handle, xdc_IArg);
    xdc_Bits32 *(*getReservedMask)(void);
    xdc_SizeT (*sharedMemReq)(const ti_sdo_ipc_interfaces_IGateMPSupport_Params*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_gates_GateAAMonitor_Fxns__ ti_sdo_ipc_gates_GateAAMonitor_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_gates_GateAAMonitor_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_Instance_init__E, "ti_sdo_ipc_gates_GateAAMonitor_Instance_init")
__extern xdc_Int ti_sdo_ipc_gates_GateAAMonitor_Instance_init__E(ti_sdo_ipc_gates_GateAAMonitor_Object *, xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GateAAMonitor_Params *, xdc_runtime_Error_Block *);

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_Handle__label__S, "ti_sdo_ipc_gates_GateAAMonitor_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_gates_GateAAMonitor_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_Module__startupDone__S, "ti_sdo_ipc_gates_GateAAMonitor_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_gates_GateAAMonitor_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_Object__create__S, "ti_sdo_ipc_gates_GateAAMonitor_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateAAMonitor_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_create, "ti_sdo_ipc_gates_GateAAMonitor_create")
__extern ti_sdo_ipc_gates_GateAAMonitor_Handle ti_sdo_ipc_gates_GateAAMonitor_create( xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GateAAMonitor_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_construct, "ti_sdo_ipc_gates_GateAAMonitor_construct")
__extern void ti_sdo_ipc_gates_GateAAMonitor_construct( ti_sdo_ipc_gates_GateAAMonitor_Struct *__obj, xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GateAAMonitor_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_Object__delete__S, "ti_sdo_ipc_gates_GateAAMonitor_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_gates_GateAAMonitor_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_delete, "ti_sdo_ipc_gates_GateAAMonitor_delete")
__extern void ti_sdo_ipc_gates_GateAAMonitor_delete(ti_sdo_ipc_gates_GateAAMonitor_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_Object__destruct__S, "ti_sdo_ipc_gates_GateAAMonitor_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_gates_GateAAMonitor_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_destruct, "ti_sdo_ipc_gates_GateAAMonitor_destruct")
__extern void ti_sdo_ipc_gates_GateAAMonitor_destruct(ti_sdo_ipc_gates_GateAAMonitor_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_Object__get__S, "ti_sdo_ipc_gates_GateAAMonitor_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateAAMonitor_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_Object__first__S, "ti_sdo_ipc_gates_GateAAMonitor_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateAAMonitor_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_Object__next__S, "ti_sdo_ipc_gates_GateAAMonitor_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateAAMonitor_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_Params__init__S, "ti_sdo_ipc_gates_GateAAMonitor_Params__init__S")
__extern xdc_Void ti_sdo_ipc_gates_GateAAMonitor_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* query__E */
#define ti_sdo_ipc_gates_GateAAMonitor_query ti_sdo_ipc_gates_GateAAMonitor_query__E
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_query__E, "ti_sdo_ipc_gates_GateAAMonitor_query")
__extern xdc_Bool ti_sdo_ipc_gates_GateAAMonitor_query__E( xdc_Int qual );

/* enter__E */
#define ti_sdo_ipc_gates_GateAAMonitor_enter ti_sdo_ipc_gates_GateAAMonitor_enter__E
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_enter__E, "ti_sdo_ipc_gates_GateAAMonitor_enter")
__extern xdc_IArg ti_sdo_ipc_gates_GateAAMonitor_enter__E( ti_sdo_ipc_gates_GateAAMonitor_Handle __inst );

/* leave__E */
#define ti_sdo_ipc_gates_GateAAMonitor_leave ti_sdo_ipc_gates_GateAAMonitor_leave__E
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_leave__E, "ti_sdo_ipc_gates_GateAAMonitor_leave")
__extern xdc_Void ti_sdo_ipc_gates_GateAAMonitor_leave__E( ti_sdo_ipc_gates_GateAAMonitor_Handle __inst, xdc_IArg key );

/* getReservedMask__E */
#define ti_sdo_ipc_gates_GateAAMonitor_getReservedMask ti_sdo_ipc_gates_GateAAMonitor_getReservedMask__E
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_getReservedMask__E, "ti_sdo_ipc_gates_GateAAMonitor_getReservedMask")
__extern xdc_Bits32 *ti_sdo_ipc_gates_GateAAMonitor_getReservedMask__E( void );

/* sharedMemReq__E */
#define ti_sdo_ipc_gates_GateAAMonitor_sharedMemReq ti_sdo_ipc_gates_GateAAMonitor_sharedMemReq__E
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_sharedMemReq__E, "ti_sdo_ipc_gates_GateAAMonitor_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_gates_GateAAMonitor_sharedMemReq__E( const ti_sdo_ipc_interfaces_IGateMPSupport_Params *params );

/* getLock__I */
#define ti_sdo_ipc_gates_GateAAMonitor_getLock ti_sdo_ipc_gates_GateAAMonitor_getLock__I
xdc__CODESECT(ti_sdo_ipc_gates_GateAAMonitor_getLock__I, "ti_sdo_ipc_gates_GateAAMonitor_getLock")
__extern xdc_UInt ti_sdo_ipc_gates_GateAAMonitor_getLock__I( xdc_Ptr sharedAddr );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Module ti_sdo_ipc_gates_GateAAMonitor_Module_upCast( void )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Module)&ti_sdo_ipc_gates_GateAAMonitor_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GateAAMonitor_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateAAMonitor_Module_upCast

/* Handle_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Handle ti_sdo_ipc_gates_GateAAMonitor_Handle_upCast( ti_sdo_ipc_gates_GateAAMonitor_Handle i )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GateAAMonitor_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateAAMonitor_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_gates_GateAAMonitor_Handle ti_sdo_ipc_gates_GateAAMonitor_Handle_downCast( ti_sdo_ipc_interfaces_IGateMPSupport_Handle i )
{
    ti_sdo_ipc_interfaces_IGateMPSupport_Handle i2 = (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_gates_GateAAMonitor_Module__FXNS__C ? (ti_sdo_ipc_gates_GateAAMonitor_Handle)i : (ti_sdo_ipc_gates_GateAAMonitor_Handle)0;
}

/* Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GateAAMonitor_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateAAMonitor_Handle_downCast

/* Module_upCast2 */
static inline xdc_runtime_IGateProvider_Module ti_sdo_ipc_gates_GateAAMonitor_Module_upCast2( void )
{
    return (xdc_runtime_IGateProvider_Module)&ti_sdo_ipc_gates_GateAAMonitor_Module__FXNS__C;
}

/* Module_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GateAAMonitor_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateAAMonitor_Module_upCast2

/* Handle_upCast2 */
static inline xdc_runtime_IGateProvider_Handle ti_sdo_ipc_gates_GateAAMonitor_Handle_upCast2( ti_sdo_ipc_gates_GateAAMonitor_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GateAAMonitor_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateAAMonitor_Handle_upCast2

/* Handle_downCast2 */
static inline ti_sdo_ipc_gates_GateAAMonitor_Handle ti_sdo_ipc_gates_GateAAMonitor_Handle_downCast2( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_gates_GateAAMonitor_Module__FXNS__C ? (ti_sdo_ipc_gates_GateAAMonitor_Handle)i : (ti_sdo_ipc_gates_GateAAMonitor_Handle)0;
}

/* Handle_from_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GateAAMonitor_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateAAMonitor_Handle_downCast2


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_gates_GateAAMonitor_Module_startupDone() ti_sdo_ipc_gates_GateAAMonitor_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_gates_GateAAMonitor_Object_heap() ti_sdo_ipc_gates_GateAAMonitor_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_gates_GateAAMonitor_Module_heap() ti_sdo_ipc_gates_GateAAMonitor_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_gates_GateAAMonitor_Module__id ti_sdo_ipc_gates_GateAAMonitor_Module_id( void ) 
{
    return ti_sdo_ipc_gates_GateAAMonitor_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_gates_GateAAMonitor_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_gates_GateAAMonitor_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_gates_GateAAMonitor_Module_getMask( void ) 
{
    return ti_sdo_ipc_gates_GateAAMonitor_Module__diagsMask__C != NULL ? *ti_sdo_ipc_gates_GateAAMonitor_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_gates_GateAAMonitor_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_gates_GateAAMonitor_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_gates_GateAAMonitor_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_gates_GateAAMonitor_Params_init( ti_sdo_ipc_gates_GateAAMonitor_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_gates_GateAAMonitor_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_gates_GateAAMonitor_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_gates_GateAAMonitor_Params_copy(ti_sdo_ipc_gates_GateAAMonitor_Params *dst, const ti_sdo_ipc_gates_GateAAMonitor_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_gates_GateAAMonitor_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_gates_GateAAMonitor_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_gates_GateAAMonitor_Object_count() ti_sdo_ipc_gates_GateAAMonitor_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_gates_GateAAMonitor_Object_sizeof() ti_sdo_ipc_gates_GateAAMonitor_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_gates_GateAAMonitor_Handle ti_sdo_ipc_gates_GateAAMonitor_Object_get(ti_sdo_ipc_gates_GateAAMonitor_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_gates_GateAAMonitor_Handle)ti_sdo_ipc_gates_GateAAMonitor_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_gates_GateAAMonitor_Handle ti_sdo_ipc_gates_GateAAMonitor_Object_first( void )
{
    return (ti_sdo_ipc_gates_GateAAMonitor_Handle)ti_sdo_ipc_gates_GateAAMonitor_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_gates_GateAAMonitor_Handle ti_sdo_ipc_gates_GateAAMonitor_Object_next( ti_sdo_ipc_gates_GateAAMonitor_Object *obj )
{
    return (ti_sdo_ipc_gates_GateAAMonitor_Handle)ti_sdo_ipc_gates_GateAAMonitor_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_gates_GateAAMonitor_Handle_label( ti_sdo_ipc_gates_GateAAMonitor_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_gates_GateAAMonitor_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_gates_GateAAMonitor_Handle_name( ti_sdo_ipc_gates_GateAAMonitor_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_gates_GateAAMonitor_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_gates_GateAAMonitor_Handle ti_sdo_ipc_gates_GateAAMonitor_handle( ti_sdo_ipc_gates_GateAAMonitor_Struct *str )
{
    return (ti_sdo_ipc_gates_GateAAMonitor_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_gates_GateAAMonitor_Struct *ti_sdo_ipc_gates_GateAAMonitor_struct( ti_sdo_ipc_gates_GateAAMonitor_Handle inst )
{
    return (ti_sdo_ipc_gates_GateAAMonitor_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_gates_GateAAMonitor__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_gates_GateAAMonitor__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_gates_GateAAMonitor__internalaccess))

#ifndef ti_sdo_ipc_gates_GateAAMonitor__include_state
#define ti_sdo_ipc_gates_GateAAMonitor__include_state

/* Object */
struct ti_sdo_ipc_gates_GateAAMonitor_Object {
    const ti_sdo_ipc_gates_GateAAMonitor_Fxns__ *__fxns;
    volatile xdc_UInt32 *sharedAddr;
    xdc_UInt nested;
    xdc_runtime_IGateProvider_Handle localGate;
};

#endif /* ti_sdo_ipc_gates_GateAAMonitor__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_gates_GateAAMonitor__nolocalnames)

#ifndef ti_sdo_ipc_gates_GateAAMonitor__localnames__done
#define ti_sdo_ipc_gates_GateAAMonitor__localnames__done

/* module prefix */
#define GateAAMonitor_Instance ti_sdo_ipc_gates_GateAAMonitor_Instance
#define GateAAMonitor_Handle ti_sdo_ipc_gates_GateAAMonitor_Handle
#define GateAAMonitor_Module ti_sdo_ipc_gates_GateAAMonitor_Module
#define GateAAMonitor_Object ti_sdo_ipc_gates_GateAAMonitor_Object
#define GateAAMonitor_Struct ti_sdo_ipc_gates_GateAAMonitor_Struct
#define GateAAMonitor_Q_BLOCKING ti_sdo_ipc_gates_GateAAMonitor_Q_BLOCKING
#define GateAAMonitor_Q_PREEMPTING ti_sdo_ipc_gates_GateAAMonitor_Q_PREEMPTING
#define GateAAMonitor_CACHELINE_SIZE ti_sdo_ipc_gates_GateAAMonitor_CACHELINE_SIZE
#define GateAAMonitor_SL2_RANGE_BASE ti_sdo_ipc_gates_GateAAMonitor_SL2_RANGE_BASE
#define GateAAMonitor_SL2_RANGE_MAX ti_sdo_ipc_gates_GateAAMonitor_SL2_RANGE_MAX
#define GateAAMonitor_Instance_State ti_sdo_ipc_gates_GateAAMonitor_Instance_State
#define GateAAMonitor_A_invSharedAddr ti_sdo_ipc_gates_GateAAMonitor_A_invSharedAddr
#define GateAAMonitor_numInstances ti_sdo_ipc_gates_GateAAMonitor_numInstances
#define GateAAMonitor_Params ti_sdo_ipc_gates_GateAAMonitor_Params
#define GateAAMonitor_query ti_sdo_ipc_gates_GateAAMonitor_query
#define GateAAMonitor_enter ti_sdo_ipc_gates_GateAAMonitor_enter
#define GateAAMonitor_leave ti_sdo_ipc_gates_GateAAMonitor_leave
#define GateAAMonitor_getReservedMask ti_sdo_ipc_gates_GateAAMonitor_getReservedMask
#define GateAAMonitor_sharedMemReq ti_sdo_ipc_gates_GateAAMonitor_sharedMemReq
#define GateAAMonitor_Module_name ti_sdo_ipc_gates_GateAAMonitor_Module_name
#define GateAAMonitor_Module_id ti_sdo_ipc_gates_GateAAMonitor_Module_id
#define GateAAMonitor_Module_startup ti_sdo_ipc_gates_GateAAMonitor_Module_startup
#define GateAAMonitor_Module_startupDone ti_sdo_ipc_gates_GateAAMonitor_Module_startupDone
#define GateAAMonitor_Module_hasMask ti_sdo_ipc_gates_GateAAMonitor_Module_hasMask
#define GateAAMonitor_Module_getMask ti_sdo_ipc_gates_GateAAMonitor_Module_getMask
#define GateAAMonitor_Module_setMask ti_sdo_ipc_gates_GateAAMonitor_Module_setMask
#define GateAAMonitor_Object_heap ti_sdo_ipc_gates_GateAAMonitor_Object_heap
#define GateAAMonitor_Module_heap ti_sdo_ipc_gates_GateAAMonitor_Module_heap
#define GateAAMonitor_construct ti_sdo_ipc_gates_GateAAMonitor_construct
#define GateAAMonitor_create ti_sdo_ipc_gates_GateAAMonitor_create
#define GateAAMonitor_handle ti_sdo_ipc_gates_GateAAMonitor_handle
#define GateAAMonitor_struct ti_sdo_ipc_gates_GateAAMonitor_struct
#define GateAAMonitor_Handle_label ti_sdo_ipc_gates_GateAAMonitor_Handle_label
#define GateAAMonitor_Handle_name ti_sdo_ipc_gates_GateAAMonitor_Handle_name
#define GateAAMonitor_Instance_init ti_sdo_ipc_gates_GateAAMonitor_Instance_init
#define GateAAMonitor_Object_count ti_sdo_ipc_gates_GateAAMonitor_Object_count
#define GateAAMonitor_Object_get ti_sdo_ipc_gates_GateAAMonitor_Object_get
#define GateAAMonitor_Object_first ti_sdo_ipc_gates_GateAAMonitor_Object_first
#define GateAAMonitor_Object_next ti_sdo_ipc_gates_GateAAMonitor_Object_next
#define GateAAMonitor_Object_sizeof ti_sdo_ipc_gates_GateAAMonitor_Object_sizeof
#define GateAAMonitor_Params_copy ti_sdo_ipc_gates_GateAAMonitor_Params_copy
#define GateAAMonitor_Params_init ti_sdo_ipc_gates_GateAAMonitor_Params_init
#define GateAAMonitor_delete ti_sdo_ipc_gates_GateAAMonitor_delete
#define GateAAMonitor_destruct ti_sdo_ipc_gates_GateAAMonitor_destruct
#define GateAAMonitor_Module_upCast ti_sdo_ipc_gates_GateAAMonitor_Module_upCast
#define GateAAMonitor_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateAAMonitor_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateAAMonitor_Handle_upCast ti_sdo_ipc_gates_GateAAMonitor_Handle_upCast
#define GateAAMonitor_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateAAMonitor_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateAAMonitor_Handle_downCast ti_sdo_ipc_gates_GateAAMonitor_Handle_downCast
#define GateAAMonitor_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateAAMonitor_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateAAMonitor_Module_upCast2 ti_sdo_ipc_gates_GateAAMonitor_Module_upCast2
#define GateAAMonitor_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateAAMonitor_Module_to_xdc_runtime_IGateProvider
#define GateAAMonitor_Handle_upCast2 ti_sdo_ipc_gates_GateAAMonitor_Handle_upCast2
#define GateAAMonitor_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateAAMonitor_Handle_to_xdc_runtime_IGateProvider
#define GateAAMonitor_Handle_downCast2 ti_sdo_ipc_gates_GateAAMonitor_Handle_downCast2
#define GateAAMonitor_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateAAMonitor_Handle_from_xdc_runtime_IGateProvider

#endif /* ti_sdo_ipc_gates_GateAAMonitor__localnames__done */
#endif
