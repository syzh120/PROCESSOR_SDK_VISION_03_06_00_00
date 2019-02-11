#ifndef _TI_vcop_bin_image_to_list_kernel_h_
#define _TI_vcop_bin_image_to_list_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_bin_image_to_list[38];

/* Basic Runner Function */
void vcop_bin_image_to_list(
   __vptr_uint8 im_A,
   __vptr_uint32 upperLeftXY,
   __vptr_uint32 outXY_B,
   __vptr_uint32 listSize,
   unsigned short width,
   unsigned short height,
   unsigned short inputStride,
   unsigned char outputQformat,
   __vptr_uint32 xSequence_C);
/* Custom Runner Function */
void vcop_bin_image_to_list_custom(
   __vptr_uint8 im_A,
   __vptr_uint32 upperLeftXY,
   __vptr_uint32 outXY_B,
   __vptr_uint32 listSize,
   unsigned short width,
   unsigned short height,
   unsigned short inputStride,
   unsigned char outputQformat,
   __vptr_uint32 xSequence_C,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_bin_image_to_list_init(
   __vptr_uint8 im_A,
   __vptr_uint32 upperLeftXY,
   __vptr_uint32 outXY_B,
   __vptr_uint32 listSize,
   unsigned short width,
   unsigned short height,
   unsigned short inputStride,
   unsigned char outputQformat,
   __vptr_uint32 xSequence_C,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_bin_image_to_list_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_bin_image_to_list ((unsigned int)38)
unsigned int vcop_bin_image_to_list_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_bin_image_to_list ((unsigned int)0)
unsigned int vcop_bin_image_to_list_ctrl_count(void);

/***********************************************************/
#endif

