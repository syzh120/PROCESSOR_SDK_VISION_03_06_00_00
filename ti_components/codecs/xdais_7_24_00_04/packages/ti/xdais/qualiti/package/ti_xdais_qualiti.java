/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y13
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_xdais_qualiti
{
    static final String VERS = "@(#) xdc-y13\n";

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
        Global.callFxn("loadPackage", xdcO, "xdc.tools.sg");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.tools");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.xdais.qualiti.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.xdais.qualiti", new Value.Obj("ti.xdais.qualiti", pkgP));
    }

    void Main$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.qualiti.Main.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.qualiti.Main", new Value.Obj("ti.xdais.qualiti.Main", po));
        pkgV.bind("Main", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.xdais.qualiti.Main.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.xdais.qualiti.Main$$Object", new Proto.Obj());
        Object objP = om.bind("ti.xdais.qualiti.Main.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.xdais.qualiti.Main$$Params", new Proto.Obj());
        om.bind("ti.xdais.qualiti.Main.Params", new Proto.Str(po, true));
    }

    void System$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.qualiti.System.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.qualiti.System", new Value.Obj("ti.xdais.qualiti.System", po));
        pkgV.bind("System", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.xdais.qualiti.System$$RunResult", new Proto.Obj());
        om.bind("ti.xdais.qualiti.System.RunResult", new Proto.Str(spo, true));
    }

    void ITest$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.qualiti.ITest.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.qualiti.ITest", new Value.Obj("ti.xdais.qualiti.ITest", po));
        pkgV.bind("ITest", vo);
        // decls 
        om.bind("ti.xdais.qualiti.ITest.TestStatus", new Proto.Enm("ti.xdais.qualiti.ITest.TestStatus"));
        om.bind("ti.xdais.qualiti.ITest.TestDetailLevel", new Proto.Enm("ti.xdais.qualiti.ITest.TestDetailLevel"));
        spo = (Proto.Obj)om.bind("ti.xdais.qualiti.ITest$$Test", new Proto.Obj());
        om.bind("ti.xdais.qualiti.ITest.Test", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("ti.xdais.qualiti.ITest$$TestAttrs", new Proto.Obj());
        om.bind("ti.xdais.qualiti.ITest.TestAttrs", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("ti.xdais.qualiti.ITest$$CompilerParams", new Proto.Obj());
        om.bind("ti.xdais.qualiti.ITest.CompilerParams", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("ti.xdais.qualiti.ITest$$AlgoParams", new Proto.Obj());
        om.bind("ti.xdais.qualiti.ITest.AlgoParams", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("ti.xdais.qualiti.ITest$$TestSettings", new Proto.Obj());
        om.bind("ti.xdais.qualiti.ITest.TestSettings", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("ti.xdais.qualiti.ITest$$TestResult", new Proto.Obj());
        om.bind("ti.xdais.qualiti.ITest.TestResult", new Proto.Str(spo, true));
    }

    void Compiler$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.qualiti.Compiler.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.qualiti.Compiler", new Value.Obj("ti.xdais.qualiti.Compiler", po));
        pkgV.bind("Compiler", vo);
        // decls 
        om.bind("ti.xdais.qualiti.Compiler.TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Compiler.TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Compiler.Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Compiler.TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Compiler.CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Compiler.AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Compiler.TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Compiler.TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
    }

    void Rules8_9_10$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.qualiti.Rules8_9_10.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.qualiti.Rules8_9_10", new Value.Obj("ti.xdais.qualiti.Rules8_9_10", po));
        pkgV.bind("Rules8_9_10", vo);
        // decls 
        om.bind("ti.xdais.qualiti.Rules8_9_10.TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules8_9_10.TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules8_9_10.Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules8_9_10.TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules8_9_10.CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules8_9_10.AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules8_9_10.TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules8_9_10.TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
    }

    void Rule12$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.qualiti.Rule12.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.qualiti.Rule12", new Value.Obj("ti.xdais.qualiti.Rule12", po));
        pkgV.bind("Rule12", vo);
        // decls 
        om.bind("ti.xdais.qualiti.Rule12.TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule12.TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule12.Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule12.TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule12.CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule12.AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule12.TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule12.TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
    }

    void Rules13_26$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.qualiti.Rules13_26.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.qualiti.Rules13_26", new Value.Obj("ti.xdais.qualiti.Rules13_26", po));
        pkgV.bind("Rules13_26", vo);
        // decls 
        om.bind("ti.xdais.qualiti.Rules13_26.TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules13_26.TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules13_26.Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules13_26.TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules13_26.CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules13_26.AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules13_26.TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules13_26.TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
    }

    void Rule20$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.qualiti.Rule20.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.qualiti.Rule20", new Value.Obj("ti.xdais.qualiti.Rule20", po));
        pkgV.bind("Rule20", vo);
        // decls 
        om.bind("ti.xdais.qualiti.Rule20.TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule20.TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule20.Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule20.TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule20.CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule20.AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule20.TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule20.TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
    }

    void Rules21_22$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.qualiti.Rules21_22.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.qualiti.Rules21_22", new Value.Obj("ti.xdais.qualiti.Rules21_22", po));
        pkgV.bind("Rules21_22", vo);
        // decls 
        om.bind("ti.xdais.qualiti.Rules21_22.TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules21_22.TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules21_22.Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules21_22.TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules21_22.CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules21_22.AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules21_22.TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rules21_22.TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
    }

    void Rule25$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.xdais.qualiti.Rule25.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.xdais.qualiti.Rule25", new Value.Obj("ti.xdais.qualiti.Rule25", po));
        pkgV.bind("Rule25", vo);
        // decls 
        om.bind("ti.xdais.qualiti.Rule25.TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule25.TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule25.Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule25.TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule25.CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule25.AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule25.TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        om.bind("ti.xdais.qualiti.Rule25.TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
    }

    void Main$$CONSTS()
    {
        // module Main
    }

    void System$$CONSTS()
    {
        // module System
    }

    void ITest$$CONSTS()
    {
        // interface ITest
        om.bind("ti.xdais.qualiti.ITest.TEST_NOTRUN", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"), "ti.xdais.qualiti.ITest.TEST_NOTRUN", 0));
        om.bind("ti.xdais.qualiti.ITest.TEST_PASS", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"), "ti.xdais.qualiti.ITest.TEST_PASS", 1));
        om.bind("ti.xdais.qualiti.ITest.TEST_FAIL", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"), "ti.xdais.qualiti.ITest.TEST_FAIL", 2));
        om.bind("ti.xdais.qualiti.ITest.TEST_NOTAPPLY", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"), "ti.xdais.qualiti.ITest.TEST_NOTAPPLY", 3));
        om.bind("ti.xdais.qualiti.ITest.TEST_RUNNING", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"), "ti.xdais.qualiti.ITest.TEST_RUNNING", 4));
        om.bind("ti.xdais.qualiti.ITest.TEST_RUNERROR", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"), "ti.xdais.qualiti.ITest.TEST_RUNERROR", 5));
        om.bind("ti.xdais.qualiti.ITest.DETAILLEVEL_FAILDETAILS", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"), "ti.xdais.qualiti.ITest.DETAILLEVEL_FAILDETAILS", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTLOG", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"), "ti.xdais.qualiti.ITest.DETAILLEVEL_TESTLOG", xdc.services.intern.xsr.Enum.intValue(1L)+0));
        om.bind("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTOUTPUT", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"), "ti.xdais.qualiti.ITest.DETAILLEVEL_TESTOUTPUT", xdc.services.intern.xsr.Enum.intValue(2L)+0));
    }

    void Compiler$$CONSTS()
    {
        // module Compiler
    }

    void Rules8_9_10$$CONSTS()
    {
        // module Rules8_9_10
    }

    void Rule12$$CONSTS()
    {
        // module Rule12
    }

    void Rules13_26$$CONSTS()
    {
        // module Rules13_26
    }

    void Rule20$$CONSTS()
    {
        // module Rule20
    }

    void Rules21_22$$CONSTS()
    {
        // module Rules21_22
    }

    void Rule25$$CONSTS()
    {
        // module Rule25
    }

    void Main$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.xdais.qualiti.Main$$create", new Proto.Fxn(om.findStrict("ti.xdais.qualiti.Main.Module", "ti.xdais.qualiti"), om.findStrict("ti.xdais.qualiti.Main.Instance", "ti.xdais.qualiti"), 1, 0, false));
                fxn.addArg(0, "__params", (Proto)om.findStrict("ti.xdais.qualiti.Main.Params", "ti.xdais.qualiti"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$xdais$qualiti$Main$$create = function( __params ) {\n");
            sb.append("var __mod = xdc.om['ti.xdais.qualiti.Main'];\n");
            sb.append("var __inst = xdc.om['ti.xdais.qualiti.Main.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.xdais.qualiti']);\n");
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
        fxn = (Proto.Fxn)om.bind("ti.xdais.qualiti.Main$$construct", new Proto.Fxn(om.findStrict("ti.xdais.qualiti.Main.Module", "ti.xdais.qualiti"), null, 2, 0, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.xdais.qualiti.Main$$Object", "ti.xdais.qualiti"), null);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.xdais.qualiti.Main.Params", "ti.xdais.qualiti"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$xdais$qualiti$Main$$construct = function( __obj, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.xdais.qualiti.Main'];\n");
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

    void System$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ITest$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Compiler$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Rules8_9_10$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Rule12$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Rules13_26$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Rule20$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Rules21_22$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Rule25$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Main$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Main.createPartControl
        fxn = (Proto.Fxn)om.bind("ti.xdais.qualiti.Main$$createPartControl", new Proto.Fxn(om.findStrict("ti.xdais.qualiti.Main.Module", "ti.xdais.qualiti"), null, 0, -1, false));
    }

    void System$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn System.runShellCommand
        fxn = (Proto.Fxn)om.bind("ti.xdais.qualiti.System$$runShellCommand", new Proto.Fxn(om.findStrict("ti.xdais.qualiti.System.Module", "ti.xdais.qualiti"), (Proto)om.findStrict("ti.xdais.qualiti.System.RunResult", "ti.xdais.qualiti"), 3, 3, false));
                fxn.addArg(0, "commandStr", $$T_Str, $$UNDEF);
                fxn.addArg(1, "cbPrint", $$T_Obj, $$UNDEF);
                fxn.addArg(2, "detailLevel", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
        // fxn System.getCommandPath
        fxn = (Proto.Fxn)om.bind("ti.xdais.qualiti.System$$getCommandPath", new Proto.Fxn(om.findStrict("ti.xdais.qualiti.System.Module", "ti.xdais.qualiti"), $$T_Str, 1, 1, false));
                fxn.addArg(0, "command", $$T_Str, $$UNDEF);
        // fxn System.checkPath
        fxn = (Proto.Fxn)om.bind("ti.xdais.qualiti.System$$checkPath", new Proto.Fxn(om.findStrict("ti.xdais.qualiti.System.Module", "ti.xdais.qualiti"), $$T_Str, 1, 1, false));
                fxn.addArg(0, "path", $$T_Str, $$UNDEF);
    }

    void ITest$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn ITest.reset
        fxn = (Proto.Fxn)om.bind("ti.xdais.qualiti.ITest$$reset", new Proto.Fxn(om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti"), null, 1, 1, false));
                fxn.addArg(0, "testId", $$T_Str, $$UNDEF);
        // fxn ITest.getAttrs
        fxn = (Proto.Fxn)om.bind("ti.xdais.qualiti.ITest$$getAttrs", new Proto.Fxn(om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti"), (Proto)om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"), 1, 1, false));
                fxn.addArg(0, "testId", $$T_Str, $$UNDEF);
        // fxn ITest.run
        fxn = (Proto.Fxn)om.bind("ti.xdais.qualiti.ITest$$run", new Proto.Fxn(om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti"), (Proto)om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"), 5, 5, false));
                fxn.addArg(0, "testId", $$T_Str, $$UNDEF);
                fxn.addArg(1, "algoParams", (Proto)om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"), $$DEFAULT);
                fxn.addArg(2, "testSettings", (Proto)om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"), $$DEFAULT);
                fxn.addArg(3, "testDetailLevel", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                fxn.addArg(4, "cbPrintLog", $$T_Obj, $$UNDEF);
    }

    void Compiler$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Compiler.getCompilerInfo
        fxn = (Proto.Fxn)om.bind("ti.xdais.qualiti.Compiler$$getCompilerInfo", new Proto.Fxn(om.findStrict("ti.xdais.qualiti.Compiler.Module", "ti.xdais.qualiti"), (Proto)om.findStrict("ti.xdais.qualiti.Compiler.CompilerParams", "ti.xdais.qualiti"), 4, 4, false));
                fxn.addArg(0, "algoParams", (Proto)om.findStrict("ti.xdais.qualiti.Compiler.AlgoParams", "ti.xdais.qualiti"), $$DEFAULT);
                fxn.addArg(1, "testSettings", (Proto)om.findStrict("ti.xdais.qualiti.Compiler.TestSettings", "ti.xdais.qualiti"), $$DEFAULT);
                fxn.addArg(2, "printLogFxn", $$T_Obj, $$UNDEF);
                fxn.addArg(3, "detailLevel", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
    }

    void Rules8_9_10$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Rule12$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Rules13_26$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Rule20$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Rules21_22$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Rule25$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Main$$SIZES()
    {
    }

    void System$$SIZES()
    {
    }

    void ITest$$SIZES()
    {
    }

    void Compiler$$SIZES()
    {
    }

    void Rules8_9_10$$SIZES()
    {
    }

    void Rule12$$SIZES()
    {
    }

    void Rules13_26$$SIZES()
    {
    }

    void Rule20$$SIZES()
    {
    }

    void Rules21_22$$SIZES()
    {
    }

    void Rule25$$SIZES()
    {
    }

    void Main$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/qualiti/Main.xs");
        om.bind("ti.xdais.qualiti.Main$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Main.Module", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.Main.Module", om.findStrict("xdc.tools.ICmd.Module", "ti.xdais.qualiti"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("usage", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"[-h] [-u file] [-o outDir] [-ol] [-e] [-t toolsIniFile] ", "[-d 0|1|2] [-f] [-v|q] [-g] algproject", "  -u: run user script", "(following options in command-line mode only)", "  -o: output HTML reports to outDir", "  -l: output HTML reports in the algorithm library dir", "       (default is in the algorithm base dir)", "  -e: embed time stamp in the report filename", "  -t: specify alternative Tools.ini file with toolpaths", "  -d: report detail level", "  -f: make report diff friendly", "  -v: verbose", "  -q: quiet", "  algproject: a .qti file with algorithm description"}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.Main$$create", "ti.xdais.qualiti"), Global.get("ti$xdais$qualiti$Main$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.Main$$construct", "ti.xdais.qualiti"), Global.get("ti$xdais$qualiti$Main$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.xdais.qualiti.Main$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.xdais.qualiti.Main$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.xdais.qualiti.Main$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.xdais.qualiti.Main$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "main");
                if (fxn != null) po.addFxn("main", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$main", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "exec");
                if (fxn != null) po.addFxn("exec", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$exec", "ti.xdais.qualiti"), fxn);
                po.addFxn("createPartControl", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.Main$$createPartControl", "ti.xdais.qualiti"), Global.get(cap, "createPartControl"));
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Main.Instance", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.Main.Instance", om.findStrict("xdc.tools.ICmd.Instance", "ti.xdais.qualiti"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("help", $$T_Bool, false, "wh");
        po.addFld("userIniFile", $$T_Str, null, "wh");
        po.addFld("outputInLibDir", $$T_Bool, false, "wh");
        po.addFld("diffFriendly", $$T_Bool, false, "wh");
        po.addFld("outputDir", $$T_Str, null, "wh");
        po.addFld("embedTimeStampInReportName", $$T_Bool, false, "wh");
        po.addFld("testDetailLevel", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
        po.addFld("toolsIniFile", $$T_Str, null, "wh");
        po.addFld("verbose", $$T_Bool, false, "wh");
        po.addFld("quiet", $$T_Bool, false, "wh");
        po.addFld("gui", $$T_Bool, false, "wh");
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$run", "ti.xdais.qualiti"), fxn);
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Main$$Params", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.Main.Params", om.findStrict("xdc.tools.ICmd$$Params", "ti.xdais.qualiti"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("help", $$T_Bool, false, "wh");
        po.addFld("userIniFile", $$T_Str, null, "wh");
        po.addFld("outputInLibDir", $$T_Bool, false, "wh");
        po.addFld("diffFriendly", $$T_Bool, false, "wh");
        po.addFld("outputDir", $$T_Str, null, "wh");
        po.addFld("embedTimeStampInReportName", $$T_Bool, false, "wh");
        po.addFld("testDetailLevel", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
        po.addFld("toolsIniFile", $$T_Str, null, "wh");
        po.addFld("verbose", $$T_Bool, false, "wh");
        po.addFld("quiet", $$T_Bool, false, "wh");
        po.addFld("gui", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Main$$Object", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.Main.Object", om.findStrict("ti.xdais.qualiti.Main.Instance", "ti.xdais.qualiti"));
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$run", "ti.xdais.qualiti"), fxn);
    }

    void System$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/qualiti/System.xs");
        om.bind("ti.xdais.qualiti.System$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.System.Module", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.System.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.xdais.qualiti.System$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.xdais.qualiti.System$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.xdais.qualiti.System$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("runShellCommand", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.System$$runShellCommand", "ti.xdais.qualiti"), Global.get(cap, "runShellCommand"));
                po.addFxn("getCommandPath", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.System$$getCommandPath", "ti.xdais.qualiti"), Global.get(cap, "getCommandPath"));
                po.addFxn("checkPath", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.System$$checkPath", "ti.xdais.qualiti"), Global.get(cap, "checkPath"));
        // struct System.RunResult
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.System$$RunResult", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.System.RunResult", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("status", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("stdout", $$T_Str, $$UNDEF, "w");
                po.addFld("stderr", $$T_Str, $$UNDEF, "w");
                po.addFld("stdsys", $$T_Str, $$UNDEF, "w");
    }

    void ITest$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.ITest.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        // struct ITest.Test
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.ITest$$Test", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.ITest.Test", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("id", $$T_Str, $$UNDEF, "w");
                po.addFld("title", $$T_Str, $$UNDEF, "w");
        // struct ITest.TestAttrs
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.ITest$$TestAttrs", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.ITest.TestAttrs", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("description", $$T_Str, $$UNDEF, "w");
                po.addFld("isPerformanceTest", $$T_Bool, $$UNDEF, "w");
        // struct ITest.CompilerParams
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.ITest$$CompilerParams", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.ITest.CompilerParams", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("isTICompiler", $$T_Bool, $$UNDEF, "w");
                po.addFld("isC6x", $$T_Bool, $$UNDEF, "w");
                po.addFld("libFormat", $$T_Str, $$UNDEF, "w");
                po.addFld("version", $$T_Str, $$UNDEF, "w");
                po.addFld("log", $$T_Str, $$UNDEF, "w");
        // struct ITest.AlgoParams
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.ITest$$AlgoParams", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.ITest.AlgoParams", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("moduleName", $$T_Str, $$UNDEF, "w");
                po.addFld("vendor", $$T_Str, $$UNDEF, "w");
                po.addFld("interfaceName", $$T_Str, $$UNDEF, "w");
                po.addFld("architecture", $$T_Str, $$UNDEF, "w");
                po.addFld("baseDir", $$T_Str, $$UNDEF, "w");
                po.addFld("library", $$T_Str, $$UNDEF, "w");
                po.addFld("headers", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
                po.addFld("compilerParams", (Proto)om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"), $$DEFAULT, "w");
        // struct ITest.TestSettings
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.ITest$$TestSettings", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.ITest.TestSettings", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cgtoolsDir", $$T_Str, $$UNDEF, "w");
                po.addFld("cgxmlDir", $$T_Str, $$UNDEF, "w");
        // struct ITest.TestResult
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.ITest$$TestResult", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.ITest.TestResult", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("status", (Proto)om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"), $$UNDEF, "w");
                po.addFld("statusDetails", $$T_Str, $$UNDEF, "w");
                po.addFld("runResult", (Proto)om.findStrict("ti.xdais.qualiti.System.RunResult", "ti.xdais.qualiti"), $$DEFAULT, "w");
    }

    void Compiler$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/qualiti/Compiler.xs");
        om.bind("ti.xdais.qualiti.Compiler$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Compiler.Module", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.Compiler.Module", om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.xdais.qualiti.Compiler$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.xdais.qualiti.Compiler$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.xdais.qualiti.Compiler$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "reset");
                if (fxn != null) po.addFxn("reset", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$reset", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "getAttrs");
                if (fxn != null) po.addFxn("getAttrs", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$getAttrs", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$run", "ti.xdais.qualiti"), fxn);
                po.addFxn("getCompilerInfo", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.Compiler$$getCompilerInfo", "ti.xdais.qualiti"), Global.get(cap, "getCompilerInfo"));
    }

    void Rules8_9_10$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/qualiti/Rules8_9_10.xs");
        om.bind("ti.xdais.qualiti.Rules8_9_10$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rules8_9_10.Module", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.Rules8_9_10.Module", om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("tests", new Proto.Arr((Proto)om.findStrict("ti.xdais.qualiti.Rules8_9_10.Test", "ti.xdais.qualiti"), false), Global.newArray(new Object[]{Global.newObject("id", "XDAIS Rules 8, 9 and 10", "title", "XDAIS Rules 8, 9, 10: Namespace compliance")}), "rh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rules8_9_10$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rules8_9_10$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rules8_9_10$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "reset");
                if (fxn != null) po.addFxn("reset", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$reset", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "getAttrs");
                if (fxn != null) po.addFxn("getAttrs", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$getAttrs", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$run", "ti.xdais.qualiti"), fxn);
    }

    void Rule12$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/qualiti/Rule12.xs");
        om.bind("ti.xdais.qualiti.Rule12$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rule12.Module", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.Rule12.Module", om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("tests", new Proto.Arr((Proto)om.findStrict("ti.xdais.qualiti.Rule12.Test", "ti.xdais.qualiti"), false), Global.newArray(new Object[]{Global.newObject("id", "XDAIS Rule 12", "title", "XDAIS Rule 12: IALG interface implementation")}), "rh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rule12$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rule12$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rule12$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "reset");
                if (fxn != null) po.addFxn("reset", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$reset", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "getAttrs");
                if (fxn != null) po.addFxn("getAttrs", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$getAttrs", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$run", "ti.xdais.qualiti"), fxn);
    }

    void Rules13_26$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/qualiti/Rules13_26.xs");
        om.bind("ti.xdais.qualiti.Rules13_26$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rules13_26.Module", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.Rules13_26.Module", om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("tests", new Proto.Arr((Proto)om.findStrict("ti.xdais.qualiti.Rules13_26.Test", "ti.xdais.qualiti"), false), Global.newArray(new Object[]{Global.newObject("id", "XDAIS Rule 13+", "title", "XDAIS Rule 13+: correct linker section names"), Global.newObject("id", "XDAIS Rule 26", "title", "XDAIS Rule 26: All static/global data must be far on c6x")}), "rh");
        po.addFld("standardSections", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{".cinit", ".switch", ".far", ".text", ".const", ".econst", ".bss", ".ebss", ".pinit", ".data", ".fardata"}), "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rules13_26$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rules13_26$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rules13_26$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "reset");
                if (fxn != null) po.addFxn("reset", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$reset", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "getAttrs");
                if (fxn != null) po.addFxn("getAttrs", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$getAttrs", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$run", "ti.xdais.qualiti"), fxn);
    }

    void Rule20$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/qualiti/Rule20.xs");
        om.bind("ti.xdais.qualiti.Rule20$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rule20.Module", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.Rule20.Module", om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("tests", new Proto.Arr((Proto)om.findStrict("ti.xdais.qualiti.Rule20.Test", "ti.xdais.qualiti"), false), Global.newArray(new Object[]{Global.newObject("id", "XDAIS Rule 20", "title", "XDAIS Rule 20: must declare worst-case stack requirements")}), "rh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rule20$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rule20$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rule20$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "reset");
                if (fxn != null) po.addFxn("reset", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$reset", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "getAttrs");
                if (fxn != null) po.addFxn("getAttrs", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$getAttrs", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$run", "ti.xdais.qualiti"), fxn);
    }

    void Rules21_22$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/qualiti/Rules21_22.xs");
        om.bind("ti.xdais.qualiti.Rules21_22$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rules21_22.Module", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.Rules21_22.Module", om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("tests", new Proto.Arr((Proto)om.findStrict("ti.xdais.qualiti.Rules21_22.Test", "ti.xdais.qualiti"), false), Global.newArray(new Object[]{Global.newObject("id", "XDAIS Rules 21, 22", "title", "XDAIS Rules 21, 22: must characterize static data & program memory requirements")}), "rh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rules21_22$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rules21_22$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rules21_22$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "reset");
                if (fxn != null) po.addFxn("reset", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$reset", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "getAttrs");
                if (fxn != null) po.addFxn("getAttrs", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$getAttrs", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$run", "ti.xdais.qualiti"), fxn);
    }

    void Rule25$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/xdais/qualiti/Rule25.xs");
        om.bind("ti.xdais.qualiti.Rule25$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rule25.Module", "ti.xdais.qualiti");
        po.init("ti.xdais.qualiti.Rule25.Module", om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("tests", new Proto.Arr((Proto)om.findStrict("ti.xdais.qualiti.Rule25.Test", "ti.xdais.qualiti"), false), Global.newArray(new Object[]{Global.newObject("id", "XDAIS Rule 25", "title", "XDAIS Rule 25: All C6x algorithms must be supplied in little-endian format")}), "rh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rule25$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rule25$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.xdais.qualiti.Rule25$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "reset");
                if (fxn != null) po.addFxn("reset", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$reset", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "getAttrs");
                if (fxn != null) po.addFxn("getAttrs", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$getAttrs", "ti.xdais.qualiti"), fxn);
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("ti.xdais.qualiti.ITest$$run", "ti.xdais.qualiti"), fxn);
    }

    void Main$$ROV()
    {
    }

    void System$$ROV()
    {
    }

    void ITest$$ROV()
    {
    }

    void Compiler$$ROV()
    {
    }

    void Rules8_9_10$$ROV()
    {
    }

    void Rule12$$ROV()
    {
    }

    void Rules13_26$$ROV()
    {
    }

    void Rule20$$ROV()
    {
    }

    void Rules21_22$$ROV()
    {
    }

    void Rule25$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.xdais.qualiti.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.xdais.qualiti"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.xdais.qualiti", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.xdais.qualiti");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.xdais.qualiti.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.tools.sg", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.xdais.qualiti'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Main$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.qualiti.Main", "ti.xdais.qualiti");
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Main.Module", "ti.xdais.qualiti");
        vo.init2(po, "ti.xdais.qualiti.Main", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.xdais.qualiti.Main$$capsule", "ti.xdais.qualiti"));
        vo.bind("Instance", om.findStrict("ti.xdais.qualiti.Main.Instance", "ti.xdais.qualiti"));
        vo.bind("Params", om.findStrict("ti.xdais.qualiti.Main.Params", "ti.xdais.qualiti"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.xdais.qualiti.Main.Params", "ti.xdais.qualiti")).newInstance());
        vo.bind("$package", om.findStrict("ti.xdais.qualiti", "ti.xdais.qualiti"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.tools");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.qualiti")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.qualiti.Main$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.xdais.qualiti.Main.Object", "ti.xdais.qualiti"));
        pkgV.bind("Main", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Main");
    }

    void System$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.qualiti.System", "ti.xdais.qualiti");
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.System.Module", "ti.xdais.qualiti");
        vo.init2(po, "ti.xdais.qualiti.System", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.xdais.qualiti.System$$capsule", "ti.xdais.qualiti"));
        vo.bind("$package", om.findStrict("ti.xdais.qualiti", "ti.xdais.qualiti"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("RunResult", om.findStrict("ti.xdais.qualiti.System.RunResult", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.System.RunResult", "ti.xdais.qualiti"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.qualiti")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.qualiti.System$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("System", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("System");
    }

    void ITest$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.qualiti.ITest", "ti.xdais.qualiti");
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.ITest.Module", "ti.xdais.qualiti");
        vo.init2(po, "ti.xdais.qualiti.ITest", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.xdais.qualiti", "ti.xdais.qualiti"));
        tdefs.clear();
        proxies.clear();
        inherits.clear();
        vo.bind("TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        vo.bind("TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        vo.bind("Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        vo.bind("TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        vo.bind("CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        vo.bind("AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        vo.bind("TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        vo.bind("TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTRUN", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTRUN", "ti.xdais.qualiti"));
        vo.bind("TEST_PASS", om.findStrict("ti.xdais.qualiti.ITest.TEST_PASS", "ti.xdais.qualiti"));
        vo.bind("TEST_FAIL", om.findStrict("ti.xdais.qualiti.ITest.TEST_FAIL", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTAPPLY", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTAPPLY", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNNING", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNNING", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNERROR", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNERROR", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_FAILDETAILS", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_FAILDETAILS", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTLOG", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTLOG", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTOUTPUT", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTOUTPUT", "ti.xdais.qualiti"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ITest", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ITest");
        vo.seal(null);
    }

    void Compiler$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.qualiti.Compiler", "ti.xdais.qualiti");
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Compiler.Module", "ti.xdais.qualiti");
        vo.init2(po, "ti.xdais.qualiti.Compiler", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.xdais.qualiti.Compiler$$capsule", "ti.xdais.qualiti"));
        vo.bind("$package", om.findStrict("ti.xdais.qualiti", "ti.xdais.qualiti"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        vo.bind("TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        vo.bind("Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        vo.bind("TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        vo.bind("CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        vo.bind("AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        vo.bind("TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        vo.bind("TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTRUN", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTRUN", "ti.xdais.qualiti"));
        vo.bind("TEST_PASS", om.findStrict("ti.xdais.qualiti.ITest.TEST_PASS", "ti.xdais.qualiti"));
        vo.bind("TEST_FAIL", om.findStrict("ti.xdais.qualiti.ITest.TEST_FAIL", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTAPPLY", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTAPPLY", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNNING", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNNING", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNERROR", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNERROR", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_FAILDETAILS", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_FAILDETAILS", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTLOG", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTLOG", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTOUTPUT", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTOUTPUT", "ti.xdais.qualiti"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.xdais.qualiti");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.qualiti")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.qualiti.Compiler$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Compiler", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Compiler");
    }

    void Rules8_9_10$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.qualiti.Rules8_9_10", "ti.xdais.qualiti");
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rules8_9_10.Module", "ti.xdais.qualiti");
        vo.init2(po, "ti.xdais.qualiti.Rules8_9_10", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.xdais.qualiti.Rules8_9_10$$capsule", "ti.xdais.qualiti"));
        vo.bind("$package", om.findStrict("ti.xdais.qualiti", "ti.xdais.qualiti"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        vo.bind("TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        vo.bind("Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        vo.bind("TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        vo.bind("CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        vo.bind("AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        vo.bind("TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        vo.bind("TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTRUN", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTRUN", "ti.xdais.qualiti"));
        vo.bind("TEST_PASS", om.findStrict("ti.xdais.qualiti.ITest.TEST_PASS", "ti.xdais.qualiti"));
        vo.bind("TEST_FAIL", om.findStrict("ti.xdais.qualiti.ITest.TEST_FAIL", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTAPPLY", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTAPPLY", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNNING", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNNING", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNERROR", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNERROR", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_FAILDETAILS", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_FAILDETAILS", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTLOG", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTLOG", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTOUTPUT", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTOUTPUT", "ti.xdais.qualiti"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.xdais.qualiti");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.qualiti")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.qualiti.Rules8_9_10$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Rules8_9_10", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Rules8_9_10");
    }

    void Rule12$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.qualiti.Rule12", "ti.xdais.qualiti");
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rule12.Module", "ti.xdais.qualiti");
        vo.init2(po, "ti.xdais.qualiti.Rule12", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.xdais.qualiti.Rule12$$capsule", "ti.xdais.qualiti"));
        vo.bind("$package", om.findStrict("ti.xdais.qualiti", "ti.xdais.qualiti"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        vo.bind("TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        vo.bind("Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        vo.bind("TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        vo.bind("CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        vo.bind("AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        vo.bind("TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        vo.bind("TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTRUN", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTRUN", "ti.xdais.qualiti"));
        vo.bind("TEST_PASS", om.findStrict("ti.xdais.qualiti.ITest.TEST_PASS", "ti.xdais.qualiti"));
        vo.bind("TEST_FAIL", om.findStrict("ti.xdais.qualiti.ITest.TEST_FAIL", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTAPPLY", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTAPPLY", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNNING", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNNING", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNERROR", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNERROR", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_FAILDETAILS", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_FAILDETAILS", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTLOG", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTLOG", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTOUTPUT", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTOUTPUT", "ti.xdais.qualiti"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.xdais.qualiti");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.qualiti")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.qualiti.Rule12$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Rule12", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Rule12");
    }

    void Rules13_26$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.qualiti.Rules13_26", "ti.xdais.qualiti");
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rules13_26.Module", "ti.xdais.qualiti");
        vo.init2(po, "ti.xdais.qualiti.Rules13_26", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.xdais.qualiti.Rules13_26$$capsule", "ti.xdais.qualiti"));
        vo.bind("$package", om.findStrict("ti.xdais.qualiti", "ti.xdais.qualiti"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        vo.bind("TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        vo.bind("Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        vo.bind("TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        vo.bind("CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        vo.bind("AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        vo.bind("TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        vo.bind("TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTRUN", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTRUN", "ti.xdais.qualiti"));
        vo.bind("TEST_PASS", om.findStrict("ti.xdais.qualiti.ITest.TEST_PASS", "ti.xdais.qualiti"));
        vo.bind("TEST_FAIL", om.findStrict("ti.xdais.qualiti.ITest.TEST_FAIL", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTAPPLY", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTAPPLY", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNNING", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNNING", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNERROR", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNERROR", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_FAILDETAILS", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_FAILDETAILS", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTLOG", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTLOG", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTOUTPUT", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTOUTPUT", "ti.xdais.qualiti"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.xdais.qualiti");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.qualiti")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.qualiti.Rules13_26$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Rules13_26", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Rules13_26");
    }

    void Rule20$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.qualiti.Rule20", "ti.xdais.qualiti");
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rule20.Module", "ti.xdais.qualiti");
        vo.init2(po, "ti.xdais.qualiti.Rule20", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.xdais.qualiti.Rule20$$capsule", "ti.xdais.qualiti"));
        vo.bind("$package", om.findStrict("ti.xdais.qualiti", "ti.xdais.qualiti"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        vo.bind("TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        vo.bind("Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        vo.bind("TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        vo.bind("CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        vo.bind("AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        vo.bind("TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        vo.bind("TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTRUN", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTRUN", "ti.xdais.qualiti"));
        vo.bind("TEST_PASS", om.findStrict("ti.xdais.qualiti.ITest.TEST_PASS", "ti.xdais.qualiti"));
        vo.bind("TEST_FAIL", om.findStrict("ti.xdais.qualiti.ITest.TEST_FAIL", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTAPPLY", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTAPPLY", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNNING", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNNING", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNERROR", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNERROR", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_FAILDETAILS", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_FAILDETAILS", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTLOG", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTLOG", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTOUTPUT", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTOUTPUT", "ti.xdais.qualiti"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.xdais.qualiti");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.qualiti")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.qualiti.Rule20$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Rule20", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Rule20");
    }

    void Rules21_22$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.qualiti.Rules21_22", "ti.xdais.qualiti");
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rules21_22.Module", "ti.xdais.qualiti");
        vo.init2(po, "ti.xdais.qualiti.Rules21_22", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.xdais.qualiti.Rules21_22$$capsule", "ti.xdais.qualiti"));
        vo.bind("$package", om.findStrict("ti.xdais.qualiti", "ti.xdais.qualiti"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        vo.bind("TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        vo.bind("Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        vo.bind("TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        vo.bind("CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        vo.bind("AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        vo.bind("TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        vo.bind("TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTRUN", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTRUN", "ti.xdais.qualiti"));
        vo.bind("TEST_PASS", om.findStrict("ti.xdais.qualiti.ITest.TEST_PASS", "ti.xdais.qualiti"));
        vo.bind("TEST_FAIL", om.findStrict("ti.xdais.qualiti.ITest.TEST_FAIL", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTAPPLY", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTAPPLY", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNNING", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNNING", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNERROR", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNERROR", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_FAILDETAILS", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_FAILDETAILS", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTLOG", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTLOG", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTOUTPUT", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTOUTPUT", "ti.xdais.qualiti"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.xdais.qualiti");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.qualiti")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.qualiti.Rules21_22$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Rules21_22", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Rules21_22");
    }

    void Rule25$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.xdais.qualiti.Rule25", "ti.xdais.qualiti");
        po = (Proto.Obj)om.findStrict("ti.xdais.qualiti.Rule25.Module", "ti.xdais.qualiti");
        vo.init2(po, "ti.xdais.qualiti.Rule25", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.xdais.qualiti.Rule25$$capsule", "ti.xdais.qualiti"));
        vo.bind("$package", om.findStrict("ti.xdais.qualiti", "ti.xdais.qualiti"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("TestStatus", om.findStrict("ti.xdais.qualiti.ITest.TestStatus", "ti.xdais.qualiti"));
        vo.bind("TestDetailLevel", om.findStrict("ti.xdais.qualiti.ITest.TestDetailLevel", "ti.xdais.qualiti"));
        vo.bind("Test", om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.Test", "ti.xdais.qualiti"));
        vo.bind("TestAttrs", om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestAttrs", "ti.xdais.qualiti"));
        vo.bind("CompilerParams", om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.CompilerParams", "ti.xdais.qualiti"));
        vo.bind("AlgoParams", om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.AlgoParams", "ti.xdais.qualiti"));
        vo.bind("TestSettings", om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestSettings", "ti.xdais.qualiti"));
        vo.bind("TestResult", om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        tdefs.add(om.findStrict("ti.xdais.qualiti.ITest.TestResult", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTRUN", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTRUN", "ti.xdais.qualiti"));
        vo.bind("TEST_PASS", om.findStrict("ti.xdais.qualiti.ITest.TEST_PASS", "ti.xdais.qualiti"));
        vo.bind("TEST_FAIL", om.findStrict("ti.xdais.qualiti.ITest.TEST_FAIL", "ti.xdais.qualiti"));
        vo.bind("TEST_NOTAPPLY", om.findStrict("ti.xdais.qualiti.ITest.TEST_NOTAPPLY", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNNING", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNNING", "ti.xdais.qualiti"));
        vo.bind("TEST_RUNERROR", om.findStrict("ti.xdais.qualiti.ITest.TEST_RUNERROR", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_FAILDETAILS", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_FAILDETAILS", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTLOG", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTLOG", "ti.xdais.qualiti"));
        vo.bind("DETAILLEVEL_TESTOUTPUT", om.findStrict("ti.xdais.qualiti.ITest.DETAILLEVEL_TESTOUTPUT", "ti.xdais.qualiti"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.xdais.qualiti");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.xdais.qualiti")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.xdais.qualiti.Rule25$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Rule25", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Rule25");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.qualiti.Main", "ti.xdais.qualiti"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.qualiti.System", "ti.xdais.qualiti"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.qualiti.Compiler", "ti.xdais.qualiti"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.qualiti.Rules8_9_10", "ti.xdais.qualiti"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.qualiti.Rule12", "ti.xdais.qualiti"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.qualiti.Rules13_26", "ti.xdais.qualiti"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.qualiti.Rule20", "ti.xdais.qualiti"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.qualiti.Rules21_22", "ti.xdais.qualiti"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.xdais.qualiti.Rule25", "ti.xdais.qualiti"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.xdais.qualiti.Main")).bless();
        ((Value.Obj)om.getv("ti.xdais.qualiti.System")).bless();
        ((Value.Obj)om.getv("ti.xdais.qualiti.ITest")).bless();
        ((Value.Obj)om.getv("ti.xdais.qualiti.Compiler")).bless();
        ((Value.Obj)om.getv("ti.xdais.qualiti.Rules8_9_10")).bless();
        ((Value.Obj)om.getv("ti.xdais.qualiti.Rule12")).bless();
        ((Value.Obj)om.getv("ti.xdais.qualiti.Rules13_26")).bless();
        ((Value.Obj)om.getv("ti.xdais.qualiti.Rule20")).bless();
        ((Value.Obj)om.getv("ti.xdais.qualiti.Rules21_22")).bless();
        ((Value.Obj)om.getv("ti.xdais.qualiti.Rule25")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.xdais.qualiti")).add(pkgV);
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
        Main$$OBJECTS();
        System$$OBJECTS();
        ITest$$OBJECTS();
        Compiler$$OBJECTS();
        Rules8_9_10$$OBJECTS();
        Rule12$$OBJECTS();
        Rules13_26$$OBJECTS();
        Rule20$$OBJECTS();
        Rules21_22$$OBJECTS();
        Rule25$$OBJECTS();
        Main$$CONSTS();
        System$$CONSTS();
        ITest$$CONSTS();
        Compiler$$CONSTS();
        Rules8_9_10$$CONSTS();
        Rule12$$CONSTS();
        Rules13_26$$CONSTS();
        Rule20$$CONSTS();
        Rules21_22$$CONSTS();
        Rule25$$CONSTS();
        Main$$CREATES();
        System$$CREATES();
        ITest$$CREATES();
        Compiler$$CREATES();
        Rules8_9_10$$CREATES();
        Rule12$$CREATES();
        Rules13_26$$CREATES();
        Rule20$$CREATES();
        Rules21_22$$CREATES();
        Rule25$$CREATES();
        Main$$FUNCTIONS();
        System$$FUNCTIONS();
        ITest$$FUNCTIONS();
        Compiler$$FUNCTIONS();
        Rules8_9_10$$FUNCTIONS();
        Rule12$$FUNCTIONS();
        Rules13_26$$FUNCTIONS();
        Rule20$$FUNCTIONS();
        Rules21_22$$FUNCTIONS();
        Rule25$$FUNCTIONS();
        Main$$SIZES();
        System$$SIZES();
        ITest$$SIZES();
        Compiler$$SIZES();
        Rules8_9_10$$SIZES();
        Rule12$$SIZES();
        Rules13_26$$SIZES();
        Rule20$$SIZES();
        Rules21_22$$SIZES();
        Rule25$$SIZES();
        Main$$TYPES();
        System$$TYPES();
        ITest$$TYPES();
        Compiler$$TYPES();
        Rules8_9_10$$TYPES();
        Rule12$$TYPES();
        Rules13_26$$TYPES();
        Rule20$$TYPES();
        Rules21_22$$TYPES();
        Rule25$$TYPES();
        if (isROV) {
            Main$$ROV();
            System$$ROV();
            ITest$$ROV();
            Compiler$$ROV();
            Rules8_9_10$$ROV();
            Rule12$$ROV();
            Rules13_26$$ROV();
            Rule20$$ROV();
            Rules21_22$$ROV();
            Rule25$$ROV();
        }//isROV
        $$SINGLETONS();
        Main$$SINGLETONS();
        System$$SINGLETONS();
        ITest$$SINGLETONS();
        Compiler$$SINGLETONS();
        Rules8_9_10$$SINGLETONS();
        Rule12$$SINGLETONS();
        Rules13_26$$SINGLETONS();
        Rule20$$SINGLETONS();
        Rules21_22$$SINGLETONS();
        Rule25$$SINGLETONS();
        $$INITIALIZATION();
    }
}
