/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A71
 */

#ifndef ti_sysbios_family_c64p_Cache__INTERNAL__
#define ti_sysbios_family_c64p_Cache__INTERNAL__

#ifndef ti_sysbios_family_c64p_Cache__internalaccess
#define ti_sysbios_family_c64p_Cache__internalaccess
#endif

#include <ti/sysbios/family/c64p/Cache.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* enable */
#undef ti_sysbios_family_c64p_Cache_enable
#define ti_sysbios_family_c64p_Cache_enable ti_sysbios_family_c64p_Cache_enable__E

/* inv */
#undef ti_sysbios_family_c64p_Cache_inv
#define ti_sysbios_family_c64p_Cache_inv ti_sysbios_family_c64p_Cache_inv__E

/* wb */
#undef ti_sysbios_family_c64p_Cache_wb
#define ti_sysbios_family_c64p_Cache_wb ti_sysbios_family_c64p_Cache_wb__E

/* wbInv */
#undef ti_sysbios_family_c64p_Cache_wbInv
#define ti_sysbios_family_c64p_Cache_wbInv ti_sysbios_family_c64p_Cache_wbInv__E

/* wait */
#undef ti_sysbios_family_c64p_Cache_wait
#define ti_sysbios_family_c64p_Cache_wait ti_sysbios_family_c64p_Cache_wait__E

/* disable */
#undef ti_sysbios_family_c64p_Cache_disable
#define ti_sysbios_family_c64p_Cache_disable ti_sysbios_family_c64p_Cache_disable__E

/* setMode */
#undef ti_sysbios_family_c64p_Cache_setMode
#define ti_sysbios_family_c64p_Cache_setMode ti_sysbios_family_c64p_Cache_setMode__E

/* getMode */
#undef ti_sysbios_family_c64p_Cache_getMode
#define ti_sysbios_family_c64p_Cache_getMode ti_sysbios_family_c64p_Cache_getMode__E

/* setSize */
#undef ti_sysbios_family_c64p_Cache_setSize
#define ti_sysbios_family_c64p_Cache_setSize ti_sysbios_family_c64p_Cache_setSize__E

/* getSize */
#undef ti_sysbios_family_c64p_Cache_getSize
#define ti_sysbios_family_c64p_Cache_getSize ti_sysbios_family_c64p_Cache_getSize__E

/* getMar */
#undef ti_sysbios_family_c64p_Cache_getMar
#define ti_sysbios_family_c64p_Cache_getMar ti_sysbios_family_c64p_Cache_getMar__E

/* setMar */
#undef ti_sysbios_family_c64p_Cache_setMar
#define ti_sysbios_family_c64p_Cache_setMar ti_sysbios_family_c64p_Cache_setMar__E

/* invL1pAll */
#undef ti_sysbios_family_c64p_Cache_invL1pAll
#define ti_sysbios_family_c64p_Cache_invL1pAll ti_sysbios_family_c64p_Cache_invL1pAll__E

/* wbAll */
#undef ti_sysbios_family_c64p_Cache_wbAll
#define ti_sysbios_family_c64p_Cache_wbAll ti_sysbios_family_c64p_Cache_wbAll__E

/* wbL1dAll */
#undef ti_sysbios_family_c64p_Cache_wbL1dAll
#define ti_sysbios_family_c64p_Cache_wbL1dAll ti_sysbios_family_c64p_Cache_wbL1dAll__E

/* wbInvAll */
#undef ti_sysbios_family_c64p_Cache_wbInvAll
#define ti_sysbios_family_c64p_Cache_wbInvAll ti_sysbios_family_c64p_Cache_wbInvAll__E

/* wbInvL1dAll */
#undef ti_sysbios_family_c64p_Cache_wbInvL1dAll
#define ti_sysbios_family_c64p_Cache_wbInvL1dAll ti_sysbios_family_c64p_Cache_wbInvL1dAll__E

/* all */
#define Cache_all ti_sysbios_family_c64p_Cache_all__I

/* block */
#define Cache_block ti_sysbios_family_c64p_Cache_block__I

/* getL1DInitSize */
#define Cache_getL1DInitSize ti_sysbios_family_c64p_Cache_getL1DInitSize__I

/* getL1PInitSize */
#define Cache_getL1PInitSize ti_sysbios_family_c64p_Cache_getL1PInitSize__I

/* getL2InitSize */
#define Cache_getL2InitSize ti_sysbios_family_c64p_Cache_getL2InitSize__I

/* marInit */
#define Cache_marInit ti_sysbios_family_c64p_Cache_marInit__I

/* Module_startup */
#undef ti_sysbios_family_c64p_Cache_Module_startup
#define ti_sysbios_family_c64p_Cache_Module_startup ti_sysbios_family_c64p_Cache_Module_startup__E

/* Instance_init */
#undef ti_sysbios_family_c64p_Cache_Instance_init
#define ti_sysbios_family_c64p_Cache_Instance_init ti_sysbios_family_c64p_Cache_Instance_init__E

/* Instance_finalize */
#undef ti_sysbios_family_c64p_Cache_Instance_finalize
#define ti_sysbios_family_c64p_Cache_Instance_finalize ti_sysbios_family_c64p_Cache_Instance_finalize__E

/* module */
#define Cache_module ((ti_sysbios_family_c64p_Cache_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_c64p_Cache_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_sysbios_family_c64p_Cache__cplusplus)
#define module ((ti_sysbios_family_c64p_Cache_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_c64p_Cache_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sysbios_family_c64p_Cache_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sysbios_family_c64p_Cache_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sysbios_family_c64p_Cache_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sysbios_family_c64p_Cache_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sysbios_family_c64p_Cache_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sysbios_family_c64p_Cache_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sysbios_family_c64p_Cache_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sysbios_family_c64p_Cache_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sysbios_family_c64p_Cache_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sysbios_family_c64p_Cache_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sysbios_family_c64p_Cache_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sysbios_family_c64p_Cache_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sysbios_family_c64p_Cache_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sysbios_family_c64p_Cache_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sysbios_family_c64p_Cache_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sysbios_family_c64p_Cache_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sysbios_family_c64p_Cache_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sysbios_family_c64p_Cache_Module_GateProxy_query


#endif /* ti_sysbios_family_c64p_Cache__INTERNAL____ */
