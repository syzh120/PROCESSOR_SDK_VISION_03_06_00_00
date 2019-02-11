/*
* module name       : BufferManager.c 
*
* module descripton : This is source module for buffer manager functionality
*
* Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/ 
*
* ALL RIGHTS RESERVED 
*
*
*/

#include <stdio.h>
#include <stdlib.h>

#include "buffermanager.h"

BUFFMGR_buffEle buffArray[MAX_BUFF_ELEMENTS];                              

/*****************************************************************************/
/**
*@func BUFFMGR_Init()
*@brief  TII's (Texas Instrument India) implementation of buffer manager 
*       initialization module
*
*        The BUFFMGR_Init function is called by the test application to
*        initialise the global buffer element array to default and to allocate
*        required number of memory data for input buffers.
*
*@param  numBufs
*        Number of buffers to be allocated
*
*@param  bufSizes
*        Address of array containing the buffer sizes of the numbufs
*
*@return Success(0)/failure(-1) in allocating and initialising
*
*/
/*****************************************************************************/
int32_t BUFFMGR_Init(int32_t numBufs, 
                        IVISION_BufDesc   *BufDescList)
{
    uint32_t tmpCnt;
    uint8_t  idx;

    //uint8_t *tmpBufPtr;

    
    /* Initialise the elements in the global buffer array */
    for(tmpCnt = 0; tmpCnt < MAX_BUFF_ELEMENTS; tmpCnt++)
    {
        buffArray[tmpCnt].bufId      = tmpCnt+1;
        buffArray[tmpCnt].bufStatus  = BUFFMGR_BUFFER_FREE;

        for (idx = 0; idx < MAX_BUFS_IN_FRAME; idx++)
        {
            buffArray[tmpCnt].bufSize[idx] = (BufDescList[tmpCnt].bufPlanes[idx].width*
            BufDescList[tmpCnt].bufPlanes[idx].height);
            buffArray[tmpCnt].buf[idx]     = (uint8_t*)BufDescList[tmpCnt].bufPlanes[idx].buf;
        }
    }
    
     return 0;
}


/*****************************************************************************/
/**
*@func BUFFMGR_GetFreeBuffer()
*@brief  TII's (Texas Instrument India) implementation of buffer manager 
*       get free buffer module
*
*        The BUFFMGR_GetFreeBuffer function searches for a free buffer in the 
*        global buffer array and returns the address of that element. Incase
*        if none of the elements are free then it returns NULL
*
*
*@return Valid buffer element address or NULL incase if no buffers are empty
*
*/
/*****************************************************************************/
BUFFMGR_buffEleHandle BUFFMGR_GetFreeBuffer()
{
    uint32_t tmpCnt;
    for(tmpCnt = 0; 
        tmpCnt < MAX_BUFF_ELEMENTS; 
        tmpCnt++)
    {
        /* Check for first empty buffer in the array and return its address */
        if(buffArray[tmpCnt].bufStatus == BUFFMGR_BUFFER_FREE)
        {
            buffArray[tmpCnt].bufStatus = BUFFMGR_BUFFER_USED;
            return (&buffArray[tmpCnt]);
        }
    }    
    /* Incase if no elements in the array are free then return NULL */
    return NULL;
}


/*****************************************************************************/
/**
*@func BUFFMGR_ReleaseBuffer(buffId)
*@brief  TII's (Texas Instrument India) implementation of buffer manager 
*       release buffer module
*
*        The BUFFMGR_ReleaseBuffer function takes an array of buffer-ids
*        which are released by the test-app. "0" is not a valid buffer Id
*        hence this function keeps moving until it encounters a buffer Id 
*        as zero or it hits the MAX_BUFF_ELEMENTS
*
*
*@return None
*
*/
/*****************************************************************************/
void BUFFMGR_ReleaseBuffer(uint32_t bufffId[])
{
    uint32_t tmpCnt, tmpId;
    for(tmpCnt = 0; 
        (tmpCnt < MAX_BUFF_ELEMENTS); 
        tmpCnt++)
    {
        tmpId = bufffId[tmpCnt];
        /*
         * Check if the buffer Id = 0 condition has reached. zero is not a 
         * valid buffer Id hence that value is used to identify the end of 
         * buffer array
         */
        if(tmpId == 0)
        {
           break;
        }
        /* 
         * convert the buffer-Id to its corresponding index in the global 
         * array 
         */
/*         printf("   |   |%3d|\n", tmpId);                                   */
        tmpId--;

        /* Set the status of the buffer to FREE */
        buffArray[tmpId].bufStatus = BUFFMGR_BUFFER_FREE;
    }    
    return;
}

/****************************************************************************/
/**
*@func BUFFMGR_ReleaseAllBuffers()
*@brief  TII's (Texas Instrument India) implementation of buffer manager 
*       release all buffers module
*
*       The BUFFMGR_ReleaseAllBuffers function will set the status of
*       all buffer elements in the buffArray[] to free. This is called
*       for cases when application does not set freebufid of all buffers 
*       typically when stream has not finished but app wants to end processing.
*
*@return None
*/
/****************************************************************************/
void BUFFMGR_ReleaseAllBuffers()
{
    uint32_t tmpCnt;
    for(tmpCnt = 0; 
        (tmpCnt < MAX_BUFF_ELEMENTS); 
        tmpCnt++)
    {
        /* Set the status of the buffer to FREE */
        buffArray[tmpCnt].bufStatus = BUFFMGR_BUFFER_FREE;
    }
    return; 
}

/****************************************************************************/
/**
*@func BUFFMGR_DeInit()
*@brief  TII's (Texas Instrument India) implementation of buffer manager 
*       de-initialization module
*
*        The BUFFMGR_DeInit function releases all memory allocated by buffer 
*           manager.
*
*@param  numBufs
*        Number of buffers to be de-allocated
*
*@return None
*
*/
/****************************************************************************/

void BUFFMGR_DeInit
(
   int32_t numBufs
)
{
    int32_t  idx, ctr;

    /* As the application would have already provided one buffer    */
    /* allocate memory for 1 minus the actual number of reference   */
    /* buffers.                                                     */

    for(idx = 0; idx < numBufs; idx++)
    {
      /* for(ctr = 0; ctr < numOutBufs; ctr++)                              */
      {
        ctr = 0;
        free((void *)buffArray[idx].buf[ctr]);
      }
    }
    return;
}
