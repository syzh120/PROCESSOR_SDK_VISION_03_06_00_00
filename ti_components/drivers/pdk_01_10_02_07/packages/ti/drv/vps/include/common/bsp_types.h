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
 *  \file bsp_types.h
 *
 *  \brief BSP header file containing commonly used data types and macros.
 *
 */

#ifndef BSP_TYPES_H_
#define BSP_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined(__GNUC__) && !defined(__ti__)
/* GCC */
#define DATA_SECTION(section_name)     __attribute__((section(section_name)))
#define DATA_ALIGN(x)                  __attribute__((aligned(x)))
#endif

/*
 * =========== Error codes returned by BSP functions ===========
 */
/** \brief BSP return type for OK */
#define BSP_SOK                         ((Int32) 0)
/** \brief BSP return type for FAIL */
#define BSP_EFAIL                       (-((int32_t) 1))
/** \brief BSP return type for Bad Arguments */
#define BSP_EBADARGS                    (-((int32_t) 2))
/** \brief BSP return type for BInvalid Parameters */
#define BSP_EINVALID_PARAMS             (-((int32_t) 3))
/** \brief BSP return type for Device In Use */
#define BSP_EDEVICE_INUSE               (-((int32_t) 4))
/** \brief BSP return type for Timeout */
#define BSP_ETIMEOUT                    (-((int32_t) 5))
/** \brief BSP return type for Alloc error */
#define BSP_EALLOC                      (-((int32_t) 6))
/** \brief BSP return type for Out of Range */
#define BSP_EOUT_OF_RANGE               (-((int32_t) 7))
/** \brief BSP return type for Try Again */
#define BSP_EAGAIN                      (-((int32_t) 8))
/** \brief BSP return type for Unsupported Command */
#define BSP_EUNSUPPORTED_CMD            (-((int32_t) 9))
/** \brief BSP return type for Nomore Buffers */
#define BSP_ENO_MORE_BUFFERS            (-((int32_t) 10))
/** \brief BSP return type for Unsupported option */
#define BSP_EUNSUPPORTED_OPS            (-((int32_t) 11))
/** \brief BSP return type for Driver in Use */
#define BSP_EDRIVER_INUSE               (-((int32_t) 12))
/** \brief BSP return type for Non Recommended parameters */
#define BSP_WNON_RECOMMENDED_PARAMS     (-((int32_t) 13))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_TYPES_H_ */
