#ifndef _TI_vcop_nnInterpolate422IchromaPblockUpdate_h_
#define _TI_vcop_nnInterpolate422IchromaPblockUpdate_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_nnInterpolate422IchromaUPblockUpdate[18];

/* Basic Runner Function */
void vcop_nnInterpolate422IchromaUPblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16);
/* Custom Runner Function */
void vcop_nnInterpolate422IchromaUPblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nnInterpolate422IchromaUPblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nnInterpolate422IchromaUPblockUpdate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nnInterpolate422IchromaUPblockUpdate ((unsigned int)18)
unsigned int vcop_nnInterpolate422IchromaUPblockUpdate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nnInterpolate422IchromaUPblockUpdate ((unsigned int)0)
unsigned int vcop_nnInterpolate422IchromaUPblockUpdate_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_nnInterpolate422IchromaVPblockUpdate[24];

/* Basic Runner Function */
void vcop_nnInterpolate422IchromaVPblockUpdate(
   __vptr_uint16 numMappedVPixels_ptr,
   __vptr_uint16 numMappedUPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int scatterStoreArray_ptr,
   __vptr_uint32 pBlock32);
/* Custom Runner Function */
void vcop_nnInterpolate422IchromaVPblockUpdate_custom(
   __vptr_uint16 numMappedVPixels_ptr,
   __vptr_uint16 numMappedUPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int scatterStoreArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nnInterpolate422IchromaVPblockUpdate_init(
   __vptr_uint16 numMappedVPixels_ptr,
   __vptr_uint16 numMappedUPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int scatterStoreArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nnInterpolate422IchromaVPblockUpdate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nnInterpolate422IchromaVPblockUpdate ((unsigned int)24)
unsigned int vcop_nnInterpolate422IchromaVPblockUpdate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nnInterpolate422IchromaVPblockUpdate ((unsigned int)0)
unsigned int vcop_nnInterpolate422IchromaVPblockUpdate_ctrl_count(void);

/***********************************************************/
#endif

