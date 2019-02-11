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

public class ti_sdo_ipc_family_da830
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.family.da830.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.family.da830", new Value.Obj("ti.sdo.ipc.family.da830", pkgP));
    }

    void NotifySetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.da830.NotifySetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.da830.NotifySetup", new Value.Obj("ti.sdo.ipc.family.da830.NotifySetup", po));
        pkgV.bind("NotifySetup", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.da830.NotifySetup.DSP_INT", new Proto.Enm("ti.sdo.ipc.family.da830.NotifySetup.DSP_INT"));
        om.bind("ti.sdo.ipc.family.da830.NotifySetup.ARM_INT", new Proto.Enm("ti.sdo.ipc.family.da830.NotifySetup.ARM_INT"));
    }

    void NotifyCircSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup", new Value.Obj("ti.sdo.ipc.family.da830.NotifyCircSetup", po));
        pkgV.bind("NotifyCircSetup", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT", new Proto.Enm("ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT"));
        om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT", new Proto.Enm("ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT"));
    }

    void InterruptDsp$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.da830.InterruptDsp.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.da830.InterruptDsp", new Value.Obj("ti.sdo.ipc.family.da830.InterruptDsp", po));
        pkgV.bind("InterruptDsp", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.da830.InterruptDsp.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.da830"));
    }

    void InterruptArm$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.da830.InterruptArm.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.da830.InterruptArm", new Value.Obj("ti.sdo.ipc.family.da830.InterruptArm", po));
        pkgV.bind("InterruptArm", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.da830.InterruptArm.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.da830"));
    }

    void NotifySetup$$CONSTS()
    {
        // module NotifySetup
        om.bind("ti.sdo.ipc.family.da830.NotifySetup.DSP_INT0", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.DSP_INT", "ti.sdo.ipc.family.da830"), "ti.sdo.ipc.family.da830.NotifySetup.DSP_INT0", xdc.services.intern.xsr.Enum.intValue(5L)+0));
        om.bind("ti.sdo.ipc.family.da830.NotifySetup.DSP_INT1", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.DSP_INT", "ti.sdo.ipc.family.da830"), "ti.sdo.ipc.family.da830.NotifySetup.DSP_INT1", xdc.services.intern.xsr.Enum.intValue(67L)+0));
        om.bind("ti.sdo.ipc.family.da830.NotifySetup.ARM_INT0", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.ARM_INT", "ti.sdo.ipc.family.da830"), "ti.sdo.ipc.family.da830.NotifySetup.ARM_INT0", xdc.services.intern.xsr.Enum.intValue(28L)+0));
        om.bind("ti.sdo.ipc.family.da830.NotifySetup.ARM_INT1", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.ARM_INT", "ti.sdo.ipc.family.da830"), "ti.sdo.ipc.family.da830.NotifySetup.ARM_INT1", xdc.services.intern.xsr.Enum.intValue(29L)+0));
        om.bind("ti.sdo.ipc.family.da830.NotifySetup.attach", new Extern("ti_sdo_ipc_family_da830_NotifySetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.da830.NotifySetup.sharedMemReq", new Extern("ti_sdo_ipc_family_da830_NotifySetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.da830.NotifySetup.numIntLines", new Extern("ti_sdo_ipc_family_da830_NotifySetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void NotifyCircSetup$$CONSTS()
    {
        // module NotifyCircSetup
        om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT0", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT", "ti.sdo.ipc.family.da830"), "ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT0", xdc.services.intern.xsr.Enum.intValue(5L)+0));
        om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT1", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT", "ti.sdo.ipc.family.da830"), "ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT1", xdc.services.intern.xsr.Enum.intValue(67L)+0));
        om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT0", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT", "ti.sdo.ipc.family.da830"), "ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT0", xdc.services.intern.xsr.Enum.intValue(28L)+0));
        om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT1", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT", "ti.sdo.ipc.family.da830"), "ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT1", xdc.services.intern.xsr.Enum.intValue(29L)+0));
        om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup.attach", new Extern("ti_sdo_ipc_family_da830_NotifyCircSetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup.sharedMemReq", new Extern("ti_sdo_ipc_family_da830_NotifyCircSetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup.numIntLines", new Extern("ti_sdo_ipc_family_da830_NotifyCircSetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void InterruptDsp$$CONSTS()
    {
        // module InterruptDsp
        om.bind("ti.sdo.ipc.family.da830.InterruptDsp.intEnable", new Extern("ti_sdo_ipc_family_da830_InterruptDsp_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptDsp.intDisable", new Extern("ti_sdo_ipc_family_da830_InterruptDsp_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptDsp.intRegister", new Extern("ti_sdo_ipc_family_da830_InterruptDsp_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptDsp.intUnregister", new Extern("ti_sdo_ipc_family_da830_InterruptDsp_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptDsp.intSend", new Extern("ti_sdo_ipc_family_da830_InterruptDsp_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptDsp.intPost", new Extern("ti_sdo_ipc_family_da830_InterruptDsp_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptDsp.intClear", new Extern("ti_sdo_ipc_family_da830_InterruptDsp_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptDsp.isIntSet", new Extern("ti_sdo_ipc_family_da830_InterruptDsp_isIntSet__E", "xdc_Bool(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
    }

    void InterruptArm$$CONSTS()
    {
        // module InterruptArm
        om.bind("ti.sdo.ipc.family.da830.InterruptArm.intEnable", new Extern("ti_sdo_ipc_family_da830_InterruptArm_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptArm.intDisable", new Extern("ti_sdo_ipc_family_da830_InterruptArm_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptArm.intRegister", new Extern("ti_sdo_ipc_family_da830_InterruptArm_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptArm.intUnregister", new Extern("ti_sdo_ipc_family_da830_InterruptArm_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptArm.intSend", new Extern("ti_sdo_ipc_family_da830_InterruptArm_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptArm.intPost", new Extern("ti_sdo_ipc_family_da830_InterruptArm_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.da830.InterruptArm.intClear", new Extern("ti_sdo_ipc_family_da830_InterruptArm_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
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

    void InterruptArm$$CREATES()
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

    void InterruptArm$$FUNCTIONS()
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

    }

    void InterruptArm$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void NotifySetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/da830/NotifySetup.xs");
        om.bind("ti.sdo.ipc.family.da830.NotifySetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.Module", "ti.sdo.ipc.family.da830");
        po.init("ti.sdo.ipc.family.da830.NotifySetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.da830"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("dspRecvIntId0", Proto.Elm.newCNum("(xdc_UInt)"), om.find("ti.sdo.ipc.family.da830.NotifySetup.DSP_INT0"), "w");
            po.addFld("dspIntVectId0", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
            po.addFld("armRecvIntId0", Proto.Elm.newCNum("(xdc_UInt)"), om.find("ti.sdo.ipc.family.da830.NotifySetup.ARM_INT0"), "w");
            po.addFld("useSecondLine", $$T_Bool, false, "w");
            po.addFld("dspRecvIntId1", Proto.Elm.newCNum("(xdc_UInt)"), om.find("ti.sdo.ipc.family.da830.NotifySetup.DSP_INT1"), "w");
            po.addFld("dspIntVectId1", Proto.Elm.newCNum("(xdc_UInt)"), 6L, "w");
            po.addFld("armRecvIntId1", Proto.Elm.newCNum("(xdc_UInt)"), om.find("ti.sdo.ipc.family.da830.NotifySetup.ARM_INT1"), "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.NotifySetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.NotifySetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.NotifySetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.NotifySetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void NotifyCircSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/da830/NotifyCircSetup.xs");
        om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.Module", "ti.sdo.ipc.family.da830");
        po.init("ti.sdo.ipc.family.da830.NotifyCircSetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.da830"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("dspRecvIntId0", Proto.Elm.newCNum("(xdc_UInt)"), om.find("ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT0"), "w");
            po.addFld("dspIntVectId0", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
            po.addFld("armRecvIntId0", Proto.Elm.newCNum("(xdc_UInt)"), om.find("ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT0"), "w");
            po.addFld("useSecondLine", $$T_Bool, false, "w");
            po.addFld("dspRecvIntId1", Proto.Elm.newCNum("(xdc_UInt)"), om.find("ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT1"), "w");
            po.addFld("dspIntVectId1", Proto.Elm.newCNum("(xdc_UInt)"), 6L, "w");
            po.addFld("armRecvIntId1", Proto.Elm.newCNum("(xdc_UInt)"), om.find("ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT1"), "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.NotifyCircSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void InterruptDsp$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/da830/InterruptDsp.xs");
        om.bind("ti.sdo.ipc.family.da830.InterruptDsp$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp.Module", "ti.sdo.ipc.family.da830");
        po.init("ti.sdo.ipc.family.da830.InterruptDsp.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.da830"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.InterruptDsp$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.InterruptDsp$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.InterruptDsp$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.InterruptDsp$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void InterruptArm$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/da830/InterruptArm.xs");
        om.bind("ti.sdo.ipc.family.da830.InterruptArm$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.da830.InterruptArm.Module", "ti.sdo.ipc.family.da830");
        po.init("ti.sdo.ipc.family.da830.InterruptArm.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.da830"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.InterruptArm$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.InterruptArm$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.InterruptArm$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.da830.InterruptArm$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void NotifySetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.da830.NotifySetup", "ti.sdo.ipc.family.da830");
    }

    void NotifyCircSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup", "ti.sdo.ipc.family.da830");
    }

    void InterruptDsp$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp", "ti.sdo.ipc.family.da830");
    }

    void InterruptArm$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.da830.InterruptArm", "ti.sdo.ipc.family.da830");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.family.da830.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.family.da830"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/da830/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.family.da830"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.family.da830"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.family.da830"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.family.da830"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.family.da830"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.family.da830"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.family.da830", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.family.da830");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.family.da830.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ipc", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.family.da830'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.family.da830$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.family.da830$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.family.da830$$stat$root'];\n");
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

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.da830.NotifySetup", "ti.sdo.ipc.family.da830");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.Module", "ti.sdo.ipc.family.da830");
        vo.init2(po, "ti.sdo.ipc.family.da830.NotifySetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.da830.NotifySetup$$capsule", "ti.sdo.ipc.family.da830"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.da830", "ti.sdo.ipc.family.da830"));
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
        vo.bind("DSP_INT", om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.DSP_INT", "ti.sdo.ipc.family.da830"));
        vo.bind("ARM_INT", om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.ARM_INT", "ti.sdo.ipc.family.da830"));
        mcfgs.add("dspRecvIntId0");
        mcfgs.add("dspIntVectId0");
        mcfgs.add("armRecvIntId0");
        mcfgs.add("useSecondLine");
        mcfgs.add("dspRecvIntId1");
        mcfgs.add("dspIntVectId1");
        mcfgs.add("armRecvIntId1");
        vo.bind("DSP_INT0", om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.DSP_INT0", "ti.sdo.ipc.family.da830"));
        vo.bind("DSP_INT1", om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.DSP_INT1", "ti.sdo.ipc.family.da830"));
        vo.bind("ARM_INT0", om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.ARM_INT0", "ti.sdo.ipc.family.da830"));
        vo.bind("ARM_INT1", om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.ARM_INT1", "ti.sdo.ipc.family.da830"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.da830")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.attach", "ti.sdo.ipc.family.da830"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.sharedMemReq", "ti.sdo.ipc.family.da830"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.da830.NotifySetup.numIntLines", "ti.sdo.ipc.family.da830"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_da830_NotifySetup_Module__startupDone__E", "ti_sdo_ipc_family_da830_NotifySetup_attach__E", "ti_sdo_ipc_family_da830_NotifySetup_sharedMemReq__E", "ti_sdo_ipc_family_da830_NotifySetup_numIntLines__E"));
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

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup", "ti.sdo.ipc.family.da830");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.Module", "ti.sdo.ipc.family.da830");
        vo.init2(po, "ti.sdo.ipc.family.da830.NotifyCircSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup$$capsule", "ti.sdo.ipc.family.da830"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.da830", "ti.sdo.ipc.family.da830"));
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
        vo.bind("DSP_INT", om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT", "ti.sdo.ipc.family.da830"));
        vo.bind("ARM_INT", om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT", "ti.sdo.ipc.family.da830"));
        mcfgs.add("dspRecvIntId0");
        mcfgs.add("dspIntVectId0");
        mcfgs.add("armRecvIntId0");
        mcfgs.add("useSecondLine");
        mcfgs.add("dspRecvIntId1");
        mcfgs.add("dspIntVectId1");
        mcfgs.add("armRecvIntId1");
        vo.bind("DSP_INT0", om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT0", "ti.sdo.ipc.family.da830"));
        vo.bind("DSP_INT1", om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.DSP_INT1", "ti.sdo.ipc.family.da830"));
        vo.bind("ARM_INT0", om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT0", "ti.sdo.ipc.family.da830"));
        vo.bind("ARM_INT1", om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.ARM_INT1", "ti.sdo.ipc.family.da830"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.da830")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.attach", "ti.sdo.ipc.family.da830"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.sharedMemReq", "ti.sdo.ipc.family.da830"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup.numIntLines", "ti.sdo.ipc.family.da830"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_da830_NotifyCircSetup_Module__startupDone__E", "ti_sdo_ipc_family_da830_NotifyCircSetup_attach__E", "ti_sdo_ipc_family_da830_NotifyCircSetup_sharedMemReq__E", "ti_sdo_ipc_family_da830_NotifyCircSetup_numIntLines__E"));
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

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp", "ti.sdo.ipc.family.da830");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp.Module", "ti.sdo.ipc.family.da830");
        vo.init2(po, "ti.sdo.ipc.family.da830.InterruptDsp", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp$$capsule", "ti.sdo.ipc.family.da830"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.da830", "ti.sdo.ipc.family.da830"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.da830"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.da830"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.da830")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp.intEnable", "ti.sdo.ipc.family.da830"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp.intDisable", "ti.sdo.ipc.family.da830"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp.intRegister", "ti.sdo.ipc.family.da830"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp.intUnregister", "ti.sdo.ipc.family.da830"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp.intSend", "ti.sdo.ipc.family.da830"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp.intPost", "ti.sdo.ipc.family.da830"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp.intClear", "ti.sdo.ipc.family.da830"));
        vo.bind("isIntSet", om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp.isIntSet", "ti.sdo.ipc.family.da830"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_da830_InterruptDsp_Module__startupDone__E", "ti_sdo_ipc_family_da830_InterruptDsp_intEnable__E", "ti_sdo_ipc_family_da830_InterruptDsp_intDisable__E", "ti_sdo_ipc_family_da830_InterruptDsp_intRegister__E", "ti_sdo_ipc_family_da830_InterruptDsp_intUnregister__E", "ti_sdo_ipc_family_da830_InterruptDsp_intSend__E", "ti_sdo_ipc_family_da830_InterruptDsp_intPost__E", "ti_sdo_ipc_family_da830_InterruptDsp_intClear__E", "ti_sdo_ipc_family_da830_InterruptDsp_isIntSet__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "isIntSet", "entry", "0x%x, %p", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("InterruptDsp", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("InterruptDsp");
    }

    void InterruptArm$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.da830.InterruptArm", "ti.sdo.ipc.family.da830");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.da830.InterruptArm.Module", "ti.sdo.ipc.family.da830");
        vo.init2(po, "ti.sdo.ipc.family.da830.InterruptArm", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.da830.InterruptArm$$capsule", "ti.sdo.ipc.family.da830"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.da830", "ti.sdo.ipc.family.da830"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.da830"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.da830"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.da830")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.da830.InterruptArm.intEnable", "ti.sdo.ipc.family.da830"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.da830.InterruptArm.intDisable", "ti.sdo.ipc.family.da830"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.da830.InterruptArm.intRegister", "ti.sdo.ipc.family.da830"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.da830.InterruptArm.intUnregister", "ti.sdo.ipc.family.da830"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.da830.InterruptArm.intSend", "ti.sdo.ipc.family.da830"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.da830.InterruptArm.intPost", "ti.sdo.ipc.family.da830"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.da830.InterruptArm.intClear", "ti.sdo.ipc.family.da830"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_da830_InterruptArm_Module__startupDone__E", "ti_sdo_ipc_family_da830_InterruptArm_intEnable__E", "ti_sdo_ipc_family_da830_InterruptArm_intDisable__E", "ti_sdo_ipc_family_da830_InterruptArm_intRegister__E", "ti_sdo_ipc_family_da830_InterruptArm_intUnregister__E", "ti_sdo_ipc_family_da830_InterruptArm_intSend__E", "ti_sdo_ipc_family_da830_InterruptArm_intPost__E", "ti_sdo_ipc_family_da830_InterruptArm_intClear__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("InterruptArm", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("InterruptArm");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.da830.NotifySetup", "ti.sdo.ipc.family.da830"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.da830.NotifyCircSetup", "ti.sdo.ipc.family.da830"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.da830.InterruptDsp", "ti.sdo.ipc.family.da830"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.da830.InterruptArm", "ti.sdo.ipc.family.da830"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.family.da830.NotifySetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.da830.NotifyCircSetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.da830.InterruptDsp")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.da830.InterruptArm")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.family.da830")).add(pkgV);
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
        InterruptArm$$OBJECTS();
        NotifySetup$$CONSTS();
        NotifyCircSetup$$CONSTS();
        InterruptDsp$$CONSTS();
        InterruptArm$$CONSTS();
        NotifySetup$$CREATES();
        NotifyCircSetup$$CREATES();
        InterruptDsp$$CREATES();
        InterruptArm$$CREATES();
        NotifySetup$$FUNCTIONS();
        NotifyCircSetup$$FUNCTIONS();
        InterruptDsp$$FUNCTIONS();
        InterruptArm$$FUNCTIONS();
        NotifySetup$$SIZES();
        NotifyCircSetup$$SIZES();
        InterruptDsp$$SIZES();
        InterruptArm$$SIZES();
        NotifySetup$$TYPES();
        NotifyCircSetup$$TYPES();
        InterruptDsp$$TYPES();
        InterruptArm$$TYPES();
        if (isROV) {
            NotifySetup$$ROV();
            NotifyCircSetup$$ROV();
            InterruptDsp$$ROV();
            InterruptArm$$ROV();
        }//isROV
        $$SINGLETONS();
        NotifySetup$$SINGLETONS();
        NotifyCircSetup$$SINGLETONS();
        InterruptDsp$$SINGLETONS();
        InterruptArm$$SINGLETONS();
        $$INITIALIZATION();
    }
}
