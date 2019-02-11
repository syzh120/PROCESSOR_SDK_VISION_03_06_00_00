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

public class ti_ipc_family_vayu
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
        pkgP = (Proto.Obj)om.bind("ti.ipc.family.vayu.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.ipc.family.vayu", new Value.Obj("ti.ipc.family.vayu", pkgP));
    }

    void VirtQueue$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.family.vayu.VirtQueue.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.family.vayu.VirtQueue", new Value.Obj("ti.ipc.family.vayu.VirtQueue", po));
        pkgV.bind("VirtQueue", vo);
        // decls 
    }

    void VirtQueue$$CONSTS()
    {
        // module VirtQueue
    }

    void VirtQueue$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VirtQueue$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VirtQueue$$SIZES()
    {
    }

    void VirtQueue$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/family/vayu/VirtQueue.xs");
        om.bind("ti.ipc.family.vayu.VirtQueue$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.family.vayu.VirtQueue.Module", "ti.ipc.family.vayu");
        po.init("ti.ipc.family.vayu.VirtQueue.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.family.vayu.VirtQueue$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.family.vayu.VirtQueue$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.family.vayu.VirtQueue$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void VirtQueue$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.ipc.family.vayu.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.ipc.family.vayu"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/family/vayu/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.ipc.family.vayu"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.ipc.family.vayu"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.ipc.family.vayu"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.ipc.family.vayu"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.ipc.family.vayu"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.ipc.family.vayu"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.ipc.family.vayu", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.ipc.family.vayu");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.ipc.family.vayu.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.ipc.family.vayu'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.ipc.family.vayu$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.ipc.family.vayu$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.ipc.family.vayu$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void VirtQueue$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.family.vayu.VirtQueue", "ti.ipc.family.vayu");
        po = (Proto.Obj)om.findStrict("ti.ipc.family.vayu.VirtQueue.Module", "ti.ipc.family.vayu");
        vo.init2(po, "ti.ipc.family.vayu.VirtQueue", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.family.vayu.VirtQueue$$capsule", "ti.ipc.family.vayu"));
        vo.bind("$package", om.findStrict("ti.ipc.family.vayu", "ti.ipc.family.vayu"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.family.vayu")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ipc.family.vayu.VirtQueue$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VirtQueue.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VirtQueue.xdt");
        pkgV.bind("VirtQueue", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VirtQueue");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.family.vayu.VirtQueue", "ti.ipc.family.vayu"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.ipc.family.vayu.VirtQueue")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.ipc.family.vayu")).add(pkgV);
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
        VirtQueue$$OBJECTS();
        VirtQueue$$CONSTS();
        VirtQueue$$CREATES();
        VirtQueue$$FUNCTIONS();
        VirtQueue$$SIZES();
        VirtQueue$$TYPES();
        if (isROV) {
            VirtQueue$$ROV();
        }//isROV
        $$SINGLETONS();
        VirtQueue$$SINGLETONS();
        $$INITIALIZATION();
    }
}
