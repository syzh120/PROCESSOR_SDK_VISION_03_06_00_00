#ifndef _TI_vcop_bilinearInterpolateYUV422Ichroma_h_
#define _TI_vcop_bilinearInterpolateYUV422Ichroma_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_bilinearInterpolateYUV422Ichroma[74];

/* Basic Runner Function */
void vcop_bilinearInterpolateYUV422Ichroma(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint16 scratchLUT,
   __vptr_uint8 scratchPixel,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set);
/* Custom Runner Function */
void vcop_bilinearInterpolateYUV422Ichroma_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint16 scratchLUT,
   __vptr_uint8 scratchPixel,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_bilinearInterpolateYUV422Ichroma_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint16 scratchLUT,
   __vptr_uint8 scratchPixel,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_bilinearInterpolateYUV422Ichroma_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_bilinearInterpolateYUV422Ichroma ((unsigned int)74)
unsigned int vcop_bilinearInterpolateYUV422Ichroma_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_bilinearInterpolateYUV422Ichroma ((unsigned int)0)
unsigned int vcop_bilinearInterpolateYUV422Ichroma_ctrl_count(void);

/***********************************************************/
#endif

