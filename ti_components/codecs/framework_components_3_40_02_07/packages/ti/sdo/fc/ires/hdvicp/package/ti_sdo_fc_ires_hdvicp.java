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

public class ti_sdo_fc_ires_hdvicp
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
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.ires.hdvicp.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.ires.hdvicp", new Value.Obj("ti.sdo.fc.ires.hdvicp", pkgP));
    }

    void HDVICP$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.ires.hdvicp.HDVICP.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.ires.hdvicp.HDVICP", new Value.Obj("ti.sdo.fc.ires.hdvicp.HDVICP", po));
        pkgV.bind("HDVICP", vo);
        // decls 
    }

    void HDVICP2$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.ires.hdvicp.HDVICP2.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.ires.hdvicp.HDVICP2", new Value.Obj("ti.sdo.fc.ires.hdvicp.HDVICP2", po));
        pkgV.bind("HDVICP2", vo);
        // decls 
    }

    void HDVICP$$CONSTS()
    {
        // module HDVICP
    }

    void HDVICP2$$CONSTS()
    {
        // module HDVICP2
        om.bind("ti.sdo.fc.ires.hdvicp.HDVICP2.MAXRESOURCES", 10L);
        om.bind("ti.sdo.fc.ires.hdvicp.HDVICP2.FOREVER", Global.eval("-1"));
    }

    void HDVICP$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void HDVICP2$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void HDVICP$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void HDVICP2$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void HDVICP$$SIZES()
    {
    }

    void HDVICP2$$SIZES()
    {
    }

    void HDVICP$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.hdvicp.HDVICP.Module", "ti.sdo.fc.ires.hdvicp");
        po.init("ti.sdo.fc.ires.hdvicp.HDVICP.Module", om.findStrict("ti.sdo.fc.ires.IRESMAN.Module", "ti.sdo.fc.ires.hdvicp"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("ipcKeyBase", Proto.Elm.newCNum("(xdc_UInt)"), 0x49564448L, "wh");
        po.addFld("autoRegister", $$T_Bool, true, "wh");
    }

    void HDVICP2$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/ires/hdvicp/HDVICP2.xs");
        om.bind("ti.sdo.fc.ires.hdvicp.HDVICP2$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.hdvicp.HDVICP2.Module", "ti.sdo.fc.ires.hdvicp");
        po.init("ti.sdo.fc.ires.hdvicp.HDVICP2.Module", om.findStrict("ti.sdo.fc.ires.IRESMAN.Module", "ti.sdo.fc.ires.hdvicp"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("MAXRESOURCES", Proto.Elm.newCNum("(xdc_Int)"), 10L, "rh");
                po.addFld("FOREVER", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("-1"), "rh");
        po.addFld("memoryBaseAddress", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(10L)), $$DEFAULT, "wh");
        po.addFld("resetControlAddress", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(10L)), $$DEFAULT, "wh");
        po.addFld("registerBaseAddress", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(10L)), $$DEFAULT, "wh");
        po.addFld("configureFxn", $$T_Str, $$UNDEF, "wh");
        po.addFld("waitFxn", $$T_Str, $$UNDEF, "wh");
        po.addFld("doneFxn", $$T_Str, $$UNDEF, "wh");
        po.addFld("resetFxn", $$T_Str, $$UNDEF, "wh");
        po.addFld("clearPRCMRegister", $$T_Bool, $$UNDEF, "wh");
        po.addFld("timeout", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
        po.addFld("delegate", $$T_Str, $$UNDEF, "wh");
        po.addFld("semCreateFxn", $$T_Str, null, "wh");
        po.addFld("semDeleteFxn", $$T_Str, null, "wh");
        po.addFld("semPendFxn", $$T_Str, null, "wh");
        po.addFld("semPostFxn", $$T_Str, null, "wh");
        po.addFld("ipcKeyBase", Proto.Elm.newCNum("(xdc_UInt)"), 0x32564448L, "wh");
        po.addFld("autoRegister", $$T_Bool, true, "wh");
        po.addFld("getHDVICP2Fxn", $$T_Str, $$UNDEF, "wh");
        po.addFld("freeHDVICP2Fxn", $$T_Str, $$UNDEF, "wh");
        po.addFld("yieldReleaseFxn", $$T_Str, $$UNDEF, "wh");
        po.addFld("yieldAcquireFxn", $$T_Str, $$UNDEF, "wh");
        po.addFld("getYieldArgsFxn", $$T_Str, $$UNDEF, "wh");
        po.addFld("maxHdvicp2ResetDelay", Proto.Elm.newCNum("(xdc_UInt)"), 1000L, "wh");
        po.addFld("numHdvicp2", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
        po.addFld("intArray", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.fc.ires.hdvicp.HDVICP2$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.fc.ires.hdvicp.HDVICP2$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.fc.ires.hdvicp.HDVICP2$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void HDVICP$$ROV()
    {
    }

    void HDVICP2$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.ires.hdvicp.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.ires.hdvicp"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/ires/hdvicp/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.ires.hdvicp"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.ires.hdvicp"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.ires.hdvicp"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.ires.hdvicp"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.ires.hdvicp"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.ires.hdvicp"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.ires.hdvicp", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.ires.hdvicp");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.ires.hdvicp.");
        pkgV.bind("$vers", Global.newArray(1, 0, 1));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.ires.hdvicp'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.fc.ires.hdvicp$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.fc.ires.hdvicp$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.fc.ires.hdvicp$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/hdvicp2.aem4',\n");
            sb.append("'lib/release/hdvicp2.aem4',\n");
            sb.append("'lib/profile/hdvicp2.aem4',\n");
            sb.append("'lib/coverage/hdvicp2.aem4',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/hdvicp2.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/hdvicp2.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/profile/hdvicp2.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/coverage/hdvicp2.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void HDVICP$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.ires.hdvicp.HDVICP", "ti.sdo.fc.ires.hdvicp");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.hdvicp.HDVICP.Module", "ti.sdo.fc.ires.hdvicp");
        vo.init2(po, "ti.sdo.fc.ires.hdvicp.HDVICP", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.ires.hdvicp", "ti.sdo.fc.ires.hdvicp"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.ires.hdvicp")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.ires.hdvicp.HDVICP$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./HDVICP.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./HDVICP.xdt");
        pkgV.bind("HDVICP", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("HDVICP");
    }

    void HDVICP2$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.ires.hdvicp.HDVICP2", "ti.sdo.fc.ires.hdvicp");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.hdvicp.HDVICP2.Module", "ti.sdo.fc.ires.hdvicp");
        vo.init2(po, "ti.sdo.fc.ires.hdvicp.HDVICP2", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.fc.ires.hdvicp.HDVICP2$$capsule", "ti.sdo.fc.ires.hdvicp"));
        vo.bind("$package", om.findStrict("ti.sdo.fc.ires.hdvicp", "ti.sdo.fc.ires.hdvicp"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.ires.hdvicp")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.ires.hdvicp.HDVICP2$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./HDVICP2.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./HDVICP2.xdt");
        pkgV.bind("HDVICP2", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("HDVICP2");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.ires.hdvicp.HDVICP", "ti.sdo.fc.ires.hdvicp"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.ires.hdvicp.HDVICP2", "ti.sdo.fc.ires.hdvicp"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.fc.ires.hdvicp.HDVICP")).bless();
        ((Value.Obj)om.getv("ti.sdo.fc.ires.hdvicp.HDVICP2")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.ires.hdvicp")).add(pkgV);
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
        HDVICP$$OBJECTS();
        HDVICP2$$OBJECTS();
        HDVICP$$CONSTS();
        HDVICP2$$CONSTS();
        HDVICP$$CREATES();
        HDVICP2$$CREATES();
        HDVICP$$FUNCTIONS();
        HDVICP2$$FUNCTIONS();
        HDVICP$$SIZES();
        HDVICP2$$SIZES();
        HDVICP$$TYPES();
        HDVICP2$$TYPES();
        if (isROV) {
            HDVICP$$ROV();
            HDVICP2$$ROV();
        }//isROV
        $$SINGLETONS();
        HDVICP$$SINGLETONS();
        HDVICP2$$SINGLETONS();
        $$INITIALIZATION();
    }
}
