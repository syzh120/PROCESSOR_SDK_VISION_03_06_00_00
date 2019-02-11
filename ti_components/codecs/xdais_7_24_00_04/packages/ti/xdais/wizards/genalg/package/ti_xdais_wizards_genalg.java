/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y13
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_xdais_wizards_genalg
{
    static final String VERS = "@(#) xdc-y13\n";

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
        Global.callFxn("loadPackage", xdcO, "xdc.tools.sg.widgets");
        Global.callFxn("loadPackage", xdcO, "xdc.tools");
        Global.callFxn("loadPackage", xdcO, "xdc.tools.mkpkg");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.xdais.wizards.genalg.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.xdais.wizards.genalg", new Value.Obj("ti.xdais.wizards.genalg", pkgP));
    }

    void Main$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.wizards.genalg.Main.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.wizards.genalg.Main", new Value.Obj("ti.xdais.wizards.genalg.Main", po));
        pkgV.bind("Main", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.xdais.wizards.genalg.Main.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.xdais.wizards.genalg.Main$$Object", new Proto.Obj());
        Object objP = om.bind("ti.xdais.wizards.genalg.Main.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.xdais.wizards.genalg.Main$$Params", new Proto.Obj());
        om.bind("ti.xdais.wizards.genalg.Main.Params", new Proto.Str(po, true));
    }

    void Gui$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.wizards.genalg.Gui.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.wizards.genalg.Gui", new Value.Obj("ti.xdais.wizards.genalg.Gui", po));
        pkgV.bind("Gui", vo);
        // decls 
    }

    void Main$$CONSTS()
    {
        // module Main
    }

    void Gui$$CONSTS()
    {
        // module Gui
    }

    void Main$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.xdais.wizards.genalg.Main$$create", new Proto.Fxn(om.findStrict("ti.xdais.wizards.genalg.Main.Module", "ti.xdais.wizards.genalg"), om.findStrict("ti.xdais.wizards.genalg.Main.Instance", "ti.xdais.wizards.genalg"), 1, 0, false));
                fxn.addArg(0, "__params", (Proto)om.findStrict("ti.xdais.wizards.genalg.Main.Params", "ti.xdais.wizards.genalg"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$xdais$wizards$genalg$Main$$create = function( __params ) {\n");
            sb.append("var __mod = xdc.om['ti.xdais.wizards.genalg.Main'];\n");
            sb.append("var __inst = xdc.om['ti.xdais.wizards.genalg.Main.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.xdais.wizards.genalg']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.xdais.wizards.genalg.Main$$construct", new Proto.Fxn(om.findStrict("ti.xdais.wizards.genalg.Main.Module", "ti.xdais.wizards.genalg"), null, 2, 0, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.xdais.wizards.genalg.Main$$Object", "ti.xdais.wizards.genalg"), null);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.xdais.wizards.genalg.Main.Params", "ti.xdais.wizards.genalg"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$xdais$wizards$genalg$Main$$construct = function( __obj, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.xdais.wizards.genalg.Main'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Gui$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Main$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Gui$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Gui.createPartControl
        fxn = (Proto.Fxn)om.bind("ti.xdais.wizards.genalg.Gui$$createPartControl", new Proto.Fxn(om.findStrict("ti.xdais.wizards.genalg.Gui.Module", "ti.xdais.wizards.genalg"), null, 0, -1, false));
    }

    void Main$$SIZES()
    {
    }

    void Gui$$SIZES()
    {
    }

    void Main$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/wizards/genalg/Main.xs");
        om.bind("ti.xdais.wizards.genalg.Main$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.xdais.wizards.genalg.Main.Module", "ti.xdais.wizards.genalg");
        po.init("ti.xdais.wizards.genalg.Main.Module", om.findStrict("xdc.tools.ICmd.Module", "ti.xdais.wizards.genalg"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("usage", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"[-g] [--cgtools <dir>] [--gcccgtools <dir>] [--m3cgtools <dir>] [-f <file> | --xml <file>] [-d <destination dir>]"}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.xdais.wizards.genalg.Main$$create", "ti.xdais.wizards.genalg"), Global.get("ti$xdais$wizards$genalg$Main$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.xdais.wizards.genalg.Main$$construct", "ti.xdais.wizards.genalg"), Global.get("ti$xdais$wizards$genalg$Main$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.xdais.wizards.genalg.Main$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.xdais.wizards.genalg.Main$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.xdais.wizards.genalg.Main$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.xdais.wizards.genalg.Main$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "main");
                if (fxn != null) po.addFxn("main", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$main", "ti.xdais.wizards.genalg"), fxn);
                fxn = Global.get(cap, "exec");
                if (fxn != null) po.addFxn("exec", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$exec", "ti.xdais.wizards.genalg"), fxn);
        po = (Proto.Obj)om.findStrict("ti.xdais.wizards.genalg.Main.Instance", "ti.xdais.wizards.genalg");
        po.init("ti.xdais.wizards.genalg.Main.Instance", om.findStrict("xdc.tools.ICmd.Instance", "ti.xdais.wizards.genalg"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("gui", $$T_Bool, false, "wh");
        po.addFld("cgTools", $$T_Str, null, "wh");
        po.addFld("gccCgTools", $$T_Str, null, "wh");
        po.addFld("m3cgTools", $$T_Str, null, "wh");
        po.addFld("xmlFile", $$T_Str, null, "wh");
        po.addFld("destDir", $$T_Str, null, "wh");
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$run", "ti.xdais.wizards.genalg"), fxn);
        po = (Proto.Obj)om.findStrict("ti.xdais.wizards.genalg.Main$$Params", "ti.xdais.wizards.genalg");
        po.init("ti.xdais.wizards.genalg.Main.Params", om.findStrict("xdc.tools.ICmd$$Params", "ti.xdais.wizards.genalg"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("gui", $$T_Bool, false, "wh");
        po.addFld("cgTools", $$T_Str, null, "wh");
        po.addFld("gccCgTools", $$T_Str, null, "wh");
        po.addFld("m3cgTools", $$T_Str, null, "wh");
        po.addFld("xmlFile", $$T_Str, null, "wh");
        po.addFld("destDir", $$T_Str, null, "wh");
        po = (Proto.Obj)om.findStrict("ti.xdais.wizards.genalg.Main$$Object", "ti.xdais.wizards.genalg");
        po.init("ti.xdais.wizards.genalg.Main.Object", om.findStrict("ti.xdais.wizards.genalg.Main.Instance", "ti.xdais.wizards.genalg"));
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$run", "ti.xdais.wizards.genalg"), fxn);
    }

    void Gui$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/wizards/genalg/Gui.xs");
        om.bind("ti.xdais.wizards.genalg.Gui$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.xdais.wizards.genalg.Gui.Module", "ti.xdais.wizards.genalg");
        po.init("ti.xdais.wizards.genalg.Gui.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.xdais.wizards.genalg.Gui$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.xdais.wizards.genalg.Gui$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.xdais.wizards.genalg.Gui$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("createPartControl", (Proto.Fxn)om.findStrict("ti.xdais.wizards.genalg.Gui$$createPartControl", "ti.xdais.wizards.genalg"), Global.get(cap, "createPartControl"));
    }

    void Main$$ROV()
    {
    }

    void Gui$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.xdais.wizards.genalg.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.xdais.wizards.genalg"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.xdais.wizards.genalg", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.xdais.wizards.genalg");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.xdais.wizards.genalg.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.tools.sg.widgets", Global.newArray()));
        imports.add(Global.newArray("xdc.tools", Global.newArray()));
        imports.add(Global.newArray("xdc.tools.mkpkg", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.xdais.wizards.genalg'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Main$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.wizards.genalg.Main", "ti.xdais.wizards.genalg");
        po = (Proto.Obj)om.findStrict("ti.xdais.wizards.genalg.Main.Module", "ti.xdais.wizards.genalg");
        vo.init2(po, "ti.xdais.wizards.genalg.Main", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.xdais.wizards.genalg.Main$$capsule", "ti.xdais.wizards.genalg"));
        vo.bind("Instance", om.findStrict("ti.xdais.wizards.genalg.Main.Instance", "ti.xdais.wizards.genalg"));
        vo.bind("Params", om.findStrict("ti.xdais.wizards.genalg.Main.Params", "ti.xdais.wizards.genalg"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.xdais.wizards.genalg.Main.Params", "ti.xdais.wizards.genalg")).newInstance());
        vo.bind("$package", om.findStrict("ti.xdais.wizards.genalg", "ti.xdais.wizards.genalg"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.tools");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.wizards.genalg")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.wizards.genalg.Main$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.xdais.wizards.genalg.Main.Object", "ti.xdais.wizards.genalg"));
        pkgV.bind("Main", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Main");
    }

    void Gui$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.wizards.genalg.Gui", "ti.xdais.wizards.genalg");
        po = (Proto.Obj)om.findStrict("ti.xdais.wizards.genalg.Gui.Module", "ti.xdais.wizards.genalg");
        vo.init2(po, "ti.xdais.wizards.genalg.Gui", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.xdais.wizards.genalg.Gui$$capsule", "ti.xdais.wizards.genalg"));
        vo.bind("$package", om.findStrict("ti.xdais.wizards.genalg", "ti.xdais.wizards.genalg"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.wizards.genalg")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.wizards.genalg.Gui$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Gui", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Gui");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.wizards.genalg.Main", "ti.xdais.wizards.genalg"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.wizards.genalg.Gui", "ti.xdais.wizards.genalg"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.xdais.wizards.genalg.Main")).bless();
        ((Value.Obj)om.getv("ti.xdais.wizards.genalg.Gui")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.xdais.wizards.genalg")).add(pkgV);
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
        Main$$OBJECTS();
        Gui$$OBJECTS();
        Main$$CONSTS();
        Gui$$CONSTS();
        Main$$CREATES();
        Gui$$CREATES();
        Main$$FUNCTIONS();
        Gui$$FUNCTIONS();
        Main$$SIZES();
        Gui$$SIZES();
        Main$$TYPES();
        Gui$$TYPES();
        if (isROV) {
            Main$$ROV();
            Gui$$ROV();
        }//isROV
        $$SINGLETONS();
        Main$$SINGLETONS();
        Gui$$SINGLETONS();
        $$INITIALIZATION();
    }
}
