#ifndef _TI_vcop_mat_mul_kernel_h_
#define _TI_vcop_mat_mul_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_mat_mul_uchar_uchar_short[22];

/* Basic Runner Function */
void vcop_mat_mul_uchar_uchar_short(
   __vptr_uint8 in1_ary,
   __vptr_uint8 in2_ary,
   __vptr_int16 res,
   int w_in1,
   int h_in1,
   int w_in2,
   int rnd_shift);
/* Custom Runner Function */
void vcop_mat_mul_uchar_uchar_short_custom(
   __vptr_uint8 in1_ary,
   __vptr_uint8 in2_ary,
   __vptr_int16 res,
   int w_in1,
   int h_in1,
   int w_in2,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_mat_mul_uchar_uchar_short_init(
   __vptr_uint8 in1_ary,
   __vptr_uint8 in2_ary,
   __vptr_int16 res,
   int w_in1,
   int h_in1,
   int w_in2,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_mat_mul_uchar_uchar_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_mat_mul_uchar_uchar_short ((unsigned int)22)
unsigned int vcop_mat_mul_uchar_uchar_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_mat_mul_uchar_uchar_short ((unsigned int)0)
unsigned int vcop_mat_mul_uchar_uchar_short_ctrl_count(void);

/***********************************************************/
#endif

