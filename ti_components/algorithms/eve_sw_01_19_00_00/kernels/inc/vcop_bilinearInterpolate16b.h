#ifndef _TI_vcop_bilinearInterpolate16b_h_
#define _TI_vcop_bilinearInterpolate16b_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_bilinearInterpolate16b[66];

/* Basic Runner Function */
void vcop_bilinearInterpolate16b(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint16 scratchLUT,
   __vptr_uint16 scratchPixel,
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
void vcop_bilinearInterpolate16b_custom(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint16 scratchLUT,
   __vptr_uint16 scratchPixel,
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
unsigned int vcop_bilinearInterpolate16b_init(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint16 scratchLUT,
   __vptr_uint16 scratchPixel,
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
void vcop_bilinearInterpolate16b_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_bilinearInterpolate16b ((unsigned int)66)
unsigned int vcop_bilinearInterpolate16b_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_bilinearInterpolate16b ((unsigned int)0)
unsigned int vcop_bilinearInterpolate16b_ctrl_count(void);

/***********************************************************/
#endif

