/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B06
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_ndk_rov
{
    static final String VERS = "@(#) xdc-B06\n";

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
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.ndk.rov.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.ndk.rov", new Value.Obj("ti.ndk.rov", pkgP));
    }

    void Ndk$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.rov.Ndk.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.rov.Ndk", new Value.Obj("ti.ndk.rov.Ndk", po));
        pkgV.bind("Ndk", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.ndk.rov.Ndk$$Ndk_Meta", new Proto.Obj());
        om.bind("ti.ndk.rov.Ndk.Ndk_Meta", new Proto.Str(spo, false));
    }

    void Ndk$$CONSTS()
    {
        // module Ndk
    }

    void Ndk$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Ndk$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Ndk$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Ndk$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/rov/Ndk.xs");
        om.bind("ti.ndk.rov.Ndk$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.rov.Ndk.Module", "ti.ndk.rov");
        po.init("ti.ndk.rov.Ndk.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.ndk.rov"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.ndk.rov"), $$UNDEF, "wh");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.rov.Ndk$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.rov.Ndk$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.ndk.rov.Ndk$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.rov.Ndk$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct Ndk.Ndk_Meta
        po = (Proto.Obj)om.findStrict("ti.ndk.rov.Ndk$$Ndk_Meta", "ti.ndk.rov");
        po.init("ti.ndk.rov.Ndk.Ndk_Meta", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("ipAddr", $$T_Str, $$UNDEF, "w");
    }

    void Ndk$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.rov.Ndk", "ti.ndk.rov");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.ndk.rov.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.ndk.rov"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.ndk.rov", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.ndk.rov");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.ndk.rov.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.ndk.rov'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.ndk.rov$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.ndk.rov$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.ndk.rov$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Ndk$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.rov.Ndk", "ti.ndk.rov");
        po = (Proto.Obj)om.findStrict("ti.ndk.rov.Ndk.Module", "ti.ndk.rov");
        vo.init2(po, "ti.ndk.rov.Ndk", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.rov.Ndk$$capsule", "ti.ndk.rov"));
        vo.bind("$package", om.findStrict("ti.ndk.rov", "ti.ndk.rov"));
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
        vo.bind("Ndk_Meta", om.findStrict("ti.ndk.rov.Ndk.Ndk_Meta", "ti.ndk.rov"));
        tdefs.add(om.findStrict("ti.ndk.rov.Ndk.Ndk_Meta", "ti.ndk.rov"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.rov")).add(vo);
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
        vo.bind("$$fxntab", Global.newArray("ti_ndk_rov_Ndk_Module__startupDone__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Ndk", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Ndk");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.rov.Ndk", "ti.ndk.rov"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.ndk.rov.Ndk", "ti.ndk.rov");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE_DATA"), "viewInitFxn", "viewInitBasic", "structName", "Ndk_Meta")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.ndk.rov.Ndk")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.ndk.rov")).add(pkgV);
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
        Ndk$$OBJECTS();
        Ndk$$CONSTS();
        Ndk$$CREATES();
        Ndk$$FUNCTIONS();
        Ndk$$SIZES();
        Ndk$$TYPES();
        if (isROV) {
            Ndk$$ROV();
        }//isROV
        $$SINGLETONS();
        Ndk$$SINGLETONS();
        $$INITIALIZATION();
    }
}
