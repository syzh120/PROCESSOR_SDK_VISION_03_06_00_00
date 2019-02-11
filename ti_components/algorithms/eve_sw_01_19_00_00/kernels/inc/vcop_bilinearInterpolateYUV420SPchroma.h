#ifndef _TI_vcop_bilinearInterpolateYUV420SPchroma_h_
#define _TI_vcop_bilinearInterpolateYUV420SPchroma_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_bilinearInterpolateYUV420SPchroma[90];

/* Basic Runner Function */
void vcop_bilinearInterpolateYUV420SPchroma(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scattered_ofst,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned char stride,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset);
/* Custom Runner Function */
void vcop_bilinearInterpolateYUV420SPchroma_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scattered_ofst,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned char stride,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_bilinearInterpolateYUV420SPchroma_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scattered_ofst,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned char stride,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_bilinearInterpolateYUV420SPchroma_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_bilinearInterpolateYUV420SPchroma ((unsigned int)90)
unsigned int vcop_bilinearInterpolateYUV420SPchroma_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_bilinearInterpolateYUV420SPchroma ((unsigned int)0)
unsigned int vcop_bilinearInterpolateYUV420SPchroma_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_bilinearInterpolateYUV420SPchromaBB[66];

/* Basic Runner Function */
void vcop_bilinearInterpolateYUV420SPchromaBB(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set);
/* Custom Runner Function */
void vcop_bilinearInterpolateYUV420SPchromaBB_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_bilinearInterpolateYUV420SPchromaBB_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_bilinearInterpolateYUV420SPchromaBB_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_bilinearInterpolateYUV420SPchromaBB ((unsigned int)66)
unsigned int vcop_bilinearInterpolateYUV420SPchromaBB_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_bilinearInterpolateYUV420SPchromaBB ((unsigned int)0)
unsigned int vcop_bilinearInterpolateYUV420SPchromaBB_ctrl_count(void);

/***********************************************************/
#endif

