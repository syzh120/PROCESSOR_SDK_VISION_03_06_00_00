#ifndef _TI_vcop_rgb16_rgb_kernel_h_
#define _TI_vcop_rgb16_rgb_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_rgb555_rgb[22];

/* Basic Runner Function */
void vcop_rgb555_rgb(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b);
/* Custom Runner Function */
void vcop_rgb555_rgb_custom(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_rgb555_rgb_init(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_rgb555_rgb_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_rgb555_rgb ((unsigned int)22)
unsigned int vcop_rgb555_rgb_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_rgb555_rgb ((unsigned int)0)
unsigned int vcop_rgb555_rgb_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_rgb565_rgb[22];

/* Basic Runner Function */
void vcop_rgb565_rgb(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b);
/* Custom Runner Function */
void vcop_rgb565_rgb_custom(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_rgb565_rgb_init(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_rgb565_rgb_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_rgb565_rgb ((unsigned int)22)
unsigned int vcop_rgb565_rgb_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_rgb565_rgb ((unsigned int)0)
unsigned int vcop_rgb565_rgb_ctrl_count(void);

/***********************************************************/
#endif

