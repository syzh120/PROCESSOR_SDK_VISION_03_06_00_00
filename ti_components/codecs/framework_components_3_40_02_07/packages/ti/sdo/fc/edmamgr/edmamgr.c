/*
 * Copyright (c) 2013-2016, Texas Instruments Incorporated
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
#include <xdc/std.h>
#include <ti/xdais/ires.h>

#include <ti/sdo/fc/rman/rman.h>

#include "edmamgr.h"
#include "edmamgr_heap.h"

#ifndef ECPY_INLINE_ALL
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <ti/sdo/fc/ecpy/ecpy_util.h>
#endif

static IRES_ProtocolRevision _iresEDMA3ChanRevision =
        IRES_EDMA3CHAN_PROTOCOLREVISION_2_0_0;

#define EDMA_MGR_MAX_NUM_CHANNELS     32

EdmaMgr_Channel EdmaMgr_channels[EDMA_MGR_MAX_NUM_CHANNELS];

typedef struct _EdmaMgr_SaveInfo {
  EdmaMgr_Handle               handle;
  int32_t                      numPaRams;
  uint32_t                     optChained;
  IALG_MemRec                  addrTable;
  EdmaMgr_Channel             *chainedChannel;
} EdmaMgr_SaveInfo;

static EdmaMgr_SaveInfo EdmaMgr_saveInfo[EDMA_MGR_MAX_NUM_CHANNELS];

extern __FAR__ int32_t *ti_sdo_fc_edmamgr_region2Instance;
extern __FAR__ EDMA3_GblConfigParams *ti_sdo_fc_edmamgr_edma3GblConfigParams;
extern __FAR__ EDMA3_InstanceInitConfig *ti_sdo_fc_edmamgr_edma3RegionConfig;

/*********************************************************************************
 * FUNCTION PURPOSE: Init EdmaMgr resources
 *********************************************************************************
  DESCRIPTION:      This function initializes RMAN resouces

  Parameters :      Inputs: proc_id          : core ID
                            edma_config      : pointer to EDMA3 instance init
                                               configuration
                    Output: EdmaMgr_SUCCESS if initialization successful;
                            Error code otherwise
 *********************************************************************************/
int32_t EdmaMgr_init(int32_t proc_id, void *edma_config)
{
    IRES_Status ires_status;
    uint32_t edmaInstanceId;
    int32_t i;

    if (proc_id < 0 || proc_id >= EDMA3_MAX_REGIONS) {
        return EdmaMgr_ERROR_INVARG;
    }

    if (ti_sdo_fc_edmamgr_region2Instance != NULL) {
        edmaInstanceId = ti_sdo_fc_edmamgr_region2Instance[proc_id];

        if (ti_sdo_fc_edmamgr_edma3GblConfigParams != NULL) {
            EDMA3_PARAMS.globalConfig =
                    (EDMA3_GblConfigParams *) &
                    ti_sdo_fc_edmamgr_edma3GblConfigParams[edmaInstanceId];
        }
        else if (EDMA3_PARAMS.globalConfig == NULL) {
            return EdmaMgr_ERROR_INVCFG;
        }

        if (edma_config != NULL) {
            EDMA3_InstanceInitConfig *custom_config =
                    (EDMA3_InstanceInitConfig *) edma_config;

            EDMA3_PARAMS.regionConfig =
                    (EDMA3_InstanceInitConfig *) &
                    custom_config[EDMA3_MAX_REGIONS * edmaInstanceId + proc_id];
        }
        else if (ti_sdo_fc_edmamgr_edma3RegionConfig != NULL) {
            EDMA3_PARAMS.regionConfig =
                    (EDMA3_InstanceInitConfig *) &
                    ti_sdo_fc_edmamgr_edma3RegionConfig[EDMA3_MAX_REGIONS *
                    edmaInstanceId + proc_id];
        }
        else if (EDMA3_PARAMS.regionConfig == NULL) {
            return EdmaMgr_ERROR_INVCFG;
        }
    }
    else if (EDMA3_PARAMS.globalConfig || EDMA3_PARAMS.regionConfig == NULL) {
        return EdmaMgr_ERROR_INVCFG;
    }

    EdmaMgr_heap_create();

    RMAN_PARAMS.allocFxn = &EdmaMgr_heap_alloc;
    RMAN_PARAMS.freeFxn = &EdmaMgr_heap_free;
    EDMA3_PARAMS.allocFxn = &EdmaMgr_heap_alloc;
    EDMA3_PARAMS.freeFxn = &EdmaMgr_heap_free;
    ECPY_CFG_PARAMS.allocFxn = &EdmaMgr_heap_alloc;
    ECPY_CFG_PARAMS.freeFxn = &EdmaMgr_heap_free;

    /* specify EDMA instance ID */
    ti_sdo_fc_edma3_EDMA3_physicalId = edmaInstanceId;

    /* RMAN init */
    ires_status = RMAN_init();

    if (IRES_OK != ires_status) {
        return EdmaMgr_ERROR_RMANINIT;
    }

    memset(EdmaMgr_channels, 0,
            EDMA_MGR_MAX_NUM_CHANNELS * sizeof(EdmaMgr_Channel));
    for (i = 0; i < EDMA_MGR_MAX_NUM_CHANNELS; i++) {
        EdmaMgr_channels[i].edmaArgs.size = sizeof(IRES_EDMA3CHAN_ProtocolArgs);
        EdmaMgr_channels[i].edmaArgs.mode = IRES_PERSISTENT;
        EdmaMgr_channels[i].edmaArgs.numTccs = 1;
        EdmaMgr_channels[i].edmaArgs.paRamIndex = IRES_EDMA3CHAN_PARAM_ANY;
        EdmaMgr_channels[i].edmaArgs.tccIndex = IRES_EDMA3CHAN_TCC_ANY;
        EdmaMgr_channels[i].edmaArgs.qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
        EdmaMgr_channels[i].edmaArgs.edmaChan = IRES_EDMA3CHAN_EDMACHAN_ANY;
        EdmaMgr_channels[i].edmaArgs.contiguousAllocation = TRUE;
        EdmaMgr_channels[i].edmaArgs.shadowPaRamsAllocation = FALSE;
        EdmaMgr_channels[i].edmaArgs.numPaRams = 0;
    }
    return EdmaMgr_SUCCESS;
}

/*********************************************************************************
 * FUNCTION PURPOSE: Allocate EdmaMgr handle
 *********************************************************************************
  DESCRIPTION:      This function allocates an EDMA channel

  Parameters :      Inputs: max_linked_transfer  : maximum number of linked
                                                   transfers required for the
                                                   channel.

                    Output: Valid EdmaMgr handle on success;
                            NULL handle if there is an error.
 *********************************************************************************/
EdmaMgr_Handle EdmaMgr_alloc(int32_t max_linked_transfers)
{
    IRES_ResourceDescriptor resDesc;
    IRES_Status ires_status;
    int32_t scratchId = -1;
    int32_t i;

    /* Find free channel */
    for (i = 0; i < EDMA_MGR_MAX_NUM_CHANNELS; i++)
        if (EdmaMgr_channels[i].edmaArgs.numPaRams == 0)
            break;

    if (i >= EDMA_MGR_MAX_NUM_CHANNELS)
        return ((EdmaMgr_Handle)NULL);

    EdmaMgr_channels[i].edmaArgs.numPaRams = max_linked_transfers;

    /* Prepare IRES resource descriptor */
    resDesc.resourceName = IRES_EDMA3CHAN_PROTOCOLNAME;
    resDesc.revision = &_iresEDMA3ChanRevision;
    resDesc.protocolArgs = (IRES_ProtocolArgs *)&(EdmaMgr_channels[i].edmaArgs);
    resDesc.handle = (IRES_Handle)EdmaMgr_channels[i].edmaHandle;

    /* Allocate EDMA Resources */
    ires_status =
            RMAN_allocateResources((Int)EdmaMgr_channels, &resDesc, 1,
            scratchId);
    if (ires_status != IRES_OK) {
        EdmaMgr_channels[i].edmaArgs.numPaRams = 0;
        return ((EdmaMgr_Handle)NULL);
    }
    EdmaMgr_channels[i].edmaHandle = (IRES_EDMA3CHAN_Handle) resDesc.handle;

    /* Create ECPY handle */
    EdmaMgr_channels[i].ecpyHandle =
            ECPY_createHandle((IRES_EDMA3CHAN2_Handle)resDesc.handle,
            (IALG_Handle)&EdmaMgr_channels[i]);
    if (EdmaMgr_channels[i].ecpyHandle == NULL) {
        RMAN_freeAllocatedResources((Int)EdmaMgr_channels, &resDesc, 1,
                scratchId);
        EdmaMgr_channels[i].edmaHandle = NULL;
        EdmaMgr_channels[i].edmaArgs.numPaRams = 0;
        return ((EdmaMgr_Handle)NULL);
    }
    EdmaMgr_channels[i].xferPending = FALSE;

    /* HW assign */
    ECPY_activate(EdmaMgr_channels[i].ecpyHandle);
    ECPY_setEarlyCompletionMode(EdmaMgr_channels[i].ecpyHandle, FALSE);

    return ((EdmaMgr_Handle)&EdmaMgr_channels[i]);
}



/*********************************************************************************
 * FUNCTION PURPOSE: Allocate EdmaMgr handle
 *********************************************************************************
  DESCRIPTION:      Get buffer requirements for a large channel.

  Parameters :      Inputs: cfg    : Configuration for a large channel.

                    Output: memTab : Memory requirements.

                    Output: EdmaMgr_SUCCESS if successful;
                            Error code otherwise
 *********************************************************************************/
int32_t EdmaMgr_getSizesLarge( EdmaMgr_ConfigLarge *cfg, IALG_MemRec memTab[])
{
  /* Validate configuration. */
  if ( cfg->max_num_lines <= 0 )
    return EdmaMgr_ERROR_INVCFG;

  memTab[0].size      = cfg->max_num_lines * sizeof(uint32_t);
  memTab[0].alignment = sizeof(uint32_t);
  memTab[0].space     = IALG_DARAM0;
  memTab[0].attrs     = IALG_PERSIST;
  memTab[0].base      = NULL;

  return EdmaMgr_SUCCESS;
}


/*********************************************************************************
 * FUNCTION PURPOSE: Allocate EdmaMgr handle for Large strides
 *********************************************************************************
  DESCRIPTION:      This function allocates an EDMA channel for large transfers
                    where the pitch is larger than the HW limit of 16 bits.

                    Since these transfers excede the HW limits of a single PaRAM,
                    two channels must be chained, and "src" or "dst" addresses
                    will be stored in a look-up table.

                    The first EdmaMgr channel will read these addresses from the
                    table, and transfer them to the PaRAM of the second channel.
                    Once this transfer is complete, chaining will trigger the
                    transfer of the actual data in the second channel. Once the
                    second channel completes the transfer, chaining will trigger
                    the first channel to read the next address in the table.
                    This will continue until the entire data is transfered.

  Parameters :      Inputs: cfg            : Configuration for a large channel.

                            memTab         : Buffer requirements along with
                                             allocated buffers for a large
                                             channel.

                    Output: Valid EdmaMgr handle on success;
                            NULL handle if there is an error.
 *********************************************************************************/
EdmaMgr_Handle EdmaMgr_allocLarge( EdmaMgr_ConfigLarge *cfg, IALG_MemRec memTab[])
{
    EdmaMgr_Handle   h1, h2;
    EdmaMgr_Channel  *chan1, *chan2;
    uint32_t         tcc1, tcc2;

    if ( cfg->max_num_lines * sizeof(uint32_t) > memTab[0].size )
      return ((EdmaMgr_Handle)NULL);

    if ( memTab[0].base == NULL )
      return ((EdmaMgr_Handle)NULL);

    /*
     *  Allocate a basic EdmaMgr channel.
     *
     *  This channel will be responsible for transferring addresses from the
     *  lookup table to the PaRAM of the second channel.
     */
    if ( (h1 = EdmaMgr_alloc(1)) == NULL )
        return ((EdmaMgr_Handle)NULL);

    /*
     *  Allocate a basic EdmaMgr channel.
     *
     *  This channel will be responsible for transferring the data of interest,
     *  line by line.
     */
    if ( (h2 = EdmaMgr_alloc(1)) == NULL ) {
        EdmaMgr_free(h1);
        return ((EdmaMgr_Handle)NULL);
    }

    chan1 = (EdmaMgr_Channel *)h1;
    chan2 = (EdmaMgr_Channel *)h2;

    /* Copy over memory for the address lookup table. */
    memcpy( &chan1->addrTable, &memTab[0], sizeof(IALG_MemRec));

    /* Obtain each channel's TCC so that chaining can be configured, */
    tcc1 = chan1->edmaHandle->assignedTccIndices[0];
    tcc2 = chan2->edmaHandle->assignedTccIndices[0];

    /* PaRAM OPT settings for first in chain. */
    /* This TCC will load the second in the chain with the SRC address from a table in memory */
    chan1->optChained = ECPY_PARAMOPTS_TCCBITS(tcc2) |   /* Chain to the second channel's TCC */
                        ECPY_PARAMOPTS_ITCCHEN       |   /* Chain on intermediate transfers (after each address is loaded to the second channel). */
                        ECPY_PARAMOPTS_TCCHEN        |   /* Chain on final transfer (after last address is loaded). */
                        ECPY_PARAMOPTS_TCC_INTEN     |   /* Enable interrupt on final transfer (Sets IPR bit after final transfer). */
                        ECPY_PARAMOPTS_ABSYNC;           /* Sync transfer chaining on A and B CNTs. */

    /* PaRAM OPT settings for second in chain. */
    /* This TCC will transfer the actual data of interest. */
    chan2->optChained = ECPY_PARAMOPTS_TCCBITS(tcc1) |   /* Chain to the first channel. */
                        ECPY_PARAMOPTS_ITCCHEN       |   /* Chain in intermediate transfers (to obtain next address from table). */
                        ECPY_PARAMOPTS_TCC_INTEN     |   /* Enable interrupt on final transfer (Sets IPR bit after final transfer). */
                        ECPY_PARAMOPTS_ABSYNC;           /* Sync transfer chaining on A and B CNTs. */

    chan1->chainedChannel = chan2;

    return ((EdmaMgr_Handle)chan1);
}

/*********************************************************************************
 * FUNCTION PURPOSE: Free EdmaMgr handle
 *********************************************************************************
  DESCRIPTION:      This function frees an EDMA channel

  Parameters :      Inputs: h   : EdmaMgr handle

                    Output: EdmaMgr_SUCCESS if free is successful;
                            Error code otherwise.
 *********************************************************************************/
int32_t EdmaMgr_free(EdmaMgr_Handle h)
{
    EdmaMgr_Channel *chan = (EdmaMgr_Channel *)h;
    IRES_ResourceDescriptor resDesc;
    IRES_Status ires_status;
    int32_t scratchId = -1;
    int32_t i, ret_val = EdmaMgr_SUCCESS;

    /* Make sure all transfers have completed */
    EdmaMgr_wait(h);

    /* While loop for freeing chained channels. */
    while ( chan != NULL ) {
      EdmaMgr_Channel *chainedChan = chan->chainedChannel;

      /* Verify that this is a valid handle? */
      for (i = 0; i < EDMA_MGR_MAX_NUM_CHANNELS; i++)
          if (chan == &EdmaMgr_channels[i])
              break;

      if (i >= EDMA_MGR_MAX_NUM_CHANNELS)
          return EdmaMgr_ERROR_INVHANDLE;

      /* Prepare IRES resource descriptor */
      resDesc.resourceName = IRES_EDMA3CHAN_PROTOCOLNAME;
      resDesc.revision = &_iresEDMA3ChanRevision;
      resDesc.protocolArgs = (IRES_ProtocolArgs *)&(chan->edmaArgs);
      resDesc.handle = (IRES_Handle)chan->edmaHandle;

      ECPY_deleteHandle(chan->ecpyHandle);

      ires_status =
              RMAN_freeAllocatedResources((Int)EdmaMgr_channels, &resDesc, 1,
              scratchId);
      if (ires_status != IRES_OK) {
          ret_val = EdmaMgr_ERROR_FREE;
      }

      chan->ecpyHandle = NULL;
      chan->edmaHandle = NULL;
      chan->xferPending = FALSE;

      chan->edmaArgs.numPaRams = 0;
      chan->chainedChannel = NULL;

      if ( chan->addrTable.base ) {
          chan->addrTable.base = NULL;
          chan->addrTable.size = 0;
      }

      chan = chainedChan;
    }

    return ret_val;
}


/*********************************************************************************
 * FUNCTION PURPOSE: Free EdmaMgr HW resources
 *********************************************************************************
  DESCRIPTION:      This function frees HW resources for all EDMA channels

  Parameters :      Inputs:

                    Output: EdmaMgr_SUCCESS if free is successful;
                            Error code otherwise.
 *********************************************************************************/
int32_t EdmaMgr_hwFreeAll()
{
    int32_t i, ret_val = EdmaMgr_SUCCESS;
    EdmaMgr_Channel *chan;
    EdmaMgr_SaveInfo *saveInfo;
    IRES_Status ires_status;

    memset(EdmaMgr_saveInfo, 0, sizeof(EdmaMgr_SaveInfo)*EDMA_MGR_MAX_NUM_CHANNELS);

    for (i = 0; i < EDMA_MGR_MAX_NUM_CHANNELS; i++) {
        chan = &EdmaMgr_channels[i];

        /* Save info for recovering the EDMA channels */
        if (chan->edmaArgs.numPaRams > 0) {

            saveInfo = &EdmaMgr_saveInfo[i];

            saveInfo->numPaRams = chan->edmaArgs.numPaRams;

            saveInfo->handle = (EdmaMgr_Handle) chan;

            /* Save info for a large channel*/
            if (chan->chainedChannel != NULL) {
                saveInfo->chainedChannel = chan->chainedChannel;
            }

            if (chan->addrTable.base != NULL) {
                memcpy(&saveInfo->addrTable, &chan->addrTable, sizeof(IALG_MemRec));
            }

            saveInfo->optChained = chan->optChained;

            /* Free EdmaMgr channel */
            ret_val = EdmaMgr_free((EdmaMgr_Handle)chan);
            if (ret_val != EdmaMgr_SUCCESS) {
                return ret_val;
            }
        }
    }

    return ret_val;
}

/*********************************************************************************
 * FUNCTION PURPOSE: Restore EdmaMgr HW resources
 *********************************************************************************
  DESCRIPTION:      This function restores HW resources for all EDMA channels

  Parameters :      Inputs:

                    Output: EdmaMgr_SUCCESS if restore is successful;
                            Error code otherwise.
 *********************************************************************************/
int32_t EdmaMgr_hwAllocAll()
{
    int32_t i, ret_val = EdmaMgr_SUCCESS;
    EdmaMgr_Channel *chan;
    EdmaMgr_SaveInfo *saveInfo;
    EdmaMgr_Handle   h;
    IRES_Status ires_status;

    for (i = 0; i < EDMA_MGR_MAX_NUM_CHANNELS; i++) {
        saveInfo = &EdmaMgr_saveInfo[i];

        /* Restore an EDMA channel */
        if (saveInfo->numPaRams > 0) {
            do {
                h = EdmaMgr_alloc(saveInfo->numPaRams);
                if (h == saveInfo->handle) {
                    break;
                } else {
                    EdmaMgr_free (h);
                }
            } while (1);

            chan = (EdmaMgr_Channel *)h;

            /* Restore configurations for a large channel */
            if (&saveInfo->addrTable.base != NULL) {
                memcpy( &chan->addrTable, &saveInfo->addrTable, sizeof(IALG_MemRec));
            }

            chan->optChained = saveInfo->optChained;

            if (saveInfo->chainedChannel) {
                chan->chainedChannel = saveInfo->chainedChannel;
            }
        }
    }

    return ret_val;
}
