/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file bsp_common.h
 *
 *  \brief BSP header file containing commonly used functions.
 *
 */

#ifndef BSP_COMMON_H_
#define BSP_COMMON_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief BSP common library initialization parameters.
 */
typedef struct
{
    UInt32 reserved;
    /**< Reserved. Not used as of now. */
} Bsp_CommonInitParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Init the the BSP common library. This function should be called
 *  before calling any of the common utility APIs.
 *
 *  \param initPrms     [IN] Common library initialization parameters. This
 *                           parameter can't be NULL.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_commonInit(const Bsp_CommonInitParams *initPrms);

/**
 *  \brief De-init the common library.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_commonDeInit(Ptr args);

/**
 *  \brief Bsp_CommonInitParams structure init function.
 *
 *  \param initPrms     [IN] Pointer to #Bsp_CommonInitParams structure.
 *
 */
static inline void BspCommonInitParams_init(Bsp_CommonInitParams *initPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void BspCommonInitParams_init(Bsp_CommonInitParams *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->reserved = 0;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_COMMON_H_ */
