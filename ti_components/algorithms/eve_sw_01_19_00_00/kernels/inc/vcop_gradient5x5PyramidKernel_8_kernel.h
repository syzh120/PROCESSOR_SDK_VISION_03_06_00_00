#ifndef _TI_vcop_gradient5x5PyramidKernel_8_kernel_h_
#define _TI_vcop_gradient5x5PyramidKernel_8_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_gradientH5x5PyramidKernel_8[50];

/* Basic Runner Function */
void vcop_gradientH5x5PyramidKernel_8(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut);
/* Custom Runner Function */
void vcop_gradientH5x5PyramidKernel_8_custom(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gradientH5x5PyramidKernel_8_init(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gradientH5x5PyramidKernel_8_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gradientH5x5PyramidKernel_8 ((unsigned int)50)
unsigned int vcop_gradientH5x5PyramidKernel_8_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gradientH5x5PyramidKernel_8 ((unsigned int)0)
unsigned int vcop_gradientH5x5PyramidKernel_8_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_gradientV5x5PyramidKernel_8[50];

/* Basic Runner Function */
void vcop_gradientV5x5PyramidKernel_8(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut);
/* Custom Runner Function */
void vcop_gradientV5x5PyramidKernel_8_custom(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gradientV5x5PyramidKernel_8_init(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gradientV5x5PyramidKernel_8_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gradientV5x5PyramidKernel_8 ((unsigned int)50)
unsigned int vcop_gradientV5x5PyramidKernel_8_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gradientV5x5PyramidKernel_8 ((unsigned int)0)
unsigned int vcop_gradientV5x5PyramidKernel_8_ctrl_count(void);

/***********************************************************/
#endif

