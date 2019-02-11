#ifndef _TI_vcop_dsTLUindexAndFracPblockUpdate_h_
#define _TI_vcop_dsTLUindexAndFracPblockUpdate_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_dsTLUindexAndFracBilInterpolatePblockUpdate[36];

/* Basic Runner Function */
void vcop_dsTLUindexAndFracBilInterpolatePblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32);
/* Custom Runner Function */
void vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_dsTLUindexAndFracBilInterpolatePblockUpdate ((unsigned int)36)
unsigned int vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_dsTLUindexAndFracBilInterpolatePblockUpdate ((unsigned int)0)
unsigned int vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_dsTLUindexAndFracNNInterpolatePblockUpdate[36];

/* Basic Runner Function */
void vcop_dsTLUindexAndFracNNInterpolatePblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32);
/* Custom Runner Function */
void vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_dsTLUindexAndFracNNInterpolatePblockUpdate ((unsigned int)36)
unsigned int vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_dsTLUindexAndFracNNInterpolatePblockUpdate ((unsigned int)0)
unsigned int vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_ctrl_count(void);

/***********************************************************/
#endif

