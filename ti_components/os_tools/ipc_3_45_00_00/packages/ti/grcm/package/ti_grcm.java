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

public class ti_grcm
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
        pkgP = (Proto.Obj)om.bind("ti.grcm.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.grcm", new Value.Obj("ti.grcm", pkgP));
    }

    void RcmServer$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.grcm.RcmServer.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.grcm.RcmServer", new Value.Obj("ti.grcm.RcmServer", po));
        pkgV.bind("RcmServer", vo);
        // decls 
    }

    void Settings$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.grcm.Settings.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.grcm.Settings", new Value.Obj("ti.grcm.Settings", po));
        pkgV.bind("Settings", vo);
        // decls 
        om.bind("ti.grcm.Settings.IpcSupport", new Proto.Enm("ti.grcm.Settings.IpcSupport"));
    }

    void RcmServer$$CONSTS()
    {
        // module RcmServer
    }

    void Settings$$CONSTS()
    {
        // module Settings
        om.bind("ti.grcm.Settings.IpcSupport_ti_sdo_ipc", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.grcm.Settings.IpcSupport", "ti.grcm"), "ti.grcm.Settings.IpcSupport_ti_sdo_ipc", 0));
        om.bind("ti.grcm.Settings.IpcSupport_ti_syslink_ipc", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.grcm.Settings.IpcSupport", "ti.grcm"), "ti.grcm.Settings.IpcSupport_ti_syslink_ipc", 1));
    }

    void RcmServer$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Settings$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void RcmServer$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Settings$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void RcmServer$$SIZES()
    {
    }

    void Settings$$SIZES()
    {
    }

    void RcmServer$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/grcm/RcmServer.xs");
        om.bind("ti.grcm.RcmServer$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.grcm.RcmServer.Module", "ti.grcm");
        po.init("ti.grcm.RcmServer.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.grcm.RcmServer$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.grcm.RcmServer$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.grcm.RcmServer$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void Settings$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/grcm/Settings.xs");
        om.bind("ti.grcm.Settings$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.grcm.Settings.Module", "ti.grcm");
        po.init("ti.grcm.Settings.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("ipc", (Proto)om.findStrict("ti.grcm.Settings.IpcSupport", "ti.grcm"), om.find("ti.grcm.Settings.IpcSupport_ti_sdo_ipc"), "wh");
        po.addFld("loadStrings", $$T_Bool, true, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.grcm.Settings$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.grcm.Settings$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.grcm.Settings$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void RcmServer$$ROV()
    {
    }

    void Settings$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.grcm.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.grcm"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/grcm/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.grcm"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.grcm"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.grcm"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.grcm"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.grcm"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.grcm"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.grcm", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.grcm");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.grcm.");
        pkgV.bind("$vers", Global.newArray(2, 1, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.grcm'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.grcm$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.grcm$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.grcm$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/ti.grcm.aem4',\n");
            sb.append("'lib/release/ti.grcm.aem4',\n");
            sb.append("'lib/debug/ti.grcm.aem4f',\n");
            sb.append("'lib/release/ti.grcm.aem4f',\n");
            sb.append("'lib/debug/ti.grcm.ae66',\n");
            sb.append("'lib/release/ti.grcm.ae66',\n");
            sb.append("'lib/debug/ti.grcm.aearp32',\n");
            sb.append("'lib/release/ti.grcm.aearp32',\n");
            sb.append("'lib/debug/ti.grcm.aearp32F',\n");
            sb.append("'lib/release/ti.grcm.aearp32F',\n");
            sb.append("'lib/debug/ti.grcm.aa15fg',\n");
            sb.append("'lib/release/ti.grcm.aa15fg',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/ti.grcm.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.grcm.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.grcm.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.grcm.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.grcm.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/ti.grcm.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/ti.grcm.aearp32', {target: 'ti.targets.arp32.elf.ARP32', suffix: 'earp32'}],\n");
            sb.append("['lib/release/ti.grcm.aearp32', {target: 'ti.targets.arp32.elf.ARP32', suffix: 'earp32'}],\n");
            sb.append("['lib/debug/ti.grcm.aearp32F', {target: 'ti.targets.arp32.elf.ARP32_far', suffix: 'earp32F'}],\n");
            sb.append("['lib/release/ti.grcm.aearp32F', {target: 'ti.targets.arp32.elf.ARP32_far', suffix: 'earp32F'}],\n");
            sb.append("['lib/debug/ti.grcm.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/release/ti.grcm.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void RcmServer$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.grcm.RcmServer", "ti.grcm");
        po = (Proto.Obj)om.findStrict("ti.grcm.RcmServer.Module", "ti.grcm");
        vo.init2(po, "ti.grcm.RcmServer", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.grcm.RcmServer$$capsule", "ti.grcm"));
        vo.bind("$package", om.findStrict("ti.grcm", "ti.grcm"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.grcm")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.grcm.RcmServer$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("RcmServer", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("RcmServer");
    }

    void Settings$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.grcm.Settings", "ti.grcm");
        po = (Proto.Obj)om.findStrict("ti.grcm.Settings.Module", "ti.grcm");
        vo.init2(po, "ti.grcm.Settings", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.grcm.Settings$$capsule", "ti.grcm"));
        vo.bind("$package", om.findStrict("ti.grcm", "ti.grcm"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("IpcSupport", om.findStrict("ti.grcm.Settings.IpcSupport", "ti.grcm"));
        vo.bind("IpcSupport_ti_sdo_ipc", om.findStrict("ti.grcm.Settings.IpcSupport_ti_sdo_ipc", "ti.grcm"));
        vo.bind("IpcSupport_ti_syslink_ipc", om.findStrict("ti.grcm.Settings.IpcSupport_ti_syslink_ipc", "ti.grcm"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.grcm")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.grcm.Settings$$instance$static$init", null) ? 1 : 0);
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
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.grcm.RcmServer", "ti.grcm"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.grcm.Settings", "ti.grcm"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.grcm.RcmServer")).bless();
        ((Value.Obj)om.getv("ti.grcm.Settings")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.grcm")).add(pkgV);
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
        RcmServer$$OBJECTS();
        Settings$$OBJECTS();
        RcmServer$$CONSTS();
        Settings$$CONSTS();
        RcmServer$$CREATES();
        Settings$$CREATES();
        RcmServer$$FUNCTIONS();
        Settings$$FUNCTIONS();
        RcmServer$$SIZES();
        Settings$$SIZES();
        RcmServer$$TYPES();
        Settings$$TYPES();
        if (isROV) {
            RcmServer$$ROV();
            Settings$$ROV();
        }//isROV
        $$SINGLETONS();
        RcmServer$$SINGLETONS();
        Settings$$SINGLETONS();
        $$INITIALIZATION();
    }
}
