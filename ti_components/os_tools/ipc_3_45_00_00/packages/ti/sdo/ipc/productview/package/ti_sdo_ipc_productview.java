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

public class ti_sdo_ipc_productview
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
        Global.callFxn("loadPackage", xdcO, "xdc.tools.product");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ipc.productview.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ipc.productview", new Value.Obj("ti.sdo.ipc.productview", pkgP));
    }

    void IpcProductView$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ipc.productview.IpcProductView.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ipc.productview.IpcProductView", new Value.Obj("ti.sdo.ipc.productview.IpcProductView", po));
        pkgV.bind("IpcProductView", vo);
        // decls 
        om.bind("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", om.findStrict("xdc.tools.product.IProductView.ProductElemDesc", "ti.sdo.ipc.productview"));
    }

    void IpcProductView$$CONSTS()
    {
        // module IpcProductView
    }

    void IpcProductView$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IpcProductView$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IpcProductView$$SIZES()
    {
    }

    void IpcProductView$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ipc/productview/IpcProductView.xs");
        om.bind("ti.sdo.ipc.productview.IpcProductView$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.productview.IpcProductView.Module", "ti.sdo.ipc.productview");
        po.init("ti.sdo.ipc.productview.IpcProductView.Module", om.findStrict("xdc.tools.product.IProductView.Module", "ti.sdo.ipc.productview"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("ti_sdo_ipc_heaps_HeapMemMP", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ti_sdo_ipc_heaps_HeapBufMP", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ti_sdo_ipc_heaps_HeapMultiBufMP", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ti_sdo_ipc_Ipc", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ti_sdo_ipc_ListMP", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ti_sdo_ipc_GateMP", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ti_sdo_ipc_MessageQ", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ti_sdo_ipc_Notify", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ti_sdo_ipc_SharedRegion", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ti_sdo_utils_List", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ti_sdo_utils_NameServer", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ti_sdo_utils_MultiProc", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("multicoreGroup", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("utilsGroup", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("heapsGroup", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        po.addFld("ipcProduct", (Proto)om.findStrict("ti.sdo.ipc.productview.IpcProductView.ProductElemDesc", "ti.sdo.ipc.productview"), $$DEFAULT, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ipc.productview.IpcProductView$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ipc.productview.IpcProductView$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ipc.productview.IpcProductView$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getProductDescriptor");
                if (fxn != null) po.addFxn("getProductDescriptor", (Proto.Fxn)om.findStrict("xdc.tools.product.IProductView$$getProductDescriptor", "ti.sdo.ipc.productview"), fxn);
    }

    void IpcProductView$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ipc.productview.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ipc.productview"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.sdo.ipc.productview", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ipc.productview");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ipc.productview.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ipc.productview'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sdo.ipc.productview$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sdo.ipc.productview$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sdo.ipc.productview$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void IpcProductView$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ipc.productview.IpcProductView", "ti.sdo.ipc.productview");
        po = (Proto.Obj)om.findStrict("ti.sdo.ipc.productview.IpcProductView.Module", "ti.sdo.ipc.productview");
        vo.init2(po, "ti.sdo.ipc.productview.IpcProductView", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ipc.productview.IpcProductView$$capsule", "ti.sdo.ipc.productview"));
        vo.bind("$package", om.findStrict("ti.sdo.ipc.productview", "ti.sdo.ipc.productview"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("ProductElemDesc", om.findStrict("xdc.tools.product.IProductView.ProductElemDesc", "ti.sdo.ipc.productview"));
        tdefs.add(om.findStrict("xdc.tools.product.IProductView.ProductElemDesc", "ti.sdo.ipc.productview"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.tools.product");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ipc.productview")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ipc.productview.IpcProductView$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("IpcProductView", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IpcProductView");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ipc.productview.IpcProductView", "ti.sdo.ipc.productview"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ipc.productview.IpcProductView")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ipc.productview")).add(pkgV);
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
        IpcProductView$$OBJECTS();
        IpcProductView$$CONSTS();
        IpcProductView$$CREATES();
        IpcProductView$$FUNCTIONS();
        IpcProductView$$SIZES();
        IpcProductView$$TYPES();
        if (isROV) {
            IpcProductView$$ROV();
        }//isROV
        $$SINGLETONS();
        IpcProductView$$SINGLETONS();
        $$INITIALIZATION();
    }
}
