#ifndef _TI_vcop_vec_bin_image_dilate_mask_kernel_h_
#define _TI_vcop_vec_bin_image_dilate_mask_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_vec_bin_image_dilate_mask[32];

/* Basic Runner Function */
void vcop_vec_bin_image_dilate_mask(
   __vptr_uint32 pIn,
   __vptr_uint32 mask0,
   __vptr_uint32 mask1,
   __vptr_uint32 mask2,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height);
/* Custom Runner Function */
void vcop_vec_bin_image_dilate_mask_custom(
   __vptr_uint32 pIn,
   __vptr_uint32 mask0,
   __vptr_uint32 mask1,
   __vptr_uint32 mask2,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vec_bin_image_dilate_mask_init(
   __vptr_uint32 pIn,
   __vptr_uint32 mask0,
   __vptr_uint32 mask1,
   __vptr_uint32 mask2,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vec_bin_image_dilate_mask_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vec_bin_image_dilate_mask ((unsigned int)32)
unsigned int vcop_vec_bin_image_dilate_mask_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vec_bin_image_dilate_mask ((unsigned int)0)
unsigned int vcop_vec_bin_image_dilate_mask_ctrl_count(void);

/***********************************************************/
#endif

