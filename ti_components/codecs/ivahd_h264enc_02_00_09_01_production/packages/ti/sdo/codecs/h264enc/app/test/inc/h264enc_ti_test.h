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
 * @file h264enc_ti_test.h                          
 *                                       
 * @brief This File contains function definitions for a standard 
 *        implementation of a test configuration file parser. 
 *        These functiosn parses the input  configuration files and 
 *        assigns user provided values to global instance structures
 *  
 *
 * @author: Rama Mohana Reddy (rama.mr@ti.com)
 *
 * @version 0.0 (Jan 2008) : Base version created
 *                           [Pramod]
 * @version 0.1 (Oct 2009) : Review and more commenting along with cleanup
 *                           [Rama Mohan]
 * @version 0.2 (July 2010) : Changes related to MV & SAD exposure
 *                            support[Nirmal]
 *****************************************************************************
*/
#ifndef _H264_ENC_TI_CONFIG_H_
#define _H264_ENC_TI_CONFIG_H_

#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <h264enc.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/** 
 *  Output buffer size, this buffer is used to place encoded data,should be 
 *  big enough to hold the size of  typical HD sequence
*/
#define OUTPUT_BUFFER_SIZE      0x0600000

/** 
 *  Analytic info output buffer size, this buffer is used to place MV & SAD of
 *  encoded frame, should be big enough to hold the size of  typical HD sequence
*/
#define ANALYTICINFO_OUTPUT_BUFF_SIZE      0x00028000

/**
 * META DATA index for user define SEI is fixed to 0 in this test application. 
 * But it can be any. This is to have simplified implemntation of test app 
*/
#define TEST_SEI_META_DATA_IDX   (0)

/**
 * META DATA index for user define SM is fixed to 1 in this test application. 
 * But it can be any. This is to have simplified implemntation of test app 
*/
#define TEST_UD_SM_META_DATA_IDX (1)


/**
 * Some Random number is given to this channel, just to test 
 * XDM_SETLATEACQUIREARG
*/
#define CHANNEL_ID 0x100

/**
 * Total number of blocks possible in a process call
 */ 
#define TOT_BLOCKS_IN_PROCESS 0x4000
#define MAX_ITEMS_TO_RUN 4

/** 
********************************************************************************
 *  @fn     TestApp_SetInitParams
 *  @brief  Function to set default parameters
 *          This function will set default params for params function and
 *          dynamicparams function. This must be called before parsing config
 *          file so that default values are set when config file does not 
 *          specify any value
 *          
 *  @param[in] params : pointer to the XDM params interface structure
 *
 *  @param[in] dynamicParams : Pointer to t he XDM dynamicparams structure
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void TestApp_SetInitParams(H264ENC_Params *params, 
                                          H264ENC_DynamicParams *dynamicParams);


/** 
********************************************************************************
 *  @fn     readparamfile
 *  @brief  Reads the entire param file contents into a global buffer,which is
 *          used for parsing and updates the params to given addresses.
 *          
 *  @param[in]  file name : Name of the configuration file with path
 *
 *  @return     0 - if successfully parsed all the elements in param file and 
 *                  their  values read into the memory addresses given in 
 *                  token mappign array.
 *             XDM_EFAIL - For any file read operation related errors or if 
 *                  unknown parameter names are entered or if the parameter 
 *                  file syntax is not in compliance with the below 
 *                  implementation.
********************************************************************************
*/

XDAS_Int32 readparamfile(XDAS_Int8 *configFile);

/** 
********************************************************************************
 *  @fn     H264ENC_TI_Report_Error
 *  @brief  This function will print error messages
 *          
 *          This function will check for codec errors which are mapped to 
 *          extended errors in videnc2status structure and prints them in cosole
 *          Returns XDM_EFAIL in case of fatal error
 *
 *  @param[in]  uiErrorMsg  : Extended error message
 *
 *  @param[in]  fTrace_file : File pointer to the trace log file
 *
 *  @return     XDM_EOK -  when there is no fatal error
 *              XDM_EFAIL - when it is fatal error
********************************************************************************
*/

XDAS_Int32 H264ENC_TI_Report_Error(FILE * fTrace_file,XDAS_Int32 uiErrorMsg);

void H264ENC_TI_IntraRestrictDump();
void H264ENC_TI_PredictorDump();
void printDTCMAddresses(int addr, int size, char** fieldName);

#endif /* #ifndef _H264_ENC_TI_CONFIG_H_ */
