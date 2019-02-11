#ifndef _TI_vcop_nonMaxSuppress_mxn_32s_kernel_h_
#define _TI_vcop_nonMaxSuppress_mxn_32s_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_nonMaxSuppress_mxn_32s[76];

/* Basic Runner Function */
void vcop_nonMaxSuppress_mxn_32s(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int m,
   int n,
   int thresh);
/* Custom Runner Function */
void vcop_nonMaxSuppress_mxn_32s_custom(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int m,
   int n,
   int thresh,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nonMaxSuppress_mxn_32s_init(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int m,
   int n,
   int thresh,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nonMaxSuppress_mxn_32s_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nonMaxSuppress_mxn_32s ((unsigned int)76)
unsigned int vcop_nonMaxSuppress_mxn_32s_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nonMaxSuppress_mxn_32s ((unsigned int)0)
unsigned int vcop_nonMaxSuppress_mxn_32s_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_nonMaxSuppress_mxn_32s_bitPack[68];

/* Basic Runner Function */
void vcop_nonMaxSuppress_mxn_32s_bitPack(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int windowWidth,
   int windowHeight,
   int thresh);
/* Custom Runner Function */
void vcop_nonMaxSuppress_mxn_32s_bitPack_custom(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int windowWidth,
   int windowHeight,
   int thresh,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nonMaxSuppress_mxn_32s_bitPack_init(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int windowWidth,
   int windowHeight,
   int thresh,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nonMaxSuppress_mxn_32s_bitPack_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nonMaxSuppress_mxn_32s_bitPack ((unsigned int)68)
unsigned int vcop_nonMaxSuppress_mxn_32s_bitPack_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nonMaxSuppress_mxn_32s_bitPack ((unsigned int)0)
unsigned int vcop_nonMaxSuppress_mxn_32s_bitPack_ctrl_count(void);

/***********************************************************/
#endif

