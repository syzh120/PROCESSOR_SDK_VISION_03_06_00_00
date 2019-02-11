#ifndef _TI_vcop_sum_grad_cross_inter_frame_diff_7x7_kernel_h_
#define _TI_vcop_sum_grad_cross_inter_frame_diff_7x7_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_sum_grad_cross_inter_frame_diff_7x7[44];

/* Basic Runner Function */
void vcop_sum_grad_cross_inter_frame_diff_7x7(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   __vptr_uint8 im1_a,
   __vptr_uint8 im2_b,
   unsigned short gradStride,
   unsigned short imStride,
   unsigned short n,
   __vptr_int32 IxIt_a,
   __vptr_int32 IyIt_b,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b);
/* Custom Runner Function */
void vcop_sum_grad_cross_inter_frame_diff_7x7_custom(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   __vptr_uint8 im1_a,
   __vptr_uint8 im2_b,
   unsigned short gradStride,
   unsigned short imStride,
   unsigned short n,
   __vptr_int32 IxIt_a,
   __vptr_int32 IyIt_b,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_sum_grad_cross_inter_frame_diff_7x7_init(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   __vptr_uint8 im1_a,
   __vptr_uint8 im2_b,
   unsigned short gradStride,
   unsigned short imStride,
   unsigned short n,
   __vptr_int32 IxIt_a,
   __vptr_int32 IyIt_b,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_sum_grad_cross_inter_frame_diff_7x7_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_sum_grad_cross_inter_frame_diff_7x7 ((unsigned int)44)
unsigned int vcop_sum_grad_cross_inter_frame_diff_7x7_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_sum_grad_cross_inter_frame_diff_7x7 ((unsigned int)0)
unsigned int vcop_sum_grad_cross_inter_frame_diff_7x7_ctrl_count(void);

/***********************************************************/
#endif

