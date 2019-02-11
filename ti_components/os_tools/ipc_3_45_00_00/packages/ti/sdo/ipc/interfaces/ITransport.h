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
 *     PER-INSTANCE TYPES
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

#ifndef ti_sdo_ipc_interfaces_ITransport__include
#define ti_sdo_ipc_interfaces_ITransport__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_interfaces_ITransport__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_interfaces_ITransport___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/interfaces/package/package.defs.h>

#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_interfaces_ITransport_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_interfaces_ITransport_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base ti_sdo_ipc_interfaces_ITransport_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
xdc__CODESECT(ti_sdo_ipc_interfaces_ITransport_create, "ti_sdo_ipc_interfaces_ITransport_create")
__extern ti_sdo_ipc_interfaces_ITransport_Handle ti_sdo_ipc_interfaces_ITransport_create(ti_sdo_ipc_interfaces_ITransport_Module, const ti_sdo_ipc_interfaces_ITransport_Params *, xdc_runtime_Error_Block *__eb);

/* delete */
xdc__CODESECT(ti_sdo_ipc_interfaces_ITransport_delete, "ti_sdo_ipc_interfaces_ITransport_delete")
__extern xdc_Void ti_sdo_ipc_interfaces_ITransport_delete(ti_sdo_ipc_interfaces_ITransport_Handle *);

/* Handle_to_Module */
static inline ti_sdo_ipc_interfaces_ITransport_Module ti_sdo_ipc_interfaces_ITransport_Handle_to_Module( ti_sdo_ipc_interfaces_ITransport_Handle inst )
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_interfaces_ITransport_Handle_label( ti_sdo_ipc_interfaces_ITransport_Handle inst, xdc_runtime_Types_Label *lab )
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId ti_sdo_ipc_interfaces_ITransport_Module_id( ti_sdo_ipc_interfaces_ITransport_Module mod )
{
    return mod->__sysp->__mid;
}


/*
 * ======== FUNCTION SELECTORS ========
 */


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_interfaces_ITransport__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_interfaces_ITransport__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_interfaces_ITransport__nolocalnames)

#ifndef ti_sdo_ipc_interfaces_ITransport__localnames__done
#define ti_sdo_ipc_interfaces_ITransport__localnames__done

/* module prefix */
#define ITransport_Instance ti_sdo_ipc_interfaces_ITransport_Instance
#define ITransport_Handle ti_sdo_ipc_interfaces_ITransport_Handle
#define ITransport_Module ti_sdo_ipc_interfaces_ITransport_Module
#define ITransport_Params ti_sdo_ipc_interfaces_ITransport_Params
#define ITransport_Module_name ti_sdo_ipc_interfaces_ITransport_Module_name
#define ITransport_delete ti_sdo_ipc_interfaces_ITransport_delete
#define ITransport_Handle_label ti_sdo_ipc_interfaces_ITransport_Handle_label
#define ITransport_Handle_to_Module ti_sdo_ipc_interfaces_ITransport_Handle_to_Module

#endif /* ti_sdo_ipc_interfaces_ITransport__localnames__done */
#endif
