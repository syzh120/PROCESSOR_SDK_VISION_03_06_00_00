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

public class ti_xdais_dm_examples_universal_copy
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
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.xdais.dm.examples.universal_copy.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.xdais.dm.examples.universal_copy", new Value.Obj("ti.xdais.dm.examples.universal_copy", pkgP));
    }

    void UniversalCopy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.dm.examples.universal_copy.UniversalCopy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.dm.examples.universal_copy.UniversalCopy", new Value.Obj("ti.xdais.dm.examples.universal_copy.UniversalCopy", po));
        pkgV.bind("UniversalCopy", vo);
        // decls 
    }

    void UniversalCopy$$CONSTS()
    {
        // module UniversalCopy
    }

    void UniversalCopy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void UniversalCopy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void UniversalCopy$$SIZES()
    {
    }

    void UniversalCopy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.xdais.dm.examples.universal_copy.UniversalCopy.Module", "ti.xdais.dm.examples.universal_copy");
        po.init("ti.xdais.dm.examples.universal_copy.UniversalCopy.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("enableTrace", $$T_Bool, false, "wh");
    }

    void UniversalCopy$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.xdais.dm.examples.universal_copy.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.xdais.dm.examples.universal_copy"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/dm/examples/universal_copy/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.xdais.dm.examples.universal_copy"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.xdais.dm.examples.universal_copy"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.xdais.dm.examples.universal_copy"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.xdais.dm.examples.universal_copy"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.xdais.dm.examples.universal_copy"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.xdais.dm.examples.universal_copy"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.xdais.dm.examples.universal_copy", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.xdais.dm.examples.universal_copy");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.xdais.dm.examples.universal_copy.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.xdais.dm.examples.universal_copy'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/universal_copy.a64P',\n");
            sb.append("'lib/debug/universal_copy_trace.a64P',\n");
            sb.append("'lib/release/universal_copy.a64P',\n");
            sb.append("'lib/release/universal_copy_trace.a64P',\n");
            sb.append("'lib/debug/universal_copy.ae64P',\n");
            sb.append("'lib/debug/universal_copy_trace.ae64P',\n");
            sb.append("'lib/release/universal_copy.ae64P',\n");
            sb.append("'lib/release/universal_copy_trace.ae64P',\n");
            sb.append("'lib/debug/universal_copy.a28L',\n");
            sb.append("'lib/debug/universal_copy_trace.a28L',\n");
            sb.append("'lib/release/universal_copy.a28L',\n");
            sb.append("'lib/release/universal_copy_trace.a28L',\n");
            sb.append("'lib/debug/universal_copy.a674',\n");
            sb.append("'lib/debug/universal_copy_trace.a674',\n");
            sb.append("'lib/release/universal_copy.a674',\n");
            sb.append("'lib/release/universal_copy_trace.a674',\n");
            sb.append("'lib/debug/universal_copy.ae674',\n");
            sb.append("'lib/debug/universal_copy_trace.ae674',\n");
            sb.append("'lib/release/universal_copy.ae674',\n");
            sb.append("'lib/release/universal_copy_trace.ae674',\n");
            sb.append("'lib/debug/universal_copy.ae66',\n");
            sb.append("'lib/debug/universal_copy_trace.ae66',\n");
            sb.append("'lib/release/universal_copy.ae66',\n");
            sb.append("'lib/release/universal_copy_trace.ae66',\n");
            sb.append("'lib/debug/universal_copy.ae64T',\n");
            sb.append("'lib/debug/universal_copy_trace.ae64T',\n");
            sb.append("'lib/release/universal_copy.ae64T',\n");
            sb.append("'lib/release/universal_copy_trace.ae64T',\n");
            sb.append("'lib/debug/universal_copy.aem3',\n");
            sb.append("'lib/debug/universal_copy_trace.aem3',\n");
            sb.append("'lib/release/universal_copy.aem3',\n");
            sb.append("'lib/release/universal_copy_trace.aem3',\n");
            sb.append("'lib/debug/universal_copy.a86U',\n");
            sb.append("'lib/debug/universal_copy_trace.a86U',\n");
            sb.append("'lib/release/universal_copy.a86U',\n");
            sb.append("'lib/release/universal_copy_trace.a86U',\n");
            sb.append("'lib/debug/universal_copy.av5T',\n");
            sb.append("'lib/debug/universal_copy_trace.av5T',\n");
            sb.append("'lib/release/universal_copy.av5T',\n");
            sb.append("'lib/release/universal_copy_trace.av5T',\n");
            sb.append("'lib/debug/universal_copy.av6',\n");
            sb.append("'lib/debug/universal_copy_trace.av6',\n");
            sb.append("'lib/release/universal_copy.av6',\n");
            sb.append("'lib/release/universal_copy_trace.av6',\n");
            sb.append("'lib/debug/universal_copy.av7A',\n");
            sb.append("'lib/debug/universal_copy_trace.av7A',\n");
            sb.append("'lib/release/universal_copy.av7A',\n");
            sb.append("'lib/release/universal_copy_trace.av7A',\n");
            sb.append("'lib/debug/universal_copy.a470uC',\n");
            sb.append("'lib/debug/universal_copy_trace.a470uC',\n");
            sb.append("'lib/release/universal_copy.a470uC',\n");
            sb.append("'lib/release/universal_copy_trace.a470uC',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/universal_copy.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/debug/universal_copy_trace.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/release/universal_copy.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/release/universal_copy_trace.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/debug/universal_copy.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/debug/universal_copy_trace.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/release/universal_copy.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/release/universal_copy_trace.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/debug/universal_copy.a28L', {target: 'ti.targets.C28_large', suffix: '28L'}],\n");
            sb.append("['lib/debug/universal_copy_trace.a28L', {target: 'ti.targets.C28_large', suffix: '28L'}],\n");
            sb.append("['lib/release/universal_copy.a28L', {target: 'ti.targets.C28_large', suffix: '28L'}],\n");
            sb.append("['lib/release/universal_copy_trace.a28L', {target: 'ti.targets.C28_large', suffix: '28L'}],\n");
            sb.append("['lib/debug/universal_copy.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/debug/universal_copy_trace.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/release/universal_copy.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/release/universal_copy_trace.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/debug/universal_copy.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/universal_copy_trace.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/universal_copy.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/universal_copy_trace.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/universal_copy.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/universal_copy_trace.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/universal_copy.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/universal_copy_trace.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/universal_copy.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/debug/universal_copy_trace.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/release/universal_copy.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/release/universal_copy_trace.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/debug/universal_copy.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/universal_copy_trace.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/universal_copy.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/universal_copy_trace.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/universal_copy.a86U', {target: 'gnu.targets.Linux86', suffix: '86U'}],\n");
            sb.append("['lib/debug/universal_copy_trace.a86U', {target: 'gnu.targets.Linux86', suffix: '86U'}],\n");
            sb.append("['lib/release/universal_copy.a86U', {target: 'gnu.targets.Linux86', suffix: '86U'}],\n");
            sb.append("['lib/release/universal_copy_trace.a86U', {target: 'gnu.targets.Linux86', suffix: '86U'}],\n");
            sb.append("['lib/debug/universal_copy.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/debug/universal_copy_trace.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/release/universal_copy.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/release/universal_copy_trace.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/debug/universal_copy.av6', {target: 'gnu.targets.arm.GCArmv6', suffix: 'v6'}],\n");
            sb.append("['lib/debug/universal_copy_trace.av6', {target: 'gnu.targets.arm.GCArmv6', suffix: 'v6'}],\n");
            sb.append("['lib/release/universal_copy.av6', {target: 'gnu.targets.arm.GCArmv6', suffix: 'v6'}],\n");
            sb.append("['lib/release/universal_copy_trace.av6', {target: 'gnu.targets.arm.GCArmv6', suffix: 'v6'}],\n");
            sb.append("['lib/debug/universal_copy.av7A', {target: 'gnu.targets.arm.GCArmv7A', suffix: 'v7A'}],\n");
            sb.append("['lib/debug/universal_copy_trace.av7A', {target: 'gnu.targets.arm.GCArmv7A', suffix: 'v7A'}],\n");
            sb.append("['lib/release/universal_copy.av7A', {target: 'gnu.targets.arm.GCArmv7A', suffix: 'v7A'}],\n");
            sb.append("['lib/release/universal_copy_trace.av7A', {target: 'gnu.targets.arm.GCArmv7A', suffix: 'v7A'}],\n");
            sb.append("['lib/debug/universal_copy.a470uC', {target: 'gnu.targets.UCArm9', suffix: '470uC'}],\n");
            sb.append("['lib/debug/universal_copy_trace.a470uC', {target: 'gnu.targets.UCArm9', suffix: '470uC'}],\n");
            sb.append("['lib/release/universal_copy.a470uC', {target: 'gnu.targets.UCArm9', suffix: '470uC'}],\n");
            sb.append("['lib/release/universal_copy_trace.a470uC', {target: 'gnu.targets.UCArm9', suffix: '470uC'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void UniversalCopy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.dm.examples.universal_copy.UniversalCopy", "ti.xdais.dm.examples.universal_copy");
        po = (Proto.Obj)om.findStrict("ti.xdais.dm.examples.universal_copy.UniversalCopy.Module", "ti.xdais.dm.examples.universal_copy");
        vo.init2(po, "ti.xdais.dm.examples.universal_copy.UniversalCopy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.xdais.dm.examples.universal_copy", "ti.xdais.dm.examples.universal_copy"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.dm.examples.universal_copy")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.dm.examples.universal_copy.UniversalCopy$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("UniversalCopy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("UniversalCopy");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.dm.examples.universal_copy.UniversalCopy", "ti.xdais.dm.examples.universal_copy"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.xdais.dm.examples.universal_copy.UniversalCopy")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.xdais.dm.examples.universal_copy")).add(pkgV);
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
        UniversalCopy$$OBJECTS();
        UniversalCopy$$CONSTS();
        UniversalCopy$$CREATES();
        UniversalCopy$$FUNCTIONS();
        UniversalCopy$$SIZES();
        UniversalCopy$$TYPES();
        if (isROV) {
            UniversalCopy$$ROV();
        }//isROV
        $$SINGLETONS();
        UniversalCopy$$SINGLETONS();
        $$INITIALIZATION();
    }
}
