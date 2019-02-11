/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A71
 */

#ifndef ti_sysbios_hal_unicache_Cache__INTERNAL__
#define ti_sysbios_hal_unicache_Cache__INTERNAL__

#ifndef ti_sysbios_hal_unicache_Cache__internalaccess
#define ti_sysbios_hal_unicache_Cache__internalaccess
#endif

#include <ti/sysbios/hal/unicache/Cache.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* enable */
#undef ti_sysbios_hal_unicache_Cache_enable
#define ti_sysbios_hal_unicache_Cache_enable ti_sysbios_hal_unicache_Cache_enable__E

/* disable */
#undef ti_sysbios_hal_unicache_Cache_disable
#define ti_sysbios_hal_unicache_Cache_disable ti_sysbios_hal_unicache_Cache_disable__E

/* inv */
#undef ti_sysbios_hal_unicache_Cache_inv
#define ti_sysbios_hal_unicache_Cache_inv ti_sysbios_hal_unicache_Cache_inv__E

/* wb */
#undef ti_sysbios_hal_unicache_Cache_wb
#define ti_sysbios_hal_unicache_Cache_wb ti_sysbios_hal_unicache_Cache_wb__E

/* wbInv */
#undef ti_sysbios_hal_unicache_Cache_wbInv
#define ti_sysbios_hal_unicache_Cache_wbInv ti_sysbios_hal_unicache_Cache_wbInv__E

/* wait */
#undef ti_sysbios_hal_unicache_Cache_wait
#define ti_sysbios_hal_unicache_Cache_wait ti_sysbios_hal_unicache_Cache_wait__E

/* lock */
#undef ti_sysbios_hal_unicache_Cache_lock
#define ti_sysbios_hal_unicache_Cache_lock ti_sysbios_hal_unicache_Cache_lock__E

/* unlock */
#undef ti_sysbios_hal_unicache_Cache_unlock
#define ti_sysbios_hal_unicache_Cache_unlock ti_sysbios_hal_unicache_Cache_unlock__E

/* preload */
#undef ti_sysbios_hal_unicache_Cache_preload
#define ti_sysbios_hal_unicache_Cache_preload ti_sysbios_hal_unicache_Cache_preload__E

/* preloadLock */
#undef ti_sysbios_hal_unicache_Cache_preloadLock
#define ti_sysbios_hal_unicache_Cache_preloadLock ti_sysbios_hal_unicache_Cache_preloadLock__E

/* wbAll */
#undef ti_sysbios_hal_unicache_Cache_wbAll
#define ti_sysbios_hal_unicache_Cache_wbAll ti_sysbios_hal_unicache_Cache_wbAll__E

/* invAll */
#undef ti_sysbios_hal_unicache_Cache_invAll
#define ti_sysbios_hal_unicache_Cache_invAll ti_sysbios_hal_unicache_Cache_invAll__E

/* wbInvAll */
#undef ti_sysbios_hal_unicache_Cache_wbInvAll
#define ti_sysbios_hal_unicache_Cache_wbInvAll ti_sysbios_hal_unicache_Cache_wbInvAll__E

/* read */
#undef ti_sysbios_hal_unicache_Cache_read
#define ti_sysbios_hal_unicache_Cache_read ti_sysbios_hal_unicache_Cache_read__E

/* dumpRegs */
#undef ti_sysbios_hal_unicache_Cache_dumpRegs
#define ti_sysbios_hal_unicache_Cache_dumpRegs ti_sysbios_hal_unicache_Cache_dumpRegs__E

/* seizeRegs */
#define Cache_seizeRegs ti_sysbios_hal_unicache_Cache_seizeRegs__I

/* releaseRegs */
#define Cache_releaseRegs ti_sysbios_hal_unicache_Cache_releaseRegs__I

/* ISR */
#define Cache_ISR ti_sysbios_hal_unicache_Cache_ISR__I

/* invAllI */
#define Cache_invAllI ti_sysbios_hal_unicache_Cache_invAllI__I

/* printInfo */
#define Cache_printInfo ti_sysbios_hal_unicache_Cache_printInfo__I

/* printConfig */
#define Cache_printConfig ti_sysbios_hal_unicache_Cache_printConfig__I

/* printOCP */
#define Cache_printOCP ti_sysbios_hal_unicache_Cache_printOCP__I

/* startup */
#define Cache_startup ti_sysbios_hal_unicache_Cache_startup__I

/* Module_startup */
#undef ti_sysbios_hal_unicache_Cache_Module_startup
#define ti_sysbios_hal_unicache_Cache_Module_startup ti_sysbios_hal_unicache_Cache_Module_startup__E

/* Instance_init */
#undef ti_sysbios_hal_unicache_Cache_Instance_init
#define ti_sysbios_hal_unicache_Cache_Instance_init ti_sysbios_hal_unicache_Cache_Instance_init__E

/* Instance_finalize */
#undef ti_sysbios_hal_unicache_Cache_Instance_finalize
#define ti_sysbios_hal_unicache_Cache_Instance_finalize ti_sysbios_hal_unicache_Cache_Instance_finalize__E

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sysbios_hal_unicache_Cache_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sysbios_hal_unicache_Cache_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sysbios_hal_unicache_Cache_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sysbios_hal_unicache_Cache_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sysbios_hal_unicache_Cache_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sysbios_hal_unicache_Cache_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sysbios_hal_unicache_Cache_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sysbios_hal_unicache_Cache_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sysbios_hal_unicache_Cache_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sysbios_hal_unicache_Cache_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sysbios_hal_unicache_Cache_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sysbios_hal_unicache_Cache_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sysbios_hal_unicache_Cache_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sysbios_hal_unicache_Cache_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sysbios_hal_unicache_Cache_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sysbios_hal_unicache_Cache_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sysbios_hal_unicache_Cache_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sysbios_hal_unicache_Cache_Module_GateProxy_query


#endif /* ti_sysbios_hal_unicache_Cache__INTERNAL____ */
