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

#ifndef BUFFMANAGER_H_
#define BUFFMANAGER_H_

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>
#include "xdais_types.h"
#include <stdint.h>
#include "iop_ti.h"

#define MAX_BUFF_ELEMENTS TIOP_INPUT_TOTAL_FRAMES
#define MAX_BUFS_IN_FRAME TIOP_IN_BUFDESC_TOTAL

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
    uint32_t bufId;
    BUFFMGR_BufferStatus bufStatus;
    uint32_t bufSize[MAX_BUFS_IN_FRAME];
    uint8_t *buf[MAX_BUFS_IN_FRAME];
} BUFFMGR_buffEle;

typedef BUFFMGR_buffEle* BUFFMGR_buffEleHandle;

extern BUFFMGR_buffEle buffArray[MAX_BUFF_ELEMENTS];

/**
*@func BUFFMGR_Init()
*        The BUFFMGR_Init function is called by the test application to
*        initialise the global buffer element array to default and to allocate
*        required number of memory data for input buffers.
*/
extern int32_t BUFFMGR_Init(int32_t numBufs, IVISION_BufDesc *BufDescList);

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
extern void BUFFMGR_ReleaseBuffer(uint32_t bufffId[]);

/**
*@func BUFFMGR_DeInit()
*        The BUFFMGR_DeInit function releases all memory allocated by buffer 
*           manager.
*/
extern void BUFFMGR_DeInit
(
   int32_t numRefBufs
);

/**
*@func BUFFMGR_ReleaseAllBuffers()
*        The BUFFMGR_ReleaseAllBuffers function will set the status of all
*        buffer elements in the buffArray[] to be free. 
*/
extern void BUFFMGR_ReleaseAllBuffers();

#endif
