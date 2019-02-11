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

#ifndef ti_sdo_ipc_notifyDrivers_NotifyDriverShm__include
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/notifyDrivers/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <ti/sdo/utils/MultiProc.h>
#include <ti/sdo/ipc/interfaces/INotifyDriver.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>
#include <ti/sdo/ipc/Notify.h>
#include <ti/sdo/ipc/notifyDrivers/package/NotifyDriverShm_InterruptProxy.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* DOWN */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_DOWN (0)

/* UP */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_UP (1)

/* INIT_STAMP */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_INIT_STAMP (0xA9C8B7D6)

/* EventEntry */
struct ti_sdo_ipc_notifyDrivers_NotifyDriverShm_EventEntry {
    volatile xdc_Bits32 flag;
    volatile xdc_Bits32 payload;
    volatile xdc_Bits32 reserved;
};

/* ProcCtrl */
struct ti_sdo_ipc_notifyDrivers_NotifyDriverShm_ProcCtrl {
    volatile xdc_Bits32 recvInitStatus;
    volatile xdc_Bits32 sendInitStatus;
    volatile xdc_Bits32 eventRegMask;
    volatile xdc_Bits32 eventEnableMask;
};

/* Instance_State */
typedef xdc_UInt32 __T1_ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_State__regChart;
typedef xdc_UInt32 *__ARRAY1_ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_State__regChart;
typedef __ARRAY1_ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_State__regChart __TA_ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_State__regChart;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsEnabled ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsIncluded ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsMask ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__gateObj ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__gatePrms ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__id ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerDefined ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerObj ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn0 ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn1 ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn2 ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn4 ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn8 ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__startupDoneFxn ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__count ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__heap ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__sizeof ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__table ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_Ptr sharedAddr;
    xdc_Bool cacheEnabled;
    xdc_SizeT cacheLineSize;
    xdc_UInt16 remoteProcId;
    xdc_UInt intVectorId;
    xdc_UInt localIntId;
    xdc_UInt remoteIntId;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Struct {
    const ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Fxns__ *__fxns;
    ti_sdo_ipc_notifyDrivers_NotifyDriverShm_ProcCtrl *__f0;
    ti_sdo_ipc_notifyDrivers_NotifyDriverShm_ProcCtrl *__f1;
    ti_sdo_ipc_notifyDrivers_NotifyDriverShm_EventEntry *__f2;
    ti_sdo_ipc_notifyDrivers_NotifyDriverShm_EventEntry *__f3;
    ti_sdo_ipc_Notify_Handle __f4;
    __TA_ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_State__regChart __f5;
    xdc_UInt __f6;
    xdc_UInt __f7;
    ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo __f8;
    xdc_UInt16 __f9;
    xdc_UInt __f10;
    xdc_Bool __f11;
    xdc_SizeT __f12;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Void (*registerEvent)(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle, xdc_UInt32);
    xdc_Void (*unregisterEvent)(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle, xdc_UInt32);
    xdc_Int (*sendEvent)(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle, xdc_UInt32, xdc_UInt32, xdc_Bool);
    xdc_Void (*disable)(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle);
    xdc_Void (*enable)(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle);
    xdc_Void (*disableEvent)(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle, xdc_UInt32);
    xdc_Void (*enableEvent)(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle, xdc_UInt32);
    xdc_Void (*setNotifyHandle)(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle, xdc_Ptr);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Fxns__ ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_init__E, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_init")
__extern xdc_Int ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_init__E(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object *, const ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params *, xdc_runtime_Error_Block *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_finalize__E, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_finalize")
__extern void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_finalize__E( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle__label__S, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__startupDone__S, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__create__S, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_create, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_create")
__extern ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle ti_sdo_ipc_notifyDrivers_NotifyDriverShm_create( const ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_construct, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_construct")
__extern void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_construct( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Struct *__obj, const ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__delete__S, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_delete, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_delete")
__extern void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_delete(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__destruct__S, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_destruct, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_destruct")
__extern void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_destruct(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__get__S, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__first__S, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__next__S, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params__init__S, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params__init__S")
__extern xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* registerEvent__E */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_registerEvent ti_sdo_ipc_notifyDrivers_NotifyDriverShm_registerEvent__E
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_registerEvent__E, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_registerEvent")
__extern xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_registerEvent__E( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle __inst, xdc_UInt32 eventId );

/* unregisterEvent__E */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_unregisterEvent ti_sdo_ipc_notifyDrivers_NotifyDriverShm_unregisterEvent__E
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_unregisterEvent__E, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_unregisterEvent")
__extern xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_unregisterEvent__E( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle __inst, xdc_UInt32 eventId );

/* sendEvent__E */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sendEvent ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sendEvent__E
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sendEvent__E, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sendEvent")
__extern xdc_Int ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sendEvent__E( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle __inst, xdc_UInt32 eventId, xdc_UInt32 payload, xdc_Bool waitClear );

/* disable__E */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disable ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disable__E
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disable__E, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disable")
__extern xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disable__E( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle __inst );

/* enable__E */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enable ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enable__E
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enable__E, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enable")
__extern xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enable__E( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle __inst );

/* disableEvent__E */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disableEvent ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disableEvent__E
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disableEvent__E, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disableEvent")
__extern xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disableEvent__E( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle __inst, xdc_UInt32 eventId );

/* enableEvent__E */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enableEvent ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enableEvent__E
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enableEvent__E, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enableEvent")
__extern xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enableEvent__E( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle __inst, xdc_UInt32 eventId );

/* setNotifyHandle__E */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_setNotifyHandle ti_sdo_ipc_notifyDrivers_NotifyDriverShm_setNotifyHandle__E
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_setNotifyHandle__E, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_setNotifyHandle")
__extern xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_setNotifyHandle__E( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle __inst, xdc_Ptr driverHandle );

/* sharedMemReq__E */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sharedMemReq ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sharedMemReq__E
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sharedMemReq__E, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sharedMemReq__E( const ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params *params );
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sharedMemReq__F, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sharedMemReq__F( const ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params *params );

/* isr__I */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_isr ti_sdo_ipc_notifyDrivers_NotifyDriverShm_isr__I
xdc__CODESECT(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_isr__I, "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_isr")
__extern xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_isr__I( xdc_UArg arg );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_INotifyDriver_Module ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_upCast( void )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_Module)&ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_INotifyDriver */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_to_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_upCast

/* Handle_upCast */
static inline ti_sdo_ipc_interfaces_INotifyDriver_Handle ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_upCast( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle i )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_INotifyDriver */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_to_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_downCast( ti_sdo_ipc_interfaces_INotifyDriver_Handle i )
{
    ti_sdo_ipc_interfaces_INotifyDriver_Handle i2 = (ti_sdo_ipc_interfaces_INotifyDriver_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__FXNS__C ? (ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle)i : (ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle)0;
}

/* Handle_from_ti_sdo_ipc_interfaces_INotifyDriver */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_from_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_startupDone() ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_heap() ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_heap() ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__id ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_id( void ) 
{
    return ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_getMask( void ) 
{
    return ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsMask__C != NULL ? *ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params_init( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params_copy(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params *dst, const ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_count() ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_sizeof() ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_get(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle)ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_first( void )
{
    return (ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle)ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_next( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object *obj )
{
    return (ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle)ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_label( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_name( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle ti_sdo_ipc_notifyDrivers_NotifyDriverShm_handle( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Struct *str )
{
    return (ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Struct *ti_sdo_ipc_notifyDrivers_NotifyDriverShm_struct( ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle inst )
{
    return (ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_notifyDrivers_NotifyDriverShm__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_notifyDrivers_NotifyDriverShm__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_notifyDrivers_NotifyDriverShm__internalaccess))

#ifndef ti_sdo_ipc_notifyDrivers_NotifyDriverShm__include_state
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm__include_state

/* Object */
struct ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object {
    const ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Fxns__ *__fxns;
    ti_sdo_ipc_notifyDrivers_NotifyDriverShm_ProcCtrl *selfProcCtrl;
    ti_sdo_ipc_notifyDrivers_NotifyDriverShm_ProcCtrl *otherProcCtrl;
    ti_sdo_ipc_notifyDrivers_NotifyDriverShm_EventEntry *selfEventChart;
    ti_sdo_ipc_notifyDrivers_NotifyDriverShm_EventEntry *otherEventChart;
    ti_sdo_ipc_Notify_Handle notifyHandle;
    __TA_ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_State__regChart regChart;
    xdc_UInt selfId;
    xdc_UInt otherId;
    ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo intInfo;
    xdc_UInt16 remoteProcId;
    xdc_UInt nesting;
    xdc_Bool cacheEnabled;
    xdc_SizeT eventEntrySize;
};

#endif /* ti_sdo_ipc_notifyDrivers_NotifyDriverShm__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_notifyDrivers_NotifyDriverShm__nolocalnames)

#ifndef ti_sdo_ipc_notifyDrivers_NotifyDriverShm__localnames__done
#define ti_sdo_ipc_notifyDrivers_NotifyDriverShm__localnames__done

/* module prefix */
#define NotifyDriverShm_Instance ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance
#define NotifyDriverShm_Handle ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle
#define NotifyDriverShm_Module ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module
#define NotifyDriverShm_Object ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object
#define NotifyDriverShm_Struct ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Struct
#define NotifyDriverShm_DOWN ti_sdo_ipc_notifyDrivers_NotifyDriverShm_DOWN
#define NotifyDriverShm_UP ti_sdo_ipc_notifyDrivers_NotifyDriverShm_UP
#define NotifyDriverShm_INIT_STAMP ti_sdo_ipc_notifyDrivers_NotifyDriverShm_INIT_STAMP
#define NotifyDriverShm_EventEntry ti_sdo_ipc_notifyDrivers_NotifyDriverShm_EventEntry
#define NotifyDriverShm_ProcCtrl ti_sdo_ipc_notifyDrivers_NotifyDriverShm_ProcCtrl
#define NotifyDriverShm_Instance_State ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_State
#define NotifyDriverShm_Params ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params
#define NotifyDriverShm_registerEvent ti_sdo_ipc_notifyDrivers_NotifyDriverShm_registerEvent
#define NotifyDriverShm_unregisterEvent ti_sdo_ipc_notifyDrivers_NotifyDriverShm_unregisterEvent
#define NotifyDriverShm_sendEvent ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sendEvent
#define NotifyDriverShm_disable ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disable
#define NotifyDriverShm_enable ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enable
#define NotifyDriverShm_disableEvent ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disableEvent
#define NotifyDriverShm_enableEvent ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enableEvent
#define NotifyDriverShm_setNotifyHandle ti_sdo_ipc_notifyDrivers_NotifyDriverShm_setNotifyHandle
#define NotifyDriverShm_sharedMemReq ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sharedMemReq
#define NotifyDriverShm_Module_name ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_name
#define NotifyDriverShm_Module_id ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_id
#define NotifyDriverShm_Module_startup ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_startup
#define NotifyDriverShm_Module_startupDone ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_startupDone
#define NotifyDriverShm_Module_hasMask ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_hasMask
#define NotifyDriverShm_Module_getMask ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_getMask
#define NotifyDriverShm_Module_setMask ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_setMask
#define NotifyDriverShm_Object_heap ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_heap
#define NotifyDriverShm_Module_heap ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_heap
#define NotifyDriverShm_construct ti_sdo_ipc_notifyDrivers_NotifyDriverShm_construct
#define NotifyDriverShm_create ti_sdo_ipc_notifyDrivers_NotifyDriverShm_create
#define NotifyDriverShm_handle ti_sdo_ipc_notifyDrivers_NotifyDriverShm_handle
#define NotifyDriverShm_struct ti_sdo_ipc_notifyDrivers_NotifyDriverShm_struct
#define NotifyDriverShm_Handle_label ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_label
#define NotifyDriverShm_Handle_name ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_name
#define NotifyDriverShm_Instance_init ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_init
#define NotifyDriverShm_Object_count ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_count
#define NotifyDriverShm_Object_get ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_get
#define NotifyDriverShm_Object_first ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_first
#define NotifyDriverShm_Object_next ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_next
#define NotifyDriverShm_Object_sizeof ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object_sizeof
#define NotifyDriverShm_Params_copy ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params_copy
#define NotifyDriverShm_Params_init ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params_init
#define NotifyDriverShm_Instance_finalize ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Instance_finalize
#define NotifyDriverShm_delete ti_sdo_ipc_notifyDrivers_NotifyDriverShm_delete
#define NotifyDriverShm_destruct ti_sdo_ipc_notifyDrivers_NotifyDriverShm_destruct
#define NotifyDriverShm_Module_upCast ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_upCast
#define NotifyDriverShm_Module_to_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module_to_ti_sdo_ipc_interfaces_INotifyDriver
#define NotifyDriverShm_Handle_upCast ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_upCast
#define NotifyDriverShm_Handle_to_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_to_ti_sdo_ipc_interfaces_INotifyDriver
#define NotifyDriverShm_Handle_downCast ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_downCast
#define NotifyDriverShm_Handle_from_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle_from_ti_sdo_ipc_interfaces_INotifyDriver

/* proxies */
#include <ti/sdo/ipc/notifyDrivers/package/NotifyDriverShm_InterruptProxy.h>

#endif /* ti_sdo_ipc_notifyDrivers_NotifyDriverShm__localnames__done */
#endif
