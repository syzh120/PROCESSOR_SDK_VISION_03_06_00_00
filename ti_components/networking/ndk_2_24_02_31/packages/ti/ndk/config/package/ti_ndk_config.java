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

public class ti_ndk_config
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
        pkgP = (Proto.Obj)om.bind("ti.ndk.config.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.ndk.config", new Value.Obj("ti.ndk.config", pkgP));
    }

    void Global$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Global.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Global", new Value.Obj("ti.ndk.config.Global", po));
        pkgV.bind("Global", vo);
        // decls 
        om.bind("ti.ndk.config.Global.NetEventSchedPri", new Proto.Enm("ti.ndk.config.Global.NetEventSchedPri"));
        om.bind("ti.ndk.config.Global.NetEventSchedOp", new Proto.Enm("ti.ndk.config.Global.NetEventSchedOp"));
        om.bind("ti.ndk.config.Global.DebugLevel", new Proto.Enm("ti.ndk.config.Global.DebugLevel"));
        om.bind("ti.ndk.config.Global.StackLibProtocol", new Proto.Enm("ti.ndk.config.Global.StackLibProtocol"));
        spo = (Proto.Obj)om.bind("ti.ndk.config.Global$$Account", new Proto.Obj());
        om.bind("ti.ndk.config.Global.Account", new Proto.Str(spo, true));
    }

    void Http$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Http.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Http", new Value.Obj("ti.ndk.config.Http", po));
        pkgV.bind("Http", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.ndk.config.Http.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.ndk.config.Http$$Object", new Proto.Obj());
        om.bind("ti.ndk.config.Http.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.ndk.config.Http$$Params", new Proto.Obj());
        om.bind("ti.ndk.config.Http.Params", new Proto.Str(po, true));
    }

    void Telnet$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Telnet.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Telnet", new Value.Obj("ti.ndk.config.Telnet", po));
        pkgV.bind("Telnet", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.ndk.config.Telnet.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.ndk.config.Telnet$$Object", new Proto.Obj());
        om.bind("ti.ndk.config.Telnet.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.ndk.config.Telnet$$Params", new Proto.Obj());
        om.bind("ti.ndk.config.Telnet.Params", new Proto.Str(po, true));
    }

    void DhcpClient$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.DhcpClient.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.DhcpClient", new Value.Obj("ti.ndk.config.DhcpClient", po));
        pkgV.bind("DhcpClient", vo);
        // decls 
    }

    void DhcpServer$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.DhcpServer.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.DhcpServer", new Value.Obj("ti.ndk.config.DhcpServer", po));
        pkgV.bind("DhcpServer", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.ndk.config.DhcpServer.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.ndk.config.DhcpServer$$Object", new Proto.Obj());
        om.bind("ti.ndk.config.DhcpServer.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.ndk.config.DhcpServer$$Params", new Proto.Obj());
        om.bind("ti.ndk.config.DhcpServer.Params", new Proto.Str(po, true));
    }

    void Dns$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Dns.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Dns", new Value.Obj("ti.ndk.config.Dns", po));
        pkgV.bind("Dns", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.ndk.config.Dns.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.ndk.config.Dns$$Object", new Proto.Obj());
        om.bind("ti.ndk.config.Dns.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.ndk.config.Dns$$Params", new Proto.Obj());
        om.bind("ti.ndk.config.Dns.Params", new Proto.Str(po, true));
    }

    void Nat$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Nat.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Nat", new Value.Obj("ti.ndk.config.Nat", po));
        pkgV.bind("Nat", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.ndk.config.Nat.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.ndk.config.Nat$$Object", new Proto.Obj());
        om.bind("ti.ndk.config.Nat.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.ndk.config.Nat$$Params", new Proto.Obj());
        om.bind("ti.ndk.config.Nat.Params", new Proto.Str(po, true));
    }

    void Tcp$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Tcp.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Tcp", new Value.Obj("ti.ndk.config.Tcp", po));
        pkgV.bind("Tcp", vo);
        // decls 
    }

    void Ip$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Ip.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Ip", new Value.Obj("ti.ndk.config.Ip", po));
        pkgV.bind("Ip", vo);
        // decls 
    }

    void Route$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Route.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Route", new Value.Obj("ti.ndk.config.Route", po));
        pkgV.bind("Route", vo);
        // decls 
    }

    void Icmp$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Icmp.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Icmp", new Value.Obj("ti.ndk.config.Icmp", po));
        pkgV.bind("Icmp", vo);
        // decls 
    }

    void Udp$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Udp.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Udp", new Value.Obj("ti.ndk.config.Udp", po));
        pkgV.bind("Udp", vo);
        // decls 
    }

    void Emac$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Emac.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Emac", new Value.Obj("ti.ndk.config.Emac", po));
        pkgV.bind("Emac", vo);
        // decls 
        om.bind("ti.ndk.config.Emac.DeviceSupport", new Proto.Enm("ti.ndk.config.Emac.DeviceSupport"));
    }

    void Ppp$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Ppp.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Ppp", new Value.Obj("ti.ndk.config.Ppp", po));
        pkgV.bind("Ppp", vo);
        // decls 
    }

    void Pppoe$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.ndk.config.Pppoe.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.ndk.config.Pppoe", new Value.Obj("ti.ndk.config.Pppoe", po));
        pkgV.bind("Pppoe", vo);
        // decls 
    }

    void Global$$CONSTS()
    {
        // module Global
        om.bind("ti.ndk.config.Global.NC_PRIORITY_LOW", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.NetEventSchedPri", "ti.ndk.config"), "ti.ndk.config.Global.NC_PRIORITY_LOW", 0));
        om.bind("ti.ndk.config.Global.NC_PRIORITY_HIGH", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.NetEventSchedPri", "ti.ndk.config"), "ti.ndk.config.Global.NC_PRIORITY_HIGH", 1));
        om.bind("ti.ndk.config.Global.NC_OPMODE_POLLING", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.NetEventSchedOp", "ti.ndk.config"), "ti.ndk.config.Global.NC_OPMODE_POLLING", 0));
        om.bind("ti.ndk.config.Global.NC_OPMODE_INTERRUPT", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.NetEventSchedOp", "ti.ndk.config"), "ti.ndk.config.Global.NC_OPMODE_INTERRUPT", 1));
        om.bind("ti.ndk.config.Global.DBG_INFO", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.DebugLevel", "ti.ndk.config"), "ti.ndk.config.Global.DBG_INFO", xdc.services.intern.xsr.Enum.intValue(1L)+0));
        om.bind("ti.ndk.config.Global.DBG_WARN", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.DebugLevel", "ti.ndk.config"), "ti.ndk.config.Global.DBG_WARN", xdc.services.intern.xsr.Enum.intValue(om.findStrict("ti.ndk.config.Global.DBG_INFO", "ti.ndk.config"))+1));
        om.bind("ti.ndk.config.Global.DBG_ERROR", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.DebugLevel", "ti.ndk.config"), "ti.ndk.config.Global.DBG_ERROR", xdc.services.intern.xsr.Enum.intValue(om.findStrict("ti.ndk.config.Global.DBG_INFO", "ti.ndk.config"))+2));
        om.bind("ti.ndk.config.Global.DBG_NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.DebugLevel", "ti.ndk.config"), "ti.ndk.config.Global.DBG_NONE", xdc.services.intern.xsr.Enum.intValue(om.findStrict("ti.ndk.config.Global.DBG_INFO", "ti.ndk.config"))+3));
        om.bind("ti.ndk.config.Global.NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.StackLibProtocol", "ti.ndk.config"), "ti.ndk.config.Global.NONE", 0));
        om.bind("ti.ndk.config.Global.NAT", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.StackLibProtocol", "ti.ndk.config"), "ti.ndk.config.Global.NAT", 1));
        om.bind("ti.ndk.config.Global.NAT_PPP", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.StackLibProtocol", "ti.ndk.config"), "ti.ndk.config.Global.NAT_PPP", 2));
        om.bind("ti.ndk.config.Global.NAT_PPP_PPPOE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.StackLibProtocol", "ti.ndk.config"), "ti.ndk.config.Global.NAT_PPP_PPPOE", 3));
        om.bind("ti.ndk.config.Global.PPP", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.StackLibProtocol", "ti.ndk.config"), "ti.ndk.config.Global.PPP", 4));
        om.bind("ti.ndk.config.Global.PPP_PPPOE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.StackLibProtocol", "ti.ndk.config"), "ti.ndk.config.Global.PPP_PPPOE", 5));
        om.bind("ti.ndk.config.Global.MIN", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Global.StackLibProtocol", "ti.ndk.config"), "ti.ndk.config.Global.MIN", 6));
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_0", 0x1L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_1", 0x2L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_2", 0x4L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_3", 0x8L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_4", 0x10L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_5", 0x20L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_6", 0x40L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_7", 0x80L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_8", 0x100L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_9", 0x200L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_10", 0x400L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_11", 0x800L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_12", 0x1000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_13", 0x2000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_14", 0x4000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_15", 0x8000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_16", 0x10000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_17", 0x20000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_18", 0x40000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_19", 0x80000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_20", 0x100000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_21", 0x200000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_22", 0x400000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_23", 0x800000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_24", 0x1000000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_25", 0x2000000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_26", 0x4000000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_27", 0x8000000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_28", 0x10000000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_29", 0x20000000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_30", 0x40000000L);
        om.bind("ti.ndk.config.Global.STACKRUN_FLG_CORE_31", 0x80000000L);
        om.bind("ti.ndk.config.Global.defaultDebugPrintLevel", om.find("ti.ndk.config.Global.DBG_INFO"));
        om.bind("ti.ndk.config.Global.defaultDebugAbortLevel", om.find("ti.ndk.config.Global.DBG_ERROR"));
        om.bind("ti.ndk.config.Global.defaultLowTaskPriLevel", 3L);
        om.bind("ti.ndk.config.Global.defaultNormTaskPriLevel", 5L);
        om.bind("ti.ndk.config.Global.defaultHighTaskPriLevel", 7L);
        om.bind("ti.ndk.config.Global.defaultKernTaskPriLevel", 9L);
        om.bind("ti.ndk.config.Global.defaultLowTaskStackSize", 3072L);
        om.bind("ti.ndk.config.Global.defaultNormTaskStackSize", 4096L);
        om.bind("ti.ndk.config.Global.defaultHighTaskStackSize", 5120L);
        om.bind("ti.ndk.config.Global.defaultNdkTaskStackSize", 8192L);
        om.bind("ti.ndk.config.Global.defaultNdkTickPeriod", 100L);
    }

    void Http$$CONSTS()
    {
        // module Http
        om.bind("ti.ndk.config.Http.CIS_FLG_IFIDXVALID", 0x0001L);
        om.bind("ti.ndk.config.Http.CIS_FLG_RESOLVEIP", 0x0002L);
        om.bind("ti.ndk.config.Http.CIS_FLG_CALLBYIP", 0x0004L);
        om.bind("ti.ndk.config.Http.CIS_FLG_RESTARTIPTERM", 0x0008L);
    }

    void Telnet$$CONSTS()
    {
        // module Telnet
        om.bind("ti.ndk.config.Telnet.CIS_FLG_IFIDXVALID", 0x0001L);
        om.bind("ti.ndk.config.Telnet.CIS_FLG_RESOLVEIP", 0x0002L);
        om.bind("ti.ndk.config.Telnet.CIS_FLG_CALLBYIP", 0x0004L);
        om.bind("ti.ndk.config.Telnet.CIS_FLG_RESTARTIPTERM", 0x0008L);
    }

    void DhcpClient$$CONSTS()
    {
        // module DhcpClient
    }

    void DhcpServer$$CONSTS()
    {
        // module DhcpServer
        om.bind("ti.ndk.config.DhcpServer.DHCPS_FLG_LOCALDNS", 0x0001L);
        om.bind("ti.ndk.config.DhcpServer.DHCPS_FLG_LOCALDOMAIN", 0x0002L);
    }

    void Dns$$CONSTS()
    {
        // module Dns
        om.bind("ti.ndk.config.Dns.CIS_FLG_IFIDXVALID", 0x0001L);
        om.bind("ti.ndk.config.Dns.CIS_FLG_RESOLVEIP", 0x0002L);
        om.bind("ti.ndk.config.Dns.CIS_FLG_CALLBYIP", 0x0004L);
        om.bind("ti.ndk.config.Dns.CIS_FLG_RESTARTIPTERM", 0x0008L);
    }

    void Nat$$CONSTS()
    {
        // module Nat
        om.bind("ti.ndk.config.Nat.CIS_FLG_IFIDXVALID", 0x0001L);
        om.bind("ti.ndk.config.Nat.CIS_FLG_RESOLVEIP", 0x0002L);
        om.bind("ti.ndk.config.Nat.CIS_FLG_CALLBYIP", 0x0004L);
        om.bind("ti.ndk.config.Nat.CIS_FLG_RESTARTIPTERM", 0x0008L);
    }

    void Tcp$$CONSTS()
    {
        // module Tcp
        om.bind("ti.ndk.config.Tcp.defaultMaxReasmPkts", 2L);
        om.bind("ti.ndk.config.Tcp.defaultTxBufSize", 8192L);
        om.bind("ti.ndk.config.Tcp.defaultRxBufSize", 8192L);
        om.bind("ti.ndk.config.Tcp.defaultRxBufLimit", 8192L);
        om.bind("ti.ndk.config.Tcp.defaultKeepIdleTime", 72000L);
        om.bind("ti.ndk.config.Tcp.defaultKpProbIntv", 750L);
        om.bind("ti.ndk.config.Tcp.defaultKpProbTimeout", 6000L);
    }

    void Ip$$CONSTS()
    {
        // module Ip
        om.bind("ti.ndk.config.Ip.defaultStartIndex", 1L);
        om.bind("ti.ndk.config.Ip.defaultPortForwarding", false);
        om.bind("ti.ndk.config.Ip.defaultPortFiltering", false);
        om.bind("ti.ndk.config.Ip.defaultMaxReasmTime", 10L);
        om.bind("ti.ndk.config.Ip.defaultMaxReasmSize", 3020L);
        om.bind("ti.ndk.config.Ip.defaultIcmpDoRedir", true);
        om.bind("ti.ndk.config.Ip.defaultIcmpTTL", 64L);
        om.bind("ti.ndk.config.Ip.defaultIcmpTTLecho", 255L);
        om.bind("ti.ndk.config.Ip.defaultIcmpBcastReply", false);
        om.bind("ti.ndk.config.Ip.defaultIcmpMcastReply", false);
        om.bind("ti.ndk.config.Ip.defaultDirBcast", true);
        om.bind("ti.ndk.config.Ip.defaultRteDownTime", 20L);
        om.bind("ti.ndk.config.Ip.defaultRteKpAliveTime", 1200L);
        om.bind("ti.ndk.config.Ip.defaultRteCloneTimeout", 120L);
        om.bind("ti.ndk.config.Ip.defaultRteMtu", 64L);
        om.bind("ti.ndk.config.Ip.defaultRteCtrlDbg", false);
        om.bind("ti.ndk.config.Ip.defaultRteAdverPer", 0L);
        om.bind("ti.ndk.config.Ip.defaultRteAdverLife", 120L);
        om.bind("ti.ndk.config.Ip.defaultRteAdverLvl", 0L);
        om.bind("ti.ndk.config.Ip.defaultSockTTL", 64L);
        om.bind("ti.ndk.config.Ip.defaultSockTos", 0L);
        om.bind("ti.ndk.config.Ip.defaultSockMaxConn", 8L);
        om.bind("ti.ndk.config.Ip.defaultSockConnTimeout", 80L);
        om.bind("ti.ndk.config.Ip.defaultSockIoTimeout", 0L);
        om.bind("ti.ndk.config.Ip.defaultSockBufTxSz", 2048L);
        om.bind("ti.ndk.config.Ip.defaultSockBufRxSz", 1L);
        om.bind("ti.ndk.config.Ip.defaultPipIoTimeout", 0L);
        om.bind("ti.ndk.config.Ip.defaultPipMaxBufSz", 1024L);
        om.bind("ti.ndk.config.Ip.defaultPipBufTxSz", 256L);
        om.bind("ti.ndk.config.Ip.defaultPipBufRxSz", 1L);
        om.bind("ti.ndk.config.Ip.CIS_FLG_IFIDXVALID", 0x0001L);
        om.bind("ti.ndk.config.Ip.CIS_FLG_RESOLVEIP", 0x0002L);
        om.bind("ti.ndk.config.Ip.CIS_FLG_CALLBYIP", 0x0004L);
        om.bind("ti.ndk.config.Ip.CIS_FLG_RESTARTIPTERM", 0x0008L);
    }

    void Route$$CONSTS()
    {
        // module Route
    }

    void Icmp$$CONSTS()
    {
        // module Icmp
    }

    void Udp$$CONSTS()
    {
        // module Udp
        om.bind("ti.ndk.config.Udp.defaultRxBufSize", 8192L);
    }

    void Emac$$CONSTS()
    {
        // module Emac
        om.bind("ti.ndk.config.Emac.EVMOMAPL138", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Emac.DeviceSupport", "ti.ndk.config"), "ti.ndk.config.Emac.EVMOMAPL138", 0));
        om.bind("ti.ndk.config.Emac.TMDXDOCKH52C1", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Emac.DeviceSupport", "ti.ndk.config"), "ti.ndk.config.Emac.TMDXDOCKH52C1", 1));
        om.bind("ti.ndk.config.Emac.DK_LM3S9D96", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Emac.DeviceSupport", "ti.ndk.config"), "ti.ndk.config.Emac.DK_LM3S9D96", 2));
        om.bind("ti.ndk.config.Emac.NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.ndk.config.Emac.DeviceSupport", "ti.ndk.config"), "ti.ndk.config.Emac.NONE", 3));
    }

    void Ppp$$CONSTS()
    {
        // module Ppp
    }

    void Pppoe$$CONSTS()
    {
        // module Pppoe
    }

    void Global$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Http$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.ndk.config.Http$$create", new Proto.Fxn(om.findStrict("ti.ndk.config.Http.Module", "ti.ndk.config"), om.findStrict("ti.ndk.config.Http.Instance", "ti.ndk.config"), 1, 0, false));
                fxn.addArg(0, "__params", (Proto)om.findStrict("ti.ndk.config.Http.Params", "ti.ndk.config"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$ndk$config$Http$$create = function( __params ) {\n");
            sb.append("var __mod = xdc.om['ti.ndk.config.Http'];\n");
            sb.append("var __inst = xdc.om['ti.ndk.config.Http.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.ndk.config']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cgiFunctions = __mod.PARAMS.cgiFunctions;\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.ndk.config.Http$$construct", new Proto.Fxn(om.findStrict("ti.ndk.config.Http.Module", "ti.ndk.config"), null, 2, 0, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.ndk.config.Http$$Object", "ti.ndk.config"), null);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.ndk.config.Http.Params", "ti.ndk.config"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$ndk$config$Http$$construct = function( __obj, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.ndk.config.Http'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cgiFunctions = __mod.PARAMS.cgiFunctions;\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Telnet$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.ndk.config.Telnet$$create", new Proto.Fxn(om.findStrict("ti.ndk.config.Telnet.Module", "ti.ndk.config"), om.findStrict("ti.ndk.config.Telnet.Instance", "ti.ndk.config"), 1, 0, false));
                fxn.addArg(0, "__params", (Proto)om.findStrict("ti.ndk.config.Telnet.Params", "ti.ndk.config"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$ndk$config$Telnet$$create = function( __params ) {\n");
            sb.append("var __mod = xdc.om['ti.ndk.config.Telnet'];\n");
            sb.append("var __inst = xdc.om['ti.ndk.config.Telnet.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.ndk.config']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.ndk.config.Telnet$$construct", new Proto.Fxn(om.findStrict("ti.ndk.config.Telnet.Module", "ti.ndk.config"), null, 2, 0, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.ndk.config.Telnet$$Object", "ti.ndk.config"), null);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.ndk.config.Telnet.Params", "ti.ndk.config"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$ndk$config$Telnet$$construct = function( __obj, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.ndk.config.Telnet'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void DhcpClient$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void DhcpServer$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.ndk.config.DhcpServer$$create", new Proto.Fxn(om.findStrict("ti.ndk.config.DhcpServer.Module", "ti.ndk.config"), om.findStrict("ti.ndk.config.DhcpServer.Instance", "ti.ndk.config"), 1, 0, false));
                fxn.addArg(0, "__params", (Proto)om.findStrict("ti.ndk.config.DhcpServer.Params", "ti.ndk.config"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$ndk$config$DhcpServer$$create = function( __params ) {\n");
            sb.append("var __mod = xdc.om['ti.ndk.config.DhcpServer'];\n");
            sb.append("var __inst = xdc.om['ti.ndk.config.DhcpServer.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.ndk.config']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.ndk.config.DhcpServer$$construct", new Proto.Fxn(om.findStrict("ti.ndk.config.DhcpServer.Module", "ti.ndk.config"), null, 2, 0, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.ndk.config.DhcpServer$$Object", "ti.ndk.config"), null);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.ndk.config.DhcpServer.Params", "ti.ndk.config"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$ndk$config$DhcpServer$$construct = function( __obj, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.ndk.config.DhcpServer'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Dns$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.ndk.config.Dns$$create", new Proto.Fxn(om.findStrict("ti.ndk.config.Dns.Module", "ti.ndk.config"), om.findStrict("ti.ndk.config.Dns.Instance", "ti.ndk.config"), 1, 0, false));
                fxn.addArg(0, "__params", (Proto)om.findStrict("ti.ndk.config.Dns.Params", "ti.ndk.config"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$ndk$config$Dns$$create = function( __params ) {\n");
            sb.append("var __mod = xdc.om['ti.ndk.config.Dns'];\n");
            sb.append("var __inst = xdc.om['ti.ndk.config.Dns.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.ndk.config']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.ndk.config.Dns$$construct", new Proto.Fxn(om.findStrict("ti.ndk.config.Dns.Module", "ti.ndk.config"), null, 2, 0, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.ndk.config.Dns$$Object", "ti.ndk.config"), null);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.ndk.config.Dns.Params", "ti.ndk.config"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$ndk$config$Dns$$construct = function( __obj, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.ndk.config.Dns'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Nat$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.ndk.config.Nat$$create", new Proto.Fxn(om.findStrict("ti.ndk.config.Nat.Module", "ti.ndk.config"), om.findStrict("ti.ndk.config.Nat.Instance", "ti.ndk.config"), 1, 0, false));
                fxn.addArg(0, "__params", (Proto)om.findStrict("ti.ndk.config.Nat.Params", "ti.ndk.config"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$ndk$config$Nat$$create = function( __params ) {\n");
            sb.append("var __mod = xdc.om['ti.ndk.config.Nat'];\n");
            sb.append("var __inst = xdc.om['ti.ndk.config.Nat.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.ndk.config']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.ndk.config.Nat$$construct", new Proto.Fxn(om.findStrict("ti.ndk.config.Nat.Module", "ti.ndk.config"), null, 2, 0, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.ndk.config.Nat$$Object", "ti.ndk.config"), null);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.ndk.config.Nat.Params", "ti.ndk.config"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$ndk$config$Nat$$construct = function( __obj, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.ndk.config.Nat'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Tcp$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Ip$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Route$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Icmp$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Udp$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Emac$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Ppp$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Pppoe$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Global$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Global.addUserAccount
        fxn = (Proto.Fxn)om.bind("ti.ndk.config.Global$$addUserAccount", new Proto.Fxn(om.findStrict("ti.ndk.config.Global.Module", "ti.ndk.config"), null, 1, 1, false));
                fxn.addArg(0, "account", (Proto)om.findStrict("ti.ndk.config.Global.Account", "ti.ndk.config"), $$DEFAULT);
    }

    void Http$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Telnet$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void DhcpClient$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void DhcpServer$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Dns$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Nat$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Tcp$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Ip$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Route$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Icmp$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Udp$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Emac$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Ppp$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Pppoe$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Global$$SIZES()
    {
    }

    void Http$$SIZES()
    {
    }

    void Telnet$$SIZES()
    {
    }

    void DhcpClient$$SIZES()
    {
    }

    void DhcpServer$$SIZES()
    {
    }

    void Dns$$SIZES()
    {
    }

    void Nat$$SIZES()
    {
    }

    void Tcp$$SIZES()
    {
    }

    void Ip$$SIZES()
    {
    }

    void Route$$SIZES()
    {
    }

    void Icmp$$SIZES()
    {
    }

    void Udp$$SIZES()
    {
    }

    void Emac$$SIZES()
    {
    }

    void Ppp$$SIZES()
    {
    }

    void Pppoe$$SIZES()
    {
    }

    void Global$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/Global.xs");
        om.bind("ti.ndk.config.Global$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Global.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Global.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("STACKRUN_FLG_CORE_0", Proto.Elm.newCNum("(xdc_Bits32)"), 0x1L, "rh");
                po.addFld("STACKRUN_FLG_CORE_1", Proto.Elm.newCNum("(xdc_Bits32)"), 0x2L, "rh");
                po.addFld("STACKRUN_FLG_CORE_2", Proto.Elm.newCNum("(xdc_Bits32)"), 0x4L, "rh");
                po.addFld("STACKRUN_FLG_CORE_3", Proto.Elm.newCNum("(xdc_Bits32)"), 0x8L, "rh");
                po.addFld("STACKRUN_FLG_CORE_4", Proto.Elm.newCNum("(xdc_Bits32)"), 0x10L, "rh");
                po.addFld("STACKRUN_FLG_CORE_5", Proto.Elm.newCNum("(xdc_Bits32)"), 0x20L, "rh");
                po.addFld("STACKRUN_FLG_CORE_6", Proto.Elm.newCNum("(xdc_Bits32)"), 0x40L, "rh");
                po.addFld("STACKRUN_FLG_CORE_7", Proto.Elm.newCNum("(xdc_Bits32)"), 0x80L, "rh");
                po.addFld("STACKRUN_FLG_CORE_8", Proto.Elm.newCNum("(xdc_Bits32)"), 0x100L, "rh");
                po.addFld("STACKRUN_FLG_CORE_9", Proto.Elm.newCNum("(xdc_Bits32)"), 0x200L, "rh");
                po.addFld("STACKRUN_FLG_CORE_10", Proto.Elm.newCNum("(xdc_Bits32)"), 0x400L, "rh");
                po.addFld("STACKRUN_FLG_CORE_11", Proto.Elm.newCNum("(xdc_Bits32)"), 0x800L, "rh");
                po.addFld("STACKRUN_FLG_CORE_12", Proto.Elm.newCNum("(xdc_Bits32)"), 0x1000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_13", Proto.Elm.newCNum("(xdc_Bits32)"), 0x2000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_14", Proto.Elm.newCNum("(xdc_Bits32)"), 0x4000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_15", Proto.Elm.newCNum("(xdc_Bits32)"), 0x8000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_16", Proto.Elm.newCNum("(xdc_Bits32)"), 0x10000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_17", Proto.Elm.newCNum("(xdc_Bits32)"), 0x20000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_18", Proto.Elm.newCNum("(xdc_Bits32)"), 0x40000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_19", Proto.Elm.newCNum("(xdc_Bits32)"), 0x80000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_20", Proto.Elm.newCNum("(xdc_Bits32)"), 0x100000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_21", Proto.Elm.newCNum("(xdc_Bits32)"), 0x200000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_22", Proto.Elm.newCNum("(xdc_Bits32)"), 0x400000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_23", Proto.Elm.newCNum("(xdc_Bits32)"), 0x800000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_24", Proto.Elm.newCNum("(xdc_Bits32)"), 0x1000000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_25", Proto.Elm.newCNum("(xdc_Bits32)"), 0x2000000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_26", Proto.Elm.newCNum("(xdc_Bits32)"), 0x4000000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_27", Proto.Elm.newCNum("(xdc_Bits32)"), 0x8000000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_28", Proto.Elm.newCNum("(xdc_Bits32)"), 0x10000000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_29", Proto.Elm.newCNum("(xdc_Bits32)"), 0x20000000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_30", Proto.Elm.newCNum("(xdc_Bits32)"), 0x40000000L, "rh");
                po.addFld("STACKRUN_FLG_CORE_31", Proto.Elm.newCNum("(xdc_Bits32)"), 0x80000000L, "rh");
                po.addFld("defaultDebugPrintLevel", (Proto)om.findStrict("ti.ndk.config.Global.DebugLevel", "ti.ndk.config"), om.find("ti.ndk.config.Global.DBG_INFO"), "rh");
                po.addFld("defaultDebugAbortLevel", (Proto)om.findStrict("ti.ndk.config.Global.DebugLevel", "ti.ndk.config"), om.find("ti.ndk.config.Global.DBG_ERROR"), "rh");
                po.addFld("defaultLowTaskPriLevel", Proto.Elm.newCNum("(xdc_Int)"), 3L, "rh");
                po.addFld("defaultNormTaskPriLevel", Proto.Elm.newCNum("(xdc_Int)"), 5L, "rh");
                po.addFld("defaultHighTaskPriLevel", Proto.Elm.newCNum("(xdc_Int)"), 7L, "rh");
                po.addFld("defaultKernTaskPriLevel", Proto.Elm.newCNum("(xdc_Int)"), 9L, "rh");
                po.addFld("defaultLowTaskStackSize", Proto.Elm.newCNum("(xdc_Int)"), 3072L, "rh");
                po.addFld("defaultNormTaskStackSize", Proto.Elm.newCNum("(xdc_Int)"), 4096L, "rh");
                po.addFld("defaultHighTaskStackSize", Proto.Elm.newCNum("(xdc_Int)"), 5120L, "rh");
                po.addFld("defaultNdkTaskStackSize", Proto.Elm.newCNum("(xdc_Int)"), 8192L, "rh");
                po.addFld("defaultNdkTickPeriod", Proto.Elm.newCNum("(xdc_Int)"), 100L, "rh");
        po.addFld("userAccounts", new Proto.Arr((Proto)om.findStrict("ti.ndk.config.Global.Account", "ti.ndk.config"), true), Global.newArray(new Object[]{}), "wh");
        po.addFld("multiCoreStackRunMode", Proto.Elm.newCNum("(xdc_Bits32)"), 0x1L, "wh");
        po.addFld("IPv6", $$T_Bool, true, "wh");
        po.addFld("stackLibType", (Proto)om.findStrict("ti.ndk.config.Global.StackLibProtocol", "ti.ndk.config"), om.find("ti.ndk.config.Global.NONE"), "wh");
        po.addFld("useSemLibs", $$T_Bool, false, "wh");
        po.addFld("debugPrintLevel", (Proto)om.findStrict("ti.ndk.config.Global.DebugLevel", "ti.ndk.config"), om.find("ti.ndk.config.Global.DBG_INFO"), "wh");
        po.addFld("debugAbortLevel", (Proto)om.findStrict("ti.ndk.config.Global.DebugLevel", "ti.ndk.config"), om.find("ti.ndk.config.Global.DBG_ERROR"), "wh");
        po.addFld("lowTaskPriLevel", Proto.Elm.newCNum("(xdc_Int)"), 3L, "wh");
        po.addFld("normTaskPriLevel", Proto.Elm.newCNum("(xdc_Int)"), 5L, "wh");
        po.addFld("highTaskPriLevel", Proto.Elm.newCNum("(xdc_Int)"), 7L, "wh");
        po.addFld("kernTaskPriLevel", Proto.Elm.newCNum("(xdc_Int)"), 9L, "wh");
        po.addFld("lowTaskStackSize", Proto.Elm.newCNum("(xdc_Int)"), 3072L, "wh");
        po.addFld("normTaskStackSize", Proto.Elm.newCNum("(xdc_Int)"), 4096L, "wh");
        po.addFld("highTaskStackSize", Proto.Elm.newCNum("(xdc_Int)"), 5120L, "wh");
        po.addFld("enableCodeGeneration", $$T_Bool, true, "wh");
        po.addFld("autoOpenCloseFD", $$T_Bool, false, "wh");
        po.addFld("stackThreadUser", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), null, "wh");
        po.addFld("ndkThreadPri", Proto.Elm.newCNum("(xdc_Int)"), 5L, "wh");
        po.addFld("ndkThreadStackSize", Proto.Elm.newCNum("(xdc_Int)"), 8192L, "wh");
        po.addFld("ndkTickPeriod", Proto.Elm.newCNum("(xdc_Int)"), 100L, "wh");
        po.addFld("netSchedulerPri", (Proto)om.findStrict("ti.ndk.config.Global.NetEventSchedPri", "ti.ndk.config"), om.find("ti.ndk.config.Global.NC_PRIORITY_LOW"), "wh");
        po.addFld("netSchedulerOpMode", (Proto)om.findStrict("ti.ndk.config.Global.NetEventSchedOp", "ti.ndk.config"), om.find("ti.ndk.config.Global.NC_OPMODE_INTERRUPT"), "wh");
        po.addFld("realm1Name", $$T_Str, null, "wh");
        po.addFld("realm2Name", $$T_Str, null, "wh");
        po.addFld("realm3Name", $$T_Str, null, "wh");
        po.addFld("realm4Name", $$T_Str, null, "wh");
        po.addFld("pktNumFrameBufs", Proto.Elm.newCNum("(xdc_Int)"), 192L, "wh");
        po.addFld("pktSizeFrameBuf", Proto.Elm.newCNum("(xdc_Int)"), 1536L, "wh");
        po.addFld("pbmDataSection", $$T_Str, ".far:NDK_PACKETMEM", "wh");
        po.addFld("memRawPageSize", Proto.Elm.newCNum("(xdc_Int)"), 3072L, "wh");
        po.addFld("memRawPageCount", Proto.Elm.newCNum("(xdc_Int)"), 16L, "wh");
        po.addFld("memDataSection", $$T_Str, ".far:NDK_MMBUFFER", "wh");
        po.addFld("stackBeginHook", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), null, "wh");
        po.addFld("stackInitHook", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), null, "wh");
        po.addFld("stackRebootHook", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), null, "wh");
        po.addFld("stackDeleteHook", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), null, "wh");
        po.addFld("serviceReportHook", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), null, "wh");
        po.addFld("networkOpenHook", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), null, "wh");
        po.addFld("networkCloseHook", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), null, "wh");
        po.addFld("networkIPAddrHook", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), null, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.Global$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Global$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.Global$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("addUserAccount", (Proto.Fxn)om.findStrict("ti.ndk.config.Global$$addUserAccount", "ti.ndk.config"), Global.get(cap, "addUserAccount"));
        // struct Global.Account
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Global$$Account", "ti.ndk.config");
        po.init("ti.ndk.config.Global.Account", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("username", $$T_Str, $$UNDEF, "w");
                po.addFld("password", $$T_Str, $$UNDEF, "w");
        // typedef Global.ndkHookFxn
        om.bind("ti.ndk.config.Global.ndkHookFxn", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"));
        // typedef Global.StackRunModeFlags
        om.bind("ti.ndk.config.Global.StackRunModeFlags", Proto.Elm.newCNum("(xdc_Bits32)"));
    }

    void Http$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/Http.xs");
        om.bind("ti.ndk.config.Http$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Http.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Http.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.ndk.config.Http$$create", "ti.ndk.config"), Global.get("ti$ndk$config$Http$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.ndk.config.Http$$construct", "ti.ndk.config"), Global.get("ti$ndk$config$Http$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.Http$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Http$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Http$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.Http$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Http.Instance", "ti.ndk.config");
        po.init("ti.ndk.config.Http.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
        po.addFld("maxCon", Proto.Elm.newCNum("(xdc_Int)"), 8L, "wh");
        po.addFld("port", Proto.Elm.newCNum("(xdc_Int)"), 80L, "wh");
        po.addFld("mode", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "wh");
        po.addFld("ifIdx", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("ipAddr", $$T_Str, "INADDR_ANY", "wh");
        po.addFld("pCbSrv", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"), "&ti_ndk_config_Global_serviceReport", "wh");
        po.addFld("cgiFunctions", new Proto.Map($$T_Str), $$DEFAULT, "wh");
        po.addFld("IfIdXValid", $$T_Bool, false, "wh");
        po.addFld("ResolveIP", $$T_Bool, false, "wh");
        po.addFld("CallByIP", $$T_Bool, false, "wh");
        po.addFld("RestartIPTerm", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Http$$Params", "ti.ndk.config");
        po.init("ti.ndk.config.Http.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
        po.addFld("maxCon", Proto.Elm.newCNum("(xdc_Int)"), 8L, "wh");
        po.addFld("port", Proto.Elm.newCNum("(xdc_Int)"), 80L, "wh");
        po.addFld("mode", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "wh");
        po.addFld("ifIdx", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("ipAddr", $$T_Str, "INADDR_ANY", "wh");
        po.addFld("pCbSrv", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"), "&ti_ndk_config_Global_serviceReport", "wh");
        po.addFld("cgiFunctions", new Proto.Map($$T_Str), $$DEFAULT, "wh");
        po.addFld("IfIdXValid", $$T_Bool, false, "wh");
        po.addFld("ResolveIP", $$T_Bool, false, "wh");
        po.addFld("CallByIP", $$T_Bool, false, "wh");
        po.addFld("RestartIPTerm", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Http$$Object", "ti.ndk.config");
        po.init("ti.ndk.config.Http.Object", om.findStrict("ti.ndk.config.Http.Instance", "ti.ndk.config"));
        // typedef Http.httpServiceFxn
        om.bind("ti.ndk.config.Http.httpServiceFxn", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"));
        // typedef Http.CisFlags
        om.bind("ti.ndk.config.Http.CisFlags", Proto.Elm.newCNum("(xdc_Bits16)"));
    }

    void Telnet$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/Telnet.xs");
        om.bind("ti.ndk.config.Telnet$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Telnet.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Telnet.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.ndk.config.Telnet$$create", "ti.ndk.config"), Global.get("ti$ndk$config$Telnet$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.ndk.config.Telnet$$construct", "ti.ndk.config"), Global.get("ti$ndk$config$Telnet$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.Telnet$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Telnet$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Telnet$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.Telnet$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Telnet.Instance", "ti.ndk.config");
        po.init("ti.ndk.config.Telnet.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
        po.addFld("maxCon", Proto.Elm.newCNum("(xdc_Int)"), 8L, "wh");
        po.addFld("port", Proto.Elm.newCNum("(xdc_Int)"), 23L, "wh");
        po.addFld("mode", Proto.Elm.newCNum("(xdc_Int)"), 0L, "wh");
        po.addFld("ifIdx", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("ipAddr", $$T_Str, "INADDR_ANY", "wh");
        po.addFld("pCbSrv", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"), "&ti_ndk_config_Global_serviceReport", "wh");
        po.addFld("callBackFxn", new Proto.Adr("xdc_Int(*)(xdc_Void*)", "PFn"), null, "wh");
        po.addFld("IfIdXValid", $$T_Bool, false, "wh");
        po.addFld("ResolveIP", $$T_Bool, false, "wh");
        po.addFld("CallByIP", $$T_Bool, false, "wh");
        po.addFld("RestartIPTerm", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Telnet$$Params", "ti.ndk.config");
        po.init("ti.ndk.config.Telnet.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
        po.addFld("maxCon", Proto.Elm.newCNum("(xdc_Int)"), 8L, "wh");
        po.addFld("port", Proto.Elm.newCNum("(xdc_Int)"), 23L, "wh");
        po.addFld("mode", Proto.Elm.newCNum("(xdc_Int)"), 0L, "wh");
        po.addFld("ifIdx", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("ipAddr", $$T_Str, "INADDR_ANY", "wh");
        po.addFld("pCbSrv", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"), "&ti_ndk_config_Global_serviceReport", "wh");
        po.addFld("callBackFxn", new Proto.Adr("xdc_Int(*)(xdc_Void*)", "PFn"), null, "wh");
        po.addFld("IfIdXValid", $$T_Bool, false, "wh");
        po.addFld("ResolveIP", $$T_Bool, false, "wh");
        po.addFld("CallByIP", $$T_Bool, false, "wh");
        po.addFld("RestartIPTerm", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Telnet$$Object", "ti.ndk.config");
        po.init("ti.ndk.config.Telnet.Object", om.findStrict("ti.ndk.config.Telnet.Instance", "ti.ndk.config"));
        // typedef Telnet.telnetServiceFxn
        om.bind("ti.ndk.config.Telnet.telnetServiceFxn", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"));
        // typedef Telnet.telnetCallbackFxn
        om.bind("ti.ndk.config.Telnet.telnetCallbackFxn", new Proto.Adr("xdc_Int(*)(xdc_Void*)", "PFn"));
        // typedef Telnet.CisFlags
        om.bind("ti.ndk.config.Telnet.CisFlags", Proto.Elm.newCNum("(xdc_Bits16)"));
    }

    void DhcpClient$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/DhcpClient.xs");
        om.bind("ti.ndk.config.DhcpClient$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.DhcpClient.Module", "ti.ndk.config");
        po.init("ti.ndk.config.DhcpClient.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.DhcpClient$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.DhcpClient$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.DhcpClient$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void DhcpServer$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/DhcpServer.xs");
        om.bind("ti.ndk.config.DhcpServer$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.DhcpServer.Module", "ti.ndk.config");
        po.init("ti.ndk.config.DhcpServer.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("DHCPS_FLG_LOCALDNS", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("DHCPS_FLG_LOCALDOMAIN", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.ndk.config.DhcpServer$$create", "ti.ndk.config"), Global.get("ti$ndk$config$DhcpServer$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.ndk.config.DhcpServer$$construct", "ti.ndk.config"), Global.get("ti$ndk$config$DhcpServer$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.DhcpServer$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.DhcpServer$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.DhcpServer$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.DhcpServer$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.DhcpServer.Instance", "ti.ndk.config");
        po.init("ti.ndk.config.DhcpServer.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("DHCPS_FLG_LOCALDNS", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("DHCPS_FLG_LOCALDOMAIN", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
        po.addFld("ipAddrPoolBase", $$T_Str, "192.168.1.2", "wh");
        po.addFld("ipAddrPoolCount", Proto.Elm.newCNum("(xdc_Int)"), 253L, "wh");
        po.addFld("ifIdx", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("pCbSrv", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"), "&ti_ndk_config_Global_serviceReport", "wh");
        po.addFld("localDNS", $$T_Bool, false, "wh");
        po.addFld("localDomain", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.DhcpServer$$Params", "ti.ndk.config");
        po.init("ti.ndk.config.DhcpServer.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("DHCPS_FLG_LOCALDNS", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("DHCPS_FLG_LOCALDOMAIN", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
        po.addFld("ipAddrPoolBase", $$T_Str, "192.168.1.2", "wh");
        po.addFld("ipAddrPoolCount", Proto.Elm.newCNum("(xdc_Int)"), 253L, "wh");
        po.addFld("ifIdx", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("pCbSrv", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"), "&ti_ndk_config_Global_serviceReport", "wh");
        po.addFld("localDNS", $$T_Bool, false, "wh");
        po.addFld("localDomain", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.DhcpServer$$Object", "ti.ndk.config");
        po.init("ti.ndk.config.DhcpServer.Object", om.findStrict("ti.ndk.config.DhcpServer.Instance", "ti.ndk.config"));
        // typedef DhcpServer.dhcpServerServiceFxn
        om.bind("ti.ndk.config.DhcpServer.dhcpServerServiceFxn", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"));
        // typedef DhcpServer.DhcpServerFlag
        om.bind("ti.ndk.config.DhcpServer.DhcpServerFlag", Proto.Elm.newCNum("(xdc_Bits16)"));
    }

    void Dns$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/Dns.xs");
        om.bind("ti.ndk.config.Dns$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Dns.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Dns.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
        po.addFld("externDnsServIp", $$T_Str, null, "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.ndk.config.Dns$$create", "ti.ndk.config"), Global.get("ti$ndk$config$Dns$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.ndk.config.Dns$$construct", "ti.ndk.config"), Global.get("ti$ndk$config$Dns$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.Dns$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Dns$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Dns$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.Dns$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Dns.Instance", "ti.ndk.config");
        po.init("ti.ndk.config.Dns.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
        po.addFld("mode", Proto.Elm.newCNum("(xdc_Bits16)"), 0L, "wh");
        po.addFld("ifIdx", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("ipAddr", $$T_Str, "INADDR_ANY", "wh");
        po.addFld("pCbSrv", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"), "&ti_ndk_config_Global_serviceReport", "wh");
        po.addFld("IfIdXValid", $$T_Bool, false, "wh");
        po.addFld("ResolveIP", $$T_Bool, false, "wh");
        po.addFld("CallByIP", $$T_Bool, false, "wh");
        po.addFld("RestartIPTerm", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Dns$$Params", "ti.ndk.config");
        po.init("ti.ndk.config.Dns.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
        po.addFld("mode", Proto.Elm.newCNum("(xdc_Bits16)"), 0L, "wh");
        po.addFld("ifIdx", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("ipAddr", $$T_Str, "INADDR_ANY", "wh");
        po.addFld("pCbSrv", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"), "&ti_ndk_config_Global_serviceReport", "wh");
        po.addFld("IfIdXValid", $$T_Bool, false, "wh");
        po.addFld("ResolveIP", $$T_Bool, false, "wh");
        po.addFld("CallByIP", $$T_Bool, false, "wh");
        po.addFld("RestartIPTerm", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Dns$$Object", "ti.ndk.config");
        po.init("ti.ndk.config.Dns.Object", om.findStrict("ti.ndk.config.Dns.Instance", "ti.ndk.config"));
        // typedef Dns.dnsServiceFxn
        om.bind("ti.ndk.config.Dns.dnsServiceFxn", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"));
        // typedef Dns.CisFlags
        om.bind("ti.ndk.config.Dns.CisFlags", Proto.Elm.newCNum("(xdc_Bits16)"));
    }

    void Nat$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/Nat.xs");
        om.bind("ti.ndk.config.Nat$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Nat.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Nat.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.ndk.config.Nat$$create", "ti.ndk.config"), Global.get("ti$ndk$config$Nat$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.ndk.config.Nat$$construct", "ti.ndk.config"), Global.get("ti$ndk$config$Nat$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.Nat$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Nat$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Nat$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.Nat$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Nat.Instance", "ti.ndk.config");
        po.init("ti.ndk.config.Nat.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
        po.addFld("virtualIpAddr", $$T_Str, null, "wh");
        po.addFld("virtualMask", $$T_Str, "255.255.254.0", "wh");
        po.addFld("mtu", Proto.Elm.newCNum("(xdc_Int)"), 1500L, "wh");
        po.addFld("mode", Proto.Elm.newCNum("(xdc_Int)"), 0L, "wh");
        po.addFld("ifIdx", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("pCbSrv", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"), "&ti_ndk_config_Global_serviceReport", "wh");
        po.addFld("IfIdXValid", $$T_Bool, false, "wh");
        po.addFld("ResolveIP", $$T_Bool, false, "wh");
        po.addFld("CallByIP", $$T_Bool, false, "wh");
        po.addFld("RestartIPTerm", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Nat$$Params", "ti.ndk.config");
        po.init("ti.ndk.config.Nat.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
        po.addFld("virtualIpAddr", $$T_Str, null, "wh");
        po.addFld("virtualMask", $$T_Str, "255.255.254.0", "wh");
        po.addFld("mtu", Proto.Elm.newCNum("(xdc_Int)"), 1500L, "wh");
        po.addFld("mode", Proto.Elm.newCNum("(xdc_Int)"), 0L, "wh");
        po.addFld("ifIdx", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("pCbSrv", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"), "&ti_ndk_config_Global_serviceReport", "wh");
        po.addFld("IfIdXValid", $$T_Bool, false, "wh");
        po.addFld("ResolveIP", $$T_Bool, false, "wh");
        po.addFld("CallByIP", $$T_Bool, false, "wh");
        po.addFld("RestartIPTerm", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Nat$$Object", "ti.ndk.config");
        po.init("ti.ndk.config.Nat.Object", om.findStrict("ti.ndk.config.Nat.Instance", "ti.ndk.config"));
        // typedef Nat.natServiceFxn
        om.bind("ti.ndk.config.Nat.natServiceFxn", new Proto.Adr("xdc_Void(*)(xdc_Int,xdc_Int,xdc_Int,xdc_Void*)", "PFv"));
        // typedef Nat.CisFlags
        om.bind("ti.ndk.config.Nat.CisFlags", Proto.Elm.newCNum("(xdc_Bits16)"));
    }

    void Tcp$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/Tcp.xs");
        om.bind("ti.ndk.config.Tcp$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Tcp.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Tcp.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("defaultMaxReasmPkts", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("defaultTxBufSize", Proto.Elm.newCNum("(xdc_Int)"), 8192L, "rh");
                po.addFld("defaultRxBufSize", Proto.Elm.newCNum("(xdc_Int)"), 8192L, "rh");
                po.addFld("defaultRxBufLimit", Proto.Elm.newCNum("(xdc_Int)"), 8192L, "rh");
                po.addFld("defaultKeepIdleTime", Proto.Elm.newCNum("(xdc_Int)"), 72000L, "rh");
                po.addFld("defaultKpProbIntv", Proto.Elm.newCNum("(xdc_Int)"), 750L, "rh");
                po.addFld("defaultKpProbTimeout", Proto.Elm.newCNum("(xdc_Int)"), 6000L, "rh");
        po.addFld("maxNumReasmPkts", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
        po.addFld("transmitBufSize", Proto.Elm.newCNum("(xdc_Int)"), 8192L, "wh");
        po.addFld("receiveBufSize", Proto.Elm.newCNum("(xdc_Int)"), 8192L, "wh");
        po.addFld("receiveBufLimit", Proto.Elm.newCNum("(xdc_Int)"), 8192L, "wh");
        po.addFld("keepIdleTime", Proto.Elm.newCNum("(xdc_Int)"), 72000L, "wh");
        po.addFld("keepProbeInterval", Proto.Elm.newCNum("(xdc_Int)"), 750L, "wh");
        po.addFld("keepProbeTimeout", Proto.Elm.newCNum("(xdc_Int)"), 6000L, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.Tcp$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Tcp$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.Tcp$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void Ip$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/Ip.xs");
        om.bind("ti.ndk.config.Ip$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Ip.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Ip.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("defaultStartIndex", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("defaultPortForwarding", $$T_Bool, false, "rh");
                po.addFld("defaultPortFiltering", $$T_Bool, false, "rh");
                po.addFld("defaultMaxReasmTime", Proto.Elm.newCNum("(xdc_Int)"), 10L, "rh");
                po.addFld("defaultMaxReasmSize", Proto.Elm.newCNum("(xdc_Int)"), 3020L, "rh");
                po.addFld("defaultIcmpDoRedir", $$T_Bool, true, "rh");
                po.addFld("defaultIcmpTTL", Proto.Elm.newCNum("(xdc_Int)"), 64L, "rh");
                po.addFld("defaultIcmpTTLecho", Proto.Elm.newCNum("(xdc_Int)"), 255L, "rh");
                po.addFld("defaultIcmpBcastReply", $$T_Bool, false, "rh");
                po.addFld("defaultIcmpMcastReply", $$T_Bool, false, "rh");
                po.addFld("defaultDirBcast", $$T_Bool, true, "rh");
                po.addFld("defaultRteDownTime", Proto.Elm.newCNum("(xdc_Int)"), 20L, "rh");
                po.addFld("defaultRteKpAliveTime", Proto.Elm.newCNum("(xdc_Int)"), 1200L, "rh");
                po.addFld("defaultRteCloneTimeout", Proto.Elm.newCNum("(xdc_Int)"), 120L, "rh");
                po.addFld("defaultRteMtu", Proto.Elm.newCNum("(xdc_Int)"), 64L, "rh");
                po.addFld("defaultRteCtrlDbg", $$T_Bool, false, "rh");
                po.addFld("defaultRteAdverPer", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("defaultRteAdverLife", Proto.Elm.newCNum("(xdc_Int)"), 120L, "rh");
                po.addFld("defaultRteAdverLvl", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("defaultSockTTL", Proto.Elm.newCNum("(xdc_Int)"), 64L, "rh");
                po.addFld("defaultSockTos", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("defaultSockMaxConn", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFld("defaultSockConnTimeout", Proto.Elm.newCNum("(xdc_Int)"), 80L, "rh");
                po.addFld("defaultSockIoTimeout", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("defaultSockBufTxSz", Proto.Elm.newCNum("(xdc_Int)"), 2048L, "rh");
                po.addFld("defaultSockBufRxSz", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("defaultPipIoTimeout", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("defaultPipMaxBufSz", Proto.Elm.newCNum("(xdc_Int)"), 1024L, "rh");
                po.addFld("defaultPipBufTxSz", Proto.Elm.newCNum("(xdc_Int)"), 256L, "rh");
                po.addFld("defaultPipBufRxSz", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("CIS_FLG_IFIDXVALID", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("CIS_FLG_RESOLVEIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("CIS_FLG_CALLBYIP", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("CIS_FLG_RESTARTIPTERM", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
        po.addFld("DHCPOPT_TIME_OFFSET", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_TIME_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_NAME_SERVERS", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_LOG_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_COOKIE_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_LPR_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_IMPRESS_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_RESOURCE_LOCATION_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_BOOT_FILE_SIZE", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_MERIT_DUMP_FILE", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_SWAP_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_ROOT_PATH", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_EXTENTIONS_PATH", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_IP_FORWARDING", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_NONLOCAL_SOURCE_ROUTING", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_POLICTY_FILTER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_MAXIMUM_DATAGRAM_REASSEMBLY_SIZE", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_DEFAULT_IP_TTL", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_PATH_MTU_AGING_TIMEOUT", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_PATH_MTU_PLATEAU_TIMEOUT", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_INTERFACE_MTU", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_ALL_SUBNETS_LOCAL", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_BROADCAST_ADDRESS", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_PERFORM_MASK_DISCOVERY", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_MASK_SUPPLIER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_PERFORM_ROUTER_DISCOVERY", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_ROUTER_SOLICITATION_ADDRESS", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_STATIC_ROUTE", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_TRAILER_ENCAPSULATION", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_ARP_CACHE_TIMEOUT", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_ETHERNET_ENCAPSULATION", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_TCP_DEFUALT_TTL", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_TCP_KEEPALIVE_INTERVAL", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_TCP_KEEPALIVE_GARBAGE", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_NIS_DOMAIN", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_NIS_SERVERS", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_NIS_TIME_PROTOCOL_SERVERS", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_VENDOR_SPECIFIC_INFORMATION", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_NETBIOS_DATAGRAM_DISTRIBUTION_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_XWINDOWS_FONT_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_XWINDOWS_DISPLAY_MANAGER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_REQUESTED_IP_ADDRESS", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_IP_ADDRESS_LEASE_TIME", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_OPTION_OVERLOAD", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_DHCP_MESSAGE_TYPE", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_SERVER_IDENTIFIER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_PARAMETER_REQUEST_LIST", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_MESSAGE", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_MAXIMUM_DHCP_MESSAGE_SIZE", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_RENEWAL_T1_TIME_VALUE", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_RENEWAL_T2_TIME_VALUE", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_VENDOR_CLASS_IDENTIFIER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_CLIENT_IDENTIFIER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_NISPLUS_DOMAIN", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_NISPLUS_SERVERS", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_TFTP_SERVER_NAME", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_BOOTFILE_NAME", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_MOBILE_IP_HOME_AGENT", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_SMTP_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_POP3_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_NNTP_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_DEFAULT_WWW_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_DEFAULT_FINGER_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_DEFAULT_IRC_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_STREETTALK_SERVER", $$T_Bool, false, "wh");
        po.addFld("DHCPOPT_STREETALK_DISCOVERY_ASSISTANCE_SERVER", $$T_Bool, false, "wh");
        po.addFld("hostName", $$T_Str, "tisoc", "wh");
        po.addFld("address", $$T_Str, null, "wh");
        po.addFld("ifIdx", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("dhcpClientMode", Proto.Elm.newCNum("(xdc_Bits16)"), 1L, "wh");
        po.addFld("dhcpClientPcbServer", new Proto.Adr("xdc_Void*", "Pv"), "&ti_ndk_config_Global_serviceReport", "wh");
        po.addFld("mask", $$T_Str, "255.255.254.0", "wh");
        po.addFld("gatewayIpAddr", $$T_Str, "0.0.0.0", "wh");
        po.addFld("domainName", $$T_Str, "demo.net", "wh");
        po.addFld("indexStart", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("enableForwarding", $$T_Bool, false, "wh");
        po.addFld("enableFiltering", $$T_Bool, false, "wh");
        po.addFld("maxReassemblyTime", Proto.Elm.newCNum("(xdc_Int)"), 10L, "wh");
        po.addFld("maxReassemblySize", Proto.Elm.newCNum("(xdc_Int)"), 3020L, "wh");
        po.addFld("icmpDoRedirect", $$T_Bool, true, "wh");
        po.addFld("icmpTimeToLive", Proto.Elm.newCNum("(xdc_Int)"), 64L, "wh");
        po.addFld("icmpTimeToLiveEcho", Proto.Elm.newCNum("(xdc_Int)"), 255L, "wh");
        po.addFld("icmpDontReplyToBcast", $$T_Bool, false, "wh");
        po.addFld("icmpDontReplyToMcast", $$T_Bool, false, "wh");
        po.addFld("enableDirectedBroadcast", $$T_Bool, true, "wh");
        po.addFld("routeDownTime", Proto.Elm.newCNum("(xdc_Int)"), 20L, "wh");
        po.addFld("routeKeepAliveTime", Proto.Elm.newCNum("(xdc_Int)"), 1200L, "wh");
        po.addFld("routeCloneTimeout", Proto.Elm.newCNum("(xdc_Int)"), 120L, "wh");
        po.addFld("routeDefaultMtu", Proto.Elm.newCNum("(xdc_Int)"), 64L, "wh");
        po.addFld("routeCtrlEnableDebug", $$T_Bool, false, "wh");
        po.addFld("routeAdvertisePeriod", Proto.Elm.newCNum("(xdc_Int)"), 0L, "wh");
        po.addFld("routeAdvertiseLifetime", Proto.Elm.newCNum("(xdc_Int)"), 120L, "wh");
        po.addFld("routeAdvertisePrefLvl", Proto.Elm.newCNum("(xdc_Int)"), 0L, "wh");
        po.addFld("socketTimeToLive", Proto.Elm.newCNum("(xdc_Int)"), 64L, "wh");
        po.addFld("socketTos", Proto.Elm.newCNum("(xdc_Int)"), 0L, "wh");
        po.addFld("socketMaxConnections", Proto.Elm.newCNum("(xdc_Int)"), 8L, "wh");
        po.addFld("socketConnectTimeout", Proto.Elm.newCNum("(xdc_Int)"), 80L, "wh");
        po.addFld("socketIoTimeout", Proto.Elm.newCNum("(xdc_Int)"), 0L, "wh");
        po.addFld("socketBufMinTxSize", Proto.Elm.newCNum("(xdc_Int)"), 2048L, "wh");
        po.addFld("socketBufMinRxSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("pipeIoTimeout", Proto.Elm.newCNum("(xdc_Int)"), 0L, "wh");
        po.addFld("pipeMaxBufSize", Proto.Elm.newCNum("(xdc_Int)"), 1024L, "wh");
        po.addFld("pipeBufMinTxSize", Proto.Elm.newCNum("(xdc_Int)"), 256L, "wh");
        po.addFld("pipeBufMinRxSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("IfIdXValid", $$T_Bool, true, "wh");
        po.addFld("ResolveIP", $$T_Bool, false, "wh");
        po.addFld("CallByIP", $$T_Bool, false, "wh");
        po.addFld("RestartIPTerm", $$T_Bool, false, "wh");
        po.addFld("autoIp", $$T_Bool, true, "wh");
        po.addFld("NetType", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.Ip$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Ip$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.Ip$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // typedef Ip.CisFlags
        om.bind("ti.ndk.config.Ip.CisFlags", Proto.Elm.newCNum("(xdc_Bits16)"));
    }

    void Route$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/Route.xs");
        om.bind("ti.ndk.config.Route$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Route.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Route.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.Route$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Route$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.Route$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void Icmp$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/Icmp.xs");
        om.bind("ti.ndk.config.Icmp$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Icmp.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Icmp.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.Icmp$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Icmp$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.Icmp$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void Udp$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/Udp.xs");
        om.bind("ti.ndk.config.Udp$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Udp.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Udp.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("defaultRxBufSize", Proto.Elm.newCNum("(xdc_Int)"), 8192L, "rh");
        po.addFld("receiveBufSize", Proto.Elm.newCNum("(xdc_Int)"), 8192L, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.ndk.config.Udp$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.ndk.config.Udp$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.ndk.config.Udp$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void Emac$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.ndk.config.Emac.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Emac.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("device", (Proto)om.findStrict("ti.ndk.config.Emac.DeviceSupport", "ti.ndk.config"), om.find("ti.ndk.config.Emac.NONE"), "wh");
    }

    void Ppp$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.ndk.config.Ppp.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Ppp.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
    }

    void Pppoe$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.ndk.config.Pppoe.Module", "ti.ndk.config");
        po.init("ti.ndk.config.Pppoe.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
    }

    void Global$$ROV()
    {
    }

    void Http$$ROV()
    {
    }

    void Telnet$$ROV()
    {
    }

    void DhcpClient$$ROV()
    {
    }

    void DhcpServer$$ROV()
    {
    }

    void Dns$$ROV()
    {
    }

    void Nat$$ROV()
    {
    }

    void Tcp$$ROV()
    {
    }

    void Ip$$ROV()
    {
    }

    void Route$$ROV()
    {
    }

    void Icmp$$ROV()
    {
    }

    void Udp$$ROV()
    {
    }

    void Emac$$ROV()
    {
    }

    void Ppp$$ROV()
    {
    }

    void Pppoe$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.ndk.config.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.ndk.config"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/config/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.ndk.config"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.ndk.config"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.ndk.config"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.ndk.config"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.ndk.config"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.ndk.config"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.ndk.config", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.ndk.config");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.ndk.config.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.ndk.config'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.ndk.config$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.ndk.config$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.ndk.config$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Global$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Global", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Global.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Global", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.Global$$capsule", "ti.ndk.config"));
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("NetEventSchedPri", om.findStrict("ti.ndk.config.Global.NetEventSchedPri", "ti.ndk.config"));
        vo.bind("NetEventSchedOp", om.findStrict("ti.ndk.config.Global.NetEventSchedOp", "ti.ndk.config"));
        vo.bind("DebugLevel", om.findStrict("ti.ndk.config.Global.DebugLevel", "ti.ndk.config"));
        vo.bind("StackLibProtocol", om.findStrict("ti.ndk.config.Global.StackLibProtocol", "ti.ndk.config"));
        vo.bind("Account", om.findStrict("ti.ndk.config.Global.Account", "ti.ndk.config"));
        tdefs.add(om.findStrict("ti.ndk.config.Global.Account", "ti.ndk.config"));
        vo.bind("ndkHookFxn", om.findStrict("ti.ndk.config.Global.ndkHookFxn", "ti.ndk.config"));
        vo.bind("StackRunModeFlags", om.findStrict("ti.ndk.config.Global.StackRunModeFlags", "ti.ndk.config"));
        vo.bind("NC_PRIORITY_LOW", om.findStrict("ti.ndk.config.Global.NC_PRIORITY_LOW", "ti.ndk.config"));
        vo.bind("NC_PRIORITY_HIGH", om.findStrict("ti.ndk.config.Global.NC_PRIORITY_HIGH", "ti.ndk.config"));
        vo.bind("NC_OPMODE_POLLING", om.findStrict("ti.ndk.config.Global.NC_OPMODE_POLLING", "ti.ndk.config"));
        vo.bind("NC_OPMODE_INTERRUPT", om.findStrict("ti.ndk.config.Global.NC_OPMODE_INTERRUPT", "ti.ndk.config"));
        vo.bind("DBG_INFO", om.findStrict("ti.ndk.config.Global.DBG_INFO", "ti.ndk.config"));
        vo.bind("DBG_WARN", om.findStrict("ti.ndk.config.Global.DBG_WARN", "ti.ndk.config"));
        vo.bind("DBG_ERROR", om.findStrict("ti.ndk.config.Global.DBG_ERROR", "ti.ndk.config"));
        vo.bind("DBG_NONE", om.findStrict("ti.ndk.config.Global.DBG_NONE", "ti.ndk.config"));
        vo.bind("NONE", om.findStrict("ti.ndk.config.Global.NONE", "ti.ndk.config"));
        vo.bind("NAT", om.findStrict("ti.ndk.config.Global.NAT", "ti.ndk.config"));
        vo.bind("NAT_PPP", om.findStrict("ti.ndk.config.Global.NAT_PPP", "ti.ndk.config"));
        vo.bind("NAT_PPP_PPPOE", om.findStrict("ti.ndk.config.Global.NAT_PPP_PPPOE", "ti.ndk.config"));
        vo.bind("PPP", om.findStrict("ti.ndk.config.Global.PPP", "ti.ndk.config"));
        vo.bind("PPP_PPPOE", om.findStrict("ti.ndk.config.Global.PPP_PPPOE", "ti.ndk.config"));
        vo.bind("MIN", om.findStrict("ti.ndk.config.Global.MIN", "ti.ndk.config"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Global$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Global.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Global.xdt");
        pkgV.bind("Global", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Global");
    }

    void Http$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Http", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Http.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Http", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.Http$$capsule", "ti.ndk.config"));
        vo.bind("Instance", om.findStrict("ti.ndk.config.Http.Instance", "ti.ndk.config"));
        vo.bind("Params", om.findStrict("ti.ndk.config.Http.Params", "ti.ndk.config"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.ndk.config.Http.Params", "ti.ndk.config")).newInstance());
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("httpServiceFxn", om.findStrict("ti.ndk.config.Http.httpServiceFxn", "ti.ndk.config"));
        vo.bind("CisFlags", om.findStrict("ti.ndk.config.Http.CisFlags", "ti.ndk.config"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Http$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Http.xdt");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.ndk.config.Http.Object", "ti.ndk.config"));
        vo.bind("TEMPLATE$", "./Http.xdt");
        pkgV.bind("Http", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Http");
    }

    void Telnet$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Telnet", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Telnet.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Telnet", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.Telnet$$capsule", "ti.ndk.config"));
        vo.bind("Instance", om.findStrict("ti.ndk.config.Telnet.Instance", "ti.ndk.config"));
        vo.bind("Params", om.findStrict("ti.ndk.config.Telnet.Params", "ti.ndk.config"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.ndk.config.Telnet.Params", "ti.ndk.config")).newInstance());
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("telnetServiceFxn", om.findStrict("ti.ndk.config.Telnet.telnetServiceFxn", "ti.ndk.config"));
        vo.bind("telnetCallbackFxn", om.findStrict("ti.ndk.config.Telnet.telnetCallbackFxn", "ti.ndk.config"));
        vo.bind("CisFlags", om.findStrict("ti.ndk.config.Telnet.CisFlags", "ti.ndk.config"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Telnet$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Telnet.xdt");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.ndk.config.Telnet.Object", "ti.ndk.config"));
        vo.bind("TEMPLATE$", "./Telnet.xdt");
        pkgV.bind("Telnet", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Telnet");
    }

    void DhcpClient$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.DhcpClient", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.DhcpClient.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.DhcpClient", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.DhcpClient$$capsule", "ti.ndk.config"));
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.DhcpClient$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("DhcpClient", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("DhcpClient");
    }

    void DhcpServer$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.DhcpServer", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.DhcpServer.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.DhcpServer", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.DhcpServer$$capsule", "ti.ndk.config"));
        vo.bind("Instance", om.findStrict("ti.ndk.config.DhcpServer.Instance", "ti.ndk.config"));
        vo.bind("Params", om.findStrict("ti.ndk.config.DhcpServer.Params", "ti.ndk.config"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.ndk.config.DhcpServer.Params", "ti.ndk.config")).newInstance());
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("dhcpServerServiceFxn", om.findStrict("ti.ndk.config.DhcpServer.dhcpServerServiceFxn", "ti.ndk.config"));
        vo.bind("DhcpServerFlag", om.findStrict("ti.ndk.config.DhcpServer.DhcpServerFlag", "ti.ndk.config"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.DhcpServer$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./DhcpServer.xdt");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.ndk.config.DhcpServer.Object", "ti.ndk.config"));
        vo.bind("TEMPLATE$", "./DhcpServer.xdt");
        pkgV.bind("DhcpServer", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("DhcpServer");
    }

    void Dns$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Dns", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Dns.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Dns", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.Dns$$capsule", "ti.ndk.config"));
        vo.bind("Instance", om.findStrict("ti.ndk.config.Dns.Instance", "ti.ndk.config"));
        vo.bind("Params", om.findStrict("ti.ndk.config.Dns.Params", "ti.ndk.config"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.ndk.config.Dns.Params", "ti.ndk.config")).newInstance());
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("dnsServiceFxn", om.findStrict("ti.ndk.config.Dns.dnsServiceFxn", "ti.ndk.config"));
        vo.bind("CisFlags", om.findStrict("ti.ndk.config.Dns.CisFlags", "ti.ndk.config"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Dns$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Dns.xdt");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.ndk.config.Dns.Object", "ti.ndk.config"));
        vo.bind("TEMPLATE$", "./Dns.xdt");
        pkgV.bind("Dns", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Dns");
    }

    void Nat$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Nat", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Nat.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Nat", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.Nat$$capsule", "ti.ndk.config"));
        vo.bind("Instance", om.findStrict("ti.ndk.config.Nat.Instance", "ti.ndk.config"));
        vo.bind("Params", om.findStrict("ti.ndk.config.Nat.Params", "ti.ndk.config"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.ndk.config.Nat.Params", "ti.ndk.config")).newInstance());
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("natServiceFxn", om.findStrict("ti.ndk.config.Nat.natServiceFxn", "ti.ndk.config"));
        vo.bind("CisFlags", om.findStrict("ti.ndk.config.Nat.CisFlags", "ti.ndk.config"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Nat$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Nat.xdt");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.ndk.config.Nat.Object", "ti.ndk.config"));
        vo.bind("TEMPLATE$", "./Nat.xdt");
        pkgV.bind("Nat", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Nat");
    }

    void Tcp$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Tcp", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Tcp.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Tcp", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.Tcp$$capsule", "ti.ndk.config"));
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Tcp$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Tcp.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Tcp.xdt");
        pkgV.bind("Tcp", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Tcp");
    }

    void Ip$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Ip", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Ip.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Ip", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.Ip$$capsule", "ti.ndk.config"));
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("CisFlags", om.findStrict("ti.ndk.config.Ip.CisFlags", "ti.ndk.config"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Ip$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Ip.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Ip.xdt");
        pkgV.bind("Ip", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Ip");
    }

    void Route$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Route", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Route.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Route", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.Route$$capsule", "ti.ndk.config"));
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Route$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Route", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Route");
    }

    void Icmp$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Icmp", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Icmp.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Icmp", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.Icmp$$capsule", "ti.ndk.config"));
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Icmp$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Icmp", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Icmp");
    }

    void Udp$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Udp", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Udp.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Udp", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.ndk.config.Udp$$capsule", "ti.ndk.config"));
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Udp$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Udp.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Udp.xdt");
        pkgV.bind("Udp", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Udp");
    }

    void Emac$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Emac", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Emac.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Emac", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("DeviceSupport", om.findStrict("ti.ndk.config.Emac.DeviceSupport", "ti.ndk.config"));
        vo.bind("EVMOMAPL138", om.findStrict("ti.ndk.config.Emac.EVMOMAPL138", "ti.ndk.config"));
        vo.bind("TMDXDOCKH52C1", om.findStrict("ti.ndk.config.Emac.TMDXDOCKH52C1", "ti.ndk.config"));
        vo.bind("DK_LM3S9D96", om.findStrict("ti.ndk.config.Emac.DK_LM3S9D96", "ti.ndk.config"));
        vo.bind("NONE", om.findStrict("ti.ndk.config.Emac.NONE", "ti.ndk.config"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Emac$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Emac", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Emac");
    }

    void Ppp$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Ppp", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Ppp.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Ppp", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Ppp$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Ppp", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Ppp");
    }

    void Pppoe$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.ndk.config.Pppoe", "ti.ndk.config");
        po = (Proto.Obj)om.findStrict("ti.ndk.config.Pppoe.Module", "ti.ndk.config");
        vo.init2(po, "ti.ndk.config.Pppoe", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.ndk.config", "ti.ndk.config"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.ndk.config")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.ndk.config.Pppoe$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Pppoe", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Pppoe");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Global", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Http", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Telnet", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.DhcpClient", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.DhcpServer", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Dns", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Nat", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Tcp", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Ip", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Route", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Icmp", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Udp", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Emac", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Ppp", "ti.ndk.config"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.ndk.config.Pppoe", "ti.ndk.config"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.ndk.config.Global")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Http")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Telnet")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.DhcpClient")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.DhcpServer")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Dns")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Nat")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Tcp")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Ip")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Route")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Icmp")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Udp")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Emac")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Ppp")).bless();
        ((Value.Obj)om.getv("ti.ndk.config.Pppoe")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.ndk.config")).add(pkgV);
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
        Global$$OBJECTS();
        Http$$OBJECTS();
        Telnet$$OBJECTS();
        DhcpClient$$OBJECTS();
        DhcpServer$$OBJECTS();
        Dns$$OBJECTS();
        Nat$$OBJECTS();
        Tcp$$OBJECTS();
        Ip$$OBJECTS();
        Route$$OBJECTS();
        Icmp$$OBJECTS();
        Udp$$OBJECTS();
        Emac$$OBJECTS();
        Ppp$$OBJECTS();
        Pppoe$$OBJECTS();
        Global$$CONSTS();
        Http$$CONSTS();
        Telnet$$CONSTS();
        DhcpClient$$CONSTS();
        DhcpServer$$CONSTS();
        Dns$$CONSTS();
        Nat$$CONSTS();
        Tcp$$CONSTS();
        Ip$$CONSTS();
        Route$$CONSTS();
        Icmp$$CONSTS();
        Udp$$CONSTS();
        Emac$$CONSTS();
        Ppp$$CONSTS();
        Pppoe$$CONSTS();
        Global$$CREATES();
        Http$$CREATES();
        Telnet$$CREATES();
        DhcpClient$$CREATES();
        DhcpServer$$CREATES();
        Dns$$CREATES();
        Nat$$CREATES();
        Tcp$$CREATES();
        Ip$$CREATES();
        Route$$CREATES();
        Icmp$$CREATES();
        Udp$$CREATES();
        Emac$$CREATES();
        Ppp$$CREATES();
        Pppoe$$CREATES();
        Global$$FUNCTIONS();
        Http$$FUNCTIONS();
        Telnet$$FUNCTIONS();
        DhcpClient$$FUNCTIONS();
        DhcpServer$$FUNCTIONS();
        Dns$$FUNCTIONS();
        Nat$$FUNCTIONS();
        Tcp$$FUNCTIONS();
        Ip$$FUNCTIONS();
        Route$$FUNCTIONS();
        Icmp$$FUNCTIONS();
        Udp$$FUNCTIONS();
        Emac$$FUNCTIONS();
        Ppp$$FUNCTIONS();
        Pppoe$$FUNCTIONS();
        Global$$SIZES();
        Http$$SIZES();
        Telnet$$SIZES();
        DhcpClient$$SIZES();
        DhcpServer$$SIZES();
        Dns$$SIZES();
        Nat$$SIZES();
        Tcp$$SIZES();
        Ip$$SIZES();
        Route$$SIZES();
        Icmp$$SIZES();
        Udp$$SIZES();
        Emac$$SIZES();
        Ppp$$SIZES();
        Pppoe$$SIZES();
        Global$$TYPES();
        Http$$TYPES();
        Telnet$$TYPES();
        DhcpClient$$TYPES();
        DhcpServer$$TYPES();
        Dns$$TYPES();
        Nat$$TYPES();
        Tcp$$TYPES();
        Ip$$TYPES();
        Route$$TYPES();
        Icmp$$TYPES();
        Udp$$TYPES();
        Emac$$TYPES();
        Ppp$$TYPES();
        Pppoe$$TYPES();
        if (isROV) {
            Global$$ROV();
            Http$$ROV();
            Telnet$$ROV();
            DhcpClient$$ROV();
            DhcpServer$$ROV();
            Dns$$ROV();
            Nat$$ROV();
            Tcp$$ROV();
            Ip$$ROV();
            Route$$ROV();
            Icmp$$ROV();
            Udp$$ROV();
            Emac$$ROV();
            Ppp$$ROV();
            Pppoe$$ROV();
        }//isROV
        $$SINGLETONS();
        Global$$SINGLETONS();
        Http$$SINGLETONS();
        Telnet$$SINGLETONS();
        DhcpClient$$SINGLETONS();
        DhcpServer$$SINGLETONS();
        Dns$$SINGLETONS();
        Nat$$SINGLETONS();
        Tcp$$SINGLETONS();
        Ip$$SINGLETONS();
        Route$$SINGLETONS();
        Icmp$$SINGLETONS();
        Udp$$SINGLETONS();
        Emac$$SINGLETONS();
        Ppp$$SINGLETONS();
        Pppoe$$SINGLETONS();
        $$INITIALIZATION();
    }
}
