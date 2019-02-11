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

#ifndef ti_sdo_ipc_gates_GatePeterson__include
#define ti_sdo_ipc_gates_GatePeterson__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_gates_GatePeterson__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_gates_GatePeterson___VERS 160


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
#include <ti/sdo/utils/MultiProc.h>
#include <ti/sdo/ipc/Ipc.h>
#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */
#define ti_sdo_ipc_gates_GatePeterson_Q_BLOCKING (1)

/* Q_PREEMPTING */
#define ti_sdo_ipc_gates_GatePeterson_Q_PREEMPTING (2)


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_gates_GatePeterson_Args__create {
    xdc_runtime_IGateProvider_Handle localGate;
} ti_sdo_ipc_gates_GatePeterson_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* FREE */
#define ti_sdo_ipc_gates_GatePeterson_FREE (0)

/* BUSY */
#define ti_sdo_ipc_gates_GatePeterson_BUSY (1)

/* Attrs */
struct ti_sdo_ipc_gates_GatePeterson_Attrs {
    xdc_Bits16 creatorProcId;
    xdc_Bits16 openerProcId;
};

/* Instance_State */
typedef volatile xdc_Bits16 *__T1_ti_sdo_ipc_gates_GatePeterson_Instance_State__flag;
typedef volatile xdc_Bits16 *__ARRAY1_ti_sdo_ipc_gates_GatePeterson_Instance_State__flag[2];
typedef __ARRAY1_ti_sdo_ipc_gates_GatePeterson_Instance_State__flag __TA_ti_sdo_ipc_gates_GatePeterson_Instance_State__flag;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_gates_GatePeterson_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__diagsEnabled ti_sdo_ipc_gates_GatePeterson_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_gates_GatePeterson_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__diagsIncluded ti_sdo_ipc_gates_GatePeterson_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_gates_GatePeterson_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__diagsMask ti_sdo_ipc_gates_GatePeterson_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GatePeterson_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__gateObj ti_sdo_ipc_gates_GatePeterson_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GatePeterson_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__gatePrms ti_sdo_ipc_gates_GatePeterson_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_gates_GatePeterson_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__id ti_sdo_ipc_gates_GatePeterson_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerDefined ti_sdo_ipc_gates_GatePeterson_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerObj ti_sdo_ipc_gates_GatePeterson_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn0 ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn1 ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn2 ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn4 ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn8 ti_sdo_ipc_gates_GatePeterson_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_gates_GatePeterson_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Module__startupDoneFxn ti_sdo_ipc_gates_GatePeterson_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_gates_GatePeterson_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Object__count ti_sdo_ipc_gates_GatePeterson_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_gates_GatePeterson_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Object__heap ti_sdo_ipc_gates_GatePeterson_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_gates_GatePeterson_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Object__sizeof ti_sdo_ipc_gates_GatePeterson_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GatePeterson_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_Object__table ti_sdo_ipc_gates_GatePeterson_Object__table__C;

/* E_gateRemotelyOpened */
#define ti_sdo_ipc_gates_GatePeterson_E_gateRemotelyOpened (ti_sdo_ipc_gates_GatePeterson_E_gateRemotelyOpened__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_gates_GatePeterson_E_gateRemotelyOpened;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_E_gateRemotelyOpened ti_sdo_ipc_gates_GatePeterson_E_gateRemotelyOpened__C;

/* numInstances */
#ifdef ti_sdo_ipc_gates_GatePeterson_numInstances__D
#define ti_sdo_ipc_gates_GatePeterson_numInstances (ti_sdo_ipc_gates_GatePeterson_numInstances__D)
#else
#define ti_sdo_ipc_gates_GatePeterson_numInstances (ti_sdo_ipc_gates_GatePeterson_numInstances__C)
typedef xdc_UInt CT__ti_sdo_ipc_gates_GatePeterson_numInstances;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GatePeterson_numInstances ti_sdo_ipc_gates_GatePeterson_numInstances__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_gates_GatePeterson_Params {
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
struct ti_sdo_ipc_gates_GatePeterson_Struct {
    const ti_sdo_ipc_gates_GatePeterson_Fxns__ *__fxns;
    ti_sdo_ipc_gates_GatePeterson_Attrs *__f0;
    __TA_ti_sdo_ipc_gates_GatePeterson_Instance_State__flag __f1;
    volatile xdc_Bits16 *__f2;
    xdc_UInt16 __f3;
    xdc_UInt16 __f4;
    xdc_UInt __f5;
    xdc_runtime_IGateProvider_Handle __f6;
    ti_sdo_ipc_Ipc_ObjType __f7;
    xdc_SizeT __f8;
    xdc_Bool __f9;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_gates_GatePeterson_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(ti_sdo_ipc_gates_GatePeterson_Handle);
    xdc_Void (*leave)(ti_sdo_ipc_gates_GatePeterson_Handle, xdc_IArg);
    xdc_Bits32 *(*getReservedMask)(void);
    xdc_SizeT (*sharedMemReq)(const ti_sdo_ipc_interfaces_IGateMPSupport_Params*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_gates_GatePeterson_Fxns__ ti_sdo_ipc_gates_GatePeterson_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_gates_GatePeterson_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_Instance_init__E, "ti_sdo_ipc_gates_GatePeterson_Instance_init")
__extern xdc_Int ti_sdo_ipc_gates_GatePeterson_Instance_init__E(ti_sdo_ipc_gates_GatePeterson_Object *, xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GatePeterson_Params *, xdc_runtime_Error_Block *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_Instance_finalize__E, "ti_sdo_ipc_gates_GatePeterson_Instance_finalize")
__extern void ti_sdo_ipc_gates_GatePeterson_Instance_finalize__E( ti_sdo_ipc_gates_GatePeterson_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_Handle__label__S, "ti_sdo_ipc_gates_GatePeterson_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_gates_GatePeterson_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_Module__startupDone__S, "ti_sdo_ipc_gates_GatePeterson_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_gates_GatePeterson_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_Object__create__S, "ti_sdo_ipc_gates_GatePeterson_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GatePeterson_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_create, "ti_sdo_ipc_gates_GatePeterson_create")
__extern ti_sdo_ipc_gates_GatePeterson_Handle ti_sdo_ipc_gates_GatePeterson_create( xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GatePeterson_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_construct, "ti_sdo_ipc_gates_GatePeterson_construct")
__extern void ti_sdo_ipc_gates_GatePeterson_construct( ti_sdo_ipc_gates_GatePeterson_Struct *__obj, xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GatePeterson_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_Object__delete__S, "ti_sdo_ipc_gates_GatePeterson_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_gates_GatePeterson_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_delete, "ti_sdo_ipc_gates_GatePeterson_delete")
__extern void ti_sdo_ipc_gates_GatePeterson_delete(ti_sdo_ipc_gates_GatePeterson_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_Object__destruct__S, "ti_sdo_ipc_gates_GatePeterson_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_gates_GatePeterson_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_destruct, "ti_sdo_ipc_gates_GatePeterson_destruct")
__extern void ti_sdo_ipc_gates_GatePeterson_destruct(ti_sdo_ipc_gates_GatePeterson_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_Object__get__S, "ti_sdo_ipc_gates_GatePeterson_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GatePeterson_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_Object__first__S, "ti_sdo_ipc_gates_GatePeterson_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GatePeterson_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_Object__next__S, "ti_sdo_ipc_gates_GatePeterson_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GatePeterson_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_Params__init__S, "ti_sdo_ipc_gates_GatePeterson_Params__init__S")
__extern xdc_Void ti_sdo_ipc_gates_GatePeterson_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* query__E */
#define ti_sdo_ipc_gates_GatePeterson_query ti_sdo_ipc_gates_GatePeterson_query__E
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_query__E, "ti_sdo_ipc_gates_GatePeterson_query")
__extern xdc_Bool ti_sdo_ipc_gates_GatePeterson_query__E( xdc_Int qual );

/* getReservedMask__E */
#define ti_sdo_ipc_gates_GatePeterson_getReservedMask ti_sdo_ipc_gates_GatePeterson_getReservedMask__E
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_getReservedMask__E, "ti_sdo_ipc_gates_GatePeterson_getReservedMask")
__extern xdc_Bits32 *ti_sdo_ipc_gates_GatePeterson_getReservedMask__E( void );

/* sharedMemReq__E */
#define ti_sdo_ipc_gates_GatePeterson_sharedMemReq ti_sdo_ipc_gates_GatePeterson_sharedMemReq__E
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_sharedMemReq__E, "ti_sdo_ipc_gates_GatePeterson_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_gates_GatePeterson_sharedMemReq__E( const ti_sdo_ipc_interfaces_IGateMPSupport_Params *params );

/* enter__E */
#define ti_sdo_ipc_gates_GatePeterson_enter ti_sdo_ipc_gates_GatePeterson_enter__E
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_enter__E, "ti_sdo_ipc_gates_GatePeterson_enter")
__extern xdc_IArg ti_sdo_ipc_gates_GatePeterson_enter__E( ti_sdo_ipc_gates_GatePeterson_Handle __inst );

/* leave__E */
#define ti_sdo_ipc_gates_GatePeterson_leave ti_sdo_ipc_gates_GatePeterson_leave__E
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_leave__E, "ti_sdo_ipc_gates_GatePeterson_leave")
__extern xdc_Void ti_sdo_ipc_gates_GatePeterson_leave__E( ti_sdo_ipc_gates_GatePeterson_Handle __inst, xdc_IArg key );

/* postInit__I */
#define ti_sdo_ipc_gates_GatePeterson_postInit ti_sdo_ipc_gates_GatePeterson_postInit__I
xdc__CODESECT(ti_sdo_ipc_gates_GatePeterson_postInit__I, "ti_sdo_ipc_gates_GatePeterson_postInit")
__extern xdc_Void ti_sdo_ipc_gates_GatePeterson_postInit__I( ti_sdo_ipc_gates_GatePeterson_Object *obj );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Module ti_sdo_ipc_gates_GatePeterson_Module_upCast( void )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Module)&ti_sdo_ipc_gates_GatePeterson_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GatePeterson_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GatePeterson_Module_upCast

/* Handle_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Handle ti_sdo_ipc_gates_GatePeterson_Handle_upCast( ti_sdo_ipc_gates_GatePeterson_Handle i )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GatePeterson_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GatePeterson_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_gates_GatePeterson_Handle ti_sdo_ipc_gates_GatePeterson_Handle_downCast( ti_sdo_ipc_interfaces_IGateMPSupport_Handle i )
{
    ti_sdo_ipc_interfaces_IGateMPSupport_Handle i2 = (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_gates_GatePeterson_Module__FXNS__C ? (ti_sdo_ipc_gates_GatePeterson_Handle)i : (ti_sdo_ipc_gates_GatePeterson_Handle)0;
}

/* Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GatePeterson_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GatePeterson_Handle_downCast

/* Module_upCast2 */
static inline xdc_runtime_IGateProvider_Module ti_sdo_ipc_gates_GatePeterson_Module_upCast2( void )
{
    return (xdc_runtime_IGateProvider_Module)&ti_sdo_ipc_gates_GatePeterson_Module__FXNS__C;
}

/* Module_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GatePeterson_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GatePeterson_Module_upCast2

/* Handle_upCast2 */
static inline xdc_runtime_IGateProvider_Handle ti_sdo_ipc_gates_GatePeterson_Handle_upCast2( ti_sdo_ipc_gates_GatePeterson_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GatePeterson_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GatePeterson_Handle_upCast2

/* Handle_downCast2 */
static inline ti_sdo_ipc_gates_GatePeterson_Handle ti_sdo_ipc_gates_GatePeterson_Handle_downCast2( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_gates_GatePeterson_Module__FXNS__C ? (ti_sdo_ipc_gates_GatePeterson_Handle)i : (ti_sdo_ipc_gates_GatePeterson_Handle)0;
}

/* Handle_from_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GatePeterson_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GatePeterson_Handle_downCast2


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_gates_GatePeterson_Module_startupDone() ti_sdo_ipc_gates_GatePeterson_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_gates_GatePeterson_Object_heap() ti_sdo_ipc_gates_GatePeterson_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_gates_GatePeterson_Module_heap() ti_sdo_ipc_gates_GatePeterson_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_gates_GatePeterson_Module__id ti_sdo_ipc_gates_GatePeterson_Module_id( void ) 
{
    return ti_sdo_ipc_gates_GatePeterson_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_gates_GatePeterson_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_gates_GatePeterson_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_gates_GatePeterson_Module_getMask( void ) 
{
    return ti_sdo_ipc_gates_GatePeterson_Module__diagsMask__C != NULL ? *ti_sdo_ipc_gates_GatePeterson_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_gates_GatePeterson_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_gates_GatePeterson_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_gates_GatePeterson_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_gates_GatePeterson_Params_init( ti_sdo_ipc_gates_GatePeterson_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_gates_GatePeterson_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_gates_GatePeterson_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_gates_GatePeterson_Params_copy(ti_sdo_ipc_gates_GatePeterson_Params *dst, const ti_sdo_ipc_gates_GatePeterson_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_gates_GatePeterson_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_gates_GatePeterson_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_gates_GatePeterson_Object_count() ti_sdo_ipc_gates_GatePeterson_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_gates_GatePeterson_Object_sizeof() ti_sdo_ipc_gates_GatePeterson_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_gates_GatePeterson_Handle ti_sdo_ipc_gates_GatePeterson_Object_get(ti_sdo_ipc_gates_GatePeterson_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_gates_GatePeterson_Handle)ti_sdo_ipc_gates_GatePeterson_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_gates_GatePeterson_Handle ti_sdo_ipc_gates_GatePeterson_Object_first( void )
{
    return (ti_sdo_ipc_gates_GatePeterson_Handle)ti_sdo_ipc_gates_GatePeterson_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_gates_GatePeterson_Handle ti_sdo_ipc_gates_GatePeterson_Object_next( ti_sdo_ipc_gates_GatePeterson_Object *obj )
{
    return (ti_sdo_ipc_gates_GatePeterson_Handle)ti_sdo_ipc_gates_GatePeterson_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_gates_GatePeterson_Handle_label( ti_sdo_ipc_gates_GatePeterson_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_gates_GatePeterson_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_gates_GatePeterson_Handle_name( ti_sdo_ipc_gates_GatePeterson_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_gates_GatePeterson_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_gates_GatePeterson_Handle ti_sdo_ipc_gates_GatePeterson_handle( ti_sdo_ipc_gates_GatePeterson_Struct *str )
{
    return (ti_sdo_ipc_gates_GatePeterson_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_gates_GatePeterson_Struct *ti_sdo_ipc_gates_GatePeterson_struct( ti_sdo_ipc_gates_GatePeterson_Handle inst )
{
    return (ti_sdo_ipc_gates_GatePeterson_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_gates_GatePeterson__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_gates_GatePeterson__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_gates_GatePeterson__internalaccess))

#ifndef ti_sdo_ipc_gates_GatePeterson__include_state
#define ti_sdo_ipc_gates_GatePeterson__include_state

/* Object */
struct ti_sdo_ipc_gates_GatePeterson_Object {
    const ti_sdo_ipc_gates_GatePeterson_Fxns__ *__fxns;
    ti_sdo_ipc_gates_GatePeterson_Attrs *attrs;
    __TA_ti_sdo_ipc_gates_GatePeterson_Instance_State__flag flag;
    volatile xdc_Bits16 *turn;
    xdc_UInt16 selfId;
    xdc_UInt16 otherId;
    xdc_UInt nested;
    xdc_runtime_IGateProvider_Handle localGate;
    ti_sdo_ipc_Ipc_ObjType objType;
    xdc_SizeT cacheLineSize;
    xdc_Bool cacheEnabled;
};

#endif /* ti_sdo_ipc_gates_GatePeterson__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_gates_GatePeterson__nolocalnames)

#ifndef ti_sdo_ipc_gates_GatePeterson__localnames__done
#define ti_sdo_ipc_gates_GatePeterson__localnames__done

/* module prefix */
#define GatePeterson_Instance ti_sdo_ipc_gates_GatePeterson_Instance
#define GatePeterson_Handle ti_sdo_ipc_gates_GatePeterson_Handle
#define GatePeterson_Module ti_sdo_ipc_gates_GatePeterson_Module
#define GatePeterson_Object ti_sdo_ipc_gates_GatePeterson_Object
#define GatePeterson_Struct ti_sdo_ipc_gates_GatePeterson_Struct
#define GatePeterson_Q_BLOCKING ti_sdo_ipc_gates_GatePeterson_Q_BLOCKING
#define GatePeterson_Q_PREEMPTING ti_sdo_ipc_gates_GatePeterson_Q_PREEMPTING
#define GatePeterson_FREE ti_sdo_ipc_gates_GatePeterson_FREE
#define GatePeterson_BUSY ti_sdo_ipc_gates_GatePeterson_BUSY
#define GatePeterson_Attrs ti_sdo_ipc_gates_GatePeterson_Attrs
#define GatePeterson_Instance_State ti_sdo_ipc_gates_GatePeterson_Instance_State
#define GatePeterson_E_gateRemotelyOpened ti_sdo_ipc_gates_GatePeterson_E_gateRemotelyOpened
#define GatePeterson_numInstances ti_sdo_ipc_gates_GatePeterson_numInstances
#define GatePeterson_Params ti_sdo_ipc_gates_GatePeterson_Params
#define GatePeterson_query ti_sdo_ipc_gates_GatePeterson_query
#define GatePeterson_getReservedMask ti_sdo_ipc_gates_GatePeterson_getReservedMask
#define GatePeterson_sharedMemReq ti_sdo_ipc_gates_GatePeterson_sharedMemReq
#define GatePeterson_enter ti_sdo_ipc_gates_GatePeterson_enter
#define GatePeterson_leave ti_sdo_ipc_gates_GatePeterson_leave
#define GatePeterson_Module_name ti_sdo_ipc_gates_GatePeterson_Module_name
#define GatePeterson_Module_id ti_sdo_ipc_gates_GatePeterson_Module_id
#define GatePeterson_Module_startup ti_sdo_ipc_gates_GatePeterson_Module_startup
#define GatePeterson_Module_startupDone ti_sdo_ipc_gates_GatePeterson_Module_startupDone
#define GatePeterson_Module_hasMask ti_sdo_ipc_gates_GatePeterson_Module_hasMask
#define GatePeterson_Module_getMask ti_sdo_ipc_gates_GatePeterson_Module_getMask
#define GatePeterson_Module_setMask ti_sdo_ipc_gates_GatePeterson_Module_setMask
#define GatePeterson_Object_heap ti_sdo_ipc_gates_GatePeterson_Object_heap
#define GatePeterson_Module_heap ti_sdo_ipc_gates_GatePeterson_Module_heap
#define GatePeterson_construct ti_sdo_ipc_gates_GatePeterson_construct
#define GatePeterson_create ti_sdo_ipc_gates_GatePeterson_create
#define GatePeterson_handle ti_sdo_ipc_gates_GatePeterson_handle
#define GatePeterson_struct ti_sdo_ipc_gates_GatePeterson_struct
#define GatePeterson_Handle_label ti_sdo_ipc_gates_GatePeterson_Handle_label
#define GatePeterson_Handle_name ti_sdo_ipc_gates_GatePeterson_Handle_name
#define GatePeterson_Instance_init ti_sdo_ipc_gates_GatePeterson_Instance_init
#define GatePeterson_Object_count ti_sdo_ipc_gates_GatePeterson_Object_count
#define GatePeterson_Object_get ti_sdo_ipc_gates_GatePeterson_Object_get
#define GatePeterson_Object_first ti_sdo_ipc_gates_GatePeterson_Object_first
#define GatePeterson_Object_next ti_sdo_ipc_gates_GatePeterson_Object_next
#define GatePeterson_Object_sizeof ti_sdo_ipc_gates_GatePeterson_Object_sizeof
#define GatePeterson_Params_copy ti_sdo_ipc_gates_GatePeterson_Params_copy
#define GatePeterson_Params_init ti_sdo_ipc_gates_GatePeterson_Params_init
#define GatePeterson_Instance_finalize ti_sdo_ipc_gates_GatePeterson_Instance_finalize
#define GatePeterson_delete ti_sdo_ipc_gates_GatePeterson_delete
#define GatePeterson_destruct ti_sdo_ipc_gates_GatePeterson_destruct
#define GatePeterson_Module_upCast ti_sdo_ipc_gates_GatePeterson_Module_upCast
#define GatePeterson_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GatePeterson_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GatePeterson_Handle_upCast ti_sdo_ipc_gates_GatePeterson_Handle_upCast
#define GatePeterson_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GatePeterson_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GatePeterson_Handle_downCast ti_sdo_ipc_gates_GatePeterson_Handle_downCast
#define GatePeterson_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GatePeterson_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport
#define GatePeterson_Module_upCast2 ti_sdo_ipc_gates_GatePeterson_Module_upCast2
#define GatePeterson_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GatePeterson_Module_to_xdc_runtime_IGateProvider
#define GatePeterson_Handle_upCast2 ti_sdo_ipc_gates_GatePeterson_Handle_upCast2
#define GatePeterson_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GatePeterson_Handle_to_xdc_runtime_IGateProvider
#define GatePeterson_Handle_downCast2 ti_sdo_ipc_gates_GatePeterson_Handle_downCast2
#define GatePeterson_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GatePeterson_Handle_from_xdc_runtime_IGateProvider

#endif /* ti_sdo_ipc_gates_GatePeterson__localnames__done */
#endif
