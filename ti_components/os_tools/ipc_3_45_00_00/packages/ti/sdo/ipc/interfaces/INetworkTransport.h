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
 *     CONVERTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_sdo_ipc_interfaces_INetworkTransport__include
#define ti_sdo_ipc_interfaces_INetworkTransport__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_interfaces_INetworkTransport__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_interfaces_INetworkTransport___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/interfaces/package/package.defs.h>

#include <ti/sdo/ipc/interfaces/ITransport.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_interfaces_INetworkTransport_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_interfaces_INetworkTransport_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*bind)(void*, xdc_UInt32);
    xdc_Int (*unbind)(void*, xdc_UInt32);
    xdc_Bool (*put)(void*, xdc_Ptr);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base ti_sdo_ipc_interfaces_INetworkTransport_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
xdc__CODESECT(ti_sdo_ipc_interfaces_INetworkTransport_create, "ti_sdo_ipc_interfaces_INetworkTransport_create")
__extern ti_sdo_ipc_interfaces_INetworkTransport_Handle ti_sdo_ipc_interfaces_INetworkTransport_create(ti_sdo_ipc_interfaces_INetworkTransport_Module, const ti_sdo_ipc_interfaces_INetworkTransport_Params *, xdc_runtime_Error_Block *__eb);

/* delete */
xdc__CODESECT(ti_sdo_ipc_interfaces_INetworkTransport_delete, "ti_sdo_ipc_interfaces_INetworkTransport_delete")
__extern xdc_Void ti_sdo_ipc_interfaces_INetworkTransport_delete(ti_sdo_ipc_interfaces_INetworkTransport_Handle *);

/* Handle_to_Module */
static inline ti_sdo_ipc_interfaces_INetworkTransport_Module ti_sdo_ipc_interfaces_INetworkTransport_Handle_to_Module( ti_sdo_ipc_interfaces_INetworkTransport_Handle inst )
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_interfaces_INetworkTransport_Handle_label( ti_sdo_ipc_interfaces_INetworkTransport_Handle inst, xdc_runtime_Types_Label *lab )
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId ti_sdo_ipc_interfaces_INetworkTransport_Module_id( ti_sdo_ipc_interfaces_INetworkTransport_Module mod )
{
    return mod->__sysp->__mid;
}

/* bind */
static inline xdc_Int ti_sdo_ipc_interfaces_INetworkTransport_bind( ti_sdo_ipc_interfaces_INetworkTransport_Handle __inst, xdc_UInt32 queueId )
{
    return __inst->__fxns->bind((void*)__inst, queueId);
}

/* unbind */
static inline xdc_Int ti_sdo_ipc_interfaces_INetworkTransport_unbind( ti_sdo_ipc_interfaces_INetworkTransport_Handle __inst, xdc_UInt32 queueId )
{
    return __inst->__fxns->unbind((void*)__inst, queueId);
}

/* put */
static inline xdc_Bool ti_sdo_ipc_interfaces_INetworkTransport_put( ti_sdo_ipc_interfaces_INetworkTransport_Handle __inst, xdc_Ptr msg )
{
    return __inst->__fxns->put((void*)__inst, msg);
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

/* bind_{FxnT,fxnP} */
typedef xdc_Int (*ti_sdo_ipc_interfaces_INetworkTransport_bind_FxnT)(xdc_Void *, xdc_UInt32);
static inline ti_sdo_ipc_interfaces_INetworkTransport_bind_FxnT ti_sdo_ipc_interfaces_INetworkTransport_bind_fxnP( ti_sdo_ipc_interfaces_INetworkTransport_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_INetworkTransport_bind_FxnT)__inst->__fxns->bind;
}

/* unbind_{FxnT,fxnP} */
typedef xdc_Int (*ti_sdo_ipc_interfaces_INetworkTransport_unbind_FxnT)(xdc_Void *, xdc_UInt32);
static inline ti_sdo_ipc_interfaces_INetworkTransport_unbind_FxnT ti_sdo_ipc_interfaces_INetworkTransport_unbind_fxnP( ti_sdo_ipc_interfaces_INetworkTransport_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_INetworkTransport_unbind_FxnT)__inst->__fxns->unbind;
}

/* put_{FxnT,fxnP} */
typedef xdc_Bool (*ti_sdo_ipc_interfaces_INetworkTransport_put_FxnT)(xdc_Void *, xdc_Ptr);
static inline ti_sdo_ipc_interfaces_INetworkTransport_put_FxnT ti_sdo_ipc_interfaces_INetworkTransport_put_fxnP( ti_sdo_ipc_interfaces_INetworkTransport_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_INetworkTransport_put_FxnT)__inst->__fxns->put;
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_ITransport_Module ti_sdo_ipc_interfaces_INetworkTransport_Module_upCast( ti_sdo_ipc_interfaces_INetworkTransport_Module m )
{
    return(ti_sdo_ipc_interfaces_ITransport_Module)m;
}

/* Module_to_ti_sdo_ipc_interfaces_ITransport */
#define ti_sdo_ipc_interfaces_INetworkTransport_Module_to_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_interfaces_INetworkTransport_Module_upCast

/* Module_downCast */
static inline ti_sdo_ipc_interfaces_INetworkTransport_Module ti_sdo_ipc_interfaces_INetworkTransport_Module_downCast( ti_sdo_ipc_interfaces_ITransport_Module m )
{
    const xdc_runtime_Types_Base* b;
    for (b = m->__base; b; b = b->base) {
        if (b == &ti_sdo_ipc_interfaces_INetworkTransport_Interface__BASE__C) {
            return (ti_sdo_ipc_interfaces_INetworkTransport_Module)m;
        }
    } return 0;
}

/* Module_from_ti_sdo_ipc_interfaces_ITransport */
#define ti_sdo_ipc_interfaces_INetworkTransport_Module_from_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_interfaces_INetworkTransport_Module_downCast

/* Handle_upCast */
static inline ti_sdo_ipc_interfaces_ITransport_Handle ti_sdo_ipc_interfaces_INetworkTransport_Handle_upCast( ti_sdo_ipc_interfaces_INetworkTransport_Handle i )
{
    return (ti_sdo_ipc_interfaces_ITransport_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_ITransport */
#define ti_sdo_ipc_interfaces_INetworkTransport_Handle_to_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_interfaces_INetworkTransport_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_interfaces_INetworkTransport_Handle ti_sdo_ipc_interfaces_INetworkTransport_Handle_downCast( ti_sdo_ipc_interfaces_ITransport_Handle i )
{
    ti_sdo_ipc_interfaces_ITransport_Handle i2 = (ti_sdo_ipc_interfaces_ITransport_Handle)i;
    const xdc_runtime_Types_Base* b;
    for (b = i2->__fxns->__base; b; b = b->base) {
        if (b == &ti_sdo_ipc_interfaces_INetworkTransport_Interface__BASE__C) {
            return (ti_sdo_ipc_interfaces_INetworkTransport_Handle)i;
        }
    } return 0;
}

/* Handle_from_ti_sdo_ipc_interfaces_ITransport */
#define ti_sdo_ipc_interfaces_INetworkTransport_Handle_from_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_interfaces_INetworkTransport_Handle_downCast


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_interfaces_INetworkTransport__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_interfaces_INetworkTransport__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_interfaces_INetworkTransport__nolocalnames)

#ifndef ti_sdo_ipc_interfaces_INetworkTransport__localnames__done
#define ti_sdo_ipc_interfaces_INetworkTransport__localnames__done

/* module prefix */
#define INetworkTransport_Instance ti_sdo_ipc_interfaces_INetworkTransport_Instance
#define INetworkTransport_Handle ti_sdo_ipc_interfaces_INetworkTransport_Handle
#define INetworkTransport_Module ti_sdo_ipc_interfaces_INetworkTransport_Module
#define INetworkTransport_Params ti_sdo_ipc_interfaces_INetworkTransport_Params
#define INetworkTransport_bind ti_sdo_ipc_interfaces_INetworkTransport_bind
#define INetworkTransport_bind_fxnP ti_sdo_ipc_interfaces_INetworkTransport_bind_fxnP
#define INetworkTransport_bind_FxnT ti_sdo_ipc_interfaces_INetworkTransport_bind_FxnT
#define INetworkTransport_unbind ti_sdo_ipc_interfaces_INetworkTransport_unbind
#define INetworkTransport_unbind_fxnP ti_sdo_ipc_interfaces_INetworkTransport_unbind_fxnP
#define INetworkTransport_unbind_FxnT ti_sdo_ipc_interfaces_INetworkTransport_unbind_FxnT
#define INetworkTransport_put ti_sdo_ipc_interfaces_INetworkTransport_put
#define INetworkTransport_put_fxnP ti_sdo_ipc_interfaces_INetworkTransport_put_fxnP
#define INetworkTransport_put_FxnT ti_sdo_ipc_interfaces_INetworkTransport_put_FxnT
#define INetworkTransport_Module_name ti_sdo_ipc_interfaces_INetworkTransport_Module_name
#define INetworkTransport_create ti_sdo_ipc_interfaces_INetworkTransport_create
#define INetworkTransport_delete ti_sdo_ipc_interfaces_INetworkTransport_delete
#define INetworkTransport_Handle_label ti_sdo_ipc_interfaces_INetworkTransport_Handle_label
#define INetworkTransport_Handle_to_Module ti_sdo_ipc_interfaces_INetworkTransport_Handle_to_Module
#define INetworkTransport_Module_upCast ti_sdo_ipc_interfaces_INetworkTransport_Module_upCast
#define INetworkTransport_Module_to_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_interfaces_INetworkTransport_Module_to_ti_sdo_ipc_interfaces_ITransport
#define INetworkTransport_Module_downCast ti_sdo_ipc_interfaces_INetworkTransport_Module_downCast
#define INetworkTransport_Module_from_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_interfaces_INetworkTransport_Module_from_ti_sdo_ipc_interfaces_ITransport
#define INetworkTransport_Handle_upCast ti_sdo_ipc_interfaces_INetworkTransport_Handle_upCast
#define INetworkTransport_Handle_to_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_interfaces_INetworkTransport_Handle_to_ti_sdo_ipc_interfaces_ITransport
#define INetworkTransport_Handle_downCast ti_sdo_ipc_interfaces_INetworkTransport_Handle_downCast
#define INetworkTransport_Handle_from_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_interfaces_INetworkTransport_Handle_from_ti_sdo_ipc_interfaces_ITransport

#endif /* ti_sdo_ipc_interfaces_INetworkTransport__localnames__done */
#endif
