#ifndef _TI_vcop_intensity_scaling_kernel_h_
#define _TI_vcop_intensity_scaling_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_intensity_scaling[14];

/* Basic Runner Function */
void vcop_intensity_scaling(
   __vptr_uint8 inImg_A,
   __vptr_uint8 scalingLUT_C,
   __vptr_uint8 outImg_B,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride);
/* Custom Runner Function */
void vcop_intensity_scaling_custom(
   __vptr_uint8 inImg_A,
   __vptr_uint8 scalingLUT_C,
   __vptr_uint8 outImg_B,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_intensity_scaling_init(
   __vptr_uint8 inImg_A,
   __vptr_uint8 scalingLUT_C,
   __vptr_uint8 outImg_B,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_intensity_scaling_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_intensity_scaling ((unsigned int)14)
unsigned int vcop_intensity_scaling_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_intensity_scaling ((unsigned int)0)
unsigned int vcop_intensity_scaling_ctrl_count(void);

/***********************************************************/
#endif

