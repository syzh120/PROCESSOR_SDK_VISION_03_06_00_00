/*
 * Copyright (c) 2012-2014 Texas Instruments Incorporated - http://www.ti.com
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
/*
 *  ======== TableInit.xs ========
 *
 */

/*
 * When assigning virtual indexes to each core make sure
 * to assign even virtual indexes to DSP/M4 cores with
 * even Core Ids, and assign odd virtual indexes to DSP/M4
 * cores with odd Core Ids.
 *
 * Example:
 *     DSP physical Core Id = 0 -> Virtual Index = 4;
 *     DSP physical Core Id = 1 -> Virtual Index = 5;
 *
 * Virtual Index Assignment:
 *
 * | EVE1 -> 0 | EVE2 -> 1   | EVE3 -> 2   | EVE4 -> 3   |
 * | DSP1 -> 4 | DSP2 -> 5   | IPU1-0 -> 6 | IPU2-0 -> 7 |
 * | HOST -> 8 | IPU1-1 -> 9 | IPU2-1 -> 10
 *
 */
var eve1VirtId    = 0;
var eve2VirtId    = 1;
var eve3VirtId    = 2;
var eve4VirtId    = 3;
var dsp1VirtId    = 4;
var dsp2VirtId    = 5;
var ipu1_0VirtId  = 6;
var ipu2_0VirtId  = 7;
var hostVirtId    = 8;
var ipu1_1VirtId  = 9;
var ipu2_1VirtId  = 10;


/*
 *  ======== initProcId ========
 *  Assign MultiProc ids and virtual processor ids.
 */
function initProcId(mod)
{
    var MultiProc = xdc.useModule("ti.sdo.utils.MultiProc");

    for (var i = 0; i < mod.procIdTable.length; i++) {
        mod.procIdTable[i] = -1;
    }

    mod.eve1ProcId   = MultiProc.getIdMeta("EVE1");
    mod.eve2ProcId   = MultiProc.getIdMeta("EVE2");
    mod.eve3ProcId   = MultiProc.getIdMeta("EVE3");
    mod.eve4ProcId   = MultiProc.getIdMeta("EVE4");
    mod.dsp1ProcId   = MultiProc.getIdMeta("DSP1");
    mod.dsp2ProcId   = MultiProc.getIdMeta("DSP2");
    mod.ipu1_0ProcId = MultiProc.getIdMeta("IPU1");  /* assume smp */
    mod.ipu1_1ProcId = MultiProc.getIdMeta("IPU1-1");
    mod.ipu2_0ProcId = MultiProc.getIdMeta("IPU2");  /* assume smp */
    mod.ipu2_1ProcId = MultiProc.getIdMeta("IPU2-1");
    mod.hostProcId   = MultiProc.getIdMeta("HOST");

    if (mod.eve1ProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.eve1ProcId] = eve1VirtId;
    }
    if (mod.eve2ProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.eve2ProcId] = eve2VirtId;
    }
    if (mod.eve3ProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.eve3ProcId] = eve3VirtId;
    }
    if (mod.eve4ProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.eve4ProcId] = eve4VirtId;
    }
    if (mod.dsp1ProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.dsp1ProcId] = dsp1VirtId;
    }
    if (mod.dsp2ProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.dsp2ProcId] = dsp2VirtId;
    }

    if (mod.ipu1_0ProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.ipu1_0ProcId] = ipu1_0VirtId;
    }
    else {
        /* IPU1 not smp */
        mod.ipu1_0ProcId = MultiProc.getIdMeta("IPU1-0");

        if (mod.ipu1_0ProcId != MultiProc.INVALIDID) {
            mod.procIdTable[mod.ipu1_0ProcId] = ipu1_0VirtId;
        }
    }

    if (mod.ipu1_1ProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.ipu1_1ProcId] = ipu1_1VirtId;
    }

    if (mod.ipu2_0ProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.ipu2_0ProcId] = ipu2_0VirtId;
    }
    else {
        /* IPU2 not smp */
        mod.ipu2_0ProcId = MultiProc.getIdMeta("IPU2-0");

        if (mod.ipu2_0ProcId != MultiProc.INVALIDID) {
            mod.procIdTable[mod.ipu2_0ProcId] = ipu2_0VirtId;
        }
    }

    if (mod.ipu2_1ProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.ipu2_1ProcId] = ipu2_1VirtId;
    }

    if (mod.hostProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.hostProcId] = hostVirtId;
    }
}

/*
 * Function to generate mailbox table
 */
function generateTable(InterruptCore)
{
    var SYS_MBX5_OFFSET = 0;
    var SYS_MBX6_OFFSET = 1;
    var SYS_MBX7_OFFSET = 2;
    var SYS_MBX8_OFFSET = 3;
    var eveMbx2BaseIdx = 2;

    var index;
    var subMbxIdx;
    var tableEntry;
    var mbxUserIdx;
    var mbxBaseAddrIdx;

    /*
     * Each entry in the mailbox table stores 3 indexes.
     * The breakup of each entry is shown below:
     * Entry format : 0xAAAABBCC
     *         AAAA : Mailbox base address table index
     *           BB : Mailbox User Id
     *           CC : Sub-mailbox index
     *
     * In order to lookup the User Id, Sub-mailbox Index and mailbox base
     * address for a given src and dst core from the mailboxTable, the
     * procedure shown below is followed:
     *     1. Find the right entry for the given src and dst core.
     *        mailboxTable index is given by:
     *            Index = (src * NumCores) + dst
     *     2. Mbx BaseAddr Index = mailboxTable[Index] >> 16
     *     2. dst Mailbox UserId = (mailboxTable[Index] >> 8) & 0xFF
     *     3. Sub-Mailbox Index  = mailboxTable[Index] & 0xFF
     */

    /*
     * 'i' is src core index, and
     * 'j' is dst core index
     */
    for (var i = 0; i < InterruptCore.NUM_CORES; i++) {
        for (var j = 0; j < InterruptCore.NUM_CORES; j++) {

            /* init mailboxTable */
            index = (i * InterruptCore.NUM_CORES) + j;
            InterruptCore.mailboxTable[index] = -1;

            /* EVE Internal Mailbox 2 */
            if ((i < InterruptCore.NUM_EVES) && (j < InterruptCore.NUM_EVES)) {

                /* Generate 3 masks forming a single table entry */
                mbxBaseAddrIdx = ((j * 3) + eveMbx2BaseIdx) << 16;

                /* Determined based on the send remote receive local
                 * methodology being followed for EVE-to-EVE communication.
                 */
                mbxUserIdx = 0 << 8;
                subMbxIdx = i;

                tableEntry = mbxBaseAddrIdx | mbxUserIdx | subMbxIdx;
                InterruptCore.mailboxTable[index] = tableEntry;
                continue;
            }

            /* EVE Internal Mailbox 0/1 */
            if ((i < InterruptCore.NUM_EVES) || (j < InterruptCore.NUM_EVES)) {
                if (i < InterruptCore.NUM_EVES) {
                    mbxBaseAddrIdx = ((i * 3) + (j % 2)) << 16;

                    if ((j == dsp1VirtId) || (j == dsp2VirtId)) {
                        /* Destination is DSP1 or DSP2 */
                        mbxUserIdx = 1 << 8;
                        subMbxIdx = 0;
                    }
                    else if ((j == ipu1_0VirtId) || (j == ipu2_0VirtId)) {
                        /* Destination is IPU1-0 or IPU2-0 */
                        mbxUserIdx = 2 << 8;
                        subMbxIdx = 2;
                    }
                    else if ((j == ipu1_1VirtId) || (j == hostVirtId) ||
                        (j == ipu2_1VirtId)) {
                        /* Destination is Host or IPU1-1 */
                        mbxUserIdx = 3 << 8;
                        subMbxIdx = 4;

                        if (j == ipu2_1VirtId) {
                            mbxBaseAddrIdx = ((i * 3) + ((j - 1) % 2)) << 16;
                        }
                    }

                    tableEntry = mbxBaseAddrIdx | mbxUserIdx | subMbxIdx;
                    InterruptCore.mailboxTable[index] = tableEntry;
                    continue;
                }
                else if (j < InterruptCore.NUM_EVES) {
                    mbxBaseAddrIdx = ((j * 3) + (i % 2)) << 16;
                    mbxUserIdx = 0 << 8; /* destination is always EVE */

                    if ((i == dsp1VirtId) || (i == dsp2VirtId)) {
                        /* Source is DSP1 or DSP2 */
                        subMbxIdx = 1;
                    }
                    else if ((i == ipu1_0VirtId) || (i == ipu2_0VirtId)) {
                        /* Source is IPU1-0 or IPU2-0 */
                        subMbxIdx = 3;
                    }
                    else if ((i == ipu1_1VirtId) || (i == hostVirtId) ||
                        (i == ipu2_1VirtId)) {
                        /* Source is Host or IPU1-1*/
                        subMbxIdx = 5;

                        if (i == ipu2_1VirtId) {
                            mbxBaseAddrIdx = ((j * 3) + ((i - 1) % 2)) << 16;
                        }
                    }

                    tableEntry = mbxBaseAddrIdx | mbxUserIdx | subMbxIdx;
                    InterruptCore.mailboxTable[index] = tableEntry;
                    continue;
                }
            }

            /* System Mailbox 5 */
            /* For communication between HOST<->DSP1/IPU1 */
            if (((i == dsp1VirtId) || (i == ipu1_0VirtId) ||
                (i == hostVirtId) || (i == ipu1_1VirtId)) &&
                ((j == dsp1VirtId) || (j == ipu1_0VirtId) ||
                (j == hostVirtId) || (j == ipu1_1VirtId))) {

                mbxBaseAddrIdx = ((InterruptCore.NUM_EVES * 3) +
                                  SYS_MBX5_OFFSET) << 16;

                /* These combinations do not need mailbox */
                if ((i == j) ||
                    (i == ipu1_0VirtId && j == ipu1_1VirtId) ||
                    (i == ipu1_1VirtId && j == ipu1_0VirtId)) {
                    continue;
                }

                if (j == dsp1VirtId) {
                    mbxUserIdx = 0;
                    if (i == ipu1_0VirtId) {
                        subMbxIdx = 3;
                    }
                    else if (i == hostVirtId) {
                        subMbxIdx = 5;
                    }
                    else if (i == ipu1_1VirtId) {
                        subMbxIdx = 8;
                    }
                }
                else if (j == ipu1_0VirtId) {
                    mbxUserIdx = 1 << 8;
                    if (i == dsp1VirtId) {
                        subMbxIdx = 0;
                    }
                    else if (i == hostVirtId) {
                        subMbxIdx = 6;
                    }
                }
                else if (j == hostVirtId) {
                    mbxUserIdx = 2 << 8;
                    if (i == dsp1VirtId) {
                        subMbxIdx = 1;
                    }
                    else if (i == ipu1_0VirtId) {
                        subMbxIdx = 4;
                    }
                    else if (i == ipu1_1VirtId) {
                        subMbxIdx = 9;
                    }
                }
                else if (j == ipu1_1VirtId) {
                    mbxUserIdx = 3 << 8;
                    if (i == dsp1VirtId) {
                        subMbxIdx = 2;
                    }
                    else if (i == hostVirtId) {
                        subMbxIdx = 7;
                    }
                }

                tableEntry = mbxBaseAddrIdx | mbxUserIdx | subMbxIdx;
                InterruptCore.mailboxTable[index] = tableEntry;
                continue;
            }

            /* System Mailbox 6 */
            /* For communication between HOST<->DSP2/IPU2 */
            if (((i == dsp2VirtId) || (i == ipu2_0VirtId) ||
                (i == hostVirtId) || (i == ipu2_1VirtId)) &&
                ((j == dsp2VirtId) || (j == ipu2_0VirtId) ||
                (j == hostVirtId) || (j ==ipu2_1VirtId))) {

                mbxBaseAddrIdx = ((InterruptCore.NUM_EVES * 3) +
                                   SYS_MBX6_OFFSET) << 16;

                /* These combinations do not need mailbox */
                if ((i == j) ||
                    (i == ipu2_0VirtId && j == ipu2_1VirtId) ||
                    (i == ipu2_1VirtId && j == ipu2_0VirtId)) {
                    continue;
                }

                if (j == dsp2VirtId) {
                    mbxUserIdx = 0;
                    if (i == ipu2_0VirtId) {
                        subMbxIdx = 3;
                    }
                    else if (i == hostVirtId) {
                        subMbxIdx = 5;
                    }
                    else if (i == ipu2_1VirtId) {
                        subMbxIdx = 8;
                    }
                }
                else if (j == ipu2_0VirtId) {
                    mbxUserIdx = 1 << 8;
                    if (i == dsp2VirtId) {
                        subMbxIdx = 0;
                    }
                    else if (i == hostVirtId) {
                        subMbxIdx = 6;
                    }
                }
                else if (j == hostVirtId) {
                    mbxUserIdx = 2 << 8;
                    if (i == dsp2VirtId) {
                        subMbxIdx = 1;
                    }
                    else if (i == ipu2_0VirtId) {
                        subMbxIdx = 4;
                    }
                    else if (i == ipu2_1VirtId) {
                        subMbxIdx = 9;
                    }
                }
                else if (j == ipu2_1VirtId) {
                    mbxUserIdx = 3 << 8;
                    if (i == dsp2VirtId) {
                        subMbxIdx = 2;
                    }
                    else if (i == hostVirtId) {
                        subMbxIdx = 7;
                    }
                }

                tableEntry = mbxBaseAddrIdx | mbxUserIdx | subMbxIdx;
                InterruptCore.mailboxTable[index] = tableEntry;
                continue;
            }

            /*  System Mailbox 7
             *  This is for communication between DSP1/IPU1_0<->DSP2/IPU2-0
             *  but not DSP1<->IPU1-0 or DSP<->IPU2-0. Those communication
             *  lines have already been established above.
             */
            if (((i == dsp1VirtId) || (i == dsp2VirtId)     ||
                (i == ipu1_0VirtId) || (i == ipu2_0VirtId)) &&
                ((j == dsp1VirtId) || (j == dsp2VirtId)     ||
                (j == ipu1_0VirtId) || (j == ipu2_0VirtId))) {

                mbxBaseAddrIdx = ((InterruptCore.NUM_EVES * 3) +
                                  SYS_MBX7_OFFSET) << 16;

                /* DSP1/IPU1 and DSP2/IPU2 already established previously */
                if (i == j) {
                    continue;
                }
                if ((i == dsp1VirtId && j == ipu1_0VirtId) ||
                    (i == dsp2VirtId && j == ipu2_0VirtId)) {
                    continue;
                }

                if (j == dsp1VirtId) {
                    mbxUserIdx = 0;
                    if (i == dsp2VirtId) {
                        subMbxIdx = 2;
                    }
                    else if (i == ipu2_0VirtId) {
                        subMbxIdx = 6;
                    }
                }
                else if (j == dsp2VirtId) {
                    mbxUserIdx = 1 << 8;
                    if (i == dsp1VirtId) {
                        subMbxIdx = 0;
                    }
                    else if (i == ipu1_0VirtId) {
                        subMbxIdx = 4;
                    }
                }
                else if (j == ipu1_0VirtId) {
                    mbxUserIdx = 2 << 8;
                    if (i == dsp2VirtId) {
                        subMbxIdx = 3;
                    }
                    else if (i == ipu2_0VirtId) {
                        subMbxIdx = 7;
                    }
                }
                else if (j == ipu2_0VirtId) {
                    mbxUserIdx = 3 << 8;
                    if (i == dsp1VirtId) {
                        subMbxIdx = 1;
                    }
                    else if (i == ipu1_0VirtId) {
                        subMbxIdx = 5;
                    }
                }

                tableEntry = mbxBaseAddrIdx | mbxUserIdx | subMbxIdx;
                InterruptCore.mailboxTable[index] = tableEntry;
            }

            /*  System Mailbox 8
             *  This is required only if one of the IPU is running
             *  NON-SMP BIOS. This is for the second core of
             *  IPU1-1<->DSP2/IPU2 or second core of IPU2-1<->DSP1/IPU1.
             */
            if (((i == dsp1VirtId) || (i == dsp2VirtId) ||
                (i == ipu1_0VirtId) || (i == ipu1_1VirtId) ||
                (i == ipu2_0VirtId) || (i == ipu2_1VirtId)) &&
                ((j == dsp1VirtId) || (j == dsp2VirtId) ||
                (j == ipu1_0VirtId) || (j == ipu1_1VirtId) ||
                (j == ipu2_0VirtId) || (j == ipu2_1VirtId))) {

                mbxBaseAddrIdx = ((InterruptCore.NUM_EVES * 3) +
                                  SYS_MBX8_OFFSET) << 16;

                /* Don't set any previously established lines */
                if (i == j) {
                    continue;
                }

                if ((i == dsp1VirtId) && (j != ipu2_1VirtId)) {
                    continue;
                }

                if ((i == dsp2VirtId) && (j != ipu1_1VirtId)) {
                    continue;
                }

                if ((i == ipu1_0VirtId) && (j != ipu2_1VirtId)) {
                    continue;
                }

                if ((i == ipu1_1VirtId) &&
                    ((j != dsp2VirtId) && (j != ipu2_0VirtId))) {
                    continue;
                }

                if ((i == ipu2_0VirtId) && (j != ipu1_1VirtId)) {
                    continue;
                }

                if ((i == ipu2_1VirtId) &&
                    ((j != dsp1VirtId) && (j != ipu1_0VirtId))) {
                    continue;
                }

                /* Set new communication lines */
                if (j == dsp1VirtId) {
                    /* only required when IPU2 is NON-SMP BIOS */
                    mbxUserIdx = 0;
                    if (i == ipu2_1VirtId) {
                        subMbxIdx = 2;
                    }
                }
                else if (j == dsp2VirtId) {
                    /* only required when IPU1 is NON-SMP BIOS */
                    mbxUserIdx = 1 << 8;
                    if (i == ipu1_1VirtId) {
                        subMbxIdx = 1;
                    }
                }
                else if (j == ipu1_0VirtId) {
                    /* only required when IPU2 is NON-SMP BIOS */
                    mbxUserIdx = 2 << 8;
                    if (i == ipu2_1VirtId) {
                        subMbxIdx = 3;
                    }
                }
                else if (j == ipu1_1VirtId) {
                    /* only required when IPU1 is NON-SMP BIOS */
                    mbxUserIdx = 2 << 8;
                    if (i == dsp2VirtId) {
                        subMbxIdx = 0;
                    }
                    else if (i == ipu2_0VirtId) {
                        subMbxIdx = 3;
                    }
                }
                else if (j == ipu2_0VirtId) {
                    /* only required when IPU1 is NON-SMP BIOS */
                    mbxUserIdx = 3 << 8;
                    if (i == ipu1_1VirtId) {
                        subMbxIdx = 2;
                    }
                }
                else if (j == ipu2_1VirtId) {
                    /* only required when IPU2 is NON-SMP BIOS */
                    mbxUserIdx = 3 << 8;
                    if (i == dsp1VirtId) {
                        subMbxIdx = 0;
                    }
                    else if (i == ipu1_0VirtId) {
                        subMbxIdx = 1;
                    }
                }

                tableEntry = mbxBaseAddrIdx | mbxUserIdx | subMbxIdx;
                InterruptCore.mailboxTable[index] = tableEntry;
            }
        }
    }

    /* added mailbox for NotifyDriverMbx support */
    index = (ipu1_0VirtId * InterruptCore.NUM_CORES) + ipu1_1VirtId;
    InterruptCore.mailboxTable[index] = 15 << 16 | 2 << 8 | 4;

    index = (ipu1_1VirtId * InterruptCore.NUM_CORES) + ipu1_0VirtId;
    InterruptCore.mailboxTable[index] = 14 << 16 | 2 << 8 | 8;
}
