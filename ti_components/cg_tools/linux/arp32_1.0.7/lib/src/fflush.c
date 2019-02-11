/*****************************************************************************/
/*  FFLUSH.C v1.0.7                                                          */
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
/* FUNCTIONS:                                                                */
/*    fflush   -  Call _doflush for all streams that require flushing        */
/*    _doflush -  Flush one stream                                           */
/*****************************************************************************/
#include <stdio.h>
#include <_mutex.h>
#include <_data_synch.h>
#include "file.h"

extern _DATA_ACCESS int _ft_end;

_CODE_ACCESS int _doflush(FILE *_fp);


/*****************************************************************************/
/* FFLUSH   -  Call _doflush for all streams that require flushing           */
/*                                                                           */
/*    This function returns a 0 upon success, and an EOF upon failure.       */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS int fflush(register FILE *_fp)
{
   int result = 0;
 
   /*------------------------------------------------------------------------*/
   /* The current thread in a multi-threaded application must protect access */
   /* to __TI_LOCK_FILE_TBL shared resources (_ftable[], _ft_end, and        */
   /* _tmpnams[]). In this case, _doflush will update _ftable[] and the      */
   /* below loop will cache a local copy of _ft_end. Ensure that the local   */
   /* copy of _ftable[] is flushed to shared memory and the local copy of    */
   /* _ft_end is invalidated before leaving the critical section.            */
   /*------------------------------------------------------------------------*/
   __TI_resource_lock(__TI_LOCK_FILE_TBL);

   /*------------------------------------------------------------------------*/
   /* If _fp is not a NULL pointer, call _DOFLUSH for that stream.           */
   /* Otherwise, call _DOFLUSH for all file streams in the table that are    */
   /* active.                                                                */
   /*------------------------------------------------------------------------*/
   if (_fp) result = _doflush(_fp);
   else
   {
      int index;
      for(index = 0; index < _ft_end; index++)
         if(_ftable[index].fd != -1) result |= _doflush(&_ftable[index]);
   }

   __TI_data_synch_WBINV(&_ftable, sizeof(_ftable));
   __TI_data_synch_INV(&_ft_end, sizeof(_ft_end));
   __TI_resource_unlock(__TI_LOCK_FILE_TBL);
   return (result);
}


/*****************************************************************************/
/* _DOFLUSH -  Flush one stream                                              */
/*                                                                           */
/*    This function flushes the stream pointed to by _fp.  If the function   */
/*    is successful, it returns a 0.  If unsuccessful, it returns an EOF     */
/*                                                                           */
/*    For multi-threaded applications, this function should always be called */
/*    within a critical section that guarantees single-threaded access to    */
/*    __TI_LOCK_FILE_TBL resources (_ftable[] in this case).                 */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS int _doflush(FILE *_fp)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*                                                                        */
   /*    num_write   -  The number of bytes to be written to the file        */
   /*    errchk      -  An indicator to see if WRITE was successful          */
   /*------------------------------------------------------------------------*/
   unsigned num_write = _fp->pos - _fp->buf;
   int errchk = 0;
 
   /*------------------------------------------------------------------------*/
   /* If the current stream is not associated with a file, return an error.  */
   /*------------------------------------------------------------------------*/
   if (_fp->fd == -1) return (EOF);

   /*------------------------------------------------------------------------*/
   /* If the stream is writable, and it has a buffer, call WRITE, and store  */
   /* its return value in errchk                                             */
   /*------------------------------------------------------------------------*/
   if (_STCHK(_fp, _MODEW) && _fp->buf != NULL && num_write != 0)
      errchk = write(_fp->fd, (char *)_fp->buf, num_write);
 
   /*------------------------------------------------------------------------*/
   /* If WRITE fails, set the error flag in the stream pointer, and return   */
   /* an EOF                                                                 */
   /*------------------------------------------------------------------------*/
   if (errchk < 0)
   {
      _SET(_fp, _STATERR);
      return (EOF);
   }
 
   /*------------------------------------------------------------------------*/
   /* Reset the buffer pointer, make files opened with the "+" flag          */
   /* available for wither reading or writing, and return a 0, indicating    */
   /* a success                                                              */
   /*------------------------------------------------------------------------*/
   _fp->pos = _fp->buff_stop = _fp->buf;
   if (_STCHK(_fp, _MODERW)) _UNSET(_fp, (_MODER | _MODEW));
   return 0;
}
 
