#ifndef _TI_vcop_tensor_matrix_7x7_s16_grad_kernel_h_
#define _TI_vcop_tensor_matrix_7x7_s16_grad_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_tensor_matrix_7x7_s16_grad[54];

/* Basic Runner Function */
void vcop_tensor_matrix_7x7_s16_grad(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   unsigned short stride,
   unsigned short n,
   __vptr_int32 Ix2_a,
   __vptr_int32 Iy2_b,
   __vptr_int32 Ixy_c,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   __vptr_int32 scartch_c);
/* Custom Runner Function */
void vcop_tensor_matrix_7x7_s16_grad_custom(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   unsigned short stride,
   unsigned short n,
   __vptr_int32 Ix2_a,
   __vptr_int32 Iy2_b,
   __vptr_int32 Ixy_c,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   __vptr_int32 scartch_c,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_tensor_matrix_7x7_s16_grad_init(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   unsigned short stride,
   unsigned short n,
   __vptr_int32 Ix2_a,
   __vptr_int32 Iy2_b,
   __vptr_int32 Ixy_c,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   __vptr_int32 scartch_c,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_tensor_matrix_7x7_s16_grad_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_tensor_matrix_7x7_s16_grad ((unsigned int)54)
unsigned int vcop_tensor_matrix_7x7_s16_grad_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_tensor_matrix_7x7_s16_grad ((unsigned int)0)
unsigned int vcop_tensor_matrix_7x7_s16_grad_ctrl_count(void);

/***********************************************************/
#endif

