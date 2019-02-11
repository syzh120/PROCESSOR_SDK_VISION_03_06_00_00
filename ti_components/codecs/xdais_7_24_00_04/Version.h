/*
 *  Copyright 2013 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y13
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
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

#ifndef xdais_7_24_00_04_Version__include
#define xdais_7_24_00_04_Version__include

#ifndef __nested__
#define __nested__
#define xdais_7_24_00_04_Version__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdais_7_24_00_04_Version___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdais_7_24_00_04/package/package.defs.h>

#include <ti/sdoarch/standards/pkg/IVersion.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* MAJOR */
#define xdais_7_24_00_04_Version_MAJOR (7)

/* MINOR */
#define xdais_7_24_00_04_Version_MINOR (24)

/* PATCH */
#define xdais_7_24_00_04_Version_PATCH (00)

/* WIDTH */
#define xdais_7_24_00_04_Version_WIDTH (2)


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdais_7_24_00_04_Version_Module__diagsEnabled;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__diagsEnabled xdais_7_24_00_04_Version_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdais_7_24_00_04_Version_Module__diagsIncluded;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__diagsIncluded xdais_7_24_00_04_Version_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdais_7_24_00_04_Version_Module__diagsMask;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__diagsMask xdais_7_24_00_04_Version_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdais_7_24_00_04_Version_Module__gateObj;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__gateObj xdais_7_24_00_04_Version_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdais_7_24_00_04_Version_Module__gatePrms;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__gatePrms xdais_7_24_00_04_Version_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdais_7_24_00_04_Version_Module__id;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__id xdais_7_24_00_04_Version_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdais_7_24_00_04_Version_Module__loggerDefined;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__loggerDefined xdais_7_24_00_04_Version_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdais_7_24_00_04_Version_Module__loggerObj;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__loggerObj xdais_7_24_00_04_Version_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdais_7_24_00_04_Version_Module__loggerFxn0;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__loggerFxn0 xdais_7_24_00_04_Version_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdais_7_24_00_04_Version_Module__loggerFxn1;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__loggerFxn1 xdais_7_24_00_04_Version_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdais_7_24_00_04_Version_Module__loggerFxn2;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__loggerFxn2 xdais_7_24_00_04_Version_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdais_7_24_00_04_Version_Module__loggerFxn4;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__loggerFxn4 xdais_7_24_00_04_Version_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdais_7_24_00_04_Version_Module__loggerFxn8;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__loggerFxn8 xdais_7_24_00_04_Version_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdais_7_24_00_04_Version_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Module__startupDoneFxn xdais_7_24_00_04_Version_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdais_7_24_00_04_Version_Object__count;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Object__count xdais_7_24_00_04_Version_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdais_7_24_00_04_Version_Object__heap;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Object__heap xdais_7_24_00_04_Version_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdais_7_24_00_04_Version_Object__sizeof;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Object__sizeof xdais_7_24_00_04_Version_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdais_7_24_00_04_Version_Object__table;
__extern __FAR__ const CT__xdais_7_24_00_04_Version_Object__table xdais_7_24_00_04_Version_Object__table__C;


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdais_7_24_00_04_Version_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const xdais_7_24_00_04_Version_Fxns__ xdais_7_24_00_04_Version_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdais_7_24_00_04_Version_Module_startup( state ) -1

/* Module__startupDone__S */
xdc__CODESECT(xdais_7_24_00_04_Version_Module__startupDone__S, "xdais_7_24_00_04_Version_Module__startupDone")
__extern xdc_Bool xdais_7_24_00_04_Version_Module__startupDone__S( void );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdoarch_standards_pkg_IVersion_Module xdais_7_24_00_04_Version_Module_upCast( void )
{
    return (ti_sdoarch_standards_pkg_IVersion_Module)&xdais_7_24_00_04_Version_Module__FXNS__C;
}

/* Module_to_ti_sdoarch_standards_pkg_IVersion */
#define xdais_7_24_00_04_Version_Module_to_ti_sdoarch_standards_pkg_IVersion xdais_7_24_00_04_Version_Module_upCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdais_7_24_00_04_Version_Module_startupDone() xdais_7_24_00_04_Version_Module__startupDone__S()

/* Object_heap */
#define xdais_7_24_00_04_Version_Object_heap() xdais_7_24_00_04_Version_Object__heap__C

/* Module_heap */
#define xdais_7_24_00_04_Version_Module_heap() xdais_7_24_00_04_Version_Object__heap__C

/* Module_id */
static inline CT__xdais_7_24_00_04_Version_Module__id xdais_7_24_00_04_Version_Module_id( void ) 
{
    return xdais_7_24_00_04_Version_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdais_7_24_00_04_Version_Module_hasMask( void ) 
{
    return xdais_7_24_00_04_Version_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 xdais_7_24_00_04_Version_Module_getMask( void ) 
{
    return xdais_7_24_00_04_Version_Module__diagsMask__C != NULL ? *xdais_7_24_00_04_Version_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void xdais_7_24_00_04_Version_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdais_7_24_00_04_Version_Module__diagsMask__C != NULL) *xdais_7_24_00_04_Version_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdais_7_24_00_04_Version__top__
#undef __nested__
#endif

#endif /* xdais_7_24_00_04_Version__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdais_7_24_00_04_Version__internalaccess))

#ifndef xdais_7_24_00_04_Version__include_state
#define xdais_7_24_00_04_Version__include_state


#endif /* xdais_7_24_00_04_Version__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdais_7_24_00_04_Version__nolocalnames)

#ifndef xdais_7_24_00_04_Version__localnames__done
#define xdais_7_24_00_04_Version__localnames__done

/* module prefix */
#define Version_MAJOR xdais_7_24_00_04_Version_MAJOR
#define Version_MINOR xdais_7_24_00_04_Version_MINOR
#define Version_PATCH xdais_7_24_00_04_Version_PATCH
#define Version_WIDTH xdais_7_24_00_04_Version_WIDTH
#define Version_Module_name xdais_7_24_00_04_Version_Module_name
#define Version_Module_id xdais_7_24_00_04_Version_Module_id
#define Version_Module_startup xdais_7_24_00_04_Version_Module_startup
#define Version_Module_startupDone xdais_7_24_00_04_Version_Module_startupDone
#define Version_Module_hasMask xdais_7_24_00_04_Version_Module_hasMask
#define Version_Module_getMask xdais_7_24_00_04_Version_Module_getMask
#define Version_Module_setMask xdais_7_24_00_04_Version_Module_setMask
#define Version_Object_heap xdais_7_24_00_04_Version_Object_heap
#define Version_Module_heap xdais_7_24_00_04_Version_Module_heap
#define Version_Module_upCast xdais_7_24_00_04_Version_Module_upCast
#define Version_Module_to_ti_sdoarch_standards_pkg_IVersion xdais_7_24_00_04_Version_Module_to_ti_sdoarch_standards_pkg_IVersion

#endif /* xdais_7_24_00_04_Version__localnames__done */
#endif
/*
 *  @(#) xdais_7_24_00_04; 1, 0, 0,1; 5-20-2013 12:17:15; /db/wtree/library/trees/dais/dais-x04/src/ xlibrary

 */

