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

#ifndef ti_ipc_remoteproc_Resource__include
#define ti_ipc_remoteproc_Resource__include

#ifndef __nested__
#define __nested__
#define ti_ipc_remoteproc_Resource__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_ipc_remoteproc_Resource___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/ipc/remoteproc/package/package.defs.h>

#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* S_SUCCESS */
#define ti_ipc_remoteproc_Resource_S_SUCCESS (0)

/* E_NOTFOUND */
#define ti_ipc_remoteproc_Resource_E_NOTFOUND (-1)

/* RscTable */
typedef xdc_UInt32 __T1_ti_ipc_remoteproc_Resource_RscTable__reserved;
typedef xdc_UInt32 __ARRAY1_ti_ipc_remoteproc_Resource_RscTable__reserved[2];
typedef __ARRAY1_ti_ipc_remoteproc_Resource_RscTable__reserved __TA_ti_ipc_remoteproc_Resource_RscTable__reserved;
typedef xdc_UInt32 __T1_ti_ipc_remoteproc_Resource_RscTable__offset;
typedef xdc_UInt32 __ARRAY1_ti_ipc_remoteproc_Resource_RscTable__offset[1];
typedef __ARRAY1_ti_ipc_remoteproc_Resource_RscTable__offset __TA_ti_ipc_remoteproc_Resource_RscTable__offset;
struct ti_ipc_remoteproc_Resource_RscTable {
    xdc_UInt32 ver;
    xdc_UInt32 num;
    __TA_ti_ipc_remoteproc_Resource_RscTable__reserved reserved;
    __TA_ti_ipc_remoteproc_Resource_RscTable__offset offset;
};

/* MemEntry */
typedef xdc_Char __T1_ti_ipc_remoteproc_Resource_MemEntry__name;
typedef xdc_Char __ARRAY1_ti_ipc_remoteproc_Resource_MemEntry__name[32];
typedef __ARRAY1_ti_ipc_remoteproc_Resource_MemEntry__name __TA_ti_ipc_remoteproc_Resource_MemEntry__name;
struct ti_ipc_remoteproc_Resource_MemEntry {
    xdc_UInt32 type;
    xdc_UInt32 da;
    xdc_UInt32 pa;
    xdc_UInt32 len;
    xdc_UInt32 flags;
    xdc_UInt32 reserved;
    __TA_ti_ipc_remoteproc_Resource_MemEntry__name name;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_ipc_remoteproc_Resource_Module__diagsEnabled;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__diagsEnabled ti_ipc_remoteproc_Resource_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_ipc_remoteproc_Resource_Module__diagsIncluded;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__diagsIncluded ti_ipc_remoteproc_Resource_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_ipc_remoteproc_Resource_Module__diagsMask;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__diagsMask ti_ipc_remoteproc_Resource_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_ipc_remoteproc_Resource_Module__gateObj;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__gateObj ti_ipc_remoteproc_Resource_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_ipc_remoteproc_Resource_Module__gatePrms;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__gatePrms ti_ipc_remoteproc_Resource_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_ipc_remoteproc_Resource_Module__id;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__id ti_ipc_remoteproc_Resource_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_ipc_remoteproc_Resource_Module__loggerDefined;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__loggerDefined ti_ipc_remoteproc_Resource_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_ipc_remoteproc_Resource_Module__loggerObj;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__loggerObj ti_ipc_remoteproc_Resource_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_ipc_remoteproc_Resource_Module__loggerFxn0;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__loggerFxn0 ti_ipc_remoteproc_Resource_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_ipc_remoteproc_Resource_Module__loggerFxn1;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__loggerFxn1 ti_ipc_remoteproc_Resource_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_ipc_remoteproc_Resource_Module__loggerFxn2;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__loggerFxn2 ti_ipc_remoteproc_Resource_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_ipc_remoteproc_Resource_Module__loggerFxn4;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__loggerFxn4 ti_ipc_remoteproc_Resource_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_ipc_remoteproc_Resource_Module__loggerFxn8;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__loggerFxn8 ti_ipc_remoteproc_Resource_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_ipc_remoteproc_Resource_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Module__startupDoneFxn ti_ipc_remoteproc_Resource_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_ipc_remoteproc_Resource_Object__count;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Object__count ti_ipc_remoteproc_Resource_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_ipc_remoteproc_Resource_Object__heap;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Object__heap ti_ipc_remoteproc_Resource_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_ipc_remoteproc_Resource_Object__sizeof;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Object__sizeof ti_ipc_remoteproc_Resource_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_ipc_remoteproc_Resource_Object__table;
__extern __FAR__ const CT__ti_ipc_remoteproc_Resource_Object__table ti_ipc_remoteproc_Resource_Object__table__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_ipc_remoteproc_Resource_Module_startup ti_ipc_remoteproc_Resource_Module_startup__E
xdc__CODESECT(ti_ipc_remoteproc_Resource_Module_startup__E, "ti_ipc_remoteproc_Resource_Module_startup")
__extern xdc_Int ti_ipc_remoteproc_Resource_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_ipc_remoteproc_Resource_Module_startup__F, "ti_ipc_remoteproc_Resource_Module_startup")
__extern xdc_Int ti_ipc_remoteproc_Resource_Module_startup__F( xdc_Int state );

/* Module__startupDone__S */
xdc__CODESECT(ti_ipc_remoteproc_Resource_Module__startupDone__S, "ti_ipc_remoteproc_Resource_Module__startupDone__S")
__extern xdc_Bool ti_ipc_remoteproc_Resource_Module__startupDone__S( void );

/* virtToPhys__E */
#define ti_ipc_remoteproc_Resource_virtToPhys ti_ipc_remoteproc_Resource_virtToPhys__E
xdc__CODESECT(ti_ipc_remoteproc_Resource_virtToPhys__E, "ti_ipc_remoteproc_Resource_virtToPhys")
__extern xdc_Int ti_ipc_remoteproc_Resource_virtToPhys__E( xdc_UInt32 da, xdc_UInt32 *pa );

/* physToVirt__E */
#define ti_ipc_remoteproc_Resource_physToVirt ti_ipc_remoteproc_Resource_physToVirt__E
xdc__CODESECT(ti_ipc_remoteproc_Resource_physToVirt__E, "ti_ipc_remoteproc_Resource_physToVirt")
__extern xdc_Int ti_ipc_remoteproc_Resource_physToVirt__E( xdc_UInt32 pa, xdc_UInt32 *da );

/* getTraceBufPtr__E */
#define ti_ipc_remoteproc_Resource_getTraceBufPtr ti_ipc_remoteproc_Resource_getTraceBufPtr__E
xdc__CODESECT(ti_ipc_remoteproc_Resource_getTraceBufPtr__E, "ti_ipc_remoteproc_Resource_getTraceBufPtr")
__extern xdc_Ptr ti_ipc_remoteproc_Resource_getTraceBufPtr__E( void );

/* getVdevStatus__E */
#define ti_ipc_remoteproc_Resource_getVdevStatus ti_ipc_remoteproc_Resource_getVdevStatus__E
xdc__CODESECT(ti_ipc_remoteproc_Resource_getVdevStatus__E, "ti_ipc_remoteproc_Resource_getVdevStatus")
__extern xdc_Char ti_ipc_remoteproc_Resource_getVdevStatus__E( xdc_UInt32 id );

/* getVringDA__E */
#define ti_ipc_remoteproc_Resource_getVringDA ti_ipc_remoteproc_Resource_getVringDA__E
xdc__CODESECT(ti_ipc_remoteproc_Resource_getVringDA__E, "ti_ipc_remoteproc_Resource_getVringDA")
__extern xdc_Ptr ti_ipc_remoteproc_Resource_getVringDA__E( xdc_UInt32 vqId );

/* init__I */
#define ti_ipc_remoteproc_Resource_init ti_ipc_remoteproc_Resource_init__I
xdc__CODESECT(ti_ipc_remoteproc_Resource_init__I, "ti_ipc_remoteproc_Resource_init")
__extern xdc_Void ti_ipc_remoteproc_Resource_init__I( void );

/* getMemEntry__I */
#define ti_ipc_remoteproc_Resource_getMemEntry ti_ipc_remoteproc_Resource_getMemEntry__I
xdc__CODESECT(ti_ipc_remoteproc_Resource_getMemEntry__I, "ti_ipc_remoteproc_Resource_getMemEntry")
__extern ti_ipc_remoteproc_Resource_MemEntry *ti_ipc_remoteproc_Resource_getMemEntry__I( xdc_UInt index );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_ipc_remoteproc_Resource_Module_startupDone() ti_ipc_remoteproc_Resource_Module__startupDone__S()

/* Object_heap */
#define ti_ipc_remoteproc_Resource_Object_heap() ti_ipc_remoteproc_Resource_Object__heap__C

/* Module_heap */
#define ti_ipc_remoteproc_Resource_Module_heap() ti_ipc_remoteproc_Resource_Object__heap__C

/* Module_id */
static inline CT__ti_ipc_remoteproc_Resource_Module__id ti_ipc_remoteproc_Resource_Module_id( void ) 
{
    return ti_ipc_remoteproc_Resource_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_ipc_remoteproc_Resource_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_ipc_remoteproc_Resource_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_ipc_remoteproc_Resource_Module_getMask( void ) 
{
    return ti_ipc_remoteproc_Resource_Module__diagsMask__C != NULL ? *ti_ipc_remoteproc_Resource_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_ipc_remoteproc_Resource_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_ipc_remoteproc_Resource_Module__diagsMask__C != NULL) {
        *ti_ipc_remoteproc_Resource_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_ipc_remoteproc_Resource__top__
#undef __nested__
#endif

#endif /* ti_ipc_remoteproc_Resource__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_ipc_remoteproc_Resource__internalaccess))

#ifndef ti_ipc_remoteproc_Resource__include_state
#define ti_ipc_remoteproc_Resource__include_state

/* Module_State */
struct ti_ipc_remoteproc_Resource_Module_State {
    ti_ipc_remoteproc_Resource_RscTable *pTable;
};

/* Module__state__V */
extern struct ti_ipc_remoteproc_Resource_Module_State__ ti_ipc_remoteproc_Resource_Module__state__V;

#endif /* ti_ipc_remoteproc_Resource__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_ipc_remoteproc_Resource__nolocalnames)

#ifndef ti_ipc_remoteproc_Resource__localnames__done
#define ti_ipc_remoteproc_Resource__localnames__done

/* module prefix */
#define Resource_S_SUCCESS ti_ipc_remoteproc_Resource_S_SUCCESS
#define Resource_E_NOTFOUND ti_ipc_remoteproc_Resource_E_NOTFOUND
#define Resource_RscTable ti_ipc_remoteproc_Resource_RscTable
#define Resource_MemEntry ti_ipc_remoteproc_Resource_MemEntry
#define Resource_Module_State ti_ipc_remoteproc_Resource_Module_State
#define Resource_virtToPhys ti_ipc_remoteproc_Resource_virtToPhys
#define Resource_physToVirt ti_ipc_remoteproc_Resource_physToVirt
#define Resource_getTraceBufPtr ti_ipc_remoteproc_Resource_getTraceBufPtr
#define Resource_getVdevStatus ti_ipc_remoteproc_Resource_getVdevStatus
#define Resource_getVringDA ti_ipc_remoteproc_Resource_getVringDA
#define Resource_Module_name ti_ipc_remoteproc_Resource_Module_name
#define Resource_Module_id ti_ipc_remoteproc_Resource_Module_id
#define Resource_Module_startup ti_ipc_remoteproc_Resource_Module_startup
#define Resource_Module_startupDone ti_ipc_remoteproc_Resource_Module_startupDone
#define Resource_Module_hasMask ti_ipc_remoteproc_Resource_Module_hasMask
#define Resource_Module_getMask ti_ipc_remoteproc_Resource_Module_getMask
#define Resource_Module_setMask ti_ipc_remoteproc_Resource_Module_setMask
#define Resource_Object_heap ti_ipc_remoteproc_Resource_Object_heap
#define Resource_Module_heap ti_ipc_remoteproc_Resource_Module_heap

#endif /* ti_ipc_remoteproc_Resource__localnames__done */
#endif
