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
 *     PER-INSTANCE TYPES
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

#ifndef ti_sdo_ipc_heaps_HeapMultiBufMP__include
#define ti_sdo_ipc_heaps_HeapMultiBufMP__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_heaps_HeapMultiBufMP__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_heaps_HeapMultiBufMP___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/heaps/package/package.defs.h>

#include <ti/sdo/ipc/SharedRegion.h>
#include <ti/sdo/ipc/Ipc.h>
#include <ti/sdo/ipc/GateMP.h>
#include <ti/sdo/utils/NameServer.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/IHeap.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Bucket */
struct ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket {
    xdc_SizeT blockSize;
    xdc_UInt numBlocks;
    xdc_SizeT align;
};

/* ExtendedStats */
typedef xdc_UInt __T1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__numBlocks;
typedef xdc_UInt __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__numBlocks[8];
typedef __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__numBlocks __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__numBlocks;
typedef xdc_UInt __T1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__blockSize;
typedef xdc_UInt __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__blockSize[8];
typedef __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__blockSize __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__blockSize;
typedef xdc_UInt __T1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__align;
typedef xdc_UInt __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__align[8];
typedef __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__align __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__align;
typedef xdc_UInt __T1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__maxAllocatedBlocks;
typedef xdc_UInt __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__maxAllocatedBlocks[8];
typedef __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__maxAllocatedBlocks __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__maxAllocatedBlocks;
typedef xdc_UInt __T1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__numAllocatedBlocks;
typedef xdc_UInt __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__numAllocatedBlocks[8];
typedef __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__numAllocatedBlocks __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__numAllocatedBlocks;
struct ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats {
    xdc_UInt numBuckets;
    __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__numBlocks numBlocks;
    __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__blockSize blockSize;
    __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__align align;
    __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__maxAllocatedBlocks maxAllocatedBlocks;
    __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats__numAllocatedBlocks numAllocatedBlocks;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* CREATED */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_CREATED (0x05101920)

/* Elem */
struct ti_sdo_ipc_heaps_HeapMultiBufMP_Elem {
    volatile ti_sdo_ipc_SharedRegion_SRPtr next;
};

/* BucketAttrs */
struct ti_sdo_ipc_heaps_HeapMultiBufMP_BucketAttrs {
    ti_sdo_ipc_SharedRegion_SRPtr head;
    ti_sdo_ipc_SharedRegion_SRPtr tail;
    ti_sdo_ipc_SharedRegion_SRPtr baseAddr;
    xdc_Bits32 numFreeBlocks;
    xdc_Bits32 minFreeBlocks;
    xdc_Bits32 blockSize;
    xdc_Bits32 align;
    xdc_Bits32 numBlocks;
};

/* Attrs */
typedef ti_sdo_ipc_heaps_HeapMultiBufMP_BucketAttrs __T1_ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs__buckets;
typedef ti_sdo_ipc_heaps_HeapMultiBufMP_BucketAttrs __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs__buckets[8];
typedef __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs__buckets __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs__buckets;
struct ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs {
    xdc_Bits32 status;
    ti_sdo_ipc_SharedRegion_SRPtr gateMPAddr;
    xdc_Bits32 numBuckets;
    __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs__buckets buckets;
    xdc_Bits16 exact;
};

/* Instance_State */
typedef ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket __T1_ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_State__bucketEntries;
typedef ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket *__ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_State__bucketEntries;
typedef __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_State__bucketEntries __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_State__bucketEntries;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsEnabled ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsIncluded ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsMask ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__gateObj ti_sdo_ipc_heaps_HeapMultiBufMP_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__gatePrms ti_sdo_ipc_heaps_HeapMultiBufMP_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__id ti_sdo_ipc_heaps_HeapMultiBufMP_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerDefined ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerObj ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn0 ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn1 ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn2 ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn4 ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn8 ti_sdo_ipc_heaps_HeapMultiBufMP_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__startupDoneFxn ti_sdo_ipc_heaps_HeapMultiBufMP_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Object__count ti_sdo_ipc_heaps_HeapMultiBufMP_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Object__heap ti_sdo_ipc_heaps_HeapMultiBufMP_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Object__sizeof ti_sdo_ipc_heaps_HeapMultiBufMP_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Object__table ti_sdo_ipc_heaps_HeapMultiBufMP_Object__table__C;

/* A_invalidAlign */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_A_invalidAlign (ti_sdo_ipc_heaps_HeapMultiBufMP_A_invalidAlign__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_heaps_HeapMultiBufMP_A_invalidAlign;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_A_invalidAlign ti_sdo_ipc_heaps_HeapMultiBufMP_A_invalidAlign__C;

/* A_sizeNotFound */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_A_sizeNotFound (ti_sdo_ipc_heaps_HeapMultiBufMP_A_sizeNotFound__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_heaps_HeapMultiBufMP_A_sizeNotFound;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_A_sizeNotFound ti_sdo_ipc_heaps_HeapMultiBufMP_A_sizeNotFound__C;

/* A_addrNotFound */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_A_addrNotFound (ti_sdo_ipc_heaps_HeapMultiBufMP_A_addrNotFound__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_heaps_HeapMultiBufMP_A_addrNotFound;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_A_addrNotFound ti_sdo_ipc_heaps_HeapMultiBufMP_A_addrNotFound__C;

/* E_exactFail */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_E_exactFail (ti_sdo_ipc_heaps_HeapMultiBufMP_E_exactFail__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_heaps_HeapMultiBufMP_E_exactFail;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_E_exactFail ti_sdo_ipc_heaps_HeapMultiBufMP_E_exactFail__C;

/* E_size */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_E_size (ti_sdo_ipc_heaps_HeapMultiBufMP_E_size__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_heaps_HeapMultiBufMP_E_size;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_E_size ti_sdo_ipc_heaps_HeapMultiBufMP_E_size__C;

/* E_noBlocksLeft */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_E_noBlocksLeft (ti_sdo_ipc_heaps_HeapMultiBufMP_E_noBlocksLeft__C)
typedef xdc_runtime_Error_Id CT__ti_sdo_ipc_heaps_HeapMultiBufMP_E_noBlocksLeft;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_E_noBlocksLeft ti_sdo_ipc_heaps_HeapMultiBufMP_E_noBlocksLeft__C;

/* maxNameLen */
#ifdef ti_sdo_ipc_heaps_HeapMultiBufMP_maxNameLen__D
#define ti_sdo_ipc_heaps_HeapMultiBufMP_maxNameLen (ti_sdo_ipc_heaps_HeapMultiBufMP_maxNameLen__D)
#else
#define ti_sdo_ipc_heaps_HeapMultiBufMP_maxNameLen (ti_sdo_ipc_heaps_HeapMultiBufMP_maxNameLen__C)
typedef xdc_UInt CT__ti_sdo_ipc_heaps_HeapMultiBufMP_maxNameLen;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_maxNameLen ti_sdo_ipc_heaps_HeapMultiBufMP_maxNameLen__C;
#endif

/* trackMaxAllocs */
#ifdef ti_sdo_ipc_heaps_HeapMultiBufMP_trackMaxAllocs__D
#define ti_sdo_ipc_heaps_HeapMultiBufMP_trackMaxAllocs (ti_sdo_ipc_heaps_HeapMultiBufMP_trackMaxAllocs__D)
#else
#define ti_sdo_ipc_heaps_HeapMultiBufMP_trackMaxAllocs (ti_sdo_ipc_heaps_HeapMultiBufMP_trackMaxAllocs__C)
typedef xdc_Bool CT__ti_sdo_ipc_heaps_HeapMultiBufMP_trackMaxAllocs;
__extern __FAR__ const CT__ti_sdo_ipc_heaps_HeapMultiBufMP_trackMaxAllocs ti_sdo_ipc_heaps_HeapMultiBufMP_trackMaxAllocs__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
typedef ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket __T1_ti_sdo_ipc_heaps_HeapMultiBufMP_bucketEntries;
typedef ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket *__ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_bucketEntries;
typedef __ARRAY1_ti_sdo_ipc_heaps_HeapMultiBufMP_bucketEntries __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_bucketEntries;
struct ti_sdo_ipc_heaps_HeapMultiBufMP_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    ti_sdo_ipc_GateMP_Handle gate;
    xdc_Bool openFlag;
    xdc_Bool exact;
    xdc_String name;
    xdc_Int numBuckets;
    __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_bucketEntries bucketEntries;
    xdc_UInt16 regionId;
    xdc_Ptr sharedAddr;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_heaps_HeapMultiBufMP_Struct {
    const ti_sdo_ipc_heaps_HeapMultiBufMP_Fxns__ *__fxns;
    ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs *__f0;
    ti_sdo_ipc_GateMP_Handle __f1;
    ti_sdo_ipc_Ipc_ObjType __f2;
    xdc_Ptr __f3;
    xdc_Bool __f4;
    xdc_UInt16 __f5;
    xdc_SizeT __f6;
    xdc_Char *__f7;
    __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_State__bucketEntries __f8;
    xdc_UInt __f9;
    xdc_Bool __f10;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_heaps_HeapMultiBufMP_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Ptr (*alloc)(ti_sdo_ipc_heaps_HeapMultiBufMP_Handle, xdc_SizeT, xdc_SizeT, xdc_runtime_Error_Block*);
    xdc_Void (*free)(ti_sdo_ipc_heaps_HeapMultiBufMP_Handle, xdc_Ptr, xdc_SizeT);
    xdc_Bool (*isBlocking)(ti_sdo_ipc_heaps_HeapMultiBufMP_Handle);
    xdc_Void (*getStats)(ti_sdo_ipc_heaps_HeapMultiBufMP_Handle, xdc_runtime_Memory_Stats*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_heaps_HeapMultiBufMP_Fxns__ ti_sdo_ipc_heaps_HeapMultiBufMP_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_init__E, "ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_init")
__extern xdc_Int ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_init__E(ti_sdo_ipc_heaps_HeapMultiBufMP_Object *, const ti_sdo_ipc_heaps_HeapMultiBufMP_Params *, xdc_runtime_Error_Block *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_finalize__E, "ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_finalize")
__extern void ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_finalize__E( ti_sdo_ipc_heaps_HeapMultiBufMP_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_Handle__label__S, "ti_sdo_ipc_heaps_HeapMultiBufMP_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_heaps_HeapMultiBufMP_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_Module__startupDone__S, "ti_sdo_ipc_heaps_HeapMultiBufMP_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_heaps_HeapMultiBufMP_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_Object__create__S, "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_heaps_HeapMultiBufMP_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_create, "ti_sdo_ipc_heaps_HeapMultiBufMP_create")
__extern ti_sdo_ipc_heaps_HeapMultiBufMP_Handle ti_sdo_ipc_heaps_HeapMultiBufMP_create( const ti_sdo_ipc_heaps_HeapMultiBufMP_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_construct, "ti_sdo_ipc_heaps_HeapMultiBufMP_construct")
__extern void ti_sdo_ipc_heaps_HeapMultiBufMP_construct( ti_sdo_ipc_heaps_HeapMultiBufMP_Struct *__obj, const ti_sdo_ipc_heaps_HeapMultiBufMP_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_Object__delete__S, "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMultiBufMP_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_delete, "ti_sdo_ipc_heaps_HeapMultiBufMP_delete")
__extern void ti_sdo_ipc_heaps_HeapMultiBufMP_delete(ti_sdo_ipc_heaps_HeapMultiBufMP_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_Object__destruct__S, "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMultiBufMP_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_destruct, "ti_sdo_ipc_heaps_HeapMultiBufMP_destruct")
__extern void ti_sdo_ipc_heaps_HeapMultiBufMP_destruct(ti_sdo_ipc_heaps_HeapMultiBufMP_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_Object__get__S, "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_heaps_HeapMultiBufMP_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_Object__first__S, "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_heaps_HeapMultiBufMP_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_Object__next__S, "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_heaps_HeapMultiBufMP_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_Params__init__S, "ti_sdo_ipc_heaps_HeapMultiBufMP_Params__init__S")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMultiBufMP_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* isBlocking__E */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_isBlocking ti_sdo_ipc_heaps_HeapMultiBufMP_isBlocking__E
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_isBlocking__E, "ti_sdo_ipc_heaps_HeapMultiBufMP_isBlocking")
__extern xdc_Bool ti_sdo_ipc_heaps_HeapMultiBufMP_isBlocking__E( ti_sdo_ipc_heaps_HeapMultiBufMP_Handle __inst );

/* getStats__E */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_getStats ti_sdo_ipc_heaps_HeapMultiBufMP_getStats__E
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_getStats__E, "ti_sdo_ipc_heaps_HeapMultiBufMP_getStats")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMultiBufMP_getStats__E( ti_sdo_ipc_heaps_HeapMultiBufMP_Handle __inst, xdc_runtime_Memory_Stats *stats );

/* alloc__E */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_alloc ti_sdo_ipc_heaps_HeapMultiBufMP_alloc__E
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_alloc__E, "ti_sdo_ipc_heaps_HeapMultiBufMP_alloc")
__extern xdc_Ptr ti_sdo_ipc_heaps_HeapMultiBufMP_alloc__E( ti_sdo_ipc_heaps_HeapMultiBufMP_Handle __inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block *eb );

/* free__E */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_free ti_sdo_ipc_heaps_HeapMultiBufMP_free__E
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_free__E, "ti_sdo_ipc_heaps_HeapMultiBufMP_free")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMultiBufMP_free__E( ti_sdo_ipc_heaps_HeapMultiBufMP_Handle __inst, xdc_Ptr block, xdc_SizeT size );

/* postInit__I */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_postInit ti_sdo_ipc_heaps_HeapMultiBufMP_postInit__I
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_postInit__I, "ti_sdo_ipc_heaps_HeapMultiBufMP_postInit")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMultiBufMP_postInit__I( ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj, xdc_runtime_Error_Block *eb );

/* processBuckets__I */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_processBuckets ti_sdo_ipc_heaps_HeapMultiBufMP_processBuckets__I
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_processBuckets__I, "ti_sdo_ipc_heaps_HeapMultiBufMP_processBuckets")
__extern xdc_UInt ti_sdo_ipc_heaps_HeapMultiBufMP_processBuckets__I( ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket *bucketEntries, ti_sdo_ipc_heaps_HeapMultiBufMP_Params *params, xdc_UInt16 regionId );

/* putTail__I */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_putTail ti_sdo_ipc_heaps_HeapMultiBufMP_putTail__I
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_putTail__I, "ti_sdo_ipc_heaps_HeapMultiBufMP_putTail")
__extern xdc_Void ti_sdo_ipc_heaps_HeapMultiBufMP_putTail__I( ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj, xdc_Int index, ti_sdo_ipc_heaps_HeapMultiBufMP_Elem *block );

/* getHead__I */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_getHead ti_sdo_ipc_heaps_HeapMultiBufMP_getHead__I
xdc__CODESECT(ti_sdo_ipc_heaps_HeapMultiBufMP_getHead__I, "ti_sdo_ipc_heaps_HeapMultiBufMP_getHead")
__extern ti_sdo_ipc_heaps_HeapMultiBufMP_Elem *ti_sdo_ipc_heaps_HeapMultiBufMP_getHead__I( ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj, xdc_Int index );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_IHeap_Module ti_sdo_ipc_heaps_HeapMultiBufMP_Module_upCast( void )
{
    return (xdc_runtime_IHeap_Module)&ti_sdo_ipc_heaps_HeapMultiBufMP_Module__FXNS__C;
}

/* Module_to_xdc_runtime_IHeap */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_Module_to_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMultiBufMP_Module_upCast

/* Handle_upCast */
static inline xdc_runtime_IHeap_Handle ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_upCast( ti_sdo_ipc_heaps_HeapMultiBufMP_Handle i )
{
    return (xdc_runtime_IHeap_Handle)i;
}

/* Handle_to_xdc_runtime_IHeap */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_to_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_heaps_HeapMultiBufMP_Handle ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_downCast( xdc_runtime_IHeap_Handle i )
{
    xdc_runtime_IHeap_Handle i2 = (xdc_runtime_IHeap_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_heaps_HeapMultiBufMP_Module__FXNS__C ? (ti_sdo_ipc_heaps_HeapMultiBufMP_Handle)i : (ti_sdo_ipc_heaps_HeapMultiBufMP_Handle)0;
}

/* Handle_from_xdc_runtime_IHeap */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_from_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_Module_startupDone() ti_sdo_ipc_heaps_HeapMultiBufMP_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_Object_heap() ti_sdo_ipc_heaps_HeapMultiBufMP_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_Module_heap() ti_sdo_ipc_heaps_HeapMultiBufMP_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_heaps_HeapMultiBufMP_Module__id ti_sdo_ipc_heaps_HeapMultiBufMP_Module_id( void ) 
{
    return ti_sdo_ipc_heaps_HeapMultiBufMP_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_heaps_HeapMultiBufMP_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_heaps_HeapMultiBufMP_Module_getMask( void ) 
{
    return ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsMask__C != NULL ? *ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_heaps_HeapMultiBufMP_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_heaps_HeapMultiBufMP_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_heaps_HeapMultiBufMP_Params_init( ti_sdo_ipc_heaps_HeapMultiBufMP_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_heaps_HeapMultiBufMP_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_heaps_HeapMultiBufMP_Params_copy(ti_sdo_ipc_heaps_HeapMultiBufMP_Params *dst, const ti_sdo_ipc_heaps_HeapMultiBufMP_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_heaps_HeapMultiBufMP_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_Object_count() ti_sdo_ipc_heaps_HeapMultiBufMP_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_heaps_HeapMultiBufMP_Object_sizeof() ti_sdo_ipc_heaps_HeapMultiBufMP_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_heaps_HeapMultiBufMP_Handle ti_sdo_ipc_heaps_HeapMultiBufMP_Object_get(ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_heaps_HeapMultiBufMP_Handle)ti_sdo_ipc_heaps_HeapMultiBufMP_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_heaps_HeapMultiBufMP_Handle ti_sdo_ipc_heaps_HeapMultiBufMP_Object_first( void )
{
    return (ti_sdo_ipc_heaps_HeapMultiBufMP_Handle)ti_sdo_ipc_heaps_HeapMultiBufMP_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_heaps_HeapMultiBufMP_Handle ti_sdo_ipc_heaps_HeapMultiBufMP_Object_next( ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj )
{
    return (ti_sdo_ipc_heaps_HeapMultiBufMP_Handle)ti_sdo_ipc_heaps_HeapMultiBufMP_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_label( ti_sdo_ipc_heaps_HeapMultiBufMP_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_heaps_HeapMultiBufMP_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_name( ti_sdo_ipc_heaps_HeapMultiBufMP_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_heaps_HeapMultiBufMP_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_heaps_HeapMultiBufMP_Handle ti_sdo_ipc_heaps_HeapMultiBufMP_handle( ti_sdo_ipc_heaps_HeapMultiBufMP_Struct *str )
{
    return (ti_sdo_ipc_heaps_HeapMultiBufMP_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_heaps_HeapMultiBufMP_Struct *ti_sdo_ipc_heaps_HeapMultiBufMP_struct( ti_sdo_ipc_heaps_HeapMultiBufMP_Handle inst )
{
    return (ti_sdo_ipc_heaps_HeapMultiBufMP_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_heaps_HeapMultiBufMP__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_heaps_HeapMultiBufMP__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_heaps_HeapMultiBufMP__internalaccess))

#ifndef ti_sdo_ipc_heaps_HeapMultiBufMP__include_state
#define ti_sdo_ipc_heaps_HeapMultiBufMP__include_state

/* Module_State */
struct ti_sdo_ipc_heaps_HeapMultiBufMP_Module_State {
    ti_sdo_utils_NameServer_Handle nameServer;
};

/* Module__state__V */
extern struct ti_sdo_ipc_heaps_HeapMultiBufMP_Module_State__ ti_sdo_ipc_heaps_HeapMultiBufMP_Module__state__V;

/* Object */
struct ti_sdo_ipc_heaps_HeapMultiBufMP_Object {
    const ti_sdo_ipc_heaps_HeapMultiBufMP_Fxns__ *__fxns;
    ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs *attrs;
    ti_sdo_ipc_GateMP_Handle gate;
    ti_sdo_ipc_Ipc_ObjType objType;
    xdc_Ptr nsKey;
    xdc_Bool cacheEnabled;
    xdc_UInt16 regionId;
    xdc_SizeT allocSize;
    xdc_Char *buf;
    __TA_ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_State__bucketEntries bucketEntries;
    xdc_UInt numBuckets;
    xdc_Bool exact;
};

#endif /* ti_sdo_ipc_heaps_HeapMultiBufMP__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_heaps_HeapMultiBufMP__nolocalnames)

#ifndef ti_sdo_ipc_heaps_HeapMultiBufMP__localnames__done
#define ti_sdo_ipc_heaps_HeapMultiBufMP__localnames__done

/* module prefix */
#define HeapMultiBufMP_Instance ti_sdo_ipc_heaps_HeapMultiBufMP_Instance
#define HeapMultiBufMP_Handle ti_sdo_ipc_heaps_HeapMultiBufMP_Handle
#define HeapMultiBufMP_Module ti_sdo_ipc_heaps_HeapMultiBufMP_Module
#define HeapMultiBufMP_Object ti_sdo_ipc_heaps_HeapMultiBufMP_Object
#define HeapMultiBufMP_Struct ti_sdo_ipc_heaps_HeapMultiBufMP_Struct
#define HeapMultiBufMP_Bucket ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket
#define HeapMultiBufMP_ExtendedStats ti_sdo_ipc_heaps_HeapMultiBufMP_ExtendedStats
#define HeapMultiBufMP_CREATED ti_sdo_ipc_heaps_HeapMultiBufMP_CREATED
#define HeapMultiBufMP_Elem ti_sdo_ipc_heaps_HeapMultiBufMP_Elem
#define HeapMultiBufMP_BucketAttrs ti_sdo_ipc_heaps_HeapMultiBufMP_BucketAttrs
#define HeapMultiBufMP_Attrs ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs
#define HeapMultiBufMP_Instance_State ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_State
#define HeapMultiBufMP_Module_State ti_sdo_ipc_heaps_HeapMultiBufMP_Module_State
#define HeapMultiBufMP_A_invalidAlign ti_sdo_ipc_heaps_HeapMultiBufMP_A_invalidAlign
#define HeapMultiBufMP_A_sizeNotFound ti_sdo_ipc_heaps_HeapMultiBufMP_A_sizeNotFound
#define HeapMultiBufMP_A_addrNotFound ti_sdo_ipc_heaps_HeapMultiBufMP_A_addrNotFound
#define HeapMultiBufMP_E_exactFail ti_sdo_ipc_heaps_HeapMultiBufMP_E_exactFail
#define HeapMultiBufMP_E_size ti_sdo_ipc_heaps_HeapMultiBufMP_E_size
#define HeapMultiBufMP_E_noBlocksLeft ti_sdo_ipc_heaps_HeapMultiBufMP_E_noBlocksLeft
#define HeapMultiBufMP_maxNameLen ti_sdo_ipc_heaps_HeapMultiBufMP_maxNameLen
#define HeapMultiBufMP_trackMaxAllocs ti_sdo_ipc_heaps_HeapMultiBufMP_trackMaxAllocs
#define HeapMultiBufMP_Params ti_sdo_ipc_heaps_HeapMultiBufMP_Params
#define HeapMultiBufMP_isBlocking ti_sdo_ipc_heaps_HeapMultiBufMP_isBlocking
#define HeapMultiBufMP_getStats ti_sdo_ipc_heaps_HeapMultiBufMP_getStats
#define HeapMultiBufMP_alloc ti_sdo_ipc_heaps_HeapMultiBufMP_alloc
#define HeapMultiBufMP_free ti_sdo_ipc_heaps_HeapMultiBufMP_free
#define HeapMultiBufMP_Module_name ti_sdo_ipc_heaps_HeapMultiBufMP_Module_name
#define HeapMultiBufMP_Module_id ti_sdo_ipc_heaps_HeapMultiBufMP_Module_id
#define HeapMultiBufMP_Module_startup ti_sdo_ipc_heaps_HeapMultiBufMP_Module_startup
#define HeapMultiBufMP_Module_startupDone ti_sdo_ipc_heaps_HeapMultiBufMP_Module_startupDone
#define HeapMultiBufMP_Module_hasMask ti_sdo_ipc_heaps_HeapMultiBufMP_Module_hasMask
#define HeapMultiBufMP_Module_getMask ti_sdo_ipc_heaps_HeapMultiBufMP_Module_getMask
#define HeapMultiBufMP_Module_setMask ti_sdo_ipc_heaps_HeapMultiBufMP_Module_setMask
#define HeapMultiBufMP_Object_heap ti_sdo_ipc_heaps_HeapMultiBufMP_Object_heap
#define HeapMultiBufMP_Module_heap ti_sdo_ipc_heaps_HeapMultiBufMP_Module_heap
#define HeapMultiBufMP_construct ti_sdo_ipc_heaps_HeapMultiBufMP_construct
#define HeapMultiBufMP_create ti_sdo_ipc_heaps_HeapMultiBufMP_create
#define HeapMultiBufMP_handle ti_sdo_ipc_heaps_HeapMultiBufMP_handle
#define HeapMultiBufMP_struct ti_sdo_ipc_heaps_HeapMultiBufMP_struct
#define HeapMultiBufMP_Handle_label ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_label
#define HeapMultiBufMP_Handle_name ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_name
#define HeapMultiBufMP_Instance_init ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_init
#define HeapMultiBufMP_Object_count ti_sdo_ipc_heaps_HeapMultiBufMP_Object_count
#define HeapMultiBufMP_Object_get ti_sdo_ipc_heaps_HeapMultiBufMP_Object_get
#define HeapMultiBufMP_Object_first ti_sdo_ipc_heaps_HeapMultiBufMP_Object_first
#define HeapMultiBufMP_Object_next ti_sdo_ipc_heaps_HeapMultiBufMP_Object_next
#define HeapMultiBufMP_Object_sizeof ti_sdo_ipc_heaps_HeapMultiBufMP_Object_sizeof
#define HeapMultiBufMP_Params_copy ti_sdo_ipc_heaps_HeapMultiBufMP_Params_copy
#define HeapMultiBufMP_Params_init ti_sdo_ipc_heaps_HeapMultiBufMP_Params_init
#define HeapMultiBufMP_Instance_finalize ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_finalize
#define HeapMultiBufMP_delete ti_sdo_ipc_heaps_HeapMultiBufMP_delete
#define HeapMultiBufMP_destruct ti_sdo_ipc_heaps_HeapMultiBufMP_destruct
#define HeapMultiBufMP_Module_upCast ti_sdo_ipc_heaps_HeapMultiBufMP_Module_upCast
#define HeapMultiBufMP_Module_to_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMultiBufMP_Module_to_xdc_runtime_IHeap
#define HeapMultiBufMP_Handle_upCast ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_upCast
#define HeapMultiBufMP_Handle_to_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_to_xdc_runtime_IHeap
#define HeapMultiBufMP_Handle_downCast ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_downCast
#define HeapMultiBufMP_Handle_from_xdc_runtime_IHeap ti_sdo_ipc_heaps_HeapMultiBufMP_Handle_from_xdc_runtime_IHeap

#endif /* ti_sdo_ipc_heaps_HeapMultiBufMP__localnames__done */
#endif
