/*
********************************************************************************
* HDVICP2.0 Based JPEG Encoder
*
* "HDVICP2.0 Based JPEG Encoder" is software module developed for
* TI's HDVICP2 based SoCs. This module is capable of encoding a raw image
* by compressing it into a JPEG bitstream compliant with ISO/IEC IS 10918-1.
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
********************************************************************************
*/
/**
********************************************************************************
* @file      jpegenc_ti_alg_malloc.c
*
* @brief     This module implements an algorithm memory management "policy" in
*            which no memory is shared among algorithm objects.  Memory is,
*            however reclaimed when objects are deleted.
*            This file is reused between platforms.Any change should be made
*            after considering the impact on multiple platforms
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
*
* @version 0.1 (Feb 2010) : Cleaned code to adhere for the coding guidelines
*                           [Vasudev]
*
********************************************************************************
*/
/* -------------------- compilation control switches -------------------------*/
#pragma CODE_SECTION(ALG_init, ".text:init")
#pragma CODE_SECTION(ALG_exit, ".text:exit")
#pragma CODE_SECTION(_ALG_allocMemory, ".text:create")
#pragma CODE_SECTION(_ALG_freeMemory, ".text:create")

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/ialg.h>
#include <stdlib.h>     /* malloc/free declarations */
#include <string.h>     /* memset declaration */

/*---------------------Macros-------------------------------------------------*/

#if defined (_54_) || (_55_) || (_28_)
void *mem_align(size_t alignment, size_t size);
void mem_free(void *ptr);
#define myMemalign  mem_align
#define myFree      mem_free
#else /*#if defined (_54_) || (_55_) || (_28_)*/
#define myMemalign  memalign
#define myFree      free
#endif /*#if defined (_54_) || (_55_) || (_28_)*/


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
    memTab[idx].base = (void *)myMemalign(memTab[idx].alignment,
    memTab[idx].size);

    if (memTab[idx].base == NULL)
    {
      _ALG_freeMemory(memTab, idx);
      return (FALSE);
    }
    else
    {
      /* Nothing to execute*/
    }
  }
  return (TRUE);
}

/**
********************************************************************************
*  @fn         _ALG_freeMemory(IALG_MemRec memTab[], Int n)
*
*  @brief      This function frees the specified number of memory Blocks
*
*  @param[in]  memTab   :  Array containing the base address
*
*  @param[in]  n        : Number of Memory instance to be freed
*
*  @return     none
********************************************************************************
*/
Void _ALG_freeMemory(IALG_MemRec memTab[], Int n)
{
  Int i;

  for (i = 0; i < n; i++)
  {
    if (memTab[i].base != NULL)
    {
      myFree(memTab[i].base);
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
*  @fn     mem_align(size_t alignment, size_t size)
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
  /* return if invalid size value                                             */
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
  /* return aligned memory                                                    */
  /*--------------------------------------------------------------------------*/
  return ((void *)retPtr);
}

/**
********************************************************************************
*  @fn     mem_free(void *ptr)
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

#endif /*#if defined (_54_) || (_55_) || (_28_)*/


