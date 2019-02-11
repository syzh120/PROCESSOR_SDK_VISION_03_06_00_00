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

public class ti_ipc_ipcmgr
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
        pkgP = (Proto.Obj)om.bind("ti.ipc.ipcmgr.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.ipc.ipcmgr", new Value.Obj("ti.ipc.ipcmgr", pkgP));
    }

    void IpcMgr$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ipc.ipcmgr.IpcMgr.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ipc.ipcmgr.IpcMgr", new Value.Obj("ti.ipc.ipcmgr.IpcMgr", po));
        pkgV.bind("IpcMgr", vo);
        // decls 
        om.bind("ti.ipc.ipcmgr.IpcMgr.TransCombo", new Proto.Enm("ti.ipc.ipcmgr.IpcMgr.TransCombo"));
    }

    void IpcMgr$$CONSTS()
    {
        // module IpcMgr
        om.bind("ti.ipc.ipcmgr.IpcMgr.TransCombo_RPMSG", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ipc.ipcmgr.IpcMgr.TransCombo", "ti.ipc.ipcmgr"), "ti.ipc.ipcmgr.IpcMgr.TransCombo_RPMSG", 0));
        om.bind("ti.ipc.ipcmgr.IpcMgr.TransCombo_RPMSG_MESSAGEQ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ipc.ipcmgr.IpcMgr.TransCombo", "ti.ipc.ipcmgr"), "ti.ipc.ipcmgr.IpcMgr.TransCombo_RPMSG_MESSAGEQ", 1));
        om.bind("ti.ipc.ipcmgr.IpcMgr.TransCombo_RPMSG_IPC", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ipc.ipcmgr.IpcMgr.TransCombo", "ti.ipc.ipcmgr"), "ti.ipc.ipcmgr.IpcMgr.TransCombo_RPMSG_IPC", 2));
    }

    void IpcMgr$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IpcMgr$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn IpcMgr.getDefs
        fxn = (Proto.Fxn)om.bind("ti.ipc.ipcmgr.IpcMgr$$getDefs", new Proto.Fxn(om.findStrict("ti.ipc.ipcmgr.IpcMgr.Module", "ti.ipc.ipcmgr"), $$T_Str, 0, 0, false));
    }

    void IpcMgr$$SIZES()
    {
    }

    void IpcMgr$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/ipcmgr/IpcMgr.xs");
        om.bind("ti.ipc.ipcmgr.IpcMgr$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ipc.ipcmgr.IpcMgr.Module", "ti.ipc.ipcmgr");
        po.init("ti.ipc.ipcmgr.IpcMgr.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("transportCombo", (Proto)om.findStrict("ti.ipc.ipcmgr.IpcMgr.TransCombo", "ti.ipc.ipcmgr"), $$UNDEF, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ipc.ipcmgr.IpcMgr$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ipc.ipcmgr.IpcMgr$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ipc.ipcmgr.IpcMgr$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("getDefs", (Proto.Fxn)om.findStrict("ti.ipc.ipcmgr.IpcMgr$$getDefs", "ti.ipc.ipcmgr"), Global.get(cap, "getDefs"));
    }

    void IpcMgr$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.ipc.ipcmgr.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.ipc.ipcmgr"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ipc/ipcmgr/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.ipc.ipcmgr"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.ipc.ipcmgr"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.ipc.ipcmgr"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.ipc.ipcmgr"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.ipc.ipcmgr"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.ipc.ipcmgr"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.ipc.ipcmgr", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.ipc.ipcmgr");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.ipc.ipcmgr.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.ipc.ipcmgr'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.ipc.ipcmgr$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.ipc.ipcmgr$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.ipc.ipcmgr$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/ti.ipc.ipcmgr.aem4',\n");
            sb.append("'lib/debug/ti.ipc.ipcmgr_deh.aem4',\n");
            sb.append("'lib/release/ti.ipc.ipcmgr.aem4',\n");
            sb.append("'lib/release/ti.ipc.ipcmgr_deh.aem4',\n");
            sb.append("'lib/debug/ti.ipc.ipcmgr.aem4f',\n");
            sb.append("'lib/debug/ti.ipc.ipcmgr_deh.aem4f',\n");
            sb.append("'lib/release/ti.ipc.ipcmgr.aem4f',\n");
            sb.append("'lib/release/ti.ipc.ipcmgr_deh.aem4f',\n");
            sb.append("'lib/debug/ti.ipc.ipcmgr.ae66',\n");
            sb.append("'lib/debug/ti.ipc.ipcmgr_deh.ae66',\n");
            sb.append("'lib/release/ti.ipc.ipcmgr.ae66',\n");
            sb.append("'lib/release/ti.ipc.ipcmgr_deh.ae66',\n");
            sb.append("'lib/debug/ti.ipc.ipcmgr.aearp32',\n");
            sb.append("'lib/release/ti.ipc.ipcmgr.aearp32',\n");
            sb.append("'lib/debug/ti.ipc.ipcmgr.aearp32F',\n");
            sb.append("'lib/release/ti.ipc.ipcmgr.aearp32F',\n");
            sb.append("'lib/debug/ti.ipc.ipcmgr.aa15fg',\n");
            sb.append("'lib/release/ti.ipc.ipcmgr.aa15fg',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/ti.ipc.ipcmgr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.ipc.ipcmgr_deh.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.ipc.ipcmgr.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/release/ti.ipc.ipcmgr_deh.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/debug/ti.ipc.ipcmgr.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.ipc.ipcmgr_deh.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.ipc.ipcmgr.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/release/ti.ipc.ipcmgr_deh.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/debug/ti.ipc.ipcmgr.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/ti.ipc.ipcmgr_deh.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/ti.ipc.ipcmgr.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/release/ti.ipc.ipcmgr_deh.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/debug/ti.ipc.ipcmgr.aearp32', {target: 'ti.targets.arp32.elf.ARP32', suffix: 'earp32'}],\n");
            sb.append("['lib/release/ti.ipc.ipcmgr.aearp32', {target: 'ti.targets.arp32.elf.ARP32', suffix: 'earp32'}],\n");
            sb.append("['lib/debug/ti.ipc.ipcmgr.aearp32F', {target: 'ti.targets.arp32.elf.ARP32_far', suffix: 'earp32F'}],\n");
            sb.append("['lib/release/ti.ipc.ipcmgr.aearp32F', {target: 'ti.targets.arp32.elf.ARP32_far', suffix: 'earp32F'}],\n");
            sb.append("['lib/debug/ti.ipc.ipcmgr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/release/ti.ipc.ipcmgr.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void IpcMgr$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ipc.ipcmgr.IpcMgr", "ti.ipc.ipcmgr");
        po = (Proto.Obj)om.findStrict("ti.ipc.ipcmgr.IpcMgr.Module", "ti.ipc.ipcmgr");
        vo.init2(po, "ti.ipc.ipcmgr.IpcMgr", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ipc.ipcmgr.IpcMgr$$capsule", "ti.ipc.ipcmgr"));
        vo.bind("$package", om.findStrict("ti.ipc.ipcmgr", "ti.ipc.ipcmgr"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("TransCombo", om.findStrict("ti.ipc.ipcmgr.IpcMgr.TransCombo", "ti.ipc.ipcmgr"));
        vo.bind("TransCombo_RPMSG", om.findStrict("ti.ipc.ipcmgr.IpcMgr.TransCombo_RPMSG", "ti.ipc.ipcmgr"));
        vo.bind("TransCombo_RPMSG_MESSAGEQ", om.findStrict("ti.ipc.ipcmgr.IpcMgr.TransCombo_RPMSG_MESSAGEQ", "ti.ipc.ipcmgr"));
        vo.bind("TransCombo_RPMSG_IPC", om.findStrict("ti.ipc.ipcmgr.IpcMgr.TransCombo_RPMSG_IPC", "ti.ipc.ipcmgr"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ipc.ipcmgr")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ipc.ipcmgr.IpcMgr$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("IpcMgr", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IpcMgr");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ipc.ipcmgr.IpcMgr", "ti.ipc.ipcmgr"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.ipc.ipcmgr.IpcMgr")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.ipc.ipcmgr")).add(pkgV);
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
        IpcMgr$$OBJECTS();
        IpcMgr$$CONSTS();
        IpcMgr$$CREATES();
        IpcMgr$$FUNCTIONS();
        IpcMgr$$SIZES();
        IpcMgr$$TYPES();
        if (isROV) {
            IpcMgr$$ROV();
        }//isROV
        $$SINGLETONS();
        IpcMgr$$SINGLETONS();
        $$INITIALIZATION();
    }
}
