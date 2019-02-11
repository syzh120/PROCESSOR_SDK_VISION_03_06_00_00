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

/*                                                                          */

#ifndef VCOP_SELECT_LIST_ELEMENTS_CN_H_
#define VCOP_SELECT_LIST_ELEMENTS_CN_H_

/* ==================================================
 *  @func     vcop_select_list_elements_cn
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
 *
 *  @constraints Following constraints
 *                          selectionMaskSize should be multiple of 8
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_select_list_elements_cn
(
  uint32_t  *inputList,
  uint32_t  *outputList,
  uint8_t   *selectionMask,
  uint32_t   *ouputListSize,
  uint32_t  listSize,
  uint16_t  selectionMaskSize
);

#endif /* VCOP_SELECT_LIST_ELEMENTS_CN_H_ */

