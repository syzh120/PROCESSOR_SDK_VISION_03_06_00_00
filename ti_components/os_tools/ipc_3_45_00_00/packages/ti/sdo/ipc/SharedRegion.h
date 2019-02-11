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

#ifndef ti_sdo_ipc_SharedRegion__include
#define ti_sdo_ipc_SharedRegion__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_SharedRegion__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_SharedRegion___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sdo/ipc/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/IModule.h>
#include <xdc/runtime/Assert.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* SRPtr */
typedef xdc_Bits32 ti_sdo_ipc_SharedRegion_SRPtr;

/* Entry */
struct ti_sdo_ipc_SharedRegion_Entry {
    xdc_Ptr base;
    xdc_SizeT len;
    xdc_UInt16 ownerProcId;
    xdc_Bool isValid;
    xdc_Bool cacheEnable;
    xdc_SizeT cacheLineSize;
    xdc_Bool createHeap;
    xdc_String name;
};

/* INVALIDREGIONID */
#define ti_sdo_ipc_SharedRegion_INVALIDREGIONID (0xFFFF)

/* DEFAULTOWNERID */
#define ti_sdo_ipc_SharedRegion_DEFAULTOWNERID (~0)


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* CREATED */
#define ti_sdo_ipc_SharedRegion_CREATED (0x08111963)

/* Region */
struct ti_sdo_ipc_SharedRegion_Region {
    ti_sdo_ipc_SharedRegion_Entry entry;
    xdc_SizeT reservedSize;
    xdc_runtime_IHeap_Handle heap;
};

/* Module_State */
typedef ti_sdo_ipc_SharedRegion_Region __T1_ti_sdo_ipc_SharedRegion_Module_State__regions;
typedef ti_sdo_ipc_SharedRegion_Region *__ARRAY1_ti_sdo_ipc_SharedRegion_Module_State__regions;
typedef __ARRAY1_ti_sdo_ipc_SharedRegion_Module_State__regions __TA_ti_sdo_ipc_SharedRegion_Module_State__regions;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_SharedRegion_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__diagsEnabled ti_sdo_ipc_SharedRegion_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_SharedRegion_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__diagsIncluded ti_sdo_ipc_SharedRegion_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_SharedRegion_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__diagsMask ti_sdo_ipc_SharedRegion_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_SharedRegion_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__gateObj ti_sdo_ipc_SharedRegion_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_SharedRegion_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__gatePrms ti_sdo_ipc_SharedRegion_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_SharedRegion_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__id ti_sdo_ipc_SharedRegion_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_SharedRegion_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__loggerDefined ti_sdo_ipc_SharedRegion_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_SharedRegion_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__loggerObj ti_sdo_ipc_SharedRegion_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_SharedRegion_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__loggerFxn0 ti_sdo_ipc_SharedRegion_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_SharedRegion_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__loggerFxn1 ti_sdo_ipc_SharedRegion_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_SharedRegion_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__loggerFxn2 ti_sdo_ipc_SharedRegion_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_SharedRegion_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__loggerFxn4 ti_sdo_ipc_SharedRegion_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_SharedRegion_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__loggerFxn8 ti_sdo_ipc_SharedRegion_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_SharedRegion_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Module__startupDoneFxn ti_sdo_ipc_SharedRegion_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_SharedRegion_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Object__count ti_sdo_ipc_SharedRegion_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_SharedRegion_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Object__heap ti_sdo_ipc_SharedRegion_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_SharedRegion_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Object__sizeof ti_sdo_ipc_SharedRegion_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_SharedRegion_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_Object__table ti_sdo_ipc_SharedRegion_Object__table__C;

/* A_idTooLarge */
#define ti_sdo_ipc_SharedRegion_A_idTooLarge (ti_sdo_ipc_SharedRegion_A_idTooLarge__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_SharedRegion_A_idTooLarge;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_A_idTooLarge ti_sdo_ipc_SharedRegion_A_idTooLarge__C;

/* A_addrOutOfRange */
#define ti_sdo_ipc_SharedRegion_A_addrOutOfRange (ti_sdo_ipc_SharedRegion_A_addrOutOfRange__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_SharedRegion_A_addrOutOfRange;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_A_addrOutOfRange ti_sdo_ipc_SharedRegion_A_addrOutOfRange__C;

/* A_region0Clear */
#define ti_sdo_ipc_SharedRegion_A_region0Clear (ti_sdo_ipc_SharedRegion_A_region0Clear__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_SharedRegion_A_region0Clear;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_A_region0Clear ti_sdo_ipc_SharedRegion_A_region0Clear__C;

/* A_region0Invalid */
#define ti_sdo_ipc_SharedRegion_A_region0Invalid (ti_sdo_ipc_SharedRegion_A_region0Invalid__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_SharedRegion_A_region0Invalid;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_A_region0Invalid ti_sdo_ipc_SharedRegion_A_region0Invalid__C;

/* A_regionInvalid */
#define ti_sdo_ipc_SharedRegion_A_regionInvalid (ti_sdo_ipc_SharedRegion_A_regionInvalid__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_SharedRegion_A_regionInvalid;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_A_regionInvalid ti_sdo_ipc_SharedRegion_A_regionInvalid__C;

/* A_reserveTooMuch */
#define ti_sdo_ipc_SharedRegion_A_reserveTooMuch (ti_sdo_ipc_SharedRegion_A_reserveTooMuch__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_SharedRegion_A_reserveTooMuch;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_A_reserveTooMuch ti_sdo_ipc_SharedRegion_A_reserveTooMuch__C;

/* A_cacheLineSizeIsZero */
#define ti_sdo_ipc_SharedRegion_A_cacheLineSizeIsZero (ti_sdo_ipc_SharedRegion_A_cacheLineSizeIsZero__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_SharedRegion_A_cacheLineSizeIsZero;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_A_cacheLineSizeIsZero ti_sdo_ipc_SharedRegion_A_cacheLineSizeIsZero__C;

/* A_overlap */
#define ti_sdo_ipc_SharedRegion_A_overlap (ti_sdo_ipc_SharedRegion_A_overlap__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_SharedRegion_A_overlap;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_A_overlap ti_sdo_ipc_SharedRegion_A_overlap__C;

/* A_alreadyExists */
#define ti_sdo_ipc_SharedRegion_A_alreadyExists (ti_sdo_ipc_SharedRegion_A_alreadyExists__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_SharedRegion_A_alreadyExists;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_A_alreadyExists ti_sdo_ipc_SharedRegion_A_alreadyExists__C;

/* A_noHeap */
#define ti_sdo_ipc_SharedRegion_A_noHeap (ti_sdo_ipc_SharedRegion_A_noHeap__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_SharedRegion_A_noHeap;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_A_noHeap ti_sdo_ipc_SharedRegion_A_noHeap__C;

/* cacheLineSize */
#ifdef ti_sdo_ipc_SharedRegion_cacheLineSize__D
#define ti_sdo_ipc_SharedRegion_cacheLineSize (ti_sdo_ipc_SharedRegion_cacheLineSize__D)
#else
#define ti_sdo_ipc_SharedRegion_cacheLineSize (ti_sdo_ipc_SharedRegion_cacheLineSize__C)
typedef xdc_SizeT CT__ti_sdo_ipc_SharedRegion_cacheLineSize;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_cacheLineSize ti_sdo_ipc_SharedRegion_cacheLineSize__C;
#endif

/* numEntries */
#ifdef ti_sdo_ipc_SharedRegion_numEntries__D
#define ti_sdo_ipc_SharedRegion_numEntries (ti_sdo_ipc_SharedRegion_numEntries__D)
#else
#define ti_sdo_ipc_SharedRegion_numEntries (ti_sdo_ipc_SharedRegion_numEntries__C)
typedef xdc_UInt16 CT__ti_sdo_ipc_SharedRegion_numEntries;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_numEntries ti_sdo_ipc_SharedRegion_numEntries__C;
#endif

/* translate */
#ifdef ti_sdo_ipc_SharedRegion_translate__D
#define ti_sdo_ipc_SharedRegion_translate (ti_sdo_ipc_SharedRegion_translate__D)
#else
#define ti_sdo_ipc_SharedRegion_translate (ti_sdo_ipc_SharedRegion_translate__C)
typedef xdc_Bool CT__ti_sdo_ipc_SharedRegion_translate;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_translate ti_sdo_ipc_SharedRegion_translate__C;
#endif

/* INVALIDSRPTR */
#ifdef ti_sdo_ipc_SharedRegion_INVALIDSRPTR__D
#define ti_sdo_ipc_SharedRegion_INVALIDSRPTR (ti_sdo_ipc_SharedRegion_INVALIDSRPTR__D)
#else
#define ti_sdo_ipc_SharedRegion_INVALIDSRPTR (ti_sdo_ipc_SharedRegion_INVALIDSRPTR__C)
typedef ti_sdo_ipc_SharedRegion_SRPtr CT__ti_sdo_ipc_SharedRegion_INVALIDSRPTR;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_INVALIDSRPTR ti_sdo_ipc_SharedRegion_INVALIDSRPTR__C;
#endif

/* numOffsetBits */
#ifdef ti_sdo_ipc_SharedRegion_numOffsetBits__D
#define ti_sdo_ipc_SharedRegion_numOffsetBits (ti_sdo_ipc_SharedRegion_numOffsetBits__D)
#else
#define ti_sdo_ipc_SharedRegion_numOffsetBits (ti_sdo_ipc_SharedRegion_numOffsetBits__C)
typedef xdc_UInt32 CT__ti_sdo_ipc_SharedRegion_numOffsetBits;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_numOffsetBits ti_sdo_ipc_SharedRegion_numOffsetBits__C;
#endif

/* offsetMask */
#ifdef ti_sdo_ipc_SharedRegion_offsetMask__D
#define ti_sdo_ipc_SharedRegion_offsetMask (ti_sdo_ipc_SharedRegion_offsetMask__D)
#else
#define ti_sdo_ipc_SharedRegion_offsetMask (ti_sdo_ipc_SharedRegion_offsetMask__C)
typedef xdc_UInt32 CT__ti_sdo_ipc_SharedRegion_offsetMask;
__extern __FAR__ const CT__ti_sdo_ipc_SharedRegion_offsetMask ti_sdo_ipc_SharedRegion_offsetMask__C;
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_SharedRegion_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_SharedRegion_Module__startupDone__S, "ti_sdo_ipc_SharedRegion_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_SharedRegion_Module__startupDone__S( void );

/* attach__E */
#define ti_sdo_ipc_SharedRegion_attach ti_sdo_ipc_SharedRegion_attach__E
xdc__CODESECT(ti_sdo_ipc_SharedRegion_attach__E, "ti_sdo_ipc_SharedRegion_attach")
__extern xdc_Int ti_sdo_ipc_SharedRegion_attach__E( xdc_UInt16 remoteProcId );
xdc__CODESECT(ti_sdo_ipc_SharedRegion_attach__F, "ti_sdo_ipc_SharedRegion_attach")
__extern xdc_Int ti_sdo_ipc_SharedRegion_attach__F( xdc_UInt16 remoteProcId );

/* clearReservedMemory__E */
#define ti_sdo_ipc_SharedRegion_clearReservedMemory ti_sdo_ipc_SharedRegion_clearReservedMemory__E
xdc__CODESECT(ti_sdo_ipc_SharedRegion_clearReservedMemory__E, "ti_sdo_ipc_SharedRegion_clearReservedMemory")
__extern xdc_Void ti_sdo_ipc_SharedRegion_clearReservedMemory__E( void );
xdc__CODESECT(ti_sdo_ipc_SharedRegion_clearReservedMemory__F, "ti_sdo_ipc_SharedRegion_clearReservedMemory")
__extern xdc_Void ti_sdo_ipc_SharedRegion_clearReservedMemory__F( void );

/* detach__E */
#define ti_sdo_ipc_SharedRegion_detach ti_sdo_ipc_SharedRegion_detach__E
xdc__CODESECT(ti_sdo_ipc_SharedRegion_detach__E, "ti_sdo_ipc_SharedRegion_detach")
__extern xdc_Int ti_sdo_ipc_SharedRegion_detach__E( xdc_UInt16 remoteProcId );
xdc__CODESECT(ti_sdo_ipc_SharedRegion_detach__F, "ti_sdo_ipc_SharedRegion_detach")
__extern xdc_Int ti_sdo_ipc_SharedRegion_detach__F( xdc_UInt16 remoteProcId );

/* reserveMemory__E */
#define ti_sdo_ipc_SharedRegion_reserveMemory ti_sdo_ipc_SharedRegion_reserveMemory__E
xdc__CODESECT(ti_sdo_ipc_SharedRegion_reserveMemory__E, "ti_sdo_ipc_SharedRegion_reserveMemory")
__extern xdc_Ptr ti_sdo_ipc_SharedRegion_reserveMemory__E( xdc_UInt16 id, xdc_SizeT size );
xdc__CODESECT(ti_sdo_ipc_SharedRegion_reserveMemory__F, "ti_sdo_ipc_SharedRegion_reserveMemory")
__extern xdc_Ptr ti_sdo_ipc_SharedRegion_reserveMemory__F( xdc_UInt16 id, xdc_SizeT size );

/* resetInternalFields__E */
#define ti_sdo_ipc_SharedRegion_resetInternalFields ti_sdo_ipc_SharedRegion_resetInternalFields__E
xdc__CODESECT(ti_sdo_ipc_SharedRegion_resetInternalFields__E, "ti_sdo_ipc_SharedRegion_resetInternalFields")
__extern xdc_Void ti_sdo_ipc_SharedRegion_resetInternalFields__E( xdc_UInt16 id );
xdc__CODESECT(ti_sdo_ipc_SharedRegion_resetInternalFields__F, "ti_sdo_ipc_SharedRegion_resetInternalFields")
__extern xdc_Void ti_sdo_ipc_SharedRegion_resetInternalFields__F( xdc_UInt16 id );

/* start__E */
#define ti_sdo_ipc_SharedRegion_start ti_sdo_ipc_SharedRegion_start__E
xdc__CODESECT(ti_sdo_ipc_SharedRegion_start__E, "ti_sdo_ipc_SharedRegion_start")
__extern xdc_Int ti_sdo_ipc_SharedRegion_start__E( void );
xdc__CODESECT(ti_sdo_ipc_SharedRegion_start__F, "ti_sdo_ipc_SharedRegion_start")
__extern xdc_Int ti_sdo_ipc_SharedRegion_start__F( void );

/* stop__E */
#define ti_sdo_ipc_SharedRegion_stop ti_sdo_ipc_SharedRegion_stop__E
xdc__CODESECT(ti_sdo_ipc_SharedRegion_stop__E, "ti_sdo_ipc_SharedRegion_stop")
__extern xdc_Int ti_sdo_ipc_SharedRegion_stop__E( void );
xdc__CODESECT(ti_sdo_ipc_SharedRegion_stop__F, "ti_sdo_ipc_SharedRegion_stop")
__extern xdc_Int ti_sdo_ipc_SharedRegion_stop__F( void );

/* checkOverlap__I */
#define ti_sdo_ipc_SharedRegion_checkOverlap ti_sdo_ipc_SharedRegion_checkOverlap__I
xdc__CODESECT(ti_sdo_ipc_SharedRegion_checkOverlap__I, "ti_sdo_ipc_SharedRegion_checkOverlap")
__extern xdc_Int ti_sdo_ipc_SharedRegion_checkOverlap__I( xdc_Ptr base, xdc_SizeT len );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_SharedRegion_Module_startupDone() ti_sdo_ipc_SharedRegion_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_SharedRegion_Object_heap() ti_sdo_ipc_SharedRegion_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_SharedRegion_Module_heap() ti_sdo_ipc_SharedRegion_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_SharedRegion_Module__id ti_sdo_ipc_SharedRegion_Module_id( void ) 
{
    return ti_sdo_ipc_SharedRegion_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_SharedRegion_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_SharedRegion_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_SharedRegion_Module_getMask( void ) 
{
    return ti_sdo_ipc_SharedRegion_Module__diagsMask__C != NULL ? *ti_sdo_ipc_SharedRegion_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_SharedRegion_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_SharedRegion_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_SharedRegion_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_SharedRegion__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_SharedRegion__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_SharedRegion__internalaccess))

#ifndef ti_sdo_ipc_SharedRegion__include_state
#define ti_sdo_ipc_SharedRegion__include_state

/* Module_State */
struct ti_sdo_ipc_SharedRegion_Module_State {
    __TA_ti_sdo_ipc_SharedRegion_Module_State__regions regions;
};

/* Module__state__V */
extern struct ti_sdo_ipc_SharedRegion_Module_State__ ti_sdo_ipc_SharedRegion_Module__state__V;

#endif /* ti_sdo_ipc_SharedRegion__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_SharedRegion__nolocalnames)

#ifndef ti_sdo_ipc_SharedRegion__localnames__done
#define ti_sdo_ipc_SharedRegion__localnames__done

/* module prefix */
#define SharedRegion_SRPtr ti_sdo_ipc_SharedRegion_SRPtr
#define SharedRegion_Entry ti_sdo_ipc_SharedRegion_Entry
#define SharedRegion_INVALIDREGIONID ti_sdo_ipc_SharedRegion_INVALIDREGIONID
#define SharedRegion_DEFAULTOWNERID ti_sdo_ipc_SharedRegion_DEFAULTOWNERID
#define SharedRegion_CREATED ti_sdo_ipc_SharedRegion_CREATED
#define SharedRegion_Region ti_sdo_ipc_SharedRegion_Region
#define SharedRegion_Module_State ti_sdo_ipc_SharedRegion_Module_State
#define SharedRegion_A_idTooLarge ti_sdo_ipc_SharedRegion_A_idTooLarge
#define SharedRegion_A_addrOutOfRange ti_sdo_ipc_SharedRegion_A_addrOutOfRange
#define SharedRegion_A_region0Clear ti_sdo_ipc_SharedRegion_A_region0Clear
#define SharedRegion_A_region0Invalid ti_sdo_ipc_SharedRegion_A_region0Invalid
#define SharedRegion_A_regionInvalid ti_sdo_ipc_SharedRegion_A_regionInvalid
#define SharedRegion_A_reserveTooMuch ti_sdo_ipc_SharedRegion_A_reserveTooMuch
#define SharedRegion_A_cacheLineSizeIsZero ti_sdo_ipc_SharedRegion_A_cacheLineSizeIsZero
#define SharedRegion_A_overlap ti_sdo_ipc_SharedRegion_A_overlap
#define SharedRegion_A_alreadyExists ti_sdo_ipc_SharedRegion_A_alreadyExists
#define SharedRegion_A_noHeap ti_sdo_ipc_SharedRegion_A_noHeap
#define SharedRegion_cacheLineSize ti_sdo_ipc_SharedRegion_cacheLineSize
#define SharedRegion_numEntries ti_sdo_ipc_SharedRegion_numEntries
#define SharedRegion_translate ti_sdo_ipc_SharedRegion_translate
#define SharedRegion_INVALIDSRPTR ti_sdo_ipc_SharedRegion_INVALIDSRPTR
#define SharedRegion_numOffsetBits ti_sdo_ipc_SharedRegion_numOffsetBits
#define SharedRegion_offsetMask ti_sdo_ipc_SharedRegion_offsetMask
#define SharedRegion_attach ti_sdo_ipc_SharedRegion_attach
#define SharedRegion_clearReservedMemory ti_sdo_ipc_SharedRegion_clearReservedMemory
#define SharedRegion_detach ti_sdo_ipc_SharedRegion_detach
#define SharedRegion_reserveMemory ti_sdo_ipc_SharedRegion_reserveMemory
#define SharedRegion_resetInternalFields ti_sdo_ipc_SharedRegion_resetInternalFields
#define SharedRegion_start ti_sdo_ipc_SharedRegion_start
#define SharedRegion_stop ti_sdo_ipc_SharedRegion_stop
#define SharedRegion_Module_name ti_sdo_ipc_SharedRegion_Module_name
#define SharedRegion_Module_id ti_sdo_ipc_SharedRegion_Module_id
#define SharedRegion_Module_startup ti_sdo_ipc_SharedRegion_Module_startup
#define SharedRegion_Module_startupDone ti_sdo_ipc_SharedRegion_Module_startupDone
#define SharedRegion_Module_hasMask ti_sdo_ipc_SharedRegion_Module_hasMask
#define SharedRegion_Module_getMask ti_sdo_ipc_SharedRegion_Module_getMask
#define SharedRegion_Module_setMask ti_sdo_ipc_SharedRegion_Module_setMask
#define SharedRegion_Object_heap ti_sdo_ipc_SharedRegion_Object_heap
#define SharedRegion_Module_heap ti_sdo_ipc_SharedRegion_Module_heap

#endif /* ti_sdo_ipc_SharedRegion__localnames__done */
#endif
