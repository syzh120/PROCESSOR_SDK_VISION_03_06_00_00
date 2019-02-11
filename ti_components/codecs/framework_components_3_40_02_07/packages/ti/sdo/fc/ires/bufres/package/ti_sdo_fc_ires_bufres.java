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

public class ti_sdo_fc_ires_bufres
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.ires.bufres.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.ires.bufres", new Value.Obj("ti.sdo.fc.ires.bufres", pkgP));
    }

    void BUFRES$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.ires.bufres.BUFRES.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.ires.bufres.BUFRES", new Value.Obj("ti.sdo.fc.ires.bufres.BUFRES", po));
        pkgV.bind("BUFRES", vo);
        // decls 
    }

    void BUFRES$$CONSTS()
    {
        // module BUFRES
    }

    void BUFRES$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void BUFRES$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void BUFRES$$SIZES()
    {
    }

    void BUFRES$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/ires/bufres/BUFRES.xs");
        om.bind("ti.sdo.fc.ires.bufres.BUFRES$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.bufres.BUFRES.Module", "ti.sdo.fc.ires.bufres");
        po.init("ti.sdo.fc.ires.bufres.BUFRES.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("persistentAllocFxn", $$T_Str, "DSKT2_allocPersistent", "wh");
        po.addFld("persistentFreeFxn", $$T_Str, "DSKT2_freePersistent", "wh");
        po.addFld("bufBase", new Proto.Adr("xdc_Ptr", "Pv"), null, "wh");
        po.addFld("bufLength", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "wh");
        po.addFld("autoRegister", $$T_Bool, false, "wh");
        po.addFld("enableLog", $$T_Bool, $$UNDEF, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.fc.ires.bufres.BUFRES$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.fc.ires.bufres.BUFRES$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.fc.ires.bufres.BUFRES$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void BUFRES$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.ires.bufres.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.ires.bufres"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/ires/bufres/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.ires.bufres"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.ires.bufres"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.ires.bufres"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.ires.bufres"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.ires.bufres"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.ires.bufres"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.ires.bufres", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.ires.bufres");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.ires.bufres.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.ires.bufres'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.fc.ires.bufres$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.fc.ires.bufres$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.fc.ires.bufres$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/bufres.a64P',\n");
            sb.append("'lib/release/bufres.a64P',\n");
            sb.append("'lib/notrace/bufres.a64P',\n");
            sb.append("'lib/debug/bufres.a674',\n");
            sb.append("'lib/release/bufres.a674',\n");
            sb.append("'lib/notrace/bufres.a674',\n");
            sb.append("'lib/debug/bufres.aem3',\n");
            sb.append("'lib/release/bufres.aem3',\n");
            sb.append("'lib/notrace/bufres.aem3',\n");
            sb.append("'lib/debug/bufres.aem4',\n");
            sb.append("'lib/release/bufres.aem4',\n");
            sb.append("'lib/notrace/bufres.aem4',\n");
            sb.append("'lib/debug/bufres.ae64P',\n");
            sb.append("'lib/release/bufres.ae64P',\n");
            sb.append("'lib/notrace/bufres.ae64P',\n");
            sb.append("'lib/debug/bufres.ae64T',\n");
            sb.append("'lib/release/bufres.ae64T',\n");
            sb.append("'lib/notrace/bufres.ae64T',\n");
            sb.append("'lib/debug/bufres.ae66',\n");
            sb.append("'lib/release/bufres.ae66',\n");
            sb.append("'lib/notrace/bufres.ae66',\n");
            sb.append("'lib/debug/bufres.ae66e',\n");
            sb.append("'lib/release/bufres.ae66e',\n");
            sb.append("'lib/notrace/bufres.ae66e',\n");
            sb.append("'lib/debug/bufres.ae674',\n");
            sb.append("'lib/release/bufres.ae674',\n");
            sb.append("'lib/notrace/bufres.ae674',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/bufres.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/release/bufres.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/notrace/bufres.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/debug/bufres.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/release/bufres.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/notrace/bufres.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/debug/bufres.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/bufres.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/notrace/bufres.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/bufres.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/bufres.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/notrace/bufres.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/bufres.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/release/bufres.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/notrace/bufres.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/debug/bufres.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/release/bufres.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/notrace/bufres.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/debug/bufres.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/bufres.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/notrace/bufres.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/bufres.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/release/bufres.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/notrace/bufres.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/debug/bufres.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/bufres.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/notrace/bufres.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void BUFRES$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.ires.bufres.BUFRES", "ti.sdo.fc.ires.bufres");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.bufres.BUFRES.Module", "ti.sdo.fc.ires.bufres");
        vo.init2(po, "ti.sdo.fc.ires.bufres.BUFRES", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.fc.ires.bufres.BUFRES$$capsule", "ti.sdo.fc.ires.bufres"));
        vo.bind("$package", om.findStrict("ti.sdo.fc.ires.bufres", "ti.sdo.fc.ires.bufres"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.ires.bufres")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.ires.bufres.BUFRES$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./BUFRES.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./BUFRES.xdt");
        pkgV.bind("BUFRES", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("BUFRES");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.ires.bufres.BUFRES", "ti.sdo.fc.ires.bufres"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.fc.ires.bufres.BUFRES")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.ires.bufres")).add(pkgV);
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
        BUFRES$$OBJECTS();
        BUFRES$$CONSTS();
        BUFRES$$CREATES();
        BUFRES$$FUNCTIONS();
        BUFRES$$SIZES();
        BUFRES$$TYPES();
        if (isROV) {
            BUFRES$$ROV();
        }//isROV
        $$SINGLETONS();
        BUFRES$$SINGLETONS();
        $$INITIALIZATION();
    }
}
