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
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_sdo_ipc_interfaces_ITransportSetup__include
#define ti_sdo_ipc_interfaces_ITransportSetup__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_interfaces_ITransportSetup__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_interfaces_ITransportSetup___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sdo/ipc/interfaces/package/package.defs.h>

#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_interfaces_ITransportSetup_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*attach)(xdc_UInt16, xdc_Ptr);
    xdc_Int (*detach)(xdc_UInt16);
    xdc_Bool (*isRegistered)(xdc_UInt16);
    xdc_SizeT (*sharedMemReq)(xdc_Ptr);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base ti_sdo_ipc_interfaces_ITransportSetup_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* Module_id */
static inline xdc_runtime_Types_ModuleId ti_sdo_ipc_interfaces_ITransportSetup_Module_id( ti_sdo_ipc_interfaces_ITransportSetup_Module mod )
{
    return mod->__sysp->__mid;
}

/* attach */
static inline xdc_Int ti_sdo_ipc_interfaces_ITransportSetup_attach( ti_sdo_ipc_interfaces_ITransportSetup_Module __inst, xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr )
{
    return __inst->attach(remoteProcId, sharedAddr);
}

/* detach */
static inline xdc_Int ti_sdo_ipc_interfaces_ITransportSetup_detach( ti_sdo_ipc_interfaces_ITransportSetup_Module __inst, xdc_UInt16 remoteProcId )
{
    return __inst->detach(remoteProcId);
}

/* isRegistered */
static inline xdc_Bool ti_sdo_ipc_interfaces_ITransportSetup_isRegistered( ti_sdo_ipc_interfaces_ITransportSetup_Module __inst, xdc_UInt16 remoteProcId )
{
    return __inst->isRegistered(remoteProcId);
}

/* sharedMemReq */
static inline xdc_SizeT ti_sdo_ipc_interfaces_ITransportSetup_sharedMemReq( ti_sdo_ipc_interfaces_ITransportSetup_Module __inst, xdc_Ptr sharedAddr )
{
    return __inst->sharedMemReq(sharedAddr);
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

/* attach_{FxnT,fxnP} */
typedef xdc_Int (*ti_sdo_ipc_interfaces_ITransportSetup_attach_FxnT)(xdc_UInt16, xdc_Ptr);
static inline ti_sdo_ipc_interfaces_ITransportSetup_attach_FxnT ti_sdo_ipc_interfaces_ITransportSetup_attach_fxnP( ti_sdo_ipc_interfaces_ITransportSetup_Module __inst )
{
    return (ti_sdo_ipc_interfaces_ITransportSetup_attach_FxnT)__inst->attach;
}

/* detach_{FxnT,fxnP} */
typedef xdc_Int (*ti_sdo_ipc_interfaces_ITransportSetup_detach_FxnT)(xdc_UInt16);
static inline ti_sdo_ipc_interfaces_ITransportSetup_detach_FxnT ti_sdo_ipc_interfaces_ITransportSetup_detach_fxnP( ti_sdo_ipc_interfaces_ITransportSetup_Module __inst )
{
    return (ti_sdo_ipc_interfaces_ITransportSetup_detach_FxnT)__inst->detach;
}

/* isRegistered_{FxnT,fxnP} */
typedef xdc_Bool (*ti_sdo_ipc_interfaces_ITransportSetup_isRegistered_FxnT)(xdc_UInt16);
static inline ti_sdo_ipc_interfaces_ITransportSetup_isRegistered_FxnT ti_sdo_ipc_interfaces_ITransportSetup_isRegistered_fxnP( ti_sdo_ipc_interfaces_ITransportSetup_Module __inst )
{
    return (ti_sdo_ipc_interfaces_ITransportSetup_isRegistered_FxnT)__inst->isRegistered;
}

/* sharedMemReq_{FxnT,fxnP} */
typedef xdc_SizeT (*ti_sdo_ipc_interfaces_ITransportSetup_sharedMemReq_FxnT)(xdc_Ptr);
static inline ti_sdo_ipc_interfaces_ITransportSetup_sharedMemReq_FxnT ti_sdo_ipc_interfaces_ITransportSetup_sharedMemReq_fxnP( ti_sdo_ipc_interfaces_ITransportSetup_Module __inst )
{
    return (ti_sdo_ipc_interfaces_ITransportSetup_sharedMemReq_FxnT)__inst->sharedMemReq;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_interfaces_ITransportSetup__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_interfaces_ITransportSetup__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_interfaces_ITransportSetup__nolocalnames)

#ifndef ti_sdo_ipc_interfaces_ITransportSetup__localnames__done
#define ti_sdo_ipc_interfaces_ITransportSetup__localnames__done

/* module prefix */
#define ITransportSetup_Module ti_sdo_ipc_interfaces_ITransportSetup_Module
#define ITransportSetup_attach ti_sdo_ipc_interfaces_ITransportSetup_attach
#define ITransportSetup_attach_fxnP ti_sdo_ipc_interfaces_ITransportSetup_attach_fxnP
#define ITransportSetup_attach_FxnT ti_sdo_ipc_interfaces_ITransportSetup_attach_FxnT
#define ITransportSetup_detach ti_sdo_ipc_interfaces_ITransportSetup_detach
#define ITransportSetup_detach_fxnP ti_sdo_ipc_interfaces_ITransportSetup_detach_fxnP
#define ITransportSetup_detach_FxnT ti_sdo_ipc_interfaces_ITransportSetup_detach_FxnT
#define ITransportSetup_isRegistered ti_sdo_ipc_interfaces_ITransportSetup_isRegistered
#define ITransportSetup_isRegistered_fxnP ti_sdo_ipc_interfaces_ITransportSetup_isRegistered_fxnP
#define ITransportSetup_isRegistered_FxnT ti_sdo_ipc_interfaces_ITransportSetup_isRegistered_FxnT
#define ITransportSetup_sharedMemReq ti_sdo_ipc_interfaces_ITransportSetup_sharedMemReq
#define ITransportSetup_sharedMemReq_fxnP ti_sdo_ipc_interfaces_ITransportSetup_sharedMemReq_fxnP
#define ITransportSetup_sharedMemReq_FxnT ti_sdo_ipc_interfaces_ITransportSetup_sharedMemReq_FxnT
#define ITransportSetup_Module_name ti_sdo_ipc_interfaces_ITransportSetup_Module_name

#endif /* ti_sdo_ipc_interfaces_ITransportSetup__localnames__done */
#endif
