/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A71
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_sysbios_family_arm_v6m
{
    static final String VERS = "@(#) xdc-A71\n";

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
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.interfaces");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sysbios.family.arm.v6m", new Value.Obj("ti.sysbios.family.arm.v6m", pkgP));
    }

    void Clobber$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Clobber.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v6m.Clobber", new Value.Obj("ti.sysbios.family.arm.v6m.Clobber", po));
        pkgV.bind("Clobber", vo);
        // decls 
    }

    void Hwi$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi", new Value.Obj("ti.sysbios.family.arm.v6m.Hwi", po));
        pkgV.bind("Hwi", vo);
        // decls 
        om.bind("ti.sysbios.family.arm.v6m.Hwi.HookSet", om.findStrict("ti.sysbios.interfaces.IHwi.HookSet", "ti.sysbios.family.arm.v6m"));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.MaskingOption", om.findStrict("ti.sysbios.interfaces.IHwi.MaskingOption", "ti.sysbios.family.arm.v6m"));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.StackInfo", om.findStrict("ti.sysbios.interfaces.IHwi.StackInfo", "ti.sysbios.family.arm.v6m"));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi$$CCR", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Hwi.CCR", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi$$NVIC", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Hwi.NVIC", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi$$ExcContext", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Hwi.ExcContext", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi$$BasicView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Hwi.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi$$DetailedView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Hwi.DetailedView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi$$ModuleView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Hwi.ModuleView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi$$InterruptObj", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Hwi.InterruptObj", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi$$Instance_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Hwi.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi$$Module_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Hwi.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sysbios.family.arm.v6m.Hwi.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi$$Object", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Hwi.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Hwi$$Params", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Hwi.Params", new Proto.Str(po, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.Handle", insP);
        if (isROV) {
            om.bind("ti.sysbios.family.arm.v6m.Hwi.Object", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Instance_State", "ti.sysbios.family.arm.v6m"));
        }//isROV
    }

    void IntrinsicsSupport$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.IntrinsicsSupport.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v6m.IntrinsicsSupport", new Value.Obj("ti.sysbios.family.arm.v6m.IntrinsicsSupport", po));
        pkgV.bind("IntrinsicsSupport", vo);
        // decls 
    }

    void TaskSupport$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.TaskSupport.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v6m.TaskSupport", new Value.Obj("ti.sysbios.family.arm.v6m.TaskSupport", po));
        pkgV.bind("TaskSupport", vo);
        // decls 
    }

    void Timer$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Timer.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v6m.Timer", new Value.Obj("ti.sysbios.family.arm.v6m.Timer", po));
        pkgV.bind("Timer", vo);
        // decls 
        om.bind("ti.sysbios.family.arm.v6m.Timer.StartMode", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode", "ti.sysbios.family.arm.v6m"));
        om.bind("ti.sysbios.family.arm.v6m.Timer.RunMode", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode", "ti.sysbios.family.arm.v6m"));
        om.bind("ti.sysbios.family.arm.v6m.Timer.Status", om.findStrict("ti.sysbios.interfaces.ITimer.Status", "ti.sysbios.family.arm.v6m"));
        om.bind("ti.sysbios.family.arm.v6m.Timer.PeriodType", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType", "ti.sysbios.family.arm.v6m"));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Timer$$BasicView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Timer.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Timer$$ModuleView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Timer.ModuleView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Timer$$DeviceView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Timer.DeviceView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Timer$$Instance_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Timer.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Timer$$Module_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Timer.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sysbios.family.arm.v6m.Timer.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Timer$$Object", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Timer.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.Timer$$Params", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.Timer.Params", new Proto.Str(po, false));
        om.bind("ti.sysbios.family.arm.v6m.Timer.Handle", insP);
        if (isROV) {
            om.bind("ti.sysbios.family.arm.v6m.Timer.Object", om.findStrict("ti.sysbios.family.arm.v6m.Timer.Instance_State", "ti.sysbios.family.arm.v6m"));
        }//isROV
    }

    void TimestampProvider$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.TimestampProvider.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v6m.TimestampProvider", new Value.Obj("ti.sysbios.family.arm.v6m.TimestampProvider", po));
        pkgV.bind("TimestampProvider", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v6m.TimestampProvider$$Module_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v6m.TimestampProvider.Module_State", new Proto.Str(spo, false));
    }

    void Clobber$$CONSTS()
    {
        // module Clobber
        om.bind("ti.sysbios.family.arm.v6m.Clobber.trashRegs", new Extern("ti_sysbios_family_arm_v6m_Clobber_trashRegs__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Clobber.postIntr", new Extern("ti_sysbios_family_arm_v6m_Clobber_postIntr__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Clobber.checkRegs", new Extern("ti_sysbios_family_arm_v6m_Clobber_checkRegs__E", "xdc_UInt(*)(xdc_UInt)", true, false));
    }

    void Hwi$$CONSTS()
    {
        // module Hwi
        om.bind("ti.sysbios.family.arm.v6m.Hwi.nvic", new Extern("ti_sysbios_family_arm_v6m_Hwi_nvic", "ti_sysbios_family_arm_v6m_Hwi_NVIC*", false, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.getStackInfo", new Extern("ti_sysbios_family_arm_v6m_Hwi_getStackInfo__E", "xdc_Bool(*)(ti_sysbios_interfaces_IHwi_StackInfo*,xdc_Bool)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.getCoreStackInfo", new Extern("ti_sysbios_family_arm_v6m_Hwi_getCoreStackInfo__E", "xdc_Bool(*)(ti_sysbios_interfaces_IHwi_StackInfo*,xdc_Bool,xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.startup", new Extern("ti_sysbios_family_arm_v6m_Hwi_startup__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.switchFromBootStack", new Extern("ti_sysbios_family_arm_v6m_Hwi_switchFromBootStack__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.post", new Extern("ti_sysbios_family_arm_v6m_Hwi_post__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.getTaskSP", new Extern("ti_sysbios_family_arm_v6m_Hwi_getTaskSP__E", "xdc_Char*(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.disableInterrupt", new Extern("ti_sysbios_family_arm_v6m_Hwi_disableInterrupt__E", "xdc_UInt(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.enableInterrupt", new Extern("ti_sysbios_family_arm_v6m_Hwi_enableInterrupt__E", "xdc_UInt(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.restoreInterrupt", new Extern("ti_sysbios_family_arm_v6m_Hwi_restoreInterrupt__E", "xdc_Void(*)(xdc_UInt,xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.clearInterrupt", new Extern("ti_sysbios_family_arm_v6m_Hwi_clearInterrupt__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.disableFxn", new Extern("ti_sysbios_family_arm_v6m_Hwi_disableFxn__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.enableFxn", new Extern("ti_sysbios_family_arm_v6m_Hwi_enableFxn__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.restoreFxn", new Extern("ti_sysbios_family_arm_v6m_Hwi_restoreFxn__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.plug", new Extern("ti_sysbios_family_arm_v6m_Hwi_plug__E", "xdc_Void(*)(xdc_UInt,xdc_Void*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.getHandle", new Extern("ti_sysbios_family_arm_v6m_Hwi_getHandle__E", "ti_sysbios_family_arm_v6m_Hwi_Handle(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.setPriority", new Extern("ti_sysbios_family_arm_v6m_Hwi_setPriority__E", "xdc_Void(*)(xdc_UInt,xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excSetBuffers", new Extern("ti_sysbios_family_arm_v6m_Hwi_excSetBuffers__E", "xdc_Void(*)(xdc_Ptr,xdc_Ptr)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.initNVIC", new Extern("ti_sysbios_family_arm_v6m_Hwi_initNVIC__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.initStacks", new Extern("ti_sysbios_family_arm_v6m_Hwi_initStacks__E", "xdc_Void(*)(xdc_Ptr)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.flushVnvic", new Extern("ti_sysbios_family_arm_v6m_Hwi_flushVnvic__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.postInit", new Extern("ti_sysbios_family_arm_v6m_Hwi_postInit__I", "xdc_Int(*)(ti_sysbios_family_arm_v6m_Hwi_Object*,xdc_runtime_Error_Block*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.updateNvic", new Extern("ti_sysbios_family_arm_v6m_Hwi_updateNvic__I", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excHandlerAsm", new Extern("ti_sysbios_family_arm_v6m_Hwi_excHandlerAsm__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excHandler", new Extern("ti_sysbios_family_arm_v6m_Hwi_excHandler__I", "xdc_Void(*)(xdc_UInt*,xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excHandlerMin", new Extern("ti_sysbios_family_arm_v6m_Hwi_excHandlerMin__I", "xdc_Void(*)(xdc_UInt*,xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excHandlerMax", new Extern("ti_sysbios_family_arm_v6m_Hwi_excHandlerMax__I", "xdc_Void(*)(xdc_UInt*,xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excFillContext", new Extern("ti_sysbios_family_arm_v6m_Hwi_excFillContext__I", "xdc_Void(*)(xdc_UInt*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excNmi", new Extern("ti_sysbios_family_arm_v6m_Hwi_excNmi__I", "xdc_Void(*)(xdc_UInt*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excHardFault", new Extern("ti_sysbios_family_arm_v6m_Hwi_excHardFault__I", "xdc_Void(*)(xdc_UInt*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excMemFault", new Extern("ti_sysbios_family_arm_v6m_Hwi_excMemFault__I", "xdc_Void(*)(xdc_UInt*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excBusFault", new Extern("ti_sysbios_family_arm_v6m_Hwi_excBusFault__I", "xdc_Void(*)(xdc_UInt*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excUsageFault", new Extern("ti_sysbios_family_arm_v6m_Hwi_excUsageFault__I", "xdc_Void(*)(xdc_UInt*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excSvCall", new Extern("ti_sysbios_family_arm_v6m_Hwi_excSvCall__I", "xdc_Void(*)(xdc_UInt*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excDebugMon", new Extern("ti_sysbios_family_arm_v6m_Hwi_excDebugMon__I", "xdc_Void(*)(xdc_UInt*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excReserved", new Extern("ti_sysbios_family_arm_v6m_Hwi_excReserved__I", "xdc_Void(*)(xdc_UInt*,xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excNoIsr", new Extern("ti_sysbios_family_arm_v6m_Hwi_excNoIsr__I", "xdc_Void(*)(xdc_UInt*,xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.excDumpRegs", new Extern("ti_sysbios_family_arm_v6m_Hwi_excDumpRegs__I", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.pendSV", new Extern("ti_sysbios_family_arm_v6m_Hwi_pendSV__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.dispatch", new Extern("ti_sysbios_family_arm_v6m_Hwi_dispatch__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.dispatchC", new Extern("ti_sysbios_family_arm_v6m_Hwi_dispatchC__I", "xdc_UInt(*)(xdc_UArg,xdc_UInt32,xdc_UInt32,ti_sysbios_family_arm_v6m_Hwi_Object*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.doSwiRestore", new Extern("ti_sysbios_family_arm_v6m_Hwi_doSwiRestore__I", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Hwi.doTaskRestore", new Extern("ti_sysbios_family_arm_v6m_Hwi_doTaskRestore__I", "xdc_Void(*)(xdc_UInt)", true, false));
    }

    void IntrinsicsSupport$$CONSTS()
    {
        // module IntrinsicsSupport
        om.bind("ti.sysbios.family.arm.v6m.IntrinsicsSupport.maxbit", new Extern("ti_sysbios_family_arm_v6m_IntrinsicsSupport_maxbit__E", "xdc_UInt(*)(xdc_UInt)", true, false));
    }

    void TaskSupport$$CONSTS()
    {
        // module TaskSupport
        om.bind("ti.sysbios.family.arm.v6m.TaskSupport.start", new Extern("ti_sysbios_family_arm_v6m_TaskSupport_start__E", "xdc_Ptr(*)(xdc_Ptr,xdc_Void(*)(xdc_Void),xdc_Void(*)(xdc_Void),xdc_runtime_Error_Block*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.TaskSupport.swap", new Extern("ti_sysbios_family_arm_v6m_TaskSupport_swap__E", "xdc_Void(*)(xdc_Ptr*,xdc_Ptr*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.TaskSupport.checkStack", new Extern("ti_sysbios_family_arm_v6m_TaskSupport_checkStack__E", "xdc_Bool(*)(xdc_Char*,xdc_SizeT)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.TaskSupport.stackUsed", new Extern("ti_sysbios_family_arm_v6m_TaskSupport_stackUsed__E", "xdc_SizeT(*)(xdc_Char*,xdc_SizeT)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.TaskSupport.getStackAlignment", new Extern("ti_sysbios_family_arm_v6m_TaskSupport_getStackAlignment__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.TaskSupport.getDefaultStackSize", new Extern("ti_sysbios_family_arm_v6m_TaskSupport_getDefaultStackSize__E", "xdc_SizeT(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.TaskSupport.getCheckValueAddr", new Extern("ti_sysbios_family_arm_v6m_TaskSupport_getCheckValueAddr__E", "xdc_Ptr(*)(xdc_Ptr)", true, false));
    }

    void Timer$$CONSTS()
    {
        // module Timer
        om.bind("ti.sysbios.family.arm.v6m.Timer.MAX_PERIOD", 0x00ffffffL);
        om.bind("ti.sysbios.family.arm.v6m.Timer.NUM_TIMER_DEVICES", 1L);
        om.bind("ti.sysbios.family.arm.v6m.Timer.TIMER_CLOCK_DIVIDER", 1L);
        om.bind("ti.sysbios.family.arm.v6m.Timer.MIN_SWEEP_PERIOD", 1L);
        om.bind("ti.sysbios.family.arm.v6m.Timer.getNumTimers", new Extern("ti_sysbios_family_arm_v6m_Timer_getNumTimers__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Timer.getStatus", new Extern("ti_sysbios_family_arm_v6m_Timer_getStatus__E", "ti_sysbios_interfaces_ITimer_Status(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Timer.startup", new Extern("ti_sysbios_family_arm_v6m_Timer_startup__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Timer.getHandle", new Extern("ti_sysbios_family_arm_v6m_Timer_getHandle__E", "ti_sysbios_family_arm_v6m_Timer_Handle(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Timer.getTickCount", new Extern("ti_sysbios_family_arm_v6m_Timer_getTickCount__E", "xdc_UInt32(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Timer.initDevice", new Extern("ti_sysbios_family_arm_v6m_Timer_initDevice__I", "xdc_Void(*)(ti_sysbios_family_arm_v6m_Timer_Object*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Timer.postInit", new Extern("ti_sysbios_family_arm_v6m_Timer_postInit__I", "xdc_Int(*)(ti_sysbios_family_arm_v6m_Timer_Object*,xdc_runtime_Error_Block*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Timer.oneShotStub", new Extern("ti_sysbios_family_arm_v6m_Timer_oneShotStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.Timer.periodicStub", new Extern("ti_sysbios_family_arm_v6m_Timer_periodicStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void TimestampProvider$$CONSTS()
    {
        // module TimestampProvider
        om.bind("ti.sysbios.family.arm.v6m.TimestampProvider.get32", new Extern("ti_sysbios_family_arm_v6m_TimestampProvider_get32__E", "xdc_Bits32(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.TimestampProvider.get64", new Extern("ti_sysbios_family_arm_v6m_TimestampProvider_get64__E", "xdc_Void(*)(xdc_runtime_Types_Timestamp64*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.TimestampProvider.getFreq", new Extern("ti_sysbios_family_arm_v6m_TimestampProvider_getFreq__E", "xdc_Void(*)(xdc_runtime_Types_FreqHz*)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.TimestampProvider.startTimer", new Extern("ti_sysbios_family_arm_v6m_TimestampProvider_startTimer__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v6m.TimestampProvider.rolloverFunc", new Extern("ti_sysbios_family_arm_v6m_TimestampProvider_rolloverFunc__E", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void Clobber$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Hwi$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v6m$Hwi$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sysbios.family.arm.v6m.Hwi.create() called before xdc.useModule('ti.sysbios.family.arm.v6m.Hwi')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.intNum, inst.$args.hwiFxn, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sysbios.family.arm.v6m.Hwi$$create", new Proto.Fxn(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Module", "ti.sysbios.family.arm.v6m"), om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Instance", "ti.sysbios.family.arm.v6m"), 3, 2, false));
                        fxn.addArg(0, "intNum", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                        fxn.addArg(1, "hwiFxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Params", "ti.sysbios.family.arm.v6m"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v6m$Hwi$$create = function( intNum, hwiFxn, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sysbios.family.arm.v6m.Hwi'];\n");
                sb.append("var __inst = xdc.om['ti.sysbios.family.arm.v6m.Hwi.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sysbios.family.arm.v6m']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {intNum:intNum, hwiFxn:hwiFxn});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sysbios.family.arm.v6m.Hwi'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [intNum, hwiFxn]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sysbios.family.arm.v6m.Hwi'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sysbios.family.arm.v6m.Hwi$$construct", new Proto.Fxn(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Module", "ti.sysbios.family.arm.v6m"), null, 4, 2, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$Object", "ti.sysbios.family.arm.v6m"), null);
                        fxn.addArg(1, "intNum", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                        fxn.addArg(2, "hwiFxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF);
                        fxn.addArg(3, "__params", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Params", "ti.sysbios.family.arm.v6m"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v6m$Hwi$$construct = function( __obj, intNum, hwiFxn, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sysbios.family.arm.v6m.Hwi'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {intNum:intNum, hwiFxn:hwiFxn});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sysbios.family.arm.v6m.Hwi'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sysbios.family.arm.v6m.Hwi'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void IntrinsicsSupport$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TaskSupport$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Timer$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v6m$Timer$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sysbios.family.arm.v6m.Timer.create() called before xdc.useModule('ti.sysbios.family.arm.v6m.Timer')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.id, inst.$args.tickFxn, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sysbios.family.arm.v6m.Timer$$create", new Proto.Fxn(om.findStrict("ti.sysbios.family.arm.v6m.Timer.Module", "ti.sysbios.family.arm.v6m"), om.findStrict("ti.sysbios.family.arm.v6m.Timer.Instance", "ti.sysbios.family.arm.v6m"), 3, 2, false));
                        fxn.addArg(0, "id", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                        fxn.addArg(1, "tickFxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Timer.Params", "ti.sysbios.family.arm.v6m"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v6m$Timer$$create = function( id, tickFxn, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sysbios.family.arm.v6m.Timer'];\n");
                sb.append("var __inst = xdc.om['ti.sysbios.family.arm.v6m.Timer.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sysbios.family.arm.v6m']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {id:id, tickFxn:tickFxn});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sysbios.family.arm.v6m.Timer'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [id, tickFxn]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sysbios.family.arm.v6m.Timer'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sysbios.family.arm.v6m.Timer$$construct", new Proto.Fxn(om.findStrict("ti.sysbios.family.arm.v6m.Timer.Module", "ti.sysbios.family.arm.v6m"), null, 4, 2, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$Object", "ti.sysbios.family.arm.v6m"), null);
                        fxn.addArg(1, "id", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                        fxn.addArg(2, "tickFxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF);
                        fxn.addArg(3, "__params", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Timer.Params", "ti.sysbios.family.arm.v6m"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v6m$Timer$$construct = function( __obj, id, tickFxn, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sysbios.family.arm.v6m.Timer'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {id:id, tickFxn:tickFxn});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sysbios.family.arm.v6m.Timer'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sysbios.family.arm.v6m.Timer'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void TimestampProvider$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Clobber$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Hwi$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Hwi.inUseMeta
        fxn = (Proto.Fxn)om.bind("ti.sysbios.family.arm.v6m.Hwi$$inUseMeta", new Proto.Fxn(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Module", "ti.sysbios.family.arm.v6m"), $$T_Bool, 1, 1, false));
                fxn.addArg(0, "intNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF);
    }

    void IntrinsicsSupport$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TaskSupport$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Timer$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TimestampProvider$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Clobber$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Hwi$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.CCR", "ti.sysbios.family.arm.v6m");
        sizes.clear();
        sizes.add(Global.newArray("STKALIGN", "UInt8"));
        sizes.add(Global.newArray("BFHFNMIGN", "UInt8"));
        sizes.add(Global.newArray("DIV_0_TRP", "UInt8"));
        sizes.add(Global.newArray("UNALIGN_TRP", "UInt8"));
        sizes.add(Global.newArray("USERSETMPEND", "UInt8"));
        sizes.add(Global.newArray("NONEBASETHRDENA", "UInt8"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.CCR']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.CCR']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.CCR'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.NVIC", "ti.sysbios.family.arm.v6m");
        sizes.clear();
        sizes.add(Global.newArray("RES_00", "UInt32"));
        sizes.add(Global.newArray("ICTR", "UInt32"));
        sizes.add(Global.newArray("RES_08", "UInt32"));
        sizes.add(Global.newArray("RES_0C", "UInt32"));
        sizes.add(Global.newArray("STCSR", "UInt32"));
        sizes.add(Global.newArray("STRVR", "UInt32"));
        sizes.add(Global.newArray("STCVR", "UInt32"));
        sizes.add(Global.newArray("STCALIB", "UInt32"));
        sizes.add(Global.newArray("RES_20", "A56;UInt32"));
        sizes.add(Global.newArray("ISER", "A8;UInt32"));
        sizes.add(Global.newArray("RES_120", "A24;UInt32"));
        sizes.add(Global.newArray("ICER", "A8;UInt32"));
        sizes.add(Global.newArray("RES_1A0", "A24;UInt32"));
        sizes.add(Global.newArray("ISPR", "A8;UInt32"));
        sizes.add(Global.newArray("RES_220", "A24;UInt32"));
        sizes.add(Global.newArray("ICPR", "A8;UInt32"));
        sizes.add(Global.newArray("RES_2A0", "A24;UInt32"));
        sizes.add(Global.newArray("IABR", "A8;UInt32"));
        sizes.add(Global.newArray("RES_320", "A56;UInt32"));
        sizes.add(Global.newArray("IPR", "A60;UInt32"));
        sizes.add(Global.newArray("RES_4F0", "A516;UInt32"));
        sizes.add(Global.newArray("CPUIDBR", "UInt32"));
        sizes.add(Global.newArray("ICSR", "UInt32"));
        sizes.add(Global.newArray("VTOR", "UInt32"));
        sizes.add(Global.newArray("AIRCR", "UInt32"));
        sizes.add(Global.newArray("SCR", "UInt32"));
        sizes.add(Global.newArray("CCR", "UInt32"));
        sizes.add(Global.newArray("SHPR", "A3;UInt32"));
        sizes.add(Global.newArray("SHCSR", "UInt32"));
        sizes.add(Global.newArray("CFSR", "UInt32"));
        sizes.add(Global.newArray("HFSR", "UInt32"));
        sizes.add(Global.newArray("DFSR", "UInt32"));
        sizes.add(Global.newArray("MMAR", "UInt32"));
        sizes.add(Global.newArray("BFAR", "UInt32"));
        sizes.add(Global.newArray("AFSR", "UInt32"));
        sizes.add(Global.newArray("PFR0", "UInt32"));
        sizes.add(Global.newArray("PFR1", "UInt32"));
        sizes.add(Global.newArray("DFR0", "UInt32"));
        sizes.add(Global.newArray("AFR0", "UInt32"));
        sizes.add(Global.newArray("MMFR0", "UInt32"));
        sizes.add(Global.newArray("MMFR1", "UInt32"));
        sizes.add(Global.newArray("MMFR2", "UInt32"));
        sizes.add(Global.newArray("MMFR3", "UInt32"));
        sizes.add(Global.newArray("ISAR0", "UInt32"));
        sizes.add(Global.newArray("ISAR1", "UInt32"));
        sizes.add(Global.newArray("ISAR2", "UInt32"));
        sizes.add(Global.newArray("ISAR3", "UInt32"));
        sizes.add(Global.newArray("ISAR4", "UInt32"));
        sizes.add(Global.newArray("RES_D74", "A5;UInt32"));
        sizes.add(Global.newArray("CPACR", "UInt32"));
        sizes.add(Global.newArray("RES_D8C", "A93;UInt32"));
        sizes.add(Global.newArray("STI", "UInt32"));
        sizes.add(Global.newArray("RES_F04", "A12;UInt32"));
        sizes.add(Global.newArray("FPCCR", "UInt32"));
        sizes.add(Global.newArray("FPCAR", "UInt32"));
        sizes.add(Global.newArray("FPDSCR", "UInt32"));
        sizes.add(Global.newArray("MVFR0", "UInt32"));
        sizes.add(Global.newArray("MVFR1", "UInt32"));
        sizes.add(Global.newArray("RES_F48", "A34;UInt32"));
        sizes.add(Global.newArray("PID4", "UInt32"));
        sizes.add(Global.newArray("PID5", "UInt32"));
        sizes.add(Global.newArray("PID6", "UInt32"));
        sizes.add(Global.newArray("PID7", "UInt32"));
        sizes.add(Global.newArray("PID0", "UInt32"));
        sizes.add(Global.newArray("PID1", "UInt32"));
        sizes.add(Global.newArray("PID2", "UInt32"));
        sizes.add(Global.newArray("PID3", "UInt32"));
        sizes.add(Global.newArray("CID0", "UInt32"));
        sizes.add(Global.newArray("CID1", "UInt32"));
        sizes.add(Global.newArray("CID2", "UInt32"));
        sizes.add(Global.newArray("CID3", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.NVIC']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.NVIC']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.NVIC'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.ExcContext", "ti.sysbios.family.arm.v6m");
        sizes.clear();
        sizes.add(Global.newArray("threadType", "Nti.sysbios.BIOS.ThreadType;;;;;"));
        sizes.add(Global.newArray("threadHandle", "UPtr"));
        sizes.add(Global.newArray("threadStack", "UPtr"));
        sizes.add(Global.newArray("threadStackSize", "USize"));
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
        sizes.add(Global.newArray("DFSR", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.ExcContext']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.ExcContext']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.ExcContext'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Instance_State", "ti.sysbios.family.arm.v6m");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("arg", "UIArg"));
        sizes.add(Global.newArray("fxn", "UFxn"));
        sizes.add(Global.newArray("irp", "UIArg"));
        sizes.add(Global.newArray("priority", "UInt8"));
        sizes.add(Global.newArray("intNum", "TInt16"));
        sizes.add(Global.newArray("hookEnv", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Module_State", "ti.sysbios.family.arm.v6m");
        sizes.clear();
        sizes.add(Global.newArray("taskSP", "UPtr"));
        sizes.add(Global.newArray("excActive", "UPtr"));
        sizes.add(Global.newArray("excContext", "UPtr"));
        sizes.add(Global.newArray("excStack", "UPtr"));
        sizes.add(Global.newArray("isrStack", "UPtr"));
        sizes.add(Global.newArray("isrStackBase", "UPtr"));
        sizes.add(Global.newArray("isrStackSize", "USize"));
        sizes.add(Global.newArray("vectorTableBase", "UPtr"));
        sizes.add(Global.newArray("swiTaskKeys", "UInt"));
        sizes.add(Global.newArray("dispatchTable", "UPtr"));
        sizes.add(Global.newArray("vnvicFlushRequired", "UShort"));
        sizes.add(Global.newArray("intAffinity", "UPtr"));
        sizes.add(Global.newArray("intAffinityMasks", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v6m.Hwi.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void IntrinsicsSupport$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void TaskSupport$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Timer$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v6m.Timer.Instance_State", "ti.sysbios.family.arm.v6m");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("staticInst", "UShort"));
        sizes.add(Global.newArray("id", "TInt"));
        sizes.add(Global.newArray("runMode", "Nti.sysbios.interfaces.ITimer.RunMode;;;;"));
        sizes.add(Global.newArray("startMode", "Nti.sysbios.interfaces.ITimer.StartMode;;;"));
        sizes.add(Global.newArray("period", "UInt"));
        sizes.add(Global.newArray("periodType", "Nti.sysbios.interfaces.ITimer.PeriodType;;;"));
        sizes.add(Global.newArray("intNum", "UInt"));
        sizes.add(Global.newArray("arg", "UIArg"));
        sizes.add(Global.newArray("tickFxn", "UFxn"));
        sizes.add(Global.newArray("extFreq", "Sxdc.runtime.Types;FreqHz"));
        sizes.add(Global.newArray("hwi", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v6m.Timer.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v6m.Timer.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v6m.Timer.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v6m.Timer.Module_State", "ti.sysbios.family.arm.v6m");
        sizes.clear();
        sizes.add(Global.newArray("tickCount", "UInt"));
        sizes.add(Global.newArray("availMask", "UInt"));
        sizes.add(Global.newArray("handle", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v6m.Timer.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v6m.Timer.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v6m.Timer.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TimestampProvider$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider.Module_State", "ti.sysbios.family.arm.v6m");
        sizes.clear();
        sizes.add(Global.newArray("timer", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v6m.TimestampProvider.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v6m.TimestampProvider.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v6m.TimestampProvider.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Clobber$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v6m/Clobber.xs");
        om.bind("ti.sysbios.family.arm.v6m.Clobber$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Clobber.Module", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Clobber.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sysbios.family.arm.v6m"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("postIntrCheck", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Clobber$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Clobber$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Clobber$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Clobber$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void Hwi$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v6m/Hwi.xs");
        om.bind("ti.sysbios.family.arm.v6m.Hwi$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Module", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.Module", om.findStrict("ti.sysbios.interfaces.IHwi.Module", "ti.sysbios.family.arm.v6m"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("NUM_INTERRUPTS", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
            po.addFld("NUM_PRIORITIES", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sysbios.family.arm.v6m"), $$UNDEF, "wh");
            po.addFld("LM_begin", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sysbios.family.arm.v6m"), Global.newObject("mask", Global.eval("0x0100 | 0x0200"), "msg", "LM_begin: hwi: 0x%x, func: 0x%x, preThread: %d, intNum: %d, irp: 0x%x"), "w");
            po.addFld("LD_end", (Proto)om.findStrict("xdc.runtime.Log$$Event", "ti.sysbios.family.arm.v6m"), Global.newObject("mask", 0x0200L, "msg", "LD_end: hwi: 0x%x"), "w");
            po.addFld("A_unsupportedMaskingOption", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "A_unsupportedMaskingOption: unsupported maskSetting."), "w");
            po.addFld("E_alreadyDefined", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_alreadyDefined: Hwi already defined: intr# %d"), "w");
            po.addFld("E_hwiLimitExceeded", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_hwiLimitExceeded: Too many interrupts defined"), "w");
            po.addFld("E_exception", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_exception: id = %d, pc = %08x.\nTo see more exception detail, set ti.sysbios.family.arm.v6m.Hwi.enableException = true or,\nexamine the Exception view for the ti.sysbios.family.arm.v6m.Hwi module using ROV."), "w");
            po.addFld("E_noIsr", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_noIsr: id = %d, pc = %08x"), "w");
            po.addFld("E_NMI", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_NMI: %s"), "w");
            po.addFld("E_hardFault", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_hardFault: %s"), "w");
            po.addFld("E_memFault", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_memFault: %s, address: %08x"), "w");
            po.addFld("E_busFault", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_busFault: %s, address: %08x"), "w");
            po.addFld("E_usageFault", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_usageFault: %s"), "w");
            po.addFld("E_svCall", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_svCall: svNum = %d"), "w");
            po.addFld("E_debugMon", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_debugMon: %s"), "w");
            po.addFld("E_reserved", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_reserved: %s %d"), "w");
            po.addFld("dispatchTableSize", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
            po.addFld("vectorTableAddress", new Proto.Adr("xdc_Ptr", "Pv"), 0x00000000L, "wh");
            po.addFld("resetVectorAddress", new Proto.Adr("xdc_Ptr", "Pv"), 0x00000000L, "wh");
            po.addFld("resetFunc", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), $$UNDEF, "wh");
            po.addFld("nmiFunc", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), $$UNDEF, "wh");
            po.addFld("hardFaultFunc", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), $$UNDEF, "wh");
            po.addFld("svCallFunc", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), $$UNDEF, "wh");
            po.addFld("debugMonFunc", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), $$UNDEF, "wh");
            po.addFld("reservedFunc", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), $$UNDEF, "wh");
            po.addFld("nullIsrFunc", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), $$UNDEF, "w");
            po.addFld("excHandlerFunc", new Proto.Adr("xdc_Void(*)(xdc_UInt*,xdc_UInt)", "PFv"), om.find("ti.sysbios.family.arm.v6m.Hwi.excHandlerMax"), "w");
            po.addFld("intAffinity", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt8)"), false), $$DEFAULT, "wh");
            po.addFld("enableException", $$T_Bool, true, "wh");
            po.addFld("excContextBuffer", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "wh");
            po.addFld("excContextBuffers", new Proto.Arr(new Proto.Adr("xdc_Ptr", "Pv"), false), $$DEFAULT, "wh");
            po.addFld("excStackBuffer", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "wh");
            po.addFld("excStackBuffers", new Proto.Arr(new Proto.Adr("xdc_Ptr", "Pv"), false), $$DEFAULT, "wh");
            po.addFld("excHookFunc", new Proto.Adr("xdc_Void(*)(ti_sysbios_family_arm_v6m_Hwi_ExcContext*)", "PFv"), null, "w");
            po.addFld("excHookFuncs", new Proto.Arr(new Proto.Adr("xdc_Void(*)(ti_sysbios_family_arm_v6m_Hwi_ExcContext*)", "PFv"), false), $$DEFAULT, "w");
            po.addFld("nvicCCR", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.CCR", "ti.sysbios.family.arm.v6m"), Global.newObject("STKALIGN", 1L, "BFHFNMIGN", 0L, "DIV_0_TRP", 0L, "UNALIGN_TRP", 0L, "USERSETMPEND", 0L, "NONEBASETHRDENA", 0L), "wh");
            po.addFld("numSparseInterrupts", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("isTiva", $$T_Bool, false, "wh");
            po.addFld("enableWA1_1", $$T_Bool, false, "wh");
            po.addFld("swiDisable", new Proto.Adr("xdc_UInt(*)(xdc_Void)", "PFn"), $$UNDEF, "w");
            po.addFld("swiRestoreHwi", new Proto.Adr("xdc_Void(*)(xdc_UInt)", "PFv"), $$UNDEF, "w");
            po.addFld("taskDisable", new Proto.Adr("xdc_UInt(*)(xdc_Void)", "PFn"), $$UNDEF, "w");
            po.addFld("taskRestoreHwi", new Proto.Adr("xdc_Void(*)(xdc_UInt)", "PFv"), $$UNDEF, "w");
            po.addFld("ccr", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
            po.addFld("hooks", new Proto.Arr((Proto)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.HookSet", "ti.sysbios.family.arm.v6m"), true), Global.newArray(new Object[]{}), "w");
            po.addFld("interrupt", new Proto.Arr((Proto)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.InterruptObj", "ti.sysbios.family.arm.v6m"), false), $$DEFAULT, "wh");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$create", "ti.sysbios.family.arm.v6m"), Global.get("ti$sysbios$family$arm$v6m$Hwi$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$construct", "ti.sysbios.family.arm.v6m"), Global.get("ti$sysbios$family$arm$v6m$Hwi$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Hwi$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Hwi$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Hwi$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Hwi$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Hwi$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Hwi$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "addHookSet");
                if (fxn != null) po.addFxn("addHookSet", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.IHwi$$addHookSet", "ti.sysbios.family.arm.v6m"), fxn);
                fxn = Global.get(cap, "viewGetStackInfo");
                if (fxn != null) po.addFxn("viewGetStackInfo", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.IHwi$$viewGetStackInfo", "ti.sysbios.family.arm.v6m"), fxn);
                po.addFxn("inUseMeta", (Proto.Fxn)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$inUseMeta", "ti.sysbios.family.arm.v6m"), Global.get(cap, "inUseMeta"));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Instance", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.Instance", om.findStrict("ti.sysbios.interfaces.IHwi.Instance", "ti.sysbios.family.arm.v6m"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("priority", Proto.Elm.newCNum("(xdc_Int)"), 255L, "w");
            po.addFld("maskSetting", (Proto)om.findStrict("ti.sysbios.interfaces.IHwi.MaskingOption", "ti.sysbios.family.arm.v6m"), om.find("ti.sysbios.interfaces.IHwi.MaskingOption_LOWER"), "w");
            po.addFld("useDispatcher", $$T_Bool, true, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$Params", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.Params", om.findStrict("ti.sysbios.interfaces.IHwi$$Params", "ti.sysbios.family.arm.v6m"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("priority", Proto.Elm.newCNum("(xdc_Int)"), 255L, "w");
            po.addFld("maskSetting", (Proto)om.findStrict("ti.sysbios.interfaces.IHwi.MaskingOption", "ti.sysbios.family.arm.v6m"), om.find("ti.sysbios.interfaces.IHwi.MaskingOption_LOWER"), "w");
            po.addFld("useDispatcher", $$T_Bool, true, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$Object", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.Object", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Instance", "ti.sysbios.family.arm.v6m"));
        // typedef Hwi.VectorFuncPtr
        om.bind("ti.sysbios.family.arm.v6m.Hwi.VectorFuncPtr", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"));
        // typedef Hwi.ExceptionHookFuncPtr
        om.bind("ti.sysbios.family.arm.v6m.Hwi.ExceptionHookFuncPtr", new Proto.Adr("xdc_Void(*)(ti_sysbios_family_arm_v6m_Hwi_ExcContext*)", "PFv"));
        // struct Hwi.CCR
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$CCR", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.CCR", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("STKALIGN", Proto.Elm.newCNum("(xdc_Bits8)"), $$UNDEF, "w");
                po.addFld("BFHFNMIGN", Proto.Elm.newCNum("(xdc_Bits8)"), $$UNDEF, "w");
                po.addFld("DIV_0_TRP", Proto.Elm.newCNum("(xdc_Bits8)"), $$UNDEF, "w");
                po.addFld("UNALIGN_TRP", Proto.Elm.newCNum("(xdc_Bits8)"), $$UNDEF, "w");
                po.addFld("USERSETMPEND", Proto.Elm.newCNum("(xdc_Bits8)"), $$UNDEF, "w");
                po.addFld("NONEBASETHRDENA", Proto.Elm.newCNum("(xdc_Bits8)"), $$UNDEF, "w");
        // struct Hwi.NVIC
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$NVIC", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.NVIC", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("RES_00", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("ICTR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RES_08", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RES_0C", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("STCSR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("STRVR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("STCVR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("STCALIB", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RES_20", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(56L)), $$DEFAULT, "w");
                po.addFld("ISER", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("RES_120", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(24L)), $$DEFAULT, "w");
                po.addFld("ICER", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("RES_1A0", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(24L)), $$DEFAULT, "w");
                po.addFld("ISPR", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("RES_220", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(24L)), $$DEFAULT, "w");
                po.addFld("ICPR", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("RES_2A0", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(24L)), $$DEFAULT, "w");
                po.addFld("IABR", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
                po.addFld("RES_320", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(56L)), $$DEFAULT, "w");
                po.addFld("IPR", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(60L)), $$DEFAULT, "w");
                po.addFld("RES_4F0", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(516L)), $$DEFAULT, "w");
                po.addFld("CPUIDBR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("ICSR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("VTOR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("AIRCR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("SCR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("CCR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("SHPR", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(3L)), $$DEFAULT, "w");
                po.addFld("SHCSR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("CFSR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("HFSR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("DFSR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("MMAR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("BFAR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("AFSR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("PFR0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("PFR1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("DFR0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("AFR0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("MMFR0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("MMFR1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("MMFR2", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("MMFR3", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("ISAR0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("ISAR1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("ISAR2", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("ISAR3", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("ISAR4", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RES_D74", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
                po.addFld("CPACR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RES_D8C", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(93L)), $$DEFAULT, "w");
                po.addFld("STI", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RES_F04", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(12L)), $$DEFAULT, "w");
                po.addFld("FPCCR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("FPCAR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("FPDSCR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("MVFR0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("MVFR1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RES_F48", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(34L)), $$DEFAULT, "w");
                po.addFld("PID4", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("PID5", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("PID6", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("PID7", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("PID0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("PID1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("PID2", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("PID3", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("CID0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("CID1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("CID2", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("CID3", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
        // struct Hwi.ExcContext
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$ExcContext", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.ExcContext", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("threadType", (Proto)om.findStrict("ti.sysbios.BIOS.ThreadType", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
                po.addFld("threadHandle", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("threadStack", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("threadStackSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
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
                po.addFld("DFSR", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct Hwi.BasicView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$BasicView", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("halHwiHandle", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("label", $$T_Str, $$UNDEF, "w");
                po.addFld("type", $$T_Str, $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("priority", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("fxn", $$T_Str, $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct Hwi.DetailedView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$DetailedView", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.DetailedView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("halHwiHandle", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("label", $$T_Str, $$UNDEF, "w");
                po.addFld("type", $$T_Str, $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("priority", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("fxn", $$T_Str, $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("irp", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("status", $$T_Str, $$UNDEF, "w");
        // struct Hwi.ModuleView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$ModuleView", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("options", new Proto.Arr($$T_Str, false, xdc.services.intern.xsr.Enum.intValue(4L)), $$DEFAULT, "w");
                po.addFld("activeInterrupt", $$T_Str, $$UNDEF, "w");
                po.addFld("pendingInterrupt", $$T_Str, $$UNDEF, "w");
                po.addFld("exception", $$T_Str, $$UNDEF, "w");
                po.addFld("hwiStackPeak", $$T_Str, $$UNDEF, "w");
                po.addFld("hwiStackSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("hwiStackBase", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // typedef Hwi.ExcHandlerFuncPtr
        om.bind("ti.sysbios.family.arm.v6m.Hwi.ExcHandlerFuncPtr", new Proto.Adr("xdc_Void(*)(xdc_UInt*,xdc_UInt)", "PFv"));
        // typedef Hwi.HandlerFuncPtr
        om.bind("ti.sysbios.family.arm.v6m.Hwi.HandlerFuncPtr", new Proto.Adr("xdc_Void(*)(ti_sysbios_family_arm_v6m_Hwi_Handle,xdc_UInt)", "PFv"));
        // struct Hwi.InterruptObj
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$InterruptObj", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.InterruptObj", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("used", $$T_Bool, $$UNDEF, "w");
                po.addFld("useDispatcher", $$T_Bool, $$UNDEF, "w");
                po.addFld("priority", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("fxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF, "w");
                po.addFld("hwi", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Handle", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
        // struct Hwi.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$Instance_State", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("fxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF, "w");
                po.addFld("irp", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("priority", Proto.Elm.newCNum("(xdc_UInt8)"), $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_Int16)"), $$UNDEF, "w");
                po.addFld("hookEnv", new Proto.Arr(new Proto.Adr("xdc_Ptr", "Pv"), false), $$DEFAULT, "w");
        // struct Hwi.Module_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$Module_State", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Hwi.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("taskSP", new Proto.Adr("xdc_Char*", "Pn"), $$UNDEF, "w");
                po.addFld("excActive", new Proto.Arr($$T_Bool, false), $$DEFAULT, "w");
                po.addFld("excContext", new Proto.Arr(new Proto.Adr("ti_sysbios_family_arm_v6m_Hwi_ExcContext*", "PS"), false), $$DEFAULT, "w");
                po.addFld("excStack", new Proto.Arr(new Proto.Adr("xdc_Ptr", "Pv"), false), $$DEFAULT, "w");
                po.addFld("isrStack", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("isrStackBase", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("isrStackSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("vectorTableBase", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("swiTaskKeys", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("dispatchTable", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("vnvicFlushRequired", $$T_Bool, $$UNDEF, "w");
                po.addFld("intAffinity", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt8)"), false), $$DEFAULT, "w");
                po.addFld("intAffinityMasks", new Proto.Arr(new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false), false), $$DEFAULT, "w");
    }

    void IntrinsicsSupport$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.IntrinsicsSupport.Module", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.IntrinsicsSupport.Module", om.findStrict("ti.sysbios.interfaces.IIntrinsicsSupport.Module", "ti.sysbios.family.arm.v6m"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void TaskSupport$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v6m/TaskSupport.xs");
        om.bind("ti.sysbios.family.arm.v6m.TaskSupport$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport.Module", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.TaskSupport.Module", om.findStrict("ti.sysbios.interfaces.ITaskSupport.Module", "ti.sysbios.family.arm.v6m"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("defaultStackSize", Proto.Elm.newCNum("(xdc_SizeT)"), 2048L, "r");
            po.addFld("stackAlignment", Proto.Elm.newCNum("(xdc_UInt)"), 8L, "r");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.TaskSupport$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.TaskSupport$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.TaskSupport$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.TaskSupport$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "stackUsed$view");
                if (fxn != null) po.addFxn("stackUsed$view", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.ITaskSupport$$stackUsed$view", "ti.sysbios.family.arm.v6m"), fxn);
                fxn = Global.get(cap, "getCallStack$view");
                if (fxn != null) po.addFxn("getCallStack$view", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.ITaskSupport$$getCallStack$view", "ti.sysbios.family.arm.v6m"), fxn);
    }

    void Timer$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v6m/Timer.xs");
        om.bind("ti.sysbios.family.arm.v6m.Timer$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer.Module", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Timer.Module", om.findStrict("ti.sysbios.interfaces.ITimer.Module", "ti.sysbios.family.arm.v6m"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~0"), "rh");
                po.addFld("MAX_PERIOD", Proto.Elm.newCNum("(xdc_UInt)"), 0x00ffffffL, "rh");
                po.addFld("NUM_TIMER_DEVICES", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("TIMER_CLOCK_DIVIDER", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("MIN_SWEEP_PERIOD", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sysbios.family.arm.v6m"), $$UNDEF, "wh");
            po.addFld("E_invalidTimer", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_invalidTimer: Invalid Timer Id %d"), "w");
            po.addFld("E_notAvailable", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_notAvailable: Timer not available %d"), "w");
            po.addFld("E_cannotSupport", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v6m"), Global.newObject("msg", "E_cannotSupport: Timer cannot support requested period %d"), "w");
            po.addFld("anyMask", Proto.Elm.newCNum("(xdc_UInt)"), 0x1L, "w");
            po.addFld("timerInUse", $$T_Bool, false, "wh");
            po.addFld("startupNeeded", Proto.Elm.newCNum("(xdc_UInt)"), false, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$create", "ti.sysbios.family.arm.v6m"), Global.get("ti$sysbios$family$arm$v6m$Timer$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$construct", "ti.sysbios.family.arm.v6m"), Global.get("ti$sysbios$family$arm$v6m$Timer$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Timer$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Timer$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Timer$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Timer$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Timer$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.Timer$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "viewGetCurrentClockTick");
                if (fxn != null) po.addFxn("viewGetCurrentClockTick", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.ITimer$$viewGetCurrentClockTick", "ti.sysbios.family.arm.v6m"), fxn);
                fxn = Global.get(cap, "getFreqMeta");
                if (fxn != null) po.addFxn("getFreqMeta", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.ITimer$$getFreqMeta", "ti.sysbios.family.arm.v6m"), fxn);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer.Instance", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Timer.Instance", om.findStrict("ti.sysbios.interfaces.ITimer.Instance", "ti.sysbios.family.arm.v6m"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~0"), "rh");
                po.addFld("MAX_PERIOD", Proto.Elm.newCNum("(xdc_UInt)"), 0x00ffffffL, "rh");
                po.addFld("NUM_TIMER_DEVICES", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("TIMER_CLOCK_DIVIDER", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("MIN_SWEEP_PERIOD", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
        if (isCFG) {
            po.addFld("hwiParams", new Proto.Adr("ti_sysbios_family_arm_v6m_Hwi_Params*", "PS"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$Params", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Timer.Params", om.findStrict("ti.sysbios.interfaces.ITimer$$Params", "ti.sysbios.family.arm.v6m"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~0"), "rh");
                po.addFld("MAX_PERIOD", Proto.Elm.newCNum("(xdc_UInt)"), 0x00ffffffL, "rh");
                po.addFld("NUM_TIMER_DEVICES", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("TIMER_CLOCK_DIVIDER", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("MIN_SWEEP_PERIOD", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
        if (isCFG) {
            po.addFld("hwiParams", new Proto.Adr("ti_sysbios_family_arm_v6m_Hwi_Params*", "PS"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$Object", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Timer.Object", om.findStrict("ti.sysbios.family.arm.v6m.Timer.Instance", "ti.sysbios.family.arm.v6m"));
        // struct Timer.BasicView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$BasicView", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Timer.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("halTimerHandle", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("label", $$T_Str, $$UNDEF, "w");
                po.addFld("id", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("device", $$T_Str, $$UNDEF, "w");
                po.addFld("startMode", $$T_Str, $$UNDEF, "w");
                po.addFld("runMode", $$T_Str, $$UNDEF, "w");
                po.addFld("period", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("periodType", $$T_Str, $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("tickFxn", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("extFreq", $$T_Str, $$UNDEF, "w");
                po.addFld("hwiHandle", $$T_Str, $$UNDEF, "w");
                po.addFxn("$xml", $$T_Met, Global.get("$$xml"));
        // struct Timer.ModuleView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$ModuleView", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Timer.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("availMask", $$T_Str, $$UNDEF, "w");
                po.addFld("tickCount", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        // struct Timer.DeviceView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$DeviceView", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Timer.DeviceView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("id", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("device", $$T_Str, $$UNDEF, "w");
                po.addFld("devAddr", $$T_Str, $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("runMode", $$T_Str, $$UNDEF, "w");
                po.addFld("period", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("currCount", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("remainingCount", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        // struct Timer.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$Instance_State", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Timer.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("staticInst", $$T_Bool, $$UNDEF, "w");
                po.addFld("id", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("runMode", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Timer.RunMode", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
                po.addFld("startMode", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Timer.StartMode", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
                po.addFld("period", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("periodType", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Timer.PeriodType", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("tickFxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF, "w");
                po.addFld("extFreq", (Proto)om.findStrict("xdc.runtime.Types.FreqHz", "ti.sysbios.family.arm.v6m"), $$DEFAULT, "w");
                po.addFld("hwi", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Handle", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
        // struct Timer.Module_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$Module_State", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.Timer.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("tickCount", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("availMask", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("handle", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Timer.Handle", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
    }

    void TimestampProvider$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v6m/TimestampProvider.xs");
        om.bind("ti.sysbios.family.arm.v6m.TimestampProvider$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider.Module", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.TimestampProvider.Module", om.findStrict("ti.sysbios.interfaces.ITimestamp.Module", "ti.sysbios.family.arm.v6m"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("configTimer", $$T_Bool, false, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.TimestampProvider$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.TimestampProvider$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.TimestampProvider$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v6m.TimestampProvider$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getFreqMeta");
                if (fxn != null) po.addFxn("getFreqMeta", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.ITimestamp$$getFreqMeta", "ti.sysbios.family.arm.v6m"), fxn);
        // struct TimestampProvider.Module_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider$$Module_State", "ti.sysbios.family.arm.v6m");
        po.init("ti.sysbios.family.arm.v6m.TimestampProvider.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("timer", (Proto)om.findStrict("ti.sysbios.family.arm.v6m.Timer.Handle", "ti.sysbios.family.arm.v6m"), $$UNDEF, "w");
    }

    void Clobber$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Clobber", "ti.sysbios.family.arm.v6m");
    }

    void Hwi$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi", "ti.sysbios.family.arm.v6m");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$Instance_State", "ti.sysbios.family.arm.v6m");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("CCR$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v6m.Hwi.CCR", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$CCR", "ti.sysbios.family.arm.v6m");
        vo.bind("NVIC$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v6m.Hwi.NVIC", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$NVIC", "ti.sysbios.family.arm.v6m");
        vo.bind("ExcContext$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v6m.Hwi.ExcContext", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$ExcContext", "ti.sysbios.family.arm.v6m");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v6m.Hwi.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$Instance_State", "ti.sysbios.family.arm.v6m");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v6m.Hwi.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$Module_State", "ti.sysbios.family.arm.v6m");
        po.bind("excActive$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Bool", "isScalar", true));
        po.bind("intAffinity$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_UInt8", "isScalar", true));
    }

    void IntrinsicsSupport$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.IntrinsicsSupport", "ti.sysbios.family.arm.v6m");
    }

    void TaskSupport$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport", "ti.sysbios.family.arm.v6m");
    }

    void Timer$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer", "ti.sysbios.family.arm.v6m");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$Instance_State", "ti.sysbios.family.arm.v6m");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v6m.Timer.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$Instance_State", "ti.sysbios.family.arm.v6m");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v6m.Timer.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer$$Module_State", "ti.sysbios.family.arm.v6m");
    }

    void TimestampProvider$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider", "ti.sysbios.family.arm.v6m");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v6m.TimestampProvider.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider$$Module_State", "ti.sysbios.family.arm.v6m");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sysbios.family.arm.v6m.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sysbios.family.arm.v6m"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v6m/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sysbios.family.arm.v6m"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sysbios.family.arm.v6m"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sysbios.family.arm.v6m"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sysbios.family.arm.v6m"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sysbios.family.arm.v6m"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sysbios.family.arm.v6m"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sysbios.family.arm.v6m", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sysbios.family.arm.v6m");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sysbios.family.arm.v6m.");
        pkgV.bind("$vers", Global.newArray(2, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sysbios.interfaces", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sysbios.family.arm.v6m'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sysbios.family.arm.v6m$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sysbios.family.arm.v6m$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sysbios.family.arm.v6m$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/sysbios/debug/ti.sysbios.family.arm.v6m.aem0',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/sysbios/debug/ti.sysbios.family.arm.v6m.aem0', {target: 'ti.targets.arm.elf.M0', suffix: 'em0'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Clobber$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Clobber", "ti.sysbios.family.arm.v6m");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Clobber.Module", "ti.sysbios.family.arm.v6m");
        vo.init2(po, "ti.sysbios.family.arm.v6m.Clobber", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v6m.Clobber$$capsule", "ti.sysbios.family.arm.v6m"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v6m", "ti.sysbios.family.arm.v6m"));
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
        mcfgs.add("postIntrCheck");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v6m")).add(vo);
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
        vo.bind("trashRegs", om.findStrict("ti.sysbios.family.arm.v6m.Clobber.trashRegs", "ti.sysbios.family.arm.v6m"));
        vo.bind("postIntr", om.findStrict("ti.sysbios.family.arm.v6m.Clobber.postIntr", "ti.sysbios.family.arm.v6m"));
        vo.bind("checkRegs", om.findStrict("ti.sysbios.family.arm.v6m.Clobber.checkRegs", "ti.sysbios.family.arm.v6m"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v6m_Clobber_Module__startupDone__E", "ti_sysbios_family_arm_v6m_Clobber_trashRegs__E", "ti_sysbios_family_arm_v6m_Clobber_postIntr__E", "ti_sysbios_family_arm_v6m_Clobber_checkRegs__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Clobber", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Clobber");
    }

    void Hwi$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi", "ti.sysbios.family.arm.v6m");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Module", "ti.sysbios.family.arm.v6m");
        vo.init2(po, "ti.sysbios.family.arm.v6m.Hwi", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v6m.Hwi$$capsule", "ti.sysbios.family.arm.v6m"));
        vo.bind("Instance", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Instance", "ti.sysbios.family.arm.v6m"));
        vo.bind("Params", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Params", "ti.sysbios.family.arm.v6m"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Params", "ti.sysbios.family.arm.v6m")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Handle", "ti.sysbios.family.arm.v6m"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v6m", "ti.sysbios.family.arm.v6m"));
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
        vo.bind("FuncPtr", om.findStrict("ti.sysbios.interfaces.IHwi.FuncPtr", "ti.sysbios.family.arm.v6m"));
        vo.bind("Irp", om.findStrict("ti.sysbios.interfaces.IHwi.Irp", "ti.sysbios.family.arm.v6m"));
        vo.bind("HookSet", om.findStrict("ti.sysbios.interfaces.IHwi.HookSet", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.interfaces.IHwi.HookSet", "ti.sysbios.family.arm.v6m"));
        vo.bind("MaskingOption", om.findStrict("ti.sysbios.interfaces.IHwi.MaskingOption", "ti.sysbios.family.arm.v6m"));
        vo.bind("StackInfo", om.findStrict("ti.sysbios.interfaces.IHwi.StackInfo", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.interfaces.IHwi.StackInfo", "ti.sysbios.family.arm.v6m"));
        mcfgs.add("dispatcherAutoNestingSupport");
        mcfgs.add("dispatcherSwiSupport");
        mcfgs.add("dispatcherTaskSupport");
        mcfgs.add("dispatcherIrpTrackingSupport");
        mcfgs.add("NUM_INTERRUPTS");
        mcfgs.add("NUM_PRIORITIES");
        vo.bind("VectorFuncPtr", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.VectorFuncPtr", "ti.sysbios.family.arm.v6m"));
        vo.bind("ExceptionHookFuncPtr", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.ExceptionHookFuncPtr", "ti.sysbios.family.arm.v6m"));
        vo.bind("CCR", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.CCR", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.CCR", "ti.sysbios.family.arm.v6m"));
        vo.bind("NVIC", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.NVIC", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.NVIC", "ti.sysbios.family.arm.v6m"));
        vo.bind("nvic", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.nvic", "ti.sysbios.family.arm.v6m"));
        vo.bind("ExcContext", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.ExcContext", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.ExcContext", "ti.sysbios.family.arm.v6m"));
        vo.bind("BasicView", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.BasicView", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.BasicView", "ti.sysbios.family.arm.v6m"));
        vo.bind("DetailedView", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.DetailedView", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.DetailedView", "ti.sysbios.family.arm.v6m"));
        vo.bind("ModuleView", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.ModuleView", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.ModuleView", "ti.sysbios.family.arm.v6m"));
        mcfgs.add("LM_begin");
        mcfgs.add("LD_end");
        mcfgs.add("A_unsupportedMaskingOption");
        mcfgs.add("E_alreadyDefined");
        mcfgs.add("E_hwiLimitExceeded");
        mcfgs.add("E_exception");
        mcfgs.add("E_noIsr");
        mcfgs.add("E_NMI");
        mcfgs.add("E_hardFault");
        mcfgs.add("E_memFault");
        mcfgs.add("E_busFault");
        mcfgs.add("E_usageFault");
        mcfgs.add("E_svCall");
        mcfgs.add("E_debugMon");
        mcfgs.add("E_reserved");
        mcfgs.add("nullIsrFunc");
        vo.bind("ExcHandlerFuncPtr", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.ExcHandlerFuncPtr", "ti.sysbios.family.arm.v6m"));
        mcfgs.add("excHandlerFunc");
        mcfgs.add("excHookFunc");
        mcfgs.add("excHookFuncs");
        mcfgs.add("numSparseInterrupts");
        icfgs.add("numSparseInterrupts");
        icfgs.add("isTiva");
        icfgs.add("enableWA1_1");
        mcfgs.add("swiDisable");
        icfgs.add("swiDisable");
        mcfgs.add("swiRestoreHwi");
        icfgs.add("swiRestoreHwi");
        mcfgs.add("taskDisable");
        icfgs.add("taskDisable");
        mcfgs.add("taskRestoreHwi");
        icfgs.add("taskRestoreHwi");
        mcfgs.add("ccr");
        icfgs.add("ccr");
        mcfgs.add("hooks");
        icfgs.add("hooks");
        vo.bind("HandlerFuncPtr", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.HandlerFuncPtr", "ti.sysbios.family.arm.v6m"));
        vo.bind("InterruptObj", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.InterruptObj", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.InterruptObj", "ti.sysbios.family.arm.v6m"));
        icfgs.add("interrupt");
        vo.bind("Instance_State", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Instance_State", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Instance_State", "ti.sysbios.family.arm.v6m"));
        vo.bind("Module_State", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Module_State", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Module_State", "ti.sysbios.family.arm.v6m"));
        vo.bind("MaskingOption_NONE", om.findStrict("ti.sysbios.interfaces.IHwi.MaskingOption_NONE", "ti.sysbios.family.arm.v6m"));
        vo.bind("MaskingOption_ALL", om.findStrict("ti.sysbios.interfaces.IHwi.MaskingOption_ALL", "ti.sysbios.family.arm.v6m"));
        vo.bind("MaskingOption_SELF", om.findStrict("ti.sysbios.interfaces.IHwi.MaskingOption_SELF", "ti.sysbios.family.arm.v6m"));
        vo.bind("MaskingOption_BITMASK", om.findStrict("ti.sysbios.interfaces.IHwi.MaskingOption_BITMASK", "ti.sysbios.family.arm.v6m"));
        vo.bind("MaskingOption_LOWER", om.findStrict("ti.sysbios.interfaces.IHwi.MaskingOption_LOWER", "ti.sysbios.family.arm.v6m"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sysbios.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v6m")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sysbios.family.arm.v6m.Hwi$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sysbios$family$arm$v6m$Hwi$$__initObject"));
        }//isCFG
        vo.bind("getStackInfo", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.getStackInfo", "ti.sysbios.family.arm.v6m"));
        vo.bind("getCoreStackInfo", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.getCoreStackInfo", "ti.sysbios.family.arm.v6m"));
        vo.bind("startup", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.startup", "ti.sysbios.family.arm.v6m"));
        vo.bind("switchFromBootStack", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.switchFromBootStack", "ti.sysbios.family.arm.v6m"));
        vo.bind("post", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.post", "ti.sysbios.family.arm.v6m"));
        vo.bind("getTaskSP", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.getTaskSP", "ti.sysbios.family.arm.v6m"));
        vo.bind("disableInterrupt", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.disableInterrupt", "ti.sysbios.family.arm.v6m"));
        vo.bind("enableInterrupt", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.enableInterrupt", "ti.sysbios.family.arm.v6m"));
        vo.bind("restoreInterrupt", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.restoreInterrupt", "ti.sysbios.family.arm.v6m"));
        vo.bind("clearInterrupt", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.clearInterrupt", "ti.sysbios.family.arm.v6m"));
        vo.bind("disableFxn", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.disableFxn", "ti.sysbios.family.arm.v6m"));
        vo.bind("enableFxn", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.enableFxn", "ti.sysbios.family.arm.v6m"));
        vo.bind("restoreFxn", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.restoreFxn", "ti.sysbios.family.arm.v6m"));
        vo.bind("plug", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.plug", "ti.sysbios.family.arm.v6m"));
        vo.bind("getHandle", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.getHandle", "ti.sysbios.family.arm.v6m"));
        vo.bind("setPriority", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.setPriority", "ti.sysbios.family.arm.v6m"));
        vo.bind("excSetBuffers", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excSetBuffers", "ti.sysbios.family.arm.v6m"));
        vo.bind("initNVIC", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.initNVIC", "ti.sysbios.family.arm.v6m"));
        vo.bind("initStacks", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.initStacks", "ti.sysbios.family.arm.v6m"));
        vo.bind("flushVnvic", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.flushVnvic", "ti.sysbios.family.arm.v6m"));
        vo.bind("postInit", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.postInit", "ti.sysbios.family.arm.v6m"));
        vo.bind("updateNvic", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.updateNvic", "ti.sysbios.family.arm.v6m"));
        vo.bind("excHandlerAsm", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excHandlerAsm", "ti.sysbios.family.arm.v6m"));
        vo.bind("excHandler", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excHandler", "ti.sysbios.family.arm.v6m"));
        vo.bind("excHandlerMin", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excHandlerMin", "ti.sysbios.family.arm.v6m"));
        vo.bind("excHandlerMax", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excHandlerMax", "ti.sysbios.family.arm.v6m"));
        vo.bind("excFillContext", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excFillContext", "ti.sysbios.family.arm.v6m"));
        vo.bind("excNmi", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excNmi", "ti.sysbios.family.arm.v6m"));
        vo.bind("excHardFault", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excHardFault", "ti.sysbios.family.arm.v6m"));
        vo.bind("excMemFault", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excMemFault", "ti.sysbios.family.arm.v6m"));
        vo.bind("excBusFault", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excBusFault", "ti.sysbios.family.arm.v6m"));
        vo.bind("excUsageFault", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excUsageFault", "ti.sysbios.family.arm.v6m"));
        vo.bind("excSvCall", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excSvCall", "ti.sysbios.family.arm.v6m"));
        vo.bind("excDebugMon", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excDebugMon", "ti.sysbios.family.arm.v6m"));
        vo.bind("excReserved", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excReserved", "ti.sysbios.family.arm.v6m"));
        vo.bind("excNoIsr", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excNoIsr", "ti.sysbios.family.arm.v6m"));
        vo.bind("excDumpRegs", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.excDumpRegs", "ti.sysbios.family.arm.v6m"));
        vo.bind("pendSV", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.pendSV", "ti.sysbios.family.arm.v6m"));
        vo.bind("dispatch", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.dispatch", "ti.sysbios.family.arm.v6m"));
        vo.bind("dispatchC", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.dispatchC", "ti.sysbios.family.arm.v6m"));
        vo.bind("doSwiRestore", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.doSwiRestore", "ti.sysbios.family.arm.v6m"));
        vo.bind("doTaskRestore", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.doTaskRestore", "ti.sysbios.family.arm.v6m"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v6m_Hwi_Handle__label__E", "ti_sysbios_family_arm_v6m_Hwi_Module__startupDone__E", "ti_sysbios_family_arm_v6m_Hwi_Object__create__E", "ti_sysbios_family_arm_v6m_Hwi_Object__delete__E", "ti_sysbios_family_arm_v6m_Hwi_Object__destruct__E", "ti_sysbios_family_arm_v6m_Hwi_Object__get__E", "ti_sysbios_family_arm_v6m_Hwi_Object__first__E", "ti_sysbios_family_arm_v6m_Hwi_Object__next__E", "ti_sysbios_family_arm_v6m_Hwi_Params__init__E", "ti_sysbios_family_arm_v6m_Hwi_getStackInfo__E", "ti_sysbios_family_arm_v6m_Hwi_getCoreStackInfo__E", "ti_sysbios_family_arm_v6m_Hwi_startup__E", "ti_sysbios_family_arm_v6m_Hwi_switchFromBootStack__E", "ti_sysbios_family_arm_v6m_Hwi_post__E", "ti_sysbios_family_arm_v6m_Hwi_getTaskSP__E", "ti_sysbios_family_arm_v6m_Hwi_disableInterrupt__E", "ti_sysbios_family_arm_v6m_Hwi_enableInterrupt__E", "ti_sysbios_family_arm_v6m_Hwi_restoreInterrupt__E", "ti_sysbios_family_arm_v6m_Hwi_clearInterrupt__E", "ti_sysbios_family_arm_v6m_Hwi_getFunc__E", "ti_sysbios_family_arm_v6m_Hwi_setFunc__E", "ti_sysbios_family_arm_v6m_Hwi_getHookContext__E", "ti_sysbios_family_arm_v6m_Hwi_setHookContext__E", "ti_sysbios_family_arm_v6m_Hwi_getIrp__E", "ti_sysbios_family_arm_v6m_Hwi_disable__E", "ti_sysbios_family_arm_v6m_Hwi_enable__E", "ti_sysbios_family_arm_v6m_Hwi_restore__E", "ti_sysbios_family_arm_v6m_Hwi_disableFxn__E", "ti_sysbios_family_arm_v6m_Hwi_enableFxn__E", "ti_sysbios_family_arm_v6m_Hwi_restoreFxn__E", "ti_sysbios_family_arm_v6m_Hwi_plug__E", "ti_sysbios_family_arm_v6m_Hwi_getHandle__E", "ti_sysbios_family_arm_v6m_Hwi_setPriority__E", "ti_sysbios_family_arm_v6m_Hwi_excSetBuffers__E", "ti_sysbios_family_arm_v6m_Hwi_initNVIC__E", "ti_sysbios_family_arm_v6m_Hwi_initStacks__E", "ti_sysbios_family_arm_v6m_Hwi_flushVnvic__E", "ti_sysbios_family_arm_v6m_Hwi_reconfig__E"));
        vo.bind("$$logEvtCfgs", Global.newArray("LM_begin", "LD_end"));
        vo.bind("$$errorDescCfgs", Global.newArray("E_alreadyDefined", "E_hwiLimitExceeded", "E_exception", "E_noIsr", "E_NMI", "E_hardFault", "E_memFault", "E_busFault", "E_usageFault", "E_svCall", "E_debugMon", "E_reserved"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_unsupportedMaskingOption"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Hwi.xdt");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sysbios.family.arm.v6m.Hwi.Object", "ti.sysbios.family.arm.v6m"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./Hwi.xdt");
        pkgV.bind("Hwi", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Hwi");
    }

    void IntrinsicsSupport$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.IntrinsicsSupport", "ti.sysbios.family.arm.v6m");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.IntrinsicsSupport.Module", "ti.sysbios.family.arm.v6m");
        vo.init2(po, "ti.sysbios.family.arm.v6m.IntrinsicsSupport", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v6m", "ti.sysbios.family.arm.v6m"));
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
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sysbios.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v6m")).add(vo);
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
        vo.bind("maxbit", om.findStrict("ti.sysbios.family.arm.v6m.IntrinsicsSupport.maxbit", "ti.sysbios.family.arm.v6m"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v6m_IntrinsicsSupport_Module__startupDone__E", "ti_sysbios_family_arm_v6m_IntrinsicsSupport_maxbit__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("IntrinsicsSupport", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IntrinsicsSupport");
    }

    void TaskSupport$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport", "ti.sysbios.family.arm.v6m");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport.Module", "ti.sysbios.family.arm.v6m");
        vo.init2(po, "ti.sysbios.family.arm.v6m.TaskSupport", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport$$capsule", "ti.sysbios.family.arm.v6m"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v6m", "ti.sysbios.family.arm.v6m"));
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
        vo.bind("FuncPtr", om.findStrict("ti.sysbios.interfaces.ITaskSupport.FuncPtr", "ti.sysbios.family.arm.v6m"));
        mcfgs.add("defaultStackSize");
        mcfgs.add("stackAlignment");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sysbios.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v6m")).add(vo);
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
        vo.bind("start", om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport.start", "ti.sysbios.family.arm.v6m"));
        vo.bind("swap", om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport.swap", "ti.sysbios.family.arm.v6m"));
        vo.bind("checkStack", om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport.checkStack", "ti.sysbios.family.arm.v6m"));
        vo.bind("stackUsed", om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport.stackUsed", "ti.sysbios.family.arm.v6m"));
        vo.bind("getStackAlignment", om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport.getStackAlignment", "ti.sysbios.family.arm.v6m"));
        vo.bind("getDefaultStackSize", om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport.getDefaultStackSize", "ti.sysbios.family.arm.v6m"));
        vo.bind("getCheckValueAddr", om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport.getCheckValueAddr", "ti.sysbios.family.arm.v6m"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v6m_TaskSupport_Module__startupDone__E", "ti_sysbios_family_arm_v6m_TaskSupport_start__E", "ti_sysbios_family_arm_v6m_TaskSupport_swap__E", "ti_sysbios_family_arm_v6m_TaskSupport_checkStack__E", "ti_sysbios_family_arm_v6m_TaskSupport_stackUsed__E", "ti_sysbios_family_arm_v6m_TaskSupport_getStackAlignment__E", "ti_sysbios_family_arm_v6m_TaskSupport_getDefaultStackSize__E", "ti_sysbios_family_arm_v6m_TaskSupport_getCheckValueAddr__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TaskSupport", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TaskSupport");
    }

    void Timer$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer", "ti.sysbios.family.arm.v6m");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer.Module", "ti.sysbios.family.arm.v6m");
        vo.init2(po, "ti.sysbios.family.arm.v6m.Timer", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v6m.Timer$$capsule", "ti.sysbios.family.arm.v6m"));
        vo.bind("Instance", om.findStrict("ti.sysbios.family.arm.v6m.Timer.Instance", "ti.sysbios.family.arm.v6m"));
        vo.bind("Params", om.findStrict("ti.sysbios.family.arm.v6m.Timer.Params", "ti.sysbios.family.arm.v6m"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sysbios.family.arm.v6m.Timer.Params", "ti.sysbios.family.arm.v6m")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sysbios.family.arm.v6m.Timer.Handle", "ti.sysbios.family.arm.v6m"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v6m", "ti.sysbios.family.arm.v6m"));
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
        vo.bind("FuncPtr", om.findStrict("ti.sysbios.interfaces.ITimer.FuncPtr", "ti.sysbios.family.arm.v6m"));
        vo.bind("StartMode", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode", "ti.sysbios.family.arm.v6m"));
        vo.bind("RunMode", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode", "ti.sysbios.family.arm.v6m"));
        vo.bind("Status", om.findStrict("ti.sysbios.interfaces.ITimer.Status", "ti.sysbios.family.arm.v6m"));
        vo.bind("PeriodType", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType", "ti.sysbios.family.arm.v6m"));
        vo.bind("BasicView", om.findStrict("ti.sysbios.family.arm.v6m.Timer.BasicView", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Timer.BasicView", "ti.sysbios.family.arm.v6m"));
        vo.bind("ModuleView", om.findStrict("ti.sysbios.family.arm.v6m.Timer.ModuleView", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Timer.ModuleView", "ti.sysbios.family.arm.v6m"));
        vo.bind("DeviceView", om.findStrict("ti.sysbios.family.arm.v6m.Timer.DeviceView", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Timer.DeviceView", "ti.sysbios.family.arm.v6m"));
        mcfgs.add("E_invalidTimer");
        mcfgs.add("E_notAvailable");
        mcfgs.add("E_cannotSupport");
        mcfgs.add("anyMask");
        icfgs.add("timerInUse");
        mcfgs.add("startupNeeded");
        icfgs.add("startupNeeded");
        vo.bind("Instance_State", om.findStrict("ti.sysbios.family.arm.v6m.Timer.Instance_State", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Timer.Instance_State", "ti.sysbios.family.arm.v6m"));
        vo.bind("Module_State", om.findStrict("ti.sysbios.family.arm.v6m.Timer.Module_State", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.Timer.Module_State", "ti.sysbios.family.arm.v6m"));
        vo.bind("StartMode_AUTO", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode_AUTO", "ti.sysbios.family.arm.v6m"));
        vo.bind("StartMode_USER", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode_USER", "ti.sysbios.family.arm.v6m"));
        vo.bind("RunMode_CONTINUOUS", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode_CONTINUOUS", "ti.sysbios.family.arm.v6m"));
        vo.bind("RunMode_ONESHOT", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode_ONESHOT", "ti.sysbios.family.arm.v6m"));
        vo.bind("RunMode_DYNAMIC", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode_DYNAMIC", "ti.sysbios.family.arm.v6m"));
        vo.bind("Status_INUSE", om.findStrict("ti.sysbios.interfaces.ITimer.Status_INUSE", "ti.sysbios.family.arm.v6m"));
        vo.bind("Status_FREE", om.findStrict("ti.sysbios.interfaces.ITimer.Status_FREE", "ti.sysbios.family.arm.v6m"));
        vo.bind("PeriodType_MICROSECS", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType_MICROSECS", "ti.sysbios.family.arm.v6m"));
        vo.bind("PeriodType_COUNTS", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType_COUNTS", "ti.sysbios.family.arm.v6m"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sysbios.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v6m")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sysbios.family.arm.v6m.Timer$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sysbios$family$arm$v6m$Timer$$__initObject"));
        }//isCFG
        vo.bind("getNumTimers", om.findStrict("ti.sysbios.family.arm.v6m.Timer.getNumTimers", "ti.sysbios.family.arm.v6m"));
        vo.bind("getStatus", om.findStrict("ti.sysbios.family.arm.v6m.Timer.getStatus", "ti.sysbios.family.arm.v6m"));
        vo.bind("startup", om.findStrict("ti.sysbios.family.arm.v6m.Timer.startup", "ti.sysbios.family.arm.v6m"));
        vo.bind("getHandle", om.findStrict("ti.sysbios.family.arm.v6m.Timer.getHandle", "ti.sysbios.family.arm.v6m"));
        vo.bind("getTickCount", om.findStrict("ti.sysbios.family.arm.v6m.Timer.getTickCount", "ti.sysbios.family.arm.v6m"));
        vo.bind("initDevice", om.findStrict("ti.sysbios.family.arm.v6m.Timer.initDevice", "ti.sysbios.family.arm.v6m"));
        vo.bind("postInit", om.findStrict("ti.sysbios.family.arm.v6m.Timer.postInit", "ti.sysbios.family.arm.v6m"));
        vo.bind("oneShotStub", om.findStrict("ti.sysbios.family.arm.v6m.Timer.oneShotStub", "ti.sysbios.family.arm.v6m"));
        vo.bind("periodicStub", om.findStrict("ti.sysbios.family.arm.v6m.Timer.periodicStub", "ti.sysbios.family.arm.v6m"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v6m_Timer_Handle__label__E", "ti_sysbios_family_arm_v6m_Timer_Module__startupDone__E", "ti_sysbios_family_arm_v6m_Timer_Object__create__E", "ti_sysbios_family_arm_v6m_Timer_Object__delete__E", "ti_sysbios_family_arm_v6m_Timer_Object__destruct__E", "ti_sysbios_family_arm_v6m_Timer_Object__get__E", "ti_sysbios_family_arm_v6m_Timer_Object__first__E", "ti_sysbios_family_arm_v6m_Timer_Object__next__E", "ti_sysbios_family_arm_v6m_Timer_Params__init__E", "ti_sysbios_family_arm_v6m_Timer_getNumTimers__E", "ti_sysbios_family_arm_v6m_Timer_getStatus__E", "ti_sysbios_family_arm_v6m_Timer_startup__E", "ti_sysbios_family_arm_v6m_Timer_getMaxTicks__E", "ti_sysbios_family_arm_v6m_Timer_setNextTick__E", "ti_sysbios_family_arm_v6m_Timer_start__E", "ti_sysbios_family_arm_v6m_Timer_stop__E", "ti_sysbios_family_arm_v6m_Timer_setPeriod__E", "ti_sysbios_family_arm_v6m_Timer_setPeriodMicroSecs__E", "ti_sysbios_family_arm_v6m_Timer_getPeriod__E", "ti_sysbios_family_arm_v6m_Timer_getCount__E", "ti_sysbios_family_arm_v6m_Timer_getFreq__E", "ti_sysbios_family_arm_v6m_Timer_getFunc__E", "ti_sysbios_family_arm_v6m_Timer_setFunc__E", "ti_sysbios_family_arm_v6m_Timer_trigger__E", "ti_sysbios_family_arm_v6m_Timer_getExpiredCounts__E", "ti_sysbios_family_arm_v6m_Timer_getExpiredTicks__E", "ti_sysbios_family_arm_v6m_Timer_getCurrentTick__E", "ti_sysbios_family_arm_v6m_Timer_getHandle__E", "ti_sysbios_family_arm_v6m_Timer_getTickCount__E", "ti_sysbios_family_arm_v6m_Timer_reconfig__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_invalidTimer", "E_notAvailable", "E_cannotSupport"));
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sysbios.family.arm.v6m.Timer.Object", "ti.sysbios.family.arm.v6m"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Timer", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Timer");
    }

    void TimestampProvider$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider", "ti.sysbios.family.arm.v6m");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider.Module", "ti.sysbios.family.arm.v6m");
        vo.init2(po, "ti.sysbios.family.arm.v6m.TimestampProvider", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider$$capsule", "ti.sysbios.family.arm.v6m"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v6m", "ti.sysbios.family.arm.v6m"));
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
        mcfgs.add("configTimer");
        vo.bind("Module_State", om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider.Module_State", "ti.sysbios.family.arm.v6m"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider.Module_State", "ti.sysbios.family.arm.v6m"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sysbios.interfaces");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v6m")).add(vo);
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
        vo.bind("get32", om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider.get32", "ti.sysbios.family.arm.v6m"));
        vo.bind("get64", om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider.get64", "ti.sysbios.family.arm.v6m"));
        vo.bind("getFreq", om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider.getFreq", "ti.sysbios.family.arm.v6m"));
        vo.bind("startTimer", om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider.startTimer", "ti.sysbios.family.arm.v6m"));
        vo.bind("rolloverFunc", om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider.rolloverFunc", "ti.sysbios.family.arm.v6m"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v6m_TimestampProvider_Module__startupDone__E", "ti_sysbios_family_arm_v6m_TimestampProvider_get32__E", "ti_sysbios_family_arm_v6m_TimestampProvider_get64__E", "ti_sysbios_family_arm_v6m_TimestampProvider_getFreq__E", "ti_sysbios_family_arm_v6m_TimestampProvider_startTimer__E", "ti_sysbios_family_arm_v6m_TimestampProvider_rolloverFunc__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TimestampProvider", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TimestampProvider");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sysbios.family.arm.v6m")).findStrict("PARAMS", "ti.sysbios.family.arm.v6m");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sysbios.family.arm.v6m.Hwi", "ti.sysbios.family.arm.v6m")).findStrict("PARAMS", "ti.sysbios.family.arm.v6m");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sysbios.family.arm.v6m.Timer", "ti.sysbios.family.arm.v6m")).findStrict("PARAMS", "ti.sysbios.family.arm.v6m");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v6m.Clobber", "ti.sysbios.family.arm.v6m"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v6m.Hwi", "ti.sysbios.family.arm.v6m"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v6m.IntrinsicsSupport", "ti.sysbios.family.arm.v6m"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v6m.TaskSupport", "ti.sysbios.family.arm.v6m"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v6m.Timer", "ti.sysbios.family.arm.v6m"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v6m.TimestampProvider", "ti.sysbios.family.arm.v6m"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Hwi", "ti.sysbios.family.arm.v6m");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Detailed", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitDetailed", "structName", "DetailedView")}), Global.newArray(new Object[]{"Module", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE"), "viewInitFxn", "viewInitModule", "structName", "ModuleView")}), Global.newArray(new Object[]{"Exception", Global.newObject("type", om.find("xdc.rov.ViewInfo.TREE"), "viewInitFxn", "viewInitException", "structName", "ExcContext")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v6m.Timer", "ti.sysbios.family.arm.v6m");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Device", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitDevice", "structName", "DeviceView")}), Global.newArray(new Object[]{"Module", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE"), "viewInitFxn", "viewInitModule", "structName", "ModuleView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v6m.Clobber")).bless();
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v6m.Hwi")).bless();
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v6m.IntrinsicsSupport")).bless();
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v6m.TaskSupport")).bless();
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v6m.Timer")).bless();
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v6m.TimestampProvider")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sysbios.family.arm.v6m")).add(pkgV);
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
        Clobber$$OBJECTS();
        Hwi$$OBJECTS();
        IntrinsicsSupport$$OBJECTS();
        TaskSupport$$OBJECTS();
        Timer$$OBJECTS();
        TimestampProvider$$OBJECTS();
        Clobber$$CONSTS();
        Hwi$$CONSTS();
        IntrinsicsSupport$$CONSTS();
        TaskSupport$$CONSTS();
        Timer$$CONSTS();
        TimestampProvider$$CONSTS();
        Clobber$$CREATES();
        Hwi$$CREATES();
        IntrinsicsSupport$$CREATES();
        TaskSupport$$CREATES();
        Timer$$CREATES();
        TimestampProvider$$CREATES();
        Clobber$$FUNCTIONS();
        Hwi$$FUNCTIONS();
        IntrinsicsSupport$$FUNCTIONS();
        TaskSupport$$FUNCTIONS();
        Timer$$FUNCTIONS();
        TimestampProvider$$FUNCTIONS();
        Clobber$$SIZES();
        Hwi$$SIZES();
        IntrinsicsSupport$$SIZES();
        TaskSupport$$SIZES();
        Timer$$SIZES();
        TimestampProvider$$SIZES();
        Clobber$$TYPES();
        Hwi$$TYPES();
        IntrinsicsSupport$$TYPES();
        TaskSupport$$TYPES();
        Timer$$TYPES();
        TimestampProvider$$TYPES();
        if (isROV) {
            Clobber$$ROV();
            Hwi$$ROV();
            IntrinsicsSupport$$ROV();
            TaskSupport$$ROV();
            Timer$$ROV();
            TimestampProvider$$ROV();
        }//isROV
        $$SINGLETONS();
        Clobber$$SINGLETONS();
        Hwi$$SINGLETONS();
        IntrinsicsSupport$$SINGLETONS();
        TaskSupport$$SINGLETONS();
        Timer$$SINGLETONS();
        TimestampProvider$$SINGLETONS();
        $$INITIALIZATION();
    }
}
