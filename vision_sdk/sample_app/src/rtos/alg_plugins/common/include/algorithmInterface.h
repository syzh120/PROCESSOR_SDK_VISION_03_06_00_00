/******************************************************************************
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
******************************************************************************/
/*
 *=======================================================================
 *
 * \file algorithmInterface.h
 *
 * \brief Interface file for memory requests and other interactions between
 *        algorithm and framework
 *
 *        This interface file is a clean and quick way only for short term
 *        It is NOT product quality.
 *
 *        Usage Flow:
 *        Step1: Framework shall call function Algorithm_memQuery
 *        with create time params and pointer to struct AlgLink_MemRequests
 *        Step2: Algorithm shall implement function Algorithm_memQuery.
 *        In this function, it shall populate all the necessary
 *        memory requests based on the create time parameters.
 *          NOTE: Memory needed for algorithm internal object also needs to be
 *          requested. So it will be one of the element in memTab array.
 *          Keep it as the first element memtab[0]
 *        Step3: Framework shall allocate the requested memory and populate
 *        pointer in memTab structure
 *        Step4: Framework shall call function Algorithm_create
 *        with create time params and pointer to struct AlgLink_MemRequests
 *        Step5: Now algorithm will have all the pointer values for all buffers
 *
 * \version 0.0 (Oct 8 2013) : PS
 * \version 0.1 (Oct 9 2013) : BZ
 *=======================================================================*/

#ifndef _IMEMEREQUESTALGO_H_
#define _IMEMEREQUESTALGO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 ******************************************************************************/
#define MAX_NUM_MEMORY_REQUESTS (16)
/**< Maximum number of memory requests */

#define ALGORITHM_PROCESS_OK (SYSTEM_LINK_STATUS_SOK)
/**< Return value for algorithm process being successful */

#define ALGORITHM_PROCESS_FAIL (SYSTEM_LINK_STATUS_EFAIL)
/**< Return value for algorithm process being failure */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for the various memory locations
 *
 *******************************************************************************
*/
typedef enum
{
    ALGORITHM_LINK_MEM_DSPL1D = 0,
    /**< DSP L1D */

    ALGORITHM_LINK_MEM_DSPL2,
    /**< DSP L2 */

    ALGORITHM_LINK_MEM_OCMC,
    /**< OCMC */

    ALGORITHM_LINK_MEM_DDR,
    /**< DDR */

    ALGORITHM_LINK_MEM_FORCE32BITS = 0xFFFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} AlgorithmLink_MemoryLocation;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure for one memory request
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 size;
    /**< Size of the memory buffer needed */
    UInt32 alignment;
    /**< Alignment (in bytes) needed for base address of the buffer */
    UInt32 persistentFlag;
    /**< 1 - Persitant memory request, 0 - Scratch memory request */
    AlgorithmLink_MemoryLocation memLocation;
    /**< To indication the location where memory is needed */
    void * basePtr;
    /**< Alignment needed for base address of the pointer */
} AlgLink_MemTab;

/**
 *******************************************************************************
 *
 *   \brief Structure of all memory requests to be exchanged between alg
 *          and framework
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 numMemTabs;
    /**< Number of memory requests done by the algorithm */
    AlgLink_MemTab memTab[MAX_NUM_MEMORY_REQUESTS];
    /**< Place holder for all the memory requests */
} AlgLink_MemRequests;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
