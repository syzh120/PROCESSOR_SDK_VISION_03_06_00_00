/*****************************************************************************/
/* stdarg.h   v1.0.7                                                         */
/*                                                                           */
/* Copyright (c) 1993-2015 Texas Instruments Incorporated                    */
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

#ifndef _STDARG
#define _STDARG

#ifdef __cplusplus
namespace std
{
#endif

typedef char *va_list;

#ifdef __cplusplus
}
#endif

/*****************************************************************************/
/* VA_END - Reclaim resources used by varargs handling.                      */
/*                                                                           */
/* No action needed                                                          */
/*****************************************************************************/
#define va_end(_ap) ((void)0)

/*****************************************************************************/
/* VA_START - Set up the va_list pointer.                                    */
/* - va_list pointer set to the address of the arg plus its size             */
/* - va_list pointer points one byte beyond the last argument (ELF).         */
/*---------------------------------------------------------------------------*/
#define va_start(_ap, _parmN)                                    \
         (_ap = ((char *)__va_parmadr(_parmN)) +                 \
                (__va_argref(_parmN) ? sizeof(&_parmN) :         \
                        sizeof(_parmN)))

/*****************************************************************************/
/* VA_ARG - Return the next argument, adjust va_list pointer                 */
/*                                                                           */
/* Some arguments passed by value are turned into pass-by-reference by       */
/* making a temporary object and passing a pointer to this temporary.  For   */
/* such an argument (indicated by __va_argref(_type)) the actual argument    */
/* passed is a pointer, so it must be dealt with specially.                  */
/*                                                                           */
/* What happens on every va_arg(_ap, _type) call is:                         */
/* 1) Align the value of _ap (the va_list pointer) appropriately for _type   */
/*    (the requested type).                                                  */
/* 2) Increment _ap appropriately for _type (sizeof(_type)).                 */
/* 3) Return the value by dereferencing _ap (return *(ap-sizeof(_type))      */
/*---------------------------------------------------------------------------*/
#define __TI_ALIGNOF_PROMOTED_TYPE(_type)                                \
        (__va_argref(_type) ? __alignof__(_type *) :                     \
         (sizeof(_type) < 4) ? __alignof__(int) :                        \
                               __alignof__(_type))

#define __TI_ALIGN(e, _type)                                                \
        ((char *)(((unsigned)(e) + __TI_ALIGNOF_PROMOTED_TYPE(_type) - 1) & \
                                 ~(__TI_ALIGNOF_PROMOTED_TYPE(_type) - 1)))

#define __TI_SIZEOF_PROMOTED_TYPE(_type)                                 \
        (__va_argref(_type) ? sizeof(_type *) :                          \
         (sizeof(_type) < 4) ? sizeof(int) : sizeof(_type))

#define __TI_DEREF(e, _type)                                             \
        (__va_argref(_type) ? **(_type **)(e) : *(_type *)(e))

#define va_arg(_ap, _type)                                               \
        (_ap = __TI_ALIGN(_ap, _type),                                   \
         _ap += __TI_SIZEOF_PROMOTED_TYPE(_type),                        \
         __TI_DEREF(_ap - __TI_SIZEOF_PROMOTED_TYPE(_type), _type))

#endif /* _STDARG */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)
using std::va_list;
#endif /* __cplusplus */

