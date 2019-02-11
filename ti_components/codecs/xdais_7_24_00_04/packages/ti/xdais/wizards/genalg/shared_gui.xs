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
var swt;
var browser;
var custom;
var graphics;
var layout;
var widgets;
var events;

var base = String(xdc.csd()).replace(/\\/g,"/");

function initSWT() {
    swt = xdc.jre.org.eclipse.swt;
    browser = xdc.jre.org.eclipse.swt.browser;
    custom = xdc.jre.org.eclipse.swt.custom;
    graphics = xdc.jre.org.eclipse.swt.graphics;
    layout = xdc.jre.org.eclipse.swt.layout;
    widgets = xdc.jre.org.eclipse.swt.widgets;
    events = xdc.jre.org.eclipse.swt.events;
}

/**
* Opens a new message box widget
* @param {String} message This message will be displayed in the message box
* @param {algEnv} 
*/            
function createMessageBox(message, algEnv)
{ 
    if (algEnv.tid != algEnv.guiId) {
         _syncExecMessageBox(message, algEnv);
    }
    else {
        _createMessageBox(message, algEnv);
    }
}

function _createMessageBox(message, algEnv)
{ 
    initSWT();

    if (algEnv.shell && !algEnv.shell.isDisposed()) {
        var shellMessage = algEnv.shell;
    }
    else if (algEnv.display && !algEnv.display.isDisposed()) {
        var shellMessage = new widgets.Shell(algEnv.display, 
                                             swt.SWT.APPLICATION_MODAL);
    }
    else {
        var shellMessage = new widgets.Shell();
    }
    if (algEnv.shellLocation != null) {
        shellMessage.setLocation(algEnv.shellLocation);
    }
    var msgBox = widgets.MessageBox(shellMessage, swt.SWT.OK);
    msgBox.setText("XDAIS GenAlg Wizard");
    msgBox.setMessage(message);
    msgBox.open();
}

function _syncExecMessageBox(message, algEnv)
{
    if (!algEnv.display.isDisposed()) {
        try {
            algEnv.display.syncExec(
                new java.lang.Runnable() {
                    run: function() {
                        try {
                            retVal = _createMessageBox(message, algEnv);
                        }
                        catch (e) {}
                    }
            });
        }
        catch (e) {}
    }
}

/**
* Opens a new message box widget with yes and no options
* @param {String} message This message will be displayed in the message box
* @param {algEnv}
*/            
function createYesNoBox(message, algEnv)
{ 
    if (algEnv.tid != algEnv.guiId) {
        var retVal = _syncExecYesNoBox(message, algEnv);
    }
    else {
        var retVal = _createYesNoBox(message, algEnv);
    }
    return (retVal);
}

function _createYesNoBox(message, algEnv)
{ 
    initSWT();

    if (algEnv.shell && !algEnv.shell.isDisposed()) {
        var shellMessage = algEnv.shell;
    }
    else if (algEnv.display && !algEnv.display.isDisposed()) {
        var shellMessage = new widgets.Shell(algEnv.display, 
                                             swt.SWT.APPLICATION_MODAL);
    }
    else {
        var shellMessage = new widgets.Shell();
    }
    if (algEnv.shellLocation!=null) {
        shellMessage.setLocation(algEnv.shellLocation);
    }
    var msgBox = widgets.MessageBox(shellMessage, swt.SWT.YES|swt.SWT.NO);
    msgBox.setText("XDAIS GenAlg Wizard");
    msgBox.setMessage(message);
    var retVal = msgBox.open();
    return (retVal == swt.SWT.YES) ? 1 : 2;
}


function _syncExecYesNoBox(message, algEnv)
{
    var retVal = 2;
    if (!algEnv.display.isDisposed()) {
        try {
            algEnv.display.syncExec(
                new java.lang.Runnable() {
                    run: function() {
                        try {
                            retVal = _createYesNoBox(message, algEnv);
                        }
                        catch (e) {}
                    }
            });
        }
        catch (e) {}
    }
    return (retVal);
}

