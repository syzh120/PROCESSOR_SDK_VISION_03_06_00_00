/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-z44
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_mas_swtools
{
    static final String VERS = "@(#) xdc-z44\n";

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
        pkgP = (Proto.Obj)om.bind("ti.mas.swtools.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.mas.swtools", new Value.Obj("ti.mas.swtools", pkgP));
    }

    void IVersion2$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.mas.swtools.IVersion2.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.mas.swtools.IVersion2", new Value.Obj("ti.mas.swtools.IVersion2", po));
        pkgV.bind("IVersion2", vo);
        // decls 
    }

    void Version$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.mas.swtools.Version.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.mas.swtools.Version", new Value.Obj("ti.mas.swtools.Version", po));
        pkgV.bind("Version", vo);
        // decls 
    }

    void Ccase$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.mas.swtools.Ccase.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.mas.swtools.Ccase", new Value.Obj("ti.mas.swtools.Ccase", po));
        pkgV.bind("Ccase", vo);
        // decls 
    }

    void CommonBld$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.mas.swtools.CommonBld.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.mas.swtools.CommonBld", new Value.Obj("ti.mas.swtools.CommonBld", po));
        pkgV.bind("CommonBld", vo);
        // decls 
    }

    void IVersion$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.mas.swtools.IVersion.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.mas.swtools.IVersion", new Value.Obj("ti.mas.swtools.IVersion", po));
        pkgV.bind("IVersion", vo);
        // decls 
    }

    void IVersion2$$CONSTS()
    {
        // interface IVersion2
        om.bind("ti.mas.swtools.IVersion2.QUALITY_PREALPHA", 0L);
        om.bind("ti.mas.swtools.IVersion2.QUALITY_ALPHA", 1L);
        om.bind("ti.mas.swtools.IVersion2.QUALITY_BETA", 2L);
        om.bind("ti.mas.swtools.IVersion2.QUALITY_GA", 3L);
        om.bind("ti.mas.swtools.IVersion2.BTYPE_STANDARD", 0L);
        om.bind("ti.mas.swtools.IVersion2.BTYPE_ENGINEERING", 1L);
        om.bind("ti.mas.swtools.IVersion2.BTYPE_DEBUG", 2L);
    }

    void Version$$CONSTS()
    {
        // module Version
        om.bind("ti.mas.swtools.Version.MAJOR", 5L);
        om.bind("ti.mas.swtools.Version.MINOR", 0L);
        om.bind("ti.mas.swtools.Version.PATCH", 3L);
        om.bind("ti.mas.swtools.Version.BUILD", 2L);
        om.bind("ti.mas.swtools.Version.QUALITY", 2L);
        om.bind("ti.mas.swtools.Version.BTYPE", 0L);
        om.bind("ti.mas.swtools.Version.WIDTH", 0L);
        om.bind("ti.mas.swtools.Version.PKGSTD", 2L);
    }

    void Ccase$$CONSTS()
    {
        // module Ccase
    }

    void CommonBld$$CONSTS()
    {
        // module CommonBld
    }

    void IVersion$$CONSTS()
    {
        // interface IVersion
    }

    void IVersion2$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Version$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Ccase$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void CommonBld$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVersion$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVersion2$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn IVersion2.getString
        fxn = (Proto.Fxn)om.bind("ti.mas.swtools.IVersion2$$getString", new Proto.Fxn(om.findStrict("ti.mas.swtools.IVersion2.Module", "ti.mas.swtools"), null, 0, -1, false));
    }

    void Version$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Ccase$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void CommonBld$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn CommonBld.parseArgs
        fxn = (Proto.Fxn)om.bind("ti.mas.swtools.CommonBld$$parseArgs", new Proto.Fxn(om.findStrict("ti.mas.swtools.CommonBld.Module", "ti.mas.swtools"), null, 0, -1, false));
        // fxn CommonBld.createLib
        fxn = (Proto.Fxn)om.bind("ti.mas.swtools.CommonBld$$createLib", new Proto.Fxn(om.findStrict("ti.mas.swtools.CommonBld.Module", "ti.mas.swtools"), null, 0, -1, false));
        // fxn CommonBld.createExe
        fxn = (Proto.Fxn)om.bind("ti.mas.swtools.CommonBld$$createExe", new Proto.Fxn(om.findStrict("ti.mas.swtools.CommonBld.Module", "ti.mas.swtools"), null, 0, -1, false));
        // fxn CommonBld.createTar
        fxn = (Proto.Fxn)om.bind("ti.mas.swtools.CommonBld$$createTar", new Proto.Fxn(om.findStrict("ti.mas.swtools.CommonBld.Module", "ti.mas.swtools"), null, 0, -1, false));
        // fxn CommonBld.packageClean
        fxn = (Proto.Fxn)om.bind("ti.mas.swtools.CommonBld$$packageClean", new Proto.Fxn(om.findStrict("ti.mas.swtools.CommonBld.Module", "ti.mas.swtools"), null, 0, -1, false));
        // fxn CommonBld.printUsage
        fxn = (Proto.Fxn)om.bind("ti.mas.swtools.CommonBld$$printUsage", new Proto.Fxn(om.findStrict("ti.mas.swtools.CommonBld.Module", "ti.mas.swtools"), null, 0, -1, false));
        // fxn CommonBld.addUsage
        fxn = (Proto.Fxn)om.bind("ti.mas.swtools.CommonBld$$addUsage", new Proto.Fxn(om.findStrict("ti.mas.swtools.CommonBld.Module", "ti.mas.swtools"), null, 0, -1, false));
    }

    void IVersion$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn IVersion.getString
        fxn = (Proto.Fxn)om.bind("ti.mas.swtools.IVersion$$getString", new Proto.Fxn(om.findStrict("ti.mas.swtools.IVersion.Module", "ti.mas.swtools"), null, 0, -1, false));
    }

    void IVersion2$$SIZES()
    {
    }

    void Version$$SIZES()
    {
    }

    void Ccase$$SIZES()
    {
    }

    void CommonBld$$SIZES()
    {
    }

    void IVersion$$SIZES()
    {
    }

    void IVersion2$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/mas/swtools/IVersion2.xs");
        om.bind("ti.mas.swtools.IVersion2$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.mas.swtools.IVersion2.Module", "ti.mas.swtools");
        po.init("ti.mas.swtools.IVersion2.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("MAJOR", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "rh");
                po.addFld("MINOR", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "rh");
                po.addFld("PATCH", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "rh");
                po.addFld("QUALITY_PREALPHA", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "rh");
                po.addFld("QUALITY_ALPHA", Proto.Elm.newCNum("(xdc_UInt16)"), 1L, "rh");
                po.addFld("QUALITY_BETA", Proto.Elm.newCNum("(xdc_UInt16)"), 2L, "rh");
                po.addFld("QUALITY_GA", Proto.Elm.newCNum("(xdc_UInt16)"), 3L, "rh");
                po.addFld("QUALITY", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "rh");
                po.addFld("BTYPE_STANDARD", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "rh");
                po.addFld("BTYPE_ENGINEERING", Proto.Elm.newCNum("(xdc_UInt16)"), 1L, "rh");
                po.addFld("BTYPE_DEBUG", Proto.Elm.newCNum("(xdc_UInt16)"), 2L, "rh");
                po.addFld("BTYPE", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "rh");
                po.addFld("WIDTH", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "rh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.mas.swtools.IVersion2$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.mas.swtools.IVersion2$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.mas.swtools.IVersion2$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getString");
                if (fxn != null) po.addFxn("getString", (Proto.Fxn)om.findStrict("ti.mas.swtools.IVersion2$$getString", "ti.mas.swtools"), fxn);
    }

    void Version$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.mas.swtools.Version.Module", "ti.mas.swtools");
        po.init("ti.mas.swtools.Version.Module", om.findStrict("ti.mas.swtools.IVersion2.Module", "ti.mas.swtools"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("QUALITY_PREALPHA", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "rh");
                po.addFld("QUALITY_ALPHA", Proto.Elm.newCNum("(xdc_UInt16)"), 1L, "rh");
                po.addFld("QUALITY_BETA", Proto.Elm.newCNum("(xdc_UInt16)"), 2L, "rh");
                po.addFld("QUALITY_GA", Proto.Elm.newCNum("(xdc_UInt16)"), 3L, "rh");
                po.addFld("BTYPE_STANDARD", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "rh");
                po.addFld("BTYPE_ENGINEERING", Proto.Elm.newCNum("(xdc_UInt16)"), 1L, "rh");
                po.addFld("BTYPE_DEBUG", Proto.Elm.newCNum("(xdc_UInt16)"), 2L, "rh");
                po.addFld("MAJOR", Proto.Elm.newCNum("(xdc_UInt16)"), 5L, "rh");
                po.addFld("MINOR", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "rh");
                po.addFld("PATCH", Proto.Elm.newCNum("(xdc_UInt16)"), 3L, "rh");
                po.addFld("BUILD", Proto.Elm.newCNum("(xdc_UInt16)"), 2L, "rh");
                po.addFld("QUALITY", Proto.Elm.newCNum("(xdc_UInt16)"), 2L, "rh");
                po.addFld("BTYPE", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "rh");
                po.addFld("WIDTH", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "rh");
                po.addFld("PKGSTD", Proto.Elm.newCNum("(xdc_UInt16)"), 2L, "rh");
                po.addFxn("getString", (Proto.Fxn)om.findStrict("ti.mas.swtools.IVersion2$$getString", "ti.mas.swtools"), $$UNDEF);
    }

    void Ccase$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.mas.swtools.Ccase.Module", "ti.mas.swtools");
        po.init("ti.mas.swtools.Ccase.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("ignoreList", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"ti.sdoarch.standards.pkg", "ti.xdais"}), "wh");
    }

    void CommonBld$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/mas/swtools/CommonBld.xs");
        om.bind("ti.mas.swtools.CommonBld$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.mas.swtools.CommonBld.Module", "ti.mas.swtools");
        po.init("ti.mas.swtools.CommonBld.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.mas.swtools.CommonBld$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.mas.swtools.CommonBld$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.mas.swtools.CommonBld$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("parseArgs", (Proto.Fxn)om.findStrict("ti.mas.swtools.CommonBld$$parseArgs", "ti.mas.swtools"), Global.get(cap, "parseArgs"));
                po.addFxn("createLib", (Proto.Fxn)om.findStrict("ti.mas.swtools.CommonBld$$createLib", "ti.mas.swtools"), Global.get(cap, "createLib"));
                po.addFxn("createExe", (Proto.Fxn)om.findStrict("ti.mas.swtools.CommonBld$$createExe", "ti.mas.swtools"), Global.get(cap, "createExe"));
                po.addFxn("createTar", (Proto.Fxn)om.findStrict("ti.mas.swtools.CommonBld$$createTar", "ti.mas.swtools"), Global.get(cap, "createTar"));
                po.addFxn("packageClean", (Proto.Fxn)om.findStrict("ti.mas.swtools.CommonBld$$packageClean", "ti.mas.swtools"), Global.get(cap, "packageClean"));
                po.addFxn("printUsage", (Proto.Fxn)om.findStrict("ti.mas.swtools.CommonBld$$printUsage", "ti.mas.swtools"), Global.get(cap, "printUsage"));
                po.addFxn("addUsage", (Proto.Fxn)om.findStrict("ti.mas.swtools.CommonBld$$addUsage", "ti.mas.swtools"), Global.get(cap, "addUsage"));
    }

    void IVersion$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.mas.swtools.IVersion.Module", "ti.mas.swtools");
        po.init("ti.mas.swtools.IVersion.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("MAJOR", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "rh");
                po.addFld("MINOR", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "rh");
                po.addFld("PATCH", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "rh");
                po.addFld("WIDTH", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "rh");
    }

    void IVersion2$$ROV()
    {
    }

    void Version$$ROV()
    {
    }

    void Ccase$$ROV()
    {
    }

    void CommonBld$$ROV()
    {
    }

    void IVersion$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.mas.swtools.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.mas.swtools"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.mas.swtools", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.mas.swtools");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.mas.swtools.");
        pkgV.bind("$vers", Global.newArray("3, 0, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.mas.swtools'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void IVersion2$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.mas.swtools.IVersion2", "ti.mas.swtools");
        po = (Proto.Obj)om.findStrict("ti.mas.swtools.IVersion2.Module", "ti.mas.swtools");
        vo.init2(po, "ti.mas.swtools.IVersion2", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("ti.mas.swtools.IVersion2$$capsule", "ti.mas.swtools"));
        vo.bind("$package", om.findStrict("ti.mas.swtools", "ti.mas.swtools"));
        tdefs.clear();
        proxies.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVersion2", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVersion2");
        vo.seal(null);
    }

    void Version$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.mas.swtools.Version", "ti.mas.swtools");
        po = (Proto.Obj)om.findStrict("ti.mas.swtools.Version.Module", "ti.mas.swtools");
        vo.init2(po, "ti.mas.swtools.Version", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.mas.swtools", "ti.mas.swtools"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.mas.swtools");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.mas.swtools")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.mas.swtools.Version$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Version", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Version");
    }

    void Ccase$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.mas.swtools.Ccase", "ti.mas.swtools");
        po = (Proto.Obj)om.findStrict("ti.mas.swtools.Ccase.Module", "ti.mas.swtools");
        vo.init2(po, "ti.mas.swtools.Ccase", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.mas.swtools", "ti.mas.swtools"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.mas.swtools")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.mas.swtools.Ccase$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Ccase", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Ccase");
    }

    void CommonBld$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.mas.swtools.CommonBld", "ti.mas.swtools");
        po = (Proto.Obj)om.findStrict("ti.mas.swtools.CommonBld.Module", "ti.mas.swtools");
        vo.init2(po, "ti.mas.swtools.CommonBld", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.mas.swtools.CommonBld$$capsule", "ti.mas.swtools"));
        vo.bind("$package", om.findStrict("ti.mas.swtools", "ti.mas.swtools"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.mas.swtools")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.mas.swtools.CommonBld$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("CommonBld", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("CommonBld");
    }

    void IVersion$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.mas.swtools.IVersion", "ti.mas.swtools");
        po = (Proto.Obj)om.findStrict("ti.mas.swtools.IVersion.Module", "ti.mas.swtools");
        vo.init2(po, "ti.mas.swtools.IVersion", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.mas.swtools", "ti.mas.swtools"));
        tdefs.clear();
        proxies.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVersion", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVersion");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.mas.swtools.Version", "ti.mas.swtools"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.mas.swtools.Ccase", "ti.mas.swtools"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.mas.swtools.CommonBld", "ti.mas.swtools"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.mas.swtools.IVersion2")).bless();
        ((Value.Obj)om.getv("ti.mas.swtools.Version")).bless();
        ((Value.Obj)om.getv("ti.mas.swtools.Ccase")).bless();
        ((Value.Obj)om.getv("ti.mas.swtools.CommonBld")).bless();
        ((Value.Obj)om.getv("ti.mas.swtools.IVersion")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.mas.swtools")).add(pkgV);
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
        IVersion2$$OBJECTS();
        Version$$OBJECTS();
        Ccase$$OBJECTS();
        CommonBld$$OBJECTS();
        IVersion$$OBJECTS();
        IVersion2$$CONSTS();
        Version$$CONSTS();
        Ccase$$CONSTS();
        CommonBld$$CONSTS();
        IVersion$$CONSTS();
        IVersion2$$CREATES();
        Version$$CREATES();
        Ccase$$CREATES();
        CommonBld$$CREATES();
        IVersion$$CREATES();
        IVersion2$$FUNCTIONS();
        Version$$FUNCTIONS();
        Ccase$$FUNCTIONS();
        CommonBld$$FUNCTIONS();
        IVersion$$FUNCTIONS();
        IVersion2$$SIZES();
        Version$$SIZES();
        Ccase$$SIZES();
        CommonBld$$SIZES();
        IVersion$$SIZES();
        IVersion2$$TYPES();
        Version$$TYPES();
        Ccase$$TYPES();
        CommonBld$$TYPES();
        IVersion$$TYPES();
        if (isROV) {
            IVersion2$$ROV();
            Version$$ROV();
            Ccase$$ROV();
            CommonBld$$ROV();
            IVersion$$ROV();
        }//isROV
        $$SINGLETONS();
        IVersion2$$SINGLETONS();
        Version$$SINGLETONS();
        Ccase$$SINGLETONS();
        CommonBld$$SINGLETONS();
        IVersion$$SINGLETONS();
        $$INITIALIZATION();
    }
}
