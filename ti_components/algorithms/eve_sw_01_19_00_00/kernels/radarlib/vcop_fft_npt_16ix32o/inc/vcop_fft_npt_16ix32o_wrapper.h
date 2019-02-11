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
/*     @file : vcop_fft_npt_16ix16o_wrapper.h                                 */
/*                                                                          */
/*     @brief : This file contains declarations for the wrapper functions   */
/*     for the different FFT sizes                                      */
/*                                                                          */
/*     Wrappers for the following FFTs are provided:    */
/*                                         */
/*                                                                          */
/*     @version 1.0 (August 2016) : Base version.                         */
/*                                                                          */
/*==========================================================================*/
#ifndef VCOP_FFT_NPT_16IX16TX32O_WRAPPER_H_
#define VCOP_FFT_NPT_16IX16TX32O_WRAPPER_H_

typedef void (*VCOP_FFT_NPT_16ix32o_KernelFuncType)(uint16_t pblock[]);

typedef struct
{
    uint16_t* pblock_stage_1;
    uint16_t* pblock_stage_2;
    uint16_t* pblock_stage_3;
    uint16_t* pblock_stage_4;
    uint16_t* pblock_stage_5;
    VCOP_FFT_NPT_16ix32o_KernelFuncType execFunc[5];
} sVCOP_FFT_1024_pBlock_t;

typedef struct
{
    uint16_t* pblock_stage_1;
    uint16_t* pblock_stage_2;
    uint16_t* pblock_stage_3;
    uint16_t* pblock_stage_4;
    uint16_t* pblock_stage_5;
    VCOP_FFT_NPT_16ix32o_KernelFuncType execFunc[5];
} sVCOP_FFT_512_pBlock_t;

typedef struct
{
    uint16_t* pblock_stage_1;
    uint16_t* pblock_stage_2;
    uint16_t* pblock_stage_3;
    uint16_t* pblock_stage_4;
    VCOP_FFT_NPT_16ix32o_KernelFuncType execFunc[4];
} sVCOP_FFT_128_pBlock_t;

typedef struct
{
    uint16_t* pblock_stage_1;
    uint16_t* pblock_stage_2;
    uint16_t* pblock_stage_3;
    uint16_t* pblock_stage_4;
    VCOP_FFT_NPT_16ix32o_KernelFuncType execFunc[4];
} sVCOP_FFT_256_pBlock_t;

typedef struct
{
    uint16_t* pblock_stage_1;
    uint16_t* pblock_stage_2;
    uint16_t* pblock_stage_3;
    VCOP_FFT_NPT_16ix32o_KernelFuncType execFunc[3];
} sVCOP_FFT_64_pBlock_t;

typedef enum{
 VCOP_FFT_NPT_16ix32o_STAGE1_OVERFLOW     = (uint32_t)1U << 0U,
 VCOP_FFT_NPT_16ix32o_STAGE2_OVERFLOW     = (uint32_t)1U << 1U,
 VCOP_FFT_NPT_16ix32o_STAGE3_OVERFLOW     = (uint32_t)1U << 2U,
 VCOP_FFT_NPT_16ix32o_STAGE4_OVERFLOW     = (uint32_t)1U << 3U,
 VCOP_FFT_NPT_16ix32o_STAGE5_OVERFLOW     = (uint32_t)1U << 4U,
 VCOP_FFT_NPT_16ix32o_STAGE_ALL_OVERFLOW  = 0xFFFFU
}VCOP_FFT_NPT_16ix32o_STAGE_OVERFLOW_MASK_TYPE;


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_512_16i_32o_param_count
 *
 *  @desc     This is a wrapper function on top of various FFT stages for 512 point
 *                FFT. This returns the param count needed for all the stages of FFT
 *
 *  @inputs   This kernel takes following Inputs
 *                NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                 NONE
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    Returns the total number of param count needed by 512 point FFT kernel
 *
 *  =======================================================
 */
uint32_t vcop_fft_512_16i_32o_param_count(void);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_512_16i_32o_init
 *
 *  @desc     This is a wrapper function of init function for all FFT stages for 512 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *              pInputDataWBuf :
 *                         Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This buffer is expected to be in WBUF
 *                          Refer testbench to know the amount of memory required for this
  *                pTwiddleFactor :
 *                          Buffer which holds twidlde factor for this kernel implementaion. The order
 *                          in which these are generated can be seen from vcop_fft_npt_16ix16o_gen_twiddleFactor.c file
 *                           Size of this buffer should be getSizeTwiddleFactor_512()
 *                 pScatterOffset :
 *                          Buffer which stores 8 indexes to be used for doing transpose. Please refer the testbench
 *                           to check how this is calculated :
 *
 *                scaleFactorArray :
 *                          Scale factor to be used for reach stage
 *                numOfLines :
 *                          Number of lines for which this processing needs to be done
 *                pblock :
 *                          Pointer to the structure param block
 *               enableInPlaceCompute :
 *                          If enabled the kernel will overwrite the input data itself otherwise output would be written to
 *                          pScratchIBufH
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                pScratchIBufL :
 *                          Scratch buffer in Image buffer L which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *                pScratchIBufH :
 *                          Scratch buffer in Image buffer H which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *
 *  @outputs   This kernel produce following outputs
 *                Output of the kernel is depends on enableInPlaceCompute
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
uint32_t vcop_fft_512_16i_32o_init(
    int16_t      pInputDataWBuf[],
    int16_t      pScratchIBufL[],
    int16_t      pScratchIBufH[],
    int16_t      twiddleFactorBuf[],
    uint16_t     *pScatterOffset,
    uint8_t      pScaleFactorOut[],
    uint8_t      numValidBits,
    uint16_t     pitch,
    uint16_t     scaleFactorArray[],
    uint16_t     numOfLines,
    uint8_t      enableInPlaceCompute,
    uint32_t      overflowMask,
    uint16_t      saturationLimit,
    uint16_t     *pblock);


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_512_16i_32o_vloops
 *
 *  @desc     This is a wrapper function of vloops function for all FFT stages for 512 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *             pblock :
 *                        Pointer to the structure param block. It is important to note that
 *                        user should not provide this pointer in memory which is not accessible to
 *                        ARP32. For this reason it is advised that user should copy the param blcok
 *                        of each stage in a local memory which is accessible to ARP32.
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
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_512_16i_32o_vloops(uint16_t pblock[]);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_512_16i_32o
 *
 *  @desc     This is a wrapper function of init and vloop for all FFT stages for 512 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *              pInputDataWBuf :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This buffer is expected to be in WBUF
 *                          Refer testbench to know the amount of memory required for this
  *                pTwiddleFactor :
 *                          Buffer which holds twidlde factor for this kernel implementaion. The order
 *                          in which these are generated can be seen from vcop_fft_npt_16ix16o_gen_twiddleFactor.c file
 *                           Size of this buffer should be getSizeTwiddleFactor_512()
 *                 pScatterOffset :
 *                          Buffer which stores 8 indexes to be used for doing transpose. Please refer the testbench
 *                           to check how this is calculated :
 *
 *                scaleFactorArray :
 *                          Scale factor to be used for reach stage
 *                numOfLines :
 *                          Number of lines for which this processing needs to be done
 *               enableInPlaceCompute :
 *                          If enabled the kernel will overwrite the input data itself otherwise output would be written to
 *                          pScratchIBufH
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                pScratchIBufL :
 *                          Scratch buffer in Image buffer L which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *                pScratchIBufH :
 *                          Scratch buffer in Image buffer H which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *
 *  @outputs   This kernel produce following outputs
 *                Output of the kernel is depends on enableInPlaceCompute
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_512_16i_32o(
    int16_t      pInputDataWBuf[],
    int16_t      pScratchIBufL[],
    int16_t      pScratchIBufH[],
    int16_t      twiddleFactorBuf[],
    uint16_t     *pScatterOffset,
    uint8_t      pScaleFactorOut[],
    uint8_t      numValidBits,
    uint16_t     pitch,
    uint16_t     scaleFactorArray[],
    uint16_t     numOfLines,
    uint8_t      enableInPlaceCompute,
    uint32_t      overflowMask,
    uint16_t      saturationLimit);



/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_128_16i_32o_param_count
 *
 *  @desc     This is a wrapper function on top of various FFT stages for 128 point
 *                FFT. This returns the param count needed for all the stages of FFT
 *
 *  @inputs   This kernel takes following Inputs
 *                NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                 NONE
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    Returns the total number of param count needed by 128 point FFT kernel
 *
 *  =======================================================
 */
uint32_t vcop_fft_128_16i_32o_param_count(void);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_128_16i_32o_init
 *
 *  @desc     This is a wrapper function of init function for all FFT stages for 128 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *              pInputDataWBuf :
 *                         Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This buffer is expected to be in WBUF
 *                          Refer testbench to know the amount of memory required for this
  *                pTwiddleFactor :
 *                          Buffer which holds twidlde factor for this kernel implementaion. The order
 *                          in which these are generated can be seen from vcop_fft_npt_16ix16o_gen_twiddleFactor.c file
 *                           Size of this buffer should be getSizeTwiddleFactor_128()
 *                 pScatterOffset :
 *                          Buffer which stores 8 indexes to be used for doing transpose. Please refer the testbench
 *                           to check how this is calculated :
 *                  pitch :
 *                         Offset in terms of number of bytes to move from one line to the next line. Pitch should be word
 *                         aligned
 *
 *                scaleFactorArray :
 *                          Scale factor to be used for reach stage
 *                numOfLines :
 *                          Number of lines for which this processing needs to be done
 *               enableInPlaceCompute :
 *                          If enabled the kernel will overwrite the input data itself otherwise output would be written to
 *                          pScratchIBufH
 *                pblock :
 *                          Pointer to the structure param block
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                pScratchIBufL :
 *                          Scratch buffer in Image buffer L which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *                pScratchIBufH :
 *                          Scratch buffer in Image buffer H which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *
 *  @outputs   This kernel produce following outputs
 *                Output of the kernel is depends on enableInPlaceCompute
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
uint32_t vcop_fft_128_16i_32o_init(
    int16_t      pInputDataWBuf[],
    int16_t      pScratchIBufL[],
    int16_t      pScratchIBufH[],
    int16_t      twiddleFactorBuf[],
    uint16_t     *pScatterOffset,
    uint8_t      pScaleFactorOut[],
    uint8_t      numValidBits,
    uint16_t     pitch,
    uint16_t     scaleFactorArray[],
    uint16_t     numOfLines,
    uint8_t      enableInPlaceCompute,
    uint32_t      overflowMask,
    uint16_t     saturationLimit,
    uint16_t     *pblock);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_128_16i_32o_vloops
 *
 *  @desc     This is a wrapper function of vloops function for all FFT stages for 128 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *             pblock :
 *                        Pointer to the structure param block. It is important to note that
 *                        user should not provide this pointer in memory which is not accessible to
 *                        ARP32. For this reason it is advised that user should copy the param blcok
 *                        of each stage in a local memory which is accessible to ARP32.
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
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_128_16i_32o_vloops(uint16_t pblock[]);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_128_16i_32o
 *
 *  @desc     This is a wrapper function of init and vloop for all FFT stages for 128 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *              pInputDataWBuf :
 *                         Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This buffer is expected to be in WBUF
 *                          Refer testbench to know the amount of memory required for this
  *                pTwiddleFactor :
 *                          Buffer which holds twidlde factor for this kernel implementaion. The order
 *                          in which these are generated can be seen from vcop_fft_npt_16ix16o_gen_twiddleFactor.c file
 *                           Size of this buffer should be getSizeTwiddleFactor_128()
 *                 pScatterOffset :
 *                          Buffer which stores 8 indexes to be used for doing transpose. Please refer the testbench
 *                           to check how this is calculated :
 *                  pitch :
 *                         Offset in terms of number of bytes to move from one line to the next line
 *
 *                scaleFactorArray :
 *                          Scale factor to be used for reach stage
 *                numOfLines :
 *                          Number of lines for which this processing needs to be done
 *               enableInPlaceCompute :
 *                          If enabled the kernel will overwrite the input data itself otherwise output would be written to
 *                          pScratchIBufH
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                pScratchIBufL :
 *                          Scratch buffer in Image buffer L which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *                pScratchIBufH :
 *                          Scratch buffer in Image buffer H which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *
 *  @outputs   This kernel produce following outputs
 *                Output of the kernel is depends on enableInPlaceCompute
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_128_16i_32o(
    int16_t      pInputDataWBuf[],
    int16_t      pScratchIBufL[],
    int16_t      pScratchIBufH[],
    int16_t      twiddleFactorBuf[],
    uint16_t     *pScatterOffset,
    uint8_t      pScaleFactorOut[],
    uint8_t      numValidBits,
    uint16_t     pitch,
    uint16_t     scaleFactorArray[],
    uint16_t     numOfLines,
    uint8_t      enableInPlaceCompute,
    uint32_t      overflowMask,
    uint16_t     saturationLimit);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_256_16i_32o_param_count
 *
 *  @desc     This is a wrapper function on top of various FFT stages for 256 point
 *                FFT. This returns the param count needed for all the stages of FFT
 *
 *  @inputs   This kernel takes following Inputs
 *                NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                 NONE
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    Returns the total number of param count needed by 256 point FFT kernel
 *
 *  =======================================================
 */
uint32_t vcop_fft_256_16i_32o_param_count(void);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_256_16i_32o_init
 *
 *  @desc     This is a wrapper function of init function for all FFT stages for 256 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *              pInputDataWBuf :
 *                         Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This buffer is expected to be in WBUF
 *                          Refer testbench to know the amount of memory required for this
  *                pTwiddleFactor :
 *                          Buffer which holds twidlde factor for this kernel implementaion. The order
 *                          in which these are generated can be seen from vcop_fft_npt_16ix16o_gen_twiddleFactor.c file
 *                           Size of this buffer should be getSizeTwiddleFactor_256()
 *                 pScatterOffset :
 *                          Buffer which stores 8 indexes to be used for doing transpose. Please refer the testbench
 *                           to check how this is calculated :
 *
 *                scaleFactorArray :
 *                          Scale factor to be used for reach stage
 *                numOfLines :
 *                          Number of lines for which this processing needs to be done
 *                  pitch :
 *                         Offset in terms of number of bytes to move from one line to the next line
 *               enableInPlaceCompute :
 *                          If enabled the kernel will overwrite the input data itself otherwise output would be written to
 *                          pScratchIBufH
 *                pblock :
 *                          Pointer to the structure param block
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                pScratchIBufL :
 *                          Scratch buffer in Image buffer L which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *                pScratchIBufH :
 *                          Scratch buffer in Image buffer H which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *
 *  @outputs   This kernel produce following outputs
 *                Output of the kernel is depends on enableInPlaceCompute
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
uint32_t vcop_fft_256_16i_32o_init(
    int16_t      pInputDataWBuf[],
    int16_t      pScratchIBufL[],
    int16_t      pScratchIBufH[],
    int16_t      twiddleFactorBuf[],
    uint16_t     *pScatterOffset,
    uint8_t      pScaleFactorOut[],
    uint8_t      numValidBits,
    uint16_t     pitch,
    uint16_t     scaleFactorArray[],
    uint16_t     numOfLines,
    uint8_t      enableInPlaceCompute,
    uint32_t      overflowMask,
    uint16_t     saturationLimit,
    uint16_t     *pblock);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_256_16i_32o_vloops
 *
 *  @desc     This is a wrapper function of vloops function for all FFT stages for 256 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *             pblock :
 *                        Pointer to the structure param block. It is important to note that
 *                        user should not provide this pointer in memory which is not accessible to
 *                        ARP32. For this reason it is advised that user should copy the param blcok
 *                        of each stage in a local memory which is accessible to ARP32.
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
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_256_16i_32o_vloops(uint16_t pblock[]);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_256_16i_32o
 *
 *  @desc     This is a wrapper function of init and vloop for all FFT stages for 256 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *              pInputDataWBuf :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This buffer is expected to be in WBUF
 *                          Refer testbench to know the amount of memory required for this
  *                pTwiddleFactor :
 *                          Buffer which holds twidlde factor for this kernel implementaion. The order
 *                          in which these are generated can be seen from vcop_fft_npt_16ix16o_gen_twiddleFactor.c file
 *                           Size of this buffer should be getSizeTwiddleFactor_256()
 *                 pScatterOffset :
 *                          Buffer which stores 8 indexes to be used for doing transpose. Please refer the testbench
 *                           to check how this is calculated :
 *                  pitch :
 *                         Offset in terms of number of bytes to move from one line to the next line
 *
 *                scaleFactorArray :
 *                          Scale factor to be used for reach stage
 *                numOfLines :
 *                          Number of lines for which this processing needs to be done
 *               enableInPlaceCompute :
 *                          If enabled the kernel will overwrite the input data itself otherwise output would be written to
 *                          pScratchIBufH
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                pScratchIBufL :
 *                          Scratch buffer in Image buffer L which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *                pScratchIBufH :
 *                          Scratch buffer in Image buffer H which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *
 *  @outputs   This kernel produce following outputs
 *                Output of the kernel is depends on enableInPlaceCompute
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_256_16i_32o(
    int16_t      pInputDataWBuf[],
    int16_t      pScratchIBufL[],
    int16_t      pScratchIBufH[],
    int16_t      twiddleFactorBuf[],
    uint16_t     *pScatterOffset,
    uint8_t      pScaleFactorOut[],
    uint8_t      numValidBits,
    uint16_t     pitch,
    uint16_t     scaleFactorArray[],
    uint16_t     numOfLines,
    uint8_t      enableInPlaceCompute,
    uint32_t     overflowMask,
    uint16_t     saturationLimit);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_64_16i_32o_param_count
 *
 *  @desc     This is a wrapper function on top of various FFT stages for 64 point
 *                FFT. This returns the param count needed for all the stages of FFT
 *
 *  @inputs   This kernel takes following Inputs
 *                NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                 NONE
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    Returns the total number of param count needed by 64 point FFT kernel
 *
 *  =======================================================
 */
uint32_t vcop_fft_64_16i_32o_param_count(void);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_64_16i_32o_init
 *
 *  @desc     This is a wrapper function of init function for all FFT stages for 64 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *              pInputDataWBuf :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This buffer is expected to be in WBUF
 *                          Refer testbench to know the amount of memory required for this
  *                pTwiddleFactor :
 *                          Buffer which holds twidlde factor for this kernel implementaion. The order
 *                          in which these are generated can be seen from vcop_fft_npt_16ix16o_gen_twiddleFactor.c file
 *                           Size of this buffer should be getSizeTwiddleFactor_64()
 *                 pScatterOffset :
 *                          Buffer which stores 8 indexes to be used for doing transpose. Please refer the testbench
 *                           to check how this is calculated :
 *
 *                scaleFactorArray :
 *                          Scale factor to be used for reach stage
 *                numOfLines :
 *                          Number of lines for which this processing needs to be done
 *                  pitch :
 *                         Offset in terms of number of bytes to move from one line to the next line
 *               enableInPlaceCompute :
 *                          If enabled the kernel will overwrite the input data itself otherwise output would be written to
 *                          pScratchIBufH
 *                pblock :
 *                          Pointer to the structure param block
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                pScratchIBufL :
 *                          Scratch buffer in Image buffer L which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *                pScratchIBufH :
 *                          Scratch buffer in Image buffer H which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *
 *  @outputs   This kernel produce following outputs
 *                Output of the kernel is depends on enableInPlaceCompute
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
uint32_t vcop_fft_64_16i_32o_init(
    int16_t      pInputDataWBuf[],
    int16_t      pScratchIBufL[],
    int16_t      pScratchIBufH[],
    int16_t      twiddleFactorBuf[],
    uint16_t     pScatterOffset[],
    uint8_t      pScaleFactorOut[],
    uint8_t      numValidBits,
    uint16_t     pitch,
    uint16_t     scaleFactorArray[],
    uint16_t     numOfLines,
    uint8_t      enableInPlaceCompute,
    uint32_t      overflowMask,
    uint16_t      saturationLimit,
    uint16_t     *pblock);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_64_16i_32o_vloops
 *
 *  @desc     This is a wrapper function of vloops function for all FFT stages for 64 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *             pblock :
 *                        Pointer to the structure param block. It is important to note that
 *                        user should not provide this pointer in memory which is not accessible to
 *                        ARP32. For this reason it is advised that user should copy the param blcok
 *                        of each stage in a local memory which is accessible to ARP32.
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
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_64_16i_32o_vloops(uint16_t pblock[]);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_64_16i_32o
 *
 *  @desc     This is a wrapper function of init and vloop for all FFT stages for 64 point. This will
 *                initialize all the param blocks;
 *
 *  @inputs   This kernel takes following Inputs
 *              pInputDataWBuf :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This buffer is expected to be in WBUF
 *                          Refer testbench to know the amount of memory required for this
  *                pTwiddleFactor :
 *                          Buffer which holds twidlde factor for this kernel implementaion. The order
 *                          in which these are generated can be seen from vcop_fft_npt_16ix16o_gen_twiddleFactor.c file
 *                           Size of this buffer should be getSizeTwiddleFactor_64()
 *                 pScatterOffset :
 *                          This is scratch buffer used to store pscatter indexes. We need to store 16 indexes for this kernel
 *                           hence size of this buffer should be 16 * sizeof(uint16_t)
 *                  pitch :
 *                         Offset in terms of number of bytes to move from one line to the next line
 *
 *                scaleFactorArray :
 *                          Scale factor to be used for reach stage
 *                numOfLines :
 *                          Number of lines for which this processing needs to be done
 *               enableInPlaceCompute :
 *                          If enabled the kernel will overwrite the input data itself otherwise output would be written to
 *                          pScratchIBufH
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                pScratchIBufL :
 *                          Scratch buffer in Image buffer L which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *                pScratchIBufH :
 *                          Scratch buffer in Image buffer H which store intermediate FFT stage result.
 *                          Refer testbench to know the amount of memory required for this
 *
 *  @outputs   This kernel produce following outputs
 *                Output of the kernel is depends on enableInPlaceCompute
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_64_16i_32o(
    int16_t      pInputDataWBuf[],
    int16_t      pScratchIBufL[],
    int16_t      pScratchIBufH[],
    int16_t      twiddleFactorBuf[],
    uint16_t     pScatterOffset[],
    uint8_t      pScaleFactorOut[],
    uint8_t      numValidBits,
    uint16_t     pitch,
    uint16_t     scaleFactorArray[],
    uint16_t     numOfLines,
    uint8_t      enableInPlaceCompute,
    uint32_t     overflowMask,
    uint16_t     saturationLimit);


#endif /*VCOP_FFT_NPT_16IX16TX32O_WRAPPER_H_*/


