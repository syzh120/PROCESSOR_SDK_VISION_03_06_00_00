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
********************************************************************************
* @file <TestappConfigparser.c>                          
*                                       
* @brief This file contains the following functions of the application.
*
*          1. Wrapper function for getting config file contents
*          2. Function for reading the config file
*          3. Function for parsing the read contents using a table map
*
* @author: Shyam Jagannathan
*
* @version 0.0 (21-06-2006) : Created
*                             [Shyam Jagannathan]
* @version 0.1 (04-04-2007) : Commented and cleaned the code
*                             [Srenivas Varadarajan]
* @version 0.2 (Jul 2010)   : Modified to support string entries in config file
*                             [Ramakrishna Adireddy]
*******************************************************************************
*/

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/*!
 * ----------------------- SYSTEM AND PLATFORM FILES --------------------------
 */
/*!
 * ------------------------------ PROGRAM FILES -------------------------------
 */
/* ------------------------------------------------------------------------- */
/*  Client header file                                                       */
/* ------------------------------------------------------------------------- */
#include <xdc/std.h>
#include <TestAppDecoder.h>

/******************************************************************************
*               PUBLIC DECLARATIONS Defined here, used elsewhere
******************************************************************************/

/*!
 * ---------------------------- DATA DECLARATIONS -----------------------------
 */
#define MAX_ITEMS_TO_PARSE  1000

/* -------------------------------------------------------------------------- */
/*  Array of structures for capturing the input from config file              */
/* -------------------------------------------------------------------------- */

#ifdef _TMS320C6X
extern far sTokenMapping sTokenMap[] ;
#else
extern sTokenMapping sTokenMap[] ;
#endif

static XDAS_Int8 buf[20000];

/** 
********************************************************************************
 *  @fn     GetConfigFileContent
 *  @brief  TThe function reads the configuration file content in a buffer 
 *          and returns the address of the buffer. 
 *          
 *  @param[in] fname    : name of the config file to be parsed.
 *          
 *  @return Pointer to the buffer; 0 if an error in reading it.
********************************************************************************
*/
static XDAS_Int8 *GetConfigFileContent (FILE *fname)
{
  XDAS_Int32 FileSize;

  if (0 != fseek (fname, 0, SEEK_END))
  {
    return 0;
  }

  FileSize = ftell (fname);
  if (FileSize < 0 || FileSize > 20000)
  {
    return 0;

  }
  if (0 != fseek (fname, 0, SEEK_SET))
  {
    return 0;
  }

  /* ------------------------------------------------------------------------ */
  /* Note that ftell() gives us the file size as the file system sees it.     */
  /* The actual file size, as reported by fread() below will be often smaller */ 
  /* due to CR/LF to CR conversion and/or control characters after the dos    */
  /* EOF marker in the file.                                                  */
  /* ------------------------------------------------------------------------ */
  FileSize = fread (buf, 1, FileSize, fname);
  buf[FileSize] = '\0';

  fclose (fname);

  return buf;
}

/** 
********************************************************************************
 *  @fn     ParameterNameToMapIndex
 *  @brief  The function  Returns the index number from sTokenMap[] for a given
 *          parameter name.
 *          
 *  @param[in] s    : parameter name,string.
 *          
 *  @return Index number in the table if the string is a valid parameter name
 *          else -1 for error 
********************************************************************************
*/
static XDAS_Int32 ParameterNameToMapIndex (XDAS_Int8 *s)
{
  XDAS_Int32 i = 0;

  while (sTokenMap[i].tokenName != NULL)
    if (0 == strcmp ((const char *)(sTokenMap[i].tokenName), (const char *)s))
      return i;
    else
      i++;
  return -1;
}
 
/** 
********************************************************************************
 *  @fn     ParseContent
 *  @brief  Parses the character array buf and writes global variable input, 
 *          which is defined in configfile.h.  This hack will continue to be 
 *          necessary to facilitate the addition of new parameters through the 
 *          sTokenMap[] mechanism-Need compiler-generated addresses in sTokenMap
 *          
 *  @param[in] buf        : Buffer to be parsed.
 *  @param[in] bufsize    : Size of the buffer.
 *          
 *  @return status ( PASS/ FAIL)
********************************************************************************
*/
static XDAS_Int32 ParseContent (XDAS_Int8 *buf, XDAS_Int32 bufsize)
{

  XDAS_Int8 *items[MAX_ITEMS_TO_PARSE];
  XDAS_Int32 MapIdx;
  XDAS_Int32 item = 0;
  XDAS_Int32 InString = 0, InItem = 0;
  XDAS_Int8 *p = buf;
  XDAS_Int8 *bufend = &buf[bufsize];
  XDAS_Int32 IntContent;
  XDAS_Int32 i;
  FILE *fpErr = stderr;


  /* ---------------------------------------------------------------------- */
  /* Stage one: Generate an argc/argv-type list in items[], without comments*/
  /* and whitespace.This is context insensitive and could be done most      */
  /* easily with lex(1).                                                    */                                                 
  /* ---------------------------------------------------------------------- */

  while (p < bufend)
  {
    switch (*p)
    {
    case 13:
      p++;
      break;
      /* ------------------------------------------------------------------ */
      /* Found comment.Replace '#' with '\0' in case of comment             */
      /* immediately following integer or string                            */
      /* ------------------------------------------------------------------ */
    case '#':     
      *p = '\0';   
      
      /* ---------------------------------------------------------------- */
      /* Skip till EOL or EOF, whichever comes first                      */
      /* ---------------------------------------------------------------- */  
      while (*p != '\n' && p < bufend)  
        p++;
      InString = 0;
      InItem = 0;
      break;
    case '\n':
      InItem = 0;
      InString = 0;
      *p++='\0';
      break;
      /* ------------------------------------------------------------------ */
      /*   Skip whitespace, leave state unchanged                           */
      /* ------------------------------------------------------------------ */
    case ' ':
    case '\t':              
      if (InString)
        p++;
      else
      { 
        /* -------------------------------------------------------------- */
        /* Terminate non-strings once whitespace is found                 */
        /* -------------------------------------------------------------- */
        *p++ = '\0';
        InItem = 0;
      }
      break;

      /* ------------------------------------------------------------------ */
      /*   Begin/End of String                                              */
      /* ------------------------------------------------------------------ */
    case '"':               
      *p++ = '\0';
      if (!InString)
      {
        items[item++] = p;
        InItem = ~InItem;
      }
      else
        InItem = 0;

      /* ---------------------------------------------------------------- */
      /*   Toggle                                                         */
      /* ---------------------------------------------------------------- */
      InString = ~InString; 
      break;

    default:
      if (!InItem)
      {
        items[item++] = p;
        InItem = ~InItem;
      }
      p++;
    }
  }

  item--;

  for (i=0; i<item; i+= 3)
  {
    if (0 > (MapIdx = ParameterNameToMapIndex (items[i])))
    {
      fprintf(fpErr, " \nParameter Name '%s' not recognized.. ", items[i]);
      return -1 ;

    }
    if (strcmp ("=", (const char *)items[i+1]))
    {
      fprintf(fpErr, " \nfile: '=' expected as the second token in each line.");
      return -1 ;
    }

    /*----------------------------------------------------------------------*/
    /* depending upon the type of content convert them and populate the     */
    /* corresponding entry in the token map array with this value           */
    /*----------------------------------------------------------------------*/
    if(sTokenMap[MapIdx].type != 0)
    {
      strcpy((char *)sTokenMap[MapIdx].place, (char *)items[i+2]);
    }
    else
    {
      sscanf ((const char *)items[i+2], "%d", &IntContent) ;
      * ((XDAS_Int32 *) (sTokenMap[MapIdx].place)) = IntContent;
    }
  }
  return 0 ;
}
/** 
********************************************************************************
 *  @fn     readparamfile
 *  @brief  Wrapper function for getting config file contents
 *          
 *  @param[in] fname      : name of the config file to be parsed.
 *          
 *  @return status ( PASS/ FAIL)
********************************************************************************
*/
XDAS_Int32 readparamfile(FILE * fname)
{
  XDAS_Int8 *FileBuffer = NULL ;
  XDAS_Int32 retVal ; 

  /* ----------------------------------------------------------------------- */
  /* read the content in a buffer                                            */
  /* ----------------------------------------------------------------------- */
  FileBuffer = GetConfigFileContent(fname);

  if(FileBuffer)
  {
    retVal  = ParseContent(FileBuffer,strlen((const char *)FileBuffer));
    return retVal ;
  }
  else
    return -1;
}



