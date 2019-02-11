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

#ifndef ti_sdo_ipc_family_vayu_NotifyDriverMbx__include
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ipc_family_vayu_NotifyDriverMbx___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/sdo/ipc/family/vayu/package/package.defs.h>

#include <ti/sdo/utils/MultiProc.h>
#include <ti/sdo/ipc/interfaces/INotifyDriver.h>
#include <ti/sdo/ipc/Notify.h>
#include <ti/sysbios/hal/Hwi.h>
#include <xdc/runtime/Assert.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* NUM_CORES */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_NUM_CORES (11)

/* NUM_EVES */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_NUM_EVES (4)

/* NUM_EVE_MBX */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_NUM_EVE_MBX (12)

/* NUM_SYS_MBX */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_NUM_SYS_MBX (4)

/* Module_State */
typedef ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle __T1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_State__drvHandles;
typedef ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle __ARRAY1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_State__drvHandles[11];
typedef __ARRAY1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_State__drvHandles __TA_ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_State__drvHandles;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsEnabled ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsIncluded ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsMask ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__gateObj ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__gatePrms ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__id;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__id ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerDefined ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerObj ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn0 ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn1 ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn2 ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn4 ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn8 ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__startupDoneFxn ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__count;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__count ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__heap;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__heap ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__sizeof ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__table;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__table ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__table__C;

/* A_notSupported */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_A_notSupported (ti_sdo_ipc_family_vayu_NotifyDriverMbx_A_notSupported__C)
typedef xdc_runtime_Assert_Id CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_A_notSupported;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_A_notSupported ti_sdo_ipc_family_vayu_NotifyDriverMbx_A_notSupported__C;

/* mailboxTable */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxTable (ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxTable__C)
typedef xdc_UInt32 __T1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxTable;
typedef xdc_UInt32 __ARRAY1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxTable[11 * 11];
typedef __ARRAY1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxTable __TA_ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxTable;
typedef __TA_ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxTable CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxTable;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxTable ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxTable__C;

/* mailboxBaseAddr */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxBaseAddr (ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxBaseAddr__C)
typedef xdc_UInt32 __T1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxBaseAddr;
typedef xdc_UInt32 __ARRAY1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxBaseAddr[12 + 4];
typedef __ARRAY1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxBaseAddr __TA_ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxBaseAddr;
typedef __TA_ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxBaseAddr CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxBaseAddr;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxBaseAddr ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxBaseAddr__C;

/* procIdTable */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_procIdTable (ti_sdo_ipc_family_vayu_NotifyDriverMbx_procIdTable__C)
typedef xdc_UInt32 __T1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_procIdTable;
typedef xdc_UInt32 __ARRAY1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_procIdTable[11];
typedef __ARRAY1_ti_sdo_ipc_family_vayu_NotifyDriverMbx_procIdTable __TA_ti_sdo_ipc_family_vayu_NotifyDriverMbx_procIdTable;
typedef __TA_ti_sdo_ipc_family_vayu_NotifyDriverMbx_procIdTable CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_procIdTable;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_procIdTable ti_sdo_ipc_family_vayu_NotifyDriverMbx_procIdTable__C;

/* eve1ProcId */
#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve1ProcId__D
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve1ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve1ProcId__D)
#else
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve1ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve1ProcId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve1ProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve1ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve1ProcId__C;
#endif

/* eve2ProcId */
#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve2ProcId__D
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve2ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve2ProcId__D)
#else
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve2ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve2ProcId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve2ProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve2ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve2ProcId__C;
#endif

/* eve3ProcId */
#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve3ProcId__D
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve3ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve3ProcId__D)
#else
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve3ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve3ProcId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve3ProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve3ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve3ProcId__C;
#endif

/* eve4ProcId */
#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve4ProcId__D
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve4ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve4ProcId__D)
#else
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve4ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve4ProcId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve4ProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve4ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve4ProcId__C;
#endif

/* dsp1ProcId */
#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp1ProcId__D
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp1ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp1ProcId__D)
#else
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp1ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp1ProcId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp1ProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp1ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp1ProcId__C;
#endif

/* dsp2ProcId */
#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp2ProcId__D
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp2ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp2ProcId__D)
#else
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp2ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp2ProcId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp2ProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp2ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp2ProcId__C;
#endif

/* ipu1_0ProcId */
#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_0ProcId__D
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_0ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_0ProcId__D)
#else
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_0ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_0ProcId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_0ProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_0ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_0ProcId__C;
#endif

/* ipu2_0ProcId */
#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_0ProcId__D
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_0ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_0ProcId__D)
#else
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_0ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_0ProcId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_0ProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_0ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_0ProcId__C;
#endif

/* hostProcId */
#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx_hostProcId__D
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_hostProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_hostProcId__D)
#else
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_hostProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_hostProcId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_hostProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_hostProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_hostProcId__C;
#endif

/* ipu1_1ProcId */
#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_1ProcId__D
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_1ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_1ProcId__D)
#else
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_1ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_1ProcId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_1ProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_1ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_1ProcId__C;
#endif

/* ipu2_1ProcId */
#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_1ProcId__D
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_1ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_1ProcId__D)
#else
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_1ProcId (ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_1ProcId__C)
typedef xdc_UInt CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_1ProcId;
__extern __FAR__ const CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_1ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_1ProcId__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_UInt16 remoteProcId;
    xdc_UInt intVectorId;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sdo_ipc_family_vayu_NotifyDriverMbx_Struct {
    const ti_sdo_ipc_family_vayu_NotifyDriverMbx_Fxns__ *__fxns;
    xdc_Bits32 __f0;
    ti_sdo_ipc_Notify_Handle __f1;
    xdc_UInt16 __f2;
    xdc_UInt16 __f3;
    xdc_Int __f4;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ipc_family_vayu_NotifyDriverMbx_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Void (*registerEvent)(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle, xdc_UInt32);
    xdc_Void (*unregisterEvent)(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle, xdc_UInt32);
    xdc_Int (*sendEvent)(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle, xdc_UInt32, xdc_UInt32, xdc_Bool);
    xdc_Void (*disable)(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle);
    xdc_Void (*enable)(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle);
    xdc_Void (*disableEvent)(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle, xdc_UInt32);
    xdc_Void (*enableEvent)(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle, xdc_UInt32);
    xdc_Void (*setNotifyHandle)(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle, xdc_Ptr);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ipc_family_vayu_NotifyDriverMbx_Fxns__ ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_startup ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_startup__E
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_startup__E, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_startup")
__extern xdc_Int ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_startup__F, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_startup")
__extern xdc_Int ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_startup__F( xdc_Int state );

/* Instance_init__E */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Instance_init__E, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Instance_init")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_Instance_init__E(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object *, const ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params *);

/* Instance_finalize__E */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Instance_finalize__E, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Instance_finalize")
__extern void ti_sdo_ipc_family_vayu_NotifyDriverMbx_Instance_finalize__E( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object* );

/* Handle__label__S */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle__label__S, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__startupDone__S, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__startupDone__S")
__extern xdc_Bool ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__create__S, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__create__S")
__extern xdc_Ptr ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_create, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_create")
__extern ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle ti_sdo_ipc_family_vayu_NotifyDriverMbx_create( const ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params *__prms, xdc_runtime_Error_Block *__eb );

/* construct */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_construct, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_construct")
__extern void ti_sdo_ipc_family_vayu_NotifyDriverMbx_construct( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Struct *__obj, const ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params *__prms );

/* Object__delete__S */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__delete__S, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__delete__S")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_delete, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_delete")
__extern void ti_sdo_ipc_family_vayu_NotifyDriverMbx_delete(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__destruct__S, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__destruct__S")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__destruct__S( xdc_Ptr objp );

/* destruct */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_destruct, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_destruct")
__extern void ti_sdo_ipc_family_vayu_NotifyDriverMbx_destruct(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Struct *obj);

/* Object__get__S */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__get__S, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__get__S")
__extern xdc_Ptr ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__first__S, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__first__S")
__extern xdc_Ptr ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__next__S, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__next__S")
__extern xdc_Ptr ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params__init__S, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params__init__S")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* registerEvent__E */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_registerEvent ti_sdo_ipc_family_vayu_NotifyDriverMbx_registerEvent__E
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_registerEvent__E, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_registerEvent")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_registerEvent__E( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle __inst, xdc_UInt32 eventId );

/* unregisterEvent__E */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_unregisterEvent ti_sdo_ipc_family_vayu_NotifyDriverMbx_unregisterEvent__E
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_unregisterEvent__E, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_unregisterEvent")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_unregisterEvent__E( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle __inst, xdc_UInt32 eventId );

/* sendEvent__E */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_sendEvent ti_sdo_ipc_family_vayu_NotifyDriverMbx_sendEvent__E
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_sendEvent__E, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_sendEvent")
__extern xdc_Int ti_sdo_ipc_family_vayu_NotifyDriverMbx_sendEvent__E( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle __inst, xdc_UInt32 eventId, xdc_UInt32 payload, xdc_Bool waitClear );

/* disable__E */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_disable ti_sdo_ipc_family_vayu_NotifyDriverMbx_disable__E
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_disable__E, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_disable")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_disable__E( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle __inst );

/* enable__E */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_enable ti_sdo_ipc_family_vayu_NotifyDriverMbx_enable__E
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_enable__E, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_enable")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_enable__E( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle __inst );

/* disableEvent__E */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_disableEvent ti_sdo_ipc_family_vayu_NotifyDriverMbx_disableEvent__E
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_disableEvent__E, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_disableEvent")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_disableEvent__E( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle __inst, xdc_UInt32 eventId );

/* enableEvent__E */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_enableEvent ti_sdo_ipc_family_vayu_NotifyDriverMbx_enableEvent__E
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_enableEvent__E, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_enableEvent")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_enableEvent__E( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle __inst, xdc_UInt32 eventId );

/* setNotifyHandle__E */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_setNotifyHandle ti_sdo_ipc_family_vayu_NotifyDriverMbx_setNotifyHandle__E
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_setNotifyHandle__E, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_setNotifyHandle")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_setNotifyHandle__E( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle __inst, xdc_Ptr driverHandle );

/* isr__I */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_isr ti_sdo_ipc_family_vayu_NotifyDriverMbx_isr__I
xdc__CODESECT(ti_sdo_ipc_family_vayu_NotifyDriverMbx_isr__I, "ti_sdo_ipc_family_vayu_NotifyDriverMbx_isr")
__extern xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_isr__I( xdc_UInt16 idx );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_INotifyDriver_Module ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_upCast( void )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_Module)&ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_INotifyDriver */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_to_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_upCast

/* Handle_upCast */
static inline ti_sdo_ipc_interfaces_INotifyDriver_Handle ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_upCast( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle i )
{
    return (ti_sdo_ipc_interfaces_INotifyDriver_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_INotifyDriver */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_to_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_upCast

/* Handle_downCast */
static inline ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_downCast( ti_sdo_ipc_interfaces_INotifyDriver_Handle i )
{
    ti_sdo_ipc_interfaces_INotifyDriver_Handle i2 = (ti_sdo_ipc_interfaces_INotifyDriver_Handle)i;
    return (const void*)i2->__fxns == (const void*)&ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__FXNS__C ? (ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle)i : (ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle)0;
}

/* Handle_from_ti_sdo_ipc_interfaces_INotifyDriver */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_from_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_startupDone() ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_heap() ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__heap__C

/* Module_heap */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_heap() ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__id ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_id( void ) 
{
    return ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_getMask( void ) 
{
    return ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsMask__C != NULL ? *ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsMask__C != NULL) {
        *ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params_init( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params *prms ) 
{
    if (prms) {
        ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params__init__S(prms, 0, sizeof(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params_copy(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params *dst, const ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params *src) 
{
    if (dst) {
        ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params__init__S(dst, (const void *)src, sizeof(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_count() ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__count__C

/* Object_sizeof */
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_sizeof() ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__sizeof__C

/* Object_get */
static inline ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_get(ti_sdo_ipc_family_vayu_NotifyDriverMbx_Instance_State *oarr, int i) 
{
    return (ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle)ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_first( void )
{
    return (ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle)ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__first__S();
}

/* Object_next */
static inline ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_next( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object *obj )
{
    return (ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle)ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_label( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle inst, xdc_runtime_Types_Label *lab )
{
    return ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_name( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle ti_sdo_ipc_family_vayu_NotifyDriverMbx_handle( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Struct *str )
{
    return (ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle)str;
}

/* struct */
static inline ti_sdo_ipc_family_vayu_NotifyDriverMbx_Struct *ti_sdo_ipc_family_vayu_NotifyDriverMbx_struct( ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle inst )
{
    return (ti_sdo_ipc_family_vayu_NotifyDriverMbx_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ipc_family_vayu_NotifyDriverMbx__top__
#undef __nested__
#endif

#endif /* ti_sdo_ipc_family_vayu_NotifyDriverMbx__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ipc_family_vayu_NotifyDriverMbx__internalaccess))

#ifndef ti_sdo_ipc_family_vayu_NotifyDriverMbx__include_state
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx__include_state

/* Module_State */
struct ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_State {
    __TA_ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_State__drvHandles drvHandles;
};

/* Module__state__V */
extern struct ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_State__ ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module__state__V;

/* Object */
struct ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object {
    const ti_sdo_ipc_family_vayu_NotifyDriverMbx_Fxns__ *__fxns;
    xdc_Bits32 evtRegMask;
    ti_sdo_ipc_Notify_Handle notifyHandle;
    xdc_UInt16 remoteProcId;
    xdc_UInt16 remoteVirtId;
    xdc_Int cpuIntrNum;
};

#endif /* ti_sdo_ipc_family_vayu_NotifyDriverMbx__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ipc_family_vayu_NotifyDriverMbx__nolocalnames)

#ifndef ti_sdo_ipc_family_vayu_NotifyDriverMbx__localnames__done
#define ti_sdo_ipc_family_vayu_NotifyDriverMbx__localnames__done

/* module prefix */
#define NotifyDriverMbx_Instance ti_sdo_ipc_family_vayu_NotifyDriverMbx_Instance
#define NotifyDriverMbx_Handle ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle
#define NotifyDriverMbx_Module ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module
#define NotifyDriverMbx_Object ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object
#define NotifyDriverMbx_Struct ti_sdo_ipc_family_vayu_NotifyDriverMbx_Struct
#define NotifyDriverMbx_NUM_CORES ti_sdo_ipc_family_vayu_NotifyDriverMbx_NUM_CORES
#define NotifyDriverMbx_NUM_EVES ti_sdo_ipc_family_vayu_NotifyDriverMbx_NUM_EVES
#define NotifyDriverMbx_NUM_EVE_MBX ti_sdo_ipc_family_vayu_NotifyDriverMbx_NUM_EVE_MBX
#define NotifyDriverMbx_NUM_SYS_MBX ti_sdo_ipc_family_vayu_NotifyDriverMbx_NUM_SYS_MBX
#define NotifyDriverMbx_Instance_State ti_sdo_ipc_family_vayu_NotifyDriverMbx_Instance_State
#define NotifyDriverMbx_Module_State ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_State
#define NotifyDriverMbx_A_notSupported ti_sdo_ipc_family_vayu_NotifyDriverMbx_A_notSupported
#define NotifyDriverMbx_mailboxTable ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxTable
#define NotifyDriverMbx_mailboxBaseAddr ti_sdo_ipc_family_vayu_NotifyDriverMbx_mailboxBaseAddr
#define NotifyDriverMbx_procIdTable ti_sdo_ipc_family_vayu_NotifyDriverMbx_procIdTable
#define NotifyDriverMbx_eve1ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve1ProcId
#define NotifyDriverMbx_eve2ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve2ProcId
#define NotifyDriverMbx_eve3ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve3ProcId
#define NotifyDriverMbx_eve4ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_eve4ProcId
#define NotifyDriverMbx_dsp1ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp1ProcId
#define NotifyDriverMbx_dsp2ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_dsp2ProcId
#define NotifyDriverMbx_ipu1_0ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_0ProcId
#define NotifyDriverMbx_ipu2_0ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_0ProcId
#define NotifyDriverMbx_hostProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_hostProcId
#define NotifyDriverMbx_ipu1_1ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu1_1ProcId
#define NotifyDriverMbx_ipu2_1ProcId ti_sdo_ipc_family_vayu_NotifyDriverMbx_ipu2_1ProcId
#define NotifyDriverMbx_Params ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params
#define NotifyDriverMbx_registerEvent ti_sdo_ipc_family_vayu_NotifyDriverMbx_registerEvent
#define NotifyDriverMbx_unregisterEvent ti_sdo_ipc_family_vayu_NotifyDriverMbx_unregisterEvent
#define NotifyDriverMbx_sendEvent ti_sdo_ipc_family_vayu_NotifyDriverMbx_sendEvent
#define NotifyDriverMbx_disable ti_sdo_ipc_family_vayu_NotifyDriverMbx_disable
#define NotifyDriverMbx_enable ti_sdo_ipc_family_vayu_NotifyDriverMbx_enable
#define NotifyDriverMbx_disableEvent ti_sdo_ipc_family_vayu_NotifyDriverMbx_disableEvent
#define NotifyDriverMbx_enableEvent ti_sdo_ipc_family_vayu_NotifyDriverMbx_enableEvent
#define NotifyDriverMbx_setNotifyHandle ti_sdo_ipc_family_vayu_NotifyDriverMbx_setNotifyHandle
#define NotifyDriverMbx_Module_name ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_name
#define NotifyDriverMbx_Module_id ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_id
#define NotifyDriverMbx_Module_startup ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_startup
#define NotifyDriverMbx_Module_startupDone ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_startupDone
#define NotifyDriverMbx_Module_hasMask ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_hasMask
#define NotifyDriverMbx_Module_getMask ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_getMask
#define NotifyDriverMbx_Module_setMask ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_setMask
#define NotifyDriverMbx_Object_heap ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_heap
#define NotifyDriverMbx_Module_heap ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_heap
#define NotifyDriverMbx_construct ti_sdo_ipc_family_vayu_NotifyDriverMbx_construct
#define NotifyDriverMbx_create ti_sdo_ipc_family_vayu_NotifyDriverMbx_create
#define NotifyDriverMbx_handle ti_sdo_ipc_family_vayu_NotifyDriverMbx_handle
#define NotifyDriverMbx_struct ti_sdo_ipc_family_vayu_NotifyDriverMbx_struct
#define NotifyDriverMbx_Handle_label ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_label
#define NotifyDriverMbx_Handle_name ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_name
#define NotifyDriverMbx_Instance_init ti_sdo_ipc_family_vayu_NotifyDriverMbx_Instance_init
#define NotifyDriverMbx_Object_count ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_count
#define NotifyDriverMbx_Object_get ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_get
#define NotifyDriverMbx_Object_first ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_first
#define NotifyDriverMbx_Object_next ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_next
#define NotifyDriverMbx_Object_sizeof ti_sdo_ipc_family_vayu_NotifyDriverMbx_Object_sizeof
#define NotifyDriverMbx_Params_copy ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params_copy
#define NotifyDriverMbx_Params_init ti_sdo_ipc_family_vayu_NotifyDriverMbx_Params_init
#define NotifyDriverMbx_Instance_finalize ti_sdo_ipc_family_vayu_NotifyDriverMbx_Instance_finalize
#define NotifyDriverMbx_delete ti_sdo_ipc_family_vayu_NotifyDriverMbx_delete
#define NotifyDriverMbx_destruct ti_sdo_ipc_family_vayu_NotifyDriverMbx_destruct
#define NotifyDriverMbx_Module_upCast ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_upCast
#define NotifyDriverMbx_Module_to_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_family_vayu_NotifyDriverMbx_Module_to_ti_sdo_ipc_interfaces_INotifyDriver
#define NotifyDriverMbx_Handle_upCast ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_upCast
#define NotifyDriverMbx_Handle_to_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_to_ti_sdo_ipc_interfaces_INotifyDriver
#define NotifyDriverMbx_Handle_downCast ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_downCast
#define NotifyDriverMbx_Handle_from_ti_sdo_ipc_interfaces_INotifyDriver ti_sdo_ipc_family_vayu_NotifyDriverMbx_Handle_from_ti_sdo_ipc_interfaces_INotifyDriver

#endif /* ti_sdo_ipc_family_vayu_NotifyDriverMbx__localnames__done */
#endif
