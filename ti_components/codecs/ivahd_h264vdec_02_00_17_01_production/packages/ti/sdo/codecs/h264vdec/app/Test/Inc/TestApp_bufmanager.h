/*
*******************************************************************************
 * HDVICP2.0 Based H.264 HP Decoder
 * 
 * "HDVICP2.0 Based H.264 HP Decoder" is a software module developed on TI's 
 *  HDVICP2 based SOCs. This module is capable of decoding a compressed 
 *  high/main/baseline profile H.264 bit-stream into a YUV 4:2:0 Raw video.
 *  Based on "ISO/IEC 14496-10". 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
*******************************************************************************
*/

/**  
*******************************************************************************
 * @file TestApp_bufmanager.h                       
 *                                       
 * @brief  This file contains function & enum declaration for buffer manager 
 *         functionality using XDM Interface  
 *
 * @author:  Ramakrishna Adireddy
 *
 * @version 0.1 (Jan 2009) : Base version Created
 * @version 0.2 (Jun 2010) : Generalized the Reinit function by passing the
 *                           start index [Ramakrishna Adireddy]
 ******************************************************************************
*/

#ifndef _TESTAPP_BUFMANAGER_H_
#define _TESTAPP_BUFMANAGER_H_

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/xdm.h>

#define my_Memalign(align, size) memalign(align, size)

#define MAX_BUFF_ELEMENTS 33
#define MAX_BUFS_IN_FRAME 7
#define ADD_DISPLAY_BUFS  0

/** 
 ******************************************************************************
 *  @enum       BUFFMGR_BufferStatus
 *  @brief      This tells the buffer element's status
 *  @details   
 ******************************************************************************
*/
typedef enum
{
  BUFFMGR_BUFFER_FREE = 0,
    /**<
    * This indicates the buffer element is free, available for use.
    */   
     
  BUFFMGR_BUFFER_USED = 1      
    /**<
    * This indicates the buffer element is in use.
    */   
} BUFFMGR_BufferStatus;

/**
 ******************************************************************************
 *  @struct BuffEle
 *
 *  @brief  This tells about Each element in the buffer array.
 *
 *  @param  bufId :
 *
 *  @param  bufStatus : 
 *
 *  @param  bufSize[MAX_BUFS_IN_FRAME] :
 *
 *  @param  buf[MAX_BUFS_IN_FRAME] : 
 *
 ******************************************************************************
*/
typedef struct BuffEle
{
  XDAS_UInt32           bufId;
  BUFFMGR_BufferStatus  bufStatus;
  XDM2_BufSize          bufSize[MAX_BUFS_IN_FRAME];
  volatile XDAS_UInt8  *buf[MAX_BUFS_IN_FRAME];

} BUFFMGR_buffEle;

typedef BUFFMGR_buffEle* BUFFMGR_buffEleHandle;


/** 
********************************************************************************
 *  @fn     BUFFMGR_Init()
 *  @brief  This function is called by the test application to initialise the 
 *          global buffer element array to default and to allocate required 
 *          number of memory data for reference and output buffers.
 *          The maximum required dpb size is defined by the supported profile & 
 *          level.
 *          
 *  @param[in] numBufs   : Pointer to CodecParams.
 *  @param[in] bufSizes : Packed MB level Intermediate Info.
 *  @param[in] memType     : MB number in Frame. 
 *          
 *  @return XDAS_Int32
********************************************************************************
*/
extern XDAS_Int32 BUFFMGR_Init(XDAS_Int32 numBufs, XDM2_BufSize *bufSizes, 
                               XDAS_Int32 *memType,XDAS_Int8 chnlNum);

/**
*@fn BUFFMGR_ReInit()
*        The BUFFMGR_ReInit function allocates global luma and chroma buffers
*       and allocates entire space to first element. This element will be used 
*       in first frame decode. After the picture's height and width and its luma 
*       and chroma buffer requirements are obtained the global luma and chroma
*       buffers are re-initialised to other elements in teh buffer arary. 
*/
extern XDAS_Int32 BUFFMGR_ReInit
(
   XDAS_Int32 numRefBufs,
   XDAS_Int32 numOutBufs,
   XDM2_BufSize *bufSizes,
   XDAS_Int32 *memType,
   XDAS_Int32  startBufIdx,
   XDAS_Int8   chnlNum
);

/**
*@fn BUFFMGR_GetFreeBuffer()
*        The BUFFMGR_GetFreeBuffer function searches for a free buffer in the 
*        global buffer array and returns the address of that element. Incase
*        if none of the elements are free then it returns NULL
*/
extern BUFFMGR_buffEleHandle BUFFMGR_GetFreeBuffer(XDAS_Int8 chnlNum);

/**
*@fn BUFFMGR_ReleaseBuffer(buffId)
*        The BUFFMGR_ReleaseBuffer function takes an array of buffer-ids
*        which are released by the test-app. "0" is not a valid buffer Id
*        hence this function keeps moving until it encounters a buffer Id 
*        as zero or it hits the MAX_BUFF_ELEMENTS
*/
void BUFFMGR_ReleaseBuffer(XDAS_UInt32 bufffId[],XDAS_Int8 chnlNum);

/**
*@fn BUFFMGR_ReleaseAllBuffers()
*        The BUFFMGR_DeInit function releases all memory allocated by buffer 
*           manager.
*/
void BUFFMGR_ReleaseAllBuffers(XDAS_Int8 chnlNum);

/**
*@fn BUFFMGR_DeInit()
*        The BUFFMGR_DeInit function releases all memory allocated by buffer 
*           manager.
*/
void BUFFMGR_DeInit
(
   XDAS_Int32 numRefBufs,
   XDAS_Int32 numOutBufs,
   XDAS_Int8  chnlNum
);

#endif

