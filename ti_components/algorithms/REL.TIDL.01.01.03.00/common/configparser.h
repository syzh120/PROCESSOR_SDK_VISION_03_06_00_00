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


#ifndef _CONFIGPARSER_H_
#define _CONFIGPARSER_H_

#define MAX_ITEMS_TO_PARSE (512)

typedef enum
{
  STRING   = 0,
  INT_8    = 1,
  INT_16   = 2,
  INT_32   = 3,
  FLOAT    = 4

}einfoType ;
typedef char infoType_t ;

typedef enum
{
  SINGLE   = 0,
  MULTI    = 1

}eValueCategory ;

typedef char valueCategory_t ;


 /**
 *******************************************************************************
 *  @struct sTokenMapping
 *  @brief  Token Mapping structure for parsing codec specific configuration file
 *
 *  @param  tokenName : Name of the parameter in config file exposed to user
 *  @param  place : Place holder for the data
 *  @param  type : Variable to specify whether the parameter is string or number
 *                 With the help of this parser function will use either memcpy
 *                 or fscanf fucntions
 *
 *******************************************************************************
*/



typedef struct {
  char           *tokenName;
  void           *place;
  infoType_t      type;
  valueCategory_t valCat ;
} sTokenMapping;


int readparamfile(char *configFile, sTokenMapping *sTokenMap);

void printparams(sTokenMapping * sTokenMap,int numToken, unsigned int stratAddr, unsigned int size);

#endif
