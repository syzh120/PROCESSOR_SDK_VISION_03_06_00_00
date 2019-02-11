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

#ifndef ti_sdo_ipc_gates_GateMPSupportNull__include
#define ti_sdo_ipc_gates_GateMPSupportNull__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_gates_GateMPSupportNull__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_gates_GateMPSupportNull___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/gates/package/package.defs.h>

#include <xdc/runtime/Assert.h>
#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */
#define ti_sdo_ipc_gates_GateMPSupportNull_Q_BLOCKING (1)

/* Q_PREEMPTING */
#define ti_sdo_ipc_gates_GateMPSupportNull_Q_PREEMPTING (2)

/* Action */
enum ti_sdo_ipc_gates_GateMPSupportNull_Action {
    ti_sdo_ipc_gates_GateMPSupportNull_Action_NONE = 0,
    ti_sdo_ipc_gates_GateMPSupportNull_Action_ASSERT = 1
};
typedef enum ti_sdo_ipc_gates_GateMPSupportNull_Action ti_sdo_ipc_gates_GateMPSupportNull_Action;


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_gates_GateMPSupportNull_Args__create {
    xdc_runtime_IGateProvider_Handle localGate;
} ti_sdo_ipc_gates_GateMPSupportNull_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsEnabled ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsIncluded ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsMask ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__gateObj ti_sdo_ipc_gates_GateMPSupportNull_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__gatePrms ti_sdo_ipc_gates_GateMPSupportNull_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__id ti_sdo_ipc_gates_GateMPSupportNull_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerDefined ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerObj ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn0 ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn1 ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn2 ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn4 ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn8 ti_sdo_ipc_gates_GateMPSupportNull_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__startupDoneFxn ti_sdo_ipc_gates_GateMPSupportNull_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_gates_GateMPSupportNull_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Object__count ti_sdo_ipc_gates_GateMPSupportNull_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_gates_GateMPSupportNull_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Object__heap ti_sdo_ipc_gates_GateMPSupportNull_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_gates_GateMPSupportNull_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Object__sizeof ti_sdo_ipc_gates_GateMPSupportNull_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_gates_GateMPSupportNull_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_Object__table ti_sdo_ipc_gates_GateMPSupportNull_Object__table__C;

/* A_invalidAction */
#define ti_sdo_ipc_gates_GateMPSupportNull_A_invalidAction (ti_sdo_ipc_gates_GateMPSupportNull_A_invalidAction__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_gates_GateMPSupportNull_A_invalidAction;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_A_invalidAction ti_sdo_ipc_gates_GateMPSupportNull_A_invalidAction__C;

/* action */
#define ti_sdo_ipc_gates_GateMPSupportNull_action (ti_sdo_ipc_gates_GateMPSupportNull_action__C)
typedef ti_sdo_ipc_gates_GateMPSupportNull_Action CT__ti_sdo_ipc_gates_GateMPSupportNull_action;
__extern __FAR__ const CT__ti_sdo_ipc_gates_GateMPSupportNull_action ti_sdo_ipc_gates_GateMPSupportNull_action__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_gates_GateMPSupportNull_Params {
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
struct ti_sdo_ipc_gates_GateMPSupportNull_Struct {
    const ti_sdo_ipc_gates_GateMPSupportNull_Fxns__ *__fxns;
    xdc_UInt __f0;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_gates_GateMPSupportNull_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(ti_sdo_ipc_gates_GateMPSupportNull_Handle);
    xdc_Void (*leave)(ti_sdo_ipc_gates_GateMPSupportNull_Handle, xdc_IArg);
    xdc_Bits32 *(*getReservedMask)(void);
    xdc_SizeT (*sharedMemReq)(const ti_sdo_ipc_interfaces_IGateMPSupport_Params*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_gates_GateMPSupportNull_Fxns__ ti_sdo_ipc_gates_GateMPSupportNull_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_gates_GateMPSupportNull_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_Instance_init__E, "ti_sdo_ipc_gates_GateMPSupportNull_Instance_init")
__extern xdc_Void ti_sdo_ipc_gates_GateMPSupportNull_Instance_init__E(ti_sdo_ipc_gates_GateMPSupportNull_Object *, xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GateMPSupportNull_Params *);

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_Handle__label__S, "ti_sdo_ipc_gates_GateMPSupportNull_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_gates_GateMPSupportNull_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_Module__startupDone__S, "ti_sdo_ipc_gates_GateMPSupportNull_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_gates_GateMPSupportNull_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_Object__create__S, "ti_sdo_ipc_gates_GateMPSupportNull_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateMPSupportNull_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_create, "ti_sdo_ipc_gates_GateMPSupportNull_create")
__extern ti_sdo_ipc_gates_GateMPSupportNull_Handle ti_sdo_ipc_gates_GateMPSupportNull_create( xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GateMPSupportNull_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_construct, "ti_sdo_ipc_gates_GateMPSupportNull_construct")
__extern void ti_sdo_ipc_gates_GateMPSupportNull_construct( ti_sdo_ipc_gates_GateMPSupportNull_Struct *__obj, xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_gates_GateMPSupportNull_Params *__prms );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_Object__delete__S, "ti_sdo_ipc_gates_GateMPSupportNull_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_gates_GateMPSupportNull_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_delete, "ti_sdo_ipc_gates_GateMPSupportNull_delete")
__extern void ti_sdo_ipc_gates_GateMPSupportNull_delete(ti_sdo_ipc_gates_GateMPSupportNull_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_Object__destruct__S, "ti_sdo_ipc_gates_GateMPSupportNull_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_gates_GateMPSupportNull_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_destruct, "ti_sdo_ipc_gates_GateMPSupportNull_destruct")
__extern void ti_sdo_ipc_gates_GateMPSupportNull_destruct(ti_sdo_ipc_gates_GateMPSupportNull_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_Object__get__S, "ti_sdo_ipc_gates_GateMPSupportNull_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateMPSupportNull_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_Object__first__S, "ti_sdo_ipc_gates_GateMPSupportNull_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateMPSupportNull_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_Object__next__S, "ti_sdo_ipc_gates_GateMPSupportNull_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_gates_GateMPSupportNull_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_Params__init__S, "ti_sdo_ipc_gates_GateMPSupportNull_Params__init__S")
__extern xdc_Void ti_sdo_ipc_gates_GateMPSupportNull_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* query__E */
#define ti_sdo_ipc_gates_GateMPSupportNull_query ti_sdo_ipc_gates_GateMPSupportNull_query__E
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_query__E, "ti_sdo_ipc_gates_GateMPSupportNull_query")
__extern xdc_Bool ti_sdo_ipc_gates_GateMPSupportNull_query__E( xdc_Int qual );

/* getReservedMask__E */
#define ti_sdo_ipc_gates_GateMPSupportNull_getReservedMask ti_sdo_ipc_gates_GateMPSupportNull_getReservedMask__E
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_getReservedMask__E, "ti_sdo_ipc_gates_GateMPSupportNull_getReservedMask")
__extern xdc_Bits32 *ti_sdo_ipc_gates_GateMPSupportNull_getReservedMask__E( void );

/* sharedMemReq__E */
#define ti_sdo_ipc_gates_GateMPSupportNull_sharedMemReq ti_sdo_ipc_gates_GateMPSupportNull_sharedMemReq__E
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_sharedMemReq__E, "ti_sdo_ipc_gates_GateMPSupportNull_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_gates_GateMPSupportNull_sharedMemReq__E( const ti_sdo_ipc_interfaces_IGateMPSupport_Params *params );

/* enter__E */
#define ti_sdo_ipc_gates_GateMPSupportNull_enter ti_sdo_ipc_gates_GateMPSupportNull_enter__E
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_enter__E, "ti_sdo_ipc_gates_GateMPSupportNull_enter")
__extern xdc_IArg ti_sdo_ipc_gates_GateMPSupportNull_enter__E( ti_sdo_ipc_gates_GateMPSupportNull_Handle __inst );

/* leave__E */
#define ti_sdo_ipc_gates_GateMPSupportNull_leave ti_sdo_ipc_gates_GateMPSupportNull_leave__E
xdc__CODESECT(ti_sdo_ipc_gates_GateMPSupportNull_leave__E, "ti_sdo_ipc_gates_GateMPSupportNull_leave")
__extern xdc_Void ti_sdo_ipc_gates_GateMPSupportNull_leave__E( ti_sdo_ipc_gates_GateMPSupportNull_Handle __inst, xdc_IArg key );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Module ti_sdo_ipc_gates_GateMPSupportNull_Module_upCast( void )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Module)&ti_sdo_ipc_gates_GateMPSupportNull_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GateMPSupportNull_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateMPSupportNull_Module_upCast

/* Handle_upCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Handle ti_sdo_ipc_gates_GateMPSupportNull_Handle_upCast( ti_sdo_ipc_gates_GateMPSupportNull_Handle i )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GateMPSupportNull_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateMPSupportNull_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_gates_GateMPSupportNull_Handle ti_sdo_ipc_gates_GateMPSupportNull_Handle_downCast( ti_sdo_ipc_interfaces_IGateMPSupport_Handle i )
{
    ti_sdo_ipc_interfaces_IGateMPSupport_Handle i2 = (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_gates_GateMPSupportNull_Module__FXNS__C ? (ti_sdo_ipc_gates_GateMPSupportNull_Handle)i : (ti_sdo_ipc_gates_GateMPSupportNull_Handle)0;
}

/* Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport */
#define ti_sdo_ipc_gates_GateMPSupportNull_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateMPSupportNull_Handle_downCast

/* Module_upCast2 */
static inline xdc_runtime_IGateProvider_Module ti_sdo_ipc_gates_GateMPSupportNull_Module_upCast2( void )
{
    return (xdc_runtime_IGateProvider_Module)&ti_sdo_ipc_gates_GateMPSupportNull_Module__FXNS__C;
}

/* Module_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GateMPSupportNull_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateMPSupportNull_Module_upCast2

/* Handle_upCast2 */
static inline xdc_runtime_IGateProvider_Handle ti_sdo_ipc_gates_GateMPSupportNull_Handle_upCast2( ti_sdo_ipc_gates_GateMPSupportNull_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GateMPSupportNull_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateMPSupportNull_Handle_upCast2

/* Handle_downCast2 */
static inline ti_sdo_ipc_gates_GateMPSupportNull_Handle ti_sdo_ipc_gates_GateMPSupportNull_Handle_downCast2( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_gates_GateMPSupportNull_Module__FXNS__C ? (ti_sdo_ipc_gates_GateMPSupportNull_Handle)i : (ti_sdo_ipc_gates_GateMPSupportNull_Handle)0;
}

/* Handle_from_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_gates_GateMPSupportNull_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateMPSupportNull_Handle_downCast2


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_gates_GateMPSupportNull_Module_startupDone() ti_sdo_ipc_gates_GateMPSupportNull_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_gates_GateMPSupportNull_Object_heap() ti_sdo_ipc_gates_GateMPSupportNull_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_gates_GateMPSupportNull_Module_heap() ti_sdo_ipc_gates_GateMPSupportNull_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_gates_GateMPSupportNull_Module__id ti_sdo_ipc_gates_GateMPSupportNull_Module_id( void ) 
{
    return ti_sdo_ipc_gates_GateMPSupportNull_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_gates_GateMPSupportNull_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_gates_GateMPSupportNull_Module_getMask( void ) 
{
    return ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsMask__C != NULL ? *ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_gates_GateMPSupportNull_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_gates_GateMPSupportNull_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_gates_GateMPSupportNull_Params_init( ti_sdo_ipc_gates_GateMPSupportNull_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_gates_GateMPSupportNull_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_gates_GateMPSupportNull_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_gates_GateMPSupportNull_Params_copy(ti_sdo_ipc_gates_GateMPSupportNull_Params *dst, const ti_sdo_ipc_gates_GateMPSupportNull_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_gates_GateMPSupportNull_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_gates_GateMPSupportNull_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_gates_GateMPSupportNull_Object_count() ti_sdo_ipc_gates_GateMPSupportNull_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_gates_GateMPSupportNull_Object_sizeof() ti_sdo_ipc_gates_GateMPSupportNull_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_gates_GateMPSupportNull_Handle ti_sdo_ipc_gates_GateMPSupportNull_Object_get(ti_sdo_ipc_gates_GateMPSupportNull_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_gates_GateMPSupportNull_Handle)ti_sdo_ipc_gates_GateMPSupportNull_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_gates_GateMPSupportNull_Handle ti_sdo_ipc_gates_GateMPSupportNull_Object_first( void )
{
    return (ti_sdo_ipc_gates_GateMPSupportNull_Handle)ti_sdo_ipc_gates_GateMPSupportNull_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_gates_GateMPSupportNull_Handle ti_sdo_ipc_gates_GateMPSupportNull_Object_next( ti_sdo_ipc_gates_GateMPSupportNull_Object *obj )
{
    return (ti_sdo_ipc_gates_GateMPSupportNull_Handle)ti_sdo_ipc_gates_GateMPSupportNull_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_gates_GateMPSupportNull_Handle_label( ti_sdo_ipc_gates_GateMPSupportNull_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_gates_GateMPSupportNull_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_gates_GateMPSupportNull_Handle_name( ti_sdo_ipc_gates_GateMPSupportNull_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_gates_GateMPSupportNull_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_gates_GateMPSupportNull_Handle ti_sdo_ipc_gates_GateMPSupportNull_handle( ti_sdo_ipc_gates_GateMPSupportNull_Struct *str )
{
    return (ti_sdo_ipc_gates_GateMPSupportNull_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_gates_GateMPSupportNull_Struct *ti_sdo_ipc_gates_GateMPSupportNull_struct( ti_sdo_ipc_gates_GateMPSupportNull_Handle inst )
{
    return (ti_sdo_ipc_gates_GateMPSupportNull_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_gates_GateMPSupportNull__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_gates_GateMPSupportNull__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_gates_GateMPSupportNull__internalaccess))

#ifndef ti_sdo_ipc_gates_GateMPSupportNull__include_state
#define ti_sdo_ipc_gates_GateMPSupportNull__include_state

/* Object */
struct ti_sdo_ipc_gates_GateMPSupportNull_Object {
    const ti_sdo_ipc_gates_GateMPSupportNull_Fxns__ *__fxns;
    xdc_UInt resourceId;
};

#endif /* ti_sdo_ipc_gates_GateMPSupportNull__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_gates_GateMPSupportNull__nolocalnames)

#ifndef ti_sdo_ipc_gates_GateMPSupportNull__localnames__done
#define ti_sdo_ipc_gates_GateMPSupportNull__localnames__done

/* module prefix */
#define GateMPSupportNull_Instance ti_sdo_ipc_gates_GateMPSupportNull_Instance
#define GateMPSupportNull_Handle ti_sdo_ipc_gates_GateMPSupportNull_Handle
#define GateMPSupportNull_Module ti_sdo_ipc_gates_GateMPSupportNull_Module
#define GateMPSupportNull_Object ti_sdo_ipc_gates_GateMPSupportNull_Object
#define GateMPSupportNull_Struct ti_sdo_ipc_gates_GateMPSupportNull_Struct
#define GateMPSupportNull_Q_BLOCKING ti_sdo_ipc_gates_GateMPSupportNull_Q_BLOCKING
#define GateMPSupportNull_Q_PREEMPTING ti_sdo_ipc_gates_GateMPSupportNull_Q_PREEMPTING
#define GateMPSupportNull_Action ti_sdo_ipc_gates_GateMPSupportNull_Action
#define GateMPSupportNull_Instance_State ti_sdo_ipc_gates_GateMPSupportNull_Instance_State
#define GateMPSupportNull_Action_NONE ti_sdo_ipc_gates_GateMPSupportNull_Action_NONE
#define GateMPSupportNull_Action_ASSERT ti_sdo_ipc_gates_GateMPSupportNull_Action_ASSERT
#define GateMPSupportNull_A_invalidAction ti_sdo_ipc_gates_GateMPSupportNull_A_invalidAction
#define GateMPSupportNull_action ti_sdo_ipc_gates_GateMPSupportNull_action
#define GateMPSupportNull_Params ti_sdo_ipc_gates_GateMPSupportNull_Params
#define GateMPSupportNull_query ti_sdo_ipc_gates_GateMPSupportNull_query
#define GateMPSupportNull_getReservedMask ti_sdo_ipc_gates_GateMPSupportNull_getReservedMask
#define GateMPSupportNull_sharedMemReq ti_sdo_ipc_gates_GateMPSupportNull_sharedMemReq
#define GateMPSupportNull_enter ti_sdo_ipc_gates_GateMPSupportNull_enter
#define GateMPSupportNull_leave ti_sdo_ipc_gates_GateMPSupportNull_leave
#define GateMPSupportNull_Module_name ti_sdo_ipc_gates_GateMPSupportNull_Module_name
#define GateMPSupportNull_Module_id ti_sdo_ipc_gates_GateMPSupportNull_Module_id
#define GateMPSupportNull_Module_startup ti_sdo_ipc_gates_GateMPSupportNull_Module_startup
#define GateMPSupportNull_Module_startupDone ti_sdo_ipc_gates_GateMPSupportNull_Module_startupDone
#define GateMPSupportNull_Module_hasMask ti_sdo_ipc_gates_GateMPSupportNull_Module_hasMask
#define GateMPSupportNull_Module_getMask ti_sdo_ipc_gates_GateMPSupportNull_Module_getMask
#define GateMPSupportNull_Module_setMask ti_sdo_ipc_gates_GateMPSupportNull_Module_setMask
#define GateMPSupportNull_Object_heap ti_sdo_ipc_gates_GateMPSupportNull_Object_heap
#define GateMPSupportNull_Module_heap ti_sdo_ipc_gates_GateMPSupportNull_Module_heap
#define GateMPSupportNull_construct ti_sdo_ipc_gates_GateMPSupportNull_construct
#define GateMPSupportNull_create ti_sdo_ipc_gates_GateMPSupportNull_create
#define GateMPSupportNull_handle ti_sdo_ipc_gates_GateMPSupportNull_handle
#define GateMPSupportNull_struct ti_sdo_ipc_gates_GateMPSupportNull_struct
#define GateMPSupportNull_Handle_label ti_sdo_ipc_gates_GateMPSupportNull_Handle_label
#define GateMPSupportNull_Handle_name ti_sdo_ipc_gates_GateMPSupportNull_Handle_name
#define GateMPSupportNull_Instance_init ti_sdo_ipc_gates_GateMPSupportNull_Instance_init
#define GateMPSupportNull_Object_count ti_sdo_ipc_gates_GateMPSupportNull_Object_count
#define GateMPSupportNull_Object_get ti_sdo_ipc_gates_GateMPSupportNull_Object_get
#define GateMPSupportNull_Object_first ti_sdo_ipc_gates_GateMPSupportNull_Object_first
#define GateMPSupportNull_Object_next ti_sdo_ipc_gates_GateMPSupportNull_Object_next
#define GateMPSupportNull_Object_sizeof ti_sdo_ipc_gates_GateMPSupportNull_Object_sizeof
#define GateMPSupportNull_Params_copy ti_sdo_ipc_gates_GateMPSupportNull_Params_copy
#define GateMPSupportNull_Params_init ti_sdo_ipc_gates_GateMPSupportNull_Params_init
#define GateMPSupportNull_delete ti_sdo_ipc_gates_GateMPSupportNull_delete
#define GateMPSupportNull_destruct ti_sdo_ipc_gates_GateMPSupportNull_destruct
#define GateMPSupportNull_Module_upCast ti_sdo_ipc_gates_GateMPSupportNull_Module_upCast
#define GateMPSupportNull_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateMPSupportNull_Module_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateMPSupportNull_Handle_upCast ti_sdo_ipc_gates_GateMPSupportNull_Handle_upCast
#define GateMPSupportNull_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateMPSupportNull_Handle_to_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateMPSupportNull_Handle_downCast ti_sdo_ipc_gates_GateMPSupportNull_Handle_downCast
#define GateMPSupportNull_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport ti_sdo_ipc_gates_GateMPSupportNull_Handle_from_ti_sdo_ipc_interfaces_IGateMPSupport
#define GateMPSupportNull_Module_upCast2 ti_sdo_ipc_gates_GateMPSupportNull_Module_upCast2
#define GateMPSupportNull_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateMPSupportNull_Module_to_xdc_runtime_IGateProvider
#define GateMPSupportNull_Handle_upCast2 ti_sdo_ipc_gates_GateMPSupportNull_Handle_upCast2
#define GateMPSupportNull_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateMPSupportNull_Handle_to_xdc_runtime_IGateProvider
#define GateMPSupportNull_Handle_downCast2 ti_sdo_ipc_gates_GateMPSupportNull_Handle_downCast2
#define GateMPSupportNull_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_gates_GateMPSupportNull_Handle_from_xdc_runtime_IGateProvider

#endif /* ti_sdo_ipc_gates_GateMPSupportNull__localnames__done */
#endif
