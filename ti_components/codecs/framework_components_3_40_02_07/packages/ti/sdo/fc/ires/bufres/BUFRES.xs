/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
/*
 *  ======== BUFRES.xs ========
 */

function module$use()
{
    var BUFRES = this;
    var os = Program.build.target.os;
    var fcSettings = xdc.useModule('ti.sdo.fc.global.Settings');

    //print(this.$name + ".module$use() ...");
    xdc.useModule('xdc.runtime.Log');
    xdc.useModule('xdc.runtime.Assert');
    var Diags = xdc.useModule('xdc.runtime.Diags');

    var defaultMask;

if (0) {

    if ((BUFRES.enableLog == undefined)&&(fcSettings.enableLogFC==false) ||
            (BUFRES.enableLog == false)) {
        defaultMask = Diags.ALWAYS_OFF;

        BUFRES.enableLog = false;
    }
    else {
        defaultMask = Diags.RUNTIME_OFF;
        BUFRES.enableLog = true;
    }

    if (BUFRES.common$.diags_ASSERT == undefined) {
        BUFRES.common$.diags_ASSERT = defaultMask;
    }

    if (BUFRES.common$.diags_ENTRY == undefined) {
        BUFRES.common$.diags_ENTRY = defaultMask;
    }

    if (BUFRES.common$.diags_EXIT == undefined) {
        BUFRES.common$.diags_EXIT = defaultMask;
    }

    if (BUFRES.common$.diags_INTERNAL == undefined) {
        BUFRES.common$.diags_INTERNAL = defaultMask;
    }

    if (BUFRES.common$.diags_USER1 == undefined) {
        BUFRES.common$.diags_USER1 = defaultMask;
    }

    if (BUFRES.common$.diags_USER2 == undefined) {
        BUFRES.common$.diags_USER2 = defaultMask;
    }

    if (BUFRES.common$.diags_USER3 == undefined) {
        BUFRES.common$.diags_USER3 = defaultMask;
    }

    if (BUFRES.common$.diags_USER4 == undefined) {
        BUFRES.common$.diags_USER4 = defaultMask;
    }

    if (BUFRES.common$.diags_USER5 == undefined) {
        BUFRES.common$.diags_USER5 = defaultMask;
    }

    if (BUFRES.common$.diags_USER6 == undefined) {
        BUFRES.common$.diags_USER6 = defaultMask;
    }

    if (BUFRES.common$.diags_USER7 == undefined) {
        BUFRES.common$.diags_USER7 = defaultMask;
    }

    if (BUFRES.common$.diags_USER8 == undefined) {
        BUFRES.common$.diags_USER8 = defaultMask;
    }
}
}
