#ifndef _TI_vcop_bilinearInterpolateUV_h_
#define _TI_vcop_bilinearInterpolateUV_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_bilinearInterpolateUV[56];

/* Basic Runner Function */
void vcop_bilinearInterpolateUV(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned short stride,
   unsigned int inSize,
   __vptr_uint8 inLUT,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char mult,
   unsigned char rightShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set);
/* Custom Runner Function */
void vcop_bilinearInterpolateUV_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned short stride,
   unsigned int inSize,
   __vptr_uint8 inLUT,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char mult,
   unsigned char rightShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_bilinearInterpolateUV_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned short stride,
   unsigned int inSize,
   __vptr_uint8 inLUT,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char mult,
   unsigned char rightShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_bilinearInterpolateUV_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_bilinearInterpolateUV ((unsigned int)56)
unsigned int vcop_bilinearInterpolateUV_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_bilinearInterpolateUV ((unsigned int)0)
unsigned int vcop_bilinearInterpolateUV_ctrl_count(void);

/***********************************************************/
#endif

