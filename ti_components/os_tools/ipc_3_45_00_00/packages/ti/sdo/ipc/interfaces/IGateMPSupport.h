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
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     CONVERTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_sdo_ipc_interfaces_IGateMPSupport__include
#define ti_sdo_ipc_interfaces_IGateMPSupport__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_interfaces_IGateMPSupport__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_interfaces_IGateMPSupport___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/interfaces/package/package.defs.h>

#include <xdc/runtime/IGateProvider.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */
#define ti_sdo_ipc_interfaces_IGateMPSupport_Q_BLOCKING (1)

/* Q_PREEMPTING */
#define ti_sdo_ipc_interfaces_IGateMPSupport_Q_PREEMPTING (2)


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_interfaces_IGateMPSupport_Args__create {
    xdc_runtime_IGateProvider_Handle localGate;
} ti_sdo_ipc_interfaces_IGateMPSupport_Args__create;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_interfaces_IGateMPSupport_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_UInt resourceId;
    xdc_Bool openFlag;
    xdc_UInt16 regionId;
    xdc_Ptr sharedAddr;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_interfaces_IGateMPSupport_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(void*);
    xdc_Void (*leave)(void*, xdc_IArg);
    xdc_Bits32 *(*getReservedMask)(void);
    xdc_SizeT (*sharedMemReq)(const ti_sdo_ipc_interfaces_IGateMPSupport_Params*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base ti_sdo_ipc_interfaces_IGateMPSupport_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
xdc__CODESECT(ti_sdo_ipc_interfaces_IGateMPSupport_create, "ti_sdo_ipc_interfaces_IGateMPSupport_create")
__extern ti_sdo_ipc_interfaces_IGateMPSupport_Handle ti_sdo_ipc_interfaces_IGateMPSupport_create(ti_sdo_ipc_interfaces_IGateMPSupport_Module, xdc_runtime_IGateProvider_Handle localGate, const ti_sdo_ipc_interfaces_IGateMPSupport_Params *, xdc_runtime_Error_Block *__eb);

/* delete */
xdc__CODESECT(ti_sdo_ipc_interfaces_IGateMPSupport_delete, "ti_sdo_ipc_interfaces_IGateMPSupport_delete")
__extern xdc_Void ti_sdo_ipc_interfaces_IGateMPSupport_delete(ti_sdo_ipc_interfaces_IGateMPSupport_Handle *);

/* Handle_to_Module */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Module ti_sdo_ipc_interfaces_IGateMPSupport_Handle_to_Module( ti_sdo_ipc_interfaces_IGateMPSupport_Handle inst )
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_interfaces_IGateMPSupport_Handle_label( ti_sdo_ipc_interfaces_IGateMPSupport_Handle inst, xdc_runtime_Types_Label *lab )
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId ti_sdo_ipc_interfaces_IGateMPSupport_Module_id( ti_sdo_ipc_interfaces_IGateMPSupport_Module mod )
{
    return mod->__sysp->__mid;
}

/* query */
static inline xdc_Bool ti_sdo_ipc_interfaces_IGateMPSupport_query( ti_sdo_ipc_interfaces_IGateMPSupport_Module __inst, xdc_Int qual )
{
    return __inst->query(qual);
}

/* enter */
static inline xdc_IArg ti_sdo_ipc_interfaces_IGateMPSupport_enter( ti_sdo_ipc_interfaces_IGateMPSupport_Handle __inst )
{
    return __inst->__fxns->enter((void*)__inst);
}

/* leave */
static inline xdc_Void ti_sdo_ipc_interfaces_IGateMPSupport_leave( ti_sdo_ipc_interfaces_IGateMPSupport_Handle __inst, xdc_IArg key )
{
    __inst->__fxns->leave((void*)__inst, key);
}

/* getReservedMask */
static inline xdc_Bits32 *ti_sdo_ipc_interfaces_IGateMPSupport_getReservedMask( ti_sdo_ipc_interfaces_IGateMPSupport_Module __inst )
{
    return __inst->getReservedMask();
}

/* sharedMemReq */
static inline xdc_SizeT ti_sdo_ipc_interfaces_IGateMPSupport_sharedMemReq( ti_sdo_ipc_interfaces_IGateMPSupport_Module __inst, const ti_sdo_ipc_interfaces_IGateMPSupport_Params *params )
{
    return __inst->sharedMemReq(params);
}


/*
 * ======== FUNCTION SELECTORS ========
 */

/* These functions return function pointers for module and instance functions.
 * The functions accept modules and instances declared as types defined in this
 * interface, but they return functions defined for the actual objects passed
 * as parameters. These functions are not invoked by any generated code or
 * XDCtools internal code.
 */

/* query_{FxnT,fxnP} */
typedef xdc_Bool (*ti_sdo_ipc_interfaces_IGateMPSupport_query_FxnT)(xdc_Int);
static inline ti_sdo_ipc_interfaces_IGateMPSupport_query_FxnT ti_sdo_ipc_interfaces_IGateMPSupport_query_fxnP( ti_sdo_ipc_interfaces_IGateMPSupport_Module __inst )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_query_FxnT)__inst->query;
}

/* enter_{FxnT,fxnP} */
typedef xdc_IArg (*ti_sdo_ipc_interfaces_IGateMPSupport_enter_FxnT)(xdc_Void *);
static inline ti_sdo_ipc_interfaces_IGateMPSupport_enter_FxnT ti_sdo_ipc_interfaces_IGateMPSupport_enter_fxnP( ti_sdo_ipc_interfaces_IGateMPSupport_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_enter_FxnT)__inst->__fxns->enter;
}

/* leave_{FxnT,fxnP} */
typedef xdc_Void (*ti_sdo_ipc_interfaces_IGateMPSupport_leave_FxnT)(xdc_Void *, xdc_IArg);
static inline ti_sdo_ipc_interfaces_IGateMPSupport_leave_FxnT ti_sdo_ipc_interfaces_IGateMPSupport_leave_fxnP( ti_sdo_ipc_interfaces_IGateMPSupport_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_leave_FxnT)__inst->__fxns->leave;
}

/* getReservedMask_{FxnT,fxnP} */
typedef xdc_Bits32 *(*ti_sdo_ipc_interfaces_IGateMPSupport_getReservedMask_FxnT)(void);
static inline ti_sdo_ipc_interfaces_IGateMPSupport_getReservedMask_FxnT ti_sdo_ipc_interfaces_IGateMPSupport_getReservedMask_fxnP( ti_sdo_ipc_interfaces_IGateMPSupport_Module __inst )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_getReservedMask_FxnT)__inst->getReservedMask;
}

/* sharedMemReq_{FxnT,fxnP} */
typedef xdc_SizeT (*ti_sdo_ipc_interfaces_IGateMPSupport_sharedMemReq_FxnT)(const ti_sdo_ipc_interfaces_IGateMPSupport_Params*);
static inline ti_sdo_ipc_interfaces_IGateMPSupport_sharedMemReq_FxnT ti_sdo_ipc_interfaces_IGateMPSupport_sharedMemReq_fxnP( ti_sdo_ipc_interfaces_IGateMPSupport_Module __inst )
{
    return (ti_sdo_ipc_interfaces_IGateMPSupport_sharedMemReq_FxnT)__inst->sharedMemReq;
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_IGateProvider_Module ti_sdo_ipc_interfaces_IGateMPSupport_Module_upCast( ti_sdo_ipc_interfaces_IGateMPSupport_Module m )
{
    return(xdc_runtime_IGateProvider_Module)m;
}

/* Module_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_interfaces_IGateMPSupport_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_interfaces_IGateMPSupport_Module_upCast

/* Module_downCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Module ti_sdo_ipc_interfaces_IGateMPSupport_Module_downCast( xdc_runtime_IGateProvider_Module m )
{
    const xdc_runtime_Types_Base* b;
    for (b = m->__base; b; b = b->base) {
        if (b == &ti_sdo_ipc_interfaces_IGateMPSupport_Interface__BASE__C) {
            return (ti_sdo_ipc_interfaces_IGateMPSupport_Module)m;
        }
    } return 0;
}

/* Module_from_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_interfaces_IGateMPSupport_Module_from_xdc_runtime_IGateProvider ti_sdo_ipc_interfaces_IGateMPSupport_Module_downCast

/* Handle_upCast */
static inline xdc_runtime_IGateProvider_Handle ti_sdo_ipc_interfaces_IGateMPSupport_Handle_upCast( ti_sdo_ipc_interfaces_IGateMPSupport_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_interfaces_IGateMPSupport_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_interfaces_IGateMPSupport_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_interfaces_IGateMPSupport_Handle ti_sdo_ipc_interfaces_IGateMPSupport_Handle_downCast( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
    const xdc_runtime_Types_Base* b;
    for (b = i2->__fxns->__base; b; b = b->base) {
        if (b == &ti_sdo_ipc_interfaces_IGateMPSupport_Interface__BASE__C) {
            return (ti_sdo_ipc_interfaces_IGateMPSupport_Handle)i;
        }
    } return 0;
}

/* Handle_from_xdc_runtime_IGateProvider */
#define ti_sdo_ipc_interfaces_IGateMPSupport_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_interfaces_IGateMPSupport_Handle_downCast


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_interfaces_IGateMPSupport__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_interfaces_IGateMPSupport__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_interfaces_IGateMPSupport__nolocalnames)

#ifndef ti_sdo_ipc_interfaces_IGateMPSupport__localnames__done
#define ti_sdo_ipc_interfaces_IGateMPSupport__localnames__done

/* module prefix */
#define IGateMPSupport_Instance ti_sdo_ipc_interfaces_IGateMPSupport_Instance
#define IGateMPSupport_Handle ti_sdo_ipc_interfaces_IGateMPSupport_Handle
#define IGateMPSupport_Module ti_sdo_ipc_interfaces_IGateMPSupport_Module
#define IGateMPSupport_Q_BLOCKING ti_sdo_ipc_interfaces_IGateMPSupport_Q_BLOCKING
#define IGateMPSupport_Q_PREEMPTING ti_sdo_ipc_interfaces_IGateMPSupport_Q_PREEMPTING
#define IGateMPSupport_Params ti_sdo_ipc_interfaces_IGateMPSupport_Params
#define IGateMPSupport_query ti_sdo_ipc_interfaces_IGateMPSupport_query
#define IGateMPSupport_query_fxnP ti_sdo_ipc_interfaces_IGateMPSupport_query_fxnP
#define IGateMPSupport_query_FxnT ti_sdo_ipc_interfaces_IGateMPSupport_query_FxnT
#define IGateMPSupport_enter ti_sdo_ipc_interfaces_IGateMPSupport_enter
#define IGateMPSupport_enter_fxnP ti_sdo_ipc_interfaces_IGateMPSupport_enter_fxnP
#define IGateMPSupport_enter_FxnT ti_sdo_ipc_interfaces_IGateMPSupport_enter_FxnT
#define IGateMPSupport_leave ti_sdo_ipc_interfaces_IGateMPSupport_leave
#define IGateMPSupport_leave_fxnP ti_sdo_ipc_interfaces_IGateMPSupport_leave_fxnP
#define IGateMPSupport_leave_FxnT ti_sdo_ipc_interfaces_IGateMPSupport_leave_FxnT
#define IGateMPSupport_getReservedMask ti_sdo_ipc_interfaces_IGateMPSupport_getReservedMask
#define IGateMPSupport_getReservedMask_fxnP ti_sdo_ipc_interfaces_IGateMPSupport_getReservedMask_fxnP
#define IGateMPSupport_getReservedMask_FxnT ti_sdo_ipc_interfaces_IGateMPSupport_getReservedMask_FxnT
#define IGateMPSupport_sharedMemReq ti_sdo_ipc_interfaces_IGateMPSupport_sharedMemReq
#define IGateMPSupport_sharedMemReq_fxnP ti_sdo_ipc_interfaces_IGateMPSupport_sharedMemReq_fxnP
#define IGateMPSupport_sharedMemReq_FxnT ti_sdo_ipc_interfaces_IGateMPSupport_sharedMemReq_FxnT
#define IGateMPSupport_Module_name ti_sdo_ipc_interfaces_IGateMPSupport_Module_name
#define IGateMPSupport_create ti_sdo_ipc_interfaces_IGateMPSupport_create
#define IGateMPSupport_delete ti_sdo_ipc_interfaces_IGateMPSupport_delete
#define IGateMPSupport_Handle_label ti_sdo_ipc_interfaces_IGateMPSupport_Handle_label
#define IGateMPSupport_Handle_to_Module ti_sdo_ipc_interfaces_IGateMPSupport_Handle_to_Module
#define IGateMPSupport_Module_upCast ti_sdo_ipc_interfaces_IGateMPSupport_Module_upCast
#define IGateMPSupport_Module_to_xdc_runtime_IGateProvider ti_sdo_ipc_interfaces_IGateMPSupport_Module_to_xdc_runtime_IGateProvider
#define IGateMPSupport_Module_downCast ti_sdo_ipc_interfaces_IGateMPSupport_Module_downCast
#define IGateMPSupport_Module_from_xdc_runtime_IGateProvider ti_sdo_ipc_interfaces_IGateMPSupport_Module_from_xdc_runtime_IGateProvider
#define IGateMPSupport_Handle_upCast ti_sdo_ipc_interfaces_IGateMPSupport_Handle_upCast
#define IGateMPSupport_Handle_to_xdc_runtime_IGateProvider ti_sdo_ipc_interfaces_IGateMPSupport_Handle_to_xdc_runtime_IGateProvider
#define IGateMPSupport_Handle_downCast ti_sdo_ipc_interfaces_IGateMPSupport_Handle_downCast
#define IGateMPSupport_Handle_from_xdc_runtime_IGateProvider ti_sdo_ipc_interfaces_IGateMPSupport_Handle_from_xdc_runtime_IGateProvider

#endif /* ti_sdo_ipc_interfaces_IGateMPSupport__localnames__done */
#endif
