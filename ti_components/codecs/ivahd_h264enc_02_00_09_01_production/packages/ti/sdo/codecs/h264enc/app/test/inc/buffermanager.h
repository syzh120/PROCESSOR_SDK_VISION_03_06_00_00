/*
 *******************************************************************************
*
 * HDVICP2.0 Based H.264 HP Encoder
*
 * "HDVICP2.0 Based H.264 HP Encoder" is software module developed on TI's 
 *  HDVICP2 based SOCs. This module is capable of compressing a 4:2:0 Raw 
 *  video into a high/main/baseline profile bit-stream. Based on ISO/IEC      
 *  14496-10." 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 *******************************************************************************
*/

#ifndef BUFFMANAGER_H_
#define BUFFMANAGER_H_
/** @mainpage HDVICP2.0 Based H.264 HP Encoder 
 * @brief "HDVICP2.0 Based H.264 HP Encoder"is software module developed on TI's 
 *  HDVICP2 based SOCs. This module is capable of compressing a 4:2:0 Raw 
 *  video into a high/main/baseline profile bit-stream. Based on ISO/IEC      
 *  14496-10." 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
*/

/*!
********************************************************************************
@file     BufferManager.c
@brief    This is source module for buffer manager functionality
(High Profile) Video Decoder Call using XDM Interface
@author   Multimedia Codecs TI India
@version  0.0 - May 17,2007    initial version
********************************************************************************
*/

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>
#include <ti/xdais/xdas.h>
#include <h264enc_ti_test.h>

#define MAX_BUFF_ELEMENTS 35
#define MAX_BUFS_IN_FRAME 35
/**
 *  @brief      Status of the buffer elements.
 */
typedef enum {
    BUFFMGR_BUFFER_FREE = 0,      
    BUFFMGR_BUFFER_USED = 1      
} BUFFMGR_BufferStatus;

/**
 *  @brief      Each element in the buffer array.
 */
typedef struct BuffEle
{
    XDAS_UInt32 bufId;
    BUFFMGR_BufferStatus bufStatus;
    XDAS_UInt32 bufSize[MAX_BUFS_IN_FRAME];
    volatile XDAS_UInt8 *buf[MAX_BUFS_IN_FRAME];
} BUFFMGR_buffEle;

typedef BUFFMGR_buffEle* BUFFMGR_buffEleHandle;

extern BUFFMGR_buffEle buffArray[MAX_ITEMS_TO_RUN][MAX_BUFF_ELEMENTS];

/**
*@func BUFFMGR_Init()
*        The BUFFMGR_Init function is called by the test application to
*        initialise the global buffer element array to default and to allocate
*        required number of memory data for reference and output buffers.
*        The maximum required dpb size is defined by the supported profile & 
*        level.
*/
/* extern XDAS_Int32 BUFFMGR_Init(XDAS_Int32 numBufs, XDM2_BufSize *bufSizes);*/
extern XDAS_Int32 BUFFMGR_Init(XDAS_Int32 numRefBufs, XDAS_Int32 numBufs, 
                 XDM2_BufSize *bufSizes,XDAS_Int8 lumaTilerSpace, 
                 XDAS_Int8 chromaTilerSpace);
/**
*@func BUFFMGR_ReInit()
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
   XDM2_BufSize *bufSizes
);

/**
*@func BUFFMGR_GetFreeBuffer()
*        The BUFFMGR_GetFreeBuffer function searches for a free buffer in the 
*        global buffer array and returns the address of that element. Incase
*        if none of the elements are free then it returns NULL
*/
extern BUFFMGR_buffEleHandle BUFFMGR_GetFreeBuffer();

/**
*@func BUFFMGR_ReleaseBuffer(buffId)
*        The BUFFMGR_ReleaseBuffer function takes an array of buffer-ids
*        which are released by the test-app. "0" is not a valid buffer Id
*        hence this function keeps moving until it encounters a buffer Id 
*        as zero or it hits the MAX_BUFF_ELEMENTS
*/
extern void BUFFMGR_ReleaseBuffer(XDAS_UInt32 bufffId[]);

/**
*@func BUFFMGR_DeInit()
*        The BUFFMGR_DeInit function releases all memory allocated by buffer 
*           manager.
*/
extern void BUFFMGR_DeInit
(
   XDAS_Int32 numRefBufs,
   XDAS_Int32 numOutBufs
);
void BUFFMGR_ReleaseAllBuffers();

#endif

