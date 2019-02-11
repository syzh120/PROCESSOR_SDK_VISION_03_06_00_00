/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A71
 */

#ifndef ti_sysbios_family_arm_a15_smp_Core__INTERNAL__
#define ti_sysbios_family_arm_a15_smp_Core__INTERNAL__

#ifndef ti_sysbios_family_arm_a15_smp_Core__internalaccess
#define ti_sysbios_family_arm_a15_smp_Core__internalaccess
#endif

#include <ti/sysbios/family/arm/a15/smp/Core.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* getId */
#undef ti_sysbios_family_arm_a15_smp_Core_getId
#define ti_sysbios_family_arm_a15_smp_Core_getId ti_sysbios_family_arm_a15_smp_Core_getId__E

/* interruptCore */
#undef ti_sysbios_family_arm_a15_smp_Core_interruptCore
#define ti_sysbios_family_arm_a15_smp_Core_interruptCore ti_sysbios_family_arm_a15_smp_Core_interruptCore__E

/* lock */
#undef ti_sysbios_family_arm_a15_smp_Core_lock
#define ti_sysbios_family_arm_a15_smp_Core_lock ti_sysbios_family_arm_a15_smp_Core_lock__E

/* unlock */
#undef ti_sysbios_family_arm_a15_smp_Core_unlock
#define ti_sysbios_family_arm_a15_smp_Core_unlock ti_sysbios_family_arm_a15_smp_Core_unlock__E

/* getRevisionNumber */
#undef ti_sysbios_family_arm_a15_smp_Core_getRevisionNumber
#define ti_sysbios_family_arm_a15_smp_Core_getRevisionNumber ti_sysbios_family_arm_a15_smp_Core_getRevisionNumber__E

/* notifySpinLock */
#undef ti_sysbios_family_arm_a15_smp_Core_notifySpinLock
#define ti_sysbios_family_arm_a15_smp_Core_notifySpinLock ti_sysbios_family_arm_a15_smp_Core_notifySpinLock__E

/* notifySpinUnlock */
#undef ti_sysbios_family_arm_a15_smp_Core_notifySpinUnlock
#define ti_sysbios_family_arm_a15_smp_Core_notifySpinUnlock ti_sysbios_family_arm_a15_smp_Core_notifySpinUnlock__E

/* notify */
#undef ti_sysbios_family_arm_a15_smp_Core_notify
#define ti_sysbios_family_arm_a15_smp_Core_notify ti_sysbios_family_arm_a15_smp_Core_notify__E

/* enableActlrSmp */
#define Core_enableActlrSmp ti_sysbios_family_arm_a15_smp_Core_enableActlrSmp__I

/* resetOMAP5xxx */
#define Core_resetOMAP5xxx ti_sysbios_family_arm_a15_smp_Core_resetOMAP5xxx__I

/* resetKeystone2 */
#define Core_resetKeystone2 ti_sysbios_family_arm_a15_smp_Core_resetKeystone2__I

/* startCoreXOMAP5xxx */
#define Core_startCoreXOMAP5xxx ti_sysbios_family_arm_a15_smp_Core_startCoreXOMAP5xxx__I

/* startCoreXKeystone2 */
#define Core_startCoreXKeystone2 ti_sysbios_family_arm_a15_smp_Core_startCoreXKeystone2__I

/* exit */
#define Core_exit ti_sysbios_family_arm_a15_smp_Core_exit__I

/* hwiFunc */
#define Core_hwiFunc ti_sysbios_family_arm_a15_smp_Core_hwiFunc__I

/* skernelCmd */
#define Core_skernelCmd ti_sysbios_family_arm_a15_smp_Core_skernelCmd__I

/* smpBoot */
#define Core_smpBoot ti_sysbios_family_arm_a15_smp_Core_smpBoot__I

/* startup */
#define Core_startup ti_sysbios_family_arm_a15_smp_Core_startup__I

/* atexit */
#define Core_atexit ti_sysbios_family_arm_a15_smp_Core_atexit__I

/* Module_startup */
#undef ti_sysbios_family_arm_a15_smp_Core_Module_startup
#define ti_sysbios_family_arm_a15_smp_Core_Module_startup ti_sysbios_family_arm_a15_smp_Core_Module_startup__E

/* Instance_init */
#undef ti_sysbios_family_arm_a15_smp_Core_Instance_init
#define ti_sysbios_family_arm_a15_smp_Core_Instance_init ti_sysbios_family_arm_a15_smp_Core_Instance_init__E

/* Instance_finalize */
#undef ti_sysbios_family_arm_a15_smp_Core_Instance_finalize
#define ti_sysbios_family_arm_a15_smp_Core_Instance_finalize ti_sysbios_family_arm_a15_smp_Core_Instance_finalize__E

/* module */
#define Core_module ((ti_sysbios_family_arm_a15_smp_Core_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_arm_a15_smp_Core_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_sysbios_family_arm_a15_smp_Core__cplusplus)
#define module ((ti_sysbios_family_arm_a15_smp_Core_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_arm_a15_smp_Core_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sysbios_family_arm_a15_smp_Core_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sysbios_family_arm_a15_smp_Core_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sysbios_family_arm_a15_smp_Core_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sysbios_family_arm_a15_smp_Core_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sysbios_family_arm_a15_smp_Core_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sysbios_family_arm_a15_smp_Core_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sysbios_family_arm_a15_smp_Core_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sysbios_family_arm_a15_smp_Core_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sysbios_family_arm_a15_smp_Core_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sysbios_family_arm_a15_smp_Core_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sysbios_family_arm_a15_smp_Core_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sysbios_family_arm_a15_smp_Core_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sysbios_family_arm_a15_smp_Core_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sysbios_family_arm_a15_smp_Core_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sysbios_family_arm_a15_smp_Core_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sysbios_family_arm_a15_smp_Core_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sysbios_family_arm_a15_smp_Core_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sysbios_family_arm_a15_smp_Core_Module_GateProxy_query


#endif /* ti_sysbios_family_arm_a15_smp_Core__INTERNAL____ */
