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

public class ti_sdo_ipc_family_omap4430
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
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.utils");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.interfaces");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.notifyDrivers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.family.omap4430.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.family.omap4430", new Value.Obj("ti.sdo.ipc.family.omap4430", pkgP));
    }

    void NotifySetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.omap4430.NotifySetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.omap4430.NotifySetup", new Value.Obj("ti.sdo.ipc.family.omap4430.NotifySetup", po));
        pkgV.bind("NotifySetup", vo);
        // decls 
    }

    void NotifyCircSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.omap4430.NotifyCircSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.omap4430.NotifyCircSetup", new Value.Obj("ti.sdo.ipc.family.omap4430.NotifyCircSetup", po));
        pkgV.bind("NotifyCircSetup", vo);
        // decls 
    }

    void InterruptDsp$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp", new Value.Obj("ti.sdo.ipc.family.omap4430.InterruptDsp", po));
        pkgV.bind("InterruptDsp", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.omap4430"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp$$FxnTable", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.FxnTable", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.Module_State", new Proto.Str(spo, false));
    }

    void InterruptDucati$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati", new Value.Obj("ti.sdo.ipc.family.omap4430.InterruptDucati", po));
        pkgV.bind("InterruptDucati", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.omap4430"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati$$FxnTable", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.FxnTable", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.Module_State", new Proto.Str(spo, false));
    }

    void NotifySetup$$CONSTS()
    {
        // module NotifySetup
        om.bind("ti.sdo.ipc.family.omap4430.NotifySetup.attach", new Extern("ti_sdo_ipc_family_omap4430_NotifySetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.NotifySetup.sharedMemReq", new Extern("ti_sdo_ipc_family_omap4430_NotifySetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.NotifySetup.numIntLines", new Extern("ti_sdo_ipc_family_omap4430_NotifySetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void NotifyCircSetup$$CONSTS()
    {
        // module NotifyCircSetup
        om.bind("ti.sdo.ipc.family.omap4430.NotifyCircSetup.attach", new Extern("ti_sdo_ipc_family_omap4430_NotifyCircSetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.NotifyCircSetup.sharedMemReq", new Extern("ti_sdo_ipc_family_omap4430_NotifyCircSetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.NotifyCircSetup.numIntLines", new Extern("ti_sdo_ipc_family_omap4430_NotifyCircSetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void InterruptDsp$$CONSTS()
    {
        // module InterruptDsp
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.intEnable", new Extern("ti_sdo_ipc_family_omap4430_InterruptDsp_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.intDisable", new Extern("ti_sdo_ipc_family_omap4430_InterruptDsp_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.intRegister", new Extern("ti_sdo_ipc_family_omap4430_InterruptDsp_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.intUnregister", new Extern("ti_sdo_ipc_family_omap4430_InterruptDsp_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.intSend", new Extern("ti_sdo_ipc_family_omap4430_InterruptDsp_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.intPost", new Extern("ti_sdo_ipc_family_omap4430_InterruptDsp_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.intClear", new Extern("ti_sdo_ipc_family_omap4430_InterruptDsp_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp.intShmStub", new Extern("ti_sdo_ipc_family_omap4430_InterruptDsp_intShmStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void InterruptDucati$$CONSTS()
    {
        // module InterruptDucati
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.intEnable", new Extern("ti_sdo_ipc_family_omap4430_InterruptDucati_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.intDisable", new Extern("ti_sdo_ipc_family_omap4430_InterruptDucati_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.intRegister", new Extern("ti_sdo_ipc_family_omap4430_InterruptDucati_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.intUnregister", new Extern("ti_sdo_ipc_family_omap4430_InterruptDucati_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.intSend", new Extern("ti_sdo_ipc_family_omap4430_InterruptDucati_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.intPost", new Extern("ti_sdo_ipc_family_omap4430_InterruptDucati_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.intClear", new Extern("ti_sdo_ipc_family_omap4430_InterruptDucati_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.intShmDucatiStub", new Extern("ti_sdo_ipc_family_omap4430_InterruptDucati_intShmDucatiStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati.intShmMbxStub", new Extern("ti_sdo_ipc_family_omap4430_InterruptDucati_intShmMbxStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void NotifySetup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NotifyCircSetup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void InterruptDsp$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void InterruptDucati$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NotifySetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifyCircSetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void InterruptDsp$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void InterruptDucati$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifySetup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void NotifyCircSetup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void InterruptDsp$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.FxnTable", "ti.sdo.ipc.family.omap4430");
        sizes.clear();
        sizes.add(Global.newArray("func", "UFxn"));
        sizes.add(Global.newArray("arg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDsp.FxnTable']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDsp.FxnTable']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDsp.FxnTable'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.Module_State", "ti.sdo.ipc.family.omap4430");
        sizes.clear();
        sizes.add(Global.newArray("fxnTable", "A2;Sti.sdo.ipc.family.omap4430.InterruptDsp;FxnTable"));
        sizes.add(Global.newArray("numPlugged", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDsp.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDsp.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDsp.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void InterruptDucati$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.FxnTable", "ti.sdo.ipc.family.omap4430");
        sizes.clear();
        sizes.add(Global.newArray("func", "UFxn"));
        sizes.add(Global.newArray("arg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDucati.FxnTable']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDucati.FxnTable']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDucati.FxnTable'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.Module_State", "ti.sdo.ipc.family.omap4430");
        sizes.clear();
        sizes.add(Global.newArray("fxnTable", "A3;Sti.sdo.ipc.family.omap4430.InterruptDucati;FxnTable"));
        sizes.add(Global.newArray("numPlugged", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDucati.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDucati.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.omap4430.InterruptDucati.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NotifySetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/omap4430/NotifySetup.xs");
        om.bind("ti.sdo.ipc.family.omap4430.NotifySetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.NotifySetup.Module", "ti.sdo.ipc.family.omap4430");
        po.init("ti.sdo.ipc.family.omap4430.NotifySetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.omap4430"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("E_noInterruptLine", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.family.omap4430"), Global.newObject("msg", "E_noInterruptLine: Trying to attach between CORE1 and %s"), "w");
            po.addFld("dspIntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("core0ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("core1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.NotifySetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.NotifySetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.NotifySetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.NotifySetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void NotifyCircSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/omap4430/NotifyCircSetup.xs");
        om.bind("ti.sdo.ipc.family.omap4430.NotifyCircSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.NotifyCircSetup.Module", "ti.sdo.ipc.family.omap4430");
        po.init("ti.sdo.ipc.family.omap4430.NotifyCircSetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.omap4430"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("E_noInterruptLine", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sdo.ipc.family.omap4430"), Global.newObject("msg", "E_noInterruptLine: Trying to attach between CORE1 and %s"), "w");
            po.addFld("dspIntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("core0ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("core1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.NotifyCircSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.NotifyCircSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.NotifyCircSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.NotifyCircSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void InterruptDsp$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/omap4430/InterruptDsp.xs");
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.Module", "ti.sdo.ipc.family.omap4430");
        po.init("ti.sdo.ipc.family.omap4430.InterruptDsp.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.omap4430"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("mailboxBaseAddr", Proto.Elm.newCNum("(xdc_UInt32)"), 0x4A0F4000L, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("core0ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("core1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.InterruptDsp$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct InterruptDsp.FxnTable
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp$$FxnTable", "ti.sdo.ipc.family.omap4430");
        po.init("ti.sdo.ipc.family.omap4430.InterruptDsp.FxnTable", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("func", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct InterruptDsp.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp$$Module_State", "ti.sdo.ipc.family.omap4430");
        po.init("ti.sdo.ipc.family.omap4430.InterruptDsp.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fxnTable", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.FxnTable", "ti.sdo.ipc.family.omap4430"), false, xdc.services.intern.xsr.Enum.intValue(2L)), $$DEFAULT, "w");
                po.addFld("numPlugged", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void InterruptDucati$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/omap4430/InterruptDucati.xs");
        om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.Module", "ti.sdo.ipc.family.omap4430");
        po.init("ti.sdo.ipc.family.omap4430.InterruptDucati.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.omap4430"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("mailboxBaseAddr", Proto.Elm.newCNum("(xdc_UInt32)"), 0x4A0F4000L, "w");
            po.addFld("ducatiCtrlBaseAddr", Proto.Elm.newCNum("(xdc_UInt32)"), 0x40001000L, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("core0ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("core1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.omap4430.InterruptDucati$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct InterruptDucati.FxnTable
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati$$FxnTable", "ti.sdo.ipc.family.omap4430");
        po.init("ti.sdo.ipc.family.omap4430.InterruptDucati.FxnTable", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("func", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct InterruptDucati.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati$$Module_State", "ti.sdo.ipc.family.omap4430");
        po.init("ti.sdo.ipc.family.omap4430.InterruptDucati.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fxnTable", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.FxnTable", "ti.sdo.ipc.family.omap4430"), false, xdc.services.intern.xsr.Enum.intValue(3L)), $$DEFAULT, "w");
                po.addFld("numPlugged", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void NotifySetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.NotifySetup", "ti.sdo.ipc.family.omap4430");
    }

    void NotifyCircSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.NotifyCircSetup", "ti.sdo.ipc.family.omap4430");
    }

    void InterruptDsp$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp", "ti.sdo.ipc.family.omap4430");
        vo.bind("FxnTable$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.omap4430.InterruptDsp.FxnTable", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp$$FxnTable", "ti.sdo.ipc.family.omap4430");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.omap4430.InterruptDsp.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp$$Module_State", "ti.sdo.ipc.family.omap4430");
    }

    void InterruptDucati$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati", "ti.sdo.ipc.family.omap4430");
        vo.bind("FxnTable$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.omap4430.InterruptDucati.FxnTable", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati$$FxnTable", "ti.sdo.ipc.family.omap4430");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.omap4430.InterruptDucati.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati$$Module_State", "ti.sdo.ipc.family.omap4430");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.family.omap4430.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.family.omap4430"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/omap4430/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.family.omap4430"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.family.omap4430"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.family.omap4430"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.family.omap4430"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.family.omap4430"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.family.omap4430"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.family.omap4430", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.family.omap4430");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.family.omap4430.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ipc", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.family.omap4430'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.family.omap4430$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.family.omap4430$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.family.omap4430$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void NotifySetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.NotifySetup", "ti.sdo.ipc.family.omap4430");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.NotifySetup.Module", "ti.sdo.ipc.family.omap4430");
        vo.init2(po, "ti.sdo.ipc.family.omap4430.NotifySetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.omap4430.NotifySetup$$capsule", "ti.sdo.ipc.family.omap4430"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.omap4430", "ti.sdo.ipc.family.omap4430"));
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
        mcfgs.add("E_noInterruptLine");
        mcfgs.add("dspIntVectId");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        mcfgs.add("core0ProcId");
        icfgs.add("core0ProcId");
        mcfgs.add("core1ProcId");
        icfgs.add("core1ProcId");
        mcfgs.add("hostProcId");
        icfgs.add("hostProcId");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.omap4430")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.omap4430.NotifySetup.attach", "ti.sdo.ipc.family.omap4430"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.omap4430.NotifySetup.sharedMemReq", "ti.sdo.ipc.family.omap4430"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.omap4430.NotifySetup.numIntLines", "ti.sdo.ipc.family.omap4430"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_omap4430_NotifySetup_Module__startupDone__E", "ti_sdo_ipc_family_omap4430_NotifySetup_attach__E", "ti_sdo_ipc_family_omap4430_NotifySetup_sharedMemReq__E", "ti_sdo_ipc_family_omap4430_NotifySetup_numIntLines__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_noInterruptLine"));
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NotifySetup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifySetup");
    }

    void NotifyCircSetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.NotifyCircSetup", "ti.sdo.ipc.family.omap4430");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.NotifyCircSetup.Module", "ti.sdo.ipc.family.omap4430");
        vo.init2(po, "ti.sdo.ipc.family.omap4430.NotifyCircSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.omap4430.NotifyCircSetup$$capsule", "ti.sdo.ipc.family.omap4430"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.omap4430", "ti.sdo.ipc.family.omap4430"));
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
        mcfgs.add("E_noInterruptLine");
        mcfgs.add("dspIntVectId");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        mcfgs.add("core0ProcId");
        icfgs.add("core0ProcId");
        mcfgs.add("core1ProcId");
        icfgs.add("core1ProcId");
        mcfgs.add("hostProcId");
        icfgs.add("hostProcId");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.omap4430")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.omap4430.NotifyCircSetup.attach", "ti.sdo.ipc.family.omap4430"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.omap4430.NotifyCircSetup.sharedMemReq", "ti.sdo.ipc.family.omap4430"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.omap4430.NotifyCircSetup.numIntLines", "ti.sdo.ipc.family.omap4430"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_omap4430_NotifyCircSetup_Module__startupDone__E", "ti_sdo_ipc_family_omap4430_NotifyCircSetup_attach__E", "ti_sdo_ipc_family_omap4430_NotifyCircSetup_sharedMemReq__E", "ti_sdo_ipc_family_omap4430_NotifyCircSetup_numIntLines__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_noInterruptLine"));
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NotifyCircSetup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifyCircSetup");
    }

    void InterruptDsp$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp", "ti.sdo.ipc.family.omap4430");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.Module", "ti.sdo.ipc.family.omap4430");
        vo.init2(po, "ti.sdo.ipc.family.omap4430.InterruptDsp", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp$$capsule", "ti.sdo.ipc.family.omap4430"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.omap4430", "ti.sdo.ipc.family.omap4430"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.omap4430"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.omap4430"));
        mcfgs.add("mailboxBaseAddr");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        mcfgs.add("hostProcId");
        icfgs.add("hostProcId");
        mcfgs.add("core0ProcId");
        icfgs.add("core0ProcId");
        mcfgs.add("core1ProcId");
        icfgs.add("core1ProcId");
        vo.bind("FxnTable", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.FxnTable", "ti.sdo.ipc.family.omap4430"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.FxnTable", "ti.sdo.ipc.family.omap4430"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.Module_State", "ti.sdo.ipc.family.omap4430"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.Module_State", "ti.sdo.ipc.family.omap4430"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.omap4430")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.intEnable", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.intDisable", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.intRegister", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.intUnregister", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.intSend", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.intPost", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.intClear", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intShmStub", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp.intShmStub", "ti.sdo.ipc.family.omap4430"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_omap4430_InterruptDsp_Module__startupDone__E", "ti_sdo_ipc_family_omap4430_InterruptDsp_intEnable__E", "ti_sdo_ipc_family_omap4430_InterruptDsp_intDisable__E", "ti_sdo_ipc_family_omap4430_InterruptDsp_intRegister__E", "ti_sdo_ipc_family_omap4430_InterruptDsp_intUnregister__E", "ti_sdo_ipc_family_omap4430_InterruptDsp_intSend__E", "ti_sdo_ipc_family_omap4430_InterruptDsp_intPost__E", "ti_sdo_ipc_family_omap4430_InterruptDsp_intClear__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("InterruptDsp", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("InterruptDsp");
    }

    void InterruptDucati$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati", "ti.sdo.ipc.family.omap4430");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.Module", "ti.sdo.ipc.family.omap4430");
        vo.init2(po, "ti.sdo.ipc.family.omap4430.InterruptDucati", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati$$capsule", "ti.sdo.ipc.family.omap4430"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.omap4430", "ti.sdo.ipc.family.omap4430"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.omap4430"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.omap4430"));
        mcfgs.add("mailboxBaseAddr");
        mcfgs.add("ducatiCtrlBaseAddr");
        vo.bind("FxnTable", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.FxnTable", "ti.sdo.ipc.family.omap4430"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.FxnTable", "ti.sdo.ipc.family.omap4430"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.Module_State", "ti.sdo.ipc.family.omap4430"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.Module_State", "ti.sdo.ipc.family.omap4430"));
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        mcfgs.add("hostProcId");
        icfgs.add("hostProcId");
        mcfgs.add("core0ProcId");
        icfgs.add("core0ProcId");
        mcfgs.add("core1ProcId");
        icfgs.add("core1ProcId");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.omap4430")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.intEnable", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.intDisable", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.intRegister", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.intUnregister", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.intSend", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.intPost", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.intClear", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intShmDucatiStub", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.intShmDucatiStub", "ti.sdo.ipc.family.omap4430"));
        vo.bind("intShmMbxStub", om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati.intShmMbxStub", "ti.sdo.ipc.family.omap4430"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_omap4430_InterruptDucati_Module__startupDone__E", "ti_sdo_ipc_family_omap4430_InterruptDucati_intEnable__E", "ti_sdo_ipc_family_omap4430_InterruptDucati_intDisable__E", "ti_sdo_ipc_family_omap4430_InterruptDucati_intRegister__E", "ti_sdo_ipc_family_omap4430_InterruptDucati_intUnregister__E", "ti_sdo_ipc_family_omap4430_InterruptDucati_intSend__E", "ti_sdo_ipc_family_omap4430_InterruptDucati_intPost__E", "ti_sdo_ipc_family_omap4430_InterruptDucati_intClear__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("InterruptDucati", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("InterruptDucati");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.omap4430.NotifySetup", "ti.sdo.ipc.family.omap4430"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.omap4430.NotifyCircSetup", "ti.sdo.ipc.family.omap4430"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDsp", "ti.sdo.ipc.family.omap4430"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.omap4430.InterruptDucati", "ti.sdo.ipc.family.omap4430"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.family.omap4430.NotifySetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.omap4430.NotifyCircSetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.omap4430.InterruptDsp")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.omap4430.InterruptDucati")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.family.omap4430")).add(pkgV);
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
        NotifySetup$$OBJECTS();
        NotifyCircSetup$$OBJECTS();
        InterruptDsp$$OBJECTS();
        InterruptDucati$$OBJECTS();
        NotifySetup$$CONSTS();
        NotifyCircSetup$$CONSTS();
        InterruptDsp$$CONSTS();
        InterruptDucati$$CONSTS();
        NotifySetup$$CREATES();
        NotifyCircSetup$$CREATES();
        InterruptDsp$$CREATES();
        InterruptDucati$$CREATES();
        NotifySetup$$FUNCTIONS();
        NotifyCircSetup$$FUNCTIONS();
        InterruptDsp$$FUNCTIONS();
        InterruptDucati$$FUNCTIONS();
        NotifySetup$$SIZES();
        NotifyCircSetup$$SIZES();
        InterruptDsp$$SIZES();
        InterruptDucati$$SIZES();
        NotifySetup$$TYPES();
        NotifyCircSetup$$TYPES();
        InterruptDsp$$TYPES();
        InterruptDucati$$TYPES();
        if (isROV) {
            NotifySetup$$ROV();
            NotifyCircSetup$$ROV();
            InterruptDsp$$ROV();
            InterruptDucati$$ROV();
        }//isROV
        $$SINGLETONS();
        NotifySetup$$SINGLETONS();
        NotifyCircSetup$$SINGLETONS();
        InterruptDsp$$SINGLETONS();
        InterruptDucati$$SINGLETONS();
        $$INITIALIZATION();
    }
}
