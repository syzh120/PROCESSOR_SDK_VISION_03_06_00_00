#ifndef _TI_vcop_vec_bin_image_morph_diff_kernel_h_
#define _TI_vcop_vec_bin_image_morph_diff_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_vec_bin_image_morph_diff[24];

/* Basic Runner Function */
void vcop_vec_bin_image_morph_diff(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint32 data1_ptr,
   unsigned short data1_bit_shift,
   __vptr_uint32 data2_ptr,
   unsigned short data2_bit_shift,
   __vptr_uint32 output_ptr);
/* Custom Runner Function */
void vcop_vec_bin_image_morph_diff_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint32 data1_ptr,
   unsigned short data1_bit_shift,
   __vptr_uint32 data2_ptr,
   unsigned short data2_bit_shift,
   __vptr_uint32 output_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vec_bin_image_morph_diff_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint32 data1_ptr,
   unsigned short data1_bit_shift,
   __vptr_uint32 data2_ptr,
   unsigned short data2_bit_shift,
   __vptr_uint32 output_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vec_bin_image_morph_diff_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vec_bin_image_morph_diff ((unsigned int)24)
unsigned int vcop_vec_bin_image_morph_diff_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vec_bin_image_morph_diff ((unsigned int)0)
unsigned int vcop_vec_bin_image_morph_diff_ctrl_count(void);

/***********************************************************/
#endif

