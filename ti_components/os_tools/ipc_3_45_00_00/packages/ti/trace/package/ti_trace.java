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

public class ti_trace
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
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.trace.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.trace", new Value.Obj("ti.trace", pkgP));
    }

    void SysMin$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.trace.SysMin.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.trace.SysMin", new Value.Obj("ti.trace.SysMin", po));
        pkgV.bind("SysMin", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.trace.SysMin$$ModuleView", new Proto.Obj());
        om.bind("ti.trace.SysMin.ModuleView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.trace.SysMin$$BufferEntryView", new Proto.Obj());
        om.bind("ti.trace.SysMin.BufferEntryView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.trace.SysMin$$LineBuffer", new Proto.Obj());
        om.bind("ti.trace.SysMin.LineBuffer", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.trace.SysMin$$Module_State", new Proto.Obj());
        om.bind("ti.trace.SysMin.Module_State", new Proto.Str(spo, false));
    }

    void SysMin$$CONSTS()
    {
        // module SysMin
        om.bind("ti.trace.SysMin.LINEBUFSIZE", 0x100L);
        om.bind("ti.trace.SysMin.abort", new Extern("ti_trace_SysMin_abort__E", "xdc_Void(*)(xdc_CString)", true, false));
        om.bind("ti.trace.SysMin.exit", new Extern("ti_trace_SysMin_exit__E", "xdc_Void(*)(xdc_Int)", true, false));
        om.bind("ti.trace.SysMin.flush", new Extern("ti_trace_SysMin_flush__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.trace.SysMin.putch", new Extern("ti_trace_SysMin_putch__E", "xdc_Void(*)(xdc_Char)", true, false));
        om.bind("ti.trace.SysMin.ready", new Extern("ti_trace_SysMin_ready__E", "xdc_Bool(*)(xdc_Void)", true, false));
    }

    void SysMin$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void SysMin$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void SysMin$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.trace.SysMin.LineBuffer", "ti.trace");
        sizes.clear();
        sizes.add(Global.newArray("lineidx", "UInt"));
        sizes.add(Global.newArray("linebuf", "A0x100;TChar"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.trace.SysMin.LineBuffer']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.trace.SysMin.LineBuffer']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.trace.SysMin.LineBuffer'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.trace.SysMin.Module_State", "ti.trace");
        sizes.clear();
        sizes.add(Global.newArray("lineBuffers", "UPtr"));
        sizes.add(Global.newArray("outbuf", "UPtr"));
        sizes.add(Global.newArray("outidx", "UInt"));
        sizes.add(Global.newArray("getTime", "UShort"));
        sizes.add(Global.newArray("wrapped", "UShort"));
        sizes.add(Global.newArray("writeidx", "UPtr"));
        sizes.add(Global.newArray("readidx", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.trace.SysMin.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.trace.SysMin.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.trace.SysMin.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void SysMin$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/trace/SysMin.xs");
        om.bind("ti.trace.SysMin$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.trace.SysMin.Module", "ti.trace");
        po.init("ti.trace.SysMin.Module", om.findStrict("xdc.runtime.ISystemSupport.Module", "ti.trace"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("LINEBUFSIZE", Proto.Elm.newCNum("(xdc_SizeT)"), 0x100L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.trace"), $$UNDEF, "wh");
            po.addFld("bufSize", Proto.Elm.newCNum("(xdc_SizeT)"), 0x1000L, "w");
            po.addFld("sectionName", $$T_Str, null, "wh");
            po.addFld("flushAtExit", $$T_Bool, true, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.trace.SysMin$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.trace.SysMin$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.trace.SysMin$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.trace.SysMin$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct SysMin.ModuleView
        po = (Proto.Obj)om.findStrict("ti.trace.SysMin$$ModuleView", "ti.trace");
        po.init("ti.trace.SysMin.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("outBuf", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("outBufIndex", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("getTime", $$T_Bool, $$UNDEF, "w");
                po.addFld("wrapped", $$T_Bool, $$UNDEF, "w");
        // struct SysMin.BufferEntryView
        po = (Proto.Obj)om.findStrict("ti.trace.SysMin$$BufferEntryView", "ti.trace");
        po.init("ti.trace.SysMin.BufferEntryView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("entry", $$T_Str, $$UNDEF, "w");
        // struct SysMin.LineBuffer
        po = (Proto.Obj)om.findStrict("ti.trace.SysMin$$LineBuffer", "ti.trace");
        po.init("ti.trace.SysMin.LineBuffer", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("lineidx", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("linebuf", new Proto.Arr(Proto.Elm.newCNum("(xdc_Char)"), false, xdc.services.intern.xsr.Enum.intValue(0x100L)), $$DEFAULT, "w");
        // struct SysMin.Module_State
        po = (Proto.Obj)om.findStrict("ti.trace.SysMin$$Module_State", "ti.trace");
        po.init("ti.trace.SysMin.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("lineBuffers", new Proto.Arr((Proto)om.findStrict("ti.trace.SysMin.LineBuffer", "ti.trace"), false), $$DEFAULT, "w");
                po.addFld("outbuf", new Proto.Arr(Proto.Elm.newCNum("(xdc_Char)"), false), $$DEFAULT, "w");
                po.addFld("outidx", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("getTime", $$T_Bool, $$UNDEF, "w");
                po.addFld("wrapped", $$T_Bool, $$UNDEF, "w");
                po.addFld("writeidx", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false), $$DEFAULT, "w");
                po.addFld("readidx", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false), $$DEFAULT, "w");
    }

    void SysMin$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.trace.SysMin", "ti.trace");
        vo.bind("LineBuffer$fetchDesc", Global.newObject("type", "ti.trace.SysMin.LineBuffer", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.trace.SysMin$$LineBuffer", "ti.trace");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.trace.SysMin.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.trace.SysMin$$Module_State", "ti.trace");
        po.bind("lineBuffers$fetchDesc", Global.newObject("type", "ti.trace.SysMin.LineBuffer", "isScalar", false));
        po.bind("outbuf$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Char", "isScalar", true));
        po.bind("writeidx$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_UInt", "isScalar", true));
        po.bind("readidx$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_UInt", "isScalar", true));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.trace.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.trace"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/trace/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.trace"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.trace"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.trace"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.trace"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.trace"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.trace"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.trace", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.trace");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.trace.");
        pkgV.bind("$vers", Global.newArray(0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.trace'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.trace$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.trace$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.trace$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/ti.trace_smp.aem4',\n");
            sb.append("'lib/release/ti.trace_smp.aem4',\n");
            sb.append("'lib/debug/ti.trace_smp.aem4f',\n");
            sb.append("'lib/release/ti.trace_smp.aem4f',\n");
            sb.append("'lib/debug/ti.trace.aem4',\n");
            sb.append("'lib/release/ti.trace.aem4',\n");
            sb.append("'lib/debug/ti.trace.aem4f',\n");
            sb.append("'lib/release/ti.trace.aem4f',\n");
            sb.append("'lib/debug/ti.trace.ae66',\n");
            sb.append("'lib/release/ti.trace.ae66',\n");
            sb.append("'lib/debug/ti.trace.aearp32',\n");
            sb.append("'lib/release/ti.trace.aearp32',\n");
            sb.append("'lib/debug/ti.trace.aearp32F',\n");
            sb.append("'lib/release/ti.trace.aearp32F',\n");
            sb.append("'lib/debug/ti.trace.aa15fg',\n");
            sb.append("'lib/release/ti.trace.aa15fg',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/ti.trace_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.trace_smp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.trace_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.trace_smp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.trace.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.trace.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.trace.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.trace.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.trace.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/ti.trace.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/ti.trace.aearp32', {target: 'ti.targets.arp32.elf.ARP32', suffix: 'earp32'}],\n");
            sb.append("['lib/release/ti.trace.aearp32', {target: 'ti.targets.arp32.elf.ARP32', suffix: 'earp32'}],\n");
            sb.append("['lib/debug/ti.trace.aearp32F', {target: 'ti.targets.arp32.elf.ARP32_far', suffix: 'earp32F'}],\n");
            sb.append("['lib/release/ti.trace.aearp32F', {target: 'ti.targets.arp32.elf.ARP32_far', suffix: 'earp32F'}],\n");
            sb.append("['lib/debug/ti.trace.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/release/ti.trace.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void SysMin$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.trace.SysMin", "ti.trace");
        po = (Proto.Obj)om.findStrict("ti.trace.SysMin.Module", "ti.trace");
        vo.init2(po, "ti.trace.SysMin", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.trace.SysMin$$capsule", "ti.trace"));
        vo.bind("$package", om.findStrict("ti.trace", "ti.trace"));
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
        vo.bind("ModuleView", om.findStrict("ti.trace.SysMin.ModuleView", "ti.trace"));
        tdefs.add(om.findStrict("ti.trace.SysMin.ModuleView", "ti.trace"));
        vo.bind("BufferEntryView", om.findStrict("ti.trace.SysMin.BufferEntryView", "ti.trace"));
        tdefs.add(om.findStrict("ti.trace.SysMin.BufferEntryView", "ti.trace"));
        mcfgs.add("bufSize");
        mcfgs.add("flushAtExit");
        vo.bind("LineBuffer", om.findStrict("ti.trace.SysMin.LineBuffer", "ti.trace"));
        tdefs.add(om.findStrict("ti.trace.SysMin.LineBuffer", "ti.trace"));
        vo.bind("Module_State", om.findStrict("ti.trace.SysMin.Module_State", "ti.trace"));
        tdefs.add(om.findStrict("ti.trace.SysMin.Module_State", "ti.trace"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.trace")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("abort", om.findStrict("ti.trace.SysMin.abort", "ti.trace"));
        vo.bind("exit", om.findStrict("ti.trace.SysMin.exit", "ti.trace"));
        vo.bind("flush", om.findStrict("ti.trace.SysMin.flush", "ti.trace"));
        vo.bind("putch", om.findStrict("ti.trace.SysMin.putch", "ti.trace"));
        vo.bind("ready", om.findStrict("ti.trace.SysMin.ready", "ti.trace"));
        vo.bind("$$fxntab", Global.newArray("ti_trace_SysMin_Module__startupDone__E", "ti_trace_SysMin_abort__E", "ti_trace_SysMin_exit__E", "ti_trace_SysMin_flush__E", "ti_trace_SysMin_putch__E", "ti_trace_SysMin_ready__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./SysMin.xdt");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./SysMin.xdt");
        pkgV.bind("SysMin", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("SysMin");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.trace.SysMin", "ti.trace"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.trace.SysMin", "ti.trace");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Module", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE"), "viewInitFxn", "viewInitModule", "structName", "ModuleView")}), Global.newArray(new Object[]{"OutputBuffer", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE_DATA"), "viewInitFxn", "viewInitOutputBuffer", "structName", "BufferEntryView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.trace.SysMin")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.trace")).add(pkgV);
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
        SysMin$$OBJECTS();
        SysMin$$CONSTS();
        SysMin$$CREATES();
        SysMin$$FUNCTIONS();
        SysMin$$SIZES();
        SysMin$$TYPES();
        if (isROV) {
            SysMin$$ROV();
        }//isROV
        $$SINGLETONS();
        SysMin$$SINGLETONS();
        $$INITIALIZATION();
    }
}
