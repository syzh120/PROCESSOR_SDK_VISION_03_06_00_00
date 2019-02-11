/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A75
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

#ifndef ti_opencl_DSPMonitor__include
#define ti_opencl_DSPMonitor__include

#ifndef __nested__
#define __nested__
#define ti_opencl_DSPMonitor__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_opencl_DSPMonitor___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/opencl/package/package.defs.h>

#include <xdc/runtime/Types.h>
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
typedef xdc_Bits32 CT__ti_opencl_DSPMonitor_Module__diagsEnabled;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__diagsEnabled ti_opencl_DSPMonitor_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_opencl_DSPMonitor_Module__diagsIncluded;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__diagsIncluded ti_opencl_DSPMonitor_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_opencl_DSPMonitor_Module__diagsMask;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__diagsMask ti_opencl_DSPMonitor_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_opencl_DSPMonitor_Module__gateObj;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__gateObj ti_opencl_DSPMonitor_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_opencl_DSPMonitor_Module__gatePrms;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__gatePrms ti_opencl_DSPMonitor_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_opencl_DSPMonitor_Module__id;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__id ti_opencl_DSPMonitor_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_opencl_DSPMonitor_Module__loggerDefined;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__loggerDefined ti_opencl_DSPMonitor_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_opencl_DSPMonitor_Module__loggerObj;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__loggerObj ti_opencl_DSPMonitor_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_opencl_DSPMonitor_Module__loggerFxn0;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__loggerFxn0 ti_opencl_DSPMonitor_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_opencl_DSPMonitor_Module__loggerFxn1;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__loggerFxn1 ti_opencl_DSPMonitor_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_opencl_DSPMonitor_Module__loggerFxn2;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__loggerFxn2 ti_opencl_DSPMonitor_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_opencl_DSPMonitor_Module__loggerFxn4;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__loggerFxn4 ti_opencl_DSPMonitor_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_opencl_DSPMonitor_Module__loggerFxn8;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__loggerFxn8 ti_opencl_DSPMonitor_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_opencl_DSPMonitor_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Module__startupDoneFxn ti_opencl_DSPMonitor_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_opencl_DSPMonitor_Object__count;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Object__count ti_opencl_DSPMonitor_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_opencl_DSPMonitor_Object__heap;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Object__heap ti_opencl_DSPMonitor_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_opencl_DSPMonitor_Object__sizeof;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Object__sizeof ti_opencl_DSPMonitor_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_opencl_DSPMonitor_Object__table;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_Object__table ti_opencl_DSPMonitor_Object__table__C;

/* OCL_monitor_priority */
#ifdef ti_opencl_DSPMonitor_OCL_monitor_priority__D
#define ti_opencl_DSPMonitor_OCL_monitor_priority (ti_opencl_DSPMonitor_OCL_monitor_priority__D)
#else
#define ti_opencl_DSPMonitor_OCL_monitor_priority (ti_opencl_DSPMonitor_OCL_monitor_priority__C)
typedef xdc_UInt32 CT__ti_opencl_DSPMonitor_OCL_monitor_priority;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_OCL_monitor_priority ti_opencl_DSPMonitor_OCL_monitor_priority__C;
#endif

/* OCL_ipc_customized */
#ifdef ti_opencl_DSPMonitor_OCL_ipc_customized__D
#define ti_opencl_DSPMonitor_OCL_ipc_customized (ti_opencl_DSPMonitor_OCL_ipc_customized__D)
#else
#define ti_opencl_DSPMonitor_OCL_ipc_customized (ti_opencl_DSPMonitor_OCL_ipc_customized__C)
typedef xdc_Bool CT__ti_opencl_DSPMonitor_OCL_ipc_customized;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_OCL_ipc_customized ti_opencl_DSPMonitor_OCL_ipc_customized__C;
#endif

/* OCL_link_extra_sym_def */
#ifdef ti_opencl_DSPMonitor_OCL_link_extra_sym_def__D
#define ti_opencl_DSPMonitor_OCL_link_extra_sym_def (ti_opencl_DSPMonitor_OCL_link_extra_sym_def__D)
#else
#define ti_opencl_DSPMonitor_OCL_link_extra_sym_def (ti_opencl_DSPMonitor_OCL_link_extra_sym_def__C)
typedef xdc_Bool CT__ti_opencl_DSPMonitor_OCL_link_extra_sym_def;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_OCL_link_extra_sym_def ti_opencl_DSPMonitor_OCL_link_extra_sym_def__C;
#endif

/* OCL_memory_customized */
#ifdef ti_opencl_DSPMonitor_OCL_memory_customized__D
#define ti_opencl_DSPMonitor_OCL_memory_customized (ti_opencl_DSPMonitor_OCL_memory_customized__D)
#else
#define ti_opencl_DSPMonitor_OCL_memory_customized (ti_opencl_DSPMonitor_OCL_memory_customized__C)
typedef xdc_Bool CT__ti_opencl_DSPMonitor_OCL_memory_customized;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_OCL_memory_customized ti_opencl_DSPMonitor_OCL_memory_customized__C;
#endif

/* OCL_SR0_base */
#ifdef ti_opencl_DSPMonitor_OCL_SR0_base__D
#define ti_opencl_DSPMonitor_OCL_SR0_base (ti_opencl_DSPMonitor_OCL_SR0_base__D)
#else
#define ti_opencl_DSPMonitor_OCL_SR0_base (ti_opencl_DSPMonitor_OCL_SR0_base__C)
typedef xdc_UInt32 CT__ti_opencl_DSPMonitor_OCL_SR0_base;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_OCL_SR0_base ti_opencl_DSPMonitor_OCL_SR0_base__C;
#endif

/* OCL_SR0_len */
#ifdef ti_opencl_DSPMonitor_OCL_SR0_len__D
#define ti_opencl_DSPMonitor_OCL_SR0_len (ti_opencl_DSPMonitor_OCL_SR0_len__D)
#else
#define ti_opencl_DSPMonitor_OCL_SR0_len (ti_opencl_DSPMonitor_OCL_SR0_len__C)
typedef xdc_UInt32 CT__ti_opencl_DSPMonitor_OCL_SR0_len;
__extern __FAR__ const CT__ti_opencl_DSPMonitor_OCL_SR0_len ti_opencl_DSPMonitor_OCL_SR0_len__C;
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_opencl_DSPMonitor_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_opencl_DSPMonitor_Module__startupDone__S, "ti_opencl_DSPMonitor_Module__startupDone__S")
__extern xdc_Bool ti_opencl_DSPMonitor_Module__startupDone__S( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_opencl_DSPMonitor_Module_startupDone() ti_opencl_DSPMonitor_Module__startupDone__S()

/* Object_heap */
#define ti_opencl_DSPMonitor_Object_heap() ti_opencl_DSPMonitor_Object__heap__C

/* Module_heap */
#define ti_opencl_DSPMonitor_Module_heap() ti_opencl_DSPMonitor_Object__heap__C

/* Module_id */
static inline CT__ti_opencl_DSPMonitor_Module__id ti_opencl_DSPMonitor_Module_id( void ) 
{
    return ti_opencl_DSPMonitor_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_opencl_DSPMonitor_Module_hasMask( void ) 
{
    return ti_opencl_DSPMonitor_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 ti_opencl_DSPMonitor_Module_getMask( void ) 
{
    return ti_opencl_DSPMonitor_Module__diagsMask__C != NULL ? *ti_opencl_DSPMonitor_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void ti_opencl_DSPMonitor_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_opencl_DSPMonitor_Module__diagsMask__C != NULL) *ti_opencl_DSPMonitor_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_opencl_DSPMonitor__top__
#undef __nested__
#endif

#endif /* ti_opencl_DSPMonitor__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_opencl_DSPMonitor__internalaccess))

#ifndef ti_opencl_DSPMonitor__include_state
#define ti_opencl_DSPMonitor__include_state


#endif /* ti_opencl_DSPMonitor__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_opencl_DSPMonitor__nolocalnames)

#ifndef ti_opencl_DSPMonitor__localnames__done
#define ti_opencl_DSPMonitor__localnames__done

/* module prefix */
#define DSPMonitor_OCL_monitor_priority ti_opencl_DSPMonitor_OCL_monitor_priority
#define DSPMonitor_OCL_ipc_customized ti_opencl_DSPMonitor_OCL_ipc_customized
#define DSPMonitor_OCL_link_extra_sym_def ti_opencl_DSPMonitor_OCL_link_extra_sym_def
#define DSPMonitor_OCL_memory_customized ti_opencl_DSPMonitor_OCL_memory_customized
#define DSPMonitor_OCL_SR0_base ti_opencl_DSPMonitor_OCL_SR0_base
#define DSPMonitor_OCL_SR0_len ti_opencl_DSPMonitor_OCL_SR0_len
#define DSPMonitor_Module_name ti_opencl_DSPMonitor_Module_name
#define DSPMonitor_Module_id ti_opencl_DSPMonitor_Module_id
#define DSPMonitor_Module_startup ti_opencl_DSPMonitor_Module_startup
#define DSPMonitor_Module_startupDone ti_opencl_DSPMonitor_Module_startupDone
#define DSPMonitor_Module_hasMask ti_opencl_DSPMonitor_Module_hasMask
#define DSPMonitor_Module_getMask ti_opencl_DSPMonitor_Module_getMask
#define DSPMonitor_Module_setMask ti_opencl_DSPMonitor_Module_setMask
#define DSPMonitor_Object_heap ti_opencl_DSPMonitor_Object_heap
#define DSPMonitor_Module_heap ti_opencl_DSPMonitor_Module_heap

#endif /* ti_opencl_DSPMonitor__localnames__done */
#endif
