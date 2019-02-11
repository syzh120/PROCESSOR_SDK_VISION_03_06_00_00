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

#ifndef ti_sdo_ipc_interfaces_INotifySetup__include
#define ti_sdo_ipc_interfaces_INotifySetup__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_interfaces_INotifySetup__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_interfaces_INotifySetup___VERS 160


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
struct ti_sdo_ipc_interfaces_INotifySetup_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*attach)(xdc_UInt16, xdc_Ptr);
    xdc_SizeT (*sharedMemReq)(xdc_UInt16, xdc_Ptr);
    xdc_UInt16 (*numIntLines)(xdc_UInt16);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base ti_sdo_ipc_interfaces_INotifySetup_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* Module_id */
static inline xdc_runtime_Types_ModuleId ti_sdo_ipc_interfaces_INotifySetup_Module_id( ti_sdo_ipc_interfaces_INotifySetup_Module mod )
{
    return mod->__sysp->__mid;
}

/* attach */
static inline xdc_Int ti_sdo_ipc_interfaces_INotifySetup_attach( ti_sdo_ipc_interfaces_INotifySetup_Module __inst, xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr )
{
    return __inst->attach(remoteProcId, sharedAddr);
}

/* sharedMemReq */
static inline xdc_SizeT ti_sdo_ipc_interfaces_INotifySetup_sharedMemReq( ti_sdo_ipc_interfaces_INotifySetup_Module __inst, xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr )
{
    return __inst->sharedMemReq(remoteProcId, sharedAddr);
}

/* numIntLines */
static inline xdc_UInt16 ti_sdo_ipc_interfaces_INotifySetup_numIntLines( ti_sdo_ipc_interfaces_INotifySetup_Module __inst, xdc_UInt16 remoteProcId )
{
    return __inst->numIntLines(remoteProcId);
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
typedef xdc_Int (*ti_sdo_ipc_interfaces_INotifySetup_attach_FxnT)(xdc_UInt16, xdc_Ptr);
static inline ti_sdo_ipc_interfaces_INotifySetup_attach_FxnT ti_sdo_ipc_interfaces_INotifySetup_attach_fxnP( ti_sdo_ipc_interfaces_INotifySetup_Module __inst )
{
    return (ti_sdo_ipc_interfaces_INotifySetup_attach_FxnT)__inst->attach;
}

/* sharedMemReq_{FxnT,fxnP} */
typedef xdc_SizeT (*ti_sdo_ipc_interfaces_INotifySetup_sharedMemReq_FxnT)(xdc_UInt16, xdc_Ptr);
static inline ti_sdo_ipc_interfaces_INotifySetup_sharedMemReq_FxnT ti_sdo_ipc_interfaces_INotifySetup_sharedMemReq_fxnP( ti_sdo_ipc_interfaces_INotifySetup_Module __inst )
{
    return (ti_sdo_ipc_interfaces_INotifySetup_sharedMemReq_FxnT)__inst->sharedMemReq;
}

/* numIntLines_{FxnT,fxnP} */
typedef xdc_UInt16 (*ti_sdo_ipc_interfaces_INotifySetup_numIntLines_FxnT)(xdc_UInt16);
static inline ti_sdo_ipc_interfaces_INotifySetup_numIntLines_FxnT ti_sdo_ipc_interfaces_INotifySetup_numIntLines_fxnP( ti_sdo_ipc_interfaces_INotifySetup_Module __inst )
{
    return (ti_sdo_ipc_interfaces_INotifySetup_numIntLines_FxnT)__inst->numIntLines;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_interfaces_INotifySetup__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_interfaces_INotifySetup__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_interfaces_INotifySetup__nolocalnames)

#ifndef ti_sdo_ipc_interfaces_INotifySetup__localnames__done
#define ti_sdo_ipc_interfaces_INotifySetup__localnames__done

/* module prefix */
#define INotifySetup_Module ti_sdo_ipc_interfaces_INotifySetup_Module
#define INotifySetup_attach ti_sdo_ipc_interfaces_INotifySetup_attach
#define INotifySetup_attach_fxnP ti_sdo_ipc_interfaces_INotifySetup_attach_fxnP
#define INotifySetup_attach_FxnT ti_sdo_ipc_interfaces_INotifySetup_attach_FxnT
#define INotifySetup_sharedMemReq ti_sdo_ipc_interfaces_INotifySetup_sharedMemReq
#define INotifySetup_sharedMemReq_fxnP ti_sdo_ipc_interfaces_INotifySetup_sharedMemReq_fxnP
#define INotifySetup_sharedMemReq_FxnT ti_sdo_ipc_interfaces_INotifySetup_sharedMemReq_FxnT
#define INotifySetup_numIntLines ti_sdo_ipc_interfaces_INotifySetup_numIntLines
#define INotifySetup_numIntLines_fxnP ti_sdo_ipc_interfaces_INotifySetup_numIntLines_fxnP
#define INotifySetup_numIntLines_FxnT ti_sdo_ipc_interfaces_INotifySetup_numIntLines_FxnT
#define INotifySetup_Module_name ti_sdo_ipc_interfaces_INotifySetup_Module_name

#endif /* ti_sdo_ipc_interfaces_INotifySetup__localnames__done */
#endif
