#ifndef _TI_vcop_bayer_subsampling_kernel_h_
#define _TI_vcop_bayer_subsampling_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_bayer_subSampling[16];

/* Basic Runner Function */
void bayer_subSampling(
   __vptr_uint16 CFA_short,
   __vptr_uint16 subSample_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned int subSample_X,
   unsigned int subSample_Y,
   unsigned int NumOfSample);
/* Custom Runner Function */
void bayer_subSampling_custom(
   __vptr_uint16 CFA_short,
   __vptr_uint16 subSample_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned int subSample_X,
   unsigned int subSample_Y,
   unsigned int NumOfSample,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int bayer_subSampling_init(
   __vptr_uint16 CFA_short,
   __vptr_uint16 subSample_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned int subSample_X,
   unsigned int subSample_Y,
   unsigned int NumOfSample,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void bayer_subSampling_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_bayer_subSampling ((unsigned int)16)
unsigned int bayer_subSampling_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_bayer_subSampling ((unsigned int)0)
unsigned int bayer_subSampling_ctrl_count(void);

/***********************************************************/
#endif

