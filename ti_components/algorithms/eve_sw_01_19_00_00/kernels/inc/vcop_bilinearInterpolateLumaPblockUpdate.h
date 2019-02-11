#ifndef _TI_vcop_bilinearInterpolateLumaPblockUpdate_h_
#define _TI_vcop_bilinearInterpolateLumaPblockUpdate_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_bilinearInterpolateLumaPblockUpdate[24];

/* Basic Runner Function */
void vcop_bilinearInterpolateLumaPblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16);
/* Custom Runner Function */
void vcop_bilinearInterpolateLumaPblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_bilinearInterpolateLumaPblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_bilinearInterpolateLumaPblockUpdate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_bilinearInterpolateLumaPblockUpdate ((unsigned int)24)
unsigned int vcop_bilinearInterpolateLumaPblockUpdate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_bilinearInterpolateLumaPblockUpdate ((unsigned int)0)
unsigned int vcop_bilinearInterpolateLumaPblockUpdate_ctrl_count(void);

/***********************************************************/
#endif

