/*
 * Copyright (c) 2006-2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/* TODO:M  Need to autogen this version based on XDAIS release. */
var appVersion    = "7.20";
var appTitle      = "QualiTI [" + appVersion + "]";
var appShellTitle = "Texas Instruments: " + appTitle;

var os = java.lang.System.getProperty("os.name") + "";
var isWin = (os.match(/^Windows/i) != null);
var pathSeparator = isWin ? "\\" : "/";
var iniFilesDir;

// self properties, initialized in below, used throughout
var thisMod;
var thisPkg;
var thisPkgDir;
var ITest;
var Compiler;
var System;
var csd = String(xdc.csd()).replace(/\\/g,"/") + '/';
var instructions = xdc.loadCapsule( "help.xs" );
var ecParent = null;

var validLibExt = {'l64P':'', 'l674':'', 'l470':'', 'lv5T':'', 'lv6':'', 'lv7A':''};

function module$meta$init()
{
    thisPkg     = this.$package;
    thisPkgDir  = csd;
    thisMod     = this;
    ITest       = xdc.module( thisPkg.$name + ".ITest" );
    Compiler    = xdc.module( thisPkg.$name + ".Compiler" );
    System      = xdc.module( thisPkg.$name + ".System" );

    if (isWin) {
        iniFilesDir = environment[ "user.home" ] + "/Application Data/QualiTI/";
        if (!java.io.File( iniFilesDir ).exists()) {
            java.io.File( iniFilesDir ).mkdir();
        }
    } else {
        iniFilesDir = environment[ "user.home" ] + "/";
    }
}

var browser;
var custom;
var graphics;
var layout;
var widgets;
var events;
var swt;
var SWT;

function initSWT()
{
// references to required SWT Java packages (Standard Windowing Toolkit)
    browser  = xdc.jre.org.eclipse.swt.browser;
    custom   = xdc.jre.org.eclipse.swt.custom;
    graphics = xdc.jre.org.eclipse.swt.graphics;
    layout   = xdc.jre.org.eclipse.swt.layout;
    widgets  = xdc.jre.org.eclipse.swt.widgets;
    events   = xdc.jre.org.eclipse.swt.events;
    swt      = xdc.jre.org.eclipse.swt;
    SWT      = xdc.jre.org.eclipse.swt.SWT;
}

// standard font size
var STANDARD_FONT_SIZE = 8;

// fixed width font
var FIXED_WIDTH_FONT_NAME = "Lucida Console"; // "Terminal" also looks great
var FIXED_WIDTH_FONT_SIZE = 8;
if (!isWin) {
    FIXED_WIDTH_FONT_NAME = "Courier New";
    FIXED_WIDTH_FONT_SIZE = 7;
}

var NUMBER_OF_VISIBLE_TABLE_ROWS = 4;

// debugging -- turn it on or off by commenting out one or the other Fxn
var debugFxn = print;                // this turns debugging on
// var debugFxn = function() {}      // this turns debugging off

var display = null;
var shell   = null;

// hash table of all the widgets in the application window
var myWidgets = {};

var tests = [];
var numFailedTests = 0;

var compilerLog = "";
var architectureLog = "";
var cgxmlLog = "";
var libraryLog = "";

var lastGeneratedReport = null;

var projectFile = undefined;

var LIB_WARNING = ' does not have a valid extension. If it is not a valid library, ofd6x will not be able to recognize it.';

var XDCVERS_MSG = 'The version of xdctools is older than 3.05. Restart '
+'QualiTI with xdctools 3.05 or higher.';

var MIN_CGXML_VERS = 2.12;
var CGXML_VERS_MSG = "cg_xml 2.12 or greater is required";

function getTests()
{
    var mods = thisPkg.$modules;
    var i, j;
    for (i = 0; i < mods.length; i++) {
        var mod = mods[i];
        if (mod.$name == thisMod.$name ||
            mod.$name == thisPkg.$name + ".System" ||
            mod.$name == thisPkg.$name + ".Compiler") {
            continue;
        }
        for (j = 0; j < mod.tests.length; j++) {
            var attrs = mod.getAttrs( mod.tests[j].id );
            var test = {
                mod:               mod,
                modName:           mod.$name,
                id:                mod.tests[j].id,
                title:             mod.tests[j].title,
                description:       attrs.description,
                isPerformanceTest: attrs.isPerformanceTest,
                status:            ITest.TEST_NOTRUN,
                statusDetails:     "Test has not been run yet.",
                log:               "",
                doTest:            true
            };
            tests[ tests.length ] = test;
        }
    }

    // sort the tests by its first word and first number
    function getTestIdSortValue( id )
    {
        var w = id.split( " " )[0];
        var n = parseInt( id.replace( /^[^0-9]+/, "" ) );
        return w + (n < 10 ? "00" : n < 100 ? "0" : "") + n;
    }
    for (i = 0; i < tests.length - 1; i++) {
        for (j = i + 1; j < tests.length; j++) {
            if (getTestIdSortValue( tests[j].id ) < getTestIdSortValue( tests[i].id )) {
                var x = tests[i];
                tests[i] = tests[j];
                tests[j] = x;
            }
        }
    }
}


function generateHTMLReport( outFileName, algorithm, testSettings, diffFriendly )
{
    var t = xdc.loadTemplate( thisPkg.$name.replace( /\./g, "/") +
            "/report.html.xdt" );
    try {
        t.genFile( outFileName,
            {
                algorithm:    algorithm,
                tests:        tests,
                ITest:        ITest,
                version:      appVersion,
                testSettings: testSettings,
                diffFriendly: diffFriendly
            }
        );
    }
    catch(e) {
        var message = "ERROR: Could not create HTML report file '" +
            outFileName + "'.\n\n" +
            "Check if you have write access to the report directory.\n\n" +
            "Details: " + e + "\n\n";
        throw( message );
    }
}

function guiMain(fileName, parent)
{
    initSWT();
    if (parent) {
        display = parent.getDisplay();
        ecParent = display;
    }
    else {
        display = new widgets.Display();
    }

    // create a shell window in which to display all screen controls (widgets)
    shell = new widgets.Shell(display, SWT.CLOSE| SWT.MIN|SWT.TITLE);
    shell.setLayout( new layout.RowLayout( SWT.VERTICAL ) );
    shell.setText( appShellTitle );
    shell.setImage( graphics.Image( display, thisPkgDir + "/ti.ico" ) );

    // call the function that lays out all the widgets to the shell
    layoutWidgets();

    // call the function that sets listener functions for important widgets
    setEventListeners();

    readIniFile();
    readToolsIniFile();
    var w = myWidgets;
    if (fileName) {
        openProject(fileName);
    }

    // set the initial "enbledness" state of the widgets (everything disabled)
    // setWidgetsState( { connected: false, started: false } );

    // position the shell window at the top
    var rect = shell.computeSize( SWT.DEFAULT, SWT.DEFAULT, true );
    var top  = 50;
    if (display.getBounds().height < 800) {
        top = 4;
    }
    shell.setBounds( 200, top, rect.x, rect.y - 14 );

    // activate the shell window
    shell.open();

    // while the shell window exists (i.e. the user didn't alt-F4-ed it)
    while(!shell.isDisposed()) {
        // call display's work queue; will return false if nothing to do
        if (!display.readAndDispatch()) {
            display.sleep();
        }
    }

    // sleep a little to let any sleeping threads finish
    java.lang.Thread.sleep( 300 );
}


// ======== layoutWidgets ========
//
// [4] This function uses "display" and "shell" to create and position all the
// GUI widgets on the screen, saving their references in the "myWidgets"
// hash table for later referencing by the event listeners for some widgets
//
function layoutWidgets()
{
    var w = myWidgets;  // alias

    var GD  = layout.GridData;

    var $w$stack = [];
    var $w = shell;

    function WID( w ) { $w$stack.push($w); $w = w; return $w; }
    function END() { $w = $w$stack.pop(); return $w; }
    function LBL( text ) {
        WID( widgets.Label( $w, SWT.NONE ) );
            $w.setText( text == undefined ? "" : text );
        END();
    }

    var RULETABLE_WIDTH  = 620;
    var FILENAMEBOX_LENGTH = 270;
    var RULETABLE_HEIGHT = 112; // change NUMBER_OF_VISIBLE_TABLE_ROWS when changing this
    var RULEDESC_HEIGHT  =  80;
    var REPORTLOG_HEIGHT    = 100;

    // expand the window a little more if we're not running on an old laptop
    var scrHeight = display.getBounds().height;
    if (scrHeight > 1050) {
        scrHeight = 1050;
    }
    if (scrHeight > 768) {
        var extra = scrHeight - 768 - 150;
        var increaseInRows = 1;
        var newRuleTableHeight = RULETABLE_HEIGHT * (NUMBER_OF_VISIBLE_TABLE_ROWS + increaseInRows) / NUMBER_OF_VISIBLE_TABLE_ROWS;
        if ((newRuleTableHeight - RULETABLE_HEIGHT) < extra) {
            extra -= (newRuleTableHeight - RULETABLE_HEIGHT);
            RULETABLE_HEIGHT = newRuleTableHeight;
            NUMBER_OF_VISIBLE_TABLE_ROWS += increaseInRows;
            RULEDESC_HEIGHT += extra * .4;
            REPORTLOG_HEIGHT += extra * .6;
        }
    }


    // create the widgets tree that defines the appearance of controls on the
    // screen; in myWidgets[] hash table store references of those widgets
    // that are to be read and written throughout the rest of the program
    //
    // Please see README-DemoApp.txt, section "Drawing screen controls"
    // for details. Look at http://www.eclipse.org/swt/widgets for APIs.

                                // top level Composite that holds all widgets
    w["cmpAll"] =               WID( widgets.Composite( $w, SWT.NONE ) );
                                    var gl = new layout.GridLayout( 2, false );
                                    gl.marginWidth = 4;
                                    $w.setLayout( gl );

                                    // upper Composite that holds Connection and "Target App" groups
                                    WID( widgets.Composite( $w, SWT.NONE ) );
                                        var gl = new layout.GridLayout( 1, false );
                                        gl.marginWidth = 2;
                                        $w.setLayout( gl );


    w["grpSettings"] =                  WID( widgets.Group( $w, SWT.NONE ) );
                                            $w.setText( "Settings" );
                                            var gl = layout.GridLayout( 1, false );
                                            gl.marginWidth = 6;
                                            $w.setLayout( gl );
                                            $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );

    w["tabFolderSettings"] =                WID( widgets.TabFolder( $w, SWT.NONE ) );
                                                $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );

    w["cmpAlgorithm"] =                         WID( widgets.Composite( $w, SWT.NONE ) );
                                                    var gl = new layout.GridLayout( 2, false );
                                                    gl.marginWidth = 6;
                                                    gl.horizontalSpacing = 6;
                                                    gl.verticalSpacing = 0;
                                                    $w.setLayout( gl );
                                                    // $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );

                                                    WID( widgets.Composite( $w, SWT.NONE ) );
                                                        var gl = new layout.GridLayout( 2, false );
                                                        gl.marginWidth = 0;
                                                        gl.horizontalSpacing = 10;
                                                        gl.verticalSpacing = 6;
                                                        $w.setLayout( gl );
                                                        $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );

                                                        LBL( "Module:" );
    w["txtModuleName"] =                                WID( widgets.Text( $w, SWT.BORDER ) );
                                                            $w.setLayoutData( GD( 90, SWT.DEFAULT ) );
                                                                $w.addListener (SWT.KeyUp, function(e) {
                                                                            w["txtInterfaceName"].setText( "I" + w["txtModuleName"].getText() );
                                                                });
                                                        END();
                                                        LBL( "Vendor:" );
    w["txtVendor"] =                                    WID( widgets.Text( $w, SWT.BORDER ) );
                                                            $w.setLayoutData( GD( 90, SWT.DEFAULT ) );
                                                        END();
                                                        LBL( "Interface:" );
    w["txtInterfaceName"] =                                 WID( widgets.Text( $w, SWT.BORDER ) );
                                                            $w.setLayoutData( GD( 90, SWT.DEFAULT ) );
                                                        END();

    w["cmbArchitecture"] =                              WID( widgets.Combo( $w, SWT.READ_ONLY ) );
                                                            $w.add( "C64P");
                                                            $w.add( "C674");
                                                            $w.add( "470");
                                                            $w.select( 0 );
                                                            $w.setLayoutData( GD( isWin ? 40 : 65, SWT.DEFAULT ) );
                                                        END();
    w["cmbArchitecture"].setVisible(false);
                                                    END();

                                                    WID( widgets.Composite( $w, SWT.NONE ) );
                                                        var gl = new layout.GridLayout( 4, false );
                                                        gl.marginWidth = 0;
                                                        gl.horizontalSpacing = 10;
                                                        gl.verticalSpacing = 4;
                                                        $w.setLayout( gl );
                                                        $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );

                                                        LBL( "Base Dir:" );
    w["txtBaseDir"] =                                   WID( widgets.Text( $w, SWT.BORDER ) );
                                                            $w.setLayoutData( GD( FILENAMEBOX_LENGTH, SWT.DEFAULT ) );
                                                        END();
                                                        WID( widgets.Button( $w, SWT.PUSH ) );
                                                            $w.setText( "..." );
                                                            $w.addListener( SWT.Selection, function( event ) {
                                                                var dialog = new widgets.DirectoryDialog( shell );
                                                                var baseDir = getGuiBaseDir();
                                                                dialog.setFilterPath(baseDir == "" ? environment["user.dir"] : baseDir);
                                                                var fileName = dialog.open();
                                                                if (fileName != null) {
                                                                    w["txtBaseDir"].setText( fileName );
                                                                }
                                                            } );
                                                        END();
                                                        LBL();
                                                        LBL( "Library:" );
    w["txtLibrary"] =                                   WID( widgets.Text( $w, SWT.BORDER ) );
                                                            $w.setLayoutData( GD( FILENAMEBOX_LENGTH, SWT.DEFAULT ) );
                                                        END();
                                                        WID( widgets.Button( $w, SWT.PUSH ) );
                                                            $w.setText( "..." );
                                                            $w.addListener( SWT.Selection, function( event ) {
                                                                var dialog = new widgets.FileDialog( shell );
                                                                var baseDir = getGuiBaseDir()
                                                                dialog.setFilterPath(baseDir);
                                                                dialog.setFilterExtensions(["*.*","*.l64*;*.a64*","*.l674;*.a674*","*.l470*;*.a470*"]);
                                                                var fileName = dialog.open();
                                                                if (fileName != null) {
                                                                    var name = fileName.replace(baseDir, "" );
                                                                    if (name.substr(0,1) == "/") {
                                                                        name = "." + name;
                                                                    }
                                                                    else if (name.substr(0,1) == "\\") {
                                                                        name = name.substr(1);
                                                                    }
                                                                    w["txtLibrary"].setText( name  );
                                                                    if ( name.match( " " ) ) {
                                                                        showMessage( "Warning: The library may not contain spaces." );
                                                                    }
/*
                                                                    var libExt = name.substr( name.lastIndexOf ( "." ) + 1 );
                                                                    if ( !( libExt in validLibExt ) ) {
                                                                        showMessage('Warning: ' + java.io.File(name).getName() + LIB_WARNING);
                                                                    }
                                                                    else {
                                                                        switch ( libExt ) {
                                                                        case "l64P":
                                                                            w["cmbArchitecture"].setText("C64P");
                                                                            break;
                                                                        case "l674":
                                                                            w["cmbArchitecture"].setText("C674");
                                                                            break;
                                                                        case "l470":
                                                                            w["cmbArchitecture"].setText("470");
                                                                            break;
                                                                        }
                                                                    }
*/
                                                                }
                                                            } );
                                                        END();
                                                        LBL();
                                                        LBL( "Headers:" );
            w["lstHeaders"] =                           WID( widgets.List( $w, SWT.BORDER | SWT.SINGLE ) );
                                                            var gd = GD( FILENAMEBOX_LENGTH + 5, 40 );
                                                            gd.horizontalAlignment = GD.END;
                                                            gl.marginWidth = 10;
                                                            $w.setLayoutData( gd );
                                                        END();
                                                        WID( widgets.Button( $w, SWT.PUSH ) );
                                                            $w.setText( "..." );
                                                            $w.addListener( SWT.Selection, function( event ) {
                                                                var dialog = new widgets.FileDialog( shell );
                                                                var baseDir = getGuiBaseDir();
                                                                dialog.setFilterPath(baseDir);
                                                                dialog.setFilterExtensions( [ "*.h", "*.*" ] );
                                                                var fileName = dialog.open();
                                                                if (fileName != null) {
                                                                    var name = fileName.replace(baseDir, "" );
                                                                    if (name.substr(0,1) == "/" || name.substr(0,1) == "\\") {
                                                                        name = "." + name;
                                                                    }
                                                                    w["lstHeaders"].add( name, 0 );
                                                                }
                                                            } );
                                                        END();
                                                        WID( widgets.Button( $w, SWT.PUSH ) );
                                                            $w.setText( "Clear" );
                                                            $w.addListener( SWT.Selection, function( event ) {
                                                                w["lstHeaders"].removeAll();
                                                            } );
                                                        END();

                                                    END();

                                                END();
    w["tabAlgorithm"] =                         WID( widgets.TabItem( $w, SWT.NONE ) );
                                                   $w.setText( " Algorithm " );
                                                   $w.setControl( w["cmpAlgorithm"] );
                                                END();

    w["cmpTools"] =                             WID( widgets.Composite( $w, SWT.NONE ) );
                                                    var gl = new layout.GridLayout( 3, false );
                                                    gl.marginWidth = gl.horizontalSpacing = 10;
                                                    gl.verticalSpacing = 4;
                                                    $w.setLayout( gl );
                                                    $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );

                                                    LBL( "TI 'cg_xml' tools Dir:" );
    w["txtCgxmlDir"] =                              WID( widgets.Text( $w, SWT.BORDER ) );
                                                        $w.setLayoutData( GD(400, SWT.DEFAULT ) );
                                                    END();
                                                    WID( widgets.Button( $w, SWT.PUSH ) );
                                                        $w.setText( "..." );
                                                        $w.addListener( SWT.Selection, function( event ) {
                                                            var dialog = new widgets.DirectoryDialog( shell );
                                                            dialog.setFilterPath( w["txtCgxmlDir"].getText() == "" ? environment["user.dir"] : w["txtCgxmlDir"].getText() );
                                                            var dirName = dialog.open();
                                                            if (dirName != null) {
                                                                w["txtCgxmlDir"].setText( dirName );
                                                                var validDir = true;
                                                                if (! (java.io.File( dirName + "/bin/sectti.exe").exists() ||
                                                                       java.io.File( dirName + "/bin/sectti").exists())) {
                                                                       validDir = false;
                                                                }
                                                                else if (! (java.io.File( dirName + "/bin/call_graph.exe").exists() ||
                                                                       java.io.File( dirName + "/bin/call_graph").exists())) {
                                                                       validDir = false;
                                                                }
                                                                if (! validDir ) {
                                                                    showMessage("Warning: directory '" + dirName + "' is not valid -- it must contain a 'bin' subdirectory "
                                                                                + "with 'sectti' and 'call_graph' executables.");
                                                                }
                                                            }
                                                        } );
                                                    END();
    var cgToolsLbl =                                WID(widgets.Label($w, SWT.NONE));
                                                        $w.setText("C6000 TI 'cgtools' Dir:");
                                                    END()
    w["txtC64PcgtoolsDir"] =                        WID( widgets.Text( $w, SWT.BORDER ) );
                                                        $w.setLayoutData( GD(400, SWT.DEFAULT ) );
                                                    END();
    var cgtoolsBtn =                                WID( widgets.Button( $w, SWT.PUSH ) );
                                                        $w.setText( "..." );
                                                        $w.addListener( SWT.Selection, function( event ) {
                                                            var dialog = new widgets.DirectoryDialog( shell );
                                                            dialog.setFilterPath( w["txtC64PcgtoolsDir"].getText() == "" ? environment["user.dir"] : w["txtC64PcgtoolsDir"].getText() );
                                                            var dirName = dialog.open();
                                                            if (dirName != null) {
                                                                w["txtC64PcgtoolsDir"].setText( dirName );
                                                                var validDir = true;
                                                                if (! (java.io.File( dirName + "/bin/nm6x.exe" ).exists() ||
                                                                        java.io.File( dirName + "/bin/nm6x" ).exists()) ) {
                                                                        validDir = false;
                                                                }
                                                                else if (! (java.io.File( dirName + "/bin/ofd6x.exe").exists() ||
                                                                       java.io.File( dirName + "/bin/ofd6x").exists())) {
                                                                       validDir = false;
                                                                }
                                                                if (! validDir ) {
                                                                    showMessage( "Warning: directory '" + dirName + "' is not valid -- it must contain a 'bin' subdirectory with "
                                                                                    + " 'nm6x' and 'ofd6x' executables." );
                                                                }
                                                            }
                                                        } );
                                                    END();
   // cgToolsLbl.setVisible(false);
   // w["txtC64PcgtoolsDir"].setVisible(false);
      w["txtC64PcgtoolsDir"].setEditable(false);
    cgtoolsBtn.setVisible(false);
                                                    WID( widgets.Group( $w, SWT.NONE ) );
                                                        $w.setText( "Note" );
                                                        var gl = layout.GridLayout(1, false );
                                                        $w.setLayout( gl );
                                                        var gd = layout.GridData()
                                                        gd.horizontalSpan = 2;
                                                        $w.setLayoutData(gd);
                                                        LBL("C6000 TI 'cgtools' are currently bundled with QualiTI and cannot be edited." );
                                                    END();
                                                END();
    w["tabTools"] =                             WID( widgets.TabItem( $w, SWT.NONE ) );
                                                   $w.setText( " Tools " );
                                                   $w.setControl( w["cmpTools"] );
                                                END();



    w["cmpReport"] =                            WID( widgets.Composite( $w, SWT.NONE ) );
                                                    var gl = new layout.GridLayout( 3, false );
                                                    gl.marginWidth = gl.horizontalSpacing = 10;
                                                    gl.verticalSpacing = 4;
                                                    $w.setLayout( gl );
                                                    $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );


        w["radioReportInBaseDir"] =                 WID( widgets.Button( $w, SWT.RADIO ) );
                                                        $w.setText( "Create Report in Algorithm Base Directory        " );
                                                        $w.setSelection( true );
                                                    END();

        w["chkEmbedTimeStampInReportName"] =        WID( widgets.Button( $w, SWT.CHECK ) );
                                                        $w.setText( "Embed Date and Time in Report Filename" );
                                                    END();
                                                    LBL();

        w["radioReportInAlgLibDir"] =               WID( widgets.Button( $w, SWT.RADIO ) );
                                                        $w.setText( "Create Report in Algorithm Library Directory" );
                                                        $w.setSelection( false );
                                                    END();

        w["chkDiffFriendlyReport"] =                WID( widgets.Button( $w, SWT.CHECK ) );
                                                        $w.setText( "Make Report &diff Friendly" );
                                                    END();
                                                    LBL();

        w["radioReportInDir"] =                     WID( widgets.Button( $w, SWT.RADIO ) );
                                                        $w.setText( "Create Report in a Custom Directory:" );
                                                        $w.setSelection( false );
                                                    END();

w["txtReportDir"] =                                 WID( widgets.Text( $w, SWT.BORDER ) );
                                                        $w.setLayoutData( GD( FILENAMEBOX_LENGTH - 30, SWT.DEFAULT ) );
                                                    END();

                                                    WID( widgets.Button( $w, SWT.PUSH ) );
                                                        $w.setLayoutData( GD( SWT.DEFAULT, isWin ? 20 : SWT.DEFAULT ) );
                                                        $w.setText( "..." );
                                                        $w.addListener( SWT.Selection, function( event ) {
                                                            var dialog = new widgets.DirectoryDialog( shell );
                                                            var baseDir = getGuiBaseDir();
                                                            dialog.setFilterPath(baseDir == "" ? environment["user.dir"] : baseDir);
                                                            var fileName = dialog.open();
                                                            if (fileName != null) {
                                                                w["txtReportDir"].setText( fileName );
                                                            }
                                                        } );
                                                    END();

        w["radioNoReport"] =                        WID( widgets.Button( $w, SWT.RADIO ) );
                                                        $w.setText( "Do Not Create Report" );
                                                        $w.setSelection( false );
                                                    END();
        w["btnOpenLastReport"] =                    WID( widgets.Button( $w, SWT.PUSH ) );
                                                        $w.setText( " &Open Last Generated Report " );
                                                        $w.setLayoutData( GD( SWT.DEFAULT, isWin ? 20 : SWT.DEFAULT ) );

                                                        $w.addListener( SWT.Selection, function( event ) {
                                                            if (lastGeneratedReport == null) {
                                                                showMessage( "No reports have been generated yet." );
                                                                return;
                                                            }
                                                            if (isWin) {
                                                                java.lang.Runtime.getRuntime().exec("cmd /c \"" + lastGeneratedReport + "\"");
                                                            }
                                                            else {
                                                                showMessage( "This button only works on Windows for now, sorry." );
                                                            }
                                                        } );
                                                    END();
                                                    LBL();

                                                END();

    w["tabReport"] =                            WID( widgets.TabItem( $w, SWT.NONE ) );
                                                   $w.setText( " R&eports " );
                                                   $w.setControl( w["cmpReport"] );
                                                END();

                                             END();
                                        END();

                                        // Rule table group
    w["grpRules"] =                     WID( widgets.Group( $w, SWT.NONE ) );
                                            $w.setText( "Rules" );
                                            var gl = layout.GridLayout( 1, false );
                                            gl.marginWidth = gl.horizontalSpacing = 6;
                                            gl.verticalSpacing = 2;
                                            $w.setLayout( gl );
                                            $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );

w["cmpTableRules"] =                        WID( widgets.Composite( $w, SWT.NONE ) );
                                                var gl = new layout.GridLayout( 1, false );
                                                gl.marginWidth = 0;
                                                gl.verticalSpacing = 0;
                                                $w.setLayout( gl );
                                                // create a table widget
            w["tableRules"] =                   WID( widgets.Table( $w, swt.SWT.SINGLE | swt.SWT.BORDER | swt.SWT.FULL_SELECTION | swt.SWT.CHECK ) );
                                                    $w.setLayoutData( layout.GridData( RULETABLE_WIDTH, RULETABLE_HEIGHT ) );
                                                    $w.setHeaderVisible( true );
                                                    $w.setLinesVisible( false );

                                                    // set column names
                                                    widgets.TableColumn( $w, swt.SWT.NONE ).setText( "Do" );    // 0
                                                    widgets.TableColumn( $w, swt.SWT.NONE ).setText( "Test Title" );    // 1
                                                    widgets.TableColumn( $w, swt.SWT.NONE ).setText( "Status" );     // 2
                                                    widgets.TableColumn( $w, swt.SWT.NONE ).setText( "" );        // 3
                                                    widgets.TableColumn( $w, swt.SWT.NONE ).setText( "" );        // 4

                                                    // populate table rows from the userIn.extMem array of objects
                                                    var tableHeight = 22;
                                                    var dummyImage = graphics.Image( null, tableHeight, tableHeight );
                                                    for (var i = 0; i < tests.length; i++) {
                                                        // create a new row
                                                        WID( widgets.TableItem( $w, swt.SWT.NULL ) );
                                                            // $w.setText( 0, "" + i );  // set column 0
                                                            $w.setText( 1, tests[i].title );
                                                            showTestStatusInTable( $w, 2, tests[i] );
                                                            $w.setText( 3, "                                                                  " );
                                                            bgColor = (i%2) ? swt.graphics.Color( null, /* 220, 240, */ 255, 255, 255 ) : swt.graphics.Color( null, 255, 255, 192 );
                                                            $w.setBackground( bgColor );
                                                            $w.setBackground( 0, bgColor );
                                                            $w.setImage( 4, dummyImage );
                                                            $w.setChecked( tests[i].doTest );
                                                        END();
                                                    }
                                                    for (var i = 0; i < 4; i++) {
                                                        var tableCol = $w.getColumn( i );
                                                        tableCol.pack(); // compactize all columns
                                                        var width = (i == 0) ? 30 : (i == 1) ? RULETABLE_WIDTH - 120 : 100;
                                                        tableCol.setWidth( width );
                                                    }

                                                    $w.addListener( SWT.Selection, function( event ) {
                                                        var i = w["tableRules"].indexOf( event.item );
                                                        if (event.detail == SWT.CHECK) {
                                                            tests[i].doTest = event.item.getChecked();
                                                        } else {
                                                            highlightTableRow( i );
                                                        }
                                                    } );

                                                    $w.getColumn( 2 ).addListener(SWT.Selection, function( event ) {
                                                        var cur = w["tableRules"].getSelectionIndex();
                                                        var numTested = 0;
                                                        for (var i = cur; (numTested < tests.length); numTested++) {
                                                            if (++i >= tests.length) {
                                                                i = 0;
                                                            }
                                                            if (tests[i].status == ITest.TEST_FAIL ||
                                                                tests[i].status == ITest.TEST_RUNERROR ) {
                                                                w["tableRules"].select( i );
                                                                if (i < cur) {
                                                                    if (i >= NUMBER_OF_VISIBLE_TABLE_ROWS - 1) {
                                                                        w["tableRules"].setTopIndex( i - 2 );
                                                                    } else {
                                                                        w["tableRules"].setTopIndex( 0 );
                                                                    }
                                                                    cur = i;
                                                                } else {
                                                                    if (i - w["tableRules"].getTopIndex() >= NUMBER_OF_VISIBLE_TABLE_ROWS) {
                                                                        w["tableRules"].setTopIndex( i - (NUMBER_OF_VISIBLE_TABLE_ROWS - 1) );
                                                                    }
                                                                }
                                                                highlightTableRow( i );
                                                                break;
                                                            }
                                                        }
                                                   } );

                                                END();


                                            END();

                                            WID( widgets.Composite( $w, SWT.NONE ) );
                                                var gl = new layout.GridLayout( 2, true);
                                                gl.marginWidth = 0;
                                                gl.horizontalSpacing = 10;
                                                gl.verticalSpacing = 2;
                                                $w.setLayout( gl );
                                                $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );

       w["lblDescription"] =                    WID( widgets.Label( $w, SWT.NONE) );
                                                    $w.setText( "Description" );
                                                END()
       w["lblStatusDetails"] =                  WID( widgets.Label( $w, SWT.NONE) );
                                                    $w.setText( "Status Details" );
                                                END();

       w["txtDescription"] =                    WID( widgets.Text( $w, SWT.BORDER | SWT.MULTI  | SWT.WRAP | SWT.V_SCROLL | SWT.READ_ONLY ) );
                                                    $w.setLayoutData( GD( RULETABLE_WIDTH/2 - (isWin ? 24 : 16), RULEDESC_HEIGHT ) );
                                                    //$w.setForeground( swt.graphics.Color( null, 0, 0, 214 ) );
                                                    $w.setBackground( swt.graphics.Color( null, 255, 255, 255 ) );
                                                    //$w.setFont( swt.graphics.Font( display, FIXED_WIDTH_FONT_NAME, FIXED_WIDTH_FONT_SIZE, SWT.NONE ) );
                                                END();

       w["txtStatusDetails"] =                  WID( widgets.Text( $w, SWT.BORDER | SWT.MULTI  | SWT.WRAP | SWT.V_SCROLL | SWT.READ_ONLY ) );
                                                    $w.setLayoutData( GD( RULETABLE_WIDTH/2 - (isWin ? 24 : 16), RULEDESC_HEIGHT ) );
                                                    //$w.setForeground( swt.graphics.Color( null, 0, 0, 214 ) );
                                                    $w.setBackground( swt.graphics.Color( null, 255, 255, 255 ) );
                                                    //$w.setFont( swt.graphics.Font( display, FIXED_WIDTH_FONT_NAME, FIXED_WIDTH_FONT_SIZE, SWT.NONE ) );
                                                END();

                                            END();

                                            LBL( "Test Execution Log                    " );
    w["txtExecutionLog"] =                  WID( widgets.Text( $w, SWT.BORDER | SWT.MULTI  | 1 * SWT.H_SCROLL | SWT.V_SCROLL | SWT.READ_ONLY ) );
                                                $w.setLayoutData( GD( RULETABLE_WIDTH, REPORTLOG_HEIGHT ) );
                                                $w.setForeground( swt.graphics.Color( null, 192, 192, 192 ) );
                                                $w.setBackground( swt.graphics.Color( null, 16, 16, 16 ) );
                                                //$w.setBackground( swt.graphics.Color( null, 64, 64, 64 ) );
                                                // $w.setForeground( swt.graphics.Color( null, 255, 255, 214 ) );
                                                // $w.setBackground( swt.graphics.Color( null, 230, 230, 230 ) );
                                                // $w.setBackground( shell.getBackground() );
                                                $w.setFont( swt.graphics.Font( display, FIXED_WIDTH_FONT_NAME, FIXED_WIDTH_FONT_SIZE, SWT.NONE ) );
                                                // $w.setText( "extracting all symbols...\n  running> nm6x video_copy.x64\n    _T_ _video_copy\n" );
                                            END();

                                        END(); // Rule Group

                                        // composite with Run/Cancel buttons
                                        WID( widgets.Composite( $w, SWT.NONE ) );
                                            var gl = new layout.GridLayout( 5, false );
                                            gl.marginWidth = 0;
                                            gl.horizontalSpacing = gl.verticalSpacing = 10;
                                            $w.setLayout( gl );
                                            $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );

                                            WID( widgets.Composite( $w, SWT.NONE ) );
                                                var gl = new layout.GridLayout( 2, false );
                                                gl.marginWidth = 0;
                                                gl.horizontalSpacing = gl.verticalSpacing = 0;
                                                $w.setLayout( gl );
                                                $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );

                                                LBL( "&Detail Level:" );

        w["sclDetailLevel"] =                   WID( widgets.Scale( $w, SWT.NONE ) );
                                                    $w.setMaximum( 2 );
                                                    $w.setPageIncrement( 1 );
                                                    $w.setLayoutData( GD( 80, SWT.DEFAULT ) );
                                                END();

                                            END();

                                            WID( widgets.Composite( $w, SWT.NONE ) );
                                                var gl = new layout.GridLayout( 1, false );
                                                gl.marginWidth = 0;
                                                gl.horizontalSpacing = gl.verticalSpacing = 6;
                                                $w.setLayout( gl );
                                                $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );
    w["chkRunSelectedOnly"] =                   WID( widgets.Button( $w, SWT.CHECK ) );
                                                    $w.setText( "Run Highlighted &Test Only" );
                                                END();
    w["chkRunTilFailure"] =                     WID( widgets.Button( $w, SWT.CHECK ) );
                                                    $w.setText( "Sto&p at First Failure" );
                                                END();
                                            END();
                                            WID( widgets.Composite( $w, SWT.NONE ) );
                                                var gl = new layout.GridLayout( 2, false );
                                                gl.marginWidth = 0;
                                                gl.horizontalSpacing = gl.verticalSpacing = 6;
                                                $w.setLayout( gl );
                                                $w.setLayoutData( layout.GridData( GD.FILL_BOTH ) );
                                                LBL( "Progress:" );
        w["barProgress"] =                      WID( widgets.ProgressBar( $w, SWT.HORIZONTAL ) );
                                                    $w.setLayoutData( GD( 110, SWT.DEFAULT ) );
                                                END();
                                                LBL( "Score:");
    w["txtScore"] =                             WID( widgets.Label( $w, SWT.BORDER ) );
                                                    $w.setLayoutData( GD( 110, SWT.DEFAULT ) );
                                                    $w.setText( "PASS: 0     FAIL: 0" );
                                                    $w.setForeground( swt.graphics.Color( null, 0, 0, 128 ) );
                                                END();
                                            END();

    w["btnRun"] =                           WID( widgets.Button( $w, SWT.PUSH ) );
                                                $w.setText( "      &Run      " );
                                            END();
    w["btnCancel"]  =                       WID( widgets.Button( $w, SWT.PUSH ) );
                                                $w.setText( "   &Cancel   " );
                                            END();
                                        END(); // composite with Start and Stop buttons

                                    END();
                                    END();

    w["menuBar"] =              WID( widgets.Menu( $w, SWT.BAR ) );
                                            shell.setMenuBar( $w );

        w["mnuFile"] =                  WID( widgets.MenuItem( $w, SWT.CASCADE ) );
                                                $w.setText( "&File" );
                                            END();
        w["mnuHelp"] =                  WID( widgets.MenuItem( $w, SWT.CASCADE ) );
                                                $w.setText( "&Help" );
                                            END();
                                        END();

                                        WID( widgets.Menu( $w, SWT.DROP_DOWN ) );
                                            w["mnuFile"].setMenu( $w );

        w["mnuOpenProject"] =           WID( widgets.MenuItem( $w, SWT.PUSH ) );
                                        $w.setText( "&Open Project\tCtrl+O" );
                                        $w.setAccelerator (SWT.MOD1 + 79 /* 'O' */ );
                                    END();
                                    WID( widgets.MenuItem( $w, SWT.SEPARATOR ) );
                                    END();
        w["mnuSaveProject"] =           WID( widgets.MenuItem( $w, SWT.PUSH ) );
                                        $w.setText( "&Save Project  (unnamed)" );
                                    END();
        w["mnuSaveProjectAs"] =         WID( widgets.MenuItem( $w, SWT.PUSH ) );
                                        $w.setText( "Save Project &As" );
                                    END();
                                    WID( widgets.MenuItem( $w, SWT.SEPARATOR ) );
                                    END();
                                            WID( widgets.MenuItem( $w, SWT.PUSH ) );
                                        $w.setText( "E&xit" );
                                        $w.addListener (SWT.Selection, function( event ) {
                                            optionallyQuit();
                                        });
                                    END();
                                END();

                                        WID( widgets.Menu( $w, SWT.DROP_DOWN ) );
                                            w["mnuHelp"].setMenu( $w );
        w["mnuInstructions"] =              WID( widgets.MenuItem( $w, SWT.PUSH ) );
                                            $w.setText( "&Instructions\tF1" );
                                            $w.setAccelerator (SWT.F1);
                                            $w.addListener (SWT.Selection, function( instructionListener ) {
                                                var ishell = new widgets.Shell(shell, swt.SWT.DIALOG_TRIM |
                                                                                   swt.SWT.RESIZE |
                                                                                   swt.SWT.APPLICATION_MODAL);
/*
                                                if (shellLocation!=null) {
                                                    ishell.setLocation(shellLocation);
                                                }
                                                ishell.setImage(image);
*/
                                                ishell.setSize( 600, 480 );
                                                ishell.setText( "Instructions" );

                                                var grid = new layout.GridLayout( 1, false );
                                                ishell.setLayout(grid);

                                                var comp = new widgets.Composite(ishell, SWT.NONE);
                                                comp.setLayout(new layout.GridLayout());

                                                var text = new widgets.Text( comp, SWT.WRAP | SWT.BORDER |
                                                    SWT.READ_ONLY | SWT.MULTI | SWT.V_SCROLL );
                                                text.setText( instructions.TEXT );
                                                text.setLayoutData( new layout.GridData( 550, 400 ) );

                                                var okBtn = new widgets.Button(comp, SWT.PUSH);
                                                okBtn.setText("    OK    ");

                                                okBtn.addListener( SWT.Selection, function (okEvent) {
                                                    ishell.dispose();
                                                } );
                                                ishell.open();
                                            } );
                                        END();

                                        WID( widgets.MenuItem( $w, SWT.PUSH ) );
                                        $w.setText( "&About" );
                                        $w.addListener (SWT.Selection, function( event ) {
                                            showMessage( "QualiTI\n\n(" + appVersion + ")" );
                                        });

                                    END();
                                END();

    function standardizeFontSize() {
        var l = new widgets.Label(shell, SWT.NO_FOCUS);
        var initialFont = l.getFont();
        l.dispose();
        var fontData = initialFont.getFontData();
        for (var i = 0; i < fontData.length; i++) {
            fontData[ i ].setHeight( STANDARD_FONT_SIZE );
        }
        var standardFont = new swt.graphics.Font( display, fontData );
        function setFont( widgets ) {
            for (var i = 0; i < widgets.length; i++) {
                if (widgets[i] == w["txtExecutionLog"]) {
                    continue;
                }
                try {
                    widgets[i].setFont( standardFont );
                } catch (e) {
                    print( "error: " + e);
                }
                if (widgets[i].getChildren != undefined) {
                    setFont( widgets[i].getChildren() );
                }
            }
        }
        setFont( w["cmpAll"].getChildren() );
    }

    standardizeFontSize();

    // some default values
    w["tableRules"].select( 0 );
    highlightTableRow( 0 );
    w["sclDetailLevel"].setSelection( 2 );
    w["lblDescription"].setText( "Description                                           " ); // leave room for extra info
    w["lblStatusDetails"].setText( "Status Details                                           " ); // leave room for extra info
    // w["btnCancel"].setEnabled( false );


}


var lastHilitRow = -1;
var hilitFont = null;
var nonHilitFont = null;

function highlightTableRow( rowNum )
{
    var w = myWidgets;
    var ti = w["tableRules"].getItem( rowNum );
    if (hilitFont == null) {
        nonhilitFont = ti.getFont();
        var fontData = nonhilitFont.getFontData();
            for (var i = 0; i < fontData.length; i++) {
                fontData[ i ].setStyle( SWT.BOLD );
        }
        hilitFont = new swt.graphics.Font( display, fontData );
        //hilitFont = swt.graphics.Font( display, FIXED_WIDTH_FONT_NAME, FIXED_WIDTH_FONT_SIZE, SWT.BOLD );
        //nonhilitFont = swt.graphics.Font( display, FIXED_WIDTH_FONT_NAME, FIXED_WIDTH_FONT_SIZE, SWT.NONE );
    }
    if (lastHilitRow > -1) {
        w["tableRules"].getItem( lastHilitRow ).setFont( nonhilitFont );
    }
    lastHilitRow = rowNum;
    ti.setFont( hilitFont );
    w["txtDescription"  ].setText( tests[ rowNum ].description );
    w["txtStatusDetails"].setText( tests[ rowNum ].statusDetails );
    w["txtStatusDetails"].setForeground(
        (tests[ rowNum ].status == ITest.TEST_FAIL || tests[ rowNum ].status == ITest.TEST_RUNERROR ) ? swt.graphics.Color( null, 255, 0, 0 ) :
        (tests[ rowNum ].status == ITest.TEST_PASS) ? swt.graphics.Color( null,   0, 160, 0 ) : swt.graphics.Color( null,   0, 0, 0 ) );
    w["txtExecutionLog" ].setText( tests[ rowNum ].log );


    var failCount = 0;
    var i = -1;
    if (numFailedTests > 0) {
        for (i = 0; i < tests.length; i++) {
            if (tests[i].status == ITest.TEST_FAIL ||
                tests[i].status == ITest.TEST_RUNERROR ) {
                ++failCount;
                if (i == rowNum) {
                    w["lblStatusDetails"].setText( "Status Details (failure " + failCount + " of " + numFailedTests + ")" );
                     break;
                 }
             }
         }
     }
     if (i != rowNum) {
        w["lblStatusDetails"].setText( "Status Details" );
     }
     // w["lblDescription"].setText( "Description (\"" + tests[ rowNum ].id + "\")" );
}


function showTestStatusInTable( tableItem, index, test )
{
    var text, color;
    switch (test.status) {
        case ITest.TEST_NOTRUN:   text = "not tested"; color = [0,0,0]; break;
        case ITest.TEST_FAIL:     text = "FAIL";       color = [255,0,0]; break;
        case ITest.TEST_PASS:     text = "PASS";       color = [0,160,0]; break;
        case ITest.TEST_NOTAPPLY: text = "N/A";        color = [80,80,80]; break;
        case ITest.TEST_RUNERROR: text = "run error";  color = [192,0,128]; break;
        case ITest.TEST_RUNNING:  text = "RUNNING..."; color = [0,0,214]; break;
        default:                  text = "INTERNAL ERROR";
    }
    if (test.isPerformanceTest &&
        (test.status == ITest.TEST_FAIL ||
         test.status == ITest.TEST_PASS ||
         test.status == ITest.TEST_NOTAPPLY ||
         test.status == ITest.TEST_RUNNING
         )) {
        text += " (perf)";
    }

    tableItem.setText( index, text );
    tableItem.setForeground( index, swt.graphics.Color( null, color[0], color[1], color[2] ) );
}

function readAlgoParamsFromGui(resolveBase)
{
    var w = myWidgets;

    var baseDir = resolveBase ? getGuiBaseDir() :
                  String(w["txtBaseDir"].getText());
    var algoParams = {
        moduleName:    w["txtModuleName"   ].getText() + "",
        vendor:        w["txtVendor"       ].getText() + "",
        interfaceName: w["txtInterfaceName"].getText() + "",
//        architecture:  w["cmbArchitecture" ].getText() + "",
        baseDir:       baseDir,
        library:       w["txtLibrary"      ].getText() + "",
        headers:       []
    };
    for (var j = 0; j < w["lstHeaders"].getItemCount(); j++) {
        algoParams.headers[j] = w["lstHeaders"].getItems()[j] + "";
    }

    return algoParams;
}

function storeAlgoParamsToGui( algoParams )
{
    var w = myWidgets;
    w["txtModuleName"   ].setText( algoParams.moduleName );
    w["txtVendor"       ].setText( algoParams.vendor );
    w["txtInterfaceName"].setText( algoParams.interfaceName );
    w["cmbArchitecture" ].setText( algoParams.architecture );
    w["txtBaseDir"      ].setText( algoParams.baseDir );
    w["txtLibrary"      ].setText( algoParams.library );
    w["lstHeaders"      ].removeAll();
    for (var i = algoParams.headers.length - 1; i >= 0; i--) {
        w["lstHeaders"].add( algoParams.headers[i] );
    }
}

function runOneTest( test, algoParams, testSettings, testDetailLevel, printLogFxn )
{
    var testResult = test.mod.run( test.id, algoParams, testSettings, testDetailLevel, printLogFxn );
    test.status        = testResult.status;
    test.statusDetails = testResult.statusDetails;
    if (test.status == ITest.TEST_RUNERROR) {
        printLogFxn( "Error: Command execution failed.\n"  );
        // analyze runResult's stdout, maybe something useful can be said
        if (testResult.runResult.stderr.match( ": not found" ) || testResult.runResult.stderr.match( ": No such file or directory" )) {
            test.statusDetails += "Test command execution failed -- most likely cgtools and/or utility executables could not be found. " +
                                  "Please verify that the tools paths are correct.";
        } else {
            test.statusDetails += "An unknown command line execution error occured. Please " +
                                  "check the execution log and try to repeat the commands in the " +
                                  "shell to see what the problem could be. Most likely the Settings " +
                                  "are somehow wrong.";
        }
    }
    return testResult;
}


function validateAlgoParams()
{
/*
    if (algoParams.moduleName.toUpperCase() != algoParams.moduleName) {
        print("Error: module name must be all uppercase.");
        return false;
    }
    if (algoParams.vendor.toUpperCase() != algoParams.vendor) {
        print("Error: vendor name must be all uppercase.");
        return false;
    }
    if (algoParams.interfaceName.toUpperCase() != algoParams.interfaceName) {
        print("Error: interface name must be all uppercase.");
        return false;
    }
*/
    if (!java.io.File(algoParams.baseDir).exists()) {
        print("Error: Base Directory '" + algoParams.baseDir + "' does not exist.");
        return false;
    }
    var libFile = algoParams.library;
    if (libFile[0] == "/" || libFile[1] == ":") {
    }
    else {
        libFile = algoParams.baseDir + pathSeparator + libFile;
    }
    if (!java.io.File(libFile).exists()) {
        print("Error: Library '" + libFile + "' does not exist.");
        return false;
    }
    return true;
}

function validateGuiAlgoParams()
{
    var w = myWidgets;
    if ((w["txtModuleName"].getText() + "").toUpperCase() != w["txtModuleName"].getText()) {
        showMessage( "Error: module name must be all uppercase." );
        return false;
    }
    if ((w["txtVendor"].getText() + "").toUpperCase() != w["txtVendor"].getText()) {
        showMessage( "Error: vendor name must be all uppercase." );
        return false;
    }
    if ((w["txtInterfaceName"].getText() + "").toUpperCase() != w["txtInterfaceName"].getText()) {
        showMessage( "Error: interface name must be all uppercase." );
        return false;
    }
    var baseDir = getGuiBaseDir();
    if (!java.io.File( baseDir ).exists()) {
        showMessage( "Error: Base Directory '" + baseDir + "' does not exist." );
        return false;
    }
    var libFile = w["txtLibrary"].getText() + "";
    if (libFile[0] == "/" || libFile[1] == ":") {
    } else {
        libFile = baseDir + pathSeparator + libFile;
    }
    if (!java.io.File( libFile ).exists()) {
        showMessage( "Error: Library '" + libFile + "' does not exist." );
        return false;
    }
    // won't bother to test for header files, tests will fail in a
    // comprehensible way if they are missing
    return true;
}

function isValidLibrary(algoPrams, testSettings, cbPrintLog, detailLevel)
{
    var cgtoolsDir = testSettings.cgtoolsDir + "/";

    // See if ofd6x output contains "ARCHIVE:" string
    var ofd_cmd = System.getCommandPath(cgtoolsDir + "bin/ofd6x");

    /* always call checkPath when passing a path to a command */
    var libPath = System.checkPath(algoParams.baseDir + "/" + algoParams.library);

    ofd_cmd += " --obj_display=none " + libPath;
    var runResult = System.runShellCommand(ofd_cmd, cbPrintLog, detailLevel);
    if (runResult.status != 0) {
    }
    var stdoutLines = runResult.stdout.split('\n');
    var foundArchive = false;
    for (var i = 0; i < stdoutLines.length; i++) {
        if (stdoutLines[i].match('ARCHIVE:')) {
            foundArchive = true;
            break;
        }
    }
    return (foundArchive);
}

function setEventListeners()
{
    var w = myWidgets;

    var testThreadRunning   = false;
    var cancelButtonPressed = false;

    w["btnRun"].addListener( SWT.Selection, function( event ) {

        var testSettings = {
            cgtoolsDir:   w["txtC64PcgtoolsDir"].getText() + "",
            cgxmlDir:     w["txtCgxmlDir"    ].getText() + ""
        };

        var testDetailLevel = w["sclDetailLevel"].getSelection();

        cgxmlLog = "";
        try {
            var cgxmlVers = getCgxmlVers(testSettings.cgxmlDir,
                            function (text) { cgxmlLog += text; });
            if (cgxmlVers < MIN_CGXML_VERS) {
                showMessage(CGXML_VERS_MSG);
                return;
            }
        }
        catch (e) {
            showMessage( e + " Could not determine cg_xml version" );
            return;
        }

        if (!validateGuiAlgoParams()) {
            return;
        }

        w["btnRun"].setEnabled( false );
        w["btnCancel"].setEnabled( true );
        w["cmpTableRules"].setEnabled( false );
        w["tableRules"].getColumn(2).setText( "Status" );
        w["btnCancel"].setFocus();

        var numberOfTestCurrentlyRunning;

        // clear table
        if (w["chkRunSelectedOnly"].getSelection() == false) {
            for (i = 0; i < tests.length; i++) {
                var test = tests[i];
                test.mod.reset( test.id );
                test.status = ITest.TEST_NOTRUN;
                test.statusDetails = "Test has not been run yet."; // fixme: repetition
                test.log = "";
                showTestStatusInTable( w["tableRules"].getItem(i), 2, test );
            }
            w["txtDescription"  ].setText( "" );
            w["txtStatusDetails"].setText( "" );
            w["txtExecutionLog" ].setText( "" );
        }
        else {
            var i = w["tableRules"].getSelectionIndex();
            if (i != -1) {
                var test = tests[i];
                test.mod.reset( test.id );
            }
        }

        cancelButtonPressed = false;

        var lastNl = false;
        var freshLogStart;
        var submittedUpdates = 0;
        var realizedUpdates = 0;
        printLogFxn = function( text ) {
            if (lastNl) {
                text = "\n  " + text;
                lastNl = false;
            }
//            if (text.substr( 0, text[ text.length - 1] == "\n" ) {
//                text = text.substr( 0, text.length - 1 );
//                lastNl = true;
//            }
            tests[ numberOfTestCurrentlyRunning ].log += text;
            if (freshLogStart) {
                freshLogStart = false;
                text = String.fromCharCode( 666 ) + text; // this means "CLS"
            }
            ++submittedUpdates;
            asyncDisplayUpdate( function() {
                if (text.charCodeAt(0,1) == 666 ) {
                    w["txtExecutionLog"].setText( text.substr( 1 ) );
                } else {
                    w["txtExecutionLog"].append( text );
                }
                ++realizedUpdates;
            } );
        };

        var firstFailedIndex = -1;
        var passCount = 0;
        var failCount = 0;
        var progressCount = 0;
        var totalCount = 0;
        for (i = 0; i < tests.length; i++) {
            if (tests[i].doTest) {
                ++totalCount;
            }
        }
        if (w["chkRunSelectedOnly"].getSelection()) {
            totalCount = 1;
        }
        w["barProgress"].setMaximum( totalCount );
        w["barProgress"].setSelection( 0 );
        w["txtScore"].setText( "PASS: 0     FAIL: 0" );

        algoParams = readAlgoParamsFromGui(true);
        libraryLog = "";
        try {
            if (!isValidLibrary(algoParams,
                                testSettings, 
                                function (text) { libraryLog += text; },                            
                                testDetailLevel)) {
                showMessage("Warning: '" + algoParams.baseDir + "/" + algoParams.library +
                            "' does not appear to be a valid library archive.");
            }
        }
        catch (e) {
            showMessage('Could not determine if library is valid ' + e);
        }

        architectureLog = "";
        try {
            algoParams.architecture = getArchitecture(algoParams,
                    testSettings,
                    function (text) { architectureLog += text; },
                    testDetailLevel);
            if (!algoParams.architecture .length) {
                showMessage("Could not determine architecure");
            }
        }
        catch (e) {
            showMessage( e + " Could not determine architecure" );
        }

        compilerLog = "";
        try {
            algoParams.compilerParams = Compiler.getCompilerInfo(algoParams ,
                    testSettings,
                    function (text) { compilerLog += text; },
                    testDetailLevel);
        }
        catch (e) {
            showMessage( e + " Could not determine compiler info" );
        }
        algoParams.compilerParams.log = compilerLog;

        for (i = 0; i < tests.length; i++) {

            if (w["chkRunSelectedOnly"].getSelection()) {
                i = w["tableRules"].getSelectionIndex();
                if (i == -1) {
                    // fixme: say nothing is selected.
                    break;
                }
            } else {
                w["tableRules"].setSelection( i );
                highlightTableRow( i );
            }

            var test = tests[i];

            if (test.doTest == false) {
                test.status        = ITest.TEST_NOTRUN;
                test.statusDetails = "Test has not been run."; // fixme: repetition
                continue;
            }

            test.status        = ITest.TEST_RUNNING;
            test.statusDetails = "Test running...";
            test.log           = "";

            // fixme: make this better
            showTestStatusInTable( w["tableRules"].getItem(i), 2, test );
            w["txtDescription"].setText( test.description );
            w["txtStatusDetails"].setText( test.statusDetails );
            // w["txtExecutionLog"].setText( "" );

            numberOfTestCurrentlyRunning = i;

            var thread = new java.lang.Thread(function() {
                freshLogStart = true;
                submittedUpdates = 0;
                realizedUpdates  = 0;
                runOneTest( test, algoParams, testSettings, testDetailLevel, printLogFxn );
                while (realizedUpdates < submittedUpdates) {
                    java.lang.Thread['yield']();
                }
                testThreadRunning  = false;
                display.wake();
            });
            testThreadRunning = true;
            thread.start();

            while (testThreadRunning) {
                if (!display.readAndDispatch()) {
                    display.sleep();
                }
            }
            thread.join();

            showTestStatusInTable( w["tableRules"].getItem(i), 2, test );
            w["txtDescription"].setText( test.description );
            w["txtStatusDetails"].setText( test.statusDetails );
            // fixme: repetition
            w["txtStatusDetails"].setForeground(
                (test.status == ITest.TEST_FAIL || test.status == ITest.TEST_RUNERROR ) ? swt.graphics.Color( null, 255, 0, 0 ) :
                (test.status == ITest.TEST_PASS) ? swt.graphics.Color( null,   0, 160, 0 ) : swt.graphics.Color( null,   0, 0, 0 ) );

            if ((test.status == ITest.TEST_FAIL ||
                test.status == ITest.TEST_RUNERROR)) {
                if (firstFailedIndex == -1) {
                    firstFailedIndex = i;
                }
                ++failCount;
            }
            if (test.status == ITest.TEST_PASS) {
                ++passCount;
            }
            ++progressCount;
            w["barProgress"].setSelection( progressCount );
            w["txtScore"].setText( "PASS: " + passCount + "     FAIL: " + failCount );

            if ((test.status == ITest.TEST_FAIL ||
                test.status == ITest.TEST_RUNERROR) &&
                w["chkRunTilFailure"].getSelection()) {
                break;
            }
            if (w["chkRunSelectedOnly"].getSelection()) {
                break;
            }
            numFailedTests = failCount;
            if (cancelButtonPressed) {
                break;
            }
        }
        if (firstFailedIndex > -1) {
            w["tableRules"].select( firstFailedIndex );
            if (firstFailedIndex >= NUMBER_OF_VISIBLE_TABLE_ROWS - 1) {
                w["tableRules"].setTopIndex( firstFailedIndex - 2 );
            } else {
                w["tableRules"].setTopIndex( 0 );
            }
            highlightTableRow( firstFailedIndex );
        }
        w["btnRun"].setEnabled( true );
        // w["btnCancel"].setEnabled( false );
        w["cmpTableRules"].setEnabled( true );
        if (numFailedTests > 0) {
            w["tableRules"].getColumn(2).setText( "Status    [...]" );
        }
        w["tableRules"].setFocus();
        if ((w["radioNoReport"].getSelection() == false) && (!w["chkRunSelectedOnly"].getSelection())) {
            var d = new Date();
            var timeStamp = "";
            if (w["chkEmbedTimeStampInReportName"].getSelection()) {
                timeStamp = "--" + (d.toString()).substr( 4, 20 ).replace( / /g, "-" ).replace( ":", "h" ).replace( ":", "m") + "s";
            }
            var ext = algoParams.library.substr(algoParams.library.lastIndexOf('.') + 1);
            var modvend = "--" + algoParams.moduleName + "_" + algoParams.vendor + "_" + ext;
            var outFileName = "qualiti" + modvend + timeStamp + "--report.html";
            var outDir;
            if (w["radioReportInDir"].getSelection()) {
                outDir = w["txtReportDir"].getText();
            }
            else if (w["radioReportInBaseDir"].getSelection()) {
                outDir = algoParams.baseDir;
            }
            else {
                outDir = java.io.File( algoParams.baseDir + "/" + algoParams.library ).getParent();
            }
            try {
                generateHTMLReport( outDir + "/" + outFileName, algoParams, testSettings, w["chkDiffFriendlyReport"].getSelection() );
                lastGeneratedReport = outDir + "/" + outFileName;
            } catch (e) {
                showMessage( e +
                    "You can turn off automatic report generation in the 'Reports' tab of the " +
                    "'Settings' section."
                );
            }
        }
    } );


    w["btnCancel"].addListener( SWT.Selection, function( event ) {
        if (w["btnRun"].enabled) {
            optionallyQuit();
        } else {
            cancelButtonPressed = true;
        }
    } );

    // set an event listener to exit the app on "escape" key
    display.addFilter( SWT.KeyDown, function( event ) {
        if (event.keyCode == 27) {
            optionallyQuit();
        }
    } );

    // handle app exiting -- write the values of select widgets to an INI file
    shell.addDisposeListener( function( event ) {

        // called here when the shell (window) is about to be closed; we use
        // the opportunity to read some widgets and save them to a file
        writeIniFile();
        writeToolsIniFile();
    } );

    function saveProject() {
        var algoParams = readAlgoParamsFromGui(false);

        if (algoParams.baseDir == java.io.File( projectFile ).getParent()) {
            algoParams.baseDir = ".";
        }

        var f = new java.io.FileWriter( new java.io.File( projectFile ) );
        f.write( "algoParams = {\n" );
        for (var i in algoParams) {
            var o = algoParams[i];
            f.write( '  ' + i + ': ' );
            if (o.constructor.toString().indexOf("Array") == -1) {
                f.write( '"' + o.replace( /\\/g, "\\\\" ) + '",\n' );
            } else {
                f.write ( '[\n' );
                for (var j = 0; j < o.length; j++) {
                    f.write( '    "' + o[j].replace( /\\/g, "\\\\" ) + '",\n' );
                }
                f.write ( '  ],\n' );
            }
        }
        f.write( '}\n' );
        f.close();
    }

    function saveProjectAs() {
        var dialog = new widgets.FileDialog( shell, SWT.SAVE );
        dialog.setFilterPath(getGuiBaseDir());
        dialog.setFilterExtensions( [ "*.qti" ] );
        var fileName = dialog.open();
        if (fileName == null) {
            return false;
        }
        if (java.io.File( fileName ).exists()) {
            var mbox = widgets.MessageBox( shell, SWT.YES | SWT.NO );
            mbox.setText( "Save project" );
            mbox.setMessage( "Project file \"" + fileName + "\" already exists. Do you want to replace it?" );
            var res = mbox.open();
            if (res == SWT.NO) {
                return false;
            }
        }
        projectFile = fileName;
        saveProject();
        return true;
    }

    function setNewTitle() {
        var file = java.io.File( projectFile ).getCanonicalPath();
        w["mnuSaveProject"].setText( "&Save Project  (\"" + file + "\")" );
        shell.setText( appShellTitle + '   [' + file + ']' );
    }

        w["mnuOpenProject"].addListener( SWT.Selection, function( event ) {
        if (openProject()) {
            setNewTitle();
            }
    });
        w["mnuSaveProject"].addListener( SWT.Selection, function( event ) {
        if (projectFile == undefined) {
                if (saveProjectAs()) {
                    setNewTitle();
            }
            } else {
            saveProject();
            }
    });
        w["mnuSaveProjectAs"].addListener( SWT.Selection, function( event ) {
        if (saveProjectAs()) {
            setNewTitle();
            }
    });

}

function openProject(fileName)
{
    var w = myWidgets;
    if (!fileName) {
        var dialog = new widgets.FileDialog( shell );
        dialog.setFilterPath(getGuiBaseDir());
        dialog.setFilterExtensions( [ "*.qti" ] );
        fileName = dialog.open();
        if (fileName == null) {
            return false;
        }
    }
    try {
        load( fileName );
    } catch( e ) {
        showMessage( "Error loading project '" + fileName + '": ' + e );
        return false;
    }
    projectFile = fileName;
    storeAlgoParamsToGui(algoParams);
    return true;
}

// ======== asyncDisplayUpdate ========
//
// Updates the display widgets when run from another thread. Any exception
// that may happen would happen at the close of the program, so we simply
// catch them and ignore them.
// Input: function to run that updates widgets
//
function asyncDisplayUpdate( asyncDisplayUpdateFxn )
{
    if (!display.isDisposed()) {
        try {
            display.asyncExec(
                new java.lang.Runnable() {
                    run: function() {
                        try {
                            asyncDisplayUpdateFxn();
                        } catch (e) {}
                    }
                }
            );
        } catch (e) {}
    }
}


// ======== showMessage ========
//
// Show text in a message box
// Input: text to show
//
function showMessage( msg )
{
    var mbox = widgets.MessageBox( shell, SWT.ICON_INFORMATION );
    mbox.setText( appTitle );
    mbox.setMessage( msg );
    mbox.open();
}

function optionallyQuit() {
    var mbox = widgets.MessageBox( shell, SWT.YES | SWT.NO );
    mbox.setText( appTitle );
    mbox.setMessage( "Are you sure you want to abandon QualiTI?" );
    var res = mbox.open();
    if (res == SWT.YES) {
        if (ecParent) {
            shell.dispose();
        }
        else {
        display.dispose();
        }
    }
}

// ======== writeToIniFile ========
//
// Write relevant textboxes contents into QualiTI.ini file, to be read the next
// time at startup. Format it as script statements so that load is simple.
//
// (Instead of writing data that we would read later, as non-script applications
// do, we write a script /function/ that, when directly executed, sets the
// textboxes' contents properly. That is why readFromInFile() is so simple.
//
function writeIniFile()
{
    var w = myWidgets;

    try {
        function dumpText( textName ) {
            f.write( 'w["' + textName + '"].setText("' + (w[textName].getText() + "").replace( /\\/g, "\\\\" ) + '");\n' );
        }
        function dumpCombo( comboName ) {
            var itemCount = w[ comboName ].getItemCount();
            var i;
            for (i = itemCount - 1; i >=0 ; i--) {
                f.write( 'w["' + comboName + '"].add("' +
                         (w[comboName].getItem( i ) + "").replace( /\\/g, "\\\\" ) +
                         '");\n' );
            }
        }
        function dumpSelection( selName ) {
            f.write( 'w["' + selName + '"].setSelection( ' + w[ selName ].getSelection() + ' );\n' );
        }


        var f = new java.io.FileWriter( new java.io.File( iniFilesDir + ".qualiTI.ini" ) );
        f.write( 'function iniRun( w ) {\n' );

        dumpText( "txtModuleName" );
        dumpText( "txtVendor" );
        dumpText( "txtInterfaceName" );
        f.write( 'w["cmbArchitecture"].select( ' + w["cmbArchitecture"].getSelectionIndex() + ' );\n' );

        dumpText( "txtBaseDir" );
        dumpText( "txtLibrary" );
        dumpCombo( "lstHeaders" );

        dumpText("txtC64PcgtoolsDir");
        dumpText( "txtCgxmlDir" );

        dumpSelection( "radioReportInBaseDir" );
        dumpSelection( "radioReportInAlgLibDir" );
        dumpSelection( "radioReportInDir" );
        dumpText( "txtReportDir" );
        dumpSelection( "radioNoReport" );
        dumpSelection( "chkEmbedTimeStampInReportName" );
        dumpSelection( "chkDiffFriendlyReport" );

        dumpSelection( "sclDetailLevel" );


        f.write( '}\n' );
        f.close();
    }
    catch (e) {
        print( "Warning: storing settings to the ini file failed. Reason: " + e);
    }
}

// ======== writeToolsIniFile ========
//
//
function writeToolsIniFile()
{
    var w = myWidgets;
    try {
        f = new java.io.FileWriter( new java.io.File(iniFilesDir + ".qualiTI-tools.ini"));
        f.write('var c64PcgtoolsDir = "' + (w["txtC64PcgtoolsDir"].getText() + "").replace( /\\/g, "\\\\") + '";\n');
        f.write('var cgxmlDir       = "' + (w["txtCgxmlDir"].getText()          + "").replace( /\\/g, "\\\\") + '";\n');
        f.close();

    }
    catch (e) {
        print( "Warning: storing settings to the tools ini file failed. Reason: " + e);
    }
}

// ======== readIniFile ========
//
// Read ini file, if there is one, to set default values for some widgets
//
function readIniFile()
{
    try {
        var w = myWidgets;
        if (new java.io.File( iniFilesDir + ".qualiTI.ini" ).exists()) {
            load( iniFilesDir + ".qualiTI.ini" );
            iniRun(w);
        }
        else {
            // fill in the fields with some educational default values
            w["txtModuleName"].setText("FIR");
            w["txtVendor"].setText("TI");
            w["txtInterfaceName"].setText("IFIR");

            w["txtBaseDir"].setText("<USER_EDIT_THIS_PATH>");
            w["txtLibrary"].setText("<USER_EDIT_THIS_LIBRARY>");
        }
    }
    catch (e) {
        print("Warning: Reading qualiTI.ini file failed. Reason: " + e);
    }
}


// ======== readToolsIniFile ========
//
//
function readToolsIniFile()
{
    try {
        var w = myWidgets;
        if (new java.io.File(iniFilesDir + ".qualiTI-tools.ini").exists()) {
            load(iniFilesDir + ".qualiTI-tools.ini");
            w["txtCgxmlDir"].setText(cgxmlDir);
        }
        else {
            w["txtCgxmlDir"].setText("C:\\USER_EDIT_THIS_PATH\\cg_xml");
        }
        if (isWin) {
            w["txtC64PcgtoolsDir"].setText(thisPkgDir.replace(/\//g, "\\" ) + "cgtools");
        }
        else {
            w["txtC64PcgtoolsDir"].setText(thisPkgDir + "cgtools");
        }
    }
    catch (e) {
        print("Warning: Reading qualiTI-tools.ini file failed. Reason: " + e);
    }
}

function runTestsOffLine(algProjectFile, outputInLibDir, outputDir,
                         embedTimeStampInReportName, testDetailLevel,
                         toolsIniFile, verbose, quiet, diffFriendly)
{

    try {
        if (!quiet) {
            print( "Opening algorithm project " + algProjectFile );
        }
        if (!java.io.File( algProjectFile ).exists()) {
            throw "File does not exist";
        }
        load(algProjectFile);
        if (algoParams.baseDir == ".") {
            algoParams.baseDir = java.io.File( algProjectFile ).getParent();
        }
        else if (!java.io.File(algoParams.baseDir).isAbsolute()) {
            var baseDir = java.io.File(algProjectFile).getAbsoluteFile().getParent() +
                          pathSeparator + algoParams.baseDir;
            algoParams.baseDir = java.io.File(baseDir).getCanonicalPath();
        }
    }
    catch(e) {
        print("Error opening project file '" + algProjectFile + '": ' + e);
        return -1;
    }

    var testSettings = {};

    try {
        if (toolsIniFile == null) {
            toolsIniFile = iniFilesDir + ".qualiTI-tools.ini";
        }
        if (verbose) {
            print("Opening tool paths file " + toolsIniFile);
        }
        if (isWin) {
            testSettings.cgtoolsDir = thisPkgDir.replace(/\//g, "\\" ) + "cgtools";
        }
        else {
            testSettings.cgtoolsDir = thisPkgDir + "cgtools";
        }
        load(toolsIniFile);
        testSettings.cgxmlDir = cgxmlDir;
    }
    catch(e) {
        print("Error loading tools ini file'" + toolsIniFile + "': " + e);
        return -1;
    }

    if (verbose) {
        print("Checking cg_xml version");
    }

    cgxmlLog = "";
    try {
        var cgxmlVers = getCgxmlVers(testSettings.cgxmlDir,
                        function (text) { cgxmlLog += text; });
        if (cgxmlVers < MIN_CGXML_VERS) {
            print(CGXML_VERS_MSG);
            return -1;
        }
    }
    catch (e) {
        print(e + " Could not determine cg_xml version");
        return -1;
    }

    if (!validateAlgoParams()) {
        return -1;
    }
    if (verbose) {
        print("Determining architecture");
    }

    libraryLog = "";
    try {
        if (!isValidLibrary(algoParams,
                            testSettings, 
                            function (text) { libraryLog += text; },                            
                            testDetailLevel)) {
            print("Warning: '" + algoParams.baseDir + "/" + algoParams.library +
                  "' does not appear to be a valid library archive.");
        }
    }
    catch (e) {
        print('Could not determine if library is valid ' + e);
    }

    architectureLog = "";
    try {
        algoParams.architecture = getArchitecture(algoParams,
                testSettings,
                function (text) { architectureLog += text; },
                testDetailLevel);
        if (!algoParams.architecture.length) {
            print("Could not determine architecure");
        }
    }
    catch (e) {
        print('Could not determine architecture ' + e);
    }
    compilerLog = "";
    if (verbose) {
        print("Gathering compiler info");
    }
    try {
        algoParams.compilerParams = Compiler.getCompilerInfo(algoParams,
                 testSettings,
                 function (text) { compilerLog += text; },
                 testDetailLevel);
    }
    catch (e) {
        print(e);
    }
    algoParams.compilerParams.log = compilerLog;

    var firstFailedIndex = -1;
    var passCount = 0;
    var failCount = 0;
    var progressCount = 0;
    var totalCount = tests.length;

    if (!quiet) {
        print( "Running " + totalCount + " tests" );
    }

    for (i = 0; i < tests.length; i++) {

        var test = tests[i];
        test.log = "";

        if (verbose) {
            java.lang.System.out.print( "Running test " + test.id + "...");
        }

        runOneTest( test, algoParams, testSettings, testDetailLevel,
            function( text ) {
                test.log += text;
            } );

        if ((test.status == ITest.TEST_FAIL ||
            test.status == ITest.TEST_RUNERROR)) {
            if (firstFailedIndex == -1) {
                firstFailedIndex = i;
            }
            ++failCount;
            if (verbose) {
                print( " FAIL");
            }
        }
        if (test.status == ITest.TEST_PASS) {
            ++passCount;
            if (verbose) {
                print( " PASS");
            }
        }
        ++progressCount;
    }
    var ext = algoParams.library.substr(algoParams.library.lastIndexOf('.') + 1);
    if (!quiet) {
        print( "Final score for algorithm " + algoParams.moduleName + "_" +
               algoParams.vendor + "(" + ext + "): " +
               "PASS: " + passCount + ", FAIL: " + failCount );
    }

    var d = new Date();
    var timeStamp = "";
    if (embedTimeStampInReportName) {
        timeStamp = "--" + (d.toString()).substr( 4, 20 ).replace( / /g, "-" ).replace( ":", "h" ).replace( ":", "m") + "s";
    }
    var modvend = "--" + algoParams.moduleName + "_" + algoParams.vendor + "_" + ext;
    var outFileName = "qualiti" + modvend + timeStamp + "--report.html";

    if (outputDir == null) {
        if (outputInLibDir) {
            outputDir = java.io.File(algoParams.baseDir + "/"
                                     + algoParams.library).getParent();
        }
        else {
            outputDir = algoParams.baseDir;
        }
    }

    if (!quiet) {
        print("Generating report in " + outputDir + "");
    }
    try {
        generateHTMLReport(outputDir + "/" + outFileName, algoParams, testSettings, diffFriendly);
    }
    catch (e) {
        print(e);
    }
}

function readUserIniFile(userIniFile)
{
    print("Loading user script " + userIniFile);
    try {
        load(userIniFile);
    }
    catch(e) {
        print("Error loading user script " + userIniFile + "\n"
              + "Details: " + e);
    }
}

/*
 *  ======== getArchitecture ========
 */
function getArchitecture(algoParams, testSettings, cbPrintLog, detailLevel)
{
    cbPrintLog( "Determining architecture.\n\n" );

    var cgtoolsDir = testSettings.cgtoolsDir + "/";
    var runResult;

    // get architecture by parsing 'Machine:' in ofd6x output
    var ofd_cmd = System.getCommandPath( cgtoolsDir + "bin/ofd6x" );

    /* always call checkPath when passing a path to a command */
    var libPath = System.checkPath(algoParams.baseDir + "/" + algoParams.library);

    ofd_cmd += " --obj_display=none,header " + libPath;
    runResult = System.runShellCommand(ofd_cmd, cbPrintLog, detailLevel);
    if (runResult.status != 0) {
        return ('');
    }
    var arch = '';
    for each (var line in runResult.stdout.split('\n')) {
        if (line.length) {
            if (line.match('Machine:')) {
                if (line.match('C6x')) {
                    arch = 'C6x';
                    break;
                }
                else if (line.match('ARM')) {
                    arch = 'ARM';
                    break;
                }
                else if (line.match('C55x')) {
                    arch = 'C55x';
                    break;
                }
                else if (line.match('C2000')) {
                    arch = 'C28x';
                    break;
                }
            }
        }
    }
    return (arch);
}

/*
 *  ======== getGuiBaseDir ========
 */
function getGuiBaseDir()
{
    var w = myWidgets;
    var baseDir = String(w["txtBaseDir"].getText());
    if (baseDir.length && !java.io.File(baseDir).isAbsolute()) {
        var projFile = java.io.File(projectFile);
        if (projFile.exists()) {
            absBase = java.io.File(projectFile).getAbsoluteFile().getParent();
        }
        else {
            absBase = '.';
        }
        if (baseDir == '.') {
            baseDir = String(java.io.File(absBase).getCanonicalPath());

        }
        else {
            baseDir = String(java.io.File(absBase + pathSeparator + baseDir).
                      getCanonicalPath());
        }
    }
    return (baseDir);
}

/*
 *  ======== createPartControl ========
 */
function createPartControl(parent)
{
    guiMain(null, parent);
}

/*
 *  ======== run ========
 *  Main function, executed from the command line. Parses the arguments
 *  using getopt() and calls the above. If any function raises an
 *  exception, prints the error message and the usage.
 */
function run(cmdr, args)
{

    if (this.userIniFile != null) {
        readUserIniFile( this.userIniFile );
    }
    getTests();

    if (this.help || args.length > 1) {
        cmdr.usage();
        return 1;
    }
    try {
        if (cmdr.tid) {
            var gui;
            /* for each module in this package ... */
            for each (var mod in this.$package.$modules) {
                var cap = mod.$capsule;
                if (cap && "createPartControl" in cap) {
                    gui = cap;
                    break;
                }
            }
            /* create an instance of IWorkbenchPart and send it */
            /* back to the server to call gui.createPartControl */
            var wbp = new Packages.org.eclipse.ui.IWorkbenchPart(gui);
            cmdr.socket.giveToClient(wbp);
            /* wait for gui to close */
            var val = cmdr.socket.takeFromClient();
            return;
        }
    }
    catch (e) {
        print (XDCVERS_MSG);
        return;
    }

    if (args.length == 0 || this.gui) {
        if (args.length) {
            guiMain(args[0]);
        }
        else {
            guiMain();
        }
        return;
    }

    var retval = runTestsOffLine(
        args[0],
        this.outputInLibDir,
        this.outputDir,
        this.embedTimeStampInReportName,
        this.testDetailLevel,
        this.toolsIniFile,
        this.verbose,
        this.quiet,
        this.diffFriendly
    );

    return retval;
}

/*
 *  ======== getCgxmlVers ========
 */
function getCgxmlVers(cgxmlDir, cbPrintLog)
{
    cbPrintLog("Checking cg_xml version.\n\n");

    var vers = 0;
    /* get cg_xml version by parsing 'Release Version n.nn.nn'
       in readme.txt */
    var inp = java.io.BufferedReader(java.io.FileReader(cgxmlDir + '/readme.txt'));
    while (line = String(inp.readLine())) {
        if (line.length) {
            if (line.match('Release Version ')) {
                vers = Number(line.substr(16, 4));
                break;
            }
        }
    }
    return (vers);
}

