/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/** ===========================================================================
* @file   dma_resource_allocator.c
*
* @path   $(STARTERWAREPATH)/drivers/src/
*
* @desc   This  File contains functions that implement dma_resource manager
*
* =====================================================================
*
* Use of this software is controlled by the terms and conditions found
*/

/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/*  These are the include files that are needed for edma/qdma.           */
/*-----------------------------------------------------------------------*/
#include "dma_resource_allocator.h"
#include "edmacc_config.h"

/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <string.h>
/*#pragma RESET_MISRA ("required")*/

/** ========================================================
 *  @name   DMA_globalStateStruct
 *
 *  @desc   This structure stores the state of EDMA resources in terms of
 *          number of EDMA channels, number of QDMA channels and number
 *          of param sets
 *
 *  @field  edmaChannelState
 *              Stores the state of each EDMA channel. A value of -1 means the channel
 *              is free
 *
 *  @field  qdmaChannelState[]
 *              Stores the state of each QDMA channel. A value of -1 means the channel
 *              is free
 *
 *  @field  tccState[]
 *              Stores the state of each Transfer Completion Code. A value of -1 means
 *              the TCC is free
 *
 *  @field  paramSetState[]
 *              Stores the state of each paramset. A value of -1 means the param set
 *              is free
 *
 *
 *  ===============================================================
 */

typedef struct dma_globalStateStruct
{
    int8_t edmaChannelState[NUM_EDMA_CHANNELS];
    int8_t qdmaChannelState[NUM_QDMA_CHANNELS];
    int8_t tccState[EDMA_NUM_TCCS];
    int8_t paramSetState[EDMA_NUM_PARAMS];
} DMA_globalStateStruct;

/** ====================================================
 *  @name   DMA_resourceStatus
 *
 *  @desc   Describes the status of EDMA resources
 *
 *  @field  DMA_RESOURCE_FREE
 *             Indicates a particular EDMA resource is FREE
 *
 *  @field  DMA_RESOURCE_OCCUPIED
 *             Indicates a particular EDMA resource is OCCUPIED
 *  ====================================================
 */
typedef enum dma_resourceStatus
{
    DMA_RESOURCE_FREE = 0,
    DMA_RESOURCE_OCCUPIED = 1
}DMA_resourceStatus;

/* Global Structure to keep track of EDMA resources */
#if defined(HOST_EMULATION) || defined(_TMS320C6X)

static DMA_globalStateStruct gDmaResourceState;
static EDMA3_RM_Handle gEdma3RmHandle = NULL;

#else
#ifndef _TMS320C6X
near static DMA_globalStateStruct gDmaResourceState;
near static EDMA3_RM_Handle gEdma3RmHandle = NULL;
#else
static DMA_globalStateStruct gDmaResourceState;
static EDMA3_RM_Handle gEdma3RmHandle = NULL;
#endif
#endif

/* Declaration of local Functions : Needed for Misra C */
static int32_t resourceAllocator_allocateValidChannel(uint8_t dmaAttr , uint32_t * validChannel);
static int32_t resourceAllocator_allocateValidParamSet(uint32_t numParam,
                uint32_t * validParamSet );
static int32_t resourceAllocator_allocateValidTcc(uint32_t * validTcc);


/* ==================================================
 *  @func   resourceAllocator_allocateValidChannel
 *
 *  @desc   This is a local function for allocating a FREE
 *          available channel
 *
 *
 *  @modif    This function modifies validChannel
 *
 *  @inputs   This function takes following Inputs
 *              dmaAttr :
 *                  DMA attribute for the channel ( Wethers its DMA or QDMA
 *                  channel. For valid values refer to DMA_chanAttr enum
 *
 *  @outputs
 *              validChannel :
 *                  Allocated channel Number
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
static int32_t resourceAllocator_allocateValidChannel(uint8_t dmaAttr , uint32_t * validChannel)
{
    uint32_t channelCnt;
    uint32_t numMaxChannel;
    int8_t   (*channelState)[NUM_EDMA_CHANNELS];
    uint32_t validEntryFound = 0;
    int32_t  status = 0;

    if ( dmaAttr == DMA_CHAN_ATTR_EDMA )
    {
        numMaxChannel   = NUM_EDMA_CHANNELS;
        channelState    = (int8_t (*)[NUM_EDMA_CHANNELS])gDmaResourceState.edmaChannelState;
    }
    else
    {
        numMaxChannel = NUM_QDMA_CHANNELS;
        channelState    = (int8_t (*)[NUM_EDMA_CHANNELS])gDmaResourceState.qdmaChannelState;
    }

    for ( channelCnt = 0 ; channelCnt < numMaxChannel; channelCnt++ )
    {
        if ( (*channelState)[channelCnt] == DMA_RESOURCE_FREE )
        {
            validEntryFound = 1U;
            (*channelState)[channelCnt] = DMA_RESOURCE_OCCUPIED;
            *validChannel = channelCnt;
            break;
        }
    }

    if ( validEntryFound == 0)
    {
        status = -1;
    }

    return status;
}

/* ==================================================
 *  @func   resourceAllocator_allocateValidTcc
 *
 *  @desc   This is a local function for allocating a FREE
 *          available Transfer completion Code (TCC)
 *
 *
 *  @modif    This function modifies validChannel
 *
 *
 *  @outputs
 *              validTcc :
 *                  Allocated TCC Number
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
static int32_t resourceAllocator_allocateValidTcc(uint32_t * validTcc)
{
    uint32_t tccCnt;
    uint32_t validEntryFound = 0;
    int32_t  status = 0;

    for ( tccCnt = 0 ; tccCnt < EDMA_NUM_TCCS ; tccCnt++ )
    {
        if ( gDmaResourceState.tccState[tccCnt] == DMA_RESOURCE_FREE )
        {
            validEntryFound = 1U;
            gDmaResourceState.tccState[tccCnt] = DMA_RESOURCE_OCCUPIED;
            *validTcc = tccCnt;
            break;
        }
    }

    if ( validEntryFound == 0)
    {
        status = -1;
    }

    return status;
}


/* ==================================================
 *  @func   resourceAllocator_allocateValidParamSet
 *
 *  @desc   This is a local function for allocating a group of contigous
 *          free available param sets.
 *
 *
 *  @modif    This function modifies validChannel
 *
 *  @inputs
 *              numParam : Number of contigous param set needed to be allocated
 *
 *  @outputs
 *              validParamSet :
 *                  Number of allocated paramset. It only  returns the starting
 *                  param set number
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
static int32_t resourceAllocator_allocateValidParamSet(uint32_t numParam,
                uint32_t * validParamSet )
{
    uint32_t paramCnt = 0;
    uint32_t requestedParamCnt = 0;
    uint32_t validEntryFound = 0;
    uint32_t validEntry = 0;
    int32_t status = 0;
    int32_t exitFlag = 0;

    while ( paramCnt < EDMA_NUM_PARAMS )
    {
        if ( gDmaResourceState.paramSetState[paramCnt] == DMA_RESOURCE_FREE )
        {
            exitFlag = 0;
            for (requestedParamCnt = 0; requestedParamCnt < numParam; requestedParamCnt++)
            {
                if ( (paramCnt + requestedParamCnt) < EDMA_NUM_PARAMS )
                {
                    if ( gDmaResourceState.paramSetState[paramCnt + requestedParamCnt] !=
                        DMA_RESOURCE_FREE )
                    {
                        exitFlag = 1;
                    }
                }
                else
                {
                    status = -1;
                    exitFlag = 1;
                }
                if ( exitFlag == 1 )
                {
                    break;
                }
            }
            if ( requestedParamCnt == numParam )
            {
                validEntryFound = 1U;
                validEntry = paramCnt;
                break;
            }
            paramCnt = paramCnt + requestedParamCnt;
        }
        else
        {
            paramCnt++;
        }
    }

    if ( validEntryFound == 0)
    {
        status = -1;
    }
    else
    {
        *validParamSet = validEntry;

        for ( paramCnt = 0 ; paramCnt < numParam ; paramCnt++ )
        {
            gDmaResourceState.paramSetState[validEntry + paramCnt] = DMA_RESOURCE_OCCUPIED;

        }
    }

    return status;
}

/* ==================================================
 *  @func     DMA_resourceAllocator_setEdma3RmHandle
 *
 *  @desc     This functions set the resource manager Handle. A value of NULL
 *                is also a valid value for this function. For NUL handle we dont use
 *                EDMA3 LLD for resource allocation
 *
 *  @modif    This function modifies internal global resource structure
 *
 *  @inputs   NONE
 *
 *  @outputs  NONE
 *
 *  @return   NONE
 *
 *  =======================================================
 */
void DMA_resourceAllocator_setEdma3RmHandle(EDMA3_RM_Handle edma3RmHandle)
{
    gEdma3RmHandle = edma3RmHandle;
#ifdef HOST_EMULATION
    gEdma3RmHandle = NULL;
#endif

#ifndef USE_EDMA3LLD
    gEdma3RmHandle = NULL;
#endif

}


/* ==================================================
 *  @func     DMA_resourceAllocator_initResources
 *
 *  @desc     This functions initializes resets all the allocated resources
 *            of EDMA. After this call all the EDMA resources are freshly
 *            available
 *
 *  @modif    This function modifies internal global resource structure
 *
 *  @inputs   NONE
 *
 *  @outputs  NONE
 *
 *  @return   NONE
 *
 *  =======================================================
 */
void DMA_resourceAllocator_initResources(void)

{
    memset(&gDmaResourceState , (int32_t) 0 , sizeof(DMA_globalStateStruct));

    gDmaResourceState.qdmaChannelState[NUM_QDMA_CHANNELS - 1U]  = DMA_RESOURCE_OCCUPIED;
    gDmaResourceState.tccState[EDMA_NUM_TCCS - 1U]              = DMA_RESOURCE_OCCUPIED;
    gDmaResourceState.paramSetState[EDMA_NUM_PARAMS - 1U]       = DMA_RESOURCE_OCCUPIED;
}

/* ==================================================
 *  @func   DMA_resourceAllocator_allocateResources
 *
 *  @desc   This functions allocates EDMA resources for given number of
 *          channels. It also needs to know the EDMA attribute
 *          (EDMA/QDMA channel). How many param sets needed for each
 *          channel and which hardware que each channel should go to.
 *
 *  @modif    This function modifies edmaResources structure
 *
 *  @inputs   This function takes following Inputs
 *              edmaCc :
 *                  Pointer to the address space of EDMA module.
 *
 *              edmaResources :
 *                  Pointer to the resource structure defined in dma_resource.h.
 *                  User is expected to populate following fields of this
 *                  structure as an input and resourceAllocator will  populate
 *                  the remaining fields.
 *                      Input :
 *                          numChannels,
 *
 *                          dmaAttr[for Each channel requested],
 *
 *                          numParam[for Each channel requested], a value of
 *                          -1 means use default value which is 1
 *
 *                          queNo[for Each channel requested], - a value of
 *                          -1 means use default value.
 *
 *                      Output :
 *                          logicalChannelNo[for Each channel requested],
 *
 *                          tccVal[for Each channel requested],
 *
 *                          baseParam[for Each channel requested]
 *
 *  @outputs  edmaResources:
 *                      Contains the resources allocated for all the channels
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */

int32_t DMA_resourceAllocator_allocateResources(
                                            CSL_EdmaccRegsOvly edmaCc,
                                            DMA_resourceStruct * edmaResources)
{
    uint32_t channelCnt = 0;
    int32_t  status = 0;

    uint32_t validParamSet;
    uint32_t validChannel;
    uint32_t validTcc;

    if ( edmaResources == NULL )
    {
#ifdef DEBUG
        printf("DMA_resourceAllocator_allocateResources : NULL pointer passed\n");
#endif
        status = -1;
    }

    if ( status == 0 )
    {
        if ( gEdma3RmHandle == NULL )
        {

            for (channelCnt = 0; channelCnt < edmaResources->numChannels ; channelCnt++)
            {
                status = resourceAllocator_allocateValidChannel( edmaResources->dmaAttr[channelCnt],
                                                        &validChannel );
                if ( status != 0)
                {
#ifdef DEBUG
                    printf("DMA_resourceAllocator_allocateResources : Fail to Allocate Channel \n");
#endif
                }

                if ( status == 0 )
                {
                    status = resourceAllocator_allocateValidTcc( &validTcc );
                }
                else
                {
#ifdef DEBUG
                    printf("DMA_resourceAllocator_allocateResources : Fail to Allocate TCC \n");
#endif
                }
                if ( status == 0 )
                {
                    status = resourceAllocator_allocateValidParamSet((uint32_t) edmaResources->numParam[channelCnt],
                                                                      &validParamSet);
                }
                else
                {
#ifdef DEBUG
                    printf("DMA_resourceAllocator_allocateResources : Fail to Allocate Param Set\n");
#endif
                }
                if ( status != 0 )
                {
                    break;
                }
                edmaResources->logicalChannelNo[channelCnt]   = (uint8_t)validChannel;
                edmaResources->tccVal[channelCnt]             = (uint8_t)validTcc;
                edmaResources->baseParam[channelCnt]          = (volatile uint32_t *)(volatile void *) &edmaCc->PARAMENTRY[validParamSet];

            }
        }
        else
        {
            status = EDMA3LLD_SUPPORT_requestResources( gEdma3RmHandle, edmaCc ,(DMA_resourceStruct *)edmaResources );
        }
    }

    return status;
}

/* ==================================================
 *  @func   DMA_resourceAllocator_deallocateResources
 *
 *  @desc   This functions deallocates EDMA resources which are allocated using
 *          DMA_resourceAllocator_allocateResources API
 *
 *
 *  @modif    This function modifies internal global resource structure
 *
 *  @inputs   This function takes following Inputs
 *              edmaCc :
 *                  Pointer to the address space of EDMA module.
 *
 *              edmaResources :
 *                  Pointer to the resource structure allocated using
 *                  DMA_resourceAllocator_allocateResources API
 *                          baseParam[for Each channel requested]
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
int32_t DMA_resourceAllocator_deallocateResources(
                                            CSL_EdmaccRegsOvly edmaCc,
                                            DMA_resourceStruct * edmaResources)
{
    uint32_t    channelCnt;
    uint32_t    paramCnt;
    int32_t     status = 0;
    uint32_t    paramNum;

    if ( edmaResources == NULL )
    {
        status = -1;
    }

    if ( status == 0 )
    {
        if ( gEdma3RmHandle == NULL )
        {
            for ( channelCnt = 0 ; channelCnt < edmaResources->numChannels ; channelCnt++ )
            {
                if ( edmaResources->dmaAttr[channelCnt] == DMA_CHAN_ATTR_EDMA)
                {
                    gDmaResourceState.edmaChannelState[edmaResources->logicalChannelNo[channelCnt]] =
                        DMA_RESOURCE_FREE;
                }
                else
                {
                    gDmaResourceState.qdmaChannelState[edmaResources->logicalChannelNo[channelCnt]] =
                        DMA_RESOURCE_FREE;
                }
                gDmaResourceState.tccState[edmaResources->tccVal[channelCnt]] =
                    DMA_RESOURCE_FREE;


                /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
                /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
                /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
                   The address space is 32 bit and type casting to integer will not result into any loss because of TI's
                 compiler teratment to integer.   */
                paramNum = ((uint32_t)edmaResources->baseParam[channelCnt] -
                                            (uint32_t)&edmaCc->PARAMENTRY[0])>>
                                            CSL_EDMACC_DCHMAP_PAENTRY_SHIFT;
                /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

                for ( paramCnt = 0 ; paramCnt < edmaResources->numParam[channelCnt] ; paramCnt++ )
                {
                    gDmaResourceState.paramSetState[paramNum + paramCnt] =
                        DMA_RESOURCE_FREE;
                }

            }
        }
        else
        {
            status = EDMA3LLD_SUPPORT_releaseResources( gEdma3RmHandle, edmaCc , edmaResources );
        }
    }

    return status;
}


