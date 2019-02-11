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

#ifndef ti_srvmgr_omx_OmxSrvMgr__include
#define ti_srvmgr_omx_OmxSrvMgr__include

#ifndef __nested__
#define __nested__
#define ti_srvmgr_omx_OmxSrvMgr__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_srvmgr_omx_OmxSrvMgr___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/srvmgr/omx/package/package.defs.h>

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
typedef xdc_Bits32 CT__ti_srvmgr_omx_OmxSrvMgr_Module__diagsEnabled;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__diagsEnabled ti_srvmgr_omx_OmxSrvMgr_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_srvmgr_omx_OmxSrvMgr_Module__diagsIncluded;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__diagsIncluded ti_srvmgr_omx_OmxSrvMgr_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_srvmgr_omx_OmxSrvMgr_Module__diagsMask;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__diagsMask ti_srvmgr_omx_OmxSrvMgr_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_srvmgr_omx_OmxSrvMgr_Module__gateObj;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__gateObj ti_srvmgr_omx_OmxSrvMgr_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_srvmgr_omx_OmxSrvMgr_Module__gatePrms;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__gatePrms ti_srvmgr_omx_OmxSrvMgr_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_srvmgr_omx_OmxSrvMgr_Module__id;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__id ti_srvmgr_omx_OmxSrvMgr_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerDefined;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerDefined ti_srvmgr_omx_OmxSrvMgr_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerObj;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerObj ti_srvmgr_omx_OmxSrvMgr_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn0;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn0 ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn1;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn1 ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn2;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn2 ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn4;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn4 ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn8;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn8 ti_srvmgr_omx_OmxSrvMgr_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_srvmgr_omx_OmxSrvMgr_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Module__startupDoneFxn ti_srvmgr_omx_OmxSrvMgr_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_srvmgr_omx_OmxSrvMgr_Object__count;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Object__count ti_srvmgr_omx_OmxSrvMgr_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_srvmgr_omx_OmxSrvMgr_Object__heap;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Object__heap ti_srvmgr_omx_OmxSrvMgr_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_srvmgr_omx_OmxSrvMgr_Object__sizeof;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Object__sizeof ti_srvmgr_omx_OmxSrvMgr_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_srvmgr_omx_OmxSrvMgr_Object__table;
__extern __FAR__ const CT__ti_srvmgr_omx_OmxSrvMgr_Object__table ti_srvmgr_omx_OmxSrvMgr_Object__table__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_srvmgr_omx_OmxSrvMgr_Module_startup ti_srvmgr_omx_OmxSrvMgr_Module_startup__E
xdc__CODESECT(ti_srvmgr_omx_OmxSrvMgr_Module_startup__E, "ti_srvmgr_omx_OmxSrvMgr_Module_startup")
__extern xdc_Int ti_srvmgr_omx_OmxSrvMgr_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_srvmgr_omx_OmxSrvMgr_Module_startup__F, "ti_srvmgr_omx_OmxSrvMgr_Module_startup")
__extern xdc_Int ti_srvmgr_omx_OmxSrvMgr_Module_startup__F( xdc_Int state );

/* Module__startupDone__S */
xdc__CODESECT(ti_srvmgr_omx_OmxSrvMgr_Module__startupDone__S, "ti_srvmgr_omx_OmxSrvMgr_Module__startupDone__S")
__extern xdc_Bool ti_srvmgr_omx_OmxSrvMgr_Module__startupDone__S( void );

/* taskFxn__I */
#define ti_srvmgr_omx_OmxSrvMgr_taskFxn ti_srvmgr_omx_OmxSrvMgr_taskFxn__I
xdc__CODESECT(ti_srvmgr_omx_OmxSrvMgr_taskFxn__I, "ti_srvmgr_omx_OmxSrvMgr_taskFxn")
__extern xdc_Void ti_srvmgr_omx_OmxSrvMgr_taskFxn__I( xdc_UArg arg0, xdc_UArg arg1 );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_srvmgr_omx_OmxSrvMgr_Module_startupDone() ti_srvmgr_omx_OmxSrvMgr_Module__startupDone__S()

/* Object_heap */
#define ti_srvmgr_omx_OmxSrvMgr_Object_heap() ti_srvmgr_omx_OmxSrvMgr_Object__heap__C

/* Module_heap */
#define ti_srvmgr_omx_OmxSrvMgr_Module_heap() ti_srvmgr_omx_OmxSrvMgr_Object__heap__C

/* Module_id */
static inline CT__ti_srvmgr_omx_OmxSrvMgr_Module__id ti_srvmgr_omx_OmxSrvMgr_Module_id( void ) 
{
    return ti_srvmgr_omx_OmxSrvMgr_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_srvmgr_omx_OmxSrvMgr_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_srvmgr_omx_OmxSrvMgr_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_srvmgr_omx_OmxSrvMgr_Module_getMask( void ) 
{
    return ti_srvmgr_omx_OmxSrvMgr_Module__diagsMask__C != NULL ? *ti_srvmgr_omx_OmxSrvMgr_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_srvmgr_omx_OmxSrvMgr_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_srvmgr_omx_OmxSrvMgr_Module__diagsMask__C != NULL) {
        *ti_srvmgr_omx_OmxSrvMgr_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_srvmgr_omx_OmxSrvMgr__top__
#undef __nested__
#endif

#endif /* ti_srvmgr_omx_OmxSrvMgr__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_srvmgr_omx_OmxSrvMgr__internalaccess))

#ifndef ti_srvmgr_omx_OmxSrvMgr__include_state
#define ti_srvmgr_omx_OmxSrvMgr__include_state


#endif /* ti_srvmgr_omx_OmxSrvMgr__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_srvmgr_omx_OmxSrvMgr__nolocalnames)

#ifndef ti_srvmgr_omx_OmxSrvMgr__localnames__done
#define ti_srvmgr_omx_OmxSrvMgr__localnames__done

/* module prefix */
#define OmxSrvMgr_Module_name ti_srvmgr_omx_OmxSrvMgr_Module_name
#define OmxSrvMgr_Module_id ti_srvmgr_omx_OmxSrvMgr_Module_id
#define OmxSrvMgr_Module_startup ti_srvmgr_omx_OmxSrvMgr_Module_startup
#define OmxSrvMgr_Module_startupDone ti_srvmgr_omx_OmxSrvMgr_Module_startupDone
#define OmxSrvMgr_Module_hasMask ti_srvmgr_omx_OmxSrvMgr_Module_hasMask
#define OmxSrvMgr_Module_getMask ti_srvmgr_omx_OmxSrvMgr_Module_getMask
#define OmxSrvMgr_Module_setMask ti_srvmgr_omx_OmxSrvMgr_Module_setMask
#define OmxSrvMgr_Object_heap ti_srvmgr_omx_OmxSrvMgr_Object_heap
#define OmxSrvMgr_Module_heap ti_srvmgr_omx_OmxSrvMgr_Module_heap

#endif /* ti_srvmgr_omx_OmxSrvMgr__localnames__done */
#endif
