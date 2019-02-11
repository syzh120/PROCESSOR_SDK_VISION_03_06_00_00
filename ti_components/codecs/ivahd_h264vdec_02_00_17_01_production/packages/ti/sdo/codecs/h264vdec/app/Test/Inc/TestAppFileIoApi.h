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
 *****************************************************************************
 * @file h264vdec_ti_fileIO.h                          
 *                                       
 * @brief This File contains file input\output interface functions to file
 *        operating functions
 *  
 * @author: Ramakrishna Adireddy (x0086452@ti.com)
 *
 * @version 0.0 (Jan 2011) : Base version created
 *                           [Ramakrishna]
 *****************************************************************************
*/
#ifndef _FILE_IO_H_
#define _FILE_IO_H_

#include <xdc/std.h>
#include <stdio.h>
#include <ti/xdais/xdas.h>

/** 
 ******************************************************************************
 *  @enum       fileIOtypes
 *  @brief      This tells kind of file IO can be used.
 *  @details   
 ******************************************************************************
*/
typedef enum _fileIOtypes
{
  AX_FILE_IO = 1,
    /**<
    * This indicates file IO operations done by other than M3.
    * Even we call this as fast file IO. The HOST in this case will be A8/A9
    */   
  PCI_FILE_IO = 2,
    /**<
    * This indicates file IO operations using PCI i.e., dss script based
    */   
  RTSC_FILE_IO = 3
    /**<
    * This indicates standare file IO operations
    */   
}fileIOtypes;

/** 
********************************************************************************
 *  @fn     my_initFileIO
 *  @brief  initializes the file IO system specific to the platform
 *          
 *  @param[in]  ioType : Indicates the kind of FILE IO type intended
 *
 *  @return     None
 *
********************************************************************************
*/
void my_initFileIO(XDAS_UInt32 ioType);

/** 
********************************************************************************
 *  @fn     my_fopen
 *  @brief  Interface function for standard fopen file
 *          
 *  @param[in]  filename : Pointer to the filename along with path
 *
 *  @param[in]  mode : Mode of the file to be opened (read,write,append...)
 *
 *  @param[in]  ioType : Indicates the kind of FILE IO type intended
 *
 *  @return     Pointer to file handle on successfull open
 *              NULL in case of error
 *
********************************************************************************
*/
FILE *my_fopen(const char *pInputFileName,const char *mode, XDAS_UInt32 ioType);

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
 *  @param[in]  ioType : Indicates the kind of FILE IO type intended
 *
 *  @return     number of bytes read
 *
********************************************************************************
*/
XDAS_UInt32 my_fread(void *pOutputPtr, XDAS_UInt32 uiSize, XDAS_UInt32 uiCount,
                     FILE *fp, XDAS_UInt32 ioType);

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
 *  @param[in]  ioType : Indicates the kind of FILE IO type intended
 *
 *  @return     number of bytes read
 *
********************************************************************************
*/
XDAS_UInt32 my_fwrite(const void *pInputPtr, XDAS_UInt32 uiSize,
                      XDAS_UInt32 uiCount, FILE *fp, XDAS_UInt32 ioType);

/** 
********************************************************************************
 *  @fn     my_fseek
 *  @brief  Interface function for standard fseek operation
 *          
 *  @param[in]  fp : Pointer to the file handle
 *
 *  @param[in]  uiOffset : Offset from the location
 *
 *  @param[in]  uiPosition : Poisition in file from where pointer to be moved
 *
 *  @param[in]  ioType : Indicates the kind of FILE IO type intended
 *
 *  @return     0 - when no error in closing file
 *              ErrorCode - when it encouters error while closing
 *
********************************************************************************
*/
XDAS_UInt32 my_fseek(FILE *fp, XDAS_UInt32 uiOffset, XDAS_UInt32 uiPosition,
                     XDAS_UInt32 ioType);

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
 *  @param[in]  ioType : Indicates the kind of FILE IO type intended
 *
 *  @return     0 - when no error in closing file
 *              ErrorCode - when it encouters error while closing
 *
********************************************************************************
*/
XDAS_Int32 my_fclose(FILE *fp, XDAS_UInt32 ioType);

/** 
********************************************************************************
 *  @fn     XDAS_UInt32 TestApp_FileLength(FILE *fp)
 *  @brief  Calculates the file size in bytes
 *          
 *  @param[in]  fp : File pointer for which size needs to be calculated
 *
 *  @param[in]  ioType : Indicates the kind of FILE IO type intended
 *
 *  @return    XDAS_UInt32 size of the file
 *             
********************************************************************************
*/
XDAS_UInt32 TestApp_FileLength(FILE *fp, XDAS_UInt32 ioType);


#endif

