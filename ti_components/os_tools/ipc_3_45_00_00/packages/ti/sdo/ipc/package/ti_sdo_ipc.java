/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B21
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_sdo_ipc
{
    static final String VERS = "@(#) xdc-B21\n";

    static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
    static final Proto.Elm $$T_Num = Proto.Elm.newNum();
    static final Proto.Elm $$T_Str = Proto.Elm.newStr();
    static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

    static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
    static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
    static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

    static final XScriptO $$DEFAULT = Value.DEFAULT;
    static final Object $$UNDEF = Undefined.instance;

    static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
    static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
    static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
    static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

    static final Object $$objFldGet = Global.get("$$objFldGet");
    static final Object $$objFldSet = Global.get("$$objFldSet");
    static final Object $$proxyGet = Global.get("$$proxyGet");
    static final Object $$proxySet = Global.get("$$proxySet");
    static final Object $$delegGet = Global.get("$$delegGet");
    static final Object $$delegSet = Global.get("$$delegSet");

    Scriptable xdcO;
    Session ses;
    Value.Obj om;

    boolean isROV;
    boolean isCFG;

    Proto.Obj pkgP;
    Value.Obj pkgV;

    ArrayList<Object> imports = new ArrayList<Object>();
    ArrayList<Object> loggables = new ArrayList<Object>();
    ArrayList<Object> mcfgs = new ArrayList<Object>();
    ArrayList<Object> icfgs = new ArrayList<Object>();
    ArrayList<String> inherits = new ArrayList<String>();
    ArrayList<Object> proxies = new ArrayList<Object>();
    ArrayList<Object> sizes = new ArrayList<Object>();
    ArrayList<Object> tdefs = new ArrayList<Object>();

    void $$IMPORTS()
    {
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.bld");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.utils");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.interfaces");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime.knl");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.syncs");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc", new Value.Obj("ti.sdo.ipc", pkgP));
    }

    void Build$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.Build.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.Build", new Value.Obj("ti.sdo.ipc.Build", po));
        pkgV.bind("Build", vo);
        // decls 
        om.bind("ti.sdo.ipc.Build.LibType", new Proto.Enm("ti.sdo.ipc.Build.LibType"));
    }

    void GateMP$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.GateMP", new Value.Obj("ti.sdo.ipc.GateMP", po));
        pkgV.bind("GateMP", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP$$ModuleView", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP.ModuleView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP$$Reserved", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP.Reserved", new Proto.Str(spo, false));
        om.bind("ti.sdo.ipc.GateMP.LocalProtect", new Proto.Enm("ti.sdo.ipc.GateMP.LocalProtect"));
        om.bind("ti.sdo.ipc.GateMP.RemoteProtect", new Proto.Enm("ti.sdo.ipc.GateMP.RemoteProtect"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP$$LocalGate", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP.LocalGate", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP$$Attrs", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP.Attrs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.GateMP.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.GateMP.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.GateMP.Object", om.findStrict("ti.sdo.ipc.GateMP.Instance_State", "ti.sdo.ipc"));
        }//isROV
    }

    void MessageQ$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.MessageQ", new Value.Obj("ti.sdo.ipc.MessageQ", po));
        pkgV.bind("MessageQ", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ$$QueuesView", new Proto.Obj());
        om.bind("ti.sdo.ipc.MessageQ.QueuesView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ$$MessagesView", new Proto.Obj());
        om.bind("ti.sdo.ipc.MessageQ.MessagesView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ$$ModuleView", new Proto.Obj());
        om.bind("ti.sdo.ipc.MessageQ.ModuleView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ$$MsgHeader", new Proto.Obj());
        om.bind("ti.sdo.ipc.MessageQ.MsgHeader", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ$$HeapEntry", new Proto.Obj());
        om.bind("ti.sdo.ipc.MessageQ.HeapEntry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ$$TransportEntry", new Proto.Obj());
        om.bind("ti.sdo.ipc.MessageQ.TransportEntry", new Proto.Str(spo, false));
        om.bind("ti.sdo.ipc.MessageQ.TransportType", new Proto.Enm("ti.sdo.ipc.MessageQ.TransportType"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ$$RegisteredTransport", new Proto.Obj());
        om.bind("ti.sdo.ipc.MessageQ.RegisteredTransport", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.MessageQ.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.MessageQ.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.MessageQ.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.MessageQ.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.MessageQ.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.MessageQ.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.MessageQ.Object", om.findStrict("ti.sdo.ipc.MessageQ.Instance_State", "ti.sdo.ipc"));
        }//isROV
    }

    void SharedRegion$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.SharedRegion.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.SharedRegion", new Value.Obj("ti.sdo.ipc.SharedRegion", po));
        pkgV.bind("SharedRegion", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.SharedRegion$$RegionView", new Proto.Obj());
        om.bind("ti.sdo.ipc.SharedRegion.RegionView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.SharedRegion$$Entry", new Proto.Obj());
        om.bind("ti.sdo.ipc.SharedRegion.Entry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.SharedRegion$$Region", new Proto.Obj());
        om.bind("ti.sdo.ipc.SharedRegion.Region", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.SharedRegion$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.SharedRegion.Module_State", new Proto.Str(spo, false));
    }

    void ListMP$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.ListMP.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.ListMP", new Value.Obj("ti.sdo.ipc.ListMP", po));
        pkgV.bind("ListMP", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.ListMP$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.ListMP.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.ListMP$$ElemView", new Proto.Obj());
        om.bind("ti.sdo.ipc.ListMP.ElemView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.ListMP$$Elem", new Proto.Obj());
        om.bind("ti.sdo.ipc.ListMP.Elem", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.ListMP$$Attrs", new Proto.Obj());
        om.bind("ti.sdo.ipc.ListMP.Attrs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.ListMP$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.ListMP.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.ListMP$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.ListMP.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.ListMP.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.ListMP$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.ListMP.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.ListMP$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.ListMP.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.ListMP.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.ListMP.Object", om.findStrict("ti.sdo.ipc.ListMP.Instance_State", "ti.sdo.ipc"));
        }//isROV
    }

    void Ipc$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.Ipc.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.Ipc", new Value.Obj("ti.sdo.ipc.Ipc", po));
        pkgV.bind("Ipc", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Ipc$$ModuleView", new Proto.Obj());
        om.bind("ti.sdo.ipc.Ipc.ModuleView", new Proto.Str(spo, false));
        om.bind("ti.sdo.ipc.Ipc.ProcSync", new Proto.Enm("ti.sdo.ipc.Ipc.ProcSync"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Ipc$$Entry", new Proto.Obj());
        om.bind("ti.sdo.ipc.Ipc.Entry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Ipc$$UserFxn", new Proto.Obj());
        om.bind("ti.sdo.ipc.Ipc.UserFxn", new Proto.Str(spo, false));
        om.bind("ti.sdo.ipc.Ipc.ObjType", new Proto.Enm("ti.sdo.ipc.Ipc.ObjType"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Ipc$$ConfigEntry", new Proto.Obj());
        om.bind("ti.sdo.ipc.Ipc.ConfigEntry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Ipc$$ProcEntry", new Proto.Obj());
        om.bind("ti.sdo.ipc.Ipc.ProcEntry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Ipc$$Reserved", new Proto.Obj());
        om.bind("ti.sdo.ipc.Ipc.Reserved", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Ipc$$UserFxnAndArg", new Proto.Obj());
        om.bind("ti.sdo.ipc.Ipc.UserFxnAndArg", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Ipc$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.Ipc.Module_State", new Proto.Str(spo, false));
    }

    void Notify$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.Notify.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.Notify", new Value.Obj("ti.sdo.ipc.Notify", po));
        pkgV.bind("Notify", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Notify$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.Notify.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Notify$$EventDataView", new Proto.Obj());
        om.bind("ti.sdo.ipc.Notify.EventDataView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Notify$$EventCallback", new Proto.Obj());
        om.bind("ti.sdo.ipc.Notify.EventCallback", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Notify$$EventListener", new Proto.Obj());
        om.bind("ti.sdo.ipc.Notify.EventListener", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Notify$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.Notify.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.Notify$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.Notify.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.Notify.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.Notify$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.Notify.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.Notify$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.Notify.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.Notify.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.Notify.Object", om.findStrict("ti.sdo.ipc.Notify.Instance_State", "ti.sdo.ipc"));
        }//isROV
    }

    void GateMP_RemoteSystemProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy", new Value.Obj("ti.sdo.ipc.GateMP_RemoteSystemProxy", po));
        pkgV.bind("GateMP_RemoteSystemProxy", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy.Instance_State", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy.Object", om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Instance_State", "ti.sdo.ipc"));
        }//isROV
    }

    void GateMP_RemoteCustom1Proxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy", new Value.Obj("ti.sdo.ipc.GateMP_RemoteCustom1Proxy", po));
        pkgV.bind("GateMP_RemoteCustom1Proxy", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Instance_State", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Object", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Instance_State", "ti.sdo.ipc"));
        }//isROV
    }

    void GateMP_RemoteCustom2Proxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy", new Value.Obj("ti.sdo.ipc.GateMP_RemoteCustom2Proxy", po));
        pkgV.bind("GateMP_RemoteCustom2Proxy", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Instance_State", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Object", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Instance_State", "ti.sdo.ipc"));
        }//isROV
    }

    void MessageQ_SetupTransportProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.MessageQ_SetupTransportProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.MessageQ_SetupTransportProxy", new Value.Obj("ti.sdo.ipc.MessageQ_SetupTransportProxy", po));
        pkgV.bind("MessageQ_SetupTransportProxy", vo);
        // decls 
    }

    void Notify_SetupProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.Notify_SetupProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.Notify_SetupProxy", new Value.Obj("ti.sdo.ipc.Notify_SetupProxy", po));
        pkgV.bind("Notify_SetupProxy", vo);
        // decls 
    }

    void Notify_Module_GateProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.Notify_Module_GateProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.Notify_Module_GateProxy", new Value.Obj("ti.sdo.ipc.Notify_Module_GateProxy", po));
        pkgV.bind("Notify_Module_GateProxy", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.sdo.ipc.Notify_Module_GateProxy.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.Notify_Module_GateProxy$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.Notify_Module_GateProxy.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.Notify_Module_GateProxy$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.Notify_Module_GateProxy.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.Notify_Module_GateProxy$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.Notify_Module_GateProxy.Instance_State", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.Notify_Module_GateProxy.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.Notify_Module_GateProxy.Object", om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Instance_State", "ti.sdo.ipc"));
        }//isROV
    }

    void Build$$CONSTS()
    {
        // module Build
        om.bind("ti.sdo.ipc.Build.LibType_Instrumented", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Build.LibType", "ti.sdo.ipc"), "ti.sdo.ipc.Build.LibType_Instrumented", 0));
        om.bind("ti.sdo.ipc.Build.LibType_NonInstrumented", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Build.LibType", "ti.sdo.ipc"), "ti.sdo.ipc.Build.LibType_NonInstrumented", 1));
        om.bind("ti.sdo.ipc.Build.LibType_Custom", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Build.LibType", "ti.sdo.ipc"), "ti.sdo.ipc.Build.LibType_Custom", 2));
        om.bind("ti.sdo.ipc.Build.LibType_Debug", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Build.LibType", "ti.sdo.ipc"), "ti.sdo.ipc.Build.LibType_Debug", 3));
        om.bind("ti.sdo.ipc.Build.LibType_PkgLib", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Build.LibType", "ti.sdo.ipc"), "ti.sdo.ipc.Build.LibType_PkgLib", 4));
    }

    void GateMP$$CONSTS()
    {
        // module GateMP
        om.bind("ti.sdo.ipc.GateMP.LocalProtect_NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.GateMP.LocalProtect", "ti.sdo.ipc"), "ti.sdo.ipc.GateMP.LocalProtect_NONE", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.sdo.ipc.GateMP.LocalProtect_INTERRUPT", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.GateMP.LocalProtect", "ti.sdo.ipc"), "ti.sdo.ipc.GateMP.LocalProtect_INTERRUPT", xdc.services.intern.xsr.Enum.intValue(1L)+0));
        om.bind("ti.sdo.ipc.GateMP.LocalProtect_TASKLET", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.GateMP.LocalProtect", "ti.sdo.ipc"), "ti.sdo.ipc.GateMP.LocalProtect_TASKLET", xdc.services.intern.xsr.Enum.intValue(2L)+0));
        om.bind("ti.sdo.ipc.GateMP.LocalProtect_THREAD", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.GateMP.LocalProtect", "ti.sdo.ipc"), "ti.sdo.ipc.GateMP.LocalProtect_THREAD", xdc.services.intern.xsr.Enum.intValue(3L)+0));
        om.bind("ti.sdo.ipc.GateMP.LocalProtect_PROCESS", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.GateMP.LocalProtect", "ti.sdo.ipc"), "ti.sdo.ipc.GateMP.LocalProtect_PROCESS", xdc.services.intern.xsr.Enum.intValue(4L)+0));
        om.bind("ti.sdo.ipc.GateMP.RemoteProtect_NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect", "ti.sdo.ipc"), "ti.sdo.ipc.GateMP.RemoteProtect_NONE", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.sdo.ipc.GateMP.RemoteProtect_SYSTEM", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect", "ti.sdo.ipc"), "ti.sdo.ipc.GateMP.RemoteProtect_SYSTEM", xdc.services.intern.xsr.Enum.intValue(1L)+0));
        om.bind("ti.sdo.ipc.GateMP.RemoteProtect_CUSTOM1", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect", "ti.sdo.ipc"), "ti.sdo.ipc.GateMP.RemoteProtect_CUSTOM1", xdc.services.intern.xsr.Enum.intValue(2L)+0));
        om.bind("ti.sdo.ipc.GateMP.RemoteProtect_CUSTOM2", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect", "ti.sdo.ipc"), "ti.sdo.ipc.GateMP.RemoteProtect_CUSTOM2", xdc.services.intern.xsr.Enum.intValue(3L)+0));
        om.bind("ti.sdo.ipc.GateMP.VERSION", 1L);
        om.bind("ti.sdo.ipc.GateMP.CREATED", 0x11202009L);
        om.bind("ti.sdo.ipc.GateMP.ProxyOrder_SYSTEM", 0L);
        om.bind("ti.sdo.ipc.GateMP.ProxyOrder_CUSTOM1", 1L);
        om.bind("ti.sdo.ipc.GateMP.ProxyOrder_CUSTOM2", 2L);
        om.bind("ti.sdo.ipc.GateMP.ProxyOrder_NUM", 3L);
        om.bind("ti.sdo.ipc.GateMP.createLocal", new Extern("ti_sdo_ipc_GateMP_createLocal__E", "xdc_runtime_IGateProvider_Handle(*)(ti_sdo_ipc_GateMP_LocalProtect)", true, false));
        om.bind("ti.sdo.ipc.GateMP.attach", new Extern("ti_sdo_ipc_GateMP_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.GateMP.detach", new Extern("ti_sdo_ipc_GateMP_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.GateMP.getRegion0ReservedSize", new Extern("ti_sdo_ipc_GateMP_getRegion0ReservedSize__E", "xdc_SizeT(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.GateMP.setRegion0Reserved", new Extern("ti_sdo_ipc_GateMP_setRegion0Reserved__E", "xdc_Void(*)(xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.GateMP.openRegion0Reserved", new Extern("ti_sdo_ipc_GateMP_openRegion0Reserved__E", "xdc_Void(*)(xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.GateMP.setDefaultRemote", new Extern("ti_sdo_ipc_GateMP_setDefaultRemote__E", "xdc_Void(*)(ti_sdo_ipc_GateMP_Handle)", true, false));
        om.bind("ti.sdo.ipc.GateMP.start", new Extern("ti_sdo_ipc_GateMP_start__E", "xdc_Int(*)(xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.GateMP.stop", new Extern("ti_sdo_ipc_GateMP_stop__E", "xdc_Int(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.GateMP.getFreeResource", new Extern("ti_sdo_ipc_GateMP_getFreeResource__I", "xdc_UInt(*)(xdc_UInt8*,xdc_Int,xdc_runtime_Error_Block*)", true, false));
    }

    void MessageQ$$CONSTS()
    {
        // module MessageQ
        om.bind("ti.sdo.ipc.MessageQ.NORMALPRI", 0L);
        om.bind("ti.sdo.ipc.MessageQ.HIGHPRI", 1L);
        om.bind("ti.sdo.ipc.MessageQ.RESERVEDPRI", 2L);
        om.bind("ti.sdo.ipc.MessageQ.URGENTPRI", 3L);
        om.bind("ti.sdo.ipc.MessageQ.ANY", Global.eval("~(0)"));
        om.bind("ti.sdo.ipc.MessageQ.VERSIONMASK", 0xE000L);
        om.bind("ti.sdo.ipc.MessageQ.HEADERVERSION", 0x2000L);
        om.bind("ti.sdo.ipc.MessageQ.TRACEMASK", 0x1000L);
        om.bind("ti.sdo.ipc.MessageQ.TRACESHIFT", 12L);
        om.bind("ti.sdo.ipc.MessageQ.PRIORITYMASK", 0x3L);
        om.bind("ti.sdo.ipc.MessageQ.TRANSPORTPRIORITYMASK", 0x1L);
        om.bind("ti.sdo.ipc.MessageQ.PROXY_FAILURE", 1L);
        om.bind("ti.sdo.ipc.MessageQ.STATICMSG", 0xFFFFL);
        om.bind("ti.sdo.ipc.MessageQ.TransportType_IMessageQTransport", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.MessageQ.TransportType", "ti.sdo.ipc"), "ti.sdo.ipc.MessageQ.TransportType_IMessageQTransport", 0));
        om.bind("ti.sdo.ipc.MessageQ.TransportType_INetworkTransport", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.MessageQ.TransportType", "ti.sdo.ipc"), "ti.sdo.ipc.MessageQ.TransportType_INetworkTransport", 1));
        om.bind("ti.sdo.ipc.MessageQ.TransportType_Invalid", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.MessageQ.TransportType", "ti.sdo.ipc"), "ti.sdo.ipc.MessageQ.TransportType_Invalid", 2));
        om.bind("ti.sdo.ipc.MessageQ.registerTransport", new Extern("ti_sdo_ipc_MessageQ_registerTransport__E", "xdc_Bool(*)(ti_sdo_ipc_interfaces_IMessageQTransport_Handle,xdc_UInt16,xdc_UInt)", true, false));
        om.bind("ti.sdo.ipc.MessageQ.unregisterTransport", new Extern("ti_sdo_ipc_MessageQ_unregisterTransport__E", "xdc_Void(*)(xdc_UInt16,xdc_UInt)", true, false));
        om.bind("ti.sdo.ipc.MessageQ.grow", new Extern("ti_sdo_ipc_MessageQ_grow__I", "xdc_UInt16(*)(ti_sdo_ipc_MessageQ_Object*,xdc_runtime_Error_Block*)", true, false));
    }

    void SharedRegion$$CONSTS()
    {
        // module SharedRegion
        om.bind("ti.sdo.ipc.SharedRegion.INVALIDREGIONID", 0xFFFFL);
        om.bind("ti.sdo.ipc.SharedRegion.DEFAULTOWNERID", Global.eval("~0"));
        om.bind("ti.sdo.ipc.SharedRegion.CREATED", 0x08111963L);
        om.bind("ti.sdo.ipc.SharedRegion.attach", new Extern("ti_sdo_ipc_SharedRegion_attach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.SharedRegion.clearReservedMemory", new Extern("ti_sdo_ipc_SharedRegion_clearReservedMemory__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.SharedRegion.detach", new Extern("ti_sdo_ipc_SharedRegion_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.SharedRegion.reserveMemory", new Extern("ti_sdo_ipc_SharedRegion_reserveMemory__E", "xdc_Ptr(*)(xdc_UInt16,xdc_SizeT)", true, false));
        om.bind("ti.sdo.ipc.SharedRegion.resetInternalFields", new Extern("ti_sdo_ipc_SharedRegion_resetInternalFields__E", "xdc_Void(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.SharedRegion.start", new Extern("ti_sdo_ipc_SharedRegion_start__E", "xdc_Int(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.SharedRegion.stop", new Extern("ti_sdo_ipc_SharedRegion_stop__E", "xdc_Int(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.SharedRegion.checkOverlap", new Extern("ti_sdo_ipc_SharedRegion_checkOverlap__I", "xdc_Int(*)(xdc_Ptr,xdc_SizeT)", true, false));
    }

    void ListMP$$CONSTS()
    {
        // module ListMP
        om.bind("ti.sdo.ipc.ListMP.CREATED", 0x12181964L);
        om.bind("ti.sdo.ipc.ListMP.elemClear", new Extern("ti_sdo_ipc_ListMP_elemClear__I", "xdc_Void(*)(ti_sdo_ipc_ListMP_Elem*)", true, false));
        om.bind("ti.sdo.ipc.ListMP.postInit", new Extern("ti_sdo_ipc_ListMP_postInit__I", "xdc_Void(*)(ti_sdo_ipc_ListMP_Object*,xdc_runtime_Error_Block*)", true, false));
    }

    void Ipc$$CONSTS()
    {
        // module Ipc
        om.bind("ti.sdo.ipc.Ipc.ProcSync_NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Ipc.ProcSync", "ti.sdo.ipc"), "ti.sdo.ipc.Ipc.ProcSync_NONE", 0));
        om.bind("ti.sdo.ipc.Ipc.ProcSync_PAIR", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Ipc.ProcSync", "ti.sdo.ipc"), "ti.sdo.ipc.Ipc.ProcSync_PAIR", 1));
        om.bind("ti.sdo.ipc.Ipc.ProcSync_ALL", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Ipc.ProcSync", "ti.sdo.ipc"), "ti.sdo.ipc.Ipc.ProcSync_ALL", 2));
        om.bind("ti.sdo.ipc.Ipc.PROCSYNCSTART", 1L);
        om.bind("ti.sdo.ipc.Ipc.PROCSYNCFINISH", 2L);
        om.bind("ti.sdo.ipc.Ipc.PROCSYNCDETACH", 3L);
        om.bind("ti.sdo.ipc.Ipc.ObjType_CREATESTATIC", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc"), "ti.sdo.ipc.Ipc.ObjType_CREATESTATIC", xdc.services.intern.xsr.Enum.intValue(0x1L)+0));
        om.bind("ti.sdo.ipc.Ipc.ObjType_CREATESTATIC_REGION", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc"), "ti.sdo.ipc.Ipc.ObjType_CREATESTATIC_REGION", xdc.services.intern.xsr.Enum.intValue(0x2L)+0));
        om.bind("ti.sdo.ipc.Ipc.ObjType_CREATEDYNAMIC", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc"), "ti.sdo.ipc.Ipc.ObjType_CREATEDYNAMIC", xdc.services.intern.xsr.Enum.intValue(0x4L)+0));
        om.bind("ti.sdo.ipc.Ipc.ObjType_CREATEDYNAMIC_REGION", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc"), "ti.sdo.ipc.Ipc.ObjType_CREATEDYNAMIC_REGION", xdc.services.intern.xsr.Enum.intValue(0x8L)+0));
        om.bind("ti.sdo.ipc.Ipc.ObjType_OPENDYNAMIC", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc"), "ti.sdo.ipc.Ipc.ObjType_OPENDYNAMIC", xdc.services.intern.xsr.Enum.intValue(0x10L)+0));
        om.bind("ti.sdo.ipc.Ipc.ObjType_LOCAL", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc"), "ti.sdo.ipc.Ipc.ObjType_LOCAL", xdc.services.intern.xsr.Enum.intValue(0x20L)+0));
        om.bind("ti.sdo.ipc.Ipc.getEntry", new Extern("ti_sdo_ipc_Ipc_getEntry__E", "xdc_Void(*)(ti_sdo_ipc_Ipc_Entry*)", true, false));
        om.bind("ti.sdo.ipc.Ipc.setEntry", new Extern("ti_sdo_ipc_Ipc_setEntry__E", "xdc_Void(*)(ti_sdo_ipc_Ipc_Entry*)", true, false));
        om.bind("ti.sdo.ipc.Ipc.dummy", new Extern("ti_sdo_ipc_Ipc_dummy__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.Ipc.getMasterAddr", new Extern("ti_sdo_ipc_Ipc_getMasterAddr__I", "xdc_Ptr(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.Ipc.getRegion0ReservedSize", new Extern("ti_sdo_ipc_Ipc_getRegion0ReservedSize__I", "xdc_SizeT(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.Ipc.getSlaveAddr", new Extern("ti_sdo_ipc_Ipc_getSlaveAddr__I", "xdc_Ptr(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.Ipc.procSyncStart", new Extern("ti_sdo_ipc_Ipc_procSyncStart__I", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.Ipc.procSyncFinish", new Extern("ti_sdo_ipc_Ipc_procSyncFinish__I", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.Ipc.reservedSizePerProc", new Extern("ti_sdo_ipc_Ipc_reservedSizePerProc__I", "xdc_SizeT(*)(xdc_Void)", true, false));
    }

    void Notify$$CONSTS()
    {
        // module Notify
        om.bind("ti.sdo.ipc.Notify.MAXEVENTS", 32L);
        om.bind("ti.sdo.ipc.Notify.detach", new Extern("ti_sdo_ipc_Notify_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.Notify.execMany", new Extern("ti_sdo_ipc_Notify_execMany__I", "xdc_Void(*)(xdc_UInt16,xdc_UInt16,xdc_UInt32,xdc_UArg,xdc_UInt32)", true, false));
    }

    void GateMP_RemoteSystemProxy$$CONSTS()
    {
        // module GateMP_RemoteSystemProxy
        om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy.query", new Extern("ti_sdo_ipc_GateMP_RemoteSystemProxy_query__E", "xdc_Bool(*)(xdc_Int)", true, false));
        om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy.getReservedMask", new Extern("ti_sdo_ipc_GateMP_RemoteSystemProxy_getReservedMask__E", "xdc_Bits32*(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy.sharedMemReq", new Extern("ti_sdo_ipc_GateMP_RemoteSystemProxy_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_interfaces_IGateMPSupport_Params*)", true, false));
    }

    void GateMP_RemoteCustom1Proxy$$CONSTS()
    {
        // module GateMP_RemoteCustom1Proxy
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.query", new Extern("ti_sdo_ipc_GateMP_RemoteCustom1Proxy_query__E", "xdc_Bool(*)(xdc_Int)", true, false));
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.getReservedMask", new Extern("ti_sdo_ipc_GateMP_RemoteCustom1Proxy_getReservedMask__E", "xdc_Bits32*(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.sharedMemReq", new Extern("ti_sdo_ipc_GateMP_RemoteCustom1Proxy_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_interfaces_IGateMPSupport_Params*)", true, false));
    }

    void GateMP_RemoteCustom2Proxy$$CONSTS()
    {
        // module GateMP_RemoteCustom2Proxy
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.query", new Extern("ti_sdo_ipc_GateMP_RemoteCustom2Proxy_query__E", "xdc_Bool(*)(xdc_Int)", true, false));
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.getReservedMask", new Extern("ti_sdo_ipc_GateMP_RemoteCustom2Proxy_getReservedMask__E", "xdc_Bits32*(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.sharedMemReq", new Extern("ti_sdo_ipc_GateMP_RemoteCustom2Proxy_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_interfaces_IGateMPSupport_Params*)", true, false));
    }

    void MessageQ_SetupTransportProxy$$CONSTS()
    {
        // module MessageQ_SetupTransportProxy
        om.bind("ti.sdo.ipc.MessageQ_SetupTransportProxy.attach", new Extern("ti_sdo_ipc_MessageQ_SetupTransportProxy_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.MessageQ_SetupTransportProxy.detach", new Extern("ti_sdo_ipc_MessageQ_SetupTransportProxy_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.MessageQ_SetupTransportProxy.isRegistered", new Extern("ti_sdo_ipc_MessageQ_SetupTransportProxy_isRegistered__E", "xdc_Bool(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.MessageQ_SetupTransportProxy.sharedMemReq", new Extern("ti_sdo_ipc_MessageQ_SetupTransportProxy_sharedMemReq__E", "xdc_SizeT(*)(xdc_Ptr)", true, false));
    }

    void Notify_SetupProxy$$CONSTS()
    {
        // module Notify_SetupProxy
        om.bind("ti.sdo.ipc.Notify_SetupProxy.attach", new Extern("ti_sdo_ipc_Notify_SetupProxy_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.Notify_SetupProxy.sharedMemReq", new Extern("ti_sdo_ipc_Notify_SetupProxy_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.Notify_SetupProxy.numIntLines", new Extern("ti_sdo_ipc_Notify_SetupProxy_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void Notify_Module_GateProxy$$CONSTS()
    {
        // module Notify_Module_GateProxy
        om.bind("ti.sdo.ipc.Notify_Module_GateProxy.query", new Extern("ti_sdo_ipc_Notify_Module_GateProxy_query__E", "xdc_Bool(*)(xdc_Int)", true, false));
    }

    void Build$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void GateMP$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$GateMP$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.GateMP.create() called before xdc.useModule('ti.sdo.ipc.GateMP')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.GateMP$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.GateMP.Module", "ti.sdo.ipc"), om.findStrict("ti.sdo.ipc.GateMP.Instance", "ti.sdo.ipc"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$GateMP$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.GateMP'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.GateMP.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.GateMP'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.GateMP'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.GateMP$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.GateMP.Module", "ti.sdo.ipc"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.GateMP$$Object", "ti.sdo.ipc"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$GateMP$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.GateMP'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.GateMP'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.GateMP'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void MessageQ$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$MessageQ$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.MessageQ.create() called before xdc.useModule('ti.sdo.ipc.MessageQ')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.name, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.MessageQ$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.MessageQ.Module", "ti.sdo.ipc"), om.findStrict("ti.sdo.ipc.MessageQ.Instance", "ti.sdo.ipc"), 2, 1, false));
                        fxn.addArg(0, "name", $$T_Str, $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.MessageQ.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$MessageQ$$create = function( name, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.MessageQ'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.MessageQ.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {name:name});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.MessageQ'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [name]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.MessageQ'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.MessageQ$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.MessageQ.Module", "ti.sdo.ipc"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.MessageQ$$Object", "ti.sdo.ipc"), null);
                        fxn.addArg(1, "name", $$T_Str, $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.MessageQ.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$MessageQ$$construct = function( __obj, name, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.MessageQ'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {name:name});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.MessageQ'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.MessageQ'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void SharedRegion$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ListMP$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$ListMP$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.ListMP.create() called before xdc.useModule('ti.sdo.ipc.ListMP')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.ListMP$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.ListMP.Module", "ti.sdo.ipc"), om.findStrict("ti.sdo.ipc.ListMP.Instance", "ti.sdo.ipc"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ipc.ListMP.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$ListMP$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.ListMP'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.ListMP.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.ListMP'].Instance_State);\n");
                sb.append("__inst.metaListMP = __mod.PARAMS.metaListMP;\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.ListMP'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.ListMP$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.ListMP.Module", "ti.sdo.ipc"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.ListMP$$Object", "ti.sdo.ipc"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.ListMP.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$ListMP$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.ListMP'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.ListMP'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("__inst.metaListMP = __mod.PARAMS.metaListMP;\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.ListMP'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void Ipc$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Notify$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$Notify$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.Notify.create() called before xdc.useModule('ti.sdo.ipc.Notify')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.driverHandle, inst.$args.remoteProcId, inst.$args.lineId, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Notify$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Notify.Module", "ti.sdo.ipc"), om.findStrict("ti.sdo.ipc.Notify.Instance", "ti.sdo.ipc"), 4, 3, false));
                        fxn.addArg(0, "driverHandle", (Proto)om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver.Handle", "ti.sdo.ipc"), $$UNDEF);
                        fxn.addArg(1, "remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(2, "lineId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(3, "__params", (Proto)om.findStrict("ti.sdo.ipc.Notify.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$Notify$$create = function( driverHandle, remoteProcId, lineId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.Notify'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.Notify.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {driverHandle:driverHandle, remoteProcId:remoteProcId, lineId:lineId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.Notify'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [driverHandle, remoteProcId, lineId]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.Notify'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Notify$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Notify.Module", "ti.sdo.ipc"), null, 5, 3, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.Notify$$Object", "ti.sdo.ipc"), null);
                        fxn.addArg(1, "driverHandle", (Proto)om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver.Handle", "ti.sdo.ipc"), $$UNDEF);
                        fxn.addArg(2, "remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(3, "lineId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(4, "__params", (Proto)om.findStrict("ti.sdo.ipc.Notify.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$Notify$$construct = function( __obj, driverHandle, remoteProcId, lineId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.Notify'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {driverHandle:driverHandle, remoteProcId:remoteProcId, lineId:lineId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.Notify'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.Notify'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void GateMP_RemoteSystemProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$GateMP_RemoteSystemProxy$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.GateMP_RemoteSystemProxy.create() called before xdc.useModule('ti.sdo.ipc.GateMP_RemoteSystemProxy')\");\n");
                sb.append("}\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.GateMP_RemoteSystemProxy$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Module", "ti.sdo.ipc"), om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Instance", "ti.sdo.ipc"), 2, 1, false));
                        fxn.addArg(0, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$GateMP_RemoteSystemProxy$$create = function( localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.GateMP_RemoteSystemProxy'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.GateMP_RemoteSystemProxy.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.GateMP_RemoteSystemProxy'].Instance_State);\n");
                sb.append("if (!__mod.delegate$) {\n");
                    sb.append("throw new Error(\"Unbound proxy module: ti.sdo.ipc.GateMP_RemoteSystemProxy\");\n");
                sb.append("}\n");
                sb.append("var __dmod = __mod.delegate$.$orig;\n");
                sb.append("var __dinst = __dmod.create(localGate, __params);\n");
                sb.append("__inst.$$bind('delegate$', __dinst);\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [localGate]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.GateMP_RemoteSystemProxy'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void GateMP_RemoteCustom1Proxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$GateMP_RemoteCustom1Proxy$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.GateMP_RemoteCustom1Proxy.create() called before xdc.useModule('ti.sdo.ipc.GateMP_RemoteCustom1Proxy')\");\n");
                sb.append("}\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.GateMP_RemoteCustom1Proxy$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Module", "ti.sdo.ipc"), om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Instance", "ti.sdo.ipc"), 2, 1, false));
                        fxn.addArg(0, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$GateMP_RemoteCustom1Proxy$$create = function( localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.GateMP_RemoteCustom1Proxy'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.GateMP_RemoteCustom1Proxy'].Instance_State);\n");
                sb.append("if (!__mod.delegate$) {\n");
                    sb.append("throw new Error(\"Unbound proxy module: ti.sdo.ipc.GateMP_RemoteCustom1Proxy\");\n");
                sb.append("}\n");
                sb.append("var __dmod = __mod.delegate$.$orig;\n");
                sb.append("var __dinst = __dmod.create(localGate, __params);\n");
                sb.append("__inst.$$bind('delegate$', __dinst);\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [localGate]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.GateMP_RemoteCustom1Proxy'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void GateMP_RemoteCustom2Proxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$GateMP_RemoteCustom2Proxy$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.GateMP_RemoteCustom2Proxy.create() called before xdc.useModule('ti.sdo.ipc.GateMP_RemoteCustom2Proxy')\");\n");
                sb.append("}\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.GateMP_RemoteCustom2Proxy$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Module", "ti.sdo.ipc"), om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Instance", "ti.sdo.ipc"), 2, 1, false));
                        fxn.addArg(0, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$GateMP_RemoteCustom2Proxy$$create = function( localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.GateMP_RemoteCustom2Proxy'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.GateMP_RemoteCustom2Proxy'].Instance_State);\n");
                sb.append("if (!__mod.delegate$) {\n");
                    sb.append("throw new Error(\"Unbound proxy module: ti.sdo.ipc.GateMP_RemoteCustom2Proxy\");\n");
                sb.append("}\n");
                sb.append("var __dmod = __mod.delegate$.$orig;\n");
                sb.append("var __dinst = __dmod.create(localGate, __params);\n");
                sb.append("__inst.$$bind('delegate$', __dinst);\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [localGate]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.GateMP_RemoteCustom2Proxy'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void MessageQ_SetupTransportProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Notify_SetupProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Notify_Module_GateProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$Notify_Module_GateProxy$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.Notify_Module_GateProxy.create() called before xdc.useModule('ti.sdo.ipc.Notify_Module_GateProxy')\");\n");
                sb.append("}\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Notify_Module_GateProxy$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Module", "ti.sdo.ipc"), om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Instance", "ti.sdo.ipc"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Params", "ti.sdo.ipc"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$Notify_Module_GateProxy$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.Notify_Module_GateProxy'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.Notify_Module_GateProxy.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.Notify_Module_GateProxy'].Instance_State);\n");
                sb.append("if (!__mod.delegate$) {\n");
                    sb.append("throw new Error(\"Unbound proxy module: ti.sdo.ipc.Notify_Module_GateProxy\");\n");
                sb.append("}\n");
                sb.append("var __dmod = __mod.delegate$.$orig;\n");
                sb.append("var __dinst = __dmod.create(__params);\n");
                sb.append("__inst.$$bind('delegate$', __dinst);\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.Notify_Module_GateProxy'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void Build$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Build.getCCOpts
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Build$$getCCOpts", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Build.Module", "ti.sdo.ipc"), $$T_Str, 1, 1, false));
                fxn.addArg(0, "target", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.sdo.ipc"), $$UNDEF);
        // fxn Build.getDefaultCustomCCOpts
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Build$$getDefaultCustomCCOpts", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Build.Module", "ti.sdo.ipc"), $$T_Str, 0, 0, false));
        // fxn Build.getDefs
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Build$$getDefs", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Build.Module", "ti.sdo.ipc"), $$T_Str, 0, 0, false));
        // fxn Build.getCFiles
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Build$$getCFiles", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Build.Module", "ti.sdo.ipc"), $$T_Str, 1, 1, false));
                fxn.addArg(0, "target", $$T_Str, $$UNDEF);
        // fxn Build.getAsmFiles
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Build$$getAsmFiles", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Build.Module", "ti.sdo.ipc"), $$T_Obj, 1, 1, false));
                fxn.addArg(0, "target", $$T_Str, $$UNDEF);
        // fxn Build.buildLibs
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Build$$buildLibs", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Build.Module", "ti.sdo.ipc"), null, 0, -1, false));
        // fxn Build.getLibs
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Build$$getLibs", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Build.Module", "ti.sdo.ipc"), null, 0, -1, false));
    }

    void GateMP$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void MessageQ$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn MessageQ.registerHeapMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.MessageQ$$registerHeapMeta", new Proto.Fxn(om.findStrict("ti.sdo.ipc.MessageQ.Module", "ti.sdo.ipc"), null, 2, 2, false));
                fxn.addArg(0, "heap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "ti.sdo.ipc"), $$UNDEF);
                fxn.addArg(1, "heapId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
        // fxn MessageQ.registerTransportMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.MessageQ$$registerTransportMeta", new Proto.Fxn(om.findStrict("ti.sdo.ipc.MessageQ.Module", "ti.sdo.ipc"), null, 3, 3, false));
                fxn.addArg(0, "transport", (Proto)om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Handle", "ti.sdo.ipc"), $$UNDEF);
                fxn.addArg(1, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                fxn.addArg(2, "priority", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF);
    }

    void SharedRegion$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn SharedRegion.genSectionInCmd
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.SharedRegion$$genSectionInCmd", new Proto.Fxn(om.findStrict("ti.sdo.ipc.SharedRegion.Module", "ti.sdo.ipc"), null, 2, 2, false));
                fxn.addArg(0, "id", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                fxn.addArg(1, "gen", $$T_Bool, $$UNDEF);
        // fxn SharedRegion.getCacheLineSizeMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.SharedRegion$$getCacheLineSizeMeta", new Proto.Fxn(om.findStrict("ti.sdo.ipc.SharedRegion.Module", "ti.sdo.ipc"), Proto.Elm.newCNum("(xdc_SizeT)"), 1, 1, false));
                fxn.addArg(0, "id", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
        // fxn SharedRegion.getIdMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.SharedRegion$$getIdMeta", new Proto.Fxn(om.findStrict("ti.sdo.ipc.SharedRegion.Module", "ti.sdo.ipc"), Proto.Elm.newCNum("(xdc_UInt16)"), 1, 1, false));
                fxn.addArg(0, "addr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF);
        // fxn SharedRegion.getPtrMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.SharedRegion$$getPtrMeta", new Proto.Fxn(om.findStrict("ti.sdo.ipc.SharedRegion.Module", "ti.sdo.ipc"), new Proto.Adr("xdc_Ptr", "Pv"), 1, 1, false));
                fxn.addArg(0, "srptr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF);
        // fxn SharedRegion.getPtrMeta$view
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.SharedRegion$$getPtrMeta$view", new Proto.Fxn(om.findStrict("ti.sdo.ipc.SharedRegion.Module", "ti.sdo.ipc"), new Proto.Adr("xdc_Ptr", "Pv"), 1, 1, false));
                fxn.addArg(0, "srptr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF);
        // fxn SharedRegion.getSRPtrMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.SharedRegion$$getSRPtrMeta", new Proto.Fxn(om.findStrict("ti.sdo.ipc.SharedRegion.Module", "ti.sdo.ipc"), Proto.Elm.newCNum("(xdc_Bits32)"), 1, 1, false));
                fxn.addArg(0, "addr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF);
        // fxn SharedRegion.getSRPtrMeta$view
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.SharedRegion$$getSRPtrMeta$view", new Proto.Fxn(om.findStrict("ti.sdo.ipc.SharedRegion.Module", "ti.sdo.ipc"), Proto.Elm.newCNum("(xdc_Bits32)"), 1, 1, false));
                fxn.addArg(0, "addr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF);
        // fxn SharedRegion.isCacheEnabledMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.SharedRegion$$isCacheEnabledMeta", new Proto.Fxn(om.findStrict("ti.sdo.ipc.SharedRegion.Module", "ti.sdo.ipc"), $$T_Bool, 1, 1, false));
                fxn.addArg(0, "id", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
        // fxn SharedRegion.setEntryMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.SharedRegion$$setEntryMeta", new Proto.Fxn(om.findStrict("ti.sdo.ipc.SharedRegion.Module", "ti.sdo.ipc"), null, 2, 2, false));
                fxn.addArg(0, "id", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                fxn.addArg(1, "entry", (Proto)om.findStrict("ti.sdo.ipc.SharedRegion.Entry", "ti.sdo.ipc"), $$DEFAULT);
    }

    void ListMP$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Ipc$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Ipc.addUserFxn
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Ipc$$addUserFxn", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Ipc.Module", "ti.sdo.ipc"), null, 2, 2, false));
                fxn.addArg(0, "fxn", (Proto)om.findStrict("ti.sdo.ipc.Ipc.UserFxn", "ti.sdo.ipc"), $$DEFAULT);
                fxn.addArg(1, "arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF);
        // fxn Ipc.setEntryMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Ipc$$setEntryMeta", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Ipc.Module", "ti.sdo.ipc"), null, 1, 1, false));
                fxn.addArg(0, "entry", (Proto)om.findStrict("ti.sdo.ipc.Ipc.Entry", "ti.sdo.ipc"), $$DEFAULT);
        // fxn Ipc.getObjTypeStr$view
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.Ipc$$getObjTypeStr$view", new Proto.Fxn(om.findStrict("ti.sdo.ipc.Ipc.Module", "ti.sdo.ipc"), $$T_Str, 1, 1, false));
                fxn.addArg(0, "type", (Proto)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc"), $$UNDEF);
    }

    void Notify$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GateMP_RemoteSystemProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GateMP_RemoteCustom1Proxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GateMP_RemoteCustom2Proxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void MessageQ_SetupTransportProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Notify_SetupProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Notify_Module_GateProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Build$$SIZES()
    {
    }

    void GateMP$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.GateMP.Reserved", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("version", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.GateMP.Reserved']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.GateMP.Reserved']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.GateMP.Reserved'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.GateMP.LocalGate", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("localGate", "UPtr"));
        sizes.add(Global.newArray("refCount", "TInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.GateMP.LocalGate']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.GateMP.LocalGate']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.GateMP.LocalGate'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.GateMP.Attrs", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("mask", "UInt16"));
        sizes.add(Global.newArray("creatorProcId", "UInt16"));
        sizes.add(Global.newArray("arg", "UInt32"));
        sizes.add(Global.newArray("status", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.GateMP.Attrs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.GateMP.Attrs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.GateMP.Attrs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.GateMP.Instance_State", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("remoteProtect", "Nti.sdo.ipc.GateMP.RemoteProtect;;0;1;2;3"));
        sizes.add(Global.newArray("localProtect", "Nti.sdo.ipc.GateMP.LocalProtect;;0;1;2;3;4"));
        sizes.add(Global.newArray("nsKey", "UPtr"));
        sizes.add(Global.newArray("numOpens", "TInt"));
        sizes.add(Global.newArray("cacheEnabled", "UShort"));
        sizes.add(Global.newArray("attrs", "UPtr"));
        sizes.add(Global.newArray("regionId", "UInt16"));
        sizes.add(Global.newArray("allocSize", "USize"));
        sizes.add(Global.newArray("objType", "Nti.sdo.ipc.Ipc.ObjType;;0x1;0x2;0x4;0x8;0x10;0x20"));
        sizes.add(Global.newArray("proxyAttrs", "UPtr"));
        sizes.add(Global.newArray("resourceId", "UInt"));
        sizes.add(Global.newArray("gateHandle", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.GateMP.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.GateMP.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.GateMP.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.GateMP.Module_State", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("nameServer", "UPtr"));
        sizes.add(Global.newArray("numRemoteSystem", "TInt"));
        sizes.add(Global.newArray("numRemoteCustom1", "TInt"));
        sizes.add(Global.newArray("numRemoteCustom2", "TInt"));
        sizes.add(Global.newArray("remoteSystemInUse", "UPtr"));
        sizes.add(Global.newArray("remoteCustom1InUse", "UPtr"));
        sizes.add(Global.newArray("remoteCustom2InUse", "UPtr"));
        sizes.add(Global.newArray("remoteSystemGates", "UPtr"));
        sizes.add(Global.newArray("remoteCustom1Gates", "UPtr"));
        sizes.add(Global.newArray("remoteCustom2Gates", "UPtr"));
        sizes.add(Global.newArray("gateAll", "UPtr"));
        sizes.add(Global.newArray("gateSwi", "UPtr"));
        sizes.add(Global.newArray("gateMutexPri", "UPtr"));
        sizes.add(Global.newArray("gateNull", "UPtr"));
        sizes.add(Global.newArray("defaultGate", "UPtr"));
        sizes.add(Global.newArray("nsKey", "UPtr"));
        sizes.add(Global.newArray("hostSupport", "UShort"));
        sizes.add(Global.newArray("proxyMap", "A3;TInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.GateMP.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.GateMP.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.GateMP.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void MessageQ$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.MessageQ.MsgHeader", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("reserved0", "UInt32"));
        sizes.add(Global.newArray("reserved1", "UInt32"));
        sizes.add(Global.newArray("msgSize", "UInt32"));
        sizes.add(Global.newArray("flags", "UInt16"));
        sizes.add(Global.newArray("msgId", "UInt16"));
        sizes.add(Global.newArray("dstId", "UInt16"));
        sizes.add(Global.newArray("dstProc", "UInt16"));
        sizes.add(Global.newArray("replyId", "UInt16"));
        sizes.add(Global.newArray("replyProc", "UInt16"));
        sizes.add(Global.newArray("srcProc", "UInt16"));
        sizes.add(Global.newArray("heapId", "UInt16"));
        sizes.add(Global.newArray("seqNum", "UInt16"));
        sizes.add(Global.newArray("reserved", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.MessageQ.MsgHeader']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.MessageQ.MsgHeader']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.MessageQ.MsgHeader'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.MessageQ.HeapEntry", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("heap", "UPtr"));
        sizes.add(Global.newArray("heapId", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.MessageQ.HeapEntry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.MessageQ.HeapEntry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.MessageQ.HeapEntry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.MessageQ.TransportEntry", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("transport", "UPtr"));
        sizes.add(Global.newArray("procId", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.MessageQ.TransportEntry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.MessageQ.TransportEntry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.MessageQ.TransportEntry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.MessageQ.RegisteredTransport", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("transport", "UPtr"));
        sizes.add(Global.newArray("type", "Nti.sdo.ipc.MessageQ.TransportType;;;;"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.MessageQ.RegisteredTransport']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.MessageQ.RegisteredTransport']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.MessageQ.RegisteredTransport'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.MessageQ.Instance_State", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("queue", "UInt32"));
        sizes.add(Global.newArray("synchronizer", "UPtr"));
        sizes.add(Global.newArray("nsKey", "UPtr"));
        sizes.add(Global.newArray("syncSemHandle", "UPtr"));
        sizes.add(Global.newArray("unblocked", "UShort"));
        sizes.add(Global.newArray("normalList", "Sti.sdo.utils.List;Instance_State"));
        sizes.add(Global.newArray("highList", "Sti.sdo.utils.List;Instance_State"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.MessageQ.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.MessageQ.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.MessageQ.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.MessageQ.Module_State", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("transports", "Sxdc.runtime.Types;Vec"));
        sizes.add(Global.newArray("queues", "UPtr"));
        sizes.add(Global.newArray("heaps", "UPtr"));
        sizes.add(Global.newArray("gate", "UPtr"));
        sizes.add(Global.newArray("numQueues", "UInt16"));
        sizes.add(Global.newArray("numHeaps", "UInt16"));
        sizes.add(Global.newArray("nameServer", "UPtr"));
        sizes.add(Global.newArray("freeHookFxn", "UFxn"));
        sizes.add(Global.newArray("putHookFxn", "UFxn"));
        sizes.add(Global.newArray("canFreeQueues", "UShort"));
        sizes.add(Global.newArray("seqNum", "UInt16"));
        sizes.add(Global.newArray("regTrans", "A8;Sti.sdo.ipc.MessageQ;RegisteredTransport"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.MessageQ.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.MessageQ.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.MessageQ.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void SharedRegion$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.SharedRegion.Entry", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("base", "UPtr"));
        sizes.add(Global.newArray("len", "USize"));
        sizes.add(Global.newArray("ownerProcId", "UInt16"));
        sizes.add(Global.newArray("isValid", "UShort"));
        sizes.add(Global.newArray("cacheEnable", "UShort"));
        sizes.add(Global.newArray("cacheLineSize", "USize"));
        sizes.add(Global.newArray("createHeap", "UShort"));
        sizes.add(Global.newArray("name", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.SharedRegion.Entry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.SharedRegion.Entry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.SharedRegion.Entry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.SharedRegion.Region", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("entry", "Sti.sdo.ipc.SharedRegion;Entry"));
        sizes.add(Global.newArray("reservedSize", "USize"));
        sizes.add(Global.newArray("heap", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.SharedRegion.Region']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.SharedRegion.Region']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.SharedRegion.Region'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.SharedRegion.Module_State", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("regions", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.SharedRegion.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.SharedRegion.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.SharedRegion.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void ListMP$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.ListMP.Elem", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("next", "UInt32"));
        sizes.add(Global.newArray("prev", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.ListMP.Elem']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.ListMP.Elem']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.ListMP.Elem'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.ListMP.Attrs", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("status", "UInt32"));
        sizes.add(Global.newArray("gateMPAddr", "UInt32"));
        sizes.add(Global.newArray("head", "Sti.sdo.ipc.ListMP;Elem"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.ListMP.Attrs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.ListMP.Attrs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.ListMP.Attrs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.ListMP.Instance_State", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("attrs", "UPtr"));
        sizes.add(Global.newArray("nsKey", "UPtr"));
        sizes.add(Global.newArray("objType", "Nti.sdo.ipc.Ipc.ObjType;;0x1;0x2;0x4;0x8;0x10;0x20"));
        sizes.add(Global.newArray("gate", "UPtr"));
        sizes.add(Global.newArray("allocSize", "USize"));
        sizes.add(Global.newArray("regionId", "UInt16"));
        sizes.add(Global.newArray("cacheEnabled", "UShort"));
        sizes.add(Global.newArray("cacheLineSize", "USize"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.ListMP.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.ListMP.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.ListMP.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.ListMP.Module_State", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("nameServer", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.ListMP.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.ListMP.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.ListMP.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Ipc$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.Ipc.Entry", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        sizes.add(Global.newArray("setupNotify", "UShort"));
        sizes.add(Global.newArray("setupMessageQ", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.Ipc.Entry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.Ipc.Entry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.Ipc.Entry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.Ipc.UserFxn", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("attach", "UFxn"));
        sizes.add(Global.newArray("detach", "UFxn"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.Ipc.UserFxn']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.Ipc.UserFxn']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.Ipc.UserFxn'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.Ipc.ConfigEntry", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("remoteProcId", "UInt32"));
        sizes.add(Global.newArray("localProcId", "UInt32"));
        sizes.add(Global.newArray("tag", "UInt32"));
        sizes.add(Global.newArray("size", "UInt32"));
        sizes.add(Global.newArray("next", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.Ipc.ConfigEntry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.Ipc.ConfigEntry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.Ipc.ConfigEntry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.Ipc.ProcEntry", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("localConfigList", "UPtr"));
        sizes.add(Global.newArray("remoteConfigList", "UPtr"));
        sizes.add(Global.newArray("attached", "UInt"));
        sizes.add(Global.newArray("entry", "Sti.sdo.ipc.Ipc;Entry"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.Ipc.ProcEntry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.Ipc.ProcEntry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.Ipc.ProcEntry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.Ipc.Reserved", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("startedKey", "UInt32"));
        sizes.add(Global.newArray("notifySRPtr", "UInt32"));
        sizes.add(Global.newArray("nsrnSRPtr", "UInt32"));
        sizes.add(Global.newArray("transportSRPtr", "UInt32"));
        sizes.add(Global.newArray("configListHead", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.Ipc.Reserved']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.Ipc.Reserved']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.Ipc.Reserved'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.Ipc.UserFxnAndArg", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("userFxn", "Sti.sdo.ipc.Ipc;UserFxn"));
        sizes.add(Global.newArray("arg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.Ipc.UserFxnAndArg']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.Ipc.UserFxnAndArg']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.Ipc.UserFxnAndArg'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.Ipc.Module_State", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("ipcSharedAddr", "UPtr"));
        sizes.add(Global.newArray("gateMPSharedAddr", "UPtr"));
        sizes.add(Global.newArray("procEntry", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.Ipc.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.Ipc.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.Ipc.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Notify$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.Notify.EventCallback", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("fnNotifyCbck", "UFxn"));
        sizes.add(Global.newArray("cbckArg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.Notify.EventCallback']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.Notify.EventCallback']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.Notify.EventCallback'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.Notify.EventListener", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("element", "Sti.sdo.utils.List;Elem"));
        sizes.add(Global.newArray("callback", "Sti.sdo.ipc.Notify;EventCallback"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.Notify.EventListener']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.Notify.EventListener']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.Notify.EventListener'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.Notify.Instance_State", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("nesting", "UInt"));
        sizes.add(Global.newArray("driverHandle", "UPtr"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        sizes.add(Global.newArray("lineId", "UInt16"));
        sizes.add(Global.newArray("callbacks", "UPtr"));
        sizes.add(Global.newArray("eventList", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.Notify.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.Notify.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.Notify.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.Notify.Module_State", "ti.sdo.ipc");
        sizes.clear();
        sizes.add(Global.newArray("notifyHandles", "UPtr"));
        sizes.add(Global.newArray("localEnableMask", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.Notify.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.Notify.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.Notify.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void GateMP_RemoteSystemProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void GateMP_RemoteCustom1Proxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void GateMP_RemoteCustom2Proxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void MessageQ_SetupTransportProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Notify_SetupProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Notify_Module_GateProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Build$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/Build.xs");
        om.bind("ti.sdo.ipc.Build$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Build.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Build.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("libType", (Proto)om.findStrict("ti.sdo.ipc.Build.LibType", "ti.sdo.ipc"), $$UNDEF, "wh");
        po.addFld("customCCOpts", $$T_Str, $$UNDEF, "wh");
        po.addFld("assertsEnabled", $$T_Bool, true, "wh");
        po.addFld("logsEnabled", $$T_Bool, true, "wh");
        po.addFld("libDir", $$T_Str, null, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.Build$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.Build$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.Build$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("getCCOpts", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Build$$getCCOpts", "ti.sdo.ipc"), Global.get(cap, "getCCOpts"));
                po.addFxn("getDefaultCustomCCOpts", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Build$$getDefaultCustomCCOpts", "ti.sdo.ipc"), Global.get(cap, "getDefaultCustomCCOpts"));
                po.addFxn("getDefs", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Build$$getDefs", "ti.sdo.ipc"), Global.get(cap, "getDefs"));
                po.addFxn("getCFiles", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Build$$getCFiles", "ti.sdo.ipc"), Global.get(cap, "getCFiles"));
                po.addFxn("getAsmFiles", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Build$$getAsmFiles", "ti.sdo.ipc"), Global.get(cap, "getAsmFiles"));
                po.addFxn("buildLibs", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Build$$buildLibs", "ti.sdo.ipc"), Global.get(cap, "buildLibs"));
                po.addFxn("getLibs", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Build$$getLibs", "ti.sdo.ipc"), Global.get(cap, "getLibs"));
    }

    void GateMP$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/GateMP.xs");
        om.bind("ti.sdo.ipc.GateMP$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("VERSION", Proto.Elm.newCNum("(xdc_UInt32)"), 1L, "rh");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x11202009L, "rh");
                po.addFld("ProxyOrder_SYSTEM", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("ProxyOrder_CUSTOM1", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("ProxyOrder_CUSTOM2", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("ProxyOrder_NUM", Proto.Elm.newCNum("(xdc_Int)"), 3L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc"), $$UNDEF, "wh");
            po.addFld("E_gateUnavailable", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc"), Global.newObject("msg", "E_gateUnavailable: No gates of requested type are available"), "w");
            po.addFld("E_localGate", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc"), Global.newObject("msg", "E_localGate: Only creator can open local Gate"), "w");
            po.addFld("A_invalidClose", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_invalidClose: Calling GateMP_close with the wrong handle"), "w");
            po.addFld("A_invalidDelete", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_invalidDelete: Calling GateMP_delete incorrectly"), "w");
            po.addFld("LM_enter", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_enter: Gate (remoteGate = %d, resourceId = %d) entered, returning key = %d"), "w");
            po.addFld("LM_leave", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_leave: Gate (remoteGate = %d, resourceId = %d) left using key = %d"), "w");
            po.addFld("LM_create", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_create: Gate (remoteGate = %d, resourceId = %d) created"), "w");
            po.addFld("LM_open", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_open: Remote gate (remoteGate = %d, resourceId = %d) opened"), "w");
            po.addFld("LM_delete", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_delete: Gate (remoteGate = %d, resourceId = %d) deleted"), "w");
            po.addFld("LM_close", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_close: Gate (remoteGate = %d, resourceId = %d) closed"), "w");
            po.addFld("maxRuntimeEntries", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "wh");
            po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "w");
            po.addFld("hostSupport", $$T_Bool, false, "wh");
            po.addFld("tableSection", $$T_Str, null, "wh");
            po.addFldV("RemoteSystemProxy", (Proto)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc"), null, "wh", $$delegGet, $$delegSet);
            po.addFldV("RemoteCustom1Proxy", (Proto)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc"), null, "wh", $$delegGet, $$delegSet);
            po.addFldV("RemoteCustom2Proxy", (Proto)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc"), null, "wh", $$delegGet, $$delegSet);
            po.addFld("nameSrvPrms", (Proto)om.findStrict("ti.sdo.utils.NameServer.Params", "ti.sdo.ipc"), $$DEFAULT, "wh");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.GateMP$$create", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$GateMP$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.GateMP$$construct", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$GateMP$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.GateMP$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.GateMP$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.GateMP$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.GateMP$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.GateMP$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.GateMP$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP.Instance", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("VERSION", Proto.Elm.newCNum("(xdc_UInt32)"), 1L, "rh");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x11202009L, "rh");
                po.addFld("ProxyOrder_SYSTEM", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("ProxyOrder_CUSTOM1", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("ProxyOrder_CUSTOM2", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("ProxyOrder_NUM", Proto.Elm.newCNum("(xdc_Int)"), 3L, "rh");
        if (isCFG) {
            po.addFld("name", $$T_Str, null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("resourceId", Proto.Elm.newCNum("(xdc_Bits32)"), 0L, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("localProtect", (Proto)om.findStrict("ti.sdo.ipc.GateMP.LocalProtect", "ti.sdo.ipc"), om.find("ti.sdo.ipc.GateMP.LocalProtect_THREAD"), "w");
            po.addFld("remoteProtect", (Proto)om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect", "ti.sdo.ipc"), om.find("ti.sdo.ipc.GateMP.RemoteProtect_SYSTEM"), "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$Params", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("VERSION", Proto.Elm.newCNum("(xdc_UInt32)"), 1L, "rh");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x11202009L, "rh");
                po.addFld("ProxyOrder_SYSTEM", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("ProxyOrder_CUSTOM1", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("ProxyOrder_CUSTOM2", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("ProxyOrder_NUM", Proto.Elm.newCNum("(xdc_Int)"), 3L, "rh");
        if (isCFG) {
            po.addFld("name", $$T_Str, null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("resourceId", Proto.Elm.newCNum("(xdc_Bits32)"), 0L, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("localProtect", (Proto)om.findStrict("ti.sdo.ipc.GateMP.LocalProtect", "ti.sdo.ipc"), om.find("ti.sdo.ipc.GateMP.LocalProtect_THREAD"), "w");
            po.addFld("remoteProtect", (Proto)om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect", "ti.sdo.ipc"), om.find("ti.sdo.ipc.GateMP.RemoteProtect_SYSTEM"), "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$Object", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP.Object", om.findStrict("ti.sdo.ipc.GateMP.Instance", "ti.sdo.ipc"));
        // struct GateMP.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$BasicView", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("remoteProtect", $$T_Str, $$UNDEF, "w");
                po.addFld("remoteStatus", $$T_Str, $$UNDEF, "w");
                po.addFld("localProtect", $$T_Str, $$UNDEF, "w");
                po.addFld("numOpens", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("resourceId", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("creatorProcId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("objType", $$T_Str, $$UNDEF, "w");
        // struct GateMP.ModuleView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$ModuleView", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("numGatesSystem", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numUsedSystem", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numGatesCustom1", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numUsedCustom1", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numGatesCustom2", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numUsedCustom2", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        // struct GateMP.Reserved
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$Reserved", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP.Reserved", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("version", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct GateMP.LocalGate
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$LocalGate", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP.LocalGate", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("refCount", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
        // struct GateMP.Attrs
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$Attrs", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP.Attrs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("mask", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("creatorProcId", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("arg", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("status", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct GateMP.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$Instance_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("remoteProtect", (Proto)om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("localProtect", (Proto)om.findStrict("ti.sdo.ipc.GateMP.LocalProtect", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("nsKey", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("numOpens", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("attrs", new Proto.Adr("ti_sdo_ipc_GateMP_Attrs*", "PS"), $$UNDEF, "w");
                po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("allocSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("objType", (Proto)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("proxyAttrs", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("resourceId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("gateHandle", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
        // struct GateMP.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$Module_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("nameServer", (Proto)om.findStrict("ti.sdo.utils.NameServer.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("numRemoteSystem", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("numRemoteCustom1", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("numRemoteCustom2", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("remoteSystemInUse", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt8)"), false), $$DEFAULT, "w");
                po.addFld("remoteCustom1InUse", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt8)"), false), $$DEFAULT, "w");
                po.addFld("remoteCustom2InUse", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt8)"), false), $$DEFAULT, "w");
                po.addFld("remoteSystemGates", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc"), false), $$DEFAULT, "w");
                po.addFld("remoteCustom1Gates", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc"), false), $$DEFAULT, "w");
                po.addFld("remoteCustom2Gates", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc"), false), $$DEFAULT, "w");
                po.addFld("gateAll", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("gateSwi", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("gateMutexPri", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("gateNull", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("defaultGate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("nsKey", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("hostSupport", $$T_Bool, $$UNDEF, "w");
                po.addFld("proxyMap", new Proto.Arr(Proto.Elm.newCNum("(xdc_Int)"), false, xdc.services.intern.xsr.Enum.intValue(3L)), $$DEFAULT, "w");
    }

    void MessageQ$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/MessageQ.xs");
        om.bind("ti.sdo.ipc.MessageQ$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NORMALPRI", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "rh");
                po.addFld("HIGHPRI", Proto.Elm.newCNum("(xdc_UInt)"), 1L, "rh");
                po.addFld("RESERVEDPRI", Proto.Elm.newCNum("(xdc_UInt)"), 2L, "rh");
                po.addFld("URGENTPRI", Proto.Elm.newCNum("(xdc_UInt)"), 3L, "rh");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_Bits16)"), Global.eval("~(0)"), "rh");
                po.addFld("VERSIONMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0xE000L, "rh");
                po.addFld("HEADERVERSION", Proto.Elm.newCNum("(xdc_UInt)"), 0x2000L, "rh");
                po.addFld("TRACEMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0x1000L, "rh");
                po.addFld("TRACESHIFT", Proto.Elm.newCNum("(xdc_UInt)"), 12L, "rh");
                po.addFld("PRIORITYMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0x3L, "rh");
                po.addFld("TRANSPORTPRIORITYMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0x1L, "rh");
                po.addFld("PROXY_FAILURE", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("STATICMSG", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc"), $$UNDEF, "wh");
            po.addFld("LM_setTrace", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_setTrace: Message 0x%x (seqNum = %d, srcProc = %d) traceFlag = %d"), "w");
            po.addFld("LM_alloc", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_alloc: Message 0x%x (seqNum = %d, srcProc = %d) was allocated"), "w");
            po.addFld("LM_staticMsgInit", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_staticMsgInit: Message 0x%x (seqNum = %d, srcProc = %d) was set in MessageQ_staticMsgInit"), "w");
            po.addFld("LM_free", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_free: Message 0x%x (seqNum = %d, srcProc = %d) was freed"), "w");
            po.addFld("LM_putLocal", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_putLocal: Message 0x%x (seqNum = %d, srcProc = %d) was placed onto queue 0x%x"), "w");
            po.addFld("LM_putRemote", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_putRemote: Message 0x%x (seqNum = %d, srcProc = %d) was given to processor %d transport"), "w");
            po.addFld("LM_rcvByTransport", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_rcvByTransport: Message 0x%x (seqNum = %d, srcProc = %d) was received"), "w");
            po.addFld("LM_get", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc"), Global.newObject("mask", 0x0100L, "msg", "LM_get: Message 0x%x (seqNum = %d, srcProc = %d) was received by queue 0x%x"), "w");
            po.addFldV("SetupTransportProxy", (Proto)om.findStrict("ti.sdo.ipc.interfaces.ITransportSetup.Module", "ti.sdo.ipc"), null, "wh", $$delegGet, $$delegSet);
            po.addFld("A_invalidContext", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_invalidContext: Cannot call with an open/create handle"), "w");
            po.addFld("A_cannotFreeStaticMsg", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_cannotFreeStaticMsg: Cannot call MessageQ_free with static msg"), "w");
            po.addFld("A_invalidMsg", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_invalidMsg: Invalid message"), "w");
            po.addFld("A_invalidQueueId", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_invalidQueueId: Invalid queueId is used"), "w");
            po.addFld("A_heapIdInvalid", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_heapIdInvalid: heapId is invalid"), "w");
            po.addFld("A_procIdInvalid", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_procIdInvalid: procId is invalid"), "w");
            po.addFld("A_invalidObj", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_invalidObj: an invalid obj is used"), "w");
            po.addFld("A_invalidParam", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_invalidParam: an invalid parameter was passed in"), "w");
            po.addFld("A_unregisteredTransport", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_unregisteredTransport: transport is not registered"), "w");
            po.addFld("A_invalidUnblock", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_invalidUnblock: Trying to unblock a remote MessageQ or a queue with non-blocking synchronizer"), "w");
            po.addFld("E_maxReached", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc"), Global.newObject("msg", "E_maxReached: All objects in use. MessageQ.maxRuntimeEntries is %d"), "w");
            po.addFld("E_unregisterHeapId", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc"), Global.newObject("msg", "E_unregisterHeapId: Heap id %d not registered"), "w");
            po.addFld("E_nameFailed", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc"), Global.newObject("msg", "E_nameFailed: '%s' name failed to be added to NameServer"), "w");
            po.addFld("E_indexNotAvailable", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc"), Global.newObject("msg", "E_indexNotAvailable: queueIndex %d not available"), "w");
            po.addFld("traceFlag", $$T_Bool, false, "w");
            po.addFld("numHeaps", Proto.Elm.newCNum("(xdc_UInt16)"), 8L, "w");
            po.addFld("maxRuntimeEntries", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "w");
            po.addFld("numReservedEntries", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("nameTableGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc"), null, "w");
            po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "w");
            po.addFld("tableSection", $$T_Str, null, "wh");
            po.addFld("freeHookFxn", new Proto.Adr("xdc_Void(*)(xdc_Bits16,xdc_Bits16)", "PFv"), null, "w");
            po.addFld("putHookFxn", new Proto.Adr("xdc_Void(*)(xdc_Bits32,xdc_Ptr)", "PFv"), null, "w");
            po.addFld("nameSrvPrms", (Proto)om.findStrict("ti.sdo.utils.NameServer.Params", "ti.sdo.ipc"), $$DEFAULT, "wh");
            po.addFld("staticHeaps", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.MessageQ.HeapEntry", "ti.sdo.ipc"), false), $$DEFAULT, "wh");
            po.addFld("staticTransports", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.MessageQ.TransportEntry", "ti.sdo.ipc"), false), $$DEFAULT, "wh");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.MessageQ$$create", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$MessageQ$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.MessageQ$$construct", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$MessageQ$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.MessageQ$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.MessageQ$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.MessageQ$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.MessageQ$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.MessageQ$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.MessageQ$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                po.addFxn("registerHeapMeta", (Proto.Fxn)om.findStrict("ti.sdo.ipc.MessageQ$$registerHeapMeta", "ti.sdo.ipc"), Global.get(cap, "registerHeapMeta"));
                po.addFxn("registerTransportMeta", (Proto.Fxn)om.findStrict("ti.sdo.ipc.MessageQ$$registerTransportMeta", "ti.sdo.ipc"), Global.get(cap, "registerTransportMeta"));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ.Instance", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NORMALPRI", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "rh");
                po.addFld("HIGHPRI", Proto.Elm.newCNum("(xdc_UInt)"), 1L, "rh");
                po.addFld("RESERVEDPRI", Proto.Elm.newCNum("(xdc_UInt)"), 2L, "rh");
                po.addFld("URGENTPRI", Proto.Elm.newCNum("(xdc_UInt)"), 3L, "rh");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_Bits16)"), Global.eval("~(0)"), "rh");
                po.addFld("VERSIONMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0xE000L, "rh");
                po.addFld("HEADERVERSION", Proto.Elm.newCNum("(xdc_UInt)"), 0x2000L, "rh");
                po.addFld("TRACEMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0x1000L, "rh");
                po.addFld("TRACESHIFT", Proto.Elm.newCNum("(xdc_UInt)"), 12L, "rh");
                po.addFld("PRIORITYMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0x3L, "rh");
                po.addFld("TRANSPORTPRIORITYMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0x1L, "rh");
                po.addFld("PROXY_FAILURE", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("STATICMSG", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "rh");
        if (isCFG) {
            po.addFld("synchronizer", (Proto)om.findStrict("xdc.runtime.knl.ISync.Handle", "ti.sdo.ipc"), null, "w");
            po.addFld("queueIndex", Proto.Elm.newCNum("(xdc_UInt16)"), Global.eval("~(0)"), "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$Params", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NORMALPRI", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "rh");
                po.addFld("HIGHPRI", Proto.Elm.newCNum("(xdc_UInt)"), 1L, "rh");
                po.addFld("RESERVEDPRI", Proto.Elm.newCNum("(xdc_UInt)"), 2L, "rh");
                po.addFld("URGENTPRI", Proto.Elm.newCNum("(xdc_UInt)"), 3L, "rh");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_Bits16)"), Global.eval("~(0)"), "rh");
                po.addFld("VERSIONMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0xE000L, "rh");
                po.addFld("HEADERVERSION", Proto.Elm.newCNum("(xdc_UInt)"), 0x2000L, "rh");
                po.addFld("TRACEMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0x1000L, "rh");
                po.addFld("TRACESHIFT", Proto.Elm.newCNum("(xdc_UInt)"), 12L, "rh");
                po.addFld("PRIORITYMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0x3L, "rh");
                po.addFld("TRANSPORTPRIORITYMASK", Proto.Elm.newCNum("(xdc_UInt)"), 0x1L, "rh");
                po.addFld("PROXY_FAILURE", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("STATICMSG", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "rh");
        if (isCFG) {
            po.addFld("synchronizer", (Proto)om.findStrict("xdc.runtime.knl.ISync.Handle", "ti.sdo.ipc"), null, "w");
            po.addFld("queueIndex", Proto.Elm.newCNum("(xdc_UInt16)"), Global.eval("~(0)"), "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$Object", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.Object", om.findStrict("ti.sdo.ipc.MessageQ.Instance", "ti.sdo.ipc"));
        // struct MessageQ.QueuesView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$QueuesView", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.QueuesView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("queueId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("reserved", $$T_Bool, $$UNDEF, "w");
        // struct MessageQ.MessagesView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$MessagesView", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.MessagesView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("seqNum", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("msgSize", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("priority", $$T_Str, $$UNDEF, "w");
                po.addFld("srcProc", $$T_Str, $$UNDEF, "w");
                po.addFld("replyProc", $$T_Str, $$UNDEF, "w");
                po.addFld("replyId", $$T_Str, $$UNDEF, "w");
                po.addFld("msgId", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("heap", $$T_Str, $$UNDEF, "w");
                po.addFld("traceEnabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("version", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
        // struct MessageQ.ModuleView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$ModuleView", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("heaps", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
                po.addFld("gate", $$T_Str, $$UNDEF, "w");
                po.addFld("nextSeqNum", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("freeHookFxn", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
        // typedef MessageQ.FreeHookFxn
        om.bind("ti.sdo.ipc.MessageQ.FreeHookFxn", new Proto.Adr("xdc_Void(*)(xdc_Bits16,xdc_Bits16)", "PFv"));
        // typedef MessageQ.PutHookFxn
        om.bind("ti.sdo.ipc.MessageQ.PutHookFxn", new Proto.Adr("xdc_Void(*)(xdc_Bits32,xdc_Ptr)", "PFv"));
        // typedef MessageQ.QueueId
        om.bind("ti.sdo.ipc.MessageQ.QueueId", Proto.Elm.newCNum("(xdc_UInt32)"));
        // struct MessageQ.MsgHeader
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$MsgHeader", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.MsgHeader", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("reserved0", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("reserved1", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("msgSize", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("flags", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("msgId", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("dstId", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("dstProc", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("replyId", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("replyProc", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("srcProc", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("heapId", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("seqNum", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("reserved", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
        // struct MessageQ.HeapEntry
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$HeapEntry", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.HeapEntry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("heap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("heapId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
        // struct MessageQ.TransportEntry
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$TransportEntry", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.TransportEntry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("transport", (Proto)om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
        // struct MessageQ.RegisteredTransport
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$RegisteredTransport", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.RegisteredTransport", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("transport", (Proto)om.findStrict("ti.sdo.ipc.interfaces.ITransport.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("type", (Proto)om.findStrict("ti.sdo.ipc.MessageQ.TransportType", "ti.sdo.ipc"), $$UNDEF, "w");
        // struct MessageQ.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$Instance_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("queue", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("synchronizer", (Proto)om.findStrict("xdc.runtime.knl.ISync.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("nsKey", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("syncSemHandle", (Proto)om.findStrict("ti.sysbios.syncs.SyncSem.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("unblocked", $$T_Bool, $$UNDEF, "w");
                po.addFldV("normalList", (Proto)om.findStrict("ti.sdo.utils.List.Object", "ti.sdo.ipc"), $$DEFAULT, "wh", $$objFldGet, $$objFldSet);
                po.addFld("Object_field_normalList", (Proto)om.findStrict("ti.sdo.utils.List.Object", "ti.sdo.ipc"), $$DEFAULT, "w");
                po.addFldV("highList", (Proto)om.findStrict("ti.sdo.utils.List.Object", "ti.sdo.ipc"), $$DEFAULT, "wh", $$objFldGet, $$objFldSet);
                po.addFld("Object_field_highList", (Proto)om.findStrict("ti.sdo.utils.List.Object", "ti.sdo.ipc"), $$DEFAULT, "w");
        // struct MessageQ.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$Module_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("transports", new Proto.Arr(new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Handle", "ti.sdo.ipc"), false, xdc.services.intern.xsr.Enum.intValue(2L)), true), $$DEFAULT, "w");
                po.addFld("queues", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.MessageQ.Handle", "ti.sdo.ipc"), false), $$DEFAULT, "w");
                po.addFld("heaps", new Proto.Arr((Proto)om.findStrict("xdc.runtime.IHeap.Handle", "ti.sdo.ipc"), false), $$DEFAULT, "w");
                po.addFld("gate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("numQueues", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("numHeaps", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("nameServer", (Proto)om.findStrict("ti.sdo.utils.NameServer.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("freeHookFxn", new Proto.Adr("xdc_Void(*)(xdc_Bits16,xdc_Bits16)", "PFv"), $$UNDEF, "w");
                po.addFld("putHookFxn", new Proto.Adr("xdc_Void(*)(xdc_Bits32,xdc_Ptr)", "PFv"), $$UNDEF, "w");
                po.addFld("canFreeQueues", $$T_Bool, $$UNDEF, "w");
                po.addFld("seqNum", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("regTrans", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.MessageQ.RegisteredTransport", "ti.sdo.ipc"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
    }

    void SharedRegion$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/SharedRegion.xs");
        om.bind("ti.sdo.ipc.SharedRegion$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.SharedRegion.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.SharedRegion.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("INVALIDREGIONID", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "rh");
                po.addFld("DEFAULTOWNERID", Proto.Elm.newCNum("(xdc_UInt16)"), Global.eval("~0"), "rh");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x08111963L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc"), $$UNDEF, "wh");
            po.addFld("A_idTooLarge", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_idTooLarge: id cannot be larger than numEntries"), "w");
            po.addFld("A_addrOutOfRange", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_addrOutOfRange: Address is out of region id's range"), "w");
            po.addFld("A_region0Clear", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_region0Clear: Region 0 cannot be cleared"), "w");
            po.addFld("A_region0Invalid", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_region0Invalid: Region zero is invalid"), "w");
            po.addFld("A_regionInvalid", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_regionInvalid: Region is invalid"), "w");
            po.addFld("A_reserveTooMuch", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_reserveTooMuch: Trying to reserve too much memory"), "w");
            po.addFld("A_cacheLineSizeIsZero", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_cacheLineSizeIsZero: cache line size cannot be zero"), "w");
            po.addFld("A_overlap", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_overlap: Shared region overlaps"), "w");
            po.addFld("A_alreadyExists", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_alreadyExists: Trying to overwrite an existing valid entry"), "w");
            po.addFld("A_noHeap", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_noHeap: Region has no heap"), "w");
            po.addFld("cacheLineSize", Proto.Elm.newCNum("(xdc_SizeT)"), 128L, "w");
            po.addFld("numEntries", Proto.Elm.newCNum("(xdc_UInt16)"), 4L, "w");
            po.addFld("translate", $$T_Bool, true, "w");
            po.addFld("INVALIDSRPTR", Proto.Elm.newCNum("(xdc_Bits32)"), 0xFFFFFFFFL, "w");
            po.addFld("entry", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.SharedRegion.Entry", "ti.sdo.ipc"), false), $$DEFAULT, "wh");
            po.addFld("genSectionInLinkCmd", new Proto.Arr($$T_Bool, false), $$DEFAULT, "wh");
            po.addFld("entryCount", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
            po.addFld("numOffsetBits", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
            po.addFld("offsetMask", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.SharedRegion$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.SharedRegion$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.SharedRegion$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.SharedRegion$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("genSectionInCmd", (Proto.Fxn)om.findStrict("ti.sdo.ipc.SharedRegion$$genSectionInCmd", "ti.sdo.ipc"), Global.get(cap, "genSectionInCmd"));
                po.addFxn("getCacheLineSizeMeta", (Proto.Fxn)om.findStrict("ti.sdo.ipc.SharedRegion$$getCacheLineSizeMeta", "ti.sdo.ipc"), Global.get(cap, "getCacheLineSizeMeta"));
                po.addFxn("getIdMeta", (Proto.Fxn)om.findStrict("ti.sdo.ipc.SharedRegion$$getIdMeta", "ti.sdo.ipc"), Global.get(cap, "getIdMeta"));
                po.addFxn("getPtrMeta", (Proto.Fxn)om.findStrict("ti.sdo.ipc.SharedRegion$$getPtrMeta", "ti.sdo.ipc"), Global.get(cap, "getPtrMeta"));
                po.addFxn("getPtrMeta$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.SharedRegion$$getPtrMeta$view", "ti.sdo.ipc"), Global.get(cap, "getPtrMeta$view"));
                po.addFxn("getSRPtrMeta", (Proto.Fxn)om.findStrict("ti.sdo.ipc.SharedRegion$$getSRPtrMeta", "ti.sdo.ipc"), Global.get(cap, "getSRPtrMeta"));
                po.addFxn("getSRPtrMeta$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.SharedRegion$$getSRPtrMeta$view", "ti.sdo.ipc"), Global.get(cap, "getSRPtrMeta$view"));
                po.addFxn("isCacheEnabledMeta", (Proto.Fxn)om.findStrict("ti.sdo.ipc.SharedRegion$$isCacheEnabledMeta", "ti.sdo.ipc"), Global.get(cap, "isCacheEnabledMeta"));
                po.addFxn("setEntryMeta", (Proto.Fxn)om.findStrict("ti.sdo.ipc.SharedRegion$$setEntryMeta", "ti.sdo.ipc"), Global.get(cap, "setEntryMeta"));
        // struct SharedRegion.RegionView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.SharedRegion$$RegionView", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.SharedRegion.RegionView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("id", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("base", $$T_Str, $$UNDEF, "w");
                po.addFld("end", $$T_Str, $$UNDEF, "w");
                po.addFld("len", $$T_Str, $$UNDEF, "w");
                po.addFld("ownerProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("cacheEnable", $$T_Bool, $$UNDEF, "w");
                po.addFld("isValid", $$T_Bool, $$UNDEF, "w");
                po.addFld("cacheLineSize", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("reservedSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("heap", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
        // typedef SharedRegion.SRPtr
        om.bind("ti.sdo.ipc.SharedRegion.SRPtr", Proto.Elm.newCNum("(xdc_Bits32)"));
        // struct SharedRegion.Entry
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.SharedRegion$$Entry", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.SharedRegion.Entry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("base", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("len", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("ownerProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("isValid", $$T_Bool, $$UNDEF, "w");
                po.addFld("cacheEnable", $$T_Bool, $$UNDEF, "w");
                po.addFld("cacheLineSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("createHeap", $$T_Bool, $$UNDEF, "w");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
        // struct SharedRegion.Region
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.SharedRegion$$Region", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.SharedRegion.Region", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("entry", (Proto)om.findStrict("ti.sdo.ipc.SharedRegion.Entry", "ti.sdo.ipc"), $$DEFAULT, "w");
                po.addFld("reservedSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("heap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
        // struct SharedRegion.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.SharedRegion$$Module_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.SharedRegion.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("regions", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.SharedRegion.Region", "ti.sdo.ipc"), false), $$DEFAULT, "w");
    }

    void ListMP$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/ListMP.xs");
        om.bind("ti.sdo.ipc.ListMP$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.ListMP.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x12181964L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc"), $$UNDEF, "wh");
            po.addFld("maxRuntimeEntries", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "wh");
            po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "wh");
            po.addFld("tableSection", $$T_Str, null, "wh");
            po.addFld("nameSrvPrms", (Proto)om.findStrict("ti.sdo.utils.NameServer.Params", "ti.sdo.ipc"), $$DEFAULT, "wh");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.ListMP$$create", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$ListMP$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.ListMP$$construct", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$ListMP$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.ListMP$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.ListMP$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.ListMP$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.ListMP$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.ListMP$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.ListMP$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP.Instance", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.ListMP.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x12181964L, "rh");
        if (isCFG) {
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc"), null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("name", $$T_Str, null, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("metaListMP", new Proto.Arr($$T_Obj, false), $$DEFAULT, "wh");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$Params", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.ListMP.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x12181964L, "rh");
        if (isCFG) {
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc"), null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("name", $$T_Str, null, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("metaListMP", new Proto.Arr($$T_Obj, false), $$DEFAULT, "wh");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$Object", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.ListMP.Object", om.findStrict("ti.sdo.ipc.ListMP.Instance", "ti.sdo.ipc"));
        // struct ListMP.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$BasicView", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.ListMP.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("label", $$T_Str, $$UNDEF, "w");
                po.addFld("type", $$T_Str, $$UNDEF, "w");
                po.addFld("gate", $$T_Str, $$UNDEF, "w");
        // struct ListMP.ElemView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$ElemView", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.ListMP.ElemView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("index", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("srPtr", $$T_Str, $$UNDEF, "w");
                po.addFld("addr", $$T_Str, $$UNDEF, "w");
        // struct ListMP.Elem
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$Elem", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.ListMP.Elem", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("next", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("prev", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct ListMP.Attrs
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$Attrs", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.ListMP.Attrs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("status", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("gateMPAddr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("head", (Proto)om.findStrict("ti.sdo.ipc.ListMP.Elem", "ti.sdo.ipc"), $$DEFAULT, "w");
        // struct ListMP.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$Instance_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.ListMP.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("attrs", new Proto.Adr("ti_sdo_ipc_ListMP_Attrs*", "PS"), $$UNDEF, "w");
                po.addFld("nsKey", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("objType", (Proto)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("allocSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("cacheLineSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
        // struct ListMP.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$Module_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.ListMP.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("nameServer", (Proto)om.findStrict("ti.sdo.utils.NameServer.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
    }

    void Ipc$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/Ipc.xs");
        om.bind("ti.sdo.ipc.Ipc$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Ipc.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("PROCSYNCSTART", Proto.Elm.newCNum("(xdc_UInt32)"), 1L, "rh");
                po.addFld("PROCSYNCFINISH", Proto.Elm.newCNum("(xdc_UInt32)"), 2L, "rh");
                po.addFld("PROCSYNCDETACH", Proto.Elm.newCNum("(xdc_UInt32)"), 3L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc"), $$UNDEF, "wh");
            po.addFld("A_addrNotInSharedRegion", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_addrNotInSharedRegion: Address not in any shared region"), "w");
            po.addFld("A_addrNotCacheAligned", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_addrNotCacheAligned: Address is not cache aligned"), "w");
            po.addFld("A_nullArgument", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_nullArgument: Required argument is null"), "w");
            po.addFld("A_nullPointer", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_nullPointer: Pointer is null"), "w");
            po.addFld("A_invArgument", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_invArgument: Invalid argument supplied"), "w");
            po.addFld("A_invParam", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_invParam: Invalid configuration parameter supplied"), "w");
            po.addFld("A_internal", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_internal: An internal error has occurred"), "w");
            po.addFld("E_nameFailed", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc"), Global.newObject("msg", "E_nameFailed: '%s' name failed to be added to NameServer"), "w");
            po.addFld("E_internal", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc"), Global.newObject("msg", "E_internal: An internal error occurred"), "w");
            po.addFld("E_versionMismatch", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc"), Global.newObject("msg", "E_versionMismatch: IPC Module version mismatch: creator: %d, opener: %d"), "w");
            po.addFld("sr0MemorySetup", $$T_Bool, $$UNDEF, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "wh");
            po.addFld("procSync", (Proto)om.findStrict("ti.sdo.ipc.Ipc.ProcSync", "ti.sdo.ipc"), om.find("ti.sdo.ipc.Ipc.ProcSync_PAIR"), "w");
            po.addFld("generateSlaveDataForHost", $$T_Bool, $$UNDEF, "w");
            po.addFld("userFxn", (Proto)om.findStrict("ti.sdo.ipc.Ipc.UserFxn", "ti.sdo.ipc"), $$DEFAULT, "w");
            po.addFld("entry", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.Ipc.Entry", "ti.sdo.ipc"), false), $$DEFAULT, "wh");
            po.addFld("numUserFxns", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("userFxns", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.Ipc.UserFxnAndArg", "ti.sdo.ipc"), false), Global.newArray(new Object[]{}), "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.Ipc$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.Ipc$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.Ipc$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.Ipc$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("addUserFxn", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Ipc$$addUserFxn", "ti.sdo.ipc"), Global.get(cap, "addUserFxn"));
                po.addFxn("setEntryMeta", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Ipc$$setEntryMeta", "ti.sdo.ipc"), Global.get(cap, "setEntryMeta"));
                po.addFxn("getObjTypeStr$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Ipc$$getObjTypeStr$view", "ti.sdo.ipc"), Global.get(cap, "getObjTypeStr$view"));
        // struct Ipc.ModuleView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$ModuleView", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Ipc.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("attached", $$T_Bool, $$UNDEF, "w");
                po.addFld("setupNotify", $$T_Bool, $$UNDEF, "w");
                po.addFld("setupMessageQ", $$T_Bool, $$UNDEF, "w");
        // struct Ipc.Entry
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$Entry", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Ipc.Entry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("setupNotify", $$T_Bool, $$UNDEF, "w");
                po.addFld("setupMessageQ", $$T_Bool, $$UNDEF, "w");
        // struct Ipc.UserFxn
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$UserFxn", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Ipc.UserFxn", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("attach", new Proto.Adr("xdc_Int(*)(xdc_UArg,xdc_UInt16)", "PFn"), $$UNDEF, "w");
                po.addFld("detach", new Proto.Adr("xdc_Int(*)(xdc_UArg,xdc_UInt16)", "PFn"), $$UNDEF, "w");
        // struct Ipc.ConfigEntry
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$ConfigEntry", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Ipc.ConfigEntry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("localProcId", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("tag", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("size", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("next", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct Ipc.ProcEntry
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$ProcEntry", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Ipc.ProcEntry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("localConfigList", new Proto.Adr("xdc_Bits32*", "Pn"), $$UNDEF, "w");
                po.addFld("remoteConfigList", new Proto.Adr("xdc_Bits32*", "Pn"), $$UNDEF, "w");
                po.addFld("attached", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("entry", (Proto)om.findStrict("ti.sdo.ipc.Ipc.Entry", "ti.sdo.ipc"), $$DEFAULT, "w");
        // struct Ipc.Reserved
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$Reserved", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Ipc.Reserved", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("startedKey", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("notifySRPtr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("nsrnSRPtr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("transportSRPtr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("configListHead", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct Ipc.UserFxnAndArg
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$UserFxnAndArg", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Ipc.UserFxnAndArg", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("userFxn", (Proto)om.findStrict("ti.sdo.ipc.Ipc.UserFxn", "ti.sdo.ipc"), $$DEFAULT, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct Ipc.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$Module_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Ipc.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ipcSharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("gateMPSharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("procEntry", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.Ipc.ProcEntry", "ti.sdo.ipc"), false), $$DEFAULT, "w");
    }

    void Notify$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/Notify.xs");
        om.bind("ti.sdo.ipc.Notify$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("MAXEVENTS", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc"), $$UNDEF, "wh");
            po.addFld("A_alreadyRegistered", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_alreadyRegistered: Notify instance for the processor/line already registered"), "w");
            po.addFld("A_notRegistered", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_notRegistered: Notify instance not yet registered for the processor/line"), "w");
            po.addFld("A_reservedEvent", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_reservedEvent: Improper use of a reserved event"), "w");
            po.addFld("A_outOfOrderNesting", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_outOfOrderNesting: Out of order nesting"), "w");
            po.addFld("A_invArgument", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_invArgument: Invalid argument supplied"), "w");
            po.addFld("A_internal", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc"), Global.newObject("msg", "A_internal: An internal error has occurred"), "w");
            po.addFldV("SetupProxy", (Proto)om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc"), null, "wh", $$delegGet, $$delegSet);
            po.addFld("numEvents", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "w");
            po.addFld("sendEventPollCount", Proto.Elm.newCNum("(xdc_UInt32)"), Global.eval("-1"), "w");
            po.addFld("numLines", Proto.Elm.newCNum("(xdc_UInt16)"), 1L, "w");
            po.addFld("reservedEvents", Proto.Elm.newCNum("(xdc_UInt16)"), 5L, "w");
            po.addFldV("Module_GateProxy", (Proto)om.findStrict("xdc.runtime.IGateProvider.Module", "ti.sdo.ipc"), null, "wh", $$delegGet, $$delegSet);
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Notify$$create", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$Notify$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Notify$$construct", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$Notify$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.Notify$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.Notify$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.Notify$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.Notify$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.Notify$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.Notify$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify.Instance", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("MAXEVENTS", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$Params", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("MAXEVENTS", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$Object", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify.Object", om.findStrict("ti.sdo.ipc.Notify.Instance", "ti.sdo.ipc"));
        // struct Notify.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$BasicView", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("remoteProcName", $$T_Str, $$UNDEF, "w");
                po.addFld("lineId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("disabled", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        // struct Notify.EventDataView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$EventDataView", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify.EventDataView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("eventId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("fnNotifyCbck", $$T_Str, $$UNDEF, "w");
                po.addFld("cbckArg", $$T_Str, $$UNDEF, "w");
        // struct Notify.EventCallback
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$EventCallback", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify.EventCallback", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fnNotifyCbck", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("cbckArg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct Notify.EventListener
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$EventListener", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify.EventListener", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("element", (Proto)om.findStrict("ti.sdo.utils.List.Elem", "ti.sdo.ipc"), $$DEFAULT, "w");
                po.addFld("callback", (Proto)om.findStrict("ti.sdo.ipc.Notify.EventCallback", "ti.sdo.ipc"), $$DEFAULT, "w");
        // struct Notify.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$Instance_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("nesting", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("driverHandle", (Proto)om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver.Handle", "ti.sdo.ipc"), $$UNDEF, "w");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("lineId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("callbacks", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.Notify.EventCallback", "ti.sdo.ipc"), false), $$DEFAULT, "w");
                po.addFld("eventList", new Proto.Arr((Proto)om.findStrict("ti.sdo.utils.List.Object", "ti.sdo.ipc"), false), $$DEFAULT, "w");
        // struct Notify.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$Module_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("notifyHandles", new Proto.Arr(new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.Notify.Handle", "ti.sdo.ipc"), false), false), $$DEFAULT, "w");
                po.addFld("localEnableMask", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
    }

    void GateMP_RemoteSystemProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteSystemProxy.Module", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc"));
                po.addFld("delegate$", (Proto)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc"), null, "wh");
                po.addFld("abstractInstances$", $$T_Bool, false, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy$$create", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$GateMP_RemoteSystemProxy$$create"));
        }//isCFG
                po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "ti.sdo.ipc"), $$UNDEF);
                po.addFxn("getNumResources", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getNumResources", "ti.sdo.ipc"), $$UNDEF);
                po.addFxn("getRemoteStatus$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getRemoteStatus$view", "ti.sdo.ipc"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Instance", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteSystemProxy.Instance", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Instance", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFldV("resourceId", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w", $$proxyGet, $$proxySet);
            po.addFldV("openFlag", $$T_Bool, false, "w", $$proxyGet, $$proxySet);
            po.addFldV("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w", $$proxyGet, $$proxySet);
            po.addFldV("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w", $$proxyGet, $$proxySet);
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy$$Params", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteSystemProxy.Params", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$Params", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFld("resourceId", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy$$Object", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteSystemProxy.Object", om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Instance", "ti.sdo.ipc"));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy$$Instance_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteSystemProxy.Instance_State", null);
        po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void GateMP_RemoteCustom1Proxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Module", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc"));
                po.addFld("delegate$", (Proto)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc"), null, "wh");
                po.addFld("abstractInstances$", $$T_Bool, false, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy$$create", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$GateMP_RemoteCustom1Proxy$$create"));
        }//isCFG
                po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "ti.sdo.ipc"), $$UNDEF);
                po.addFxn("getNumResources", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getNumResources", "ti.sdo.ipc"), $$UNDEF);
                po.addFxn("getRemoteStatus$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getRemoteStatus$view", "ti.sdo.ipc"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Instance", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Instance", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Instance", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFldV("resourceId", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w", $$proxyGet, $$proxySet);
            po.addFldV("openFlag", $$T_Bool, false, "w", $$proxyGet, $$proxySet);
            po.addFldV("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w", $$proxyGet, $$proxySet);
            po.addFldV("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w", $$proxyGet, $$proxySet);
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy$$Params", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Params", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$Params", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFld("resourceId", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy$$Object", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Object", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Instance", "ti.sdo.ipc"));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy$$Instance_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Instance_State", null);
        po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void GateMP_RemoteCustom2Proxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Module", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc"));
                po.addFld("delegate$", (Proto)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc"), null, "wh");
                po.addFld("abstractInstances$", $$T_Bool, false, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy$$create", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$GateMP_RemoteCustom2Proxy$$create"));
        }//isCFG
                po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "ti.sdo.ipc"), $$UNDEF);
                po.addFxn("getNumResources", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getNumResources", "ti.sdo.ipc"), $$UNDEF);
                po.addFxn("getRemoteStatus$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getRemoteStatus$view", "ti.sdo.ipc"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Instance", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Instance", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Instance", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFldV("resourceId", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w", $$proxyGet, $$proxySet);
            po.addFldV("openFlag", $$T_Bool, false, "w", $$proxyGet, $$proxySet);
            po.addFldV("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w", $$proxyGet, $$proxySet);
            po.addFldV("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w", $$proxyGet, $$proxySet);
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy$$Params", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Params", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$Params", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFld("resourceId", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy$$Object", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Object", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Instance", "ti.sdo.ipc"));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy$$Instance_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Instance_State", null);
        po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void MessageQ_SetupTransportProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ_SetupTransportProxy.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.MessageQ_SetupTransportProxy.Module", om.findStrict("ti.sdo.ipc.interfaces.ITransportSetup.Module", "ti.sdo.ipc"));
                po.addFld("delegate$", (Proto)om.findStrict("ti.sdo.ipc.interfaces.ITransportSetup.Module", "ti.sdo.ipc"), null, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFldV("priority", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w", $$proxyGet, $$proxySet);
        }//isCFG
    }

    void Notify_SetupProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify_SetupProxy.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify_SetupProxy.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc"));
                po.addFld("delegate$", (Proto)om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc"), null, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void Notify_Module_GateProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Module", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify_Module_GateProxy.Module", om.findStrict("xdc.runtime.IGateProvider.Module", "ti.sdo.ipc"));
                po.addFld("delegate$", (Proto)om.findStrict("xdc.runtime.IGateProvider.Module", "ti.sdo.ipc"), null, "wh");
                po.addFld("abstractInstances$", $$T_Bool, false, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy$$create", "ti.sdo.ipc"), Global.get("ti$sdo$ipc$Notify_Module_GateProxy$$create"));
        }//isCFG
                po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "ti.sdo.ipc"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Instance", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify_Module_GateProxy.Instance", om.findStrict("xdc.runtime.IGateProvider.Instance", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy$$Params", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify_Module_GateProxy.Params", om.findStrict("xdc.runtime.IGateProvider$$Params", "ti.sdo.ipc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy$$Object", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify_Module_GateProxy.Object", om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Instance", "ti.sdo.ipc"));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy$$Instance_State", "ti.sdo.ipc");
        po.init("ti.sdo.ipc.Notify_Module_GateProxy.Instance_State", null);
        po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void Build$$ROV()
    {
    }

    void GateMP$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.GateMP", "ti.sdo.ipc");
        vo.bind("Reserved$fetchDesc", Global.newObject("type", "ti.sdo.ipc.GateMP.Reserved", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$Reserved", "ti.sdo.ipc");
        vo.bind("LocalGate$fetchDesc", Global.newObject("type", "ti.sdo.ipc.GateMP.LocalGate", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$LocalGate", "ti.sdo.ipc");
        vo.bind("Attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.GateMP.Attrs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$Attrs", "ti.sdo.ipc");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.GateMP.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$Instance_State", "ti.sdo.ipc");
        po.bind("attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.GateMP.Attrs", "isScalar", false));
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.GateMP.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP$$Module_State", "ti.sdo.ipc");
        po.bind("remoteSystemInUse$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_UInt8", "isScalar", true));
        po.bind("remoteCustom1InUse$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_UInt8", "isScalar", true));
        po.bind("remoteCustom2InUse$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_UInt8", "isScalar", true));
        po.bind("remoteSystemGates$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Ptr", "isScalar", true));
        po.bind("remoteCustom1Gates$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Ptr", "isScalar", true));
        po.bind("remoteCustom2Gates$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Ptr", "isScalar", true));
    }

    void MessageQ$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.MessageQ", "ti.sdo.ipc");
        vo.bind("MsgHeader$fetchDesc", Global.newObject("type", "ti.sdo.ipc.MessageQ.MsgHeader", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$MsgHeader", "ti.sdo.ipc");
        vo.bind("HeapEntry$fetchDesc", Global.newObject("type", "ti.sdo.ipc.MessageQ.HeapEntry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$HeapEntry", "ti.sdo.ipc");
        vo.bind("TransportEntry$fetchDesc", Global.newObject("type", "ti.sdo.ipc.MessageQ.TransportEntry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$TransportEntry", "ti.sdo.ipc");
        vo.bind("RegisteredTransport$fetchDesc", Global.newObject("type", "ti.sdo.ipc.MessageQ.RegisteredTransport", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$RegisteredTransport", "ti.sdo.ipc");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.MessageQ.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$Instance_State", "ti.sdo.ipc");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.MessageQ.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ$$Module_State", "ti.sdo.ipc");
        po.bind("queues$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Ptr", "isScalar", true));
        po.bind("heaps$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Ptr", "isScalar", true));
    }

    void SharedRegion$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.SharedRegion", "ti.sdo.ipc");
        vo.bind("Entry$fetchDesc", Global.newObject("type", "ti.sdo.ipc.SharedRegion.Entry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.SharedRegion$$Entry", "ti.sdo.ipc");
        vo.bind("Region$fetchDesc", Global.newObject("type", "ti.sdo.ipc.SharedRegion.Region", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.SharedRegion$$Region", "ti.sdo.ipc");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.SharedRegion.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.SharedRegion$$Module_State", "ti.sdo.ipc");
        po.bind("regions$fetchDesc", Global.newObject("type", "ti.sdo.ipc.SharedRegion.Region", "isScalar", false));
    }

    void ListMP$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.ListMP", "ti.sdo.ipc");
        vo.bind("Elem$fetchDesc", Global.newObject("type", "ti.sdo.ipc.ListMP.Elem", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$Elem", "ti.sdo.ipc");
        vo.bind("Attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.ListMP.Attrs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$Attrs", "ti.sdo.ipc");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.ListMP.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$Instance_State", "ti.sdo.ipc");
        po.bind("attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.ListMP.Attrs", "isScalar", false));
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.ListMP.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP$$Module_State", "ti.sdo.ipc");
    }

    void Ipc$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.Ipc", "ti.sdo.ipc");
        vo.bind("Entry$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Ipc.Entry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$Entry", "ti.sdo.ipc");
        vo.bind("UserFxn$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Ipc.UserFxn", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$UserFxn", "ti.sdo.ipc");
        vo.bind("ConfigEntry$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Ipc.ConfigEntry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$ConfigEntry", "ti.sdo.ipc");
        vo.bind("ProcEntry$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Ipc.ProcEntry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$ProcEntry", "ti.sdo.ipc");
        vo.bind("Reserved$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Ipc.Reserved", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$Reserved", "ti.sdo.ipc");
        vo.bind("UserFxnAndArg$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Ipc.UserFxnAndArg", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$UserFxnAndArg", "ti.sdo.ipc");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Ipc.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc$$Module_State", "ti.sdo.ipc");
        po.bind("procEntry$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Ipc.ProcEntry", "isScalar", false));
    }

    void Notify$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.Notify", "ti.sdo.ipc");
        vo.bind("EventCallback$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Notify.EventCallback", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$EventCallback", "ti.sdo.ipc");
        vo.bind("EventListener$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Notify.EventListener", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$EventListener", "ti.sdo.ipc");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Notify.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$Instance_State", "ti.sdo.ipc");
        po.bind("callbacks$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Notify.EventCallback", "isScalar", false));
        po.bind("eventList$fetchDesc", Global.newObject("type", "ti.sdo.utils.List.Object", "isScalar", false));
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.Notify.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify$$Module_State", "ti.sdo.ipc");
    }

    void GateMP_RemoteSystemProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy$$Instance_State", "ti.sdo.ipc");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void GateMP_RemoteCustom1Proxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy$$Instance_State", "ti.sdo.ipc");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void GateMP_RemoteCustom2Proxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy$$Instance_State", "ti.sdo.ipc");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void MessageQ_SetupTransportProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.MessageQ_SetupTransportProxy", "ti.sdo.ipc");
    }

    void Notify_SetupProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.Notify_SetupProxy", "ti.sdo.ipc");
    }

    void Notify_Module_GateProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy$$Instance_State", "ti.sdo.ipc");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Build$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.Build", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Build.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.Build", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.Build$$capsule", "ti.sdo.ipc"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("LibType", om.findStrict("ti.sdo.ipc.Build.LibType", "ti.sdo.ipc"));
        vo.bind("LibType_Instrumented", om.findStrict("ti.sdo.ipc.Build.LibType_Instrumented", "ti.sdo.ipc"));
        vo.bind("LibType_NonInstrumented", om.findStrict("ti.sdo.ipc.Build.LibType_NonInstrumented", "ti.sdo.ipc"));
        vo.bind("LibType_Custom", om.findStrict("ti.sdo.ipc.Build.LibType_Custom", "ti.sdo.ipc"));
        vo.bind("LibType_Debug", om.findStrict("ti.sdo.ipc.Build.LibType_Debug", "ti.sdo.ipc"));
        vo.bind("LibType_PkgLib", om.findStrict("ti.sdo.ipc.Build.LibType_PkgLib", "ti.sdo.ipc"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.Build$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Build.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Build.xdt");
        pkgV.bind("Build", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Build");
    }

    void GateMP$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.GateMP", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.GateMP", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.GateMP$$capsule", "ti.sdo.ipc"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.GateMP.Instance", "ti.sdo.ipc"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.GateMP.Params", "ti.sdo.ipc"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.GateMP.Params", "ti.sdo.ipc")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        icfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.GateMP.BasicView", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.GateMP.BasicView", "ti.sdo.ipc"));
        vo.bind("ModuleView", om.findStrict("ti.sdo.ipc.GateMP.ModuleView", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.GateMP.ModuleView", "ti.sdo.ipc"));
        vo.bind("Reserved", om.findStrict("ti.sdo.ipc.GateMP.Reserved", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.GateMP.Reserved", "ti.sdo.ipc"));
        mcfgs.add("E_gateUnavailable");
        mcfgs.add("E_localGate");
        mcfgs.add("A_invalidClose");
        mcfgs.add("A_invalidDelete");
        mcfgs.add("LM_enter");
        mcfgs.add("LM_leave");
        mcfgs.add("LM_create");
        mcfgs.add("LM_open");
        mcfgs.add("LM_delete");
        mcfgs.add("LM_close");
        vo.bind("LocalProtect", om.findStrict("ti.sdo.ipc.GateMP.LocalProtect", "ti.sdo.ipc"));
        vo.bind("RemoteProtect", om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect", "ti.sdo.ipc"));
        mcfgs.add("maxNameLen");
        vo.bind("RemoteSystemProxy$proxy", om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy", "ti.sdo.ipc"));
        proxies.add("RemoteSystemProxy");
        vo.bind("RemoteCustom1Proxy$proxy", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy", "ti.sdo.ipc"));
        proxies.add("RemoteCustom1Proxy");
        vo.bind("RemoteCustom2Proxy$proxy", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy", "ti.sdo.ipc"));
        proxies.add("RemoteCustom2Proxy");
        icfgs.add("nameSrvPrms");
        vo.bind("LocalGate", om.findStrict("ti.sdo.ipc.GateMP.LocalGate", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.GateMP.LocalGate", "ti.sdo.ipc"));
        vo.bind("Attrs", om.findStrict("ti.sdo.ipc.GateMP.Attrs", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.GateMP.Attrs", "ti.sdo.ipc"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.GateMP.Instance_State", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.GateMP.Instance_State", "ti.sdo.ipc"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.GateMP.Module_State", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.GateMP.Module_State", "ti.sdo.ipc"));
        vo.bind("LocalProtect_NONE", om.findStrict("ti.sdo.ipc.GateMP.LocalProtect_NONE", "ti.sdo.ipc"));
        vo.bind("LocalProtect_INTERRUPT", om.findStrict("ti.sdo.ipc.GateMP.LocalProtect_INTERRUPT", "ti.sdo.ipc"));
        vo.bind("LocalProtect_TASKLET", om.findStrict("ti.sdo.ipc.GateMP.LocalProtect_TASKLET", "ti.sdo.ipc"));
        vo.bind("LocalProtect_THREAD", om.findStrict("ti.sdo.ipc.GateMP.LocalProtect_THREAD", "ti.sdo.ipc"));
        vo.bind("LocalProtect_PROCESS", om.findStrict("ti.sdo.ipc.GateMP.LocalProtect_PROCESS", "ti.sdo.ipc"));
        vo.bind("RemoteProtect_NONE", om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect_NONE", "ti.sdo.ipc"));
        vo.bind("RemoteProtect_SYSTEM", om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect_SYSTEM", "ti.sdo.ipc"));
        vo.bind("RemoteProtect_CUSTOM1", om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect_CUSTOM1", "ti.sdo.ipc"));
        vo.bind("RemoteProtect_CUSTOM2", om.findStrict("ti.sdo.ipc.GateMP.RemoteProtect_CUSTOM2", "ti.sdo.ipc"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.GateMP$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$GateMP$$__initObject"));
        }//isCFG
        vo.bind("createLocal", om.findStrict("ti.sdo.ipc.GateMP.createLocal", "ti.sdo.ipc"));
        vo.bind("attach", om.findStrict("ti.sdo.ipc.GateMP.attach", "ti.sdo.ipc"));
        vo.bind("detach", om.findStrict("ti.sdo.ipc.GateMP.detach", "ti.sdo.ipc"));
        vo.bind("getRegion0ReservedSize", om.findStrict("ti.sdo.ipc.GateMP.getRegion0ReservedSize", "ti.sdo.ipc"));
        vo.bind("setRegion0Reserved", om.findStrict("ti.sdo.ipc.GateMP.setRegion0Reserved", "ti.sdo.ipc"));
        vo.bind("openRegion0Reserved", om.findStrict("ti.sdo.ipc.GateMP.openRegion0Reserved", "ti.sdo.ipc"));
        vo.bind("setDefaultRemote", om.findStrict("ti.sdo.ipc.GateMP.setDefaultRemote", "ti.sdo.ipc"));
        vo.bind("start", om.findStrict("ti.sdo.ipc.GateMP.start", "ti.sdo.ipc"));
        vo.bind("stop", om.findStrict("ti.sdo.ipc.GateMP.stop", "ti.sdo.ipc"));
        vo.bind("getFreeResource", om.findStrict("ti.sdo.ipc.GateMP.getFreeResource", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_GateMP_Handle__label__E", "ti_sdo_ipc_GateMP_Module__startupDone__E", "ti_sdo_ipc_GateMP_Object__create__E", "ti_sdo_ipc_GateMP_Object__delete__E", "ti_sdo_ipc_GateMP_Object__destruct__E", "ti_sdo_ipc_GateMP_Object__get__E", "ti_sdo_ipc_GateMP_Object__first__E", "ti_sdo_ipc_GateMP_Object__next__E", "ti_sdo_ipc_GateMP_Params__init__E", "ti_sdo_ipc_GateMP_createLocal__E", "ti_sdo_ipc_GateMP_attach__E", "ti_sdo_ipc_GateMP_detach__E", "ti_sdo_ipc_GateMP_getRegion0ReservedSize__E", "ti_sdo_ipc_GateMP_setRegion0Reserved__E", "ti_sdo_ipc_GateMP_openRegion0Reserved__E", "ti_sdo_ipc_GateMP_setDefaultRemote__E", "ti_sdo_ipc_GateMP_start__E", "ti_sdo_ipc_GateMP_stop__E", "ti_sdo_ipc_GateMP_getSharedAddr__E"));
        vo.bind("$$logEvtCfgs", Global.newArray("LM_enter", "LM_leave", "LM_create", "LM_open", "LM_delete", "LM_close"));
        vo.bind("$$errorDescCfgs", Global.newArray("E_gateUnavailable", "E_localGate"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_invalidClose", "A_invalidDelete"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./GateMP.xdt");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.GateMP.Object", "ti.sdo.ipc"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "createLocal", "entry", "%d", "exit", "%p"));
        loggables.add(Global.newObject("name", "attach", "entry", "0x%x, %p", "exit", "%d"));
        loggables.add(Global.newObject("name", "detach", "entry", "0x%x", "exit", "%d"));
        loggables.add(Global.newObject("name", "getRegion0ReservedSize", "entry", "", "exit", "0x%x"));
        loggables.add(Global.newObject("name", "setRegion0Reserved", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "openRegion0Reserved", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "setDefaultRemote", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "start", "entry", "%p", "exit", "%d"));
        loggables.add(Global.newObject("name", "stop", "entry", "", "exit", "%d"));
        loggables.add(Global.newObject("name", "getSharedAddr", "entry", "%p", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./GateMP.xdt");
        pkgV.bind("GateMP", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GateMP");
    }

    void MessageQ$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.MessageQ", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.MessageQ", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.MessageQ$$capsule", "ti.sdo.ipc"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.MessageQ.Instance", "ti.sdo.ipc"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.MessageQ.Params", "ti.sdo.ipc"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.MessageQ.Params", "ti.sdo.ipc")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.MessageQ.Handle", "ti.sdo.ipc"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        icfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("QueuesView", om.findStrict("ti.sdo.ipc.MessageQ.QueuesView", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.MessageQ.QueuesView", "ti.sdo.ipc"));
        vo.bind("MessagesView", om.findStrict("ti.sdo.ipc.MessageQ.MessagesView", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.MessageQ.MessagesView", "ti.sdo.ipc"));
        vo.bind("ModuleView", om.findStrict("ti.sdo.ipc.MessageQ.ModuleView", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.MessageQ.ModuleView", "ti.sdo.ipc"));
        mcfgs.add("LM_setTrace");
        mcfgs.add("LM_alloc");
        mcfgs.add("LM_staticMsgInit");
        mcfgs.add("LM_free");
        mcfgs.add("LM_putLocal");
        mcfgs.add("LM_putRemote");
        mcfgs.add("LM_rcvByTransport");
        mcfgs.add("LM_get");
        vo.bind("FreeHookFxn", om.findStrict("ti.sdo.ipc.MessageQ.FreeHookFxn", "ti.sdo.ipc"));
        vo.bind("PutHookFxn", om.findStrict("ti.sdo.ipc.MessageQ.PutHookFxn", "ti.sdo.ipc"));
        vo.bind("QueueId", om.findStrict("ti.sdo.ipc.MessageQ.QueueId", "ti.sdo.ipc"));
        vo.bind("SetupTransportProxy$proxy", om.findStrict("ti.sdo.ipc.MessageQ_SetupTransportProxy", "ti.sdo.ipc"));
        proxies.add("SetupTransportProxy");
        mcfgs.add("A_invalidContext");
        mcfgs.add("A_cannotFreeStaticMsg");
        mcfgs.add("A_invalidMsg");
        mcfgs.add("A_invalidQueueId");
        mcfgs.add("A_heapIdInvalid");
        mcfgs.add("A_procIdInvalid");
        mcfgs.add("A_invalidObj");
        mcfgs.add("A_invalidParam");
        mcfgs.add("A_unregisteredTransport");
        mcfgs.add("A_invalidUnblock");
        mcfgs.add("E_maxReached");
        mcfgs.add("E_unregisterHeapId");
        mcfgs.add("E_nameFailed");
        mcfgs.add("E_indexNotAvailable");
        mcfgs.add("traceFlag");
        mcfgs.add("numHeaps");
        mcfgs.add("maxRuntimeEntries");
        mcfgs.add("numReservedEntries");
        mcfgs.add("nameTableGate");
        mcfgs.add("maxNameLen");
        mcfgs.add("freeHookFxn");
        mcfgs.add("putHookFxn");
        vo.bind("MsgHeader", om.findStrict("ti.sdo.ipc.MessageQ.MsgHeader", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.MessageQ.MsgHeader", "ti.sdo.ipc"));
        vo.bind("HeapEntry", om.findStrict("ti.sdo.ipc.MessageQ.HeapEntry", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.MessageQ.HeapEntry", "ti.sdo.ipc"));
        vo.bind("TransportEntry", om.findStrict("ti.sdo.ipc.MessageQ.TransportEntry", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.MessageQ.TransportEntry", "ti.sdo.ipc"));
        vo.bind("TransportType", om.findStrict("ti.sdo.ipc.MessageQ.TransportType", "ti.sdo.ipc"));
        vo.bind("RegisteredTransport", om.findStrict("ti.sdo.ipc.MessageQ.RegisteredTransport", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.MessageQ.RegisteredTransport", "ti.sdo.ipc"));
        icfgs.add("nameSrvPrms");
        icfgs.add("staticHeaps");
        icfgs.add("staticTransports");
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.MessageQ.Instance_State", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.MessageQ.Instance_State", "ti.sdo.ipc"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.MessageQ.Module_State", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.MessageQ.Module_State", "ti.sdo.ipc"));
        vo.bind("TransportType_IMessageQTransport", om.findStrict("ti.sdo.ipc.MessageQ.TransportType_IMessageQTransport", "ti.sdo.ipc"));
        vo.bind("TransportType_INetworkTransport", om.findStrict("ti.sdo.ipc.MessageQ.TransportType_INetworkTransport", "ti.sdo.ipc"));
        vo.bind("TransportType_Invalid", om.findStrict("ti.sdo.ipc.MessageQ.TransportType_Invalid", "ti.sdo.ipc"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.MessageQ$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$MessageQ$$__initObject"));
        }//isCFG
        vo.bind("registerTransport", om.findStrict("ti.sdo.ipc.MessageQ.registerTransport", "ti.sdo.ipc"));
        vo.bind("unregisterTransport", om.findStrict("ti.sdo.ipc.MessageQ.unregisterTransport", "ti.sdo.ipc"));
        vo.bind("grow", om.findStrict("ti.sdo.ipc.MessageQ.grow", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_MessageQ_Handle__label__E", "ti_sdo_ipc_MessageQ_Module__startupDone__E", "ti_sdo_ipc_MessageQ_Object__create__E", "ti_sdo_ipc_MessageQ_Object__delete__E", "ti_sdo_ipc_MessageQ_Object__destruct__E", "ti_sdo_ipc_MessageQ_Object__get__E", "ti_sdo_ipc_MessageQ_Object__first__E", "ti_sdo_ipc_MessageQ_Object__next__E", "ti_sdo_ipc_MessageQ_Params__init__E", "ti_sdo_ipc_MessageQ_registerTransport__E", "ti_sdo_ipc_MessageQ_unregisterTransport__E"));
        vo.bind("$$logEvtCfgs", Global.newArray("LM_setTrace", "LM_alloc", "LM_staticMsgInit", "LM_free", "LM_putLocal", "LM_putRemote", "LM_rcvByTransport", "LM_get"));
        vo.bind("$$errorDescCfgs", Global.newArray("E_maxReached", "E_unregisterHeapId", "E_nameFailed", "E_indexNotAvailable"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_invalidContext", "A_cannotFreeStaticMsg", "A_invalidMsg", "A_invalidQueueId", "A_heapIdInvalid", "A_procIdInvalid", "A_invalidObj", "A_invalidParam", "A_unregisteredTransport", "A_invalidUnblock"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.MessageQ.Object", "ti.sdo.ipc"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "registerTransport", "entry", "%p, 0x%x, 0x%x", "exit", "%d"));
        loggables.add(Global.newObject("name", "unregisterTransport", "entry", "0x%x, 0x%x", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("MessageQ", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("MessageQ");
    }

    void SharedRegion$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.SharedRegion", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.SharedRegion.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.SharedRegion", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.SharedRegion$$capsule", "ti.sdo.ipc"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        icfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("RegionView", om.findStrict("ti.sdo.ipc.SharedRegion.RegionView", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.SharedRegion.RegionView", "ti.sdo.ipc"));
        vo.bind("SRPtr", om.findStrict("ti.sdo.ipc.SharedRegion.SRPtr", "ti.sdo.ipc"));
        mcfgs.add("A_idTooLarge");
        mcfgs.add("A_addrOutOfRange");
        mcfgs.add("A_region0Clear");
        mcfgs.add("A_region0Invalid");
        mcfgs.add("A_regionInvalid");
        mcfgs.add("A_reserveTooMuch");
        mcfgs.add("A_cacheLineSizeIsZero");
        mcfgs.add("A_overlap");
        mcfgs.add("A_alreadyExists");
        mcfgs.add("A_noHeap");
        vo.bind("Entry", om.findStrict("ti.sdo.ipc.SharedRegion.Entry", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.SharedRegion.Entry", "ti.sdo.ipc"));
        mcfgs.add("cacheLineSize");
        mcfgs.add("numEntries");
        mcfgs.add("translate");
        mcfgs.add("INVALIDSRPTR");
        vo.bind("Region", om.findStrict("ti.sdo.ipc.SharedRegion.Region", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.SharedRegion.Region", "ti.sdo.ipc"));
        icfgs.add("entry");
        icfgs.add("genSectionInLinkCmd");
        icfgs.add("entryCount");
        mcfgs.add("numOffsetBits");
        icfgs.add("numOffsetBits");
        mcfgs.add("offsetMask");
        icfgs.add("offsetMask");
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.SharedRegion.Module_State", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.SharedRegion.Module_State", "ti.sdo.ipc"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("attach", om.findStrict("ti.sdo.ipc.SharedRegion.attach", "ti.sdo.ipc"));
        vo.bind("clearReservedMemory", om.findStrict("ti.sdo.ipc.SharedRegion.clearReservedMemory", "ti.sdo.ipc"));
        vo.bind("detach", om.findStrict("ti.sdo.ipc.SharedRegion.detach", "ti.sdo.ipc"));
        vo.bind("reserveMemory", om.findStrict("ti.sdo.ipc.SharedRegion.reserveMemory", "ti.sdo.ipc"));
        vo.bind("resetInternalFields", om.findStrict("ti.sdo.ipc.SharedRegion.resetInternalFields", "ti.sdo.ipc"));
        vo.bind("start", om.findStrict("ti.sdo.ipc.SharedRegion.start", "ti.sdo.ipc"));
        vo.bind("stop", om.findStrict("ti.sdo.ipc.SharedRegion.stop", "ti.sdo.ipc"));
        vo.bind("checkOverlap", om.findStrict("ti.sdo.ipc.SharedRegion.checkOverlap", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_SharedRegion_Module__startupDone__E", "ti_sdo_ipc_SharedRegion_attach__E", "ti_sdo_ipc_SharedRegion_clearReservedMemory__E", "ti_sdo_ipc_SharedRegion_detach__E", "ti_sdo_ipc_SharedRegion_reserveMemory__E", "ti_sdo_ipc_SharedRegion_resetInternalFields__E", "ti_sdo_ipc_SharedRegion_start__E", "ti_sdo_ipc_SharedRegion_stop__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_idTooLarge", "A_addrOutOfRange", "A_region0Clear", "A_region0Invalid", "A_regionInvalid", "A_reserveTooMuch", "A_cacheLineSizeIsZero", "A_overlap", "A_alreadyExists", "A_noHeap"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "attach", "entry", "0x%x", "exit", "%d"));
        loggables.add(Global.newObject("name", "clearReservedMemory", "entry", "", "exit", ""));
        loggables.add(Global.newObject("name", "detach", "entry", "0x%x", "exit", "%d"));
        loggables.add(Global.newObject("name", "reserveMemory", "entry", "0x%x, 0x%x", "exit", "%p"));
        loggables.add(Global.newObject("name", "resetInternalFields", "entry", "0x%x", "exit", ""));
        loggables.add(Global.newObject("name", "start", "entry", "", "exit", "%d"));
        loggables.add(Global.newObject("name", "stop", "entry", "", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("SharedRegion", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("SharedRegion");
    }

    void ListMP$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.ListMP", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.ListMP.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.ListMP", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.ListMP$$capsule", "ti.sdo.ipc"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.ListMP.Instance", "ti.sdo.ipc"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.ListMP.Params", "ti.sdo.ipc"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.ListMP.Params", "ti.sdo.ipc")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.ListMP.Handle", "ti.sdo.ipc"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        icfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.ListMP.BasicView", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.ListMP.BasicView", "ti.sdo.ipc"));
        vo.bind("ElemView", om.findStrict("ti.sdo.ipc.ListMP.ElemView", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.ListMP.ElemView", "ti.sdo.ipc"));
        vo.bind("Elem", om.findStrict("ti.sdo.ipc.ListMP.Elem", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.ListMP.Elem", "ti.sdo.ipc"));
        icfgs.add("nameSrvPrms");
        vo.bind("Attrs", om.findStrict("ti.sdo.ipc.ListMP.Attrs", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.ListMP.Attrs", "ti.sdo.ipc"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.ListMP.Instance_State", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.ListMP.Instance_State", "ti.sdo.ipc"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.ListMP.Module_State", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.ListMP.Module_State", "ti.sdo.ipc"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.ListMP$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$ListMP$$__initObject"));
        }//isCFG
        vo.bind("elemClear", om.findStrict("ti.sdo.ipc.ListMP.elemClear", "ti.sdo.ipc"));
        vo.bind("postInit", om.findStrict("ti.sdo.ipc.ListMP.postInit", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_ListMP_Handle__label__E", "ti_sdo_ipc_ListMP_Module__startupDone__E", "ti_sdo_ipc_ListMP_Object__create__E", "ti_sdo_ipc_ListMP_Object__delete__E", "ti_sdo_ipc_ListMP_Object__destruct__E", "ti_sdo_ipc_ListMP_Object__get__E", "ti_sdo_ipc_ListMP_Object__first__E", "ti_sdo_ipc_ListMP_Object__next__E", "ti_sdo_ipc_ListMP_Params__init__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.ListMP.Object", "ti.sdo.ipc"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("ListMP", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ListMP");
    }

    void Ipc$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.Ipc", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Ipc.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.Ipc", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.Ipc$$capsule", "ti.sdo.ipc"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        icfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("ModuleView", om.findStrict("ti.sdo.ipc.Ipc.ModuleView", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Ipc.ModuleView", "ti.sdo.ipc"));
        vo.bind("ProcSync", om.findStrict("ti.sdo.ipc.Ipc.ProcSync", "ti.sdo.ipc"));
        vo.bind("Entry", om.findStrict("ti.sdo.ipc.Ipc.Entry", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Ipc.Entry", "ti.sdo.ipc"));
        vo.bind("UserFxn", om.findStrict("ti.sdo.ipc.Ipc.UserFxn", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Ipc.UserFxn", "ti.sdo.ipc"));
        mcfgs.add("A_addrNotInSharedRegion");
        mcfgs.add("A_addrNotCacheAligned");
        mcfgs.add("A_nullArgument");
        mcfgs.add("A_nullPointer");
        mcfgs.add("A_invArgument");
        mcfgs.add("A_invParam");
        mcfgs.add("A_internal");
        mcfgs.add("E_nameFailed");
        mcfgs.add("E_internal");
        mcfgs.add("E_versionMismatch");
        mcfgs.add("sr0MemorySetup");
        mcfgs.add("procSync");
        mcfgs.add("generateSlaveDataForHost");
        mcfgs.add("userFxn");
        vo.bind("ObjType", om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc"));
        vo.bind("ConfigEntry", om.findStrict("ti.sdo.ipc.Ipc.ConfigEntry", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Ipc.ConfigEntry", "ti.sdo.ipc"));
        vo.bind("ProcEntry", om.findStrict("ti.sdo.ipc.Ipc.ProcEntry", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Ipc.ProcEntry", "ti.sdo.ipc"));
        vo.bind("Reserved", om.findStrict("ti.sdo.ipc.Ipc.Reserved", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Ipc.Reserved", "ti.sdo.ipc"));
        vo.bind("UserFxnAndArg", om.findStrict("ti.sdo.ipc.Ipc.UserFxnAndArg", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Ipc.UserFxnAndArg", "ti.sdo.ipc"));
        icfgs.add("entry");
        mcfgs.add("numUserFxns");
        icfgs.add("numUserFxns");
        mcfgs.add("userFxns");
        icfgs.add("userFxns");
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.Ipc.Module_State", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Ipc.Module_State", "ti.sdo.ipc"));
        vo.bind("ProcSync_NONE", om.findStrict("ti.sdo.ipc.Ipc.ProcSync_NONE", "ti.sdo.ipc"));
        vo.bind("ProcSync_PAIR", om.findStrict("ti.sdo.ipc.Ipc.ProcSync_PAIR", "ti.sdo.ipc"));
        vo.bind("ProcSync_ALL", om.findStrict("ti.sdo.ipc.Ipc.ProcSync_ALL", "ti.sdo.ipc"));
        vo.bind("ObjType_CREATESTATIC", om.findStrict("ti.sdo.ipc.Ipc.ObjType_CREATESTATIC", "ti.sdo.ipc"));
        vo.bind("ObjType_CREATESTATIC_REGION", om.findStrict("ti.sdo.ipc.Ipc.ObjType_CREATESTATIC_REGION", "ti.sdo.ipc"));
        vo.bind("ObjType_CREATEDYNAMIC", om.findStrict("ti.sdo.ipc.Ipc.ObjType_CREATEDYNAMIC", "ti.sdo.ipc"));
        vo.bind("ObjType_CREATEDYNAMIC_REGION", om.findStrict("ti.sdo.ipc.Ipc.ObjType_CREATEDYNAMIC_REGION", "ti.sdo.ipc"));
        vo.bind("ObjType_OPENDYNAMIC", om.findStrict("ti.sdo.ipc.Ipc.ObjType_OPENDYNAMIC", "ti.sdo.ipc"));
        vo.bind("ObjType_LOCAL", om.findStrict("ti.sdo.ipc.Ipc.ObjType_LOCAL", "ti.sdo.ipc"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("getEntry", om.findStrict("ti.sdo.ipc.Ipc.getEntry", "ti.sdo.ipc"));
        vo.bind("setEntry", om.findStrict("ti.sdo.ipc.Ipc.setEntry", "ti.sdo.ipc"));
        vo.bind("dummy", om.findStrict("ti.sdo.ipc.Ipc.dummy", "ti.sdo.ipc"));
        vo.bind("getMasterAddr", om.findStrict("ti.sdo.ipc.Ipc.getMasterAddr", "ti.sdo.ipc"));
        vo.bind("getRegion0ReservedSize", om.findStrict("ti.sdo.ipc.Ipc.getRegion0ReservedSize", "ti.sdo.ipc"));
        vo.bind("getSlaveAddr", om.findStrict("ti.sdo.ipc.Ipc.getSlaveAddr", "ti.sdo.ipc"));
        vo.bind("procSyncStart", om.findStrict("ti.sdo.ipc.Ipc.procSyncStart", "ti.sdo.ipc"));
        vo.bind("procSyncFinish", om.findStrict("ti.sdo.ipc.Ipc.procSyncFinish", "ti.sdo.ipc"));
        vo.bind("reservedSizePerProc", om.findStrict("ti.sdo.ipc.Ipc.reservedSizePerProc", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_Ipc_Module__startupDone__E", "ti_sdo_ipc_Ipc_getEntry__E", "ti_sdo_ipc_Ipc_setEntry__E", "ti_sdo_ipc_Ipc_dummy__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_nameFailed", "E_internal", "E_versionMismatch"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_addrNotInSharedRegion", "A_addrNotCacheAligned", "A_nullArgument", "A_nullPointer", "A_invArgument", "A_invParam", "A_internal"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Ipc.xdt");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "getEntry", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "setEntry", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "dummy", "entry", "", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./Ipc.xdt");
        pkgV.bind("Ipc", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Ipc");
    }

    void Notify$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.Notify", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.Notify", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.Notify$$capsule", "ti.sdo.ipc"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.Notify.Instance", "ti.sdo.ipc"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.Notify.Params", "ti.sdo.ipc"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.Notify.Params", "ti.sdo.ipc")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.Notify.Handle", "ti.sdo.ipc"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        icfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.Notify.BasicView", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Notify.BasicView", "ti.sdo.ipc"));
        vo.bind("EventDataView", om.findStrict("ti.sdo.ipc.Notify.EventDataView", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Notify.EventDataView", "ti.sdo.ipc"));
        mcfgs.add("A_alreadyRegistered");
        mcfgs.add("A_notRegistered");
        mcfgs.add("A_reservedEvent");
        mcfgs.add("A_outOfOrderNesting");
        mcfgs.add("A_invArgument");
        mcfgs.add("A_internal");
        vo.bind("SetupProxy$proxy", om.findStrict("ti.sdo.ipc.Notify_SetupProxy", "ti.sdo.ipc"));
        proxies.add("SetupProxy");
        mcfgs.add("numEvents");
        mcfgs.add("sendEventPollCount");
        mcfgs.add("numLines");
        mcfgs.add("reservedEvents");
        vo.bind("EventCallback", om.findStrict("ti.sdo.ipc.Notify.EventCallback", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Notify.EventCallback", "ti.sdo.ipc"));
        vo.bind("EventListener", om.findStrict("ti.sdo.ipc.Notify.EventListener", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Notify.EventListener", "ti.sdo.ipc"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.Notify.Instance_State", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Notify.Instance_State", "ti.sdo.ipc"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.Notify.Module_State", "ti.sdo.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ipc.Notify.Module_State", "ti.sdo.ipc"));
        vo.bind("Module_GateProxy$proxy", om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy", "ti.sdo.ipc"));
        proxies.add("Module_GateProxy");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.Notify$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$Notify$$__initObject"));
        }//isCFG
        vo.bind("detach", om.findStrict("ti.sdo.ipc.Notify.detach", "ti.sdo.ipc"));
        vo.bind("execMany", om.findStrict("ti.sdo.ipc.Notify.execMany", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_Notify_Handle__label__E", "ti_sdo_ipc_Notify_Module__startupDone__E", "ti_sdo_ipc_Notify_Object__create__E", "ti_sdo_ipc_Notify_Object__delete__E", "ti_sdo_ipc_Notify_Object__destruct__E", "ti_sdo_ipc_Notify_Object__get__E", "ti_sdo_ipc_Notify_Object__first__E", "ti_sdo_ipc_Notify_Object__next__E", "ti_sdo_ipc_Notify_Params__init__E", "ti_sdo_ipc_Notify_detach__E", "ti_sdo_ipc_Notify_exec__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_alreadyRegistered", "A_notRegistered", "A_reservedEvent", "A_outOfOrderNesting", "A_invArgument", "A_internal"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.Notify.Object", "ti.sdo.ipc"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "detach", "entry", "0x%x", "exit", "%d"));
        loggables.add(Global.newObject("name", "exec", "entry", "%p, 0x%x, 0x%x", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Notify", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Notify");
    }

    void GateMP_RemoteSystemProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.GateMP_RemoteSystemProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Instance", "ti.sdo.ipc"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Params", "ti.sdo.ipc"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Params", "ti.sdo.ipc")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Handle", "ti.sdo.ipc"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$GateMP_RemoteSystemProxy$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.query", "ti.sdo.ipc"));
        vo.bind("getReservedMask", om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.getReservedMask", "ti.sdo.ipc"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.sharedMemReq", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__Handle__label", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__Module__startupDone", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__Object__create", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__Object__delete", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__Object__destruct", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__Object__get", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__Object__first", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__Object__next", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__Params__init", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__Proxy__abstract", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__Proxy__delegate", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__queryMeta", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__query", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__enter", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__leave", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__getNumResources", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__getReservedMask", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__sharedMemReq", "ti_sdo_ipc_GateMP_RemoteSystemProxy_DELEGATE__getRemoteStatus$view"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Object", "ti.sdo.ipc"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy.Instance_State", "ti.sdo.ipc"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("GateMP_RemoteSystemProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GateMP_RemoteSystemProxy");
    }

    void GateMP_RemoteCustom1Proxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.GateMP_RemoteCustom1Proxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Instance", "ti.sdo.ipc"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Params", "ti.sdo.ipc"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Params", "ti.sdo.ipc")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Handle", "ti.sdo.ipc"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$GateMP_RemoteCustom1Proxy$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.query", "ti.sdo.ipc"));
        vo.bind("getReservedMask", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.getReservedMask", "ti.sdo.ipc"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.sharedMemReq", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__Handle__label", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__Module__startupDone", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__Object__create", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__Object__delete", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__Object__destruct", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__Object__get", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__Object__first", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__Object__next", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__Params__init", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__Proxy__abstract", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__Proxy__delegate", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__queryMeta", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__query", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__enter", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__leave", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__getNumResources", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__getReservedMask", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__sharedMemReq", "ti_sdo_ipc_GateMP_RemoteCustom1Proxy_DELEGATE__getRemoteStatus$view"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Object", "ti.sdo.ipc"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy.Instance_State", "ti.sdo.ipc"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("GateMP_RemoteCustom1Proxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GateMP_RemoteCustom1Proxy");
    }

    void GateMP_RemoteCustom2Proxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.GateMP_RemoteCustom2Proxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Instance", "ti.sdo.ipc"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Params", "ti.sdo.ipc"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Params", "ti.sdo.ipc")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Handle", "ti.sdo.ipc"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$GateMP_RemoteCustom2Proxy$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.query", "ti.sdo.ipc"));
        vo.bind("getReservedMask", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.getReservedMask", "ti.sdo.ipc"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.sharedMemReq", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__Handle__label", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__Module__startupDone", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__Object__create", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__Object__delete", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__Object__destruct", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__Object__get", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__Object__first", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__Object__next", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__Params__init", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__Proxy__abstract", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__Proxy__delegate", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__queryMeta", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__query", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__enter", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__leave", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__getNumResources", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__getReservedMask", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__sharedMemReq", "ti_sdo_ipc_GateMP_RemoteCustom2Proxy_DELEGATE__getRemoteStatus$view"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Object", "ti.sdo.ipc"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy.Instance_State", "ti.sdo.ipc"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("GateMP_RemoteCustom2Proxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GateMP_RemoteCustom2Proxy");
    }

    void MessageQ_SetupTransportProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.MessageQ_SetupTransportProxy", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.MessageQ_SetupTransportProxy.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.MessageQ_SetupTransportProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("attach", om.findStrict("ti.sdo.ipc.MessageQ_SetupTransportProxy.attach", "ti.sdo.ipc"));
        vo.bind("detach", om.findStrict("ti.sdo.ipc.MessageQ_SetupTransportProxy.detach", "ti.sdo.ipc"));
        vo.bind("isRegistered", om.findStrict("ti.sdo.ipc.MessageQ_SetupTransportProxy.isRegistered", "ti.sdo.ipc"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.MessageQ_SetupTransportProxy.sharedMemReq", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__Handle__label", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__Module__startupDone", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__Object__create", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__Object__delete", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__Object__destruct", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__Object__get", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__Object__first", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__Object__next", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__Params__init", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__Proxy__abstract", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__Proxy__delegate", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__attach", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__detach", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__isRegistered", "ti_sdo_ipc_MessageQ_SetupTransportProxy_DELEGATE__sharedMemReq"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("MessageQ_SetupTransportProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("MessageQ_SetupTransportProxy");
    }

    void Notify_SetupProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.Notify_SetupProxy", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify_SetupProxy.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.Notify_SetupProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("attach", om.findStrict("ti.sdo.ipc.Notify_SetupProxy.attach", "ti.sdo.ipc"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.Notify_SetupProxy.sharedMemReq", "ti.sdo.ipc"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.Notify_SetupProxy.numIntLines", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_Notify_SetupProxy_DELEGATE__Handle__label", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__Module__startupDone", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__Object__create", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__Object__delete", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__Object__destruct", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__Object__get", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__Object__first", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__Object__next", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__Params__init", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__Proxy__abstract", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__Proxy__delegate", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__attach", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__sharedMemReq", "ti_sdo_ipc_Notify_SetupProxy_DELEGATE__numIntLines"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Notify_SetupProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Notify_SetupProxy");
    }

    void Notify_Module_GateProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy", "ti.sdo.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Module", "ti.sdo.ipc");
        vo.init2(po, "ti.sdo.ipc.Notify_Module_GateProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Instance", "ti.sdo.ipc"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Params", "ti.sdo.ipc"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Params", "ti.sdo.ipc")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Handle", "ti.sdo.ipc"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc", "ti.sdo.ipc"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$Notify_Module_GateProxy$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.query", "ti.sdo.ipc"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__Handle__label", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__Module__startupDone", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__Object__create", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__Object__delete", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__Object__destruct", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__Object__get", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__Object__first", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__Object__next", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__Params__init", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__Proxy__abstract", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__Proxy__delegate", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__queryMeta", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__query", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__enter", "ti_sdo_ipc_Notify_Module_GateProxy_DELEGATE__leave"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Object", "ti.sdo.ipc"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy.Instance_State", "ti.sdo.ipc"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Notify_Module_GateProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Notify_Module_GateProxy");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sdo.ipc")).findStrict("PARAMS", "ti.sdo.ipc");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.GateMP", "ti.sdo.ipc")).findStrict("PARAMS", "ti.sdo.ipc");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.MessageQ", "ti.sdo.ipc")).findStrict("PARAMS", "ti.sdo.ipc");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.ListMP", "ti.sdo.ipc")).findStrict("PARAMS", "ti.sdo.ipc");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.Notify", "ti.sdo.ipc")).findStrict("PARAMS", "ti.sdo.ipc");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy", "ti.sdo.ipc")).findStrict("PARAMS", "ti.sdo.ipc");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy", "ti.sdo.ipc")).findStrict("PARAMS", "ti.sdo.ipc");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy", "ti.sdo.ipc")).findStrict("PARAMS", "ti.sdo.ipc");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy", "ti.sdo.ipc")).findStrict("PARAMS", "ti.sdo.ipc");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.Build", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.GateMP", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.MessageQ", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.SharedRegion", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.ListMP", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.Ipc", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.Notify", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.GateMP_RemoteSystemProxy", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom1Proxy", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.GateMP_RemoteCustom2Proxy", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.MessageQ_SetupTransportProxy", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.Notify_SetupProxy", "ti.sdo.ipc"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.Notify_Module_GateProxy", "ti.sdo.ipc"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.GateMP", "ti.sdo.ipc");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Gate Resources", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE"), "viewInitFxn", "viewInitModule", "structName", "ModuleView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.MessageQ", "ti.sdo.ipc");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Queues", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitQueues", "structName", "QueuesView")}), Global.newArray(new Object[]{"Messages", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE_DATA"), "viewInitFxn", "viewInitMessages", "structName", "MessagesView")}), Global.newArray(new Object[]{"Module", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE"), "viewInitFxn", "viewInitModule", "structName", "ModuleView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.SharedRegion", "ti.sdo.ipc");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Regions", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE_DATA"), "viewInitFxn", "viewInitRegions", "structName", "RegionView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.ListMP", "ti.sdo.ipc");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Lists", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE_DATA"), "viewInitFxn", "viewInitLists", "structName", "ElemView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.Ipc", "ti.sdo.ipc");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Module", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE_DATA"), "viewInitFxn", "viewInitModule", "structName", "ModuleView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.Notify", "ti.sdo.ipc");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"EventListeners", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE_DATA"), "viewInitFxn", "viewInitData", "structName", "EventDataView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.Build")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.GateMP")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.MessageQ")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.SharedRegion")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.ListMP")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.Ipc")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.Notify")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.GateMP_RemoteSystemProxy")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.GateMP_RemoteCustom1Proxy")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.GateMP_RemoteCustom2Proxy")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.MessageQ_SetupTransportProxy")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.Notify_SetupProxy")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.Notify_Module_GateProxy")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc")).add(pkgV);
    }

    public void exec( Scriptable xdcO, Session ses )
    {
        this.xdcO = xdcO;
        this.ses = ses;
        om = (Value.Obj)xdcO.get("om", null);

        Object o = om.geto("$name");
        String s = o instanceof String ? (String)o : null;
        isCFG = s != null && s.equals("cfg");
        isROV = s != null && s.equals("rov");

        $$IMPORTS();
        $$OBJECTS();
        Build$$OBJECTS();
        GateMP$$OBJECTS();
        MessageQ$$OBJECTS();
        SharedRegion$$OBJECTS();
        ListMP$$OBJECTS();
        Ipc$$OBJECTS();
        Notify$$OBJECTS();
        GateMP_RemoteSystemProxy$$OBJECTS();
        GateMP_RemoteCustom1Proxy$$OBJECTS();
        GateMP_RemoteCustom2Proxy$$OBJECTS();
        MessageQ_SetupTransportProxy$$OBJECTS();
        Notify_SetupProxy$$OBJECTS();
        Notify_Module_GateProxy$$OBJECTS();
        Build$$CONSTS();
        GateMP$$CONSTS();
        MessageQ$$CONSTS();
        SharedRegion$$CONSTS();
        ListMP$$CONSTS();
        Ipc$$CONSTS();
        Notify$$CONSTS();
        GateMP_RemoteSystemProxy$$CONSTS();
        GateMP_RemoteCustom1Proxy$$CONSTS();
        GateMP_RemoteCustom2Proxy$$CONSTS();
        MessageQ_SetupTransportProxy$$CONSTS();
        Notify_SetupProxy$$CONSTS();
        Notify_Module_GateProxy$$CONSTS();
        Build$$CREATES();
        GateMP$$CREATES();
        MessageQ$$CREATES();
        SharedRegion$$CREATES();
        ListMP$$CREATES();
        Ipc$$CREATES();
        Notify$$CREATES();
        GateMP_RemoteSystemProxy$$CREATES();
        GateMP_RemoteCustom1Proxy$$CREATES();
        GateMP_RemoteCustom2Proxy$$CREATES();
        MessageQ_SetupTransportProxy$$CREATES();
        Notify_SetupProxy$$CREATES();
        Notify_Module_GateProxy$$CREATES();
        Build$$FUNCTIONS();
        GateMP$$FUNCTIONS();
        MessageQ$$FUNCTIONS();
        SharedRegion$$FUNCTIONS();
        ListMP$$FUNCTIONS();
        Ipc$$FUNCTIONS();
        Notify$$FUNCTIONS();
        GateMP_RemoteSystemProxy$$FUNCTIONS();
        GateMP_RemoteCustom1Proxy$$FUNCTIONS();
        GateMP_RemoteCustom2Proxy$$FUNCTIONS();
        MessageQ_SetupTransportProxy$$FUNCTIONS();
        Notify_SetupProxy$$FUNCTIONS();
        Notify_Module_GateProxy$$FUNCTIONS();
        Build$$SIZES();
        GateMP$$SIZES();
        MessageQ$$SIZES();
        SharedRegion$$SIZES();
        ListMP$$SIZES();
        Ipc$$SIZES();
        Notify$$SIZES();
        GateMP_RemoteSystemProxy$$SIZES();
        GateMP_RemoteCustom1Proxy$$SIZES();
        GateMP_RemoteCustom2Proxy$$SIZES();
        MessageQ_SetupTransportProxy$$SIZES();
        Notify_SetupProxy$$SIZES();
        Notify_Module_GateProxy$$SIZES();
        Build$$TYPES();
        GateMP$$TYPES();
        MessageQ$$TYPES();
        SharedRegion$$TYPES();
        ListMP$$TYPES();
        Ipc$$TYPES();
        Notify$$TYPES();
        GateMP_RemoteSystemProxy$$TYPES();
        GateMP_RemoteCustom1Proxy$$TYPES();
        GateMP_RemoteCustom2Proxy$$TYPES();
        MessageQ_SetupTransportProxy$$TYPES();
        Notify_SetupProxy$$TYPES();
        Notify_Module_GateProxy$$TYPES();
        if (isROV) {
            Build$$ROV();
            GateMP$$ROV();
            MessageQ$$ROV();
            SharedRegion$$ROV();
            ListMP$$ROV();
            Ipc$$ROV();
            Notify$$ROV();
            GateMP_RemoteSystemProxy$$ROV();
            GateMP_RemoteCustom1Proxy$$ROV();
            GateMP_RemoteCustom2Proxy$$ROV();
            MessageQ_SetupTransportProxy$$ROV();
            Notify_SetupProxy$$ROV();
            Notify_Module_GateProxy$$ROV();
        }//isROV
        $$SINGLETONS();
        Build$$SINGLETONS();
        GateMP$$SINGLETONS();
        MessageQ$$SINGLETONS();
        SharedRegion$$SINGLETONS();
        ListMP$$SINGLETONS();
        Ipc$$SINGLETONS();
        Notify$$SINGLETONS();
        GateMP_RemoteSystemProxy$$SINGLETONS();
        GateMP_RemoteCustom1Proxy$$SINGLETONS();
        GateMP_RemoteCustom2Proxy$$SINGLETONS();
        MessageQ_SetupTransportProxy$$SINGLETONS();
        Notify_SetupProxy$$SINGLETONS();
        Notify_Module_GateProxy$$SINGLETONS();
        $$INITIALIZATION();
    }
}
