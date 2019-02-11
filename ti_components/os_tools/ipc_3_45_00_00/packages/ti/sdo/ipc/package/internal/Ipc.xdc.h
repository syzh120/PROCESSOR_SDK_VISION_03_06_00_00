/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B21
 */

#ifndef ti_sdo_ipc_Ipc__INTERNAL__
#define ti_sdo_ipc_Ipc__INTERNAL__

#ifndef ti_sdo_ipc_Ipc__internalaccess
#define ti_sdo_ipc_Ipc__internalaccess
#endif

#include <ti/sdo/ipc/Ipc.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* getEntry */
#undef ti_sdo_ipc_Ipc_getEntry
#define ti_sdo_ipc_Ipc_getEntry ti_sdo_ipc_Ipc_getEntry__F

/* setEntry */
#undef ti_sdo_ipc_Ipc_setEntry
#define ti_sdo_ipc_Ipc_setEntry ti_sdo_ipc_Ipc_setEntry__F

/* dummy */
#undef ti_sdo_ipc_Ipc_dummy
#define ti_sdo_ipc_Ipc_dummy ti_sdo_ipc_Ipc_dummy__F

/* getMasterAddr */
#define Ipc_getMasterAddr ti_sdo_ipc_Ipc_getMasterAddr__I

/* getRegion0ReservedSize */
#define Ipc_getRegion0ReservedSize ti_sdo_ipc_Ipc_getRegion0ReservedSize__I

/* getSlaveAddr */
#define Ipc_getSlaveAddr ti_sdo_ipc_Ipc_getSlaveAddr__I

/* procSyncStart */
#define Ipc_procSyncStart ti_sdo_ipc_Ipc_procSyncStart__I

/* procSyncFinish */
#define Ipc_procSyncFinish ti_sdo_ipc_Ipc_procSyncFinish__I

/* reservedSizePerProc */
#define Ipc_reservedSizePerProc ti_sdo_ipc_Ipc_reservedSizePerProc__I

/* Module_startup */
#undef ti_sdo_ipc_Ipc_Module_startup
#define ti_sdo_ipc_Ipc_Module_startup ti_sdo_ipc_Ipc_Module_startup__E

/* Instance_init */
#undef ti_sdo_ipc_Ipc_Instance_init
#define ti_sdo_ipc_Ipc_Instance_init ti_sdo_ipc_Ipc_Instance_init__E

/* Instance_finalize */
#undef ti_sdo_ipc_Ipc_Instance_finalize
#define ti_sdo_ipc_Ipc_Instance_finalize ti_sdo_ipc_Ipc_Instance_finalize__E

/* module */
#define Ipc_module ((ti_sdo_ipc_Ipc_Module_State *)(xdc__MODOBJADDR__(ti_sdo_ipc_Ipc_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_sdo_ipc_Ipc__cplusplus)
#define module ((ti_sdo_ipc_Ipc_Module_State *)(xdc__MODOBJADDR__(ti_sdo_ipc_Ipc_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_ipc_Ipc_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_ipc_Ipc_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_ipc_Ipc_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_ipc_Ipc_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_ipc_Ipc_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_ipc_Ipc_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_ipc_Ipc_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_ipc_Ipc_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_ipc_Ipc_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_ipc_Ipc_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_ipc_Ipc_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_ipc_Ipc_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_ipc_Ipc_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_ipc_Ipc_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_ipc_Ipc_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_ipc_Ipc_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_ipc_Ipc_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_ipc_Ipc_Module_GateProxy_query


#endif /* ti_sdo_ipc_Ipc__INTERNAL____ */
