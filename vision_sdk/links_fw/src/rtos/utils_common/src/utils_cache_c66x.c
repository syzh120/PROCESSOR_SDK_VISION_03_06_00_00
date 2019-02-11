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
 * \file utils_idle_c66x.c
 *
 * \brief  APIs from this file are used to interface the CPU Idle functions
 *
 *         The APIs allow a user to enable CPU idle on a given processor.
 *
 * \version 0.0 (Dec 2014) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <ti/sysbios/family/c66/Cache.h>
#include <include/link_api/system.h>
#include <src/rtos/utils_common/include/utils_mem_cfg.h>

#define DSP_SRAM_SIZE_MAX   (288U) /* in KB's */

Void Utils_dspCacheInit(void);




/**
 *******************************************************************************
 *
 * \brief This function divids DSPL2  into a cache and heap
 *
 *******************************************************************************
 */
Void Utils_dspCacheInit(void)
{
    Cache_Size cachePrm;
    char *L1_size[] = { "0 KB", "4 KB", "8 KB", "16 KB", "32 KB"};
    char *L2_size[] = { "0 KB", "32 KB", "64 KB", "128 KB", "256 KB", "512 KB", "1024 KB"};

    Cache_getSize(&cachePrm);

    Vps_printf(" SYSTEM: CACHE: L1P = %s, L1D = %s, L2 = %s ... after boot !!!\n",
        L1_size[cachePrm.l1pSize],
        L1_size[cachePrm.l1dSize],
        L2_size[cachePrm.l2Size]
        );

    #if 0 /*def ENABLE_HEAP_L2 */
    {
        UInt32 heapSize = (UInt32)((UInt32)UTILS_MEM_L2RAM_SIZE/(UInt32)1024U);
        /* INVARIANT_CONDITION.UNREACH
        * MISRAC_2004_Rule_13.7
        * MISRAC_WAIVER:
        * Code is currently unreachable.
        * This is kept to ensure future updates to macro / memory region.
        */
        if(heapSize <= (DSP_SRAM_SIZE_MAX-(UInt32)256U))
        {
            cachePrm.l2Size = Cache_L2Size_256K;
        }
        else if(heapSize <= (DSP_SRAM_SIZE_MAX-(UInt32)128U))
        {
            cachePrm.l2Size = Cache_L2Size_128K;
        }
        else if(heapSize <= (DSP_SRAM_SIZE_MAX-(UInt32)64U))
        {
            cachePrm.l2Size = Cache_L2Size_64K;
        }
        else if(heapSize <= (DSP_SRAM_SIZE_MAX-(UInt32)32U))
        {
            cachePrm.l2Size = Cache_L2Size_32K;
        }
        else
        {
            cachePrm.l2Size = Cache_L2Size_0K;
        }

        Cache_setSize(&cachePrm);
    }
    #endif

    Cache_getSize(&cachePrm);

    Vps_printf(" SYSTEM: CACHE: L1P = %s, L1D = %s, L2 = %s ... after update by APP !!!\n",
        L1_size[cachePrm.l1pSize],
        L1_size[cachePrm.l1dSize],
        L2_size[cachePrm.l2Size]
        );
}


/* Nothing beyond this point */
