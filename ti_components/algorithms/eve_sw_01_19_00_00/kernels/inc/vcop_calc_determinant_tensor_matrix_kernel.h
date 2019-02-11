#ifndef _TI_vcop_calc_determinant_tensor_matrix_kernel_h_
#define _TI_vcop_calc_determinant_tensor_matrix_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_calc_determinant_tensor_matrix[30];

/* Basic Runner Function */
void vcop_calc_determinant_tensor_matrix(
   __vptr_uint16 Ix2L_a,
   __vptr_uint16 Iy2L_b,
   __vptr_uint16 IxyL_c,
   __vptr_int16 Ix2H_a,
   __vptr_int16 Iy2H_b,
   __vptr_int16 IxyH_c,
   __vptr_uint16 d_nrsb_a,
   __vptr_int32 d_norm_b,
   unsigned short n);
/* Custom Runner Function */
void vcop_calc_determinant_tensor_matrix_custom(
   __vptr_uint16 Ix2L_a,
   __vptr_uint16 Iy2L_b,
   __vptr_uint16 IxyL_c,
   __vptr_int16 Ix2H_a,
   __vptr_int16 Iy2H_b,
   __vptr_int16 IxyH_c,
   __vptr_uint16 d_nrsb_a,
   __vptr_int32 d_norm_b,
   unsigned short n,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_calc_determinant_tensor_matrix_init(
   __vptr_uint16 Ix2L_a,
   __vptr_uint16 Iy2L_b,
   __vptr_uint16 IxyL_c,
   __vptr_int16 Ix2H_a,
   __vptr_int16 Iy2H_b,
   __vptr_int16 IxyH_c,
   __vptr_uint16 d_nrsb_a,
   __vptr_int32 d_norm_b,
   unsigned short n,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_calc_determinant_tensor_matrix_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_calc_determinant_tensor_matrix ((unsigned int)30)
unsigned int vcop_calc_determinant_tensor_matrix_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_calc_determinant_tensor_matrix ((unsigned int)0)
unsigned int vcop_calc_determinant_tensor_matrix_ctrl_count(void);

/***********************************************************/
#endif

