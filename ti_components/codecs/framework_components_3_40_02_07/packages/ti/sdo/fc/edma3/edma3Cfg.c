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
 *  ======== edma3Config.c ========
 *  Creates an EDMA3_PARAMS structure to be used by non-RTSC build,
 */

#include <xdc/std.h>
#include <ti/sdo/fc/edma3/edma3_config.h>


#define EDMA3_PARAMS_REGION     1
#define EDMA3_PARAMS_GLOBALINIT FALSE
#define EDMA3_PARAMS_ALLOCFXN   NULL
#define EDMA3_PARAMS_FREEFXN    NULL
#define EDMA3_PARAMS_GLOBALCONFIG NULL
#define EDMA3_PARAMS_REGIONCONFIG NULL
#define EDMA3_PARAMS_NUMGROUPS 0
#define EDMA3_PARAMS_CONTIGPARAMS TRUE

__FAR__ Uns ti_sdo_fc_edma3_EDMA3_physicalId = 0;

/*
 * Structures to provide global/regional configuration for devices that are
 * supported by FC but not natively by EDMA3 LLD.
 * Set these to one of the structures defined in edma3lld_cfg.h or to custom
 * configuration.
 */
__FAR__ EDMA3_GblConfigParams * ti_sdo_fc_edma3_Settings_globalConfig = NULL;

__FAR__ EDMA3_InstanceInitConfig * ti_sdo_fc_edma3_Settings_regionConfig = NULL;

/*
 * EDMA3_PARAMS structure can be over-ridden with actual values
 */
__FAR__ EDMA3_Params EDMA3_PARAMS = {

    EDMA3_PARAMS_REGION,

    EDMA3_PARAMS_GLOBALINIT,

    EDMA3_PARAMS_ALLOCFXN,

    EDMA3_PARAMS_FREEFXN,

    EDMA3_PARAMS_GLOBALCONFIG,

    EDMA3_PARAMS_REGIONCONFIG,

    EDMA3_PARAMS_NUMGROUPS,

    EDMA3_PARAMS_CONTIGPARAMS
};

/* Array of maximum scratch paRam requirements of all groups */
__FAR__ Uns EDMA3_paRamScratchSizes[EDMA3_MAXGROUPS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* Array of maximum scratch edma channel requirements of all groups */
__FAR__ Uns EDMA3_edmaChanScratchSizes[EDMA3_MAXGROUPS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};

/* Array of maximum scratch qdma channel requirements of all groups */
__FAR__ Uns EDMA3_qdmaChanScratchSizes[EDMA3_MAXGROUPS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* Array of maximum scratch tcc requirements of all groups */
__FAR__ Uns EDMA3_tccScratchSizes[EDMA3_MAXGROUPS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/*
 * Array of EDMA3 LLD RM configuration structure for all the scratch groups
 */
__FAR__ EDMA3_InstanceInitConfig EDMA3_scratchResourceConfig[EDMA3_MAXGROUPS];

#ifdef _xdc_target__os_Linux
UInt32 _EDMA3_ipcKeyBase = 0x33414D44;

__FAR__ Int ti_sdo_fc_edma3_EDMA3_MAXEDMAREQUESTS = 64;

#endif
/*
 * TC and Queue setup data structures
 */
__FAR__ Bool ti_sdo_fc_edma3_Settings_eventQueueSetup = FALSE;

__FAR__ Int ti_sdo_fc_edma3_Settings_queueTCMap[EDMA3_MAX_TC] = { 0, 0, 0, 0,
        0, 0, 0, 0};

__FAR__ Int ti_sdo_fc_edma3_Settings_queuePriority[EDMA3_MAX_TC] = { 0, 0, 0, 0,
        0, 0, 0, 0};

__FAR__ Int ti_sdo_fc_edma3_Settings_memTypeTCMap[8] = {0, 0, 0, 0, 0,
        0, 0, 0};

__FAR__ Uns ti_sdo_fc_edma3_Settings_defaultQ = 0x0;
