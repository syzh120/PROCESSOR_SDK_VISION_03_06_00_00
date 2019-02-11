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

public class ti_sdo_ipc_heaps
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
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.heaps", new Value.Obj("ti.sdo.ipc.heaps", pkgP));
    }

    void HeapBufMP$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapBufMP.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.heaps.HeapBufMP", new Value.Obj("ti.sdo.ipc.heaps.HeapBufMP", po));
        pkgV.bind("HeapBufMP", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapBufMP$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapBufMP.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapBufMP$$Attrs", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapBufMP.Attrs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapBufMP$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapBufMP.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapBufMP$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapBufMP.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.heaps.HeapBufMP.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapBufMP$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapBufMP.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapBufMP$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapBufMP.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.heaps.HeapBufMP.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.heaps.HeapBufMP.Object", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Instance_State", "ti.sdo.ipc.heaps"));
        }//isROV
    }

    void HeapMultiBufMP$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP", new Value.Obj("ti.sdo.ipc.heaps.HeapMultiBufMP", po));
        pkgV.bind("HeapMultiBufMP", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$BucketsView", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.BucketsView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$Bucket", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$ExtendedStats", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.ExtendedStats", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$Elem", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.Elem", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$BucketAttrs", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.BucketAttrs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$Attrs", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.Attrs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.Object", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance_State", "ti.sdo.ipc.heaps"));
        }//isROV
    }

    void HeapMemMP$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP", new Value.Obj("ti.sdo.ipc.heaps.HeapMemMP", po));
        pkgV.bind("HeapMemMP", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$DetailedView", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.DetailedView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$FreeBlockView", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.FreeBlockView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$ExtendedStats", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.ExtendedStats", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$Header", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.Header", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$Attrs", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.Attrs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.heaps.HeapMemMP.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.heaps.HeapMemMP.Object", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Instance_State", "ti.sdo.ipc.heaps"));
        }//isROV
    }

    void HeapBufMP$$CONSTS()
    {
        // module HeapBufMP
        om.bind("ti.sdo.ipc.heaps.HeapBufMP.CREATED", 0x05251995L);
        om.bind("ti.sdo.ipc.heaps.HeapBufMP.postInit", new Extern("ti_sdo_ipc_heaps_HeapBufMP_postInit__I", "xdc_Void(*)(ti_sdo_ipc_heaps_HeapBufMP_Object*,xdc_runtime_Error_Block*)", true, false));
    }

    void HeapMultiBufMP$$CONSTS()
    {
        // module HeapMultiBufMP
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.CREATED", 0x05101920L);
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.postInit", new Extern("ti_sdo_ipc_heaps_HeapMultiBufMP_postInit__I", "xdc_Void(*)(ti_sdo_ipc_heaps_HeapMultiBufMP_Object*,xdc_runtime_Error_Block*)", true, false));
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.processBuckets", new Extern("ti_sdo_ipc_heaps_HeapMultiBufMP_processBuckets__I", "xdc_UInt(*)(ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket*,ti_sdo_ipc_heaps_HeapMultiBufMP_Params*,xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.putTail", new Extern("ti_sdo_ipc_heaps_HeapMultiBufMP_putTail__I", "xdc_Void(*)(ti_sdo_ipc_heaps_HeapMultiBufMP_Object*,xdc_Int,ti_sdo_ipc_heaps_HeapMultiBufMP_Elem*)", true, false));
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP.getHead", new Extern("ti_sdo_ipc_heaps_HeapMultiBufMP_getHead__I", "ti_sdo_ipc_heaps_HeapMultiBufMP_Elem*(*)(ti_sdo_ipc_heaps_HeapMultiBufMP_Object*,xdc_Int)", true, false));
    }

    void HeapMemMP$$CONSTS()
    {
        // module HeapMemMP
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.CREATED", 0x07041776L);
        om.bind("ti.sdo.ipc.heaps.HeapMemMP.postInit", new Extern("ti_sdo_ipc_heaps_HeapMemMP_postInit__I", "xdc_Void(*)(ti_sdo_ipc_heaps_HeapMemMP_Object*,xdc_runtime_Error_Block*)", true, false));
    }

    void HeapBufMP$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$heaps$HeapBufMP$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.heaps.HeapBufMP.create() called before xdc.useModule('ti.sdo.ipc.heaps.HeapBufMP')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.heaps.HeapBufMP$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Module", "ti.sdo.ipc.heaps"), om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Instance", "ti.sdo.ipc.heaps"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Params", "ti.sdo.ipc.heaps"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$heaps$HeapBufMP$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.heaps.HeapBufMP'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.heaps.HeapBufMP.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.heaps']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.heaps.HeapBufMP'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.heaps.HeapBufMP'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.heaps.HeapBufMP$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Module", "ti.sdo.ipc.heaps"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$Object", "ti.sdo.ipc.heaps"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Params", "ti.sdo.ipc.heaps"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$heaps$HeapBufMP$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.heaps.HeapBufMP'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.heaps.HeapBufMP'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.heaps.HeapBufMP'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void HeapMultiBufMP$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$heaps$HeapMultiBufMP$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.heaps.HeapMultiBufMP.create() called before xdc.useModule('ti.sdo.ipc.heaps.HeapMultiBufMP')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Module", "ti.sdo.ipc.heaps"), om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance", "ti.sdo.ipc.heaps"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Params", "ti.sdo.ipc.heaps"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$heaps$HeapMultiBufMP$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.heaps']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP'].Instance_State);\n");
                sb.append("__inst.bucketEntries = __mod.PARAMS.bucketEntries;\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Module", "ti.sdo.ipc.heaps"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Object", "ti.sdo.ipc.heaps"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Params", "ti.sdo.ipc.heaps"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$heaps$HeapMultiBufMP$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("__inst.bucketEntries = __mod.PARAMS.bucketEntries;\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void HeapMemMP$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$heaps$HeapMemMP$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.heaps.HeapMemMP.create() called before xdc.useModule('ti.sdo.ipc.heaps.HeapMemMP')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Module", "ti.sdo.ipc.heaps"), om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Instance", "ti.sdo.ipc.heaps"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Params", "ti.sdo.ipc.heaps"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$heaps$HeapMemMP$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.heaps.HeapMemMP'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.heaps']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.heaps.HeapMemMP'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.heaps.HeapMemMP'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.heaps.HeapMemMP$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Module", "ti.sdo.ipc.heaps"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Object", "ti.sdo.ipc.heaps"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Params", "ti.sdo.ipc.heaps"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$heaps$HeapMemMP$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.heaps.HeapMemMP'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.heaps.HeapMemMP'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.heaps.HeapMemMP'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void HeapBufMP$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void HeapMultiBufMP$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void HeapMemMP$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void HeapBufMP$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Attrs", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("status", "UInt32"));
        sizes.add(Global.newArray("gateMPAddr", "UInt32"));
        sizes.add(Global.newArray("bufPtr", "UInt32"));
        sizes.add(Global.newArray("numFreeBlocks", "UInt32"));
        sizes.add(Global.newArray("minFreeBlocks", "UInt32"));
        sizes.add(Global.newArray("blockSize", "UInt32"));
        sizes.add(Global.newArray("align", "UInt32"));
        sizes.add(Global.newArray("numBlocks", "UInt32"));
        sizes.add(Global.newArray("exact", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapBufMP.Attrs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapBufMP.Attrs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapBufMP.Attrs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Instance_State", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("attrs", "UPtr"));
        sizes.add(Global.newArray("gate", "UPtr"));
        sizes.add(Global.newArray("objType", "Nti.sdo.ipc.Ipc.ObjType;;0x1;0x2;0x4;0x8;0x10;0x20"));
        sizes.add(Global.newArray("nsKey", "UPtr"));
        sizes.add(Global.newArray("cacheEnabled", "UShort"));
        sizes.add(Global.newArray("regionId", "UInt16"));
        sizes.add(Global.newArray("allocSize", "USize"));
        sizes.add(Global.newArray("buf", "UPtr"));
        sizes.add(Global.newArray("freeList", "UPtr"));
        sizes.add(Global.newArray("blockSize", "USize"));
        sizes.add(Global.newArray("align", "USize"));
        sizes.add(Global.newArray("numBlocks", "UInt"));
        sizes.add(Global.newArray("exact", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapBufMP.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapBufMP.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapBufMP.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Module_State", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("nameServer", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapBufMP.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapBufMP.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapBufMP.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void HeapMultiBufMP$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("blockSize", "USize"));
        sizes.add(Global.newArray("numBlocks", "UInt"));
        sizes.add(Global.newArray("align", "USize"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.ExtendedStats", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("numBuckets", "UInt"));
        sizes.add(Global.newArray("numBlocks", "A8;UInt"));
        sizes.add(Global.newArray("blockSize", "A8;UInt"));
        sizes.add(Global.newArray("align", "A8;UInt"));
        sizes.add(Global.newArray("maxAllocatedBlocks", "A8;UInt"));
        sizes.add(Global.newArray("numAllocatedBlocks", "A8;UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.ExtendedStats']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.ExtendedStats']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.ExtendedStats'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Elem", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("next", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Elem']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Elem']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Elem'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.BucketAttrs", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("head", "UInt32"));
        sizes.add(Global.newArray("tail", "UInt32"));
        sizes.add(Global.newArray("baseAddr", "UInt32"));
        sizes.add(Global.newArray("numFreeBlocks", "UInt32"));
        sizes.add(Global.newArray("minFreeBlocks", "UInt32"));
        sizes.add(Global.newArray("blockSize", "UInt32"));
        sizes.add(Global.newArray("align", "UInt32"));
        sizes.add(Global.newArray("numBlocks", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.BucketAttrs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.BucketAttrs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.BucketAttrs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Attrs", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("status", "UInt32"));
        sizes.add(Global.newArray("gateMPAddr", "UInt32"));
        sizes.add(Global.newArray("numBuckets", "UInt32"));
        sizes.add(Global.newArray("buckets", "A8;Sti.sdo.ipc.heaps.HeapMultiBufMP;BucketAttrs"));
        sizes.add(Global.newArray("exact", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Attrs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Attrs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Attrs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance_State", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("attrs", "UPtr"));
        sizes.add(Global.newArray("gate", "UPtr"));
        sizes.add(Global.newArray("objType", "Nti.sdo.ipc.Ipc.ObjType;;0x1;0x2;0x4;0x8;0x10;0x20"));
        sizes.add(Global.newArray("nsKey", "UPtr"));
        sizes.add(Global.newArray("cacheEnabled", "UShort"));
        sizes.add(Global.newArray("regionId", "UInt16"));
        sizes.add(Global.newArray("allocSize", "USize"));
        sizes.add(Global.newArray("buf", "UPtr"));
        sizes.add(Global.newArray("bucketEntries", "UPtr"));
        sizes.add(Global.newArray("numBuckets", "UInt"));
        sizes.add(Global.newArray("exact", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Module_State", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("nameServer", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMultiBufMP.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void HeapMemMP$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.ExtendedStats", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("buf", "UPtr"));
        sizes.add(Global.newArray("size", "USize"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.ExtendedStats']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.ExtendedStats']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.ExtendedStats'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Header", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("next", "UInt32"));
        sizes.add(Global.newArray("size", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Header']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Header']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Header'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Attrs", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("status", "UInt32"));
        sizes.add(Global.newArray("bufPtr", "UInt32"));
        sizes.add(Global.newArray("head", "Sti.sdo.ipc.heaps.HeapMemMP;Header"));
        sizes.add(Global.newArray("gateMPAddr", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Attrs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Attrs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Attrs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Instance_State", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("attrs", "UPtr"));
        sizes.add(Global.newArray("gate", "UPtr"));
        sizes.add(Global.newArray("objType", "Nti.sdo.ipc.Ipc.ObjType;;0x1;0x2;0x4;0x8;0x10;0x20"));
        sizes.add(Global.newArray("nsKey", "UPtr"));
        sizes.add(Global.newArray("cacheEnabled", "UShort"));
        sizes.add(Global.newArray("regionId", "UInt16"));
        sizes.add(Global.newArray("allocSize", "USize"));
        sizes.add(Global.newArray("buf", "UPtr"));
        sizes.add(Global.newArray("minAlign", "USize"));
        sizes.add(Global.newArray("bufSize", "USize"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Module_State", "ti.sdo.ipc.heaps");
        sizes.clear();
        sizes.add(Global.newArray("nameServer", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.heaps.HeapMemMP.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void HeapBufMP$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/heaps/HeapBufMP.xs");
        om.bind("ti.sdo.ipc.heaps.HeapBufMP$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Module", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapBufMP.Module", om.findStrict("xdc.runtime.IHeap.Module", "ti.sdo.ipc.heaps"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x05251995L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.heaps"), $$UNDEF, "wh");
            po.addFld("A_invBlockFreed", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "A_invBlockFreed: Invalid block being freed"), "w");
            po.addFld("A_badAlignment", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "A_badAlignment: Block being freed is not aligned properly "), "w");
            po.addFld("E_sizeTooLarge", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "E_sizeTooLarge: Requested alloc size of %u is greater than %u"), "w");
            po.addFld("E_alignTooLarge", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "E_alignTooLarge: Requested alignment size of %u is greater than %u"), "w");
            po.addFld("E_exactFail", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "E_exactFail: Exact allocation failed (requested size = %u and buffer size = %u)"), "w");
            po.addFld("E_noBlocksLeft", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "E_noBlocksLeft: No more blocks left in buffer (handle = 0x%x, requested size = %u)"), "w");
            po.addFld("maxRuntimeEntries", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "wh");
            po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "w");
            po.addFld("tableSection", $$T_Str, null, "wh");
            po.addFld("trackAllocs", $$T_Bool, false, "w");
            po.addFld("nameSrvPrms", (Proto)om.findStrict("ti.sdo.utils.NameServer.Params", "ti.sdo.ipc.heaps"), $$DEFAULT, "wh");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$create", "ti.sdo.ipc.heaps"), Global.get("ti$sdo$ipc$heaps$HeapBufMP$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$construct", "ti.sdo.ipc.heaps"), Global.get("ti$sdo$ipc$heaps$HeapBufMP$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapBufMP$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapBufMP$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapBufMP$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapBufMP$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapBufMP$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapBufMP$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Instance", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapBufMP.Instance", om.findStrict("xdc.runtime.IHeap.Instance", "ti.sdo.ipc.heaps"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x05251995L, "rh");
        if (isCFG) {
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.heaps"), null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("exact", $$T_Bool, false, "w");
            po.addFld("name", $$T_Str, null, "w");
            po.addFld("align", Proto.Elm.newCNum("(xdc_SizeT)"), 0L, "w");
            po.addFld("numBlocks", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("blockSize", Proto.Elm.newCNum("(xdc_SizeT)"), 0L, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$Params", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapBufMP.Params", om.findStrict("xdc.runtime.IHeap$$Params", "ti.sdo.ipc.heaps"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x05251995L, "rh");
        if (isCFG) {
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.heaps"), null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("exact", $$T_Bool, false, "w");
            po.addFld("name", $$T_Str, null, "w");
            po.addFld("align", Proto.Elm.newCNum("(xdc_SizeT)"), 0L, "w");
            po.addFld("numBlocks", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("blockSize", Proto.Elm.newCNum("(xdc_SizeT)"), 0L, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$Object", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapBufMP.Object", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Instance", "ti.sdo.ipc.heaps"));
        // struct HeapBufMP.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$BasicView", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapBufMP.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("buf", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("objType", $$T_Str, $$UNDEF, "w");
                po.addFld("gate", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("exact", $$T_Bool, $$UNDEF, "w");
                po.addFld("align", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("blockSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("numBlocks", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("curAllocated", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("maxAllocated", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("freeList", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct HeapBufMP.Attrs
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$Attrs", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapBufMP.Attrs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("status", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("gateMPAddr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("bufPtr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("numFreeBlocks", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("minFreeBlocks", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("blockSize", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("align", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("numBlocks", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("exact", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
        // struct HeapBufMP.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$Instance_State", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapBufMP.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("attrs", new Proto.Adr("ti_sdo_ipc_heaps_HeapBufMP_Attrs*", "PS"), $$UNDEF, "w");
                po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
                po.addFld("objType", (Proto)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
                po.addFld("nsKey", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("allocSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("buf", new Proto.Adr("xdc_Char*", "Pn"), $$UNDEF, "w");
                po.addFld("freeList", (Proto)om.findStrict("ti.sdo.ipc.ListMP.Handle", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
                po.addFld("blockSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("align", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("numBlocks", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("exact", $$T_Bool, $$UNDEF, "w");
        // struct HeapBufMP.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$Module_State", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapBufMP.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("nameServer", (Proto)om.findStrict("ti.sdo.utils.NameServer.Handle", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
    }

    void HeapMultiBufMP$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/heaps/HeapMultiBufMP.xs");
        om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Module", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.Module", om.findStrict("xdc.runtime.IHeap.Module", "ti.sdo.ipc.heaps"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x05101920L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.heaps"), $$UNDEF, "wh");
            po.addFld("A_invalidAlign", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "align parameter must be a power of 2"), "w");
            po.addFld("A_sizeNotFound", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "an invalid buffer size was passed to free"), "w");
            po.addFld("A_addrNotFound", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "an invalid buffer address was passed to free"), "w");
            po.addFld("E_exactFail", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "E_exactFail: Exact allocation failed (requested size = %u and buffer size = %u)"), "w");
            po.addFld("E_size", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "E_size: requested size/alignment is too big (requested size = %u and requested align = %u)"), "w");
            po.addFld("E_noBlocksLeft", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "E_noBlocksLeft: No more blocks left in buffer (buffer size = %u and buffer align = %u)"), "w");
            po.addFld("maxRuntimeEntries", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "wh");
            po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "w");
            po.addFld("tableSection", $$T_Str, null, "wh");
            po.addFld("trackMaxAllocs", $$T_Bool, false, "w");
            po.addFld("nameSrvPrms", (Proto)om.findStrict("ti.sdo.utils.NameServer.Params", "ti.sdo.ipc.heaps"), $$DEFAULT, "wh");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$create", "ti.sdo.ipc.heaps"), Global.get("ti$sdo$ipc$heaps$HeapMultiBufMP$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$construct", "ti.sdo.ipc.heaps"), Global.get("ti$sdo$ipc$heaps$HeapMultiBufMP$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMultiBufMP$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance", om.findStrict("xdc.runtime.IHeap.Instance", "ti.sdo.ipc.heaps"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x05101920L, "rh");
        if (isCFG) {
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.heaps"), null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("exact", $$T_Bool, false, "w");
            po.addFld("name", $$T_Str, null, "w");
            po.addFld("numBuckets", Proto.Elm.newCNum("(xdc_Int)"), 0L, "w");
            po.addFld("bucketEntries", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket", "ti.sdo.ipc.heaps"), false), $$DEFAULT, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Params", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.Params", om.findStrict("xdc.runtime.IHeap$$Params", "ti.sdo.ipc.heaps"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x05101920L, "rh");
        if (isCFG) {
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.heaps"), null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("exact", $$T_Bool, false, "w");
            po.addFld("name", $$T_Str, null, "w");
            po.addFld("numBuckets", Proto.Elm.newCNum("(xdc_Int)"), 0L, "w");
            po.addFld("bucketEntries", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket", "ti.sdo.ipc.heaps"), false), $$DEFAULT, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Object", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.Object", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance", "ti.sdo.ipc.heaps"));
        // struct HeapMultiBufMP.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$BasicView", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("buf", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("totalSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("objType", $$T_Str, $$UNDEF, "w");
                po.addFld("gate", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("exact", $$T_Bool, $$UNDEF, "w");
        // struct HeapMultiBufMP.BucketsView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$BucketsView", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.BucketsView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("baseAddr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("blockSize", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("align", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numBlocks", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numFreeBlocks", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("minFreeBlocks", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        // struct HeapMultiBufMP.Bucket
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Bucket", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("blockSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("numBlocks", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("align", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
        // struct HeapMultiBufMP.ExtendedStats
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$ExtendedStats", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.ExtendedStats", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("numBuckets", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numBlocks", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("blockSize", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("align", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("maxAllocatedBlocks", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("numAllocatedBlocks", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
        // struct HeapMultiBufMP.Elem
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Elem", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.Elem", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("next", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct HeapMultiBufMP.BucketAttrs
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$BucketAttrs", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.BucketAttrs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("head", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("tail", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("baseAddr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("numFreeBlocks", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("minFreeBlocks", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("blockSize", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("align", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("numBlocks", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct HeapMultiBufMP.Attrs
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Attrs", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.Attrs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("status", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("gateMPAddr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("numBuckets", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("buckets", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.BucketAttrs", "ti.sdo.ipc.heaps"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("exact", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
        // struct HeapMultiBufMP.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Instance_State", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("attrs", new Proto.Adr("ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs*", "PS"), $$UNDEF, "w");
                po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
                po.addFld("objType", (Proto)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
                po.addFld("nsKey", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("allocSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("buf", new Proto.Adr("xdc_Char*", "Pn"), $$UNDEF, "w");
                po.addFld("bucketEntries", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket", "ti.sdo.ipc.heaps"), false), $$DEFAULT, "w");
                po.addFld("numBuckets", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("exact", $$T_Bool, $$UNDEF, "w");
        // struct HeapMultiBufMP.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Module_State", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMultiBufMP.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("nameServer", (Proto)om.findStrict("ti.sdo.utils.NameServer.Handle", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
    }

    void HeapMemMP$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/heaps/HeapMemMP.xs");
        om.bind("ti.sdo.ipc.heaps.HeapMemMP$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Module", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.Module", om.findStrict("xdc.runtime.IHeap.Module", "ti.sdo.ipc.heaps"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x07041776L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.heaps"), $$UNDEF, "wh");
            po.addFld("A_zeroBlock", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "A_zeroBlock: Cannot allocate size 0"), "w");
            po.addFld("A_heapSize", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "A_heapSize: Requested heap size is too small"), "w");
            po.addFld("A_align", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "A_align: Requested align is not a power of 2"), "w");
            po.addFld("A_invalidFree", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "A_invalidFree: Invalid free"), "w");
            po.addFld("E_memory", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.heaps"), Global.newObject("msg", "E_memory: Out of memory: handle=0x%x, size=%u"), "w");
            po.addFld("maxRuntimeEntries", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "wh");
            po.addFld("maxNameLen", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "w");
            po.addFld("tableSection", $$T_Str, null, "wh");
            po.addFld("nameSrvPrms", (Proto)om.findStrict("ti.sdo.utils.NameServer.Params", "ti.sdo.ipc.heaps"), $$DEFAULT, "wh");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$create", "ti.sdo.ipc.heaps"), Global.get("ti$sdo$ipc$heaps$HeapMemMP$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$construct", "ti.sdo.ipc.heaps"), Global.get("ti$sdo$ipc$heaps$HeapMemMP$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMemMP$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMemMP$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMemMP$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMemMP$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMemMP$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.heaps.HeapMemMP$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Instance", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.Instance", om.findStrict("xdc.runtime.IHeap.Instance", "ti.sdo.ipc.heaps"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x07041776L, "rh");
        if (isCFG) {
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.heaps"), null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("name", $$T_Str, null, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("sharedBufSize", Proto.Elm.newCNum("(xdc_SizeT)"), 0L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Params", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.Params", om.findStrict("xdc.runtime.IHeap$$Params", "ti.sdo.ipc.heaps"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("CREATED", Proto.Elm.newCNum("(xdc_UInt32)"), 0x07041776L, "rh");
        if (isCFG) {
            po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.heaps"), null, "w");
            po.addFld("openFlag", $$T_Bool, false, "w");
            po.addFld("name", $$T_Str, null, "w");
            po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "w");
            po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("sharedBufSize", Proto.Elm.newCNum("(xdc_SizeT)"), 0L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Object", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.Object", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Instance", "ti.sdo.ipc.heaps"));
        // struct HeapMemMP.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$BasicView", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("buf", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("totalSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("objType", $$T_Str, $$UNDEF, "w");
                po.addFld("gate", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct HeapMemMP.DetailedView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$DetailedView", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.DetailedView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("buf", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("totalSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("objType", $$T_Str, $$UNDEF, "w");
                po.addFld("gate", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("attrs", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("totalFreeSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("largestFreeSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct HeapMemMP.FreeBlockView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$FreeBlockView", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.FreeBlockView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("address", $$T_Str, $$UNDEF, "w");
                po.addFld("label", $$T_Str, $$UNDEF, "w");
                po.addFld("size", $$T_Str, $$UNDEF, "w");
        // struct HeapMemMP.ExtendedStats
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$ExtendedStats", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.ExtendedStats", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("buf", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("size", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
        // struct HeapMemMP.Header
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Header", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.Header", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("next", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("size", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct HeapMemMP.Attrs
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Attrs", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.Attrs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("status", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("bufPtr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("head", (Proto)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Header", "ti.sdo.ipc.heaps"), $$DEFAULT, "w");
                po.addFld("gateMPAddr", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct HeapMemMP.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Instance_State", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("attrs", new Proto.Adr("ti_sdo_ipc_heaps_HeapMemMP_Attrs*", "PS"), $$UNDEF, "w");
                po.addFld("gate", (Proto)om.findStrict("ti.sdo.ipc.GateMP.Handle", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
                po.addFld("objType", (Proto)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
                po.addFld("nsKey", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("regionId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("allocSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("buf", new Proto.Adr("xdc_Char*", "Pn"), $$UNDEF, "w");
                po.addFld("minAlign", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("bufSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
        // struct HeapMemMP.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Module_State", "ti.sdo.ipc.heaps");
        po.init("ti.sdo.ipc.heaps.HeapMemMP.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("nameServer", (Proto)om.findStrict("ti.sdo.utils.NameServer.Handle", "ti.sdo.ipc.heaps"), $$UNDEF, "w");
    }

    void HeapBufMP$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP", "ti.sdo.ipc.heaps");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$Instance_State", "ti.sdo.ipc.heaps");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapBufMP.Attrs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$Attrs", "ti.sdo.ipc.heaps");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapBufMP.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$Instance_State", "ti.sdo.ipc.heaps");
        po.bind("attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapBufMP.Attrs", "isScalar", false));
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapBufMP.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$Module_State", "ti.sdo.ipc.heaps");
    }

    void HeapMultiBufMP$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP", "ti.sdo.ipc.heaps");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Instance_State", "ti.sdo.ipc.heaps");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Bucket$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Bucket", "ti.sdo.ipc.heaps");
        vo.bind("ExtendedStats$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMultiBufMP.ExtendedStats", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$ExtendedStats", "ti.sdo.ipc.heaps");
        vo.bind("Elem$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMultiBufMP.Elem", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Elem", "ti.sdo.ipc.heaps");
        vo.bind("BucketAttrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMultiBufMP.BucketAttrs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$BucketAttrs", "ti.sdo.ipc.heaps");
        vo.bind("Attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMultiBufMP.Attrs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Attrs", "ti.sdo.ipc.heaps");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMultiBufMP.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Instance_State", "ti.sdo.ipc.heaps");
        po.bind("attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMultiBufMP.Attrs", "isScalar", false));
        po.bind("bucketEntries$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket", "isScalar", false));
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMultiBufMP.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$Module_State", "ti.sdo.ipc.heaps");
    }

    void HeapMemMP$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP", "ti.sdo.ipc.heaps");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Instance_State", "ti.sdo.ipc.heaps");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("ExtendedStats$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMemMP.ExtendedStats", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$ExtendedStats", "ti.sdo.ipc.heaps");
        vo.bind("Header$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMemMP.Header", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Header", "ti.sdo.ipc.heaps");
        vo.bind("Attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMemMP.Attrs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Attrs", "ti.sdo.ipc.heaps");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMemMP.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Instance_State", "ti.sdo.ipc.heaps");
        po.bind("attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMemMP.Attrs", "isScalar", false));
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.heaps.HeapMemMP.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$Module_State", "ti.sdo.ipc.heaps");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.heaps.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.heaps"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/heaps/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.heaps"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.heaps"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.heaps"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.heaps"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.heaps"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.heaps"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.heaps", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.heaps");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.heaps.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ipc", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ipc.interfaces", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.utils", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.heaps'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.heaps$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.heaps$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.heaps$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void HeapBufMP$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP", "ti.sdo.ipc.heaps");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Module", "ti.sdo.ipc.heaps");
        vo.init2(po, "ti.sdo.ipc.heaps.HeapBufMP", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP$$capsule", "ti.sdo.ipc.heaps"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Instance", "ti.sdo.ipc.heaps"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Params", "ti.sdo.ipc.heaps"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Params", "ti.sdo.ipc.heaps")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Handle", "ti.sdo.ipc.heaps"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.heaps", "ti.sdo.ipc.heaps"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.BasicView", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.BasicView", "ti.sdo.ipc.heaps"));
        mcfgs.add("A_invBlockFreed");
        mcfgs.add("A_badAlignment");
        mcfgs.add("E_sizeTooLarge");
        mcfgs.add("E_alignTooLarge");
        mcfgs.add("E_exactFail");
        mcfgs.add("E_noBlocksLeft");
        mcfgs.add("maxNameLen");
        mcfgs.add("trackAllocs");
        icfgs.add("nameSrvPrms");
        vo.bind("Attrs", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Attrs", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Attrs", "ti.sdo.ipc.heaps"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Instance_State", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Instance_State", "ti.sdo.ipc.heaps"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Module_State", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Module_State", "ti.sdo.ipc.heaps"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.heaps")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.heaps.HeapBufMP$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$heaps$HeapBufMP$$__initObject"));
        }//isCFG
        vo.bind("postInit", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.postInit", "ti.sdo.ipc.heaps"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_heaps_HeapBufMP_Handle__label__E", "ti_sdo_ipc_heaps_HeapBufMP_Module__startupDone__E", "ti_sdo_ipc_heaps_HeapBufMP_Object__create__E", "ti_sdo_ipc_heaps_HeapBufMP_Object__delete__E", "ti_sdo_ipc_heaps_HeapBufMP_Object__destruct__E", "ti_sdo_ipc_heaps_HeapBufMP_Object__get__E", "ti_sdo_ipc_heaps_HeapBufMP_Object__first__E", "ti_sdo_ipc_heaps_HeapBufMP_Object__next__E", "ti_sdo_ipc_heaps_HeapBufMP_Params__init__E", "ti_sdo_ipc_heaps_HeapBufMP_isBlocking__E", "ti_sdo_ipc_heaps_HeapBufMP_getStats__E", "ti_sdo_ipc_heaps_HeapBufMP_alloc__E", "ti_sdo_ipc_heaps_HeapBufMP_free__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_sizeTooLarge", "E_alignTooLarge", "E_exactFail", "E_noBlocksLeft"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_invBlockFreed", "A_badAlignment"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.heaps.HeapBufMP.Object", "ti.sdo.ipc.heaps"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("HeapBufMP", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("HeapBufMP");
    }

    void HeapMultiBufMP$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP", "ti.sdo.ipc.heaps");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Module", "ti.sdo.ipc.heaps");
        vo.init2(po, "ti.sdo.ipc.heaps.HeapMultiBufMP", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP$$capsule", "ti.sdo.ipc.heaps"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance", "ti.sdo.ipc.heaps"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Params", "ti.sdo.ipc.heaps"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Params", "ti.sdo.ipc.heaps")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Handle", "ti.sdo.ipc.heaps"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.heaps", "ti.sdo.ipc.heaps"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.BasicView", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.BasicView", "ti.sdo.ipc.heaps"));
        vo.bind("BucketsView", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.BucketsView", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.BucketsView", "ti.sdo.ipc.heaps"));
        vo.bind("Bucket", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Bucket", "ti.sdo.ipc.heaps"));
        vo.bind("ExtendedStats", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.ExtendedStats", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.ExtendedStats", "ti.sdo.ipc.heaps"));
        mcfgs.add("A_invalidAlign");
        mcfgs.add("A_sizeNotFound");
        mcfgs.add("A_addrNotFound");
        mcfgs.add("E_exactFail");
        mcfgs.add("E_size");
        mcfgs.add("E_noBlocksLeft");
        mcfgs.add("maxNameLen");
        mcfgs.add("trackMaxAllocs");
        icfgs.add("nameSrvPrms");
        vo.bind("Elem", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Elem", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Elem", "ti.sdo.ipc.heaps"));
        vo.bind("BucketAttrs", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.BucketAttrs", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.BucketAttrs", "ti.sdo.ipc.heaps"));
        vo.bind("Attrs", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Attrs", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Attrs", "ti.sdo.ipc.heaps"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance_State", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Instance_State", "ti.sdo.ipc.heaps"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Module_State", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Module_State", "ti.sdo.ipc.heaps"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.heaps")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.heaps.HeapMultiBufMP$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$heaps$HeapMultiBufMP$$__initObject"));
        }//isCFG
        vo.bind("postInit", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.postInit", "ti.sdo.ipc.heaps"));
        vo.bind("processBuckets", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.processBuckets", "ti.sdo.ipc.heaps"));
        vo.bind("putTail", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.putTail", "ti.sdo.ipc.heaps"));
        vo.bind("getHead", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.getHead", "ti.sdo.ipc.heaps"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_heaps_HeapMultiBufMP_Handle__label__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_Module__startupDone__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__create__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__delete__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__destruct__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__get__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__first__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_Object__next__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_Params__init__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_isBlocking__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_getStats__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_alloc__E", "ti_sdo_ipc_heaps_HeapMultiBufMP_free__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_exactFail", "E_size", "E_noBlocksLeft"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_invalidAlign", "A_sizeNotFound", "A_addrNotFound"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP.Object", "ti.sdo.ipc.heaps"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("HeapMultiBufMP", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("HeapMultiBufMP");
    }

    void HeapMemMP$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP", "ti.sdo.ipc.heaps");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Module", "ti.sdo.ipc.heaps");
        vo.init2(po, "ti.sdo.ipc.heaps.HeapMemMP", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP$$capsule", "ti.sdo.ipc.heaps"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Instance", "ti.sdo.ipc.heaps"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Params", "ti.sdo.ipc.heaps"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Params", "ti.sdo.ipc.heaps")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Handle", "ti.sdo.ipc.heaps"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.heaps", "ti.sdo.ipc.heaps"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.BasicView", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.BasicView", "ti.sdo.ipc.heaps"));
        vo.bind("DetailedView", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.DetailedView", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.DetailedView", "ti.sdo.ipc.heaps"));
        vo.bind("FreeBlockView", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.FreeBlockView", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.FreeBlockView", "ti.sdo.ipc.heaps"));
        vo.bind("ExtendedStats", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.ExtendedStats", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.ExtendedStats", "ti.sdo.ipc.heaps"));
        mcfgs.add("A_zeroBlock");
        mcfgs.add("A_heapSize");
        mcfgs.add("A_align");
        mcfgs.add("A_invalidFree");
        mcfgs.add("E_memory");
        mcfgs.add("maxNameLen");
        icfgs.add("nameSrvPrms");
        vo.bind("Header", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Header", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Header", "ti.sdo.ipc.heaps"));
        vo.bind("Attrs", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Attrs", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Attrs", "ti.sdo.ipc.heaps"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Instance_State", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Instance_State", "ti.sdo.ipc.heaps"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Module_State", "ti.sdo.ipc.heaps"));
        tdefs.add(om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Module_State", "ti.sdo.ipc.heaps"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.heaps")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.heaps.HeapMemMP$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$heaps$HeapMemMP$$__initObject"));
        }//isCFG
        vo.bind("postInit", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.postInit", "ti.sdo.ipc.heaps"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_heaps_HeapMemMP_Handle__label__E", "ti_sdo_ipc_heaps_HeapMemMP_Module__startupDone__E", "ti_sdo_ipc_heaps_HeapMemMP_Object__create__E", "ti_sdo_ipc_heaps_HeapMemMP_Object__delete__E", "ti_sdo_ipc_heaps_HeapMemMP_Object__destruct__E", "ti_sdo_ipc_heaps_HeapMemMP_Object__get__E", "ti_sdo_ipc_heaps_HeapMemMP_Object__first__E", "ti_sdo_ipc_heaps_HeapMemMP_Object__next__E", "ti_sdo_ipc_heaps_HeapMemMP_Params__init__E", "ti_sdo_ipc_heaps_HeapMemMP_isBlocking__E", "ti_sdo_ipc_heaps_HeapMemMP_getStats__E", "ti_sdo_ipc_heaps_HeapMemMP_alloc__E", "ti_sdo_ipc_heaps_HeapMemMP_free__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_memory"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_zeroBlock", "A_heapSize", "A_align", "A_invalidFree"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.heaps.HeapMemMP.Object", "ti.sdo.ipc.heaps"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("HeapMemMP", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("HeapMemMP");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sdo.ipc.heaps")).findStrict("PARAMS", "ti.sdo.ipc.heaps");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP", "ti.sdo.ipc.heaps")).findStrict("PARAMS", "ti.sdo.ipc.heaps");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP", "ti.sdo.ipc.heaps")).findStrict("PARAMS", "ti.sdo.ipc.heaps");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP", "ti.sdo.ipc.heaps")).findStrict("PARAMS", "ti.sdo.ipc.heaps");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP", "ti.sdo.ipc.heaps"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP", "ti.sdo.ipc.heaps"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP", "ti.sdo.ipc.heaps"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapBufMP", "ti.sdo.ipc.heaps");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMultiBufMP", "ti.sdo.ipc.heaps");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Buffer Information", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE_DATA"), "viewInitFxn", "viewInitData", "structName", "BucketsView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.heaps.HeapMemMP", "ti.sdo.ipc.heaps");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Detailed", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitDetailed", "structName", "DetailedView")}), Global.newArray(new Object[]{"FreeList", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE_DATA"), "viewInitFxn", "viewInitData", "structName", "FreeBlockView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.heaps.HeapBufMP")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.heaps.HeapMultiBufMP")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.heaps.HeapMemMP")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.heaps")).add(pkgV);
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
        HeapBufMP$$OBJECTS();
        HeapMultiBufMP$$OBJECTS();
        HeapMemMP$$OBJECTS();
        HeapBufMP$$CONSTS();
        HeapMultiBufMP$$CONSTS();
        HeapMemMP$$CONSTS();
        HeapBufMP$$CREATES();
        HeapMultiBufMP$$CREATES();
        HeapMemMP$$CREATES();
        HeapBufMP$$FUNCTIONS();
        HeapMultiBufMP$$FUNCTIONS();
        HeapMemMP$$FUNCTIONS();
        HeapBufMP$$SIZES();
        HeapMultiBufMP$$SIZES();
        HeapMemMP$$SIZES();
        HeapBufMP$$TYPES();
        HeapMultiBufMP$$TYPES();
        HeapMemMP$$TYPES();
        if (isROV) {
            HeapBufMP$$ROV();
            HeapMultiBufMP$$ROV();
            HeapMemMP$$ROV();
        }//isROV
        $$SINGLETONS();
        HeapBufMP$$SINGLETONS();
        HeapMultiBufMP$$SINGLETONS();
        HeapMemMP$$SINGLETONS();
        $$INITIALIZATION();
    }
}
