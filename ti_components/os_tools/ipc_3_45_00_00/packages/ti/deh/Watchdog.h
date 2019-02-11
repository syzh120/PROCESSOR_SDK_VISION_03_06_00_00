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

#ifndef ti_deh_Watchdog__include
#define ti_deh_Watchdog__include

#ifndef __nested__
#define __nested__
#define ti_deh_Watchdog__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_deh_Watchdog___VERS 160


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

/* TimerRegs */
typedef xdc_UInt __T1_ti_deh_Watchdog_TimerRegs__empty;
typedef xdc_UInt __ARRAY1_ti_deh_Watchdog_TimerRegs__empty[3];
typedef __ARRAY1_ti_deh_Watchdog_TimerRegs__empty __TA_ti_deh_Watchdog_TimerRegs__empty;
typedef xdc_UInt __T1_ti_deh_Watchdog_TimerRegs__empty1;
typedef xdc_UInt __ARRAY1_ti_deh_Watchdog_TimerRegs__empty1[3];
typedef __ARRAY1_ti_deh_Watchdog_TimerRegs__empty1 __TA_ti_deh_Watchdog_TimerRegs__empty1;
struct ti_deh_Watchdog_TimerRegs {
    xdc_UInt tidr;
    __TA_ti_deh_Watchdog_TimerRegs__empty empty;
    xdc_UInt tiocpCfg;
    __TA_ti_deh_Watchdog_TimerRegs__empty1 empty1;
    xdc_UInt irq_eoi;
    xdc_UInt irqstat_raw;
    xdc_UInt tisr;
    xdc_UInt tier;
    xdc_UInt irqen_clr;
    xdc_UInt twer;
    xdc_UInt tclr;
    xdc_Int tcrr;
    xdc_Int tldr;
    xdc_UInt ttgr;
    xdc_UInt twps;
    xdc_UInt tmar;
    xdc_UInt tcar1;
    xdc_UInt tsicr;
    xdc_UInt tcar2;
};

/* TimerDevice */
struct ti_deh_Watchdog_TimerDevice {
    xdc_Ptr baseAddr;
    xdc_Ptr clkCtrl;
    xdc_Int32 intNum;
    xdc_Int eventId;
};

/* Mode */
enum ti_deh_Watchdog_Mode {
    ti_deh_Watchdog_Mode_DISABLED,
    ti_deh_Watchdog_Mode_ENABLED
};
typedef enum ti_deh_Watchdog_Mode ti_deh_Watchdog_Mode;

/* TIME_SEC */
#define ti_deh_Watchdog_TIME_SEC (5)

/* BOOT_TIME_SEC */
#define ti_deh_Watchdog_BOOT_TIME_SEC (10)


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* Module_State */
typedef ti_deh_Watchdog_TimerDevice __T1_ti_deh_Watchdog_Module_State__device;
typedef ti_deh_Watchdog_TimerDevice *__ARRAY1_ti_deh_Watchdog_Module_State__device;
typedef __ARRAY1_ti_deh_Watchdog_Module_State__device __TA_ti_deh_Watchdog_Module_State__device;
typedef ti_deh_Watchdog_Mode __T1_ti_deh_Watchdog_Module_State__status;
typedef ti_deh_Watchdog_Mode *__ARRAY1_ti_deh_Watchdog_Module_State__status;
typedef __ARRAY1_ti_deh_Watchdog_Module_State__status __TA_ti_deh_Watchdog_Module_State__status;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_deh_Watchdog_Module__diagsEnabled;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__diagsEnabled ti_deh_Watchdog_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_deh_Watchdog_Module__diagsIncluded;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__diagsIncluded ti_deh_Watchdog_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_deh_Watchdog_Module__diagsMask;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__diagsMask ti_deh_Watchdog_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_deh_Watchdog_Module__gateObj;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__gateObj ti_deh_Watchdog_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_deh_Watchdog_Module__gatePrms;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__gatePrms ti_deh_Watchdog_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_deh_Watchdog_Module__id;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__id ti_deh_Watchdog_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_deh_Watchdog_Module__loggerDefined;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__loggerDefined ti_deh_Watchdog_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_deh_Watchdog_Module__loggerObj;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__loggerObj ti_deh_Watchdog_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_deh_Watchdog_Module__loggerFxn0;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__loggerFxn0 ti_deh_Watchdog_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_deh_Watchdog_Module__loggerFxn1;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__loggerFxn1 ti_deh_Watchdog_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_deh_Watchdog_Module__loggerFxn2;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__loggerFxn2 ti_deh_Watchdog_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_deh_Watchdog_Module__loggerFxn4;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__loggerFxn4 ti_deh_Watchdog_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_deh_Watchdog_Module__loggerFxn8;
__extern __FAR__ const CT__ti_deh_Watchdog_Module__loggerFxn8 ti_deh_Watchdog_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_deh_Watchdog_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_deh_Watchdog_Module__startupDoneFxn ti_deh_Watchdog_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_deh_Watchdog_Object__count;
__extern __FAR__ const CT__ti_deh_Watchdog_Object__count ti_deh_Watchdog_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_deh_Watchdog_Object__heap;
__extern __FAR__ const CT__ti_deh_Watchdog_Object__heap ti_deh_Watchdog_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_deh_Watchdog_Object__sizeof;
__extern __FAR__ const CT__ti_deh_Watchdog_Object__sizeof ti_deh_Watchdog_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_deh_Watchdog_Object__table;
__extern __FAR__ const CT__ti_deh_Watchdog_Object__table ti_deh_Watchdog_Object__table__C;

/* disableWatchdog */
#ifdef ti_deh_Watchdog_disableWatchdog__D
#define ti_deh_Watchdog_disableWatchdog (ti_deh_Watchdog_disableWatchdog__D)
#else
#define ti_deh_Watchdog_disableWatchdog (ti_deh_Watchdog_disableWatchdog__C)
typedef xdc_Bool CT__ti_deh_Watchdog_disableWatchdog;
__extern __FAR__ const CT__ti_deh_Watchdog_disableWatchdog ti_deh_Watchdog_disableWatchdog__C;
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_deh_Watchdog_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_deh_Watchdog_Module__startupDone__S, "ti_deh_Watchdog_Module__startupDone__S")
__extern xdc_Bool ti_deh_Watchdog_Module__startupDone__S( void );

/* init__E */
#define ti_deh_Watchdog_init ti_deh_Watchdog_init__E
xdc__CODESECT(ti_deh_Watchdog_init__E, "ti_deh_Watchdog_init")
__extern xdc_Void ti_deh_Watchdog_init__E( xdc_Void (*timerFxn)(xdc_Void) );
xdc__CODESECT(ti_deh_Watchdog_init__F, "ti_deh_Watchdog_init")
__extern xdc_Void ti_deh_Watchdog_init__F( xdc_Void (*timerFxn)(xdc_Void) );

/* idleBegin__E */
#define ti_deh_Watchdog_idleBegin ti_deh_Watchdog_idleBegin__E
xdc__CODESECT(ti_deh_Watchdog_idleBegin__E, "ti_deh_Watchdog_idleBegin")
__extern xdc_Void ti_deh_Watchdog_idleBegin__E( void );
xdc__CODESECT(ti_deh_Watchdog_idleBegin__F, "ti_deh_Watchdog_idleBegin")
__extern xdc_Void ti_deh_Watchdog_idleBegin__F( void );

/* taskSwitch__E */
#define ti_deh_Watchdog_taskSwitch ti_deh_Watchdog_taskSwitch__E
xdc__CODESECT(ti_deh_Watchdog_taskSwitch__E, "ti_deh_Watchdog_taskSwitch")
__extern xdc_Void ti_deh_Watchdog_taskSwitch__E( ti_sysbios_knl_Task_Handle p, ti_sysbios_knl_Task_Handle n );
xdc__CODESECT(ti_deh_Watchdog_taskSwitch__F, "ti_deh_Watchdog_taskSwitch")
__extern xdc_Void ti_deh_Watchdog_taskSwitch__F( ti_sysbios_knl_Task_Handle p, ti_sysbios_knl_Task_Handle n );

/* swiPrehook__E */
#define ti_deh_Watchdog_swiPrehook ti_deh_Watchdog_swiPrehook__E
xdc__CODESECT(ti_deh_Watchdog_swiPrehook__E, "ti_deh_Watchdog_swiPrehook")
__extern xdc_Void ti_deh_Watchdog_swiPrehook__E( ti_sysbios_knl_Swi_Handle swi );
xdc__CODESECT(ti_deh_Watchdog_swiPrehook__F, "ti_deh_Watchdog_swiPrehook")
__extern xdc_Void ti_deh_Watchdog_swiPrehook__F( ti_sysbios_knl_Swi_Handle swi );

/* isException__E */
#define ti_deh_Watchdog_isException ti_deh_Watchdog_isException__E
xdc__CODESECT(ti_deh_Watchdog_isException__E, "ti_deh_Watchdog_isException")
__extern xdc_Bool ti_deh_Watchdog_isException__E( xdc_UInt excNum );
xdc__CODESECT(ti_deh_Watchdog_isException__F, "ti_deh_Watchdog_isException")
__extern xdc_Bool ti_deh_Watchdog_isException__F( xdc_UInt excNum );

/* stop__I */
#define ti_deh_Watchdog_stop ti_deh_Watchdog_stop__I
xdc__CODESECT(ti_deh_Watchdog_stop__I, "ti_deh_Watchdog_stop")
__extern xdc_Void ti_deh_Watchdog_stop__I( xdc_Int core );

/* start__I */
#define ti_deh_Watchdog_start ti_deh_Watchdog_start__I
xdc__CODESECT(ti_deh_Watchdog_start__I, "ti_deh_Watchdog_start")
__extern xdc_Void ti_deh_Watchdog_start__I( xdc_Int core );

/* kick__I */
#define ti_deh_Watchdog_kick ti_deh_Watchdog_kick__I
xdc__CODESECT(ti_deh_Watchdog_kick__I, "ti_deh_Watchdog_kick")
__extern xdc_Void ti_deh_Watchdog_kick__I( xdc_Int core );

/* restore__I */
#define ti_deh_Watchdog_restore ti_deh_Watchdog_restore__I
xdc__CODESECT(ti_deh_Watchdog_restore__I, "ti_deh_Watchdog_restore")
__extern xdc_Void ti_deh_Watchdog_restore__I( xdc_Int event, xdc_Ptr data );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_deh_Watchdog_Module_startupDone() ti_deh_Watchdog_Module__startupDone__S()

/* Object_heap */
#define ti_deh_Watchdog_Object_heap() ti_deh_Watchdog_Object__heap__C

/* Module_heap */
#define ti_deh_Watchdog_Module_heap() ti_deh_Watchdog_Object__heap__C

/* Module_id */
static inline CT__ti_deh_Watchdog_Module__id ti_deh_Watchdog_Module_id( void ) 
{
    return ti_deh_Watchdog_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_deh_Watchdog_Module_hasMask( void ) 
{
    return (xdc_Bool)(ti_deh_Watchdog_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_deh_Watchdog_Module_getMask( void ) 
{
    return ti_deh_Watchdog_Module__diagsMask__C != NULL ? *ti_deh_Watchdog_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_deh_Watchdog_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_deh_Watchdog_Module__diagsMask__C != NULL) {
        *ti_deh_Watchdog_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_deh_Watchdog__top__
#undef __nested__
#endif

#endif /* ti_deh_Watchdog__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_deh_Watchdog__internalaccess))

#ifndef ti_deh_Watchdog__include_state
#define ti_deh_Watchdog__include_state

/* Module_State */
struct ti_deh_Watchdog_Module_State {
    __TA_ti_deh_Watchdog_Module_State__device device;
    __TA_ti_deh_Watchdog_Module_State__status status;
    xdc_Int wdtCores;
};

/* Module__state__V */
extern struct ti_deh_Watchdog_Module_State__ ti_deh_Watchdog_Module__state__V;

#endif /* ti_deh_Watchdog__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_deh_Watchdog__nolocalnames)

#ifndef ti_deh_Watchdog__localnames__done
#define ti_deh_Watchdog__localnames__done

/* module prefix */
#define Watchdog_TimerRegs ti_deh_Watchdog_TimerRegs
#define Watchdog_TimerDevice ti_deh_Watchdog_TimerDevice
#define Watchdog_Mode ti_deh_Watchdog_Mode
#define Watchdog_TIME_SEC ti_deh_Watchdog_TIME_SEC
#define Watchdog_BOOT_TIME_SEC ti_deh_Watchdog_BOOT_TIME_SEC
#define Watchdog_Module_State ti_deh_Watchdog_Module_State
#define Watchdog_Mode_DISABLED ti_deh_Watchdog_Mode_DISABLED
#define Watchdog_Mode_ENABLED ti_deh_Watchdog_Mode_ENABLED
#define Watchdog_disableWatchdog ti_deh_Watchdog_disableWatchdog
#define Watchdog_init ti_deh_Watchdog_init
#define Watchdog_idleBegin ti_deh_Watchdog_idleBegin
#define Watchdog_taskSwitch ti_deh_Watchdog_taskSwitch
#define Watchdog_swiPrehook ti_deh_Watchdog_swiPrehook
#define Watchdog_isException ti_deh_Watchdog_isException
#define Watchdog_Module_name ti_deh_Watchdog_Module_name
#define Watchdog_Module_id ti_deh_Watchdog_Module_id
#define Watchdog_Module_startup ti_deh_Watchdog_Module_startup
#define Watchdog_Module_startupDone ti_deh_Watchdog_Module_startupDone
#define Watchdog_Module_hasMask ti_deh_Watchdog_Module_hasMask
#define Watchdog_Module_getMask ti_deh_Watchdog_Module_getMask
#define Watchdog_Module_setMask ti_deh_Watchdog_Module_setMask
#define Watchdog_Object_heap ti_deh_Watchdog_Object_heap
#define Watchdog_Module_heap ti_deh_Watchdog_Module_heap

#endif /* ti_deh_Watchdog__localnames__done */
#endif
