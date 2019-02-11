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

#ifndef ti_ipc_namesrv_NameServerRemoteRpmsg__include
#define ti_ipc_namesrv_NameServerRemoteRpmsg__include

#ifndef __nested__
#define __nested__
#define ti_ipc_namesrv_NameServerRemoteRpmsg__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_ipc_namesrv_NameServerRemoteRpmsg___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/ipc/namesrv/package/package.defs.h>

#include <xdc/runtime/Assert.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/gates/GateMutex.h>
#include <ti/sdo/utils/INameServerRemote.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Status */
typedef ti_sdo_utils_INameServerRemote_Status ti_ipc_namesrv_NameServerRemoteRpmsg_Status;

/* S_SUCCESS */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_S_SUCCESS ti_sdo_utils_INameServerRemote_S_SUCCESS

/* E_FAIL */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_E_FAIL ti_sdo_utils_INameServerRemote_E_FAIL

/* E_ERROR */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_E_ERROR ti_sdo_utils_INameServerRemote_E_ERROR


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_ipc_namesrv_NameServerRemoteRpmsg_Args__create {
    xdc_UInt16 procId;
} ti_ipc_namesrv_NameServerRemoteRpmsg_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* Type */
enum ti_ipc_namesrv_NameServerRemoteRpmsg_Type {
    ti_ipc_namesrv_NameServerRemoteRpmsg_REQUEST = 0,
    ti_ipc_namesrv_NameServerRemoteRpmsg_RESPONSE = 1
};
typedef enum ti_ipc_namesrv_NameServerRemoteRpmsg_Type ti_ipc_namesrv_NameServerRemoteRpmsg_Type;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsEnabled;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsEnabled ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsIncluded;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsIncluded ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsMask;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsMask ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__gateObj;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__gateObj ti_ipc_namesrv_NameServerRemoteRpmsg_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__gatePrms;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__gatePrms ti_ipc_namesrv_NameServerRemoteRpmsg_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__id;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__id ti_ipc_namesrv_NameServerRemoteRpmsg_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerDefined;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerDefined ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerObj;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerObj ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn0;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn0 ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn1;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn1 ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn2;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn2 ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn4;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn4 ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn8;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn8 ti_ipc_namesrv_NameServerRemoteRpmsg_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__startupDoneFxn ti_ipc_namesrv_NameServerRemoteRpmsg_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Object__count;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Object__count ti_ipc_namesrv_NameServerRemoteRpmsg_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Object__heap;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Object__heap ti_ipc_namesrv_NameServerRemoteRpmsg_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Object__sizeof;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Object__sizeof ti_ipc_namesrv_NameServerRemoteRpmsg_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Object__table;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Object__table ti_ipc_namesrv_NameServerRemoteRpmsg_Object__table__C;

/* timeoutInMicroSecs */
#ifdef ti_ipc_namesrv_NameServerRemoteRpmsg_timeoutInMicroSecs__D
#define ti_ipc_namesrv_NameServerRemoteRpmsg_timeoutInMicroSecs (ti_ipc_namesrv_NameServerRemoteRpmsg_timeoutInMicroSecs__D)
#else
#define ti_ipc_namesrv_NameServerRemoteRpmsg_timeoutInMicroSecs (ti_ipc_namesrv_NameServerRemoteRpmsg_timeoutInMicroSecs__C)
typedef xdc_UInt CT__ti_ipc_namesrv_NameServerRemoteRpmsg_timeoutInMicroSecs;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_timeoutInMicroSecs ti_ipc_namesrv_NameServerRemoteRpmsg_timeoutInMicroSecs__C;
#endif

/* A_nameIsTooLong */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_A_nameIsTooLong (ti_ipc_namesrv_NameServerRemoteRpmsg_A_nameIsTooLong__C)
typedef xdc_runtime_Assert_Id CT__ti_ipc_namesrv_NameServerRemoteRpmsg_A_nameIsTooLong;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_A_nameIsTooLong ti_ipc_namesrv_NameServerRemoteRpmsg_A_nameIsTooLong__C;

/* timeout */
#ifdef ti_ipc_namesrv_NameServerRemoteRpmsg_timeout__D
#define ti_ipc_namesrv_NameServerRemoteRpmsg_timeout (ti_ipc_namesrv_NameServerRemoteRpmsg_timeout__D)
#else
#define ti_ipc_namesrv_NameServerRemoteRpmsg_timeout (ti_ipc_namesrv_NameServerRemoteRpmsg_timeout__C)
typedef xdc_UInt CT__ti_ipc_namesrv_NameServerRemoteRpmsg_timeout;
__extern __FAR__ const CT__ti_ipc_namesrv_NameServerRemoteRpmsg_timeout ti_ipc_namesrv_NameServerRemoteRpmsg_timeout__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_ipc_namesrv_NameServerRemoteRpmsg_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_ipc_namesrv_NameServerRemoteRpmsg_Struct {
    const ti_ipc_namesrv_NameServerRemoteRpmsg_Fxns__ *__fxns;
    xdc_UInt16 __f0;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_ipc_namesrv_NameServerRemoteRpmsg_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*attach)(xdc_UInt16, xdc_Ptr);
    xdc_Int (*detach)(xdc_UInt16);
    xdc_SizeT (*sharedMemReq)(xdc_Ptr);
    xdc_Int (*get)(ti_ipc_namesrv_NameServerRemoteRpmsg_Handle, xdc_String, xdc_String, xdc_Ptr, xdc_UInt32*, xdc_runtime_knl_ISync_Handle, xdc_runtime_Error_Block*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_ipc_namesrv_NameServerRemoteRpmsg_Fxns__ ti_ipc_namesrv_NameServerRemoteRpmsg_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_Instance_init__E, "ti_ipc_namesrv_NameServerRemoteRpmsg_Instance_init")
__extern xdc_Void ti_ipc_namesrv_NameServerRemoteRpmsg_Instance_init__E(ti_ipc_namesrv_NameServerRemoteRpmsg_Object *, xdc_UInt16 procId, const ti_ipc_namesrv_NameServerRemoteRpmsg_Params *);

/* Instance_finalize__E */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_Instance_finalize__E, "ti_ipc_namesrv_NameServerRemoteRpmsg_Instance_finalize")
__extern void ti_ipc_namesrv_NameServerRemoteRpmsg_Instance_finalize__E( ti_ipc_namesrv_NameServerRemoteRpmsg_Object* );

/* Handle__label__S */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_Handle__label__S, "ti_ipc_namesrv_NameServerRemoteRpmsg_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_ipc_namesrv_NameServerRemoteRpmsg_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_Module__startupDone__S, "ti_ipc_namesrv_NameServerRemoteRpmsg_Module__startupDone__S")
__extern xdc_Bool ti_ipc_namesrv_NameServerRemoteRpmsg_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_Object__create__S, "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__create__S")
__extern xdc_Ptr ti_ipc_namesrv_NameServerRemoteRpmsg_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_create, "ti_ipc_namesrv_NameServerRemoteRpmsg_create")
__extern ti_ipc_namesrv_NameServerRemoteRpmsg_Handle ti_ipc_namesrv_NameServerRemoteRpmsg_create( xdc_UInt16 procId, const ti_ipc_namesrv_NameServerRemoteRpmsg_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_construct, "ti_ipc_namesrv_NameServerRemoteRpmsg_construct")
__extern void ti_ipc_namesrv_NameServerRemoteRpmsg_construct( ti_ipc_namesrv_NameServerRemoteRpmsg_Struct *__obj, xdc_UInt16 procId, const ti_ipc_namesrv_NameServerRemoteRpmsg_Params *__prms );

/* Object__delete__S */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_Object__delete__S, "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__delete__S")
__extern xdc_Void ti_ipc_namesrv_NameServerRemoteRpmsg_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_delete, "ti_ipc_namesrv_NameServerRemoteRpmsg_delete")
__extern void ti_ipc_namesrv_NameServerRemoteRpmsg_delete(ti_ipc_namesrv_NameServerRemoteRpmsg_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_Object__destruct__S, "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__destruct__S")
__extern xdc_Void ti_ipc_namesrv_NameServerRemoteRpmsg_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_destruct, "ti_ipc_namesrv_NameServerRemoteRpmsg_destruct")
__extern void ti_ipc_namesrv_NameServerRemoteRpmsg_destruct(ti_ipc_namesrv_NameServerRemoteRpmsg_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_Object__get__S, "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__get__S")
__extern xdc_Ptr ti_ipc_namesrv_NameServerRemoteRpmsg_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_Object__first__S, "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__first__S")
__extern xdc_Ptr ti_ipc_namesrv_NameServerRemoteRpmsg_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_Object__next__S, "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__next__S")
__extern xdc_Ptr ti_ipc_namesrv_NameServerRemoteRpmsg_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_Params__init__S, "ti_ipc_namesrv_NameServerRemoteRpmsg_Params__init__S")
__extern xdc_Void ti_ipc_namesrv_NameServerRemoteRpmsg_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* attach__E */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_attach ti_ipc_namesrv_NameServerRemoteRpmsg_attach__E
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_attach__E, "ti_ipc_namesrv_NameServerRemoteRpmsg_attach")
__extern xdc_Int ti_ipc_namesrv_NameServerRemoteRpmsg_attach__E( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* detach__E */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_detach ti_ipc_namesrv_NameServerRemoteRpmsg_detach__E
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_detach__E, "ti_ipc_namesrv_NameServerRemoteRpmsg_detach")
__extern xdc_Int ti_ipc_namesrv_NameServerRemoteRpmsg_detach__E( xdc_UInt16 remoteProcId );

/* sharedMemReq__E */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_sharedMemReq ti_ipc_namesrv_NameServerRemoteRpmsg_sharedMemReq__E
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_sharedMemReq__E, "ti_ipc_namesrv_NameServerRemoteRpmsg_sharedMemReq")
__extern xdc_SizeT ti_ipc_namesrv_NameServerRemoteRpmsg_sharedMemReq__E( xdc_Ptr sharedAddr );

/* get__E */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_get ti_ipc_namesrv_NameServerRemoteRpmsg_get__E
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_get__E, "ti_ipc_namesrv_NameServerRemoteRpmsg_get")
__extern xdc_Int ti_ipc_namesrv_NameServerRemoteRpmsg_get__E( ti_ipc_namesrv_NameServerRemoteRpmsg_Handle __inst, xdc_String instanceName, xdc_String name, xdc_Ptr value, xdc_UInt32 *valueLen, xdc_runtime_knl_ISync_Handle syncHandle, xdc_runtime_Error_Block *eb );
xdc__CODESECT(ti_ipc_namesrv_NameServerRemoteRpmsg_get__F, "ti_ipc_namesrv_NameServerRemoteRpmsg_get")
__extern xdc_Int ti_ipc_namesrv_NameServerRemoteRpmsg_get__F( ti_ipc_namesrv_NameServerRemoteRpmsg_Object *__inst, xdc_String instanceName, xdc_String name, xdc_Ptr value, xdc_UInt32 *valueLen, xdc_runtime_knl_ISync_Handle syncHandle, xdc_runtime_Error_Block *eb );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_utils_INameServerRemote_Module ti_ipc_namesrv_NameServerRemoteRpmsg_Module_upCast( void )
{
    return (ti_sdo_utils_INameServerRemote_Module)&ti_ipc_namesrv_NameServerRemoteRpmsg_Module__FXNS__C;
}

/* Module_to_ti_sdo_utils_INameServerRemote */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_Module_to_ti_sdo_utils_INameServerRemote ti_ipc_namesrv_NameServerRemoteRpmsg_Module_upCast

/* Handle_upCast */
static inline ti_sdo_utils_INameServerRemote_Handle ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_upCast( ti_ipc_namesrv_NameServerRemoteRpmsg_Handle i )
{
    return (ti_sdo_utils_INameServerRemote_Handle)i;
}

/* Handle_to_ti_sdo_utils_INameServerRemote */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_to_ti_sdo_utils_INameServerRemote ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_upCast

/* Handle_downCast */
static inline ti_ipc_namesrv_NameServerRemoteRpmsg_Handle ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_downCast( ti_sdo_utils_INameServerRemote_Handle i )
{
    ti_sdo_utils_INameServerRemote_Handle i2 = (ti_sdo_utils_INameServerRemote_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_ipc_namesrv_NameServerRemoteRpmsg_Module__FXNS__C ? (ti_ipc_namesrv_NameServerRemoteRpmsg_Handle)i : (ti_ipc_namesrv_NameServerRemoteRpmsg_Handle)0;
}

/* Handle_from_ti_sdo_utils_INameServerRemote */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_from_ti_sdo_utils_INameServerRemote ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_Module_startupDone() ti_ipc_namesrv_NameServerRemoteRpmsg_Module__startupDone__S()

/* Object_heap */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_Object_heap() ti_ipc_namesrv_NameServerRemoteRpmsg_Object__heap__C

/* Module_heap */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_Module_heap() ti_ipc_namesrv_NameServerRemoteRpmsg_Object__heap__C

/* Module_id */
static inline CT__ti_ipc_namesrv_NameServerRemoteRpmsg_Module__id ti_ipc_namesrv_NameServerRemoteRpmsg_Module_id( void ) 
{
    return ti_ipc_namesrv_NameServerRemoteRpmsg_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_ipc_namesrv_NameServerRemoteRpmsg_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_ipc_namesrv_NameServerRemoteRpmsg_Module_getMask( void ) 
{
    return ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsMask__C != NULL ? *ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_ipc_namesrv_NameServerRemoteRpmsg_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsMask__C != NULL) {
        *ti_ipc_namesrv_NameServerRemoteRpmsg_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_ipc_namesrv_NameServerRemoteRpmsg_Params_init( ti_ipc_namesrv_NameServerRemoteRpmsg_Params *prms ) 
{
    if (prms) {
        ti_ipc_namesrv_NameServerRemoteRpmsg_Params__init__S(prms, 0, sizeof(ti_ipc_namesrv_NameServerRemoteRpmsg_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_ipc_namesrv_NameServerRemoteRpmsg_Params_copy(ti_ipc_namesrv_NameServerRemoteRpmsg_Params *dst, const ti_ipc_namesrv_NameServerRemoteRpmsg_Params *src) 
{
    if (dst) {
        ti_ipc_namesrv_NameServerRemoteRpmsg_Params__init__S(dst, (const void *)src, sizeof(ti_ipc_namesrv_NameServerRemoteRpmsg_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_Object_count() ti_ipc_namesrv_NameServerRemoteRpmsg_Object__count__C

/* Object_sizeof */
#define ti_ipc_namesrv_NameServerRemoteRpmsg_Object_sizeof() ti_ipc_namesrv_NameServerRemoteRpmsg_Object__sizeof__C

/* Object_get */
static inline ti_ipc_namesrv_NameServerRemoteRpmsg_Handle ti_ipc_namesrv_NameServerRemoteRpmsg_Object_get(ti_ipc_namesrv_NameServerRemoteRpmsg_Instance_State *oarr, int i) 
{
    return (ti_ipc_namesrv_NameServerRemoteRpmsg_Handle)ti_ipc_namesrv_NameServerRemoteRpmsg_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_ipc_namesrv_NameServerRemoteRpmsg_Handle ti_ipc_namesrv_NameServerRemoteRpmsg_Object_first( void )
{
    return (ti_ipc_namesrv_NameServerRemoteRpmsg_Handle)ti_ipc_namesrv_NameServerRemoteRpmsg_Object__first__S();
}

/* Object_next */
static inline ti_ipc_namesrv_NameServerRemoteRpmsg_Handle ti_ipc_namesrv_NameServerRemoteRpmsg_Object_next( ti_ipc_namesrv_NameServerRemoteRpmsg_Object *obj )
{
    return (ti_ipc_namesrv_NameServerRemoteRpmsg_Handle)ti_ipc_namesrv_NameServerRemoteRpmsg_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_label( ti_ipc_namesrv_NameServerRemoteRpmsg_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_ipc_namesrv_NameServerRemoteRpmsg_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_name( ti_ipc_namesrv_NameServerRemoteRpmsg_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_ipc_namesrv_NameServerRemoteRpmsg_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_ipc_namesrv_NameServerRemoteRpmsg_Handle ti_ipc_namesrv_NameServerRemoteRpmsg_handle( ti_ipc_namesrv_NameServerRemoteRpmsg_Struct *str )
{
    return (ti_ipc_namesrv_NameServerRemoteRpmsg_Handle)str;
}

/* struct */
static inline ti_ipc_namesrv_NameServerRemoteRpmsg_Struct *ti_ipc_namesrv_NameServerRemoteRpmsg_struct( ti_ipc_namesrv_NameServerRemoteRpmsg_Handle inst )
{
    return (ti_ipc_namesrv_NameServerRemoteRpmsg_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_ipc_namesrv_NameServerRemoteRpmsg__top__
#undef __nested__
#endif

#endif /* ti_ipc_namesrv_NameServerRemoteRpmsg__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_ipc_namesrv_NameServerRemoteRpmsg__internalaccess))

#ifndef ti_ipc_namesrv_NameServerRemoteRpmsg__include_state
#define ti_ipc_namesrv_NameServerRemoteRpmsg__include_state

/* Module_State */
struct ti_ipc_namesrv_NameServerRemoteRpmsg_Module_State {
    ti_sysbios_knl_Semaphore_Handle semRemoteWait;
    ti_sysbios_gates_GateMutex_Handle gateMutex;
    xdc_Ptr nsMsg;
    xdc_Int nsPort;
};

/* Module__state__V */
extern struct ti_ipc_namesrv_NameServerRemoteRpmsg_Module_State__ ti_ipc_namesrv_NameServerRemoteRpmsg_Module__state__V;

/* Object */
struct ti_ipc_namesrv_NameServerRemoteRpmsg_Object {
    const ti_ipc_namesrv_NameServerRemoteRpmsg_Fxns__ *__fxns;
    xdc_UInt16 remoteProcId;
};

#endif /* ti_ipc_namesrv_NameServerRemoteRpmsg__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_ipc_namesrv_NameServerRemoteRpmsg__nolocalnames)

#ifndef ti_ipc_namesrv_NameServerRemoteRpmsg__localnames__done
#define ti_ipc_namesrv_NameServerRemoteRpmsg__localnames__done

/* module prefix */
#define NameServerRemoteRpmsg_Instance ti_ipc_namesrv_NameServerRemoteRpmsg_Instance
#define NameServerRemoteRpmsg_Handle ti_ipc_namesrv_NameServerRemoteRpmsg_Handle
#define NameServerRemoteRpmsg_Module ti_ipc_namesrv_NameServerRemoteRpmsg_Module
#define NameServerRemoteRpmsg_Object ti_ipc_namesrv_NameServerRemoteRpmsg_Object
#define NameServerRemoteRpmsg_Struct ti_ipc_namesrv_NameServerRemoteRpmsg_Struct
#define NameServerRemoteRpmsg_Status ti_ipc_namesrv_NameServerRemoteRpmsg_Status
#define NameServerRemoteRpmsg_Type ti_ipc_namesrv_NameServerRemoteRpmsg_Type
#define NameServerRemoteRpmsg_Instance_State ti_ipc_namesrv_NameServerRemoteRpmsg_Instance_State
#define NameServerRemoteRpmsg_Module_State ti_ipc_namesrv_NameServerRemoteRpmsg_Module_State
#define NameServerRemoteRpmsg_S_SUCCESS ti_ipc_namesrv_NameServerRemoteRpmsg_S_SUCCESS
#define NameServerRemoteRpmsg_E_FAIL ti_ipc_namesrv_NameServerRemoteRpmsg_E_FAIL
#define NameServerRemoteRpmsg_E_ERROR ti_ipc_namesrv_NameServerRemoteRpmsg_E_ERROR
#define NameServerRemoteRpmsg_REQUEST ti_ipc_namesrv_NameServerRemoteRpmsg_REQUEST
#define NameServerRemoteRpmsg_RESPONSE ti_ipc_namesrv_NameServerRemoteRpmsg_RESPONSE
#define NameServerRemoteRpmsg_timeoutInMicroSecs ti_ipc_namesrv_NameServerRemoteRpmsg_timeoutInMicroSecs
#define NameServerRemoteRpmsg_A_nameIsTooLong ti_ipc_namesrv_NameServerRemoteRpmsg_A_nameIsTooLong
#define NameServerRemoteRpmsg_timeout ti_ipc_namesrv_NameServerRemoteRpmsg_timeout
#define NameServerRemoteRpmsg_Params ti_ipc_namesrv_NameServerRemoteRpmsg_Params
#define NameServerRemoteRpmsg_attach ti_ipc_namesrv_NameServerRemoteRpmsg_attach
#define NameServerRemoteRpmsg_detach ti_ipc_namesrv_NameServerRemoteRpmsg_detach
#define NameServerRemoteRpmsg_sharedMemReq ti_ipc_namesrv_NameServerRemoteRpmsg_sharedMemReq
#define NameServerRemoteRpmsg_get ti_ipc_namesrv_NameServerRemoteRpmsg_get
#define NameServerRemoteRpmsg_Module_name ti_ipc_namesrv_NameServerRemoteRpmsg_Module_name
#define NameServerRemoteRpmsg_Module_id ti_ipc_namesrv_NameServerRemoteRpmsg_Module_id
#define NameServerRemoteRpmsg_Module_startup ti_ipc_namesrv_NameServerRemoteRpmsg_Module_startup
#define NameServerRemoteRpmsg_Module_startupDone ti_ipc_namesrv_NameServerRemoteRpmsg_Module_startupDone
#define NameServerRemoteRpmsg_Module_hasMask ti_ipc_namesrv_NameServerRemoteRpmsg_Module_hasMask
#define NameServerRemoteRpmsg_Module_getMask ti_ipc_namesrv_NameServerRemoteRpmsg_Module_getMask
#define NameServerRemoteRpmsg_Module_setMask ti_ipc_namesrv_NameServerRemoteRpmsg_Module_setMask
#define NameServerRemoteRpmsg_Object_heap ti_ipc_namesrv_NameServerRemoteRpmsg_Object_heap
#define NameServerRemoteRpmsg_Module_heap ti_ipc_namesrv_NameServerRemoteRpmsg_Module_heap
#define NameServerRemoteRpmsg_construct ti_ipc_namesrv_NameServerRemoteRpmsg_construct
#define NameServerRemoteRpmsg_create ti_ipc_namesrv_NameServerRemoteRpmsg_create
#define NameServerRemoteRpmsg_handle ti_ipc_namesrv_NameServerRemoteRpmsg_handle
#define NameServerRemoteRpmsg_struct ti_ipc_namesrv_NameServerRemoteRpmsg_struct
#define NameServerRemoteRpmsg_Handle_label ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_label
#define NameServerRemoteRpmsg_Handle_name ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_name
#define NameServerRemoteRpmsg_Instance_init ti_ipc_namesrv_NameServerRemoteRpmsg_Instance_init
#define NameServerRemoteRpmsg_Object_count ti_ipc_namesrv_NameServerRemoteRpmsg_Object_count
#define NameServerRemoteRpmsg_Object_get ti_ipc_namesrv_NameServerRemoteRpmsg_Object_get
#define NameServerRemoteRpmsg_Object_first ti_ipc_namesrv_NameServerRemoteRpmsg_Object_first
#define NameServerRemoteRpmsg_Object_next ti_ipc_namesrv_NameServerRemoteRpmsg_Object_next
#define NameServerRemoteRpmsg_Object_sizeof ti_ipc_namesrv_NameServerRemoteRpmsg_Object_sizeof
#define NameServerRemoteRpmsg_Params_copy ti_ipc_namesrv_NameServerRemoteRpmsg_Params_copy
#define NameServerRemoteRpmsg_Params_init ti_ipc_namesrv_NameServerRemoteRpmsg_Params_init
#define NameServerRemoteRpmsg_Instance_finalize ti_ipc_namesrv_NameServerRemoteRpmsg_Instance_finalize
#define NameServerRemoteRpmsg_delete ti_ipc_namesrv_NameServerRemoteRpmsg_delete
#define NameServerRemoteRpmsg_destruct ti_ipc_namesrv_NameServerRemoteRpmsg_destruct
#define NameServerRemoteRpmsg_Module_upCast ti_ipc_namesrv_NameServerRemoteRpmsg_Module_upCast
#define NameServerRemoteRpmsg_Module_to_ti_sdo_utils_INameServerRemote ti_ipc_namesrv_NameServerRemoteRpmsg_Module_to_ti_sdo_utils_INameServerRemote
#define NameServerRemoteRpmsg_Handle_upCast ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_upCast
#define NameServerRemoteRpmsg_Handle_to_ti_sdo_utils_INameServerRemote ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_to_ti_sdo_utils_INameServerRemote
#define NameServerRemoteRpmsg_Handle_downCast ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_downCast
#define NameServerRemoteRpmsg_Handle_from_ti_sdo_utils_INameServerRemote ti_ipc_namesrv_NameServerRemoteRpmsg_Handle_from_ti_sdo_utils_INameServerRemote

#endif /* ti_ipc_namesrv_NameServerRemoteRpmsg__localnames__done */
#endif
