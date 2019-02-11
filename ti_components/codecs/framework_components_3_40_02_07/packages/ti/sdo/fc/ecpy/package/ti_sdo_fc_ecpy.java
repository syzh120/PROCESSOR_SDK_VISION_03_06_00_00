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

public class ti_sdo_fc_ecpy
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
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.ecpy.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.ecpy", new Value.Obj("ti.sdo.fc.ecpy", pkgP));
    }

    void ECPY$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.ecpy.ECPY.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.ecpy.ECPY", new Value.Obj("ti.sdo.fc.ecpy.ECPY", po));
        pkgV.bind("ECPY", vo);
        // decls 
    }

    void ECPY$$CONSTS()
    {
        // module ECPY
    }

    void ECPY$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ECPY$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void ECPY$$SIZES()
    {
    }

    void ECPY$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/ecpy/ECPY.xs");
        om.bind("ti.sdo.fc.ecpy.ECPY$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ecpy.ECPY.Module", "ti.sdo.fc.ecpy");
        po.init("ti.sdo.fc.ecpy.ECPY.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("cachedIresMode", $$T_Bool, true, "wh");
        po.addFld("persistentAllocFxn", $$T_Str, null, "wh");
        po.addFld("persistentFreeFxn", $$T_Str, null, "wh");
        po.addFld("scratchAllocFxn", $$T_Str, null, "wh");
        po.addFld("scratchFreeFxn", $$T_Str, null, "wh");
        po.addFld("getScratchIdFxn", $$T_Str, null, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.fc.ecpy.ECPY$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.fc.ecpy.ECPY$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.fc.ecpy.ECPY$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void ECPY$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.ecpy.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.ecpy"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/ecpy/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.ecpy"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.ecpy"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.ecpy"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.ecpy"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.ecpy"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.ecpy"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.ecpy", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.ecpy");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.ecpy.");
        pkgV.bind("$vers", Global.newArray(1, 0, 1));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.ecpy'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.fc.ecpy$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.fc.ecpy$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.fc.ecpy$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/ecpy.a64P',\n");
            sb.append("'lib/release/ecpy.a64P',\n");
            sb.append("'lib/debug/ecpy.a674',\n");
            sb.append("'lib/release/ecpy.a674',\n");
            sb.append("'lib/debug/ecpy.ae64P',\n");
            sb.append("'lib/release/ecpy.ae64P',\n");
            sb.append("'lib/debug/ecpy.ae64T',\n");
            sb.append("'lib/release/ecpy.ae64T',\n");
            sb.append("'lib/debug/ecpy.ae66',\n");
            sb.append("'lib/release/ecpy.ae66',\n");
            sb.append("'lib/debug/ecpy.ae66e',\n");
            sb.append("'lib/release/ecpy.ae66e',\n");
            sb.append("'lib/debug/ecpy.ae674',\n");
            sb.append("'lib/release/ecpy.ae674',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/ecpy.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/release/ecpy.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/debug/ecpy.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/release/ecpy.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/debug/ecpy.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/release/ecpy.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/debug/ecpy.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/release/ecpy.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/debug/ecpy.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/ecpy.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/ecpy.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/release/ecpy.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/debug/ecpy.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/ecpy.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void ECPY$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.ecpy.ECPY", "ti.sdo.fc.ecpy");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ecpy.ECPY.Module", "ti.sdo.fc.ecpy");
        vo.init2(po, "ti.sdo.fc.ecpy.ECPY", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.fc.ecpy.ECPY$$capsule", "ti.sdo.fc.ecpy"));
        vo.bind("$package", om.findStrict("ti.sdo.fc.ecpy", "ti.sdo.fc.ecpy"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.ecpy")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.ecpy.ECPY$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./ECPY.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./ECPY.xdt");
        pkgV.bind("ECPY", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ECPY");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.ecpy.ECPY", "ti.sdo.fc.ecpy"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.fc.ecpy.ECPY")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.ecpy")).add(pkgV);
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
        ECPY$$OBJECTS();
        ECPY$$CONSTS();
        ECPY$$CREATES();
        ECPY$$FUNCTIONS();
        ECPY$$SIZES();
        ECPY$$TYPES();
        if (isROV) {
            ECPY$$ROV();
        }//isROV
        $$SINGLETONS();
        ECPY$$SINGLETONS();
        $$INITIALIZATION();
    }
}
