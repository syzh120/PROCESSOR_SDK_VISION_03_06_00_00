/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A71
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

#ifndef ti_sysbios_rts_iar_MultithreadSupport__include
#define ti_sysbios_rts_iar_MultithreadSupport__include

#ifndef __nested__
#define __nested__
#define ti_sysbios_rts_iar_MultithreadSupport__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sysbios_rts_iar_MultithreadSupport___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sysbios/rts/iar/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <ti/sysbios/knl/Task.h>
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
typedef xdc_Bits32 CT__ti_sysbios_rts_iar_MultithreadSupport_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__diagsEnabled ti_sysbios_rts_iar_MultithreadSupport_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_rts_iar_MultithreadSupport_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__diagsIncluded ti_sysbios_rts_iar_MultithreadSupport_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sysbios_rts_iar_MultithreadSupport_Module__diagsMask;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__diagsMask ti_sysbios_rts_iar_MultithreadSupport_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_rts_iar_MultithreadSupport_Module__gateObj;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__gateObj ti_sysbios_rts_iar_MultithreadSupport_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_rts_iar_MultithreadSupport_Module__gatePrms;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__gatePrms ti_sysbios_rts_iar_MultithreadSupport_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_rts_iar_MultithreadSupport_Module__id;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__id ti_sysbios_rts_iar_MultithreadSupport_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerDefined;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerDefined ti_sysbios_rts_iar_MultithreadSupport_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerObj;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerObj ti_sysbios_rts_iar_MultithreadSupport_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn0 ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn1 ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn2 ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn4 ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn8 ti_sysbios_rts_iar_MultithreadSupport_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_rts_iar_MultithreadSupport_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Module__startupDoneFxn ti_sysbios_rts_iar_MultithreadSupport_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_rts_iar_MultithreadSupport_Object__count;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Object__count ti_sysbios_rts_iar_MultithreadSupport_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_rts_iar_MultithreadSupport_Object__heap;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Object__heap ti_sysbios_rts_iar_MultithreadSupport_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_rts_iar_MultithreadSupport_Object__sizeof;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Object__sizeof ti_sysbios_rts_iar_MultithreadSupport_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_rts_iar_MultithreadSupport_Object__table;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_Object__table ti_sysbios_rts_iar_MultithreadSupport_Object__table__C;

/* enableMultithreadSupport */
#ifdef ti_sysbios_rts_iar_MultithreadSupport_enableMultithreadSupport__D
#define ti_sysbios_rts_iar_MultithreadSupport_enableMultithreadSupport (ti_sysbios_rts_iar_MultithreadSupport_enableMultithreadSupport__D)
#else
#define ti_sysbios_rts_iar_MultithreadSupport_enableMultithreadSupport (ti_sysbios_rts_iar_MultithreadSupport_enableMultithreadSupport__C)
typedef xdc_Bool CT__ti_sysbios_rts_iar_MultithreadSupport_enableMultithreadSupport;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_enableMultithreadSupport ti_sysbios_rts_iar_MultithreadSupport_enableMultithreadSupport__C;
#endif

/* A_badThreadType */
#define ti_sysbios_rts_iar_MultithreadSupport_A_badThreadType (ti_sysbios_rts_iar_MultithreadSupport_A_badThreadType__C)
typedef xdc_runtime_Assert_Id CT__ti_sysbios_rts_iar_MultithreadSupport_A_badThreadType;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_A_badThreadType ti_sysbios_rts_iar_MultithreadSupport_A_badThreadType__C;

/* A_badLockRelease */
#define ti_sysbios_rts_iar_MultithreadSupport_A_badLockRelease (ti_sysbios_rts_iar_MultithreadSupport_A_badLockRelease__C)
typedef xdc_runtime_Assert_Id CT__ti_sysbios_rts_iar_MultithreadSupport_A_badLockRelease;
__extern __FAR__ const CT__ti_sysbios_rts_iar_MultithreadSupport_A_badLockRelease ti_sysbios_rts_iar_MultithreadSupport_A_badLockRelease__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sysbios_rts_iar_MultithreadSupport_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_sysbios_rts_iar_MultithreadSupport_Module__startupDone__S, "ti_sysbios_rts_iar_MultithreadSupport_Module__startupDone__S")
__extern xdc_Bool ti_sysbios_rts_iar_MultithreadSupport_Module__startupDone__S( void );

/* perThreadAccess__I */
#define ti_sysbios_rts_iar_MultithreadSupport_perThreadAccess ti_sysbios_rts_iar_MultithreadSupport_perThreadAccess__I
xdc__CODESECT(ti_sysbios_rts_iar_MultithreadSupport_perThreadAccess__I, "ti_sysbios_rts_iar_MultithreadSupport_perThreadAccess")
__extern xdc_Void *ti_sysbios_rts_iar_MultithreadSupport_perThreadAccess__I( xdc_Void *symbp );

/* initLock__I */
#define ti_sysbios_rts_iar_MultithreadSupport_initLock ti_sysbios_rts_iar_MultithreadSupport_initLock__I
xdc__CODESECT(ti_sysbios_rts_iar_MultithreadSupport_initLock__I, "ti_sysbios_rts_iar_MultithreadSupport_initLock")
__extern xdc_Void ti_sysbios_rts_iar_MultithreadSupport_initLock__I( xdc_Void **ptr );

/* destroyLock__I */
#define ti_sysbios_rts_iar_MultithreadSupport_destroyLock ti_sysbios_rts_iar_MultithreadSupport_destroyLock__I
xdc__CODESECT(ti_sysbios_rts_iar_MultithreadSupport_destroyLock__I, "ti_sysbios_rts_iar_MultithreadSupport_destroyLock")
__extern xdc_Void ti_sysbios_rts_iar_MultithreadSupport_destroyLock__I( xdc_Void **ptr );

/* acquireLock__I */
#define ti_sysbios_rts_iar_MultithreadSupport_acquireLock ti_sysbios_rts_iar_MultithreadSupport_acquireLock__I
xdc__CODESECT(ti_sysbios_rts_iar_MultithreadSupport_acquireLock__I, "ti_sysbios_rts_iar_MultithreadSupport_acquireLock")
__extern xdc_Void ti_sysbios_rts_iar_MultithreadSupport_acquireLock__I( xdc_Void **ptr );

/* releaseLock__I */
#define ti_sysbios_rts_iar_MultithreadSupport_releaseLock ti_sysbios_rts_iar_MultithreadSupport_releaseLock__I
xdc__CODESECT(ti_sysbios_rts_iar_MultithreadSupport_releaseLock__I, "ti_sysbios_rts_iar_MultithreadSupport_releaseLock")
__extern xdc_Void ti_sysbios_rts_iar_MultithreadSupport_releaseLock__I( xdc_Void **ptr );

/* taskCreateHook__I */
#define ti_sysbios_rts_iar_MultithreadSupport_taskCreateHook ti_sysbios_rts_iar_MultithreadSupport_taskCreateHook__I
xdc__CODESECT(ti_sysbios_rts_iar_MultithreadSupport_taskCreateHook__I, "ti_sysbios_rts_iar_MultithreadSupport_taskCreateHook")
__extern xdc_Void ti_sysbios_rts_iar_MultithreadSupport_taskCreateHook__I( ti_sysbios_knl_Task_Handle task, xdc_runtime_Error_Block *eb );

/* taskDeleteHook__I */
#define ti_sysbios_rts_iar_MultithreadSupport_taskDeleteHook ti_sysbios_rts_iar_MultithreadSupport_taskDeleteHook__I
xdc__CODESECT(ti_sysbios_rts_iar_MultithreadSupport_taskDeleteHook__I, "ti_sysbios_rts_iar_MultithreadSupport_taskDeleteHook")
__extern xdc_Void ti_sysbios_rts_iar_MultithreadSupport_taskDeleteHook__I( ti_sysbios_knl_Task_Handle task );

/* taskRegHook__I */
#define ti_sysbios_rts_iar_MultithreadSupport_taskRegHook ti_sysbios_rts_iar_MultithreadSupport_taskRegHook__I
xdc__CODESECT(ti_sysbios_rts_iar_MultithreadSupport_taskRegHook__I, "ti_sysbios_rts_iar_MultithreadSupport_taskRegHook")
__extern xdc_Void ti_sysbios_rts_iar_MultithreadSupport_taskRegHook__I( xdc_Int id );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sysbios_rts_iar_MultithreadSupport_Module_startupDone() ti_sysbios_rts_iar_MultithreadSupport_Module__startupDone__S()

/* Object_heap */
#define ti_sysbios_rts_iar_MultithreadSupport_Object_heap() ti_sysbios_rts_iar_MultithreadSupport_Object__heap__C

/* Module_heap */
#define ti_sysbios_rts_iar_MultithreadSupport_Module_heap() ti_sysbios_rts_iar_MultithreadSupport_Object__heap__C

/* Module_id */
static inline CT__ti_sysbios_rts_iar_MultithreadSupport_Module__id ti_sysbios_rts_iar_MultithreadSupport_Module_id( void ) 
{
    return ti_sysbios_rts_iar_MultithreadSupport_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_rts_iar_MultithreadSupport_Module_hasMask( void ) 
{
    return ti_sysbios_rts_iar_MultithreadSupport_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_rts_iar_MultithreadSupport_Module_getMask( void ) 
{
    return ti_sysbios_rts_iar_MultithreadSupport_Module__diagsMask__C != NULL ? *ti_sysbios_rts_iar_MultithreadSupport_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void ti_sysbios_rts_iar_MultithreadSupport_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_rts_iar_MultithreadSupport_Module__diagsMask__C != NULL) *ti_sysbios_rts_iar_MultithreadSupport_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sysbios_rts_iar_MultithreadSupport__top__
#undef __nested__
#endif

#endif /* ti_sysbios_rts_iar_MultithreadSupport__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sysbios_rts_iar_MultithreadSupport__internalaccess))

#ifndef ti_sysbios_rts_iar_MultithreadSupport__include_state
#define ti_sysbios_rts_iar_MultithreadSupport__include_state

/* Module_State */
struct ti_sysbios_rts_iar_MultithreadSupport_Module_State {
    xdc_Int taskHId;
};

/* Module__state__V */
extern struct ti_sysbios_rts_iar_MultithreadSupport_Module_State__ ti_sysbios_rts_iar_MultithreadSupport_Module__state__V;

#endif /* ti_sysbios_rts_iar_MultithreadSupport__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sysbios_rts_iar_MultithreadSupport__nolocalnames)

#ifndef ti_sysbios_rts_iar_MultithreadSupport__localnames__done
#define ti_sysbios_rts_iar_MultithreadSupport__localnames__done

/* module prefix */
#define MultithreadSupport_Module_State ti_sysbios_rts_iar_MultithreadSupport_Module_State
#define MultithreadSupport_enableMultithreadSupport ti_sysbios_rts_iar_MultithreadSupport_enableMultithreadSupport
#define MultithreadSupport_A_badThreadType ti_sysbios_rts_iar_MultithreadSupport_A_badThreadType
#define MultithreadSupport_A_badLockRelease ti_sysbios_rts_iar_MultithreadSupport_A_badLockRelease
#define MultithreadSupport_Module_name ti_sysbios_rts_iar_MultithreadSupport_Module_name
#define MultithreadSupport_Module_id ti_sysbios_rts_iar_MultithreadSupport_Module_id
#define MultithreadSupport_Module_startup ti_sysbios_rts_iar_MultithreadSupport_Module_startup
#define MultithreadSupport_Module_startupDone ti_sysbios_rts_iar_MultithreadSupport_Module_startupDone
#define MultithreadSupport_Module_hasMask ti_sysbios_rts_iar_MultithreadSupport_Module_hasMask
#define MultithreadSupport_Module_getMask ti_sysbios_rts_iar_MultithreadSupport_Module_getMask
#define MultithreadSupport_Module_setMask ti_sysbios_rts_iar_MultithreadSupport_Module_setMask
#define MultithreadSupport_Object_heap ti_sysbios_rts_iar_MultithreadSupport_Object_heap
#define MultithreadSupport_Module_heap ti_sysbios_rts_iar_MultithreadSupport_Module_heap

#endif /* ti_sysbios_rts_iar_MultithreadSupport__localnames__done */
#endif
