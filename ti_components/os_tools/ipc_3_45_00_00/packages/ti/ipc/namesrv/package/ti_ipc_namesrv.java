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

public class ti_ipc_namesrv
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
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.knl");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.gates");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.utils");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.ipc.namesrv.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.ipc.namesrv", new Value.Obj("ti.ipc.namesrv", pkgP));
    }

    void NameServerRemoteRpmsg$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg", new Value.Obj("ti.ipc.namesrv.NameServerRemoteRpmsg", po));
        pkgV.bind("NameServerRemoteRpmsg", vo);
        // decls 
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.Status", om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.ipc.namesrv"));
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.Type", new Proto.Enm("ti.ipc.namesrv.NameServerRemoteRpmsg.Type"));
        spo = (Proto.Obj)om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$Instance_State", new Proto.Obj());
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$Module_State", new Proto.Obj());
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$Object", new Proto.Obj());
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$Params", new Proto.Obj());
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.Params", new Proto.Str(po, false));
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.Handle", insP);
        if (isROV) {
            om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.Object", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance_State", "ti.ipc.namesrv"));
        }//isROV
    }

    void NameServerRemoteRpmsg$$CONSTS()
    {
        // module NameServerRemoteRpmsg
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.REQUEST", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Type", "ti.ipc.namesrv"), "ti.ipc.namesrv.NameServerRemoteRpmsg.REQUEST", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.RESPONSE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Type", "ti.ipc.namesrv"), "ti.ipc.namesrv.NameServerRemoteRpmsg.RESPONSE", xdc.services.intern.xsr.Enum.intValue(1L)+0));
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.attach", new Extern("ti_ipc_namesrv_NameServerRemoteRpmsg_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.detach", new Extern("ti_ipc_namesrv_NameServerRemoteRpmsg_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg.sharedMemReq", new Extern("ti_ipc_namesrv_NameServerRemoteRpmsg_sharedMemReq__E", "xdc_SizeT(*)(xdc_Ptr)", true, false));
    }

    void NameServerRemoteRpmsg$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$ipc$namesrv$NameServerRemoteRpmsg$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.ipc.namesrv.NameServerRemoteRpmsg.create() called before xdc.useModule('ti.ipc.namesrv.NameServerRemoteRpmsg')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.procId, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$create", new Proto.Fxn(om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Module", "ti.ipc.namesrv"), om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance", "ti.ipc.namesrv"), 2, 1, false));
                        fxn.addArg(0, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Params", "ti.ipc.namesrv"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$ipc$namesrv$NameServerRemoteRpmsg$$create = function( procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg'];\n");
                sb.append("var __inst = xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.ipc.namesrv']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [procId]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$construct", new Proto.Fxn(om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Module", "ti.ipc.namesrv"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg$$Object", "ti.ipc.namesrv"), null);
                        fxn.addArg(1, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Params", "ti.ipc.namesrv"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$ipc$namesrv$NameServerRemoteRpmsg$$construct = function( __obj, procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void NameServerRemoteRpmsg$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NameServerRemoteRpmsg$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance_State", "ti.ipc.namesrv");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Module_State", "ti.ipc.namesrv");
        sizes.clear();
        sizes.add(Global.newArray("semRemoteWait", "UPtr"));
        sizes.add(Global.newArray("gateMutex", "UPtr"));
        sizes.add(Global.newArray("nsMsg", "UPtr"));
        sizes.add(Global.newArray("nsPort", "TInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.ipc.namesrv.NameServerRemoteRpmsg.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NameServerRemoteRpmsg$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/namesrv/NameServerRemoteRpmsg.xs");
        om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Module", "ti.ipc.namesrv");
        po.init("ti.ipc.namesrv.NameServerRemoteRpmsg.Module", om.findStrict("ti.sdo.utils.INameServerRemote.Module", "ti.ipc.namesrv"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("timeoutInMicroSecs", Proto.Elm.newCNum("(xdc_UInt)"), 1000000L, "w");
            po.addFld("A_nameIsTooLong", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.ipc.namesrv"), Global.newObject("msg", "Too many characters in name"), "w");
            po.addFld("timeout", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg$$create", "ti.ipc.namesrv"), Global.get("ti$ipc$namesrv$NameServerRemoteRpmsg$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg$$construct", "ti.ipc.namesrv"), Global.get("ti$ipc$namesrv$NameServerRemoteRpmsg$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.ipc.namesrv.NameServerRemoteRpmsg$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance", "ti.ipc.namesrv");
        po.init("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance", om.findStrict("ti.sdo.utils.INameServerRemote.Instance", "ti.ipc.namesrv"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.ipc.namesrv"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg$$Params", "ti.ipc.namesrv");
        po.init("ti.ipc.namesrv.NameServerRemoteRpmsg.Params", om.findStrict("ti.sdo.utils.INameServerRemote$$Params", "ti.ipc.namesrv"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.ipc.namesrv"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg$$Object", "ti.ipc.namesrv");
        po.init("ti.ipc.namesrv.NameServerRemoteRpmsg.Object", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance", "ti.ipc.namesrv"));
        // struct NameServerRemoteRpmsg.Instance_State
        po = (Proto.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg$$Instance_State", "ti.ipc.namesrv");
        po.init("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
        // struct NameServerRemoteRpmsg.Module_State
        po = (Proto.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg$$Module_State", "ti.ipc.namesrv");
        po.init("ti.ipc.namesrv.NameServerRemoteRpmsg.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("semRemoteWait", (Proto)om.findStrict("ti.sysbios.knl.Semaphore.Handle", "ti.ipc.namesrv"), $$UNDEF, "w");
                po.addFld("gateMutex", (Proto)om.findStrict("ti.sysbios.gates.GateMutex.Handle", "ti.ipc.namesrv"), $$UNDEF, "w");
                po.addFld("nsMsg", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("nsPort", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
    }

    void NameServerRemoteRpmsg$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg", "ti.ipc.namesrv");
        po = (Proto.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg$$Instance_State", "ti.ipc.namesrv");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.ipc.namesrv.NameServerRemoteRpmsg.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg$$Instance_State", "ti.ipc.namesrv");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.ipc.namesrv.NameServerRemoteRpmsg.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg$$Module_State", "ti.ipc.namesrv");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.ipc.namesrv.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.ipc.namesrv"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/namesrv/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.ipc.namesrv"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.ipc.namesrv"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.ipc.namesrv"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.ipc.namesrv"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.ipc.namesrv"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.ipc.namesrv"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.ipc.namesrv", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.ipc.namesrv");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.ipc.namesrv.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.ipc.namesrv'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.ipc.namesrv$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.ipc.namesrv$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.ipc.namesrv$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void NameServerRemoteRpmsg$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg", "ti.ipc.namesrv");
        po = (Proto.Obj)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Module", "ti.ipc.namesrv");
        vo.init2(po, "ti.ipc.namesrv.NameServerRemoteRpmsg", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg$$capsule", "ti.ipc.namesrv"));
        vo.bind("Instance", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance", "ti.ipc.namesrv"));
        vo.bind("Params", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Params", "ti.ipc.namesrv"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Params", "ti.ipc.namesrv")).newInstance());
        vo.bind("Handle", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Handle", "ti.ipc.namesrv"));
        vo.bind("$package", om.findStrict("ti.ipc.namesrv", "ti.ipc.namesrv"));
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
        vo.bind("Status", om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.ipc.namesrv"));
        mcfgs.add("timeoutInMicroSecs");
        mcfgs.add("A_nameIsTooLong");
        mcfgs.add("timeout");
        icfgs.add("timeout");
        vo.bind("Type", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Type", "ti.ipc.namesrv"));
        vo.bind("Instance_State", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance_State", "ti.ipc.namesrv"));
        tdefs.add(om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Instance_State", "ti.ipc.namesrv"));
        vo.bind("Module_State", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Module_State", "ti.ipc.namesrv"));
        tdefs.add(om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Module_State", "ti.ipc.namesrv"));
        vo.bind("S_SUCCESS", om.findStrict("ti.sdo.utils.INameServerRemote.S_SUCCESS", "ti.ipc.namesrv"));
        vo.bind("E_FAIL", om.findStrict("ti.sdo.utils.INameServerRemote.E_FAIL", "ti.ipc.namesrv"));
        vo.bind("E_ERROR", om.findStrict("ti.sdo.utils.INameServerRemote.E_ERROR", "ti.ipc.namesrv"));
        vo.bind("REQUEST", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.REQUEST", "ti.ipc.namesrv"));
        vo.bind("RESPONSE", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.RESPONSE", "ti.ipc.namesrv"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.utils");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.namesrv")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.ipc.namesrv.NameServerRemoteRpmsg$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$ipc$namesrv$NameServerRemoteRpmsg$$__initObject"));
        }//isCFG
        vo.bind("attach", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.attach", "ti.ipc.namesrv"));
        vo.bind("detach", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.detach", "ti.ipc.namesrv"));
        vo.bind("sharedMemReq", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.sharedMemReq", "ti.ipc.namesrv"));
        vo.bind("$$fxntab", Global.newArray("ti_ipc_namesrv_NameServerRemoteRpmsg_Handle__label__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_Module__startupDone__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__create__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__delete__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__destruct__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__get__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__first__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_Object__next__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_Params__init__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_attach__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_detach__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_sharedMemReq__E", "ti_ipc_namesrv_NameServerRemoteRpmsg_get__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_nameIsTooLong"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg.Object", "ti.ipc.namesrv"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "get", "entry", "%p, \"%s\", \"%s\", %p, %p, %p, %p", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NameServerRemoteRpmsg", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NameServerRemoteRpmsg");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.ipc.namesrv")).findStrict("PARAMS", "ti.ipc.namesrv");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg", "ti.ipc.namesrv")).findStrict("PARAMS", "ti.ipc.namesrv");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.namesrv.NameServerRemoteRpmsg", "ti.ipc.namesrv"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.ipc.namesrv.NameServerRemoteRpmsg")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.ipc.namesrv")).add(pkgV);
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
        NameServerRemoteRpmsg$$OBJECTS();
        NameServerRemoteRpmsg$$CONSTS();
        NameServerRemoteRpmsg$$CREATES();
        NameServerRemoteRpmsg$$FUNCTIONS();
        NameServerRemoteRpmsg$$SIZES();
        NameServerRemoteRpmsg$$TYPES();
        if (isROV) {
            NameServerRemoteRpmsg$$ROV();
        }//isROV
        $$SINGLETONS();
        NameServerRemoteRpmsg$$SINGLETONS();
        $$INITIALIZATION();
    }
}
