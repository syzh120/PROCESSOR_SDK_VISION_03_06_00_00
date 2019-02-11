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

public class ti_sdo_ipc_notifyDrivers
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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.interfaces");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.utils");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.notifyDrivers", new Value.Obj("ti.sdo.ipc.notifyDrivers", pkgP));
    }

    void NotifyDriverShm$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm", new Value.Obj("ti.sdo.ipc.notifyDrivers.NotifyDriverShm", po));
        pkgV.bind("NotifyDriverShm", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$EventDataView", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventDataView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$EventEntry", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventEntry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$ProcCtrl", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.ProcCtrl", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Object", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance_State", "ti.sdo.ipc.notifyDrivers"));
        }//isROV
    }

    void NotifyDriverCirc$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc", new Value.Obj("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc", po));
        pkgV.bind("NotifyDriverCirc", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$EventDataView", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventDataView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$EventEntry", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventEntry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Object", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance_State", "ti.sdo.ipc.notifyDrivers"));
        }//isROV
    }

    void NotifySetupNull$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifySetupNull.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifySetupNull", new Value.Obj("ti.sdo.ipc.notifyDrivers.NotifySetupNull", po));
        pkgV.bind("NotifySetupNull", vo);
        // decls 
    }

    void IInterrupt$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.notifyDrivers.IInterrupt", new Value.Obj("ti.sdo.ipc.notifyDrivers.IInterrupt", po));
        pkgV.bind("IInterrupt", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.IInterrupt$$IntInfo", new Proto.Obj());
        om.bind("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", new Proto.Str(spo, false));
    }

    void NotifyDriverShm_InterruptProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy", new Value.Obj("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy", po));
        pkgV.bind("NotifyDriverShm_InterruptProxy", vo);
        // decls 
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.notifyDrivers"));
    }

    void NotifyDriverCirc_InterruptProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy", new Value.Obj("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy", po));
        pkgV.bind("NotifyDriverCirc_InterruptProxy", vo);
        // decls 
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.notifyDrivers"));
    }

    void NotifyDriverShm$$CONSTS()
    {
        // module NotifyDriverShm
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.DOWN", 0L);
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.UP", 1L);
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.INIT_STAMP", 0xA9C8B7D6L);
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.sharedMemReq", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params*)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.isr", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_isr__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void NotifyDriverCirc$$CONSTS()
    {
        // module NotifyDriverCirc
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.sharedMemReq", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_Params*)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.isr", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_isr__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void NotifySetupNull$$CONSTS()
    {
        // module NotifySetupNull
        om.bind("ti.sdo.ipc.notifyDrivers.NotifySetupNull.attach", new Extern("ti_sdo_ipc_notifyDrivers_NotifySetupNull_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifySetupNull.sharedMemReq", new Extern("ti_sdo_ipc_notifyDrivers_NotifySetupNull_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifySetupNull.numIntLines", new Extern("ti_sdo_ipc_notifyDrivers_NotifySetupNull_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void IInterrupt$$CONSTS()
    {
        // interface IInterrupt
    }

    void NotifyDriverShm_InterruptProxy$$CONSTS()
    {
        // module NotifyDriverShm_InterruptProxy
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intEnable", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intDisable", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intRegister", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intUnregister", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intSend", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intPost", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intClear", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
    }

    void NotifyDriverCirc_InterruptProxy$$CONSTS()
    {
        // module NotifyDriverCirc_InterruptProxy
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intEnable", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intDisable", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intRegister", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intUnregister", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intSend", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intPost", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intClear", new Extern("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
    }

    void NotifyDriverShm$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$notifyDrivers$NotifyDriverShm$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.notifyDrivers.NotifyDriverShm.create() called before xdc.useModule('ti.sdo.ipc.notifyDrivers.NotifyDriverShm')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Module", "ti.sdo.ipc.notifyDrivers"), om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance", "ti.sdo.ipc.notifyDrivers"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Params", "ti.sdo.ipc.notifyDrivers"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$notifyDrivers$NotifyDriverShm$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.notifyDrivers']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Module", "ti.sdo.ipc.notifyDrivers"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$Object", "ti.sdo.ipc.notifyDrivers"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Params", "ti.sdo.ipc.notifyDrivers"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$notifyDrivers$NotifyDriverShm$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void NotifyDriverCirc$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$notifyDrivers$NotifyDriverCirc$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.create() called before xdc.useModule('ti.sdo.ipc.notifyDrivers.NotifyDriverCirc')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Module", "ti.sdo.ipc.notifyDrivers"), om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance", "ti.sdo.ipc.notifyDrivers"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Params", "ti.sdo.ipc.notifyDrivers"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$notifyDrivers$NotifyDriverCirc$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.notifyDrivers']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Module", "ti.sdo.ipc.notifyDrivers"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$Object", "ti.sdo.ipc.notifyDrivers"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Params", "ti.sdo.ipc.notifyDrivers"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$notifyDrivers$NotifyDriverCirc$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void NotifySetupNull$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IInterrupt$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NotifyDriverShm_InterruptProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NotifyDriverCirc_InterruptProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NotifyDriverShm$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifyDriverCirc$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifySetupNull$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IInterrupt$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifyDriverShm_InterruptProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifyDriverCirc_InterruptProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifyDriverShm$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventEntry", "ti.sdo.ipc.notifyDrivers");
        sizes.clear();
        sizes.add(Global.newArray("flag", "UInt32"));
        sizes.add(Global.newArray("payload", "UInt32"));
        sizes.add(Global.newArray("reserved", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventEntry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventEntry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventEntry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.ProcCtrl", "ti.sdo.ipc.notifyDrivers");
        sizes.clear();
        sizes.add(Global.newArray("recvInitStatus", "UInt32"));
        sizes.add(Global.newArray("sendInitStatus", "UInt32"));
        sizes.add(Global.newArray("eventRegMask", "UInt32"));
        sizes.add(Global.newArray("eventEnableMask", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm.ProcCtrl']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm.ProcCtrl']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm.ProcCtrl'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance_State", "ti.sdo.ipc.notifyDrivers");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("selfProcCtrl", "UPtr"));
        sizes.add(Global.newArray("otherProcCtrl", "UPtr"));
        sizes.add(Global.newArray("selfEventChart", "UPtr"));
        sizes.add(Global.newArray("otherEventChart", "UPtr"));
        sizes.add(Global.newArray("notifyHandle", "UPtr"));
        sizes.add(Global.newArray("regChart", "UPtr"));
        sizes.add(Global.newArray("selfId", "UInt"));
        sizes.add(Global.newArray("otherId", "UInt"));
        sizes.add(Global.newArray("intInfo", "Sti.sdo.ipc.notifyDrivers.IInterrupt;IntInfo"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        sizes.add(Global.newArray("nesting", "UInt"));
        sizes.add(Global.newArray("cacheEnabled", "UShort"));
        sizes.add(Global.newArray("eventEntrySize", "USize"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NotifyDriverCirc$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventEntry", "ti.sdo.ipc.notifyDrivers");
        sizes.clear();
        sizes.add(Global.newArray("eventid", "UInt32"));
        sizes.add(Global.newArray("payload", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventEntry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventEntry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventEntry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance_State", "ti.sdo.ipc.notifyDrivers");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("putBuffer", "UPtr"));
        sizes.add(Global.newArray("putReadIndex", "UPtr"));
        sizes.add(Global.newArray("putWriteIndex", "UPtr"));
        sizes.add(Global.newArray("getBuffer", "UPtr"));
        sizes.add(Global.newArray("getReadIndex", "UPtr"));
        sizes.add(Global.newArray("getWriteIndex", "UPtr"));
        sizes.add(Global.newArray("evtRegMask", "UInt32"));
        sizes.add(Global.newArray("opCacheSize", "USize"));
        sizes.add(Global.newArray("spinCount", "UInt32"));
        sizes.add(Global.newArray("spinWaitTime", "UInt32"));
        sizes.add(Global.newArray("notifyHandle", "UPtr"));
        sizes.add(Global.newArray("intInfo", "Sti.sdo.ipc.notifyDrivers.IInterrupt;IntInfo"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        sizes.add(Global.newArray("cacheEnabled", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NotifySetupNull$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void IInterrupt$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.notifyDrivers");
        sizes.clear();
        sizes.add(Global.newArray("localIntId", "UInt"));
        sizes.add(Global.newArray("remoteIntId", "UInt"));
        sizes.add(Global.newArray("intVectorId", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NotifyDriverShm_InterruptProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void NotifyDriverCirc_InterruptProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void NotifyDriverShm$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/notifyDrivers/NotifyDriverShm.xs");
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Module", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver.Module", "ti.sdo.ipc.notifyDrivers"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("DOWN", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "rh");
                po.addFld("UP", Proto.Elm.newCNum("(xdc_UInt16)"), 1L, "rh");
                po.addFld("INIT_STAMP", Proto.Elm.newCNum("(xdc_UInt32)"), 0xA9C8B7D6L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.notifyDrivers"), $$UNDEF, "wh");
            po.addFldV("InterruptProxy", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.notifyDrivers"), null, "wh", $$delegGet, $$delegSet);
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$create", "ti.sdo.ipc.notifyDrivers"), Global.get("ti$sdo$ipc$notifyDrivers$NotifyDriverShm$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$construct", "ti.sdo.ipc.notifyDrivers"), Global.get("ti$sdo$ipc$notifyDrivers$NotifyDriverShm$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver.Instance", "ti.sdo.ipc.notifyDrivers"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("DOWN", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "rh");
                po.addFld("UP", Proto.Elm.newCNum("(xdc_UInt16)"), 1L, "rh");
                po.addFld("INIT_STAMP", Proto.Elm.newCNum("(xdc_UInt32)"), 0xA9C8B7D6L, "rh");
        if (isCFG) {
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("cacheEnabled", $$T_Bool, true, "w");
            po.addFld("cacheLineSize", Proto.Elm.newCNum("(xdc_SizeT)"), 128L, "w");
            po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
            po.addFld("intVectorId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~1"), "w");
            po.addFld("localIntId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("-1"), "w");
            po.addFld("remoteIntId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("-1"), "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.notifyDrivers"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$Params", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Params", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver$$Params", "ti.sdo.ipc.notifyDrivers"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("DOWN", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "rh");
                po.addFld("UP", Proto.Elm.newCNum("(xdc_UInt16)"), 1L, "rh");
                po.addFld("INIT_STAMP", Proto.Elm.newCNum("(xdc_UInt32)"), 0xA9C8B7D6L, "rh");
        if (isCFG) {
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("cacheEnabled", $$T_Bool, true, "w");
            po.addFld("cacheLineSize", Proto.Elm.newCNum("(xdc_SizeT)"), 128L, "w");
            po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
            po.addFld("intVectorId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~1"), "w");
            po.addFld("localIntId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("-1"), "w");
            po.addFld("remoteIntId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("-1"), "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.notifyDrivers"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$Object", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Object", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance", "ti.sdo.ipc.notifyDrivers"));
        // struct NotifyDriverShm.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$BasicView", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteProcName", $$T_Str, $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
        // struct NotifyDriverShm.EventDataView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$EventDataView", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventDataView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("eventId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("procName", $$T_Str, $$UNDEF, "w");
                po.addFld("enabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("flagged", $$T_Bool, $$UNDEF, "w");
                po.addFld("payload", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct NotifyDriverShm.EventEntry
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$EventEntry", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventEntry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("flag", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("payload", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("reserved", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct NotifyDriverShm.ProcCtrl
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$ProcCtrl", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.ProcCtrl", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("recvInitStatus", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("sendInitStatus", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("eventRegMask", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("eventEnableMask", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct NotifyDriverShm.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$Instance_State", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("selfProcCtrl", new Proto.Adr("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_ProcCtrl*", "PS"), $$UNDEF, "w");
                po.addFld("otherProcCtrl", new Proto.Adr("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_ProcCtrl*", "PS"), $$UNDEF, "w");
                po.addFld("selfEventChart", new Proto.Adr("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_EventEntry*", "PS"), $$UNDEF, "w");
                po.addFld("otherEventChart", new Proto.Adr("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_EventEntry*", "PS"), $$UNDEF, "w");
                po.addFld("notifyHandle", (Proto)om.findStrict("ti.sdo.ipc.Notify.Handle", "ti.sdo.ipc.notifyDrivers"), $$UNDEF, "w");
                po.addFld("regChart", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false), $$DEFAULT, "w");
                po.addFld("selfId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("otherId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("intInfo", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.notifyDrivers"), $$DEFAULT, "w");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("nesting", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("eventEntrySize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
    }

    void NotifyDriverCirc$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/notifyDrivers/NotifyDriverCirc.xs");
        om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Module", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver.Module", "ti.sdo.ipc.notifyDrivers"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.notifyDrivers"), $$UNDEF, "wh");
            po.addFld("A_notSupported", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.notifyDrivers"), Global.newObject("msg", "A_notSupported: [enable/disable]Event not supported by NotifyDriverCirc"), "w");
            po.addFldV("InterruptProxy", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.notifyDrivers"), null, "wh", $$delegGet, $$delegSet);
            po.addFld("enableStats", $$T_Bool, false, "w");
            po.addFld("numMsgs", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "w");
            po.addFld("maxIndex", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
            po.addFld("modIndex", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$create", "ti.sdo.ipc.notifyDrivers"), Global.get("ti$sdo$ipc$notifyDrivers$NotifyDriverCirc$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$construct", "ti.sdo.ipc.notifyDrivers"), Global.get("ti$sdo$ipc$notifyDrivers$NotifyDriverCirc$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver.Instance", "ti.sdo.ipc.notifyDrivers"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("cacheEnabled", $$T_Bool, true, "w");
            po.addFld("cacheLineSize", Proto.Elm.newCNum("(xdc_SizeT)"), 128L, "w");
            po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
            po.addFld("intVectorId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~1"), "w");
            po.addFld("localIntId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("-1"), "w");
            po.addFld("remoteIntId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("-1"), "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.notifyDrivers"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$Params", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Params", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver$$Params", "ti.sdo.ipc.notifyDrivers"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("cacheEnabled", $$T_Bool, true, "w");
            po.addFld("cacheLineSize", Proto.Elm.newCNum("(xdc_SizeT)"), 128L, "w");
            po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
            po.addFld("intVectorId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~1"), "w");
            po.addFld("localIntId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("-1"), "w");
            po.addFld("remoteIntId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("-1"), "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.notifyDrivers"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$Object", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Object", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance", "ti.sdo.ipc.notifyDrivers"));
        // struct NotifyDriverCirc.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$BasicView", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteProcName", $$T_Str, $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("bufSize", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("spinCount", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("maxSpinWait", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        // struct NotifyDriverCirc.EventDataView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$EventDataView", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventDataView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("index", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("buffer", $$T_Str, $$UNDEF, "w");
                po.addFld("addr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("eventId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("payload", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct NotifyDriverCirc.EventEntry
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$EventEntry", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventEntry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("eventid", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("payload", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct NotifyDriverCirc.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$Instance_State", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("putBuffer", new Proto.Adr("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_EventEntry*", "PS"), $$UNDEF, "w");
                po.addFld("putReadIndex", new Proto.Adr("xdc_Bits32*", "Pn"), $$UNDEF, "w");
                po.addFld("putWriteIndex", new Proto.Adr("xdc_Bits32*", "Pn"), $$UNDEF, "w");
                po.addFld("getBuffer", new Proto.Adr("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_EventEntry*", "PS"), $$UNDEF, "w");
                po.addFld("getReadIndex", new Proto.Adr("xdc_Bits32*", "Pn"), $$UNDEF, "w");
                po.addFld("getWriteIndex", new Proto.Adr("xdc_Bits32*", "Pn"), $$UNDEF, "w");
                po.addFld("evtRegMask", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("opCacheSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("spinCount", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("spinWaitTime", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("notifyHandle", (Proto)om.findStrict("ti.sdo.ipc.Notify.Handle", "ti.sdo.ipc.notifyDrivers"), $$UNDEF, "w");
                po.addFld("intInfo", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.notifyDrivers"), $$DEFAULT, "w");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
    }

    void NotifySetupNull$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/notifyDrivers/NotifySetupNull.xs");
        om.bind("ti.sdo.ipc.notifyDrivers.NotifySetupNull$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifySetupNull.Module", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifySetupNull.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.notifyDrivers"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifySetupNull$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifySetupNull$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifySetupNull$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.notifyDrivers.NotifySetupNull$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void IInterrupt$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.ipc.notifyDrivers"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        // struct IInterrupt.IntInfo
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt$$IntInfo", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("localIntId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("remoteIntId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("intVectorId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void NotifyDriverShm_InterruptProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.Module", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.notifyDrivers"));
                po.addFld("delegate$", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.notifyDrivers"), null, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void NotifyDriverCirc_InterruptProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.Module", "ti.sdo.ipc.notifyDrivers");
        po.init("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.notifyDrivers"));
                po.addFld("delegate$", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.notifyDrivers"), null, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void NotifyDriverShm$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm", "ti.sdo.ipc.notifyDrivers");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$Instance_State", "ti.sdo.ipc.notifyDrivers");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("EventEntry$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventEntry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$EventEntry", "ti.sdo.ipc.notifyDrivers");
        vo.bind("ProcCtrl$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.NotifyDriverShm.ProcCtrl", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$ProcCtrl", "ti.sdo.ipc.notifyDrivers");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$Instance_State", "ti.sdo.ipc.notifyDrivers");
        po.bind("selfProcCtrl$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.NotifyDriverShm.ProcCtrl", "isScalar", false));
        po.bind("otherProcCtrl$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.NotifyDriverShm.ProcCtrl", "isScalar", false));
        po.bind("selfEventChart$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventEntry", "isScalar", false));
        po.bind("otherEventChart$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventEntry", "isScalar", false));
        po.bind("regChart$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_UInt32", "isScalar", true));
    }

    void NotifyDriverCirc$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc", "ti.sdo.ipc.notifyDrivers");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$Instance_State", "ti.sdo.ipc.notifyDrivers");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("EventEntry$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventEntry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$EventEntry", "ti.sdo.ipc.notifyDrivers");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$Instance_State", "ti.sdo.ipc.notifyDrivers");
        po.bind("putBuffer$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventEntry", "isScalar", false));
        po.bind("getBuffer$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventEntry", "isScalar", false));
    }

    void NotifySetupNull$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifySetupNull", "ti.sdo.ipc.notifyDrivers");
    }

    void IInterrupt$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt", "ti.sdo.ipc.notifyDrivers");
        vo.bind("IntInfo$fetchDesc", Global.newObject("type", "ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt$$IntInfo", "ti.sdo.ipc.notifyDrivers");
    }

    void NotifyDriverShm_InterruptProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy", "ti.sdo.ipc.notifyDrivers");
    }

    void NotifyDriverCirc_InterruptProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy", "ti.sdo.ipc.notifyDrivers");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.notifyDrivers.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.notifyDrivers"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/notifyDrivers/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.notifyDrivers"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.notifyDrivers"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.notifyDrivers"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.notifyDrivers"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.notifyDrivers"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.notifyDrivers"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.notifyDrivers", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.notifyDrivers");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.notifyDrivers.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ipc", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ipc.interfaces", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.utils", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.notifyDrivers'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.notifyDrivers$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.notifyDrivers$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.notifyDrivers$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void NotifyDriverShm$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm", "ti.sdo.ipc.notifyDrivers");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Module", "ti.sdo.ipc.notifyDrivers");
        vo.init2(po, "ti.sdo.ipc.notifyDrivers.NotifyDriverShm", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$capsule", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Params", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Params", "ti.sdo.ipc.notifyDrivers")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Handle", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.notifyDrivers", "ti.sdo.ipc.notifyDrivers"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.BasicView", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.BasicView", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("EventDataView", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventDataView", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventDataView", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("InterruptProxy$proxy", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy", "ti.sdo.ipc.notifyDrivers"));
        proxies.add("InterruptProxy");
        vo.bind("EventEntry", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventEntry", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.EventEntry", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("ProcCtrl", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.ProcCtrl", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.ProcCtrl", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance_State", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Instance_State", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.notifyDrivers")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.notifyDrivers.NotifyDriverShm$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$notifyDrivers$NotifyDriverShm$$__initObject"));
        }//isCFG
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.sharedMemReq", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("isr", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.isr", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Handle__label__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Module__startupDone__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__create__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__delete__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__destruct__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__get__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__first__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Object__next__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_Params__init__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_registerEvent__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_unregisterEvent__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sendEvent__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disable__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enable__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_disableEvent__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_enableEvent__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_setNotifyHandle__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_sharedMemReq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm.Object", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "sharedMemReq", "entry", "%p", "exit", "0x%x"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NotifyDriverShm", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifyDriverShm");
    }

    void NotifyDriverCirc$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc", "ti.sdo.ipc.notifyDrivers");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Module", "ti.sdo.ipc.notifyDrivers");
        vo.init2(po, "ti.sdo.ipc.notifyDrivers.NotifyDriverCirc", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$capsule", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Params", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Params", "ti.sdo.ipc.notifyDrivers")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Handle", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.notifyDrivers", "ti.sdo.ipc.notifyDrivers"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.BasicView", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.BasicView", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("EventDataView", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventDataView", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventDataView", "ti.sdo.ipc.notifyDrivers"));
        mcfgs.add("A_notSupported");
        vo.bind("InterruptProxy$proxy", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy", "ti.sdo.ipc.notifyDrivers"));
        proxies.add("InterruptProxy");
        mcfgs.add("enableStats");
        mcfgs.add("numMsgs");
        mcfgs.add("maxIndex");
        icfgs.add("maxIndex");
        mcfgs.add("modIndex");
        icfgs.add("modIndex");
        vo.bind("EventEntry", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventEntry", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.EventEntry", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance_State", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Instance_State", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.notifyDrivers")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$notifyDrivers$NotifyDriverCirc$$__initObject"));
        }//isCFG
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.sharedMemReq", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("isr", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.isr", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_Handle__label__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_Module__startupDone__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_Object__create__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_Object__delete__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_Object__destruct__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_Object__get__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_Object__first__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_Object__next__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_Params__init__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_registerEvent__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_unregisterEvent__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_sendEvent__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_disable__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_enable__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_disableEvent__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_enableEvent__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_setNotifyHandle__E", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_sharedMemReq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_notSupported"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc.Object", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "sharedMemReq", "entry", "%p", "exit", "0x%x"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NotifyDriverCirc", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifyDriverCirc");
    }

    void NotifySetupNull$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifySetupNull", "ti.sdo.ipc.notifyDrivers");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifySetupNull.Module", "ti.sdo.ipc.notifyDrivers");
        vo.init2(po, "ti.sdo.ipc.notifyDrivers.NotifySetupNull", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifySetupNull$$capsule", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.notifyDrivers", "ti.sdo.ipc.notifyDrivers"));
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
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.notifyDrivers")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifySetupNull.attach", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifySetupNull.sharedMemReq", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifySetupNull.numIntLines", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_notifyDrivers_NotifySetupNull_Module__startupDone__E", "ti_sdo_ipc_notifyDrivers_NotifySetupNull_attach__E", "ti_sdo_ipc_notifyDrivers_NotifySetupNull_sharedMemReq__E", "ti_sdo_ipc_notifyDrivers_NotifySetupNull_numIntLines__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NotifySetupNull", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifySetupNull");
    }

    void IInterrupt$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt", "ti.sdo.ipc.notifyDrivers");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.notifyDrivers");
        vo.init2(po, "ti.sdo.ipc.notifyDrivers.IInterrupt", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ipc.notifyDrivers", "ti.sdo.ipc.notifyDrivers"));
        tdefs.clear();
        proxies.clear();
        inherits.clear();
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IInterrupt", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IInterrupt");
        vo.seal(null);
        if (vo.getProto().lookupFld("$used") != null) {
            vo.unseal("$used");
        }
    }

    void NotifyDriverShm_InterruptProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy", "ti.sdo.ipc.notifyDrivers");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.Module", "ti.sdo.ipc.notifyDrivers");
        vo.init2(po, "ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ipc.notifyDrivers", "ti.sdo.ipc.notifyDrivers"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        inherits.clear();
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.notifyDrivers")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intEnable", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intDisable", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intRegister", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intUnregister", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intSend", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intPost", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy.intClear", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__Handle__label", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__Module__startupDone", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__Object__create", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__Object__delete", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__Object__destruct", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__Object__get", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__Object__first", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__Object__next", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__Params__init", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__Proxy__abstract", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__Proxy__delegate", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__intEnable", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__intDisable", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__intRegister", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__intUnregister", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__intSend", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__intPost", "ti_sdo_ipc_notifyDrivers_NotifyDriverShm_InterruptProxy_DELEGATE__intClear"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NotifyDriverShm_InterruptProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifyDriverShm_InterruptProxy");
    }

    void NotifyDriverCirc_InterruptProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy", "ti.sdo.ipc.notifyDrivers");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.Module", "ti.sdo.ipc.notifyDrivers");
        vo.init2(po, "ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ipc.notifyDrivers", "ti.sdo.ipc.notifyDrivers"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        inherits.clear();
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.notifyDrivers"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.notifyDrivers")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intEnable", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intDisable", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intRegister", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intUnregister", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intSend", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intPost", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy.intClear", "ti.sdo.ipc.notifyDrivers"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__Handle__label", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__Module__startupDone", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__Object__create", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__Object__delete", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__Object__destruct", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__Object__get", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__Object__first", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__Object__next", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__Params__init", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__Proxy__abstract", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__Proxy__delegate", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__intEnable", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__intDisable", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__intRegister", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__intUnregister", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__intSend", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__intPost", "ti_sdo_ipc_notifyDrivers_NotifyDriverCirc_InterruptProxy_DELEGATE__intClear"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NotifyDriverCirc_InterruptProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifyDriverCirc_InterruptProxy");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sdo.ipc.notifyDrivers")).findStrict("PARAMS", "ti.sdo.ipc.notifyDrivers");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm", "ti.sdo.ipc.notifyDrivers")).findStrict("PARAMS", "ti.sdo.ipc.notifyDrivers");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc", "ti.sdo.ipc.notifyDrivers")).findStrict("PARAMS", "ti.sdo.ipc.notifyDrivers");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm", "ti.sdo.ipc.notifyDrivers"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc", "ti.sdo.ipc.notifyDrivers"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifySetupNull", "ti.sdo.ipc.notifyDrivers"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy", "ti.sdo.ipc.notifyDrivers"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy", "ti.sdo.ipc.notifyDrivers"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverShm", "ti.sdo.ipc.notifyDrivers");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Events", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE_DATA"), "viewInitFxn", "viewInitData", "structName", "EventDataView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc", "ti.sdo.ipc.notifyDrivers");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Events", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE_DATA"), "viewInitFxn", "viewInitData", "structName", "EventDataView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.notifyDrivers.NotifyDriverShm")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.notifyDrivers.NotifySetupNull")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.notifyDrivers.IInterrupt")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.notifyDrivers.NotifyDriverShm_InterruptProxy")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.notifyDrivers.NotifyDriverCirc_InterruptProxy")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.notifyDrivers")).add(pkgV);
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
        NotifyDriverShm$$OBJECTS();
        NotifyDriverCirc$$OBJECTS();
        NotifySetupNull$$OBJECTS();
        IInterrupt$$OBJECTS();
        NotifyDriverShm_InterruptProxy$$OBJECTS();
        NotifyDriverCirc_InterruptProxy$$OBJECTS();
        NotifyDriverShm$$CONSTS();
        NotifyDriverCirc$$CONSTS();
        NotifySetupNull$$CONSTS();
        IInterrupt$$CONSTS();
        NotifyDriverShm_InterruptProxy$$CONSTS();
        NotifyDriverCirc_InterruptProxy$$CONSTS();
        NotifyDriverShm$$CREATES();
        NotifyDriverCirc$$CREATES();
        NotifySetupNull$$CREATES();
        IInterrupt$$CREATES();
        NotifyDriverShm_InterruptProxy$$CREATES();
        NotifyDriverCirc_InterruptProxy$$CREATES();
        NotifyDriverShm$$FUNCTIONS();
        NotifyDriverCirc$$FUNCTIONS();
        NotifySetupNull$$FUNCTIONS();
        IInterrupt$$FUNCTIONS();
        NotifyDriverShm_InterruptProxy$$FUNCTIONS();
        NotifyDriverCirc_InterruptProxy$$FUNCTIONS();
        NotifyDriverShm$$SIZES();
        NotifyDriverCirc$$SIZES();
        NotifySetupNull$$SIZES();
        IInterrupt$$SIZES();
        NotifyDriverShm_InterruptProxy$$SIZES();
        NotifyDriverCirc_InterruptProxy$$SIZES();
        NotifyDriverShm$$TYPES();
        NotifyDriverCirc$$TYPES();
        NotifySetupNull$$TYPES();
        IInterrupt$$TYPES();
        NotifyDriverShm_InterruptProxy$$TYPES();
        NotifyDriverCirc_InterruptProxy$$TYPES();
        if (isROV) {
            NotifyDriverShm$$ROV();
            NotifyDriverCirc$$ROV();
            NotifySetupNull$$ROV();
            IInterrupt$$ROV();
            NotifyDriverShm_InterruptProxy$$ROV();
            NotifyDriverCirc_InterruptProxy$$ROV();
        }//isROV
        $$SINGLETONS();
        NotifyDriverShm$$SINGLETONS();
        NotifyDriverCirc$$SINGLETONS();
        NotifySetupNull$$SINGLETONS();
        IInterrupt$$SINGLETONS();
        NotifyDriverShm_InterruptProxy$$SINGLETONS();
        NotifyDriverCirc_InterruptProxy$$SINGLETONS();
        $$INITIALIZATION();
    }
}
