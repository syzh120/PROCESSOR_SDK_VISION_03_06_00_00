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
 *  @file               ti/sdo/fc/dskt2/dskt2_mem.h
 *
 *  @brief              Functions for getting algorithm memory usage
 */

#ifndef ti_sdo_fc_dskt2_DSKT2_MEM
#define ti_sdo_fc_dskt2_DSKT2_MEM

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup ti_sdo_fc_dskt2_DSKT2 */
/*@{*/

#include "dskt2.h"

/*
 *  ======== DSKT2_getMemRecs ========
 */
/**
 *  @brief      Get records of memory allocated to an algorithm by DSKT2.
 *
 *              This function will copy up to @c nRecs records of the memory
 *              actually allocated to @c alg by DSKT2 into the @c memTab
 *              array. These records will be different then those returned
 *              by the algorithm's @c algAlloc() function, if the algorithm
 *              requested memory of a type (eg, IALG_DARAM0 or IALG_SCRATCH)
 *              that had an insufficient amount available.
 *
 *  @param[in]  alg     Handle to the algorithm instance created with
 *                      DSKT2_createAlg().
 *  @param[out] memTab  Location to copy the IALG_MemRecs assigned to the
 *                      algorithm.
 *  @param[in]  nRecs   Maximuum number of IALG_MemRec records that can be
 *                      copied into memTab.
 *
 *  @retval     > 0     The number of IALG_MemRecs copied into memTab.
 *  @retval     0       The algorithm instance could not be found in the
 *                      internal list of algorithms that have been created
 *                      through DSKT2.
 *
 *  @sa         DSKT2_getMemRecs()
 */
extern Int DSKT2_getMemRecs(IALG_Handle alg, IALG_MemRec *memTab, Int nRecs);


/*
 *  ======== DSKT2_getNumMemRecs ========
 */
/**
 *  @brief      Get the number of IALG_MemRecs used by an algorithm.
 *
 *  @param[in]  alg     Handle to the algorithm instance created with
 *                      DSKT2_createAlg().
 *
 *  @retval     > 0     The number of IALG_MemRecs used by the algorithm. This
 *                      is the same number that would be returned by the
 *                      algorithm's @c algAlloc() function.
 *  @retval     0       The algorithm instance could not be found in the
 *                      internal list of algorithms that have been created
 *                      through DSKT2.
 *
 *  @sa         DSKT2_getMemRecs()
 */
extern Int DSKT2_getNumMemRecs(IALG_Handle alg);

/*@}*/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
