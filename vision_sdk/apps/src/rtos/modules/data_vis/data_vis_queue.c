/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include <src/rtos/utils_common/include/utils_stat_collector.h>
#include "data_vis_priv.h"

Void DataVis_queueDataBwCreate()
{
    DataVis_CreatePrm *pCreatePrm;

    pCreatePrm = &gDataVis_Obj.createPrm;

    gDataVis_Obj.queue.readIdx = 0;
    gDataVis_Obj.queue.writeIdx = 0;
    gDataVis_Obj.queue.count = 0;

    gDataVis_Obj.queue.data =
        Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            sizeof(DataVis_DataBwElement)*pCreatePrm->maxNumberOfSamples, 32);
    UTILS_assert(gDataVis_Obj.pDrawDataBwElements != NULL);
}

Void DataVis_queueDataBwDelete()
{
    DataVis_CreatePrm *pCreatePrm;

    pCreatePrm = &gDataVis_Obj.createPrm;

    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
        gDataVis_Obj.queue.data,
        sizeof(DataVis_DataBwElement)*pCreatePrm->maxNumberOfSamples
        );
}

/*******************************************************************************
 *  \brief Write one element of data BW collected to shared memory
 *
 *         Called by the data collection thread.
 *
 *         API has no effect if DataVis_create() and DataVis_setDataBwPrm()
 *         are not called
 *
 *         If shared memory is full, the API internally reads one element to make
 *         space for new element
 *
 *******************************************************************************
 */
Int32 DataVis_writeDataBwData(DataVis_DataBwElement *pElem)
{
    Int32 retVal = SYSTEM_LINK_STATUS_EFAIL;
    DataVis_CreatePrm *pCreatePrm;

    if(gDataVis_Obj.isSetPrmDone==FALSE)
        return retVal;

    pCreatePrm = &gDataVis_Obj.createPrm;

    DataVis_lock();

    /* If we will overflow readPtr, increment readPtr */
    if(gDataVis_Obj.queue.count >= pCreatePrm->maxNumberOfSamples)
    {
        gDataVis_Obj.queue.readIdx = (gDataVis_Obj.queue.readIdx+1)%pCreatePrm->maxNumberOfSamples;
        gDataVis_Obj.queue.count--;
    }

    memcpy(&gDataVis_Obj.queue.data[gDataVis_Obj.queue.writeIdx],
           pElem,
           sizeof(DataVis_DataBwElement));

    gDataVis_Obj.queue.count++;
    gDataVis_Obj.queue.writeIdx = (gDataVis_Obj.queue.writeIdx+1)%pCreatePrm->maxNumberOfSamples;

    retVal = SYSTEM_LINK_STATUS_SOK;

    DataVis_unlock();

    return retVal;
}

/*******************************************************************************
 *  \brief Read element's of data BW collected in shared memory for drawing
 *         purpose
 *
 *         Called by the DataVis_drawDataBw() internally
 *
 *******************************************************************************
 */
Int32 DataVis_readDataBwData(DataVis_DataBwElement *pElem, UInt32 *numElementsRead, UInt32 maxElementsToRead)
{
    Int32 retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 elemToRead;
    DataVis_CreatePrm *pCreatePrm;

    if(gDataVis_Obj.isSetPrmDone==FALSE)
        return retVal;

    pCreatePrm = &gDataVis_Obj.createPrm;

    DataVis_lock();

    if((gDataVis_Obj.queue.count == 0) || (maxElementsToRead == 0))
    {
        /* Ignore if nothing has been written */
        *numElementsRead = 0;
        retVal = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        if(gDataVis_Obj.queue.readIdx < gDataVis_Obj.queue.writeIdx)
        {
            /* Read till gDataVis_Obj.queue.writeIdx */
            elemToRead = gDataVis_Obj.queue.writeIdx - gDataVis_Obj.queue.readIdx;
            if(elemToRead > maxElementsToRead)
            {
                /* But don't exceed maxElementsToRead */
                elemToRead = maxElementsToRead;
            }
            memcpy(pElem,
                   &gDataVis_Obj.queue.data[gDataVis_Obj.queue.readIdx],
                   sizeof(DataVis_DataBwElement)*elemToRead);
            gDataVis_Obj.queue.readIdx = (gDataVis_Obj.queue.readIdx+elemToRead)%pCreatePrm->maxNumberOfSamples;
            gDataVis_Obj.queue.count -= elemToRead;

            *numElementsRead = elemToRead;
        }
        else
        {
            /* Read till end of buffer */
            elemToRead = pCreatePrm->maxNumberOfSamples - gDataVis_Obj.queue.readIdx;
            if(elemToRead > maxElementsToRead)
            {
                /* But don't exceed maxElementsToRead */
                elemToRead = maxElementsToRead;
            }
            memcpy(pElem,
                   &gDataVis_Obj.queue.data[gDataVis_Obj.queue.readIdx],
                   sizeof(DataVis_DataBwElement)*elemToRead);
            gDataVis_Obj.queue.readIdx = (gDataVis_Obj.queue.readIdx+elemToRead)%pCreatePrm->maxNumberOfSamples;
            gDataVis_Obj.queue.count -= elemToRead;
            *numElementsRead = elemToRead;

            /* If maxElementsToRead is not reached proceed */
            if(elemToRead < maxElementsToRead)
            {
                /* Update src and dest */
                pElem += elemToRead;

                /* Read till gDataVis_Obj.queue.writeIdx */
                if(gDataVis_Obj.queue.writeIdx > (maxElementsToRead - elemToRead))
                {
                    /* But don't exceed maxElementsToRead */
                    elemToRead = maxElementsToRead - elemToRead;
                }
                else
                {
                    elemToRead = gDataVis_Obj.queue.writeIdx;
                }
                memcpy(pElem,
                       &gDataVis_Obj.queue.data[gDataVis_Obj.queue.readIdx],
                       sizeof(DataVis_DataBwElement)*elemToRead);
                gDataVis_Obj.queue.readIdx = (gDataVis_Obj.queue.readIdx+elemToRead)%pCreatePrm->maxNumberOfSamples;
                gDataVis_Obj.queue.count -= elemToRead;
                *numElementsRead += elemToRead;
            }
        }

        retVal = SYSTEM_LINK_STATUS_SOK;
    }

    DataVis_unlock();

    return retVal;
}
