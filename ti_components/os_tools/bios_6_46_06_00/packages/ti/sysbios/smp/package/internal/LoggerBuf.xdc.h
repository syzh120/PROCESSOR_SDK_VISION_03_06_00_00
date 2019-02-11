/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A71
 */

#ifndef ti_sysbios_smp_LoggerBuf__INTERNAL__
#define ti_sysbios_smp_LoggerBuf__INTERNAL__

#ifndef ti_sysbios_smp_LoggerBuf__internalaccess
#define ti_sysbios_smp_LoggerBuf__internalaccess
#endif

#include <ti/sysbios/smp/LoggerBuf.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* enable */
#undef ti_sysbios_smp_LoggerBuf_enable
#define ti_sysbios_smp_LoggerBuf_enable ti_sysbios_smp_LoggerBuf_enable__E

/* disable */
#undef ti_sysbios_smp_LoggerBuf_disable
#define ti_sysbios_smp_LoggerBuf_disable ti_sysbios_smp_LoggerBuf_disable__E

/* write0 */
#undef ti_sysbios_smp_LoggerBuf_write0
#define ti_sysbios_smp_LoggerBuf_write0 ti_sysbios_smp_LoggerBuf_write0__E

/* write1 */
#undef ti_sysbios_smp_LoggerBuf_write1
#define ti_sysbios_smp_LoggerBuf_write1 ti_sysbios_smp_LoggerBuf_write1__E

/* write2 */
#undef ti_sysbios_smp_LoggerBuf_write2
#define ti_sysbios_smp_LoggerBuf_write2 ti_sysbios_smp_LoggerBuf_write2__E

/* write4 */
#undef ti_sysbios_smp_LoggerBuf_write4
#define ti_sysbios_smp_LoggerBuf_write4 ti_sysbios_smp_LoggerBuf_write4__E

/* write8 */
#undef ti_sysbios_smp_LoggerBuf_write8
#define ti_sysbios_smp_LoggerBuf_write8 ti_sysbios_smp_LoggerBuf_write8__E

/* setFilterLevel */
#undef ti_sysbios_smp_LoggerBuf_setFilterLevel
#define ti_sysbios_smp_LoggerBuf_setFilterLevel ti_sysbios_smp_LoggerBuf_setFilterLevel__E

/* getFilterLevel */
#undef ti_sysbios_smp_LoggerBuf_getFilterLevel
#define ti_sysbios_smp_LoggerBuf_getFilterLevel ti_sysbios_smp_LoggerBuf_getFilterLevel__E

/* flushAll */
#undef ti_sysbios_smp_LoggerBuf_flushAll
#define ti_sysbios_smp_LoggerBuf_flushAll ti_sysbios_smp_LoggerBuf_flushAll__E

/* flushAllInternal */
#undef ti_sysbios_smp_LoggerBuf_flushAllInternal
#define ti_sysbios_smp_LoggerBuf_flushAllInternal ti_sysbios_smp_LoggerBuf_flushAllInternal__E

/* reset */
#undef ti_sysbios_smp_LoggerBuf_reset
#define ti_sysbios_smp_LoggerBuf_reset ti_sysbios_smp_LoggerBuf_reset__E

/* flush */
#undef ti_sysbios_smp_LoggerBuf_flush
#define ti_sysbios_smp_LoggerBuf_flush ti_sysbios_smp_LoggerBuf_flush__E

/* getNextEntry */
#undef ti_sysbios_smp_LoggerBuf_getNextEntry
#define ti_sysbios_smp_LoggerBuf_getNextEntry ti_sysbios_smp_LoggerBuf_getNextEntry__E

/* filterOutEvent */
#define LoggerBuf_filterOutEvent ti_sysbios_smp_LoggerBuf_filterOutEvent__I

/* instanceStartup */
#define LoggerBuf_instanceStartup ti_sysbios_smp_LoggerBuf_instanceStartup__I

/* Module_startup */
#undef ti_sysbios_smp_LoggerBuf_Module_startup
#define ti_sysbios_smp_LoggerBuf_Module_startup ti_sysbios_smp_LoggerBuf_Module_startup__E

/* Instance_init */
#undef ti_sysbios_smp_LoggerBuf_Instance_init
#define ti_sysbios_smp_LoggerBuf_Instance_init ti_sysbios_smp_LoggerBuf_Instance_init__E

/* Instance_finalize */
#undef ti_sysbios_smp_LoggerBuf_Instance_finalize
#define ti_sysbios_smp_LoggerBuf_Instance_finalize ti_sysbios_smp_LoggerBuf_Instance_finalize__E

/* module */
#define LoggerBuf_module ((ti_sysbios_smp_LoggerBuf_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_smp_LoggerBuf_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_sysbios_smp_LoggerBuf__cplusplus)
#define module ((ti_sysbios_smp_LoggerBuf_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_smp_LoggerBuf_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sysbios_smp_LoggerBuf_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sysbios_smp_LoggerBuf_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sysbios_smp_LoggerBuf_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sysbios_smp_LoggerBuf_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sysbios_smp_LoggerBuf_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sysbios_smp_LoggerBuf_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sysbios_smp_LoggerBuf_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sysbios_smp_LoggerBuf_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sysbios_smp_LoggerBuf_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sysbios_smp_LoggerBuf_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sysbios_smp_LoggerBuf_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sysbios_smp_LoggerBuf_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sysbios_smp_LoggerBuf_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sysbios_smp_LoggerBuf_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sysbios_smp_LoggerBuf_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sysbios_smp_LoggerBuf_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sysbios_smp_LoggerBuf_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sysbios_smp_LoggerBuf_Module_GateProxy_query

/* Object__sizingError */
#line 1 "Error_inconsistent_object_size_in_ti.sysbios.smp.LoggerBuf"
typedef char ti_sysbios_smp_LoggerBuf_Object__sizingError[sizeof(ti_sysbios_smp_LoggerBuf_Object) > sizeof(ti_sysbios_smp_LoggerBuf_Struct) ? -1 : 1];


#endif /* ti_sysbios_smp_LoggerBuf__INTERNAL____ */
