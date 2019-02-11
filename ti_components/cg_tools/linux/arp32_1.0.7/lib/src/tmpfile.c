/*****************************************************************************/
/*  TMPFILE.C v1.0.7                                                         */
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
/*    TMPFILE  -  Create a temporary file, and return a pointer to the       */
/*                stream                                                     */
/*****************************************************************************/
#include <stdio.h>
#include <_mutex.h>
#include <_data_synch.h>
#include "file.h"
#include <string.h>


/*****************************************************************************/
/* TMPFILE  -  Create a temporary file, and return a pointer to its FILE     */
/*             structure                                                     */
/*****************************************************************************/
_CODE_ACCESS FILE *tmpfile(void)
{
   char tfname[L_tmpnam];
   FILE *_fp = NULL;
   
   /*------------------------------------------------------------------------*/
   /* For multi-threaded applications, accesses to any of the shared data    */
   /* objects related to the management of the file table (_ftable[] and     */
   /* _tmpnams[] in this case) should be protected by a critical section.    */
   /* Modifications to file table shared data objects will require that      */
   /* the new values be propagated to shared memory before exiting the       */
   /* critical section.                                                      */
   /*------------------------------------------------------------------------*/
   __TI_resource_lock(__TI_LOCK_FILE_TBL);

   /*------------------------------------------------------------------------*/
   /* The call to tmpnam() is included in the critical section to ensure,    */
   /* on behalf of this call site, that only one thread is executing the     */
   /* body of tmpnam() at a time. Within tmpnam(), the static variables that */
   /* are involved in the generation of the temporary file name are given    */
   /* thread-local storage.                                                  */
   /*------------------------------------------------------------------------*/
   if (tmpnam(tfname)) _fp = fopen(tfname, "wb+");

   /*------------------------------------------------------------------------*/
   /* A non-NULL _fp returned from fopen() is assumed to be a pointer to an  */
   /* element in _ftable[] which is a shared resource.                       */
   /*------------------------------------------------------------------------*/
   if (_fp)
   {
      _SET(_fp, _TMPFILE);
      strcpy(_tmpnams[_fp->fd], tfname);
      __TI_data_synch_WBINV(&_tmpnams, sizeof(_tmpnams));
   }

   __TI_data_synch_WBINV(&_ftable, sizeof(_ftable));
   __TI_resource_unlock(__TI_LOCK_FILE_TBL);

   return (_fp);
}

