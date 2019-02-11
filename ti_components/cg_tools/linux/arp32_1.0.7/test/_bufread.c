/*****************************************************************************/
/*  _BUFREAD.C v1.0.7                                                        */
/*                                                                           */
/* Copyright (c) 1995-2015 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/
 
/*****************************************************************************/
/* Functions:                                                                */
/*    _BUFF_READ  -  Fill a stream's buffer from its file                    */
/*****************************************************************************/
#include <stdio.h>
#include <_data_synch.h>
#include "file.h"

extern _DATA_ACCESS int  _ft_end;
extern _CODE_ACCESS int  _doflush(FILE *_fp);

_CODE_ACCESS void _buff_read(FILE *_fp);


/*****************************************************************************/
/* _BUFF_READ  -   Fill a stream's buffer from its file                      */
/*                                                                           */
/*    This function fills stream _FP's buffer with the contents of the file  */
/*    it is associated with.  It returns nothing, but sets flags in the      */
/*    stream if any I/O errors occur.                                        */
/*                                                                           */
/*    For multi-threaded applications, this function should always be called */
/*    within a critical section that guarantees single-threaded access to    */
/*    the __TI_LOCK_FILE_TBL resources (_ftable[], _ft_end, and _tmpnams[]). */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS void _buff_read(FILE *_fp)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   int   errchk,
         j,
         buffer_size    = _fp->bufend - _fp->buf;

   /*------------------------------------------------------------------------*/
   /* If this is a line buffered stream, flush all line buffered streams.    */
   /*------------------------------------------------------------------------*/
   if (_BUFFMODE(_fp) == _IOLBF)
   {
       for (j=0; j < _ft_end; j++)
	   if (_BUFFMODE(&_ftable[j]) == _IOLBF)
	       _doflush(&_ftable[j]);

       /*--------------------------------------------------------------------*/
       /* Callers to _buff_read() will keep _ftable[] in synch, but we will  */
       /* handle synchronization of _ft_end here.                            */
       /*--------------------------------------------------------------------*/
       __TI_data_synch_WBINV(&_ft_end, sizeof(_ft_end));
   }

   /*------------------------------------------------------------------------*/
   /* Read in the next characters from the file.                             */
   /*------------------------------------------------------------------------*/
   errchk = read(_fp->fd, (char *)_fp->buf, buffer_size);

   /*------------------------------------------------------------------------*/
   /* Adjust the buffer pointers.                                            */
   /*------------------------------------------------------------------------*/
   _fp->buff_stop = _fp->buf + errchk;
   _fp->pos = _fp->buf;

   /*------------------------------------------------------------------------*/
   /* Set any error flags if necessary.                                      */
   /*------------------------------------------------------------------------*/
   switch (errchk)
   {
      case -1 : _SET(_fp, _STATERR);
                break;
 
      case 0  : _SET(_fp, _STATEOF);
                break;
   }

   return;
 
}
 
