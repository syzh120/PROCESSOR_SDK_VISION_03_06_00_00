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

#ifndef ti_deh_Deh__include
#define ti_deh_Deh__include

#ifndef __nested__
#define __nested__
#define ti_deh_Deh__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_deh_Deh___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/deh/package/package.defs.h>

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Swi.h>
#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* ExcRegs */
struct ti_deh_Deh_ExcRegs {
    xdc_Ptr r0;
    xdc_Ptr r1;
    xdc_Ptr r2;
    xdc_Ptr r3;
    xdc_Ptr r4;
    xdc_Ptr r5;
    xdc_Ptr r6;
    xdc_Ptr r7;
    xdc_Ptr r8;
    xdc_Ptr r9;
    xdc_Ptr r10;
    xdc_Ptr r11;
    xdc_Ptr r12;
    xdc_Ptr sp;
    xdc_Ptr lr;
    xdc_Ptr pc;
    xdc_Ptr psr;
    xdc_Ptr ICSR;
    xdc_Ptr MMFSR;
    xdc_Ptr BFSR;
    xdc_Ptr UFSR;
    xdc_Ptr HFSR;
    xdc_Ptr DFSR;
    xdc_Ptr MMAR;
    xdc_Ptr BFAR;
    xdc_Ptr AFSR;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* Module_State */
typedef xdc_Char __T1_ti_deh_Deh_Module_State__outbuf;
typedef xdc_Char *__ARRAY1_ti_deh_Deh_Module_State__outbuf;
typedef __ARRAY1_ti_deh_Deh_Module_State__outbuf __TA_ti_deh_Deh_Module_State__outbuf;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_deh_Deh_Module__diagsEnabled;
__extern __FAR__ const CT__ti_deh_Deh_Module__diagsEnabled ti_deh_Deh_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_deh_Deh_Module__diagsIncluded;
__extern __FAR__ const CT__ti_deh_Deh_Module__diagsIncluded ti_deh_Deh_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_deh_Deh_Module__diagsMask;
__extern __FAR__ const CT__ti_deh_Deh_Module__diagsMask ti_deh_Deh_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_deh_Deh_Module__gateObj;
__extern __FAR__ const CT__ti_deh_Deh_Module__gateObj ti_deh_Deh_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_deh_Deh_Module__gatePrms;
__extern __FAR__ const CT__ti_deh_Deh_Module__gatePrms ti_deh_Deh_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_deh_Deh_Module__id;
__extern __FAR__ const CT__ti_deh_Deh_Module__id ti_deh_Deh_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_deh_Deh_Module__loggerDefined;
__extern __FAR__ const CT__ti_deh_Deh_Module__loggerDefined ti_deh_Deh_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_deh_Deh_Module__loggerObj;
__extern __FAR__ const CT__ti_deh_Deh_Module__loggerObj ti_deh_Deh_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_deh_Deh_Module__loggerFxn0;
__extern __FAR__ const CT__ti_deh_Deh_Module__loggerFxn0 ti_deh_Deh_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_deh_Deh_Module__loggerFxn1;
__extern __FAR__ const CT__ti_deh_Deh_Module__loggerFxn1 ti_deh_Deh_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_deh_Deh_Module__loggerFxn2;
__extern __FAR__ const CT__ti_deh_Deh_Module__loggerFxn2 ti_deh_Deh_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_deh_Deh_Module__loggerFxn4;
__extern __FAR__ const CT__ti_deh_Deh_Module__loggerFxn4 ti_deh_Deh_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_deh_Deh_Module__loggerFxn8;
__extern __FAR__ const CT__ti_deh_Deh_Module__loggerFxn8 ti_deh_Deh_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_deh_Deh_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_deh_Deh_Module__startupDoneFxn ti_deh_Deh_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_deh_Deh_Object__count;
__extern __FAR__ const CT__ti_deh_Deh_Object__count ti_deh_Deh_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_deh_Deh_Object__heap;
__extern __FAR__ const CT__ti_deh_Deh_Object__heap ti_deh_Deh_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_deh_Deh_Object__sizeof;
__extern __FAR__ const CT__ti_deh_Deh_Object__sizeof ti_deh_Deh_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_deh_Deh_Object__table;
__extern __FAR__ const CT__ti_deh_Deh_Object__table ti_deh_Deh_Object__table__C;

/* bufSize */
#ifdef ti_deh_Deh_bufSize__D
#define ti_deh_Deh_bufSize (ti_deh_Deh_bufSize__D)
#else
#define ti_deh_Deh_bufSize (ti_deh_Deh_bufSize__C)
typedef xdc_SizeT CT__ti_deh_Deh_bufSize;
__extern __FAR__ const CT__ti_deh_Deh_bufSize ti_deh_Deh_bufSize__C;
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_deh_Deh_Module_startup ti_deh_Deh_Module_startup__E
xdc__CODESECT(ti_deh_Deh_Module_startup__E, "ti_deh_Deh_Module_startup")
__extern xdc_Int ti_deh_Deh_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_deh_Deh_Module_startup__F, "ti_deh_Deh_Module_startup")
__extern xdc_Int ti_deh_Deh_Module_startup__F( xdc_Int state );

/* Module__startupDone__S */
xdc__CODESECT(ti_deh_Deh_Module__startupDone__S, "ti_deh_Deh_Module__startupDone__S")
__extern xdc_Bool ti_deh_Deh_Module__startupDone__S( void );

/* excHandler__E */
#define ti_deh_Deh_excHandler ti_deh_Deh_excHandler__E
xdc__CODESECT(ti_deh_Deh_excHandler__E, "ti_deh_Deh_excHandler")
__extern xdc_Void ti_deh_Deh_excHandler__E( xdc_UInt *excStack, xdc_UInt lr );
xdc__CODESECT(ti_deh_Deh_excHandler__F, "ti_deh_Deh_excHandler")
__extern xdc_Void ti_deh_Deh_excHandler__F( xdc_UInt *excStack, xdc_UInt lr );

/* excHandlerDsp__E */
#define ti_deh_Deh_excHandlerDsp ti_deh_Deh_excHandlerDsp__E
xdc__CODESECT(ti_deh_Deh_excHandlerDsp__E, "ti_deh_Deh_excHandlerDsp")
__extern xdc_Void ti_deh_Deh_excHandlerDsp__E( void );
xdc__CODESECT(ti_deh_Deh_excHandlerDsp__F, "ti_deh_Deh_excHandlerDsp")
__extern xdc_Void ti_deh_Deh_excHandlerDsp__F( void );

/* idleBegin__E */
#define ti_deh_Deh_idleBegin ti_deh_Deh_idleBegin__E
xdc__CODESECT(ti_deh_Deh_idleBegin__E, "ti_deh_Deh_idleBegin")
__extern xdc_Void ti_deh_Deh_idleBegin__E( void );
xdc__CODESECT(ti_deh_Deh_idleBegin__F, "ti_deh_Deh_idleBegin")
__extern xdc_Void ti_deh_Deh_idleBegin__F( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_deh_Deh_Module_startupDone() ti_deh_Deh_Module__startupDone__S()

/* Object_heap */
#define ti_deh_Deh_Object_heap() ti_deh_Deh_Object__heap__C

/* Module_heap */
#define ti_deh_Deh_Module_heap() ti_deh_Deh_Object__heap__C

/* Module_id */
static inline CT__ti_deh_Deh_Module__id ti_deh_Deh_Module_id( void ) 
{
    return ti_deh_Deh_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_deh_Deh_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_deh_Deh_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_deh_Deh_Module_getMask( void ) 
{
    return ti_deh_Deh_Module__diagsMask__C != NULL ? *ti_deh_Deh_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_deh_Deh_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_deh_Deh_Module__diagsMask__C != NULL) {
        *ti_deh_Deh_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_deh_Deh__top__
#undef __nested__
#endif

#endif /* ti_deh_Deh__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_deh_Deh__internalaccess))

#ifndef ti_deh_Deh__include_state
#define ti_deh_Deh__include_state

/* Module_State */
struct ti_deh_Deh_Module_State {
    __TA_ti_deh_Deh_Module_State__outbuf outbuf;
    xdc_SizeT isrStackSize;
    xdc_Ptr isrStackBase;
};

/* Module__state__V */
extern struct ti_deh_Deh_Module_State__ ti_deh_Deh_Module__state__V;

#endif /* ti_deh_Deh__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_deh_Deh__nolocalnames)

#ifndef ti_deh_Deh__localnames__done
#define ti_deh_Deh__localnames__done

/* module prefix */
#define Deh_ExcRegs ti_deh_Deh_ExcRegs
#define Deh_Module_State ti_deh_Deh_Module_State
#define Deh_bufSize ti_deh_Deh_bufSize
#define Deh_excHandler ti_deh_Deh_excHandler
#define Deh_excHandlerDsp ti_deh_Deh_excHandlerDsp
#define Deh_idleBegin ti_deh_Deh_idleBegin
#define Deh_Module_name ti_deh_Deh_Module_name
#define Deh_Module_id ti_deh_Deh_Module_id
#define Deh_Module_startup ti_deh_Deh_Module_startup
#define Deh_Module_startupDone ti_deh_Deh_Module_startupDone
#define Deh_Module_hasMask ti_deh_Deh_Module_hasMask
#define Deh_Module_getMask ti_deh_Deh_Module_getMask
#define Deh_Module_setMask ti_deh_Deh_Module_setMask
#define Deh_Object_heap ti_deh_Deh_Object_heap
#define Deh_Module_heap ti_deh_Deh_Module_heap

#endif /* ti_deh_Deh__localnames__done */
#endif
