/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A54
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_sdo_fc_ires_vicp
{
    static final String VERS = "@(#) xdc-A54\n";

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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.ires.vicp.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.ires.vicp", new Value.Obj("ti.sdo.fc.ires.vicp", pkgP));
    }

    void VICP$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.ires.vicp.VICP.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.ires.vicp.VICP", new Value.Obj("ti.sdo.fc.ires.vicp.VICP", po));
        pkgV.bind("VICP", vo);
        // decls 
    }

    void VICP2$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.ires.vicp.VICP2.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.ires.vicp.VICP2", new Value.Obj("ti.sdo.fc.ires.vicp.VICP2", po));
        pkgV.bind("VICP2", vo);
        // decls 
    }

    void VICP$$CONSTS()
    {
        // module VICP
    }

    void VICP2$$CONSTS()
    {
        // module VICP2
    }

    void VICP$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VICP2$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VICP$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VICP2$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VICP$$SIZES()
    {
    }

    void VICP2$$SIZES()
    {
    }

    void VICP$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.vicp.VICP.Module", "ti.sdo.fc.ires.vicp");
        po.init("ti.sdo.fc.ires.vicp.VICP.Module", om.findStrict("ti.sdo.fc.ires.IRESMAN.Module", "ti.sdo.fc.ires.vicp"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("autoRegister", $$T_Bool, true, "wh");
    }

    void VICP2$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.vicp.VICP2.Module", "ti.sdo.fc.ires.vicp");
        po.init("ti.sdo.fc.ires.vicp.VICP2.Module", om.findStrict("ti.sdo.fc.ires.IRESMAN.Module", "ti.sdo.fc.ires.vicp"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("ipcKeyBase", Proto.Elm.newCNum("(xdc_UInt)"), 0x50434956L, "wh");
        po.addFld("autoRegister", $$T_Bool, true, "wh");
    }

    void VICP$$ROV()
    {
    }

    void VICP2$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.ires.vicp.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.ires.vicp"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/ires/vicp/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.ires.vicp"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.ires.vicp"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.ires.vicp"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.ires.vicp"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.ires.vicp"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.ires.vicp"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.ires.vicp", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.ires.vicp");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.ires.vicp.");
        pkgV.bind("$vers", Global.newArray(1, 0, 1));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.ires.vicp'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.fc.ires.vicp$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.fc.ires.vicp$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.fc.ires.vicp$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/vicp.a64P',\n");
            sb.append("'lib/release/vicp.a64P',\n");
            sb.append("'lib/notrace/vicp.a64P',\n");
            sb.append("'lib/debug/vicp.ae64P',\n");
            sb.append("'lib/release/vicp.ae64P',\n");
            sb.append("'lib/notrace/vicp.ae64P',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/vicp.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/release/vicp.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/notrace/vicp.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/debug/vicp.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/release/vicp.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/notrace/vicp.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void VICP$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.ires.vicp.VICP", "ti.sdo.fc.ires.vicp");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.vicp.VICP.Module", "ti.sdo.fc.ires.vicp");
        vo.init2(po, "ti.sdo.fc.ires.vicp.VICP", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.ires.vicp", "ti.sdo.fc.ires.vicp"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.fc.ires");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.ires.vicp")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.ires.vicp.VICP$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VICP.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VICP.xdt");
        pkgV.bind("VICP", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VICP");
    }

    void VICP2$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.ires.vicp.VICP2", "ti.sdo.fc.ires.vicp");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.vicp.VICP2.Module", "ti.sdo.fc.ires.vicp");
        vo.init2(po, "ti.sdo.fc.ires.vicp.VICP2", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.ires.vicp", "ti.sdo.fc.ires.vicp"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.fc.ires");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.ires.vicp")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.ires.vicp.VICP2$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VICP2.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VICP2.xdt");
        pkgV.bind("VICP2", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VICP2");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.ires.vicp.VICP", "ti.sdo.fc.ires.vicp"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.ires.vicp.VICP2", "ti.sdo.fc.ires.vicp"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.fc.ires.vicp.VICP")).bless();
        ((Value.Obj)om.getv("ti.sdo.fc.ires.vicp.VICP2")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.ires.vicp")).add(pkgV);
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
        VICP$$OBJECTS();
        VICP2$$OBJECTS();
        VICP$$CONSTS();
        VICP2$$CONSTS();
        VICP$$CREATES();
        VICP2$$CREATES();
        VICP$$FUNCTIONS();
        VICP2$$FUNCTIONS();
        VICP$$SIZES();
        VICP2$$SIZES();
        VICP$$TYPES();
        VICP2$$TYPES();
        if (isROV) {
            VICP$$ROV();
            VICP2$$ROV();
        }//isROV
        $$SINGLETONS();
        VICP$$SINGLETONS();
        VICP2$$SINGLETONS();
        $$INITIALIZATION();
    }
}
