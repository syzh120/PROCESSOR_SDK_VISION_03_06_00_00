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
 * @file h264enc_ti_file_io.h                          
 *                                       
 * @brief This File contains file input\output interface functions to standard
 *        C library functions
 *  
 *
 * @author: Rama Mohana Reddy (rama.mr@ti.com)
 *
 * @version 0.0 (Oct 2009) : Base version created
 *                           [Rama Mohan]
 * @version 0.1 (Oct 2009) : Review and more commenting along with cleanup
 *                           [Rama Mohan]
 *****************************************************************************
*/
#ifndef _H264ENC_TI_FILE_IO_H_
#define _H264ENC_TI_FILE_IO_H_
#include <xdc/std.h>
#include <stdio.h>
#include <ti/xdais/xdas.h>

/** 
********************************************************************************
 *  @fn     init_file_io()
 *  @brief  initializes the file IO system specific to the platform
 *          
 *  @param[in]  None
 *
 *  @return     None
 *
********************************************************************************
*/
void init_file_io();


/** 
********************************************************************************
 *  @fn     my_fopen
 *  @brief  Interface function for standard fopen file
 *          
 *  @param[in]  filename : Pointer to the filename along with path
 *
 *  @param[in]  mode : Mode of the file to be opened (read,write,append...)
 *
 *  @return     Pointer to file handle on successfull open
 *              NULL in case of error
 *
********************************************************************************
*/

FILE *my_fopen(const char *pInputFileName,const char *mode);

/** 
********************************************************************************
 *  @fn     my_fread
 *  @brief  Interface function for standard fread operation
 *          
 *  @param[in]  pOutputPtr : Pointer to the data buffer to place read data
 *
 *  @param[in]  uiSize : Size of each unit
 *
 *  @param[in]  count : Number of units to be read
 *
 *  @param[in]  fp : Pointer to the file handle
 *
 *  @return     number of bytes read
 *
********************************************************************************
*/

XDAS_UInt32 my_fread(void *pOutputPtr,XDAS_UInt32 uiSize,XDAS_UInt32 uiCount,
                                                  FILE *fp);

/** 
********************************************************************************
 *  @fn     my_fwrite
 *  @brief  Interface function for standard fwrite operation
 *          
 *  @param[in]  pInputPtr : Pointer to the data buffer containing the data to be
 *              to be written
 *
 *  @param[in]  uiSize : Size of each unit
 *
 *  @param[in]  count : Number of units to be written
 *
 *  @param[in]  fp : Pointer to the file handle
 *
 *  @return     number of bytes read
 *
********************************************************************************
*/

XDAS_UInt32 my_fwrite(const void *pInputPtr,XDAS_UInt32 uiSize,
                              XDAS_UInt32 uiCount,FILE *fp);

/** 
********************************************************************************
 *  @fn     my_fseek
 *  @brief  Interface function for standard fseek operation
 *          
 *  @param[in]  fp : Pointer to the file handle
 *
 *  @param[in]  uiOffset : Offset from the location
 *
 *  @param[in]  uiPosition : Poisition in the file from were pointer to be moved
 *
 *  @return     0 - when no error in closing file
 *              ErrorCode - when it encouters error while closing
 *
********************************************************************************
*/

XDAS_UInt32 my_fseek(FILE *fp,XDAS_UInt32 uiOffset,XDAS_UInt32 uiPosition);

/** 
********************************************************************************
 *  @fn     my_fclose
 *  @brief  Interface function for standard fclose operation
 *          
 *  @param[in]  fp : Pointer to the file handle
 *
 *
 *  @param[in]  uiPosition : Poisition in the file from were pointer to be moved
 *
 *  @return     0 - when no error in closing file
 *              ErrorCode - when it encouters error while closing
 *
********************************************************************************
*/

XDAS_Int32 my_fclose(FILE *fp);

/** 
********************************************************************************
 *  @fn     XDAS_UInt32 TestApp_FileLength(FILE *fp)
 *  @brief  Calculates the file size in bytes
 *          
 *  @param[in]  fp : File pointer for which size needs to be calculated
 *
 *  @return    XDAS_UInt32 size of the file
 *             
********************************************************************************
*/


XDAS_UInt32 TestApp_FileLength(FILE *fp);



#endif /*#ifndef _H264ENC_TI_FILE_IO_H_*/
