/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *
 * \file alg_malloc.c
 *
 * \brief This module implements an algorithm memory management "policy" in
 *        which no memory is shared among algorithm objects.  Memory is,
 *        however reclaimed when objects are deleted.
 *        This file is reused between platforms.Any change should be made
 *        after considering the impact on multiple platforms
 *
 * \version 0.0 (Jan 2014) : [SS] First version
 *
 *******************************************************************************
 */

/*----------------------- data declarations ----------------------------------*/

#pragma CODE_SECTION(ALG_init, ".text:init")
#pragma CODE_SECTION(ALG_exit, ".text:exit")
#pragma CODE_SECTION(_ALG_allocMemory, ".text:create")
#pragma CODE_SECTION(_ALG_freeMemory, ".text:create")

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
#include <xdc/std.h>
#include <src/rtos/links_ipu/iva/codec_utils/src/alg.h>
#include <ti/xdais/ialg.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#include <stdlib.h>     /* malloc/free declarations */
#include <string.h>     /* memset declaration */

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
#if defined (_54_) || (_55_) || (_28_)
void *mem_align(size_t alignment, size_t size);

void mem_free(void *ptr);

#define myMemalign  mem_align

#define myFree      mem_free

#else
#define myMemalign  memalign

#define myFree      free

#endif

/*-----------------------function prototypes ---------------------------------*/

Bool _ALG_allocMemory(IALG_MemRec memTab[], Int n);
Void _ALG_freeMemory(IALG_MemRec memTab[], Int n);

/**
********************************************************************************
*  @fn     ALG_activate(ALG_Handle alg)
*
*  @brief  This function does app specific initialization of scratch memory
*
*  @param[in,out]  alg     :  This handle type is used to reference all
*                             ALG instance objects
*
*  @return    none
********************************************************************************
*/
Void ALG_activate(ALG_Handle alg)
{
  /*--------------------------------------------------------------------------*/
  /* Restore all persistant shared memory                                     */
  /*--------------------------------------------------------------------------*/

  if (alg->fxns->algActivate != NULL)
  {
    alg->fxns->algActivate(alg);
  }
  else
  {
    /* Nothing to execute*/
  }
}

/**
********************************************************************************
*  @fn     ALG_deactivate(ALG_Handle alg)
*
*  @brief  This function does application specific store of persistent data
*
*  @param[in]  alg         :  This handle type is used to reference all
*                             ALG instance objects
*
*  @return    none
********************************************************************************
*/
Void ALG_deactivate(ALG_Handle alg)
{
  /*--------------------------------------------------------------------------*/
  /* do app specific store of persistent data                                 */
  /*--------------------------------------------------------------------------*/
  if (alg->fxns->algDeactivate != NULL)
  {
    alg->fxns->algDeactivate(alg);
  }
  else
  {
    /* Nothing to execute*/
  }

}

/**
********************************************************************************
*  @fn     ALG_exit(Void)
*
*  @brief  This function is for Module finalization
*
*  @return    none
********************************************************************************
*/
Void ALG_exit(Void)
{
}

/**
********************************************************************************
*  @fn     ALG_init(Void)
*
*  @brief  This function is for Module initialization
*
*  @return    none
********************************************************************************
*/
Void ALG_init(Void)
{
}


/**
********************************************************************************
*  @fn     _ALG_allocMemory(IALG_MemRec memTab[], Int n)
*
*  @brief  This function allocates the specified number of memory blocks with
*          alignment.
*
*  @param[in]  memTab   :  Array containing the base address
*
*  @param[in]  n        : Number of Memory instance to be freed
*
*  @return    TRUE if allocated else FALSE
********************************************************************************
*/
Bool _ALG_allocMemory(IALG_MemRec memTab[], Int n)
{
  Int idx;

  for (idx = 0; idx < n; idx++)
  {
    memTab[idx].base = (void *)Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                              memTab[idx].size,
                                              memTab[idx].alignment);

    if (memTab[idx].base == NULL)
    {
      _ALG_freeMemory(memTab, idx);
      return (FALSE);
    }
    else
    {
      if (0 == idx)
      {
          /* As per xdaised standard, memTab[0] is guaranteed to be
           * initialized to zero.
           */
          memset(memTab[idx].base,0,memTab[idx].size);

      }
    }

  }

  return (TRUE);
}

/**
********************************************************************************
*  @fn     _ALG_freeMemory(IALG_MemRec memTab[], Int n)
*
*  @brief  This function frees the specified number of memory Blocks
*
*  @param[in]  memTab   :  Array containing the base address
*
*  @param[in]  n        : Number of Memory instance to be freed
*
*  @return    none
********************************************************************************
*/
Void _ALG_freeMemory(IALG_MemRec memTab[], Int n)
{
  Int i;

  for (i = 0; i < n; i++)
  {
    if (memTab[i].base != NULL)
    {
      Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                   (Ptr)memTab[i].base, memTab[i].size);

    }
    else
    {
      /* Nothing to execute*/
    }
  }
}
#if defined (_54_) || (_55_) || (_28_)

/**
********************************************************************************
*  @fn     mem_align
*
*  @brief  This function allocates alignment memory depending on 'alignment'
*           specified
*
*  @param[in]  alignment   :  specifies the alignment
*
*  @param[in]  size        :  Size of the memory to be allcoated
*
*  @return    On sucess returns pointer
********************************************************************************
*/
void *mem_align(size_t alignment, size_t size)
{
  void     **mallocPtr;
  void     **retPtr;

  /*--------------------------------------------------------------------------*/
  /* Return if invalid size value                                             */
  /*--------------------------------------------------------------------------*/
  if (size <= 0)
  {
    return (0);
  }
  else
  {
    /* Nothing to execute*/
  }

  /*--------------------------------------------------------------------------*/
  /* If alignment is not a power of two, return what malloc returns.          */
  /* This is how memalign behaves on the c6x.                                 */
  /*--------------------------------------------------------------------------*/
  if ((alignment & (alignment - 1)) || (alignment <= 1))
  {
    if( (mallocPtr = malloc(size + sizeof(mallocPtr))) != NULL )
    {
      *mallocPtr = mallocPtr;
      mallocPtr++;
    }
    else
    {
      /* Nothing to execute*/
    }
    return ((void *)mallocPtr);
  }
  else
  {
    /* Nothing to execute*/
  }

  /*--------------------------------------------------------------------------*/
  /* allocate block of memory                                                 */
  /*--------------------------------------------------------------------------*/
  if ( !(mallocPtr = malloc(alignment + size)) )
  {
    return (0);
  }
  else
  {
    /* Nothing to execute*/
  }

  /*--------------------------------------------------------------------------*/
  /* Calculate aligned memory address                                         */
  /*--------------------------------------------------------------------------*/
  retPtr = (void *)(((Uns)mallocPtr + alignment) & ~(alignment - 1));

  /*--------------------------------------------------------------------------*/
  /* Set pointer to be used in the mem_free() fxn                             */
  /*--------------------------------------------------------------------------*/
  retPtr[-1] = mallocPtr;

  /*--------------------------------------------------------------------------*/
  /* return aligned memory pointer                                            */
  /*--------------------------------------------------------------------------*/
  return ((void *)retPtr);
}

/**
********************************************************************************
*  @fn     mem_free
*
*  @brief  This function Frees the allocated Memory
*
*  @param[in]  ptr   : Pointer to the location which needs to be freed.
*
*  @return    none
********************************************************************************
*/
Void mem_free(void *ptr)
{
  free((void *)((void **)ptr)[-1]);
}

#endif

/* Nothing beyond this point */

