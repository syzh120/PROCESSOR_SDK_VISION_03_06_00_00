#ifndef _TI_vcop_census_16bits_kernel_h_
#define _TI_vcop_census_16bits_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_census_16bits[86];

/* Basic Runner Function */
void vcop_census_16bits(
   __vptr_uint16 pIn16,
   __vptr_uint8 pOut,
   __vptr_uint8 pScratchBitmask,
   __vptr_uint16 pScratch16,
   __vptr_uint8 pScratch8,
   __vptr_uint16 pOffset,
   __vptr_uint8 pCodeWordMask,
   __vptr_uint8 pRowMask,
   unsigned char winWidth,
   unsigned char winHeight,
   unsigned char winHorzStep,
   unsigned char winVertStep,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inStride,
   unsigned short outStride,
   unsigned short scratchStride);
/* Custom Runner Function */
void vcop_census_16bits_custom(
   __vptr_uint16 pIn16,
   __vptr_uint8 pOut,
   __vptr_uint8 pScratchBitmask,
   __vptr_uint16 pScratch16,
   __vptr_uint8 pScratch8,
   __vptr_uint16 pOffset,
   __vptr_uint8 pCodeWordMask,
   __vptr_uint8 pRowMask,
   unsigned char winWidth,
   unsigned char winHeight,
   unsigned char winHorzStep,
   unsigned char winVertStep,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inStride,
   unsigned short outStride,
   unsigned short scratchStride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_census_16bits_init(
   __vptr_uint16 pIn16,
   __vptr_uint8 pOut,
   __vptr_uint8 pScratchBitmask,
   __vptr_uint16 pScratch16,
   __vptr_uint8 pScratch8,
   __vptr_uint16 pOffset,
   __vptr_uint8 pCodeWordMask,
   __vptr_uint8 pRowMask,
   unsigned char winWidth,
   unsigned char winHeight,
   unsigned char winHorzStep,
   unsigned char winVertStep,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inStride,
   unsigned short outStride,
   unsigned short scratchStride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_census_16bits_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_census_16bits ((unsigned int)86)
unsigned int vcop_census_16bits_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_census_16bits ((unsigned int)0)
unsigned int vcop_census_16bits_ctrl_count(void);

/***********************************************************/
#endif

