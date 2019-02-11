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

#ifndef ti_sdo_ipc_nsremote_NameServerMessageQ__include
#define ti_sdo_ipc_nsremote_NameServerMessageQ__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_nsremote_NameServerMessageQ__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_nsremote_NameServerMessageQ___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/nsremote/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/syncs/SyncSwi.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/gates/GateMutex.h>
#include <ti/sdo/ipc/MessageQ.h>
#include <ti/sdo/utils/INameServerRemote.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Status */
typedef ti_sdo_utils_INameServerRemote_Status ti_sdo_ipc_nsremote_NameServerMessageQ_Status;

/* maxNameLen */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_maxNameLen (32)

/* S_SUCCESS */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_S_SUCCESS ti_sdo_utils_INameServerRemote_S_SUCCESS

/* E_FAIL */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_E_FAIL ti_sdo_utils_INameServerRemote_E_FAIL

/* E_ERROR */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_E_ERROR ti_sdo_utils_INameServerRemote_E_ERROR


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sdo_ipc_nsremote_NameServerMessageQ_Args__create {
    xdc_UInt16 procId;
} ti_sdo_ipc_nsremote_NameServerMessageQ_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* Type */
enum ti_sdo_ipc_nsremote_NameServerMessageQ_Type {
    ti_sdo_ipc_nsremote_NameServerMessageQ_REQUEST = 0,
    ti_sdo_ipc_nsremote_NameServerMessageQ_RESPONSE = 1
};
typedef enum ti_sdo_ipc_nsremote_NameServerMessageQ_Type ti_sdo_ipc_nsremote_NameServerMessageQ_Type;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsEnabled ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsIncluded ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsMask ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__gateObj ti_sdo_ipc_nsremote_NameServerMessageQ_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__gatePrms ti_sdo_ipc_nsremote_NameServerMessageQ_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__id ti_sdo_ipc_nsremote_NameServerMessageQ_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerDefined ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerObj ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn0 ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn1 ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn2 ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn4 ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn8 ti_sdo_ipc_nsremote_NameServerMessageQ_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__startupDoneFxn ti_sdo_ipc_nsremote_NameServerMessageQ_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Object__count ti_sdo_ipc_nsremote_NameServerMessageQ_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Object__heap ti_sdo_ipc_nsremote_NameServerMessageQ_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Object__sizeof ti_sdo_ipc_nsremote_NameServerMessageQ_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Object__table ti_sdo_ipc_nsremote_NameServerMessageQ_Object__table__C;

/* A_reservedMsgQueueId */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_A_reservedMsgQueueId (ti_sdo_ipc_nsremote_NameServerMessageQ_A_reservedMsgQueueId__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_nsremote_NameServerMessageQ_A_reservedMsgQueueId;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_A_reservedMsgQueueId ti_sdo_ipc_nsremote_NameServerMessageQ_A_reservedMsgQueueId__C;

/* A_nameIsTooLong */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_A_nameIsTooLong (ti_sdo_ipc_nsremote_NameServerMessageQ_A_nameIsTooLong__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_nsremote_NameServerMessageQ_A_nameIsTooLong;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_A_nameIsTooLong ti_sdo_ipc_nsremote_NameServerMessageQ_A_nameIsTooLong__C;

/* E_outOfMemory */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_E_outOfMemory (ti_sdo_ipc_nsremote_NameServerMessageQ_E_outOfMemory__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_nsremote_NameServerMessageQ_E_outOfMemory;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_E_outOfMemory ti_sdo_ipc_nsremote_NameServerMessageQ_E_outOfMemory__C;

/* heapId */
#ifdef ti_sdo_ipc_nsremote_NameServerMessageQ_heapId__D
#define ti_sdo_ipc_nsremote_NameServerMessageQ_heapId (ti_sdo_ipc_nsremote_NameServerMessageQ_heapId__D)
#else
#define ti_sdo_ipc_nsremote_NameServerMessageQ_heapId (ti_sdo_ipc_nsremote_NameServerMessageQ_heapId__C)
typedef xdc_UInt16 CT__ti_sdo_ipc_nsremote_NameServerMessageQ_heapId;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_heapId ti_sdo_ipc_nsremote_NameServerMessageQ_heapId__C;
#endif

/* timeoutInMicroSecs */
#ifdef ti_sdo_ipc_nsremote_NameServerMessageQ_timeoutInMicroSecs__D
#define ti_sdo_ipc_nsremote_NameServerMessageQ_timeoutInMicroSecs (ti_sdo_ipc_nsremote_NameServerMessageQ_timeoutInMicroSecs__D)
#else
#define ti_sdo_ipc_nsremote_NameServerMessageQ_timeoutInMicroSecs (ti_sdo_ipc_nsremote_NameServerMessageQ_timeoutInMicroSecs__C)
typedef xdc_UInt CT__ti_sdo_ipc_nsremote_NameServerMessageQ_timeoutInMicroSecs;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_timeoutInMicroSecs ti_sdo_ipc_nsremote_NameServerMessageQ_timeoutInMicroSecs__C;
#endif

/* timeout */
#ifdef ti_sdo_ipc_nsremote_NameServerMessageQ_timeout__D
#define ti_sdo_ipc_nsremote_NameServerMessageQ_timeout (ti_sdo_ipc_nsremote_NameServerMessageQ_timeout__D)
#else
#define ti_sdo_ipc_nsremote_NameServerMessageQ_timeout (ti_sdo_ipc_nsremote_NameServerMessageQ_timeout__C)
typedef xdc_UInt CT__ti_sdo_ipc_nsremote_NameServerMessageQ_timeout;
__extern __FAR__ const CT__ti_sdo_ipc_nsremote_NameServerMessageQ_timeout ti_sdo_ipc_nsremote_NameServerMessageQ_timeout__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_nsremote_NameServerMessageQ_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_nsremote_NameServerMessageQ_Struct {
    const ti_sdo_ipc_nsremote_NameServerMessageQ_Fxns__ *__fxns;
    xdc_UInt16 __f0;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_nsremote_NameServerMessageQ_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*attach)(xdc_UInt16, xdc_Ptr);
    xdc_Int (*detach)(xdc_UInt16);
    xdc_SizeT (*sharedMemReq)(xdc_Ptr);
    xdc_Int (*get)(ti_sdo_ipc_nsremote_NameServerMessageQ_Handle, xdc_String, xdc_String, xdc_Ptr, xdc_UInt32*, xdc_runtime_knl_ISync_Handle, xdc_runtime_Error_Block*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_nsremote_NameServerMessageQ_Fxns__ ti_sdo_ipc_nsremote_NameServerMessageQ_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_Module_startup ti_sdo_ipc_nsremote_NameServerMessageQ_Module_startup__E
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Module_startup__E, "ti_sdo_ipc_nsremote_NameServerMessageQ_Module_startup")
__extern xdc_Int ti_sdo_ipc_nsremote_NameServerMessageQ_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Module_startup__F, "ti_sdo_ipc_nsremote_NameServerMessageQ_Module_startup")
__extern xdc_Int ti_sdo_ipc_nsremote_NameServerMessageQ_Module_startup__F( xdc_Int state );

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Instance_init__E, "ti_sdo_ipc_nsremote_NameServerMessageQ_Instance_init")
__extern xdc_Void ti_sdo_ipc_nsremote_NameServerMessageQ_Instance_init__E(ti_sdo_ipc_nsremote_NameServerMessageQ_Object *, xdc_UInt16 procId, const ti_sdo_ipc_nsremote_NameServerMessageQ_Params *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Instance_finalize__E, "ti_sdo_ipc_nsremote_NameServerMessageQ_Instance_finalize")
__extern void ti_sdo_ipc_nsremote_NameServerMessageQ_Instance_finalize__E( ti_sdo_ipc_nsremote_NameServerMessageQ_Object* );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Handle__label__S, "ti_sdo_ipc_nsremote_NameServerMessageQ_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_nsremote_NameServerMessageQ_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Module__startupDone__S, "ti_sdo_ipc_nsremote_NameServerMessageQ_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_nsremote_NameServerMessageQ_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Object__create__S, "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_nsremote_NameServerMessageQ_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_create, "ti_sdo_ipc_nsremote_NameServerMessageQ_create")
__extern ti_sdo_ipc_nsremote_NameServerMessageQ_Handle ti_sdo_ipc_nsremote_NameServerMessageQ_create( xdc_UInt16 procId, const ti_sdo_ipc_nsremote_NameServerMessageQ_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_construct, "ti_sdo_ipc_nsremote_NameServerMessageQ_construct")
__extern void ti_sdo_ipc_nsremote_NameServerMessageQ_construct( ti_sdo_ipc_nsremote_NameServerMessageQ_Struct *__obj, xdc_UInt16 procId, const ti_sdo_ipc_nsremote_NameServerMessageQ_Params *__prms );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Object__delete__S, "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_nsremote_NameServerMessageQ_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_delete, "ti_sdo_ipc_nsremote_NameServerMessageQ_delete")
__extern void ti_sdo_ipc_nsremote_NameServerMessageQ_delete(ti_sdo_ipc_nsremote_NameServerMessageQ_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Object__destruct__S, "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_nsremote_NameServerMessageQ_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_destruct, "ti_sdo_ipc_nsremote_NameServerMessageQ_destruct")
__extern void ti_sdo_ipc_nsremote_NameServerMessageQ_destruct(ti_sdo_ipc_nsremote_NameServerMessageQ_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Object__get__S, "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_nsremote_NameServerMessageQ_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Object__first__S, "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_nsremote_NameServerMessageQ_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Object__next__S, "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_nsremote_NameServerMessageQ_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_Params__init__S, "ti_sdo_ipc_nsremote_NameServerMessageQ_Params__init__S")
__extern xdc_Void ti_sdo_ipc_nsremote_NameServerMessageQ_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* attach__E */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_attach ti_sdo_ipc_nsremote_NameServerMessageQ_attach__E
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_attach__E, "ti_sdo_ipc_nsremote_NameServerMessageQ_attach")
__extern xdc_Int ti_sdo_ipc_nsremote_NameServerMessageQ_attach__E( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* detach__E */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_detach ti_sdo_ipc_nsremote_NameServerMessageQ_detach__E
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_detach__E, "ti_sdo_ipc_nsremote_NameServerMessageQ_detach")
__extern xdc_Int ti_sdo_ipc_nsremote_NameServerMessageQ_detach__E( xdc_UInt16 remoteProcId );

/* sharedMemReq__E */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_sharedMemReq ti_sdo_ipc_nsremote_NameServerMessageQ_sharedMemReq__E
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_sharedMemReq__E, "ti_sdo_ipc_nsremote_NameServerMessageQ_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_nsremote_NameServerMessageQ_sharedMemReq__E( xdc_Ptr sharedAddr );

/* get__E */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_get ti_sdo_ipc_nsremote_NameServerMessageQ_get__E
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_get__E, "ti_sdo_ipc_nsremote_NameServerMessageQ_get")
__extern xdc_Int ti_sdo_ipc_nsremote_NameServerMessageQ_get__E( ti_sdo_ipc_nsremote_NameServerMessageQ_Handle __inst, xdc_String instanceName, xdc_String name, xdc_Ptr value, xdc_UInt32 *valueLen, xdc_runtime_knl_ISync_Handle syncHandle, xdc_runtime_Error_Block *eb );
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_get__F, "ti_sdo_ipc_nsremote_NameServerMessageQ_get")
__extern xdc_Int ti_sdo_ipc_nsremote_NameServerMessageQ_get__F( ti_sdo_ipc_nsremote_NameServerMessageQ_Object *__inst, xdc_String instanceName, xdc_String name, xdc_Ptr value, xdc_UInt32 *valueLen, xdc_runtime_knl_ISync_Handle syncHandle, xdc_runtime_Error_Block *eb );

/* swiFxn__I */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_swiFxn ti_sdo_ipc_nsremote_NameServerMessageQ_swiFxn__I
xdc__CODESECT(ti_sdo_ipc_nsremote_NameServerMessageQ_swiFxn__I, "ti_sdo_ipc_nsremote_NameServerMessageQ_swiFxn")
__extern xdc_Void ti_sdo_ipc_nsremote_NameServerMessageQ_swiFxn__I( xdc_UArg arg0, xdc_UArg arg1 );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_utils_INameServerRemote_Module ti_sdo_ipc_nsremote_NameServerMessageQ_Module_upCast( void )
{
    return (ti_sdo_utils_INameServerRemote_Module)&ti_sdo_ipc_nsremote_NameServerMessageQ_Module__FXNS__C;
}

/* Module_to_ti_sdo_utils_INameServerRemote */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_Module_to_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerMessageQ_Module_upCast

/* Handle_upCast */
static inline ti_sdo_utils_INameServerRemote_Handle ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_upCast( ti_sdo_ipc_nsremote_NameServerMessageQ_Handle i )
{
    return (ti_sdo_utils_INameServerRemote_Handle)i;
}

/* Handle_to_ti_sdo_utils_INameServerRemote */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_to_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_nsremote_NameServerMessageQ_Handle ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_downCast( ti_sdo_utils_INameServerRemote_Handle i )
{
    ti_sdo_utils_INameServerRemote_Handle i2 = (ti_sdo_utils_INameServerRemote_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_nsremote_NameServerMessageQ_Module__FXNS__C ? (ti_sdo_ipc_nsremote_NameServerMessageQ_Handle)i : (ti_sdo_ipc_nsremote_NameServerMessageQ_Handle)0;
}

/* Handle_from_ti_sdo_utils_INameServerRemote */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_from_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_Module_startupDone() ti_sdo_ipc_nsremote_NameServerMessageQ_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_Object_heap() ti_sdo_ipc_nsremote_NameServerMessageQ_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_Module_heap() ti_sdo_ipc_nsremote_NameServerMessageQ_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_nsremote_NameServerMessageQ_Module__id ti_sdo_ipc_nsremote_NameServerMessageQ_Module_id( void ) 
{
    return ti_sdo_ipc_nsremote_NameServerMessageQ_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_nsremote_NameServerMessageQ_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_nsremote_NameServerMessageQ_Module_getMask( void ) 
{
    return ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsMask__C != NULL ? *ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_nsremote_NameServerMessageQ_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_nsremote_NameServerMessageQ_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_nsremote_NameServerMessageQ_Params_init( ti_sdo_ipc_nsremote_NameServerMessageQ_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_nsremote_NameServerMessageQ_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_nsremote_NameServerMessageQ_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_nsremote_NameServerMessageQ_Params_copy(ti_sdo_ipc_nsremote_NameServerMessageQ_Params *dst, const ti_sdo_ipc_nsremote_NameServerMessageQ_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_nsremote_NameServerMessageQ_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_nsremote_NameServerMessageQ_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_Object_count() ti_sdo_ipc_nsremote_NameServerMessageQ_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_nsremote_NameServerMessageQ_Object_sizeof() ti_sdo_ipc_nsremote_NameServerMessageQ_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_nsremote_NameServerMessageQ_Handle ti_sdo_ipc_nsremote_NameServerMessageQ_Object_get(ti_sdo_ipc_nsremote_NameServerMessageQ_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_nsremote_NameServerMessageQ_Handle)ti_sdo_ipc_nsremote_NameServerMessageQ_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_nsremote_NameServerMessageQ_Handle ti_sdo_ipc_nsremote_NameServerMessageQ_Object_first( void )
{
    return (ti_sdo_ipc_nsremote_NameServerMessageQ_Handle)ti_sdo_ipc_nsremote_NameServerMessageQ_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_nsremote_NameServerMessageQ_Handle ti_sdo_ipc_nsremote_NameServerMessageQ_Object_next( ti_sdo_ipc_nsremote_NameServerMessageQ_Object *obj )
{
    return (ti_sdo_ipc_nsremote_NameServerMessageQ_Handle)ti_sdo_ipc_nsremote_NameServerMessageQ_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_label( ti_sdo_ipc_nsremote_NameServerMessageQ_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_nsremote_NameServerMessageQ_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_name( ti_sdo_ipc_nsremote_NameServerMessageQ_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_nsremote_NameServerMessageQ_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_nsremote_NameServerMessageQ_Handle ti_sdo_ipc_nsremote_NameServerMessageQ_handle( ti_sdo_ipc_nsremote_NameServerMessageQ_Struct *str )
{
    return (ti_sdo_ipc_nsremote_NameServerMessageQ_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_nsremote_NameServerMessageQ_Struct *ti_sdo_ipc_nsremote_NameServerMessageQ_struct( ti_sdo_ipc_nsremote_NameServerMessageQ_Handle inst )
{
    return (ti_sdo_ipc_nsremote_NameServerMessageQ_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_nsremote_NameServerMessageQ__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_nsremote_NameServerMessageQ__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_nsremote_NameServerMessageQ__internalaccess))

#ifndef ti_sdo_ipc_nsremote_NameServerMessageQ__include_state
#define ti_sdo_ipc_nsremote_NameServerMessageQ__include_state

/* Module_State */
struct ti_sdo_ipc_nsremote_NameServerMessageQ_Module_State {
    ti_sdo_ipc_MessageQ_Handle msgHandle;
    ti_sysbios_knl_Swi_Handle swiHandle;
    ti_sysbios_syncs_SyncSwi_Handle syncSwiHandle;
    ti_sysbios_knl_Semaphore_Handle semRemoteWait;
    ti_sysbios_gates_GateMutex_Handle gateMutex;
    xdc_Ptr msg;
};

/* Module__state__V */
extern struct ti_sdo_ipc_nsremote_NameServerMessageQ_Module_State__ ti_sdo_ipc_nsremote_NameServerMessageQ_Module__state__V;

/* Object */
struct ti_sdo_ipc_nsremote_NameServerMessageQ_Object {
    const ti_sdo_ipc_nsremote_NameServerMessageQ_Fxns__ *__fxns;
    xdc_UInt16 remoteProcId;
};

#endif /* ti_sdo_ipc_nsremote_NameServerMessageQ__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_nsremote_NameServerMessageQ__nolocalnames)

#ifndef ti_sdo_ipc_nsremote_NameServerMessageQ__localnames__done
#define ti_sdo_ipc_nsremote_NameServerMessageQ__localnames__done

/* module prefix */
#define NameServerMessageQ_Instance ti_sdo_ipc_nsremote_NameServerMessageQ_Instance
#define NameServerMessageQ_Handle ti_sdo_ipc_nsremote_NameServerMessageQ_Handle
#define NameServerMessageQ_Module ti_sdo_ipc_nsremote_NameServerMessageQ_Module
#define NameServerMessageQ_Object ti_sdo_ipc_nsremote_NameServerMessageQ_Object
#define NameServerMessageQ_Struct ti_sdo_ipc_nsremote_NameServerMessageQ_Struct
#define NameServerMessageQ_Status ti_sdo_ipc_nsremote_NameServerMessageQ_Status
#define NameServerMessageQ_maxNameLen ti_sdo_ipc_nsremote_NameServerMessageQ_maxNameLen
#define NameServerMessageQ_Type ti_sdo_ipc_nsremote_NameServerMessageQ_Type
#define NameServerMessageQ_Instance_State ti_sdo_ipc_nsremote_NameServerMessageQ_Instance_State
#define NameServerMessageQ_Module_State ti_sdo_ipc_nsremote_NameServerMessageQ_Module_State
#define NameServerMessageQ_S_SUCCESS ti_sdo_ipc_nsremote_NameServerMessageQ_S_SUCCESS
#define NameServerMessageQ_E_FAIL ti_sdo_ipc_nsremote_NameServerMessageQ_E_FAIL
#define NameServerMessageQ_E_ERROR ti_sdo_ipc_nsremote_NameServerMessageQ_E_ERROR
#define NameServerMessageQ_REQUEST ti_sdo_ipc_nsremote_NameServerMessageQ_REQUEST
#define NameServerMessageQ_RESPONSE ti_sdo_ipc_nsremote_NameServerMessageQ_RESPONSE
#define NameServerMessageQ_A_reservedMsgQueueId ti_sdo_ipc_nsremote_NameServerMessageQ_A_reservedMsgQueueId
#define NameServerMessageQ_A_nameIsTooLong ti_sdo_ipc_nsremote_NameServerMessageQ_A_nameIsTooLong
#define NameServerMessageQ_E_outOfMemory ti_sdo_ipc_nsremote_NameServerMessageQ_E_outOfMemory
#define NameServerMessageQ_heapId ti_sdo_ipc_nsremote_NameServerMessageQ_heapId
#define NameServerMessageQ_timeoutInMicroSecs ti_sdo_ipc_nsremote_NameServerMessageQ_timeoutInMicroSecs
#define NameServerMessageQ_timeout ti_sdo_ipc_nsremote_NameServerMessageQ_timeout
#define NameServerMessageQ_Params ti_sdo_ipc_nsremote_NameServerMessageQ_Params
#define NameServerMessageQ_attach ti_sdo_ipc_nsremote_NameServerMessageQ_attach
#define NameServerMessageQ_detach ti_sdo_ipc_nsremote_NameServerMessageQ_detach
#define NameServerMessageQ_sharedMemReq ti_sdo_ipc_nsremote_NameServerMessageQ_sharedMemReq
#define NameServerMessageQ_get ti_sdo_ipc_nsremote_NameServerMessageQ_get
#define NameServerMessageQ_Module_name ti_sdo_ipc_nsremote_NameServerMessageQ_Module_name
#define NameServerMessageQ_Module_id ti_sdo_ipc_nsremote_NameServerMessageQ_Module_id
#define NameServerMessageQ_Module_startup ti_sdo_ipc_nsremote_NameServerMessageQ_Module_startup
#define NameServerMessageQ_Module_startupDone ti_sdo_ipc_nsremote_NameServerMessageQ_Module_startupDone
#define NameServerMessageQ_Module_hasMask ti_sdo_ipc_nsremote_NameServerMessageQ_Module_hasMask
#define NameServerMessageQ_Module_getMask ti_sdo_ipc_nsremote_NameServerMessageQ_Module_getMask
#define NameServerMessageQ_Module_setMask ti_sdo_ipc_nsremote_NameServerMessageQ_Module_setMask
#define NameServerMessageQ_Object_heap ti_sdo_ipc_nsremote_NameServerMessageQ_Object_heap
#define NameServerMessageQ_Module_heap ti_sdo_ipc_nsremote_NameServerMessageQ_Module_heap
#define NameServerMessageQ_construct ti_sdo_ipc_nsremote_NameServerMessageQ_construct
#define NameServerMessageQ_create ti_sdo_ipc_nsremote_NameServerMessageQ_create
#define NameServerMessageQ_handle ti_sdo_ipc_nsremote_NameServerMessageQ_handle
#define NameServerMessageQ_struct ti_sdo_ipc_nsremote_NameServerMessageQ_struct
#define NameServerMessageQ_Handle_label ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_label
#define NameServerMessageQ_Handle_name ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_name
#define NameServerMessageQ_Instance_init ti_sdo_ipc_nsremote_NameServerMessageQ_Instance_init
#define NameServerMessageQ_Object_count ti_sdo_ipc_nsremote_NameServerMessageQ_Object_count
#define NameServerMessageQ_Object_get ti_sdo_ipc_nsremote_NameServerMessageQ_Object_get
#define NameServerMessageQ_Object_first ti_sdo_ipc_nsremote_NameServerMessageQ_Object_first
#define NameServerMessageQ_Object_next ti_sdo_ipc_nsremote_NameServerMessageQ_Object_next
#define NameServerMessageQ_Object_sizeof ti_sdo_ipc_nsremote_NameServerMessageQ_Object_sizeof
#define NameServerMessageQ_Params_copy ti_sdo_ipc_nsremote_NameServerMessageQ_Params_copy
#define NameServerMessageQ_Params_init ti_sdo_ipc_nsremote_NameServerMessageQ_Params_init
#define NameServerMessageQ_Instance_finalize ti_sdo_ipc_nsremote_NameServerMessageQ_Instance_finalize
#define NameServerMessageQ_delete ti_sdo_ipc_nsremote_NameServerMessageQ_delete
#define NameServerMessageQ_destruct ti_sdo_ipc_nsremote_NameServerMessageQ_destruct
#define NameServerMessageQ_Module_upCast ti_sdo_ipc_nsremote_NameServerMessageQ_Module_upCast
#define NameServerMessageQ_Module_to_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerMessageQ_Module_to_ti_sdo_utils_INameServerRemote
#define NameServerMessageQ_Handle_upCast ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_upCast
#define NameServerMessageQ_Handle_to_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_to_ti_sdo_utils_INameServerRemote
#define NameServerMessageQ_Handle_downCast ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_downCast
#define NameServerMessageQ_Handle_from_ti_sdo_utils_INameServerRemote ti_sdo_ipc_nsremote_NameServerMessageQ_Handle_from_ti_sdo_utils_INameServerRemote

#endif /* ti_sdo_ipc_nsremote_NameServerMessageQ__localnames__done */
#endif
