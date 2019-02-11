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

public class ti_sdo_ipc_family_c647x
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
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.notifyDrivers");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.interfaces");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.family.c647x.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.family.c647x", new Value.Obj("ti.sdo.ipc.family.c647x", pkgP));
    }

    void Interrupt$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.c647x.Interrupt.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.c647x.Interrupt", new Value.Obj("ti.sdo.ipc.family.c647x.Interrupt", po));
        pkgV.bind("Interrupt", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.c647x"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.c647x.Interrupt$$InterruptDataStruct", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.InterruptDataStruct", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.c647x.Interrupt$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.Module_State", new Proto.Str(spo, false));
    }

    void MultiProcSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.c647x.MultiProcSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.c647x.MultiProcSetup", new Value.Obj("ti.sdo.ipc.family.c647x.MultiProcSetup", po));
        pkgV.bind("MultiProcSetup", vo);
        // decls 
    }

    void NotifySetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.c647x.NotifySetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.c647x.NotifySetup", new Value.Obj("ti.sdo.ipc.family.c647x.NotifySetup", po));
        pkgV.bind("NotifySetup", vo);
        // decls 
    }

    void NotifyCircSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.c647x.NotifyCircSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.c647x.NotifyCircSetup", new Value.Obj("ti.sdo.ipc.family.c647x.NotifyCircSetup", po));
        pkgV.bind("NotifyCircSetup", vo);
        // decls 
    }

    void Interrupt$$CONSTS()
    {
        // module Interrupt
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.SRCSx_SHIFT", 4L);
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.intEnable", new Extern("ti_sdo_ipc_family_c647x_Interrupt_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.intDisable", new Extern("ti_sdo_ipc_family_c647x_Interrupt_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.intRegister", new Extern("ti_sdo_ipc_family_c647x_Interrupt_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.intUnregister", new Extern("ti_sdo_ipc_family_c647x_Interrupt_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.intSend", new Extern("ti_sdo_ipc_family_c647x_Interrupt_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.intPost", new Extern("ti_sdo_ipc_family_c647x_Interrupt_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.intClear", new Extern("ti_sdo_ipc_family_c647x_Interrupt_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.Interrupt.intShmStub", new Extern("ti_sdo_ipc_family_c647x_Interrupt_intShmStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void MultiProcSetup$$CONSTS()
    {
        // module MultiProcSetup
        om.bind("ti.sdo.ipc.family.c647x.MultiProcSetup.getProcId", new Extern("ti_sdo_ipc_family_c647x_MultiProcSetup_getProcId__I", "xdc_UInt16(*)(xdc_UInt)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.MultiProcSetup.init", new Extern("ti_sdo_ipc_family_c647x_MultiProcSetup_init__I", "xdc_Void(*)(xdc_Void)", true, false));
    }

    void NotifySetup$$CONSTS()
    {
        // module NotifySetup
        om.bind("ti.sdo.ipc.family.c647x.NotifySetup.attach", new Extern("ti_sdo_ipc_family_c647x_NotifySetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.NotifySetup.sharedMemReq", new Extern("ti_sdo_ipc_family_c647x_NotifySetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.NotifySetup.numIntLines", new Extern("ti_sdo_ipc_family_c647x_NotifySetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void NotifyCircSetup$$CONSTS()
    {
        // module NotifyCircSetup
        om.bind("ti.sdo.ipc.family.c647x.NotifyCircSetup.attach", new Extern("ti_sdo_ipc_family_c647x_NotifyCircSetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.NotifyCircSetup.sharedMemReq", new Extern("ti_sdo_ipc_family_c647x_NotifyCircSetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.c647x.NotifyCircSetup.numIntLines", new Extern("ti_sdo_ipc_family_c647x_NotifyCircSetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void Interrupt$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void MultiProcSetup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

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

    void Interrupt$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void MultiProcSetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifySetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifyCircSetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Interrupt$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.Module_State", "ti.sdo.ipc.family.c647x");
        sizes.clear();
        sizes.add(Global.newArray("func", "UFxn"));
        sizes.add(Global.newArray("args", "UPtr"));
        sizes.add(Global.newArray("numPlugged", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.c647x.Interrupt.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.c647x.Interrupt.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.c647x.Interrupt.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void MultiProcSetup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

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

    void Interrupt$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/c647x/Interrupt.xs");
        om.bind("ti.sdo.ipc.family.c647x.Interrupt$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.Module", "ti.sdo.ipc.family.c647x");
        po.init("ti.sdo.ipc.family.c647x.Interrupt.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.c647x"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("SRCSx_SHIFT", Proto.Elm.newCNum("(xdc_UInt)"), 4L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.family.c647x"), $$UNDEF, "wh");
            po.addFld("enableKick", $$T_Bool, true, "w");
            po.addFld("IPCGR0", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
            po.addFld("IPCAR0", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
            po.addFld("KICK0", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
            po.addFld("KICK1", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
            po.addFld("INTERDSPINT", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.Interrupt$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.Interrupt$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.Interrupt$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.Interrupt$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct Interrupt.InterruptDataStruct
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.c647x.Interrupt$$InterruptDataStruct", "ti.sdo.ipc.family.c647x");
        po.init("ti.sdo.ipc.family.c647x.Interrupt.InterruptDataStruct", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteCoreId", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("isrFxn", $$T_Str, $$UNDEF, "w");
                po.addFld("isrArg", $$T_Str, $$UNDEF, "w");
                po.addFld("isFlagged", $$T_Bool, $$UNDEF, "w");
        // struct Interrupt.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.c647x.Interrupt$$Module_State", "ti.sdo.ipc.family.c647x");
        po.init("ti.sdo.ipc.family.c647x.Interrupt.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("func", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("args", new Proto.Arr(new Proto.Adr("xdc_UArg", "Pv"), false), $$DEFAULT, "w");
                po.addFld("numPlugged", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void MultiProcSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/c647x/MultiProcSetup.xs");
        om.bind("ti.sdo.ipc.family.c647x.MultiProcSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.c647x.MultiProcSetup.Module", "ti.sdo.ipc.family.c647x");
        po.init("ti.sdo.ipc.family.c647x.MultiProcSetup.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.ipc.family.c647x"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("configureProcId", $$T_Bool, true, "w");
            po.addFld("A_invalidProcessor", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.family.c647x"), Global.newObject("msg", "A_invalidProcessor: This core is not present in the MultiProc name list"), "w");
            po.addFld("procMap", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt16)"), false), $$DEFAULT, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.MultiProcSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.MultiProcSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.MultiProcSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.MultiProcSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void NotifySetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/c647x/NotifySetup.xs");
        om.bind("ti.sdo.ipc.family.c647x.NotifySetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.c647x.NotifySetup.Module", "ti.sdo.ipc.family.c647x");
        po.init("ti.sdo.ipc.family.c647x.NotifySetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.c647x"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("dspIntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.NotifySetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.NotifySetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.NotifySetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.NotifySetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void NotifyCircSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/c647x/NotifyCircSetup.xs");
        om.bind("ti.sdo.ipc.family.c647x.NotifyCircSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.c647x.NotifyCircSetup.Module", "ti.sdo.ipc.family.c647x");
        po.init("ti.sdo.ipc.family.c647x.NotifyCircSetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.c647x"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("dspIntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.NotifyCircSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.NotifyCircSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.NotifyCircSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.c647x.NotifyCircSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void Interrupt$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.c647x.Interrupt", "ti.sdo.ipc.family.c647x");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.c647x.Interrupt.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.c647x.Interrupt$$Module_State", "ti.sdo.ipc.family.c647x");
    }

    void MultiProcSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.c647x.MultiProcSetup", "ti.sdo.ipc.family.c647x");
    }

    void NotifySetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.c647x.NotifySetup", "ti.sdo.ipc.family.c647x");
    }

    void NotifyCircSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.c647x.NotifyCircSetup", "ti.sdo.ipc.family.c647x");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.family.c647x.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.family.c647x"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/c647x/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.family.c647x"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.family.c647x"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.family.c647x"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.family.c647x"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.family.c647x"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.family.c647x"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.family.c647x", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.family.c647x");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.family.c647x.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ipc", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.family.c647x'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.family.c647x$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.family.c647x$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.family.c647x$$stat$root'];\n");
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

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.c647x.Interrupt", "ti.sdo.ipc.family.c647x");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.Module", "ti.sdo.ipc.family.c647x");
        vo.init2(po, "ti.sdo.ipc.family.c647x.Interrupt", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.c647x.Interrupt$$capsule", "ti.sdo.ipc.family.c647x"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.c647x", "ti.sdo.ipc.family.c647x"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.c647x"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.c647x"));
        vo.bind("InterruptDataStruct", om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.InterruptDataStruct", "ti.sdo.ipc.family.c647x"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.InterruptDataStruct", "ti.sdo.ipc.family.c647x"));
        mcfgs.add("enableKick");
        mcfgs.add("IPCGR0");
        icfgs.add("IPCGR0");
        mcfgs.add("IPCAR0");
        icfgs.add("IPCAR0");
        mcfgs.add("KICK0");
        icfgs.add("KICK0");
        mcfgs.add("KICK1");
        icfgs.add("KICK1");
        mcfgs.add("INTERDSPINT");
        icfgs.add("INTERDSPINT");
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.Module_State", "ti.sdo.ipc.family.c647x"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.Module_State", "ti.sdo.ipc.family.c647x"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.c647x")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.intEnable", "ti.sdo.ipc.family.c647x"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.intDisable", "ti.sdo.ipc.family.c647x"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.intRegister", "ti.sdo.ipc.family.c647x"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.intUnregister", "ti.sdo.ipc.family.c647x"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.intSend", "ti.sdo.ipc.family.c647x"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.intPost", "ti.sdo.ipc.family.c647x"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.intClear", "ti.sdo.ipc.family.c647x"));
        vo.bind("intShmStub", om.findStrict("ti.sdo.ipc.family.c647x.Interrupt.intShmStub", "ti.sdo.ipc.family.c647x"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_c647x_Interrupt_Module__startupDone__E", "ti_sdo_ipc_family_c647x_Interrupt_intEnable__E", "ti_sdo_ipc_family_c647x_Interrupt_intDisable__E", "ti_sdo_ipc_family_c647x_Interrupt_intRegister__E", "ti_sdo_ipc_family_c647x_Interrupt_intUnregister__E", "ti_sdo_ipc_family_c647x_Interrupt_intSend__E", "ti_sdo_ipc_family_c647x_Interrupt_intPost__E", "ti_sdo_ipc_family_c647x_Interrupt_intClear__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Interrupt", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Interrupt");
    }

    void MultiProcSetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.c647x.MultiProcSetup", "ti.sdo.ipc.family.c647x");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.c647x.MultiProcSetup.Module", "ti.sdo.ipc.family.c647x");
        vo.init2(po, "ti.sdo.ipc.family.c647x.MultiProcSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.c647x.MultiProcSetup$$capsule", "ti.sdo.ipc.family.c647x"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.c647x", "ti.sdo.ipc.family.c647x"));
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
        mcfgs.add("configureProcId");
        mcfgs.add("A_invalidProcessor");
        mcfgs.add("procMap");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.c647x")).add(vo);
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
        vo.bind("getProcId", om.findStrict("ti.sdo.ipc.family.c647x.MultiProcSetup.getProcId", "ti.sdo.ipc.family.c647x"));
        vo.bind("init", om.findStrict("ti.sdo.ipc.family.c647x.MultiProcSetup.init", "ti.sdo.ipc.family.c647x"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_c647x_MultiProcSetup_Module__startupDone__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_invalidProcessor"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("MultiProcSetup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("MultiProcSetup");
    }

    void NotifySetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.c647x.NotifySetup", "ti.sdo.ipc.family.c647x");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.c647x.NotifySetup.Module", "ti.sdo.ipc.family.c647x");
        vo.init2(po, "ti.sdo.ipc.family.c647x.NotifySetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.c647x.NotifySetup$$capsule", "ti.sdo.ipc.family.c647x"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.c647x", "ti.sdo.ipc.family.c647x"));
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
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.c647x")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.c647x.NotifySetup.attach", "ti.sdo.ipc.family.c647x"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.c647x.NotifySetup.sharedMemReq", "ti.sdo.ipc.family.c647x"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.c647x.NotifySetup.numIntLines", "ti.sdo.ipc.family.c647x"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_c647x_NotifySetup_Module__startupDone__E", "ti_sdo_ipc_family_c647x_NotifySetup_attach__E", "ti_sdo_ipc_family_c647x_NotifySetup_sharedMemReq__E", "ti_sdo_ipc_family_c647x_NotifySetup_numIntLines__E"));
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

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.c647x.NotifyCircSetup", "ti.sdo.ipc.family.c647x");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.c647x.NotifyCircSetup.Module", "ti.sdo.ipc.family.c647x");
        vo.init2(po, "ti.sdo.ipc.family.c647x.NotifyCircSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.c647x.NotifyCircSetup$$capsule", "ti.sdo.ipc.family.c647x"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.c647x", "ti.sdo.ipc.family.c647x"));
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
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.c647x")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.c647x.NotifyCircSetup.attach", "ti.sdo.ipc.family.c647x"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.c647x.NotifyCircSetup.sharedMemReq", "ti.sdo.ipc.family.c647x"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.c647x.NotifyCircSetup.numIntLines", "ti.sdo.ipc.family.c647x"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_c647x_NotifyCircSetup_Module__startupDone__E", "ti_sdo_ipc_family_c647x_NotifyCircSetup_attach__E", "ti_sdo_ipc_family_c647x_NotifyCircSetup_sharedMemReq__E", "ti_sdo_ipc_family_c647x_NotifyCircSetup_numIntLines__E"));
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

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.c647x.Interrupt", "ti.sdo.ipc.family.c647x"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.c647x.MultiProcSetup", "ti.sdo.ipc.family.c647x"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.c647x.NotifySetup", "ti.sdo.ipc.family.c647x"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.c647x.NotifyCircSetup", "ti.sdo.ipc.family.c647x"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.c647x.Interrupt", "ti.sdo.ipc.family.c647x");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Registered Interrupts", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE_DATA"), "viewInitFxn", "viewInterruptsData", "structName", "InterruptDataStruct")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.family.c647x.Interrupt")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.c647x.MultiProcSetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.c647x.NotifySetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.c647x.NotifyCircSetup")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.family.c647x")).add(pkgV);
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
        MultiProcSetup$$OBJECTS();
        NotifySetup$$OBJECTS();
        NotifyCircSetup$$OBJECTS();
        Interrupt$$CONSTS();
        MultiProcSetup$$CONSTS();
        NotifySetup$$CONSTS();
        NotifyCircSetup$$CONSTS();
        Interrupt$$CREATES();
        MultiProcSetup$$CREATES();
        NotifySetup$$CREATES();
        NotifyCircSetup$$CREATES();
        Interrupt$$FUNCTIONS();
        MultiProcSetup$$FUNCTIONS();
        NotifySetup$$FUNCTIONS();
        NotifyCircSetup$$FUNCTIONS();
        Interrupt$$SIZES();
        MultiProcSetup$$SIZES();
        NotifySetup$$SIZES();
        NotifyCircSetup$$SIZES();
        Interrupt$$TYPES();
        MultiProcSetup$$TYPES();
        NotifySetup$$TYPES();
        NotifyCircSetup$$TYPES();
        if (isROV) {
            Interrupt$$ROV();
            MultiProcSetup$$ROV();
            NotifySetup$$ROV();
            NotifyCircSetup$$ROV();
        }//isROV
        $$SINGLETONS();
        Interrupt$$SINGLETONS();
        MultiProcSetup$$SINGLETONS();
        NotifySetup$$SINGLETONS();
        NotifyCircSetup$$SINGLETONS();
        $$INITIALIZATION();
    }
}
