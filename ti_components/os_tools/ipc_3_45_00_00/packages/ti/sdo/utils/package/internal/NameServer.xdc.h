/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B21
 */

#ifndef ti_sdo_utils_NameServer__INTERNAL__
#define ti_sdo_utils_NameServer__INTERNAL__

#ifndef ti_sdo_utils_NameServer__internalaccess
#define ti_sdo_utils_NameServer__internalaccess
#endif

#include <ti/sdo/utils/NameServer.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* isRegistered */
#undef ti_sdo_utils_NameServer_isRegistered
#define ti_sdo_utils_NameServer_isRegistered ti_sdo_utils_NameServer_isRegistered__E

/* registerRemoteDriver */
#undef ti_sdo_utils_NameServer_registerRemoteDriver
#define ti_sdo_utils_NameServer_registerRemoteDriver ti_sdo_utils_NameServer_registerRemoteDriver__E

/* unregisterRemoteDriver */
#undef ti_sdo_utils_NameServer_unregisterRemoteDriver
#define ti_sdo_utils_NameServer_unregisterRemoteDriver ti_sdo_utils_NameServer_unregisterRemoteDriver__E

/* getKey */
#undef ti_sdo_utils_NameServer_getKey
#define ti_sdo_utils_NameServer_getKey ti_sdo_utils_NameServer_getKey__E

/* postInit */
#define NameServer_postInit ti_sdo_utils_NameServer_postInit__I

/* findLocal */
#define NameServer_findLocal ti_sdo_utils_NameServer_findLocal__I

/* removeLocal */
#define NameServer_removeLocal ti_sdo_utils_NameServer_removeLocal__I

/* editLocal */
#define NameServer_editLocal ti_sdo_utils_NameServer_editLocal__I

/* Module_startup */
#undef ti_sdo_utils_NameServer_Module_startup
#define ti_sdo_utils_NameServer_Module_startup ti_sdo_utils_NameServer_Module_startup__E

/* Instance_init */
#undef ti_sdo_utils_NameServer_Instance_init
#define ti_sdo_utils_NameServer_Instance_init ti_sdo_utils_NameServer_Instance_init__E

/* Instance_finalize */
#undef ti_sdo_utils_NameServer_Instance_finalize
#define ti_sdo_utils_NameServer_Instance_finalize ti_sdo_utils_NameServer_Instance_finalize__E

/* module */
#define NameServer_module ((ti_sdo_utils_NameServer_Module_State *)(xdc__MODOBJADDR__(ti_sdo_utils_NameServer_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_sdo_utils_NameServer__cplusplus)
#define module ((ti_sdo_utils_NameServer_Module_State *)(xdc__MODOBJADDR__(ti_sdo_utils_NameServer_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_utils_NameServer_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_utils_NameServer_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_utils_NameServer_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_utils_NameServer_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_utils_NameServer_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_utils_NameServer_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_utils_NameServer_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_utils_NameServer_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_utils_NameServer_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_utils_NameServer_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_utils_NameServer_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_utils_NameServer_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_utils_NameServer_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_utils_NameServer_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_utils_NameServer_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_utils_NameServer_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_utils_NameServer_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_utils_NameServer_Module_GateProxy_query

/* Object__sizingError */
#line 1 "Error_inconsistent_object_size_in_ti.sdo.utils.NameServer"
typedef char ti_sdo_utils_NameServer_Object__sizingError[sizeof(ti_sdo_utils_NameServer_Object) > sizeof(ti_sdo_utils_NameServer_Struct) ? -1 : 1];


#endif /* ti_sdo_utils_NameServer__INTERNAL____ */
