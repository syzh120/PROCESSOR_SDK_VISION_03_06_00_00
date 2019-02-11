/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 */
/* This "requires" list describes what packages to import into this bundle */
requires ti.sdo.fc.global;
requires ti.sdo.fc.dskt2;
requires ti.sdo.fc.ecpy;

requires ti.sdo.fc.utils;
requires ti.sdo.fc.utils.osalsupport;
requires ti.sdo.fc.memutils;

requires ti.sdo.fc.ires;
requires ti.sdo.fc.ires.bufres;
requires ti.sdo.fc.ires.edma3chan;
requires ti.sdo.fc.ires.hdvicp;
requires ti.sdo.fc.ires.nullresource;
requires ti.sdo.fc.ires.tiledmemory;
requires ti.sdo.fc.ires.vicp;

requires ti.sdo.fc.rman;

requires ti.sdo.fc.edma3;
requires ti.sdo.fc.edmamgr;

requires ti.sdo.tiler;

/* Examples */
//requires ti.sdo.fc.ires.examples.codecs;
//requires ti.sdo.fc.ires.examples.codecs.template;
//requires ti.sdo.fc.ires.examples.codecs.universal_dma;

/*!
 *  ======== framework_components ========
 *  The Framework Components product package.
 *
 *  This package is a "bundle" of several Framework Components packages.
 */
package framework_components_3_40_02_07 [1, 0, 0] {
}
