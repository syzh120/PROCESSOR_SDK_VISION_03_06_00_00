/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 */

/**
 *  @file       ti/ipc/mm/MmType.h
 *
 *  @brief      Specific types to support the MmRpc and MmServiceMgr modules
 *
 *
 */

#ifndef ti_ipc_mm_MmType__include
#define ti_ipc_mm_MmType__include

#include <ti/grcm/RcmServer.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 *  @brief      Maximum function name length
 */
#define MmType_MAX_NAMELEN (64)

/*!
 *  @brief      Maximum number of parameters
 */
#define MmType_MAX_PARAMS (10)

/*!
 *  @brief      Compute number of elements in given array
 *
 *              The given array must be the actual array buffer,
 *              not a pointer to it.
 */
#define MmType_NumElem(x) (sizeof(x)/sizeof((x)[0]))

/*!
 *  @brief      Parameter Direction
 *
 *              The parameter direction relative to the function
 *              it describes.
 */
typedef enum {
    MmType_Dir_In = 0,
    MmType_Dir_Out,
    MmType_Dir_Bi,
    MmType_Dir_MAX
} MmType_Dir;

/*!
 *  @brief      Parameter Type
 */
typedef enum {
    MmType_Param_VOID = 0,
    MmType_Param_S08,
    MmType_Param_U08,
    MmType_Param_S16,
    MmType_Param_U16,
    MmType_Param_S32,
    MmType_Param_U32,
    MmType_Param_S64,
    MmType_Param_U64,

    MmType_Param_PTR = 0x80,   /*!< OR'd with lower type to make a
                                    pointer to the correct type */
    MmType_Param_MAX
} MmType_ParamType;

#define MmType_PtrType(type)    ((type) | MmType_Param_PTR)

/*!
 *  @brief      Parameter Signature
 */
typedef struct {
    UInt32 direction;   /*!< @see MmType_Dir */
    UInt32 type;        /*!< @see MmType_ParamType */
    UInt32 count;       /*!< basic sanity checking on array bounds */
} MmType_ParamSig;

/*!
 *  @brief      Function Signature
 *
 *  The first parameter (params[0]) is the return value.
 */
typedef struct {
    Char                name[MmType_MAX_NAMELEN];
    UInt32              numParam;
    MmType_ParamSig     params[MmType_MAX_PARAMS + 1];
} MmType_FxnSig;

/*!
 *  @brief      Function Signature Table
 *
 */
typedef struct {
    UInt                count;
    MmType_FxnSig *     table;
} MmType_FxnSigTab;

/*!
 *  @brief      Marshalled Parameter structure
 *
 */
typedef struct {
    SizeT size;
    SizeT data;
} MmType_Param;


#if defined(__cplusplus)
}
#endif
#endif /* ti_ipc_mm_MmType__include */
