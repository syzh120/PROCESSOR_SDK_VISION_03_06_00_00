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

public class ti_sdo_ipc_family_tda3xx
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
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.utils");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.interfaces");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.hal");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ipc.notifyDrivers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.family.tda3xx", new Value.Obj("ti.sdo.ipc.family.tda3xx", pkgP));
    }

    void TableInit$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.TableInit.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.tda3xx.TableInit", new Value.Obj("ti.sdo.ipc.family.tda3xx.TableInit", po));
        pkgV.bind("TableInit", vo);
        // decls 
    }

    void NotifySetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup", new Value.Obj("ti.sdo.ipc.family.tda3xx.NotifySetup", po));
        pkgV.bind("NotifySetup", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.Driver", new Proto.Enm("ti.sdo.ipc.family.tda3xx.NotifySetup.Driver"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup$$Connection", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.Connection", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup$$DrvBind", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.DrvBind", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.Module_State", new Proto.Str(spo, false));
    }

    void NotifyDriverMbx$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx", new Value.Obj("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx", po));
        pkgV.bind("NotifyDriverMbx", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$MailboxView", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.MailboxView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$ModuleView", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.ModuleView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Object", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance_State", "ti.sdo.ipc.family.tda3xx"));
        }//isROV
    }

    void InterruptArp32$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32", new Value.Obj("ti.sdo.ipc.family.tda3xx.InterruptArp32", po));
        pkgV.bind("InterruptArp32", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.tda3xx"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32$$FxnTable", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.FxnTable", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.Module_State", new Proto.Str(spo, false));
    }

    void InterruptDsp$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp", new Value.Obj("ti.sdo.ipc.family.tda3xx.InterruptDsp", po));
        pkgV.bind("InterruptDsp", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.tda3xx"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp$$InterruptDataView", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.InterruptDataView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp$$FxnTable", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.FxnTable", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.Module_State", new Proto.Str(spo, false));
    }

    void InterruptIpu$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu", new Value.Obj("ti.sdo.ipc.family.tda3xx.InterruptIpu", po));
        pkgV.bind("InterruptIpu", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.tda3xx"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu$$FxnTable", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.FxnTable", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.Module_State", new Proto.Str(spo, false));
    }

    void TableInit$$CONSTS()
    {
        // module TableInit
    }

    void NotifySetup$$CONSTS()
    {
        // module NotifySetup
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.Driver_SHAREDMEMORY", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Driver", "ti.sdo.ipc.family.tda3xx"), "ti.sdo.ipc.family.tda3xx.NotifySetup.Driver_SHAREDMEMORY", xdc.services.intern.xsr.Enum.intValue(0x01L)+0));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.Driver_MAILBOX", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Driver", "ti.sdo.ipc.family.tda3xx"), "ti.sdo.ipc.family.tda3xx.NotifySetup.Driver_MAILBOX", xdc.services.intern.xsr.Enum.intValue(0x02L)+0));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.NUM_CORES", 5L);
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.NUM_EVES", 1L);
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.NUM_EVE_MBX", 2L);
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.NUM_SYS_MBX", 1L);
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.attach", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.sharedMemReq", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.numIntLines", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.plugHwi", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_plugHwi__E", "xdc_Void(*)(xdc_UInt16,xdc_Int,xdc_Void(*)(xdc_UInt16))", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.unplugHwi", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_unplugHwi__E", "xdc_Void(*)(xdc_UInt16,xdc_Int)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.interruptTable", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_interruptTable__E", "xdc_UInt16(*)(xdc_Int)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.driverType", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_driverType__I", "ti_sdo_ipc_family_tda3xx_NotifySetup_Driver(*)(xdc_UInt16)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.Shm_attach", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_Shm_attach__I", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.Shm_sharedMemReq", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_Shm_sharedMemReq__I", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.Mbx_attach", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_Mbx_attach__I", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.Mbx_sharedMemReq", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_Mbx_sharedMemReq__I", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.dispatchIsr", new Extern("ti_sdo_ipc_family_tda3xx_NotifySetup_dispatchIsr__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void NotifyDriverMbx$$CONSTS()
    {
        // module NotifyDriverMbx
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.NUM_CORES", 5L);
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.NUM_EVES", 1L);
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.NUM_EVE_MBX", 2L);
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.NUM_SYS_MBX", 1L);
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.isr", new Extern("ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_isr__I", "xdc_Void(*)(xdc_UInt16)", true, false));
    }

    void InterruptArp32$$CONSTS()
    {
        // module InterruptArp32
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.NUM_CORES", 5L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.NUM_EVES", 1L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.NUM_EVE_MBX", 2L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.NUM_SYS_MBX", 1L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.intEnable", new Extern("ti_sdo_ipc_family_tda3xx_InterruptArp32_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.intDisable", new Extern("ti_sdo_ipc_family_tda3xx_InterruptArp32_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.intRegister", new Extern("ti_sdo_ipc_family_tda3xx_InterruptArp32_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.intUnregister", new Extern("ti_sdo_ipc_family_tda3xx_InterruptArp32_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.intSend", new Extern("ti_sdo_ipc_family_tda3xx_InterruptArp32_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.intPost", new Extern("ti_sdo_ipc_family_tda3xx_InterruptArp32_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.intClear", new Extern("ti_sdo_ipc_family_tda3xx_InterruptArp32_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32.intShmStub", new Extern("ti_sdo_ipc_family_tda3xx_InterruptArp32_intShmStub__I", "xdc_Void(*)(xdc_UInt16)", true, false));
    }

    void InterruptDsp$$CONSTS()
    {
        // module InterruptDsp
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.NUM_CORES", 5L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.NUM_EVES", 1L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.NUM_EVE_MBX", 2L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.NUM_SYS_MBX", 1L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.intEnable", new Extern("ti_sdo_ipc_family_tda3xx_InterruptDsp_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.intDisable", new Extern("ti_sdo_ipc_family_tda3xx_InterruptDsp_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.intRegister", new Extern("ti_sdo_ipc_family_tda3xx_InterruptDsp_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.intUnregister", new Extern("ti_sdo_ipc_family_tda3xx_InterruptDsp_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.intSend", new Extern("ti_sdo_ipc_family_tda3xx_InterruptDsp_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.intPost", new Extern("ti_sdo_ipc_family_tda3xx_InterruptDsp_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.intClear", new Extern("ti_sdo_ipc_family_tda3xx_InterruptDsp_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp.intShmStub", new Extern("ti_sdo_ipc_family_tda3xx_InterruptDsp_intShmStub__I", "xdc_Void(*)(xdc_UInt16)", true, false));
    }

    void InterruptIpu$$CONSTS()
    {
        // module InterruptIpu
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.NUM_CORES", 5L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.NUM_EVES", 1L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.NUM_Ipu_CORES", 2L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.NUM_EVE_MBX", Global.eval("1 * 2"));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.NUM_SYS_MBX", 1L);
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.intEnable", new Extern("ti_sdo_ipc_family_tda3xx_InterruptIpu_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.intDisable", new Extern("ti_sdo_ipc_family_tda3xx_InterruptIpu_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.intRegister", new Extern("ti_sdo_ipc_family_tda3xx_InterruptIpu_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.intUnregister", new Extern("ti_sdo_ipc_family_tda3xx_InterruptIpu_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.intSend", new Extern("ti_sdo_ipc_family_tda3xx_InterruptIpu_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.intPost", new Extern("ti_sdo_ipc_family_tda3xx_InterruptIpu_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.intClear", new Extern("ti_sdo_ipc_family_tda3xx_InterruptIpu_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.intShmDucatiStub", new Extern("ti_sdo_ipc_family_tda3xx_InterruptIpu_intShmDucatiStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu.intShmMbxStub", new Extern("ti_sdo_ipc_family_tda3xx_InterruptIpu_intShmMbxStub__I", "xdc_Void(*)(xdc_UInt16)", true, false));
    }

    void TableInit$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NotifySetup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NotifyDriverMbx$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$family$tda3xx$NotifyDriverMbx$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.create() called before xdc.useModule('ti.sdo.ipc.family.tda3xx.NotifyDriverMbx')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module", "ti.sdo.ipc.family.tda3xx"), om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance", "ti.sdo.ipc.family.tda3xx"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Params", "ti.sdo.ipc.family.tda3xx"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$family$tda3xx$NotifyDriverMbx$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.family.tda3xx']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module", "ti.sdo.ipc.family.tda3xx"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Object", "ti.sdo.ipc.family.tda3xx"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Params", "ti.sdo.ipc.family.tda3xx"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$family$tda3xx$NotifyDriverMbx$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void InterruptArp32$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void InterruptDsp$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void InterruptIpu$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TableInit$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn TableInit.initProcId
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.tda3xx.TableInit$$initProcId", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.tda3xx.TableInit.Module", "ti.sdo.ipc.family.tda3xx"), null, 1, 1, false));
                fxn.addArg(0, "InterruptCore", $$T_Obj, $$UNDEF);
        // fxn TableInit.generateTable
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.tda3xx.TableInit$$generateTable", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.tda3xx.TableInit.Module", "ti.sdo.ipc.family.tda3xx"), null, 1, 1, false));
                fxn.addArg(0, "InterruptCore", $$T_Obj, $$UNDEF);
    }

    void NotifySetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifyDriverMbx$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void InterruptArp32$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void InterruptDsp$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void InterruptIpu$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TableInit$$SIZES()
    {
    }

    void NotifySetup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Connection", "ti.sdo.ipc.family.tda3xx");
        sizes.clear();
        sizes.add(Global.newArray("driver", "Nti.sdo.ipc.family.tda3xx.NotifySetup.Driver;;0x01;0x02"));
        sizes.add(Global.newArray("procName", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifySetup.Connection']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifySetup.Connection']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifySetup.Connection'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.DrvBind", "ti.sdo.ipc.family.tda3xx");
        sizes.clear();
        sizes.add(Global.newArray("driver", "Nti.sdo.ipc.family.tda3xx.NotifySetup.Driver;;0x01;0x02"));
        sizes.add(Global.newArray("procId", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifySetup.DrvBind']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifySetup.DrvBind']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifySetup.DrvBind'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Module_State", "ti.sdo.ipc.family.tda3xx");
        sizes.clear();
        sizes.add(Global.newArray("numPlugged", "UPtr"));
        sizes.add(Global.newArray("connAry", "Sxdc.runtime.Types;Vec"));
        sizes.add(Global.newArray("interruptTable", "A5;UInt16"));
        sizes.add(Global.newArray("isrDispatchTable", "A5;UFxn"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifySetup.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifySetup.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifySetup.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NotifyDriverMbx$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance_State", "ti.sdo.ipc.family.tda3xx");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("evtRegMask", "UInt32"));
        sizes.add(Global.newArray("notifyHandle", "UPtr"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        sizes.add(Global.newArray("remoteVirtId", "UInt16"));
        sizes.add(Global.newArray("cpuIntrNum", "TInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module_State", "ti.sdo.ipc.family.tda3xx");
        sizes.clear();
        sizes.add(Global.newArray("drvHandles", "A5;UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void InterruptArp32$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.FxnTable", "ti.sdo.ipc.family.tda3xx");
        sizes.clear();
        sizes.add(Global.newArray("func", "UFxn"));
        sizes.add(Global.newArray("arg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptArp32.FxnTable']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptArp32.FxnTable']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptArp32.FxnTable'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.Module_State", "ti.sdo.ipc.family.tda3xx");
        sizes.clear();
        sizes.add(Global.newArray("fxnTable", "A5;Sti.sdo.ipc.family.tda3xx.InterruptArp32;FxnTable"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptArp32.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptArp32.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptArp32.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void InterruptDsp$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.FxnTable", "ti.sdo.ipc.family.tda3xx");
        sizes.clear();
        sizes.add(Global.newArray("func", "UFxn"));
        sizes.add(Global.newArray("arg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptDsp.FxnTable']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptDsp.FxnTable']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptDsp.FxnTable'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.Module_State", "ti.sdo.ipc.family.tda3xx");
        sizes.clear();
        sizes.add(Global.newArray("fxnTable", "A5;Sti.sdo.ipc.family.tda3xx.InterruptDsp;FxnTable"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptDsp.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptDsp.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptDsp.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void InterruptIpu$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.FxnTable", "ti.sdo.ipc.family.tda3xx");
        sizes.clear();
        sizes.add(Global.newArray("func", "UFxn"));
        sizes.add(Global.newArray("arg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptIpu.FxnTable']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptIpu.FxnTable']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptIpu.FxnTable'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.Module_State", "ti.sdo.ipc.family.tda3xx");
        sizes.clear();
        sizes.add(Global.newArray("fxnTable", "A5;Sti.sdo.ipc.family.tda3xx.InterruptIpu;FxnTable"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptIpu.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptIpu.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.tda3xx.InterruptIpu.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TableInit$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/tda3xx/TableInit.xs");
        om.bind("ti.sdo.ipc.family.tda3xx.TableInit$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.TableInit.Module", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.TableInit.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.TableInit$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.TableInit$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.TableInit$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("initProcId", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.tda3xx.TableInit$$initProcId", "ti.sdo.ipc.family.tda3xx"), Global.get(cap, "initProcId"));
                po.addFxn("generateTable", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.tda3xx.TableInit$$generateTable", "ti.sdo.ipc.family.tda3xx"), Global.get(cap, "generateTable"));
    }

    void NotifySetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/tda3xx/NotifySetup.xs");
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Module", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifySetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.tda3xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NUM_CORES", Proto.Elm.newCNum("(xdc_UInt8)"), 5L, "rh");
                po.addFld("NUM_EVES", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("NUM_EVE_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
                po.addFld("NUM_SYS_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
        if (isCFG) {
            po.addFld("connections", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Connection", "ti.sdo.ipc.family.tda3xx"), true), $$DEFAULT, "wh");
            po.addFld("dspIntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 4L, "w");
            po.addFld("eveIntVectId_INTC0", Proto.Elm.newCNum("(xdc_UInt)"), 4L, "w");
            po.addFld("eveIntVectId_INTC1", Proto.Elm.newCNum("(xdc_UInt)"), 8L, "w");
            po.addFld("mailboxTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(Global.eval("5 * 5"))), $$DEFAULT, "w");
            po.addFld("mailboxBaseAddr", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(Global.eval("2 + 1"))), $$DEFAULT, "w");
            po.addFld("eve1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dsp1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dsp2ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("ipu1_0ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("ipu1_1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("procIdTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
            po.addFld("A_internal", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.family.tda3xx"), Global.newObject("msg", "A_internal: internal implementation error"), "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // typedef NotifySetup.DriverIsr
        om.bind("ti.sdo.ipc.family.tda3xx.NotifySetup.DriverIsr", new Proto.Adr("xdc_Void(*)(xdc_UInt16)", "PFv"));
        // struct NotifySetup.Connection
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup$$Connection", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifySetup.Connection", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("driver", (Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Driver", "ti.sdo.ipc.family.tda3xx"), $$UNDEF, "w");
                po.addFld("procName", $$T_Str, $$UNDEF, "w");
        // struct NotifySetup.DrvBind
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup$$DrvBind", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifySetup.DrvBind", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("driver", (Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Driver", "ti.sdo.ipc.family.tda3xx"), $$UNDEF, "w");
                po.addFld("procId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
        // struct NotifySetup.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup$$Module_State", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifySetup.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("numPlugged", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt16)"), false), $$DEFAULT, "w");
                po.addFld("connAry", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.DrvBind", "ti.sdo.ipc.family.tda3xx"), true), $$DEFAULT, "w");
                po.addFld("interruptTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt16)"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
                po.addFld("isrDispatchTable", new Proto.Arr(new Proto.Adr("xdc_Void(*)(xdc_UInt16)", "PFv"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
    }

    void NotifyDriverMbx$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/tda3xx/NotifyDriverMbx.xs");
        om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver.Module", "ti.sdo.ipc.family.tda3xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NUM_CORES", Proto.Elm.newCNum("(xdc_UInt8)"), 5L, "rh");
                po.addFld("NUM_EVES", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("NUM_EVE_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
                po.addFld("NUM_SYS_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.family.tda3xx"), $$UNDEF, "wh");
            po.addFld("A_notSupported", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.family.tda3xx"), Global.newObject("msg", "A_notSupported: [enable/disable]Event not supported"), "w");
            po.addFld("mailboxTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(Global.eval("5 * 5"))), $$DEFAULT, "w");
            po.addFld("mailboxBaseAddr", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(Global.eval("2 + 1"))), $$DEFAULT, "w");
            po.addFld("procIdTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
            po.addFld("eve1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dsp1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dsp2ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("ipu1_0ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("ipu1_1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$create", "ti.sdo.ipc.family.tda3xx"), Global.get("ti$sdo$ipc$family$tda3xx$NotifyDriverMbx$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$construct", "ti.sdo.ipc.family.tda3xx"), Global.get("ti$sdo$ipc$family$tda3xx$NotifyDriverMbx$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver.Instance", "ti.sdo.ipc.family.tda3xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NUM_CORES", Proto.Elm.newCNum("(xdc_UInt8)"), 5L, "rh");
                po.addFld("NUM_EVES", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("NUM_EVE_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
                po.addFld("NUM_SYS_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
        if (isCFG) {
            po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
            po.addFld("intVectorId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~1"), "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.family.tda3xx"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Params", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Params", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver$$Params", "ti.sdo.ipc.family.tda3xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NUM_CORES", Proto.Elm.newCNum("(xdc_UInt8)"), 5L, "rh");
                po.addFld("NUM_EVES", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("NUM_EVE_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
                po.addFld("NUM_SYS_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
        if (isCFG) {
            po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
            po.addFld("intVectorId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~1"), "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.family.tda3xx"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Object", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Object", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance", "ti.sdo.ipc.family.tda3xx"));
        // struct NotifyDriverMbx.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$BasicView", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteProc", $$T_Str, $$UNDEF, "w");
        // struct NotifyDriverMbx.MailboxView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$MailboxView", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.MailboxView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("direction", $$T_Str, $$UNDEF, "w");
                po.addFld("mailboxAddr", $$T_Str, $$UNDEF, "w");
                po.addFld("subMbxId", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("msgCount", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("mbxInterrupt", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
        // struct NotifyDriverMbx.ModuleView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$ModuleView", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("drvHandles", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Handle", "ti.sdo.ipc.family.tda3xx"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
        // struct NotifyDriverMbx.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Instance_State", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("evtRegMask", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("notifyHandle", (Proto)om.findStrict("ti.sdo.ipc.Notify.Handle", "ti.sdo.ipc.family.tda3xx"), $$UNDEF, "w");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("remoteVirtId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("cpuIntrNum", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
        // struct NotifyDriverMbx.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Module_State", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("drvHandles", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Handle", "ti.sdo.ipc.family.tda3xx"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
    }

    void InterruptArp32$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/tda3xx/InterruptArp32.xs");
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.Module", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.InterruptArp32.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.tda3xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NUM_CORES", Proto.Elm.newCNum("(xdc_UInt8)"), 5L, "rh");
                po.addFld("NUM_EVES", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("NUM_EVE_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
                po.addFld("NUM_SYS_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
        if (isCFG) {
            po.addFld("mailboxBaseAddr", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(Global.eval("2 + 1"))), $$DEFAULT, "w");
            po.addFld("mailboxTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(Global.eval("5 * 5"))), $$DEFAULT, "w");
            po.addFld("eveInterruptTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
            po.addFld("procIdTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
            po.addFld("eve1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dsp1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dsp2ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("ipu1_0ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("ipu1_1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptArp32$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct InterruptArp32.FxnTable
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32$$FxnTable", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.InterruptArp32.FxnTable", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("func", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct InterruptArp32.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32$$Module_State", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.InterruptArp32.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fxnTable", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.FxnTable", "ti.sdo.ipc.family.tda3xx"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
    }

    void InterruptDsp$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/tda3xx/InterruptDsp.xs");
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.Module", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.InterruptDsp.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.tda3xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NUM_CORES", Proto.Elm.newCNum("(xdc_UInt8)"), 5L, "rh");
                po.addFld("NUM_EVES", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("NUM_EVE_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
                po.addFld("NUM_SYS_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
        if (isCFG) {
            po.addFld("mailboxBaseAddr", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(Global.eval("2 + 1"))), $$DEFAULT, "w");
            po.addFld("mailboxTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(Global.eval("5 * 5"))), $$DEFAULT, "w");
            po.addFld("procIdTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
            po.addFld("eve1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dsp1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dsp2ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("ipu1_0ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("ipu1_1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptDsp$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct InterruptDsp.InterruptDataView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp$$InterruptDataView", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.InterruptDsp.InterruptDataView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteProcName", $$T_Str, $$UNDEF, "w");
                po.addFld("registered", $$T_Bool, $$UNDEF, "w");
                po.addFld("enabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("intPending", $$T_Bool, $$UNDEF, "w");
                po.addFld("payload", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct InterruptDsp.FxnTable
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp$$FxnTable", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.InterruptDsp.FxnTable", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("func", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct InterruptDsp.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp$$Module_State", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.InterruptDsp.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fxnTable", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.FxnTable", "ti.sdo.ipc.family.tda3xx"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
    }

    void InterruptIpu$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/tda3xx/InterruptIpu.xs");
        om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.Module", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.InterruptIpu.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.tda3xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NUM_CORES", Proto.Elm.newCNum("(xdc_UInt8)"), 5L, "rh");
                po.addFld("NUM_EVES", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
                po.addFld("NUM_Ipu_CORES", Proto.Elm.newCNum("(xdc_UInt8)"), 2L, "rh");
                po.addFld("NUM_EVE_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), Global.eval("1 * 2"), "rh");
                po.addFld("NUM_SYS_MBX", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "rh");
        if (isCFG) {
            po.addFld("mailboxBaseAddr", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(Global.eval("1 * 2 + 1"))), $$DEFAULT, "w");
            po.addFld("mailboxTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(Global.eval("5 * 5"))), $$DEFAULT, "w");
            po.addFld("ducatiCtrlBaseAddr", Proto.Elm.newCNum("(xdc_UInt32)"), 0x40001000L, "w");
            po.addFld("procIdTable", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
            po.addFld("eve1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dsp1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dsp2ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("ipu1_0ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("ipu1_1ProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.tda3xx.InterruptIpu$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct InterruptIpu.FxnTable
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu$$FxnTable", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.InterruptIpu.FxnTable", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("func", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct InterruptIpu.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu$$Module_State", "ti.sdo.ipc.family.tda3xx");
        po.init("ti.sdo.ipc.family.tda3xx.InterruptIpu.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fxnTable", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.FxnTable", "ti.sdo.ipc.family.tda3xx"), false, xdc.services.intern.xsr.Enum.intValue(5L)), $$DEFAULT, "w");
    }

    void TableInit$$ROV()
    {
    }

    void NotifySetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup", "ti.sdo.ipc.family.tda3xx");
        vo.bind("Connection$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.tda3xx.NotifySetup.Connection", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup$$Connection", "ti.sdo.ipc.family.tda3xx");
        vo.bind("DrvBind$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.tda3xx.NotifySetup.DrvBind", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup$$DrvBind", "ti.sdo.ipc.family.tda3xx");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.tda3xx.NotifySetup.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup$$Module_State", "ti.sdo.ipc.family.tda3xx");
        po.bind("numPlugged$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_UInt16", "isScalar", true));
    }

    void NotifyDriverMbx$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx", "ti.sdo.ipc.family.tda3xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Instance_State", "ti.sdo.ipc.family.tda3xx");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Instance_State", "ti.sdo.ipc.family.tda3xx");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$Module_State", "ti.sdo.ipc.family.tda3xx");
    }

    void InterruptArp32$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32", "ti.sdo.ipc.family.tda3xx");
        vo.bind("FxnTable$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.tda3xx.InterruptArp32.FxnTable", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32$$FxnTable", "ti.sdo.ipc.family.tda3xx");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.tda3xx.InterruptArp32.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32$$Module_State", "ti.sdo.ipc.family.tda3xx");
    }

    void InterruptDsp$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp", "ti.sdo.ipc.family.tda3xx");
        vo.bind("FxnTable$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.tda3xx.InterruptDsp.FxnTable", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp$$FxnTable", "ti.sdo.ipc.family.tda3xx");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.tda3xx.InterruptDsp.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp$$Module_State", "ti.sdo.ipc.family.tda3xx");
    }

    void InterruptIpu$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu", "ti.sdo.ipc.family.tda3xx");
        vo.bind("FxnTable$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.tda3xx.InterruptIpu.FxnTable", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu$$FxnTable", "ti.sdo.ipc.family.tda3xx");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.tda3xx.InterruptIpu.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu$$Module_State", "ti.sdo.ipc.family.tda3xx");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.family.tda3xx.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.family.tda3xx"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/tda3xx/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.family.tda3xx"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.family.tda3xx"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.family.tda3xx"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.family.tda3xx"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.family.tda3xx"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.family.tda3xx"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.family.tda3xx", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.family.tda3xx");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.family.tda3xx.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ipc", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.family.tda3xx'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.family.tda3xx$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.family.tda3xx$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.family.tda3xx$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void TableInit$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.TableInit", "ti.sdo.ipc.family.tda3xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.TableInit.Module", "ti.sdo.ipc.family.tda3xx");
        vo.init2(po, "ti.sdo.ipc.family.tda3xx.TableInit", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.tda3xx.TableInit$$capsule", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.tda3xx", "ti.sdo.ipc.family.tda3xx"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.tda3xx")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.family.tda3xx.TableInit$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("TableInit", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TableInit");
    }

    void NotifySetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup", "ti.sdo.ipc.family.tda3xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Module", "ti.sdo.ipc.family.tda3xx");
        vo.init2(po, "ti.sdo.ipc.family.tda3xx.NotifySetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup$$capsule", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.tda3xx", "ti.sdo.ipc.family.tda3xx"));
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
        vo.bind("DriverIsr", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.DriverIsr", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Driver", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Driver", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Connection", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Connection", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Connection", "ti.sdo.ipc.family.tda3xx"));
        mcfgs.add("dspIntVectId");
        icfgs.add("dspIntVectId");
        mcfgs.add("eveIntVectId_INTC0");
        icfgs.add("eveIntVectId_INTC0");
        mcfgs.add("eveIntVectId_INTC1");
        icfgs.add("eveIntVectId_INTC1");
        mcfgs.add("mailboxTable");
        icfgs.add("mailboxTable");
        mcfgs.add("mailboxBaseAddr");
        icfgs.add("mailboxBaseAddr");
        mcfgs.add("eve1ProcId");
        icfgs.add("eve1ProcId");
        mcfgs.add("dsp1ProcId");
        icfgs.add("dsp1ProcId");
        mcfgs.add("dsp2ProcId");
        icfgs.add("dsp2ProcId");
        mcfgs.add("ipu1_0ProcId");
        icfgs.add("ipu1_0ProcId");
        mcfgs.add("ipu1_1ProcId");
        icfgs.add("ipu1_1ProcId");
        mcfgs.add("procIdTable");
        icfgs.add("procIdTable");
        vo.bind("DrvBind", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.DrvBind", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.DrvBind", "ti.sdo.ipc.family.tda3xx"));
        mcfgs.add("A_internal");
        icfgs.add("A_internal");
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Module_State", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Module_State", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Driver_SHAREDMEMORY", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Driver_SHAREDMEMORY", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Driver_MAILBOX", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Driver_MAILBOX", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.tda3xx")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.attach", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.sharedMemReq", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.numIntLines", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("plugHwi", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.plugHwi", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("unplugHwi", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.unplugHwi", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("interruptTable", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.interruptTable", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("driverType", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.driverType", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Shm_attach", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Shm_attach", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Shm_sharedMemReq", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Shm_sharedMemReq", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Mbx_attach", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Mbx_attach", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Mbx_sharedMemReq", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.Mbx_sharedMemReq", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("dispatchIsr", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup.dispatchIsr", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_tda3xx_NotifySetup_Module__startupDone__E", "ti_sdo_ipc_family_tda3xx_NotifySetup_attach__E", "ti_sdo_ipc_family_tda3xx_NotifySetup_sharedMemReq__E", "ti_sdo_ipc_family_tda3xx_NotifySetup_numIntLines__E", "ti_sdo_ipc_family_tda3xx_NotifySetup_plugHwi__E", "ti_sdo_ipc_family_tda3xx_NotifySetup_unplugHwi__E", "ti_sdo_ipc_family_tda3xx_NotifySetup_interruptTable__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_internal"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./NotifySetup.xdt");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "plugHwi", "entry", "0x%x, %d, %p", "exit", ""));
        loggables.add(Global.newObject("name", "unplugHwi", "entry", "0x%x, %d", "exit", ""));
        loggables.add(Global.newObject("name", "interruptTable", "entry", "%d", "exit", "0x%x"));
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./NotifySetup.xdt");
        pkgV.bind("NotifySetup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifySetup");
    }

    void NotifyDriverMbx$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx", "ti.sdo.ipc.family.tda3xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module", "ti.sdo.ipc.family.tda3xx");
        vo.init2(po, "ti.sdo.ipc.family.tda3xx.NotifyDriverMbx", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$capsule", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Params", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Params", "ti.sdo.ipc.family.tda3xx")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Handle", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.tda3xx", "ti.sdo.ipc.family.tda3xx"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.BasicView", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.BasicView", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("MailboxView", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.MailboxView", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.MailboxView", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("ModuleView", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.ModuleView", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.ModuleView", "ti.sdo.ipc.family.tda3xx"));
        mcfgs.add("A_notSupported");
        mcfgs.add("mailboxTable");
        icfgs.add("mailboxTable");
        mcfgs.add("mailboxBaseAddr");
        icfgs.add("mailboxBaseAddr");
        mcfgs.add("procIdTable");
        icfgs.add("procIdTable");
        mcfgs.add("eve1ProcId");
        icfgs.add("eve1ProcId");
        mcfgs.add("dsp1ProcId");
        icfgs.add("dsp1ProcId");
        mcfgs.add("dsp2ProcId");
        icfgs.add("dsp2ProcId");
        mcfgs.add("ipu1_0ProcId");
        icfgs.add("ipu1_0ProcId");
        mcfgs.add("ipu1_1ProcId");
        icfgs.add("ipu1_1ProcId");
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance_State", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Instance_State", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module_State", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Module_State", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.tda3xx")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$family$tda3xx$NotifyDriverMbx$$__initObject"));
        }//isCFG
        vo.bind("isr", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.isr", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_Handle__label__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_Module__startupDone__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_Object__create__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_Object__delete__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_Object__destruct__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_Object__get__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_Object__first__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_Object__next__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_Params__init__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_registerEvent__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_unregisterEvent__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_sendEvent__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_disable__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_enable__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_disableEvent__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_enableEvent__E", "ti_sdo_ipc_family_tda3xx_NotifyDriverMbx_setNotifyHandle__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_notSupported"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx.Object", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NotifyDriverMbx", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifyDriverMbx");
    }

    void InterruptArp32$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32", "ti.sdo.ipc.family.tda3xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.Module", "ti.sdo.ipc.family.tda3xx");
        vo.init2(po, "ti.sdo.ipc.family.tda3xx.InterruptArp32", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32$$capsule", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.tda3xx", "ti.sdo.ipc.family.tda3xx"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.tda3xx"));
        mcfgs.add("mailboxBaseAddr");
        mcfgs.add("mailboxTable");
        icfgs.add("mailboxTable");
        mcfgs.add("eveInterruptTable");
        icfgs.add("eveInterruptTable");
        mcfgs.add("procIdTable");
        icfgs.add("procIdTable");
        mcfgs.add("eve1ProcId");
        icfgs.add("eve1ProcId");
        mcfgs.add("dsp1ProcId");
        icfgs.add("dsp1ProcId");
        mcfgs.add("dsp2ProcId");
        icfgs.add("dsp2ProcId");
        mcfgs.add("ipu1_0ProcId");
        icfgs.add("ipu1_0ProcId");
        mcfgs.add("ipu1_1ProcId");
        icfgs.add("ipu1_1ProcId");
        vo.bind("FxnTable", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.FxnTable", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.FxnTable", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.Module_State", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.Module_State", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.tda3xx")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.intEnable", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.intDisable", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.intRegister", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.intUnregister", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.intSend", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.intPost", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.intClear", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intShmStub", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32.intShmStub", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_tda3xx_InterruptArp32_Module__startupDone__E", "ti_sdo_ipc_family_tda3xx_InterruptArp32_intEnable__E", "ti_sdo_ipc_family_tda3xx_InterruptArp32_intDisable__E", "ti_sdo_ipc_family_tda3xx_InterruptArp32_intRegister__E", "ti_sdo_ipc_family_tda3xx_InterruptArp32_intUnregister__E", "ti_sdo_ipc_family_tda3xx_InterruptArp32_intSend__E", "ti_sdo_ipc_family_tda3xx_InterruptArp32_intPost__E", "ti_sdo_ipc_family_tda3xx_InterruptArp32_intClear__E"));
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

    void InterruptDsp$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp", "ti.sdo.ipc.family.tda3xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.Module", "ti.sdo.ipc.family.tda3xx");
        vo.init2(po, "ti.sdo.ipc.family.tda3xx.InterruptDsp", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp$$capsule", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.tda3xx", "ti.sdo.ipc.family.tda3xx"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("InterruptDataView", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.InterruptDataView", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.InterruptDataView", "ti.sdo.ipc.family.tda3xx"));
        mcfgs.add("mailboxBaseAddr");
        mcfgs.add("mailboxTable");
        icfgs.add("mailboxTable");
        mcfgs.add("procIdTable");
        icfgs.add("procIdTable");
        mcfgs.add("eve1ProcId");
        icfgs.add("eve1ProcId");
        mcfgs.add("dsp1ProcId");
        icfgs.add("dsp1ProcId");
        mcfgs.add("dsp2ProcId");
        icfgs.add("dsp2ProcId");
        mcfgs.add("ipu1_0ProcId");
        icfgs.add("ipu1_0ProcId");
        mcfgs.add("ipu1_1ProcId");
        icfgs.add("ipu1_1ProcId");
        vo.bind("FxnTable", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.FxnTable", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.FxnTable", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.Module_State", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.Module_State", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.tda3xx")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.intEnable", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.intDisable", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.intRegister", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.intUnregister", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.intSend", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.intPost", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.intClear", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intShmStub", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp.intShmStub", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_tda3xx_InterruptDsp_Module__startupDone__E", "ti_sdo_ipc_family_tda3xx_InterruptDsp_intEnable__E", "ti_sdo_ipc_family_tda3xx_InterruptDsp_intDisable__E", "ti_sdo_ipc_family_tda3xx_InterruptDsp_intRegister__E", "ti_sdo_ipc_family_tda3xx_InterruptDsp_intUnregister__E", "ti_sdo_ipc_family_tda3xx_InterruptDsp_intSend__E", "ti_sdo_ipc_family_tda3xx_InterruptDsp_intPost__E", "ti_sdo_ipc_family_tda3xx_InterruptDsp_intClear__E"));
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

    void InterruptIpu$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu", "ti.sdo.ipc.family.tda3xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.Module", "ti.sdo.ipc.family.tda3xx");
        vo.init2(po, "ti.sdo.ipc.family.tda3xx.InterruptIpu", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu$$capsule", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.tda3xx", "ti.sdo.ipc.family.tda3xx"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.tda3xx"));
        mcfgs.add("mailboxBaseAddr");
        mcfgs.add("mailboxTable");
        mcfgs.add("ducatiCtrlBaseAddr");
        mcfgs.add("procIdTable");
        mcfgs.add("eve1ProcId");
        icfgs.add("eve1ProcId");
        mcfgs.add("dsp1ProcId");
        icfgs.add("dsp1ProcId");
        mcfgs.add("dsp2ProcId");
        icfgs.add("dsp2ProcId");
        mcfgs.add("ipu1_0ProcId");
        icfgs.add("ipu1_0ProcId");
        mcfgs.add("ipu1_1ProcId");
        icfgs.add("ipu1_1ProcId");
        vo.bind("FxnTable", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.FxnTable", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.FxnTable", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.Module_State", "ti.sdo.ipc.family.tda3xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.Module_State", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.tda3xx")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.intEnable", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.intDisable", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.intRegister", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.intUnregister", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.intSend", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.intPost", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.intClear", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intShmDucatiStub", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.intShmDucatiStub", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("intShmMbxStub", om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu.intShmMbxStub", "ti.sdo.ipc.family.tda3xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_tda3xx_InterruptIpu_Module__startupDone__E", "ti_sdo_ipc_family_tda3xx_InterruptIpu_intEnable__E", "ti_sdo_ipc_family_tda3xx_InterruptIpu_intDisable__E", "ti_sdo_ipc_family_tda3xx_InterruptIpu_intRegister__E", "ti_sdo_ipc_family_tda3xx_InterruptIpu_intUnregister__E", "ti_sdo_ipc_family_tda3xx_InterruptIpu_intSend__E", "ti_sdo_ipc_family_tda3xx_InterruptIpu_intPost__E", "ti_sdo_ipc_family_tda3xx_InterruptIpu_intClear__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("InterruptIpu", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("InterruptIpu");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sdo.ipc.family.tda3xx")).findStrict("PARAMS", "ti.sdo.ipc.family.tda3xx");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx", "ti.sdo.ipc.family.tda3xx")).findStrict("PARAMS", "ti.sdo.ipc.family.tda3xx");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.tda3xx.TableInit", "ti.sdo.ipc.family.tda3xx"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifySetup", "ti.sdo.ipc.family.tda3xx"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx", "ti.sdo.ipc.family.tda3xx"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptArp32", "ti.sdo.ipc.family.tda3xx"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptDsp", "ti.sdo.ipc.family.tda3xx"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.tda3xx.InterruptIpu", "ti.sdo.ipc.family.tda3xx"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx", "ti.sdo.ipc.family.tda3xx");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Mailbox", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE_DATA"), "viewInitFxn", "viewInitMailbox", "structName", "MailboxView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.family.tda3xx.TableInit")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.tda3xx.NotifySetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.tda3xx.NotifyDriverMbx")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.tda3xx.InterruptArp32")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.tda3xx.InterruptDsp")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.tda3xx.InterruptIpu")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.family.tda3xx")).add(pkgV);
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
        TableInit$$OBJECTS();
        NotifySetup$$OBJECTS();
        NotifyDriverMbx$$OBJECTS();
        InterruptArp32$$OBJECTS();
        InterruptDsp$$OBJECTS();
        InterruptIpu$$OBJECTS();
        TableInit$$CONSTS();
        NotifySetup$$CONSTS();
        NotifyDriverMbx$$CONSTS();
        InterruptArp32$$CONSTS();
        InterruptDsp$$CONSTS();
        InterruptIpu$$CONSTS();
        TableInit$$CREATES();
        NotifySetup$$CREATES();
        NotifyDriverMbx$$CREATES();
        InterruptArp32$$CREATES();
        InterruptDsp$$CREATES();
        InterruptIpu$$CREATES();
        TableInit$$FUNCTIONS();
        NotifySetup$$FUNCTIONS();
        NotifyDriverMbx$$FUNCTIONS();
        InterruptArp32$$FUNCTIONS();
        InterruptDsp$$FUNCTIONS();
        InterruptIpu$$FUNCTIONS();
        TableInit$$SIZES();
        NotifySetup$$SIZES();
        NotifyDriverMbx$$SIZES();
        InterruptArp32$$SIZES();
        InterruptDsp$$SIZES();
        InterruptIpu$$SIZES();
        TableInit$$TYPES();
        NotifySetup$$TYPES();
        NotifyDriverMbx$$TYPES();
        InterruptArp32$$TYPES();
        InterruptDsp$$TYPES();
        InterruptIpu$$TYPES();
        if (isROV) {
            TableInit$$ROV();
            NotifySetup$$ROV();
            NotifyDriverMbx$$ROV();
            InterruptArp32$$ROV();
            InterruptDsp$$ROV();
            InterruptIpu$$ROV();
        }//isROV
        $$SINGLETONS();
        TableInit$$SINGLETONS();
        NotifySetup$$SINGLETONS();
        NotifyDriverMbx$$SINGLETONS();
        InterruptArp32$$SINGLETONS();
        InterruptDsp$$SINGLETONS();
        InterruptIpu$$SINGLETONS();
        $$INITIALIZATION();
    }
}
