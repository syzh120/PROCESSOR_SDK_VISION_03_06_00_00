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

public class ti_sdo_ipc_family_ti81xx
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
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.hal");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.family.ti81xx", new Value.Obj("ti.sdo.ipc.family.ti81xx", pkgP));
    }

    void NotifySetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifySetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifySetup", new Value.Obj("ti.sdo.ipc.family.ti81xx.NotifySetup", po));
        pkgV.bind("NotifySetup", vo);
        // decls 
    }

    void NotifyMbxSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup", new Value.Obj("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup", po));
        pkgV.bind("NotifyMbxSetup", vo);
        // decls 
    }

    void NotifyCircSetup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifyCircSetup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifyCircSetup", new Value.Obj("ti.sdo.ipc.family.ti81xx.NotifyCircSetup", po));
        pkgV.bind("NotifyCircSetup", vo);
        // decls 
    }

    void InterruptDsp$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp", new Value.Obj("ti.sdo.ipc.family.ti81xx.InterruptDsp", po));
        pkgV.bind("InterruptDsp", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.ti81xx"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp$$InterruptDataView", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.InterruptDataView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp$$FxnTable", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.FxnTable", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.Module_State", new Proto.Str(spo, false));
    }

    void InterruptDucati$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati", new Value.Obj("ti.sdo.ipc.family.ti81xx.InterruptDucati", po));
        pkgV.bind("InterruptDucati", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.ti81xx"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati$$FxnTable", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.FxnTable", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.Module_State", new Proto.Str(spo, false));
    }

    void InterruptHost$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost", new Value.Obj("ti.sdo.ipc.family.ti81xx.InterruptHost", po));
        pkgV.bind("InterruptHost", vo);
        // decls 
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.ti81xx"));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost$$InterruptDataView", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.InterruptDataView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost$$FxnTable", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.FxnTable", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.Module_State", new Proto.Str(spo, false));
    }

    void NotifyDriverMbx$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx", new Value.Obj("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx", po));
        pkgV.bind("NotifyDriverMbx", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$BasicView", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Object", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Params", new Proto.Obj());
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Params", new Proto.Str(po, false));
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Object", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance_State", "ti.sdo.ipc.family.ti81xx"));
        }//isROV
    }

    void NotifySetup$$CONSTS()
    {
        // module NotifySetup
        om.bind("ti.sdo.ipc.family.ti81xx.NotifySetup.attach", new Extern("ti_sdo_ipc_family_ti81xx_NotifySetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.NotifySetup.sharedMemReq", new Extern("ti_sdo_ipc_family_ti81xx_NotifySetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.NotifySetup.numIntLines", new Extern("ti_sdo_ipc_family_ti81xx_NotifySetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void NotifyMbxSetup$$CONSTS()
    {
        // module NotifyMbxSetup
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup.attach", new Extern("ti_sdo_ipc_family_ti81xx_NotifyMbxSetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup.sharedMemReq", new Extern("ti_sdo_ipc_family_ti81xx_NotifyMbxSetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup.numIntLines", new Extern("ti_sdo_ipc_family_ti81xx_NotifyMbxSetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void NotifyCircSetup$$CONSTS()
    {
        // module NotifyCircSetup
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyCircSetup.attach", new Extern("ti_sdo_ipc_family_ti81xx_NotifyCircSetup_attach__E", "xdc_Int(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyCircSetup.sharedMemReq", new Extern("ti_sdo_ipc_family_ti81xx_NotifyCircSetup_sharedMemReq__E", "xdc_SizeT(*)(xdc_UInt16,xdc_Ptr)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyCircSetup.numIntLines", new Extern("ti_sdo_ipc_family_ti81xx_NotifyCircSetup_numIntLines__E", "xdc_UInt16(*)(xdc_UInt16)", true, false));
    }

    void InterruptDsp$$CONSTS()
    {
        // module InterruptDsp
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.intEnable", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDsp_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.intDisable", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDsp_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.intRegister", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDsp_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.intUnregister", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDsp_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.intSend", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDsp_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.intPost", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDsp_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.intClear", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDsp_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp.intShmStub", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDsp_intShmStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void InterruptDucati$$CONSTS()
    {
        // module InterruptDucati
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.intEnable", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDucati_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.intDisable", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDucati_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.intRegister", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDucati_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.intUnregister", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDucati_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.intSend", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDucati_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.intPost", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDucati_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.intClear", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDucati_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.intShmDucatiStub", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDucati_intShmDucatiStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati.intShmMbxStub", new Extern("ti_sdo_ipc_family_ti81xx_InterruptDucati_intShmMbxStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void InterruptHost$$CONSTS()
    {
        // module InterruptHost
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.intEnable", new Extern("ti_sdo_ipc_family_ti81xx_InterruptHost_intEnable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.intDisable", new Extern("ti_sdo_ipc_family_ti81xx_InterruptHost_intDisable__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.intRegister", new Extern("ti_sdo_ipc_family_ti81xx_InterruptHost_intRegister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_Fxn,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.intUnregister", new Extern("ti_sdo_ipc_family_ti81xx_InterruptHost_intUnregister__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.intSend", new Extern("ti_sdo_ipc_family_ti81xx_InterruptHost_intSend__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.intPost", new Extern("ti_sdo_ipc_family_ti81xx_InterruptHost_intPost__E", "xdc_Void(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*,xdc_UArg)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.intClear", new Extern("ti_sdo_ipc_family_ti81xx_InterruptHost_intClear__E", "xdc_UInt(*)(xdc_UInt16,ti_sdo_ipc_notifyDrivers_IInterrupt_IntInfo*)", true, false));
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost.intShmStub", new Extern("ti_sdo_ipc_family_ti81xx_InterruptHost_intShmStub__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void NotifyDriverMbx$$CONSTS()
    {
        // module NotifyDriverMbx
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.isr", new Extern("ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_isr__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void NotifySetup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NotifyMbxSetup$$CREATES()
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

    void InterruptHost$$CREATES()
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
            sb.append("ti$sdo$ipc$family$ti81xx$NotifyDriverMbx$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.create() called before xdc.useModule('ti.sdo.ipc.family.ti81xx.NotifyDriverMbx')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$create", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module", "ti.sdo.ipc.family.ti81xx"), om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance", "ti.sdo.ipc.family.ti81xx"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Params", "ti.sdo.ipc.family.ti81xx"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$family$ti81xx$NotifyDriverMbx$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ipc.family.ti81xx']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module", "ti.sdo.ipc.family.ti81xx"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Object", "ti.sdo.ipc.family.ti81xx"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Params", "ti.sdo.ipc.family.ti81xx"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ipc$family$ti81xx$NotifyDriverMbx$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void NotifySetup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifyMbxSetup$$FUNCTIONS()
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

    void InterruptHost$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifyDriverMbx$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NotifySetup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void NotifyMbxSetup$$SIZES()
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

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.FxnTable", "ti.sdo.ipc.family.ti81xx");
        sizes.clear();
        sizes.add(Global.newArray("func", "UFxn"));
        sizes.add(Global.newArray("arg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDsp.FxnTable']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDsp.FxnTable']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDsp.FxnTable'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.Module_State", "ti.sdo.ipc.family.ti81xx");
        sizes.clear();
        sizes.add(Global.newArray("fxnTable", "A3;Sti.sdo.ipc.family.ti81xx.InterruptDsp;FxnTable"));
        sizes.add(Global.newArray("numPlugged", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDsp.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDsp.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDsp.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void InterruptDucati$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.FxnTable", "ti.sdo.ipc.family.ti81xx");
        sizes.clear();
        sizes.add(Global.newArray("func", "UFxn"));
        sizes.add(Global.newArray("arg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDucati.FxnTable']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDucati.FxnTable']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDucati.FxnTable'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.Module_State", "ti.sdo.ipc.family.ti81xx");
        sizes.clear();
        sizes.add(Global.newArray("fxnTable", "A3;Sti.sdo.ipc.family.ti81xx.InterruptDucati;FxnTable"));
        sizes.add(Global.newArray("numPlugged", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDucati.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDucati.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptDucati.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void InterruptHost$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.FxnTable", "ti.sdo.ipc.family.ti81xx");
        sizes.clear();
        sizes.add(Global.newArray("func", "UFxn"));
        sizes.add(Global.newArray("arg", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptHost.FxnTable']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptHost.FxnTable']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptHost.FxnTable'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.Module_State", "ti.sdo.ipc.family.ti81xx");
        sizes.clear();
        sizes.add(Global.newArray("fxnTable", "A3;Sti.sdo.ipc.family.ti81xx.InterruptHost;FxnTable"));
        sizes.add(Global.newArray("numPlugged", "UInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptHost.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptHost.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.ti81xx.InterruptHost.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NotifyDriverMbx$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance_State", "ti.sdo.ipc.family.ti81xx");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("evtRegMask", "UInt32"));
        sizes.add(Global.newArray("notifyHandle", "UPtr"));
        sizes.add(Global.newArray("remoteProcId", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module_State", "ti.sdo.ipc.family.ti81xx");
        sizes.clear();
        sizes.add(Global.newArray("drvHandles", "A4;UPtr"));
        sizes.add(Global.newArray("hwi", "Sti.sysbios.hal.Hwi;Instance_State"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void NotifySetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/ti81xx/NotifySetup.xs");
        om.bind("ti.sdo.ipc.family.ti81xx.NotifySetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifySetup.Module", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.NotifySetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.ti81xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("dspIntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
            po.addFld("videoProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("vpssProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifySetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifySetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifySetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifySetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void NotifyMbxSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/ti81xx/NotifyMbxSetup.xs");
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup.Module", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.ti81xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("dspIntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
            po.addFld("videoProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("vpssProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void NotifyCircSetup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/ti81xx/NotifyCircSetup.xs");
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyCircSetup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyCircSetup.Module", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.NotifyCircSetup.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifySetup.Module", "ti.sdo.ipc.family.ti81xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("dspIntVectId", Proto.Elm.newCNum("(xdc_UInt)"), 5L, "w");
            po.addFld("videoProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("vpssProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyCircSetup$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyCircSetup$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyCircSetup$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyCircSetup$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void InterruptDsp$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/ti81xx/InterruptDsp.xs");
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.Module", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.InterruptDsp.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.ti81xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.family.ti81xx"), $$UNDEF, "wh");
            po.addFld("mailboxBaseAddr", Proto.Elm.newCNum("(xdc_UInt32)"), 0x080C8000L, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("videoProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("vpssProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptDsp$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct InterruptDsp.InterruptDataView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp$$InterruptDataView", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.InterruptDsp.InterruptDataView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteProcName", $$T_Str, $$UNDEF, "w");
                po.addFld("registered", $$T_Bool, $$UNDEF, "w");
                po.addFld("enabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("intPending", $$T_Bool, $$UNDEF, "w");
                po.addFld("payload", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct InterruptDsp.FxnTable
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp$$FxnTable", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.InterruptDsp.FxnTable", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("func", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct InterruptDsp.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp$$Module_State", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.InterruptDsp.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fxnTable", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.FxnTable", "ti.sdo.ipc.family.ti81xx"), false, xdc.services.intern.xsr.Enum.intValue(3L)), $$DEFAULT, "w");
                po.addFld("numPlugged", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void InterruptDucati$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/ti81xx/InterruptDucati.xs");
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.Module", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.InterruptDucati.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.ti81xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("mailboxBaseAddr", Proto.Elm.newCNum("(xdc_UInt32)"), 0x480C8000L, "w");
            po.addFld("ducatiCtrlBaseAddr", Proto.Elm.newCNum("(xdc_UInt32)"), 0x40001000L, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("videoProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("vpssProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptDucati$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct InterruptDucati.FxnTable
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati$$FxnTable", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.InterruptDucati.FxnTable", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("func", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct InterruptDucati.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati$$Module_State", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.InterruptDucati.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fxnTable", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.FxnTable", "ti.sdo.ipc.family.ti81xx"), false, xdc.services.intern.xsr.Enum.intValue(3L)), $$DEFAULT, "w");
                po.addFld("numPlugged", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void InterruptHost$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/ti81xx/InterruptHost.xs");
        om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.Module", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.InterruptHost.Module", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.Module", "ti.sdo.ipc.family.ti81xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.family.ti81xx"), $$UNDEF, "wh");
            po.addFld("mailboxBaseAddr", Proto.Elm.newCNum("(xdc_UInt32)"), 0x480C8000L, "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("videoProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
            po.addFld("vpssProcId", Proto.Elm.newCNum("(xdc_UInt)"), 0xFFFFL, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.InterruptHost$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct InterruptHost.InterruptDataView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost$$InterruptDataView", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.InterruptHost.InterruptDataView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteProcName", $$T_Str, $$UNDEF, "w");
                po.addFld("registered", $$T_Bool, $$UNDEF, "w");
                po.addFld("enabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("intPending", $$T_Bool, $$UNDEF, "w");
                po.addFld("payload", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct InterruptHost.FxnTable
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost$$FxnTable", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.InterruptHost.FxnTable", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("func", new Proto.Adr("xdc_Fxn", "Pf"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct InterruptHost.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost$$Module_State", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.InterruptHost.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fxnTable", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.FxnTable", "ti.sdo.ipc.family.ti81xx"), false, xdc.services.intern.xsr.Enum.intValue(3L)), $$DEFAULT, "w");
                po.addFld("numPlugged", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void NotifyDriverMbx$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/ti81xx/NotifyDriverMbx.xs");
        om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver.Module", "ti.sdo.ipc.family.ti81xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ipc.family.ti81xx"), $$UNDEF, "wh");
            po.addFld("A_notSupported", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sdo.ipc.family.ti81xx"), Global.newObject("msg", "A_notSupported: [enable/disable]Event not supported by NotifyDriverMbx"), "w");
            po.addFld("mailboxBaseAddr", Proto.Elm.newCNum("(xdc_UInt32)"), 0x480C8000L, "w");
            po.addFld("intVectorId", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~1"), "w");
            po.addFld("dspProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
            po.addFld("hostProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
            po.addFld("videoProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
            po.addFld("vpssProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$create", "ti.sdo.ipc.family.ti81xx"), Global.get("ti$sdo$ipc$family$ti81xx$NotifyDriverMbx$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$construct", "ti.sdo.ipc.family.ti81xx"), Global.get("ti$sdo$ipc$family$ti81xx$NotifyDriverMbx$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver.Instance", "ti.sdo.ipc.family.ti81xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.family.ti81xx"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Params", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Params", om.findStrict("ti.sdo.ipc.interfaces.INotifyDriver$$Params", "ti.sdo.ipc.family.ti81xx"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), 0xFFFFL, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ipc.family.ti81xx"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Object", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Object", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance", "ti.sdo.ipc.family.ti81xx"));
        // struct NotifyDriverMbx.BasicView
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$BasicView", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("remoteProcName", $$T_Str, $$UNDEF, "w");
                po.addFld("numIncomingPending", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("numOutgoingPending", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("incomingIntStatus", $$T_Str, $$UNDEF, "w");
                po.addFld("outgoingIntStatus", $$T_Str, $$UNDEF, "w");
                po.addFld("registeredEvents", $$T_Str, $$UNDEF, "w");
        // struct NotifyDriverMbx.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Instance_State", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("evtRegMask", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("notifyHandle", (Proto)om.findStrict("ti.sdo.ipc.Notify.Handle", "ti.sdo.ipc.family.ti81xx"), $$UNDEF, "w");
                po.addFld("remoteProcId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
        // struct NotifyDriverMbx.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Module_State", "ti.sdo.ipc.family.ti81xx");
        po.init("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("drvHandles", new Proto.Arr((Proto)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Handle", "ti.sdo.ipc.family.ti81xx"), false, xdc.services.intern.xsr.Enum.intValue(4L)), $$DEFAULT, "w");
                po.addFldV("hwi", (Proto)om.findStrict("ti.sysbios.hal.Hwi.Object", "ti.sdo.ipc.family.ti81xx"), $$DEFAULT, "wh", $$objFldGet, $$objFldSet);
                po.addFld("Object_field_hwi", (Proto)om.findStrict("ti.sysbios.hal.Hwi.Object", "ti.sdo.ipc.family.ti81xx"), $$DEFAULT, "w");
    }

    void NotifySetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifySetup", "ti.sdo.ipc.family.ti81xx");
    }

    void NotifyMbxSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup", "ti.sdo.ipc.family.ti81xx");
    }

    void NotifyCircSetup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyCircSetup", "ti.sdo.ipc.family.ti81xx");
    }

    void InterruptDsp$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp", "ti.sdo.ipc.family.ti81xx");
        vo.bind("FxnTable$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.ti81xx.InterruptDsp.FxnTable", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp$$FxnTable", "ti.sdo.ipc.family.ti81xx");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.ti81xx.InterruptDsp.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp$$Module_State", "ti.sdo.ipc.family.ti81xx");
    }

    void InterruptDucati$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati", "ti.sdo.ipc.family.ti81xx");
        vo.bind("FxnTable$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.ti81xx.InterruptDucati.FxnTable", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati$$FxnTable", "ti.sdo.ipc.family.ti81xx");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.ti81xx.InterruptDucati.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati$$Module_State", "ti.sdo.ipc.family.ti81xx");
    }

    void InterruptHost$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost", "ti.sdo.ipc.family.ti81xx");
        vo.bind("FxnTable$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.ti81xx.InterruptHost.FxnTable", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost$$FxnTable", "ti.sdo.ipc.family.ti81xx");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.ti81xx.InterruptHost.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost$$Module_State", "ti.sdo.ipc.family.ti81xx");
    }

    void NotifyDriverMbx$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx", "ti.sdo.ipc.family.ti81xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Instance_State", "ti.sdo.ipc.family.ti81xx");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Instance_State", "ti.sdo.ipc.family.ti81xx");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$Module_State", "ti.sdo.ipc.family.ti81xx");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.family.ti81xx.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.family.ti81xx"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/ti81xx/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.family.ti81xx"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.family.ti81xx"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.family.ti81xx"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.family.ti81xx"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.family.ti81xx"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.family.ti81xx"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.family.ti81xx", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.family.ti81xx");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.family.ti81xx.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ipc", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.family.ti81xx'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.family.ti81xx$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.family.ti81xx$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.family.ti81xx$$stat$root'];\n");
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

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifySetup", "ti.sdo.ipc.family.ti81xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifySetup.Module", "ti.sdo.ipc.family.ti81xx");
        vo.init2(po, "ti.sdo.ipc.family.ti81xx.NotifySetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifySetup$$capsule", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.ti81xx", "ti.sdo.ipc.family.ti81xx"));
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
        mcfgs.add("videoProcId");
        icfgs.add("videoProcId");
        mcfgs.add("vpssProcId");
        icfgs.add("vpssProcId");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.ti81xx")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifySetup.attach", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifySetup.sharedMemReq", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifySetup.numIntLines", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_ti81xx_NotifySetup_Module__startupDone__E", "ti_sdo_ipc_family_ti81xx_NotifySetup_attach__E", "ti_sdo_ipc_family_ti81xx_NotifySetup_sharedMemReq__E", "ti_sdo_ipc_family_ti81xx_NotifySetup_numIntLines__E"));
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

    void NotifyMbxSetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup", "ti.sdo.ipc.family.ti81xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup.Module", "ti.sdo.ipc.family.ti81xx");
        vo.init2(po, "ti.sdo.ipc.family.ti81xx.NotifyMbxSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup$$capsule", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.ti81xx", "ti.sdo.ipc.family.ti81xx"));
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
        mcfgs.add("videoProcId");
        icfgs.add("videoProcId");
        mcfgs.add("vpssProcId");
        icfgs.add("vpssProcId");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.ti81xx")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup.attach", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup.sharedMemReq", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup.numIntLines", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_ti81xx_NotifyMbxSetup_Module__startupDone__E", "ti_sdo_ipc_family_ti81xx_NotifyMbxSetup_attach__E", "ti_sdo_ipc_family_ti81xx_NotifyMbxSetup_sharedMemReq__E", "ti_sdo_ipc_family_ti81xx_NotifyMbxSetup_numIntLines__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NotifyMbxSetup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifyMbxSetup");
    }

    void NotifyCircSetup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyCircSetup", "ti.sdo.ipc.family.ti81xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyCircSetup.Module", "ti.sdo.ipc.family.ti81xx");
        vo.init2(po, "ti.sdo.ipc.family.ti81xx.NotifyCircSetup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyCircSetup$$capsule", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.ti81xx", "ti.sdo.ipc.family.ti81xx"));
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
        mcfgs.add("videoProcId");
        icfgs.add("videoProcId");
        mcfgs.add("vpssProcId");
        icfgs.add("vpssProcId");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.ti81xx")).add(vo);
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
        vo.bind("attach", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyCircSetup.attach", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("sharedMemReq", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyCircSetup.sharedMemReq", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("numIntLines", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyCircSetup.numIntLines", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_ti81xx_NotifyCircSetup_Module__startupDone__E", "ti_sdo_ipc_family_ti81xx_NotifyCircSetup_attach__E", "ti_sdo_ipc_family_ti81xx_NotifyCircSetup_sharedMemReq__E", "ti_sdo_ipc_family_ti81xx_NotifyCircSetup_numIntLines__E"));
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

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp", "ti.sdo.ipc.family.ti81xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.Module", "ti.sdo.ipc.family.ti81xx");
        vo.init2(po, "ti.sdo.ipc.family.ti81xx.InterruptDsp", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp$$capsule", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.ti81xx", "ti.sdo.ipc.family.ti81xx"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("InterruptDataView", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.InterruptDataView", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.InterruptDataView", "ti.sdo.ipc.family.ti81xx"));
        mcfgs.add("mailboxBaseAddr");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        mcfgs.add("hostProcId");
        icfgs.add("hostProcId");
        mcfgs.add("videoProcId");
        icfgs.add("videoProcId");
        mcfgs.add("vpssProcId");
        icfgs.add("vpssProcId");
        vo.bind("FxnTable", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.FxnTable", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.FxnTable", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.Module_State", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.Module_State", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.ti81xx")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.intEnable", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.intDisable", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.intRegister", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.intUnregister", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.intSend", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.intPost", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.intClear", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intShmStub", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp.intShmStub", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_ti81xx_InterruptDsp_Module__startupDone__E", "ti_sdo_ipc_family_ti81xx_InterruptDsp_intEnable__E", "ti_sdo_ipc_family_ti81xx_InterruptDsp_intDisable__E", "ti_sdo_ipc_family_ti81xx_InterruptDsp_intRegister__E", "ti_sdo_ipc_family_ti81xx_InterruptDsp_intUnregister__E", "ti_sdo_ipc_family_ti81xx_InterruptDsp_intSend__E", "ti_sdo_ipc_family_ti81xx_InterruptDsp_intPost__E", "ti_sdo_ipc_family_ti81xx_InterruptDsp_intClear__E"));
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

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati", "ti.sdo.ipc.family.ti81xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.Module", "ti.sdo.ipc.family.ti81xx");
        vo.init2(po, "ti.sdo.ipc.family.ti81xx.InterruptDucati", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati$$capsule", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.ti81xx", "ti.sdo.ipc.family.ti81xx"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.ti81xx"));
        mcfgs.add("mailboxBaseAddr");
        mcfgs.add("ducatiCtrlBaseAddr");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        mcfgs.add("hostProcId");
        icfgs.add("hostProcId");
        mcfgs.add("videoProcId");
        icfgs.add("videoProcId");
        mcfgs.add("vpssProcId");
        icfgs.add("vpssProcId");
        vo.bind("FxnTable", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.FxnTable", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.FxnTable", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.Module_State", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.Module_State", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.ti81xx")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.intEnable", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.intDisable", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.intRegister", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.intUnregister", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.intSend", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.intPost", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.intClear", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intShmDucatiStub", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.intShmDucatiStub", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intShmMbxStub", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati.intShmMbxStub", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_ti81xx_InterruptDucati_Module__startupDone__E", "ti_sdo_ipc_family_ti81xx_InterruptDucati_intEnable__E", "ti_sdo_ipc_family_ti81xx_InterruptDucati_intDisable__E", "ti_sdo_ipc_family_ti81xx_InterruptDucati_intRegister__E", "ti_sdo_ipc_family_ti81xx_InterruptDucati_intUnregister__E", "ti_sdo_ipc_family_ti81xx_InterruptDucati_intSend__E", "ti_sdo_ipc_family_ti81xx_InterruptDucati_intPost__E", "ti_sdo_ipc_family_ti81xx_InterruptDucati_intClear__E"));
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

    void InterruptHost$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost", "ti.sdo.ipc.family.ti81xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.Module", "ti.sdo.ipc.family.ti81xx");
        vo.init2(po, "ti.sdo.ipc.family.ti81xx.InterruptHost", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost$$capsule", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.ti81xx", "ti.sdo.ipc.family.ti81xx"));
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
        vo.bind("IntInfo", om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.notifyDrivers.IInterrupt.IntInfo", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("InterruptDataView", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.InterruptDataView", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.InterruptDataView", "ti.sdo.ipc.family.ti81xx"));
        mcfgs.add("mailboxBaseAddr");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        mcfgs.add("hostProcId");
        icfgs.add("hostProcId");
        mcfgs.add("videoProcId");
        icfgs.add("videoProcId");
        mcfgs.add("vpssProcId");
        icfgs.add("vpssProcId");
        vo.bind("FxnTable", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.FxnTable", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.FxnTable", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.Module_State", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.Module_State", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.notifyDrivers");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.ti81xx")).add(vo);
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
        vo.bind("intEnable", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.intEnable", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intDisable", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.intDisable", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intRegister", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.intRegister", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intUnregister", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.intUnregister", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intSend", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.intSend", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intPost", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.intPost", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intClear", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.intClear", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("intShmStub", om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost.intShmStub", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_ti81xx_InterruptHost_Module__startupDone__E", "ti_sdo_ipc_family_ti81xx_InterruptHost_intEnable__E", "ti_sdo_ipc_family_ti81xx_InterruptHost_intDisable__E", "ti_sdo_ipc_family_ti81xx_InterruptHost_intRegister__E", "ti_sdo_ipc_family_ti81xx_InterruptHost_intUnregister__E", "ti_sdo_ipc_family_ti81xx_InterruptHost_intSend__E", "ti_sdo_ipc_family_ti81xx_InterruptHost_intPost__E", "ti_sdo_ipc_family_ti81xx_InterruptHost_intClear__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("InterruptHost", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("InterruptHost");
    }

    void NotifyDriverMbx$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx", "ti.sdo.ipc.family.ti81xx");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module", "ti.sdo.ipc.family.ti81xx");
        vo.init2(po, "ti.sdo.ipc.family.ti81xx.NotifyDriverMbx", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$capsule", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("Instance", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("Params", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Params", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Params", "ti.sdo.ipc.family.ti81xx")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Handle", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family.ti81xx", "ti.sdo.ipc.family.ti81xx"));
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
        vo.bind("BasicView", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.BasicView", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.BasicView", "ti.sdo.ipc.family.ti81xx"));
        mcfgs.add("A_notSupported");
        mcfgs.add("mailboxBaseAddr");
        mcfgs.add("intVectorId");
        mcfgs.add("dspProcId");
        icfgs.add("dspProcId");
        mcfgs.add("hostProcId");
        icfgs.add("hostProcId");
        mcfgs.add("videoProcId");
        icfgs.add("videoProcId");
        mcfgs.add("vpssProcId");
        icfgs.add("vpssProcId");
        vo.bind("Instance_State", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance_State", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Instance_State", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("Module_State", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module_State", "ti.sdo.ipc.family.ti81xx"));
        tdefs.add(om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Module_State", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ipc.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family.ti81xx")).add(vo);
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
            vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sdo$ipc$family$ti81xx$NotifyDriverMbx$$__initObject"));
        }//isCFG
        vo.bind("isr", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.isr", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_Handle__label__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_Module__startupDone__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_Object__create__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_Object__delete__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_Object__destruct__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_Object__get__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_Object__first__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_Object__next__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_Params__init__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_registerEvent__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_unregisterEvent__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_sendEvent__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_disable__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_enable__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_disableEvent__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_enableEvent__E", "ti_sdo_ipc_family_ti81xx_NotifyDriverMbx_setNotifyHandle__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_notSupported"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx.Object", "ti.sdo.ipc.family.ti81xx"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("NotifyDriverMbx", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NotifyDriverMbx");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sdo.ipc.family.ti81xx")).findStrict("PARAMS", "ti.sdo.ipc.family.ti81xx");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx", "ti.sdo.ipc.family.ti81xx")).findStrict("PARAMS", "ti.sdo.ipc.family.ti81xx");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifySetup", "ti.sdo.ipc.family.ti81xx"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup", "ti.sdo.ipc.family.ti81xx"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyCircSetup", "ti.sdo.ipc.family.ti81xx"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp", "ti.sdo.ipc.family.ti81xx"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDucati", "ti.sdo.ipc.family.ti81xx"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost", "ti.sdo.ipc.family.ti81xx"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx", "ti.sdo.ipc.family.ti81xx"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptDsp", "ti.sdo.ipc.family.ti81xx");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"IncomingInterrupts", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE_DATA"), "viewInitFxn", "viewInitInterrupt", "structName", "InterruptDataView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.InterruptHost", "ti.sdo.ipc.family.ti81xx");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"IncomingInterrupts", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE_DATA"), "viewInitFxn", "viewInitInterrupt", "structName", "InterruptDataView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx", "ti.sdo.ipc.family.ti81xx");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.family.ti81xx.NotifySetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.ti81xx.NotifyMbxSetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.ti81xx.NotifyCircSetup")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.ti81xx.InterruptDsp")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.ti81xx.InterruptDucati")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.ti81xx.InterruptHost")).bless();
        ((Value.Obj)om.getv("ti.sdo.ipc.family.ti81xx.NotifyDriverMbx")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.family.ti81xx")).add(pkgV);
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
        NotifyMbxSetup$$OBJECTS();
        NotifyCircSetup$$OBJECTS();
        InterruptDsp$$OBJECTS();
        InterruptDucati$$OBJECTS();
        InterruptHost$$OBJECTS();
        NotifyDriverMbx$$OBJECTS();
        NotifySetup$$CONSTS();
        NotifyMbxSetup$$CONSTS();
        NotifyCircSetup$$CONSTS();
        InterruptDsp$$CONSTS();
        InterruptDucati$$CONSTS();
        InterruptHost$$CONSTS();
        NotifyDriverMbx$$CONSTS();
        NotifySetup$$CREATES();
        NotifyMbxSetup$$CREATES();
        NotifyCircSetup$$CREATES();
        InterruptDsp$$CREATES();
        InterruptDucati$$CREATES();
        InterruptHost$$CREATES();
        NotifyDriverMbx$$CREATES();
        NotifySetup$$FUNCTIONS();
        NotifyMbxSetup$$FUNCTIONS();
        NotifyCircSetup$$FUNCTIONS();
        InterruptDsp$$FUNCTIONS();
        InterruptDucati$$FUNCTIONS();
        InterruptHost$$FUNCTIONS();
        NotifyDriverMbx$$FUNCTIONS();
        NotifySetup$$SIZES();
        NotifyMbxSetup$$SIZES();
        NotifyCircSetup$$SIZES();
        InterruptDsp$$SIZES();
        InterruptDucati$$SIZES();
        InterruptHost$$SIZES();
        NotifyDriverMbx$$SIZES();
        NotifySetup$$TYPES();
        NotifyMbxSetup$$TYPES();
        NotifyCircSetup$$TYPES();
        InterruptDsp$$TYPES();
        InterruptDucati$$TYPES();
        InterruptHost$$TYPES();
        NotifyDriverMbx$$TYPES();
        if (isROV) {
            NotifySetup$$ROV();
            NotifyMbxSetup$$ROV();
            NotifyCircSetup$$ROV();
            InterruptDsp$$ROV();
            InterruptDucati$$ROV();
            InterruptHost$$ROV();
            NotifyDriverMbx$$ROV();
        }//isROV
        $$SINGLETONS();
        NotifySetup$$SINGLETONS();
        NotifyMbxSetup$$SINGLETONS();
        NotifyCircSetup$$SINGLETONS();
        InterruptDsp$$SINGLETONS();
        InterruptDucati$$SINGLETONS();
        InterruptHost$$SINGLETONS();
        NotifyDriverMbx$$SINGLETONS();
        $$INITIALIZATION();
    }
}
