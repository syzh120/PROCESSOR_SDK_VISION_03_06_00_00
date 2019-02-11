/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A71
 */

#ifndef ti_sysbios_family_arp32_Hwi__INTERNAL__
#define ti_sysbios_family_arp32_Hwi__INTERNAL__

#ifndef ti_sysbios_family_arp32_Hwi__internalaccess
#define ti_sysbios_family_arp32_Hwi__internalaccess
#endif

#include <ti/sysbios/family/arp32/Hwi.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* getStackInfo */
#undef ti_sysbios_family_arp32_Hwi_getStackInfo
#define ti_sysbios_family_arp32_Hwi_getStackInfo ti_sysbios_family_arp32_Hwi_getStackInfo__E

/* getCoreStackInfo */
#undef ti_sysbios_family_arp32_Hwi_getCoreStackInfo
#define ti_sysbios_family_arp32_Hwi_getCoreStackInfo ti_sysbios_family_arp32_Hwi_getCoreStackInfo__E

/* startup */
#undef ti_sysbios_family_arp32_Hwi_startup
#define ti_sysbios_family_arp32_Hwi_startup ti_sysbios_family_arp32_Hwi_startup__E

/* switchFromBootStack */
#undef ti_sysbios_family_arp32_Hwi_switchFromBootStack
#define ti_sysbios_family_arp32_Hwi_switchFromBootStack ti_sysbios_family_arp32_Hwi_switchFromBootStack__E

/* post */
#undef ti_sysbios_family_arp32_Hwi_post
#define ti_sysbios_family_arp32_Hwi_post ti_sysbios_family_arp32_Hwi_post__E

/* getTaskSP */
#undef ti_sysbios_family_arp32_Hwi_getTaskSP
#define ti_sysbios_family_arp32_Hwi_getTaskSP ti_sysbios_family_arp32_Hwi_getTaskSP__E

/* disableInterrupt */
#undef ti_sysbios_family_arp32_Hwi_disableInterrupt
#define ti_sysbios_family_arp32_Hwi_disableInterrupt ti_sysbios_family_arp32_Hwi_disableInterrupt__E

/* enableInterrupt */
#undef ti_sysbios_family_arp32_Hwi_enableInterrupt
#define ti_sysbios_family_arp32_Hwi_enableInterrupt ti_sysbios_family_arp32_Hwi_enableInterrupt__E

/* restoreInterrupt */
#undef ti_sysbios_family_arp32_Hwi_restoreInterrupt
#define ti_sysbios_family_arp32_Hwi_restoreInterrupt ti_sysbios_family_arp32_Hwi_restoreInterrupt__E

/* clearInterrupt */
#undef ti_sysbios_family_arp32_Hwi_clearInterrupt
#define ti_sysbios_family_arp32_Hwi_clearInterrupt ti_sysbios_family_arp32_Hwi_clearInterrupt__E

/* getFunc */
#undef ti_sysbios_family_arp32_Hwi_getFunc
#define ti_sysbios_family_arp32_Hwi_getFunc ti_sysbios_family_arp32_Hwi_getFunc__E

/* setFunc */
#undef ti_sysbios_family_arp32_Hwi_setFunc
#define ti_sysbios_family_arp32_Hwi_setFunc ti_sysbios_family_arp32_Hwi_setFunc__E

/* getHookContext */
#undef ti_sysbios_family_arp32_Hwi_getHookContext
#define ti_sysbios_family_arp32_Hwi_getHookContext ti_sysbios_family_arp32_Hwi_getHookContext__E

/* setHookContext */
#undef ti_sysbios_family_arp32_Hwi_setHookContext
#define ti_sysbios_family_arp32_Hwi_setHookContext ti_sysbios_family_arp32_Hwi_setHookContext__E

/* getIrp */
#undef ti_sysbios_family_arp32_Hwi_getIrp
#define ti_sysbios_family_arp32_Hwi_getIrp ti_sysbios_family_arp32_Hwi_getIrp__E

/* selfLoop */
#undef ti_sysbios_family_arp32_Hwi_selfLoop
#define ti_sysbios_family_arp32_Hwi_selfLoop ti_sysbios_family_arp32_Hwi_selfLoop__E

/* getHandle */
#undef ti_sysbios_family_arp32_Hwi_getHandle
#define ti_sysbios_family_arp32_Hwi_getHandle ti_sysbios_family_arp32_Hwi_getHandle__E

/* disableIER */
#undef ti_sysbios_family_arp32_Hwi_disableIER
#define ti_sysbios_family_arp32_Hwi_disableIER ti_sysbios_family_arp32_Hwi_disableIER__E

/* enableIER */
#undef ti_sysbios_family_arp32_Hwi_enableIER
#define ti_sysbios_family_arp32_Hwi_enableIER ti_sysbios_family_arp32_Hwi_enableIER__E

/* restoreIER */
#undef ti_sysbios_family_arp32_Hwi_restoreIER
#define ti_sysbios_family_arp32_Hwi_restoreIER ti_sysbios_family_arp32_Hwi_restoreIER__E

/* plug */
#undef ti_sysbios_family_arp32_Hwi_plug
#define ti_sysbios_family_arp32_Hwi_plug ti_sysbios_family_arp32_Hwi_plug__E

/* postIntVector */
#undef ti_sysbios_family_arp32_Hwi_postIntVector
#define ti_sysbios_family_arp32_Hwi_postIntVector ti_sysbios_family_arp32_Hwi_postIntVector__E

/* reconfig */
#undef ti_sysbios_family_arp32_Hwi_reconfig
#define ti_sysbios_family_arp32_Hwi_reconfig ti_sysbios_family_arp32_Hwi_reconfig__E

/* getIsrStackAddress */
#define Hwi_getIsrStackAddress ti_sysbios_family_arp32_Hwi_getIsrStackAddress__I

/* dispatchC */
#define Hwi_dispatchC ti_sysbios_family_arp32_Hwi_dispatchC__I

/* dispatchCore */
#define Hwi_dispatchCore ti_sysbios_family_arp32_Hwi_dispatchCore__I

/* switchAndDispatch */
#define Hwi_switchAndDispatch ti_sysbios_family_arp32_Hwi_switchAndDispatch__I

/* unPluggedInterrupt */
#define Hwi_unPluggedInterrupt ti_sysbios_family_arp32_Hwi_unPluggedInterrupt__I

/* nmiInterrupt */
#define Hwi_nmiInterrupt ti_sysbios_family_arp32_Hwi_nmiInterrupt__I

/* swiInterrupt */
#define Hwi_swiInterrupt ti_sysbios_family_arp32_Hwi_swiInterrupt__I

/* undefInterrupt */
#define Hwi_undefInterrupt ti_sysbios_family_arp32_Hwi_undefInterrupt__I

/* dispIsr4 */
#define Hwi_dispIsr4 ti_sysbios_family_arp32_Hwi_dispIsr4__I

/* dispIsr5 */
#define Hwi_dispIsr5 ti_sysbios_family_arp32_Hwi_dispIsr5__I

/* dispIsr6 */
#define Hwi_dispIsr6 ti_sysbios_family_arp32_Hwi_dispIsr6__I

/* dispIsr7 */
#define Hwi_dispIsr7 ti_sysbios_family_arp32_Hwi_dispIsr7__I

/* dispIsr8 */
#define Hwi_dispIsr8 ti_sysbios_family_arp32_Hwi_dispIsr8__I

/* dispIsr9 */
#define Hwi_dispIsr9 ti_sysbios_family_arp32_Hwi_dispIsr9__I

/* dispIsr10 */
#define Hwi_dispIsr10 ti_sysbios_family_arp32_Hwi_dispIsr10__I

/* dispIsr11 */
#define Hwi_dispIsr11 ti_sysbios_family_arp32_Hwi_dispIsr11__I

/* dispIsr12 */
#define Hwi_dispIsr12 ti_sysbios_family_arp32_Hwi_dispIsr12__I

/* dispIsr13 */
#define Hwi_dispIsr13 ti_sysbios_family_arp32_Hwi_dispIsr13__I

/* dispIsr14 */
#define Hwi_dispIsr14 ti_sysbios_family_arp32_Hwi_dispIsr14__I

/* dispIsr15 */
#define Hwi_dispIsr15 ti_sysbios_family_arp32_Hwi_dispIsr15__I

/* postInit */
#define Hwi_postInit ti_sysbios_family_arp32_Hwi_postInit__I

/* Module_startup */
#undef ti_sysbios_family_arp32_Hwi_Module_startup
#define ti_sysbios_family_arp32_Hwi_Module_startup ti_sysbios_family_arp32_Hwi_Module_startup__E

/* Instance_init */
#undef ti_sysbios_family_arp32_Hwi_Instance_init
#define ti_sysbios_family_arp32_Hwi_Instance_init ti_sysbios_family_arp32_Hwi_Instance_init__E

/* Instance_finalize */
#undef ti_sysbios_family_arp32_Hwi_Instance_finalize
#define ti_sysbios_family_arp32_Hwi_Instance_finalize ti_sysbios_family_arp32_Hwi_Instance_finalize__E

/* module */
#define Hwi_module ((ti_sysbios_family_arp32_Hwi_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_arp32_Hwi_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_sysbios_family_arp32_Hwi__cplusplus)
#define module ((ti_sysbios_family_arp32_Hwi_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_arp32_Hwi_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sysbios_family_arp32_Hwi_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sysbios_family_arp32_Hwi_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sysbios_family_arp32_Hwi_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sysbios_family_arp32_Hwi_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sysbios_family_arp32_Hwi_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sysbios_family_arp32_Hwi_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sysbios_family_arp32_Hwi_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sysbios_family_arp32_Hwi_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sysbios_family_arp32_Hwi_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sysbios_family_arp32_Hwi_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sysbios_family_arp32_Hwi_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sysbios_family_arp32_Hwi_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sysbios_family_arp32_Hwi_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sysbios_family_arp32_Hwi_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sysbios_family_arp32_Hwi_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sysbios_family_arp32_Hwi_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sysbios_family_arp32_Hwi_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sysbios_family_arp32_Hwi_Module_GateProxy_query

/* Object__sizingError */
#line 1 "Error_inconsistent_object_size_in_ti.sysbios.family.arp32.Hwi"
typedef char ti_sysbios_family_arp32_Hwi_Object__sizingError[sizeof(ti_sysbios_family_arp32_Hwi_Object) > sizeof(ti_sysbios_family_arp32_Hwi_Struct) ? -1 : 1];


#endif /* ti_sysbios_family_arp32_Hwi__INTERNAL____ */
