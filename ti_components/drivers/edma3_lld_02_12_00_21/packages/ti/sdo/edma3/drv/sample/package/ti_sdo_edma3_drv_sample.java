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

public class ti_sdo_edma3_drv_sample
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
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.hal");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.knl");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.edma3.drv");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.edma3.drv.sample.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.edma3.drv.sample", new Value.Obj("ti.sdo.edma3.drv.sample", pkgP));
    }

    void DrvSample$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.edma3.drv.sample.DrvSample.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.edma3.drv.sample.DrvSample", new Value.Obj("ti.sdo.edma3.drv.sample.DrvSample", po));
        pkgV.bind("DrvSample", vo);
        // decls 
    }

    void DrvSample$$CONSTS()
    {
        // module DrvSample
    }

    void DrvSample$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void DrvSample$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void DrvSample$$SIZES()
    {
    }

    void DrvSample$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.edma3.drv.sample.DrvSample.Module", "ti.sdo.edma3.drv.sample");
        po.init("ti.sdo.edma3.drv.sample.DrvSample.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
    }

    void DrvSample$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.edma3.drv.sample.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.edma3.drv.sample"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/edma3/drv/sample/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.edma3.drv.sample"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.edma3.drv.sample"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.edma3.drv.sample"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.edma3.drv.sample"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.edma3.drv.sample"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.edma3.drv.sample"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.edma3.drv.sample", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.edma3.drv.sample");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.edma3.drv.sample.");
        pkgV.bind("$vers", Global.newArray(02, 02, 15));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sysbios.hal", Global.newArray()));
        imports.add(Global.newArray("ti.sysbios.knl", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.edma3.drv", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.edma3.drv.sample'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.edma3.drv.sample$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.edma3.drv.sample$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.edma3.drv.sample$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/c6472-evm/64p/debug/ti.sdo.edma3.drv.sample.a64P',\n");
            sb.append("'lib/c6472-evm/64p/release/ti.sdo.edma3.drv.sample.a64P',\n");
            sb.append("'lib/tci6486-evm/64p/debug/ti.sdo.edma3.drv.sample.a64P',\n");
            sb.append("'lib/tci6486-evm/64p/release/ti.sdo.edma3.drv.sample.a64P',\n");
            sb.append("'lib/c6472-evm/64p/debug/ti.sdo.edma3.drv.sample.a64Pe',\n");
            sb.append("'lib/c6472-evm/64p/release/ti.sdo.edma3.drv.sample.a64Pe',\n");
            sb.append("'lib/tci6486-evm/64p/debug/ti.sdo.edma3.drv.sample.a64Pe',\n");
            sb.append("'lib/tci6486-evm/64p/release/ti.sdo.edma3.drv.sample.a64Pe',\n");
            sb.append("'lib/da830-evm/674/debug/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/da830-evm/674/release/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/c6748-evm/674/debug/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/c6748-evm/674/release/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/omapl137-evm/674/debug/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/omapl137-evm/674/release/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/omapl138-evm/674/debug/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/omapl138-evm/674/release/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/ti816x-sim/674/debug/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/ti816x-sim/674/release/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/ti816x-evm/674/debug/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/ti816x-evm/674/release/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/ti814x-evm/674/release/ti.sdo.edma3.drv.sample.a674',\n");
            sb.append("'lib/c6472-evm/64p/debug/ti.sdo.edma3.drv.sample.ae64P',\n");
            sb.append("'lib/c6472-evm/64p/release/ti.sdo.edma3.drv.sample.ae64P',\n");
            sb.append("'lib/tci6486-evm/64p/debug/ti.sdo.edma3.drv.sample.ae64P',\n");
            sb.append("'lib/tci6486-evm/64p/release/ti.sdo.edma3.drv.sample.ae64P',\n");
            sb.append("'lib/c6472-evm/64p/debug/ti.sdo.edma3.drv.sample.ae64Pe',\n");
            sb.append("'lib/c6472-evm/64p/release/ti.sdo.edma3.drv.sample.ae64Pe',\n");
            sb.append("'lib/tci6486-evm/64p/debug/ti.sdo.edma3.drv.sample.ae64Pe',\n");
            sb.append("'lib/tci6486-evm/64p/release/ti.sdo.edma3.drv.sample.ae64Pe',\n");
            sb.append("'lib/da830-evm/674/debug/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/da830-evm/674/release/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/c6748-evm/674/debug/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/c6748-evm/674/release/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/omapl137-evm/674/debug/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/omapl137-evm/674/release/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/omapl138-evm/674/debug/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/omapl138-evm/674/release/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/ti816x-sim/674/debug/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/ti816x-sim/674/release/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/ti816x-evm/674/debug/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/ti816x-evm/674/release/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/ti814x-evm/674/release/ti.sdo.edma3.drv.sample.ae674',\n");
            sb.append("'lib/tci6608-sim/66/debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6608-sim/66/release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6616-sim/66/debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6616-sim/66/release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6614-sim/66/debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6614-sim/66/release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/c6657-sim/66/debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/c6657-sim/66/release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6638k2k-sim/66/debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6638k2k-sim/66/release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/c6670-evm/66debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/c6670-evm/66release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/c6678-evm/66debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/c6678-evm/66release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6614-evm/66debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6614-evm/66release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/c6657-evm/66debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/c6657-evm/66release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6638k2k-evm/66debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6638k2k-evm/66release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6636k2h-evm/66debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6636k2h-evm/66release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6630k2l-evm/66debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6630k2l-evm/66release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/c66ak2e-evm/66debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/c66ak2e-evm/66release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci66ak2g02-evm/66debug/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci66ak2g02-evm/66release/ti.sdo.edma3.drv.sample.ae66',\n");
            sb.append("'lib/tci6608-sim/66/debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6608-sim/66/release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6616-sim/66/debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6616-sim/66/release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6614-sim/66/debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6614-sim/66/release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/c6657-sim/66/debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/c6657-sim/66/release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6638k2k-sim/66/debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6638k2k-sim/66/release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/c6670-evm/66debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/c6670-evm/66release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/c6678-evm/66debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/c6678-evm/66release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6614-evm/66debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6614-evm/66release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/c6657-evm/66debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/c6657-evm/66release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6638k2k-evm/66debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6638k2k-evm/66release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6636k2h-evm/66debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci6636k2h-evm/66release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci66ak2g02-evm/66debug/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/tci66ak2g02-evm/66release/ti.sdo.edma3.drv.sample.ae66e',\n");
            sb.append("'lib/omapl137-evm/arm9/debug/ti.sdo.edma3.drv.sample.ae9',\n");
            sb.append("'lib/omapl137-evm/arm9/release/ti.sdo.edma3.drv.sample.ae9',\n");
            sb.append("'lib/omapl138-evm/arm9/debug/ti.sdo.edma3.drv.sample.ae9',\n");
            sb.append("'lib/omapl138-evm/arm9/release/ti.sdo.edma3.drv.sample.ae9',\n");
            sb.append("'lib/am437x-evm/arm9/debug/ti.sdo.edma3.drv.sample.ae9',\n");
            sb.append("'lib/am437x-evm/arm9/release/ti.sdo.edma3.drv.sample.ae9',\n");
            sb.append("'lib/ti814x-evm/a8/debug/ti.sdo.edma3.drv.sample.aea8f',\n");
            sb.append("'lib/ti814x-evm/a8/release/ti.sdo.edma3.drv.sample.aea8f',\n");
            sb.append("'lib/am335x-evm/a8/debug/ti.sdo.edma3.drv.sample.aea8f',\n");
            sb.append("'lib/am335x-evm/a8/release/ti.sdo.edma3.drv.sample.aea8f',\n");
            sb.append("'lib/ti816x-evm/m3/debug/ti.sdo.edma3.drv.sample.aem3',\n");
            sb.append("'lib/ti816x-evm/m3/release/ti.sdo.edma3.drv.sample.aem3',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/c6472-evm/64p/debug/ti.sdo.edma3.drv.sample.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/c6472-evm/64p/release/ti.sdo.edma3.drv.sample.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/tci6486-evm/64p/debug/ti.sdo.edma3.drv.sample.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/tci6486-evm/64p/release/ti.sdo.edma3.drv.sample.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/c6472-evm/64p/debug/ti.sdo.edma3.drv.sample.a64Pe', {target: 'ti.targets.C64P_big_endian', suffix: '64Pe'}],\n");
            sb.append("['lib/c6472-evm/64p/release/ti.sdo.edma3.drv.sample.a64Pe', {target: 'ti.targets.C64P_big_endian', suffix: '64Pe'}],\n");
            sb.append("['lib/tci6486-evm/64p/debug/ti.sdo.edma3.drv.sample.a64Pe', {target: 'ti.targets.C64P_big_endian', suffix: '64Pe'}],\n");
            sb.append("['lib/tci6486-evm/64p/release/ti.sdo.edma3.drv.sample.a64Pe', {target: 'ti.targets.C64P_big_endian', suffix: '64Pe'}],\n");
            sb.append("['lib/da830-evm/674/debug/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/da830-evm/674/release/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/c6748-evm/674/debug/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/c6748-evm/674/release/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/omapl137-evm/674/debug/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/omapl137-evm/674/release/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/omapl138-evm/674/debug/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/omapl138-evm/674/release/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/ti816x-sim/674/debug/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/ti816x-sim/674/release/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/ti816x-evm/674/debug/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/ti816x-evm/674/release/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/ti814x-evm/674/release/ti.sdo.edma3.drv.sample.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/c6472-evm/64p/debug/ti.sdo.edma3.drv.sample.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/c6472-evm/64p/release/ti.sdo.edma3.drv.sample.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/tci6486-evm/64p/debug/ti.sdo.edma3.drv.sample.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/tci6486-evm/64p/release/ti.sdo.edma3.drv.sample.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/c6472-evm/64p/debug/ti.sdo.edma3.drv.sample.ae64Pe', {target: 'ti.targets.elf.C64P_big_endian', suffix: 'e64Pe'}],\n");
            sb.append("['lib/c6472-evm/64p/release/ti.sdo.edma3.drv.sample.ae64Pe', {target: 'ti.targets.elf.C64P_big_endian', suffix: 'e64Pe'}],\n");
            sb.append("['lib/tci6486-evm/64p/debug/ti.sdo.edma3.drv.sample.ae64Pe', {target: 'ti.targets.elf.C64P_big_endian', suffix: 'e64Pe'}],\n");
            sb.append("['lib/tci6486-evm/64p/release/ti.sdo.edma3.drv.sample.ae64Pe', {target: 'ti.targets.elf.C64P_big_endian', suffix: 'e64Pe'}],\n");
            sb.append("['lib/da830-evm/674/debug/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/da830-evm/674/release/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/c6748-evm/674/debug/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/c6748-evm/674/release/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/omapl137-evm/674/debug/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/omapl137-evm/674/release/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/omapl138-evm/674/debug/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/omapl138-evm/674/release/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/ti816x-sim/674/debug/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/ti816x-sim/674/release/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/ti816x-evm/674/debug/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/ti816x-evm/674/release/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/ti814x-evm/674/debug/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/ti814x-evm/674/release/ti.sdo.edma3.drv.sample.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/tci6608-sim/66/debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6608-sim/66/release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6616-sim/66/debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6616-sim/66/release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6614-sim/66/debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6614-sim/66/release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/c6657-sim/66/debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/c6657-sim/66/release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6638k2k-sim/66/debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6638k2k-sim/66/release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/c6670-evm/66debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/c6670-evm/66release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/c6678-evm/66debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/c6678-evm/66release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6614-evm/66debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6614-evm/66release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/c6657-evm/66debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/c6657-evm/66release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6638k2k-evm/66debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6638k2k-evm/66release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6636k2h-evm/66debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6636k2h-evm/66release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6630k2l-evm/66debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6630k2l-evm/66release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/c66ak2e-evm/66debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/c66ak2e-evm/66release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci66ak2g02-evm/66debug/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci66ak2g02-evm/66release/ti.sdo.edma3.drv.sample.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/tci6608-sim/66/debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6608-sim/66/release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6616-sim/66/debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6616-sim/66/release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6614-sim/66/debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6614-sim/66/release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/c6657-sim/66/debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/c6657-sim/66/release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6638k2k-sim/66/debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6638k2k-sim/66/release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/c6670-evm/66debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/c6670-evm/66release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/c6678-evm/66debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/c6678-evm/66release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6614-evm/66debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6614-evm/66release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/c6657-evm/66debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/c6657-evm/66release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6638k2k-evm/66debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6638k2k-evm/66release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6636k2h-evm/66debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci6636k2h-evm/66release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci66ak2g02-evm/66debug/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/tci66ak2g02-evm/66release/ti.sdo.edma3.drv.sample.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/omapl137-evm/arm9/debug/ti.sdo.edma3.drv.sample.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/omapl137-evm/arm9/release/ti.sdo.edma3.drv.sample.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/omapl138-evm/arm9/debug/ti.sdo.edma3.drv.sample.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/omapl138-evm/arm9/release/ti.sdo.edma3.drv.sample.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/am437x-evm/arm9/debug/ti.sdo.edma3.drv.sample.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/am437x-evm/arm9/release/ti.sdo.edma3.drv.sample.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/ti814x-evm/a8/debug/ti.sdo.edma3.drv.sample.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/ti814x-evm/a8/release/ti.sdo.edma3.drv.sample.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/am335x-evm/a8/debug/ti.sdo.edma3.drv.sample.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/am335x-evm/a8/release/ti.sdo.edma3.drv.sample.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/ti816x-evm/m3/debug/ti.sdo.edma3.drv.sample.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/ti816x-evm/m3/release/ti.sdo.edma3.drv.sample.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void DrvSample$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.edma3.drv.sample.DrvSample", "ti.sdo.edma3.drv.sample");
        po = (Proto.Obj)om.findStrict("ti.sdo.edma3.drv.sample.DrvSample.Module", "ti.sdo.edma3.drv.sample");
        vo.init2(po, "ti.sdo.edma3.drv.sample.DrvSample", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.edma3.drv.sample", "ti.sdo.edma3.drv.sample"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.edma3.drv.sample")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.edma3.drv.sample.DrvSample$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("DrvSample", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("DrvSample");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.edma3.drv.sample.DrvSample", "ti.sdo.edma3.drv.sample"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.edma3.drv.sample.DrvSample")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.edma3.drv.sample")).add(pkgV);
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
        DrvSample$$OBJECTS();
        DrvSample$$CONSTS();
        DrvSample$$CREATES();
        DrvSample$$FUNCTIONS();
        DrvSample$$SIZES();
        DrvSample$$TYPES();
        if (isROV) {
            DrvSample$$ROV();
        }//isROV
        $$SINGLETONS();
        DrvSample$$SINGLETONS();
        $$INITIALIZATION();
    }
}
