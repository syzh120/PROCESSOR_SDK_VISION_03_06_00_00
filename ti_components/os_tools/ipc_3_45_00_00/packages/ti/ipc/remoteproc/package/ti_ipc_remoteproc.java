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

public class ti_ipc_remoteproc
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
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.ipc.remoteproc.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.ipc.remoteproc", new Value.Obj("ti.ipc.remoteproc", pkgP));
    }

    void Resource$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.remoteproc.Resource.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.remoteproc.Resource", new Value.Obj("ti.ipc.remoteproc.Resource", po));
        pkgV.bind("Resource", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.ipc.remoteproc.Resource$$RscTable", new Proto.Obj());
        om.bind("ti.ipc.remoteproc.Resource.RscTable", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.ipc.remoteproc.Resource$$MemEntry", new Proto.Obj());
        om.bind("ti.ipc.remoteproc.Resource.MemEntry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.ipc.remoteproc.Resource$$Module_State", new Proto.Obj());
        om.bind("ti.ipc.remoteproc.Resource.Module_State", new Proto.Str(spo, false));
    }

    void Resource$$CONSTS()
    {
        // module Resource
        om.bind("ti.ipc.remoteproc.Resource.S_SUCCESS", 0L);
        om.bind("ti.ipc.remoteproc.Resource.E_NOTFOUND", Global.eval("-1"));
        om.bind("ti.ipc.remoteproc.Resource.virtToPhys", new Extern("ti_ipc_remoteproc_Resource_virtToPhys__E", "xdc_Int(*)(xdc_UInt32,xdc_UInt32*)", true, false));
        om.bind("ti.ipc.remoteproc.Resource.physToVirt", new Extern("ti_ipc_remoteproc_Resource_physToVirt__E", "xdc_Int(*)(xdc_UInt32,xdc_UInt32*)", true, false));
        om.bind("ti.ipc.remoteproc.Resource.getTraceBufPtr", new Extern("ti_ipc_remoteproc_Resource_getTraceBufPtr__E", "xdc_Ptr(*)(xdc_Void)", true, false));
        om.bind("ti.ipc.remoteproc.Resource.getVdevStatus", new Extern("ti_ipc_remoteproc_Resource_getVdevStatus__E", "xdc_Char(*)(xdc_UInt32)", true, false));
        om.bind("ti.ipc.remoteproc.Resource.getVringDA", new Extern("ti_ipc_remoteproc_Resource_getVringDA__E", "xdc_Ptr(*)(xdc_UInt32)", true, false));
        om.bind("ti.ipc.remoteproc.Resource.init", new Extern("ti_ipc_remoteproc_Resource_init__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.ipc.remoteproc.Resource.getMemEntry", new Extern("ti_ipc_remoteproc_Resource_getMemEntry__I", "ti_ipc_remoteproc_Resource_MemEntry*(*)(xdc_UInt)", true, false));
    }

    void Resource$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Resource$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Resource$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.ipc.remoteproc.Resource.RscTable", "ti.ipc.remoteproc");
        sizes.clear();
        sizes.add(Global.newArray("ver", "UInt32"));
        sizes.add(Global.newArray("num", "UInt32"));
        sizes.add(Global.newArray("reserved", "A2;UInt32"));
        sizes.add(Global.newArray("offset", "A1;UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.ipc.remoteproc.Resource.RscTable']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.ipc.remoteproc.Resource.RscTable']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.ipc.remoteproc.Resource.RscTable'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.ipc.remoteproc.Resource.MemEntry", "ti.ipc.remoteproc");
        sizes.clear();
        sizes.add(Global.newArray("type", "UInt32"));
        sizes.add(Global.newArray("da", "UInt32"));
        sizes.add(Global.newArray("pa", "UInt32"));
        sizes.add(Global.newArray("len", "UInt32"));
        sizes.add(Global.newArray("flags", "UInt32"));
        sizes.add(Global.newArray("reserved", "UInt32"));
        sizes.add(Global.newArray("name", "A32;TChar"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.ipc.remoteproc.Resource.MemEntry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.ipc.remoteproc.Resource.MemEntry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.ipc.remoteproc.Resource.MemEntry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.ipc.remoteproc.Resource.Module_State", "ti.ipc.remoteproc");
        sizes.clear();
        sizes.add(Global.newArray("pTable", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.ipc.remoteproc.Resource.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.ipc.remoteproc.Resource.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.ipc.remoteproc.Resource.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Resource$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/remoteproc/Resource.xs");
        om.bind("ti.ipc.remoteproc.Resource$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.remoteproc.Resource.Module", "ti.ipc.remoteproc");
        po.init("ti.ipc.remoteproc.Resource.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.ipc.remoteproc"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("S_SUCCESS", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("E_NOTFOUND", Proto.Elm.newCNum("(xdc_Int)"), Global.eval("-1"), "rh");
        if (isCFG) {
            po.addFld("loadAddr", Proto.Elm.newCNum("(xdc_UInt)"), 0x3000L, "wh");
            po.addFld("loadSegment", $$T_Str, $$UNDEF, "wh");
            po.addFld("traceOnly", $$T_Bool, false, "wh");
            po.addFld("customTable", $$T_Bool, false, "wh");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.remoteproc.Resource$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.remoteproc.Resource$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.ipc.remoteproc.Resource$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.remoteproc.Resource$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct Resource.RscTable
        po = (Proto.Obj)om.findStrict("ti.ipc.remoteproc.Resource$$RscTable", "ti.ipc.remoteproc");
        po.init("ti.ipc.remoteproc.Resource.RscTable", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ver", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("num", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("reserved", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(2L)), $$DEFAULT, "w");
                po.addFld("offset", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt32)"), false, xdc.services.intern.xsr.Enum.intValue(1L)), $$DEFAULT, "w");
        // struct Resource.MemEntry
        po = (Proto.Obj)om.findStrict("ti.ipc.remoteproc.Resource$$MemEntry", "ti.ipc.remoteproc");
        po.init("ti.ipc.remoteproc.Resource.MemEntry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("type", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("da", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("pa", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("len", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("flags", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("reserved", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("name", new Proto.Arr(Proto.Elm.newCNum("(xdc_Char)"), false, xdc.services.intern.xsr.Enum.intValue(32L)), $$DEFAULT, "w");
        // struct Resource.Module_State
        po = (Proto.Obj)om.findStrict("ti.ipc.remoteproc.Resource$$Module_State", "ti.ipc.remoteproc");
        po.init("ti.ipc.remoteproc.Resource.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("pTable", new Proto.Adr("ti_ipc_remoteproc_Resource_RscTable*", "PS"), $$UNDEF, "w");
    }

    void Resource$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.remoteproc.Resource", "ti.ipc.remoteproc");
        vo.bind("RscTable$fetchDesc", Global.newObject("type", "ti.ipc.remoteproc.Resource.RscTable", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.ipc.remoteproc.Resource$$RscTable", "ti.ipc.remoteproc");
        vo.bind("MemEntry$fetchDesc", Global.newObject("type", "ti.ipc.remoteproc.Resource.MemEntry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.ipc.remoteproc.Resource$$MemEntry", "ti.ipc.remoteproc");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.ipc.remoteproc.Resource.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.ipc.remoteproc.Resource$$Module_State", "ti.ipc.remoteproc");
        po.bind("pTable$fetchDesc", Global.newObject("type", "ti.ipc.remoteproc.Resource.RscTable", "isScalar", false));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.ipc.remoteproc.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.ipc.remoteproc"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/remoteproc/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.ipc.remoteproc"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.ipc.remoteproc"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.ipc.remoteproc"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.ipc.remoteproc"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.ipc.remoteproc"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.ipc.remoteproc"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.ipc.remoteproc", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.ipc.remoteproc");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.ipc.remoteproc.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.ipc.remoteproc'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.ipc.remoteproc$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.ipc.remoteproc$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.ipc.remoteproc$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Resource$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.remoteproc.Resource", "ti.ipc.remoteproc");
        po = (Proto.Obj)om.findStrict("ti.ipc.remoteproc.Resource.Module", "ti.ipc.remoteproc");
        vo.init2(po, "ti.ipc.remoteproc.Resource", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.remoteproc.Resource$$capsule", "ti.ipc.remoteproc"));
        vo.bind("$package", om.findStrict("ti.ipc.remoteproc", "ti.ipc.remoteproc"));
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
        vo.bind("RscTable", om.findStrict("ti.ipc.remoteproc.Resource.RscTable", "ti.ipc.remoteproc"));
        tdefs.add(om.findStrict("ti.ipc.remoteproc.Resource.RscTable", "ti.ipc.remoteproc"));
        vo.bind("MemEntry", om.findStrict("ti.ipc.remoteproc.Resource.MemEntry", "ti.ipc.remoteproc"));
        tdefs.add(om.findStrict("ti.ipc.remoteproc.Resource.MemEntry", "ti.ipc.remoteproc"));
        vo.bind("Module_State", om.findStrict("ti.ipc.remoteproc.Resource.Module_State", "ti.ipc.remoteproc"));
        tdefs.add(om.findStrict("ti.ipc.remoteproc.Resource.Module_State", "ti.ipc.remoteproc"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.remoteproc")).add(vo);
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
        vo.bind("virtToPhys", om.findStrict("ti.ipc.remoteproc.Resource.virtToPhys", "ti.ipc.remoteproc"));
        vo.bind("physToVirt", om.findStrict("ti.ipc.remoteproc.Resource.physToVirt", "ti.ipc.remoteproc"));
        vo.bind("getTraceBufPtr", om.findStrict("ti.ipc.remoteproc.Resource.getTraceBufPtr", "ti.ipc.remoteproc"));
        vo.bind("getVdevStatus", om.findStrict("ti.ipc.remoteproc.Resource.getVdevStatus", "ti.ipc.remoteproc"));
        vo.bind("getVringDA", om.findStrict("ti.ipc.remoteproc.Resource.getVringDA", "ti.ipc.remoteproc"));
        vo.bind("init", om.findStrict("ti.ipc.remoteproc.Resource.init", "ti.ipc.remoteproc"));
        vo.bind("getMemEntry", om.findStrict("ti.ipc.remoteproc.Resource.getMemEntry", "ti.ipc.remoteproc"));
        vo.bind("$$fxntab", Global.newArray("ti_ipc_remoteproc_Resource_Module__startupDone__E", "ti_ipc_remoteproc_Resource_virtToPhys__E", "ti_ipc_remoteproc_Resource_physToVirt__E", "ti_ipc_remoteproc_Resource_getTraceBufPtr__E", "ti_ipc_remoteproc_Resource_getVdevStatus__E", "ti_ipc_remoteproc_Resource_getVringDA__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Resource.xdt");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./Resource.xdt");
        pkgV.bind("Resource", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Resource");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.remoteproc.Resource", "ti.ipc.remoteproc"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.ipc.remoteproc.Resource")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.ipc.remoteproc")).add(pkgV);
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
        Resource$$OBJECTS();
        Resource$$CONSTS();
        Resource$$CREATES();
        Resource$$FUNCTIONS();
        Resource$$SIZES();
        Resource$$TYPES();
        if (isROV) {
            Resource$$ROV();
        }//isROV
        $$SINGLETONS();
        Resource$$SINGLETONS();
        $$INITIALIZATION();
    }
}
