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

#ifndef ti_sdo_ipc_family_tci663x_MultiProcSetup__include
#define ti_sdo_ipc_family_tci663x_MultiProcSetup__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_family_tci663x_MultiProcSetup__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_family_tci663x_MultiProcSetup___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sdo/ipc/family/tci663x/package/package.defs.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsEnabled ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsIncluded ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsMask ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__gateObj ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__gatePrms ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__id ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerDefined ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerObj ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn0 ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn1 ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn2 ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn4 ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn8 ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__startupDoneFxn ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__count ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__heap ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__sizeof ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__table ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__table__C;

/* configureProcId */
#ifdef ti_sdo_ipc_family_tci663x_MultiProcSetup_configureProcId__D
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_configureProcId (ti_sdo_ipc_family_tci663x_MultiProcSetup_configureProcId__D)
#else
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_configureProcId (ti_sdo_ipc_family_tci663x_MultiProcSetup_configureProcId__C)
typedef xdc_Bool CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_configureProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_configureProcId ti_sdo_ipc_family_tci663x_MultiProcSetup_configureProcId__C;
#endif

/* A_invalidProcessor */
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_A_invalidProcessor (ti_sdo_ipc_family_tci663x_MultiProcSetup_A_invalidProcessor__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_A_invalidProcessor;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_A_invalidProcessor ti_sdo_ipc_family_tci663x_MultiProcSetup_A_invalidProcessor__C;

/* procMap */
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_procMap (ti_sdo_ipc_family_tci663x_MultiProcSetup_procMap__C)
typedef xdc_UInt16 __T1_ti_sdo_ipc_family_tci663x_MultiProcSetup_procMap;
typedef xdc_UInt16 *__ARRAY1_ti_sdo_ipc_family_tci663x_MultiProcSetup_procMap;
typedef __ARRAY1_ti_sdo_ipc_family_tci663x_MultiProcSetup_procMap __TA_ti_sdo_ipc_family_tci663x_MultiProcSetup_procMap;
typedef __TA_ti_sdo_ipc_family_tci663x_MultiProcSetup_procMap CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_procMap;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_procMap ti_sdo_ipc_family_tci663x_MultiProcSetup_procMap__C;

/* segmentSize */
#ifdef ti_sdo_ipc_family_tci663x_MultiProcSetup_segmentSize__D
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_segmentSize (ti_sdo_ipc_family_tci663x_MultiProcSetup_segmentSize__D)
#else
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_segmentSize (ti_sdo_ipc_family_tci663x_MultiProcSetup_segmentSize__C)
typedef xdc_UInt16 CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_segmentSize;
__extern __FAR__ const CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_segmentSize ti_sdo_ipc_family_tci663x_MultiProcSetup_segmentSize__C;
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__startupDone__S, "ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__startupDone__S( void );

/* getProcId__I */
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_getProcId ti_sdo_ipc_family_tci663x_MultiProcSetup_getProcId__I
xdc__CODESECT(ti_sdo_ipc_family_tci663x_MultiProcSetup_getProcId__I, "ti_sdo_ipc_family_tci663x_MultiProcSetup_getProcId")
__extern xdc_UInt16 ti_sdo_ipc_family_tci663x_MultiProcSetup_getProcId__I( xdc_UInt coreId );

/* init__I */
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_init ti_sdo_ipc_family_tci663x_MultiProcSetup_init__I
xdc__CODESECT(ti_sdo_ipc_family_tci663x_MultiProcSetup_init__I, "ti_sdo_ipc_family_tci663x_MultiProcSetup_init")
__extern xdc_Void ti_sdo_ipc_family_tci663x_MultiProcSetup_init__I( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_startupDone() ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_Object_heap() ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_heap() ti_sdo_ipc_family_tci663x_MultiProcSetup_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__id ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_id( void ) 
{
    return ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_getMask( void ) 
{
    return ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsMask__C != NULL ? *ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_family_tci663x_MultiProcSetup_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_family_tci663x_MultiProcSetup__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_family_tci663x_MultiProcSetup__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_family_tci663x_MultiProcSetup__internalaccess))

#ifndef ti_sdo_ipc_family_tci663x_MultiProcSetup__include_state
#define ti_sdo_ipc_family_tci663x_MultiProcSetup__include_state


#endif /* ti_sdo_ipc_family_tci663x_MultiProcSetup__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_family_tci663x_MultiProcSetup__nolocalnames)

#ifndef ti_sdo_ipc_family_tci663x_MultiProcSetup__localnames__done
#define ti_sdo_ipc_family_tci663x_MultiProcSetup__localnames__done

/* module prefix */
#define MultiProcSetup_configureProcId ti_sdo_ipc_family_tci663x_MultiProcSetup_configureProcId
#define MultiProcSetup_A_invalidProcessor ti_sdo_ipc_family_tci663x_MultiProcSetup_A_invalidProcessor
#define MultiProcSetup_procMap ti_sdo_ipc_family_tci663x_MultiProcSetup_procMap
#define MultiProcSetup_segmentSize ti_sdo_ipc_family_tci663x_MultiProcSetup_segmentSize
#define MultiProcSetup_Module_name ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_name
#define MultiProcSetup_Module_id ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_id
#define MultiProcSetup_Module_startup ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_startup
#define MultiProcSetup_Module_startupDone ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_startupDone
#define MultiProcSetup_Module_hasMask ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_hasMask
#define MultiProcSetup_Module_getMask ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_getMask
#define MultiProcSetup_Module_setMask ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_setMask
#define MultiProcSetup_Object_heap ti_sdo_ipc_family_tci663x_MultiProcSetup_Object_heap
#define MultiProcSetup_Module_heap ti_sdo_ipc_family_tci663x_MultiProcSetup_Module_heap

#endif /* ti_sdo_ipc_family_tci663x_MultiProcSetup__localnames__done */
#endif
