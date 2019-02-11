/*
********************************************************************************  
 * HDVICP2.0 Based tiler allocator
 * 
 * "HDVICP2.0 Based tiler allocator" is software module developed on TI's 
 *  HDVICP2 based SOCs. 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
********************************************************************************
*/
/**
  ******************************************************************************
  *  @file     tilerBuf.h
  *
  *  @brief    Definition of the routines for the tiler. This file contains 
  *            the apis for deriving tiler address, api for moving the a memory 
  *            block from raw memory to tiled memory
  *            It handles only TILED8 and TILED16 memory request
  *
  *  @author   Pramod Swami , Uday Kiran P. (udaykiran@ti.com)
  *
  *  @version  0.1 - Mar 2010 : Initial Version [Pramod, Nirmal] 
  *  @version  0.2 - Jul 2010 : Documentation and comments are added [Uday] 
  *****************************************************************************
*/

#ifndef _TILERBUF_H_
#define _TILERBUF_H_

/**
  Definitions for different types of the memory containers identifications
*/
#define RAW_MEMORY        (0)
#define CONTAINER_8BITS   (1)
#define CONTAINER_16BITS  (2)
/**
  Maximum numbe of the buffers that the tiler lib can give to application 
*/
#define MAX_BUFS (128)
/**
 *******************************************************************************
 *  @struct sTilerParams
 *  @brief  This structure contains all the parameters that are needed for 
 *          deriving the memory pointers for the tiler buffers 
 *
 * @param tiledBufferAddr : array of pointers that contains the address of the 
 *                          tiler buffers derived by the api. 
 *                          - Even locations are luma address 
 *                          - Odd locations are Chroma address 
 *                          Total number of addres populated depeds on the size
 *                          memory given. 
 *                          <b> this is populated by the library </b> 
 * @param tilerSpace      : Tells the what is the tiler space for the luma and 
 *                           chroma. 
 *                          - Location 0 is luma 
 *                          - Location 1 is Chroma  
 *                          <b> this is populated by the application and can be 
 *                              over ridden by lib</b> 
 * @param memoryOffset    : Tells the offset that needs to added to the tiler 
 *                          base. 
 *                          - location 0 is for luma 
 *                          - location 1 is for chroma 
 *                          <b> this is populated by the application and can be 
 *                              over ridden by lib</b> 
 * @param totalSizeLuma   : Total size of the memory available for Luma buffers
 *                          based on this, and buffer dimentions, total num 
 *                          of bufers are derived. 
 *                          It is asumed that chroma memory is half of this. 
 *                          <b> this is populated by the application </b> 
 * @param imageDim        : Dimentions of the buffers. 
 *                          - location 0 is width 
 *                          - Location 1 is height 
 *                          <b> this is populated by the application </b> 
 *
 *******************************************************************************
 **/

typedef struct {
  unsigned int tiledBufferAddr[MAX_BUFS];
  unsigned int tilerSpace[2];
  unsigned int memoryOffset[2];
  unsigned int totalSizeLuma;
  unsigned int imageDim[2];
}sTilerParams;
/** 
 *******************************************************************************
 *  @fn    Tiler_DataMove
 *
 *  @brief This function copies the data from the raw memory into tiled memorys
 *        
 *  @param[in] input  : pointer to the input block 
 *  @param[in] output : pointer to the output block
 *  @param[in] sizeX  : width of the buffer to copy
 *  @param[in] sizeY  : height of the bufffer to copy
 *  @param[in] tilerSpace : access unit of the output buffer
 *
 *  @return None
 *******************************************************************************
*/
void Tiler_DataMove(char *input,char *output, int sizeX, int sizeY, 
                    int tilerSpace);
/** 
 *******************************************************************************
 *  @fn    tiler_init
 *
 *  @brief This function initializes the memory pointers in the given structure 
 *        
 *  @param[in/out] pTilerParams   : pointer to the tiler params 
 *
 *  @return  number of buffers if success else -1
 *******************************************************************************
*/
int tiler_init(sTilerParams *pTilerParams )   ;
#endif
