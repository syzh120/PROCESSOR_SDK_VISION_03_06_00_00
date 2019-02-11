#ifndef _TI_vcop_rgb_rgb16_kernel_h_
#define _TI_vcop_rgb_rgb16_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_rgb_rgb555[30];

/* Basic Runner Function */
void vcop_rgb_rgb555(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb555);
/* Custom Runner Function */
void vcop_rgb_rgb555_custom(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb555,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_rgb_rgb555_init(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb555,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_rgb_rgb555_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_rgb_rgb555 ((unsigned int)30)
unsigned int vcop_rgb_rgb555_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_rgb_rgb555 ((unsigned int)0)
unsigned int vcop_rgb_rgb555_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_rgb_rgb565[32];

/* Basic Runner Function */
void vcop_rgb_rgb565(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb565);
/* Custom Runner Function */
void vcop_rgb_rgb565_custom(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb565,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_rgb_rgb565_init(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb565,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_rgb_rgb565_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_rgb_rgb565 ((unsigned int)32)
unsigned int vcop_rgb_rgb565_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_rgb_rgb565 ((unsigned int)0)
unsigned int vcop_rgb_rgb565_ctrl_count(void);

/***********************************************************/
#endif

