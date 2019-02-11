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

#ifndef _TI_vcop_filter_kernel_h_
#define _TI_vcop_filter_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_uchar_char_uchar[22];

/* Basic Runner Function */
void vcop_filter_uchar_char_uchar(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_uint8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_uchar_char_uchar_custom(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_uint8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_uchar_char_uchar_init(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_uint8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_uchar_char_uchar_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_uchar_char_uchar ((unsigned int)22)
unsigned int vcop_filter_uchar_char_uchar_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_uchar_char_uchar ((unsigned int)0)
unsigned int vcop_filter_uchar_char_uchar_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_uchar_char_char[22];

/* Basic Runner Function */
void vcop_filter_uchar_char_char(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_uchar_char_char_custom(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_uchar_char_char_init(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_uchar_char_char_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_uchar_char_char ((unsigned int)22)
unsigned int vcop_filter_uchar_char_char_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_uchar_char_char ((unsigned int)0)
unsigned int vcop_filter_uchar_char_char_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_uchar_char_short[22];

/* Basic Runner Function */
void vcop_filter_uchar_char_short(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_uchar_char_short_custom(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_uchar_char_short_init(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_uchar_char_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_uchar_char_short ((unsigned int)22)
unsigned int vcop_filter_uchar_char_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_uchar_char_short ((unsigned int)0)
unsigned int vcop_filter_uchar_char_short_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_ushort_short_short[22];

/* Basic Runner Function */
void vcop_filter_ushort_short_short(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_ushort_short_short_custom(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_ushort_short_short_init(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_ushort_short_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_ushort_short_short ((unsigned int)22)
unsigned int vcop_filter_ushort_short_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_ushort_short_short ((unsigned int)0)
unsigned int vcop_filter_ushort_short_short_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_short_short_short[22];

/* Basic Runner Function */
void vcop_filter_short_short_short(
   __vptr_int16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_short_short_short_custom(
   __vptr_int16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_short_short_short_init(
   __vptr_int16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_short_short_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_short_short_short ((unsigned int)22)
unsigned int vcop_filter_short_short_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_short_short_short ((unsigned int)0)
unsigned int vcop_filter_short_short_short_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_ushort_ushort_short[22];

/* Basic Runner Function */
void vcop_filter_ushort_ushort_short(
   __vptr_uint16 in,
   __vptr_uint16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_ushort_ushort_short_custom(
   __vptr_uint16 in,
   __vptr_uint16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_ushort_ushort_short_init(
   __vptr_uint16 in,
   __vptr_uint16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_ushort_ushort_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_ushort_ushort_short ((unsigned int)22)
unsigned int vcop_filter_ushort_ushort_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_ushort_ushort_short ((unsigned int)0)
unsigned int vcop_filter_ushort_ushort_short_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_ushort_short_int[22];

/* Basic Runner Function */
void vcop_filter_ushort_short_int(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int32 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_ushort_short_int_custom(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int32 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_ushort_short_int_init(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int32 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_ushort_short_int_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_ushort_short_int ((unsigned int)22)
unsigned int vcop_filter_ushort_short_int_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_ushort_short_int ((unsigned int)0)
unsigned int vcop_filter_ushort_short_int_ctrl_count(void);

/***********************************************************/
#endif

