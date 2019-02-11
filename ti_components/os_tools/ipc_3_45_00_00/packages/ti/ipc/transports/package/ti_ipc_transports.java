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

public class ti_ipc_transports
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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.interfaces");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.ipc.transports.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.ipc.transports", new Value.Obj("ti.ipc.transports", pkgP));
    }

    void TransportRpmsg$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.transports.TransportRpmsg.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.transports.TransportRpmsg", new Value.Obj("ti.ipc.transports.TransportRpmsg", po));
        pkgV.bind("TransportRpmsg", vo);
        // decls 
        om.bind("ti.ipc.transports.TransportRpmsg.Status", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Status", "ti.ipc.transports"));
        om.bind("ti.ipc.transports.TransportRpmsg.Reason", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason", "ti.ipc.transports"));
        spo = (Proto.Obj)om.bind("ti.ipc.transports.TransportRpmsg$$Instance_State", new Proto.Obj());
        om.bind("ti.ipc.transports.TransportRpmsg.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.ipc.transports.TransportRpmsg.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.ipc.transports.TransportRpmsg$$Object", new Proto.Obj());
        om.bind("ti.ipc.transports.TransportRpmsg.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.ipc.transports.TransportRpmsg$$Params", new Proto.Obj());
        om.bind("ti.ipc.transports.TransportRpmsg.Params", new Proto.Str(po, false));
        om.bind("ti.ipc.transports.TransportRpmsg.Handle", insP);
        if (isROV) {
            om.bind("ti.ipc.transports.TransportRpmsg.Object", om.findStrict("ti.ipc.transports.TransportRpmsg.Instance_State", "ti.ipc.transports"));
        }//isROV
    }

    void TransportRpmsgSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.transports.TransportRpmsgSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.transports.TransportRpmsgSetup", new Value.Obj("ti.ipc.transports.TransportRpmsgSetup", po));
        pkgV.bind("TransportRpmsgSetup", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.ipc.transports.TransportRpmsgSetup$$Module_State", new Proto.Obj());
        om.bind("ti.ipc.transports.TransportRpmsgSetup.Module_State", new Proto.Str(spo, false));
    }

    void TransportRpmsg$$CONSTS()
    {
        // module TransportRpmsg
        om.bind("ti.ipc.transports.TransportRpmsg.setErrFxn", new Extern("ti_ipc_transports_TransportRpmsg_setErrFxn__E", "xdc_Void(*)(xdc_Void(*)(ti_sdo_ipc_interfaces_IMessageQTransport_Reason,ti_sdo_ipc_interfaces_IMessageQTransport_Handle,xdc_Ptr,xdc_UArg))", true, false));
    }

    void TransportRpmsgSetup$$CONSTS()
    {
        // module TransportRpmsgSetup
        om.bind("ti.ipc.transports.TransportRpmsgSetup.attach", new Extern("ti_ipc_transports_TransportRpmsgSetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.ipc.transports.TransportRpmsgSetup.detach", new Extern("ti_ipc_transports_TransportRpmsgSetup_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.ipc.transports.TransportRpmsgSetup.isRegistered", new Extern("ti_ipc_transports_TransportRpmsgSetup_isRegistered__E", "xdc_Bool(*)(xdc_UInt16)", true, false));
        om.bind("ti.ipc.transports.TransportRpmsgSetup.sharedMemReq", new Extern("ti_ipc_transports_TransportRpmsgSetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_Ptr)", true, false));
    }

    void TransportRpmsg$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$ipc$transports$TransportRpmsg$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.ipc.transports.TransportRpmsg.create() called before xdc.useModule('ti.ipc.transports.TransportRpmsg')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.procId, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.ipc.transports.TransportRpmsg$$create", new Proto.Fxn(om.findStrict("ti.ipc.transports.TransportRpmsg.Module", "ti.ipc.transports"), om.findStrict("ti.ipc.transports.TransportRpmsg.Instance", "ti.ipc.transports"), 2, 1, false));
                        fxn.addArg(0, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.ipc.transports.TransportRpmsg.Params", "ti.ipc.transports"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$ipc$transports$TransportRpmsg$$create = function( procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.ipc.transports.TransportRpmsg'];\n");
                sb.append("var __inst = xdc.om['ti.ipc.transports.TransportRpmsg.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.ipc.transports']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.ipc.transports.TransportRpmsg'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [procId]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.ipc.transports.TransportRpmsg'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.ipc.transports.TransportRpmsg$$construct", new Proto.Fxn(om.findStrict("ti.ipc.transports.TransportRpmsg.Module", "ti.ipc.transports"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.ipc.transports.TransportRpmsg$$Object", "ti.ipc.transports"), null);
                        fxn.addArg(1, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.ipc.transports.TransportRpmsg.Params", "ti.ipc.transports"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$ipc$transports$TransportRpmsg$$construct = function( __obj, procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.ipc.transports.TransportRpmsg'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.ipc.transports.TransportRpmsg'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.ipc.transports.TransportRpmsg'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void TransportRpmsgSetup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TransportRpmsg$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TransportRpmsgSetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TransportRpmsg$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.ipc.transports.TransportRpmsg.Instance_State", "ti.ipc.transports");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("priority", "UInt16"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        sizes.add(Global.newArray("msgqHandle", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.ipc.transports.TransportRpmsg.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.ipc.transports.TransportRpmsg.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.ipc.transports.TransportRpmsg.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TransportRpmsgSetup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.ipc.transports.TransportRpmsgSetup.Module_State", "ti.ipc.transports");
        sizes.clear();
        sizes.add(Global.newArray("handles", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.ipc.transports.TransportRpmsgSetup.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.ipc.transports.TransportRpmsgSetup.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.ipc.transports.TransportRpmsgSetup.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TransportRpmsg$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/transports/TransportRpmsg.xs");
        om.bind("ti.ipc.transports.TransportRpmsg$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsg.Module", "ti.ipc.transports");
        po.init("ti.ipc.transports.TransportRpmsg.Module", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Module", "ti.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.ipc.transports.TransportRpmsg$$create", "ti.ipc.transports"), Global.get("ti$ipc$transports$TransportRpmsg$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.ipc.transports.TransportRpmsg$$construct", "ti.ipc.transports"), Global.get("ti$ipc$transports$TransportRpmsg$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.transports.TransportRpmsg$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.transports.TransportRpmsg$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.ipc.transports.TransportRpmsg$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.ipc.transports.TransportRpmsg$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.transports.TransportRpmsg$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.ipc.transports.TransportRpmsg$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsg.Instance", "ti.ipc.transports");
        po.init("ti.ipc.transports.TransportRpmsg.Instance", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Instance", "ti.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.ipc.transports"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsg$$Params", "ti.ipc.transports");
        po.init("ti.ipc.transports.TransportRpmsg.Params", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport$$Params", "ti.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.ipc.transports"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsg$$Object", "ti.ipc.transports");
        po.init("ti.ipc.transports.TransportRpmsg.Object", om.findStrict("ti.ipc.transports.TransportRpmsg.Instance", "ti.ipc.transports"));
        // struct TransportRpmsg.Instance_State
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsg$$Instance_State", "ti.ipc.transports");
        po.init("ti.ipc.transports.TransportRpmsg.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("priority", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("msgqHandle", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void TransportRpmsgSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/transports/TransportRpmsgSetup.xs");
        om.bind("ti.ipc.transports.TransportRpmsgSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsgSetup.Module", "ti.ipc.transports");
        po.init("ti.ipc.transports.TransportRpmsgSetup.Module", om.findStrict("ti.sdo.ipc.interfaces.ITransportSetup.Module", "ti.ipc.transports"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.transports.TransportRpmsgSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.transports.TransportRpmsgSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.ipc.transports.TransportRpmsgSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.transports.TransportRpmsgSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct TransportRpmsgSetup.Module_State
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsgSetup$$Module_State", "ti.ipc.transports");
        po.init("ti.ipc.transports.TransportRpmsgSetup.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("handles", new Proto.Arr((Proto)om.findStrict("ti.ipc.transports.TransportRpmsg.Handle", "ti.ipc.transports"), false), $$DEFAULT, "w");
    }

    void TransportRpmsg$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.transports.TransportRpmsg", "ti.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsg$$Instance_State", "ti.ipc.transports");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.ipc.transports.TransportRpmsg.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsg$$Instance_State", "ti.ipc.transports");
    }

    void TransportRpmsgSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.transports.TransportRpmsgSetup", "ti.ipc.transports");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.ipc.transports.TransportRpmsgSetup.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsgSetup$$Module_State", "ti.ipc.transports");
        po.bind("handles$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Ptr", "isScalar", true));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.ipc.transports.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.ipc.transports"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/transports/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.ipc.transports"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.ipc.transports"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.ipc.transports"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.ipc.transports"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.ipc.transports"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.ipc.transports"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.ipc.transports", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.ipc.transports");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.ipc.transports.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.ipc.transports'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.ipc.transports$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.ipc.transports$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.ipc.transports$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/ti.ipc.transports.aem4',\n");
            sb.append("'lib/debug/ti.ipc.transports_rpmsg2.aem4',\n");
            sb.append("'lib/release/ti.ipc.transports.aem4',\n");
            sb.append("'lib/release/ti.ipc.transports_rpmsg2.aem4',\n");
            sb.append("'lib/debug/ti.ipc.transports.aem4f',\n");
            sb.append("'lib/debug/ti.ipc.transports_rpmsg2.aem4f',\n");
            sb.append("'lib/release/ti.ipc.transports.aem4f',\n");
            sb.append("'lib/release/ti.ipc.transports_rpmsg2.aem4f',\n");
            sb.append("'lib/debug/ti.ipc.transports.ae66',\n");
            sb.append("'lib/debug/ti.ipc.transports_rpmsg2.ae66',\n");
            sb.append("'lib/release/ti.ipc.transports.ae66',\n");
            sb.append("'lib/release/ti.ipc.transports_rpmsg2.ae66',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/ti.ipc.transports.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.ipc.transports_rpmsg2.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.ipc.transports.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.ipc.transports_rpmsg2.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.ipc.transports.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.ipc.transports_rpmsg2.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.ipc.transports.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.ipc.transports_rpmsg2.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.ipc.transports.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/ti.ipc.transports_rpmsg2.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/ti.ipc.transports.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/ti.ipc.transports_rpmsg2.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void TransportRpmsg$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.transports.TransportRpmsg", "ti.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsg.Module", "ti.ipc.transports");
        vo.init2(po, "ti.ipc.transports.TransportRpmsg", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.transports.TransportRpmsg$$capsule", "ti.ipc.transports"));
        vo.bind("Instance", om.findStrict("ti.ipc.transports.TransportRpmsg.Instance", "ti.ipc.transports"));
        vo.bind("Params", om.findStrict("ti.ipc.transports.TransportRpmsg.Params", "ti.ipc.transports"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.ipc.transports.TransportRpmsg.Params", "ti.ipc.transports")).newInstance());
        vo.bind("Handle", om.findStrict("ti.ipc.transports.TransportRpmsg.Handle", "ti.ipc.transports"));
        vo.bind("$package", om.findStrict("ti.ipc.transports", "ti.ipc.transports"));
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
        vo.bind("Status", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Status", "ti.ipc.transports"));
        vo.bind("Reason", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason", "ti.ipc.transports"));
        mcfgs.add("errFxn");
        vo.bind("ErrFxn", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.ErrFxn", "ti.ipc.transports"));
        vo.bind("Instance_State", om.findStrict("ti.ipc.transports.TransportRpmsg.Instance_State", "ti.ipc.transports"));
        tdefs.add(om.findStrict("ti.ipc.transports.TransportRpmsg.Instance_State", "ti.ipc.transports"));
        vo.bind("S_SUCCESS", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.S_SUCCESS", "ti.ipc.transports"));
        vo.bind("E_FAIL", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.E_FAIL", "ti.ipc.transports"));
        vo.bind("E_ERROR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.E_ERROR", "ti.ipc.transports"));
        vo.bind("Reason_FAILEDPUT", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_FAILEDPUT", "ti.ipc.transports"));
        vo.bind("Reason_INTERNALERR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_INTERNALERR", "ti.ipc.transports"));
        vo.bind("Reason_PHYSICALERR", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_PHYSICALERR", "ti.ipc.transports"));
        vo.bind("Reason_FAILEDALLOC", om.findStrict("ti.sdo.ipc.interfaces.IMessageQTransport.Reason_FAILEDALLOC", "ti.ipc.transports"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.transports")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.ipc.transports.TransportRpmsg$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$ipc$transports$TransportRpmsg$$__initObject"));
        }//isCFG
        vo.bind("setErrFxn", om.findStrict("ti.ipc.transports.TransportRpmsg.setErrFxn", "ti.ipc.transports"));
        vo.bind("$$fxntab", Global.newArray("ti_ipc_transports_TransportRpmsg_Handle__label__E", "ti_ipc_transports_TransportRpmsg_Module__startupDone__E", "ti_ipc_transports_TransportRpmsg_Object__create__E", "ti_ipc_transports_TransportRpmsg_Object__delete__E", "ti_ipc_transports_TransportRpmsg_Object__destruct__E", "ti_ipc_transports_TransportRpmsg_Object__get__E", "ti_ipc_transports_TransportRpmsg_Object__first__E", "ti_ipc_transports_TransportRpmsg_Object__next__E", "ti_ipc_transports_TransportRpmsg_Params__init__E", "ti_ipc_transports_TransportRpmsg_setErrFxn__E", "ti_ipc_transports_TransportRpmsg_getStatus__E", "ti_ipc_transports_TransportRpmsg_put__E", "ti_ipc_transports_TransportRpmsg_control__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.ipc.transports.TransportRpmsg.Object", "ti.ipc.transports"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TransportRpmsg", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TransportRpmsg");
    }

    void TransportRpmsgSetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.transports.TransportRpmsgSetup", "ti.ipc.transports");
        po = (Proto.Obj)om.findStrict("ti.ipc.transports.TransportRpmsgSetup.Module", "ti.ipc.transports");
        vo.init2(po, "ti.ipc.transports.TransportRpmsgSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.transports.TransportRpmsgSetup$$capsule", "ti.ipc.transports"));
        vo.bind("$package", om.findStrict("ti.ipc.transports", "ti.ipc.transports"));
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
        vo.bind("Module_State", om.findStrict("ti.ipc.transports.TransportRpmsgSetup.Module_State", "ti.ipc.transports"));
        tdefs.add(om.findStrict("ti.ipc.transports.TransportRpmsgSetup.Module_State", "ti.ipc.transports"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.transports")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.ipc.transports.TransportRpmsgSetup.attach", "ti.ipc.transports"));
        vo.bind("detach", om.findStrict("ti.ipc.transports.TransportRpmsgSetup.detach", "ti.ipc.transports"));
        vo.bind("isRegistered", om.findStrict("ti.ipc.transports.TransportRpmsgSetup.isRegistered", "ti.ipc.transports"));
        vo.bind("sharedMemReq", om.findStrict("ti.ipc.transports.TransportRpmsgSetup.sharedMemReq", "ti.ipc.transports"));
        vo.bind("$$fxntab", Global.newArray("ti_ipc_transports_TransportRpmsgSetup_Module__startupDone__E", "ti_ipc_transports_TransportRpmsgSetup_attach__E", "ti_ipc_transports_TransportRpmsgSetup_detach__E", "ti_ipc_transports_TransportRpmsgSetup_isRegistered__E", "ti_ipc_transports_TransportRpmsgSetup_sharedMemReq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TransportRpmsgSetup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TransportRpmsgSetup");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.ipc.transports")).findStrict("PARAMS", "ti.ipc.transports");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.ipc.transports.TransportRpmsg", "ti.ipc.transports")).findStrict("PARAMS", "ti.ipc.transports");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.transports.TransportRpmsg", "ti.ipc.transports"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.transports.TransportRpmsgSetup", "ti.ipc.transports"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.ipc.transports.TransportRpmsg")).bless();
        ((Value.Obj)om.getv("ti.ipc.transports.TransportRpmsgSetup")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.ipc.transports")).add(pkgV);
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
        TransportRpmsg$$OBJECTS();
        TransportRpmsgSetup$$OBJECTS();
        TransportRpmsg$$CONSTS();
        TransportRpmsgSetup$$CONSTS();
        TransportRpmsg$$CREATES();
        TransportRpmsgSetup$$CREATES();
        TransportRpmsg$$FUNCTIONS();
        TransportRpmsgSetup$$FUNCTIONS();
        TransportRpmsg$$SIZES();
        TransportRpmsgSetup$$SIZES();
        TransportRpmsg$$TYPES();
        TransportRpmsgSetup$$TYPES();
        if (isROV) {
            TransportRpmsg$$ROV();
            TransportRpmsgSetup$$ROV();
        }//isROV
        $$SINGLETONS();
        TransportRpmsg$$SINGLETONS();
        TransportRpmsgSetup$$SINGLETONS();
        $$INITIALIZATION();
    }
}
