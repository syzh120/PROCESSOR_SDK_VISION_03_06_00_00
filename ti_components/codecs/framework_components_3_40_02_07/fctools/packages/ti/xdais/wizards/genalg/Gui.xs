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
 * */

var csd = String(xdc.csd()).replace(/\\/g,"/");

var swt;
var browser;
var custom;
var graphics;
var layout;
var widgets;
var events;
var dnd;
var program;

var display;
var image;
var algEnv = null;

var xmlOps = xdc.loadCapsule("xmlOps.xs");
var wizard_constants = xdc.loadCapsule("wizard_constants.xs");
xmlOps.setWizardConstants(wizard_constants);
var fileModule = xdc.module('xdc.services.io.File');
var logic = xdc.loadCapsule("logic.xs");
var shared_gui = xdc.loadCapsule("shared_gui.xs");
xmlOps.setLogic(logic);
var os = String(java.lang.System.getProperty('os.name'));
var isWin = (os.match(/^Windows/i) != null);
var SHELL_WIDTH = isWin ? 575 : 680;
var SHELL_HEIGHT = isWin ? 527 : 600;
var XDCVERS_MSG = 'The version of xdctools is older than 3.16. Either restart '
+'GenAlg Wizard with xdctools 3.16 or higher, or modify the generated '
+'makefile to point at a newer version of xdctools.';

function initSWT() {
    swt = xdc.jre.org.eclipse.swt;
    browser = xdc.jre.org.eclipse.swt.browser;
    custom = xdc.jre.org.eclipse.swt.custom;
    graphics = xdc.jre.org.eclipse.swt.graphics;
    layout = xdc.jre.org.eclipse.swt.layout;
    widgets = xdc.jre.org.eclipse.swt.widgets;
    events = xdc.jre.org.eclipse.swt.events;
    dnd = xdc.jre.org.eclipse.swt.dnd;
    program = xdc.jre.org.eclipse.swt.program;
}

function setAlgEnv(ae)
{
    algEnv = ae;
}

function createPartControl(parent)
{
    main(algEnv, parent);
}

var buttons = {
    finishEnabled:    false,
    updated:          false
}

var pageFxns = [page0Fxn];
var numberOfPages = pageFxns.length;

var hoverTip = null;
var hoverLabel = null;

var filterExt = ['*.genalg', '*.*'];
var filterNames = ['Genalg Files (*.genalg)', 'All Files (*.*)'];

function init(algEnv, parent)
{
    if (parent) {
        display = parent.getDisplay();
    }
    else {
        display = new widgets.Display();
    }
    algEnv.display = display;
    image = new graphics.Image(display, csd + "/img/tray.JPG");
    ICO_ERROR = graphics.Image(display, csd + "/img/error_tsk.gif");
    ICO_WARNING = graphics.Image(display, csd + "/img/warning.gif");

    var shellLocation = graphics.Point(66,87);

    algEnv.shellLocation = shellLocation;
/*
    var shell = new widgets.Shell(display, swt.SWT.DIALOG_TRIM |
                                  swt.SWT.APPLICATION_MODAL);

    shell.setImage(image);
    shell.setSize(200, 100);
    shell.setText("Loading...");

    if (algEnv.shellLocation!=null) {
        shell.setLocation(algEnv.shellLocation);
    }

    var grid = new layout.GridLayout(1, false);
    shell.setLayout(grid);

    var comp = new widgets.Composite(shell, swt.SWT.NONE);
    comp.setLayout(new layout.GridLayout());

    var text = new widgets.Text(comp, swt.SWT.WRAP | swt.SWT.READ_ONLY);
    text.setText(wizard_constants.INIT_MESSAGE);
    text.setLayoutData(new layout.GridData(180, 50));

    var pb = new widgets.ProgressBar(comp, swt.SWT.HORIZONTAL);
    pb.setMinimum(0);
    pb.setMaximum(100);
    pb.setBounds(10, 10, 200, 20);
    shell.pack();
    shell.open();

    pb.setSelection(30);

    pb.setSelection(50);
    pb.setSelection(80);
    pb.setSelection(100);
    shell.dispose();
*/
}


function page0Fxn(comp)
{
    /* required user input:
       optional user input: */

    var targMsg = 'Please select one or more targets';
    var shell = comp.getShell();

    var errObj = createImageLabel(comp, 2, 2);

    var col1Comp = widgets.Composite(comp, swt.SWT.NONE);
    var col1CompLayout = layout.GridLayout();
    col1CompLayout.numColumns = 2;
    col1Comp.setLayout(col1CompLayout);
    var col1CompData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|layout.GridData.FILL_HORIZONTAL);
    col1CompData.minimumWidth = SHELL_WIDTH / 3;
    col1CompData.widthHint = SHELL_WIDTH / 3;
    col1Comp.setLayoutData(col1CompData);

    var mviComp = widgets.Composite(col1Comp, swt.SWT.BORDER);
    var mviLayout = layout.GridLayout();
    mviLayout.numColumns = 2;
    mviComp.setLayout(mviLayout);
    var mviData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|layout.GridData.FILL_HORIZONTAL);
    mviData.horizontalSpan = 2;
    mviComp.setLayoutData(mviData);

    var lbl = widgets.Label(mviComp, swt.SWT.NONE);
    lbl.setText('Module:');
    lbl.setToolTipText(wizard_constants.GENALG_MODULE_HOVER);
    var textModuleName = widgets.Text(mviComp, swt.SWT.BORDER);
    textModuleName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    textModuleName.addListener(swt.SWT.Modify, function(e) {
        textInterfaceName.setText('I' + textModuleName.getText());
        if (!expertCheck.getSelection()) {
            textPackageName.setText(textVendorName.getText() + '.' +
                                    textModuleName.getText());
        }
        setState();
    });
    textModuleName.addListener(swt.SWT.Verify, function(e) {
        e.text = String(e.text).toUpperCase();
    });
    addSelectAllListener(textModuleName);

    var lbl = widgets.Label(mviComp, swt.SWT.NONE);
    lbl.setText('Vendor:');
    lbl.setToolTipText(wizard_constants.GENALG_VENDOR_HOVER);
    var textVendorName = widgets.Text(mviComp, swt.SWT.BORDER);
    textVendorName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    textVendorName.addListener(swt.SWT.Modify, function(e) {
        if (!expertCheck.getSelection()) {
            textPackageName.setText(textVendorName.getText() + '.' +
                                    textModuleName.getText());
        }
        setState();
    });
    textVendorName.addListener(swt.SWT.Verify, function(e) {
        e.text = String(e.text).toUpperCase();
    });
    addSelectAllListener(textVendorName);

    var lbl = widgets.Label(mviComp, swt.SWT.NONE);
    lbl.setText('Interface:');
    lbl.setToolTipText(wizard_constants.GENALG_INTERFACE_HOVER);
    var textInterfaceName = widgets.Text(mviComp, swt.SWT.BORDER);
    textInterfaceName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    textInterfaceName.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    textInterfaceName.addListener(swt.SWT.Verify, function(e) {
        e.text = String(e.text).toUpperCase();
    });
    addSelectAllListener(textInterfaceName);

    // Templates Drop-down ComboBox
    var lbl = new widgets.Label(col1Comp, swt.SWT.NONE);
    lbl.setText("Base Interface: ");
    var templateComboBox = new widgets.Combo(col1Comp, swt.SWT.DROP_DOWN |
        swt.SWT.READ_ONLY);
    templateComboBox.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));

    var col2Comp = widgets.Composite(comp, swt.SWT.NONE);
    var col2Layout = layout.GridLayout();
    col2Layout.numColumns = 2;
    col2Comp.setLayout(col2Layout);
    var col2Data = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|layout.GridData.FILL_HORIZONTAL);
    col2Data.minimumWidth = SHELL_WIDTH / 2;
    col2Data.widthHint = SHELL_WIDTH / 2;
    col2Comp.setLayoutData(col2Data);

    var lbl = widgets.Label(col2Comp, swt.SWT.NONE);
    lbl.setText('Package Name:');
    lbl.setToolTipText(wizard_constants.GENALG_XDM_ALG_PKG_HOVER);
    var textPackageName = widgets.Text(col2Comp, swt.SWT.BORDER);
    textPackageName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    textPackageName.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    textPackageName.addListener(swt.SWT.Verify, function(e) {
        e.text = String(e.text).toLowerCase();
    });
    addSelectAllListener(textPackageName);

    // Targets table
    var lbl = new widgets.Label(col2Comp, swt.SWT.NONE );
    var lblData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING);
    lblData.verticalIndent = 4;
    lbl.setLayoutData(lblData);
    lbl.setText("Targets: ");
    lbl.setToolTipText(wizard_constants.GENALG_TARGET);

    var targetTable = widgets.Table(col2Comp,
            swt.SWT.SINGLE|swt.SWT.CHECK|swt.SWT.BORDER|swt.SWT.V_SCROLL);
    var gridDataStretch = layout.GridData(layout.GridData.FILL_HORIZONTAL);
    gridDataStretch.verticalIndent = 8;
    gridDataStretch.heightHint = 72;
    targetTable.setLayoutData(gridDataStretch);
    targetTable.addListener(swt.SWT.Selection, function(e) {
        if (e.detail == swt.SWT.CHECK) {
            setState();
        }
    });
    targetTable.addListener(swt.SWT.MouseHover, function(e) {
        controlMouseOver(shell, targetTable, e);
    });
    targetTable.addListener(swt.SWT.Dispose, function(e){ mouseLeave(e); });
    targetTable.addListener(swt.SWT.KeyDown, function(e){ mouseLeave(e); });
    targetTable.addListener(swt.SWT.MouseMove, function(e){ mouseLeave(e); });

    /* TODO: handle INVALID TARGET! */
    /* populate and init target table */
    function populateTargetTable(targetsObj) {
        targetTable.removeAll();
        for (var i = 0; i < wizard_constants.targetList.length; i++) {
            var item = widgets.TableItem(targetTable, 0);
            item.setText(wizard_constants.targetDesc[i]);
            var data = {};
            data.target = wizard_constants.targetList[i];
            data.targname = data.target.substr(data.target.lastIndexOf('.') + 1);
            data.targsuffix = wizard_constants.targetSuffixes[i];
            data.ccOpts = wizard_constants.ccOpts[i];
            data.cgTools = wizard_constants.cgTools[i];
            data.hover = wizard_constants.targetList[i];
            item.setData(data);
            if (targetsObj) {
                for (var j = 0; j < targetsObj.length; j++) {
                    if (targetsObj[j].target == wizard_constants.targetList[i]) {
                        item.setChecked(true);
                    }
                }
            }
        }
    }

    var iresCheck = widgets.Button(col2Comp, swt.SWT.CHECK);
    iresCheck.setText('Add IRES Interface');
    iresCheck.setToolTipText(wizard_constants.IRES_HOVER);

    var row2Comp = widgets.Composite(comp, swt.SWT.NONE);
    var row2Layout = layout.GridLayout();
    row2Layout.numColumns = 2;
    row2Comp.setLayout(row2Layout);
    var row2Data = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    row2Data.horizontalSpan = 2;
    row2Comp.setLayoutData(row2Data);

    // Browse for output directory
    var output = new BrowseButton(row2Comp, shell, isWin ? 200 : 230);
    output.setMessage("Set Destination Directory");
    output.btn.setToolTipText(wizard_constants.OUTPUT_HOVER);
    output.addListener("", "Please enter a valid package directory", false);
    output.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
    });
    output.textBox.addListener(swt.SWT.Modify, function(e) {
        setState();
    });

    var cgToolsGroup = createGroup(row2Comp, "'cgTools' Directories");
    var cgToolsGroupLayout = layout.GridLayout();
    cgToolsGroupLayout.numColumns = 2;
    cgToolsGroup.setLayout(cgToolsGroupLayout);
    var cgToolsGroupData = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    cgToolsGroupData.horizontalSpan = 2;
    cgToolsGroupData.horizontalIndent = -5;
    cgToolsGroup.setLayoutData(cgToolsGroupData);


    var cgTabFolder = widgets.TabFolder(cgToolsGroup, swt.SWT.NONE);
    var dataF = layout.GridData(layout.GridData.FILL_HORIZONTAL);
    cgTabFolder.setLayoutData(dataF);

    var tiC6000 = createTabItem(cgTabFolder, "C6000");

    // Browse for C6000 cgtools dir
    var cgTools = new BrowseButton(tiC6000.comp, shell, 0, true);
    cgTools.setMessage("Set C6000 TI 'cgtools' Dir");
    cgTools.btn.setToolTipText(wizard_constants.CGTOOLS_DESC);
    cgTools.textBox.setToolTipText(wizard_constants.CGTOOLS_DESC);
    cgTools.addListener("", "Please enter a valid TI CodeGen tools directory", false);
    cgTools.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
    });
    cgTools.textBox.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    tiC6000.item.setControl(tiC6000.comp);

    var tiM3 = createTabItem(cgTabFolder, "M3");

    // Browse for M3 cgtools dir
    var m3cgTools = new BrowseButton(tiM3.comp, shell, 0, true);
    m3cgTools.setMessage("Set ARM M3 TI 'cgtools' Dir");
    m3cgTools.btn.setToolTipText(wizard_constants.M3_CGTOOLS_DESC);
    m3cgTools.textBox.setToolTipText(wizard_constants.M3_CGTOOLS_DESC);
    m3cgTools.addListener("", "Please enter a valid TI ARM M3 CodeGen tools directory", false);
    m3cgTools.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
    });
    m3cgTools.textBox.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    tiM3.item.setControl(tiM3.comp);

    var tiGCC = createTabItem(cgTabFolder, "GCC");

    // Browse for Linux ARM cgtools dir
    var gccCgTools = new BrowseButton(tiGCC.comp, shell, 0, true);
    gccCgTools.setMessage("Set ARM GCC Linux 'cgtools' Dir");
    gccCgTools.btn.setToolTipText(wizard_constants.ARM_CGTOOLS_DESC);
    gccCgTools.textBox.setToolTipText(wizard_constants.ARM_CGTOOLS_DESC);
    gccCgTools.addListener("", "Please enter a valid ARM GCC Linux CodeGen tools directory", false);
    gccCgTools.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
    });
    gccCgTools.textBox.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    tiGCC.item.setControl(tiGCC.comp);

    var expertCheck = widgets.Button(comp, swt.SWT.CHECK);
    expertCheck.setText('Expert Mode');
    var expCheckData = new layout.GridData();
    expCheckData.horizontalIndent = 8;
    expertCheck.setLayoutData(expCheckData);
    expertCheck.setToolTipText(wizard_constants.EXPERT_HOVER);
    expertCheck.addListener(swt.SWT.Selection, function(e) {
        algEnv.expertCheck = e.widget.getSelection() ? true : false;
        if (!algEnv.expertCheck) {
            textPackageName.setText(textVendorName.getText() + '.' +
                                    textModuleName.getText());
        }
        setState();
    });

    var CCSProjCheck = widgets.Button(comp, swt.SWT.CHECK);
    CCSProjCheck.setText('Generate CCS Eclipse project');
    var projCheckData = new layout.GridData(layout.GridData.HORIZONTAL_ALIGN_END);
    CCSProjCheck.setLayoutData(projCheckData);

    var rulesCheck = widgets.Button(comp, swt.SWT.CHECK);
    rulesCheck.setText("Don't check for build dependencies, I'll modify the generated makefile (e.g. Rules.make users)");
    var rulesCheckData = new layout.GridData();
    rulesCheckData.verticalIndent = 8;
    rulesCheckData.horizontalIndent = 8;
    rulesCheckData.horizontalSpan = 2;
    rulesCheck.setLayoutData(rulesCheckData);
    rulesCheck.addListener(swt.SWT.Selection, function(e) {
        algEnv.rulesCheck = e.widget.getSelection() ? true : false;
        setState();
    });

    if (!algEnv.xdcVersOK) {
        var msgComp = widgets.Composite(comp, swt.SWT.NONE);
        var msgLayout = layout.GridLayout();
        msgLayout.numColumns = 2;
        msgComp.setLayout(msgLayout);
        var compData = layout.GridData(layout.GridData.FILL_HORIZONTAL);
        compData.horizontalSpan = 2;
        msgComp.setLayoutData(compData);

        var imgLabel = widgets.Label(msgComp, swt.SWT.NONE);
        imgData = layout.GridData();
        imgData.widthHint = 15;
        imgLabel.setLayoutData(imgData);
        imgLabel.setImage(ICO_WARNING);

        var textBox = new widgets.Text(msgComp, swt.SWT.WRAP|swt.SWT.MULTI|
                                                swt.SWT.READ_ONLY);
        var gridHint = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
        textBox.setLayoutData(gridHint);
        textBox.setText(XDCVERS_MSG);
    }


    // Create menu bar with listeners
    var menuBar = createMenu(shell, 0);
    menuBar.getItem(0).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (openListener) {
        algEnv = readXmlFile(shell, image, algEnv);
        populatePanel();
    });
    menuBar.getItem(0).getMenu().addListener(swt.SWT.Show, function(e) {
        menuBar.getItem(0).getMenu().getItem(1).setEnabled(!hasError());
    } );
    menuBar.getItem(0).getMenu().getItem(1).addListener(swt.SWT.Selection,
    function(saveListener) {
        collectInput();

        var complete = saveXmlFile(shell, algEnv);
        if (complete == true) {
            shared_gui.createMessageBox( "Save successful", algEnv);
        }
    } );

    menuBar.getItem(0).getMenu().getItem(3).addListener(swt.SWT.Selection,
    function() {
        var dialog = new widgets.DirectoryDialog(shell);
        dialog.setFilterPath(algEnv.templatesDir);
        var dir = dialog.open();
        if (dir != null) {
            algEnv.templatesDir = String(dir).replace(/\\/g,"/");
            updateTemplatesCombo();
            setState();
        }
    });
    menuBar.getItem(1).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (faqListener) {
        program.Program.launch(wizard_constants.GUI_HELP_LINK);
    } );
    menuBar.getItem(1).getMenu().getItem(1).addListener(swt.SWT.Selection,
    function (faqListener) {
        program.Program.launch(wizard_constants.FAQ_LINK);
    } );
    menuBar.getItem(1).getMenu().getItem(2).addListener(swt.SWT.Selection,
    function (tdListener) {
        program.Program.launch(wizard_constants.TEMPLATES_DIR_LINK);
    } );

    function updateTemplatesCombo() {
        var tFile = java.io.File(algEnv.templatesDir);
        templateComboBox.removeAll();
        // save/try to restore previous
        for each (var f in tFile.listFiles()) {
            if (f.isDirectory() &&

                java.io.File(f.getCanonicalPath() + '/mkpkg.xdt').exists()) {
                templateComboBox.add(f.getName());
            }
        }
        if (templateComboBox.getItemCount()) {
            var text = null;
            if (algEnv.templateName &&
                templateComboBox.indexOf(algEnv.templateName) != -1) {

               text = algEnv.templateName;
            }
            if (!text) {
                var index = templateComboBox.indexOf('IUNIVERSAL');
                if (index == -1) {
                    index = 0;
                }
                text = templateComboBox.getItem(index)
            }
            templateComboBox.setText(text);
        }
    }

    function populatePanel() {
        if (algEnv.packageName != null) {
            textPackageName.setText(algEnv.packageName);
        }
        if (algEnv.moduleName != null) {
            textModuleName.setText(algEnv.moduleName);
        }
        if (algEnv.vendorName != null) {
            textVendorName.setText(algEnv.vendorName);
        }
        if (algEnv.interfaceName != null) {
            textInterfaceName.setText(algEnv.interfaceName);
        }
        if (algEnv.templateName != null) {
            templateComboBox.setText(algEnv.templateName);
        }
        if (algEnv.output != null && algEnv.output != "null") {
            output.textBox.setText(algEnv.output);
        }
        populateTargetTable(algEnv.targets);
        if (algEnv.cgTools != null) {
            cgTools.textBox.setText(algEnv.cgTools.replace(/\\/g,'/'));
        }
        if (algEnv.m3cgTools != null) {
            m3cgTools.textBox.setText(algEnv.m3cgTools.replace(/\\/g,'/'));
        }
        if (algEnv.gccCgTools != null) {
            gccCgTools.textBox.setText(algEnv.gccCgTools.replace(/\\/g,'/'));
        }
        iresCheck.setSelection((algEnv.ires == true) ? true : false);
        CCSProjCheck.setSelection((algEnv.genCCSProj == true) ? true : false);
        rulesCheck.setSelection((algEnv.rulesCheck == true) ? true : false);
        expertCheck.setSelection((algEnv.expertCheck == true) ? true : false);

        setState();
    }

    updateTemplatesCombo();
    populatePanel();

    function hasError() {
        return (errObj.label1.getImage() != null);
    }

    function setState() {
        textInterfaceName.setEnabled(algEnv.expertCheck ? true : false);
        textPackageName.setEnabled(algEnv.expertCheck ? true : false);
        var C6x = false;
        var gcc = false;
        var M3 = false;
        for (var i = 0; i < targetTable.getItemCount(); i++) {
            if (targetTable.getItem(i).getChecked()) {
                if (!C6x && (wizard_constants.cgTools[i] == 'C64P' || wizard_constants.cgTools[i] == 'C674' ||
                    wizard_constants.cgTools[i] == 'C66' || wizard_constants.cgTools[i] == 'C67P')) {
                    C6x = true;
                }
                else if (!gcc && (wizard_constants.cgTools[i] == 'v5T' || wizard_constants.cgTools[i] == 'v6' ||
                         wizard_constants.cgTools[i] == 'v7A')) {
                    gcc = true;
                }
                else if (!M3 && wizard_constants.cgTools[i] == 'M3') {
                    M3 = true;
                }
            }
                if (C6x && gcc && M3) {
                    break;
                }
        }
        cgTools.textBox.setEnabled(C6x);
        cgTools.btn.setEnabled(C6x);
        gccCgTools.textBox.setEnabled(gcc);
        gccCgTools.btn.setEnabled(gcc);
        m3cgTools.textBox.setEnabled(M3);
        m3cgTools.btn.setEnabled(M3);
        var valid = validateInput();
        buttons.finishEnabled = valid;
        buttons.updated = true;
    }

    function validateInput() {
        var warnMsg = null;
        var msg;
        var valid = true;
        var validOutput = true;
        var validCgTools = true;
        var validGccCgTools = true;
        var validM3cgTools = true;

        if (String(textPackageName.getText()).length == 0 ||
            String(textModuleName.getText()).length == 0  ||
            String(textVendorName.getText()).length == 0  ||
            String(textInterfaceName.getText()).length == 0) {

            valid = false;
            msg = 'One or more empty fields';
        }
        else if (String(textPackageName.getText()).match(/ /) ||
            String(textModuleName.getText()).match(/ /)  ||
            String(textVendorName.getText()).match(/ /)  ||
            String(textInterfaceName.getText()).match(/ /)) {

            valid = false;
            msg = 'Spaces not allowed in Module, Vendor, Interface or Package name';
        }
        else if (String(templateComboBox.getText()).length == 0) {
            valid = false;
            msg = 'No templates';
        }
        if (valid) {
            var checked = false;
            for (var i = 0; i < targetTable.getItemCount(); i++) {
                if (targetTable.getItem(i).getChecked()) {
                    checked = true;
                    break;
                }
            }
            if (!checked) {
                valid = false;
                msg = targMsg;
            }
        }
        if (valid) {
            var outdir = String(output.textBox.getText());
            if (!outdir.length || !java.io.File(outdir).isDirectory()) {
                valid = validOutput = false;
            }
            if (valid) {
                /* check for overwrite */
                outdir = outdir + '/' +
                         String(textPackageName.getText()).replace(/\./g,'/');
                outdir = outdir.replace(/\\/g, '/');
                var outf = java.io.File(outdir);
                if (outf.exists() && outf.list().length > 0) {
                    warnMsg = 'Destination Directory is not empty--files may be overwritten';
                }
            }

            if (!rulesCheck.getSelection()) {
                if (cgTools.textBox.getEnabled() &&
                    !logic.validCgToolsDir(cgTools.textBox.getText())) {

                    valid = validCgTools = false;
                    cgTabFolder.setSelection(0);
                }
                else if (m3cgTools.textBox.getEnabled() &&
                         !logic.validM3cgToolsDir(m3cgTools.textBox.getText())) {
                    valid = validM3cgTools = false;
                    cgTabFolder.setSelection(1);
                }
                else if (gccCgTools.textBox.getEnabled() &&
                         !logic.validGccCgToolsDir(gccCgTools.textBox.getText())) {
                    valid = validGccCgTools = false;
                    cgTabFolder.setSelection(2);
                }
            }
            if (!valid) {
                msg = "Please enter valid ";
                if (!validOutput) {
                    msg += 'Destination Directory';
                    if (!validCgTools || !validGccCgTools || !validM3cgTools) {
                        msg += ' and ';
                    }
                }
                if (!validCgTools) {
                    msg += "C6000 TI 'cgTools' Dir";
                }
                else if (!validGccCgTools) {
                    msg += "ARM GCC Linux 'cgTools' Dir";
                }
                else if (!validM3cgTools) {
                    msg += "ARM M3 TI 'cgTools' Dir";
                }
            }
        }
        if (!valid) {
            setImageLabel(errObj, ICO_ERROR, msg);
        }
        else if (warnMsg) {
            setImageLabel(errObj, ICO_WARNING, warnMsg);
        }
        else {
            setImageLabel(errObj, null, '');
        }
        return (valid);
    }

    function collectInput() {
        algEnv.packageName = String(textPackageName.getText());
        algEnv.moduleName = String(textModuleName.getText());
        algEnv.vendorName = String(textVendorName.getText());
        algEnv.interfaceName = String(textInterfaceName.getText());
        algEnv.templateName = String(templateComboBox.getText());
        algEnv.output = String(output.textBox.getText());
        algEnv.targets = [];
        for (var i = 0; i < targetTable.getItemCount(); i++) {
            if (targetTable.getItem(i).getChecked()) {
                algEnv.targets.push(targetTable.getItem(i).getData());
            }
        }
        algEnv.ires = iresCheck.getSelection() ? true : false;
        algEnv.genCCSProj = CCSProjCheck.getSelection() ? true : false;
        if (cgTools.textBox.getEnabled()) {
            algEnv.cgTools = String(cgTools.textBox.getText());
        }
        if (gccCgTools.textBox.getEnabled()) {
            algEnv.gccCgTools = String(gccCgTools.textBox.getText());
        }
    }

    return {
        title:		    "   Basic Algorithm Information",
        composite:	    comp,
        collectInputFxn:    collectInput
    };
}

function finishOK(algEnv)
{
    var OK = true;
    return (OK);
}

function posNumberText(textBox, img, zeroOk)
{
    var valid = true;
    if (!isPosNumber(textBox.getText(), zeroOk)) {
        img.setImage(ICO_ERROR);
        valid = false;
    }
    else {
        img.setImage(null);
    }
    return (valid);
}



function createGroup(comp, text)
{
    var group = widgets.Group(comp, swt.SWT.SHADOW_NONE);
    group.setText(text);
    var layoutGroup = layout.GridLayout();
    layoutGroup.numColumns = 2;
    group.setLayout(layoutGroup);
    group.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    return (group);
}

function createTabItem(tabFolder, text)
{
    var item = widgets.TabItem(tabFolder, swt.SWT.NONE);
    item.setText(text);
    var comp = widgets.Composite(tabFolder, swt.SWT.NONE);
    comp.setBackground(display.getSystemColor(swt.SWT.COLOR_WIDGET_BACKGROUND));
    var itemLayout = new layout.GridLayout()
    itemLayout.numColumns = 2;
    comp.setLayout(itemLayout);
    var compData = layout.GridData(layout.GridData.FILL_BOTH);
    comp.setLayoutData(compData);
    return ({ item : item, comp : comp });
}

/**
 * Creates the menu bar at the top of each panel
 * @param {Shell}
 * @param {String} Message to display when user clicks on Instructions
 * @return menuBar
 */
function createMenu(shell, pageNum)
{
    var menuBar = new widgets.Menu(shell, swt.SWT.BAR);
    shell.setMenuBar(menuBar);

    var fileItem = new widgets.MenuItem(menuBar, swt.SWT.CASCADE);
    fileItem.setText ("&File");

    var fileSubmenu = new widgets.Menu(shell, swt.SWT.DROP_DOWN);
    fileItem.setMenu(fileSubmenu);

    var open = new widgets.MenuItem(fileSubmenu, swt.SWT.PUSH);
    open.setText("&Open");
    open.setAccelerator(swt.SWT.CTRL + 111); //111 is dec of o
    var save = new widgets.MenuItem(fileSubmenu, swt.SWT.PUSH);
    save.setText("&Save");
    save.setAccelerator(swt.SWT.CTRL + 115); //115 is dec of s
    new widgets.MenuItem(fileSubmenu, swt.SWT.SEPARATOR);
    var templatesDir = new widgets.MenuItem(fileSubmenu, swt.SWT.PUSH);
    templatesDir.setText("Set &Templates Directory...");
    templatesDir.setAccelerator(swt.SWT.CTRL + 116); //116 is dec of t


    var helpItem = new widgets.MenuItem(menuBar, swt.SWT.CASCADE);
    helpItem.setText ("&Help");
    helpItem.setAccelerator(swt.SWT.CTRL + 104); //104 is dec of h

    var helpSubmenu = new widgets.Menu(shell, swt.SWT.DROP_DOWN);
    helpItem.setMenu(helpSubmenu);

    var basic = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
    basic.setText("&Basic Algorithm Information");
    basic.setAccelerator(swt.SWT.CTRL + 98); //98 is dec of b

    var faq = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
    faq.setText("GenAlg Wizard &FAQ");
    faq.setAccelerator(swt.SWT.CTRL + 102); //102 is dec of f

    var templatesDir = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
    templatesDir.setText("&Templates Directory");
    templatesDir.setAccelerator(swt.SWT.CTRL + 116);

    new widgets.MenuItem(helpSubmenu, swt.SWT.SEPARATOR);
    var about = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
    about.setText("About");
    about.addListener(swt.SWT.Selection, function (aboutListener) {
        var msg = wizard_constants.ABOUT_MESSAGE + '\n\n' + csd;
        shared_gui.createMessageBox(msg, algEnv);
    });

    return menuBar;
}

/**
 * Generates a button that when selected creates a file dialog
 * @param {Composite}
 * @param {Shell}
 */
function BrowseButton(comp, shell, width, ellipsis) {

    this.comp = comp;
    this.shell = shell;

    var message = "";
    var errorMessage = "";
    var stringMatch = "";

    this.setMessage = function(message) {
        this.message = message;
        if (!this.ellipsis) {
            btn.setText(message);
        }
    }

    if (!ellipsis) {
        var btn = new widgets.Button(comp, swt.SWT.PUSH);
        var data = new layout.GridData();
        data.widthHint = width;
        btn.setLayoutData(data);
        this.btn = btn;
    }

    this.addListener = function(stringMatch, errorMessage, fileBool) {
        if (fileBool==true) {
            btn.addListener(swt.SWT.Selection, function(event) {
                var dialog = new widgets.FileDialog(shell);
                dialog.setFilterPath(textBox.getText());

                var file = dialog.open();
                if (file != null) {
                    file = String(file).replace(/\\/g,"/");
                    var suffix = file + "";
                    suffix = suffix.substring(
                        (suffix.lastIndexOf("/")+1), suffix.length);

                    if (suffix.match(stringMatch)!=null) {
                        textBox.setText(file);
                    }
                    else {
                        textBox.setText("");
                        shared_gui.createMessageBox(errorMessage, algEnv);
                    }

                }
            });
        }
        else {
            btn.addListener(swt.SWT.Selection, function(event) {
                var dialog = new widgets.DirectoryDialog(shell);
                dialog.setFilterPath(textBox.getText());

                var dir = dialog.open();
                if (dir != null) {
                    dir = String(dir).replace(/\\/g,"/");
                    var suffix = dir;
                    suffix = suffix.substring(
                        (suffix.lastIndexOf("/")+1), suffix.length);

                    if (suffix.match(stringMatch)!=null) {
                        textBox.setText(dir);
                    }
                    else {
                        textBox.setText("");
                        shared_gui.createMessageBox(errorMessage, algEnv);
                    }
                }
            });
        }
    }

    var textBox = new widgets.Text(comp, swt.SWT.SINGLE |
                                         swt.SWT.BORDER);
    textBox.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    addSelectAllListener(textBox);
    this.textBox = textBox;
    if (ellipsis) {
        var btn = new widgets.Button(comp, swt.SWT.PUSH);
        btn.setText(' ... ');
        this.btn = btn;
    }
    this.ellipsis = ellipsis;
}

/**
* GUI to save current algEnv to user_specified_loc.xml
* @param {Shell}
* @param {algEnv}
* @return Boolean: true if save successful, false otherwise
*/
function saveXmlFile(shell, algEnv) {

    /* create text for XML file from algEnv */
    var xmlText = xmlOps.saveXml(algEnv);

    /* get output location */
    var dialog = new widgets.FileDialog(shell, swt.SWT.SAVE);
    dialog.setFilterExtensions(filterExt);
    dialog.setFilterNames(filterNames);
    dialog.setFilterPath(algEnv.output);
    dialog.setFileName(algEnv.packageName.replace(/\./g,'_')
        + '_wizard.genalg');
    var file = dialog.open();
    if (file != null) {
        try {
            if (java.io.File(file).exists()) {
                var btnClicked = shared_gui.createYesNoBox(
                        file + " already exists! Do you want to overwrite it?",
                        algEnv);
                if (btnClicked == 1) {
                    var status = xmlOps.textFileWriter(file, xmlText);
                    if (status==-1) { return false; }
                    return true;
                }
            } else {
                var status = xmlOps.textFileWriter(file, xmlText);
                if (status==-1) { return false; }
                return true;
            }
        }
        catch(e) {
            shared_gui.createMessageBox("Error occured writing XML file:\n" + e,
                algEnv);
        }
    }
    return false;
}

/**
* GUI needed to read XML file
* @param image to be displayed on shell
* @param algEnv to be modified based on XML file
* @param shellLocation
* @return updated algEnv based on XML file
*/
function readXmlFile(shell, image, algEnv) {

    var xshell = new widgets.Shell(shell, swt.SWT.DIALOG_TRIM |
                                          swt.SWT.RESIZE);
    xshell.setSize(100,100);
    if (algEnv.shellLocation!=null) {
        xshell.setLocation(algEnv.shellLocation);
    }
    xshell.setImage(image);
    var dialog = new widgets.FileDialog(shell);
    dialog.setFilterExtensions(filterExt);
    dialog.setFilterNames(filterNames);
    var file = dialog.open();
    if (file != null) {
        try {
            algEnv = xmlOps.loadXml(file, algEnv);
        }
        catch(e) {
            var mbox = widgets.MessageBox(shell, swt.SWT.ICON_INFORMATION);
            mbox.setText("GenAlg Wizard Message");
            mbox.setMessage("Error occured reading XML file: " + e);
            mbox.open();
        }
    }
    xshell.close();
    return algEnv;
}

function controlMouseOver(shell, control, e)
{
    var item =  control.getItem(graphics.Point(e.x, e.y));
    if (item != null  && item.getData() != null) {
        var infoStr = '';
        var idata = item.getData();
        if (idata.hover) {
            infoStr = String(idata.hover);
        }
        else {
            infoStr = String(data);
            if (algEnv.reposMap[infoStr]) {
                infoStr += "\n in " + algEnv.reposMap[infoStr];
            }
        }
        itemHover(shell, control, item, infoStr, graphics.Point(e.x, e.y));
    }
}

function itemHover(shell, control, item, text, curPt)
{
    var pt;

    if (hoverTip != null  && !hoverTip.isDisposed()) {
        hoverTip.dispose();
    }
    hoverTip = widgets.Shell(shell, swt.SWT.ON_TOP|swt.SWT.NO_FOCUS|swt.SWT.TOOL);
    hoverTip.setBackground (display.getSystemColor (swt.SWT.COLOR_INFO_BACKGROUND));
    var lo = layout.FillLayout();
    lo.marginWidth = 2;
    hoverTip.setLayout(lo);
    hoverLabel = widgets.Label(hoverTip, swt.SWT.NONE);
    hoverLabel.setForeground(display.getSystemColor(swt.SWT.COLOR_INFO_FOREGROUND));
    hoverLabel.setBackground(display.getSystemColor(swt.SWT.COLOR_INFO_BACKGROUND));
    hoverLabel.setText(text);
    hoverLabel.addListener(swt.SWT.MouseExit, function(e) { mouseLeave(e); });
    hoverLabel.addListener(swt.SWT.MouseDown, function(e) { mouseLeave(e); });
    var size = hoverTip.computeSize(swt.SWT.DEFAULT, swt.SWT.DEFAULT);
    var rect = item.getBounds(0);
    if (curPt == undefined) {
        pt = control.toDisplay(rect.x, rect.y);
    }
    else {
        pt = control.toDisplay(curPt.x, curPt.y);
    }
    var monRect = display.getPrimaryMonitor().getClientArea();
    var left = (pt.x + size.x <= monRect.width) ? pt.x :
               pt.x - size.x;

    var top = (pt.y + rect.height + 4 + size.y <= monRect.height) ?
              pt.y + rect.height + 4 : pt.y - size.y - 4;
    if (top < 0) {
        top = 0;
    }
    hoverTip.setBounds(left, top, size.x, size.y);
    hoverTip.setVisible(true);
}

function mouseLeave(e)
{
    if (hoverTip != null) {
        hoverTip.dispose();
        hoverTip = null;
        hoverLabel = null;
    }
}

function navigatePages(parent)
{
    var currentPage = 0;

    while (true) {

        var shell = new widgets.Shell(display, swt.SWT.DIALOG_TRIM |
            swt.SWT.RESIZE | swt.SWT.MIN);
        shell.setImage(image);
        shell.setLayout(new layout.FormLayout());
        shell.setText("XDM GenAlg Wizard");
        shell.setMinimumSize(SHELL_WIDTH, SHELL_HEIGHT);
        shell.addListener(swt.SWT.Move, function(event) {
            try {
                algEnv.shellLocation = shell.getLocation();
            }
            catch(e) {}
        });
        algEnv.shell = shell;

        var compMain = new widgets.Composite(shell, swt.SWT.NONE);
        var layoutMain = new layout.GridLayout();
        layoutMain.numColumns = 2;
        layoutMain.horizontalSpacing = 15;
        compMain.setLayout(layoutMain);

        var labelTitle = new widgets.Label(compMain, swt.SWT.WRAP);
        var fillLabelTitle = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
        fillLabelTitle.horizontalSpan = 2;
        labelTitle.setLayoutData(fillLabelTitle);

        var space = new widgets.Label(compMain, swt.SWT.SEPARATOR |
            swt.SWT.HORIZONTAL);
        fillLabelTitle = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
        fillLabelTitle.horizontalSpan = 2;
        space.setLayoutData(fillLabelTitle);

        var pageData = pageFxns[ currentPage ](compMain);
        var point = pageData.composite.computeSize(swt.SWT.DEFAULT,
            swt.SWT.DEFAULT, false);
        labelTitle.setText(pageData.title);

        var formMain = new layout.FormData();
        formMain.top = new layout.FormAttachment(0, 10);
        formMain.left = new layout.FormAttachment(0, 10);
        formMain.right = new layout.FormAttachment(100, -10);
        compMain.setLayoutData(formMain);

        var compLine = new widgets.Composite(shell, swt.SWT.NONE);
        var layoutLine = new layout.RowLayout();
        layoutLine.pack = false;
        compLine.setLayout(layoutLine);
        var lbl = new widgets.Label(compLine, swt.SWT.SEPARATOR |
            swt.SWT.HORIZONTAL);
        lbl.setLayoutData(new layout.RowData(1000, swt.SWT.DEFAULT));

        var comp = new widgets.Composite(shell, swt.SWT.NONE);
        var lay = new layout.RowLayout();
        lay.pack = false;
        comp.setLayout(lay);

        var btnFinish = new widgets.Button(comp, swt.SWT.PUSH);
        btnFinish.setText("   &Finish   ");

        var btnCancel = new widgets.Button(comp, swt.SWT.PUSH);
        btnCancel.setText("   &Cancel   ");

        var formRow = new layout.FormData();
        formRow.left = new layout.FormAttachment(0, 200);
        formRow.bottom = new layout.FormAttachment(100, -10);
        formRow.right = new layout.FormAttachment(100, -10);
        comp.setLayoutData(formRow);

        var formLine = new layout.FormData();
        formLine.left = new layout.FormAttachment(0, 10);
        formLine.right = new layout.FormAttachment(100, -10);
        formLine.bottom = new layout.FormAttachment(comp, -5, swt.SWT.TOP);
        compLine.setLayoutData(formLine);

        btnFinish.enabled = buttons.finishEnabled;

        var eventFinish = false;
        var eventCancel = false;

        btnCancel.addListener(swt.SWT.Selection, function(e) {
            eventCancel = true;
        });

        btnFinish.addListener(swt.SWT.Selection, function(e) {
            eventFinish = true;
        });

        var displayRect = display.getBounds();
        if (algEnv.shellLocation!=null) {
            shell.setLocation(algEnv.shellLocation);
        }

        shell.setSize(SHELL_WIDTH, SHELL_HEIGHT);
        shell.open();
        buttons.updated = false;

        shell.addListener(swt.SWT.Close, function(e) {
              pageData.collectInputFxn();
              var btnClicked = shared_gui.createYesNoBox(
                  "Do you want to quit?", algEnv);
              if (btnClicked == 1) {
                  print("Closing XDM GenAlg Wizard now...");
                  shell.dispose();
                  eventCancel = true;
              }
        });
        while(!shell.isDisposed()) {
            if (!display.readAndDispatch()) {
                java.lang.Thread.sleep(50);
                if (eventFinish) {
                    pageData.collectInputFxn();
/*
                    if (!finishOK(algEnv)) {
                        eventFinish = false;
                        continue;
                    }
*/
                    var btnClicked = shared_gui.createYesNoBox(
                        "Would you like to save the values entered into "
                        + "the XDM GenAlg Wizard?", algEnv);
                    if (btnClicked == 1) {
                        var complete = saveXmlFile(shell, algEnv);
                        if (complete == true) {
                            shared_gui.createMessageBox("Save successful",
                                                        algEnv);
                        }
                    }
                    break;
                }
                if (eventCancel) {
                    pageData.collectInputFxn();
                    var btnClicked = shared_gui.createYesNoBox(
                        "Do you want to quit?", algEnv);
                    if (btnClicked == 1) {
                        print("Closing GUI XDM GenAlg Wizard now...");
                    }
                    else {
                        eventCancel = false;
                    }
                    break;
                }
                if (buttons.updated) {
                    buttons.updated   = false;
                    btnFinish.enabled = buttons.finishEnabled;
                }
            }
            try {
                shellLocation = shell.getLocation();
            }
            catch(e) {}
        }
        if (!shell.isDisposed()) {
            shell.dispose();
        }
        if (eventFinish || eventCancel) {
            break;
        }
    }
    if (!parent) {
        display.dispose();
    }
    return (eventFinish == true);
}

function main(algEnv, parent) {
    print("\nStarting GUI XDM GenAlg Wizard now...");
    print('GUI XDM GenAlg Wizard user:\n'
          + 'You can ignore any warnings below about Mozilla this or that missing.');

    initSWT();

    init(algEnv, parent);


    this.algEnv = algEnv;
    var success = navigatePages(parent);


    if (!success) {
        algEnv.error = true;
    }
    return (algEnv);
}


function isPosNumber(text, zeroOK)
{
    var ret = false;

    text = String(text);
    if (text.length > 0) {
        if (!text.match(/\D/g)) {
            if ((zeroOK && Number(text) >= 0) ||
                Number(text) > 0) {

                ret = true;
            }
        }
    }
    return (ret);
}


/**
 * Creates a banner of instructions at the top of each panel
 * @param {Shell}
 * @param {String} Message to display at top of panel
 */
function InstructionBanner(comp) {
    var text = "";

    var textBox = new widgets.Text(comp, swt.SWT.WRAP
        |swt.SWT.MULTI | swt.SWT.BORDER|swt.SWT.READ_ONLY);
    var gridHint = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    gridHint.horizontalSpan = 2;
    textBox.setLayoutData(gridHint);

    this.setText = function(text) {
        this.text = text;
        textBox.setText(text);
    }
}

function createImageLabel(comp, cols, span)
{
    var lblComp = widgets.Composite(comp, swt.SWT.NONE);
    var lblLayout = layout.GridLayout();
    lblLayout.numColumns = cols;
    lblComp.setLayout(lblLayout);
    var compData = layout.GridData(layout.GridData.FILL_HORIZONTAL);
    compData.horizontalSpan = span;
    lblComp.setLayoutData(compData);

    var label1 = widgets.Label(lblComp, swt.SWT.NONE);
    label1Data = layout.GridData();
    label1Data.widthHint = 15;
    label1.setLayoutData(label1Data);
    label1.setImage(null);

    var label2 = widgets.Label(lblComp, swt.SWT.NONE);
    label2.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    return {
        label1: label1,
        label2: label2
    };
}

function setImageLabel(msgObj, img, msg)
{
    msgObj.label1.setImage(img);
    msgObj.label2.setText(msg);
}

function selectAllListener(e)
{
    if (e.widget.getEditable()) {
        e.widget.setSelection(0, String(e.widget.getText()).length);
    }
}

function addSelectAllListener(text)
{
    text.addListener(swt.SWT.FocusIn, selectAllListener);
}

