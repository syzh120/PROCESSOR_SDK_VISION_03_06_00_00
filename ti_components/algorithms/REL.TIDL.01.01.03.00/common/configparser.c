/*
 *
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the  
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/**
 *  @file       configparser.c
 *
 *  @brief      This file implements routines for config parser for test app
 *  @version    1.0 (July 2014) : Implemented support for MULTI input (array)
 *              read for integral data types
 *  @version    1.1 (Sep 2014) : Added support to print the config params
 */

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "ti_file_io.h"
#include "configparser.h"

static int filelength(TI_FILE *fp)
{
  int len;
  if(fp == NULL) return 0;
  FSEEK(fp, 0, SEEK_END);
  len = FTELL(fp);
  FSEEK(fp, 0, SEEK_SET);
  return len;
}

/**
********************************************************************************
 *  @fn     ParameterNameToMapIndex
 *  @brief  Returns the index number from sTokenMap for a given parameter name.
 *
 *
 *  @param[in]  s  : pointer to the TokenMap string to be searched
 *
 *  @return i  : Index number if it finds the sring in token map structure
 *               -1 in case it does not find string in tokem map structure
********************************************************************************
*/

static int ParameterNameToMapIndex (char *s, sTokenMapping *sTokenMap)
{
  int i = 0;

  while ((sTokenMap + i)->tokenName != NULL)
  {
    if (0==strcmp((const char *)(sTokenMap + i)->tokenName, (const char *)s))
      return i;
    else
      i++;
  }

  return -1;
}/* ParameterNameToMapIndex */

 /**
********************************************************************************
 *  @fn     ParseContent
 *  @brief  Parses the character array buf and writes global variable input,
 *          which is defined above. This hack will continue to be
 *          necessary to facilitate the addition of new parameters through the
 *          sTokenMap[] mechanism-Need compiler-generated addresses in sTokenMap
 *
 *
 *  @param[in]  buf : buffer to be parsed
 *
 *  @param[in]  bufsize : size of the buffer
 *
 *  @return     0 - if successfully parsed all the elements in param file and
 *                  their  values read into the memory addresses given in
 *                  token mappign array.
 *             -1 - For any file read operation related errors or if
 *                  unknown parameter names are entered or if the parameter
 *                  file syntax is not in compliance with the below
 *                  implementation.
********************************************************************************
*/

static int ParseContent (unsigned char *buf, int bufsize, sTokenMapping *sTokenMap)
{
  char lineEnd[] = "LINEEND" ;
  /*--------------------------------------------------------------------------*/
  /* Total number of parameter initialisation lines in the file this          */
  /* excludes comment lines and blank lines if any                            */
  /*--------------------------------------------------------------------------*/
  char *items[MAX_ITEMS_TO_PARSE];
  int item = 0;
  /*--------------------------------------------------------------------------*/
  /* Index into the token map array - into which the corresponding            */
  /* parameter values needs to be initialised  from the param file            */
  /*--------------------------------------------------------------------------*/
  int MapIdx;
  /*--------------------------------------------------------------------------*/
  /* Flags which indicate the current state of the state machine              */
  /* InString - indicates that buffer pointer is currently in between         */
  /* a valid string, which inturn can contain multiple items.                 */
  /* InItem - indicates that buffer pointer is within a valid item            */
  /*--------------------------------------------------------------------------*/
  int InString = 0, InItem = 0;
  /*--------------------------------------------------------------------------*/
  /* Dynamic pointer movign allong the param file buffer byte-by-byte         */
  /*--------------------------------------------------------------------------*/
  char *p = (char*) buf;
  /*--------------------------------------------------------------------------*/
  /* end of buffer - used for terminating the parse loop                      */
  /*--------------------------------------------------------------------------*/
  char *bufend = (char*) &buf[bufsize];
  /*--------------------------------------------------------------------------*/
  /* Parameter value read from the file and loop counter                      */
  /*--------------------------------------------------------------------------*/
  int IntContent;
  float floatContent;
  int i, k, assignData;
  int lastElementSpace = 0 ;

  /*--------------------------------------------------------------------------*/
  /*                                STAGE ONE                                 */
  /* Generate an argc/argv-type list in items[], without comments and         */
  /* whitespace. This is context insensitive and could be done most easily    */
  /* with lex(1).                                                             */
  /*--------------------------------------------------------------------------*/
  while (p < bufend)
  {
    switch (*p)
    {
      /*----------------------------------------------------------------------*/
      /* blank space - skip the character and go to next                      */
      /*----------------------------------------------------------------------*/
      case 13:
        p++;
        lastElementSpace = 0 ;
      break;
      /*----------------------------------------------------------------------*/
      /* Found a comment line skip all characters until end-of-line is found  */
      /*----------------------------------------------------------------------*/
      case '#':
        /*--------------------------------------------------------------------*/
        /* Replace '#' with '\0' in case of comment immediately following     */
        /* integer or string Skip till EOL or EOF, whichever comes first      */
        /*--------------------------------------------------------------------*/
        *p = '\0';
        while (*p != '\n' && p < bufend)
          p++;
        lastElementSpace = 0 ;
      break;
      /*----------------------------------------------------------------------*/
      /* end of line - skip the character and go to next,reset the InItem flag*/
      /* to indicate that we are not in any valid item                        */
      /*----------------------------------------------------------------------*/
      case '\n':
        if(InItem || lastElementSpace == 1) items[item++] = lineEnd;
        InItem = 0;
        InString = 0;
        *p++='\0';
        lastElementSpace = 0 ;
      break;
      /*----------------------------------------------------------------------*/
      /* Whitespaces and tabs indicate end of an item                         */
      /*----------------------------------------------------------------------*/
      case ' ':
      case '\t':
        /*--------------------------------------------------------------------*/
        /* if the state machine is within a string Skip whitespace,           */
        /* leave state unchanged                                              */
        /* else Terminate non-strings once whitespace is found                */
        /*--------------------------------------------------------------------*/
        if (InString)
          p++;
        else
        {
          *p++ = '\0';
          InItem = 0;
        }
        lastElementSpace = 1 ;
      break;
      /*----------------------------------------------------------------------*/
      /* begining or end of string - toggle the string indication flag        */
      /*----------------------------------------------------------------------*/
      case '"':
        *p++ = '\0';
        if (!InString)
        {
          items[item++] = p;
          assert(item < MAX_ITEMS_TO_PARSE);
          InItem = ~InItem;
        }
        else
          InItem = 0;
        InString = ~InString;
        lastElementSpace = 0 ;
      break;
      /*----------------------------------------------------------------------*/
      /* Any othe character is taken into the item provided the state machine */
      /* is within a valid Item                                               */
      /*----------------------------------------------------------------------*/
    default:
      if (!InItem)
      {
        items[item++] = p;
        assert(item < MAX_ITEMS_TO_PARSE);
        InItem = ~InItem;
      }
      lastElementSpace = 0 ;
      p++;
    }
  }
  item--;
  /*--------------------------------------------------------------------------*/
  /* for all the items found - check if they correspond to any valid parameter*/
  /* names specified by the user through token map array,                     */
  /* Note: Contigous three items are grouped into triplets. Thsi oredered     */
  /* triplet is used to identify the valid parameter entry in the Token map   */
  /* array.                                                                   */
  /* First item in the triplet has to eb a parameter name.                    */
  /* Second item has to be a "=" symbol                                       */
  /* Third item has to be a integer value.                                    */
  /* Any violation of the above order in the triplets found would lead        */
  /* to error condition.                                                      */
  /*--------------------------------------------------------------------------*/
  for (i=0; i<item; )
  {
    /*------------------------------------------------------------------------*/
    /* Get the map index into the token map array - corresponding to the      */
    /* first item - in a item-triplet                                         */
    /*------------------------------------------------------------------------*/
    if (0 <= (MapIdx = ParameterNameToMapIndex (items[i], sTokenMap)))
    {
      /*----------------------------------------------------------------------*/
      /* Assert if the second item is indeed "=" symbol                       */
      /*----------------------------------------------------------------------*/
      if (strcmp ((const char *)"=", (const char *)items[i+1]))
      {
        printf(
          "\nfile: '=' expected as the second token in each line.");
        return -1;
      }
      /*----------------------------------------------------------------------*/
      /* depending upon the type of content convert them and populate the     */
      /* corresponding entry in the token map array with this value           */
      /*----------------------------------------------------------------------*/
      i = i + 2 ;
      if(sTokenMap[MapIdx].type == STRING)
      {
        strcpy((char *)sTokenMap[MapIdx].place, (char *)items[i]);
        if(sTokenMap[MapIdx].valCat == MULTI)
        {
          printf("\n MULTI is not supported for strings - picking up only first value");
        }
      }

      else
      {
        k = 0;
        assignData=  1;
        do
        {
          if(assignData)
          {
            if (sTokenMap[MapIdx].type == INT_32)
            {
              sscanf ((const char *)items[i], "%d", (&IntContent));
              * ((int *) (sTokenMap[MapIdx].place) + k) = IntContent;
            }
            else if (sTokenMap[MapIdx].type == INT_16)
            {
              sscanf ((const char *)items[i], "%d", &IntContent);
              * ((short *) (sTokenMap[MapIdx].place) + k) = IntContent;
            }
            else if (sTokenMap[MapIdx].type == INT_8)
            {
              sscanf ((const char *)items[i], "%d", &IntContent);
              * ((unsigned char *) (sTokenMap[MapIdx].place) + k) = IntContent;
            }
            else if (sTokenMap[MapIdx].type == FLOAT)
            {
              sscanf ((const char *)items[i], "%f", &floatContent);
              * ((float *) (sTokenMap[MapIdx].place) + k) = floatContent;
            }
            else
            {
              printf("\nParameter Name '%s' not recognized...  \n", items[i]);
              break;
            }
          }
          k++;
          i++;
          if(sTokenMap[MapIdx].valCat != MULTI)
          {
            assignData = 0 ;
          }
        } while (strcmp(items[i], lineEnd) );
      }
    }
    i++;
  }
  return 0 ;
}/* ParseContent */


int readparamfile(char *configFile, sTokenMapping *sTokenMap)
{
  unsigned char *fileBuffer = NULL;
  int  retVal, fileSize ;
  TI_FILE       *fConfigFile;
  /*--------------------------------------------------------------------------*/
  /*  Open Test Config File                                                   */
  /*--------------------------------------------------------------------------*/
  fConfigFile = FOPEN((char *)configFile,"r");
  /*--------------------------------------------------------------------------*/
  /*  Perform file open error check.                                          */
  /*--------------------------------------------------------------------------*/
  if (!fConfigFile)
  {
    printf("Couldn't open Parameter Config file %s.\n",configFile);
    return -1;
  }
  /*--------------------------------------------------------------------------*/
  /* read the content in a buffer                                             */
  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/
  /* Allocate the buffer with size as file size                               */
  /* One byte extra allocated to insert end of string delimeter               */
  /*--------------------------------------------------------------------------*/
  fileSize = filelength (fConfigFile);
  fileBuffer = (unsigned char*) malloc(fileSize + 2);
  if (fileBuffer == NULL)
  {
    fprintf(stdout, "No Enough memory for Config Buffer");
    return -1 ;
  }
  memset(fileBuffer, 0, fileSize + 2);
  FREAD (fileBuffer, 1, fileSize, fConfigFile);
  /*--------------------------------------------------------------------------*/
  /* Put end of string marker and end of Line if not present                  */
  /*--------------------------------------------------------------------------*/
  if(fileBuffer[fileSize-1] !='\n')
  {
   fileBuffer[fileSize] = '\n';
   fileSize++;
  }
  fileBuffer[fileSize] = '\0';

  /*--------------------------------------------------------------------------*/
  /*    Close Config Parameter File.                                          */
  /*--------------------------------------------------------------------------*/
  FCLOSE(fConfigFile);

  /*------------------------------------------------------------------------*/
  /* Parse every string into items and group them into triplets.            */
  /* Decode these ordered triplets into correspondign indices in the global */
  /* Token Map arrray provided by the user.                                 */
  /*------------------------------------------------------------------------*/
  retVal  = ParseContent(fileBuffer,fileSize, sTokenMap);

  /*------------------------------------------------------------------------*/
  /* Free the buffer allocated in "GetConfigFileContent" function           */
  /*------------------------------------------------------------------------*/
  free(fileBuffer) ;
  return retVal;

}/* readparamfile */

static void sortTokenMapInr(sTokenMapping * sTokenMap,int numToken)
{
  int i,j;
  sTokenMapping temp;
  for(i = 0; i < numToken-1; i++)
  {
    for(j = i+1; j < numToken; j++)
    {
      if(((uintptr_t)(sTokenMap[j].place)) < ((uintptr_t)(sTokenMap[i].place)))
      {
        temp = sTokenMap[i];
        sTokenMap[i] = sTokenMap[j];
        sTokenMap[j] = temp;
      }
    }
  }
}

static void sortTokenMapDcr(sTokenMapping * sTokenMap,int numToken)
{
  int i,j;
  sTokenMapping temp;
  for(i = 0; i < numToken-1; i++)
  {
    for(j = i+1; j < numToken; j++)
    {
      if(((uintptr_t)(sTokenMap[j].place)) > ((uintptr_t)(sTokenMap[i].place)))
      {
        temp = sTokenMap[i];
        sTokenMap[i] = sTokenMap[j];
        sTokenMap[j] = temp;
      }
    }
  }
}

void printparams(sTokenMapping * sTokenMap,int numToken, unsigned int stratAddr, unsigned int size)
{
  int i,j;
  ptrdiff_t numEntries;
  uintptr_t endAddr;

  sortTokenMapInr(sTokenMap,numToken);

  for(i = 0; i < numToken; i++)
  {
    if((((uintptr_t)(sTokenMap[i].place)) >= (uintptr_t)stratAddr) && ((uintptr_t)(sTokenMap[i].place)) < ((uintptr_t)stratAddr+(uintptr_t)size))
    {
      if((i+1) < numToken)
      {
        endAddr = ((uintptr_t)(sTokenMap[i+1].place)) ;
      }
      else
      {
        endAddr = (stratAddr+size) ;
      }
      numEntries = (ptrdiff_t)(endAddr - ((uintptr_t)(sTokenMap[i].place)));

      if(sTokenMap[i].type == STRING)
      {
        printf("\nTEST_REPORT_CONFIG_STRING : %s = %s\n",sTokenMap[i].tokenName, (char*)sTokenMap[i].place);
      }
      else if(sTokenMap[i].type == INT_8)
      {
        char * ptr = (char *)sTokenMap[i].place;
        printf("\nTEST_REPORT_CONFIG_INT8 : %s = ",sTokenMap[i].tokenName);
        if(sTokenMap[i].valCat == MULTI)
        {
          numEntries = numEntries/1;
        }
        else
        {
          numEntries = 1;
        }
        for(j = 0; j < numEntries; j++)
        {
          printf(" %d", ptr[j]);
        }
      }
      else if(sTokenMap[i].type == INT_16)
      {
        short * ptr = (short *)sTokenMap[i].place;
        printf("\nTEST_REPORT_CONFIG_INT16 : %s = ",sTokenMap[i].tokenName);
        if(sTokenMap[i].valCat == MULTI)
        {
          numEntries = numEntries/2;
        }
        else
        {
          numEntries = 1;
        }
        for(j = 0; j < numEntries; j++)
        {
          printf(" %d", ptr[j]);
        }
      }
      else if(sTokenMap[i].type == INT_32)
      {
        int * ptr = (int *)sTokenMap[i].place;
        printf("\nTEST_REPORT_CONFIG_INT32 : %s = ",sTokenMap[i].tokenName);
        if(sTokenMap[i].valCat == MULTI)
        {
          numEntries = numEntries/4;
        }
        else
        {
          numEntries = 1;
        }
        for(j = 0; j < numEntries; j++)
        {
          printf(" %d", ptr[j]);
        }
      }
      else if(sTokenMap[i].type == FLOAT)
      {
        float * ptr = (float *)sTokenMap[i].place;
        printf("\nTEST_REPORT_CONFIG_FLOAT : %s = ",sTokenMap[i].tokenName);
        if(sTokenMap[i].valCat == MULTI)
        {
          numEntries = numEntries/4;
        }
        else
        {
          numEntries = 1;
        }
        for(j = 0; j < numEntries; j++)
        {
          printf(" %f", ptr[j]);
        }
      }
      printf("\n");

    }

  }
  sortTokenMapDcr(sTokenMap,numToken);

}


#pragma RESET_MISRA ("required")
