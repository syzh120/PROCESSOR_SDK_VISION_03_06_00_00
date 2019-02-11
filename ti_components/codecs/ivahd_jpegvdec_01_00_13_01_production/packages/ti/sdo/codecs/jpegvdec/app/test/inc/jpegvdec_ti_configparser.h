/*
********************************************************************************  
* HDVICP2.0 Based JPEG Decoder
*
* "HDVICP2.0 Based JPEG Decoder" is software module developed on
* TI's HDVICP2 based SOCs. This module is capable of generating a raw image 
* by de-compressing/decoding a jpeg bit-stream based on ISO/IEC IS 10918-1. 
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
* ALL RIGHTS RESERVED 
********************************************************************************
*/

/**  
********************************************************************************
* @file      jpegvdec_ti_configparser.h                      
*
* @brief     This file contains parsing routines for configuration file.
*
* @author    Chetan
*
* @version 0.0 (Dec 2008) : Created the initial version.[Odanaka]
*
* @version 0.1 (Feb 2010) : Cleaned code to adhere for the coding guidelines
*                           [Chetan] 
********************************************************************************
*/

/*----------------------compilation control switches -------------------------*/

/*******************************************************************************
*   INCLUDE FILES
*******************************************************************************/
/*--------------------- system and platform files ----------------------------*/

/*----------------------program files ----------------------------------------*/

/*******************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/*******************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/* ---------------------------- macros ------------------------------------ */
#ifndef _JPEGVDEC_TI_CONFIG_PARSER_H__
#define _JPEGVDEC_TI_CONFIG_PARSER_H__

#define MAX_BUFF_FILE_SIZE (20000)

/**
********************************************************************************
*  @fn          GetConfigFileContent(FILE *fname)
*
*  @brief       This function Reads the configuration file content in a buffer  
*               and returns theaddress
*
*  @param [in]  fname             :  name of the config file to be parsed
*
*  @return      Pointer to the buffer; 0 if an error in reading it.
********************************************************************************
*/
static XDAS_Int8 *GetConfigFileContent (FILE *fname);

/**
********************************************************************************
*  @fn          ParameterNameToMapIndex(XDAS_Int8 *s)
*
*  @brief       The function  Returns the index number from sTokenMap[] for a 
*               given parameter name.
*
*  @param [in]  s                 :  name string.
*
*  @return      Index number if the string is a valid parameter name,
*               -1 for error 
********************************************************************************
*/
static XDAS_Int32 ParameterNameToMapIndex(XDAS_Int8 *s);

/**
********************************************************************************
*  @fn          ParseContent(XDAS_Int8 *buf, XDAS_Int32 bufsize)
*
*  @brief       Parses the character array buf and writes global variable 
*               input, which is defined in configfile.h.  This hack will 
*               continue to be  necessary to facilitate the addition of new 
*               parameters through the  sTokenMap[] mechanism-Need 
*               compiler-generated addresses in  sTokenMap
*
*  @param [in]  buf               :  buffer to be parsed.
*
*  @param [in]  bufsize           :  size of buffer.
*
*  @return      status            :  ( PASS/ FAIL)  
********************************************************************************
*/
static XDAS_Int32 ParseContent (XDAS_Int8 *buf, XDAS_Int32 bufsize);

/**
********************************************************************************
*  @fn          readparamfile(FILE * fname)
*
*  @brief       Wrapper function for getting config file contents
*
*  @param [in]  fname             :  name of the config file to be parsed
*
*  @return      status            :  ( PASS/ FAIL)  
********************************************************************************
*/
XDAS_Int32 readparamfile(FILE * fname);

#endif /*_JPEGVDEC_TI_CONFIG_PARSER_H__*/
