#ifndef _TI_vcop_raw2rgb_i16u_o16u_kernel_h_
#define _TI_vcop_raw2rgb_i16u_o16u_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_raw2rgb_CGGC_i16u_o16u[186];

/* Basic Runner Function */
void vcop_raw2rgb_CGGC_i16u_o16u(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride);
/* Custom Runner Function */
void vcop_raw2rgb_CGGC_i16u_o16u_custom(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_raw2rgb_CGGC_i16u_o16u_init(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_raw2rgb_CGGC_i16u_o16u_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_raw2rgb_CGGC_i16u_o16u ((unsigned int)186)
unsigned int vcop_raw2rgb_CGGC_i16u_o16u_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_raw2rgb_CGGC_i16u_o16u ((unsigned int)0)
unsigned int vcop_raw2rgb_CGGC_i16u_o16u_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_raw2rgb_GCCG_i16u_o16u[190];

/* Basic Runner Function */
void vcop_raw2rgb_GCCG_i16u_o16u(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride);
/* Custom Runner Function */
void vcop_raw2rgb_GCCG_i16u_o16u_custom(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_raw2rgb_GCCG_i16u_o16u_init(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_raw2rgb_GCCG_i16u_o16u_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_raw2rgb_GCCG_i16u_o16u ((unsigned int)190)
unsigned int vcop_raw2rgb_GCCG_i16u_o16u_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_raw2rgb_GCCG_i16u_o16u ((unsigned int)0)
unsigned int vcop_raw2rgb_GCCG_i16u_o16u_ctrl_count(void);

/***********************************************************/
#endif

