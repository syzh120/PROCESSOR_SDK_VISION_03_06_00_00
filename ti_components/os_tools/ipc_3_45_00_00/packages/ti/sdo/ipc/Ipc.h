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

#ifndef ti_sdo_ipc_Ipc__include
#define ti_sdo_ipc_Ipc__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_Ipc__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_Ipc___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sdo/ipc/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <ti/sdo/utils/MultiProc.h>
#include <xdc/runtime/IModule.h>
#include <ti/sdo/ipc/SharedRegion.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* ProcSync */
enum ti_sdo_ipc_Ipc_ProcSync {
    ti_sdo_ipc_Ipc_ProcSync_NONE,
    ti_sdo_ipc_Ipc_ProcSync_PAIR,
    ti_sdo_ipc_Ipc_ProcSync_ALL
};
typedef enum ti_sdo_ipc_Ipc_ProcSync ti_sdo_ipc_Ipc_ProcSync;

/* Entry */
struct ti_sdo_ipc_Ipc_Entry {
    xdc_UInt16 remoteProcId;
    xdc_Bool setupNotify;
    xdc_Bool setupMessageQ;
};

/* UserFxn */
struct ti_sdo_ipc_Ipc_UserFxn {
    xdc_Int (*attach)(xdc_UArg, xdc_UInt16);
    xdc_Int (*detach)(xdc_UArg, xdc_UInt16);
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* PROCSYNCSTART */
#define ti_sdo_ipc_Ipc_PROCSYNCSTART (1)

/* PROCSYNCFINISH */
#define ti_sdo_ipc_Ipc_PROCSYNCFINISH (2)

/* PROCSYNCDETACH */
#define ti_sdo_ipc_Ipc_PROCSYNCDETACH (3)

/* ObjType */
enum ti_sdo_ipc_Ipc_ObjType {
    ti_sdo_ipc_Ipc_ObjType_CREATESTATIC = 0x1,
    ti_sdo_ipc_Ipc_ObjType_CREATESTATIC_REGION = 0x2,
    ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC = 0x4,
    ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION = 0x8,
    ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC = 0x10,
    ti_sdo_ipc_Ipc_ObjType_LOCAL = 0x20
};
typedef enum ti_sdo_ipc_Ipc_ObjType ti_sdo_ipc_Ipc_ObjType;

/* ConfigEntry */
struct ti_sdo_ipc_Ipc_ConfigEntry {
    xdc_Bits32 remoteProcId;
    xdc_Bits32 localProcId;
    xdc_Bits32 tag;
    xdc_Bits32 size;
    xdc_Bits32 next;
};

/* ProcEntry */
struct ti_sdo_ipc_Ipc_ProcEntry {
    ti_sdo_ipc_SharedRegion_SRPtr *localConfigList;
    ti_sdo_ipc_SharedRegion_SRPtr *remoteConfigList;
    xdc_UInt attached;
    ti_sdo_ipc_Ipc_Entry entry;
};

/* Reserved */
struct ti_sdo_ipc_Ipc_Reserved {
    volatile xdc_Bits32 startedKey;
    ti_sdo_ipc_SharedRegion_SRPtr notifySRPtr;
    ti_sdo_ipc_SharedRegion_SRPtr nsrnSRPtr;
    ti_sdo_ipc_SharedRegion_SRPtr transportSRPtr;
    ti_sdo_ipc_SharedRegion_SRPtr configListHead;
};

/* UserFxnAndArg */
struct ti_sdo_ipc_Ipc_UserFxnAndArg {
    ti_sdo_ipc_Ipc_UserFxn userFxn;
    xdc_UArg arg;
};

/* Module_State */
typedef ti_sdo_ipc_Ipc_ProcEntry __T1_ti_sdo_ipc_Ipc_Module_State__procEntry;
typedef ti_sdo_ipc_Ipc_ProcEntry *__ARRAY1_ti_sdo_ipc_Ipc_Module_State__procEntry;
typedef __ARRAY1_ti_sdo_ipc_Ipc_Module_State__procEntry __TA_ti_sdo_ipc_Ipc_Module_State__procEntry;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_Ipc_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__diagsEnabled ti_sdo_ipc_Ipc_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_Ipc_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__diagsIncluded ti_sdo_ipc_Ipc_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_Ipc_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__diagsMask ti_sdo_ipc_Ipc_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_Ipc_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__gateObj ti_sdo_ipc_Ipc_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_Ipc_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__gatePrms ti_sdo_ipc_Ipc_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_Ipc_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__id ti_sdo_ipc_Ipc_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_Ipc_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__loggerDefined ti_sdo_ipc_Ipc_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_Ipc_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__loggerObj ti_sdo_ipc_Ipc_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_Ipc_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__loggerFxn0 ti_sdo_ipc_Ipc_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_Ipc_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__loggerFxn1 ti_sdo_ipc_Ipc_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_Ipc_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__loggerFxn2 ti_sdo_ipc_Ipc_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_Ipc_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__loggerFxn4 ti_sdo_ipc_Ipc_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_Ipc_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__loggerFxn8 ti_sdo_ipc_Ipc_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_Ipc_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Module__startupDoneFxn ti_sdo_ipc_Ipc_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_Ipc_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Object__count ti_sdo_ipc_Ipc_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_Ipc_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Object__heap ti_sdo_ipc_Ipc_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_Ipc_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Object__sizeof ti_sdo_ipc_Ipc_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_Ipc_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_Object__table ti_sdo_ipc_Ipc_Object__table__C;

/* A_addrNotInSharedRegion */
#define ti_sdo_ipc_Ipc_A_addrNotInSharedRegion (ti_sdo_ipc_Ipc_A_addrNotInSharedRegion__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Ipc_A_addrNotInSharedRegion;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_A_addrNotInSharedRegion ti_sdo_ipc_Ipc_A_addrNotInSharedRegion__C;

/* A_addrNotCacheAligned */
#define ti_sdo_ipc_Ipc_A_addrNotCacheAligned (ti_sdo_ipc_Ipc_A_addrNotCacheAligned__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Ipc_A_addrNotCacheAligned;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_A_addrNotCacheAligned ti_sdo_ipc_Ipc_A_addrNotCacheAligned__C;

/* A_nullArgument */
#define ti_sdo_ipc_Ipc_A_nullArgument (ti_sdo_ipc_Ipc_A_nullArgument__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Ipc_A_nullArgument;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_A_nullArgument ti_sdo_ipc_Ipc_A_nullArgument__C;

/* A_nullPointer */
#define ti_sdo_ipc_Ipc_A_nullPointer (ti_sdo_ipc_Ipc_A_nullPointer__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Ipc_A_nullPointer;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_A_nullPointer ti_sdo_ipc_Ipc_A_nullPointer__C;

/* A_invArgument */
#define ti_sdo_ipc_Ipc_A_invArgument (ti_sdo_ipc_Ipc_A_invArgument__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Ipc_A_invArgument;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_A_invArgument ti_sdo_ipc_Ipc_A_invArgument__C;

/* A_invParam */
#define ti_sdo_ipc_Ipc_A_invParam (ti_sdo_ipc_Ipc_A_invParam__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Ipc_A_invParam;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_A_invParam ti_sdo_ipc_Ipc_A_invParam__C;

/* A_internal */
#define ti_sdo_ipc_Ipc_A_internal (ti_sdo_ipc_Ipc_A_internal__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_Ipc_A_internal;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_A_internal ti_sdo_ipc_Ipc_A_internal__C;

/* E_nameFailed */
#define ti_sdo_ipc_Ipc_E_nameFailed (ti_sdo_ipc_Ipc_E_nameFailed__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_Ipc_E_nameFailed;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_E_nameFailed ti_sdo_ipc_Ipc_E_nameFailed__C;

/* E_internal */
#define ti_sdo_ipc_Ipc_E_internal (ti_sdo_ipc_Ipc_E_internal__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_Ipc_E_internal;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_E_internal ti_sdo_ipc_Ipc_E_internal__C;

/* E_versionMismatch */
#define ti_sdo_ipc_Ipc_E_versionMismatch (ti_sdo_ipc_Ipc_E_versionMismatch__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_Ipc_E_versionMismatch;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_E_versionMismatch ti_sdo_ipc_Ipc_E_versionMismatch__C;

/* sr0MemorySetup */
#ifdef ti_sdo_ipc_Ipc_sr0MemorySetup__D
#define ti_sdo_ipc_Ipc_sr0MemorySetup (ti_sdo_ipc_Ipc_sr0MemorySetup__D)
#else
#define ti_sdo_ipc_Ipc_sr0MemorySetup (ti_sdo_ipc_Ipc_sr0MemorySetup__C)
typedef xdc_Bool CT__ti_sdo_ipc_Ipc_sr0MemorySetup;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_sr0MemorySetup ti_sdo_ipc_Ipc_sr0MemorySetup__C;
#endif

/* procSync */
#define ti_sdo_ipc_Ipc_procSync (ti_sdo_ipc_Ipc_procSync__C)
typedef ti_sdo_ipc_Ipc_ProcSync CT__ti_sdo_ipc_Ipc_procSync;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_procSync ti_sdo_ipc_Ipc_procSync__C;

/* generateSlaveDataForHost */
#ifdef ti_sdo_ipc_Ipc_generateSlaveDataForHost__D
#define ti_sdo_ipc_Ipc_generateSlaveDataForHost (ti_sdo_ipc_Ipc_generateSlaveDataForHost__D)
#else
#define ti_sdo_ipc_Ipc_generateSlaveDataForHost (ti_sdo_ipc_Ipc_generateSlaveDataForHost__C)
typedef xdc_Bool CT__ti_sdo_ipc_Ipc_generateSlaveDataForHost;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_generateSlaveDataForHost ti_sdo_ipc_Ipc_generateSlaveDataForHost__C;
#endif

/* userFxn */
#define ti_sdo_ipc_Ipc_userFxn (ti_sdo_ipc_Ipc_userFxn__C)
typedef ti_sdo_ipc_Ipc_UserFxn CT__ti_sdo_ipc_Ipc_userFxn;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_userFxn ti_sdo_ipc_Ipc_userFxn__C;

/* numUserFxns */
#ifdef ti_sdo_ipc_Ipc_numUserFxns__D
#define ti_sdo_ipc_Ipc_numUserFxns (ti_sdo_ipc_Ipc_numUserFxns__D)
#else
#define ti_sdo_ipc_Ipc_numUserFxns (ti_sdo_ipc_Ipc_numUserFxns__C)
typedef xdc_UInt CT__ti_sdo_ipc_Ipc_numUserFxns;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_numUserFxns ti_sdo_ipc_Ipc_numUserFxns__C;
#endif

/* userFxns */
#define ti_sdo_ipc_Ipc_userFxns (ti_sdo_ipc_Ipc_userFxns__C)
typedef ti_sdo_ipc_Ipc_UserFxnAndArg __T1_ti_sdo_ipc_Ipc_userFxns;
typedef ti_sdo_ipc_Ipc_UserFxnAndArg *__ARRAY1_ti_sdo_ipc_Ipc_userFxns;
typedef __ARRAY1_ti_sdo_ipc_Ipc_userFxns __TA_ti_sdo_ipc_Ipc_userFxns;
typedef __TA_ti_sdo_ipc_Ipc_userFxns CT__ti_sdo_ipc_Ipc_userFxns;
__extern __FAR__ const CT__ti_sdo_ipc_Ipc_userFxns ti_sdo_ipc_Ipc_userFxns__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_Ipc_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_Ipc_Module__startupDone__S, "ti_sdo_ipc_Ipc_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_Ipc_Module__startupDone__S( void );

/* getEntry__E */
#define ti_sdo_ipc_Ipc_getEntry ti_sdo_ipc_Ipc_getEntry__E
xdc__CODESECT(ti_sdo_ipc_Ipc_getEntry__E, "ti_sdo_ipc_Ipc_getEntry")
__extern xdc_Void ti_sdo_ipc_Ipc_getEntry__E( ti_sdo_ipc_Ipc_Entry *entry );
xdc__CODESECT(ti_sdo_ipc_Ipc_getEntry__F, "ti_sdo_ipc_Ipc_getEntry")
__extern xdc_Void ti_sdo_ipc_Ipc_getEntry__F( ti_sdo_ipc_Ipc_Entry *entry );

/* setEntry__E */
#define ti_sdo_ipc_Ipc_setEntry ti_sdo_ipc_Ipc_setEntry__E
xdc__CODESECT(ti_sdo_ipc_Ipc_setEntry__E, "ti_sdo_ipc_Ipc_setEntry")
__extern xdc_Void ti_sdo_ipc_Ipc_setEntry__E( ti_sdo_ipc_Ipc_Entry *entry );
xdc__CODESECT(ti_sdo_ipc_Ipc_setEntry__F, "ti_sdo_ipc_Ipc_setEntry")
__extern xdc_Void ti_sdo_ipc_Ipc_setEntry__F( ti_sdo_ipc_Ipc_Entry *entry );

/* dummy__E */
#define ti_sdo_ipc_Ipc_dummy ti_sdo_ipc_Ipc_dummy__E
xdc__CODESECT(ti_sdo_ipc_Ipc_dummy__E, "ti_sdo_ipc_Ipc_dummy")
__extern xdc_Void ti_sdo_ipc_Ipc_dummy__E( void );
xdc__CODESECT(ti_sdo_ipc_Ipc_dummy__F, "ti_sdo_ipc_Ipc_dummy")
__extern xdc_Void ti_sdo_ipc_Ipc_dummy__F( void );

/* getMasterAddr__I */
#define ti_sdo_ipc_Ipc_getMasterAddr ti_sdo_ipc_Ipc_getMasterAddr__I
xdc__CODESECT(ti_sdo_ipc_Ipc_getMasterAddr__I, "ti_sdo_ipc_Ipc_getMasterAddr")
__extern xdc_Ptr ti_sdo_ipc_Ipc_getMasterAddr__I( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* getRegion0ReservedSize__I */
#define ti_sdo_ipc_Ipc_getRegion0ReservedSize ti_sdo_ipc_Ipc_getRegion0ReservedSize__I
xdc__CODESECT(ti_sdo_ipc_Ipc_getRegion0ReservedSize__I, "ti_sdo_ipc_Ipc_getRegion0ReservedSize")
__extern xdc_SizeT ti_sdo_ipc_Ipc_getRegion0ReservedSize__I( void );

/* getSlaveAddr__I */
#define ti_sdo_ipc_Ipc_getSlaveAddr ti_sdo_ipc_Ipc_getSlaveAddr__I
xdc__CODESECT(ti_sdo_ipc_Ipc_getSlaveAddr__I, "ti_sdo_ipc_Ipc_getSlaveAddr")
__extern xdc_Ptr ti_sdo_ipc_Ipc_getSlaveAddr__I( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* procSyncStart__I */
#define ti_sdo_ipc_Ipc_procSyncStart ti_sdo_ipc_Ipc_procSyncStart__I
xdc__CODESECT(ti_sdo_ipc_Ipc_procSyncStart__I, "ti_sdo_ipc_Ipc_procSyncStart")
__extern xdc_Int ti_sdo_ipc_Ipc_procSyncStart__I( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* procSyncFinish__I */
#define ti_sdo_ipc_Ipc_procSyncFinish ti_sdo_ipc_Ipc_procSyncFinish__I
xdc__CODESECT(ti_sdo_ipc_Ipc_procSyncFinish__I, "ti_sdo_ipc_Ipc_procSyncFinish")
__extern xdc_Int ti_sdo_ipc_Ipc_procSyncFinish__I( xdc_UInt16 remoteProcId, xdc_Ptr sharedAddr );

/* reservedSizePerProc__I */
#define ti_sdo_ipc_Ipc_reservedSizePerProc ti_sdo_ipc_Ipc_reservedSizePerProc__I
xdc__CODESECT(ti_sdo_ipc_Ipc_reservedSizePerProc__I, "ti_sdo_ipc_Ipc_reservedSizePerProc")
__extern xdc_SizeT ti_sdo_ipc_Ipc_reservedSizePerProc__I( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_Ipc_Module_startupDone() ti_sdo_ipc_Ipc_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_Ipc_Object_heap() ti_sdo_ipc_Ipc_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_Ipc_Module_heap() ti_sdo_ipc_Ipc_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_Ipc_Module__id ti_sdo_ipc_Ipc_Module_id( void ) 
{
    return ti_sdo_ipc_Ipc_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_Ipc_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_Ipc_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_Ipc_Module_getMask( void ) 
{
    return ti_sdo_ipc_Ipc_Module__diagsMask__C != NULL ? *ti_sdo_ipc_Ipc_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_Ipc_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_Ipc_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_Ipc_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_Ipc__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_Ipc__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_Ipc__internalaccess))

#ifndef ti_sdo_ipc_Ipc__include_state
#define ti_sdo_ipc_Ipc__include_state

/* Module_State */
struct ti_sdo_ipc_Ipc_Module_State {
    xdc_Ptr ipcSharedAddr;
    xdc_Ptr gateMPSharedAddr;
    __TA_ti_sdo_ipc_Ipc_Module_State__procEntry procEntry;
};

/* Module__state__V */
extern struct ti_sdo_ipc_Ipc_Module_State__ ti_sdo_ipc_Ipc_Module__state__V;

#endif /* ti_sdo_ipc_Ipc__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_Ipc__nolocalnames)

#ifndef ti_sdo_ipc_Ipc__localnames__done
#define ti_sdo_ipc_Ipc__localnames__done

/* module prefix */
#define Ipc_ProcSync ti_sdo_ipc_Ipc_ProcSync
#define Ipc_Entry ti_sdo_ipc_Ipc_Entry
#define Ipc_UserFxn ti_sdo_ipc_Ipc_UserFxn
#define Ipc_PROCSYNCSTART ti_sdo_ipc_Ipc_PROCSYNCSTART
#define Ipc_PROCSYNCFINISH ti_sdo_ipc_Ipc_PROCSYNCFINISH
#define Ipc_PROCSYNCDETACH ti_sdo_ipc_Ipc_PROCSYNCDETACH
#define Ipc_ObjType ti_sdo_ipc_Ipc_ObjType
#define Ipc_ConfigEntry ti_sdo_ipc_Ipc_ConfigEntry
#define Ipc_ProcEntry ti_sdo_ipc_Ipc_ProcEntry
#define Ipc_Reserved ti_sdo_ipc_Ipc_Reserved
#define Ipc_UserFxnAndArg ti_sdo_ipc_Ipc_UserFxnAndArg
#define Ipc_Module_State ti_sdo_ipc_Ipc_Module_State
#define Ipc_ProcSync_NONE ti_sdo_ipc_Ipc_ProcSync_NONE
#define Ipc_ProcSync_PAIR ti_sdo_ipc_Ipc_ProcSync_PAIR
#define Ipc_ProcSync_ALL ti_sdo_ipc_Ipc_ProcSync_ALL
#define Ipc_ObjType_CREATESTATIC ti_sdo_ipc_Ipc_ObjType_CREATESTATIC
#define Ipc_ObjType_CREATESTATIC_REGION ti_sdo_ipc_Ipc_ObjType_CREATESTATIC_REGION
#define Ipc_ObjType_CREATEDYNAMIC ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC
#define Ipc_ObjType_CREATEDYNAMIC_REGION ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION
#define Ipc_ObjType_OPENDYNAMIC ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC
#define Ipc_ObjType_LOCAL ti_sdo_ipc_Ipc_ObjType_LOCAL
#define Ipc_A_addrNotInSharedRegion ti_sdo_ipc_Ipc_A_addrNotInSharedRegion
#define Ipc_A_addrNotCacheAligned ti_sdo_ipc_Ipc_A_addrNotCacheAligned
#define Ipc_A_nullArgument ti_sdo_ipc_Ipc_A_nullArgument
#define Ipc_A_nullPointer ti_sdo_ipc_Ipc_A_nullPointer
#define Ipc_A_invArgument ti_sdo_ipc_Ipc_A_invArgument
#define Ipc_A_invParam ti_sdo_ipc_Ipc_A_invParam
#define Ipc_A_internal ti_sdo_ipc_Ipc_A_internal
#define Ipc_E_nameFailed ti_sdo_ipc_Ipc_E_nameFailed
#define Ipc_E_internal ti_sdo_ipc_Ipc_E_internal
#define Ipc_E_versionMismatch ti_sdo_ipc_Ipc_E_versionMismatch
#define Ipc_sr0MemorySetup ti_sdo_ipc_Ipc_sr0MemorySetup
#define Ipc_procSync ti_sdo_ipc_Ipc_procSync
#define Ipc_generateSlaveDataForHost ti_sdo_ipc_Ipc_generateSlaveDataForHost
#define Ipc_userFxn ti_sdo_ipc_Ipc_userFxn
#define Ipc_numUserFxns ti_sdo_ipc_Ipc_numUserFxns
#define Ipc_userFxns ti_sdo_ipc_Ipc_userFxns
#define Ipc_getEntry ti_sdo_ipc_Ipc_getEntry
#define Ipc_setEntry ti_sdo_ipc_Ipc_setEntry
#define Ipc_dummy ti_sdo_ipc_Ipc_dummy
#define Ipc_Module_name ti_sdo_ipc_Ipc_Module_name
#define Ipc_Module_id ti_sdo_ipc_Ipc_Module_id
#define Ipc_Module_startup ti_sdo_ipc_Ipc_Module_startup
#define Ipc_Module_startupDone ti_sdo_ipc_Ipc_Module_startupDone
#define Ipc_Module_hasMask ti_sdo_ipc_Ipc_Module_hasMask
#define Ipc_Module_getMask ti_sdo_ipc_Ipc_Module_getMask
#define Ipc_Module_setMask ti_sdo_ipc_Ipc_Module_setMask
#define Ipc_Object_heap ti_sdo_ipc_Ipc_Object_heap
#define Ipc_Module_heap ti_sdo_ipc_Ipc_Module_heap

#endif /* ti_sdo_ipc_Ipc__localnames__done */
#endif
