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

#ifndef ti_sdo_ipc_interfaces_INotifyDriver__include
#define ti_sdo_ipc_interfaces_INotifyDriver__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_interfaces_INotifyDriver__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_interfaces_INotifyDriver___VERS 160


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
struct ti_sdo_ipc_interfaces_INotifyDriver_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_interfaces_INotifyDriver_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Void (*registerEvent)(void*, xdc_UInt32);
    xdc_Void (*unregisterEvent)(void*, xdc_UInt32);
    xdc_Int (*sendEvent)(void*, xdc_UInt32, xdc_UInt32, xdc_Bool);
    xdc_Void (*disable)(void*);
    xdc_Void (*enable)(void*);
    xdc_Void (*disableEvent)(void*, xdc_UInt32);
    xdc_Void (*enableEvent)(void*, xdc_UInt32);
    xdc_Void (*setNotifyHandle)(void*, xdc_Ptr);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base ti_sdo_ipc_interfaces_INotifyDriver_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
xdc__CODESECT(ti_sdo_ipc_interfaces_INotifyDriver_create, "ti_sdo_ipc_interfaces_INotifyDriver_create")
__extern ti_sdo_ipc_interfaces_INotifyDriver_Handle ti_sdo_ipc_interfaces_INotifyDriver_create(ti_sdo_ipc_interfaces_INotifyDriver_Module, const ti_sdo_ipc_interfaces_INotifyDriver_Params *, xdc_runtime_Error_Block *__eb);

/* delete */
xdc__CODESECT(ti_sdo_ipc_interfaces_INotifyDriver_delete, "ti_sdo_ipc_interfaces_INotifyDriver_delete")
__extern xdc_Void ti_sdo_ipc_interfaces_INotifyDriver_delete(ti_sdo_ipc_interfaces_INotifyDriver_Handle *);

/* Handle_to_Module */
static inline ti_sdo_ipc_interfaces_INotifyDriver_Module ti_sdo_ipc_interfaces_INotifyDriver_Handle_to_Module( ti_sdo_ipc_interfaces_INotifyDriver_Handle inst )
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_interfaces_INotifyDriver_Handle_label( ti_sdo_ipc_interfaces_INotifyDriver_Handle inst, xdc_runtime_Types_Label *lab )
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId ti_sdo_ipc_interfaces_INotifyDriver_Module_id( ti_sdo_ipc_interfaces_INotifyDriver_Module mod )
{
    return mod->__sysp->__mid;
}

/* registerEvent */
static inline xdc_Void ti_sdo_ipc_interfaces_INotifyDriver_registerEvent( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst, xdc_UInt32 eventId )
{
    __inst->__fxns->registerEvent((void*)__inst, eventId);
}

/* unregisterEvent */
static inline xdc_Void ti_sdo_ipc_interfaces_INotifyDriver_unregisterEvent( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst, xdc_UInt32 eventId )
{
    __inst->__fxns->unregisterEvent((void*)__inst, eventId);
}

/* sendEvent */
static inline xdc_Int ti_sdo_ipc_interfaces_INotifyDriver_sendEvent( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst, xdc_UInt32 eventId, xdc_UInt32 payload, xdc_Bool waitClear )
{
    return __inst->__fxns->sendEvent((void*)__inst, eventId, payload, waitClear);
}

/* disable */
static inline xdc_Void ti_sdo_ipc_interfaces_INotifyDriver_disable( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst )
{
    __inst->__fxns->disable((void*)__inst);
}

/* enable */
static inline xdc_Void ti_sdo_ipc_interfaces_INotifyDriver_enable( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst )
{
    __inst->__fxns->enable((void*)__inst);
}

/* disableEvent */
static inline xdc_Void ti_sdo_ipc_interfaces_INotifyDriver_disableEvent( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst, xdc_UInt32 eventId )
{
    __inst->__fxns->disableEvent((void*)__inst, eventId);
}

/* enableEvent */
static inline xdc_Void ti_sdo_ipc_interfaces_INotifyDriver_enableEvent( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst, xdc_UInt32 eventId )
{
    __inst->__fxns->enableEvent((void*)__inst, eventId);
}

/* setNotifyHandle */
static inline xdc_Void ti_sdo_ipc_interfaces_INotifyDriver_setNotifyHandle( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst, xdc_Ptr driverHandle )
{
    __inst->__fxns->setNotifyHandle((void*)__inst, driverHandle);
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

/* registerEvent_{FxnT,fxnP} */
typedef xdc_Void (*ti_sdo_ipc_interfaces_INotifyDriver_registerEvent_FxnT)(xdc_Void *, xdc_UInt32);
static inline ti_sdo_ipc_interfaces_INotifyDriver_registerEvent_FxnT ti_sdo_ipc_interfaces_INotifyDriver_registerEvent_fxnP( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_registerEvent_FxnT)__inst->__fxns->registerEvent;
}

/* unregisterEvent_{FxnT,fxnP} */
typedef xdc_Void (*ti_sdo_ipc_interfaces_INotifyDriver_unregisterEvent_FxnT)(xdc_Void *, xdc_UInt32);
static inline ti_sdo_ipc_interfaces_INotifyDriver_unregisterEvent_FxnT ti_sdo_ipc_interfaces_INotifyDriver_unregisterEvent_fxnP( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_unregisterEvent_FxnT)__inst->__fxns->unregisterEvent;
}

/* sendEvent_{FxnT,fxnP} */
typedef xdc_Int (*ti_sdo_ipc_interfaces_INotifyDriver_sendEvent_FxnT)(xdc_Void *, xdc_UInt32, xdc_UInt32, xdc_Bool);
static inline ti_sdo_ipc_interfaces_INotifyDriver_sendEvent_FxnT ti_sdo_ipc_interfaces_INotifyDriver_sendEvent_fxnP( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_sendEvent_FxnT)__inst->__fxns->sendEvent;
}

/* disable_{FxnT,fxnP} */
typedef xdc_Void (*ti_sdo_ipc_interfaces_INotifyDriver_disable_FxnT)(xdc_Void *);
static inline ti_sdo_ipc_interfaces_INotifyDriver_disable_FxnT ti_sdo_ipc_interfaces_INotifyDriver_disable_fxnP( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_disable_FxnT)__inst->__fxns->disable;
}

/* enable_{FxnT,fxnP} */
typedef xdc_Void (*ti_sdo_ipc_interfaces_INotifyDriver_enable_FxnT)(xdc_Void *);
static inline ti_sdo_ipc_interfaces_INotifyDriver_enable_FxnT ti_sdo_ipc_interfaces_INotifyDriver_enable_fxnP( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_enable_FxnT)__inst->__fxns->enable;
}

/* disableEvent_{FxnT,fxnP} */
typedef xdc_Void (*ti_sdo_ipc_interfaces_INotifyDriver_disableEvent_FxnT)(xdc_Void *, xdc_UInt32);
static inline ti_sdo_ipc_interfaces_INotifyDriver_disableEvent_FxnT ti_sdo_ipc_interfaces_INotifyDriver_disableEvent_fxnP( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_disableEvent_FxnT)__inst->__fxns->disableEvent;
}

/* enableEvent_{FxnT,fxnP} */
typedef xdc_Void (*ti_sdo_ipc_interfaces_INotifyDriver_enableEvent_FxnT)(xdc_Void *, xdc_UInt32);
static inline ti_sdo_ipc_interfaces_INotifyDriver_enableEvent_FxnT ti_sdo_ipc_interfaces_INotifyDriver_enableEvent_fxnP( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_enableEvent_FxnT)__inst->__fxns->enableEvent;
}

/* setNotifyHandle_{FxnT,fxnP} */
typedef xdc_Void (*ti_sdo_ipc_interfaces_INotifyDriver_setNotifyHandle_FxnT)(xdc_Void *, xdc_Ptr);
static inline ti_sdo_ipc_interfaces_INotifyDriver_setNotifyHandle_FxnT ti_sdo_ipc_interfaces_INotifyDriver_setNotifyHandle_fxnP( ti_sdo_ipc_interfaces_INotifyDriver_Handle __inst )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_setNotifyHandle_FxnT)__inst->__fxns->setNotifyHandle;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_interfaces_INotifyDriver__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_interfaces_INotifyDriver__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_interfaces_INotifyDriver__nolocalnames)

#ifndef ti_sdo_ipc_interfaces_INotifyDriver__localnames__done
#define ti_sdo_ipc_interfaces_INotifyDriver__localnames__done

/* module prefix */
#define INotifyDriver_Instance ti_sdo_ipc_interfaces_INotifyDriver_Instance
#define INotifyDriver_Handle ti_sdo_ipc_interfaces_INotifyDriver_Handle
#define INotifyDriver_Module ti_sdo_ipc_interfaces_INotifyDriver_Module
#define INotifyDriver_Params ti_sdo_ipc_interfaces_INotifyDriver_Params
#define INotifyDriver_registerEvent ti_sdo_ipc_interfaces_INotifyDriver_registerEvent
#define INotifyDriver_registerEvent_fxnP ti_sdo_ipc_interfaces_INotifyDriver_registerEvent_fxnP
#define INotifyDriver_registerEvent_FxnT ti_sdo_ipc_interfaces_INotifyDriver_registerEvent_FxnT
#define INotifyDriver_unregisterEvent ti_sdo_ipc_interfaces_INotifyDriver_unregisterEvent
#define INotifyDriver_unregisterEvent_fxnP ti_sdo_ipc_interfaces_INotifyDriver_unregisterEvent_fxnP
#define INotifyDriver_unregisterEvent_FxnT ti_sdo_ipc_interfaces_INotifyDriver_unregisterEvent_FxnT
#define INotifyDriver_sendEvent ti_sdo_ipc_interfaces_INotifyDriver_sendEvent
#define INotifyDriver_sendEvent_fxnP ti_sdo_ipc_interfaces_INotifyDriver_sendEvent_fxnP
#define INotifyDriver_sendEvent_FxnT ti_sdo_ipc_interfaces_INotifyDriver_sendEvent_FxnT
#define INotifyDriver_disable ti_sdo_ipc_interfaces_INotifyDriver_disable
#define INotifyDriver_disable_fxnP ti_sdo_ipc_interfaces_INotifyDriver_disable_fxnP
#define INotifyDriver_disable_FxnT ti_sdo_ipc_interfaces_INotifyDriver_disable_FxnT
#define INotifyDriver_enable ti_sdo_ipc_interfaces_INotifyDriver_enable
#define INotifyDriver_enable_fxnP ti_sdo_ipc_interfaces_INotifyDriver_enable_fxnP
#define INotifyDriver_enable_FxnT ti_sdo_ipc_interfaces_INotifyDriver_enable_FxnT
#define INotifyDriver_disableEvent ti_sdo_ipc_interfaces_INotifyDriver_disableEvent
#define INotifyDriver_disableEvent_fxnP ti_sdo_ipc_interfaces_INotifyDriver_disableEvent_fxnP
#define INotifyDriver_disableEvent_FxnT ti_sdo_ipc_interfaces_INotifyDriver_disableEvent_FxnT
#define INotifyDriver_enableEvent ti_sdo_ipc_interfaces_INotifyDriver_enableEvent
#define INotifyDriver_enableEvent_fxnP ti_sdo_ipc_interfaces_INotifyDriver_enableEvent_fxnP
#define INotifyDriver_enableEvent_FxnT ti_sdo_ipc_interfaces_INotifyDriver_enableEvent_FxnT
#define INotifyDriver_setNotifyHandle ti_sdo_ipc_interfaces_INotifyDriver_setNotifyHandle
#define INotifyDriver_setNotifyHandle_fxnP ti_sdo_ipc_interfaces_INotifyDriver_setNotifyHandle_fxnP
#define INotifyDriver_setNotifyHandle_FxnT ti_sdo_ipc_interfaces_INotifyDriver_setNotifyHandle_FxnT
#define INotifyDriver_Module_name ti_sdo_ipc_interfaces_INotifyDriver_Module_name
#define INotifyDriver_delete ti_sdo_ipc_interfaces_INotifyDriver_delete
#define INotifyDriver_Handle_label ti_sdo_ipc_interfaces_INotifyDriver_Handle_label
#define INotifyDriver_Handle_to_Module ti_sdo_ipc_interfaces_INotifyDriver_Handle_to_Module

#endif /* ti_sdo_ipc_interfaces_INotifyDriver__localnames__done */
#endif
