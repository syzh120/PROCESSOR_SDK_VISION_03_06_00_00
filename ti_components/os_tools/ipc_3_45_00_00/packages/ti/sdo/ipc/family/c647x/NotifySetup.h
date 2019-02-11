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

#ifndef ti_sdo_ipc_family_c647x_NotifySetup__include
#define ti_sdo_ipc_family_c647x_NotifySetup__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_family_c647x_NotifySetup__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_family_c647x_NotifySetup___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sdo/ipc/family/c647x/package/package.defs.h>

#include <ti/sdo/ipc/interfaces/INotifySetup.h>


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
typedef xdc_Bits32 CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsEnabled ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsIncluded ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsMask ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__gateObj ti_sdo_ipc_family_c647x_NotifySetup_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__gatePrms ti_sdo_ipc_family_c647x_NotifySetup_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__id ti_sdo_ipc_family_c647x_NotifySetup_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerDefined ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerObj ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn0 ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn1 ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn2 ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn4 ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn8 ti_sdo_ipc_family_c647x_NotifySetup_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__startupDoneFxn ti_sdo_ipc_family_c647x_NotifySetup_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_family_c647x_NotifySetup_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Object__count ti_sdo_ipc_family_c647x_NotifySetup_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_family_c647x_NotifySetup_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Object__heap ti_sdo_ipc_family_c647x_NotifySetup_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_family_c647x_NotifySetup_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Object__sizeof ti_sdo_ipc_family_c647x_NotifySetup_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_family_c647x_NotifySetup_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_Object__table ti_sdo_ipc_family_c647x_NotifySetup_Object__table__C;

/* dspIntVectId */
#ifdef ti_sdo_ipc_family_c647x_NotifySetup_dspIntVectId__D
#define ti_sdo_ipc_family_c647x_NotifySetup_dspIntVectId (ti_sdo_ipc_family_c647x_NotifySetup_dspIntVectId__D)
#else
#define ti_sdo_ipc_family_c647x_NotifySetup_dspIntVectId (ti_sdo_ipc_family_c647x_NotifySetup_dspIntVectId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_c647x_NotifySetup_dspIntVectId;
__extern __FAR__ const CT__ti_sdo_ipc_family_c647x_NotifySetup_dspIntVectId ti_sdo_ipc_family_c647x_NotifySetup_dspIntVectId__C;
#endif


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_family_c647x_NotifySetup_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*attach)(xdc_UInt16, xdc_Ptr);
    xdc_SizeT (*sharedMemReq)(xdc_UInt16, xdc_Ptr);
    xdc_UInt16 (*numIntLines)(xdc_UInt16);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_family_c647x_NotifySetup_Fxns__ ti_sdo_ipc_family_c647x_NotifySetup_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_family_c647x_NotifySetup_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_family_c647x_NotifySetup_Module__startupDone__S, "ti_sdo_ipc_family_c647x_NotifySetup_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_family_c647x_NotifySetup_Module__startupDone__S( void );

/* attach__E */
#define ti_sdo_ipc_family_c647x_NotifySetup_attach ti_sdo_ipc_family_c647x_NotifySetup_attach__E
xdc__CODESECT(ti_sdo_ipc_family_c647x_NotifySetup_attach__E, "ti_sdo_ipc_family_c647x_NotifySetup_attach")
__extern xdc_Int ti_sdo_ipc_family_c647x_NotifySetup_attach__E( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* sharedMemReq__E */
#define ti_sdo_ipc_family_c647x_NotifySetup_sharedMemReq ti_sdo_ipc_family_c647x_NotifySetup_sharedMemReq__E
xdc__CODESECT(ti_sdo_ipc_family_c647x_NotifySetup_sharedMemReq__E, "ti_sdo_ipc_family_c647x_NotifySetup_sharedMemReq")
__extern xdc_SizeT ti_sdo_ipc_family_c647x_NotifySetup_sharedMemReq__E( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* numIntLines__E */
#define ti_sdo_ipc_family_c647x_NotifySetup_numIntLines ti_sdo_ipc_family_c647x_NotifySetup_numIntLines__E
xdc__CODESECT(ti_sdo_ipc_family_c647x_NotifySetup_numIntLines__E, "ti_sdo_ipc_family_c647x_NotifySetup_numIntLines")
__extern xdc_UInt16 ti_sdo_ipc_family_c647x_NotifySetup_numIntLines__E( xdc_UInt16 remoteProcId );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_INotifySetup_Module ti_sdo_ipc_family_c647x_NotifySetup_Module_upCast( void )
{
    return (ti_sdo_ipc_interfaces_INotifySetup_Module)&ti_sdo_ipc_family_c647x_NotifySetup_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_INotifySetup */
#define ti_sdo_ipc_family_c647x_NotifySetup_Module_to_ti_sdo_ipc_interfaces_INotifySetup ti_sdo_ipc_family_c647x_NotifySetup_Module_upCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_family_c647x_NotifySetup_Module_startupDone() ti_sdo_ipc_family_c647x_NotifySetup_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_family_c647x_NotifySetup_Object_heap() ti_sdo_ipc_family_c647x_NotifySetup_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_family_c647x_NotifySetup_Module_heap() ti_sdo_ipc_family_c647x_NotifySetup_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_family_c647x_NotifySetup_Module__id ti_sdo_ipc_family_c647x_NotifySetup_Module_id( void ) 
{
    return ti_sdo_ipc_family_c647x_NotifySetup_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_family_c647x_NotifySetup_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_family_c647x_NotifySetup_Module_getMask( void ) 
{
    return ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsMask__C != NULL ? *ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_family_c647x_NotifySetup_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_family_c647x_NotifySetup_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_family_c647x_NotifySetup__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_family_c647x_NotifySetup__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_family_c647x_NotifySetup__internalaccess))

#ifndef ti_sdo_ipc_family_c647x_NotifySetup__include_state
#define ti_sdo_ipc_family_c647x_NotifySetup__include_state


#endif /* ti_sdo_ipc_family_c647x_NotifySetup__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_family_c647x_NotifySetup__nolocalnames)

#ifndef ti_sdo_ipc_family_c647x_NotifySetup__localnames__done
#define ti_sdo_ipc_family_c647x_NotifySetup__localnames__done

/* module prefix */
#define NotifySetup_dspIntVectId ti_sdo_ipc_family_c647x_NotifySetup_dspIntVectId
#define NotifySetup_attach ti_sdo_ipc_family_c647x_NotifySetup_attach
#define NotifySetup_sharedMemReq ti_sdo_ipc_family_c647x_NotifySetup_sharedMemReq
#define NotifySetup_numIntLines ti_sdo_ipc_family_c647x_NotifySetup_numIntLines
#define NotifySetup_Module_name ti_sdo_ipc_family_c647x_NotifySetup_Module_name
#define NotifySetup_Module_id ti_sdo_ipc_family_c647x_NotifySetup_Module_id
#define NotifySetup_Module_startup ti_sdo_ipc_family_c647x_NotifySetup_Module_startup
#define NotifySetup_Module_startupDone ti_sdo_ipc_family_c647x_NotifySetup_Module_startupDone
#define NotifySetup_Module_hasMask ti_sdo_ipc_family_c647x_NotifySetup_Module_hasMask
#define NotifySetup_Module_getMask ti_sdo_ipc_family_c647x_NotifySetup_Module_getMask
#define NotifySetup_Module_setMask ti_sdo_ipc_family_c647x_NotifySetup_Module_setMask
#define NotifySetup_Object_heap ti_sdo_ipc_family_c647x_NotifySetup_Object_heap
#define NotifySetup_Module_heap ti_sdo_ipc_family_c647x_NotifySetup_Module_heap
#define NotifySetup_Module_upCast ti_sdo_ipc_family_c647x_NotifySetup_Module_upCast
#define NotifySetup_Module_to_ti_sdo_ipc_interfaces_INotifySetup ti_sdo_ipc_family_c647x_NotifySetup_Module_to_ti_sdo_ipc_interfaces_INotifySetup

#endif /* ti_sdo_ipc_family_c647x_NotifySetup__localnames__done */
#endif
