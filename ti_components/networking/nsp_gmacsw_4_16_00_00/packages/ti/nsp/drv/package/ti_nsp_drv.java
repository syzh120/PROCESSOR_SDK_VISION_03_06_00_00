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

public class ti_nsp_drv
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
        pkgP = (Proto.Obj)om.bind("ti.nsp.drv.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.nsp.drv", new Value.Obj("ti.nsp.drv", pkgP));
    }

    void GMACSW$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.nsp.drv.GMACSW.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.nsp.drv.GMACSW", new Value.Obj("ti.nsp.drv.GMACSW", po));
        pkgV.bind("GMACSW", vo);
        // decls 
        om.bind("ti.nsp.drv.GMACSW.Device", new Proto.Enm("ti.nsp.drv.GMACSW.Device"));
    }

    void GMACSW$$CONSTS()
    {
        // module GMACSW
        om.bind("ti.nsp.drv.GMACSW.DEVICE_VAYU", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.nsp.drv.GMACSW.Device", "ti.nsp.drv"), "ti.nsp.drv.GMACSW.DEVICE_VAYU", 0));
        om.bind("ti.nsp.drv.GMACSW.DEVICE_TDA3XX", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.nsp.drv.GMACSW.Device", "ti.nsp.drv"), "ti.nsp.drv.GMACSW.DEVICE_TDA3XX", 1));
        om.bind("ti.nsp.drv.GMACSW.DEVICE_J5ECO", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.nsp.drv.GMACSW.Device", "ti.nsp.drv"), "ti.nsp.drv.GMACSW.DEVICE_J5ECO", 2));
        om.bind("ti.nsp.drv.GMACSW.DEVICE_DM385", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.nsp.drv.GMACSW.Device", "ti.nsp.drv"), "ti.nsp.drv.GMACSW.DEVICE_DM385", 3));
        om.bind("ti.nsp.drv.GMACSW.DEVICE_SUBARCTIC", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.nsp.drv.GMACSW.Device", "ti.nsp.drv"), "ti.nsp.drv.GMACSW.DEVICE_SUBARCTIC", 4));
        om.bind("ti.nsp.drv.GMACSW.DEVICE_CENTAURUS", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.nsp.drv.GMACSW.Device", "ti.nsp.drv"), "ti.nsp.drv.GMACSW.DEVICE_CENTAURUS", 5));
    }

    void GMACSW$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void GMACSW$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GMACSW$$SIZES()
    {
    }

    void GMACSW$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.nsp.drv.GMACSW.Module", "ti.nsp.drv");
        po.init("ti.nsp.drv.GMACSW.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("instrumentedBuild", $$T_Bool, false, "wh");
        po.addFld("tfdtpBuild", $$T_Bool, false, "wh");
        po.addFld("device", (Proto)om.findStrict("ti.nsp.drv.GMACSW.Device", "ti.nsp.drv"), om.find("ti.nsp.drv.GMACSW.DEVICE_VAYU"), "wh");
    }

    void GMACSW$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.nsp.drv.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.nsp.drv"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/nsp/drv/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.nsp.drv"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.nsp.drv"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.nsp.drv"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.nsp.drv"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.nsp.drv"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.nsp.drv"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.nsp.drv", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.nsp.drv");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.nsp.drv.");
        pkgV.bind("$vers", Global.newArray(4, 16, 00, 00));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.nsp.drv'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.nsp.drv$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.nsp.drv$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.nsp.drv$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/vayu/debug/ti.nsp.drv.gmacsw.aa15fg',\n");
            sb.append("'lib/vayu/debug/ti.nsp.drv.gmacsw_instr.aa15fg',\n");
            sb.append("'lib/vayu/release/ti.nsp.drv.gmacsw.aa15fg',\n");
            sb.append("'lib/vayu/release/ti.nsp.drv.gmacsw_instr.aa15fg',\n");
            sb.append("'lib/vayu/debug/ti.nsp.drv.gmacsw.aem4',\n");
            sb.append("'lib/vayu/debug/ti.nsp.drv.gmacsw_instr.aem4',\n");
            sb.append("'lib/vayu/release/ti.nsp.drv.gmacsw.aem4',\n");
            sb.append("'lib/vayu/release/ti.nsp.drv.gmacsw_instr.aem4',\n");
            sb.append("'lib/debug/ti.nsp.drv.ndktfdtp2nsp.aa15fg',\n");
            sb.append("'lib/debug/ti.nsp.drv.ndktfdtp2nsp_instr.aa15fg',\n");
            sb.append("'lib/debug/ti.nsp.drv.ndk2nsp.aa15fg',\n");
            sb.append("'lib/debug/ti.nsp.drv.ndk2nsp_instr.aa15fg',\n");
            sb.append("'lib/release/ti.nsp.drv.ndktfdtp2nsp.aa15fg',\n");
            sb.append("'lib/release/ti.nsp.drv.ndktfdtp2nsp_instr.aa15fg',\n");
            sb.append("'lib/release/ti.nsp.drv.ndk2nsp.aa15fg',\n");
            sb.append("'lib/release/ti.nsp.drv.ndk2nsp_instr.aa15fg',\n");
            sb.append("'lib/debug/ti.nsp.drv.ndktfdtp2nsp.aem4',\n");
            sb.append("'lib/debug/ti.nsp.drv.ndktfdtp2nsp_instr.aem4',\n");
            sb.append("'lib/debug/ti.nsp.drv.ndk2nsp.aem4',\n");
            sb.append("'lib/debug/ti.nsp.drv.ndk2nsp_instr.aem4',\n");
            sb.append("'lib/release/ti.nsp.drv.ndktfdtp2nsp.aem4',\n");
            sb.append("'lib/release/ti.nsp.drv.ndktfdtp2nsp_instr.aem4',\n");
            sb.append("'lib/release/ti.nsp.drv.ndk2nsp.aem4',\n");
            sb.append("'lib/release/ti.nsp.drv.ndk2nsp_instr.aem4',\n");
            sb.append("'lib/debug/ti.nsp.drv.tfdtp.aa15fg',\n");
            sb.append("'lib/debug/ti.nsp.drv.tfdtp_instr.aa15fg',\n");
            sb.append("'lib/release/ti.nsp.drv.tfdtp.aa15fg',\n");
            sb.append("'lib/release/ti.nsp.drv.tfdtp_instr.aa15fg',\n");
            sb.append("'lib/debug/ti.nsp.drv.tfdtp.aem4',\n");
            sb.append("'lib/debug/ti.nsp.drv.tfdtp_instr.aem4',\n");
            sb.append("'lib/release/ti.nsp.drv.tfdtp.aem4',\n");
            sb.append("'lib/release/ti.nsp.drv.tfdtp_instr.aem4',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/vayu/debug/ti.nsp.drv.gmacsw.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/vayu/debug/ti.nsp.drv.gmacsw_instr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/vayu/release/ti.nsp.drv.gmacsw.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/vayu/release/ti.nsp.drv.gmacsw_instr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/vayu/debug/ti.nsp.drv.gmacsw.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/vayu/debug/ti.nsp.drv.gmacsw_instr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/vayu/release/ti.nsp.drv.gmacsw.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/vayu/release/ti.nsp.drv.gmacsw_instr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.ndktfdtp2nsp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.ndktfdtp2nsp_instr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.ndk2nsp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.ndk2nsp_instr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/release/ti.nsp.drv.ndktfdtp2nsp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/release/ti.nsp.drv.ndktfdtp2nsp_instr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/release/ti.nsp.drv.ndk2nsp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/release/ti.nsp.drv.ndk2nsp_instr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.ndktfdtp2nsp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.ndktfdtp2nsp_instr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.ndk2nsp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.ndk2nsp_instr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.nsp.drv.ndktfdtp2nsp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.nsp.drv.ndktfdtp2nsp_instr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.nsp.drv.ndk2nsp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.nsp.drv.ndk2nsp_instr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.tfdtp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.tfdtp_instr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/release/ti.nsp.drv.tfdtp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/release/ti.nsp.drv.tfdtp_instr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.tfdtp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.nsp.drv.tfdtp_instr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.nsp.drv.tfdtp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.nsp.drv.tfdtp_instr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void GMACSW$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.nsp.drv.GMACSW", "ti.nsp.drv");
        po = (Proto.Obj)om.findStrict("ti.nsp.drv.GMACSW.Module", "ti.nsp.drv");
        vo.init2(po, "ti.nsp.drv.GMACSW", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.nsp.drv", "ti.nsp.drv"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("Device", om.findStrict("ti.nsp.drv.GMACSW.Device", "ti.nsp.drv"));
        vo.bind("DEVICE_VAYU", om.findStrict("ti.nsp.drv.GMACSW.DEVICE_VAYU", "ti.nsp.drv"));
        vo.bind("DEVICE_TDA3XX", om.findStrict("ti.nsp.drv.GMACSW.DEVICE_TDA3XX", "ti.nsp.drv"));
        vo.bind("DEVICE_J5ECO", om.findStrict("ti.nsp.drv.GMACSW.DEVICE_J5ECO", "ti.nsp.drv"));
        vo.bind("DEVICE_DM385", om.findStrict("ti.nsp.drv.GMACSW.DEVICE_DM385", "ti.nsp.drv"));
        vo.bind("DEVICE_SUBARCTIC", om.findStrict("ti.nsp.drv.GMACSW.DEVICE_SUBARCTIC", "ti.nsp.drv"));
        vo.bind("DEVICE_CENTAURUS", om.findStrict("ti.nsp.drv.GMACSW.DEVICE_CENTAURUS", "ti.nsp.drv"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.nsp.drv")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.nsp.drv.GMACSW$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("GMACSW", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GMACSW");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.nsp.drv.GMACSW", "ti.nsp.drv"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.nsp.drv.GMACSW")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.nsp.drv")).add(pkgV);
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
        GMACSW$$OBJECTS();
        GMACSW$$CONSTS();
        GMACSW$$CREATES();
        GMACSW$$FUNCTIONS();
        GMACSW$$SIZES();
        GMACSW$$TYPES();
        if (isROV) {
            GMACSW$$ROV();
        }//isROV
        $$SINGLETONS();
        GMACSW$$SINGLETONS();
        $$INITIALIZATION();
    }
}
