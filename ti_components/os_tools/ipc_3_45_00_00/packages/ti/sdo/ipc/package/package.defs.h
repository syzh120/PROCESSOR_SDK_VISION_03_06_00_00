/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B21
 */

#ifndef ti_sdo_ipc__
#define ti_sdo_ipc__


/*
 * ======== module ti.sdo.ipc.GateMP ========
 */

typedef struct ti_sdo_ipc_GateMP_Reserved ti_sdo_ipc_GateMP_Reserved;
typedef struct ti_sdo_ipc_GateMP_LocalGate ti_sdo_ipc_GateMP_LocalGate;
typedef struct ti_sdo_ipc_GateMP_Attrs ti_sdo_ipc_GateMP_Attrs;
typedef struct ti_sdo_ipc_GateMP_Module_State ti_sdo_ipc_GateMP_Module_State;
typedef struct ti_sdo_ipc_GateMP_Params ti_sdo_ipc_GateMP_Params;
typedef struct ti_sdo_ipc_GateMP_Object ti_sdo_ipc_GateMP_Object;
typedef struct ti_sdo_ipc_GateMP_Struct ti_sdo_ipc_GateMP_Struct;
typedef ti_sdo_ipc_GateMP_Object* ti_sdo_ipc_GateMP_Handle;
typedef struct ti_sdo_ipc_GateMP_Object__ ti_sdo_ipc_GateMP_Instance_State;
typedef ti_sdo_ipc_GateMP_Object* ti_sdo_ipc_GateMP_Instance;

/*
 * ======== module ti.sdo.ipc.MessageQ ========
 */

typedef struct ti_sdo_ipc_MessageQ_MsgHeader ti_sdo_ipc_MessageQ_MsgHeader;
typedef struct ti_sdo_ipc_MessageQ_HeapEntry ti_sdo_ipc_MessageQ_HeapEntry;
typedef struct ti_sdo_ipc_MessageQ_TransportEntry ti_sdo_ipc_MessageQ_TransportEntry;
typedef struct ti_sdo_ipc_MessageQ_RegisteredTransport ti_sdo_ipc_MessageQ_RegisteredTransport;
typedef struct ti_sdo_ipc_MessageQ_Module_State ti_sdo_ipc_MessageQ_Module_State;
typedef struct ti_sdo_ipc_MessageQ_Params ti_sdo_ipc_MessageQ_Params;
typedef struct ti_sdo_ipc_MessageQ_Object ti_sdo_ipc_MessageQ_Object;
typedef struct ti_sdo_ipc_MessageQ_Struct ti_sdo_ipc_MessageQ_Struct;
typedef ti_sdo_ipc_MessageQ_Object* ti_sdo_ipc_MessageQ_Handle;
typedef struct ti_sdo_ipc_MessageQ_Object__ ti_sdo_ipc_MessageQ_Instance_State;
typedef ti_sdo_ipc_MessageQ_Object* ti_sdo_ipc_MessageQ_Instance;

/*
 * ======== module ti.sdo.ipc.SharedRegion ========
 */

typedef struct ti_sdo_ipc_SharedRegion_Entry ti_sdo_ipc_SharedRegion_Entry;
typedef struct ti_sdo_ipc_SharedRegion_Region ti_sdo_ipc_SharedRegion_Region;
typedef struct ti_sdo_ipc_SharedRegion_Module_State ti_sdo_ipc_SharedRegion_Module_State;

/*
 * ======== module ti.sdo.ipc.ListMP ========
 */

typedef struct ti_sdo_ipc_ListMP_Elem ti_sdo_ipc_ListMP_Elem;
typedef struct ti_sdo_ipc_ListMP_Attrs ti_sdo_ipc_ListMP_Attrs;
typedef struct ti_sdo_ipc_ListMP_Module_State ti_sdo_ipc_ListMP_Module_State;
typedef struct ti_sdo_ipc_ListMP_Params ti_sdo_ipc_ListMP_Params;
typedef struct ti_sdo_ipc_ListMP_Object ti_sdo_ipc_ListMP_Object;
typedef struct ti_sdo_ipc_ListMP_Struct ti_sdo_ipc_ListMP_Struct;
typedef ti_sdo_ipc_ListMP_Object* ti_sdo_ipc_ListMP_Handle;
typedef struct ti_sdo_ipc_ListMP_Object__ ti_sdo_ipc_ListMP_Instance_State;
typedef ti_sdo_ipc_ListMP_Object* ti_sdo_ipc_ListMP_Instance;

/*
 * ======== module ti.sdo.ipc.Ipc ========
 */

typedef struct ti_sdo_ipc_Ipc_Entry ti_sdo_ipc_Ipc_Entry;
typedef struct ti_sdo_ipc_Ipc_UserFxn ti_sdo_ipc_Ipc_UserFxn;
typedef struct ti_sdo_ipc_Ipc_ConfigEntry ti_sdo_ipc_Ipc_ConfigEntry;
typedef struct ti_sdo_ipc_Ipc_ProcEntry ti_sdo_ipc_Ipc_ProcEntry;
typedef struct ti_sdo_ipc_Ipc_Reserved ti_sdo_ipc_Ipc_Reserved;
typedef struct ti_sdo_ipc_Ipc_UserFxnAndArg ti_sdo_ipc_Ipc_UserFxnAndArg;
typedef struct ti_sdo_ipc_Ipc_Module_State ti_sdo_ipc_Ipc_Module_State;

/*
 * ======== module ti.sdo.ipc.Notify ========
 */

typedef struct ti_sdo_ipc_Notify_EventCallback ti_sdo_ipc_Notify_EventCallback;
typedef struct ti_sdo_ipc_Notify_EventListener ti_sdo_ipc_Notify_EventListener;
typedef struct ti_sdo_ipc_Notify_Module_State ti_sdo_ipc_Notify_Module_State;
typedef struct ti_sdo_ipc_Notify_Params ti_sdo_ipc_Notify_Params;
typedef struct ti_sdo_ipc_Notify_Object ti_sdo_ipc_Notify_Object;
typedef struct ti_sdo_ipc_Notify_Struct ti_sdo_ipc_Notify_Struct;
typedef ti_sdo_ipc_Notify_Object* ti_sdo_ipc_Notify_Handle;
typedef struct ti_sdo_ipc_Notify_Object__ ti_sdo_ipc_Notify_Instance_State;
typedef ti_sdo_ipc_Notify_Object* ti_sdo_ipc_Notify_Instance;

/*
 * ======== module ti.sdo.ipc.GateMP_RemoteSystemProxy ========
 */

typedef struct ti_sdo_ipc_GateMP_RemoteSystemProxy_Fxns__ ti_sdo_ipc_GateMP_RemoteSystemProxy_Fxns__;
typedef const struct ti_sdo_ipc_GateMP_RemoteSystemProxy_Fxns__* ti_sdo_ipc_GateMP_RemoteSystemProxy_Module;
typedef struct ti_sdo_ipc_GateMP_RemoteSystemProxy_Params ti_sdo_ipc_GateMP_RemoteSystemProxy_Params;
typedef struct ti_sdo_ipc_interfaces_IGateMPSupport___Object *ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle;

/*
 * ======== module ti.sdo.ipc.GateMP_RemoteCustom1Proxy ========
 */

typedef struct ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Fxns__ ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Fxns__;
typedef const struct ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Fxns__* ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Module;
typedef struct ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params;
typedef struct ti_sdo_ipc_interfaces_IGateMPSupport___Object *ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle;

/*
 * ======== module ti.sdo.ipc.GateMP_RemoteCustom2Proxy ========
 */

typedef struct ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Fxns__ ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Fxns__;
typedef const struct ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Fxns__* ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Module;
typedef struct ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Params ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Params;
typedef struct ti_sdo_ipc_interfaces_IGateMPSupport___Object *ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Handle;

/*
 * ======== module ti.sdo.ipc.MessageQ_SetupTransportProxy ========
 */

typedef struct ti_sdo_ipc_MessageQ_SetupTransportProxy_Fxns__ ti_sdo_ipc_MessageQ_SetupTransportProxy_Fxns__;
typedef const struct ti_sdo_ipc_MessageQ_SetupTransportProxy_Fxns__* ti_sdo_ipc_MessageQ_SetupTransportProxy_Module;

/*
 * ======== module ti.sdo.ipc.Notify_SetupProxy ========
 */

typedef struct ti_sdo_ipc_Notify_SetupProxy_Fxns__ ti_sdo_ipc_Notify_SetupProxy_Fxns__;
typedef const struct ti_sdo_ipc_Notify_SetupProxy_Fxns__* ti_sdo_ipc_Notify_SetupProxy_Module;

/*
 * ======== module ti.sdo.ipc.Notify_Module_GateProxy ========
 */

typedef struct ti_sdo_ipc_Notify_Module_GateProxy_Fxns__ ti_sdo_ipc_Notify_Module_GateProxy_Fxns__;
typedef const struct ti_sdo_ipc_Notify_Module_GateProxy_Fxns__* ti_sdo_ipc_Notify_Module_GateProxy_Module;
typedef struct ti_sdo_ipc_Notify_Module_GateProxy_Params ti_sdo_ipc_Notify_Module_GateProxy_Params;
typedef struct xdc_runtime_IGateProvider___Object *ti_sdo_ipc_Notify_Module_GateProxy_Handle;


#endif /* ti_sdo_ipc__ */ 
