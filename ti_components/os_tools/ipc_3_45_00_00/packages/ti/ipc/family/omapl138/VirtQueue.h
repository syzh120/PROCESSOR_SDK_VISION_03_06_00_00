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

#ifndef ti_ipc_family_omapl138_VirtQueue__include
#define ti_ipc_family_omapl138_VirtQueue__include

#ifndef __nested__
#define __nested__
#define ti_ipc_family_omapl138_VirtQueue__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_ipc_family_omapl138_VirtQueue___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/ipc/family/omapl138/package/package.defs.h>

#include <ti/sysbios/knl/Swi.h>
#include <ti/sdo/utils/MultiProc.h>
#include <ti/sysbios/gates/GateAll.h>
#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_ipc_family_omapl138_VirtQueue_Args__create {
    xdc_UInt16 remoteProcId;
} ti_ipc_family_omapl138_VirtQueue_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_ipc_family_omapl138_VirtQueue_Module__diagsEnabled;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__diagsEnabled ti_ipc_family_omapl138_VirtQueue_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_ipc_family_omapl138_VirtQueue_Module__diagsIncluded;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__diagsIncluded ti_ipc_family_omapl138_VirtQueue_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_ipc_family_omapl138_VirtQueue_Module__diagsMask;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__diagsMask ti_ipc_family_omapl138_VirtQueue_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_ipc_family_omapl138_VirtQueue_Module__gateObj;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__gateObj ti_ipc_family_omapl138_VirtQueue_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_ipc_family_omapl138_VirtQueue_Module__gatePrms;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__gatePrms ti_ipc_family_omapl138_VirtQueue_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_ipc_family_omapl138_VirtQueue_Module__id;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__id ti_ipc_family_omapl138_VirtQueue_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerDefined;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerDefined ti_ipc_family_omapl138_VirtQueue_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerObj;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerObj ti_ipc_family_omapl138_VirtQueue_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn0;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn0 ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn1;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn1 ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn2;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn2 ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn4;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn4 ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn8;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn8 ti_ipc_family_omapl138_VirtQueue_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_ipc_family_omapl138_VirtQueue_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Module__startupDoneFxn ti_ipc_family_omapl138_VirtQueue_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_ipc_family_omapl138_VirtQueue_Object__count;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Object__count ti_ipc_family_omapl138_VirtQueue_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_ipc_family_omapl138_VirtQueue_Object__heap;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Object__heap ti_ipc_family_omapl138_VirtQueue_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_ipc_family_omapl138_VirtQueue_Object__sizeof;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Object__sizeof ti_ipc_family_omapl138_VirtQueue_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_ipc_family_omapl138_VirtQueue_Object__table;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_Object__table ti_ipc_family_omapl138_VirtQueue_Object__table__C;

/* VQ0_SIZE */
#ifdef ti_ipc_family_omapl138_VirtQueue_VQ0_SIZE__D
#define ti_ipc_family_omapl138_VirtQueue_VQ0_SIZE (ti_ipc_family_omapl138_VirtQueue_VQ0_SIZE__D)
#else
#define ti_ipc_family_omapl138_VirtQueue_VQ0_SIZE (ti_ipc_family_omapl138_VirtQueue_VQ0_SIZE__C)
typedef xdc_UInt CT__ti_ipc_family_omapl138_VirtQueue_VQ0_SIZE;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_VQ0_SIZE ti_ipc_family_omapl138_VirtQueue_VQ0_SIZE__C;
#endif

/* VQ1_SIZE */
#ifdef ti_ipc_family_omapl138_VirtQueue_VQ1_SIZE__D
#define ti_ipc_family_omapl138_VirtQueue_VQ1_SIZE (ti_ipc_family_omapl138_VirtQueue_VQ1_SIZE__D)
#else
#define ti_ipc_family_omapl138_VirtQueue_VQ1_SIZE (ti_ipc_family_omapl138_VirtQueue_VQ1_SIZE__C)
typedef xdc_UInt CT__ti_ipc_family_omapl138_VirtQueue_VQ1_SIZE;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_VQ1_SIZE ti_ipc_family_omapl138_VirtQueue_VQ1_SIZE__C;
#endif

/* RP_MSG_NUM_BUFS */
#ifdef ti_ipc_family_omapl138_VirtQueue_RP_MSG_NUM_BUFS__D
#define ti_ipc_family_omapl138_VirtQueue_RP_MSG_NUM_BUFS (ti_ipc_family_omapl138_VirtQueue_RP_MSG_NUM_BUFS__D)
#else
#define ti_ipc_family_omapl138_VirtQueue_RP_MSG_NUM_BUFS (ti_ipc_family_omapl138_VirtQueue_RP_MSG_NUM_BUFS__C)
typedef xdc_UInt CT__ti_ipc_family_omapl138_VirtQueue_RP_MSG_NUM_BUFS;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_RP_MSG_NUM_BUFS ti_ipc_family_omapl138_VirtQueue_RP_MSG_NUM_BUFS__C;
#endif

/* PAGE_SIZE */
#ifdef ti_ipc_family_omapl138_VirtQueue_PAGE_SIZE__D
#define ti_ipc_family_omapl138_VirtQueue_PAGE_SIZE (ti_ipc_family_omapl138_VirtQueue_PAGE_SIZE__D)
#else
#define ti_ipc_family_omapl138_VirtQueue_PAGE_SIZE (ti_ipc_family_omapl138_VirtQueue_PAGE_SIZE__C)
typedef xdc_UInt CT__ti_ipc_family_omapl138_VirtQueue_PAGE_SIZE;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_PAGE_SIZE ti_ipc_family_omapl138_VirtQueue_PAGE_SIZE__C;
#endif

/* RP_MSG_VRING_ALIGN */
#ifdef ti_ipc_family_omapl138_VirtQueue_RP_MSG_VRING_ALIGN__D
#define ti_ipc_family_omapl138_VirtQueue_RP_MSG_VRING_ALIGN (ti_ipc_family_omapl138_VirtQueue_RP_MSG_VRING_ALIGN__D)
#else
#define ti_ipc_family_omapl138_VirtQueue_RP_MSG_VRING_ALIGN (ti_ipc_family_omapl138_VirtQueue_RP_MSG_VRING_ALIGN__C)
typedef xdc_UInt CT__ti_ipc_family_omapl138_VirtQueue_RP_MSG_VRING_ALIGN;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_RP_MSG_VRING_ALIGN ti_ipc_family_omapl138_VirtQueue_RP_MSG_VRING_ALIGN__C;
#endif

/* hostProcId */
#ifdef ti_ipc_family_omapl138_VirtQueue_hostProcId__D
#define ti_ipc_family_omapl138_VirtQueue_hostProcId (ti_ipc_family_omapl138_VirtQueue_hostProcId__D)
#else
#define ti_ipc_family_omapl138_VirtQueue_hostProcId (ti_ipc_family_omapl138_VirtQueue_hostProcId__C)
typedef xdc_UInt CT__ti_ipc_family_omapl138_VirtQueue_hostProcId;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_hostProcId ti_ipc_family_omapl138_VirtQueue_hostProcId__C;
#endif

/* dspProcId */
#ifdef ti_ipc_family_omapl138_VirtQueue_dspProcId__D
#define ti_ipc_family_omapl138_VirtQueue_dspProcId (ti_ipc_family_omapl138_VirtQueue_dspProcId__D)
#else
#define ti_ipc_family_omapl138_VirtQueue_dspProcId (ti_ipc_family_omapl138_VirtQueue_dspProcId__C)
typedef xdc_UInt CT__ti_ipc_family_omapl138_VirtQueue_dspProcId;
__extern __FAR__ const CT__ti_ipc_family_omapl138_VirtQueue_dspProcId ti_ipc_family_omapl138_VirtQueue_dspProcId__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_ipc_family_omapl138_VirtQueue_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_Fxn callback;
    xdc_Int vqId;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_ipc_family_omapl138_VirtQueue_Struct {
    xdc_Bool __f0;
    xdc_UInt16 __f1;
    xdc_Fxn __f2;
    xdc_Void *__f3;
    xdc_UInt16 __f4;
    xdc_UInt16 __f5;
    xdc_UInt16 __f6;
    xdc_UInt16 __f7;
    ti_sysbios_gates_GateAll_Handle __f8;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_ipc_family_omapl138_VirtQueue_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_Instance_init__E, "ti_ipc_family_omapl138_VirtQueue_Instance_init")
__extern xdc_Int ti_ipc_family_omapl138_VirtQueue_Instance_init__E(ti_ipc_family_omapl138_VirtQueue_Object *, xdc_UInt16 remoteProcId, const ti_ipc_family_omapl138_VirtQueue_Params *, xdc_runtime_Error_Block *);

/* Handle__label__S */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_Handle__label__S, "ti_ipc_family_omapl138_VirtQueue_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_ipc_family_omapl138_VirtQueue_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_Module__startupDone__S, "ti_ipc_family_omapl138_VirtQueue_Module__startupDone__S")
__extern xdc_Bool ti_ipc_family_omapl138_VirtQueue_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_Object__create__S, "ti_ipc_family_omapl138_VirtQueue_Object__create__S")
__extern xdc_Ptr ti_ipc_family_omapl138_VirtQueue_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_create, "ti_ipc_family_omapl138_VirtQueue_create")
__extern ti_ipc_family_omapl138_VirtQueue_Handle ti_ipc_family_omapl138_VirtQueue_create( xdc_UInt16 remoteProcId, const ti_ipc_family_omapl138_VirtQueue_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_construct, "ti_ipc_family_omapl138_VirtQueue_construct")
__extern void ti_ipc_family_omapl138_VirtQueue_construct( ti_ipc_family_omapl138_VirtQueue_Struct *__obj, xdc_UInt16 remoteProcId, const ti_ipc_family_omapl138_VirtQueue_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_Object__delete__S, "ti_ipc_family_omapl138_VirtQueue_Object__delete__S")
__extern xdc_Void ti_ipc_family_omapl138_VirtQueue_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_delete, "ti_ipc_family_omapl138_VirtQueue_delete")
__extern void ti_ipc_family_omapl138_VirtQueue_delete(ti_ipc_family_omapl138_VirtQueue_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_Object__destruct__S, "ti_ipc_family_omapl138_VirtQueue_Object__destruct__S")
__extern xdc_Void ti_ipc_family_omapl138_VirtQueue_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_destruct, "ti_ipc_family_omapl138_VirtQueue_destruct")
__extern void ti_ipc_family_omapl138_VirtQueue_destruct(ti_ipc_family_omapl138_VirtQueue_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_Object__get__S, "ti_ipc_family_omapl138_VirtQueue_Object__get__S")
__extern xdc_Ptr ti_ipc_family_omapl138_VirtQueue_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_Object__first__S, "ti_ipc_family_omapl138_VirtQueue_Object__first__S")
__extern xdc_Ptr ti_ipc_family_omapl138_VirtQueue_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_Object__next__S, "ti_ipc_family_omapl138_VirtQueue_Object__next__S")
__extern xdc_Ptr ti_ipc_family_omapl138_VirtQueue_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_Params__init__S, "ti_ipc_family_omapl138_VirtQueue_Params__init__S")
__extern xdc_Void ti_ipc_family_omapl138_VirtQueue_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* startup__E */
#define ti_ipc_family_omapl138_VirtQueue_startup ti_ipc_family_omapl138_VirtQueue_startup__E
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_startup__E, "ti_ipc_family_omapl138_VirtQueue_startup")
__extern xdc_Void ti_ipc_family_omapl138_VirtQueue_startup__E( xdc_UInt16 remoteProcId, xdc_Bool isHost );
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_startup__F, "ti_ipc_family_omapl138_VirtQueue_startup")
__extern xdc_Void ti_ipc_family_omapl138_VirtQueue_startup__F( xdc_UInt16 remoteProcId, xdc_Bool isHost );

/* kick__E */
#define ti_ipc_family_omapl138_VirtQueue_kick ti_ipc_family_omapl138_VirtQueue_kick__E
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_kick__E, "ti_ipc_family_omapl138_VirtQueue_kick")
__extern xdc_Void ti_ipc_family_omapl138_VirtQueue_kick__E( ti_ipc_family_omapl138_VirtQueue_Handle __inst );

/* isSlave__E */
#define ti_ipc_family_omapl138_VirtQueue_isSlave ti_ipc_family_omapl138_VirtQueue_isSlave__E
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_isSlave__E, "ti_ipc_family_omapl138_VirtQueue_isSlave")
__extern xdc_Bool ti_ipc_family_omapl138_VirtQueue_isSlave__E( ti_ipc_family_omapl138_VirtQueue_Handle __inst );

/* isHost__E */
#define ti_ipc_family_omapl138_VirtQueue_isHost ti_ipc_family_omapl138_VirtQueue_isHost__E
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_isHost__E, "ti_ipc_family_omapl138_VirtQueue_isHost")
__extern xdc_Bool ti_ipc_family_omapl138_VirtQueue_isHost__E( ti_ipc_family_omapl138_VirtQueue_Handle __inst );

/* getId__E */
#define ti_ipc_family_omapl138_VirtQueue_getId ti_ipc_family_omapl138_VirtQueue_getId__E
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_getId__E, "ti_ipc_family_omapl138_VirtQueue_getId")
__extern xdc_UInt16 ti_ipc_family_omapl138_VirtQueue_getId__E( ti_ipc_family_omapl138_VirtQueue_Handle __inst );

/* getSwiHandle__E */
#define ti_ipc_family_omapl138_VirtQueue_getSwiHandle ti_ipc_family_omapl138_VirtQueue_getSwiHandle__E
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_getSwiHandle__E, "ti_ipc_family_omapl138_VirtQueue_getSwiHandle")
__extern ti_sysbios_knl_Swi_Handle ti_ipc_family_omapl138_VirtQueue_getSwiHandle__E( ti_ipc_family_omapl138_VirtQueue_Handle __inst );

/* addAvailBuf__E */
#define ti_ipc_family_omapl138_VirtQueue_addAvailBuf ti_ipc_family_omapl138_VirtQueue_addAvailBuf__E
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_addAvailBuf__E, "ti_ipc_family_omapl138_VirtQueue_addAvailBuf")
__extern xdc_Int ti_ipc_family_omapl138_VirtQueue_addAvailBuf__E( ti_ipc_family_omapl138_VirtQueue_Handle __inst, xdc_Void *buf );

/* getUsedBuf__E */
#define ti_ipc_family_omapl138_VirtQueue_getUsedBuf ti_ipc_family_omapl138_VirtQueue_getUsedBuf__E
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_getUsedBuf__E, "ti_ipc_family_omapl138_VirtQueue_getUsedBuf")
__extern xdc_Void *ti_ipc_family_omapl138_VirtQueue_getUsedBuf__E( ti_ipc_family_omapl138_VirtQueue_Handle __inst );

/* getAvailBuf__E */
#define ti_ipc_family_omapl138_VirtQueue_getAvailBuf ti_ipc_family_omapl138_VirtQueue_getAvailBuf__E
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_getAvailBuf__E, "ti_ipc_family_omapl138_VirtQueue_getAvailBuf")
__extern xdc_Int16 ti_ipc_family_omapl138_VirtQueue_getAvailBuf__E( ti_ipc_family_omapl138_VirtQueue_Handle __inst, xdc_Void **buf, xdc_Int *len );

/* addUsedBuf__E */
#define ti_ipc_family_omapl138_VirtQueue_addUsedBuf ti_ipc_family_omapl138_VirtQueue_addUsedBuf__E
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_addUsedBuf__E, "ti_ipc_family_omapl138_VirtQueue_addUsedBuf")
__extern xdc_Int ti_ipc_family_omapl138_VirtQueue_addUsedBuf__E( ti_ipc_family_omapl138_VirtQueue_Handle __inst, xdc_Int16 token, xdc_Int len );

/* hostIsr__I */
#define ti_ipc_family_omapl138_VirtQueue_hostIsr ti_ipc_family_omapl138_VirtQueue_hostIsr__I
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_hostIsr__I, "ti_ipc_family_omapl138_VirtQueue_hostIsr")
__extern xdc_Void ti_ipc_family_omapl138_VirtQueue_hostIsr__I( xdc_UArg msg );

/* slaveIsr__I */
#define ti_ipc_family_omapl138_VirtQueue_slaveIsr ti_ipc_family_omapl138_VirtQueue_slaveIsr__I
xdc__CODESECT(ti_ipc_family_omapl138_VirtQueue_slaveIsr__I, "ti_ipc_family_omapl138_VirtQueue_slaveIsr")
__extern xdc_Void ti_ipc_family_omapl138_VirtQueue_slaveIsr__I( xdc_UArg msg );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_ipc_family_omapl138_VirtQueue_Module_startupDone() ti_ipc_family_omapl138_VirtQueue_Module__startupDone__S()

/* Object_heap */
#define ti_ipc_family_omapl138_VirtQueue_Object_heap() ti_ipc_family_omapl138_VirtQueue_Object__heap__C

/* Module_heap */
#define ti_ipc_family_omapl138_VirtQueue_Module_heap() ti_ipc_family_omapl138_VirtQueue_Object__heap__C

/* Module_id */
static inline CT__ti_ipc_family_omapl138_VirtQueue_Module__id ti_ipc_family_omapl138_VirtQueue_Module_id( void ) 
{
    return ti_ipc_family_omapl138_VirtQueue_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_ipc_family_omapl138_VirtQueue_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_ipc_family_omapl138_VirtQueue_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_ipc_family_omapl138_VirtQueue_Module_getMask( void ) 
{
    return ti_ipc_family_omapl138_VirtQueue_Module__diagsMask__C != NULL ? *ti_ipc_family_omapl138_VirtQueue_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_ipc_family_omapl138_VirtQueue_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_ipc_family_omapl138_VirtQueue_Module__diagsMask__C != NULL) {
        *ti_ipc_family_omapl138_VirtQueue_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_ipc_family_omapl138_VirtQueue_Params_init( ti_ipc_family_omapl138_VirtQueue_Params *prms ) 
{
    if (prms) {
        ti_ipc_family_omapl138_VirtQueue_Params__init__S(prms, 0, sizeof(ti_ipc_family_omapl138_VirtQueue_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_ipc_family_omapl138_VirtQueue_Params_copy(ti_ipc_family_omapl138_VirtQueue_Params *dst, const ti_ipc_family_omapl138_VirtQueue_Params *src) 
{
    if (dst) {
        ti_ipc_family_omapl138_VirtQueue_Params__init__S(dst, (const void *)src, sizeof(ti_ipc_family_omapl138_VirtQueue_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_ipc_family_omapl138_VirtQueue_Object_count() ti_ipc_family_omapl138_VirtQueue_Object__count__C

/* Object_sizeof */
#define ti_ipc_family_omapl138_VirtQueue_Object_sizeof() ti_ipc_family_omapl138_VirtQueue_Object__sizeof__C

/* Object_get */
static inline ti_ipc_family_omapl138_VirtQueue_Handle ti_ipc_family_omapl138_VirtQueue_Object_get(ti_ipc_family_omapl138_VirtQueue_Instance_State *oarr, int i) 
{
    return (ti_ipc_family_omapl138_VirtQueue_Handle)ti_ipc_family_omapl138_VirtQueue_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_ipc_family_omapl138_VirtQueue_Handle ti_ipc_family_omapl138_VirtQueue_Object_first( void )
{
    return (ti_ipc_family_omapl138_VirtQueue_Handle)ti_ipc_family_omapl138_VirtQueue_Object__first__S();
}

/* Object_next */
static inline ti_ipc_family_omapl138_VirtQueue_Handle ti_ipc_family_omapl138_VirtQueue_Object_next( ti_ipc_family_omapl138_VirtQueue_Object *obj )
{
    return (ti_ipc_family_omapl138_VirtQueue_Handle)ti_ipc_family_omapl138_VirtQueue_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_ipc_family_omapl138_VirtQueue_Handle_label( ti_ipc_family_omapl138_VirtQueue_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_ipc_family_omapl138_VirtQueue_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_ipc_family_omapl138_VirtQueue_Handle_name( ti_ipc_family_omapl138_VirtQueue_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_ipc_family_omapl138_VirtQueue_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_ipc_family_omapl138_VirtQueue_Handle ti_ipc_family_omapl138_VirtQueue_handle( ti_ipc_family_omapl138_VirtQueue_Struct *str )
{
    return (ti_ipc_family_omapl138_VirtQueue_Handle)str;
}

/* struct */
static inline ti_ipc_family_omapl138_VirtQueue_Struct *ti_ipc_family_omapl138_VirtQueue_struct( ti_ipc_family_omapl138_VirtQueue_Handle inst )
{
    return (ti_ipc_family_omapl138_VirtQueue_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_ipc_family_omapl138_VirtQueue__top__
#undef __nested__
#endif

#endif /* ti_ipc_family_omapl138_VirtQueue__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_ipc_family_omapl138_VirtQueue__internalaccess))

#ifndef ti_ipc_family_omapl138_VirtQueue__include_state
#define ti_ipc_family_omapl138_VirtQueue__include_state

/* Module_State */
struct ti_ipc_family_omapl138_VirtQueue_Module_State {
    xdc_UInt16 hostSlaveSynced;
    xdc_UInt16 virtQueueInitialized;
    xdc_UInt32 *queueRegistry;
    xdc_Ptr traceBufPtr;
};

/* Module__state__V */
extern struct ti_ipc_family_omapl138_VirtQueue_Module_State__ ti_ipc_family_omapl138_VirtQueue_Module__state__V;

/* Object */
struct ti_ipc_family_omapl138_VirtQueue_Object {
    xdc_Bool hostSlaveSynced;
    xdc_UInt16 id;
    xdc_Fxn callback;
    xdc_Void *vringPtr;
    xdc_UInt16 num_free;
    xdc_UInt16 last_avail_idx;
    xdc_UInt16 last_used_idx;
    xdc_UInt16 procId;
    ti_sysbios_gates_GateAll_Handle gateH;
};

#endif /* ti_ipc_family_omapl138_VirtQueue__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_ipc_family_omapl138_VirtQueue__nolocalnames)

#ifndef ti_ipc_family_omapl138_VirtQueue__localnames__done
#define ti_ipc_family_omapl138_VirtQueue__localnames__done

/* module prefix */
#define VirtQueue_Instance ti_ipc_family_omapl138_VirtQueue_Instance
#define VirtQueue_Handle ti_ipc_family_omapl138_VirtQueue_Handle
#define VirtQueue_Module ti_ipc_family_omapl138_VirtQueue_Module
#define VirtQueue_Object ti_ipc_family_omapl138_VirtQueue_Object
#define VirtQueue_Struct ti_ipc_family_omapl138_VirtQueue_Struct
#define VirtQueue_Module_State ti_ipc_family_omapl138_VirtQueue_Module_State
#define VirtQueue_Instance_State ti_ipc_family_omapl138_VirtQueue_Instance_State
#define VirtQueue_VQ0_SIZE ti_ipc_family_omapl138_VirtQueue_VQ0_SIZE
#define VirtQueue_VQ1_SIZE ti_ipc_family_omapl138_VirtQueue_VQ1_SIZE
#define VirtQueue_RP_MSG_NUM_BUFS ti_ipc_family_omapl138_VirtQueue_RP_MSG_NUM_BUFS
#define VirtQueue_PAGE_SIZE ti_ipc_family_omapl138_VirtQueue_PAGE_SIZE
#define VirtQueue_RP_MSG_VRING_ALIGN ti_ipc_family_omapl138_VirtQueue_RP_MSG_VRING_ALIGN
#define VirtQueue_hostProcId ti_ipc_family_omapl138_VirtQueue_hostProcId
#define VirtQueue_dspProcId ti_ipc_family_omapl138_VirtQueue_dspProcId
#define VirtQueue_Params ti_ipc_family_omapl138_VirtQueue_Params
#define VirtQueue_startup ti_ipc_family_omapl138_VirtQueue_startup
#define VirtQueue_kick ti_ipc_family_omapl138_VirtQueue_kick
#define VirtQueue_isSlave ti_ipc_family_omapl138_VirtQueue_isSlave
#define VirtQueue_isHost ti_ipc_family_omapl138_VirtQueue_isHost
#define VirtQueue_getId ti_ipc_family_omapl138_VirtQueue_getId
#define VirtQueue_getSwiHandle ti_ipc_family_omapl138_VirtQueue_getSwiHandle
#define VirtQueue_addAvailBuf ti_ipc_family_omapl138_VirtQueue_addAvailBuf
#define VirtQueue_getUsedBuf ti_ipc_family_omapl138_VirtQueue_getUsedBuf
#define VirtQueue_getAvailBuf ti_ipc_family_omapl138_VirtQueue_getAvailBuf
#define VirtQueue_addUsedBuf ti_ipc_family_omapl138_VirtQueue_addUsedBuf
#define VirtQueue_Module_name ti_ipc_family_omapl138_VirtQueue_Module_name
#define VirtQueue_Module_id ti_ipc_family_omapl138_VirtQueue_Module_id
#define VirtQueue_Module_startup ti_ipc_family_omapl138_VirtQueue_Module_startup
#define VirtQueue_Module_startupDone ti_ipc_family_omapl138_VirtQueue_Module_startupDone
#define VirtQueue_Module_hasMask ti_ipc_family_omapl138_VirtQueue_Module_hasMask
#define VirtQueue_Module_getMask ti_ipc_family_omapl138_VirtQueue_Module_getMask
#define VirtQueue_Module_setMask ti_ipc_family_omapl138_VirtQueue_Module_setMask
#define VirtQueue_Object_heap ti_ipc_family_omapl138_VirtQueue_Object_heap
#define VirtQueue_Module_heap ti_ipc_family_omapl138_VirtQueue_Module_heap
#define VirtQueue_construct ti_ipc_family_omapl138_VirtQueue_construct
#define VirtQueue_create ti_ipc_family_omapl138_VirtQueue_create
#define VirtQueue_handle ti_ipc_family_omapl138_VirtQueue_handle
#define VirtQueue_struct ti_ipc_family_omapl138_VirtQueue_struct
#define VirtQueue_Handle_label ti_ipc_family_omapl138_VirtQueue_Handle_label
#define VirtQueue_Handle_name ti_ipc_family_omapl138_VirtQueue_Handle_name
#define VirtQueue_Instance_init ti_ipc_family_omapl138_VirtQueue_Instance_init
#define VirtQueue_Object_count ti_ipc_family_omapl138_VirtQueue_Object_count
#define VirtQueue_Object_get ti_ipc_family_omapl138_VirtQueue_Object_get
#define VirtQueue_Object_first ti_ipc_family_omapl138_VirtQueue_Object_first
#define VirtQueue_Object_next ti_ipc_family_omapl138_VirtQueue_Object_next
#define VirtQueue_Object_sizeof ti_ipc_family_omapl138_VirtQueue_Object_sizeof
#define VirtQueue_Params_copy ti_ipc_family_omapl138_VirtQueue_Params_copy
#define VirtQueue_Params_init ti_ipc_family_omapl138_VirtQueue_Params_init
#define VirtQueue_delete ti_ipc_family_omapl138_VirtQueue_delete
#define VirtQueue_destruct ti_ipc_family_omapl138_VirtQueue_destruct

#endif /* ti_ipc_family_omapl138_VirtQueue__localnames__done */
#endif
