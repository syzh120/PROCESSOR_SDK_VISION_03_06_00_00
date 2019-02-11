/*
 ===========================================================================
 * HDVICP2 Based H.264 HP Encoder
 * 
 * "HDVICP2 Based H.264 HP Encoder" is software module developed on TI's 
 * HDVICP2 based SOCs. This module is capable of compressing a 4:2:0 Raw 
 * video into a high/main/baseline profile bit-stream.
 *
 * Copyright (C) {2009} Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 *
 ===========================================================================
*/


/**  
 *****************************************************************************
 * @file BufferManager.c
 *                                       
 * @brief This is source module for buffer manager functionality
 *        (Baseline Profile) Video Encoder Call using XDM Interface.
 *  
 *
 * @author: Multimedia Codecs TI India
 *
 * @version 0.0 (Jan 2008) : Base version created
 *                           [MMCODECS]
 * @version 0.1 (Nov 2009) : Review and more commenting along with cleanup
 *                           [Rama Mohan]
 * @version 0.2 (April 2010) : Support of tiler buffer control [Pramod]
 * @version 0.3 (Aug 2010) : Added support for 2Kx2K
 *****************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>

#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/xdm.h>
#include "buffermanager.h"
/* #include <H264BPEncconfig.h>                                               */
#include <h264enc.h>
#include <tilerBuf.h>

#define MAX_DPB_LUMA_SIZE   (10705920)
#define MAX_DPB_CHROMA_SIZE (5352960)

/* BUFFMGR_buffEle buffArray[MAX_BUFF_ELEMENTS];                              */
BUFFMGR_buffEle buffArray[MAX_ITEMS_TO_RUN][MAX_BUFF_ELEMENTS];
XDAS_UInt8 *globalBufferHandle[XDM_MAX_IO_BUFFERS];
XDAS_UInt32 globalBufferSizes[XDM_MAX_IO_BUFFERS];

#pragma DATA_SECTION(InBuffers, ".inputbuffer_mem");
XDAS_UInt8 InBuffers[(2048*2048 + 2048*1024 + 32 )*9];
XDAS_UInt8 *InbufPtr;
extern sTilerParams TilerParams;
extern H264ENC_Params     gParams;
extern H264ENC_DynamicParams  gDynamicParams;
extern XDAS_UInt32   insChanid;

/*****************************************************************************/
/**
*@func BUFFMGR_Init()
*@brief  TII's (Texas Instrument India) implementation of buffer manager 
*       initialization module
*
*        The BUFFMGR_Init function is called by the test application to
*        initialise the global buffer element array to default and to allocate
*        required number of memory data for reference and output buffers.
*        The maximum required dpb size is defined by the supported profile & 
*        level.
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
XDAS_Int32 BUFFMGR_Init(XDAS_Int32 numRefBufs, XDAS_Int32 numBufs, 
                        XDM2_BufSize *bufSizes,
                        XDAS_Int8 lumaTilerSpace, XDAS_Int8 chromaTilerSpace)
{
    XDAS_UInt32 tmpCnt, size;
    XDAS_UInt8  idx;

    XDAS_UInt8 *tmpBufPtr;

    
    /* Initialise the elements in the global buffer array */
    for(tmpCnt = 0; tmpCnt < MAX_BUFF_ELEMENTS; tmpCnt++)
    {
        buffArray[insChanid][tmpCnt].bufId      = tmpCnt+1;
        buffArray[insChanid][tmpCnt].bufStatus  = BUFFMGR_BUFFER_FREE;

        for (idx = 0; idx < MAX_BUFS_IN_FRAME; idx++)
        {
            buffArray[insChanid][tmpCnt].bufSize[idx] = 0;
            buffArray[insChanid][tmpCnt].buf[idx]     = NULL;
        }
    }
    
    
    for(idx = 0; idx < numRefBufs; idx++)
     {
       size = bufSizes[0].bytes + bufSizes[1].bytes + 32;
     tmpBufPtr = (InbufPtr + size*idx + 15);
     tmpBufPtr = (XDAS_UInt8*)((XDAS_UInt32)tmpBufPtr >> 4); 
     tmpBufPtr = (XDAS_UInt8*)((XDAS_UInt32)tmpBufPtr << 4); 

       /* Check if allocation took place properly or not */
       if (tmpBufPtr == NULL)
       {
           return -1;
      }
     
    if(lumaTilerSpace) 
    {
      buffArray[insChanid][idx].buf[0]     = 
                   (volatile XDAS_UInt8 *)TilerParams.tiledBufferAddr[2*idx + 
                                                  (numRefBufs * 2 * insChanid)];
    }
    else
    {
           buffArray[insChanid][idx].buf[0]     = tmpBufPtr;
    }
           buffArray[insChanid][idx].bufSize[0] = bufSizes[0].bytes;
    if(chromaTilerSpace) 
    {
    buffArray[insChanid][idx].buf[1]     = 
                 (volatile XDAS_UInt8 *)TilerParams.tiledBufferAddr[2*idx+1 + 
                                                  (numRefBufs * 2 * insChanid)];
    }
    else
    {
           buffArray[insChanid][idx].buf[1]     = tmpBufPtr + bufSizes[0].bytes;
    }
           buffArray[insChanid][idx].bufSize[1] = bufSizes[1].bytes;


    }
    InbufPtr = tmpBufPtr + bufSizes[0].bytes;
     return 0;
}


/****************************************************************************/
/**
*@func BUFFMGR_ReInit()
*@brief  TII's (Texas Instrument India) implementation of buffer manager 
*       re-initialization module
*
*       The BUFFMGR_ReInit function allocates global luma and chroma buffers
*       and allocates entire space to first element. This element will be used 
*       in first frame decode. After the picture's height and width and its  
*       luma and chroma buffer requirements are obtained the global luma and 
*       chroma buffers are re-initialised to other elements in teh buffer 
*       array. 
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
/****************************************************************************/

XDAS_Int32 BUFFMGR_ReInit
(
   XDAS_Int32 numRefBufs,
   XDAS_Int32 numOutBufs,
   XDM2_BufSize *bufSizes
)
{
    XDAS_UInt8 *tmpBufPtr;
  XDAS_Int32  idx, ctr, size;

    /* As the application would have already provided one buffer    */
    /* allocate memory for 1 minus the actual number of reference   */
    /* buffers.                                                     */

    for(idx = 1; idx < numRefBufs; idx++)
    {
       /* for(ctr = 0; ctr < numOutBufs; ctr++)                              */
       {
          ctr = 0;
          size = bufSizes[ctr].bytes + bufSizes[ctr+1].bytes + 32;
          tmpBufPtr = malloc (size * sizeof(XDAS_UInt8));
          /* memset(tmpBufPtr,0,size);                                       */

          if(tmpBufPtr == NULL)
          {
            free(tmpBufPtr);
            return -1;
          }

          buffArray[insChanid][idx].buf[ctr]     = tmpBufPtr;
          buffArray[insChanid][idx].bufSize[ctr] = bufSizes[ctr].bytes;
          buffArray[insChanid][idx].buf[ctr + 1]     = 
                                               tmpBufPtr + bufSizes[ctr].bytes;
          buffArray[insChanid][idx].bufSize[ctr + 1] = bufSizes[ctr + 1].bytes;

       }
    }
    return 0;
}


/*****************************************************************************/
/**
*@func BUFFMGR_GetFreeBuffer()
*@brief  TII's (Texas Instrument India) implementation of buffer manager 
*       re-initialization module
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
    XDAS_UInt32 tmpCnt;
    for(tmpCnt = 0; 
        tmpCnt < MAX_BUFF_ELEMENTS; 
        tmpCnt++)
    {
        /* Check for first empty buffer in the array and return its address */
        if(buffArray[insChanid][tmpCnt].bufStatus == BUFFMGR_BUFFER_FREE)
        {
            buffArray[insChanid][tmpCnt].bufStatus = BUFFMGR_BUFFER_USED;
            return (&buffArray[insChanid][tmpCnt]);
        }
    }    
    /* Incase if no elements in the array are free then return NULL */
    return NULL;
}


/*****************************************************************************/
/**
*@func BUFFMGR_ReleaseBuffer(buffId)
*@brief  TII's (Texas Instrument India) implementation of buffer manager 
*       re-initialization module
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
void BUFFMGR_ReleaseBuffer(XDAS_UInt32 bufffId[])
{
    XDAS_UInt32 tmpCnt, tmpId;
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
        buffArray[insChanid][tmpId].bufStatus = BUFFMGR_BUFFER_FREE;
    }    
    return;
}

/****************************************************************************/
/**
*@func BUFFMGR_ReleaseAllBuffers()
*@brief  TII's (Texas Instrument India) implementation of buffer manager 
*       re-initialization module
*
*       The BUFFMGR_ReleaseAllBuffers function will set the status of
*       all buffer elements in the buffArray[] to free. This is called
*       for cases when application does not set freebufid of all buffers 
*       typically when stream has not finished but app wants to end decoding.
*
*@return None
*/
/****************************************************************************/
void BUFFMGR_ReleaseAllBuffers()
{
    XDAS_UInt32 tmpCnt;
    for(tmpCnt = 0; 
        (tmpCnt < MAX_BUFF_ELEMENTS); 
        tmpCnt++)
    {
        /* Set the status of the buffer to FREE */
        buffArray[insChanid][tmpCnt].bufStatus = BUFFMGR_BUFFER_FREE;
    }
    return; 
}
/****************************************************************************/
/**
*@func BUFFMGR_DeInit()
*@brief  TII's (Texas Instrument India) implementation of buffer manager 
*       re-initialization module
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
   XDAS_Int32 numRefBufs,
   XDAS_Int32 numOutBufs
)
{
    XDAS_Int32  idx, ctr;

    /* As the application would have already provided one buffer    */
    /* allocate memory for 1 minus the actual number of reference   */
    /* buffers.                                                     */

    for(idx = 0; idx < numRefBufs; idx++)
    {
        /* for(ctr = 0; ctr < numOutBufs; ctr++)                              */
        {
       ctr = 0;
           free((void *)buffArray[insChanid][idx].buf[ctr]);
        }
    }
    return;
}
