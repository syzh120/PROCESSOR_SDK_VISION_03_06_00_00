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

public class ti_sdo_fc_ires_nullresource
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.ires.nullresource.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.ires.nullresource", new Value.Obj("ti.sdo.fc.ires.nullresource", pkgP));
    }

    void NULLRES$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.ires.nullresource.NULLRES.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.ires.nullresource.NULLRES", new Value.Obj("ti.sdo.fc.ires.nullresource.NULLRES", po));
        pkgV.bind("NULLRES", vo);
        // decls 
    }

    void NULLRES$$CONSTS()
    {
        // module NULLRES
    }

    void NULLRES$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NULLRES$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NULLRES$$SIZES()
    {
    }

    void NULLRES$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.nullresource.NULLRES.Module", "ti.sdo.fc.ires.nullresource");
        po.init("ti.sdo.fc.ires.nullresource.NULLRES.Module", om.findStrict("ti.sdo.fc.ires.IRESMAN.Module", "ti.sdo.fc.ires.nullresource"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("autoRegister", $$T_Bool, false, "wh");
    }

    void NULLRES$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.ires.nullresource.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.ires.nullresource"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/ires/nullresource/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.ires.nullresource"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.ires.nullresource"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.ires.nullresource"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.ires.nullresource"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.ires.nullresource"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.ires.nullresource"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.ires.nullresource", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.ires.nullresource");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.ires.nullresource.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.ires.nullresource'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.fc.ires.nullresource$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.fc.ires.nullresource$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.fc.ires.nullresource$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/nullres.a64P',\n");
            sb.append("'lib/release/nullres.a64P',\n");
            sb.append("'lib/notrace/nullres.a64P',\n");
            sb.append("'lib/debug/nullres.a674',\n");
            sb.append("'lib/release/nullres.a674',\n");
            sb.append("'lib/notrace/nullres.a674',\n");
            sb.append("'lib/debug/nullres.aem3',\n");
            sb.append("'lib/release/nullres.aem3',\n");
            sb.append("'lib/notrace/nullres.aem3',\n");
            sb.append("'lib/debug/nullres.aem4',\n");
            sb.append("'lib/release/nullres.aem4',\n");
            sb.append("'lib/notrace/nullres.aem4',\n");
            sb.append("'lib/debug/nullres.ae64P',\n");
            sb.append("'lib/release/nullres.ae64P',\n");
            sb.append("'lib/notrace/nullres.ae64P',\n");
            sb.append("'lib/debug/nullres.ae64T',\n");
            sb.append("'lib/release/nullres.ae64T',\n");
            sb.append("'lib/notrace/nullres.ae64T',\n");
            sb.append("'lib/debug/nullres.ae66',\n");
            sb.append("'lib/release/nullres.ae66',\n");
            sb.append("'lib/notrace/nullres.ae66',\n");
            sb.append("'lib/debug/nullres.ae66e',\n");
            sb.append("'lib/release/nullres.ae66e',\n");
            sb.append("'lib/notrace/nullres.ae66e',\n");
            sb.append("'lib/debug/nullres.ae674',\n");
            sb.append("'lib/release/nullres.ae674',\n");
            sb.append("'lib/notrace/nullres.ae674',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/nullres.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/release/nullres.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/notrace/nullres.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/debug/nullres.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/release/nullres.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/notrace/nullres.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/debug/nullres.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/nullres.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/notrace/nullres.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/nullres.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/nullres.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/notrace/nullres.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/nullres.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/release/nullres.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/notrace/nullres.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/debug/nullres.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/release/nullres.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/notrace/nullres.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/debug/nullres.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/nullres.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/notrace/nullres.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/nullres.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/release/nullres.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/notrace/nullres.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/debug/nullres.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/nullres.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/notrace/nullres.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void NULLRES$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.ires.nullresource.NULLRES", "ti.sdo.fc.ires.nullresource");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.nullresource.NULLRES.Module", "ti.sdo.fc.ires.nullresource");
        vo.init2(po, "ti.sdo.fc.ires.nullresource.NULLRES", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.ires.nullresource", "ti.sdo.fc.ires.nullresource"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.ires.nullresource")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.ires.nullresource.NULLRES$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("NULLRES", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NULLRES");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.ires.nullresource.NULLRES", "ti.sdo.fc.ires.nullresource"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.fc.ires.nullresource.NULLRES")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.ires.nullresource")).add(pkgV);
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
        NULLRES$$OBJECTS();
        NULLRES$$CONSTS();
        NULLRES$$CREATES();
        NULLRES$$FUNCTIONS();
        NULLRES$$SIZES();
        NULLRES$$TYPES();
        if (isROV) {
            NULLRES$$ROV();
        }//isROV
        $$SINGLETONS();
        NULLRES$$SINGLETONS();
        $$INITIALIZATION();
    }
}
