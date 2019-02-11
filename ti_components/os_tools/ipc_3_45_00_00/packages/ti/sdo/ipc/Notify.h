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
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_sdo_ipc_Notify__include
#define ti_sdo_ipc_Notify__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_Notify__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_Notify___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/package/package.defs.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <ti/sdo/utils/List.h>
#include <ti/sdo/ipc/interfaces/INotifyDriver.h>
#include <xdc/runtime/IModule.h>
#include <ti/sdo/ipc/interfaces/INotifySetup.h>
#include <xdc/runtime/IGateProvider.h>
#include <ti/sdo/ipc/package/Notify_SetupProxy.h>
#include <ti/sdo/ipc/package/Notify_Module_GateProxy.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* MAXEVENTS */
#define ti_sdo_ipc_Notify_MAXEVENTS (32)


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_Notify_Args__create {
    ti_sdo_ipc_interfaces_INotifyDriver_Handle driverHandle;
    xdc_UInt16 remoteProcId;
    xdc_UInt16 lineId;
} ti_sdo_ipc_Notify_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* EventCallback */
struct ti_sdo_ipc_Notify_EventCallback {
    xdc_Fxn fnNotifyCbck;
    xdc_UArg cbckArg;
};

/* EventListener */
struct ti_sdo_ipc_Notify_EventListener {
    ti_sdo_utils_List_Elem element;
    ti_sdo_ipc_Notify_EventCallback callback;
};

/* Instance_State */
typedef ti_sdo_ipc_Notify_EventCallback __T1_ti_sdo_ipc_Notify_Instance_State__callbacks;
typedef ti_sdo_ipc_Notify_EventCallback *__ARRAY1_ti_sdo_ipc_Notify_Instance_State__callbacks;
typedef __ARRAY1_ti_sdo_ipc_Notify_Instance_State__callbacks __TA_ti_sdo_ipc_Notify_Instance_State__callbacks;
typedef ti_sdo_utils_List_Instance_State __T1_ti_sdo_ipc_Notify_Instance_State__eventList;
typedef ti_sdo_utils_List_Instance_State *__ARRAY1_ti_sdo_ipc_Notify_Instance_State__eventList;
typedef __ARRAY1_ti_sdo_ipc_Notify_Instance_State__eventList __TA_ti_sdo_ipc_Notify_Instance_State__eventList;

/* Module_State */
typedef ti_sdo_ipc_Notify_Handle __T1_ti_sdo_ipc_Notify_Module_State__notifyHandles;
typedef ti_sdo_ipc_Notify_Handle *__ARRAY1_ti_sdo_ipc_Notify_Module_State__notifyHandles;
typedef __ARRAY1_ti_sdo_ipc_Notify_Module_State__notifyHandles __T2_ti_sdo_ipc_Notify_Module_State__notifyHandles;
typedef ti_sdo_ipc_Notify_Handle **__ARRAY2_ti_sdo_ipc_Notify_Module_State__notifyHandles;
typedef __ARRAY2_ti_sdo_ipc_Notify_Module_State__notifyHandles __TA_ti_sdo_ipc_Notify_Module_State__notifyHandles;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_Notify_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__diagsEnabled ti_sdo_ipc_Notify_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_Notify_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__diagsIncluded ti_sdo_ipc_Notify_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_Notify_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__diagsMask ti_sdo_ipc_Notify_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_Notify_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__gateObj ti_sdo_ipc_Notify_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_Notify_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__gatePrms ti_sdo_ipc_Notify_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_Notify_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__id ti_sdo_ipc_Notify_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_Notify_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__loggerDefined ti_sdo_ipc_Notify_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_Notify_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__loggerObj ti_sdo_ipc_Notify_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_Notify_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__loggerFxn0 ti_sdo_ipc_Notify_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_Notify_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__loggerFxn1 ti_sdo_ipc_Notify_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_Notify_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__loggerFxn2 ti_sdo_ipc_Notify_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_Notify_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__loggerFxn4 ti_sdo_ipc_Notify_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_Notify_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__loggerFxn8 ti_sdo_ipc_Notify_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_Notify_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Module__startupDoneFxn ti_sdo_ipc_Notify_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_Notify_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Object__count ti_sdo_ipc_Notify_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_Notify_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Object__heap ti_sdo_ipc_Notify_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_Notify_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Object__sizeof ti_sdo_ipc_Notify_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_Notify_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_Object__table ti_sdo_ipc_Notify_Object__table__C;

/* A_alreadyRegistered */
#define ti_sdo_ipc_Notify_A_alreadyRegistered (ti_sdo_ipc_Notify_A_alreadyRegistered__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Notify_A_alreadyRegistered;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_A_alreadyRegistered ti_sdo_ipc_Notify_A_alreadyRegistered__C;

/* A_notRegistered */
#define ti_sdo_ipc_Notify_A_notRegistered (ti_sdo_ipc_Notify_A_notRegistered__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Notify_A_notRegistered;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_A_notRegistered ti_sdo_ipc_Notify_A_notRegistered__C;

/* A_reservedEvent */
#define ti_sdo_ipc_Notify_A_reservedEvent (ti_sdo_ipc_Notify_A_reservedEvent__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Notify_A_reservedEvent;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_A_reservedEvent ti_sdo_ipc_Notify_A_reservedEvent__C;

/* A_outOfOrderNesting */
#define ti_sdo_ipc_Notify_A_outOfOrderNesting (ti_sdo_ipc_Notify_A_outOfOrderNesting__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Notify_A_outOfOrderNesting;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_A_outOfOrderNesting ti_sdo_ipc_Notify_A_outOfOrderNesting__C;

/* A_invArgument */
#define ti_sdo_ipc_Notify_A_invArgument (ti_sdo_ipc_Notify_A_invArgument__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Notify_A_invArgument;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_A_invArgument ti_sdo_ipc_Notify_A_invArgument__C;

/* A_internal */
#define ti_sdo_ipc_Notify_A_internal (ti_sdo_ipc_Notify_A_internal__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Notify_A_internal;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_A_internal ti_sdo_ipc_Notify_A_internal__C;

/* numEvents */
#ifdef ti_sdo_ipc_Notify_numEvents__D
#define ti_sdo_ipc_Notify_numEvents (ti_sdo_ipc_Notify_numEvents__D)
#else
#define ti_sdo_ipc_Notify_numEvents (ti_sdo_ipc_Notify_numEvents__C)
typedef xdc_UInt CT__ti_sdo_ipc_Notify_numEvents;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_numEvents ti_sdo_ipc_Notify_numEvents__C;
#endif

/* sendEventPollCount */
#ifdef ti_sdo_ipc_Notify_sendEventPollCount__D
#define ti_sdo_ipc_Notify_sendEventPollCount (ti_sdo_ipc_Notify_sendEventPollCount__D)
#else
#define ti_sdo_ipc_Notify_sendEventPollCount (ti_sdo_ipc_Notify_sendEventPollCount__C)
typedef xdc_UInt32 CT__ti_sdo_ipc_Notify_sendEventPollCount;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_sendEventPollCount ti_sdo_ipc_Notify_sendEventPollCount__C;
#endif

/* numLines */
#ifdef ti_sdo_ipc_Notify_numLines__D
#define ti_sdo_ipc_Notify_numLines (ti_sdo_ipc_Notify_numLines__D)
#else
#define ti_sdo_ipc_Notify_numLines (ti_sdo_ipc_Notify_numLines__C)
typedef xdc_UInt16 CT__ti_sdo_ipc_Notify_numLines;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_numLines ti_sdo_ipc_Notify_numLines__C;
#endif

/* reservedEvents */
#ifdef ti_sdo_ipc_Notify_reservedEvents__D
#define ti_sdo_ipc_Notify_reservedEvents (ti_sdo_ipc_Notify_reservedEvents__D)
#else
#define ti_sdo_ipc_Notify_reservedEvents (ti_sdo_ipc_Notify_reservedEvents__C)
typedef xdc_UInt16 CT__ti_sdo_ipc_Notify_reservedEvents;
__extern __FAR__ const CT__ti_sdo_ipc_Notify_reservedEvents ti_sdo_ipc_Notify_reservedEvents__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_Notify_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_Notify_Struct {
    xdc_UInt __f0;
    ti_sdo_ipc_interfaces_INotifyDriver_Handle __f1;
    xdc_UInt16 __f2;
    xdc_UInt16 __f3;
    __TA_ti_sdo_ipc_Notify_Instance_State__callbacks __f4;
    __TA_ti_sdo_ipc_Notify_Instance_State__eventList __f5;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_Notify_Module_startup ti_sdo_ipc_Notify_Module_startup__E
xdc__CODESECT(ti_sdo_ipc_Notify_Module_startup__E, "ti_sdo_ipc_Notify_Module_startup")
__extern xdc_Int ti_sdo_ipc_Notify_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_sdo_ipc_Notify_Module_startup__F, "ti_sdo_ipc_Notify_Module_startup")
__extern xdc_Int ti_sdo_ipc_Notify_Module_startup__F( xdc_Int state );

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_Notify_Instance_init__E, "ti_sdo_ipc_Notify_Instance_init")
__extern xdc_Int ti_sdo_ipc_Notify_Instance_init__E(ti_sdo_ipc_Notify_Object *, ti_sdo_ipc_interfaces_INotifyDriver_Handle driverHandle, xdc_UInt16 remoteProcId, xdc_UInt16 lineId, const ti_sdo_ipc_Notify_Params *, xdc_runtime_Error_Block *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_Notify_Instance_finalize__E, "ti_sdo_ipc_Notify_Instance_finalize")
__extern void ti_sdo_ipc_Notify_Instance_finalize__E( ti_sdo_ipc_Notify_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Handle__label__S, "ti_sdo_ipc_Notify_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_Notify_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Module__startupDone__S, "ti_sdo_ipc_Notify_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_Notify_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Object__create__S, "ti_sdo_ipc_Notify_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_Notify_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_Notify_create, "ti_sdo_ipc_Notify_create")
__extern ti_sdo_ipc_Notify_Handle ti_sdo_ipc_Notify_create( ti_sdo_ipc_interfaces_INotifyDriver_Handle driverHandle, xdc_UInt16 remoteProcId, xdc_UInt16 lineId, const ti_sdo_ipc_Notify_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_Notify_construct, "ti_sdo_ipc_Notify_construct")
__extern void ti_sdo_ipc_Notify_construct( ti_sdo_ipc_Notify_Struct *__obj, ti_sdo_ipc_interfaces_INotifyDriver_Handle driverHandle, xdc_UInt16 remoteProcId, xdc_UInt16 lineId, const ti_sdo_ipc_Notify_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Object__delete__S, "ti_sdo_ipc_Notify_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_Notify_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_Notify_delete, "ti_sdo_ipc_Notify_delete")
__extern void ti_sdo_ipc_Notify_delete(ti_sdo_ipc_Notify_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Object__destruct__S, "ti_sdo_ipc_Notify_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_Notify_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_Notify_destruct, "ti_sdo_ipc_Notify_destruct")
__extern void ti_sdo_ipc_Notify_destruct(ti_sdo_ipc_Notify_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Object__get__S, "ti_sdo_ipc_Notify_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_Notify_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Object__first__S, "ti_sdo_ipc_Notify_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_Notify_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Object__next__S, "ti_sdo_ipc_Notify_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_Notify_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_Notify_Params__init__S, "ti_sdo_ipc_Notify_Params__init__S")
__extern xdc_Void ti_sdo_ipc_Notify_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* detach__E */
#define ti_sdo_ipc_Notify_detach ti_sdo_ipc_Notify_detach__E
xdc__CODESECT(ti_sdo_ipc_Notify_detach__E, "ti_sdo_ipc_Notify_detach")
__extern xdc_Int ti_sdo_ipc_Notify_detach__E( xdc_UInt16 remoteProcId );
xdc__CODESECT(ti_sdo_ipc_Notify_detach__F, "ti_sdo_ipc_Notify_detach")
__extern xdc_Int ti_sdo_ipc_Notify_detach__F( xdc_UInt16 remoteProcId );

/* exec__E */
#define ti_sdo_ipc_Notify_exec ti_sdo_ipc_Notify_exec__E
xdc__CODESECT(ti_sdo_ipc_Notify_exec__E, "ti_sdo_ipc_Notify_exec")
__extern xdc_Void ti_sdo_ipc_Notify_exec__E( ti_sdo_ipc_Notify_Handle __inst, xdc_UInt32 eventId, xdc_UInt32 payload );
xdc__CODESECT(ti_sdo_ipc_Notify_exec__F, "ti_sdo_ipc_Notify_exec")
__extern xdc_Void ti_sdo_ipc_Notify_exec__F( ti_sdo_ipc_Notify_Object *__inst, xdc_UInt32 eventId, xdc_UInt32 payload );

/* execMany__I */
#define ti_sdo_ipc_Notify_execMany ti_sdo_ipc_Notify_execMany__I
xdc__CODESECT(ti_sdo_ipc_Notify_execMany__I, "ti_sdo_ipc_Notify_execMany")
__extern xdc_Void ti_sdo_ipc_Notify_execMany__I( xdc_UInt16 remoteProcId, xdc_UInt16 lineId, xdc_UInt32 eventId, xdc_UArg arg, xdc_UInt32 payload );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_Notify_Module_startupDone() ti_sdo_ipc_Notify_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_Notify_Object_heap() ti_sdo_ipc_Notify_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_Notify_Module_heap() ti_sdo_ipc_Notify_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_Notify_Module__id ti_sdo_ipc_Notify_Module_id( void ) 
{
    return ti_sdo_ipc_Notify_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_Notify_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_Notify_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_Notify_Module_getMask( void ) 
{
    return ti_sdo_ipc_Notify_Module__diagsMask__C != NULL ? *ti_sdo_ipc_Notify_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_Notify_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_Notify_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_Notify_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_Notify_Params_init( ti_sdo_ipc_Notify_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_Notify_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_Notify_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_Notify_Params_copy(ti_sdo_ipc_Notify_Params *dst, const ti_sdo_ipc_Notify_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_Notify_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_Notify_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_Notify_Object_count() ti_sdo_ipc_Notify_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_Notify_Object_sizeof() ti_sdo_ipc_Notify_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_Notify_Handle ti_sdo_ipc_Notify_Object_get(ti_sdo_ipc_Notify_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_Notify_Handle)ti_sdo_ipc_Notify_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_Notify_Handle ti_sdo_ipc_Notify_Object_first( void )
{
    return (ti_sdo_ipc_Notify_Handle)ti_sdo_ipc_Notify_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_Notify_Handle ti_sdo_ipc_Notify_Object_next( ti_sdo_ipc_Notify_Object *obj )
{
    return (ti_sdo_ipc_Notify_Handle)ti_sdo_ipc_Notify_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_Notify_Handle_label( ti_sdo_ipc_Notify_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_Notify_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_Notify_Handle_name( ti_sdo_ipc_Notify_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_Notify_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_Notify_Handle ti_sdo_ipc_Notify_handle( ti_sdo_ipc_Notify_Struct *str )
{
    return (ti_sdo_ipc_Notify_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_Notify_Struct *ti_sdo_ipc_Notify_struct( ti_sdo_ipc_Notify_Handle inst )
{
    return (ti_sdo_ipc_Notify_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_Notify__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_Notify__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_Notify__internalaccess))

#ifndef ti_sdo_ipc_Notify__include_state
#define ti_sdo_ipc_Notify__include_state

/* Module_State */
struct ti_sdo_ipc_Notify_Module_State {
    __TA_ti_sdo_ipc_Notify_Module_State__notifyHandles notifyHandles;
    xdc_Bits32 localEnableMask;
};

/* Module__state__V */
extern struct ti_sdo_ipc_Notify_Module_State__ ti_sdo_ipc_Notify_Module__state__V;

/* Object */
struct ti_sdo_ipc_Notify_Object {
    xdc_UInt nesting;
    ti_sdo_ipc_interfaces_INotifyDriver_Handle driverHandle;
    xdc_UInt16 remoteProcId;
    xdc_UInt16 lineId;
    __TA_ti_sdo_ipc_Notify_Instance_State__callbacks callbacks;
    __TA_ti_sdo_ipc_Notify_Instance_State__eventList eventList;
};

#endif /* ti_sdo_ipc_Notify__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_Notify__nolocalnames)

#ifndef ti_sdo_ipc_Notify__localnames__done
#define ti_sdo_ipc_Notify__localnames__done

/* module prefix */
#define Notify_Instance ti_sdo_ipc_Notify_Instance
#define Notify_Handle ti_sdo_ipc_Notify_Handle
#define Notify_Module ti_sdo_ipc_Notify_Module
#define Notify_Object ti_sdo_ipc_Notify_Object
#define Notify_Struct ti_sdo_ipc_Notify_Struct
#define Notify_MAXEVENTS ti_sdo_ipc_Notify_MAXEVENTS
#define Notify_EventCallback ti_sdo_ipc_Notify_EventCallback
#define Notify_EventListener ti_sdo_ipc_Notify_EventListener
#define Notify_Instance_State ti_sdo_ipc_Notify_Instance_State
#define Notify_Module_State ti_sdo_ipc_Notify_Module_State
#define Notify_A_alreadyRegistered ti_sdo_ipc_Notify_A_alreadyRegistered
#define Notify_A_notRegistered ti_sdo_ipc_Notify_A_notRegistered
#define Notify_A_reservedEvent ti_sdo_ipc_Notify_A_reservedEvent
#define Notify_A_outOfOrderNesting ti_sdo_ipc_Notify_A_outOfOrderNesting
#define Notify_A_invArgument ti_sdo_ipc_Notify_A_invArgument
#define Notify_A_internal ti_sdo_ipc_Notify_A_internal
#define Notify_numEvents ti_sdo_ipc_Notify_numEvents
#define Notify_sendEventPollCount ti_sdo_ipc_Notify_sendEventPollCount
#define Notify_numLines ti_sdo_ipc_Notify_numLines
#define Notify_reservedEvents ti_sdo_ipc_Notify_reservedEvents
#define Notify_Params ti_sdo_ipc_Notify_Params
#define Notify_detach ti_sdo_ipc_Notify_detach
#define Notify_exec ti_sdo_ipc_Notify_exec
#define Notify_Module_name ti_sdo_ipc_Notify_Module_name
#define Notify_Module_id ti_sdo_ipc_Notify_Module_id
#define Notify_Module_startup ti_sdo_ipc_Notify_Module_startup
#define Notify_Module_startupDone ti_sdo_ipc_Notify_Module_startupDone
#define Notify_Module_hasMask ti_sdo_ipc_Notify_Module_hasMask
#define Notify_Module_getMask ti_sdo_ipc_Notify_Module_getMask
#define Notify_Module_setMask ti_sdo_ipc_Notify_Module_setMask
#define Notify_Object_heap ti_sdo_ipc_Notify_Object_heap
#define Notify_Module_heap ti_sdo_ipc_Notify_Module_heap
#define Notify_construct ti_sdo_ipc_Notify_construct
#define Notify_create ti_sdo_ipc_Notify_create
#define Notify_handle ti_sdo_ipc_Notify_handle
#define Notify_struct ti_sdo_ipc_Notify_struct
#define Notify_Handle_label ti_sdo_ipc_Notify_Handle_label
#define Notify_Handle_name ti_sdo_ipc_Notify_Handle_name
#define Notify_Instance_init ti_sdo_ipc_Notify_Instance_init
#define Notify_Object_count ti_sdo_ipc_Notify_Object_count
#define Notify_Object_get ti_sdo_ipc_Notify_Object_get
#define Notify_Object_first ti_sdo_ipc_Notify_Object_first
#define Notify_Object_next ti_sdo_ipc_Notify_Object_next
#define Notify_Object_sizeof ti_sdo_ipc_Notify_Object_sizeof
#define Notify_Params_copy ti_sdo_ipc_Notify_Params_copy
#define Notify_Params_init ti_sdo_ipc_Notify_Params_init
#define Notify_Instance_finalize ti_sdo_ipc_Notify_Instance_finalize
#define Notify_delete ti_sdo_ipc_Notify_delete
#define Notify_destruct ti_sdo_ipc_Notify_destruct

/* proxies */
#include <ti/sdo/ipc/package/Notify_SetupProxy.h>

/* proxies */
#include <ti/sdo/ipc/package/Notify_Module_GateProxy.h>

#endif /* ti_sdo_ipc_Notify__localnames__done */
#endif
