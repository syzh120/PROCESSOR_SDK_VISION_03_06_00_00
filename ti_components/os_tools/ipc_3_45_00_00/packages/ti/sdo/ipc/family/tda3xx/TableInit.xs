/*
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com
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
 */

/* Virtual Index Assignment (invariant)
 *     DSP1:        0
 *     DSP2:        1
 *     IPU1,IPU1-0: 2
 *     IPU1-1:      3
 *     EVE1:        4
 */
var dsp1VirtId    = 0;
var dsp2VirtId    = 1;
var ipu1_0VirtId  = 2;
var ipu1_1VirtId  = 3;
var eve1VirtId    = 4;


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
    mod.dsp1ProcId   = MultiProc.getIdMeta("DSP1");
    mod.dsp2ProcId   = MultiProc.getIdMeta("DSP2");
    mod.ipu1_0ProcId = MultiProc.getIdMeta("IPU1");  /* assume smp */
    mod.ipu1_1ProcId = MultiProc.getIdMeta("IPU1-1");

    if (mod.eve1ProcId != MultiProc.INVALIDID) {
        mod.procIdTable[mod.eve1ProcId] = eve1VirtId;
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
}

/*
 *  ======== idx ========
 *  Compute the table index from source and destination input
 */
function idx(mod, src, dst)
{
    return ((src * mod.NUM_CORES) + dst);
}

/*
 *  ======== enc ========
 *  Encode the table entry from input values
 */
function enc(mbxIdx, user, fifo)
{
    return ((mbxIdx << 16) | (user << 8) | fifo);
}

/*
 * Function to generate mailbox table
 */
function generateTable(mod)
{
    /* Each entry in the mailbox table stores 3 indexes.
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

    /*  idx(mod, src, dst) - compute table index
     *      src: source core virtual index
     *      dst: destination core virtual index
     *
     *  enc(mbxIdx, user, fifo) - encode mailbox table entry
     *      mbxIdx: mailbox index
     *          0: EVE1 Mailbox 0
     *          1: EVE1 Mailbox 1
     *          2: System Mailbox 2
     *      user: mailbox user interrupt
     *      fifo: mailbox fifo number
     */

    mod.mailboxTable[idx(mod,0,0)] = -1;            /* DSP1 -> DSP1 */
    mod.mailboxTable[idx(mod,0,1)] = enc(2,1,3);    /* DSP1 -> DSP2 */
    mod.mailboxTable[idx(mod,0,2)] = enc(2,2,6);    /* DSP1 -> IPU1-0 */
    mod.mailboxTable[idx(mod,0,3)] = enc(2,3,9);    /* DSP1 -> IPU1-1 */
    mod.mailboxTable[idx(mod,0,4)] = enc(0,0,1);    /* DSP1 -> EVE1 */

    mod.mailboxTable[idx(mod,1,0)] = enc(2,0,0);    /* DSP2 -> DSP1 */
    mod.mailboxTable[idx(mod,1,1)] = -1;            /* DSP2 -> DSP2 */
    mod.mailboxTable[idx(mod,1,2)] = enc(2,2,7);    /* DSP2 -> IPU1-0 */
    mod.mailboxTable[idx(mod,1,3)] = enc(2,3,10);   /* DSP2 -> IPU1-1 */
    mod.mailboxTable[idx(mod,1,4)] = enc(0,0,3);    /* DSP2 -> EVE1 */

    mod.mailboxTable[idx(mod,2,0)] = enc(2,0,1);    /* IPU1-0 -> DSP1 */
    mod.mailboxTable[idx(mod,2,1)] = enc(2,1,4);    /* IPU1-0 -> DSP2 */
    mod.mailboxTable[idx(mod,2,2)] = -1;            /* IPU1-0 -> IPU1-0 */
    mod.mailboxTable[idx(mod,2,3)] = enc(2,3,11);   /* IPU1-0 -> IPU1-1 */
    mod.mailboxTable[idx(mod,2,4)] = enc(0,0,5);    /* IPU1-0 -> EVE1 */

    mod.mailboxTable[idx(mod,3,0)] = enc(2,0,2);    /* IPU1-1 -> DSP1 */
    mod.mailboxTable[idx(mod,3,1)] = enc(2,1,5);    /* IPU1-1 -> DSP2 */
    mod.mailboxTable[idx(mod,3,2)] = enc(2,2,8);    /* IPU1-1 -> IPU1-0 */
    mod.mailboxTable[idx(mod,3,3)] = -1;            /* IPU1-1 -> IPU1-1 */
    mod.mailboxTable[idx(mod,3,4)] = enc(1,0,1);    /* IPU1-1 -> EVE1 */

    mod.mailboxTable[idx(mod,4,0)] = enc(0,1,0);    /* EVE1 -> DSP1 */
    mod.mailboxTable[idx(mod,4,1)] = enc(0,2,2);    /* EVE1 -> DSP2 */
    mod.mailboxTable[idx(mod,4,2)] = enc(0,3,4);    /* EVE1 -> IPU1-0 */
    mod.mailboxTable[idx(mod,4,3)] = enc(1,1,0);    /* EVE1 -> IPU1-1 */
    mod.mailboxTable[idx(mod,4,4)] = -1;            /* EVE1 -> EVE1 */
}
