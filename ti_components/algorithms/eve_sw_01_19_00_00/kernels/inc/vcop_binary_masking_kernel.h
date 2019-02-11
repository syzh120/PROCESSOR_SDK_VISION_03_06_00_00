#ifndef _TI_vcop_binary_masking_kernel_h_
#define _TI_vcop_binary_masking_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_binary_masking[16];

/* Basic Runner Function */
void vcop_binary_masking(
   __vptr_uint8 inByteData,
   __vptr_uint8 inBitPackedData,
   __vptr_uint8 outBitPackedData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputByteDataPitch,
   unsigned short inputBitDataPitch,
   unsigned short outputPitch);
/* Custom Runner Function */
void vcop_binary_masking_custom(
   __vptr_uint8 inByteData,
   __vptr_uint8 inBitPackedData,
   __vptr_uint8 outBitPackedData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputByteDataPitch,
   unsigned short inputBitDataPitch,
   unsigned short outputPitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_binary_masking_init(
   __vptr_uint8 inByteData,
   __vptr_uint8 inBitPackedData,
   __vptr_uint8 outBitPackedData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputByteDataPitch,
   unsigned short inputBitDataPitch,
   unsigned short outputPitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_binary_masking_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_binary_masking ((unsigned int)16)
unsigned int vcop_binary_masking_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_binary_masking ((unsigned int)0)
unsigned int vcop_binary_masking_ctrl_count(void);

/***********************************************************/
#endif

