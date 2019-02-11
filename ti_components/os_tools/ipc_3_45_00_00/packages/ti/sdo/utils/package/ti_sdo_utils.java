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

public class ti_sdo_utils
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
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.gates");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime.knl");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.utils.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.utils", new Value.Obj("ti.sdo.utils", pkgP));
    }

    void Build$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.utils.Build.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.utils.Build", new Value.Obj("ti.sdo.utils.Build", po));
        pkgV.bind("Build", vo);
        // decls 
    }

    void NameServer$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.utils.NameServer.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.utils.NameServer", new Value.Obj("ti.sdo.utils.NameServer", po));
        pkgV.bind("NameServer", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.utils.NameServer$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServer.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.utils.NameServer$$NamesListView", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServer.NamesListView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.utils.NameServer$$Entry", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServer.Entry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.utils.NameServer$$TableEntry", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServer.TableEntry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.utils.NameServer$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServer.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.utils.NameServer$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServer.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.utils.NameServer.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.utils.NameServer$$Object", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServer.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.utils.NameServer$$Params", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServer.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.utils.NameServer.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.utils.NameServer.Object", om.findStrict("ti.sdo.utils.NameServer.Instance_State", "ti.sdo.utils"));
        }//isROV
    }

    void INameServerRemote$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.utils.INameServerRemote.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.utils.INameServerRemote", new Value.Obj("ti.sdo.utils.INameServerRemote", po));
        pkgV.bind("INameServerRemote", vo);
        // decls 
        om.bind("ti.sdo.utils.INameServerRemote.Status", new Proto.Enm("ti.sdo.utils.INameServerRemote.Status"));
        // insts 
        Object insP = om.bind("ti.sdo.utils.INameServerRemote.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.utils.INameServerRemote$$Object", new Proto.Obj());
        om.bind("ti.sdo.utils.INameServerRemote.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.utils.INameServerRemote$$Params", new Proto.Obj());
        om.bind("ti.sdo.utils.INameServerRemote.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.utils.INameServerRemote$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.utils.INameServerRemote.Instance_State", new Proto.Str(po, false));
        om.bind("ti.sdo.utils.INameServerRemote.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.utils.INameServerRemote.Object", om.findStrict("ti.sdo.utils.INameServerRemote.Instance_State", "ti.sdo.utils"));
        }//isROV
    }

    void NameServerRemoteNull$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.utils.NameServerRemoteNull.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.utils.NameServerRemoteNull", new Value.Obj("ti.sdo.utils.NameServerRemoteNull", po));
        pkgV.bind("NameServerRemoteNull", vo);
        // decls 
        om.bind("ti.sdo.utils.NameServerRemoteNull.Status", om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.utils"));
        spo = (Proto.Obj)om.bind("ti.sdo.utils.NameServerRemoteNull$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServerRemoteNull.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.utils.NameServerRemoteNull.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.utils.NameServerRemoteNull$$Object", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServerRemoteNull.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.utils.NameServerRemoteNull$$Params", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServerRemoteNull.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.utils.NameServerRemoteNull.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.utils.NameServerRemoteNull.Object", om.findStrict("ti.sdo.utils.NameServerRemoteNull.Instance_State", "ti.sdo.utils"));
        }//isROV
    }

    void MultiProc$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.utils.MultiProc.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.utils.MultiProc", new Value.Obj("ti.sdo.utils.MultiProc", po));
        pkgV.bind("MultiProc", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.utils.MultiProc$$ModuleView", new Proto.Obj());
        om.bind("ti.sdo.utils.MultiProc.ModuleView", new Proto.Str(spo, false));
        om.bind("ti.sdo.utils.MultiProc.ProcAddrMode", new Proto.Enm("ti.sdo.utils.MultiProc.ProcAddrMode"));
        spo = (Proto.Obj)om.bind("ti.sdo.utils.MultiProc$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.utils.MultiProc.Module_State", new Proto.Str(spo, false));
    }

    void List$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.utils.List.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.utils.List", new Value.Obj("ti.sdo.utils.List", po));
        pkgV.bind("List", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.utils.List$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.utils.List.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.utils.List$$Elem", new Proto.Obj());
        om.bind("ti.sdo.utils.List.Elem", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.utils.List$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.utils.List.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.utils.List.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.utils.List$$Object", new Proto.Obj());
        om.bind("ti.sdo.utils.List.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.utils.List$$Params", new Proto.Obj());
        om.bind("ti.sdo.utils.List.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.utils.List.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.utils.List.Object", om.findStrict("ti.sdo.utils.List.Instance_State", "ti.sdo.utils"));
        }//isROV
    }

    void NameServer_SetupProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.utils.NameServer_SetupProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.utils.NameServer_SetupProxy", new Value.Obj("ti.sdo.utils.NameServer_SetupProxy", po));
        pkgV.bind("NameServer_SetupProxy", vo);
        // decls 
        om.bind("ti.sdo.utils.NameServer_SetupProxy.Status", om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.utils"));
        // insts 
        Object insP = om.bind("ti.sdo.utils.NameServer_SetupProxy.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.utils.NameServer_SetupProxy$$Object", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServer_SetupProxy.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.utils.NameServer_SetupProxy$$Params", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServer_SetupProxy.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.utils.NameServer_SetupProxy$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.utils.NameServer_SetupProxy.Instance_State", new Proto.Str(po, false));
        om.bind("ti.sdo.utils.NameServer_SetupProxy.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.utils.NameServer_SetupProxy.Object", om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Instance_State", "ti.sdo.utils"));
        }//isROV
    }

    void Build$$CONSTS()
    {
        // module Build
    }

    void NameServer$$CONSTS()
    {
        // module NameServer
        om.bind("ti.sdo.utils.NameServer.ALLOWGROWTH", (Global.eval("~0")));
        om.bind("ti.sdo.utils.NameServer.isRegistered", new Extern("ti_sdo_utils_NameServer_isRegistered__E", "xdc_Bool(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.utils.NameServer.registerRemoteDriver", new Extern("ti_sdo_utils_NameServer_registerRemoteDriver__E", "xdc_Int(*)(ti_sdo_utils_INameServerRemote_Handle,xdc_UInt16)", true, false));
        om.bind("ti.sdo.utils.NameServer.unregisterRemoteDriver", new Extern("ti_sdo_utils_NameServer_unregisterRemoteDriver__E", "xdc_Void(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.utils.NameServer.postInit", new Extern("ti_sdo_utils_NameServer_postInit__I", "xdc_Int(*)(ti_sdo_utils_NameServer_Object*)", true, false));
        om.bind("ti.sdo.utils.NameServer.findLocal", new Extern("ti_sdo_utils_NameServer_findLocal__I", "ti_sdo_utils_NameServer_TableEntry*(*)(ti_sdo_utils_NameServer_Object*,xdc_String)", true, false));
        om.bind("ti.sdo.utils.NameServer.removeLocal", new Extern("ti_sdo_utils_NameServer_removeLocal__I", "xdc_Void(*)(ti_sdo_utils_NameServer_Object*,ti_sdo_utils_NameServer_TableEntry*)", true, false));
        om.bind("ti.sdo.utils.NameServer.editLocal", new Extern("ti_sdo_utils_NameServer_editLocal__I", "xdc_Void(*)(ti_sdo_utils_NameServer_Object*,ti_sdo_utils_NameServer_TableEntry*,xdc_Ptr)", true, false));
    }

    void INameServerRemote$$CONSTS()
    {
        // interface INameServerRemote
        om.bind("ti.sdo.utils.INameServerRemote.S_SUCCESS", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.utils"), "ti.sdo.utils.INameServerRemote.S_SUCCESS", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.sdo.utils.INameServerRemote.E_FAIL", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.utils"), "ti.sdo.utils.INameServerRemote.E_FAIL", xdc.services.intern.xsr.Enum.intValue(Global.eval("-1"))+0));
        om.bind("ti.sdo.utils.INameServerRemote.E_ERROR", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.utils"), "ti.sdo.utils.INameServerRemote.E_ERROR", xdc.services.intern.xsr.Enum.intValue(Global.eval("-2"))+0));
    }

    void NameServerRemoteNull$$CONSTS()
    {
        // module NameServerRemoteNull
        om.bind("ti.sdo.utils.NameServerRemoteNull.attach", new Extern("ti_sdo_utils_NameServerRemoteNull_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.utils.NameServerRemoteNull.detach", new Extern("ti_sdo_utils_NameServerRemoteNull_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.utils.NameServerRemoteNull.sharedMemReq", new Extern("ti_sdo_utils_NameServerRemoteNull_sharedMemReq__E", "xdc_SizeT(*)(xdc_Ptr)", true, false));
    }

    void MultiProc$$CONSTS()
    {
        // module MultiProc
        om.bind("ti.sdo.utils.MultiProc.INVALIDID", 0xFFFFL);
        om.bind("ti.sdo.utils.MultiProc.ProcAddrMode_Global", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.utils.MultiProc.ProcAddrMode", "ti.sdo.utils"), "ti.sdo.utils.MultiProc.ProcAddrMode_Global", 0));
        om.bind("ti.sdo.utils.MultiProc.ProcAddrMode_Cluster", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.utils.MultiProc.ProcAddrMode", "ti.sdo.utils"), "ti.sdo.utils.MultiProc.ProcAddrMode_Cluster", 1));
        om.bind("ti.sdo.utils.MultiProc.getClusterId", new Extern("ti_sdo_utils_MultiProc_getClusterId__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.utils.MultiProc.dummy", new Extern("ti_sdo_utils_MultiProc_dummy__E", "xdc_Void(*)(xdc_Void)", true, false));
    }

    void List$$CONSTS()
    {
        // module List
        om.bind("ti.sdo.utils.List.elemClear", new Extern("ti_sdo_utils_List_elemClear__E", "xdc_Void(*)(ti_sdo_utils_List_Elem*)", true, false));
    }

    void NameServer_SetupProxy$$CONSTS()
    {
        // module NameServer_SetupProxy
        om.bind("ti.sdo.utils.NameServer_SetupProxy.attach", new Extern("ti_sdo_utils_NameServer_SetupProxy_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.utils.NameServer_SetupProxy.detach", new Extern("ti_sdo_utils_NameServer_SetupProxy_detach__E", "xdc_Int(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.utils.NameServer_SetupProxy.sharedMemReq", new Extern("ti_sdo_utils_NameServer_SetupProxy_sharedMemReq__E", "xdc_SizeT(*)(xdc_Ptr)", true, false));
    }

    void Build$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NameServer$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$utils$NameServer$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.utils.NameServer.create() called before xdc.useModule('ti.sdo.utils.NameServer')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.name, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.utils.NameServer$$create", new Proto.Fxn(om.findStrict("ti.sdo.utils.NameServer.Module", "ti.sdo.utils"), om.findStrict("ti.sdo.utils.NameServer.Instance", "ti.sdo.utils"), 2, 1, false));
                        fxn.addArg(0, "name", $$T_Str, $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.utils.NameServer.Params", "ti.sdo.utils"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$utils$NameServer$$create = function( name, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.utils.NameServer'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.utils.NameServer.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.utils']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {name:name});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.utils.NameServer'].Instance_State);\n");
                sb.append("__inst.metaTable = __mod.PARAMS.metaTable;\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [name]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.utils.NameServer'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.utils.NameServer$$construct", new Proto.Fxn(om.findStrict("ti.sdo.utils.NameServer.Module", "ti.sdo.utils"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.utils.NameServer$$Object", "ti.sdo.utils"), null);
                        fxn.addArg(1, "name", $$T_Str, $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.utils.NameServer.Params", "ti.sdo.utils"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$utils$NameServer$$construct = function( __obj, name, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.utils.NameServer'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {name:name});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.utils.NameServer'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("__inst.metaTable = __mod.PARAMS.metaTable;\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.utils.NameServer'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void INameServerRemote$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NameServerRemoteNull$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$utils$NameServerRemoteNull$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.utils.NameServerRemoteNull.create() called before xdc.useModule('ti.sdo.utils.NameServerRemoteNull')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.procId, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.utils.NameServerRemoteNull$$create", new Proto.Fxn(om.findStrict("ti.sdo.utils.NameServerRemoteNull.Module", "ti.sdo.utils"), om.findStrict("ti.sdo.utils.NameServerRemoteNull.Instance", "ti.sdo.utils"), 2, 1, false));
                        fxn.addArg(0, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.utils.NameServerRemoteNull.Params", "ti.sdo.utils"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$utils$NameServerRemoteNull$$create = function( procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.utils.NameServerRemoteNull'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.utils.NameServerRemoteNull.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.utils']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.utils.NameServerRemoteNull'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [procId]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.utils.NameServerRemoteNull'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.utils.NameServerRemoteNull$$construct", new Proto.Fxn(om.findStrict("ti.sdo.utils.NameServerRemoteNull.Module", "ti.sdo.utils"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.utils.NameServerRemoteNull$$Object", "ti.sdo.utils"), null);
                        fxn.addArg(1, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.utils.NameServerRemoteNull.Params", "ti.sdo.utils"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$utils$NameServerRemoteNull$$construct = function( __obj, procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.utils.NameServerRemoteNull'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.utils.NameServerRemoteNull'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.utils.NameServerRemoteNull'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void MultiProc$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void List$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$utils$List$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.utils.List.create() called before xdc.useModule('ti.sdo.utils.List')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.utils.List$$create", new Proto.Fxn(om.findStrict("ti.sdo.utils.List.Module", "ti.sdo.utils"), om.findStrict("ti.sdo.utils.List.Instance", "ti.sdo.utils"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.utils.List.Params", "ti.sdo.utils"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$utils$List$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.utils.List'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.utils.List.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.utils']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.utils.List'].Instance_State);\n");
                sb.append("__inst.metaList = __mod.PARAMS.metaList;\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.utils.List'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.utils.List$$construct", new Proto.Fxn(om.findStrict("ti.sdo.utils.List.Module", "ti.sdo.utils"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.utils.List$$Object", "ti.sdo.utils"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.utils.List.Params", "ti.sdo.utils"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$utils$List$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.utils.List'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.utils.List'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("__inst.metaList = __mod.PARAMS.metaList;\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.utils.List'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void NameServer_SetupProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$utils$NameServer_SetupProxy$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.utils.NameServer_SetupProxy.create() called before xdc.useModule('ti.sdo.utils.NameServer_SetupProxy')\");\n");
                sb.append("}\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.utils.NameServer_SetupProxy$$create", new Proto.Fxn(om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Module", "ti.sdo.utils"), om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Instance", "ti.sdo.utils"), 2, 1, false));
                        fxn.addArg(0, "procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Params", "ti.sdo.utils"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$utils$NameServer_SetupProxy$$create = function( procId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.utils.NameServer_SetupProxy'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.utils.NameServer_SetupProxy.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.utils']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {procId:procId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.utils.NameServer_SetupProxy'].Instance_State);\n");
                sb.append("if (!__mod.delegate$) {\n");
                    sb.append("throw new Error(\"Unbound proxy module: ti.sdo.utils.NameServer_SetupProxy\");\n");
                sb.append("}\n");
                sb.append("var __dmod = __mod.delegate$.$orig;\n");
                sb.append("var __dinst = __dmod.create(procId, __params);\n");
                sb.append("__inst.$$bind('delegate$', __dinst);\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [procId]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.utils.NameServer_SetupProxy'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void Build$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Build.getDefaultCustomCCOpts
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.Build$$getDefaultCustomCCOpts", new Proto.Fxn(om.findStrict("ti.sdo.utils.Build.Module", "ti.sdo.utils"), $$T_Str, 0, 0, false));
        // fxn Build.getDefs
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.Build$$getDefs", new Proto.Fxn(om.findStrict("ti.sdo.utils.Build.Module", "ti.sdo.utils"), $$T_Str, 0, 0, false));
        // fxn Build.getCFiles
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.Build$$getCFiles", new Proto.Fxn(om.findStrict("ti.sdo.utils.Build.Module", "ti.sdo.utils"), $$T_Str, 1, 1, false));
                fxn.addArg(0, "target", $$T_Str, $$UNDEF);
        // fxn Build.getAsmFiles
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.Build$$getAsmFiles", new Proto.Fxn(om.findStrict("ti.sdo.utils.Build.Module", "ti.sdo.utils"), $$T_Obj, 1, 1, false));
                fxn.addArg(0, "target", $$T_Str, $$UNDEF);
        // fxn Build.buildLibs
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.Build$$buildLibs", new Proto.Fxn(om.findStrict("ti.sdo.utils.Build.Module", "ti.sdo.utils"), null, 0, -1, false));
        // fxn Build.getLibs
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.Build$$getLibs", new Proto.Fxn(om.findStrict("ti.sdo.utils.Build.Module", "ti.sdo.utils"), null, 0, -1, false));
    }

    void NameServer$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn NameServer.modAddMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.NameServer$$modAddMeta", new Proto.Fxn(om.findStrict("ti.sdo.utils.NameServer.Module", "ti.sdo.utils"), null, 4, 4, false));
                fxn.addArg(0, "instName", $$T_Str, $$UNDEF);
                fxn.addArg(1, "name", $$T_Str, $$UNDEF);
                fxn.addArg(2, "value", $$T_Obj, $$UNDEF);
                fxn.addArg(3, "len", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF);
        // fxn NameServer.getName$view
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.NameServer$$getName$view", new Proto.Fxn(om.findStrict("ti.sdo.utils.NameServer.Module", "ti.sdo.utils"), $$T_Str, 2, 2, false));
                fxn.addArg(0, "tableName", $$T_Str, $$UNDEF);
                fxn.addArg(1, "value", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF);
        // fxn NameServer.getNameByKey$view
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.NameServer$$getNameByKey$view", new Proto.Fxn(om.findStrict("ti.sdo.utils.NameServer.Module", "ti.sdo.utils"), $$T_Str, 1, 1, false));
                fxn.addArg(0, "addr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF);
        // fxn NameServer.addUInt32Meta
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.NameServer$$addUInt32Meta", new Proto.Fxn(om.findStrict("ti.sdo.utils.NameServer.Instance", "ti.sdo.utils"), null, 2, 2, false));
                fxn.addArg(0, "name", $$T_Str, $$UNDEF);
                fxn.addArg(1, "value", $$T_Obj, $$UNDEF);
        // fxn NameServer.addMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.NameServer$$addMeta", new Proto.Fxn(om.findStrict("ti.sdo.utils.NameServer.Instance", "ti.sdo.utils"), null, 3, 3, false));
                fxn.addArg(0, "name", $$T_Str, $$UNDEF);
                fxn.addArg(1, "value", $$T_Obj, $$UNDEF);
                fxn.addArg(2, "len", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF);
        // fxn NameServer.getMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.NameServer$$getMeta", new Proto.Fxn(om.findStrict("ti.sdo.utils.NameServer.Instance", "ti.sdo.utils"), (Proto)om.findStrict("ti.sdo.utils.NameServer.Entry", "ti.sdo.utils"), 1, 1, false));
                fxn.addArg(0, "name", $$T_Str, $$UNDEF);
    }

    void INameServerRemote$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NameServerRemoteNull$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void MultiProc$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn MultiProc.getIdMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.MultiProc$$getIdMeta", new Proto.Fxn(om.findStrict("ti.sdo.utils.MultiProc.Module", "ti.sdo.utils"), Proto.Elm.newCNum("(xdc_UInt16)"), 1, 1, false));
                fxn.addArg(0, "name", $$T_Str, $$UNDEF);
        // fxn MultiProc.getDeviceProcNames
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.MultiProc$$getDeviceProcNames", new Proto.Fxn(om.findStrict("ti.sdo.utils.MultiProc.Module", "ti.sdo.utils"), $$T_Obj, 0, 0, false));
        // fxn MultiProc.setConfig
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.MultiProc$$setConfig", new Proto.Fxn(om.findStrict("ti.sdo.utils.MultiProc.Module", "ti.sdo.utils"), null, 2, 2, false));
                fxn.addArg(0, "name", $$T_Str, $$UNDEF);
                fxn.addArg(1, "nameList", new Proto.Arr($$T_Str, false), $$DEFAULT);
        // fxn MultiProc.getName$view
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.MultiProc$$getName$view", new Proto.Fxn(om.findStrict("ti.sdo.utils.MultiProc.Module", "ti.sdo.utils"), $$T_Str, 1, 1, false));
                fxn.addArg(0, "id", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF);
        // fxn MultiProc.self$view
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.MultiProc$$self$view", new Proto.Fxn(om.findStrict("ti.sdo.utils.MultiProc.Module", "ti.sdo.utils"), Proto.Elm.newCNum("(xdc_UInt)"), 0, 0, false));
    }

    void List$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn List.elemClearMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.List$$elemClearMeta", new Proto.Fxn(om.findStrict("ti.sdo.utils.List.Module", "ti.sdo.utils"), null, 1, 1, false));
                fxn.addArg(0, "elem", new Proto.Adr("ti_sdo_utils_List_Elem*", "PS"), $$UNDEF);
        // fxn List.putMeta
        fxn = (Proto.Fxn)om.bind("ti.sdo.utils.List$$putMeta", new Proto.Fxn(om.findStrict("ti.sdo.utils.List.Instance", "ti.sdo.utils"), null, 1, 1, false));
                fxn.addArg(0, "elem", new Proto.Adr("ti_sdo_utils_List_Elem*", "PS"), $$UNDEF);
    }

    void NameServer_SetupProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Build$$SIZES()
    {
    }

    void NameServer$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.utils.NameServer.TableEntry", "ti.sdo.utils");
        sizes.clear();
        sizes.add(Global.newArray("elem", "Sti.sdo.utils.List;Elem"));
        sizes.add(Global.newArray("name", "UPtr"));
        sizes.add(Global.newArray("len", "UInt"));
        sizes.add(Global.newArray("value", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.utils.NameServer.TableEntry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.utils.NameServer.TableEntry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.utils.NameServer.TableEntry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.utils.NameServer.Instance_State", "ti.sdo.utils");
        sizes.clear();
        sizes.add(Global.newArray("name", "UPtr"));
        sizes.add(Global.newArray("maxNameLen", "UInt"));
        sizes.add(Global.newArray("maxValueLen", "UInt"));
        sizes.add(Global.newArray("numStatic", "UInt"));
        sizes.add(Global.newArray("numDynamic", "UInt"));
        sizes.add(Global.newArray("table", "UPtr"));
        sizes.add(Global.newArray("names", "UPtr"));
        sizes.add(Global.newArray("values", "UPtr"));
        sizes.add(Global.newArray("tableHeap", "UPtr"));
        sizes.add(Global.newArray("checkExisting", "UShort"));
        sizes.add(Global.newArray("refCount", "UInt32"));
        sizes.add(Global.newArray("freeList", "Sti.sdo.utils.List;Instance_State"));
        sizes.add(Global.newArray("nameList", "Sti.sdo.utils.List;Instance_State"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.utils.NameServer.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.utils.NameServer.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.utils.NameServer.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.utils.NameServer.Module_State", "ti.sdo.utils");
        sizes.clear();
        sizes.add(Global.newArray("nsRemoteHandle", "Sxdc.runtime.Types;Vec"));
        sizes.add(Global.newArray("gate", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.utils.NameServer.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.utils.NameServer.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.utils.NameServer.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void INameServerRemote$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void NameServerRemoteNull$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.utils.NameServerRemoteNull.Instance_State", "ti.sdo.utils");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.utils.NameServerRemoteNull.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.utils.NameServerRemoteNull.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.utils.NameServerRemoteNull.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void MultiProc$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.utils.MultiProc.Module_State", "ti.sdo.utils");
        sizes.clear();
        sizes.add(Global.newArray("id", "UInt16"));
        sizes.add(Global.newArray("baseIdOfCluster", "UInt16"));
        sizes.add(Global.newArray("clusterProcList", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.utils.MultiProc.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.utils.MultiProc.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.utils.MultiProc.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void List$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.utils.List.Elem", "ti.sdo.utils");
        sizes.clear();
        sizes.add(Global.newArray("next", "UPtr"));
        sizes.add(Global.newArray("prev", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.utils.List.Elem']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.utils.List.Elem']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.utils.List.Elem'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.utils.List.Instance_State", "ti.sdo.utils");
        sizes.clear();
        sizes.add(Global.newArray("elem", "Sti.sdo.utils.List;Elem"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.utils.List.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.utils.List.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.utils.List.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NameServer_SetupProxy$$SIZES()
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

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/utils/Build.xs");
        om.bind("ti.sdo.utils.Build$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.Build.Module", "ti.sdo.utils");
        po.init("ti.sdo.utils.Build.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("doBuild", $$T_Bool, true, "wh");
        po.addFld("libDir", $$T_Str, null, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.utils.Build$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.utils.Build$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.utils.Build$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("getDefaultCustomCCOpts", (Proto.Fxn)om.findStrict("ti.sdo.utils.Build$$getDefaultCustomCCOpts", "ti.sdo.utils"), Global.get(cap, "getDefaultCustomCCOpts"));
                po.addFxn("getDefs", (Proto.Fxn)om.findStrict("ti.sdo.utils.Build$$getDefs", "ti.sdo.utils"), Global.get(cap, "getDefs"));
                po.addFxn("getCFiles", (Proto.Fxn)om.findStrict("ti.sdo.utils.Build$$getCFiles", "ti.sdo.utils"), Global.get(cap, "getCFiles"));
                po.addFxn("getAsmFiles", (Proto.Fxn)om.findStrict("ti.sdo.utils.Build$$getAsmFiles", "ti.sdo.utils"), Global.get(cap, "getAsmFiles"));
                po.addFxn("buildLibs", (Proto.Fxn)om.findStrict("ti.sdo.utils.Build$$buildLibs", "ti.sdo.utils"), Global.get(cap, "buildLibs"));
                po.addFxn("getLibs", (Proto.Fxn)om.findStrict("ti.sdo.utils.Build$$getLibs", "ti.sdo.utils"), Global.get(cap, "getLibs"));
    }

    void NameServer$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/utils/NameServer.xs");
        om.bind("ti.sdo.utils.NameServer$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer.Module", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.utils"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ALLOWGROWTH", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.utils"), $$UNDEF, "wh");
            po.addFld("A_invalidLen", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.utils"), Global.newObject("msg", "A_invalidLen: Invalid length"), "w");
            po.addFld("A_invArgument", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.utils"), Global.newObject("msg", "A_invArgument: Invalid argument supplied"), "w");
            po.addFld("E_maxReached", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.utils"), Global.newObject("msg", "E_maxReached: All entries in use. NameServer.maxRuntimeEntries is %d"), "w");
            po.addFld("E_entryExists", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.utils"), Global.newObject("msg", "E_entryExists: %s name already in table "), "w");
            po.addFld("E_paramMismatch", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.utils"), Global.newObject("msg", "E_paramMismatch: parameters do not match existing NameServer %s "), "w");
            po.addFldV("SetupProxy", (Proto)om.findStrict("ti.sdo.utils.INameServerRemote.Module", "ti.sdo.utils"), null, "wh", $$delegGet, $$delegSet);
            po.addFld("singleProcessor", $$T_Bool, true, "w");
            po.addFld("metaModTable", new Proto.Map(new Proto.Arr((Proto)om.findStrict("ti.sdo.utils.NameServer.Entry", "ti.sdo.utils"), false)), $$DEFAULT, "wh");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer$$create", "ti.sdo.utils"), Global.get("ti$sdo$utils$NameServer$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer$$construct", "ti.sdo.utils"), Global.get("ti$sdo$utils$NameServer$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.utils.NameServer$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.utils.NameServer$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.utils.NameServer$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.utils.NameServer$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.utils.NameServer$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.utils.NameServer$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                po.addFxn("modAddMeta", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer$$modAddMeta", "ti.sdo.utils"), Global.get(cap, "modAddMeta"));
                po.addFxn("getName$view", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer$$getName$view", "ti.sdo.utils"), Global.get(cap, "getName$view"));
                po.addFxn("getNameByKey$view", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer$$getNameByKey$view", "ti.sdo.utils"), Global.get(cap, "getNameByKey$view"));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer.Instance", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ALLOWGROWTH", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "rh");
        if (isCFG) {
            po.addFld("maxRuntimeEntries", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "w");
            po.addFld("tableHeap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "ti.sdo.utils"), null, "w");
            po.addFld("tableSection", $$T_Str, null, "wh");
            po.addFld("checkExisting", $$T_Bool, true, "w");
            po.addFld("maxValueLen", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), 16L, "w");
            po.addFld("metaTable", new Proto.Arr((Proto)om.findStrict("ti.sdo.utils.NameServer.Entry", "ti.sdo.utils"), false), $$DEFAULT, "wh");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.utils"), $$UNDEF, "w");
        }//isCFG
                po.addFxn("addUInt32Meta", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer$$addUInt32Meta", "ti.sdo.utils"), Global.get(cap, "addUInt32Meta"));
                po.addFxn("addMeta", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer$$addMeta", "ti.sdo.utils"), Global.get(cap, "addMeta"));
                po.addFxn("getMeta", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer$$getMeta", "ti.sdo.utils"), Global.get(cap, "getMeta"));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer$$Params", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ALLOWGROWTH", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "rh");
        if (isCFG) {
            po.addFld("maxRuntimeEntries", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "w");
            po.addFld("tableHeap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "ti.sdo.utils"), null, "w");
            po.addFld("tableSection", $$T_Str, null, "wh");
            po.addFld("checkExisting", $$T_Bool, true, "w");
            po.addFld("maxValueLen", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), 16L, "w");
            po.addFld("metaTable", new Proto.Arr((Proto)om.findStrict("ti.sdo.utils.NameServer.Entry", "ti.sdo.utils"), false), $$DEFAULT, "wh");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.utils"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer$$Object", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer.Object", om.findStrict("ti.sdo.utils.NameServer.Instance", "ti.sdo.utils"));
                po.addFxn("addUInt32Meta", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer$$addUInt32Meta", "ti.sdo.utils"), Global.get(cap, "addUInt32Meta"));
                po.addFxn("addMeta", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer$$addMeta", "ti.sdo.utils"), Global.get(cap, "addMeta"));
                po.addFxn("getMeta", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer$$getMeta", "ti.sdo.utils"), Global.get(cap, "getMeta"));
        // struct NameServer.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer$$BasicView", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("checkExisting", $$T_Bool, $$UNDEF, "w");
                po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("maxValueLen", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numStatic", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numDynamic", $$T_Str, $$UNDEF, "w");
        // struct NameServer.NamesListView
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer$$NamesListView", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer.NamesListView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("value", $$T_Str, $$UNDEF, "w");
                po.addFld("len", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("nsKey", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct NameServer.Entry
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer$$Entry", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer.Entry", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("len", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("value", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // typedef NameServer.EntryMap
        om.bind("ti.sdo.utils.NameServer.EntryMap", new Proto.Arr((Proto)om.findStrict("ti.sdo.utils.NameServer.Entry", "ti.sdo.utils"), false));
        // struct NameServer.TableEntry
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer$$TableEntry", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer.TableEntry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("elem", (Proto)om.findStrict("ti.sdo.utils.List.Elem", "ti.sdo.utils"), $$DEFAULT, "w");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("len", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("value", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct NameServer.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer$$Instance_State", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("maxValueLen", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numStatic", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numDynamic", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("table", new Proto.Arr((Proto)om.findStrict("ti.sdo.utils.NameServer.TableEntry", "ti.sdo.utils"), false), $$DEFAULT, "w");
                po.addFld("names", new Proto.Arr(Proto.Elm.newCNum("(xdc_Char)"), false), $$DEFAULT, "w");
                po.addFld("values", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt8)"), false), $$DEFAULT, "w");
                po.addFld("tableHeap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "ti.sdo.utils"), $$UNDEF, "w");
                po.addFld("checkExisting", $$T_Bool, $$UNDEF, "w");
                po.addFld("refCount", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFldV("freeList", (Proto)om.findStrict("ti.sdo.utils.List.Object", "ti.sdo.utils"), $$DEFAULT, "wh", $$objFldGet, $$objFldSet);
                po.addFld("Object_field_freeList", (Proto)om.findStrict("ti.sdo.utils.List.Object", "ti.sdo.utils"), $$DEFAULT, "w");
                po.addFldV("nameList", (Proto)om.findStrict("ti.sdo.utils.List.Object", "ti.sdo.utils"), $$DEFAULT, "wh", $$objFldGet, $$objFldSet);
                po.addFld("Object_field_nameList", (Proto)om.findStrict("ti.sdo.utils.List.Object", "ti.sdo.utils"), $$DEFAULT, "w");
        // struct NameServer.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer$$Module_State", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("nsRemoteHandle", new Proto.Arr((Proto)om.findStrict("ti.sdo.utils.INameServerRemote.Handle", "ti.sdo.utils"), true), $$DEFAULT, "w");
                po.addFld("gate", (Proto)om.findStrict("ti.sysbios.gates.GateSwi.Handle", "ti.sdo.utils"), $$UNDEF, "w");
    }

    void INameServerRemote$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.utils.INameServerRemote.Module", "ti.sdo.utils");
        po.init("ti.sdo.utils.INameServerRemote.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.utils"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.INameServerRemote.Instance", "ti.sdo.utils");
        po.init("ti.sdo.utils.INameServerRemote.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.INameServerRemote$$Params", "ti.sdo.utils");
        po.init("ti.sdo.utils.INameServerRemote.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void NameServerRemoteNull$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/utils/NameServerRemoteNull.xs");
        om.bind("ti.sdo.utils.NameServerRemoteNull$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServerRemoteNull.Module", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServerRemoteNull.Module", om.findStrict("ti.sdo.utils.INameServerRemote.Module", "ti.sdo.utils"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServerRemoteNull$$create", "ti.sdo.utils"), Global.get("ti$sdo$utils$NameServerRemoteNull$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServerRemoteNull$$construct", "ti.sdo.utils"), Global.get("ti$sdo$utils$NameServerRemoteNull$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.utils.NameServerRemoteNull$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.utils.NameServerRemoteNull$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.utils.NameServerRemoteNull$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.utils.NameServerRemoteNull$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.utils.NameServerRemoteNull$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.utils.NameServerRemoteNull$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServerRemoteNull.Instance", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServerRemoteNull.Instance", om.findStrict("ti.sdo.utils.INameServerRemote.Instance", "ti.sdo.utils"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.utils"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServerRemoteNull$$Params", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServerRemoteNull.Params", om.findStrict("ti.sdo.utils.INameServerRemote$$Params", "ti.sdo.utils"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.utils"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServerRemoteNull$$Object", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServerRemoteNull.Object", om.findStrict("ti.sdo.utils.NameServerRemoteNull.Instance", "ti.sdo.utils"));
        // struct NameServerRemoteNull.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServerRemoteNull$$Instance_State", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServerRemoteNull.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void MultiProc$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/utils/MultiProc.xs");
        om.bind("ti.sdo.utils.MultiProc$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.MultiProc.Module", "ti.sdo.utils");
        po.init("ti.sdo.utils.MultiProc.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.utils"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("INVALIDID", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.utils"), $$UNDEF, "wh");
            po.addFld("A_invalidMultiProcId", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.utils"), Global.newObject("msg", "A_invalidMultiProcId: Invalid MultiProc id"), "w");
            po.addFld("A_invalidProcName", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.utils"), Global.newObject("msg", "A_invalidProcName: NULL MultiProc name encountered"), "w");
            po.addFld("nameList", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
            po.addFld("id", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "wh");
            po.addFld("numProcsInCluster", Proto.Elm.newCNum("(xdc_UInt16)"), 1L, "w");
            po.addFld("baseIdOfCluster", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "wh");
            po.addFld("numProcessors", Proto.Elm.newCNum("(xdc_UInt16)"), 1L, "w");
            po.addFld("procAddrMode", (Proto)om.findStrict("ti.sdo.utils.MultiProc.ProcAddrMode", "ti.sdo.utils"), om.find("ti.sdo.utils.MultiProc.ProcAddrMode_Global"), "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.utils.MultiProc$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.utils.MultiProc$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.utils.MultiProc$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.utils.MultiProc$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("getIdMeta", (Proto.Fxn)om.findStrict("ti.sdo.utils.MultiProc$$getIdMeta", "ti.sdo.utils"), Global.get(cap, "getIdMeta"));
                po.addFxn("getDeviceProcNames", (Proto.Fxn)om.findStrict("ti.sdo.utils.MultiProc$$getDeviceProcNames", "ti.sdo.utils"), Global.get(cap, "getDeviceProcNames"));
                po.addFxn("setConfig", (Proto.Fxn)om.findStrict("ti.sdo.utils.MultiProc$$setConfig", "ti.sdo.utils"), Global.get(cap, "setConfig"));
                po.addFxn("getName$view", (Proto.Fxn)om.findStrict("ti.sdo.utils.MultiProc$$getName$view", "ti.sdo.utils"), Global.get(cap, "getName$view"));
                po.addFxn("self$view", (Proto.Fxn)om.findStrict("ti.sdo.utils.MultiProc$$self$view", "ti.sdo.utils"), Global.get(cap, "self$view"));
        // struct MultiProc.ModuleView
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.MultiProc$$ModuleView", "ti.sdo.utils");
        po.init("ti.sdo.utils.MultiProc.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("id", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("numProcessors", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("nameList", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
        // struct MultiProc.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.MultiProc$$Module_State", "ti.sdo.utils");
        po.init("ti.sdo.utils.MultiProc.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("id", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("baseIdOfCluster", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("clusterProcList", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt16)"), false), $$DEFAULT, "w");
    }

    void List$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/utils/List.xs");
        om.bind("ti.sdo.utils.List$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.List.Module", "ti.sdo.utils");
        po.init("ti.sdo.utils.List.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.utils"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.utils"), $$UNDEF, "wh");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.utils.List$$create", "ti.sdo.utils"), Global.get("ti$sdo$utils$List$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.utils.List$$construct", "ti.sdo.utils"), Global.get("ti$sdo$utils$List$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.utils.List$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.utils.List$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.utils.List$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.utils.List$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.utils.List$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.utils.List$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                po.addFxn("elemClearMeta", (Proto.Fxn)om.findStrict("ti.sdo.utils.List$$elemClearMeta", "ti.sdo.utils"), Global.get(cap, "elemClearMeta"));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.List.Instance", "ti.sdo.utils");
        po.init("ti.sdo.utils.List.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("metaList", new Proto.Arr($$T_Obj, false), $$DEFAULT, "wh");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.utils"), $$UNDEF, "w");
        }//isCFG
                po.addFxn("putMeta", (Proto.Fxn)om.findStrict("ti.sdo.utils.List$$putMeta", "ti.sdo.utils"), Global.get(cap, "putMeta"));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.List$$Params", "ti.sdo.utils");
        po.init("ti.sdo.utils.List.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("metaList", new Proto.Arr($$T_Obj, false), $$DEFAULT, "wh");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.utils"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.List$$Object", "ti.sdo.utils");
        po.init("ti.sdo.utils.List.Object", om.findStrict("ti.sdo.utils.List.Instance", "ti.sdo.utils"));
                po.addFxn("putMeta", (Proto.Fxn)om.findStrict("ti.sdo.utils.List$$putMeta", "ti.sdo.utils"), Global.get(cap, "putMeta"));
        // struct List.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.List$$BasicView", "ti.sdo.utils");
        po.init("ti.sdo.utils.List.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("label", $$T_Str, $$UNDEF, "w");
                po.addFld("elems", new Proto.Arr(new Proto.Adr("xdc_Ptr", "Pv"), false), $$DEFAULT, "w");
        // struct List.Elem
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.List$$Elem", "ti.sdo.utils");
        po.init("ti.sdo.utils.List.Elem", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("next", new Proto.Adr("ti_sdo_utils_List_Elem*", "PS"), $$UNDEF, "w");
                po.addFld("prev", new Proto.Adr("ti_sdo_utils_List_Elem*", "PS"), $$UNDEF, "w");
        // struct List.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.List$$Instance_State", "ti.sdo.utils");
        po.init("ti.sdo.utils.List.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("elem", (Proto)om.findStrict("ti.sdo.utils.List.Elem", "ti.sdo.utils"), $$DEFAULT, "w");
    }

    void NameServer_SetupProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Module", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer_SetupProxy.Module", om.findStrict("ti.sdo.utils.INameServerRemote.Module", "ti.sdo.utils"));
                po.addFld("delegate$", (Proto)om.findStrict("ti.sdo.utils.INameServerRemote.Module", "ti.sdo.utils"), null, "wh");
                po.addFld("abstractInstances$", $$T_Bool, false, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.utils.NameServer_SetupProxy$$create", "ti.sdo.utils"), Global.get("ti$sdo$utils$NameServer_SetupProxy$$create"));
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Instance", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer_SetupProxy.Instance", om.findStrict("ti.sdo.utils.INameServerRemote.Instance", "ti.sdo.utils"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.utils"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer_SetupProxy$$Params", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer_SetupProxy.Params", om.findStrict("ti.sdo.utils.INameServerRemote$$Params", "ti.sdo.utils"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.utils"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer_SetupProxy$$Object", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer_SetupProxy.Object", om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Instance", "ti.sdo.utils"));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer_SetupProxy$$Instance_State", "ti.sdo.utils");
        po.init("ti.sdo.utils.NameServer_SetupProxy.Instance_State", null);
        po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void Build$$ROV()
    {
    }

    void NameServer$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.NameServer", "ti.sdo.utils");
        vo.bind("TableEntry$fetchDesc", Global.newObject("type", "ti.sdo.utils.NameServer.TableEntry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer$$TableEntry", "ti.sdo.utils");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.utils.NameServer.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer$$Instance_State", "ti.sdo.utils");
        po.bind("table$fetchDesc", Global.newObject("type", "ti.sdo.utils.NameServer.TableEntry", "isScalar", false));
        po.bind("names$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Char", "isScalar", true));
        po.bind("values$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_UInt8", "isScalar", true));
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.utils.NameServer.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer$$Module_State", "ti.sdo.utils");
    }

    void INameServerRemote$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.INameServerRemote", "ti.sdo.utils");
    }

    void NameServerRemoteNull$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.NameServerRemoteNull", "ti.sdo.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServerRemoteNull$$Instance_State", "ti.sdo.utils");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.utils.NameServerRemoteNull.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServerRemoteNull$$Instance_State", "ti.sdo.utils");
    }

    void MultiProc$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.MultiProc", "ti.sdo.utils");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.utils.MultiProc.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.MultiProc$$Module_State", "ti.sdo.utils");
        po.bind("clusterProcList$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_UInt16", "isScalar", true));
    }

    void List$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.List", "ti.sdo.utils");
        vo.bind("Elem$fetchDesc", Global.newObject("type", "ti.sdo.utils.List.Elem", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.List$$Elem", "ti.sdo.utils");
        po.bind("next$fetchDesc", Global.newObject("type", "ti.sdo.utils.List.Elem", "isScalar", false));
        po.bind("prev$fetchDesc", Global.newObject("type", "ti.sdo.utils.List.Elem", "isScalar", false));
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.utils.List.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.List$$Instance_State", "ti.sdo.utils");
    }

    void NameServer_SetupProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.NameServer_SetupProxy", "ti.sdo.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer_SetupProxy$$Instance_State", "ti.sdo.utils");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.utils.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.utils"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/utils/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.utils"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.utils"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.utils"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.utils"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.utils"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.utils"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.utils", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.utils");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.utils.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.utils'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.utils$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.utils$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.utils$$stat$root'];\n");
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

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.Build", "ti.sdo.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.Build.Module", "ti.sdo.utils");
        vo.init2(po, "ti.sdo.utils.Build", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.utils.Build$$capsule", "ti.sdo.utils"));
        vo.bind("$package", om.findStrict("ti.sdo.utils", "ti.sdo.utils"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.utils")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.utils.Build$$instance$static$init", null) ? 1 : 0);
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

    void NameServer$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.NameServer", "ti.sdo.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer.Module", "ti.sdo.utils");
        vo.init2(po, "ti.sdo.utils.NameServer", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.utils.NameServer$$capsule", "ti.sdo.utils"));
        vo.bind("Instance", om.findStrict("ti.sdo.utils.NameServer.Instance", "ti.sdo.utils"));
        vo.bind("Params", om.findStrict("ti.sdo.utils.NameServer.Params", "ti.sdo.utils"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.utils.NameServer.Params", "ti.sdo.utils")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.utils.NameServer.Handle", "ti.sdo.utils"));
        vo.bind("$package", om.findStrict("ti.sdo.utils", "ti.sdo.utils"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.utils.NameServer.BasicView", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.NameServer.BasicView", "ti.sdo.utils"));
        vo.bind("NamesListView", om.findStrict("ti.sdo.utils.NameServer.NamesListView", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.NameServer.NamesListView", "ti.sdo.utils"));
        mcfgs.add("A_invalidLen");
        mcfgs.add("A_invArgument");
        mcfgs.add("E_maxReached");
        mcfgs.add("E_entryExists");
        mcfgs.add("E_paramMismatch");
        vo.bind("Entry", om.findStrict("ti.sdo.utils.NameServer.Entry", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.NameServer.Entry", "ti.sdo.utils"));
        vo.bind("SetupProxy$proxy", om.findStrict("ti.sdo.utils.NameServer_SetupProxy", "ti.sdo.utils"));
        proxies.add("SetupProxy");
        mcfgs.add("singleProcessor");
        icfgs.add("singleProcessor");
        vo.bind("EntryMap", om.findStrict("ti.sdo.utils.NameServer.EntryMap", "ti.sdo.utils"));
        vo.bind("TableEntry", om.findStrict("ti.sdo.utils.NameServer.TableEntry", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.NameServer.TableEntry", "ti.sdo.utils"));
        icfgs.add("metaModTable");
        vo.bind("Instance_State", om.findStrict("ti.sdo.utils.NameServer.Instance_State", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.NameServer.Instance_State", "ti.sdo.utils"));
        vo.bind("Module_State", om.findStrict("ti.sdo.utils.NameServer.Module_State", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.NameServer.Module_State", "ti.sdo.utils"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.utils")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.utils.NameServer$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$utils$NameServer$$__initObject"));
        }//isCFG
        vo.bind("isRegistered", om.findStrict("ti.sdo.utils.NameServer.isRegistered", "ti.sdo.utils"));
        vo.bind("registerRemoteDriver", om.findStrict("ti.sdo.utils.NameServer.registerRemoteDriver", "ti.sdo.utils"));
        vo.bind("unregisterRemoteDriver", om.findStrict("ti.sdo.utils.NameServer.unregisterRemoteDriver", "ti.sdo.utils"));
        vo.bind("postInit", om.findStrict("ti.sdo.utils.NameServer.postInit", "ti.sdo.utils"));
        vo.bind("findLocal", om.findStrict("ti.sdo.utils.NameServer.findLocal", "ti.sdo.utils"));
        vo.bind("removeLocal", om.findStrict("ti.sdo.utils.NameServer.removeLocal", "ti.sdo.utils"));
        vo.bind("editLocal", om.findStrict("ti.sdo.utils.NameServer.editLocal", "ti.sdo.utils"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_utils_NameServer_Handle__label__E", "ti_sdo_utils_NameServer_Module__startupDone__E", "ti_sdo_utils_NameServer_Object__create__E", "ti_sdo_utils_NameServer_Object__delete__E", "ti_sdo_utils_NameServer_Object__destruct__E", "ti_sdo_utils_NameServer_Object__get__E", "ti_sdo_utils_NameServer_Object__first__E", "ti_sdo_utils_NameServer_Object__next__E", "ti_sdo_utils_NameServer_Params__init__E", "ti_sdo_utils_NameServer_isRegistered__E", "ti_sdo_utils_NameServer_registerRemoteDriver__E", "ti_sdo_utils_NameServer_unregisterRemoteDriver__E", "ti_sdo_utils_NameServer_getKey__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_maxReached", "E_entryExists", "E_paramMismatch"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_invalidLen", "A_invArgument"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.utils.NameServer.Object", "ti.sdo.utils"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NameServer", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NameServer");
    }

    void INameServerRemote$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.INameServerRemote", "ti.sdo.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.INameServerRemote.Module", "ti.sdo.utils");
        vo.init2(po, "ti.sdo.utils.INameServerRemote", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.sdo.utils.INameServerRemote.Instance", "ti.sdo.utils"));
        vo.bind("Params", om.findStrict("ti.sdo.utils.INameServerRemote.Params", "ti.sdo.utils"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.utils.INameServerRemote.Params", "ti.sdo.utils")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.utils.INameServerRemote.Handle", "ti.sdo.utils"));
        vo.bind("$package", om.findStrict("ti.sdo.utils", "ti.sdo.utils"));
        tdefs.clear();
        proxies.clear();
        inherits.clear();
        vo.bind("Status", om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.utils"));
        vo.bind("S_SUCCESS", om.findStrict("ti.sdo.utils.INameServerRemote.S_SUCCESS", "ti.sdo.utils"));
        vo.bind("E_FAIL", om.findStrict("ti.sdo.utils.INameServerRemote.E_FAIL", "ti.sdo.utils"));
        vo.bind("E_ERROR", om.findStrict("ti.sdo.utils.INameServerRemote.E_ERROR", "ti.sdo.utils"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("INameServerRemote", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("INameServerRemote");
        vo.seal(null);
        if (vo.getProto().lookupFld("$used") != null) {
            vo.unseal("$used");
        }
    }

    void NameServerRemoteNull$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.NameServerRemoteNull", "ti.sdo.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServerRemoteNull.Module", "ti.sdo.utils");
        vo.init2(po, "ti.sdo.utils.NameServerRemoteNull", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.utils.NameServerRemoteNull$$capsule", "ti.sdo.utils"));
        vo.bind("Instance", om.findStrict("ti.sdo.utils.NameServerRemoteNull.Instance", "ti.sdo.utils"));
        vo.bind("Params", om.findStrict("ti.sdo.utils.NameServerRemoteNull.Params", "ti.sdo.utils"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.utils.NameServerRemoteNull.Params", "ti.sdo.utils")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.utils.NameServerRemoteNull.Handle", "ti.sdo.utils"));
        vo.bind("$package", om.findStrict("ti.sdo.utils", "ti.sdo.utils"));
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
        vo.bind("Status", om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.utils"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.utils.NameServerRemoteNull.Instance_State", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.NameServerRemoteNull.Instance_State", "ti.sdo.utils"));
        vo.bind("S_SUCCESS", om.findStrict("ti.sdo.utils.INameServerRemote.S_SUCCESS", "ti.sdo.utils"));
        vo.bind("E_FAIL", om.findStrict("ti.sdo.utils.INameServerRemote.E_FAIL", "ti.sdo.utils"));
        vo.bind("E_ERROR", om.findStrict("ti.sdo.utils.INameServerRemote.E_ERROR", "ti.sdo.utils"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.utils");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.utils")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.utils.NameServerRemoteNull$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$utils$NameServerRemoteNull$$__initObject"));
        }//isCFG
        vo.bind("attach", om.findStrict("ti.sdo.utils.NameServerRemoteNull.attach", "ti.sdo.utils"));
        vo.bind("detach", om.findStrict("ti.sdo.utils.NameServerRemoteNull.detach", "ti.sdo.utils"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.utils.NameServerRemoteNull.sharedMemReq", "ti.sdo.utils"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_utils_NameServerRemoteNull_Handle__label__E", "ti_sdo_utils_NameServerRemoteNull_Module__startupDone__E", "ti_sdo_utils_NameServerRemoteNull_Object__create__E", "ti_sdo_utils_NameServerRemoteNull_Object__delete__E", "ti_sdo_utils_NameServerRemoteNull_Object__destruct__E", "ti_sdo_utils_NameServerRemoteNull_Object__get__E", "ti_sdo_utils_NameServerRemoteNull_Object__first__E", "ti_sdo_utils_NameServerRemoteNull_Object__next__E", "ti_sdo_utils_NameServerRemoteNull_Params__init__E", "ti_sdo_utils_NameServerRemoteNull_attach__E", "ti_sdo_utils_NameServerRemoteNull_detach__E", "ti_sdo_utils_NameServerRemoteNull_sharedMemReq__E", "ti_sdo_utils_NameServerRemoteNull_get__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.utils.NameServerRemoteNull.Object", "ti.sdo.utils"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "get", "entry", "%p, \"%s\", \"%s\", %p, %p, %p, %p", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NameServerRemoteNull", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NameServerRemoteNull");
    }

    void MultiProc$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.MultiProc", "ti.sdo.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.MultiProc.Module", "ti.sdo.utils");
        vo.init2(po, "ti.sdo.utils.MultiProc", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.utils.MultiProc$$capsule", "ti.sdo.utils"));
        vo.bind("$package", om.findStrict("ti.sdo.utils", "ti.sdo.utils"));
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
        vo.bind("ModuleView", om.findStrict("ti.sdo.utils.MultiProc.ModuleView", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.MultiProc.ModuleView", "ti.sdo.utils"));
        mcfgs.add("A_invalidMultiProcId");
        mcfgs.add("A_invalidProcName");
        mcfgs.add("nameList");
        mcfgs.add("numProcsInCluster");
        mcfgs.add("numProcessors");
        vo.bind("ProcAddrMode", om.findStrict("ti.sdo.utils.MultiProc.ProcAddrMode", "ti.sdo.utils"));
        mcfgs.add("procAddrMode");
        vo.bind("Module_State", om.findStrict("ti.sdo.utils.MultiProc.Module_State", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.MultiProc.Module_State", "ti.sdo.utils"));
        vo.bind("ProcAddrMode_Global", om.findStrict("ti.sdo.utils.MultiProc.ProcAddrMode_Global", "ti.sdo.utils"));
        vo.bind("ProcAddrMode_Cluster", om.findStrict("ti.sdo.utils.MultiProc.ProcAddrMode_Cluster", "ti.sdo.utils"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.utils")).add(vo);
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
        vo.bind("getClusterId", om.findStrict("ti.sdo.utils.MultiProc.getClusterId", "ti.sdo.utils"));
        vo.bind("dummy", om.findStrict("ti.sdo.utils.MultiProc.dummy", "ti.sdo.utils"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_utils_MultiProc_Module__startupDone__E", "ti_sdo_utils_MultiProc_getClusterId__E", "ti_sdo_utils_MultiProc_dummy__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_invalidMultiProcId", "A_invalidProcName"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "getClusterId", "entry", "0x%x", "exit", "0x%x"));
        loggables.add(Global.newObject("name", "dummy", "entry", "", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("MultiProc", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("MultiProc");
    }

    void List$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.List", "ti.sdo.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.List.Module", "ti.sdo.utils");
        vo.init2(po, "ti.sdo.utils.List", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.utils.List$$capsule", "ti.sdo.utils"));
        vo.bind("Instance", om.findStrict("ti.sdo.utils.List.Instance", "ti.sdo.utils"));
        vo.bind("Params", om.findStrict("ti.sdo.utils.List.Params", "ti.sdo.utils"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.utils.List.Params", "ti.sdo.utils")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.utils.List.Handle", "ti.sdo.utils"));
        vo.bind("$package", om.findStrict("ti.sdo.utils", "ti.sdo.utils"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.utils.List.BasicView", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.List.BasicView", "ti.sdo.utils"));
        vo.bind("Elem", om.findStrict("ti.sdo.utils.List.Elem", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.List.Elem", "ti.sdo.utils"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.utils.List.Instance_State", "ti.sdo.utils"));
        tdefs.add(om.findStrict("ti.sdo.utils.List.Instance_State", "ti.sdo.utils"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.utils")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.utils.List$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$utils$List$$__initObject"));
        }//isCFG
        vo.bind("elemClear", om.findStrict("ti.sdo.utils.List.elemClear", "ti.sdo.utils"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_utils_List_Handle__label__E", "ti_sdo_utils_List_Module__startupDone__E", "ti_sdo_utils_List_Object__create__E", "ti_sdo_utils_List_Object__delete__E", "ti_sdo_utils_List_Object__destruct__E", "ti_sdo_utils_List_Object__get__E", "ti_sdo_utils_List_Object__first__E", "ti_sdo_utils_List_Object__next__E", "ti_sdo_utils_List_Params__init__E", "ti_sdo_utils_List_elemClear__E", "ti_sdo_utils_List_empty__E", "ti_sdo_utils_List_get__E", "ti_sdo_utils_List_put__E", "ti_sdo_utils_List_putHead__E", "ti_sdo_utils_List_next__E", "ti_sdo_utils_List_prev__E", "ti_sdo_utils_List_insert__E", "ti_sdo_utils_List_remove__E", "ti_sdo_utils_List_dequeue__E", "ti_sdo_utils_List_enqueue__E", "ti_sdo_utils_List_enqueueHead__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.utils.List.Object", "ti.sdo.utils"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("List", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("List");
    }

    void NameServer_SetupProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.utils.NameServer_SetupProxy", "ti.sdo.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Module", "ti.sdo.utils");
        vo.init2(po, "ti.sdo.utils.NameServer_SetupProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Instance", "ti.sdo.utils"));
        vo.bind("Params", om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Params", "ti.sdo.utils"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Params", "ti.sdo.utils")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Handle", "ti.sdo.utils"));
        vo.bind("$package", om.findStrict("ti.sdo.utils", "ti.sdo.utils"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        inherits.clear();
        vo.bind("Status", om.findStrict("ti.sdo.utils.INameServerRemote.Status", "ti.sdo.utils"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.utils");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.utils")).add(vo);
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
            vo.bind("__initObject", Global.get("ti$sdo$utils$NameServer_SetupProxy$$__initObject"));
        }//isCFG
        vo.bind("attach", om.findStrict("ti.sdo.utils.NameServer_SetupProxy.attach", "ti.sdo.utils"));
        vo.bind("detach", om.findStrict("ti.sdo.utils.NameServer_SetupProxy.detach", "ti.sdo.utils"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.utils.NameServer_SetupProxy.sharedMemReq", "ti.sdo.utils"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_utils_NameServer_SetupProxy_DELEGATE__Handle__label", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__Module__startupDone", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__Object__create", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__Object__delete", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__Object__destruct", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__Object__get", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__Object__first", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__Object__next", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__Params__init", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__Proxy__abstract", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__Proxy__delegate", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__attach", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__detach", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__sharedMemReq", "ti_sdo_utils_NameServer_SetupProxy_DELEGATE__get"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Object", "ti.sdo.utils"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.utils.NameServer_SetupProxy.Instance_State", "ti.sdo.utils"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        loggables.add(Global.newObject("name", "get", "entry", "%p, \"%s\", \"%s\", %p, %p, %p, %p", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NameServer_SetupProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NameServer_SetupProxy");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sdo.utils")).findStrict("PARAMS", "ti.sdo.utils");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.utils.NameServer", "ti.sdo.utils")).findStrict("PARAMS", "ti.sdo.utils");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.utils.NameServerRemoteNull", "ti.sdo.utils")).findStrict("PARAMS", "ti.sdo.utils");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.utils.List", "ti.sdo.utils")).findStrict("PARAMS", "ti.sdo.utils");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.utils.NameServer_SetupProxy", "ti.sdo.utils")).findStrict("PARAMS", "ti.sdo.utils");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.utils.Build", "ti.sdo.utils"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.utils.NameServer", "ti.sdo.utils"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.utils.NameServerRemoteNull", "ti.sdo.utils"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.utils.MultiProc", "ti.sdo.utils"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.utils.List", "ti.sdo.utils"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.utils.NameServer_SetupProxy", "ti.sdo.utils"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.utils.NameServer", "ti.sdo.utils");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"NamesValues", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE_DATA"), "viewInitFxn", "viewInitData", "structName", "NamesListView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.utils.MultiProc", "ti.sdo.utils");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Module", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE"), "viewInitFxn", "viewInitModule", "structName", "ModuleView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.utils.List", "ti.sdo.utils");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitInstance", "structName", "BasicView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.utils.Build")).bless();
        ((Value.Obj)om.getv("ti.sdo.utils.NameServer")).bless();
        ((Value.Obj)om.getv("ti.sdo.utils.INameServerRemote")).bless();
        ((Value.Obj)om.getv("ti.sdo.utils.NameServerRemoteNull")).bless();
        ((Value.Obj)om.getv("ti.sdo.utils.MultiProc")).bless();
        ((Value.Obj)om.getv("ti.sdo.utils.List")).bless();
        ((Value.Obj)om.getv("ti.sdo.utils.NameServer_SetupProxy")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.utils")).add(pkgV);
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
        NameServer$$OBJECTS();
        INameServerRemote$$OBJECTS();
        NameServerRemoteNull$$OBJECTS();
        MultiProc$$OBJECTS();
        List$$OBJECTS();
        NameServer_SetupProxy$$OBJECTS();
        Build$$CONSTS();
        NameServer$$CONSTS();
        INameServerRemote$$CONSTS();
        NameServerRemoteNull$$CONSTS();
        MultiProc$$CONSTS();
        List$$CONSTS();
        NameServer_SetupProxy$$CONSTS();
        Build$$CREATES();
        NameServer$$CREATES();
        INameServerRemote$$CREATES();
        NameServerRemoteNull$$CREATES();
        MultiProc$$CREATES();
        List$$CREATES();
        NameServer_SetupProxy$$CREATES();
        Build$$FUNCTIONS();
        NameServer$$FUNCTIONS();
        INameServerRemote$$FUNCTIONS();
        NameServerRemoteNull$$FUNCTIONS();
        MultiProc$$FUNCTIONS();
        List$$FUNCTIONS();
        NameServer_SetupProxy$$FUNCTIONS();
        Build$$SIZES();
        NameServer$$SIZES();
        INameServerRemote$$SIZES();
        NameServerRemoteNull$$SIZES();
        MultiProc$$SIZES();
        List$$SIZES();
        NameServer_SetupProxy$$SIZES();
        Build$$TYPES();
        NameServer$$TYPES();
        INameServerRemote$$TYPES();
        NameServerRemoteNull$$TYPES();
        MultiProc$$TYPES();
        List$$TYPES();
        NameServer_SetupProxy$$TYPES();
        if (isROV) {
            Build$$ROV();
            NameServer$$ROV();
            INameServerRemote$$ROV();
            NameServerRemoteNull$$ROV();
            MultiProc$$ROV();
            List$$ROV();
            NameServer_SetupProxy$$ROV();
        }//isROV
        $$SINGLETONS();
        Build$$SINGLETONS();
        NameServer$$SINGLETONS();
        INameServerRemote$$SINGLETONS();
        NameServerRemoteNull$$SINGLETONS();
        MultiProc$$SINGLETONS();
        List$$SINGLETONS();
        NameServer_SetupProxy$$SINGLETONS();
        $$INITIALIZATION();
    }
}
