/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A75
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_opencl
{
    static final String VERS = "@(#) xdc-A75\n";

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
        pkgP = (Proto.Obj)om.bind("ti.opencl.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.opencl", new Value.Obj("ti.opencl", pkgP));
    }

    void OpenCL$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.opencl.OpenCL.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.opencl.OpenCL", new Value.Obj("ti.opencl.OpenCL", po));
        pkgV.bind("OpenCL", vo);
        // decls 
    }

    void DSPMonitor$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.opencl.DSPMonitor.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.opencl.DSPMonitor", new Value.Obj("ti.opencl.DSPMonitor", po));
        pkgV.bind("DSPMonitor", vo);
        // decls 
    }

    void OpenCL$$CONSTS()
    {
        // module OpenCL
    }

    void DSPMonitor$$CONSTS()
    {
        // module DSPMonitor
    }

    void OpenCL$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void DSPMonitor$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void OpenCL$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void DSPMonitor$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void OpenCL$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void DSPMonitor$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void OpenCL$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/opencl/OpenCL.xs");
        om.bind("ti.opencl.OpenCL$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.opencl.OpenCL.Module", "ti.opencl");
        po.init("ti.opencl.OpenCL.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.opencl"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("computeUnitList", $$T_Str, "0, 1", "w");
            po.addFld("OCL_ipc_customized", $$T_Bool, false, "w");
            po.addFld("OCL_memory_customized", $$T_Bool, false, "w");
            po.addFld("OCL_HOSTPROG_base", Proto.Elm.newCNum("(xdc_UInt32)"), 0L, "w");
            po.addFld("OCL_HOSTPROG_len", Proto.Elm.newCNum("(xdc_UInt32)"), 0L, "w");
            po.addFld("OCL_GLOBAL_base", Proto.Elm.newCNum("(xdc_UInt32)"), 0L, "w");
            po.addFld("OCL_GLOBAL_len", Proto.Elm.newCNum("(xdc_UInt32)"), 0L, "w");
            po.addFld("OCL_LOCAL_base", Proto.Elm.newCNum("(xdc_UInt32)"), 0L, "w");
            po.addFld("OCL_LOCAL_len", Proto.Elm.newCNum("(xdc_UInt32)"), 0L, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.opencl.OpenCL$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.opencl.OpenCL$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.opencl.OpenCL$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.opencl.OpenCL$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void DSPMonitor$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/opencl/DSPMonitor.xs");
        om.bind("ti.opencl.DSPMonitor$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.opencl.DSPMonitor.Module", "ti.opencl");
        po.init("ti.opencl.DSPMonitor.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.opencl"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("OCL_monitor_priority", Proto.Elm.newCNum("(xdc_UInt32)"), 3L, "w");
            po.addFld("OCL_ipc_customized", $$T_Bool, false, "w");
            po.addFld("OCL_link_extra_sym_def", $$T_Bool, false, "w");
            po.addFld("OCL_memory_customized", $$T_Bool, false, "w");
            po.addFld("OCL_SR0_base", Proto.Elm.newCNum("(xdc_UInt32)"), 0L, "w");
            po.addFld("OCL_SR0_len", Proto.Elm.newCNum("(xdc_UInt32)"), 0L, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.opencl.DSPMonitor$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.opencl.DSPMonitor$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.opencl.DSPMonitor$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.opencl.DSPMonitor$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void OpenCL$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.opencl.OpenCL", "ti.opencl");
    }

    void DSPMonitor$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.opencl.DSPMonitor", "ti.opencl");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.opencl.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.opencl"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/opencl/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.opencl"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.opencl"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.opencl"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.opencl"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.opencl"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.opencl"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.opencl", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.opencl");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.opencl.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.opencl'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.opencl$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.opencl$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.opencl$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/ti.opencl.aa15fg',\n");
            sb.append("'lib/ti.opencl.ae66',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/ti.opencl.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/ti.opencl.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void OpenCL$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.opencl.OpenCL", "ti.opencl");
        po = (Proto.Obj)om.findStrict("ti.opencl.OpenCL.Module", "ti.opencl");
        vo.init2(po, "ti.opencl.OpenCL", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.opencl.OpenCL$$capsule", "ti.opencl"));
        vo.bind("$package", om.findStrict("ti.opencl", "ti.opencl"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        icfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        mcfgs.add("computeUnitList");
        mcfgs.add("OCL_ipc_customized");
        mcfgs.add("OCL_memory_customized");
        mcfgs.add("OCL_HOSTPROG_base");
        mcfgs.add("OCL_HOSTPROG_len");
        mcfgs.add("OCL_GLOBAL_base");
        mcfgs.add("OCL_GLOBAL_len");
        mcfgs.add("OCL_LOCAL_base");
        mcfgs.add("OCL_LOCAL_len");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.opencl")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("$$fxntab", Global.newArray("ti_opencl_OpenCL_Module__startupDone__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("OpenCL", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("OpenCL");
    }

    void DSPMonitor$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.opencl.DSPMonitor", "ti.opencl");
        po = (Proto.Obj)om.findStrict("ti.opencl.DSPMonitor.Module", "ti.opencl");
        vo.init2(po, "ti.opencl.DSPMonitor", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.opencl.DSPMonitor$$capsule", "ti.opencl"));
        vo.bind("$package", om.findStrict("ti.opencl", "ti.opencl"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        icfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        mcfgs.add("OCL_monitor_priority");
        mcfgs.add("OCL_ipc_customized");
        mcfgs.add("OCL_link_extra_sym_def");
        mcfgs.add("OCL_memory_customized");
        mcfgs.add("OCL_SR0_base");
        mcfgs.add("OCL_SR0_len");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.opencl")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("$$fxntab", Global.newArray("ti_opencl_DSPMonitor_Module__startupDone__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("DSPMonitor", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("DSPMonitor");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.opencl.OpenCL", "ti.opencl"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.opencl.DSPMonitor", "ti.opencl"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.opencl.OpenCL")).bless();
        ((Value.Obj)om.getv("ti.opencl.DSPMonitor")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.opencl")).add(pkgV);
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
        OpenCL$$OBJECTS();
        DSPMonitor$$OBJECTS();
        OpenCL$$CONSTS();
        DSPMonitor$$CONSTS();
        OpenCL$$CREATES();
        DSPMonitor$$CREATES();
        OpenCL$$FUNCTIONS();
        DSPMonitor$$FUNCTIONS();
        OpenCL$$SIZES();
        DSPMonitor$$SIZES();
        OpenCL$$TYPES();
        DSPMonitor$$TYPES();
        if (isROV) {
            OpenCL$$ROV();
            DSPMonitor$$ROV();
        }//isROV
        $$SINGLETONS();
        OpenCL$$SINGLETONS();
        DSPMonitor$$SINGLETONS();
        $$INITIALIZATION();
    }
}
