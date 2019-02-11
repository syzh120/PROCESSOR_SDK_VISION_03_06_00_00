#ifndef _TI_vcop_yuv_scalar_kernel_h_
#define _TI_vcop_yuv_scalar_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_yuv_scalar_pixels_look_up_kernel[14];

/* Basic Runner Function */
void yuv_scalar_pixels_look_up_kernel(
   __vptr_uint32 src,
   __vptr_uint16 index,
   __vptr_uint32 outBuf,
   short int numTaps,
   short int src_w,
   short int dst_h);
/* Custom Runner Function */
void yuv_scalar_pixels_look_up_kernel_custom(
   __vptr_uint32 src,
   __vptr_uint16 index,
   __vptr_uint32 outBuf,
   short int numTaps,
   short int src_w,
   short int dst_h,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int yuv_scalar_pixels_look_up_kernel_init(
   __vptr_uint32 src,
   __vptr_uint16 index,
   __vptr_uint32 outBuf,
   short int numTaps,
   short int src_w,
   short int dst_h,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void yuv_scalar_pixels_look_up_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_yuv_scalar_pixels_look_up_kernel ((unsigned int)14)
unsigned int yuv_scalar_pixels_look_up_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_yuv_scalar_pixels_look_up_kernel ((unsigned int)0)
unsigned int yuv_scalar_pixels_look_up_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_yuv_scalar_interpolation_kernel[26];

/* Basic Runner Function */
void yuv_scalar_interpolation_kernel(
   __vptr_uint8 inPtr,
   __vptr_uint8 fracPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   __vptr_uint16 offsetPtr,
   short int tempBufPitch,
   short int fracBits,
   short int numTaps,
   short int src_w,
   short int src_pitch,
   short int dst_h);
/* Custom Runner Function */
void yuv_scalar_interpolation_kernel_custom(
   __vptr_uint8 inPtr,
   __vptr_uint8 fracPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   __vptr_uint16 offsetPtr,
   short int tempBufPitch,
   short int fracBits,
   short int numTaps,
   short int src_w,
   short int src_pitch,
   short int dst_h,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int yuv_scalar_interpolation_kernel_init(
   __vptr_uint8 inPtr,
   __vptr_uint8 fracPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   __vptr_uint16 offsetPtr,
   short int tempBufPitch,
   short int fracBits,
   short int numTaps,
   short int src_w,
   short int src_pitch,
   short int dst_h,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void yuv_scalar_interpolation_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_yuv_scalar_interpolation_kernel ((unsigned int)26)
unsigned int yuv_scalar_interpolation_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_yuv_scalar_interpolation_kernel ((unsigned int)0)
unsigned int yuv_scalar_interpolation_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_yuv_scalar_luma_copy_kernel[16];

/* Basic Runner Function */
void yuv_scalar_luma_copy_kernel(
   __vptr_uint32 outPtr,
   __vptr_uint32 temp1Ptr,
   __vptr_uint32 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h);
/* Custom Runner Function */
void yuv_scalar_luma_copy_kernel_custom(
   __vptr_uint32 outPtr,
   __vptr_uint32 temp1Ptr,
   __vptr_uint32 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int yuv_scalar_luma_copy_kernel_init(
   __vptr_uint32 outPtr,
   __vptr_uint32 temp1Ptr,
   __vptr_uint32 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void yuv_scalar_luma_copy_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_yuv_scalar_luma_copy_kernel ((unsigned int)16)
unsigned int yuv_scalar_luma_copy_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_yuv_scalar_luma_copy_kernel ((unsigned int)0)
unsigned int yuv_scalar_luma_copy_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_yuv_scalar_chroma_copy_kernel[16];

/* Basic Runner Function */
void yuv_scalar_chroma_copy_kernel(
   __vptr_uint8 outPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h);
/* Custom Runner Function */
void yuv_scalar_chroma_copy_kernel_custom(
   __vptr_uint8 outPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int yuv_scalar_chroma_copy_kernel_init(
   __vptr_uint8 outPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void yuv_scalar_chroma_copy_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_yuv_scalar_chroma_copy_kernel ((unsigned int)16)
unsigned int yuv_scalar_chroma_copy_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_yuv_scalar_chroma_copy_kernel ((unsigned int)0)
unsigned int yuv_scalar_chroma_copy_kernel_ctrl_count(void);

/***********************************************************/
#endif

