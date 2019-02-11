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

public class ti_avbtp
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
        Global.callFxn("loadPackage", xdcO, "ti.nsp.drv");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.edma3.drv");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.edma3.rm");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.avbtp.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.avbtp", new Value.Obj("ti.avbtp", pkgP));
    }

    void AVBTP$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.avbtp.AVBTP.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.avbtp.AVBTP", new Value.Obj("ti.avbtp.AVBTP", po));
        pkgV.bind("AVBTP", vo);
        // decls 
    }

    void AVBTP$$CONSTS()
    {
        // module AVBTP
    }

    void AVBTP$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void AVBTP$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void AVBTP$$SIZES()
    {
    }

    void AVBTP$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.avbtp.AVBTP.Module", "ti.avbtp");
        po.init("ti.avbtp.AVBTP.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("instrumentedBuild", $$T_Bool, false, "wh");
    }

    void AVBTP$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.avbtp.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.avbtp"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/avbtp/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.avbtp"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.avbtp"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.avbtp"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.avbtp"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.avbtp"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.avbtp"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.avbtp", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.avbtp");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.avbtp.");
        pkgV.bind("$vers", Global.newArray(00, 10, 00, 00));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.nsp.drv", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.edma3.drv", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.edma3.rm", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.avbtp'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.avbtp$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.avbtp$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.avbtp$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/ti.avbtp.aem3',\n");
            sb.append("'lib/debug/ti.avbtp_instr.aem3',\n");
            sb.append("'lib/release/ti.avbtp.aem3',\n");
            sb.append("'lib/release/ti.avbtp_instr.aem3',\n");
            sb.append("'lib/debug/ti.avbtp.aem4',\n");
            sb.append("'lib/debug/ti.avbtp_instr.aem4',\n");
            sb.append("'lib/release/ti.avbtp.aem4',\n");
            sb.append("'lib/release/ti.avbtp_instr.aem4',\n");
            sb.append("'lib/debug/ti.avbtp.aea8f',\n");
            sb.append("'lib/debug/ti.avbtp_instr.aea8f',\n");
            sb.append("'lib/release/ti.avbtp.aea8f',\n");
            sb.append("'lib/release/ti.avbtp_instr.aea8f',\n");
            sb.append("'lib/debug/ti.avbtp.aa15fg',\n");
            sb.append("'lib/debug/ti.avbtp_instr.aa15fg',\n");
            sb.append("'lib/release/ti.avbtp.aa15fg',\n");
            sb.append("'lib/release/ti.avbtp_instr.aa15fg',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/ti.avbtp.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/ti.avbtp_instr.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/ti.avbtp.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/ti.avbtp_instr.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/ti.avbtp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.avbtp_instr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.avbtp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.avbtp_instr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.avbtp.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/debug/ti.avbtp_instr.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/release/ti.avbtp.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/release/ti.avbtp_instr.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/debug/ti.avbtp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/debug/ti.avbtp_instr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/release/ti.avbtp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/release/ti.avbtp_instr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void AVBTP$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.avbtp.AVBTP", "ti.avbtp");
        po = (Proto.Obj)om.findStrict("ti.avbtp.AVBTP.Module", "ti.avbtp");
        vo.init2(po, "ti.avbtp.AVBTP", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.avbtp", "ti.avbtp"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.avbtp")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.avbtp.AVBTP$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("AVBTP", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("AVBTP");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.avbtp.AVBTP", "ti.avbtp"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.avbtp.AVBTP")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.avbtp")).add(pkgV);
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
        AVBTP$$OBJECTS();
        AVBTP$$CONSTS();
        AVBTP$$CREATES();
        AVBTP$$FUNCTIONS();
        AVBTP$$SIZES();
        AVBTP$$TYPES();
        if (isROV) {
            AVBTP$$ROV();
        }//isROV
        $$SINGLETONS();
        AVBTP$$SINGLETONS();
        $$INITIALIZATION();
    }
}
