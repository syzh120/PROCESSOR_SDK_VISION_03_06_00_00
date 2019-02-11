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

#ifndef ti_sdo_ipc_transports_TransportShmCirc__include
#define ti_sdo_ipc_transports_TransportShmCirc__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_transports_TransportShmCirc__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_transports_TransportShmCirc___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/transports/package/package.defs.h>

#include <ti/sdo/utils/MultiProc.h>
#include <ti/sdo/ipc/Ipc.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sdo/ipc/interfaces/IMessageQTransport.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Status */
typedef ti_sdo_ipc_interfaces_IMessageQTransport_Status ti_sdo_ipc_transports_TransportShmCirc_Status;

/* Reason */
typedef ti_sdo_ipc_interfaces_IMessageQTransport_Reason ti_sdo_ipc_transports_TransportShmCirc_Reason;

/* ErrFxn */
typedef ti_sdo_ipc_interfaces_IMessageQTransport_ErrFxn ti_sdo_ipc_transports_TransportShmCirc_ErrFxn;

/* S_SUCCESS */
#define ti_sdo_ipc_transports_TransportShmCirc_S_SUCCESS ti_sdo_ipc_interfaces_IMessageQTransport_S_SUCCESS

/* E_FAIL */
#define ti_sdo_ipc_transports_TransportShmCirc_E_FAIL ti_sdo_ipc_interfaces_IMessageQTransport_E_FAIL

/* E_ERROR */
#define ti_sdo_ipc_transports_TransportShmCirc_E_ERROR ti_sdo_ipc_interfaces_IMessageQTransport_E_ERROR

/* Reason_FAILEDPUT */
#define ti_sdo_ipc_transports_TransportShmCirc_Reason_FAILEDPUT ti_sdo_ipc_interfaces_IMessageQTransport_Reason_FAILEDPUT

/* Reason_INTERNALERR */
#define ti_sdo_ipc_transports_TransportShmCirc_Reason_INTERNALERR ti_sdo_ipc_interfaces_IMessageQTransport_Reason_INTERNALERR

/* Reason_PHYSICALERR */
#define ti_sdo_ipc_transports_TransportShmCirc_Reason_PHYSICALERR ti_sdo_ipc_interfaces_IMessageQTransport_Reason_PHYSICALERR

/* Reason_FAILEDALLOC */
#define ti_sdo_ipc_transports_TransportShmCirc_Reason_FAILEDALLOC ti_sdo_ipc_interfaces_IMessageQTransport_Reason_FAILEDALLOC


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_transports_TransportShmCirc_Args__create {
    xdc_UInt16 procId;
} ti_sdo_ipc_transports_TransportShmCirc_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_transports_TransportShmCirc_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__diagsEnabled ti_sdo_ipc_transports_TransportShmCirc_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_transports_TransportShmCirc_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__diagsIncluded ti_sdo_ipc_transports_TransportShmCirc_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_transports_TransportShmCirc_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__diagsMask ti_sdo_ipc_transports_TransportShmCirc_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_transports_TransportShmCirc_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__gateObj ti_sdo_ipc_transports_TransportShmCirc_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_transports_TransportShmCirc_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__gatePrms ti_sdo_ipc_transports_TransportShmCirc_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_transports_TransportShmCirc_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__id ti_sdo_ipc_transports_TransportShmCirc_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerDefined ti_sdo_ipc_transports_TransportShmCirc_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerObj ti_sdo_ipc_transports_TransportShmCirc_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn0 ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn1 ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn2 ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn4 ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn8 ti_sdo_ipc_transports_TransportShmCirc_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_transports_TransportShmCirc_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Module__startupDoneFxn ti_sdo_ipc_transports_TransportShmCirc_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_transports_TransportShmCirc_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Object__count ti_sdo_ipc_transports_TransportShmCirc_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_transports_TransportShmCirc_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Object__heap ti_sdo_ipc_transports_TransportShmCirc_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_transports_TransportShmCirc_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Object__sizeof ti_sdo_ipc_transports_TransportShmCirc_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_transports_TransportShmCirc_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_Object__table ti_sdo_ipc_transports_TransportShmCirc_Object__table__C;

/* errFxn */
#define ti_sdo_ipc_transports_TransportShmCirc_errFxn (ti_sdo_ipc_transports_TransportShmCirc_errFxn__C)
typedef ti_sdo_ipc_interfaces_IMessageQTransport_ErrFxn CT__ti_sdo_ipc_transports_TransportShmCirc_errFxn;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_errFxn ti_sdo_ipc_transports_TransportShmCirc_errFxn__C;

/* alwaysWriteBackMsg */
#ifdef ti_sdo_ipc_transports_TransportShmCirc_alwaysWriteBackMsg__D
#define ti_sdo_ipc_transports_TransportShmCirc_alwaysWriteBackMsg (ti_sdo_ipc_transports_TransportShmCirc_alwaysWriteBackMsg__D)
#else
#define ti_sdo_ipc_transports_TransportShmCirc_alwaysWriteBackMsg (ti_sdo_ipc_transports_TransportShmCirc_alwaysWriteBackMsg__C)
typedef xdc_Bool CT__ti_sdo_ipc_transports_TransportShmCirc_alwaysWriteBackMsg;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_alwaysWriteBackMsg ti_sdo_ipc_transports_TransportShmCirc_alwaysWriteBackMsg__C;
#endif

/* enableStats */
#ifdef ti_sdo_ipc_transports_TransportShmCirc_enableStats__D
#define ti_sdo_ipc_transports_TransportShmCirc_enableStats (ti_sdo_ipc_transports_TransportShmCirc_enableStats__D)
#else
#define ti_sdo_ipc_transports_TransportShmCirc_enableStats (ti_sdo_ipc_transports_TransportShmCirc_enableStats__C)
typedef xdc_Bool CT__ti_sdo_ipc_transports_TransportShmCirc_enableStats;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_enableStats ti_sdo_ipc_transports_TransportShmCirc_enableStats__C;
#endif

/* notifyEventId */
#ifdef ti_sdo_ipc_transports_TransportShmCirc_notifyEventId__D
#define ti_sdo_ipc_transports_TransportShmCirc_notifyEventId (ti_sdo_ipc_transports_TransportShmCirc_notifyEventId__D)
#else
#define ti_sdo_ipc_transports_TransportShmCirc_notifyEventId (ti_sdo_ipc_transports_TransportShmCirc_notifyEventId__C)
typedef xdc_UInt16 CT__ti_sdo_ipc_transports_TransportShmCirc_notifyEventId;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_notifyEventId ti_sdo_ipc_transports_TransportShmCirc_notifyEventId__C;
#endif

/* numMsgs */
#ifdef ti_sdo_ipc_transports_TransportShmCirc_numMsgs__D
#define ti_sdo_ipc_transports_TransportShmCirc_numMsgs (ti_sdo_ipc_transports_TransportShmCirc_numMsgs__D)
#else
#define ti_sdo_ipc_transports_TransportShmCirc_numMsgs (ti_sdo_ipc_transports_TransportShmCirc_numMsgs__C)
typedef xdc_UInt CT__ti_sdo_ipc_transports_TransportShmCirc_numMsgs;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_numMsgs ti_sdo_ipc_transports_TransportShmCirc_numMsgs__C;
#endif

/* maxIndex */
#ifdef ti_sdo_ipc_transports_TransportShmCirc_maxIndex__D
#define ti_sdo_ipc_transports_TransportShmCirc_maxIndex (ti_sdo_ipc_transports_TransportShmCirc_maxIndex__D)
#else
#define ti_sdo_ipc_transports_TransportShmCirc_maxIndex (ti_sdo_ipc_transports_TransportShmCirc_maxIndex__C)
typedef xdc_UInt CT__ti_sdo_ipc_transports_TransportShmCirc_maxIndex;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_maxIndex ti_sdo_ipc_transports_TransportShmCirc_maxIndex__C;
#endif

/* modIndex */
#ifdef ti_sdo_ipc_transports_TransportShmCirc_modIndex__D
#define ti_sdo_ipc_transports_TransportShmCirc_modIndex (ti_sdo_ipc_transports_TransportShmCirc_modIndex__D)
#else
#define ti_sdo_ipc_transports_TransportShmCirc_modIndex (ti_sdo_ipc_transports_TransportShmCirc_modIndex__C)
typedef xdc_UInt CT__ti_sdo_ipc_transports_TransportShmCirc_modIndex;
__extern __FAR__ const CT__ti_sdo_ipc_transports_TransportShmCirc_modIndex ti_sdo_ipc_transports_TransportShmCirc_modIndex__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_transports_TransportShmCirc_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_UInt priority;
    xdc_Ptr sharedAddr;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_transports_TransportShmCirc_Struct {
    const ti_sdo_ipc_transports_TransportShmCirc_Fxns__ *__fxns;
    xdc_Ptr *__f0;
    xdc_Bits32 *__f1;
    xdc_Bits32 *__f2;
    xdc_Ptr *__f3;
    xdc_Bits32 *__f4;
    xdc_Bits32 *__f5;
    xdc_SizeT __f6;
    xdc_UInt16 __f7;
    xdc_UInt16 __f8;
    xdc_Bool __f9;
    xdc_UInt16 __f10;
    ti_sdo_ipc_Ipc_ObjType __f11;
    ti_sysbios_knl_Swi_Struct __f12;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_transports_TransportShmCirc_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Void (*setErrFxn)(ti_sdo_ipc_interfaces_IMessageQTransport_ErrFxn);
    xdc_Int (*getStatus)(ti_sdo_ipc_transports_TransportShmCirc_Handle);
    xdc_Bool (*put)(ti_sdo_ipc_transports_TransportShmCirc_Handle, xdc_Ptr);
    xdc_Bool (*control)(ti_sdo_ipc_transports_TransportShmCirc_Handle, xdc_UInt, xdc_UArg);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_transports_TransportShmCirc_Fxns__ ti_sdo_ipc_transports_TransportShmCirc_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_transports_TransportShmCirc_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_Instance_init__E, "ti_sdo_ipc_transports_TransportShmCirc_Instance_init")
__extern xdc_Int ti_sdo_ipc_transports_TransportShmCirc_Instance_init__E(ti_sdo_ipc_transports_TransportShmCirc_Object *, xdc_UInt16 procId, const ti_sdo_ipc_transports_TransportShmCirc_Params *, xdc_runtime_Error_Block *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_Instance_finalize__E, "ti_sdo_ipc_transports_TransportShmCirc_Instance_finalize")
__extern void ti_sdo_ipc_transports_TransportShmCirc_Instance_finalize__E( ti_sdo_ipc_transports_TransportShmCirc_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_Handle__label__S, "ti_sdo_ipc_transports_TransportShmCirc_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_transports_TransportShmCirc_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_Module__startupDone__S, "ti_sdo_ipc_transports_TransportShmCirc_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_transports_TransportShmCirc_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_Object__create__S, "ti_sdo_ipc_transports_TransportShmCirc_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_transports_TransportShmCirc_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_create, "ti_sdo_ipc_transports_TransportShmCirc_create")
__extern ti_sdo_ipc_transports_TransportShmCirc_Handle ti_sdo_ipc_transports_TransportShmCirc_create( xdc_UInt16 procId, const ti_sdo_ipc_transports_TransportShmCirc_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_construct, "ti_sdo_ipc_transports_TransportShmCirc_construct")
__extern void ti_sdo_ipc_transports_TransportShmCirc_construct( ti_sdo_ipc_transports_TransportShmCirc_Struct *__obj, xdc_UInt16 procId, const ti_sdo_ipc_transports_TransportShmCirc_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_Object__delete__S, "ti_sdo_ipc_transports_TransportShmCirc_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_transports_TransportShmCirc_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_delete, "ti_sdo_ipc_transports_TransportShmCirc_delete")
__extern void ti_sdo_ipc_transports_TransportShmCirc_delete(ti_sdo_ipc_transports_TransportShmCirc_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_Object__destruct__S, "ti_sdo_ipc_transports_TransportShmCirc_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_transports_TransportShmCirc_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_destruct, "ti_sdo_ipc_transports_TransportShmCirc_destruct")
__extern void ti_sdo_ipc_transports_TransportShmCirc_destruct(ti_sdo_ipc_transports_TransportShmCirc_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_Object__get__S, "ti_sdo_ipc_transports_TransportShmCirc_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_transports_TransportShmCirc_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_Object__first__S, "ti_sdo_ipc_transports_TransportShmCirc_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_transports_TransportShmCirc_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_Object__next__S, "ti_sdo_ipc_transports_TransportShmCirc_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_transports_TransportShmCirc_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_Params__init__S, "ti_sdo_ipc_transports_TransportShmCirc_Params__init__S")
__extern xdc_Void ti_sdo_ipc_transports_TransportShmCirc_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* setErrFxn__E */
#define ti_sdo_ipc_transports_TransportShmCirc_setErrFxn ti_sdo_ipc_transports_TransportShmCirc_setErrFxn__E
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_setErrFxn__E, "ti_sdo_ipc_transports_TransportShmCirc_setErrFxn")
__extern xdc_Void ti_sdo_ipc_transports_TransportShmCirc_setErrFxn__E( ti_sdo_ipc_interfaces_IMessageQTransport_ErrFxn errFxn );

/* getStatus__E */
#define ti_sdo_ipc_transports_TransportShmCirc_getStatus ti_sdo_ipc_transports_TransportShmCirc_getStatus__E
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_getStatus__E, "ti_sdo_ipc_transports_TransportShmCirc_getStatus")
__extern xdc_Int ti_sdo_ipc_transports_TransportShmCirc_getStatus__E( ti_sdo_ipc_transports_TransportShmCirc_Handle __inst );

/* put__E */
#define ti_sdo_ipc_transports_TransportShmCirc_put ti_sdo_ipc_transports_TransportShmCirc_put__E
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_put__E, "ti_sdo_ipc_transports_TransportShmCirc_put")
__extern xdc_Bool ti_sdo_ipc_transports_TransportShmCirc_put__E( ti_sdo_ipc_transports_TransportShmCirc_Handle __inst, xdc_Ptr msg );

/* control__E */
#define ti_sdo_ipc_transports_TransportShmCirc_control ti_sdo_ipc_transports_TransportShmCirc_control__E
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_control__E, "ti_sdo_ipc_transports_TransportShmCirc_control")
__extern xdc_Bool ti_sdo_ipc_transports_TransportShmCirc_control__E( ti_sdo_ipc_transports_TransportShmCirc_Handle __inst, xdc_UInt cmd, xdc_UArg cmdArg );

/* sharedMemReq__E */
#define ti_sdo_ipc_transports_TransportShmCirc_sharedMemReq ti_sdo_ipc_transports_TransportShmCirc_sharedMemReq__E
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_sharedMemReq__E, "ti_sdo_ipc_transports_TransportShmCirc_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_transports_TransportShmCirc_sharedMemReq__E( const ti_sdo_ipc_transports_TransportShmCirc_Params *params );

/* swiFxn__I */
#define ti_sdo_ipc_transports_TransportShmCirc_swiFxn ti_sdo_ipc_transports_TransportShmCirc_swiFxn__I
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_swiFxn__I, "ti_sdo_ipc_transports_TransportShmCirc_swiFxn")
__extern xdc_Void ti_sdo_ipc_transports_TransportShmCirc_swiFxn__I( xdc_UArg arg );

/* notifyFxn__I */
#define ti_sdo_ipc_transports_TransportShmCirc_notifyFxn ti_sdo_ipc_transports_TransportShmCirc_notifyFxn__I
xdc__CODESECT(ti_sdo_ipc_transports_TransportShmCirc_notifyFxn__I, "ti_sdo_ipc_transports_TransportShmCirc_notifyFxn")
__extern xdc_Void ti_sdo_ipc_transports_TransportShmCirc_notifyFxn__I( xdc_UInt16 procId, xdc_UInt16 lineId, xdc_UInt32 eventId, xdc_UArg arg, xdc_UInt32 payload );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_IMessageQTransport_Module ti_sdo_ipc_transports_TransportShmCirc_Module_upCast( void )
{
    return (ti_sdo_ipc_interfaces_IMessageQTransport_Module)&ti_sdo_ipc_transports_TransportShmCirc_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_IMessageQTransport */
#define ti_sdo_ipc_transports_TransportShmCirc_Module_to_ti_sdo_ipc_interfaces_IMessageQTransport ti_sdo_ipc_transports_TransportShmCirc_Module_upCast

/* Handle_upCast */
static inline ti_sdo_ipc_interfaces_IMessageQTransport_Handle ti_sdo_ipc_transports_TransportShmCirc_Handle_upCast( ti_sdo_ipc_transports_TransportShmCirc_Handle i )
{
    return (ti_sdo_ipc_interfaces_IMessageQTransport_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_IMessageQTransport */
#define ti_sdo_ipc_transports_TransportShmCirc_Handle_to_ti_sdo_ipc_interfaces_IMessageQTransport ti_sdo_ipc_transports_TransportShmCirc_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_transports_TransportShmCirc_Handle ti_sdo_ipc_transports_TransportShmCirc_Handle_downCast( ti_sdo_ipc_interfaces_IMessageQTransport_Handle i )
{
    ti_sdo_ipc_interfaces_IMessageQTransport_Handle i2 = (ti_sdo_ipc_interfaces_IMessageQTransport_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_transports_TransportShmCirc_Module__FXNS__C ? (ti_sdo_ipc_transports_TransportShmCirc_Handle)i : (ti_sdo_ipc_transports_TransportShmCirc_Handle)0;
}

/* Handle_from_ti_sdo_ipc_interfaces_IMessageQTransport */
#define ti_sdo_ipc_transports_TransportShmCirc_Handle_from_ti_sdo_ipc_interfaces_IMessageQTransport ti_sdo_ipc_transports_TransportShmCirc_Handle_downCast

/* Module_upCast2 */
static inline ti_sdo_ipc_interfaces_ITransport_Module ti_sdo_ipc_transports_TransportShmCirc_Module_upCast2( void )
{
    return (ti_sdo_ipc_interfaces_ITransport_Module)&ti_sdo_ipc_transports_TransportShmCirc_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_ITransport */
#define ti_sdo_ipc_transports_TransportShmCirc_Module_to_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_transports_TransportShmCirc_Module_upCast2

/* Handle_upCast2 */
static inline ti_sdo_ipc_interfaces_ITransport_Handle ti_sdo_ipc_transports_TransportShmCirc_Handle_upCast2( ti_sdo_ipc_transports_TransportShmCirc_Handle i )
{
    return (ti_sdo_ipc_interfaces_ITransport_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_ITransport */
#define ti_sdo_ipc_transports_TransportShmCirc_Handle_to_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_transports_TransportShmCirc_Handle_upCast2

/* Handle_downCast2 */
static inline ti_sdo_ipc_transports_TransportShmCirc_Handle ti_sdo_ipc_transports_TransportShmCirc_Handle_downCast2( ti_sdo_ipc_interfaces_ITransport_Handle i )
{
    ti_sdo_ipc_interfaces_ITransport_Handle i2 = (ti_sdo_ipc_interfaces_ITransport_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_transports_TransportShmCirc_Module__FXNS__C ? (ti_sdo_ipc_transports_TransportShmCirc_Handle)i : (ti_sdo_ipc_transports_TransportShmCirc_Handle)0;
}

/* Handle_from_ti_sdo_ipc_interfaces_ITransport */
#define ti_sdo_ipc_transports_TransportShmCirc_Handle_from_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_transports_TransportShmCirc_Handle_downCast2


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_transports_TransportShmCirc_Module_startupDone() ti_sdo_ipc_transports_TransportShmCirc_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_transports_TransportShmCirc_Object_heap() ti_sdo_ipc_transports_TransportShmCirc_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_transports_TransportShmCirc_Module_heap() ti_sdo_ipc_transports_TransportShmCirc_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_transports_TransportShmCirc_Module__id ti_sdo_ipc_transports_TransportShmCirc_Module_id( void ) 
{
    return ti_sdo_ipc_transports_TransportShmCirc_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_transports_TransportShmCirc_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_transports_TransportShmCirc_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_transports_TransportShmCirc_Module_getMask( void ) 
{
    return ti_sdo_ipc_transports_TransportShmCirc_Module__diagsMask__C != NULL ? *ti_sdo_ipc_transports_TransportShmCirc_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_transports_TransportShmCirc_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_transports_TransportShmCirc_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_transports_TransportShmCirc_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_transports_TransportShmCirc_Params_init( ti_sdo_ipc_transports_TransportShmCirc_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_transports_TransportShmCirc_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_transports_TransportShmCirc_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_transports_TransportShmCirc_Params_copy(ti_sdo_ipc_transports_TransportShmCirc_Params *dst, const ti_sdo_ipc_transports_TransportShmCirc_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_transports_TransportShmCirc_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_transports_TransportShmCirc_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_transports_TransportShmCirc_Object_count() ti_sdo_ipc_transports_TransportShmCirc_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_transports_TransportShmCirc_Object_sizeof() ti_sdo_ipc_transports_TransportShmCirc_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_transports_TransportShmCirc_Handle ti_sdo_ipc_transports_TransportShmCirc_Object_get(ti_sdo_ipc_transports_TransportShmCirc_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_transports_TransportShmCirc_Handle)ti_sdo_ipc_transports_TransportShmCirc_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_transports_TransportShmCirc_Handle ti_sdo_ipc_transports_TransportShmCirc_Object_first( void )
{
    return (ti_sdo_ipc_transports_TransportShmCirc_Handle)ti_sdo_ipc_transports_TransportShmCirc_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_transports_TransportShmCirc_Handle ti_sdo_ipc_transports_TransportShmCirc_Object_next( ti_sdo_ipc_transports_TransportShmCirc_Object *obj )
{
    return (ti_sdo_ipc_transports_TransportShmCirc_Handle)ti_sdo_ipc_transports_TransportShmCirc_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_transports_TransportShmCirc_Handle_label( ti_sdo_ipc_transports_TransportShmCirc_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_transports_TransportShmCirc_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_transports_TransportShmCirc_Handle_name( ti_sdo_ipc_transports_TransportShmCirc_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_transports_TransportShmCirc_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_transports_TransportShmCirc_Handle ti_sdo_ipc_transports_TransportShmCirc_handle( ti_sdo_ipc_transports_TransportShmCirc_Struct *str )
{
    return (ti_sdo_ipc_transports_TransportShmCirc_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_transports_TransportShmCirc_Struct *ti_sdo_ipc_transports_TransportShmCirc_struct( ti_sdo_ipc_transports_TransportShmCirc_Handle inst )
{
    return (ti_sdo_ipc_transports_TransportShmCirc_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_transports_TransportShmCirc__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_transports_TransportShmCirc__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_transports_TransportShmCirc__internalaccess))

#ifndef ti_sdo_ipc_transports_TransportShmCirc__include_state
#define ti_sdo_ipc_transports_TransportShmCirc__include_state

/* Object */
struct ti_sdo_ipc_transports_TransportShmCirc_Object {
    const ti_sdo_ipc_transports_TransportShmCirc_Fxns__ *__fxns;
    xdc_Ptr *putBuffer;
    xdc_Bits32 *putReadIndex;
    xdc_Bits32 *putWriteIndex;
    xdc_Ptr *getBuffer;
    xdc_Bits32 *getReadIndex;
    xdc_Bits32 *getWriteIndex;
    xdc_SizeT opCacheSize;
    xdc_UInt16 regionId;
    xdc_UInt16 remoteProcId;
    xdc_Bool cacheEnabled;
    xdc_UInt16 priority;
    ti_sdo_ipc_Ipc_ObjType objType;
    char __dummy;
};

/* Instance_State_swiObj */
__extern __FAR__ const xdc_SizeT ti_sdo_ipc_transports_TransportShmCirc_Instance_State_swiObj__O;
static inline ti_sysbios_knl_Swi_Handle ti_sdo_ipc_transports_TransportShmCirc_Instance_State_swiObj(ti_sdo_ipc_transports_TransportShmCirc_Object *obj)
{
    return (ti_sysbios_knl_Swi_Handle)(((char*)obj) + ti_sdo_ipc_transports_TransportShmCirc_Instance_State_swiObj__O);
}

#endif /* ti_sdo_ipc_transports_TransportShmCirc__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_transports_TransportShmCirc__nolocalnames)

#ifndef ti_sdo_ipc_transports_TransportShmCirc__localnames__done
#define ti_sdo_ipc_transports_TransportShmCirc__localnames__done

/* module prefix */
#define TransportShmCirc_Instance ti_sdo_ipc_transports_TransportShmCirc_Instance
#define TransportShmCirc_Handle ti_sdo_ipc_transports_TransportShmCirc_Handle
#define TransportShmCirc_Module ti_sdo_ipc_transports_TransportShmCirc_Module
#define TransportShmCirc_Object ti_sdo_ipc_transports_TransportShmCirc_Object
#define TransportShmCirc_Struct ti_sdo_ipc_transports_TransportShmCirc_Struct
#define TransportShmCirc_Status ti_sdo_ipc_transports_TransportShmCirc_Status
#define TransportShmCirc_Reason ti_sdo_ipc_transports_TransportShmCirc_Reason
#define TransportShmCirc_ErrFxn ti_sdo_ipc_transports_TransportShmCirc_ErrFxn
#define TransportShmCirc_Instance_State ti_sdo_ipc_transports_TransportShmCirc_Instance_State
#define TransportShmCirc_S_SUCCESS ti_sdo_ipc_transports_TransportShmCirc_S_SUCCESS
#define TransportShmCirc_E_FAIL ti_sdo_ipc_transports_TransportShmCirc_E_FAIL
#define TransportShmCirc_E_ERROR ti_sdo_ipc_transports_TransportShmCirc_E_ERROR
#define TransportShmCirc_Reason_FAILEDPUT ti_sdo_ipc_transports_TransportShmCirc_Reason_FAILEDPUT
#define TransportShmCirc_Reason_INTERNALERR ti_sdo_ipc_transports_TransportShmCirc_Reason_INTERNALERR
#define TransportShmCirc_Reason_PHYSICALERR ti_sdo_ipc_transports_TransportShmCirc_Reason_PHYSICALERR
#define TransportShmCirc_Reason_FAILEDALLOC ti_sdo_ipc_transports_TransportShmCirc_Reason_FAILEDALLOC
#define TransportShmCirc_errFxn ti_sdo_ipc_transports_TransportShmCirc_errFxn
#define TransportShmCirc_alwaysWriteBackMsg ti_sdo_ipc_transports_TransportShmCirc_alwaysWriteBackMsg
#define TransportShmCirc_enableStats ti_sdo_ipc_transports_TransportShmCirc_enableStats
#define TransportShmCirc_notifyEventId ti_sdo_ipc_transports_TransportShmCirc_notifyEventId
#define TransportShmCirc_numMsgs ti_sdo_ipc_transports_TransportShmCirc_numMsgs
#define TransportShmCirc_maxIndex ti_sdo_ipc_transports_TransportShmCirc_maxIndex
#define TransportShmCirc_modIndex ti_sdo_ipc_transports_TransportShmCirc_modIndex
#define TransportShmCirc_Instance_State_swiObj ti_sdo_ipc_transports_TransportShmCirc_Instance_State_swiObj
#define TransportShmCirc_Params ti_sdo_ipc_transports_TransportShmCirc_Params
#define TransportShmCirc_setErrFxn ti_sdo_ipc_transports_TransportShmCirc_setErrFxn
#define TransportShmCirc_getStatus ti_sdo_ipc_transports_TransportShmCirc_getStatus
#define TransportShmCirc_put ti_sdo_ipc_transports_TransportShmCirc_put
#define TransportShmCirc_control ti_sdo_ipc_transports_TransportShmCirc_control
#define TransportShmCirc_sharedMemReq ti_sdo_ipc_transports_TransportShmCirc_sharedMemReq
#define TransportShmCirc_Module_name ti_sdo_ipc_transports_TransportShmCirc_Module_name
#define TransportShmCirc_Module_id ti_sdo_ipc_transports_TransportShmCirc_Module_id
#define TransportShmCirc_Module_startup ti_sdo_ipc_transports_TransportShmCirc_Module_startup
#define TransportShmCirc_Module_startupDone ti_sdo_ipc_transports_TransportShmCirc_Module_startupDone
#define TransportShmCirc_Module_hasMask ti_sdo_ipc_transports_TransportShmCirc_Module_hasMask
#define TransportShmCirc_Module_getMask ti_sdo_ipc_transports_TransportShmCirc_Module_getMask
#define TransportShmCirc_Module_setMask ti_sdo_ipc_transports_TransportShmCirc_Module_setMask
#define TransportShmCirc_Object_heap ti_sdo_ipc_transports_TransportShmCirc_Object_heap
#define TransportShmCirc_Module_heap ti_sdo_ipc_transports_TransportShmCirc_Module_heap
#define TransportShmCirc_construct ti_sdo_ipc_transports_TransportShmCirc_construct
#define TransportShmCirc_create ti_sdo_ipc_transports_TransportShmCirc_create
#define TransportShmCirc_handle ti_sdo_ipc_transports_TransportShmCirc_handle
#define TransportShmCirc_struct ti_sdo_ipc_transports_TransportShmCirc_struct
#define TransportShmCirc_Handle_label ti_sdo_ipc_transports_TransportShmCirc_Handle_label
#define TransportShmCirc_Handle_name ti_sdo_ipc_transports_TransportShmCirc_Handle_name
#define TransportShmCirc_Instance_init ti_sdo_ipc_transports_TransportShmCirc_Instance_init
#define TransportShmCirc_Object_count ti_sdo_ipc_transports_TransportShmCirc_Object_count
#define TransportShmCirc_Object_get ti_sdo_ipc_transports_TransportShmCirc_Object_get
#define TransportShmCirc_Object_first ti_sdo_ipc_transports_TransportShmCirc_Object_first
#define TransportShmCirc_Object_next ti_sdo_ipc_transports_TransportShmCirc_Object_next
#define TransportShmCirc_Object_sizeof ti_sdo_ipc_transports_TransportShmCirc_Object_sizeof
#define TransportShmCirc_Params_copy ti_sdo_ipc_transports_TransportShmCirc_Params_copy
#define TransportShmCirc_Params_init ti_sdo_ipc_transports_TransportShmCirc_Params_init
#define TransportShmCirc_Instance_finalize ti_sdo_ipc_transports_TransportShmCirc_Instance_finalize
#define TransportShmCirc_delete ti_sdo_ipc_transports_TransportShmCirc_delete
#define TransportShmCirc_destruct ti_sdo_ipc_transports_TransportShmCirc_destruct
#define TransportShmCirc_Module_upCast ti_sdo_ipc_transports_TransportShmCirc_Module_upCast
#define TransportShmCirc_Module_to_ti_sdo_ipc_interfaces_IMessageQTransport ti_sdo_ipc_transports_TransportShmCirc_Module_to_ti_sdo_ipc_interfaces_IMessageQTransport
#define TransportShmCirc_Handle_upCast ti_sdo_ipc_transports_TransportShmCirc_Handle_upCast
#define TransportShmCirc_Handle_to_ti_sdo_ipc_interfaces_IMessageQTransport ti_sdo_ipc_transports_TransportShmCirc_Handle_to_ti_sdo_ipc_interfaces_IMessageQTransport
#define TransportShmCirc_Handle_downCast ti_sdo_ipc_transports_TransportShmCirc_Handle_downCast
#define TransportShmCirc_Handle_from_ti_sdo_ipc_interfaces_IMessageQTransport ti_sdo_ipc_transports_TransportShmCirc_Handle_from_ti_sdo_ipc_interfaces_IMessageQTransport
#define TransportShmCirc_Module_upCast2 ti_sdo_ipc_transports_TransportShmCirc_Module_upCast2
#define TransportShmCirc_Module_to_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_transports_TransportShmCirc_Module_to_ti_sdo_ipc_interfaces_ITransport
#define TransportShmCirc_Handle_upCast2 ti_sdo_ipc_transports_TransportShmCirc_Handle_upCast2
#define TransportShmCirc_Handle_to_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_transports_TransportShmCirc_Handle_to_ti_sdo_ipc_interfaces_ITransport
#define TransportShmCirc_Handle_downCast2 ti_sdo_ipc_transports_TransportShmCirc_Handle_downCast2
#define TransportShmCirc_Handle_from_ti_sdo_ipc_interfaces_ITransport ti_sdo_ipc_transports_TransportShmCirc_Handle_from_ti_sdo_ipc_interfaces_ITransport

#endif /* ti_sdo_ipc_transports_TransportShmCirc__localnames__done */
#endif
