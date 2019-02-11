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

#ifndef ti_sdo_utils_MultiProc__include
#define ti_sdo_utils_MultiProc__include

#ifndef __nested__
#define __nested__
#define ti_sdo_utils_MultiProc__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_utils_MultiProc___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sdo/utils/package/package.defs.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* INVALIDID */
#define ti_sdo_utils_MultiProc_INVALIDID (0xFFFF)

/* ProcAddrMode */
enum ti_sdo_utils_MultiProc_ProcAddrMode {
    ti_sdo_utils_MultiProc_ProcAddrMode_Global,
    ti_sdo_utils_MultiProc_ProcAddrMode_Cluster
};
typedef enum ti_sdo_utils_MultiProc_ProcAddrMode ti_sdo_utils_MultiProc_ProcAddrMode;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* Module_State */
typedef xdc_UInt16 __T1_ti_sdo_utils_MultiProc_Module_State__clusterProcList;
typedef xdc_UInt16 *__ARRAY1_ti_sdo_utils_MultiProc_Module_State__clusterProcList;
typedef __ARRAY1_ti_sdo_utils_MultiProc_Module_State__clusterProcList __TA_ti_sdo_utils_MultiProc_Module_State__clusterProcList;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_utils_MultiProc_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__diagsEnabled ti_sdo_utils_MultiProc_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_utils_MultiProc_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__diagsIncluded ti_sdo_utils_MultiProc_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_utils_MultiProc_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__diagsMask ti_sdo_utils_MultiProc_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_utils_MultiProc_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__gateObj ti_sdo_utils_MultiProc_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_utils_MultiProc_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__gatePrms ti_sdo_utils_MultiProc_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_utils_MultiProc_Module__id;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__id ti_sdo_utils_MultiProc_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_utils_MultiProc_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__loggerDefined ti_sdo_utils_MultiProc_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_utils_MultiProc_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__loggerObj ti_sdo_utils_MultiProc_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_utils_MultiProc_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__loggerFxn0 ti_sdo_utils_MultiProc_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_utils_MultiProc_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__loggerFxn1 ti_sdo_utils_MultiProc_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_utils_MultiProc_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__loggerFxn2 ti_sdo_utils_MultiProc_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_utils_MultiProc_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__loggerFxn4 ti_sdo_utils_MultiProc_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_utils_MultiProc_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__loggerFxn8 ti_sdo_utils_MultiProc_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_utils_MultiProc_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Module__startupDoneFxn ti_sdo_utils_MultiProc_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_utils_MultiProc_Object__count;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Object__count ti_sdo_utils_MultiProc_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_utils_MultiProc_Object__heap;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Object__heap ti_sdo_utils_MultiProc_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_utils_MultiProc_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Object__sizeof ti_sdo_utils_MultiProc_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_utils_MultiProc_Object__table;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_Object__table ti_sdo_utils_MultiProc_Object__table__C;

/* A_invalidMultiProcId */
#define ti_sdo_utils_MultiProc_A_invalidMultiProcId (ti_sdo_utils_MultiProc_A_invalidMultiProcId__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_utils_MultiProc_A_invalidMultiProcId;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_A_invalidMultiProcId ti_sdo_utils_MultiProc_A_invalidMultiProcId__C;

/* A_invalidProcName */
#define ti_sdo_utils_MultiProc_A_invalidProcName (ti_sdo_utils_MultiProc_A_invalidProcName__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_utils_MultiProc_A_invalidProcName;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_A_invalidProcName ti_sdo_utils_MultiProc_A_invalidProcName__C;

/* nameList */
#define ti_sdo_utils_MultiProc_nameList (ti_sdo_utils_MultiProc_nameList__C)
typedef xdc_String __T1_ti_sdo_utils_MultiProc_nameList;
typedef xdc_String *__ARRAY1_ti_sdo_utils_MultiProc_nameList;
typedef __ARRAY1_ti_sdo_utils_MultiProc_nameList __TA_ti_sdo_utils_MultiProc_nameList;
typedef __TA_ti_sdo_utils_MultiProc_nameList CT__ti_sdo_utils_MultiProc_nameList;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_nameList ti_sdo_utils_MultiProc_nameList__C;

/* numProcsInCluster */
#ifdef ti_sdo_utils_MultiProc_numProcsInCluster__D
#define ti_sdo_utils_MultiProc_numProcsInCluster (ti_sdo_utils_MultiProc_numProcsInCluster__D)
#else
#define ti_sdo_utils_MultiProc_numProcsInCluster (ti_sdo_utils_MultiProc_numProcsInCluster__C)
typedef xdc_UInt16 CT__ti_sdo_utils_MultiProc_numProcsInCluster;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_numProcsInCluster ti_sdo_utils_MultiProc_numProcsInCluster__C;
#endif

/* numProcessors */
#ifdef ti_sdo_utils_MultiProc_numProcessors__D
#define ti_sdo_utils_MultiProc_numProcessors (ti_sdo_utils_MultiProc_numProcessors__D)
#else
#define ti_sdo_utils_MultiProc_numProcessors (ti_sdo_utils_MultiProc_numProcessors__C)
typedef xdc_UInt16 CT__ti_sdo_utils_MultiProc_numProcessors;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_numProcessors ti_sdo_utils_MultiProc_numProcessors__C;
#endif

/* procAddrMode */
#define ti_sdo_utils_MultiProc_procAddrMode (ti_sdo_utils_MultiProc_procAddrMode__C)
typedef ti_sdo_utils_MultiProc_ProcAddrMode CT__ti_sdo_utils_MultiProc_procAddrMode;
__extern __FAR__ const CT__ti_sdo_utils_MultiProc_procAddrMode ti_sdo_utils_MultiProc_procAddrMode__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_utils_MultiProc_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_utils_MultiProc_Module__startupDone__S, "ti_sdo_utils_MultiProc_Module__startupDone__S")
__extern xdc_Bool ti_sdo_utils_MultiProc_Module__startupDone__S( void );

/* getClusterId__E */
#define ti_sdo_utils_MultiProc_getClusterId ti_sdo_utils_MultiProc_getClusterId__E
xdc__CODESECT(ti_sdo_utils_MultiProc_getClusterId__E, "ti_sdo_utils_MultiProc_getClusterId")
__extern xdc_UInt16 ti_sdo_utils_MultiProc_getClusterId__E( xdc_UInt16 procId );
xdc__CODESECT(ti_sdo_utils_MultiProc_getClusterId__F, "ti_sdo_utils_MultiProc_getClusterId")
__extern xdc_UInt16 ti_sdo_utils_MultiProc_getClusterId__F( xdc_UInt16 procId );

/* dummy__E */
#define ti_sdo_utils_MultiProc_dummy ti_sdo_utils_MultiProc_dummy__E
xdc__CODESECT(ti_sdo_utils_MultiProc_dummy__E, "ti_sdo_utils_MultiProc_dummy")
__extern xdc_Void ti_sdo_utils_MultiProc_dummy__E( void );
xdc__CODESECT(ti_sdo_utils_MultiProc_dummy__F, "ti_sdo_utils_MultiProc_dummy")
__extern xdc_Void ti_sdo_utils_MultiProc_dummy__F( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_utils_MultiProc_Module_startupDone() ti_sdo_utils_MultiProc_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_utils_MultiProc_Object_heap() ti_sdo_utils_MultiProc_Object__heap__C

/* Module_heap */
#define ti_sdo_utils_MultiProc_Module_heap() ti_sdo_utils_MultiProc_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_utils_MultiProc_Module__id ti_sdo_utils_MultiProc_Module_id( void ) 
{
    return ti_sdo_utils_MultiProc_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_utils_MultiProc_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_utils_MultiProc_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_utils_MultiProc_Module_getMask( void ) 
{
    return ti_sdo_utils_MultiProc_Module__diagsMask__C != NULL ? *ti_sdo_utils_MultiProc_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_utils_MultiProc_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_utils_MultiProc_Module__diagsMask__C != NULL) {
        *ti_sdo_utils_MultiProc_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_utils_MultiProc__top__
#undef __nested__
#endif

#endif /* ti_sdo_utils_MultiProc__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_utils_MultiProc__internalaccess))

#ifndef ti_sdo_utils_MultiProc__include_state
#define ti_sdo_utils_MultiProc__include_state

/* Module_State */
struct ti_sdo_utils_MultiProc_Module_State {
    xdc_UInt16 id;
    xdc_UInt16 baseIdOfCluster;
    __TA_ti_sdo_utils_MultiProc_Module_State__clusterProcList clusterProcList;
};

/* Module__state__V */
extern struct ti_sdo_utils_MultiProc_Module_State__ ti_sdo_utils_MultiProc_Module__state__V;

#endif /* ti_sdo_utils_MultiProc__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_utils_MultiProc__nolocalnames)

#ifndef ti_sdo_utils_MultiProc__localnames__done
#define ti_sdo_utils_MultiProc__localnames__done

/* module prefix */
#define MultiProc_INVALIDID ti_sdo_utils_MultiProc_INVALIDID
#define MultiProc_ProcAddrMode ti_sdo_utils_MultiProc_ProcAddrMode
#define MultiProc_Module_State ti_sdo_utils_MultiProc_Module_State
#define MultiProc_ProcAddrMode_Global ti_sdo_utils_MultiProc_ProcAddrMode_Global
#define MultiProc_ProcAddrMode_Cluster ti_sdo_utils_MultiProc_ProcAddrMode_Cluster
#define MultiProc_A_invalidMultiProcId ti_sdo_utils_MultiProc_A_invalidMultiProcId
#define MultiProc_A_invalidProcName ti_sdo_utils_MultiProc_A_invalidProcName
#define MultiProc_nameList ti_sdo_utils_MultiProc_nameList
#define MultiProc_numProcsInCluster ti_sdo_utils_MultiProc_numProcsInCluster
#define MultiProc_numProcessors ti_sdo_utils_MultiProc_numProcessors
#define MultiProc_procAddrMode ti_sdo_utils_MultiProc_procAddrMode
#define MultiProc_getClusterId ti_sdo_utils_MultiProc_getClusterId
#define MultiProc_dummy ti_sdo_utils_MultiProc_dummy
#define MultiProc_Module_name ti_sdo_utils_MultiProc_Module_name
#define MultiProc_Module_id ti_sdo_utils_MultiProc_Module_id
#define MultiProc_Module_startup ti_sdo_utils_MultiProc_Module_startup
#define MultiProc_Module_startupDone ti_sdo_utils_MultiProc_Module_startupDone
#define MultiProc_Module_hasMask ti_sdo_utils_MultiProc_Module_hasMask
#define MultiProc_Module_getMask ti_sdo_utils_MultiProc_Module_getMask
#define MultiProc_Module_setMask ti_sdo_utils_MultiProc_Module_setMask
#define MultiProc_Object_heap ti_sdo_utils_MultiProc_Object_heap
#define MultiProc_Module_heap ti_sdo_utils_MultiProc_Module_heap

#endif /* ti_sdo_utils_MultiProc__localnames__done */
#endif
