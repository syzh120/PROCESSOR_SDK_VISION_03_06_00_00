/* ======================================================================= */
/* DSP_urand32.h -- Optimized C source interface header file               */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (c) 2011 Mutsuo Saito, Makoto Matsumoto, Hiroshima            */
/* University and The University of Tokyo. All rights reserved.            */
/*                                                                         */
/* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/  */
/*                                                                         */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*                                                                         */
/*    Redistributions of source code must retain the above copyright       */
/*    notice, this list of conditions and the following disclaimer.        */
/*                                                                         */
/*    Redistributions in binary form must reproduce the above copyright    */
/*    notice, this list of conditions and the following disclaimer in the  */
/*    documentation and/or other materials provided with the               */
/*    distribution.                                                        */
/*                                                                         */
/*    Neither the name of Texas Instruments Incorporated nor the names of  */
/*    its contributors may be used to endorse or promote products derived  */
/*    from this software without specific prior written permission.        */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                         */
/* ======================================================================= */

#ifndef DSP_URAND32_H_
#define DSP_URAND32_H_


#ifndef __TI_COMPILER_VERSION__           // for non TI compiler
#include "assert.h"                       // intrinsics prototypes
#include "C6xSimulator.h"                 // intrinsics prototypes
#include "C6xSimulator_type_modifiers.h"  // define/undefine typing keywords
#endif


/*===========================================================================*/
/* External Function Prototypes and Documentation                            */
/*===========================================================================*/

/** @ingroup MATH */
/* @{ */

/** @defgroup DSP_urand32_init*/
/** @ingroup  DSP_urand32_init*/
/* @{ */

/**
 *     This function is used to seed the uniformly distributed
 *     random number generator (RNG). It must be called prior to
 *     using any of the 32-bit RNG's provided in DSPLIB
 *
 *          @param seed = An arbitrary unsigned integer chosen by the user.
 *
 *          @param polynomial = Array of 3 non-arbitrary unsigned integers,
 *          previously generated using the included TinyMTDC program and/or
 *          from the provided text file; numbers from different sets @b MUST
 *          @b NOT be mixed and matched. Should the user provide a NULL
 *          pointer instead, default values will be used instead. These
 *          parameters ensure (mostly) statistically independent random
 *          numbers among different generators. Users should place numbers in
 *          the polynomial parameter in the order in which they appear in the
 *          text file or TinyMTDC program. That is columns 0, 1, and 2 (mat1,
 *          mat2, and tmat of TinyMTDC) correspond to positions 0, 1, and 2 of
 *          the polynomial.
 *
 *          @param state = An array of 7 unsigned 32-bit integers which need
 *          not be initialized to any values by the user; the user is only
 *          required to allocate such space and maintain (but @b NEVER modify)
 *          it.
 *
 * @par Algorithm:
 * The random number generator is based on the Tiny Mersenne Twister (TinyMT).
 * <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/TINYMT/"
 * >Click here for more information.</a>
 *
 * @par Assumptions:
 *     The user has properly initialized the "polynomial" and "state"
 *     parameters.
 *
 * @par Implementation notes:
 * @b Endian @b Support: The code supports both big and little endian modes. <BR>
 * @b Interruptibility: The code not interruptible. <BR>
 *
 */



void DSP_urand32_init(
    unsigned int seed,        /*Arbitrary number used for initialization     */
    void* restrict polynomial,/*Array of length 3 containing polynomial data */
    void* restrict state);    /*Array of length 7 allocated and uninitialized*/




/** @defgroup DSP_urand32*/
/** @ingroup  DSP_urand32*/
/* @{ */

/**
 *     This function is used to fill an array with uniformly distributed
 *     random unsigned 32-bit integers on the interval [0,(2^32)-1].
 *
 *          @param size = The size of the array to be filled.
 *
 *          @param vector = The array which the user wants to fill with random
 *          values. Again, it should be of type @b unsigned @b int.
 *
 *          @param state = The array which was initialized with the
 *          "DSP_urand32_init" function and maintained (but @b NEVER modified)
 *          by the user between subsequent calls to this function.
 *
 * @par Algorithm:
 * The random number generator is based on the Tiny Mersenne Twister (TinyMT).
 * <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/TINYMT/"
 * >Click here for more information.</a>
 *
 * @par Assumptions:
 *     The user has previously called the "DSP_urand32_init"
 *     function at least once, has maintained the state array, and allocated
 *     an array of @b int types of the desired width.
 *
 * @par Implementation notes:
 * @b Endian Support: The code supports both big and little endian modes. <BR>
 * @b Interruptibility: The code is not interruptible. <BR>
 *
 */

/* }@ */ /* ingroup */
/* }@ */ /* ingroup */

void DSP_urand32(unsigned int size,  /*   Size of the vector to be filled*/
                 void* vector,       /* Pointer to the destination vector*/
                 void* state);       /*   State vector maintained by user*/

/*===========================================================================*/
/* Internal Code                                                             */
/*===========================================================================*/

/* All code below this disclaimer is for internal DSPLIB use only and should
 * not be used by the user.
 */

/*================================ Typedefs ================================*/

/* Internal Portable 32-bit type */
#ifndef TI_UINT32_TYPE_
#define TI_UINT32_TYPE_

typedef unsigned int _ti_uint32;
typedef int _ti_int32;

#endif /* TI_UINT32_TYPE_*/

/*================================ Constants ===============================*/
/*State*/
#define DSP_urand32_STATUS_0 (0)
#define DSP_urand32_STATUS_1 (1)
#define DSP_urand32_STATUS_2 (2)
#define DSP_urand32_STATUS_3 (3)

/*Polynomial*/
#define DSP_urand32_MAT_1 (4)
#define DSP_urand32_MAT_2 (5)
#define DSP_urand32_TMAT  (6)

#define DSP_urand32_TINYMT_MASK  (0x7ffffffful)
#define DSPF_sp_urand_UINT_TO_FLOAT 2.3283063e-010

/*================================ Macros ==================================*/


#define DSP_urand32_SAVE_STATE(s0,s1,s2,s3)                          \
           {v_state[DSP_urand32_STATUS_0] = (s0);                    \
            v_state[DSP_urand32_STATUS_1] = (s1);                    \
            v_state[DSP_urand32_STATUS_2] = (s2);                    \
            v_state[DSP_urand32_STATUS_3] = (s3);}


/*================================ Functions ===============================*/

/* Function Name: DSP_urand32_get_ti_uint32
 *
 *  @Purpose: This function is used internally to generate a random number
 *  based on the current state It should not be called by the user. It
 *  basically concatenates the 4 status variables into one @b _ti_uint32.
 *  It should not be called by the user.
 *
 *  @Precondition: The calling function has passed valid state variable
 *  pointers and polynomial constants and "DSP_urand32_next_state()"
 *  was previously called
 *
 *  @Postcondition: A random integer based on the current state of the RNG has
 *  been returned
 *
 *  @param s0 : Pointer to the STATUS_0 variable of type @b _ti_uint32
 *  @param s2 : Pointer to the STATUS_2 variable of type @b _ti_uint32
 *  @param s3 : Pointer to the STATUS_3 variable of type @b _ti_uint32
 *
 *  @param tmat : constant polynomial characteristic number TMAT
 *   of type @b _ti_uint32
 *
 *  @returns A uniformly distributed random @b _ti_uint32.
 *
 */
#pragma CODE_SECTION(DSP_urand32_get_ti_uint32,".text:optimized");
#pragma FUNC_ALWAYS_INLINE(DSP_urand32_get_ti_uint32)
static inline _ti_uint32 DSP_urand32_get_ti_uint32(
    _ti_uint32 s0,          /*Status_0*/
    _ti_uint32 s2,          /*Status_2*/
    _ti_uint32 s3,          /*Status_3*/
    const _ti_uint32 tmat)  /*Polynomial constant tmat*/
{
  /* Temporary variables */
  _ti_uint32 j, k;

  /* Compute next random integer from the state */
  j = s3;
  k = s0 + (s2 >> 8);
  j ^= k;
  j ^= -((_ti_int32) (k & 1)) & tmat;
  return j;
} /* DSP_urand32_get_ti_uint32 */



/* Function Name : DSP_urand32_next_state
 *
 *  @Purpose : This function is used internally to modify the state so that
 *  the next random number may be generated. It should not be called by the
 *  user. This implementation is taken verbatim from the original algorithm.
 *
 *  @Precondition : The calling function has passed valid state variable
 *  pointers and polynomial constants.
 *
 *  @Postcondition : The "state machine" of the RNG has been modified
 *  so that the next random transition can occur.
 *
 *  @param s0 : Pointer to the STATUS_0 variable of type @b _ti_uint32
 *  @param s1 : Pointer to the STATUS_1 variable of type @b _ti_uint32
 *  @param s2 : Pointer to the STATUS_2 variable of type @b _ti_uint32
 *  @param s3 : Pointer to the STATUS_3 variable of type @b _ti_uint32
 *
 *  @param mat1 : constant polynomial characteristic number MAT_1
 *   of type @b _ti_uint32
 *
 *  @param mat2 : constant polynomial characteristic number MAT_2
 *   of type @b _ti_uint32
 *
 */
#pragma CODE_SECTION(DSP_urand32_next_state,".text:optimized");
#pragma FUNC_ALWAYS_INLINE(DSP_urand32_next_state)
static inline void DSP_urand32_next_state(
    _ti_uint32 *s0,         /*Status_0*/
    _ti_uint32 *s1,         /*Status_1*/
    _ti_uint32 *s2,         /*Status_2*/
    _ti_uint32 *s3,         /*Status_3*/
    const _ti_uint32 mat1,  /*Polynomial constant mat1*/
    const _ti_uint32 mat2)  /*Polynomial constant mat2*/
{
  /* Compute Next State*/

  /* Temporary variables */
    _ti_uint32 temp;

    temp = (*s0 & DSP_urand32_TINYMT_MASK) ^ *s1 ^ *s2;
    temp ^= (temp << 1);
    *s3 ^= (*s3 >> 1) ^ temp;
    *s0 = *s1;
    *s1 = *s2;
    *s2 = temp ^ (*s3 << 10);
    *s1 ^= -((_ti_int32) (*s3 & 1)) & mat1;
    *s2 ^= -((_ti_int32) (*s3 & 1)) & mat2;
} /* DSP_urand32_next_state */

/* Function Name : DSP_urand32_generate_random_ti_uint32
 *
 *  @Purpose : This function is used to generate and return a single
 *   pseudo-random @b _ti_uint32 number on the interval [0,2^32-1].
 *   It should not be called by the user.
 *
 *  @Precondition : The calling function has passed valid state variable
 *  pointers and polynomial constants.
 *
 *  @Postcondition : The "state machine" of the RNG has been modified
 *  so that the next random transition can occur and a pseudo-random
 *  @b _ti_uint32 has been returned.
 *
 *  @param s0 : Pointer to the STATUS_0 variable of type @b _ti_uint32
 *  @param s1 : Pointer to the STATUS_1 variable of type @b _ti_uint32
 *  @param s2 : Pointer to the STATUS_2 variable of type @b _ti_uint32
 *  @param s3 : Pointer to the STATUS_3 variable of type @b _ti_uint32
 *
 *  @param mat1 : constant polynomial characteristic number MAT_1
 *   of type @b _ti_uint32
 *
 *  @param mat2 : constant polynomial characteristic number MAT_2
 *   of type @b _ti_uint32
 *
 *  @param tmat : constant polynomial characteristic number TMAT
 *   of type @b _ti_uint32
 *
 *  @returns : pseudo-random @b _ti_uint32
 */

#pragma CODE_SECTION(DSP_urand32_generate_random_ti_uint32,".text:optimized");
#pragma FUNC_ALWAYS_INLINE(DSP_urand32_generate_random_ti_uint32);
static inline _ti_uint32 DSP_urand32_generate_random_ti_uint32(
       _ti_uint32 *s0, /* STATUS 0 */
       _ti_uint32 *s1, /* STATUS 1 */
       _ti_uint32 *s2, /* STATUS 2 */
       _ti_uint32 *s3, /* STATUS 3 */
       const _ti_uint32 mat1,/* Polynomial Constant MAT1 */
       const _ti_uint32 mat2,/* Polynomial Constant MAT2 */
       const _ti_uint32 tmat)/* Polynomial Constant TMAT */
{
  /*Hash the state vector*/
  DSP_urand32_next_state(s0, s1, s2, s3, mat1, mat2);

  /*Concatenate random number from state variables */
  return DSP_urand32_get_ti_uint32(*s0, *s2, *s3, tmat);

} /* DSP_urand32_generate_random_ti_uint32 */

#endif /* DSP_URAND32_H_ */

/* ======================================================================== */
/*  End of file:  DSP_urand32.h                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
