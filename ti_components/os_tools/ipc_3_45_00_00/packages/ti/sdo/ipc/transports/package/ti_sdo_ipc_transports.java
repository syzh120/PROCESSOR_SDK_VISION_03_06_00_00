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

public class ti_sdo_ipc_transports
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
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.knl");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.interfaces");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.utils");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.transports.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.transports", new Value.Obj("ti.sdo.ipc.transports", pkgP));
    }

    void TransportShm$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShm.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.transports.TransportShm", new Value.Obj("ti.sdo.ipc.transports.TransportShm", po));
        pkgV.bind("TransportShm", vo);
        // decls 
        om.bind("ti.sdo.ipc.transports.TransportShm.Status", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Status", "ti.sdo.ipc.transports"));
        om.bind("ti.sdo.ipc.transports.TransportShm.Reason", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason", "ti.sdo.ipc.transports"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShm$$Attrs", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShm.Attrs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShm$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShm.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.transports.TransportShm.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShm$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShm.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShm$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShm.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.transports.TransportShm.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.transports.TransportShm.Object", om.findStrict("ti.sdo.ipc.transports.TransportShm.Instance_State", "ti.sdo.ipc.transports"));
        }//isROV
    }

    void TransportShmSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.transports.TransportShmSetup", new Value.Obj("ti.sdo.ipc.transports.TransportShmSetup", po));
        pkgV.bind("TransportShmSetup", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmSetup$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShmSetup.Module_State", new Proto.Str(spo, false));
    }

    void TransportShmCirc$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmCirc.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.transports.TransportShmCirc", new Value.Obj("ti.sdo.ipc.transports.TransportShmCirc", po));
        pkgV.bind("TransportShmCirc", vo);
        // decls 
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.Status", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Status", "ti.sdo.ipc.transports"));
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.Reason", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason", "ti.sdo.ipc.transports"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmCirc$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmCirc$$EventDataView", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.EventDataView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmCirc$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.transports.TransportShmCirc.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmCirc$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmCirc$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.transports.TransportShmCirc.Object", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Instance_State", "ti.sdo.ipc.transports"));
        }//isROV
    }

    void TransportShmCircSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmCircSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.transports.TransportShmCircSetup", new Value.Obj("ti.sdo.ipc.transports.TransportShmCircSetup", po));
        pkgV.bind("TransportShmCircSetup", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmCircSetup$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShmCircSetup.Module_State", new Proto.Str(spo, false));
    }

    void TransportShmNotify$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmNotify.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.transports.TransportShmNotify", new Value.Obj("ti.sdo.ipc.transports.TransportShmNotify", po));
        pkgV.bind("TransportShmNotify", vo);
        // decls 
        om.bind("ti.sdo.ipc.transports.TransportShmNotify.Status", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Status", "ti.sdo.ipc.transports"));
        om.bind("ti.sdo.ipc.transports.TransportShmNotify.Reason", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason", "ti.sdo.ipc.transports"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmNotify$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShmNotify.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.transports.TransportShmNotify.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmNotify$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShmNotify.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmNotify$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShmNotify.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.transports.TransportShmNotify.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.transports.TransportShmNotify.Object", om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Instance_State", "ti.sdo.ipc.transports"));
        }//isROV
    }

    void TransportShmNotifySetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup", new Value.Obj("ti.sdo.ipc.transports.TransportShmNotifySetup", po));
        pkgV.bind("TransportShmNotifySetup", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup.Module_State", new Proto.Str(spo, false));
    }

    void TransportNullSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.transports.TransportNullSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.transports.TransportNullSetup", new Value.Obj("ti.sdo.ipc.transports.TransportNullSetup", po));
        pkgV.bind("TransportNullSetup", vo);
        // decls 
    }

    void TransportShm$$CONSTS()
    {
        // module TransportShm
        om.bind("ti.sdo.ipc.transports.TransportShm.UP", 0xBADC0FFEL);
        om.bind("ti.sdo.ipc.transports.TransportShm.setErrFxn", new Extern("ti_sdo_ipc_transports_TransportShm_setErrFxn__E", "xdc_Void(*)(xdc_Void(*)(ti_sdo_ipc_interfaces_IMessageQTransport_Reason,ti_sdo_ipc_interfaces_IMessageQTransport_Handle,xdc_Ptr,xdc_UArg))", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShm.openByAddr", new Extern("ti_sdo_ipc_transports_TransportShm_openByAddr__E", "xdc_Int(*)(xdc_Ptr,ti_sdo_ipc_transports_TransportShm_Handle*,xdc_runtime_Error_Block*)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShm.close", new Extern("ti_sdo_ipc_transports_TransportShm_close__E", "xdc_Void(*)(ti_sdo_ipc_transports_TransportShm_Handle*)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShm.sharedMemReq", new Extern("ti_sdo_ipc_transports_TransportShm_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_transports_TransportShm_Params*)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShm.swiFxn", new Extern("ti_sdo_ipc_transports_TransportShm_swiFxn__I", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShm.notifyFxn", new Extern("ti_sdo_ipc_transports_TransportShm_notifyFxn__I", "xdc_Void(*)(xdc_UInt16,xdc_UInt16,xdc_UInt32,xdc_UArg,xdc_UInt32)", true, false));
    }

    void TransportShmSetup$$CONSTS()
    {
        // module TransportShmSetup
        om.bind("ti.sdo.ipc.transports.TransportShmSetup.attach", new Extern("ti_sdo_ipc_transports_TransportShmSetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmSetup.detach", new Extern("ti_sdo_ipc_transports_TransportShmSetup_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmSetup.isRegistered", new Extern("ti_sdo_ipc_transports_TransportShmSetup_isRegistered__E", "xdc_Bool(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmSetup.sharedMemReq", new Extern("ti_sdo_ipc_transports_TransportShmSetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_Ptr)", true, false));
    }

    void TransportShmCirc$$CONSTS()
    {
        // module TransportShmCirc
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.setErrFxn", new Extern("ti_sdo_ipc_transports_TransportShmCirc_setErrFxn__E", "xdc_Void(*)(xdc_Void(*)(ti_sdo_ipc_interfaces_IMessageQTransport_Reason,ti_sdo_ipc_interfaces_IMessageQTransport_Handle,xdc_Ptr,xdc_UArg))", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.sharedMemReq", new Extern("ti_sdo_ipc_transports_TransportShmCirc_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_transports_TransportShmCirc_Params*)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.swiFxn", new Extern("ti_sdo_ipc_transports_TransportShmCirc_swiFxn__I", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmCirc.notifyFxn", new Extern("ti_sdo_ipc_transports_TransportShmCirc_notifyFxn__I", "xdc_Void(*)(xdc_UInt16,xdc_UInt16,xdc_UInt32,xdc_UArg,xdc_UInt32)", true, false));
    }

    void TransportShmCircSetup$$CONSTS()
    {
        // module TransportShmCircSetup
        om.bind("ti.sdo.ipc.transports.TransportShmCircSetup.attach", new Extern("ti_sdo_ipc_transports_TransportShmCircSetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmCircSetup.detach", new Extern("ti_sdo_ipc_transports_TransportShmCircSetup_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmCircSetup.isRegistered", new Extern("ti_sdo_ipc_transports_TransportShmCircSetup_isRegistered__E", "xdc_Bool(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmCircSetup.sharedMemReq", new Extern("ti_sdo_ipc_transports_TransportShmCircSetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_Ptr)", true, false));
    }

    void TransportShmNotify$$CONSTS()
    {
        // module TransportShmNotify
        om.bind("ti.sdo.ipc.transports.TransportShmNotify.setErrFxn", new Extern("ti_sdo_ipc_transports_TransportShmNotify_setErrFxn__E", "xdc_Void(*)(xdc_Void(*)(ti_sdo_ipc_interfaces_IMessageQTransport_Reason,ti_sdo_ipc_interfaces_IMessageQTransport_Handle,xdc_Ptr,xdc_UArg))", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmNotify.notifyFxn", new Extern("ti_sdo_ipc_transports_TransportShmNotify_notifyFxn__I", "xdc_Void(*)(xdc_UInt16,xdc_UInt16,xdc_UInt32,xdc_UArg,xdc_UInt32)", true, false));
    }

    void TransportShmNotifySetup$$CONSTS()
    {
        // module TransportShmNotifySetup
        om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup.attach", new Extern("ti_sdo_ipc_transports_TransportShmNotifySetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup.detach", new Extern("ti_sdo_ipc_transports_TransportShmNotifySetup_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup.isRegistered", new Extern("ti_sdo_ipc_transports_TransportShmNotifySetup_isRegistered__E", "xdc_Bool(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup.sharedMemReq", new Extern("ti_sdo_ipc_transports_TransportShmNotifySetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_Ptr)", true, false));
    }

    void TransportNullSetup$$CONSTS()
    {
        // module TransportNullSetup
        om.bind("ti.sdo.ipc.transports.TransportNullSetup.attach", new Extern("ti_sdo_ipc_transports_TransportNullSetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportNullSetup.detach", new Extern("ti_sdo_ipc_transports_TransportNullSetup_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportNullSetup.isRegistered", new Extern("ti_sdo_ipc_transports_TransportNullSetup_isRegistered__E", "xdc_Bool(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.transports.TransportNullSetup.sharedMemReq", new Extern("ti_sdo_ipc_transports_TransportNullSetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_Ptr)", true, false));
    }

    void TransportShm$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$transports$TransportShm$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.transports.TransportShm.create() called before xdc.useModule('ti.sdo.ipc.transports.TransportShm')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.procId, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.transports.TransportShm$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.transports.TransportShm.Module", "ti.sdo.ipc.transports"), om.findStrict("ti.sdo.ipc.transports.TransportShm.Instance", "ti.sdo.ipc.transports"), 2, 1, false));
                        fxn.addArg(0, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.transports.TransportShm.Params", "ti.sdo.ipc.transports"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$transports$TransportShm$$create = function( procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.transports.TransportShm'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.transports.TransportShm.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.transports']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.transports.TransportShm'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [procId]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.transports.TransportShm'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.transports.TransportShm$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.transports.TransportShm.Module", "ti.sdo.ipc.transports"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.transports.TransportShm$$Object", "ti.sdo.ipc.transports"), null);
                        fxn.addArg(1, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.transports.TransportShm.Params", "ti.sdo.ipc.transports"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$transports$TransportShm$$construct = function( __obj, procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.transports.TransportShm'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.transports.TransportShm'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.transports.TransportShm'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void TransportShmSetup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TransportShmCirc$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$transports$TransportShmCirc$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.transports.TransportShmCirc.create() called before xdc.useModule('ti.sdo.ipc.transports.TransportShmCirc')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.procId, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.transports.TransportShmCirc$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Module", "ti.sdo.ipc.transports"), om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Instance", "ti.sdo.ipc.transports"), 2, 1, false));
                        fxn.addArg(0, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Params", "ti.sdo.ipc.transports"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$transports$TransportShmCirc$$create = function( procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.transports.TransportShmCirc'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.transports.TransportShmCirc.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.transports']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.transports.TransportShmCirc'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [procId]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.transports.TransportShmCirc'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.transports.TransportShmCirc$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Module", "ti.sdo.ipc.transports"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc$$Object", "ti.sdo.ipc.transports"), null);
                        fxn.addArg(1, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Params", "ti.sdo.ipc.transports"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$transports$TransportShmCirc$$construct = function( __obj, procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.transports.TransportShmCirc'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.transports.TransportShmCirc'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.transports.TransportShmCirc'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void TransportShmCircSetup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TransportShmNotify$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$transports$TransportShmNotify$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.transports.TransportShmNotify.create() called before xdc.useModule('ti.sdo.ipc.transports.TransportShmNotify')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.procId, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.transports.TransportShmNotify$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Module", "ti.sdo.ipc.transports"), om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Instance", "ti.sdo.ipc.transports"), 2, 1, false));
                        fxn.addArg(0, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Params", "ti.sdo.ipc.transports"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$transports$TransportShmNotify$$create = function( procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.transports.TransportShmNotify'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.transports.TransportShmNotify.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.transports']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.transports.TransportShmNotify'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [procId]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.transports.TransportShmNotify'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.transports.TransportShmNotify$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Module", "ti.sdo.ipc.transports"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify$$Object", "ti.sdo.ipc.transports"), null);
                        fxn.addArg(1, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Params", "ti.sdo.ipc.transports"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$transports$TransportShmNotify$$construct = function( __obj, procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.transports.TransportShmNotify'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.transports.TransportShmNotify'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.transports.TransportShmNotify'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void TransportShmNotifySetup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TransportNullSetup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TransportShm$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TransportShmSetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TransportShmCirc$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TransportShmCircSetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TransportShmNotify$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TransportShmNotifySetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TransportNullSetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TransportShm$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.transports.TransportShm.Attrs", "ti.sdo.ipc.transports");
        sizes.clear();
        sizes.add(Global.newArray("flag", "UInt32"));
        sizes.add(Global.newArray("creatorProcId", "UInt32"));
        sizes.add(Global.newArray("notifyEventId", "UInt32"));
        sizes.add(Global.newArray("priority", "UInt16"));
        sizes.add(Global.newArray("gateMPAddr", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.transports.TransportShm.Attrs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.transports.TransportShm.Attrs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.transports.TransportShm.Attrs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.transports.TransportShm.Instance_State", "ti.sdo.ipc.transports");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("self", "UPtr"));
        sizes.add(Global.newArray("other", "UPtr"));
        sizes.add(Global.newArray("localList", "UPtr"));
        sizes.add(Global.newArray("remoteList", "UPtr"));
        sizes.add(Global.newArray("status", "UInt32"));
        sizes.add(Global.newArray("objType", "Nti.sdo.ipc.Ipc.ObjType;;0x1;0x2;0x4;0x8;0x10;0x20"));
        sizes.add(Global.newArray("allocSize", "USize"));
        sizes.add(Global.newArray("cacheEnabled", "UShort"));
        sizes.add(Global.newArray("regionId", "UInt16"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        sizes.add(Global.newArray("priority", "UInt16"));
        sizes.add(Global.newArray("gate", "UPtr"));
        sizes.add(Global.newArray("swiObj", "Sti.sysbios.knl.Swi;Instance_State"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.transports.TransportShm.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.transports.TransportShm.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.transports.TransportShm.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TransportShmSetup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.transports.TransportShmSetup.Module_State", "ti.sdo.ipc.transports");
        sizes.clear();
        sizes.add(Global.newArray("handles", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.transports.TransportShmSetup.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.transports.TransportShmSetup.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.transports.TransportShmSetup.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TransportShmCirc$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Instance_State", "ti.sdo.ipc.transports");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("putBuffer", "UPtr"));
        sizes.add(Global.newArray("putReadIndex", "UPtr"));
        sizes.add(Global.newArray("putWriteIndex", "UPtr"));
        sizes.add(Global.newArray("getBuffer", "UPtr"));
        sizes.add(Global.newArray("getReadIndex", "UPtr"));
        sizes.add(Global.newArray("getWriteIndex", "UPtr"));
        sizes.add(Global.newArray("opCacheSize", "USize"));
        sizes.add(Global.newArray("regionId", "UInt16"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        sizes.add(Global.newArray("cacheEnabled", "UShort"));
        sizes.add(Global.newArray("priority", "UInt16"));
        sizes.add(Global.newArray("objType", "Nti.sdo.ipc.Ipc.ObjType;;0x1;0x2;0x4;0x8;0x10;0x20"));
        sizes.add(Global.newArray("swiObj", "Sti.sysbios.knl.Swi;Instance_State"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.transports.TransportShmCirc.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.transports.TransportShmCirc.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.transports.TransportShmCirc.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TransportShmCircSetup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup.Module_State", "ti.sdo.ipc.transports");
        sizes.clear();
        sizes.add(Global.newArray("handles", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.transports.TransportShmCircSetup.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.transports.TransportShmCircSetup.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.transports.TransportShmCircSetup.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TransportShmNotify$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Instance_State", "ti.sdo.ipc.transports");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        sizes.add(Global.newArray("priority", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.transports.TransportShmNotify.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.transports.TransportShmNotify.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.transports.TransportShmNotify.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TransportShmNotifySetup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup.Module_State", "ti.sdo.ipc.transports");
        sizes.clear();
        sizes.add(Global.newArray("handles", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.transports.TransportShmNotifySetup.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.transports.TransportShmNotifySetup.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.transports.TransportShmNotifySetup.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TransportNullSetup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void TransportShm$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/transports/TransportShm.xs");
        om.bind("ti.sdo.ipc.transports.TransportShm$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm.Module", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShm.Module", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Module", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("UP", Proto.Elm.newCNum("(xdc_UInt32)"), 0xBADC0FFEL, "rh");
        if (isCFG) {
            po.addFld("notifyEventId", Proto.Elm.newCNum("(xdc_UInt16)"), 2L, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.transports.TransportShm$$create", "ti.sdo.ipc.transports"), Global.get("ti$sdo$ipc$transports$TransportShm$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.transports.TransportShm$$construct", "ti.sdo.ipc.transports"), Global.get("ti$sdo$ipc$transports$TransportShm$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShm$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShm$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShm$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShm$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShm$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShm$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm.Instance", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShm.Instance", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Instance", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("UP", Proto.Elm.newCNum("(xdc_UInt32)"), 0xBADC0FFEL, "rh");
        if (isCFG) {
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.transports"), null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.transports"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm$$Params", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShm.Params", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport$$Params", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("UP", Proto.Elm.newCNum("(xdc_UInt32)"), 0xBADC0FFEL, "rh");
        if (isCFG) {
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.transports"), null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.transports"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm$$Object", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShm.Object", om.findStrict("ti.sdo.ipc.transports.TransportShm.Instance", "ti.sdo.ipc.transports"));
        // struct TransportShm.Attrs
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm$$Attrs", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShm.Attrs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("flag", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("creatorProcId", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("notifyEventId", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("priority", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("gateMPAddr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct TransportShm.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm$$Instance_State", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShm.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("self", new Proto.Adr("ti_sdo_ipc_transports_TransportShm_Attrs*", "PS"), $$UNDEF, "w");
                po.addFld("other", new Proto.Adr("ti_sdo_ipc_transports_TransportShm_Attrs*", "PS"), $$UNDEF, "w");
                po.addFld("localList", (Proto)om.findStrict("ti.sdo.ipc.ListMP.Handle", "ti.sdo.ipc.transports"), $$UNDEF, "w");
                po.addFld("remoteList", (Proto)om.findStrict("ti.sdo.ipc.ListMP.Handle", "ti.sdo.ipc.transports"), $$UNDEF, "w");
                po.addFld("status", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("objType", (Proto)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc.transports"), $$UNDEF, "w");
                po.addFld("allocSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("priority", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.transports"), $$UNDEF, "w");
                po.addFldV("swiObj", (Proto)om.findStrict("ti.sysbios.knl.Swi.Object", "ti.sdo.ipc.transports"), $$DEFAULT, "wh", $$objFldGet, $$objFldSet);
                po.addFld("Object_field_swiObj", (Proto)om.findStrict("ti.sysbios.knl.Swi.Object", "ti.sdo.ipc.transports"), $$DEFAULT, "w");
    }

    void TransportShmSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/transports/TransportShmSetup.xs");
        om.bind("ti.sdo.ipc.transports.TransportShmSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmSetup.Module", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmSetup.Module", om.findStrict("ti.sdo.ipc.interfaces.ITransportSetup.Module", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct TransportShmSetup.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmSetup$$Module_State", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmSetup.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("handles", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.transports.TransportShm.Handle", "ti.sdo.ipc.transports"), false), $$DEFAULT, "w");
    }

    void TransportShmCirc$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/transports/TransportShmCirc.xs");
        om.bind("ti.sdo.ipc.transports.TransportShmCirc$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Module", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmCirc.Module", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Module", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.transports"), $$UNDEF, "wh");
            po.addFld("alwaysWriteBackMsg", $$T_Bool, true, "w");
            po.addFld("enableStats", $$T_Bool, false, "w");
            po.addFld("notifyEventId", Proto.Elm.newCNum("(xdc_UInt16)"), 2L, "w");
            po.addFld("numMsgs", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "w");
            po.addFld("maxIndex", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
            po.addFld("modIndex", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc$$create", "ti.sdo.ipc.transports"), Global.get("ti$sdo$ipc$transports$TransportShmCirc$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc$$construct", "ti.sdo.ipc.transports"), Global.get("ti$sdo$ipc$transports$TransportShmCirc$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmCirc$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmCirc$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmCirc$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmCirc$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmCirc$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmCirc$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Instance", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmCirc.Instance", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Instance", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.transports"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc$$Params", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmCirc.Params", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport$$Params", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.transports"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc$$Object", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmCirc.Object", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Instance", "ti.sdo.ipc.transports"));
        // struct TransportShmCirc.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc$$BasicView", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmCirc.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteProcName", $$T_Str, $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
        // struct TransportShmCirc.EventDataView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc$$EventDataView", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmCirc.EventDataView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("index", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("buffer", $$T_Str, $$UNDEF, "w");
                po.addFld("addr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("message", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct TransportShmCirc.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc$$Instance_State", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmCirc.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("putBuffer", new Proto.Adr("xdc_Ptr*", "PPv"), $$UNDEF, "w");
                po.addFld("putReadIndex", new Proto.Adr("xdc_Bits32*", "Pn"), $$UNDEF, "w");
                po.addFld("putWriteIndex", new Proto.Adr("xdc_Bits32*", "Pn"), $$UNDEF, "w");
                po.addFld("getBuffer", new Proto.Adr("xdc_Ptr*", "PPv"), $$UNDEF, "w");
                po.addFld("getReadIndex", new Proto.Adr("xdc_Bits32*", "Pn"), $$UNDEF, "w");
                po.addFld("getWriteIndex", new Proto.Adr("xdc_Bits32*", "Pn"), $$UNDEF, "w");
                po.addFld("opCacheSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("priority", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("objType", (Proto)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc.transports"), $$UNDEF, "w");
                po.addFldV("swiObj", (Proto)om.findStrict("ti.sysbios.knl.Swi.Object", "ti.sdo.ipc.transports"), $$DEFAULT, "wh", $$objFldGet, $$objFldSet);
                po.addFld("Object_field_swiObj", (Proto)om.findStrict("ti.sysbios.knl.Swi.Object", "ti.sdo.ipc.transports"), $$DEFAULT, "w");
    }

    void TransportShmCircSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/transports/TransportShmCircSetup.xs");
        om.bind("ti.sdo.ipc.transports.TransportShmCircSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup.Module", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmCircSetup.Module", om.findStrict("ti.sdo.ipc.interfaces.ITransportSetup.Module", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmCircSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmCircSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmCircSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmCircSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct TransportShmCircSetup.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup$$Module_State", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmCircSetup.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("handles", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Handle", "ti.sdo.ipc.transports"), false), $$DEFAULT, "w");
    }

    void TransportShmNotify$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/transports/TransportShmNotify.xs");
        om.bind("ti.sdo.ipc.transports.TransportShmNotify$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Module", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmNotify.Module", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Module", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("notifyEventId", Proto.Elm.newCNum("(xdc_UInt16)"), 2L, "w");
            po.addFld("alwaysWriteBackMsg", $$T_Bool, true, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify$$create", "ti.sdo.ipc.transports"), Global.get("ti$sdo$ipc$transports$TransportShmNotify$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify$$construct", "ti.sdo.ipc.transports"), Global.get("ti$sdo$ipc$transports$TransportShmNotify$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmNotify$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmNotify$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmNotify$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmNotify$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmNotify$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmNotify$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Instance", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmNotify.Instance", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Instance", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.transports"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify$$Params", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmNotify.Params", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport$$Params", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.transports"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify$$Object", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmNotify.Object", om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Instance", "ti.sdo.ipc.transports"));
        // struct TransportShmNotify.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify$$Instance_State", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmNotify.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("priority", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
    }

    void TransportShmNotifySetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/transports/TransportShmNotifySetup.xs");
        om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup.Module", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmNotifySetup.Module", om.findStrict("ti.sdo.ipc.interfaces.ITransportSetup.Module", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportShmNotifySetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct TransportShmNotifySetup.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup$$Module_State", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportShmNotifySetup.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("handles", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Handle", "ti.sdo.ipc.transports"), false), $$DEFAULT, "w");
    }

    void TransportNullSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/transports/TransportNullSetup.xs");
        om.bind("ti.sdo.ipc.transports.TransportNullSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportNullSetup.Module", "ti.sdo.ipc.transports");
        po.init("ti.sdo.ipc.transports.TransportNullSetup.Module", om.findStrict("ti.sdo.ipc.interfaces.ITransportSetup.Module", "ti.sdo.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportNullSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportNullSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportNullSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.transports.TransportNullSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void TransportShm$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm", "ti.sdo.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm$$Instance_State", "ti.sdo.ipc.transports");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.transports.TransportShm.Attrs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm$$Attrs", "ti.sdo.ipc.transports");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.transports.TransportShm.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm$$Instance_State", "ti.sdo.ipc.transports");
        po.bind("self$fetchDesc", Global.newObject("type", "ti.sdo.ipc.transports.TransportShm.Attrs", "isScalar", false));
        po.bind("other$fetchDesc", Global.newObject("type", "ti.sdo.ipc.transports.TransportShm.Attrs", "isScalar", false));
    }

    void TransportShmSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmSetup", "ti.sdo.ipc.transports");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.transports.TransportShmSetup.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmSetup$$Module_State", "ti.sdo.ipc.transports");
        po.bind("handles$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Ptr", "isScalar", true));
    }

    void TransportShmCirc$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc", "ti.sdo.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc$$Instance_State", "ti.sdo.ipc.transports");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.transports.TransportShmCirc.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc$$Instance_State", "ti.sdo.ipc.transports");
    }

    void TransportShmCircSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup", "ti.sdo.ipc.transports");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.transports.TransportShmCircSetup.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup$$Module_State", "ti.sdo.ipc.transports");
        po.bind("handles$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Ptr", "isScalar", true));
    }

    void TransportShmNotify$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify", "ti.sdo.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify$$Instance_State", "ti.sdo.ipc.transports");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.transports.TransportShmNotify.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify$$Instance_State", "ti.sdo.ipc.transports");
    }

    void TransportShmNotifySetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup", "ti.sdo.ipc.transports");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.transports.TransportShmNotifySetup.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup$$Module_State", "ti.sdo.ipc.transports");
        po.bind("handles$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Ptr", "isScalar", true));
    }

    void TransportNullSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportNullSetup", "ti.sdo.ipc.transports");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.transports.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.transports"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/transports/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.transports"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.transports"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.transports"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.transports"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.transports"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.transports"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.transports", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.transports");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.transports.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.transports'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.transports$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.transports$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.transports$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void TransportShm$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm", "ti.sdo.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShm.Module", "ti.sdo.ipc.transports");
        vo.init2(po, "ti.sdo.ipc.transports.TransportShm", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.transports.TransportShm$$capsule", "ti.sdo.ipc.transports"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.transports.TransportShm.Instance", "ti.sdo.ipc.transports"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.transports.TransportShm.Params", "ti.sdo.ipc.transports"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.transports.TransportShm.Params", "ti.sdo.ipc.transports")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.transports.TransportShm.Handle", "ti.sdo.ipc.transports"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.transports", "ti.sdo.ipc.transports"));
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
        vo.bind("Status", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Status", "ti.sdo.ipc.transports"));
        vo.bind("Reason", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason", "ti.sdo.ipc.transports"));
        mcfgs.add("errFxn");
        vo.bind("ErrFxn", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.ErrFxn", "ti.sdo.ipc.transports"));
        mcfgs.add("notifyEventId");
        vo.bind("Attrs", om.findStrict("ti.sdo.ipc.transports.TransportShm.Attrs", "ti.sdo.ipc.transports"));
        tdefs.add(om.findStrict("ti.sdo.ipc.transports.TransportShm.Attrs", "ti.sdo.ipc.transports"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.transports.TransportShm.Instance_State", "ti.sdo.ipc.transports"));
        tdefs.add(om.findStrict("ti.sdo.ipc.transports.TransportShm.Instance_State", "ti.sdo.ipc.transports"));
        vo.bind("S_SUCCESS", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.S_SUCCESS", "ti.sdo.ipc.transports"));
        vo.bind("E_FAIL", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.E_FAIL", "ti.sdo.ipc.transports"));
        vo.bind("E_ERROR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.E_ERROR", "ti.sdo.ipc.transports"));
        vo.bind("Reason_FAILEDPUT", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_FAILEDPUT", "ti.sdo.ipc.transports"));
        vo.bind("Reason_INTERNALERR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_INTERNALERR", "ti.sdo.ipc.transports"));
        vo.bind("Reason_PHYSICALERR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_PHYSICALERR", "ti.sdo.ipc.transports"));
        vo.bind("Reason_FAILEDALLOC", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_FAILEDALLOC", "ti.sdo.ipc.transports"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.transports")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.transports.TransportShm$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$transports$TransportShm$$__initObject"));
        }//isCFG
        vo.bind("setErrFxn", om.findStrict("ti.sdo.ipc.transports.TransportShm.setErrFxn", "ti.sdo.ipc.transports"));
        vo.bind("openByAddr", om.findStrict("ti.sdo.ipc.transports.TransportShm.openByAddr", "ti.sdo.ipc.transports"));
        vo.bind("close", om.findStrict("ti.sdo.ipc.transports.TransportShm.close", "ti.sdo.ipc.transports"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.transports.TransportShm.sharedMemReq", "ti.sdo.ipc.transports"));
        vo.bind("swiFxn", om.findStrict("ti.sdo.ipc.transports.TransportShm.swiFxn", "ti.sdo.ipc.transports"));
        vo.bind("notifyFxn", om.findStrict("ti.sdo.ipc.transports.TransportShm.notifyFxn", "ti.sdo.ipc.transports"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_transports_TransportShm_Handle__label__E", "ti_sdo_ipc_transports_TransportShm_Module__startupDone__E", "ti_sdo_ipc_transports_TransportShm_Object__create__E", "ti_sdo_ipc_transports_TransportShm_Object__delete__E", "ti_sdo_ipc_transports_TransportShm_Object__destruct__E", "ti_sdo_ipc_transports_TransportShm_Object__get__E", "ti_sdo_ipc_transports_TransportShm_Object__first__E", "ti_sdo_ipc_transports_TransportShm_Object__next__E", "ti_sdo_ipc_transports_TransportShm_Params__init__E", "ti_sdo_ipc_transports_TransportShm_setErrFxn__E", "ti_sdo_ipc_transports_TransportShm_getStatus__E", "ti_sdo_ipc_transports_TransportShm_put__E", "ti_sdo_ipc_transports_TransportShm_control__E", "ti_sdo_ipc_transports_TransportShm_openByAddr__E", "ti_sdo_ipc_transports_TransportShm_close__E", "ti_sdo_ipc_transports_TransportShm_sharedMemReq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.transports.TransportShm.Object", "ti.sdo.ipc.transports"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TransportShm", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TransportShm");
    }

    void TransportShmSetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmSetup", "ti.sdo.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmSetup.Module", "ti.sdo.ipc.transports");
        vo.init2(po, "ti.sdo.ipc.transports.TransportShmSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.transports.TransportShmSetup$$capsule", "ti.sdo.ipc.transports"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.transports", "ti.sdo.ipc.transports"));
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
        mcfgs.add("priority");
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.transports.TransportShmSetup.Module_State", "ti.sdo.ipc.transports"));
        tdefs.add(om.findStrict("ti.sdo.ipc.transports.TransportShmSetup.Module_State", "ti.sdo.ipc.transports"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.transports")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("attach", om.findStrict("ti.sdo.ipc.transports.TransportShmSetup.attach", "ti.sdo.ipc.transports"));
        vo.bind("detach", om.findStrict("ti.sdo.ipc.transports.TransportShmSetup.detach", "ti.sdo.ipc.transports"));
        vo.bind("isRegistered", om.findStrict("ti.sdo.ipc.transports.TransportShmSetup.isRegistered", "ti.sdo.ipc.transports"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.transports.TransportShmSetup.sharedMemReq", "ti.sdo.ipc.transports"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_transports_TransportShmSetup_Module__startupDone__E", "ti_sdo_ipc_transports_TransportShmSetup_attach__E", "ti_sdo_ipc_transports_TransportShmSetup_detach__E", "ti_sdo_ipc_transports_TransportShmSetup_isRegistered__E", "ti_sdo_ipc_transports_TransportShmSetup_sharedMemReq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TransportShmSetup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TransportShmSetup");
    }

    void TransportShmCirc$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc", "ti.sdo.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Module", "ti.sdo.ipc.transports");
        vo.init2(po, "ti.sdo.ipc.transports.TransportShmCirc", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc$$capsule", "ti.sdo.ipc.transports"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Instance", "ti.sdo.ipc.transports"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Params", "ti.sdo.ipc.transports"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Params", "ti.sdo.ipc.transports")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Handle", "ti.sdo.ipc.transports"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.transports", "ti.sdo.ipc.transports"));
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
        vo.bind("Status", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Status", "ti.sdo.ipc.transports"));
        vo.bind("Reason", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason", "ti.sdo.ipc.transports"));
        mcfgs.add("errFxn");
        vo.bind("ErrFxn", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.ErrFxn", "ti.sdo.ipc.transports"));
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.BasicView", "ti.sdo.ipc.transports"));
        tdefs.add(om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.BasicView", "ti.sdo.ipc.transports"));
        vo.bind("EventDataView", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.EventDataView", "ti.sdo.ipc.transports"));
        tdefs.add(om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.EventDataView", "ti.sdo.ipc.transports"));
        mcfgs.add("alwaysWriteBackMsg");
        mcfgs.add("enableStats");
        mcfgs.add("notifyEventId");
        mcfgs.add("numMsgs");
        mcfgs.add("maxIndex");
        icfgs.add("maxIndex");
        mcfgs.add("modIndex");
        icfgs.add("modIndex");
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Instance_State", "ti.sdo.ipc.transports"));
        tdefs.add(om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Instance_State", "ti.sdo.ipc.transports"));
        vo.bind("S_SUCCESS", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.S_SUCCESS", "ti.sdo.ipc.transports"));
        vo.bind("E_FAIL", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.E_FAIL", "ti.sdo.ipc.transports"));
        vo.bind("E_ERROR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.E_ERROR", "ti.sdo.ipc.transports"));
        vo.bind("Reason_FAILEDPUT", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_FAILEDPUT", "ti.sdo.ipc.transports"));
        vo.bind("Reason_INTERNALERR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_INTERNALERR", "ti.sdo.ipc.transports"));
        vo.bind("Reason_PHYSICALERR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_PHYSICALERR", "ti.sdo.ipc.transports"));
        vo.bind("Reason_FAILEDALLOC", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_FAILEDALLOC", "ti.sdo.ipc.transports"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.transports")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.transports.TransportShmCirc$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$transports$TransportShmCirc$$__initObject"));
        }//isCFG
        vo.bind("setErrFxn", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.setErrFxn", "ti.sdo.ipc.transports"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.sharedMemReq", "ti.sdo.ipc.transports"));
        vo.bind("swiFxn", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.swiFxn", "ti.sdo.ipc.transports"));
        vo.bind("notifyFxn", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.notifyFxn", "ti.sdo.ipc.transports"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_transports_TransportShmCirc_Handle__label__E", "ti_sdo_ipc_transports_TransportShmCirc_Module__startupDone__E", "ti_sdo_ipc_transports_TransportShmCirc_Object__create__E", "ti_sdo_ipc_transports_TransportShmCirc_Object__delete__E", "ti_sdo_ipc_transports_TransportShmCirc_Object__destruct__E", "ti_sdo_ipc_transports_TransportShmCirc_Object__get__E", "ti_sdo_ipc_transports_TransportShmCirc_Object__first__E", "ti_sdo_ipc_transports_TransportShmCirc_Object__next__E", "ti_sdo_ipc_transports_TransportShmCirc_Params__init__E", "ti_sdo_ipc_transports_TransportShmCirc_setErrFxn__E", "ti_sdo_ipc_transports_TransportShmCirc_getStatus__E", "ti_sdo_ipc_transports_TransportShmCirc_put__E", "ti_sdo_ipc_transports_TransportShmCirc_control__E", "ti_sdo_ipc_transports_TransportShmCirc_sharedMemReq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.transports.TransportShmCirc.Object", "ti.sdo.ipc.transports"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TransportShmCirc", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TransportShmCirc");
    }

    void TransportShmCircSetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup", "ti.sdo.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup.Module", "ti.sdo.ipc.transports");
        vo.init2(po, "ti.sdo.ipc.transports.TransportShmCircSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup$$capsule", "ti.sdo.ipc.transports"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.transports", "ti.sdo.ipc.transports"));
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
        mcfgs.add("priority");
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup.Module_State", "ti.sdo.ipc.transports"));
        tdefs.add(om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup.Module_State", "ti.sdo.ipc.transports"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.transports")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("attach", om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup.attach", "ti.sdo.ipc.transports"));
        vo.bind("detach", om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup.detach", "ti.sdo.ipc.transports"));
        vo.bind("isRegistered", om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup.isRegistered", "ti.sdo.ipc.transports"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup.sharedMemReq", "ti.sdo.ipc.transports"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_transports_TransportShmCircSetup_Module__startupDone__E", "ti_sdo_ipc_transports_TransportShmCircSetup_attach__E", "ti_sdo_ipc_transports_TransportShmCircSetup_detach__E", "ti_sdo_ipc_transports_TransportShmCircSetup_isRegistered__E", "ti_sdo_ipc_transports_TransportShmCircSetup_sharedMemReq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TransportShmCircSetup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TransportShmCircSetup");
    }

    void TransportShmNotify$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify", "ti.sdo.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Module", "ti.sdo.ipc.transports");
        vo.init2(po, "ti.sdo.ipc.transports.TransportShmNotify", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.transports.TransportShmNotify$$capsule", "ti.sdo.ipc.transports"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Instance", "ti.sdo.ipc.transports"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Params", "ti.sdo.ipc.transports"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Params", "ti.sdo.ipc.transports")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Handle", "ti.sdo.ipc.transports"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.transports", "ti.sdo.ipc.transports"));
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
        vo.bind("Status", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Status", "ti.sdo.ipc.transports"));
        vo.bind("Reason", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason", "ti.sdo.ipc.transports"));
        mcfgs.add("errFxn");
        vo.bind("ErrFxn", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.ErrFxn", "ti.sdo.ipc.transports"));
        mcfgs.add("notifyEventId");
        mcfgs.add("alwaysWriteBackMsg");
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Instance_State", "ti.sdo.ipc.transports"));
        tdefs.add(om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Instance_State", "ti.sdo.ipc.transports"));
        vo.bind("S_SUCCESS", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.S_SUCCESS", "ti.sdo.ipc.transports"));
        vo.bind("E_FAIL", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.E_FAIL", "ti.sdo.ipc.transports"));
        vo.bind("E_ERROR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.E_ERROR", "ti.sdo.ipc.transports"));
        vo.bind("Reason_FAILEDPUT", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_FAILEDPUT", "ti.sdo.ipc.transports"));
        vo.bind("Reason_INTERNALERR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_INTERNALERR", "ti.sdo.ipc.transports"));
        vo.bind("Reason_PHYSICALERR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_PHYSICALERR", "ti.sdo.ipc.transports"));
        vo.bind("Reason_FAILEDALLOC", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_FAILEDALLOC", "ti.sdo.ipc.transports"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.transports")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.transports.TransportShmNotify$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$transports$TransportShmNotify$$__initObject"));
        }//isCFG
        vo.bind("setErrFxn", om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.setErrFxn", "ti.sdo.ipc.transports"));
        vo.bind("notifyFxn", om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.notifyFxn", "ti.sdo.ipc.transports"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_transports_TransportShmNotify_Handle__label__E", "ti_sdo_ipc_transports_TransportShmNotify_Module__startupDone__E", "ti_sdo_ipc_transports_TransportShmNotify_Object__create__E", "ti_sdo_ipc_transports_TransportShmNotify_Object__delete__E", "ti_sdo_ipc_transports_TransportShmNotify_Object__destruct__E", "ti_sdo_ipc_transports_TransportShmNotify_Object__get__E", "ti_sdo_ipc_transports_TransportShmNotify_Object__first__E", "ti_sdo_ipc_transports_TransportShmNotify_Object__next__E", "ti_sdo_ipc_transports_TransportShmNotify_Params__init__E", "ti_sdo_ipc_transports_TransportShmNotify_setErrFxn__E", "ti_sdo_ipc_transports_TransportShmNotify_getStatus__E", "ti_sdo_ipc_transports_TransportShmNotify_put__E", "ti_sdo_ipc_transports_TransportShmNotify_control__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.transports.TransportShmNotify.Object", "ti.sdo.ipc.transports"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TransportShmNotify", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TransportShmNotify");
    }

    void TransportShmNotifySetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup", "ti.sdo.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup.Module", "ti.sdo.ipc.transports");
        vo.init2(po, "ti.sdo.ipc.transports.TransportShmNotifySetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup$$capsule", "ti.sdo.ipc.transports"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.transports", "ti.sdo.ipc.transports"));
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
        mcfgs.add("priority");
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup.Module_State", "ti.sdo.ipc.transports"));
        tdefs.add(om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup.Module_State", "ti.sdo.ipc.transports"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.transports")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("attach", om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup.attach", "ti.sdo.ipc.transports"));
        vo.bind("detach", om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup.detach", "ti.sdo.ipc.transports"));
        vo.bind("isRegistered", om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup.isRegistered", "ti.sdo.ipc.transports"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup.sharedMemReq", "ti.sdo.ipc.transports"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_transports_TransportShmNotifySetup_Module__startupDone__E", "ti_sdo_ipc_transports_TransportShmNotifySetup_attach__E", "ti_sdo_ipc_transports_TransportShmNotifySetup_detach__E", "ti_sdo_ipc_transports_TransportShmNotifySetup_isRegistered__E", "ti_sdo_ipc_transports_TransportShmNotifySetup_sharedMemReq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TransportShmNotifySetup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TransportShmNotifySetup");
    }

    void TransportNullSetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportNullSetup", "ti.sdo.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.transports.TransportNullSetup.Module", "ti.sdo.ipc.transports");
        vo.init2(po, "ti.sdo.ipc.transports.TransportNullSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.transports.TransportNullSetup$$capsule", "ti.sdo.ipc.transports"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.transports", "ti.sdo.ipc.transports"));
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
        mcfgs.add("priority");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.transports")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("attach", om.findStrict("ti.sdo.ipc.transports.TransportNullSetup.attach", "ti.sdo.ipc.transports"));
        vo.bind("detach", om.findStrict("ti.sdo.ipc.transports.TransportNullSetup.detach", "ti.sdo.ipc.transports"));
        vo.bind("isRegistered", om.findStrict("ti.sdo.ipc.transports.TransportNullSetup.isRegistered", "ti.sdo.ipc.transports"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.transports.TransportNullSetup.sharedMemReq", "ti.sdo.ipc.transports"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_transports_TransportNullSetup_Module__startupDone__E", "ti_sdo_ipc_transports_TransportNullSetup_attach__E", "ti_sdo_ipc_transports_TransportNullSetup_detach__E", "ti_sdo_ipc_transports_TransportNullSetup_isRegistered__E", "ti_sdo_ipc_transports_TransportNullSetup_sharedMemReq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TransportNullSetup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TransportNullSetup");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sdo.ipc.transports")).findStrict("PARAMS", "ti.sdo.ipc.transports");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.transports.TransportShm", "ti.sdo.ipc.transports")).findStrict("PARAMS", "ti.sdo.ipc.transports");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc", "ti.sdo.ipc.transports")).findStrict("PARAMS", "ti.sdo.ipc.transports");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify", "ti.sdo.ipc.transports")).findStrict("PARAMS", "ti.sdo.ipc.transports");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.transports.TransportShm", "ti.sdo.ipc.transports"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.transports.TransportShmSetup", "ti.sdo.ipc.transports"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc", "ti.sdo.ipc.transports"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.transports.TransportShmCircSetup", "ti.sdo.ipc.transports"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.transports.TransportShmNotify", "ti.sdo.ipc.transports"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.transports.TransportShmNotifySetup", "ti.sdo.ipc.transports"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.transports.TransportNullSetup", "ti.sdo.ipc.transports"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.transports.TransportShmCirc", "ti.sdo.ipc.transports");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Events", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE_DATA"), "viewInitFxn", "viewInitData", "structName", "EventDataView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.transports.TransportShm")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.transports.TransportShmSetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.transports.TransportShmCirc")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.transports.TransportShmCircSetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.transports.TransportShmNotify")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.transports.TransportShmNotifySetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.transports.TransportNullSetup")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.transports")).add(pkgV);
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
        TransportShm$$OBJECTS();
        TransportShmSetup$$OBJECTS();
        TransportShmCirc$$OBJECTS();
        TransportShmCircSetup$$OBJECTS();
        TransportShmNotify$$OBJECTS();
        TransportShmNotifySetup$$OBJECTS();
        TransportNullSetup$$OBJECTS();
        TransportShm$$CONSTS();
        TransportShmSetup$$CONSTS();
        TransportShmCirc$$CONSTS();
        TransportShmCircSetup$$CONSTS();
        TransportShmNotify$$CONSTS();
        TransportShmNotifySetup$$CONSTS();
        TransportNullSetup$$CONSTS();
        TransportShm$$CREATES();
        TransportShmSetup$$CREATES();
        TransportShmCirc$$CREATES();
        TransportShmCircSetup$$CREATES();
        TransportShmNotify$$CREATES();
        TransportShmNotifySetup$$CREATES();
        TransportNullSetup$$CREATES();
        TransportShm$$FUNCTIONS();
        TransportShmSetup$$FUNCTIONS();
        TransportShmCirc$$FUNCTIONS();
        TransportShmCircSetup$$FUNCTIONS();
        TransportShmNotify$$FUNCTIONS();
        TransportShmNotifySetup$$FUNCTIONS();
        TransportNullSetup$$FUNCTIONS();
        TransportShm$$SIZES();
        TransportShmSetup$$SIZES();
        TransportShmCirc$$SIZES();
        TransportShmCircSetup$$SIZES();
        TransportShmNotify$$SIZES();
        TransportShmNotifySetup$$SIZES();
        TransportNullSetup$$SIZES();
        TransportShm$$TYPES();
        TransportShmSetup$$TYPES();
        TransportShmCirc$$TYPES();
        TransportShmCircSetup$$TYPES();
        TransportShmNotify$$TYPES();
        TransportShmNotifySetup$$TYPES();
        TransportNullSetup$$TYPES();
        if (isROV) {
            TransportShm$$ROV();
            TransportShmSetup$$ROV();
            TransportShmCirc$$ROV();
            TransportShmCircSetup$$ROV();
            TransportShmNotify$$ROV();
            TransportShmNotifySetup$$ROV();
            TransportNullSetup$$ROV();
        }//isROV
        $$SINGLETONS();
        TransportShm$$SINGLETONS();
        TransportShmSetup$$SINGLETONS();
        TransportShmCirc$$SINGLETONS();
        TransportShmCircSetup$$SINGLETONS();
        TransportShmNotify$$SINGLETONS();
        TransportShmNotifySetup$$SINGLETONS();
        TransportNullSetup$$SINGLETONS();
        $$INITIALIZATION();
    }
}
