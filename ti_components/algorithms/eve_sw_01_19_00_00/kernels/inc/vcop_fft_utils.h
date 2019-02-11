#ifndef _TI_vcop_fft_utils_h_
#define _TI_vcop_fft_utils_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_zero_padding_kernel[10];

/* Basic Runner Function */
void vcop_fft_zero_padding_kernel(
   __vptr_uint32 inputData,
   unsigned short numActualPoints,
   unsigned short numOfLines,
   unsigned short numPointsZeroPadding,
   unsigned short pitch);
/* Custom Runner Function */
void vcop_fft_zero_padding_kernel_custom(
   __vptr_uint32 inputData,
   unsigned short numActualPoints,
   unsigned short numOfLines,
   unsigned short numPointsZeroPadding,
   unsigned short pitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_zero_padding_kernel_init(
   __vptr_uint32 inputData,
   unsigned short numActualPoints,
   unsigned short numOfLines,
   unsigned short numPointsZeroPadding,
   unsigned short pitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_zero_padding_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_zero_padding_kernel ((unsigned int)10)
unsigned int vcop_fft_zero_padding_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_zero_padding_kernel ((unsigned int)0)
unsigned int vcop_fft_zero_padding_kernel_ctrl_count(void);

/***********************************************************/
#endif

