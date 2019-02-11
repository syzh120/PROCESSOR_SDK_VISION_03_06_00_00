#ifndef _TI_vcop_calc_inverse_structure_tensor_2x2_kernel_h_
#define _TI_vcop_calc_inverse_structure_tensor_2x2_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_calc_inverse_structure_tensor_2x2[54];

/* Basic Runner Function */
void vcop_calc_inverse_structure_tensor_2x2(
   __vptr_int32 pTensorArrInp_A,
   __vptr_uint16 pD_nrsb_B,
   __vptr_uint32 pD_norm_C,
   __vptr_int16 pInverseArrOut_A,
   __vptr_int32 pScratchNorm_C,
   __vptr_uint32 pScratchDividend_C,
   unsigned short inputStride,
   unsigned short outputStride,
   unsigned short numFracBits,
   unsigned short numKeyPoints);
/* Custom Runner Function */
void vcop_calc_inverse_structure_tensor_2x2_custom(
   __vptr_int32 pTensorArrInp_A,
   __vptr_uint16 pD_nrsb_B,
   __vptr_uint32 pD_norm_C,
   __vptr_int16 pInverseArrOut_A,
   __vptr_int32 pScratchNorm_C,
   __vptr_uint32 pScratchDividend_C,
   unsigned short inputStride,
   unsigned short outputStride,
   unsigned short numFracBits,
   unsigned short numKeyPoints,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_calc_inverse_structure_tensor_2x2_init(
   __vptr_int32 pTensorArrInp_A,
   __vptr_uint16 pD_nrsb_B,
   __vptr_uint32 pD_norm_C,
   __vptr_int16 pInverseArrOut_A,
   __vptr_int32 pScratchNorm_C,
   __vptr_uint32 pScratchDividend_C,
   unsigned short inputStride,
   unsigned short outputStride,
   unsigned short numFracBits,
   unsigned short numKeyPoints,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_calc_inverse_structure_tensor_2x2_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_calc_inverse_structure_tensor_2x2 ((unsigned int)54)
unsigned int vcop_calc_inverse_structure_tensor_2x2_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_calc_inverse_structure_tensor_2x2 ((unsigned int)0)
unsigned int vcop_calc_inverse_structure_tensor_2x2_ctrl_count(void);

/***********************************************************/
#endif

