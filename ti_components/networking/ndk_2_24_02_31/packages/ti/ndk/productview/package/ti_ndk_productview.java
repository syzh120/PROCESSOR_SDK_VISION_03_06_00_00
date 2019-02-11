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

public class ti_ndk_productview
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
        Global.callFxn("loadPackage", xdcO, "xdc.tools.product");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.ndk.productview.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.ndk.productview", new Value.Obj("ti.ndk.productview", pkgP));
    }

    void NdkProductView$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.productview.NdkProductView.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.productview.NdkProductView", new Value.Obj("ti.ndk.productview.NdkProductView", po));
        pkgV.bind("NdkProductView", vo);
        // decls 
        om.bind("ti.ndk.productview.NdkProductView.ProductElemDesc", om.findStrict("xdc.tools.product.IProductView.ProductElemDesc", "ti.ndk.productview"));
    }

    void NdkProductView$$CONSTS()
    {
        // module NdkProductView
    }

    void NdkProductView$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void NdkProductView$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void NdkProductView$$SIZES()
    {
    }

    void NdkProductView$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/productview/NdkProductView.xs");
        om.bind("ti.ndk.productview.NdkProductView$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.productview.NdkProductView.Module", "ti.ndk.productview");
        po.init("ti.ndk.productview.NdkProductView.Module", om.findStrict("xdc.tools.product.IProductView.Module", "ti.ndk.productview"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("homeModule", $$T_Str, "ti.ndk.config.Global", "wh");
        po.addFld("linksToArray", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{}), "wh");
        po.addFld("ti_ndk_config_DhcpClient", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_DhcpServer", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Dns", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Emac", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Global", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Http", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Icmp", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Ip", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Nat", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Ppp", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Pppoe", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Route", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Tcp", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Telnet", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ti_ndk_config_Udp", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("applicationLayerGroup", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("transportLayerGroup", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("networkLayerGroup", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("datalinkLayerGroup", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        po.addFld("ndkProduct", (Proto)om.findStrict("ti.ndk.productview.NdkProductView.ProductElemDesc", "ti.ndk.productview"), $$DEFAULT, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.productview.NdkProductView$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.productview.NdkProductView$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.productview.NdkProductView$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getProductDescriptor");
                if (fxn != null) po.addFxn("getProductDescriptor", (Proto.Fxn)om.findStrict("xdc.tools.product.IProductView$$getProductDescriptor", "ti.ndk.productview"), fxn);
    }

    void NdkProductView$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.ndk.productview.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.ndk.productview"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.ndk.productview", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.ndk.productview");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.ndk.productview.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.ndk.productview'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.ndk.productview$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.ndk.productview$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.ndk.productview$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void NdkProductView$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.productview.NdkProductView", "ti.ndk.productview");
        po = (Proto.Obj)om.findStrict("ti.ndk.productview.NdkProductView.Module", "ti.ndk.productview");
        vo.init2(po, "ti.ndk.productview.NdkProductView", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.productview.NdkProductView$$capsule", "ti.ndk.productview"));
        vo.bind("$package", om.findStrict("ti.ndk.productview", "ti.ndk.productview"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("ProductElemDesc", om.findStrict("xdc.tools.product.IProductView.ProductElemDesc", "ti.ndk.productview"));
        tdefs.add(om.findStrict("xdc.tools.product.IProductView.ProductElemDesc", "ti.ndk.productview"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.tools.product");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.productview")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.productview.NdkProductView$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("NdkProductView", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("NdkProductView");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.productview.NdkProductView", "ti.ndk.productview"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.ndk.productview.NdkProductView")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.ndk.productview")).add(pkgV);
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
        NdkProductView$$OBJECTS();
        NdkProductView$$CONSTS();
        NdkProductView$$CREATES();
        NdkProductView$$FUNCTIONS();
        NdkProductView$$SIZES();
        NdkProductView$$TYPES();
        if (isROV) {
            NdkProductView$$ROV();
        }//isROV
        $$SINGLETONS();
        NdkProductView$$SINGLETONS();
        $$INITIALIZATION();
    }
}
