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
* @file      jpegvdec_ti_configParser.c                         
*
* @brief     This file contains parsing routines for configuration file.
*
* @author    Odanaka
*
* @version 0.0 (Dec 2008) : Created the initial version.[Odanaka]
*
* @version 0.1 (Feb 2010) : Cleaned code to adhere for the coding guidelines
*                           [Chetan]  
*
*******************************************************************************
*/

/*----------------------compilation control switches -------------------------*/

/*******************************************************************************
*   INCLUDE FILES
*******************************************************************************/
/*--------------------- system and platform files ----------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/xdais/xdas.h>

/*----------------------program files ----------------------------------------*/
#include "jpegvdec_ti_hosttestapp.h"
#include "jpegvdec_ti_configparser.h"

/*******************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/
extern sTokenMapping sTokenMap[] ;

/*******************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/
static XDAS_Int8 buf[MAX_BUFF_FILE_SIZE];

/* ------------------------------ macros ------------------------------------ */

/* ------------------------ function prototypes ----------------------------- */
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
static XDAS_Int8 *GetConfigFileContent (FILE *fname)
{
  XDAS_Int32 FileSize;

  if (0 != fseek (fname, 0, SEEK_END))
  {
    return 0;
  }
  else
  {
    /* Nothing to execute*/
  }
  FileSize = ftell (fname);
  if (FileSize < 0 || FileSize > MAX_BUFF_FILE_SIZE)
  {
    return 0;
  }
  else
  {
    /* Nothing to execute*/
  }
  if (0 != fseek (fname, 0, SEEK_SET))
  {
    return 0;
  }
  else
  {
    /* Nothing to execute*/
  }

  /* -------------------------------------------------------------------------*/
  /* Note that ftell() gives us the file size as the file system sees it.     */
  /* The actual file size, as reported by fread() below will be often smaller */
  /* due to CR/LF to CR conversion and/or control characters after the the    */
  /* EOF marker in the file.                                                  */
  /* -------------------------------------------------------------------------*/
  FileSize = fread (buf,  sizeof(Uint8), FileSize, fname);
  buf[FileSize] = '\0';
  fclose (fname);
  return buf;
} /* GetConfigFileContent() */


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
static XDAS_Int32 ParameterNameToMapIndex(XDAS_Int8 *s)
{
  XDAS_Int32 i = 0;

  while(sTokenMap[i].tokenName != NULL)
  {
    if(0 == strcmp((const char *)sTokenMap[i].tokenName, (const char *)s))
    {
      return i;
    }
    else
    {
      i++;
    }
  }
  return -1;
} /* ParameterNameToMapIndex() */



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
static XDAS_Int32 ParseContent (XDAS_Int8 *buf, XDAS_Int32 bufsize)
{

  XDAS_Int8  *items[MAX_ITEMS_TO_PARSE];
  XDAS_Int32 MapIdx;
  XDAS_Int32 item     = 0;
  XDAS_Int32 InString = 0;
  XDAS_Int32 InItem   = 0;
  XDAS_Int8  *p       = buf;
  XDAS_Int8  *bufend  = &buf[bufsize];
  XDAS_Int32 IntContent;
  XDAS_Int32 i;
  FILE       *fpErr   = stderr;

  /*--------------------------------------------------------------------------*/
  /* Stage one: Generate an argc/argv-type list in items[], without           */
  /* comments  and whitespace.                                                */
  /* This is context insensitive and could be done most easily with lex(1)    */
  /*--------------------------------------------------------------------------*/

  while (p < bufend)
  {
    switch (*p)
    {
    case 13:
      p++;
      break;
    case '#': 
      /*----------------------------------------------------------------------*/
      /* Found comment Replace '#' with '\0'in case of comment                */
      /* immediately following integer or string Skip till                    */
      /*  EOL or EOF, whichever comes first                                   */
      /*----------------------------------------------------------------------*/
      *p = '\0';  
      while (*p != '\n' && p < bufend)
      {  
        p++;
      }
      InString = 0;
      InItem = 0;
      break;
    case '\n':
      InItem   = 0;
      InString = 0;
      *p++='\0';
      break;
    case ' ':
    case '\t':           
      /*----------------------------------------------------------------------*/
      /* Skip whitespace, leave state unchanged                               */
      /*----------------------------------------------------------------------*/
      if (InString)
      {
        p++;
      }
      else
      {     
        /*--------------------------------------------------------------------*/
        /* Terminate non-strings once whitespace is found                     */
        /*--------------------------------------------------------------------*/
        *p++ = '\0';
        InItem = 0;
      }
      break;

    case '"':               
      /*----------------------------------------------------------------------*/
      /* Begin/End of String                                                  */
      /*----------------------------------------------------------------------*/

      *p++ = '\0';
      if (!InString)
      {
        items[item++] = p;
        InItem = ~InItem;
      }
      else
      {
        InItem = 0;
      }
      InString = ~InString; /* Toggle                         */
      break;

    default:
      if (!InItem)
      {
        items[item++] = p;
        InItem = ~InItem;
      }
      else
      {
        /* Nothing to execute*/
      }
      p++;
    }
  }

  item--;

  for(i=0 ; i<item ; i += 3)
  {
    if(0 < (MapIdx = ParameterNameToMapIndex(items[i])))
    {
      
    }
    else
    {
      /* Nothing to execute*/
    }
    if (strcmp ("=", (const char *)items[i+1]))
    {
      fprintf(fpErr, 
      "\nfile:'=' expected as the second token in each line.");
      return -1 ;
    }
    else
    {
      /* Nothing to execute*/
    }
    sscanf ((const char *)items[i+2], "%d", &IntContent) ;
    * ((XDAS_Int32 *) (sTokenMap[MapIdx].place)) = IntContent;
  }
  return 0 ;
}  /* ParseContent () */



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
XDAS_Int32 readparamfile(FILE * fname)
{
  XDAS_Int8 *FileBuffer = NULL ;
  XDAS_Int32 retVal ; 

  /*--------------------------------------------------------------------------*/
  /* read the content in a buffer                                             */
  /*--------------------------------------------------------------------------*/
  FileBuffer = GetConfigFileContent(fname);
  if(FileBuffer)
  {
    retVal  = ParseContent(FileBuffer,strlen((const char *)FileBuffer));
    return retVal ;
  }
  else
  {
    return -1;
  }
} /* readparamfile(FILE * fname) */




