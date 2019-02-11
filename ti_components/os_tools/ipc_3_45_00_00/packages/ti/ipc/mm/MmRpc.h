/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 *  @file       ti/ipc/mm/MmRpc.h
 *
 *  @brief      Multi-Media derived Remote Procedure Call
 *
 *  @note       MmRpc is currently only available for HLOS (Linux, QNX, Android).
 */

#ifndef ti_ipc_mm_MmRpc__include
#define ti_ipc_mm_MmRpc__include

/* add includes here */
#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 *  @brief  Operation is successful
 */
#define MmRpc_S_SUCCESS (0)

/*!
 *  @brief  Operation failed
 */
#define MmRpc_E_FAIL (-1)

/*!
 *  @brief  Invalid parameter type
 */
#define MmRpc_E_INVALIDPARAM (-2)

/*!
 *  @brief  Memory allocation failed
 */
#define MmRpc_E_NOMEM (-3)

/*!
 *  @brief  A system call failed
 */
#define MmRpc_E_SYS (-4)

/*!
 *  @brief  Size of parameter array in function context structure
 */
#define MmRpc_MAX_PARAMS (10)

/*!
 *  @brief  Maximum size of translation array in function context structure
 */
#define MmRpc_MAX_TRANSLATIONS (1024)

/*!
 *  @brief  Macro for computing offset to a field of a structure.
 *
 *  @code
 *  struct foobar {
 *      int a;
 *      int *p;
 *  };
 *
 *  struct foobar *sp = ...;
 *  offset = MmRpc_OFFSET(sp, &sp->p);
 *  struct foobar st = ...;
 *  offset = MmRpc_OFFSET(&st, &st.p);
 *  @endcode
 */
#define MmRpc_OFFSET(base, field) ((unsigned int)(field)-(unsigned int)(base))

/*!
 *  @brief      MmRpc_Handle type
 */
typedef struct MmRpc_Object *MmRpc_Handle;

/*!
 *  @brief      MmRpc_ParamType enum
 */
typedef enum {
    MmRpc_ParamType_Scalar = 1, /*!< pass by value */
    MmRpc_ParamType_Ptr,        /*!< data pointer */
    MmRpc_ParamType_OffPtr,     /*!< buffer at offset in memory block */
    MmRpc_ParamType_Elem        /*!< array element */
} MmRpc_ParamType;

/*!
 *  @brief      MmRpc_Param type
 */
typedef struct {
    MmRpc_ParamType     type;   /*!< parameter type */

    union {
        struct {
            size_t      size;   /*!< size of the data */
            size_t      data;   /*!< data (pass by value)*/
        } scalar;

        struct {
            size_t      size;   /*!< size of the data referenced */
            size_t      addr;   /*!< pointer value */
            size_t      handle; /*!< memory allocator handle */
        } ptr;

        struct {
            size_t      size;   /*!< size (bytes) of param structure */
            size_t      base;   /*!< param address */
            size_t      offset; /*!< offset within param */
            size_t      handle; /*!< memory allocator handle */
        } offPtr;

    } param;
} MmRpc_Param;

typedef struct {
    uint32_t    index;  /*!< parameter index to base pointer */
    ptrdiff_t   offset; /*!< offset to embedded pointer
                         *
                         *   If param type is MmRpc_ParamType_Ptr, offset
                         *   to embedded pointer from addr. If param type
                         *   is MmRpc_ParamType_OffPtr, offset to embedded
                         *   pointer from base+offset.
                         */
    size_t      base;   /*!< addr or file descriptor [+ data offset]
                         *
                         *   If param type is MmRpc_ParamType_Ptr, the
                         *   value of the embedded pointer. If param type
                         *   is MmRpc_ParamType_OffPtr, the file descriptor
                         *   of the block referenced by the embedded pointer
                         *   plus an optional data offset.
                         */
    size_t      handle; /*!< memory allocator handle */
} MmRpc_Xlt;

/*!
 *  @brief      Function call context structure
 */
typedef struct {
    uint32_t    fxn_id;         /*!< function id to call */
    uint32_t    num_params;     /*!< number of parameters in params array */
    MmRpc_Param params[MmRpc_MAX_PARAMS];
                                /*!< the array of parameters */
    uint32_t    num_xlts;       /*!< number of translations in xltAry */
    MmRpc_Xlt * xltAry;         /*!< array of translations */
} MmRpc_FxnCtx;

/*!
 *  @brief      Memory buffer types
 *
 *  @remark     Not all operating systems support all buffer types.
 */
typedef enum {
    MmRpc_BufType_Handle,       /*!< memory allocator handle */
    MmRpc_BufType_Ptr           /*!< buffer address */
} MmRpc_BufType;

/*!
 *  @brief      Memory buffer descriptor
 */
typedef union {
    size_t      handle;         /*!< file descriptor or handle */

    struct {
        size_t  addr;           /*!< address of memory buffer */
        size_t  size;           /*!< size (bytes) of memory buffer */
    } ptr;

} MmRpc_BufDesc;

/*!
 *  @brief      Instance create parameters
 */
typedef struct {
    int reserved;
} MmRpc_Params;

/*!
 *  @brief      Invoke a remote procedure call
 *
 *  @param[in]      handle  MmRpc handle, obtained from MmRpc_create()
 *  @param[in]      ctx     Context with which to invoke the remote service
 *  @param[in, out] ret     Return value from the remotely invoked service
 *
 *  @pre        @c handle must be a valid handle for the service instance
 *              returned by an earlier call to MmRpc_create().
 *
 *  @sa MmRpc_create()
 *  @sa MmRpc_delete()
 */
int MmRpc_call(MmRpc_Handle handle, MmRpc_FxnCtx *ctx, int32_t *ret);

/*!
 *  @brief      Create an MmRpc instance
 *
 *  @param[in]      service     Name of the service to create
 *  @param[in]      params      Initialized MmRpc parameters
 *  @param[in,out]  handlePtr   Space to hold the MmRpc handle
 *
 *  @retval     MmRpc_S_SUCCESS @copydoc MmRpc_S_SUCCESS
 *  @retval     MmRpc_E_FAIL    @copydoc MmRpc_E_FAIL
 *
 *  @remark     This instantiates an instance of the service on a remote
 *              core.  Each remote instance consists of a unique thread
 *              listening for requests made via a call to MmRpc_call().
 */
int MmRpc_create(const char *service, const MmRpc_Params *params,
        MmRpc_Handle *handlePtr);

/*!
 *  @brief      Delete an MmRpc instance
 *
 *  @param[in]  handlePtr  MmRpc handle, obtained from MmRpc_create()
 *
 *  @pre        @c handlePtr must be a valid handle for the service instance
 *              returned by an earlier call to MmRpc_create()
 *
 *  @sa MmRpc_create()
 */
int MmRpc_delete(MmRpc_Handle *handlePtr);

/*!
 *  @brief      Release buffers which were declared in use
 *
 *  @param[in]  handle  Service handle returned by MmRpc_create()
 *  @param[in]  type    Buffer descriptor type
 *  @param[in]  num     Number of elements in @c desc array
 *  @param[in]  desc    Pointer to array of buffer descriptors
 *
 *  @pre        @c handle must be a valid handle for the service instance
 *              returned by an earlier call to MmRpc_create().
 *
 *  @remark     When the remote processor no longer needs a reference
 *              to a buffer, calling MmRpc_release() will release the
 *              buffer and any associated resources.
 *
 *  @retval     MmRpc_S_SUCCESS         @copydoc MmRpc_S_SUCCESS
 *  @retval     MmRpc_E_INVALIDPARAM    @copydoc MmRpc_E_INVALIDPARAM
 *  @retval     MmRpc_E_NOMEM           @copydoc MmRpc_E_NOMEM
 *  @retval     MmRpc_E_SYS             @copydoc MmRpc_E_SYS
 *
 *  @sa         MmRpc_use()
 */
int MmRpc_release(MmRpc_Handle handle, MmRpc_BufType type, int num,
        MmRpc_BufDesc *desc);

/*!
 *  @brief      Declare the use of the given buffers
 *
 *  @param[in]  handle  Service handle returned by MmRpc_create()
 *  @param[in]  type    Buffer descriptor type
 *  @param[in]  num     Number of elements in @c desc array
 *  @param[in]  desc    Pointer to array of buffer descriptors
 *
 *  @pre        @c handle must be a valid handle for the service instance
 *              returned by an earlier call to MmRpc_create().
 *
 *  @remark     When using MmRpc_call() to invoke remote function calls,
 *              any referenced buffers will be made available to the
 *              remote processor only for the duration of the remote
 *              function call. If the remote processor maintains a
 *              reference to the buffer across multiple invocations of
 *              MmRpc_call(), then the application must declare the buffer
 *              "in use". This will make the buffer persistent.
 *
 *  @remark     The application must release the buffer when it is no
 *              longer needed.
 *
 *  @code
 *      #include <ti/ipc/mm/MmRpc.h>
 *
 *      MmRpc_BufDesc desc[2];
 *
 *      desc[0].handle = fd1;
 *      desc[1].handle = fd2;
 *
 *      MmRpc_use(h, MmRpc_BufType_Handle, 2, desc);
 *  @endcode
 *
 *  @retval     MmRpc_S_SUCCESS         @copydoc MmRpc_S_SUCCESS
 *  @retval     MmRpc_E_INVALIDPARAM    @copydoc MmRpc_E_INVALIDPARAM
 *  @retval     MmRpc_E_NOMEM           @copydoc MmRpc_E_NOMEM
 *  @retval     MmRpc_E_SYS             @copydoc MmRpc_E_SYS
 *
 *  @sa         MmRpc_release()
 */
int MmRpc_use(MmRpc_Handle handle, MmRpc_BufType type, int num,
        MmRpc_BufDesc *desc);

/*!
 *  @brief      Initialize the instance create parameter structure
 *
 */
void MmRpc_Params_init(MmRpc_Params *params);


#if defined(__cplusplus)
}
#endif
#endif /* ti_ipc_mm_MmRpc__include */
