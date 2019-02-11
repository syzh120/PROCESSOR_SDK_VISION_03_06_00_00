/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B21
 */

#ifndef ti_deh_StackDbg__INTERNAL__
#define ti_deh_StackDbg__INTERNAL__

#ifndef ti_deh_StackDbg__internalaccess
#define ti_deh_StackDbg__internalaccess
#endif

#include <ti/deh/StackDbg.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* walkStack */
#undef ti_deh_StackDbg_walkStack
#define ti_deh_StackDbg_walkStack ti_deh_StackDbg_walkStack__F

/* Module_startup */
#undef ti_deh_StackDbg_Module_startup
#define ti_deh_StackDbg_Module_startup ti_deh_StackDbg_Module_startup__E

/* Instance_init */
#undef ti_deh_StackDbg_Instance_init
#define ti_deh_StackDbg_Instance_init ti_deh_StackDbg_Instance_init__E

/* Instance_finalize */
#undef ti_deh_StackDbg_Instance_finalize
#define ti_deh_StackDbg_Instance_finalize ti_deh_StackDbg_Instance_finalize__E

/* module */
#define StackDbg_module ((ti_deh_StackDbg_Module_State *)(xdc__MODOBJADDR__(ti_deh_StackDbg_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_deh_StackDbg__cplusplus)
#define module ((ti_deh_StackDbg_Module_State *)(xdc__MODOBJADDR__(ti_deh_StackDbg_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_deh_StackDbg_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_deh_StackDbg_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_deh_StackDbg_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_deh_StackDbg_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_deh_StackDbg_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_deh_StackDbg_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_deh_StackDbg_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_deh_StackDbg_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_deh_StackDbg_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_deh_StackDbg_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_deh_StackDbg_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_deh_StackDbg_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_deh_StackDbg_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_deh_StackDbg_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_deh_StackDbg_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_deh_StackDbg_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_deh_StackDbg_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_deh_StackDbg_Module_GateProxy_query


#endif /* ti_deh_StackDbg__INTERNAL____ */
