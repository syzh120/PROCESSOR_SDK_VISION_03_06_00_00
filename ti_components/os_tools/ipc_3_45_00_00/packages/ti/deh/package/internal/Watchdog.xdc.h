/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B21
 */

#ifndef ti_deh_Watchdog__INTERNAL__
#define ti_deh_Watchdog__INTERNAL__

#ifndef ti_deh_Watchdog__internalaccess
#define ti_deh_Watchdog__internalaccess
#endif

#include <ti/deh/Watchdog.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* init */
#undef ti_deh_Watchdog_init
#define ti_deh_Watchdog_init ti_deh_Watchdog_init__F

/* idleBegin */
#undef ti_deh_Watchdog_idleBegin
#define ti_deh_Watchdog_idleBegin ti_deh_Watchdog_idleBegin__F

/* taskSwitch */
#undef ti_deh_Watchdog_taskSwitch
#define ti_deh_Watchdog_taskSwitch ti_deh_Watchdog_taskSwitch__F

/* swiPrehook */
#undef ti_deh_Watchdog_swiPrehook
#define ti_deh_Watchdog_swiPrehook ti_deh_Watchdog_swiPrehook__F

/* isException */
#undef ti_deh_Watchdog_isException
#define ti_deh_Watchdog_isException ti_deh_Watchdog_isException__F

/* stop */
#define Watchdog_stop ti_deh_Watchdog_stop__I

/* start */
#define Watchdog_start ti_deh_Watchdog_start__I

/* kick */
#define Watchdog_kick ti_deh_Watchdog_kick__I

/* restore */
#define Watchdog_restore ti_deh_Watchdog_restore__I

/* Module_startup */
#undef ti_deh_Watchdog_Module_startup
#define ti_deh_Watchdog_Module_startup ti_deh_Watchdog_Module_startup__E

/* Instance_init */
#undef ti_deh_Watchdog_Instance_init
#define ti_deh_Watchdog_Instance_init ti_deh_Watchdog_Instance_init__E

/* Instance_finalize */
#undef ti_deh_Watchdog_Instance_finalize
#define ti_deh_Watchdog_Instance_finalize ti_deh_Watchdog_Instance_finalize__E

/* module */
#define Watchdog_module ((ti_deh_Watchdog_Module_State *)(xdc__MODOBJADDR__(ti_deh_Watchdog_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_deh_Watchdog__cplusplus)
#define module ((ti_deh_Watchdog_Module_State *)(xdc__MODOBJADDR__(ti_deh_Watchdog_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_deh_Watchdog_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_deh_Watchdog_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_deh_Watchdog_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_deh_Watchdog_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_deh_Watchdog_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_deh_Watchdog_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_deh_Watchdog_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_deh_Watchdog_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_deh_Watchdog_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_deh_Watchdog_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_deh_Watchdog_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_deh_Watchdog_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_deh_Watchdog_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_deh_Watchdog_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_deh_Watchdog_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_deh_Watchdog_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_deh_Watchdog_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_deh_Watchdog_Module_GateProxy_query


#endif /* ti_deh_Watchdog__INTERNAL____ */
