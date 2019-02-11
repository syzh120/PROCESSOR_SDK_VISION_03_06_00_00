#ifndef _TI_vcop_nnInterpolate422Ichroma_h_
#define _TI_vcop_nnInterpolate422Ichroma_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_nnInterpolate422Ichroma[36];

/* Basic Runner Function */
void vcop_nnInterpolate422Ichroma(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set);
/* Custom Runner Function */
void vcop_nnInterpolate422Ichroma_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nnInterpolate422Ichroma_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nnInterpolate422Ichroma_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nnInterpolate422Ichroma ((unsigned int)36)
unsigned int vcop_nnInterpolate422Ichroma_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nnInterpolate422Ichroma ((unsigned int)0)
unsigned int vcop_nnInterpolate422Ichroma_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_nnInterpolate422IchromaBB[28];

/* Basic Runner Function */
void vcop_nnInterpolate422IchromaBB(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 scratchHbuf,
   __vptr_uint8 scattered_ofst,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set);
/* Custom Runner Function */
void vcop_nnInterpolate422IchromaBB_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 scratchHbuf,
   __vptr_uint8 scattered_ofst,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nnInterpolate422IchromaBB_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 scratchHbuf,
   __vptr_uint8 scattered_ofst,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nnInterpolate422IchromaBB_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nnInterpolate422IchromaBB ((unsigned int)28)
unsigned int vcop_nnInterpolate422IchromaBB_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nnInterpolate422IchromaBB ((unsigned int)0)
unsigned int vcop_nnInterpolate422IchromaBB_ctrl_count(void);

/***********************************************************/
#endif

