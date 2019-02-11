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

public class ti_sdo_fc_edmamgr
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
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.edmamgr.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.edmamgr", new Value.Obj("ti.sdo.fc.edmamgr", pkgP));
    }

    void EdmaMgr$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.edmamgr.EdmaMgr.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.edmamgr.EdmaMgr", new Value.Obj("ti.sdo.fc.edmamgr.EdmaMgr", po));
        pkgV.bind("EdmaMgr", vo);
        // decls 
    }

    void EdmaMgr$$CONSTS()
    {
        // module EdmaMgr
    }

    void EdmaMgr$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void EdmaMgr$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void EdmaMgr$$SIZES()
    {
    }

    void EdmaMgr$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/edmamgr/EdmaMgr.xs");
        om.bind("ti.sdo.fc.edmamgr.EdmaMgr$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.edmamgr.EdmaMgr.Module", "ti.sdo.fc.edmamgr");
        po.init("ti.sdo.fc.edmamgr.EdmaMgr.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.fc.edmamgr.EdmaMgr$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.fc.edmamgr.EdmaMgr$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.fc.edmamgr.EdmaMgr$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void EdmaMgr$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.edmamgr.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.edmamgr"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/edmamgr/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.edmamgr"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.edmamgr"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.edmamgr"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.edmamgr"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.edmamgr"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.edmamgr"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.edmamgr", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.edmamgr");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.edmamgr.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.edmamgr'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.fc.edmamgr$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.fc.edmamgr$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.fc.edmamgr$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/edmamgr.a64P',\n");
            sb.append("'lib/release/edmamgr.a64P',\n");
            sb.append("'lib/notrace/edmamgr.a64P',\n");
            sb.append("'lib/debug/edmamgr.a674',\n");
            sb.append("'lib/release/edmamgr.a674',\n");
            sb.append("'lib/notrace/edmamgr.a674',\n");
            sb.append("'lib/debug/edmamgr.ae64P',\n");
            sb.append("'lib/release/edmamgr.ae64P',\n");
            sb.append("'lib/notrace/edmamgr.ae64P',\n");
            sb.append("'lib/debug/edmamgr.ae64T',\n");
            sb.append("'lib/release/edmamgr.ae64T',\n");
            sb.append("'lib/notrace/edmamgr.ae64T',\n");
            sb.append("'lib/debug/edmamgr.ae66',\n");
            sb.append("'lib/release/edmamgr.ae66',\n");
            sb.append("'lib/notrace/edmamgr.ae66',\n");
            sb.append("'lib/debug/edmamgr.ae66e',\n");
            sb.append("'lib/release/edmamgr.ae66e',\n");
            sb.append("'lib/notrace/edmamgr.ae66e',\n");
            sb.append("'lib/debug/edmamgr.ae674',\n");
            sb.append("'lib/release/edmamgr.ae674',\n");
            sb.append("'lib/notrace/edmamgr.ae674',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/edmamgr.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/release/edmamgr.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/notrace/edmamgr.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/debug/edmamgr.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/release/edmamgr.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/notrace/edmamgr.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/debug/edmamgr.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/release/edmamgr.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/notrace/edmamgr.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/debug/edmamgr.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/release/edmamgr.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/notrace/edmamgr.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/debug/edmamgr.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/edmamgr.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/notrace/edmamgr.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/edmamgr.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/release/edmamgr.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/notrace/edmamgr.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/debug/edmamgr.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/edmamgr.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/notrace/edmamgr.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void EdmaMgr$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.edmamgr.EdmaMgr", "ti.sdo.fc.edmamgr");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.edmamgr.EdmaMgr.Module", "ti.sdo.fc.edmamgr");
        vo.init2(po, "ti.sdo.fc.edmamgr.EdmaMgr", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.fc.edmamgr.EdmaMgr$$capsule", "ti.sdo.fc.edmamgr"));
        vo.bind("$package", om.findStrict("ti.sdo.fc.edmamgr", "ti.sdo.fc.edmamgr"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.edmamgr")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.edmamgr.EdmaMgr$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("EdmaMgr", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("EdmaMgr");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.edmamgr.EdmaMgr", "ti.sdo.fc.edmamgr"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.fc.edmamgr.EdmaMgr")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.edmamgr")).add(pkgV);
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
        EdmaMgr$$OBJECTS();
        EdmaMgr$$CONSTS();
        EdmaMgr$$CREATES();
        EdmaMgr$$FUNCTIONS();
        EdmaMgr$$SIZES();
        EdmaMgr$$TYPES();
        if (isROV) {
            EdmaMgr$$ROV();
        }//isROV
        $$SINGLETONS();
        EdmaMgr$$SINGLETONS();
        $$INITIALIZATION();
    }
}
