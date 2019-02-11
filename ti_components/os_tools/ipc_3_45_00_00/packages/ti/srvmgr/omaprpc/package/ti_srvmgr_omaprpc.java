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

public class ti_srvmgr_omaprpc
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
        pkgP = (Proto.Obj)om.bind("ti.srvmgr.omaprpc.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.srvmgr.omaprpc", new Value.Obj("ti.srvmgr.omaprpc", pkgP));
    }

    void OmapRpc$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.srvmgr.omaprpc.OmapRpc.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.srvmgr.omaprpc.OmapRpc", new Value.Obj("ti.srvmgr.omaprpc.OmapRpc", po));
        pkgV.bind("OmapRpc", vo);
        // decls 
    }

    void OmapRpc$$CONSTS()
    {
        // module OmapRpc
    }

    void OmapRpc$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void OmapRpc$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void OmapRpc$$SIZES()
    {
    }

    void OmapRpc$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/srvmgr/omaprpc/OmapRpc.xs");
        om.bind("ti.srvmgr.omaprpc.OmapRpc$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.srvmgr.omaprpc.OmapRpc.Module", "ti.srvmgr.omaprpc");
        po.init("ti.srvmgr.omaprpc.OmapRpc.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.srvmgr.omaprpc.OmapRpc$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.srvmgr.omaprpc.OmapRpc$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.srvmgr.omaprpc.OmapRpc$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void OmapRpc$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.srvmgr.omaprpc.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.srvmgr.omaprpc"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/srvmgr/omaprpc/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.srvmgr.omaprpc"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.srvmgr.omaprpc"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.srvmgr.omaprpc"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.srvmgr.omaprpc"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.srvmgr.omaprpc"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.srvmgr.omaprpc"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.srvmgr.omaprpc", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.srvmgr.omaprpc");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.srvmgr.omaprpc.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.srvmgr.omaprpc'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.srvmgr.omaprpc$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.srvmgr.omaprpc$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.srvmgr.omaprpc$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/ti.srvmgr.omaprpc_smp.aem4',\n");
            sb.append("'lib/release/ti.srvmgr.omaprpc_smp.aem4',\n");
            sb.append("'lib/debug/ti.srvmgr.omaprpc_smp.aem4f',\n");
            sb.append("'lib/release/ti.srvmgr.omaprpc_smp.aem4f',\n");
            sb.append("'lib/debug/ti.srvmgr.omaprpc.ae66',\n");
            sb.append("'lib/release/ti.srvmgr.omaprpc.ae66',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/ti.srvmgr.omaprpc_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.srvmgr.omaprpc_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.srvmgr.omaprpc_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.srvmgr.omaprpc_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.srvmgr.omaprpc.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/ti.srvmgr.omaprpc.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void OmapRpc$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.srvmgr.omaprpc.OmapRpc", "ti.srvmgr.omaprpc");
        po = (Proto.Obj)om.findStrict("ti.srvmgr.omaprpc.OmapRpc.Module", "ti.srvmgr.omaprpc");
        vo.init2(po, "ti.srvmgr.omaprpc.OmapRpc", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.srvmgr.omaprpc.OmapRpc$$capsule", "ti.srvmgr.omaprpc"));
        vo.bind("$package", om.findStrict("ti.srvmgr.omaprpc", "ti.srvmgr.omaprpc"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.srvmgr.omaprpc")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.srvmgr.omaprpc.OmapRpc$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("OmapRpc", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("OmapRpc");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.srvmgr.omaprpc.OmapRpc", "ti.srvmgr.omaprpc"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.srvmgr.omaprpc.OmapRpc")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.srvmgr.omaprpc")).add(pkgV);
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
        OmapRpc$$OBJECTS();
        OmapRpc$$CONSTS();
        OmapRpc$$CREATES();
        OmapRpc$$FUNCTIONS();
        OmapRpc$$SIZES();
        OmapRpc$$TYPES();
        if (isROV) {
            OmapRpc$$ROV();
        }//isROV
        $$SINGLETONS();
        OmapRpc$$SINGLETONS();
        $$INITIALIZATION();
    }
}
