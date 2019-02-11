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
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_sdo_utils_INameServerRemote__include
#define ti_sdo_utils_INameServerRemote__include

#ifndef __nested__
#define __nested__
#define ti_sdo_utils_INameServerRemote__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_utils_INameServerRemote___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/utils/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/IModule.h>
#include <xdc/runtime/knl/ISync.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Status */
enum ti_sdo_utils_INameServerRemote_Status {
    ti_sdo_utils_INameServerRemote_S_SUCCESS = 0,
    ti_sdo_utils_INameServerRemote_E_FAIL = -1,
    ti_sdo_utils_INameServerRemote_E_ERROR = -2
};
typedef enum ti_sdo_utils_INameServerRemote_Status ti_sdo_utils_INameServerRemote_Status;


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_utils_INameServerRemote_Args__create {
    xdc_UInt16 procId;
} ti_sdo_utils_INameServerRemote_Args__create;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_utils_INameServerRemote_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_utils_INameServerRemote_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*attach)(xdc_UInt16, xdc_Ptr);
    xdc_Int (*detach)(xdc_UInt16);
    xdc_SizeT (*sharedMemReq)(xdc_Ptr);
    xdc_Int (*get)(void*, xdc_String, xdc_String, xdc_Ptr, xdc_UInt32*, xdc_runtime_knl_ISync_Handle, xdc_runtime_Error_Block*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base ti_sdo_utils_INameServerRemote_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
xdc__CODESECT(ti_sdo_utils_INameServerRemote_create, "ti_sdo_utils_INameServerRemote_create")
__extern ti_sdo_utils_INameServerRemote_Handle ti_sdo_utils_INameServerRemote_create(ti_sdo_utils_INameServerRemote_Module, xdc_UInt16 procId, const ti_sdo_utils_INameServerRemote_Params *, xdc_runtime_Error_Block *__eb);

/* delete */
xdc__CODESECT(ti_sdo_utils_INameServerRemote_delete, "ti_sdo_utils_INameServerRemote_delete")
__extern xdc_Void ti_sdo_utils_INameServerRemote_delete(ti_sdo_utils_INameServerRemote_Handle *);

/* Handle_to_Module */
static inline ti_sdo_utils_INameServerRemote_Module ti_sdo_utils_INameServerRemote_Handle_to_Module( ti_sdo_utils_INameServerRemote_Handle inst )
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_utils_INameServerRemote_Handle_label( ti_sdo_utils_INameServerRemote_Handle inst, xdc_runtime_Types_Label *lab )
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId ti_sdo_utils_INameServerRemote_Module_id( ti_sdo_utils_INameServerRemote_Module mod )
{
    return mod->__sysp->__mid;
}

/* attach */
static inline xdc_Int ti_sdo_utils_INameServerRemote_attach( ti_sdo_utils_INameServerRemote_Module __inst, xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr )
{
    return __inst->attach(remoteProcId, sharedAddr);
}

/* detach */
static inline xdc_Int ti_sdo_utils_INameServerRemote_detach( ti_sdo_utils_INameServerRemote_Module __inst, xdc_UInt16 remoteProcId )
{
    return __inst->detach(remoteProcId);
}

/* sharedMemReq */
static inline xdc_SizeT ti_sdo_utils_INameServerRemote_sharedMemReq( ti_sdo_utils_INameServerRemote_Module __inst, xdc_Ptr sharedAddr )
{
    return __inst->sharedMemReq(sharedAddr);
}

/* get */
static inline xdc_Int ti_sdo_utils_INameServerRemote_get( ti_sdo_utils_INameServerRemote_Handle __inst, xdc_String instanceName, xdc_String name, xdc_Ptr value, xdc_UInt32 *valueLen, xdc_runtime_knl_ISync_Handle syncHandle, xdc_runtime_Error_Block *eb )
{
    return __inst->__fxns->get((void*)__inst, instanceName, name, value, valueLen, syncHandle, eb);
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
typedef xdc_Int (*ti_sdo_utils_INameServerRemote_attach_FxnT)(xdc_UInt16, xdc_Ptr);
static inline ti_sdo_utils_INameServerRemote_attach_FxnT ti_sdo_utils_INameServerRemote_attach_fxnP( ti_sdo_utils_INameServerRemote_Module __inst )
{
    return (ti_sdo_utils_INameServerRemote_attach_FxnT)__inst->attach;
}

/* detach_{FxnT,fxnP} */
typedef xdc_Int (*ti_sdo_utils_INameServerRemote_detach_FxnT)(xdc_UInt16);
static inline ti_sdo_utils_INameServerRemote_detach_FxnT ti_sdo_utils_INameServerRemote_detach_fxnP( ti_sdo_utils_INameServerRemote_Module __inst )
{
    return (ti_sdo_utils_INameServerRemote_detach_FxnT)__inst->detach;
}

/* sharedMemReq_{FxnT,fxnP} */
typedef xdc_SizeT (*ti_sdo_utils_INameServerRemote_sharedMemReq_FxnT)(xdc_Ptr);
static inline ti_sdo_utils_INameServerRemote_sharedMemReq_FxnT ti_sdo_utils_INameServerRemote_sharedMemReq_fxnP( ti_sdo_utils_INameServerRemote_Module __inst )
{
    return (ti_sdo_utils_INameServerRemote_sharedMemReq_FxnT)__inst->sharedMemReq;
}

/* get_{FxnT,fxnP} */
typedef xdc_Int (*ti_sdo_utils_INameServerRemote_get_FxnT)(xdc_Void *, xdc_String, xdc_String, xdc_Ptr, xdc_UInt32*, xdc_runtime_knl_ISync_Handle, xdc_runtime_Error_Block*);
static inline ti_sdo_utils_INameServerRemote_get_FxnT ti_sdo_utils_INameServerRemote_get_fxnP( ti_sdo_utils_INameServerRemote_Handle __inst )
{
    return (ti_sdo_utils_INameServerRemote_get_FxnT)__inst->__fxns->get;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_utils_INameServerRemote__top__
#undef __nested__
#endif

#endif /* ti_sdo_utils_INameServerRemote__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_utils_INameServerRemote__nolocalnames)

#ifndef ti_sdo_utils_INameServerRemote__localnames__done
#define ti_sdo_utils_INameServerRemote__localnames__done

/* module prefix */
#define INameServerRemote_Instance ti_sdo_utils_INameServerRemote_Instance
#define INameServerRemote_Handle ti_sdo_utils_INameServerRemote_Handle
#define INameServerRemote_Module ti_sdo_utils_INameServerRemote_Module
#define INameServerRemote_Status ti_sdo_utils_INameServerRemote_Status
#define INameServerRemote_S_SUCCESS ti_sdo_utils_INameServerRemote_S_SUCCESS
#define INameServerRemote_E_FAIL ti_sdo_utils_INameServerRemote_E_FAIL
#define INameServerRemote_E_ERROR ti_sdo_utils_INameServerRemote_E_ERROR
#define INameServerRemote_Params ti_sdo_utils_INameServerRemote_Params
#define INameServerRemote_attach ti_sdo_utils_INameServerRemote_attach
#define INameServerRemote_attach_fxnP ti_sdo_utils_INameServerRemote_attach_fxnP
#define INameServerRemote_attach_FxnT ti_sdo_utils_INameServerRemote_attach_FxnT
#define INameServerRemote_detach ti_sdo_utils_INameServerRemote_detach
#define INameServerRemote_detach_fxnP ti_sdo_utils_INameServerRemote_detach_fxnP
#define INameServerRemote_detach_FxnT ti_sdo_utils_INameServerRemote_detach_FxnT
#define INameServerRemote_sharedMemReq ti_sdo_utils_INameServerRemote_sharedMemReq
#define INameServerRemote_sharedMemReq_fxnP ti_sdo_utils_INameServerRemote_sharedMemReq_fxnP
#define INameServerRemote_sharedMemReq_FxnT ti_sdo_utils_INameServerRemote_sharedMemReq_FxnT
#define INameServerRemote_get ti_sdo_utils_INameServerRemote_get
#define INameServerRemote_get_fxnP ti_sdo_utils_INameServerRemote_get_fxnP
#define INameServerRemote_get_FxnT ti_sdo_utils_INameServerRemote_get_FxnT
#define INameServerRemote_Module_name ti_sdo_utils_INameServerRemote_Module_name
#define INameServerRemote_create ti_sdo_utils_INameServerRemote_create
#define INameServerRemote_delete ti_sdo_utils_INameServerRemote_delete
#define INameServerRemote_Handle_label ti_sdo_utils_INameServerRemote_Handle_label
#define INameServerRemote_Handle_to_Module ti_sdo_utils_INameServerRemote_Handle_to_Module

#endif /* ti_sdo_utils_INameServerRemote__localnames__done */
#endif
