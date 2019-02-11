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

#ifndef ti_sdo_ipc_gates_GateHWSem__include
#define ti_sdo_ipc_gates_GateHWSem__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_gates_GateHWSem__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_gates_GateHWSem___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/gates/package/package.defs.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IGateProvider.h>
#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */
#define ti_sdo_ipc_gates_GateHWSem_Q_BLOCKING (1)

/* Q_PREEMPTING */
#define ti_sdo_ipc_gates_GateHWSem_Q_PREEMPTING (2)


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_gates_GateHWSem_Args__create {
    xdc_runtime_IGateProvider_Handle localGate;
} ti_sdo_ipc_gates_GateHWSem_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_gates_GateHWSem_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__diagsEnabled ti_sdo_ipc_gates_GateHWSem_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_gates_GateHWSem_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__diagsIncluded ti_sdo_ipc_gates_GateHWSem_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_gates_GateHWSem_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__diagsMask ti_sdo_ipc_gates_GateHWSem_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateHWSem_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__gateObj ti_sdo_ipc_gates_GateHWSem_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateHWSem_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__gatePrms ti_sdo_ipc_gates_GateHWSem_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_gates_GateHWSem_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__id ti_sdo_ipc_gates_GateHWSem_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerDefined ti_sdo_ipc_gates_GateHWSem_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerObj ti_sdo_ipc_gates_GateHWSem_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn0 ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn1 ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn2 ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn4 ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn8 ti_sdo_ipc_gates_GateHWSem_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_gates_GateHWSem_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Module__startupDoneFxn ti_sdo_ipc_gates_GateHWSem_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_gates_GateHWSem_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Object__count ti_sdo_ipc_gates_GateHWSem_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_gates_GateHWSem_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Object__heap ti_sdo_ipc_gates_GateHWSem_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_gates_GateHWSem_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Object__sizeof ti_sdo_ipc_gates_GateHWSem_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateHWSem_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_Object__table ti_sdo_ipc_gates_GateHWSem_Object__table__C;

/* A_invSemNum */
#define ti_sdo_ipc_gates_GateHWSem_A_invSemNum (ti_sdo_ipc_gates_GateHWSem_A_invSemNum__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_gates_GateHWSem_A_invSemNum;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_A_invSemNum ti_sdo_ipc_gates_GateHWSem_A_invSemNum__C;

/* baseAddr */
#define ti_sdo_ipc_gates_GateHWSem_baseAddr (ti_sdo_ipc_gates_GateHWSem_baseAddr__C)
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateHWSem_baseAddr;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_baseAddr ti_sdo_ipc_gates_GateHWSem_baseAddr__C;

/* queryAddr */
#define ti_sdo_ipc_gates_GateHWSem_queryAddr (ti_sdo_ipc_gates_GateHWSem_queryAddr__C)
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateHWSem_queryAddr;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_queryAddr ti_sdo_ipc_gates_GateHWSem_queryAddr__C;

/* numSems */
#ifdef ti_sdo_ipc_gates_GateHWSem_numSems__D
#define ti_sdo_ipc_gates_GateHWSem_numSems (ti_sdo_ipc_gates_GateHWSem_numSems__D)
#else
#define ti_sdo_ipc_gates_GateHWSem_numSems (ti_sdo_ipc_gates_GateHWSem_numSems__C)
typedef xdc_UInt CT__ti_sdo_ipc_gates_GateHWSem_numSems;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_numSems ti_sdo_ipc_gates_GateHWSem_numSems__C;
#endif

/* reservedMaskArr */
#define ti_sdo_ipc_gates_GateHWSem_reservedMaskArr (ti_sdo_ipc_gates_GateHWSem_reservedMaskArr__C)
typedef xdc_Bits32 __T1_ti_sdo_ipc_gates_GateHWSem_reservedMaskArr;
typedef xdc_Bits32 *__ARRAY1_ti_sdo_ipc_gates_GateHWSem_reservedMaskArr;
typedef __ARRAY1_ti_sdo_ipc_gates_GateHWSem_reservedMaskArr __TA_ti_sdo_ipc_gates_GateHWSem_reservedMaskArr;
typedef __TA_ti_sdo_ipc_gates_GateHWSem_reservedMaskArr CT__ti_sdo_ipc_gates_GateHWSem_reservedMaskArr;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateHWSem_reservedMaskArr ti_sdo_ipc_gates_GateHWSem_reservedMaskArr__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_gates_GateHWSem_Params {
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
struct ti_sdo_ipc_gates_GateHWSem_Struct {
    const ti_sdo_ipc_gates_GateHWSem_Fxns__ *__fxns;
    xdc_UInt __f0;
    xdc_UInt __f1;
    xdc_runtime_IGateProvider_Handle __f2;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_gates_GateHWSem_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(ti_sdo_ipc_gates_GateHWSem_Handle);
    xdc_Void (*leave)(ti_sdo_ipc_gates_GateHWSem_Handle, xdc_IArg);
    xdc_Bits32 *(*getReservedMask)(void);
    xdc_SizeT (*sharedMemReq)(const ti_sdo_ipc_interfaces_IGateMPSupport_Params*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_gates_GateHWSem_Fxns__ ti_sdo_ipc_gates_GateHWSem_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_gates_GateHWSem_Module_startup ti_sdo_ipc_gates_GateHWSem_Module_startup__E
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Module_startup__E, "ti_sdo_ipc_gates_GateHWSem_Module_startup")
__extern xdc_Int ti_sdo_ipc_gates_GateHWSem_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Module_startup__F, "ti_sdo_ipc_gates_GateHWSem_Module_startup")
__extern xdc_Int ti_sdo_ipc_gates_GateHWSem_Module_startup__F( xdc_Int state );

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Instance_init__E, "ti_sdo_ipc_gates_GateHWSem_Instance_init")
__extern xdc_Void ti_sdo_ipc_gates_GateHWSem_Instance_init__E(ti_sdo_ipc_gates_GateHWSem_Object *, xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GateHWSem_Params *);

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Handle__label__S, "ti_sdo_ipc_gates_GateHWSem_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_gates_GateHWSem_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Module__startupDone__S, "ti_sdo_ipc_gates_GateHWSem_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_gates_GateHWSem_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Object__create__S, "ti_sdo_ipc_gates_GateHWSem_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateHWSem_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_create, "ti_sdo_ipc_gates_GateHWSem_create")
__extern ti_sdo_ipc_gates_GateHWSem_Handle ti_sdo_ipc_gates_GateHWSem_create( xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GateHWSem_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_construct, "ti_sdo_ipc_gates_GateHWSem_construct")
__extern void ti_sdo_ipc_gates_GateHWSem_construct( ti_sdo_ipc_gates_GateHWSem_Struct *__obj, xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GateHWSem_Params *__prms );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Object__delete__S, "ti_sdo_ipc_gates_GateHWSem_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_gates_GateHWSem_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_delete, "ti_sdo_ipc_gates_GateHWSem_delete")
__extern void ti_sdo_ipc_gates_GateHWSem_delete(ti_sdo_ipc_gates_GateHWSem_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Object__destruct__S, "ti_sdo_ipc_gates_GateHWSem_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_gates_GateHWSem_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_destruct, "ti_sdo_ipc_gates_GateHWSem_destruct")
__extern void ti_sdo_ipc_gates_GateHWSem_destruct(ti_sdo_ipc_gates_GateHWSem_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Object__get__S, "ti_sdo_ipc_gates_GateHWSem_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateHWSem_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Object__first__S, "ti_sdo_ipc_gates_GateHWSem_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateHWSem_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Object__next__S, "ti_sdo_ipc_gates_GateHWSem_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateHWSem_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_Params__init__S, "ti_sdo_ipc_gates_GateHWSem_Params__init__S")
__extern xdc_Void ti_sdo_ipc_gates_GateHWSem_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* query__E */
#define ti_sdo_ipc_gates_GateHWSem_query ti_sdo_ipc_gates_GateHWSem_query__E
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_query__E, "ti_sdo_ipc_gates_GateHWSem_query")
__extern xdc_Bool ti_sdo_ipc_gates_GateHWSem_query__E( xdc_Int qual );

/* getReservedMask__E */
#define ti_sdo_ipc_gates_GateHWSem_getReservedMask ti_sdo_ipc_gates_GateHWSem_getReservedMask__E
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_getReservedMask__E, "ti_sdo_ipc_gates_GateHWSem_getReservedMask")
__extern xdc_Bits32 *ti_sdo_ipc_gates_GateHWSem_getReservedMask__E( void );

/* sharedMemReq__E */
#define ti_sdo_ipc_gates_GateHWSem_sharedMemReq ti_sdo_ipc_gates_GateHWSem_sharedMemReq__E
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_sharedMemReq__E, "ti_sdo_ipc_gates_GateHWSem_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_gates_GateHWSem_sharedMemReq__E( const ti_sdo_ipc_interfaces_IGateMPSupport_Params *params );

/* enter__E */
#define ti_sdo_ipc_gates_GateHWSem_enter ti_sdo_ipc_gates_GateHWSem_enter__E
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_enter__E, "ti_sdo_ipc_gates_GateHWSem_enter")
__extern xdc_IArg ti_sdo_ipc_gates_GateHWSem_enter__E( ti_sdo_ipc_gates_GateHWSem_Handle __inst );

/* leave__E */
#define ti_sdo_ipc_gates_GateHWSem_leave ti_sdo_ipc_gates_GateHWSem_leave__E
xdc__CODESECT(ti_sdo_ipc_gates_GateHWSem_leave__E, "ti_sdo_ipc_gates_GateHWSem_leave")
__extern xdc_Void ti_sdo_ipc_gates_GateHWSem_leave__E( ti_sdo_ipc_gates_GateHWSem_Handle __inst, xdc_IArg key );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Module ti_sdo_ipc_gates_GateHWSem_Module_upCast( void )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Module)&ti_sdo_ipc_gates_GateHWSem_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GateHWSem_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateHWSem_Module_upCast

/* Handle_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Handle ti_sdo_ipc_gates_GateHWSem_Handle_upCast( ti_sdo_ipc_gates_GateHWSem_Handle i )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GateHWSem_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateHWSem_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_gates_GateHWSem_Handle ti_sdo_ipc_gates_GateHWSem_Handle_downCast( ti_sdo_ipc_interfaces_IGateMPSupport_Handle i )
{
    ti_sdo_ipc_interfaces_IGateMPSupport_Handle i2 = (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_gates_GateHWSem_Module__FXNS__C ? (ti_sdo_ipc_gates_GateHWSem_Handle)i : (ti_sdo_ipc_gates_GateHWSem_Handle)0;
}

/* Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GateHWSem_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateHWSem_Handle_downCast

/* Module_upCast2 */
static inline xdc_runtime_IGateProvider_Module ti_sdo_ipc_gates_GateHWSem_Module_upCast2( void )
{
    return (xdc_runtime_IGateProvider_Module)&ti_sdo_ipc_gates_GateHWSem_Module__FXNS__C;
}

/* Module_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GateHWSem_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateHWSem_Module_upCast2

/* Handle_upCast2 */
static inline xdc_runtime_IGateProvider_Handle ti_sdo_ipc_gates_GateHWSem_Handle_upCast2( ti_sdo_ipc_gates_GateHWSem_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GateHWSem_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateHWSem_Handle_upCast2

/* Handle_downCast2 */
static inline ti_sdo_ipc_gates_GateHWSem_Handle ti_sdo_ipc_gates_GateHWSem_Handle_downCast2( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_gates_GateHWSem_Module__FXNS__C ? (ti_sdo_ipc_gates_GateHWSem_Handle)i : (ti_sdo_ipc_gates_GateHWSem_Handle)0;
}

/* Handle_from_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GateHWSem_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateHWSem_Handle_downCast2


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_gates_GateHWSem_Module_startupDone() ti_sdo_ipc_gates_GateHWSem_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_gates_GateHWSem_Object_heap() ti_sdo_ipc_gates_GateHWSem_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_gates_GateHWSem_Module_heap() ti_sdo_ipc_gates_GateHWSem_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_gates_GateHWSem_Module__id ti_sdo_ipc_gates_GateHWSem_Module_id( void ) 
{
    return ti_sdo_ipc_gates_GateHWSem_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_gates_GateHWSem_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_gates_GateHWSem_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_gates_GateHWSem_Module_getMask( void ) 
{
    return ti_sdo_ipc_gates_GateHWSem_Module__diagsMask__C != NULL ? *ti_sdo_ipc_gates_GateHWSem_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_gates_GateHWSem_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_gates_GateHWSem_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_gates_GateHWSem_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_gates_GateHWSem_Params_init( ti_sdo_ipc_gates_GateHWSem_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_gates_GateHWSem_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_gates_GateHWSem_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_gates_GateHWSem_Params_copy(ti_sdo_ipc_gates_GateHWSem_Params *dst, const ti_sdo_ipc_gates_GateHWSem_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_gates_GateHWSem_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_gates_GateHWSem_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_gates_GateHWSem_Object_count() ti_sdo_ipc_gates_GateHWSem_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_gates_GateHWSem_Object_sizeof() ti_sdo_ipc_gates_GateHWSem_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_gates_GateHWSem_Handle ti_sdo_ipc_gates_GateHWSem_Object_get(ti_sdo_ipc_gates_GateHWSem_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_gates_GateHWSem_Handle)ti_sdo_ipc_gates_GateHWSem_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_gates_GateHWSem_Handle ti_sdo_ipc_gates_GateHWSem_Object_first( void )
{
    return (ti_sdo_ipc_gates_GateHWSem_Handle)ti_sdo_ipc_gates_GateHWSem_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_gates_GateHWSem_Handle ti_sdo_ipc_gates_GateHWSem_Object_next( ti_sdo_ipc_gates_GateHWSem_Object *obj )
{
    return (ti_sdo_ipc_gates_GateHWSem_Handle)ti_sdo_ipc_gates_GateHWSem_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_gates_GateHWSem_Handle_label( ti_sdo_ipc_gates_GateHWSem_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_gates_GateHWSem_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_gates_GateHWSem_Handle_name( ti_sdo_ipc_gates_GateHWSem_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_gates_GateHWSem_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_gates_GateHWSem_Handle ti_sdo_ipc_gates_GateHWSem_handle( ti_sdo_ipc_gates_GateHWSem_Struct *str )
{
    return (ti_sdo_ipc_gates_GateHWSem_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_gates_GateHWSem_Struct *ti_sdo_ipc_gates_GateHWSem_struct( ti_sdo_ipc_gates_GateHWSem_Handle inst )
{
    return (ti_sdo_ipc_gates_GateHWSem_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_gates_GateHWSem__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_gates_GateHWSem__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_gates_GateHWSem__internalaccess))

#ifndef ti_sdo_ipc_gates_GateHWSem__include_state
#define ti_sdo_ipc_gates_GateHWSem__include_state

/* Object */
struct ti_sdo_ipc_gates_GateHWSem_Object {
    const ti_sdo_ipc_gates_GateHWSem_Fxns__ *__fxns;
    xdc_UInt semNum;
    xdc_UInt nested;
    xdc_runtime_IGateProvider_Handle localGate;
};

#endif /* ti_sdo_ipc_gates_GateHWSem__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_gates_GateHWSem__nolocalnames)

#ifndef ti_sdo_ipc_gates_GateHWSem__localnames__done
#define ti_sdo_ipc_gates_GateHWSem__localnames__done

/* module prefix */
#define GateHWSem_Instance ti_sdo_ipc_gates_GateHWSem_Instance
#define GateHWSem_Handle ti_sdo_ipc_gates_GateHWSem_Handle
#define GateHWSem_Module ti_sdo_ipc_gates_GateHWSem_Module
#define GateHWSem_Object ti_sdo_ipc_gates_GateHWSem_Object
#define GateHWSem_Struct ti_sdo_ipc_gates_GateHWSem_Struct
#define GateHWSem_Q_BLOCKING ti_sdo_ipc_gates_GateHWSem_Q_BLOCKING
#define GateHWSem_Q_PREEMPTING ti_sdo_ipc_gates_GateHWSem_Q_PREEMPTING
#define GateHWSem_Instance_State ti_sdo_ipc_gates_GateHWSem_Instance_State
#define GateHWSem_A_invSemNum ti_sdo_ipc_gates_GateHWSem_A_invSemNum
#define GateHWSem_baseAddr ti_sdo_ipc_gates_GateHWSem_baseAddr
#define GateHWSem_queryAddr ti_sdo_ipc_gates_GateHWSem_queryAddr
#define GateHWSem_numSems ti_sdo_ipc_gates_GateHWSem_numSems
#define GateHWSem_reservedMaskArr ti_sdo_ipc_gates_GateHWSem_reservedMaskArr
#define GateHWSem_Params ti_sdo_ipc_gates_GateHWSem_Params
#define GateHWSem_query ti_sdo_ipc_gates_GateHWSem_query
#define GateHWSem_getReservedMask ti_sdo_ipc_gates_GateHWSem_getReservedMask
#define GateHWSem_sharedMemReq ti_sdo_ipc_gates_GateHWSem_sharedMemReq
#define GateHWSem_enter ti_sdo_ipc_gates_GateHWSem_enter
#define GateHWSem_leave ti_sdo_ipc_gates_GateHWSem_leave
#define GateHWSem_Module_name ti_sdo_ipc_gates_GateHWSem_Module_name
#define GateHWSem_Module_id ti_sdo_ipc_gates_GateHWSem_Module_id
#define GateHWSem_Module_startup ti_sdo_ipc_gates_GateHWSem_Module_startup
#define GateHWSem_Module_startupDone ti_sdo_ipc_gates_GateHWSem_Module_startupDone
#define GateHWSem_Module_hasMask ti_sdo_ipc_gates_GateHWSem_Module_hasMask
#define GateHWSem_Module_getMask ti_sdo_ipc_gates_GateHWSem_Module_getMask
#define GateHWSem_Module_setMask ti_sdo_ipc_gates_GateHWSem_Module_setMask
#define GateHWSem_Object_heap ti_sdo_ipc_gates_GateHWSem_Object_heap
#define GateHWSem_Module_heap ti_sdo_ipc_gates_GateHWSem_Module_heap
#define GateHWSem_construct ti_sdo_ipc_gates_GateHWSem_construct
#define GateHWSem_create ti_sdo_ipc_gates_GateHWSem_create
#define GateHWSem_handle ti_sdo_ipc_gates_GateHWSem_handle
#define GateHWSem_struct ti_sdo_ipc_gates_GateHWSem_struct
#define GateHWSem_Handle_label ti_sdo_ipc_gates_GateHWSem_Handle_label
#define GateHWSem_Handle_name ti_sdo_ipc_gates_GateHWSem_Handle_name
#define GateHWSem_Instance_init ti_sdo_ipc_gates_GateHWSem_Instance_init
#define GateHWSem_Object_count ti_sdo_ipc_gates_GateHWSem_Object_count
#define GateHWSem_Object_get ti_sdo_ipc_gates_GateHWSem_Object_get
#define GateHWSem_Object_first ti_sdo_ipc_gates_GateHWSem_Object_first
#define GateHWSem_Object_next ti_sdo_ipc_gates_GateHWSem_Object_next
#define GateHWSem_Object_sizeof ti_sdo_ipc_gates_GateHWSem_Object_sizeof
#define GateHWSem_Params_copy ti_sdo_ipc_gates_GateHWSem_Params_copy
#define GateHWSem_Params_init ti_sdo_ipc_gates_GateHWSem_Params_init
#define GateHWSem_delete ti_sdo_ipc_gates_GateHWSem_delete
#define GateHWSem_destruct ti_sdo_ipc_gates_GateHWSem_destruct
#define GateHWSem_Module_upCast ti_sdo_ipc_gates_GateHWSem_Module_upCast
#define GateHWSem_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateHWSem_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateHWSem_Handle_upCast ti_sdo_ipc_gates_GateHWSem_Handle_upCast
#define GateHWSem_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateHWSem_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateHWSem_Handle_downCast ti_sdo_ipc_gates_GateHWSem_Handle_downCast
#define GateHWSem_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateHWSem_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateHWSem_Module_upCast2 ti_sdo_ipc_gates_GateHWSem_Module_upCast2
#define GateHWSem_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateHWSem_Module_to_xdc_runtime_IGateProvider
#define GateHWSem_Handle_upCast2 ti_sdo_ipc_gates_GateHWSem_Handle_upCast2
#define GateHWSem_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateHWSem_Handle_to_xdc_runtime_IGateProvider
#define GateHWSem_Handle_downCast2 ti_sdo_ipc_gates_GateHWSem_Handle_downCast2
#define GateHWSem_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateHWSem_Handle_from_xdc_runtime_IGateProvider

#endif /* ti_sdo_ipc_gates_GateHWSem__localnames__done */
#endif
