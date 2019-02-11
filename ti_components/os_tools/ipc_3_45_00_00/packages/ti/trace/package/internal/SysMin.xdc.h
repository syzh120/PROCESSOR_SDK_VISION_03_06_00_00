/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B21
 */

#ifndef ti_trace_SysMin__INTERNAL__
#define ti_trace_SysMin__INTERNAL__

#ifndef ti_trace_SysMin__internalaccess
#define ti_trace_SysMin__internalaccess
#endif

#include <ti/trace/SysMin.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* abort */
#undef ti_trace_SysMin_abort
#define ti_trace_SysMin_abort ti_trace_SysMin_abort__E

/* exit */
#undef ti_trace_SysMin_exit
#define ti_trace_SysMin_exit ti_trace_SysMin_exit__E

/* flush */
#undef ti_trace_SysMin_flush
#define ti_trace_SysMin_flush ti_trace_SysMin_flush__E

/* putch */
#undef ti_trace_SysMin_putch
#define ti_trace_SysMin_putch ti_trace_SysMin_putch__E

/* ready */
#undef ti_trace_SysMin_ready
#define ti_trace_SysMin_ready ti_trace_SysMin_ready__E

/* Module_startup */
#undef ti_trace_SysMin_Module_startup
#define ti_trace_SysMin_Module_startup ti_trace_SysMin_Module_startup__E

/* Instance_init */
#undef ti_trace_SysMin_Instance_init
#define ti_trace_SysMin_Instance_init ti_trace_SysMin_Instance_init__E

/* Instance_finalize */
#undef ti_trace_SysMin_Instance_finalize
#define ti_trace_SysMin_Instance_finalize ti_trace_SysMin_Instance_finalize__E

/* module */
#define SysMin_module ((ti_trace_SysMin_Module_State *)(xdc__MODOBJADDR__(ti_trace_SysMin_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_trace_SysMin__cplusplus)
#define module ((ti_trace_SysMin_Module_State *)(xdc__MODOBJADDR__(ti_trace_SysMin_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_trace_SysMin_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_trace_SysMin_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_trace_SysMin_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_trace_SysMin_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_trace_SysMin_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_trace_SysMin_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_trace_SysMin_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_trace_SysMin_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_trace_SysMin_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_trace_SysMin_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_trace_SysMin_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_trace_SysMin_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_trace_SysMin_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_trace_SysMin_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_trace_SysMin_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_trace_SysMin_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_trace_SysMin_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_trace_SysMin_Module_GateProxy_query


#endif /* ti_trace_SysMin__INTERNAL____ */
