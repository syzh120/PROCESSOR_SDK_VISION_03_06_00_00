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

#ifndef ti_deh_StackDbg__include
#define ti_deh_StackDbg__include

#ifndef __nested__
#define __nested__
#define ti_deh_StackDbg__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_deh_StackDbg___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/deh/package/package.defs.h>

#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* StackEntry */
struct ti_deh_StackDbg_StackEntry {
    xdc_UInt instr;
    xdc_UInt op;
    xdc_UInt target;
    xdc_UInt sp;
    xdc_UInt ret;
    xdc_UInt bogus;
};

/* VisitFuncPtr */
typedef xdc_Bool (*ti_deh_StackDbg_VisitFuncPtr)(ti_deh_StackDbg_StackEntry*, xdc_Void*);


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_deh_StackDbg_Module__diagsEnabled;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__diagsEnabled ti_deh_StackDbg_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_deh_StackDbg_Module__diagsIncluded;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__diagsIncluded ti_deh_StackDbg_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_deh_StackDbg_Module__diagsMask;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__diagsMask ti_deh_StackDbg_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_deh_StackDbg_Module__gateObj;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__gateObj ti_deh_StackDbg_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_deh_StackDbg_Module__gatePrms;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__gatePrms ti_deh_StackDbg_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_deh_StackDbg_Module__id;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__id ti_deh_StackDbg_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_deh_StackDbg_Module__loggerDefined;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__loggerDefined ti_deh_StackDbg_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_deh_StackDbg_Module__loggerObj;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__loggerObj ti_deh_StackDbg_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_deh_StackDbg_Module__loggerFxn0;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__loggerFxn0 ti_deh_StackDbg_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_deh_StackDbg_Module__loggerFxn1;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__loggerFxn1 ti_deh_StackDbg_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_deh_StackDbg_Module__loggerFxn2;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__loggerFxn2 ti_deh_StackDbg_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_deh_StackDbg_Module__loggerFxn4;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__loggerFxn4 ti_deh_StackDbg_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_deh_StackDbg_Module__loggerFxn8;
__extern __FAR__ const CT__ti_deh_StackDbg_Module__loggerFxn8 ti_deh_StackDbg_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_deh_StackDbg_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_deh_StackDbg_Module__startupDoneFxn ti_deh_StackDbg_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_deh_StackDbg_Object__count;
__extern __FAR__ const CT__ti_deh_StackDbg_Object__count ti_deh_StackDbg_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_deh_StackDbg_Object__heap;
__extern __FAR__ const CT__ti_deh_StackDbg_Object__heap ti_deh_StackDbg_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_deh_StackDbg_Object__sizeof;
__extern __FAR__ const CT__ti_deh_StackDbg_Object__sizeof ti_deh_StackDbg_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_deh_StackDbg_Object__table;
__extern __FAR__ const CT__ti_deh_StackDbg_Object__table ti_deh_StackDbg_Object__table__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_deh_StackDbg_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_deh_StackDbg_Module__startupDone__S, "ti_deh_StackDbg_Module__startupDone__S")
__extern xdc_Bool ti_deh_StackDbg_Module__startupDone__S( void );

/* walkStack__E */
#define ti_deh_StackDbg_walkStack ti_deh_StackDbg_walkStack__E
xdc__CODESECT(ti_deh_StackDbg_walkStack__E, "ti_deh_StackDbg_walkStack")
__extern xdc_Void ti_deh_StackDbg_walkStack__E( xdc_UInt base, xdc_UInt size, xdc_UInt start, ti_deh_StackDbg_VisitFuncPtr visit, xdc_Ptr user );
xdc__CODESECT(ti_deh_StackDbg_walkStack__F, "ti_deh_StackDbg_walkStack")
__extern xdc_Void ti_deh_StackDbg_walkStack__F( xdc_UInt base, xdc_UInt size, xdc_UInt start, ti_deh_StackDbg_VisitFuncPtr visit, xdc_Ptr user );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_deh_StackDbg_Module_startupDone() ti_deh_StackDbg_Module__startupDone__S()

/* Object_heap */
#define ti_deh_StackDbg_Object_heap() ti_deh_StackDbg_Object__heap__C

/* Module_heap */
#define ti_deh_StackDbg_Module_heap() ti_deh_StackDbg_Object__heap__C

/* Module_id */
static inline CT__ti_deh_StackDbg_Module__id ti_deh_StackDbg_Module_id( void ) 
{
    return ti_deh_StackDbg_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_deh_StackDbg_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_deh_StackDbg_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_deh_StackDbg_Module_getMask( void ) 
{
    return ti_deh_StackDbg_Module__diagsMask__C != NULL ? *ti_deh_StackDbg_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_deh_StackDbg_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_deh_StackDbg_Module__diagsMask__C != NULL) {
        *ti_deh_StackDbg_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_deh_StackDbg__top__
#undef __nested__
#endif

#endif /* ti_deh_StackDbg__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_deh_StackDbg__internalaccess))

#ifndef ti_deh_StackDbg__include_state
#define ti_deh_StackDbg__include_state

/* Module_State */
struct ti_deh_StackDbg_Module_State {
    xdc_UInt codeBegin;
    xdc_UInt codeEnd;
};

/* Module__state__V */
extern struct ti_deh_StackDbg_Module_State__ ti_deh_StackDbg_Module__state__V;

#endif /* ti_deh_StackDbg__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_deh_StackDbg__nolocalnames)

#ifndef ti_deh_StackDbg__localnames__done
#define ti_deh_StackDbg__localnames__done

/* module prefix */
#define StackDbg_StackEntry ti_deh_StackDbg_StackEntry
#define StackDbg_VisitFuncPtr ti_deh_StackDbg_VisitFuncPtr
#define StackDbg_Module_State ti_deh_StackDbg_Module_State
#define StackDbg_walkStack ti_deh_StackDbg_walkStack
#define StackDbg_Module_name ti_deh_StackDbg_Module_name
#define StackDbg_Module_id ti_deh_StackDbg_Module_id
#define StackDbg_Module_startup ti_deh_StackDbg_Module_startup
#define StackDbg_Module_startupDone ti_deh_StackDbg_Module_startupDone
#define StackDbg_Module_hasMask ti_deh_StackDbg_Module_hasMask
#define StackDbg_Module_getMask ti_deh_StackDbg_Module_getMask
#define StackDbg_Module_setMask ti_deh_StackDbg_Module_setMask
#define StackDbg_Object_heap ti_deh_StackDbg_Object_heap
#define StackDbg_Module_heap ti_deh_StackDbg_Module_heap

#endif /* ti_deh_StackDbg__localnames__done */
#endif
