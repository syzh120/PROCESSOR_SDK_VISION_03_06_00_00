#ifndef _TI_vcop_bilinearInterpolateYUV422IchromaPblockUpdate_h_
#define _TI_vcop_bilinearInterpolateYUV422IchromaPblockUpdate_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_bilinearInterpolateYUV422IchromaUPblockUpdate[26];

/* Basic Runner Function */
void vcop_bilinearInterpolateYUV422IchromaUPblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16);
/* Custom Runner Function */
void vcop_bilinearInterpolateYUV422IchromaUPblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_bilinearInterpolateYUV422IchromaUPblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_bilinearInterpolateYUV422IchromaUPblockUpdate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_bilinearInterpolateYUV422IchromaUPblockUpdate ((unsigned int)26)
unsigned int vcop_bilinearInterpolateYUV422IchromaUPblockUpdate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_bilinearInterpolateYUV422IchromaUPblockUpdate ((unsigned int)0)
unsigned int vcop_bilinearInterpolateYUV422IchromaUPblockUpdate_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_bilinearInterpolateYUV422IchromaVPblockUpdate[32];

/* Basic Runner Function */
void vcop_bilinearInterpolateYUV422IchromaVPblockUpdate(
   __vptr_uint16 numMappedVPixels_ptr,
   __vptr_uint16 numMappedUPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int scatterStoreArray_ptr,
   __vptr_uint32 pBlock32);
/* Custom Runner Function */
void vcop_bilinearInterpolateYUV422IchromaVPblockUpdate_custom(
   __vptr_uint16 numMappedVPixels_ptr,
   __vptr_uint16 numMappedUPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int scatterStoreArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_bilinearInterpolateYUV422IchromaVPblockUpdate_init(
   __vptr_uint16 numMappedVPixels_ptr,
   __vptr_uint16 numMappedUPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int scatterStoreArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_bilinearInterpolateYUV422IchromaVPblockUpdate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_bilinearInterpolateYUV422IchromaVPblockUpdate ((unsigned int)32)
unsigned int vcop_bilinearInterpolateYUV422IchromaVPblockUpdate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_bilinearInterpolateYUV422IchromaVPblockUpdate ((unsigned int)0)
unsigned int vcop_bilinearInterpolateYUV422IchromaVPblockUpdate_ctrl_count(void);

/***********************************************************/
#endif

