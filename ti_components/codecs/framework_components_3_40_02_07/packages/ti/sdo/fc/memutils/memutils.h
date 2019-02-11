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
 *
 */
/**
 *  @file       ti/sdo/fc/memutils/memutils.h
 *
 *  @brief      MEMUTILS Interface Definitions - Memory and Cache related APIs
 */

/**
 *  @defgroup   ti_sdo_fc_memutils_MEMUTILS MEMUTILS
 *
 *              MEMUTILS is a set of APIs that can be called by xDAIS algorithms
 *              to manage their Cache and also to obtain Physical addresses
 *              for algorithms that need to program accelarators (i.e., EDMA3,
 *              HDVICP etc)
 *
 *  @remark
 *
 */

#ifndef ti_sdo_fc_memutils_MEMUTILS
#define ti_sdo_fc_memutils_MEMUTILS

/** @ingroup    ti_sdo_fc_memutils_MEMUTILS */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Name used to identify the module for setting xdc.runtime.Diags
 *        masks.
 */
#define MEMUTILS_MODNAME "ti.sdo.fc.memutils"

/*
 *  ======== MEMUTILS_cacheInv ========
 */
/**
 *  @brief      Invalidate a range of cache.
 *
 *  @param[in]  addr            Address of the beginning of the buffer
 *                               to invalidate.
 *  @param[in]  sizeInBytes     Size of the buffer to invalidate.
 *
 *  @remarks    In addition to application usage, this is often called by
 *              a skeleton implementor after it has received a shared memory
 *              buffer from another processor, and before it invokes an
 *              algorithm's interface which will operate on that shared
 *              memory buffer.
 *
 *  @sa         MEMUTILS_cacheWb()
 *  @sa         MEMUTILS_cacheWbInv()
 */
extern Void MEMUTILS_cacheInv(Ptr addr, Int sizeInBytes);

/*
 *  ======== MEMUTILS_cacheWb ========
 */
/**
 *  @brief      Write back cache.
 *
 *  @param[in]  addr            Address of the beginning of the buffer
 *                              to writeback.
 *  @param[in]  sizeInBytes     Size of the buffer to writeback.
 *
 *  @sa         MEMUTILS_cacheInv()
 *  @sa         MEMUTILS_cacheWbInv()
 */
extern Void MEMUTILS_cacheWb(Ptr addr, Int sizeInBytes);


/*
 *  ======== MEMUTILS_cacheWbInv ========
 */
/**
 *  @brief      Write back and invalidate cache.
 *
 *  @param[in]  addr            Address of the beginning of the buffer
 *                              to writeback and invalidate.
 *  @param[in]  sizeInBytes     Size of the buffer to writeback invalidate.
 *
 *  @sa         MEMUTILS_cacheInv()
 *  @sa         MEMUTILS_cacheWb()
 */
extern Void MEMUTILS_cacheWbInv(Ptr addr, Int sizeInBytes);


/*
 *  ======== MEMUTILS_getPhysicalAddr ========
 */
/**
 *  @brief      Obtain physical (hardware specific) address
 *
 *  @param[in]  addr            Address to convert to physical (hardware)
 *                              address
 *
 */
extern Void * MEMUTILS_getPhysicalAddr(Ptr addr);


#ifdef __cplusplus
}
#endif /* extern "C" */


/*@}*/

#endif
