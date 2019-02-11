#ifndef _TI_vcop_chromaTLUIndexCalcPblockUpdate_h_
#define _TI_vcop_chromaTLUIndexCalcPblockUpdate_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate[14];

/* Basic Runner Function */
void vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16);
/* Custom Runner Function */
void vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate ((unsigned int)14)
unsigned int vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate ((unsigned int)0)
unsigned int vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate[14];

/* Basic Runner Function */
void vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16);
/* Custom Runner Function */
void vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate ((unsigned int)14)
unsigned int vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate ((unsigned int)0)
unsigned int vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_ctrl_count(void);

/***********************************************************/
#endif

