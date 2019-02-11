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

public class ti_sdo_fc_dskt2
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
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.dskt2.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.dskt2", new Value.Obj("ti.sdo.fc.dskt2", pkgP));
    }

    void DSKT2$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.dskt2.DSKT2.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.dskt2.DSKT2", new Value.Obj("ti.sdo.fc.dskt2.DSKT2", po));
        pkgV.bind("DSKT2", vo);
        // decls 
    }

    void DSKT2$$CONSTS()
    {
        // module DSKT2
    }

    void DSKT2$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void DSKT2$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void DSKT2$$SIZES()
    {
    }

    void DSKT2$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.dskt2.DSKT2.Module", "ti.sdo.fc.dskt2");
        po.init("ti.sdo.fc.dskt2.DSKT2.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("DARAM0", $$T_Str, $$UNDEF, "wh");
        po.addFld("DARAM1", $$T_Str, $$UNDEF, "wh");
        po.addFld("DARAM2", $$T_Str, $$UNDEF, "wh");
        po.addFld("SARAM0", $$T_Str, $$UNDEF, "wh");
        po.addFld("SARAM1", $$T_Str, $$UNDEF, "wh");
        po.addFld("SARAM2", $$T_Str, $$UNDEF, "wh");
        po.addFld("ESDATA", $$T_Str, $$UNDEF, "wh");
        po.addFld("IPROG", $$T_Str, $$UNDEF, "wh");
        po.addFld("EPROG", $$T_Str, $$UNDEF, "wh");
        po.addFld("DSKT2_HEAP", $$T_Str, $$UNDEF, "wh");
        po.addFld("ALLOW_EXTERNAL_SCRATCH", $$T_Bool, true, "wh");
        po.addFld("DARAM_SCRATCH_SIZES", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false), Global.newArray(new Object[]{0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L}), "wh");
        po.addFld("SARAM_SCRATCH_SIZES", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false), Global.newArray(new Object[]{0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L}), "wh");
        po.addFld("cacheWritebackInvalidateFxn", $$T_Str, "DSKT2_cacheWBInv", "wh");
        po.addFld("disableLazyDeactivate", $$T_Bool, $$UNDEF, "wh");
        po.addFld("ipcKeyBase", Proto.Elm.newCNum("(xdc_UInt)"), 0x44534B54L, "wh");
    }

    void DSKT2$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.dskt2.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.dskt2"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/dskt2/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.dskt2"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.dskt2"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.dskt2"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.dskt2"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.dskt2"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.dskt2"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.dskt2", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.dskt2");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.dskt2.");
        pkgV.bind("$vers", Global.newArray(1, 0, 4));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.dskt2'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.fc.dskt2$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.fc.dskt2$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.fc.dskt2$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/dskt2.aem4',\n");
            sb.append("'lib/release/dskt2_lazydDisable.aem4',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/dskt2.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/dskt2_lazydDisable.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void DSKT2$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.dskt2.DSKT2", "ti.sdo.fc.dskt2");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.dskt2.DSKT2.Module", "ti.sdo.fc.dskt2");
        vo.init2(po, "ti.sdo.fc.dskt2.DSKT2", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.dskt2", "ti.sdo.fc.dskt2"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.dskt2")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.dskt2.DSKT2$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./DSKT2.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./DSKT2.xdt");
        pkgV.bind("DSKT2", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("DSKT2");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.dskt2.DSKT2", "ti.sdo.fc.dskt2"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.fc.dskt2.DSKT2")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.dskt2")).add(pkgV);
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
        DSKT2$$OBJECTS();
        DSKT2$$CONSTS();
        DSKT2$$CREATES();
        DSKT2$$FUNCTIONS();
        DSKT2$$SIZES();
        DSKT2$$TYPES();
        if (isROV) {
            DSKT2$$ROV();
        }//isROV
        $$SINGLETONS();
        DSKT2$$SINGLETONS();
        $$INITIALIZATION();
    }
}
