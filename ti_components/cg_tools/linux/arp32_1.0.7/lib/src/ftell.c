/*****************************************************************************/
/*  FTELL.C v1.0.7                                                           */
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
#include <errno.h>
#include <stdio.h>
#include <_mutex.h>
#include <_data_synch.h>
#include "file.h"

/*****************************************************************************/
/* FTELL -  Get the location of the file pointer in a stream                 */
/*                                                                           */
/*    This function gets the current location of the file pointer for the    */
/*    given stream, and returns it after adjusting it for any inaccuracies   */
/*    that buffering might have caused.                                      */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS long ftell(FILE *_fp)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   fpos_t  _pos;
   int   adjust   = 0;

   /*------------------------------------------------------------------------*/
   /* The current thread in a multi-threaded application must protect access */
   /* to __TI_LOCK_FILE_TBL shared resources (_ftable[], _ft_end, and        */
   /* _tmpnams[]). In this case, _ftable[] may be updated, so we must ensure */
   /* that the local copy of _ftable[] is flushed to shared memory before    */
   /* leaving the critical section (invalidated if it is not modified).      */
   /*------------------------------------------------------------------------*/
   __TI_resource_lock(__TI_LOCK_FILE_TBL);

   /*------------------------------------------------------------------------*/
   /* If the stream pointer given is not currently open, return a -1.        */
   /*------------------------------------------------------------------------*/
   if (_fp->fd == -1) 
   { 
      __TI_data_synch_INV(&_ftable, sizeof(_ftable));
      __TI_resource_unlock(__TI_LOCK_FILE_TBL);
      errno = EFPOS; 
      return (-1L);
   }

   /*------------------------------------------------------------------------*/
   /* For files in read mode, we must subtract the unread data in the buffer */
   /* from the location of the file pointer.  For files in write mode, we    */
   /* must add the data in the buffer that has not yet gone to disk.         */
   /*------------------------------------------------------------------------*/
   if (_fp->pos)
   {
      if (_STCHK(_fp, _MODER) && _fp->buff_stop > _fp->pos)
	 adjust = -(_fp->buff_stop - _fp->pos);
      if (_STCHK(_fp, _MODEW)) adjust = (_fp->pos - _fp->buf); 
   }
 
   /*------------------------------------------------------------------------*/
   /* Get the file pointer's position                                        */
   /*------------------------------------------------------------------------*/
   _pos = lseek(_fp->fd, 0L, SEEK_CUR);

   /*------------------------------------------------------------------------*/
   /* If the call to lseek was unsuccessful, return an -1                    */
   /*------------------------------------------------------------------------*/
   if (_pos < 0) 
   { 
      __TI_data_synch_WBINV(&_ftable, sizeof(_ftable));
      __TI_resource_unlock(__TI_LOCK_FILE_TBL); 
      errno = EFPOS; 
      return (-1L);
   }

   /*------------------------------------------------------------------------*/
   /* Make the necessary adjustment, and return the value                    */
   /*------------------------------------------------------------------------*/
   _pos += adjust;
   __TI_data_synch_WBINV(&_ftable, sizeof(_ftable));
   __TI_resource_unlock(__TI_LOCK_FILE_TBL);
   return (_pos);
}

