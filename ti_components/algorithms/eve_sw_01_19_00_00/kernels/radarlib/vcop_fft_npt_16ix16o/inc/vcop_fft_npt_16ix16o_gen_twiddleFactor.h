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
/*     @file : vcop_fft_npt_16ix16o_gen_twiddleFactor.h                                 */
/*                                                                          */
/*     @brief : This file contains declarations for the functions to generate twiddle factor  */
/*     for target implementation   */
/*                                                                          */
/*                                         */
/*                                                                          */
/*     @version 1.0 (August 2016) : Base version.                         */
/*                                                                          */

#ifndef VCOP_FFT_NPT_16IX16O_GEN_TWIDDLEFACTOR_H_
#define VCOP_FFT_NPT_16IX16O_GEN_TWIDDLEFACTOR_H_ 1

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     getSizeTwiddleFactor_1024
 *
 *  @desc     This function return the size required to store twiddle factor
 *
 *  @inputs   This kernel takes following Inputs
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    Size of twiddle factor required in terms of bytes
 *
 *  =======================================================
 */
uint32_t getSizeTwiddleFactor_1024(void);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     generateTwiddleFactor_1024
 *
 *  @desc     This function generates twiddle factor to be used for the target FFT implementation of 1024
 *                point
 *
 *  @inputs   This kernel takes following Inputs
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                twiddleFactorBuf
 *                          This buffer will get populated  by this function with the corresponding twiddle factors.
 *                           Size of this buffer can be requested using getSizeTwiddleFactor_1024 function.

 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    None
 *
 *  =======================================================
 */
void generateTwiddleFactor_1024(int16_t  twiddleFactorBuf[]);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     getSizeTwiddleFactor_512
 *
 *  @desc     This function return the size required to store twiddle factor
 *
 *  @inputs   This kernel takes following Inputs
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    Size of twiddle factor required in terms of bytes
 *
 *  =======================================================
 */
uint32_t getSizeTwiddleFactor_512(void);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     generateTwiddleFactor_512
 *
 *  @desc     This function generates twiddle factor to be used for the target FFT implementation of 512
 *                point
 *
 *  @inputs   This kernel takes following Inputs
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                twiddleFactorBuf
 *                          This buffer will get populated  by this function with the corresponding twiddle factors.
 *                           Size of this buffer can be requested using getSizeTwiddleFactor_512 function.

 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    None
 *
 *  =======================================================
 */
void generateTwiddleFactor_512(int16_t twiddleFactorBuf[]);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     getSizeTwiddleFactor_128
 *
 *  @desc     This function return the size required to store twiddle factor
 *
 *  @inputs   This kernel takes following Inputs
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    Size of twiddle factor required in terms of bytes
 *
 *  =======================================================
 */
uint32_t getSizeTwiddleFactor_128(void);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     generateTwiddleFactor_128
 *
 *  @desc     This function generates twiddle factor to be used for the target FFT implementation of 128
 *                point
 *
 *  @inputs   This kernel takes following Inputs
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                twiddleFactorBuf
 *                          This buffer will get populated  by this function with the corresponding twiddle factors.
 *                           Size of this buffer can be requested using getSizeTwiddleFactor_128 function.
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    None
 *
 *  =======================================================
 */
void generateTwiddleFactor_128(int16_t twiddleFactorBuf[]);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     getSizeTwiddleFactor_256
 *
 *  @desc     This function return the size required to store twiddle factor
 *
 *  @inputs   This kernel takes following Inputs
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    Size of twiddle factor required in terms of bytes
 *
 *  =======================================================
 */
uint32_t getSizeTwiddleFactor_256(void);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     generateTwiddleFactor_256
 *
 *  @desc     This function generates twiddle factor to be used for the target FFT implementation of 256
 *                point
 *
 *  @inputs   This kernel takes following Inputs
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                twiddleFactorBuf
 *                          This buffer will get populated  by this function with the corresponding twiddle factors.
 *                           Size of this buffer can be requested using getSizeTwiddleFactor_256 function.
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    None
 *
 *  =======================================================
 */
void generateTwiddleFactor_256(int16_t twiddleFactorBuf[]);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     getSizeTwiddleFactor_64
 *
 *  @desc     This function return the size required to store twiddle factor
 *
 *  @inputs   This kernel takes following Inputs
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    Size of twiddle factor required in terms of bytes
 *
 *  =======================================================
 */
uint32_t getSizeTwiddleFactor_64(void);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     generateTwiddleFactor_64
 *
 *  @desc     This function generates twiddle factor to be used for the target FFT implementation of 64
 *                point
 *
 *  @inputs   This kernel takes following Inputs
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                twiddleFactorBuf
 *                          This buffer will get populated  by this function with the corresponding twiddle factors.
 *                           Size of this buffer can be requested using getSizeTwiddleFactor_64 function.
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    None
 *
 *  =======================================================
 */
void generateTwiddleFactor_64(int16_t twiddleFactorBuf[]);


#endif /*VCOP_FFT_NPT_16IX16O_GEN_TWIDDLEFACTOR_H_*/


/* ======================================================================== */
/*  End of file:  vcop_fft_npt_16ix16o_gen_twiddleFactor.h                                       */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2001 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

