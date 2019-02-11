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

#ifndef ti_sysbios_family_shared_vayu_Mmu__include
#define ti_sysbios_family_shared_vayu_Mmu__include

#ifndef __nested__
#define __nested__
#define ti_sysbios_family_shared_vayu_Mmu__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sysbios_family_shared_vayu_Mmu___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sysbios/family/shared/vayu/package/package.defs.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* FirstLevelDesc */
enum ti_sysbios_family_shared_vayu_Mmu_FirstLevelDesc {
    ti_sysbios_family_shared_vayu_Mmu_FirstLevelDesc_FAULT = 0,
    ti_sysbios_family_shared_vayu_Mmu_FirstLevelDesc_PAGE_TABLE = 1,
    ti_sysbios_family_shared_vayu_Mmu_FirstLevelDesc_SECTION = 2
};
typedef enum ti_sysbios_family_shared_vayu_Mmu_FirstLevelDesc ti_sysbios_family_shared_vayu_Mmu_FirstLevelDesc;

/* PageSize */
enum ti_sysbios_family_shared_vayu_Mmu_PageSize {
    ti_sysbios_family_shared_vayu_Mmu_PageSize_SECTION = 0,
    ti_sysbios_family_shared_vayu_Mmu_PageSize_LARGE = 1,
    ti_sysbios_family_shared_vayu_Mmu_PageSize_SMALL = 2,
    ti_sysbios_family_shared_vayu_Mmu_PageSize_SUPERSECTION = 3
};
typedef enum ti_sysbios_family_shared_vayu_Mmu_PageSize ti_sysbios_family_shared_vayu_Mmu_PageSize;

/* FirstLevelDescAttrs */
struct ti_sysbios_family_shared_vayu_Mmu_FirstLevelDescAttrs {
    ti_sysbios_family_shared_vayu_Mmu_FirstLevelDesc type;
    xdc_Bool supersection;
};

/* Regs */
typedef xdc_UInt32 __T1_ti_sysbios_family_shared_vayu_Mmu_Regs__hole1;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_shared_vayu_Mmu_Regs__hole1[3];
typedef __ARRAY1_ti_sysbios_family_shared_vayu_Mmu_Regs__hole1 __TA_ti_sysbios_family_shared_vayu_Mmu_Regs__hole1;
typedef xdc_UInt32 __T1_ti_sysbios_family_shared_vayu_Mmu_Regs__hole2;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_shared_vayu_Mmu_Regs__hole2[8];
typedef __ARRAY1_ti_sysbios_family_shared_vayu_Mmu_Regs__hole2 __TA_ti_sysbios_family_shared_vayu_Mmu_Regs__hole2;
typedef xdc_UInt32 __T1_ti_sysbios_family_shared_vayu_Mmu_Regs__hole3;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_shared_vayu_Mmu_Regs__hole3[3];
typedef __ARRAY1_ti_sysbios_family_shared_vayu_Mmu_Regs__hole3 __TA_ti_sysbios_family_shared_vayu_Mmu_Regs__hole3;
struct ti_sysbios_family_shared_vayu_Mmu_Regs {
    xdc_UInt32 REVISION;
    __TA_ti_sysbios_family_shared_vayu_Mmu_Regs__hole1 hole1;
    xdc_UInt32 SYSCONFIG;
    xdc_UInt32 SYSSTATUS;
    xdc_UInt32 IRQSTATUS;
    xdc_UInt32 IRQENABLE;
    __TA_ti_sysbios_family_shared_vayu_Mmu_Regs__hole2 hole2;
    xdc_UInt32 WALKING_ST;
    xdc_UInt32 CNTL;
    xdc_UInt32 FAULT_AD;
    xdc_UInt32 TTB;
    xdc_UInt32 LOCK;
    xdc_UInt32 LD_TLB;
    xdc_UInt32 CAM;
    xdc_UInt32 RAM;
    xdc_UInt32 GFLUSH;
    xdc_UInt32 FLUSH_ENTRY;
    xdc_UInt32 READ_CAM;
    xdc_UInt32 READ_RAM;
    xdc_UInt32 EMU_FAULT_AD;
    __TA_ti_sysbios_family_shared_vayu_Mmu_Regs__hole3 hole3;
    xdc_UInt32 FAULT_PC;
    xdc_UInt32 FAULT_STATUS;
    xdc_UInt32 GPR;
    xdc_UInt32 BYPASS_REGION1_ADDR;
    xdc_UInt32 BYPASS_REGION1_SIZE;
    xdc_UInt32 BYPASS_REGION2_ADDR;
    xdc_UInt32 BYPASS_REGION2_SIZE;
    xdc_UInt32 BYPASS_REGION3_ADDR;
    xdc_UInt32 BYPASS_REGION3_SIZE;
    xdc_UInt32 BYPASS_REGION4_ADDR;
    xdc_UInt32 BYPASS_REGION4_SIZE;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* Module_State */
typedef xdc_UInt32 __T1_ti_sysbios_family_shared_vayu_Mmu_Module_State__tableBuf;
typedef xdc_UInt32 *__ARRAY1_ti_sysbios_family_shared_vayu_Mmu_Module_State__tableBuf;
typedef __ARRAY1_ti_sysbios_family_shared_vayu_Mmu_Module_State__tableBuf __TA_ti_sysbios_family_shared_vayu_Mmu_Module_State__tableBuf;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_family_shared_vayu_Mmu_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__diagsEnabled ti_sysbios_family_shared_vayu_Mmu_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_family_shared_vayu_Mmu_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__diagsIncluded ti_sysbios_family_shared_vayu_Mmu_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sysbios_family_shared_vayu_Mmu_Module__diagsMask;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__diagsMask ti_sysbios_family_shared_vayu_Mmu_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_family_shared_vayu_Mmu_Module__gateObj;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__gateObj ti_sysbios_family_shared_vayu_Mmu_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_family_shared_vayu_Mmu_Module__gatePrms;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__gatePrms ti_sysbios_family_shared_vayu_Mmu_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_family_shared_vayu_Mmu_Module__id;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__id ti_sysbios_family_shared_vayu_Mmu_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerDefined;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerDefined ti_sysbios_family_shared_vayu_Mmu_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerObj;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerObj ti_sysbios_family_shared_vayu_Mmu_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn0 ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn1 ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn2 ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn4 ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn8 ti_sysbios_family_shared_vayu_Mmu_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_family_shared_vayu_Mmu_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Module__startupDoneFxn ti_sysbios_family_shared_vayu_Mmu_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_family_shared_vayu_Mmu_Object__count;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Object__count ti_sysbios_family_shared_vayu_Mmu_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_family_shared_vayu_Mmu_Object__heap;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Object__heap ti_sysbios_family_shared_vayu_Mmu_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_family_shared_vayu_Mmu_Object__sizeof;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Object__sizeof ti_sysbios_family_shared_vayu_Mmu_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_family_shared_vayu_Mmu_Object__table;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_Object__table ti_sysbios_family_shared_vayu_Mmu_Object__table__C;

/* A_nullPointer */
#define ti_sysbios_family_shared_vayu_Mmu_A_nullPointer (ti_sysbios_family_shared_vayu_Mmu_A_nullPointer__C)
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_shared_vayu_Mmu_A_nullPointer;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_A_nullPointer ti_sysbios_family_shared_vayu_Mmu_A_nullPointer__C;

/* A_unknownDescType */
#define ti_sysbios_family_shared_vayu_Mmu_A_unknownDescType (ti_sysbios_family_shared_vayu_Mmu_A_unknownDescType__C)
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_shared_vayu_Mmu_A_unknownDescType;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_A_unknownDescType ti_sysbios_family_shared_vayu_Mmu_A_unknownDescType__C;

/* A_baseValueOutOfRange */
#define ti_sysbios_family_shared_vayu_Mmu_A_baseValueOutOfRange (ti_sysbios_family_shared_vayu_Mmu_A_baseValueOutOfRange__C)
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_shared_vayu_Mmu_A_baseValueOutOfRange;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_A_baseValueOutOfRange ti_sysbios_family_shared_vayu_Mmu_A_baseValueOutOfRange__C;

/* defaultAttrs */
#define ti_sysbios_family_shared_vayu_Mmu_defaultAttrs (ti_sysbios_family_shared_vayu_Mmu_defaultAttrs__C)
typedef ti_sysbios_family_shared_vayu_Mmu_FirstLevelDescAttrs CT__ti_sysbios_family_shared_vayu_Mmu_defaultAttrs;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_defaultAttrs ti_sysbios_family_shared_vayu_Mmu_defaultAttrs__C;

/* enableMMU */
#ifdef ti_sysbios_family_shared_vayu_Mmu_enableMMU__D
#define ti_sysbios_family_shared_vayu_Mmu_enableMMU (ti_sysbios_family_shared_vayu_Mmu_enableMMU__D)
#else
#define ti_sysbios_family_shared_vayu_Mmu_enableMMU (ti_sysbios_family_shared_vayu_Mmu_enableMMU__C)
typedef xdc_Bool CT__ti_sysbios_family_shared_vayu_Mmu_enableMMU;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_enableMMU ti_sysbios_family_shared_vayu_Mmu_enableMMU__C;
#endif

/* baseAddr */
#define ti_sysbios_family_shared_vayu_Mmu_baseAddr (ti_sysbios_family_shared_vayu_Mmu_baseAddr__C)
typedef ti_sysbios_family_shared_vayu_Mmu_Regs *CT__ti_sysbios_family_shared_vayu_Mmu_baseAddr;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_baseAddr ti_sysbios_family_shared_vayu_Mmu_baseAddr__C;

/* numTLBEntries */
#ifdef ti_sysbios_family_shared_vayu_Mmu_numTLBEntries__D
#define ti_sysbios_family_shared_vayu_Mmu_numTLBEntries (ti_sysbios_family_shared_vayu_Mmu_numTLBEntries__D)
#else
#define ti_sysbios_family_shared_vayu_Mmu_numTLBEntries (ti_sysbios_family_shared_vayu_Mmu_numTLBEntries__C)
typedef xdc_UInt CT__ti_sysbios_family_shared_vayu_Mmu_numTLBEntries;
__extern __FAR__ const CT__ti_sysbios_family_shared_vayu_Mmu_numTLBEntries ti_sysbios_family_shared_vayu_Mmu_numTLBEntries__C;
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sysbios_family_shared_vayu_Mmu_Module_startup ti_sysbios_family_shared_vayu_Mmu_Module_startup__E
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_Module_startup__E, "ti_sysbios_family_shared_vayu_Mmu_Module_startup")
__extern xdc_Int ti_sysbios_family_shared_vayu_Mmu_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_Module_startup__F, "ti_sysbios_family_shared_vayu_Mmu_Module_startup")
__extern xdc_Int ti_sysbios_family_shared_vayu_Mmu_Module_startup__F( xdc_Int state );

/* Module__startupDone__S */
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_Module__startupDone__S, "ti_sysbios_family_shared_vayu_Mmu_Module__startupDone__S")
__extern xdc_Bool ti_sysbios_family_shared_vayu_Mmu_Module__startupDone__S( void );

/* disable__E */
#define ti_sysbios_family_shared_vayu_Mmu_disable ti_sysbios_family_shared_vayu_Mmu_disable__E
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_disable__E, "ti_sysbios_family_shared_vayu_Mmu_disable")
__extern xdc_Void ti_sysbios_family_shared_vayu_Mmu_disable__E( void );

/* enable__E */
#define ti_sysbios_family_shared_vayu_Mmu_enable ti_sysbios_family_shared_vayu_Mmu_enable__E
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_enable__E, "ti_sysbios_family_shared_vayu_Mmu_enable")
__extern xdc_Void ti_sysbios_family_shared_vayu_Mmu_enable__E( void );

/* initDescAttrs__E */
#define ti_sysbios_family_shared_vayu_Mmu_initDescAttrs ti_sysbios_family_shared_vayu_Mmu_initDescAttrs__E
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_initDescAttrs__E, "ti_sysbios_family_shared_vayu_Mmu_initDescAttrs")
__extern xdc_Void ti_sysbios_family_shared_vayu_Mmu_initDescAttrs__E( ti_sysbios_family_shared_vayu_Mmu_FirstLevelDescAttrs *attrs );

/* isEnabled__E */
#define ti_sysbios_family_shared_vayu_Mmu_isEnabled ti_sysbios_family_shared_vayu_Mmu_isEnabled__E
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_isEnabled__E, "ti_sysbios_family_shared_vayu_Mmu_isEnabled")
__extern xdc_Bool ti_sysbios_family_shared_vayu_Mmu_isEnabled__E( void );

/* setFirstLevelDesc__E */
#define ti_sysbios_family_shared_vayu_Mmu_setFirstLevelDesc ti_sysbios_family_shared_vayu_Mmu_setFirstLevelDesc__E
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_setFirstLevelDesc__E, "ti_sysbios_family_shared_vayu_Mmu_setFirstLevelDesc")
__extern xdc_Void ti_sysbios_family_shared_vayu_Mmu_setFirstLevelDesc__E( xdc_Ptr virtualAddr, xdc_Ptr phyAddr, ti_sysbios_family_shared_vayu_Mmu_FirstLevelDescAttrs *attrs );

/* writeTLBEntry__E */
#define ti_sysbios_family_shared_vayu_Mmu_writeTLBEntry ti_sysbios_family_shared_vayu_Mmu_writeTLBEntry__E
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_writeTLBEntry__E, "ti_sysbios_family_shared_vayu_Mmu_writeTLBEntry")
__extern xdc_Bool ti_sysbios_family_shared_vayu_Mmu_writeTLBEntry__E( xdc_Ptr virtualAddr, xdc_Ptr physicalAddr, ti_sysbios_family_shared_vayu_Mmu_PageSize size );

/* clearTLBEntry__E */
#define ti_sysbios_family_shared_vayu_Mmu_clearTLBEntry ti_sysbios_family_shared_vayu_Mmu_clearTLBEntry__E
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_clearTLBEntry__E, "ti_sysbios_family_shared_vayu_Mmu_clearTLBEntry")
__extern xdc_Void ti_sysbios_family_shared_vayu_Mmu_clearTLBEntry__E( xdc_Ptr virtualAddr );

/* setTLBLockBaseValue__E */
#define ti_sysbios_family_shared_vayu_Mmu_setTLBLockBaseValue ti_sysbios_family_shared_vayu_Mmu_setTLBLockBaseValue__E
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_setTLBLockBaseValue__E, "ti_sysbios_family_shared_vayu_Mmu_setTLBLockBaseValue")
__extern xdc_Void ti_sysbios_family_shared_vayu_Mmu_setTLBLockBaseValue__E( xdc_UInt basevalue );

/* init__I */
#define ti_sysbios_family_shared_vayu_Mmu_init ti_sysbios_family_shared_vayu_Mmu_init__I
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_init__I, "ti_sysbios_family_shared_vayu_Mmu_init")
__extern xdc_Void ti_sysbios_family_shared_vayu_Mmu_init__I( void );

/* initTableBuf__I */
#define ti_sysbios_family_shared_vayu_Mmu_initTableBuf ti_sysbios_family_shared_vayu_Mmu_initTableBuf__I
xdc__CODESECT(ti_sysbios_family_shared_vayu_Mmu_initTableBuf__I, "ti_sysbios_family_shared_vayu_Mmu_initTableBuf")
__extern xdc_Void ti_sysbios_family_shared_vayu_Mmu_initTableBuf__I( xdc_UInt32 *mmuTableBuf );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sysbios_family_shared_vayu_Mmu_Module_startupDone() ti_sysbios_family_shared_vayu_Mmu_Module__startupDone__S()

/* Object_heap */
#define ti_sysbios_family_shared_vayu_Mmu_Object_heap() ti_sysbios_family_shared_vayu_Mmu_Object__heap__C

/* Module_heap */
#define ti_sysbios_family_shared_vayu_Mmu_Module_heap() ti_sysbios_family_shared_vayu_Mmu_Object__heap__C

/* Module_id */
static inline CT__ti_sysbios_family_shared_vayu_Mmu_Module__id ti_sysbios_family_shared_vayu_Mmu_Module_id( void ) 
{
    return ti_sysbios_family_shared_vayu_Mmu_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_family_shared_vayu_Mmu_Module_hasMask( void ) 
{
    return ti_sysbios_family_shared_vayu_Mmu_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_family_shared_vayu_Mmu_Module_getMask( void ) 
{
    return ti_sysbios_family_shared_vayu_Mmu_Module__diagsMask__C != NULL ? *ti_sysbios_family_shared_vayu_Mmu_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void ti_sysbios_family_shared_vayu_Mmu_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_family_shared_vayu_Mmu_Module__diagsMask__C != NULL) *ti_sysbios_family_shared_vayu_Mmu_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sysbios_family_shared_vayu_Mmu__top__
#undef __nested__
#endif

#endif /* ti_sysbios_family_shared_vayu_Mmu__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sysbios_family_shared_vayu_Mmu__internalaccess))

#ifndef ti_sysbios_family_shared_vayu_Mmu__include_state
#define ti_sysbios_family_shared_vayu_Mmu__include_state

/* Module_State */
struct ti_sysbios_family_shared_vayu_Mmu_Module_State {
    volatile ti_sysbios_family_shared_vayu_Mmu_Regs *regs;
    __TA_ti_sysbios_family_shared_vayu_Mmu_Module_State__tableBuf tableBuf;
};

/* Module__state__V */
extern struct ti_sysbios_family_shared_vayu_Mmu_Module_State__ ti_sysbios_family_shared_vayu_Mmu_Module__state__V;

#endif /* ti_sysbios_family_shared_vayu_Mmu__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sysbios_family_shared_vayu_Mmu__nolocalnames)

#ifndef ti_sysbios_family_shared_vayu_Mmu__localnames__done
#define ti_sysbios_family_shared_vayu_Mmu__localnames__done

/* module prefix */
#define Mmu_FirstLevelDesc ti_sysbios_family_shared_vayu_Mmu_FirstLevelDesc
#define Mmu_PageSize ti_sysbios_family_shared_vayu_Mmu_PageSize
#define Mmu_FirstLevelDescAttrs ti_sysbios_family_shared_vayu_Mmu_FirstLevelDescAttrs
#define Mmu_Regs ti_sysbios_family_shared_vayu_Mmu_Regs
#define Mmu_Module_State ti_sysbios_family_shared_vayu_Mmu_Module_State
#define Mmu_FirstLevelDesc_FAULT ti_sysbios_family_shared_vayu_Mmu_FirstLevelDesc_FAULT
#define Mmu_FirstLevelDesc_PAGE_TABLE ti_sysbios_family_shared_vayu_Mmu_FirstLevelDesc_PAGE_TABLE
#define Mmu_FirstLevelDesc_SECTION ti_sysbios_family_shared_vayu_Mmu_FirstLevelDesc_SECTION
#define Mmu_PageSize_SECTION ti_sysbios_family_shared_vayu_Mmu_PageSize_SECTION
#define Mmu_PageSize_LARGE ti_sysbios_family_shared_vayu_Mmu_PageSize_LARGE
#define Mmu_PageSize_SMALL ti_sysbios_family_shared_vayu_Mmu_PageSize_SMALL
#define Mmu_PageSize_SUPERSECTION ti_sysbios_family_shared_vayu_Mmu_PageSize_SUPERSECTION
#define Mmu_A_nullPointer ti_sysbios_family_shared_vayu_Mmu_A_nullPointer
#define Mmu_A_unknownDescType ti_sysbios_family_shared_vayu_Mmu_A_unknownDescType
#define Mmu_A_baseValueOutOfRange ti_sysbios_family_shared_vayu_Mmu_A_baseValueOutOfRange
#define Mmu_defaultAttrs ti_sysbios_family_shared_vayu_Mmu_defaultAttrs
#define Mmu_enableMMU ti_sysbios_family_shared_vayu_Mmu_enableMMU
#define Mmu_baseAddr ti_sysbios_family_shared_vayu_Mmu_baseAddr
#define Mmu_numTLBEntries ti_sysbios_family_shared_vayu_Mmu_numTLBEntries
#define Mmu_disable ti_sysbios_family_shared_vayu_Mmu_disable
#define Mmu_enable ti_sysbios_family_shared_vayu_Mmu_enable
#define Mmu_initDescAttrs ti_sysbios_family_shared_vayu_Mmu_initDescAttrs
#define Mmu_isEnabled ti_sysbios_family_shared_vayu_Mmu_isEnabled
#define Mmu_setFirstLevelDesc ti_sysbios_family_shared_vayu_Mmu_setFirstLevelDesc
#define Mmu_writeTLBEntry ti_sysbios_family_shared_vayu_Mmu_writeTLBEntry
#define Mmu_clearTLBEntry ti_sysbios_family_shared_vayu_Mmu_clearTLBEntry
#define Mmu_setTLBLockBaseValue ti_sysbios_family_shared_vayu_Mmu_setTLBLockBaseValue
#define Mmu_Module_name ti_sysbios_family_shared_vayu_Mmu_Module_name
#define Mmu_Module_id ti_sysbios_family_shared_vayu_Mmu_Module_id
#define Mmu_Module_startup ti_sysbios_family_shared_vayu_Mmu_Module_startup
#define Mmu_Module_startupDone ti_sysbios_family_shared_vayu_Mmu_Module_startupDone
#define Mmu_Module_hasMask ti_sysbios_family_shared_vayu_Mmu_Module_hasMask
#define Mmu_Module_getMask ti_sysbios_family_shared_vayu_Mmu_Module_getMask
#define Mmu_Module_setMask ti_sysbios_family_shared_vayu_Mmu_Module_setMask
#define Mmu_Object_heap ti_sysbios_family_shared_vayu_Mmu_Object_heap
#define Mmu_Module_heap ti_sysbios_family_shared_vayu_Mmu_Module_heap

#endif /* ti_sysbios_family_shared_vayu_Mmu__localnames__done */
#endif
