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

public class ti_sdo_ipc_gates
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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.interfaces");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.utils");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.gates.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.gates", new Value.Obj("ti.sdo.ipc.gates", pkgP));
    }

    void GateAAMonitor$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateAAMonitor.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.gates.GateAAMonitor", new Value.Obj("ti.sdo.ipc.gates.GateAAMonitor", po));
        pkgV.bind("GateAAMonitor", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateAAMonitor$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateAAMonitor$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.gates.GateAAMonitor.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateAAMonitor$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateAAMonitor$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.gates.GateAAMonitor.Object", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Instance_State", "ti.sdo.ipc.gates"));
        }//isROV
    }

    void GateHWSem$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateHWSem.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.gates.GateHWSem", new Value.Obj("ti.sdo.ipc.gates.GateHWSem", po));
        pkgV.bind("GateHWSem", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateHWSem$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateHWSem.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateHWSem$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateHWSem.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.gates.GateHWSem.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateHWSem$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateHWSem.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateHWSem$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateHWSem.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.gates.GateHWSem.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.gates.GateHWSem.Object", om.findStrict("ti.sdo.ipc.gates.GateHWSem.Instance_State", "ti.sdo.ipc.gates"));
        }//isROV
    }

    void GateHWSpinlock$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateHWSpinlock.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.gates.GateHWSpinlock", new Value.Obj("ti.sdo.ipc.gates.GateHWSpinlock", po));
        pkgV.bind("GateHWSpinlock", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateHWSpinlock.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateHWSpinlock.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.gates.GateHWSpinlock.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateHWSpinlock.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateHWSpinlock.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.gates.GateHWSpinlock.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.gates.GateHWSpinlock.Object", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Instance_State", "ti.sdo.ipc.gates"));
        }//isROV
    }

    void GatePeterson$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GatePeterson.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.gates.GatePeterson", new Value.Obj("ti.sdo.ipc.gates.GatePeterson", po));
        pkgV.bind("GatePeterson", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GatePeterson$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GatePeterson.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GatePeterson$$Attrs", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GatePeterson.Attrs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GatePeterson$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GatePeterson.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.gates.GatePeterson.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GatePeterson$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GatePeterson.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GatePeterson$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GatePeterson.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.gates.GatePeterson.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.gates.GatePeterson.Object", om.findStrict("ti.sdo.ipc.gates.GatePeterson.Instance_State", "ti.sdo.ipc.gates"));
        }//isROV
    }

    void GatePetersonN$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GatePetersonN.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.gates.GatePetersonN", new Value.Obj("ti.sdo.ipc.gates.GatePetersonN", po));
        pkgV.bind("GatePetersonN", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GatePetersonN$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GatePetersonN.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GatePetersonN$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GatePetersonN.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.gates.GatePetersonN.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GatePetersonN$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GatePetersonN.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GatePetersonN$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GatePetersonN.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.gates.GatePetersonN.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.gates.GatePetersonN.Object", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Instance_State", "ti.sdo.ipc.gates"));
        }//isROV
    }

    void GateMPSupportNull$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateMPSupportNull.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.gates.GateMPSupportNull", new Value.Obj("ti.sdo.ipc.gates.GateMPSupportNull", po));
        pkgV.bind("GateMPSupportNull", vo);
        // decls 
        om.bind("ti.sdo.ipc.gates.GateMPSupportNull.Action", new Proto.Enm("ti.sdo.ipc.gates.GateMPSupportNull.Action"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateMPSupportNull.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.gates.GateMPSupportNull.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateMPSupportNull.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.gates.GateMPSupportNull.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.gates.GateMPSupportNull.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.gates.GateMPSupportNull.Object", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Instance_State", "ti.sdo.ipc.gates"));
        }//isROV
    }

    void GateAAMonitor$$CONSTS()
    {
        // module GateAAMonitor
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.CACHELINE_SIZE", 64L);
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.SL2_RANGE_BASE", 0x00200000L);
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.SL2_RANGE_MAX", 0x002bffffL);
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.query", new Extern("ti_sdo_ipc_gates_GateAAMonitor_query__E", "xdc_Bool(*)(xdc_Int)", true, false));
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.getReservedMask", new Extern("ti_sdo_ipc_gates_GateAAMonitor_getReservedMask__E", "xdc_Bits32*(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.sharedMemReq", new Extern("ti_sdo_ipc_gates_GateAAMonitor_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_interfaces_IGateMPSupport_Params*)", true, false));
        om.bind("ti.sdo.ipc.gates.GateAAMonitor.getLock", new Extern("ti_sdo_ipc_gates_GateAAMonitor_getLock__I", "xdc_UInt(*)(xdc_Ptr)", true, false));
    }

    void GateHWSem$$CONSTS()
    {
        // module GateHWSem
        om.bind("ti.sdo.ipc.gates.GateHWSem.query", new Extern("ti_sdo_ipc_gates_GateHWSem_query__E", "xdc_Bool(*)(xdc_Int)", true, false));
        om.bind("ti.sdo.ipc.gates.GateHWSem.getReservedMask", new Extern("ti_sdo_ipc_gates_GateHWSem_getReservedMask__E", "xdc_Bits32*(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.gates.GateHWSem.sharedMemReq", new Extern("ti_sdo_ipc_gates_GateHWSem_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_interfaces_IGateMPSupport_Params*)", true, false));
    }

    void GateHWSpinlock$$CONSTS()
    {
        // module GateHWSpinlock
        om.bind("ti.sdo.ipc.gates.GateHWSpinlock.query", new Extern("ti_sdo_ipc_gates_GateHWSpinlock_query__E", "xdc_Bool(*)(xdc_Int)", true, false));
        om.bind("ti.sdo.ipc.gates.GateHWSpinlock.getReservedMask", new Extern("ti_sdo_ipc_gates_GateHWSpinlock_getReservedMask__E", "xdc_Bits32*(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.gates.GateHWSpinlock.sharedMemReq", new Extern("ti_sdo_ipc_gates_GateHWSpinlock_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_interfaces_IGateMPSupport_Params*)", true, false));
    }

    void GatePeterson$$CONSTS()
    {
        // module GatePeterson
        om.bind("ti.sdo.ipc.gates.GatePeterson.FREE", 0L);
        om.bind("ti.sdo.ipc.gates.GatePeterson.BUSY", 1L);
        om.bind("ti.sdo.ipc.gates.GatePeterson.query", new Extern("ti_sdo_ipc_gates_GatePeterson_query__E", "xdc_Bool(*)(xdc_Int)", true, false));
        om.bind("ti.sdo.ipc.gates.GatePeterson.getReservedMask", new Extern("ti_sdo_ipc_gates_GatePeterson_getReservedMask__E", "xdc_Bits32*(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.gates.GatePeterson.sharedMemReq", new Extern("ti_sdo_ipc_gates_GatePeterson_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_interfaces_IGateMPSupport_Params*)", true, false));
        om.bind("ti.sdo.ipc.gates.GatePeterson.postInit", new Extern("ti_sdo_ipc_gates_GatePeterson_postInit__I", "xdc_Void(*)(ti_sdo_ipc_gates_GatePeterson_Object*)", true, false));
    }

    void GatePetersonN$$CONSTS()
    {
        // module GatePetersonN
        om.bind("ti.sdo.ipc.gates.GatePetersonN.NOT_INTERESTED", Global.eval("-1"));
        om.bind("ti.sdo.ipc.gates.GatePetersonN.query", new Extern("ti_sdo_ipc_gates_GatePetersonN_query__E", "xdc_Bool(*)(xdc_Int)", true, false));
        om.bind("ti.sdo.ipc.gates.GatePetersonN.getReservedMask", new Extern("ti_sdo_ipc_gates_GatePetersonN_getReservedMask__E", "xdc_Bits32*(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.gates.GatePetersonN.sharedMemReq", new Extern("ti_sdo_ipc_gates_GatePetersonN_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_interfaces_IGateMPSupport_Params*)", true, false));
        om.bind("ti.sdo.ipc.gates.GatePetersonN.postInit", new Extern("ti_sdo_ipc_gates_GatePetersonN_postInit__I", "xdc_Void(*)(ti_sdo_ipc_gates_GatePetersonN_Object*)", true, false));
    }

    void GateMPSupportNull$$CONSTS()
    {
        // module GateMPSupportNull
        om.bind("ti.sdo.ipc.gates.GateMPSupportNull.Action_NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Action", "ti.sdo.ipc.gates"), "ti.sdo.ipc.gates.GateMPSupportNull.Action_NONE", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.sdo.ipc.gates.GateMPSupportNull.Action_ASSERT", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Action", "ti.sdo.ipc.gates"), "ti.sdo.ipc.gates.GateMPSupportNull.Action_ASSERT", xdc.services.intern.xsr.Enum.intValue(1L)+0));
        om.bind("ti.sdo.ipc.gates.GateMPSupportNull.query", new Extern("ti_sdo_ipc_gates_GateMPSupportNull_query__E", "xdc_Bool(*)(xdc_Int)", true, false));
        om.bind("ti.sdo.ipc.gates.GateMPSupportNull.getReservedMask", new Extern("ti_sdo_ipc_gates_GateMPSupportNull_getReservedMask__E", "xdc_Bits32*(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ipc.gates.GateMPSupportNull.sharedMemReq", new Extern("ti_sdo_ipc_gates_GateMPSupportNull_sharedMemReq__E", "xdc_SizeT(*)(ti_sdo_ipc_interfaces_IGateMPSupport_Params*)", true, false));
    }

    void GateAAMonitor$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateAAMonitor$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.gates.GateAAMonitor.create() called before xdc.useModule('ti.sdo.ipc.gates.GateAAMonitor')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.localGate, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GateAAMonitor$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Module", "ti.sdo.ipc.gates"), om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Instance", "ti.sdo.ipc.gates"), 2, 1, false));
                        fxn.addArg(0, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateAAMonitor$$create = function( localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GateAAMonitor'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.gates.GateAAMonitor.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.gates']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.gates.GateAAMonitor'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [localGate]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GateAAMonitor'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GateAAMonitor$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Module", "ti.sdo.ipc.gates"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor$$Object", "ti.sdo.ipc.gates"), null);
                        fxn.addArg(1, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateAAMonitor$$construct = function( __obj, localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GateAAMonitor'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.gates.GateAAMonitor'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GateAAMonitor'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void GateHWSem$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateHWSem$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.gates.GateHWSem.create() called before xdc.useModule('ti.sdo.ipc.gates.GateHWSem')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.localGate, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GateHWSem$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GateHWSem.Module", "ti.sdo.ipc.gates"), om.findStrict("ti.sdo.ipc.gates.GateHWSem.Instance", "ti.sdo.ipc.gates"), 2, 1, false));
                        fxn.addArg(0, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GateHWSem.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateHWSem$$create = function( localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GateHWSem'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.gates.GateHWSem.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.gates']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.gates.GateHWSem'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [localGate]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GateHWSem'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GateHWSem$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GateHWSem.Module", "ti.sdo.ipc.gates"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.gates.GateHWSem$$Object", "ti.sdo.ipc.gates"), null);
                        fxn.addArg(1, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GateHWSem.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateHWSem$$construct = function( __obj, localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GateHWSem'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.gates.GateHWSem'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GateHWSem'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void GateHWSpinlock$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateHWSpinlock$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.gates.GateHWSpinlock.create() called before xdc.useModule('ti.sdo.ipc.gates.GateHWSpinlock')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.localGate, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Module", "ti.sdo.ipc.gates"), om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Instance", "ti.sdo.ipc.gates"), 2, 1, false));
                        fxn.addArg(0, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateHWSpinlock$$create = function( localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GateHWSpinlock'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.gates.GateHWSpinlock.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.gates']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.gates.GateHWSpinlock'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [localGate]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GateHWSpinlock'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Module", "ti.sdo.ipc.gates"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock$$Object", "ti.sdo.ipc.gates"), null);
                        fxn.addArg(1, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateHWSpinlock$$construct = function( __obj, localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GateHWSpinlock'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.gates.GateHWSpinlock'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GateHWSpinlock'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void GatePeterson$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GatePeterson$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.gates.GatePeterson.create() called before xdc.useModule('ti.sdo.ipc.gates.GatePeterson')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.localGate, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GatePeterson$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GatePeterson.Module", "ti.sdo.ipc.gates"), om.findStrict("ti.sdo.ipc.gates.GatePeterson.Instance", "ti.sdo.ipc.gates"), 2, 1, false));
                        fxn.addArg(0, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GatePeterson.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GatePeterson$$create = function( localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GatePeterson'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.gates.GatePeterson.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.gates']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.gates.GatePeterson'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [localGate]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GatePeterson'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GatePeterson$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GatePeterson.Module", "ti.sdo.ipc.gates"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.gates.GatePeterson$$Object", "ti.sdo.ipc.gates"), null);
                        fxn.addArg(1, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GatePeterson.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GatePeterson$$construct = function( __obj, localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GatePeterson'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.gates.GatePeterson'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GatePeterson'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void GatePetersonN$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GatePetersonN$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.gates.GatePetersonN.create() called before xdc.useModule('ti.sdo.ipc.gates.GatePetersonN')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.localGate, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GatePetersonN$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Module", "ti.sdo.ipc.gates"), om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Instance", "ti.sdo.ipc.gates"), 2, 1, false));
                        fxn.addArg(0, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GatePetersonN$$create = function( localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GatePetersonN'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.gates.GatePetersonN.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.gates']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.gates.GatePetersonN'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [localGate]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GatePetersonN'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GatePetersonN$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Module", "ti.sdo.ipc.gates"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.gates.GatePetersonN$$Object", "ti.sdo.ipc.gates"), null);
                        fxn.addArg(1, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GatePetersonN$$construct = function( __obj, localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GatePetersonN'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.gates.GatePetersonN'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GatePetersonN'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void GateMPSupportNull$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateMPSupportNull$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.gates.GateMPSupportNull.create() called before xdc.useModule('ti.sdo.ipc.gates.GateMPSupportNull')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.localGate, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Module", "ti.sdo.ipc.gates"), om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Instance", "ti.sdo.ipc.gates"), 2, 1, false));
                        fxn.addArg(0, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateMPSupportNull$$create = function( localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GateMPSupportNull'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.gates.GateMPSupportNull.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.gates']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.gates.GateMPSupportNull'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [localGate]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GateMPSupportNull'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Module", "ti.sdo.ipc.gates"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull$$Object", "ti.sdo.ipc.gates"), null);
                        fxn.addArg(1, "localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Params", "ti.sdo.ipc.gates"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$gates$GateMPSupportNull$$construct = function( __obj, localGate, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.gates.GateMPSupportNull'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {localGate:localGate});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.gates.GateMPSupportNull'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.gates.GateMPSupportNull'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void GateAAMonitor$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GateHWSem$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn GateHWSem.setReserved
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GateHWSem$$setReserved", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GateHWSem.Module", "ti.sdo.ipc.gates"), null, 1, 1, false));
                fxn.addArg(0, "semNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF);
    }

    void GateHWSpinlock$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn GateHWSpinlock.setReserved
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$setReserved", new Proto.Fxn(om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Module", "ti.sdo.ipc.gates"), null, 1, 1, false));
                fxn.addArg(0, "lockNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF);
    }

    void GatePeterson$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GatePetersonN$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GateMPSupportNull$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GateAAMonitor$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Instance_State", "ti.sdo.ipc.gates");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("sharedAddr", "UPtr"));
        sizes.add(Global.newArray("nested", "UInt"));
        sizes.add(Global.newArray("localGate", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.gates.GateAAMonitor.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.gates.GateAAMonitor.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.gates.GateAAMonitor.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void GateHWSem$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.gates.GateHWSem.Instance_State", "ti.sdo.ipc.gates");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("semNum", "UInt"));
        sizes.add(Global.newArray("nested", "UInt"));
        sizes.add(Global.newArray("localGate", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.gates.GateHWSem.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.gates.GateHWSem.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.gates.GateHWSem.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void GateHWSpinlock$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Instance_State", "ti.sdo.ipc.gates");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("lockNum", "UInt"));
        sizes.add(Global.newArray("nested", "UInt"));
        sizes.add(Global.newArray("localGate", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.gates.GateHWSpinlock.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.gates.GateHWSpinlock.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.gates.GateHWSpinlock.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void GatePeterson$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.gates.GatePeterson.Attrs", "ti.sdo.ipc.gates");
        sizes.clear();
        sizes.add(Global.newArray("creatorProcId", "UInt16"));
        sizes.add(Global.newArray("openerProcId", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.gates.GatePeterson.Attrs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.gates.GatePeterson.Attrs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.gates.GatePeterson.Attrs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.gates.GatePeterson.Instance_State", "ti.sdo.ipc.gates");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("attrs", "UPtr"));
        sizes.add(Global.newArray("flag", "A2;UPtr"));
        sizes.add(Global.newArray("turn", "UPtr"));
        sizes.add(Global.newArray("selfId", "UInt16"));
        sizes.add(Global.newArray("otherId", "UInt16"));
        sizes.add(Global.newArray("nested", "UInt"));
        sizes.add(Global.newArray("localGate", "UPtr"));
        sizes.add(Global.newArray("objType", "Nti.sdo.ipc.Ipc.ObjType;;0x1;0x2;0x4;0x8;0x10;0x20"));
        sizes.add(Global.newArray("cacheLineSize", "USize"));
        sizes.add(Global.newArray("cacheEnabled", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.gates.GatePeterson.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.gates.GatePeterson.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.gates.GatePeterson.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void GatePetersonN$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Instance_State", "ti.sdo.ipc.gates");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("enteredStage", "A8;UPtr"));
        sizes.add(Global.newArray("lastProcEnteringStage", "A8 - 1;UPtr"));
        sizes.add(Global.newArray("selfId", "UInt16"));
        sizes.add(Global.newArray("numProcessors", "UInt16"));
        sizes.add(Global.newArray("nested", "UInt"));
        sizes.add(Global.newArray("localGate", "UPtr"));
        sizes.add(Global.newArray("objType", "Nti.sdo.ipc.Ipc.ObjType;;0x1;0x2;0x4;0x8;0x10;0x20"));
        sizes.add(Global.newArray("cacheLineSize", "USize"));
        sizes.add(Global.newArray("cacheEnabled", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.gates.GatePetersonN.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.gates.GatePetersonN.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.gates.GatePetersonN.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void GateMPSupportNull$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Instance_State", "ti.sdo.ipc.gates");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("resourceId", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.gates.GateMPSupportNull.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.gates.GateMPSupportNull.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.gates.GateMPSupportNull.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void GateAAMonitor$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/gates/GateAAMonitor.xs");
        om.bind("ti.sdo.ipc.gates.GateAAMonitor$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Module", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateAAMonitor.Module", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("CACHELINE_SIZE", Proto.Elm.newCNum("(xdc_UInt)"), 64L, "rh");
                po.addFld("SL2_RANGE_BASE", new Proto.Adr("xdc_Ptr", "Pv"), 0x00200000L, "rh");
                po.addFld("SL2_RANGE_MAX", new Proto.Adr("xdc_Ptr", "Pv"), 0x002bffffL, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.gates"), $$UNDEF, "wh");
            po.addFld("A_invSharedAddr", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.gates"), Global.newObject("msg", "A_invSharedAddr: Address must be in shared L2 address space"), "w");
            po.addFld("numInstances", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor$$create", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GateAAMonitor$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor$$construct", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GateAAMonitor$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateAAMonitor$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateAAMonitor$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateAAMonitor$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateAAMonitor$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateAAMonitor$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateAAMonitor$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "queryMeta");
                if (fxn != null) po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getNumResources");
                if (fxn != null) po.addFxn("getNumResources", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getNumResources", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getRemoteStatus$view");
                if (fxn != null) po.addFxn("getRemoteStatus$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getRemoteStatus$view", "ti.sdo.ipc.gates"), fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Instance", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateAAMonitor.Instance", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Instance", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("CACHELINE_SIZE", Proto.Elm.newCNum("(xdc_UInt)"), 64L, "rh");
                po.addFld("SL2_RANGE_BASE", new Proto.Adr("xdc_Ptr", "Pv"), 0x00200000L, "rh");
                po.addFld("SL2_RANGE_MAX", new Proto.Adr("xdc_Ptr", "Pv"), 0x002bffffL, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor$$Params", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateAAMonitor.Params", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$Params", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("CACHELINE_SIZE", Proto.Elm.newCNum("(xdc_UInt)"), 64L, "rh");
                po.addFld("SL2_RANGE_BASE", new Proto.Adr("xdc_Ptr", "Pv"), 0x00200000L, "rh");
                po.addFld("SL2_RANGE_MAX", new Proto.Adr("xdc_Ptr", "Pv"), 0x002bffffL, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor$$Object", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateAAMonitor.Object", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Instance", "ti.sdo.ipc.gates"));
        // struct GateAAMonitor.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor$$BasicView", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateAAMonitor.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("sharedAddr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("nested", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("enteredBy", $$T_Str, $$UNDEF, "w");
        // struct GateAAMonitor.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor$$Instance_State", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateAAMonitor.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("sharedAddr", new Proto.Adr("xdc_UInt32*", "Pn"), $$UNDEF, "w");
                po.addFld("nested", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF, "w");
    }

    void GateHWSem$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/gates/GateHWSem.xs");
        om.bind("ti.sdo.ipc.gates.GateHWSem$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem.Module", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSem.Module", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.gates"), $$UNDEF, "wh");
            po.addFld("A_invSemNum", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.gates"), Global.newObject("msg", "A_invSemNum: Invalid hardware semaphore number"), "w");
            po.addFld("baseAddr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
            po.addFld("queryAddr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
            po.addFld("numSems", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
            po.addFld("reservedMaskArr", new Proto.Arr(Proto.Elm.newCNum("(xdc_Bits32)"), false), $$DEFAULT, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GateHWSem$$create", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GateHWSem$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GateHWSem$$construct", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GateHWSem$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSem$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSem$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSem$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSem$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSem$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSem$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "queryMeta");
                if (fxn != null) po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getNumResources");
                if (fxn != null) po.addFxn("getNumResources", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getNumResources", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getRemoteStatus$view");
                if (fxn != null) po.addFxn("getRemoteStatus$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getRemoteStatus$view", "ti.sdo.ipc.gates"), fxn);
                po.addFxn("setReserved", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GateHWSem$$setReserved", "ti.sdo.ipc.gates"), Global.get(cap, "setReserved"));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem.Instance", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSem.Instance", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Instance", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem$$Params", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSem.Params", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$Params", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem$$Object", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSem.Object", om.findStrict("ti.sdo.ipc.gates.GateHWSem.Instance", "ti.sdo.ipc.gates"));
        // struct GateHWSem.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem$$BasicView", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSem.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("semNum", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("nested", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("enteredBy", $$T_Str, $$UNDEF, "w");
        // struct GateHWSem.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem$$Instance_State", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSem.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("semNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("nested", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF, "w");
    }

    void GateHWSpinlock$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/gates/GateHWSpinlock.xs");
        om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Module", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSpinlock.Module", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.gates"), $$UNDEF, "wh");
            po.addFld("LM_enter", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc.gates"), Global.newObject("mask", 0x0100L, "msg", "LM_enter: Gate (lockNum = %d) entered, returning key = %d"), "w");
            po.addFld("LM_leave", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc.gates"), Global.newObject("mask", 0x0100L, "msg", "LM_leave: Gate (lockNum = %d) left using key = %d"), "w");
            po.addFld("LM_create", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc.gates"), Global.newObject("mask", 0x0100L, "msg", "LM_create: Gate (lockNum = %d) created"), "w");
            po.addFld("LM_open", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc.gates"), Global.newObject("mask", 0x0100L, "msg", "LM_open: Remote gate (lockNum = %d) opened"), "w");
            po.addFld("LM_delete", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc.gates"), Global.newObject("mask", 0x0100L, "msg", "LM_delete: Gate (lockNum = %d) deleted"), "w");
            po.addFld("LM_close", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sdo.ipc.gates"), Global.newObject("mask", 0x0100L, "msg", "LM_close: Gate (lockNum = %d) closed"), "w");
            po.addFld("A_invSpinLockNum", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.gates"), Global.newObject("msg", "A_invSpinLockNum: Invalid hardware spinlock number"), "w");
            po.addFld("baseAddr", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("numLocks", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
            po.addFld("reservedMaskArr", new Proto.Arr(Proto.Elm.newCNum("(xdc_Bits32)"), false), $$DEFAULT, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock$$create", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GateHWSpinlock$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock$$construct", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GateHWSpinlock$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateHWSpinlock$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "queryMeta");
                if (fxn != null) po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getNumResources");
                if (fxn != null) po.addFxn("getNumResources", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getNumResources", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getRemoteStatus$view");
                if (fxn != null) po.addFxn("getRemoteStatus$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getRemoteStatus$view", "ti.sdo.ipc.gates"), fxn);
                po.addFxn("setReserved", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock$$setReserved", "ti.sdo.ipc.gates"), Global.get(cap, "setReserved"));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Instance", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSpinlock.Instance", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Instance", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock$$Params", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSpinlock.Params", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$Params", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock$$Object", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSpinlock.Object", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Instance", "ti.sdo.ipc.gates"));
        // struct GateHWSpinlock.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock$$BasicView", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSpinlock.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("lockNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("nested", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        // struct GateHWSpinlock.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock$$Instance_State", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateHWSpinlock.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("lockNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("nested", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF, "w");
    }

    void GatePeterson$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/gates/GatePeterson.xs");
        om.bind("ti.sdo.ipc.gates.GatePeterson$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson.Module", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePeterson.Module", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("FREE", Proto.Elm.newCNum("(xdc_UInt32)"), 0L, "rh");
                po.addFld("BUSY", Proto.Elm.newCNum("(xdc_UInt32)"), 1L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.gates"), $$UNDEF, "wh");
            po.addFld("E_gateRemotelyOpened", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.gates"), Global.newObject("msg", "E_gateRemotelyOpened: Gate already in use by two other processors: creator: %d, opener: %d"), "w");
            po.addFld("numInstances", Proto.Elm.newCNum("(xdc_UInt)"), 512L, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GatePeterson$$create", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GatePeterson$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GatePeterson$$construct", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GatePeterson$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePeterson$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePeterson$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePeterson$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePeterson$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePeterson$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePeterson$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "queryMeta");
                if (fxn != null) po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getNumResources");
                if (fxn != null) po.addFxn("getNumResources", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getNumResources", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getRemoteStatus$view");
                if (fxn != null) po.addFxn("getRemoteStatus$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getRemoteStatus$view", "ti.sdo.ipc.gates"), fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson.Instance", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePeterson.Instance", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Instance", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("FREE", Proto.Elm.newCNum("(xdc_UInt32)"), 0L, "rh");
                po.addFld("BUSY", Proto.Elm.newCNum("(xdc_UInt32)"), 1L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson$$Params", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePeterson.Params", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$Params", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("FREE", Proto.Elm.newCNum("(xdc_UInt32)"), 0L, "rh");
                po.addFld("BUSY", Proto.Elm.newCNum("(xdc_UInt32)"), 1L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson$$Object", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePeterson.Object", om.findStrict("ti.sdo.ipc.gates.GatePeterson.Instance", "ti.sdo.ipc.gates"));
        // struct GatePeterson.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson$$BasicView", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePeterson.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("objType", $$T_Str, $$UNDEF, "w");
                po.addFld("localGate", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("nested", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("creatorProcId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("openerProcId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("gateOwner", $$T_Str, $$UNDEF, "w");
        // struct GatePeterson.Attrs
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson$$Attrs", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePeterson.Attrs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("creatorProcId", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("openerProcId", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
        // struct GatePeterson.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson$$Instance_State", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePeterson.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("attrs", new Proto.Adr("ti_sdo_ipc_gates_GatePeterson_Attrs*", "PS"), $$UNDEF, "w");
                po.addFld("flag", new Proto.Arr(new Proto.Adr("xdc_Bits16*", "Pn"), false, xdc.services.intern.xsr.Enum.intValue(2L)), $$DEFAULT, "w");
                po.addFld("turn", new Proto.Adr("xdc_Bits16*", "Pn"), $$UNDEF, "w");
                po.addFld("selfId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("otherId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("nested", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF, "w");
                po.addFld("objType", (Proto)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc.gates"), $$UNDEF, "w");
                po.addFld("cacheLineSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
    }

    void GatePetersonN$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/gates/GatePetersonN.xs");
        om.bind("ti.sdo.ipc.gates.GatePetersonN$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Module", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePetersonN.Module", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("NOT_INTERESTED", Proto.Elm.newCNum("(xdc_Int32)"), Global.eval("-1"), "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.gates"), $$UNDEF, "wh");
            po.addFld("numInstances", Proto.Elm.newCNum("(xdc_UInt)"), 512L, "w");
            po.addFld("MAX_NUM_PROCS", Proto.Elm.newCNum("(xdc_UInt)"), 8L, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GatePetersonN$$create", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GatePetersonN$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GatePetersonN$$construct", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GatePetersonN$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePetersonN$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePetersonN$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePetersonN$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePetersonN$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePetersonN$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GatePetersonN$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "queryMeta");
                if (fxn != null) po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getNumResources");
                if (fxn != null) po.addFxn("getNumResources", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getNumResources", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getRemoteStatus$view");
                if (fxn != null) po.addFxn("getRemoteStatus$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getRemoteStatus$view", "ti.sdo.ipc.gates"), fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Instance", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePetersonN.Instance", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Instance", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("NOT_INTERESTED", Proto.Elm.newCNum("(xdc_Int32)"), Global.eval("-1"), "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN$$Params", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePetersonN.Params", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$Params", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("NOT_INTERESTED", Proto.Elm.newCNum("(xdc_Int32)"), Global.eval("-1"), "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN$$Object", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePetersonN.Object", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Instance", "ti.sdo.ipc.gates"));
        // struct GatePetersonN.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN$$BasicView", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePetersonN.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("objType", $$T_Str, $$UNDEF, "w");
                po.addFld("localGate", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("nested", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("gateOwner", $$T_Str, $$UNDEF, "w");
        // struct GatePetersonN.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN$$Instance_State", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GatePetersonN.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("enteredStage", new Proto.Arr(new Proto.Adr("xdc_Int32*", "Pn"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("lastProcEnteringStage", new Proto.Arr(new Proto.Adr("xdc_Int32*", "Pn"), false, xdc.services.intern.xsr.Enum.intValue(Global.eval("8 - 1"))), $$DEFAULT, "w");
                po.addFld("selfId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("numProcessors", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("nested", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("localGate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "ti.sdo.ipc.gates"), $$UNDEF, "w");
                po.addFld("objType", (Proto)om.findStrict("ti.sdo.ipc.Ipc.ObjType", "ti.sdo.ipc.gates"), $$UNDEF, "w");
                po.addFld("cacheLineSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("cacheEnabled", $$T_Bool, $$UNDEF, "w");
    }

    void GateMPSupportNull$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/gates/GateMPSupportNull.xs");
        om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Module", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateMPSupportNull.Module", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Module", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFld("A_invalidAction", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.gates"), Global.newObject("msg", "A_invalidAction: Cannot use ti.sdo.ipc.gates.GateMPSupportNull"), "w");
            po.addFld("action", (Proto)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Action", "ti.sdo.ipc.gates"), om.find("ti.sdo.ipc.gates.GateMPSupportNull.Action_ASSERT"), "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull$$create", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GateMPSupportNull$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull$$construct", "ti.sdo.ipc.gates"), Global.get("ti$sdo$ipc$gates$GateMPSupportNull$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.gates.GateMPSupportNull$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "queryMeta");
                if (fxn != null) po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getNumResources");
                if (fxn != null) po.addFxn("getNumResources", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getNumResources", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getRemoteStatus$view");
                if (fxn != null) po.addFxn("getRemoteStatus$view", (Proto.Fxn)om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$getRemoteStatus$view", "ti.sdo.ipc.gates"), fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Instance", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateMPSupportNull.Instance", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport.Instance", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull$$Params", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateMPSupportNull.Params", om.findStrict("ti.sdo.ipc.interfaces.IGateMPSupport$$Params", "ti.sdo.ipc.gates"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.gates"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull$$Object", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateMPSupportNull.Object", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Instance", "ti.sdo.ipc.gates"));
        // struct GateMPSupportNull.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull$$Instance_State", "ti.sdo.ipc.gates");
        po.init("ti.sdo.ipc.gates.GateMPSupportNull.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("resourceId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void GateAAMonitor$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor$$Instance_State", "ti.sdo.ipc.gates");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.gates.GateAAMonitor.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor$$Instance_State", "ti.sdo.ipc.gates");
    }

    void GateHWSem$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem$$Instance_State", "ti.sdo.ipc.gates");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.gates.GateHWSem.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem$$Instance_State", "ti.sdo.ipc.gates");
    }

    void GateHWSpinlock$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock$$Instance_State", "ti.sdo.ipc.gates");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.gates.GateHWSpinlock.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock$$Instance_State", "ti.sdo.ipc.gates");
    }

    void GatePeterson$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson$$Instance_State", "ti.sdo.ipc.gates");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.gates.GatePeterson.Attrs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson$$Attrs", "ti.sdo.ipc.gates");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.gates.GatePeterson.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson$$Instance_State", "ti.sdo.ipc.gates");
        po.bind("attrs$fetchDesc", Global.newObject("type", "ti.sdo.ipc.gates.GatePeterson.Attrs", "isScalar", false));
    }

    void GatePetersonN$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN$$Instance_State", "ti.sdo.ipc.gates");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.gates.GatePetersonN.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN$$Instance_State", "ti.sdo.ipc.gates");
    }

    void GateMPSupportNull$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull$$Instance_State", "ti.sdo.ipc.gates");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.gates.GateMPSupportNull.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull$$Instance_State", "ti.sdo.ipc.gates");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.gates.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.gates"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/gates/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.gates"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.gates"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.gates", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.gates");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.gates.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.gates'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.gates$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.gates$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.gates$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void GateAAMonitor$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Module", "ti.sdo.ipc.gates");
        vo.init2(po, "ti.sdo.ipc.gates.GateAAMonitor", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor$$capsule", "ti.sdo.ipc.gates"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Instance", "ti.sdo.ipc.gates"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Params", "ti.sdo.ipc.gates"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Params", "ti.sdo.ipc.gates")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Handle", "ti.sdo.ipc.gates"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.gates", "ti.sdo.ipc.gates"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.BasicView", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.BasicView", "ti.sdo.ipc.gates"));
        mcfgs.add("A_invSharedAddr");
        mcfgs.add("numInstances");
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Instance_State", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Instance_State", "ti.sdo.ipc.gates"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.gates")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.gates.GateAAMonitor$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$gates$GateAAMonitor$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.query", "ti.sdo.ipc.gates"));
        vo.bind("getReservedMask", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.getReservedMask", "ti.sdo.ipc.gates"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.sharedMemReq", "ti.sdo.ipc.gates"));
        vo.bind("getLock", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.getLock", "ti.sdo.ipc.gates"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_gates_GateAAMonitor_Handle__label__E", "ti_sdo_ipc_gates_GateAAMonitor_Module__startupDone__E", "ti_sdo_ipc_gates_GateAAMonitor_Object__create__E", "ti_sdo_ipc_gates_GateAAMonitor_Object__delete__E", "ti_sdo_ipc_gates_GateAAMonitor_Object__destruct__E", "ti_sdo_ipc_gates_GateAAMonitor_Object__get__E", "ti_sdo_ipc_gates_GateAAMonitor_Object__first__E", "ti_sdo_ipc_gates_GateAAMonitor_Object__next__E", "ti_sdo_ipc_gates_GateAAMonitor_Params__init__E", "ti_sdo_ipc_gates_GateAAMonitor_query__E", "ti_sdo_ipc_gates_GateAAMonitor_enter__E", "ti_sdo_ipc_gates_GateAAMonitor_leave__E", "ti_sdo_ipc_gates_GateAAMonitor_getReservedMask__E", "ti_sdo_ipc_gates_GateAAMonitor_sharedMemReq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_invSharedAddr"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.gates.GateAAMonitor.Object", "ti.sdo.ipc.gates"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("GateAAMonitor", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GateAAMonitor");
    }

    void GateHWSem$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem.Module", "ti.sdo.ipc.gates");
        vo.init2(po, "ti.sdo.ipc.gates.GateHWSem", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.gates.GateHWSem$$capsule", "ti.sdo.ipc.gates"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.gates.GateHWSem.Instance", "ti.sdo.ipc.gates"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.gates.GateHWSem.Params", "ti.sdo.ipc.gates"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.gates.GateHWSem.Params", "ti.sdo.ipc.gates")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.gates.GateHWSem.Handle", "ti.sdo.ipc.gates"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.gates", "ti.sdo.ipc.gates"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.gates.GateHWSem.BasicView", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GateHWSem.BasicView", "ti.sdo.ipc.gates"));
        mcfgs.add("A_invSemNum");
        mcfgs.add("baseAddr");
        icfgs.add("baseAddr");
        mcfgs.add("queryAddr");
        icfgs.add("queryAddr");
        mcfgs.add("numSems");
        icfgs.add("numSems");
        mcfgs.add("reservedMaskArr");
        icfgs.add("reservedMaskArr");
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.gates.GateHWSem.Instance_State", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GateHWSem.Instance_State", "ti.sdo.ipc.gates"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.gates")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.gates.GateHWSem$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$gates$GateHWSem$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("ti.sdo.ipc.gates.GateHWSem.query", "ti.sdo.ipc.gates"));
        vo.bind("getReservedMask", om.findStrict("ti.sdo.ipc.gates.GateHWSem.getReservedMask", "ti.sdo.ipc.gates"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.gates.GateHWSem.sharedMemReq", "ti.sdo.ipc.gates"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_gates_GateHWSem_Handle__label__E", "ti_sdo_ipc_gates_GateHWSem_Module__startupDone__E", "ti_sdo_ipc_gates_GateHWSem_Object__create__E", "ti_sdo_ipc_gates_GateHWSem_Object__delete__E", "ti_sdo_ipc_gates_GateHWSem_Object__destruct__E", "ti_sdo_ipc_gates_GateHWSem_Object__get__E", "ti_sdo_ipc_gates_GateHWSem_Object__first__E", "ti_sdo_ipc_gates_GateHWSem_Object__next__E", "ti_sdo_ipc_gates_GateHWSem_Params__init__E", "ti_sdo_ipc_gates_GateHWSem_query__E", "ti_sdo_ipc_gates_GateHWSem_getReservedMask__E", "ti_sdo_ipc_gates_GateHWSem_sharedMemReq__E", "ti_sdo_ipc_gates_GateHWSem_enter__E", "ti_sdo_ipc_gates_GateHWSem_leave__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_invSemNum"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.gates.GateHWSem.Object", "ti.sdo.ipc.gates"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("GateHWSem", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GateHWSem");
    }

    void GateHWSpinlock$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Module", "ti.sdo.ipc.gates");
        vo.init2(po, "ti.sdo.ipc.gates.GateHWSpinlock", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock$$capsule", "ti.sdo.ipc.gates"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Instance", "ti.sdo.ipc.gates"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Params", "ti.sdo.ipc.gates"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Params", "ti.sdo.ipc.gates")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Handle", "ti.sdo.ipc.gates"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.gates", "ti.sdo.ipc.gates"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.BasicView", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.BasicView", "ti.sdo.ipc.gates"));
        mcfgs.add("LM_enter");
        mcfgs.add("LM_leave");
        mcfgs.add("LM_create");
        mcfgs.add("LM_open");
        mcfgs.add("LM_delete");
        mcfgs.add("LM_close");
        mcfgs.add("A_invSpinLockNum");
        mcfgs.add("baseAddr");
        mcfgs.add("numLocks");
        icfgs.add("numLocks");
        mcfgs.add("reservedMaskArr");
        icfgs.add("reservedMaskArr");
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Instance_State", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Instance_State", "ti.sdo.ipc.gates"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.gates")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.gates.GateHWSpinlock$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$gates$GateHWSpinlock$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.query", "ti.sdo.ipc.gates"));
        vo.bind("getReservedMask", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.getReservedMask", "ti.sdo.ipc.gates"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.sharedMemReq", "ti.sdo.ipc.gates"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_gates_GateHWSpinlock_Handle__label__E", "ti_sdo_ipc_gates_GateHWSpinlock_Module__startupDone__E", "ti_sdo_ipc_gates_GateHWSpinlock_Object__create__E", "ti_sdo_ipc_gates_GateHWSpinlock_Object__delete__E", "ti_sdo_ipc_gates_GateHWSpinlock_Object__destruct__E", "ti_sdo_ipc_gates_GateHWSpinlock_Object__get__E", "ti_sdo_ipc_gates_GateHWSpinlock_Object__first__E", "ti_sdo_ipc_gates_GateHWSpinlock_Object__next__E", "ti_sdo_ipc_gates_GateHWSpinlock_Params__init__E", "ti_sdo_ipc_gates_GateHWSpinlock_query__E", "ti_sdo_ipc_gates_GateHWSpinlock_getReservedMask__E", "ti_sdo_ipc_gates_GateHWSpinlock_sharedMemReq__E", "ti_sdo_ipc_gates_GateHWSpinlock_enter__E", "ti_sdo_ipc_gates_GateHWSpinlock_leave__E"));
        vo.bind("$$logEvtCfgs", Global.newArray("LM_enter", "LM_leave", "LM_create", "LM_open", "LM_delete", "LM_close"));
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_invSpinLockNum"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock.Object", "ti.sdo.ipc.gates"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("GateHWSpinlock", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GateHWSpinlock");
    }

    void GatePeterson$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson.Module", "ti.sdo.ipc.gates");
        vo.init2(po, "ti.sdo.ipc.gates.GatePeterson", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.gates.GatePeterson$$capsule", "ti.sdo.ipc.gates"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.gates.GatePeterson.Instance", "ti.sdo.ipc.gates"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.gates.GatePeterson.Params", "ti.sdo.ipc.gates"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.gates.GatePeterson.Params", "ti.sdo.ipc.gates")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.gates.GatePeterson.Handle", "ti.sdo.ipc.gates"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.gates", "ti.sdo.ipc.gates"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.gates.GatePeterson.BasicView", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GatePeterson.BasicView", "ti.sdo.ipc.gates"));
        mcfgs.add("E_gateRemotelyOpened");
        mcfgs.add("numInstances");
        vo.bind("Attrs", om.findStrict("ti.sdo.ipc.gates.GatePeterson.Attrs", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GatePeterson.Attrs", "ti.sdo.ipc.gates"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.gates.GatePeterson.Instance_State", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GatePeterson.Instance_State", "ti.sdo.ipc.gates"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.gates")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.gates.GatePeterson$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$gates$GatePeterson$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("ti.sdo.ipc.gates.GatePeterson.query", "ti.sdo.ipc.gates"));
        vo.bind("getReservedMask", om.findStrict("ti.sdo.ipc.gates.GatePeterson.getReservedMask", "ti.sdo.ipc.gates"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.gates.GatePeterson.sharedMemReq", "ti.sdo.ipc.gates"));
        vo.bind("postInit", om.findStrict("ti.sdo.ipc.gates.GatePeterson.postInit", "ti.sdo.ipc.gates"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_gates_GatePeterson_Handle__label__E", "ti_sdo_ipc_gates_GatePeterson_Module__startupDone__E", "ti_sdo_ipc_gates_GatePeterson_Object__create__E", "ti_sdo_ipc_gates_GatePeterson_Object__delete__E", "ti_sdo_ipc_gates_GatePeterson_Object__destruct__E", "ti_sdo_ipc_gates_GatePeterson_Object__get__E", "ti_sdo_ipc_gates_GatePeterson_Object__first__E", "ti_sdo_ipc_gates_GatePeterson_Object__next__E", "ti_sdo_ipc_gates_GatePeterson_Params__init__E", "ti_sdo_ipc_gates_GatePeterson_query__E", "ti_sdo_ipc_gates_GatePeterson_getReservedMask__E", "ti_sdo_ipc_gates_GatePeterson_sharedMemReq__E", "ti_sdo_ipc_gates_GatePeterson_enter__E", "ti_sdo_ipc_gates_GatePeterson_leave__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_gateRemotelyOpened"));
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.gates.GatePeterson.Object", "ti.sdo.ipc.gates"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("GatePeterson", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GatePeterson");
    }

    void GatePetersonN$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Module", "ti.sdo.ipc.gates");
        vo.init2(po, "ti.sdo.ipc.gates.GatePetersonN", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.gates.GatePetersonN$$capsule", "ti.sdo.ipc.gates"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Instance", "ti.sdo.ipc.gates"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Params", "ti.sdo.ipc.gates"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Params", "ti.sdo.ipc.gates")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Handle", "ti.sdo.ipc.gates"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.gates", "ti.sdo.ipc.gates"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.BasicView", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GatePetersonN.BasicView", "ti.sdo.ipc.gates"));
        mcfgs.add("numInstances");
        mcfgs.add("MAX_NUM_PROCS");
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Instance_State", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Instance_State", "ti.sdo.ipc.gates"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.gates")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.gates.GatePetersonN$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$gates$GatePetersonN$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.query", "ti.sdo.ipc.gates"));
        vo.bind("getReservedMask", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.getReservedMask", "ti.sdo.ipc.gates"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.sharedMemReq", "ti.sdo.ipc.gates"));
        vo.bind("postInit", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.postInit", "ti.sdo.ipc.gates"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_gates_GatePetersonN_Handle__label__E", "ti_sdo_ipc_gates_GatePetersonN_Module__startupDone__E", "ti_sdo_ipc_gates_GatePetersonN_Object__create__E", "ti_sdo_ipc_gates_GatePetersonN_Object__delete__E", "ti_sdo_ipc_gates_GatePetersonN_Object__destruct__E", "ti_sdo_ipc_gates_GatePetersonN_Object__get__E", "ti_sdo_ipc_gates_GatePetersonN_Object__first__E", "ti_sdo_ipc_gates_GatePetersonN_Object__next__E", "ti_sdo_ipc_gates_GatePetersonN_Params__init__E", "ti_sdo_ipc_gates_GatePetersonN_query__E", "ti_sdo_ipc_gates_GatePetersonN_getReservedMask__E", "ti_sdo_ipc_gates_GatePetersonN_sharedMemReq__E", "ti_sdo_ipc_gates_GatePetersonN_enter__E", "ti_sdo_ipc_gates_GatePetersonN_leave__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.gates.GatePetersonN.Object", "ti.sdo.ipc.gates"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("GatePetersonN", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GatePetersonN");
    }

    void GateMPSupportNull$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull", "ti.sdo.ipc.gates");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Module", "ti.sdo.ipc.gates");
        vo.init2(po, "ti.sdo.ipc.gates.GateMPSupportNull", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull$$capsule", "ti.sdo.ipc.gates"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Instance", "ti.sdo.ipc.gates"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Params", "ti.sdo.ipc.gates"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Params", "ti.sdo.ipc.gates")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Handle", "ti.sdo.ipc.gates"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.gates", "ti.sdo.ipc.gates"));
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
        mcfgs.add("A_invalidAction");
        vo.bind("Action", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Action", "ti.sdo.ipc.gates"));
        mcfgs.add("action");
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Instance_State", "ti.sdo.ipc.gates"));
        tdefs.add(om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Instance_State", "ti.sdo.ipc.gates"));
        vo.bind("Action_NONE", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Action_NONE", "ti.sdo.ipc.gates"));
        vo.bind("Action_ASSERT", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Action_ASSERT", "ti.sdo.ipc.gates"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.gates")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.gates.GateMPSupportNull$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$gates$GateMPSupportNull$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.query", "ti.sdo.ipc.gates"));
        vo.bind("getReservedMask", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.getReservedMask", "ti.sdo.ipc.gates"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.sharedMemReq", "ti.sdo.ipc.gates"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_gates_GateMPSupportNull_Handle__label__E", "ti_sdo_ipc_gates_GateMPSupportNull_Module__startupDone__E", "ti_sdo_ipc_gates_GateMPSupportNull_Object__create__E", "ti_sdo_ipc_gates_GateMPSupportNull_Object__delete__E", "ti_sdo_ipc_gates_GateMPSupportNull_Object__destruct__E", "ti_sdo_ipc_gates_GateMPSupportNull_Object__get__E", "ti_sdo_ipc_gates_GateMPSupportNull_Object__first__E", "ti_sdo_ipc_gates_GateMPSupportNull_Object__next__E", "ti_sdo_ipc_gates_GateMPSupportNull_Params__init__E", "ti_sdo_ipc_gates_GateMPSupportNull_query__E", "ti_sdo_ipc_gates_GateMPSupportNull_getReservedMask__E", "ti_sdo_ipc_gates_GateMPSupportNull_sharedMemReq__E", "ti_sdo_ipc_gates_GateMPSupportNull_enter__E", "ti_sdo_ipc_gates_GateMPSupportNull_leave__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_invalidAction"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull.Object", "ti.sdo.ipc.gates"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("GateMPSupportNull", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GateMPSupportNull");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sdo.ipc.gates")).findStrict("PARAMS", "ti.sdo.ipc.gates");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor", "ti.sdo.ipc.gates")).findStrict("PARAMS", "ti.sdo.ipc.gates");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.gates.GateHWSem", "ti.sdo.ipc.gates")).findStrict("PARAMS", "ti.sdo.ipc.gates");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock", "ti.sdo.ipc.gates")).findStrict("PARAMS", "ti.sdo.ipc.gates");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.gates.GatePeterson", "ti.sdo.ipc.gates")).findStrict("PARAMS", "ti.sdo.ipc.gates");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.gates.GatePetersonN", "ti.sdo.ipc.gates")).findStrict("PARAMS", "ti.sdo.ipc.gates");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull", "ti.sdo.ipc.gates")).findStrict("PARAMS", "ti.sdo.ipc.gates");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor", "ti.sdo.ipc.gates"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.gates.GateHWSem", "ti.sdo.ipc.gates"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock", "ti.sdo.ipc.gates"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.gates.GatePeterson", "ti.sdo.ipc.gates"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.gates.GatePetersonN", "ti.sdo.ipc.gates"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.gates.GateMPSupportNull", "ti.sdo.ipc.gates"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GateAAMonitor", "ti.sdo.ipc.gates");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSem", "ti.sdo.ipc.gates");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GateHWSpinlock", "ti.sdo.ipc.gates");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GatePeterson", "ti.sdo.ipc.gates");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.gates.GatePetersonN", "ti.sdo.ipc.gates");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.gates.GateAAMonitor")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.gates.GateHWSem")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.gates.GateHWSpinlock")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.gates.GatePeterson")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.gates.GatePetersonN")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.gates.GateMPSupportNull")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.gates")).add(pkgV);
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
        GateAAMonitor$$OBJECTS();
        GateHWSem$$OBJECTS();
        GateHWSpinlock$$OBJECTS();
        GatePeterson$$OBJECTS();
        GatePetersonN$$OBJECTS();
        GateMPSupportNull$$OBJECTS();
        GateAAMonitor$$CONSTS();
        GateHWSem$$CONSTS();
        GateHWSpinlock$$CONSTS();
        GatePeterson$$CONSTS();
        GatePetersonN$$CONSTS();
        GateMPSupportNull$$CONSTS();
        GateAAMonitor$$CREATES();
        GateHWSem$$CREATES();
        GateHWSpinlock$$CREATES();
        GatePeterson$$CREATES();
        GatePetersonN$$CREATES();
        GateMPSupportNull$$CREATES();
        GateAAMonitor$$FUNCTIONS();
        GateHWSem$$FUNCTIONS();
        GateHWSpinlock$$FUNCTIONS();
        GatePeterson$$FUNCTIONS();
        GatePetersonN$$FUNCTIONS();
        GateMPSupportNull$$FUNCTIONS();
        GateAAMonitor$$SIZES();
        GateHWSem$$SIZES();
        GateHWSpinlock$$SIZES();
        GatePeterson$$SIZES();
        GatePetersonN$$SIZES();
        GateMPSupportNull$$SIZES();
        GateAAMonitor$$TYPES();
        GateHWSem$$TYPES();
        GateHWSpinlock$$TYPES();
        GatePeterson$$TYPES();
        GatePetersonN$$TYPES();
        GateMPSupportNull$$TYPES();
        if (isROV) {
            GateAAMonitor$$ROV();
            GateHWSem$$ROV();
            GateHWSpinlock$$ROV();
            GatePeterson$$ROV();
            GatePetersonN$$ROV();
            GateMPSupportNull$$ROV();
        }//isROV
        $$SINGLETONS();
        GateAAMonitor$$SINGLETONS();
        GateHWSem$$SINGLETONS();
        GateHWSpinlock$$SINGLETONS();
        GatePeterson$$SINGLETONS();
        GatePetersonN$$SINGLETONS();
        GateMPSupportNull$$SINGLETONS();
        $$INITIALIZATION();
    }
}
