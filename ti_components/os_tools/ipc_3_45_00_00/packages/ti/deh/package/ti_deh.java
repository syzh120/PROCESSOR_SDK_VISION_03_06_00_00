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

public class ti_deh
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
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.knl");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.deh.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.deh", new Value.Obj("ti.deh", pkgP));
    }

    void Deh$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.deh.Deh.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.deh.Deh", new Value.Obj("ti.deh.Deh", po));
        pkgV.bind("Deh", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.deh.Deh$$ExcRegs", new Proto.Obj());
        om.bind("ti.deh.Deh.ExcRegs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.deh.Deh$$Module_State", new Proto.Obj());
        om.bind("ti.deh.Deh.Module_State", new Proto.Str(spo, false));
    }

    void StackDbg$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.deh.StackDbg.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.deh.StackDbg", new Value.Obj("ti.deh.StackDbg", po));
        pkgV.bind("StackDbg", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.deh.StackDbg$$StackEntry", new Proto.Obj());
        om.bind("ti.deh.StackDbg.StackEntry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.deh.StackDbg$$Module_State", new Proto.Obj());
        om.bind("ti.deh.StackDbg.Module_State", new Proto.Str(spo, false));
    }

    void Watchdog$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.deh.Watchdog.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.deh.Watchdog", new Value.Obj("ti.deh.Watchdog", po));
        pkgV.bind("Watchdog", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.deh.Watchdog$$TimerRegs", new Proto.Obj());
        om.bind("ti.deh.Watchdog.TimerRegs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.deh.Watchdog$$TimerDevice", new Proto.Obj());
        om.bind("ti.deh.Watchdog.TimerDevice", new Proto.Str(spo, false));
        om.bind("ti.deh.Watchdog.Mode", new Proto.Enm("ti.deh.Watchdog.Mode"));
        spo = (Proto.Obj)om.bind("ti.deh.Watchdog$$Module_State", new Proto.Obj());
        om.bind("ti.deh.Watchdog.Module_State", new Proto.Str(spo, false));
    }

    void Deh$$CONSTS()
    {
        // module Deh
        om.bind("ti.deh.Deh.excHandler", new Extern("ti_deh_Deh_excHandler__E", "xdc_Void(*)(xdc_UInt*,xdc_UInt)", true, false));
        om.bind("ti.deh.Deh.excHandlerDsp", new Extern("ti_deh_Deh_excHandlerDsp__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.deh.Deh.idleBegin", new Extern("ti_deh_Deh_idleBegin__E", "xdc_Void(*)(xdc_Void)", true, false));
    }

    void StackDbg$$CONSTS()
    {
        // module StackDbg
        om.bind("ti.deh.StackDbg.walkStack", new Extern("ti_deh_StackDbg_walkStack__E", "xdc_Void(*)(xdc_UInt,xdc_UInt,xdc_UInt,xdc_Bool(*)(ti_deh_StackDbg_StackEntry*,xdc_Void*),xdc_Ptr)", true, false));
    }

    void Watchdog$$CONSTS()
    {
        // module Watchdog
        om.bind("ti.deh.Watchdog.Mode_DISABLED", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.deh.Watchdog.Mode", "ti.deh"), "ti.deh.Watchdog.Mode_DISABLED", 0));
        om.bind("ti.deh.Watchdog.Mode_ENABLED", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.deh.Watchdog.Mode", "ti.deh"), "ti.deh.Watchdog.Mode_ENABLED", 1));
        om.bind("ti.deh.Watchdog.TIME_SEC", 5L);
        om.bind("ti.deh.Watchdog.BOOT_TIME_SEC", 10L);
        om.bind("ti.deh.Watchdog.init", new Extern("ti_deh_Watchdog_init__E", "xdc_Void(*)(xdc_Void(*)(xdc_Void))", true, false));
        om.bind("ti.deh.Watchdog.idleBegin", new Extern("ti_deh_Watchdog_idleBegin__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.deh.Watchdog.taskSwitch", new Extern("ti_deh_Watchdog_taskSwitch__E", "xdc_Void(*)(ti_sysbios_knl_Task_Handle,ti_sysbios_knl_Task_Handle)", true, false));
        om.bind("ti.deh.Watchdog.swiPrehook", new Extern("ti_deh_Watchdog_swiPrehook__E", "xdc_Void(*)(ti_sysbios_knl_Swi_Handle)", true, false));
        om.bind("ti.deh.Watchdog.isException", new Extern("ti_deh_Watchdog_isException__E", "xdc_Bool(*)(xdc_UInt)", true, false));
        om.bind("ti.deh.Watchdog.stop", new Extern("ti_deh_Watchdog_stop__I", "xdc_Void(*)(xdc_Int)", true, false));
        om.bind("ti.deh.Watchdog.start", new Extern("ti_deh_Watchdog_start__I", "xdc_Void(*)(xdc_Int)", true, false));
        om.bind("ti.deh.Watchdog.kick", new Extern("ti_deh_Watchdog_kick__I", "xdc_Void(*)(xdc_Int)", true, false));
        om.bind("ti.deh.Watchdog.restore", new Extern("ti_deh_Watchdog_restore__I", "xdc_Void(*)(xdc_Int,xdc_Ptr)", true, false));
    }

    void Deh$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void StackDbg$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Watchdog$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Deh$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void StackDbg$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Watchdog$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Deh$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.deh.Deh.ExcRegs", "ti.deh");
        sizes.clear();
        sizes.add(Global.newArray("r0", "UPtr"));
        sizes.add(Global.newArray("r1", "UPtr"));
        sizes.add(Global.newArray("r2", "UPtr"));
        sizes.add(Global.newArray("r3", "UPtr"));
        sizes.add(Global.newArray("r4", "UPtr"));
        sizes.add(Global.newArray("r5", "UPtr"));
        sizes.add(Global.newArray("r6", "UPtr"));
        sizes.add(Global.newArray("r7", "UPtr"));
        sizes.add(Global.newArray("r8", "UPtr"));
        sizes.add(Global.newArray("r9", "UPtr"));
        sizes.add(Global.newArray("r10", "UPtr"));
        sizes.add(Global.newArray("r11", "UPtr"));
        sizes.add(Global.newArray("r12", "UPtr"));
        sizes.add(Global.newArray("sp", "UPtr"));
        sizes.add(Global.newArray("lr", "UPtr"));
        sizes.add(Global.newArray("pc", "UPtr"));
        sizes.add(Global.newArray("psr", "UPtr"));
        sizes.add(Global.newArray("ICSR", "UPtr"));
        sizes.add(Global.newArray("MMFSR", "UPtr"));
        sizes.add(Global.newArray("BFSR", "UPtr"));
        sizes.add(Global.newArray("UFSR", "UPtr"));
        sizes.add(Global.newArray("HFSR", "UPtr"));
        sizes.add(Global.newArray("DFSR", "UPtr"));
        sizes.add(Global.newArray("MMAR", "UPtr"));
        sizes.add(Global.newArray("BFAR", "UPtr"));
        sizes.add(Global.newArray("AFSR", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.deh.Deh.ExcRegs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.deh.Deh.ExcRegs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.deh.Deh.ExcRegs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.deh.Deh.Module_State", "ti.deh");
        sizes.clear();
        sizes.add(Global.newArray("outbuf", "UPtr"));
        sizes.add(Global.newArray("isrStackSize", "USize"));
        sizes.add(Global.newArray("isrStackBase", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.deh.Deh.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.deh.Deh.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.deh.Deh.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void StackDbg$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.deh.StackDbg.StackEntry", "ti.deh");
        sizes.clear();
        sizes.add(Global.newArray("instr", "UInt"));
        sizes.add(Global.newArray("op", "UInt"));
        sizes.add(Global.newArray("target", "UInt"));
        sizes.add(Global.newArray("sp", "UInt"));
        sizes.add(Global.newArray("ret", "UInt"));
        sizes.add(Global.newArray("bogus", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.deh.StackDbg.StackEntry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.deh.StackDbg.StackEntry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.deh.StackDbg.StackEntry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.deh.StackDbg.Module_State", "ti.deh");
        sizes.clear();
        sizes.add(Global.newArray("codeBegin", "UInt"));
        sizes.add(Global.newArray("codeEnd", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.deh.StackDbg.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.deh.StackDbg.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.deh.StackDbg.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Watchdog$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.deh.Watchdog.TimerRegs", "ti.deh");
        sizes.clear();
        sizes.add(Global.newArray("tidr", "UInt"));
        sizes.add(Global.newArray("empty", "A3;UInt"));
        sizes.add(Global.newArray("tiocpCfg", "UInt"));
        sizes.add(Global.newArray("empty1", "A3;UInt"));
        sizes.add(Global.newArray("irq_eoi", "UInt"));
        sizes.add(Global.newArray("irqstat_raw", "UInt"));
        sizes.add(Global.newArray("tisr", "UInt"));
        sizes.add(Global.newArray("tier", "UInt"));
        sizes.add(Global.newArray("irqen_clr", "UInt"));
        sizes.add(Global.newArray("twer", "UInt"));
        sizes.add(Global.newArray("tclr", "UInt"));
        sizes.add(Global.newArray("tcrr", "TInt"));
        sizes.add(Global.newArray("tldr", "TInt"));
        sizes.add(Global.newArray("ttgr", "UInt"));
        sizes.add(Global.newArray("twps", "UInt"));
        sizes.add(Global.newArray("tmar", "UInt"));
        sizes.add(Global.newArray("tcar1", "UInt"));
        sizes.add(Global.newArray("tsicr", "UInt"));
        sizes.add(Global.newArray("tcar2", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.deh.Watchdog.TimerRegs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.deh.Watchdog.TimerRegs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.deh.Watchdog.TimerRegs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.deh.Watchdog.TimerDevice", "ti.deh");
        sizes.clear();
        sizes.add(Global.newArray("baseAddr", "UPtr"));
        sizes.add(Global.newArray("clkCtrl", "UPtr"));
        sizes.add(Global.newArray("intNum", "TInt32"));
        sizes.add(Global.newArray("eventId", "TInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.deh.Watchdog.TimerDevice']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.deh.Watchdog.TimerDevice']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.deh.Watchdog.TimerDevice'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.deh.Watchdog.Module_State", "ti.deh");
        sizes.clear();
        sizes.add(Global.newArray("device", "UPtr"));
        sizes.add(Global.newArray("status", "UPtr"));
        sizes.add(Global.newArray("wdtCores", "TInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.deh.Watchdog.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.deh.Watchdog.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.deh.Watchdog.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Deh$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/deh/Deh.xs");
        om.bind("ti.deh.Deh$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.deh.Deh.Module", "ti.deh");
        po.init("ti.deh.Deh.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.deh"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("bufSize", Proto.Elm.newCNum("(xdc_SizeT)"), 0x200L, "w");
            po.addFld("sectionName", $$T_Str, null, "wh");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.deh.Deh$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.deh.Deh$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.deh.Deh$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.deh.Deh$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct Deh.ExcRegs
        po = (Proto.Obj)om.findStrict("ti.deh.Deh$$ExcRegs", "ti.deh");
        po.init("ti.deh.Deh.ExcRegs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("r0", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r1", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r2", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r3", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r4", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r5", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r6", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r7", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r8", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r9", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r10", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r11", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("r12", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("sp", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("lr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("pc", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("psr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("ICSR", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("MMFSR", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("BFSR", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("UFSR", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("HFSR", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("DFSR", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("MMAR", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("BFAR", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("AFSR", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct Deh.Module_State
        po = (Proto.Obj)om.findStrict("ti.deh.Deh$$Module_State", "ti.deh");
        po.init("ti.deh.Deh.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("outbuf", new Proto.Arr(Proto.Elm.newCNum("(xdc_Char)"), false), $$DEFAULT, "w");
                po.addFld("isrStackSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("isrStackBase", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void StackDbg$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/deh/StackDbg.xs");
        om.bind("ti.deh.StackDbg$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.deh.StackDbg.Module", "ti.deh");
        po.init("ti.deh.StackDbg.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.deh"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.deh.StackDbg$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.deh.StackDbg$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.deh.StackDbg$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.deh.StackDbg$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct StackDbg.StackEntry
        po = (Proto.Obj)om.findStrict("ti.deh.StackDbg$$StackEntry", "ti.deh");
        po.init("ti.deh.StackDbg.StackEntry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("instr", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("op", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("target", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("sp", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("ret", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("bogus", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        // typedef StackDbg.VisitFuncPtr
        om.bind("ti.deh.StackDbg.VisitFuncPtr", new Proto.Adr("xdc_Bool(*)(ti_deh_StackDbg_StackEntry*,xdc_Void*)", "PFb"));
        // struct StackDbg.Module_State
        po = (Proto.Obj)om.findStrict("ti.deh.StackDbg$$Module_State", "ti.deh");
        po.init("ti.deh.StackDbg.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("codeBegin", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("codeEnd", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void Watchdog$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/deh/Watchdog.xs");
        om.bind("ti.deh.Watchdog$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.deh.Watchdog.Module", "ti.deh");
        po.init("ti.deh.Watchdog.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.deh"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("TIME_SEC", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "rh");
                po.addFld("BOOT_TIME_SEC", Proto.Elm.newCNum("(xdc_UInt)"), 10L, "rh");
        if (isCFG) {
            po.addFld("timerSettings", new Proto.Arr((Proto)om.findStrict("ti.deh.Watchdog.TimerDevice", "ti.deh"), false), Global.newArray(new Object[]{}), "wh");
            po.addFld("timerIds", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{}), "wh");
            po.addFld("disableWatchdog", $$T_Bool, false, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.deh.Watchdog$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.deh.Watchdog$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.deh.Watchdog$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.deh.Watchdog$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct Watchdog.TimerRegs
        po = (Proto.Obj)om.findStrict("ti.deh.Watchdog$$TimerRegs", "ti.deh");
        po.init("ti.deh.Watchdog.TimerRegs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("tidr", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("empty", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(3L)), $$DEFAULT, "w");
                po.addFld("tiocpCfg", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("empty1", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(3L)), $$DEFAULT, "w");
                po.addFld("irq_eoi", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("irqstat_raw", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("tisr", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("tier", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("irqen_clr", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("twer", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("tclr", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("tcrr", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("tldr", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("ttgr", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("twps", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("tmar", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("tcar1", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("tsicr", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("tcar2", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        // struct Watchdog.TimerDevice
        po = (Proto.Obj)om.findStrict("ti.deh.Watchdog$$TimerDevice", "ti.deh");
        po.init("ti.deh.Watchdog.TimerDevice", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("baseAddr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("clkCtrl", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_Int32)"), $$UNDEF, "w");
                po.addFld("eventId", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
        // struct Watchdog.Module_State
        po = (Proto.Obj)om.findStrict("ti.deh.Watchdog$$Module_State", "ti.deh");
        po.init("ti.deh.Watchdog.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("device", new Proto.Arr((Proto)om.findStrict("ti.deh.Watchdog.TimerDevice", "ti.deh"), false), $$DEFAULT, "w");
                po.addFld("status", new Proto.Arr((Proto)om.findStrict("ti.deh.Watchdog.Mode", "ti.deh"), false), $$DEFAULT, "w");
                po.addFld("wdtCores", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
    }

    void Deh$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.deh.Deh", "ti.deh");
        vo.bind("ExcRegs$fetchDesc", Global.newObject("type", "ti.deh.Deh.ExcRegs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.deh.Deh$$ExcRegs", "ti.deh");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.deh.Deh.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.deh.Deh$$Module_State", "ti.deh");
        po.bind("outbuf$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Char", "isScalar", true));
    }

    void StackDbg$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.deh.StackDbg", "ti.deh");
        vo.bind("StackEntry$fetchDesc", Global.newObject("type", "ti.deh.StackDbg.StackEntry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.deh.StackDbg$$StackEntry", "ti.deh");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.deh.StackDbg.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.deh.StackDbg$$Module_State", "ti.deh");
    }

    void Watchdog$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.deh.Watchdog", "ti.deh");
        vo.bind("TimerRegs$fetchDesc", Global.newObject("type", "ti.deh.Watchdog.TimerRegs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.deh.Watchdog$$TimerRegs", "ti.deh");
        vo.bind("TimerDevice$fetchDesc", Global.newObject("type", "ti.deh.Watchdog.TimerDevice", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.deh.Watchdog$$TimerDevice", "ti.deh");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.deh.Watchdog.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.deh.Watchdog$$Module_State", "ti.deh");
        po.bind("device$fetchDesc", Global.newObject("type", "ti.deh.Watchdog.TimerDevice", "isScalar", false));
        po.bind("status$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Mode", "isScalar", true));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.deh.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.deh"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/deh/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.deh"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.deh"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.deh"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.deh"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.deh"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.deh"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.deh", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.deh");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.deh.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.deh'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.deh$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.deh$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.deh$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/ti.deh_omap5_smp.aem4',\n");
            sb.append("'lib/debug/ti.deh_vayu_smp.aem4',\n");
            sb.append("'lib/release/ti.deh_omap5_smp.aem4',\n");
            sb.append("'lib/release/ti.deh_vayu_smp.aem4',\n");
            sb.append("'lib/debug/ti.deh_omap5_smp.aem4f',\n");
            sb.append("'lib/debug/ti.deh_vayu_smp.aem4f',\n");
            sb.append("'lib/release/ti.deh_omap5_smp.aem4f',\n");
            sb.append("'lib/release/ti.deh_vayu_smp.aem4f',\n");
            sb.append("'lib/debug/ti.deh_vayu.ae66',\n");
            sb.append("'lib/release/ti.deh_vayu.ae66',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/ti.deh_omap5_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.deh_vayu_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.deh_omap5_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.deh_vayu_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.deh_omap5_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.deh_vayu_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.deh_omap5_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.deh_vayu_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.deh_vayu.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/ti.deh_vayu.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Deh$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.deh.Deh", "ti.deh");
        po = (Proto.Obj)om.findStrict("ti.deh.Deh.Module", "ti.deh");
        vo.init2(po, "ti.deh.Deh", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.deh.Deh$$capsule", "ti.deh"));
        vo.bind("$package", om.findStrict("ti.deh", "ti.deh"));
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
        vo.bind("ExcRegs", om.findStrict("ti.deh.Deh.ExcRegs", "ti.deh"));
        tdefs.add(om.findStrict("ti.deh.Deh.ExcRegs", "ti.deh"));
        mcfgs.add("bufSize");
        vo.bind("Module_State", om.findStrict("ti.deh.Deh.Module_State", "ti.deh"));
        tdefs.add(om.findStrict("ti.deh.Deh.Module_State", "ti.deh"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.deh")).add(vo);
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
        vo.bind("excHandler", om.findStrict("ti.deh.Deh.excHandler", "ti.deh"));
        vo.bind("excHandlerDsp", om.findStrict("ti.deh.Deh.excHandlerDsp", "ti.deh"));
        vo.bind("idleBegin", om.findStrict("ti.deh.Deh.idleBegin", "ti.deh"));
        vo.bind("$$fxntab", Global.newArray("ti_deh_Deh_Module__startupDone__E", "ti_deh_Deh_excHandler__E", "ti_deh_Deh_excHandlerDsp__E", "ti_deh_Deh_idleBegin__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Deh.xdt");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "excHandler", "entry", "%p, 0x%x", "exit", ""));
        loggables.add(Global.newObject("name", "excHandlerDsp", "entry", "", "exit", ""));
        loggables.add(Global.newObject("name", "idleBegin", "entry", "", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./Deh.xdt");
        pkgV.bind("Deh", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Deh");
    }

    void StackDbg$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.deh.StackDbg", "ti.deh");
        po = (Proto.Obj)om.findStrict("ti.deh.StackDbg.Module", "ti.deh");
        vo.init2(po, "ti.deh.StackDbg", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.deh.StackDbg$$capsule", "ti.deh"));
        vo.bind("$package", om.findStrict("ti.deh", "ti.deh"));
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
        vo.bind("StackEntry", om.findStrict("ti.deh.StackDbg.StackEntry", "ti.deh"));
        tdefs.add(om.findStrict("ti.deh.StackDbg.StackEntry", "ti.deh"));
        vo.bind("VisitFuncPtr", om.findStrict("ti.deh.StackDbg.VisitFuncPtr", "ti.deh"));
        vo.bind("Module_State", om.findStrict("ti.deh.StackDbg.Module_State", "ti.deh"));
        tdefs.add(om.findStrict("ti.deh.StackDbg.Module_State", "ti.deh"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.deh")).add(vo);
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
        vo.bind("walkStack", om.findStrict("ti.deh.StackDbg.walkStack", "ti.deh"));
        vo.bind("$$fxntab", Global.newArray("ti_deh_StackDbg_Module__startupDone__E", "ti_deh_StackDbg_walkStack__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "walkStack", "entry", "0x%x, 0x%x, 0x%x, %p, %p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("StackDbg", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("StackDbg");
    }

    void Watchdog$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.deh.Watchdog", "ti.deh");
        po = (Proto.Obj)om.findStrict("ti.deh.Watchdog.Module", "ti.deh");
        vo.init2(po, "ti.deh.Watchdog", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.deh.Watchdog$$capsule", "ti.deh"));
        vo.bind("$package", om.findStrict("ti.deh", "ti.deh"));
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
        vo.bind("TimerRegs", om.findStrict("ti.deh.Watchdog.TimerRegs", "ti.deh"));
        tdefs.add(om.findStrict("ti.deh.Watchdog.TimerRegs", "ti.deh"));
        vo.bind("TimerDevice", om.findStrict("ti.deh.Watchdog.TimerDevice", "ti.deh"));
        tdefs.add(om.findStrict("ti.deh.Watchdog.TimerDevice", "ti.deh"));
        vo.bind("Mode", om.findStrict("ti.deh.Watchdog.Mode", "ti.deh"));
        mcfgs.add("disableWatchdog");
        vo.bind("Module_State", om.findStrict("ti.deh.Watchdog.Module_State", "ti.deh"));
        tdefs.add(om.findStrict("ti.deh.Watchdog.Module_State", "ti.deh"));
        vo.bind("Mode_DISABLED", om.findStrict("ti.deh.Watchdog.Mode_DISABLED", "ti.deh"));
        vo.bind("Mode_ENABLED", om.findStrict("ti.deh.Watchdog.Mode_ENABLED", "ti.deh"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.deh")).add(vo);
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
        vo.bind("init", om.findStrict("ti.deh.Watchdog.init", "ti.deh"));
        vo.bind("idleBegin", om.findStrict("ti.deh.Watchdog.idleBegin", "ti.deh"));
        vo.bind("taskSwitch", om.findStrict("ti.deh.Watchdog.taskSwitch", "ti.deh"));
        vo.bind("swiPrehook", om.findStrict("ti.deh.Watchdog.swiPrehook", "ti.deh"));
        vo.bind("isException", om.findStrict("ti.deh.Watchdog.isException", "ti.deh"));
        vo.bind("stop", om.findStrict("ti.deh.Watchdog.stop", "ti.deh"));
        vo.bind("start", om.findStrict("ti.deh.Watchdog.start", "ti.deh"));
        vo.bind("kick", om.findStrict("ti.deh.Watchdog.kick", "ti.deh"));
        vo.bind("restore", om.findStrict("ti.deh.Watchdog.restore", "ti.deh"));
        vo.bind("$$fxntab", Global.newArray("ti_deh_Watchdog_Module__startupDone__E", "ti_deh_Watchdog_init__E", "ti_deh_Watchdog_idleBegin__E", "ti_deh_Watchdog_taskSwitch__E", "ti_deh_Watchdog_swiPrehook__E", "ti_deh_Watchdog_isException__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "init", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "idleBegin", "entry", "", "exit", ""));
        loggables.add(Global.newObject("name", "taskSwitch", "entry", "%p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "swiPrehook", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "isException", "entry", "0x%x", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Watchdog", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Watchdog");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.deh.Deh", "ti.deh"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.deh.StackDbg", "ti.deh"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.deh.Watchdog", "ti.deh"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.deh.Deh")).bless();
        ((Value.Obj)om.getv("ti.deh.StackDbg")).bless();
        ((Value.Obj)om.getv("ti.deh.Watchdog")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.deh")).add(pkgV);
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
        Deh$$OBJECTS();
        StackDbg$$OBJECTS();
        Watchdog$$OBJECTS();
        Deh$$CONSTS();
        StackDbg$$CONSTS();
        Watchdog$$CONSTS();
        Deh$$CREATES();
        StackDbg$$CREATES();
        Watchdog$$CREATES();
        Deh$$FUNCTIONS();
        StackDbg$$FUNCTIONS();
        Watchdog$$FUNCTIONS();
        Deh$$SIZES();
        StackDbg$$SIZES();
        Watchdog$$SIZES();
        Deh$$TYPES();
        StackDbg$$TYPES();
        Watchdog$$TYPES();
        if (isROV) {
            Deh$$ROV();
            StackDbg$$ROV();
            Watchdog$$ROV();
        }//isROV
        $$SINGLETONS();
        Deh$$SINGLETONS();
        StackDbg$$SINGLETONS();
        Watchdog$$SINGLETONS();
        $$INITIALIZATION();
    }
}
