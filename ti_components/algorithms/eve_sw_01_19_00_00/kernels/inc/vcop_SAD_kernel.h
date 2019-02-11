#ifndef _TI_vcop_SAD_kernel_h_
#define _TI_vcop_SAD_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_SAD_char_int[56];

/* Basic Runner Function */
void vcop_SAD_char_int(
   __vptr_int8 in,
   __vptr_int8 ref,
   __vptr_int16 vert_sad,
   __vptr_int16 vert_sad_t,
   __vptr_int16 sad_array,
   int blk_w,
   int blk_h,
   int in_w,
   int in_h,
   int ref_w,
   int ref_h,
   int offset_horz,
   int offset_vert,
   int steps_horz,
   int steps_vert);
/* Custom Runner Function */
void vcop_SAD_char_int_custom(
   __vptr_int8 in,
   __vptr_int8 ref,
   __vptr_int16 vert_sad,
   __vptr_int16 vert_sad_t,
   __vptr_int16 sad_array,
   int blk_w,
   int blk_h,
   int in_w,
   int in_h,
   int ref_w,
   int ref_h,
   int offset_horz,
   int offset_vert,
   int steps_horz,
   int steps_vert,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_SAD_char_int_init(
   __vptr_int8 in,
   __vptr_int8 ref,
   __vptr_int16 vert_sad,
   __vptr_int16 vert_sad_t,
   __vptr_int16 sad_array,
   int blk_w,
   int blk_h,
   int in_w,
   int in_h,
   int ref_w,
   int ref_h,
   int offset_horz,
   int offset_vert,
   int steps_horz,
   int steps_vert,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_SAD_char_int_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_SAD_char_int ((unsigned int)56)
unsigned int vcop_SAD_char_int_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_SAD_char_int ((unsigned int)0)
unsigned int vcop_SAD_char_int_ctrl_count(void);

/***********************************************************/
#endif

