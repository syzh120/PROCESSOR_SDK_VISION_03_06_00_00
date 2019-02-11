/*  ============================================================================
 *  Copyright (c) Texas Instruments Incorporated 2002, 2003, 2004, 2005, 2006, 2008
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
/** ============================================================================
 *   @file  csl_types.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for CSL types
 *
 */


#ifndef CSL_TYPES_H
#define CSL_TYPES_H

#include <ti/csl/tistdtypes.h>

#ifndef TRUE

#define TRUE		((Bool) 1)
#define FALSE		((Bool) 0)

#endif

typedef Int16           CSL_Uid;
typedef Int16           CSL_ModuleId;
typedef Uint32          CSL_Xio;

typedef Uint8           CSL_BitMask8;
typedef Uint16          CSL_BitMask16;
typedef Uint32          CSL_BitMask32;

typedef volatile Uint8  CSL_Reg8;
typedef volatile Uint16 CSL_Reg16;
typedef volatile Uint32 CSL_Reg32;

typedef Int16           CSL_Status;
typedef Int16           CSL_InstNum;
typedef Int16           CSL_ChaNum;

typedef unsigned long long int  CSL_Uint64;

typedef enum {
  CSL_EXCLUSIVE = 0,
  CSL_SHARED    = 1
} CSL_OpenMode;

typedef enum {
  CSL_FAIL      = 0,
  CSL_PASS      = 1
} CSL_Test;

#ifndef NULL
#define NULL            ((void*)0)
#endif

#define STW_SOK                         ((int32_t) 0)
#define STW_EFAIL                       (-((int32_t) 1))
#define STW_EBADARGS                    (-((int32_t) 2))
#define STW_EINVALID_PARAMS             (-((int32_t) 3))
#define STW_ETIMEOUT                    (-((int32_t) 4))
#define STW_EOUT_OF_RANGE               (-((int32_t) 5))
#define STW_EUNSUPPORTED_CMD            (-((int32_t) 6))
#define STW_EUNSUPPORTED_OPS            (-((int32_t) 7))

#endif /* CSL_TYPES_H */

