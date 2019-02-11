/*
*******************************************************************************
 * HDVICP2.0 Based H.264 HP Decoder
 * 
 * "HDVICP2.0 Based H.264 HP Decoder" is a software module developed on TI's 
 *  HDVICP2 based SOCs. This module is capable of decoding a compressed 
 *  high/main/baseline profile H.264 bit-stream into a YUV 4:2:0 Raw video.
 *  Based on "ISO/IEC 14496-10". 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
*******************************************************************************
*/


/**  
********************************************************************************
 * @file <alg_malloc.c>                          
 *                                       
 * @brief This module implements an algorithm memory management "policy" in 
 *        which no memory is shared among algorithm objects. Memory is, however
 *        reclaimed when objects are deleted.
 * 
 *        preemption      sharing             object deletion 
 *        ----------      -------             ---------------
 *        yes(*)          none                yes
 *  
 *        Note 1: this module uses run-time support functions malloc() and 
 *        free() to allocate and free memory.  Since these functions are *not* 
 *        reentrant, either all object creation and deletion must be performed 
 *        by a single thread or reentrant versions or these functions must be 
 *        created.
 *       
 *        Note 2: Memory alignment is supported for the c5000 targets with the
 *        memalign5000() function which allocates 'size + align' memory. This
 *        is necessary since the compiler's run-time library does not support 
 *        memalign().  This wastes 'align' extra memory.
 *
 * @author: Multimedia Codecs TI
 *
 * @version 0.0 (Jan 2008) : Initial version
 * @version 0.2 (Jul 2010) : Added code to test scratch corruption
 *                           [Ramakrishna]
********************************************************************************
*/

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
#include <stdlib.h> 
#include <string.h> 
#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/sdo/fc/utils/api/_alg.h>
#include <TestApp_Constants.h>

#ifdef MEM_CORRUPTION_TEST
extern XDAS_Int32    countConfigSet;
#endif
/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
#if defined (_54_) || (_55_) || (_28_)
void *mem_align(size_t alignment, size_t size);
void mem_free(void *ptr);

#define myMemalign  mem_align
#define myFree      mem_free
#else
#define myMemalign(align, size)  malloc((size))
#define myFree      free
#endif

/** 
********************************************************************************
 *  @fn     ALG_activate
 *  @brief  This function does app specific initialization of scratch memory
 *          
 *  @param[in/out] alg   : Algorithm Handle
 *          
 *  @return None.
********************************************************************************
*/
Void ALG_activate(ALG_Handle alg)
{
  /*--------------------------------------------------------------------------*/
  /* Restore all persistant shared memory                                     */
  /*--------------------------------------------------------------------------*/
  
  /*--------------------------------------------------------------------------*/
  /* Nothing to do since memory allocation never shares any data              */
  /*--------------------------------------------------------------------------*/
  ; 
  /*--------------------------------------------------------------------------*/
  /* Do app specific initialization of scratch memory                         */
  /*--------------------------------------------------------------------------*/
  
  if (alg->fxns->algActivate != NULL) 
  {
    alg->fxns->algActivate(alg);
  }
}
/** 
********************************************************************************
 *  @fn     ALG_deactivate
 *  @brief  This function does application specific store of persistent data
 *          
 *  @param[in] alg   : Algorithm Handle
 *          
 *  @return None
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
  /*--------------------------------------------------------------------------*/
  /* save all persistant shared memory                                        */
  /*--------------------------------------------------------------------------*/
  
  /*--------------------------------------------------------------------------*/
  /* nothing to do since memory allocation never shares any data              */
  /*--------------------------------------------------------------------------*/
  ;
}

/** 
********************************************************************************
 *  @fn     ALG_exit
 *  @brief  Alg Exit
 *          
 *  @return Void
********************************************************************************
*/
Void ALG_exit(Void)
{
}

/** 
********************************************************************************
 *  @fn     ALG_init
 *  @brief  Alg Init
 *          
 *  @return Void
********************************************************************************
*/
Void ALG_init(Void)
{
}

/** 
********************************************************************************
 *  @fn     _ALG_freeMemory
 *  @brief  This function frees the specified number of memory Blocks
 *
 *  @param[in] memTab  : Array containing the base address
 *  @param[in] numObjs : Number of Memory instance to be freed
 *          
 *  @return Void
********************************************************************************
*/
Void _ALG_freeMemory(IALG_MemRec memTab[], Int numObjs)
{
  Int index;

  for (index = 0; index < numObjs; index++) 
  {
    if (memTab[index].base != NULL) 
    {
      myFree(memTab[index].base);
    }
  }
}

/** 
********************************************************************************
 *  @fn     _ALG_allocMemory
 *  @brief  This function allocates the specified number of memory blocks with
 *          alignment.
 *
 *  @param[in] memTab  : Array containing the base address
 *  @param[in] numObjs : Number of Memory instance to be freed
 *          
 *  @return TRUE if allocated else FALSE
********************************************************************************
*/
Bool _ALG_allocMemory(IALG_MemRec memTab[], Int numObjs)
{
  Int idx;

#ifdef MEM_TAB_DUMPS
  FILE *fp_memtab;
  fp_memtab = fopen("mem_tab_dump.xls","w");
#endif

  for (idx = 0; idx < numObjs; idx++) 
  {
    memTab[idx].base = (void *)myMemalign(memTab[idx].alignment, 
                                          memTab[idx].size);

#ifdef MEM_TAB_DUMPS
    fprintf(fp_memtab, "%d \n ", memTab[idx].size);
#endif

    if (memTab[idx].base == NULL) 
    {
      _ALG_freeMemory(memTab, idx);
      return (FALSE);
    }

#ifdef MEM_CORRUPTION_TEST
    {
      /*---------------------------------------------------------------------*/
      /* Fill DDR memtabs with some data to check that codec doesnt depend   */
      /* on initial DDR content(Memory corruption)                           */
      /*---------------------------------------------------------------------*/
      char word_pattern[4] = {0x00, 0xAA, 0x55, 0x99};
      char word = word_pattern[countConfigSet & 0x3];
      memset(memTab[idx].base, word, memTab[idx].size);
    }
#endif
  }

#ifdef MEM_TAB_DUMPS
  fclose(fp_memtab);
#endif

  return (TRUE);
}


#if defined (_54_) || (_55_) || (_28_)
/** 
********************************************************************************
 *  @fn     mem_align
 *  @brief  This function allocates alignment memory depending on 'alignment' 
 *           specified
 *
 *  @param[in] alignment  : specifies the alignment 
 *  @param[in] size       : Size of the memory to be allcoated
 *          
 *  @return on sucess returns pointer 
********************************************************************************
*/
void *mem_align(size_t alignment, size_t size)
{
  void **mallocPtr;
  void **retPtr;
  /*--------------------------------------------------------------------------*/
  /* return if invalid size value                                             */
  /*--------------------------------------------------------------------------*/
  if (size <= 0) 
  {
    return (0);
  }
  /*--------------------------------------------------------------------------*/
  /* If alignment is not a power of two, return what malloc returns. This is  */
  /* how memalign behaves on the c6x.                                         */
  /*--------------------------------------------------------------------------*/
  if ((alignment & (alignment - 1)) || (alignment <= 1)) 
  {
    if ((mallocPtr = malloc(size + sizeof(mallocPtr))) != NULL) 
    {
      *mallocPtr = mallocPtr;
      mallocPtr++;
    }
    return ((void *)mallocPtr);
  }
  /*--------------------------------------------------------------------------*/
  /* allocate block of memory                                                 */
  /*--------------------------------------------------------------------------*/
  if (!(mallocPtr = malloc(alignment + size))) 
  {
    return (0);
  }
  /*--------------------------------------------------------------------------*/
  /* Calculate aligned memory address                                         */
  /*--------------------------------------------------------------------------*/
  retPtr = (void *)(((Uns) mallocPtr + alignment) & ~(alignment - 1));

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
 *  @fn     mem_free
 *  @brief  Memory Free
 *
 *  @param[in] alignment  : specifies the alignment 
 *  @param[in] size       : Size of the memory to be allcoated
 *          
 *  @return success(1)/Fail(0)
********************************************************************************
*/
Void mem_free(void *ptr)
{
  free((void *)((void **)ptr)[-1]);
}

#endif
