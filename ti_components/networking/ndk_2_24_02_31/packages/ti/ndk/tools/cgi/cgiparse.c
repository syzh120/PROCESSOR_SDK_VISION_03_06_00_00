/*
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 * ======== cgiparse.c ========
 *
 * Basic CGI Parsing functions.
 *
 */


#include <netmain.h>
#include <_stack.h>
#include "cgiparse.h"

#include <stdlib.h>

/*
 * cgiParseVars()
 * Reads input from a CGI post operation in pointed to by PostIn and
 * returns in sequence a pointer the name and then the value of each
 * post entry. This function modifies the data in PostIn. It also
 * returns the current parsing position in the variable pParseIndex.
 * The parse index must be set to 0 on initial call.
 */
char *cgiParseVars(char PostIn[], int *pParseIndex )
{
  int  out;
  int  in;
  char hexch;
  char hexval[3];
  int start;
  char ch;

  /* Get the current parse index. On the first call, it */
  /* must be zero. */
  in = *pParseIndex;

  hexval[2] = '\0';
  if( in == 0 )
    out = 0;
  else if( in == -1 )
    return NULL;
  else
    out = ++in;

  start = in;
  while (((ch = PostIn[in]) != '=') && (ch != '&') && (ch != '\0'))
  {
    if (ch == '+')
      PostIn[out++] = ' ';
    else if (ch == '%')
    {
      hexval[0] = PostIn[++in];
      hexval[1] = PostIn[++in];
      hexch = (char) strtol(hexval, NULL, 16);
      PostIn[out++] = hexch;
     }
     else
      PostIn[out++] = ch;
    in++;
  }

  /* If we got to the end of the string, set the parse index to -1 */
  if( ch == '\0' )
      in = -1;

  /* Null terminate the result string */
  PostIn[out++] = '\0';

  /* Save the value of the current parse index */
  *pParseIndex = in;

  /* Return a pointer to the start of the result string */
  return (&PostIn[start]);
}
