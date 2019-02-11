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

public class ti_ipc_rpmsg
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
        pkgP = (Proto.Obj)om.bind("ti.ipc.rpmsg.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.ipc.rpmsg", new Value.Obj("ti.ipc.rpmsg", pkgP));
    }

    void Build$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.rpmsg.Build.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.rpmsg.Build", new Value.Obj("ti.ipc.rpmsg.Build", po));
        pkgV.bind("Build", vo);
        // decls 
    }

    void NameMap$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.rpmsg.NameMap.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.rpmsg.NameMap", new Value.Obj("ti.ipc.rpmsg.NameMap", po));
        pkgV.bind("NameMap", vo);
        // decls 
    }

    void RPMessage$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.rpmsg.RPMessage.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.rpmsg.RPMessage", new Value.Obj("ti.ipc.rpmsg.RPMessage", po));
        pkgV.bind("RPMessage", vo);
        // decls 
    }

    void Build$$CONSTS()
    {
        // module Build
    }

    void NameMap$$CONSTS()
    {
        // module NameMap
    }

    void RPMessage$$CONSTS()
    {
        // module RPMessage
    }

    void Build$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NameMap$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void RPMessage$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Build$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Build.getDefs
        fxn = (Proto.Fxn)om.bind("ti.ipc.rpmsg.Build$$getDefs", new Proto.Fxn(om.findStrict("ti.ipc.rpmsg.Build.Module", "ti.ipc.rpmsg"), $$T_Str, 0, 0, false));
    }

    void NameMap$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void RPMessage$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Build$$SIZES()
    {
    }

    void NameMap$$SIZES()
    {
    }

    void RPMessage$$SIZES()
    {
    }

    void Build$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/rpmsg/Build.xs");
        om.bind("ti.ipc.rpmsg.Build$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.rpmsg.Build.Module", "ti.ipc.rpmsg");
        po.init("ti.ipc.rpmsg.Build.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.rpmsg.Build$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.rpmsg.Build$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.rpmsg.Build$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("getDefs", (Proto.Fxn)om.findStrict("ti.ipc.rpmsg.Build$$getDefs", "ti.ipc.rpmsg"), Global.get(cap, "getDefs"));
    }

    void NameMap$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/rpmsg/NameMap.xs");
        om.bind("ti.ipc.rpmsg.NameMap$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.rpmsg.NameMap.Module", "ti.ipc.rpmsg");
        po.init("ti.ipc.rpmsg.NameMap.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.rpmsg.NameMap$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.rpmsg.NameMap$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.rpmsg.NameMap$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void RPMessage$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/rpmsg/RPMessage.xs");
        om.bind("ti.ipc.rpmsg.RPMessage$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.rpmsg.RPMessage.Module", "ti.ipc.rpmsg");
        po.init("ti.ipc.rpmsg.RPMessage.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("numMessageBuffers", Proto.Elm.newCNum("(xdc_UInt)"), 512L, "wh");
        po.addFld("messageBufferSize", Proto.Elm.newCNum("(xdc_UInt)"), 512L, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.rpmsg.RPMessage$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.rpmsg.RPMessage$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.rpmsg.RPMessage$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void Build$$ROV()
    {
    }

    void NameMap$$ROV()
    {
    }

    void RPMessage$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.ipc.rpmsg.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.ipc.rpmsg"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/rpmsg/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.ipc.rpmsg"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.ipc.rpmsg"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.ipc.rpmsg"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.ipc.rpmsg"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.ipc.rpmsg"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.ipc.rpmsg"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.ipc.rpmsg", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.ipc.rpmsg");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.ipc.rpmsg.");
        pkgV.bind("$vers", Global.newArray(1, 0, 1));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.ipc.rpmsg'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.ipc.rpmsg$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.ipc.rpmsg$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.ipc.rpmsg$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/ti.ipc.rpmsg_omap5_smp.aem4',\n");
            sb.append("'lib/debug/ti.ipc.rpmsg_vayu_smp.aem4',\n");
            sb.append("'lib/release/ti.ipc.rpmsg_omap5_smp.aem4',\n");
            sb.append("'lib/release/ti.ipc.rpmsg_vayu_smp.aem4',\n");
            sb.append("'lib/debug/ti.ipc.rpmsg_omap5_smp.aem4f',\n");
            sb.append("'lib/debug/ti.ipc.rpmsg_vayu_smp.aem4f',\n");
            sb.append("'lib/release/ti.ipc.rpmsg_omap5_smp.aem4f',\n");
            sb.append("'lib/release/ti.ipc.rpmsg_vayu_smp.aem4f',\n");
            sb.append("'lib/debug/ti.ipc.rpmsg_tci6638.ae66',\n");
            sb.append("'lib/debug/ti.ipc.rpmsg_vayu.ae66',\n");
            sb.append("'lib/release/ti.ipc.rpmsg_tci6638.ae66',\n");
            sb.append("'lib/release/ti.ipc.rpmsg_vayu.ae66',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/ti.ipc.rpmsg_omap5_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.ipc.rpmsg_vayu_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.ipc.rpmsg_omap5_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.ipc.rpmsg_vayu_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.ipc.rpmsg_omap5_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.ipc.rpmsg_vayu_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.ipc.rpmsg_omap5_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.ipc.rpmsg_vayu_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.ipc.rpmsg_tci6638.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/ti.ipc.rpmsg_vayu.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/ti.ipc.rpmsg_tci6638.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/ti.ipc.rpmsg_vayu.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Build$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.rpmsg.Build", "ti.ipc.rpmsg");
        po = (Proto.Obj)om.findStrict("ti.ipc.rpmsg.Build.Module", "ti.ipc.rpmsg");
        vo.init2(po, "ti.ipc.rpmsg.Build", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.rpmsg.Build$$capsule", "ti.ipc.rpmsg"));
        vo.bind("$package", om.findStrict("ti.ipc.rpmsg", "ti.ipc.rpmsg"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.rpmsg")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ipc.rpmsg.Build$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Build", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Build");
    }

    void NameMap$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.rpmsg.NameMap", "ti.ipc.rpmsg");
        po = (Proto.Obj)om.findStrict("ti.ipc.rpmsg.NameMap.Module", "ti.ipc.rpmsg");
        vo.init2(po, "ti.ipc.rpmsg.NameMap", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.rpmsg.NameMap$$capsule", "ti.ipc.rpmsg"));
        vo.bind("$package", om.findStrict("ti.ipc.rpmsg", "ti.ipc.rpmsg"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.rpmsg")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ipc.rpmsg.NameMap$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("NameMap", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NameMap");
    }

    void RPMessage$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.rpmsg.RPMessage", "ti.ipc.rpmsg");
        po = (Proto.Obj)om.findStrict("ti.ipc.rpmsg.RPMessage.Module", "ti.ipc.rpmsg");
        vo.init2(po, "ti.ipc.rpmsg.RPMessage", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.rpmsg.RPMessage$$capsule", "ti.ipc.rpmsg"));
        vo.bind("$package", om.findStrict("ti.ipc.rpmsg", "ti.ipc.rpmsg"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.rpmsg")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ipc.rpmsg.RPMessage$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./RPMessage.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./RPMessage.xdt");
        pkgV.bind("RPMessage", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("RPMessage");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.rpmsg.Build", "ti.ipc.rpmsg"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.rpmsg.NameMap", "ti.ipc.rpmsg"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.rpmsg.RPMessage", "ti.ipc.rpmsg"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.ipc.rpmsg.Build")).bless();
        ((Value.Obj)om.getv("ti.ipc.rpmsg.NameMap")).bless();
        ((Value.Obj)om.getv("ti.ipc.rpmsg.RPMessage")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.ipc.rpmsg")).add(pkgV);
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
        Build$$OBJECTS();
        NameMap$$OBJECTS();
        RPMessage$$OBJECTS();
        Build$$CONSTS();
        NameMap$$CONSTS();
        RPMessage$$CONSTS();
        Build$$CREATES();
        NameMap$$CREATES();
        RPMessage$$CREATES();
        Build$$FUNCTIONS();
        NameMap$$FUNCTIONS();
        RPMessage$$FUNCTIONS();
        Build$$SIZES();
        NameMap$$SIZES();
        RPMessage$$SIZES();
        Build$$TYPES();
        NameMap$$TYPES();
        RPMessage$$TYPES();
        if (isROV) {
            Build$$ROV();
            NameMap$$ROV();
            RPMessage$$ROV();
        }//isROV
        $$SINGLETONS();
        Build$$SINGLETONS();
        NameMap$$SINGLETONS();
        RPMessage$$SINGLETONS();
        $$INITIALIZATION();
    }
}
