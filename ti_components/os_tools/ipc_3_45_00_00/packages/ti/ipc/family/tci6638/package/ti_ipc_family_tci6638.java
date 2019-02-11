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

public class ti_ipc_family_tci6638
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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.notifyDrivers");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.utils");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.gates");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.knl");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.interfaces");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.ipc.family.tci6638.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.ipc.family.tci6638", new Value.Obj("ti.ipc.family.tci6638", pkgP));
    }

    void Interrupt$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.family.tci6638.Interrupt.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.family.tci6638.Interrupt", new Value.Obj("ti.ipc.family.tci6638.Interrupt", po));
        pkgV.bind("Interrupt", vo);
        // decls 
        om.bind("ti.ipc.family.tci6638.Interrupt.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.ipc.family.tci6638"));
    }

    void VirtQueue$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.family.tci6638.VirtQueue.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.family.tci6638.VirtQueue", new Value.Obj("ti.ipc.family.tci6638.VirtQueue", po));
        pkgV.bind("VirtQueue", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.ipc.family.tci6638.VirtQueue$$BasicView", new Proto.Obj());
        om.bind("ti.ipc.family.tci6638.VirtQueue.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.ipc.family.tci6638.VirtQueue$$ModuleView", new Proto.Obj());
        om.bind("ti.ipc.family.tci6638.VirtQueue.ModuleView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.ipc.family.tci6638.VirtQueue$$Module_State", new Proto.Obj());
        om.bind("ti.ipc.family.tci6638.VirtQueue.Module_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.ipc.family.tci6638.VirtQueue$$Instance_State", new Proto.Obj());
        om.bind("ti.ipc.family.tci6638.VirtQueue.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.ipc.family.tci6638.VirtQueue.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.ipc.family.tci6638.VirtQueue$$Object", new Proto.Obj());
        om.bind("ti.ipc.family.tci6638.VirtQueue.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.ipc.family.tci6638.VirtQueue$$Params", new Proto.Obj());
        om.bind("ti.ipc.family.tci6638.VirtQueue.Params", new Proto.Str(po, false));
        om.bind("ti.ipc.family.tci6638.VirtQueue.Handle", insP);
        if (isROV) {
            om.bind("ti.ipc.family.tci6638.VirtQueue.Object", om.findStrict("ti.ipc.family.tci6638.VirtQueue.Instance_State", "ti.ipc.family.tci6638"));
        }//isROV
    }

    void NotifyCircSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.family.tci6638.NotifyCircSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.family.tci6638.NotifyCircSetup", new Value.Obj("ti.ipc.family.tci6638.NotifyCircSetup", po));
        pkgV.bind("NotifyCircSetup", vo);
        // decls 
    }

    void VirtQueue_InterruptProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.family.tci6638.VirtQueue_InterruptProxy", new Value.Obj("ti.ipc.family.tci6638.VirtQueue_InterruptProxy", po));
        pkgV.bind("VirtQueue_InterruptProxy", vo);
        // decls 
        om.bind("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.ipc.family.tci6638"));
    }

    void Interrupt$$CONSTS()
    {
        // module Interrupt
        om.bind("ti.ipc.family.tci6638.Interrupt.INVALIDPAYLOAD", 0xFFFFFFFFL);
        om.bind("ti.ipc.family.tci6638.Interrupt.SRCS_BITPOS_CORE0", 4L);
        om.bind("ti.ipc.family.tci6638.Interrupt.SRCS_BITPOS_HOST", 31L);
        om.bind("ti.ipc.family.tci6638.Interrupt.intEnable", new Extern("ti_ipc_family_tci6638_Interrupt_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.ipc.family.tci6638.Interrupt.intDisable", new Extern("ti_ipc_family_tci6638_Interrupt_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.ipc.family.tci6638.Interrupt.intRegister", new Extern("ti_ipc_family_tci6638_Interrupt_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.ipc.family.tci6638.Interrupt.intUnregister", new Extern("ti_ipc_family_tci6638_Interrupt_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.ipc.family.tci6638.Interrupt.intSend", new Extern("ti_ipc_family_tci6638_Interrupt_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.ipc.family.tci6638.Interrupt.intPost", new Extern("ti_ipc_family_tci6638_Interrupt_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.ipc.family.tci6638.Interrupt.intClear", new Extern("ti_ipc_family_tci6638_Interrupt_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.ipc.family.tci6638.Interrupt.intClearAll", new Extern("ti_ipc_family_tci6638_Interrupt_intClearAll__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.ipc.family.tci6638.Interrupt.checkAndClear", new Extern("ti_ipc_family_tci6638_Interrupt_checkAndClear__E", "xdc_UInt(*)(xdc_UInt16,ti_ipc_family_tci6638_Interrupt_IntInfo*)", true, false));
    }

    void VirtQueue$$CONSTS()
    {
        // module VirtQueue
        om.bind("ti.ipc.family.tci6638.VirtQueue.startup", new Extern("ti_ipc_family_tci6638_VirtQueue_startup__E", "xdc_Void(*)(xdc_UInt16,xdc_Bool)", true, false));
        om.bind("ti.ipc.family.tci6638.VirtQueue.cacheWb", new Extern("ti_ipc_family_tci6638_VirtQueue_cacheWb__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.ipc.family.tci6638.VirtQueue.init", new Extern("ti_ipc_family_tci6638_VirtQueue_init__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.ipc.family.tci6638.VirtQueue.hostIsr", new Extern("ti_ipc_family_tci6638_VirtQueue_hostIsr__I", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.ipc.family.tci6638.VirtQueue.slaveIsr", new Extern("ti_ipc_family_tci6638_VirtQueue_slaveIsr__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void NotifyCircSetup$$CONSTS()
    {
        // module NotifyCircSetup
        om.bind("ti.ipc.family.tci6638.NotifyCircSetup.SRCS_BITPOS_CORE0", 4L);
        om.bind("ti.ipc.family.tci6638.NotifyCircSetup.SRCS_BITPOS_HOST", 31L);
        om.bind("ti.ipc.family.tci6638.NotifyCircSetup.attach", new Extern("ti_ipc_family_tci6638_NotifyCircSetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.ipc.family.tci6638.NotifyCircSetup.sharedMemReq", new Extern("ti_ipc_family_tci6638_NotifyCircSetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.ipc.family.tci6638.NotifyCircSetup.numIntLines", new Extern("ti_ipc_family_tci6638_NotifyCircSetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void VirtQueue_InterruptProxy$$CONSTS()
    {
        // module VirtQueue_InterruptProxy
        om.bind("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intEnable", new Extern("ti_ipc_family_tci6638_VirtQueue_InterruptProxy_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intDisable", new Extern("ti_ipc_family_tci6638_VirtQueue_InterruptProxy_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intRegister", new Extern("ti_ipc_family_tci6638_VirtQueue_InterruptProxy_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intUnregister", new Extern("ti_ipc_family_tci6638_VirtQueue_InterruptProxy_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intSend", new Extern("ti_ipc_family_tci6638_VirtQueue_InterruptProxy_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intPost", new Extern("ti_ipc_family_tci6638_VirtQueue_InterruptProxy_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intClear", new Extern("ti_ipc_family_tci6638_VirtQueue_InterruptProxy_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
    }

    void Interrupt$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VirtQueue$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$ipc$family$tci6638$VirtQueue$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.ipc.family.tci6638.VirtQueue.create() called before xdc.useModule('ti.ipc.family.tci6638.VirtQueue')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.remoteProcId, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.ipc.family.tci6638.VirtQueue$$create", new Proto.Fxn(om.findStrict("ti.ipc.family.tci6638.VirtQueue.Module", "ti.ipc.family.tci6638"), om.findStrict("ti.ipc.family.tci6638.VirtQueue.Instance", "ti.ipc.family.tci6638"), 2, 1, false));
                        fxn.addArg(0, "remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.ipc.family.tci6638.VirtQueue.Params", "ti.ipc.family.tci6638"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$ipc$family$tci6638$VirtQueue$$create = function( remoteProcId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.ipc.family.tci6638.VirtQueue'];\n");
                sb.append("var __inst = xdc.om['ti.ipc.family.tci6638.VirtQueue.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.ipc.family.tci6638']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {remoteProcId:remoteProcId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.ipc.family.tci6638.VirtQueue'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [remoteProcId]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.ipc.family.tci6638.VirtQueue'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.ipc.family.tci6638.VirtQueue$$construct", new Proto.Fxn(om.findStrict("ti.ipc.family.tci6638.VirtQueue.Module", "ti.ipc.family.tci6638"), null, 3, 1, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.ipc.family.tci6638.VirtQueue$$Object", "ti.ipc.family.tci6638"), null);
                        fxn.addArg(1, "remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.ipc.family.tci6638.VirtQueue.Params", "ti.ipc.family.tci6638"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$ipc$family$tci6638$VirtQueue$$construct = function( __obj, remoteProcId, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.ipc.family.tci6638.VirtQueue'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {remoteProcId:remoteProcId});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.ipc.family.tci6638.VirtQueue'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.ipc.family.tci6638.VirtQueue'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void NotifyCircSetup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VirtQueue_InterruptProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Interrupt$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VirtQueue$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifyCircSetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VirtQueue_InterruptProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Interrupt$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void VirtQueue$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.ipc.family.tci6638.VirtQueue.Module_State", "ti.ipc.family.tci6638");
        sizes.clear();
        sizes.add(Global.newArray("hostSlaveSynced", "UInt16"));
        sizes.add(Global.newArray("virtQueueInitialized", "UInt16"));
        sizes.add(Global.newArray("queueRegistry", "UPtr"));
        sizes.add(Global.newArray("traceBufPtr", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.ipc.family.tci6638.VirtQueue.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.ipc.family.tci6638.VirtQueue.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.ipc.family.tci6638.VirtQueue.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.ipc.family.tci6638.VirtQueue.Instance_State", "ti.ipc.family.tci6638");
        sizes.clear();
        sizes.add(Global.newArray("hostSlaveSynced", "UShort"));
        sizes.add(Global.newArray("id", "UInt16"));
        sizes.add(Global.newArray("callback", "UFxn"));
        sizes.add(Global.newArray("swiHandle", "UPtr"));
        sizes.add(Global.newArray("vringPtr", "UPtr"));
        sizes.add(Global.newArray("num_free", "UInt16"));
        sizes.add(Global.newArray("last_avail_idx", "UInt16"));
        sizes.add(Global.newArray("last_used_idx", "UInt16"));
        sizes.add(Global.newArray("procId", "UInt16"));
        sizes.add(Global.newArray("gateH", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.ipc.family.tci6638.VirtQueue.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.ipc.family.tci6638.VirtQueue.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.ipc.family.tci6638.VirtQueue.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NotifyCircSetup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void VirtQueue_InterruptProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Interrupt$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/family/tci6638/Interrupt.xs");
        om.bind("ti.ipc.family.tci6638.Interrupt$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.Interrupt.Module", "ti.ipc.family.tci6638");
        po.init("ti.ipc.family.tci6638.Interrupt.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.ipc.family.tci6638"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("INVALIDPAYLOAD", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFFFFFL, "rh");
                po.addFld("SRCS_BITPOS_CORE0", Proto.Elm.newCNum("(xdc_UInt)"), 4L, "rh");
                po.addFld("SRCS_BITPOS_HOST", Proto.Elm.newCNum("(xdc_UInt)"), 31L, "rh");
        if (isCFG) {
            po.addFld("enableKick", $$T_Bool, true, "w");
            po.addFld("A_notImplemented", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.ipc.family.tci6638"), Global.newObject("msg", "A_notImplemented: this function is not implemented"), "w");
            po.addFld("IPCGR0", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("IPCAR0", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("IPCGRH", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("IPCARH", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("KICK0", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("KICK1", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
            po.addFld("INTERDSPINT", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("-1"), "w");
            po.addFld("DSPINT", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("-1"), "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.Interrupt$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.Interrupt$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.Interrupt$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.Interrupt$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void VirtQueue$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/family/tci6638/VirtQueue.xs");
        om.bind("ti.ipc.family.tci6638.VirtQueue$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue.Module", "ti.ipc.family.tci6638");
        po.init("ti.ipc.family.tci6638.VirtQueue.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.ipc.family.tci6638"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFldV("InterruptProxy", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.ipc.family.tci6638"), null, "wh", $$delegGet, $$delegSet);
            po.addFld("VRING_OFFSET", Proto.Elm.newCNum("(xdc_UInt32)"), 0x00080000L, "w");
            po.addFld("VQ0_SIZE", Proto.Elm.newCNum("(xdc_UInt)"), 256L, "w");
            po.addFld("VQ1_SIZE", Proto.Elm.newCNum("(xdc_UInt)"), 256L, "w");
            po.addFld("RP_MSG_NUM_BUFS", Proto.Elm.newCNum("(xdc_UInt)"), 256L, "w");
            po.addFld("PAGE_SIZE", Proto.Elm.newCNum("(xdc_UInt)"), 4096L, "w");
            po.addFld("RP_MSG_VRING_ALIGN", Proto.Elm.newCNum("(xdc_UInt)"), 4096L, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.ipc.family.tci6638.VirtQueue$$create", "ti.ipc.family.tci6638"), Global.get("ti$ipc$family$tci6638$VirtQueue$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.ipc.family.tci6638.VirtQueue$$construct", "ti.ipc.family.tci6638"), Global.get("ti$ipc$family$tci6638$VirtQueue$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.VirtQueue$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.VirtQueue$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.VirtQueue$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.VirtQueue$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.VirtQueue$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.VirtQueue$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue.Instance", "ti.ipc.family.tci6638");
        po.init("ti.ipc.family.tci6638.VirtQueue.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("host", $$T_Bool, false, "w");
            po.addFld("callback", new Proto.Adr("xdc_Fxn", "Pf"), null, "w");
            po.addFld("swiHandle", (Proto)om.findStrict("ti.sysbios.knl.Swi.Handle", "ti.ipc.family.tci6638"), null, "w");
            po.addFld("intVectorId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~1"), "w");
            po.addFld("vqId", Proto.Elm.newCNum("(xdc_Int)"), 0L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.ipc.family.tci6638"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue$$Params", "ti.ipc.family.tci6638");
        po.init("ti.ipc.family.tci6638.VirtQueue.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("host", $$T_Bool, false, "w");
            po.addFld("callback", new Proto.Adr("xdc_Fxn", "Pf"), null, "w");
            po.addFld("swiHandle", (Proto)om.findStrict("ti.sysbios.knl.Swi.Handle", "ti.ipc.family.tci6638"), null, "w");
            po.addFld("intVectorId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~1"), "w");
            po.addFld("vqId", Proto.Elm.newCNum("(xdc_Int)"), 0L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.ipc.family.tci6638"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue$$Object", "ti.ipc.family.tci6638");
        po.init("ti.ipc.family.tci6638.VirtQueue.Object", om.findStrict("ti.ipc.family.tci6638.VirtQueue.Instance", "ti.ipc.family.tci6638"));
        // struct VirtQueue.BasicView
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue$$BasicView", "ti.ipc.family.tci6638");
        po.init("ti.ipc.family.tci6638.VirtQueue.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        // struct VirtQueue.ModuleView
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue$$ModuleView", "ti.ipc.family.tci6638");
        po.init("ti.ipc.family.tci6638.VirtQueue.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        // struct VirtQueue.Module_State
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue$$Module_State", "ti.ipc.family.tci6638");
        po.init("ti.ipc.family.tci6638.VirtQueue.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("hostSlaveSynced", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("virtQueueInitialized", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("queueRegistry", new Proto.Adr("xdc_UInt32*", "Pn"), $$UNDEF, "w");
                po.addFld("traceBufPtr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct VirtQueue.Instance_State
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue$$Instance_State", "ti.ipc.family.tci6638");
        po.init("ti.ipc.family.tci6638.VirtQueue.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("hostSlaveSynced", $$T_Bool, $$UNDEF, "w");
                po.addFld("id", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("callback", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("swiHandle", (Proto)om.findStrict("ti.sysbios.knl.Swi.Handle", "ti.ipc.family.tci6638"), $$UNDEF, "w");
                po.addFld("vringPtr", new Proto.Adr("xdc_Void*", "Pv"), $$UNDEF, "w");
                po.addFld("num_free", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("last_avail_idx", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("last_used_idx", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("gateH", (Proto)om.findStrict("ti.sysbios.gates.GateAll.Handle", "ti.ipc.family.tci6638"), $$UNDEF, "w");
    }

    void NotifyCircSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/family/tci6638/NotifyCircSetup.xs");
        om.bind("ti.ipc.family.tci6638.NotifyCircSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.NotifyCircSetup.Module", "ti.ipc.family.tci6638");
        po.init("ti.ipc.family.tci6638.NotifyCircSetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.ipc.family.tci6638"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("SRCS_BITPOS_CORE0", Proto.Elm.newCNum("(xdc_UInt)"), 4L, "rh");
                po.addFld("SRCS_BITPOS_HOST", Proto.Elm.newCNum("(xdc_UInt)"), 31L, "rh");
        if (isCFG) {
            po.addFld("dspIntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
            po.addFld("A_notImplemented", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.ipc.family.tci6638"), Global.newObject("msg", "A_notImplemented: this function is not implemented"), "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.NotifyCircSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.NotifyCircSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.NotifyCircSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.family.tci6638.NotifyCircSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void VirtQueue_InterruptProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.Module", "ti.ipc.family.tci6638");
        po.init("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.ipc.family.tci6638"));
                po.addFld("delegate$", (Proto)om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.ipc.family.tci6638"), null, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void Interrupt$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.family.tci6638.Interrupt", "ti.ipc.family.tci6638");
    }

    void VirtQueue$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue", "ti.ipc.family.tci6638");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.ipc.family.tci6638.VirtQueue.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue$$Module_State", "ti.ipc.family.tci6638");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.ipc.family.tci6638.VirtQueue.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue$$Instance_State", "ti.ipc.family.tci6638");
    }

    void NotifyCircSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.family.tci6638.NotifyCircSetup", "ti.ipc.family.tci6638");
    }

    void VirtQueue_InterruptProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy", "ti.ipc.family.tci6638");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.ipc.family.tci6638.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.ipc.family.tci6638"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/family/tci6638/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.ipc.family.tci6638"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.ipc.family.tci6638"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.ipc.family.tci6638"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.ipc.family.tci6638"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.ipc.family.tci6638"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.ipc.family.tci6638"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.ipc.family.tci6638", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.ipc.family.tci6638");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.ipc.family.tci6638.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.ipc.family.tci6638'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.ipc.family.tci6638$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.ipc.family.tci6638$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.ipc.family.tci6638$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Interrupt$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.family.tci6638.Interrupt", "ti.ipc.family.tci6638");
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.Interrupt.Module", "ti.ipc.family.tci6638");
        vo.init2(po, "ti.ipc.family.tci6638.Interrupt", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.family.tci6638.Interrupt$$capsule", "ti.ipc.family.tci6638"));
        vo.bind("$package", om.findStrict("ti.ipc.family.tci6638", "ti.ipc.family.tci6638"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.ipc.family.tci6638"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.ipc.family.tci6638"));
        mcfgs.add("enableKick");
        mcfgs.add("A_notImplemented");
        mcfgs.add("IPCGR0");
        icfgs.add("IPCGR0");
        mcfgs.add("IPCAR0");
        icfgs.add("IPCAR0");
        mcfgs.add("IPCGRH");
        icfgs.add("IPCGRH");
        mcfgs.add("IPCARH");
        icfgs.add("IPCARH");
        mcfgs.add("KICK0");
        icfgs.add("KICK0");
        mcfgs.add("KICK1");
        icfgs.add("KICK1");
        mcfgs.add("INTERDSPINT");
        icfgs.add("INTERDSPINT");
        mcfgs.add("DSPINT");
        icfgs.add("DSPINT");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.family.tci6638")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.ipc.family.tci6638.Interrupt.intEnable", "ti.ipc.family.tci6638"));
        vo.bind("intDisable", om.findStrict("ti.ipc.family.tci6638.Interrupt.intDisable", "ti.ipc.family.tci6638"));
        vo.bind("intRegister", om.findStrict("ti.ipc.family.tci6638.Interrupt.intRegister", "ti.ipc.family.tci6638"));
        vo.bind("intUnregister", om.findStrict("ti.ipc.family.tci6638.Interrupt.intUnregister", "ti.ipc.family.tci6638"));
        vo.bind("intSend", om.findStrict("ti.ipc.family.tci6638.Interrupt.intSend", "ti.ipc.family.tci6638"));
        vo.bind("intPost", om.findStrict("ti.ipc.family.tci6638.Interrupt.intPost", "ti.ipc.family.tci6638"));
        vo.bind("intClear", om.findStrict("ti.ipc.family.tci6638.Interrupt.intClear", "ti.ipc.family.tci6638"));
        vo.bind("intClearAll", om.findStrict("ti.ipc.family.tci6638.Interrupt.intClearAll", "ti.ipc.family.tci6638"));
        vo.bind("checkAndClear", om.findStrict("ti.ipc.family.tci6638.Interrupt.checkAndClear", "ti.ipc.family.tci6638"));
        vo.bind("$$fxntab", Global.newArray("ti_ipc_family_tci6638_Interrupt_Module__startupDone__E", "ti_ipc_family_tci6638_Interrupt_intEnable__E", "ti_ipc_family_tci6638_Interrupt_intDisable__E", "ti_ipc_family_tci6638_Interrupt_intRegister__E", "ti_ipc_family_tci6638_Interrupt_intUnregister__E", "ti_ipc_family_tci6638_Interrupt_intSend__E", "ti_ipc_family_tci6638_Interrupt_intPost__E", "ti_ipc_family_tci6638_Interrupt_intClear__E", "ti_ipc_family_tci6638_Interrupt_intClearAll__E", "ti_ipc_family_tci6638_Interrupt_checkAndClear__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_notImplemented"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "intClearAll", "entry", "", "exit", ""));
        loggables.add(Global.newObject("name", "checkAndClear", "entry", "0x%x, %p", "exit", "0x%x"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Interrupt", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Interrupt");
    }

    void VirtQueue$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue", "ti.ipc.family.tci6638");
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue.Module", "ti.ipc.family.tci6638");
        vo.init2(po, "ti.ipc.family.tci6638.VirtQueue", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.family.tci6638.VirtQueue$$capsule", "ti.ipc.family.tci6638"));
        vo.bind("Instance", om.findStrict("ti.ipc.family.tci6638.VirtQueue.Instance", "ti.ipc.family.tci6638"));
        vo.bind("Params", om.findStrict("ti.ipc.family.tci6638.VirtQueue.Params", "ti.ipc.family.tci6638"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.ipc.family.tci6638.VirtQueue.Params", "ti.ipc.family.tci6638")).newInstance());
        vo.bind("Handle", om.findStrict("ti.ipc.family.tci6638.VirtQueue.Handle", "ti.ipc.family.tci6638"));
        vo.bind("$package", om.findStrict("ti.ipc.family.tci6638", "ti.ipc.family.tci6638"));
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
        vo.bind("BasicView", om.findStrict("ti.ipc.family.tci6638.VirtQueue.BasicView", "ti.ipc.family.tci6638"));
        tdefs.add(om.findStrict("ti.ipc.family.tci6638.VirtQueue.BasicView", "ti.ipc.family.tci6638"));
        vo.bind("ModuleView", om.findStrict("ti.ipc.family.tci6638.VirtQueue.ModuleView", "ti.ipc.family.tci6638"));
        tdefs.add(om.findStrict("ti.ipc.family.tci6638.VirtQueue.ModuleView", "ti.ipc.family.tci6638"));
        vo.bind("InterruptProxy$proxy", om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy", "ti.ipc.family.tci6638"));
        proxies.add("InterruptProxy");
        mcfgs.add("VRING_OFFSET");
        mcfgs.add("VQ0_SIZE");
        mcfgs.add("VQ1_SIZE");
        mcfgs.add("RP_MSG_NUM_BUFS");
        mcfgs.add("PAGE_SIZE");
        mcfgs.add("RP_MSG_VRING_ALIGN");
        vo.bind("Module_State", om.findStrict("ti.ipc.family.tci6638.VirtQueue.Module_State", "ti.ipc.family.tci6638"));
        tdefs.add(om.findStrict("ti.ipc.family.tci6638.VirtQueue.Module_State", "ti.ipc.family.tci6638"));
        vo.bind("Instance_State", om.findStrict("ti.ipc.family.tci6638.VirtQueue.Instance_State", "ti.ipc.family.tci6638"));
        tdefs.add(om.findStrict("ti.ipc.family.tci6638.VirtQueue.Instance_State", "ti.ipc.family.tci6638"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.family.tci6638")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.ipc.family.tci6638.VirtQueue$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$ipc$family$tci6638$VirtQueue$$__initObject"));
        }//isCFG
        vo.bind("startup", om.findStrict("ti.ipc.family.tci6638.VirtQueue.startup", "ti.ipc.family.tci6638"));
        vo.bind("cacheWb", om.findStrict("ti.ipc.family.tci6638.VirtQueue.cacheWb", "ti.ipc.family.tci6638"));
        vo.bind("init", om.findStrict("ti.ipc.family.tci6638.VirtQueue.init", "ti.ipc.family.tci6638"));
        vo.bind("hostIsr", om.findStrict("ti.ipc.family.tci6638.VirtQueue.hostIsr", "ti.ipc.family.tci6638"));
        vo.bind("slaveIsr", om.findStrict("ti.ipc.family.tci6638.VirtQueue.slaveIsr", "ti.ipc.family.tci6638"));
        vo.bind("$$fxntab", Global.newArray("ti_ipc_family_tci6638_VirtQueue_Handle__label__E", "ti_ipc_family_tci6638_VirtQueue_Module__startupDone__E", "ti_ipc_family_tci6638_VirtQueue_Object__create__E", "ti_ipc_family_tci6638_VirtQueue_Object__delete__E", "ti_ipc_family_tci6638_VirtQueue_Object__destruct__E", "ti_ipc_family_tci6638_VirtQueue_Object__get__E", "ti_ipc_family_tci6638_VirtQueue_Object__first__E", "ti_ipc_family_tci6638_VirtQueue_Object__next__E", "ti_ipc_family_tci6638_VirtQueue_Params__init__E", "ti_ipc_family_tci6638_VirtQueue_startup__E", "ti_ipc_family_tci6638_VirtQueue_cacheWb__E", "ti_ipc_family_tci6638_VirtQueue_kick__E", "ti_ipc_family_tci6638_VirtQueue_isSlave__E", "ti_ipc_family_tci6638_VirtQueue_isHost__E", "ti_ipc_family_tci6638_VirtQueue_getId__E", "ti_ipc_family_tci6638_VirtQueue_getSwiHandle__E", "ti_ipc_family_tci6638_VirtQueue_addAvailBuf__E", "ti_ipc_family_tci6638_VirtQueue_getUsedBuf__E", "ti_ipc_family_tci6638_VirtQueue_getAvailBuf__E", "ti_ipc_family_tci6638_VirtQueue_addUsedBuf__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VirtQueue.xdt");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.ipc.family.tci6638.VirtQueue.Object", "ti.ipc.family.tci6638"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "startup", "entry", "0x%x, %d", "exit", ""));
        loggables.add(Global.newObject("name", "cacheWb", "entry", "", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./VirtQueue.xdt");
        pkgV.bind("VirtQueue", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VirtQueue");
    }

    void NotifyCircSetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.family.tci6638.NotifyCircSetup", "ti.ipc.family.tci6638");
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.NotifyCircSetup.Module", "ti.ipc.family.tci6638");
        vo.init2(po, "ti.ipc.family.tci6638.NotifyCircSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.family.tci6638.NotifyCircSetup$$capsule", "ti.ipc.family.tci6638"));
        vo.bind("$package", om.findStrict("ti.ipc.family.tci6638", "ti.ipc.family.tci6638"));
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
        mcfgs.add("dspIntVectId");
        mcfgs.add("A_notImplemented");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.family.tci6638")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.ipc.family.tci6638.NotifyCircSetup.attach", "ti.ipc.family.tci6638"));
        vo.bind("sharedMemReq", om.findStrict("ti.ipc.family.tci6638.NotifyCircSetup.sharedMemReq", "ti.ipc.family.tci6638"));
        vo.bind("numIntLines", om.findStrict("ti.ipc.family.tci6638.NotifyCircSetup.numIntLines", "ti.ipc.family.tci6638"));
        vo.bind("$$fxntab", Global.newArray("ti_ipc_family_tci6638_NotifyCircSetup_Module__startupDone__E", "ti_ipc_family_tci6638_NotifyCircSetup_attach__E", "ti_ipc_family_tci6638_NotifyCircSetup_sharedMemReq__E", "ti_ipc_family_tci6638_NotifyCircSetup_numIntLines__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_notImplemented"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NotifyCircSetup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifyCircSetup");
    }

    void VirtQueue_InterruptProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy", "ti.ipc.family.tci6638");
        po = (Proto.Obj)om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.Module", "ti.ipc.family.tci6638");
        vo.init2(po, "ti.ipc.family.tci6638.VirtQueue_InterruptProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.ipc.family.tci6638", "ti.ipc.family.tci6638"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        inherits.clear();
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.ipc.family.tci6638"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.ipc.family.tci6638"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.family.tci6638")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intEnable", "ti.ipc.family.tci6638"));
        vo.bind("intDisable", om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intDisable", "ti.ipc.family.tci6638"));
        vo.bind("intRegister", om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intRegister", "ti.ipc.family.tci6638"));
        vo.bind("intUnregister", om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intUnregister", "ti.ipc.family.tci6638"));
        vo.bind("intSend", om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intSend", "ti.ipc.family.tci6638"));
        vo.bind("intPost", om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intPost", "ti.ipc.family.tci6638"));
        vo.bind("intClear", om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy.intClear", "ti.ipc.family.tci6638"));
        vo.bind("$$fxntab", Global.newArray("ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__Handle__label", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__Module__startupDone", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__Object__create", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__Object__delete", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__Object__destruct", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__Object__get", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__Object__first", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__Object__next", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__Params__init", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__Proxy__abstract", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__Proxy__delegate", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__intEnable", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__intDisable", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__intRegister", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__intUnregister", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__intSend", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__intPost", "ti_ipc_family_tci6638_VirtQueue_InterruptProxy_DELEGATE__intClear"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("VirtQueue_InterruptProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VirtQueue_InterruptProxy");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.ipc.family.tci6638")).findStrict("PARAMS", "ti.ipc.family.tci6638");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.ipc.family.tci6638.VirtQueue", "ti.ipc.family.tci6638")).findStrict("PARAMS", "ti.ipc.family.tci6638");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.family.tci6638.Interrupt", "ti.ipc.family.tci6638"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.family.tci6638.VirtQueue", "ti.ipc.family.tci6638"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.family.tci6638.NotifyCircSetup", "ti.ipc.family.tci6638"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.family.tci6638.VirtQueue_InterruptProxy", "ti.ipc.family.tci6638"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.ipc.family.tci6638.Interrupt")).bless();
        ((Value.Obj)om.getv("ti.ipc.family.tci6638.VirtQueue")).bless();
        ((Value.Obj)om.getv("ti.ipc.family.tci6638.NotifyCircSetup")).bless();
        ((Value.Obj)om.getv("ti.ipc.family.tci6638.VirtQueue_InterruptProxy")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.ipc.family.tci6638")).add(pkgV);
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
        Interrupt$$OBJECTS();
        VirtQueue$$OBJECTS();
        NotifyCircSetup$$OBJECTS();
        VirtQueue_InterruptProxy$$OBJECTS();
        Interrupt$$CONSTS();
        VirtQueue$$CONSTS();
        NotifyCircSetup$$CONSTS();
        VirtQueue_InterruptProxy$$CONSTS();
        Interrupt$$CREATES();
        VirtQueue$$CREATES();
        NotifyCircSetup$$CREATES();
        VirtQueue_InterruptProxy$$CREATES();
        Interrupt$$FUNCTIONS();
        VirtQueue$$FUNCTIONS();
        NotifyCircSetup$$FUNCTIONS();
        VirtQueue_InterruptProxy$$FUNCTIONS();
        Interrupt$$SIZES();
        VirtQueue$$SIZES();
        NotifyCircSetup$$SIZES();
        VirtQueue_InterruptProxy$$SIZES();
        Interrupt$$TYPES();
        VirtQueue$$TYPES();
        NotifyCircSetup$$TYPES();
        VirtQueue_InterruptProxy$$TYPES();
        if (isROV) {
            Interrupt$$ROV();
            VirtQueue$$ROV();
            NotifyCircSetup$$ROV();
            VirtQueue_InterruptProxy$$ROV();
        }//isROV
        $$SINGLETONS();
        Interrupt$$SINGLETONS();
        VirtQueue$$SINGLETONS();
        NotifyCircSetup$$SINGLETONS();
        VirtQueue_InterruptProxy$$SINGLETONS();
        $$INITIALIZATION();
    }
}
