#ifndef _TI_vcop_nonMaxSuppress_mxn_16s_kernel_h_
#define _TI_vcop_nonMaxSuppress_mxn_16s_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_nonMaxSuppress_mxn_16s[70];

/* Basic Runner Function */
void vcop_nonMaxSuppress_mxn_16s(
   __vptr_uint16 im_A,
   __vptr_uint8 out_B,
   __vptr_uint16 scratch_B,
   __vptr_uint16 scratch_C,
   unsigned short height,
   unsigned short width,
   unsigned short input_stride,
   unsigned short output_stride,
   unsigned short m,
   unsigned short n,
   short thresh);
/* Custom Runner Function */
void vcop_nonMaxSuppress_mxn_16s_custom(
   __vptr_uint16 im_A,
   __vptr_uint8 out_B,
   __vptr_uint16 scratch_B,
   __vptr_uint16 scratch_C,
   unsigned short height,
   unsigned short width,
   unsigned short input_stride,
   unsigned short output_stride,
   unsigned short m,
   unsigned short n,
   short thresh,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nonMaxSuppress_mxn_16s_init(
   __vptr_uint16 im_A,
   __vptr_uint8 out_B,
   __vptr_uint16 scratch_B,
   __vptr_uint16 scratch_C,
   unsigned short height,
   unsigned short width,
   unsigned short input_stride,
   unsigned short output_stride,
   unsigned short m,
   unsigned short n,
   short thresh,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nonMaxSuppress_mxn_16s_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nonMaxSuppress_mxn_16s ((unsigned int)70)
unsigned int vcop_nonMaxSuppress_mxn_16s_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nonMaxSuppress_mxn_16s ((unsigned int)0)
unsigned int vcop_nonMaxSuppress_mxn_16s_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_nonMaxSuppress_mxn_16sbitPack[62];

/* Basic Runner Function */
void vcop_nonMaxSuppress_mxn_16sbitPack(
   __vptr_int16 im_A,
   __vptr_uint8 out_B,
   __vptr_uint16 scratch_B,
   __vptr_uint16 scratch_C,
   unsigned short width,
   unsigned short height,
   unsigned short input_stride,
   unsigned short output_stride,
   unsigned short windowWidth,
   unsigned short windowHeight,
   short thresh);
/* Custom Runner Function */
void vcop_nonMaxSuppress_mxn_16sbitPack_custom(
   __vptr_int16 im_A,
   __vptr_uint8 out_B,
   __vptr_uint16 scratch_B,
   __vptr_uint16 scratch_C,
   unsigned short width,
   unsigned short height,
   unsigned short input_stride,
   unsigned short output_stride,
   unsigned short windowWidth,
   unsigned short windowHeight,
   short thresh,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nonMaxSuppress_mxn_16sbitPack_init(
   __vptr_int16 im_A,
   __vptr_uint8 out_B,
   __vptr_uint16 scratch_B,
   __vptr_uint16 scratch_C,
   unsigned short width,
   unsigned short height,
   unsigned short input_stride,
   unsigned short output_stride,
   unsigned short windowWidth,
   unsigned short windowHeight,
   short thresh,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nonMaxSuppress_mxn_16sbitPack_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nonMaxSuppress_mxn_16sbitPack ((unsigned int)62)
unsigned int vcop_nonMaxSuppress_mxn_16sbitPack_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nonMaxSuppress_mxn_16sbitPack ((unsigned int)0)
unsigned int vcop_nonMaxSuppress_mxn_16sbitPack_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_nonMaxSuppress_mxn_16sUpdateDstPtr[14];

/* Basic Runner Function */
void vcop_nonMaxSuppress_mxn_16sUpdateDstPtr(
   __vptr_uint32 pBlock,
   unsigned int pDstPtr1,
   unsigned int pDstPtr2,
   __vptr_uint16 pDstPtrOffset,
   unsigned short nmsBinPackPrmBlockOffset1,
   unsigned short nmsBinPackPrmBlockOffset2);
/* Custom Runner Function */
void vcop_nonMaxSuppress_mxn_16sUpdateDstPtr_custom(
   __vptr_uint32 pBlock,
   unsigned int pDstPtr1,
   unsigned int pDstPtr2,
   __vptr_uint16 pDstPtrOffset,
   unsigned short nmsBinPackPrmBlockOffset1,
   unsigned short nmsBinPackPrmBlockOffset2,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nonMaxSuppress_mxn_16sUpdateDstPtr_init(
   __vptr_uint32 pBlock,
   unsigned int pDstPtr1,
   unsigned int pDstPtr2,
   __vptr_uint16 pDstPtrOffset,
   unsigned short nmsBinPackPrmBlockOffset1,
   unsigned short nmsBinPackPrmBlockOffset2,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nonMaxSuppress_mxn_16sUpdateDstPtr_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nonMaxSuppress_mxn_16sUpdateDstPtr ((unsigned int)14)
unsigned int vcop_nonMaxSuppress_mxn_16sUpdateDstPtr_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nonMaxSuppress_mxn_16sUpdateDstPtr ((unsigned int)0)
unsigned int vcop_nonMaxSuppress_mxn_16sUpdateDstPtr_ctrl_count(void);

/***********************************************************/
#endif

