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

#ifndef ti_ipc_family_tci6638_NotifyCircSetup__include
#define ti_ipc_family_tci6638_NotifyCircSetup__include

#ifndef __nested__
#define __nested__
#define ti_ipc_family_tci6638_NotifyCircSetup__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_ipc_family_tci6638_NotifyCircSetup___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/ipc/family/tci6638/package/package.defs.h>

#include <xdc/runtime/Assert.h>
#include <ti/sdo/ipc/interfaces/INotifySetup.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* SRCS_BITPOS_CORE0 */
#define ti_ipc_family_tci6638_NotifyCircSetup_SRCS_BITPOS_CORE0 (4)

/* SRCS_BITPOS_HOST */
#define ti_ipc_family_tci6638_NotifyCircSetup_SRCS_BITPOS_HOST (31)


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsEnabled;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsEnabled ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsIncluded;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsIncluded ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsMask;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsMask ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__gateObj;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__gateObj ti_ipc_family_tci6638_NotifyCircSetup_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__gatePrms;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__gatePrms ti_ipc_family_tci6638_NotifyCircSetup_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__id;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__id ti_ipc_family_tci6638_NotifyCircSetup_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerDefined;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerDefined ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerObj;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerObj ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn0;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn0 ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn1;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn1 ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn2;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn2 ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn4;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn4 ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn8;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn8 ti_ipc_family_tci6638_NotifyCircSetup_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__startupDoneFxn ti_ipc_family_tci6638_NotifyCircSetup_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_ipc_family_tci6638_NotifyCircSetup_Object__count;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Object__count ti_ipc_family_tci6638_NotifyCircSetup_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_ipc_family_tci6638_NotifyCircSetup_Object__heap;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Object__heap ti_ipc_family_tci6638_NotifyCircSetup_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_ipc_family_tci6638_NotifyCircSetup_Object__sizeof;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Object__sizeof ti_ipc_family_tci6638_NotifyCircSetup_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_ipc_family_tci6638_NotifyCircSetup_Object__table;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_Object__table ti_ipc_family_tci6638_NotifyCircSetup_Object__table__C;

/* dspIntVectId */
#ifdef ti_ipc_family_tci6638_NotifyCircSetup_dspIntVectId__D
#define ti_ipc_family_tci6638_NotifyCircSetup_dspIntVectId (ti_ipc_family_tci6638_NotifyCircSetup_dspIntVectId__D)
#else
#define ti_ipc_family_tci6638_NotifyCircSetup_dspIntVectId (ti_ipc_family_tci6638_NotifyCircSetup_dspIntVectId__C)
typedef xdc_UInt CT__ti_ipc_family_tci6638_NotifyCircSetup_dspIntVectId;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_dspIntVectId ti_ipc_family_tci6638_NotifyCircSetup_dspIntVectId__C;
#endif

/* A_notImplemented */
#define ti_ipc_family_tci6638_NotifyCircSetup_A_notImplemented (ti_ipc_family_tci6638_NotifyCircSetup_A_notImplemented__C)
typedef xdc_runtime_Assert_Id CT__ti_ipc_family_tci6638_NotifyCircSetup_A_notImplemented;
__extern __FAR__ const CT__ti_ipc_family_tci6638_NotifyCircSetup_A_notImplemented ti_ipc_family_tci6638_NotifyCircSetup_A_notImplemented__C;


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_ipc_family_tci6638_NotifyCircSetup_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*attach)(xdc_UInt16, xdc_Ptr);
    xdc_SizeT (*sharedMemReq)(xdc_UInt16, xdc_Ptr);
    xdc_UInt16 (*numIntLines)(xdc_UInt16);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_ipc_family_tci6638_NotifyCircSetup_Fxns__ ti_ipc_family_tci6638_NotifyCircSetup_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_ipc_family_tci6638_NotifyCircSetup_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_ipc_family_tci6638_NotifyCircSetup_Module__startupDone__S, "ti_ipc_family_tci6638_NotifyCircSetup_Module__startupDone__S")
__extern xdc_Bool ti_ipc_family_tci6638_NotifyCircSetup_Module__startupDone__S( void );

/* attach__E */
#define ti_ipc_family_tci6638_NotifyCircSetup_attach ti_ipc_family_tci6638_NotifyCircSetup_attach__E
xdc__CODESECT(ti_ipc_family_tci6638_NotifyCircSetup_attach__E, "ti_ipc_family_tci6638_NotifyCircSetup_attach")
__extern xdc_Int ti_ipc_family_tci6638_NotifyCircSetup_attach__E( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* sharedMemReq__E */
#define ti_ipc_family_tci6638_NotifyCircSetup_sharedMemReq ti_ipc_family_tci6638_NotifyCircSetup_sharedMemReq__E
xdc__CODESECT(ti_ipc_family_tci6638_NotifyCircSetup_sharedMemReq__E, "ti_ipc_family_tci6638_NotifyCircSetup_sharedMemReq")
__extern xdc_SizeT ti_ipc_family_tci6638_NotifyCircSetup_sharedMemReq__E( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* numIntLines__E */
#define ti_ipc_family_tci6638_NotifyCircSetup_numIntLines ti_ipc_family_tci6638_NotifyCircSetup_numIntLines__E
xdc__CODESECT(ti_ipc_family_tci6638_NotifyCircSetup_numIntLines__E, "ti_ipc_family_tci6638_NotifyCircSetup_numIntLines")
__extern xdc_UInt16 ti_ipc_family_tci6638_NotifyCircSetup_numIntLines__E( xdc_UInt16 remoteProcId );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_INotifySetup_Module ti_ipc_family_tci6638_NotifyCircSetup_Module_upCast( void )
{
    return (ti_sdo_ipc_interfaces_INotifySetup_Module)&ti_ipc_family_tci6638_NotifyCircSetup_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_INotifySetup */
#define ti_ipc_family_tci6638_NotifyCircSetup_Module_to_ti_sdo_ipc_interfaces_INotifySetup ti_ipc_family_tci6638_NotifyCircSetup_Module_upCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_ipc_family_tci6638_NotifyCircSetup_Module_startupDone() ti_ipc_family_tci6638_NotifyCircSetup_Module__startupDone__S()

/* Object_heap */
#define ti_ipc_family_tci6638_NotifyCircSetup_Object_heap() ti_ipc_family_tci6638_NotifyCircSetup_Object__heap__C

/* Module_heap */
#define ti_ipc_family_tci6638_NotifyCircSetup_Module_heap() ti_ipc_family_tci6638_NotifyCircSetup_Object__heap__C

/* Module_id */
static inline CT__ti_ipc_family_tci6638_NotifyCircSetup_Module__id ti_ipc_family_tci6638_NotifyCircSetup_Module_id( void ) 
{
    return ti_ipc_family_tci6638_NotifyCircSetup_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_ipc_family_tci6638_NotifyCircSetup_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_ipc_family_tci6638_NotifyCircSetup_Module_getMask( void ) 
{
    return ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsMask__C != NULL ? *ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_ipc_family_tci6638_NotifyCircSetup_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsMask__C != NULL) {
        *ti_ipc_family_tci6638_NotifyCircSetup_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_ipc_family_tci6638_NotifyCircSetup__top__
#undef __nested__
#endif

#endif /* ti_ipc_family_tci6638_NotifyCircSetup__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_ipc_family_tci6638_NotifyCircSetup__internalaccess))

#ifndef ti_ipc_family_tci6638_NotifyCircSetup__include_state
#define ti_ipc_family_tci6638_NotifyCircSetup__include_state


#endif /* ti_ipc_family_tci6638_NotifyCircSetup__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_ipc_family_tci6638_NotifyCircSetup__nolocalnames)

#ifndef ti_ipc_family_tci6638_NotifyCircSetup__localnames__done
#define ti_ipc_family_tci6638_NotifyCircSetup__localnames__done

/* module prefix */
#define NotifyCircSetup_SRCS_BITPOS_CORE0 ti_ipc_family_tci6638_NotifyCircSetup_SRCS_BITPOS_CORE0
#define NotifyCircSetup_SRCS_BITPOS_HOST ti_ipc_family_tci6638_NotifyCircSetup_SRCS_BITPOS_HOST
#define NotifyCircSetup_dspIntVectId ti_ipc_family_tci6638_NotifyCircSetup_dspIntVectId
#define NotifyCircSetup_A_notImplemented ti_ipc_family_tci6638_NotifyCircSetup_A_notImplemented
#define NotifyCircSetup_attach ti_ipc_family_tci6638_NotifyCircSetup_attach
#define NotifyCircSetup_sharedMemReq ti_ipc_family_tci6638_NotifyCircSetup_sharedMemReq
#define NotifyCircSetup_numIntLines ti_ipc_family_tci6638_NotifyCircSetup_numIntLines
#define NotifyCircSetup_Module_name ti_ipc_family_tci6638_NotifyCircSetup_Module_name
#define NotifyCircSetup_Module_id ti_ipc_family_tci6638_NotifyCircSetup_Module_id
#define NotifyCircSetup_Module_startup ti_ipc_family_tci6638_NotifyCircSetup_Module_startup
#define NotifyCircSetup_Module_startupDone ti_ipc_family_tci6638_NotifyCircSetup_Module_startupDone
#define NotifyCircSetup_Module_hasMask ti_ipc_family_tci6638_NotifyCircSetup_Module_hasMask
#define NotifyCircSetup_Module_getMask ti_ipc_family_tci6638_NotifyCircSetup_Module_getMask
#define NotifyCircSetup_Module_setMask ti_ipc_family_tci6638_NotifyCircSetup_Module_setMask
#define NotifyCircSetup_Object_heap ti_ipc_family_tci6638_NotifyCircSetup_Object_heap
#define NotifyCircSetup_Module_heap ti_ipc_family_tci6638_NotifyCircSetup_Module_heap
#define NotifyCircSetup_Module_upCast ti_ipc_family_tci6638_NotifyCircSetup_Module_upCast
#define NotifyCircSetup_Module_to_ti_sdo_ipc_interfaces_INotifySetup ti_ipc_family_tci6638_NotifyCircSetup_Module_to_ti_sdo_ipc_interfaces_INotifySetup

#endif /* ti_ipc_family_tci6638_NotifyCircSetup__localnames__done */
#endif
