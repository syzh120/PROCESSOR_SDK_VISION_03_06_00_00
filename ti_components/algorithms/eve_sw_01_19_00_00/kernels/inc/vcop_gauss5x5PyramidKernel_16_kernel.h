#ifndef _TI_vcop_gauss5x5PyramidKernel_16_kernel_h_
#define _TI_vcop_gauss5x5PyramidKernel_16_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_gauss5x5PyramidKernel_16_horiz[22];

/* Basic Runner Function */
void vcop_gauss5x5PyramidKernel_16_horiz(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch);
/* Custom Runner Function */
void vcop_gauss5x5PyramidKernel_16_horiz_custom(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gauss5x5PyramidKernel_16_horiz_init(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gauss5x5PyramidKernel_16_horiz_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gauss5x5PyramidKernel_16_horiz ((unsigned int)22)
unsigned int vcop_gauss5x5PyramidKernel_16_horiz_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gauss5x5PyramidKernel_16_horiz ((unsigned int)0)
unsigned int vcop_gauss5x5PyramidKernel_16_horiz_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_gauss5x5PyramidKernel_16_vert[24];

/* Basic Runner Function */
void vcop_gauss5x5PyramidKernel_16_vert(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch);
/* Custom Runner Function */
void vcop_gauss5x5PyramidKernel_16_vert_custom(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gauss5x5PyramidKernel_16_vert_init(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gauss5x5PyramidKernel_16_vert_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gauss5x5PyramidKernel_16_vert ((unsigned int)24)
unsigned int vcop_gauss5x5PyramidKernel_16_vert_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gauss5x5PyramidKernel_16_vert ((unsigned int)0)
unsigned int vcop_gauss5x5PyramidKernel_16_vert_ctrl_count(void);

/***********************************************************/
#endif

