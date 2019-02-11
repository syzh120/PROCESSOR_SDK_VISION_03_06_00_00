#ifndef _TI_vcop_gauss5x5PyramidKernel_8_kernel_h_
#define _TI_vcop_gauss5x5PyramidKernel_8_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_gauss5x5PyramidKernel_8_horiz[22];

/* Basic Runner Function */
void vcop_gauss5x5PyramidKernel_8_horiz(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch);
/* Custom Runner Function */
void vcop_gauss5x5PyramidKernel_8_horiz_custom(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gauss5x5PyramidKernel_8_horiz_init(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gauss5x5PyramidKernel_8_horiz_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gauss5x5PyramidKernel_8_horiz ((unsigned int)22)
unsigned int vcop_gauss5x5PyramidKernel_8_horiz_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gauss5x5PyramidKernel_8_horiz ((unsigned int)0)
unsigned int vcop_gauss5x5PyramidKernel_8_horiz_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_gauss5x5PyramidKernel_8_vert[24];

/* Basic Runner Function */
void vcop_gauss5x5PyramidKernel_8_vert(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch);
/* Custom Runner Function */
void vcop_gauss5x5PyramidKernel_8_vert_custom(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gauss5x5PyramidKernel_8_vert_init(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gauss5x5PyramidKernel_8_vert_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gauss5x5PyramidKernel_8_vert ((unsigned int)24)
unsigned int vcop_gauss5x5PyramidKernel_8_vert_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gauss5x5PyramidKernel_8_vert ((unsigned int)0)
unsigned int vcop_gauss5x5PyramidKernel_8_vert_ctrl_count(void);

/***********************************************************/
#endif

