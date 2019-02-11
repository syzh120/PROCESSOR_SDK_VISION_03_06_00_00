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

public class ti_sdo_ipc_family_arctic
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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.interfaces");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.notifyDrivers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.family.arctic.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.family.arctic", new Value.Obj("ti.sdo.ipc.family.arctic", pkgP));
    }

    void NotifySetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.arctic.NotifySetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.arctic.NotifySetup", new Value.Obj("ti.sdo.ipc.family.arctic.NotifySetup", po));
        pkgV.bind("NotifySetup", vo);
        // decls 
    }

    void NotifyCircSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.arctic.NotifyCircSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.arctic.NotifyCircSetup", new Value.Obj("ti.sdo.ipc.family.arctic.NotifyCircSetup", po));
        pkgV.bind("NotifyCircSetup", vo);
        // decls 
    }

    void InterruptDsp$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.arctic.InterruptDsp", new Value.Obj("ti.sdo.ipc.family.arctic.InterruptDsp", po));
        pkgV.bind("InterruptDsp", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.arctic"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.arctic.InterruptDsp$$FxnTable", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.FxnTable", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.arctic.InterruptDsp$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.Module_State", new Proto.Str(spo, false));
    }

    void InterruptArp32$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.arctic.InterruptArp32", new Value.Obj("ti.sdo.ipc.family.arctic.InterruptArp32", po));
        pkgV.bind("InterruptArp32", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.arctic"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.arctic.InterruptArp32$$FxnTable", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.FxnTable", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.arctic.InterruptArp32$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.Module_State", new Proto.Str(spo, false));
    }

    void NotifySetup$$CONSTS()
    {
        // module NotifySetup
        om.bind("ti.sdo.ipc.family.arctic.NotifySetup.attach", new Extern("ti_sdo_ipc_family_arctic_NotifySetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.NotifySetup.sharedMemReq", new Extern("ti_sdo_ipc_family_arctic_NotifySetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.NotifySetup.numIntLines", new Extern("ti_sdo_ipc_family_arctic_NotifySetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void NotifyCircSetup$$CONSTS()
    {
        // module NotifyCircSetup
        om.bind("ti.sdo.ipc.family.arctic.NotifyCircSetup.attach", new Extern("ti_sdo_ipc_family_arctic_NotifyCircSetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.NotifyCircSetup.sharedMemReq", new Extern("ti_sdo_ipc_family_arctic_NotifyCircSetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.NotifyCircSetup.numIntLines", new Extern("ti_sdo_ipc_family_arctic_NotifyCircSetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void InterruptDsp$$CONSTS()
    {
        // module InterruptDsp
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.intEnable", new Extern("ti_sdo_ipc_family_arctic_InterruptDsp_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.intDisable", new Extern("ti_sdo_ipc_family_arctic_InterruptDsp_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.intRegister", new Extern("ti_sdo_ipc_family_arctic_InterruptDsp_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.intUnregister", new Extern("ti_sdo_ipc_family_arctic_InterruptDsp_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.intSend", new Extern("ti_sdo_ipc_family_arctic_InterruptDsp_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.intPost", new Extern("ti_sdo_ipc_family_arctic_InterruptDsp_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.intClear", new Extern("ti_sdo_ipc_family_arctic_InterruptDsp_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp.intShmStub", new Extern("ti_sdo_ipc_family_arctic_InterruptDsp_intShmStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void InterruptArp32$$CONSTS()
    {
        // module InterruptArp32
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.intEnable", new Extern("ti_sdo_ipc_family_arctic_InterruptArp32_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.intDisable", new Extern("ti_sdo_ipc_family_arctic_InterruptArp32_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.intRegister", new Extern("ti_sdo_ipc_family_arctic_InterruptArp32_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.intUnregister", new Extern("ti_sdo_ipc_family_arctic_InterruptArp32_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.intSend", new Extern("ti_sdo_ipc_family_arctic_InterruptArp32_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.intPost", new Extern("ti_sdo_ipc_family_arctic_InterruptArp32_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.intClear", new Extern("ti_sdo_ipc_family_arctic_InterruptArp32_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32.intShmStub", new Extern("ti_sdo_ipc_family_arctic_InterruptArp32_intShmStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
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

    void InterruptArp32$$CREATES()
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

    void InterruptArp32$$FUNCTIONS()
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

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.FxnTable", "ti.sdo.ipc.family.arctic");
        sizes.clear();
        sizes.add(Global.newArray("func", "UFxn"));
        sizes.add(Global.newArray("arg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.arctic.InterruptDsp.FxnTable']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.arctic.InterruptDsp.FxnTable']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.arctic.InterruptDsp.FxnTable'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.Module_State", "ti.sdo.ipc.family.arctic");
        sizes.clear();
        sizes.add(Global.newArray("fxnTable", "Sti.sdo.ipc.family.arctic.InterruptDsp;FxnTable"));
        sizes.add(Global.newArray("numPlugged", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.arctic.InterruptDsp.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.arctic.InterruptDsp.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.arctic.InterruptDsp.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void InterruptArp32$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.FxnTable", "ti.sdo.ipc.family.arctic");
        sizes.clear();
        sizes.add(Global.newArray("func", "UFxn"));
        sizes.add(Global.newArray("arg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.arctic.InterruptArp32.FxnTable']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.arctic.InterruptArp32.FxnTable']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.arctic.InterruptArp32.FxnTable'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.Module_State", "ti.sdo.ipc.family.arctic");
        sizes.clear();
        sizes.add(Global.newArray("fxnTable", "Sti.sdo.ipc.family.arctic.InterruptArp32;FxnTable"));
        sizes.add(Global.newArray("numPlugged", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.arctic.InterruptArp32.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.arctic.InterruptArp32.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.arctic.InterruptArp32.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NotifySetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/arctic/NotifySetup.xs");
        om.bind("ti.sdo.ipc.family.arctic.NotifySetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.NotifySetup.Module", "ti.sdo.ipc.family.arctic");
        po.init("ti.sdo.ipc.family.arctic.NotifySetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.arctic"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("dspIntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
            po.addFld("arp32IntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 4L, "w");
            po.addFld("arp32ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.NotifySetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.NotifySetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.NotifySetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.NotifySetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void NotifyCircSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/arctic/NotifyCircSetup.xs");
        om.bind("ti.sdo.ipc.family.arctic.NotifyCircSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.NotifyCircSetup.Module", "ti.sdo.ipc.family.arctic");
        po.init("ti.sdo.ipc.family.arctic.NotifyCircSetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.arctic"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("dspIntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
            po.addFld("arp32IntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 4L, "w");
            po.addFld("arp32ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.NotifyCircSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.NotifyCircSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.NotifyCircSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.NotifyCircSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void InterruptDsp$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/arctic/InterruptDsp.xs");
        om.bind("ti.sdo.ipc.family.arctic.InterruptDsp$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.Module", "ti.sdo.ipc.family.arctic");
        po.init("ti.sdo.ipc.family.arctic.InterruptDsp.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.arctic"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("mailboxBaseAddr", Proto.Elm.newCNum("(xdc_UInt32)"), 0x5908B000L, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("arp32ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.InterruptDsp$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.InterruptDsp$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.InterruptDsp$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.InterruptDsp$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct InterruptDsp.FxnTable
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp$$FxnTable", "ti.sdo.ipc.family.arctic");
        po.init("ti.sdo.ipc.family.arctic.InterruptDsp.FxnTable", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("func", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct InterruptDsp.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp$$Module_State", "ti.sdo.ipc.family.arctic");
        po.init("ti.sdo.ipc.family.arctic.InterruptDsp.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fxnTable", (Proto)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.FxnTable", "ti.sdo.ipc.family.arctic"), $$DEFAULT, "w");
                po.addFld("numPlugged", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void InterruptArp32$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/arctic/InterruptArp32.xs");
        om.bind("ti.sdo.ipc.family.arctic.InterruptArp32$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.Module", "ti.sdo.ipc.family.arctic");
        po.init("ti.sdo.ipc.family.arctic.InterruptArp32.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.arctic"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("mailboxBaseAddr", Proto.Elm.newCNum("(xdc_UInt32)"), 0x4008B000L, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("arp32ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.InterruptArp32$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.InterruptArp32$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.InterruptArp32$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.arctic.InterruptArp32$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct InterruptArp32.FxnTable
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32$$FxnTable", "ti.sdo.ipc.family.arctic");
        po.init("ti.sdo.ipc.family.arctic.InterruptArp32.FxnTable", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("func", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct InterruptArp32.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32$$Module_State", "ti.sdo.ipc.family.arctic");
        po.init("ti.sdo.ipc.family.arctic.InterruptArp32.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fxnTable", (Proto)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.FxnTable", "ti.sdo.ipc.family.arctic"), $$DEFAULT, "w");
                po.addFld("numPlugged", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void NotifySetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.arctic.NotifySetup", "ti.sdo.ipc.family.arctic");
    }

    void NotifyCircSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.arctic.NotifyCircSetup", "ti.sdo.ipc.family.arctic");
    }

    void InterruptDsp$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp", "ti.sdo.ipc.family.arctic");
        vo.bind("FxnTable$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.arctic.InterruptDsp.FxnTable", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp$$FxnTable", "ti.sdo.ipc.family.arctic");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.arctic.InterruptDsp.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp$$Module_State", "ti.sdo.ipc.family.arctic");
    }

    void InterruptArp32$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32", "ti.sdo.ipc.family.arctic");
        vo.bind("FxnTable$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.arctic.InterruptArp32.FxnTable", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32$$FxnTable", "ti.sdo.ipc.family.arctic");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.arctic.InterruptArp32.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32$$Module_State", "ti.sdo.ipc.family.arctic");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.family.arctic.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.family.arctic"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/arctic/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.family.arctic"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.family.arctic"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.family.arctic"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.family.arctic"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.family.arctic"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.family.arctic"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.family.arctic", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.family.arctic");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.family.arctic.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ipc", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.family.arctic'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.family.arctic$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.family.arctic$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.family.arctic$$stat$root'];\n");
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

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.arctic.NotifySetup", "ti.sdo.ipc.family.arctic");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.NotifySetup.Module", "ti.sdo.ipc.family.arctic");
        vo.init2(po, "ti.sdo.ipc.family.arctic.NotifySetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.arctic.NotifySetup$$capsule", "ti.sdo.ipc.family.arctic"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.arctic", "ti.sdo.ipc.family.arctic"));
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
        mcfgs.add("arp32IntVectId");
        mcfgs.add("arp32ProcId");
        icfgs.add("arp32ProcId");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.arctic")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.arctic.NotifySetup.attach", "ti.sdo.ipc.family.arctic"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.arctic.NotifySetup.sharedMemReq", "ti.sdo.ipc.family.arctic"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.arctic.NotifySetup.numIntLines", "ti.sdo.ipc.family.arctic"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_arctic_NotifySetup_Module__startupDone__E", "ti_sdo_ipc_family_arctic_NotifySetup_attach__E", "ti_sdo_ipc_family_arctic_NotifySetup_sharedMemReq__E", "ti_sdo_ipc_family_arctic_NotifySetup_numIntLines__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
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

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.arctic.NotifyCircSetup", "ti.sdo.ipc.family.arctic");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.NotifyCircSetup.Module", "ti.sdo.ipc.family.arctic");
        vo.init2(po, "ti.sdo.ipc.family.arctic.NotifyCircSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.arctic.NotifyCircSetup$$capsule", "ti.sdo.ipc.family.arctic"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.arctic", "ti.sdo.ipc.family.arctic"));
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
        mcfgs.add("arp32IntVectId");
        mcfgs.add("arp32ProcId");
        icfgs.add("arp32ProcId");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.arctic")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.arctic.NotifyCircSetup.attach", "ti.sdo.ipc.family.arctic"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.arctic.NotifyCircSetup.sharedMemReq", "ti.sdo.ipc.family.arctic"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.arctic.NotifyCircSetup.numIntLines", "ti.sdo.ipc.family.arctic"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_arctic_NotifyCircSetup_Module__startupDone__E", "ti_sdo_ipc_family_arctic_NotifyCircSetup_attach__E", "ti_sdo_ipc_family_arctic_NotifyCircSetup_sharedMemReq__E", "ti_sdo_ipc_family_arctic_NotifyCircSetup_numIntLines__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
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

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp", "ti.sdo.ipc.family.arctic");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.Module", "ti.sdo.ipc.family.arctic");
        vo.init2(po, "ti.sdo.ipc.family.arctic.InterruptDsp", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp$$capsule", "ti.sdo.ipc.family.arctic"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.arctic", "ti.sdo.ipc.family.arctic"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.arctic"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.arctic"));
        mcfgs.add("mailboxBaseAddr");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        mcfgs.add("arp32ProcId");
        icfgs.add("arp32ProcId");
        vo.bind("FxnTable", om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.FxnTable", "ti.sdo.ipc.family.arctic"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.FxnTable", "ti.sdo.ipc.family.arctic"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.Module_State", "ti.sdo.ipc.family.arctic"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.Module_State", "ti.sdo.ipc.family.arctic"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.arctic")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.intEnable", "ti.sdo.ipc.family.arctic"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.intDisable", "ti.sdo.ipc.family.arctic"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.intRegister", "ti.sdo.ipc.family.arctic"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.intUnregister", "ti.sdo.ipc.family.arctic"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.intSend", "ti.sdo.ipc.family.arctic"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.intPost", "ti.sdo.ipc.family.arctic"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.intClear", "ti.sdo.ipc.family.arctic"));
        vo.bind("intShmStub", om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp.intShmStub", "ti.sdo.ipc.family.arctic"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_arctic_InterruptDsp_Module__startupDone__E", "ti_sdo_ipc_family_arctic_InterruptDsp_intEnable__E", "ti_sdo_ipc_family_arctic_InterruptDsp_intDisable__E", "ti_sdo_ipc_family_arctic_InterruptDsp_intRegister__E", "ti_sdo_ipc_family_arctic_InterruptDsp_intUnregister__E", "ti_sdo_ipc_family_arctic_InterruptDsp_intSend__E", "ti_sdo_ipc_family_arctic_InterruptDsp_intPost__E", "ti_sdo_ipc_family_arctic_InterruptDsp_intClear__E"));
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

    void InterruptArp32$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32", "ti.sdo.ipc.family.arctic");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.Module", "ti.sdo.ipc.family.arctic");
        vo.init2(po, "ti.sdo.ipc.family.arctic.InterruptArp32", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32$$capsule", "ti.sdo.ipc.family.arctic"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.arctic", "ti.sdo.ipc.family.arctic"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.arctic"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.arctic"));
        mcfgs.add("mailboxBaseAddr");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        mcfgs.add("arp32ProcId");
        icfgs.add("arp32ProcId");
        vo.bind("FxnTable", om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.FxnTable", "ti.sdo.ipc.family.arctic"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.FxnTable", "ti.sdo.ipc.family.arctic"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.Module_State", "ti.sdo.ipc.family.arctic"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.Module_State", "ti.sdo.ipc.family.arctic"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.arctic")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.intEnable", "ti.sdo.ipc.family.arctic"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.intDisable", "ti.sdo.ipc.family.arctic"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.intRegister", "ti.sdo.ipc.family.arctic"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.intUnregister", "ti.sdo.ipc.family.arctic"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.intSend", "ti.sdo.ipc.family.arctic"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.intPost", "ti.sdo.ipc.family.arctic"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.intClear", "ti.sdo.ipc.family.arctic"));
        vo.bind("intShmStub", om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32.intShmStub", "ti.sdo.ipc.family.arctic"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_arctic_InterruptArp32_Module__startupDone__E", "ti_sdo_ipc_family_arctic_InterruptArp32_intEnable__E", "ti_sdo_ipc_family_arctic_InterruptArp32_intDisable__E", "ti_sdo_ipc_family_arctic_InterruptArp32_intRegister__E", "ti_sdo_ipc_family_arctic_InterruptArp32_intUnregister__E", "ti_sdo_ipc_family_arctic_InterruptArp32_intSend__E", "ti_sdo_ipc_family_arctic_InterruptArp32_intPost__E", "ti_sdo_ipc_family_arctic_InterruptArp32_intClear__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("InterruptArp32", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("InterruptArp32");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.arctic.NotifySetup", "ti.sdo.ipc.family.arctic"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.arctic.NotifyCircSetup", "ti.sdo.ipc.family.arctic"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.arctic.InterruptDsp", "ti.sdo.ipc.family.arctic"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.arctic.InterruptArp32", "ti.sdo.ipc.family.arctic"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.family.arctic.NotifySetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.arctic.NotifyCircSetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.arctic.InterruptDsp")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.arctic.InterruptArp32")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.family.arctic")).add(pkgV);
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
        InterruptArp32$$OBJECTS();
        NotifySetup$$CONSTS();
        NotifyCircSetup$$CONSTS();
        InterruptDsp$$CONSTS();
        InterruptArp32$$CONSTS();
        NotifySetup$$CREATES();
        NotifyCircSetup$$CREATES();
        InterruptDsp$$CREATES();
        InterruptArp32$$CREATES();
        NotifySetup$$FUNCTIONS();
        NotifyCircSetup$$FUNCTIONS();
        InterruptDsp$$FUNCTIONS();
        InterruptArp32$$FUNCTIONS();
        NotifySetup$$SIZES();
        NotifyCircSetup$$SIZES();
        InterruptDsp$$SIZES();
        InterruptArp32$$SIZES();
        NotifySetup$$TYPES();
        NotifyCircSetup$$TYPES();
        InterruptDsp$$TYPES();
        InterruptArp32$$TYPES();
        if (isROV) {
            NotifySetup$$ROV();
            NotifyCircSetup$$ROV();
            InterruptDsp$$ROV();
            InterruptArp32$$ROV();
        }//isROV
        $$SINGLETONS();
        NotifySetup$$SINGLETONS();
        NotifyCircSetup$$SINGLETONS();
        InterruptDsp$$SINGLETONS();
        InterruptArp32$$SINGLETONS();
        $$INITIALIZATION();
    }
}
