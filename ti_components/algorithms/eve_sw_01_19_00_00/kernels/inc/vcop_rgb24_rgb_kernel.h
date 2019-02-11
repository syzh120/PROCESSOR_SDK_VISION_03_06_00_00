#ifndef _TI_vcop_rgb24_rgb_kernel_h_
#define _TI_vcop_rgb24_rgb_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_rgb24_rgb[28];

/* Basic Runner Function */
void vcop_rgb24_rgb(
   __vptr_uint32 rgb24,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b);
/* Custom Runner Function */
void vcop_rgb24_rgb_custom(
   __vptr_uint32 rgb24,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_rgb24_rgb_init(
   __vptr_uint32 rgb24,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_rgb24_rgb_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_rgb24_rgb ((unsigned int)28)
unsigned int vcop_rgb24_rgb_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_rgb24_rgb ((unsigned int)0)
unsigned int vcop_rgb24_rgb_ctrl_count(void);

/***********************************************************/
#endif

