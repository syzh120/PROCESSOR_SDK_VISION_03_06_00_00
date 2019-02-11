#ifndef _TI_vcop_compute_rBrief_kernel_h_
#define _TI_vcop_compute_rBrief_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_compute_rBrief[220];

/* Basic Runner Function */
void vcop_compute_rBrief(
   __vptr_int8 moments_col_mask,
   __vptr_int16 moments_col_sum,
   __vptr_int8 moments_row_mask,
   __vptr_int16 moments_row_sum,
   __vptr_int16 moments_m10,
   __vptr_int16 moments_m01,
   __vptr_uint16 arctan_xthr,
   __vptr_uint8 arctan_pack_decision,
   __vptr_int16 cos_array_ptr,
   __vptr_int16 sin_array_ptr,
   __vptr_uint16 offset_ptr,
   __vptr_int16 cos_ptr,
   __vptr_int16 sin_ptr,
   __vptr_uint8 input_image_ptr,
   __vptr_int16 col_sum_ptr,
   __vptr_int16 row_col_sum_ct_ptr,
   __vptr_int8 in_src_dst_x_ptr,
   __vptr_int8 in_src_dst_y_ptr,
   __vptr_int8 rot_src_dst_ptr_x,
   __vptr_int8 rot_src_dst_ptr_y,
   __vptr_uint16 rot_src_lin_ptr,
   __vptr_uint16 rot_dst_lin_ptr,
   __vptr_int16 tlu_src_ptr,
   __vptr_int16 tlu_dst_ptr,
   __vptr_uint8 true_descriptor_optr);
/* Custom Runner Function */
void vcop_compute_rBrief_custom(
   __vptr_int8 moments_col_mask,
   __vptr_int16 moments_col_sum,
   __vptr_int8 moments_row_mask,
   __vptr_int16 moments_row_sum,
   __vptr_int16 moments_m10,
   __vptr_int16 moments_m01,
   __vptr_uint16 arctan_xthr,
   __vptr_uint8 arctan_pack_decision,
   __vptr_int16 cos_array_ptr,
   __vptr_int16 sin_array_ptr,
   __vptr_uint16 offset_ptr,
   __vptr_int16 cos_ptr,
   __vptr_int16 sin_ptr,
   __vptr_uint8 input_image_ptr,
   __vptr_int16 col_sum_ptr,
   __vptr_int16 row_col_sum_ct_ptr,
   __vptr_int8 in_src_dst_x_ptr,
   __vptr_int8 in_src_dst_y_ptr,
   __vptr_int8 rot_src_dst_ptr_x,
   __vptr_int8 rot_src_dst_ptr_y,
   __vptr_uint16 rot_src_lin_ptr,
   __vptr_uint16 rot_dst_lin_ptr,
   __vptr_int16 tlu_src_ptr,
   __vptr_int16 tlu_dst_ptr,
   __vptr_uint8 true_descriptor_optr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_compute_rBrief_init(
   __vptr_int8 moments_col_mask,
   __vptr_int16 moments_col_sum,
   __vptr_int8 moments_row_mask,
   __vptr_int16 moments_row_sum,
   __vptr_int16 moments_m10,
   __vptr_int16 moments_m01,
   __vptr_uint16 arctan_xthr,
   __vptr_uint8 arctan_pack_decision,
   __vptr_int16 cos_array_ptr,
   __vptr_int16 sin_array_ptr,
   __vptr_uint16 offset_ptr,
   __vptr_int16 cos_ptr,
   __vptr_int16 sin_ptr,
   __vptr_uint8 input_image_ptr,
   __vptr_int16 col_sum_ptr,
   __vptr_int16 row_col_sum_ct_ptr,
   __vptr_int8 in_src_dst_x_ptr,
   __vptr_int8 in_src_dst_y_ptr,
   __vptr_int8 rot_src_dst_ptr_x,
   __vptr_int8 rot_src_dst_ptr_y,
   __vptr_uint16 rot_src_lin_ptr,
   __vptr_uint16 rot_dst_lin_ptr,
   __vptr_int16 tlu_src_ptr,
   __vptr_int16 tlu_dst_ptr,
   __vptr_uint8 true_descriptor_optr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_compute_rBrief_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_compute_rBrief ((unsigned int)220)
unsigned int vcop_compute_rBrief_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_compute_rBrief ((unsigned int)0)
unsigned int vcop_compute_rBrief_ctrl_count(void);

/***********************************************************/
#endif

