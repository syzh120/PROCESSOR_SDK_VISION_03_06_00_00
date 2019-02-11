/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B21
 */

#ifndef ti_ipc_family_tci6638_VirtQueue__INTERNAL__
#define ti_ipc_family_tci6638_VirtQueue__INTERNAL__

#ifndef ti_ipc_family_tci6638_VirtQueue__internalaccess
#define ti_ipc_family_tci6638_VirtQueue__internalaccess
#endif

#include <ti/ipc/family/tci6638/VirtQueue.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* startup */
#undef ti_ipc_family_tci6638_VirtQueue_startup
#define ti_ipc_family_tci6638_VirtQueue_startup ti_ipc_family_tci6638_VirtQueue_startup__F

/* cacheWb */
#undef ti_ipc_family_tci6638_VirtQueue_cacheWb
#define ti_ipc_family_tci6638_VirtQueue_cacheWb ti_ipc_family_tci6638_VirtQueue_cacheWb__F

/* kick */
#undef ti_ipc_family_tci6638_VirtQueue_kick
#define ti_ipc_family_tci6638_VirtQueue_kick ti_ipc_family_tci6638_VirtQueue_kick__E

/* isSlave */
#undef ti_ipc_family_tci6638_VirtQueue_isSlave
#define ti_ipc_family_tci6638_VirtQueue_isSlave ti_ipc_family_tci6638_VirtQueue_isSlave__E

/* isHost */
#undef ti_ipc_family_tci6638_VirtQueue_isHost
#define ti_ipc_family_tci6638_VirtQueue_isHost ti_ipc_family_tci6638_VirtQueue_isHost__E

/* getId */
#undef ti_ipc_family_tci6638_VirtQueue_getId
#define ti_ipc_family_tci6638_VirtQueue_getId ti_ipc_family_tci6638_VirtQueue_getId__E

/* getSwiHandle */
#undef ti_ipc_family_tci6638_VirtQueue_getSwiHandle
#define ti_ipc_family_tci6638_VirtQueue_getSwiHandle ti_ipc_family_tci6638_VirtQueue_getSwiHandle__E

/* addAvailBuf */
#undef ti_ipc_family_tci6638_VirtQueue_addAvailBuf
#define ti_ipc_family_tci6638_VirtQueue_addAvailBuf ti_ipc_family_tci6638_VirtQueue_addAvailBuf__E

/* getUsedBuf */
#undef ti_ipc_family_tci6638_VirtQueue_getUsedBuf
#define ti_ipc_family_tci6638_VirtQueue_getUsedBuf ti_ipc_family_tci6638_VirtQueue_getUsedBuf__E

/* getAvailBuf */
#undef ti_ipc_family_tci6638_VirtQueue_getAvailBuf
#define ti_ipc_family_tci6638_VirtQueue_getAvailBuf ti_ipc_family_tci6638_VirtQueue_getAvailBuf__E

/* addUsedBuf */
#undef ti_ipc_family_tci6638_VirtQueue_addUsedBuf
#define ti_ipc_family_tci6638_VirtQueue_addUsedBuf ti_ipc_family_tci6638_VirtQueue_addUsedBuf__E

/* init */
#define VirtQueue_init ti_ipc_family_tci6638_VirtQueue_init__I

/* hostIsr */
#define VirtQueue_hostIsr ti_ipc_family_tci6638_VirtQueue_hostIsr__I

/* slaveIsr */
#define VirtQueue_slaveIsr ti_ipc_family_tci6638_VirtQueue_slaveIsr__I

/* Module_startup */
#undef ti_ipc_family_tci6638_VirtQueue_Module_startup
#define ti_ipc_family_tci6638_VirtQueue_Module_startup ti_ipc_family_tci6638_VirtQueue_Module_startup__E

/* Instance_init */
#undef ti_ipc_family_tci6638_VirtQueue_Instance_init
#define ti_ipc_family_tci6638_VirtQueue_Instance_init ti_ipc_family_tci6638_VirtQueue_Instance_init__E

/* Instance_finalize */
#undef ti_ipc_family_tci6638_VirtQueue_Instance_finalize
#define ti_ipc_family_tci6638_VirtQueue_Instance_finalize ti_ipc_family_tci6638_VirtQueue_Instance_finalize__E

/* module */
#define VirtQueue_module ((ti_ipc_family_tci6638_VirtQueue_Module_State *)(xdc__MODOBJADDR__(ti_ipc_family_tci6638_VirtQueue_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_ipc_family_tci6638_VirtQueue__cplusplus)
#define module ((ti_ipc_family_tci6638_VirtQueue_Module_State *)(xdc__MODOBJADDR__(ti_ipc_family_tci6638_VirtQueue_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_ipc_family_tci6638_VirtQueue_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_ipc_family_tci6638_VirtQueue_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_ipc_family_tci6638_VirtQueue_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_ipc_family_tci6638_VirtQueue_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_ipc_family_tci6638_VirtQueue_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_ipc_family_tci6638_VirtQueue_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_ipc_family_tci6638_VirtQueue_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_ipc_family_tci6638_VirtQueue_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_ipc_family_tci6638_VirtQueue_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_ipc_family_tci6638_VirtQueue_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_ipc_family_tci6638_VirtQueue_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_ipc_family_tci6638_VirtQueue_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_ipc_family_tci6638_VirtQueue_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_ipc_family_tci6638_VirtQueue_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_ipc_family_tci6638_VirtQueue_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_ipc_family_tci6638_VirtQueue_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_ipc_family_tci6638_VirtQueue_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_ipc_family_tci6638_VirtQueue_Module_GateProxy_query

/* Object__sizingError */
#line 1 "Error_inconsistent_object_size_in_ti.ipc.family.tci6638.VirtQueue"
typedef char ti_ipc_family_tci6638_VirtQueue_Object__sizingError[sizeof(ti_ipc_family_tci6638_VirtQueue_Object) > sizeof(ti_ipc_family_tci6638_VirtQueue_Struct) ? -1 : 1];


#endif /* ti_ipc_family_tci6638_VirtQueue__INTERNAL____ */
