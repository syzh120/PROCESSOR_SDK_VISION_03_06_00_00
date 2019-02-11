/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

/* ==================================================
 *  @kernel     vcop_select_list_elements
 *
 *  @desc     This function uses the selectionMask and selects only those elements from the
 *                  inputList where selectionMask at that byte location has a value of 1
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputList :
 *                          Input list data
 *                          Size of this buffer should be listSize *  sizeof(uint32_t)
 *                  selectionMask :
 *                          Mask which will be used to select elements from the list, Mask will have a value of 1
 *                          at the location where we want to pick the value from the list and 0 at other places.
 *                          The size of this mask should be multiple of 8.
 *                          Size of this buffer should be selectionMaskSize * sizeof(uint8_t)
 *                  listSize :
 *                          Total number of elements present in the list
 *                  selectionMaskSize :
 *                          Size of the mask to be used in terms of bytes. This should be multiple of 8.
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                          None
 *
 *  @outputs   This kernel produce following outputs
  *                  outputList
 *                          Pointer to the output buffer which will contain the elements which are selected from the
 *                          input list based on the mask provided
 *                          User should give a worst case buffer size which is same as inputList size
 *                  ouputListSize
 *                          Pointer to the buffer which will store the number of elements detected
 *                          Size of this buffer should be sizeof(uint8_T) * 8.
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          inputList -> ACOPY
 *                          outputList-> B COPY
 *                          selectionMask-> C COPY
 *                          ouputListSize-> Any
 *
 *  @constraints Following constraints
 *                          selectionMaskSize should be multiple of 8
 *                          listSize should be multiple of selectionMaskSize
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_select_list_elements
(
  __vptr_uint32  inputList,
  __vptr_uint32  outputList,
  __vptr_uint8   selectionMask,
  __vptr_uint16  ouputListSize,
  unsigned short listSize,
  unsigned short  selectionMaskSize
)
{
  __vector VSelectionMask;
  __vector VListData;
  __vector VMask;
  __vector VOutputListSize;
  __agen  addr0;

  VOutputListSize = 0;
  addr0 = 0;

  for(int k = 0; k < 1; k++)
  {
    _COLLATE(outputList);
    for ( int i = 0; i < (listSize / selectionMaskSize); i++)
    {
      for ( int j = 0; j < (selectionMaskSize / VCOP_SIMD_WIDTH) ; j++)
      {
        __agen inAddr;
        __agen selectionMaskAddr;

        inAddr = i * selectionMaskSize * sizeof(*inputList) + j * VCOP_SIMD_WIDTH * sizeof(*inputList);

        selectionMaskAddr = j * VCOP_SIMD_WIDTH * sizeof(*selectionMask);

        VListData       = inputList[inAddr];
        VSelectionMask  = selectionMask[selectionMaskAddr];

        /* Keep on incrementing the size based on the new elements detected.
        Once this loop finishes this vector will have 8 enteries each having some of
        elements in that lane. To get the final number of points we will have to sum
        these 8 enteries which is done in the second loop of this kernel */
        VOutputListSize += VSelectionMask;

        outputList[collate(VSelectionMask)] = VListData;

      }
    }
    ouputListSize[addr0] = VOutputListSize;
  }


  for(int i = 0; i < 1; i++)
  {
    for(int j = 0; j < 7; j++)
    {
      __agen Addr1;
      __vector VnumElems;

      Addr1 = j * sizeof(*ouputListSize);

      VnumElems = (ouputListSize + sizeof(*ouputListSize))[Addr1].onept();

      VOutputListSize += VnumElems;
    }
    ouputListSize[addr0].onept() = VOutputListSize;
  }
}


#define SELECT_LIST_ELEMENTS_PREG4  (4U)
#define SELECT_LIST_ELEMENTS_PREG14 (24U)

/* ==================================================
 *  @kernel     vcop_select_list_elements_param_block_update
 *
 *  @desc     This function is to update the values of param block for the last block size
 *
 *  @inputs   This kernel takes following Inputs
 *                  pBlock :
 *                          Pointer to the param block of vcop_select_list_elements kernel
 *                  pReg4Val :
 *                          Value to be stored at PREG 4 location. Expected value is
 *                          ((listSize / selectionMaskSize))-1u)
 *                  pReg14Val :
 *                           Value to be stored at PREG 4 location. Expected value is
 *                          -(selectionMaskSize*sizeof(*inputList))*(((listSize / selectionMaskSize))-1u) -(8u*sizeof(*inputList))*(((selectionMaskSize / (8u)))-1u))
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                          None
 *
 *  @outputs   This kernel produce following outputs
 *                          None
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          None
 *  @constraints Following constraints
 *                          None
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_select_list_elements_param_block_update
(
  __vptr_uint16   pBlock,
  unsigned short  pReg4Val,
  unsigned short  pReg14Val)
{

  __vector VPreg4Val;
  __vector VPreg14Val;
  __agen addr0 = 0;


  VPreg4Val  = pReg4Val;
  VPreg14Val = pReg14Val;

  for ( int i = 0 ; i < 1 ; i++)
  {
    (pBlock + SELECT_LIST_ELEMENTS_PREG4)[addr0].onept() = VPreg4Val;
    (pBlock + SELECT_LIST_ELEMENTS_PREG14)[addr0].onept() = VPreg14Val;
  }

}

