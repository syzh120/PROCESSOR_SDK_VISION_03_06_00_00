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

public class ti_sdo_ipc_nsremote
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
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.knl");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.utils");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.syncs");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.gates");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.nsremote", new Value.Obj("ti.sdo.ipc.nsremote", pkgP));
    }

    void NameServerRemoteNotify$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify", new Value.Obj("ti.sdo.ipc.nsremote.NameServerRemoteNotify", po));
        pkgV.bind("NameServerRemoteNotify", vo);
        // decls 
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Status", om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.ipc.nsremote"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Message", new Proto.Obj());
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Message", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Object", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance_State", "ti.sdo.ipc.nsremote"));
        }//isROV
    }

    void NameServerMessageQ$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ", new Value.Obj("ti.sdo.ipc.nsremote.NameServerMessageQ", po));
        pkgV.bind("NameServerMessageQ", vo);
        // decls 
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.Status", om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.ipc.nsremote"));
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.Type", new Proto.Enm("ti.sdo.ipc.nsremote.NameServerMessageQ.Type"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.Object", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance_State", "ti.sdo.ipc.nsremote"));
        }//isROV
    }

    void NameServerRemoteNotify$$CONSTS()
    {
        // module NameServerRemoteNotify
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.IDLE", 0L);
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.SEND_REQUEST", 1L);
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.RECEIVE_RESPONSE", 2L);
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.RECEIVE_REQUEST", 1L);
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.SEND_RESPONSE", 2L);
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.attach", new Extern("ti_sdo_ipc_nsremote_NameServerRemoteNotify_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.detach", new Extern("ti_sdo_ipc_nsremote_NameServerRemoteNotify_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.sharedMemReq", new Extern("ti_sdo_ipc_nsremote_NameServerRemoteNotify_sharedMemReq__E", "xdc_SizeT(*)(xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.cbFxn", new Extern("ti_sdo_ipc_nsremote_NameServerRemoteNotify_cbFxn__I", "xdc_Void(*)(xdc_UInt16,xdc_UInt16,xdc_UInt32,xdc_UArg,xdc_UInt32)", true, false));
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.swiFxnRequest", new Extern("ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnRequest__I", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify.swiFxnResponse", new Extern("ti_sdo_ipc_nsremote_NameServerRemoteNotify_swiFxnResponse__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void NameServerMessageQ$$CONSTS()
    {
        // module NameServerMessageQ
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.maxNameLen", 32L);
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.REQUEST", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Type", "ti.sdo.ipc.nsremote"), "ti.sdo.ipc.nsremote.NameServerMessageQ.REQUEST", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.RESPONSE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Type", "ti.sdo.ipc.nsremote"), "ti.sdo.ipc.nsremote.NameServerMessageQ.RESPONSE", xdc.services.intern.xsr.Enum.intValue(1L)+0));
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.attach", new Extern("ti_sdo_ipc_nsremote_NameServerMessageQ_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.detach", new Extern("ti_sdo_ipc_nsremote_NameServerMessageQ_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.sharedMemReq", new Extern("ti_sdo_ipc_nsremote_NameServerMessageQ_sharedMemReq__E", "xdc_SizeT(*)(xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ.swiFxn", new Extern("ti_sdo_ipc_nsremote_NameServerMessageQ_swiFxn__I", "xdc_Void(*)(xdc_UArg,xdc_UArg)", true, false));
    }

    void NameServerRemoteNotify$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$nsremote$NameServerRemoteNotify$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.nsremote.NameServerRemoteNotify.create() called before xdc.useModule('ti.sdo.ipc.nsremote.NameServerRemoteNotify')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.procId, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Module", "ti.sdo.ipc.nsremote"), om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance", "ti.sdo.ipc.nsremote"), 2, 1, false));
                        fxn.addArg(0, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Params", "ti.sdo.ipc.nsremote"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$nsremote$NameServerRemoteNotify$$create = function( procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.nsremote']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [procId]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Module", "ti.sdo.ipc.nsremote"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Object", "ti.sdo.ipc.nsremote"), null);
                        fxn.addArg(1, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Params", "ti.sdo.ipc.nsremote"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$nsremote$NameServerRemoteNotify$$construct = function( __obj, procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void NameServerMessageQ$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$nsremote$NameServerMessageQ$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.nsremote.NameServerMessageQ.create() called before xdc.useModule('ti.sdo.ipc.nsremote.NameServerMessageQ')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.procId, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Module", "ti.sdo.ipc.nsremote"), om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance", "ti.sdo.ipc.nsremote"), 2, 1, false));
                        fxn.addArg(0, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Params", "ti.sdo.ipc.nsremote"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$nsremote$NameServerMessageQ$$create = function( procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.nsremote']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [procId]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Module", "ti.sdo.ipc.nsremote"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ$$Object", "ti.sdo.ipc.nsremote"), null);
                        fxn.addArg(1, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Params", "ti.sdo.ipc.nsremote"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$nsremote$NameServerMessageQ$$construct = function( __obj, procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void NameServerRemoteNotify$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NameServerMessageQ$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NameServerRemoteNotify$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Message", "ti.sdo.ipc.nsremote");
        sizes.clear();
        sizes.add(Global.newArray("requestStatus", "UInt32"));
        sizes.add(Global.newArray("value", "UInt32"));
        sizes.add(Global.newArray("valueLen", "UInt32"));
        sizes.add(Global.newArray("instanceName", "A8;UInt32"));
        sizes.add(Global.newArray("name", "A8;UInt32"));
        sizes.add(Global.newArray("valueBuf", "A77;UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify.Message']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify.Message']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify.Message'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance_State", "ti.sdo.ipc.nsremote");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("msg", "A2;UPtr"));
        sizes.add(Global.newArray("regionId", "UInt16"));
        sizes.add(Global.newArray("localState", "UInt8"));
        sizes.add(Global.newArray("remoteState", "UInt8"));
        sizes.add(Global.newArray("gate", "UPtr"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        sizes.add(Global.newArray("cacheEnable", "UShort"));
        sizes.add(Global.newArray("semRemoteWait", "Sti.sysbios.knl.Semaphore;Instance_State"));
        sizes.add(Global.newArray("semMultiBlock", "Sti.sysbios.knl.Semaphore;Instance_State"));
        sizes.add(Global.newArray("swiRequest", "Sti.sysbios.knl.Swi;Instance_State"));
        sizes.add(Global.newArray("swiResponse", "Sti.sysbios.knl.Swi;Instance_State"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NameServerMessageQ$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance_State", "ti.sdo.ipc.nsremote");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Module_State", "ti.sdo.ipc.nsremote");
        sizes.clear();
        sizes.add(Global.newArray("msgHandle", "UPtr"));
        sizes.add(Global.newArray("swiHandle", "UPtr"));
        sizes.add(Global.newArray("syncSwiHandle", "UPtr"));
        sizes.add(Global.newArray("semRemoteWait", "UPtr"));
        sizes.add(Global.newArray("gateMutex", "UPtr"));
        sizes.add(Global.newArray("msg", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.nsremote.NameServerMessageQ.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NameServerRemoteNotify$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/nsremote/NameServerRemoteNotify.xs");
        om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Module", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Module", om.findStrict("ti.sdo.utils.INameServerRemote.Module", "ti.sdo.ipc.nsremote"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("IDLE", Proto.Elm.newCNum("(xdc_UInt8)"), 0L, "rh");
                po.addFld("SEND_REQUEST", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("RECEIVE_RESPONSE", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
                po.addFld("RECEIVE_REQUEST", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("SEND_RESPONSE", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.nsremote"), $$UNDEF, "wh");
            po.addFld("A_invalidValueLen", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.nsremote"), Global.newObject("msg", "A_invalidValueLen: Invalid valueLen (too large)"), "w");
            po.addFld("A_messageSize", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.nsremote"), Global.newObject("msg", "A_messageSize: message size not aligned with cache line size."), "w");
            po.addFld("notifyEventId", Proto.Elm.newCNum("(xdc_UInt)"), 4L, "w");
            po.addFld("timeoutInMicroSecs", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~(0)"), "w");
            po.addFld("timeout", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$create", "ti.sdo.ipc.nsremote"), Global.get("ti$sdo$ipc$nsremote$NameServerRemoteNotify$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$construct", "ti.sdo.ipc.nsremote"), Global.get("ti$sdo$ipc$nsremote$NameServerRemoteNotify$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance", om.findStrict("ti.sdo.utils.INameServerRemote.Instance", "ti.sdo.ipc.nsremote"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("IDLE", Proto.Elm.newCNum("(xdc_UInt8)"), 0L, "rh");
                po.addFld("SEND_REQUEST", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("RECEIVE_RESPONSE", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
                po.addFld("RECEIVE_REQUEST", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("SEND_RESPONSE", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
        if (isCFG) {
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.nsremote"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.nsremote"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Params", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Params", om.findStrict("ti.sdo.utils.INameServerRemote$$Params", "ti.sdo.ipc.nsremote"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("IDLE", Proto.Elm.newCNum("(xdc_UInt8)"), 0L, "rh");
                po.addFld("SEND_REQUEST", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("RECEIVE_RESPONSE", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
                po.addFld("RECEIVE_REQUEST", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("SEND_RESPONSE", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
        if (isCFG) {
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.nsremote"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.nsremote"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Object", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Object", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance", "ti.sdo.ipc.nsremote"));
        // struct NameServerRemoteNotify.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$BasicView", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerRemoteNotify.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("remoteProcName", $$T_Str, $$UNDEF, "w");
                po.addFld("localRequestStatus", $$T_Str, $$UNDEF, "w");
                po.addFld("localInstanceName", $$T_Str, $$UNDEF, "w");
                po.addFld("localName", $$T_Str, $$UNDEF, "w");
                po.addFld("localValue", $$T_Str, $$UNDEF, "w");
                po.addFld("remoteRequestStatus", $$T_Str, $$UNDEF, "w");
                po.addFld("remoteInstanceName", $$T_Str, $$UNDEF, "w");
                po.addFld("remoteName", $$T_Str, $$UNDEF, "w");
                po.addFld("remoteValue", $$T_Str, $$UNDEF, "w");
        // struct NameServerRemoteNotify.Message
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Message", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Message", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("requestStatus", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("value", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("valueLen", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("instanceName", new Proto.Arr(Proto.Elm.newCNum("(xdc_Bits32)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("name", new Proto.Arr(Proto.Elm.newCNum("(xdc_Bits32)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("valueBuf", new Proto.Arr(Proto.Elm.newCNum("(xdc_Bits32)"), false, xdc.services.intern.xsr.Enum.intValue(77L)), $$DEFAULT, "w");
        // struct NameServerRemoteNotify.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Instance_State", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("msg", new Proto.Arr(new Proto.Adr("ti_sdo_ipc_nsremote_NameServerRemoteNotify_Message*", "PS"), false, xdc.services.intern.xsr.Enum.intValue(2L)), $$DEFAULT, "w");
                po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("localState", Proto.Elm.newCNum("(xdc_UInt8)"), $$UNDEF, "w");
                po.addFld("remoteState", Proto.Elm.newCNum("(xdc_UInt8)"), $$UNDEF, "w");
                po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.nsremote"), $$UNDEF, "w");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("cacheEnable", $$T_Bool, $$UNDEF, "w");
                po.addFldV("semRemoteWait", (Proto)om.findStrict("ti.sysbios.knl.Semaphore.Object", "ti.sdo.ipc.nsremote"), $$DEFAULT, "wh", $$objFldGet, $$objFldSet);
                po.addFld("Object_field_semRemoteWait", (Proto)om.findStrict("ti.sysbios.knl.Semaphore.Object", "ti.sdo.ipc.nsremote"), $$DEFAULT, "w");
                po.addFldV("semMultiBlock", (Proto)om.findStrict("ti.sysbios.knl.Semaphore.Object", "ti.sdo.ipc.nsremote"), $$DEFAULT, "wh", $$objFldGet, $$objFldSet);
                po.addFld("Object_field_semMultiBlock", (Proto)om.findStrict("ti.sysbios.knl.Semaphore.Object", "ti.sdo.ipc.nsremote"), $$DEFAULT, "w");
                po.addFldV("swiRequest", (Proto)om.findStrict("ti.sysbios.knl.Swi.Object", "ti.sdo.ipc.nsremote"), $$DEFAULT, "wh", $$objFldGet, $$objFldSet);
                po.addFld("Object_field_swiRequest", (Proto)om.findStrict("ti.sysbios.knl.Swi.Object", "ti.sdo.ipc.nsremote"), $$DEFAULT, "w");
                po.addFldV("swiResponse", (Proto)om.findStrict("ti.sysbios.knl.Swi.Object", "ti.sdo.ipc.nsremote"), $$DEFAULT, "wh", $$objFldGet, $$objFldSet);
                po.addFld("Object_field_swiResponse", (Proto)om.findStrict("ti.sysbios.knl.Swi.Object", "ti.sdo.ipc.nsremote"), $$DEFAULT, "w");
    }

    void NameServerMessageQ$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/nsremote/NameServerMessageQ.xs");
        om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Module", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerMessageQ.Module", om.findStrict("ti.sdo.utils.INameServerRemote.Module", "ti.sdo.ipc.nsremote"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "rh");
        if (isCFG) {
            po.addFld("A_reservedMsgQueueId", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.nsremote"), Global.newObject("msg", "MessageQ Id 0 is reserved for NameServer"), "w");
            po.addFld("A_nameIsTooLong", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.nsremote"), Global.newObject("msg", "Too many characters in name"), "w");
            po.addFld("E_outOfMemory", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.nsremote"), Global.newObject("msg", "E_outOfMemory: MessageQ_alloc faild from heap: %d"), "w");
            po.addFld("heapId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("timeoutInMicroSecs", Proto.Elm.newCNum("(xdc_UInt)"), 1000000L, "w");
            po.addFld("timeout", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ$$create", "ti.sdo.ipc.nsremote"), Global.get("ti$sdo$ipc$nsremote$NameServerMessageQ$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ$$construct", "ti.sdo.ipc.nsremote"), Global.get("ti$sdo$ipc$nsremote$NameServerMessageQ$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.nsremote.NameServerMessageQ$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance", om.findStrict("ti.sdo.utils.INameServerRemote.Instance", "ti.sdo.ipc.nsremote"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.nsremote"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ$$Params", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerMessageQ.Params", om.findStrict("ti.sdo.utils.INameServerRemote$$Params", "ti.sdo.ipc.nsremote"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.nsremote"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ$$Object", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerMessageQ.Object", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance", "ti.sdo.ipc.nsremote"));
        // struct NameServerMessageQ.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ$$Instance_State", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
        // struct NameServerMessageQ.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ$$Module_State", "ti.sdo.ipc.nsremote");
        po.init("ti.sdo.ipc.nsremote.NameServerMessageQ.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("msgHandle", (Proto)om.findStrict("ti.sdo.ipc.MessageQ.Handle", "ti.sdo.ipc.nsremote"), $$UNDEF, "w");
                po.addFld("swiHandle", (Proto)om.findStrict("ti.sysbios.knl.Swi.Handle", "ti.sdo.ipc.nsremote"), $$UNDEF, "w");
                po.addFld("syncSwiHandle", (Proto)om.findStrict("ti.sysbios.syncs.SyncSwi.Handle", "ti.sdo.ipc.nsremote"), $$UNDEF, "w");
                po.addFld("semRemoteWait", (Proto)om.findStrict("ti.sysbios.knl.Semaphore.Handle", "ti.sdo.ipc.nsremote"), $$UNDEF, "w");
                po.addFld("gateMutex", (Proto)om.findStrict("ti.sysbios.gates.GateMutex.Handle", "ti.sdo.ipc.nsremote"), $$UNDEF, "w");
                po.addFld("msg", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void NameServerRemoteNotify$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify", "ti.sdo.ipc.nsremote");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Instance_State", "ti.sdo.ipc.nsremote");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Message$fetchDesc", Global.newObject("type", "ti.sdo.ipc.nsremote.NameServerRemoteNotify.Message", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Message", "ti.sdo.ipc.nsremote");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$Instance_State", "ti.sdo.ipc.nsremote");
    }

    void NameServerMessageQ$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ", "ti.sdo.ipc.nsremote");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ$$Instance_State", "ti.sdo.ipc.nsremote");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.nsremote.NameServerMessageQ.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ$$Instance_State", "ti.sdo.ipc.nsremote");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.nsremote.NameServerMessageQ.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ$$Module_State", "ti.sdo.ipc.nsremote");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.nsremote.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.nsremote"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/nsremote/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.nsremote"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.nsremote"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.nsremote"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.nsremote"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.nsremote"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.nsremote"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.nsremote", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.nsremote");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.nsremote.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.nsremote'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.nsremote$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.nsremote$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.nsremote$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void NameServerRemoteNotify$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify", "ti.sdo.ipc.nsremote");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Module", "ti.sdo.ipc.nsremote");
        vo.init2(po, "ti.sdo.ipc.nsremote.NameServerRemoteNotify", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$capsule", "ti.sdo.ipc.nsremote"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance", "ti.sdo.ipc.nsremote"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Params", "ti.sdo.ipc.nsremote"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Params", "ti.sdo.ipc.nsremote")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Handle", "ti.sdo.ipc.nsremote"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.nsremote", "ti.sdo.ipc.nsremote"));
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
        vo.bind("Status", om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.ipc.nsremote"));
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.BasicView", "ti.sdo.ipc.nsremote"));
        tdefs.add(om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.BasicView", "ti.sdo.ipc.nsremote"));
        vo.bind("Message", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Message", "ti.sdo.ipc.nsremote"));
        tdefs.add(om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Message", "ti.sdo.ipc.nsremote"));
        mcfgs.add("A_invalidValueLen");
        mcfgs.add("A_messageSize");
        mcfgs.add("notifyEventId");
        mcfgs.add("timeoutInMicroSecs");
        mcfgs.add("timeout");
        icfgs.add("timeout");
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance_State", "ti.sdo.ipc.nsremote"));
        tdefs.add(om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Instance_State", "ti.sdo.ipc.nsremote"));
        vo.bind("S_SUCCESS", om.findStrict("ti.sdo.utils.INameServerRemote.S_SUCCESS", "ti.sdo.ipc.nsremote"));
        vo.bind("E_FAIL", om.findStrict("ti.sdo.utils.INameServerRemote.E_FAIL", "ti.sdo.ipc.nsremote"));
        vo.bind("E_ERROR", om.findStrict("ti.sdo.utils.INameServerRemote.E_ERROR", "ti.sdo.ipc.nsremote"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.utils");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.nsremote")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.nsremote.NameServerRemoteNotify$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$nsremote$NameServerRemoteNotify$$__initObject"));
        }//isCFG
        vo.bind("attach", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.attach", "ti.sdo.ipc.nsremote"));
        vo.bind("detach", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.detach", "ti.sdo.ipc.nsremote"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.sharedMemReq", "ti.sdo.ipc.nsremote"));
        vo.bind("cbFxn", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.cbFxn", "ti.sdo.ipc.nsremote"));
        vo.bind("swiFxnRequest", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.swiFxnRequest", "ti.sdo.ipc.nsremote"));
        vo.bind("swiFxnResponse", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.swiFxnResponse", "ti.sdo.ipc.nsremote"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_nsremote_NameServerRemoteNotify_Handle__label__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Module__startupDone__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__create__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__delete__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__destruct__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__get__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__first__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Object__next__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_Params__init__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_attach__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_detach__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_sharedMemReq__E", "ti_sdo_ipc_nsremote_NameServerRemoteNotify_get__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_invalidValueLen", "A_messageSize"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify.Object", "ti.sdo.ipc.nsremote"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "get", "entry", "%p, \"%s\", \"%s\", %p, %p, %p, %p", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NameServerRemoteNotify", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NameServerRemoteNotify");
    }

    void NameServerMessageQ$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ", "ti.sdo.ipc.nsremote");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Module", "ti.sdo.ipc.nsremote");
        vo.init2(po, "ti.sdo.ipc.nsremote.NameServerMessageQ", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ$$capsule", "ti.sdo.ipc.nsremote"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance", "ti.sdo.ipc.nsremote"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Params", "ti.sdo.ipc.nsremote"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Params", "ti.sdo.ipc.nsremote")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Handle", "ti.sdo.ipc.nsremote"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.nsremote", "ti.sdo.ipc.nsremote"));
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
        vo.bind("Status", om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.ipc.nsremote"));
        mcfgs.add("A_reservedMsgQueueId");
        mcfgs.add("A_nameIsTooLong");
        mcfgs.add("E_outOfMemory");
        mcfgs.add("heapId");
        mcfgs.add("timeoutInMicroSecs");
        mcfgs.add("timeout");
        icfgs.add("timeout");
        vo.bind("Type", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Type", "ti.sdo.ipc.nsremote"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance_State", "ti.sdo.ipc.nsremote"));
        tdefs.add(om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Instance_State", "ti.sdo.ipc.nsremote"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Module_State", "ti.sdo.ipc.nsremote"));
        tdefs.add(om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Module_State", "ti.sdo.ipc.nsremote"));
        vo.bind("S_SUCCESS", om.findStrict("ti.sdo.utils.INameServerRemote.S_SUCCESS", "ti.sdo.ipc.nsremote"));
        vo.bind("E_FAIL", om.findStrict("ti.sdo.utils.INameServerRemote.E_FAIL", "ti.sdo.ipc.nsremote"));
        vo.bind("E_ERROR", om.findStrict("ti.sdo.utils.INameServerRemote.E_ERROR", "ti.sdo.ipc.nsremote"));
        vo.bind("REQUEST", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.REQUEST", "ti.sdo.ipc.nsremote"));
        vo.bind("RESPONSE", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.RESPONSE", "ti.sdo.ipc.nsremote"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.utils");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.nsremote")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.nsremote.NameServerMessageQ$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$nsremote$NameServerMessageQ$$__initObject"));
        }//isCFG
        vo.bind("attach", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.attach", "ti.sdo.ipc.nsremote"));
        vo.bind("detach", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.detach", "ti.sdo.ipc.nsremote"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.sharedMemReq", "ti.sdo.ipc.nsremote"));
        vo.bind("swiFxn", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.swiFxn", "ti.sdo.ipc.nsremote"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_nsremote_NameServerMessageQ_Handle__label__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_Module__startupDone__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__create__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__delete__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__destruct__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__get__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__first__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_Object__next__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_Params__init__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_attach__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_detach__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_sharedMemReq__E", "ti_sdo_ipc_nsremote_NameServerMessageQ_get__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_outOfMemory"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_reservedMsgQueueId", "A_nameIsTooLong"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ.Object", "ti.sdo.ipc.nsremote"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "get", "entry", "%p, \"%s\", \"%s\", %p, %p, %p, %p", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NameServerMessageQ", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NameServerMessageQ");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sdo.ipc.nsremote")).findStrict("PARAMS", "ti.sdo.ipc.nsremote");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify", "ti.sdo.ipc.nsremote")).findStrict("PARAMS", "ti.sdo.ipc.nsremote");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ", "ti.sdo.ipc.nsremote")).findStrict("PARAMS", "ti.sdo.ipc.nsremote");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify", "ti.sdo.ipc.nsremote"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.nsremote.NameServerMessageQ", "ti.sdo.ipc.nsremote"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.nsremote.NameServerRemoteNotify", "ti.sdo.ipc.nsremote");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.nsremote.NameServerRemoteNotify")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.nsremote.NameServerMessageQ")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.nsremote")).add(pkgV);
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
        NameServerRemoteNotify$$OBJECTS();
        NameServerMessageQ$$OBJECTS();
        NameServerRemoteNotify$$CONSTS();
        NameServerMessageQ$$CONSTS();
        NameServerRemoteNotify$$CREATES();
        NameServerMessageQ$$CREATES();
        NameServerRemoteNotify$$FUNCTIONS();
        NameServerMessageQ$$FUNCTIONS();
        NameServerRemoteNotify$$SIZES();
        NameServerMessageQ$$SIZES();
        NameServerRemoteNotify$$TYPES();
        NameServerMessageQ$$TYPES();
        if (isROV) {
            NameServerRemoteNotify$$ROV();
            NameServerMessageQ$$ROV();
        }//isROV
        $$SINGLETONS();
        NameServerRemoteNotify$$SINGLETONS();
        NameServerMessageQ$$SINGLETONS();
        $$INITIALIZATION();
    }
}
