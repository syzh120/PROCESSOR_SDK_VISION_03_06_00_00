/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-v49
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.*;

public class ti_sdo_codecs_hdvicp20api_ce
{
    static final String VERS = "@(#) xdc-v49\n";

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
    ArrayList<Object> proxies = new ArrayList<Object>();
    ArrayList<Object> sizes = new ArrayList<Object>();
    ArrayList<Object> tdefs = new ArrayList<Object>();

    void $$IMPORTS()
    {
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.universal");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.codecs.hdvicp20api");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.codecs.hdvicp20api.ce.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.codecs.hdvicp20api.ce", new Value.Obj("ti.sdo.codecs.hdvicp20api.ce", pkgP));
    }

    void HDVICP20API$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API", new Value.Obj("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API", po));
        pkgV.bind("HDVICP20API", vo);
        // decls 
    }

    void HDVICP20API$$CONSTS()
    {
        // module HDVICP20API
    }

    void HDVICP20API$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void HDVICP20API$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void HDVICP20API$$SIZES()
    {
    }

    void HDVICP20API$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/codecs/hdvicp20api/ce/HDVICP20API.xs");
        om.bind("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API.Module", "ti.sdo.codecs.hdvicp20api.ce");
        po.init("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API.Module", om.findStrict("ti.sdo.ce.universal.IUNIVERSAL.Module", "ti.sdo.codecs.hdvicp20api.ce"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("alg", (Proto)om.findStrict("ti.sdo.codecs.hdvicp20api.HDVICP20API.Module", "ti.sdo.codecs.hdvicp20api.ce"), om.find("ti.sdo.codecs.hdvicp20api.HDVICP20API"), "rh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getCreationStackSize");
                if (fxn != null) po.addFxn("getCreationStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getCreationStackSize", "ti.sdo.codecs.hdvicp20api.ce"), fxn);
                fxn = Global.get(cap, "getDaramScratchSize");
                if (fxn != null) po.addFxn("getDaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getDaramScratchSize", "ti.sdo.codecs.hdvicp20api.ce"), fxn);
                fxn = Global.get(cap, "getSaramScratchSize");
                if (fxn != null) po.addFxn("getSaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getSaramScratchSize", "ti.sdo.codecs.hdvicp20api.ce"), fxn);
                fxn = Global.get(cap, "getStackSize");
                if (fxn != null) po.addFxn("getStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getStackSize", "ti.sdo.codecs.hdvicp20api.ce"), fxn);
                fxn = Global.get(cap, "getUUID");
                if (fxn != null) po.addFxn("getUUID", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getUUID", "ti.sdo.codecs.hdvicp20api.ce"), fxn);
    }

    void HDVICP20API$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.codecs.hdvicp20api.ce.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.codecs.hdvicp20api.ce"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.sdo.codecs.hdvicp20api.ce", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.codecs.hdvicp20api.ce");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.codecs.hdvicp20api.ce.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ce.universal", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.codecs.hdvicp20api", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.codecs.hdvicp20api.ce'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void HDVICP20API$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API", "ti.sdo.codecs.hdvicp20api.ce");
        po = (Proto.Obj)om.findStrict("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API.Module", "ti.sdo.codecs.hdvicp20api.ce");
        vo.init2(po, "ti.sdo.codecs.hdvicp20api.ce.HDVICP20API", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API$$capsule", "ti.sdo.codecs.hdvicp20api.ce"));
        vo.bind("$package", om.findStrict("ti.sdo.codecs.hdvicp20api.ce", "ti.sdo.codecs.hdvicp20api.ce"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.codecs.hdvicp20api.ce")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("HDVICP20API", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("HDVICP20API");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API", "ti.sdo.codecs.hdvicp20api.ce"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.codecs.hdvicp20api.ce.HDVICP20API")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.codecs.hdvicp20api.ce")).add(pkgV);
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
        HDVICP20API$$OBJECTS();
        HDVICP20API$$CONSTS();
        HDVICP20API$$CREATES();
        HDVICP20API$$FUNCTIONS();
        HDVICP20API$$SIZES();
        HDVICP20API$$TYPES();
        if (isROV) {
            HDVICP20API$$ROV();
        }//isROV
        $$SINGLETONS();
        HDVICP20API$$SINGLETONS();
        $$INITIALIZATION();
    }
}
