/*
*
* Copyright (c) {YEAR} Texas Instruments Incorporated
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

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage1_0[];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage1_0(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage1_0_custom(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short* pblock);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage1_0_init(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short* pblock);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage1_0_vloops(
   unsigned short* pblock);

/* Parameter Register Count Function */
unsigned int vcop_fft_1024_32x16t_stage1_0_param_count();
/* Internal Value Count */
unsigned int vcop_fft_1024_32x16t_stage1_0_ctrl_count();

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage1_1[];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage1_1(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage1_1_custom(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short* pblock);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage1_1_init(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short* pblock);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage1_1_vloops(
   unsigned short* pblock);

/* Parameter Register Count Function */
unsigned int vcop_fft_1024_32x16t_stage1_1_param_count();
/* Internal Value Count */
unsigned int vcop_fft_1024_32x16t_stage1_1_ctrl_count();

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage2_0[];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage2_0(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage2_0_custom(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short* pblock);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage2_0_init(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short* pblock);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage2_0_vloops(
   unsigned short* pblock);

/* Parameter Register Count Function */
unsigned int vcop_fft_1024_32x16t_stage2_0_param_count();
/* Internal Value Count */
unsigned int vcop_fft_1024_32x16t_stage2_0_ctrl_count();

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage2_1[];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage2_1(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage2_1_custom(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short* pblock);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage2_1_init(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short* pblock);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage2_1_vloops(
   unsigned short* pblock);

/* Parameter Register Count Function */
unsigned int vcop_fft_1024_32x16t_stage2_1_param_count();
/* Internal Value Count */
unsigned int vcop_fft_1024_32x16t_stage2_1_ctrl_count();

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage3_0[];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage3_0(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage3_0_custom(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short* pblock);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage3_0_init(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short* pblock);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage3_0_vloops(
   unsigned short* pblock);

/* Parameter Register Count Function */
unsigned int vcop_fft_1024_32x16t_stage3_0_param_count();
/* Internal Value Count */
unsigned int vcop_fft_1024_32x16t_stage3_0_ctrl_count();

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage3_1[];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage3_1(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 C,
   __vptr_int16 S,
   __vptr_int32 out_x,
   __vptr_int32 out_y);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage3_1_custom(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 C,
   __vptr_int16 S,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short* pblock);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage3_1_init(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 C,
   __vptr_int16 S,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short* pblock);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage3_1_vloops(
   unsigned short* pblock);

/* Parameter Register Count Function */
unsigned int vcop_fft_1024_32x16t_stage3_1_param_count();
/* Internal Value Count */
unsigned int vcop_fft_1024_32x16t_stage3_1_ctrl_count();

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage4_0[];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage4_0(
   __vptr_int32 Pin_xL0_01234567,
   __vptr_int32 Pin_yL0_01234567,
   __vptr_int32 Pin_xL1_01234567,
   __vptr_int32 Pin_yL1_01234567,
   __vptr_int32 Pin_xL2_01234567,
   __vptr_int32 Pin_yL2_01234567,
   __vptr_int32 Pin_xL3_01234567,
   __vptr_int32 Pin_yL3_01234567,
   __vptr_int32 Pou_xL0_01234567,
   __vptr_int32 Pou_yL0_01234567,
   __vptr_int32 Pou_xL1_01234567,
   __vptr_int32 Pou_yL1_01234567,
   __vptr_int32 Pou_xL2_01234567,
   __vptr_int32 Pou_yL2_01234567,
   __vptr_int32 Pou_xL3_01234567,
   __vptr_int32 Pou_yL3_01234567);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage4_0_custom(
   __vptr_int32 Pin_xL0_01234567,
   __vptr_int32 Pin_yL0_01234567,
   __vptr_int32 Pin_xL1_01234567,
   __vptr_int32 Pin_yL1_01234567,
   __vptr_int32 Pin_xL2_01234567,
   __vptr_int32 Pin_yL2_01234567,
   __vptr_int32 Pin_xL3_01234567,
   __vptr_int32 Pin_yL3_01234567,
   __vptr_int32 Pou_xL0_01234567,
   __vptr_int32 Pou_yL0_01234567,
   __vptr_int32 Pou_xL1_01234567,
   __vptr_int32 Pou_yL1_01234567,
   __vptr_int32 Pou_xL2_01234567,
   __vptr_int32 Pou_yL2_01234567,
   __vptr_int32 Pou_xL3_01234567,
   __vptr_int32 Pou_yL3_01234567,
   unsigned short* pblock);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage4_0_init(
   __vptr_int32 Pin_xL0_01234567,
   __vptr_int32 Pin_yL0_01234567,
   __vptr_int32 Pin_xL1_01234567,
   __vptr_int32 Pin_yL1_01234567,
   __vptr_int32 Pin_xL2_01234567,
   __vptr_int32 Pin_yL2_01234567,
   __vptr_int32 Pin_xL3_01234567,
   __vptr_int32 Pin_yL3_01234567,
   __vptr_int32 Pou_xL0_01234567,
   __vptr_int32 Pou_yL0_01234567,
   __vptr_int32 Pou_xL1_01234567,
   __vptr_int32 Pou_yL1_01234567,
   __vptr_int32 Pou_xL2_01234567,
   __vptr_int32 Pou_yL2_01234567,
   __vptr_int32 Pou_xL3_01234567,
   __vptr_int32 Pou_yL3_01234567,
   unsigned short* pblock);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage4_0_vloops(
   unsigned short* pblock);

/* Parameter Register Count Function */
unsigned int vcop_fft_1024_32x16t_stage4_0_param_count();
/* Internal Value Count */
unsigned int vcop_fft_1024_32x16t_stage4_0_ctrl_count();

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage4_1[];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage4_1(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 CS,
   __vptr_int32 out_x,
   __vptr_int32 out_y);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage4_1_custom(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 CS,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short* pblock);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage4_1_init(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 CS,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short* pblock);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage4_1_vloops(
   unsigned short* pblock);

/* Parameter Register Count Function */
unsigned int vcop_fft_1024_32x16t_stage4_1_param_count();
/* Internal Value Count */
unsigned int vcop_fft_1024_32x16t_stage4_1_ctrl_count();

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage5[];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage5(
   __vptr_int32 Pxi0,
   __vptr_int32 Pyi0,
   __vptr_int32 Pxi1,
   __vptr_int32 Pyi1,
   __vptr_int32 Pxi2,
   __vptr_int32 Pyi2,
   __vptr_int32 Pxi3,
   __vptr_int32 Pyi3,
   __vptr_int32 Pox0,
   __vptr_int32 Poy0,
   __vptr_int32 Pox1,
   __vptr_int32 Poy1,
   __vptr_int32 Pox2,
   __vptr_int32 Poy2,
   __vptr_int32 Pox3,
   __vptr_int32 Poy3);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage5_custom(
   __vptr_int32 Pxi0,
   __vptr_int32 Pyi0,
   __vptr_int32 Pxi1,
   __vptr_int32 Pyi1,
   __vptr_int32 Pxi2,
   __vptr_int32 Pyi2,
   __vptr_int32 Pxi3,
   __vptr_int32 Pyi3,
   __vptr_int32 Pox0,
   __vptr_int32 Poy0,
   __vptr_int32 Pox1,
   __vptr_int32 Poy1,
   __vptr_int32 Pox2,
   __vptr_int32 Poy2,
   __vptr_int32 Pox3,
   __vptr_int32 Poy3,
   unsigned short* pblock);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage5_init(
   __vptr_int32 Pxi0,
   __vptr_int32 Pyi0,
   __vptr_int32 Pxi1,
   __vptr_int32 Pyi1,
   __vptr_int32 Pxi2,
   __vptr_int32 Pyi2,
   __vptr_int32 Pxi3,
   __vptr_int32 Pyi3,
   __vptr_int32 Pox0,
   __vptr_int32 Poy0,
   __vptr_int32 Pox1,
   __vptr_int32 Poy1,
   __vptr_int32 Pox2,
   __vptr_int32 Poy2,
   __vptr_int32 Pox3,
   __vptr_int32 Poy3,
   unsigned short* pblock);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage5_vloops(
   unsigned short* pblock);

/* Parameter Register Count Function */
unsigned int vcop_fft_1024_32x16t_stage5_param_count();
/* Internal Value Count */
unsigned int vcop_fft_1024_32x16t_stage5_ctrl_count();

/***********************************************************/
