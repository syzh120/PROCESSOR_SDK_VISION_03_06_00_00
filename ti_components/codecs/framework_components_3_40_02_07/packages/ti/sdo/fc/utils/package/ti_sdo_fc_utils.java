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

public class ti_sdo_fc_utils
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.utils.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.utils", new Value.Obj("ti.sdo.fc.utils", pkgP));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.utils.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.utils"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/utils/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.utils"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.utils"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.utils"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.utils"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.utils"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.utils"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.utils", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.utils");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.utils.");
        pkgV.bind("$vers", Global.newArray(1, 0, 3));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.utils'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.fc.utils$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.fc.utils$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.fc.utils$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/rmm.a64P',\n");
            sb.append("'lib/release/rmm.a64P',\n");
            sb.append("'lib/notrace/rmm.a64P',\n");
            sb.append("'lib/debug/smgr.a64P',\n");
            sb.append("'lib/release/smgr.a64P',\n");
            sb.append("'lib/notrace/smgr.a64P',\n");
            sb.append("'lib/debug/rmmp.a64P',\n");
            sb.append("'lib/release/rmmp.a64P',\n");
            sb.append("'lib/notrace/rmmp.a64P',\n");
            sb.append("'lib/debug/fcutils.a64P',\n");
            sb.append("'lib/release/fcutils.a64P',\n");
            sb.append("'lib/notrace/fcutils.a64P',\n");
            sb.append("'lib/debug/rmm.a674',\n");
            sb.append("'lib/release/rmm.a674',\n");
            sb.append("'lib/notrace/rmm.a674',\n");
            sb.append("'lib/debug/smgr.a674',\n");
            sb.append("'lib/release/smgr.a674',\n");
            sb.append("'lib/notrace/smgr.a674',\n");
            sb.append("'lib/debug/rmmp.a674',\n");
            sb.append("'lib/release/rmmp.a674',\n");
            sb.append("'lib/notrace/rmmp.a674',\n");
            sb.append("'lib/debug/fcutils.a674',\n");
            sb.append("'lib/release/fcutils.a674',\n");
            sb.append("'lib/notrace/fcutils.a674',\n");
            sb.append("'lib/debug/rmm.aem3',\n");
            sb.append("'lib/release/rmm.aem3',\n");
            sb.append("'lib/notrace/rmm.aem3',\n");
            sb.append("'lib/debug/smgr.aem3',\n");
            sb.append("'lib/release/smgr.aem3',\n");
            sb.append("'lib/notrace/smgr.aem3',\n");
            sb.append("'lib/debug/rmmp.aem3',\n");
            sb.append("'lib/release/rmmp.aem3',\n");
            sb.append("'lib/notrace/rmmp.aem3',\n");
            sb.append("'lib/debug/fcutils.aem3',\n");
            sb.append("'lib/release/fcutils.aem3',\n");
            sb.append("'lib/notrace/fcutils.aem3',\n");
            sb.append("'lib/debug/rmm.aem4',\n");
            sb.append("'lib/release/rmm.aem4',\n");
            sb.append("'lib/notrace/rmm.aem4',\n");
            sb.append("'lib/debug/smgr.aem4',\n");
            sb.append("'lib/release/smgr.aem4',\n");
            sb.append("'lib/notrace/smgr.aem4',\n");
            sb.append("'lib/debug/rmmp.aem4',\n");
            sb.append("'lib/release/rmmp.aem4',\n");
            sb.append("'lib/notrace/rmmp.aem4',\n");
            sb.append("'lib/debug/fcutils.aem4',\n");
            sb.append("'lib/release/fcutils.aem4',\n");
            sb.append("'lib/notrace/fcutils.aem4',\n");
            sb.append("'lib/debug/rmm.ae64P',\n");
            sb.append("'lib/release/rmm.ae64P',\n");
            sb.append("'lib/notrace/rmm.ae64P',\n");
            sb.append("'lib/debug/smgr.ae64P',\n");
            sb.append("'lib/release/smgr.ae64P',\n");
            sb.append("'lib/notrace/smgr.ae64P',\n");
            sb.append("'lib/debug/rmmp.ae64P',\n");
            sb.append("'lib/release/rmmp.ae64P',\n");
            sb.append("'lib/notrace/rmmp.ae64P',\n");
            sb.append("'lib/debug/fcutils.ae64P',\n");
            sb.append("'lib/release/fcutils.ae64P',\n");
            sb.append("'lib/notrace/fcutils.ae64P',\n");
            sb.append("'lib/debug/rmm.ae64T',\n");
            sb.append("'lib/release/rmm.ae64T',\n");
            sb.append("'lib/notrace/rmm.ae64T',\n");
            sb.append("'lib/debug/smgr.ae64T',\n");
            sb.append("'lib/release/smgr.ae64T',\n");
            sb.append("'lib/notrace/smgr.ae64T',\n");
            sb.append("'lib/debug/rmmp.ae64T',\n");
            sb.append("'lib/release/rmmp.ae64T',\n");
            sb.append("'lib/notrace/rmmp.ae64T',\n");
            sb.append("'lib/debug/fcutils.ae64T',\n");
            sb.append("'lib/release/fcutils.ae64T',\n");
            sb.append("'lib/notrace/fcutils.ae64T',\n");
            sb.append("'lib/debug/rmm.ae66',\n");
            sb.append("'lib/release/rmm.ae66',\n");
            sb.append("'lib/notrace/rmm.ae66',\n");
            sb.append("'lib/debug/smgr.ae66',\n");
            sb.append("'lib/release/smgr.ae66',\n");
            sb.append("'lib/notrace/smgr.ae66',\n");
            sb.append("'lib/debug/rmmp.ae66',\n");
            sb.append("'lib/release/rmmp.ae66',\n");
            sb.append("'lib/notrace/rmmp.ae66',\n");
            sb.append("'lib/debug/fcutils.ae66',\n");
            sb.append("'lib/release/fcutils.ae66',\n");
            sb.append("'lib/notrace/fcutils.ae66',\n");
            sb.append("'lib/debug/rmm.ae66e',\n");
            sb.append("'lib/release/rmm.ae66e',\n");
            sb.append("'lib/notrace/rmm.ae66e',\n");
            sb.append("'lib/debug/smgr.ae66e',\n");
            sb.append("'lib/release/smgr.ae66e',\n");
            sb.append("'lib/notrace/smgr.ae66e',\n");
            sb.append("'lib/debug/rmmp.ae66e',\n");
            sb.append("'lib/release/rmmp.ae66e',\n");
            sb.append("'lib/notrace/rmmp.ae66e',\n");
            sb.append("'lib/debug/fcutils.ae66e',\n");
            sb.append("'lib/release/fcutils.ae66e',\n");
            sb.append("'lib/notrace/fcutils.ae66e',\n");
            sb.append("'lib/debug/rmm.ae674',\n");
            sb.append("'lib/release/rmm.ae674',\n");
            sb.append("'lib/notrace/rmm.ae674',\n");
            sb.append("'lib/debug/smgr.ae674',\n");
            sb.append("'lib/release/smgr.ae674',\n");
            sb.append("'lib/notrace/smgr.ae674',\n");
            sb.append("'lib/debug/rmmp.ae674',\n");
            sb.append("'lib/release/rmmp.ae674',\n");
            sb.append("'lib/notrace/rmmp.ae674',\n");
            sb.append("'lib/debug/fcutils.ae674',\n");
            sb.append("'lib/release/fcutils.ae674',\n");
            sb.append("'lib/notrace/fcutils.ae674',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/rmm.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/release/rmm.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/notrace/rmm.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/debug/smgr.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/release/smgr.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/notrace/smgr.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/debug/rmmp.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/release/rmmp.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/notrace/rmmp.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/debug/fcutils.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/release/fcutils.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/notrace/fcutils.a64P', {target: 'ti.targets.C64P', suffix: '64P'}],\n");
            sb.append("['lib/debug/rmm.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/release/rmm.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/notrace/rmm.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/debug/smgr.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/release/smgr.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/notrace/smgr.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/debug/rmmp.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/release/rmmp.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/notrace/rmmp.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/debug/fcutils.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/release/fcutils.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/notrace/fcutils.a674', {target: 'ti.targets.C674', suffix: '674'}],\n");
            sb.append("['lib/debug/rmm.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/rmm.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/notrace/rmm.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/smgr.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/smgr.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/notrace/smgr.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/rmmp.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/rmmp.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/notrace/rmmp.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/fcutils.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/fcutils.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/notrace/fcutils.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/rmm.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/rmm.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/notrace/rmm.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/smgr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/smgr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/notrace/smgr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/rmmp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/rmmp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/notrace/rmmp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/fcutils.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/fcutils.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/notrace/fcutils.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/rmm.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/release/rmm.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/notrace/rmm.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/debug/smgr.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/release/smgr.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/notrace/smgr.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/debug/rmmp.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/release/rmmp.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/notrace/rmmp.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/debug/fcutils.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/release/fcutils.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/notrace/fcutils.ae64P', {target: 'ti.targets.elf.C64P', suffix: 'e64P'}],\n");
            sb.append("['lib/debug/rmm.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/release/rmm.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/notrace/rmm.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/debug/smgr.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/release/smgr.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/notrace/smgr.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/debug/rmmp.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/release/rmmp.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/notrace/rmmp.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/debug/fcutils.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/release/fcutils.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/notrace/fcutils.ae64T', {target: 'ti.targets.elf.C64T', suffix: 'e64T'}],\n");
            sb.append("['lib/debug/rmm.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/rmm.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/notrace/rmm.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/smgr.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/smgr.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/notrace/smgr.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/rmmp.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/rmmp.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/notrace/rmmp.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/fcutils.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/fcutils.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/notrace/fcutils.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/rmm.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/release/rmm.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/notrace/rmm.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/debug/smgr.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/release/smgr.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/notrace/smgr.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/debug/rmmp.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/release/rmmp.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/notrace/rmmp.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/debug/fcutils.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/release/fcutils.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/notrace/fcutils.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/debug/rmm.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/rmm.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/notrace/rmm.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/smgr.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/smgr.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/notrace/smgr.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/rmmp.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/rmmp.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/notrace/rmmp.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/fcutils.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/fcutils.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/notrace/fcutils.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.utils")).add(pkgV);
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
        if (isROV) {
        }//isROV
        $$SINGLETONS();
        $$INITIALIZATION();
    }
}
