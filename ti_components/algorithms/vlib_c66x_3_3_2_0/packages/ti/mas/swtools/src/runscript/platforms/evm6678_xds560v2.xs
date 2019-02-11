/* --COPYRIGHT--,BSD
 * Copyright (c) $(CPYYEAR), Texas Instruments Incorporated
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
 * --/COPYRIGHT--*/
var Main = xdc.useModule('runscript.Main');

/* ========= Start edit here ======== */
/* Configure the scripts for this specific target configuration. */

var platformName = "ti.omp.examples.platforms.evm6678";

Main.addCpu(platformName, "C66xx_0", false);
Main.addCpu(platformName, "C66xx_1", false);
Main.addCpu(platformName, "C66xx_2", false);
Main.addCpu(platformName, "C66xx_3", false);
Main.addCpu(platformName, "C66xx_4", false);
Main.addCpu(platformName, "C66xx_5", false);
Main.addCpu(platformName, "C66xx_6", false);
Main.addCpu(platformName, "C66xx_7", false);

Main.CCSPlatform = "*";
Main.shortPlatformName = "evm6678";

Main.ccxmlConfigFile = "regression/common/ccxml/evm6678_xds560v2.ccxml";

/* ========= End edit here ======== */

Main.run(arguments);
