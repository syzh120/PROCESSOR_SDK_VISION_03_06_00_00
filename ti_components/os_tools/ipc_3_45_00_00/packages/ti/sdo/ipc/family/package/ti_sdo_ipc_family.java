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

public class ti_sdo_ipc_family
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
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.family.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.family", new Value.Obj("ti.sdo.ipc.family", pkgP));
    }

    void Settings$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.family.Settings.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.family.Settings", new Value.Obj("ti.sdo.ipc.family.Settings", po));
        pkgV.bind("Settings", vo);
        // decls 
    }

    void Settings$$CONSTS()
    {
        // module Settings
    }

    void Settings$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Settings$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Settings.getDefaultInterruptDelegate
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$getDefaultInterruptDelegate", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), $$T_Str, 0, 0, false));
        // fxn Settings.getGateHWSpinlockSettings
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$getGateHWSpinlockSettings", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), $$T_Obj, 0, 0, false));
        // fxn Settings.getGateHWSemSettings
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$getGateHWSemSettings", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), $$T_Obj, 0, 0, false));
        // fxn Settings.getHWGate
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$getHWGate", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), $$T_Str, 0, 0, false));
        // fxn Settings.getIpcSR0Setup
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$getIpcSR0Setup", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), $$T_Bool, 0, 0, false));
        // fxn Settings.getHostProcId
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$getHostProcId", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), Proto.Elm.newCNum("(xdc_UInt16)"), 0, 0, false));
        // fxn Settings.procInDevice
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$procInDevice", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), $$T_Bool, 1, 1, false));
                fxn.addArg(0, "procName", $$T_Str, $$UNDEF);
        // fxn Settings.getDeviceProcNames
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$getDeviceProcNames", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), $$T_Obj, 0, 0, false));
        // fxn Settings.getNameServerRemoteDelegate
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$getNameServerRemoteDelegate", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), $$T_Str, 0, 0, false));
        // fxn Settings.getNotifySetupDelegate
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$getNotifySetupDelegate", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), $$T_Str, 0, 0, false));
        // fxn Settings.getMessageQSetupDelegate
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$getMessageQSetupDelegate", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), $$T_Str, 0, 0, false));
        // fxn Settings.generateSlaveDataForHost
        fxn = (Proto.Fxn)om.bind("ti.sdo.ipc.family.Settings$$generateSlaveDataForHost", new Proto.Fxn(om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family"), $$T_Bool, 0, 0, false));
    }

    void Settings$$SIZES()
    {
    }

    void Settings$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/Settings.xs");
        om.bind("ti.sdo.ipc.family.Settings$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family");
        po.init("ti.sdo.ipc.family.Settings.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.family.Settings$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.family.Settings$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.family.Settings$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("getDefaultInterruptDelegate", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$getDefaultInterruptDelegate", "ti.sdo.ipc.family"), Global.get(cap, "getDefaultInterruptDelegate"));
                po.addFxn("getGateHWSpinlockSettings", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$getGateHWSpinlockSettings", "ti.sdo.ipc.family"), Global.get(cap, "getGateHWSpinlockSettings"));
                po.addFxn("getGateHWSemSettings", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$getGateHWSemSettings", "ti.sdo.ipc.family"), Global.get(cap, "getGateHWSemSettings"));
                po.addFxn("getHWGate", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$getHWGate", "ti.sdo.ipc.family"), Global.get(cap, "getHWGate"));
                po.addFxn("getIpcSR0Setup", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$getIpcSR0Setup", "ti.sdo.ipc.family"), Global.get(cap, "getIpcSR0Setup"));
                po.addFxn("getHostProcId", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$getHostProcId", "ti.sdo.ipc.family"), Global.get(cap, "getHostProcId"));
                po.addFxn("procInDevice", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$procInDevice", "ti.sdo.ipc.family"), Global.get(cap, "procInDevice"));
                po.addFxn("getDeviceProcNames", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$getDeviceProcNames", "ti.sdo.ipc.family"), Global.get(cap, "getDeviceProcNames"));
                po.addFxn("getNameServerRemoteDelegate", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$getNameServerRemoteDelegate", "ti.sdo.ipc.family"), Global.get(cap, "getNameServerRemoteDelegate"));
                po.addFxn("getNotifySetupDelegate", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$getNotifySetupDelegate", "ti.sdo.ipc.family"), Global.get(cap, "getNotifySetupDelegate"));
                po.addFxn("getMessageQSetupDelegate", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$getMessageQSetupDelegate", "ti.sdo.ipc.family"), Global.get(cap, "getMessageQSetupDelegate"));
                po.addFxn("generateSlaveDataForHost", (Proto.Fxn)om.findStrict("ti.sdo.ipc.family.Settings$$generateSlaveDataForHost", "ti.sdo.ipc.family"), Global.get(cap, "generateSlaveDataForHost"));
    }

    void Settings$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.family.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.family"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/family/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ipc.family"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ipc.family"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ipc.family"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ipc.family"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ipc.family"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ipc.family"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ipc.family", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.family");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.family.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.family'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.family$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.family$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.family$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Settings$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.family.Settings", "ti.sdo.ipc.family");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.family.Settings.Module", "ti.sdo.ipc.family");
        vo.init2(po, "ti.sdo.ipc.family.Settings", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.family.Settings$$capsule", "ti.sdo.ipc.family"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.family", "ti.sdo.ipc.family"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.family")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.family.Settings$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Settings", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Settings");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.family.Settings", "ti.sdo.ipc.family"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.family.Settings")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.family")).add(pkgV);
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
        Settings$$OBJECTS();
        Settings$$CONSTS();
        Settings$$CREATES();
        Settings$$FUNCTIONS();
        Settings$$SIZES();
        Settings$$TYPES();
        if (isROV) {
            Settings$$ROV();
        }//isROV
        $$SINGLETONS();
        Settings$$SINGLETONS();
        $$INITIALIZATION();
    }
}
